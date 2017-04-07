#include "pch.hpp"
#include "texture_view.hpp"
#include <be/core/alg.hpp>

namespace be::gfx::detail {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
TextureView<TextureStorage, ImageView>::TextureView()
   : storage_(&TextureStorage::nil),
     tex_class_(TextureClass::lineal),
     base_layer_(0),
     layers_(0),
     base_face_(0),
     faces_(0),
     base_level_(0),
     levels_(0) { }

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
TextureView<TextureStorage, ImageView>::TextureView(const ImageFormat& format, TextureClass tex_class, TextureStorage& storage,
                         std::size_t base_layer, std::size_t layers,
                         std::size_t base_face, std::size_t faces,
                         std::size_t base_level, std::size_t levels)
   : storage_(&storage),
     tex_class_(tex_class),
     base_layer_(static_cast<layer_index_type>(base_layer)),
     layers_(is_array(tex_class) ? static_cast<layer_index_type>(min(layers, storage.layers() - base_layer)) : 1u),
     base_face_(static_cast<face_index_type>(base_face)),
     faces_(be::gfx::faces(tex_class) == 1u ? 1u : static_cast<face_index_type>(min(faces, storage.faces() - base_face))),
     base_level_(static_cast<level_index_type>(base_level)),
     levels_(static_cast<level_index_type>(min(levels, storage.levels() - base_level))) {
   assert(is_valid(tex_class));
   assert(base_layer < storage.layers());
   assert(base_face < storage.faces());
   assert(base_level < storage.levels());
   assert(format.block_dim() == storage.block_dim());
   assert(format.block_size() <= storage.block_size());
   for (glm::length_t c = dimensionality(tex_class); c < 3; ++c) {
      assert(storage.dim(base_level)[c] == 1);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
TextureView<TextureStorage, ImageView>::TextureView(const ImageFormat& format, TextureClass tex_class, TextureView& other)
   : storage_(other.storage_),
     tex_class_(tex_class),
     base_layer_(other.base_layer_),
     layers_(is_array(tex_class) ? other.layers_ : 1u),
     base_face_(other.base_face_),
     faces_(be::gfx::faces(tex_class) == 1u ? 1u : other.faces_),
     base_level_(other.base_level_),
     levels_(other.levels_) {
   assert(is_valid(tex_class));
   assert(format.block_dim() == storage_->block_dim());
   assert(format.block_size() <= storage_->block_size());
   for (glm::length_t c = dimensionality(tex_class); c < 3; ++c) {
      assert(storage_->dim(base_level_)[c] == 1);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
TextureView<TextureStorage, ImageView>::operator TextureView<const TextureStorage, ConstImageView>() const {
   return TextureView<const TextureStorage, ConstImageView>(format_, tex_class_, *storage_, base_layer_, layers_, base_face_, faces_, base_level_, levels_);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
TextureStorage& TextureView<TextureStorage, ImageView>::storage() {
   return *storage_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
const TextureStorage& TextureView<TextureStorage, ImageView>::storage() const {
   return *storage_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
TextureClass TextureView<TextureStorage, ImageView>::texture_class() const {
   return tex_class_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
const ImageFormat& TextureView<TextureStorage, ImageView>::format() const {
   return format_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
TextureView<TextureStorage, ImageView>::operator bool() const {
   return storage().size() > 0;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
bool TextureView<TextureStorage, ImageView>::empty() const {
   return storage().empty();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
ImageView TextureView<TextureStorage, ImageView>::image(std::size_t layer, std::size_t face, std::size_t level) {
   return ImageView(format_, *storage_, base_layer_ + layer, base_face_ + face, base_level_ + level);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
ConstImageView TextureView<TextureStorage, ImageView>::image(std::size_t layer, std::size_t face, std::size_t level) const {
   return ConstImageView(format_, *storage_, base_layer_ + layer, base_face_ + face, base_level_ + level);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::layers() const {
   return layers_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::base_layer() const {
   return base_layer_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::max_layer() const {
   return base_layer_ + layers_ - 1;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::faces() const {
   return faces_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::base_face() const {
   return base_face_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::max_face() const {
   return base_face_ + faces_ - 1;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::levels() const {
   return levels_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::base_level() const {
   return base_level_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::max_level() const {
   return base_level_ + levels_ - 1;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
typename TextureView<TextureStorage, ImageView>::block_size_type TextureView<TextureStorage, ImageView>::block_size() const {
   return storage_->block_size();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::line_span(std::size_t level) const {
   return storage_->line_span(base_level_ + level);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::plane_span(std::size_t level) const {
   return storage_->plane_span(base_level_ + level);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::level_offset(std::size_t level) const {
   return storage_->level_offset(base_level_ + level);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::face_span() const {
   return storage_->face_span();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
std::size_t TextureView<TextureStorage, ImageView>::layer_span() const {
   return storage_->layer_span();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
typename TextureView<TextureStorage, ImageView>::block_dim_type TextureView<TextureStorage, ImageView>::block_dim() const {
   return storage_->block_dim();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
ivec3 TextureView<TextureStorage, ImageView>::dim(std::size_t level) const {
   return storage_->dim(base_level_ + level);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename ImageView>
ivec3 TextureView<TextureStorage, ImageView>::dim_blocks(std::size_t level) const {
   return storage_->dim_blocks(base_level_ + level);
}

template class TextureView<TextureStorage, be::gfx::ImageView>;
template class TextureView<const TextureStorage, ConstImageView>;

} // be::gfx::detail
