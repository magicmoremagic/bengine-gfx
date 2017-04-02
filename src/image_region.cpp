#include "pch.hpp"
#include "image_region.hpp"

namespace be::gfx {
namespace {

///////////////////////////////////////////////////////////////////////////////
ImageRegion::basis pos_basis(ImageRegion::basis b) {
   switch (b) {
      case ImageRegion::pos_x: return ImageRegion::pos_x;
      case ImageRegion::pos_y: return ImageRegion::pos_y;
      case ImageRegion::pos_z: return ImageRegion::pos_z;
      case ImageRegion::neg_x: return ImageRegion::pos_x;
      case ImageRegion::neg_y: return ImageRegion::pos_y;
      case ImageRegion::neg_z: return ImageRegion::pos_z;
   }
   return b;
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion::basis negate_basis(ImageRegion::basis b) {
   switch (b) {
      case ImageRegion::pos_x: return ImageRegion::neg_x;
      case ImageRegion::pos_y: return ImageRegion::neg_y;
      case ImageRegion::pos_z: return ImageRegion::neg_z;
      case ImageRegion::neg_x: return ImageRegion::pos_x;
      case ImageRegion::neg_y: return ImageRegion::pos_y;
      case ImageRegion::neg_z: return ImageRegion::pos_z;
   }
   return b;
}

///////////////////////////////////////////////////////////////////////////////
bool is_basis_negative(ImageRegion::basis b) {
   switch (b) {
      case ImageRegion::pos_x:
      case ImageRegion::pos_y:
      case ImageRegion::pos_z:
         return false;
      case ImageRegion::neg_x:
      case ImageRegion::neg_y:
      case ImageRegion::neg_z:
         return true;
   }
   return false;
}

} // be::gfx::()

///////////////////////////////////////////////////////////////////////////////
ImageRegion::ImageRegion()
   : basis_(pos_x, pos_y, pos_z) { }

///////////////////////////////////////////////////////////////////////////////
ImageRegion::ImageRegion(ibox extents)
   : extents_(extents),
     basis_(pos_x, pos_y, pos_z) { }

///////////////////////////////////////////////////////////////////////////////
ImageRegion::ImageRegion(ibox extents, basis x_basis, basis y_basis, basis z_basis)
   : extents_(extents),
     basis_(x_basis, y_basis, z_basis) { }

///////////////////////////////////////////////////////////////////////////////
ibox ImageRegion::extents() const {
   return extents_;
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion::basis_vec_type ImageRegion::basis_vec() const {
   return basis_;
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion::basis ImageRegion::x_basis() const {
   return (basis)basis_.x;
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion::basis ImageRegion::y_basis() const {
   return (basis)basis_.y;
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion::basis ImageRegion::z_basis() const {
   return (basis)basis_.z;
}

///////////////////////////////////////////////////////////////////////////////
bool ImageRegion::operator==(const ImageRegion& other) const {
   return extents_ == other.extents_ && basis_ == other.basis_;
}

///////////////////////////////////////////////////////////////////////////////
bool ImageRegion::operator!=(const ImageRegion& other) const {
   return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////////
ivec3 region_dim(ImageRegion region) {
   ibox extents = region.extents();
   return ivec3(extents.dim[pos_basis(region.x_basis())],
                extents.dim[pos_basis(region.y_basis())],
                extents.dim[pos_basis(region.z_basis())]);
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion subregion(ImageRegion parent, ibox extents) {
   ibox p1 { region_to_image(parent, extents.offset), ivec3(1) };
   ibox p2 { region_to_image(parent, extents.offset + extents.dim - 1), ivec3(1) };
   return ImageRegion(p1.union_bounds(p2), parent.x_basis(), parent.y_basis(), parent.z_basis());
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion subregion(ImageRegion parent, ibox extents, ImageRegion::basis x_basis, ImageRegion::basis y_basis, ImageRegion::basis z_basis) {
   using basis = ImageRegion::basis;
   using basis_vec_type = ImageRegion::basis_vec_type;

   basis_vec_type parent_basis = parent.basis_vec();
   
   basis x = (basis)parent_basis[pos_basis(x_basis)];
   basis y = (basis)parent_basis[pos_basis(y_basis)];
   basis z = (basis)parent_basis[pos_basis(z_basis)];

   if (is_basis_negative(x_basis)) x = negate_basis(x);
   if (is_basis_negative(y_basis)) y = negate_basis(y);
   if (is_basis_negative(z_basis)) z = negate_basis(z);

   ibox p1 { region_to_image(parent, extents.offset), ivec3(1) };
   ibox p2 { region_to_image(parent, extents.offset + extents.dim - 1), ivec3(1) };
   return ImageRegion(p1.union_bounds(p2), x, y, z);
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion rotate(ImageRegion region, ImageRegion::basis axis) {
   using basis = ImageRegion::basis;
   basis x, y, z;
   switch (pos_basis(axis)) {
      case basis::pos_x:
         x = region.x_basis();
         y = negate_basis(region.y_basis());
         z = negate_basis(region.z_basis());
         break;
      case basis::pos_y:
         x = negate_basis(region.x_basis());
         y = region.y_basis();
         z = negate_basis(region.z_basis());
         break;
      case basis::pos_z:
         x = negate_basis(region.x_basis());
         y = negate_basis(region.y_basis());
         z = region.z_basis();
         break;
      default:
         x = region.x_basis();
         y = region.y_basis();
         z = region.z_basis();
   }
   return ImageRegion(region.extents(), x, y, z);
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion rotate_cw(ImageRegion region, ImageRegion::basis axis) {
   if (is_basis_negative(axis)) {
      using basis = ImageRegion::basis;
      basis x, y, z;
      switch (axis) {
         case basis::neg_x:
            x = region.x_basis();
            y = region.z_basis();
            z = negate_basis(region.y_basis());
            break;
         case basis::neg_y:
            x = negate_basis(region.z_basis());
            y = region.y_basis();
            z = region.x_basis();
            break;
         case basis::neg_z:
            x = region.y_basis();
            y = negate_basis(region.x_basis());
            z = region.z_basis();
            break;
         default:
            x = region.x_basis();
            y = region.y_basis();
            z = region.z_basis();
      }
      return ImageRegion(region.extents(), x, y, z);
   } else {
      return rotate_ccw(region, negate_basis(axis));
   }
}

///////////////////////////////////////////////////////////////////////////////
ImageRegion rotate_ccw(ImageRegion region, ImageRegion::basis axis) {
   if (is_basis_negative(axis)) {
      using basis = ImageRegion::basis;
      basis x, y, z;
      switch (axis) {
         case basis::neg_x:
            x = region.x_basis();
            y = negate_basis(region.z_basis());
            z = region.y_basis();
            break;
         case basis::neg_y:
            x = region.z_basis();
            y = region.y_basis();
            z = negate_basis(region.x_basis());
            break;
         case basis::neg_z:
            x = negate_basis(region.y_basis());
            y = region.x_basis();
            z = region.z_basis();
            break;
         default:
            x = region.x_basis();
            y = region.y_basis();
            z = region.z_basis();
      }
      return ImageRegion(region.extents(), x, y, z);
   } else {
      return rotate_cw(region, negate_basis(axis));
   }
}

///////////////////////////////////////////////////////////////////////////////
ivec3 region_to_image(ImageRegion region, ivec3 region_coord) {
   using basis = ImageRegion::basis;

   ivec3 image_coord;
   ImageRegion::basis_vec_type region_basis = region.basis_vec();

   for (glm::length_t i = 0; i < 3; ++i) {
      basis b = (basis)region_basis[i];
      if (is_basis_negative(b)) {
         b = pos_basis(b);
         image_coord[b] = region.extents().dim[b] - 1 - region_coord[i];
      } else {
         image_coord[b] = region_coord[i];
      }
   }

   image_coord += region.extents().offset;
   return image_coord;
}

///////////////////////////////////////////////////////////////////////////////
ivec3 image_to_region(ivec3 image_coord, ImageRegion region) {
   using basis = ImageRegion::basis;

   ivec3 region_coord;
   image_coord -= region.extents().offset;
   ImageRegion::basis_vec_type region_basis = region.basis_vec();

   for (glm::length_t i = 0; i < 3; ++i) {
      basis b = (basis)region_basis[i];
      if (is_basis_negative(b)) {
         b = pos_basis(b);
         region_coord[i] = region.extents().dim[b] - 1 - image_coord[b];
      } else {
         region_coord[i] = image_coord[b];
      }
   }

   return region_coord;
}

} // be::gfx
