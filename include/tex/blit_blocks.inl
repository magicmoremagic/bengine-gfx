#if !defined(BE_GFX_TEX_BLIT_BLOCKS_HPP_) && !defined(DOXYGEN)
#include "blit_blocks.hpp"
#elif !defined(BE_GFX_TEX_BLIT_BLOCKS_INL_)
#define BE_GFX_TEX_BLIT_BLOCKS_INL_

namespace be::gfx::tex {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_level(const SourceImageView& src, DestImageView& dest) {
   const std::size_t size = src.plane_span() * (std::size_t)src.dim_blocks().z;
   assert(src.size() >= size);
   assert(dest.size() >= size);
   std::memcpy(dest.data(), src.data(), size);
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_plane_range(const SourceImageView& src, ibox src_block_extents, DestImageView& dest, ibox dest_block_extents) {
   const std::size_t size = src.plane_span() * (std::size_t)src_block_extents.dim.z;
   const std::size_t src_offset = src.plane_span() * (std::size_t)src_block_extents.offset.z;
   const std::size_t dest_offset = dest.plane_span() * (std::size_t)dest_block_extents.offset.z;
   assert(src.size() >= src_offset + size);
   assert(dest.size() >= dest_offset + size);

   const UC* src_ptr = src.data() + src_offset;
   UC* dest_ptr = dest.data() + dest_offset;

   std::memcpy(dest_ptr, src_ptr, size);
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_by_planes(const SourceImageView& src, DestImageView& dest) {
   const std::size_t size = src.line_span() * (std::size_t)src.dim_blocks().y;
   const std::size_t src_plane_span = src.plane_span();
   const std::size_t dest_plane_span = dest.plane_span();
   assert(src_plane_span >= size);
   assert(dest_plane_span >= size);

   const UC* src_ptr = src.data();
   UC* dest_ptr = dest.data();

   const I32 dim = src.dim_blocks().z;
   for (I32 z = 0; z < dim; ++z) {
      std::memcpy(dest_ptr, src_ptr, size);
      src_ptr += src_plane_span;
      dest_ptr += dest_plane_span;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_by_plane_segments(const SourceImageView& src, ibox src_block_extents, DestImageView& dest, ibox dest_block_extents) {
   const std::size_t size = src.line_span() * (std::size_t)src_block_extents.dim.y;
   const std::size_t src_plane_span = src.plane_span();
   const std::size_t dest_plane_span = dest.plane_span();
   const std::size_t src_line_offset = src.line_span() * (std::size_t)src_block_extents.offset.y;
   const std::size_t dest_line_offset = dest.line_span() * (std::size_t)dest_block_extents.offset.y;
   assert(src_plane_span >= src_line_offset + size);
   assert(dest_plane_span >= dest_line_offset + size);

   const std::size_t src_plane_offset = src.plane_span() * (std::size_t)src_block_extents.offset.z;
   const std::size_t dest_plane_offset = dest.plane_span() * (std::size_t)dest_block_extents.offset.z;

   const UC* src_ptr = src.data() + src_plane_offset + src_line_offset;
   UC* dest_ptr = dest.data() + dest_plane_offset + dest_line_offset;

   const I32 dim = src_block_extents.dim.z;
   for (I32 z = 0; z < dim; ++z) {
      std::memcpy(dest_ptr, src_ptr, size);
      src_ptr += src_plane_span;
      dest_ptr += dest_plane_span;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_by_lines(const SourceImageView& src, DestImageView& dest) {
   const std::size_t size = src.block_span() * (std::size_t)src.dim_blocks().x;
   const std::size_t src_plane_span = src.plane_span();
   const std::size_t dest_plane_span = dest.plane_span();
   const std::size_t src_line_span = src.line_span();
   const std::size_t dest_line_span = dest.line_span();
   assert(src_line_span >= size);
   assert(dest_line_span >= size);

   const UC* src_plane_ptr = src.data();
   UC* dest_plane_ptr = dest.data();

   const ivec3 dim = src.dim_blocks();
   for (I32 z = 0; z < dim.z; ++z) {
      const UC* src_ptr = src_plane_ptr;
      UC* dest_ptr = dest_plane_ptr;
      for (I32 y = 0; y < dim.y; ++y) {
         std::memcpy(dest_ptr, src_ptr, size);
         src_ptr += src_line_span;
         dest_ptr += dest_line_span;
      }
      src_plane_ptr += src_plane_span;
      dest_plane_ptr += dest_plane_span;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_by_line_segments(const SourceImageView& src, ibox src_block_extents, DestImageView& dest, ibox dest_block_extents) {
   const std::size_t size = src.block_span() * (std::size_t)src_block_extents.dim.x;
   const std::size_t src_plane_span = src.plane_span();
   const std::size_t dest_plane_span = dest.plane_span();
   const std::size_t src_line_span = src.line_span();
   const std::size_t dest_line_span = dest.line_span();
   const std::size_t src_block_offset = src.block_span() * (std::size_t)src_block_extents.offset.x;
   const std::size_t dest_block_offset = dest.block_span() * (std::size_t)dest_block_extents.offset.x;
   assert(src_line_span >= src_block_offset + size);
   assert(dest_line_span >= dest_block_offset + size);

   const std::size_t src_line_offset = src.line_span() * (std::size_t)src_block_extents.offset.y;
   const std::size_t dest_line_offset = dest.line_span() * (std::size_t)dest_block_extents.offset.y;
   const std::size_t src_plane_offset = src.plane_span() * (std::size_t)src_block_extents.offset.z;
   const std::size_t dest_plane_offset = dest.plane_span() * (std::size_t)dest_block_extents.offset.z;

   const UC* src_plane_ptr = src.data() + src_plane_offset + src_line_offset + src_block_offset;
   UC* dest_plane_ptr = dest.data() + dest_plane_offset + dest_line_offset + dest_block_offset;

   const ivec3 dim = src_block_extents.dim;
   for (I32 z = 0; z < dim.z; ++z) {
      const UC* src_ptr = src_plane_ptr;
      UC* dest_ptr = dest_plane_ptr;
      for (I32 y = 0; y < dim.y; ++y) {
         std::memcpy(dest_ptr, src_ptr, size);
         src_ptr += src_line_span;
         dest_ptr += dest_line_span;
      }
      src_plane_ptr += src_plane_span;
      dest_plane_ptr += dest_plane_span;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_by_blocks(const SourceImageView& src, DestImageView& dest) {
   const std::size_t size = src.format().block_size();
   const std::size_t src_plane_span = src.plane_span();
   const std::size_t dest_plane_span = dest.plane_span();
   const std::size_t src_line_span = src.line_span();
   const std::size_t dest_line_span = dest.line_span();
   const std::size_t src_block_span = src.block_span();
   const std::size_t dest_block_span = dest.block_span();
   assert(src_block_span >= size);
   assert(dest_block_span >= size);

   const UC* src_plane_ptr = src.data();
   UC* dest_plane_ptr = dest.data();

   const ivec3 dim = src.dim_blocks();
   for (I32 z = 0; z < dim.z; ++z) {
      const UC* src_line_ptr = src_plane_ptr;
      UC* dest_line_ptr = dest_plane_ptr;
      for (I32 y = 0; y < dim.y; ++y) {
         const UC* src_ptr = src_line_ptr;
         UC* dest_ptr = dest_line_ptr;
         for (I32 x = 0; x < dim.x; ++x) {
            std::memcpy(dest_ptr, src_ptr, size);
            src_ptr += src_block_span;
            dest_ptr += dest_block_span;
         }
         src_line_ptr += src_line_span;
         dest_line_ptr += dest_line_span;
      }
      src_plane_ptr += src_plane_span;
      dest_plane_ptr += dest_plane_span;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_by_blocks(const SourceImageView& src, ibox src_block_extents, DestImageView& dest, ibox dest_block_extents) {
   const std::size_t size = src.format().block_size();
   const std::size_t src_plane_span = src.plane_span();
   const std::size_t dest_plane_span = dest.plane_span();
   const std::size_t src_line_span = src.line_span();
   const std::size_t dest_line_span = dest.line_span();
   const std::size_t src_block_span = src.block_span();
   const std::size_t dest_block_span = dest.block_span();
   assert(src_block_span >= size);
   assert(dest_block_span >= size);

   const std::size_t src_block_offset = src_block_span * (std::size_t)src_block_extents.offset.x;
   const std::size_t dest_block_offset = dest_block_span * (std::size_t)dest_block_extents.offset.x;
   const std::size_t src_line_offset = src_line_span * (std::size_t)src_block_extents.offset.y;
   const std::size_t dest_line_offset = dest_line_span * (std::size_t)dest_block_extents.offset.y;
   const std::size_t src_plane_offset = src_plane_span * (std::size_t)src_block_extents.offset.z;
   const std::size_t dest_plane_offset = dest_plane_span * (std::size_t)dest_block_extents.offset.z;

   const UC* src_plane_ptr = src.data() + src_plane_offset + src_line_offset + src_block_offset;
   UC* dest_plane_ptr = dest.data() + dest_plane_offset + dest_line_offset + dest_block_offset;

   const ivec3 dim = src_block_extents.dim;
   for (I32 z = 0; z < dim.z; ++z) {
      const UC* src_line_ptr = src_plane_ptr;
      UC* dest_line_ptr = dest_plane_ptr;
      for (I32 y = 0; y < dim.y; ++y) {
         const UC* src_ptr = src_line_ptr;
         UC* dest_ptr = dest_line_ptr;
         for (I32 x = 0; x < dim.x; ++x) {
            std::memcpy(dest_ptr, src_ptr, size);
            src_ptr += src_block_span;
            dest_ptr += dest_block_span;
         }
         src_line_ptr += src_line_span;
         dest_line_ptr += dest_line_span;
      }
      src_plane_ptr += src_plane_span;
      dest_plane_ptr += dest_plane_span;
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_compatible_blocks(const SourceImageView& src, DestImageView& dest) {
   if (src.block_span() == dest.block_span()) {
      if (src.dim_blocks().x == dest.dim_blocks().x && src.line_span() == dest.line_span()) {
         if (src.dim_blocks().y == dest.dim_blocks().y && src.plane_span() == dest.plane_span()) {
            detail::memcpy_blit_level(src, dest);
         } else {
            detail::memcpy_blit_by_planes(src, dest);
         }
      } else {
         detail::memcpy_blit_by_lines(src, dest);
      }
   } else {
      detail::memcpy_blit_by_blocks(src, dest);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void memcpy_blit_compatible_blocks(const SourceImageView& src, ibox src_block_extents, DestImageView& dest, ibox dest_block_extents) {
   if (src.block_span() == dest.block_span()) {

      if (src.line_span() == dest.line_span() &&
          src_block_extents.offset.x == 0 && src_block_extents.dim.x == src.dim_blocks().x &&
          dest_block_extents.offset.x == 0 && dest_block_extents.dim.x == dest.dim_blocks().x) {

         if (src.plane_span() == dest.plane_span() &&
             src_block_extents.offset.y == 0 && src_block_extents.dim.y == src.dim_blocks().y &&
             dest_block_extents.offset.y == 0 && dest_block_extents.dim.y == dest.dim_blocks().y) {

            if (src_block_extents.offset.z == 0 && src_block_extents.dim.z == src.dim_blocks().z &&
                dest_block_extents.offset.z == 0 && dest_block_extents.dim.z == dest.dim_blocks().z) {
               detail::memcpy_blit_level(src, dest);
            } else {
               detail::memcpy_blit_plane_range(src, src_block_extents, dest, dest_block_extents);
            }
         } else {
            detail::memcpy_blit_by_plane_segments(src, src_block_extents, dest, dest_block_extents);
         }
      } else {
         detail::memcpy_blit_by_line_segments(src, src_block_extents, dest, dest_block_extents);
      }
   } else {
      detail::memcpy_blit_by_blocks(src, src_block_extents, dest, dest_block_extents);
   }
}

} // be::gfx::tex::detail

  ///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void blit_blocks(const SourceImageView& src, DestImageView& dest) {
   assert(dest.block_dim() == src.block_dim());
   assert(dest.format() == src.format());
   assert(dest.data() + dest.size() <= src.data() || src.data() + src.size() <= dest.data());
   assert(dest.dim_blocks().x >= src.dim_blocks().x);
   assert(dest.dim_blocks().y >= src.dim_blocks().y);
   assert(dest.dim_blocks().z >= src.dim_blocks().z);
   
   detail::memcpy_blit_compatible_blocks(src, dest);
}

///////////////////////////////////////////////////////////////////////////////
template <typename SourceImageView, typename DestImageView>
void blit_blocks(const SourceImageView& src, ImageRegion src_block_region, DestImageView& dest, ImageRegion dest_block_region) {
   assert(dest.block_dim() == src.block_dim());
   assert(dest.format() == src.format());

   assert(src_block_region.extents().left() >= 0);
   assert(src_block_region.extents().bottom() >= 0);
   assert(src_block_region.extents().back() >= 0);
   assert(src_block_region.extents().right() <= src.dim_blocks().x);
   assert(src_block_region.extents().top() <= src.dim_blocks().y);
   assert(src_block_region.extents().front() <= src.dim_blocks().z);

   const ivec3 src_region_dim = region_dim(src_block_region);
   dest_block_region = subregion(dest_block_region, ibox { ivec3(), src_region_dim });

   assert(dest_block_region.extents().left() >= 0);
   assert(dest_block_region.extents().bottom() >= 0);
   assert(dest_block_region.extents().back() >= 0);
   assert(dest_block_region.extents().right() <= dest.dim_blocks().x);
   assert(dest_block_region.extents().top() <= dest.dim_blocks().y);
   assert(dest_block_region.extents().front() <= dest.dim_blocks().z);

   assert(dest.data() + dest.size() <= src.data() ||
          src.data() + src.size() <= dest.data() ||
          !src_block_region.extents().intersects(dest_block_region.extents()));

   if (src_block_region.basis_vec() == dest_block_region.basis_vec()) {
      detail::memcpy_blit_compatible_blocks(src, src_block_region.extents(), dest, dest_block_region.extents());
   } else {
      assert(src.block_dim() == ImageFormat::block_dim_type(1));

      const std::size_t size = src.format().block_size();

      ibox src_extents = src_block_region.extents();
      ibox dest_extents = dest_block_region.extents();

      if (src_extents.offset.z == 0 && src_extents.dim.z == 1 &&
          dest_extents.offset.z == 0 && dest_extents.dim.z == 1) {
         if (src_extents.offset.y == 0 && src_extents.dim.y == 1 &&
             dest_extents.offset.y == 0 && dest_extents.dim.y == 1) {
            // lineal blit
            ivec3 rc;
            for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
               for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
                  for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                     const void* src_ptr = src.data() + block_offset(src, region_to_image(src_block_region, rc).x);
                     void* dest_ptr = dest.data() + block_offset(dest, region_to_image(dest_block_region, rc).x);
                     std::memcpy(dest_ptr, src_ptr, size);
                  }
               }
            }
         } else {
            // planar blit
            ivec3 rc;
            for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
               for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
                  for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                     const void* src_ptr = src.data() + block_offset(src, ivec2(region_to_image(src_block_region, rc)));
                     void* dest_ptr = dest.data() + block_offset(dest, ivec2(region_to_image(dest_block_region, rc)));
                     std::memcpy(dest_ptr, src_ptr, size);
                  }
               }
            }
         }
      } else {
         // volumetric blit
         ivec3 rc;
         for (rc.z = 0; rc.z < src_region_dim.z; ++rc.z) {
            for (rc.y = 0; rc.y < src_region_dim.y; ++rc.y) {
               for (rc.x = 0; rc.x < src_region_dim.x; ++rc.x) {
                  const void* src_ptr = src.data() + block_offset(src, region_to_image(src_block_region, rc));
                  void* dest_ptr = dest.data() + block_offset(dest, region_to_image(dest_block_region, rc));
                  std::memcpy(dest_ptr, src_ptr, size);
               }
            }
         }
      }
   }
}

} // be::gfx::tex

#endif
