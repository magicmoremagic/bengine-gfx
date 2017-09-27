#pragma once
#ifndef BE_GFX_TEX_IMAGE_FORMAT_HPP_
#define BE_GFX_TEX_IMAGE_FORMAT_HPP_

#include "colorspace.hpp"
#include "block_packing.hpp"
#include "field_type.hpp"
#include "swizzle.hpp"
#include <be/core/glm.hpp>
#include <be/core/buf.hpp>
#include <be/core/enum_vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class ImageFormat final {
public:
   using block_size_type = U8;
   using block_dim_type = glm::vec<3, block_size_type>;
   using field_count_type = U8;
   using component_count_type = U8;

   static constexpr block_size_type max_block_size = block_size_type(-1);
   static constexpr block_size_type max_block_dim = block_size_type(-1);
   static constexpr field_count_type max_fields = field_count_type(4);
   static constexpr component_count_type max_components = component_count_type(-1);
   static constexpr component_count_type max_mapped_components = component_count_type(4);

   using field_types_type = enum_vec<max_fields, FieldType>;
   using swizzles_type = enum_vec<max_mapped_components, Swizzle>;

   ImageFormat();
   ImageFormat(std::size_t block_size, std::size_t block_dim, BlockPacking packing, glm::length_t components, field_types_type field_types, swizzles_type swizzles, Colorspace colorspace, bool premultiplied);
   ImageFormat(std::size_t block_size, block_dim_type block_dim, BlockPacking packing, glm::length_t components, field_types_type field_types, swizzles_type swizzles, Colorspace colorspace, bool premultiplied);

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

   ImageFormat& field_types(field_types_type types);
   field_types_type field_types() const;

   ImageFormat& field_type(glm::length_t field, FieldType type);
   FieldType field_type(glm::length_t field) const;

   ImageFormat& swizzles(swizzles_type mapping);
   swizzles_type swizzles() const;

   ImageFormat& swizzle(glm::length_t component, Swizzle mapping);
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
   field_types_type field_types_;
   swizzles_type swizzles_;
   Colorspace colorspace_;
   bool premultiplied_;
};

ImageFormat simple_format(ImageFormat format);

ImageFormat::field_types_type field_types(FieldType type, glm::length_t n_fields = 1);
ImageFormat::field_types_type field_types(FieldType type0, FieldType type1);
ImageFormat::field_types_type field_types(FieldType type0, FieldType type1, FieldType type2);
ImageFormat::field_types_type field_types(FieldType type0, FieldType type1, FieldType type2, FieldType type3);
ImageFormat::field_types_type field_types(std::initializer_list<FieldType> types);

ImageFormat::swizzles_type swizzles(Swizzle s0 = Swizzle::literal_zero, Swizzle s1 = Swizzle::literal_zero, Swizzle s2 = Swizzle::literal_zero, Swizzle s3 = Swizzle::literal_one);
ImageFormat::swizzles_type swizzles(std::initializer_list<Swizzle> mapping);
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
