#pragma once
#ifndef BE_GFX_TEX_BETX_HEADER_HPP_
#define BE_GFX_TEX_BETX_HEADER_HPP_

#include "tex/texture_file_info.hpp"
#include <be/core/byte_order.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
struct BetxSignature {
   static constexpr UC full[] = { 0x57, 0xC0, 'M', 'M', 'b', 'e', 'T', 'x', '\r', '\n', 0x1a, '\n', 0x4F, 0xE9, 0x39, 0xFD };
   static constexpr UC mmm[] =  { 0x57, 0xC0, 'M', 'M' };
   static constexpr UC betx_a[] =                     { 'b', 'e', 'T', 'x' };
   static constexpr UC check[] =                                          { '\r', '\n', 0x1a, '\n' };
   static constexpr UC lflf[] =                                           { '\n', 0x1a, '\n' };
   static constexpr UC crcr[] =                                           { '\r', '\n', 0x1a, '\r', '\n' };
   static constexpr UC betx_b[] =                                                                 { 0x4F, 0xE9, 0x39, 0xFD };
   static constexpr UC footer[] = { 'b', 'e', 'T', 'x' };
};

///////////////////////////////////////////////////////////////////////////////
struct BetxHeader {
   U8 signature[sizeof(BetxSignature::full)];
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
   U8 line_alignment;
   U8 plane_alignment;
   U8 level_alignment;
   U8 face_alignment;
   U8 layer_alignment;
   U8 reserved;
   U8 payload_compression;
};

} // be::gfx::tex::detail
namespace be::bo {

///////////////////////////////////////////////////////////////////////////////
template <>
struct Converter<be::gfx::tex::detail::BetxHeader> : ConvertBase<be::gfx::tex::detail::BetxHeader> {
   using base::in_place;

   static void in_place(type& v, Little, Big) {
      static_to_big<Little::value>(v.layers);
      static_to_big<Little::value>(v.dim);
      static_to_big<Little::value>(v.payload_offset);
      static_to_big<Little::value>(v.payload_size);
   }

   static void in_place(type& v, Big, Little) {
      static_to_little<Big::value>(v.layers);
      static_to_little<Big::value>(v.dim);
      static_to_little<Big::value>(v.payload_offset);
      static_to_little<Big::value>(v.payload_size);
   }
};

} // be::bo

#endif
