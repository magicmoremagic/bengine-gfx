#pragma once
#ifndef BE_GFX_TEX_BETX_HEADER_01_HPP_
#define BE_GFX_TEX_BETX_HEADER_01_HPP_

#include <be/core/byte_order.hpp>

namespace be::gfx::tex::detail {

struct BeTxHeader01 {
   U64 endianness;
   U64 image_buffer_size;
   U8 block_size;
   U8 block_dim[3];
   U8 packing;
   U8 components;
   U8 component_types[4];
   U8 swizzle[4];
   U8 colorspace;
   U8 flags;
   U8 reserved_a[3];
   U8 texture_class;
   I32 dim[3];
   U16 layers;
   U8 faces;
   U8 levels;
   U8 aligned_block_size;
   U8 line_alignment_type;
   U8 plane_alignment_type;
   U8 level_alignment_type;
   U8 face_alignment_type;
   U8 layer_alignment_type;
   U8 reserved_b[6];
};

} // be::gfx::tex::detail
namespace be::bo {

template <>
struct Converter<be::gfx::tex::detail::BeTxHeader01> : ConvertBase<be::gfx::tex::detail::BeTxHeader01> {
   using base::in_place;

   
   static void in_place(type& v, Little, Big) {
      
   }

   static void in_place(type& v, Big, Little) {
      static_to_v.endianness
   }

   static T convert(T v, Little, Big) { return static_cast<T>(BE_BSWAP_U16(v)); }
   static T convert(T v, Big, Little) { return static_cast<T>(BE_BSWAP_U16(v)); }
};

} // be::bo

#endif
