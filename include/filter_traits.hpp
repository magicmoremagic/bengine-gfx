#pragma once
#ifndef BE_TEXI_FILTER_TRAITS_HPP_
#define BE_TEXI_FILTER_TRAITS_HPP_

namespace be {
namespace texi {

template <typename F>
struct FilterSupportRange {
   template <typename T>
   T operator()() {
      return T(1);
   }
};

} // be::texi
} // be

#endif
