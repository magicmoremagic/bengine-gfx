#pragma once
#ifndef BE_GFX_TEX_PIXEL_ACCESS_HPP_
#define BE_GFX_TEX_PIXEL_ACCESS_HPP_

#include "block_packing.hpp"
#include "image_format.hpp"
#include "block_access.hpp"
#include "dimension_tag.hpp"
#include <be/core/glm_helpers.hpp>
#include <cassert>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
using PixelOffsetFunc = std::size_t(*)(const ImageView&, Coord);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
PixelOffsetFunc<Coord, ImageView> pixel_offset_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
std::size_t pixel_offset(const ImageView& image, Coord pixel_coord);

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
using GetPixelFunc = T(*)(const ImageView&, Coord);

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
GetPixelFunc<T, Coord, ImageView> get_pixel_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
T get_pixel(const ImageView& image, Coord pixel_coord);

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
using PutPixelFunc = void(*)(ImageView&, Coord, T);

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
PutPixelFunc<T, Coord, ImageView> put_pixel_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
void put_pixel(ImageView& image, Coord pixel_coord, T pixel);

} // be::gfx::tex

#include "pixel_access.inl"

#endif
