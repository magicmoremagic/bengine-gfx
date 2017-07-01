#pragma once
#ifndef BE_GFX_TEX_BETX_READER_HPP_
#define BE_GFX_TEX_BETX_READER_HPP_

#include "default_texture_reader.hpp"
#include "betx_payload_compression_mode.hpp"
#include <be/core/logging.hpp>
#include <be/util/util_compression_autolink.hpp>

namespace be::gfx::tex {
namespace detail {

struct BetxHeader;

} // be::gfx::tex::detail

///////////////////////////////////////////////////////////////////////////////
bool is_betx(const Buf<const UC>& buf) noexcept;

///////////////////////////////////////////////////////////////////////////////
class BetxReader final : public detail::DefaultTextureReader {
public:
   BetxReader(bool strict = false, Log& log = default_log());

private:
   void reset_impl_() noexcept final;
   TextureFileFormat format_impl_() noexcept final;
   TextureFileInfo info_impl_(std::error_code& ec) noexcept final;
   Texture texture_(std::error_code& ec) noexcept final;
   Image image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept final;

   TextureFileInfo info_v1_(const detail::BetxHeader& header, std::error_code& ec) noexcept;

   bool should_continue_(std::error_code new_error, std::error_code& ec) const noexcept;
   void try_fix_crlf_corruption_(std::error_code& ec) noexcept;
   void try_fix_lf_corruption_(std::error_code& ec) noexcept;

   TextureAlignment alignment_;
   U8 block_span_;
   bool big_endian_;
   detail::BetxPayloadCompressionMode payload_compression_;
   std::size_t texture_size_;
   Buf<const UC> payload_;
   Buf<const UC> metadata_;
};

} // be::gfx::tex

#endif
