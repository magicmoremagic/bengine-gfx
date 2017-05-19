#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_pnm(const Buf<const UC>& buf) {
   constexpr UC signature1[] = { 'P', '5' };
   constexpr UC signature2[] = { 'P', '6' };
   return util::file_signature_matches(buf, signature1) ||
      util::file_signature_matches(buf, signature2);
}

} // be::gfx::tex::detail
