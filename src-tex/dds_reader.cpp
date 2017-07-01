#include "pch.hpp"
#include "tex/dds_reader.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_dds(const Buf<const UC>& buf) noexcept {
   constexpr UC signature[] = { 'D', 'D', 'S', ' ' };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
DdsReader::DdsReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log) { }

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat DdsReader::format_impl_() noexcept {
   return TextureFileFormat::bmp;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo DdsReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::bmp;
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture DdsReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image DdsReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   return img;
}

} // be::gfx::tex
