#pragma once
#ifndef BE_GFX_TEX_MIPMAPPING_HPP_
#define BE_GFX_TEX_MIPMAPPING_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/common.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename C>
C mipmap_dim(C base_dim, U8 level) {
   return glm::max(C(static_cast<C::value_type>(1)), base_dim >> static_cast<C::value_type>(level));
}

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(std::size_t dim);
U8 mipmap_levels(ivec1 dim);
U8 mipmap_levels(ivec2 dim);
U8 mipmap_levels(ivec3 dim);
U8 mipmap_levels(uvec1 dim);
U8 mipmap_levels(uvec2 dim);
U8 mipmap_levels(uvec3 dim);

} // be::gfx::tex

#endif
