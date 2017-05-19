#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_pic(const Buf<const UC>& buf) {
   constexpr UC signature1[] = { 0x53, 0x80, 0xf6, 0x34 };
   constexpr UC signature2[] = { 'P', 'I', 'C', 'T' };
   return util::file_signature_matches(buf, signature1) &&
      util::file_signature_matches<88>(buf, signature2);
}

} // be::gfx::tex::detail
