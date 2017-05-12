#pragma once
#ifndef BE_GFX_TEX_COMPONENT_TYPE_HPP_
#define BE_GFX_TEX_COMPONENT_TYPE_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/be.hpp>

namespace be::gfx::tex {

/*!! include 'tex/component_type' !! 19 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
enum class ComponentType : U8 {
   none = 0,
   unorm,
   snorm,
   uint,
   sint,
   ufloat,
   sfloat,
   expo
};

bool is_valid(ComponentType constant) noexcept;
const char* component_type_name(ComponentType constant) noexcept;
bool is_unsigned(ComponentType constant) noexcept;
/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx::tex

#endif
