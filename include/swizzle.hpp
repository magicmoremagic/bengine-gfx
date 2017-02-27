#pragma once
#ifndef BE_GFX_SWIZZLE_HPP_
#define BE_GFX_SWIZZLE_HPP_

#include <be/core/be.hpp>

namespace be::gfx {

/*!! include 'swizzle' !! 16 */
/* ######## !! GENERATED CODE -- DO NOT MODIFY !! ######## */

///////////////////////////////////////////////////////////////////////////////
enum class Swizzle : U8 {
   zero = 0,
   one,
   red,
   green,
   blue,
   alpha
};

bool is_valid(Swizzle constant);
const char* swizzle_name(Swizzle constant);
/* ################ END OF GENERATED CODE ################ */

} // be::gfx

#endif
