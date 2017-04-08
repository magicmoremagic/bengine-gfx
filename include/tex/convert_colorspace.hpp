#pragma once
#ifndef BE_GFX_TEX_CONVERT_COLORSPACE_HPP_
#define BE_GFX_TEX_CONVERT_COLORSPACE_HPP_

#include "colorspace.hpp"
#include "pixel_norm_transform.hpp"
#include <glm/vec4.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
PixelNormTransformFunc convert_colorspace_func(Colorspace input, Colorspace output);

///////////////////////////////////////////////////////////////////////////////
vec4 convert_colorspace(vec4 pixel_norm, Colorspace input, Colorspace output);

} // be::gfx::tex

#endif
