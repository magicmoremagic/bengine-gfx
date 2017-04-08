#pragma once
#ifndef BE_GFX_TEX_IMAGE_VIEW_HASH_HPP_
#define BE_GFX_TEX_IMAGE_VIEW_HASH_HPP_

#include "image_view.hpp"
#include <be/core/alg.hpp>
#include <functional>

/*!! write_template('common/std_hash', 'be::gfx::tex::ImageView')
write_template('common/std_hash', 'be::gfx::tex::ConstImageView') !! 20 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

template <>
struct std::hash<be::gfx::tex::ImageView> {
   std::size_t operator()(const be::gfx::tex::ImageView& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

template <>
struct std::hash<be::gfx::tex::ConstImageView> {
   std::size_t operator()(const be::gfx::tex::ConstImageView& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
