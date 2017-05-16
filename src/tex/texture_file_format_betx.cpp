#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_betx(const Buf<const UC>& buf) {
   // TODO
   constexpr UC signature[] = { 0x57, 0xcf, 'b', 'e', 'T', 'x', '\r', '\n', 0x1a, '\n' };
   return util::file_signature_matches(buf, signature);
}

} // be::gfx::tex::detail
