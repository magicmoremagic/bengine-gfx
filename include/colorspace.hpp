#pragma once
#ifndef BE_GFX_COLORSPACE_HPP_
#define BE_GFX_COLORSPACE_HPP_

#include <be/core/be.hpp>

namespace be::gfx {

// TODO RGBE
// TODO logLUV, RGBM http://graphicrants.blogspot.fr/2009/04/rgbm-color-encoding.html

/*!! include 'colorspace' !! 188 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
enum class ColorspaceFamily : U8 {
   none = 0,
   bt709_linear,
   bt709,
   srgb,
   cie
};

///////////////////////////////////////////////////////////////////////////////
enum class ColorspaceVariant : U8 {
   none = 0,
   hsl,
   hsv,
   ycbcr
};

///////////////////////////////////////////////////////////////////////////////
enum class Colorspace : U8 {
   unknown = 0,
   linear_other,
   linear_depth_stencil,
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
bool is_valid(ColorspaceFamily constant) noexcept;
bool is_valid(ColorspaceVariant constant) noexcept;
const char* colorspace_name(Colorspace constant) noexcept;
const char* colorspace_family_name(ColorspaceFamily constant) noexcept;
const char* colorspace_variant_name(ColorspaceVariant constant) noexcept;
Colorspace base_colorspace(ColorspaceFamily constant) noexcept;
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
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::none> {
   static constexpr Colorspace base = Colorspace::linear_other;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::bt709_linear> {
   static constexpr Colorspace base = Colorspace::bt709_linear_rgb;
   static constexpr F32 kr = 0.2126f;
   static constexpr F32 kb = 0.0722f;
   static constexpr F32 kg = 0.7152f;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::bt709> {
   static constexpr Colorspace base = Colorspace::bt709_rgb;
   static constexpr F32 kr = 0.2126f;
   static constexpr F32 kb = 0.0722f;
   static constexpr F32 kg = 0.7152f;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::srgb> {
   static constexpr Colorspace base = Colorspace::srgb;
   static constexpr F32 kr = 0.2126f;
   static constexpr F32 kb = 0.0722f;
   static constexpr F32 kg = 0.7152f;
};

template <> struct ColorspaceFamilyInfo<ColorspaceFamily::cie> {
   static constexpr Colorspace base = Colorspace::cie_xyz;
};

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx

#endif
