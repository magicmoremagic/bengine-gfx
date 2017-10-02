#include "pch.hpp"
#include "tex/betx_writer.hpp"
#include "tex/texture.hpp"
#include "tex/duplicate_texture.hpp"
#include "tex/byte_order.hpp"
#include "tex/betx_write_error.hpp"
#include "betx_header_.hpp"
#include <be/util/put_file_contents.hpp>
#include <be/util/zlib.hpp>
#include <be/core/exceptions.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
BetxWriter::BetxWriter(Log& log)
   : log_(log),
     compression_(detail::BetxPayloadCompressionMode::none),
     compression_level_(-1),
     endianness_(bo::Host::value) { }

///////////////////////////////////////////////////////////////////////////////
void BetxWriter::reset() {
   tex_ = ConstTextureView();
   compression_ = detail::BetxPayloadCompressionMode::none;
   compression_level_ = -1;
   endianness_ = bo::Host::value;
}

///////////////////////////////////////////////////////////////////////////////
void BetxWriter::texture(const ConstTextureView& view) noexcept {
   tex_ = view;
}

///////////////////////////////////////////////////////////////////////////////
void BetxWriter::image(const ConstImageView& view) noexcept {
   TextureClass tc;
   if (view.dim().z == 1) {
      if (view.dim().y == 1) {
         tc = TextureClass::lineal;
      } else {
         tc = TextureClass::planar;
      }
   } else {
      tc = TextureClass::volumetric;
   }

   tex_ = ConstTextureView(view.format(), tc, view.storage(), view.layer(), 1, view.face(), 1, view.level(), 1);
}

///////////////////////////////////////////////////////////////////////////////
void BetxWriter::payload_compression(PayloadCompressionMode mode, I8 level) noexcept {
   compression_ = mode;
   compression_level_ = level;
}

///////////////////////////////////////////////////////////////////////////////
void BetxWriter::endianness(ByteOrderType endianness) noexcept {
   endianness_ = endianness;
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> BetxWriter::write() {
   Buf<UC> result;
   std::error_code ec;
   result = write(ec);
   if (ec) {
      throw RecoverableError(ec);
   }
   return result;
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> BetxWriter::write(std::error_code& ec) noexcept {
   using err = detail::BetxWriteError;
   using sig = detail::BetxSignature;

   Buf<UC> result;

   if (!tex_) {
      ec = err::empty_texture;
      return result;
   }

   detail::BetxHeader header;
   static_assert(sizeof(header.signature) == sizeof(detail::BetxSignature::full));
   std::memcpy(header.signature, detail::BetxSignature::full, sizeof(header.signature));

   if (endianness_ == bo::Big::value) {
      header.endianness = 0xFF;
   } else if (endianness_ == bo::Little::value) {
      header.endianness = 0x00;
   } else {
      ec = err::invalid_endianness;
      return result;
   }

   ConstTextureView t;
   Texture tmp_tex;
   if (tex_.base_layer() != 0 || tex_.layers() != tex_.storage().layers() ||
       tex_.base_face() != 0 || tex_.faces() != tex_.storage().faces() ||
       tex_.base_level() != 0 || tex_.levels() != tex_.storage().levels() ||
       endianness_ != bo::Host::value) {
      try {
         tmp_tex = duplicate_texture(tex_);
      } catch (const std::bad_alloc&) {
         ec = err::not_enough_memory;
         return result;
      }
      t = tmp_tex.view;
      if (endianness_ != bo::Host::value) {
         reverse_endianness(*tmp_tex.storage, t.format().packing());
      }
   } else {
      t = tex_;
   }

   header.version = 0x01; // v1

   ImageFormat format = t.format();
   TextureAlignment alignment = t.storage().alignment();

   if (!is_valid(t.texture_class())) {
      ec = err::invalid_texture_class;
      return result;
   } else if (!is_valid(format.packing())) {
      ec = err::invalid_block_packing;
      return result;
   } else if (!is_valid(format.colorspace())) {
      ec = err::invalid_colorspace;
      return result;
   } else if (t.layers() == 0 || t.layers() > std::numeric_limits<U16>::max()) {
      ec = err::invalid_layer_count;
      return result;
   } else if (t.faces() == 0 || t.faces() > std::numeric_limits<U8>::max()) {
      ec = err::invalid_face_count;
      return result;
   } else if (t.levels() == 0 || t.levels() > std::numeric_limits<U8>::max()) {
      ec = err::invalid_level_count;
      return result;
   }

   header.texture_class = static_cast<U8>(t.texture_class());
   header.layers = static_cast<U16>(t.layers());
   header.faces = static_cast<U8>(t.faces());
   header.levels = static_cast<U8>(t.levels());
   header.dim[0] = t.dim(0).x;
   header.dim[1] = t.dim(0).y;
   header.dim[2] = t.dim(0).z;
   header.block_size = format.block_size();
   header.block_dim[0] = t.block_dim().x;
   header.block_dim[1] = t.block_dim().y;
   header.block_dim[2] = t.block_dim().z;
   header.components = format.components();
   header.block_packing = static_cast<U8>(format.packing());
   header.colorspace = static_cast<U8>(format.colorspace());
   header.block_span = t.block_span();
   header.line_alignment = alignment.line_bits();
   header.plane_alignment = alignment.plane_bits();
   header.level_alignment = alignment.level_bits();
   header.face_alignment = alignment.face_bits();
   header.layer_alignment = alignment.layer_bits();

   for (glm::length_t c = 0; c < 4; ++c) {
      if (!is_valid(format.field_type(c))) {
         ec = err::invalid_field_type;
         return result;
      } else if (!is_valid(format.swizzle(c))) {
         ec = err::invalid_swizzle;
         return result;
      }

      header.field_types[c] = static_cast<U8>(format.field_type(c));
      header.swizzle[c] = static_cast<U8>(format.swizzle(c));
   }

   header.format_flags = 0;
   if (format.premultiplied()) {
      header.format_flags |= 1u;
   }

   header.reserved = 0;
   header.metadata_location = 0x00; // no metadata
   header.payload_offset = sizeof(header);
   header.payload_compression = static_cast<U8>(compression_);

   switch (compression_) {
      case PayloadCompressionMode::none:
         header.payload_size = t.storage().size();

         if (endianness_ == ByteOrderType::big_endian) {
            bo::static_to_big<>(header);
         } else if (endianness_ == ByteOrderType::little_endian) {
            bo::static_to_little<>(header);
         }

         try {
            result = make_buf<UC>(sizeof(header) + t.storage().size() + sizeof(sig::footer));
         } catch (const std::bad_alloc&) {
            ec = err::not_enough_memory;
            return result;
         }
         std::memcpy(result.get(), &header, sizeof(header));
         std::memcpy(result.get() + result.size() - sizeof(sig::footer), sig::footer, sizeof(sig::footer));
         std::memcpy(result.get() + sizeof(header), t.storage().data(), t.storage().size());
         break;

      case PayloadCompressionMode::zlib:
      {
         Buf<UC> compressed = util::deflate_buf(Buf<const UC>(t.storage().data(), t.storage().size()), ec,
                                                false, compression_level_ < 0 ? 9 : compression_level_);
         if (ec) {
            return result;
         }

         header.payload_size = compressed.size();

         if (endianness_ == ByteOrderType::big_endian) {
            bo::static_to_big<>(header);
         } else if (endianness_ == ByteOrderType::little_endian) {
            bo::static_to_little<>(header);
         }

         try {
            result = make_buf<UC>(sizeof(header) + compressed.size() + sizeof(sig::footer));
         } catch (const std::bad_alloc&) {
            ec = err::not_enough_memory;
            return result;
         }
         std::memcpy(result.get(), &header, sizeof(header));
         std::memcpy(result.get() + result.size() - sizeof(sig::footer), sig::footer, sizeof(sig::footer));
         std::memcpy(result.get() + sizeof(header), compressed.get(), compressed.size());
         break;
      }

      default:
         ec = err::invalid_payload_compression;
         return result;
   }

   return result;
}

///////////////////////////////////////////////////////////////////////////////
void BetxWriter::write(const Path& path) {
   util::put_file_contents(path, write());
}

///////////////////////////////////////////////////////////////////////////////
void BetxWriter::write(const Path& path, std::error_code& ec) noexcept {
   Buf<UC> data = write(ec);
   if (data) {
      util::put_file_contents(path, std::move(data), ec);
   }
}

} // be::gfx::tex
