#include "pch.hpp"
#include "tex/read.hpp"
#include "tex/read_betx.hpp"
#include "tex/read_bmp.hpp"
#include "tex/read_dds.hpp"
#include "tex/read_gif.hpp"
#include "tex/read_glraw.hpp"
#include "tex/read_hdr.hpp"
#include "tex/read_jpeg.hpp"
#include "tex/read_ktx.hpp"
#include "tex/read_pic.hpp"
#include "tex/read_png.hpp"
#include "tex/read_pnm.hpp"
#include "tex/read_psd.hpp"
#include "tex/read_tga.hpp"
#include <be/util/files.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat read_format(const Buf<const UC>& buf) {
   if (is_betx(buf)) return TextureFileFormat::betx;
   else if (is_ktx(buf)) return TextureFileFormat::ktx;
   else if (is_png(buf)) return TextureFileFormat::png;
   else if (is_glraw(buf)) return TextureFileFormat::glraw;
   else if (is_dds(buf)) return TextureFileFormat::dds;
   else if (is_hdr(buf)) return TextureFileFormat::hdr;
   else if (is_gif(buf)) return TextureFileFormat::gif;
   else if (is_pic(buf)) return TextureFileFormat::pic;
   else if (is_psd(buf)) return TextureFileFormat::psd;
   else if (is_jpeg(buf)) return TextureFileFormat::jpeg;
   else if (is_bmp(buf)) return TextureFileFormat::bmp;
   else if (is_pnm(buf)) return TextureFileFormat::pnm;
   else if (is_tga(buf)) return TextureFileFormat::tga;
   else return TextureFileFormat::unknown;
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_info(const Buf<const UC>& buf) {
   return read_info(read_format(buf), buf);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_info(Path path) {
   auto result = util::get_file_contents_buf(path);
   switch (result.second) {
      case util::FileReadError::none:              return read_info(std::move(result.first));
      case util::FileReadError::file_not_found:    return std::make_pair(TextureFileInfo(), TextureFileReadError::file_not_found);
      case util::FileReadError::file_not_readable: return std::make_pair(TextureFileInfo(), TextureFileReadError::file_not_readable);
      case util::FileReadError::out_of_memory:     return std::make_pair(TextureFileInfo(), TextureFileReadError::out_of_memory);
      default:                                     return std::make_pair(TextureFileInfo(), TextureFileReadError::unknown_filesystem_error);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_info(TextureFileFormat type, const Buf<const UC>& buf) {
   switch (type) {
      case TextureFileFormat::betx:    return read_betx_info(buf);
      case TextureFileFormat::ktx:     return read_ktx_info(buf);
      case TextureFileFormat::png:     return read_png_info(buf);
      case TextureFileFormat::glraw:   return read_glraw_info(buf);
      case TextureFileFormat::dds:     return read_dds_info(buf);
      case TextureFileFormat::hdr:     return read_hdr_info(buf);
      case TextureFileFormat::gif:     return read_gif_info(buf);
      case TextureFileFormat::pic:     return read_pic_info(buf);
      case TextureFileFormat::psd:     return read_psd_info(buf);
      case TextureFileFormat::jpeg:    return read_jpeg_info(buf);
      case TextureFileFormat::bmp:     return read_bmp_info(buf);
      case TextureFileFormat::pnm:     return read_pnm_info(buf);
      case TextureFileFormat::tga:     return read_tga_info(buf);

      default:
         return std::make_pair(TextureFileInfo(), TextureFileReadError::unsupported_file_format);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<TextureFileInfo, TextureFileReadError> read_info(TextureFileFormat type, Path path) {
   auto result = util::get_file_contents_buf(path);
   switch (result.second) {
      case util::FileReadError::none:              return read_info(type, std::move(result.first));
      case util::FileReadError::file_not_found:    return std::make_pair(TextureFileInfo(), TextureFileReadError::file_not_found);
      case util::FileReadError::file_not_readable: return std::make_pair(TextureFileInfo(), TextureFileReadError::file_not_readable);
      case util::FileReadError::out_of_memory:     return std::make_pair(TextureFileInfo(), TextureFileReadError::out_of_memory);
      default:                                     return std::make_pair(TextureFileInfo(), TextureFileReadError::unknown_filesystem_error);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_texture(const Buf<const UC>& buf) {
   return read_texture(read_format(buf), buf);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_texture(Path path) {
   auto result = util::get_file_contents_buf(path);
   switch (result.second) {
      case util::FileReadError::none:              return read_texture(std::move(result.first));
      case util::FileReadError::file_not_found:    return std::make_pair(Texture(), TextureFileReadError::file_not_found);
      case util::FileReadError::file_not_readable: return std::make_pair(Texture(), TextureFileReadError::file_not_readable);
      case util::FileReadError::out_of_memory:     return std::make_pair(Texture(), TextureFileReadError::out_of_memory);
      default:                                     return std::make_pair(Texture(), TextureFileReadError::unknown_filesystem_error);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_texture(TextureFileFormat type, const Buf<const UC>& buf) {
   switch (type) {
      case TextureFileFormat::betx:    return read_betx_texture(buf);
      case TextureFileFormat::ktx:     return read_ktx_texture(buf);
      case TextureFileFormat::png:     return read_png_texture(buf);
      case TextureFileFormat::glraw:   return read_glraw_texture(buf);
      case TextureFileFormat::dds:     return read_dds_texture(buf);
      case TextureFileFormat::hdr:     return read_hdr_texture(buf);
      case TextureFileFormat::gif:     return read_gif_texture(buf);
      case TextureFileFormat::pic:     return read_pic_texture(buf);
      case TextureFileFormat::psd:     return read_psd_texture(buf);
      case TextureFileFormat::jpeg:    return read_jpeg_texture(buf);
      case TextureFileFormat::bmp:     return read_bmp_texture(buf);
      case TextureFileFormat::pnm:     return read_pnm_texture(buf);
      case TextureFileFormat::tga:     return read_tga_texture(buf);

      default:
         return std::make_pair(Texture(), TextureFileReadError::unsupported_file_format);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Texture, TextureFileReadError> read_texture(TextureFileFormat type, Path path) {
   auto result = util::get_file_contents_buf(path);
   switch (result.second) {
      case util::FileReadError::none:              return read_texture(type, std::move(result.first));
      case util::FileReadError::file_not_found:    return std::make_pair(Texture(), TextureFileReadError::file_not_found);
      case util::FileReadError::file_not_readable: return std::make_pair(Texture(), TextureFileReadError::file_not_readable);
      case util::FileReadError::out_of_memory:     return std::make_pair(Texture(), TextureFileReadError::out_of_memory);
      default:                                     return std::make_pair(Texture(), TextureFileReadError::unknown_filesystem_error);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_image(const Buf<const UC>& buf) {
   return read_image(read_format(buf), buf);
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_image(Path path) {
   auto result = util::get_file_contents_buf(path);
   switch (result.second) {
      case util::FileReadError::none:              return read_image(std::move(result.first));
      case util::FileReadError::file_not_found:    return std::make_pair(Image(), TextureFileReadError::file_not_found);
      case util::FileReadError::file_not_readable: return std::make_pair(Image(), TextureFileReadError::file_not_readable);
      case util::FileReadError::out_of_memory:     return std::make_pair(Image(), TextureFileReadError::out_of_memory);
      default:                                     return std::make_pair(Image(), TextureFileReadError::unknown_filesystem_error);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_image(TextureFileFormat type, const Buf<const UC>& buf) {
   switch (type) {
      case TextureFileFormat::betx:    return read_betx_image(buf);
      case TextureFileFormat::ktx:     return read_ktx_image(buf);
      case TextureFileFormat::png:     return read_png_image(buf);
      case TextureFileFormat::glraw:   return read_glraw_image(buf);
      case TextureFileFormat::dds:     return read_dds_image(buf);
      case TextureFileFormat::hdr:     return read_hdr_image(buf);
      case TextureFileFormat::gif:     return read_gif_image(buf);
      case TextureFileFormat::pic:     return read_pic_image(buf);
      case TextureFileFormat::psd:     return read_psd_image(buf);
      case TextureFileFormat::jpeg:    return read_jpeg_image(buf);
      case TextureFileFormat::bmp:     return read_bmp_image(buf);
      case TextureFileFormat::pnm:     return read_pnm_image(buf);
      case TextureFileFormat::tga:     return read_tga_image(buf);

      default:
         return std::make_pair(Image(), TextureFileReadError::unsupported_file_format);
   }
}

///////////////////////////////////////////////////////////////////////////////
std::pair<Image, TextureFileReadError> read_image(TextureFileFormat type, Path path) {
   auto result = util::get_file_contents_buf(path);
   switch (result.second) {
      case util::FileReadError::none:              return read_image(type, std::move(result.first));
      case util::FileReadError::file_not_found:    return std::make_pair(Image(), TextureFileReadError::file_not_found);
      case util::FileReadError::file_not_readable: return std::make_pair(Image(), TextureFileReadError::file_not_readable);
      case util::FileReadError::out_of_memory:     return std::make_pair(Image(), TextureFileReadError::out_of_memory);
      default:                                     return std::make_pair(Image(), TextureFileReadError::unknown_filesystem_error);
   }
}

} // be::gfx::tex
