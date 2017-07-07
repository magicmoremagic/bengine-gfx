#include "pch.hpp"
#include "tex/betx_reader.hpp"
#include "tex/mipmapping.hpp"
#include "tex/byte_order.hpp"
#include "betx_header_.hpp"
#include "betx_read_error_.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/util/zlib.hpp>
#include <numeric>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_betx(const Buf<const UC>& buf) noexcept {
   using sig = detail::BetxSignature;
   return util::file_signature_matches(buf, sig::full) &&
      util::file_signature_matches(buf, buf.size() - sizeof(sig::footer), sig::footer);
}

///////////////////////////////////////////////////////////////////////////////
BetxReader::BetxReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     block_span_(0),
     big_endian_(false),
     payload_compression_(detail::BetxPayloadCompressionMode::none),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
void BetxReader::reset_impl_() noexcept {
   alignment_ = TextureAlignment();
   block_span_ = 0;
   big_endian_ = false;
   payload_compression_ = detail::BetxPayloadCompressionMode::none;
   texture_size_ = 0;
   payload_ = Buf<const UC>();
   metadata_ = Buf<const UC>();
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat BetxReader::format_impl_() noexcept {
   return TextureFileFormat::betx;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo BetxReader::info_impl_(std::error_code& ec) noexcept {
   using err = detail::BetxReadError;
   using sig = detail::BetxSignature;

   TextureFileInfo info;
   info.file_format = TextureFileFormat::betx;

   be_debug() << "Calculating beTx TextureFileInfo"
      & attr(ids::log_attr_path) << path().string()
      | log();

   if (buf_.size() < sizeof(sig::full) || !util::file_signature_matches(buf_, sig::mmm) &&
       !should_continue_(err::not_a_mmm_binary_file, ec)) {
      return info;
   }
   
   if (!util::file_signature_matches(buf_, sizeof(sig::mmm), sig::betx_a) &&
       !should_continue_(err::not_a_betx_file, ec)) {
      return info;
   }

   constexpr auto check_signature_offset = sizeof(sig::mmm) + sizeof(sig::betx_a);

   if (!util::file_signature_matches(buf_, check_signature_offset, sig::check)) {
      if (util::file_signature_matches(buf_, check_signature_offset, sig::lflf)) {
         if (should_continue_(err::crlf_corruption, ec)) {
            try_fix_crlf_corruption_(ec);
         } else {
            return info;
         }
      } else if (util::file_signature_matches(buf_, check_signature_offset, sig::crcr)) {
         if (should_continue_(err::lf_corruption, ec)) {
            try_fix_lf_corruption_(ec);
         } else {
            return info;
         }
      } else {
         if (!should_continue_(err::not_a_mmm_binary_file, ec)) {
            return info;
         }
      }
   }
   
   if (!util::file_signature_matches(buf_, check_signature_offset + sizeof(sig::check), sig::betx_b) &&
       !should_continue_(err::not_a_betx_file, ec)) {
      return info;
   }
   
   if (!util::file_signature_matches(buf_, buf_.size() - sizeof(sig::footer), sig::footer) &&
       !should_continue_(err::footer_missing, ec)) {
      return info;
   }

   detail::BetxHeader header;
   if (buf_.size() >= sizeof(detail::BetxHeader)) {
      std::memcpy(&header, buf_.get(), sizeof(detail::BetxHeader));
   } else if (!should_continue_(err::header_missing, ec)) {
      return info;
   } else {
      std::memset(&header, 0, sizeof(detail::BetxHeader));
   }

   if (header.endianness == 0) {
      big_endian_ = false;
      bo::static_to_host<bo::Little::value>(header);
   } else if (header.endianness == 0xFFu) {
      big_endian_ = true;
      bo::static_to_host<bo::Big::value>(header);
   } else if (!should_continue_(err::invalid_endianness, ec)) {
      return info;
   }

   switch (header.version) {
      case 0x1:
         info = info_v1_(header, ec);
         break;

      default:
         be_warn() << "Unknown beTx file version"
            & attr(ids::log_attr_version) << (int)buf_[16]
            & attr(ids::log_attr_path) << path().string()
            | log();

         if (!strict()) {
            std::error_code ec2;
            info = info_v1_(header, ec2);
            if (ec2 == TextureFileError::fatal_error) {
               if (!should_continue_(err::unsupported_file_version, ec)) {
                  return info;
               }
            } else if (!ec) {
               ec = ec2;
            }
         }
         break;
   }

   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture BetxReader::texture_(std::error_code& ec) noexcept {
   using err = detail::BetxReadError;
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (ec && (strict() || ec == TextureFileError::fatal_error)) {
      return tex;
   }

   if ((texture_size_ == 0 || !payload_) && !should_continue_(err::empty_texture, ec)) {
      return tex;
   }

   Buf<UC> data;
   bool use_data = false;

   switch (payload_compression_) {
      case detail::BetxPayloadCompressionMode::zlib: {
         std::error_code ec2;
         use_data = true;
         data = util::inflate_buf(payload_, texture_size_, ec2);
         should_continue_(ec2, ec);
         break;
      }

      default:
         break;
   }

   if ((use_data && data.size() < texture_size_ ||
       !use_data && payload_.size() < texture_size_) &&
       !should_continue_(err::not_enough_texture_data, ec)) {
      return tex;
   }

   try {
      if (use_data) {
         if (aligned_ptr(data.get(), alignment_.layer()) != data.get()) {
            // alignment off; realloc
            tex.storage = std::make_unique<TextureStorage>(i.layers, i.faces, i.levels, i.dim, i.format.block_dim(), block_span_, alignment_);
            if (tex.storage->size() > data.size()) {
               std::memset(tex.storage->data() + data.size(), 0, tex.storage->size() - data.size());
               if (data.size() > 0) {
                  std::memcpy(tex.storage->data(), data.get(), data.size());
               }
            } else {
               std::memcpy(tex.storage->data(), data.get(), tex.storage->size());
            }
         } else if (data.size() >= texture_size_) {
            // use data buffer as-is
            tex.storage = std::make_unique<TextureStorage>(i.layers, i.faces, i.levels, i.dim, i.format.block_dim(), block_span_, std::move(data), alignment_);
         } else {
            // not enough texture data
            tex.storage = std::make_unique<TextureStorage>(i.layers, i.faces, i.levels, i.dim, i.format.block_dim(), block_span_, alignment_);
            std::memset(tex.storage->data() + data.size(), 0, tex.storage->size() - data.size());
            if (data.size() > 0) {
               std::memcpy(tex.storage->data(), data.get(), data.size());
            }
         }
      } else {
         // using payload_; realloc
         tex.storage = std::make_unique<TextureStorage>(i.layers, i.faces, i.levels, i.dim, i.format.block_dim(), block_span_, alignment_);
         if (tex.storage->size() > payload_.size()) {
            std::memset(tex.storage->data() + payload_.size(), 0, tex.storage->size() - payload_.size());
            if (payload_.size() > 0) {
               std::memcpy(tex.storage->data(), payload_.get(), payload_.size());
            }
         } else {
            std::memcpy(tex.storage->data(), payload_.get(), tex.storage->size());
         }
      }
   } catch (const std::bad_alloc&) {
      if (!should_continue_(err::not_enough_memory, ec)) {
         return tex;
      }
   }

   if (tex.storage) {
      tex.view = TextureView(i.format, i.tex_class, *tex.storage, 0, i.layers, 0, i.faces, 0, i.levels);

      if (big_endian_ && std::is_same<bo::Host, bo::Little>::value ||
          !big_endian_ && std::is_same<bo::Host, bo::Big>::value) {
         reverse_endianness(*tex.storage, i.format.packing());
      }
   }

   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image BetxReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   using err = detail::BetxReadError;
   Image img;
   const TextureFileInfo& i = info(ec);
   if (ec && (strict() || ec == TextureFileError::fatal_error)) {
      return img;
   }

   if ((layer >= i.layers || face >= i.faces || level >= i.levels) && !should_continue_(err::image_unavailable, ec)) {
      return img;
   }

   if ((texture_size_ == 0 || !payload_) && !should_continue_(err::empty_texture, ec)) {
      return img;
   }

   TextureAlignment image_alignment = TextureAlignment(alignment_.line_bits(), alignment_.plane_bits());
   ivec3 image_dim = mipmap_dim(i.dim, (U8)level);

   std::error_code ec2;
   calculate_required_texture_storage(1, 1, 1, image_dim, i.format.block_dim(), block_span_, ec2, image_alignment);
   if (ec2 == std::errc::value_too_large) {
      if (!should_continue_(err::unsupported_alignment, ec)) {
         return img;
      }
   } else if (ec2 && !should_continue_(err::empty_texture, ec)) {
      return img;
   }

   ec2 = std::error_code();
   std::size_t image_offset = calculate_image_offset(layer, face, level, i.layers, i.faces, i.levels, i.dim, i.format.block_dim(), block_span_, ec2, alignment_);
   if (ec2 == std::errc::value_too_large) {
      if (!should_continue_(err::unsupported_alignment, ec)) {
         return img;
      }
   } else if (ec2 && !should_continue_(err::image_unavailable, ec)) {
      return img;
   }

   Buf<UC> data;
   bool use_data = false;

   switch (payload_compression_) {
      case detail::BetxPayloadCompressionMode::zlib: {
         ec2 = std::error_code();
         use_data = true;
         data = util::inflate_buf(payload_, texture_size_, ec2);
         should_continue_(ec2, ec);
         break;
      }

      default:
         break;
   }

   if ((use_data && data.size() < texture_size_ ||
       !use_data && payload_.size() < texture_size_) &&
       !should_continue_(err::not_enough_texture_data, ec)) {
      return img;
   }

   try {
      if (use_data) {
         img.storage = std::make_unique<TextureStorage>(1, 1, 1, image_dim, i.format.block_dim(), block_span_, image_alignment);
         std::size_t data_bytes = data.size() > image_offset ? data.size() - image_offset : 0;
         if (img.storage->size() > data_bytes) {
            std::memset(img.storage->data() + data_bytes, 0, img.storage->size() - data_bytes);
            if (data_bytes > 0) {
               std::memcpy(img.storage->data(), data.get() + image_offset, data_bytes);
            }
         } else {
            std::memcpy(img.storage->data(), data.get() + image_offset, img.storage->size());
         }
      } else { // using payload_
         img.storage = std::make_unique<TextureStorage>(1, 1, 1, image_dim, i.format.block_dim(), block_span_, image_alignment);
         std::size_t payload_bytes = payload_.size() > image_offset ? payload_.size() - image_offset : 0;
         if (img.storage->size() > payload_bytes) {
            std::memset(img.storage->data() + payload_bytes, 0, img.storage->size() - payload_bytes);
            if (payload_bytes > 0) {
               std::memcpy(img.storage->data(), payload_.get() + image_offset, payload_bytes);
            }
         } else {
            std::memcpy(img.storage->data(), payload_.get() + image_offset, img.storage->size());
         }
      }
   } catch (const std::bad_alloc&) {
      if (!should_continue_(err::not_enough_memory, ec)) {
         return img;
      }
   }

   if (img.storage) {
      img.view = ImageView(i.format, *img.storage, 0, 0, 0);

      if (big_endian_ && std::is_same<bo::Host, bo::Little>::value ||
          !big_endian_ && std::is_same<bo::Host, bo::Big>::value) {
         reverse_endianness(*img.storage, i.format.packing());
      }
   }

   return img;
}

///////////////////////////////////////////////////////////////////////////////
bool BetxReader::should_continue_(std::error_code new_error, std::error_code& ec) const noexcept {
   if (!ec || ec != TextureFileError::fatal_error && new_error == TextureFileError::fatal_error) {
      ec = new_error;
   }

   if (!ec) {
      return true;
   }

   if (!strict() && new_error != TextureFileError::fatal_error) {
      be_info() << "Error while reading beTx file; continuing"
         & attr(ids::log_attr_category) << new_error.category().name()
         & attr(ids::log_attr_error_code) << new_error.value()
         & attr(ids::log_attr_description) << new_error.message()
         & attr(ids::log_attr_path) << path().string()
         | log();

      return true;
   }

   if (new_error != ec) {
      be_warn() << "Error while reading beTx file: aborting"
         & attr(ids::log_attr_category) << new_error.category().name()
         & attr(ids::log_attr_error_code) << new_error.value()
         & attr(ids::log_attr_description) << new_error.message()
         & attr(ids::log_attr_path) << path().string()
         | log();
   }

   return false;
}

///////////////////////////////////////////////////////////////////////////////
void BetxReader::try_fix_crlf_corruption_(std::error_code& ec) noexcept {
   using sig = detail::BetxSignature;

   // replace all LFs (except the one at byte 10) with CR-LFs
   be_warn() << "Attempting to fix CR-LF corruption in beTx file"
      & attr(ids::log_attr_path) << path().string()
      | log();
   
   std::size_t offset = sizeof(sig::mmm) + sizeof(sig::betx_a) + sizeof(sig::lflf);

   const UC* src = buf_.get() + offset;
   const UC* src_end = buf_.get() + buf_.size();

   UC prev = 0;
   std::size_t count = 0;
   while (src < src_end) {
      UC c = *src;
      if (c == '\n' && prev != '\r') {
         ++count;
      }
      prev = c;
   }

   try {
      Buf<UC> new_buf = make_buf<UC>(buf_.size() - offset + sizeof(sig::mmm) + sizeof(sig::betx_a) + sizeof(sig::check) + count);

      src = buf_.get() + offset;
      src_end = buf_.get() + buf_.size();

      UC* dest = new_buf.get();
      UC* dest_end = new_buf.get() + new_buf.size();
      std::memcpy(dest, sig::mmm, sizeof(sig::mmm)); dest += sizeof(sig::mmm);
      std::memcpy(dest, sig::betx_a, sizeof(sig::betx_a)); dest += sizeof(sig::betx_a);
      std::memcpy(dest, sig::check, sizeof(sig::check)); dest += sizeof(sig::check);

      prev = 0;
      while (src < src_end && dest < dest_end) {
         UC c = *src;
         if (c == '\n' && prev != '\r' && (dest + 1 < dest_end)) {
            dest[0] = '\r';
            dest[1] = '\n';
            dest += 2;
         } else {
            *dest = c;
            ++dest;
         }
         prev = c;
      }

      buf_ = std::move(new_buf);
   } catch (const std::bad_alloc&) {
      be_warn() << "Failed to allocate memory for new payload while attempting to fix CR-LF corruption"
         & attr(ids::log_attr_path) << path().string()
         | log();
   }
}

///////////////////////////////////////////////////////////////////////////////
void BetxReader::try_fix_lf_corruption_(std::error_code& ec) noexcept {
   using sig = detail::BetxSignature;
   // replace all CR-LFs with LFs (except the one at byte 11)
   be_warn() << "Attempting to fix LF corruption in beTx file"
      & attr(ids::log_attr_path) << path().string()
      | log();

   std::size_t offset = sizeof(sig::mmm) + sizeof(sig::betx_a) + sizeof(sig::crcr);

   const UC* src = buf_.get() + offset;
   const UC* src_end = buf_.get() + buf_.size();

   UC prev = 0;
   std::size_t count = 0;
   while (src < src_end) {
      UC c = *src;
      if (c == '\n' && prev == '\r') {
         ++count;
      }
      prev = c;
   }

   try {
      Buf<UC> new_buf = make_buf<UC>(buf_.size() - offset + sizeof(sig::mmm) + sizeof(sig::betx_a) + sizeof(sig::check) - count);

      src = buf_.get() + offset;
      src_end = buf_.get() + buf_.size();

      UC* dest = new_buf.get();
      UC* dest_end = new_buf.get() + new_buf.size();
      std::memcpy(dest, sig::mmm, sizeof(sig::mmm)); dest += sizeof(sig::mmm);
      std::memcpy(dest, sig::betx_a, sizeof(sig::betx_a)); dest += sizeof(sig::betx_a);
      std::memcpy(dest, sig::check, sizeof(sig::check)); dest += sizeof(sig::check);

      prev = 0;
      while (src < src_end && dest < dest_end) {
         UC c = *src;
         if (c == '\n' && prev == '\r') {
            *(dest - 1) = '\n';
         } else {
            *dest = c;
            ++dest;
         }
         prev = c;
      }

      buf_ = std::move(new_buf);
   } catch (const std::bad_alloc&) {
      be_warn() << "Failed to allocate memory for new payload while attempting to fix LF corruption"
         & attr(ids::log_attr_path) << path().string()
         | log();
   }
}

} // be::gfx::tex
