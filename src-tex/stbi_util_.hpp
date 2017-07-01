#pragma once
#ifndef BE_GFX_TEX_STBI_UTIL_HPP_
#define BE_GFX_TEX_STBI_UTIL_HPP_

#include "tex/texture_file_info.hpp"

#include "tex/texture.hpp"
#include "tex/image.hpp"
#include "stbi_.h"
#include <be/core/buf.hpp>

namespace be::gfx::tex::detail {

std::pair<TextureFileInfo, std::size_t> read_stbi_info(const Buf<const UC>& buf, TextureFileFormat format, be_stbi_info_func info_func, std::error_code& ec) noexcept;
Texture read_stbi_texture(const Buf<const UC>& buf, const TextureFileInfo& info, std::size_t texture_size, be_stbi_load_func load_func, std::error_code& ec) noexcept;
Image read_stbi_image(const Buf<const UC>& buf, const TextureFileInfo& info, std::size_t texture_size, be_stbi_load_func load_func, std::error_code& ec) noexcept;

} // be::gfx::tex::detail

#endif
