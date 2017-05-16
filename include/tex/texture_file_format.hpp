#pragma once
#ifndef BE_GFX_TEX_TEXTURE_FILE_FORMAT_HPP_
#define BE_GFX_TEX_TEXTURE_FILE_FORMAT_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/enum_traits.hpp>

/*!! include 'tex/texture_file_format' !! 74 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class TextureFileFormat : U8 {
   betx = 0,
   glraw,
   ktx,
   kmg,
   dds,
   etc,
   png,
   tga,
   bmp,
   jpeg,
   hdr,
   pic,
   pnm,
   gif,
   psd
};

bool is_valid(TextureFileFormat constant) noexcept;
const char* texture_file_format_name(TextureFileFormat constant) noexcept;
std::array<const TextureFileFormat, 15> texture_file_format_values() noexcept;
std::ostream& operator<<(std::ostream& os, TextureFileFormat constant);

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::TextureFileFormat> {
   using type = ::be::gfx::tex::TextureFileFormat;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 15;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::texture_file_format_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::TextureFileFormat::betx,
         ::be::gfx::tex::TextureFileFormat::glraw,
         ::be::gfx::tex::TextureFileFormat::ktx,
         ::be::gfx::tex::TextureFileFormat::kmg,
         ::be::gfx::tex::TextureFileFormat::dds,
         ::be::gfx::tex::TextureFileFormat::etc,
         ::be::gfx::tex::TextureFileFormat::png,
         ::be::gfx::tex::TextureFileFormat::tga,
         ::be::gfx::tex::TextureFileFormat::bmp,
         ::be::gfx::tex::TextureFileFormat::jpeg,
         ::be::gfx::tex::TextureFileFormat::hdr,
         ::be::gfx::tex::TextureFileFormat::pic,
         ::be::gfx::tex::TextureFileFormat::pnm,
         ::be::gfx::tex::TextureFileFormat::gif,
         ::be::gfx::tex::TextureFileFormat::psd,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
