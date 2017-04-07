#pragma once
#ifndef BE_GFX_IMAGE_HPP_
#define BE_GFX_IMAGE_HPP_

#include "texture_storage.hpp"
#include "image_view.hpp"

namespace be::gfx {

struct Image final {
   std::unique_ptr<TextureStorage> data;
   ImageView view;
};

} // be::gfx

#endif
