#pragma once
#ifndef BE_GFX_IMAGE_FORMAT_HPP_
#define BE_GFX_IMAGE_FORMAT_HPP_

#include "swizzle.hpp"
#include "colorspace.hpp"
#include <be/core/glm.hpp>
#include <be/core/buf.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
class ImageFormat final {
public:
   using block_size_type = U8;
   using block_dim_type = glm::vec<3, block_size_type>;
   using bpc_vec_type = glm::vec<4, U8>;
   using swizzle_vec_type = glm::vec<4, U8>;
   
   static constexpr std::size_t max_block_size = std::size_t(block_size_type(-1)) + 1u;
   static constexpr std::size_t max_block_dim = std::size_t(block_size_type(-1)) + 1u;

   ImageFormat();
   ImageFormat(block_size_type block_size, block_dim_type block_dim, U8 components, bpc_vec_type bits, swizzle_vec_type swizzle, Colorspace colorspace);

   explicit operator bool() const;

   block_size_type block_size() const;
   block_dim_type block_dim() const;
   U8 components() const;
   bpc_vec_type bits() const;
   U8 bits(glm::length_t component) const;
   swizzle_vec_type swizzle() const;
   Swizzle swizzle(glm::length_t component) const;
   Colorspace colorspace() const;

private:
   block_size_type block_size_;
   block_dim_type block_dim_;
   U8 components_;
   bpc_vec_type bits_;
   swizzle_vec_type swizzle_;
   Colorspace colorspace_;
};

} // be::gfx

#endif
