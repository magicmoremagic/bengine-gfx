#pragma once
#ifndef BE_GFX_TEX_DEFAULT_TEXTURE_READER_HPP_
#define BE_GFX_TEX_DEFAULT_TEXTURE_READER_HPP_

#include "texture_reader_base.hpp"

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
class DefaultTextureReader : public TextureReaderBase {
protected:
   DefaultTextureReader(bool strict, Log& log);

   Buf<const UC> buf_;

   const Path& path() const;

private:
   void reset_() final;

   void read_(Buf<const UC> buf, const Path& path) final;
   void read_(Buf<const UC> buf, std::error_code& ec, const Path& path) noexcept final;

   void read_(const Path& path) final;
   void read_(const Path& path, std::error_code& ec) noexcept final;

   TextureFileFormat format_() noexcept final;

   const TextureFileInfo& info_() final;
   const TextureFileInfo& info_(std::error_code& ec) noexcept final;

   void reset_caches_() noexcept;

   virtual void reset_impl_() noexcept;
   virtual TextureFileFormat format_impl_() noexcept = 0;
   virtual TextureFileInfo info_impl_(std::error_code& ec) noexcept = 0;

   TextureFileFormat cached_format_;
   TextureFileInfo cached_info_;
   std::error_code cached_info_error_;
   Path path_;
};

} // be::gfx::tex::detail

#endif
