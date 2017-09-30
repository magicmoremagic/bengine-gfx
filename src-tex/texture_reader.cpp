#include "pch.hpp"
#include "tex/texture_reader.hpp"
#include "tex/betx_reader.hpp"
#include "tex/bmp_reader.hpp"
#include "tex/dds_reader.hpp"
#include "tex/gif_reader.hpp"
#include "tex/hdr_reader.hpp"
#include "tex/jpeg_reader.hpp"
#include "tex/ktx_reader.hpp"
#include "tex/png_reader.hpp"
#include "tex/pnm_reader.hpp"
#include "tex/psd_reader.hpp"
#include "tex/tga_reader.hpp"
#include <be/core/exceptions.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
TextureReader::TextureReader(bool strict, Log& log)
   : TextureReaderBase(strict, log),
     requested_type_(TextureFileFormat::unknown),
     inner_type_(TextureFileFormat::unknown) { }

///////////////////////////////////////////////////////////////////////////////
void TextureReader::reset(TextureFileFormat type) {
   requested_type_ = type;
   inner_type_ = TextureFileFormat::unknown;
   inner_.reset();
}

///////////////////////////////////////////////////////////////////////////////
TextureReaderBase& TextureReader::inner() {
   return *inner_;
}

///////////////////////////////////////////////////////////////////////////////
void TextureReader::reset_() {
   reset(TextureFileFormat::unknown);
}

///////////////////////////////////////////////////////////////////////////////
void TextureReader::read_(Buf<const UC> buf, const Path& path) {
   std::error_code ec;
   setup_inner_(buf, ec);
   if (ec) {
      throw RecoverableError(ec);
   }
   inner_->read(std::move(buf), path);
}

///////////////////////////////////////////////////////////////////////////////
void TextureReader::read_(Buf<const UC> buf, std::error_code& ec, const Path& path) noexcept {
   setup_inner_(buf, ec);
   if (!ec) {
      inner_->read(std::move(buf), ec, path);
   }
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat TextureReader::format_() noexcept {
   return inner_type_;
}

///////////////////////////////////////////////////////////////////////////////
const TextureFileInfo& TextureReader::info_() {
   return inner_->info();
}

///////////////////////////////////////////////////////////////////////////////
const TextureFileInfo& TextureReader::info_(std::error_code& ec) noexcept {
   return inner_->info(ec);
}

///////////////////////////////////////////////////////////////////////////////
Texture TextureReader::texture_() {
   return inner_->texture();
}

///////////////////////////////////////////////////////////////////////////////
Texture TextureReader::texture_(std::error_code& ec) noexcept {
   return inner_->texture(ec);
}

///////////////////////////////////////////////////////////////////////////////
Image TextureReader::image_(std::size_t layer, std::size_t face, std::size_t level) {
   return inner_->image(layer, face, level);
}

///////////////////////////////////////////////////////////////////////////////
Image TextureReader::image_(std::error_code& ec, std::size_t layer, std::size_t face, std::size_t level) noexcept {
   return inner_->image(ec, layer, face, level);
}

///////////////////////////////////////////////////////////////////////////////
void TextureReader::setup_inner_(const Buf<const UC>& buf, std::error_code& ec) noexcept {
   TextureFileFormat format = requested_type_;
   if (format == TextureFileFormat::unknown) {
      if (is_betx(buf))       { format = TextureFileFormat::betx;  }
      else if (is_ktx(buf))   { format = TextureFileFormat::ktx;   }
      else if (is_png(buf))   { format = TextureFileFormat::png;   }
      else if (is_dds(buf))   { format = TextureFileFormat::dds;   }
      else if (is_hdr(buf))   { format = TextureFileFormat::hdr;   }
      else if (is_gif(buf))   { format = TextureFileFormat::gif;   }
      else if (is_psd(buf))   { format = TextureFileFormat::psd;   }
      else if (is_jpeg(buf))  { format = TextureFileFormat::jpeg;  }
      else if (is_bmp(buf))   { format = TextureFileFormat::bmp;   }
      else if (is_pnm(buf))   { format = TextureFileFormat::pnm;   }
      else if (is_tga(buf))   { format = TextureFileFormat::tga;   }
      else {
         ec = std::make_error_code(std::errc::not_supported);
         return;
      }
   }
   if (inner_type_ != format) {
      inner_ = make_texture_reader(format, strict(), log());
      if (inner_) {
         inner_type_ = format;
      } else {
         ec = std::make_error_code(std::errc::not_supported);
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
std::unique_ptr<TextureReaderBase> make_texture_reader(TextureFileFormat format, bool strict, Log& log) {
   switch (format) {
      case TextureFileFormat::betx:    return std::make_unique<BetxReader>(strict, log);
      case TextureFileFormat::ktx:     return std::make_unique<KtxReader>(strict, log);
      case TextureFileFormat::png:     return std::make_unique<PngReader>(strict, log);
      case TextureFileFormat::dds:     return std::make_unique<DdsReader>(strict, log);
      case TextureFileFormat::hdr:     return std::make_unique<HdrReader>(strict, log);
      case TextureFileFormat::gif:     return std::make_unique<GifReader>(strict, log);
      case TextureFileFormat::psd:     return std::make_unique<PsdReader>(strict, log);
      case TextureFileFormat::jpeg:    return std::make_unique<JpegReader>(strict, log);
      case TextureFileFormat::bmp:     return std::make_unique<BmpReader>(strict, log);
      case TextureFileFormat::pnm:     return std::make_unique<PnmReader>(strict, log);
      case TextureFileFormat::tga:     return std::make_unique<TgaReader>(strict, log);
      default: return std::unique_ptr<TextureReaderBase>();
   }
}

} // be::gfx::tex
