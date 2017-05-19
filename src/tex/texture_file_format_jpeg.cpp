#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_jpeg(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 0xFF, 0xD8, 0xFF };
   return util::file_signature_matches(buf, signature);
}

} // be::gfx::tex::detail
