#pragma once
#ifndef BE_GFX_VISIT_IMAGE_HPP_
#define BE_GFX_VISIT_IMAGE_HPP_

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_blocks(ImageView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_pixels(ImageView& texture, Visitor visitor);

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_image_pixels_norm(ImageView& texture, Visitor visitor);

} // be::gfx

#endif
