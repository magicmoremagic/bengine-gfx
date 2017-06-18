#include "pch.hpp"
#include "tex/make_texture.hpp"
#include "tex/mipmapping.hpp"
#include <be/core/alg.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/vec1.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
Texture make_lineal_texture(const ImageFormat& format, I32 dim, std::size_t levels, Buf<UC> buf, TextureAlignment alignment) {
   return make_texture(TextureClass::lineal, format, ivec3(dim, 1, 1), 1, levels, std::move(buf), alignment);
}

///////////////////////////////////////////////////////////////////////////////
Texture make_lineal_array_texture(const ImageFormat& format, I32 dim, std::size_t layers, std::size_t levels, Buf<UC> buf, TextureAlignment alignment) {
   return make_texture(TextureClass::lineal_array, format, ivec3(dim, 1, 1), layers, levels, std::move(buf), alignment);
}

///////////////////////////////////////////////////////////////////////////////
Texture make_planar_texture(const ImageFormat& format, ivec2 dim, std::size_t levels, Buf<UC> buf, TextureAlignment alignment) {
   return make_texture(TextureClass::planar, format, ivec3(dim, 1), 1, levels, std::move(buf), alignment);
}

///////////////////////////////////////////////////////////////////////////////
Texture make_planar_array_texture(const ImageFormat& format, ivec2 dim, std::size_t layers, std::size_t levels, Buf<UC> buf, TextureAlignment alignment) {
   return make_texture(TextureClass::planar_array, format, ivec3(dim, 1), layers, levels, std::move(buf), alignment);
}

///////////////////////////////////////////////////////////////////////////////
Texture make_volumetric_texture(const ImageFormat& format, ivec3 dim, std::size_t levels, Buf<UC> buf, TextureAlignment alignment) {
   return make_texture(TextureClass::volumetric, format, dim, 1, levels, std::move(buf), alignment);
}

///////////////////////////////////////////////////////////////////////////////
Texture make_directional_texture(const ImageFormat& format, ivec2 dim, std::size_t levels, Buf<UC> buf, TextureAlignment alignment) {
   return make_texture(TextureClass::directional, format, ivec3(dim, 1), 1, levels, std::move(buf), alignment);
}

///////////////////////////////////////////////////////////////////////////////
Texture make_directional_array_texture(const ImageFormat& format, ivec2 dim, std::size_t layers, std::size_t levels, Buf<UC> buf, TextureAlignment alignment) {
   return make_texture(TextureClass::directional_array, format, ivec3(dim, 1), layers, levels, std::move(buf), alignment);
}

///////////////////////////////////////////////////////////////////////////////
Texture make_texture(TextureClass tex_class, const ImageFormat& format, ivec3 dim, std::size_t layers, std::size_t levels, Buf<UC> buf, TextureAlignment alignment) {
   Texture tex;

   if (!is_array(tex_class)) {
      assert(layers == 1);
      layers = 1;
   }

   std::size_t faces = be::gfx::tex::faces(tex_class);

   if (buf) {
      tex.storage = std::make_unique<TextureStorage>(layers, faces, levels, dim, format.block_dim(), format.block_size(), std::move(buf), alignment);
   } else {
      tex.storage = std::make_unique<TextureStorage>(layers, faces, levels, dim, format.block_dim(), format.block_size(), alignment);
   }

   tex.view = TextureView(format, tex_class, *tex.storage, 0, layers, 0, faces, 0, levels);

   return tex;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_lineal_texture_size(const ImageFormat& format, I32 dim, std::size_t levels, TextureAlignment alignment) {
   return calculate_required_texture_size(TextureClass::lineal, format, ivec3(dim, 1, 1), 1, levels, alignment);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_lineal_array_texture_size(const ImageFormat& format, I32 dim, std::size_t layers, std::size_t levels, TextureAlignment alignment) {
   return calculate_required_texture_size(TextureClass::lineal_array, format, ivec3(dim, 1, 1), layers, levels, alignment);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_planar_texture_size(const ImageFormat& format, ivec2 dim, std::size_t levels, TextureAlignment alignment) {
   return calculate_required_texture_size(TextureClass::planar, format, ivec3(dim, 1), 1, levels, alignment);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_planar_array_texture_size(const ImageFormat& format, ivec2 dim, std::size_t layers, std::size_t levels, TextureAlignment alignment) {
   return calculate_required_texture_size(TextureClass::planar_array, format, ivec3(dim, 1), layers, levels, alignment);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_volumetric_texture_size(const ImageFormat& format, ivec3 dim, std::size_t levels, TextureAlignment alignment) {
   return calculate_required_texture_size(TextureClass::volumetric, format, dim, 1, levels, alignment);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_directional_texture_size(const ImageFormat& format, ivec2 dim, std::size_t levels, TextureAlignment alignment) {
   return calculate_required_texture_size(TextureClass::directional, format, ivec3(dim, 1), 1, levels, alignment);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_directional_array_texture_size(const ImageFormat& format, ivec2 dim, std::size_t layers, std::size_t levels, TextureAlignment alignment) {
   return calculate_required_texture_size(TextureClass::directional_array, format, ivec3(dim, 1), layers, levels, alignment);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_texture_size(TextureClass tex_class, const ImageFormat& format, ivec3 dim, std::size_t layers, std::size_t levels, TextureAlignment alignment) {
   if (!is_array(tex_class)) {
      assert(layers == 1);
      layers = 1;
   }

   std::size_t faces = be::gfx::tex::faces(tex_class);

   return calculate_required_texture_storage(layers, faces, levels, dim, format.block_dim(), format.block_size(), alignment);
}

} // be::gfx::tex
