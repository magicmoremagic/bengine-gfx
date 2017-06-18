#pragma once
#ifndef BE_GFX_TEX_BETX_V1_HPP_
#define BE_GFX_TEX_BETX_V1_HPP_

#include "tex/block_packing.hpp"
#include "tex/component_type.hpp"
#include "tex/swizzle.hpp"
#include "tex/colorspace.hpp"
#include "tex/texture_class.hpp"
#include "tex/texture_file_read_error.hpp"
#include "betx_payload_compression_mode_.hpp"

namespace be::gfx::tex::betx::detail {

///////////////////////////////////////////////////////////////////////////////
BlockPacking get_block_packing_v1(U8 value, TextureFileReadError& error) {
   switch (value) {
      case 0x00: return BlockPacking::s_8;
      case 0x01: return BlockPacking::s_8_8;
      case 0x02: return BlockPacking::s_8_8_8;
      case 0x03: return BlockPacking::s_8_8_8_8;
      case 0x04: return BlockPacking::s_16;
      case 0x05: return BlockPacking::s_16_16;
      case 0x06: return BlockPacking::s_16_16_16;
      case 0x07: return BlockPacking::s_16_16_16_16;
      case 0x08: return BlockPacking::s_32;
      case 0x09: return BlockPacking::s_32_32;
      case 0x0A: return BlockPacking::s_32_32_32;
      case 0x0B: return BlockPacking::s_32_32_32_32;
      case 0x0C: return BlockPacking::s_64;
      case 0x0D: return BlockPacking::s_64_64;
      case 0x0E: return BlockPacking::s_64_64_64;
      case 0x0F: return BlockPacking::s_64_64_64_64;
      case 0x10: return BlockPacking::p_4_4;
      case 0x11: return BlockPacking::p_3_3_2;
      case 0x12: return BlockPacking::p_2_3_3;
      case 0x13: return BlockPacking::p_3_2_3;
      case 0x14: return BlockPacking::p_2_2_2_2;
      case 0x15: return BlockPacking::p_4_4_4_4;
      case 0x16: return BlockPacking::p_1_5_5_5;
      case 0x17: return BlockPacking::p_5_5_5_1;
      case 0x18: return BlockPacking::p_6_5_5;
      case 0x19: return BlockPacking::p_5_5_6;
      case 0x1A: return BlockPacking::p_5_6_5;
      case 0x1B: return BlockPacking::p_8_24;
      case 0x1C: return BlockPacking::p_24_8;
      case 0x1D: return BlockPacking::p_11_11_10;
      case 0x1E: return BlockPacking::p_10_11_11;
      case 0x1F: return BlockPacking::p_11_10_11;
      case 0x20: return BlockPacking::p_8_8_8_8;
      case 0x21: return BlockPacking::p_9_9_9_5;
      case 0x22: return BlockPacking::p_5_9_9_9;
      case 0x23: return BlockPacking::p_10_10_10_2;
      case 0x24: return BlockPacking::p_2_10_10_10;
      case 0x25: return BlockPacking::s_32_p_24_8;
      case 0x26: return BlockPacking::c_astc;
      case 0x27: return BlockPacking::c_bptc;
      case 0x28: return BlockPacking::c_etc1;
      case 0x29: return BlockPacking::c_etc2;
      case 0x2A: return BlockPacking::c_s3tc1;
      case 0x2B: return BlockPacking::c_s3tc2;
      case 0x2C: return BlockPacking::c_s3tc3;
      case 0x2D: return BlockPacking::c_rgtc1;
      case 0x2E: return BlockPacking::c_rgtc2;

      default:
         error = TextureFileReadError::file_corruption;
         return BlockPacking::s_8;
   }
}

///////////////////////////////////////////////////////////////////////////////
ComponentType get_component_type_v1(U8 value, TextureFileReadError& error) {
   switch (value) {
      case 0x0: return ComponentType::none;
      case 0x1: return ComponentType::unorm;
      case 0x2: return ComponentType::snorm;
      case 0x3: return ComponentType::uint;
      case 0x4: return ComponentType::sint;
      case 0x5: return ComponentType::ufloat;
      case 0x6: return ComponentType::sfloat;
      case 0x7: return ComponentType::expo;

      default:
         error = TextureFileReadError::file_corruption;
         return ComponentType::none;
   }
}

///////////////////////////////////////////////////////////////////////////////
Swizzle get_swizzle_v1(U8 value, TextureFileReadError& error) {
   switch (value) {
      case 0x0: return Swizzle::zero;
      case 0x1: return Swizzle::one;
      case 0x2: return Swizzle::red;
      case 0x3: return Swizzle::green;
      case 0x4: return Swizzle::blue;
      case 0x5: return Swizzle::alpha;

      default:
         error = TextureFileReadError::file_corruption;
         return Swizzle::zero;
   }
}

///////////////////////////////////////////////////////////////////////////////
Colorspace get_colorspace_v1(U8 value, TextureFileReadError& error) {
   switch (value) {
      case 0x00: return Colorspace::unknown;
      case 0x01: return Colorspace::linear_other;
      case 0x02: return Colorspace::linear_depth_stencil;
      case 0x03: return Colorspace::linear_depth;
      case 0x04: return Colorspace::linear_stencil;
      case 0x05: return Colorspace::bt709_linear_rgb;
      case 0x06: return Colorspace::bt709_linear_hsl;
      case 0x07: return Colorspace::bt709_linear_hsv;
      case 0x08: return Colorspace::bt709_linear_ycbcr;
      case 0x09: return Colorspace::bt709_rgb;
      case 0x0A: return Colorspace::bt709_hsl;
      case 0x0B: return Colorspace::bt709_hsv;
      case 0x0C: return Colorspace::bt709_ycbcr;
      case 0x0D: return Colorspace::srgb;
      case 0x0E: return Colorspace::srgb_hsl;
      case 0x0F: return Colorspace::srgb_hsv;
      case 0x10: return Colorspace::srgb_ycbcr;
      case 0x11: return Colorspace::cie_xyz;
      case 0x12: return Colorspace::cie_lab_d65;
      case 0x13: return Colorspace::cie_lchab_d65;
      case 0x14: return Colorspace::cie_luv_d65;
      case 0x15: return Colorspace::cie_lchuv_d65;
      case 0x16: return Colorspace::cie_xyy;

      default:
         error = TextureFileReadError::file_corruption;
         return Colorspace::unknown;
   }
}

///////////////////////////////////////////////////////////////////////////////
TextureClass get_texture_class_v1(U8 value, TextureFileReadError& error) {
   switch (value) {
      case 0x0: return TextureClass::lineal;
      case 0x1: return TextureClass::lineal_array;
      case 0x2: return TextureClass::planar;
      case 0x3: return TextureClass::planar_array;
      case 0x4: return TextureClass::volumetric;
      case 0x5: return TextureClass::volumetric_array;
      case 0x6: return TextureClass::directional;
      case 0x7: return TextureClass::directional_array;

      default:
         error = TextureFileReadError::file_corruption;
         return TextureClass::volumetric_array;
   }
}

///////////////////////////////////////////////////////////////////////////////
PayloadCompressionMode get_payload_compression_mode_v1(U8 value, TextureFileReadError& error) {
   switch (value) {
      case 0x0: return PayloadCompressionMode::none;
      case 0x1: return PayloadCompressionMode::zlib;

      default:
         error = TextureFileReadError::file_corruption;
         return PayloadCompressionMode::none;
   }
}

///////////////////////////////////////////////////////////////////////////////
TextureAlignment get_alignment_v1(const BeTxHeader& header) {
   return TextureAlignment(header.line_span_granularity,
                           header.plane_span_granularity,
                           header.level_span_granularity,
                           header.face_span_granularity,
                           header.layer_span_granularity);
}

} // be::gfx::tex::betx::detail

#endif
