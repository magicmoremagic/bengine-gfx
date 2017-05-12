#pragma once
#ifndef BE_GFX_TEX_SWIZZLE_HPP_
#define BE_GFX_TEX_SWIZZLE_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/gfx/glbinding.hpp>
#include <be/core/be.hpp>

namespace be::gfx::tex {

/*!! include 'tex/swizzle' !! 18 */
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
gl::GLenum swizzle_to_gl(Swizzle constant) noexcept;
Swizzle swizzle_from_gl(gl::GLenum constant) noexcept;
/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx::tex

#endif
