#pragma once
#ifndef BE_GFX_TEX_CONVERT_COLORSPACE_SRGB_HPP_
#define BE_GFX_TEX_CONVERT_COLORSPACE_SRGB_HPP_

#include <be/core/glm.hpp>
#include <glm/vec3.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
inline vec3 linear_to_srgb(vec3 linear_color) {
   for (glm::length_t i = 0; i < 3; ++i) {
      const F32 c = linear_color[i];
      if (c <= 0.00313066844250063f) {
         linear_color[i] = c * 12.92f;
      } else {
         linear_color[i] = 1.055f * std::pow(c, 1.f / 2.4f) - 0.055f;
      }
   }
   return linear_color;
}

///////////////////////////////////////////////////////////////////////////////
inline vec3 srgb_to_linear(vec3 srgb_color) {
   for (glm::length_t i = 0; i < 3; ++i) {
      const F32 c = srgb_color[i];
      if (c <= 0.0404482362771082f) {
         srgb_color[i] = c / 12.92f;
      } else {
         srgb_color[i] = std::pow((c + 0.055f) / 1.055f, 2.4f);
      }
   }
   return srgb_color;
}

} // be::gfx::tex

#endif
