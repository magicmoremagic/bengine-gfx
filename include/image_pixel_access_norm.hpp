#pragma once
#ifndef BE_GFX_IMAGE_PIXEL_ACCESS_NORM_HPP_
#define BE_GFX_IMAGE_PIXEL_ACCESS_NORM_HPP_

#include "image_pixel_access.hpp"
#include <be/core/builtins.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace be::gfx {

template <typename ImageView, typename Coord> using GetImagePixelNormFunc = vec4(*)(const ImageView&, Coord);
template <typename ImageView, typename Coord> GetImagePixelNormFunc<ImageView, Coord> get_pixel_norm_func(const ImageView& image);

template <typename ImageView, typename Coord>
vec4 get_pixel_norm(const ImageView& image, Coord pixel_coord);

template <typename ImageView> using GetImagePixelNormLinealFunc = GetImagePixelNormFunc<ImageView, I32>;
template <typename ImageView> GetImagePixelNormLinealFunc<ImageView> get_pixel_norm_lineal_func(const ImageView& image);

template <typename ImageView> using GetImagePixelNormPlanarFunc = GetImagePixelNormFunc<ImageView, ivec2>;
template <typename ImageView> GetImagePixelNormPlanarFunc<ImageView> get_pixel_norm_planar_func(const ImageView& image);

template <typename ImageView> using GetImagePixelNormVolumetricFunc = GetImagePixelNormFunc<ImageView, ivec3>;
template <typename ImageView> GetImagePixelNormVolumetricFunc<ImageView> get_pixel_norm_volumetric_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////

template <typename ImageView, typename Coord> using PutImagePixelNormFunc = void(*)(ImageView&, Coord, vec4);
template <typename ImageView, typename Coord> PutImagePixelNormFunc<ImageView, Coord> put_pixel_norm_func(const ImageView& image);

template <typename ImageView, typename Coord>
void put_pixel_norm(ImageView& image, Coord pixel_coord, vec4 pixel);

template <typename ImageView> using PutImagePixelNormLinealFunc = PutImagePixelNormFunc<ImageView, I32>;
template <typename ImageView> PutImagePixelNormLinealFunc<ImageView> put_pixel_norm_lineal_func(const ImageView& image);

template <typename ImageView> using PutImagePixelNormPlanarFunc = PutImagePixelNormFunc<ImageView, ivec2>;
template <typename ImageView> PutImagePixelNormPlanarFunc<ImageView> put_pixel_norm_planar_func(const ImageView& image);

template <typename ImageView> using PutImagePixelNormVolumetricFunc = PutImagePixelNormFunc<ImageView, ivec3>;
template <typename ImageView> PutImagePixelNormVolumetricFunc<ImageView> put_pixel_norm_volumetric_func(const ImageView& image);

} // be::gfx

#include "image_pixel_access_norm.inl"

#endif
