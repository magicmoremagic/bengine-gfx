#ifdef BE_TEST

#include "tostring.hpp"
#include "tex/image.hpp"
#include "tex/make_image.hpp"
#include "tex/pixel_access.hpp"
#include "tex/visit_image.hpp"
#include <glm/glm.hpp>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageView]"

using namespace be;
using namespace be::gfx::tex;

TEST_CASE("ImageView pixel access (simple)", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, field_types(FieldType::unorm, 4),
                           swizzles_rgba(), Colorspace::srgb, false);

   const int dim = 4;
   Image img = make_image(format, ivec3(dim));

   SECTION("lineal") {
      SECTION("func") {
         auto get = get_pixel_func<RGBA, I32>(img.view);
         auto put = put_pixel_func<RGBA, I32>(img.view);
         visit_image_pixels<I32>(img.view, [put](ImageView& view, I32 pc) {
            put(view, pc, RGBA(pc, pc * 2, pc * 4, 13u));
         });
         visit_image_pixels<I32>(img.view, [get](ImageView& view, I32 pc) {
            REQUIRE(get(view, pc) == RGBA(pc, pc * 2, pc * 4, 13u));
         });
      }
      SECTION("helper") {
         visit_image_pixels<I32>(img.view, [](ImageView& view, I32 pc) {
            put_pixel(view, pc, RGBA(pc, pc * 2, pc * 4, 13u));
         });
         visit_image_pixels<I32>(img.view, [](ImageView& view, I32 pc) {
            REQUIRE(get_pixel<RGBA>(view, pc) == RGBA(pc, pc * 2, pc * 4, 13u));
         });
      }
   }

   SECTION("planar") {
      SECTION("func") {
         auto get = get_pixel_func<RGBA, ivec2>(img.view);
         auto put = put_pixel_func<RGBA, ivec2>(img.view);
         visit_image_pixels<ivec2>(img.view, [put](ImageView& view, ivec2 pc) {
            put(view, pc, RGBA(pc.x * 64, pc.y * 64, 0, 13u));
         });
         visit_image_pixels<ivec2>(img.view, [get](ImageView& view, ivec2 pc) {
            REQUIRE(get(view, pc) == RGBA(pc.x * 64, pc.y * 64, 0, 13u));
         });
      }
      SECTION("helper") {
         visit_image_pixels<ivec2>(img.view, [](ImageView& view, ivec2 pc) {
            put_pixel(view, pc, RGBA(pc.x * 64, pc.y * 64, 0, 13u));
         });
         visit_image_pixels<ivec2>(img.view, [](ImageView& view, ivec2 pc) {
            REQUIRE(get_pixel<RGBA>(view, pc) == RGBA(pc.x * 64, pc.y * 64, 0, 13u));
         });
      }
   }

   SECTION("volumetric") {
      SECTION("func") {
         auto get = get_pixel_func<RGBA, ivec3>(img.view);
         auto put = put_pixel_func<RGBA, ivec3>(img.view);
         visit_image_pixels<ivec3>(img.view, [put](ImageView& view, ivec3 pc) {
            put(view, pc, RGBA(glm::u8vec3(pc * 64), 13u));
         });
         visit_image_pixels<ivec3>(img.view, [get](ImageView& view, ivec3 pc) {
            REQUIRE(get(view, pc) == RGBA(glm::u8vec3(pc * 64), 13u));
         });
      }
      SECTION("helper") {
         visit_image_pixels<ivec3>(img.view, [](ImageView& view, ivec3 pc) {
            put_pixel(view, pc, RGBA(glm::u8vec3(pc * 64), 13u));
         });
         visit_image_pixels<ivec3>(img.view, [](ImageView& view, ivec3 pc) {
            REQUIRE(get_pixel<RGBA>(view, pc) == RGBA(glm::u8vec3(pc * 64), 13u));
         });
      }
   }
}

TEST_CASE("ImageView pixel access (packed block)", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, field_types(FieldType::unorm, 4),
                           swizzles_rgba(), Colorspace::srgb, false);

   const int dim = 4;
   Image img = make_image(format, ivec3(dim));

   SECTION("lineal") {
      SECTION("func") {
         auto get = get_pixel_func<RGBA, I32>(img.view);
         auto put = put_pixel_func<RGBA, I32>(img.view);
         int tc;
         for (tc = 0; tc < dim; ++tc) {
            put(img.view, tc, RGBA(tc, tc * 2, tc * 4, 13u));
         }
         for (tc = 0; tc < dim; ++tc) {
            REQUIRE(get(img.view, tc) == RGBA(tc, tc * 2, tc * 4, 13u));
         }
      }
      SECTION("helper") {
         int tc;
         for (tc = 0; tc < dim; ++tc) {
            put_pixel(img.view, tc, RGBA(tc, tc * 2, tc * 4, 13u));
         }
         for (tc = 0; tc < dim; ++tc) {
            REQUIRE(get_pixel<RGBA>(img.view, tc) == RGBA(tc, tc * 2, tc * 4, 13u));
         }
      }
   }

   SECTION("planar") {
      SECTION("func") {
         auto get = get_pixel_func<RGBA, ivec2>(img.view);
         auto put = put_pixel_func<RGBA, ivec2>(img.view);
         ivec2 tc;
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               put(img.view, tc, RGBA(tc.x * 64, tc.y * 64, 0, 13u));
            }
         }
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(get(img.view, tc) == RGBA(tc.x * 64, tc.y * 64, 0, 13u));
            }
         }
      }
      SECTION("helper") {
         ivec2 tc;
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               put_pixel(img.view, tc, RGBA(tc.x * 64, tc.y * 64, 0, 13u));
            }
         }
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(get_pixel<RGBA>(img.view, tc) == RGBA(tc.x * 64, tc.y * 64, 0, 13u));
            }
         }
      }
   }

   SECTION("volumetric") {
      SECTION("func") {
         auto get = get_pixel_func<RGBA, ivec3>(img.view);
         auto put = put_pixel_func<RGBA, ivec3>(img.view);
         ivec3 tc;
         for (tc.z = 0; tc.z < dim; ++tc.z) {
            for (tc.y = 0; tc.y < dim; ++tc.y) {
               for (tc.x = 0; tc.x < dim; ++tc.x) {
                  put(img.view, tc, RGBA(glm::u8vec3(tc * 64), 13u));
               }
            }
         }
         for (tc.z = 0; tc.z < dim; ++tc.z) {
            for (tc.y = 0; tc.y < dim; ++tc.y) {
               for (tc.x = 0; tc.x < dim; ++tc.x) {
                  REQUIRE(get(img.view, tc) == RGBA(glm::u8vec3(tc * 64), 13u));
               }
            }
         }
      }
      SECTION("helper") {
         ivec3 tc;
         for (tc.z = 0; tc.z < dim; ++tc.z) {
            for (tc.y = 0; tc.y < dim; ++tc.y) {
               for (tc.x = 0; tc.x < dim; ++tc.x) {
                  put_pixel(img.view, tc, RGBA(glm::u8vec3(tc * 64), 13u));
               }
            }
         }
         for (tc.z = 0; tc.z < dim; ++tc.z) {
            for (tc.y = 0; tc.y < dim; ++tc.y) {
               for (tc.x = 0; tc.x < dim; ++tc.x) {
                  REQUIRE(get_pixel<RGBA>(img.view, tc) == RGBA(glm::u8vec3(tc * 64), 13u));
               }
            }
         }
      }
   }
}

#endif
