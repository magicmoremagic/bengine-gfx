#include "pch.hpp"
#include "tex/texture_file_read_error.hpp"

/*!! include 'tex/texture_file_read_error' !! 61 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(TextureFileReadError constant) noexcept {
   switch (constant) {
      case TextureFileReadError::none:
      case TextureFileReadError::unsupported_file_format:
      case TextureFileReadError::unsupported_file_format_version:
      case TextureFileReadError::unsupported_texture:
      case TextureFileReadError::unsupported_texture_size:
      case TextureFileReadError::unknown_filesystem_error:
      case TextureFileReadError::file_not_found:
      case TextureFileReadError::file_not_readable:
      case TextureFileReadError::file_corruption:
      case TextureFileReadError::out_of_memory:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* texture_file_read_error_name(TextureFileReadError constant) noexcept {
   switch (constant) {
      case TextureFileReadError::none:                            return "none";
      case TextureFileReadError::unsupported_file_format:         return "unsupported_file_format";
      case TextureFileReadError::unsupported_file_format_version: return "unsupported_file_format_version";
      case TextureFileReadError::unsupported_texture:             return "unsupported_texture";
      case TextureFileReadError::unsupported_texture_size:        return "unsupported_texture_size";
      case TextureFileReadError::unknown_filesystem_error:        return "unknown_filesystem_error";
      case TextureFileReadError::file_not_found:                  return "file_not_found";
      case TextureFileReadError::file_not_readable:               return "file_not_readable";
      case TextureFileReadError::file_corruption:                 return "file_corruption";
      case TextureFileReadError::out_of_memory:                   return "out_of_memory";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const TextureFileReadError, 10> texture_file_read_error_values() noexcept {
   return ::be::EnumTraits<TextureFileReadError>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, TextureFileReadError constant) {
   if (is_valid(constant)) {
      os << texture_file_read_error_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */
