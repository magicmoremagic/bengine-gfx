#include "pch.hpp"
#include "tex/png_reader.hpp"
#include "tex/texture_file_error.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_png(const Buf<const UC>& buf) noexcept {
   constexpr UC signature[] = { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n' };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
PngReader::PngReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
void PngReader::reset_impl_() noexcept {
   texture_size_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat PngReader::format_impl_() noexcept {
   return TextureFileFormat::png;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo PngReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::png;
   std::tie(info, texture_size_) = detail::read_stbi_info(buf_, TextureFileFormat::png, be_stbi_png_info_from_memory, ec);
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture PngReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (!ec) {
      tex = detail::read_stbi_texture(buf_, i, texture_size_, be_stbi_load_png_from_memory, ec);
   }
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image PngReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   if (layer != 0 || face != 0 || level != 0) {
      ec = make_error_code(TextureFileError::image_unavailable);
   } else {
      const TextureFileInfo& i = info(ec);
      if (!ec) {
         img = detail::read_stbi_image(buf_, i, texture_size_, be_stbi_load_png_from_memory, ec);
      }
   }
   return img;
}


} // be::gfx::tex
