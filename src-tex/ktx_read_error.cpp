#include "pch.hpp"
#include "tex/ktx_read_error.hpp"

/*!! include 'tex/ktx_read_error' !! 185 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(KtxReadError constant) noexcept {
   switch (constant) {
      case KtxReadError::not_a_ktx_file:
      case KtxReadError::unsupported_file_version:
      case KtxReadError::file_corruption:
      case KtxReadError::header_missing:
      case KtxReadError::unsupported_endianness:
      case KtxReadError::unsupported_image_format:
      case KtxReadError::invalid_gl_type_size:
      case KtxReadError::invalid_texture_class:
      case KtxReadError::invalid_dimensions:
      case KtxReadError::unsupported_dimensions:
      case KtxReadError::unsupported_layer_count:
      case KtxReadError::invalid_face_count:
      case KtxReadError::unsupported_face_count:
      case KtxReadError::unsupported_level_count:
      case KtxReadError::unnecessary_levels:
      case KtxReadError::empty_texture:
      case KtxReadError::metadata_missing:
      case KtxReadError::not_enough_texture_data:
      case KtxReadError::image_unavailable:
      case KtxReadError::layered_non_array:
      case KtxReadError::not_enough_faces:
      case KtxReadError::too_many_faces:
      case KtxReadError::not_enough_memory:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* ktx_read_error_name(KtxReadError constant) noexcept {
   switch (constant) {
      case KtxReadError::not_a_ktx_file:           return "not_a_ktx_file";
      case KtxReadError::unsupported_file_version: return "unsupported_file_version";
      case KtxReadError::file_corruption:          return "file_corruption";
      case KtxReadError::header_missing:           return "header_missing";
      case KtxReadError::unsupported_endianness:   return "unsupported_endianness";
      case KtxReadError::unsupported_image_format: return "unsupported_image_format";
      case KtxReadError::invalid_gl_type_size:     return "invalid_gl_type_size";
      case KtxReadError::invalid_texture_class:    return "invalid_texture_class";
      case KtxReadError::invalid_dimensions:       return "invalid_dimensions";
      case KtxReadError::unsupported_dimensions:   return "unsupported_dimensions";
      case KtxReadError::unsupported_layer_count:  return "unsupported_layer_count";
      case KtxReadError::invalid_face_count:       return "invalid_face_count";
      case KtxReadError::unsupported_face_count:   return "unsupported_face_count";
      case KtxReadError::unsupported_level_count:  return "unsupported_level_count";
      case KtxReadError::unnecessary_levels:       return "unnecessary_levels";
      case KtxReadError::empty_texture:            return "empty_texture";
      case KtxReadError::metadata_missing:         return "metadata_missing";
      case KtxReadError::not_enough_texture_data:  return "not_enough_texture_data";
      case KtxReadError::image_unavailable:        return "image_unavailable";
      case KtxReadError::layered_non_array:        return "layered_non_array";
      case KtxReadError::not_enough_faces:         return "not_enough_faces";
      case KtxReadError::too_many_faces:           return "too_many_faces";
      case KtxReadError::not_enough_memory:        return "not_enough_memory";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const KtxReadError, 23> ktx_read_error_values() noexcept {
   return ::be::EnumTraits<KtxReadError>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, KtxReadError constant) {
   if (is_valid(constant)) {
      os << ktx_read_error_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

///////////////////////////////////////////////////////////////////////////////
bool is_fatal(KtxReadError constant) noexcept {
   switch (constant) {
      case KtxReadError::not_a_ktx_file:           return true;
      case KtxReadError::header_missing:           return true;
      case KtxReadError::unsupported_endianness:   return true;
      case KtxReadError::unsupported_image_format: return true;
      case KtxReadError::unsupported_dimensions:   return true;
      case KtxReadError::empty_texture:            return true;
      case KtxReadError::not_enough_memory:        return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
int texture_file_error_condition(KtxReadError constant) noexcept {
   switch (constant) {
      case KtxReadError::not_a_ktx_file:           return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::unsupported_file_version: return static_cast<int>(TextureFileError::unsupported);
      case KtxReadError::file_corruption:          return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::header_missing:           return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::unsupported_endianness:   return static_cast<int>(TextureFileError::unsupported);
      case KtxReadError::unsupported_image_format: return static_cast<int>(TextureFileError::unsupported);
      case KtxReadError::invalid_gl_type_size:     return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::invalid_texture_class:    return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::invalid_dimensions:       return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::unsupported_dimensions:   return static_cast<int>(TextureFileError::unsupported);
      case KtxReadError::unsupported_layer_count:  return static_cast<int>(TextureFileError::unsupported);
      case KtxReadError::invalid_face_count:       return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::unsupported_face_count:   return static_cast<int>(TextureFileError::unsupported);
      case KtxReadError::unsupported_level_count:  return static_cast<int>(TextureFileError::unsupported);
      case KtxReadError::empty_texture:            return static_cast<int>(TextureFileError::unsupported);
      case KtxReadError::metadata_missing:         return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::not_enough_texture_data:  return static_cast<int>(TextureFileError::corrupted);
      case KtxReadError::image_unavailable:        return static_cast<int>(TextureFileError::image_unavailable);
      default:
         return 0;
   }
}

///////////////////////////////////////////////////////////////////////////////
int generic_error_condition(KtxReadError constant) noexcept {
   switch (constant) {
      case KtxReadError::not_a_ktx_file:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::unsupported_file_version: return static_cast<int>(std::errc::not_supported);
      case KtxReadError::file_corruption:          return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::header_missing:           return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::unsupported_endianness:   return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::unsupported_image_format: return static_cast<int>(std::errc::not_supported);
      case KtxReadError::invalid_gl_type_size:     return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::invalid_texture_class:    return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::invalid_dimensions:       return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::unsupported_dimensions:   return static_cast<int>(std::errc::not_supported);
      case KtxReadError::unsupported_layer_count:  return static_cast<int>(std::errc::not_supported);
      case KtxReadError::invalid_face_count:       return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::unsupported_face_count:   return static_cast<int>(std::errc::not_supported);
      case KtxReadError::unsupported_level_count:  return static_cast<int>(std::errc::not_supported);
      case KtxReadError::empty_texture:            return static_cast<int>(std::errc::not_supported);
      case KtxReadError::metadata_missing:         return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::not_enough_texture_data:  return static_cast<int>(std::errc::illegal_byte_sequence);
      case KtxReadError::not_enough_memory:        return static_cast<int>(std::errc::not_enough_memory);
      default:
         return 0;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* read_error_msg(KtxReadError constant) noexcept {
   switch (constant) {
      case KtxReadError::not_a_ktx_file:           return "Not a Khronos texture file";
      case KtxReadError::unsupported_file_version: return "KTX file version is invalid or unsupported";
      case KtxReadError::file_corruption:          return "File appears to be corrupted";
      case KtxReadError::header_missing:           return "KTX header not present; file may have been truncated";
      case KtxReadError::unsupported_endianness:   return "Nonstandard byte orders are not supported";
      case KtxReadError::unsupported_image_format: return "Unsupported image format";
      case KtxReadError::invalid_gl_type_size:     return "glTypeSize does not match expected word size";
      case KtxReadError::invalid_texture_class:    return "Could not determine texture class";
      case KtxReadError::invalid_dimensions:       return "All texture dimensions must be >= 1";
      case KtxReadError::unsupported_dimensions:   return "Texture dimensions too large to load";
      case KtxReadError::unsupported_layer_count:  return "Layer count too large to load";
      case KtxReadError::invalid_face_count:       return "Only planar textures may have multiple faces";
      case KtxReadError::unsupported_face_count:   return "Face count too large to load";
      case KtxReadError::unsupported_level_count:  return "Mipmap level count too large to load";
      case KtxReadError::unnecessary_levels:       return "More mipmap levels specified than necessary";
      case KtxReadError::empty_texture:            return "Texture format and dimensions have zero size";
      case KtxReadError::metadata_missing:         return "Metadata not present; file may have been truncated";
      case KtxReadError::not_enough_texture_data:  return "Calculated texture size is greater than the payload data size";
      case KtxReadError::image_unavailable:        return "The requested layer, face, or mipmap level is not present in the texture";
      case KtxReadError::layered_non_array:        return "Multiple layers specified, but not using an array texture class";
      case KtxReadError::not_enough_faces:         return "Fewer faces specified than expected for this texture class";
      case KtxReadError::too_many_faces:           return "More faces specified than expected for this texture class";
      case KtxReadError::not_enough_memory:        return "Could not allocate enough memory for texture storage";
      default:
         return "An unknown error occurred";
   }
}

} // be::gfx::tex::detail


/* ######################### END OF GENERATED CODE ######################### */

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
S KtxReadErrorCategory::message(int condition) const {
   return read_error_msg(static_cast<KtxReadError>(condition));
}

///////////////////////////////////////////////////////////////////////////////
bool KtxReadErrorCategory::equivalent(int code, const std::error_condition& condition) const noexcept {
   if (condition.category() == std::generic_category() &&
       condition.value() == generic_error_condition(static_cast<KtxReadError>(code))) {
      return true;
   }

   if (condition.category() == texture_file_error_category()) {
      if (condition.value() == static_cast<int>(TextureFileError::fatal_error) && is_fatal(static_cast<KtxReadError>(code))) {
         return true;
      }
      if (condition.value() == texture_file_error_condition(static_cast<KtxReadError>(code))) {
         return true;
      }
   }

   if (condition.category() == ktx_read_error_category() &&
       condition.value() == code) {
      return true;
   }

   return false;
}

///////////////////////////////////////////////////////////////////////////////
const std::error_category& ktx_read_error_category() {
   static KtxReadErrorCategory instance;
   return instance;
}

///////////////////////////////////////////////////////////////////////////////
std::error_code make_error_code(KtxReadError e) {
   return std::error_code(static_cast<int>(e), ktx_read_error_category());
}

///////////////////////////////////////////////////////////////////////////////
std::error_condition make_error_condition(KtxReadError e) {
   return std::error_condition(static_cast<int>(e), ktx_read_error_category());
}

} // be::gfx::tex::detail
