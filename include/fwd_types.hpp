#pragma once
#ifndef BE_TEXI_FWD_TYPES_HPP_
#define BE_TEXI_FWD_TYPES_HPP_

#include <glm/fwd.hpp>

namespace gli {

typedef glm::vec<1, int, glm::highp> extent1d;
typedef glm::ivec2 extent2d;
typedef glm::ivec3 extent3d;
typedef glm::ivec4 extent4d;

class image;
class texture;
class texture1d;
class texture1d_array;
class texture2d;
class texture2d_array;
class texture3d;
class texture_cube;
class texture_cube_array;

class sampler;
template <typename T, glm::precision P = glm::defaultp>
class sampler1d;
template <typename T, glm::precision P = glm::defaultp>
class sampler1d_array;
template <typename T, glm::precision P = glm::defaultp>
class sampler2d;
template <typename T, glm::precision P = glm::defaultp>
class sampler2d_array;
template <typename T, glm::precision P = glm::defaultp>
class sampler3d;
template <typename T, glm::precision P = glm::defaultp>
class sampler_cube;
template <typename T, glm::precision P = glm::defaultp>
class sampler_cube_array;

} // gli

namespace be {
namespace texi {

using gli::extent1d;
using gli::extent2d;
using gli::extent3d;
using gli::extent4d;

using gli::image;
using gli::texture;
using gli::texture1d;
using gli::texture1d_array;
using gli::texture2d;
using gli::texture2d_array;
using gli::texture3d;
using gli::texture_cube;
using gli::texture_cube_array;

using gli::sampler;
using gli::sampler1d;
using gli::sampler1d_array;
using gli::sampler2d;
using gli::sampler2d_array;
using gli::sampler3d;
using gli::sampler_cube;
using gli::sampler_cube_array;

} // be::texi
} // be

#endif
