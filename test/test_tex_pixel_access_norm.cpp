#ifdef BE_TEST

#include <glm/glm.hpp>
#include "tostring.hpp"
#include "tex/image.hpp"
#include "tex/image_format_gl.hpp"
#include "tex/make_image.hpp"
#include "tex/pixel_access_norm.hpp"
#include "tex/visit_image.hpp"
#include <be/core/id.hpp>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageView]"

using namespace be;
using namespace be::gfx::gl;
using namespace be::gfx::tex;

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

bool hash_bit(const ivec3 tc, int comp = 0) {
   static const U64 bits = (U64)Id("Lauren Epson Dollar sat on Emmet.");
   const int n = 32 + comp + 4 * (tc.x + tc.y * 43 + tc.z * 149);
   return 0 != (bits & (1ull << (n & 0x3f)));
}

F32 monochrome_comp(const ivec3 tc, int comp) {
   return hash_bit(tc, comp) ? 1.f : 0.f;
}

vec4 monochrome_pixel(const ivec3 tc, int comps) {
   vec4 pixel = vec4(0.f, 0.f, 0.f, 1.f);

   if (comps == 1) {
      for (glm::length_t c = 0; c < 3; ++c) {
         pixel[c] = monochrome_comp(tc, 0);
      }
   } else {
      for (glm::length_t c = 0; c < comps; ++c) {
         pixel[c] = monochrome_comp(tc, c);
      }
   }

   return pixel;
}

void monochrome_test(ImageFormat format) {
   const int dim = 3;
   Image img = make_image(format, ivec3(dim));
   ivec3 tc;

   for (tc.z = 0; tc.z < dim; ++tc.z) {
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            vec4 pixel = monochrome_pixel(tc, format.components());
            put_pixel_norm(img.view, tc, pixel);
         }
      }
   }

   for (tc.z = 0; tc.z < dim; ++tc.z) {
      for (tc.y = 0; tc.y < dim; ++tc.y) {
         for (tc.x = 0; tc.x < dim; ++tc.x) {
            vec4 pixel = get_pixel_norm(img.view, tc);
            vec4 expected = monochrome_pixel(tc, format.components());
            vec4 diff = expected - pixel;
            vec4 absdiff = glm::abs(diff);
            REQUIRE(absdiff.r == 0);
            REQUIRE(absdiff.g == 0);
            REQUIRE(absdiff.b == 0);
            REQUIRE(absdiff.a == 0);

            if (tc.z == 0) {
               REQUIRE(get_pixel_norm(img.view, ivec2(tc)) == pixel);
               if (tc.y == 0) {
                  REQUIRE(get_pixel_norm(img.view, tc.x) == pixel);
               }
            }
         }
      }
   }
}

TEST_CASE("normalized pixel access - monochrome components", BE_CATCH_TAGS) {

   /*!! register_template_string([[`with each $ using # { `SECTION("`$`") { monochrome_test(canonical_format(`$`)); }`nl }]], 'gl_monochrome_test')
   write_template('gl_monochrome_test', {
   'GL_R8',                'GL_R16',            'GL_R8_SNORM',          'GL_R16_SNORM',
   'GL_R8UI',              'GL_R16UI',          'GL_R32UI',             'GL_R8I',
   'GL_R16I',              'GL_R32I',           'GL_R16F',              'GL_R32F',
   'GL_RG8',               'GL_RG16',           'GL_RG8_SNORM',         'GL_RG16_SNORM',
   'GL_RG8UI',             'GL_RG16UI',         'GL_RG32UI',            'GL_RG8I',
   'GL_RG16I',             'GL_RG32I',          'GL_RG16F',             'GL_RG32F',
   'GL_SRGB8',             'GL_RGB8',           'GL_RGB16',             'GL_R3_G3_B2',
   --[['GL_RGB565',]]      'GL_RGB4',           'GL_RGB5',              'GL_RGB8_SNORM',
   'GL_RGB16_SNORM',       'GL_RGB8UI',         'GL_RGB16UI',           'GL_RGB32UI',
   'GL_RGB8I',             'GL_RGB16I',         'GL_RGB32I',            'GL_R11F_G11F_B10F',
   'GL_RGB16F',            'GL_RGB32F',         'GL_RGB9_E5',           'GL_RGBA16',
   'GL_RGBA4',             'GL_RGB5_A1',        'GL_RGB10_A2',          'GL_RGBA8_SNORM',
   'GL_RGBA16_SNORM',      'GL_RGBA8UI',        'GL_RGBA16UI',          'GL_RGBA32UI',
   'GL_RGB10_A2UI',        'GL_RGBA8I',         'GL_RGBA16I',           'GL_RGBA32I',
   'GL_RGBA16F',           'GL_RGBA32F',        'GL_DEPTH_COMPONENT16', 'GL_DEPTH_COMPONENT32F',
   'GL_DEPTH_COMPONENT24', 'GL_STENCIL_INDEX8', 'GL_DEPTH24_STENCIL8',  'GL_DEPTH32F_STENCIL8'
   }) !! 67 */
   /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
   SECTION("GL_R8") { monochrome_test(canonical_format(GL_R8)); }
   SECTION("GL_R16") { monochrome_test(canonical_format(GL_R16)); }
   SECTION("GL_R8_SNORM") { monochrome_test(canonical_format(GL_R8_SNORM)); }
   SECTION("GL_R16_SNORM") { monochrome_test(canonical_format(GL_R16_SNORM)); }
   SECTION("GL_R8UI") { monochrome_test(canonical_format(GL_R8UI)); }
   SECTION("GL_R16UI") { monochrome_test(canonical_format(GL_R16UI)); }
   SECTION("GL_R32UI") { monochrome_test(canonical_format(GL_R32UI)); }
   SECTION("GL_R8I") { monochrome_test(canonical_format(GL_R8I)); }
   SECTION("GL_R16I") { monochrome_test(canonical_format(GL_R16I)); }
   SECTION("GL_R32I") { monochrome_test(canonical_format(GL_R32I)); }
   SECTION("GL_R16F") { monochrome_test(canonical_format(GL_R16F)); }
   SECTION("GL_R32F") { monochrome_test(canonical_format(GL_R32F)); }
   SECTION("GL_RG8") { monochrome_test(canonical_format(GL_RG8)); }
   SECTION("GL_RG16") { monochrome_test(canonical_format(GL_RG16)); }
   SECTION("GL_RG8_SNORM") { monochrome_test(canonical_format(GL_RG8_SNORM)); }
   SECTION("GL_RG16_SNORM") { monochrome_test(canonical_format(GL_RG16_SNORM)); }
   SECTION("GL_RG8UI") { monochrome_test(canonical_format(GL_RG8UI)); }
   SECTION("GL_RG16UI") { monochrome_test(canonical_format(GL_RG16UI)); }
   SECTION("GL_RG32UI") { monochrome_test(canonical_format(GL_RG32UI)); }
   SECTION("GL_RG8I") { monochrome_test(canonical_format(GL_RG8I)); }
   SECTION("GL_RG16I") { monochrome_test(canonical_format(GL_RG16I)); }
   SECTION("GL_RG32I") { monochrome_test(canonical_format(GL_RG32I)); }
   SECTION("GL_RG16F") { monochrome_test(canonical_format(GL_RG16F)); }
   SECTION("GL_RG32F") { monochrome_test(canonical_format(GL_RG32F)); }
   SECTION("GL_SRGB8") { monochrome_test(canonical_format(GL_SRGB8)); }
   SECTION("GL_RGB8") { monochrome_test(canonical_format(GL_RGB8)); }
   SECTION("GL_RGB16") { monochrome_test(canonical_format(GL_RGB16)); }
   SECTION("GL_R3_G3_B2") { monochrome_test(canonical_format(GL_R3_G3_B2)); }
   SECTION("GL_RGB4") { monochrome_test(canonical_format(GL_RGB4)); }
   SECTION("GL_RGB5") { monochrome_test(canonical_format(GL_RGB5)); }
   SECTION("GL_RGB8_SNORM") { monochrome_test(canonical_format(GL_RGB8_SNORM)); }
   SECTION("GL_RGB16_SNORM") { monochrome_test(canonical_format(GL_RGB16_SNORM)); }
   SECTION("GL_RGB8UI") { monochrome_test(canonical_format(GL_RGB8UI)); }
   SECTION("GL_RGB16UI") { monochrome_test(canonical_format(GL_RGB16UI)); }
   SECTION("GL_RGB32UI") { monochrome_test(canonical_format(GL_RGB32UI)); }
   SECTION("GL_RGB8I") { monochrome_test(canonical_format(GL_RGB8I)); }
   SECTION("GL_RGB16I") { monochrome_test(canonical_format(GL_RGB16I)); }
   SECTION("GL_RGB32I") { monochrome_test(canonical_format(GL_RGB32I)); }
   SECTION("GL_R11F_G11F_B10F") { monochrome_test(canonical_format(GL_R11F_G11F_B10F)); }
   SECTION("GL_RGB16F") { monochrome_test(canonical_format(GL_RGB16F)); }
   SECTION("GL_RGB32F") { monochrome_test(canonical_format(GL_RGB32F)); }
   SECTION("GL_RGB9_E5") { monochrome_test(canonical_format(GL_RGB9_E5)); }
   SECTION("GL_RGBA16") { monochrome_test(canonical_format(GL_RGBA16)); }
   SECTION("GL_RGBA4") { monochrome_test(canonical_format(GL_RGBA4)); }
   SECTION("GL_RGB5_A1") { monochrome_test(canonical_format(GL_RGB5_A1)); }
   SECTION("GL_RGB10_A2") { monochrome_test(canonical_format(GL_RGB10_A2)); }
   SECTION("GL_RGBA8_SNORM") { monochrome_test(canonical_format(GL_RGBA8_SNORM)); }
   SECTION("GL_RGBA16_SNORM") { monochrome_test(canonical_format(GL_RGBA16_SNORM)); }
   SECTION("GL_RGBA8UI") { monochrome_test(canonical_format(GL_RGBA8UI)); }
   SECTION("GL_RGBA16UI") { monochrome_test(canonical_format(GL_RGBA16UI)); }
   SECTION("GL_RGBA32UI") { monochrome_test(canonical_format(GL_RGBA32UI)); }
   SECTION("GL_RGB10_A2UI") { monochrome_test(canonical_format(GL_RGB10_A2UI)); }
   SECTION("GL_RGBA8I") { monochrome_test(canonical_format(GL_RGBA8I)); }
   SECTION("GL_RGBA16I") { monochrome_test(canonical_format(GL_RGBA16I)); }
   SECTION("GL_RGBA32I") { monochrome_test(canonical_format(GL_RGBA32I)); }
   SECTION("GL_RGBA16F") { monochrome_test(canonical_format(GL_RGBA16F)); }
   SECTION("GL_RGBA32F") { monochrome_test(canonical_format(GL_RGBA32F)); }
   SECTION("GL_DEPTH_COMPONENT16") { monochrome_test(canonical_format(GL_DEPTH_COMPONENT16)); }
   SECTION("GL_DEPTH_COMPONENT32F") { monochrome_test(canonical_format(GL_DEPTH_COMPONENT32F)); }
   SECTION("GL_DEPTH_COMPONENT24") { monochrome_test(canonical_format(GL_DEPTH_COMPONENT24)); }
   SECTION("GL_STENCIL_INDEX8") { monochrome_test(canonical_format(GL_STENCIL_INDEX8)); }
   SECTION("GL_DEPTH24_STENCIL8") { monochrome_test(canonical_format(GL_DEPTH24_STENCIL8)); }
   SECTION("GL_DEPTH32F_STENCIL8") { monochrome_test(canonical_format(GL_DEPTH32F_STENCIL8)); }

   /* ######################### END OF GENERATED CODE ######################### */
   /* ######################### END OF GENERATED CODE ######################### */

   /* ######################### END OF GENERATED CODE ######################### */
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
   ImageFormat format = canonical_format(GL_RGB9_E5);
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

#endif
