#include "pch.hpp"
#include "image_format.hpp"

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ImageFormat() 
   : block_size_(0),
     packing_(ImageBlockPacking::s_8),
     components_(0),
     colorspace_(Colorspace::unknown),
     premultiplied_(false) { }

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ImageFormat(block_size_type block_size,
                         block_dim_type block_dim,
                         ImageBlockPacking packing,
                         U8 components,
                         ctype_vec_type component_types,
                         swizzle_vec_type swizzle,
                         Colorspace colorspace,
                         bool premultiplied)
   : block_size_(block_size),
     block_dim_(block_dim),
     packing_(packing),
     components_(components),
     component_types_(component_types),
     swizzle_(swizzle),
     colorspace_(colorspace),
     premultiplied_(premultiplied) {
   assert(block_size > 0);
   assert(block_dim.x > 0);
   assert(block_dim.y > 0);
   assert(block_dim.z > 0);
   assert(is_valid(packing));
   assert(components > 0);
   assert(is_valid(static_cast<ImageComponentType>(component_types.r)));
   assert(is_valid(static_cast<ImageComponentType>(component_types.g)));
   assert(is_valid(static_cast<ImageComponentType>(component_types.b)));
   assert(is_valid(static_cast<ImageComponentType>(component_types.a)));
   assert(is_valid(static_cast<Swizzle>(swizzle.r)));
   assert(is_valid(static_cast<Swizzle>(swizzle.g)));
   assert(is_valid(static_cast<Swizzle>(swizzle.b)));
   assert(is_valid(static_cast<Swizzle>(swizzle.a)));
   assert(is_valid(colorspace));
   assert(!premultiplied || components == 4);
   assert(block_size >= block_dim.x * block_dim.y * block_dim.z * image_block_pixel_size(packing));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::operator bool() const {
   return block_size_ > 0;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::block_size(block_size_type size) {
   assert(size > 0);
   block_size_ = size;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::block_size_type ImageFormat::block_size() const {
   return block_size_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::block_dim(block_dim_type block_dim) {
   assert(block_dim.x > 0);
   assert(block_dim.y > 0);
   assert(block_dim.z > 0);
   block_dim_ = block_dim;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::block_dim_type ImageFormat::block_dim() const {
   return block_dim_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::components(U8 n_comps) {
   assert(n_comps > 0);
   components_ = n_comps;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
U8 ImageFormat::components() const {
   return components_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::packing(ImageBlockPacking value) {
   assert(is_valid(value));
   packing_ = value;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageBlockPacking ImageFormat::packing() const {
   return packing_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::component_types(ctype_vec_type types) {
   assert(is_valid(static_cast<ImageComponentType>(types.r)));
   assert(is_valid(static_cast<ImageComponentType>(types.g)));
   assert(is_valid(static_cast<ImageComponentType>(types.b)));
   assert(is_valid(static_cast<ImageComponentType>(types.a)));
   component_types_ = types;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ctype_vec_type ImageFormat::component_types() const {
   return component_types_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::component_type(glm::length_t component, ImageComponentType type) {
   assert(is_valid(static_cast<ImageComponentType>(type)));
   component_types_[component] = static_cast<ctype_vec_type::value_type>(type);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageComponentType ImageFormat::component_type(glm::length_t component) const {
   return static_cast<ImageComponentType>(component_types_[component]);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::swizzle(swizzle_vec_type swizzle) {
   assert(is_valid(static_cast<Swizzle>(swizzle.r)));
   assert(is_valid(static_cast<Swizzle>(swizzle.g)));
   assert(is_valid(static_cast<Swizzle>(swizzle.b)));
   assert(is_valid(static_cast<Swizzle>(swizzle.a)));
   swizzle_ = swizzle;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzle_vec_type ImageFormat::swizzle() const {
   return swizzle_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::swizzle(glm::length_t component, Swizzle swizzle) {
   assert(is_valid(static_cast<Swizzle>(swizzle)));
   swizzle_[component] = static_cast<ctype_vec_type::value_type>(swizzle);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
Swizzle ImageFormat::swizzle(glm::length_t component) const {
   return static_cast<Swizzle>(swizzle_[component]);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::colorspace(Colorspace colorspace) {
   assert(is_valid(colorspace));
   colorspace_ = colorspace;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
Colorspace ImageFormat::colorspace() const {
   return colorspace_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::premultiplied(bool premultiplied) {
   assert(!premultiplied || components_ == 4);
   premultiplied_ = premultiplied;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
bool ImageFormat::premultiplied() const {
   return premultiplied_;
}

///////////////////////////////////////////////////////////////////////////////
bool ImageFormat::operator==(const ImageFormat& other) const {
   return block_size_ == other.block_size_ &&
      block_dim_ == other.block_dim_ &&
      packing_ == other.packing_ &&
      components_ == other.components_ &&
      component_types_ == other.component_types_ &&
      swizzle_ == other.swizzle_ &&
      colorspace_ == other.colorspace_ &&
      premultiplied_ == other.premultiplied_;
}

///////////////////////////////////////////////////////////////////////////////
bool ImageFormat::operator!=(const ImageFormat& other) const {
   return !(*this == other);
}

} // be::gfx
