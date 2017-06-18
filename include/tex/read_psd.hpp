#pragma once
#ifndef BE_GFX_TEX_READ_PSD_HPP_
#define BE_GFX_TEX_READ_PSD_HPP_

#include "tex/texture_file_info.hpp"
#include "tex/texture_file_read_error.hpp"
#include "tex/texture.hpp"
#include "tex/image.hpp"
#include <be/core/buf.hpp>

namespace be::gfx::tex {

bool is_psd(const Buf<const UC>& buf);
std::pair<TextureFileInfo, TextureFileReadError> read_psd_info(const Buf<const UC>& buf);
std::pair<Texture, TextureFileReadError> read_psd_texture(const Buf<const UC>& buf);
std::pair<Image, TextureFileReadError> read_psd_image(const Buf<const UC>& buf);

} // be::gfx::tex

#endif
