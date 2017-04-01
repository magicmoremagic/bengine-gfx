#pragma once
#ifndef BE_GFX_VISIT_TEXTURE_HPP_
#define BE_GFX_VISIT_TEXTURE_HPP_

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_images(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_blocks_lineal(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_blocks_planar(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_blocks_volumetric(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_pixels_lineal(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_pixels_planar(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_pixels_volumetric(TextureView& texture, Visitor visitor);

} // be::gfx

#include "visit_texture.inl"

#endif
