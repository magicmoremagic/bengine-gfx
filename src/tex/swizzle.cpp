#include "pch.hpp"
#include "swizzle.hpp"

namespace be::gfx {

/*!! include 'swizzle' !! 33 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
bool is_valid(Swizzle constant) noexcept {
   switch (constant) {
      case Swizzle::zero:
      case Swizzle::one:
      case Swizzle::red:
      case Swizzle::green:
      case Swizzle::blue:
      case Swizzle::alpha:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* swizzle_name(Swizzle constant) noexcept {
   switch (constant) {
      case Swizzle::zero:  return "zero";
      case Swizzle::one:   return "one";
      case Swizzle::red:   return "red";
      case Swizzle::green: return "green";
      case Swizzle::blue:  return "blue";
      case Swizzle::alpha: return "alpha";
      default:
         return "?";
   }
}

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx
