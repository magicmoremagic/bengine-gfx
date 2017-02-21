#pragma once
#ifndef BE_TEXI_GAUSSIAN_FILTER_HPP_
#define BE_TEXI_GAUSSIAN_FILTER_HPP_

#include "memoized_filter.hpp"

namespace be {
namespace texi {
namespace detail {

template <int S, int D, int M, typename T>
struct GaussianFilterConstants {
   static constexpr double sigma = double(S) / double(D);
   static constexpr T c = T(1.0 / (2.506628274631000502415765 * sigma));
   static constexpr T k = T(-1.0 / (2.0 * sigma * sigma));
   static constexpr T support = T(sigma * M);
};

} // be::texi::detail

template <int S = 1, int D = 2, int M = 4>
struct GaussianFilter {
   template <typename T = float>
   T operator()(T x) {
      return detail::GaussianFilterConstants<S,D,M,T>::c * exp(detail::GaussianFilterConstants<S,D,M,T>::k * x * x);
   }
};

template <int S, int D, int M>
struct FilterSupportRange<GaussianFilter<S, D, M>> {
   template <typename T>
   T operator()() {
      return detail::GaussianFilterConstants<S,D,M,T>::support;
   }
};

template <typename T, int S = 1, int D = 2, int M = 4>
using MemoizedGaussianFilter = MemoizedFilter<T, GaussianFilter<S,D,M>>;

} // be::texi
} // be

#endif
