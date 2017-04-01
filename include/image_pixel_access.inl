#if !defined(BE_GFX_IMAGE_PIXEL_ACCESS_HPP_) && !defined(DOXYGEN)
#include "image_pixel_access.hpp"
#elif !defined(BE_GFX_IMAGE_PIXEL_ACCESS_INL_)
#define BE_GFX_IMAGE_PIXEL_ACCESS_INL_

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView, typename Coord, bool IsSimple, glm::length_t Dimension = t::vector_components<Coord>::value>
struct image_pixel_access_uncompressed { };

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView, typename Coord>
struct image_pixel_access_uncompressed<T, ImageView, Coord, true, 1> {
   static T get(const ImageView& image, Coord pixel_coord) {
      T pixel;
      assert(pixel_coord >= 0);
      assert(pixel_coord < image.dim_blocks().x);
      const UC* ptr = image.data() +
         pixel_coord * image.block_size();
      std::memcpy(&pixel, ptr, sizeof(T));
      return pixel;
   }
   static void put(ImageView& image, Coord pixel_coord, T pixel) {
      assert(pixel_coord >= 0);
      assert(pixel_coord < image.dim_blocks().x);
      UC* ptr = image.data() +
         pixel_coord * image.block_size();
      std::memcpy(ptr, &pixel, sizeof(T));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView, typename Coord>
struct image_pixel_access_uncompressed<T, ImageView, Coord, true, 2> {
   static T get(const ImageView& image, Coord pixel_coord) {
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
   static void put(ImageView& image, Coord pixel_coord, T pixel) {
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
template <typename T, typename ImageView, typename Coord>
struct image_pixel_access_uncompressed<T, ImageView, Coord, true, 3> {
   static T get(const ImageView& image, Coord pixel_coord) {
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
   static void put(ImageView& image, Coord pixel_coord, T pixel) {
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
template <typename T, typename ImageView, typename Coord>
struct image_pixel_access_uncompressed<T, ImageView, Coord, false, 1> {
   static T get(const ImageView& image, Coord pixel_coord) {
      T pixel;
      Coord block_coord = pixel_coord / image.block_dim().x;
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
   static void put(ImageView& image, Coord pixel_coord, T pixel) {
      Coord block_coord = pixel_coord / image.block_dim().x;
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
template <typename T, typename ImageView, typename Coord>
struct image_pixel_access_uncompressed<T, ImageView, Coord, false, 2> {
   static T get(const ImageView& image, Coord pixel_coord) {
      T pixel;
      Coord block_dim = image.block_dim();
      Coord block_coord = pixel_coord / block_dim;
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
   static void put(ImageView& image, Coord pixel_coord, T pixel) {
      Coord block_dim = image.block_dim();
      Coord block_coord = pixel_coord / block_dim;
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
template <typename T, typename ImageView, typename Coord>
struct image_pixel_access_uncompressed<T, ImageView, Coord, false, 3> {
   static T get(const ImageView& image, Coord pixel_coord) {
      T pixel;
      Coord block_dim = image.block_dim();
      Coord block_coord = pixel_coord / block_dim;
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
   static void put(ImageView& image, Coord pixel_coord, T pixel) {
      Coord block_dim = image.block_dim();
      Coord block_coord = pixel_coord / block_dim;
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

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView, typename Coord>
GetImagePixelFunc<T, ImageView, Coord> get_pixel_func(const ImageView& image) {
   using dim_type = glm::vec<t::vector_components<Coord>::value, ImageFormat::block_size_type>;
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
      return detail::image_pixel_access_uncompressed<T, ImageView, Coord, true>::get;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, Coord, false>::get;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView, typename Coord>
T get_pixel(const ImageView& image, Coord pixel_coord) {
   return get_pixel_func<T, ImageView, Coord>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelLinealFunc<T, ImageView> get_pixel_lineal_func(const ImageView& image) {
   return get_pixel_func<T, ImageView, I32>(image);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelPlanarFunc<T, ImageView> get_pixel_planar_func(const ImageView& image) {
   return get_pixel_func<T, ImageView, ivec2>(image);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
GetImagePixelVolumetricFunc<T, ImageView> get_pixel_volumetric_func(const ImageView& image) {
   return get_pixel_func<T, ImageView, ivec3>(image);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView, typename Coord>
PutImagePixelFunc<T, ImageView, Coord> put_pixel_func(const ImageView& image) {
   using dim_type = glm::vec<t::vector_components<Coord>::value, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      assert(sizeof(T) <= image.block_size());
      return detail::image_pixel_access_uncompressed<T, ImageView, Coord, true>::put;
   } else {
      assert(sizeof(T) <= image_block_pixel_size(image.format().packing()));
      return detail::image_pixel_access_uncompressed<T, ImageView, Coord, false>::put;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView, typename Coord>
void put_pixel(ImageView& image, Coord pixel_coord, T pixel) {
   put_pixel_func<T, ImageView, Coord>(image)(image, pixel_coord, pixel);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelLinealFunc<T, ImageView> put_pixel_lineal_func(const ImageView& image) {
   return put_pixel_func<T, ImageView, I32>(image);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelPlanarFunc<T, ImageView> put_pixel_planar_func(const ImageView& image) {
   return put_pixel_func<T, ImageView, ivec2>(image);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ImageView>
PutImagePixelVolumetricFunc<T, ImageView> put_pixel_volumetric_func(const ImageView& image) {
   return put_pixel_func<T, ImageView, ivec3>(image);
}

} // be::gfx

#endif
