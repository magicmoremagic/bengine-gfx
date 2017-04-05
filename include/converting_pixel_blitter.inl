#if !defined(BE_GFX_CONVERTING_PIXEL_BLITTER_HPP_) && !defined(DOXYGEN)
#include "converting_pixel_blitter.hpp"
#elif !defined(BE_GFX_CONVERTING_PIXEL_BLITTER_INL_)
#define BE_GFX_CONVERTING_PIXEL_BLITTER_INL_

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename SourceCoord, typename DestCoord, typename SourceImageView, typename DestImageView>
ConvertingPixelBlitter<SourceCoord, DestCoord, SourceImageView, DestImageView>::
ConvertingPixelBlitter(const SourceImageView& source, DestImageView& dest)
   : source_(source),
     dest_(dest),
     get_(get_pixel_norm_func<SourceCoord, SourceImageView>(source)),
     put_(put_pixel_norm_func<DestCoord, DestImageView>(dest)) {
   Colorspace source_color = source.format().colorspace();
   Colorspace dest_color = dest.format().colorspace();

   bool source_premult = source.format().premultiplied();
   bool dest_premult = dest.format().premultiplied();

   if (source_premult != dest_premult) {
      if (is_linear(source_color)) {
         if (source_color != dest_color) {
            conversions_[0] = convert_premultiplication_func(source_premult, dest_premult);
            conversions_[1] = convert_colorspace_func(source_color, dest_color);
            convert_ = &convert2_;
         } else {
            conversions_[0] = convert_premultiplication_func(source_premult, dest_premult);
            convert_ = &convert1_;
         }
      } else if (is_linear(dest_color)) {
         // we know dest_color != source_color, otherwise the is_linear(source_color) would have been true
         conversions_[0] = convert_colorspace_func(source_color, dest_color);
         conversions_[1] = convert_premultiplication_func(source_premult, dest_premult);
         convert_ = &convert2_;
      } else {
         // we know we need 3 conversions here because we know source_color and dest_color are both nonlinear
         Colorspace linear_source_color = linear_colorspace(colorspace_family(source_color));
         conversions_[0] = convert_colorspace_func(source_color, linear_source_color);
         conversions_[1] = convert_premultiplication_func(source_premult, dest_premult);
         conversions_[2] = convert_colorspace_func(linear_source_color, dest_color);
         convert_ = &convert3_;
      }
   } else {
      if (source_color != dest_color) {
         conversions_[0] = convert_colorspace_func(source_color, dest_color);
         convert_ = &convert1_;
      } else {
         convert_ = &convert0_;
      }
   }
}

} // be::gfx

#endif
