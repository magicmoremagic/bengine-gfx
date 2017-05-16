#pragma once
#ifndef BE_GFX_TEX_TEXTURE_STORAGE_HASH_HPP_
#define BE_GFX_TEX_TEXTURE_STORAGE_HASH_HPP_

#include "texture_storage.hpp"
#include <be/core/alg.hpp>
#include <functional>

/*!! write_template('common/templates/std_hash', 'be::gfx::tex::TextureStorage') !! 12 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

template <>
struct std::hash<be::gfx::tex::TextureStorage> {
   std::size_t operator()(const be::gfx::tex::TextureStorage& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
