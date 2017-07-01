#include "pch.hpp"
#include "tex/texture_reader_base.hpp"
#include <be/core/exceptions.hpp>
#include <be/util/get_file_contents.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
void TextureReaderBase::reset() {
   reset_();
}

///////////////////////////////////////////////////////////////////////////////
void TextureReaderBase::read(Buf<const UC> buf, const Path& path) {
   read_(std::move(buf), path);
}

///////////////////////////////////////////////////////////////////////////////
void TextureReaderBase::read(Buf<const UC> buf, std::error_code& ec, const Path& path) noexcept {
   read_(std::move(buf), ec, path);
}

///////////////////////////////////////////////////////////////////////////////
void TextureReaderBase::read(const Path& path) {
   read_(path);
}

///////////////////////////////////////////////////////////////////////////////
void TextureReaderBase::read(const Path& path, std::error_code& ec) noexcept {
   read_(path, ec);
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat TextureReaderBase::format() noexcept {
   return format_();
}

///////////////////////////////////////////////////////////////////////////////
const TextureFileInfo& TextureReaderBase::info() {
   return info_();
}

///////////////////////////////////////////////////////////////////////////////
const TextureFileInfo& TextureReaderBase::info(std::error_code& ec) noexcept {
   return info_(ec);
}

///////////////////////////////////////////////////////////////////////////////
Texture TextureReaderBase::texture() {
   return texture_();
}

///////////////////////////////////////////////////////////////////////////////
Texture TextureReaderBase::texture(std::error_code& ec) noexcept {
   return texture_(ec);
}

///////////////////////////////////////////////////////////////////////////////
Image TextureReaderBase::image(std::size_t layer, std::size_t face, std::size_t level) {
   return image_(layer, face, level);
}

///////////////////////////////////////////////////////////////////////////////
Image TextureReaderBase::image(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   return image_(ec, layer, face, level);
}

///////////////////////////////////////////////////////////////////////////////
TextureReaderBase::TextureReaderBase(bool strict, Log& log)
   : log_(log),
     strict_(strict) { }

///////////////////////////////////////////////////////////////////////////////
bool TextureReaderBase::strict() const {
   return strict_;
}

///////////////////////////////////////////////////////////////////////////////
Log& TextureReaderBase::log() const {
   return log_;
}

///////////////////////////////////////////////////////////////////////////////
void TextureReaderBase::read_(Buf<const UC> buf, const Path& path) {
   std::error_code ec;
   read_(std::move(buf), ec, path);
   if (ec) {
      throw RecoverableError(ec);
   }
}

///////////////////////////////////////////////////////////////////////////////
void TextureReaderBase::read_(const Path& path) {
   read_(util::get_file_contents_buf(path), path);
}

///////////////////////////////////////////////////////////////////////////////
void TextureReaderBase::read_(const Path& path, std::error_code& ec) noexcept {
   read_(util::get_file_contents_buf(path, ec), ec, path);
}

///////////////////////////////////////////////////////////////////////////////
const TextureFileInfo& TextureReaderBase::info_() {
   std::error_code ec;
   const TextureFileInfo& info = info_(ec);
   if (ec) {
      throw RecoverableError(ec);
   }
   return info;
}

///////////////////////////////////////////////////////////////////////////////
Texture TextureReaderBase::texture_() {
   Texture tex;
   std::error_code ec;
   tex = texture_(ec);
   if (ec) {
      throw RecoverableError(ec);
   }
   return tex;
}

///////////////////////////////////////////////////////////////////////////////
Image TextureReaderBase::image_(std::size_t layer, std::size_t face, std::size_t level) {
   Image img;
   std::error_code ec;
   img = image_(ec, layer, face, level);
   if (ec) {
      throw RecoverableError(ec);
   }
   return img;
}

} // be::gfx::tex
