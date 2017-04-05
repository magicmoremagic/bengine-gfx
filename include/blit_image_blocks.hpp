#pragma once
#ifndef BE_GFX_BLIT_IMAGE_BLOCKS_HPP_
#define BE_GFX_BLIT_IMAGE_BLOCKS_HPP_

#include "image_region.hpp"
#include "image_block_access.hpp"

namespace be::gfx {

template <typename SourceImageView, typename DestImageView>
void blit_blocks(const SourceImageView& src, DestImageView& dest);

template <typename SourceImageView, typename DestImageView>
void blit_blocks(const SourceImageView& src, ImageRegion src_block_region, DestImageView& dest, ImageRegion dest_block_region);

} // be::gfx

#include "blit_image_blocks.inl"

#endif
