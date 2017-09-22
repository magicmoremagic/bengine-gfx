#pragma once
#ifndef BE_GFX_TEX_TEXTURE_READER_BASE_HPP_
#define BE_GFX_TEX_TEXTURE_READER_BASE_HPP_

#include "texture.hpp"
#include "image.hpp"
#include "texture_file_info.hpp"
#include <be/core/buf.hpp>
#include <be/core/filesystem.hpp>
#include <be/core/log.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class TextureReaderBase : public Immovable {
public:
   virtual ~TextureReaderBase() = default;

   void reset();

   void read(Buf<const UC> buf, const Path& path = Path());
   void read(Buf<const UC> buf, std::error_code& ec, const Path& path = Path()) noexcept;

   void read(const Path& path);
   void read(const Path& path, std::error_code& ec) noexcept;

   TextureFileFormat format() noexcept;

   const TextureFileInfo& info();
   const TextureFileInfo& info(std::error_code& ec) noexcept;

   Texture texture();
   Texture texture(std::error_code& ec) noexcept;

   Image image(std::size_t layer = 0, std::size_t face = 0, std::size_t level = 0);
   Image image(std::error_code& ec, std::size_t layer = 0, std::size_t face = 0, std::size_t level = 0) noexcept;

   // TODO metadata

protected:
   TextureReaderBase(bool strict, Log& log);

   bool strict() const;
   Log& log() const;

private:
   virtual void reset_() = 0;

   virtual void read_(Buf<const UC> buf, const Path& path);
   virtual void read_(Buf<const UC> buf, std::error_code& ec, const Path& path) noexcept = 0;

   virtual void read_(const Path& path);
   virtual void read_(const Path& path, std::error_code& ec) noexcept;

   virtual TextureFileFormat format_() noexcept = 0;

   virtual const TextureFileInfo& info_();
   virtual const TextureFileInfo& info_(std::error_code& ec) noexcept = 0;

   virtual Texture texture_();
   virtual Texture texture_(std::error_code& ec) noexcept = 0;

   virtual Image image_(std::size_t layer, std::size_t face, std::size_t level);
   virtual Image image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept = 0;

   Log& log_;
   bool strict_;
};

} // be::gfx::tex

#endif
