#pragma once
#ifndef BE_GFX_MIPMAPPING_HPP_
#define BE_GFX_MIPMAPPING_HPP_

#include <be/core/glm.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(std::size_t dim);
U8 mipmap_levels(ivec1 dim);
U8 mipmap_levels(ivec2 dim);
U8 mipmap_levels(ivec3 dim);
U8 mipmap_levels(uvec1 dim);
U8 mipmap_levels(uvec2 dim);
U8 mipmap_levels(uvec3 dim);

} // be::gfx

#endif
