#include "pch.hpp"
#include "tex/image_format_gl.hpp"
#include <be/core/enum_vec3.hpp>
#include <be/core/enum_vec4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace be::gfx::tex {
namespace {

//////////////////////////////////////////////////////////////////////////////
void swap_rg_swizzles(gl::GLenum* swizzles) {
   using namespace gl;
   for (std::size_t i = 0; i < 4; ++i) {
      switch (swizzles[i]) {
         case GL_RED: swizzles[i] = GL_GREEN;
         case GL_GREEN: swizzles[i] = GL_RED;
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
void swap_rb_swizzles(gl::GLenum* swizzles) {
   using namespace gl;
   for (std::size_t i = 0; i < 4; ++i) {
      switch (swizzles[i]) {
         case GL_RED: swizzles[i] = GL_BLUE;
         case GL_BLUE: swizzles[i] = GL_RED;
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
void swap_ra_swizzles(gl::GLenum* swizzles) {
   using namespace gl;
   for (std::size_t i = 0; i < 4; ++i) {
      switch (swizzles[i]) {
         case GL_RED: swizzles[i] = GL_ALPHA;
         case GL_ALPHA: swizzles[i] = GL_RED;
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
void swap_gb_swizzles(gl::GLenum* swizzles) {
   using namespace gl;
   for (std::size_t i = 0; i < 4; ++i) {
      switch (swizzles[i]) {
         case GL_GREEN: swizzles[i] = GL_BLUE;
         case GL_BLUE: swizzles[i] = GL_GREEN;
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
void reverse_rgba_swizzles(gl::GLenum* swizzles) {
   using namespace gl;
   for (std::size_t i = 0; i < 4; ++i) {
      switch (swizzles[i]) {
         case GL_RED: swizzles[i] = GL_ALPHA;
         case GL_GREEN: swizzles[i] = GL_BLUE;
         case GL_BLUE: swizzles[i] = GL_GREEN;
         case GL_ALPHA: swizzles[i] = GL_RED;
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
ImageFormatGl to_gl_format_compressed(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
   f.base_internal_format = GL_INVALID_VALUE;
   f.internal_format = GL_INVALID_VALUE;
   f.data_format = GL_NONE;
   f.data_type = GL_NONE;
   f.swizzle[0] = swizzle_to_gl(format.swizzle(0));
   f.swizzle[1] = swizzle_to_gl(format.swizzle(1));
   f.swizzle[2] = swizzle_to_gl(format.swizzle(2));
   f.swizzle[3] = swizzle_to_gl(format.swizzle(3));

   switch (format.packing()) {
      case BlockPacking::c_s3tc1:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 8) {
            if (format.components() == 3 && format.field_types() == field_types(FieldType::unorm, 3)) {
               f.base_internal_format = GL_RGB;
               if (format.colorspace() == Colorspace::srgb) {
                  //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
                  f.internal_format = GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
               } else {
                  //#bgl checked (GL_EXT_texture_compression_s3tc)
                  f.internal_format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
               }
            } else if (format.components() == 4 && format.field_types() == field_types(FieldType::unorm, 4)) {
               f.base_internal_format = GL_RGBA;
               if (format.colorspace() == Colorspace::srgb) {
                  //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
                  f.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
               } else {
                  //#bgl checked (GL_EXT_texture_compression_s3tc)
                  f.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
               }
            }
         }
         break;

      case BlockPacking::c_s3tc2:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 16 &&
             format.components() == 4 && format.field_types() == field_types(FieldType::unorm, 4)) {
            f.base_internal_format = GL_RGBA;
            if (format.colorspace() == Colorspace::srgb) {
               //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
               f.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
            } else {
               //#bgl checked (GL_EXT_texture_compression_s3tc)
               f.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            }
         }
         break;

      case BlockPacking::c_s3tc3:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 16 &&
             format.components() == 4 && format.field_types() == field_types(FieldType::unorm, 4)) {
            f.base_internal_format = GL_RGBA;
            if (format.colorspace() == Colorspace::srgb) {
               //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
               f.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
            } else {
               //#bgl checked (GL_EXT_texture_compression_s3tc)
               f.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
               //#bgl unchecked
            }
         }
         break;
      

      case BlockPacking::c_rgtc1:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 8 && format.components() == 1) {
            f.base_internal_format = GL_RED;
            if (format.field_types() == field_types(FieldType::unorm, 1)) {
               f.internal_format = GL_COMPRESSED_RED_RGTC1;
            } else if (format.field_types() == field_types(FieldType::snorm, 1)) {
               f.internal_format = GL_COMPRESSED_SIGNED_RED_RGTC1;
            }
         }
         break;

      case BlockPacking::c_rgtc2:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 16 && format.components() == 2) {
            f.base_internal_format = GL_RG;
            if (format.field_types() == field_types(FieldType::unorm, 2)) {
               f.internal_format = GL_COMPRESSED_RG_RGTC2;
            } else if (format.field_types() == field_types(FieldType::snorm, 2)) {
               f.internal_format = GL_COMPRESSED_SIGNED_RG_RGTC2;
            }
         }
         break;

      //#bgl checked (4.2)
      case BlockPacking::c_bptc:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 16) {
            if (format.components() == 4 && format.field_types() == field_types(FieldType::unorm, 4)) {
               f.base_internal_format = GL_RGBA;
               if (format.colorspace() == Colorspace::srgb) {
                  f.internal_format = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM;
               } else {
                  f.internal_format = GL_COMPRESSED_RGBA_BPTC_UNORM;
               }
            } else if (format.components() == 3) {
               f.base_internal_format = GL_RGB;
               if (format.field_types() == field_types(FieldType::sfloat, 3)) {
                  f.internal_format = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT;
               } else if (format.field_types() == field_types(FieldType::ufloat, 3)) {
                  f.internal_format = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;
               }
            }
         }
         break;
      //#bgl unchecked
   }
   return f;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormatGl to_gl_format_depth(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
   f.base_internal_format = GL_DEPTH_COMPONENT;
   f.internal_format = GL_INVALID_VALUE;
   f.data_format = GL_INVALID_VALUE;
   f.data_type = GL_INVALID_VALUE;
   f.swizzle[0] = swizzle_to_gl(format.swizzle(0));
   f.swizzle[1] = swizzle_to_gl(format.swizzle(1));
   f.swizzle[2] = swizzle_to_gl(format.swizzle(2));
   f.swizzle[3] = swizzle_to_gl(format.swizzle(3));

   if (format.block_dim() == ImageFormat::block_dim_type(1) && format.components() == 1) {
      switch (format.packing()) {
         case BlockPacking::s_16:
            if (format.field_types() == field_types(FieldType::unorm, 1)) {
               f.internal_format = GL_DEPTH_COMPONENT16;
               f.data_format = GL_DEPTH_COMPONENT;
               f.data_type = GL_UNSIGNED_SHORT;
            }
            break;

         case BlockPacking::s_32:
            if (format.field_types() == field_types(FieldType::unorm, 1)) {
               f.internal_format = GL_DEPTH_COMPONENT32;
               f.data_format = GL_DEPTH_COMPONENT;
               f.data_type = GL_UNSIGNED_INT;
            } else if (format.field_types() == field_types(FieldType::sfloat, 1)) {
               f.internal_format = GL_DEPTH_COMPONENT32F;
               f.data_format = GL_DEPTH_COMPONENT;
               f.data_type = GL_FLOAT;
            }
            break;

         case BlockPacking::p_8_24:
            if (format.field_types() == field_types(FieldType::none, FieldType::unorm)) {
               f.internal_format = GL_DEPTH_COMPONENT24;
               f.data_format = GL_DEPTH_COMPONENT;
               f.data_type = GL_UNSIGNED_INT;
               swap_rg_swizzles(f.swizzle);
            }
            break;
      }
   }

   return f;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormatGl to_gl_format_stencil(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
   f.base_internal_format = GL_STENCIL_INDEX;
   f.internal_format = GL_INVALID_VALUE;
   f.data_format = GL_INVALID_VALUE;
   f.data_type = GL_INVALID_VALUE;
   f.swizzle[0] = swizzle_to_gl(format.swizzle(0));
   f.swizzle[1] = swizzle_to_gl(format.swizzle(1));
   f.swizzle[2] = swizzle_to_gl(format.swizzle(2));
   f.swizzle[3] = swizzle_to_gl(format.swizzle(3));

   if (format.block_dim() == ImageFormat::block_dim_type(1) && format.components() == 1 &&
       format.packing() == BlockPacking::s_8 && format.field_types() == field_types(FieldType::uint, 1)) {
      f.internal_format = GL_STENCIL_INDEX8;
      f.data_format = GL_STENCIL_INDEX;
      f.data_type = GL_UNSIGNED_BYTE;
   }

   return f;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormatGl to_gl_format_depth_stencil(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
   f.base_internal_format = GL_DEPTH_STENCIL;
   f.internal_format = GL_INVALID_VALUE;
   f.data_format = GL_INVALID_VALUE;
   f.data_type = GL_INVALID_VALUE;
   f.swizzle[0] = swizzle_to_gl(format.swizzle(0));
   f.swizzle[1] = swizzle_to_gl(format.swizzle(1));
   f.swizzle[2] = swizzle_to_gl(format.swizzle(2));
   f.swizzle[3] = swizzle_to_gl(format.swizzle(3));

   if (format.block_dim() == ImageFormat::block_dim_type(1) && format.components() == 2) {
      if (format.packing() == BlockPacking::p_24_8 && format.field_types() == field_types(FieldType::unorm, FieldType::uint)) {
         f.data_format = GL_DEPTH_STENCIL;
         f.internal_format = GL_DEPTH24_STENCIL8;
         f.data_type = GL_UNSIGNED_INT_24_8;
      } else if (format.packing() == BlockPacking::s_32_p_24_8 && format.field_types() == field_types(FieldType::sfloat, FieldType::none, FieldType::uint)) {
         f.data_format = GL_DEPTH_STENCIL;
         f.internal_format = GL_DEPTH32F_STENCIL8;
         f.data_type = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
         swap_gb_swizzles(f.swizzle);
      }
   }

   return f;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormatGl to_gl_format_uncompressed(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
   f.base_internal_format = GL_INVALID_VALUE;
   f.internal_format = GL_INVALID_VALUE;
   f.data_format = GL_INVALID_VALUE;
   f.data_type = GL_INVALID_VALUE;
   f.swizzle[0] = swizzle_to_gl(format.swizzle(0));
   f.swizzle[1] = swizzle_to_gl(format.swizzle(1));
   f.swizzle[2] = swizzle_to_gl(format.swizzle(2));
   f.swizzle[3] = swizzle_to_gl(format.swizzle(3));

   if (format.block_dim() != ImageFormat::block_dim_type(1)) {
      return f;
   }

   FieldType first_type = format.field_type(0);
   switch (format.components()) {
      case 1:
         f.base_internal_format = GL_RED;
         if (format.field_types() == field_types(first_type, 1)) {
            switch (first_type) {
               case FieldType::unorm:
                  switch (format.packing()) {
                     case BlockPacking::s_8:
                        f.internal_format = GL_R8;
                        f.data_type = GL_UNSIGNED_BYTE;
                        break;

                     case BlockPacking::s_16:
                        f.internal_format = GL_R16;
                        f.data_type = GL_UNSIGNED_SHORT;
                        break;
                  }
                  f.data_format = GL_RED;
                  break;

               case FieldType::snorm:
                  switch (format.packing()) {
                     case BlockPacking::s_8:
                        f.internal_format = GL_R8_SNORM;
                        f.data_type = GL_BYTE;
                        break;

                     case BlockPacking::s_16:
                        f.internal_format = GL_R16_SNORM;
                        f.data_type = GL_SHORT;
                        break;
                  }
                  f.data_format = GL_RED;
                  break;

               case FieldType::uint:
                  switch (format.packing()) {
                     case BlockPacking::s_8:
                        f.internal_format = GL_R8UI;
                        f.data_type = GL_UNSIGNED_BYTE;
                        break;

                     case BlockPacking::s_16:
                        f.internal_format = GL_R16UI;
                        f.data_type = GL_UNSIGNED_SHORT;
                        break;

                     case BlockPacking::s_32:
                        f.internal_format = GL_R32UI;
                        f.data_type = GL_UNSIGNED_INT;
                        break;
                  }
                  f.data_format = GL_RED_INTEGER;
                  break;

               case FieldType::sint:
                  switch (format.packing()) {
                     case BlockPacking::s_8:
                        f.internal_format = GL_R8I;
                        f.data_type = GL_BYTE;
                        break;

                     case BlockPacking::s_16:
                        f.internal_format = GL_R16I;
                        f.data_type = GL_SHORT;
                        break;

                     case BlockPacking::s_32:
                        f.internal_format = GL_R32I;
                        f.data_type = GL_INT;
                        break;
                  }
                  f.data_format = GL_RED_INTEGER;
                  break;

               case FieldType::sfloat:
                  switch (format.packing()) {
                     case BlockPacking::s_16:
                        f.internal_format = GL_R16F;
                        f.data_type = GL_HALF_FLOAT;
                        break;

                     case BlockPacking::s_32:
                        f.internal_format = GL_R32F;
                        f.data_type = GL_FLOAT;
                        break;
                  }
                  f.data_format = GL_RED;
                  break;
            }
         }
         break;

      case 2:
         f.base_internal_format = GL_RG;
         if (format.field_types() == field_types(first_type, 2)) {
            switch (first_type) {
               case FieldType::unorm:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8:
                        f.internal_format = GL_RG8;
                        f.data_type = GL_UNSIGNED_BYTE;
                        break;

                     case BlockPacking::s_16_16:
                        f.internal_format = GL_RG16;
                        f.data_type = GL_UNSIGNED_SHORT;
                        break;
                  }
                  f.data_format = GL_RG;
                  break;

               case FieldType::snorm:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8:
                        f.internal_format = GL_RG8_SNORM;
                        f.data_type = GL_BYTE;
                        break;

                     case BlockPacking::s_16_16:
                        f.internal_format = GL_RG16_SNORM;
                        f.data_type = GL_SHORT;
                        break;
                  }
                  f.data_format = GL_RG;
                  break;

               case FieldType::uint:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8:
                        f.internal_format = GL_RG8UI;
                        f.data_type = GL_UNSIGNED_BYTE;
                        break;

                     case BlockPacking::s_16_16:
                        f.internal_format = GL_RG16UI;
                        f.data_type = GL_UNSIGNED_SHORT;
                        break;

                     case BlockPacking::s_32_32:
                        f.internal_format = GL_RG32UI;
                        f.data_type = GL_UNSIGNED_INT;
                        break;
                  }
                  f.data_format = GL_RG_INTEGER;
                  break;

               case FieldType::sint:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8:
                        f.internal_format = GL_RG8I;
                        f.data_type = GL_BYTE;
                        break;

                     case BlockPacking::s_16_16:
                        f.internal_format = GL_RG16I;
                        f.data_type = GL_SHORT;
                        break;

                     case BlockPacking::s_32_32:
                        f.internal_format = GL_RG32I;
                        f.data_type = GL_INT;
                        break;
                  }
                  f.data_format = GL_RG_INTEGER;
                  break;

               case FieldType::sfloat:
                  switch (format.packing()) {
                     case BlockPacking::s_16_16:
                        f.internal_format = GL_RG16F;
                        f.data_type = GL_HALF_FLOAT;
                        break;

                     case BlockPacking::s_32_32:
                        f.internal_format = GL_RG32F;
                        f.data_type = GL_FLOAT;
                        break;
                  }
                  f.data_format = GL_RG;
                  break;
            }
         }
         break;

      case 3:
         f.base_internal_format = GL_RGB;
         if (format.field_types() == field_types(first_type, 3)) {
            switch (first_type) {
               case FieldType::unorm:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8_8:
                        if (format.colorspace() == Colorspace::srgb) {
                           f.internal_format = GL_SRGB8;
                        } else {
                           f.internal_format = GL_RGB8;
                        }
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGR;
                        } else {
                           f.data_format = GL_RGB;
                        }
                        f.data_type = GL_UNSIGNED_BYTE;
                        break;

                     case BlockPacking::s_16_16_16:
                        f.internal_format = GL_RGB16;
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGR;
                        } else {
                           f.data_format = GL_RGB;
                        }
                        f.data_type = GL_UNSIGNED_SHORT;
                        break;

                     case BlockPacking::p_3_3_2:
                        f.internal_format = GL_R3_G3_B2;
                        f.data_format = GL_RGB;
                        f.data_type = GL_UNSIGNED_BYTE_3_3_2;
                        break;

                     case BlockPacking::p_2_3_3:
                        f.internal_format = GL_R3_G3_B2;
                        f.data_format = GL_RGB;
                        f.data_type = GL_UNSIGNED_BYTE_2_3_3_REV;
                        swap_rb_swizzles(f.swizzle);
                        break;

                     //#bgl checked (4.1)
                     case BlockPacking::p_5_6_5:
                        f.internal_format = GL_RGB565;
                        f.data_format = GL_RGB;
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_type = GL_UNSIGNED_SHORT_5_6_5_REV;
                        } else {
                           f.data_type = GL_UNSIGNED_SHORT_5_6_5;
                        }
                        break;
                     //#bgl unchecked

                     case BlockPacking::p_4_4_4_4:
                        f.internal_format = GL_RGB4;
                        f.data_type = GL_UNSIGNED_SHORT_4_4_4_4;
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }
                        break;

                     case BlockPacking::p_5_5_5_1:
                        f.internal_format = GL_RGB5;
                        f.data_type = GL_UNSIGNED_SHORT_5_5_5_1;
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }
                        break;
                  }
                  break;

               case FieldType::snorm:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8_8:
                        f.internal_format = GL_RGB8_SNORM;
                        f.data_type = GL_BYTE;
                        break;

                     case BlockPacking::s_16_16_16:
                        f.internal_format = GL_RGB16_SNORM;
                        f.data_type = GL_SHORT;
                        break;
                  }
                  if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                     swap_rb_swizzles(f.swizzle);
                     f.data_format = GL_BGR;
                  } else {
                     f.data_format = GL_RGB;
                  }
                  break;

               case FieldType::uint:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8_8:
                        f.internal_format = GL_RGB8UI;
                        f.data_type = GL_UNSIGNED_BYTE;
                        break;

                     case BlockPacking::s_16_16_16:
                        f.internal_format = GL_RGB16UI;
                        f.data_type = GL_UNSIGNED_SHORT;
                        break;

                     case BlockPacking::s_32_32_32:
                        f.internal_format = GL_RGB32UI;
                        f.data_type = GL_UNSIGNED_INT;
                        break;
                  }
                  if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                     swap_rb_swizzles(f.swizzle);
                     f.data_format = GL_BGR_INTEGER;
                  } else {
                     f.data_format = GL_RGB_INTEGER;
                  }
                  break;

               case FieldType::sint:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8_8:
                        f.internal_format = GL_RGB8I;
                        f.data_type = GL_BYTE;
                        break;

                     case BlockPacking::s_16_16_16:
                        f.internal_format = GL_RGB16I;
                        f.data_type = GL_SHORT;
                        break;

                     case BlockPacking::s_32_32_32:
                        f.internal_format = GL_RGB32I;
                        f.data_type = GL_INT;
                        break;
                  }
                  if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                     swap_rb_swizzles(f.swizzle);
                     f.data_format = GL_BGR_INTEGER;
                  } else {
                     f.data_format = GL_RGB_INTEGER;
                  }
                  break;

               case FieldType::ufloat:
                  switch (format.packing()) {
                     case BlockPacking::p_10_11_11:
                        f.internal_format = GL_R11F_G11F_B10F;
                        f.data_type = GL_UNSIGNED_INT_10F_11F_11F_REV;
                        swap_rb_swizzles(f.swizzle);
                        break;
                  }
                  f.data_format = GL_RGB;
                  break;

               case FieldType::sfloat:
                  switch (format.packing()) {
                     case BlockPacking::s_16_16_16:
                        f.internal_format = GL_RGB16F;
                        f.data_type = GL_HALF_FLOAT;
                        break;

                     case BlockPacking::s_32_32_32:
                        f.internal_format = GL_RGB32F;
                        f.data_type = GL_FLOAT;
                        break;
                  }
                  if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                     swap_rb_swizzles(f.swizzle);
                     f.data_format = GL_BGR;
                  } else {
                     f.data_format = GL_RGB;
                  }
                  break;
            }
         } else if (format.packing() == BlockPacking::p_1_5_5_5 && format.field_types() == field_types(FieldType::none, FieldType::unorm, FieldType::unorm, FieldType::unorm)) {
            f.internal_format = GL_RGB5;
            f.data_type = GL_UNSIGNED_SHORT_1_5_5_5_REV;
            reverse_rgba_swizzles(f.swizzle);
            if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
               swap_rb_swizzles(f.swizzle);
               f.data_format = GL_BGRA;
            } else {
               f.data_format = GL_RGBA;
            }
         } else if (format.packing() == BlockPacking::p_4_4_4_4 && format.field_types() == field_types(FieldType::none, FieldType::unorm, FieldType::unorm, FieldType::unorm)) {
            f.internal_format = GL_RGB4;
            f.data_type = GL_UNSIGNED_SHORT_4_4_4_4_REV;
            reverse_rgba_swizzles(f.swizzle);
            if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
               swap_rb_swizzles(f.swizzle);
               f.data_format = GL_BGRA;
            } else {
               f.data_format = GL_RGBA;
            }
         } else if (format.packing() == BlockPacking::p_5_9_9_9 && format.field_types() == field_types(FieldType::expo, FieldType::ufloat, FieldType::ufloat, FieldType::ufloat)) {
            f.data_format = GL_RGB;
            f.internal_format = GL_RGB9_E5;
            f.data_type = GL_UNSIGNED_INT_5_9_9_9_REV;
            reverse_rgba_swizzles(f.swizzle);
         }
         break;

      case 4:
         f.base_internal_format = GL_RGBA;
         if (format.field_types() == field_types(first_type, 4)) {
            switch (first_type) {
               case FieldType::unorm:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8_8_8:
                        if (format.colorspace() == Colorspace::srgb) {
                           f.internal_format = GL_SRGB8_ALPHA8;
                        } else {
                           f.internal_format = GL_RGBA8;
                        }
                        f.data_type = GL_UNSIGNED_BYTE;
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }
                        break;

                     case BlockPacking::s_16_16_16_16:
                        f.internal_format = GL_RGBA16;
                        f.data_type = GL_UNSIGNED_SHORT;
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }

                        break;

                     case BlockPacking::p_4_4_4_4:
                        f.internal_format = GL_RGBA4;
                        if (f.swizzle[0] == GL_ALPHA) {
                           reverse_rgba_swizzles(f.swizzle);
                           f.data_type = GL_UNSIGNED_SHORT_4_4_4_4_REV;
                        } else {
                           f.data_type = GL_UNSIGNED_SHORT_4_4_4_4;
                        }
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }
                        break;

                     case BlockPacking::p_5_5_5_1:
                        f.internal_format = GL_RGB5_A1;
                        f.data_type = GL_UNSIGNED_SHORT_5_5_5_1;
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }

                        break;

                     case BlockPacking::p_1_5_5_5:
                        f.internal_format = GL_RGB5_A1;
                        f.data_type = GL_UNSIGNED_SHORT_1_5_5_5_REV;
                        reverse_rgba_swizzles(f.swizzle);
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }
                        break;

                     case BlockPacking::p_10_10_10_2:
                        f.internal_format = GL_RGB10_A2;
                        f.data_type = GL_UNSIGNED_INT_10_10_10_2;
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }
                        break;

                     case BlockPacking::p_2_10_10_10:
                        f.internal_format = GL_RGB10_A2;
                        f.data_type = GL_UNSIGNED_INT_2_10_10_10_REV;
                        reverse_rgba_swizzles(f.swizzle);
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }
                        break;

                     case BlockPacking::p_8_8_8_8:
                        f.internal_format = GL_RGBA8;
                        if (f.swizzle[0] == GL_ALPHA) {
                           reverse_rgba_swizzles(f.swizzle);
                           f.data_type = GL_UNSIGNED_INT_8_8_8_8_REV;
                        } else {
                           f.data_type = GL_UNSIGNED_INT_8_8_8_8;
                        }
                        if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                           swap_rb_swizzles(f.swizzle);
                           f.data_format = GL_BGRA;
                        } else {
                           f.data_format = GL_RGBA;
                        }
                        break;
                  }

                  break;

               case FieldType::snorm:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8_8_8:
                        f.internal_format = GL_RGBA8_SNORM;
                        f.data_type = GL_BYTE;
                        break;

                     case BlockPacking::s_16_16_16_16:
                        f.internal_format = GL_RGBA16_SNORM;
                        f.data_type = GL_SHORT;
                        break;
                  }
                  if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                     swap_rb_swizzles(f.swizzle);
                     f.data_format = GL_BGRA;
                  } else {
                     f.data_format = GL_RGBA;
                  }
                  break;

               case FieldType::uint:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8_8_8:
                        f.internal_format = GL_RGBA8UI;
                        f.data_type = GL_UNSIGNED_BYTE;
                        break;

                     case BlockPacking::s_16_16_16_16:
                        f.internal_format = GL_RGBA16UI;
                        f.data_type = GL_UNSIGNED_SHORT;
                        break;

                     case BlockPacking::s_32_32_32_32:
                        f.internal_format = GL_RGBA32UI;
                        f.data_type = GL_UNSIGNED_INT;
                        break;

                     case BlockPacking::p_10_10_10_2:
                        f.internal_format = GL_RGB10_A2UI;
                        f.data_type = GL_UNSIGNED_INT_10_10_10_2;
                        break;

                     case BlockPacking::p_2_10_10_10:
                        f.internal_format = GL_RGB10_A2UI;
                        f.data_type = GL_UNSIGNED_INT_2_10_10_10_REV;
                        reverse_rgba_swizzles(f.swizzle);
                        break;
                  }
                  if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                     swap_rb_swizzles(f.swizzle);
                     f.data_format = GL_BGRA_INTEGER;
                  } else {
                     f.data_format = GL_RGBA_INTEGER;
                  }
                  break;

               case FieldType::sint:
                  switch (format.packing()) {
                     case BlockPacking::s_8_8_8_8:
                        f.internal_format = GL_RGBA8I;
                        f.data_type = GL_BYTE;
                        break;

                     case BlockPacking::s_16_16_16_16:
                        f.internal_format = GL_RGBA16I;
                        f.data_type = GL_SHORT;
                        break;

                     case BlockPacking::s_32_32_32_32:
                        f.internal_format = GL_RGBA32I;
                        f.data_type = GL_INT;
                        break;
                  }
                  if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                     swap_rb_swizzles(f.swizzle);
                     f.data_format = GL_BGRA_INTEGER;
                  } else {
                     f.data_format = GL_RGBA_INTEGER;
                  }
                  break;

               case FieldType::sfloat:
                  switch (format.packing()) {
                     case BlockPacking::s_16_16_16_16:
                        f.internal_format = GL_RGBA16F;
                        f.data_type = GL_HALF_FLOAT;
                        break;

                     case BlockPacking::s_32_32_32_32:
                        f.internal_format = GL_RGBA32F;
                        f.data_type = GL_FLOAT;
                        break;
                  }
                  if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
                     swap_rb_swizzles(f.swizzle);
                     f.data_format = GL_BGRA;
                  } else {
                     f.data_format = GL_RGBA;
                  }
                  break;
            }
         }
         break;
   }
   return f;
}

} // be::gfx::tex::()

//////////////////////////////////////////////////////////////////////////////
ImageFormatGl to_gl_format(ImageFormat format) {
   ImageFormatGl f;
   std::error_code ec;
   f = to_gl_format(format, ec);
   if (ec) {
      throw std::system_error(ec);
   }
   return f;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormatGl to_gl_format(ImageFormat format, std::error_code& ec) noexcept {
   ImageFormatGl f;
   switch (format.colorspace()) {
      case Colorspace::linear_depth:
         f = to_gl_format_depth(format);
         break;

      case Colorspace::linear_stencil:
         f = to_gl_format_stencil(format);
         break;

      case Colorspace::linear_depth_stencil:
         f = to_gl_format_depth_stencil(format);
         break;

      default:
         f = is_compressed(format.packing()) ? to_gl_format_compressed(format) : to_gl_format_uncompressed(format);
         break;
   }

   using namespace gl;
   if (f.base_internal_format == GL_INVALID_VALUE || f.internal_format == GL_INVALID_VALUE ||
       f.data_format == GL_INVALID_VALUE || f.data_type == GL_INVALID_VALUE) {
      ec = std::make_error_code(std::errc::not_supported);
   }

   return f;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormat from_gl_format(ImageFormatGl format) {
   ImageFormat f;
   std::error_code ec;
   f = from_gl_format(format, ec);
   if (ec) {
      throw std::system_error(ec);
   }
   return f;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormat from_gl_format(ImageFormatGl format, std::error_code& ec) noexcept {
   using namespace gl;
   ImageFormat f;
   bool compressed = false;
   bool is_signed = false;
   bool is_int = false;
   bool is_float = false;
   U8 components = 0;
   U8 word_size = 0;
   BlockPacking packing = BlockPacking::s_8;

   switch (format.base_internal_format) {
      case GL_RED:
      case GL_RG:
      case GL_RGB:
      case GL_RGBA:
      case GL_INTENSITY:
      case GL_LUMINANCE:
      case GL_ALPHA:
      case GL_LUMINANCE_ALPHA:
         f.colorspace(Colorspace::linear_other);
         break;
      case GL_BGR:
      case GL_BGRA:
         // using BGR/BGRA isn't valid here, but some files do it anyway...
         f.colorspace(Colorspace::linear_other);
         break;
      case GL_STENCIL_INDEX:
         f.colorspace(Colorspace::linear_stencil);
         break;
      case GL_DEPTH_COMPONENT:
         f.colorspace(Colorspace::linear_depth);
         break;
      case GL_DEPTH_STENCIL:
         f.colorspace(Colorspace::linear_depth_stencil);
         break;
      default:
         ec = std::make_error_code(std::errc::not_supported);
   }

   switch (format.data_format) {
      case GL_STENCIL_INDEX:   components = 1; f.swizzles(swizzles_r()); break;
      case GL_DEPTH_COMPONENT: components = 1; f.swizzles(swizzles_r()); break;
      case GL_DEPTH_STENCIL:   components = 2; f.swizzles(swizzles_rg()); break;
      case GL_RED:             components = 1; f.swizzles(swizzles_r()); break;
      case GL_GREEN:           components = 1; f.swizzles(swizzles(Swizzle::literal_zero, Swizzle::field_zero)); break;
      case GL_BLUE:            components = 1; f.swizzles(swizzles(Swizzle::literal_zero, Swizzle::literal_zero, Swizzle::field_zero)); break;
      case GL_ALPHA:           components = 1; f.swizzles(evec4<Swizzle>(evec3<Swizzle>(Swizzle::literal_zero), Swizzle::field_zero)); break;
      case GL_RG:              components = 2; f.swizzles(swizzles_rg()); break;
      case GL_RGB:             components = 3; f.swizzles(swizzles_rgb()); break;
      case GL_RGBA:            components = 4; f.swizzles(swizzles_rgba()); break;
      case GL_BGR:             components = 3; f.swizzles(swizzles_bgr()); break;
      case GL_BGRA:            components = 4; f.swizzles(swizzles_bgra()); break;
      case GL_INTENSITY:       components = 1; f.swizzles(evec4<Swizzle>(Swizzle::field_zero)); break;
      case GL_LUMINANCE:       components = 1; f.swizzles(format.base_internal_format == GL_INTENSITY ? evec4<Swizzle>(Swizzle::field_zero) : swizzles_rrr()); break;
      case GL_LUMINANCE_ALPHA: components = 2; f.swizzles(evec4<Swizzle>(evec3<Swizzle>(Swizzle::field_zero), Swizzle::field_one)); break;
      case GL_RED_INTEGER:     components = 1; is_int = true; f.swizzles(swizzles_r()); break;
      case GL_GREEN_INTEGER:   components = 1; is_int = true; f.swizzles(swizzles(Swizzle::literal_zero, Swizzle::field_zero)); break;
      case GL_BLUE_INTEGER:    components = 1; is_int = true; f.swizzles(swizzles(Swizzle::literal_zero, Swizzle::literal_zero, Swizzle::field_zero)); break;
      case GL_ALPHA_INTEGER:   components = 1; is_int = true; f.swizzles(evec4<Swizzle>(evec3<Swizzle>(Swizzle::literal_zero), Swizzle::field_zero)); break;
      case GL_RG_INTEGER:      components = 2; is_int = true; f.swizzles(swizzles_rg()); break;
      case GL_RGB_INTEGER:     components = 3; is_int = true; f.swizzles(swizzles_rgb()); break;
      case GL_RGBA_INTEGER:    components = 4; is_int = true; f.swizzles(swizzles_rgba()); break;
      case GL_BGR_INTEGER:     components = 3; is_int = true; f.swizzles(swizzles_bgr()); break;
      case GL_BGRA_INTEGER:    components = 4; is_int = true; f.swizzles(swizzles_bgra()); break;
      default:
         if (format.data_type != GL_NONE) {
            ec = std::make_error_code(std::errc::not_supported);
         }
         break;
   }

   switch (format.data_type) {
      case GL_NONE:           compressed = true; break;
      case GL_UNSIGNED_BYTE:  word_size = 1; break;
      case GL_BYTE:           word_size = 1; is_signed = true; break;
      case GL_UNSIGNED_SHORT: word_size = 2; break;
      case GL_SHORT:          word_size = 2; is_signed = true; break;
      case GL_UNSIGNED_INT:   word_size = 4; break;
      case GL_INT:            word_size = 4; is_signed = true; break;
      case GL_HALF_FLOAT:     word_size = 2; is_signed = true; is_float = true; break;
      case GL_FLOAT:          word_size = 4; is_signed = true; is_float = true; break;
      case GL_UNSIGNED_BYTE_3_3_2:
         packing = BlockPacking::p_3_3_2;
         f.swizzles(swizzles_rgb());
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 3));
         } else {
            f.field_types(field_types(FieldType::unorm, 3));
         }
         break;
      case GL_UNSIGNED_BYTE_2_3_3_REV:
         packing = BlockPacking::p_2_3_3;
         f.swizzles(swizzles_bgr());
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 3));
         } else {
            f.field_types(field_types(FieldType::unorm, 3));
         }
         break;
      case GL_UNSIGNED_SHORT_5_6_5:
         packing = BlockPacking::p_5_6_5;
         f.swizzles(swizzles_rgb());
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 3));
         } else {
            f.field_types(field_types(FieldType::unorm, 3));
         }
         break;
      case GL_UNSIGNED_SHORT_5_6_5_REV:
         packing = BlockPacking::p_5_6_5;
         f.swizzles(swizzles_bgr());
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 3));
         } else {
            f.field_types(field_types(FieldType::unorm, 3));
         }
         break;
      case GL_UNSIGNED_SHORT_4_4_4_4:
         packing = BlockPacking::p_4_4_4_4;
         if (f.swizzle(0) == Swizzle::field_zero) {
            f.swizzles(swizzles_rgba());
         } else {
            f.swizzles(swizzles_bgra());
         }
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 4));
         } else {
            f.field_types(field_types(FieldType::unorm, 4));
         }
         break;
      case GL_UNSIGNED_SHORT_4_4_4_4_REV:
         packing = BlockPacking::p_4_4_4_4;
         if (f.swizzle(0) == Swizzle::field_zero) {
            f.swizzles(swizzles_abgr());
         } else {
            f.swizzles(swizzles_argb());
         }
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 4));
         } else {
            f.field_types(field_types(FieldType::unorm, 4));
         }
         break;
      case GL_UNSIGNED_SHORT_5_5_5_1:
         packing = BlockPacking::p_5_5_5_1;
         if (f.swizzle(0) == Swizzle::field_zero) {
            f.swizzles(swizzles_rgba());
         } else {
            f.swizzles(swizzles_bgra());
         }
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 4));
         } else {
            f.field_types(field_types(FieldType::unorm, 4));
         }
         break;
      case GL_UNSIGNED_SHORT_1_5_5_5_REV:
         packing = BlockPacking::p_1_5_5_5;
         if (f.swizzle(0) == Swizzle::field_zero) {
            f.swizzles(swizzles_abgr());
         } else {
            f.swizzles(swizzles_argb());
         }
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 4));
         } else {
            f.field_types(field_types(FieldType::unorm, 4));
         }
         break;
      case GL_UNSIGNED_INT_8_8_8_8:
         packing = BlockPacking::p_8_8_8_8;
         if (f.swizzle(0) == Swizzle::field_zero) {
            f.swizzles(swizzles_rgba());
         } else {
            f.swizzles(swizzles_bgra());
         }
         if (is_int) {
            if (format.internal_format == GL_RGBA8I) {
               f.field_types(field_types(FieldType::sint, 4));
            } else {
               f.field_types(field_types(FieldType::uint, 4));
            }
         } else {
            if (format.internal_format == GL_RGBA8_SNORM) {
               f.field_types(field_types(FieldType::snorm, 4));
            } else {
               f.field_types(field_types(FieldType::unorm, 4));
            }
         }
         break;
      case GL_UNSIGNED_INT_8_8_8_8_REV:
         packing = BlockPacking::p_8_8_8_8;
         if (f.swizzle(0) == Swizzle::field_zero) {
            f.swizzles(swizzles_abgr());
         } else {
            f.swizzles(swizzles_argb());
         }
         if (is_int) {
            if (format.internal_format == GL_RGBA8I) {
               f.field_types(field_types(FieldType::sint, 4));
            } else {
               f.field_types(field_types(FieldType::uint, 4));
            }
         } else {
            if (format.internal_format == GL_RGBA8_SNORM) {
               f.field_types(field_types(FieldType::snorm, 4));
            } else {
               f.field_types(field_types(FieldType::unorm, 4));
            }
         }
         break;
      case GL_UNSIGNED_INT_10_10_10_2:
         packing = BlockPacking::p_10_10_10_2;
         if (f.swizzle(0) == Swizzle::field_zero) {
            f.swizzles(swizzles_rgba());
         } else {
            f.swizzles(swizzles_bgra());
         }
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 4));
         } else {
            f.field_types(field_types(FieldType::unorm, 4));
         }
         break;
      case GL_UNSIGNED_INT_2_10_10_10_REV:
         packing = BlockPacking::p_2_10_10_10;
         if (f.swizzle(0) == Swizzle::field_zero) {
            f.swizzles(swizzles_abgr());
         } else {
            f.swizzles(swizzles_argb());
         }
         if (is_int) {
            f.field_types(field_types(FieldType::uint, 4));
         } else {
            f.field_types(field_types(FieldType::unorm, 4));
         }
         break;
      case GL_UNSIGNED_INT_24_8:
         packing = BlockPacking::p_24_8;
         f.swizzles(swizzles_rg());
         f.field_types(field_types(FieldType::unorm, FieldType::uint));
         break;
      case GL_UNSIGNED_INT_10F_11F_11F_REV:
         packing = BlockPacking::p_10_11_11;
         f.swizzles(swizzles_bgr());
         f.field_types(field_types(FieldType::ufloat, 3));
         break;
      case GL_UNSIGNED_INT_5_9_9_9_REV:
         packing = BlockPacking::p_5_9_9_9;
         f.swizzles(swizzles(Swizzle::field_three, Swizzle::field_two, Swizzle::field_one));
         f.field_types(field_types(FieldType::expo, FieldType::ufloat, FieldType::ufloat, FieldType::ufloat));
         break;
      case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:
         packing = BlockPacking::s_32_p_24_8;
         f.swizzles(swizzles(Swizzle::field_zero, Swizzle::field_two));
         f.field_types(field_types(FieldType::sfloat, FieldType::none, FieldType::uint));
         break;
      default:
         ec = std::make_error_code(std::errc::not_supported);
         break;
   }

   if (word_size > 0) {
      FieldType ft;
      if (is_signed) {
         if (is_float) {
            ft = FieldType::sfloat;
         } else if (is_int) {
            ft = FieldType::sint;
         } else {
            ft = FieldType::snorm;
         }
      } else {
         if (is_float) {
            ft = FieldType::ufloat;
         } else if (is_int) {
            ft = FieldType::uint;
         } else {
            ft = FieldType::unorm;
         }
      }
      f.field_types(field_types(ft, components));

      switch ((word_size << 4) | components) {
         case 0x11: packing = BlockPacking::s_8; break;
         case 0x12: packing = BlockPacking::s_8_8; break;
         case 0x13: packing = BlockPacking::s_8_8_8; break;
         case 0x14: packing = BlockPacking::s_8_8_8_8; break;
         case 0x21: packing = BlockPacking::s_16; break;
         case 0x22: packing = BlockPacking::s_16_16; break;
         case 0x23: packing = BlockPacking::s_16_16_16; break;
         case 0x24: packing = BlockPacking::s_16_16_16_16; break;
         case 0x41: packing = BlockPacking::s_32; break;
         case 0x42: packing = BlockPacking::s_32_32; break;
         case 0x43: packing = BlockPacking::s_32_32_32; break;
         case 0x44: packing = BlockPacking::s_32_32_32_32; break;
         default:
            ec = std::make_error_code(std::errc::not_supported);
            break;
      }
   }

   if (compressed) {
      switch (format.internal_format) {
         //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
         case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
         //#bgl checked (GL_EXT_texture_compression_s3tc)
         case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
         //#bgl unchecked
            f.packing(BlockPacking::c_s3tc1);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(8));
            f.components(3);
            f.field_types(field_types(FieldType::unorm, 3));
            f.swizzles(swizzles_rgb());
            break;
         //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
         case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
         //#bgl checked (GL_EXT_texture_compression_s3tc)
         case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
         //#bgl unchecked
            f.packing(BlockPacking::c_s3tc1);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(8));
            f.components(4);
            f.field_types(field_types(FieldType::unorm, 4));
            f.swizzles(swizzles_rgba());
            break;
         //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
         case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
         //#bgl checked (GL_EXT_texture_compression_s3tc)
         case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
         //#bgl unchecked
            f.packing(BlockPacking::c_s3tc2);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(16));
            f.components(4);
            f.field_types(field_types(FieldType::unorm, 4));
            f.swizzles(swizzles_rgba());
            break;
         //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
         case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
         //#bgl checked (GL_EXT_texture_compression_s3tc)
         case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
         //#bgl unchecked
            f.packing(BlockPacking::c_s3tc3);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(16));
            f.components(4);
            f.field_types(field_types(FieldType::unorm, 4));
            f.swizzles(swizzles_rgba());
            break;
         case GL_COMPRESSED_RED_RGTC1:
            f.packing(BlockPacking::c_rgtc1);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(8));
            f.components(1);
            f.field_types(field_types(FieldType::unorm, 1));
            f.swizzles(swizzles_r());
            break;
         case GL_COMPRESSED_SIGNED_RED_RGTC1:
            f.packing(BlockPacking::c_rgtc1);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(8));
            f.components(1);
            f.field_types(field_types(FieldType::snorm, 1));
            f.swizzles(swizzles_r());
            break;
         case GL_COMPRESSED_RG_RGTC2:
            f.packing(BlockPacking::c_rgtc2);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(16));
            f.components(2);
            f.field_types(field_types(FieldType::unorm, 2));
            f.swizzles(swizzles_rg());
            break;
         case GL_COMPRESSED_SIGNED_RG_RGTC2:
            f.packing(BlockPacking::c_rgtc2);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(16));
            f.components(2);
            f.field_types(field_types(FieldType::snorm, 2));
            f.swizzles(swizzles_rg());
            break;
         //#bgl checked (GL_VERSION_4_2)
         case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:
         case GL_COMPRESSED_RGBA_BPTC_UNORM:
         //#bgl unchecked
            f.packing(BlockPacking::c_bptc);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(16));
            f.components(4);
            f.field_types(field_types(FieldType::unorm, 4));
            f.swizzles(swizzles_rgba());
            break;
         //#bgl checked (GL_VERSION_4_2)
         case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:
         //#bgl unchecked
            f.packing(BlockPacking::c_bptc);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(16));
            f.components(3);
            f.field_types(field_types(FieldType::sfloat, 3));
            f.swizzles(swizzles_rgb());
         //#bgl checked (GL_VERSION_4_2)
         case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:
         //#bgl unchecked
            f.packing(BlockPacking::c_bptc);
            f.block_dim(ImageFormat::block_dim_type(U8(4), U8(4), U8(1)));
            f.block_size(U8(16));
            f.components(3);
            f.field_types(field_types(FieldType::ufloat, 3));
            f.swizzles(swizzles_rgb());
            break;
         default:
            ec = std::make_error_code(std::errc::not_supported);
            break;
      }
   } else {
      f.block_dim(1);
      f.packing(packing);
      f.block_size(block_word_size(packing) * block_word_count(packing));
      f.components(components);
   }
   
   switch (format.internal_format) {
      //#bgl checked (GL_EXT_texture_sRGB)
      case GL_SRGB:
      case GL_SRGB_ALPHA:
      case GL_SRGB8:
      case GL_SRGB8_ALPHA8:
      //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
      case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
      //#bgl checked (GL_VERSION_4_2)
      case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:
      //#bgl unchecked
         f.colorspace(Colorspace::srgb);
         break;
      default:
         break;
   }

   auto new_swizzles = f.swizzles();
   for (glm::length_t c = 0; c < new_swizzles.length(); ++c) {
      switch (format.swizzle[c]) {
         case GL_RED:
            new_swizzles[c] = f.swizzle(0);
            break;
         case GL_GREEN:
            new_swizzles[c] = f.swizzle(1);
            break;
         case GL_BLUE:
            new_swizzles[c] = f.swizzle(2);
            break;
         case GL_ALPHA:
            new_swizzles[c] = f.swizzle(3);
            break;
         case GL_ONE:
            new_swizzles[c] = Swizzle::literal_one;
            break;
         case GL_ZERO:
            new_swizzles[c] = Swizzle::literal_zero;
            break;
         default:
            ec = std::make_error_code(std::errc::invalid_argument);
            break;
      }
   }
   f.swizzles(new_swizzles);

   return f;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormat canonical_format(gl::GLenum internal_format) {
   ImageFormat format;
   std::error_code ec;
   format = canonical_format(internal_format, ec);
   if (ec) {
      throw std::system_error(ec);
   }
   return format;
}

//////////////////////////////////////////////////////////////////////////////
ImageFormat canonical_format(gl::GLenum internal_format, std::error_code& ec) noexcept {
   using namespace gl;
   using Dim = ImageFormat::block_dim_type;

   switch (internal_format) {
      //#bgl checked (GL_EXT_texture_compression_s3tc)
      case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:        return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc1, U8(3), field_types(FieldType::unorm, 3), swizzles_rgb(),  Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:       return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc1, U8(4), field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:       return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc2, U8(4), field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:       return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc3, U8(4), field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      //#bgl checked (GL_EXT_texture_compression_s3tc_srgb)
      case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:       return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc1, U8(3), field_types(FieldType::unorm, 3), swizzles_rgb(),  Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT: return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc1, U8(4), field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT: return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc2, U8(4), field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT: return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc3, U8(4), field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      //#bgl unchecked
      case GL_COMPRESSED_RED_RGTC1:                return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_rgtc1, U8(1), field_types(FieldType::unorm, 1), swizzles_r(),    Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SIGNED_RED_RGTC1:         return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_rgtc1, U8(1), field_types(FieldType::snorm, 1), swizzles_r(),    Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RG_RGTC2:                 return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_rgtc2, U8(2), field_types(FieldType::unorm, 2), swizzles_rg(),   Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SIGNED_RG_RGTC2:          return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_rgtc2, U8(2), field_types(FieldType::snorm, 2), swizzles_rg(),   Colorspace::bt709_linear_rgb, true);
      //#bgl checked (4.2)
      case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:    return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_bptc, U8(4), field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_RGBA_BPTC_UNORM:          return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_bptc, U8(4), field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:    return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_bptc, U8(3), field_types(FieldType::sfloat, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:  return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_bptc, U8(3), field_types(FieldType::ufloat, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      //#bgl unchecked

      case GL_DEPTH_COMPONENT:
      case GL_DEPTH_COMPONENT32:    return ImageFormat(U8(4), U8(1), BlockPacking::s_32, U8(1), field_types(FieldType::unorm, 1), swizzles_rrr(), Colorspace::linear_depth, true);
      case GL_DEPTH_COMPONENT16:    return ImageFormat(U8(2), U8(1), BlockPacking::s_16, U8(1), field_types(FieldType::unorm, 1), swizzles_rrr(), Colorspace::linear_depth, true);
      case GL_DEPTH_COMPONENT32F:   return ImageFormat(U8(4), U8(1), BlockPacking::s_32, U8(1), field_types(FieldType::sfloat, 1), swizzles_rrr(), Colorspace::linear_depth, true);
      case GL_DEPTH_COMPONENT24:    return ImageFormat(U8(4), U8(1), BlockPacking::p_8_24, U8(1), field_types(FieldType::none, FieldType::unorm), swizzles(Swizzle::field_one, Swizzle::field_one, Swizzle::field_one), Colorspace::linear_depth, true);

      case GL_STENCIL_INDEX:
      case GL_STENCIL_INDEX8:       return ImageFormat(U8(1), U8(1), BlockPacking::s_8, U8(1), field_types(FieldType::uint, 1), swizzles_rrr(), Colorspace::linear_stencil, true);

      case GL_DEPTH_STENCIL:
      case GL_DEPTH24_STENCIL8:     return ImageFormat(U8(4), U8(1), BlockPacking::p_24_8, U8(2), field_types(FieldType::unorm, FieldType::uint), swizzles_rg(), Colorspace::linear_depth_stencil, true);
      case GL_DEPTH32F_STENCIL8:    return ImageFormat(U8(8), U8(1), BlockPacking::s_32_p_24_8, U8(2), field_types(FieldType::sfloat, FieldType::none, FieldType::uint), swizzles(Swizzle::field_zero, Swizzle::field_two), Colorspace::linear_depth_stencil, true);

      case GL_RED:
      case GL_R8:             return ImageFormat(U8(1), U8(1), BlockPacking::s_8,  1, field_types(FieldType::unorm, 1),  swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16:            return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, field_types(FieldType::unorm, 1),  swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R8_SNORM:       return ImageFormat(U8(1), U8(1), BlockPacking::s_8,  1, field_types(FieldType::snorm, 1),  swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16_SNORM:      return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, field_types(FieldType::snorm, 1),  swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R8UI:           return ImageFormat(U8(1), U8(1), BlockPacking::s_8,  1, field_types(FieldType::uint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16UI:          return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, field_types(FieldType::uint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R32UI:          return ImageFormat(U8(4), U8(1), BlockPacking::s_32, 1, field_types(FieldType::uint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R8I:            return ImageFormat(U8(1), U8(1), BlockPacking::s_8,  1, field_types(FieldType::sint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16I:           return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, field_types(FieldType::sint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R32I:           return ImageFormat(U8(4), U8(1), BlockPacking::s_32, 1, field_types(FieldType::sint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16F:           return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, field_types(FieldType::sfloat, 1), swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R32F:           return ImageFormat(U8(4), U8(1), BlockPacking::s_32, 1, field_types(FieldType::sfloat, 1), swizzles_rrr(), Colorspace::bt709_linear_rgb, true);

      case GL_RG:
      case GL_RG8:            return ImageFormat(U8(2), U8(1), BlockPacking::s_8_8,   2, field_types(FieldType::unorm, 2),  swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16:           return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, field_types(FieldType::unorm, 2),  swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG8_SNORM:      return ImageFormat(U8(2), U8(1), BlockPacking::s_8_8,   2, field_types(FieldType::snorm, 2),  swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16_SNORM:     return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, field_types(FieldType::snorm, 2),  swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG8UI:          return ImageFormat(U8(2), U8(1), BlockPacking::s_8_8,   2, field_types(FieldType::uint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16UI:         return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, field_types(FieldType::uint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG32UI:         return ImageFormat(U8(8), U8(1), BlockPacking::s_32_32, 2, field_types(FieldType::uint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG8I:           return ImageFormat(U8(2), U8(1), BlockPacking::s_8_8,   2, field_types(FieldType::sint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16I:          return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, field_types(FieldType::sint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG32I:          return ImageFormat(U8(8), U8(1), BlockPacking::s_32_32, 2, field_types(FieldType::sint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16F:          return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, field_types(FieldType::sfloat, 2), swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG32F:          return ImageFormat(U8(8), U8(1), BlockPacking::s_32_32, 2, field_types(FieldType::sfloat, 2), swizzles_rg(), Colorspace::bt709_linear_rgb, true);

      case GL_SRGB:
      case GL_SRGB8:          return ImageFormat(U8(3), U8(1), BlockPacking::s_8_8_8, 3, field_types(FieldType::unorm, 3), swizzles_rgb(), Colorspace::srgb, true);

      case GL_RGB:
      case GL_RGB8:           return ImageFormat(U8(3), U8(1), BlockPacking::s_8_8_8, 3, field_types(FieldType::unorm, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);

      case GL_RGB16:          return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, field_types(FieldType::unorm, 3),  swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_R3_G3_B2:       return ImageFormat(U8(1),  U8(1), BlockPacking::p_2_3_3,    3, field_types(FieldType::unorm, 3),  swizzles_bgr(), Colorspace::bt709_linear_rgb, true);
      //#bgl checked (4.1)
      case GL_RGB565:         return ImageFormat(U8(2),  U8(1), BlockPacking::p_5_6_5,    3, field_types(FieldType::unorm, 3),  swizzles_bgr(), Colorspace::bt709_linear_rgb, true);
      //#bgl unchecked
      case GL_RGB4:           return ImageFormat(U8(2),  U8(1), BlockPacking::p_4_4_4_4,  3, field_types(FieldType::none, FieldType::unorm, FieldType::unorm, FieldType::unorm), swizzles_abg(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB5:           return ImageFormat(U8(2),  U8(1), BlockPacking::p_1_5_5_5,  3, field_types(FieldType::none, FieldType::unorm, FieldType::unorm, FieldType::unorm), swizzles_abg(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB8_SNORM:     return ImageFormat(U8(3),  U8(1), BlockPacking::s_8_8_8,    3, field_types(FieldType::snorm, 3),  swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB16_SNORM:    return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, field_types(FieldType::snorm, 3),  swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB8UI:         return ImageFormat(U8(3),  U8(1), BlockPacking::s_8_8_8,    3, field_types(FieldType::uint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB16UI:        return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, field_types(FieldType::uint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB32UI:        return ImageFormat(U8(12), U8(1), BlockPacking::s_32_32_32, 3, field_types(FieldType::uint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB8I:          return ImageFormat(U8(3),  U8(1), BlockPacking::s_8_8_8,    3, field_types(FieldType::sint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB16I:         return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, field_types(FieldType::sint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB32I:         return ImageFormat(U8(12), U8(1), BlockPacking::s_32_32_32, 3, field_types(FieldType::sint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_R11F_G11F_B10F: return ImageFormat(U8(4),  U8(1), BlockPacking::p_10_11_11, 3, field_types(FieldType::ufloat, 3), swizzles_bgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB16F:         return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, field_types(FieldType::sfloat, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB32F:         return ImageFormat(U8(12), U8(1), BlockPacking::s_32_32_32, 3, field_types(FieldType::sfloat, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB9_E5:        return ImageFormat(U8(4),  U8(1), BlockPacking::p_5_9_9_9,  3, field_types(FieldType::expo, FieldType::ufloat, FieldType::ufloat, FieldType::ufloat), swizzles_abg(), Colorspace::bt709_linear_rgb, true);

      case GL_RGBA16:         return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, field_types(FieldType::unorm, 4),  swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA4:          return ImageFormat(U8(2),  U8(1), BlockPacking::p_4_4_4_4,     4, field_types(FieldType::unorm, 4),  swizzles_abgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB5_A1:        return ImageFormat(U8(2),  U8(1), BlockPacking::p_1_5_5_5,     4, field_types(FieldType::unorm, 4),  swizzles_abgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB10_A2:       return ImageFormat(U8(4),  U8(1), BlockPacking::p_2_10_10_10,  4, field_types(FieldType::unorm, 4),  swizzles_abgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA8_SNORM:    return ImageFormat(U8(4),  U8(1), BlockPacking::s_8_8_8_8,     4, field_types(FieldType::snorm, 4),  swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA16_SNORM:   return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, field_types(FieldType::snorm, 4),  swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA8UI:        return ImageFormat(U8(4),  U8(1), BlockPacking::s_8_8_8_8,     4, field_types(FieldType::uint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA16UI:       return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, field_types(FieldType::uint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA32UI:       return ImageFormat(U8(16), U8(1), BlockPacking::s_32_32_32_32, 4, field_types(FieldType::uint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB10_A2UI:     return ImageFormat(U8(4),  U8(1), BlockPacking::p_2_10_10_10,  4, field_types(FieldType::uint, 4),   swizzles_abgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA8I:         return ImageFormat(U8(4),  U8(1), BlockPacking::s_8_8_8_8,     4, field_types(FieldType::sint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA16I:        return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, field_types(FieldType::sint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA32I:        return ImageFormat(U8(16), U8(1), BlockPacking::s_32_32_32_32, 4, field_types(FieldType::sint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA16F:        return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, field_types(FieldType::sfloat, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA32F:        return ImageFormat(U8(18), U8(1), BlockPacking::s_32_32_32_32, 4, field_types(FieldType::sfloat, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);

      case GL_SRGB_ALPHA:
      case GL_SRGB8_ALPHA8:   return ImageFormat(U8(4), U8(1), BlockPacking::s_8_8_8_8, 4, field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);

      case GL_RGBA:
      case GL_RGBA8:          return ImageFormat(U8(4), U8(1), BlockPacking::s_8_8_8_8, 4, field_types(FieldType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);

      default:
         ec = std::make_error_code(std::errc::not_supported);
         return ImageFormat();
   }
}




// TODO preferred_format




} // be::gfx::tex

