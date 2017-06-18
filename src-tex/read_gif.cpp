#include "pch.hpp"
#include "tex/read_gif.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_gif(const Buf<const UC>& buf) {
   constexpr UC signature1[] = { 'G', 'I', 'F', '8', '9', 'a' };
   constexpr UC signature2[] = { 'G', 'I', 'F', '8', '7', 'a' };
   return util::file_signature_matches(buf, signature1) ||
      util::file_signature_matches(buf, signature2);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_gif_info(const Buf<const UC>& buf) {
   if (is_gif(buf)) {
      return stbi::detail::read_stbi_info(buf, TextureFileFormat::gif, be_stbi_gif_info_from_memory);
   } else {
      return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_gif_texture(const Buf<const UC>& buf) {
   if (is_gif(buf)) {
      return stbi::detail::read_stbi_texture(buf, be_stbi_load_gif_from_memory);
   } else {
      return std::make_pair(Texture(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_gif_image(const Buf<const UC>& buf) {
   if (is_gif(buf)) {
      return stbi::detail::read_stbi_image(buf, be_stbi_load_gif_from_memory);
   } else {
      return std::make_pair(Image(), TextureFileReadError::file_corruption);
   }
}


} // be::gfx::tex
