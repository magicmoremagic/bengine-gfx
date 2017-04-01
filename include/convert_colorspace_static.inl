#if !defined(BE_GFX_CONVERT_COLORSPACE_STATIC_HPP_) && !defined(DOXYGEN)
#include "convert_colorspace_static.hpp"
#elif !defined(BE_GFX_CONVERT_COLORSPACE_STATIC_INL_)
#define BE_GFX_CONVERT_COLORSPACE_STATIC_INL_

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <Colorspace S>
using ColorspaceType = std::integral_constant<Colorspace, S>;

///////////////////////////////////////////////////////////////////////////////
template <ColorspaceFamily F>
using ColorspaceFamilyType = std::integral_constant<ColorspaceFamily, F>;

///////////////////////////////////////////////////////////////////////////////
template <ColorspaceVariant V>
using ColorspaceVariantType = std::integral_constant<ColorspaceVariant, V>;

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output,
   bool Same = std::is_same_v<Input, Output>,
   typename InputFamily = ColorspaceFamilyType<ColorspaceInfo<Input::value>::family>,
   typename OutputFamily = ColorspaceFamilyType<ColorspaceInfo<Output::value>::family>,
   typename InputVariant = ColorspaceVariantType<ColorspaceInfo<Input::value>::variant>,
   typename OutputVariant = ColorspaceVariantType<ColorspaceInfo<Output::value>::variant>>
struct convert_colorspace {
   static vec4 convert(vec4 pixel_norm) {
      using InputBase = ColorspaceType<ColorspaceFamilyInfo<InputFamily::value>::base>;
      using OutputBase = ColorspaceType<ColorspaceFamilyInfo<OutputFamily::value>::base>;
      pixel_norm = convert_colorspace<Input, InputBase>::convert(pixel_norm);
      pixel_norm = convert_colorspace<InputBase, OutputBase>::convert(pixel_norm);
      pixel_norm = convert_colorspace<OutputBase, Output>::convert(pixel_norm);
      return pixel_norm;
   }
};

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_nop {
   static vec4 convert(vec4 pixel_norm) {
      return pixel_norm;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename S>
struct convert_colorspace<S, S, true> : convert_colorspace_nop { };

#pragma region RGB <--> HSL/HSV

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_hsl_to_hsv {
   static vec4 convert(vec4 hsl) {
      F32 s = hsl.y * (hsl.z <= 0.5f ? hsl.z : 1.f - hsl.z);
      F32 v = hsl.z + s;
      s = v <= 0.f ? 0.f : 2.f * s / v;
      return vec4(hsl.x, s, v, hsl.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_hsv_to_hsl {
   static vec4 convert(vec4 hsv) {
      F32 l = hsv.z * (2.f - hsv.y);
      F32 s;
      if (l <= 0.f || l >= 2.f) {
         s = 0.f;
      } else {
         s = hsv.y * hsv.z / (l <= 1.f ? l : 2.f - l);
      }

      l *= 0.5;

      return vec4(hsv.x, s, l, hsv.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_none_to_hsv {
   static vec4 convert(vec4 pixel_norm) {
      F32 h = 0, s, v, m, d;

      v = std::max(std::max(pixel_norm.r, pixel_norm.g), pixel_norm.b);
      m = std::min(std::min(pixel_norm.r, pixel_norm.g), pixel_norm.b);

      d = v - m;
      s = v <= 0.f ? 0.f : d / v;

      if (v == m)
         h = 0;
      else if (v == pixel_norm.r)
         h = (pixel_norm.g - pixel_norm.b) / d + (pixel_norm.g < pixel_norm.b ? 6.f : 0.f);
      else if (v == pixel_norm.g)
         h = (pixel_norm.b - pixel_norm.r) / d + 2.f;
      else if (v == pixel_norm.b)
         h = (pixel_norm.r - pixel_norm.g) / d + 4.f;

      h /= 6.f;

      return vec4(h, s, v, pixel_norm.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_hsv_to_none {
   static vec4 convert(vec4 hsv) {
      F32 h, f, p, q, t, v;
      I32 i;

      v = hsv.z;

      if (v == 0 || hsv.y == 0)
         return vec4(v, v, v, hsv.a);

      h = hsv.x * 6.f;
      i = (I32)std::floor(h);
      f = h - i;

      p = v * (1.f - hsv.y);
      q = v * (1.f - hsv.y * f);
      t = v * (1.f - hsv.y * (1.f - f));

      switch (i % 6) {
         case 0:   return vec4(v, t, p, hsv.a);
         case 1:   return vec4(q, v, p, hsv.a);
         case 2:   return vec4(p, v, t, hsv.a);
         case 3:   return vec4(p, q, v, hsv.a);
         case 4:   return vec4(t, p, v, hsv.a);
         default:  return vec4(v, p, q, hsv.a);
      }
   }
};

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_none_to_hsl {
   static vec4 convert(vec4 pixel_norm) {
      return convert_colorspace_hsv_to_hsl::convert(convert_colorspace_none_to_hsv::convert(pixel_norm));
   }
};

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_hsl_to_none {
   static vec4 convert(vec4 hsl) {
      return convert_colorspace_hsv_to_none::convert(convert_colorspace_hsl_to_hsv::convert(hsl));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output, typename Family>
struct convert_colorspace<Input, Output, false, Family, Family,
   ColorspaceVariantType<ColorspaceVariant::hsl>,
   ColorspaceVariantType<ColorspaceVariant::hsv>> : convert_colorspace_hsl_to_hsv { };

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output, typename Family>
struct convert_colorspace<Input, Output, false, Family, Family,
   ColorspaceVariantType<ColorspaceVariant::hsv>,
   ColorspaceVariantType<ColorspaceVariant::hsl>> : convert_colorspace_hsv_to_hsl { };

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output, typename Family>
struct convert_colorspace<Input, Output, false, Family, Family,
   ColorspaceVariantType<ColorspaceVariant::none>,
   ColorspaceVariantType<ColorspaceVariant::hsl>> : convert_colorspace_none_to_hsl { };

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output, typename Family>
struct convert_colorspace<Input, Output, false, Family, Family,
   ColorspaceVariantType<ColorspaceVariant::hsl>,
   ColorspaceVariantType<ColorspaceVariant::none>> : convert_colorspace_hsl_to_none { };

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output, typename Family>
struct convert_colorspace<Input, Output, false, Family, Family,
   ColorspaceVariantType<ColorspaceVariant::none>,
   ColorspaceVariantType<ColorspaceVariant::hsv>> : convert_colorspace_none_to_hsv { };

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output, typename Family>
struct convert_colorspace<Input, Output, false, Family, Family,
   ColorspaceVariantType<ColorspaceVariant::hsv>,
   ColorspaceVariantType<ColorspaceVariant::none>> : convert_colorspace_hsv_to_none { };

#pragma endregion
#pragma region RGB <--> YCbCr

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output, typename Family>
struct convert_colorspace<Input, Output, false, Family, Family,
   ColorspaceVariantType<ColorspaceVariant::none>,
   ColorspaceVariantType<ColorspaceVariant::ycbcr>> {
   static vec4 convert(vec4 rgb) {
      using Info = ColorspaceFamilyInfo<Family::value>;
      F32 y = Info::kr * rgb.r + Info::kg * rgb.g + Info::kb * rgb.b;
      return vec4(y, (rgb.b - y) / (2.f - 2.f * Info::kb), (rgb.b - y) / (2.f - 2.f * Info::kr), rgb.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename Input, typename Output, typename Family>
struct convert_colorspace<Input, Output, false, Family, Family,
   ColorspaceVariantType<ColorspaceVariant::ycbcr>,
   ColorspaceVariantType<ColorspaceVariant::none>> {
   static vec4 convert(vec4 ycbcr) {
      using Info = ColorspaceFamilyInfo<Family::value>;
      F32 b = ycbcr[0] + ycbcr[1] * (2.f - 2.f * Info::kb);
      F32 r = ycbcr[0] + ycbcr[2] * (2.f - 2.f * Info::kr);
      return vec4(r, ycbcr[0] - Info::kr * r - Info::kb * b, b, ycbcr.a);
   }
};

#pragma endregion
#pragma region CIE XYZ <--> bt709 linear

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::bt709_linear_rgb>> {
   static vec4 convert(vec4 xyz) {
      const mat3 xform(
          3.2404542f, -0.9692660f,  0.0556434f,
         -1.5371385f,  1.8760108f, -0.2040259f,
         -0.4985314f,  0.0415560f,  1.0572252f);

      return vec4(xform * vec3(xyz), xyz.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::cie_xyz>> {
   static vec4 convert(vec4 rgb) {
      const mat3 xform(
         0.4124564f, 0.2126729f, 0.0193339f,
         0.3575761f, 0.7151522f, 0.1191920f,
         0.1804375f, 0.0721750f, 0.9503041f);

      return vec4(xform * vec3(rgb),rgb.a);
   }
};

#pragma endregion
#pragma region bt709 gamma conversion

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::srgb>> {
   static vec4 convert(vec4 rgb) {
      for (glm::length_t i = 0; i < 3; ++i) {
         const F32 c = rgb[i];
         if (c <= 0.00313066844250063f) {
            rgb[i] = c * 12.92f;
         } else {
            rgb[i] = 1.055f * std::pow(c, 1.f / 2.4f) - 0.055f;
         }
      }
      return rgb;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::srgb>, ColorspaceType<Colorspace::bt709_linear_rgb>> {
   static vec4 convert(vec4 rgb) {
      for (glm::length_t i = 0; i < 3; ++i) {
         const F32 c = rgb[i];
         if (c <= 0.0404482362771082f) {
            rgb[i] = c / 12.92f;
         } else {
            rgb[i] = std::pow((c + 0.055f) / 1.055f, 2.4f);
         }
      }
      return rgb;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::bt709_rgb>> {
   static vec4 convert(vec4 rgb) {
      for (glm::length_t i = 0; i < 3; ++i) {
         const F32 c = rgb[i];
         if (c < 0.018f) {
            rgb[i] = c * 4.5f;
         } else {
            rgb[i] = 1.099f * std::pow(c, 0.45f) - 0.099f;
         }
      }
      return rgb;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::bt709_rgb>, ColorspaceType<Colorspace::bt709_linear_rgb>> {
   static vec4 convert(vec4 rgb) {
      for (glm::length_t i = 0; i < 3; ++i) {
         const F32 c = rgb[i];
         if (c < 0.081) {
            rgb[i] = c / 4.5f;
         } else {
            rgb[i] = std::pow((c + 0.099f) / 1.099f, 1.f / 0.45f);
         }
      }
      return rgb;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::bt709_rgb>, ColorspaceType<Colorspace::srgb>> {
   static vec4 convert(vec4 rgb) {
      return convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::srgb>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::bt709_rgb>, ColorspaceType<Colorspace::bt709_linear_rgb>>::convert(rgb));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::srgb>, ColorspaceType<Colorspace::bt709_rgb>> {
   static vec4 convert(vec4 rgb) {
      return convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::bt709_rgb>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::srgb>, ColorspaceType<Colorspace::bt709_linear_rgb>>::convert(rgb));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::srgb>> {
   static vec4 convert(vec4 xyz) {
      return convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::srgb>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::bt709_linear_rgb>>::convert(xyz));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::srgb>, ColorspaceType<Colorspace::cie_xyz>> {
   static vec4 convert(vec4 rgb) {
      return convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::cie_xyz>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::srgb>, ColorspaceType<Colorspace::bt709_linear_rgb>>::convert(rgb));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::bt709_rgb>> {
   static vec4 convert(vec4 xyz) {
      return convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::bt709_rgb>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::bt709_linear_rgb>>::convert(xyz));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::bt709_rgb>, ColorspaceType<Colorspace::cie_xyz>> {
   static vec4 convert(vec4 rgb) {
      return convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::cie_xyz>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::bt709_rgb>, ColorspaceType<Colorspace::bt709_linear_rgb>>::convert(rgb));
   }
};

#pragma endregion
#pragma region CIE

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::cie_xyy>> {
   static vec4 convert(vec4 xyz) {
      F32 d = xyz.x + xyz.y + xyz.z;
      return d == 0.f ? vec4(0.f, 0.f, 0.f, xyz.a) : vec4(xyz.x / d, xyz.y / d, xyz.y, xyz.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_xyy>, ColorspaceType<Colorspace::cie_xyz>> {
   static vec4 convert(vec4 xyy) {
      return xyy.y == 0.f ? vec4(0.f, 0.f, 0.f, xyy.a) : vec4(xyy.x * xyy.z / xyy.y, xyy.z, (1.f - xyy.x - xyy.y) * xyy.z / xyy.y, xyy.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::cie_lab_d65>> {
   static vec4 convert(vec4 xyz) {
      constexpr F32 epsilon = 216.f / 24389.f;
      constexpr F32 kappa = 24389.f / 27.f;

      // D65 white point compensation
      xyz.x /= 0.95047f;
      xyz.z /= 1.08883f;

      for (glm::length_t i = 0; i < 3; ++i) {
         const F32 c = xyz[i];
         if (c > epsilon) {
            xyz[i] = std::cbrt(c);
         } else {
            xyz[i] = (kappa * c + 16.f) / 116.f;
         }
      }

      return vec4(116.f * xyz.y - 16, 500.f * (xyz.x - xyz.y), 200.f * (xyz.y - xyz.z), xyz.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_lab_d65>, ColorspaceType<Colorspace::cie_xyz>> {
   static vec4 convert(vec4 lab) {
      constexpr F32 epsilon = 216.f / 24389.f;
      constexpr F32 kappa = 24389.f / 27.f;

      F32 y = (lab.x + 16.f) / 116.f;

      F32 x = lab.y / 500.f + y;
      const F32 xxx = x * x * x;
      if (xxx > epsilon) {
         x = xxx;
      } else {
         x = (116.f * x - 16.f) / kappa;
      }

      F32 z = y - lab.z / 200.f;
      const F32 zzz = z * z * z;
      if (zzz > epsilon) {
         z = zzz;
      } else {
         z = (116.f * z - 16.f) / kappa;
      }

      if (lab.x > kappa * epsilon) {
         y = y * y * y;
      } else {
         y = lab.x / kappa;
      }

      // D65 white point compensation
      x *= 0.95047f;
      z *= 1.08883f;
      
      return vec4(x, y, z, lab.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::cie_luv_d65>> {
   static vec4 convert(vec4 xyz) {
      constexpr F32 epsilon = 216.f / 24389.f;
      constexpr F32 kappa = 24389.f / 27.f;
      constexpr F32 xw = 0.95047f;
      constexpr F32 yw = 1.f;
      constexpr F32 zw = 1.08883f;
      constexpr F32 dw = (xw + 15.f * yw + 3.f * zw);
      constexpr F32 uw = 4.f * xw / dw;
      constexpr F32 vw = 9.f * yw / dw;

      const F32 y = xyz.y / yw;
      const F32 dp = xyz.x + 15.f * xyz.y + 3.f * xyz.z;
      const F32 up = 4.f * xyz.x / dp;
      const F32 vp = 9.f * xyz.y / dp;

      const F32 l = y > epsilon ? (116.f * std::cbrt(y) - 16.f) : kappa * y;
      const F32 u = 13.f * l * (up - uw);
      const F32 v = 13.f * l * (vp - vw);

      return vec4(l, u, v, xyz.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct convert_colorspace<ColorspaceType<Colorspace::cie_luv_d65>, ColorspaceType<Colorspace::cie_xyz>> {
   static vec4 convert(vec4 luv) {
      constexpr F32 epsilon = 216.f / 24389.f;
      constexpr F32 kappa = 24389.f / 27.f;
      constexpr F32 xw = 0.95047f;
      constexpr F32 yw = 1.f;
      constexpr F32 zw = 1.08883f;
      constexpr F32 dw = (xw + 15.f * yw + 3.f * zw);
      constexpr F32 uw = 4.f * xw / dw;
      constexpr F32 vw = 9.f * yw / dw;

      F32 y;
      if (luv.x > kappa * epsilon) {
         y = (luv.x + 16.f) / 116.f;
         y = y * y * y;
      } else {
         y = luv.x / kappa;
      }

      const F32 a = 1.f / 3.f * (52.f * luv.x / (luv.y + 13.f * luv.x * uw) - 1.f);
      const F32 b = -5.f * y;
      const F32 c = -1.f / 3.f;
      const F32 d = y * (39.f * luv.x / (luv.z + 13.f * luv.x * vw) - 5.f);

      const F32 x = (d - b) / (a  - c);
      const F32 z = x * a + b;

      return vec4(x, y, z, luv.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_lmn_to_lch {
   static vec4 convert(vec4 lmn) {
      const F32 c = std::sqrt(lmn.y * lmn.y + lmn.z * lmn.z);
      const F32 h = glm::degrees(std::atan2(lmn.z, lmn.y));
      return vec4(lmn.x, c, h < 0 ? h + 360.f : h, lmn.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
struct convert_colorspace_lch_to_lmn {
   static vec4 convert(vec4 lch) {
      const F32 rad = glm::radians(lch.z);
      return vec4(lch.x, lch.y * std::cos(rad), lch.y * std::sin(rad), lch.a);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_lab_d65>, ColorspaceType<Colorspace::cie_lchab_d65>> : convert_colorspace_lmn_to_lch { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_luv_d65>, ColorspaceType<Colorspace::cie_lchuv_d65>> : convert_colorspace_lmn_to_lch { };

///////////////////////////////////////////////////////////////////////////////
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_lchab_d65>, ColorspaceType<Colorspace::cie_lab_d65>> : convert_colorspace_lch_to_lmn { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_lchuv_d65>, ColorspaceType<Colorspace::cie_luv_d65>> : convert_colorspace_lch_to_lmn { };

///////////////////////////////////////////////////////////////////////////////
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::cie_lchab_d65>> {
   static vec4 convert(vec4 xyz) {
      return convert_colorspace<ColorspaceType<Colorspace::cie_lab_d65>, ColorspaceType<Colorspace::cie_lchab_d65>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::cie_lab_d65>>::convert(xyz));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_lchab_d65>, ColorspaceType<Colorspace::cie_xyz>> {
   static vec4 convert(vec4 lchab) {
      return convert_colorspace<ColorspaceType<Colorspace::cie_lab_d65>, ColorspaceType<Colorspace::cie_xyz>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::cie_lchab_d65>, ColorspaceType<Colorspace::cie_lab_d65>>::convert(lchab));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::cie_lchuv_d65>> {
   static vec4 convert(vec4 xyz) {
      return convert_colorspace<ColorspaceType<Colorspace::cie_luv_d65>, ColorspaceType<Colorspace::cie_lchuv_d65>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::cie_luv_d65>>::convert(xyz));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_lchuv_d65>, ColorspaceType<Colorspace::cie_xyz>> {
   static vec4 convert(vec4 lchuv) {
      return convert_colorspace<ColorspaceType<Colorspace::cie_luv_d65>, ColorspaceType<Colorspace::cie_xyz>>::convert(
         convert_colorspace<ColorspaceType<Colorspace::cie_lchuv_d65>, ColorspaceType<Colorspace::cie_luv_d65>>::convert(lchuv));
   }
};

#pragma endregion
#pragma region Unknown/Nonspecific

///////////////////////////////////////////////////////////////////////////////
template <typename Input>
struct convert_colorspace<Input, ColorspaceType<Colorspace::unknown>, false> : convert_colorspace_nop { };

///////////////////////////////////////////////////////////////////////////////
template <typename Output>
struct convert_colorspace<ColorspaceType<Colorspace::unknown>, Output, false> : convert_colorspace_nop { };

///////////////////////////////////////////////////////////////////////////////
template <> struct convert_colorspace<ColorspaceType<Colorspace::linear_other>, ColorspaceType<Colorspace::linear_depth_stencil>> : convert_colorspace_nop { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::linear_other>, ColorspaceType<Colorspace::bt709_linear_rgb>> : convert_colorspace_nop { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::linear_other>, ColorspaceType<Colorspace::bt709_rgb>> : convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::bt709_rgb>> { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::linear_other>, ColorspaceType<Colorspace::srgb>> : convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::srgb>> { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::linear_other>, ColorspaceType<Colorspace::cie_xyz>> : convert_colorspace_nop { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::linear_depth_stencil>, ColorspaceType<Colorspace::linear_other>> : convert_colorspace_nop { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::bt709_linear_rgb>, ColorspaceType<Colorspace::linear_other>> : convert_colorspace_nop { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::cie_xyz>, ColorspaceType<Colorspace::linear_other>> : convert_colorspace_nop { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::bt709_rgb>, ColorspaceType<Colorspace::linear_other>> : convert_colorspace<ColorspaceType<Colorspace::bt709_rgb>, ColorspaceType<Colorspace::bt709_linear_rgb>> { };
template <> struct convert_colorspace<ColorspaceType<Colorspace::srgb>, ColorspaceType<Colorspace::linear_other>> : convert_colorspace<ColorspaceType<Colorspace::srgb>, ColorspaceType<Colorspace::bt709_linear_rgb>> { };

#pragma endregion

} // be::gfx::detail

///////////////////////////////////////////////////////////////////////////////
template <Colorspace Input, Colorspace Output>
ImagePixelNormTransformFunc convert_colorspace_func() {
   return detail::convert_colorspace<detail::ColorspaceType<Input>, detail::ColorspaceType<Output>>::convert;
}

///////////////////////////////////////////////////////////////////////////////
template <Colorspace Input, Colorspace Output>
vec4 convert_colorspace(vec4 pixel_norm) {
   return detail::convert_colorspace<detail::ColorspaceType<Input>, detail::ColorspaceType<Output>>::convert(pixel_norm);
}

} // be::gfx

#endif
