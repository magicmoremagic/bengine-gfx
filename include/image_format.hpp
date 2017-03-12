#pragma once
#ifndef BE_GFX_IMAGE_FORMAT_HPP_
#define BE_GFX_IMAGE_FORMAT_HPP_

#include "swizzle.hpp"
#include "colorspace.hpp"
#include "image_block_packing.hpp"
#include "image_component_type.hpp"

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

   using ctype_vec_type = glm::vec<4, U8>;
   using swizzle_vec_type = glm::vec<4, U8>;
   
   static constexpr std::size_t max_block_size = std::size_t(block_size_type(-1)) + 1u;
   static constexpr std::size_t max_block_dim = std::size_t(block_size_type(-1)) + 1u;

   ImageFormat();
   ImageFormat(block_size_type block_size, block_dim_type block_dim, ImageBlockPacking packing, U8 components, ctype_vec_type component_types, swizzle_vec_type swizzle, Colorspace colorspace, bool premultiplied);

   explicit operator bool() const;

   ImageFormat& block_size(block_size_type size);
   block_size_type block_size() const;
   
   ImageFormat& block_dim(block_dim_type block_dim);
   block_dim_type block_dim() const;

   ImageFormat& components(U8 n_comps);
   U8 components() const;

   ImageFormat& packing(ImageBlockPacking value);
   ImageBlockPacking packing() const;

   ImageFormat& component_types(ctype_vec_type types);
   ctype_vec_type component_types() const;

   ImageFormat& component_type(glm::length_t component, ImageComponentType type);
   ImageComponentType component_type(glm::length_t component) const;

   ImageFormat& swizzle(swizzle_vec_type swizzle);
   swizzle_vec_type swizzle() const;

   ImageFormat& swizzle(glm::length_t component, Swizzle swizzle);
   Swizzle swizzle(glm::length_t component) const;

   ImageFormat& colorspace(Colorspace colorspace);
   Colorspace colorspace() const;

   ImageFormat& premultiplied(bool premultiplied);
   bool premultiplied() const;

   bool operator==(const ImageFormat& other) const;
   bool operator!=(const ImageFormat& other) const;

private:
   block_size_type block_size_;
   block_dim_type block_dim_;
   ImageBlockPacking packing_;
   U8 components_;
   ctype_vec_type component_types_;
   swizzle_vec_type swizzle_;
   Colorspace colorspace_;
   bool premultiplied_;
};

} // be::gfx

#endif
