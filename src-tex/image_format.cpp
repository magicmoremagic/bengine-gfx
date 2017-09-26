#include "pch.hpp"
#include "tex/image_format.hpp"

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ImageFormat()
   : block_size_(0),
     packing_(BlockPacking::s_8),
     components_(0),
     colorspace_(Colorspace::unknown),
     premultiplied_(false) { }

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ImageFormat(std::size_t block_size,
                         std::size_t block_dim,
                         BlockPacking packing,
                         glm::length_t components,
                         field_types_type field_types,
                         swizzles_type swizzles,
                         Colorspace colorspace,
                         bool premultiplied)
   : ImageFormat(block_size, block_dim_type(static_cast<block_size_type>(block_dim)), packing, components, field_types, swizzles, colorspace, premultiplied) {
   assert(block_dim <= max_block_dim);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ImageFormat(std::size_t block_size,
                         block_dim_type block_dim,
                         BlockPacking packing,
                         glm::length_t components,
                         field_types_type field_types,
                         swizzles_type swizzles,
                         Colorspace colorspace,
                         bool premultiplied)
   : block_size_(static_cast<block_size_type>(block_size)),
     block_dim_(block_dim),
     packing_(packing),
     components_(static_cast<component_count_type>(components)),
     field_types_(field_types),
     swizzles_(swizzles),
     colorspace_(colorspace),
     premultiplied_(premultiplied) {
   assert(block_size > 0);
   assert(block_size <= max_block_size);
   assert(block_dim.x > 0);
   assert(block_dim.y > 0);
   assert(block_dim.z > 0);
   assert(block_dim.x <= max_block_dim);
   assert(block_dim.y <= max_block_dim);
   assert(block_dim.z <= max_block_dim);
   assert(is_valid(packing));
   assert(components > 0);
   assert(components <= max_components);
   assert(is_valid(static_cast<FieldType>(field_types.r)));
   assert(is_valid(static_cast<FieldType>(field_types.g)));
   assert(is_valid(static_cast<FieldType>(field_types.b)));
   assert(is_valid(static_cast<FieldType>(field_types.a)));
   assert(is_valid(static_cast<Swizzle>(swizzles.r)));
   assert(is_valid(static_cast<Swizzle>(swizzles.g)));
   assert(is_valid(static_cast<Swizzle>(swizzles.b)));
   assert(is_valid(static_cast<Swizzle>(swizzles.a)));
   assert(is_valid(colorspace));
   assert(block_size >= block_dim.x * block_dim.y * block_dim.z * block_pixel_size(packing));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::operator bool() const {
   return block_size_ > 0;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::block_size(std::size_t size) {
   assert(size > 0);
   assert(size <= max_block_size);
   block_size_ = static_cast<block_size_type>(size);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::block_size_type ImageFormat::block_size() const {
   return block_size_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::block_dim(std::size_t block_dim) {
   assert(block_dim > 0);
   assert(block_dim <= max_block_dim);
   block_dim_.x = static_cast<block_size_type>(block_dim);
   block_dim_.y = static_cast<block_size_type>(block_dim);
   block_dim_.z = static_cast<block_size_type>(block_dim);
   return *this;
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
ImageFormat& ImageFormat::components(glm::length_t n_comps) {
   assert(n_comps > 0);
   assert(n_comps <= max_components);
   components_ = static_cast<component_count_type>(n_comps);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::component_count_type ImageFormat::components() const {
   return components_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::packing(BlockPacking value) {
   assert(is_valid(value));
   packing_ = value;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
BlockPacking ImageFormat::packing() const {
   return packing_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::field_types(field_types_type types) {
   assert(is_valid(static_cast<FieldType>(types.r)));
   assert(is_valid(static_cast<FieldType>(types.g)));
   assert(is_valid(static_cast<FieldType>(types.b)));
   assert(is_valid(static_cast<FieldType>(types.a)));
   field_types_ = types;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::field_types_type ImageFormat::field_types() const {
   return field_types_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::field_type(glm::length_t field, FieldType type) {
   assert(is_valid(static_cast<FieldType>(type)));
   assert(field <= max_fields);
   field_types_[field] = static_cast<field_types_type::value_type>(type);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
FieldType ImageFormat::field_type(glm::length_t field) const {
   assert(field <= max_fields);
   return static_cast<FieldType>(field_types_[field]);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::swizzles(swizzles_type swizzle) {
   assert(is_valid(static_cast<Swizzle>(swizzle.r)));
   assert(is_valid(static_cast<Swizzle>(swizzle.g)));
   assert(is_valid(static_cast<Swizzle>(swizzle.b)));
   assert(is_valid(static_cast<Swizzle>(swizzle.a)));
   swizzles_ = swizzle;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type ImageFormat::swizzles() const {
   return swizzles_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::swizzle(glm::length_t component, Swizzle swizzle) {
   assert(is_valid(static_cast<Swizzle>(swizzle)));
   assert(component <= max_mapped_components);
   swizzles_[component] = static_cast<swizzles_type::value_type>(swizzle);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
Swizzle ImageFormat::swizzle(glm::length_t component) const {
   assert(component <= max_mapped_components);
   return static_cast<Swizzle>(swizzles_[component]);
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
      field_types_ == other.field_types_ &&
      swizzles_ == other.swizzles_ &&
      colorspace_ == other.colorspace_ &&
      premultiplied_ == other.premultiplied_;
}

///////////////////////////////////////////////////////////////////////////////
bool ImageFormat::operator!=(const ImageFormat& other) const {
   return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat simple_format(ImageFormat format) {
   if (is_compressed(format.packing())) {
      return format;
   } else {
      return ImageFormat(block_pixel_size(format.packing()), 1u, format.packing(),
                         format.components(), format.field_types(), format.swizzles(),
                         format.colorspace(), format.premultiplied());
   }
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::field_types_type field_types(FieldType type, glm::length_t n_fields) {
   using V = ImageFormat::field_types_type;
   using T = V::value_type;
   V vec(static_cast<T>(FieldType::none));
   for (glm::length_t i = 0; i < n_fields; ++i) {
      vec[i] = static_cast<T>(type);
   }
   return vec;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::field_types_type field_types(FieldType type0, FieldType type1) {
   using V = ImageFormat::field_types_type;
   using T = V::value_type;
   return V(static_cast<T>(type0),
            static_cast<T>(type1),
            static_cast<T>(FieldType::none),
            static_cast<T>(FieldType::none));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::field_types_type field_types(FieldType type0, FieldType type1, FieldType type2) {
   using V = ImageFormat::field_types_type;
   using T = V::value_type;
   return V(static_cast<T>(type0),
            static_cast<T>(type1),
            static_cast<T>(type2),
            static_cast<T>(FieldType::none));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::field_types_type field_types(FieldType type0, FieldType type1, FieldType type2, FieldType type3) {
   using V = ImageFormat::field_types_type;
   using T = V::value_type;
   return V(static_cast<T>(type0),
            static_cast<T>(type1),
            static_cast<T>(type2),
            static_cast<T>(type3));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::field_types_type field_types(std::initializer_list<FieldType> types) {
   assert(types.size() <= 4);
   using V = ImageFormat::field_types_type;
   using T = V::value_type;
   V vec(static_cast<T>(FieldType::none));
   glm::length_t i = 0;
   for (FieldType type : types) {
      vec[i++] = static_cast<T>(type);
   }
   return vec;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles(Swizzle s0, Swizzle s1, Swizzle s2, Swizzle s3) {
   using V = ImageFormat::swizzles_type;
   using T = V::value_type;
   return V(static_cast<T>(s0),
            static_cast<T>(s1),
            static_cast<T>(s2),
            static_cast<T>(s3));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles(std::initializer_list<Swizzle> swizzles) {
   assert(swizzles.size() <= 4);
   using V = ImageFormat::swizzles_type;
   using T = V::value_type;
   V vec(static_cast<T>(Swizzle::literal_zero),
         static_cast<T>(Swizzle::literal_zero),
         static_cast<T>(Swizzle::literal_zero),
         static_cast<T>(Swizzle::literal_one));
   glm::length_t i = 0;
   for (Swizzle s : swizzles) {
      vec[i++] = static_cast<T>(s);
   }
   return vec;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_r() {
   return swizzles(Swizzle::field_zero);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_rrr() {
   return swizzles(Swizzle::field_zero, Swizzle::field_zero, Swizzle::field_zero);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_rg() {
   return swizzles(Swizzle::field_zero, Swizzle::field_one);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_rgb() {
   return swizzles(Swizzle::field_zero, Swizzle::field_one, Swizzle::field_two);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_bgr() {
   return swizzles(Swizzle::field_two, Swizzle::field_one, Swizzle::field_zero);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_abg() {
   return swizzles(Swizzle::field_three, Swizzle::field_two, Swizzle::field_one);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_rgba() {
   return swizzles(Swizzle::field_zero, Swizzle::field_one, Swizzle::field_two, Swizzle::field_three);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_bgra() {
   return swizzles(Swizzle::field_two, Swizzle::field_one, Swizzle::field_zero, Swizzle::field_three);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_abgr() {
   return swizzles(Swizzle::field_three, Swizzle::field_two, Swizzle::field_one, Swizzle::field_zero);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_argb() {
   return swizzles(Swizzle::field_three, Swizzle::field_zero, Swizzle::field_one, Swizzle::field_two);
}

} // be::gfx::tex
