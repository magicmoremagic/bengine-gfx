#pragma once
#ifndef BE_GFX_CONVERTING_PIXEL_BLITTER_HPP_
#define BE_GFX_CONVERTING_PIXEL_BLITTER_HPP_

#include "image_pixel_access_norm.hpp"
#include "convert_colorspace.hpp"
#include "premultiply_alpha.hpp"
#include "image_view.hpp"

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename SourceCoord, typename DestCoord, typename SourceImageView, typename DestImageView = ImageView,
   typename GetFunc = GetImagePixelNormFunc<SourceImageView, SourceCoord>,
   typename PutFunc = PutImagePixelNormFunc<DestImageView, DestCoord>>
class ConvertingPixelBlitter final {
   using type = ConvertingPixelBlitter<SourceCoord, DestCoord, SourceImageView, DestImageView, GetFunc, PutFunc>;
public:
   ConvertingPixelBlitter(const SourceImageView& source, DestImageView& dest);

   void operator()(SourceCoord source, DestCoord dest);

private:
   void convert0_(SourceCoord source, DestCoord dest);
   void convert1_(SourceCoord source, DestCoord dest);
   void convert2_(SourceCoord source, DestCoord dest);
   void convert3_(SourceCoord source, DestCoord dest);

   using ConvertFunc = void (type::*)(SourceCoord, DestCoord);

   const SourceImageView& source_;
   DestImageView& dest_;

   ConvertFunc convert_;
   GetFunc get_;
   PutFunc put_;
   ImagePixelNormTransformFunc conversions_[3];
};

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
using ConvertingPixelBlitterLineal = ConvertingPixelBlitter<I32, I32, SourceImageView, DestImageView>;

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
using ConvertingPixelBlitterPlanar = ConvertingPixelBlitter<ivec2, ivec2, SourceImageView, DestImageView>;

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
using ConvertingPixelBlitterVolumetric = ConvertingPixelBlitter<ivec3, ivec3, SourceImageView, DestImageView>;

} // be::gfx

#include "converting_pixel_blitter.inl"

#endif
