#pragma once
#ifndef BE_GFX_TEX_DUPLICATE_IMAGE_HPP_
#define BE_GFX_TEX_DUPLICATE_IMAGE_HPP_

#include "image.hpp"
#include "blit_blocks.hpp"

namespace be::gfx::tex {

//////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
Image duplicate_image(const ImageView& source) {
   Image img;
   img.storage = std::make_unique<TextureStorage>(1, 1, 1, source.dim(), source.block_dim(), source.block_span(), source.storage().alignment());
   img.view = tex::ImageView(source.format(), *img.storage, 0, 0, 0);
   assert(source.size() == img.view.size());
   std::memcpy(img.view.data(), source.data(), img.view.size());
   return img;
}

//////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
Image duplicate_image(const ImageView& source, U8 block_span, TextureAlignment alignment) {
   Image img;
   img.storage = std::make_unique<TextureStorage>(1, 1, 1, source.dim(), source.block_dim(), block_span, alignment);
   img.view = tex::ImageView(source.format(), *img.storage, 0, 0, 0);
   assert(source.dim() == img.view.dim());
   blit_blocks(source, img.view);
   return img;
}

} // be::gfx::tex

#endif
