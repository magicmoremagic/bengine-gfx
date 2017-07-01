#include "pch.hpp"
#include "tex/betx_payload_compression_mode.hpp"

/*!! include 'tex/betx_payload_compression_mode' !! 45 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(BetxPayloadCompressionMode constant) noexcept {
   switch (constant) {
      case BetxPayloadCompressionMode::none:
      case BetxPayloadCompressionMode::zlib:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* betx_payload_compression_mode_name(BetxPayloadCompressionMode constant) noexcept {
   switch (constant) {
      case BetxPayloadCompressionMode::none: return "none";
      case BetxPayloadCompressionMode::zlib: return "zlib";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const BetxPayloadCompressionMode, 2> betx_payload_compression_mode_values() noexcept {
   return ::be::EnumTraits<BetxPayloadCompressionMode>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, BetxPayloadCompressionMode constant) {
   if (is_valid(constant)) {
      os << betx_payload_compression_mode_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

} // be::gfx::tex::detail


/* ######################### END OF GENERATED CODE ######################### */
