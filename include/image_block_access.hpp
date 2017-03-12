#pragma once
#ifndef BE_GFX_IMAGE_BLOCK_ACCESS_HPP_
#define BE_GFX_IMAGE_BLOCK_ACCESS_HPP_

#include <be/core/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace be::gfx {

template <typename T, typename ImageView>
T get_block(const ImageView& image, I32 block_coord);

template <typename T, typename ImageView>
T get_block(const ImageView& image, ivec2 block_coord);

template <typename T, typename ImageView>
T get_block(const ImageView& image, ivec3 block_coord);

template <typename T, typename ImageView>
void put_block(ImageView& image, I32 block_coord, const T& block);

template <typename T, typename ImageView>
void put_block(ImageView& image, ivec2 block_coord, const T& block);

template <typename T, typename ImageView>
void put_block(ImageView& image, ivec3 block_coord, const T& block);

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, I32 pixel_coord);

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, ivec2 pixel_coord);

template <typename T, typename ImageView>
T get_pixel(const ImageView& image, ivec3 pixel_coord);

template <typename T, typename ImageView>
void put_pixel(ImageView& image, I32 pixel_coord, const T& pixel);

template <typename T, typename ImageView>
void put_pixel(ImageView& image, ivec2 pixel_coord, const T& pixel);

template <typename T, typename ImageView>
void put_pixel(ImageView& image, ivec3 pixel_coord, const T& pixel);

} // be::gfx

#endif
