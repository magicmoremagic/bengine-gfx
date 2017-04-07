#if !defined(BE_GFX_MAKE_IMAGE_HPP_) && !defined(DOXYGEN)
#include "make_image.hpp"
#elif !defined(BE_GFX_MAKE_IMAGE_INL_)
#define BE_GFX_MAKE_IMAGE_INL_

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, glm::length_t Dimension = t::vector_components<Coord>::value>
struct CoordToVec3 { };

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
struct CoordToVec3<Coord, 1> {
   static ivec3 convert(Coord coord) {
      return ivec3((ivec3::value_type)coord, 0, 0);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
struct CoordToVec3<Coord, 2> {
   static ivec3 convert(Coord coord) {
      return ivec3(ivec2(coord), 0);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
struct CoordToVec3<Coord, 3> {
   static ivec3 convert(Coord coord) {
      return ivec3(coord);
   }
};

} // be::gfx::detail

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
Image make_image(const ImageFormat& format, Coord dim, Buf<UC> buf, TextureAlignment alignment) {
   Image img;

   ivec3 dim3 = detail::CoordToVec3<Coord>::convert(dim);

   if (buf) {
      img.data = std::make_unique<TextureStorage>(1, 1, 1, dim3, format.block_dim(), format.block_size(), std::move(buf), alignment);
   } else {
      img.data = std::make_unique<TextureStorage>(1, 1, 1, dim3, format.block_dim(), format.block_size(), alignment);
   }

   img.view = ImageView(format, *img.data, 0, 0, 0);

   return img;
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord>
std::size_t calculate_required_image_size(const ImageFormat& format, Coord dim, TextureAlignment alignment) {
   ivec3 dim3 = detail::CoordToVec3<Coord>::convert(dim);
   return calculate_required_texture_storage(1, 1, 1, dim3, format.block_dim(), format.block_size(), alignment);
}

} // be::gfx

#endif
