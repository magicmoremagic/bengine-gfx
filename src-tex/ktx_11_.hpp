#pragma once
#ifndef BE_GFX_TEX_KTX_11_HPP_
#define BE_GFX_TEX_KTX_11_HPP_

#include "ktx_header_.hpp"
#include "tex/texture_class.hpp"

namespace be::gfx::tex::ktx::detail {

/////////////////////////////////////////////////////////////////////////////////
//TextureClass get_texture_class_v11(const KtxHeader& header, TextureFileReadError& error) {
//   U8 dimensionality;
//   if (header.pixel_depth > 0) {
//      dimensionality = 3;
//      if (header.pixel_height == 0) {
//         error = TextureFileReadError::file_corruption;
//      }
//   } else if (header.pixel_height > 0) {
//      dimensionality = 2;
//   } else {
//      dimensionality = 1;
//   }
//
//   if (header.pixel_width == 0) {
//      error = TextureFileReadError::file_corruption;
//   }
//
//   bool is_array = header.number_of_array_elements > 0;
//
//   if (header.number_of_faces > 1) {
//      if (dimensionality != 2) {
//         error = TextureFileReadError::file_corruption;
//      }
//      return is_array ? TextureClass::directional_array : TextureClass::directional;
//   } else switch (dimensionality) {
//      case 1:  return is_array ? TextureClass::lineal_array : TextureClass::lineal;
//      case 2:  return is_array ? TextureClass::planar_array : TextureClass::planar;
//      case 3:  return is_array ? TextureClass::volumetric_array : TextureClass::volumetric;
//      default:
//         error = TextureFileReadError::file_corruption;
//         return TextureClass::volumetric_array;
//   }
//}

/////////////////////////////////////////////////////////////////////////////////
//ImageFormatGl get_image_format_gl_v11(const KtxHeader& header, TextureFileReadError& error) {
//   using namespace gl;
//   ImageFormatGl result;
//   result.swizzle[0] = GL_RED;
//   result.swizzle[0] = GL_GREEN;
//   result.swizzle[0] = GL_BLUE;
//   result.swizzle[0] = GL_ALPHA;
//
//   int components = 4;
//   bool intensify = false;
//   bool alpha_only = false;
//
//   switch (header.gl_internal_format) {
//      case 0x80E0: // GL_BGR // TODO log warning
//      case 0x1907:   components = 3; result.internal_format = GL_RGB; break;
//      case 0x80E1: //GL_BGRA // TODO log warning
//      case 0x1908:   components = 4; result.internal_format = GL_RGBA; break;
//
//      case 0x8229:   components = 1; result.internal_format = GL_R8; break;
//      case 0x822B:   components = 2; result.internal_format = GL_RG8; break;
//      case 0x8051:   components = 3; result.internal_format = GL_RGB8; break;
//      case 0x93A1: //GL_BGRA8_EXT // TODO log warning
//      case 0x8058:   components = 4; result.internal_format = GL_RGBA8; break;
//      case 0x822A:   components = 1; result.internal_format = GL_R16; break;
//      case 0x822C:   components = 2; result.internal_format = GL_RG16; break;
//      case 0x8054:   components = 3; result.internal_format = GL_RGB16; break;
//      case 0x805B:   components = 4; result.internal_format = GL_RGBA16; break;
//      case 0x8F94:   components = 1; result.internal_format = GL_R8_SNORM; break;
//      case 0x8F95:   components = 2; result.internal_format = GL_RG8_SNORM; break;
//      case 0x8F96:   components = 3; result.internal_format = GL_RGB8_SNORM; break;
//      case 0x8F97:   components = 4; result.internal_format = GL_RGBA8_SNORM; break;
//      case 0x8F98:   components = 1; result.internal_format = GL_R16_SNORM; break;
//      case 0x8F99:   components = 2; result.internal_format = GL_RG16_SNORM; break;
//      case 0x8F9A:   components = 3; result.internal_format = GL_RGB16_SNORM; break;
//      case 0x8F9B:   components = 4; result.internal_format = GL_RGBA16_SNORM; break;
//      case 0x8232:   components = 1; result.internal_format = GL_R8UI; break;
//      case 0x8238:   components = 2; result.internal_format = GL_RG8UI; break;
//      case 0x8D7D:   components = 3; result.internal_format = GL_RGB8UI; break;
//      case 0x8D7C:   components = 4; result.internal_format = GL_RGBA8UI; break;
//      case 0x8234:   components = 1; result.internal_format = GL_R16UI; break;
//      case 0x823A:   components = 2; result.internal_format = GL_RG16UI; break;
//      case 0x8D77:   components = 3; result.internal_format = GL_RGB16UI; break;
//      case 0x8D76:   components = 4; result.internal_format = GL_RGBA16UI; break;
//      case 0x8236:   components = 1; result.internal_format = GL_R32UI; break;
//      case 0x823C:   components = 2; result.internal_format = GL_RG32UI; break;
//      case 0x8D71:   components = 3; result.internal_format = GL_RGB32UI; break;
//      case 0x8D70:   components = 4; result.internal_format = GL_RGBA32UI; break;
//      case 0x8231:   components = 1; result.internal_format = GL_R8I; break;
//      case 0x8237:   components = 2; result.internal_format = GL_RG8I; break;
//      case 0x8D8F:   components = 3; result.internal_format = GL_RGB8I; break;
//      case 0x8D8E:   components = 4; result.internal_format = GL_RGBA8I; break;
//      case 0x8233:   components = 1; result.internal_format = GL_R16I; break;
//      case 0x8239:   components = 2; result.internal_format = GL_RG16I; break;
//      case 0x8D89:   components = 3; result.internal_format = GL_RGB16I; break;
//      case 0x8D88:   components = 4; result.internal_format = GL_RGBA16I; break;
//      case 0x8235:   components = 1; result.internal_format = GL_R32I; break;
//      case 0x823B:   components = 2; result.internal_format = GL_RG32I; break;
//      case 0x8D83:   components = 3; result.internal_format = GL_RGB32I; break;
//      case 0x8D82:   components = 4; result.internal_format = GL_RGBA32I; break;
//      case 0x822D:   components = 1; result.internal_format = GL_R16F; break;
//      case 0x822F:   components = 2; result.internal_format = GL_RG16F; break;
//      case 0x881B:   components = 3; result.internal_format = GL_RGB16F; break;
//      case 0x881A:   components = 4; result.internal_format = GL_RGBA16F; break;
//      case 0x822E:   components = 1; result.internal_format = GL_R32F; break;
//      case 0x8230:   components = 2; result.internal_format = GL_RG32F; break;
//      case 0x8815:   components = 3; result.internal_format = GL_RGB32F; break;
//      case 0x8814:   components = 4; result.internal_format = GL_RGBA32F; break;
//      case 0x8C41:   components = 3; result.internal_format = GL_SRGB8; break;
//      case 0x8C43:   components = 4; result.internal_format = GL_SRGB8_ALPHA8; break;
//      case 0x8059:   components = 4; result.internal_format = GL_RGB10_A2; break;
//      case 0x906F:   components = 4; result.internal_format = GL_RGB10_A2UI; break;
//      case 0x8C3D:   components = 3; result.internal_format = GL_RGB9_E5; break;
//      case 0x8C3A:   components = 3; result.internal_format = GL_R11F_G11F_B10F; break;
//      case 0x2A10:   components = 3; result.internal_format = GL_R3_G3_B2; break;
//      case 0x8D62:   components = 3; result.internal_format = GL_RGB565; break;
//      case 0x8057:   components = 4; result.internal_format = GL_RGB5_A1; break;
//      case 0x8056:   components = 4; result.internal_format = GL_RGBA4; break;
//      case 0x8043:   components = 2; result.internal_format = GL_LUMINANCE4_ALPHA4; intensify = true; break;
//      case 0x8040:   components = 1; result.internal_format = GL_LUMINANCE8; intensify = true; break;
//      case 0x803C:   components = 1; result.internal_format = GL_ALPHA8; alpha_only = true; break;
//      case 0x8045:   components = 2; result.internal_format = GL_LUMINANCE8_ALPHA8; intensify = true; break;
//      case 0x8042:   components = 1; result.internal_format = GL_LUMINANCE16; intensify = true; break;
//      case 0x803E:   components = 1; result.internal_format = GL_ALPHA16; alpha_only = true; break;
//      case 0x8048:   components = 2; result.internal_format = GL_LUMINANCE16_ALPHA16; intensify = true; break;
//      case 0x81A5:   components = 1; result.internal_format = GL_DEPTH_COMPONENT16; break;
//      case 0x81A6:   components = 1; result.internal_format = GL_DEPTH_COMPONENT24; break;
//      case 0x88F0:   components = 2; result.internal_format = GL_DEPTH24_STENCIL8; break;
//      case 0x81A7:   components = 1; result.internal_format = GL_DEPTH_COMPONENT32; break;
//      case 0x8CAC:   components = 1; result.internal_format = GL_DEPTH_COMPONENT32F; break;
//      case 0x8CAD:   components = 2; result.internal_format = GL_DEPTH32F_STENCIL8; break;
//      case 0x8D48:   components = 1; result.internal_format = GL_STENCIL_INDEX8; break;
//      case 0x83F0:   components = 3; result.internal_format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT; break;
//      case 0x83F1:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
//      case 0x83F2:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
//      case 0x83F3:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
//      case 0x8DBB:   components = 1; result.internal_format = GL_COMPRESSED_RED_RGTC1; break;
//      case 0x8DBC:   components = 1; result.internal_format = GL_COMPRESSED_SIGNED_RED_RGTC1; break;
//      case 0x8DBD:   components = 2; result.internal_format = GL_COMPRESSED_RG_RGTC2; break;
//      case 0x8DBE:   components = 2; result.internal_format = GL_COMPRESSED_SIGNED_RG_RGTC2; break;
//      case 0x8E8F:   components = 3; result.internal_format = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT; break;
//      case 0x8E8E:   components = 3; result.internal_format = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT; break;
//      case 0x8E8C:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_BPTC_UNORM; break;
//      case 0x9274:   components = 3; result.internal_format = GL_COMPRESSED_RGB8_ETC2; break;
//      case 0x9276:   components = 4; result.internal_format = GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2; break;
//      case 0x9278:   components = 4; result.internal_format = GL_COMPRESSED_RGBA8_ETC2_EAC; break;
//      case 0x9270:   components = 1; result.internal_format = GL_COMPRESSED_R11_EAC; break;
//      case 0x9271:   components = 1; result.internal_format = GL_COMPRESSED_SIGNED_R11_EAC; break;
//      case 0x9272:   components = 2; result.internal_format = GL_COMPRESSED_RG11_EAC; break;
//      case 0x9273:   components = 2; result.internal_format = GL_COMPRESSED_SIGNED_RG11_EAC; break;
//      case 0x93B0:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_4x4_KHR; break;
//      case 0x93B1:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_5x4_KHR; break;
//      case 0x93B2:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_5x5_KHR; break;
//      case 0x93B3:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_6x5_KHR; break;
//      case 0x93B4:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_6x6_KHR; break;
//      case 0x93B5:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_8x5_KHR; break;
//      case 0x93B6:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_8x6_KHR; break;
//      case 0x93B7:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_8x8_KHR; break;
//      case 0x93B8:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_10x5_KHR; break;
//      case 0x93B9:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_10x6_KHR; break;
//      case 0x93BA:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_10x8_KHR; break;
//      case 0x93BB:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_10x10_KHR; break;
//      case 0x93BC:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_12x10_KHR; break;
//      case 0x93BD:   components = 4; result.internal_format = GL_COMPRESSED_RGBA_ASTC_12x12_KHR; break;
//      case 0x8C4C:   components = 3; result.internal_format = GL_COMPRESSED_SRGB_S3TC_DXT1_EXT; break;
//      case 0x8C4D:   components = 4; result.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT; break;
//      case 0x8C4E:   components = 4; result.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT; break;
//      case 0x8C4F:   components = 4; result.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT; break;
//      case 0x8E8D:   components = 4; result.internal_format = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM; break;
//      case 0x9275:   components = 3; result.internal_format = GL_COMPRESSED_SRGB8_ETC2; break;
//      case 0x9277:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2; break;
//      case 0x9279:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC; break;
//      case 0x93D0:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR; break;
//      case 0x93D1:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR; break;
//      case 0x93D2:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR; break;
//      case 0x93D3:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR; break;
//      case 0x93D4:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR; break;
//      case 0x93D5:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR; break;
//      case 0x93D6:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR; break;
//      case 0x93D7:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR; break;
//      case 0x93D8:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR; break;
//      case 0x93D9:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR; break;
//      case 0x93DA:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR; break;
//      case 0x93DB:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR; break;
//      case 0x93DC:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR; break;
//      case 0x93DD:   components = 4; result.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR; break;
//   }
//
//   return result;
//}

} // be::gfx::tex::ktx::detail

#endif
