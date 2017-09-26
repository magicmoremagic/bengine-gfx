#include "pch.hpp"
#include "tex/field_type.hpp"

/*!! include 'tex/field_type' !! 68 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(FieldType constant) noexcept {
   switch (constant) {
      case FieldType::none:
      case FieldType::unorm:
      case FieldType::snorm:
      case FieldType::uint:
      case FieldType::sint:
      case FieldType::ufloat:
      case FieldType::sfloat:
      case FieldType::expo:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* field_type_name(FieldType constant) noexcept {
   switch (constant) {
      case FieldType::none:   return "none";
      case FieldType::unorm:  return "unorm";
      case FieldType::snorm:  return "snorm";
      case FieldType::uint:   return "uint";
      case FieldType::sint:   return "sint";
      case FieldType::ufloat: return "ufloat";
      case FieldType::sfloat: return "sfloat";
      case FieldType::expo:   return "expo";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const FieldType, 8> field_type_values() noexcept {
   return ::be::EnumTraits<FieldType>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, FieldType constant) {
   if (is_valid(constant)) {
      os << field_type_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
bool is_unsigned(FieldType constant) noexcept {
   switch (constant) {
      case FieldType::unorm:  return true;
      case FieldType::uint:   return true;
      case FieldType::ufloat: return true;
      default:
         return false;
   }
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */

