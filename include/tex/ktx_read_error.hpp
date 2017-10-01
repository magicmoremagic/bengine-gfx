#pragma once
#ifndef BE_GFX_TEX_KTX_READ_ERROR_HPP_
#define BE_GFX_TEX_KTX_READ_ERROR_HPP_

#include "tex/texture_file_error.hpp"
#include <be/core/enum_traits.hpp>

/*!! include 'tex/ktx_read_error' !! 94 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
enum class KtxReadError : U8 {
   not_a_ktx_file = 0,
   unsupported_file_version,
   file_corruption,
   header_missing,
   unsupported_endianness,
   unsupported_image_format,
   invalid_gl_type_size,
   invalid_texture_class,
   invalid_dimensions,
   unsupported_dimensions,
   unsupported_layer_count,
   invalid_face_count,
   unsupported_face_count,
   unsupported_level_count,
   unnecessary_levels,
   empty_texture,
   metadata_missing,
   not_enough_texture_data,
   image_unavailable,
   layered_non_array,
   not_enough_faces,
   too_many_faces,
   not_enough_memory
};

bool is_valid(KtxReadError constant) noexcept;
const char* ktx_read_error_name(KtxReadError constant) noexcept;
std::array<const KtxReadError, 23> ktx_read_error_values() noexcept;
std::ostream& operator<<(std::ostream& os, KtxReadError constant);
bool is_fatal(KtxReadError constant) noexcept;
int texture_file_error_condition(KtxReadError constant) noexcept;
int generic_error_condition(KtxReadError constant) noexcept;
const char* read_error_msg(KtxReadError constant) noexcept;

} // be::gfx::tex::detail

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::detail::KtxReadError> {
   using type = ::be::gfx::tex::detail::KtxReadError;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 23;

   static bool is_valid(type value) {
      return ::be::gfx::tex::detail::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::detail::ktx_read_error_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::detail::KtxReadError::not_a_ktx_file,
         ::be::gfx::tex::detail::KtxReadError::unsupported_file_version,
         ::be::gfx::tex::detail::KtxReadError::file_corruption,
         ::be::gfx::tex::detail::KtxReadError::header_missing,
         ::be::gfx::tex::detail::KtxReadError::unsupported_endianness,
         ::be::gfx::tex::detail::KtxReadError::unsupported_image_format,
         ::be::gfx::tex::detail::KtxReadError::invalid_gl_type_size,
         ::be::gfx::tex::detail::KtxReadError::invalid_texture_class,
         ::be::gfx::tex::detail::KtxReadError::invalid_dimensions,
         ::be::gfx::tex::detail::KtxReadError::unsupported_dimensions,
         ::be::gfx::tex::detail::KtxReadError::unsupported_layer_count,
         ::be::gfx::tex::detail::KtxReadError::invalid_face_count,
         ::be::gfx::tex::detail::KtxReadError::unsupported_face_count,
         ::be::gfx::tex::detail::KtxReadError::unsupported_level_count,
         ::be::gfx::tex::detail::KtxReadError::unnecessary_levels,
         ::be::gfx::tex::detail::KtxReadError::empty_texture,
         ::be::gfx::tex::detail::KtxReadError::metadata_missing,
         ::be::gfx::tex::detail::KtxReadError::not_enough_texture_data,
         ::be::gfx::tex::detail::KtxReadError::image_unavailable,
         ::be::gfx::tex::detail::KtxReadError::layered_non_array,
         ::be::gfx::tex::detail::KtxReadError::not_enough_faces,
         ::be::gfx::tex::detail::KtxReadError::too_many_faces,
         ::be::gfx::tex::detail::KtxReadError::not_enough_memory,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
class KtxReadErrorCategory : public std::error_category {
public:
   virtual const char* name() const noexcept { return "KTX Read Error"; }
   virtual S message(int condition) const;
   virtual bool equivalent(int code, const std::error_condition& condition) const noexcept;
};

const std::error_category& ktx_read_error_category();
std::error_code make_error_code(KtxReadError e);
std::error_condition make_error_condition(KtxReadError e);

} // be::gfx::tex::detail

namespace std {

///////////////////////////////////////////////////////////////////////////////
template <>
struct is_error_code_enum<be::gfx::tex::detail::KtxReadError> : std::true_type { };

} // std

#endif
