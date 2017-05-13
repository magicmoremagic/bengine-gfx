#pragma once
#ifndef BE_GFX_TEX_IMAGE_FORMAT_GL_HPP_
#define BE_GFX_TEX_IMAGE_FORMAT_GL_HPP_

#include "image_format.hpp"
#include <be/gfx/glbinding.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
struct ImageFormatGl {
   gl::GLenum internal_format;
   gl::GLenum data_format;
   gl::GLenum data_type;
   gl::GLenum swizzle[4];
};

///////////////////////////////////////////////////////////////////////////////
ImageFormatGl gl_format(ImageFormat format);

///////////////////////////////////////////////////////////////////////////////
ImageFormat canonical_format(gl::GLenum internal_format);

///////////////////////////////////////////////////////////////////////////////
ImageFormat preferred_format(gl::GLenum target, gl::GLenum internal_format);

} // be::gfx::tex

#endif