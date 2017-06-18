#include "pch.hpp"
#include "tex/read_pic.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_pic(const Buf<const UC>& buf) {
   constexpr UC signature1[] = { 0x53, 0x80, 0xf6, 0x34 };
   constexpr UC signature2[] = { 'P', 'I', 'C', 'T' };
   return util::file_signature_matches(buf, signature1) &&
      util::file_signature_matches<88>(buf, signature2);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_pic_info(const Buf<const UC>& buf) {
   if (is_pic(buf)) {
      return stbi::detail::read_stbi_info(buf, TextureFileFormat::pic, be_stbi_pic_info_from_memory);
   } else {
      return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_pic_texture(const Buf<const UC>& buf) {
   if (is_pic(buf)) {
      return stbi::detail::read_stbi_texture(buf, be_stbi_load_pic_from_memory);
   } else {
      return std::make_pair(Texture(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_pic_image(const Buf<const UC>& buf) {
   if (is_pic(buf)) {
      return stbi::detail::read_stbi_image(buf, be_stbi_load_pic_from_memory);
   } else {
      return std::make_pair(Image(), TextureFileReadError::file_corruption);
   }
}


} // be::gfx::tex
