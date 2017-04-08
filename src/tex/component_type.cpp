#include "tex/pch.hpp"
#include "tex/component_type.hpp"

namespace be::gfx::tex {

/*!! include 'tex/component_type' !! 37 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
bool is_valid(ComponentType constant) noexcept {
   switch (constant) {
      case ComponentType::none:
      case ComponentType::unorm:
      case ComponentType::snorm:
      case ComponentType::uint:
      case ComponentType::sint:
      case ComponentType::ufloat:
      case ComponentType::sfloat:
      case ComponentType::expo:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* component_type_name(ComponentType constant) noexcept {
   switch (constant) {
      case ComponentType::none:   return "none";
      case ComponentType::unorm:  return "unorm";
      case ComponentType::snorm:  return "snorm";
      case ComponentType::uint:   return "uint";
      case ComponentType::sint:   return "sint";
      case ComponentType::ufloat: return "ufloat";
      case ComponentType::sfloat: return "sfloat";
      case ComponentType::expo:   return "expo";
      default:
         return "?";
   }
}

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx::tex
