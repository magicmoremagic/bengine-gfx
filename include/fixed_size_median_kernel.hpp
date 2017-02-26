#pragma once
#ifndef BE_GFX_FIXED_SIZE_MEDIAN_KERNEL_HPP_
#define BE_GFX_FIXED_SIZE_MEDIAN_KERNEL_HPP_

#include "gfx_autolink.hpp"
#include <be/core/t_covering_unsigned.hpp>
#include <array>

namespace be {
namespace gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
class FixedSizeMedianKernel {
public:
   using value_type = std::remove_cv_t<T>;
   using index_type = std::make_unsigned_t<value_type>;
   using count_type = t::CoveringUnsigned<N>;

   static_assert(sizeof(value_type) == sizeof(index_type), "Invalid value type");

   static constexpr std::size_t histogram_size = 1 << (sizeof(index_type) * 8);
   static constexpr count_type sample_count = static_cast<count_type>(N);
   static constexpr count_type median_sample = (sample_count - 1) >> 1;

   void remove(value_type sample);
   void insert(value_type sample);

   value_type median();

private:
   index_type to_index_(value_type sample) const;
   value_type to_sample_(index_type index) const;

   std::array<count_type, histogram_size> histogram_ = { };
   index_type median_ = 0;
   count_type before_median_ = 0;
};

} // be::gfx
} // be

#include "fixed_size_median_kernel.inl"

#endif
