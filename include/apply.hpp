#pragma once
#ifndef BE_TEXI_APPLY_HPP_
#define BE_TEXI_APPLY_HPP_

#include <gli/texture1d.hpp>
#include <gli/texture1d_array.hpp>
#include <gli/texture2d.hpp>
#include <gli/texture2d_array.hpp>
#include <gli/texture3d.hpp>
#include <gli/texture_cube.hpp>
#include <gli/texture_cube_array.hpp>

namespace gli {

template <typename vec_type>
struct apply_func {
   typedef vec_type(*type)(vec_type const & A);
};

template <typename vec_type>
void apply(texture1d & Out, texture1d const & In, typename apply_func<vec_type>::type TexelFunc);

template <typename vec_type>
void apply(texture1d_array & Out, texture1d_array const & In, typename apply_func<vec_type>::type TexelFunc);

template <typename vec_type>
void apply(texture2d & Out, texture2d const & In, typename apply_func<vec_type>::type TexelFunc);

template <typename vec_type>
void apply(texture2d_array & Out, texture2d_array const & In, typename apply_func<vec_type>::type TexelFunc);

template <typename vec_type>
void apply(texture3d & Out, texture3d const & In, typename apply_func<vec_type>::type TexelFunc);

template <typename vec_type>
void apply(texture_cube & Out, texture_cube const & In, typename apply_func<vec_type>::type TexelFunc);

template <typename vec_type>
void apply(texture_cube_array & Out, texture_cube_array const & In, typename apply_func<vec_type>::type TexelFunc);

} // gli

#include "apply.inl"

#endif
