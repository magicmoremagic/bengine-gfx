#pragma once
#ifndef BE_GFX_TEX_BLOCK_ACCESS_HPP_
#define BE_GFX_TEX_BLOCK_ACCESS_HPP_

#include <be/core/glm_helpers.hpp>
#include <cassert>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
std::size_t block_offset(const ImageView& image, Coord block_coord);

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
T get_block(const ImageView& image, Coord block_coord);

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
void put_block(ImageView& image, Coord block_coord, const T& block);

} // be::gfx::tex

#include "block_access.inl"

#endif
