#ifdef BE_TEST

#include "image_region.hpp"
#include "image_region_hash.hpp"
#include "make_image.hpp"
#include <be/core/extents.hpp>
#include <catch/catch.hpp>
#include <unordered_set>
#include <sstream>
#include <iomanip>

#define BE_CATCH_TAGS "[gfx][gfx:ImageRegion]"

using namespace be;

namespace Catch {

std::string toString(be::ivec3 value) {
   std::ostringstream oss;
   oss << "vec3(" << value.x << ", " << value.y << ", " << value.z << ")";
   return oss.str();
}

std::string toString(const be::ibox& value) {
   std::ostringstream oss;
   oss << "ibox[ (" << value.offset.x << ", " << value.offset.y << ", " << value.offset.z
       << "), ("    << value.dim.x << ", " << value.dim.y << ", " << value.dim.z << ") ]";
   return oss.str();
}

} // Catch

TEST_CASE("std::hash<ImageRegion>", BE_CATCH_TAGS) {
   std::unordered_set<be::gfx::ImageRegion> stet3;
   stet3.emplace();
}

TEST_CASE("ImageRegion default construction", BE_CATCH_TAGS) {
   gfx::ImageRegion region;

   REQUIRE(region.extents() == ibox());
   REQUIRE(region.x_basis() == gfx::ImageRegion::pos_x);
   REQUIRE(region.y_basis() == gfx::ImageRegion::pos_y);
   REQUIRE(region.z_basis() == gfx::ImageRegion::pos_z);
   REQUIRE(region == gfx::ImageRegion());
}

TEST_CASE("ImageRegion direct construction", BE_CATCH_TAGS) {
   using basis = gfx::ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   gfx::ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   REQUIRE(region.extents() == extents);
   REQUIRE(region.x_basis() == gfx::ImageRegion::pos_y);
   REQUIRE(region.y_basis() == gfx::ImageRegion::neg_x);
   REQUIRE(region.z_basis() == gfx::ImageRegion::neg_z);
   REQUIRE(region == region);
   REQUIRE(region != gfx::ImageRegion());
   REQUIRE(region == gfx::ImageRegion(region));
}

TEST_CASE("ImageRegion from ImageView", BE_CATCH_TAGS) {
   gfx::ImageFormat format(U8(4), 1, gfx::ImageBlockPacking::s_8_8_8_8, 4, gfx::component_types(gfx::ImageComponentType::unorm, 4),
                           gfx::swizzles_rgba(), gfx::Colorspace::srgb, false);

   const int dim = 4;
   gfx::Image img = gfx::make_image(format, ivec3(dim));

   gfx::ImageRegion region(img.view);

   REQUIRE(region.extents() == make_extents(ivec3(), img.view.dim()));
   REQUIRE(region.x_basis() == gfx::ImageRegion::pos_x);
   REQUIRE(region.y_basis() == gfx::ImageRegion::pos_y);
   REQUIRE(region.z_basis() == gfx::ImageRegion::pos_z);
}

TEST_CASE("region_dim(ImageRegion)", BE_CATCH_TAGS) {
   using basis = gfx::ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   gfx::ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   REQUIRE(gfx::region_dim(region) == ivec3(7, 13, 2));
}

TEST_CASE("subregion(ImageRegion, ibox)", BE_CATCH_TAGS) {
   using basis = gfx::ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   gfx::ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   gfx::ImageRegion subregion = gfx::subregion(region, ibox { ivec3(4,3,2), ivec3(3, 2, 1) });

   REQUIRE(subregion.basis_vec() == region.basis_vec());
   REQUIRE(subregion.extents() == make_extents(ivec3(9, 6, 2), ivec3(2, 3, 1)));
}

TEST_CASE("subregion(ImageRegion, ibox, basis, basis, basis)", BE_CATCH_TAGS) {
   using basis = gfx::ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   gfx::ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   gfx::ImageRegion subregion = gfx::subregion(region, ibox { ivec3(4,3,2), ivec3(3, 2, 1) }, basis::neg_y, basis::pos_x, basis::neg_z);

   REQUIRE(subregion.x_basis() == gfx::ImageRegion::pos_x);
   REQUIRE(subregion.y_basis() == gfx::ImageRegion::pos_y);
   REQUIRE(subregion.z_basis() == gfx::ImageRegion::pos_z);
   REQUIRE(subregion.extents() == make_extents(ivec3(9, 6, 2), ivec3(2, 3, 1)));
}

TEST_CASE("rotate(ImageRegion, basis)", BE_CATCH_TAGS) {
   using basis = gfx::ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   gfx::ImageRegion region(extents);

   gfx::ImageRegion rotated = gfx::rotate(region);
   REQUIRE(rotated.x_basis() == gfx::ImageRegion::neg_x);
   REQUIRE(rotated.y_basis() == gfx::ImageRegion::neg_y);
   REQUIRE(rotated.z_basis() == gfx::ImageRegion::pos_z);
   REQUIRE(rotated.extents() == region.extents());
   REQUIRE(gfx::region_dim(rotated) == gfx::region_dim(region));

   rotated = gfx::rotate(region, gfx::ImageRegion::pos_x);
   REQUIRE(rotated.x_basis() == gfx::ImageRegion::pos_x);
   REQUIRE(rotated.y_basis() == gfx::ImageRegion::neg_y);
   REQUIRE(rotated.z_basis() == gfx::ImageRegion::neg_z);
   REQUIRE(rotated.extents() == region.extents());
   REQUIRE(gfx::region_dim(rotated) == gfx::region_dim(region));
}

TEST_CASE("rotate_cw(ImageRegion, basis)", BE_CATCH_TAGS) {
   using basis = gfx::ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   gfx::ImageRegion region(extents);

   gfx::ImageRegion rotated = gfx::rotate_cw(region);
   REQUIRE(rotated.x_basis() == gfx::ImageRegion::pos_y);
   REQUIRE(rotated.y_basis() == gfx::ImageRegion::neg_x);
   REQUIRE(rotated.z_basis() == gfx::ImageRegion::pos_z);
   REQUIRE(rotated.extents() == region.extents());
   REQUIRE(gfx::region_dim(rotated) == ivec3(7, 13, 2));

   REQUIRE(region == gfx::rotate_ccw(rotated));
   REQUIRE(gfx::rotate(region) == gfx::rotate_cw(rotated));
   REQUIRE(gfx::rotate_cw(region, gfx::ImageRegion::pos_x) == gfx::rotate_ccw(region, gfx::ImageRegion::neg_x));
}

TEST_CASE("region_to_image(ImageRegion, ivec3)", BE_CATCH_TAGS) {
   using basis = gfx::ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   gfx::ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   REQUIRE(gfx::region_to_image(region, ivec3()) == ivec3(13, 2, 4));
   REQUIRE(gfx::region_to_image(region, ivec3(1)) == ivec3(12, 3, 3));
   REQUIRE(gfx::region_to_image(region, ivec3(1, 0, 0)) == ivec3(13, 3, 4));
   REQUIRE(gfx::region_to_image(region, ivec3(0, 12, 0)) == ivec3(1, 2, 4));
   REQUIRE(gfx::region_to_image(region, ivec3(0, 0, 1)) == ivec3(13, 2, 3));
}

TEST_CASE("image_to_region(ivec3, ImageRegion)", BE_CATCH_TAGS) {
   using basis = gfx::ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   gfx::ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   REQUIRE(gfx::image_to_region(ivec3(), region) == ivec3(-2, 13, 4));
   REQUIRE(gfx::image_to_region(ivec3(1), region) == ivec3(-1, 12, 3));
   REQUIRE(gfx::image_to_region(ivec3(1, 0, 0), region) == ivec3(-2, 12, 4));
   REQUIRE(gfx::image_to_region(ivec3(0, 12, 0), region) == ivec3(10, 13, 4));
   REQUIRE(gfx::image_to_region(ivec3(0, 0, 1), region) == ivec3(-2, 13, 3));
}

#endif
