#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_gif(const Buf<const UC>& buf) {
   constexpr UC signature1[] = { 'G', 'I', 'F', '8', '9', 'a' };
   constexpr UC signature2[] = { 'G', 'I', 'F', '8', '7', 'a' };
   return util::file_signature_matches(buf, signature1) ||
      util::file_signature_matches(buf, signature2);
}

} // be::gfx::tex::detail
