#include "tex/pch.hpp"
#include "tex/texture_file_format_png.hpp"
#include "tex/texture_file_info.hpp"
#include <be/util/check_file_signature.hpp>
#include <be/core/byte_order.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_betx(const Buf<const UC>& buf) {
   constexpr UC signature[] = { 0x57, 0xC0, 'b', 'e', 'T', 'x', '\r', '\n', 0x1a, '\n', 0x4F, 0xE9, 0x39, 0xFD };
   return util::file_signature_matches(buf, signature);
}

///////////////////////////////////////////////////////////////////////////////
//TextureFileInfo load_betx_info(const Buf<const UC>& buf) {
//   TextureFileInfo info;
//   if (is_betx(buf)) {
//      info.file_format = TextureFileFormat::betx;
//      if (buf[14] == '0' && buf[15] == '1' && buf.size() >= 16 + sizeof(BeTxHeader01)) {
//         BeTxHeader01 header;
//         memcpy(&header, buf.get() + 16, sizeof(BeTxHeader01));
//
//         if (header.endianness == 0x1122334455667788ull) {
//            bo::static_to_little<bo::Big::value>(header);
//         } else if (header.endianness != 0x8877665544332211ull) {
//            return info;
//         }
//
//         info.format = ImageFormat(header.block_size,
//                                   ImageFormat::block_dim_type(header.block_dim[0],
//                                                               header.block_dim[1],
//                                                               header.block_dim[2]),
//                                   static_cast<BlockPacking>(header.packing),
//                                   header.components,
//                                   ImageFormat::component_types_type(header.component_types[0],
//                                                                     header.component_types[1],
//                                                                     header.component_types[2],
//                                                                     header.component_types[3]),
//                                   ImageFormat::swizzles_type(header.swizzle[0],
//                                                              header.swizzle[1],
//                                                              header.swizzle[2],
//                                                              header.swizzle[3]),
//                                   static_cast<Colorspace>(header.colorspace),
//                                   header.flags != 0);
//
//         info.tex_class = static_cast<TextureClass>(header.texture_class);
//         info.dim = ivec3(header.dim[0], header.dim[1], header.dim[2]);
//         info.layers = header.layers;
//         info.faces = header.faces;
//         info.levels = header.levels;
//
//      }
//   }
//   return info;
//}



} // be::gfx::tex::detail
