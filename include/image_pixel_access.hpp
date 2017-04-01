#pragma once
#ifndef BE_GFX_IMAGE_PIXEL_ACCESS_HPP_
#define BE_GFX_IMAGE_PIXEL_ACCESS_HPP_

#include "image_block_packing.hpp"
#include "image_format.hpp"
#include <be/core/glm.hpp>
#include <be/core/glm_helpers.hpp>
#include <cassert>

namespace be::gfx {

template <typename T, typename ImageView, typename Coord> using GetImagePixelFunc = T(*)(const ImageView&, Coord);
template <typename T, typename ImageView, typename Coord> GetImagePixelFunc<T, ImageView, Coord> get_pixel_func(const ImageView& image);

template <typename T, typename ImageView, typename Coord>
T get_pixel(const ImageView& image, Coord pixel_coord);

template <typename T, typename ImageView> using GetImagePixelLinealFunc = GetImagePixelFunc<T, ImageView, I32>;
template <typename T, typename ImageView> GetImagePixelLinealFunc<T, ImageView> get_pixel_lineal_func(const ImageView& image);

template <typename T, typename ImageView> using GetImagePixelPlanarFunc = GetImagePixelFunc<T, ImageView, ivec2>;
template <typename T, typename ImageView> GetImagePixelPlanarFunc<T, ImageView> get_pixel_planar_func(const ImageView& image);

template <typename T, typename ImageView> using GetImagePixelVolumetricFunc = GetImagePixelFunc<T, ImageView, ivec3>;
template <typename T, typename ImageView> GetImagePixelVolumetricFunc<T, ImageView> get_pixel_volumetric_func(const ImageView& image);

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename ImageView, typename Coord> using PutImagePixelFunc = void(*)(ImageView&, Coord, T);
template <typename T, typename ImageView, typename Coord> PutImagePixelFunc<T, ImageView, Coord> put_pixel_func(const ImageView& image);

template <typename T, typename ImageView, typename Coord>
void put_pixel(ImageView& image, Coord pixel_coord, T pixel);

template <typename T, typename ImageView> using PutImagePixelLinealFunc = PutImagePixelFunc<T, ImageView, I32>;
template <typename T, typename ImageView> PutImagePixelLinealFunc<T, ImageView> put_pixel_lineal_func(const ImageView& image);

template <typename T, typename ImageView> using PutImagePixelPlanarFunc = PutImagePixelFunc<T, ImageView, ivec2>;
template <typename T, typename ImageView> PutImagePixelPlanarFunc<T, ImageView> put_pixel_planar_func(const ImageView& image);

template <typename T, typename ImageView> using PutImagePixelVolumetricFunc = PutImagePixelFunc<T, ImageView, ivec3>;
template <typename T, typename ImageView> PutImagePixelVolumetricFunc<T, ImageView> put_pixel_volumetric_func(const ImageView& image);

} // be::gfx

#include "image_pixel_access.inl"

#endif
