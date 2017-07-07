#pragma once
#ifndef BE_GFX_TEX_LOG_TEXTURE_INFO_HPP_
#define BE_GFX_TEX_LOG_TEXTURE_INFO_HPP_

#include "texture_view.hpp"
#include "texture_file_format.hpp"
#include <be/core/log.hpp>
#include <be/core/service_log.hpp>
#include <be/core/filesystem.hpp>

namespace be::gfx::tex {

void log_texture_info(const ConstTextureView& view, S msg,
                      v::Verbosity verbosity = v::info, Log& log = default_log());

void log_texture_info(const ConstTextureView& view, S msg,
                      Path path, TextureFileFormat format = TextureFileFormat::unknown,
                      v::Verbosity verbosity = v::info, Log& log = default_log());

} // be::gfx::tex

#endif
