#include "pch.hpp"
#include "colorspace.hpp"

namespace be::gfx {

/*!! include 'colorspace' !! 170 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
bool is_linear(Colorspace constant) {
   switch (constant) {
      case Colorspace::bt709_linear_rgb:   return true;
      case Colorspace::cie_xyz:            return true;
      case Colorspace::cie_rgb:            return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
ColorspaceFamily colorspace_family(Colorspace constant) {
   switch (constant) {
      case Colorspace::bt709_linear_rgb:   return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_linear_hsl:   return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_linear_hsv:   return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_linear_ycbcr: return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_linear_yuv:   return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_rgb:          return ColorspaceFamily::bt709;
      case Colorspace::bt709_hsl:          return ColorspaceFamily::bt709;
      case Colorspace::bt709_hsv:          return ColorspaceFamily::bt709;
      case Colorspace::bt709_ycbcr:        return ColorspaceFamily::bt709;
      case Colorspace::bt709_yuv:          return ColorspaceFamily::bt709;
      case Colorspace::srgb:               return ColorspaceFamily::srgb;
      case Colorspace::srgb_hsl:           return ColorspaceFamily::srgb;
      case Colorspace::srgb_hsv:           return ColorspaceFamily::srgb;
      case Colorspace::srgb_ycbcr:         return ColorspaceFamily::srgb;
      case Colorspace::srgb_yuv:           return ColorspaceFamily::srgb;
      case Colorspace::cie_xyz:            return ColorspaceFamily::cie;
      case Colorspace::cie_rgb:            return ColorspaceFamily::cie;
      case Colorspace::cie_lab:            return ColorspaceFamily::cie;
      default:
         return ColorspaceFamily::none;
   }
}

///////////////////////////////////////////////////////////////////////////////
ColorspaceVariant colorspace_variant(Colorspace constant) {
   switch (constant) {
      case Colorspace::bt709_linear_hsl:   return ColorspaceVariant::hsl;
      case Colorspace::bt709_linear_hsv:   return ColorspaceVariant::hsv;
      case Colorspace::bt709_linear_ycbcr: return ColorspaceVariant::ycbcr;
      case Colorspace::bt709_linear_yuv:   return ColorspaceVariant::yuv;
      case Colorspace::bt709_hsl:          return ColorspaceVariant::hsl;
      case Colorspace::bt709_hsv:          return ColorspaceVariant::hsv;
      case Colorspace::bt709_ycbcr:        return ColorspaceVariant::ycbcr;
      case Colorspace::bt709_yuv:          return ColorspaceVariant::yuv;
      case Colorspace::srgb_hsl:           return ColorspaceVariant::hsl;
      case Colorspace::srgb_hsv:           return ColorspaceVariant::hsv;
      case Colorspace::srgb_ycbcr:         return ColorspaceVariant::ycbcr;
      case Colorspace::srgb_yuv:           return ColorspaceVariant::yuv;
      default:
         return ColorspaceVariant::none;
   }
}

///////////////////////////////////////////////////////////////////////////////
bool is_valid(Colorspace constant) {
   switch (constant) {
      case Colorspace::none:
      case Colorspace::bt709_linear_rgb:
      case Colorspace::bt709_linear_hsl:
      case Colorspace::bt709_linear_hsv:
      case Colorspace::bt709_linear_ycbcr:
      case Colorspace::bt709_linear_yuv:
      case Colorspace::bt709_rgb:
      case Colorspace::bt709_hsl:
      case Colorspace::bt709_hsv:
      case Colorspace::bt709_ycbcr:
      case Colorspace::bt709_yuv:
      case Colorspace::srgb:
      case Colorspace::srgb_hsl:
      case Colorspace::srgb_hsv:
      case Colorspace::srgb_ycbcr:
      case Colorspace::srgb_yuv:
      case Colorspace::cie_xyz:
      case Colorspace::cie_rgb:
      case Colorspace::cie_lab:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
bool is_valid(ColorspaceFamily constant) {
   switch (constant) {
      case ColorspaceFamily::none:
      case ColorspaceFamily::bt709_linear:
      case ColorspaceFamily::bt709:
      case ColorspaceFamily::srgb:
      case ColorspaceFamily::cie:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
bool is_valid(ColorspaceVariant constant) {
   switch (constant) {
      case ColorspaceVariant::none:
      case ColorspaceVariant::hsl:
      case ColorspaceVariant::hsv:
      case ColorspaceVariant::ycbcr:
      case ColorspaceVariant::yuv:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* colorspace_name(Colorspace constant) {
   switch (constant) {
      case Colorspace::none:               return "none";
      case Colorspace::bt709_linear_rgb:   return "bt709_linear_rgb";
      case Colorspace::bt709_linear_hsl:   return "bt709_linear_hsl";
      case Colorspace::bt709_linear_hsv:   return "bt709_linear_hsv";
      case Colorspace::bt709_linear_ycbcr: return "bt709_linear_ycbcr";
      case Colorspace::bt709_linear_yuv:   return "bt709_linear_yuv";
      case Colorspace::bt709_rgb:          return "bt709_rgb";
      case Colorspace::bt709_hsl:          return "bt709_hsl";
      case Colorspace::bt709_hsv:          return "bt709_hsv";
      case Colorspace::bt709_ycbcr:        return "bt709_ycbcr";
      case Colorspace::bt709_yuv:          return "bt709_yuv";
      case Colorspace::srgb:               return "srgb";
      case Colorspace::srgb_hsl:           return "srgb_hsl";
      case Colorspace::srgb_hsv:           return "srgb_hsv";
      case Colorspace::srgb_ycbcr:         return "srgb_ycbcr";
      case Colorspace::srgb_yuv:           return "srgb_yuv";
      case Colorspace::cie_xyz:            return "cie_xyz";
      case Colorspace::cie_rgb:            return "cie_rgb";
      case Colorspace::cie_lab:            return "cie_lab";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* colorspace_family_name(ColorspaceFamily constant) {
   switch (constant) {
      case ColorspaceFamily::none:         return "none";
      case ColorspaceFamily::bt709_linear: return "bt709_linear";
      case ColorspaceFamily::bt709:        return "bt709";
      case ColorspaceFamily::srgb:         return "srgb";
      case ColorspaceFamily::cie:          return "cie";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* colorspace_variant_name(ColorspaceVariant constant) {
   switch (constant) {
      case ColorspaceVariant::none:  return "none";
      case ColorspaceVariant::hsl:   return "hsl";
      case ColorspaceVariant::hsv:   return "hsv";
      case ColorspaceVariant::ycbcr: return "ycbcr";
      case ColorspaceVariant::yuv:   return "yuv";
      default:
         return "?";
   }
}

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx
