#include "pch.hpp"
#include "tex/convert_colorspace.hpp"
#include "tex/convert_colorspace_static.hpp"

namespace be::gfx::tex {

/*!! include('tex/colorspace', true)
register_template_string([[
`max_length = colorspace.max_constant_name_length
constants = colorspace.constants
`
///////////////////////////////////////////////////////////////////////////////
PixelNormTransformFunc convert_colorspace_func(Colorspace input, Colorspace output) {
   switch (input) {`
with each constants using # {`
      case Colorspace::`name`:
         switch (output) {`
   input_name = name
   with each constants using # {`
            case Colorspace::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::`input_name`>, detail::ColorspaceTag<Colorspace::`name`>>::convert;`
   }
   `
         }
         break;`
}`
   }
   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
}
]], 'convert_colorspace_func')

write_template 'convert_colorspace_func' !! 632 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
PixelNormTransformFunc convert_colorspace_func(Colorspace input, Colorspace output) {
   switch (input) {
      case Colorspace::unknown:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::linear_other:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_other>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::linear_depth_stencil:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth_stencil>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::linear_depth:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_depth>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::linear_stencil:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::linear_stencil>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_linear_rgb:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_rgb>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_linear_hsl:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsl>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_linear_hsv:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_hsv>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_linear_ycbcr:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_rgb:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_rgb>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_hsl:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsl>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_hsv:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_hsv>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_ycbcr:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::bt709_ycbcr>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::srgb:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::srgb_hsl:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsl>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::srgb_hsv:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_hsv>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::srgb_ycbcr:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::srgb_ycbcr>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_xyz:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyz>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_lab_d65:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lab_d65>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_lchab_d65:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchab_d65>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_luv_d65:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_luv_d65>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_lchuv_d65:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_lchuv_d65>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_xyy:
         switch (output) {
            case Colorspace::unknown:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::linear_depth:         return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::linear_depth>>::convert;
            case Colorspace::linear_stencil:       return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::linear_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::cie_xyy>, detail::ColorspaceTag<Colorspace::cie_xyy>>::convert;
         }
         break;
   }
   return detail::ConvertColorspace<detail::ColorspaceTag<Colorspace::unknown>, detail::ColorspaceTag<Colorspace::unknown>>::convert;
}

/* ######################### END OF GENERATED CODE ######################### */

///////////////////////////////////////////////////////////////////////////////
vec4 convert_colorspace(vec4 pixel_norm, Colorspace input, Colorspace output) {
   return convert_colorspace_func(input, output)(pixel_norm);
}

} // be::gfx::tex
