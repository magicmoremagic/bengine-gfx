#include "tex/pch.hpp"
#include "tex/texture_alignment.hpp"

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
TextureAlignment::TextureAlignment(U8 line_bits, U8 plane_bits, U8 level_bits, U8 face_bits, U8 layer_bits)
   : line_bits_(std::max(U8(1), line_bits)),
     plane_bits_(plane_bits),
     level_bits_(level_bits),
     face_bits_(face_bits),
     layer_bits_(layer_bits) {

   if (line_bits_ > plane_bits_) {
      plane_bits_ = line_bits_;
   }
   if (plane_bits_ > level_bits_) {
      level_bits_ = plane_bits_;
   }
   if (level_bits_ > face_bits_) {
      face_bits_ = level_bits_;
   }
   if (face_bits_ > layer_bits_) {
      layer_bits_ = face_bits_;
   }
}

///////////////////////////////////////////////////////////////////////////////
void TextureAlignment::line_bits(U8 bits) {
   line_bits_ = std::max(U8(1), bits);

   if (line_bits_ > plane_bits_) {
      plane_bits_ = line_bits_;
      if (plane_bits_ > level_bits_) {
         level_bits_ = plane_bits_;
         if (level_bits_ > face_bits_) {
            face_bits_ = level_bits_;
            if (face_bits_ > layer_bits_) {
               layer_bits_ = face_bits_;
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
void TextureAlignment::plane_bits(U8 bits) {
   plane_bits_ = std::max(U8(1), bits);

   if (line_bits_ > plane_bits_) {
      line_bits_ = plane_bits_;
   }
   if (plane_bits_ > level_bits_) {
      level_bits_ = plane_bits_;
      if (level_bits_ > face_bits_) {
         face_bits_ = level_bits_;
         if (face_bits_ > layer_bits_) {
            layer_bits_ = face_bits_;
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
void TextureAlignment::level_bits(U8 bits) {
   level_bits_ = std::max(U8(1), bits);

   if (plane_bits_ > level_bits_) {
      plane_bits_ = level_bits_;
      if (line_bits_ > plane_bits_) {
         line_bits_ = plane_bits_;
      }
   }
   
   if (level_bits_ > face_bits_) {
      face_bits_ = level_bits_;
      if (face_bits_ > layer_bits_) {
         layer_bits_ = face_bits_;
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
void TextureAlignment::face_bits(U8 bits) {
   face_bits_ = std::max(U8(1), bits);

   if (level_bits_ > face_bits_) {
      level_bits_ = face_bits_;
      if (plane_bits_ > level_bits_) {
         plane_bits_ = level_bits_;
         if (line_bits_ > plane_bits_) {
            line_bits_ = plane_bits_;
         }
      }
   }
   
   if (face_bits_ > layer_bits_) {
      layer_bits_ = face_bits_;
   }
}

///////////////////////////////////////////////////////////////////////////////
void TextureAlignment::layer_bits(U8 bits) {
   layer_bits_ = std::max(U8(1), bits);

   if (face_bits_ > layer_bits_) {
      face_bits_ = layer_bits_;
      if (level_bits_ > face_bits_) {
         level_bits_ = face_bits_;
         if (plane_bits_ > level_bits_) {
            plane_bits_ = level_bits_;
            if (line_bits_ > plane_bits_) {
               line_bits_ = plane_bits_;
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
bool TextureAlignment::operator==(const TextureAlignment& other) const {
   return line_bits_ == other.line_bits_ &&
      plane_bits_ == other.plane_bits_ &&
      level_bits_ == other.level_bits_ &&
      face_bits_ == other.face_bits_ &&
      layer_bits_ == other.layer_bits_;
}

///////////////////////////////////////////////////////////////////////////////
bool TextureAlignment::operator!=(const TextureAlignment& other) const {
   return !(*this == other);
}

} // be::gfx::tex
