#pragma once
#ifndef BE_GFX_TEX_STBI_UTIL_HPP_
#define BE_GFX_TEX_STBI_UTIL_HPP_

#include "tex/texture_file_info.hpp"
#include "tex/texture_file_read_error.hpp"
#include "tex/texture.hpp"
#include "tex/image.hpp"
#include "stbi_.h"
#include <be/core/buf.hpp>

namespace be::gfx::tex::stbi::detail {

std::pair<TextureFileInfo, TextureFileReadError> read_stbi_info(const Buf<const UC>& buf, TextureFileFormat format, be_stbi_info_func info_func);
std::pair<Texture, TextureFileReadError> read_stbi_texture(const Buf<const UC>& buf, be_stbi_load_func load_func);
std::pair<Image, TextureFileReadError> read_stbi_image(const Buf<const UC>& buf, be_stbi_load_func load_func);

} // be::gfx::tex::detail

#endif
