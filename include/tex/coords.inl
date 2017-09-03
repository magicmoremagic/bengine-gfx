#if !defined(BE_GFX_TEX_COORDS_HPP_) && !defined(DOXYGEN)
#include "coords.hpp"
#elif !defined(BE_GFX_TEX_COORDS_INL_)
#define BE_GFX_TEX_COORDS_INL_

namespace be::gfx::tex {
namespace detail {

#pragma region CoordConverter

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord, glm::length_t OutDimension = t::vector_components<OutCoord>::value, glm::length_t InDimension = t::vector_components<InCoord>::value>
struct CoordConverter { };

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 1, 1> {
   static OutCoord convert(InCoord coord) noexcept {
      return static_cast<OutCoord>(coord);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 2, 1> {
   static OutCoord convert(InCoord coord) noexcept {
      using V = typename OutCoord::value_type;
      return OutCoord { static_cast<V>(coord), V(0) };
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 3, 1> {
   static OutCoord convert(InCoord coord) noexcept {
      using V = typename OutCoord::value_type;
      return OutCoord { static_cast<V>(coord), V(0), V(0) };
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 1, 2> {
   static OutCoord convert(InCoord coord) noexcept {
      return static_cast<OutCoord>(coord.x);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 2, 2> {
   static OutCoord convert(InCoord coord) noexcept {
      using V = typename OutCoord::value_type;
      return OutCoord { static_cast<V>(coord.x), static_cast<V>(coord.y) };
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 3, 2> {
   static OutCoord convert(InCoord coord) noexcept {
      using V = typename OutCoord::value_type;
      return OutCoord { static_cast<V>(coord.x), static_cast<V>(coord.y), V(0) };
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 1, 3> {
   static OutCoord convert(InCoord coord) noexcept {
      return static_cast<OutCoord>(coord.x);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 2, 3> {
   static OutCoord convert(InCoord coord) noexcept {
      using V = typename OutCoord::value_type;
      return OutCoord { static_cast<V>(coord.x), static_cast<V>(coord.y) };
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
struct CoordConverter<OutCoord, InCoord, 3, 3> {
   static OutCoord convert(InCoord coord) noexcept {
      using V = typename OutCoord::value_type;
      return OutCoord { static_cast<V>(coord.x), static_cast<V>(coord.y), static_cast<V>(coord.z) };
   }
};

#pragma endregion
#pragma region BlockCoordConverter

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, glm::length_t Dimension = t::vector_components<Coord>::value>
struct BlockCoordConverter { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct BlockCoordConverter<ImageView, Coord, 1> {
   static Coord to_pixel_coord(const ImageView& image, Coord block_coord, Coord block_local_coord) {
      assert(image);
      return block_coord * Coord(image.block_dim().x) + block_local_coord;
   }
   static std::pair<Coord, Coord> to_block_coords(const ImageView& image, Coord pixel_coord) {
      assert(image);
      assert(pixel_coord >= 0);
      Coord block = pixel_coord / Coord(image.block_dim().x);
      return std::make_pair(block, pixel_coord - block);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct BlockCoordConverter<ImageView, Coord, 2> {
   using V = typename Coord::value_type;
   static Coord to_pixel_coord(const ImageView& image, Coord block_coord, Coord block_local_coord) {
      assert(image);
      auto block_dim = image.block_dim();
      return Coord {
         block_coord.x * V(block_dim.x) + block_local_coord.x,
         block_coord.y * V(block_dim.y) + block_local_coord.y
      };
   }
   static std::pair<Coord, Coord> to_block_coords(const ImageView& image, Coord pixel_coord) {
      assert(image);
      assert(pixel_coord.x >= 0);
      assert(pixel_coord.y >= 0);
      auto block_dim = image.block_dim();
      Coord block = Coord { pixel_coord.x / V(block_dim.x),
                            pixel_coord.y / V(block_dim.y) };
      return std::make_pair(block, pixel_coord - block);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct BlockCoordConverter<ImageView, Coord, 3> {
   using V = typename Coord::value_type;
   static Coord to_pixel_coord(const ImageView& image, Coord block_coord, Coord block_local_coord) {
      assert(image);
      auto block_dim = image.block_dim();
      return Coord {
         block_coord.x * V(block_dim.x) + block_local_coord.x,
         block_coord.y * V(block_dim.y) + block_local_coord.y,
         block_coord.z * V(block_dim.z) + block_local_coord.z,
      };
   }
   static std::pair<Coord, Coord> to_block_coords(const ImageView& image, Coord pixel_coord) {
      assert(image);
      assert(pixel_coord.x >= 0);
      assert(pixel_coord.y >= 0);
      assert(pixel_coord.z >= 0);
      auto block_dim = image.block_dim();
      Coord block = Coord { pixel_coord.x / V(block_dim.x),
                            pixel_coord.y / V(block_dim.y),
                            pixel_coord.z / V(block_dim.z) };
      return std::make_pair(block, pixel_coord - block);
   }
};

#pragma endregion

} // be::gfx::tex::detail

///////////////////////////////////////////////////////////////////////////////
template <typename OutCoord, typename InCoord>
OutCoord convert_coord(InCoord coord) {
   return detail::CoordConverter<OutCoord, InCoord>::convert(coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
Coord to_pixel_coord(const ImageView& image, Coord block_coord, Coord block_local_coord) {
   return detail::BlockCoordConverter<ImageView, Coord>::to_pixel_coord(image, block_coord, block_local_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
Coord to_block_coord(const ImageView& image, Coord pixel_coord) {
   Coord block_coord;
   std::tie(block_coord, std::ignore) = detail::BlockCoordConverter<ImageView, Coord>::to_block_coords(image, block_coord);
   return block_coord;
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
Coord to_block_local_coord(const ImageView& image, Coord pixel_coord) {
   Coord local_coord;
   std::tie(std::ignore, local_coord) = detail::BlockCoordConverter<ImageView, Coord>::to_block_coords(image, pixel_coord);
   return local_coord;
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
std::pair<Coord, Coord> to_block_coords(const ImageView& image, Coord pixel_coord) {
   return detail::BlockCoordConverter<ImageView, Coord>::to_block_coords(image, pixel_coord);
}

} // be::gfx::tex

#endif
