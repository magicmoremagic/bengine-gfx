#include "pch.hpp"
#include "texture_class.hpp"

namespace be::gfx {

/*!! include 'texture_class' !! 79 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
bool is_valid(TextureClass constant) noexcept {
   switch (constant) {
      case TextureClass::lineal:
      case TextureClass::lineal_array:
      case TextureClass::planar:
      case TextureClass::planar_array:
      case TextureClass::volumetric:
      case TextureClass::directional:
      case TextureClass::directional_array:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* texture_class_name(TextureClass constant) noexcept {
   switch (constant) {
      case TextureClass::lineal:            return "lineal";
      case TextureClass::lineal_array:      return "lineal_array";
      case TextureClass::planar:            return "planar";
      case TextureClass::planar_array:      return "planar_array";
      case TextureClass::volumetric:        return "volumetric";
      case TextureClass::directional:       return "directional";
      case TextureClass::directional_array: return "directional_array";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
bool is_array(TextureClass constant) noexcept {
   switch (constant) {
      case TextureClass::lineal_array:      return true;
      case TextureClass::planar_array:      return true;
      case TextureClass::directional_array: return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 dimensionality(TextureClass constant) noexcept {
   switch (constant) {
      case TextureClass::lineal:            return U8(1);
      case TextureClass::lineal_array:      return U8(1);
      case TextureClass::volumetric:        return U8(3);
      default:
         return U8(2);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 degree(TextureClass constant) noexcept {
   switch (constant) {
      case TextureClass::lineal:            return U8(1);
      case TextureClass::planar_array:      return U8(3);
      case TextureClass::volumetric:        return U8(3);
      case TextureClass::directional_array: return U8(3);
      default:
         return U8(2);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 faces(TextureClass constant) noexcept {
   switch (constant) {
      case TextureClass::directional:       return U8(6);
      case TextureClass::directional_array: return U8(6);
      default:
         return U8(1);
   }
}

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx
