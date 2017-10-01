#pragma once
#ifndef BE_GFX_TEX_KTX_READER_HPP_
#define BE_GFX_TEX_KTX_READER_HPP_

#include "default_texture_reader.hpp"
#include "betx_payload_compression_mode.hpp"
#include <be/core/logging.hpp>

namespace be::gfx::tex {
namespace detail {

struct KtxHeader;

} // be::gfx::tex::detail

///////////////////////////////////////////////////////////////////////////////
bool is_ktx(const Buf<const UC>& buf) noexcept;

///////////////////////////////////////////////////////////////////////////////
class KtxReader final : public detail::DefaultTextureReader {
public:
   KtxReader(bool strict = false, Log& log = default_log());

   const std::vector<std::pair<SV, SV>>& metadata();
   const std::vector<std::pair<SV, SV>>& metadata(std::error_code& ec) noexcept;

private:
   void reset_impl_() noexcept final;
   TextureFileFormat format_impl_() noexcept final;
   TextureFileInfo info_impl_(std::error_code& ec) noexcept final;
   Texture texture_(std::error_code& ec) noexcept final;
   Image image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept final;
   
   TextureFileInfo info_v11_(const detail::KtxHeader& header, std::error_code& ec) noexcept;

   bool should_continue_(std::error_code new_error, std::error_code& ec) const noexcept;

   bool big_endian_;
   std::size_t texture_size_;
   Buf<const UC> payload_;
   std::vector<std::pair<SV, SV>> metadata_;
};

} // be::gfx::tex

#endif
