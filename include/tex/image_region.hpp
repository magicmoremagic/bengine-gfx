#pragma once
#ifndef BE_GFX_TEX_IMAGE_REGION_HPP_
#define BE_GFX_TEX_IMAGE_REGION_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/extents.hpp>
#include <be/core/glm_helpers.hpp>
#include <glm/vec3.hpp>

namespace be::gfx::tex {

class ImageRegion final {
public:
   using basis_vec_type = glm::vec<3, U8>;

   enum basis : U8 {
      pos_x,
      pos_y,
      pos_z,
      neg_x,
      neg_y,
      neg_z
   };

   ImageRegion();
   ImageRegion(ibox extents);
   ImageRegion(ibox extents, basis x_basis, basis y_basis, basis z_basis);
   
   ibox extents() const;

   basis_vec_type basis_vec() const;

   basis x_basis() const;
   basis y_basis() const;
   basis z_basis() const;

   bool operator==(const ImageRegion& other) const;
   bool operator!=(const ImageRegion& other) const;

private:
   ibox extents_; // image-space coordinates
   basis_vec_type basis_;
};

template <typename ImageView>
ImageRegion pixel_region(const ImageView& image) {
   return ImageRegion(ibox { ivec3(), image.dim() });
}

template <typename ImageView>
ImageRegion block_region(const ImageView& image) {
   return ImageRegion(ibox { ivec3(), image.dim_blocks() });
}

ivec3 region_dim(ImageRegion region);

ImageRegion subregion(ImageRegion parent, ibox extents);
ImageRegion subregion(ImageRegion parent, ibox extents, ImageRegion::basis x_basis, ImageRegion::basis y_basis, ImageRegion::basis z_basis);

template <typename Coord>
ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents);

template <typename Coord>
ImageRegion subregion(ImageRegion parent, generic_extents<Coord, Coord> extents, ImageRegion::basis x_basis, ImageRegion::basis y_basis, ImageRegion::basis z_basis);

ImageRegion rotate(ImageRegion region, ImageRegion::basis axis = ImageRegion::neg_z);
ImageRegion rotate_cw(ImageRegion region, ImageRegion::basis axis = ImageRegion::neg_z);
ImageRegion rotate_ccw(ImageRegion region, ImageRegion::basis axis = ImageRegion::neg_z);

ivec3 region_to_image(ImageRegion region, ivec3 region_coord);
template <typename Coord> Coord region_to_image(ImageRegion region, Coord region_coord);

ivec3 image_to_region(ivec3 image_coord, ImageRegion region);
template <typename Coord> Coord image_to_region(Coord image_coord, ImageRegion region);

} // be::gfx::tex

#include "image_region.inl"

#endif
