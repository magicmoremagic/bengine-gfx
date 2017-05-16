#pragma once
#ifndef BE_GFX_TEX_READ_HPP_
#define BE_GFX_TEX_READ_HPP_

#include "texture.hpp"
#include "image.hpp"
#include "texture_file_info.hpp"
#include <be/core/buf.hpp>
#include <be/core/filesystem.hpp>

namespace be::gfx::tex {

TextureFileInfo read_info(const Buf<const UC>& buf);
TextureFileInfo read_info(Path path);

Texture read_texture(const Buf<const UC>& buf);
bool read_texture(const Buf<const UC>& buf, TextureView& dest);
Texture read_texture(Path path);
bool read_texture(Path path, TextureView& dest);
Texture read_texture(TextureFileFormat type, const Buf<const UC>& buf);
bool read_texture(TextureFileFormat type, const Buf<const UC>& buf, TextureView& dest);
Texture read_texture(TextureFileFormat type, Path path);
bool read_texture(TextureFileFormat type, Path path, TextureView& dest);

Image read_image(const Buf<const UC>& buf);
bool read_image(const Buf<const UC>& buf, ImageView& dest);
Image read_image(Path path);
bool read_image(Path path, ImageView& dest);
Image read_image(TextureFileFormat type, const Buf<const UC>& buf);
bool read_image(TextureFileFormat type, const Buf<const UC>& buf, ImageView& dest);
Image read_image(TextureFileFormat type, Path path);
bool read_image(TextureFileFormat type, Path path, ImageView& dest);

} // be::gfx::tex

#endif
