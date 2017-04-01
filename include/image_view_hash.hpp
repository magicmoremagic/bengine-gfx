#pragma once
#ifndef BE_GFX_IMAGE_VIEW_HASH_HPP_
#define BE_GFX_IMAGE_VIEW_HASH_HPP_

#include "image_view.hpp"
#include <be/core/alg.hpp>
#include <functional>

/*!! write_template('common/std_hash', 'be::gfx::ImageView')
write_template('common/std_hash', 'be::gfx::ConstImageView') !! 20 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

template <>
struct std::hash<be::gfx::ImageView> {
   std::size_t operator()(const be::gfx::ImageView& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

template <>
struct std::hash<be::gfx::ConstImageView> {
   std::size_t operator()(const be::gfx::ConstImageView& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
