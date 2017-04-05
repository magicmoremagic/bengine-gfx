#pragma once
#ifndef BE_GFX_CONVERTING_PIXEL_BLITTER_HPP_
#define BE_GFX_CONVERTING_PIXEL_BLITTER_HPP_

#include "image_pixel_access_norm.hpp"
#include "convert_colorspace.hpp"
#include "premultiply_alpha.hpp"
#include "image_view.hpp"

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename SourceCoord, typename DestCoord, typename SourceImageView, typename DestImageView>
class ConvertingPixelBlitter final {
   using type = ConvertingPixelBlitter<SourceCoord, DestCoord, SourceImageView, DestImageView>;
   using get_func = GetPixelNormFunc<SourceCoord, SourceImageView>;
   using put_func = PutPixelNormFunc<DestCoord, DestImageView>;
   using convert_func = void (type::*)(SourceCoord, DestCoord);
public:
   ConvertingPixelBlitter(const SourceImageView& source, DestImageView& dest);

   void operator()(SourceCoord source, DestCoord dest) {
      (this->*convert_)(source, dest);
   }

private:
   void convert0_(SourceCoord source, DestCoord dest) {
      put_(dest_, dest, get_(source_, source));
   }
   void convert1_(SourceCoord source, DestCoord dest) {
      put_(dest_, dest, conversions_[0](get_(source_, source)));
   }
   void convert2_(SourceCoord source, DestCoord dest) {
      put_(dest_, dest, conversions_[1](conversions_[0](get_(source_, source))));
   }
   void convert3_(SourceCoord source, DestCoord dest) {
      put_(dest_, dest, conversions_[2](conversions_[1](conversions_[0](get_(source_, source)))));
   }

   const SourceImageView& source_;
   DestImageView& dest_;

   convert_func convert_;
   get_func get_;
   put_func put_;
   ImagePixelNormTransformFunc conversions_[3];
};

} // be::gfx

#include "converting_pixel_blitter.inl"

#endif
