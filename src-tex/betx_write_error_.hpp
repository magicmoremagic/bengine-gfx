#pragma once
#ifndef BE_GFX_TEX_BETX_WRITE_ERROR_HPP_
#define BE_GFX_TEX_BETX_WRITE_ERROR_HPP_

#include "tex/texture_file_error.hpp"
#include <be/core/enum_traits.hpp>

/*!! include 'tex/betx_write_error' !! 71 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
enum class BetxWriteError : U8 {
   invalid_endianness = 1,
   empty_texture,
   invalid_texture_class,
   invalid_block_packing,
   invalid_colorspace,
   invalid_layer_count,
   invalid_face_count,
   invalid_level_count,
   invalid_component_type,
   invalid_swizzle,
   invalid_payload_compression,
   not_enough_memory
};

bool is_valid(BetxWriteError constant) noexcept;
const char* betx_write_error_name(BetxWriteError constant) noexcept;
std::array<const BetxWriteError, 12> betx_write_error_values() noexcept;
std::ostream& operator<<(std::ostream& os, BetxWriteError constant);
int texture_file_error_condition(BetxWriteError constant) noexcept;
int generic_error_condition(BetxWriteError constant) noexcept;
const char* write_error_msg(BetxWriteError constant) noexcept;

} // be::gfx::tex::detail

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::detail::BetxWriteError> {
   using type = ::be::gfx::tex::detail::BetxWriteError;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 12;

   static bool is_valid(type value) {
      return ::be::gfx::tex::detail::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::detail::betx_write_error_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::detail::BetxWriteError::invalid_endianness,
         ::be::gfx::tex::detail::BetxWriteError::empty_texture,
         ::be::gfx::tex::detail::BetxWriteError::invalid_texture_class,
         ::be::gfx::tex::detail::BetxWriteError::invalid_block_packing,
         ::be::gfx::tex::detail::BetxWriteError::invalid_colorspace,
         ::be::gfx::tex::detail::BetxWriteError::invalid_layer_count,
         ::be::gfx::tex::detail::BetxWriteError::invalid_face_count,
         ::be::gfx::tex::detail::BetxWriteError::invalid_level_count,
         ::be::gfx::tex::detail::BetxWriteError::invalid_component_type,
         ::be::gfx::tex::detail::BetxWriteError::invalid_swizzle,
         ::be::gfx::tex::detail::BetxWriteError::invalid_payload_compression,
         ::be::gfx::tex::detail::BetxWriteError::not_enough_memory,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
class BetxWriteErrorCategory : public std::error_category {
public:
   virtual const char* name() const noexcept { return "beTx Write Error"; }
   virtual S message(int condition) const;
   virtual bool equivalent(int code, const std::error_condition& condition) const noexcept;
};

const std::error_category& betx_write_error_category();
std::error_code make_error_code(BetxWriteError e);
std::error_condition make_error_condition(BetxWriteError e);

} // be::gfx::tex::detail

namespace std {

///////////////////////////////////////////////////////////////////////////////
template <>
struct is_error_code_enum<be::gfx::tex::detail::BetxWriteError> : std::true_type { };

} // std

#endif
