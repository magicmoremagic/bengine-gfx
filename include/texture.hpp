#pragma once
#ifndef BE_GFX_TEXTURE_HPP_
#define BE_GFX_TEXTURE_HPP_

#include "texture_storage.hpp"
#include "texture_view.hpp"

namespace be::gfx {

struct Texture final {
   TextureStorage data;
   TextureView view;
};

} // be::gfx

#endif
