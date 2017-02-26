#pragma once
#ifndef BE_GFX_STEP_FILTER_HPP_
#define BE_GFX_SETP_FILTER_HPP_

#include "filter_traits.hpp"

namespace be {
namespace gfx {
namespace detail {

template <int S, int D, typename T>
struct BoxFilterSupport {
   static constexpr T s = T(S) / T(D);
};

template <int S, int D, int B, typename T>
struct HatFilterSupport {
   static constexpr T s = T(S) / T(D);
   static constexpr T s2 = s * 2;
   static constexpr T b = T(1) / B;
};

} // be::gfx::detail

template <int S = 1, int D = 2>
struct BoxFilter {
   template <typename T = float>
   T operator()(T x) {
      x = x < T(0) ? -x : x;
      if (x < detail::BoxFilterSupport<S, D, T>::s) {
         return T(1);
      } else {
         return T(0);
      }
   }
};

template <int S, int D>
struct FilterSupportRange<BoxFilter<S, D>> {
   template <typename T>
   T operator()() {
      return detail::BoxFilterSupport<S, D, T>::s;
   }
};

template <int S = 1, int D = 2, int B = 100000>
struct HatFilter {
   template <typename T = float>
   T operator()(T x) {
      x = x < T(0) ? -x : x;
      if (x < detail::HatFilterSupport<S, D, B, T>::s) {
         return T(1);
      } else if (x < detail::HatFilterSupport<S, D, B, T>::s2) {
            return detail::HatFilterSupport<S, D, B, T>::b;
      } else {
         return T(0);
      }
   }
};

template <int S, int D, int B>
struct FilterSupportRange<HatFilter<S, D, B>> {
   template <typename T>
   T operator()() {
      return detail::HatFilterSupport<S, D, B, T>::s2;
   }
};

template <int N = 2, int S = 1, int D = 1, int B = 100000>
struct StepFilter {
   template <typename T = float>
   T operator()(T x) {
      x = x < T(0) ? -x : x;
      if (x < detail::HatFilterSupport<S, D, B, T>::s) {
         return (T(1) - floor((x / detail::HatFilterSupport<S, D, B, T>::s) * T(N + 1)) / T(N)) + detail::HatFilterSupport<S, D, B, T>::b;
      } else {
         return T(0);
      }
   }
};

template <int N, int S, int D, int B>
struct FilterSupportRange<StepFilter<N, S, D, B>> {
   template <typename T>
   T operator()() {
      return detail::HatFilterSupport<S, D, B, T>::s;
   }
};


} // be::gfx
} // be

#endif
