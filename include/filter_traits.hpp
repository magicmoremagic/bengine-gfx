#pragma once
#ifndef BE_GFX_FILTER_TRAITS_HPP_
#define BE_GFX_FILTER_TRAITS_HPP_

namespace be {
namespace gfx {

template <typename F>
struct FilterSupportRange {
   template <typename T>
   T operator()() {
      return T(1);
   }
};

} // be::gfx
} // be

#endif
