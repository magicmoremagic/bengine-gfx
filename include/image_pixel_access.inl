#if !defined(BE_GFX_IMAGE_PIXEL_ACCESS_HPP_) && !defined(DOXYGEN)
#include "image_pixel_access.hpp"
#elif !defined(BE_GFX_IMAGE_PIXEL_ACCESS_INL_)
#define BE_GFX_IMAGE_PIXEL_ACCESS_INL_

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel_simple_1(const ImageView& image, I32 pixel_coord) {
   T pixel;
   assert(pixel_coord >= 0);
   assert(pixel_coord < image.dim_blocks().x);
   const UC* ptr = image.data() +
      pixel_coord * image.block_size();
   std::memcpy(&pixel, ptr, sizeof(T));
   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel_simple_2(const ImageView& image, ivec2 pixel_coord) {
   T pixel;
   assert(pixel_coord.x >= 0);
   assert(pixel_coord.y >= 0);
   assert(pixel_coord.x < image.dim_blocks().x);
   assert(pixel_coord.y < image.dim_blocks().y);
   const UC* ptr = image.data() +
      pixel_coord.y * image.line_span() +
      pixel_coord.x * image.block_size();
   std::memcpy(&pixel, ptr, sizeof(T));
   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel_simple_3(const ImageView& image, ivec3 pixel_coord) {
   T pixel;
   assert(pixel_coord.x >= 0);
   assert(pixel_coord.y >= 0);
   assert(pixel_coord.z >= 0);
   assert(pixel_coord.x < image.dim_blocks().x);
   assert(pixel_coord.y < image.dim_blocks().y);
   assert(pixel_coord.z < image.dim_blocks().z);
   const UC* ptr = image.data() +
      pixel_coord.z * image.plane_span() +
      pixel_coord.y * image.line_span() +
      pixel_coord.x * image.block_size();
   std::memcpy(&pixel, ptr, sizeof(T));
   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel_packed_block_1(const ImageView& image, I32 pixel_coord) {
   T pixel;
   I32 block_coord = pixel_coord / image.block_dim().x;
   pixel_coord -= block_coord * image.block_dim().x;
   assert(block_coord >= 0);
   assert(block_coord < image.dim_blocks().x);
   assert(pixel_coord >= 0);
   const UC* ptr = image.data() +
      block_coord * image.block_size() +
      pixel_coord * image_block_pixel_size(image.format().packing());
   std::memcpy(&pixel, ptr, sizeof(T));
   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel_packed_block_2(const ImageView& image, ivec2 pixel_coord) {
   T pixel;
   ivec2 block_dim = image.block_dim();
   ivec2 block_coord = pixel_coord / block_dim;
   pixel_coord -= block_coord * block_dim;
   assert(block_coord.x >= 0);
   assert(block_coord.y >= 0);
   assert(block_coord.x < image.dim_blocks().x);
   assert(block_coord.y < image.dim_blocks().y);
   assert(pixel_coord.x >= 0);
   assert(pixel_coord.y >= 0);
   const UC* ptr = image.data() +
      block_coord.y * image.line_span() +
      block_coord.x * image.block_size() +
      (pixel_coord.y * block_dim.x + pixel_coord.x) *
      image_block_pixel_size(image.format().packing());
   std::memcpy(&pixel, ptr, sizeof(T));
   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel_packed_block_3(const ImageView& image, ivec3 pixel_coord) {
   T pixel;
   ivec3 block_dim = image.block_dim();
   ivec3 block_coord = pixel_coord / block_dim;
   pixel_coord -= block_coord * block_dim;
   assert(block_coord.x >= 0);
   assert(block_coord.y >= 0);
   assert(block_coord.z >= 0);
   assert(block_coord.x < image.dim_blocks().x);
   assert(block_coord.y < image.dim_blocks().y);
   assert(block_coord.z < image.dim_blocks().z);
   assert(pixel_coord.x >= 0);
   assert(pixel_coord.y >= 0);
   assert(pixel_coord.z >= 0);
   const UC* ptr = image.data() +
      block_coord.z * image.plane_span() +
      block_coord.y * image.line_span() +
      block_coord.x * image.block_size() +
      ((pixel_coord.z * block_dim.y + pixel_coord.y) * block_dim.x + pixel_coord.x) *
      image_block_pixel_size(image.format().packing());
   std::memcpy(&pixel, ptr, sizeof(T));
   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel_simple_1(ImageView& image, I32 pixel_coord, T pixel) {
   assert(pixel_coord >= 0);
   assert(pixel_coord < image.dim_blocks().x);
   UC* ptr = image.data() +
      pixel_coord * image.block_size();
   std::memcpy(ptr, &pixel, sizeof(T));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel_simple_2(ImageView& image, ivec2 pixel_coord, T pixel) {
   assert(pixel_coord.x >= 0);
   assert(pixel_coord.y >= 0);
   assert(pixel_coord.x < image.dim_blocks().x);
   assert(pixel_coord.y < image.dim_blocks().y);
   UC* ptr = image.data() +
      pixel_coord.y * image.line_span() +
      pixel_coord.x * image.block_size();
   std::memcpy(ptr, &pixel, sizeof(T));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel_simple_3(ImageView& image, ivec3 pixel_coord, T pixel) {
   assert(pixel_coord.x >= 0);
   assert(pixel_coord.y >= 0);
   assert(pixel_coord.z >= 0);
   assert(pixel_coord.x < image.dim_blocks().x);
   assert(pixel_coord.y < image.dim_blocks().y);
   assert(pixel_coord.z < image.dim_blocks().z);
   UC* ptr = image.data() +
      pixel_coord.z * image.plane_span() +
      pixel_coord.y * image.line_span() +
      pixel_coord.x * image.block_size();
   std::memcpy(ptr, &pixel, sizeof(T));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel_packed_block_1(ImageView& image, I32 pixel_coord, T pixel) {
   I32 block_coord = pixel_coord / image.block_dim().x;
   pixel_coord -= block_coord * image.block_dim().x;
   assert(block_coord >= 0);
   assert(block_coord < image.dim_blocks().x);
   assert(pixel_coord >= 0);
   UC* ptr = image.data() +
      block_coord * image.block_size() +
      pixel_coord * image_block_pixel_size(image.format().packing());
   std::memcpy(ptr, &pixel, sizeof(T));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel_packed_block_2(ImageView& image, ivec2 pixel_coord, T pixel) {
   ivec2 block_dim = image.block_dim();
   ivec2 block_coord = pixel_coord / block_dim;
   pixel_coord -= block_coord * block_dim;
   assert(block_coord.x >= 0);
   assert(block_coord.y >= 0);
   assert(block_coord.x < image.dim_blocks().x);
   assert(block_coord.y < image.dim_blocks().y);
   assert(pixel_coord.x >= 0);
   assert(pixel_coord.y >= 0);
   UC* ptr = image.data() +
      block_coord.y * image.line_span() +
      block_coord.x * image.block_size() +
      (pixel_coord.y * block_dim.x + pixel_coord.x) *
      image_block_pixel_size(image.format().packing());
   std::memcpy(ptr, &pixel, sizeof(T));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel_packed_block_3(ImageView& image, ivec3 pixel_coord, T pixel) {
   ivec3 block_dim = image.block_dim();
   ivec3 block_coord = pixel_coord / block_dim;
   pixel_coord -= block_coord * block_dim;
   assert(block_coord.x >= 0);
   assert(block_coord.y >= 0);
   assert(block_coord.z >= 0);
   assert(block_coord.x < image.dim_blocks().x);
   assert(block_coord.y < image.dim_blocks().y);
   assert(block_coord.z < image.dim_blocks().z);
   assert(pixel_coord.x >= 0);
   assert(pixel_coord.y >= 0);
   assert(pixel_coord.z >= 0);
   UC* ptr = image.data() +
      block_coord.z * image.plane_span() +
      block_coord.y * image.line_span() +
      block_coord.x * image.block_size() +
      ((pixel_coord.z * block_dim.y + pixel_coord.y) * block_dim.x + pixel_coord.x) *
      image_block_pixel_size(image.format().packing());
   std::memcpy(ptr, &pixel, sizeof(T));
}

} // be::gfx::detail

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelLinealFunc<T, ImageView> get_pixel_lineal_func(const ImageView& image) {
   assert(image);
   if (is_compressed(image.format().packing())) {
      switch (image.format().packing()) {
         case ImageBlockPacking::c_astc:
         case ImageBlockPacking::c_atc:
         case ImageBlockPacking::c_bptc:
         case ImageBlockPacking::c_eac:
         case ImageBlockPacking::c_etc1:
         case ImageBlockPacking::c_etc2:
         case ImageBlockPacking::c_pvrtc1:
         case ImageBlockPacking::c_pvrtc2:
         case ImageBlockPacking::c_s3tc1:
         case ImageBlockPacking::c_s3tc2:
         case ImageBlockPacking::c_s3tc3:
         case ImageBlockPacking::c_s3tc4:
         case ImageBlockPacking::c_s3tc5:
            // TODO
            break;
         default:
            assert(false);
            break;
      }
      return nullptr;
   } else if (image.block_dim().x == 1) {
      assert(sizeof(T) <= image.block_size());
      return detail::get_pixel_simple_1<T, ImageView>;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::get_pixel_packed_block_1<T, ImageView>;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelPlanarFunc<T, ImageView> get_pixel_planar_func(const ImageView& image) {
   assert(image);
   if (is_compressed(image.format().packing())) {
      switch (image.format().packing()) {
         case ImageBlockPacking::c_astc:
         case ImageBlockPacking::c_atc:
         case ImageBlockPacking::c_bptc:
         case ImageBlockPacking::c_eac:
         case ImageBlockPacking::c_etc1:
         case ImageBlockPacking::c_etc2:
         case ImageBlockPacking::c_pvrtc1:
         case ImageBlockPacking::c_pvrtc2:
         case ImageBlockPacking::c_s3tc1:
         case ImageBlockPacking::c_s3tc2:
         case ImageBlockPacking::c_s3tc3:
         case ImageBlockPacking::c_s3tc4:
         case ImageBlockPacking::c_s3tc5:
            // TODO
            break;
         default:
            assert(false);
            break;
      }
      return nullptr;
   } else if (image.block_dim().x == 1 && image.block_dim().y == 1) {
      assert(sizeof(T) <= image.block_size());
      return detail::get_pixel_simple_2<T, ImageView>;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::get_pixel_packed_block_2<T, ImageView>;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelVolumetricFunc<T, ImageView> get_pixel_volumetric_func(const ImageView& image) {
   assert(image);
   if (is_compressed(image.format().packing())) {
      switch (image.format().packing()) {
         case ImageBlockPacking::c_astc:
         case ImageBlockPacking::c_atc:
         case ImageBlockPacking::c_bptc:
         case ImageBlockPacking::c_eac:
         case ImageBlockPacking::c_etc1:
         case ImageBlockPacking::c_etc2:
         case ImageBlockPacking::c_pvrtc1:
         case ImageBlockPacking::c_pvrtc2:
         case ImageBlockPacking::c_s3tc1:
         case ImageBlockPacking::c_s3tc2:
         case ImageBlockPacking::c_s3tc3:
         case ImageBlockPacking::c_s3tc4:
         case ImageBlockPacking::c_s3tc5:
            // TODO
            break;
         default:
            assert(false);
            break;
      }
      return nullptr;
   } else if (image.block_dim() == ImageFormat::block_dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::get_pixel_simple_3<T, ImageView>;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::get_pixel_packed_block_3<T, ImageView>;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelLinealFunc<T, ImageView> put_pixel_lineal_func(const ImageView& image) {
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (image.block_dim().x == 1) {
      assert(sizeof(T) <= image.block_size());
      return detail::put_pixel_simple_1<T, ImageView>;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::put_pixel_packed_block_1<T, ImageView>;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelPlanarFunc<T, ImageView> put_pixel_planar_func(const ImageView& image) {
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (image.block_dim().x == 1 && image.block_dim().y == 1) {
      assert(sizeof(T) <= image.block_size());
      return detail::put_pixel_simple_2<T, ImageView>;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::put_pixel_packed_block_2<T, ImageView>;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelVolumetricFunc<T, ImageView> put_pixel_volumetric_func(const ImageView& image) {
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (image.block_dim() == ImageFormat::block_dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::put_pixel_simple_3<T, ImageView>;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::put_pixel_packed_block_3<T, ImageView>;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel(const ImageView& image, I32 pixel_coord) {
   return get_pixel_lineal_func<T, ImageView>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel(const ImageView& image, ivec2 pixel_coord) {
   return get_pixel_planar_func<T, ImageView>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
T get_pixel(const ImageView& image, ivec3 pixel_coord) {
   return get_pixel_volumetric_func<T, ImageView>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel(ImageView& image, I32 pixel_coord, T pixel) {
   put_pixel_lineal_func<T, ImageView>(image)(image, pixel_coord, pixel);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel(ImageView& image, ivec2 pixel_coord, T pixel) {
   put_pixel_planar_func<T, ImageView>(image)(image, pixel_coord, pixel);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
void put_pixel(ImageView& image, ivec3 pixel_coord, T pixel) {
   put_pixel_volumetric_func<T, ImageView>(image)(image, pixel_coord, pixel);
}

} // be::gfx

#endif
