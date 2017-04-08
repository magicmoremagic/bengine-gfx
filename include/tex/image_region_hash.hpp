#pragma once
#ifndef BE_GFX_TEX_IMAGE_REGION_HASH_HPP_
#define BE_GFX_TEX_IMAGE_REGION_HASH_HPP_

#include "image_region.hpp"
#include <be/core/alg.hpp>
#include <functional>

/*!! write_template('common/std_hash', 'be::gfx::tex::ImageRegion') !! 12 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

template <>
struct std::hash<be::gfx::tex::ImageRegion> {
   std::size_t operator()(const be::gfx::tex::ImageRegion& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
