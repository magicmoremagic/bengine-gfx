#include "pch.hpp"
#include "tex/read_glraw.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_glraw(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 0xF5, 0xC6 };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_glraw_info(const Buf<const UC>& buf) {
   return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_glraw_texture(const Buf<const UC>& buf) {
   return std::make_pair(Texture(), TextureFileReadError::file_corruption);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_glraw_image(const Buf<const UC>& buf) {
   return std::make_pair(Image(), TextureFileReadError::file_corruption);
}

} // be::gfx::tex
