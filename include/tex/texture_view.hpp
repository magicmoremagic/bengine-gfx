#pragma once
#ifndef BE_GFX_TEX_TEXTURE_VIEW_HPP_
#define BE_GFX_TEX_TEXTURE_VIEW_HPP_

#include "image_view.hpp"
#include "texture_class.hpp"

namespace be::gfx::tex {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
class TextureView final {
public:
   using texture_storage_type = TextureStorage;
   using image_view_type = ImageView;
   using layer_index_type = typename TextureStorage::layer_index_type;
   using face_index_type = typename TextureStorage::face_index_type;
   using level_index_type = typename TextureStorage::level_index_type;
   using block_size_type = typename ImageFormat::block_size_type;
   using block_dim_type = typename ImageFormat::block_dim_type;

   TextureView();
   TextureView(const ImageFormat& format, TextureClass tex_class, TextureStorage& storage,
               std::size_t base_layer = 0, std::size_t layers = TextureStorage::max_layers,
               std::size_t base_face = 0, std::size_t faces = TextureStorage::max_faces,
               std::size_t base_level = 0, std::size_t levels = TextureStorage::max_levels);
   TextureView(const ImageFormat& format, TextureClass tex_class, TextureView& other);
   
   operator TextureView<const TextureStorage, ConstImageView>() const;

   TextureStorage& storage();
   const TextureStorage& storage() const;

   TextureClass texture_class() const;

   const ImageFormat& format() const;

   explicit operator bool() const; ///< Returns true if 0 < storage().size()
   bool empty() const; ///< Returns true if 0 == storage().size()

   ImageView image(std::size_t layer = 0, std::size_t face = 0, std::size_t level = 0);
   ConstImageView image(std::size_t layer = 0, std::size_t face = 0, std::size_t level = 0) const;

   std::size_t layers() const;
   std::size_t base_layer() const;
   std::size_t max_layer() const;

   std::size_t faces() const; 
   std::size_t base_face() const;
   std::size_t max_face() const;

   std::size_t levels() const;
   std::size_t base_level() const;
   std::size_t max_level() const;

   block_size_type block_size() const;
   std::size_t line_span(std::size_t level) const;
   std::size_t plane_span(std::size_t level) const;
   std::size_t level_offset(std::size_t level) const;
   std::size_t face_span() const;
   std::size_t layer_span() const;

   block_dim_type block_dim() const;
   ivec3 dim(std::size_t level) const;
   ivec3 dim_blocks(std::size_t level) const;

private:
   TextureStorage* storage_;
   ImageFormat format_;
   TextureClass tex_class_;
   layer_index_type base_layer_;
   layer_index_type layers_;
   face_index_type base_face_;
   face_index_type faces_;
   level_index_type base_level_;
   level_index_type levels_;
};

template <typename TextureStorageA, typename ImageViewA, typename TextureStorageB, typename ImageViewB>
bool operator==(const TextureView<TextureStorageA, ImageViewA>& a, const TextureView<TextureStorageB, ImageViewB>& b) {
   return &a.storage() == &b.storage() &&
      a.format() == b.format() &&
      a.texture_class() == b.texture_class() &&
      a.base_layer() == b.base_layer() &&
      a.layers() == b.layers() &&
      a.base_face() == b.base_face() &&
      a.faces() == b.faces() &&
      a.base_level() == b.base_level() &&
      a.levels() == b.levels();
}

template <typename TextureStorageA, typename ImageViewA, typename TextureStorageB, typename ImageViewB>
bool operator!=(const TextureView<TextureStorageA, ImageViewA>& a, const TextureView<TextureStorageB, ImageViewB>& b) {
   return !(a == b);
}

} // be::gfx::tex::detail

using TextureView = detail::TextureView<TextureStorage, ImageView>;
using ConstTextureView = detail::TextureView<const TextureStorage, ConstImageView>;

} // be::gfx::tex

#endif
