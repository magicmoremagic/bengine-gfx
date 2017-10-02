#include "pch.hpp"
#include "ktx_header_.hpp"
#include "tex/ktx_read_error.hpp"
#include "tex/texture_class.hpp"
#include "tex/ktx_reader.hpp"
#include "tex/mipmapping.hpp"
#include "tex/image_format_gl.hpp"
#include <be/core/enum_vec3.hpp>
#include <glm/common.hpp>
#include <glm/vector_relational.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo KtxReader::info_v11_(const detail::KtxHeader& header, std::error_code& ec) noexcept {
   using namespace gl;
   using err = detail::KtxReadError;

   TextureFileInfo info;
   info.file_format = TextureFileFormat::ktx;
   info.layers = TextureStorage::layer_index_type(header.number_of_array_elements);
   info.faces = TextureStorage::face_index_type(header.number_of_faces);
   info.levels = TextureStorage::level_index_type(header.number_of_mipmap_levels);
   info.dim = ivec3((I32)header.pixel_width, (I32)header.pixel_height, (I32)header.pixel_depth);

   // info.tex_class
   U8 dimensionality;
   if (header.pixel_depth > 0) {
      dimensionality = 3;
      if (header.pixel_height == 0) {
         if (!should_continue_(err::invalid_dimensions, ec)) {
            return info;
         }
      }
   } else if (header.pixel_height > 0) {
      dimensionality = 2;
   } else {
      dimensionality = 1;
   }

   if (header.pixel_width == 0 && !should_continue_(err::invalid_dimensions, ec)) {
      return info;
   }

   bool is_array = info.layers > 0;

   if (info.faces > 1) {
      info.tex_class = is_array ? TextureClass::directional_array : TextureClass::directional;
      if (dimensionality != 2 && !should_continue_(err::invalid_face_count, ec)) {
         return info;
      }
   } else switch (dimensionality) {
      case 1:  info.tex_class = is_array ? TextureClass::lineal_array : TextureClass::lineal; break;
      case 2:  info.tex_class = is_array ? TextureClass::planar_array : TextureClass::planar; break;
      case 3:  info.tex_class = is_array ? TextureClass::volumetric_array : TextureClass::volumetric; break;
      default:
         info.tex_class = TextureClass::volumetric_array;
         if (!should_continue_(err::invalid_texture_class, ec)) {
            return info;
         }
         break;
   }
   
   // info.dim
   for (glm::length_t i = dimensionality; i < info.dim.length(); ++i) {
      info.dim[i] = 1;
   }
   if (glm::any(glm::greaterThan(info.dim, ivec3(ivec3::value_type(TextureStorage::max_dim))))) {
      if (should_continue_(err::unsupported_dimensions, ec)) {
         info.dim = glm::min(info.dim, ivec3(TextureStorage::max_dim));
      } else {
         return info;
      }
   }
   
   // info.layers
   if (header.number_of_array_elements > TextureStorage::max_layers) {
      if (should_continue_(err::unsupported_layer_count, ec)) {
         info.layers = TextureStorage::max_layers;
      } else {
         return info;
      }
   } else if (info.layers == 0) {
      info.layers = 1;
   }

   // info.faces
   if (header.number_of_faces > TextureStorage::max_faces) {
      if (should_continue_(err::unsupported_face_count, ec)) {
         info.faces = TextureStorage::max_faces;
      } else {
         return info;
      }
   } else if (info.faces == 0) {
      info.faces = faces(info.tex_class);
   }

   // info.levels
   if (header.number_of_mipmap_levels > TextureStorage::max_levels && !should_continue_(err::unsupported_level_count, ec)) {
      return info;
   } else if (info.levels > mipmap_levels(info.dim) && !should_continue_(err::unnecessary_levels, ec)) {
      return info;
   } else if (info.levels == 0) {
      // technically this means "generate mipmaps at load time" according to the spec, but we're not going to.
      info.levels = 1;
   }

   ImageFormatGl gl_fmt;
   gl_fmt.base_internal_format = header.gl_base_internal_format;
   gl_fmt.internal_format = header.gl_internal_format;
   gl_fmt.data_format = header.gl_format;
   gl_fmt.data_type = header.gl_type;
   gl_fmt.swizzle[0] = GL_RED;
   gl_fmt.swizzle[1] = GL_GREEN;
   gl_fmt.swizzle[2] = GL_BLUE;
   gl_fmt.swizzle[3] = GL_ALPHA;

   be_debug() << "KTX format enums"
      & attr("Base Internal Format") << enum_name(gl_fmt.base_internal_format) << " (" << gl_fmt.base_internal_format << ")"
      & attr("Internal Format") << enum_name(gl_fmt.internal_format) << " (" << gl_fmt.internal_format << ")"
      & attr("Data Format") << enum_name(gl_fmt.data_format) << " (" << gl_fmt.data_format << ")"
      & attr("Data Type") << enum_name(gl_fmt.data_type) << " (" << gl_fmt.data_type << ")"
      | log();

   std::error_code ec2;
   info.format = from_gl_format(gl_fmt, ec2);
   if (ec2 && !should_continue_(err::unsupported_image_format, ec)) {
      return info;
   }

   if (!is_compressed(info.format.packing()) && header.gl_type_size != block_word_size(info.format.packing())) { 
      be_notice() << "Block word size mismatch"
         & attr("Expected") << U32(block_word_size(info.format.packing()))
         & attr("Found") << header.gl_type_size
         | log();

      if (!should_continue_(err::invalid_gl_type_size, ec)) {
         return info;
      }
   }

   if (buf_.size() < sizeof(header) + header.bytes_of_key_value_data && !should_continue_(err::metadata_missing, ec)) {
      return info;
   } else {
      metadata_.clear();
      SV metadata = SV(static_cast<const char*>(static_cast<const void*>(buf_.get())) + sizeof(header), header.bytes_of_key_value_data);
      
      while (metadata.length() > sizeof(U32)) {
         U32 kv_size;
         std::memcpy(&kv_size, metadata.data(), sizeof(U32));
         if (big_endian_) {
            kv_size = bo::to_host<bo::Big::value>(kv_size);
         } else {
            kv_size = bo::to_host<bo::Little::value>(kv_size);
         }

         if (sizeof(U32) + kv_size <= metadata.length()) {
            SV key = SV(metadata.data() + sizeof(U32));
            std::size_t offset = sizeof(U32) + key.length();
            SV value = SV(metadata.data() + offset, kv_size - offset);

            metadata_.push_back(std::make_pair(key, value));
         }

         metadata.remove_prefix(aligned_size<sizeof(U32)>(sizeof(U32) + kv_size));
      }
   }

   payload_ = sub_buf(buf_, sizeof(header) + header.bytes_of_key_value_data);


   // texture_size_
   ec2 = std::error_code();
   texture_size_ = calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim, info.format.block_dim(), info.format.block_size(), ec2, TextureAlignment(2));
   if (ec2 && !should_continue_(err::empty_texture, ec)) {
      return info;
   }
   if (payload_.size() < texture_size_ + sizeof(U32) * info.levels && !should_continue_(err::not_enough_texture_data, ec)) {
      return info;
   }

   // validate layer count
   if (!tex::is_array(info.tex_class) && info.layers > 1 && !should_continue_(err::layered_non_array, ec)) {
      return info;
   }

   // validate face count
   if (info.faces < faces(info.tex_class) && !should_continue_(err::not_enough_faces, ec)) {
      return info;
   } else if (info.faces > faces(info.tex_class) && !should_continue_(err::too_many_faces, ec)) {
      return info;
   }

   return info;
}

} // be::gfx::tex
