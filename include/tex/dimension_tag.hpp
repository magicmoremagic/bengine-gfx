#pragma once
#ifndef BE_GFX_TEX_DIMENSION_TAG_HPP_
#define BE_GFX_TEX_DIMENSION_TAG_HPP_

#include <be/core/glm.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
template <glm::length_t Dimension>
using DimensionTag = std::integral_constant<glm::length_t, Dimension>;

} // be::gfx::tex::detail

#endif
