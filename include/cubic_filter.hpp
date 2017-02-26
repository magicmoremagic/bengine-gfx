#pragma once
#ifndef BE_GFX_CUBIC_FILTER_HPP_
#define BE_GFX_CUBIC_FILTER_HPP_

#include "filter_traits.hpp"

namespace be {
namespace gfx {
namespace detail {

template <int B, int C, int D, typename T>
struct MitchellNetravaliBC {
   static constexpr T b = T(B) / T(D);
   static constexpr T c = T(C) / T(D);

   static constexpr T p = T(12 - 9 * b - 6 * c) / T(6);
   static constexpr T q = T(-18 + 12 * b + 6 * c) / T(6);
   static constexpr T s = T(6 - 2 * b) / T(6);

   static constexpr T t = T(-b - 6 * c) / T(6);
   static constexpr T u = T(6 * b + 30 * c) / T(6);
   static constexpr T v = T(-12 * b - 48 * c) / T(6);
   static constexpr T w = T(8 * b + 24 * c) / T(6);
};

} // be::gfx::detail

template <int B, int C, int D = 1>
struct MitchellNetravaliCubicFilter {
   template <typename T = float>
   T operator()(T x) {
      T xx = x * x;
      x = x < T(0) ? -x : x;
      T xxx = xx * x;
      if (x < T(1)) {
         return detail::MitchellNetravaliBC<B,C,D,T>::s +
            detail::MitchellNetravaliBC<B,C,D,T>::q * xx +
            detail::MitchellNetravaliBC<B,C,D,T>::p * xxx;
      } else if (x < T(2)) {
         return detail::MitchellNetravaliBC<B,C,D,T>::w +
            detail::MitchellNetravaliBC<B,C,D,T>::v * x +
            detail::MitchellNetravaliBC<B,C,D,T>::u * xx +
            detail::MitchellNetravaliBC<B,C,D,T>::t * xxx;
      } else {
         return T(0);
      }
   }
};

template <int B, int C, int D>
struct FilterSupportRange<MitchellNetravaliCubicFilter<B, C, D>> {
   template <typename T>
   T operator()() {
      return T(2);
   }
};

template <int D>
struct FilterSupportRange<MitchellNetravaliCubicFilter<0, 0, D>> {
   template <typename T>
   T operator()() {
      return T(1);
   }
};

using CubicHermiteFilter = MitchellNetravaliCubicFilter<0,0>;
using BSplineFilter = MitchellNetravaliCubicFilter<1,0>;
using CatmullRomFilter = MitchellNetravaliCubicFilter<0,1,2>;
using MitchellNetravaliFilter = MitchellNetravaliCubicFilter<1,1,3>;

template <int A, int D = 1>
using KeysFilter = MitchellNetravaliCubicFilter<D - 2 * A, A, D>;

template <typename T>
struct DynamicMitchellNetravaliCubicFilter {
   DynamicMitchellNetravaliCubicFilter(T b, T c)
      : p((T(12) - T(9) * b - T(6) * c) / T(6)),
        q((T(-18) + T(12) * b + T(6) * c) / T(6)),
        s((T(6) - T(2) * b) / T(6)),
        t((-b - T(6) * c) / T(6)),
        u((T(6) * b + T(30) * c) / T(6)),
        v((T(-12) * b - T(48) * c) / T(6)),
        w((T(8) * b + T(24) * c) / T(6)) { }

   T operator()(T x) {
      T xx = x * x;
      x = x < T(0) ? -x : x;
      T xxx = xx * x;
      if (x < T(1)) {
         return s + q * xx + p * xxx;
      } else if (x < T(2)) {
         return w + v * x + u * xx + t * xxx;
      } else {
         return T(0);
      }
   }

private:
   T p,q,s,t,u,v,w;
};

template <typename T>
struct FilterSupportRange<DynamicMitchellNetravaliCubicFilter<T>> {
   template <typename U>
   U operator()() {
      return U(2);
   }
};

template <typename T>
DynamicMitchellNetravaliCubicFilter<T> make_keys_filter(T alpha) {
   return DynamicMitchellNetravaliCubicFilter<T>(T(1) - T(2) * alpha, alpha);
}

} // be::gfx
} // be

#endif
