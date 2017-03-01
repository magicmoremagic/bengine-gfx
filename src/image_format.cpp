#include "pch.hpp"
#include "image_format.hpp"

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ImageFormat() 
   : block_size_(0),
     components_(0),
     colorspace_(Colorspace::none) { }

///////////////////////////////////////////////////////////////////////////////
ImageFormat::ImageFormat(block_size_type block_size,
                         block_dim_type block_dim,
                         U8 components,
                         bpc_vec_type bits,
                         swizzle_vec_type swizzle,
                         Colorspace colorspace)
   : block_size_(block_size),
     block_dim_(block_dim),
     components_(components),
     bits_(bits),
     swizzle_(swizzle),
     colorspace_(colorspace) {
   assert(block_size > 0);
   assert(block_dim.x > 0);
   assert(block_dim.y > 0);
   assert(block_dim.z > 0);
   assert(components > 0);
   assert(is_valid(static_cast<Swizzle>(swizzle.r)));
   assert(is_valid(static_cast<Swizzle>(swizzle.g)));
   assert(is_valid(static_cast<Swizzle>(swizzle.b)));
   assert(is_valid(static_cast<Swizzle>(swizzle.a)));
   assert(is_valid(colorspace));
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::operator bool() const {
   return block_size_ > 0;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::block_size_type ImageFormat::block_size() const {
   return block_size_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::block_dim_type ImageFormat::block_dim() const {
   return block_dim_;
}

///////////////////////////////////////////////////////////////////////////////
U8 ImageFormat::components() const {
   return components_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::bpc_vec_type ImageFormat::bits() const {
   return bits_;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormat::swizzle_vec_type ImageFormat::swizzle() const {
   return swizzle_;
}

///////////////////////////////////////////////////////////////////////////////
Colorspace ImageFormat::colorspace() const {
   return colorspace_;
}

} // be::gfx
