#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/core/byte_order.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_bmp(const Buf<const UC>& buf) {
   if (buf.size() < 26) {
      return false;
   }
   
   constexpr UC signature[] = { 'B', 'M' };
   if (!util::file_signature_matches(buf, signature)) {
      return false;
   }

   U32 header_size;
   memcpy(&header_size, buf.get() + 0xE, sizeof(header_size));
   bo::static_to_host<bo::Little::value>(header_size);

   return header_size == 12 || header_size == 40 || header_size == 56 || header_size == 108 || header_size == 124;
}

} // be::gfx::tex::detail
