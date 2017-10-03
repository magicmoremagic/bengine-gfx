#pragma once
#ifndef BE_GFX_TEX_DUPLICATE_TEXTURE_HPP_
#define BE_GFX_TEX_DUPLICATE_TEXTURE_HPP_

#include "texture.hpp"
#include "blit_blocks.hpp"

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView>
Texture duplicate_texture(const TextureView& source) {
   Texture texture;
   if (source) {
      std::size_t n_layers = source.layers();
      std::size_t n_faces = source.faces();
      std::size_t n_levels = source.levels();

      texture.storage = std::make_unique<TextureStorage>(n_layers, n_faces, n_levels, source.image().dim(), source.block_dim(), source.block_span(), source.storage().alignment());
      texture.view = be::gfx::tex::TextureView(source.format(), source.texture_class(), *texture.storage, 0, n_layers, 0, n_faces, 0, n_levels);

      for (std::size_t layer = 0; layer < n_layers; ++layer) {
         for (std::size_t face = 0; face < n_faces; ++face) {
            for (std::size_t level = 0; level < n_levels; ++level) {
               auto src_view = source.image(layer, face, level);
               auto dest_view = texture.view.image(layer, face, level);
               assert(src_view.size() == dest_view.size());
               std::memcpy(dest_view.data(), src_view.data(), dest_view.size());
            }
         }
      }
   }

   return texture;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView>
Texture duplicate_texture(const TextureView& source, U8 block_span, TextureAlignment alignment) {
   Texture texture;
   if (source) {
      std::size_t n_layers = source.layers();
      std::size_t n_faces = source.faces();
      std::size_t n_levels = source.levels();

      texture.storage = std::make_unique<TextureStorage>(n_layers, n_faces, n_levels, source.image().dim(), source.block_dim(), block_span, alignment);
      texture.view = be::gfx::tex::TextureView(source.format(), source.texture_class(), *texture.storage, 0, n_layers, 0, n_faces, 0, n_levels);

      for (std::size_t layer = 0; layer < n_layers; ++layer) {
         for (std::size_t face = 0; face < n_faces; ++face) {
            for (std::size_t level = 0; level < n_levels; ++level) {
               auto src_view = source.image(layer, face, level);
               auto dest_view = texture.view.image(layer, face, level);
               assert(src_view.dim() == dest_view.dim());
               blit_blocks(src_view, dest_view);
            }
         }
      }
   }

   return texture;
}

} // be::gfx::tex

#endif
