#pragma once
#ifndef BE_GFX_VISIT_TEXTURE_HPP_
#define BE_GFX_VISIT_TEXTURE_HPP_

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_images(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_blocks(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_pixels(TextureView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_pixels_norm(TextureView& texture, Visitor visitor);

} // be::gfx

#endif
