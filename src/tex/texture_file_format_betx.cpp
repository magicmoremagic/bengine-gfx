#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_betx(const Buf<const UC>& buf) {
   // #57c0 - magicmoremagic prefix
   // 'beTx' - canonical extension
   // #0D0A1A0A - see PNG signature rationale
   // #4FE939FD - idgen -f canonical -s 32 "beTx - bengine texture file format"
   constexpr UC signature[] = { 0x57, 0xc0, 'b', 'e', 'T', 'x', '\r', '\n', 0x1a, '\n', 0x4F, 0xE9, 0x39, 0xFD };
   return util::file_signature_matches(buf, signature);
}

} // be::gfx::tex::detail
