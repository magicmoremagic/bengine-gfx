#include "tex/pch.hpp"
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
ImageFormat::ImageFormat(block_size_type block_size,
                         block_size_type block_dim,
                         BlockPacking packing,
                         U8 components,
                         component_types_type component_types,
                         swizzles_type swizzles,
                         Colorspace colorspace,
                         bool premultiplied)
   : ImageFormat(block_size, block_dim_type(block_dim), packing, components, component_types, swizzles, colorspace, premultiplied) { }

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ImageFormat(block_size_type block_size,
                         block_dim_type block_dim,
                         BlockPacking packing,
                         U8 components,
                         component_types_type component_types,
                         swizzles_type swizzles,
                         Colorspace colorspace,
                         bool premultiplied)
   : block_size_(block_size),
     block_dim_(block_dim),
     packing_(packing),
     components_(components),
     component_types_(component_types),
     swizzle_(swizzles),
     colorspace_(colorspace),
     premultiplied_(premultiplied) {
   assert(block_size > 0);
   assert(block_dim.x > 0);
   assert(block_dim.y > 0);
   assert(block_dim.z > 0);
   assert(is_valid(packing));
   assert(components > 0);
   assert(is_valid(static_cast<ComponentType>(component_types.r)));
   assert(is_valid(static_cast<ComponentType>(component_types.g)));
   assert(is_valid(static_cast<ComponentType>(component_types.b)));
   assert(is_valid(static_cast<ComponentType>(component_types.a)));
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
ImageFormat& ImageFormat::block_dim(block_size_type block_dim) {
   assert(block_dim > 0);
   block_dim_.x = block_dim;
   block_dim_.y = block_dim;
   block_dim_.z = block_dim;
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
ImageFormat& ImageFormat::component_types(component_types_type types) {
   assert(is_valid(static_cast<ComponentType>(types.r)));
   assert(is_valid(static_cast<ComponentType>(types.g)));
   assert(is_valid(static_cast<ComponentType>(types.b)));
   assert(is_valid(static_cast<ComponentType>(types.a)));
   component_types_ = types;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::component_types_type ImageFormat::component_types() const {
   return component_types_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::component_type(glm::length_t component, ComponentType type) {
   assert(is_valid(static_cast<ComponentType>(type)));
   component_types_[component] = static_cast<component_types_type::value_type>(type);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ComponentType ImageFormat::component_type(glm::length_t component) const {
   return static_cast<ComponentType>(component_types_[component]);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::swizzles(swizzles_type swizzle) {
   assert(is_valid(static_cast<Swizzle>(swizzle.r)));
   assert(is_valid(static_cast<Swizzle>(swizzle.g)));
   assert(is_valid(static_cast<Swizzle>(swizzle.b)));
   assert(is_valid(static_cast<Swizzle>(swizzle.a)));
   swizzle_ = swizzle;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type ImageFormat::swizzles() const {
   return swizzle_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat& ImageFormat::swizzle(glm::length_t component, Swizzle swizzle) {
   assert(is_valid(static_cast<Swizzle>(swizzle)));
   swizzle_[component] = static_cast<component_types_type::value_type>(swizzle);
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

///////////////////////////////////////////////////////////////////////////////
ImageFormat simple_format(ImageFormat format) {
   if (is_compressed(format.packing())) {
      return format;
   } else {
      return ImageFormat(block_pixel_size(format.packing()), 1u, format.packing(),
                         format.components(), format.component_types(), format.swizzles(),
                         format.colorspace(), format.premultiplied());
   }
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::component_types_type component_types(ComponentType type, glm::length_t n_components) {
   using V = ImageFormat::component_types_type;
   using T = V::value_type;
   V vec(static_cast<T>(ComponentType::none));
   for (glm::length_t i = 0; i < n_components; ++i) {
      vec[i] = static_cast<T>(type);
   }
   return vec;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::component_types_type component_types(ComponentType type0, ComponentType type1) {
   using V = ImageFormat::component_types_type;
   using T = V::value_type;
   return V(static_cast<T>(type0),
            static_cast<T>(type1),
            static_cast<T>(ComponentType::none),
            static_cast<T>(ComponentType::none));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::component_types_type component_types(ComponentType type0, ComponentType type1, ComponentType type2) {
   using V = ImageFormat::component_types_type;
   using T = V::value_type;
   return V(static_cast<T>(type0),
            static_cast<T>(type1),
            static_cast<T>(type2),
            static_cast<T>(ComponentType::none));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::component_types_type component_types(ComponentType type0, ComponentType type1, ComponentType type2, ComponentType type3) {
   using V = ImageFormat::component_types_type;
   using T = V::value_type;
   return V(static_cast<T>(type0),
            static_cast<T>(type1),
            static_cast<T>(type2),
            static_cast<T>(type3));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::component_types_type component_types(std::initializer_list<ComponentType> types) {
   assert(types.size() <= 4);
   using V = ImageFormat::component_types_type;
   using T = V::value_type;
   V vec(static_cast<T>(ComponentType::none));
   glm::length_t i = 0;
   for (ComponentType type : types) {
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
   V vec(static_cast<T>(Swizzle::zero),
         static_cast<T>(Swizzle::zero),
         static_cast<T>(Swizzle::zero),
         static_cast<T>(Swizzle::one));
   glm::length_t i = 0;
   for (Swizzle s : swizzles) {
      vec[i++] = static_cast<T>(s);
   }
   return vec;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_r() {
   return swizzles(Swizzle::red);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_rrr() {
   return swizzles(Swizzle::red, Swizzle::red, Swizzle::red);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_rg() {
   return swizzles(Swizzle::red, Swizzle::green);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_rgb() {
   return swizzles(Swizzle::red, Swizzle::green, Swizzle::blue);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_bgr() {
   return swizzles(Swizzle::blue, Swizzle::green, Swizzle::red);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_abg() {
   return swizzles(Swizzle::alpha, Swizzle::blue, Swizzle::green);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_rgba() {
   return swizzles(Swizzle::red, Swizzle::green, Swizzle::blue, Swizzle::alpha);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_bgra() {
   return swizzles(Swizzle::blue, Swizzle::green, Swizzle::red, Swizzle::alpha);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_abgr() {
   return swizzles(Swizzle::alpha, Swizzle::blue, Swizzle::green, Swizzle::red);
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzles_type swizzles_argb() {
   return swizzles(Swizzle::alpha, Swizzle::red, Swizzle::green, Swizzle::blue);
}

} // be::gfx::tex
