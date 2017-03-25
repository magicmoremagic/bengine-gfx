#if !defined(BE_GFX_IMAGE_PIXEL_ACCESS_HPP_) && !defined(DOXYGEN)
#include "image_pixel_access.hpp"
#elif !defined(BE_GFX_IMAGE_PIXEL_ACCESS_INL_)
#define BE_GFX_IMAGE_PIXEL_ACCESS_INL_

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView, U8 Dimension, bool IsSimple>
struct image_pixel_access_uncompressed { };

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
struct image_pixel_access_uncompressed<T, ImageView, 1, true> {
   static T get(const ImageView& image, I32 pixel_coord) {
      T pixel;
      assert(pixel_coord >= 0);
      assert(pixel_coord < image.dim_blocks().x);
      const UC* ptr = image.data() +
         pixel_coord * image.block_size();
      std::memcpy(&pixel, ptr, sizeof(T));
      return pixel;
   }
   static void put(ImageView& image, I32 pixel_coord, T pixel) {
      assert(pixel_coord >= 0);
      assert(pixel_coord < image.dim_blocks().x);
      UC* ptr = image.data() +
         pixel_coord * image.block_size();
      std::memcpy(ptr, &pixel, sizeof(T));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
struct image_pixel_access_uncompressed<T, ImageView, 2, true> {
   static T get(const ImageView& image, ivec2 pixel_coord) {
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
   static void put(ImageView& image, ivec2 pixel_coord, T pixel) {
      assert(pixel_coord.x >= 0);
      assert(pixel_coord.y >= 0);
      assert(pixel_coord.x < image.dim_blocks().x);
      assert(pixel_coord.y < image.dim_blocks().y);
      UC* ptr = image.data() +
         pixel_coord.y * image.line_span() +
         pixel_coord.x * image.block_size();
      std::memcpy(ptr, &pixel, sizeof(T));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
struct image_pixel_access_uncompressed<T, ImageView, 3, true> {
   static T get(const ImageView& image, ivec3 pixel_coord) {
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
   static void put(ImageView& image, ivec3 pixel_coord, T pixel) {
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
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
struct image_pixel_access_uncompressed<T, ImageView, 1, false> {
   static T get(const ImageView& image, I32 pixel_coord) {
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
   static void put(ImageView& image, I32 pixel_coord, T pixel) {
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
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
struct image_pixel_access_uncompressed<T, ImageView, 2, false> {
   static T get(const ImageView& image, ivec2 pixel_coord) {
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
   static void put(ImageView& image, ivec2 pixel_coord, T pixel) {
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
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
struct image_pixel_access_uncompressed<T, ImageView, 3, false> {
   static T get(const ImageView& image, ivec3 pixel_coord) {
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
   static void put(ImageView& image, ivec3 pixel_coord, T pixel) {
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
};

} // be::gfx::detail

/*!! register_template_string([[

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixel`dim_text`Func<T, ImageView> get_pixel_`string.lower(dim_text)`_func(const ImageView& image) {
   using dim_type = glm::vec<`i`, ImageFormat::block_size_type>;
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
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, `i`, true>::get;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, `i`, false>::get;
   }
}
]], 'get_pixel')

register_template_string([[

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixel`dim_text`Func<T, ImageView> put_pixel_`string.lower(dim_text)`_func(const ImageView& image) {
   using dim_type = glm::vec<`i`, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, `i`, true>::put;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, `i`, false>::put;
   }
}
]], 'put_pixel')

write_template('get_pixel', { i = 1, dim_text = 'Lineal' })
write_template('get_pixel', { i = 2, dim_text = 'Planar' })
write_template('get_pixel', { i = 3, dim_text = 'Volumetric' })

write_template('put_pixel', { i = 1, dim_text = 'Lineal' })
write_template('put_pixel', { i = 2, dim_text = 'Planar' })
write_template('put_pixel', { i = 3, dim_text = 'Volumetric' })
!! 157 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelLinealFunc<T, ImageView> get_pixel_lineal_func(const ImageView& image) {
   using dim_type = glm::vec<1, ImageFormat::block_size_type>;
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
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, 1, true>::get;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, 1, false>::get;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelPlanarFunc<T, ImageView> get_pixel_planar_func(const ImageView& image) {
   using dim_type = glm::vec<2, ImageFormat::block_size_type>;
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
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, 2, true>::get;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, 2, false>::get;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelVolumetricFunc<T, ImageView> get_pixel_volumetric_func(const ImageView& image) {
   using dim_type = glm::vec<3, ImageFormat::block_size_type>;
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
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, 3, true>::get;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, 3, false>::get;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelLinealFunc<T, ImageView> put_pixel_lineal_func(const ImageView& image) {
   using dim_type = glm::vec<1, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, 1, true>::put;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, 1, false>::put;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelPlanarFunc<T, ImageView> put_pixel_planar_func(const ImageView& image) {
   using dim_type = glm::vec<2, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, 2, true>::put;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, 2, false>::put;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelVolumetricFunc<T, ImageView> put_pixel_volumetric_func(const ImageView& image) {
   using dim_type = glm::vec<3, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, 3, true>::put;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, 3, false>::put;
   }
}

/* ######################### END OF GENERATED CODE ######################### */

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
