#include "pch.hpp"
#include "stbi_util_.hpp"
#include "tex/texture_file_error.hpp"
#include <be/core/glm.hpp>
#include <glm/vector_relational.hpp>

namespace be::gfx::tex::detail {
namespace {

///////////////////////////////////////////////////////////////////////////////
void stbi_deleter(void* ptr, std::size_t size) noexcept {
   stbi_image_free(ptr);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t get_stbi_texture_file_info(int w, int h, int components, int bpc, TextureFileInfo& info, std::error_code& ec) noexcept {
   std::size_t texture_size = 0;

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
            ec = make_error_code(TextureFileError::unsupported);
            break;
      }
   } else if (bpc == 16) {
      switch (components) {
         case 1: info.format = ImageFormat(2, 1, BlockPacking::s_16, 1, component_types(ComponentType::unorm, 1), swizzles_rrr(), Colorspace::unknown, false); break;
         case 2: info.format = ImageFormat(4, 1, BlockPacking::s_16_16, 2, component_types(ComponentType::unorm, 2), swizzles(Swizzle::red, Swizzle::red, Swizzle::red, Swizzle::green), Colorspace::unknown, false); break;
         case 3: info.format = ImageFormat(6, 1, BlockPacking::s_16_16_16, 3, component_types(ComponentType::unorm, 3), swizzles_rgb(), Colorspace::unknown, false); break;
         case 4: info.format = ImageFormat(8, 1, BlockPacking::s_16_16_16_16, 4, component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::unknown, false); break;
         default:
            ec = make_error_code(TextureFileError::unsupported);
            break;
      }
   } else if (bpc == 32) {
      switch (components) {
         case 1: info.format = ImageFormat(4, 1, BlockPacking::s_32, 1, component_types(ComponentType::sfloat, 1), swizzles_rrr(), Colorspace::linear_other, false); break;
         case 2: info.format = ImageFormat(8, 1, BlockPacking::s_32_32, 2, component_types(ComponentType::sfloat, 2), swizzles(Swizzle::red, Swizzle::red, Swizzle::red, Swizzle::green), Colorspace::linear_other, false); break;
         case 3: info.format = ImageFormat(12, 1, BlockPacking::s_32_32_32, 3, component_types(ComponentType::sfloat, 3), swizzles_rgb(), Colorspace::linear_other, false); break;
         case 4: info.format = ImageFormat(16, 1, BlockPacking::s_32_32_32_32, 4, component_types(ComponentType::sfloat, 4), swizzles_rgba(), Colorspace::linear_other, false); break;
         default:
            ec = make_error_code(TextureFileError::unsupported);
            break;
      }
   } else {
      ec = make_error_code(TextureFileError::unsupported);
   }

   if (!ec) {
      if (glm::any(glm::lessThanEqual(info.dim, ivec3()))) {
         ec = make_error_code(TextureFileError::unsupported);
      } else if (glm::any(glm::greaterThan(info.dim, ivec3(TextureStorage::max_dim)))) {
         ec = make_error_code(TextureFileError::unsupported);
      } else {
         std::error_code ec2;
         texture_size = calculate_required_texture_storage(info.layers, info.faces, info.levels, info.dim,
                                                           info.format.block_dim(), info.format.block_size(), ec2,
                                                           TextureAlignment(0, 0, 0, 0, 0));
         if (texture_size == 0 || ec2) {
            ec = make_error_code(TextureFileError::unsupported);
         }
      }
   }

   return texture_size;
}

} // be::gfx::tex::detail::()

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, std::size_t> read_stbi_info(const Buf<const UC>& buf, TextureFileFormat format, be_stbi_info_func info_func, std::error_code& ec) noexcept {
   std::pair<TextureFileInfo, std::size_t> result;
   result.first.file_format = format;
   result.second = 0;

   if (buf.size() > std::numeric_limits<int>::max()) {
      ec = make_error_code(TextureFileError::unsupported);
   } else {
      int w, h, components, bpc;
      if (0 == info_func(buf.get(), (int)buf.size(), &w, &h, &components, &bpc)) {
         ec = make_error_code(TextureFileError::unsupported);
      } else {
         result.second = get_stbi_texture_file_info(w, h, components, bpc, result.first, ec);
      }
   }
   return result;
}

///////////////////////////////////////////////////////////////////////////////
Texture read_stbi_texture(const Buf<const UC>& buf, const TextureFileInfo& info, std::size_t texture_size, be_stbi_load_func load_func, std::error_code& ec) noexcept {
   Texture tex;

   if (buf.size() > std::numeric_limits<int>::max()) {
      ec = make_error_code(TextureFileError::unsupported);
   } else {
      int w, h, components, bpc;
      auto stbi_image_data = load_func(buf.get(), (int)buf.size(), &w, &h, &components, &bpc);
      if (stbi_image_data) {
         Buf<UC> data((UC*)stbi_image_data, texture_size, stbi_deleter);
         
         if (!ec) {
            tex.storage = std::make_unique<TextureStorage>(info.layers, info.faces, info.levels, info.dim, info.format.block_dim(), info.format.block_size(), std::move(data), TextureAlignment(0, 0, 0, 0, 0));
            tex.view = tex::TextureView(info.format, info.tex_class, *tex.storage, 0, info.layers, 0, info.faces, 0, info.levels);
         }
      } else {
         ec = make_error_code(TextureFileError::unsupported);
      }
   }

   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image read_stbi_image(const Buf<const UC>& buf, const TextureFileInfo& info, std::size_t texture_size, be_stbi_load_func load_func, std::error_code& ec) noexcept {
   Image img;

   if (buf.size() > std::numeric_limits<int>::max()) {
      ec = make_error_code(TextureFileError::unsupported);
   } else {
      int w, h, components, bpc;
      auto stbi_image_data = load_func(buf.get(), (int)buf.size(), &w, &h, &components, &bpc);
      if (stbi_image_data) {
         Buf<UC> data((UC*)stbi_image_data, texture_size, stbi_deleter);

         if (!ec) {
            img.storage = std::make_unique<TextureStorage>(info.layers, info.faces, info.levels, info.dim, info.format.block_dim(), info.format.block_size(), std::move(data), TextureAlignment(0, 0, 0, 0, 0));
            img.view = tex::ImageView(info.format, *img.storage, 0, 0, 0);
         }
      } else {
         ec = make_error_code(TextureFileError::unsupported);
      }
   }

   return img;
}

} // be::gfx::tex::detail
