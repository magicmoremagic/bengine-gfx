#pragma once
#ifndef BE_GFX_COLORSPACE_HPP_
#define BE_GFX_COLORSPACE_HPP_

#include <be/core/be.hpp>

namespace be::gfx {

/*!! include 'colorspace' !! 54 */
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
   ycbcr,
   yuv
};

///////////////////////////////////////////////////////////////////////////////
enum class Colorspace : U8 {
   none = 0,
   bt709_linear_rgb,
   bt709_linear_hsl,
   bt709_linear_hsv,
   bt709_linear_ycbcr,
   bt709_linear_yuv,
   bt709_rgb,
   bt709_hsl,
   bt709_hsv,
   bt709_ycbcr,
   bt709_yuv,
   srgb,
   srgb_hsl,
   srgb_hsv,
   srgb_ycbcr,
   srgb_yuv,
   cie_xyz,
   cie_rgb,
   cie_lab
};

bool is_linear(Colorspace constant);
ColorspaceFamily colorspace_family(Colorspace constant);
ColorspaceVariant colorspace_variant(Colorspace constant);
bool is_valid(Colorspace constant);
bool is_valid(ColorspaceFamily constant);
bool is_valid(ColorspaceVariant constant);
const char* colorspace_name(Colorspace constant);
const char* colorspace_family_name(ColorspaceFamily constant);
const char* colorspace_variant_name(ColorspaceVariant constant);
/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx

#endif
