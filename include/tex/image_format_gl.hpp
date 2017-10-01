#pragma once
#ifndef BE_GFX_TEX_IMAGE_FORMAT_GL_HPP_
#define BE_GFX_TEX_IMAGE_FORMAT_GL_HPP_

#include "image_format.hpp"
#include <be/gfx/bgl.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
struct ImageFormatGl {
   gl::GLenum base_internal_format;
   gl::GLenum internal_format;
   gl::GLenum data_format;
   gl::GLenum data_type;
   gl::GLenum swizzle[4];
};

///////////////////////////////////////////////////////////////////////////////
ImageFormatGl to_gl_format(ImageFormat format);
ImageFormatGl to_gl_format(ImageFormat format, std::error_code& ec) noexcept;

///////////////////////////////////////////////////////////////////////////////
ImageFormat from_gl_format(ImageFormatGl format);
ImageFormat from_gl_format(ImageFormatGl format, std::error_code& ec) noexcept;

///////////////////////////////////////////////////////////////////////////////
ImageFormat canonical_format(gl::GLenum internal_format);
ImageFormat canonical_format(gl::GLenum internal_format, std::error_code& ec) noexcept;

///////////////////////////////////////////////////////////////////////////////
ImageFormat preferred_format(gl::GLenum target, gl::GLenum internal_format);
ImageFormat preferred_format(gl::GLenum target, gl::GLenum internal_format, std::error_code& ec) noexcept;

} // be::gfx::tex

#endif
