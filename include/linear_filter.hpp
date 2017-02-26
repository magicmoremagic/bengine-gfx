#pragma once
#ifndef BE_GFX_LINEAR_FILTER_HPP_
#define BE_GFX_LINEAR_FILTER_HPP_

#include "filter_traits.hpp"

namespace be {
namespace gfx {
namespace detail {

template <int S, int D, typename T>
struct TriangularFilterSupport {
   static constexpr T s = T(S) / T(D);
};

} // be::gfx::detail

template <int S = 1, int D = 1>
struct TriangularFilter {
   template <typename T = float>
   T operator()(T x) {
      x = x < T(0) ? -x : x;
      if (x < detail::TriangularFilterSupport<S, D, T>::s) {
         return T(1) - x / detail::TriangularFilterSupport<S, D, T>::s;
      } else {
         return T(0);
      }
   }
};

template <int S, int D>
struct FilterSupportRange<TriangularFilter<S, D>> {
   template <typename T>
   T operator()() {
      return detail::TriangularFilterSupport<S, D, T>::s;
   }
};

using LinearFilter = TriangularFilter<>;

} // be::gfx
} // be

#endif
