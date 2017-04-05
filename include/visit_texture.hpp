#pragma once
#ifndef BE_GFX_VISIT_TEXTURE_HPP_
#define BE_GFX_VISIT_TEXTURE_HPP_

#include <be/core/glm_helpers.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename Visitor, typename TextureView>
void visit_texture_images(TextureView& texture, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename TextureView>
void visit_texture_blocks(TextureView& texture, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename TextureView>
void visit_texture_pixels(TextureView& texture, Visitor visitor = Visitor());

} // be::gfx

#include "visit_texture.inl"

#endif
