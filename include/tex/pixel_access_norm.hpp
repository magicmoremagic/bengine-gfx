#pragma once
#ifndef BE_GFX_TEX_PIXEL_ACCESS_NORM_HPP_
#define BE_GFX_TEX_PIXEL_ACCESS_NORM_HPP_

#include "pixel_access.hpp"
#include <be/core/builtins.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
using GetPixelNormFunc = vec4(*)(const ImageView&, Coord);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
GetPixelNormFunc<Coord, ImageView> get_pixel_norm_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
vec4 get_pixel_norm(const ImageView& image, Coord pixel_coord);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
using PutPixelNormFunc = void(*)(ImageView&, Coord, vec4);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
PutPixelNormFunc<Coord, ImageView> put_pixel_norm_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
void put_pixel_norm(ImageView& image, Coord pixel_coord, vec4 pixel);

} // be::gfx::tex

#include "pixel_access_norm.inl"

#endif
