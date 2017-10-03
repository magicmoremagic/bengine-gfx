#pragma once
#ifndef BE_GFX_TEX_HDR_WRITER_HPP_
#define BE_GFX_TEX_HDR_WRITER_HPP_

#include "texture_view.hpp"
#include "image_view.hpp"
#include <be/core/buf.hpp>
#include <be/core/filesystem.hpp>
#include <be/core/logging.hpp>
#include <be/core/byte_order.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class HdrWriter final : public Immovable {
public:
   HdrWriter(Log& log = default_log());
   void reset();
   void image(const ConstImageView& view, I32 z = 0) noexcept;

   Buf<UC> write();
   Buf<UC> write(std::error_code& ec) noexcept;

   void write(const Path& path);
   void write(const Path& path, std::error_code& ec) noexcept;

private:
   Log& log_;
   ConstImageView img_;
   I32 z_;
};

} // be::gfx::tex

#endif
