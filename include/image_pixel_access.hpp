#pragma once
#ifndef BE_GFX_IMAGE_PIXEL_ACCESS_HPP_
#define BE_GFX_IMAGE_PIXEL_ACCESS_HPP_

#include <be/core/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace be::gfx {

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, I32 pixel_coord);

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, ivec2 pixel_coord);

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, ivec3 pixel_coord);

template <typename T, typename ImageView>
void put_pixel(ImageView& image, I32 pixel_coord, T pixel);

template <typename T, typename ImageView>
void put_pixel(ImageView& image, ivec2 pixel_coord, T pixel);

template <typename T, typename ImageView>
void put_pixel(ImageView& image, ivec3 pixel_coord, T pixel);

} // be::gfx

#endif
