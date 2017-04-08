#pragma once
#ifndef BE_GFX_TEX_TEXTURE_CLASS_HPP_
#define BE_GFX_TEX_TEXTURE_CLASS_HPP_

#include <be/core/be.hpp>

namespace be::gfx::tex {

/*!! include 'tex/texture_class' !! 21 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
enum class TextureClass : U8 {
   lineal = 0,
   lineal_array,
   planar,
   planar_array,
   volumetric,
   directional,
   directional_array
};

bool is_valid(TextureClass constant) noexcept;
const char* texture_class_name(TextureClass constant) noexcept;
bool is_array(TextureClass constant) noexcept;
U8 dimensionality(TextureClass constant) noexcept;
U8 degree(TextureClass constant) noexcept;
U8 faces(TextureClass constant) noexcept;
/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx::tex

#endif
