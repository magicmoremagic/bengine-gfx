#include "pch.hpp"
#include "make_image.hpp"
#include <glm/vec2.hpp>
#include <glm/gtc/vec1.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
Image make_image(const ImageFormat& format, I32 dim, Buf<UC> buf) {
   return make_image(format, ivec3(dim, 1, 1), std::move(buf));
}

///////////////////////////////////////////////////////////////////////////////
Image make_image(const ImageFormat& format, ivec1 dim, Buf<UC> buf) {
   return make_image(format, ivec3(dim.x, 1, 1), std::move(buf));
}

///////////////////////////////////////////////////////////////////////////////
Image make_image(const ImageFormat& format, ivec2 dim, Buf<UC> buf) {
   return make_image(format, ivec3(dim, 1), std::move(buf));
}

///////////////////////////////////////////////////////////////////////////////
Image make_image(const ImageFormat& format, ivec3 dim, Buf<UC> buf) {
   Image img;

   if (buf) {
      img.data = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), format.block_size(), std::move(buf));
   } else {
      img.data = std::make_unique<TextureStorage>(1, 1, 1, dim, format.block_dim(), format.block_size());
   }

   img.view = ImageView(format, *img.data, 0, 0, 0);

   return img;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_image_size(const ImageFormat& format, I32 dim) {
   return calculate_required_image_size(format, ivec3(dim, 1, 1));
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_image_size(const ImageFormat& format, ivec1 dim) {
   return calculate_required_image_size(format, ivec3(dim.x, 1, 1));
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_image_size(const ImageFormat& format, ivec2 dim) {
   return calculate_required_image_size(format, ivec3(dim, 1));
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_image_size(const ImageFormat& format, ivec3 dim) {
   return calculate_required_texture_storage(1, 1, 1, dim, format.block_dim(), format.block_size());
}

} // be::gfx
