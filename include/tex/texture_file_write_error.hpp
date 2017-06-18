#pragma once
#ifndef BE_GFX_TEX_TEXTURE_FILE_WRITE_ERROR_HPP_
#define BE_GFX_TEX_TEXTURE_FILE_WRITE_ERROR_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/enum_traits.hpp>
#include <be/core/exceptions.hpp>

/*!! include 'tex/texture_file_write_error' !! 64 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class TextureFileWriteError : U8 {
   none = 0,
   unsupported_texture,
   unsupported_texture_class,
   unsupported_texture_size,
   mipmaps_not_supported,
   unknown_filesystem_error,
   failed_to_create_file,
   file_not_writable,
   disk_full,
   out_of_memory
};

bool is_valid(TextureFileWriteError constant) noexcept;
const char* texture_file_write_error_name(TextureFileWriteError constant) noexcept;
std::array<const TextureFileWriteError, 10> texture_file_write_error_values() noexcept;
std::ostream& operator<<(std::ostream& os, TextureFileWriteError constant);

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::TextureFileWriteError> {
   using type = ::be::gfx::tex::TextureFileWriteError;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 10;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::texture_file_write_error_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::TextureFileWriteError::none,
         ::be::gfx::tex::TextureFileWriteError::unsupported_texture,
         ::be::gfx::tex::TextureFileWriteError::unsupported_texture_class,
         ::be::gfx::tex::TextureFileWriteError::unsupported_texture_size,
         ::be::gfx::tex::TextureFileWriteError::mipmaps_not_supported,
         ::be::gfx::tex::TextureFileWriteError::unknown_filesystem_error,
         ::be::gfx::tex::TextureFileWriteError::failed_to_create_file,
         ::be::gfx::tex::TextureFileWriteError::file_not_writable,
         ::be::gfx::tex::TextureFileWriteError::disk_full,
         ::be::gfx::tex::TextureFileWriteError::out_of_memory,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T ignore_error(std::pair<T, TextureFileWriteError> result) {
   return std::move(result.first);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T default_on_error(std::pair<T, TextureFileWriteError> result, T default_value) {
   if (result.second == TextureFileWriteError::none) {
      return std::move(result.first);
   } else {
      return std::move(default_value);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T throw_on_error(std::pair<T, TextureFileWriteError> result) {
   switch (result.second) {
      case TextureFileWriteError::none:
         return std::move(result.first);
      default:
         throw Recoverable<>(texture_file_write_error_name(result.second));
   }
}

} // be::gfx::tex

#endif
