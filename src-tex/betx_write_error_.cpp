#include "pch.hpp"
#include "betx_write_error_.hpp"

/*!! include 'tex/betx_write_error' !! 124 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(BetxWriteError constant) noexcept {
   switch (constant) {
      case BetxWriteError::invalid_endianness:
      case BetxWriteError::empty_texture:
      case BetxWriteError::invalid_texture_class:
      case BetxWriteError::invalid_block_packing:
      case BetxWriteError::invalid_colorspace:
      case BetxWriteError::invalid_layer_count:
      case BetxWriteError::invalid_face_count:
      case BetxWriteError::invalid_level_count:
      case BetxWriteError::invalid_field_type:
      case BetxWriteError::invalid_swizzle:
      case BetxWriteError::invalid_payload_compression:
      case BetxWriteError::not_enough_memory:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* betx_write_error_name(BetxWriteError constant) noexcept {
   switch (constant) {
      case BetxWriteError::invalid_endianness:          return "invalid_endianness";
      case BetxWriteError::empty_texture:               return "empty_texture";
      case BetxWriteError::invalid_texture_class:       return "invalid_texture_class";
      case BetxWriteError::invalid_block_packing:       return "invalid_block_packing";
      case BetxWriteError::invalid_colorspace:          return "invalid_colorspace";
      case BetxWriteError::invalid_layer_count:         return "invalid_layer_count";
      case BetxWriteError::invalid_face_count:          return "invalid_face_count";
      case BetxWriteError::invalid_level_count:         return "invalid_level_count";
      case BetxWriteError::invalid_field_type:          return "invalid_field_type";
      case BetxWriteError::invalid_swizzle:             return "invalid_swizzle";
      case BetxWriteError::invalid_payload_compression: return "invalid_payload_compression";
      case BetxWriteError::not_enough_memory:           return "not_enough_memory";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const BetxWriteError, 12> betx_write_error_values() noexcept {
   return ::be::EnumTraits<BetxWriteError>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, BetxWriteError constant) {
   if (is_valid(constant)) {
      os << betx_write_error_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
int texture_file_error_condition(BetxWriteError constant) noexcept {
   switch (constant) {
      case BetxWriteError::invalid_endianness:          return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::empty_texture:               return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_texture_class:       return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_block_packing:       return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_colorspace:          return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_layer_count:         return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_face_count:          return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_level_count:         return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_field_type:          return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_swizzle:             return static_cast<int>(TextureFileError::unsupported);
      case BetxWriteError::invalid_payload_compression: return static_cast<int>(TextureFileError::unsupported);
      default:
         return 0;
   }
}

///////////////////////////////////////////////////////////////////////////////
int generic_error_condition(BetxWriteError constant) noexcept {
   switch (constant) {
      case BetxWriteError::invalid_endianness:          return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::empty_texture:               return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_texture_class:       return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_block_packing:       return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_colorspace:          return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_layer_count:         return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_face_count:          return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_level_count:         return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_field_type:          return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_swizzle:             return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::invalid_payload_compression: return static_cast<int>(std::errc::invalid_argument);
      case BetxWriteError::not_enough_memory:           return static_cast<int>(std::errc::not_enough_memory);
      default:
         return 0;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* write_error_msg(BetxWriteError constant) noexcept {
   switch (constant) {
      case BetxWriteError::invalid_endianness:          return "Endianness not recognized";
      case BetxWriteError::empty_texture:               return "Texture format and dimensions have zero size";
      case BetxWriteError::invalid_texture_class:       return "Texture class not recognized";
      case BetxWriteError::invalid_block_packing:       return "Block packing not recognized";
      case BetxWriteError::invalid_colorspace:          return "Colorspace not recognized";
      case BetxWriteError::invalid_layer_count:         return "Layer count must be in the range [ 1, 65535 ]";
      case BetxWriteError::invalid_face_count:          return "Face count must be in the range [ 1, 255 ]";
      case BetxWriteError::invalid_level_count:         return "Mipmap level count must be in the range [ 1, 255 ]";
      case BetxWriteError::invalid_field_type:          return "Field type not recognized";
      case BetxWriteError::invalid_swizzle:             return "Swizzle not recognized";
      case BetxWriteError::invalid_payload_compression: return "Payload compression mode not recognized";
      case BetxWriteError::not_enough_memory:           return "Could not allocate enough memory";
      default:
         return "An unknown error occurred";
   }
}

} // be::gfx::tex::detail


/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
S BetxWriteErrorCategory::message(int condition) const {
   return write_error_msg(static_cast<BetxWriteError>(condition));
}

///////////////////////////////////////////////////////////////////////////////
bool BetxWriteErrorCategory::equivalent(int code, const std::error_condition& condition) const noexcept {
   if (condition.category() == std::generic_category() &&
       condition.value() == generic_error_condition(static_cast<BetxWriteError>(code))) {
      return true;
   }

   if (condition.category() == texture_file_error_category() && condition.value() == texture_file_error_condition(static_cast<BetxWriteError>(code))) {
      return true;
   }

   if (condition.category() == betx_write_error_category() &&
       condition.value() == code) {
      return true;
   }

   return false;
}

///////////////////////////////////////////////////////////////////////////////
const std::error_category& betx_write_error_category() {
   static BetxWriteErrorCategory instance;
   return instance;
}

///////////////////////////////////////////////////////////////////////////////
std::error_code make_error_code(BetxWriteError e) {
   return std::error_code(static_cast<int>(e), betx_write_error_category());
}

///////////////////////////////////////////////////////////////////////////////
std::error_condition make_error_condition(BetxWriteError e) {
   return std::error_condition(static_cast<int>(e), betx_write_error_category());
}

} // be::gfx::tex::detail
