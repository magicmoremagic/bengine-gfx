#pragma once
#ifndef BE_GFX_TEX_BETX_READ_ERROR_HPP_
#define BE_GFX_TEX_BETX_READ_ERROR_HPP_

#include "tex/texture_file_error.hpp"
#include <be/core/enum_traits.hpp>

/*!! include 'tex/betx_read_error' !! 140 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
enum class BetxReadError : U8 {
   not_a_mmm_binary_file = 1,
   not_a_betx_file,
   crlf_corruption,
   lf_corruption,
   header_missing,
   footer_missing,
   invalid_endianness,
   unsupported_file_version,
   invalid_texture_class,
   invalid_dimensions,
   unsupported_dimensions,
   invalid_layer_count,
   unsupported_layer_count,
   invalid_face_count,
   unsupported_face_count,
   invalid_level_count,
   unsupported_level_count,
   unnecessary_levels,
   unsupported_alignment,
   noncanonical_alignment,
   invalid_block_packing,
   invalid_block_dimensions,
   unsupported_block_dimensions,
   invalid_block_size,
   unsupported_block_size,
   invalid_field_type,
   invalid_component_count,
   too_many_components,
   invalid_swizzle,
   invalid_colorspace,
   invalid_format_flag,
   invalid_block_span,
   negative_block_padding,
   invalid_payload_compression,
   empty_texture,
   invalid_payload_offset,
   invalid_metadata_location,
   metadata_missing,
   file_too_small,
   not_enough_texture_data,
   image_unavailable,
   layered_non_array,
   not_enough_faces,
   too_many_faces,
   nonzero_reserved,
   not_enough_memory
};

bool is_valid(BetxReadError constant) noexcept;
const char* betx_read_error_name(BetxReadError constant) noexcept;
std::array<const BetxReadError, 46> betx_read_error_values() noexcept;
std::ostream& operator<<(std::ostream& os, BetxReadError constant);
bool is_fatal(BetxReadError constant) noexcept;
int texture_file_error_condition(BetxReadError constant) noexcept;
int generic_error_condition(BetxReadError constant) noexcept;
const char* read_error_msg(BetxReadError constant) noexcept;

} // be::gfx::tex::detail

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::detail::BetxReadError> {
   using type = ::be::gfx::tex::detail::BetxReadError;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 46;

   static bool is_valid(type value) {
      return ::be::gfx::tex::detail::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::detail::betx_read_error_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::detail::BetxReadError::not_a_mmm_binary_file,
         ::be::gfx::tex::detail::BetxReadError::not_a_betx_file,
         ::be::gfx::tex::detail::BetxReadError::crlf_corruption,
         ::be::gfx::tex::detail::BetxReadError::lf_corruption,
         ::be::gfx::tex::detail::BetxReadError::header_missing,
         ::be::gfx::tex::detail::BetxReadError::footer_missing,
         ::be::gfx::tex::detail::BetxReadError::invalid_endianness,
         ::be::gfx::tex::detail::BetxReadError::unsupported_file_version,
         ::be::gfx::tex::detail::BetxReadError::invalid_texture_class,
         ::be::gfx::tex::detail::BetxReadError::invalid_dimensions,
         ::be::gfx::tex::detail::BetxReadError::unsupported_dimensions,
         ::be::gfx::tex::detail::BetxReadError::invalid_layer_count,
         ::be::gfx::tex::detail::BetxReadError::unsupported_layer_count,
         ::be::gfx::tex::detail::BetxReadError::invalid_face_count,
         ::be::gfx::tex::detail::BetxReadError::unsupported_face_count,
         ::be::gfx::tex::detail::BetxReadError::invalid_level_count,
         ::be::gfx::tex::detail::BetxReadError::unsupported_level_count,
         ::be::gfx::tex::detail::BetxReadError::unnecessary_levels,
         ::be::gfx::tex::detail::BetxReadError::unsupported_alignment,
         ::be::gfx::tex::detail::BetxReadError::noncanonical_alignment,
         ::be::gfx::tex::detail::BetxReadError::invalid_block_packing,
         ::be::gfx::tex::detail::BetxReadError::invalid_block_dimensions,
         ::be::gfx::tex::detail::BetxReadError::unsupported_block_dimensions,
         ::be::gfx::tex::detail::BetxReadError::invalid_block_size,
         ::be::gfx::tex::detail::BetxReadError::unsupported_block_size,
         ::be::gfx::tex::detail::BetxReadError::invalid_field_type,
         ::be::gfx::tex::detail::BetxReadError::invalid_component_count,
         ::be::gfx::tex::detail::BetxReadError::too_many_components,
         ::be::gfx::tex::detail::BetxReadError::invalid_swizzle,
         ::be::gfx::tex::detail::BetxReadError::invalid_colorspace,
         ::be::gfx::tex::detail::BetxReadError::invalid_format_flag,
         ::be::gfx::tex::detail::BetxReadError::invalid_block_span,
         ::be::gfx::tex::detail::BetxReadError::negative_block_padding,
         ::be::gfx::tex::detail::BetxReadError::invalid_payload_compression,
         ::be::gfx::tex::detail::BetxReadError::empty_texture,
         ::be::gfx::tex::detail::BetxReadError::invalid_payload_offset,
         ::be::gfx::tex::detail::BetxReadError::invalid_metadata_location,
         ::be::gfx::tex::detail::BetxReadError::metadata_missing,
         ::be::gfx::tex::detail::BetxReadError::file_too_small,
         ::be::gfx::tex::detail::BetxReadError::not_enough_texture_data,
         ::be::gfx::tex::detail::BetxReadError::image_unavailable,
         ::be::gfx::tex::detail::BetxReadError::layered_non_array,
         ::be::gfx::tex::detail::BetxReadError::not_enough_faces,
         ::be::gfx::tex::detail::BetxReadError::too_many_faces,
         ::be::gfx::tex::detail::BetxReadError::nonzero_reserved,
         ::be::gfx::tex::detail::BetxReadError::not_enough_memory,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
class BetxReadErrorCategory : public std::error_category {
public:
   virtual const char* name() const noexcept { return "beTx Read Error"; }
   virtual S message(int condition) const;
   virtual bool equivalent(int code, const std::error_condition& condition) const noexcept;
};

const std::error_category& betx_read_error_category();
std::error_code make_error_code(BetxReadError e);
std::error_condition make_error_condition(BetxReadError e);

} // be::gfx::tex::detail

namespace std {

///////////////////////////////////////////////////////////////////////////////
template <>
struct is_error_code_enum<be::gfx::tex::detail::BetxReadError> : std::true_type { };

} // std

#endif
