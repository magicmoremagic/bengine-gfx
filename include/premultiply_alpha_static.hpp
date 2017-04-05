#pragma once
#ifndef BE_GFX_PREMULTIPLY_ALPHA_STATIC_HPP_
#define BE_GFX_PREMULTIPLY_ALPHA_STATIC_HPP_

#include "premultiply_alpha.hpp"
#include <glm/vec4.hpp>

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
struct ConvertPremultiplicationNop {
   static vec4 convert(vec4 pixel_norm) {
      return pixel_norm;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <bool Input, bool Output>
struct ConvertPremultiplication : ConvertPremultiplicationNop { };

///////////////////////////////////////////////////////////////////////////////
template <> struct ConvertPremultiplication<false, true> {
   static vec4 convert(vec4 pixel_norm) {
      return premultiply_alpha(pixel_norm);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <> struct ConvertPremultiplication<true, false> {
   static vec4 convert(vec4 pixel_norm) {
      return unpremultiply_alpha(pixel_norm);
   }
};

} // be::gfx::detail

template <bool Input, bool Output>
ImagePixelNormTransformFunc convert_premultiplication_func() {
   return detail::ConvertPremultiplication<Input, Output>::convert;
}

} // be::gfx

#endif
