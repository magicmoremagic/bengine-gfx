#include "pch.hpp"
#include "tex/read_ktx.hpp"
#include "tex/image_format_gl.hpp"
#include "ktx_11_.hpp"
#include <be/util/check_file_signature.hpp>

namespace be::gfx::tex {
namespace {

constexpr UC signature[] = { 0xAB, 'K', 'T', 'X', ' ', '1', '1', 0xBB, '\r', '\n', 0x1A, '\n'  };

///////////////////////////////////////////////////////////////////////////////
ktx::detail::KtxHeader read_betx_header(const Buf<const UC>& buf, TextureFileReadError& err) {
   using namespace ktx::detail;
   KtxHeader header;

   if (buf.size() >= sizeof(KtxHeader)) {
      std::memcpy(&header, buf.get(), sizeof(KtxHeader));
      bo::static_to_little<bo::Big::value>(header);

      if (header.endianness != 0x04030201) {
         err = TextureFileReadError::file_corruption;
      }
   } else {
      std::memset(&header, 0, sizeof(KtxHeader));
      err = TextureFileReadError::file_corruption;
   }

   return header;
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_ktx_info_v1(const ktx::detail::KtxHeader header, const std::size_t buf_size) {
   using namespace ktx::detail;

   std::pair<TextureFileInfo, TextureFileReadError> result;
   result.second = TextureFileReadError::none;

   //TextureFileInfo& info = result.first;
   //TextureFileReadError& err = result.second;

   //info.file_format = TextureFileFormat::ktx;
   //info.layers = header.number_of_array_elements;
   //info.faces = header.number_of_faces;
   //info.levels = header.number_of_mipmap_levels;
   //info.dim = ivec3((I32)header.pixel_width, (I32)header.pixel_height, (I32)header.pixel_depth);
   //info.tex_class = get_texture_class_v11(header, err);

   //using block_dim_type = ImageFormat::block_dim_type;

   //ImageFormatGl gl_fmt;
   //gl_fmt.internal_format = get_internal_format_v11(header.gl_internal_format, err);
   //gl_fmt.data_format = get_data_format_v11(header.gl_format, err);
   //gl_fmt.data_type = get_data_type_v11(header.gl_type, err);

   //info.format = gl_format(gl_fmt);

   //ImageFormat& format = info.format;
   //format = ImageFormat(header.block_size,
   //                     block_dim_type(header.block_dim[0],
   //                     header.block_dim[1],
   //                     header.block_dim[2]),
   //                     get_block_packing_v1(header.block_packing, err),
   //                     header.components,
   //                     component_types(get_component_type_v1(header.component_types[0], err),
   //                     get_component_type_v1(header.component_types[1], err),
   //                     get_component_type_v1(header.component_types[2], err),
   //                     get_component_type_v1(header.component_types[3], err)),
   //                     swizzles(get_swizzle_v1(header.swizzle[0], err),
   //                     get_swizzle_v1(header.swizzle[1], err),
   //                     get_swizzle_v1(header.swizzle[2], err),
   //                     get_swizzle_v1(header.swizzle[3], err)),
   //                     get_colorspace_v1(header.colorspace, err),
   //                     0 != (header.format_flags & 1u));

   //TextureAlignment alignment = get_alignment_v1(header);
   //PayloadCompressionMode compression = get_payload_compression_mode_v1(header.payload_compression, err);
   //std::size_t required_size = header.payload_offset + header.payload_size + sizeof(footer);

   //if (glm::any(glm::lessThanEqual(info.dim, ivec3())) ||
   //    0 == info.layers ||
   //    0 == info.faces ||
   //    0 == info.levels ||
   //    0 == format.block_size() ||
   //    glm::any(glm::equal(format.block_dim(), block_dim_type())) ||
   //    format.components() < 1 || format.components() > 4 ||
   //    0u != (header.format_flags & (~1u)) ||
   //    format.block_size() > header.block_span ||
   //    header.payload_offset < sizeof(BeTxHeader) ||
   //    header.line_span_granularity > TextureAlignment::max_alignment_bits ||
   //    header.plane_span_granularity > TextureAlignment::max_alignment_bits ||
   //    header.level_span_granularity > TextureAlignment::max_alignment_bits ||
   //    header.face_span_granularity > TextureAlignment::max_alignment_bits ||
   //    header.layer_span_granularity > TextureAlignment::max_alignment_bits ||
   //    (is_array(info.tex_class) && info.layers > 1) ||
   //    buf_size < required_size) {
   //   err = TextureFileReadError::file_corruption;
   //}

   //if (err == TextureFileReadError::none) {
   //   if (format.block_size() > ImageFormat::max_block_size ||
   //       glm::any(glm::greaterThan(format.block_dim(), block_dim_type(block_dim_type::value_type(ImageFormat::max_block_dim)))) ||
   //       alignment.plane() > std::numeric_limits<U32>::max()) {
   //      err = TextureFileReadError::unsupported_texture;
   //   } else if (glm::any(glm::greaterThan(info.dim, ivec3(TextureStorage::max_dim))) ||
   //              info.levels > TextureStorage::max_levels ||
   //              info.faces > TextureStorage::max_faces ||
   //              info.layers > TextureStorage::max_layers) {
   //      err = TextureFileReadError::unsupported_texture_size;
   //   } else {
   //      std::size_t texture_size =  calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim,
   //                                                                     format.block_dim(), header.block_span, alignment);
   //      if (texture_size == 0) {
   //         err = TextureFileReadError::unsupported_texture_size;
   //      } else if (compression == PayloadCompressionMode::none && header.payload_size != texture_size) {
   //         err = TextureFileReadError::file_corruption;
   //      }
   //   }
   //}

   return result;
}

} // be::gfx::tex::()

///////////////////////////////////////////////////////////////////////////////
bool is_ktx(const Buf<const UC>& buf) {
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_ktx_info(const Buf<const UC>& buf) {
   return std::make_pair(TextureFileInfo(), TextureFileReadError::file_corruption);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_ktx_texture(const Buf<const UC>& buf) {
   return std::make_pair(Texture(), TextureFileReadError::file_corruption);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_ktx_image(const Buf<const UC>& buf) {
   return std::make_pair(Image(), TextureFileReadError::file_corruption);
}


} // be::gfx::tex
