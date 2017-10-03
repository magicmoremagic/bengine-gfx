#include "pch.hpp"
#include "ktx_header_.hpp"
#include "tex/ktx_writer.hpp"
#include "tex/texture.hpp"
#include "tex/duplicate_texture.hpp"
#include "tex/byte_order.hpp"
#include "tex/texture_file_error.hpp"
#include "tex/image_format_gl.hpp"
#include <be/util/put_file_contents.hpp>
#include <be/util/zlib.hpp>
#include <be/core/exceptions.hpp>

namespace be::gfx::tex {

//////////////////////////////////////////////////////////////////////////////
KtxWriter::KtxWriter(Log& log)
   : log_(log),
     endianness_(bo::Host::value) { }

//////////////////////////////////////////////////////////////////////////////
void KtxWriter::reset() {
   tex_ = ConstTextureView();
   endianness_ = bo::Host::value;
   metadata_entries_.clear();
}

//////////////////////////////////////////////////////////////////////////////
void KtxWriter::texture(const ConstTextureView& view) noexcept {
   tex_ = view;
}

//////////////////////////////////////////////////////////////////////////////
void KtxWriter::image(const ConstImageView& view) noexcept {
   TextureClass tc;
   if (view.dim().z == 1) {
      if (view.dim().y == 1) {
         tc = TextureClass::lineal;
      } else {
         tc = TextureClass::planar;
      }
   } else {
      tc = TextureClass::volumetric;
   }

   tex_ = ConstTextureView(view.format(), tc, view.storage(), view.layer(), 1, view.face(), 1, view.level(), 1);
}

//////////////////////////////////////////////////////////////////////////////
void KtxWriter::endianness(ByteOrderType endianness) noexcept {
   endianness_ = endianness;
}

//////////////////////////////////////////////////////////////////////////////
void KtxWriter::metadata(SV key, SV value) {
   assert(key.find('\0') == SV::npos); // otherwise part of the key will be prepended to the value when read
   metadata_entries_.push_back(std::make_pair(key, value));
}

//////////////////////////////////////////////////////////////////////////////
Buf<UC> KtxWriter::write() {
   Buf<UC> result;
   std::error_code ec;
   result = write(ec);
   if (ec) {
      throw RecoverableError(ec);
   }
   return result;
}

//////////////////////////////////////////////////////////////////////////////
Buf<UC> KtxWriter::write(std::error_code& ec) noexcept {
   using namespace gl;
   using err = TextureFileError;
   using sig = detail::KtxSignature;

   Buf<UC> result;

   if (!tex_) {
      ec = make_error_code(err::image_unavailable);
      return result;
   }

   if (endianness_ != bo::Big::value && endianness_ != bo::Little::value) {
      ec = make_error_code(err::unsupported);
      return result;
   }

   std::error_code ec2;
   ImageFormatGl gl_fmt = to_gl_format(tex_.format(), ec2);
   if (ec2) {
      ec = ec2;
      return result;
   }

   constexpr GLenum std_swizzle[4] = {
      GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA
   };
   for (glm::length_t c = 0; c < 4; ++c) {
      auto s = gl_fmt.swizzle[c];
      if (s == std_swizzle[c]) {
         continue;
      }
      if (c >= tex_.format().components()) {
         if (c == 3) {
            if (s == GL_ONE) {
               continue;
            }
         } else if (s == GL_ZERO) {
            continue;
         }
      }
      ec = make_error_code(err::unsupported);
      // This is a soft error; we can still generate a valid KTX file, it just might not map color channels correctly
      // so no return here.
   }

   detail::KtxHeader header;
   static_assert(sizeof(header.signature) == sizeof(detail::KtxSignature::full));
   std::memcpy(header.signature, detail::KtxSignature::full, sizeof(header.signature));

   header.endianness = 0x04030201;
   header.gl_type = gl_fmt.data_type;
   header.gl_type_size = block_word_size(tex_.format().packing());
   header.gl_format = gl_fmt.data_format;
   header.gl_internal_format = gl_fmt.internal_format;
   header.gl_base_internal_format = gl_fmt.base_internal_format;

   header.pixel_width = tex_.dim(0).x;
   header.pixel_height = tex_.dim(0).y;
   header.pixel_depth = tex_.dim(0).z;

   auto dimensionality = tex::dimensionality(tex_.texture_class());
   if (dimensionality < 3) {
      header.pixel_depth = 0;
      if (dimensionality < 2) {
         header.pixel_height = 0;
      }
   }

   if (!is_array(tex_.texture_class())) {
      header.number_of_array_elements = 0;
   } else {
      header.number_of_array_elements = tex_.layers();
   }

   header.number_of_faces = tex_.faces();
   header.number_of_mipmap_levels = tex_.levels();

   header.bytes_of_key_value_data = 0;
   for (const auto& p : metadata_entries_) {
      U32 raw_size = U32(sizeof(U32) + p.first.size() + 1 + p.second.size());
      U32 padded_size = aligned_size<sizeof(U32)>(raw_size);
      header.bytes_of_key_value_data += padded_size;
   }

   ConstTextureView t;
   Texture tmp_tex;
   if (tex_.format().block_size() != tex_.block_span() ||
       tex_.storage().alignment().line() != 4 ||
       tex_.storage().alignment().plane() != 4) {
      try {
         tmp_tex = duplicate_texture(tex_, tex_.format().block_size(), TextureAlignment(2));
      } catch (const std::bad_alloc&) {
         ec = std::make_error_code(std::errc::not_enough_memory);
         return result;
      }
      t = tmp_tex.view;
      if (endianness_ != bo::Host::value) {
         reverse_endianness(*tmp_tex.storage, t.format().packing());
      }
   } else if (endianness_ != bo::Host::value) {
      try {
         tmp_tex = duplicate_texture(tex_);
      } catch (const std::bad_alloc&) {
         ec = std::make_error_code(std::errc::not_enough_memory);
         return result;
      }
      t = tmp_tex.view;
      reverse_endianness(*tmp_tex.storage, t.format().packing());
   } else {
      t = tex_;
   }

   ec2 = std::error_code();
   std::size_t payload_size = calculate_required_texture_storage(t.layers(), t.faces(), t.levels(), t.dim(0), t.block_dim(), t.block_span(), ec2, TextureAlignment(2));
   payload_size = aligned_size<sizeof(U32)>(payload_size + sizeof(U32) * t.levels());
   if (ec2) {
      ec = ec2;
      return result;
   }

   U32 metadata_size = header.bytes_of_key_value_data; // we know this is aligned to U32 already
   const std::size_t buffer_size = sizeof(header) + metadata_size + payload_size;
   try {
      result = make_buf<UC>(buffer_size);
   } catch (const std::bad_alloc&) {
      ec = std::make_error_code(std::errc::not_enough_memory);
      return result;
   }

   if (endianness_ == ByteOrderType::big_endian) {
      bo::static_to_big<>(header);
   } else {
      bo::static_to_little<>(header);
   }
   std::memcpy(result.get(), &header, sizeof(header));

   std::size_t offset = sizeof(header);
   for (const auto& p : metadata_entries_) {
      std::size_t o = offset;
      U32 raw_size = U32(p.first.size() + 1 + p.second.size());
      U32 endian_size;
      if (endianness_ == ByteOrderType::big_endian) {
         endian_size = bo::to_big<>(raw_size);
      } else {
         endian_size = bo::to_little<>(raw_size);
      }
      std::memcpy(result.get() + o, &endian_size, sizeof(U32));
      o += sizeof(U32);
      std::memcpy(result.get() + o, p.first.data(), p.first.size());
      o += p.first.size();
      result[o] = '\0';
      ++o;
      std::memcpy(result.get() + o, p.second.data(), p.second.size());
      o += p.second.size();

      std::size_t padded_size = sizeof(U32) + aligned_size<sizeof(U32)>(raw_size);
      offset += padded_size;

      while (o < offset) {
         result[o] = '\0';
         ++o;
      }
   }

   offset = sizeof(header) + metadata_size;
   for (auto level = 0; level < t.levels(); ++level) {
      U32 level_size = 0;
      std::size_t level_size_offset = offset;
      offset += sizeof(U32);
      
      for (auto layer = 0; layer < t.layers(); ++layer) {
         for (auto face = 0; face < t.faces(); ++face) {
            auto v = t.image(layer, face, level);

            std::memcpy(result.get() + offset, v.data(), v.size());
            offset += v.size();
            level_size += (U32)v.size();
         }
      }

      if (t.layers() == 1 && t.faces() == 6) {
         // weird edge case in KTX spec for non-array cubemaps
         level_size = (U32)t.image(0, 0, level).size();
      }

      if (endianness_ == ByteOrderType::big_endian) {
         bo::static_to_big<>(level_size);
      } else {
         bo::static_to_little<>(level_size);
      }

      std::memcpy(result.get() + level_size_offset, &level_size, sizeof(U32));
   }

   return result;
}

//////////////////////////////////////////////////////////////////////////////
void KtxWriter::write(const Path& path) {
   util::put_file_contents(path, write());
}

//////////////////////////////////////////////////////////////////////////////
void KtxWriter::write(const Path& path, std::error_code& ec) noexcept {
   Buf<UC> data = write(ec);
   if (data) {
      util::put_file_contents(path, std::move(data), ec);
   }
}

} // be::gfx::tex
