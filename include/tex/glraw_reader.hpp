#pragma once
#ifndef BE_GFX_TEX_GLRAW_READER_HPP_
#define BE_GFX_TEX_GLRAW_READER_HPP_

#include "default_texture_reader.hpp"
#include "betx_payload_compression_mode.hpp"
#include <be/core/logging.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_glraw(const Buf<const UC>& buf) noexcept;

///////////////////////////////////////////////////////////////////////////////
class GlrawReader final : public detail::DefaultTextureReader {
public:
   GlrawReader(bool strict = false, Log& log = default_log());

private:
   TextureFileFormat format_impl_() noexcept final;
   TextureFileInfo info_impl_(std::error_code& ec) noexcept final;
   Texture texture_(std::error_code& ec) noexcept final;
   Image image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept final;
};

} // be::gfx::tex

#endif
