#ifdef BE_TEST

#include "tostring.hpp"
#include "tex/image.hpp"
#include "tex/make_image.hpp"
#include "tex/block_access.hpp"
#include "tex/visit_image.hpp"

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageView]"

using namespace be;
using namespace be::gfx::tex;

TEST_CASE("ImageView block access", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, field_types(FieldType::unorm, 4),
                      swizzles_rgba(), Colorspace::srgb, false);

   const int dim = 4;
   Image img = make_image(format, ivec3(dim));

   SECTION("lineal") {
      int tc;
      for (tc = 0; tc < dim; ++tc) {
         put_block(img.view, tc, RGBA(tc, tc * 2, tc * 4, 13u));
      }
      for (tc = 0; tc < dim; ++tc) {
         REQUIRE(get_block<RGBA>(img.view, tc) == RGBA(tc, tc * 2, tc * 4, 13u));
      }
   }

   SECTION("planar") {
      ivec2 tc;
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            put_block(img.view, tc, RGBA(tc.x * 64, tc.y * 64, 0, 13u));
         }
      }
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            REQUIRE(get_block<RGBA>(img.view, tc) == RGBA(tc.x * 64, tc.y * 64, 0, 13u));
         }
      }
   }

   SECTION("volumetric") {
      ivec3 tc;
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               put_block(img.view, tc, RGBA(glm::u8vec3(tc * 64), 13u));
            }
         }
      }
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(get_block<RGBA>(img.view, tc) == RGBA(glm::u8vec3(tc * 64), 13u));
            }
         }
      }
   }
}

#endif
