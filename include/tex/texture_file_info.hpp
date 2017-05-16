#pragma once
#ifndef BE_GFX_TEX_TEXTURE_FILE_INFO_HPP_
#define BE_GFX_TEX_TEXTURE_FILE_INFO_HPP_

#include "texture_storage.hpp"
#include "texture_class.hpp"
#include "texture_file_format.hpp"

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
struct TextureFileInfo {
   TextureFileFormat file_format;
   ImageFormat format;
   TextureClass tex_class;
   ivec3 dim;
   ImageFormat::block_dim_type block_dim;
   ImageFormat::block_size_type block_size;
   TextureStorage::layer_index_type layers;
   TextureStorage::face_index_type faces;
   TextureStorage::level_index_type levels;
   TextureStorage::layer_index_type base_layer;
   TextureStorage::face_index_type base_face;
   TextureStorage::level_index_type base_level;
};

} // be::gfx::tex

#endif
