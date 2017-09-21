#include "pch.hpp"
#include "tex/swizzle.hpp"

/*!! include 'tex/swizzle' !! 80 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

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

///////////////////////////////////////////////////////////////////////////////
std::array<const Swizzle, 6> swizzle_values() noexcept {
   return ::be::EnumTraits<Swizzle>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, Swizzle constant) {
   if (is_valid(constant)) {
      os << swizzle_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
gl::AllEnums swizzle_to_gl(be::gfx::tex::Swizzle constant) noexcept {
   switch (constant) {
      case be::gfx::tex::Swizzle::zero:  return gl::AllEnums::GL_ZERO;
      case be::gfx::tex::Swizzle::one:   return gl::AllEnums::GL_ONE;
      case be::gfx::tex::Swizzle::red:   return gl::AllEnums::GL_RED;
      case be::gfx::tex::Swizzle::green: return gl::AllEnums::GL_GREEN;
      case be::gfx::tex::Swizzle::blue:  return gl::AllEnums::GL_BLUE;
      case be::gfx::tex::Swizzle::alpha: return gl::AllEnums::GL_ALPHA;
      default:
         return gl::AllEnums::GL_INVALID_VALUE;
   }
}

///////////////////////////////////////////////////////////////////////////////
be::gfx::tex::Swizzle swizzle_from_gl(gl::AllEnums constant) noexcept {
   switch (constant) {
      case gl::AllEnums::GL_ONE:           return be::gfx::tex::Swizzle::one;
      case gl::AllEnums::GL_RED:           return be::gfx::tex::Swizzle::red;
      case gl::AllEnums::GL_GREEN:         return be::gfx::tex::Swizzle::green;
      case gl::AllEnums::GL_BLUE:          return be::gfx::tex::Swizzle::blue;
      case gl::AllEnums::GL_ALPHA:         return be::gfx::tex::Swizzle::alpha;
      default:
         return be::gfx::tex::Swizzle::zero;
   }
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */
