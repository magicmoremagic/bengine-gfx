#pragma once
#ifndef BE_GFX_IMAGE_PIXEL_ACCESS_NORM_HPP_
#define BE_GFX_IMAGE_PIXEL_ACCESS_NORM_HPP_

#include "image_pixel_access.hpp"
#include <be/core/builtins.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace be::gfx {

template <typename ImageView>
using GetImagePixelNormLinealFunc = vec4(*)(const ImageView&, I32);
template <typename ImageView>
GetImagePixelNormLinealFunc<ImageView> get_pixel_norm_lineal_func(const ImageView& image);

template <typename ImageView>
using GetImagePixelNormPlanarFunc = vec4(*)(const ImageView&, ivec2);
template <typename ImageView>
GetImagePixelNormPlanarFunc<ImageView> get_pixel_norm_planar_func(const ImageView& image);

template <typename ImageView>
using GetImagePixelNormVolumetricFunc = vec4(*)(const ImageView&, ivec3);
template <typename ImageView>
GetImagePixelNormVolumetricFunc<ImageView> get_pixel_norm_volumetric_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////

template <typename ImageView>
using PutImagePixelNormLinealFunc = void(*)(ImageView&, I32, vec4);
template <typename ImageView>
PutImagePixelNormLinealFunc<ImageView> put_pixel_norm_lineal_func(const ImageView& image);

template <typename ImageView>
using PutImagePixelNormPlanarFunc = void(*)(ImageView&, ivec2, vec4);
template <typename ImageView>
PutImagePixelNormPlanarFunc<ImageView> put_pixel_norm_planar_func(const ImageView& image);

template <typename ImageView>
using PutImagePixelNormVolumetricFunc = void(*)(ImageView&, ivec3, vec4);
template <typename ImageView>
PutImagePixelNormVolumetricFunc<ImageView> put_pixel_norm_volumetric_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////

template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, I32 pixel_coord);

template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, ivec2 pixel_coord);

template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, ivec3 pixel_coord);

///////////////////////////////////////////////////////////////////////////////

template <typename ImageView>
void put_pixel_norm(ImageView& image, I32 pixel_coord, vec4 pixel);

template <typename ImageView>
void put_pixel_norm(ImageView& image, ivec2 pixel_coord, vec4 pixel);

template <typename ImageView>
void put_pixel_norm(ImageView& image, ivec3 pixel_coord, vec4 pixel);

} // be::gfx

#include "image_pixel_access_norm.inl"

#endif
