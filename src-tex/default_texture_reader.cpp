#include "pch.hpp"
#include "tex/default_texture_reader.hpp"
#include <be/core/exceptions.hpp>
#include <be/util/get_file_contents.hpp>

namespace be::gfx::tex::detail {

///////////////////////////////////////////////////////////////////////////////
DefaultTextureReader::DefaultTextureReader(bool strict, Log& log)
   : TextureReaderBase(strict, log) { }

///////////////////////////////////////////////////////////////////////////////
const Path& DefaultTextureReader::path() const {
   return path_;
}

///////////////////////////////////////////////////////////////////////////////
void DefaultTextureReader::reset_() {
   reset_caches_();
   buf_ = Buf<const UC>();
}

///////////////////////////////////////////////////////////////////////////////
void DefaultTextureReader::read_(Buf<const UC> buf, const Path& path) {
   reset_caches_();
   buf_ = std::move(buf);
   path_ = path;
}

///////////////////////////////////////////////////////////////////////////////
void DefaultTextureReader::read_(Buf<const UC> buf, std::error_code& ec, const Path& path) noexcept {
   reset_caches_();
   buf_ = std::move(buf);
   path_ = path;
}

///////////////////////////////////////////////////////////////////////////////
void DefaultTextureReader::read_(const Path& path) {
   reset_caches_();
   buf_ = util::get_file_contents_buf(path);
   path_ = path;
}

///////////////////////////////////////////////////////////////////////////////
void DefaultTextureReader::read_(const Path& path, std::error_code& ec) noexcept {
   reset_caches_();
   buf_ = util::get_file_contents_buf(path, ec);
   path_ = path;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat DefaultTextureReader::format_() noexcept {
   if (cached_format_ == TextureFileFormat::unknown) {
      cached_format_ = format_impl_();
   }
   return cached_format_;
}

///////////////////////////////////////////////////////////////////////////////
const TextureFileInfo& DefaultTextureReader::info_() {
   if (cached_info_.file_format == TextureFileFormat::unknown) {
      cached_info_error_ = std::error_code();
      cached_info_ = info_impl_(cached_info_error_);
      cached_format_ = cached_info_.file_format;
   }
   if (cached_info_error_) {
      throw RecoverableError(cached_info_error_);
   }
   return cached_info_;
}

///////////////////////////////////////////////////////////////////////////////
const TextureFileInfo& DefaultTextureReader::info_(std::error_code& ec) noexcept {
   if (cached_info_.file_format == TextureFileFormat::unknown) {
      cached_info_error_ = std::error_code();
      cached_info_ = info_impl_(cached_info_error_);
      cached_format_ = cached_info_.file_format;
   }
   if (cached_info_error_) {
      ec = cached_info_error_;
   }
   return cached_info_;
}

///////////////////////////////////////////////////////////////////////////////
void DefaultTextureReader::reset_caches_() noexcept {
   reset_impl_();
   cached_format_ = TextureFileFormat::unknown;
   cached_info_ = TextureFileInfo();
   cached_info_error_ = std::error_code();
   path_ = Path();
}

///////////////////////////////////////////////////////////////////////////////
void DefaultTextureReader::reset_impl_() noexcept { }

} // be::gfx::tex::detail
