#include "pch.hpp"
#include "tex/component_type.hpp"

/*!! include 'tex/component_type' !! 68 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

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

///////////////////////////////////////////////////////////////////////////////
std::array<const ComponentType, 8> component_type_values() noexcept {
   return ::be::EnumTraits<ComponentType>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, ComponentType constant) {
   if (is_valid(constant)) {
      os << component_type_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
bool is_unsigned(ComponentType constant) noexcept {
   switch (constant) {
      case ComponentType::unorm:  return true;
      case ComponentType::uint:   return true;
      case ComponentType::ufloat: return true;
      default:
         return false;
   }
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */

