#pragma once
#ifndef BE_GFX_TEXTURE_STORAGE_HASH_HPP_
#define BE_GFX_TEXTURE_STORAGE_HASH_HPP_

#include "texture_storage.hpp"
/*!! write_template('common/std_hash', 'be::gfx::TextureStorage') !! 14 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
#include <be/core/alg.hpp>
#include <functional>

template <>
struct std::hash<be::gfx::TextureStorage> {
   std::size_t operator()(const be::gfx::TextureStorage& o) const {
      using be::std_hash;
      return std_hash(o);
   }
};

/* ######################### END OF GENERATED CODE ######################### */

#endif
