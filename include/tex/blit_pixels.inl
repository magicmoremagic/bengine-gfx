#if !defined(BE_GFX_TEX_BLIT_PIXELS_HPP_) && !defined(DOXYGEN)
#include "blit_pixels.hpp"
#elif !defined(BE_GFX_TEX_BLIT_PIXELS_INL_)
#define BE_GFX_TEX_BLIT_PIXELS_INL_

namespace be::gfx::tex {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_by_pixels(const SourceImageView& src, DestImageView& dest) {
   const std::size_t size = block_pixel_size(src.format().packing());
   const std::size_t src_plane_span = src.plane_span();
   const std::size_t dest_plane_span = dest.plane_span();
   const std::size_t src_line_span = src.line_span();
   const std::size_t dest_line_span = dest.line_span();
   const std::size_t src_block_span = src.block_span();
   const std::size_t dest_block_span = dest.block_span();

   const ivec3 src_block_dim = src.block_dim();
   ivec3 src_block_coord;

   const ivec3 dest_block_dim = dest.block_dim();
   ivec3 dest_block_coord;

   const UC* src_plane_ptr = src.data();
   UC* dest_plane_ptr = dest.data();

   const ivec3 dim = src.dim();
   ivec3 pc;
   for (pc.z = 0; pc.z < dim.z; ++pc.z) {
      const UC* src_line_ptr = src_plane_ptr;
      UC* dest_line_ptr = dest_plane_ptr;

      for (pc.y = 0; pc.y < dim.y; ++pc.y) {
         const UC* src_block_ptr = src_line_ptr;
         UC* dest_block_ptr = dest_line_ptr;

         for (pc.x = 0; pc.x < dim.x; ++pc.x) {
            const UC* src_ptr = src_block_ptr + ((src_block_coord.z * src_block_dim.y + src_block_coord.y) * src_block_dim.x + src_block_coord.x) * size;
            UC* dest_ptr = dest_block_ptr + ((dest_block_coord.z * dest_block_dim.y + dest_block_coord.y) * dest_block_dim.x + dest_block_coord.x) * size;

            std::memcpy(dest_ptr, src_ptr, size);

            ++src_block_coord.x;
            if (src_block_coord.x >= src_block_dim.x) {
               src_block_ptr += src_block_span;
               src_block_coord.x = 0;
            }

            ++dest_block_coord.x;
            if (dest_block_coord.x >= dest_block_dim.x) {
               dest_block_ptr += dest_block_span;
               dest_block_coord.x = 0;
            }
         }

         ++src_block_coord.y;
         if (src_block_coord.y >= src_block_dim.y) {
            src_line_ptr += src_line_span;
            src_block_coord.y = 0;
         }

         ++dest_block_coord.y;
         if (dest_block_coord.y >= dest_block_dim.y) {
            dest_line_ptr += dest_line_span;
            dest_block_coord.y = 0;
         }
      }

      ++src_block_coord.z;
      if (src_block_coord.z >= src_block_dim.z) {
         src_plane_ptr += src_plane_span;
         src_block_coord.z = 0;
      }

      ++dest_block_coord.z;
      if (dest_block_coord.z >= dest_block_dim.z) {
         dest_plane_ptr += dest_plane_span;
         dest_block_coord.z = 0;
      }
   }
}

} // be::gfx::tex::detail

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void blit_pixels(const SourceImageView& src, DestImageView& dest) {
   assert(dest.data() + dest.size() <= src.data() || src.data() + src.size() <= dest.data());
   assert(dest.dim().x >= src.dim().x);
   assert(dest.dim().y >= src.dim().y);
   assert(dest.dim().z >= src.dim().z);
   ImageFormat sf = src.format();
   ImageFormat df = dest.format();

   if (is_compressed(df.packing())) {
      assert(sf == df);
      assert(src.dim().x == dest.dim().x || src.dim().x % sf.block_dim().x == 0);
      assert(src.dim().y == dest.dim().y || src.dim().y % sf.block_dim().y == 0);
      assert(src.dim().z == dest.dim().z || src.dim().z % sf.block_dim().z == 0);
      detail::memcpy_blit_compatible_blocks(src, dest);
   } else {
      // dest is uncompressed
      if (sf.premultiplied() == df.premultiplied() &&
          sf.colorspace() == df.colorspace() &&
          sf.swizzles() == df.swizzles() &&
          sf.field_types() == df.field_types() &&
          sf.components() == df.components() &&
          sf.packing() == df.packing()) {
         // formats are the same, with possible exception of block_dim and block_span
         // so we can memcpy pixels (or better) and don't need ConvertingPixelBlitter
         if (sf.block_dim() == df.block_dim() && (sf.block_dim() == ImageFormat::block_dim_type(1u) ||
             (src.dim().x == dest.dim().x || src.dim().x % sf.block_dim().x == 0) &&
             (src.dim().y == dest.dim().y || src.dim().y % sf.block_dim().y == 0) &&
             (src.dim().z == dest.dim().z || src.dim().z % sf.block_dim().z == 0))) {
            detail::memcpy_blit_compatible_blocks(src, dest);
         } else {
            detail::memcpy_blit_by_pixels(src, dest);
         }
      } else {
         // pixel formats differ; use ConvertingPixelBlitter
         if (src.dim().z == 1) {
            if (src.dim().y == 1) {
               ConvertingPixelBlitter<I32, I32, SourceImageView, DestImageView> blitter(src, dest);
               I32 dim = src.dim().x;
               for (I32 pc = 0; pc < dim; ++pc) {
                  blitter(pc, pc);
               }
            } else {
               ConvertingPixelBlitter<ivec2, ivec2, SourceImageView, DestImageView> blitter(src, dest);
               ivec3 dim = src.dim();
               ivec2 pc;
               for (pc.y = 0; pc.y < dim.y; ++pc.y) {
                  for (pc.x = 0; pc.x < dim.x; ++pc.x) {
                     blitter(pc, pc);
                  }
               }
            }
         } else {
            ConvertingPixelBlitter<ivec3, ivec3, SourceImageView, DestImageView> blitter(src, dest);
            ivec3 dim = src.dim();
            ivec3 pc;
            for (pc.z = 0; pc.z < dim.z; ++pc.z) {
               for (pc.y = 0; pc.y < dim.y; ++pc.y) {
                  for (pc.x = 0; pc.x < dim.x; ++pc.x) {
                     blitter(pc, pc);
                  }
               }
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void blit_pixels(const SourceImageView& src, ImageRegion src_region, DestImageView& dest, ImageRegion dest_region) {
   assert(src_region.extents().left() >= 0);
   assert(src_region.extents().bottom() >= 0);
   assert(src_region.extents().back() >= 0);
   assert(src_region.extents().right() <= src.dim().x);
   assert(src_region.extents().top() <= src.dim().y);
   assert(src_region.extents().front() <= src.dim().z);

   const ivec3 src_region_dim = region_dim(src_region);
   dest_region = subregion(dest_region, ibox { ivec3(), src_region_dim });

   assert(dest_region.extents().left() >= 0);
   assert(dest_region.extents().bottom() >= 0);
   assert(dest_region.extents().back() >= 0);
   assert(dest_region.extents().right() <= dest.dim().x);
   assert(dest_region.extents().top() <= dest.dim().y);
   assert(dest_region.extents().front() <= dest.dim().z);

   assert(dest.data() + dest.size() <= src.data() ||
          src.data() + src.size() <= dest.data() ||
          !src_region.extents().intersects(dest_region.extents()));

   ImageFormat sf = src.format();
   ImageFormat df = dest.format();

   if (is_compressed(df.packing())) {
      assert(sf == df);
      assert(src_region.basis_vec() == dest_region.basis_vec());
      assert(src_region.extents().left() % sf.block_dim().x == 0);
      assert(src_region.extents().right() % sf.block_dim().x == 0);
      assert(dest_region.extents().left() % sf.block_dim().x == 0);
      assert(src_region.extents().bottom() % sf.block_dim().y == 0);
      assert(src_region.extents().top() % sf.block_dim().y == 0);
      assert(dest_region.extents().bottom() % sf.block_dim().y == 0);
      assert(src_region.extents().back() % sf.block_dim().z == 0);
      assert(src_region.extents().front() % sf.block_dim().z == 0);
      assert(dest_region.extents().back() % sf.block_dim().z == 0);
      ivec3 block_dim(sf.block_dim());
      ibox src_block_extents { src_region.extents().offset / block_dim, src_region.extents().dim / block_dim };
      ibox dest_block_extents { dest_region.extents().offset / block_dim, dest_region.extents().dim / block_dim };
      detail::memcpy_blit_compatible_blocks(src, src_block_extents, dest, dest_block_extents);
   } else {
      // dest is uncompressed
      ibox src_extents = src_region.extents();
      ibox dest_extents = dest_region.extents();

      if (sf.premultiplied() == df.premultiplied() && sf.colorspace() == df.colorspace() && sf.swizzles() == df.swizzles() &&
          sf.field_types() == df.field_types() && sf.components() == df.components() && sf.packing() == df.packing()) {
         // formats are the same, with possible exception of block_dim and block_size
         // so we can memcpy pixels (or better) and don't need ConvertingPixelBlitter
         if (src_region.basis_vec() == dest_region.basis_vec() && sf.block_dim() == df.block_dim() && sf.block_size() == df.block_size()) {
            if (sf.block_dim() == ImageFormat::block_dim_type(1u)) {
               detail::memcpy_blit_compatible_blocks(src, src_extents, dest, dest_extents);
               return;
            } else if (src_extents.left()   % sf.block_dim().x == 0 && src_extents.right() % sf.block_dim().x == 0 && dest_extents.left() % sf.block_dim().x == 0 &&
                       src_extents.bottom() % sf.block_dim().y == 0 && src_extents.top()   % sf.block_dim().y == 0 && dest_extents.bottom() % sf.block_dim().y == 0 &&
                       src_extents.back()   % sf.block_dim().z == 0 && src_extents.front() % sf.block_dim().z == 0 && dest_extents.back() % sf.block_dim().z == 0) {
               ivec3 block_dim(sf.block_dim());
               ibox src_block_extents { src_extents.offset / block_dim, src_extents.dim / block_dim };
               ibox dest_block_extents { dest_extents.offset / block_dim, dest_extents.dim / block_dim };
               detail::memcpy_blit_compatible_blocks(src, src_block_extents, dest, dest_block_extents);
               return;
            }
         }
         const std::size_t size = block_pixel_size(sf.packing());

         if (src_extents.offset.z == 0 && src_extents.dim.z == 1 && dest_extents.offset.z == 0 && dest_extents.dim.z == 1) {
            if (src_extents.offset.y == 0 && src_extents.dim.y == 1 && dest_extents.offset.y == 0 && dest_extents.dim.y == 1) {
               // lineal blit
               auto src_offset_func = pixel_offset_func<I32>(src);
               auto dest_offset_func = pixel_offset_func<I32>(dest);
               ivec3 rc;
               for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
                  for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
                     for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                        const void* src_ptr = src.data() + src_offset_func(src, region_to_image(src_region, rc).x);
                        void* dest_ptr = dest.data() + dest_offset_func(dest, region_to_image(dest_region, rc).x);
                        std::memcpy(dest_ptr, src_ptr, size);
                     }
                  }
               }
            } else {
               // planar blit
               auto src_offset_func = pixel_offset_func<ivec2>(src);
               auto dest_offset_func = pixel_offset_func<ivec2>(dest);
               ivec3 rc;
               for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
                  for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
                     for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                        const void* src_ptr = src.data() + src_offset_func(src, ivec2(region_to_image(src_region, rc)));
                        void* dest_ptr = dest.data() + dest_offset_func(dest, ivec2(region_to_image(dest_region, rc)));
                        std::memcpy(dest_ptr, src_ptr, size);
                     }
                  }
               }
            }
         } else {
            // volumetric blit
            ivec3 rc;
            auto src_offset_func = pixel_offset_func<ivec3>(src);
            auto dest_offset_func = pixel_offset_func<ivec3>(dest);
            for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
               for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
                  for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                     const void* src_ptr = src.data() + src_offset_func(src, region_to_image(src_region, rc));
                     void* dest_ptr = dest.data() + dest_offset_func(dest, region_to_image(dest_region, rc));
                     std::memcpy(dest_ptr, src_ptr, size);
                  }
               }
            }
         }
      } else {
         // pixel formats differ; use ConvertingPixelBlitter
         if (src_extents.offset.z == 0 && src_extents.dim.z == 1 && dest_extents.offset.z == 0 && dest_extents.dim.z == 1) {
            if (src_extents.offset.y == 0 && src_extents.dim.y == 1 && dest_extents.offset.y == 0 && dest_extents.dim.y == 1) {
               // lineal blit
               ConvertingPixelBlitter<I32, I32, SourceImageView, DestImageView> blitter(src, dest);
               ivec3 rc;
               for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
                  for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
                     for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                        blitter(region_to_image(src_region, rc).x, region_to_image(dest_region, rc).x);
                     }
                  }
               }
            } else {
               // planar blit
               ConvertingPixelBlitter<ivec2, ivec2, SourceImageView, DestImageView> blitter(src, dest);
               ivec3 rc;
               for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
                  for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
                     for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                        blitter(ivec2(region_to_image(src_region, rc)), ivec2(region_to_image(dest_region, rc)));
                     }
                  }
               }
            }
         } else {
            // volumetric blit
            ConvertingPixelBlitter<ivec3, ivec3, SourceImageView, DestImageView> blitter(src, dest);
            ivec3 rc;
            for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
               for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
                  for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                     blitter(region_to_image(src_region, rc), region_to_image(dest_region, rc));
                  }
               }
            }
         }
      }
   }
}

} // be::gfx::tex

#endif
