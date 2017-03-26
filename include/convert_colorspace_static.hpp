﻿#pragma once
#ifndef BE_GFX_CONVERT_COLORSPACE_STATIC_HPP_
#define BE_GFX_CONVERT_COLORSPACE_STATIC_HPP_

#include "colorspace.hpp"
#include "image_pixel_norm.hpp"
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <Colorspace Input, Colorspace Output>
ImagePixelNormTransformFunc convert_colorspace_func();

///////////////////////////////////////////////////////////////////////////////
template <Colorspace Input, Colorspace Output>
vec4 convert_colorspace(vec4 pixel_norm);

} // be::gfx

#include "convert_colorspace_static.inl"

#endif
