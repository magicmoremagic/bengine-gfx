//#pragma once
//#ifndef BE_GFX_WRITE_IMAGE_HPP_
//#define BE_GFX_WRITE_IMAGE_HPP_
//
//#include "gfx_autolink.hpp"
//#include "fwd_types.hpp"
//#include <be/core/buf.hpp>
//#include <be/util/files.hpp>
//
//namespace be {
//namespace gfx {
//
///*! ! 
//local texture_formats = { 'dds', 'kmg', 'ktx' }
//local image_formats = { 'png', 'bmp', 'tga', 'hdr' }
//
//write_template('write_x_image', { formats = texture_formats })
//write_template('write_x_image', { formats = image_formats, include_image_overloads = true }) !! 137 */
///* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
//
/////////////////////////////////////////////////////////////////////////////////
//Buf<UC> write_dds_texture(const gli::texture& tex);
//Buf<UC> write_kmg_texture(const gli::texture& tex);
//Buf<UC> write_ktx_texture(const gli::texture& tex);
//
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_dds_texture(const gli::texture& tex, const Path& path) {
//   Buf<const UC> buf = write_dds_texture(tex);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_kmg_texture(const gli::texture& tex, const Path& path) {
//   Buf<const UC> buf = write_kmg_texture(tex);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_ktx_texture(const gli::texture& tex, const Path& path) {
//   Buf<const UC> buf = write_ktx_texture(tex);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//Buf<UC> write_png_texture(const gli::texture& tex);
//Buf<UC> write_bmp_texture(const gli::texture& tex);
//Buf<UC> write_tga_texture(const gli::texture& tex);
//Buf<UC> write_hdr_texture(const gli::texture& tex);
//
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_png_texture(const gli::texture& tex, const Path& path) {
//   Buf<const UC> buf = write_png_texture(tex);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_bmp_texture(const gli::texture& tex, const Path& path) {
//   Buf<const UC> buf = write_bmp_texture(tex);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_tga_texture(const gli::texture& tex, const Path& path) {
//   Buf<const UC> buf = write_tga_texture(tex);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_hdr_texture(const gli::texture& tex, const Path& path) {
//   Buf<const UC> buf = write_hdr_texture(tex);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//Buf<UC> write_png_image(const gli::image& img);
//Buf<UC> write_bmp_image(const gli::image& img);
//Buf<UC> write_tga_image(const gli::image& img);
//Buf<UC> write_hdr_image(const gli::image& img);
//
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_png_image(const gli::image& img, const Path& path) {
//   Buf<const UC> buf = write_png_image(img);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_bmp_image(const gli::image& img, const Path& path) {
//   Buf<const UC> buf = write_bmp_image(img);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_tga_image(const gli::image& img, const Path& path) {
//   Buf<const UC> buf = write_tga_image(img);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//inline bool write_hdr_image(const gli::image& img, const Path& path) {
//   Buf<const UC> buf = write_hdr_image(img);
//   if (buf) {
//      util::put_file_contents(path, buf);
//      return true;
//   } else {
//      return false;
//   }
//}
//
///* ######################### END OF GENERATED CODE ######################### */
//
//} // be::gfx
//} // be
//
//#endif
