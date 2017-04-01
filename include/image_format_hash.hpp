#pragma once
#ifndef BE_GFX_IMAGE_FORMAT_HASH_HPP_
#define BE_GFX_IMAGE_FORMAT_HASH_HPP_

#include "image_format.hpp"
#include <be/core/alg.hpp>
#include <functional>

/*!! write_template('common/std_hash', 'be::gfx::ImageFormat') !! 12 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

template <>
struct std::hash<be::gfx::ImageFormat> {
   std::size_t operator()(const be::gfx::ImageFormat& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
