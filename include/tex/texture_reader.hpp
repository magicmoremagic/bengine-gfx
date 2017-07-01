#pragma once
#ifndef BE_GFX_TEX_TEXTURE_READER_HPP_
#define BE_GFX_TEX_TEXTURE_READER_HPP_

#include "texture_reader_base.hpp"
#include <be/core/logging.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class TextureReader final : public TextureReaderBase {
public:
   TextureReader(bool strict = false, Log& log = default_log());

   using TextureReaderBase::reset;
   void reset(TextureFileFormat type);

   TextureReaderBase& inner();

private:
   void reset_() final;

   void read_(Buf<const UC> buf, const Path& path) final;
   void read_(Buf<const UC> buf, std::error_code& ec, const Path& path) noexcept final;

   TextureFileFormat format_() noexcept final;

   const TextureFileInfo& info_() final;
   const TextureFileInfo& info_(std::error_code& ec) noexcept final;

   Texture texture_() final;
   Texture texture_(std::error_code& ec) noexcept final;

   Image image_(std::size_t layer, std::size_t face, std::size_t level) final;
   Image image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept final;

   void setup_inner_(const Buf<const UC>& buf, std::error_code& ec) noexcept;

   TextureFileFormat requested_type_;
   TextureFileFormat inner_type_;
   std::unique_ptr<TextureReaderBase> inner_;
};

///////////////////////////////////////////////////////////////////////////////
std::unique_ptr<TextureReaderBase> make_texture_reader(TextureFileFormat format, bool strict = false, Log& log = default_log());

} // be::gfx::tex

#endif
