#pragma once
#ifndef BE_GFX_IMAGE_COMPONENT_TYPE_HPP_
#define BE_GFX_IMAGE_COMPONENT_TYPE_HPP_

#include <be/core/be.hpp>

namespace be::gfx {

/*!! include 'image_component_type' !! 18 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
enum class ImageComponentType : U8 {
   none = 0,
   unorm,
   snorm,
   uint,
   sint,
   ufloat,
   sfloat,
   expo
};

bool is_valid(ImageComponentType constant);
const char* image_component_type_name(ImageComponentType constant);
/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx

#endif
