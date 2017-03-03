#pragma once
#ifndef BE_GFX_IMAGE_VIEW_HPP_
#define BE_GFX_IMAGE_VIEW_HPP_

#include "image_format.hpp"
#include "texture_storage.hpp"

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
class ImageView final {
public:
   using layer_index_type = typename TextureStorage::layer_index_type;
   using face_index_type = typename TextureStorage::face_index_type;
   using level_index_type = typename TextureStorage::level_index_type;
   using block_size_type = typename ImageFormat::block_size_type;
   using block_dim_type = typename ImageFormat::block_dim_type;

   ImageView();
   ImageView(const ImageFormat& format, TextureStorage& storage, std::size_t layer, std::size_t face, std::size_t level);
   ImageView(const ImageFormat& format, ImageView& other);

   operator ImageView<const TextureStorage, const UC>() const;

   TextureStorage& storage();
   const TextureStorage& storage() const;

   const ImageFormat& format() const;

   explicit operator bool() const; ///< Returns true if 0 < storage().size()
   bool empty() const; ///< Returns true if 0 == storage().size()

   std::size_t size() const; ///< The total size of the storage required for the image, in bytes
   UC* data(); ///< A pointer to the beginning of the image data.
   const UC* data() const; ///< A pointer to the beginning of the (const) image data.

   explicit operator Buf<UC>(); ///< Constructs a non-owning Buf holding this image's data.
   explicit operator Buf<const UC>() const; ///< Constructs a non-owning Buf holding this image's const data.

   std::size_t layer() const; ///< The layer index of the portion of the texture this view represents.
   std::size_t face() const; ///< The face index of the portion of the texture this view represents.
   std::size_t level() const; ///< The mipmapping level of the portion of the texture this view represents.

   block_size_type block_size() const; ///< The displacement in bytes between a block and the next one in the x direction.  Equivalent to block_size().
   std::size_t line_span() const; ///< The displacement in bytes between a block and the next one in the y direction.
   std::size_t plane_span() const; ///< The displacement in bytes between a block and the next one in the z direction.

   block_dim_type block_dim() const; ///< The dimensions of a single block, in pixels.
   const ivec3& dim() const; ///< The dimensions of a the image, in pixels
   const ivec3& dim_blocks() const; ///< The dimensions of the block array covering the image.

private:
   TextureStorage* storage_;
   ImageFormat format_;
   layer_index_type layer_;
   face_index_type face_;
   level_index_type level_;
   UC* data_;
   std::size_t size_;
};

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorageA, typename UCA, typename TextureStorageB, typename UCB>
bool operator==(const ImageView<TextureStorageA, UCA>& a, const ImageView<TextureStorageB, UCB>& b) {
   return &a.storage() == &b.storage() &&
      a.format() == b.format() &&
      a.layer() == b.layer() &&
      a.face() == b.face() &&
      a.level() == b.level() &&
      a.data() == b.data() &&
      a.size() == b.size();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorageA, typename UCA, typename TextureStorageB, typename UCB>
bool operator!=(const ImageView<TextureStorageA, UCA>& a, const ImageView<TextureStorageB, UCB>& b) {
   return !(a == b);
}

} // be::gfx::detail

using ImageView = detail::ImageView<TextureStorage, UC>;
using ConstImageView = detail::ImageView<const TextureStorage, const UC>;

} // be::gfx

#endif
