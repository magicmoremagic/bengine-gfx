#pragma once
#ifndef BE_GFX_TEXTURE_VIEW_HASH_HPP_
#define BE_GFX_TEXTURE_VIEW_HASH_HPP_

#include "texture_view.hpp"
/*!! write_template('common/std_hash', 'be::gfx::TextureView') !! 14 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
#include <be/core/alg.hpp>
#include <functional>

template <>
struct std::hash<be::gfx::TextureView> {
   std::size_t operator()(const be::gfx::TextureView& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
