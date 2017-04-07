#include "pch.hpp"
#include "mipmapping.hpp"
#include <glm/gtc/integer.hpp>
#include <be/core/alg.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(std::size_t dim) {
   return static_cast<U8>(glm::log2(dim) + 1u);
}

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(ivec1 dim) {
   return static_cast<U8>(glm::log2(max(0, dim.x)) + 1);
}

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(ivec2 dim) {
   return static_cast<U8>(glm::log2(max(0, max(dim.x, dim.y))) + 1);
}

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(ivec3 dim) {
   return static_cast<U8>(glm::log2(max(max(0, dim.x), max(dim.y, dim.z))) + 1);
}

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(uvec1 dim) {
   return static_cast<U8>(glm::log2(max(0u, dim.x)) + 1u);
}

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(uvec2 dim) {
   return static_cast<U8>(glm::log2(max(0u, max(dim.x, dim.y))) + 1u);
}

///////////////////////////////////////////////////////////////////////////////
U8 mipmap_levels(uvec3 dim) {
   return static_cast<U8>(glm::log2(max(max(0u, dim.x), max(dim.y, dim.z))) + 1u);
}

} // be::gfx
