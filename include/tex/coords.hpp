#pragma once
#ifndef BE_GFX_TEX_COORDS_HPP_
#define BE_GFX_TEX_COORDS_HPP_

#include <be/core/glm_helpers.hpp>
#include <cassert>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
OutCoord convert_coord(InCoord coord);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
Coord to_pixel_coord(const ImageView& image, Coord block_coord, Coord block_local_coord = Coord());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
Coord to_block_coord(const ImageView& image, Coord pixel_coord);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
Coord to_block_local_coord(const ImageView& image, Coord pixel_coord);

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
std::pair<Coord, Coord> to_block_coords(const ImageView& image, Coord pixel_coord);

} // be::gfx::tex

#include "coords.inl"

#endif
