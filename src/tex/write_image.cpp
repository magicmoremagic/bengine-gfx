#include "pch.hpp"
#include "write_image.hpp"
#include "stbiw_detail.h"
#include "stbi_util_detail.hpp"
#include <gli/save_dds.hpp>
#include <gli/save_kmg.hpp>
#include <gli/save_ktx.hpp>
#include <gli/convert.hpp>

namespace be {
namespace gfx {
namespace {

///////////////////////////////////////////////////////////////////////////////
void write_to_vector(void* vptr, void *data, int size) {
   auto& vec = *static_cast<std::vector<UC>*>(vptr);
   std::size_t offset = vec.size();
   vec.resize(vec.size() + size);
   memcpy(vec.data() + offset, data, size);
}

///////////////////////////////////////////////////////////////////////////////
void write_to_buf(void* vptr, void *data, int size) {
   auto& buf = *static_cast<Buf<UC>*>(vptr);
   buf = concat_buf(buf, tmp_buf(static_cast<UC*>(data), (std::size_t)size));
}

} // be::gfx::()

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_dds_texture(const gli::texture& tex) {
   std::vector<char> vec;
   gli::save_dds(tex, vec);
   return copy_buf<UC>(tmp_buf(vec));
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_kmg_texture(const gli::texture& tex) {
   std::vector<char> vec;
   gli::save_kmg(tex, vec);
   return copy_buf<UC>(tmp_buf(vec));
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_ktx_texture(const gli::texture& tex) {
   std::vector<char> vec;
   gli::save_ktx(tex, vec);
   return copy_buf<UC>(tmp_buf(vec));
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_png_texture(const gli::texture& tex) {
   gli::format format = tex.format();
   if (tex.empty() || format == gli::FORMAT_UNDEFINED) {
      return Buf<UC>();
   }
   int channels = detail::get_stbi_format_8_channels(format);
   if (channels == 0) {
      format = detail::get_stbi_format_8((int)gli::component_count(format));
      if (format == gli::FORMAT_UNDEFINED) {
         return Buf<UC>();
      }
      return write_png_texture(gli::convert(gli::texture2d(tex), format));
   } else {
      Buf<UC> buf;
      // STBI png write only calls the write callback once, so write_to_buf is more efficient than write_to_vector + copy_buf
      stbi_write_png_to_func(write_to_buf, &buf, tex.extent().x, tex.extent().y, channels, tex.data(), 0);
      return buf;
   }
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_bmp_texture(const gli::texture& tex) {
   gli::format format = tex.format();
   if (tex.empty() || format == gli::FORMAT_UNDEFINED) {
      return Buf<UC>();
   }
   int channels = detail::get_stbi_format_8_channels(format);
   if (channels == 0) {
      format = detail::get_stbi_format_8((int)gli::component_count(format));
      if (format == gli::FORMAT_UNDEFINED) {
         return Buf<UC>();
      }
      return write_bmp_texture(gli::convert(gli::texture2d(tex), format));
   } else {
      std::vector<UC> vec;
      stbi_write_bmp_to_func(write_to_vector, &vec, tex.extent().x, tex.extent().y, channels, tex.data());
      return copy_buf(tmp_buf(vec));
   }
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_tga_texture(const gli::texture& tex) {
   gli::format format = tex.format();
   if (tex.empty() || format == gli::FORMAT_UNDEFINED) {
      return Buf<UC>();
   }
   int channels = detail::get_stbi_format_8_channels(format);
   if (channels == 0) {
      format = detail::get_stbi_format_8((int)gli::component_count(format));
      if (format == gli::FORMAT_UNDEFINED) {
         return Buf<UC>();
      }
      return write_tga_texture(gli::convert(gli::texture2d(tex), format));
   } else {
      std::vector<UC> vec;
      stbi_write_tga_to_func(write_to_vector, &vec, tex.extent().x, tex.extent().y, channels, tex.data());
      return copy_buf(tmp_buf(vec));
   }
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_hdr_texture(const gli::texture& tex) {
   gli::format format = tex.format();
   if (tex.empty() || format == gli::FORMAT_UNDEFINED) {
      return Buf<UC>();
   }
   int channels = detail::get_stbi_format_32_channels(format);
   if (channels == 0) {
      format = detail::get_stbi_format_32((int)gli::component_count(format));
      if (format == gli::FORMAT_UNDEFINED) {
         return Buf<UC>();
      }
      return write_hdr_texture(gli::convert(gli::texture2d(tex), format));
   } else {
      std::vector<UC> vec;
      stbi_write_hdr_to_func(write_to_vector, &vec, tex.extent().x, tex.extent().y, channels, tex.data<float>());
      return copy_buf(tmp_buf(vec));
   }
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_png_image(const gli::image& img) {
   gli::format format = img.format();
   if (img.empty() || format == gli::FORMAT_UNDEFINED) {
      return Buf<UC>();
   }
   int channels = detail::get_stbi_format_8_channels(format);
   if (channels == 0) {
      return Buf<UC>();
   } else {
      Buf<UC> buf;
      // STBI png write only calls the write callback once, so write_to_buf is more efficient than write_to_vector + copy_buf
      stbi_write_png_to_func(write_to_buf, &buf, img.extent().x, img.extent().y, channels, img.data(), 0);
      return buf;
   }
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_bmp_image(const gli::image& img) {
   gli::format format = img.format();
   if (img.empty() || format == gli::FORMAT_UNDEFINED) {
      return Buf<UC>();
   }
   int channels = detail::get_stbi_format_8_channels(format);
   if (channels == 0) {
      return Buf<UC>();
   } else {
      std::vector<UC> vec;
      stbi_write_bmp_to_func(write_to_vector, &vec, img.extent().x, img.extent().y, channels, img.data());
      return copy_buf(tmp_buf(vec));
   }
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_tga_image(const gli::image& img) {
   gli::format format = img.format();
   if (img.empty() || format == gli::FORMAT_UNDEFINED) {
      return Buf<UC>();
   }
   int channels = detail::get_stbi_format_8_channels(format);
   if (channels == 0) {
      return Buf<UC>();
   } else {
      std::vector<UC> vec;
      stbi_write_tga_to_func(write_to_vector, &vec, img.extent().x, img.extent().y, channels, img.data());
      return copy_buf(tmp_buf(vec));
   }
}

///////////////////////////////////////////////////////////////////////////////
Buf<UC> write_hdr_image(const gli::image& img) {
   gli::format format = img.format();
   if (img.empty() || format == gli::FORMAT_UNDEFINED) {
      return Buf<UC>();
   }
   int channels = detail::get_stbi_format_32_channels(format);
   if (channels == 0) {
      return Buf<UC>();
   } else {
      std::vector<UC> vec;
      stbi_write_hdr_to_func(write_to_vector, &vec, img.extent().x, img.extent().y, channels, img.data<float>());
      return copy_buf(tmp_buf(vec));
   }
}

} // be::gfx
} // be
