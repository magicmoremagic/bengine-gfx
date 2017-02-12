#pragma once
#ifndef BE_TEXI_VARIABLE_SIZE_MEDIAN_KERNEL_HPP_
#define BE_TEXI_VARIABLE_SIZE_MEDIAN_KERNEL_HPP_

#include "texi_autolink.hpp"
#include <be/core/t_covering_unsigned.hpp>
#include <array>

namespace be {
namespace texi {

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
class VariableSizeMedianKernel {
public:
   using value_type = std::remove_cv_t<T>;
   using index_type = std::make_unsigned_t<value_type>;
   using count_type = t::CoveringUnsigned<N>;

   static_assert(sizeof(value_type) == sizeof(index_type), "Invalid value type");

   static constexpr std::size_t histogram_size = 1 << (sizeof(index_type) * 8);
   static constexpr count_type max_sample_count = static_cast<count_type>(N);

   void remove(value_type sample);
   void insert(value_type sample);

   value_type median();

private:
   index_type to_index_(value_type sample) const;
   value_type to_sample_(index_type index) const;

   std::array<count_type, histogram_size> histogram_ = { };
   count_type size_ = 0;
   index_type median_ = 0;
   count_type before_median_ = 0;
};

} // be::texi
} // be

#endif
