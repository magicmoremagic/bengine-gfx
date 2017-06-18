#include "pch.hpp"
#include "tex/read_bmp.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/core/byte_order.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_bmp(const Buf<const UC>& buf) {
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
std::pair<TextureFileInfo, TextureFileReadError> read_bmp_info(const Buf<const UC>& buf) {
   if (is_bmp(buf)) {
      return stbi::detail::read_stbi_info(buf, TextureFileFormat::bmp, be_stbi_bmp_info_from_memory);
   } else {
      return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_bmp_texture(const Buf<const UC>& buf) {
   if (is_bmp(buf)) {
      return stbi::detail::read_stbi_texture(buf, be_stbi_load_bmp_from_memory);
   } else {
      return std::make_pair(Texture(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_bmp_image(const Buf<const UC>& buf) {
   if (is_bmp(buf)) {
      return stbi::detail::read_stbi_image(buf, be_stbi_load_bmp_from_memory);
   } else {
      return std::make_pair(Image(), TextureFileReadError::file_corruption);
   }
}

} // be::gfx::tex
