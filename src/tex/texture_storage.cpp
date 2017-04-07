#include "pch.hpp"
#include "texture_storage.hpp"
#include <be/core/alg.hpp>
#include <glm/vector_relational.hpp>
#include <glm/gtc/round.hpp>
#include <cassert>

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
TextureStorage TextureStorage::nil = TextureStorage();

///////////////////////////////////////////////////////////////////////////////
TextureStorage::TextureStorage()
   : layers_(0),
     faces_(0),
     levels_(0),
     block_size_(0),
     face_span_(0),
     layer_span_(0),
     size_(0),
     dim_({}),
     dim_blocks_({}),
     line_plane_span_({}),
     level_offset_({}) { }

///////////////////////////////////////////////////////////////////////////////
TextureStorage::TextureStorage(std::size_t layers,
                               std::size_t faces,
                               std::size_t levels,
                               ivec3 base_dim,
                               block_dim_type block_dim,
                               block_size_type block_size,
                               TextureAlignment alignment)
   : layers_(layer_index_type(layers)),
     faces_(face_index_type(faces)),
     block_size_(block_size),
     block_dim_(block_dim),
     alignment_(alignment) {
   init_(levels, base_dim);
   data_ = make_aligned_buf<UC>(size_, alignment_.layer);
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::TextureStorage(std::size_t layers,
                               std::size_t faces,
                               std::size_t levels,
                               ivec3 base_dim,
                               block_dim_type block_dim,
                               block_size_type block_size,
                               Buf<UC> data,
                               TextureAlignment alignment)
   : layers_(layer_index_type(layers)),
     faces_(face_index_type(faces)),
     block_size_(block_size),
     block_dim_(block_dim),
     alignment_(alignment) {
   init_(levels, base_dim);
   assert(data.size() >= size_);
   assert(glm::ceilMultiple((uintptr_t)data.get(), (uintptr_t)alignment_.layer) == (uintptr_t)data.get());
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
TextureStorage::operator Buf<UC>() {
   return Buf<UC>(data_.get(), data_.size());
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::operator Buf<const UC>() const {
   return Buf<const UC>(data_.get(), data_.size());
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
   return line_plane_span_[level].x;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::plane_span(std::size_t level) const {
   assert(level >= 0 && level < max_levels);
   return line_plane_span_[level].y;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::level_offset(std::size_t level) const {
   assert(level >= 0 && level < max_levels);
   return level_offset_[level];
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
ivec3 TextureStorage::dim(std::size_t level) const {
   assert(level >= 0 && level < max_levels);
   return dim_[level];
}

///////////////////////////////////////////////////////////////////////////////
ivec3 TextureStorage::dim_blocks(std::size_t level) const {
   assert(level >= 0 && level < max_levels);
   return dim_blocks_[level];
}

///////////////////////////////////////////////////////////////////////////////
TextureAlignment TextureStorage::alignment() const {
   return alignment_;
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::alignment_type TextureStorage::line_alignment() const {
   return alignment_.line;
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::alignment_type TextureStorage::plane_alignment() const {
   return alignment_.plane;
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::alignment_type TextureStorage::level_alignment() const {
   return alignment_.level;
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::alignment_type TextureStorage::face_alignment() const {
   return alignment_.face;
}

///////////////////////////////////////////////////////////////////////////////
TextureStorage::alignment_type TextureStorage::layer_alignment() const {
   return alignment_.layer;
}

///////////////////////////////////////////////////////////////////////////////
bool TextureStorage::operator==(const TextureStorage& other) const {
   if (size_ != other.size_) return false;
   if (layer_span_ != other.layer_span_) return false;
   if (face_span_ != other.face_span_) return false;
   if (layers_ != other.layers_) return false;
   if (levels_ != other.levels_) return false;
   if (faces_ != other.faces_) return false;
   if (block_size_ != other.block_size_) return false;
   if (block_dim_ != other.block_dim_) return false;
   if (dim_ != other.dim_) return false;
   if (dim_blocks_ != other.dim_blocks_) return false;
   if (line_plane_span_ != other.line_plane_span_) return false;
   if (level_offset_ != other.level_offset_) return false;
   if (alignment_ != other.alignment_) return false;
   return 0 == memcmp(data_.get(), other.data_.get(), size_);
}

///////////////////////////////////////////////////////////////////////////////
bool TextureStorage::operator!=(const TextureStorage& other) const {
   return !(*this == other);
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

   alignment_.line = max((TextureStorage::alignment_type)1, alignment_.line);
   alignment_.plane = max(alignment_.line, alignment_.plane);
   alignment_.level = max(alignment_.plane, alignment_.level);
   alignment_.face = max(alignment_.level, alignment_.face);
   alignment_.layer = max(alignment_.face, alignment_.level);

   assert(glm::ceilPowerOfTwo(alignment_.line) == alignment_.line);
   assert(glm::ceilPowerOfTwo(alignment_.plane) == alignment_.plane);
   assert(glm::ceilPowerOfTwo(alignment_.level) == alignment_.level);
   assert(glm::ceilPowerOfTwo(alignment_.face) == alignment_.face);
   assert(glm::ceilPowerOfTwo(alignment_.layer) == alignment_.layer);

   std::size_t face_span = 0;
   std::size_t level = 0;
   ivec3 block_dim_ivec3 = ivec3(block_dim_);
   if (glm::all(glm::greaterThan(dim, ivec3(0)))) {
      while (level < levels) {
         level_offset_[level] = face_span;
         dim_[level] = dim;

         ivec3 dim_blocks = glm::ceilMultiple(dim, block_dim_ivec3) / block_dim_ivec3;
         dim_blocks_[level] = dim_blocks;

         U32 line_span = glm::ceilMultiple(U32(dim_blocks.x) * block_size_, (U32)alignment_.line);
         U32 plane_span = glm::ceilMultiple(U32(dim_blocks.y) * line_span, (U32)alignment_.plane);
         line_plane_span_[level] = uvec2(line_span, plane_span);

         face_span += glm::ceilMultiple(std::size_t(dim_blocks.z) * plane_span, std::size_t(alignment_.level));

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
      level_offset_[level] = face_span;
      dim_[level] = ivec3();
      dim_blocks_[level] = ivec3();
      line_plane_span_[level] = uvec2();
      ++level;
   }

   levels_ = level_index_type(levels);

   face_span_ = glm::ceilMultiple(face_span, std::size_t(alignment_.face));
   layer_span_ = glm::ceilMultiple(face_span_ * faces_, std::size_t(alignment_.layer));
   size_ = layer_span_ * layers_;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TextureStorage::hash_() const {
   using be::std_hash;
   std::size_t h = std_hash(layers_);
   h = std_hash(h, faces_);
   h = std_hash(h, levels_);
   h = std_hash(h, block_size_);
   h = std_hash(h, block_dim_);
   h = std_hash(h, face_span_);
   h = std_hash(h, layer_span_);
   h = std_hash(h, size_);
   h = std_hash(h, dim_);
   h = std_hash(h, dim_blocks_);
   h = std_hash(h, line_plane_span_);
   h = std_hash(h, level_offset_);
   h = std_hash(h, alignment_.line);
   h = std_hash(h, alignment_.plane);
   h = std_hash(h, alignment_.level);
   h = std_hash(h, alignment_.face);
   h = std_hash(h, alignment_.layer);
   h = std_hash_raw(h, data_.get(), data_.size());
   return h;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t calculate_required_texture_storage(std::size_t layers,
                                               std::size_t faces,
                                               std::size_t levels,
                                               ivec3 base_dim,
                                               TextureStorage::block_dim_type block_dim,
                                               TextureStorage::block_size_type block_size,
                                               TextureAlignment alignment) {
   if (layers == 0 || layers > TextureStorage::max_layers ||
       faces == 0 || faces > TextureStorage::max_faces ||
       block_size == 0 || block_size > TextureStorage::max_block_size) {
      return 0;
   }

   if (glm::any(glm::equal(block_dim, TextureStorage::block_dim_type())) ||
       glm::any(glm::greaterThan(ivec3(block_dim), ivec3(TextureStorage::max_block_dim)))) {
      return 0;
   }

   if (glm::any(glm::lessThanEqual(base_dim, ivec3())) ||
       glm::any(glm::greaterThan(base_dim, ivec3(TextureStorage::max_dim)))) {
      return 0;
   }

   alignment.line = max((TextureStorage::alignment_type)1, alignment.line);
   alignment.plane = max(alignment.line, alignment.plane);
   alignment.level = max(alignment.plane,alignment.level);
   alignment.face = max(alignment.level, alignment.face);
   alignment.layer = max(alignment.face, alignment.level);

   std::size_t face_span = 0;
   
   ivec3 block_dim_ivec3 = ivec3(block_dim);
   for (std::size_t level = 0; level < levels; ++level) {
      ivec3 dim_blocks = glm::ceilMultiple(base_dim, block_dim_ivec3) / block_dim_ivec3;
      std::size_t line_span = glm::ceilMultiple(std::size_t(dim_blocks.x) * block_size, std::size_t(alignment.line));
      std::size_t plane_span = glm::ceilMultiple(std::size_t(dim_blocks.y) * line_span, std::size_t(alignment.plane));
      std::size_t level_span = glm::ceilMultiple(std::size_t(dim_blocks.z) * plane_span, std::size_t(alignment.level));

      face_span += level_span;

      if (base_dim == ivec3(1)) {
         break;
      }

      base_dim = glm::max(base_dim >> 1, ivec3(1));
   }

   face_span = glm::ceilMultiple(face_span, std::size_t(alignment.face));
   std::size_t layer_span = glm::ceilMultiple(faces * face_span, std::size_t(alignment.layer));

   return layer_span * layers;
}

} // be::gfx
