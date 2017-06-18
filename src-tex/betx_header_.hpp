#pragma once
#ifndef BE_GFX_TEX_BETX_HEADER_HPP_
#define BE_GFX_TEX_BETX_HEADER_HPP_

#include <be/core/byte_order.hpp>

namespace be::gfx::tex::betx::detail {

struct BeTxHeader {
   U8 signature[16];
   U8 version;
   U8 endianness;
   U8 texture_class;
   U8 metadata_location;
   U16 layers;
   U8 faces;
   U8 levels;
   I32 dim[3];
   U8 block_size;
   U8 block_dim[3];
   U8 block_packing;
   U8 components;
   U8 colorspace;
   U8 format_flags;
   U8 component_types[4];
   U8 swizzle[4];
   U32 payload_offset;
   U64 payload_size;
   U8 block_span;
   U8 line_span_granularity;
   U8 plane_span_granularity;
   U8 level_span_granularity;
   U8 face_span_granularity;
   U8 layer_span_granularity;
   U8 reserved;
   U8 payload_compression;
};

} // be::gfx::tex::betx::detail
namespace be::bo {

template <>
struct Converter<be::gfx::tex::betx::detail::BeTxHeader> : ConvertBase<be::gfx::tex::betx::detail::BeTxHeader> {
   using base::in_place;

   static void in_place(type& v, Little, Big) {
      static_to_big<Little::value>(v.layers);
      static_to_big<Little::value>(v.dim);
      static_to_big<Little::value>(v.payload_offset);
      static_to_big<Little::value>(v.payload_size);
   }

   static void in_place(type& v, Big, Little) {
      static_to_big<Little::value>(v.layers);
      static_to_big<Little::value>(v.dim);
      static_to_big<Little::value>(v.payload_offset);
      static_to_big<Little::value>(v.payload_size);
   }
};

} // be::bo

#endif
