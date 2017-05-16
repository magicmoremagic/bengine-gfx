#include "tex/pch.hpp"
#include "tex/block_packing.hpp"

/*!! include 'tex/block_packing' !! 619 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8:
      case BlockPacking::s_8_8:
      case BlockPacking::s_8_8_8:
      case BlockPacking::s_8_8_8_8:
      case BlockPacking::s_16:
      case BlockPacking::s_16_16:
      case BlockPacking::s_16_16_16:
      case BlockPacking::s_16_16_16_16:
      case BlockPacking::s_32:
      case BlockPacking::s_32_32:
      case BlockPacking::s_32_32_32:
      case BlockPacking::s_32_32_32_32:
      case BlockPacking::s_64:
      case BlockPacking::s_64_64:
      case BlockPacking::s_64_64_64:
      case BlockPacking::s_64_64_64_64:
      case BlockPacking::p_4_4:
      case BlockPacking::p_3_3_2:
      case BlockPacking::p_2_3_3:
      case BlockPacking::p_3_2_3:
      case BlockPacking::p_2_2_2_2:
      case BlockPacking::p_4_4_4_4:
      case BlockPacking::p_1_5_5_5:
      case BlockPacking::p_5_5_5_1:
      case BlockPacking::p_6_5_5:
      case BlockPacking::p_5_5_6:
      case BlockPacking::p_5_6_5:
      case BlockPacking::p_8_24:
      case BlockPacking::p_24_8:
      case BlockPacking::p_11_11_10:
      case BlockPacking::p_10_11_11:
      case BlockPacking::p_11_10_11:
      case BlockPacking::p_8_8_8_8:
      case BlockPacking::p_9_9_9_5:
      case BlockPacking::p_5_9_9_9:
      case BlockPacking::p_10_10_10_2:
      case BlockPacking::p_2_10_10_10:
      case BlockPacking::s_32_p_24_8:
      case BlockPacking::c_astc:
      case BlockPacking::c_bptc:
      case BlockPacking::c_etc1:
      case BlockPacking::c_etc2:
      case BlockPacking::c_s3tc1:
      case BlockPacking::c_s3tc2:
      case BlockPacking::c_s3tc3:
      case BlockPacking::c_rgtc1:
      case BlockPacking::c_rgtc2:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* block_packing_name(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8:           return "s_8";
      case BlockPacking::s_8_8:         return "s_8_8";
      case BlockPacking::s_8_8_8:       return "s_8_8_8";
      case BlockPacking::s_8_8_8_8:     return "s_8_8_8_8";
      case BlockPacking::s_16:          return "s_16";
      case BlockPacking::s_16_16:       return "s_16_16";
      case BlockPacking::s_16_16_16:    return "s_16_16_16";
      case BlockPacking::s_16_16_16_16: return "s_16_16_16_16";
      case BlockPacking::s_32:          return "s_32";
      case BlockPacking::s_32_32:       return "s_32_32";
      case BlockPacking::s_32_32_32:    return "s_32_32_32";
      case BlockPacking::s_32_32_32_32: return "s_32_32_32_32";
      case BlockPacking::s_64:          return "s_64";
      case BlockPacking::s_64_64:       return "s_64_64";
      case BlockPacking::s_64_64_64:    return "s_64_64_64";
      case BlockPacking::s_64_64_64_64: return "s_64_64_64_64";
      case BlockPacking::p_4_4:         return "p_4_4";
      case BlockPacking::p_3_3_2:       return "p_3_3_2";
      case BlockPacking::p_2_3_3:       return "p_2_3_3";
      case BlockPacking::p_3_2_3:       return "p_3_2_3";
      case BlockPacking::p_2_2_2_2:     return "p_2_2_2_2";
      case BlockPacking::p_4_4_4_4:     return "p_4_4_4_4";
      case BlockPacking::p_1_5_5_5:     return "p_1_5_5_5";
      case BlockPacking::p_5_5_5_1:     return "p_5_5_5_1";
      case BlockPacking::p_6_5_5:       return "p_6_5_5";
      case BlockPacking::p_5_5_6:       return "p_5_5_6";
      case BlockPacking::p_5_6_5:       return "p_5_6_5";
      case BlockPacking::p_8_24:        return "p_8_24";
      case BlockPacking::p_24_8:        return "p_24_8";
      case BlockPacking::p_11_11_10:    return "p_11_11_10";
      case BlockPacking::p_10_11_11:    return "p_10_11_11";
      case BlockPacking::p_11_10_11:    return "p_11_10_11";
      case BlockPacking::p_8_8_8_8:     return "p_8_8_8_8";
      case BlockPacking::p_9_9_9_5:     return "p_9_9_9_5";
      case BlockPacking::p_5_9_9_9:     return "p_5_9_9_9";
      case BlockPacking::p_10_10_10_2:  return "p_10_10_10_2";
      case BlockPacking::p_2_10_10_10:  return "p_2_10_10_10";
      case BlockPacking::s_32_p_24_8:   return "s_32_p_24_8";
      case BlockPacking::c_astc:        return "c_astc";
      case BlockPacking::c_bptc:        return "c_bptc";
      case BlockPacking::c_etc1:        return "c_etc1";
      case BlockPacking::c_etc2:        return "c_etc2";
      case BlockPacking::c_s3tc1:       return "c_s3tc1";
      case BlockPacking::c_s3tc2:       return "c_s3tc2";
      case BlockPacking::c_s3tc3:       return "c_s3tc3";
      case BlockPacking::c_rgtc1:       return "c_rgtc1";
      case BlockPacking::c_rgtc2:       return "c_rgtc2";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const BlockPacking, 47> block_packing_values() noexcept {
   return ::be::EnumTraits<BlockPacking>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, BlockPacking constant) {
   if (is_valid(constant)) {
      os << block_packing_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
bool is_compressed(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::c_astc:        return true;
      case BlockPacking::c_bptc:        return true;
      case BlockPacking::c_etc1:        return true;
      case BlockPacking::c_etc2:        return true;
      case BlockPacking::c_s3tc1:       return true;
      case BlockPacking::c_s3tc2:       return true;
      case BlockPacking::c_s3tc3:       return true;
      case BlockPacking::c_rgtc1:       return true;
      case BlockPacking::c_rgtc2:       return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
bool is_packed(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::p_4_4:         return true;
      case BlockPacking::p_3_3_2:       return true;
      case BlockPacking::p_2_3_3:       return true;
      case BlockPacking::p_3_2_3:       return true;
      case BlockPacking::p_2_2_2_2:     return true;
      case BlockPacking::p_4_4_4_4:     return true;
      case BlockPacking::p_1_5_5_5:     return true;
      case BlockPacking::p_5_5_5_1:     return true;
      case BlockPacking::p_6_5_5:       return true;
      case BlockPacking::p_5_5_6:       return true;
      case BlockPacking::p_5_6_5:       return true;
      case BlockPacking::p_8_24:        return true;
      case BlockPacking::p_24_8:        return true;
      case BlockPacking::p_11_11_10:    return true;
      case BlockPacking::p_10_11_11:    return true;
      case BlockPacking::p_11_10_11:    return true;
      case BlockPacking::p_8_8_8_8:     return true;
      case BlockPacking::p_9_9_9_5:     return true;
      case BlockPacking::p_5_9_9_9:     return true;
      case BlockPacking::p_10_10_10_2:  return true;
      case BlockPacking::p_2_10_10_10:  return true;
      case BlockPacking::s_32_p_24_8:   return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 component_count(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8:           return U8(1);
      case BlockPacking::s_8_8:         return U8(2);
      case BlockPacking::s_8_8_8_8:     return U8(4);
      case BlockPacking::s_16:          return U8(1);
      case BlockPacking::s_16_16:       return U8(2);
      case BlockPacking::s_16_16_16_16: return U8(4);
      case BlockPacking::s_32:          return U8(1);
      case BlockPacking::s_32_32:       return U8(2);
      case BlockPacking::s_32_32_32_32: return U8(4);
      case BlockPacking::s_64:          return U8(1);
      case BlockPacking::s_64_64:       return U8(2);
      case BlockPacking::s_64_64_64_64: return U8(4);
      case BlockPacking::p_4_4:         return U8(2);
      case BlockPacking::p_2_2_2_2:     return U8(4);
      case BlockPacking::p_4_4_4_4:     return U8(4);
      case BlockPacking::p_1_5_5_5:     return U8(4);
      case BlockPacking::p_5_5_5_1:     return U8(4);
      case BlockPacking::p_8_24:        return U8(2);
      case BlockPacking::p_24_8:        return U8(2);
      case BlockPacking::p_8_8_8_8:     return U8(4);
      case BlockPacking::p_9_9_9_5:     return U8(4);
      case BlockPacking::p_5_9_9_9:     return U8(4);
      case BlockPacking::p_10_10_10_2:  return U8(4);
      case BlockPacking::p_2_10_10_10:  return U8(4);
      case BlockPacking::c_astc:        return U8(0);
      case BlockPacking::c_bptc:        return U8(0);
      case BlockPacking::c_etc1:        return U8(0);
      case BlockPacking::c_etc2:        return U8(0);
      case BlockPacking::c_s3tc1:       return U8(0);
      case BlockPacking::c_s3tc2:       return U8(0);
      case BlockPacking::c_s3tc3:       return U8(0);
      case BlockPacking::c_rgtc1:       return U8(0);
      case BlockPacking::c_rgtc2:       return U8(0);
      default:
         return U8(3);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_pixel_size(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8:           return U8(1);
      case BlockPacking::s_8_8:         return U8(2);
      case BlockPacking::s_8_8_8:       return U8(3);
      case BlockPacking::s_16:          return U8(2);
      case BlockPacking::s_16_16_16:    return U8(6);
      case BlockPacking::s_16_16_16_16: return U8(8);
      case BlockPacking::s_32_32:       return U8(8);
      case BlockPacking::s_32_32_32:    return U8(12);
      case BlockPacking::s_32_32_32_32: return U8(16);
      case BlockPacking::s_64:          return U8(8);
      case BlockPacking::s_64_64:       return U8(16);
      case BlockPacking::s_64_64_64:    return U8(24);
      case BlockPacking::s_64_64_64_64: return U8(32);
      case BlockPacking::p_4_4:         return U8(1);
      case BlockPacking::p_3_3_2:       return U8(1);
      case BlockPacking::p_2_3_3:       return U8(1);
      case BlockPacking::p_3_2_3:       return U8(1);
      case BlockPacking::p_2_2_2_2:     return U8(1);
      case BlockPacking::p_4_4_4_4:     return U8(2);
      case BlockPacking::p_1_5_5_5:     return U8(2);
      case BlockPacking::p_5_5_5_1:     return U8(2);
      case BlockPacking::p_6_5_5:       return U8(2);
      case BlockPacking::p_5_5_6:       return U8(2);
      case BlockPacking::p_5_6_5:       return U8(2);
      case BlockPacking::s_32_p_24_8:   return U8(8);
      case BlockPacking::c_astc:        return U8(0);
      case BlockPacking::c_bptc:        return U8(0);
      case BlockPacking::c_etc1:        return U8(0);
      case BlockPacking::c_etc2:        return U8(0);
      case BlockPacking::c_s3tc1:       return U8(0);
      case BlockPacking::c_s3tc2:       return U8(0);
      case BlockPacking::c_s3tc3:       return U8(0);
      case BlockPacking::c_rgtc1:       return U8(0);
      case BlockPacking::c_rgtc2:       return U8(0);
      default:
         return U8(4);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_word_size(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8:           return U8(1);
      case BlockPacking::s_8_8:         return U8(1);
      case BlockPacking::s_8_8_8:       return U8(1);
      case BlockPacking::s_8_8_8_8:     return U8(1);
      case BlockPacking::s_16:          return U8(2);
      case BlockPacking::s_16_16:       return U8(2);
      case BlockPacking::s_16_16_16:    return U8(2);
      case BlockPacking::s_16_16_16_16: return U8(2);
      case BlockPacking::s_64:          return U8(8);
      case BlockPacking::s_64_64:       return U8(8);
      case BlockPacking::s_64_64_64:    return U8(8);
      case BlockPacking::s_64_64_64_64: return U8(8);
      case BlockPacking::p_4_4:         return U8(1);
      case BlockPacking::p_3_3_2:       return U8(1);
      case BlockPacking::p_2_3_3:       return U8(1);
      case BlockPacking::p_3_2_3:       return U8(1);
      case BlockPacking::p_2_2_2_2:     return U8(1);
      case BlockPacking::p_4_4_4_4:     return U8(2);
      case BlockPacking::p_1_5_5_5:     return U8(2);
      case BlockPacking::p_5_5_5_1:     return U8(2);
      case BlockPacking::p_6_5_5:       return U8(2);
      case BlockPacking::p_5_5_6:       return U8(2);
      case BlockPacking::p_5_6_5:       return U8(2);
      case BlockPacking::c_astc:        return U8(0);
      case BlockPacking::c_bptc:        return U8(0);
      case BlockPacking::c_etc1:        return U8(0);
      case BlockPacking::c_etc2:        return U8(0);
      case BlockPacking::c_s3tc1:       return U8(0);
      case BlockPacking::c_s3tc2:       return U8(0);
      case BlockPacking::c_s3tc3:       return U8(0);
      case BlockPacking::c_rgtc1:       return U8(0);
      case BlockPacking::c_rgtc2:       return U8(0);
      default:
         return U8(4);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_word_count(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8_8:         return U8(2);
      case BlockPacking::s_8_8_8:       return U8(3);
      case BlockPacking::s_8_8_8_8:     return U8(4);
      case BlockPacking::s_16_16:       return U8(2);
      case BlockPacking::s_16_16_16:    return U8(3);
      case BlockPacking::s_16_16_16_16: return U8(4);
      case BlockPacking::s_32_32:       return U8(2);
      case BlockPacking::s_32_32_32:    return U8(3);
      case BlockPacking::s_32_32_32_32: return U8(4);
      case BlockPacking::s_64_64:       return U8(2);
      case BlockPacking::s_64_64_64:    return U8(3);
      case BlockPacking::s_64_64_64_64: return U8(4);
      case BlockPacking::s_32_p_24_8:   return U8(2);
      case BlockPacking::c_astc:        return U8(0);
      case BlockPacking::c_bptc:        return U8(0);
      case BlockPacking::c_etc1:        return U8(0);
      case BlockPacking::c_etc2:        return U8(0);
      case BlockPacking::c_s3tc1:       return U8(0);
      case BlockPacking::c_s3tc2:       return U8(0);
      case BlockPacking::c_s3tc3:       return U8(0);
      case BlockPacking::c_rgtc1:       return U8(0);
      case BlockPacking::c_rgtc2:       return U8(0);
      default:
         return U8(1);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_word_offset_0(BlockPacking constant) noexcept {
   switch (constant) {
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_word_offset_1(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8_8:         return U8(1);
      case BlockPacking::s_8_8_8:       return U8(1);
      case BlockPacking::s_8_8_8_8:     return U8(1);
      case BlockPacking::s_16_16:       return U8(1);
      case BlockPacking::s_16_16_16:    return U8(1);
      case BlockPacking::s_16_16_16_16: return U8(1);
      case BlockPacking::s_32_32:       return U8(1);
      case BlockPacking::s_32_32_32:    return U8(1);
      case BlockPacking::s_32_32_32_32: return U8(1);
      case BlockPacking::s_64_64:       return U8(1);
      case BlockPacking::s_64_64_64:    return U8(1);
      case BlockPacking::s_64_64_64_64: return U8(1);
      case BlockPacking::s_32_p_24_8:   return U8(1);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_word_offset_2(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8_8_8:       return U8(2);
      case BlockPacking::s_8_8_8_8:     return U8(2);
      case BlockPacking::s_16_16_16:    return U8(2);
      case BlockPacking::s_16_16_16_16: return U8(2);
      case BlockPacking::s_32_32_32:    return U8(2);
      case BlockPacking::s_32_32_32_32: return U8(2);
      case BlockPacking::s_64_64_64:    return U8(2);
      case BlockPacking::s_64_64_64_64: return U8(2);
      case BlockPacking::s_32_p_24_8:   return U8(1);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_word_offset_3(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8_8_8_8:     return U8(3);
      case BlockPacking::s_16_16_16_16: return U8(3);
      case BlockPacking::s_32_32_32_32: return U8(3);
      case BlockPacking::s_64_64_64_64: return U8(3);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_bit_offset_0(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::p_4_4:         return U8(4);
      case BlockPacking::p_3_3_2:       return U8(5);
      case BlockPacking::p_2_3_3:       return U8(6);
      case BlockPacking::p_3_2_3:       return U8(5);
      case BlockPacking::p_2_2_2_2:     return U8(6);
      case BlockPacking::p_4_4_4_4:     return U8(12);
      case BlockPacking::p_1_5_5_5:     return U8(15);
      case BlockPacking::p_5_5_5_1:     return U8(11);
      case BlockPacking::p_6_5_5:       return U8(10);
      case BlockPacking::p_5_5_6:       return U8(11);
      case BlockPacking::p_5_6_5:       return U8(11);
      case BlockPacking::p_8_24:        return U8(24);
      case BlockPacking::p_24_8:        return U8(8);
      case BlockPacking::p_11_11_10:    return U8(21);
      case BlockPacking::p_10_11_11:    return U8(22);
      case BlockPacking::p_11_10_11:    return U8(21);
      case BlockPacking::p_8_8_8_8:     return U8(24);
      case BlockPacking::p_9_9_9_5:     return U8(23);
      case BlockPacking::p_5_9_9_9:     return U8(27);
      case BlockPacking::p_10_10_10_2:  return U8(22);
      case BlockPacking::p_2_10_10_10:  return U8(30);
      case BlockPacking::s_32_p_24_8:   return U8(32);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_bit_offset_1(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::p_3_3_2:       return U8(2);
      case BlockPacking::p_2_3_3:       return U8(3);
      case BlockPacking::p_3_2_3:       return U8(3);
      case BlockPacking::p_2_2_2_2:     return U8(4);
      case BlockPacking::p_4_4_4_4:     return U8(8);
      case BlockPacking::p_1_5_5_5:     return U8(10);
      case BlockPacking::p_5_5_5_1:     return U8(6);
      case BlockPacking::p_6_5_5:       return U8(5);
      case BlockPacking::p_5_5_6:       return U8(6);
      case BlockPacking::p_5_6_5:       return U8(5);
      case BlockPacking::p_11_11_10:    return U8(10);
      case BlockPacking::p_10_11_11:    return U8(11);
      case BlockPacking::p_11_10_11:    return U8(11);
      case BlockPacking::p_8_8_8_8:     return U8(16);
      case BlockPacking::p_9_9_9_5:     return U8(14);
      case BlockPacking::p_5_9_9_9:     return U8(18);
      case BlockPacking::p_10_10_10_2:  return U8(12);
      case BlockPacking::p_2_10_10_10:  return U8(20);
      case BlockPacking::s_32_p_24_8:   return U8(8);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_bit_offset_2(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::p_2_2_2_2:     return U8(2);
      case BlockPacking::p_4_4_4_4:     return U8(4);
      case BlockPacking::p_1_5_5_5:     return U8(5);
      case BlockPacking::p_5_5_5_1:     return U8(1);
      case BlockPacking::p_8_8_8_8:     return U8(8);
      case BlockPacking::p_9_9_9_5:     return U8(5);
      case BlockPacking::p_5_9_9_9:     return U8(9);
      case BlockPacking::p_10_10_10_2:  return U8(2);
      case BlockPacking::p_2_10_10_10:  return U8(10);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_bit_offset_3(BlockPacking constant) noexcept {
   switch (constant) {
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_bit_width_0(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8:           return U8(8);
      case BlockPacking::s_8_8:         return U8(8);
      case BlockPacking::s_8_8_8:       return U8(8);
      case BlockPacking::s_8_8_8_8:     return U8(8);
      case BlockPacking::s_16:          return U8(16);
      case BlockPacking::s_16_16:       return U8(16);
      case BlockPacking::s_16_16_16:    return U8(16);
      case BlockPacking::s_16_16_16_16: return U8(16);
      case BlockPacking::s_32:          return U8(32);
      case BlockPacking::s_32_32:       return U8(32);
      case BlockPacking::s_32_32_32:    return U8(32);
      case BlockPacking::s_32_32_32_32: return U8(32);
      case BlockPacking::s_64:          return U8(64);
      case BlockPacking::s_64_64:       return U8(64);
      case BlockPacking::s_64_64_64:    return U8(64);
      case BlockPacking::s_64_64_64_64: return U8(64);
      case BlockPacking::p_4_4:         return U8(4);
      case BlockPacking::p_3_3_2:       return U8(3);
      case BlockPacking::p_2_3_3:       return U8(2);
      case BlockPacking::p_3_2_3:       return U8(3);
      case BlockPacking::p_2_2_2_2:     return U8(2);
      case BlockPacking::p_4_4_4_4:     return U8(4);
      case BlockPacking::p_1_5_5_5:     return U8(1);
      case BlockPacking::p_5_5_5_1:     return U8(5);
      case BlockPacking::p_6_5_5:       return U8(6);
      case BlockPacking::p_5_5_6:       return U8(5);
      case BlockPacking::p_5_6_5:       return U8(5);
      case BlockPacking::p_8_24:        return U8(8);
      case BlockPacking::p_24_8:        return U8(24);
      case BlockPacking::p_11_11_10:    return U8(11);
      case BlockPacking::p_10_11_11:    return U8(10);
      case BlockPacking::p_11_10_11:    return U8(11);
      case BlockPacking::p_8_8_8_8:     return U8(8);
      case BlockPacking::p_9_9_9_5:     return U8(9);
      case BlockPacking::p_5_9_9_9:     return U8(5);
      case BlockPacking::p_10_10_10_2:  return U8(10);
      case BlockPacking::p_2_10_10_10:  return U8(2);
      case BlockPacking::s_32_p_24_8:   return U8(32);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_bit_width_1(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8_8:         return U8(8);
      case BlockPacking::s_8_8_8:       return U8(8);
      case BlockPacking::s_8_8_8_8:     return U8(8);
      case BlockPacking::s_16_16:       return U8(16);
      case BlockPacking::s_16_16_16:    return U8(16);
      case BlockPacking::s_16_16_16_16: return U8(16);
      case BlockPacking::s_32_32:       return U8(32);
      case BlockPacking::s_32_32_32:    return U8(32);
      case BlockPacking::s_32_32_32_32: return U8(32);
      case BlockPacking::s_64_64:       return U8(64);
      case BlockPacking::s_64_64_64:    return U8(64);
      case BlockPacking::s_64_64_64_64: return U8(64);
      case BlockPacking::p_4_4:         return U8(4);
      case BlockPacking::p_3_3_2:       return U8(3);
      case BlockPacking::p_2_3_3:       return U8(3);
      case BlockPacking::p_3_2_3:       return U8(2);
      case BlockPacking::p_2_2_2_2:     return U8(2);
      case BlockPacking::p_4_4_4_4:     return U8(4);
      case BlockPacking::p_1_5_5_5:     return U8(5);
      case BlockPacking::p_5_5_5_1:     return U8(5);
      case BlockPacking::p_6_5_5:       return U8(5);
      case BlockPacking::p_5_5_6:       return U8(5);
      case BlockPacking::p_5_6_5:       return U8(6);
      case BlockPacking::p_8_24:        return U8(24);
      case BlockPacking::p_24_8:        return U8(8);
      case BlockPacking::p_11_11_10:    return U8(11);
      case BlockPacking::p_10_11_11:    return U8(11);
      case BlockPacking::p_11_10_11:    return U8(10);
      case BlockPacking::p_8_8_8_8:     return U8(8);
      case BlockPacking::p_9_9_9_5:     return U8(9);
      case BlockPacking::p_5_9_9_9:     return U8(9);
      case BlockPacking::p_10_10_10_2:  return U8(10);
      case BlockPacking::p_2_10_10_10:  return U8(10);
      case BlockPacking::s_32_p_24_8:   return U8(24);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_bit_width_2(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8_8_8:       return U8(8);
      case BlockPacking::s_8_8_8_8:     return U8(8);
      case BlockPacking::s_16_16_16:    return U8(16);
      case BlockPacking::s_16_16_16_16: return U8(16);
      case BlockPacking::s_32_32_32:    return U8(32);
      case BlockPacking::s_32_32_32_32: return U8(32);
      case BlockPacking::s_64_64_64:    return U8(64);
      case BlockPacking::s_64_64_64_64: return U8(64);
      case BlockPacking::p_3_3_2:       return U8(2);
      case BlockPacking::p_2_3_3:       return U8(3);
      case BlockPacking::p_3_2_3:       return U8(3);
      case BlockPacking::p_2_2_2_2:     return U8(2);
      case BlockPacking::p_4_4_4_4:     return U8(4);
      case BlockPacking::p_1_5_5_5:     return U8(5);
      case BlockPacking::p_5_5_5_1:     return U8(5);
      case BlockPacking::p_6_5_5:       return U8(5);
      case BlockPacking::p_5_5_6:       return U8(6);
      case BlockPacking::p_5_6_5:       return U8(5);
      case BlockPacking::p_11_11_10:    return U8(10);
      case BlockPacking::p_10_11_11:    return U8(11);
      case BlockPacking::p_11_10_11:    return U8(11);
      case BlockPacking::p_8_8_8_8:     return U8(8);
      case BlockPacking::p_9_9_9_5:     return U8(9);
      case BlockPacking::p_5_9_9_9:     return U8(9);
      case BlockPacking::p_10_10_10_2:  return U8(10);
      case BlockPacking::p_2_10_10_10:  return U8(10);
      case BlockPacking::s_32_p_24_8:   return U8(8);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 block_bit_width_3(BlockPacking constant) noexcept {
   switch (constant) {
      case BlockPacking::s_8_8_8_8:     return U8(8);
      case BlockPacking::s_16_16_16_16: return U8(16);
      case BlockPacking::s_32_32_32_32: return U8(32);
      case BlockPacking::s_64_64_64_64: return U8(64);
      case BlockPacking::p_2_2_2_2:     return U8(2);
      case BlockPacking::p_4_4_4_4:     return U8(4);
      case BlockPacking::p_1_5_5_5:     return U8(5);
      case BlockPacking::p_5_5_5_1:     return U8(1);
      case BlockPacking::p_8_8_8_8:     return U8(8);
      case BlockPacking::p_9_9_9_5:     return U8(5);
      case BlockPacking::p_5_9_9_9:     return U8(9);
      case BlockPacking::p_10_10_10_2:  return U8(2);
      case BlockPacking::p_2_10_10_10:  return U8(10);
      default:
         return U8(0);
   }
}

} // be::gfx::tex


/* ######################### END OF GENERATED CODE ######################### */
