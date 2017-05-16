#pragma once
#ifndef BE_GFX_TEX_TEXTURE_FILE_FORMAT_GIF_HPP_
#define BE_GFX_TEX_TEXTURE_FILE_FORMAT_GIF_HPP_

#include <be/core/buf.hpp>

namespace be::gfx::tex::detail {

bool is_gif(const Buf<const UC>& buf);

} // be::gfx::tex::detail

#endif
