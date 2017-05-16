#include "tex/pch.hpp"
#include "tex/texture_file_format.hpp"

/*!! include 'tex/texture_file_format' !! 71 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(TextureFileFormat constant) noexcept {
   switch (constant) {
      case TextureFileFormat::betx:
      case TextureFileFormat::glraw:
      case TextureFileFormat::ktx:
      case TextureFileFormat::kmg:
      case TextureFileFormat::dds:
      case TextureFileFormat::etc:
      case TextureFileFormat::png:
      case TextureFileFormat::tga:
      case TextureFileFormat::bmp:
      case TextureFileFormat::jpeg:
      case TextureFileFormat::hdr:
      case TextureFileFormat::pic:
      case TextureFileFormat::pnm:
      case TextureFileFormat::gif:
      case TextureFileFormat::psd:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* texture_file_format_name(TextureFileFormat constant) noexcept {
   switch (constant) {
      case TextureFileFormat::betx:  return "betx";
      case TextureFileFormat::glraw: return "glraw";
      case TextureFileFormat::ktx:   return "ktx";
      case TextureFileFormat::kmg:   return "kmg";
      case TextureFileFormat::dds:   return "dds";
      case TextureFileFormat::etc:   return "etc";
      case TextureFileFormat::png:   return "png";
      case TextureFileFormat::tga:   return "tga";
      case TextureFileFormat::bmp:   return "bmp";
      case TextureFileFormat::jpeg:  return "jpeg";
      case TextureFileFormat::hdr:   return "hdr";
      case TextureFileFormat::pic:   return "pic";
      case TextureFileFormat::pnm:   return "pnm";
      case TextureFileFormat::gif:   return "gif";
      case TextureFileFormat::psd:   return "psd";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const TextureFileFormat, 15> texture_file_format_values() noexcept {
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
