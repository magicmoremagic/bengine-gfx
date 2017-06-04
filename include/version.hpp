#pragma once
#ifndef BE_GFX_VERSION_HPP_
#define BE_GFX_VERSION_HPP_

#include <be/core/macros.hpp>

#define BE_GFX_VERSION_MAJOR 0
#define BE_GFX_VERSION_MINOR 1
#define BE_GFX_VERSION_REV 8

/*!! include('common/version', 'be::gfx') !! 6 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
#define BE_GFX_VERSION (BE_GFX_VERSION_MAJOR * 100000 + BE_GFX_VERSION_MINOR * 1000 + BE_GFX_VERSION_REV)
#define BE_GFX_VERSION_STRING "be::gfx " BE_STRINGIFY(BE_GFX_VERSION_MAJOR) "." BE_STRINGIFY(BE_GFX_VERSION_MINOR) "." BE_STRINGIFY(BE_GFX_VERSION_REV)

/* ######################### END OF GENERATED CODE ######################### */

#endif
