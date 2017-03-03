#pragma once
#ifndef BE_GFX_MAKE_IMAGE_HPP_
#define BE_GFX_MAKE_IMAGE_HPP_

#include "image.hpp"

namespace be::gfx {

Image make_image(const ImageFormat& format, I32 dim, Buf<UC> buf = Buf<UC>());
Image make_image(const ImageFormat& format, ivec1 dim, Buf<UC> buf = Buf<UC>());
Image make_image(const ImageFormat& format, ivec2 dim, Buf<UC> buf = Buf<UC>());
Image make_image(const ImageFormat& format, ivec3 dim, Buf<UC> buf = Buf<UC>());

std::size_t calculate_required_image_size(const ImageFormat& format, I32 dim);
std::size_t calculate_required_image_size(const ImageFormat& format, ivec1 dim);
std::size_t calculate_required_image_size(const ImageFormat& format, ivec2 dim);
std::size_t calculate_required_image_size(const ImageFormat& format, ivec3 dim);

} // be::gfx

#endif
