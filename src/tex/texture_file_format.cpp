#include "tex/pch.hpp"
#include "tex/texture_file_format.hpp"

/*!! include 'tex/texture_file_format' !! 69 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(TextureFileFormat constant) noexcept {
   switch (constant) {
      case TextureFileFormat::unknown:
      case TextureFileFormat::betx:
      case TextureFileFormat::ktx:
      case TextureFileFormat::png:
      case TextureFileFormat::glraw:
      case TextureFileFormat::dds:
      case TextureFileFormat::hdr:
      case TextureFileFormat::gif:
      case TextureFileFormat::pic:
      case TextureFileFormat::psd:
      case TextureFileFormat::jpeg:
      case TextureFileFormat::bmp:
      case TextureFileFormat::pnm:
      case TextureFileFormat::tga:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* texture_file_format_name(TextureFileFormat constant) noexcept {
   switch (constant) {
      case TextureFileFormat::unknown: return "unknown";
      case TextureFileFormat::betx:    return "betx";
      case TextureFileFormat::ktx:     return "ktx";
      case TextureFileFormat::png:     return "png";
      case TextureFileFormat::glraw:   return "glraw";
      case TextureFileFormat::dds:     return "dds";
      case TextureFileFormat::hdr:     return "hdr";
      case TextureFileFormat::gif:     return "gif";
      case TextureFileFormat::pic:     return "pic";
      case TextureFileFormat::psd:     return "psd";
      case TextureFileFormat::jpeg:    return "jpeg";
      case TextureFileFormat::bmp:     return "bmp";
      case TextureFileFormat::pnm:     return "pnm";
      case TextureFileFormat::tga:     return "tga";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const TextureFileFormat, 14> texture_file_format_values() noexcept {
   return ::be::EnumTraits<TextureFileFormat>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, TextureFileFormat constant) {
   if (is_valid(constant)) {
      os << texture_file_format_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */
