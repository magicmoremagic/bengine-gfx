#pragma once
#ifndef BE_GFX_BLIT_IMAGE_PIXELS_HPP_
#define BE_GFX_BLIT_IMAGE_PIXELS_HPP_

#include "blit_image_blocks.hpp"
#include "converting_pixel_blitter.hpp"

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void blit_pixels(const SourceImageView& src, DestImageView& dest);

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void blit_pixels(const SourceImageView& src, ImageRegion src_region, DestImageView& dest, ImageRegion dest_region);

} // be::gfx

#include "blit_image_pixels.inl"

#endif
