#pragma once
#ifndef BE_GFX_TEX_IMAGE_FORMAT_HPP_
#define BE_GFX_TEX_IMAGE_FORMAT_HPP_

#include "swizzle.hpp"
#include "colorspace.hpp"
#include "block_packing.hpp"
#include "component_type.hpp"
#include <be/core/glm.hpp>
#include <be/core/buf.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class ImageFormat final {
public:
   using block_size_type = U8;
   using block_dim_type = glm::vec<3, block_size_type>;
   using component_count_type = U8;

   static constexpr block_size_type max_block_size = block_size_type(-1);
   static constexpr block_size_type max_block_dim = block_size_type(-1);
   static constexpr component_count_type max_components = component_count_type(-1);
   static constexpr component_count_type max_typed_components = component_count_type(4);

   using component_types_type = glm::vec<max_typed_components, std::underlying_type_t<ComponentType>>;
   using swizzles_type = glm::vec<max_typed_components, std::underlying_type_t<Swizzle>>;

   ImageFormat();
   ImageFormat(std::size_t block_size, std::size_t block_dim, BlockPacking packing, glm::length_t components, component_types_type component_types, swizzles_type swizzles, Colorspace colorspace, bool premultiplied);
   ImageFormat(std::size_t block_size, block_dim_type block_dim, BlockPacking packing, glm::length_t components, component_types_type component_types, swizzles_type swizzles, Colorspace colorspace, bool premultiplied);

   explicit operator bool() const;

   ImageFormat& block_size(std::size_t size);
   block_size_type block_size() const;

   ImageFormat& block_dim(std::size_t block_dim);
   ImageFormat& block_dim(block_dim_type block_dim);
   block_dim_type block_dim() const;

   ImageFormat& components(glm::length_t n_comps);
   component_count_type components() const;

   ImageFormat& packing(BlockPacking value);
   BlockPacking packing() const;

   ImageFormat& component_types(component_types_type types);
   component_types_type component_types() const;

   ImageFormat& component_type(glm::length_t component, ComponentType type);
   ComponentType component_type(glm::length_t component) const;

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
   BlockPacking packing_;
   component_count_type components_;
   component_types_type component_types_;
   swizzles_type swizzle_;
   Colorspace colorspace_;
   bool premultiplied_;
};

ImageFormat simple_format(ImageFormat format);

ImageFormat::component_types_type component_types(ComponentType type, glm::length_t n_components = 1);
ImageFormat::component_types_type component_types(ComponentType type0, ComponentType type1);
ImageFormat::component_types_type component_types(ComponentType type0, ComponentType type1, ComponentType type2);
ImageFormat::component_types_type component_types(ComponentType type0, ComponentType type1, ComponentType type2, ComponentType type3);
ImageFormat::component_types_type component_types(std::initializer_list<ComponentType> types);

ImageFormat::swizzles_type swizzles(Swizzle s0 = Swizzle::zero, Swizzle s1 = Swizzle::zero, Swizzle s2 = Swizzle::zero, Swizzle s3 = Swizzle::one);
ImageFormat::swizzles_type swizzles(std::initializer_list<Swizzle> swizzles);
ImageFormat::swizzles_type swizzles_r();
ImageFormat::swizzles_type swizzles_rrr();
ImageFormat::swizzles_type swizzles_rg();
ImageFormat::swizzles_type swizzles_rgb();
ImageFormat::swizzles_type swizzles_bgr();
ImageFormat::swizzles_type swizzles_abg();
ImageFormat::swizzles_type swizzles_rgba();
ImageFormat::swizzles_type swizzles_bgra();
ImageFormat::swizzles_type swizzles_abgr();
ImageFormat::swizzles_type swizzles_argb();

} // be::gfx::tex

#endif
