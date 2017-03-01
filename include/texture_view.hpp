#pragma once
#ifndef BE_GFX_TEXTURE_VIEW_HPP_
#define BE_GFX_TEXTURE_VIEW_HPP_

#include "image_format.hpp"

namespace be::gfx {

class TextureStorage;

class TextureView final {
public:
   

   TextureView();
   

   TextureStorage& storage();
   const TextureStorage& storage() const;

   explicit operator bool() const; ///< Returns true if 0 < storage().size()
   bool empty() const; ///< Returns true if 0 == storage().size()

   std::size_t size() const; ///< The total size of the storage required for the texture, in bytes
   UC* data(); ///< A pointer to the beginning of the texture data.
   const UC* data() const; ///< A pointer to the beginning of the (const) texture data.

   std::size_t layers() const; ///< The number of texture array layers.  0 for an empty TextureStorage, and at least 1 for any other case.
   std::size_t faces() const; ///< The number of faces.  0 for an empty TextureStorage, at least 1 for cubemap textures, and exactly 1 in any other case.
   std::size_t levels() const; ///< The number of mipmapping levels.  0 for an empty TextureStorage, and at least 1 for any other case.  This may be less than the value specified in the constructor if the dimensions are too small.
   std::size_t block_size() const; ///< The displacement in bytes between a block and the next one in the x direction.  Equivalent to block_size().
   std::size_t line_span(std::size_t level) const; ///< The displacement in bytes between a block and the next one in the y direction.
   std::size_t plane_span(std::size_t level) const; ///< The displacement in bytes between a block and the next one in the z direction.
   std::size_t face_span() const; ///< The displacement in bytes between the first block of one face and the first block of the next face.
   std::size_t layer_span() const; ///< The displacement in bytes between the first block of the first face of one layer and the first block of the first face of the next layer.

   const ivec3& block_dim() const; ///< The dimensions of a single block, in pixels.
   const ivec3& dim(std::size_t level) const; ///< The dimensions of a single face image at the specified mipmapping level.
   const ivec3& dim_blocks(std::size_t level) const; ///< The dimensions of the block array covering a single face image at the specified mipmapping level.

private:
   TextureStorage* storage_;
};

} // be::gfx

#endif
