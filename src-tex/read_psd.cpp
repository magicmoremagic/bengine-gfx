#include "pch.hpp"
#include "tex/read_psd.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_psd(const Buf<const UC>& buf) {
   constexpr UC signature[] = { '8', 'B', 'P', 'S' };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_psd_info(const Buf<const UC>& buf) {
   if (is_psd(buf)) {
      return stbi::detail::read_stbi_info(buf, TextureFileFormat::psd, be_stbi_psd_info_from_memory);
   } else {
      return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_psd_texture(const Buf<const UC>& buf) {
   if (is_psd(buf)) {
      return stbi::detail::read_stbi_texture(buf, be_stbi_load_psd_from_memory);
   } else {
      return std::make_pair(Texture(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_psd_image(const Buf<const UC>& buf) {
   if (is_psd(buf)) {
      return stbi::detail::read_stbi_image(buf, be_stbi_load_psd_from_memory);
   } else {
      return std::make_pair(Image(), TextureFileReadError::file_corruption);
   }
}


} // be::gfx::tex
