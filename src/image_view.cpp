#include "pch.hpp"
#include "image_view.hpp"

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
ImageView::ImageView()
   : storage_(&TextureStorage::nil),
     layer_(0),
     face_(0),
     level_(0) { }

///////////////////////////////////////////////////////////////////////////////
ImageView::ImageView(const ImageFormat& format, TextureStorage& storage, std::size_t layer, std::size_t face, std::size_t level)
   : format_(format),
     storage_(&storage),
     layer_(static_cast<layer_index_type>(layer)),
     face_(static_cast<face_index_type>(face)),
     level_(static_cast<level_index_type>(level)),
     data_(storage.data()
           + layer * storage.layer_span()
           + face * storage.face_span()
           + storage.level_offset(level),
           storage.plane_span(level) * std::size_t(storage.dim_blocks(level).z)) {
   assert(layer >= 0 && layer < storage.layers());
   assert(face >= 0 && face < storage.faces());
   assert(level >= 0 && level < storage.levels());
   assert(format.block_dim() == storage.block_dim());
   assert(format.block_size() <= storage.block_size());
}

///////////////////////////////////////////////////////////////////////////////
ImageView::ImageView(const ImageFormat& format, ImageView& other)
   : format_(format),
     storage_(other.storage_),
     layer_(other.layer_),
     face_(other.face_),
     level_(other.level_),
     data_(other.data_.get(), other.data_.size()) {
   assert(format.block_dim() == storage_->block_dim());
   assert(format.block_size() <= storage_->block_size());
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage& ImageView::storage() {
   return *storage_;
}

///////////////////////////////////////////////////////////////////////////////
const TextureStorage& ImageView::storage() const {
   return *storage_;
}

///////////////////////////////////////////////////////////////////////////////
const ImageFormat& ImageView::format() const {
   return format_;
}

///////////////////////////////////////////////////////////////////////////////
ImageView::operator bool() const {
   return storage_->size() > 0;
}

///////////////////////////////////////////////////////////////////////////////
bool ImageView::empty() const {
   return storage_->size() == 0;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t ImageView::size() const {
   return data_.size();
}

///////////////////////////////////////////////////////////////////////////////
UC* ImageView::data() {
   return data_.get();
}
///////////////////////////////////////////////////////////////////////////////
const UC* ImageView::data() const {
   return data_.get();
}

///////////////////////////////////////////////////////////////////////////////
ImageView::operator Buf<UC>() {
   return Buf<UC>(data_.get(), data_.size());
}

///////////////////////////////////////////////////////////////////////////////
ImageView::operator Buf<const UC>() const {
   return Buf<const UC>(data_.get(), data_.size());
}

///////////////////////////////////////////////////////////////////////////////
std::size_t ImageView::layer() const {
   return layer_;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t ImageView::face() const {
   return face_;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t ImageView::level() const {
   return level_;
}

///////////////////////////////////////////////////////////////////////////////
ImageView::block_size_type ImageView::block_size() const {
   return storage_->block_size();
}

///////////////////////////////////////////////////////////////////////////////
std::size_t ImageView::line_span() const {
   return storage_->line_span(level_);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t ImageView::plane_span() const {
   return storage_->plane_span(level_);
}

///////////////////////////////////////////////////////////////////////////////
ImageView::block_dim_type ImageView::block_dim() const {
   return storage_->block_dim();
}

///////////////////////////////////////////////////////////////////////////////
const ivec3& ImageView::dim() const {
   return storage_->dim(level_);
}

///////////////////////////////////////////////////////////////////////////////
const ivec3& ImageView::dim_blocks() const {
   return storage_->dim_blocks(level_);
}

} // be::gfx
