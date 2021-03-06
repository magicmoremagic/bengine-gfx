#pragma once
#ifndef BE_GFX_TEX_MAKE_TEXTURE_HPP_
#define BE_GFX_TEX_MAKE_TEXTURE_HPP_

#include "texture.hpp"

namespace be::gfx::tex {

Texture make_lineal_texture(const ImageFormat& format,
                            I32 dim,
                            std::size_t levels = TextureStorage::max_levels,
                            Buf<UC> buf = Buf<UC>(),
                            TextureAlignment alignment = TextureAlignment());

Texture make_lineal_array_texture(const ImageFormat& format,
                                  I32 dim,
                                  std::size_t layers,
                                  std::size_t levels = TextureStorage::max_levels,
                                  Buf<UC> buf = Buf<UC>(),
                                  TextureAlignment alignment = TextureAlignment());

Texture make_planar_texture(const ImageFormat& format,
                            ivec2 dim,
                            std::size_t levels = TextureStorage::max_levels,
                            Buf<UC> buf = Buf<UC>(),
                            TextureAlignment alignment = TextureAlignment());

Texture make_planar_array_texture(const ImageFormat& format,
                                  ivec2 dim,
                                  std::size_t layers,
                                  std::size_t levels = TextureStorage::max_levels,
                                  Buf<UC> buf = Buf<UC>(),
                                  TextureAlignment alignment = TextureAlignment());

Texture make_volumetric_texture(const ImageFormat& format,
                                ivec3 dim,
                                std::size_t levels = TextureStorage::max_levels,
                                Buf<UC> buf = Buf<UC>(),
                                TextureAlignment alignment = TextureAlignment());

Texture make_directional_texture(const ImageFormat& format,
                                 ivec2 dim,
                                 std::size_t levels = TextureStorage::max_levels,
                                 Buf<UC> buf = Buf<UC>(),
                                 TextureAlignment alignment = TextureAlignment());

Texture make_directional_array_texture(const ImageFormat& format,
                                       ivec2 dim,
                                       std::size_t layers,
                                       std::size_t levels = TextureStorage::max_levels,
                                       Buf<UC> buf = Buf<UC>(),
                                       TextureAlignment alignment = TextureAlignment());

Texture make_texture(TextureClass tex_class,
                     const ImageFormat& format,
                     ivec3 dim,
                     std::size_t layers = 1u,
                     std::size_t levels = TextureStorage::max_levels,
                     Buf<UC> buf = Buf<UC>(),
                     TextureAlignment alignment = TextureAlignment());

std::size_t calculate_required_lineal_texture_size(const ImageFormat& format,
                                                   I32 dim,
                                                   std::size_t levels = TextureStorage::max_levels,
                                                   TextureAlignment alignment = TextureAlignment()) noexcept;

std::size_t calculate_required_lineal_array_texture_size(const ImageFormat& format,
                                                         I32 dim,
                                                         std::size_t layers,
                                                         std::size_t levels = TextureStorage::max_levels,
                                                         TextureAlignment alignment = TextureAlignment()) noexcept;

std::size_t calculate_required_planar_texture_size(const ImageFormat& format,
                                                   ivec2 dim,
                                                   std::size_t levels = TextureStorage::max_levels,
                                                   TextureAlignment alignment = TextureAlignment()) noexcept;

std::size_t calculate_required_planar_array_texture_size(const ImageFormat& format,
                                                         ivec2 dim,
                                                         std::size_t layers,
                                                         std::size_t levels = TextureStorage::max_levels,
                                                         TextureAlignment alignment = TextureAlignment()) noexcept;

std::size_t calculate_required_volumetric_texture_size(const ImageFormat& format,
                                                       ivec3 dim,
                                                       std::size_t levels = TextureStorage::max_levels,
                                                       TextureAlignment alignment = TextureAlignment()) noexcept;

std::size_t calculate_required_directional_texture_size(const ImageFormat& format,
                                                        ivec2 dim,
                                                        std::size_t levels = TextureStorage::max_levels,
                                                        TextureAlignment alignment = TextureAlignment()) noexcept;

std::size_t calculate_required_directional_array_texture_size(const ImageFormat& format,
                                                              ivec2 dim,
                                                              std::size_t layers,
                                                              std::size_t levels = TextureStorage::max_levels,
                                                              TextureAlignment alignment = TextureAlignment()) noexcept;

std::size_t calculate_required_texture_size(TextureClass tex_class,
                                            const ImageFormat& format,
                                            ivec3 dim, std::size_t layers = 1u,
                                            std::size_t levels = TextureStorage::max_levels,
                                            TextureAlignment alignment = TextureAlignment()) noexcept;

} // be::gfx::tex

#endif
