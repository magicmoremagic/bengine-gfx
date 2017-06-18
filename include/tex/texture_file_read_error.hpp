#pragma once
#ifndef BE_GFX_TEX_TEXTURE_FILE_READ_ERROR_HPP_
#define BE_GFX_TEX_TEXTURE_FILE_READ_ERROR_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/enum_traits.hpp>
#include <be/core/exceptions.hpp>

/*!! include 'tex/texture_file_read_error' !! 64 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class TextureFileReadError : U8 {
   none = 0,
   unsupported_file_format,
   unsupported_file_format_version,
   unsupported_texture,
   unsupported_texture_size,
   unknown_filesystem_error,
   file_not_found,
   file_not_readable,
   file_corruption,
   out_of_memory
};

bool is_valid(TextureFileReadError constant) noexcept;
const char* texture_file_read_error_name(TextureFileReadError constant) noexcept;
std::array<const TextureFileReadError, 10> texture_file_read_error_values() noexcept;
std::ostream& operator<<(std::ostream& os, TextureFileReadError constant);

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::TextureFileReadError> {
   using type = ::be::gfx::tex::TextureFileReadError;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 10;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::texture_file_read_error_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::TextureFileReadError::none,
         ::be::gfx::tex::TextureFileReadError::unsupported_file_format,
         ::be::gfx::tex::TextureFileReadError::unsupported_file_format_version,
         ::be::gfx::tex::TextureFileReadError::unsupported_texture,
         ::be::gfx::tex::TextureFileReadError::unsupported_texture_size,
         ::be::gfx::tex::TextureFileReadError::unknown_filesystem_error,
         ::be::gfx::tex::TextureFileReadError::file_not_found,
         ::be::gfx::tex::TextureFileReadError::file_not_readable,
         ::be::gfx::tex::TextureFileReadError::file_corruption,
         ::be::gfx::tex::TextureFileReadError::out_of_memory,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T ignore_error(std::pair<T, TextureFileReadError> result) {
   return std::move(result.first);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T default_on_error(std::pair<T, TextureFileReadError> result, T default_value) {
   if (result.second == TextureFileReadError::none) {
      return std::move(result.first);
   } else {
      return std::move(default_value);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T throw_on_error(std::pair<T, TextureFileReadError> result) {
   switch (result.second) {
      case TextureFileReadError::none:
         return std::move(result.first);
      default:
         throw Recoverable<>(texture_file_read_error_name(result.second));
   }
}

} // be::gfx::tex

#endif
