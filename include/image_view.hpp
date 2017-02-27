#pragma once
#ifndef BE_GFX_IMAGE_VIEW_HPP_
#define BE_GFX_IMAGE_VIEW_HPP_

#include "image_format.hpp"

namespace be::gfx {

class TextureStorage;

class ImageView final {
public:


   ImageView();


   TextureStorage& storage();
   const TextureStorage& storage() const;

   explicit operator bool() const; ///< Returns true if 0 < storage().size()
   bool empty() const; ///< Returns true if 0 == storage().size()

   std::size_t size() const; ///< The total size of the storage required for the image, in bytes
   UC* data(); ///< A pointer to the beginning of the image data.
   const UC* data() const; ///< A pointer to the beginning of the (const) image data.

   std::size_t block_size() const; ///< The displacement in bytes between a block and the next one in the x direction.  Equivalent to block_size().
   std::size_t line_span() const; ///< The displacement in bytes between a block and the next one in the y direction.
   std::size_t plane_span() const; ///< The displacement in bytes between a block and the next one in the z direction.

   const ivec3& block_dim() const; ///< The dimensions of a single block, in pixels.
   const ivec3& dim() const; ///< The dimensions of a single face image at the specified mipmapping level.
   const ivec3& dim_blocks() const; ///< The dimensions of the block array covering a single face image at the specified mipmapping level.

private:
   TextureStorage* storage;
};

} // be::gfx

#endif
