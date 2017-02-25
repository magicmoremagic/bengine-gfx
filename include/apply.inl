#if !defined(BE_TEXI_APPLY_HPP_) && !defined(DOXYGEN)
#include "apply.hpp"
#elif !defined(BE_TEXI_APPLY_INL_)
#define BE_TEXI_APPLY_INL_

namespace gli {
namespace detail {

template <typename vec_type>
struct compute_apply_1d {
   typedef typename apply_func<vec_type>::type func_type;
   typedef texture1d::size_type size_type;
   typedef texture1d::extent_type extent_type;

   static void call(texture1d& Output, texture1d const& A, func_type Func) {
      GLI_ASSERT(all(equal(A.extent(), Output.extent())));
      GLI_ASSERT(A.levels() == Output.levels());
      GLI_ASSERT(A.size() == Output.size());

      for(size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
         extent_type const TexelCount(A.extent(LevelIndex));
         extent_type TexelIndex(0);

         for(TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
            Output.store<vec_type>(TexelIndex, LevelIndex, Func(
               A.load<vec_type>(TexelIndex, LevelIndex)));
         }
      }
   }
};

template <typename vec_type>
struct compute_apply_1d_array {
   typedef typename apply_func<vec_type>::type func_type;
   typedef texture1d_array::size_type size_type;
   typedef texture1d_array::extent_type extent_type;

   static void call(texture1d_array& Output, texture1d_array const& A, func_type Func) {
      GLI_ASSERT(all(equal(A.extent(), Output.extent())));
      GLI_ASSERT(A.layers() == Output.layers());
      GLI_ASSERT(A.levels() == Output.levels());
      GLI_ASSERT(A.size() == Output.size());

      for(size_type LayerIndex = 0, LayerCount = A.layers(); LayerIndex < LayerCount; ++LayerIndex)
         for(size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
            extent_type const TexelCount(A.extent(LevelIndex));
            extent_type TexelIndex(0);

            for(TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
               Output.store<vec_type>(TexelIndex, LayerIndex, LevelIndex, Func(
                  A.load<vec_type>(TexelIndex, LayerIndex, LevelIndex)));
            }
         }
   }
};

template <typename vec_type>
struct compute_apply_2d {
   typedef typename apply_func<vec_type>::type func_type;
   typedef texture2d::size_type size_type;
   typedef texture2d::extent_type extent_type;

   static void call(texture2d& Output, texture2d const& A, func_type Func) {
      GLI_ASSERT(all(equal(A.extent(), Output.extent())));
      GLI_ASSERT(A.levels() == Output.levels());
      GLI_ASSERT(A.size() == Output.size());

      for(size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
         extent_type const TexelCount(A.extent(LevelIndex));
         extent_type TexelIndex(0);

         for(TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
            for(TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
               Output.store<vec_type>(TexelIndex, LevelIndex, Func(
                  A.load<vec_type>(TexelIndex, LevelIndex)));
            }
      }
   }
};

template <typename vec_type>
struct compute_apply_2d_array {
   typedef typename apply_func<vec_type>::type func_type;
   typedef texture2d_array::size_type size_type;
   typedef texture2d_array::extent_type extent_type;

   static void call(texture2d_array& Output, texture2d_array const& A, func_type Func) {
      GLI_ASSERT(all(equal(A.extent(), Output.extent())));
      GLI_ASSERT(A.layers() == Output.layers());
      GLI_ASSERT(A.levels() == Output.levels());
      GLI_ASSERT(A.size() == Output.size());

      for(size_type LayerIndex = 0, LayerCount = A.layers(); LayerIndex < LayerCount; ++LayerIndex)
         for(size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
            extent_type const TexelCount(A.extent(LevelIndex));
            extent_type TexelIndex(0);

            for(TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
               for(TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
                  Output.store<vec_type>(TexelIndex, LayerIndex, LevelIndex, Func(
                     A.load<vec_type>(TexelIndex, LayerIndex, LevelIndex)));
               }
         }
   }
};

template <typename vec_type>
struct compute_apply_3d {
   typedef typename apply_func<vec_type>::type func_type;
   typedef texture3d::size_type size_type;
   typedef texture3d::extent_type extent_type;

   static void call(texture3d& Output, texture3d const& A, func_type Func) {
      GLI_ASSERT(all(equal(A.extent(), Output.extent())));
      GLI_ASSERT(A.levels() == Output.levels());
      GLI_ASSERT(A.size() == Output.size());

      for(size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
         extent_type const TexelCount(A.extent(LevelIndex));
         extent_type TexelIndex(0);

         for(TexelIndex.z = 0; TexelIndex.z < TexelCount.z; ++TexelIndex.z)
            for(TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
               for(TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
                  Output.store<vec_type>(TexelIndex, LevelIndex, Func(
                     A.load<vec_type>(TexelIndex, LevelIndex)));
               }
      }
   }
};

template <typename vec_type>
struct compute_apply_cube {
   typedef typename apply_func<vec_type>::type func_type;
   typedef texture_cube::size_type size_type;
   typedef texture_cube::extent_type extent_type;

   static void call(texture_cube& Output, texture_cube const& A, func_type Func) {
      GLI_ASSERT(all(equal(A.extent(), Output.extent())));
      GLI_ASSERT(A.faces() == Output.faces());
      GLI_ASSERT(A.levels() == Output.levels());
      GLI_ASSERT(A.size() == Output.size());

      for(size_type FaceIndex = 0, FaceCount = A.faces(); FaceIndex < FaceCount; ++FaceIndex)
         for(size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
            extent_type const TexelCount(A.extent(LevelIndex));
            extent_type TexelIndex(0);

            for(TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
               for(TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
                  Output.store<vec_type>(TexelIndex, FaceIndex, LevelIndex, Func(
                     A.load<vec_type>(TexelIndex, FaceIndex, LevelIndex)));
               }
         }
   }
};

template <typename vec_type>
struct compute_apply_cube_array {
   typedef typename apply_func<vec_type>::type func_type;
   typedef texture_cube_array::size_type size_type;
   typedef texture_cube_array::extent_type extent_type;

   static void call(texture_cube_array& Output, texture_cube_array const& A, func_type Func) {
      GLI_ASSERT(all(equal(A.extent(), Output.extent())));
      GLI_ASSERT(A.layers() == Output.layers());
      GLI_ASSERT(A.levels() == Output.levels());
      GLI_ASSERT(A.size() == Output.size());

      for(size_type LayerIndex = 0, LayerCount = A.layers(); LayerIndex < LayerCount; ++LayerIndex)
         for(size_type FaceIndex = 0, FaceCount = A.faces(); FaceIndex < FaceCount; ++FaceIndex)
            for(size_type LevelIndex = 0, LevelCount = A.levels(); LevelIndex < LevelCount; ++LevelIndex) {
               extent_type const TexelCount(A.extent(LevelIndex));
               extent_type TexelIndex(0);

               for(TexelIndex.y = 0; TexelIndex.y < TexelCount.y; ++TexelIndex.y)
                  for(TexelIndex.x = 0; TexelIndex.x < TexelCount.x; ++TexelIndex.x) {
                     Output.store<vec_type>(TexelIndex, LayerIndex, FaceIndex, LevelIndex, Func(
                        A.load<vec_type>(TexelIndex, LayerIndex, FaceIndex, LevelIndex)));
                  }
            }
   }
};

} // gli::detail

template <typename vec_type>
inline void apply(texture1d& Out, texture1d const& In, typename apply_func<vec_type>::type Func) {
   detail::compute_apply_1d<vec_type>::call(Out, In, Func);
}

template <typename vec_type>
inline void apply(texture1d_array& Out, texture1d_array const& In, typename apply_func<vec_type>::type Func) {
   detail::compute_apply_1d_array<vec_type>::call(Out, In, Func);
}

template <typename vec_type>
inline void apply(texture2d& Out, texture2d const& In, typename apply_func<vec_type>::type Func) {
   detail::compute_apply_2d<vec_type>::call(Out, In, Func);
}

template <typename vec_type>
inline void apply(texture2d_array& Out, texture2d_array const& In, typename apply_func<vec_type>::type Func) {
   detail::compute_apply_2d_array<vec_type>::call(Out, In, Func);
}

template <typename vec_type>
inline void apply(texture3d& Out, texture3d const& In, typename apply_func<vec_type>::type Func) {
   detail::compute_apply_3d<vec_type>::call(Out, In, Func);
}

template <typename vec_type>
inline void apply(texture_cube& Out, texture_cube const& In, typename apply_func<vec_type>::type Func) {
   detail::compute_apply_cube<vec_type>::call(Out, In, Func);
}

template <typename vec_type>
inline void apply(texture_cube_array& Out, texture_cube_array const& In, typename apply_func<vec_type>::type Func) {
   detail::compute_apply_cube_array<vec_type>::call(Out, In, Func);
}

} // gli

#endif
