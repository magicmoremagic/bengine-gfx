#include "pch.hpp"
#include "tex/byte_order.hpp"
#include <be/core/byte_order.hpp>

namespace be::gfx::tex {
namespace {

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void reverse_endianness_impl(TextureStorage& storage, BlockPacking packing) {
   auto block_words = block_word_count(packing) * storage.block_dim().x * storage.block_dim().y * storage.block_dim().z;
   auto layer_ptr = storage.data();
   for (std::size_t layer = 0; layer < storage.layers(); ++layer) {
      auto face_ptr = layer_ptr;
      for (std::size_t face = 0; face < storage.faces(); ++face) {
         for (std::size_t level = 0; level < storage.levels(); ++level) {
            auto level_ptr = face_ptr + storage.level_offset(level);
            auto dim_blocks = storage.dim_blocks(level);
            auto plane_span = storage.plane_span(level);
            auto line_span = storage.line_span(level);
            auto plane_ptr = level_ptr;
            for (std::size_t z = 0; z < dim_blocks.z; ++z) {
               auto line_ptr = plane_ptr;
               for (std::size_t y = 0; y < dim_blocks.y; ++y) {
                  auto block_ptr = line_ptr;
                  for (std::size_t x = 0; x < dim_blocks.x; ++x) {
                     auto word_ptr = block_ptr;
                     for (std::size_t w = 0; w < block_words; ++w) {
                        T tmp;
                        std::memcpy(&tmp, word_ptr, sizeof(T));
                        bo::static_to_big<bo::Little::value>(tmp);
                        std::memcpy(word_ptr, &tmp, sizeof(T));
                        word_ptr += sizeof(T);
                     }
                     block_ptr += storage.block_span();
                  }
                  line_ptr += line_span;
               }
               plane_ptr += plane_span;
            }
         }
         face_ptr += storage.face_span();
      }
      layer_ptr += storage.layer_span();
   }
}

} // be::gfx::tex::()

///////////////////////////////////////////////////////////////////////////////
void reverse_endianness(TextureStorage& storage, BlockPacking packing) {
   switch (block_word_size(packing)) {
      case 2: reverse_endianness_impl<U16>(storage, packing); break;
      case 4: reverse_endianness_impl<U32>(storage, packing); break;
      case 8: reverse_endianness_impl<U64>(storage, packing); break;
   }
}

} // be::gfx::tex
