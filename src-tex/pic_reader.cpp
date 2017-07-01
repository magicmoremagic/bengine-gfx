#include "pch.hpp"
#include "tex/pic_reader.hpp"
#include "tex/texture_file_error.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_pic(const Buf<const UC>& buf) noexcept {
   constexpr UC signature1[] = { 0x53, 0x80, 0xf6, 0x34 };
   constexpr UC signature2[] = { 'P', 'I', 'C', 'T' };
   return util::file_signature_matches(buf, signature1) &&
      util::file_signature_matches<88>(buf, signature2);
}

///////////////////////////////////////////////////////////////////////////////
PicReader::PicReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
void PicReader::reset_impl_() noexcept {
   texture_size_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat PicReader::format_impl_() noexcept {
   return TextureFileFormat::pic;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo PicReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::pic;
   std::tie(info, texture_size_) = detail::read_stbi_info(buf_, TextureFileFormat::pic, be_stbi_pic_info_from_memory, ec);
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture PicReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (!ec) {
      tex = detail::read_stbi_texture(buf_, i, texture_size_, be_stbi_load_pic_from_memory, ec);
   }
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image PicReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   if (layer != 0 || face != 0 || level != 0) {
      ec = make_error_code(TextureFileError::image_unavailable);
   } else {
      const TextureFileInfo& i = info(ec);
      if (!ec) {
         img = detail::read_stbi_image(buf_, i, texture_size_, be_stbi_load_pic_from_memory, ec);
      }
   }
   return img;
}


} // be::gfx::tex
