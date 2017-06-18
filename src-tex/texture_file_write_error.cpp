#include "pch.hpp"
#include "tex/texture_file_write_error.hpp"

/*!! include 'tex/texture_file_write_error' !! 61 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(TextureFileWriteError constant) noexcept {
   switch (constant) {
      case TextureFileWriteError::none:
      case TextureFileWriteError::unsupported_texture:
      case TextureFileWriteError::unsupported_texture_class:
      case TextureFileWriteError::unsupported_texture_size:
      case TextureFileWriteError::mipmaps_not_supported:
      case TextureFileWriteError::unknown_filesystem_error:
      case TextureFileWriteError::failed_to_create_file:
      case TextureFileWriteError::file_not_writable:
      case TextureFileWriteError::disk_full:
      case TextureFileWriteError::out_of_memory:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* texture_file_write_error_name(TextureFileWriteError constant) noexcept {
   switch (constant) {
      case TextureFileWriteError::none:                      return "none";
      case TextureFileWriteError::unsupported_texture:       return "unsupported_texture";
      case TextureFileWriteError::unsupported_texture_class: return "unsupported_texture_class";
      case TextureFileWriteError::unsupported_texture_size:  return "unsupported_texture_size";
      case TextureFileWriteError::mipmaps_not_supported:     return "mipmaps_not_supported";
      case TextureFileWriteError::unknown_filesystem_error:  return "unknown_filesystem_error";
      case TextureFileWriteError::failed_to_create_file:     return "failed_to_create_file";
      case TextureFileWriteError::file_not_writable:         return "file_not_writable";
      case TextureFileWriteError::disk_full:                 return "disk_full";
      case TextureFileWriteError::out_of_memory:             return "out_of_memory";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const TextureFileWriteError, 10> texture_file_write_error_values() noexcept {
   return ::be::EnumTraits<TextureFileWriteError>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, TextureFileWriteError constant) {
   if (is_valid(constant)) {
      os << texture_file_write_error_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */
