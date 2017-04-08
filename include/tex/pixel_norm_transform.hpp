#pragma once
#ifndef BE_GFX_TEX_PIXEL_NORM_TRANSFORM_HPP_
#define BE_GFX_TEX_PIXEL_NORM_TRANSFORM_HPP_

#include <be/core/glm.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
using PixelNormTransformFunc = vec4(*)(vec4);

} // be::gfx::tex

#endif
