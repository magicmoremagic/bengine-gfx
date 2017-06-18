#include "pch.hpp"
#include "tex/texture_class.hpp"

/*!! include 'tex/texture_class' !! 104 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(TextureClass constant) noexcept {
   switch (constant) {
      case TextureClass::lineal:
      case TextureClass::lineal_array:
      case TextureClass::planar:
      case TextureClass::planar_array:
      case TextureClass::volumetric:
      case TextureClass::volumetric_array:
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
      case TextureClass::volumetric_array:  return "volumetric_array";
      case TextureClass::directional:       return "directional";
      case TextureClass::directional_array: return "directional_array";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const TextureClass, 8> texture_class_values() noexcept {
   return ::be::EnumTraits<TextureClass>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, TextureClass constant) {
   if (is_valid(constant)) {
      os << texture_class_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
bool is_array(TextureClass constant) noexcept {
   switch (constant) {
      case TextureClass::lineal_array:      return true;
      case TextureClass::planar_array:      return true;
      case TextureClass::volumetric_array:  return true;
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
      case TextureClass::volumetric_array:  return U8(3);
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
      case TextureClass::volumetric_array:  return U8(4);
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

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */
