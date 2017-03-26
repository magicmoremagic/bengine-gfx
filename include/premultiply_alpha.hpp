#pragma once
#ifndef BE_GFX_PREMULTIPLY_ALPHA_HPP_
#define BE_GFX_PREMULTIPLY_ALPHA_HPP_

#include "image_pixel_norm.hpp"

namespace be::gfx {

vec4 premultiply_alpha(vec4 unpremultiplied);
vec4 unpremultiply_alpha(vec4 premultiplied);

ImagePixelNormTransformFunc convert_premultiplication_func(bool input, bool output);

} // be::gfx

#endif
