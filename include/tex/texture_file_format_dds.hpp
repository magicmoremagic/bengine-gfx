#pragma once
#ifndef BE_GFX_TEX_TEXTURE_FILE_FORMAT_DDS_HPP_
#define BE_GFX_TEX_TEXTURE_FILE_FORMAT_DDS_HPP_

#include <be/core/buf.hpp>

namespace be::gfx::tex::detail {

bool is_dds(const Buf<const UC>& buf);

} // be::gfx::tex::detail

#endif
