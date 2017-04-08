#pragma once
#ifndef BE_GFX_TEX_VISIT_IMAGE_HPP_
#define BE_GFX_TEX_VISIT_IMAGE_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/glm_helpers.hpp>
#include <be/core/extents.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename ImageView>
void visit_image_blocks(ImageView& image, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename ImageView>
void visit_image_blocks(ImageView& image, ibox block_extents, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename ImageView>
void visit_image_pixels(ImageView& image, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename ImageView>
void visit_image_pixels(ImageView& image, ibox extents, Visitor visitor = Visitor());

} // be::gfx::tex

#include "visit_image.inl"

#endif
