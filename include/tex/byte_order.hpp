#pragma once
#ifndef BE_GFX_TEX_BYTE_ORDER_HPP_
#define BE_GFX_TEX_BYTE_ORDER_HPP_

#include "tex/texture_storage.hpp"
#include "tex/block_packing.hpp"

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
void reverse_endianness(TextureStorage& storage, BlockPacking packing);

} // be::gfx::tex

#endif
