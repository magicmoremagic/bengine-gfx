#pragma once
#ifndef BE_GFX_TEX_TEXTURE_CLASS_HPP_
#define BE_GFX_TEX_TEXTURE_CLASS_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/enum_traits.hpp>

/*!! include 'tex/texture_class' !! 62 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class TextureClass : U8 {
   lineal = 0,
   lineal_array,
   planar,
   planar_array,
   volumetric,
   directional,
   directional_array
};

bool is_valid(TextureClass constant) noexcept;
const char* texture_class_name(TextureClass constant) noexcept;
std::array<const TextureClass, 7> texture_class_values() noexcept;
std::ostream& operator<<(std::ostream& os, TextureClass constant);
bool is_array(TextureClass constant) noexcept;
U8 dimensionality(TextureClass constant) noexcept;
U8 degree(TextureClass constant) noexcept;
U8 faces(TextureClass constant) noexcept;

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::TextureClass> {
   using type = ::be::gfx::tex::TextureClass;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 7;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::texture_class_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::TextureClass::lineal,
         ::be::gfx::tex::TextureClass::lineal_array,
         ::be::gfx::tex::TextureClass::planar,
         ::be::gfx::tex::TextureClass::planar_array,
         ::be::gfx::tex::TextureClass::volumetric,
         ::be::gfx::tex::TextureClass::directional,
         ::be::gfx::tex::TextureClass::directional_array,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
