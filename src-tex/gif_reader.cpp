#include "pch.hpp"
#include "tex/gif_reader.hpp"
#include "tex/texture_file_error.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_gif(const Buf<const UC>& buf) noexcept {
   constexpr UC signature1[] = { 'G', 'I', 'F', '8', '9', 'a' };
   constexpr UC signature2[] = { 'G', 'I', 'F', '8', '7', 'a' };
   return util::file_signature_matches(buf, signature1) ||
      util::file_signature_matches(buf, signature2);
}

///////////////////////////////////////////////////////////////////////////////
GifReader::GifReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
void GifReader::reset_impl_() noexcept {
   texture_size_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat GifReader::format_impl_() noexcept {
   return TextureFileFormat::gif;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo GifReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::gif;
   std::tie(info, texture_size_) = detail::read_stbi_info(buf_, TextureFileFormat::gif, be_stbi_gif_info_from_memory, ec);
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture GifReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (!ec) {
      tex = detail::read_stbi_texture(buf_, i, texture_size_, be_stbi_load_gif_from_memory, ec);
   }
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image GifReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   if (layer != 0 || face != 0 || level != 0) {
      ec = make_error_code(TextureFileError::image_unavailable);
   } else {
      const TextureFileInfo& i = info(ec);
      if (!ec) {
         img = detail::read_stbi_image(buf_, i, texture_size_, be_stbi_load_gif_from_memory, ec);
      }
   }
   return img;
}


} // be::gfx::tex
