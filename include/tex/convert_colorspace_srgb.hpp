#pragma once
#ifndef BE_GFX_TEX_CONVERT_COLORSPACE_SRGB_HPP_
#define BE_GFX_TEX_CONVERT_COLORSPACE_SRGB_HPP_

#include <be/core/glm.hpp>
#include <glm/fwd.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
inline F32 linear_to_srgb(F32 linear_color) {
   if (linear_color <= 0.00313066844250063f) {
      return linear_color * 12.92f;
   } else {
      return 1.055f * std::pow(linear_color, 1.f / 2.4f) - 0.055f;
   }
}

///////////////////////////////////////////////////////////////////////////////
inline F32 srgb_to_linear(F32 srgb_color) {
   if (srgb_color <= 0.0404482362771082f) {
      return srgb_color / 12.92f;
   } else {
      return std::pow((srgb_color + 0.055f) / 1.055f, 2.4f);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <glm::length_t L, glm::precision P>
inline glm::vec<L, F32, P> linear_to_srgb(glm::vec<L, F32, P> color) {
   for (glm::length_t l = 0; l < L; ++l) {
      color[l] = linear_to_srgb(color[l]);
   }
   return color;
}

///////////////////////////////////////////////////////////////////////////////
template <glm::length_t L, glm::precision P>
inline glm::vec<L, F32, P> srgb_to_linear(glm::vec<L, F32, P> color) {
   for (glm::length_t l = 0; l < L; ++l) {
      color[l] = srgb_to_linear(color[l]);
   }
   return color;
}

} // be::gfx::tex

#endif
