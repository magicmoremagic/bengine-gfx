#if !defined(BE_GFX_TEX_PIXEL_ACCESS_HPP_) && !defined(DOXYGEN)
#include "pixel_access.hpp"
#elif !defined(BE_GFX_TEX_PIXEL_ACCESS_INL_)
#define BE_GFX_TEX_PIXEL_ACCESS_INL_

namespace be::gfx::tex {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, typename Dimension = DimensionTag<t::vector_components<Coord>::value>>
struct PixelOffset { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, typename Dimension>
struct PixelOffset<ImageView, Coord, true, Dimension> : BlockOffset<ImageView, Coord, Dimension::value> { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelOffset<ImageView, Coord, false, DimensionTag<1>> {
   static std::size_t offset(const ImageView& image, Coord pixel_coord) {
      Coord block_dim = Coord(image.block_dim().x);
      Coord block_coord = pixel_coord / block_dim;
      pixel_coord -= block_coord * block_dim;
      assert((I32)block_coord >= 0);
      assert((I32)block_coord < image.dim_blocks().x);
      assert((I32)pixel_coord >= 0);
      return (std::size_t)block_coord * image.block_span() +
         (std::size_t)pixel_coord * block_pixel_size(image.format().packing());
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelOffset<ImageView, Coord, false, DimensionTag<2>> {
   static std::size_t offset(const ImageView& image, Coord pixel_coord) {
      Coord block_dim = Coord(image.block_dim());
      Coord block_coord = pixel_coord / block_dim;
      pixel_coord -= block_coord * block_dim;
      assert((I32)block_coord.x >= 0);
      assert((I32)block_coord.y >= 0);
      assert((I32)block_coord.x < image.dim_blocks().x);
      assert((I32)block_coord.y < image.dim_blocks().y);
      assert((I32)pixel_coord.x >= 0);
      assert((I32)pixel_coord.y >= 0);
      return (std::size_t)block_coord.y * image.line_span() +
         (std::size_t)block_coord.x * image.block_span() +
         (std::size_t)(pixel_coord.y * block_dim.x + pixel_coord.x) *
         block_pixel_size(image.format().packing());
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelOffset<ImageView, Coord, false, DimensionTag<3>> {
   static std::size_t offset(const ImageView& image, Coord pixel_coord) {
      Coord block_dim = Coord(image.block_dim());
      Coord block_coord = pixel_coord / block_dim;
      pixel_coord -= block_coord * block_dim;
      assert((I32)block_coord.x >= 0);
      assert((I32)block_coord.y >= 0);
      assert((I32)block_coord.z >= 0);
      assert((I32)block_coord.x < image.dim_blocks().x);
      assert((I32)block_coord.y < image.dim_blocks().y);
      assert((I32)block_coord.z < image.dim_blocks().z);
      assert((I32)pixel_coord.x >= 0);
      assert((I32)pixel_coord.y >= 0);
      assert((I32)pixel_coord.z >= 0);
      return (std::size_t)block_coord.z * image.plane_span() +
         (std::size_t)block_coord.y * image.line_span() +
         (std::size_t)block_coord.x * image.block_span() +
         (std::size_t)((pixel_coord.z * block_dim.y + pixel_coord.y) * block_dim.x + pixel_coord.x) *
         block_pixel_size(image.format().packing());
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView, bool IsSimple>
T get_pixel_uncompressed(const ImageView& image, Coord coord) {
   T pixel;
   const void* ptr = image.data() + PixelOffset<ImageView, Coord, IsSimple>::offset(image, coord);
   std::memcpy(&pixel, ptr, sizeof(T));
   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView, bool IsSimple>
void put_pixel_uncompressed(ImageView& image, Coord coord, T pixel) {
   void* ptr = image.data() + PixelOffset<ImageView, Coord, IsSimple>::offset(image, coord);
   std::memcpy(ptr, &pixel, sizeof(T));
}

} // be::gfx::tex::detail

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
PixelOffsetFunc<Coord, ImageView> pixel_offset_func(const ImageView& image) {
   using dim_type = glm::vec<t::vector_components<Coord>::value, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      return detail::PixelOffset<ImageView, Coord, true>::offset;
   } else {
      return detail::PixelOffset<ImageView, Coord, false>::offset;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
std::size_t pixel_offset(const ImageView& image, Coord pixel_coord) {
   return pixel_offset_func<Coord>(image)(image, coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
GetPixelFunc<T, Coord, ImageView> get_pixel_func(const ImageView& image) {
   using dim_type = glm::vec<t::vector_components<Coord>::value, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   assert(sizeof(T) <= block_pixel_size(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      return detail::get_pixel_uncompressed<T, Coord, ImageView, true>;
   } else {
      return detail::get_pixel_uncompressed<T, Coord, ImageView, false>;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
T get_pixel(const ImageView& image, Coord pixel_coord) {
   return get_pixel_func<T, Coord, ImageView>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
PutPixelFunc<T, Coord, ImageView> put_pixel_func(const ImageView& image) {
   using dim_type = glm::vec<t::vector_components<Coord>::value, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   assert(sizeof(T) <= block_pixel_size(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      return detail::put_pixel_uncompressed<T, Coord, ImageView, true>;
   } else {
      return detail::put_pixel_uncompressed<T, Coord, ImageView, false>;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
void put_pixel(ImageView& image, Coord pixel_coord, T pixel) {
   put_pixel_func<T, Coord, ImageView>(image)(image, pixel_coord, pixel);
}

} // be::gfx::tex

#endif
