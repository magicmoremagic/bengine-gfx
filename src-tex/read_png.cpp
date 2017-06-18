#include "pch.hpp"
#include "tex/read_png.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_png(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n' };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_png_info(const Buf<const UC>& buf) {
   if (is_png(buf)) {
      return stbi::detail::read_stbi_info(buf, TextureFileFormat::png, be_stbi_png_info_from_memory);
   } else {
      return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_png_texture(const Buf<const UC>& buf) {
   if (is_png(buf)) {
      return stbi::detail::read_stbi_texture(buf, be_stbi_load_png_from_memory);
   } else {
      return std::make_pair(Texture(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_png_image(const Buf<const UC>& buf) {
   if (is_png(buf)) {
      return stbi::detail::read_stbi_image(buf, be_stbi_load_png_from_memory);
   } else {
      return std::make_pair(Image(), TextureFileReadError::file_corruption);
   }
}


} // be::gfx::tex
