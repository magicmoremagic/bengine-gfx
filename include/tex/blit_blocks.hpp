#pragma once
#ifndef BE_GFX_TEX_BLIT_BLOCKS_HPP_
#define BE_GFX_TEX_BLIT_BLOCKS_HPP_

#include "image_region.hpp"
#include "block_access.hpp"

namespace be::gfx::tex {

template <typename SourceImageView, typename DestImageView>
void blit_blocks(const SourceImageView& src, DestImageView& dest);

template <typename SourceImageView, typename DestImageView>
void blit_blocks(const SourceImageView& src, ImageRegion src_block_region, DestImageView& dest, ImageRegion dest_block_region);

} // be::gfx::tex

#include "blit_blocks.inl"

#endif
