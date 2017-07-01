#include "pch.hpp"
#include "tex/glraw_reader.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_glraw(const Buf<const UC>& buf) noexcept {
   constexpr UC signature[] = { 0xF5, 0xC6 };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
GlrawReader::GlrawReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log) { }

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat GlrawReader::format_impl_() noexcept {
   return TextureFileFormat::bmp;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo GlrawReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::bmp;
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture GlrawReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image GlrawReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   return img;
}

} // be::gfx::tex
