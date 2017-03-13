#pragma once
#ifndef BE_GFX_IMAGE_BLOCK_PACKING_HPP_
#define BE_GFX_IMAGE_BLOCK_PACKING_HPP_

#include <be/core/be.hpp>

namespace be::gfx {

/*!! include 'image_block_packing' !! 510 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
enum class ImageBlockPacking : U8 {
   s_8 = 0,
   s_8_8,
   s_8_8_8,
   s_8_8_8_8,
   s_16,
   s_16_16,
   s_16_16_16,
   s_16_16_16_16,
   s_32,
   s_32_32,
   s_32_32_32,
   s_32_32_32_32,
   s_64,
   s_64_64,
   s_64_64_64,
   s_64_64_64_64,
   p_4_4,
   p_3_3_2,
   p_2_3_3,
   p_3_2_3,
   p_4_4_4_4,
   p_1_5_5_5,
   p_5_5_5_1,
   p_5_6_5,
   p_8_24,
   p_24_8,
   p_11_11_10,
   p_10_11_11,
   p_11_10_11,
   p_8_8_8_8,
   p_9_9_9_5,
   p_5_9_9_9,
   p_10_10_10_2,
   p_2_10_10_10,
   s_32_p_24_8,
   c_astc,
   c_atc,
   c_bptc,
   c_eac,
   c_etc1,
   c_etc2,
   c_pvrtc1,
   c_pvrtc2,
   c_s3tc1,
   c_s3tc2,
   c_s3tc3,
   c_s3tc4,
   c_s3tc5
};

bool is_valid(ImageBlockPacking constant);
const char* image_block_packing_name(ImageBlockPacking constant);
bool is_compressed(ImageBlockPacking constant);
bool is_packed(ImageBlockPacking constant);
U8 component_count(ImageBlockPacking constant);
U16 image_block_pixel_size(ImageBlockPacking constant);
U8 image_block_word_size(ImageBlockPacking constant);
U8 image_block_word_count(ImageBlockPacking constant);
U8 image_block_word_offset_0(ImageBlockPacking constant);
U8 image_block_word_offset_1(ImageBlockPacking constant);
U8 image_block_word_offset_2(ImageBlockPacking constant);
U8 image_block_word_offset_3(ImageBlockPacking constant);
U8 image_block_bit_offset_0(ImageBlockPacking constant);
U8 image_block_bit_offset_1(ImageBlockPacking constant);
U8 image_block_bit_offset_2(ImageBlockPacking constant);
U8 image_block_bit_offset_3(ImageBlockPacking constant);
U8 image_block_bit_width_0(ImageBlockPacking constant);
U8 image_block_bit_width_1(ImageBlockPacking constant);
U8 image_block_bit_width_2(ImageBlockPacking constant);
U8 image_block_bit_width_3(ImageBlockPacking constant);

template <ImageBlockPacking>
struct ImageBlockPackingInfo {
   using is_compressed = True;
   using is_packed = False;
   using unsigned_word_type = void;
   static constexpr U8 components = 0;
   static constexpr U8 word_size = 0;
   static constexpr U8 words = 0;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 0, 0, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_8> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U8;
   static constexpr U8 components = 1;
   static constexpr U8 word_size = 1;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 8, 0, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_8_8> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U8;
   static constexpr U8 components = 2;
   static constexpr U8 word_size = 1;
   static constexpr U8 words = 2;
   static constexpr U8 component_word_offset[4] = { 0, 1, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 8, 8, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_8_8_8> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U8;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 1;
   static constexpr U8 words = 3;
   static constexpr U8 component_word_offset[4] = { 0, 1, 2, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 8, 8, 8, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_8_8_8_8> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U8;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 1;
   static constexpr U8 words = 4;
   static constexpr U8 component_word_offset[4] = { 0, 1, 2, 3 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 8, 8, 8, 8 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_16> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U16;
   static constexpr U8 components = 1;
   static constexpr U8 word_size = 2;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 16, 0, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_16_16> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U16;
   static constexpr U8 components = 2;
   static constexpr U8 word_size = 2;
   static constexpr U8 words = 2;
   static constexpr U8 component_word_offset[4] = { 0, 1, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 16, 16, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_16_16_16> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U16;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 2;
   static constexpr U8 words = 3;
   static constexpr U8 component_word_offset[4] = { 0, 1, 2, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 16, 16, 16, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_16_16_16_16> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U16;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 2;
   static constexpr U8 words = 4;
   static constexpr U8 component_word_offset[4] = { 0, 1, 2, 3 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 16, 16, 16, 16 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_32> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U32;
   static constexpr U8 components = 1;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 32, 0, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_32_32> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U32;
   static constexpr U8 components = 2;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 2;
   static constexpr U8 component_word_offset[4] = { 0, 1, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 32, 32, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_32_32_32> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U32;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 3;
   static constexpr U8 component_word_offset[4] = { 0, 1, 2, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 32, 32, 32, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_32_32_32_32> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U32;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 4;
   static constexpr U8 component_word_offset[4] = { 0, 1, 2, 3 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 32, 32, 32, 32 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_64> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U64;
   static constexpr U8 components = 1;
   static constexpr U8 word_size = 8;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 64, 0, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_64_64> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U64;
   static constexpr U8 components = 2;
   static constexpr U8 word_size = 8;
   static constexpr U8 words = 2;
   static constexpr U8 component_word_offset[4] = { 0, 1, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 64, 64, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_64_64_64> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U64;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 8;
   static constexpr U8 words = 3;
   static constexpr U8 component_word_offset[4] = { 0, 1, 2, 0 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 64, 64, 64, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_64_64_64_64> {
   using is_compressed = False;
   using is_packed = False;
   using unsigned_word_type = U64;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 8;
   static constexpr U8 words = 4;
   static constexpr U8 component_word_offset[4] = { 0, 1, 2, 3 };
   static constexpr U8 component_bit_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 64, 64, 64, 64 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_4_4> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U8;
   static constexpr U8 components = 2;
   static constexpr U8 word_size = 1;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 4, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 4, 4, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_3_3_2> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U8;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 1;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 5, 2, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 3, 3, 2, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_2_3_3> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U8;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 1;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 6, 3, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 2, 3, 3, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_3_2_3> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U8;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 1;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 5, 3, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 3, 2, 3, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_4_4_4_4> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U16;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 2;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 12, 8, 4, 0 };
   static constexpr U8 component_bit_width[4] = { 4, 4, 4, 4 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_1_5_5_5> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U16;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 2;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 15, 10, 5, 0 };
   static constexpr U8 component_bit_width[4] = { 1, 5, 5, 5 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_5_5_5_1> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U16;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 2;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 11, 6, 1, 0 };
   static constexpr U8 component_bit_width[4] = { 5, 5, 5, 1 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_5_6_5> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U16;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 2;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 11, 5, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 5, 6, 5, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_8_24> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 2;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 24, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 8, 24, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_24_8> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 2;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 8, 0, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 24, 8, 0, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_11_11_10> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 21, 10, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 11, 11, 10, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_10_11_11> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 22, 11, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 10, 11, 11, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_11_10_11> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 21, 11, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 11, 10, 11, 0 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_8_8_8_8> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 24, 16, 8, 0 };
   static constexpr U8 component_bit_width[4] = { 8, 8, 8, 8 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_9_9_9_5> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 23, 14, 5, 0 };
   static constexpr U8 component_bit_width[4] = { 9, 9, 9, 5 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_5_9_9_9> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 27, 18, 9, 0 };
   static constexpr U8 component_bit_width[4] = { 5, 9, 9, 9 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_10_10_10_2> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 22, 12, 2, 0 };
   static constexpr U8 component_bit_width[4] = { 10, 10, 10, 2 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::p_2_10_10_10> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 4;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 1;
   static constexpr U8 component_word_offset[4] = { 0, 0, 0, 0 };
   static constexpr U8 component_bit_offset[4] = { 30, 20, 10, 0 };
   static constexpr U8 component_bit_width[4] = { 2, 10, 10, 10 };
};

template <> struct ImageBlockPackingInfo<ImageBlockPacking::s_32_p_24_8> {
   using is_compressed = False;
   using is_packed = True;
   using unsigned_word_type = U32;
   static constexpr U8 components = 3;
   static constexpr U8 word_size = 4;
   static constexpr U8 words = 2;
   static constexpr U8 component_word_offset[4] = { 0, 1, 1, 0 };
   static constexpr U8 component_bit_offset[4] = { 32, 8, 0, 0 };
   static constexpr U8 component_bit_width[4] = { 32, 24, 8, 0 };
};

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx

#endif
