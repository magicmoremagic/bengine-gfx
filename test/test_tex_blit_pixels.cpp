#ifdef BE_TEST

#include "tostring.hpp"
#include "tex/image.hpp"
#include "tex/image_format_gl.hpp"
#include "tex/make_image.hpp"
#include "tex/pixel_access.hpp"
#include "tex/blit_pixels.hpp"
#include "tex/visit_image.hpp"

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageView]"

using namespace be;
using namespace be::gfx::tex;

TEST_CASE("ImageView blit_pixels(ImageView, ImageView)", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, field_types(FieldType::unorm, 4),
                      swizzles_rgba(), Colorspace::srgb, false);

   ivec3 dim(4);
   Image img = make_image(format, ivec3(dim));

   auto get = get_pixel_func<RGBA, ivec3>(img.view);
   auto put = put_pixel_func<RGBA, ivec3>(img.view);
   visit_image_pixels<ivec3>(img.view, [put](ImageView& view, ivec3 pc) {
      put(view, pc, RGBA(RGB(pc * 64), 255u));
   });

   SECTION("Same format, dim") {
      Image img2 = make_image(format, ivec3(dim));

      blit_pixels(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different block size") {
      Image img2;
      img2.storage = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), U8(format.block_size() * 2));
      img2.view = ImageView(format, *img2.storage, 0, 0, 0);

      blit_pixels(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different line alignment") {
      Image img2;
      img2.storage = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), format.block_size(), TextureAlignment((U8)128));
      img2.view = ImageView(format, *img2.storage, 0, 0, 0);

      blit_pixels(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different plane alignment") {
      Image img2;
      img2.storage = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), format.block_size(), TextureAlignment((U8)8, (U8)128));
      img2.view = ImageView(format, *img2.storage, 0, 0, 0);

      blit_pixels(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different dim") {
      Image img2 = make_image(format, ivec3(dim) + 1);

      blit_pixels(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

}

TEST_CASE("ImageView blit_pixels(ImageView, ImageRegion, ImageView, ImageRegion)", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, field_types(FieldType::unorm, 4),
                      swizzles_rgba(), Colorspace::srgb, false);

   ivec3 dim(4);
   Image img = make_image(format, ivec3(dim));

   auto get = get_pixel_func<RGBA, ivec3>(img.view);
   auto put = put_pixel_func<RGBA, ivec3>(img.view);
   visit_image_pixels<ivec3>(img.view, [put](ImageView& view, ivec3 pc) {
      put(view, pc, RGBA(RGB(pc * 64), 255u));
   });

   ImageRegion region = rotate_cw(pixel_region(img.view));

   SECTION("Same format, dim, unrotated") {
      Image img2 = make_image(format, ivec3(dim));

      blit_pixels(img.view, pixel_region(img.view), img2.view, pixel_region(img2.view));

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, dim") {
      Image img2 = make_image(format, ivec3(dim));

      blit_pixels(img.view, region, img2.view, pixel_region(img2.view));

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, region, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, region_to_image(region, pc)) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different block size") {
      Image img2;
      img2.storage = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), U8(format.block_size() * 2));
      img2.view = ImageView(format, *img2.storage, 0, 0, 0);

      blit_blocks(img.view, region, img2.view, pixel_region(img2.view));

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, region, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, region_to_image(region, pc)) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different dim") {
      Image img2 = make_image(format, ivec3(dim) + 1);

      blit_pixels(img.view, region, img2.view, pixel_region(img2.view));

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, region, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, region_to_image(region, pc)) == get2(img2.view, pc));
      });
   }

}

#endif
