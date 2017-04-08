#if !defined(BE_GFX_TEX_IMAGE_REGION_HPP_) && !defined(DOXYGEN)
#include "image_region.hpp"
#elif !defined(BE_GFX_TEX_IMAGE_REGION_INL_)
#define BE_GFX_TEX_IMAGE_REGION_INL_

namespace be::gfx::tex {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, glm::length_t Components = t::vector_components<Coord>::value>
struct ImageRegionHelper { };

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
struct ImageRegionHelper<Coord, 1> {
   using basis = ImageRegion::basis;

   static ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents) {
      return tex::subregion(parent, ibox { ivec3((int)extents.offset, 1, 1), ivec3((int)extents.dim, 1, 1) });
   }

   static ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents, basis x_basis, basis y_basis, basis z_basis) {
      return tex::subregion(parent, ibox { ivec3((int)extents.offset, 1, 1), ivec3((int)extents.dim, 1, 1) }, x_basis, y_basis, z_basis);
   }

   static Coord region_to_image(ImageRegion region, Coord region_coord) {
      return Coord(tex::region_to_image(region, ivec3((int)region_coord, 0, 0)).x);
   }

   static Coord image_to_region(Coord image_coord, ImageRegion region) {
      return Coord(tex::image_to_region(ivec3((int)image_coord, 0, 0), region).x);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
struct ImageRegionHelper<Coord, 2> {
   using basis = ImageRegion::basis;

   static ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents) {
      return tex::subregion(parent, ibox {
         ivec3((int)extents.offset[0], (int)extents.offset[1], 1),
         ivec3((int)extents.dim[0], (int)extents.dim[1], 1)
      });
   }

   static ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents, basis x_basis, basis y_basis, basis z_basis) {
      return tex::subregion(parent, ibox {
         ivec3((int)extents.offset[0], (int)extents.offset[1], 1),
         ivec3((int)extents.dim[1], (int)extents.dim[1], 1)
      }, x_basis, y_basis, z_basis);
   }

   static Coord region_to_image(ImageRegion region, Coord region_coord) {
      using value_type = typename Coord::value_type;
      ivec3 image_coord = tex::region_to_image(region, ivec3((int)region_coord[0], (int)region_coord[1], 0));
      return Coord((value_type)image_coord.x, (value_type)image_coord.y);
   }

   static Coord image_to_region(Coord image_coord, ImageRegion region) {
      using value_type = typename Coord::value_type;
      ivec3 region_coord = tex::region_to_image(region, ivec3((int)image_coord[0], (int)image_coord[1], 0));
      return Coord((value_type)region_coord.x, (value_type)region_coord.y);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
struct ImageRegionHelper<Coord, 3> {
   using basis = ImageRegion::basis;

   static ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents) {
      return tex::subregion(parent, ibox {
         ivec3((int)extents.offset[0], (int)extents.offset[1], (int)extents.offset[2]),
         ivec3((int)extents.dim[0], (int)extents.dim[1], (int)extents.dim[2])
      });
   }

   static ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents, basis x_basis, basis y_basis, basis z_basis) {
      return tex::subregion(parent, ibox {
         ivec3((int)extents.offset[0], (int)extents.offset[1], (int)extents.offset[2]),
         ivec3((int)extents.dim[1], (int)extents.dim[1], (int)extents.dim[2])
      }, x_basis, y_basis, z_basis);
   }

   static Coord region_to_image(ImageRegion region, Coord region_coord) {
      using value_type = typename Coord::value_type;
      ivec3 image_coord = tex::region_to_image(region, ivec3((int)region_coord[0], (int)region_coord[1], (int)region_coord[2]));
      return Coord((value_type)image_coord.x, (value_type)image_coord.y, (value_type)image_coord.z);
   }

   static Coord image_to_region(Coord image_coord, ImageRegion region) {
      using value_type = typename Coord::value_type;
      ivec3 region_coord = tex::region_to_image(region, ivec3((int)image_coord[0], (int)image_coord[1], (int)region_coord[2]));
      return Coord((value_type)region_coord.x, (value_type)region_coord.y, (value_type)region_coord.z);
   }
};

} // be::gfx::tex::detail

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents) {
   return detail::ImageRegionHelper<Coord>::subregion(parent, extents);
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents, ImageRegion::basis x_basis, ImageRegion::basis y_basis, ImageRegion::basis z_basis) {
   return detail::ImageRegionHelper<Coord>::subregion(parent, extents, x_basis, y_basis, z_basis);
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
Coord region_to_image(ImageRegion region, Coord region_coord) {
   return detail::ImageRegionHelper<Coord>::region_to_image(region, region_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
Coord image_to_region(Coord image_coord, ImageRegion region) {
   return detail::ImageRegionHelper<Coord>::image_to_region(image_coord, region);
}

} // be::gfx::tex

#endif
