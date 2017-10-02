#pragma once
#ifndef BE_GFX_TEX_BETX_HEADER_HPP_
#define BE_GFX_TEX_BETX_HEADER_HPP_

#include <be/core/byte_order.hpp>

namespace be::gfx::tex::detail {

//////////////////////////////////////////////////////////////////////////////
struct KtxSignature {
   static constexpr UC initial[] = { 0xAB, 'K', 'T', 'X', ' ' };
   static constexpr UC version[] = { 0xAB, 'K', 'T', 'X', ' ', '1', '1' };
   static constexpr UC full[] =    { 0xAB, 'K', 'T', 'X', ' ', '1', '1', 0xBB, '\r', '\n', 0x1A, '\n' };
};

//////////////////////////////////////////////////////////////////////////////
struct KtxHeader {
   U8 signature[12];
   U32 endianness;
   U32 gl_type;
   U32 gl_type_size;
   U32 gl_format;
   U32 gl_internal_format;
   U32 gl_base_internal_format;
   U32 pixel_width;
   U32 pixel_height;
   U32 pixel_depth;
   U32 number_of_array_elements;
   U32 number_of_faces;
   U32 number_of_mipmap_levels;
   U32 bytes_of_key_value_data;
};

} // be::gfx::tex::detail
namespace be::bo {

//////////////////////////////////////////////////////////////////////////////
template <>
struct Converter<be::gfx::tex::detail::KtxHeader> : ConvertBase<be::gfx::tex::detail::KtxHeader> {
   using ConvertBase<be::gfx::tex::detail::KtxHeader>::in_place;

   static void in_place(type& v, Little, Big) {
      if (v.endianness == 0x04030201) {
         return;
      }

      static_to_big<Little::value>(v.endianness);
      static_to_big<Little::value>(v.gl_type);
      static_to_big<Little::value>(v.gl_type_size);
      static_to_big<Little::value>(v.gl_format);
      static_to_big<Little::value>(v.gl_internal_format);
      static_to_big<Little::value>(v.gl_base_internal_format);
      static_to_big<Little::value>(v.pixel_width);
      static_to_big<Little::value>(v.pixel_height);
      static_to_big<Little::value>(v.pixel_depth);
      static_to_big<Little::value>(v.number_of_array_elements);
      static_to_big<Little::value>(v.number_of_faces);
      static_to_big<Little::value>(v.number_of_mipmap_levels);
      static_to_big<Little::value>(v.bytes_of_key_value_data);
   }

   static void in_place(type& v, Big, Little) {
      if (v.endianness == 0x04030201) {
         return;
      }

      static_to_little<Big::value>(v.endianness);
      static_to_little<Big::value>(v.gl_type);
      static_to_little<Big::value>(v.gl_type_size);
      static_to_little<Big::value>(v.gl_format);
      static_to_little<Big::value>(v.gl_internal_format);
      static_to_little<Big::value>(v.gl_base_internal_format);
      static_to_little<Big::value>(v.pixel_width);
      static_to_little<Big::value>(v.pixel_height);
      static_to_little<Big::value>(v.pixel_depth);
      static_to_little<Big::value>(v.number_of_array_elements);
      static_to_little<Big::value>(v.number_of_faces);
      static_to_little<Big::value>(v.number_of_mipmap_levels);
      static_to_little<Big::value>(v.bytes_of_key_value_data);
   }
};

} // be::bo

#endif
