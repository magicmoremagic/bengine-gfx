#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/core/byte_order.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
// TGA v2 detection is quite reliable, but v1 isn't, so this check should be considered unreliable overall
bool is_tga(const Buf<const UC>& buf) {
   if (buf.size() >= 44) {
      constexpr UC signature[] = { 'T', 'R', 'U', 'E', 'V', 'I', 'S', 'I', 'O', 'N', '-', 'X', 'F', 'I', 'L', 'E', '.', 0 };
      if (util::file_signature_matches(buf, buf.size() - sizeof(signature), signature)) {
         return true; // TGA v2
      }
   }

   if (buf.size() < 18) {
      return false;
   }

   U8 color_map_type = static_cast<U8>(buf[1]);
   if (color_map_type != 0 && color_map_type != 1) {
      // Technically 128-255 could be used in non-standard TGAs but we'll ignore those since there's no strong file signature.
      return false;
   }

   U8 image_type = static_cast<U8>(buf[2]);
   U8 base_image_type = image_type & 0xF7u; // remove RLE bit
   if (base_image_type != 1 && base_image_type != 2 && base_image_type != 3) {
      // ignore type 0 (no image data)
      return false;
   }

   return (static_cast<U8>(buf[17]) & 0xC0) == 0;
}

} // be::gfx::tex::detail
