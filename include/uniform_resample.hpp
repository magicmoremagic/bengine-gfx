#pragma once
#ifndef BE_TEXI_UNIFORM_RESAMPLE_HPP_
#define BE_TEXI_UNIFORM_RESAMPLE_HPP_

#include "fwd_types.hpp"
#include "cubic_filter.hpp"
#include "ignore_wrap.hpp"
#include <be/core/glm.hpp>
#include <gli/image.hpp>
#include <glm/common.hpp>
#include <map>

namespace be {
namespace texi {

template <typename T, typename F = MitchellNetravaliFilter, typename W = IgnoreWrap>
void uniform_resample_3d(image out, image in, F32 scale, quat rotation = quat(1.f, vec3()), vec3 offset = vec3(), F32 support_scale = 1.f, F filter = F(), W wrap = W());

template <typename T, typename F = MitchellNetravaliFilter, typename W = IgnoreWrap>
void uniform_resample_2d(image out, image in, F32 scale, F32 rotation = 0, vec2 offset = vec2(), F32 support_scale = 1.f, F filter = F(), W wrap = W());

template <typename T, typename F = MitchellNetravaliFilter, typename W = IgnoreWrap>
void uniform_resample_1d(image out, image in, F32 scale, F32 offset = 0, F32 support_scale = 1.f, F filter = F(), W wrap = W());

} // be::texi
} // be

#include "uniform_resample.inl"

#endif
