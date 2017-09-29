#ifdef BE_TEST

#include "tostring.hpp"
#include "tex/image_region.hpp"
#include "tex/image_region_hash.hpp"
#include "tex/make_image.hpp"
#include <be/core/extents.hpp>
#include <catch/catch.hpp>
#include <unordered_set>
#include <sstream>
#include <iomanip>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageRegion]"

using namespace be;
using namespace be::gfx::tex;

TEST_CASE("std::hash<ImageRegion>", BE_CATCH_TAGS) {
   std::unordered_set<ImageRegion> stet3;
   stet3.emplace();
}

TEST_CASE("ImageRegion default construction", BE_CATCH_TAGS) {
   ImageRegion region;

   REQUIRE(region.extents() == ibox());
   REQUIRE(region.x_basis() == ImageRegion::basis::pos_x);
   REQUIRE(region.y_basis() == ImageRegion::basis::pos_y);
   REQUIRE(region.z_basis() == ImageRegion::basis::pos_z);
   REQUIRE(region == ImageRegion());
}

TEST_CASE("ImageRegion direct construction", BE_CATCH_TAGS) {
   using basis = ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   REQUIRE(region.extents() == extents);
   REQUIRE(region.x_basis() == ImageRegion::basis::pos_y);
   REQUIRE(region.y_basis() == ImageRegion::basis::neg_x);
   REQUIRE(region.z_basis() == ImageRegion::basis::neg_z);
   REQUIRE(region == region);
   REQUIRE(region != ImageRegion());
   REQUIRE(region == ImageRegion(region));
}

TEST_CASE("ImageRegion from ImageView", BE_CATCH_TAGS) {
   ImageFormat format(U8(32), 2, BlockPacking::s_8_8_8_8, 4, field_types(FieldType::unorm, 4),
                           swizzles_rgba(), Colorspace::srgb, false);

   const int dim = 4;
   Image img = make_image(format, ivec3(dim));

   ImageRegion region = pixel_region(img.view);

   REQUIRE(region.extents() == make_extents(ivec3(), img.view.dim()));
   REQUIRE(region.x_basis() == ImageRegion::basis::pos_x);
   REQUIRE(region.y_basis() == ImageRegion::basis::pos_y);
   REQUIRE(region.z_basis() == ImageRegion::basis::pos_z);

   region = block_region(img.view);

   REQUIRE(region.extents() == make_extents(ivec3(), img.view.dim_blocks()));
   REQUIRE(region.x_basis() == ImageRegion::basis::pos_x);
   REQUIRE(region.y_basis() == ImageRegion::basis::pos_y);
   REQUIRE(region.z_basis() == ImageRegion::basis::pos_z);
}

TEST_CASE("region_dim(ImageRegion)", BE_CATCH_TAGS) {
   using basis = ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   REQUIRE(region_dim(region) == ivec3(7, 13, 2));
}

TEST_CASE("subregion(ImageRegion, ibox)", BE_CATCH_TAGS) {
   using basis = ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   ImageRegion sub = subregion(region, ibox { ivec3(4,3,2), ivec3(3, 2, 1) });

   REQUIRE(sub.basis_vec() == region.basis_vec());
   REQUIRE(sub.extents() == make_extents(ivec3(9, 6, 2), ivec3(2, 3, 1)));
}

TEST_CASE("subregion(ImageRegion, ibox, basis, basis, basis)", BE_CATCH_TAGS) {
   using basis = ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   ImageRegion sub = subregion(region, ibox { ivec3(4,3,2), ivec3(3, 2, 1) }, basis::neg_y, basis::pos_x, basis::neg_z);

   REQUIRE(sub.x_basis() == ImageRegion::basis::pos_x);
   REQUIRE(sub.y_basis() == ImageRegion::basis::pos_y);
   REQUIRE(sub.z_basis() == ImageRegion::basis::pos_z);
   REQUIRE(sub.extents() == make_extents(ivec3(9, 6, 2), ivec3(2, 3, 1)));
}

TEST_CASE("rotate(ImageRegion, basis)", BE_CATCH_TAGS) {
   using basis = ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   ImageRegion region(extents);

   ImageRegion rotated = rotate(region);
   REQUIRE(rotated.x_basis() == ImageRegion::basis::neg_x);
   REQUIRE(rotated.y_basis() == ImageRegion::basis::neg_y);
   REQUIRE(rotated.z_basis() == ImageRegion::basis::pos_z);
   REQUIRE(rotated.extents() == region.extents());
   REQUIRE(region_dim(rotated) == region_dim(region));

   rotated = rotate(region, ImageRegion::basis::pos_x);
   REQUIRE(rotated.x_basis() == ImageRegion::basis::pos_x);
   REQUIRE(rotated.y_basis() == ImageRegion::basis::neg_y);
   REQUIRE(rotated.z_basis() == ImageRegion::basis::neg_z);
   REQUIRE(rotated.extents() == region.extents());
   REQUIRE(region_dim(rotated) == region_dim(region));
}

TEST_CASE("rotate_cw(ImageRegion, basis)", BE_CATCH_TAGS) {
   using basis = ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   ImageRegion region(extents);

   ImageRegion rotated = rotate_cw(region);
   REQUIRE(rotated.x_basis() == ImageRegion::basis::pos_y);
   REQUIRE(rotated.y_basis() == ImageRegion::basis::neg_x);
   REQUIRE(rotated.z_basis() == ImageRegion::basis::pos_z);
   REQUIRE(rotated.extents() == region.extents());
   REQUIRE(region_dim(rotated) == ivec3(7, 13, 2));

   REQUIRE(region == rotate_ccw(rotated));
   REQUIRE(rotate(region) == rotate_cw(rotated));
   REQUIRE(rotate_cw(region, ImageRegion::basis::pos_x) == rotate_ccw(region, ImageRegion::basis::neg_x));
}

TEST_CASE("region_to_image(ImageRegion, ivec3)", BE_CATCH_TAGS) {
   using basis = ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   REQUIRE(region_to_image(region, ivec3()) == ivec3(13, 2, 4));
   REQUIRE(region_to_image(region, ivec3(1)) == ivec3(12, 3, 3));
   REQUIRE(region_to_image(region, ivec3(1, 0, 0)) == ivec3(13, 3, 4));
   REQUIRE(region_to_image(region, ivec3(0, 12, 0)) == ivec3(1, 2, 4));
   REQUIRE(region_to_image(region, ivec3(0, 0, 1)) == ivec3(13, 2, 3));
}

TEST_CASE("image_to_region(ivec3, ImageRegion)", BE_CATCH_TAGS) {
   using basis = ImageRegion::basis;
   ibox extents { ivec3(1, 2, 3), ivec3(13, 7, 2) };
   ImageRegion region(extents, basis::pos_y, basis::neg_x, basis::neg_z);

   REQUIRE(image_to_region(ivec3(), region) == ivec3(-2, 13, 4));
   REQUIRE(image_to_region(ivec3(1), region) == ivec3(-1, 12, 3));
   REQUIRE(image_to_region(ivec3(1, 0, 0), region) == ivec3(-2, 12, 4));
   REQUIRE(image_to_region(ivec3(0, 12, 0), region) == ivec3(10, 13, 4));
   REQUIRE(image_to_region(ivec3(0, 0, 1), region) == ivec3(-2, 13, 3));
}

#endif
