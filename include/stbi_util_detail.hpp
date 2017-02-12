#pragma once
#ifndef BE_TEXI_STBI_UTIL_DETAIL_HPP_
#define BE_TEXI_STBI_UTIL_DETAIL_HPP_

#include <gli/format.hpp>

namespace be {
namespace texi {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
gli::format get_stbi_format(int channels, int bpc);
gli::format get_stbi_format_8(int channels);
gli::format get_stbi_format_16(int channels);
gli::format get_stbi_format_32(int channels);

///////////////////////////////////////////////////////////////////////////////
int get_stbi_format_channels(gli::format format, int bpc);
int get_stbi_format_8_channels(gli::format format);
int get_stbi_format_16_channels(gli::format format);
int get_stbi_format_32_channels(gli::format format);

} // be::texi::detail
} // be::texi
} // be

#endif
