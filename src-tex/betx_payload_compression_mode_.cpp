#include "pch.hpp"
#include "betx_payload_compression_mode_.hpp"

/*!! include 'tex/betx_payload_compression_mode' !! 45 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::betx::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(PayloadCompressionMode constant) noexcept {
   switch (constant) {
      case PayloadCompressionMode::none:
      case PayloadCompressionMode::zlib:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* payload_compression_mode_name(PayloadCompressionMode constant) noexcept {
   switch (constant) {
      case PayloadCompressionMode::none: return "none";
      case PayloadCompressionMode::zlib: return "zlib";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const PayloadCompressionMode, 2> payload_compression_mode_values() noexcept {
   return ::be::EnumTraits<PayloadCompressionMode>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, PayloadCompressionMode constant) {
   if (is_valid(constant)) {
      os << payload_compression_mode_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

} // be::gfx::tex::betx::detail


/* ######################### END OF GENERATED CODE ######################### */
