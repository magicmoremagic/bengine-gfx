#pragma once
#ifndef BE_GFX_IMAGE_READ_HPP_
#define BE_GFX_IMAGE_READ_HPP_

#include "gfx_autolink.hpp"
#include <be/core/buf.hpp>
#include <be/util/files.hpp>
#include <gli/texture.hpp>
#include <gli/image.hpp>

namespace be {
namespace gfx {

/*!! 
local texture_formats = { 'dds', 'kmg', 'ktx' }

local image_formats = { 'png', 'jpeg',
   'hdr', 'pic', 'pnm', 'bmp', 'gif', 'psd',
   'tga' -- Keep me last; no easily verifiable file signature
}

local all_formats = table.pack(table.unpack(texture_formats))
table.move(image_formats, 1, #image_formats, #all_formats + 1, all_formats)
write_template('read_x_image', { formats = texture_formats })
write_template('read_x_image', { formats = image_formats, include_image_overloads = true })
write_template('read_image', { formats = all_formats })
write_template('read_image', { formats = image_formats, prefix = 'simple_', include_image_overloads = true }) !! 412 */
/* ######## !! GENERATED CODE -- DO NOT MODIFY !! ######## */

///////////////////////////////////////////////////////////////////////////////
gli::texture read_dds_texture(const Buf<const UC>& buf);
gli::texture read_kmg_texture(const Buf<const UC>& buf);
gli::texture read_ktx_texture(const Buf<const UC>& buf);

///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_dds_texture(const Path& path) {
   return read_dds_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_kmg_texture(const Path& path) {
   return read_kmg_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_ktx_texture(const Path& path) {
   return read_ktx_texture(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
gli::texture read_png_texture(const Buf<const UC>& buf);
gli::texture read_jpeg_texture(const Buf<const UC>& buf);
gli::texture read_hdr_texture(const Buf<const UC>& buf);
gli::texture read_pic_texture(const Buf<const UC>& buf);
gli::texture read_pnm_texture(const Buf<const UC>& buf);
gli::texture read_bmp_texture(const Buf<const UC>& buf);
gli::texture read_gif_texture(const Buf<const UC>& buf);
gli::texture read_psd_texture(const Buf<const UC>& buf);
gli::texture read_tga_texture(const Buf<const UC>& buf);

///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_png_texture(const Path& path) {
   return read_png_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_jpeg_texture(const Path& path) {
   return read_jpeg_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_hdr_texture(const Path& path) {
   return read_hdr_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_pic_texture(const Path& path) {
   return read_pic_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_pnm_texture(const Path& path) {
   return read_pnm_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_bmp_texture(const Path& path) {
   return read_bmp_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_gif_texture(const Path& path) {
   return read_gif_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_psd_texture(const Path& path) {
   return read_psd_texture(util::get_file_contents_buf(path));
}
///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_tga_texture(const Path& path) {
   return read_tga_texture(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
bool read_png_image(const Buf<const UC>& buf, gli::image& dest);
bool read_jpeg_image(const Buf<const UC>& buf, gli::image& dest);
bool read_hdr_image(const Buf<const UC>& buf, gli::image& dest);
bool read_pic_image(const Buf<const UC>& buf, gli::image& dest);
bool read_pnm_image(const Buf<const UC>& buf, gli::image& dest);
bool read_bmp_image(const Buf<const UC>& buf, gli::image& dest);
bool read_gif_image(const Buf<const UC>& buf, gli::image& dest);
bool read_psd_image(const Buf<const UC>& buf, gli::image& dest);
bool read_tga_image(const Buf<const UC>& buf, gli::image& dest);

///////////////////////////////////////////////////////////////////////////////
inline bool read_png_image(const Path& path, gli::image& dest) {
   return read_png_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_jpeg_image(const Path& path, gli::image& dest) {
   return read_jpeg_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_hdr_image(const Path& path, gli::image& dest) {
   return read_hdr_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_pic_image(const Path& path, gli::image& dest) {
   return read_pic_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_pnm_image(const Path& path, gli::image& dest) {
   return read_pnm_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_bmp_image(const Path& path, gli::image& dest) {
   return read_bmp_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_gif_image(const Path& path, gli::image& dest) {
   return read_gif_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_psd_image(const Path& path, gli::image& dest) {
   return read_psd_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_tga_image(const Path& path, gli::image& dest) {
   return read_tga_image(util::get_file_contents_buf(path), dest);
}

///////////////////////////////////////////////////////////////////////////////
gli::image read_png_image(const Buf<const UC>& buf);
gli::image read_jpeg_image(const Buf<const UC>& buf);
gli::image read_hdr_image(const Buf<const UC>& buf);
gli::image read_pic_image(const Buf<const UC>& buf);
gli::image read_pnm_image(const Buf<const UC>& buf);
gli::image read_bmp_image(const Buf<const UC>& buf);
gli::image read_gif_image(const Buf<const UC>& buf);
gli::image read_psd_image(const Buf<const UC>& buf);
gli::image read_tga_image(const Buf<const UC>& buf);

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_png_image(const Path& path) {
   return read_png_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_jpeg_image(const Path& path) {
   return read_jpeg_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_hdr_image(const Path& path) {
   return read_hdr_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_pic_image(const Path& path) {
   return read_pic_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_pnm_image(const Path& path) {
   return read_pnm_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_bmp_image(const Path& path) {
   return read_bmp_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_gif_image(const Path& path) {
   return read_gif_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_psd_image(const Path& path) {
   return read_psd_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_tga_image(const Path& path) {
   return read_tga_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_texture(const Buf<const UC>& buf) {
   {
      gli::texture tex = read_dds_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_kmg_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_ktx_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_png_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_jpeg_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_hdr_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_pic_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_pnm_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_bmp_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_gif_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_psd_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_tga_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   return gli::texture();
}

///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_texture(const Path& path) {
   return read_texture(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_simple_texture(const Buf<const UC>& buf) {
   {
      gli::texture tex = read_png_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_jpeg_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_hdr_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_pic_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_pnm_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_bmp_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_gif_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_psd_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   {
      gli::texture tex = read_tga_texture(buf);
      if (!tex.empty()) {
         return tex;
      }
   }
   return gli::texture();
}

///////////////////////////////////////////////////////////////////////////////
inline gli::texture read_simple_texture(const Path& path) {
   return read_simple_texture(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_simple_image(const Buf<const UC>& buf) {
   {
      gli::image img = read_png_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   {
      gli::image img = read_jpeg_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   {
      gli::image img = read_hdr_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   {
      gli::image img = read_pic_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   {
      gli::image img = read_pnm_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   {
      gli::image img = read_bmp_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   {
      gli::image img = read_gif_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   {
      gli::image img = read_psd_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   {
      gli::image img = read_tga_image(buf);
      if (!img.empty()) {
         return img;
      }
   }
   return gli::image();
}

///////////////////////////////////////////////////////////////////////////////
inline gli::image read_simple_image(const Path& path) {
   return read_simple_image(util::get_file_contents_buf(path));
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_simple_image(const Buf<const UC>& buf, gli::image& dest) {
   return 
      read_png_image(buf, dest) ||
      read_jpeg_image(buf, dest) ||
      read_hdr_image(buf, dest) ||
      read_pic_image(buf, dest) ||
      read_pnm_image(buf, dest) ||
      read_bmp_image(buf, dest) ||
      read_gif_image(buf, dest) ||
      read_psd_image(buf, dest) ||
      read_tga_image(buf, dest) ||
      false;
}

///////////////////////////////////////////////////////////////////////////////
inline bool read_simple_image(const Path& path, gli::image& dest) {
   return read_simple_image(util::get_file_contents_buf(path), dest);
}

/* ################ END OF GENERATED CODE ################ */

} // be::gfx
} // be

#endif
