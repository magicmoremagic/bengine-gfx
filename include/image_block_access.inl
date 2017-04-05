#if !defined(BE_GFX_IMAGE_BLOCK_ACCESS_HPP_) && !defined(DOXYGEN)
#include "image_block_access.hpp"
#elif !defined(BE_GFX_IMAGE_BLOCK_ACCESS_INL_)
#define BE_GFX_IMAGE_BLOCK_ACCESS_INL_

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, glm::length_t Dimension = t::vector_components<Coord>::value>
struct BlockOffset { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct BlockOffset<ImageView, Coord, 1> {
   static std::size_t offset(const ImageView& image, Coord block_coord) {
      assert(image);
      assert((I32)block_coord >= 0);
      assert((I32)block_coord < image.dim_blocks().x);
      return (std::size_t)block_coord * image.block_size();
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct BlockOffset<ImageView, Coord, 2> {
   static std::size_t offset(const ImageView& image, Coord block_coord) {
      assert(image);
      assert((I32)block_coord.x >= 0);
      assert((I32)block_coord.y >= 0);
      assert((I32)block_coord.x < image.dim_blocks().x);
      assert((I32)block_coord.y < image.dim_blocks().y);
      return (std::size_t)block_coord.y * image.line_span() +
         (std::size_t)block_coord.x * image.block_size();
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct BlockOffset<ImageView, Coord, 3> {
   static std::size_t offset(const ImageView& image, Coord block_coord) {
      assert(image);
      assert((I32)block_coord.x >= 0);
      assert((I32)block_coord.y >= 0);
      assert((I32)block_coord.z >= 0);
      assert((I32)block_coord.x < image.dim_blocks().x);
      assert((I32)block_coord.y < image.dim_blocks().y);
      assert((I32)block_coord.z < image.dim_blocks().z);
      return (std::size_t)block_coord.z * image.plane_span() +
         (std::size_t)block_coord.y * image.line_span() +
         (std::size_t)block_coord.x * image.block_size();
   }
};

} // be::gfx::detail

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
std::size_t block_offset(const ImageView& image, Coord block_coord) {
   return detail::BlockOffset<ImageView, Coord>::offset(image, block_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
T get_block(const ImageView& image, Coord block_coord) {
   T block;
   assert(sizeof(T) <= image.block_size());
   std::memcpy(&block, image.data() + block_offset<Coord, ImageView>(image, block_coord), sizeof(T));
   return block;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename Coord, typename ImageView>
void put_block(ImageView& image, Coord block_coord, const T& block) {
   assert(sizeof(T) <= image.block_size());
   std::memcpy(image.data() + block_offset<Coord, ImageView>(image, block_coord), &block, sizeof(T));
}

} // be::gfx

#endif
