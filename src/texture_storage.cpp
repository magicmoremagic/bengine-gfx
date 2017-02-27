#include "pch.hpp"
#include "texture_storage.hpp"
#include <cassert>
#include <glm/vector_relational.hpp>
#include <glm/gtc/round.hpp>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
const TextureStorage TextureStorage::nil = TextureStorage();

///////////////////////////////////////////////////////////////////////////////
TextureStorage::TextureStorage()
   : size_(0),
     layers_(0),
     faces_(0),
     levels_(0),
     block_size_(0),
     dim_({}),
     dim_blocks_({}),
     face_span_(0),
     layer_span_(0),
     line_span_({}),
     plane_span_({}) { }

///////////////////////////////////////////////////////////////////////////////
TextureStorage::TextureStorage(std::size_t layers,
                               std::size_t faces,
                               std::size_t levels,
                               ivec3 base_dim,
                               block_dim_type block_dim,
                               block_size_type block_size)
   : layers_(layer_index_type(layers)),
     faces_(face_index_type(faces)),
     block_size_(block_size),
     block_dim_(block_dim) {
   init_(levels, base_dim);
   data_ = make_buf<UC>(size_);
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::TextureStorage(std::size_t layers,
                               std::size_t faces,
                               std::size_t levels,
                               ivec3 base_dim,
                               block_dim_type block_dim,
                               block_size_type block_size,
                               Buf<UC> data)
   : layers_(layer_index_type(layers)),
     faces_(face_index_type(faces)),
     block_size_(block_size),
     block_dim_(block_dim) {
   init_(levels, base_dim);
   assert(data.size() >= size_);
   data_ = std::move(data);
}  

///////////////////////////////////////////////////////////////////////////////
TextureStorage::operator bool() const {
   return size_ > 0;
}

///////////////////////////////////////////////////////////////////////////////
bool TextureStorage::empty() const {
   return size_ == 0;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::size() const {
   return size_;
}

///////////////////////////////////////////////////////////////////////////////
UC* TextureStorage::data() {
   return data_.get();
}

///////////////////////////////////////////////////////////////////////////////
const UC* TextureStorage::data() const {
   return data_.get();
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::layers() const {
   return layers_;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::faces() const {
   return faces_;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::levels() const {
   return levels_;
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::block_size_type TextureStorage::block_size() const {
   return block_size_;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::line_span(std::size_t level) const {
   assert(level >= 0 && level < max_levels);
   return line_span_[level];
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::plane_span(std::size_t level) const {
   assert(level >= 0 && level < max_levels);
   return plane_span_[level];
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::face_span() const {
   return face_span_;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::layer_span() const {
   return layer_span_;
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::block_dim_type TextureStorage::block_dim() const {
   return block_dim_;
}

///////////////////////////////////////////////////////////////////////////////
const ivec3& TextureStorage::dim(std::size_t level) const {
   assert(level >= 0 && level < max_levels);
   return dim_[level];
}

///////////////////////////////////////////////////////////////////////////////
const ivec3& TextureStorage::dim_blocks(std::size_t level) const {
   assert(level >= 0 && level < max_levels);
   return dim_blocks_[level];
}

///////////////////////////////////////////////////////////////////////////////
void TextureStorage::init_(std::size_t levels, ivec3 dim) {
   assert(layers_ <= max_layers);
   assert(faces_ <= max_faces);
   assert(levels <= max_levels);
   assert(block_size_ <= max_block_size);

   assert(block_dim_.x > 0);
   assert(block_dim_.y > 0);
   assert(block_dim_.z > 0);

   assert(block_size_ > 0);

   assert(dim.x > 0);
   assert(dim.y > 0);
   assert(dim.z > 0);

   assert(std::size_t(dim.x) <= max_dim);
   assert(std::size_t(dim.y) <= max_dim);
   assert(std::size_t(dim.z) <= max_dim);

   std::size_t face_span = 0;
   std::size_t level = 0;
   ivec3 block_dim_ivec3 = ivec3(block_dim_);
   if (glm::all(glm::greaterThan(dim, ivec3(0)))) {
      while (level < levels) {
         dim_[level] = dim;
         ivec3 dim_blocks = glm::ceilMultiple(dim, block_dim_ivec3) / block_dim_ivec3;
         dim_blocks_[level] = dim_blocks;
         std::size_t line_span = std::size_t(dim_blocks.x) * block_size_;
         line_span_[level] = line_span;
         std::size_t plane_span = std::size_t(dim_blocks.y) * line_span;
         plane_span_[level] = plane_span;
         face_span += plane_span;

         if (dim == ivec3(1)) {
            ++level;
            levels = level;
            break;
         }

         dim = glm::max(dim >> 1, ivec3(1));
         ++level;
      }
   }

   while (level < max_levels) {
      dim_[level] = ivec3();
      dim_blocks_[level] = ivec3();
      line_span_[level] = 0;
      plane_span_[level] = 0;
      ++level;
   }

   levels_ = level_index_type(levels);
   face_span_ = face_span;
   layer_span_ = face_span * faces_;
   size_ = layer_span_ * layers_;
}

} // be::gfx
