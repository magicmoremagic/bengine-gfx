#pragma once
#ifndef BE_GFX_TEX_COLORSPACE_HPP_
#define BE_GFX_TEX_COLORSPACE_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/enum_traits.hpp>

// TODO RGBE
// TODO logLUV, RGBM http://graphicrants.blogspot.fr/2009/04/rgbm-color-encoding.html

/*!! include 'tex/colorspace' !! 319 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
enum class ColorspaceFamily : U8 {
   none = 0,
   bt709_linear,
   bt709,
   srgb,
   cie
};

bool is_valid(ColorspaceFamily constant) noexcept;
const char* colorspace_family_name(ColorspaceFamily constant) noexcept;
std::array<const ColorspaceFamily, 5> colorspace_family_values() noexcept;
std::ostream& operator<<(std::ostream& os, ColorspaceFamily constant);

///////////////////////////////////////////////////////////////////////////////
enum class ColorspaceVariant : U8 {
   none = 0,
   hsl,
   hsv,
   ycbcr
};

bool is_valid(ColorspaceVariant constant) noexcept;
const char* colorspace_variant_name(ColorspaceVariant constant) noexcept;
std::array<const ColorspaceVariant, 4> colorspace_variant_values() noexcept;
std::ostream& operator<<(std::ostream& os, ColorspaceVariant constant);

///////////////////////////////////////////////////////////////////////////////
enum class Colorspace : U8 {
   unknown = 0,
   linear_other,
   linear_depth_stencil,
   linear_depth,
   linear_stencil,
   bt709_linear_rgb,
   bt709_linear_hsl,
   bt709_linear_hsv,
   bt709_linear_ycbcr,
   bt709_rgb,
   bt709_hsl,
   bt709_hsv,
   bt709_ycbcr,
   srgb,
   srgb_hsl,
   srgb_hsv,
   srgb_ycbcr,
   cie_xyz,
   cie_lab_d65,
   cie_lchab_d65,
   cie_luv_d65,
   cie_lchuv_d65,
   cie_xyy
};

bool is_valid(Colorspace constant) noexcept;
const char* colorspace_name(Colorspace constant) noexcept;
std::array<const Colorspace, 23> colorspace_values() noexcept;
std::ostream& operator<<(std::ostream& os, Colorspace constant);
Colorspace base_colorspace(ColorspaceFamily constant) noexcept;
Colorspace linear_colorspace(ColorspaceFamily constant) noexcept;
bool is_linear(Colorspace constant) noexcept;
ColorspaceFamily colorspace_family(Colorspace constant) noexcept;
ColorspaceVariant colorspace_variant(Colorspace constant) noexcept;

template <Colorspace>
struct ColorspaceInfo {
   static constexpr ColorspaceFamily family = ColorspaceFamily::none;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::bt709_linear_rgb> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::bt709_linear;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::bt709_linear_hsl> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::bt709_linear;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::hsl;
};

template <> struct ColorspaceInfo<Colorspace::bt709_linear_hsv> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::bt709_linear;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::hsv;
};

template <> struct ColorspaceInfo<Colorspace::bt709_linear_ycbcr> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::bt709_linear;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::ycbcr;
};

template <> struct ColorspaceInfo<Colorspace::bt709_rgb> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::bt709;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::bt709_hsl> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::bt709;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::hsl;
};

template <> struct ColorspaceInfo<Colorspace::bt709_hsv> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::bt709;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::hsv;
};

template <> struct ColorspaceInfo<Colorspace::bt709_ycbcr> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::bt709;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::ycbcr;
};

template <> struct ColorspaceInfo<Colorspace::srgb> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::srgb;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::srgb_hsl> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::srgb;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::hsl;
};

template <> struct ColorspaceInfo<Colorspace::srgb_hsv> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::srgb;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::hsv;
};

template <> struct ColorspaceInfo<Colorspace::srgb_ycbcr> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::srgb;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::ycbcr;
};

template <> struct ColorspaceInfo<Colorspace::cie_xyz> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::cie;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::cie_lab_d65> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::cie;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::cie_lchab_d65> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::cie;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::cie_luv_d65> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::cie;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::cie_lchuv_d65> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::cie;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <> struct ColorspaceInfo<Colorspace::cie_xyy> {
   static constexpr ColorspaceFamily family = ColorspaceFamily::cie;
   static constexpr ColorspaceVariant variant = ColorspaceVariant::none;
};

template <ColorspaceFamily>
struct ColorspaceFamilyInfo {
   static constexpr Colorspace base = Colorspace::unknown;
   static constexpr Colorspace linear = Colorspace::linear_other;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::none> {
   static constexpr Colorspace base = Colorspace::linear_other;
   static constexpr Colorspace linear = Colorspace::linear_other;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::bt709_linear> {
   static constexpr Colorspace base = Colorspace::bt709_linear_rgb;
   static constexpr Colorspace linear = Colorspace::bt709_linear_rgb;
   static constexpr F32 kr = 0.2126f;
   static constexpr F32 kb = 0.0722f;
   static constexpr F32 kg = 0.7152f;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::bt709> {
   static constexpr Colorspace base = Colorspace::bt709_rgb;
   static constexpr Colorspace linear = Colorspace::bt709_linear_rgb;
   static constexpr F32 kr = 0.2126f;
   static constexpr F32 kb = 0.0722f;
   static constexpr F32 kg = 0.7152f;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::srgb> {
   static constexpr Colorspace base = Colorspace::srgb;
   static constexpr Colorspace linear = Colorspace::bt709_linear_rgb;
   static constexpr F32 kr = 0.2126f;
   static constexpr F32 kb = 0.0722f;
   static constexpr F32 kg = 0.7152f;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::cie> {
   static constexpr Colorspace base = Colorspace::cie_xyz;
   static constexpr Colorspace linear = Colorspace::cie_xyz;
};

} // be::gfx::tex

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::ColorspaceFamily> {
   using type = ::be::gfx::tex::ColorspaceFamily;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 5;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::colorspace_family_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::ColorspaceFamily::none,
         ::be::gfx::tex::ColorspaceFamily::bt709_linear,
         ::be::gfx::tex::ColorspaceFamily::bt709,
         ::be::gfx::tex::ColorspaceFamily::srgb,
         ::be::gfx::tex::ColorspaceFamily::cie,
      };
   }
};

} // be
namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::ColorspaceVariant> {
   using type = ::be::gfx::tex::ColorspaceVariant;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 4;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::colorspace_variant_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::ColorspaceVariant::none,
         ::be::gfx::tex::ColorspaceVariant::hsl,
         ::be::gfx::tex::ColorspaceVariant::hsv,
         ::be::gfx::tex::ColorspaceVariant::ycbcr,
      };
   }
};

} // be
namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::gfx::tex::Colorspace> {
   using type = ::be::gfx::tex::Colorspace;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 23;

   static bool is_valid(type value) {
      return ::be::gfx::tex::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::gfx::tex::colorspace_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::gfx::tex::Colorspace::unknown,
         ::be::gfx::tex::Colorspace::linear_other,
         ::be::gfx::tex::Colorspace::linear_depth_stencil,
         ::be::gfx::tex::Colorspace::linear_depth,
         ::be::gfx::tex::Colorspace::linear_stencil,
         ::be::gfx::tex::Colorspace::bt709_linear_rgb,
         ::be::gfx::tex::Colorspace::bt709_linear_hsl,
         ::be::gfx::tex::Colorspace::bt709_linear_hsv,
         ::be::gfx::tex::Colorspace::bt709_linear_ycbcr,
         ::be::gfx::tex::Colorspace::bt709_rgb,
         ::be::gfx::tex::Colorspace::bt709_hsl,
         ::be::gfx::tex::Colorspace::bt709_hsv,
         ::be::gfx::tex::Colorspace::bt709_ycbcr,
         ::be::gfx::tex::Colorspace::srgb,
         ::be::gfx::tex::Colorspace::srgb_hsl,
         ::be::gfx::tex::Colorspace::srgb_hsv,
         ::be::gfx::tex::Colorspace::srgb_ycbcr,
         ::be::gfx::tex::Colorspace::cie_xyz,
         ::be::gfx::tex::Colorspace::cie_lab_d65,
         ::be::gfx::tex::Colorspace::cie_lchab_d65,
         ::be::gfx::tex::Colorspace::cie_luv_d65,
         ::be::gfx::tex::Colorspace::cie_lchuv_d65,
         ::be::gfx::tex::Colorspace::cie_xyy,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
