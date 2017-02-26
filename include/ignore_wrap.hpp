#pragma once
#ifndef BE_GFX_IGNORE_WRAP_HPP_
#define BE_GFX_IGNORE_WRAP_HPP_

#include "filter_traits.hpp"
#include "fwd_types.hpp"
#include <be/core/be.hpp>
#include <gli/image.hpp>

namespace be {
namespace gfx {

struct IgnoreWrap {
   image::extent_type operator()(const image& image, image::extent_type tc, F32& weight) {
      if (tc.x < 0 || tc.x >= image.extent().x) {
         weight = 0;
         return image::extent_type();
      }

      if (image.extent().y > 0) {
         if (tc.y < 0 || tc.y >= image.extent().y) {
            weight = 0;
            return image::extent_type();
         }
      }
      if (image.extent().z > 0) {
         if (tc.z < 0 || tc.z >= image.extent().z) {
            weight = 0;
            return image::extent_type();
         }
      }
      return tc;
   }
};

} // be::gfx
} // be

#endif
