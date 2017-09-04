#ifdef BE_TEST

#include "tex/image.hpp"
#include "tex/image_view_hash.hpp"
#include "tex/image_format_gl.hpp"
#include "tex/make_image.hpp"
#include "tex/block_access.hpp"
#include "tex/pixel_access.hpp"
#include "tex/pixel_access_norm.hpp"
#include "tex/visit_image.hpp"
#include "tex/blit_blocks.hpp"
#include "tex/blit_pixels.hpp"
#include <be/core/be.hpp>
#include <catch/catch.hpp>
#include <unordered_set>
#include <sstream>
#include <iomanip>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageView]"

using namespace be;
using namespace be::gfx::tex;

namespace Catch {

std::string toString(const be::RGBA& value) {
   std::ostringstream oss;
   oss << "[ " << (int)value.r << ", " << (int)value.g << ", " << (int)value.b << ", " << (int)value.a << " ]";
   return oss.str();
}

std::string toString(const glm::vec4& value) {
   std::ostringstream oss;
   oss << std::scientific << std::setprecision(12) << "vec4(" << value.r << ", " << value.g << ", " << value.b << ", " << value.a << ")";
   return oss.str();
}

} // Catch

TEST_CASE("std::hash<ImageView>", BE_CATCH_TAGS) {
   std::unordered_set<ImageView> stet3;
   stet3.emplace();
}

TEST_CASE("ImageView block access", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4),
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

TEST_CASE("ImageView pixel access (simple)", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4),
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
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4),
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

TEST_CASE("detail::ComponentRawNorm<U16, 11, ufloat>", BE_CATCH_TAGS) {
   using clazz = be::gfx::tex::detail::ComponentRawNorm<U16, 11, ComponentType::ufloat>;

   SECTION("decode") {
      REQUIRE(clazz::decode(0) == 0.f);
      REQUIRE(clazz::decode(clazz::f11_exponent_basis << clazz::f11_mantissa_bits) == 1.f);
      REQUIRE(clazz::decode(clazz::f11_exponent_basis << clazz::f11_mantissa_bits | 0x3 << (clazz::f11_mantissa_bits - 2)) == 1.75f);
      REQUIRE(clazz::decode((clazz::f11_exponent_basis + 1) << clazz::f11_mantissa_bits | 0x3 << (clazz::f11_mantissa_bits - 2)) == 3.5f);
      REQUIRE(clazz::decode((clazz::f11_exponent_basis - 1) << clazz::f11_mantissa_bits | 0x1 << (clazz::f11_mantissa_bits - 1)) == 0.75f);
      REQUIRE(clazz::decode(0x1) == 9.5367431640625e-7f);
      REQUIRE(clazz::decode(clazz::f11_mantissa_mask) == 6.008148193359375e-5f);
      REQUIRE(clazz::decode(1 << clazz::f11_mantissa_bits) == 6.103515625e-5f);
      REQUIRE(std::isinf(clazz::decode(clazz::f11_exponent_mask)));
      REQUIRE(std::isnan(clazz::decode(clazz::f11_exponent_mask | 1)));
   }

   SECTION("encode") {
      REQUIRE(clazz::encode(0.f) == 0u);
      REQUIRE(clazz::encode(-0.f) == 0u);
      REQUIRE(clazz::encode(-1.f) == 0u);
      REQUIRE(clazz::encode(1e-10f) == 0u);
      REQUIRE(clazz::encode(-1e-10f) == 0u);
      REQUIRE(clazz::encode(1.f) == (clazz::f11_exponent_basis << clazz::f11_mantissa_bits));
      REQUIRE(clazz::encode(9.5367431640625e-7f) == 0x1);
      REQUIRE(clazz::encode(6.008148193359375e-5f) == clazz::f11_mantissa_mask);
      REQUIRE(clazz::encode(-6.008148193359375e-5f) == 0u);
      REQUIRE(clazz::encode(1e10f) == clazz::f11_exponent_mask);
      REQUIRE(clazz::encode(-1e10f) == 0u);
      REQUIRE(clazz::encode(clazz::decode(clazz::f11_exponent_mask)) == clazz::f11_exponent_mask);
      REQUIRE(clazz::encode(-clazz::decode(clazz::f11_exponent_mask)) == 0);
      REQUIRE((clazz::encode(clazz::decode(clazz::f11_exponent_mask | 1)) & clazz::f11_exponent_mask) == clazz::f11_exponent_mask);
      REQUIRE((clazz::encode(clazz::decode(clazz::f11_exponent_mask | 1)) & clazz::f11_mantissa_mask) != 0);
   }
}

TEST_CASE("detail::ComponentRawNorm<U16, 10, ufloat>", BE_CATCH_TAGS) {
   using clazz = be::gfx::tex::detail::ComponentRawNorm<U16, 10, ComponentType::ufloat>;

   SECTION("decode") {
      REQUIRE(clazz::decode(0) == 0.f);
      REQUIRE(clazz::decode(clazz::f10_exponent_basis << clazz::f10_mantissa_bits) == 1.f);
      REQUIRE(clazz::decode(clazz::f10_exponent_basis << clazz::f10_mantissa_bits | 0x3 << (clazz::f10_mantissa_bits - 2)) == 1.75f);
      REQUIRE(clazz::decode((clazz::f10_exponent_basis + 1) << clazz::f10_mantissa_bits | 0x3 << (clazz::f10_mantissa_bits - 2)) == 3.5f);
      REQUIRE(clazz::decode((clazz::f10_exponent_basis - 1) << clazz::f10_mantissa_bits | 0x1 << (clazz::f10_mantissa_bits - 1)) == 0.75f);
      REQUIRE(clazz::decode(0x1) == 1.9073486328125e-6f);
      REQUIRE(clazz::decode(clazz::f10_mantissa_mask) == 5.91278076171875e-5f);
      REQUIRE(clazz::decode(1 << clazz::f10_mantissa_bits) == 6.103515625e-5f);
      REQUIRE(std::isinf(clazz::decode(clazz::f10_exponent_mask)));
      REQUIRE(std::isnan(clazz::decode(clazz::f10_exponent_mask | 1)));
   }

   SECTION("encode") {
      REQUIRE(clazz::encode(0.f) == 0u);
      REQUIRE(clazz::encode(-0.f) == 0u);
      REQUIRE(clazz::encode(-1.f) == 0u);
      REQUIRE(clazz::encode(1e-10f) == 0u);
      REQUIRE(clazz::encode(-1e-10f) == 0u);
      REQUIRE(clazz::encode(1.f) == (clazz::f10_exponent_basis << clazz::f10_mantissa_bits));
      REQUIRE(clazz::encode(1.9073486328125e-6f) == 0x1);
      REQUIRE(clazz::encode(5.91278076171875e-5f) == clazz::f10_mantissa_mask);
      REQUIRE(clazz::encode(-5.91278076171875e-5f) == 0u);
      REQUIRE(clazz::encode(1e10f) == clazz::f10_exponent_mask);
      REQUIRE(clazz::encode(-1e10f) == 0u);
      REQUIRE(clazz::encode(clazz::decode(clazz::f10_exponent_mask)) == clazz::f10_exponent_mask);
      REQUIRE(clazz::encode(-clazz::decode(clazz::f10_exponent_mask)) == 0);
      REQUIRE((clazz::encode(clazz::decode(clazz::f10_exponent_mask | 1)) & clazz::f10_exponent_mask) == clazz::f10_exponent_mask);
      REQUIRE((clazz::encode(clazz::decode(clazz::f10_exponent_mask | 1)) & clazz::f10_mantissa_mask) != 0);
   }
}

TEST_CASE("detail::ImageComponentRawNorm<U16, 16, sfloat>", BE_CATCH_TAGS) {
   using clazz = be::gfx::tex::detail::ComponentRawNorm<U16, 16, ComponentType::sfloat>;

   SECTION("decode") {
      REQUIRE(clazz::decode(0) == 0.f);
      REQUIRE(clazz::decode(clazz::f16_exponent_basis << clazz::f16_mantissa_bits) == 1.f);
      REQUIRE(clazz::decode(clazz::f16_exponent_basis << clazz::f16_mantissa_bits | 0x3 << (clazz::f16_mantissa_bits - 2)) == 1.75f);
      REQUIRE(clazz::decode((clazz::f16_exponent_basis + 1) << clazz::f16_mantissa_bits | 0x3 << (clazz::f16_mantissa_bits - 2)) == 3.5f);
      REQUIRE(clazz::decode((clazz::f16_exponent_basis - 1) << clazz::f16_mantissa_bits | 0x1 << (clazz::f16_mantissa_bits - 1)) == 0.75f);
      REQUIRE(clazz::decode(0x1) == 5.9604644775390625e-8f);
      REQUIRE(clazz::decode(0x1 | clazz::f16_sign_mask) == -5.9604644775390625e-8f);
      REQUIRE(clazz::decode(clazz::f16_mantissa_mask) == 6.0975551605224609375e-5f);
      REQUIRE(clazz::decode(clazz::f16_mantissa_mask | clazz::f16_sign_mask) == -6.0975551605224609375e-5f);
      REQUIRE(clazz::decode(1 << clazz::f16_mantissa_bits) == 6.103515625e-5f);
      REQUIRE(std::isinf(clazz::decode(clazz::f16_exponent_mask)));
      REQUIRE(std::isnan(clazz::decode(clazz::f16_exponent_mask | 1)));
   }

   SECTION("encode") {
      REQUIRE(clazz::encode(0.f) == 0u);
      REQUIRE(clazz::encode(-0.f) == clazz::f16_sign_mask);
      REQUIRE(clazz::encode(1e-10f) == 0u);
      REQUIRE(clazz::encode(-1e-10f) == clazz::f16_sign_mask);
      REQUIRE(clazz::encode(1.f) == (clazz::f16_exponent_basis << clazz::f16_mantissa_bits));
      REQUIRE(clazz::encode(-1.f) == (clazz::f16_sign_mask | (clazz::f16_exponent_basis << clazz::f16_mantissa_bits)));
      REQUIRE(clazz::encode(5.9604644775390625e-8f) == 0x1);
      REQUIRE(clazz::encode(6.0975551605224609375e-5f) == clazz::f16_mantissa_mask);
      REQUIRE(clazz::encode(-6.0975551605224609375e-5f) == (clazz::f16_mantissa_mask | clazz::f16_sign_mask));
      REQUIRE(clazz::encode(1e10f) == clazz::f16_exponent_mask);
      REQUIRE(clazz::encode(-1e10f) == (clazz::f16_exponent_mask | clazz::f16_sign_mask));
      REQUIRE(clazz::encode(clazz::decode(clazz::f16_exponent_mask)) == clazz::f16_exponent_mask);
      REQUIRE(clazz::encode(-clazz::decode(clazz::f16_exponent_mask)) == (clazz::f16_exponent_mask | clazz::f16_sign_mask));
      REQUIRE((clazz::encode(clazz::decode(clazz::f16_exponent_mask | 1)) & clazz::f16_exponent_mask) == clazz::f16_exponent_mask);
      REQUIRE((clazz::encode(clazz::decode(clazz::f16_exponent_mask | 1)) & clazz::f16_mantissa_mask) != 0);
   }
}

TEST_CASE("ImageView normalized pixel access rgba8888unorm", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4),
                           swizzles_rgba(), Colorspace::srgb, false);

   const int dim = 4;
   Image img = make_image(format, ivec3(dim));

   SECTION("lineal") {
      int tc;
      for (tc = 0; tc < dim; ++tc) {
         put_pixel_norm(img.view, tc, vec4(tc / 255.f, tc * 3 / 255.f, 1 - tc / 255.f, 1 - tc * 3 / 255.f));
      }
      for (tc = 0; tc < dim; ++tc) {
         REQUIRE(glm::length(get_pixel_norm(img.view, tc) - vec4(tc / 255.f, tc * 3 / 255.f, 1 - tc / 255.f, 1 - tc * 3 / 255.f)) < 1/255.f);
      }
   }

   SECTION("planar") {
      ivec2 tc;
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            put_pixel_norm(img.view, tc, vec4(tc.x / 255.f, tc.y / 255.f, 1 - tc.x / 255.f, 1 - tc.y / 255.f));
         }
      }
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            REQUIRE(glm::length(get_pixel_norm(img.view, tc) - vec4(tc.x / 255.f, tc.y / 255.f, 1 - tc.x / 255.f, 1 - tc.y / 255.f)) < 1 / 255.f);
         }
      }
   }

   SECTION("volumetric") {
      ivec3 tc;
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               put_pixel_norm(img.view, tc, vec4(tc.x / 255.f, tc.y / 255.f, tc.z / 255.f, 1 - tc.y / 255.f));
            }
         }
      }
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(glm::length(get_pixel_norm(img.view, tc) - vec4(tc.x / 255.f, tc.y / 255.f, tc.z / 255.f, 1 - tc.y / 255.f)) < 1 / 255.f);
            }
         }
      }
   }
}

TEST_CASE("ImageView normalized pixel access bgr888uint", BE_CATCH_TAGS) {
   ImageFormat format(U8(3), 1, BlockPacking::s_8_8_8, 3, component_types(ComponentType::uint, 3),
                           swizzles_bgr(), Colorspace::srgb, false);

   const int dim = 4;
   Image img = make_image(format, ivec3(dim));

   SECTION("lineal") {
      int tc;
      for (tc = 0; tc < dim; ++tc) {
         put_pixel_norm(img.view, tc, vec4(tc, tc * 3, 100 - tc, 0.f));
      }
      for (tc = 0; tc < dim; ++tc) {
         REQUIRE(get_pixel_norm(img.view, tc) == vec4(tc, tc * 3, 100 - tc, 1.f));
      }
   }

   SECTION("planar") {
      ivec2 tc;
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            put_block(img.view, tc, RGB(1, tc.y, tc.x));
         }
      }
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            REQUIRE(get_pixel_norm(img.view, tc) == vec4(tc.x, tc.y, 1.f, 1.f));
         }
      }
   }

   SECTION("volumetric") {
      ivec3 tc;
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               put_pixel_norm(img.view, tc, vec4(tc.x, tc.y, tc.z, 0.f));
            }
         }
      }
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(get_pixel_norm(img.view, tc) == vec4(tc.x, tc.y, tc.z, 1.f));
            }
         }
      }
   }
}

TEST_CASE("ImageView normalized pixel access bgra5551unorm", BE_CATCH_TAGS) {
   ImageFormat format(U8(2), 1, BlockPacking::p_5_5_5_1, 4, component_types(ComponentType::unorm, 4),
                           swizzles_bgra(), Colorspace::srgb, false);

   const int dim = 4;
   Image img = make_image(format, ivec3(dim));

   SECTION("volumetric") {
      ivec3 tc;
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               put_pixel_norm(img.view, tc, vec4(tc.x / 31.f, tc.y / 31.f, tc.z / 31.f, tc.x + tc.y + tc.z == 2 ? 1.f : 0.f));
            }
         }
      }
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(glm::length(get_pixel_norm(img.view, tc) - vec4(tc.x / 31.f, tc.y / 31.f, tc.z / 31.f, tc.x + tc.y + tc.z == 2 ? 1.f : 0.f)) < 1/31.f);
            }
         }
      }
   }
}

TEST_CASE("ImageView normalized pixel access rgbe9995ufloat", BE_CATCH_TAGS) {
   ImageFormat format = canonical_format(gl::GL_RGB9_E5);
   const int dim = 4;
   Image img = make_image(format, ivec3(dim));

   SECTION("volumetric") {
      ivec3 tc;
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               put_pixel_norm(img.view, tc, vec4(tc.x / 31.f, tc.y / 31.f, tc.z / 31.f, 1.f));
            }
         }
      }
      for (tc.z = 0; tc.z < dim; ++tc.z) {
         for (tc.y = 0; tc.y < dim; ++tc.y) {
            for (tc.x = 0; tc.x < dim; ++tc.x) {
               REQUIRE(glm::length(get_pixel_norm(img.view, tc) - vec4(tc.x / 31.f, tc.y / 31.f, tc.z / 31.f, 1.f)) < 1/31.f);
            }
         }
      }
   }
}

TEST_CASE("ImageView blit_blocks(ImageView, ImageView)", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4),
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

      blit_blocks(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different block size") {
      Image img2;
      img2.storage = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), U8(format.block_size() * 2));
      img2.view = ImageView(format, *img2.storage, 0, 0, 0);

      blit_blocks(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different line alignment") {
      Image img2;
      img2.storage = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), format.block_size(), TextureAlignment((U8)128));
      img2.view = ImageView(format, *img2.storage, 0, 0, 0);

      blit_blocks(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different plane alignment") {
      Image img2;
      img2.storage = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), format.block_size(), TextureAlignment((U8)8, (U8)128));
      img2.view = ImageView(format, *img2.storage, 0, 0, 0);

      blit_blocks(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different dim") {
      Image img2 = make_image(format, ivec3(dim) + 1);

      blit_blocks(img.view, img2.view);

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

}

TEST_CASE("ImageView blit_blocks(ImageView, ImageRegion, ImageView, ImageRegion)", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4),
                           swizzles_rgba(), Colorspace::srgb, false);

   ivec3 dim(4);
   Image img = make_image(format, ivec3(dim));

   auto get = get_pixel_func<RGBA, ivec3>(img.view);
   auto put = put_pixel_func<RGBA, ivec3>(img.view);
   visit_image_pixels<ivec3>(img.view, [put](ImageView& view, ivec3 pc) {
      put(view, pc, RGBA(RGB(pc * 64), 255u));
   });

   ImageRegion region = rotate_cw(block_region(img.view));

   SECTION("Same format, dim, unrotated") {
      Image img2 = make_image(format, ivec3(dim));

      blit_blocks(img.view, block_region(img.view), img2.view, block_region(img2.view));

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, pc) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, dim") {
      Image img2 = make_image(format, ivec3(dim));

      blit_blocks(img.view, region, img2.view, block_region(img2.view));

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, region, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, region_to_image(region, pc)) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different block size") {
      Image img2;
      img2.storage = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), U8(format.block_size() * 2));
      img2.view = ImageView(format, *img2.storage, 0, 0, 0);

      blit_blocks(img.view, region, img2.view, block_region(img2.view));

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, region, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, region_to_image(region, pc)) == get2(img2.view, pc));
      });
   }

   SECTION("Same format, different dim") {
      Image img2 = make_image(format, ivec3(dim) + 1);

      blit_blocks(img.view, region, img2.view, block_region(img2.view));

      auto get2 = get_pixel_func<RGBA, ivec3>(img2.view);

      visit_image_pixels<ivec3>(img.view, [get, get2, region, &img2](ImageView& view, ivec3 pc) {
         REQUIRE(get(view, region_to_image(region, pc)) == get2(img2.view, pc));
      });
   }

}


TEST_CASE("ImageView blit_pixels(ImageView, ImageView)", BE_CATCH_TAGS) {
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4),
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
   ImageFormat format(U8(4), 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4),
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
