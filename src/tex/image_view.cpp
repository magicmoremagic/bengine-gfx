#include "pch.hpp"
#include "image_view.hpp"

namespace be::gfx::detail {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ImageView<TextureStorage, UC>::ImageView()
   : storage_(&TextureStorage::nil),
     layer_(0),
     face_(0),
     level_(0),
     data_(nullptr),
     size_(0) { }

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ImageView<TextureStorage, UC>::ImageView(const ImageFormat& format, TextureStorage& storage, std::size_t layer, std::size_t face, std::size_t level)
   : storage_(&storage),
     format_(format),
     layer_(static_cast<layer_index_type>(layer)),
     face_(static_cast<face_index_type>(face)),
     level_(static_cast<level_index_type>(level)),
     data_(storage.data()
           + layer * storage.layer_span()
           + face * storage.face_span()
           + storage.level_offset(level)),
     size_(storage.plane_span(level) * std::size_t(storage.dim_blocks(level).z)),
     dim_(storage.dim(level)),
     dim_blocks_(storage.dim_blocks(level)),
     line_plane_span_(storage.line_span(level), storage.plane_span(level)) {
   assert(layer >= 0 && layer < storage.layers());
   assert(face >= 0 && face < storage.faces());
   assert(level >= 0 && level < storage.levels());
   assert(format.block_dim() == storage.block_dim());
   assert(format.block_size() <= storage.block_size());
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ImageView<TextureStorage, UC>::ImageView(const ImageFormat& format, ImageView& other)
   : storage_(other.storage_),
     format_(format),
     layer_(other.layer_),
     face_(other.face_),
     level_(other.level_),
     data_(other.data_),
     size_(other.size_),
     dim_(other.dim_),
     dim_blocks_(other.dim_blocks_),
     line_plane_span_(other.line_plane_span_) {
   assert(format.block_dim() == storage_->block_dim());
   assert(format.block_size() <= storage_->block_size());
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ImageView<TextureStorage, UC>::operator ImageView<const TextureStorage, const UC>() const {
   return ImageView<const TextureStorage, const UC>(format_, *storage_, layer_, face_, level_);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
TextureStorage& ImageView<TextureStorage, UC>::storage() {
   return *storage_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
const TextureStorage& ImageView<TextureStorage, UC>::storage() const {
   return *storage_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
const ImageFormat& ImageView<TextureStorage, UC>::format() const {
   return format_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ImageView<TextureStorage, UC>::operator bool() const {
   return storage_->size() > 0;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
bool ImageView<TextureStorage, UC>::empty() const {
   return storage_->empty();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
std::size_t ImageView<TextureStorage, UC>::size() const {
   return size_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
UC* ImageView<TextureStorage, UC>::data() {
   return data_;
}
///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
const UC* ImageView<TextureStorage, UC>::data() const {
   return data_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ImageView<TextureStorage, UC>::operator Buf<UC>() {
   return Buf<UC>(data_, size_);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ImageView<TextureStorage, UC>::operator Buf<const UC>() const {
   return Buf<const UC>(data_, size_);
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
std::size_t ImageView<TextureStorage, UC>::layer() const {
   return layer_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
std::size_t ImageView<TextureStorage, UC>::face() const {
   return face_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
std::size_t ImageView<TextureStorage, UC>::level() const {
   return level_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
typename ImageView<TextureStorage, UC>::block_size_type ImageView<TextureStorage, UC>::block_size() const {
   return storage_->block_size();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
std::size_t ImageView<TextureStorage, UC>::line_span() const {
   return line_plane_span_.x;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
std::size_t ImageView<TextureStorage, UC>::plane_span() const {
   return line_plane_span_.y;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
typename ImageView<TextureStorage, UC>::block_dim_type ImageView<TextureStorage, UC>::block_dim() const {
   return storage_->block_dim();
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ivec3 ImageView<TextureStorage, UC>::dim() const {
   return dim_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureStorage, typename UC>
ivec3 ImageView<TextureStorage, UC>::dim_blocks() const {
   return dim_blocks_;
}

template class ImageView<TextureStorage, UC>;
template class ImageView<const TextureStorage, const UC>;

} // be::gfx::detail
