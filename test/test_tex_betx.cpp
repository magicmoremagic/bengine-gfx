#ifdef BE_TEST

#include "tostring.hpp"
#include "tex/image.hpp"
#include "tex/make_texture.hpp"
#include "tex/betx_read_error.hpp"
#include "tex/betx_reader.hpp"
#include "tex/betx_writer.hpp"
#include "tex/pixel_access_norm.hpp"
#include "tex/visit_texture.hpp"
#include "tex/visit_image.hpp"
#include "tex/image_format_gl.hpp"
#include <be/util/xoroshiro_128_plus.hpp>
#include <glm/vector_relational.hpp>
#include <random>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:betx]"

using namespace be;
using namespace be::gfx::tex;
using namespace std::literals::string_view_literals;

TEST_CASE("BetxReader", BE_CATCH_TAGS) {
   BetxReader reader;

   auto old_mask = default_log().verbosity_mask(v::fatal);

   SECTION("Planar 1x1x1 R8") {
      SV good_data = "\x57\xC0\x4D\x4D\x62\x65\x54\x78\x0D\x0A\x1A\x0A\x4F\xE9\x39\xFD\x01\x00\x02\x00\x01\x00\x01\x01\x01\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x01\x01\x01\x01\x00\x01\x0D\x00\x01\x00\x00\x00\x00\x00\x00\x05\x48\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x33\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x62\x65\x54\x78"sv;
      Buf<UC> data = copy_buf(tmp_buf(good_data));

      SECTION("BetxReadError::not_a_mmm_binary_file") {
         data[1] = 0x57;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::not_a_mmm_binary_file);
      }

      SECTION("BetxReadError::not_a_betx_file") {
         data[6] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::not_a_betx_file);
      }

      SECTION("BetxReadError::crlf_corruption") {
         std::memmove(data.get() + 8, data.get() + 9, data.size() - 9);
         data = copy_buf(sub_buf(data, 0, data.size() - 1));
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::crlf_corruption);
      }

      SECTION("BetxReadError::lf_corruption") {
         auto data2 = make_buf<UC>(data.size() + 1);
         std::memcpy(data2.get(), data.get(), 0xB);
         std::memcpy(data2.get() + 0xC, data.get() + 0xB, data.size() - 0xB);
         data = std::move(data2);
         data[0xB] = 0xD;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::lf_corruption);
      }

      SECTION("BetxReadError::header_missing") {
         data = copy_buf(sub_buf(data, 0, 20));
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::header_missing);
      }

      SECTION("BetxReadError::footer_missing") {
         data = copy_buf(sub_buf(data, 0, data.size() - 4));
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::footer_missing);
      }

      SECTION("BetxReadError::invalid_endianness") {
         data[0x11] = 0x20;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_endianness);
      }

      SECTION("BetxReadError::unsupported_file_version") {
         data[0x10] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(!ec);
      }

      SECTION("BetxReadError::unsupported_file_version") {
         data[0x10] = 0xFF;
         std::error_code ec;
         BetxReader strictreader(true);
         strictreader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         strictreader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::unsupported_file_version);
      }

      SECTION("BetxReadError::invalid_texture_class") {
         data[0x12] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_texture_class);
      }

      SECTION("BetxReadError::invalid_dimensions") {
         data[0x18] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_dimensions);
      }

      SECTION("BetxReadError::unsupported_dimensions") {
         data[0x1F] = 0x7F;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::unsupported_dimensions);
      }

      SECTION("BetxReadError::invalid_layer_count") {
         data[0x14] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_layer_count);
      }

      SECTION("BetxReadError::invalid_face_count") {
         data[0x16] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_face_count);
      }

      SECTION("BetxReadError::invalid_level_count") {
         data[0x17] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_level_count);
      }
      
      SECTION("BetxReadError::unsupported_level_count") {
         data[0x17] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::unsupported_level_count);
      }

      SECTION("BetxReadError::unnecessary_levels") {
         data[0x17] = 2;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::unnecessary_levels);
      }
      
      SECTION("BetxReadError::unsupported_alignment") {
         data[0x41] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::unsupported_alignment);
      }

      SECTION("BetxReadError::noncanonical_alignment") {
         data[0x41] = 1;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::noncanonical_alignment);
      }
      
      SECTION("BetxReadError::invalid_block_packing") {
         data[0x28] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_block_packing);
      }

      SECTION("BetxReadError::invalid_block_dimensions") {
         data[0x26] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_block_dimensions);
      }
      
      SECTION("BetxReadError::invalid_block_size") {
         data[0x24] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_block_size);
      }

      SECTION("BetxReadError::invalid_field_type") {
         data[0x2C] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_field_type);
      }

      SECTION("BetxReadError::invalid_component_count") {
         data[0x29] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_component_count);
      }

      SECTION("BetxReadError::too_many_components") {
         data[0x29] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::too_many_components);
      }

      SECTION("BetxReadError::invalid_swizzle") {
         data[0x30] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_swizzle);
      }

      SECTION("BetxReadError::invalid_colorspace") {
         data[0x2A] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_colorspace);
      }
      
      SECTION("BetxReadError::invalid_format_flag") {
         data[0x2B] = 0xFF;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_format_flag);
      }

      SECTION("BetxReadError::invalid_block_span") {
         data[0x40] = 0;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_block_span);
      }

      SECTION("BetxReadError::invalid_payload_compression") {
         data[0x47] = 0xFD;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_payload_compression);
      }

      SECTION("BetxReadError::invalid_payload_offset") {
         data[0x34] = 0x20;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_payload_offset);
      }

      SECTION("BetxReadError::invalid_metadata_location") {
         data[0x13] = 0xAA;
         std::error_code ec;
         reader.read(tmp_buf(data), ec);
         REQUIRE(!ec);
         reader.info(ec);
         REQUIRE(ec == be::gfx::tex::detail::BetxReadError::invalid_metadata_location);
      }

      SECTION("Normal") {
         reader.read(tmp_buf(data));

         REQUIRE(reader.format() == TextureFileFormat::betx);

         TextureFileInfo ifo = reader.info();

         REQUIRE(ifo.file_format == TextureFileFormat::betx);
         REQUIRE(ifo.tex_class == TextureClass::planar);
         REQUIRE(ifo.format.block_size() == 1);
         REQUIRE(ifo.format.block_dim() == ImageFormat::block_dim_type(1, 1, 1));
         REQUIRE(ifo.format.packing() == BlockPacking::s_8);
         REQUIRE(ifo.format.components() == 1);
         REQUIRE(ifo.format.field_types() == field_types(FieldType::unorm));
         REQUIRE(ifo.format.swizzles() == swizzles_rrr());
         REQUIRE(ifo.format.colorspace() == Colorspace::srgb);
         REQUIRE(ifo.format.premultiplied() == false);
         REQUIRE(ifo.dim == ivec3(1, 1, 1));
         REQUIRE(ifo.layers == 1);
         REQUIRE(ifo.faces == 1);
         REQUIRE(ifo.levels == 1);

         REQUIRE(reader.info().format == ifo.format);

         auto tex = reader.texture();
         REQUIRE(tex.view.format() == ifo.format);

         F32 comp = 0x33 / ( F32 ) 0xFF;
         REQUIRE(glm::all(glm::lessThan(glm::abs(get_pixel_norm(tex.view.image(), 0) - vec4(comp, comp, comp, 1.f)), vec4(1e-6f))));
      }

      default_log().verbosity_mask(old_mask);
   }
}

void roundtrip_test(util::xo128p& prng, TextureClass clazz, ImageFormat format, ivec3 dim, U8 layers = 1, U8 levels = 1, TextureAlignment alignment = TextureAlignment()) {
   Texture t = make_texture(clazz, format, dim, layers, levels, Buf<UC>(), alignment);
   
   std::uniform_real_distribution<F32> dist(0, 1.f);

   visit_texture_pixels<ivec3>(t.view, [&](ImageView& v, ivec3 pc) {
      put_pixel_norm(v, pc, vec4(dist(prng), dist(prng), dist(prng), dist(prng)));
   });

   BetxWriter writer;
   if ((prng() & 1) != 0) {
      writer.endianness();
   }
   if ((prng() & 1) != 0) {
      writer.payload_compression();
   }

   writer.texture(t.view);

   std::error_code ec;
   Buf<UC> data = writer.write(ec);
   REQUIRE(!ec);


   BetxReader reader(true);
   reader.read(tmp_buf(data), ec);
   REQUIRE(!ec);

   Texture t2 = reader.texture(ec);
   REQUIRE(!ec);

   REQUIRE(t2.view.texture_class() == t.view.texture_class());
   REQUIRE(t2.view.layers() == t.view.layers());
   REQUIRE(t2.view.faces() == t.view.faces());
   REQUIRE(t2.view.levels() == t.view.levels());
   REQUIRE(t2.view.dim(0) == t.view.dim(0));
   REQUIRE(t2.view.block_dim() == t.view.block_dim());
   REQUIRE(t2.view.block_span() == t.view.block_span());
   REQUIRE(t2.view.line_span(0) == t.view.line_span(0));
   REQUIRE(t2.view.plane_span(0) == t.view.plane_span(0));
   REQUIRE(t2.view.face_span() == t.view.face_span());
   REQUIRE(t2.view.layer_span() == t.view.layer_span());
   REQUIRE(t2.view.format() == t.view.format());
   
   visit_texture_images(t.view, [&](ImageView& v) {
      ImageView v2 = t2.view.image(v.layer(), v.face(), v.level());
      visit_image_pixels<ivec3>(v, [&](ImageView&, ivec3 pc) {
         REQUIRE(get_pixel_norm(v, pc) == get_pixel_norm(v2, pc));
      });
   });
}

TEST_CASE("Betx Round Trips", BE_CATCH_TAGS) {
   util::xo128p prng;
   prng.seed(( U64 ) Id("that's how you get ants."));

   roundtrip_test(prng, TextureClass::planar, canonical_format(be::gfx::gl::GL_RGBA8), ivec3(4,5,1), 1, 2);
   roundtrip_test(prng, TextureClass::planar, canonical_format(be::gfx::gl::GL_RGBA32F), ivec3(4,5,1), 1, 2);
   roundtrip_test(prng, TextureClass::volumetric_array, canonical_format(be::gfx::gl::GL_RG8), ivec3(32,16,4), 2, 4);
}

#endif
