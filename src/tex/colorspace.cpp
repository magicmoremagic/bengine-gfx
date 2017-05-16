#include "tex/pch.hpp"
#include "tex/colorspace.hpp"

/*!! include 'tex/colorspace' !! 253 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(ColorspaceFamily constant) noexcept {
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
const char* colorspace_family_name(ColorspaceFamily constant) noexcept {
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
std::array<const ColorspaceFamily, 5> colorspace_family_values() noexcept {
   return ::be::EnumTraits<ColorspaceFamily>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, ColorspaceFamily constant) {
   if (is_valid(constant)) {
      os << colorspace_family_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}


///////////////////////////////////////////////////////////////////////////////
bool is_valid(ColorspaceVariant constant) noexcept {
   switch (constant) {
      case ColorspaceVariant::none:
      case ColorspaceVariant::hsl:
      case ColorspaceVariant::hsv:
      case ColorspaceVariant::ycbcr:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* colorspace_variant_name(ColorspaceVariant constant) noexcept {
   switch (constant) {
      case ColorspaceVariant::none:  return "none";
      case ColorspaceVariant::hsl:   return "hsl";
      case ColorspaceVariant::hsv:   return "hsv";
      case ColorspaceVariant::ycbcr: return "ycbcr";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const ColorspaceVariant, 4> colorspace_variant_values() noexcept {
   return ::be::EnumTraits<ColorspaceVariant>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, ColorspaceVariant constant) {
   if (is_valid(constant)) {
      os << colorspace_variant_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}


///////////////////////////////////////////////////////////////////////////////
bool is_valid(Colorspace constant) noexcept {
   switch (constant) {
      case Colorspace::unknown:
      case Colorspace::linear_other:
      case Colorspace::linear_depth_stencil:
      case Colorspace::linear_depth:
      case Colorspace::linear_stencil:
      case Colorspace::bt709_linear_rgb:
      case Colorspace::bt709_linear_hsl:
      case Colorspace::bt709_linear_hsv:
      case Colorspace::bt709_linear_ycbcr:
      case Colorspace::bt709_rgb:
      case Colorspace::bt709_hsl:
      case Colorspace::bt709_hsv:
      case Colorspace::bt709_ycbcr:
      case Colorspace::srgb:
      case Colorspace::srgb_hsl:
      case Colorspace::srgb_hsv:
      case Colorspace::srgb_ycbcr:
      case Colorspace::cie_xyz:
      case Colorspace::cie_lab_d65:
      case Colorspace::cie_lchab_d65:
      case Colorspace::cie_luv_d65:
      case Colorspace::cie_lchuv_d65:
      case Colorspace::cie_xyy:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* colorspace_name(Colorspace constant) noexcept {
   switch (constant) {
      case Colorspace::unknown:              return "unknown";
      case Colorspace::linear_other:         return "linear_other";
      case Colorspace::linear_depth_stencil: return "linear_depth_stencil";
      case Colorspace::linear_depth:         return "linear_depth";
      case Colorspace::linear_stencil:       return "linear_stencil";
      case Colorspace::bt709_linear_rgb:     return "bt709_linear_rgb";
      case Colorspace::bt709_linear_hsl:     return "bt709_linear_hsl";
      case Colorspace::bt709_linear_hsv:     return "bt709_linear_hsv";
      case Colorspace::bt709_linear_ycbcr:   return "bt709_linear_ycbcr";
      case Colorspace::bt709_rgb:            return "bt709_rgb";
      case Colorspace::bt709_hsl:            return "bt709_hsl";
      case Colorspace::bt709_hsv:            return "bt709_hsv";
      case Colorspace::bt709_ycbcr:          return "bt709_ycbcr";
      case Colorspace::srgb:                 return "srgb";
      case Colorspace::srgb_hsl:             return "srgb_hsl";
      case Colorspace::srgb_hsv:             return "srgb_hsv";
      case Colorspace::srgb_ycbcr:           return "srgb_ycbcr";
      case Colorspace::cie_xyz:              return "cie_xyz";
      case Colorspace::cie_lab_d65:          return "cie_lab_d65";
      case Colorspace::cie_lchab_d65:        return "cie_lchab_d65";
      case Colorspace::cie_luv_d65:          return "cie_luv_d65";
      case Colorspace::cie_lchuv_d65:        return "cie_lchuv_d65";
      case Colorspace::cie_xyy:              return "cie_xyy";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const Colorspace, 23> colorspace_values() noexcept {
   return ::be::EnumTraits<Colorspace>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, Colorspace constant) {
   if (is_valid(constant)) {
      os << colorspace_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
Colorspace base_colorspace(ColorspaceFamily constant) noexcept {
   switch (constant) {
      case ColorspaceFamily::none:         return Colorspace::linear_other;
      case ColorspaceFamily::bt709_linear: return Colorspace::bt709_linear_rgb;
      case ColorspaceFamily::bt709:        return Colorspace::bt709_rgb;
      case ColorspaceFamily::srgb:         return Colorspace::srgb;
      case ColorspaceFamily::cie:          return Colorspace::cie_xyz;
      default:
         return Colorspace::unknown;
   }
}

///////////////////////////////////////////////////////////////////////////////
Colorspace linear_colorspace(ColorspaceFamily constant) noexcept {
   switch (constant) {
      case ColorspaceFamily::bt709_linear: return Colorspace::bt709_linear_rgb;
      case ColorspaceFamily::bt709:        return Colorspace::bt709_linear_rgb;
      case ColorspaceFamily::srgb:         return Colorspace::bt709_linear_rgb;
      case ColorspaceFamily::cie:          return Colorspace::cie_xyz;
      default:
         return Colorspace::linear_other;
   }
}

///////////////////////////////////////////////////////////////////////////////
bool is_linear(Colorspace constant) noexcept {
   switch (constant) {
      case Colorspace::linear_other:         return true;
      case Colorspace::linear_depth_stencil: return true;
      case Colorspace::linear_depth:         return true;
      case Colorspace::linear_stencil:       return true;
      case Colorspace::bt709_linear_rgb:     return true;
      case Colorspace::cie_xyz:              return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
ColorspaceFamily colorspace_family(Colorspace constant) noexcept {
   switch (constant) {
      case Colorspace::bt709_linear_rgb:     return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_linear_hsl:     return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_linear_hsv:     return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_linear_ycbcr:   return ColorspaceFamily::bt709_linear;
      case Colorspace::bt709_rgb:            return ColorspaceFamily::bt709;
      case Colorspace::bt709_hsl:            return ColorspaceFamily::bt709;
      case Colorspace::bt709_hsv:            return ColorspaceFamily::bt709;
      case Colorspace::bt709_ycbcr:          return ColorspaceFamily::bt709;
      case Colorspace::srgb:                 return ColorspaceFamily::srgb;
      case Colorspace::srgb_hsl:             return ColorspaceFamily::srgb;
      case Colorspace::srgb_hsv:             return ColorspaceFamily::srgb;
      case Colorspace::srgb_ycbcr:           return ColorspaceFamily::srgb;
      case Colorspace::cie_xyz:              return ColorspaceFamily::cie;
      case Colorspace::cie_lab_d65:          return ColorspaceFamily::cie;
      case Colorspace::cie_lchab_d65:        return ColorspaceFamily::cie;
      case Colorspace::cie_luv_d65:          return ColorspaceFamily::cie;
      case Colorspace::cie_lchuv_d65:        return ColorspaceFamily::cie;
      case Colorspace::cie_xyy:              return ColorspaceFamily::cie;
      default:
         return ColorspaceFamily::none;
   }
}

///////////////////////////////////////////////////////////////////////////////
ColorspaceVariant colorspace_variant(Colorspace constant) noexcept {
   switch (constant) {
      case Colorspace::bt709_linear_hsl:     return ColorspaceVariant::hsl;
      case Colorspace::bt709_linear_hsv:     return ColorspaceVariant::hsv;
      case Colorspace::bt709_linear_ycbcr:   return ColorspaceVariant::ycbcr;
      case Colorspace::bt709_hsl:            return ColorspaceVariant::hsl;
      case Colorspace::bt709_hsv:            return ColorspaceVariant::hsv;
      case Colorspace::bt709_ycbcr:          return ColorspaceVariant::ycbcr;
      case Colorspace::srgb_hsl:             return ColorspaceVariant::hsl;
      case Colorspace::srgb_hsv:             return ColorspaceVariant::hsv;
      case Colorspace::srgb_ycbcr:           return ColorspaceVariant::ycbcr;
      default:
         return ColorspaceVariant::none;
   }
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */
