#include "pch.hpp"
#include "tex/jpeg_reader.hpp"
#include "tex/texture_file_error.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_jpeg(const Buf<const UC>& buf) noexcept {
   constexpr UC signature[] = { 0xFF, 0xD8, 0xFF };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
JpegReader::JpegReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
void JpegReader::reset_impl_() noexcept {
   texture_size_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat JpegReader::format_impl_() noexcept {
   return TextureFileFormat::jpeg;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo JpegReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::jpeg;
   std::tie(info, texture_size_) = detail::read_stbi_info(buf_, TextureFileFormat::jpeg, be_stbi_jpeg_info_from_memory, ec);
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture JpegReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (!ec) {
      tex = detail::read_stbi_texture(buf_, i, texture_size_, be_stbi_load_jpeg_from_memory, ec);
   }
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image JpegReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   if (layer != 0 || face != 0 || level != 0) {
      ec = make_error_code(TextureFileError::image_unavailable);
   } else {
      const TextureFileInfo& i = info(ec);
      if (!ec) {
         img = detail::read_stbi_image(buf_, i, texture_size_, be_stbi_load_jpeg_from_memory, ec);
      }
   }
   return img;
}

} // be::gfx::tex
