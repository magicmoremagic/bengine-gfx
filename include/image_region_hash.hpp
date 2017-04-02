#pragma once
#ifndef BE_GFX_IMAGE_REGION_HASH_HPP_
#define BE_GFX_IMAGE_REGION_HASH_HPP_

#include "image_region.hpp"
#include <be/core/alg.hpp>
#include <functional>

/*!! write_template('common/std_hash', 'be::gfx::ImageRegion') !! 12 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

template <>
struct std::hash<be::gfx::ImageRegion> {
   std::size_t operator()(const be::gfx::ImageRegion& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
