#pragma once
#ifndef BE_GFX_TEX_DUPLICATE_TEXTURE_HPP_
#define BE_GFX_TEX_DUPLICATE_TEXTURE_HPP_

#include "texture.hpp"

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView>
Texture duplicate_texture(const TextureView& source) {
   Texture texture;

   std::size_t n_layers = source.layers();
   std::size_t n_faces = source.faces();
   std::size_t n_levels = source.levels();

   texture.data = std::make_unique<TextureStorage>(n_layers, n_faces, n_levels, source.image().dim(), source.block_dim(), source.block_size(), source.alignment());
   texture.view = TextureView(source.format(), source.texture_class(), *texture.data, 0, n_layers, 0, n_faces, 0, n_levels);

   for (std::size_t layer = 0; layer < n_layers) {
      for (std::size_t face = 0; face < n_faces) {
         for (std::size_t level = 0; level < n_levels) {
            auto src_view = source.image(layer, face, level);
            auto dest_view = texture.view.image(layer, face, level);
            assert(src_view.size() == dest_view.size());
            std::memcpy(dest_view.data(), src_view.data(), dest_view.size());
         }
      }
   }

   return texture;
}

} // be::gfx::tex

#endif
