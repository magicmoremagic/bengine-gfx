#pragma once
#ifndef BE_GFX_TEXTURE_VIEW_HASH_HPP_
#define BE_GFX_TEXTURE_VIEW_HASH_HPP_

#include "texture_view.hpp"
#include <be/core/alg.hpp>
#include <functional>

/*!! write_template('common/std_hash', 'be::gfx::TextureView')
write_template('common/std_hash', 'be::gfx::ConstTextureView') !! 20 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

template <>
struct std::hash<be::gfx::TextureView> {
   std::size_t operator()(const be::gfx::TextureView& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

template <>
struct std::hash<be::gfx::ConstTextureView> {
   std::size_t operator()(const be::gfx::ConstTextureView& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
