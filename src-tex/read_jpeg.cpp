#include "pch.hpp"
#include "tex/read_jpeg.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_jpeg(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 0xFF, 0xD8, 0xFF };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_jpeg_info(const Buf<const UC>& buf) {
   if (is_jpeg(buf)) {
      return stbi::detail::read_stbi_info(buf, TextureFileFormat::jpeg, be_stbi_jpeg_info_from_memory);
   } else {
      return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_jpeg_texture(const Buf<const UC>& buf) {
   if (is_jpeg(buf)) {
      return stbi::detail::read_stbi_texture(buf, be_stbi_load_jpeg_from_memory);
   } else {
      return std::make_pair(Texture(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_jpeg_image(const Buf<const UC>& buf) {
   if (is_jpeg(buf)) {
      return stbi::detail::read_stbi_image(buf, be_stbi_load_jpeg_from_memory);
   } else {
      return std::make_pair(Image(), TextureFileReadError::file_corruption);
   }
}


} // be::gfx::tex
