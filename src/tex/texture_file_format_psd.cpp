#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_psd(const Buf<const UC>& buf) {
   constexpr UC signature[] = { '8', 'B', 'P', 'S' };
   return util::file_signature_matches(buf, signature);
}

} // be::gfx::tex::detail
