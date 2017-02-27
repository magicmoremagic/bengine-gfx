#pragma once
#ifndef BE_GFX_IMAGE_HPP_
#define BE_GFX_IMAGE_HPP_

#include "texture_storage.hpp"
#include "image_view.hpp"

namespace be::gfx {

struct Image final {
   TextureStorage data;
   ImageView view;
};

} // be::gfx

#endif
