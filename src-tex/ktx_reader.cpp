#include "pch.hpp"
#include "ktx_header_.hpp"
#include "tex/ktx_reader.hpp"
#include "tex/ktx_read_error.hpp"
#include "tex/byte_order.hpp"
#include "tex/mipmapping.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {
namespace {

constexpr UC short_sig[] = { 0xAB, 'K', 'T', 'X', ' ' };
constexpr UC version_sig[] = { 0xAB, 'K', 'T', 'X', ' ', '1', '1' };
constexpr UC full_sig[] = { 0xAB, 'K', 'T', 'X', ' ', '1', '1', 0xBB, '\r', '\n', 0x1A, '\n' };

} // be::gfx::tex::()

///////////////////////////////////////////////////////////////////////////////
bool is_ktx(const Buf<const UC>& buf) noexcept {
   return util::file_signature_matches(buf, short_sig);
}

///////////////////////////////////////////////////////////////////////////////
KtxReader::KtxReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     big_endian_(false),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
const std::vector<std::pair<SV, SV>>& KtxReader::metadata() {
   if (metadata_.empty()) {
      info();
   }
   return metadata_;
}

///////////////////////////////////////////////////////////////////////////////
const std::vector<std::pair<SV, SV>>& KtxReader::metadata(std::error_code& ec) noexcept {
   if (metadata_.empty()) {
      info(ec);
   }
   return metadata_;
}

///////////////////////////////////////////////////////////////////////////////
void KtxReader::reset_impl_() noexcept {
   big_endian_ = false;
   texture_size_ = 0;
   payload_ = Buf<const UC>();
   metadata_.clear();
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat KtxReader::format_impl_() noexcept {
   return TextureFileFormat::ktx;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo KtxReader::info_impl_(std::error_code& ec) noexcept {
   using err = detail::KtxReadError;

   TextureFileInfo info;
   info.file_format = TextureFileFormat::ktx;

   be_debug() << "Calculating KTX TextureFileInfo"
      & attr(ids::log_attr_path) << path().string()
      | log();

   if (!util::file_signature_matches(buf_, short_sig) &&
       !should_continue_(err::not_a_ktx_file, ec)) {
      return info;
   }

   if (!util::file_signature_matches(buf_, version_sig) &&
       !should_continue_(err::unsupported_file_version, ec)) {
      return info;
   }

   if (!util::file_signature_matches(buf_, full_sig) &&
       !should_continue_(err::file_corruption, ec)) {
      return info;
   }

   detail::KtxHeader header;
   if (buf_.size() >= sizeof(detail::KtxHeader)) {
      std::memcpy(&header, buf_.get(), sizeof(detail::KtxHeader));
   } else if (!should_continue_(err::header_missing, ec)) {
      return info;
   } else {
      std::memset(&header, 0, sizeof(detail::KtxHeader));
   }

   if (buf_[12] == 1 && buf_[13] == 2 && buf_[14] == 3 && buf_[15] == 4) {
      big_endian_ = false;
      bo::static_to_host<bo::Little::value>(header);
   } else if (buf_[12] == 4 && buf_[13] == 3 && buf_[14] == 2 && buf_[15] == 1) {
      big_endian_ = true;
      bo::static_to_host<bo::Big::value>(header);
   } else if (!should_continue_(err::unsupported_endianness, ec)) {
      return info;
   }

   return info_v11_(header, ec);
}

///////////////////////////////////////////////////////////////////////////////
Texture KtxReader::texture_(std::error_code& ec) noexcept {
   using err = detail::KtxReadError;
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (ec && (strict() || ec == TextureFileError::fatal_error)) {
      return tex;
   }

   if ((texture_size_ == 0 || !payload_) && !should_continue_(err::empty_texture, ec)) {
      return tex;
   }

   try {
      tex.storage = std::make_unique<TextureStorage>(i.layers, i.faces, i.levels, i.dim, i.format.block_dim(), i.format.block_size(), TextureAlignment(2));
      tex.view = TextureView(i.format, i.tex_class, *tex.storage, 0, i.layers, 0, i.faces, 0, i.levels);

      std::size_t offset = 0;
      for (auto level = 0; level < i.levels; ++level) {
         offset += sizeof(U32); // skip useless imageSize field

         for (auto layer = 0; layer < i.layers; ++layer) {
            for (auto face = 0; face < i.faces; ++face) {
               ImageView v = tex.view.image(layer, face, level);

               if (payload_.size() >= offset + v.size()) {
                  std::memcpy(v.data(), payload_.get() + offset, v.size());
               } else {
                  std::memset(v.data(), 0, v.size());
               }

               offset += v.size();
            }
         }
      }

      if (big_endian_ && std::is_same<bo::Host, bo::Little>::value ||
          !big_endian_ && std::is_same<bo::Host, bo::Big>::value) {
         reverse_endianness(*tex.storage, i.format.packing());
      }
   } catch (const std::bad_alloc&) {
      if (!should_continue_(err::not_enough_memory, ec)) {
         return tex;
      }
   }

   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image KtxReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   using err = detail::KtxReadError;
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

   ivec3 image_dim = mipmap_dim(i.dim, (U8)level);

   std::error_code ec2;
   std::size_t image_offset = calculate_image_offset(layer, face, level, i.layers, i.faces, i.levels, i.dim, i.format.block_dim(), i.format.block_size(), ec2, TextureAlignment(2));
   image_offset += sizeof(U32) * level;
   if (ec2 && !should_continue_(err::image_unavailable, ec)) {
      return img;
   }

   try {
      img.storage = std::make_unique<TextureStorage>(1, 1, 1, image_dim, i.format.block_dim(), i.format.block_size(), TextureAlignment(2));
      img.view = ImageView(i.format, *img.storage, 0, 0, 0);

      if (payload_.size() >= image_offset + img.view.size()) {
         std::memcpy(img.view.data(), payload_.get() + image_offset, img.view.size());
      } else {
         std::memset(img.view.data(), 0, img.view.size());
      }

      if (big_endian_ && std::is_same<bo::Host, bo::Little>::value ||
          !big_endian_ && std::is_same<bo::Host, bo::Big>::value) {
         reverse_endianness(*img.storage, i.format.packing());
      }

   } catch (const std::bad_alloc&) {
      if (!should_continue_(err::not_enough_memory, ec)) {
         return img;
      }
   }

   return img;
}

///////////////////////////////////////////////////////////////////////////////
bool KtxReader::should_continue_(std::error_code new_error, std::error_code& ec) const noexcept {
   if (!ec || ec != TextureFileError::fatal_error && new_error == TextureFileError::fatal_error) {
      ec = new_error;
   }

   if (!ec) {
      return true;
   }

   if (!strict() && new_error != TextureFileError::fatal_error) {
      be_info() << "Error while reading KTX file; continuing"
         & attr(ids::log_attr_category) << new_error.category().name()
         & attr(ids::log_attr_error_code) << new_error.value()
         & attr(ids::log_attr_description) << new_error.message()
         & attr(ids::log_attr_path) << path().string()
         | log();

      return true;
   }

   if (new_error != ec) {
      be_warn() << "Error while reading KTX file: aborting"
         & attr(ids::log_attr_category) << new_error.category().name()
         & attr(ids::log_attr_error_code) << new_error.value()
         & attr(ids::log_attr_description) << new_error.message()
         & attr(ids::log_attr_path) << path().string()
         | log();
   }

   return false;
}

} // be::gfx::tex
