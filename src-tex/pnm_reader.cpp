#include "pch.hpp"
#include "tex/pnm_reader.hpp"
#include "tex/texture_file_error.hpp"
#include "stbi_util_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_pnm(const Buf<const UC>& buf) noexcept {
   constexpr UC signature1[] = { 'P', '5' };
   constexpr UC signature2[] = { 'P', '6' };
   return util::file_signature_matches(buf, signature1) ||
      util::file_signature_matches(buf, signature2);
}

///////////////////////////////////////////////////////////////////////////////
PnmReader::PnmReader(bool strict, Log& log)
   : detail::DefaultTextureReader(strict, log),
     texture_size_(0) { }

///////////////////////////////////////////////////////////////////////////////
void PnmReader::reset_impl_() noexcept {
   texture_size_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat PnmReader::format_impl_() noexcept {
   return TextureFileFormat::pnm;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo PnmReader::info_impl_(std::error_code& ec) noexcept {
   TextureFileInfo info;
   info.file_format = TextureFileFormat::pnm;
   std::tie(info, texture_size_) = detail::read_stbi_info(buf_, TextureFileFormat::pnm, be_stbi_pnm_info_from_memory, ec);
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture PnmReader::texture_(std::error_code& ec) noexcept {
   Texture tex;
   const TextureFileInfo& i = info(ec);
   if (!ec) {
      tex = detail::read_stbi_texture(buf_, i, texture_size_, be_stbi_load_pnm_from_memory, ec);
   }
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image PnmReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   Image img;
   if (layer != 0 || face != 0 || level != 0) {
      ec = make_error_code(TextureFileError::image_unavailable);
   } else {
      const TextureFileInfo& i = info(ec);
      if (!ec) {
         img = detail::read_stbi_image(buf_, i, texture_size_, be_stbi_load_pnm_from_memory, ec);
      }
   }
   return img;
}

} // be::gfx::tex
