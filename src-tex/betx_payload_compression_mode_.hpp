#pragma once
#ifndef BE_GFX_TEX_BETX_PAYLOAD_COMPRESSION_MODE_HPP_
#define BE_GFX_TEX_BETX_PAYLOAD_COMPRESSION_MODE_HPP_

#include "tex/gfx_tex_autolink.hpp"
#include <be/core/enum_traits.hpp>

/*!! include 'tex/betx_payload_compression_mode' !! 48 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::betx::detail {

///////////////////////////////////////////////////////////////////////////////
enum class PayloadCompressionMode : U8 {
   none = 0,
   zlib
};

bool is_valid(PayloadCompressionMode constant) noexcept;
const char* payload_compression_mode_name(PayloadCompressionMode constant) noexcept;
std::array<const PayloadCompressionMode, 2> payload_compression_mode_values() noexcept;
std::ostream& operator<<(std::ostream& os, PayloadCompressionMode constant);

} // be::gfx::tex::betx::detail

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::betx::detail::PayloadCompressionMode> {
   using type = ::be::gfx::tex::betx::detail::PayloadCompressionMode;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 2;

   static bool is_valid(type value) {
      return ::be::gfx::tex::betx::detail::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::betx::detail::payload_compression_mode_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::betx::detail::PayloadCompressionMode::none,
         ::be::gfx::tex::betx::detail::PayloadCompressionMode::zlib,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
