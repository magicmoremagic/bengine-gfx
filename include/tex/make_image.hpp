#pragma once
#ifndef BE_GFX_TEX_MAKE_IMAGE_HPP_
#define BE_GFX_TEX_MAKE_IMAGE_HPP_

#include "image.hpp"
#include <be/core/glm_helpers.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
Image make_image(const ImageFormat& format, Coord dim, Buf<UC> buf = Buf<UC>(), TextureAlignment alignment = TextureAlignment());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
std::size_t calculate_required_image_size(const ImageFormat& format, Coord dim, TextureAlignment alignment = TextureAlignment());

} // be::gfx::tex

#include "make_image.inl"

#endif
