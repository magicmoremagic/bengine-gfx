#pragma once
#ifndef BE_GFX_CATCH_TOSTRING_HPP_
#define BE_GFX_CATCH_TOSTRING_HPP_

#include <glm/glm.hpp>
#include <be/core/glm.hpp>
#include <be/core/extents.hpp>
#include <sstream>
#include <iomanip>

namespace Catch {

inline std::string toString(const be::RGB& value) {
   std::ostringstream oss;
   oss << "rgb[ " << (int)value.r << ", " << (int)value.g << ", " << (int)value.b << " ]";
   return oss.str();
}

inline std::string toString(const be::RGBA& value) {
   std::ostringstream oss;
   oss << "rgba[ " << (int)value.r << ", " << (int)value.g << ", " << (int)value.b << ", " << (int)value.a << " ]";
   return oss.str();
}

inline std::string toString(const be::vec4& value) {
   std::ostringstream oss;
   oss << std::scientific << std::setprecision(12) << "vec4(" << value.r << ", " << value.g << ", " << value.b << ", " << value.a << ")";
   return oss.str();
}

inline std::string toString(const be::vec3& value) {
   std::ostringstream oss;
   oss << std::scientific << std::setprecision(12) << "vec3(" << value.r << ", " << value.g << ", " << value.b << ")";
   return oss.str();
}

inline std::string toString(const be::vec2& value) {
   std::ostringstream oss;
   oss << std::scientific << std::setprecision(12) << "vec2(" << value.r << ", " << value.g << ")";
   return oss.str();
}

inline std::string toString(const be::ivec4& value) {
   std::ostringstream oss;
   oss << std::scientific << std::setprecision(12) << "ivec4(" << value.x << ", " << value.y << ", " << value.z << ", " << value.w << ")";
   return oss.str();
}

inline std::string toString(const be::ivec3& value) {
   std::ostringstream oss;
   oss << std::scientific << std::setprecision(12) << "ivec3(" << value.x << ", " << value.y << ", " << value.z << ")";
   return oss.str();
}

inline std::string toString(const be::ivec2& value) {
   std::ostringstream oss;
   oss << std::scientific << std::setprecision(12) << "ivec2(" << value.x << ", " << value.y << ")";
   return oss.str();
}

inline std::string toString(const be::ibox& value) {
   std::ostringstream oss;
   oss << "ibox[ offset(" << value.offset.x << ", " << value.offset.y << ", " << value.offset.z
      << "), dim("    << value.dim.x << ", " << value.dim.y << ", " << value.dim.z << ") ]";
   return oss.str();
}

} // Catch

#include <catch/catch.hpp>

#endif
