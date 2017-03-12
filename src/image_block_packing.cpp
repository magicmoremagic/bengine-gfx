#include "pch.hpp"
#include "image_block_packing.hpp"

namespace be::gfx {

/*!! include 'image_block_packing' !! 551 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
bool is_valid(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8:
      case ImageBlockPacking::s_8_8:
      case ImageBlockPacking::s_8_8_8:
      case ImageBlockPacking::s_8_8_8_8:
      case ImageBlockPacking::s_16:
      case ImageBlockPacking::s_16_16:
      case ImageBlockPacking::s_16_16_16:
      case ImageBlockPacking::s_16_16_16_16:
      case ImageBlockPacking::s_32:
      case ImageBlockPacking::s_32_32:
      case ImageBlockPacking::s_32_32_32:
      case ImageBlockPacking::s_32_32_32_32:
      case ImageBlockPacking::s_64:
      case ImageBlockPacking::s_64_64:
      case ImageBlockPacking::s_64_64_64:
      case ImageBlockPacking::s_64_64_64_64:
      case ImageBlockPacking::p_4_4:
      case ImageBlockPacking::p_3_3_2:
      case ImageBlockPacking::p_2_3_3:
      case ImageBlockPacking::p_3_2_3:
      case ImageBlockPacking::p_4_4_4_4:
      case ImageBlockPacking::p_1_5_5_5:
      case ImageBlockPacking::p_5_5_5_1:
      case ImageBlockPacking::p_5_6_5:
      case ImageBlockPacking::p_8_24:
      case ImageBlockPacking::p_24_8:
      case ImageBlockPacking::p_11_11_10:
      case ImageBlockPacking::p_10_11_11:
      case ImageBlockPacking::p_11_10_11:
      case ImageBlockPacking::p_8_8_8_8:
      case ImageBlockPacking::p_9_9_9_5:
      case ImageBlockPacking::p_5_9_9_9:
      case ImageBlockPacking::p_10_10_10_2:
      case ImageBlockPacking::p_2_10_10_10:
      case ImageBlockPacking::s_32_p_24_8:
      case ImageBlockPacking::c_astc:
      case ImageBlockPacking::c_atc:
      case ImageBlockPacking::c_bptc:
      case ImageBlockPacking::c_eac:
      case ImageBlockPacking::c_etc1:
      case ImageBlockPacking::c_etc2:
      case ImageBlockPacking::c_pvrtc1:
      case ImageBlockPacking::c_pvrtc2:
      case ImageBlockPacking::c_s3tc1:
      case ImageBlockPacking::c_s3tc2:
      case ImageBlockPacking::c_s3tc3:
      case ImageBlockPacking::c_s3tc4:
      case ImageBlockPacking::c_s3tc5:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* image_block_packing_name(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8:           return "s_8";
      case ImageBlockPacking::s_8_8:         return "s_8_8";
      case ImageBlockPacking::s_8_8_8:       return "s_8_8_8";
      case ImageBlockPacking::s_8_8_8_8:     return "s_8_8_8_8";
      case ImageBlockPacking::s_16:          return "s_16";
      case ImageBlockPacking::s_16_16:       return "s_16_16";
      case ImageBlockPacking::s_16_16_16:    return "s_16_16_16";
      case ImageBlockPacking::s_16_16_16_16: return "s_16_16_16_16";
      case ImageBlockPacking::s_32:          return "s_32";
      case ImageBlockPacking::s_32_32:       return "s_32_32";
      case ImageBlockPacking::s_32_32_32:    return "s_32_32_32";
      case ImageBlockPacking::s_32_32_32_32: return "s_32_32_32_32";
      case ImageBlockPacking::s_64:          return "s_64";
      case ImageBlockPacking::s_64_64:       return "s_64_64";
      case ImageBlockPacking::s_64_64_64:    return "s_64_64_64";
      case ImageBlockPacking::s_64_64_64_64: return "s_64_64_64_64";
      case ImageBlockPacking::p_4_4:         return "p_4_4";
      case ImageBlockPacking::p_3_3_2:       return "p_3_3_2";
      case ImageBlockPacking::p_2_3_3:       return "p_2_3_3";
      case ImageBlockPacking::p_3_2_3:       return "p_3_2_3";
      case ImageBlockPacking::p_4_4_4_4:     return "p_4_4_4_4";
      case ImageBlockPacking::p_1_5_5_5:     return "p_1_5_5_5";
      case ImageBlockPacking::p_5_5_5_1:     return "p_5_5_5_1";
      case ImageBlockPacking::p_5_6_5:       return "p_5_6_5";
      case ImageBlockPacking::p_8_24:        return "p_8_24";
      case ImageBlockPacking::p_24_8:        return "p_24_8";
      case ImageBlockPacking::p_11_11_10:    return "p_11_11_10";
      case ImageBlockPacking::p_10_11_11:    return "p_10_11_11";
      case ImageBlockPacking::p_11_10_11:    return "p_11_10_11";
      case ImageBlockPacking::p_8_8_8_8:     return "p_8_8_8_8";
      case ImageBlockPacking::p_9_9_9_5:     return "p_9_9_9_5";
      case ImageBlockPacking::p_5_9_9_9:     return "p_5_9_9_9";
      case ImageBlockPacking::p_10_10_10_2:  return "p_10_10_10_2";
      case ImageBlockPacking::p_2_10_10_10:  return "p_2_10_10_10";
      case ImageBlockPacking::s_32_p_24_8:   return "s_32_p_24_8";
      case ImageBlockPacking::c_astc:        return "c_astc";
      case ImageBlockPacking::c_atc:         return "c_atc";
      case ImageBlockPacking::c_bptc:        return "c_bptc";
      case ImageBlockPacking::c_eac:         return "c_eac";
      case ImageBlockPacking::c_etc1:        return "c_etc1";
      case ImageBlockPacking::c_etc2:        return "c_etc2";
      case ImageBlockPacking::c_pvrtc1:      return "c_pvrtc1";
      case ImageBlockPacking::c_pvrtc2:      return "c_pvrtc2";
      case ImageBlockPacking::c_s3tc1:       return "c_s3tc1";
      case ImageBlockPacking::c_s3tc2:       return "c_s3tc2";
      case ImageBlockPacking::c_s3tc3:       return "c_s3tc3";
      case ImageBlockPacking::c_s3tc4:       return "c_s3tc4";
      case ImageBlockPacking::c_s3tc5:       return "c_s3tc5";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
bool is_compressed(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::c_astc:        return true;
      case ImageBlockPacking::c_atc:         return true;
      case ImageBlockPacking::c_bptc:        return true;
      case ImageBlockPacking::c_eac:         return true;
      case ImageBlockPacking::c_etc1:        return true;
      case ImageBlockPacking::c_etc2:        return true;
      case ImageBlockPacking::c_pvrtc1:      return true;
      case ImageBlockPacking::c_pvrtc2:      return true;
      case ImageBlockPacking::c_s3tc1:       return true;
      case ImageBlockPacking::c_s3tc2:       return true;
      case ImageBlockPacking::c_s3tc3:       return true;
      case ImageBlockPacking::c_s3tc4:       return true;
      case ImageBlockPacking::c_s3tc5:       return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
bool is_packed(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::p_4_4:         return true;
      case ImageBlockPacking::p_3_3_2:       return true;
      case ImageBlockPacking::p_2_3_3:       return true;
      case ImageBlockPacking::p_3_2_3:       return true;
      case ImageBlockPacking::p_4_4_4_4:     return true;
      case ImageBlockPacking::p_1_5_5_5:     return true;
      case ImageBlockPacking::p_5_5_5_1:     return true;
      case ImageBlockPacking::p_5_6_5:       return true;
      case ImageBlockPacking::p_8_24:        return true;
      case ImageBlockPacking::p_24_8:        return true;
      case ImageBlockPacking::p_11_11_10:    return true;
      case ImageBlockPacking::p_10_11_11:    return true;
      case ImageBlockPacking::p_11_10_11:    return true;
      case ImageBlockPacking::p_8_8_8_8:     return true;
      case ImageBlockPacking::p_9_9_9_5:     return true;
      case ImageBlockPacking::p_5_9_9_9:     return true;
      case ImageBlockPacking::p_10_10_10_2:  return true;
      case ImageBlockPacking::p_2_10_10_10:  return true;
      case ImageBlockPacking::s_32_p_24_8:   return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 component_count(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8:           return U8(1);
      case ImageBlockPacking::s_8_8:         return U8(2);
      case ImageBlockPacking::s_8_8_8_8:     return U8(4);
      case ImageBlockPacking::s_16:          return U8(1);
      case ImageBlockPacking::s_16_16:       return U8(2);
      case ImageBlockPacking::s_16_16_16_16: return U8(4);
      case ImageBlockPacking::s_32:          return U8(1);
      case ImageBlockPacking::s_32_32:       return U8(2);
      case ImageBlockPacking::s_32_32_32_32: return U8(4);
      case ImageBlockPacking::s_64:          return U8(1);
      case ImageBlockPacking::s_64_64:       return U8(2);
      case ImageBlockPacking::s_64_64_64_64: return U8(4);
      case ImageBlockPacking::p_4_4:         return U8(2);
      case ImageBlockPacking::p_4_4_4_4:     return U8(4);
      case ImageBlockPacking::p_1_5_5_5:     return U8(4);
      case ImageBlockPacking::p_5_5_5_1:     return U8(4);
      case ImageBlockPacking::p_8_24:        return U8(2);
      case ImageBlockPacking::p_24_8:        return U8(2);
      case ImageBlockPacking::p_8_8_8_8:     return U8(4);
      case ImageBlockPacking::p_9_9_9_5:     return U8(4);
      case ImageBlockPacking::p_5_9_9_9:     return U8(4);
      case ImageBlockPacking::p_10_10_10_2:  return U8(4);
      case ImageBlockPacking::p_2_10_10_10:  return U8(4);
      case ImageBlockPacking::c_astc:        return U8(0);
      case ImageBlockPacking::c_atc:         return U8(0);
      case ImageBlockPacking::c_bptc:        return U8(0);
      case ImageBlockPacking::c_eac:         return U8(0);
      case ImageBlockPacking::c_etc1:        return U8(0);
      case ImageBlockPacking::c_etc2:        return U8(0);
      case ImageBlockPacking::c_pvrtc1:      return U8(0);
      case ImageBlockPacking::c_pvrtc2:      return U8(0);
      case ImageBlockPacking::c_s3tc1:       return U8(0);
      case ImageBlockPacking::c_s3tc2:       return U8(0);
      case ImageBlockPacking::c_s3tc3:       return U8(0);
      case ImageBlockPacking::c_s3tc4:       return U8(0);
      case ImageBlockPacking::c_s3tc5:       return U8(0);
      default:
         return U8(3);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_word_size(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8:           return U8(1);
      case ImageBlockPacking::s_8_8:         return U8(1);
      case ImageBlockPacking::s_8_8_8:       return U8(1);
      case ImageBlockPacking::s_8_8_8_8:     return U8(1);
      case ImageBlockPacking::s_16:          return U8(2);
      case ImageBlockPacking::s_16_16:       return U8(2);
      case ImageBlockPacking::s_16_16_16:    return U8(2);
      case ImageBlockPacking::s_16_16_16_16: return U8(2);
      case ImageBlockPacking::s_64:          return U8(8);
      case ImageBlockPacking::s_64_64:       return U8(8);
      case ImageBlockPacking::s_64_64_64:    return U8(8);
      case ImageBlockPacking::s_64_64_64_64: return U8(8);
      case ImageBlockPacking::p_4_4:         return U8(1);
      case ImageBlockPacking::p_3_3_2:       return U8(1);
      case ImageBlockPacking::p_2_3_3:       return U8(1);
      case ImageBlockPacking::p_3_2_3:       return U8(1);
      case ImageBlockPacking::p_4_4_4_4:     return U8(2);
      case ImageBlockPacking::p_1_5_5_5:     return U8(2);
      case ImageBlockPacking::p_5_5_5_1:     return U8(2);
      case ImageBlockPacking::p_5_6_5:       return U8(2);
      case ImageBlockPacking::c_astc:        return U8(0);
      case ImageBlockPacking::c_atc:         return U8(0);
      case ImageBlockPacking::c_bptc:        return U8(0);
      case ImageBlockPacking::c_eac:         return U8(0);
      case ImageBlockPacking::c_etc1:        return U8(0);
      case ImageBlockPacking::c_etc2:        return U8(0);
      case ImageBlockPacking::c_pvrtc1:      return U8(0);
      case ImageBlockPacking::c_pvrtc2:      return U8(0);
      case ImageBlockPacking::c_s3tc1:       return U8(0);
      case ImageBlockPacking::c_s3tc2:       return U8(0);
      case ImageBlockPacking::c_s3tc3:       return U8(0);
      case ImageBlockPacking::c_s3tc4:       return U8(0);
      case ImageBlockPacking::c_s3tc5:       return U8(0);
      default:
         return U8(4);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_word_count(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8_8:         return U8(2);
      case ImageBlockPacking::s_8_8_8:       return U8(3);
      case ImageBlockPacking::s_8_8_8_8:     return U8(4);
      case ImageBlockPacking::s_16_16:       return U8(2);
      case ImageBlockPacking::s_16_16_16:    return U8(3);
      case ImageBlockPacking::s_16_16_16_16: return U8(4);
      case ImageBlockPacking::s_32_32:       return U8(2);
      case ImageBlockPacking::s_32_32_32:    return U8(3);
      case ImageBlockPacking::s_32_32_32_32: return U8(4);
      case ImageBlockPacking::s_64_64:       return U8(2);
      case ImageBlockPacking::s_64_64_64:    return U8(3);
      case ImageBlockPacking::s_64_64_64_64: return U8(4);
      case ImageBlockPacking::s_32_p_24_8:   return U8(2);
      case ImageBlockPacking::c_astc:        return U8(0);
      case ImageBlockPacking::c_atc:         return U8(0);
      case ImageBlockPacking::c_bptc:        return U8(0);
      case ImageBlockPacking::c_eac:         return U8(0);
      case ImageBlockPacking::c_etc1:        return U8(0);
      case ImageBlockPacking::c_etc2:        return U8(0);
      case ImageBlockPacking::c_pvrtc1:      return U8(0);
      case ImageBlockPacking::c_pvrtc2:      return U8(0);
      case ImageBlockPacking::c_s3tc1:       return U8(0);
      case ImageBlockPacking::c_s3tc2:       return U8(0);
      case ImageBlockPacking::c_s3tc3:       return U8(0);
      case ImageBlockPacking::c_s3tc4:       return U8(0);
      case ImageBlockPacking::c_s3tc5:       return U8(0);
      default:
         return U8(1);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_word_offset_0(ImageBlockPacking constant) {
   switch (constant) {
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_word_offset_1(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8_8:         return U8(1);
      case ImageBlockPacking::s_8_8_8:       return U8(1);
      case ImageBlockPacking::s_8_8_8_8:     return U8(1);
      case ImageBlockPacking::s_16_16:       return U8(1);
      case ImageBlockPacking::s_16_16_16:    return U8(1);
      case ImageBlockPacking::s_16_16_16_16: return U8(1);
      case ImageBlockPacking::s_32_32:       return U8(1);
      case ImageBlockPacking::s_32_32_32:    return U8(1);
      case ImageBlockPacking::s_32_32_32_32: return U8(1);
      case ImageBlockPacking::s_64_64:       return U8(1);
      case ImageBlockPacking::s_64_64_64:    return U8(1);
      case ImageBlockPacking::s_64_64_64_64: return U8(1);
      case ImageBlockPacking::s_32_p_24_8:   return U8(1);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_word_offset_2(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8_8_8:       return U8(2);
      case ImageBlockPacking::s_8_8_8_8:     return U8(2);
      case ImageBlockPacking::s_16_16_16:    return U8(2);
      case ImageBlockPacking::s_16_16_16_16: return U8(2);
      case ImageBlockPacking::s_32_32_32:    return U8(2);
      case ImageBlockPacking::s_32_32_32_32: return U8(2);
      case ImageBlockPacking::s_64_64_64:    return U8(2);
      case ImageBlockPacking::s_64_64_64_64: return U8(2);
      case ImageBlockPacking::s_32_p_24_8:   return U8(1);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_word_offset_3(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8_8_8_8:     return U8(3);
      case ImageBlockPacking::s_16_16_16_16: return U8(3);
      case ImageBlockPacking::s_32_32_32_32: return U8(3);
      case ImageBlockPacking::s_64_64_64_64: return U8(3);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_bit_offset_0(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::p_4_4:         return U8(4);
      case ImageBlockPacking::p_3_3_2:       return U8(5);
      case ImageBlockPacking::p_2_3_3:       return U8(6);
      case ImageBlockPacking::p_3_2_3:       return U8(5);
      case ImageBlockPacking::p_4_4_4_4:     return U8(12);
      case ImageBlockPacking::p_1_5_5_5:     return U8(15);
      case ImageBlockPacking::p_5_5_5_1:     return U8(11);
      case ImageBlockPacking::p_5_6_5:       return U8(11);
      case ImageBlockPacking::p_8_24:        return U8(24);
      case ImageBlockPacking::p_24_8:        return U8(8);
      case ImageBlockPacking::p_11_11_10:    return U8(21);
      case ImageBlockPacking::p_10_11_11:    return U8(22);
      case ImageBlockPacking::p_11_10_11:    return U8(21);
      case ImageBlockPacking::p_8_8_8_8:     return U8(24);
      case ImageBlockPacking::p_9_9_9_5:     return U8(23);
      case ImageBlockPacking::p_5_9_9_9:     return U8(27);
      case ImageBlockPacking::p_10_10_10_2:  return U8(22);
      case ImageBlockPacking::p_2_10_10_10:  return U8(30);
      case ImageBlockPacking::s_32_p_24_8:   return U8(32);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_bit_offset_1(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::p_3_3_2:       return U8(2);
      case ImageBlockPacking::p_2_3_3:       return U8(3);
      case ImageBlockPacking::p_3_2_3:       return U8(3);
      case ImageBlockPacking::p_4_4_4_4:     return U8(8);
      case ImageBlockPacking::p_1_5_5_5:     return U8(10);
      case ImageBlockPacking::p_5_5_5_1:     return U8(6);
      case ImageBlockPacking::p_5_6_5:       return U8(5);
      case ImageBlockPacking::p_11_11_10:    return U8(10);
      case ImageBlockPacking::p_10_11_11:    return U8(11);
      case ImageBlockPacking::p_11_10_11:    return U8(11);
      case ImageBlockPacking::p_8_8_8_8:     return U8(16);
      case ImageBlockPacking::p_9_9_9_5:     return U8(14);
      case ImageBlockPacking::p_5_9_9_9:     return U8(18);
      case ImageBlockPacking::p_10_10_10_2:  return U8(12);
      case ImageBlockPacking::p_2_10_10_10:  return U8(20);
      case ImageBlockPacking::s_32_p_24_8:   return U8(8);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_bit_offset_2(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::p_4_4_4_4:     return U8(4);
      case ImageBlockPacking::p_1_5_5_5:     return U8(5);
      case ImageBlockPacking::p_5_5_5_1:     return U8(1);
      case ImageBlockPacking::p_8_8_8_8:     return U8(8);
      case ImageBlockPacking::p_9_9_9_5:     return U8(5);
      case ImageBlockPacking::p_5_9_9_9:     return U8(9);
      case ImageBlockPacking::p_10_10_10_2:  return U8(2);
      case ImageBlockPacking::p_2_10_10_10:  return U8(10);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_bit_offset_3(ImageBlockPacking constant) {
   switch (constant) {
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_bit_width_0(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8:           return U8(8);
      case ImageBlockPacking::s_8_8:         return U8(8);
      case ImageBlockPacking::s_8_8_8:       return U8(8);
      case ImageBlockPacking::s_8_8_8_8:     return U8(8);
      case ImageBlockPacking::s_16:          return U8(16);
      case ImageBlockPacking::s_16_16:       return U8(16);
      case ImageBlockPacking::s_16_16_16:    return U8(16);
      case ImageBlockPacking::s_16_16_16_16: return U8(16);
      case ImageBlockPacking::s_32:          return U8(32);
      case ImageBlockPacking::s_32_32:       return U8(32);
      case ImageBlockPacking::s_32_32_32:    return U8(32);
      case ImageBlockPacking::s_32_32_32_32: return U8(32);
      case ImageBlockPacking::s_64:          return U8(64);
      case ImageBlockPacking::s_64_64:       return U8(64);
      case ImageBlockPacking::s_64_64_64:    return U8(64);
      case ImageBlockPacking::s_64_64_64_64: return U8(64);
      case ImageBlockPacking::p_4_4:         return U8(4);
      case ImageBlockPacking::p_3_3_2:       return U8(3);
      case ImageBlockPacking::p_2_3_3:       return U8(2);
      case ImageBlockPacking::p_3_2_3:       return U8(3);
      case ImageBlockPacking::p_4_4_4_4:     return U8(4);
      case ImageBlockPacking::p_1_5_5_5:     return U8(1);
      case ImageBlockPacking::p_5_5_5_1:     return U8(5);
      case ImageBlockPacking::p_5_6_5:       return U8(5);
      case ImageBlockPacking::p_8_24:        return U8(8);
      case ImageBlockPacking::p_24_8:        return U8(24);
      case ImageBlockPacking::p_11_11_10:    return U8(11);
      case ImageBlockPacking::p_10_11_11:    return U8(10);
      case ImageBlockPacking::p_11_10_11:    return U8(11);
      case ImageBlockPacking::p_8_8_8_8:     return U8(8);
      case ImageBlockPacking::p_9_9_9_5:     return U8(9);
      case ImageBlockPacking::p_5_9_9_9:     return U8(5);
      case ImageBlockPacking::p_10_10_10_2:  return U8(10);
      case ImageBlockPacking::p_2_10_10_10:  return U8(2);
      case ImageBlockPacking::s_32_p_24_8:   return U8(32);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_bit_width_1(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8_8:         return U8(8);
      case ImageBlockPacking::s_8_8_8:       return U8(8);
      case ImageBlockPacking::s_8_8_8_8:     return U8(8);
      case ImageBlockPacking::s_16_16:       return U8(16);
      case ImageBlockPacking::s_16_16_16:    return U8(16);
      case ImageBlockPacking::s_16_16_16_16: return U8(16);
      case ImageBlockPacking::s_32_32:       return U8(32);
      case ImageBlockPacking::s_32_32_32:    return U8(32);
      case ImageBlockPacking::s_32_32_32_32: return U8(32);
      case ImageBlockPacking::s_64_64:       return U8(64);
      case ImageBlockPacking::s_64_64_64:    return U8(64);
      case ImageBlockPacking::s_64_64_64_64: return U8(64);
      case ImageBlockPacking::p_4_4:         return U8(4);
      case ImageBlockPacking::p_3_3_2:       return U8(3);
      case ImageBlockPacking::p_2_3_3:       return U8(3);
      case ImageBlockPacking::p_3_2_3:       return U8(2);
      case ImageBlockPacking::p_4_4_4_4:     return U8(4);
      case ImageBlockPacking::p_1_5_5_5:     return U8(5);
      case ImageBlockPacking::p_5_5_5_1:     return U8(5);
      case ImageBlockPacking::p_5_6_5:       return U8(6);
      case ImageBlockPacking::p_8_24:        return U8(24);
      case ImageBlockPacking::p_24_8:        return U8(8);
      case ImageBlockPacking::p_11_11_10:    return U8(11);
      case ImageBlockPacking::p_10_11_11:    return U8(11);
      case ImageBlockPacking::p_11_10_11:    return U8(10);
      case ImageBlockPacking::p_8_8_8_8:     return U8(8);
      case ImageBlockPacking::p_9_9_9_5:     return U8(9);
      case ImageBlockPacking::p_5_9_9_9:     return U8(9);
      case ImageBlockPacking::p_10_10_10_2:  return U8(10);
      case ImageBlockPacking::p_2_10_10_10:  return U8(10);
      case ImageBlockPacking::s_32_p_24_8:   return U8(24);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_bit_width_2(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8_8_8:       return U8(8);
      case ImageBlockPacking::s_8_8_8_8:     return U8(8);
      case ImageBlockPacking::s_16_16_16:    return U8(16);
      case ImageBlockPacking::s_16_16_16_16: return U8(16);
      case ImageBlockPacking::s_32_32_32:    return U8(32);
      case ImageBlockPacking::s_32_32_32_32: return U8(32);
      case ImageBlockPacking::s_64_64_64:    return U8(64);
      case ImageBlockPacking::s_64_64_64_64: return U8(64);
      case ImageBlockPacking::p_3_3_2:       return U8(2);
      case ImageBlockPacking::p_2_3_3:       return U8(3);
      case ImageBlockPacking::p_3_2_3:       return U8(3);
      case ImageBlockPacking::p_4_4_4_4:     return U8(4);
      case ImageBlockPacking::p_1_5_5_5:     return U8(5);
      case ImageBlockPacking::p_5_5_5_1:     return U8(5);
      case ImageBlockPacking::p_5_6_5:       return U8(5);
      case ImageBlockPacking::p_11_11_10:    return U8(10);
      case ImageBlockPacking::p_10_11_11:    return U8(11);
      case ImageBlockPacking::p_11_10_11:    return U8(11);
      case ImageBlockPacking::p_8_8_8_8:     return U8(8);
      case ImageBlockPacking::p_9_9_9_5:     return U8(9);
      case ImageBlockPacking::p_5_9_9_9:     return U8(9);
      case ImageBlockPacking::p_10_10_10_2:  return U8(10);
      case ImageBlockPacking::p_2_10_10_10:  return U8(10);
      case ImageBlockPacking::s_32_p_24_8:   return U8(8);
      default:
         return U8(0);
   }
}

///////////////////////////////////////////////////////////////////////////////
U8 image_block_bit_width_3(ImageBlockPacking constant) {
   switch (constant) {
      case ImageBlockPacking::s_8_8_8_8:     return U8(8);
      case ImageBlockPacking::s_16_16_16_16: return U8(16);
      case ImageBlockPacking::s_32_32_32_32: return U8(32);
      case ImageBlockPacking::s_64_64_64_64: return U8(64);
      case ImageBlockPacking::p_4_4_4_4:     return U8(4);
      case ImageBlockPacking::p_1_5_5_5:     return U8(5);
      case ImageBlockPacking::p_5_5_5_1:     return U8(1);
      case ImageBlockPacking::p_8_8_8_8:     return U8(8);
      case ImageBlockPacking::p_9_9_9_5:     return U8(5);
      case ImageBlockPacking::p_5_9_9_9:     return U8(9);
      case ImageBlockPacking::p_10_10_10_2:  return U8(2);
      case ImageBlockPacking::p_2_10_10_10:  return U8(10);
      default:
         return U8(0);
   }
}

/* ######################### END OF GENERATED CODE ######################### */

} // be::gfx
