#include "pch.hpp"
#include "tex/bmp_reader.hpp"
#include "tex/texture_file_error.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/core/byte_order.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_bmp(const Buf<const UC>& buf) noexcept {
   if (buf.size() < 26) {
      return false;
   }

   constexpr UC signature[] = { 'B', 'M' };
   if (!util::file_signature_matches(buf, signature)) {
      return false;
   }

   U32 header_size;
   memcpy(&header_size, buf.get() + 0xE, sizeof(header_size));
   bo::static_to_host<bo::Little::value>(header_size);

   return header_size == 12 || header_size == 40 || header_size == 56 || header_size == 108 || header_size == 124;
}

///////////////////////////////////////////////////////////////////////////////
BmpReader::BmpReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
void BmpReader::reset_impl_() noexcept {
   texture_size_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat BmpReader::format_impl_() noexcept {
   return TextureFileFormat::bmp;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo BmpReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::bmp;
   std::tie(info, texture_size_) = detail::read_stbi_info(buf_, TextureFileFormat::bmp, be_stbi_bmp_info_from_memory, ec);
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture BmpReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (!ec) {
      tex = detail::read_stbi_texture(buf_, i, texture_size_, be_stbi_load_bmp_from_memory, ec);
   }
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image BmpReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   if (layer != 0 || face != 0 || level != 0) {
      ec = make_error_code(TextureFileError::image_unavailable);
   } else {
      const TextureFileInfo& i = info(ec);
      if (!ec) {
         img = detail::read_stbi_image(buf_, i, texture_size_, be_stbi_load_bmp_from_memory, ec);
      }
   }
   return img;
}

} // be::gfx::tex
