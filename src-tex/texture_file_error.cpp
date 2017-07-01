#include "pch.hpp"
#include "tex/texture_file_error.hpp"

/*!! include 'tex/texture_file_error' !! 61 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(TextureFileError constant) noexcept {
   switch (constant) {
      case TextureFileError::corrupted:
      case TextureFileError::unsupported:
      case TextureFileError::image_unavailable:
      case TextureFileError::fatal_error:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* texture_file_error_name(TextureFileError constant) noexcept {
   switch (constant) {
      case TextureFileError::corrupted:         return "corrupted";
      case TextureFileError::unsupported:       return "unsupported";
      case TextureFileError::image_unavailable: return "image_unavailable";
      case TextureFileError::fatal_error:       return "fatal_error";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const TextureFileError, 4> texture_file_error_values() noexcept {
   return ::be::EnumTraits<TextureFileError>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, TextureFileError constant) {
   if (is_valid(constant)) {
      os << texture_file_error_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
const char* texture_file_error_msg(TextureFileError constant) noexcept {
   switch (constant) {
      case TextureFileError::corrupted:         return "Texture file data invalid or corrupted";
      case TextureFileError::unsupported:       return "Texture file unsupported";
      case TextureFileError::image_unavailable: return "The requested layer, face, or mipmap level is not present in the texture";
      case TextureFileError::fatal_error:       return "A fatal error occurred preventing the texture from being loaded";
      default:
         return "An unknown error occurred";
   }
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
S TextureFileErrorCategory::message(int condition) const {
   return texture_file_error_msg(static_cast<TextureFileError>(condition));
}

///////////////////////////////////////////////////////////////////////////////
const std::error_category& texture_file_error_category() {
   static TextureFileErrorCategory instance;
   return instance;
}

///////////////////////////////////////////////////////////////////////////////
std::error_code make_error_code(TextureFileError e) {
   return std::error_code(static_cast<int>(e), texture_file_error_category());
}

///////////////////////////////////////////////////////////////////////////////
std::error_condition make_error_condition(TextureFileError e) {
   return std::error_condition(static_cast<int>(e), texture_file_error_category());
}

} // be::gfx::tex
