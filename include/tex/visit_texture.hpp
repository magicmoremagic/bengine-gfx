#pragma once
#ifndef BE_GFX_TEX_VISIT_TEXTURE_HPP_
#define BE_GFX_TEX_VISIT_TEXTURE_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/glm_helpers.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename Visitor, typename TextureView>
void visit_texture_images(TextureView& texture, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename TextureView>
void visit_texture_blocks(TextureView& texture, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename TextureView>
void visit_texture_pixels(TextureView& texture, Visitor visitor = Visitor());

} // be::gfx::tex

#include "visit_texture.inl"

#endif
