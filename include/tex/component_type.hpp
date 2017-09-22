#pragma once
#ifndef BE_GFX_TEX_COMPONENT_TYPE_HPP_
#define BE_GFX_TEX_COMPONENT_TYPE_HPP_

#include <be/core/enum_traits.hpp>

/*!! include 'tex/component_type' !! 61 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class ComponentType : U8 {
   none = 0,
   unorm,
   snorm,
   uint,
   sint,
   ufloat,
   sfloat,
   expo
};

bool is_valid(ComponentType constant) noexcept;
const char* component_type_name(ComponentType constant) noexcept;
std::array<const ComponentType, 8> component_type_values() noexcept;
std::ostream& operator<<(std::ostream& os, ComponentType constant);
bool is_unsigned(ComponentType constant) noexcept;

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::ComponentType> {
   using type = ::be::gfx::tex::ComponentType;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 8;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::component_type_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::ComponentType::none,
         ::be::gfx::tex::ComponentType::unorm,
         ::be::gfx::tex::ComponentType::snorm,
         ::be::gfx::tex::ComponentType::uint,
         ::be::gfx::tex::ComponentType::sint,
         ::be::gfx::tex::ComponentType::ufloat,
         ::be::gfx::tex::ComponentType::sfloat,
         ::be::gfx::tex::ComponentType::expo,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
