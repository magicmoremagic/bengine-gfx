#pragma once
#ifndef BE_GFX_TEX_SWIZZLE_HPP_
#define BE_GFX_TEX_SWIZZLE_HPP_

#include <be/gfx/bgl.hpp>
#include <be/core/enum_traits.hpp>

/*!! include 'tex/swizzle' !! 58 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class Swizzle : U8 {
   field_zero = 0,
   field_one,
   field_two,
   field_three,
   literal_zero,
   literal_one
};

bool is_valid(Swizzle constant) noexcept;
const char* swizzle_name(Swizzle constant) noexcept;
std::array<const Swizzle, 6> swizzle_values() noexcept;
std::ostream& operator<<(std::ostream& os, Swizzle constant);
gl::AllEnums swizzle_to_gl(be::gfx::tex::Swizzle constant) noexcept;
be::gfx::tex::Swizzle swizzle_from_gl(gl::AllEnums constant) noexcept;

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::Swizzle> {
   using type = ::be::gfx::tex::Swizzle;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 6;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::swizzle_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::Swizzle::field_zero,
         ::be::gfx::tex::Swizzle::field_one,
         ::be::gfx::tex::Swizzle::field_two,
         ::be::gfx::tex::Swizzle::field_three,
         ::be::gfx::tex::Swizzle::literal_zero,
         ::be::gfx::tex::Swizzle::literal_one,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
