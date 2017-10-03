#include "pch.hpp"
#include "tex/png_writer.hpp"
#include "stbiw_.h"
#include "tex/image.hpp"
#include "tex/duplicate_image.hpp"
#include "tex/texture_file_error.hpp"
#include <be/util/put_file_contents.hpp>
#include <be/core/exceptions.hpp>

namespace be::gfx::tex {

//////////////////////////////////////////////////////////////////////////////
PngWriter::PngWriter(Log& log)
   : log_(log),
     z_(0) { }

//////////////////////////////////////////////////////////////////////////////
void PngWriter::reset() {
   img_ = ConstImageView();
   z_ = 0;
}

//////////////////////////////////////////////////////////////////////////////
void PngWriter::image(const ConstImageView& view, I32 z) noexcept {
   img_ = view;
   z_ = z;
}

//////////////////////////////////////////////////////////////////////////////
Buf<UC> PngWriter::write() {
   Buf<UC> result;
   std::error_code ec;
   result = write(ec);
   if (ec) {
      throw RecoverableError(ec);
   }
   return result;
}

//////////////////////////////////////////////////////////////////////////////
Buf<UC> PngWriter::write(std::error_code& ec) noexcept {
   Buf<UC> result;

   if (!img_) {
      ec = make_error_code(TextureFileError::image_unavailable);
      return result;
   }

   if (z_ < 0 || z_ >= img_.dim().z) {
      ec = make_error_code(TextureFileError::image_unavailable);
      return result;
   }

   switch (img_.format().packing()) {
      case BlockPacking::s_8:
      case BlockPacking::s_8_8:
      case BlockPacking::s_8_8_8:
      case BlockPacking::s_8_8_8_8:
         break;
      default:
         ec = make_error_code(TextureFileError::unsupported);
         return result;
   }

   if (img_.format().block_dim() != ImageFormat::block_dim_type(1)) {
      ec = make_error_code(TextureFileError::unsupported);
      return result;
   }

   int components = block_word_count(img_.format().packing());

   if (img_.format().components() != components) {
      ec = make_error_code(TextureFileError::unsupported);
      return result;
   }

   if (img_.format().block_size() != components * block_word_size(img_.format().packing())) {
      ec = make_error_code(TextureFileError::unsupported);
      return result;
   }

   for (glm::length_t c = 0; c < components; ++c) {
      if (img_.format().swizzle(c) != static_cast<Swizzle>(c)) {
         ec = make_error_code(TextureFileError::unsupported);
         // Soft error; channels will be out of order, but still a valid image
      }
   }
   
   ConstImageView iv;
   Image tmp_img;
   if (img_.block_span() != img_.format().block_size()) {
      try {
         tmp_img = duplicate_image(img_, img_.format().block_size(), TextureAlignment(0));
      } catch (const std::bad_alloc&) {
         ec = make_error_code(std::errc::not_enough_memory);
         return result;
      }
      iv = tmp_img.view;
   } else {
      iv = img_;
   }

   std::size_t size = iv.plane_span();
   const UC* data = iv.data() + size * z_;

   try {
      result = make_buf<UC>(size + 100); // hopefully header/etc isn't more than 100 bytes, or we'll have to reallocate
   } catch (const std::bad_alloc&) {
      ec = make_error_code(std::errc::not_enough_memory);
      return Buf<UC>();
   }
   
   struct out_data {
      Buf<UC>& data;
      std::size_t written;
      bool out_of_memory;
   } out { result, 0, false };

   if (!stbi_write_png_to_func(
      [](void* ctx, void* data, int size) {
         out_data& out = *static_cast<out_data*>(data);
         if (out.out_of_memory) {
            return;
         }

         if (out.written + size > out.data.size()) {
            try {
               Buf<UC> new_data = make_buf<UC>((std::size_t)((out.written + size) * 1.25f));
               std::memcpy(new_data.get(), out.data.get(), out.written);
               out.data = std::move(new_data);
            } catch (const std::bad_alloc&) {
               out.out_of_memory = true;
               return;
            }
         }

         std::memcpy(out.data.get() + out.written, data, size);
         out.written += size;

      }, &out, iv.dim().x, iv.dim().y, components, data, img_.line_span())) {
      ec = make_error_code(TextureFileError::fatal_error);
      return Buf<UC>();
   }

   if (out.out_of_memory) {
      ec = make_error_code(std::errc::not_enough_memory);
      return Buf<UC>();
   }

   if (out.written < result.size()) {
      try {
         result = copy_buf(sub_buf(result, 0, out.written));
      } catch (const std::bad_alloc&) {
         ec = make_error_code(std::errc::not_enough_memory);
         return Buf<UC>();
      }
   }

   return result;
}

//////////////////////////////////////////////////////////////////////////////
void PngWriter::write(const Path& path) {
   // could save some memory allocations by duplicating the above except writing to file stream directly, but it shouldn't really matter much.
   util::put_file_contents(path, write());
}

//////////////////////////////////////////////////////////////////////////////
void PngWriter::write(const Path& path, std::error_code& ec) noexcept {
   // could save some memory allocations by duplicating the above except writing to file stream directly, but it shouldn't really matter much.
   Buf<UC> data = write(ec);
   if (data) {
      util::put_file_contents(path, std::move(data), ec);
   }
}

} // be::gfx::tex
