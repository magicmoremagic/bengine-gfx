#include "pch.hpp"
#include "tex/image_format_gl.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace be::gfx::tex {
namespace {

///////////////////////////////////////////////////////////////////////////////
void swap_rg_swizzles(gl::GLenum* swizzles) {
   using namespace gl;
   for (std::size_t i = 0; i < 4; ++i) {
      switch (swizzles[i]) {
         case GL_RED: swizzles[i] = GL_GREEN;
         case GL_GREEN: swizzles[i] = GL_RED;
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
void swap_rb_swizzles(gl::GLenum* swizzles) {
   using namespace gl;
   for (std::size_t i = 0; i < 4; ++i) {
      switch (swizzles[i]) {
         case GL_RED: swizzles[i] = GL_BLUE;
         case GL_BLUE: swizzles[i] = GL_RED;
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
void swap_gb_swizzles(gl::GLenum* swizzles) {
   using namespace gl;
   for (std::size_t i = 0; i < 4; ++i) {
      switch (swizzles[i]) {
         case GL_GREEN: swizzles[i] = GL_BLUE;
         case GL_BLUE: swizzles[i] = GL_GREEN;
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
ImageFormatGl gl_format_compressed(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
   f.internal_format = GL_INVALID_VALUE;
   f.data_format = GL_NONE;
   f.data_type = GL_NONE;
   f.swizzle[0] = swizzle_to_gl(format.swizzle(0));
   f.swizzle[1] = swizzle_to_gl(format.swizzle(1));
   f.swizzle[2] = swizzle_to_gl(format.swizzle(2));
   f.swizzle[3] = swizzle_to_gl(format.swizzle(3));

   switch (format.packing()) {
      case BlockPacking::c_astc:
         // components() and component_types() are not checked since they can vary per block
         if (format.block_size() == 16 && format.block_dim().z == 1 && format.block_dim().y < 16) {
            if (format.colorspace() == Colorspace::srgb) {
               switch ((format.block_dim().x << 4) | (format.block_dim().y & 0xF)) {
                  case 0x44: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR; break;
                  case 0x54: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR; break;
                  case 0x55: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR; break;
                  case 0x65: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR; break;
                  case 0x66: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR; break;
                  case 0x85: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR; break;
                  case 0x86: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR; break;
                  case 0x88: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR; break;
                  case 0xA5: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR; break;
                  case 0xA6: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR; break;
                  case 0xA8: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR; break;
                  case 0xAA: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR; break;
                  case 0xCA: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR; break;
                  case 0xCC: f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR; break;
               }
            } else {
               switch ((format.block_dim().x << 4) | (format.block_dim().y & 0xF)) {
                  case 0x44: f.internal_format = GL_COMPRESSED_RGBA_ASTC_4x4_KHR; break;
                  case 0x54: f.internal_format = GL_COMPRESSED_RGBA_ASTC_5x4_KHR; break;
                  case 0x55: f.internal_format = GL_COMPRESSED_RGBA_ASTC_5x5_KHR; break;
                  case 0x65: f.internal_format = GL_COMPRESSED_RGBA_ASTC_6x5_KHR; break;
                  case 0x66: f.internal_format = GL_COMPRESSED_RGBA_ASTC_6x6_KHR; break;
                  case 0x85: f.internal_format = GL_COMPRESSED_RGBA_ASTC_8x5_KHR; break;
                  case 0x86: f.internal_format = GL_COMPRESSED_RGBA_ASTC_8x6_KHR; break;
                  case 0x88: f.internal_format = GL_COMPRESSED_RGBA_ASTC_8x8_KHR; break;
                  case 0xA5: f.internal_format = GL_COMPRESSED_RGBA_ASTC_10x5_KHR; break;
                  case 0xA6: f.internal_format = GL_COMPRESSED_RGBA_ASTC_10x6_KHR; break;
                  case 0xA8: f.internal_format = GL_COMPRESSED_RGBA_ASTC_10x8_KHR; break;
                  case 0xAA: f.internal_format = GL_COMPRESSED_RGBA_ASTC_10x10_KHR; break;
                  case 0xCA: f.internal_format = GL_COMPRESSED_RGBA_ASTC_12x10_KHR; break;
                  case 0xCC: f.internal_format = GL_COMPRESSED_RGBA_ASTC_12x12_KHR; break;
               }
            }
         }
         break;
      
      case BlockPacking::c_bptc:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 16) {
            if (format.components() == 4 && format.component_types() == component_types(ComponentType::unorm, 4)) {
               if (format.colorspace() == Colorspace::srgb) {
                  f.internal_format = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM;
               } else {
                  f.internal_format = GL_COMPRESSED_RGBA_BPTC_UNORM;
               }
            } else if (format.components() == 3) {
               if (format.component_types() == component_types(ComponentType::sfloat, 3)) {
                  f.internal_format = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT;
               } else if (format.component_types() == component_types(ComponentType::ufloat, 3)) {
                  f.internal_format = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;
               }
            }
         }
         break;

      case BlockPacking::c_etc1: // etc1 is not directly supported by opengl except as a subset of etc2
      case BlockPacking::c_etc2:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1))) {
            switch (format.components()) {
               case 1:
                  if (format.block_size() == 8) {
                     if (format.component_types() == component_types(ComponentType::unorm, 1)) {
                        f.internal_format = GL_COMPRESSED_R11_EAC;
                     } else if (format.component_types() == component_types(ComponentType::snorm, 1)) {
                        f.internal_format = GL_COMPRESSED_SIGNED_R11_EAC;
                     }
                  }
                  break;

               case 2:
                  if (format.block_size() == 16) {
                     if (format.component_types() == component_types(ComponentType::unorm, 2)) {
                        f.internal_format = GL_COMPRESSED_RG11_EAC;
                     } else if (format.component_types() == component_types(ComponentType::snorm, 2)) {
                        f.internal_format = GL_COMPRESSED_SIGNED_RG11_EAC;
                     }
                  }
                  break;

               case 3:
                  if (format.block_size() == 8 && format.component_types() == component_types(ComponentType::unorm, 3)) {
                     if (format.colorspace() == Colorspace::srgb) {
                        f.internal_format = GL_COMPRESSED_SRGB8_ETC2;
                     } else {
                        f.internal_format = GL_COMPRESSED_RGB8_ETC2;
                     }
                  }
                  break;

               case 4:
                  if (format.component_types() == component_types(ComponentType::unorm, 4)) {
                     if (format.block_size() == 8) {
                        if (format.colorspace() == Colorspace::srgb) {
                           f.internal_format = GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2;
                        } else {
                           f.internal_format = GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2;
                        }
                     } else if (format.block_size() == 16) {
                        if (format.colorspace() == Colorspace::srgb) {
                           f.internal_format = GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC;
                        } else {
                           f.internal_format = GL_COMPRESSED_RGBA8_ETC2_EAC;
                        }
                     }
                  }
                  break;
            }
         }
         break;

      case BlockPacking::c_s3tc1:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 8) {
            if (format.components() == 3 && format.component_types() == component_types(ComponentType::unorm, 3)) {
               if (format.colorspace() == Colorspace::srgb) {
                  f.internal_format = GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
               } else {
                  f.internal_format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
               }
            } else if (format.components() == 4 && format.component_types() == component_types(ComponentType::unorm, 4)) {
               if (format.colorspace() == Colorspace::srgb) {
                  f.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
               } else {
                  f.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
               }
            }
         }
         break;

      case BlockPacking::c_s3tc2:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 16 &&
             format.components() == 4 && format.component_types() == component_types(ComponentType::unorm, 4)) {
            if (format.colorspace() == Colorspace::srgb) {
               f.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
            } else {
               f.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            }
         }
         break;

      case BlockPacking::c_s3tc3:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 16 &&
             format.components() == 4 && format.component_types() == component_types(ComponentType::unorm, 4)) {
            if (format.colorspace() == Colorspace::srgb) {
               f.internal_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
            } else {
               f.internal_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            }
         }
         break;

      case BlockPacking::c_rgtc1:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 8 && format.components() == 1) {
            if (format.component_types() == component_types(ComponentType::unorm, 1)) {
               f.internal_format = GL_COMPRESSED_RED_RGTC1;
            } else if (format.component_types() == component_types(ComponentType::snorm, 1)) {
               f.internal_format = GL_COMPRESSED_SIGNED_RED_RGTC1;
            }
         }
         break;

      case BlockPacking::c_rgtc2:
         if (format.block_dim() == ImageFormat::block_dim_type(U8(4), U8(4), U8(1)) && format.block_size() == 16 && format.components() == 2) {
            if (format.component_types() == component_types(ComponentType::unorm, 2)) {
               f.internal_format = GL_COMPRESSED_RG_RGTC2;
            } else if (format.component_types() == component_types(ComponentType::snorm, 2)) {
               f.internal_format = GL_COMPRESSED_SIGNED_RG_RGTC2;
            }
         }
         break;
   }
   return f;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormatGl gl_format_depth(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
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
            if (format.component_types() == component_types(ComponentType::unorm, 1)) {
               f.internal_format = GL_DEPTH_COMPONENT16;
               f.data_format = GL_DEPTH_COMPONENT;
               f.data_type = GL_UNSIGNED_SHORT;
            }
            break;

         case BlockPacking::s_32:
            if (format.component_types() == component_types(ComponentType::unorm, 1)) {
               f.internal_format = GL_DEPTH_COMPONENT32;
               f.data_format = GL_DEPTH_COMPONENT;
               f.data_type = GL_UNSIGNED_INT;
            } else if (format.component_types() == component_types(ComponentType::sfloat, 1)) {
               f.internal_format = GL_DEPTH_COMPONENT32F;
               f.data_format = GL_DEPTH_COMPONENT;
               f.data_type = GL_FLOAT;
            }
            break;

         case BlockPacking::p_8_24:
            if (format.component_types() == component_types(ComponentType::none, ComponentType::unorm)) {
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

///////////////////////////////////////////////////////////////////////////////
ImageFormatGl gl_format_stencil(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
   f.internal_format = GL_INVALID_VALUE;
   f.data_format = GL_INVALID_VALUE;
   f.data_type = GL_INVALID_VALUE;
   f.swizzle[0] = swizzle_to_gl(format.swizzle(0));
   f.swizzle[1] = swizzle_to_gl(format.swizzle(1));
   f.swizzle[2] = swizzle_to_gl(format.swizzle(2));
   f.swizzle[3] = swizzle_to_gl(format.swizzle(3));

   if (format.block_dim() == ImageFormat::block_dim_type(1) && format.components() == 1 &&
       format.packing() == BlockPacking::s_8 && format.component_types() == component_types(ComponentType::uint, 1)) {
      f.internal_format = GL_STENCIL_INDEX8;
      f.data_format = GL_STENCIL_INDEX;
      f.data_type = GL_UNSIGNED_BYTE;
   }

   return f;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormatGl gl_format_depth_stencil(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
   f.internal_format = GL_INVALID_VALUE;
   f.data_format = GL_INVALID_VALUE;
   f.data_type = GL_INVALID_VALUE;
   f.swizzle[0] = swizzle_to_gl(format.swizzle(0));
   f.swizzle[1] = swizzle_to_gl(format.swizzle(1));
   f.swizzle[2] = swizzle_to_gl(format.swizzle(2));
   f.swizzle[3] = swizzle_to_gl(format.swizzle(3));

   if (format.block_dim() == ImageFormat::block_dim_type(1) && format.components() == 2) {
      if (format.packing() == BlockPacking::p_24_8 && format.component_types() == component_types(ComponentType::unorm, ComponentType::uint)) {
         f.data_format = GL_DEPTH_STENCIL;
         f.internal_format = GL_DEPTH24_STENCIL8;
         f.data_type = GL_UNSIGNED_INT_24_8;
      } else if (format.packing() == BlockPacking::s_32_p_24_8 && format.component_types() == component_types(ComponentType::sfloat, ComponentType::none, ComponentType::uint)) {
         f.data_format = GL_DEPTH_STENCIL;
         f.internal_format = GL_DEPTH32F_STENCIL8;
         f.data_type = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
         swap_gb_swizzles(f.swizzle);
      }
   }

   return f;
}

///////////////////////////////////////////////////////////////////////////////
ImageFormatGl gl_format_uncompressed(ImageFormat format) {
   using namespace gl;
   ImageFormatGl f;
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

   ComponentType first_type = format.component_type(0);
   switch (format.components()) {
      case 1:
         if (format.component_types() == component_types(first_type, 1)) {
            switch (first_type) {
               case ComponentType::unorm:
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

               case ComponentType::snorm:
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

               case ComponentType::uint:
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

               case ComponentType::sint:
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

               case ComponentType::sfloat:
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
         if (format.component_types() == component_types(first_type, 2)) {
            switch (first_type) {
               case ComponentType::unorm:
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

               case ComponentType::snorm:
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

               case ComponentType::uint:
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

               case ComponentType::sint:
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

               case ComponentType::sfloat:
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
         if (format.component_types() == component_types(first_type, 3)) {
            switch (first_type) {
               case ComponentType::unorm:
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

               case ComponentType::snorm:
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

               case ComponentType::uint:
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

               case ComponentType::sint:
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

               case ComponentType::ufloat:
                  switch (format.packing()) {
                     case BlockPacking::p_10_11_11:
                        f.internal_format = GL_R11F_G11F_B10F;
                        f.data_type = GL_UNSIGNED_INT_10F_11F_11F_REV;
                        swap_rb_swizzles(f.swizzle);
                        break;
                  }
                  f.data_format = GL_RGB;
                  break;

               case ComponentType::sfloat:
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
         } else if (format.packing() == BlockPacking::p_1_5_5_5 && format.component_types() == component_types(ComponentType::none, ComponentType::unorm, ComponentType::unorm, ComponentType::unorm)) {
            f.internal_format = GL_RGB5;
            f.data_type = GL_UNSIGNED_SHORT_1_5_5_5_REV;
            reverse_rgba_swizzles(f.swizzle);
            if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
               swap_rb_swizzles(f.swizzle);
               f.data_format = GL_BGRA;
            } else {
               f.data_format = GL_RGBA;
            }
         } else if (format.packing() == BlockPacking::p_4_4_4_4 && format.component_types() == component_types(ComponentType::none, ComponentType::unorm, ComponentType::unorm, ComponentType::unorm)) {
            f.internal_format = GL_RGB4;
            f.data_type = GL_UNSIGNED_SHORT_4_4_4_4_REV;
            reverse_rgba_swizzles(f.swizzle);
            if (f.swizzle[0] == GL_BLUE && f.swizzle[2] == GL_RED) {
               swap_rb_swizzles(f.swizzle);
               f.data_format = GL_BGRA;
            } else {
               f.data_format = GL_RGBA;
            }
         } else if (format.packing() == BlockPacking::p_5_9_9_9 && format.component_types() == component_types(ComponentType::expo, ComponentType::ufloat, ComponentType::ufloat, ComponentType::ufloat)) {
            f.data_format = GL_RGB;
            f.internal_format = GL_RGB9_E5;
            f.data_type = GL_UNSIGNED_INT_5_9_9_9_REV;
            reverse_rgba_swizzles(f.swizzle);
         }
         break;

      case 4:
         if (format.component_types() == component_types(first_type, 4)) {
            switch (first_type) {
               case ComponentType::unorm:
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

               case ComponentType::snorm:
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

               case ComponentType::uint:
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

               case ComponentType::sint:
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

               case ComponentType::sfloat:
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

///////////////////////////////////////////////////////////////////////////////
ImageFormatGl gl_format(ImageFormat format) {
   switch (format.colorspace()) {
      case Colorspace::linear_depth:
         return gl_format_depth(format);

      case Colorspace::linear_stencil:
         return gl_format_stencil(format);

      case Colorspace::linear_depth_stencil:
         return gl_format_depth_stencil(format);

      default:
         return is_compressed(format.packing()) ? gl_format_compressed(format) : gl_format_uncompressed(format);
   }
}

ImageFormat canonical_format(gl::GLenum internal_format) {
   using namespace gl;
   using Dim = ImageFormat::block_dim_type;

   switch (internal_format) {
      //ImageFormat(block_size_type, block_dim_type, BlockPacking, U8, component_types_type, swizzles_type, Colorspace, bool);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR:   return ImageFormat(U8(16), Dim(U8(4),  U8(4),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR:   return ImageFormat(U8(16), Dim(U8(5),  U8(4),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR:   return ImageFormat(U8(16), Dim(U8(5),  U8(5),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR:   return ImageFormat(U8(16), Dim(U8(6),  U8(5),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR:   return ImageFormat(U8(16), Dim(U8(6),  U8(6),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR:   return ImageFormat(U8(16), Dim(U8(8),  U8(5),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR:   return ImageFormat(U8(16), Dim(U8(8),  U8(6),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR:   return ImageFormat(U8(16), Dim(U8(8),  U8(8),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR:  return ImageFormat(U8(16), Dim(U8(10), U8(5),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR:  return ImageFormat(U8(16), Dim(U8(10), U8(6),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR:  return ImageFormat(U8(16), Dim(U8(10), U8(8),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR: return ImageFormat(U8(16), Dim(U8(10), U8(10), U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR: return ImageFormat(U8(16), Dim(U8(12), U8(10), U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR: return ImageFormat(U8(16), Dim(U8(12), U8(12), U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_RGBA_ASTC_4x4_KHR:           return ImageFormat(U8(16), Dim(U8(4),  U8(4),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_5x4_KHR:           return ImageFormat(U8(16), Dim(U8(5),  U8(4),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_5x5_KHR:           return ImageFormat(U8(16), Dim(U8(5),  U8(5),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_6x5_KHR:           return ImageFormat(U8(16), Dim(U8(6),  U8(5),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_6x6_KHR:           return ImageFormat(U8(16), Dim(U8(6),  U8(6),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_8x5_KHR:           return ImageFormat(U8(16), Dim(U8(8),  U8(5),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_8x6_KHR:           return ImageFormat(U8(16), Dim(U8(8),  U8(6),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_8x8_KHR:           return ImageFormat(U8(16), Dim(U8(8),  U8(8),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_10x5_KHR:          return ImageFormat(U8(16), Dim(U8(10), U8(5),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_10x6_KHR:          return ImageFormat(U8(16), Dim(U8(10), U8(6),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_10x8_KHR:          return ImageFormat(U8(16), Dim(U8(10), U8(8),  U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_10x10_KHR:         return ImageFormat(U8(16), Dim(U8(10), U8(10), U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_12x10_KHR:         return ImageFormat(U8(16), Dim(U8(12), U8(10), U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGBA_ASTC_12x12_KHR:         return ImageFormat(U8(16), Dim(U8(12), U8(12), U8(1)), BlockPacking::c_astc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);

      case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:       return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_bptc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_RGBA_BPTC_UNORM:             return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_bptc, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:       return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_bptc, U8(3), component_types(ComponentType::sfloat, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:     return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_bptc, U8(3), component_types(ComponentType::ufloat, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);

      case GL_COMPRESSED_R11_EAC:                        return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(1), component_types(ComponentType::unorm, 1), swizzles_r(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SIGNED_R11_EAC:                 return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(1), component_types(ComponentType::snorm, 1), swizzles_r(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RG11_EAC:                       return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(2), component_types(ComponentType::unorm, 2), swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SIGNED_RG11_EAC:                return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(2), component_types(ComponentType::snorm, 2), swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SRGB8_ETC2:                     return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(3), component_types(ComponentType::unorm, 3), swizzles_rgb(),  Colorspace::srgb, true);
      case GL_COMPRESSED_RGB8_ETC2:                      return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(3), component_types(ComponentType::unorm, 3), swizzles_rgb(),  Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2: return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:  return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:          return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_RGBA8_ETC2_EAC:                 return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_etc2, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);

      case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:       return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc1, U8(3), component_types(ComponentType::unorm, 3), swizzles_rgb(),  Colorspace::srgb, true);
      case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:        return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc1, U8(3), component_types(ComponentType::unorm, 3), swizzles_rgb(),  Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT: return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc1, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:       return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc1, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT: return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc2, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:       return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc2, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT: return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc3, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);
      case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:       return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_s3tc3, U8(4), component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RED_RGTC1:                return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_rgtc1, U8(1), component_types(ComponentType::unorm, 1), swizzles_r(),    Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SIGNED_RED_RGTC1:         return ImageFormat(U8(8),  Dim(U8(4), U8(4), U8(1)), BlockPacking::c_rgtc1, U8(1), component_types(ComponentType::snorm, 1), swizzles_r(),    Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_RG_RGTC2:                 return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_rgtc2, U8(2), component_types(ComponentType::unorm, 2), swizzles_rg(),   Colorspace::bt709_linear_rgb, true);
      case GL_COMPRESSED_SIGNED_RG_RGTC2:          return ImageFormat(U8(16), Dim(U8(4), U8(4), U8(1)), BlockPacking::c_rgtc2, U8(2), component_types(ComponentType::snorm, 2), swizzles_rg(),   Colorspace::bt709_linear_rgb, true);

      case GL_DEPTH_COMPONENT:
      case GL_DEPTH_COMPONENT32:    return ImageFormat(U8(4), U8(1), BlockPacking::s_32, U8(1), component_types(ComponentType::unorm, 1), swizzles_rrr(), Colorspace::linear_depth, true);
      case GL_DEPTH_COMPONENT16:    return ImageFormat(U8(2), U8(1), BlockPacking::s_16, U8(1), component_types(ComponentType::unorm, 1), swizzles_rrr(), Colorspace::linear_depth, true);
      case GL_DEPTH_COMPONENT32F:   return ImageFormat(U8(4), U8(1), BlockPacking::s_32, U8(1), component_types(ComponentType::sfloat, 1), swizzles_rrr(), Colorspace::linear_depth, true);
      case GL_DEPTH_COMPONENT24:    return ImageFormat(U8(4), U8(1), BlockPacking::p_8_24, U8(1), component_types(ComponentType::none, ComponentType::unorm), swizzles(Swizzle::green, Swizzle::green, Swizzle::green), Colorspace::linear_depth, true);

      case GL_STENCIL_INDEX:
      case GL_STENCIL_INDEX8:       return ImageFormat(U8(1), U8(1), BlockPacking::s_8, U8(1), component_types(ComponentType::uint, 1), swizzles_rrr(), Colorspace::linear_stencil, true);

      case GL_DEPTH_STENCIL:
      case GL_DEPTH24_STENCIL8:     return ImageFormat(U8(4), U8(1), BlockPacking::p_24_8, U8(2), component_types(ComponentType::unorm, ComponentType::uint), swizzles_rg(), Colorspace::linear_depth_stencil, true);
      case GL_DEPTH32F_STENCIL8:    return ImageFormat(U8(8), U8(1), BlockPacking::s_32_p_24_8, U8(2), component_types(ComponentType::sfloat, ComponentType::none, ComponentType::uint), swizzles(Swizzle::red, Swizzle::blue), Colorspace::linear_depth_stencil, true);

      case GL_RED:
      case GL_R8:             return ImageFormat(U8(1), U8(1), BlockPacking::s_8,  1, component_types(ComponentType::unorm, 1),  swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16:            return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, component_types(ComponentType::unorm, 1),  swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R8_SNORM:       return ImageFormat(U8(1), U8(1), BlockPacking::s_8,  1, component_types(ComponentType::snorm, 1),  swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16_SNORM:      return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, component_types(ComponentType::snorm, 1),  swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R8UI:           return ImageFormat(U8(1), U8(1), BlockPacking::s_8,  1, component_types(ComponentType::uint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16UI:          return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, component_types(ComponentType::uint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R32UI:          return ImageFormat(U8(4), U8(1), BlockPacking::s_32, 1, component_types(ComponentType::uint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R8I:            return ImageFormat(U8(1), U8(1), BlockPacking::s_8,  1, component_types(ComponentType::sint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16I:           return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, component_types(ComponentType::sint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R32I:           return ImageFormat(U8(4), U8(1), BlockPacking::s_32, 1, component_types(ComponentType::sint, 1),   swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R16F:           return ImageFormat(U8(2), U8(1), BlockPacking::s_16, 1, component_types(ComponentType::sfloat, 1), swizzles_rrr(), Colorspace::bt709_linear_rgb, true);
      case GL_R32F:           return ImageFormat(U8(4), U8(1), BlockPacking::s_32, 1, component_types(ComponentType::sfloat, 1), swizzles_rrr(), Colorspace::bt709_linear_rgb, true);

      case GL_RG:
      case GL_RG8:            return ImageFormat(U8(2), U8(1), BlockPacking::s_8_8,   2, component_types(ComponentType::unorm, 2),  swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16:           return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, component_types(ComponentType::unorm, 2),  swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG8_SNORM:      return ImageFormat(U8(2), U8(1), BlockPacking::s_8_8,   2, component_types(ComponentType::snorm, 2),  swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16_SNORM:     return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, component_types(ComponentType::snorm, 2),  swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG8UI:          return ImageFormat(U8(2), U8(1), BlockPacking::s_8_8,   2, component_types(ComponentType::uint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16UI:         return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, component_types(ComponentType::uint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG32UI:         return ImageFormat(U8(8), U8(1), BlockPacking::s_32_32, 2, component_types(ComponentType::uint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG8I:           return ImageFormat(U8(2), U8(1), BlockPacking::s_8_8,   2, component_types(ComponentType::sint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16I:          return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, component_types(ComponentType::sint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG32I:          return ImageFormat(U8(8), U8(1), BlockPacking::s_32_32, 2, component_types(ComponentType::sint, 2),   swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG16F:          return ImageFormat(U8(4), U8(1), BlockPacking::s_16_16, 2, component_types(ComponentType::sfloat, 2), swizzles_rg(), Colorspace::bt709_linear_rgb, true);
      case GL_RG32F:          return ImageFormat(U8(8), U8(1), BlockPacking::s_32_32, 2, component_types(ComponentType::sfloat, 2), swizzles_rg(), Colorspace::bt709_linear_rgb, true);

      case GL_SRGB:
      case GL_SRGB8:          return ImageFormat(U8(3), U8(1), BlockPacking::s_8_8_8, 3, component_types(ComponentType::unorm, 3), swizzles_rgb(), Colorspace::srgb, true);
      
      case GL_RGB:
      case GL_RGB8:           return ImageFormat(U8(3), U8(1), BlockPacking::s_8_8_8, 3, component_types(ComponentType::unorm, 3), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);

      case GL_RGB16:          return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, component_types(ComponentType::unorm, 3),  swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_R3_G3_B2:       return ImageFormat(U8(1),  U8(1), BlockPacking::p_2_3_3,    3, component_types(ComponentType::unorm, 3),  swizzles_bgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB565:         return ImageFormat(U8(2),  U8(1), BlockPacking::p_5_6_5,    3, component_types(ComponentType::unorm, 3),  swizzles_bgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB4:           return ImageFormat(U8(2),  U8(1), BlockPacking::p_4_4_4_4,  3, component_types(ComponentType::none, ComponentType::unorm, ComponentType::unorm, ComponentType::unorm), swizzles_abg(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB5:           return ImageFormat(U8(2),  U8(1), BlockPacking::p_1_5_5_5,  3, component_types(ComponentType::none, ComponentType::unorm, ComponentType::unorm, ComponentType::unorm), swizzles_abg(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB8_SNORM:     return ImageFormat(U8(3),  U8(1), BlockPacking::s_8_8_8,    3, component_types(ComponentType::snorm, 3),  swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB16_SNORM:    return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, component_types(ComponentType::snorm, 3),  swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB8UI:         return ImageFormat(U8(3),  U8(1), BlockPacking::s_8_8_8,    3, component_types(ComponentType::uint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB16UI:        return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, component_types(ComponentType::uint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB32UI:        return ImageFormat(U8(12), U8(1), BlockPacking::s_32_32_32, 3, component_types(ComponentType::uint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB8I:          return ImageFormat(U8(3),  U8(1), BlockPacking::s_8_8_8,    3, component_types(ComponentType::sint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB16I:         return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, component_types(ComponentType::sint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB32I:         return ImageFormat(U8(12), U8(1), BlockPacking::s_32_32_32, 3, component_types(ComponentType::sint, 3),   swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_R11F_G11F_B10F: return ImageFormat(U8(4),  U8(1), BlockPacking::p_10_11_11, 3, component_types(ComponentType::ufloat, 3), swizzles_bgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB16F:         return ImageFormat(U8(6),  U8(1), BlockPacking::s_16_16_16, 3, component_types(ComponentType::sfloat, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB32F:         return ImageFormat(U8(12), U8(1), BlockPacking::s_32_32_32, 3, component_types(ComponentType::sfloat, 3), swizzles_rgb(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB9_E5:        return ImageFormat(U8(4),  U8(1), BlockPacking::p_5_9_9_9,  3, component_types(ComponentType::expo, ComponentType::ufloat, ComponentType::ufloat, ComponentType::ufloat), swizzles_abg(), Colorspace::bt709_linear_rgb, true);

      case GL_RGBA16:         return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, component_types(ComponentType::unorm, 4),  swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA4:          return ImageFormat(U8(2),  U8(1), BlockPacking::p_4_4_4_4,     4, component_types(ComponentType::unorm, 4),  swizzles_abgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB5_A1:        return ImageFormat(U8(2),  U8(1), BlockPacking::p_1_5_5_5,     4, component_types(ComponentType::unorm, 4),  swizzles_abgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB10_A2:       return ImageFormat(U8(4),  U8(1), BlockPacking::p_2_10_10_10,  4, component_types(ComponentType::unorm, 4),  swizzles_abgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA8_SNORM:    return ImageFormat(U8(4),  U8(1), BlockPacking::s_8_8_8_8,     4, component_types(ComponentType::snorm, 4),  swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA16_SNORM:   return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, component_types(ComponentType::snorm, 4),  swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA8UI:        return ImageFormat(U8(4),  U8(1), BlockPacking::s_8_8_8_8,     4, component_types(ComponentType::uint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA16UI:       return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, component_types(ComponentType::uint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA32UI:       return ImageFormat(U8(16), U8(1), BlockPacking::s_32_32_32_32, 4, component_types(ComponentType::uint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGB10_A2UI:     return ImageFormat(U8(4),  U8(1), BlockPacking::p_2_10_10_10,  4, component_types(ComponentType::uint, 4),   swizzles_abgr(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA8I:         return ImageFormat(U8(4),  U8(1), BlockPacking::s_8_8_8_8,     4, component_types(ComponentType::sint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA16I:        return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, component_types(ComponentType::sint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA32I:        return ImageFormat(U8(16), U8(1), BlockPacking::s_32_32_32_32, 4, component_types(ComponentType::sint, 4),   swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA16F:        return ImageFormat(U8(8),  U8(1), BlockPacking::s_16_16_16_16, 4, component_types(ComponentType::sfloat, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
      case GL_RGBA32F:        return ImageFormat(U8(18), U8(1), BlockPacking::s_32_32_32_32, 4, component_types(ComponentType::sfloat, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);

      case GL_SRGB_ALPHA:
      case GL_SRGB8_ALPHA8:   return ImageFormat(U8(4), U8(1), BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::srgb, true);

      case GL_RGBA:
      case GL_RGBA8:
      default:                return ImageFormat(U8(4), U8(1), BlockPacking::s_8_8_8_8, 4, component_types(ComponentType::unorm, 4), swizzles_rgba(), Colorspace::bt709_linear_rgb, true);
         
   }
}

} // be::gfx::tex
