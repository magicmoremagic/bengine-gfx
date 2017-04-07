#include "pch.hpp"
#include "image_component_type.hpp"

namespace be::gfx {

/*!! include 'image_component_type' !! 37 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
bool is_valid(ImageComponentType constant) noexcept {
   switch (constant) {
      case ImageComponentType::none:
      case ImageComponentType::unorm:
      case ImageComponentType::snorm:
      case ImageComponentType::uint:
      case ImageComponentType::sint:
      case ImageComponentType::ufloat:
      case ImageComponentType::sfloat:
      case ImageComponentType::expo:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* image_component_type_name(ImageComponentType constant) noexcept {
   switch (constant) {
      case ImageComponentType::none:   return "none";
      case ImageComponentType::unorm:  return "unorm";
      case ImageComponentType::snorm:  return "snorm";
      case ImageComponentType::uint:   return "uint";
      case ImageComponentType::sint:   return "sint";
      case ImageComponentType::ufloat: return "ufloat";
      case ImageComponentType::sfloat: return "sfloat";
      case ImageComponentType::expo:   return "expo";
      default:
         return "?";
   }
}

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx
