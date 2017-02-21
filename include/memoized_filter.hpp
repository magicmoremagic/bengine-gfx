#pragma once
#ifndef BE_TEXI_MEMOIZED_FILTER_HPP_
#define BE_TEXI_MEMOIZED_FILTER_HPP_

#include "filter_traits.hpp"
#include <map>

namespace be {
namespace texi {

template <typename T, typename F>
struct MemoizedFilter {
   template <typename U>
   U operator()(U x) {
      T tx = T(x);
      auto it = memo_.find(tx);
      if (it == memo_.end()) {
         T val = inner_(tx);
         memo_.emplace(tx, val);
         return U(val);
      } else {
         return U(it->second);
      }
   }

private:
   F inner_;
   std::map<T, T> memo_;
};

template <typename T, typename F>
struct FilterSupportRange<MemoizedFilter<T, F>> : public FilterSupportRange<F> { };

} // be::texi
} // be

#endif
