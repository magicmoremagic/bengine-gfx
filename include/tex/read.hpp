#pragma once
#ifndef BE_GFX_TEX_READ_HPP_
#define BE_GFX_TEX_READ_HPP_

#include "texture.hpp"
#include "image.hpp"
#include "texture_file_info.hpp"
#include "texture_file_read_error.hpp"
#include <be/core/buf.hpp>
#include <be/core/filesystem.hpp>
#include <be/util/file_read_error.hpp>

namespace be::gfx::tex {

TextureFileFormat read_format(const Buf<const UC>& buf);

std::pair<TextureFileInfo, TextureFileReadError> read_info(const Buf<const UC>& buf);
std::pair<TextureFileInfo, TextureFileReadError> read_info(Path path);
std::pair<TextureFileInfo, TextureFileReadError> read_info(TextureFileFormat type, const Buf<const UC>& buf);
std::pair<TextureFileInfo, TextureFileReadError> read_info(TextureFileFormat type, Path path);

std::pair<Texture, TextureFileReadError> read_texture(const Buf<const UC>& buf);
std::pair<Texture, TextureFileReadError> read_texture(Path path);
std::pair<Texture, TextureFileReadError> read_texture(TextureFileFormat type, const Buf<const UC>& buf);
std::pair<Texture, TextureFileReadError> read_texture(TextureFileFormat type, Path path);

std::pair<Image, TextureFileReadError> read_image(const Buf<const UC>& buf);
std::pair<Image, TextureFileReadError> read_image(Path path);
std::pair<Image, TextureFileReadError> read_image(TextureFileFormat type, const Buf<const UC>& buf);
std::pair<Image, TextureFileReadError> read_image(TextureFileFormat type, Path path);

} // be::gfx::tex

#endif
