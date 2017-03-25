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

   using component_types_type = glm::vec<4, U8>;
   using swizzles_type = glm::vec<4, U8>;
   
   static constexpr std::size_t max_block_size = std::size_t(block_size_type(-1)) + 1u;
   static constexpr std::size_t max_block_dim = std::size_t(block_size_type(-1)) + 1u;

   ImageFormat();
   ImageFormat(block_size_type block_size, block_size_type block_dim, ImageBlockPacking packing, U8 components, component_types_type component_types, swizzles_type swizzles, Colorspace colorspace, bool premultiplied);
   ImageFormat(block_size_type block_size, block_dim_type block_dim, ImageBlockPacking packing, U8 components, component_types_type component_types, swizzles_type swizzles, Colorspace colorspace, bool premultiplied);

   explicit operator bool() const;

   ImageFormat& block_size(block_size_type size);
   block_size_type block_size() const;
   
   ImageFormat& block_dim(block_size_type block_dim);
   ImageFormat& block_dim(block_dim_type block_dim);
   block_dim_type block_dim() const;

   ImageFormat& components(U8 n_comps);
   U8 components() const;

   ImageFormat& packing(ImageBlockPacking value);
   ImageBlockPacking packing() const;

   ImageFormat& component_types(component_types_type types);
   component_types_type component_types() const;

   ImageFormat& component_type(glm::length_t component, ImageComponentType type);
   ImageComponentType component_type(glm::length_t component) const;

   ImageFormat& swizzles(swizzles_type swizzle);
   swizzles_type swizzles() const;

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
   component_types_type component_types_;
   swizzles_type swizzle_;
   Colorspace colorspace_;
   bool premultiplied_;
};

ImageFormat::component_types_type component_types(ImageComponentType type, glm::length_t n_components = 1);
ImageFormat::component_types_type component_types(ImageComponentType type0, ImageComponentType type1);
ImageFormat::component_types_type component_types(ImageComponentType type0, ImageComponentType type1, ImageComponentType type2);
ImageFormat::component_types_type component_types(ImageComponentType type0, ImageComponentType type1, ImageComponentType type2, ImageComponentType type3);
ImageFormat::component_types_type component_types(std::initializer_list<ImageComponentType> types);

ImageFormat::swizzles_type swizzles(Swizzle s0 = Swizzle::zero, Swizzle s1 = Swizzle::zero, Swizzle s2 = Swizzle::zero, Swizzle s3 = Swizzle::one);
ImageFormat::swizzles_type swizzles(std::initializer_list<Swizzle> swizzles);
ImageFormat::swizzles_type swizzles_r();
ImageFormat::swizzles_type swizzles_zzzr();
ImageFormat::swizzles_type swizzles_rrr();
ImageFormat::swizzles_type swizzles_rg();
ImageFormat::swizzles_type swizzles_rzzg();
ImageFormat::swizzles_type swizzles_rrrg();
ImageFormat::swizzles_type swizzles_rgb();
ImageFormat::swizzles_type swizzles_bgr();
ImageFormat::swizzles_type swizzles_rgba();
ImageFormat::swizzles_type swizzles_bgra();

} // be::gfx

#endif
