#pragma once
#ifndef BE_GFX_TEX_PNG_READER_HPP_
#define BE_GFX_TEX_PNG_READER_HPP_

#include "default_texture_reader.hpp"
#include "betx_payload_compression_mode.hpp"
#include <be/core/logging.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
bool is_png(const Buf<const UC>& buf) noexcept;

///////////////////////////////////////////////////////////////////////////////
class PngReader final : public detail::DefaultTextureReader {
public:
   PngReader(bool strict = false, Log& log = default_log());

private:
   void reset_impl_() noexcept final;
   TextureFileFormat format_impl_() noexcept final;
   TextureFileInfo info_impl_(std::error_code& ec) noexcept final;
   Texture texture_(std::error_code& ec) noexcept final;
   Image image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept final;

   std::size_t texture_size_;
};

} // be::gfx::tex

#endif
