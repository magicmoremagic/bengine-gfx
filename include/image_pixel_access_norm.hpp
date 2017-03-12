#pragma once
#ifndef BE_GFX_IMAGE_PIXEL_ACCESS_NORM_HPP_
#define BE_GFX_IMAGE_PIXEL_ACCESS_NORM_HPP_

#include <be/core/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace be::gfx {

template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, I32 pixel_coord);

template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, ivec2 pixel_coord);

template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, ivec3 pixel_coord);

template <typename ImageView>
void put_pixel_norm(ImageView& image, I32 pixel_coord, const vec4& pixel);

template <typename ImageView>
void put_pixel_norm(ImageView& image, ivec2 pixel_coord, const vec4& pixel);

template <typename ImageView>
void put_pixel_norm(ImageView& image, ivec3 pixel_coord, const vec4& pixel);

} // be::gfx

#endif
