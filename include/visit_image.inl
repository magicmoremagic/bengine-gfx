#if !defined(BE_GFX_VISIT_IMAGE_HPP_) && !defined(DOXYGEN)
#include "visit_image.hpp"
#elif !defined(BE_GFX_VISIT_IMAGE_INL_)
#define BE_GFX_VISIT_IMAGE_INL_

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_blocks_lineal(ImageView& image, Visitor visitor) {
   I32 bc;
   I32 dim = image.dim_blocks().x;
   for (bc = 0; bc < dim; ++bc) {
      visitor(image, bc);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_blocks_planar(ImageView& image, Visitor visitor) {
   ivec2 bc;
   ivec2 dim = ivec2(image.dim_blocks());
   for (bc.y = 0; bc.y < dim.y; ++bc.y) {
      for (bc.x = 0; bc.x < dim.x; ++bc.x) {
         visitor(image, bc);
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_blocks_volumetric(ImageView& image, Visitor visitor) {
   ivec3 bc;
   ivec3 dim = image.dim_blocks();
   for (bc.z = 0; bc.z < dim.z; ++bc.z) {
      for (bc.y = 0; bc.y < dim.y; ++bc.y) {
         for (bc.x = 0; bc.x < dim.x; ++bc.x) {
            visitor(image, bc);
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_pixels_lineal(ImageView& image, Visitor visitor) {
   I32 pc;
   I32 dim = image.dim().x;
   for (pc = 0; pc < dim; ++pc) {
      visitor(image, pc);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_pixels_planar(ImageView& image, Visitor visitor) {
   ivec2 pc;
   ivec2 dim = ivec2(image.dim());
   for (pc.y = 0; pc.y < dim.y; ++pc.y) {
      for (pc.x = 0; pc.x < dim.x; ++pc.x) {
         visitor(image, pc);
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Visitor>
void visit_image_pixels_volumetric(ImageView& image, Visitor visitor) {
   ivec3 pc;
   ivec3 dim = image.dim();
   for (pc.z = 0; pc.z < dim.z; ++pc.z) {
      for (pc.y = 0; pc.y < dim.y; ++pc.y) {
         for (pc.x = 0; pc.x < dim.x; ++pc.x) {
            visitor(image, pc);
         }
      }
   }
}

} // be::gfx

#endif
