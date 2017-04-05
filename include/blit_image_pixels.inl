//#if !defined(BE_GFX_BLIT_IMAGE_HPP_) && !defined(DOXYGEN)
//#include "blit_image.hpp"
//#elif !defined(BE_GFX_BLIT_IMAGE_INL_)
//#define BE_GFX_BLIT_IMAGE_INL_
//
//namespace be::gfx {
//namespace detail {
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_level(const SourceImageView& source, DestImageView& dest) {
//   const std::size_t size = source.plane_span() * (std::size_t)source.dim_blocks().z;
//   assert(source.size() >= size);
//   assert(dest.size() >= size);
//   std::memcpy(dest.data(), source.data(), size);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_plane_range(const SourceImageView& source, ibox source_extents, DestImageView& dest, ibox dest_extents) {
//   const std::size_t size = source.plane_span() * (std::size_t)(source_extents.dim.z / source.block_dim().z);
//   const std::size_t src_offset = source.plane_span() * (std::size_t)(source_extents.offset.z / source.block_dim().z);
//   const std::size_t dest_offset = dest.plane_span() * (std::size_t)(dest_extents.offset.z / dest.block_dim().z);
//   assert(source.size() >= src_offset + size);
//   assert(dest.size() >= dest_offset + size);
//
//   const UC* src_ptr = source.data() + src_offset;
//   UC* dest_ptr = dest.data() + dest_offset;
//
//   std::memcpy(dest_ptr, src_ptr, size);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_by_planes(const SourceImageView& source, DestImageView& dest) {
//   const std::size_t size = source.line_span() * (std::size_t)source.dim_blocks().y;
//   const std::size_t src_plane_span = source.plane_span();
//   const std::size_t dest_plane_span = dest.plane_span();
//   assert(src_plane_span >= size);
//   assert(dest_plane_span >= size);
//
//   const UC* src_ptr = source.data();
//   UC* dest_ptr = dest.data();
//
//   const I32 dim = source.dim_blocks().z;
//   for (I32 z = 0; z < dim; ++z) {
//      std::memcpy(dest_ptr, src_ptr, size);
//      src_ptr += src_plane_span;
//      dest_ptr += dest_plane_span;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_by_plane_segments(const SourceImageView& source, ibox source_extents, DestImageView& dest, ibox dest_extents) {
//   const std::size_t size = source.line_span() * (std::size_t)(source_extents.dim.y / source.block_dim().y);
//   const std::size_t src_plane_span = source.plane_span();
//   const std::size_t dest_plane_span = dest.plane_span();
//   const std::size_t src_line_offset = source.line_span() * (std::size_t)(source_extents.offset.y / source.block_dim().y);
//   const std::size_t dest_line_offset = dest.line_span() * (std::size_t)(dest_extents.offset.y / dest.block_dim().y);
//   assert(src_plane_span >= src_line_offset + size);
//   assert(dest_plane_span >= dest_line_offset + size);
//
//   const std::size_t src_plane_offset = source.plane_span() * (std::size_t)(source_extents.offset.z / source.block_dim().z);
//   const std::size_t dest_plane_offset = dest.plane_span() * (std::size_t)(dest_extents.offset.z / dest.block_dim().z);
//
//   const UC* src_ptr = source.data() + src_plane_offset + src_line_offset;
//   UC* dest_ptr = dest.data() + dest_plane_offset + dest_line_offset;
//
//   const I32 dim = source_extents.dim.z / source.block_dim().z;
//   for (I32 z = 0; z < dim; ++z) {
//      std::memcpy(dest_ptr, src_ptr, size);
//      src_ptr += src_plane_span;
//      dest_ptr += dest_plane_span;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_by_lines(const SourceImageView& source, DestImageView& dest) {
//   const std::size_t size = source.block_size() * (std::size_t)source.dim_blocks().x;
//   const std::size_t src_plane_span = source.plane_span();
//   const std::size_t dest_plane_span = dest.plane_span();
//   const std::size_t src_line_span = source.line_span();
//   const std::size_t dest_line_span = dest.line_span();
//   assert(src_line_span >= size);
//   assert(dest_line_span >= size);
//
//   const UC* src_plane_ptr = source.data();
//   UC* dest_plane_ptr = dest.data();
//
//   const ivec3 dim = source.dim_blocks();
//   for (I32 z = 0; z < dim.z; ++z) {
//      const UC* src_ptr = src_plane_ptr;
//      UC* dest_ptr = dest_plane_ptr;
//      for (I32 y = 0; y < dim.y; ++y) {
//         std::memcpy(dest_ptr, src_ptr, size);
//         src_ptr += src_line_span;
//         dest_ptr += dest_line_span;
//      }
//      src_plane_ptr += src_plane_span;
//      dest_plane_ptr += dest_plane_span;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_by_line_segments(const SourceImageView& source, ibox source_extents, DestImageView& dest, ibox dest_extents) {
//   const std::size_t size = source.block_size() * (std::size_t)(source_extents.dim.x / source.block_dim().x);
//   const std::size_t src_plane_span = source.plane_span();
//   const std::size_t dest_plane_span = dest.plane_span();
//   const std::size_t src_line_span = source.line_span();
//   const std::size_t dest_line_span = dest.line_span();
//   const std::size_t src_block_offset = source.block_size() * (std::size_t)(source_extents.offset.x / source.block_dim().x);
//   const std::size_t dest_block_offset = dest.block_size() * (std::size_t)(dest_extents.offset.x / dest.block_dim().x);
//   assert(src_line_span >= src_block_offset + size);
//   assert(dest_line_span >= dest_block_offset + size);
//
//   const std::size_t src_line_offset = source.line_span() * (std::size_t)(source_extents.offset.y / source.block_dim().y);
//   const std::size_t dest_line_offset = dest.line_span() * (std::size_t)(dest_extents.offset.y / dest.block_dim().y);
//   const std::size_t src_plane_offset = source.plane_span() * (std::size_t)(source_extents.offset.z / source.block_dim().z);
//   const std::size_t dest_plane_offset = dest.plane_span() * (std::size_t)(dest_extents.offset.z / dest.block_dim().z);
//
//   const UC* src_plane_ptr = source.data() + src_plane_offset + src_line_offset + src_block_offset;
//   UC* dest_plane_ptr = dest.data() + dest_plane_offset + dest_line_offset + dest_block_offset;
//
//   const ivec3 dim = source_extents.dim / source.block_dim();
//   for (I32 z = 0; z < dim.z; ++z) {
//      const UC* src_ptr = src_plane_ptr;
//      UC* dest_ptr = dest_plane_ptr;
//      for (I32 y = 0; y < dim.y; ++y) {
//         std::memcpy(dest_ptr, src_ptr, size);
//         src_ptr += src_line_span;
//         dest_ptr += dest_line_span;
//      }
//      src_plane_ptr += src_plane_span;
//      dest_plane_ptr += dest_plane_span;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_by_blocks(const SourceImageView& source, DestImageView& dest) {
//   const std::size_t size = source.format().block_size();
//   const std::size_t src_plane_span = source.plane_span();
//   const std::size_t dest_plane_span = dest.plane_span();
//   const std::size_t src_line_span = source.line_span();
//   const std::size_t dest_line_span = dest.line_span();
//   const std::size_t src_block_size = source.block_size();
//   const std::size_t dest_block_size = dest.block_size();
//   assert(src_block_size >= size);
//   assert(dest_block_size >= size);
//
//   const UC* src_plane_ptr = source.data();
//   UC* dest_plane_ptr = dest.data();
//
//   const ivec3 dim = source.dim_blocks();
//   for (I32 z = 0; z < dim.z; ++z) {
//      const UC* src_line_ptr = src_plane_ptr;
//      UC* dest_line_ptr = dest_plane_ptr;
//      for (I32 y = 0; y < dim.y; ++y) {
//         const UC* src_ptr = src_line_ptr;
//         UC* dest_ptr = dest_line_ptr;
//         for (I32 x = 0; x < dim.x; ++x) {
//            std::memcpy(dest_ptr, src_ptr, size);
//            src_ptr += src_block_size;
//            dest_ptr += dest_block_size;
//         }
//         src_line_ptr += src_line_span;
//         dest_line_ptr += dest_line_span;
//      }
//      src_plane_ptr += src_plane_span;
//      dest_plane_ptr += dest_plane_span;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_by_blocks(const SourceImageView& source, ibox source_extents, DestImageView& dest, ibox dest_extents) {
//   const std::size_t size = source.format().block_size();
//   const std::size_t src_plane_span = source.plane_span();
//   const std::size_t dest_plane_span = dest.plane_span();
//   const std::size_t src_line_span = source.line_span();
//   const std::size_t dest_line_span = dest.line_span();
//   const std::size_t src_block_size = source.block_size();
//   const std::size_t dest_block_size = dest.block_size();
//   assert(src_block_size >= size);
//   assert(dest_block_size >= size);
//
//   const std::size_t src_block_offset = source.block_size() * (std::size_t)(source_extents.offset.x / source.block_dim().x);
//   const std::size_t dest_block_offset = dest.block_size() * (std::size_t)(dest_extents.offset.x / dest.block_dim().x);
//   const std::size_t src_line_offset = source.line_span() * (std::size_t)(source_extents.offset.y / source.block_dim().y);
//   const std::size_t dest_line_offset = dest.line_span() * (std::size_t)(dest_extents.offset.y / dest.block_dim().y);
//   const std::size_t src_plane_offset = source.plane_span() * (std::size_t)(source_extents.offset.z / source.block_dim().z);
//   const std::size_t dest_plane_offset = dest.plane_span() * (std::size_t)(dest_extents.offset.z / dest.block_dim().z);
//
//   const UC* src_plane_ptr = source.data() + src_plane_offset + src_line_offset + src_block_offset;
//   UC* dest_plane_ptr = dest.data() + dest_plane_offset + dest_line_offset + dest_block_offset;
//
//   const ivec3 dim = source_extents.dim / source.block_dim();
//   for (I32 z = 0; z < dim.z; ++z) {
//      const UC* src_line_ptr = src_plane_ptr;
//      UC* dest_line_ptr = dest_plane_ptr;
//      for (I32 y = 0; y < dim.y; ++y) {
//         const UC* src_ptr = src_line_ptr;
//         UC* dest_ptr = dest_line_ptr;
//         for (I32 x = 0; x < dim.x; ++x) {
//            std::memcpy(dest_ptr, src_ptr, size);
//            src_ptr += src_block_size;
//            dest_ptr += dest_block_size;
//         }
//         src_line_ptr += src_line_span;
//         dest_line_ptr += dest_line_span;
//      }
//      src_plane_ptr += src_plane_span;
//      dest_plane_ptr += dest_plane_span;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_by_pixels(const SourceImageView& source, DestImageView& dest) {
//   const std::size_t size = image_block_pixel_size(source.format().packing());
//   const std::size_t src_plane_span = source.plane_span();
//   const std::size_t dest_plane_span = dest.plane_span();
//   const std::size_t src_line_span = source.line_span();
//   const std::size_t dest_line_span = dest.line_span();
//   const std::size_t src_block_size = source.block_size();
//   const std::size_t dest_block_size = dest.block_size();
//
//   const ivec3 src_block_dim = source.block_dim();
//   ivec3 src_block_coord;
//
//   const ivec3 dest_block_dim = dest.block_dim();
//   ivec3 dest_block_coord;
//
//   const UC* src_plane_ptr = source.data();
//   UC* dest_plane_ptr = dest.data();
//
//   const ivec3 dim = source.dim();
//   ivec3 pc;
//   for (pc.z = 0; pc.z < dim.z; ++pc.z) {
//      const UC* src_line_ptr = src_plane_ptr;
//      UC* dest_line_ptr = dest_plane_ptr;
//
//      for (pc.y = 0; pc.y < dim.y; ++pc.y) {
//         const UC* src_block_ptr = src_line_ptr;
//         UC* dest_block_ptr = dest_line_ptr;
//
//         for (pc.x = 0; pc.x < dim.x; ++pc.x) {
//            const UC* src_ptr = src_block_ptr + ((src_block_coord.z * src_block_dim.y + src_block_coord.y) * src_block_dim.x + src_block_coord.x) * size;
//            UC* dest_ptr = dest_block_ptr + ((dest_block_coord.z * dest_block_dim.y + dest_block_coord.y) * dest_block_dim.x + dest_block_coord.x) * size;
//
//            std::memcpy(dest_ptr, src_ptr, size);
//
//            ++src_block_coord.x;
//            if (src_block_coord.x >= src_block_dim.x) {
//               src_block_ptr += src_block_size;
//               src_block_coord.x = 0;
//            }
//
//            ++dest_block_coord.x;
//            if (dest_block_coord.x >= dest_block_dim.x) {
//               dest_block_ptr += dest_block_size;
//               dest_block_coord.x = 0;
//            }
//         }
//
//         ++src_block_coord.y;
//         if (src_block_coord.y >= src_block_dim.y) {
//            src_line_ptr += src_line_span;
//            src_block_coord.y = 0;
//         }
//
//         ++dest_block_coord.y;
//         if (dest_block_coord.y >= dest_block_dim.y) {
//            dest_line_ptr += dest_line_span;
//            dest_block_coord.y = 0;
//         }
//      }
//
//      ++src_block_coord.z;
//      if (src_block_coord.z >= src_block_dim.z) {
//         src_plane_ptr += src_plane_span;
//         src_block_coord.z = 0;
//      }
//
//      ++dest_block_coord.z;
//      if (dest_block_coord.z >= dest_block_dim.z) {
//         dest_plane_ptr += dest_plane_span;
//         dest_block_coord.z = 0;
//      }
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_compatible_blocks(const SourceImageView& source, DestImageView& dest) {
//   if (source.block_size() == dest.block_size()) {
//      if (source.dim().x == dest.dim().x && source.line_span() == dest.line_span()) {
//         if (source.dim().y == dest.dim().y && source.plane_span() == dest.plane_span()) {
//            detail::memcpy_blit_image_level(source, dest);
//         } else {
//            detail::memcpy_blit_image_by_planes(source, dest);
//         }
//      } else {
//         detail::memcpy_blit_image_by_lines(source, dest);
//      }
//   } else {
//      detail::memcpy_blit_image_by_blocks(source, dest);
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void memcpy_blit_image_compatible_blocks(const SourceImageView& source, ibox source_extents, DestImageView& dest, ibox dest_extents) {
//   if (source.block_size() == dest.block_size()) {
//
//      if (source.line_span() == dest.line_span() &&
//          source_extents.offset.x == 0 && source_extents.dim.x == source.dim().x &&
//          dest_extents.offset.x == 0 && dest_extents.dim.x == dest.dim().x) {
//
//         if (source.plane_span() == dest.plane_span() &&
//             source_extents.offset.y == 0 && source_extents.dim.y == source.dim().y &&
//             dest_extents.offset.y == 0 && dest_extents.dim.y == dest.dim().y) {
//
//            if (source_extents.offset.z == 0 && source_extents.dim.z == source.dim().z &&
//                dest_extents.offset.z == 0 && dest_extents.dim.z == dest.dim().z) {
//               detail::memcpy_blit_image_level(source, dest);
//            } else {
//               detail::memcpy_blit_image_plane_range(source, source_extents, dest, dest_extents);
//            }
//         } else {
//            detail::memcpy_blit_image_by_plane_segments(source, source_extents, dest, dest_extents);
//         }
//      } else {
//         detail::memcpy_blit_image_by_line_segments(source, source_extents, dest, dest_extents);
//      }
//   } else {
//      detail::memcpy_blit_image_by_blocks(source, source_extents, dest, dest_extents);
//   }
//}
//
//} // be::gfx::detail
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void blit_image(const SourceImageView& source, DestImageView& dest) {
//   assert(dest.data() + dest.size() <= source.data() || source.data() + source.size() <= dest.data())
//   assert(dest.dim().x >= source.dim().x);
//   assert(dest.dim().y >= source.dim().y);
//   assert(dest.dim().z >= source.dim().z);
//   ImageFormat sf = source.format();
//   ImageFormat df = dest.format();
//
//   if (gfx::is_compressed(df.packing())) {
//      assert(sf == df);
//      assert(source.dim().x == dest.dim().x || source.dim().x % sf.block_dim().x == 0);
//      assert(source.dim().y == dest.dim().y || source.dim().y % sf.block_dim().y == 0);
//      assert(source.dim().z == dest.dim().z || source.dim().z % sf.block_dim().z == 0);
//      detail::memcpy_blit_image_compatible_blocks(source, dest);
//   } else {
//      // dest is uncompressed
//      if (sf.premultiplied() == df.premultiplied() &&
//          sf.colorspace() == df.colorspace() &&
//          sf.swizzles() == df.swizzles() &&
//          sf.component_types() == df.component_types() &&
//          sf.components() == df.components() &&
//          sf.packing() == df.packing()) {
//         // formats are the same, with possible exception of block_dim and block_size
//         // so we can memcpy pixels (or better) and don't need ConvertingPixelBlitter
//         if (sf.block_dim() == df.block_dim() && (sf.block_dim() == ImageFormat::block_dim_type(1u) ||
//             (source.dim().x == dest.dim().x || source.dim().x % sf.block_dim().x == 0) &&
//             (source.dim().y == dest.dim().y || source.dim().y % sf.block_dim().y == 0) &&
//             (source.dim().z == dest.dim().z || source.dim().z % sf.block_dim().z == 0))) {
//            detail::memcpy_blit_image_compatible_blocks(source, dest);
//         } else {
//            detail::memcpy_blit_image_by_pixels(source, dest);
//         }
//      } else {
//         // pixel formats differ; use ConvertingPixelBlitter
//         if (source.dim().z == 1) {
//            if (source.dim().y == 1) {
//               ConvertingPixelBlitterLineal<SourceImageView, DestImageView> blitter(source, dest);
//               I32 dim = source.dim().x;
//               for (I32 pc = 0; pc < dim; ++pc) {
//                  blitter(pc, pc);
//               }
//            } else {
//               ConvertingPixelBlitterPlanar<SourceImageView, DestImageView> blitter(source, dest);
//               ivec3 dim = source.dim();
//               ivec2 pc;
//               for (pc.y = 0; pc.y < dim.y; ++pc.y) {
//                  for (pc.x = 0; pc.x < dim.x; ++pc.x) {
//                     blitter(pc, pc);
//                  }
//               }
//            }
//         } else {
//            ConvertingPixelBlitterVolumetric<SourceImageView, DestImageView> blitter(source, dest);
//            ivec3 dim = source.dim();
//            ivec3 pc;
//            for (pc.z = 0; pc.z < dim.z; ++pc.z) {
//               for (pc.y = 0; pc.y < dim.y; ++pc.y) {
//                  for (pc.x = 0; pc.x < dim.x; ++pc.x) {
//                     blitter(pc, pc);
//                  }
//               }
//            }
//         }
//      }
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//template <typename SourceImageView, typename DestImageView>
//void blit_image(const SourceImageView& source, ImageRegion source_region, DestImageView& dest, ImageRegion dest_region) {
//   assert(source_region.extents().left() >= 0);
//   assert(source_region.extents().bottom() >= 0);
//   assert(source_region.extents().back() >= 0);
//   assert(source_region.extents().right() <= source.dim().x);
//   assert(source_region.extents().top() <= source.dim().y);
//   assert(source_region.extents().front() <= source.dim().z);
//
//   dest_region = subregion(dest_region, ibox { ivec3(), region_dim(source_region) });
//
//   assert(dest_region.extents().left() >= 0);
//   assert(dest_region.extents().bottom() >= 0);
//   assert(dest_region.extents().back() >= 0);
//   assert(dest_region.extents().right() <= dest.dim().x);
//   assert(dest_region.extents().top() <= dest.dim().y);
//   assert(dest_region.extents().front() <= dest.dim().z);
//
//   assert(dest.data() + dest.size() <= source.data() ||
//          source.data() + source.size() <= dest.data() ||
//          !source_region.extents().intersects(dest_region.extents()));
//
//   ImageFormat sf = source.format();
//   ImageFormat df = dest.format();
//
//   if (gfx::is_compressed(df.packing())) {
//      assert(sf == df);
//      assert(source_region.basis_vec() == dest_region.basis_vec());
//      assert(source_region.extents().left() % sf.block_dim().x == 0);
//      assert(source_region.extents().bottom() % sf.block_dim().y == 0);
//      assert(source_region.extents().back() % sf.block_dim().z == 0);
//      assert(source_region.extents().right() % sf.block_dim().x == 0);
//      assert(source_region.extents().top() % sf.block_dim().y == 0);
//      assert(source_region.extents().front() % sf.block_dim().z == 0);
//      assert(dest_region.extents().left() % sf.block_dim().x == 0);
//      assert(dest_region.extents().bottom() % sf.block_dim().y == 0);
//      assert(dest_region.extents().back() % sf.block_dim().z == 0);
//      detail::memcpy_blit_image_compatible_blocks(source, source_region.extents(), dest, dest_region.extents());
//   } else {
//      // dest is uncompressed
//      if (sf.premultiplied() == df.premultiplied() &&
//          sf.colorspace() == df.colorspace() &&
//          sf.swizzles() == df.swizzles() &&
//          sf.component_types() == df.component_types() &&
//          sf.components() == df.components() &&
//          sf.packing() == df.packing()) {
//         // formats are the same, with possible exception of block_dim and block_size
//         // so we can memcpy pixels (or better) and don't need ConvertingPixelBlitter
//         if (source_region.basis_vec() == dest_region.basis_vec()) {
//            if (sf.block_dim() == df.block_dim() && (sf.block_dim() == ImageFormat::block_dim_type(1u) ||
//                source_region.extents().left() % sf.block_dim().x == 0 &&
//                source_region.extents().right() % sf.block_dim().x == 0 &&
//                dest_region.extents().left() % sf.block_dim().x == 0 &&
//                source_region.extents().bottom() % sf.block_dim().y == 0 &&
//                source_region.extents().top() % sf.block_dim().y == 0 &&
//                dest_region.extents().bottom() % sf.block_dim().y == 0 &&
//                source_region.extents().back() % sf.block_dim().z == 0 &&
//                source_region.extents().front() % sf.block_dim().z == 0 &&
//                dest_region.extents().back() % sf.block_dim().z == 0)) {
//               detail::memcpy_blit_image_compatible_blocks(source, source_region.extents(), dest, dest_region.extents());
//            } else {
//               detail::memcpy_blit_image_by_pixels(source, dest);
//            }
//         }
//
//         
//      } else {
//         // pixel formats differ; use ConvertingPixelBlitter
//         if (source.dim().z == 1) {
//            if (source.dim().y == 1) {
//               ConvertingPixelBlitterLineal<SourceImageView, DestImageView> blitter(source, dest);
//               I32 dim = source.dim().x;
//               for (I32 pc = 0; pc < dim; ++pc) {
//                  blitter(pc, pc);
//               }
//            } else {
//               ConvertingPixelBlitterPlanar<SourceImageView, DestImageView> blitter(source, dest);
//               ivec3 dim = source.dim();
//               ivec2 pc;
//               for (pc.y = 0; pc.y < dim.y; ++pc.y) {
//                  for (pc.x = 0; pc.x < dim.x; ++pc.x) {
//                     blitter(pc, pc);
//                  }
//               }
//            }
//         } else {
//            ConvertingPixelBlitterVolumetric<SourceImageView, DestImageView> blitter(source, dest);
//            ivec3 dim = source.dim();
//            ivec3 pc;
//            for (pc.z = 0; pc.z < dim.z; ++pc.z) {
//               for (pc.y = 0; pc.y < dim.y; ++pc.y) {
//                  for (pc.x = 0; pc.x < dim.x; ++pc.x) {
//                     blitter(pc, pc);
//                  }
//               }
//            }
//         }
//      }
//   }
//}
//
//} // be::gfx
//
//#endif
