#include "pch.hpp"
//#include "read_image.hpp"
//#include "stbi_detail.h"
//#include "stbi_util_detail.hpp"
//#include <gli/convert.hpp>
//#include <gli/load_dds.hpp>
//#include <gli/load_kmg.hpp>
//#include <gli/load_ktx.hpp>
//#include <glm/vec2.hpp>
//
//namespace be {
//namespace gfx {
//namespace {
//
//void stbi_deleter(void* ptr, std::size_t size) {
//   stbi_image_free(ptr);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture make_texture_from_stbi(void* data, glm::ivec2 dim, int channels, int bpc) {
//   if (!data) return gli::texture();
//   Buf<const char> buf(static_cast<const char*>(data), dim.x * dim.y * channels, stbi_deleter);
//
//   gli::format format = detail::get_stbi_format(channels, bpc);
//   if (format == gli::FORMAT_UNDEFINED) return gli::texture();
//
//   gli::texture tex(gli::target::TARGET_2D, format, gli::texture::extent_type(dim, 1), 1, 1, 1);
//   assert(tex.size() == buf.size());
//   std::memcpy(tex.data(), data, tex.size());
//   return tex;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image make_image_from_stbi(void* data, glm::ivec2 dim, int channels, int bpc) {
//   if (!data) return gli::image();
//   Buf<const char> buf(static_cast<const char*>(data), dim.x * dim.y * channels, stbi_deleter);
//
//   gli::format format = detail::get_stbi_format(channels, bpc);
//   if (format == gli::FORMAT_UNDEFINED) return gli::image();
//
//   gli::image img(format, gli::extent3d(dim, 1));
//   assert(img.size() == buf.size());
//   std::memcpy(img.data(), data, img.size());
//   return img;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool write_stbi_to_image(void* data, glm::ivec2 dim, int channels, int bpc, gli::image& dest) {
//   if (!data) return false;
//   Buf<const char> buf(static_cast<const char*>(data), dim.x * dim.y * channels, stbi_deleter);
//
//   if (dest.empty()) return false;
//
//   gli::format format = detail::get_stbi_format(channels, bpc);
//   if (format == gli::FORMAT_UNDEFINED) return false;
//
//   if (dest.format() == format) {
//      if (dest.size() == buf.size()) {
//         std::memcpy(dest.data(), data, dest.size());
//         return true;
//      }
//   } else if (!gli::is_compressed(dest.format())) {
//      gli::texture2d tmp(format, dim, 1);
//      assert(tmp.size() == buf.size());
//      std::memcpy(tmp.data(), data, tmp.size());
//      gli::texture converted = gli::convert(tmp, dest.format());
//      if (converted.size() == dest.size()) {
//         std::memcpy(dest.data(), converted.data(), dest.size());
//         return true;
//      }
//   }
//   return false;
//}
//
//} // be::gfx::()
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_dds_texture(const Buf<const UC>& buf) {
//   return gli::load_dds(static_cast<const char*>(static_cast<const void*>(buf.get())), buf.size());
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_kmg_texture(const Buf<const UC>& buf) {
//   return gli::load_kmg(static_cast<const char*>(static_cast<const void*>(buf.get())), buf.size());
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_ktx_texture(const Buf<const UC>& buf) {
//   return gli::load_ktx(static_cast<const char*>(static_cast<const void*>(buf.get())), buf.size());
//}
//
///*! ! formats = { 'png', 'jpeg', 'hdr', 'pic', 'pnm', 'bmp', 'gif', 'psd', 'tga' }
//write_template('read_stbi_image_impl', formats) !! 229 */
///* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_png_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_png_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_png_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_png_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_png_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_png_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_jpeg_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_jpeg_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_jpeg_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_jpeg_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_jpeg_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_jpeg_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_hdr_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_hdr_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_hdr_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_hdr_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_hdr_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_hdr_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_pic_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_pic_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_pic_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_pic_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_pic_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_pic_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_pnm_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_pnm_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_pnm_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_pnm_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_pnm_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_pnm_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_bmp_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_bmp_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_bmp_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_bmp_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_bmp_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_bmp_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_gif_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_gif_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_gif_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_gif_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_gif_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_gif_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_psd_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_psd_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_psd_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_psd_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_psd_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_psd_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//gli::texture read_tga_texture(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_tga_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_texture_from_stbi(data, dim, channels, bpc);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//bool read_tga_image(const Buf<const UC>& buf, gli::image& dest) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_tga_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return write_stbi_to_image(data, dim, channels, bpc, dest);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//gli::image read_tga_image(const Buf<const UC>& buf) {
//   glm::ivec2 dim;
//   int channels, bpc;
//   void* data = be_stbi_load_tga_from_memory(buf.get(), (int)buf.size(), &dim.x, &dim.y, &channels, &bpc);
//   return make_image_from_stbi(data, dim, channels, bpc);
//}
//
//
///* ######################### END OF GENERATED CODE ######################### */
//
//} // be::gfx
//} // be
