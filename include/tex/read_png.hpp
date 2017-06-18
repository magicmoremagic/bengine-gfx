#pragma once
#ifndef BE_GFX_TEX_READ_PNG_HPP_
#define BE_GFX_TEX_READ_PNG_HPP_

#include "tex/texture_file_info.hpp"
#include "tex/texture_file_read_error.hpp"
#include "tex/texture.hpp"
#include "tex/image.hpp"
#include <be/core/buf.hpp>

namespace be::gfx::tex {

bool is_png(const Buf<const UC>& buf);
std::pair<TextureFileInfo, TextureFileReadError> read_png_info(const Buf<const UC>& buf);
std::pair<Texture, TextureFileReadError> read_png_texture(const Buf<const UC>& buf);
std::pair<Image, TextureFileReadError> read_png_image(const Buf<const UC>& buf);

} // be::gfx::tex

#endif
