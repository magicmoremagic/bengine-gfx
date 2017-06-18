#include "pch.hpp"
#include "tex/read_betx.hpp"
#include "tex/texture_storage.hpp"
#include "tex/make_texture.hpp"
#include "tex/make_image.hpp"
#include "betx_header_.hpp"
#include "betx_v1_.hpp"
#include "betx_payload_compression_mode_.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/util/zlib.hpp>
#include <be/core/glm.hpp>
#include <glm/vector_relational.hpp>

namespace be::gfx::tex {
namespace {

constexpr UC signature[] = { 0x57, 0xC0, 'M', 'M', 'b', 'e', 'T', 'x', '\r', '\n', 0x1a, '\n', 0x4F, 0xE9, 0x39, 0xFD };
constexpr UC footer[] = { 'b', 'e', 'T', 'x' };

///////////////////////////////////////////////////////////////////////////////
betx::detail::BeTxHeader read_betx_header(const Buf<const UC>& buf, TextureFileReadError& err) {
   using namespace betx::detail;
   BeTxHeader header;

   if (buf.size() >= sizeof(BeTxHeader) + sizeof(footer)) {
      std::memcpy(&header, buf.get(), sizeof(BeTxHeader));

      if (header.endianness == 0) {
         bo::static_to_host<bo::Little::value>(header);
      } else if (header.endianness == 0xFFu) {
         bo::static_to_host<bo::Big::value>(header);
      } else {
         err = TextureFileReadError::file_corruption;
      }
   } else {
      std::memset(&header, 0, sizeof(BeTxHeader));
      err = TextureFileReadError::file_corruption;
   }

   return header;
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_betx_info_v1(const betx::detail::BeTxHeader header, const std::size_t buf_size) {
   using namespace betx::detail;

   std::pair<TextureFileInfo, TextureFileReadError> result;
   result.second = TextureFileReadError::none;

   TextureFileInfo& info = result.first;
   TextureFileReadError& err = result.second;

   info.file_format = TextureFileFormat::betx;
   info.layers = header.layers;
   info.faces = header.faces;
   info.levels = header.levels;
   info.dim = ivec3(header.dim[0], header.dim[1], header.dim[2]);
   info.tex_class = get_texture_class_v1(header.texture_class, err);

   using block_dim_type = ImageFormat::block_dim_type;

   ImageFormat& format = info.format;
   format = ImageFormat(header.block_size,
                        block_dim_type(header.block_dim[0],
                        header.block_dim[1],
                        header.block_dim[2]),
                        get_block_packing_v1(header.block_packing, err),
                        header.components,
                        component_types(get_component_type_v1(header.component_types[0], err),
                                        get_component_type_v1(header.component_types[1], err),
                                        get_component_type_v1(header.component_types[2], err),
                                        get_component_type_v1(header.component_types[3], err)),
                        swizzles(get_swizzle_v1(header.swizzle[0], err),
                                 get_swizzle_v1(header.swizzle[1], err),
                                 get_swizzle_v1(header.swizzle[2], err),
                                 get_swizzle_v1(header.swizzle[3], err)),
                        get_colorspace_v1(header.colorspace, err),
                        0 != (header.format_flags & 1u));

   TextureAlignment alignment = get_alignment_v1(header);
   PayloadCompressionMode compression = get_payload_compression_mode_v1(header.payload_compression, err);
   std::size_t required_size = header.payload_offset + header.payload_size + sizeof(footer);

   if (glm::any(glm::lessThanEqual(info.dim, ivec3())) ||
       0 == info.layers ||
       0 == info.faces ||
       0 == info.levels ||
       0 == format.block_size() ||
       glm::any(glm::equal(format.block_dim(), block_dim_type())) ||
       format.components() < 1 || format.components() > 4 ||
       0u != (header.format_flags & (~1u)) ||
       format.block_size() > header.block_span ||
       header.payload_offset < sizeof(BeTxHeader) ||
       header.line_span_granularity > TextureAlignment::max_alignment_bits ||
       header.plane_span_granularity > TextureAlignment::max_alignment_bits ||
       header.level_span_granularity > TextureAlignment::max_alignment_bits ||
       header.face_span_granularity > TextureAlignment::max_alignment_bits ||
       header.layer_span_granularity > TextureAlignment::max_alignment_bits ||
       (is_array(info.tex_class) && info.layers > 1) ||
       buf_size < required_size) {
      err = TextureFileReadError::file_corruption;
   }

   if (err == TextureFileReadError::none) {
      if (format.block_size() > ImageFormat::max_block_size ||
          glm::any(glm::greaterThan(format.block_dim(), block_dim_type(block_dim_type::value_type(ImageFormat::max_block_dim)))) ||
          alignment.plane() > std::numeric_limits<U32>::max()) {
         err = TextureFileReadError::unsupported_texture;
      } else if (glm::any(glm::greaterThan(info.dim, ivec3(TextureStorage::max_dim))) ||
          info.levels > TextureStorage::max_levels ||
          info.faces > TextureStorage::max_faces ||
          info.layers > TextureStorage::max_layers) {
         err = TextureFileReadError::unsupported_texture_size;
      } else {
         std::size_t texture_size =  calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim,
                                                                        format.block_dim(), header.block_span, alignment);
         if (texture_size == 0) {
            err = TextureFileReadError::unsupported_texture_size;
         } else if (compression == PayloadCompressionMode::none && header.payload_size != texture_size) {
            err = TextureFileReadError::file_corruption;
         }
      }
   }

   return result;
}

} // be::gfx::tex::()

///////////////////////////////////////////////////////////////////////////////
bool is_betx(const Buf<const UC>& buf) {
   return util::file_signature_matches(buf, signature) &&
      util::file_signature_matches(buf, buf.size() - sizeof(footer), footer);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_betx_info(const Buf<const UC>& buf) {
   using namespace betx::detail;

   std::pair<TextureFileInfo, TextureFileReadError> result;
   result.second = TextureFileReadError::none;

   if (is_betx(buf)) {
      result.first.file_format = TextureFileFormat::betx;
      const BeTxHeader header = read_betx_header(buf, result.second);
      if (result.second == TextureFileReadError::none) {
         switch (buf[16]) {
            case 0x1:
               result = read_betx_info_v1(header, buf.size());
               break;

            default:
               result.second = TextureFileReadError::unsupported_file_format_version;
               break;
         }
      }
   } else {
      result.second = TextureFileReadError::file_corruption;
   }
   return result;
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_betx_texture(const Buf<const UC>& buf) {
   using namespace betx::detail;

   std::pair<Texture, TextureFileReadError> result;
   result.second = TextureFileReadError::none;
   
   TextureFileInfo info;
   TextureAlignment alignment;
   U8 block_span = 0;
   Buf<UC> data;
   Buf<const UC> readonly_data;
   PayloadCompressionMode compression = PayloadCompressionMode::none;
   bool realloc = true;

   if (is_betx(buf)) {
      const BeTxHeader header = read_betx_header(buf, result.second);
      if (result.second == TextureFileReadError::none) {
         switch (buf[16]) {
            case 0x1:
               std::tie(info, result.second) = read_betx_info_v1(header, buf.size());
               alignment = get_alignment_v1(header);
               block_span = header.block_span;
               readonly_data = sub_buf(buf, header.payload_offset, header.payload_size);
               compression = get_payload_compression_mode_v1(header.payload_compression, result.second);
               break;

            default:
               result.second = TextureFileReadError::unsupported_file_format_version;
               break;
         }
      }
   } else {
      result.second = TextureFileReadError::file_corruption;
   }

   if (result.second == TextureFileReadError::none) {
      if (compression == PayloadCompressionMode::zlib) {
         std::size_t required_uncompressed_size = calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim,
                                                                                     info.format.block_dim(), block_span, alignment);
         try {
            data = util::inflate_blob(readonly_data, required_uncompressed_size);
            realloc = 0 != (reinterpret_cast<std::uintptr_t>(data.get()) & (alignment.layer() - 1));
         } catch (const std::bad_alloc&) {
            result.second = TextureFileReadError::out_of_memory;
         } catch (const std::exception&) {
            result.second = TextureFileReadError::file_corruption;
         }
      }

      if (result.second == TextureFileReadError::none) {
         if (!realloc && data) {
            result.first.storage = std::make_unique<TextureStorage>(info.layers, info.faces, info.levels, info.dim, info.format.block_dim(), block_span, std::move(data), alignment);
         } else {
            result.first.storage = std::make_unique<TextureStorage>(info.layers, info.faces, info.levels, info.dim, info.format.block_dim(), block_span, alignment);
            if (data) {
               assert(data.size() >= result.first.storage->size());
               std::memcpy(result.first.storage->data(), data.get(), data.size());
            } else {
               assert(readonly_data.size() >= result.first.storage->size());
               std::memcpy(result.first.storage->data(), readonly_data.get(), readonly_data.size());
            }
         }
         
         result.first.view = TextureView(info.format, info.tex_class, *result.first.storage, 0, info.layers, 0, info.faces, 0, info.levels);
      }
   }

   return result;
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_betx_image(const Buf<const UC>& buf) {
   std::pair<Image, TextureFileReadError> result;
   result.second = TextureFileReadError::none;

   // TODO

   return result;
}

} // be::gfx::tex::detail
