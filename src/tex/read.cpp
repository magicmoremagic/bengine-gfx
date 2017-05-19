#include "tex/pch.hpp"
#include "tex/read.hpp"
#include "tex/texture_file_format_betx.hpp"
#include "tex/texture_file_format_bmp.hpp"
#include "tex/texture_file_format_dds.hpp"
#include "tex/texture_file_format_gif.hpp"
#include "tex/texture_file_format_glraw.hpp"
#include "tex/texture_file_format_hdr.hpp"
#include "tex/texture_file_format_jpeg.hpp"
#include "tex/texture_file_format_ktx.hpp"
#include "tex/texture_file_format_pic.hpp"
#include "tex/texture_file_format_png.hpp"
#include "tex/texture_file_format_pnm.hpp"
#include "tex/texture_file_format_psd.hpp"
#include "tex/texture_file_format_tga.hpp"
#include <be/util/files.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat read_format(const Buf<const UC>& buf) {
   if (detail::is_betx(buf)) return TextureFileFormat::betx;
   else if (detail::is_ktx(buf)) return TextureFileFormat::ktx;
   else if (detail::is_png(buf)) return TextureFileFormat::png;
   else if (detail::is_glraw(buf)) return TextureFileFormat::glraw;
   else if (detail::is_dds(buf)) return TextureFileFormat::dds;
   else if (detail::is_hdr(buf)) return TextureFileFormat::hdr;
   else if (detail::is_gif(buf)) return TextureFileFormat::gif;
   else if (detail::is_pic(buf)) return TextureFileFormat::pic;
   else if (detail::is_psd(buf)) return TextureFileFormat::psd;
   else if (detail::is_jpeg(buf)) return TextureFileFormat::jpeg;
   else if (detail::is_bmp(buf)) return TextureFileFormat::bmp;
   else if (detail::is_pnm(buf)) return TextureFileFormat::pnm;
   else if (detail::is_tga(buf)) return TextureFileFormat::tga;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileFormat read_format(Path path) {
   return read_format(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo read_info(const Buf<const UC>& buf) {
   TextureFileInfo info;
   info.file_format = read_format(buf);
   // TODO
   return info;
}

///////////////////////////////////////////////////////////////////////////////
TextureFileInfo read_info(Path path) {
   return read_info(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
Texture read_texture(const Buf<const UC>& buf) {
   return read_texture(read_format(buf), buf);
}

///////////////////////////////////////////////////////////////////////////////
bool read_texture(const Buf<const UC>& buf, TextureView& dest) {
   return read_texture(read_format(buf), buf, dest);
}

///////////////////////////////////////////////////////////////////////////////
Texture read_texture(Path path) {
   return read_texture(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
bool read_texture(Path path, TextureView& dest) {
   return read_texture(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
Texture read_texture(TextureFileFormat type, const Buf<const UC>& buf) {
   // TODO
   return Texture();
}

///////////////////////////////////////////////////////////////////////////////
bool read_texture(TextureFileFormat type, const Buf<const UC>& buf, TextureView& dest) {
   // TODO
   return false;
}

///////////////////////////////////////////////////////////////////////////////
Texture read_texture(TextureFileFormat type, Path path) {
   return read_texture(type, util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
bool read_texture(TextureFileFormat type, Path path, TextureView& dest) {
   return read_texture(type, util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
Image read_image(const Buf<const UC>& buf) {
   return read_image(read_format(buf), buf);
}

///////////////////////////////////////////////////////////////////////////////
bool read_image(const Buf<const UC>& buf, ImageView& dest) {
   return read_image(read_format(buf), buf, dest);
}

///////////////////////////////////////////////////////////////////////////////
Image read_image(Path path) {
   return read_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
bool read_image(Path path, ImageView& dest) {
   return read_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
Image read_image(TextureFileFormat type, const Buf<const UC>& buf) {
   // TODO
   return Image();
}

///////////////////////////////////////////////////////////////////////////////
bool read_image(TextureFileFormat type, const Buf<const UC>& buf, ImageView& dest) {
   // TODO
   return false;
}

///////////////////////////////////////////////////////////////////////////////
Image read_image(TextureFileFormat type, Path path) {
   return read_image(type, util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
bool read_image(TextureFileFormat type, Path path, ImageView& dest) {
   return read_image(type, util::get_file_contents_buf(path), dest);
}

} // be::gfx::tex
