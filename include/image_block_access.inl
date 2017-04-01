#if !defined(BE_GFX_IMAGE_BLOCK_ACCESS_HPP_) && !defined(DOXYGEN)
#include "image_block_access.hpp"
#elif !defined(BE_GFX_IMAGE_BLOCK_ACCESS_INL_)
#define BE_GFX_IMAGE_BLOCK_ACCESS_INL_

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_block(const ImageView& image, I32 block_coord) {
   T block;
   assert(image);
   assert(sizeof(T) <= image.block_size());
   assert(block_coord >= 0);
   assert(block_coord < image.dim_blocks().x);
   const UC* ptr = image.data() +
      block_coord * image.block_size();
   std::memcpy(&block, ptr, sizeof(T));
   return block;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_block(const ImageView& image, ivec2 block_coord) {
   T block;
   assert(image);
   assert(sizeof(T) <= image.block_size());
   assert(block_coord.x >= 0);
   assert(block_coord.y >= 0);
   assert(block_coord.x < image.dim_blocks().x);
   assert(block_coord.y < image.dim_blocks().y);
   const UC* ptr = image.data() +
      block_coord.y * image.line_span() +
      block_coord.x * image.block_size();
   std::memcpy(&block, ptr, sizeof(T));
   return block;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_block(const ImageView& image, ivec3 block_coord) {
   T block;
   assert(image);
   assert(sizeof(T) <= image.block_size());
   assert(block_coord.x >= 0);
   assert(block_coord.y >= 0);
   assert(block_coord.z >= 0);
   assert(block_coord.x < image.dim_blocks().x);
   assert(block_coord.y < image.dim_blocks().y);
   assert(block_coord.z < image.dim_blocks().z);
   const UC* ptr = image.data() +
      block_coord.z * image.plane_span() +
      block_coord.y * image.line_span() +
      block_coord.x * image.block_size();
   std::memcpy(&block, ptr, sizeof(T));
   return block;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_block(ImageView& image, I32 block_coord, const T& block) {
   assert(image);
   assert(sizeof(T) <= image.block_size());
   assert(block_coord >= 0);
   assert(block_coord < image.dim_blocks().x);
   UC* ptr = image.data() +
      block_coord * image.block_size();
   std::memcpy(ptr, &block, sizeof(T));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_block(ImageView& image, ivec2 block_coord, const T& block) {
   assert(image);
   assert(sizeof(T) <= image.block_size());
   assert(block_coord.x >= 0);
   assert(block_coord.y >= 0);
   assert(block_coord.x < image.dim_blocks().x);
   assert(block_coord.y < image.dim_blocks().y);
   UC* ptr = image.data() +
      block_coord.y * image.line_span() +
      block_coord.x * image.block_size();
   std::memcpy(ptr, &block, sizeof(T));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_block(ImageView& image, ivec3 block_coord, const T& block) {
   assert(image);
   assert(sizeof(T) <= image.block_size());
   assert(block_coord.x >= 0);
   assert(block_coord.y >= 0);
   assert(block_coord.z >= 0);
   assert(block_coord.x < image.dim_blocks().x);
   assert(block_coord.y < image.dim_blocks().y);
   assert(block_coord.z < image.dim_blocks().z);
   UC* ptr = image.data() +
      block_coord.z * image.plane_span() +
      block_coord.y * image.line_span() +
      block_coord.x * image.block_size();
   std::memcpy(ptr, &block, sizeof(T));
}

} // be::gfx

#endif
