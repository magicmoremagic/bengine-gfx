#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_png(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n' };
   return util::file_signature_matches(buf, signature);
}

} // be::gfx::tex::detail
