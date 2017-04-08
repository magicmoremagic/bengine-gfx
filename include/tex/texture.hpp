#pragma once
#ifndef BE_GFX_TEX_TEXTURE_HPP_
#define BE_GFX_TEX_TEXTURE_HPP_

#include "texture_storage.hpp"
#include "texture_view.hpp"

namespace be::gfx::tex {

struct Texture final {
   std::unique_ptr<TextureStorage> data;
   TextureView view;
};

} // be::gfx::tex

#endif
