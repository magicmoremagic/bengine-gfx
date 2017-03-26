#pragma once
#ifndef BE_GFX_IMAGE_PIXEL_NORM_HPP_
#define BE_GFX_IMAGE_PIXEL_NORM_HPP_

#include <be/core/glm.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
using ImagePixelNormTransformFunc = vec4(*)(vec4);

} // be::gfx

#endif
