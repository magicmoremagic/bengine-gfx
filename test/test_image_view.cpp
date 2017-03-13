#ifdef BE_TEST

#include "image.hpp"
#include "image_view_hash.hpp"
#include "make_image.hpp"
#include "image_block_access.hpp"
#include "image_pixel_access.hpp"
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

   const int dim = 4;
   gfx::Image img = gfx::make_image(format, ivec3(dim));

   SECTION("lineal") {
      int tc;
      for (tc = 0; tc < dim; ++tc) {
         gfx::put_block(img.view, tc, RGBA(tc, tc * 2, tc * 4, 13u));
      }
      for (tc = 0; tc < dim; ++tc) {
         REQUIRE(gfx::get_block<RGBA>(img.view, tc) == RGBA(tc, tc * 2, tc * 4, 13u));
      }
   }

   SECTION("planar") {
      ivec2 tc;
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            gfx::put_block(img.view, tc, RGBA(tc.x * 64, tc.y * 64, 0, 13u));
         }
      }
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            REQUIRE(gfx::get_block<RGBA>(img.view, tc) == RGBA(tc.x * 64, tc.y * 64, 0, 13u));
         }
      }
   }

   SECTION("volumetric") {
      ivec3 tc;
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               gfx::put_block(img.view, tc, RGBA(glm::u8vec3(tc * 64), 13u));
            }
         }
      }
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(gfx::get_block<RGBA>(img.view, tc) == RGBA(glm::u8vec3(tc * 64), 13u));
            }
         }
      }
   }
}

TEST_CASE("ImageView pixel access (simple)", BE_CATCH_TAGS) {
   using s = gfx::Swizzle;
   gfx::ImageFormat format(U8(4), gfx::ImageFormat::block_dim_type { 1 }, gfx::ImageBlockPacking::s_8_8_8_8, 4,
                           gfx::ImageFormat::ctype_vec_type { static_cast<U8>(gfx::ImageComponentType::unorm) },
                           { static_cast<U8>(s::red), static_cast<U8>(s::green), static_cast<U8>(s::blue), static_cast<U8>(s::alpha) },
                           gfx::Colorspace::srgb, false);

   const int dim = 4;
   gfx::Image img = gfx::make_image(format, ivec3(dim));

   SECTION("lineal") {
      SECTION("func") {
         auto get = gfx::get_pixel_lineal_func<RGBA>(img.view);
         auto put = gfx::put_pixel_lineal_func<RGBA>(img.view);
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
            gfx::put_pixel(img.view, tc, RGBA(tc, tc * 2, tc * 4, 13u));
         }
         for (tc = 0; tc < dim; ++tc) {
            REQUIRE(gfx::get_pixel<RGBA>(img.view, tc) == RGBA(tc, tc * 2, tc * 4, 13u));
         }
      }
   }

   SECTION("planar") {
      SECTION("func") {
         auto get = gfx::get_pixel_planar_func<RGBA>(img.view);
         auto put = gfx::put_pixel_planar_func<RGBA>(img.view);
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
               gfx::put_pixel(img.view, tc, RGBA(tc.x * 64, tc.y * 64, 0, 13u));
            }
         }
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(gfx::get_pixel<RGBA>(img.view, tc) == RGBA(tc.x * 64, tc.y * 64, 0, 13u));
            }
         }
      }
   }

   SECTION("volumetric") {
      SECTION("func") {
         auto get = gfx::get_pixel_volumetric_func<RGBA>(img.view);
         auto put = gfx::put_pixel_volumetric_func<RGBA>(img.view);
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
                  gfx::put_pixel(img.view, tc, RGBA(glm::u8vec3(tc * 64), 13u));
               }
            }
         }
         for (tc.z = 0; tc.z < dim; ++tc.z) {
            for (tc.y = 0; tc.y < dim; ++tc.y) {
               for (tc.x = 0; tc.x < dim; ++tc.x) {
                  REQUIRE(gfx::get_pixel<RGBA>(img.view, tc) == RGBA(glm::u8vec3(tc * 64), 13u));
               }
            }
         }
      }
   }
}

TEST_CASE("ImageView pixel access (packed block)", BE_CATCH_TAGS) {
   using s = gfx::Swizzle;
   gfx::ImageFormat format(U8(32), gfx::ImageFormat::block_dim_type { 2 }, gfx::ImageBlockPacking::s_8_8_8_8, 4,
                           gfx::ImageFormat::ctype_vec_type { static_cast<U8>(gfx::ImageComponentType::unorm) },
                           { static_cast<U8>(s::red), static_cast<U8>(s::green), static_cast<U8>(s::blue), static_cast<U8>(s::alpha) },
                           gfx::Colorspace::srgb, false);

   const int dim = 4;
   gfx::Image img = gfx::make_image(format, ivec3(dim));

   SECTION("lineal") {
      SECTION("func") {
         auto get = gfx::get_pixel_lineal_func<RGBA>(img.view);
         auto put = gfx::put_pixel_lineal_func<RGBA>(img.view);
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
            gfx::put_pixel(img.view, tc, RGBA(tc, tc * 2, tc * 4, 13u));
         }
         for (tc = 0; tc < dim; ++tc) {
            REQUIRE(gfx::get_pixel<RGBA>(img.view, tc) == RGBA(tc, tc * 2, tc * 4, 13u));
         }
      }
   }

   SECTION("planar") {
      SECTION("func") {
         auto get = gfx::get_pixel_planar_func<RGBA>(img.view);
         auto put = gfx::put_pixel_planar_func<RGBA>(img.view);
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
               gfx::put_pixel(img.view, tc, RGBA(tc.x * 64, tc.y * 64, 0, 13u));
            }
         }
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(gfx::get_pixel<RGBA>(img.view, tc) == RGBA(tc.x * 64, tc.y * 64, 0, 13u));
            }
         }
      }
   }

   SECTION("volumetric") {
      SECTION("func") {
         auto get = gfx::get_pixel_volumetric_func<RGBA>(img.view);
         auto put = gfx::put_pixel_volumetric_func<RGBA>(img.view);
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
                  gfx::put_pixel(img.view, tc, RGBA(glm::u8vec3(tc * 64), 13u));
               }
            }
         }
         for (tc.z = 0; tc.z < dim; ++tc.z) {
            for (tc.y = 0; tc.y < dim; ++tc.y) {
               for (tc.x = 0; tc.x < dim; ++tc.x) {
                  REQUIRE(gfx::get_pixel<RGBA>(img.view, tc) == RGBA(glm::u8vec3(tc * 64), 13u));
               }
            }
         }
      }
   }
}

#endif
