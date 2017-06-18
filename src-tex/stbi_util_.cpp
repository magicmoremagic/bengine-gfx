#include "pch.hpp"
#include "stbi_util_.hpp"
#include <be/core/glm.hpp>
#include <glm/vector_relational.hpp>

namespace be::gfx::tex::stbi::detail {
namespace {

///////////////////////////////////////////////////////////////////////////////
void stbi_deleter(void* ptr, std::size_t size) {
   stbi_image_free(ptr);
}

///////////////////////////////////////////////////////////////////////////////
void get_stbi_texture_file_info(int w, int h, int components, int bpc, TextureFileInfo& info, TextureFileReadError& err) {
   info.dim = ivec3(w, h, 1);
   info.faces = 1;
   info.layers = 1;
   info.levels = 1;
   info.tex_class = TextureClass::planar;

   if (bpc == 8) {
      switch (components) {
         case 1: info.format = ImageFormat(1, 1, BlockPacking::s_8, 1, component_types(ComponentType::unorm, 1), swizzles_rrr(), Colorspace::unknown, false); break;
         case 2: info.format = ImageFormat(2, 1, BlockPacking::s_8_8, 2, component_types(ComponentType::unorm, 2), swizzles(Swizzle::red, Swizzle::red, Swizzle::red, Swizzle::green), Colorspace::unknown, false); break;
         case 3: info.format = ImageFormat(3, 1, BlockPacking::s_8_8_8, 3, component_types(ComponentType::unorm, 3), swizzles_rgb(), Colorspace::unknown, false); break;
         case 4: info.format = ImageFormat(4, 1, BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::unknown, false); break;
         default:
            err = TextureFileReadError::unsupported_texture;
            break;
      }
   } else if (bpc == 16) {
      switch (components) {
         case 1: info.format = ImageFormat(2, 1, BlockPacking::s_16, 1, component_types(ComponentType::unorm, 1), swizzles_rrr(), Colorspace::unknown, false); break;
         case 2: info.format = ImageFormat(4, 1, BlockPacking::s_16_16, 2, component_types(ComponentType::unorm, 2), swizzles(Swizzle::red, Swizzle::red, Swizzle::red, Swizzle::green), Colorspace::unknown, false); break;
         case 3: info.format = ImageFormat(6, 1, BlockPacking::s_16_16_16, 3, component_types(ComponentType::unorm, 3), swizzles_rgb(), Colorspace::unknown, false); break;
         case 4: info.format = ImageFormat(8, 1, BlockPacking::s_16_16_16_16, 4, component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::unknown, false); break;
         default:
            err = TextureFileReadError::unsupported_texture;
            break;
      }
   } else if (bpc == 32) {
      switch (components) {
         case 1: info.format = ImageFormat(4, 1, BlockPacking::s_32, 1, component_types(ComponentType::sfloat, 1), swizzles_rrr(), Colorspace::linear_other, false); break;
         case 2: info.format = ImageFormat(8, 1, BlockPacking::s_32_32, 2, component_types(ComponentType::sfloat, 2), swizzles(Swizzle::red, Swizzle::red, Swizzle::red, Swizzle::green), Colorspace::linear_other, false); break;
         case 3: info.format = ImageFormat(12, 1, BlockPacking::s_32_32_32, 3, component_types(ComponentType::sfloat, 3), swizzles_rgb(), Colorspace::linear_other, false); break;
         case 4: info.format = ImageFormat(16, 1, BlockPacking::s_32_32_32_32, 4, component_types(ComponentType::sfloat, 4), swizzles_rgba(), Colorspace::linear_other, false); break;
         default:
            err = TextureFileReadError::unsupported_texture;
            break;
      }
   } else {
      err = TextureFileReadError::unsupported_texture;
   }

   if (err == TextureFileReadError::none) {
      if (glm::any(glm::lessThanEqual(info.dim, ivec3()))) {
         err = TextureFileReadError::file_corruption;
      } else if (glm::any(glm::greaterThan(info.dim, ivec3(TextureStorage::max_dim)))) {
         err = TextureFileReadError::unsupported_texture_size;
      } else {
         std::size_t texture_size = calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim,
                                                                       info.format.block_dim(), info.format.block_size(),
                                                                       TextureAlignment(0, 0, 0, 0, 0));
         if (texture_size == 0) {
            err = TextureFileReadError::unsupported_texture_size;
         }
      }
   }
}

} // be::gfx::tex::stbi::detail::()

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_stbi_info(const Buf<const UC>& buf, TextureFileFormat format, be_stbi_info_func info_func) {
   std::pair<TextureFileInfo, TextureFileReadError> result;
   result.first.file_format = format;
   result.second = TextureFileReadError::none;

   if (buf.size() > std::numeric_limits<int>::max()) {
      result.second = TextureFileReadError::unsupported_texture_size;
   } else {
      int w, h, components, bpc;
      if (0 == info_func(buf.get(), (int)buf.size(), &w, &h, &components, &bpc)) {
         result.second = TextureFileReadError::unsupported_texture;
      } else {
         get_stbi_texture_file_info(w, h, components, bpc, result.first, result.second);
      }
   }
   return result;
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_stbi_texture(const Buf<const UC>& buf, be_stbi_load_func load_func) {
   std::pair<Texture, TextureFileReadError> result;
   result.second = TextureFileReadError::none;

   if (buf.size() > std::numeric_limits<int>::max()) {
      result.second = TextureFileReadError::unsupported_texture_size;
   } else {
      int w, h, components, bpc;
      auto stbi_image_data = load_func(buf.get(), (int)buf.size(), &w, &h, &components, &bpc);
      if (stbi_image_data) {
         TextureFileInfo info;
         get_stbi_texture_file_info(w, h, components, bpc, info, result.second);

         std::size_t size = calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim,
                                            info.format.block_dim(), info.format.block_size(),
                                            TextureAlignment(0, 0, 0, 0, 0));

         Buf<UC> data((UC*)stbi_image_data, size, stbi_deleter);
         
         if (result.second == TextureFileReadError::none) {
            result.first.storage = std::make_unique<TextureStorage>(info.layers, info.faces, info.levels, info.dim, info.format.block_dim(), info.format.block_size(), std::move(data), TextureAlignment(0, 0, 0, 0, 0));
            result.first.view = TextureView(info.format, info.tex_class, *result.first.storage, 0, info.layers, 0, info.faces, 0, info.levels);
         }
      } else {
         result.second = TextureFileReadError::unsupported_texture;
      }
   }

   return result;
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_stbi_image(const Buf<const UC>& buf, be_stbi_load_func load_func) {
   std::pair<Image, TextureFileReadError> result;
   result.second = TextureFileReadError::none;

   if (buf.size() > std::numeric_limits<int>::max()) {
      result.second = TextureFileReadError::unsupported_texture_size;
   } else {
      int w, h, components, bpc;
      auto stbi_image_data = load_func(buf.get(), (int)buf.size(), &w, &h, &components, &bpc);
      if (stbi_image_data) {
         TextureFileInfo info;
         get_stbi_texture_file_info(w, h, components, bpc, info, result.second);

         std::size_t size = calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim,
                                                               info.format.block_dim(), info.format.block_size(),
                                                               TextureAlignment(0, 0, 0, 0, 0));

         Buf<UC> data((UC*)stbi_image_data, size, stbi_deleter);

         if (result.second == TextureFileReadError::none) {
            result.first.storage = std::make_unique<TextureStorage>(info.layers, info.faces, info.levels, info.dim, info.format.block_dim(), info.format.block_size(), std::move(data), TextureAlignment(0, 0, 0, 0, 0));
            result.first.view = ImageView(info.format, *result.first.storage, 0, 0, 0);
         }
      } else {
         result.second = TextureFileReadError::unsupported_texture;
      }
   }

   return result;
}

} // be::gfx::tex::detail
