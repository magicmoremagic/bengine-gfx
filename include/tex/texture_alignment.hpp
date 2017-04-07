#pragma once
#ifndef BE_GFX_TEXTURE_ALIGNMENT_HPP_
#define BE_GFX_TEXTURE_ALIGNMENT_HPP_

#include <be/core/be.hpp>

namespace be::gfx {

struct TextureAlignment {
   using alignment_type = U8;

   TextureAlignment(alignment_type line = 8u,
                    alignment_type plane = 0u,
                    alignment_type level = 0u,
                    alignment_type face = 0u,
                    alignment_type layer = 0u)
      : line(line),
        plane(plane),
        level(level),
        face(face),
        layer(layer) { }

   alignment_type line;
   alignment_type plane;
   alignment_type level;
   alignment_type face;
   alignment_type layer;

   bool operator==(const TextureAlignment& other) const {
      return line == other.line && plane == other.plane && level == other.level && face == other.face && layer == other.layer;
   }

   bool operator!=(const TextureAlignment& other) const {
      return !(*this == other);
   }
};

} // be::gfx

#endif
