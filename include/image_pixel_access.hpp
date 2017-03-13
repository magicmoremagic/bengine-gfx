#pragma once
#ifndef BE_GFX_IMAGE_PIXEL_ACCESS_HPP_
#define BE_GFX_IMAGE_PIXEL_ACCESS_HPP_

#include "image_block_packing.hpp"
#include "image_format.hpp"
#include <be/core/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cassert>

namespace be::gfx {

template <typename T, typename ImageView>
using GetImagePixelLinealFunc = T(*)(const ImageView&, I32);
template <typename T, typename ImageView>
GetImagePixelLinealFunc<T, ImageView> get_pixel_lineal_func(const ImageView& image);

template <typename T, typename ImageView>
using GetImagePixelPlanarFunc = T(*)(const ImageView&, ivec2);
template <typename T, typename ImageView>
GetImagePixelPlanarFunc<T, ImageView> get_pixel_planar_func(const ImageView& image);

template <typename T, typename ImageView>
using GetImagePixelVolumetricFunc = T(*)(const ImageView&, ivec3);
template <typename T, typename ImageView>
GetImagePixelVolumetricFunc<T, ImageView> get_pixel_volumetric_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename ImageView>
using PutImagePixelLinealFunc = void(*)(ImageView&, I32, T);
template <typename T, typename ImageView>
PutImagePixelLinealFunc<T, ImageView> put_pixel_lineal_func(const ImageView& image);

template <typename T, typename ImageView>
using PutImagePixelPlanarFunc = void(*)(ImageView&, ivec2, T);
template <typename T, typename ImageView>
PutImagePixelPlanarFunc<T, ImageView> put_pixel_planar_func(const ImageView& image);

template <typename T, typename ImageView>
using PutImagePixelVolumetricFunc = void(*)(ImageView&, ivec3, T);
template <typename T, typename ImageView>
PutImagePixelVolumetricFunc<T, ImageView> put_pixel_volumetric_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, I32 pixel_coord);

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, ivec2 pixel_coord);

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, ivec3 pixel_coord);

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename ImageView>
void put_pixel(ImageView& image, I32 pixel_coord, T pixel);

template <typename T, typename ImageView>
void put_pixel(ImageView& image, ivec2 pixel_coord, T pixel);

template <typename T, typename ImageView>
void put_pixel(ImageView& image, ivec3 pixel_coord, T pixel);

} // be::gfx

#include "image_pixel_access.inl"

#endif
