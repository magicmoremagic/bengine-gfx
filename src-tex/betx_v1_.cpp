#include "pch.hpp"
#include "tex/betx_reader.hpp"
#include "tex/mipmapping.hpp"
#include "tex/betx_read_error.hpp"
#include "betx_header_.hpp"
#include <glm/common.hpp>
#include <glm/vector_relational.hpp>

namespace be::gfx::tex {
namespace {

constexpr std::size_t footer_size = 4;

} // be::gfx::tex::()

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo BetxReader::info_v1_(const detail::BetxHeader& header, std::error_code& ec) noexcept {
   using err = detail::BetxReadError;
   using block_dim_type = ImageFormat::block_dim_type;

   TextureFileInfo info;
   info.file_format = TextureFileFormat::betx;

   // info.tex_class
   switch (header.texture_class) {
      case 0x0: info.tex_class = TextureClass::lineal; break;
      case 0x1: info.tex_class = TextureClass::lineal_array; break;
      case 0x2: info.tex_class = TextureClass::planar; break;
      case 0x3: info.tex_class = TextureClass::planar_array; break;
      case 0x4: info.tex_class = TextureClass::volumetric; break;
      case 0x5: info.tex_class = TextureClass::volumetric_array; break;
      case 0x6: info.tex_class = TextureClass::directional; break;
      case 0x7: info.tex_class = TextureClass::directional_array; break;

      default:
         info.tex_class = TextureClass::volumetric_array;
         if (!should_continue_(err::invalid_texture_class, ec)) {
            return info;
         }
         break;
   }

   // info.dim
   info.dim = ivec3(header.dim[0], header.dim[1], header.dim[2]);
   if (glm::any(glm::lessThanEqual(info.dim, ivec3()))) {
      if (should_continue_(err::invalid_dimensions, ec)) {
         info.dim = glm::max(info.dim, ivec3(1));
      } else {
         return info;
      }
   } else if (glm::any(glm::greaterThan(info.dim, ivec3(ivec3::value_type(TextureStorage::max_dim))))) {
      if (should_continue_(err::unsupported_dimensions, ec)) {
         info.dim = glm::min(info.dim, ivec3(TextureStorage::max_dim));
      } else {
         return info;
      }
   }

   // info.layers
   info.layers = header.layers;
   if (info.layers == 0) {
      if (should_continue_(err::invalid_layer_count, ec)) {
         info.layers = 1;
      } else {
         return info;
      }
   } else if (info.layers > TextureStorage::max_layers) {
      if (should_continue_(err::unsupported_layer_count, ec)) {
         info.layers = TextureStorage::max_layers;
      } else {
         return info;
      }
   }

   // info.faces
   info.faces = header.faces;
   if (info.faces == 0) {
      if (should_continue_(err::invalid_face_count, ec)) {
         info.faces = faces(info.tex_class);
      } else {
         return info;
      }
   } else if (info.faces > TextureStorage::max_faces) {
      if (should_continue_(err::unsupported_face_count, ec)) {
         info.faces = TextureStorage::max_faces;
      } else {
         return info;
      }
   }

   // info.levels
   info.levels = header.levels;
   if (info.levels == 0) {
      if (should_continue_(err::invalid_level_count, ec)) {
         info.levels = 1;
      } else {
         return info;
      }
   } else if (info.levels > TextureStorage::max_levels && !should_continue_(err::unsupported_level_count, ec)) {
      return info;
   } else if (info.levels > mipmap_levels(info.dim) && !should_continue_(err::unnecessary_levels, ec)) {
      return info;
   }

   // alignment_
   alignment_ = TextureAlignment(header.line_alignment,
                                 header.plane_alignment,
                                 header.level_alignment,
                                 header.face_alignment,
                                 header.layer_alignment);
   constexpr auto max_align_bits = TextureAlignment::max_alignment_bits;
   if ((header.line_alignment > max_align_bits ||
       header.plane_alignment > max_align_bits ||
       header.level_alignment > max_align_bits ||
       header.face_alignment > max_align_bits ||
       header.layer_alignment > max_align_bits) &&
       !should_continue_(err::unsupported_alignment, ec)) {
      return info;
   }
   if ((header.plane_alignment < header.line_alignment ||
       header.level_alignment < header.plane_alignment ||
       header.face_alignment < header.level_alignment ||
       header.layer_alignment < header.face_alignment) &&
       !should_continue_(err::noncanonical_alignment, ec)) {
      return info;
   }

   // info.format
   ImageFormat& format = info.format;

   // info.format.block_packing
   switch (header.block_packing) {
      case 0x00: format.packing(BlockPacking::s_8); break;
      case 0x01: format.packing(BlockPacking::s_8_8); break;
      case 0x02: format.packing(BlockPacking::s_8_8_8); break;
      case 0x03: format.packing(BlockPacking::s_8_8_8_8); break;
      case 0x04: format.packing(BlockPacking::s_16); break;
      case 0x05: format.packing(BlockPacking::s_16_16); break;
      case 0x06: format.packing(BlockPacking::s_16_16_16); break;
      case 0x07: format.packing(BlockPacking::s_16_16_16_16); break;
      case 0x08: format.packing(BlockPacking::s_32); break;
      case 0x09: format.packing(BlockPacking::s_32_32); break;
      case 0x0A: format.packing(BlockPacking::s_32_32_32); break;
      case 0x0B: format.packing(BlockPacking::s_32_32_32_32); break;
      case 0x0C: format.packing(BlockPacking::s_64); break;
      case 0x0D: format.packing(BlockPacking::s_64_64); break;
      case 0x0E: format.packing(BlockPacking::s_64_64_64); break;
      case 0x0F: format.packing(BlockPacking::s_64_64_64_64); break;
      case 0x10: format.packing(BlockPacking::p_4_4); break;
      case 0x11: format.packing(BlockPacking::p_3_3_2); break;
      case 0x12: format.packing(BlockPacking::p_2_3_3); break;
      case 0x13: format.packing(BlockPacking::p_3_2_3); break;
      case 0x14: format.packing(BlockPacking::p_4_2_2); break;
      case 0x15: format.packing(BlockPacking::p_2_2_4); break;
      case 0x16: format.packing(BlockPacking::p_2_4_2); break;
      case 0x17: format.packing(BlockPacking::p_2_2_2_2); break;
      case 0x18: format.packing(BlockPacking::p_4_4_4_4); break;
      case 0x19: format.packing(BlockPacking::p_1_5_5_5); break;
      case 0x1A: format.packing(BlockPacking::p_5_5_5_1); break;
      case 0x1B: format.packing(BlockPacking::p_6_5_5); break;
      case 0x1C: format.packing(BlockPacking::p_5_5_6); break;
      case 0x1D: format.packing(BlockPacking::p_5_6_5); break;
      case 0x1E: format.packing(BlockPacking::p_8_24); break;
      case 0x1F: format.packing(BlockPacking::p_24_8); break;
      case 0x20: format.packing(BlockPacking::p_11_11_10); break;
      case 0x21: format.packing(BlockPacking::p_10_11_11); break;
      case 0x22: format.packing(BlockPacking::p_11_10_11); break;
      case 0x23: format.packing(BlockPacking::p_8_8_8_8); break;
      case 0x24: format.packing(BlockPacking::p_9_9_9_5); break;
      case 0x25: format.packing(BlockPacking::p_5_9_9_9); break;
      case 0x26: format.packing(BlockPacking::p_10_10_10_2); break;
      case 0x27: format.packing(BlockPacking::p_2_10_10_10); break;
      case 0x28: format.packing(BlockPacking::s_32_p_24_8); break;
      case 0x29: format.packing(BlockPacking::c_astc); break;
      case 0x2A: format.packing(BlockPacking::c_bptc); break;
      case 0x2B: format.packing(BlockPacking::c_etc1); break;
      case 0x2C: format.packing(BlockPacking::c_etc2); break;
      case 0x2D: format.packing(BlockPacking::c_s3tc1); break;
      case 0x2E: format.packing(BlockPacking::c_s3tc2); break;
      case 0x2F: format.packing(BlockPacking::c_s3tc3); break;
      case 0x30: format.packing(BlockPacking::c_rgtc1); break;
      case 0x31: format.packing(BlockPacking::c_rgtc2); break;

      default:
         format.packing(BlockPacking::s_8_8_8_8);
         if (!should_continue_(err::invalid_block_packing, ec)) {
            return info;
         }
         break;
   }

   // info.format.block_dim
   block_dim_type block_dim = block_dim_type(header.block_dim[0], header.block_dim[1], header.block_dim[2]);
   if (glm::any(glm::equal(block_dim, block_dim_type()))) {
      format.block_dim(glm::max(block_dim, block_dim_type(1)));
      if (!should_continue_(err::invalid_block_dimensions, ec)) {
         return info;
      }
   } else if (glm::any(glm::greaterThan(block_dim, block_dim_type(block_dim_type::value_type(ImageFormat::max_block_dim))))) {
      format.block_dim(glm::min(block_dim, block_dim_type(ImageFormat::max_block_dim)));
      if (!should_continue_(err::unsupported_block_dimensions, ec)) {
         return info;
      }
   } else {
      format.block_dim(block_dim);
   }

   // info.format.block_size
   if (header.block_size == 0) {
      format.block_size(std::max(static_cast<U8>(1),
                                 static_cast<U8>(block_pixel_size(format.packing()) *
                                                 format.block_dim().x *
                                                 format.block_dim().y *
                                                 format.block_dim().z)));
      if (!should_continue_(err::invalid_block_size, ec)) {
         return info;
      }
   } else if (header.block_size > ImageFormat::max_block_size) {
      format.block_size(std::min(static_cast<ImageFormat::block_size_type>(ImageFormat::max_block_size), header.block_size));
      if (!should_continue_(err::unsupported_block_size, ec)) {
         return info;
      }
   } else {
      format.block_size(header.block_size);
   }

   // info.format.component_type
   U8 expected_components = 0;
   for (glm::length_t c = 0; c < 4; ++c) {
      switch (header.field_types[c]) {
         case 0x0: format.field_type(c, FieldType::none); break;
         case 0x1: ++expected_components; format.field_type(c, FieldType::unorm); break;
         case 0x2: ++expected_components; format.field_type(c, FieldType::snorm); break;
         case 0x3: ++expected_components; format.field_type(c, FieldType::uint); break;
         case 0x4: ++expected_components; format.field_type(c, FieldType::sint); break;
         case 0x5: ++expected_components; format.field_type(c, FieldType::ufloat); break;
         case 0x6: ++expected_components; format.field_type(c, FieldType::sfloat); break;
         case 0x7: ++expected_components; format.field_type(c, FieldType::expo); break;

         default:
            format.field_type(c, FieldType::none);
            if (!should_continue_(err::invalid_field_type, ec)) {
               return info;
            }
            break;
      }
   }

   // info.format.components
   if (header.components == 0) {
      format.components(std::max(static_cast<U8>(1), expected_components));
      if (!should_continue_(err::invalid_component_count, ec)) {
         return info;
      }
   } else {
      format.components(header.components);
      if (header.components > 4 && !should_continue_(err::too_many_components, ec)) {
         return info;
      }
   }

   // info.format.swizzle
   for (glm::length_t c = 0; c < 4; ++c) {
      switch (header.swizzle[c]) {
         case 0x0: format.swizzle(c, Swizzle::field_zero); break;
         case 0x1: format.swizzle(c, Swizzle::field_one); break;
         case 0x2: format.swizzle(c, Swizzle::field_two); break;
         case 0x3: format.swizzle(c, Swizzle::field_three); break;
         case 0x4: format.swizzle(c, Swizzle::literal_zero); break;
         case 0x5: format.swizzle(c, Swizzle::literal_one); break;

         default:
            format.swizzle(c, Swizzle::literal_zero);
            if (!should_continue_(err::invalid_swizzle, ec)) {
               return info;
            }
            break;
      }
   }

   // info.format.colorspace
   switch (header.colorspace) {
      case 0x00: format.colorspace(Colorspace::unknown); break;
      case 0x01: format.colorspace(Colorspace::linear_other); break;
      case 0x02: format.colorspace(Colorspace::linear_depth_stencil); break;
      case 0x03: format.colorspace(Colorspace::linear_depth); break;
      case 0x04: format.colorspace(Colorspace::linear_stencil); break;
      case 0x05: format.colorspace(Colorspace::bt709_linear_rgb); break;
      case 0x06: format.colorspace(Colorspace::bt709_linear_hsl); break;
      case 0x07: format.colorspace(Colorspace::bt709_linear_hsv); break;
      case 0x08: format.colorspace(Colorspace::bt709_linear_ycbcr); break;
      case 0x09: format.colorspace(Colorspace::bt709_rgb); break;
      case 0x0A: format.colorspace(Colorspace::bt709_hsl); break;
      case 0x0B: format.colorspace(Colorspace::bt709_hsv); break;
      case 0x0C: format.colorspace(Colorspace::bt709_ycbcr); break;
      case 0x0D: format.colorspace(Colorspace::srgb); break;
      case 0x0E: format.colorspace(Colorspace::srgb_hsl); break;
      case 0x0F: format.colorspace(Colorspace::srgb_hsv); break;
      case 0x10: format.colorspace(Colorspace::srgb_ycbcr); break;
      case 0x11: format.colorspace(Colorspace::cie_xyz); break;
      case 0x12: format.colorspace(Colorspace::cie_lab_d65); break;
      case 0x13: format.colorspace(Colorspace::cie_lchab_d65); break;
      case 0x14: format.colorspace(Colorspace::cie_luv_d65); break;
      case 0x15: format.colorspace(Colorspace::cie_lchuv_d65); break;
      case 0x16: format.colorspace(Colorspace::cie_xyy); break;

      default:
         format.colorspace(Colorspace::unknown);
         if (!should_continue_(err::invalid_colorspace, ec)) {
            return info;
         }
         break;
   }

   // info.format.premultiplied
   format.premultiplied(0 != (header.format_flags & 1u));

   // check for illegal format flags
   if (0 != (header.format_flags & ~1u) &&
       !should_continue_(err::invalid_format_flag, ec)) {
      return info;
   }

   // block_span_
   block_span_ = header.block_span;
   if (block_span_ == 0) {
      block_span_ = format.block_size();
      if (!should_continue_(err::invalid_block_span, ec)) {
         return info;
      }
   } else if (format.block_size() > header.block_span) {
      block_span_ = format.block_size();
      if (!should_continue_(err::negative_block_padding, ec)) {
         return info;
      }
   } else {
      block_span_ = header.block_span;
   }

   // payload_compression_
   switch (header.payload_compression) {
      case 0x0: payload_compression_ = detail::BetxPayloadCompressionMode::none; break;
      case 0x1: payload_compression_ = detail::BetxPayloadCompressionMode::zlib; break;

      default:
         payload_compression_ = detail::BetxPayloadCompressionMode::none;
         if (!should_continue_(err::invalid_payload_compression, ec)) {
            return info;
         }
         break;
   }

   // texture_size_
   std::error_code ec2;
   texture_size_ = calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim, info.format.block_dim(), block_span_, ec2, alignment_);
   if (ec2 == std::errc::value_too_large) {
      if (!should_continue_(err::unsupported_alignment, ec)) {
         return info;
      }
   } else if (ec2 && !should_continue_(err::empty_texture, ec)) {
      return info;
   }

   // payload_, metadata_
   payload_ = sub_buf(buf_, header.payload_offset, header.payload_size);
   std::size_t expected_buf_size = sizeof(detail::BetxHeader) + header.payload_size + footer_size;
   if (header.metadata_location == 0x01) {
      // metadata after header
      expected_buf_size += sizeof(U64);
      U64 metadata_size = 0;
      if (buf_.size() >= sizeof(detail::BetxHeader) + sizeof(U64)) {
         std::memcpy(&metadata_size, buf_.get() + sizeof(detail::BetxHeader), sizeof(U64));
         if (big_endian_) {
            bo::static_to_host<bo::Big::value>(metadata_size);
         } else {
            bo::static_to_host<bo::Little::value>(metadata_size);
         }
         metadata_ = sub_buf(buf_, sizeof(detail::BetxHeader) + sizeof(U64), metadata_size);
      } else if (!should_continue_(err::metadata_missing, ec)) {
         return info;
      }

      if (header.payload_offset < sizeof(detail::BetxHeader) + sizeof(U64) + metadata_size && !should_continue_(err::invalid_payload_offset, ec)) {
         return info;
      }

      expected_buf_size += metadata_size;
   } else {
      // no metadata or metadata after payload
      if (header.payload_offset < sizeof(detail::BetxHeader) && !should_continue_(err::invalid_payload_offset, ec)) {
         return info;
      }

      if (header.metadata_location == 0x02) {
         // metadata after payload
         std::size_t metadata_offset = aligned_size(header.payload_offset + header.payload_size, 8ull);
         if (buf_.size() >= metadata_offset + sizeof(U64)) {
            U64 metadata_size;
            std::memcpy(&metadata_size, buf_.get() + metadata_offset, sizeof(U64));
            if (big_endian_) {
               bo::static_to_host<bo::Big::value>(metadata_size);
            } else {
               bo::static_to_host<bo::Little::value>(metadata_size);
            }
            metadata_ = sub_buf(buf_, sizeof(detail::BetxHeader) + sizeof(U64), metadata_size);
            expected_buf_size += metadata_size;
         } else if (!should_continue_(err::metadata_missing, ec)) {
            return info;
         }
      } else if (header.metadata_location != 0x0 && !should_continue_(err::invalid_metadata_location, ec)) {
         return info;
      }
   }

   // validate buf size
   if (expected_buf_size > buf_.size() && !should_continue_(err::file_too_small, ec)) {
      return info;
   }
   if (payload_compression_ == detail::BetxPayloadCompressionMode::none && payload_.size() < texture_size_ && !should_continue_(err::not_enough_texture_data, ec)) {
      return info;
   }

   // validate layer count
   if (!is_array(info.tex_class) && info.layers > 1 && !should_continue_(err::layered_non_array, ec)) {
      return info;
   }

   // validate face count
   if (info.faces < faces(info.tex_class) && !should_continue_(err::not_enough_faces, ec)) {
      return info;
   } else if (info.faces > faces(info.tex_class) && !should_continue_(err::too_many_faces, ec)) {
      return info;
   }

   // header.reserved
   if (header.reserved != 0x0 && !should_continue_(err::nonzero_reserved, ec)) {
      return info;
   }

   return info;
}

} // be::gfx::tex
