#include "pch.hpp"
#include "premultiply_alpha.hpp"
#include <glm/vec4.hpp>

namespace be::gfx {
namespace {

///////////////////////////////////////////////////////////////////////////////
vec4 nop(vec4 p) {
   return p;
}

} // be::gfx::()

///////////////////////////////////////////////////////////////////////////////
vec4 premultiply_alpha(vec4 unpremultiplied) {
   return vec4(unpremultiplied.x * unpremultiplied.a,
               unpremultiplied.y * unpremultiplied.a,
               unpremultiplied.z * unpremultiplied.a,
               unpremultiplied.a);
}

///////////////////////////////////////////////////////////////////////////////
vec4 unpremultiply_alpha(vec4 premultiplied) {
   return vec4(premultiplied.x / premultiplied.a,
               premultiplied.y / premultiplied.a,
               premultiplied.z / premultiplied.a,
               premultiplied.a);
}

///////////////////////////////////////////////////////////////////////////////
ImagePixelNormTransformFunc convert_premultiplication_func(bool input, bool output) {
   if (input != output) {
      if (output) {
         return premultiply_alpha;
      } else {
         return unpremultiply_alpha;
      }
   } else {
      return nop;
   }
}

} // be::gfx
