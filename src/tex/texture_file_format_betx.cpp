#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include "tex/texture_file_info.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/core/byte_order.hpp>

// offset   name     type                 desc
// 0                 UC[2]                magicmoremagic prefix - #57c0
// 2                 UC[4]                canonical file extension - 'beTx'
// 6                 UC[4]                see PNG signature rationale - #0D0A1A0A
// 10                UC[4]                big-endian 32b FNV-1a of "beTx - bengine texture file format" - #4FE939FD
// 14                UC[2]                version - '01'
// 16                U64                  endianness detection - 0x8877665544332211 - if read as 0x8877665544332211 no endian conversion is necessary.  if read as 0x1122334455667788 then bswap all shorts/ints/longs in the remainder of the file.  If any other value, fail read operation
// 24       S        U64                  image data size (bytes) - start of metadata section is at offset 80 + this
// 32                U8                   block size (bytes)
// 33                U8                   block width (pixels)
// 34                U8                   block height (pixels)
// 35                U8                   block depth (pixels)
// 36                BlockPacking (U8)    block data packing type
// 37                U8                   effective components per pixel
// 38                ComponentType (U8)   component 0 type
// 39                ComponentType (U8)   component 1 type
// 40                ComponentType (U8)   component 2 type
// 41                ComponentType (U8)   component 3 type
// 42                Swizzle (U8)         red swizzle
// 43                Swizzle (U8)         green swizzle
// 44                Swizzle (U8)         blue swizzle
// 45                Swizzle (U8)         alpha swizzle
// 46                Colorspace (U8)      colorspace
// 47                U8                   premultiplied flag - 0 for non-premultiplied, 1 for premultiplied
// 48                U8                   reserved - write 0
// 49                U8                   reserved - write 0
// 50                U8                   reserved - write 0
// 51                TextureClass (U8)    texture class
// 52                I32                  texture width (pixels) - must be >= 1
// 56                I32                  texture height (pixels) - must be >= 1
// 60                I32                  texture depth (pixels) - must be >= 1
// 64                U16                  layers
// 66                U8                   faces
// 67                U8                   mipmap levels
// 68                U8                   aligned block size (bytes)
// 69                U8                   line alignment (log2 bytes)
// 70                U8                   plane alignment (log2 bytes)
// 71                U8                   level alignment (log2 bytes)
// 72                U8                   face alignment (log2 bytes)
// 73                U8                   layer alignment (log2 bytes)
// 74                UC[6]                reserved - write 0
// 80                block[]              Start of image data
// 80+S     MS       U32                  Total Metadata Size (bytes; includes this field; 8 for no metadata)
// 84+S     MC       U32                  Number of metadata fields (0 for no metadata)
// 88+S+16*i         U64                  Metadata Field ID
// 96+S+16*i MOi     U32                  Metadata Field Offsets (bytes)
// 100+S+16*i MFi    U32                  Metadata Field Lengths (bytes)
// 88+S+16*MC+MOi    UC[MFi]              Metadata Field Payloads
// 80+S+MS           UC[4]                Footer - 'beTx'

namespace be::gfx::tex::detail {

struct BeTxHeader01 {
   U64 endianness;
   U64 image_buffer_size;
   U8 block_size;
   U8 block_dim[3];
   U8 packing;
   U8 components;
   U8 component_types[4];
   U8 swizzle[4];
   U8 colorspace;
   U8 flags;
   U8 reserved_a[3];
   U8 texture_class;
   I32 dim[3];
   U16 layers;
   U8 faces;
   U8 levels;
   U8 aligned_block_size;
   U8 line_alignment_type;
   U8 plane_alignment_type;
   U8 level_alignment_type;
   U8 face_alignment_type;
   U8 layer_alignment_type;
   U8 reserved_b[6];
};

static const std::size_t header_size = sizeof(BeTxHeader01);

///////////////////////////////////////////////////////////////////////////////
bool is_betx(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 0x57, 0xc0, 'b', 'e', 'T', 'x', '\r', '\n', 0x1a, '\n', 0x4F, 0xE9, 0x39, 0xFD };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo load_betx_info(const Buf<const UC>& buf) {
   TextureFileInfo info;
   if (is_betx(buf)) {
      info.file_format = TextureFileFormat::betx;
      if (buf[14] == '0' && buf[15] == '1' && buf.size() >= 16 + sizeof(BeTxHeader01)) {
         BeTxHeader01 header;
         memcpy(&header, buf.get() + 16, sizeof(BeTxHeader01));

         if (header.endianness == 0x1122334455667788ull) {
            bo::t
         } else if (header.endianness != 0x8877665544332211ull) {
            return info;
         }



      }
   }
   return info;
}



} // be::gfx::tex::detail
