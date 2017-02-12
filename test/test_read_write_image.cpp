#ifdef BE_TEST

#include "read_image.hpp"
#include "write_image.hpp"
#include <catch/catch.hpp>
#include <gli/texture2d.hpp>
#include <be/util/xoroshiro_128_plus.hpp>
#include <be/core/glm.hpp>
#include <be/core/time.hpp>
#include <random>

#define BE_CATCH_TAGS "[texi][texi:read_image][texi:write_image]"

using namespace be;

gli::texture2d create_test_image(gli::format format, gli::extent2d size) {
   gli::texture2d tex = gli::texture2d(format, size, 1);
   rnd::xo128p prng(perf_now());
   std::uniform_int_distribution<U16> dist(0, 0xFFu);
   gli::extent2d tc;

   if (format == gli::FORMAT_RGBA8_UNORM_PACK8) {
      for (tc.y = 0; tc.y < size.y; ++tc.y) {
         for (tc.x = 0; tc.x < size.x; ++tc.x) {
            tex.store(tc, 0, RGBA((U8)dist(prng), (U8)dist(prng), (U8)dist(prng), (U8)dist(prng)));
         }
      }
   } else if (format == gli::FORMAT_RGBA8_UNORM_PACK8) {
      for (tc.y = 0; tc.y < size.y; ++tc.y) {
         for (tc.x = 0; tc.x < size.x; ++tc.x) {
            tex.store(tc, 0, RGB((U8)dist(prng), (U8)dist(prng), (U8)dist(prng)));
         }
      }
   }

   return tex;
}

void require_equivalent(gli::texture& a, gli::texture& b) {
   REQUIRE(a.target() == gli::TARGET_2D);
   REQUIRE(b.target() == gli::TARGET_2D);
   REQUIRE(a.format() == b.format());
   REQUIRE(a.extent() == b.extent());
   REQUIRE(a.layers() == b.layers());
   REQUIRE(a.levels() == b.levels());

   if (a.format() == gli::FORMAT_RGBA8_UNORM_PACK8) {
      gli::extent3d tc;
      for (tc.y = 0; tc.y < a.extent().y; ++tc.y) {
         for (tc.x = 0; tc.x < a.extent().x; ++tc.x) {
            REQUIRE(a.load<RGBA>(tc, 0, 0, 0) == b.load<RGBA>(tc, 0, 0, 0));
         }
      }
   } else if (a.format() == gli::FORMAT_RGB8_UNORM_PACK8) {
      gli::extent3d tc;
      for (tc.y = 0; tc.y < a.extent().y; ++tc.y) {
         for (tc.x = 0; tc.x < a.extent().x; ++tc.x) {
            REQUIRE(a.load<RGB>(tc, 0, 0, 0) == b.load<RGB>(tc, 0, 0, 0));
         }
      }
   }
}

TEST_CASE("texi dds read/write", BE_CATCH_TAGS) {
   gli::texture tex = create_test_image(gli::FORMAT_RGBA8_UNORM_PACK8, {11, 12});
   Buf<const UC> buf;
   gli::texture tex2;

   REQUIRE_NOTHROW(buf = texi::write_dds_texture(tex));
   REQUIRE_NOTHROW(tex2 = texi::read_dds_texture(buf));
   require_equivalent(tex, tex2);
}


TEST_CASE("texi ktx read/write", BE_CATCH_TAGS) {
   gli::texture tex = create_test_image(gli::FORMAT_RGBA8_UNORM_PACK8, {11, 12});
   Buf<const UC> buf;
   gli::texture tex2;

   REQUIRE_NOTHROW(buf = texi::write_ktx_texture(tex));
   REQUIRE_NOTHROW(tex2 = texi::read_ktx_texture(buf));
   require_equivalent(tex, tex2);
}

TEST_CASE("texi kmg read/write", BE_CATCH_TAGS) {
   gli::texture tex = create_test_image(gli::FORMAT_RGBA8_UNORM_PACK8, {11, 12});
   Buf<const UC> buf;
   gli::texture tex2;

   REQUIRE_NOTHROW(buf = texi::write_kmg_texture(tex));
   REQUIRE_NOTHROW(tex2 = texi::read_kmg_texture(buf));
   require_equivalent(tex, tex2);
}

TEST_CASE("texi png read/write", BE_CATCH_TAGS) {
   gli::texture tex = create_test_image(gli::FORMAT_RGBA8_UNORM_PACK8, {11, 12});
   Buf<const UC> buf;
   gli::texture tex2;

   REQUIRE_NOTHROW(buf = texi::write_png_texture(tex));
   REQUIRE_NOTHROW(tex2 = texi::read_png_texture(buf));
   require_equivalent(tex, tex2);
}

TEST_CASE("texi bmp read/write", BE_CATCH_TAGS) {
   gli::texture tex = create_test_image(gli::FORMAT_RGB8_UNORM_PACK8, {11, 12});
   Buf<const UC> buf;
   gli::texture tex2;

   REQUIRE_NOTHROW(buf = texi::write_bmp_texture(tex));
   REQUIRE_NOTHROW(tex2 = texi::read_bmp_texture(buf));
   require_equivalent(tex, tex2);
}

TEST_CASE("texi tga read/write", BE_CATCH_TAGS) {
   gli::texture tex = create_test_image(gli::FORMAT_RGBA8_UNORM_PACK8, {11, 12});
   Buf<const UC> buf;
   gli::texture tex2;

   REQUIRE_NOTHROW(buf = texi::write_tga_texture(tex));
   REQUIRE_NOTHROW(tex2 = texi::read_tga_texture(buf));
   require_equivalent(tex, tex2);
}

#endif
