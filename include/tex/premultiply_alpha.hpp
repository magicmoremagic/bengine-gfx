#pragma once
#ifndef BE_GFX_TEX_PREMULTIPLY_ALPHA_HPP_
#define BE_GFX_TEX_PREMULTIPLY_ALPHA_HPP_

#include "pixel_norm_transform.hpp"

namespace be::gfx::tex {

vec4 premultiply_alpha(vec4 unpremultiplied);
vec4 unpremultiply_alpha(vec4 premultiplied);

PixelNormTransformFunc convert_premultiplication_func(bool input, bool output);

} // be::gfx::tex

#endif
