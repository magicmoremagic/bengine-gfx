#ifdef BE_TEST

#include "tex/image_format_hash.hpp"
#include "tex/image_format_gl.hpp"
#include <catch/catch.hpp>
#include <unordered_set>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageFormat]"

using namespace be;
using namespace be::gfx::gl;
using namespace be::gfx::tex;

TEST_CASE("std::hash<ImageFormat>", BE_CATCH_TAGS) {
   std::unordered_set<ImageFormat> stet;
   REQUIRE_NOTHROW(stet.emplace());
}

void gl_roundtrip(GLenum internal_format) {
   ImageFormat format = canonical_format(internal_format);
   ImageFormatGl gl = to_gl_format(format);
   REQUIRE(gl.internal_format == internal_format);
}

TEST_CASE("GL Internal Format <--> ImageFormat round trip") {
   //#bgl checked(4.2)
   gl_roundtrip(GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM);
   gl_roundtrip(GL_COMPRESSED_RGBA_BPTC_UNORM);
   gl_roundtrip(GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT);
   gl_roundtrip(GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT);
   //#bgl checked (GL_EXT_texture_compression_s3tc)
   gl_roundtrip(GL_COMPRESSED_RGB_S3TC_DXT1_EXT);
   gl_roundtrip(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
   gl_roundtrip(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
   gl_roundtrip(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);
   //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
   gl_roundtrip(GL_COMPRESSED_SRGB_S3TC_DXT1_EXT);
   gl_roundtrip(GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT);
   gl_roundtrip(GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT);
   gl_roundtrip(GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT);
   //#bgl unchecked
   gl_roundtrip(GL_COMPRESSED_RED_RGTC1);
   gl_roundtrip(GL_COMPRESSED_SIGNED_RED_RGTC1);
   gl_roundtrip(GL_COMPRESSED_RG_RGTC2);
   gl_roundtrip(GL_COMPRESSED_SIGNED_RG_RGTC2);
   gl_roundtrip(GL_DEPTH_COMPONENT32);
   gl_roundtrip(GL_DEPTH_COMPONENT16);
   gl_roundtrip(GL_DEPTH_COMPONENT32F);
   gl_roundtrip(GL_DEPTH_COMPONENT24);
   gl_roundtrip(GL_STENCIL_INDEX8);
   gl_roundtrip(GL_DEPTH24_STENCIL8);
   gl_roundtrip(GL_DEPTH32F_STENCIL8);
   gl_roundtrip(GL_R8);
   gl_roundtrip(GL_R16);
   gl_roundtrip(GL_R8_SNORM);
   gl_roundtrip(GL_R16_SNORM);
   gl_roundtrip(GL_R8UI);
   gl_roundtrip(GL_R16UI);
   gl_roundtrip(GL_R32UI);
   gl_roundtrip(GL_R8I);
   gl_roundtrip(GL_R16I);
   gl_roundtrip(GL_R32I);
   gl_roundtrip(GL_R16F);
   gl_roundtrip(GL_R32F);
   gl_roundtrip(GL_RG8);
   gl_roundtrip(GL_RG16);
   gl_roundtrip(GL_RG8_SNORM);
   gl_roundtrip(GL_RG16_SNORM);
   gl_roundtrip(GL_RG8UI);
   gl_roundtrip(GL_RG16UI);
   gl_roundtrip(GL_RG32UI);
   gl_roundtrip(GL_RG8I);
   gl_roundtrip(GL_RG16I);
   gl_roundtrip(GL_RG32I);
   gl_roundtrip(GL_RG16F);
   gl_roundtrip(GL_RG32F);
   gl_roundtrip(GL_SRGB8);
   gl_roundtrip(GL_RGB8);
   gl_roundtrip(GL_RGB16);
   gl_roundtrip(GL_R3_G3_B2);
   //#bgl checked (4.1)
   gl_roundtrip(GL_RGB565);
   //#bgl unchecked
   gl_roundtrip(GL_RGB4);
   gl_roundtrip(GL_RGB5);
   gl_roundtrip(GL_RGB8_SNORM);
   gl_roundtrip(GL_RGB16_SNORM);
   gl_roundtrip(GL_RGB8UI);
   gl_roundtrip(GL_RGB16UI);
   gl_roundtrip(GL_RGB32UI);
   gl_roundtrip(GL_RGB8I);
   gl_roundtrip(GL_RGB16I);
   gl_roundtrip(GL_RGB32I);
   gl_roundtrip(GL_R11F_G11F_B10F);
   gl_roundtrip(GL_RGB16F);
   gl_roundtrip(GL_RGB32F);
   gl_roundtrip(GL_RGB9_E5);
   gl_roundtrip(GL_RGBA16);
   gl_roundtrip(GL_RGBA4);
   gl_roundtrip(GL_RGB5_A1);
   gl_roundtrip(GL_RGB10_A2);
   gl_roundtrip(GL_RGBA8_SNORM);
   gl_roundtrip(GL_RGBA16_SNORM);
   gl_roundtrip(GL_RGBA8UI);
   gl_roundtrip(GL_RGBA16UI);
   gl_roundtrip(GL_RGBA32UI);
   gl_roundtrip(GL_RGB10_A2UI);
   gl_roundtrip(GL_RGBA8I);
   gl_roundtrip(GL_RGBA16I);
   gl_roundtrip(GL_RGBA32I);
   gl_roundtrip(GL_RGBA16F);
   gl_roundtrip(GL_RGBA32F);
   gl_roundtrip(GL_SRGB8_ALPHA8);
   gl_roundtrip(GL_RGBA8);
}

#endif
