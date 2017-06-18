#pragma once
#ifndef BE_GFX_TEX_TEXTURE_ALIGNMENT_HPP_
#define BE_GFX_TEX_TEXTURE_ALIGNMENT_HPP_

#include "gfx_tex_autolink.hpp"
#include <be/core/be.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
class TextureAlignment {
public:
   static constexpr U8 max_alignment_bits = 20;

   TextureAlignment(U8 line_bits = 3u, U8 plane_bits = 0, U8 level_bits = 0, U8 face_bits = 0, U8 layer_bits = 0);

   std::size_t line() const  { return 1ull << line_bits_; }
   std::size_t plane() const { return 1ull << plane_bits_; }
   std::size_t level() const { return 1ull << level_bits_; }
   std::size_t face() const  { return 1ull << face_bits_; }
   std::size_t layer() const { return 1ull << layer_bits_; }

   U8 line_bits() const  { return line_bits_; }
   U8 plane_bits() const { return plane_bits_; }
   U8 level_bits() const { return level_bits_; }
   U8 face_bits() const  { return face_bits_; }
   U8 layer_bits() const { return layer_bits_; }

   void line_bits(U8 bits);
   void plane_bits(U8 bits);   
   void level_bits(U8 bits);
   void face_bits(U8 bits);
   void layer_bits(U8 bits);

   bool operator==(const TextureAlignment& other) const;
   bool operator!=(const TextureAlignment& other) const;

private:
   U8 line_bits_;
   U8 plane_bits_;
   U8 level_bits_;
   U8 face_bits_;
   U8 layer_bits_;
};

} // be::gfx::tex

#endif
