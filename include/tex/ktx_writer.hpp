#pragma once
#ifndef BE_GFX_TEX_KTX_WRITER_HPP_
#define BE_GFX_TEX_KTX_WRITER_HPP_

#include "texture_view.hpp"
#include "image_view.hpp"
#include <be/core/buf.hpp>
#include <be/core/filesystem.hpp>
#include <be/core/logging.hpp>
#include <be/core/byte_order.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class KtxWriter final : public Immovable {
public:
   KtxWriter(Log& log = default_log());
   void reset();
   void texture(const ConstTextureView& view) noexcept;
   void image(const ConstImageView& view) noexcept;
   void endianness(ByteOrderType endianness = bo::Host::value) noexcept;
   void metadata(SV key, SV value);

   Buf<UC> write();
   Buf<UC> write(std::error_code& ec) noexcept;

   void write(const Path& path);
   void write(const Path& path, std::error_code& ec) noexcept;

private:
   Log& log_;
   ConstTextureView tex_;
   ByteOrderType endianness_;
   std::vector<std::pair<SV, SV>> metadata_entries_;
};

} // be::gfx::tex

#endif
