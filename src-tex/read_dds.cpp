#include "pch.hpp"
#include "tex/read_dds.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_dds(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 'D', 'D', 'S', ' ' };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_dds_info(const Buf<const UC>& buf) {
   return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_dds_texture(const Buf<const UC>& buf) {
   return std::make_pair(Texture(), TextureFileReadError::file_corruption);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_dds_image(const Buf<const UC>& buf) {
   return std::make_pair(Image(), TextureFileReadError::file_corruption);
}

} // be::gfx::tex
