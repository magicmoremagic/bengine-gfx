#pragma once
#ifndef BE_GFX_TEXTURE_CLASS_HPP_
#define BE_GFX_TEXTURE_CLASS_HPP_

#include <be/core/be.hpp>

namespace be::gfx {

/*!! include 'texture_class' !! 21 */
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

bool is_valid(TextureClass constant);
const char* texture_class_name(TextureClass constant);
bool is_array(TextureClass constant);
U8 dimensionality(TextureClass constant);
U8 degree(TextureClass constant);
U8 faces(TextureClass constant);
/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx

#endif
