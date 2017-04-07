#if !defined(BE_GFX_VISIT_IMAGE_HPP_) && !defined(DOXYGEN)
#include "visit_image.hpp"
#elif !defined(BE_GFX_VISIT_IMAGE_INL_)
#define BE_GFX_VISIT_IMAGE_INL_

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, typename Visitor, glm::length_t Dimension = t::vector_components<Coord>::value>
struct VisitImage { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, typename Visitor>
struct VisitImage<ImageView, Coord, Visitor, 1> {
   static void visit(ImageView& image, ibox extents, Visitor visitor) {
      Coord pc;
      Coord offset = Coord(extents.offset.x);
      Coord dim = offset + Coord(extents.dim.x);
      for (pc = offset; pc < dim; ++pc) {
         visitor(image, pc);
      }
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, typename Visitor>
struct VisitImage<ImageView, Coord, Visitor, 2> {
   static void visit(ImageView& image, ibox extents, Visitor visitor) {
      Coord pc;
      Coord offset = Coord(extents.offset);
      Coord dim = offset + Coord(extents.dim);
      for (pc.y = offset.y; pc.y < dim.y; ++pc.y) {
         for (pc.x = offset.x; pc.x < dim.x; ++pc.x) {
            visitor(image, pc);
         }
      }
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, typename Visitor>
struct VisitImage<ImageView, Coord, Visitor, 3> {
   static void visit(ImageView& image, ibox extents, Visitor visitor) {
      Coord pc;
      Coord offset = Coord(extents.offset);
      Coord dim = offset + extents.dim;
      for (pc.z = offset.z; pc.z < dim.z; ++pc.z) {
         for (pc.y = offset.y; pc.y < dim.y; ++pc.y) {
            for (pc.x = offset.x; pc.x < dim.x; ++pc.x) {
               visitor(image, pc);
            }
         }
      }
   }
};

} // be::gfx::detail

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename ImageView>
void visit_image_blocks(ImageView& image, Visitor visitor) {
   detail::VisitImage<ImageView, Coord, Visitor>::visit(image, ibox { ivec3(), image.dim_blocks() }, std::move(visitor));
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename ImageView>
void visit_image_blocks(ImageView& image, ibox block_extents, Visitor visitor) {
   assert(extents.left() >= 0);
   assert(extents.bottom() >= 0);
   assert(extents.back() >= 0);
   assert(extents.right() <= image.dim_blocks().x);
   assert(extents.top() <= image.dim_blocks().y);
   assert(extents.front() <= image.dim_blocks().z);
   detail::VisitImage<ImageView, Coord, Visitor>::visit(image, block_extents, std::move(visitor));
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename ImageView>
void visit_image_pixels(ImageView& image, Visitor visitor) {
   detail::VisitImage<ImageView, Coord, Visitor>::visit(image, ibox { ivec3(), image.dim() }, std::move(visitor));
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename ImageView>
void visit_image_pixels(ImageView& image, ibox extents, Visitor visitor) {
   assert(extents.left() >= 0);
   assert(extents.bottom() >= 0);
   assert(extents.back() >= 0);
   assert(extents.right() <= image.dim().x);
   assert(extents.top() <= image.dim().y);
   assert(extents.front() <= image.dim().z);
   detail::VisitImage<ImageView, Coord, Visitor>::visit(image, extents, std::move(visitor));
}

} // be::gfx

#endif
