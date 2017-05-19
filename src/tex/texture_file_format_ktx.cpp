#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_ktx(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 0xAB, 'K', 'T', 'X', ' ', '1', '1', 0xBB, '\r', '\n', 0x1A, '\n'  };
   return util::file_signature_matches(buf, signature);
}

} // be::gfx::tex::detail
