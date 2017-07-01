#pragma once
#ifndef BE_GFX_TEX_TEXTURE_FILE_ERROR_HPP_
#define BE_GFX_TEX_TEXTURE_FILE_ERROR_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/enum_traits.hpp>

/*!! include 'tex/texture_file_error' !! 53 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class TextureFileError : U8 {
   corrupted = 1,
   unsupported,
   image_unavailable,
   fatal_error
};

bool is_valid(TextureFileError constant) noexcept;
const char* texture_file_error_name(TextureFileError constant) noexcept;
std::array<const TextureFileError, 4> texture_file_error_values() noexcept;
std::ostream& operator<<(std::ostream& os, TextureFileError constant);
const char* texture_file_error_msg(TextureFileError constant) noexcept;

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::TextureFileError> {
   using type = ::be::gfx::tex::TextureFileError;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 4;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::texture_file_error_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::TextureFileError::corrupted,
         ::be::gfx::tex::TextureFileError::unsupported,
         ::be::gfx::tex::TextureFileError::image_unavailable,
         ::be::gfx::tex::TextureFileError::fatal_error,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class TextureFileErrorCategory : public std::error_category {
public:
   virtual const char* name() const noexcept { return "Texture File Error"; }
   virtual S message(int condition) const;
};

const std::error_category& texture_file_error_category();
std::error_code make_error_code(TextureFileError e);
std::error_condition make_error_condition(TextureFileError e);

} // be::gfx::tex

namespace std {

///////////////////////////////////////////////////////////////////////////////
template <>
struct is_error_condition_enum<be::gfx::tex::TextureFileError> : std::true_type { };

} // std

#endif
