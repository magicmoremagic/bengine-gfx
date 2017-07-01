#include "pch.hpp"
#include "tex/tga_reader.hpp"
#include "tex/texture_file_error.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/core/byte_order.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
// TGA v2 detection is quite reliable, but v1 isn't, so this check should be considered unreliable overall
bool is_tga(const Buf<const UC>& buf) noexcept {
   if (buf.size() >= 44) {
      constexpr UC signature[] = { 'T', 'R', 'U', 'E', 'V', 'I', 'S', 'I', 'O', 'N', '-', 'X', 'F', 'I', 'L', 'E', '.', 0 };
      if (util::file_signature_matches(buf, buf.size() - sizeof(signature), signature)) {
         return true; // TGA v2
      }
   }

   if (buf.size() < 18) {
      return false;
   }

   U8 color_map_type = static_cast<U8>(buf[1]);
   if (color_map_type != 0 && color_map_type != 1) {
      // Technically 128-255 could be used in non-standard TGAs but we'll ignore those since there's no strong file signature.
      return false;
   }

   U8 image_type = static_cast<U8>(buf[2]);
   U8 base_image_type = image_type & 0xF7u; // remove RLE bit
   if (base_image_type != 1 && base_image_type != 2 && base_image_type != 3) {
      // ignore type 0 (no image data)
      return false;
   }

   return (static_cast<U8>(buf[17]) & 0xC0) == 0;
}

///////////////////////////////////////////////////////////////////////////////
TgaReader::TgaReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
void TgaReader::reset_impl_() noexcept {
   texture_size_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat TgaReader::format_impl_() noexcept {
   return TextureFileFormat::tga;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo TgaReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::tga;
   std::tie(info, texture_size_) = detail::read_stbi_info(buf_, TextureFileFormat::tga, be_stbi_tga_info_from_memory, ec);
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture TgaReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (!ec) {
      tex = detail::read_stbi_texture(buf_, i, texture_size_, be_stbi_load_tga_from_memory, ec);
   }
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image TgaReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   if (layer != 0 || face != 0 || level != 0) {
      ec = make_error_code(TextureFileError::image_unavailable);
   } else {
      const TextureFileInfo& i = info(ec);
      if (!ec) {
         img = detail::read_stbi_image(buf_, i, texture_size_, be_stbi_load_tga_from_memory, ec);
      }
   }
   return img;
}

} // be::gfx::tex
