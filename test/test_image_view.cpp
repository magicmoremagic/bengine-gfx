#ifdef BE_TEST

#include "image.hpp"
#include "image_view_hash.hpp"
#include "make_image.hpp"
#include "image_block_access.hpp"
#include <be/core/be.hpp>
#include <catch/catch.hpp>
#include <unordered_set>

#define BE_CATCH_TAGS "[gfx][gfx:ImageView]"

using namespace be;

TEST_CASE("std::hash<ImageView>", BE_CATCH_TAGS) {
   std::unordered_set<be::gfx::ImageView> stet3;
   stet3.emplace();
}

TEST_CASE("ImageView block access", BE_CATCH_TAGS) {
   using s = gfx::Swizzle;
   gfx::ImageFormat format(U8(4), gfx::ImageFormat::block_dim_type { 1 }, gfx::ImageBlockPacking::s_8_8_8_8, 4,
         gfx::ImageFormat::ctype_vec_type { static_cast<U8>(gfx::ImageComponentType::unorm) },
         { static_cast<U8>(s::red), static_cast<U8>(s::green), static_cast<U8>(s::blue), static_cast<U8>(s::alpha) },
         gfx::Colorspace::srgb, false);

   gfx::Image img = gfx::make_image(format, ivec3(4));

   ivec3 tc;
   for (tc.z = 0; tc.z < 4; ++tc.z) {
      for (tc.y = 0; tc.y < 4; ++tc.y) {
         for (tc.x = 0; tc.x < 4; ++tc.x) {
            gfx::put_block(img.view, tc, RGBA(glm::u8vec3(tc * 64), 13u));
         }
      }
   }
   
   for (tc.z = 0; tc.z < 4; ++tc.z) {
      for (tc.y = 0; tc.y < 4; ++tc.y) {
         for (tc.x = 0; tc.x < 4; ++tc.x) {
            REQUIRE(gfx::get_block<RGBA>(img.view, tc) == RGBA(glm::u8vec3(tc * 64), 13u));
         }
      }
   }
}

#endif
