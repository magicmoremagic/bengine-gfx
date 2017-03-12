#pragma once
#ifndef BE_GFX_TEXTURE_STORAGE_HPP_
#define BE_GFX_TEXTURE_STORAGE_HPP_

#include "image_format.hpp"
#include <be/core/buf.hpp>
#include <glm/vec2.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
class TextureStorage final {
public:
   static TextureStorage nil;

   using alignment_type = U8;

   using layer_index_type = U16;
   using face_index_type = U8;
   using level_index_type = U8;
   using block_size_type = typename ImageFormat::block_size_type;
   using block_dim_type = typename ImageFormat::block_dim_type;

   static constexpr std::size_t max_layers = std::size_t(layer_index_type(-1)) + 1u;
   static constexpr std::size_t max_faces = std::size_t(face_index_type(-1)) + 1u;
   static constexpr std::size_t max_levels = 16;
   static constexpr std::size_t max_dim = 1 << (max_levels - 1);
   static constexpr std::size_t max_block_size = ImageFormat::max_block_size;
   static constexpr std::size_t max_block_dim = ImageFormat::max_block_dim;

   TextureStorage();
   TextureStorage(std::size_t layers,
                  std::size_t faces,
                  std::size_t levels,
                  ivec3 base_dim,
                  block_dim_type block_dim,
                  block_size_type block_size,
                  alignment_type line_alignment = 8u,
                  alignment_type plane_alignment = 0u,
                  alignment_type level_alignment = 0u,
                  alignment_type face_alignment = 0u,
                  alignment_type layer_alignment = 0u);
   TextureStorage(std::size_t layers,
                  std::size_t faces,
                  std::size_t levels,
                  ivec3 base_dim,
                  block_dim_type block_dim,
                  block_size_type block_size,
                  Buf<UC> data,
                  alignment_type line_alignment = 8u,
                  alignment_type plane_alignment = 0u,
                  alignment_type level_alignment = 0u,
                  alignment_type face_alignment = 0u,
                  alignment_type layer_alignment = 0u);

   explicit operator bool() const; ///< Returns true if 0 < size()
   bool empty() const; ///< Returns true if 0 == size()

   std::size_t size() const; ///< The total size of the storage required for the texture, in bytes
   UC* data(); ///< A pointer to the beginning of the texture data.
   const UC* data() const; ///< A pointer to the beginning of the (const) texture data.
   
   explicit operator Buf<UC>(); ///< Constructs a non-owning Buf holding this texture storage's data.
   explicit operator Buf<const UC>() const; ///< Constructs a non-owning Buf holding this texture storage's const data.

   std::size_t layers() const; ///< The number of texture array layers.  0 for an empty TextureStorage, and at least 1 for any other case.
   std::size_t faces() const; ///< The number of faces.  0 for an empty TextureStorage, at least 1 for cubemap textures, and exactly 1 in any other case.
   std::size_t levels() const; ///< The number of mipmapping levels.  0 for an empty TextureStorage, and at least 1 for any other case.  This may be less than the value specified in the constructor if the dimensions are too small.
   block_size_type block_size() const; ///< The displacement in bytes between a block and the next one in the x direction.  Equivalent to block_size().
   std::size_t line_span(std::size_t level) const; ///< The displacement in bytes between a block and the next one in the y direction.
   std::size_t plane_span(std::size_t level) const; ///< The displacement in bytes between a block and the next one in the z direction.
   std::size_t level_offset(std::size_t level) const;
   std::size_t face_span() const; ///< The displacement in bytes between the first block of one face and the first block of the next face.
   std::size_t layer_span() const; ///< The displacement in bytes between the first block of the first face of one layer and the first block of the first face of the next layer.

   block_dim_type block_dim() const; ///< The dimensions of a single block, in pixels.
   ivec3 dim(std::size_t level) const; ///< The dimensions of a single face image at the specified mipmapping level.
   ivec3 dim_blocks(std::size_t level) const; ///< The dimensions of the block array covering a single face image at the specified mipmapping level.

   alignment_type line_alignment() const;
   alignment_type plane_alignment() const;
   alignment_type level_alignment() const;
   alignment_type face_alignment() const;
   alignment_type layer_alignment() const;

   bool operator==(const TextureStorage& other) const;
   bool operator!=(const TextureStorage& other) const;

private:
   void init_(std::size_t levels, ivec3 dim);
   std::size_t hash_() const;
   friend std::size_t std_hash(const TextureStorage& s) { return s.hash_(); };

   const layer_index_type layers_;
   const face_index_type faces_;
   level_index_type levels_;
   const block_size_type block_size_;
   const block_dim_type block_dim_;
   std::size_t face_span_;
   std::size_t layer_span_;
   std::size_t size_;
   Buf<UC> data_;
   std::array<ivec3, max_levels> dim_;
   std::array<ivec3, max_levels> dim_blocks_;
   std::array<uvec2, max_levels> line_plane_span_;
   std::array<std::size_t, max_levels> level_offset_;
   alignment_type line_alignment_;
   alignment_type plane_alignment_;
   alignment_type level_alignment_;
   alignment_type face_alignment_;
   alignment_type layer_alignment_;
};

std::size_t calculate_required_texture_storage(std::size_t layers,
                                               std::size_t faces,
                                               std::size_t levels,
                                               ivec3 base_dim,
                                               TextureStorage::block_dim_type block_dim,
                                               TextureStorage::block_size_type block_size,
                                               TextureStorage::alignment_type line_alignment = 8u,
                                               TextureStorage::alignment_type plane_alignment = 0u,
                                               TextureStorage::alignment_type level_alignment = 0u,
                                               TextureStorage::alignment_type face_alignment = 0u,
                                               TextureStorage::alignment_type layer_alignment = 0u);

} // be::gfx

#endif
