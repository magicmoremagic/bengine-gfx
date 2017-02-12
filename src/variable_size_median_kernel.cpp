#include "pch.hpp"
#include "variable_size_median_kernel.hpp"

namespace be {
namespace texi {

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
void VariableSizeMedianKernel<T, N>::remove(value_type sample) {
   index_type index = to_index_(sample);
   --histogram_[index];
   if (index < median_) {
      --before_median_;
   }
   --size_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
void VariableSizeMedianKernel<T, N>::insert(value_type sample) {
   index_type index = to_index_(sample);
   ++histogram_[index];
   if (index < median_) {
      ++before_median_;
   }
   ++size_;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
typename VariableSizeMedianKernel<T, N>::value_type VariableSizeMedianKernel<T, N>::median() {
   if (size_ <= 0) {
      return value_type();
   } else {
      count_type target = ((size_ - 1) >> 1) - before_median_;
      if (target >= 0) {
         count_type c;
         while ((c = histogram_[median_]) < target) {
            before_median_ += c;
            ++median_;
            target -= c;
         }
      } else {
         do {
            --median_;
            count_type c = histogram_[median_];
            before_median_ -= c;
            target += c;
         } while (target < 0)
      }
      return to_sample_(median_);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
typename VariableSizeMedianKernel<T, N>::index_type VariableSizeMedianKernel<T, N>::to_index_(value_type sample) const {
   index_type index;
   memcpy(&index, &sample, sizeof(index_type));
   return index;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
typename VariableSizeMedianKernel<T, N>::value_type VariableSizeMedianKernel<T, N>::to_sample_(index_type index) const {
   value_type sample;
   memcpy(&sample, &index, sizeof(value_type));
   return sample;
}

} // be::texi
} // be
