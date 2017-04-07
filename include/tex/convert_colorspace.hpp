#pragma once
#ifndef BE_GFX_CONVERT_COLORSPACE_HPP_
#define BE_GFX_CONVERT_COLORSPACE_HPP_

#include "colorspace.hpp"
#include "image_pixel_norm.hpp"
#include <glm/vec4.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
ImagePixelNormTransformFunc convert_colorspace_func(Colorspace input, Colorspace output);

///////////////////////////////////////////////////////////////////////////////
vec4 convert_colorspace(vec4 pixel_norm, Colorspace input, Colorspace output);

} // be::gfx

#endif
