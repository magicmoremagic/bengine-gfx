#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_hdr(const Buf<const UC>& buf) {
   constexpr UC signature1[] = { '#', '?', 'R', 'A', 'D', 'I', 'A', 'N', 'C', 'E', '\n' };
   constexpr UC signature2[] = { '#', '?', 'R', 'G', 'B', 'E', '\n' };
   return util::file_signature_matches(buf, signature1) ||
      util::file_signature_matches(buf, signature2);
}

} // be::gfx::tex::detail
