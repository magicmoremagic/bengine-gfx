#include "pch.hpp"
#include "tex/read_hdr.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_hdr(const Buf<const UC>& buf) {
   constexpr UC signature1[] = { '#', '?', 'R', 'A', 'D', 'I', 'A', 'N', 'C', 'E', '\n' };
   constexpr UC signature2[] = { '#', '?', 'R', 'G', 'B', 'E', '\n' };
   return util::file_signature_matches(buf, signature1) ||
      util::file_signature_matches(buf, signature2);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_hdr_info(const Buf<const UC>& buf) {
   if (is_hdr(buf)) {
      return stbi::detail::read_stbi_info(buf, TextureFileFormat::hdr, be_stbi_hdr_info_from_memory);
   } else {
      return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_hdr_texture(const Buf<const UC>& buf) {
   if (is_hdr(buf)) {
      return stbi::detail::read_stbi_texture(buf, be_stbi_load_hdr_from_memory);
   } else {
      return std::make_pair(Texture(), TextureFileReadError::file_corruption);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_hdr_image(const Buf<const UC>& buf) {
   if (is_hdr(buf)) {
      return stbi::detail::read_stbi_image(buf, be_stbi_load_hdr_from_memory);
   } else {
      return std::make_pair(Image(), TextureFileReadError::file_corruption);
   }
}


} // be::gfx::tex
