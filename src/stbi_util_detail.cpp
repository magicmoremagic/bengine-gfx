#include "pch.hpp"
//#include "stbi_util_detail.hpp"
//
//namespace be {
//namespace gfx {
//namespace detail {
//
/////////////////////////////////////////////////////////////////////////////////
//gli::format get_stbi_format(int channels, int bpc) {
//   gli::format format = gli::FORMAT_UNDEFINED;
//   if (bpc == 8) {
//      format = get_stbi_format_8(channels);
//   } else if (bpc == 16) {
//      format = get_stbi_format_16(channels);
//   } else if (bpc == 32) {
//      format = get_stbi_format_32(channels);
//   }
//   return format;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::format get_stbi_format_8(int channels) {
//   switch (channels) {
//      case 1:  return gli::FORMAT_R8_UNORM_PACK8;
//      case 2:  return gli::FORMAT_RG8_UNORM_PACK8;
//      case 3:  return gli::FORMAT_RGB8_UNORM_PACK8;
//      case 4:  return gli::FORMAT_RGBA8_UNORM_PACK8;
//      default: return gli::FORMAT_UNDEFINED;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::format get_stbi_format_16(int channels) {
//   switch (channels) {
//      case 1:  return gli::FORMAT_R16_UNORM_PACK16;
//      case 2:  return gli::FORMAT_RG16_UNORM_PACK16;
//      case 3:  return gli::FORMAT_RGB16_UNORM_PACK16;
//      case 4:  return gli::FORMAT_RGBA16_UNORM_PACK16;
//      default: return gli::FORMAT_UNDEFINED;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::format get_stbi_format_32(int channels) {
//   switch (channels) {
//      case 1:  return gli::FORMAT_R32_SFLOAT_PACK32;
//      case 2:  return gli::FORMAT_RG32_SFLOAT_PACK32;
//      case 3:  return gli::FORMAT_RGB32_SFLOAT_PACK32;
//      case 4:  return gli::FORMAT_RGBA32_SFLOAT_PACK32;
//      default: return gli::format::FORMAT_UNDEFINED;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//int get_stbi_format_channels(gli::format format, int bpc) {
//   if (bpc == 8) {
//      return get_stbi_format_8_channels(format);
//   } else if (bpc == 16) {
//      return get_stbi_format_16_channels(format);
//   } else if (bpc == 32) {
//      return get_stbi_format_32_channels(format);
//   }
//   return 0;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//int get_stbi_format_8_channels(gli::format format) {
//   switch (format) {
//      case gli::FORMAT_R8_UNORM_PACK8:
//      case gli::FORMAT_R8_SNORM_PACK8:
//      case gli::FORMAT_R8_USCALED_PACK8:
//      case gli::FORMAT_R8_SSCALED_PACK8:
//      case gli::FORMAT_R8_UINT_PACK8:
//      case gli::FORMAT_R8_SINT_PACK8:
//      case gli::FORMAT_R8_SRGB_PACK8:
//         return 1;
//      case gli::FORMAT_RG8_UNORM_PACK8:
//      case gli::FORMAT_RG8_SNORM_PACK8:
//      case gli::FORMAT_RG8_USCALED_PACK8:
//      case gli::FORMAT_RG8_SSCALED_PACK8:
//      case gli::FORMAT_RG8_UINT_PACK8:
//      case gli::FORMAT_RG8_SINT_PACK8:
//      case gli::FORMAT_RG8_SRGB_PACK8:
//         return 2;
//      case gli::FORMAT_RGB8_UNORM_PACK8:
//      case gli::FORMAT_RGB8_SNORM_PACK8:
//      case gli::FORMAT_RGB8_USCALED_PACK8:
//      case gli::FORMAT_RGB8_SSCALED_PACK8:
//      case gli::FORMAT_RGB8_UINT_PACK8:
//      case gli::FORMAT_RGB8_SINT_PACK8:
//      case gli::FORMAT_RGB8_SRGB_PACK8:
//         return 3;
//      case gli::FORMAT_RGBA8_UNORM_PACK8:
//      case gli::FORMAT_RGBA8_SNORM_PACK8:
//      case gli::FORMAT_RGBA8_USCALED_PACK8:
//      case gli::FORMAT_RGBA8_SSCALED_PACK8:
//      case gli::FORMAT_RGBA8_UINT_PACK8:
//      case gli::FORMAT_RGBA8_SINT_PACK8:
//      case gli::FORMAT_RGBA8_SRGB_PACK8:
//         return 4;
//      default: return 0;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//int get_stbi_format_16_channels(gli::format format) {
//   switch (format) {
//      case gli::FORMAT_R16_UNORM_PACK16:
//      case gli::FORMAT_R16_SNORM_PACK16:
//      case gli::FORMAT_R16_USCALED_PACK16:
//      case gli::FORMAT_R16_SSCALED_PACK16:
//      case gli::FORMAT_R16_UINT_PACK16:
//      case gli::FORMAT_R16_SINT_PACK16:
//         return 1;
//      case gli::FORMAT_RG16_UNORM_PACK16:
//      case gli::FORMAT_RG16_SNORM_PACK16:
//      case gli::FORMAT_RG16_USCALED_PACK16:
//      case gli::FORMAT_RG16_SSCALED_PACK16:
//      case gli::FORMAT_RG16_UINT_PACK16:
//      case gli::FORMAT_RG16_SINT_PACK16:
//         return 2;
//      case gli::FORMAT_RGB16_UNORM_PACK16:
//      case gli::FORMAT_RGB16_SNORM_PACK16:
//      case gli::FORMAT_RGB16_USCALED_PACK16:
//      case gli::FORMAT_RGB16_SSCALED_PACK16:
//      case gli::FORMAT_RGB16_UINT_PACK16:
//      case gli::FORMAT_RGB16_SINT_PACK16:
//         return 3;
//      case gli::FORMAT_RGBA16_UNORM_PACK16:
//      case gli::FORMAT_RGBA16_SNORM_PACK16:
//      case gli::FORMAT_RGBA16_USCALED_PACK16:
//      case gli::FORMAT_RGBA16_SSCALED_PACK16:
//      case gli::FORMAT_RGBA16_UINT_PACK16:
//      case gli::FORMAT_RGBA16_SINT_PACK16:
//         return 4;
//      default: return 0;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//int get_stbi_format_32_channels(gli::format format) {
//   switch (format) {
//      case gli::FORMAT_R32_SFLOAT_PACK32: return 1;
//      case gli::FORMAT_RG32_SFLOAT_PACK32: return 2;
//      case gli::FORMAT_RGB32_SFLOAT_PACK32: return 3;
//      case gli::FORMAT_RGBA32_SFLOAT_PACK32: return 4;
//      default: return 0;
//   }
//}
//
//} // be::gfx::detail
//} // be::gfx
//} // be
