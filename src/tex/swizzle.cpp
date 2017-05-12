#include "tex/pch.hpp"
#include "tex/swizzle.hpp"

namespace be::gfx::tex {

/*!! include 'tex/swizzle' !! 60 */
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

///////////////////////////////////////////////////////////////////////////////
gl::GLenum swizzle_to_gl(Swizzle constant) noexcept {
   switch (constant) {
      case Swizzle::zero:  return gl::GLenum::GL_ZERO;
      case Swizzle::one:   return gl::GLenum::GL_ONE;
      case Swizzle::red:   return gl::GLenum::GL_RED;
      case Swizzle::green: return gl::GLenum::GL_GREEN;
      case Swizzle::blue:  return gl::GLenum::GL_BLUE;
      case Swizzle::alpha: return gl::GLenum::GL_ALPHA;
      default:
         return gl::GLenum::GL_INVALID_VALUE;
   }
}

///////////////////////////////////////////////////////////////////////////////
Swizzle swizzle_from_gl(gl::GLenum constant) noexcept {
   switch (constant) {
      case gl::GLenum::GL_ONE:           return Swizzle::one;
      case gl::GLenum::GL_RED:           return Swizzle::red;
      case gl::GLenum::GL_GREEN:         return Swizzle::green;
      case gl::GLenum::GL_BLUE:          return Swizzle::blue;
      case gl::GLenum::GL_ALPHA:         return Swizzle::alpha;
      default:
         return Swizzle::zero;
   }
}

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx::tex
