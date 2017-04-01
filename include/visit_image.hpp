#pragma once
#ifndef BE_GFX_VISIT_IMAGE_HPP_
#define BE_GFX_VISIT_IMAGE_HPP_

#include "image_view.hpp"
#include <be/core/be.hpp>
#include <be/core/glm.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_blocks_lineal(ImageView& image, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_blocks_planar(ImageView& image, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_blocks_volumetric(ImageView& image, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_pixels_lineal(ImageView& image, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_pixels_planar(ImageView& image, Visitor visitor = Visitor());

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_pixels_volumetric(ImageView& image, Visitor visitor = Visitor());

} // be::gfx

#include "visit_image.inl"

#endif
