#pragma once
#ifndef BE_GFX_TEX_SWIZZLE_HPP_
#define BE_GFX_TEX_SWIZZLE_HPP_

#include <be/core/be.hpp>

namespace be::gfx::tex {

/*!! include 'tex/swizzle' !! 16 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
enum class Swizzle : U8 {
   zero = 0,
   one,
   red,
   green,
   blue,
   alpha
};

bool is_valid(Swizzle constant) noexcept;
const char* swizzle_name(Swizzle constant) noexcept;
/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx::tex

#endif
