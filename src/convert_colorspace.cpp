#include "pch.hpp"
#include "convert_colorspace.hpp"
#include "convert_colorspace_static.hpp"

namespace be::gfx {

/*!! include('colorspace', true)
register_template_string([[
`max_length = colorspace.max_constant_name_length
constants = colorspace.constants
`
///////////////////////////////////////////////////////////////////////////////
ImagePixelNormTransformFunc convert_colorspace_func(Colorspace input, Colorspace output) {
   switch (input) {`
with each constants using # {`
      case Colorspace::`name`:
         switch (output) {`
   input_name = name
   with each constants using # {`
            case Colorspace::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::convert_colorspace<detail::ColorspaceType<Colorspace::`input_name`>, detail::ColorspaceType<Colorspace::`name`>>::convert;`
   }
   `
         }
         break;`
}`
   }
   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::unknown>>::convert;
}
]], 'convert_colorspace_func')

write_template 'convert_colorspace_func' !! 536 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
ImagePixelNormTransformFunc convert_colorspace_func(Colorspace input, Colorspace output) {
   switch (input) {
      case Colorspace::unknown:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::linear_other:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_other>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::linear_depth_stencil:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::linear_depth_stencil>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_linear_rgb:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_rgb>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_linear_hsl:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsl>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_linear_hsv:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_hsv>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_linear_ycbcr:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_rgb:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_rgb>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_hsl:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsl>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_hsv:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_hsv>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::bt709_ycbcr:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::bt709_ycbcr>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::srgb:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::srgb_hsl:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsl>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::srgb_hsv:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_hsv>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::srgb_ycbcr:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::srgb_ycbcr>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_xyz:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyz>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_lab_d65:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lab_d65>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_lchab_d65:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchab_d65>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_luv_d65:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_luv_d65>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_lchuv_d65:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_lchuv_d65>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
      case Colorspace::cie_xyy:
         switch (output) {
            case Colorspace::unknown:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::unknown>>::convert;
            case Colorspace::linear_other:         return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::linear_other>>::convert;
            case Colorspace::linear_depth_stencil: return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::linear_depth_stencil>>::convert;
            case Colorspace::bt709_linear_rgb:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::bt709_linear_rgb>>::convert;
            case Colorspace::bt709_linear_hsl:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::bt709_linear_hsl>>::convert;
            case Colorspace::bt709_linear_hsv:     return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::bt709_linear_hsv>>::convert;
            case Colorspace::bt709_linear_ycbcr:   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::bt709_linear_ycbcr>>::convert;
            case Colorspace::bt709_rgb:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::bt709_rgb>>::convert;
            case Colorspace::bt709_hsl:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::bt709_hsl>>::convert;
            case Colorspace::bt709_hsv:            return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::bt709_hsv>>::convert;
            case Colorspace::bt709_ycbcr:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::bt709_ycbcr>>::convert;
            case Colorspace::srgb:                 return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::srgb>>::convert;
            case Colorspace::srgb_hsl:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::srgb_hsl>>::convert;
            case Colorspace::srgb_hsv:             return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::srgb_hsv>>::convert;
            case Colorspace::srgb_ycbcr:           return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::srgb_ycbcr>>::convert;
            case Colorspace::cie_xyz:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::cie_xyz>>::convert;
            case Colorspace::cie_lab_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::cie_lab_d65>>::convert;
            case Colorspace::cie_lchab_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::cie_lchab_d65>>::convert;
            case Colorspace::cie_luv_d65:          return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::cie_luv_d65>>::convert;
            case Colorspace::cie_lchuv_d65:        return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::cie_lchuv_d65>>::convert;
            case Colorspace::cie_xyy:              return detail::convert_colorspace<detail::ColorspaceType<Colorspace::cie_xyy>, detail::ColorspaceType<Colorspace::cie_xyy>>::convert;
         }
         break;
   }
   return detail::convert_colorspace<detail::ColorspaceType<Colorspace::unknown>, detail::ColorspaceType<Colorspace::unknown>>::convert;
}

/* ######################### END OF GENERATED CODE ######################### */

///////////////////////////////////////////////////////////////////////////////
vec4 convert_colorspace(vec4 pixel_norm, Colorspace input, Colorspace output) {
   return convert_colorspace_func(input, output)(pixel_norm);
}

} // be::gfx
