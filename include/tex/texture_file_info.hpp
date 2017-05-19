#pragma once
#ifndef BE_GFX_TEX_TEXTURE_FILE_INFO_HPP_
#define BE_GFX_TEX_TEXTURE_FILE_INFO_HPP_

#include "texture_storage.hpp"
#include "texture_class.hpp"
#include "texture_file_format.hpp"

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
struct TextureFileInfo {
   TextureFileFormat file_format = TextureFileFormat::unknown;
   ImageFormat format;
   TextureClass tex_class = TextureClass::planar;
   ivec3 dim;
   ImageFormat::block_dim_type block_dim;
   ImageFormat::block_size_type block_size = 0;
   TextureStorage::layer_index_type layers = 0;
   TextureStorage::face_index_type faces = 0;
   TextureStorage::level_index_type levels = 0;
};

} // be::gfx::tex

#endif
