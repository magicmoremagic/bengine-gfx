#pragma once
#ifndef BE_GFX_TEX_BETX_WRITER_HPP_
#define BE_GFX_TEX_BETX_WRITER_HPP_

#include "betx_payload_compression_mode.hpp"
#include "texture_view.hpp"
#include "image_view.hpp"
#include <be/core/buf.hpp>
#include <be/core/filesystem.hpp>
#include <be/core/logging.hpp>
#include <be/core/byte_order.hpp>
#include <be/util/util_fs_autolink.hpp>
#include <be/util/util_compression_autolink.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class BetxWriter final : public Immovable {
public:
   using PayloadCompressionMode = detail::BetxPayloadCompressionMode;

   BetxWriter(Log& log = default_log());
   void reset();
   void texture(const ConstTextureView& view) noexcept;
   void image(const ConstImageView& view) noexcept;
   void payload_compression(PayloadCompressionMode mode = PayloadCompressionMode::zlib, I8 level = -1) noexcept;
   void endianness(ByteOrderType endianness = bo::Net::value) noexcept;

   // TODO metadata

   Buf<UC> write();
   Buf<UC> write(std::error_code& ec) noexcept;

   void write(const Path& path);
   void write(const Path& path, std::error_code& ec) noexcept;

private:
   Log& log_;
   ConstTextureView tex_;
   PayloadCompressionMode compression_;
   I8 compression_level_;
   ByteOrderType endianness_;
};

} // be::gfx::tex

#endif
