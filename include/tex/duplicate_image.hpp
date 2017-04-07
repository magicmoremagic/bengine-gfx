#pragma once
#ifndef BE_GFX_DUPLICATE_IMAGE_HPP_
#define BE_GFX_DUPLICATE_IMAGE_HPP_

#include "image.hpp"

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
Image duplicate_image(const ImageView& source) {
   Image img;
   img.data = std::make_unique<TextureStorage>(1, 1, 1, source.dim(), source.block_dim(), source.block_size(), source.alignment());
   img.view = ImageView(source.format(), *img.data, 0, 0, 0);
   assert(source.size() == img.view.size());
   std::memcpy(img.view.data(), source.data(), img.view.size());
   return img;
}

} // be::gfx

#endif
