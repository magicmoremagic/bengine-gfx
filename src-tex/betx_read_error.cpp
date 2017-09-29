#include "pch.hpp"
#include "tex/betx_read_error.hpp"

/*!! include 'tex/betx_read_error' !! 302 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(BetxReadError constant) noexcept {
   switch (constant) {
      case BetxReadError::not_a_mmm_binary_file:
      case BetxReadError::not_a_betx_file:
      case BetxReadError::crlf_corruption:
      case BetxReadError::lf_corruption:
      case BetxReadError::header_missing:
      case BetxReadError::footer_missing:
      case BetxReadError::invalid_endianness:
      case BetxReadError::unsupported_file_version:
      case BetxReadError::invalid_texture_class:
      case BetxReadError::invalid_dimensions:
      case BetxReadError::unsupported_dimensions:
      case BetxReadError::invalid_layer_count:
      case BetxReadError::unsupported_layer_count:
      case BetxReadError::invalid_face_count:
      case BetxReadError::unsupported_face_count:
      case BetxReadError::invalid_level_count:
      case BetxReadError::unsupported_level_count:
      case BetxReadError::unnecessary_levels:
      case BetxReadError::unsupported_alignment:
      case BetxReadError::noncanonical_alignment:
      case BetxReadError::invalid_block_packing:
      case BetxReadError::invalid_block_dimensions:
      case BetxReadError::unsupported_block_dimensions:
      case BetxReadError::invalid_block_size:
      case BetxReadError::unsupported_block_size:
      case BetxReadError::invalid_field_type:
      case BetxReadError::invalid_component_count:
      case BetxReadError::too_many_components:
      case BetxReadError::invalid_swizzle:
      case BetxReadError::invalid_colorspace:
      case BetxReadError::invalid_format_flag:
      case BetxReadError::invalid_block_span:
      case BetxReadError::negative_block_padding:
      case BetxReadError::invalid_payload_compression:
      case BetxReadError::empty_texture:
      case BetxReadError::invalid_payload_offset:
      case BetxReadError::invalid_metadata_location:
      case BetxReadError::metadata_missing:
      case BetxReadError::file_too_small:
      case BetxReadError::not_enough_texture_data:
      case BetxReadError::image_unavailable:
      case BetxReadError::layered_non_array:
      case BetxReadError::not_enough_faces:
      case BetxReadError::too_many_faces:
      case BetxReadError::nonzero_reserved:
      case BetxReadError::not_enough_memory:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* betx_read_error_name(BetxReadError constant) noexcept {
   switch (constant) {
      case BetxReadError::not_a_mmm_binary_file:        return "not_a_mmm_binary_file";
      case BetxReadError::not_a_betx_file:              return "not_a_betx_file";
      case BetxReadError::crlf_corruption:              return "crlf_corruption";
      case BetxReadError::lf_corruption:                return "lf_corruption";
      case BetxReadError::header_missing:               return "header_missing";
      case BetxReadError::footer_missing:               return "footer_missing";
      case BetxReadError::invalid_endianness:           return "invalid_endianness";
      case BetxReadError::unsupported_file_version:     return "unsupported_file_version";
      case BetxReadError::invalid_texture_class:        return "invalid_texture_class";
      case BetxReadError::invalid_dimensions:           return "invalid_dimensions";
      case BetxReadError::unsupported_dimensions:       return "unsupported_dimensions";
      case BetxReadError::invalid_layer_count:          return "invalid_layer_count";
      case BetxReadError::unsupported_layer_count:      return "unsupported_layer_count";
      case BetxReadError::invalid_face_count:           return "invalid_face_count";
      case BetxReadError::unsupported_face_count:       return "unsupported_face_count";
      case BetxReadError::invalid_level_count:          return "invalid_level_count";
      case BetxReadError::unsupported_level_count:      return "unsupported_level_count";
      case BetxReadError::unnecessary_levels:           return "unnecessary_levels";
      case BetxReadError::unsupported_alignment:        return "unsupported_alignment";
      case BetxReadError::noncanonical_alignment:       return "noncanonical_alignment";
      case BetxReadError::invalid_block_packing:        return "invalid_block_packing";
      case BetxReadError::invalid_block_dimensions:     return "invalid_block_dimensions";
      case BetxReadError::unsupported_block_dimensions: return "unsupported_block_dimensions";
      case BetxReadError::invalid_block_size:           return "invalid_block_size";
      case BetxReadError::unsupported_block_size:       return "unsupported_block_size";
      case BetxReadError::invalid_field_type:           return "invalid_field_type";
      case BetxReadError::invalid_component_count:      return "invalid_component_count";
      case BetxReadError::too_many_components:          return "too_many_components";
      case BetxReadError::invalid_swizzle:              return "invalid_swizzle";
      case BetxReadError::invalid_colorspace:           return "invalid_colorspace";
      case BetxReadError::invalid_format_flag:          return "invalid_format_flag";
      case BetxReadError::invalid_block_span:           return "invalid_block_span";
      case BetxReadError::negative_block_padding:       return "negative_block_padding";
      case BetxReadError::invalid_payload_compression:  return "invalid_payload_compression";
      case BetxReadError::empty_texture:                return "empty_texture";
      case BetxReadError::invalid_payload_offset:       return "invalid_payload_offset";
      case BetxReadError::invalid_metadata_location:    return "invalid_metadata_location";
      case BetxReadError::metadata_missing:             return "metadata_missing";
      case BetxReadError::file_too_small:               return "file_too_small";
      case BetxReadError::not_enough_texture_data:      return "not_enough_texture_data";
      case BetxReadError::image_unavailable:            return "image_unavailable";
      case BetxReadError::layered_non_array:            return "layered_non_array";
      case BetxReadError::not_enough_faces:             return "not_enough_faces";
      case BetxReadError::too_many_faces:               return "too_many_faces";
      case BetxReadError::nonzero_reserved:             return "nonzero_reserved";
      case BetxReadError::not_enough_memory:            return "not_enough_memory";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const BetxReadError, 46> betx_read_error_values() noexcept {
   return ::be::EnumTraits<BetxReadError>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, BetxReadError constant) {
   if (is_valid(constant)) {
      os << betx_read_error_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
bool is_fatal(BetxReadError constant) noexcept {
   switch (constant) {
      case BetxReadError::not_a_mmm_binary_file:        return true;
      case BetxReadError::not_a_betx_file:              return true;
      case BetxReadError::header_missing:               return true;
      case BetxReadError::invalid_endianness:           return true;
      case BetxReadError::unsupported_dimensions:       return true;
      case BetxReadError::invalid_block_packing:        return true;
      case BetxReadError::unsupported_block_dimensions: return true;
      case BetxReadError::negative_block_padding:       return true;
      case BetxReadError::invalid_payload_compression:  return true;
      case BetxReadError::empty_texture:                return true;
      case BetxReadError::not_enough_memory:            return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
int texture_file_error_condition(BetxReadError constant) noexcept {
   switch (constant) {
      case BetxReadError::not_a_mmm_binary_file:        return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::not_a_betx_file:              return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::crlf_corruption:              return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::lf_corruption:                return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::header_missing:               return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::footer_missing:               return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_endianness:           return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::unsupported_file_version:     return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::invalid_texture_class:        return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_dimensions:           return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::unsupported_dimensions:       return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::invalid_layer_count:          return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::unsupported_layer_count:      return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::invalid_face_count:           return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::unsupported_face_count:       return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::invalid_level_count:          return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::unsupported_level_count:      return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::unsupported_alignment:        return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::invalid_block_packing:        return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_block_dimensions:     return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::unsupported_block_dimensions: return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::invalid_block_size:           return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::unsupported_block_size:       return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::invalid_field_type:           return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_component_count:      return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::too_many_components:          return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_swizzle:              return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_colorspace:           return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_format_flag:          return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_block_span:           return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::negative_block_padding:       return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_payload_compression:  return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::empty_texture:                return static_cast<int>(TextureFileError::unsupported);
      case BetxReadError::invalid_payload_offset:       return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::invalid_metadata_location:    return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::metadata_missing:             return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::file_too_small:               return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::not_enough_texture_data:      return static_cast<int>(TextureFileError::corrupted);
      case BetxReadError::image_unavailable:            return static_cast<int>(TextureFileError::image_unavailable);
      case BetxReadError::nonzero_reserved:             return static_cast<int>(TextureFileError::corrupted);
      default:
         return 0;
   }
}

///////////////////////////////////////////////////////////////////////////////
int generic_error_condition(BetxReadError constant) noexcept {
   switch (constant) {
      case BetxReadError::not_a_mmm_binary_file:        return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::not_a_betx_file:              return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::crlf_corruption:              return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::lf_corruption:                return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::header_missing:               return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::footer_missing:               return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_endianness:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::unsupported_file_version:     return static_cast<int>(std::errc::not_supported);
      case BetxReadError::invalid_texture_class:        return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_dimensions:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::unsupported_dimensions:       return static_cast<int>(std::errc::not_supported);
      case BetxReadError::invalid_layer_count:          return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::unsupported_layer_count:      return static_cast<int>(std::errc::not_supported);
      case BetxReadError::invalid_face_count:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::unsupported_face_count:       return static_cast<int>(std::errc::not_supported);
      case BetxReadError::invalid_level_count:          return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::unsupported_level_count:      return static_cast<int>(std::errc::not_supported);
      case BetxReadError::unsupported_alignment:        return static_cast<int>(std::errc::not_supported);
      case BetxReadError::invalid_block_packing:        return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_block_dimensions:     return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::unsupported_block_dimensions: return static_cast<int>(std::errc::not_supported);
      case BetxReadError::invalid_block_size:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::unsupported_block_size:       return static_cast<int>(std::errc::not_supported);
      case BetxReadError::invalid_field_type:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_component_count:      return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::too_many_components:          return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_swizzle:              return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_colorspace:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_format_flag:          return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_block_span:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::negative_block_padding:       return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_payload_compression:  return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::empty_texture:                return static_cast<int>(std::errc::not_supported);
      case BetxReadError::invalid_payload_offset:       return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::invalid_metadata_location:    return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::metadata_missing:             return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::file_too_small:               return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::not_enough_texture_data:      return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::nonzero_reserved:             return static_cast<int>(std::errc::illegal_byte_sequence);
      case BetxReadError::not_enough_memory:            return static_cast<int>(std::errc::not_enough_memory);
      default:
         return 0;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* read_error_msg(BetxReadError constant) noexcept {
   switch (constant) {
      case BetxReadError::not_a_mmm_binary_file:        return "Magic/More Magic binary file header not present";
      case BetxReadError::not_a_betx_file:              return "Not a bengine texture file";
      case BetxReadError::crlf_corruption:              return "CR-LF sequences may have been converted to LF";
      case BetxReadError::lf_corruption:                return "LF bytes may have been converted to CR-LF";
      case BetxReadError::header_missing:               return "beTx header not present; file may have been truncated";
      case BetxReadError::footer_missing:               return "beTx footer not present; file may have been truncated or appended to";
      case BetxReadError::invalid_endianness:           return "Endianness not recognized";
      case BetxReadError::unsupported_file_version:     return "beTx file version is invalid or unsupported";
      case BetxReadError::invalid_texture_class:        return "Texture class not recognized";
      case BetxReadError::invalid_dimensions:           return "All texture dimensions must be >= 1";
      case BetxReadError::unsupported_dimensions:       return "Texture dimensions too large to load";
      case BetxReadError::invalid_layer_count:          return "Layer count must be >= 1";
      case BetxReadError::unsupported_layer_count:      return "Layer count too large to load";
      case BetxReadError::invalid_face_count:           return "Face count must be >= 1";
      case BetxReadError::unsupported_face_count:       return "Face count too large to load";
      case BetxReadError::invalid_level_count:          return "Mipmap level count must be >= 1";
      case BetxReadError::unsupported_level_count:      return "Mipmap level count too large to load";
      case BetxReadError::unnecessary_levels:           return "More mipmap levels specified than necessary";
      case BetxReadError::unsupported_alignment:        return "Texture data alignment is too large";
      case BetxReadError::noncanonical_alignment:       return "Line, plane, level, face, or layer alignment is smaller than a previous alignment";
      case BetxReadError::invalid_block_packing:        return "Block packing not recognized";
      case BetxReadError::invalid_block_dimensions:     return "All block dimensions must be >= 1";
      case BetxReadError::unsupported_block_dimensions: return "Block dimensions too large to load";
      case BetxReadError::invalid_block_size:           return "Block size must be >= 1";
      case BetxReadError::unsupported_block_size:       return "Block size too large to load";
      case BetxReadError::invalid_field_type:           return "Field type not recognized";
      case BetxReadError::invalid_component_count:      return "Component count must be between 1 and 4";
      case BetxReadError::too_many_components:          return "Only 4 components per texel can be accessed";
      case BetxReadError::invalid_swizzle:              return "Swizzle not recognized";
      case BetxReadError::invalid_colorspace:           return "Colorspace not recognized";
      case BetxReadError::invalid_format_flag:          return "Unrecognized format flag bit set";
      case BetxReadError::invalid_block_span:           return "Block span must be >= 1";
      case BetxReadError::negative_block_padding:       return "Block span must be >= block size";
      case BetxReadError::invalid_payload_compression:  return "Payload compression mode not recognized";
      case BetxReadError::empty_texture:                return "Texture format and dimensions have zero size";
      case BetxReadError::invalid_payload_offset:       return "Payload cannot overlap header or metadata";
      case BetxReadError::invalid_metadata_location:    return "Unrecognized metadata location";
      case BetxReadError::metadata_missing:             return "Metadata not present; file may have been truncated";
      case BetxReadError::file_too_small:               return "File is too small to fit header, metadata, payload, and footer; possible truncation, overlap, or corruption";
      case BetxReadError::not_enough_texture_data:      return "Calculated texture size is greater than the uncompressed payload data size";
      case BetxReadError::image_unavailable:            return "The requested layer, face, or mipmap level is not present in the texture";
      case BetxReadError::layered_non_array:            return "Multiple layers specified, but not using an array texture class";
      case BetxReadError::not_enough_faces:             return "Fewer faces specified than expected for this texture class";
      case BetxReadError::too_many_faces:               return "More faces specified than expected for this texture class";
      case BetxReadError::nonzero_reserved:             return "Reserved header field is not zero";
      case BetxReadError::not_enough_memory:            return "Could not allocate enough memory for texture storage";
      default:
         return "An unknown error occurred";
   }
}

} // be::gfx::tex::detail


/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
S BetxReadErrorCategory::message(int condition) const {
   return read_error_msg(static_cast<BetxReadError>(condition));
}

///////////////////////////////////////////////////////////////////////////////
bool BetxReadErrorCategory::equivalent(int code, const std::error_condition& condition) const noexcept {
   if (condition.category() == std::generic_category() &&
       condition.value() == generic_error_condition(static_cast<BetxReadError>(code))) {
      return true;
   }

   if (condition.category() == texture_file_error_category()) {
      if (condition.value() == static_cast<int>(TextureFileError::fatal_error) && is_fatal(static_cast<BetxReadError>(code))) {
         return true;
      }
      if (condition.value() == texture_file_error_condition(static_cast<BetxReadError>(code))) {
         return true;
      }
   }

   if (condition.category() == betx_read_error_category() &&
       condition.value() == code) {
      return true;
   }

   return false;
}

///////////////////////////////////////////////////////////////////////////////
const std::error_category& betx_read_error_category() {
   static BetxReadErrorCategory instance;
   return instance;
}

///////////////////////////////////////////////////////////////////////////////
std::error_code make_error_code(BetxReadError e) {
   return std::error_code(static_cast<int>(e), betx_read_error_category());
}

///////////////////////////////////////////////////////////////////////////////
std::error_condition make_error_condition(BetxReadError e) {
   return std::error_condition(static_cast<int>(e), betx_read_error_category());
}

} // be::gfx::tex::detail
