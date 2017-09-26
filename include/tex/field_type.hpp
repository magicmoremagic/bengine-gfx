#pragma once
#ifndef BE_GFX_TEX_FIELD_TYPE_HPP_
#define BE_GFX_TEX_FIELD_TYPE_HPP_

#include <be/core/enum_traits.hpp>

/*!! include 'tex/field_type' !! 61 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class FieldType : U8 {
   none = 0,
   unorm,
   snorm,
   uint,
   sint,
   ufloat,
   sfloat,
   expo
};

bool is_valid(FieldType constant) noexcept;
const char* field_type_name(FieldType constant) noexcept;
std::array<const FieldType, 8> field_type_values() noexcept;
std::ostream& operator<<(std::ostream& os, FieldType constant);
bool is_unsigned(FieldType constant) noexcept;

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::FieldType> {
   using type = ::be::gfx::tex::FieldType;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 8;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::field_type_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::FieldType::none,
         ::be::gfx::tex::FieldType::unorm,
         ::be::gfx::tex::FieldType::snorm,
         ::be::gfx::tex::FieldType::uint,
         ::be::gfx::tex::FieldType::sint,
         ::be::gfx::tex::FieldType::ufloat,
         ::be::gfx::tex::FieldType::sfloat,
         ::be::gfx::tex::FieldType::expo,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
