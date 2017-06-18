#include "pch.hpp"
#include "tex/read_pnm.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_pnm(const Buf<const UC>& buf) {
   constexpr UC signature1[] = { 'P', '5' };
   constexpr UC signature2[] = { 'P', '6' };
   return util::file_signature_matches(buf, signature1) ||
      util::file_signature_matches(buf, signature2);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_pnm_info(const Buf<const UC>& buf) {
   if (is_pnm(buf)) {
      return stbi::detail::read_stbi_info(buf, TextureFileFormat::pnm, be_stbi_pnm_info_from_memory);
   } else {
      return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_pnm_texture(const Buf<const UC>& buf) {
   if (is_pnm(buf)) {
      return stbi::detail::read_stbi_texture(buf, be_stbi_load_pnm_from_memory);
   } else {
      return std::make_pair(Texture(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_pnm_image(const Buf<const UC>& buf) {
   if (is_pnm(buf)) {
      return stbi::detail::read_stbi_image(buf, be_stbi_load_pnm_from_memory);
   } else {
      return std::make_pair(Image(), TextureFileReadError::file_corruption);
   }
}

} // be::gfx::tex
