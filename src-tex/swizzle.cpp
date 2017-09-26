#include "pch.hpp"
#include "tex/swizzle.hpp"

/*!! include 'tex/swizzle' !! 80 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(Swizzle constant) noexcept {
   switch (constant) {
      case Swizzle::field_zero:
      case Swizzle::field_one:
      case Swizzle::field_two:
      case Swizzle::field_three:
      case Swizzle::literal_zero:
      case Swizzle::literal_one:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* swizzle_name(Swizzle constant) noexcept {
   switch (constant) {
      case Swizzle::field_zero:   return "field_zero";
      case Swizzle::field_one:    return "field_one";
      case Swizzle::field_two:    return "field_two";
      case Swizzle::field_three:  return "field_three";
      case Swizzle::literal_zero: return "literal_zero";
      case Swizzle::literal_one:  return "literal_one";
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
      case be::gfx::tex::Swizzle::field_zero:   return gl::AllEnums::GL_RED;
      case be::gfx::tex::Swizzle::field_one:    return gl::AllEnums::GL_GREEN;
      case be::gfx::tex::Swizzle::field_two:    return gl::AllEnums::GL_BLUE;
      case be::gfx::tex::Swizzle::field_three:  return gl::AllEnums::GL_ALPHA;
      case be::gfx::tex::Swizzle::literal_zero: return gl::AllEnums::GL_ZERO;
      case be::gfx::tex::Swizzle::literal_one:  return gl::AllEnums::GL_ONE;
      default:
         return gl::AllEnums::GL_INVALID_VALUE;
   }
}

///////////////////////////////////////////////////////////////////////////////
be::gfx::tex::Swizzle swizzle_from_gl(gl::AllEnums constant) noexcept {
   switch (constant) {
      case gl::AllEnums::GL_RED:           return be::gfx::tex::Swizzle::field_zero;
      case gl::AllEnums::GL_GREEN:         return be::gfx::tex::Swizzle::field_one;
      case gl::AllEnums::GL_BLUE:          return be::gfx::tex::Swizzle::field_two;
      case gl::AllEnums::GL_ALPHA:         return be::gfx::tex::Swizzle::field_three;
      case gl::AllEnums::GL_ONE:           return be::gfx::tex::Swizzle::literal_one;
      default:
         return be::gfx::tex::Swizzle::literal_zero;
   }
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */
