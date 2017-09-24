/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
#pragma once
#ifndef BE_GFX_BGL_HPP_
#define BE_GFX_BGL_HPP_

//#bgl stop

/*
This file includes excerpts from the combined OpenGL XML registry:

   Copyright (c) 2013-2017 The Khronos Group Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   ------------------------------------------------------------------------

   This file, gl.xml, is the OpenGL and OpenGL API Registry. The canonical
   version of the registry, together with documentation, schema, and Python
   generator scripts used to generate C header files for OpenGL and OpenGL ES,
   can always be found in the Khronos Registry at
           https://github.com/KhronosGroup/OpenGL-Registry

*/

#if defined(__gl_h_)
#error Do not include gl.h before bgl.hpp
#elif defined(__GL_H__)
#error Do not include gl.h before bgl.hpp
#elif defined(_GL_H)
#error Do not include gl.h before bgl.hpp
#elif defined(__X_GL_H)
#error Do not include gl.h before bgl.hpp
#elif defined(__gl2_h_)
#error Do not include gl2.h before bgl.hpp
#elif defined(__gltypes_h_)
#error Do not include gltypes.h before bgl.hpp
#elif defined(__glext_h_) || defined(__GLEXT_H_)
#error Do not include glext.h before bgl.hpp
#endif
#define __gl_h_
#define __gl2_h_
#define __GL_H__
#define _GL_H
#define __gltypes_h_
#define __X_GL_H
#define __glext_h_
#define __GLEXT_H_

#ifndef GLAPIENTRY
#ifndef APIENTRY
#ifdef _WIN32
#define APIENTRY __stdcall
#else
#define APIENTRY
#endif
#define BE_GFX_BGL_APIENTRY_DEFINED
#endif
#define GLAPIENTRY APIENTRY
#endif

#include <be/core/be.hpp>

namespace be::gfx::gl {

////////// TYPES /////////////////////////////////////////////////////////////

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef void GLvoid; // Not an actual GL type, though used in headers in the past
typedef int GLint;
typedef unsigned char GLubyte;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLclampd;
typedef char GLchar;
typedef unsigned short GLhalf;
typedef void (GLAPIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);

////////// BGL ///////////////////////////////////////////////////////////////

struct BglContext;

class BglContextHandle final {
   friend struct BglContext;
   struct deleter {
      void operator()(BglContext* ptr);
   };
public:
   BglContextHandle() = default;
   const BglContext* get() const noexcept;
   BglContext* get() noexcept;
private:
   BglContextHandle(BglContext* ptr);
   std::unique_ptr<BglContext, deleter> ptr_;
};

BglContextHandle init_context();
void switch_context(const BglContextHandle& context) noexcept;
const char* enum_name (GLenum e) noexcept;

////////// FEATURES //////////////////////////////////////////////////////////

#define GL_VERSION_1_0 (::be::gfx::gl::gl10())
#define GL_VERSION_1_1 (::be::gfx::gl::gl11())
#define GL_VERSION_1_2 (::be::gfx::gl::gl12())
#define GL_VERSION_1_3 (::be::gfx::gl::gl13())
#define GL_VERSION_1_4 (::be::gfx::gl::gl14())
#define GL_VERSION_1_5 (::be::gfx::gl::gl15())
#define GL_VERSION_2_0 (::be::gfx::gl::gl20())
#define GL_VERSION_2_1 (::be::gfx::gl::gl21())
#define GL_VERSION_3_0 (::be::gfx::gl::gl30())
#define GL_VERSION_3_1 (::be::gfx::gl::gl31())
#define GL_VERSION_3_2 (::be::gfx::gl::gl32())
#define GL_VERSION_3_3 (::be::gfx::gl::gl33())

bool gl10() noexcept;
bool gl11() noexcept;
bool gl12() noexcept;
bool gl13() noexcept;
bool gl14() noexcept;
bool gl15() noexcept;
bool gl20() noexcept;
bool gl21() noexcept;
bool gl30() noexcept;
bool gl31() noexcept;
bool gl32() noexcept;
bool gl33() noexcept;

////////// EXTENSIONS ////////////////////////////////////////////////////////

#define GL_KHR_debug (::be::gfx::gl::khr_debug())

bool khr_debug() noexcept;

////////// ENUM GROUPS ///////////////////////////////////////////////////////

namespace ClearBufferMask {
enum ClearBufferMask {
   depth_buffer_bit      = 0x00000100, // GL 1.0
   accum_buffer_bit      = 0x00000200, // GL 1.0
   stencil_buffer_bit    = 0x00000400, // GL 1.0
   color_buffer_bit      = 0x00004000, // GL 1.0
};
} // ClearBufferMask

namespace PrimitiveType {
enum PrimitiveType {
   points                      = 0x0000, // GL 1.0
   lines                       = 0x0001, // GL 1.0
   line_loop                   = 0x0002, // GL 1.0
   line_strip                  = 0x0003, // GL 1.0
   triangles                   = 0x0004, // GL 1.0, ARB_tessellation_shader, EXT_tessellation_shader, OES_tessellation_shader
   triangle_strip              = 0x0005, // GL 1.0
   triangle_fan                = 0x0006, // GL 1.0
   quads                       = 0x0007, // GL 1.0, GL 4.0, ARB_tessellation_shader
   quad_strip                  = 0x0008, // GL 1.0
   polygon                     = 0x0009, // GL 1.0
   lines_adjacency             = 0x000A, // GL 3.2
   line_strip_adjacency        = 0x000B, // GL 3.2
   triangles_adjacency         = 0x000C, // GL 3.2
   triangle_strip_adjacency    = 0x000D, // GL 3.2
};
} // PrimitiveType

namespace GetPName {
enum GetPName {
   current_color                    = 0x0B00, // GL 1.0
   current_index                    = 0x0B01, // GL 1.0
   current_normal                   = 0x0B02, // GL 1.0
   current_texture_coords           = 0x0B03, // GL 1.0
   current_raster_color             = 0x0B04, // GL 1.0
   current_raster_index             = 0x0B05, // GL 1.0
   current_raster_texture_coords    = 0x0B06, // GL 1.0
   current_raster_position          = 0x0B07, // GL 1.0
   current_raster_position_valid    = 0x0B08, // GL 1.0
   current_raster_distance          = 0x0B09, // GL 1.0
   point_smooth                     = 0x0B10, // GL 1.0
   point_size                       = 0x0B11, // GL 1.0
   point_size_range                 = 0x0B12, // GL 1.0
   smooth_point_size_range          = 0x0B12, // Aliases GL_POINT_SIZE_RANGE // GL 1.2
   point_size_granularity           = 0x0B13, // GL 1.0
   smooth_point_size_granularity    = 0x0B13, // Aliases GL_POINT_SIZE_GRANULARITY // GL 1.2
   line_smooth                      = 0x0B20, // GL 1.0
   line_width                       = 0x0B21, // GL 1.0
   line_width_range                 = 0x0B22, // GL 1.0
   smooth_line_width_range          = 0x0B22, // Aliases GL_LINE_WIDTH_RANGE // GL 1.2
   line_width_granularity           = 0x0B23, // GL 1.0
   smooth_line_width_granularity    = 0x0B23, // Aliases GL_LINE_WIDTH_GRANULARITY // GL 1.2
   line_stipple                     = 0x0B24, // GL 1.0
   line_stipple_pattern             = 0x0B25, // GL 1.0
   line_stipple_repeat              = 0x0B26, // GL 1.0
   list_mode                        = 0x0B30, // GL 1.0
   max_list_nesting                 = 0x0B31, // GL 1.0
   list_base                        = 0x0B32, // GL 1.0
   list_index                       = 0x0B33, // GL 1.0
   polygon_mode                     = 0x0B40, // GL 1.0
   polygon_smooth                   = 0x0B41, // GL 1.0
   polygon_stipple                  = 0x0B42, // GL 1.0
   edge_flag                        = 0x0B43, // GL 1.0
   cull_face                        = 0x0B44, // GL 1.0
   cull_face_mode                   = 0x0B45, // GL 1.0
   front_face                       = 0x0B46, // GL 1.0
   lighting                         = 0x0B50, // GL 1.0
   light_model_local_viewer         = 0x0B51, // GL 1.0
   light_model_two_side             = 0x0B52, // GL 1.0
   light_model_ambient              = 0x0B53, // GL 1.0
   shade_model                      = 0x0B54, // GL 1.0
   color_material_face              = 0x0B55, // GL 1.0
   color_material_parameter         = 0x0B56, // GL 1.0
   color_material                   = 0x0B57, // GL 1.0
   fog                              = 0x0B60, // GL 1.0, NV_register_combiners
   fog_index                        = 0x0B61, // GL 1.0
   fog_density                      = 0x0B62, // GL 1.0
   fog_start                        = 0x0B63, // GL 1.0
   fog_end                          = 0x0B64, // GL 1.0
   fog_mode                         = 0x0B65, // GL 1.0
   fog_color                        = 0x0B66, // GL 1.0
   depth_range                      = 0x0B70, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   depth_test                       = 0x0B71, // GL 1.0
   depth_writemask                  = 0x0B72, // GL 1.0
   depth_clear_value                = 0x0B73, // GL 1.0
   depth_func                       = 0x0B74, // GL 1.0
   accum_clear_value                = 0x0B80, // GL 1.0
   stencil_test                     = 0x0B90, // GL 1.0
   stencil_clear_value              = 0x0B91, // GL 1.0
   stencil_func                     = 0x0B92, // GL 1.0
   stencil_value_mask               = 0x0B93, // GL 1.0
   stencil_fail                     = 0x0B94, // GL 1.0
   stencil_pass_depth_fail          = 0x0B95, // GL 1.0
   stencil_pass_depth_pass          = 0x0B96, // GL 1.0
   stencil_ref                      = 0x0B97, // GL 1.0
   stencil_writemask                = 0x0B98, // GL 1.0
   matrix_mode                      = 0x0BA0, // GL 1.0
   normalize                        = 0x0BA1, // GL 1.0
   viewport                         = 0x0BA2, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   modelview_stack_depth            = 0x0BA3, // GL 1.0
   projection_stack_depth           = 0x0BA4, // GL 1.0
   texture_stack_depth              = 0x0BA5, // GL 1.0
   modelview_matrix                 = 0x0BA6, // GL 1.0
   projection_matrix                = 0x0BA7, // GL 1.0
   texture_matrix                   = 0x0BA8, // GL 1.0
   attrib_stack_depth               = 0x0BB0, // GL 1.0
   client_attrib_stack_depth        = 0x0BB1, // GL 1.1
   alpha_test                       = 0x0BC0, // GL 1.0
   alpha_test_func                  = 0x0BC1, // GL 1.0
   alpha_test_ref                   = 0x0BC2, // GL 1.0
   dither                           = 0x0BD0, // GL 1.0
   blend_dst                        = 0x0BE0, // GL 1.0
   blend_src                        = 0x0BE1, // GL 1.0
   blend                            = 0x0BE2, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   logic_op_mode                    = 0x0BF0, // GL 1.0
   index_logic_op                   = 0x0BF1, // GL 1.1
   logic_op                         = 0x0BF1, // GL 1.0
   color_logic_op                   = 0x0BF2, // GL 1.1
   aux_buffers                      = 0x0C00, // GL 1.0
   draw_buffer                      = 0x0C01, // GL 1.0
   read_buffer                      = 0x0C02, // GL 1.0
   scissor_box                      = 0x0C10, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   scissor_test                     = 0x0C11, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   index_clear_value                = 0x0C20, // GL 1.0
   index_writemask                  = 0x0C21, // GL 1.0
   color_clear_value                = 0x0C22, // GL 1.0
   color_writemask                  = 0x0C23, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   index_mode                       = 0x0C30, // GL 1.0
   rgba_mode                        = 0x0C31, // GL 1.0
   doublebuffer                     = 0x0C32, // GL 1.0
   stereo                           = 0x0C33, // GL 1.0
   render_mode                      = 0x0C40, // GL 1.0
   perspective_correction_hint      = 0x0C50, // GL 1.0
   point_smooth_hint                = 0x0C51, // GL 1.0
   line_smooth_hint                 = 0x0C52, // GL 1.0
   polygon_smooth_hint              = 0x0C53, // GL 1.0
   fog_hint                         = 0x0C54, // GL 1.0
   texture_gen_s                    = 0x0C60, // GL 1.0
   texture_gen_t                    = 0x0C61, // GL 1.0
   texture_gen_r                    = 0x0C62, // GL 1.0
   texture_gen_q                    = 0x0C63, // GL 1.0
   pixel_map_i_to_i_size            = 0x0CB0, // GL 1.0
   pixel_map_s_to_s_size            = 0x0CB1, // GL 1.0
   pixel_map_i_to_r_size            = 0x0CB2, // GL 1.0
   pixel_map_i_to_g_size            = 0x0CB3, // GL 1.0
   pixel_map_i_to_b_size            = 0x0CB4, // GL 1.0
   pixel_map_i_to_a_size            = 0x0CB5, // GL 1.0
   pixel_map_r_to_r_size            = 0x0CB6, // GL 1.0
   pixel_map_g_to_g_size            = 0x0CB7, // GL 1.0
   pixel_map_b_to_b_size            = 0x0CB8, // GL 1.0
   pixel_map_a_to_a_size            = 0x0CB9, // GL 1.0
   unpack_swap_bytes                = 0x0CF0, // GL 1.0
   unpack_lsb_first                 = 0x0CF1, // GL 1.0
   unpack_row_length                = 0x0CF2, // GL 1.0
   unpack_skip_rows                 = 0x0CF3, // GL 1.0
   unpack_skip_pixels               = 0x0CF4, // GL 1.0
   unpack_alignment                 = 0x0CF5, // GL 1.0
   pack_swap_bytes                  = 0x0D00, // GL 1.0
   pack_lsb_first                   = 0x0D01, // GL 1.0
   pack_row_length                  = 0x0D02, // GL 1.0
   pack_skip_rows                   = 0x0D03, // GL 1.0
   pack_skip_pixels                 = 0x0D04, // GL 1.0
   pack_alignment                   = 0x0D05, // GL 1.0
   map_color                        = 0x0D10, // GL 1.0
   map_stencil                      = 0x0D11, // GL 1.0
   index_shift                      = 0x0D12, // GL 1.0
   index_offset                     = 0x0D13, // GL 1.0
   red_scale                        = 0x0D14, // GL 1.0
   red_bias                         = 0x0D15, // GL 1.0
   zoom_x                           = 0x0D16, // GL 1.0
   zoom_y                           = 0x0D17, // GL 1.0
   green_scale                      = 0x0D18, // GL 1.0
   green_bias                       = 0x0D19, // GL 1.0
   blue_scale                       = 0x0D1A, // GL 1.0
   blue_bias                        = 0x0D1B, // GL 1.0
   alpha_scale                      = 0x0D1C, // GL 1.0
   alpha_bias                       = 0x0D1D, // GL 1.0
   depth_scale                      = 0x0D1E, // GL 1.0
   depth_bias                       = 0x0D1F, // GL 1.0
   max_eval_order                   = 0x0D30, // GL 1.0
   max_lights                       = 0x0D31, // GL 1.0
   max_clip_planes                  = 0x0D32, // GL 1.0
   max_clip_distances               = 0x0D32, // Aliases GL_MAX_CLIP_PLANES // GL 3.0
   max_texture_size                 = 0x0D33, // GL 1.0
   max_pixel_map_table              = 0x0D34, // GL 1.0
   max_attrib_stack_depth           = 0x0D35, // GL 1.0
   max_modelview_stack_depth        = 0x0D36, // GL 1.0
   max_name_stack_depth             = 0x0D37, // GL 1.0
   max_projection_stack_depth       = 0x0D38, // GL 1.0
   max_texture_stack_depth          = 0x0D39, // GL 1.0
   max_viewport_dims                = 0x0D3A, // GL 1.0
   max_client_attrib_stack_depth    = 0x0D3B, // GL 1.1
   subpixel_bits                    = 0x0D50, // GL 1.0
   index_bits                       = 0x0D51, // GL 1.0
   red_bits                         = 0x0D52, // GL 1.0
   green_bits                       = 0x0D53, // GL 1.0
   blue_bits                        = 0x0D54, // GL 1.0
   alpha_bits                       = 0x0D55, // GL 1.0
   depth_bits                       = 0x0D56, // GL 1.0
   stencil_bits                     = 0x0D57, // GL 1.0
   accum_red_bits                   = 0x0D58, // GL 1.0
   accum_green_bits                 = 0x0D59, // GL 1.0
   accum_blue_bits                  = 0x0D5A, // GL 1.0
   accum_alpha_bits                 = 0x0D5B, // GL 1.0
   name_stack_depth                 = 0x0D70, // GL 1.0
   auto_normal                      = 0x0D80, // GL 1.0
   map1_color_4                     = 0x0D90, // GL 1.0
   map1_index                       = 0x0D91, // GL 1.0
   map1_normal                      = 0x0D92, // GL 1.0
   map1_texture_coord_1             = 0x0D93, // GL 1.0
   map1_texture_coord_2             = 0x0D94, // GL 1.0
   map1_texture_coord_3             = 0x0D95, // GL 1.0
   map1_texture_coord_4             = 0x0D96, // GL 1.0
   map1_vertex_3                    = 0x0D97, // GL 1.0
   map1_vertex_4                    = 0x0D98, // GL 1.0
   map2_color_4                     = 0x0DB0, // GL 1.0
   map2_index                       = 0x0DB1, // GL 1.0
   map2_normal                      = 0x0DB2, // GL 1.0
   map2_texture_coord_1             = 0x0DB3, // GL 1.0
   map2_texture_coord_2             = 0x0DB4, // GL 1.0
   map2_texture_coord_3             = 0x0DB5, // GL 1.0
   map2_texture_coord_4             = 0x0DB6, // GL 1.0
   map2_vertex_3                    = 0x0DB7, // GL 1.0
   map2_vertex_4                    = 0x0DB8, // GL 1.0
   map1_grid_domain                 = 0x0DD0, // GL 1.0
   map1_grid_segments               = 0x0DD1, // GL 1.0
   map2_grid_domain                 = 0x0DD2, // GL 1.0
   map2_grid_segments               = 0x0DD3, // GL 1.0
   texture_1d                       = 0x0DE0, // GL 1.0, ARB_internalformat_query2
   texture_2d                       = 0x0DE1, // GL 1.0, ARB_internalformat_query2, EXT_sparse_texture
   feedback_buffer_size             = 0x0DF1, // GL 1.1
   feedback_buffer_type             = 0x0DF2, // GL 1.1
   selection_buffer_size            = 0x0DF4, // GL 1.1
   polygon_offset_units             = 0x2A00, // GL 1.1
   polygon_offset_point             = 0x2A01, // GL 1.1
   polygon_offset_line              = 0x2A02, // GL 1.1
   clip_plane0                      = 0x3000, // GL 1.0
   clip_plane1                      = 0x3001, // GL 1.0
   clip_plane2                      = 0x3002, // GL 1.0
   clip_plane3                      = 0x3003, // GL 1.0
   clip_plane4                      = 0x3004, // GL 1.0
   clip_plane5                      = 0x3005, // GL 1.0
   light0                           = 0x4000, // GL 1.0
   light1                           = 0x4001, // GL 1.0
   light2                           = 0x4002, // GL 1.0
   light3                           = 0x4003, // GL 1.0
   light4                           = 0x4004, // GL 1.0
   light5                           = 0x4005, // GL 1.0
   light6                           = 0x4006, // GL 1.0
   light7                           = 0x4007, // GL 1.0
   polygon_offset_fill              = 0x8037, // GL 1.1
   polygon_offset_factor            = 0x8038, // GL 1.1
   texture_binding_1d               = 0x8068, // GL 1.1, GL 4.5, ARB_direct_state_access
   texture_binding_2d               = 0x8069, // GL 1.1, GL 4.5, ARB_direct_state_access
   texture_binding_3d               = 0x806A, // GL 1.2, GL 4.5, ARB_direct_state_access
   vertex_array                     = 0x8074, // GL 1.1, GL 4.3, KHR_debug
   normal_array                     = 0x8075, // GL 1.1
   color_array                      = 0x8076, // GL 1.1
   index_array                      = 0x8077, // GL 1.1
   texture_coord_array              = 0x8078, // GL 1.1
   edge_flag_array                  = 0x8079, // GL 1.1
   vertex_array_size                = 0x807A, // GL 1.1
   vertex_array_type                = 0x807B, // GL 1.1
   vertex_array_stride              = 0x807C, // GL 1.1
   normal_array_type                = 0x807E, // GL 1.1
   normal_array_stride              = 0x807F, // GL 1.1
   color_array_size                 = 0x8081, // GL 1.1
   color_array_type                 = 0x8082, // GL 1.1
   color_array_stride               = 0x8083, // GL 1.1
   index_array_type                 = 0x8085, // GL 1.1
   index_array_stride               = 0x8086, // GL 1.1
   texture_coord_array_size         = 0x8088, // GL 1.1
   texture_coord_array_type         = 0x8089, // GL 1.1
   texture_coord_array_stride       = 0x808A, // GL 1.1
   edge_flag_array_stride           = 0x808C, // GL 1.1
   light_model_color_control        = 0x81F8, // GL 1.2
   aliased_point_size_range         = 0x846D, // GL 1.2
   aliased_line_width_range         = 0x846E, // GL 1.2
};
} // GetPName

namespace EnableCap {
enum EnableCap {
   point_smooth            = 0x0B10, // GL 1.0
   line_smooth             = 0x0B20, // GL 1.0
   line_stipple            = 0x0B24, // GL 1.0
   polygon_smooth          = 0x0B41, // GL 1.0
   polygon_stipple         = 0x0B42, // GL 1.0
   cull_face               = 0x0B44, // GL 1.0
   lighting                = 0x0B50, // GL 1.0
   color_material          = 0x0B57, // GL 1.0
   fog                     = 0x0B60, // GL 1.0, NV_register_combiners
   depth_test              = 0x0B71, // GL 1.0
   stencil_test            = 0x0B90, // GL 1.0
   normalize               = 0x0BA1, // GL 1.0
   alpha_test              = 0x0BC0, // GL 1.0
   dither                  = 0x0BD0, // GL 1.0
   blend                   = 0x0BE2, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   index_logic_op          = 0x0BF1, // GL 1.1
   color_logic_op          = 0x0BF2, // GL 1.1
   scissor_test            = 0x0C11, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   texture_gen_s           = 0x0C60, // GL 1.0
   texture_gen_t           = 0x0C61, // GL 1.0
   texture_gen_r           = 0x0C62, // GL 1.0
   texture_gen_q           = 0x0C63, // GL 1.0
   auto_normal             = 0x0D80, // GL 1.0
   map1_color_4            = 0x0D90, // GL 1.0
   map1_index              = 0x0D91, // GL 1.0
   map1_normal             = 0x0D92, // GL 1.0
   map1_texture_coord_1    = 0x0D93, // GL 1.0
   map1_texture_coord_2    = 0x0D94, // GL 1.0
   map1_texture_coord_3    = 0x0D95, // GL 1.0
   map1_texture_coord_4    = 0x0D96, // GL 1.0
   map1_vertex_3           = 0x0D97, // GL 1.0
   map1_vertex_4           = 0x0D98, // GL 1.0
   map2_color_4            = 0x0DB0, // GL 1.0
   map2_index              = 0x0DB1, // GL 1.0
   map2_normal             = 0x0DB2, // GL 1.0
   map2_texture_coord_1    = 0x0DB3, // GL 1.0
   map2_texture_coord_2    = 0x0DB4, // GL 1.0
   map2_texture_coord_3    = 0x0DB5, // GL 1.0
   map2_texture_coord_4    = 0x0DB6, // GL 1.0
   map2_vertex_3           = 0x0DB7, // GL 1.0
   map2_vertex_4           = 0x0DB8, // GL 1.0
   texture_1d              = 0x0DE0, // GL 1.0, ARB_internalformat_query2
   texture_2d              = 0x0DE1, // GL 1.0, ARB_internalformat_query2, EXT_sparse_texture
   polygon_offset_point    = 0x2A01, // GL 1.1
   polygon_offset_line     = 0x2A02, // GL 1.1
   clip_plane0             = 0x3000, // GL 1.0
   clip_plane1             = 0x3001, // GL 1.0
   clip_plane2             = 0x3002, // GL 1.0
   clip_plane3             = 0x3003, // GL 1.0
   clip_plane4             = 0x3004, // GL 1.0
   clip_plane5             = 0x3005, // GL 1.0
   light0                  = 0x4000, // GL 1.0
   light1                  = 0x4001, // GL 1.0
   light2                  = 0x4002, // GL 1.0
   light3                  = 0x4003, // GL 1.0
   light4                  = 0x4004, // GL 1.0
   light5                  = 0x4005, // GL 1.0
   light6                  = 0x4006, // GL 1.0
   light7                  = 0x4007, // GL 1.0
   polygon_offset_fill     = 0x8037, // GL 1.1
   vertex_array            = 0x8074, // GL 1.1, GL 4.3, KHR_debug
   normal_array            = 0x8075, // GL 1.1
   color_array             = 0x8076, // GL 1.1
   index_array             = 0x8077, // GL 1.1
   texture_coord_array     = 0x8078, // GL 1.1
   edge_flag_array         = 0x8079, // GL 1.1
};
} // EnableCap

namespace PixelStoreParameter {
enum PixelStoreParameter {
   unpack_swap_bytes      = 0x0CF0, // GL 1.0
   unpack_lsb_first       = 0x0CF1, // GL 1.0
   unpack_row_length      = 0x0CF2, // GL 1.0
   unpack_skip_rows       = 0x0CF3, // GL 1.0
   unpack_skip_pixels     = 0x0CF4, // GL 1.0
   unpack_alignment       = 0x0CF5, // GL 1.0
   pack_swap_bytes        = 0x0D00, // GL 1.0
   pack_lsb_first         = 0x0D01, // GL 1.0
   pack_row_length        = 0x0D02, // GL 1.0
   pack_skip_rows         = 0x0D03, // GL 1.0
   pack_skip_pixels       = 0x0D04, // GL 1.0
   pack_alignment         = 0x0D05, // GL 1.0
   pack_skip_images       = 0x806B, // GL 1.2
   pack_image_height      = 0x806C, // GL 1.2
   unpack_skip_images     = 0x806D, // GL 1.2
   unpack_image_height    = 0x806E, // GL 1.2
};
} // PixelStoreParameter

namespace TextureTarget {
enum TextureTarget {
   texture_1d                            = 0x0DE0, // GL 1.0, ARB_internalformat_query2
   texture_2d                            = 0x0DE1, // GL 1.0, ARB_internalformat_query2, EXT_sparse_texture
   proxy_texture_1d                      = 0x8063, // GL 1.1
   proxy_texture_2d                      = 0x8064, // GL 1.1
   texture_3d                            = 0x806F, // GL 1.2, ARB_internalformat_query2, EXT_sparse_texture
   proxy_texture_3d                      = 0x8070, // GL 1.2
   texture_rectangle                     = 0x84F5, // GL 3.1, ARB_internalformat_query2
   proxy_texture_rectangle               = 0x84F7, // GL 3.1
   texture_cube_map                      = 0x8513, // GL 1.3, ARB_internalformat_query2, EXT_sparse_texture
   texture_cube_map_positive_x           = 0x8515, // GL 1.3
   texture_cube_map_negative_x           = 0x8516, // GL 1.3
   texture_cube_map_positive_y           = 0x8517, // GL 1.3
   texture_cube_map_negative_y           = 0x8518, // GL 1.3
   texture_cube_map_positive_z           = 0x8519, // GL 1.3
   texture_cube_map_negative_z           = 0x851A, // GL 1.3
   proxy_texture_cube_map                = 0x851B, // GL 1.3
   texture_1d_array                      = 0x8C18, // GL 3.0, ARB_internalformat_query2
   proxy_texture_1d_array                = 0x8C19, // GL 3.0
   texture_2d_array                      = 0x8C1A, // GL 3.0, ARB_internalformat_query2, EXT_sparse_texture
   proxy_texture_2d_array                = 0x8C1B, // GL 3.0
   texture_2d_multisample                = 0x9100, // GL 3.2, ARB_internalformat_query2, ARB_texture_multisample, NV_internalformat_sample_query
   proxy_texture_2d_multisample          = 0x9101, // GL 3.2, ARB_texture_multisample
   texture_2d_multisample_array          = 0x9102, // GL 3.2, ARB_internalformat_query2, ARB_texture_multisample, NV_internalformat_sample_query
   proxy_texture_2d_multisample_array    = 0x9103, // GL 3.2, ARB_texture_multisample
};
} // TextureTarget

namespace TextureParameterName {
enum TextureParameterName {
   texture_width              = 0x1000, // GL 1.0
   texture_height             = 0x1001, // GL 1.0
   texture_internal_format    = 0x1003, // GL 1.1
   texture_components         = 0x1003, // GL 1.0
   texture_border_color       = 0x1004, // GL 1.0
   texture_border             = 0x1005, // GL 1.0
   texture_mag_filter         = 0x2800, // GL 1.0
   texture_min_filter         = 0x2801, // GL 1.0
   texture_wrap_s             = 0x2802, // GL 1.0
   texture_wrap_t             = 0x2803, // GL 1.0
   texture_red_size           = 0x805C, // GL 1.1
   texture_green_size         = 0x805D, // GL 1.1
   texture_blue_size          = 0x805E, // GL 1.1
   texture_alpha_size         = 0x805F, // GL 1.1
   texture_luminance_size     = 0x8060, // GL 1.1
   texture_intensity_size     = 0x8061, // GL 1.1
   texture_priority           = 0x8066, // GL 1.1
   texture_resident           = 0x8067, // GL 1.1
   texture_wrap_r             = 0x8072, // GL 1.2
   texture_min_lod            = 0x813A, // GL 1.2
   texture_max_lod            = 0x813B, // GL 1.2
   texture_base_level         = 0x813C, // GL 1.2
   texture_max_level          = 0x813D, // GL 1.2
   generate_mipmap            = 0x8191, // GL 1.4
   texture_lod_bias           = 0x8501, // GL 1.4
   texture_compare_mode       = 0x884C, // GL 1.4
   texture_compare_func       = 0x884D, // GL 1.4
   texture_swizzle_r          = 0x8E42, // GL 3.3, ARB_texture_swizzle
   texture_swizzle_g          = 0x8E43, // GL 3.3, ARB_texture_swizzle
   texture_swizzle_b          = 0x8E44, // GL 3.3, ARB_texture_swizzle
   texture_swizzle_a          = 0x8E45, // GL 3.3, ARB_texture_swizzle
   texture_swizzle_rgba       = 0x8E46, // GL 3.3, ARB_texture_swizzle
};
} // TextureParameterName

namespace PixelType {
enum PixelType {
   byte                       = 0x1400, // GL 1.0, EXT_render_snorm, OES_byte_coordinates
   unsigned_byte              = 0x1401, // GL 1.0
   gl_short                   = 0x1402, // GL 1.0, EXT_render_snorm
   unsigned_short             = 0x1403, // GL 1.0, ANGLE_depth_texture, OES_depth_texture
   gl_int                     = 0x1404, // GL 1.0
   unsigned_int               = 0x1405, // GL 1.0, ANGLE_depth_texture, OES_depth_texture, OES_element_index_uint
   gl_float                   = 0x1406, // GL 1.0, ARB_vertex_shader, OES_texture_float
   bitmap                     = 0x1A00, // GL 1.0
   unsigned_byte_3_3_2        = 0x8032, // GL 1.2
   unsigned_short_4_4_4_4     = 0x8033, // GL 1.2
   unsigned_short_5_5_5_1     = 0x8034, // GL 1.2
   unsigned_int_8_8_8_8       = 0x8035, // GL 1.2
   unsigned_int_10_10_10_2    = 0x8036, // GL 1.2
};
} // PixelType

namespace PixelFormat {
enum PixelFormat {
   unsigned_short     = 0x1403, // GL 1.0, ANGLE_depth_texture, OES_depth_texture
   unsigned_int       = 0x1405, // GL 1.0, ANGLE_depth_texture, OES_depth_texture, OES_element_index_uint
   color_index        = 0x1900, // GL 1.0
   stencil_index      = 0x1901, // GL 1.0, GL 4.4, ARB_texture_stencil8
   depth_component    = 0x1902, // GL 1.0, ANGLE_depth_texture, OES_depth_texture
   red                = 0x1903, // GL 1.0, AMD_interleaved_elements
   green              = 0x1904, // GL 1.0, AMD_interleaved_elements
   blue               = 0x1905, // GL 1.0, AMD_interleaved_elements
   alpha              = 0x1906, // GL 1.0, AMD_interleaved_elements
   rgb                = 0x1907, // GL 1.0
   rgba               = 0x1908, // GL 1.0
   luminance          = 0x1909, // GL 1.0
   luminance_alpha    = 0x190A, // GL 1.0
};
} // PixelFormat

namespace InternalFormat {
enum InternalFormat {
   depth_component                              = 0x1902, // GL 1.0, ANGLE_depth_texture, OES_depth_texture
   red                                          = 0x1903, // GL 1.0, AMD_interleaved_elements
   rgb                                          = 0x1907, // GL 1.0
   rgba                                         = 0x1908, // GL 1.0
   r3_g3_b2                                     = 0x2A10, // GL 1.1
   alpha4                                       = 0x803B, // GL 1.1
   alpha8                                       = 0x803C, // GL 1.1
   alpha12                                      = 0x803D, // GL 1.1
   alpha16                                      = 0x803E, // GL 1.1
   luminance4                                   = 0x803F, // GL 1.1
   luminance8                                   = 0x8040, // GL 1.1
   luminance12                                  = 0x8041, // GL 1.1
   luminance16                                  = 0x8042, // GL 1.1
   luminance4_alpha4                            = 0x8043, // GL 1.1
   luminance6_alpha2                            = 0x8044, // GL 1.1
   luminance8_alpha8                            = 0x8045, // GL 1.1
   luminance12_alpha4                           = 0x8046, // GL 1.1
   luminance12_alpha12                          = 0x8047, // GL 1.1
   luminance16_alpha16                          = 0x8048, // GL 1.1
   intensity                                    = 0x8049, // GL 1.1
   intensity4                                   = 0x804A, // GL 1.1
   intensity8                                   = 0x804B, // GL 1.1
   intensity12                                  = 0x804C, // GL 1.1
   intensity16                                  = 0x804D, // GL 1.1
   rgb4                                         = 0x804F, // GL 1.1
   rgb5                                         = 0x8050, // GL 1.1
   rgb8                                         = 0x8051, // GL 1.1
   rgb10                                        = 0x8052, // GL 1.1
   rgb12                                        = 0x8053, // GL 1.1
   rgb16                                        = 0x8054, // GL 1.1
   rgba4                                        = 0x8056, // GL 1.1
   rgb5_a1                                      = 0x8057, // GL 1.1
   rgba8                                        = 0x8058, // GL 1.1
   rgb10_a2                                     = 0x8059, // GL 1.1
   rgba12                                       = 0x805A, // GL 1.1
   rgba16                                       = 0x805B, // GL 1.1
   depth_component16                            = 0x81A5, // GL 1.4, ANGLE_depth_texture
   compressed_red                               = 0x8225, // GL 3.0
   compressed_rg                                = 0x8226, // GL 3.0
   rg                                           = 0x8227, // GL 3.0, ARB_texture_rg
   r8                                           = 0x8229, // GL 3.0, ARB_texture_rg
   r16                                          = 0x822A, // GL 3.0, ARB_texture_rg
   rg8                                          = 0x822B, // GL 3.0, ARB_texture_rg
   rg16                                         = 0x822C, // GL 3.0, ARB_texture_rg
   r16f                                         = 0x822D, // GL 3.0, ARB_texture_rg
   r32f                                         = 0x822E, // GL 3.0, ARB_texture_rg
   rg16f                                        = 0x822F, // GL 3.0, ARB_texture_rg
   rg32f                                        = 0x8230, // GL 3.0, ARB_texture_rg
   r8i                                          = 0x8231, // GL 3.0, ARB_texture_rg
   r8ui                                         = 0x8232, // GL 3.0, ARB_texture_rg
   r16i                                         = 0x8233, // GL 3.0, ARB_texture_rg
   r16ui                                        = 0x8234, // GL 3.0, ARB_texture_rg
   r32i                                         = 0x8235, // GL 3.0, ARB_texture_rg
   r32ui                                        = 0x8236, // GL 3.0, ARB_texture_rg
   rg8i                                         = 0x8237, // GL 3.0, ARB_texture_rg
   rg8ui                                        = 0x8238, // GL 3.0, AMD_interleaved_elements, ARB_texture_rg
   rg16i                                        = 0x8239, // GL 3.0, ARB_texture_rg
   rg16ui                                       = 0x823A, // GL 3.0, AMD_interleaved_elements, ARB_texture_rg
   rg32i                                        = 0x823B, // GL 3.0, ARB_texture_rg
   rg32ui                                       = 0x823C, // GL 3.0, ARB_texture_rg
   compressed_rgb_s3tc_dxt1_ext                 = 0x83F0, // EXT_texture_compression_dxt1, EXT_texture_compression_s3tc
   compressed_rgba_s3tc_dxt1_ext                = 0x83F1, // EXT_texture_compression_dxt1, EXT_texture_compression_s3tc
   compressed_rgba_s3tc_dxt3_ext                = 0x83F2, // EXT_texture_compression_s3tc
   compressed_rgba_s3tc_dxt5_ext                = 0x83F3, // EXT_texture_compression_s3tc
   compressed_rgb                               = 0x84ED, // GL 1.3
   compressed_rgba                              = 0x84EE, // GL 1.3
   depth_stencil                                = 0x84F9, // GL 3.0, ARB_framebuffer_object
   rgba32f                                      = 0x8814, // GL 3.0
   rgba16f                                      = 0x881A, // GL 3.0
   rgb16f                                       = 0x881B, // GL 3.0
   depth24_stencil8                             = 0x88F0, // GL 3.0, ARB_framebuffer_object
   r11f_g11f_b10f                               = 0x8C3A, // GL 3.0
   rgb9_e5                                      = 0x8C3D, // GL 3.0
   srgb                                         = 0x8C40, // GL 2.1
   srgb8                                        = 0x8C41, // GL 2.1
   srgb_alpha                                   = 0x8C42, // GL 2.1
   srgb8_alpha8                                 = 0x8C43, // GL 2.1
   compressed_srgb                              = 0x8C48, // GL 2.1
   compressed_srgb_alpha                        = 0x8C49, // GL 2.1
   compressed_srgb_s3tc_dxt1_ext                = 0x8C4C, // EXT_texture_compression_s3tc_srgb, EXT_texture_sRGB
   compressed_srgb_alpha_s3tc_dxt1_ext          = 0x8C4D, // EXT_texture_compression_s3tc_srgb, EXT_texture_sRGB
   compressed_srgb_alpha_s3tc_dxt3_ext          = 0x8C4E, // EXT_texture_compression_s3tc_srgb, EXT_texture_sRGB
   compressed_srgb_alpha_s3tc_dxt5_ext          = 0x8C4F, // EXT_texture_compression_s3tc_srgb, EXT_texture_sRGB
   depth_component32f                           = 0x8CAC, // GL 3.0, ARB_depth_buffer_float
   depth32f_stencil8                            = 0x8CAD, // GL 3.0, ARB_depth_buffer_float
   rgba32ui                                     = 0x8D70, // GL 3.0
   rgb32ui                                      = 0x8D71, // GL 3.0, ARB_texture_buffer_object_rgb32
   rgba16ui                                     = 0x8D76, // GL 3.0
   rgb16ui                                      = 0x8D77, // GL 3.0
   rgba8ui                                      = 0x8D7C, // GL 3.0, AMD_interleaved_elements
   rgb8ui                                       = 0x8D7D, // GL 3.0
   rgba32i                                      = 0x8D82, // GL 3.0
   rgb32i                                       = 0x8D83, // GL 3.0, ARB_texture_buffer_object_rgb32, ARB_vertex_attrib_64bit
   rgba16i                                      = 0x8D88, // GL 3.0
   rgb16i                                       = 0x8D89, // GL 3.0
   rgba8i                                       = 0x8D8E, // GL 3.0
   rgb8i                                        = 0x8D8F, // GL 3.0
   compressed_red_rgtc1                         = 0x8DBB, // GL 3.0, ARB_texture_compression_rgtc
   compressed_signed_red_rgtc1                  = 0x8DBC, // GL 3.0, ARB_texture_compression_rgtc
   compressed_rg_rgtc2                          = 0x8DBD, // GL 3.0, ARB_texture_compression_rgtc
   compressed_signed_rg_rgtc2                   = 0x8DBE, // GL 3.0, ARB_texture_compression_rgtc
   compressed_rgba_bptc_unorm                   = 0x8E8C, // GL 4.2
   compressed_srgb_alpha_bptc_unorm             = 0x8E8D, // GL 4.2
   compressed_rgb_bptc_signed_float             = 0x8E8E, // GL 4.2
   compressed_rgb_bptc_unsigned_float           = 0x8E8F, // GL 4.2
   r8_snorm                                     = 0x8F94, // GL 3.1, EXT_render_snorm, EXT_texture_snorm
   rg8_snorm                                    = 0x8F95, // GL 3.1, EXT_render_snorm, EXT_texture_snorm
   rgb8_snorm                                   = 0x8F96, // GL 3.1, EXT_texture_snorm
   rgba8_snorm                                  = 0x8F97, // GL 3.1, EXT_render_snorm, EXT_texture_snorm
   r16_snorm                                    = 0x8F98, // GL 3.1, EXT_texture_snorm
   rg16_snorm                                   = 0x8F99, // GL 3.1, EXT_texture_snorm
   rgb16_snorm                                  = 0x8F9A, // GL 3.1, EXT_texture_snorm
   rgb10_a2ui                                   = 0x906F, // GL 3.3, ARB_texture_rgb10_a2ui
   compressed_r11_eac                           = 0x9270, // GL 4.3, ARB_ES3_compatibility
   compressed_signed_r11_eac                    = 0x9271, // GL 4.3, ARB_ES3_compatibility
   compressed_rg11_eac                          = 0x9272, // GL 4.3, ARB_ES3_compatibility
   compressed_signed_rg11_eac                   = 0x9273, // GL 4.3, ARB_ES3_compatibility
   compressed_rgb8_etc2                         = 0x9274, // GL 4.3, ARB_ES3_compatibility
   compressed_srgb8_etc2                        = 0x9275, // GL 4.3, ARB_ES3_compatibility
   compressed_rgb8_punchthrough_alpha1_etc2     = 0x9276, // GL 4.3, ARB_ES3_compatibility
   compressed_srgb8_punchthrough_alpha1_etc2    = 0x9277, // GL 4.3, ARB_ES3_compatibility
   compressed_rgba8_etc2_eac                    = 0x9278, // GL 4.3, ARB_ES3_compatibility
   compressed_srgb8_alpha8_etc2_eac             = 0x9279, // GL 4.3, ARB_ES3_compatibility
};
} // InternalFormat

namespace StringName {
enum StringName {
   vendor                      = 0x1F00, // GL 1.0
   renderer                    = 0x1F01, // GL 1.0
   version                     = 0x1F02, // GL 1.0
   extensions                  = 0x1F03, // GL 1.0
   shading_language_version    = 0x8B8C, // GL 2.0
};
} // StringName

namespace TextureEnvParameter {
enum TextureEnvParameter {
   texture_env_mode     = 0x2200, // GL 1.0
   texture_env_color    = 0x2201, // GL 1.0
};
} // TextureEnvParameter

namespace TextureEnvTarget {
enum TextureEnvTarget {
   texture_env    = 0x2300, // GL 1.0
};
} // TextureEnvTarget


////////// ENUMS /////////////////////////////////////////////////////////////

enum AllEnums {
   GL_CURRENT_BIT                                   = 0x00000001, // GL 1.0
   GL_POINT_BIT                                     = 0x00000002, // GL 1.0
   GL_LINE_BIT                                      = 0x00000004, // GL 1.0
   GL_POLYGON_BIT                                   = 0x00000008, // GL 1.0
   GL_POLYGON_STIPPLE_BIT                           = 0x00000010, // GL 1.0
   GL_PIXEL_MODE_BIT                                = 0x00000020, // GL 1.0
   GL_LIGHTING_BIT                                  = 0x00000040, // GL 1.0
   GL_FOG_BIT                                       = 0x00000080, // GL 1.0
   GL_DEPTH_BUFFER_BIT                              = 0x00000100, // GL 1.0
   GL_ACCUM_BUFFER_BIT                              = 0x00000200, // GL 1.0
   GL_STENCIL_BUFFER_BIT                            = 0x00000400, // GL 1.0
   GL_VIEWPORT_BIT                                  = 0x00000800, // GL 1.0
   GL_TRANSFORM_BIT                                 = 0x00001000, // GL 1.0
   GL_ENABLE_BIT                                    = 0x00002000, // GL 1.0
   GL_COLOR_BUFFER_BIT                              = 0x00004000, // GL 1.0
   GL_HINT_BIT                                      = 0x00008000, // GL 1.0
   GL_EVAL_BIT                                      = 0x00010000, // GL 1.0
   GL_LIST_BIT                                      = 0x00020000, // GL 1.0
   GL_TEXTURE_BIT                                   = 0x00040000, // GL 1.0
   GL_SCISSOR_BIT                                   = 0x00080000, // GL 1.0
   GL_MULTISAMPLE_BIT                               = 0x20000000, // GL 1.3
   GL_ALL_ATTRIB_BITS                               = 0xFFFFFFFF, // GL 1.0 // Guaranteed to mark all attribute groups at once
   GL_CLIENT_PIXEL_STORE_BIT                        = 0x00000001, // GL 1.1
   GL_CLIENT_VERTEX_ARRAY_BIT                       = 0x00000002, // GL 1.1
   GL_CLIENT_ALL_ATTRIB_BITS                        = 0xFFFFFFFF, // GL 1.1
   GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT           = 0x00000001, // GL 3.0
   GL_CONTEXT_FLAG_DEBUG_BIT                        = 0x00000002, // GL 4.3, KHR_debug
   GL_CONTEXT_CORE_PROFILE_BIT                      = 0x00000001, // GL 3.2
   GL_CONTEXT_COMPATIBILITY_PROFILE_BIT             = 0x00000002, // GL 3.2
   GL_MAP_READ_BIT                                  = 0x0001, // GL 3.0, GL 4.4, ARB_buffer_storage, ARB_map_buffer_range, EXT_buffer_storage
   GL_MAP_WRITE_BIT                                 = 0x0002, // GL 3.0, GL 4.4, ARB_buffer_storage, ARB_map_buffer_range, EXT_buffer_storage
   GL_MAP_INVALIDATE_RANGE_BIT                      = 0x0004, // GL 3.0, ARB_map_buffer_range
   GL_MAP_INVALIDATE_BUFFER_BIT                     = 0x0008, // GL 3.0, ARB_map_buffer_range
   GL_MAP_FLUSH_EXPLICIT_BIT                        = 0x0010, // GL 3.0, ARB_map_buffer_range
   GL_MAP_UNSYNCHRONIZED_BIT                        = 0x0020, // GL 3.0, ARB_map_buffer_range
   GL_SYNC_FLUSH_COMMANDS_BIT                       = 0x00000001, // GL 3.2, ARB_sync
   GL_FALSE                                         = 0, // GL 1.0
   GL_NO_ERROR                                      = 0, // GL 1.0, GL 4.5, ARB_robustness, EXT_robustness, KHR_robustness
   GL_ZERO                                          = 0, // GL 1.0, EXT_draw_buffers_indexed, NV_blend_equation_advanced, NV_register_combiners, OES_draw_buffers_indexed
   GL_NONE                                          = 0, // GL 1.0, GL 4.5, GL 4.6, KHR_context_flush_control, NV_register_combiners
   GL_TRUE                                          = 1, // GL 1.0
   GL_ONE                                           = 1, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_INVALID_INDEX                                 = 0xFFFFFFFFu, // GL 3.1, ARB_uniform_buffer_object // Tagged as uint
   GL_TIMEOUT_IGNORED                               = 0xFFFFFFFFFFFFFFFFull, // GL 3.2, ARB_sync // Tagged as uint64
   GL_POINTS                                        = 0x0000, // GL 1.0
   GL_LINES                                         = 0x0001, // GL 1.0
   GL_LINE_LOOP                                     = 0x0002, // GL 1.0
   GL_LINE_STRIP                                    = 0x0003, // GL 1.0
   GL_TRIANGLES                                     = 0x0004, // GL 1.0, ARB_tessellation_shader, EXT_tessellation_shader, OES_tessellation_shader
   GL_TRIANGLE_STRIP                                = 0x0005, // GL 1.0
   GL_TRIANGLE_FAN                                  = 0x0006, // GL 1.0
   GL_QUADS                                         = 0x0007, // GL 1.0, GL 4.0, ARB_tessellation_shader
   GL_QUAD_STRIP                                    = 0x0008, // GL 1.0
   GL_POLYGON                                       = 0x0009, // GL 1.0
   GL_LINES_ADJACENCY                               = 0x000A, // GL 3.2
   GL_LINE_STRIP_ADJACENCY                          = 0x000B, // GL 3.2
   GL_TRIANGLES_ADJACENCY                           = 0x000C, // GL 3.2
   GL_TRIANGLE_STRIP_ADJACENCY                      = 0x000D, // GL 3.2
   GL_ACCUM                                         = 0x0100, // GL 1.0
   GL_LOAD                                          = 0x0101, // GL 1.0
   GL_RETURN                                        = 0x0102, // GL 1.0
   GL_MULT                                          = 0x0103, // GL 1.0
   GL_ADD                                           = 0x0104, // GL 1.0
   GL_NEVER                                         = 0x0200, // GL 1.0
   GL_LESS                                          = 0x0201, // GL 1.0
   GL_EQUAL                                         = 0x0202, // GL 1.0, ARB_tessellation_shader, EXT_tessellation_shader, OES_tessellation_shader
   GL_LEQUAL                                        = 0x0203, // GL 1.0
   GL_GREATER                                       = 0x0204, // GL 1.0
   GL_NOTEQUAL                                      = 0x0205, // GL 1.0
   GL_GEQUAL                                        = 0x0206, // GL 1.0
   GL_ALWAYS                                        = 0x0207, // GL 1.0
   GL_SRC_COLOR                                     = 0x0300, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_ONE_MINUS_SRC_COLOR                           = 0x0301, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_SRC_ALPHA                                     = 0x0302, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_ONE_MINUS_SRC_ALPHA                           = 0x0303, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_DST_ALPHA                                     = 0x0304, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_ONE_MINUS_DST_ALPHA                           = 0x0305, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_DST_COLOR                                     = 0x0306, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_ONE_MINUS_DST_COLOR                           = 0x0307, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_SRC_ALPHA_SATURATE                            = 0x0308, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_FRONT_LEFT                                    = 0x0400, // GL 1.0
   GL_FRONT_RIGHT                                   = 0x0401, // GL 1.0
   GL_BACK_LEFT                                     = 0x0402, // GL 1.0
   GL_BACK_RIGHT                                    = 0x0403, // GL 1.0
   GL_FRONT                                         = 0x0404, // GL 1.0
   GL_BACK                                          = 0x0405, // GL 1.0, GL 4.5, ARB_ES3_1_compatibility
   GL_LEFT                                          = 0x0406, // GL 1.0
   GL_RIGHT                                         = 0x0407, // GL 1.0
   GL_FRONT_AND_BACK                                = 0x0408, // GL 1.0
   GL_AUX0                                          = 0x0409, // GL 1.0
   GL_AUX1                                          = 0x040A, // GL 1.0
   GL_AUX2                                          = 0x040B, // GL 1.0
   GL_AUX3                                          = 0x040C, // GL 1.0
   GL_INVALID_ENUM                                  = 0x0500, // GL 1.0
   GL_INVALID_VALUE                                 = 0x0501, // GL 1.0
   GL_INVALID_OPERATION                             = 0x0502, // GL 1.0
   GL_STACK_OVERFLOW                                = 0x0503, // GL 1.0, KHR_debug
   GL_STACK_UNDERFLOW                               = 0x0504, // GL 1.0, KHR_debug
   GL_OUT_OF_MEMORY                                 = 0x0505, // GL 1.0
   GL_INVALID_FRAMEBUFFER_OPERATION                 = 0x0506, // GL 3.0, ARB_framebuffer_object
   GL_2D                                            = 0x0600, // GL 1.0
   GL_3D                                            = 0x0601, // GL 1.0
   GL_3D_COLOR                                      = 0x0602, // GL 1.0
   GL_3D_COLOR_TEXTURE                              = 0x0603, // GL 1.0
   GL_4D_COLOR_TEXTURE                              = 0x0604, // GL 1.0
   GL_PASS_THROUGH_TOKEN                            = 0x0700, // GL 1.0
   GL_POINT_TOKEN                                   = 0x0701, // GL 1.0
   GL_LINE_TOKEN                                    = 0x0702, // GL 1.0
   GL_POLYGON_TOKEN                                 = 0x0703, // GL 1.0
   GL_BITMAP_TOKEN                                  = 0x0704, // GL 1.0
   GL_DRAW_PIXEL_TOKEN                              = 0x0705, // GL 1.0
   GL_COPY_PIXEL_TOKEN                              = 0x0706, // GL 1.0
   GL_LINE_RESET_TOKEN                              = 0x0707, // GL 1.0
   GL_EXP                                           = 0x0800, // GL 1.0
   GL_EXP2                                          = 0x0801, // GL 1.0
   GL_CW                                            = 0x0900, // GL 1.0, ARB_tessellation_shader, EXT_tessellation_shader, OES_tessellation_shader
   GL_CCW                                           = 0x0901, // GL 1.0, ARB_tessellation_shader, EXT_tessellation_shader, OES_tessellation_shader
   GL_COEFF                                         = 0x0A00, // GL 1.0
   GL_ORDER                                         = 0x0A01, // GL 1.0
   GL_DOMAIN                                        = 0x0A02, // GL 1.0
   GL_CURRENT_COLOR                                 = 0x0B00, // GL 1.0
   GL_CURRENT_INDEX                                 = 0x0B01, // GL 1.0
   GL_CURRENT_NORMAL                                = 0x0B02, // GL 1.0
   GL_CURRENT_TEXTURE_COORDS                        = 0x0B03, // GL 1.0
   GL_CURRENT_RASTER_COLOR                          = 0x0B04, // GL 1.0
   GL_CURRENT_RASTER_INDEX                          = 0x0B05, // GL 1.0
   GL_CURRENT_RASTER_TEXTURE_COORDS                 = 0x0B06, // GL 1.0
   GL_CURRENT_RASTER_POSITION                       = 0x0B07, // GL 1.0
   GL_CURRENT_RASTER_POSITION_VALID                 = 0x0B08, // GL 1.0
   GL_CURRENT_RASTER_DISTANCE                       = 0x0B09, // GL 1.0
   GL_POINT_SMOOTH                                  = 0x0B10, // GL 1.0
   GL_POINT_SIZE                                    = 0x0B11, // GL 1.0
   GL_POINT_SIZE_RANGE                              = 0x0B12, // GL 1.0
   GL_SMOOTH_POINT_SIZE_RANGE                       = 0x0B12, // Aliases GL_POINT_SIZE_RANGE // GL 1.2
   GL_POINT_SIZE_GRANULARITY                        = 0x0B13, // GL 1.0
   GL_SMOOTH_POINT_SIZE_GRANULARITY                 = 0x0B13, // Aliases GL_POINT_SIZE_GRANULARITY // GL 1.2
   GL_LINE_SMOOTH                                   = 0x0B20, // GL 1.0
   GL_LINE_WIDTH                                    = 0x0B21, // GL 1.0
   GL_LINE_WIDTH_RANGE                              = 0x0B22, // GL 1.0
   GL_SMOOTH_LINE_WIDTH_RANGE                       = 0x0B22, // Aliases GL_LINE_WIDTH_RANGE // GL 1.2
   GL_LINE_WIDTH_GRANULARITY                        = 0x0B23, // GL 1.0
   GL_SMOOTH_LINE_WIDTH_GRANULARITY                 = 0x0B23, // Aliases GL_LINE_WIDTH_GRANULARITY // GL 1.2
   GL_LINE_STIPPLE                                  = 0x0B24, // GL 1.0
   GL_LINE_STIPPLE_PATTERN                          = 0x0B25, // GL 1.0
   GL_LINE_STIPPLE_REPEAT                           = 0x0B26, // GL 1.0
   GL_LIST_MODE                                     = 0x0B30, // GL 1.0
   GL_MAX_LIST_NESTING                              = 0x0B31, // GL 1.0
   GL_LIST_BASE                                     = 0x0B32, // GL 1.0
   GL_LIST_INDEX                                    = 0x0B33, // GL 1.0
   GL_POLYGON_MODE                                  = 0x0B40, // GL 1.0
   GL_POLYGON_SMOOTH                                = 0x0B41, // GL 1.0
   GL_POLYGON_STIPPLE                               = 0x0B42, // GL 1.0
   GL_EDGE_FLAG                                     = 0x0B43, // GL 1.0
   GL_CULL_FACE                                     = 0x0B44, // GL 1.0
   GL_CULL_FACE_MODE                                = 0x0B45, // GL 1.0
   GL_FRONT_FACE                                    = 0x0B46, // GL 1.0
   GL_LIGHTING                                      = 0x0B50, // GL 1.0
   GL_LIGHT_MODEL_LOCAL_VIEWER                      = 0x0B51, // GL 1.0
   GL_LIGHT_MODEL_TWO_SIDE                          = 0x0B52, // GL 1.0
   GL_LIGHT_MODEL_AMBIENT                           = 0x0B53, // GL 1.0
   GL_SHADE_MODEL                                   = 0x0B54, // GL 1.0
   GL_COLOR_MATERIAL_FACE                           = 0x0B55, // GL 1.0
   GL_COLOR_MATERIAL_PARAMETER                      = 0x0B56, // GL 1.0
   GL_COLOR_MATERIAL                                = 0x0B57, // GL 1.0
   GL_FOG                                           = 0x0B60, // GL 1.0, NV_register_combiners
   GL_FOG_INDEX                                     = 0x0B61, // GL 1.0
   GL_FOG_DENSITY                                   = 0x0B62, // GL 1.0
   GL_FOG_START                                     = 0x0B63, // GL 1.0
   GL_FOG_END                                       = 0x0B64, // GL 1.0
   GL_FOG_MODE                                      = 0x0B65, // GL 1.0
   GL_FOG_COLOR                                     = 0x0B66, // GL 1.0
   GL_DEPTH_RANGE                                   = 0x0B70, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   GL_DEPTH_TEST                                    = 0x0B71, // GL 1.0
   GL_DEPTH_WRITEMASK                               = 0x0B72, // GL 1.0
   GL_DEPTH_CLEAR_VALUE                             = 0x0B73, // GL 1.0
   GL_DEPTH_FUNC                                    = 0x0B74, // GL 1.0
   GL_ACCUM_CLEAR_VALUE                             = 0x0B80, // GL 1.0
   GL_STENCIL_TEST                                  = 0x0B90, // GL 1.0
   GL_STENCIL_CLEAR_VALUE                           = 0x0B91, // GL 1.0
   GL_STENCIL_FUNC                                  = 0x0B92, // GL 1.0
   GL_STENCIL_VALUE_MASK                            = 0x0B93, // GL 1.0
   GL_STENCIL_FAIL                                  = 0x0B94, // GL 1.0
   GL_STENCIL_PASS_DEPTH_FAIL                       = 0x0B95, // GL 1.0
   GL_STENCIL_PASS_DEPTH_PASS                       = 0x0B96, // GL 1.0
   GL_STENCIL_REF                                   = 0x0B97, // GL 1.0
   GL_STENCIL_WRITEMASK                             = 0x0B98, // GL 1.0
   GL_MATRIX_MODE                                   = 0x0BA0, // GL 1.0
   GL_NORMALIZE                                     = 0x0BA1, // GL 1.0
   GL_VIEWPORT                                      = 0x0BA2, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   GL_MODELVIEW_STACK_DEPTH                         = 0x0BA3, // GL 1.0
   GL_PROJECTION_STACK_DEPTH                        = 0x0BA4, // GL 1.0
   GL_TEXTURE_STACK_DEPTH                           = 0x0BA5, // GL 1.0
   GL_MODELVIEW_MATRIX                              = 0x0BA6, // GL 1.0
   GL_PROJECTION_MATRIX                             = 0x0BA7, // GL 1.0
   GL_TEXTURE_MATRIX                                = 0x0BA8, // GL 1.0
   GL_ATTRIB_STACK_DEPTH                            = 0x0BB0, // GL 1.0
   GL_CLIENT_ATTRIB_STACK_DEPTH                     = 0x0BB1, // GL 1.1
   GL_ALPHA_TEST                                    = 0x0BC0, // GL 1.0
   GL_ALPHA_TEST_FUNC                               = 0x0BC1, // GL 1.0
   GL_ALPHA_TEST_REF                                = 0x0BC2, // GL 1.0
   GL_DITHER                                        = 0x0BD0, // GL 1.0
   GL_BLEND_DST                                     = 0x0BE0, // GL 1.0
   GL_BLEND_SRC                                     = 0x0BE1, // GL 1.0
   GL_BLEND                                         = 0x0BE2, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_LOGIC_OP_MODE                                 = 0x0BF0, // GL 1.0
   GL_INDEX_LOGIC_OP                                = 0x0BF1, // GL 1.1
   GL_LOGIC_OP                                      = 0x0BF1, // GL 1.0
   GL_COLOR_LOGIC_OP                                = 0x0BF2, // GL 1.1
   GL_AUX_BUFFERS                                   = 0x0C00, // GL 1.0
   GL_DRAW_BUFFER                                   = 0x0C01, // GL 1.0
   GL_READ_BUFFER                                   = 0x0C02, // GL 1.0
   GL_SCISSOR_BOX                                   = 0x0C10, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   GL_SCISSOR_TEST                                  = 0x0C11, // GL 1.0, ARB_viewport_array, NV_viewport_array, OES_viewport_array
   GL_INDEX_CLEAR_VALUE                             = 0x0C20, // GL 1.0
   GL_INDEX_WRITEMASK                               = 0x0C21, // GL 1.0
   GL_COLOR_CLEAR_VALUE                             = 0x0C22, // GL 1.0
   GL_COLOR_WRITEMASK                               = 0x0C23, // GL 1.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_INDEX_MODE                                    = 0x0C30, // GL 1.0
   GL_RGBA_MODE                                     = 0x0C31, // GL 1.0
   GL_DOUBLEBUFFER                                  = 0x0C32, // GL 1.0
   GL_STEREO                                        = 0x0C33, // GL 1.0
   GL_RENDER_MODE                                   = 0x0C40, // GL 1.0
   GL_PERSPECTIVE_CORRECTION_HINT                   = 0x0C50, // GL 1.0
   GL_POINT_SMOOTH_HINT                             = 0x0C51, // GL 1.0
   GL_LINE_SMOOTH_HINT                              = 0x0C52, // GL 1.0
   GL_POLYGON_SMOOTH_HINT                           = 0x0C53, // GL 1.0
   GL_FOG_HINT                                      = 0x0C54, // GL 1.0
   GL_TEXTURE_GEN_S                                 = 0x0C60, // GL 1.0
   GL_TEXTURE_GEN_T                                 = 0x0C61, // GL 1.0
   GL_TEXTURE_GEN_R                                 = 0x0C62, // GL 1.0
   GL_TEXTURE_GEN_Q                                 = 0x0C63, // GL 1.0
   GL_PIXEL_MAP_I_TO_I                              = 0x0C70, // GL 1.0
   GL_PIXEL_MAP_S_TO_S                              = 0x0C71, // GL 1.0
   GL_PIXEL_MAP_I_TO_R                              = 0x0C72, // GL 1.0
   GL_PIXEL_MAP_I_TO_G                              = 0x0C73, // GL 1.0
   GL_PIXEL_MAP_I_TO_B                              = 0x0C74, // GL 1.0
   GL_PIXEL_MAP_I_TO_A                              = 0x0C75, // GL 1.0
   GL_PIXEL_MAP_R_TO_R                              = 0x0C76, // GL 1.0
   GL_PIXEL_MAP_G_TO_G                              = 0x0C77, // GL 1.0
   GL_PIXEL_MAP_B_TO_B                              = 0x0C78, // GL 1.0
   GL_PIXEL_MAP_A_TO_A                              = 0x0C79, // GL 1.0
   GL_PIXEL_MAP_I_TO_I_SIZE                         = 0x0CB0, // GL 1.0
   GL_PIXEL_MAP_S_TO_S_SIZE                         = 0x0CB1, // GL 1.0
   GL_PIXEL_MAP_I_TO_R_SIZE                         = 0x0CB2, // GL 1.0
   GL_PIXEL_MAP_I_TO_G_SIZE                         = 0x0CB3, // GL 1.0
   GL_PIXEL_MAP_I_TO_B_SIZE                         = 0x0CB4, // GL 1.0
   GL_PIXEL_MAP_I_TO_A_SIZE                         = 0x0CB5, // GL 1.0
   GL_PIXEL_MAP_R_TO_R_SIZE                         = 0x0CB6, // GL 1.0
   GL_PIXEL_MAP_G_TO_G_SIZE                         = 0x0CB7, // GL 1.0
   GL_PIXEL_MAP_B_TO_B_SIZE                         = 0x0CB8, // GL 1.0
   GL_PIXEL_MAP_A_TO_A_SIZE                         = 0x0CB9, // GL 1.0
   GL_UNPACK_SWAP_BYTES                             = 0x0CF0, // GL 1.0
   GL_UNPACK_LSB_FIRST                              = 0x0CF1, // GL 1.0
   GL_UNPACK_ROW_LENGTH                             = 0x0CF2, // GL 1.0
   GL_UNPACK_SKIP_ROWS                              = 0x0CF3, // GL 1.0
   GL_UNPACK_SKIP_PIXELS                            = 0x0CF4, // GL 1.0
   GL_UNPACK_ALIGNMENT                              = 0x0CF5, // GL 1.0
   GL_PACK_SWAP_BYTES                               = 0x0D00, // GL 1.0
   GL_PACK_LSB_FIRST                                = 0x0D01, // GL 1.0
   GL_PACK_ROW_LENGTH                               = 0x0D02, // GL 1.0
   GL_PACK_SKIP_ROWS                                = 0x0D03, // GL 1.0
   GL_PACK_SKIP_PIXELS                              = 0x0D04, // GL 1.0
   GL_PACK_ALIGNMENT                                = 0x0D05, // GL 1.0
   GL_MAP_COLOR                                     = 0x0D10, // GL 1.0
   GL_MAP_STENCIL                                   = 0x0D11, // GL 1.0
   GL_INDEX_SHIFT                                   = 0x0D12, // GL 1.0
   GL_INDEX_OFFSET                                  = 0x0D13, // GL 1.0
   GL_RED_SCALE                                     = 0x0D14, // GL 1.0
   GL_RED_BIAS                                      = 0x0D15, // GL 1.0
   GL_ZOOM_X                                        = 0x0D16, // GL 1.0
   GL_ZOOM_Y                                        = 0x0D17, // GL 1.0
   GL_GREEN_SCALE                                   = 0x0D18, // GL 1.0
   GL_GREEN_BIAS                                    = 0x0D19, // GL 1.0
   GL_BLUE_SCALE                                    = 0x0D1A, // GL 1.0
   GL_BLUE_BIAS                                     = 0x0D1B, // GL 1.0
   GL_ALPHA_SCALE                                   = 0x0D1C, // GL 1.0
   GL_ALPHA_BIAS                                    = 0x0D1D, // GL 1.0
   GL_DEPTH_SCALE                                   = 0x0D1E, // GL 1.0
   GL_DEPTH_BIAS                                    = 0x0D1F, // GL 1.0
   GL_MAX_EVAL_ORDER                                = 0x0D30, // GL 1.0
   GL_MAX_LIGHTS                                    = 0x0D31, // GL 1.0
   GL_MAX_CLIP_PLANES                               = 0x0D32, // GL 1.0
   GL_MAX_CLIP_DISTANCES                            = 0x0D32, // Aliases GL_MAX_CLIP_PLANES // GL 3.0
   GL_MAX_TEXTURE_SIZE                              = 0x0D33, // GL 1.0
   GL_MAX_PIXEL_MAP_TABLE                           = 0x0D34, // GL 1.0
   GL_MAX_ATTRIB_STACK_DEPTH                        = 0x0D35, // GL 1.0
   GL_MAX_MODELVIEW_STACK_DEPTH                     = 0x0D36, // GL 1.0
   GL_MAX_NAME_STACK_DEPTH                          = 0x0D37, // GL 1.0
   GL_MAX_PROJECTION_STACK_DEPTH                    = 0x0D38, // GL 1.0
   GL_MAX_TEXTURE_STACK_DEPTH                       = 0x0D39, // GL 1.0
   GL_MAX_VIEWPORT_DIMS                             = 0x0D3A, // GL 1.0
   GL_MAX_CLIENT_ATTRIB_STACK_DEPTH                 = 0x0D3B, // GL 1.1
   GL_SUBPIXEL_BITS                                 = 0x0D50, // GL 1.0
   GL_INDEX_BITS                                    = 0x0D51, // GL 1.0
   GL_RED_BITS                                      = 0x0D52, // GL 1.0
   GL_GREEN_BITS                                    = 0x0D53, // GL 1.0
   GL_BLUE_BITS                                     = 0x0D54, // GL 1.0
   GL_ALPHA_BITS                                    = 0x0D55, // GL 1.0
   GL_DEPTH_BITS                                    = 0x0D56, // GL 1.0
   GL_STENCIL_BITS                                  = 0x0D57, // GL 1.0
   GL_ACCUM_RED_BITS                                = 0x0D58, // GL 1.0
   GL_ACCUM_GREEN_BITS                              = 0x0D59, // GL 1.0
   GL_ACCUM_BLUE_BITS                               = 0x0D5A, // GL 1.0
   GL_ACCUM_ALPHA_BITS                              = 0x0D5B, // GL 1.0
   GL_NAME_STACK_DEPTH                              = 0x0D70, // GL 1.0
   GL_AUTO_NORMAL                                   = 0x0D80, // GL 1.0
   GL_MAP1_COLOR_4                                  = 0x0D90, // GL 1.0
   GL_MAP1_INDEX                                    = 0x0D91, // GL 1.0
   GL_MAP1_NORMAL                                   = 0x0D92, // GL 1.0
   GL_MAP1_TEXTURE_COORD_1                          = 0x0D93, // GL 1.0
   GL_MAP1_TEXTURE_COORD_2                          = 0x0D94, // GL 1.0
   GL_MAP1_TEXTURE_COORD_3                          = 0x0D95, // GL 1.0
   GL_MAP1_TEXTURE_COORD_4                          = 0x0D96, // GL 1.0
   GL_MAP1_VERTEX_3                                 = 0x0D97, // GL 1.0
   GL_MAP1_VERTEX_4                                 = 0x0D98, // GL 1.0
   GL_MAP2_COLOR_4                                  = 0x0DB0, // GL 1.0
   GL_MAP2_INDEX                                    = 0x0DB1, // GL 1.0
   GL_MAP2_NORMAL                                   = 0x0DB2, // GL 1.0
   GL_MAP2_TEXTURE_COORD_1                          = 0x0DB3, // GL 1.0
   GL_MAP2_TEXTURE_COORD_2                          = 0x0DB4, // GL 1.0
   GL_MAP2_TEXTURE_COORD_3                          = 0x0DB5, // GL 1.0
   GL_MAP2_TEXTURE_COORD_4                          = 0x0DB6, // GL 1.0
   GL_MAP2_VERTEX_3                                 = 0x0DB7, // GL 1.0
   GL_MAP2_VERTEX_4                                 = 0x0DB8, // GL 1.0
   GL_MAP1_GRID_DOMAIN                              = 0x0DD0, // GL 1.0
   GL_MAP1_GRID_SEGMENTS                            = 0x0DD1, // GL 1.0
   GL_MAP2_GRID_DOMAIN                              = 0x0DD2, // GL 1.0
   GL_MAP2_GRID_SEGMENTS                            = 0x0DD3, // GL 1.0
   GL_TEXTURE_1D                                    = 0x0DE0, // GL 1.0, ARB_internalformat_query2
   GL_TEXTURE_2D                                    = 0x0DE1, // GL 1.0, ARB_internalformat_query2, EXT_sparse_texture
   GL_FEEDBACK_BUFFER_POINTER                       = 0x0DF0, // GL 1.1
   GL_FEEDBACK_BUFFER_SIZE                          = 0x0DF1, // GL 1.1
   GL_FEEDBACK_BUFFER_TYPE                          = 0x0DF2, // GL 1.1
   GL_SELECTION_BUFFER_POINTER                      = 0x0DF3, // GL 1.1
   GL_SELECTION_BUFFER_SIZE                         = 0x0DF4, // GL 1.1
   GL_TEXTURE_WIDTH                                 = 0x1000, // GL 1.0
   GL_TEXTURE_HEIGHT                                = 0x1001, // GL 1.0
   GL_TEXTURE_INTERNAL_FORMAT                       = 0x1003, // GL 1.1
   GL_TEXTURE_COMPONENTS                            = 0x1003, // GL 1.0
   GL_TEXTURE_BORDER_COLOR                          = 0x1004, // GL 1.0
   GL_TEXTURE_BORDER                                = 0x1005, // GL 1.0
   GL_DONT_CARE                                     = 0x1100, // GL 1.0
   GL_FASTEST                                       = 0x1101, // GL 1.0
   GL_NICEST                                        = 0x1102, // GL 1.0
   GL_AMBIENT                                       = 0x1200, // GL 1.0
   GL_DIFFUSE                                       = 0x1201, // GL 1.0
   GL_SPECULAR                                      = 0x1202, // GL 1.0
   GL_POSITION                                      = 0x1203, // GL 1.0
   GL_SPOT_DIRECTION                                = 0x1204, // GL 1.0
   GL_SPOT_EXPONENT                                 = 0x1205, // GL 1.0
   GL_SPOT_CUTOFF                                   = 0x1206, // GL 1.0
   GL_CONSTANT_ATTENUATION                          = 0x1207, // GL 1.0
   GL_LINEAR_ATTENUATION                            = 0x1208, // GL 1.0
   GL_QUADRATIC_ATTENUATION                         = 0x1209, // GL 1.0
   GL_COMPILE                                       = 0x1300, // GL 1.0
   GL_COMPILE_AND_EXECUTE                           = 0x1301, // GL 1.0
   GL_BYTE                                          = 0x1400, // GL 1.0, EXT_render_snorm, OES_byte_coordinates
   GL_UNSIGNED_BYTE                                 = 0x1401, // GL 1.0
   GL_SHORT                                         = 0x1402, // GL 1.0, EXT_render_snorm
   GL_UNSIGNED_SHORT                                = 0x1403, // GL 1.0, ANGLE_depth_texture, OES_depth_texture
   GL_INT                                           = 0x1404, // GL 1.0
   GL_UNSIGNED_INT                                  = 0x1405, // GL 1.0, ANGLE_depth_texture, OES_depth_texture, OES_element_index_uint
   GL_FLOAT                                         = 0x1406, // GL 1.0, ARB_vertex_shader, OES_texture_float
   GL_2_BYTES                                       = 0x1407, // GL 1.0
   GL_3_BYTES                                       = 0x1408, // GL 1.0
   GL_4_BYTES                                       = 0x1409, // GL 1.0
   GL_DOUBLE                                        = 0x140A, // GL 1.1, ARB_gpu_shader_fp64, EXT_vertex_attrib_64bit
   GL_HALF_FLOAT                                    = 0x140B, // GL 3.0, ARB_half_float_vertex
   GL_CLEAR                                         = 0x1500, // GL 1.0
   GL_AND                                           = 0x1501, // GL 1.0
   GL_AND_REVERSE                                   = 0x1502, // GL 1.0
   GL_COPY                                          = 0x1503, // GL 1.0
   GL_AND_INVERTED                                  = 0x1504, // GL 1.0
   GL_NOOP                                          = 0x1505, // GL 1.0
   GL_XOR                                           = 0x1506, // GL 1.0
   GL_OR                                            = 0x1507, // GL 1.0
   GL_NOR                                           = 0x1508, // GL 1.0
   GL_EQUIV                                         = 0x1509, // GL 1.0
   GL_INVERT                                        = 0x150A, // GL 1.0, NV_blend_equation_advanced
   GL_OR_REVERSE                                    = 0x150B, // GL 1.0
   GL_COPY_INVERTED                                 = 0x150C, // GL 1.0
   GL_OR_INVERTED                                   = 0x150D, // GL 1.0
   GL_NAND                                          = 0x150E, // GL 1.0
   GL_SET                                           = 0x150F, // GL 1.0
   GL_EMISSION                                      = 0x1600, // GL 1.0
   GL_SHININESS                                     = 0x1601, // GL 1.0
   GL_AMBIENT_AND_DIFFUSE                           = 0x1602, // GL 1.0
   GL_COLOR_INDEXES                                 = 0x1603, // GL 1.0
   GL_MODELVIEW                                     = 0x1700, // GL 1.0
   GL_PROJECTION                                    = 0x1701, // GL 1.0
   GL_TEXTURE                                       = 0x1702, // GL 1.0
   GL_COLOR                                         = 0x1800, // GL 1.0
   GL_DEPTH                                         = 0x1801, // GL 1.0
   GL_STENCIL                                       = 0x1802, // GL 1.0
   GL_COLOR_INDEX                                   = 0x1900, // GL 1.0
   GL_STENCIL_INDEX                                 = 0x1901, // GL 1.0, GL 4.4, ARB_texture_stencil8
   GL_DEPTH_COMPONENT                               = 0x1902, // GL 1.0, ANGLE_depth_texture, OES_depth_texture
   GL_RED                                           = 0x1903, // GL 1.0, AMD_interleaved_elements
   GL_GREEN                                         = 0x1904, // GL 1.0, AMD_interleaved_elements
   GL_BLUE                                          = 0x1905, // GL 1.0, AMD_interleaved_elements
   GL_ALPHA                                         = 0x1906, // GL 1.0, AMD_interleaved_elements
   GL_RGB                                           = 0x1907, // GL 1.0
   GL_RGBA                                          = 0x1908, // GL 1.0
   GL_LUMINANCE                                     = 0x1909, // GL 1.0
   GL_LUMINANCE_ALPHA                               = 0x190A, // GL 1.0
   GL_BITMAP                                        = 0x1A00, // GL 1.0
   GL_POINT                                         = 0x1B00, // GL 1.0
   GL_LINE                                          = 0x1B01, // GL 1.0
   GL_FILL                                          = 0x1B02, // GL 1.0
   GL_RENDER                                        = 0x1C00, // GL 1.0
   GL_FEEDBACK                                      = 0x1C01, // GL 1.0
   GL_SELECT                                        = 0x1C02, // GL 1.0
   GL_FLAT                                          = 0x1D00, // GL 1.0
   GL_SMOOTH                                        = 0x1D01, // GL 1.0
   GL_KEEP                                          = 0x1E00, // GL 1.0
   GL_REPLACE                                       = 0x1E01, // GL 1.0
   GL_INCR                                          = 0x1E02, // GL 1.0
   GL_DECR                                          = 0x1E03, // GL 1.0
   GL_VENDOR                                        = 0x1F00, // GL 1.0
   GL_RENDERER                                      = 0x1F01, // GL 1.0
   GL_VERSION                                       = 0x1F02, // GL 1.0
   GL_EXTENSIONS                                    = 0x1F03, // GL 1.0
   GL_S                                             = 0x2000, // GL 1.0
   GL_T                                             = 0x2001, // GL 1.0
   GL_R                                             = 0x2002, // GL 1.0
   GL_Q                                             = 0x2003, // GL 1.0
   GL_MODULATE                                      = 0x2100, // GL 1.0
   GL_DECAL                                         = 0x2101, // GL 1.0
   GL_TEXTURE_ENV_MODE                              = 0x2200, // GL 1.0
   GL_TEXTURE_ENV_COLOR                             = 0x2201, // GL 1.0
   GL_TEXTURE_ENV                                   = 0x2300, // GL 1.0
   GL_EYE_LINEAR                                    = 0x2400, // GL 1.0
   GL_OBJECT_LINEAR                                 = 0x2401, // GL 1.0
   GL_SPHERE_MAP                                    = 0x2402, // GL 1.0
   GL_TEXTURE_GEN_MODE                              = 0x2500, // GL 1.0
   GL_OBJECT_PLANE                                  = 0x2501, // GL 1.0
   GL_EYE_PLANE                                     = 0x2502, // GL 1.0, NV_fog_distance
   GL_NEAREST                                       = 0x2600, // GL 1.0
   GL_LINEAR                                        = 0x2601, // GL 1.0
   GL_NEAREST_MIPMAP_NEAREST                        = 0x2700, // GL 1.0
   GL_LINEAR_MIPMAP_NEAREST                         = 0x2701, // GL 1.0
   GL_NEAREST_MIPMAP_LINEAR                         = 0x2702, // GL 1.0
   GL_LINEAR_MIPMAP_LINEAR                          = 0x2703, // GL 1.0
   GL_TEXTURE_MAG_FILTER                            = 0x2800, // GL 1.0
   GL_TEXTURE_MIN_FILTER                            = 0x2801, // GL 1.0
   GL_TEXTURE_WRAP_S                                = 0x2802, // GL 1.0
   GL_TEXTURE_WRAP_T                                = 0x2803, // GL 1.0
   GL_CLAMP                                         = 0x2900, // GL 1.0
   GL_REPEAT                                        = 0x2901, // GL 1.0
   GL_POLYGON_OFFSET_UNITS                          = 0x2A00, // GL 1.1
   GL_POLYGON_OFFSET_POINT                          = 0x2A01, // GL 1.1
   GL_POLYGON_OFFSET_LINE                           = 0x2A02, // GL 1.1
   GL_R3_G3_B2                                      = 0x2A10, // GL 1.1
   GL_V2F                                           = 0x2A20, // GL 1.1
   GL_V3F                                           = 0x2A21, // GL 1.1
   GL_C4UB_V2F                                      = 0x2A22, // GL 1.1
   GL_C4UB_V3F                                      = 0x2A23, // GL 1.1
   GL_C3F_V3F                                       = 0x2A24, // GL 1.1
   GL_N3F_V3F                                       = 0x2A25, // GL 1.1
   GL_C4F_N3F_V3F                                   = 0x2A26, // GL 1.1
   GL_T2F_V3F                                       = 0x2A27, // GL 1.1
   GL_T4F_V4F                                       = 0x2A28, // GL 1.1
   GL_T2F_C4UB_V3F                                  = 0x2A29, // GL 1.1
   GL_T2F_C3F_V3F                                   = 0x2A2A, // GL 1.1
   GL_T2F_N3F_V3F                                   = 0x2A2B, // GL 1.1
   GL_T2F_C4F_N3F_V3F                               = 0x2A2C, // GL 1.1
   GL_T4F_C4F_N3F_V4F                               = 0x2A2D, // GL 1.1
   GL_CLIP_PLANE0                                   = 0x3000, // GL 1.0
   GL_CLIP_DISTANCE0                                = 0x3000, // Aliases GL_CLIP_PLANE0 // GL 3.0
   GL_CLIP_PLANE1                                   = 0x3001, // GL 1.0
   GL_CLIP_DISTANCE1                                = 0x3001, // Aliases GL_CLIP_PLANE1 // GL 3.0
   GL_CLIP_PLANE2                                   = 0x3002, // GL 1.0
   GL_CLIP_DISTANCE2                                = 0x3002, // Aliases GL_CLIP_PLANE2 // GL 3.0
   GL_CLIP_PLANE3                                   = 0x3003, // GL 1.0
   GL_CLIP_DISTANCE3                                = 0x3003, // Aliases GL_CLIP_PLANE3 // GL 3.0
   GL_CLIP_PLANE4                                   = 0x3004, // GL 1.0
   GL_CLIP_DISTANCE4                                = 0x3004, // Aliases GL_CLIP_PLANE4 // GL 3.0
   GL_CLIP_PLANE5                                   = 0x3005, // GL 1.0
   GL_CLIP_DISTANCE5                                = 0x3005, // Aliases GL_CLIP_PLANE5 // GL 3.0
   GL_CLIP_DISTANCE6                                = 0x3006, // GL 3.0
   GL_CLIP_DISTANCE7                                = 0x3007, // GL 3.0
   GL_LIGHT0                                        = 0x4000, // GL 1.0
   GL_LIGHT1                                        = 0x4001, // GL 1.0
   GL_LIGHT2                                        = 0x4002, // GL 1.0
   GL_LIGHT3                                        = 0x4003, // GL 1.0
   GL_LIGHT4                                        = 0x4004, // GL 1.0
   GL_LIGHT5                                        = 0x4005, // GL 1.0
   GL_LIGHT6                                        = 0x4006, // GL 1.0
   GL_LIGHT7                                        = 0x4007, // GL 1.0
   GL_CONSTANT_COLOR                                = 0x8001, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_ONE_MINUS_CONSTANT_COLOR                      = 0x8002, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_CONSTANT_ALPHA                                = 0x8003, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_ONE_MINUS_CONSTANT_ALPHA                      = 0x8004, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_FUNC_ADD                                      = 0x8006, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_MIN                                           = 0x8007, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_MAX                                           = 0x8008, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_BLEND_EQUATION_RGB                            = 0x8009, // GL 2.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_FUNC_SUBTRACT                                 = 0x800A, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_FUNC_REVERSE_SUBTRACT                         = 0x800B, // GL 1.4, ARB_imaging, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_UNSIGNED_BYTE_3_3_2                           = 0x8032, // GL 1.2
   GL_UNSIGNED_SHORT_4_4_4_4                        = 0x8033, // GL 1.2
   GL_UNSIGNED_SHORT_5_5_5_1                        = 0x8034, // GL 1.2
   GL_UNSIGNED_INT_8_8_8_8                          = 0x8035, // GL 1.2
   GL_UNSIGNED_INT_10_10_10_2                       = 0x8036, // GL 1.2
   GL_POLYGON_OFFSET_FILL                           = 0x8037, // GL 1.1
   GL_POLYGON_OFFSET_FACTOR                         = 0x8038, // GL 1.1
   GL_RESCALE_NORMAL                                = 0x803A, // GL 1.2
   GL_ALPHA4                                        = 0x803B, // GL 1.1
   GL_ALPHA8                                        = 0x803C, // GL 1.1
   GL_ALPHA12                                       = 0x803D, // GL 1.1
   GL_ALPHA16                                       = 0x803E, // GL 1.1
   GL_LUMINANCE4                                    = 0x803F, // GL 1.1
   GL_LUMINANCE8                                    = 0x8040, // GL 1.1
   GL_LUMINANCE12                                   = 0x8041, // GL 1.1
   GL_LUMINANCE16                                   = 0x8042, // GL 1.1
   GL_LUMINANCE4_ALPHA4                             = 0x8043, // GL 1.1
   GL_LUMINANCE6_ALPHA2                             = 0x8044, // GL 1.1
   GL_LUMINANCE8_ALPHA8                             = 0x8045, // GL 1.1
   GL_LUMINANCE12_ALPHA4                            = 0x8046, // GL 1.1
   GL_LUMINANCE12_ALPHA12                           = 0x8047, // GL 1.1
   GL_LUMINANCE16_ALPHA16                           = 0x8048, // GL 1.1
   GL_INTENSITY                                     = 0x8049, // GL 1.1
   GL_INTENSITY4                                    = 0x804A, // GL 1.1
   GL_INTENSITY8                                    = 0x804B, // GL 1.1
   GL_INTENSITY12                                   = 0x804C, // GL 1.1
   GL_INTENSITY16                                   = 0x804D, // GL 1.1
   GL_RGB4                                          = 0x804F, // GL 1.1
   GL_RGB5                                          = 0x8050, // GL 1.1
   GL_RGB8                                          = 0x8051, // GL 1.1
   GL_RGB10                                         = 0x8052, // GL 1.1
   GL_RGB12                                         = 0x8053, // GL 1.1
   GL_RGB16                                         = 0x8054, // GL 1.1
   GL_RGBA2                                         = 0x8055, // GL 1.1
   GL_RGBA4                                         = 0x8056, // GL 1.1
   GL_RGB5_A1                                       = 0x8057, // GL 1.1
   GL_RGBA8                                         = 0x8058, // GL 1.1
   GL_RGB10_A2                                      = 0x8059, // GL 1.1
   GL_RGBA12                                        = 0x805A, // GL 1.1
   GL_RGBA16                                        = 0x805B, // GL 1.1
   GL_TEXTURE_RED_SIZE                              = 0x805C, // GL 1.1
   GL_TEXTURE_GREEN_SIZE                            = 0x805D, // GL 1.1
   GL_TEXTURE_BLUE_SIZE                             = 0x805E, // GL 1.1
   GL_TEXTURE_ALPHA_SIZE                            = 0x805F, // GL 1.1
   GL_TEXTURE_LUMINANCE_SIZE                        = 0x8060, // GL 1.1
   GL_TEXTURE_INTENSITY_SIZE                        = 0x8061, // GL 1.1
   GL_PROXY_TEXTURE_1D                              = 0x8063, // GL 1.1
   GL_PROXY_TEXTURE_2D                              = 0x8064, // GL 1.1
   GL_TEXTURE_PRIORITY                              = 0x8066, // GL 1.1
   GL_TEXTURE_RESIDENT                              = 0x8067, // GL 1.1
   GL_TEXTURE_BINDING_1D                            = 0x8068, // GL 1.1, GL 4.5, ARB_direct_state_access
   GL_TEXTURE_BINDING_2D                            = 0x8069, // GL 1.1, GL 4.5, ARB_direct_state_access
   GL_TEXTURE_BINDING_3D                            = 0x806A, // GL 1.2, GL 4.5, ARB_direct_state_access
   GL_PACK_SKIP_IMAGES                              = 0x806B, // GL 1.2
   GL_PACK_IMAGE_HEIGHT                             = 0x806C, // GL 1.2
   GL_UNPACK_SKIP_IMAGES                            = 0x806D, // GL 1.2
   GL_UNPACK_IMAGE_HEIGHT                           = 0x806E, // GL 1.2
   GL_TEXTURE_3D                                    = 0x806F, // GL 1.2, ARB_internalformat_query2, EXT_sparse_texture
   GL_PROXY_TEXTURE_3D                              = 0x8070, // GL 1.2
   GL_TEXTURE_DEPTH                                 = 0x8071, // GL 1.2
   GL_TEXTURE_WRAP_R                                = 0x8072, // GL 1.2
   GL_MAX_3D_TEXTURE_SIZE                           = 0x8073, // GL 1.2
   GL_VERTEX_ARRAY                                  = 0x8074, // GL 1.1, GL 4.3, KHR_debug
   GL_NORMAL_ARRAY                                  = 0x8075, // GL 1.1
   GL_COLOR_ARRAY                                   = 0x8076, // GL 1.1
   GL_INDEX_ARRAY                                   = 0x8077, // GL 1.1
   GL_TEXTURE_COORD_ARRAY                           = 0x8078, // GL 1.1
   GL_EDGE_FLAG_ARRAY                               = 0x8079, // GL 1.1
   GL_VERTEX_ARRAY_SIZE                             = 0x807A, // GL 1.1
   GL_VERTEX_ARRAY_TYPE                             = 0x807B, // GL 1.1
   GL_VERTEX_ARRAY_STRIDE                           = 0x807C, // GL 1.1
   GL_NORMAL_ARRAY_TYPE                             = 0x807E, // GL 1.1
   GL_NORMAL_ARRAY_STRIDE                           = 0x807F, // GL 1.1
   GL_COLOR_ARRAY_SIZE                              = 0x8081, // GL 1.1
   GL_COLOR_ARRAY_TYPE                              = 0x8082, // GL 1.1
   GL_COLOR_ARRAY_STRIDE                            = 0x8083, // GL 1.1
   GL_INDEX_ARRAY_TYPE                              = 0x8085, // GL 1.1
   GL_INDEX_ARRAY_STRIDE                            = 0x8086, // GL 1.1
   GL_TEXTURE_COORD_ARRAY_SIZE                      = 0x8088, // GL 1.1
   GL_TEXTURE_COORD_ARRAY_TYPE                      = 0x8089, // GL 1.1
   GL_TEXTURE_COORD_ARRAY_STRIDE                    = 0x808A, // GL 1.1
   GL_EDGE_FLAG_ARRAY_STRIDE                        = 0x808C, // GL 1.1
   GL_VERTEX_ARRAY_POINTER                          = 0x808E, // GL 1.1
   GL_NORMAL_ARRAY_POINTER                          = 0x808F, // GL 1.1
   GL_COLOR_ARRAY_POINTER                           = 0x8090, // GL 1.1
   GL_INDEX_ARRAY_POINTER                           = 0x8091, // GL 1.1
   GL_TEXTURE_COORD_ARRAY_POINTER                   = 0x8092, // GL 1.1
   GL_EDGE_FLAG_ARRAY_POINTER                       = 0x8093, // GL 1.1
   GL_MULTISAMPLE                                   = 0x809D, // GL 1.3
   GL_SAMPLE_ALPHA_TO_COVERAGE                      = 0x809E, // GL 1.3
   GL_SAMPLE_ALPHA_TO_ONE                           = 0x809F, // GL 1.3
   GL_SAMPLE_COVERAGE                               = 0x80A0, // GL 1.3
   GL_SAMPLE_BUFFERS                                = 0x80A8, // GL 1.3
   GL_SAMPLES                                       = 0x80A9, // GL 1.3, ARB_internalformat_query2
   GL_SAMPLE_COVERAGE_VALUE                         = 0x80AA, // GL 1.3
   GL_SAMPLE_COVERAGE_INVERT                        = 0x80AB, // GL 1.3
   GL_BLEND_DST_RGB                                 = 0x80C8, // GL 1.4, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_BLEND_SRC_RGB                                 = 0x80C9, // GL 1.4, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_BLEND_DST_ALPHA                               = 0x80CA, // GL 1.4, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_BLEND_SRC_ALPHA                               = 0x80CB, // GL 1.4, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_BGR                                           = 0x80E0, // GL 1.2
   GL_BGRA                                          = 0x80E1, // GL 1.2, ARB_vertex_array_bgra, EXT_vertex_array_bgra
   GL_MAX_ELEMENTS_VERTICES                         = 0x80E8, // GL 1.2
   GL_MAX_ELEMENTS_INDICES                          = 0x80E9, // GL 1.2
   GL_POINT_SIZE_MIN                                = 0x8126, // GL 1.4
   GL_POINT_SIZE_MAX                                = 0x8127, // GL 1.4
   GL_POINT_FADE_THRESHOLD_SIZE                     = 0x8128, // GL 1.4
   GL_POINT_DISTANCE_ATTENUATION                    = 0x8129, // GL 1.4
   GL_CLAMP_TO_BORDER                               = 0x812D, // GL 1.3
   GL_CLAMP_TO_EDGE                                 = 0x812F, // GL 1.2
   GL_TEXTURE_MIN_LOD                               = 0x813A, // GL 1.2
   GL_TEXTURE_MAX_LOD                               = 0x813B, // GL 1.2
   GL_TEXTURE_BASE_LEVEL                            = 0x813C, // GL 1.2
   GL_TEXTURE_MAX_LEVEL                             = 0x813D, // GL 1.2
   GL_GENERATE_MIPMAP                               = 0x8191, // GL 1.4
   GL_GENERATE_MIPMAP_HINT                          = 0x8192, // GL 1.4
   GL_DEPTH_COMPONENT16                             = 0x81A5, // GL 1.4, ANGLE_depth_texture
   GL_DEPTH_COMPONENT24                             = 0x81A6, // GL 1.4
   GL_DEPTH_COMPONENT32                             = 0x81A7, // GL 1.4
   GL_LIGHT_MODEL_COLOR_CONTROL                     = 0x81F8, // GL 1.2
   GL_SINGLE_COLOR                                  = 0x81F9, // GL 1.2
   GL_SEPARATE_SPECULAR_COLOR                       = 0x81FA, // GL 1.2
   GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING         = 0x8210, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE         = 0x8211, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE               = 0x8212, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE             = 0x8213, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE              = 0x8214, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE             = 0x8215, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE             = 0x8216, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE           = 0x8217, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_DEFAULT                           = 0x8218, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_UNDEFINED                         = 0x8219, // GL 3.0, ARB_framebuffer_object
   GL_DEPTH_STENCIL_ATTACHMENT                      = 0x821A, // GL 3.0, ARB_framebuffer_object
   GL_MAJOR_VERSION                                 = 0x821B, // GL 3.0
   GL_MINOR_VERSION                                 = 0x821C, // GL 3.0
   GL_NUM_EXTENSIONS                                = 0x821D, // GL 3.0
   GL_CONTEXT_FLAGS                                 = 0x821E, // GL 3.0
   GL_INDEX                                         = 0x8222, // GL 3.0 (compatibility), ARB_framebuffer_object (compatibility)
   GL_COMPRESSED_RED                                = 0x8225, // GL 3.0
   GL_COMPRESSED_RG                                 = 0x8226, // GL 3.0
   GL_RG                                            = 0x8227, // GL 3.0, ARB_texture_rg
   GL_RG_INTEGER                                    = 0x8228, // GL 3.0, ARB_texture_rg
   GL_R8                                            = 0x8229, // GL 3.0, ARB_texture_rg
   GL_R16                                           = 0x822A, // GL 3.0, ARB_texture_rg
   GL_RG8                                           = 0x822B, // GL 3.0, ARB_texture_rg
   GL_RG16                                          = 0x822C, // GL 3.0, ARB_texture_rg
   GL_R16F                                          = 0x822D, // GL 3.0, ARB_texture_rg
   GL_R32F                                          = 0x822E, // GL 3.0, ARB_texture_rg
   GL_RG16F                                         = 0x822F, // GL 3.0, ARB_texture_rg
   GL_RG32F                                         = 0x8230, // GL 3.0, ARB_texture_rg
   GL_R8I                                           = 0x8231, // GL 3.0, ARB_texture_rg
   GL_R8UI                                          = 0x8232, // GL 3.0, ARB_texture_rg
   GL_R16I                                          = 0x8233, // GL 3.0, ARB_texture_rg
   GL_R16UI                                         = 0x8234, // GL 3.0, ARB_texture_rg
   GL_R32I                                          = 0x8235, // GL 3.0, ARB_texture_rg
   GL_R32UI                                         = 0x8236, // GL 3.0, ARB_texture_rg
   GL_RG8I                                          = 0x8237, // GL 3.0, ARB_texture_rg
   GL_RG8UI                                         = 0x8238, // GL 3.0, AMD_interleaved_elements, ARB_texture_rg
   GL_RG16I                                         = 0x8239, // GL 3.0, ARB_texture_rg
   GL_RG16UI                                        = 0x823A, // GL 3.0, AMD_interleaved_elements, ARB_texture_rg
   GL_RG32I                                         = 0x823B, // GL 3.0, ARB_texture_rg
   GL_RG32UI                                        = 0x823C, // GL 3.0, ARB_texture_rg
   GL_DEBUG_OUTPUT_SYNCHRONOUS                      = 0x8242, // GL 4.3, KHR_debug
   GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH              = 0x8243, // GL 4.3, KHR_debug
   GL_DEBUG_CALLBACK_FUNCTION                       = 0x8244, // GL 4.3, KHR_debug
   GL_DEBUG_CALLBACK_USER_PARAM                     = 0x8245, // GL 4.3, KHR_debug
   GL_DEBUG_SOURCE_API                              = 0x8246, // GL 4.3, KHR_debug
   GL_DEBUG_SOURCE_WINDOW_SYSTEM                    = 0x8247, // GL 4.3, KHR_debug
   GL_DEBUG_SOURCE_SHADER_COMPILER                  = 0x8248, // GL 4.3, KHR_debug
   GL_DEBUG_SOURCE_THIRD_PARTY                      = 0x8249, // GL 4.3, KHR_debug
   GL_DEBUG_SOURCE_APPLICATION                      = 0x824A, // GL 4.3, KHR_debug
   GL_DEBUG_SOURCE_OTHER                            = 0x824B, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_ERROR                              = 0x824C, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR                = 0x824D, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR                 = 0x824E, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_PORTABILITY                        = 0x824F, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_PERFORMANCE                        = 0x8250, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_OTHER                              = 0x8251, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_MARKER                             = 0x8268, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_PUSH_GROUP                         = 0x8269, // GL 4.3, KHR_debug
   GL_DEBUG_TYPE_POP_GROUP                          = 0x826A, // GL 4.3, KHR_debug
   GL_DEBUG_SEVERITY_NOTIFICATION                   = 0x826B, // GL 4.3, KHR_debug
   GL_MAX_DEBUG_GROUP_STACK_DEPTH                   = 0x826C, // GL 4.3, KHR_debug
   GL_DEBUG_GROUP_STACK_DEPTH                       = 0x826D, // GL 4.3, KHR_debug
   GL_BUFFER                                        = 0x82E0, // GL 4.3, KHR_debug
   GL_SHADER                                        = 0x82E1, // GL 4.3, KHR_debug
   GL_PROGRAM                                       = 0x82E2, // GL 4.3, KHR_debug
   GL_QUERY                                         = 0x82E3, // GL 4.3, KHR_debug
   GL_PROGRAM_PIPELINE                              = 0x82E4, // GL 4.3, KHR_debug
   GL_SAMPLER                                       = 0x82E6, // GL 4.3, EXT_debug_label, KHR_debug
   GL_DISPLAY_LIST                                  = 0x82E7, // GL 4.3 (compatibility), KHR_debug (compatibility)
   GL_MAX_LABEL_LENGTH                              = 0x82E8, // GL 4.3, KHR_debug
   GL_UNSIGNED_BYTE_2_3_3_REV                       = 0x8362, // GL 1.2
   GL_UNSIGNED_SHORT_5_6_5                          = 0x8363, // GL 1.2
   GL_UNSIGNED_SHORT_5_6_5_REV                      = 0x8364, // GL 1.2
   GL_UNSIGNED_SHORT_4_4_4_4_REV                    = 0x8365, // GL 1.2
   GL_UNSIGNED_SHORT_1_5_5_5_REV                    = 0x8366, // GL 1.2
   GL_UNSIGNED_INT_8_8_8_8_REV                      = 0x8367, // GL 1.2
   GL_UNSIGNED_INT_2_10_10_10_REV                   = 0x8368, // GL 1.2, ARB_vertex_type_2_10_10_10_rev
   GL_MIRRORED_REPEAT                               = 0x8370, // GL 1.4
   GL_COMPRESSED_RGB_S3TC_DXT1_EXT                  = 0x83F0, // EXT_texture_compression_dxt1, EXT_texture_compression_s3tc
   GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                 = 0x83F1, // EXT_texture_compression_dxt1, EXT_texture_compression_s3tc
   GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                 = 0x83F2, // EXT_texture_compression_s3tc
   GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                 = 0x83F3, // EXT_texture_compression_s3tc
   GL_FOG_COORDINATE_SOURCE                         = 0x8450, // GL 1.4
   GL_FOG_COORD_SRC                                 = 0x8450, // Aliases GL_FOG_COORDINATE_SOURCE // GL 1.5
   GL_FOG_COORDINATE                                = 0x8451, // GL 1.4
   GL_FOG_COORD                                     = 0x8451, // Aliases GL_FOG_COORDINATE // GL 1.5
   GL_FRAGMENT_DEPTH                                = 0x8452, // GL 1.4
   GL_CURRENT_FOG_COORDINATE                        = 0x8453, // GL 1.4
   GL_CURRENT_FOG_COORD                             = 0x8453, // Aliases GL_CURRENT_FOG_COORDINATE // GL 1.5
   GL_FOG_COORDINATE_ARRAY_TYPE                     = 0x8454, // GL 1.4
   GL_FOG_COORD_ARRAY_TYPE                          = 0x8454, // Aliases GL_FOG_COORDINATE_ARRAY_TYPE // GL 1.5
   GL_FOG_COORDINATE_ARRAY_STRIDE                   = 0x8455, // GL 1.4
   GL_FOG_COORD_ARRAY_STRIDE                        = 0x8455, // Aliases GL_FOG_COORDINATE_ARRAY_STRIDE // GL 1.5
   GL_FOG_COORDINATE_ARRAY_POINTER                  = 0x8456, // GL 1.4
   GL_FOG_COORD_ARRAY_POINTER                       = 0x8456, // Aliases GL_FOG_COORDINATE_ARRAY_POINTER // GL 1.5
   GL_FOG_COORDINATE_ARRAY                          = 0x8457, // GL 1.4
   GL_FOG_COORD_ARRAY                               = 0x8457, // Aliases GL_FOG_COORDINATE_ARRAY // GL 1.5
   GL_COLOR_SUM                                     = 0x8458, // GL 1.4
   GL_CURRENT_SECONDARY_COLOR                       = 0x8459, // GL 1.4
   GL_SECONDARY_COLOR_ARRAY_SIZE                    = 0x845A, // GL 1.4
   GL_SECONDARY_COLOR_ARRAY_TYPE                    = 0x845B, // GL 1.4
   GL_SECONDARY_COLOR_ARRAY_STRIDE                  = 0x845C, // GL 1.4
   GL_SECONDARY_COLOR_ARRAY_POINTER                 = 0x845D, // GL 1.4
   GL_SECONDARY_COLOR_ARRAY                         = 0x845E, // GL 1.4
   GL_CURRENT_RASTER_SECONDARY_COLOR                = 0x845F, // GL 2.1
   GL_ALIASED_POINT_SIZE_RANGE                      = 0x846D, // GL 1.2
   GL_ALIASED_LINE_WIDTH_RANGE                      = 0x846E, // GL 1.2
   GL_TEXTURE0                                      = 0x84C0, // GL 1.3
   GL_TEXTURE1                                      = 0x84C1, // GL 1.3
   GL_TEXTURE2                                      = 0x84C2, // GL 1.3
   GL_TEXTURE3                                      = 0x84C3, // GL 1.3
   GL_TEXTURE4                                      = 0x84C4, // GL 1.3
   GL_TEXTURE5                                      = 0x84C5, // GL 1.3
   GL_TEXTURE6                                      = 0x84C6, // GL 1.3
   GL_TEXTURE7                                      = 0x84C7, // GL 1.3
   GL_TEXTURE8                                      = 0x84C8, // GL 1.3
   GL_TEXTURE9                                      = 0x84C9, // GL 1.3
   GL_TEXTURE10                                     = 0x84CA, // GL 1.3
   GL_TEXTURE11                                     = 0x84CB, // GL 1.3
   GL_TEXTURE12                                     = 0x84CC, // GL 1.3
   GL_TEXTURE13                                     = 0x84CD, // GL 1.3
   GL_TEXTURE14                                     = 0x84CE, // GL 1.3
   GL_TEXTURE15                                     = 0x84CF, // GL 1.3
   GL_TEXTURE16                                     = 0x84D0, // GL 1.3
   GL_TEXTURE17                                     = 0x84D1, // GL 1.3
   GL_TEXTURE18                                     = 0x84D2, // GL 1.3
   GL_TEXTURE19                                     = 0x84D3, // GL 1.3
   GL_TEXTURE20                                     = 0x84D4, // GL 1.3
   GL_TEXTURE21                                     = 0x84D5, // GL 1.3
   GL_TEXTURE22                                     = 0x84D6, // GL 1.3
   GL_TEXTURE23                                     = 0x84D7, // GL 1.3
   GL_TEXTURE24                                     = 0x84D8, // GL 1.3
   GL_TEXTURE25                                     = 0x84D9, // GL 1.3
   GL_TEXTURE26                                     = 0x84DA, // GL 1.3
   GL_TEXTURE27                                     = 0x84DB, // GL 1.3
   GL_TEXTURE28                                     = 0x84DC, // GL 1.3
   GL_TEXTURE29                                     = 0x84DD, // GL 1.3
   GL_TEXTURE30                                     = 0x84DE, // GL 1.3
   GL_TEXTURE31                                     = 0x84DF, // GL 1.3
   GL_ACTIVE_TEXTURE                                = 0x84E0, // GL 1.3
   GL_CLIENT_ACTIVE_TEXTURE                         = 0x84E1, // GL 1.3
   GL_MAX_TEXTURE_UNITS                             = 0x84E2, // GL 1.3
   GL_TRANSPOSE_MODELVIEW_MATRIX                    = 0x84E3, // GL 1.3
   GL_TRANSPOSE_PROJECTION_MATRIX                   = 0x84E4, // GL 1.3
   GL_TRANSPOSE_TEXTURE_MATRIX                      = 0x84E5, // GL 1.3
   GL_TRANSPOSE_COLOR_MATRIX                        = 0x84E6, // GL 1.3
   GL_SUBTRACT                                      = 0x84E7, // GL 1.3
   GL_MAX_RENDERBUFFER_SIZE                         = 0x84E8, // GL 3.0, ARB_framebuffer_object
   GL_COMPRESSED_ALPHA                              = 0x84E9, // GL 1.3
   GL_COMPRESSED_LUMINANCE                          = 0x84EA, // GL 1.3
   GL_COMPRESSED_LUMINANCE_ALPHA                    = 0x84EB, // GL 1.3
   GL_COMPRESSED_INTENSITY                          = 0x84EC, // GL 1.3
   GL_COMPRESSED_RGB                                = 0x84ED, // GL 1.3
   GL_COMPRESSED_RGBA                               = 0x84EE, // GL 1.3
   GL_TEXTURE_COMPRESSION_HINT                      = 0x84EF, // GL 1.3
   GL_TEXTURE_RECTANGLE                             = 0x84F5, // GL 3.1, ARB_internalformat_query2
   GL_TEXTURE_BINDING_RECTANGLE                     = 0x84F6, // GL 3.1, GL 4.5, ARB_direct_state_access
   GL_PROXY_TEXTURE_RECTANGLE                       = 0x84F7, // GL 3.1
   GL_MAX_RECTANGLE_TEXTURE_SIZE                    = 0x84F8, // GL 3.1
   GL_DEPTH_STENCIL                                 = 0x84F9, // GL 3.0, ARB_framebuffer_object
   GL_UNSIGNED_INT_24_8                             = 0x84FA, // GL 3.0, ARB_framebuffer_object
   GL_MAX_TEXTURE_LOD_BIAS                          = 0x84FD, // GL 1.4
   GL_TEXTURE_FILTER_CONTROL                        = 0x8500, // GL 1.4
   GL_TEXTURE_LOD_BIAS                              = 0x8501, // GL 1.4
   GL_INCR_WRAP                                     = 0x8507, // GL 1.4
   GL_DECR_WRAP                                     = 0x8508, // GL 1.4
   GL_NORMAL_MAP                                    = 0x8511, // GL 1.3
   GL_REFLECTION_MAP                                = 0x8512, // GL 1.3
   GL_TEXTURE_CUBE_MAP                              = 0x8513, // GL 1.3, ARB_internalformat_query2, EXT_sparse_texture
   GL_TEXTURE_BINDING_CUBE_MAP                      = 0x8514, // GL 1.3, GL 4.5, ARB_direct_state_access
   GL_TEXTURE_CUBE_MAP_POSITIVE_X                   = 0x8515, // GL 1.3
   GL_TEXTURE_CUBE_MAP_NEGATIVE_X                   = 0x8516, // GL 1.3
   GL_TEXTURE_CUBE_MAP_POSITIVE_Y                   = 0x8517, // GL 1.3
   GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                   = 0x8518, // GL 1.3
   GL_TEXTURE_CUBE_MAP_POSITIVE_Z                   = 0x8519, // GL 1.3
   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                   = 0x851A, // GL 1.3
   GL_PROXY_TEXTURE_CUBE_MAP                        = 0x851B, // GL 1.3
   GL_MAX_CUBE_MAP_TEXTURE_SIZE                     = 0x851C, // GL 1.3
   GL_COMBINE                                       = 0x8570, // GL 1.3
   GL_COMBINE_RGB                                   = 0x8571, // GL 1.3
   GL_COMBINE_ALPHA                                 = 0x8572, // GL 1.3
   GL_RGB_SCALE                                     = 0x8573, // GL 1.3
   GL_ADD_SIGNED                                    = 0x8574, // GL 1.3
   GL_INTERPOLATE                                   = 0x8575, // GL 1.3
   GL_CONSTANT                                      = 0x8576, // GL 1.3
   GL_PRIMARY_COLOR                                 = 0x8577, // GL 1.3, NV_path_rendering (compatibility)
   GL_PREVIOUS                                      = 0x8578, // GL 1.3
   GL_SOURCE0_RGB                                   = 0x8580, // GL 1.3
   GL_SRC0_RGB                                      = 0x8580, // Aliases GL_SOURCE0_RGB // GL 1.5
   GL_SOURCE1_RGB                                   = 0x8581, // GL 1.3
   GL_SRC1_RGB                                      = 0x8581, // Aliases GL_SOURCE1_RGB // GL 1.5
   GL_SOURCE2_RGB                                   = 0x8582, // GL 1.3
   GL_SRC2_RGB                                      = 0x8582, // Aliases GL_SOURCE2_RGB // GL 1.5
   GL_SOURCE0_ALPHA                                 = 0x8588, // GL 1.3
   GL_SRC0_ALPHA                                    = 0x8588, // Aliases GL_SOURCE0_ALPHA // GL 1.5
   GL_SOURCE1_ALPHA                                 = 0x8589, // GL 1.3
   GL_SRC1_ALPHA                                    = 0x8589, // Aliases GL_SOURCE1_ALPHA // GL 1.5, ARB_blend_func_extended
   GL_SOURCE2_ALPHA                                 = 0x858A, // GL 1.3
   GL_SRC2_ALPHA                                    = 0x858A, // Aliases GL_SOURCE2_ALPHA // GL 1.5
   GL_OPERAND0_RGB                                  = 0x8590, // GL 1.3
   GL_OPERAND1_RGB                                  = 0x8591, // GL 1.3
   GL_OPERAND2_RGB                                  = 0x8592, // GL 1.3
   GL_OPERAND0_ALPHA                                = 0x8598, // GL 1.3
   GL_OPERAND1_ALPHA                                = 0x8599, // GL 1.3
   GL_OPERAND2_ALPHA                                = 0x859A, // GL 1.3
   GL_VERTEX_ARRAY_BINDING                          = 0x85B5, // GL 3.0, ARB_vertex_array_object
   GL_VERTEX_ATTRIB_ARRAY_ENABLED                   = 0x8622, // GL 2.0
   GL_VERTEX_ATTRIB_ARRAY_SIZE                      = 0x8623, // GL 2.0
   GL_VERTEX_ATTRIB_ARRAY_STRIDE                    = 0x8624, // GL 2.0
   GL_VERTEX_ATTRIB_ARRAY_TYPE                      = 0x8625, // GL 2.0
   GL_CURRENT_VERTEX_ATTRIB                         = 0x8626, // GL 2.0
   GL_VERTEX_PROGRAM_POINT_SIZE                     = 0x8642, // GL 2.0
   GL_PROGRAM_POINT_SIZE                            = 0x8642, // Aliases GL_VERTEX_PROGRAM_POINT_SIZE // GL 3.2
   GL_VERTEX_PROGRAM_TWO_SIDE                       = 0x8643, // GL 2.0
   GL_VERTEX_ATTRIB_ARRAY_POINTER                   = 0x8645, // GL 2.0
   GL_DEPTH_CLAMP                                   = 0x864F, // GL 3.2, ARB_depth_clamp
   GL_TEXTURE_COMPRESSED_IMAGE_SIZE                 = 0x86A0, // GL 1.3
   GL_TEXTURE_COMPRESSED                            = 0x86A1, // GL 1.3, ARB_internalformat_query2
   GL_NUM_COMPRESSED_TEXTURE_FORMATS                = 0x86A2, // GL 1.3
   GL_COMPRESSED_TEXTURE_FORMATS                    = 0x86A3, // GL 1.3
   GL_DOT3_RGB                                      = 0x86AE, // GL 1.3
   GL_DOT3_RGBA                                     = 0x86AF, // GL 1.3
   GL_BUFFER_SIZE                                   = 0x8764, // GL 1.5
   GL_BUFFER_USAGE                                  = 0x8765, // GL 1.5
   GL_STENCIL_BACK_FUNC                             = 0x8800, // GL 2.0
   GL_STENCIL_BACK_FAIL                             = 0x8801, // GL 2.0
   GL_STENCIL_BACK_PASS_DEPTH_FAIL                  = 0x8802, // GL 2.0
   GL_STENCIL_BACK_PASS_DEPTH_PASS                  = 0x8803, // GL 2.0
   GL_RGBA32F                                       = 0x8814, // GL 3.0
   GL_RGB32F                                        = 0x8815, // GL 3.0, ARB_texture_buffer_object_rgb32
   GL_RGBA16F                                       = 0x881A, // GL 3.0
   GL_RGB16F                                        = 0x881B, // GL 3.0
   GL_MAX_DRAW_BUFFERS                              = 0x8824, // GL 2.0
   GL_DRAW_BUFFER0                                  = 0x8825, // GL 2.0
   GL_DRAW_BUFFER1                                  = 0x8826, // GL 2.0
   GL_DRAW_BUFFER2                                  = 0x8827, // GL 2.0
   GL_DRAW_BUFFER3                                  = 0x8828, // GL 2.0
   GL_DRAW_BUFFER4                                  = 0x8829, // GL 2.0
   GL_DRAW_BUFFER5                                  = 0x882A, // GL 2.0
   GL_DRAW_BUFFER6                                  = 0x882B, // GL 2.0
   GL_DRAW_BUFFER7                                  = 0x882C, // GL 2.0
   GL_DRAW_BUFFER8                                  = 0x882D, // GL 2.0
   GL_DRAW_BUFFER9                                  = 0x882E, // GL 2.0
   GL_DRAW_BUFFER10                                 = 0x882F, // GL 2.0
   GL_DRAW_BUFFER11                                 = 0x8830, // GL 2.0
   GL_DRAW_BUFFER12                                 = 0x8831, // GL 2.0
   GL_DRAW_BUFFER13                                 = 0x8832, // GL 2.0
   GL_DRAW_BUFFER14                                 = 0x8833, // GL 2.0
   GL_DRAW_BUFFER15                                 = 0x8834, // GL 2.0
   GL_BLEND_EQUATION_ALPHA                          = 0x883D, // GL 2.0, EXT_draw_buffers_indexed, OES_draw_buffers_indexed
   GL_TEXTURE_DEPTH_SIZE                            = 0x884A, // GL 1.4
   GL_DEPTH_TEXTURE_MODE                            = 0x884B, // GL 1.4
   GL_TEXTURE_COMPARE_MODE                          = 0x884C, // GL 1.4
   GL_TEXTURE_COMPARE_FUNC                          = 0x884D, // GL 1.4
   GL_COMPARE_R_TO_TEXTURE                          = 0x884E, // GL 1.4
   GL_COMPARE_REF_TO_TEXTURE                        = 0x884E, // Aliases GL_COMPARE_R_TO_TEXTURE // GL 3.0
   GL_TEXTURE_CUBE_MAP_SEAMLESS                     = 0x884F, // GL 3.2, AMD_seamless_cubemap_per_texture, ARB_seamless_cube_map, ARB_seamless_cubemap_per_texture
   GL_POINT_SPRITE                                  = 0x8861, // GL 2.0
   GL_COORD_REPLACE                                 = 0x8862, // GL 2.0
   GL_QUERY_COUNTER_BITS                            = 0x8864, // GL 1.5
   GL_CURRENT_QUERY                                 = 0x8865, // GL 1.5
   GL_QUERY_RESULT                                  = 0x8866, // GL 1.5
   GL_QUERY_RESULT_AVAILABLE                        = 0x8867, // GL 1.5
   GL_MAX_VERTEX_ATTRIBS                            = 0x8869, // GL 2.0
   GL_VERTEX_ATTRIB_ARRAY_NORMALIZED                = 0x886A, // GL 2.0
   GL_MAX_TEXTURE_COORDS                            = 0x8871, // GL 2.0
   GL_MAX_TEXTURE_IMAGE_UNITS                       = 0x8872, // GL 2.0
   GL_ARRAY_BUFFER                                  = 0x8892, // GL 1.5
   GL_ELEMENT_ARRAY_BUFFER                          = 0x8893, // GL 1.5
   GL_ARRAY_BUFFER_BINDING                          = 0x8894, // GL 1.5
   GL_ELEMENT_ARRAY_BUFFER_BINDING                  = 0x8895, // GL 1.5
   GL_VERTEX_ARRAY_BUFFER_BINDING                   = 0x8896, // GL 1.5
   GL_NORMAL_ARRAY_BUFFER_BINDING                   = 0x8897, // GL 1.5
   GL_COLOR_ARRAY_BUFFER_BINDING                    = 0x8898, // GL 1.5
   GL_INDEX_ARRAY_BUFFER_BINDING                    = 0x8899, // GL 1.5
   GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING            = 0x889A, // GL 1.5
   GL_EDGE_FLAG_ARRAY_BUFFER_BINDING                = 0x889B, // GL 1.5
   GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING          = 0x889C, // GL 1.5
   GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING           = 0x889D, // GL 1.5
   GL_FOG_COORD_ARRAY_BUFFER_BINDING                = 0x889D, // Aliases GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING // GL 1.5
   GL_WEIGHT_ARRAY_BUFFER_BINDING                   = 0x889E, // GL 1.5
   GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING            = 0x889F, // GL 1.5
   GL_READ_ONLY                                     = 0x88B8, // GL 1.5
   GL_WRITE_ONLY                                    = 0x88B9, // GL 1.5, NV_shader_buffer_store
   GL_READ_WRITE                                    = 0x88BA, // GL 1.5, NV_shader_buffer_store
   GL_BUFFER_ACCESS                                 = 0x88BB, // GL 1.5
   GL_BUFFER_MAPPED                                 = 0x88BC, // GL 1.5
   GL_BUFFER_MAP_POINTER                            = 0x88BD, // GL 1.5
   GL_TIME_ELAPSED                                  = 0x88BF, // GL 3.3, ARB_timer_query
   GL_STREAM_DRAW                                   = 0x88E0, // GL 1.5
   GL_STREAM_READ                                   = 0x88E1, // GL 1.5
   GL_STREAM_COPY                                   = 0x88E2, // GL 1.5
   GL_STATIC_DRAW                                   = 0x88E4, // GL 1.5
   GL_STATIC_READ                                   = 0x88E5, // GL 1.5
   GL_STATIC_COPY                                   = 0x88E6, // GL 1.5
   GL_DYNAMIC_DRAW                                  = 0x88E8, // GL 1.5
   GL_DYNAMIC_READ                                  = 0x88E9, // GL 1.5
   GL_DYNAMIC_COPY                                  = 0x88EA, // GL 1.5
   GL_PIXEL_PACK_BUFFER                             = 0x88EB, // GL 2.1
   GL_PIXEL_UNPACK_BUFFER                           = 0x88EC, // GL 2.1
   GL_PIXEL_PACK_BUFFER_BINDING                     = 0x88ED, // GL 2.1
   GL_PIXEL_UNPACK_BUFFER_BINDING                   = 0x88EF, // GL 2.1
   GL_DEPTH24_STENCIL8                              = 0x88F0, // GL 3.0, ARB_framebuffer_object
   GL_TEXTURE_STENCIL_SIZE                          = 0x88F1, // GL 3.0, ARB_framebuffer_object
   GL_SRC1_COLOR                                    = 0x88F9, // GL 3.3, ARB_blend_func_extended
   GL_ONE_MINUS_SRC1_COLOR                          = 0x88FA, // GL 3.3, ARB_blend_func_extended
   GL_ONE_MINUS_SRC1_ALPHA                          = 0x88FB, // GL 3.3, ARB_blend_func_extended
   GL_MAX_DUAL_SOURCE_DRAW_BUFFERS                  = 0x88FC, // GL 3.3, ARB_blend_func_extended
   GL_VERTEX_ATTRIB_ARRAY_INTEGER                   = 0x88FD, // GL 3.0
   GL_VERTEX_ATTRIB_ARRAY_DIVISOR                   = 0x88FE, // GL 3.3
   GL_MAX_ARRAY_TEXTURE_LAYERS                      = 0x88FF, // GL 3.0
   GL_MIN_PROGRAM_TEXEL_OFFSET                      = 0x8904, // GL 3.0
   GL_MAX_PROGRAM_TEXEL_OFFSET                      = 0x8905, // GL 3.0
   GL_SAMPLES_PASSED                                = 0x8914, // GL 1.5
   GL_GEOMETRY_VERTICES_OUT                         = 0x8916, // GL 3.2
   GL_GEOMETRY_INPUT_TYPE                           = 0x8917, // GL 3.2
   GL_GEOMETRY_OUTPUT_TYPE                          = 0x8918, // GL 3.2
   GL_SAMPLER_BINDING                               = 0x8919, // GL 3.3, ARB_sampler_objects
   GL_CLAMP_VERTEX_COLOR                            = 0x891A, // GL 3.0
   GL_CLAMP_FRAGMENT_COLOR                          = 0x891B, // GL 3.0
   GL_CLAMP_READ_COLOR                              = 0x891C, // GL 3.0
   GL_FIXED_ONLY                                    = 0x891D, // GL 3.0
   GL_UNIFORM_BUFFER                                = 0x8A11, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BUFFER_BINDING                        = 0x8A28, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BUFFER_START                          = 0x8A29, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BUFFER_SIZE                           = 0x8A2A, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_VERTEX_UNIFORM_BLOCKS                     = 0x8A2B, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_GEOMETRY_UNIFORM_BLOCKS                   = 0x8A2C, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_FRAGMENT_UNIFORM_BLOCKS                   = 0x8A2D, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_COMBINED_UNIFORM_BLOCKS                   = 0x8A2E, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_UNIFORM_BUFFER_BINDINGS                   = 0x8A2F, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_UNIFORM_BLOCK_SIZE                        = 0x8A30, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS        = 0x8A31, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS      = 0x8A32, // GL 3.1, ARB_uniform_buffer_object
   GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS      = 0x8A33, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT               = 0x8A34, // GL 3.1, ARB_uniform_buffer_object
   GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH          = 0x8A35, // GL 3.1, ARB_uniform_buffer_object
   GL_ACTIVE_UNIFORM_BLOCKS                         = 0x8A36, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_TYPE                                  = 0x8A37, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_SIZE                                  = 0x8A38, // GL 3.1, ARB_shader_subroutine, ARB_uniform_buffer_object
   GL_UNIFORM_NAME_LENGTH                           = 0x8A39, // GL 3.1, ARB_shader_subroutine, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_INDEX                           = 0x8A3A, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_OFFSET                                = 0x8A3B, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_ARRAY_STRIDE                          = 0x8A3C, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_MATRIX_STRIDE                         = 0x8A3D, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_IS_ROW_MAJOR                          = 0x8A3E, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_BINDING                         = 0x8A3F, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_DATA_SIZE                       = 0x8A40, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_NAME_LENGTH                     = 0x8A41, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS                 = 0x8A42, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES          = 0x8A43, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER     = 0x8A44, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER   = 0x8A45, // GL 3.1, ARB_uniform_buffer_object
   GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER   = 0x8A46, // GL 3.1, ARB_uniform_buffer_object
   GL_FRAGMENT_SHADER                               = 0x8B30, // GL 2.0
   GL_VERTEX_SHADER                                 = 0x8B31, // GL 2.0
   GL_MAX_FRAGMENT_UNIFORM_COMPONENTS               = 0x8B49, // GL 2.0
   GL_MAX_VERTEX_UNIFORM_COMPONENTS                 = 0x8B4A, // GL 2.0
   GL_MAX_VARYING_FLOATS                            = 0x8B4B, // GL 2.0
   GL_MAX_VARYING_COMPONENTS                        = 0x8B4B, // Aliases GL_MAX_VARYING_FLOATS // GL 3.0, ARB_geometry_shader4
   GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS                = 0x8B4C, // GL 2.0
   GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS              = 0x8B4D, // GL 2.0
   GL_SHADER_TYPE                                   = 0x8B4F, // GL 2.0
   GL_FLOAT_VEC2                                    = 0x8B50, // GL 2.0
   GL_FLOAT_VEC3                                    = 0x8B51, // GL 2.0
   GL_FLOAT_VEC4                                    = 0x8B52, // GL 2.0
   GL_INT_VEC2                                      = 0x8B53, // GL 2.0
   GL_INT_VEC3                                      = 0x8B54, // GL 2.0
   GL_INT_VEC4                                      = 0x8B55, // GL 2.0
   GL_BOOL                                          = 0x8B56, // GL 2.0
   GL_BOOL_VEC2                                     = 0x8B57, // GL 2.0
   GL_BOOL_VEC3                                     = 0x8B58, // GL 2.0
   GL_BOOL_VEC4                                     = 0x8B59, // GL 2.0
   GL_FLOAT_MAT2                                    = 0x8B5A, // GL 2.0
   GL_FLOAT_MAT3                                    = 0x8B5B, // GL 2.0
   GL_FLOAT_MAT4                                    = 0x8B5C, // GL 2.0
   GL_SAMPLER_1D                                    = 0x8B5D, // GL 2.0
   GL_SAMPLER_2D                                    = 0x8B5E, // GL 2.0
   GL_SAMPLER_3D                                    = 0x8B5F, // GL 2.0
   GL_SAMPLER_CUBE                                  = 0x8B60, // GL 2.0
   GL_SAMPLER_1D_SHADOW                             = 0x8B61, // GL 2.0
   GL_SAMPLER_2D_SHADOW                             = 0x8B62, // GL 2.0
   GL_SAMPLER_2D_RECT                               = 0x8B63, // GL 3.1
   GL_SAMPLER_2D_RECT_SHADOW                        = 0x8B64, // GL 3.1
   GL_FLOAT_MAT2x3                                  = 0x8B65, // GL 2.1
   GL_FLOAT_MAT2x4                                  = 0x8B66, // GL 2.1
   GL_FLOAT_MAT3x2                                  = 0x8B67, // GL 2.1
   GL_FLOAT_MAT3x4                                  = 0x8B68, // GL 2.1
   GL_FLOAT_MAT4x2                                  = 0x8B69, // GL 2.1
   GL_FLOAT_MAT4x3                                  = 0x8B6A, // GL 2.1
   GL_DELETE_STATUS                                 = 0x8B80, // GL 2.0
   GL_COMPILE_STATUS                                = 0x8B81, // GL 2.0
   GL_LINK_STATUS                                   = 0x8B82, // GL 2.0
   GL_VALIDATE_STATUS                               = 0x8B83, // GL 2.0
   GL_INFO_LOG_LENGTH                               = 0x8B84, // GL 2.0
   GL_ATTACHED_SHADERS                              = 0x8B85, // GL 2.0
   GL_ACTIVE_UNIFORMS                               = 0x8B86, // GL 2.0
   GL_ACTIVE_UNIFORM_MAX_LENGTH                     = 0x8B87, // GL 2.0
   GL_SHADER_SOURCE_LENGTH                          = 0x8B88, // GL 2.0
   GL_ACTIVE_ATTRIBUTES                             = 0x8B89, // GL 2.0
   GL_ACTIVE_ATTRIBUTE_MAX_LENGTH                   = 0x8B8A, // GL 2.0
   GL_FRAGMENT_SHADER_DERIVATIVE_HINT               = 0x8B8B, // GL 2.0
   GL_SHADING_LANGUAGE_VERSION                      = 0x8B8C, // GL 2.0
   GL_CURRENT_PROGRAM                               = 0x8B8D, // GL 2.0
   GL_TEXTURE_RED_TYPE                              = 0x8C10, // GL 3.0
   GL_TEXTURE_GREEN_TYPE                            = 0x8C11, // GL 3.0
   GL_TEXTURE_BLUE_TYPE                             = 0x8C12, // GL 3.0
   GL_TEXTURE_ALPHA_TYPE                            = 0x8C13, // GL 3.0
   GL_TEXTURE_LUMINANCE_TYPE                        = 0x8C14, // GL 3.0 (compatibility)
   GL_TEXTURE_INTENSITY_TYPE                        = 0x8C15, // GL 3.0 (compatibility)
   GL_TEXTURE_DEPTH_TYPE                            = 0x8C16, // GL 3.0
   GL_UNSIGNED_NORMALIZED                           = 0x8C17, // GL 3.0, ARB_framebuffer_object
   GL_TEXTURE_1D_ARRAY                              = 0x8C18, // GL 3.0, ARB_internalformat_query2
   GL_PROXY_TEXTURE_1D_ARRAY                        = 0x8C19, // GL 3.0
   GL_TEXTURE_2D_ARRAY                              = 0x8C1A, // GL 3.0, ARB_internalformat_query2, EXT_sparse_texture
   GL_PROXY_TEXTURE_2D_ARRAY                        = 0x8C1B, // GL 3.0
   GL_TEXTURE_BINDING_1D_ARRAY                      = 0x8C1C, // GL 3.0, GL 4.5, ARB_direct_state_access
   GL_TEXTURE_BINDING_2D_ARRAY                      = 0x8C1D, // GL 3.0, GL 4.5, ARB_direct_state_access
   GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS              = 0x8C29, // GL 3.2
   GL_TEXTURE_BUFFER                                = 0x8C2A, // GL 3.1, ARB_internalformat_query2
   GL_MAX_TEXTURE_BUFFER_SIZE                       = 0x8C2B, // GL 3.1
   GL_TEXTURE_BINDING_BUFFER                        = 0x8C2C, // GL 3.1, GL 4.5, ARB_direct_state_access
   GL_TEXTURE_BUFFER_DATA_STORE_BINDING             = 0x8C2D, // GL 3.1
   GL_ANY_SAMPLES_PASSED                            = 0x8C2F, // GL 3.3, ARB_occlusion_query2
   GL_R11F_G11F_B10F                                = 0x8C3A, // GL 3.0
   GL_UNSIGNED_INT_10F_11F_11F_REV                  = 0x8C3B, // GL 3.0, GL 4.4, ARB_vertex_type_10f_11f_11f_rev
   GL_RGB9_E5                                       = 0x8C3D, // GL 3.0
   GL_UNSIGNED_INT_5_9_9_9_REV                      = 0x8C3E, // GL 3.0
   GL_TEXTURE_SHARED_SIZE                           = 0x8C3F, // GL 3.0
   GL_SRGB                                          = 0x8C40, // GL 2.1
   GL_SRGB8                                         = 0x8C41, // GL 2.1
   GL_SRGB_ALPHA                                    = 0x8C42, // GL 2.1
   GL_SRGB8_ALPHA8                                  = 0x8C43, // GL 2.1
   GL_SLUMINANCE_ALPHA                              = 0x8C44, // GL 2.1
   GL_SLUMINANCE8_ALPHA8                            = 0x8C45, // GL 2.1
   GL_SLUMINANCE                                    = 0x8C46, // GL 2.1
   GL_SLUMINANCE8                                   = 0x8C47, // GL 2.1
   GL_COMPRESSED_SRGB                               = 0x8C48, // GL 2.1
   GL_COMPRESSED_SRGB_ALPHA                         = 0x8C49, // GL 2.1
   GL_COMPRESSED_SLUMINANCE                         = 0x8C4A, // GL 2.1
   GL_COMPRESSED_SLUMINANCE_ALPHA                   = 0x8C4B, // GL 2.1
   GL_COMPRESSED_SRGB_S3TC_DXT1_EXT                 = 0x8C4C, // EXT_texture_compression_s3tc_srgb, EXT_texture_sRGB
   GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT           = 0x8C4D, // EXT_texture_compression_s3tc_srgb, EXT_texture_sRGB
   GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT           = 0x8C4E, // EXT_texture_compression_s3tc_srgb, EXT_texture_sRGB
   GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT           = 0x8C4F, // EXT_texture_compression_s3tc_srgb, EXT_texture_sRGB
   GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH         = 0x8C76, // GL 3.0
   GL_TRANSFORM_FEEDBACK_BUFFER_MODE                = 0x8C7F, // GL 3.0
   GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS    = 0x8C80, // GL 3.0
   GL_TRANSFORM_FEEDBACK_VARYINGS                   = 0x8C83, // GL 3.0
   GL_TRANSFORM_FEEDBACK_BUFFER_START               = 0x8C84, // GL 3.0
   GL_TRANSFORM_FEEDBACK_BUFFER_SIZE                = 0x8C85, // GL 3.0
   GL_PRIMITIVES_GENERATED                          = 0x8C87, // GL 3.0
   GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN         = 0x8C88, // GL 3.0
   GL_RASTERIZER_DISCARD                            = 0x8C89, // GL 3.0
   GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A, // GL 3.0
   GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS       = 0x8C8B, // GL 3.0
   GL_INTERLEAVED_ATTRIBS                           = 0x8C8C, // GL 3.0
   GL_SEPARATE_ATTRIBS                              = 0x8C8D, // GL 3.0
   GL_TRANSFORM_FEEDBACK_BUFFER                     = 0x8C8E, // GL 3.0, GL 4.4, ARB_enhanced_layouts
   GL_TRANSFORM_FEEDBACK_BUFFER_BINDING             = 0x8C8F, // GL 3.0
   GL_POINT_SPRITE_COORD_ORIGIN                     = 0x8CA0, // GL 2.0
   GL_LOWER_LEFT                                    = 0x8CA1, // GL 2.0, GL 4.5, ARB_clip_control
   GL_UPPER_LEFT                                    = 0x8CA2, // GL 2.0, GL 4.5, ARB_clip_control
   GL_STENCIL_BACK_REF                              = 0x8CA3, // GL 2.0
   GL_STENCIL_BACK_VALUE_MASK                       = 0x8CA4, // GL 2.0
   GL_STENCIL_BACK_WRITEMASK                        = 0x8CA5, // GL 2.0
   GL_DRAW_FRAMEBUFFER_BINDING                      = 0x8CA6, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_BINDING                           = 0x8CA6, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_BINDING                          = 0x8CA7, // GL 3.0, ARB_framebuffer_object
   GL_READ_FRAMEBUFFER                              = 0x8CA8, // GL 3.0, ARB_framebuffer_object
   GL_DRAW_FRAMEBUFFER                              = 0x8CA9, // GL 3.0, ARB_framebuffer_object
   GL_READ_FRAMEBUFFER_BINDING                      = 0x8CAA, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_SAMPLES                          = 0x8CAB, // GL 3.0, ARB_framebuffer_object
   GL_DEPTH_COMPONENT32F                            = 0x8CAC, // GL 3.0, ARB_depth_buffer_float
   GL_DEPTH32F_STENCIL8                             = 0x8CAD, // GL 3.0, ARB_depth_buffer_float
   GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE            = 0x8CD0, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME            = 0x8CD1, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL          = 0x8CD2, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE  = 0x8CD3, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER          = 0x8CD4, // GL 3.0, ARB_framebuffer_object, ARB_geometry_shader4
   GL_FRAMEBUFFER_COMPLETE                          = 0x8CD5, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT             = 0x8CD6, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT     = 0x8CD7, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER            = 0x8CDB, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER            = 0x8CDC, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_UNSUPPORTED                       = 0x8CDD, // GL 3.0, ARB_framebuffer_object
   GL_MAX_COLOR_ATTACHMENTS                         = 0x8CDF, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT0                             = 0x8CE0, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT1                             = 0x8CE1, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT2                             = 0x8CE2, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT3                             = 0x8CE3, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT4                             = 0x8CE4, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT5                             = 0x8CE5, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT6                             = 0x8CE6, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT7                             = 0x8CE7, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT8                             = 0x8CE8, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT9                             = 0x8CE9, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT10                            = 0x8CEA, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT11                            = 0x8CEB, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT12                            = 0x8CEC, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT13                            = 0x8CED, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT14                            = 0x8CEE, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT15                            = 0x8CEF, // GL 3.0, ARB_framebuffer_object
   GL_COLOR_ATTACHMENT16                            = 0x8CF0, // GL 3.0
   GL_COLOR_ATTACHMENT17                            = 0x8CF1, // GL 3.0
   GL_COLOR_ATTACHMENT18                            = 0x8CF2, // GL 3.0
   GL_COLOR_ATTACHMENT19                            = 0x8CF3, // GL 3.0
   GL_COLOR_ATTACHMENT20                            = 0x8CF4, // GL 3.0
   GL_COLOR_ATTACHMENT21                            = 0x8CF5, // GL 3.0
   GL_COLOR_ATTACHMENT22                            = 0x8CF6, // GL 3.0
   GL_COLOR_ATTACHMENT23                            = 0x8CF7, // GL 3.0
   GL_COLOR_ATTACHMENT24                            = 0x8CF8, // GL 3.0
   GL_COLOR_ATTACHMENT25                            = 0x8CF9, // GL 3.0
   GL_COLOR_ATTACHMENT26                            = 0x8CFA, // GL 3.0
   GL_COLOR_ATTACHMENT27                            = 0x8CFB, // GL 3.0
   GL_COLOR_ATTACHMENT28                            = 0x8CFC, // GL 3.0
   GL_COLOR_ATTACHMENT29                            = 0x8CFD, // GL 3.0
   GL_COLOR_ATTACHMENT30                            = 0x8CFE, // GL 3.0
   GL_COLOR_ATTACHMENT31                            = 0x8CFF, // GL 3.0
   GL_DEPTH_ATTACHMENT                              = 0x8D00, // GL 3.0, ARB_framebuffer_object
   GL_STENCIL_ATTACHMENT                            = 0x8D20, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER                                   = 0x8D40, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER                                  = 0x8D41, // GL 3.0, ARB_framebuffer_object, ARB_internalformat_query2, NV_internalformat_sample_query
   GL_RENDERBUFFER_WIDTH                            = 0x8D42, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_HEIGHT                           = 0x8D43, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_INTERNAL_FORMAT                  = 0x8D44, // GL 3.0, ARB_framebuffer_object
   GL_STENCIL_INDEX1                                = 0x8D46, // GL 3.0, ARB_framebuffer_object
   GL_STENCIL_INDEX4                                = 0x8D47, // GL 3.0, ARB_framebuffer_object
   GL_STENCIL_INDEX8                                = 0x8D48, // GL 3.0, GL 4.4, ARB_framebuffer_object, ARB_texture_stencil8
   GL_STENCIL_INDEX16                               = 0x8D49, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_RED_SIZE                         = 0x8D50, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_GREEN_SIZE                       = 0x8D51, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_BLUE_SIZE                        = 0x8D52, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_ALPHA_SIZE                       = 0x8D53, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_DEPTH_SIZE                       = 0x8D54, // GL 3.0, ARB_framebuffer_object
   GL_RENDERBUFFER_STENCIL_SIZE                     = 0x8D55, // GL 3.0, ARB_framebuffer_object
   GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE            = 0x8D56, // GL 3.0, ARB_framebuffer_object
   GL_MAX_SAMPLES                                   = 0x8D57, // GL 3.0, ARB_framebuffer_object
   GL_RGB565                                        = 0x8D62, // GL 4.1, ARB_ES2_compatibility
   GL_RGBA32UI                                      = 0x8D70, // GL 3.0
   GL_RGB32UI                                       = 0x8D71, // GL 3.0, ARB_texture_buffer_object_rgb32
   GL_RGBA16UI                                      = 0x8D76, // GL 3.0
   GL_RGB16UI                                       = 0x8D77, // GL 3.0
   GL_RGBA8UI                                       = 0x8D7C, // GL 3.0, AMD_interleaved_elements
   GL_RGB8UI                                        = 0x8D7D, // GL 3.0
   GL_RGBA32I                                       = 0x8D82, // GL 3.0
   GL_RGB32I                                        = 0x8D83, // GL 3.0, ARB_texture_buffer_object_rgb32, ARB_vertex_attrib_64bit
   GL_RGBA16I                                       = 0x8D88, // GL 3.0
   GL_RGB16I                                        = 0x8D89, // GL 3.0
   GL_RGBA8I                                        = 0x8D8E, // GL 3.0
   GL_RGB8I                                         = 0x8D8F, // GL 3.0
   GL_RED_INTEGER                                   = 0x8D94, // GL 3.0
   GL_GREEN_INTEGER                                 = 0x8D95, // GL 3.0
   GL_BLUE_INTEGER                                  = 0x8D96, // GL 3.0
   GL_ALPHA_INTEGER                                 = 0x8D97, // GL 3.0
   GL_RGB_INTEGER                                   = 0x8D98, // GL 3.0
   GL_RGBA_INTEGER                                  = 0x8D99, // GL 3.0
   GL_BGR_INTEGER                                   = 0x8D9A, // GL 3.0
   GL_BGRA_INTEGER                                  = 0x8D9B, // GL 3.0
   GL_INT_2_10_10_10_REV                            = 0x8D9F, // GL 3.3, ARB_vertex_type_2_10_10_10_rev
   GL_FRAMEBUFFER_ATTACHMENT_LAYERED                = 0x8DA7, // GL 3.2
   GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS          = 0x8DA8, // GL 3.2
   GL_FLOAT_32_UNSIGNED_INT_24_8_REV                = 0x8DAD, // GL 3.0, ARB_depth_buffer_float
   GL_FRAMEBUFFER_SRGB                              = 0x8DB9, // GL 3.0, ARB_framebuffer_sRGB
   GL_COMPRESSED_RED_RGTC1                          = 0x8DBB, // GL 3.0, ARB_texture_compression_rgtc
   GL_COMPRESSED_SIGNED_RED_RGTC1                   = 0x8DBC, // GL 3.0, ARB_texture_compression_rgtc
   GL_COMPRESSED_RG_RGTC2                           = 0x8DBD, // GL 3.0, ARB_texture_compression_rgtc
   GL_COMPRESSED_SIGNED_RG_RGTC2                    = 0x8DBE, // GL 3.0, ARB_texture_compression_rgtc
   GL_SAMPLER_1D_ARRAY                              = 0x8DC0, // GL 3.0
   GL_SAMPLER_2D_ARRAY                              = 0x8DC1, // GL 3.0
   GL_SAMPLER_BUFFER                                = 0x8DC2, // GL 3.1
   GL_SAMPLER_1D_ARRAY_SHADOW                       = 0x8DC3, // GL 3.0
   GL_SAMPLER_2D_ARRAY_SHADOW                       = 0x8DC4, // GL 3.0
   GL_SAMPLER_CUBE_SHADOW                           = 0x8DC5, // GL 3.0
   GL_UNSIGNED_INT_VEC2                             = 0x8DC6, // GL 3.0
   GL_UNSIGNED_INT_VEC3                             = 0x8DC7, // GL 3.0
   GL_UNSIGNED_INT_VEC4                             = 0x8DC8, // GL 3.0
   GL_INT_SAMPLER_1D                                = 0x8DC9, // GL 3.0
   GL_INT_SAMPLER_2D                                = 0x8DCA, // GL 3.0
   GL_INT_SAMPLER_3D                                = 0x8DCB, // GL 3.0
   GL_INT_SAMPLER_CUBE                              = 0x8DCC, // GL 3.0
   GL_INT_SAMPLER_2D_RECT                           = 0x8DCD, // GL 3.1
   GL_INT_SAMPLER_1D_ARRAY                          = 0x8DCE, // GL 3.0
   GL_INT_SAMPLER_2D_ARRAY                          = 0x8DCF, // GL 3.0
   GL_INT_SAMPLER_BUFFER                            = 0x8DD0, // GL 3.1
   GL_UNSIGNED_INT_SAMPLER_1D                       = 0x8DD1, // GL 3.0
   GL_UNSIGNED_INT_SAMPLER_2D                       = 0x8DD2, // GL 3.0
   GL_UNSIGNED_INT_SAMPLER_3D                       = 0x8DD3, // GL 3.0
   GL_UNSIGNED_INT_SAMPLER_CUBE                     = 0x8DD4, // GL 3.0
   GL_UNSIGNED_INT_SAMPLER_2D_RECT                  = 0x8DD5, // GL 3.1
   GL_UNSIGNED_INT_SAMPLER_1D_ARRAY                 = 0x8DD6, // GL 3.0
   GL_UNSIGNED_INT_SAMPLER_2D_ARRAY                 = 0x8DD7, // GL 3.0
   GL_UNSIGNED_INT_SAMPLER_BUFFER                   = 0x8DD8, // GL 3.1
   GL_GEOMETRY_SHADER                               = 0x8DD9, // GL 3.2
   GL_MAX_GEOMETRY_UNIFORM_COMPONENTS               = 0x8DDF, // GL 3.2
   GL_MAX_GEOMETRY_OUTPUT_VERTICES                  = 0x8DE0, // GL 3.2
   GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS          = 0x8DE1, // GL 3.2
   GL_QUERY_WAIT                                    = 0x8E13, // GL 3.0
   GL_QUERY_NO_WAIT                                 = 0x8E14, // GL 3.0
   GL_QUERY_BY_REGION_WAIT                          = 0x8E15, // GL 3.0
   GL_QUERY_BY_REGION_NO_WAIT                       = 0x8E16, // GL 3.0
   GL_TIMESTAMP                                     = 0x8E28, // GL 3.3, ARB_timer_query
   GL_TEXTURE_SWIZZLE_R                             = 0x8E42, // GL 3.3, ARB_texture_swizzle
   GL_TEXTURE_SWIZZLE_G                             = 0x8E43, // GL 3.3, ARB_texture_swizzle
   GL_TEXTURE_SWIZZLE_B                             = 0x8E44, // GL 3.3, ARB_texture_swizzle
   GL_TEXTURE_SWIZZLE_A                             = 0x8E45, // GL 3.3, ARB_texture_swizzle
   GL_TEXTURE_SWIZZLE_RGBA                          = 0x8E46, // GL 3.3, ARB_texture_swizzle
   GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION      = 0x8E4C, // GL 3.2, ARB_provoking_vertex
   GL_FIRST_VERTEX_CONVENTION                       = 0x8E4D, // GL 3.2, ARB_provoking_vertex, ARB_viewport_array
   GL_LAST_VERTEX_CONVENTION                        = 0x8E4E, // GL 3.2, ARB_provoking_vertex, ARB_viewport_array
   GL_PROVOKING_VERTEX                              = 0x8E4F, // GL 3.2, ARB_provoking_vertex, ARB_viewport_array
   GL_SAMPLE_POSITION                               = 0x8E50, // GL 3.2, ARB_texture_multisample
   GL_SAMPLE_MASK                                   = 0x8E51, // GL 3.2, ARB_texture_multisample
   GL_SAMPLE_MASK_VALUE                             = 0x8E52, // GL 3.2, ARB_texture_multisample
   GL_MAX_SAMPLE_MASK_WORDS                         = 0x8E59, // GL 3.2, ARB_texture_multisample
   GL_COMPRESSED_RGBA_BPTC_UNORM                    = 0x8E8C, // GL 4.2
   GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM              = 0x8E8D, // GL 4.2
   GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT              = 0x8E8E, // GL 4.2
   GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT            = 0x8E8F, // GL 4.2
   GL_COPY_READ_BUFFER                              = 0x8F36, // GL 3.1, ARB_copy_buffer
   GL_COPY_WRITE_BUFFER                             = 0x8F37, // GL 3.1, ARB_copy_buffer
   GL_R8_SNORM                                      = 0x8F94, // GL 3.1, EXT_render_snorm, EXT_texture_snorm
   GL_RG8_SNORM                                     = 0x8F95, // GL 3.1, EXT_render_snorm, EXT_texture_snorm
   GL_RGB8_SNORM                                    = 0x8F96, // GL 3.1, EXT_texture_snorm
   GL_RGBA8_SNORM                                   = 0x8F97, // GL 3.1, EXT_render_snorm, EXT_texture_snorm
   GL_R16_SNORM                                     = 0x8F98, // GL 3.1, EXT_texture_snorm
   GL_RG16_SNORM                                    = 0x8F99, // GL 3.1, EXT_texture_snorm
   GL_RGB16_SNORM                                   = 0x8F9A, // GL 3.1, EXT_texture_snorm
   GL_RGBA16_SNORM                                  = 0x8F9B, // GL 3.1, EXT_texture_snorm
   GL_SIGNED_NORMALIZED                             = 0x8F9C, // GL 3.1, EXT_texture_snorm
   GL_PRIMITIVE_RESTART                             = 0x8F9D, // GL 3.1
   GL_PRIMITIVE_RESTART_INDEX                       = 0x8F9E, // GL 3.1
   GL_RGB10_A2UI                                    = 0x906F, // GL 3.3, ARB_texture_rgb10_a2ui
   GL_TEXTURE_2D_MULTISAMPLE                        = 0x9100, // GL 3.2, ARB_internalformat_query2, ARB_texture_multisample, NV_internalformat_sample_query
   GL_PROXY_TEXTURE_2D_MULTISAMPLE                  = 0x9101, // GL 3.2, ARB_texture_multisample
   GL_TEXTURE_2D_MULTISAMPLE_ARRAY                  = 0x9102, // GL 3.2, ARB_internalformat_query2, ARB_texture_multisample, NV_internalformat_sample_query
   GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY            = 0x9103, // GL 3.2, ARB_texture_multisample
   GL_TEXTURE_BINDING_2D_MULTISAMPLE                = 0x9104, // GL 3.2, GL 4.5, ARB_direct_state_access, ARB_texture_multisample
   GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY          = 0x9105, // GL 3.2, GL 4.5, ARB_direct_state_access, ARB_texture_multisample
   GL_TEXTURE_SAMPLES                               = 0x9106, // GL 3.2, ARB_texture_multisample
   GL_TEXTURE_FIXED_SAMPLE_LOCATIONS                = 0x9107, // GL 3.2, ARB_texture_multisample
   GL_SAMPLER_2D_MULTISAMPLE                        = 0x9108, // GL 3.2, ARB_texture_multisample
   GL_INT_SAMPLER_2D_MULTISAMPLE                    = 0x9109, // GL 3.2, ARB_texture_multisample
   GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE           = 0x910A, // GL 3.2, ARB_texture_multisample
   GL_SAMPLER_2D_MULTISAMPLE_ARRAY                  = 0x910B, // GL 3.2, ARB_texture_multisample
   GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY              = 0x910C, // GL 3.2, ARB_texture_multisample
   GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY     = 0x910D, // GL 3.2, ARB_texture_multisample
   GL_MAX_COLOR_TEXTURE_SAMPLES                     = 0x910E, // GL 3.2, ARB_texture_multisample
   GL_MAX_DEPTH_TEXTURE_SAMPLES                     = 0x910F, // GL 3.2, ARB_texture_multisample
   GL_MAX_INTEGER_SAMPLES                           = 0x9110, // GL 3.2, ARB_texture_multisample
   GL_MAX_SERVER_WAIT_TIMEOUT                       = 0x9111, // GL 3.2, ARB_sync
   GL_OBJECT_TYPE                                   = 0x9112, // GL 3.2, ARB_sync
   GL_SYNC_CONDITION                                = 0x9113, // GL 3.2, ARB_sync
   GL_SYNC_STATUS                                   = 0x9114, // GL 3.2, ARB_sync
   GL_SYNC_FLAGS                                    = 0x9115, // GL 3.2, ARB_sync
   GL_SYNC_FENCE                                    = 0x9116, // GL 3.2, ARB_sync
   GL_SYNC_GPU_COMMANDS_COMPLETE                    = 0x9117, // GL 3.2, ARB_sync
   GL_UNSIGNALED                                    = 0x9118, // GL 3.2, ARB_sync
   GL_SIGNALED                                      = 0x9119, // GL 3.2, ARB_sync
   GL_ALREADY_SIGNALED                              = 0x911A, // GL 3.2, ARB_sync
   GL_TIMEOUT_EXPIRED                               = 0x911B, // GL 3.2, ARB_sync
   GL_CONDITION_SATISFIED                           = 0x911C, // GL 3.2, ARB_sync
   GL_WAIT_FAILED                                   = 0x911D, // GL 3.2, ARB_sync
   GL_BUFFER_ACCESS_FLAGS                           = 0x911F, // GL 3.0
   GL_BUFFER_MAP_LENGTH                             = 0x9120, // GL 3.0
   GL_BUFFER_MAP_OFFSET                             = 0x9121, // GL 3.0
   GL_MAX_VERTEX_OUTPUT_COMPONENTS                  = 0x9122, // GL 3.2
   GL_MAX_GEOMETRY_INPUT_COMPONENTS                 = 0x9123, // GL 3.2
   GL_MAX_GEOMETRY_OUTPUT_COMPONENTS                = 0x9124, // GL 3.2
   GL_MAX_FRAGMENT_INPUT_COMPONENTS                 = 0x9125, // GL 3.2
   GL_CONTEXT_PROFILE_MASK                          = 0x9126, // GL 3.2
   GL_MAX_DEBUG_MESSAGE_LENGTH                      = 0x9143, // GL 4.3, KHR_debug
   GL_MAX_DEBUG_LOGGED_MESSAGES                     = 0x9144, // GL 4.3, KHR_debug
   GL_DEBUG_LOGGED_MESSAGES                         = 0x9145, // GL 4.3, KHR_debug
   GL_DEBUG_SEVERITY_HIGH                           = 0x9146, // GL 4.3, KHR_debug
   GL_DEBUG_SEVERITY_MEDIUM                         = 0x9147, // GL 4.3, KHR_debug
   GL_DEBUG_SEVERITY_LOW                            = 0x9148, // GL 4.3, KHR_debug
   GL_COMPRESSED_R11_EAC                            = 0x9270, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_SIGNED_R11_EAC                     = 0x9271, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_RG11_EAC                           = 0x9272, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_SIGNED_RG11_EAC                    = 0x9273, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_RGB8_ETC2                          = 0x9274, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_SRGB8_ETC2                         = 0x9275, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2      = 0x9276, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2     = 0x9277, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_RGBA8_ETC2_EAC                     = 0x9278, // GL 4.3, ARB_ES3_compatibility
   GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC              = 0x9279, // GL 4.3, ARB_ES3_compatibility
   GL_DEBUG_OUTPUT                                  = 0x92E0, // GL 4.3, KHR_debug
   GL_COMPRESSED_RGBA_ASTC_4x4_KHR                  = 0x93B0, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_5x4_KHR                  = 0x93B1, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_5x5_KHR                  = 0x93B2, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_6x5_KHR                  = 0x93B3, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_6x6_KHR                  = 0x93B4, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_8x5_KHR                  = 0x93B5, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_8x6_KHR                  = 0x93B6, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_8x8_KHR                  = 0x93B7, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_10x5_KHR                 = 0x93B8, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_10x6_KHR                 = 0x93B9, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_10x8_KHR                 = 0x93BA, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_10x10_KHR                = 0x93BB, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_12x10_KHR                = 0x93BC, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_RGBA_ASTC_12x12_KHR                = 0x93BD, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR          = 0x93D0, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR          = 0x93D1, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR          = 0x93D2, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR          = 0x93D3, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR          = 0x93D4, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR          = 0x93D5, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR          = 0x93D6, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR          = 0x93D7, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR         = 0x93D8, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR         = 0x93D9, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR         = 0x93DA, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR        = 0x93DB, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR        = 0x93DC, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
   GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR        = 0x93DD, // KHR_texture_compression_astc_hdr, KHR_texture_compression_astc_ldr, OES_texture_compression_astc
};

////////// COMMANDS //////////////////////////////////////////////////////////

// Defined by: GL 1.0
const GLubyte *glGetString(GLenum name) noexcept;

// Defined by: GL 1.0
void glTexCoord2fv(const GLfloat * v) noexcept;

// Defined by: GL 1.0
void glTexParameteri(GLenum target, GLenum pname, GLint param) noexcept;

// Vector equiv: glVertex2fv
// Defined by: GL 1.0
void glVertex2f(GLfloat x, GLfloat y) noexcept;

// Defined by: GL 1.0
void glEnable(GLenum cap) noexcept;

// Defined by: GL 1.0
void glBegin(GLenum mode) noexcept;

// Aliases: glBindTextureEXT
// Defined by: GL 1.1
void glBindTexture(GLenum target, GLuint texture) noexcept;

// Defined by: GL 1.0
void glClear(GLbitfield mask) noexcept;

// Defined by: GL 1.0
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) noexcept;

// Defined by: GL 1.0
void glColor3fv(const GLfloat * v) noexcept;

// Aliases: glDebugMessageCallbackARB, glDebugMessageCallbackKHR
// Defined by: GL 4.3, KHR_debug
void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam) noexcept;

// Defined by: GL 1.1
void glDeleteTextures(GLsizei n, const GLuint * textures) noexcept;

// Defined by: GL 1.0
void glEnd() noexcept;

// Defined by: GL 1.1
void glGenTextures(GLsizei n, GLuint * textures) noexcept;

// Defined by: GL 1.0
void glGetIntegerv(GLenum pname, GLint * data) noexcept;

// Defined by: GL 3.0
const GLubyte *glGetStringi(GLenum name, GLuint index) noexcept;

// Defined by: GL 1.0
void glPixelStorei(GLenum pname, GLint param) noexcept;

// Defined by: GL 1.0
void glTexEnvi(GLenum target, GLenum pname, GLint param) noexcept;

// Defined by: GL 1.0
void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) noexcept;

// Defined by: GL 1.0
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) noexcept;

} // be::gfx::gl

#if defined(BE_GFX_BGL_APIENTRY_DEFINED) && !defined(BE_GFX_BGL_IMPLEMENTATION)
#undef BE_GFX_BGL_APIENTRY_DEFINED
#undef APIENTRY
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef BE_GFX_BGL_IMPLEMENTATION

#include <glfw/glfw3.h>

namespace be::gfx::gl {

////////// BGL ///////////////////////////////////////////////////////////////

using GLGETSTRING_PROC = const GLubyte *(GLAPIENTRY*)(GLenum);
using GLTEXCOORD2FV_PROC = void (GLAPIENTRY*)(const GLfloat *);
using GLTEXPARAMETERI_PROC = void (GLAPIENTRY*)(GLenum, GLenum, GLint);
using GLVERTEX2F_PROC = void (GLAPIENTRY*)(GLfloat, GLfloat);
using GLENABLE_PROC = void (GLAPIENTRY*)(GLenum);
using GLBEGIN_PROC = void (GLAPIENTRY*)(GLenum);
using GLBINDTEXTURE_PROC = void (GLAPIENTRY*)(GLenum, GLuint);
using GLCLEAR_PROC = void (GLAPIENTRY*)(GLbitfield);
using GLCLEARCOLOR_PROC = void (GLAPIENTRY*)(GLfloat, GLfloat, GLfloat, GLfloat);
using GLCOLOR3FV_PROC = void (GLAPIENTRY*)(const GLfloat *);
using GLDEBUGMESSAGECALLBACK_PROC = void (GLAPIENTRY*)(GLDEBUGPROC, const void *);
using GLDELETETEXTURES_PROC = void (GLAPIENTRY*)(GLsizei, const GLuint *);
using GLEND_PROC = void (GLAPIENTRY*)();
using GLGENTEXTURES_PROC = void (GLAPIENTRY*)(GLsizei, GLuint *);
using GLGETINTEGERV_PROC = void (GLAPIENTRY*)(GLenum, GLint *);
using GLGETSTRINGI_PROC = const GLubyte *(GLAPIENTRY*)(GLenum, GLuint);
using GLPIXELSTOREI_PROC = void (GLAPIENTRY*)(GLenum, GLint);
using GLTEXENVI_PROC = void (GLAPIENTRY*)(GLenum, GLenum, GLint);
using GLTEXIMAGE2D_PROC = void (GLAPIENTRY*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
using GLVIEWPORT_PROC = void (GLAPIENTRY*)(GLint, GLint, GLsizei, GLsizei);

struct BglContext final {
   bool bgl_version_1_0 = false;
   bool bgl_version_1_1 = false;
   bool bgl_version_1_2 = false;
   bool bgl_version_1_3 = false;
   bool bgl_version_1_4 = false;
   bool bgl_version_1_5 = false;
   bool bgl_version_2_0 = false;
   bool bgl_version_2_1 = false;
   bool bgl_version_3_0 = false;
   bool bgl_version_3_1 = false;
   bool bgl_version_3_2 = false;
   bool bgl_version_3_3 = false;

   bool bgl_khr_debug = false;

   GLGETSTRING_PROC bglGetString = nullptr;
   GLTEXCOORD2FV_PROC bglTexCoord2fv = nullptr;
   GLTEXPARAMETERI_PROC bglTexParameteri = nullptr;
   GLVERTEX2F_PROC bglVertex2f = nullptr;
   GLENABLE_PROC bglEnable = nullptr;
   GLBEGIN_PROC bglBegin = nullptr;
   GLBINDTEXTURE_PROC bglBindTexture = nullptr;
   GLCLEAR_PROC bglClear = nullptr;
   GLCLEARCOLOR_PROC bglClearColor = nullptr;
   GLCOLOR3FV_PROC bglColor3fv = nullptr;
   GLDEBUGMESSAGECALLBACK_PROC bglDebugMessageCallback = nullptr;
   GLDELETETEXTURES_PROC bglDeleteTextures = nullptr;
   GLEND_PROC bglEnd = nullptr;
   GLGENTEXTURES_PROC bglGenTextures = nullptr;
   GLGETINTEGERV_PROC bglGetIntegerv = nullptr;
   GLGETSTRINGI_PROC bglGetStringi = nullptr;
   GLPIXELSTOREI_PROC bglPixelStorei = nullptr;
   GLTEXENVI_PROC bglTexEnvi = nullptr;
   GLTEXIMAGE2D_PROC bglTexImage2D = nullptr;
   GLVIEWPORT_PROC bglViewport = nullptr;

   static BglContextHandle make_handle() {
	  return BglContextHandle(new BglContext());
   }

   static BglContextHandle make_handle(const BglContext& ctx) {
	  return BglContextHandle(new BglContext(ctx));
   }
};

namespace {

#ifdef BE_GFX_BGL_MULTITHREADED
#ifdef BE_GFX_BGL_FAST_CONTEXT_SWITCH
thread_local BglContext const* bglctx = nullptr;
#define BE_GFX_BGL_CONTEXT (*bglctx)
#else
thread_local BglContext bglctx;
#define BE_GFX_BGL_CONTEXT bglctx
#endif
#else
#ifdef BE_GFX_BGL_FAST_CONTEXT_SWITCH
BglContext const* bglctx = nullptr;
#define BE_GFX_BGL_CONTEXT (*bglctx)
#else
BglContext bglctx;
#define BE_GFX_BGL_CONTEXT bglctx
#endif
#endif

constexpr U64 fnv_basis = 14695981039346656037ull;
constexpr U64 fnv_prime = 1099511628211ull;

//////////////////////////////////////////////////////////////////////////////
U64 hash_name(const char* ptr) {
   U64 v = fnv_basis;
   for (const char* it = ptr; *it; ++it) {
      v = (v ^ static_cast<U8>(*it)) * fnv_prime;
   }
   return v;
}

//////////////////////////////////////////////////////////////////////////////
U64 hash_name(const char* begin, const char* end) {
   U64 v = fnv_basis;
   for (const char* it = begin; it != end; ++it) {
      v = (v ^ static_cast<U8>(*it)) * fnv_prime;
   }
   return v;
}

//////////////////////////////////////////////////////////////////////////////
void check_extension(U64 hash) {
   BglContext& ctx = BE_GFX_BGL_CONTEXT;
   switch (hash)  {
      case U64(-1961367689909740958ll): ctx.bgl_khr_debug = ctx.bglDebugMessageCallback; break;
   }
}

} // ()

//////////////////////////////////////////////////////////////////////////////
void BglContextHandle::deleter::operator()(BglContext* ptr) {
   // Extra layer of indirection means BglContext can remain opaque outside of
   // the implementation file.
   delete ptr;
}

//////////////////////////////////////////////////////////////////////////////
const BglContext* BglContextHandle::get() const noexcept {
	return ptr_.get();
}

//////////////////////////////////////////////////////////////////////////////
BglContext* BglContextHandle::get() noexcept {
	return ptr_.get();
}

//////////////////////////////////////////////////////////////////////////////
BglContextHandle::BglContextHandle(BglContext* ptr)
   : ptr_(ptr, deleter()) { }

//////////////////////////////////////////////////////////////////////////////
BglContextHandle init_context() {
#ifdef BE_GFX_BGL_FAST_CONTEXT_SWITCH
   BglContextHandle BglContext::make_handle();
   bglctx = context.get();
   BglContext& ctx = context.get();
#else
   BglContextHandle context;
   bglctx = BglContext();
   BglContext& ctx = bglctx;
#endif

   using GLGETSTRING_PROC = const unsigned char* (GLAPIENTRY*)(GLenum);
   using GLGETSTRINGI_PROC = const unsigned char* (GLAPIENTRY*)(GLenum, unsigned int);
   using GLGETINTEGERV_PROC = void (GLAPIENTRY*)(GLenum, int *);

   auto getString = GLGETSTRING_PROC(glfwGetProcAddress("glGetString"));
   if (!getString) {
      throw std::system_error(std::make_error_code(std::errc::not_supported), "OpenGL context and/or driver not available!");
   }

   const unsigned char* version_string = getString(GL_VERSION);

   unsigned int major = 0, minor = 0;
   {
      unsigned int* vptr = &major;
      for (const unsigned char* it = version_string; *it; ++it) {
         const char c = (char)*it;
         if (c >= '0' && c <= '9') {
            *vptr = *vptr * 10 + c - '0';
         } else if (c == '.' && vptr == &major) {
            vptr = &minor;
         } else {
            break;
         }
      }
   }

   if (major == 0) {
      throw std::system_error(std::make_error_code(std::errc::not_supported), "OpenGL version could not be parsed!");
   }

   ctx.bglGetString = GLGETSTRING_PROC(glfwGetProcAddress("glGetString"));
   ctx.bglTexCoord2fv = GLTEXCOORD2FV_PROC(glfwGetProcAddress("glTexCoord2fv"));
   ctx.bglTexParameteri = GLTEXPARAMETERI_PROC(glfwGetProcAddress("glTexParameteri"));
   ctx.bglVertex2f = GLVERTEX2F_PROC(glfwGetProcAddress("glVertex2f"));
   ctx.bglEnable = GLENABLE_PROC(glfwGetProcAddress("glEnable"));
   ctx.bglBegin = GLBEGIN_PROC(glfwGetProcAddress("glBegin"));
   ctx.bglBindTexture = GLBINDTEXTURE_PROC(glfwGetProcAddress("glBindTexture"));
   ctx.bglClear = GLCLEAR_PROC(glfwGetProcAddress("glClear"));
   ctx.bglClearColor = GLCLEARCOLOR_PROC(glfwGetProcAddress("glClearColor"));
   ctx.bglColor3fv = GLCOLOR3FV_PROC(glfwGetProcAddress("glColor3fv"));
   ctx.bglDebugMessageCallback = GLDEBUGMESSAGECALLBACK_PROC(glfwGetProcAddress("glDebugMessageCallback"));
   ctx.bglDeleteTextures = GLDELETETEXTURES_PROC(glfwGetProcAddress("glDeleteTextures"));
   ctx.bglEnd = GLEND_PROC(glfwGetProcAddress("glEnd"));
   ctx.bglGenTextures = GLGENTEXTURES_PROC(glfwGetProcAddress("glGenTextures"));
   ctx.bglGetIntegerv = GLGETINTEGERV_PROC(glfwGetProcAddress("glGetIntegerv"));
   ctx.bglGetStringi = GLGETSTRINGI_PROC(glfwGetProcAddress("glGetStringi"));
   ctx.bglPixelStorei = GLPIXELSTOREI_PROC(glfwGetProcAddress("glPixelStorei"));
   ctx.bglTexEnvi = GLTEXENVI_PROC(glfwGetProcAddress("glTexEnvi"));
   ctx.bglTexImage2D = GLTEXIMAGE2D_PROC(glfwGetProcAddress("glTexImage2D"));
   ctx.bglViewport = GLVIEWPORT_PROC(glfwGetProcAddress("glViewport"));

   ctx.bgl_version_1_0 = (major > 1 || major == 1 && minor >= 0)
       && ctx.bglBegin && ctx.bglClear && ctx.bglClearColor && ctx.bglColor3fv && ctx.bglEnable
       && ctx.bglEnd && ctx.bglGetIntegerv && ctx.bglGetString && ctx.bglPixelStorei && ctx.bglTexCoord2fv
       && ctx.bglTexEnvi && ctx.bglTexImage2D && ctx.bglTexParameteri && ctx.bglVertex2f && ctx.bglViewport;
   ctx.bgl_version_1_1 = ctx.bgl_version_1_0 && (major > 1 || major == 1 && minor >= 1)
       && ctx.bglBindTexture && ctx.bglDeleteTextures && ctx.bglGenTextures;
   ctx.bgl_version_1_2 = ctx.bgl_version_1_1 && (major > 1 || major == 1 && minor >= 2);
   ctx.bgl_version_1_3 = ctx.bgl_version_1_2 && (major > 1 || major == 1 && minor >= 3);
   ctx.bgl_version_1_4 = ctx.bgl_version_1_3 && (major > 1 || major == 1 && minor >= 4);
   ctx.bgl_version_1_5 = ctx.bgl_version_1_4 && (major > 1 || major == 1 && minor >= 5);
   ctx.bgl_version_2_0 = ctx.bgl_version_1_5 && (major > 2 || major == 2 && minor >= 0);
   ctx.bgl_version_2_1 = ctx.bgl_version_2_0 && (major > 2 || major == 2 && minor >= 1);
   ctx.bgl_version_3_0 = ctx.bgl_version_2_1 && (major > 3 || major == 3 && minor >= 0)
       && ctx.bglGetStringi;
   ctx.bgl_version_3_1 = ctx.bgl_version_3_0 && (major > 3 || major == 3 && minor >= 1);
   ctx.bgl_version_3_2 = ctx.bgl_version_3_1 && (major > 3 || major == 3 && minor >= 2);
   ctx.bgl_version_3_3 = ctx.bgl_version_3_2 && (major > 3 || major == 3 && minor >= 3);

   if (major >= 3) {
      auto getIntegerv = GLGETINTEGERV_PROC(glfwGetProcAddress("glGetIntegerv"));
      auto getStringi = GLGETSTRINGI_PROC(glfwGetProcAddress("glGetStringi"));

      if (getIntegerv && getStringi) {
         int num_extensions = 0;
         getIntegerv(GL_NUM_EXTENSIONS, &num_extensions);

         for (int i = 0; i < num_extensions; ++i) {
            const char* extension = (const char*)getStringi(GL_EXTENSIONS, i);
            if (extension) {
               check_extension(hash_name(extension));
            }
         }
      }
   } else {
      const char* extensions = (const char*)getString(GL_EXTENSIONS);
      if (extensions) {
         for (const char* begin = extensions, *it = extensions; ; ++it) {
            char c = *it;
            if (c == ' ') {
               check_extension(hash_name(begin, it));
               begin = it + 1;
            } else if (c == '\0') {
               check_extension(hash_name(begin, it));
               break;
            }
         }
      }
   }

#ifndef BE_GFX_BGL_FAST_CONTEXT_SWITCH
   context = BglContext::make_handle(ctx);
#endif
   return context;
}

//////////////////////////////////////////////////////////////////////////////
void switch_context(const BglContextHandle& context) noexcept {
#ifdef BE_GFX_BGL_FAST_CONTEXT_SWITCH
   bglctx = context.get();
#else
   bglctx = *context.get();
#endif
}

//////////////////////////////////////////////////////////////////////////////
const char* enum_name (GLenum e) noexcept {
   switch (e) {
      case 0: return "GL_FALSE";
      case 0x00000001: return "GL_CURRENT_BIT";
      case 0x00000002: return "GL_POINT_BIT";
      case 0x0003: return "GL_LINE_STRIP";
      case 0x00000004: return "GL_LINE_BIT";
      case 0x0005: return "GL_TRIANGLE_STRIP";
      case 0x0006: return "GL_TRIANGLE_FAN";
      case 0x0007: return "GL_QUADS";
      case 0x00000008: return "GL_POLYGON_BIT";
      case 0x0009: return "GL_POLYGON";
      case 0x000A: return "GL_LINES_ADJACENCY";
      case 0x000B: return "GL_LINE_STRIP_ADJACENCY";
      case 0x000C: return "GL_TRIANGLES_ADJACENCY";
      case 0x000D: return "GL_TRIANGLE_STRIP_ADJACENCY";
      case 0x00000010: return "GL_POLYGON_STIPPLE_BIT";
      case 0x00000020: return "GL_PIXEL_MODE_BIT";
      case 0x00000040: return "GL_LIGHTING_BIT";
      case 0x00000080: return "GL_FOG_BIT";
      case 0x00000100: return "GL_DEPTH_BUFFER_BIT";
      case 0x0101: return "GL_LOAD";
      case 0x0102: return "GL_RETURN";
      case 0x0103: return "GL_MULT";
      case 0x0104: return "GL_ADD";
      case 0x00000200: return "GL_ACCUM_BUFFER_BIT";
      case 0x0201: return "GL_LESS";
      case 0x0202: return "GL_EQUAL";
      case 0x0203: return "GL_LEQUAL";
      case 0x0204: return "GL_GREATER";
      case 0x0205: return "GL_NOTEQUAL";
      case 0x0206: return "GL_GEQUAL";
      case 0x0207: return "GL_ALWAYS";
      case 0x0300: return "GL_SRC_COLOR";
      case 0x0301: return "GL_ONE_MINUS_SRC_COLOR";
      case 0x0302: return "GL_SRC_ALPHA";
      case 0x0303: return "GL_ONE_MINUS_SRC_ALPHA";
      case 0x0304: return "GL_DST_ALPHA";
      case 0x0305: return "GL_ONE_MINUS_DST_ALPHA";
      case 0x0306: return "GL_DST_COLOR";
      case 0x0307: return "GL_ONE_MINUS_DST_COLOR";
      case 0x0308: return "GL_SRC_ALPHA_SATURATE";
      case 0x00000400: return "GL_STENCIL_BUFFER_BIT";
      case 0x0401: return "GL_FRONT_RIGHT";
      case 0x0402: return "GL_BACK_LEFT";
      case 0x0403: return "GL_BACK_RIGHT";
      case 0x0404: return "GL_FRONT";
      case 0x0405: return "GL_BACK";
      case 0x0406: return "GL_LEFT";
      case 0x0407: return "GL_RIGHT";
      case 0x0408: return "GL_FRONT_AND_BACK";
      case 0x0409: return "GL_AUX0";
      case 0x040A: return "GL_AUX1";
      case 0x040B: return "GL_AUX2";
      case 0x040C: return "GL_AUX3";
      case 0x0500: return "GL_INVALID_ENUM";
      case 0x0501: return "GL_INVALID_VALUE";
      case 0x0502: return "GL_INVALID_OPERATION";
      case 0x0503: return "GL_STACK_OVERFLOW";
      case 0x0504: return "GL_STACK_UNDERFLOW";
      case 0x0505: return "GL_OUT_OF_MEMORY";
      case 0x0506: return "GL_INVALID_FRAMEBUFFER_OPERATION";
      case 0x0600: return "GL_2D";
      case 0x0601: return "GL_3D";
      case 0x0602: return "GL_3D_COLOR";
      case 0x0603: return "GL_3D_COLOR_TEXTURE";
      case 0x0604: return "GL_4D_COLOR_TEXTURE";
      case 0x0700: return "GL_PASS_THROUGH_TOKEN";
      case 0x0701: return "GL_POINT_TOKEN";
      case 0x0702: return "GL_LINE_TOKEN";
      case 0x0703: return "GL_POLYGON_TOKEN";
      case 0x0704: return "GL_BITMAP_TOKEN";
      case 0x0705: return "GL_DRAW_PIXEL_TOKEN";
      case 0x0706: return "GL_COPY_PIXEL_TOKEN";
      case 0x0707: return "GL_LINE_RESET_TOKEN";
      case 0x00000800: return "GL_VIEWPORT_BIT";
      case 0x0801: return "GL_EXP2";
      case 0x0900: return "GL_CW";
      case 0x0901: return "GL_CCW";
      case 0x0A00: return "GL_COEFF";
      case 0x0A01: return "GL_ORDER";
      case 0x0A02: return "GL_DOMAIN";
      case 0x0B00: return "GL_CURRENT_COLOR";
      case 0x0B01: return "GL_CURRENT_INDEX";
      case 0x0B02: return "GL_CURRENT_NORMAL";
      case 0x0B03: return "GL_CURRENT_TEXTURE_COORDS";
      case 0x0B04: return "GL_CURRENT_RASTER_COLOR";
      case 0x0B05: return "GL_CURRENT_RASTER_INDEX";
      case 0x0B06: return "GL_CURRENT_RASTER_TEXTURE_COORDS";
      case 0x0B07: return "GL_CURRENT_RASTER_POSITION";
      case 0x0B08: return "GL_CURRENT_RASTER_POSITION_VALID";
      case 0x0B09: return "GL_CURRENT_RASTER_DISTANCE";
      case 0x0B10: return "GL_POINT_SMOOTH";
      case 0x0B11: return "GL_POINT_SIZE";
      case 0x0B12: return "GL_POINT_SIZE_RANGE";
      case 0x0B13: return "GL_POINT_SIZE_GRANULARITY";
      case 0x0B20: return "GL_LINE_SMOOTH";
      case 0x0B21: return "GL_LINE_WIDTH";
      case 0x0B22: return "GL_LINE_WIDTH_RANGE";
      case 0x0B23: return "GL_LINE_WIDTH_GRANULARITY";
      case 0x0B24: return "GL_LINE_STIPPLE";
      case 0x0B25: return "GL_LINE_STIPPLE_PATTERN";
      case 0x0B26: return "GL_LINE_STIPPLE_REPEAT";
      case 0x0B30: return "GL_LIST_MODE";
      case 0x0B31: return "GL_MAX_LIST_NESTING";
      case 0x0B32: return "GL_LIST_BASE";
      case 0x0B33: return "GL_LIST_INDEX";
      case 0x0B40: return "GL_POLYGON_MODE";
      case 0x0B41: return "GL_POLYGON_SMOOTH";
      case 0x0B42: return "GL_POLYGON_STIPPLE";
      case 0x0B43: return "GL_EDGE_FLAG";
      case 0x0B44: return "GL_CULL_FACE";
      case 0x0B45: return "GL_CULL_FACE_MODE";
      case 0x0B46: return "GL_FRONT_FACE";
      case 0x0B50: return "GL_LIGHTING";
      case 0x0B51: return "GL_LIGHT_MODEL_LOCAL_VIEWER";
      case 0x0B52: return "GL_LIGHT_MODEL_TWO_SIDE";
      case 0x0B53: return "GL_LIGHT_MODEL_AMBIENT";
      case 0x0B54: return "GL_SHADE_MODEL";
      case 0x0B55: return "GL_COLOR_MATERIAL_FACE";
      case 0x0B56: return "GL_COLOR_MATERIAL_PARAMETER";
      case 0x0B57: return "GL_COLOR_MATERIAL";
      case 0x0B60: return "GL_FOG";
      case 0x0B61: return "GL_FOG_INDEX";
      case 0x0B62: return "GL_FOG_DENSITY";
      case 0x0B63: return "GL_FOG_START";
      case 0x0B64: return "GL_FOG_END";
      case 0x0B65: return "GL_FOG_MODE";
      case 0x0B66: return "GL_FOG_COLOR";
      case 0x0B70: return "GL_DEPTH_RANGE";
      case 0x0B71: return "GL_DEPTH_TEST";
      case 0x0B72: return "GL_DEPTH_WRITEMASK";
      case 0x0B73: return "GL_DEPTH_CLEAR_VALUE";
      case 0x0B74: return "GL_DEPTH_FUNC";
      case 0x0B80: return "GL_ACCUM_CLEAR_VALUE";
      case 0x0B90: return "GL_STENCIL_TEST";
      case 0x0B91: return "GL_STENCIL_CLEAR_VALUE";
      case 0x0B92: return "GL_STENCIL_FUNC";
      case 0x0B93: return "GL_STENCIL_VALUE_MASK";
      case 0x0B94: return "GL_STENCIL_FAIL";
      case 0x0B95: return "GL_STENCIL_PASS_DEPTH_FAIL";
      case 0x0B96: return "GL_STENCIL_PASS_DEPTH_PASS";
      case 0x0B97: return "GL_STENCIL_REF";
      case 0x0B98: return "GL_STENCIL_WRITEMASK";
      case 0x0BA0: return "GL_MATRIX_MODE";
      case 0x0BA1: return "GL_NORMALIZE";
      case 0x0BA2: return "GL_VIEWPORT";
      case 0x0BA3: return "GL_MODELVIEW_STACK_DEPTH";
      case 0x0BA4: return "GL_PROJECTION_STACK_DEPTH";
      case 0x0BA5: return "GL_TEXTURE_STACK_DEPTH";
      case 0x0BA6: return "GL_MODELVIEW_MATRIX";
      case 0x0BA7: return "GL_PROJECTION_MATRIX";
      case 0x0BA8: return "GL_TEXTURE_MATRIX";
      case 0x0BB0: return "GL_ATTRIB_STACK_DEPTH";
      case 0x0BB1: return "GL_CLIENT_ATTRIB_STACK_DEPTH";
      case 0x0BC0: return "GL_ALPHA_TEST";
      case 0x0BC1: return "GL_ALPHA_TEST_FUNC";
      case 0x0BC2: return "GL_ALPHA_TEST_REF";
      case 0x0BD0: return "GL_DITHER";
      case 0x0BE0: return "GL_BLEND_DST";
      case 0x0BE1: return "GL_BLEND_SRC";
      case 0x0BE2: return "GL_BLEND";
      case 0x0BF0: return "GL_LOGIC_OP_MODE";
      case 0x0BF1: return "GL_INDEX_LOGIC_OP";
      case 0x0BF2: return "GL_COLOR_LOGIC_OP";
      case 0x0C00: return "GL_AUX_BUFFERS";
      case 0x0C01: return "GL_DRAW_BUFFER";
      case 0x0C02: return "GL_READ_BUFFER";
      case 0x0C10: return "GL_SCISSOR_BOX";
      case 0x0C11: return "GL_SCISSOR_TEST";
      case 0x0C20: return "GL_INDEX_CLEAR_VALUE";
      case 0x0C21: return "GL_INDEX_WRITEMASK";
      case 0x0C22: return "GL_COLOR_CLEAR_VALUE";
      case 0x0C23: return "GL_COLOR_WRITEMASK";
      case 0x0C30: return "GL_INDEX_MODE";
      case 0x0C31: return "GL_RGBA_MODE";
      case 0x0C32: return "GL_DOUBLEBUFFER";
      case 0x0C33: return "GL_STEREO";
      case 0x0C40: return "GL_RENDER_MODE";
      case 0x0C50: return "GL_PERSPECTIVE_CORRECTION_HINT";
      case 0x0C51: return "GL_POINT_SMOOTH_HINT";
      case 0x0C52: return "GL_LINE_SMOOTH_HINT";
      case 0x0C53: return "GL_POLYGON_SMOOTH_HINT";
      case 0x0C54: return "GL_FOG_HINT";
      case 0x0C60: return "GL_TEXTURE_GEN_S";
      case 0x0C61: return "GL_TEXTURE_GEN_T";
      case 0x0C62: return "GL_TEXTURE_GEN_R";
      case 0x0C63: return "GL_TEXTURE_GEN_Q";
      case 0x0C70: return "GL_PIXEL_MAP_I_TO_I";
      case 0x0C71: return "GL_PIXEL_MAP_S_TO_S";
      case 0x0C72: return "GL_PIXEL_MAP_I_TO_R";
      case 0x0C73: return "GL_PIXEL_MAP_I_TO_G";
      case 0x0C74: return "GL_PIXEL_MAP_I_TO_B";
      case 0x0C75: return "GL_PIXEL_MAP_I_TO_A";
      case 0x0C76: return "GL_PIXEL_MAP_R_TO_R";
      case 0x0C77: return "GL_PIXEL_MAP_G_TO_G";
      case 0x0C78: return "GL_PIXEL_MAP_B_TO_B";
      case 0x0C79: return "GL_PIXEL_MAP_A_TO_A";
      case 0x0CB0: return "GL_PIXEL_MAP_I_TO_I_SIZE";
      case 0x0CB1: return "GL_PIXEL_MAP_S_TO_S_SIZE";
      case 0x0CB2: return "GL_PIXEL_MAP_I_TO_R_SIZE";
      case 0x0CB3: return "GL_PIXEL_MAP_I_TO_G_SIZE";
      case 0x0CB4: return "GL_PIXEL_MAP_I_TO_B_SIZE";
      case 0x0CB5: return "GL_PIXEL_MAP_I_TO_A_SIZE";
      case 0x0CB6: return "GL_PIXEL_MAP_R_TO_R_SIZE";
      case 0x0CB7: return "GL_PIXEL_MAP_G_TO_G_SIZE";
      case 0x0CB8: return "GL_PIXEL_MAP_B_TO_B_SIZE";
      case 0x0CB9: return "GL_PIXEL_MAP_A_TO_A_SIZE";
      case 0x0CF0: return "GL_UNPACK_SWAP_BYTES";
      case 0x0CF1: return "GL_UNPACK_LSB_FIRST";
      case 0x0CF2: return "GL_UNPACK_ROW_LENGTH";
      case 0x0CF3: return "GL_UNPACK_SKIP_ROWS";
      case 0x0CF4: return "GL_UNPACK_SKIP_PIXELS";
      case 0x0CF5: return "GL_UNPACK_ALIGNMENT";
      case 0x0D00: return "GL_PACK_SWAP_BYTES";
      case 0x0D01: return "GL_PACK_LSB_FIRST";
      case 0x0D02: return "GL_PACK_ROW_LENGTH";
      case 0x0D03: return "GL_PACK_SKIP_ROWS";
      case 0x0D04: return "GL_PACK_SKIP_PIXELS";
      case 0x0D05: return "GL_PACK_ALIGNMENT";
      case 0x0D10: return "GL_MAP_COLOR";
      case 0x0D11: return "GL_MAP_STENCIL";
      case 0x0D12: return "GL_INDEX_SHIFT";
      case 0x0D13: return "GL_INDEX_OFFSET";
      case 0x0D14: return "GL_RED_SCALE";
      case 0x0D15: return "GL_RED_BIAS";
      case 0x0D16: return "GL_ZOOM_X";
      case 0x0D17: return "GL_ZOOM_Y";
      case 0x0D18: return "GL_GREEN_SCALE";
      case 0x0D19: return "GL_GREEN_BIAS";
      case 0x0D1A: return "GL_BLUE_SCALE";
      case 0x0D1B: return "GL_BLUE_BIAS";
      case 0x0D1C: return "GL_ALPHA_SCALE";
      case 0x0D1D: return "GL_ALPHA_BIAS";
      case 0x0D1E: return "GL_DEPTH_SCALE";
      case 0x0D1F: return "GL_DEPTH_BIAS";
      case 0x0D30: return "GL_MAX_EVAL_ORDER";
      case 0x0D31: return "GL_MAX_LIGHTS";
      case 0x0D32: return "GL_MAX_CLIP_PLANES";
      case 0x0D33: return "GL_MAX_TEXTURE_SIZE";
      case 0x0D34: return "GL_MAX_PIXEL_MAP_TABLE";
      case 0x0D35: return "GL_MAX_ATTRIB_STACK_DEPTH";
      case 0x0D36: return "GL_MAX_MODELVIEW_STACK_DEPTH";
      case 0x0D37: return "GL_MAX_NAME_STACK_DEPTH";
      case 0x0D38: return "GL_MAX_PROJECTION_STACK_DEPTH";
      case 0x0D39: return "GL_MAX_TEXTURE_STACK_DEPTH";
      case 0x0D3A: return "GL_MAX_VIEWPORT_DIMS";
      case 0x0D3B: return "GL_MAX_CLIENT_ATTRIB_STACK_DEPTH";
      case 0x0D50: return "GL_SUBPIXEL_BITS";
      case 0x0D51: return "GL_INDEX_BITS";
      case 0x0D52: return "GL_RED_BITS";
      case 0x0D53: return "GL_GREEN_BITS";
      case 0x0D54: return "GL_BLUE_BITS";
      case 0x0D55: return "GL_ALPHA_BITS";
      case 0x0D56: return "GL_DEPTH_BITS";
      case 0x0D57: return "GL_STENCIL_BITS";
      case 0x0D58: return "GL_ACCUM_RED_BITS";
      case 0x0D59: return "GL_ACCUM_GREEN_BITS";
      case 0x0D5A: return "GL_ACCUM_BLUE_BITS";
      case 0x0D5B: return "GL_ACCUM_ALPHA_BITS";
      case 0x0D70: return "GL_NAME_STACK_DEPTH";
      case 0x0D80: return "GL_AUTO_NORMAL";
      case 0x0D90: return "GL_MAP1_COLOR_4";
      case 0x0D91: return "GL_MAP1_INDEX";
      case 0x0D92: return "GL_MAP1_NORMAL";
      case 0x0D93: return "GL_MAP1_TEXTURE_COORD_1";
      case 0x0D94: return "GL_MAP1_TEXTURE_COORD_2";
      case 0x0D95: return "GL_MAP1_TEXTURE_COORD_3";
      case 0x0D96: return "GL_MAP1_TEXTURE_COORD_4";
      case 0x0D97: return "GL_MAP1_VERTEX_3";
      case 0x0D98: return "GL_MAP1_VERTEX_4";
      case 0x0DB0: return "GL_MAP2_COLOR_4";
      case 0x0DB1: return "GL_MAP2_INDEX";
      case 0x0DB2: return "GL_MAP2_NORMAL";
      case 0x0DB3: return "GL_MAP2_TEXTURE_COORD_1";
      case 0x0DB4: return "GL_MAP2_TEXTURE_COORD_2";
      case 0x0DB5: return "GL_MAP2_TEXTURE_COORD_3";
      case 0x0DB6: return "GL_MAP2_TEXTURE_COORD_4";
      case 0x0DB7: return "GL_MAP2_VERTEX_3";
      case 0x0DB8: return "GL_MAP2_VERTEX_4";
      case 0x0DD0: return "GL_MAP1_GRID_DOMAIN";
      case 0x0DD1: return "GL_MAP1_GRID_SEGMENTS";
      case 0x0DD2: return "GL_MAP2_GRID_DOMAIN";
      case 0x0DD3: return "GL_MAP2_GRID_SEGMENTS";
      case 0x0DE0: return "GL_TEXTURE_1D";
      case 0x0DE1: return "GL_TEXTURE_2D";
      case 0x0DF0: return "GL_FEEDBACK_BUFFER_POINTER";
      case 0x0DF1: return "GL_FEEDBACK_BUFFER_SIZE";
      case 0x0DF2: return "GL_FEEDBACK_BUFFER_TYPE";
      case 0x0DF3: return "GL_SELECTION_BUFFER_POINTER";
      case 0x0DF4: return "GL_SELECTION_BUFFER_SIZE";
      case 0x00001000: return "GL_TRANSFORM_BIT";
      case 0x1001: return "GL_TEXTURE_HEIGHT";
      case 0x1003: return "GL_TEXTURE_INTERNAL_FORMAT";
      case 0x1004: return "GL_TEXTURE_BORDER_COLOR";
      case 0x1005: return "GL_TEXTURE_BORDER";
      case 0x1100: return "GL_DONT_CARE";
      case 0x1101: return "GL_FASTEST";
      case 0x1102: return "GL_NICEST";
      case 0x1200: return "GL_AMBIENT";
      case 0x1201: return "GL_DIFFUSE";
      case 0x1202: return "GL_SPECULAR";
      case 0x1203: return "GL_POSITION";
      case 0x1204: return "GL_SPOT_DIRECTION";
      case 0x1205: return "GL_SPOT_EXPONENT";
      case 0x1206: return "GL_SPOT_CUTOFF";
      case 0x1207: return "GL_CONSTANT_ATTENUATION";
      case 0x1208: return "GL_LINEAR_ATTENUATION";
      case 0x1209: return "GL_QUADRATIC_ATTENUATION";
      case 0x1300: return "GL_COMPILE";
      case 0x1301: return "GL_COMPILE_AND_EXECUTE";
      case 0x1400: return "GL_BYTE";
      case 0x1401: return "GL_UNSIGNED_BYTE";
      case 0x1402: return "GL_SHORT";
      case 0x1403: return "GL_UNSIGNED_SHORT";
      case 0x1404: return "GL_INT";
      case 0x1405: return "GL_UNSIGNED_INT";
      case 0x1406: return "GL_FLOAT";
      case 0x1407: return "GL_2_BYTES";
      case 0x1408: return "GL_3_BYTES";
      case 0x1409: return "GL_4_BYTES";
      case 0x140A: return "GL_DOUBLE";
      case 0x140B: return "GL_HALF_FLOAT";
      case 0x1500: return "GL_CLEAR";
      case 0x1501: return "GL_AND";
      case 0x1502: return "GL_AND_REVERSE";
      case 0x1503: return "GL_COPY";
      case 0x1504: return "GL_AND_INVERTED";
      case 0x1505: return "GL_NOOP";
      case 0x1506: return "GL_XOR";
      case 0x1507: return "GL_OR";
      case 0x1508: return "GL_NOR";
      case 0x1509: return "GL_EQUIV";
      case 0x150A: return "GL_INVERT";
      case 0x150B: return "GL_OR_REVERSE";
      case 0x150C: return "GL_COPY_INVERTED";
      case 0x150D: return "GL_OR_INVERTED";
      case 0x150E: return "GL_NAND";
      case 0x150F: return "GL_SET";
      case 0x1600: return "GL_EMISSION";
      case 0x1601: return "GL_SHININESS";
      case 0x1602: return "GL_AMBIENT_AND_DIFFUSE";
      case 0x1603: return "GL_COLOR_INDEXES";
      case 0x1700: return "GL_MODELVIEW";
      case 0x1701: return "GL_PROJECTION";
      case 0x1702: return "GL_TEXTURE";
      case 0x1800: return "GL_COLOR";
      case 0x1801: return "GL_DEPTH";
      case 0x1802: return "GL_STENCIL";
      case 0x1900: return "GL_COLOR_INDEX";
      case 0x1901: return "GL_STENCIL_INDEX";
      case 0x1902: return "GL_DEPTH_COMPONENT";
      case 0x1903: return "GL_RED";
      case 0x1904: return "GL_GREEN";
      case 0x1905: return "GL_BLUE";
      case 0x1906: return "GL_ALPHA";
      case 0x1907: return "GL_RGB";
      case 0x1908: return "GL_RGBA";
      case 0x1909: return "GL_LUMINANCE";
      case 0x190A: return "GL_LUMINANCE_ALPHA";
      case 0x1A00: return "GL_BITMAP";
      case 0x1B00: return "GL_POINT";
      case 0x1B01: return "GL_LINE";
      case 0x1B02: return "GL_FILL";
      case 0x1C00: return "GL_RENDER";
      case 0x1C01: return "GL_FEEDBACK";
      case 0x1C02: return "GL_SELECT";
      case 0x1D00: return "GL_FLAT";
      case 0x1D01: return "GL_SMOOTH";
      case 0x1E00: return "GL_KEEP";
      case 0x1E01: return "GL_REPLACE";
      case 0x1E02: return "GL_INCR";
      case 0x1E03: return "GL_DECR";
      case 0x1F00: return "GL_VENDOR";
      case 0x1F01: return "GL_RENDERER";
      case 0x1F02: return "GL_VERSION";
      case 0x1F03: return "GL_EXTENSIONS";
      case 0x00002000: return "GL_ENABLE_BIT";
      case 0x2001: return "GL_T";
      case 0x2002: return "GL_R";
      case 0x2003: return "GL_Q";
      case 0x2100: return "GL_MODULATE";
      case 0x2101: return "GL_DECAL";
      case 0x2200: return "GL_TEXTURE_ENV_MODE";
      case 0x2201: return "GL_TEXTURE_ENV_COLOR";
      case 0x2300: return "GL_TEXTURE_ENV";
      case 0x2400: return "GL_EYE_LINEAR";
      case 0x2401: return "GL_OBJECT_LINEAR";
      case 0x2402: return "GL_SPHERE_MAP";
      case 0x2500: return "GL_TEXTURE_GEN_MODE";
      case 0x2501: return "GL_OBJECT_PLANE";
      case 0x2502: return "GL_EYE_PLANE";
      case 0x2600: return "GL_NEAREST";
      case 0x2601: return "GL_LINEAR";
      case 0x2700: return "GL_NEAREST_MIPMAP_NEAREST";
      case 0x2701: return "GL_LINEAR_MIPMAP_NEAREST";
      case 0x2702: return "GL_NEAREST_MIPMAP_LINEAR";
      case 0x2703: return "GL_LINEAR_MIPMAP_LINEAR";
      case 0x2800: return "GL_TEXTURE_MAG_FILTER";
      case 0x2801: return "GL_TEXTURE_MIN_FILTER";
      case 0x2802: return "GL_TEXTURE_WRAP_S";
      case 0x2803: return "GL_TEXTURE_WRAP_T";
      case 0x2900: return "GL_CLAMP";
      case 0x2901: return "GL_REPEAT";
      case 0x2A00: return "GL_POLYGON_OFFSET_UNITS";
      case 0x2A01: return "GL_POLYGON_OFFSET_POINT";
      case 0x2A02: return "GL_POLYGON_OFFSET_LINE";
      case 0x2A10: return "GL_R3_G3_B2";
      case 0x2A20: return "GL_V2F";
      case 0x2A21: return "GL_V3F";
      case 0x2A22: return "GL_C4UB_V2F";
      case 0x2A23: return "GL_C4UB_V3F";
      case 0x2A24: return "GL_C3F_V3F";
      case 0x2A25: return "GL_N3F_V3F";
      case 0x2A26: return "GL_C4F_N3F_V3F";
      case 0x2A27: return "GL_T2F_V3F";
      case 0x2A28: return "GL_T4F_V4F";
      case 0x2A29: return "GL_T2F_C4UB_V3F";
      case 0x2A2A: return "GL_T2F_C3F_V3F";
      case 0x2A2B: return "GL_T2F_N3F_V3F";
      case 0x2A2C: return "GL_T2F_C4F_N3F_V3F";
      case 0x2A2D: return "GL_T4F_C4F_N3F_V4F";
      case 0x3000: return "GL_CLIP_PLANE0";
      case 0x3001: return "GL_CLIP_PLANE1";
      case 0x3002: return "GL_CLIP_PLANE2";
      case 0x3003: return "GL_CLIP_PLANE3";
      case 0x3004: return "GL_CLIP_PLANE4";
      case 0x3005: return "GL_CLIP_PLANE5";
      case 0x3006: return "GL_CLIP_DISTANCE6";
      case 0x3007: return "GL_CLIP_DISTANCE7";
      case 0x00004000: return "GL_COLOR_BUFFER_BIT";
      case 0x4001: return "GL_LIGHT1";
      case 0x4002: return "GL_LIGHT2";
      case 0x4003: return "GL_LIGHT3";
      case 0x4004: return "GL_LIGHT4";
      case 0x4005: return "GL_LIGHT5";
      case 0x4006: return "GL_LIGHT6";
      case 0x4007: return "GL_LIGHT7";
      case 0x00008000: return "GL_HINT_BIT";
      case 0x8001: return "GL_CONSTANT_COLOR";
      case 0x8002: return "GL_ONE_MINUS_CONSTANT_COLOR";
      case 0x8003: return "GL_CONSTANT_ALPHA";
      case 0x8004: return "GL_ONE_MINUS_CONSTANT_ALPHA";
      case 0x8006: return "GL_FUNC_ADD";
      case 0x8007: return "GL_MIN";
      case 0x8008: return "GL_MAX";
      case 0x8009: return "GL_BLEND_EQUATION_RGB";
      case 0x800A: return "GL_FUNC_SUBTRACT";
      case 0x800B: return "GL_FUNC_REVERSE_SUBTRACT";
      case 0x8032: return "GL_UNSIGNED_BYTE_3_3_2";
      case 0x8033: return "GL_UNSIGNED_SHORT_4_4_4_4";
      case 0x8034: return "GL_UNSIGNED_SHORT_5_5_5_1";
      case 0x8035: return "GL_UNSIGNED_INT_8_8_8_8";
      case 0x8036: return "GL_UNSIGNED_INT_10_10_10_2";
      case 0x8037: return "GL_POLYGON_OFFSET_FILL";
      case 0x8038: return "GL_POLYGON_OFFSET_FACTOR";
      case 0x803A: return "GL_RESCALE_NORMAL";
      case 0x803B: return "GL_ALPHA4";
      case 0x803C: return "GL_ALPHA8";
      case 0x803D: return "GL_ALPHA12";
      case 0x803E: return "GL_ALPHA16";
      case 0x803F: return "GL_LUMINANCE4";
      case 0x8040: return "GL_LUMINANCE8";
      case 0x8041: return "GL_LUMINANCE12";
      case 0x8042: return "GL_LUMINANCE16";
      case 0x8043: return "GL_LUMINANCE4_ALPHA4";
      case 0x8044: return "GL_LUMINANCE6_ALPHA2";
      case 0x8045: return "GL_LUMINANCE8_ALPHA8";
      case 0x8046: return "GL_LUMINANCE12_ALPHA4";
      case 0x8047: return "GL_LUMINANCE12_ALPHA12";
      case 0x8048: return "GL_LUMINANCE16_ALPHA16";
      case 0x8049: return "GL_INTENSITY";
      case 0x804A: return "GL_INTENSITY4";
      case 0x804B: return "GL_INTENSITY8";
      case 0x804C: return "GL_INTENSITY12";
      case 0x804D: return "GL_INTENSITY16";
      case 0x804F: return "GL_RGB4";
      case 0x8050: return "GL_RGB5";
      case 0x8051: return "GL_RGB8";
      case 0x8052: return "GL_RGB10";
      case 0x8053: return "GL_RGB12";
      case 0x8054: return "GL_RGB16";
      case 0x8055: return "GL_RGBA2";
      case 0x8056: return "GL_RGBA4";
      case 0x8057: return "GL_RGB5_A1";
      case 0x8058: return "GL_RGBA8";
      case 0x8059: return "GL_RGB10_A2";
      case 0x805A: return "GL_RGBA12";
      case 0x805B: return "GL_RGBA16";
      case 0x805C: return "GL_TEXTURE_RED_SIZE";
      case 0x805D: return "GL_TEXTURE_GREEN_SIZE";
      case 0x805E: return "GL_TEXTURE_BLUE_SIZE";
      case 0x805F: return "GL_TEXTURE_ALPHA_SIZE";
      case 0x8060: return "GL_TEXTURE_LUMINANCE_SIZE";
      case 0x8061: return "GL_TEXTURE_INTENSITY_SIZE";
      case 0x8063: return "GL_PROXY_TEXTURE_1D";
      case 0x8064: return "GL_PROXY_TEXTURE_2D";
      case 0x8066: return "GL_TEXTURE_PRIORITY";
      case 0x8067: return "GL_TEXTURE_RESIDENT";
      case 0x8068: return "GL_TEXTURE_BINDING_1D";
      case 0x8069: return "GL_TEXTURE_BINDING_2D";
      case 0x806A: return "GL_TEXTURE_BINDING_3D";
      case 0x806B: return "GL_PACK_SKIP_IMAGES";
      case 0x806C: return "GL_PACK_IMAGE_HEIGHT";
      case 0x806D: return "GL_UNPACK_SKIP_IMAGES";
      case 0x806E: return "GL_UNPACK_IMAGE_HEIGHT";
      case 0x806F: return "GL_TEXTURE_3D";
      case 0x8070: return "GL_PROXY_TEXTURE_3D";
      case 0x8071: return "GL_TEXTURE_DEPTH";
      case 0x8072: return "GL_TEXTURE_WRAP_R";
      case 0x8073: return "GL_MAX_3D_TEXTURE_SIZE";
      case 0x8074: return "GL_VERTEX_ARRAY";
      case 0x8075: return "GL_NORMAL_ARRAY";
      case 0x8076: return "GL_COLOR_ARRAY";
      case 0x8077: return "GL_INDEX_ARRAY";
      case 0x8078: return "GL_TEXTURE_COORD_ARRAY";
      case 0x8079: return "GL_EDGE_FLAG_ARRAY";
      case 0x807A: return "GL_VERTEX_ARRAY_SIZE";
      case 0x807B: return "GL_VERTEX_ARRAY_TYPE";
      case 0x807C: return "GL_VERTEX_ARRAY_STRIDE";
      case 0x807E: return "GL_NORMAL_ARRAY_TYPE";
      case 0x807F: return "GL_NORMAL_ARRAY_STRIDE";
      case 0x8081: return "GL_COLOR_ARRAY_SIZE";
      case 0x8082: return "GL_COLOR_ARRAY_TYPE";
      case 0x8083: return "GL_COLOR_ARRAY_STRIDE";
      case 0x8085: return "GL_INDEX_ARRAY_TYPE";
      case 0x8086: return "GL_INDEX_ARRAY_STRIDE";
      case 0x8088: return "GL_TEXTURE_COORD_ARRAY_SIZE";
      case 0x8089: return "GL_TEXTURE_COORD_ARRAY_TYPE";
      case 0x808A: return "GL_TEXTURE_COORD_ARRAY_STRIDE";
      case 0x808C: return "GL_EDGE_FLAG_ARRAY_STRIDE";
      case 0x808E: return "GL_VERTEX_ARRAY_POINTER";
      case 0x808F: return "GL_NORMAL_ARRAY_POINTER";
      case 0x8090: return "GL_COLOR_ARRAY_POINTER";
      case 0x8091: return "GL_INDEX_ARRAY_POINTER";
      case 0x8092: return "GL_TEXTURE_COORD_ARRAY_POINTER";
      case 0x8093: return "GL_EDGE_FLAG_ARRAY_POINTER";
      case 0x809D: return "GL_MULTISAMPLE";
      case 0x809E: return "GL_SAMPLE_ALPHA_TO_COVERAGE";
      case 0x809F: return "GL_SAMPLE_ALPHA_TO_ONE";
      case 0x80A0: return "GL_SAMPLE_COVERAGE";
      case 0x80A8: return "GL_SAMPLE_BUFFERS";
      case 0x80A9: return "GL_SAMPLES";
      case 0x80AA: return "GL_SAMPLE_COVERAGE_VALUE";
      case 0x80AB: return "GL_SAMPLE_COVERAGE_INVERT";
      case 0x80C8: return "GL_BLEND_DST_RGB";
      case 0x80C9: return "GL_BLEND_SRC_RGB";
      case 0x80CA: return "GL_BLEND_DST_ALPHA";
      case 0x80CB: return "GL_BLEND_SRC_ALPHA";
      case 0x80E0: return "GL_BGR";
      case 0x80E1: return "GL_BGRA";
      case 0x80E8: return "GL_MAX_ELEMENTS_VERTICES";
      case 0x80E9: return "GL_MAX_ELEMENTS_INDICES";
      case 0x8126: return "GL_POINT_SIZE_MIN";
      case 0x8127: return "GL_POINT_SIZE_MAX";
      case 0x8128: return "GL_POINT_FADE_THRESHOLD_SIZE";
      case 0x8129: return "GL_POINT_DISTANCE_ATTENUATION";
      case 0x812D: return "GL_CLAMP_TO_BORDER";
      case 0x812F: return "GL_CLAMP_TO_EDGE";
      case 0x813A: return "GL_TEXTURE_MIN_LOD";
      case 0x813B: return "GL_TEXTURE_MAX_LOD";
      case 0x813C: return "GL_TEXTURE_BASE_LEVEL";
      case 0x813D: return "GL_TEXTURE_MAX_LEVEL";
      case 0x8191: return "GL_GENERATE_MIPMAP";
      case 0x8192: return "GL_GENERATE_MIPMAP_HINT";
      case 0x81A5: return "GL_DEPTH_COMPONENT16";
      case 0x81A6: return "GL_DEPTH_COMPONENT24";
      case 0x81A7: return "GL_DEPTH_COMPONENT32";
      case 0x81F8: return "GL_LIGHT_MODEL_COLOR_CONTROL";
      case 0x81F9: return "GL_SINGLE_COLOR";
      case 0x81FA: return "GL_SEPARATE_SPECULAR_COLOR";
      case 0x8210: return "GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING";
      case 0x8211: return "GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE";
      case 0x8212: return "GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE";
      case 0x8213: return "GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE";
      case 0x8214: return "GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE";
      case 0x8215: return "GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE";
      case 0x8216: return "GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE";
      case 0x8217: return "GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE";
      case 0x8218: return "GL_FRAMEBUFFER_DEFAULT";
      case 0x8219: return "GL_FRAMEBUFFER_UNDEFINED";
      case 0x821A: return "GL_DEPTH_STENCIL_ATTACHMENT";
      case 0x821B: return "GL_MAJOR_VERSION";
      case 0x821C: return "GL_MINOR_VERSION";
      case 0x821D: return "GL_NUM_EXTENSIONS";
      case 0x821E: return "GL_CONTEXT_FLAGS";
      case 0x8222: return "GL_INDEX";
      case 0x8225: return "GL_COMPRESSED_RED";
      case 0x8226: return "GL_COMPRESSED_RG";
      case 0x8227: return "GL_RG";
      case 0x8228: return "GL_RG_INTEGER";
      case 0x8229: return "GL_R8";
      case 0x822A: return "GL_R16";
      case 0x822B: return "GL_RG8";
      case 0x822C: return "GL_RG16";
      case 0x822D: return "GL_R16F";
      case 0x822E: return "GL_R32F";
      case 0x822F: return "GL_RG16F";
      case 0x8230: return "GL_RG32F";
      case 0x8231: return "GL_R8I";
      case 0x8232: return "GL_R8UI";
      case 0x8233: return "GL_R16I";
      case 0x8234: return "GL_R16UI";
      case 0x8235: return "GL_R32I";
      case 0x8236: return "GL_R32UI";
      case 0x8237: return "GL_RG8I";
      case 0x8238: return "GL_RG8UI";
      case 0x8239: return "GL_RG16I";
      case 0x823A: return "GL_RG16UI";
      case 0x823B: return "GL_RG32I";
      case 0x823C: return "GL_RG32UI";
      case 0x8242: return "GL_DEBUG_OUTPUT_SYNCHRONOUS";
      case 0x8243: return "GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH";
      case 0x8244: return "GL_DEBUG_CALLBACK_FUNCTION";
      case 0x8245: return "GL_DEBUG_CALLBACK_USER_PARAM";
      case 0x8246: return "GL_DEBUG_SOURCE_API";
      case 0x8247: return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
      case 0x8248: return "GL_DEBUG_SOURCE_SHADER_COMPILER";
      case 0x8249: return "GL_DEBUG_SOURCE_THIRD_PARTY";
      case 0x824A: return "GL_DEBUG_SOURCE_APPLICATION";
      case 0x824B: return "GL_DEBUG_SOURCE_OTHER";
      case 0x824C: return "GL_DEBUG_TYPE_ERROR";
      case 0x824D: return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
      case 0x824E: return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
      case 0x824F: return "GL_DEBUG_TYPE_PORTABILITY";
      case 0x8250: return "GL_DEBUG_TYPE_PERFORMANCE";
      case 0x8251: return "GL_DEBUG_TYPE_OTHER";
      case 0x8268: return "GL_DEBUG_TYPE_MARKER";
      case 0x8269: return "GL_DEBUG_TYPE_PUSH_GROUP";
      case 0x826A: return "GL_DEBUG_TYPE_POP_GROUP";
      case 0x826B: return "GL_DEBUG_SEVERITY_NOTIFICATION";
      case 0x826C: return "GL_MAX_DEBUG_GROUP_STACK_DEPTH";
      case 0x826D: return "GL_DEBUG_GROUP_STACK_DEPTH";
      case 0x82E0: return "GL_BUFFER";
      case 0x82E1: return "GL_SHADER";
      case 0x82E2: return "GL_PROGRAM";
      case 0x82E3: return "GL_QUERY";
      case 0x82E4: return "GL_PROGRAM_PIPELINE";
      case 0x82E6: return "GL_SAMPLER";
      case 0x82E7: return "GL_DISPLAY_LIST";
      case 0x82E8: return "GL_MAX_LABEL_LENGTH";
      case 0x8362: return "GL_UNSIGNED_BYTE_2_3_3_REV";
      case 0x8363: return "GL_UNSIGNED_SHORT_5_6_5";
      case 0x8364: return "GL_UNSIGNED_SHORT_5_6_5_REV";
      case 0x8365: return "GL_UNSIGNED_SHORT_4_4_4_4_REV";
      case 0x8366: return "GL_UNSIGNED_SHORT_1_5_5_5_REV";
      case 0x8367: return "GL_UNSIGNED_INT_8_8_8_8_REV";
      case 0x8368: return "GL_UNSIGNED_INT_2_10_10_10_REV";
      case 0x8370: return "GL_MIRRORED_REPEAT";
      case 0x83F0: return "GL_COMPRESSED_RGB_S3TC_DXT1_EXT";
      case 0x83F1: return "GL_COMPRESSED_RGBA_S3TC_DXT1_EXT";
      case 0x83F2: return "GL_COMPRESSED_RGBA_S3TC_DXT3_EXT";
      case 0x83F3: return "GL_COMPRESSED_RGBA_S3TC_DXT5_EXT";
      case 0x8450: return "GL_FOG_COORDINATE_SOURCE";
      case 0x8451: return "GL_FOG_COORDINATE";
      case 0x8452: return "GL_FRAGMENT_DEPTH";
      case 0x8453: return "GL_CURRENT_FOG_COORDINATE";
      case 0x8454: return "GL_FOG_COORDINATE_ARRAY_TYPE";
      case 0x8455: return "GL_FOG_COORDINATE_ARRAY_STRIDE";
      case 0x8456: return "GL_FOG_COORDINATE_ARRAY_POINTER";
      case 0x8457: return "GL_FOG_COORDINATE_ARRAY";
      case 0x8458: return "GL_COLOR_SUM";
      case 0x8459: return "GL_CURRENT_SECONDARY_COLOR";
      case 0x845A: return "GL_SECONDARY_COLOR_ARRAY_SIZE";
      case 0x845B: return "GL_SECONDARY_COLOR_ARRAY_TYPE";
      case 0x845C: return "GL_SECONDARY_COLOR_ARRAY_STRIDE";
      case 0x845D: return "GL_SECONDARY_COLOR_ARRAY_POINTER";
      case 0x845E: return "GL_SECONDARY_COLOR_ARRAY";
      case 0x845F: return "GL_CURRENT_RASTER_SECONDARY_COLOR";
      case 0x846D: return "GL_ALIASED_POINT_SIZE_RANGE";
      case 0x846E: return "GL_ALIASED_LINE_WIDTH_RANGE";
      case 0x84C0: return "GL_TEXTURE0";
      case 0x84C1: return "GL_TEXTURE1";
      case 0x84C2: return "GL_TEXTURE2";
      case 0x84C3: return "GL_TEXTURE3";
      case 0x84C4: return "GL_TEXTURE4";
      case 0x84C5: return "GL_TEXTURE5";
      case 0x84C6: return "GL_TEXTURE6";
      case 0x84C7: return "GL_TEXTURE7";
      case 0x84C8: return "GL_TEXTURE8";
      case 0x84C9: return "GL_TEXTURE9";
      case 0x84CA: return "GL_TEXTURE10";
      case 0x84CB: return "GL_TEXTURE11";
      case 0x84CC: return "GL_TEXTURE12";
      case 0x84CD: return "GL_TEXTURE13";
      case 0x84CE: return "GL_TEXTURE14";
      case 0x84CF: return "GL_TEXTURE15";
      case 0x84D0: return "GL_TEXTURE16";
      case 0x84D1: return "GL_TEXTURE17";
      case 0x84D2: return "GL_TEXTURE18";
      case 0x84D3: return "GL_TEXTURE19";
      case 0x84D4: return "GL_TEXTURE20";
      case 0x84D5: return "GL_TEXTURE21";
      case 0x84D6: return "GL_TEXTURE22";
      case 0x84D7: return "GL_TEXTURE23";
      case 0x84D8: return "GL_TEXTURE24";
      case 0x84D9: return "GL_TEXTURE25";
      case 0x84DA: return "GL_TEXTURE26";
      case 0x84DB: return "GL_TEXTURE27";
      case 0x84DC: return "GL_TEXTURE28";
      case 0x84DD: return "GL_TEXTURE29";
      case 0x84DE: return "GL_TEXTURE30";
      case 0x84DF: return "GL_TEXTURE31";
      case 0x84E0: return "GL_ACTIVE_TEXTURE";
      case 0x84E1: return "GL_CLIENT_ACTIVE_TEXTURE";
      case 0x84E2: return "GL_MAX_TEXTURE_UNITS";
      case 0x84E3: return "GL_TRANSPOSE_MODELVIEW_MATRIX";
      case 0x84E4: return "GL_TRANSPOSE_PROJECTION_MATRIX";
      case 0x84E5: return "GL_TRANSPOSE_TEXTURE_MATRIX";
      case 0x84E6: return "GL_TRANSPOSE_COLOR_MATRIX";
      case 0x84E7: return "GL_SUBTRACT";
      case 0x84E8: return "GL_MAX_RENDERBUFFER_SIZE";
      case 0x84E9: return "GL_COMPRESSED_ALPHA";
      case 0x84EA: return "GL_COMPRESSED_LUMINANCE";
      case 0x84EB: return "GL_COMPRESSED_LUMINANCE_ALPHA";
      case 0x84EC: return "GL_COMPRESSED_INTENSITY";
      case 0x84ED: return "GL_COMPRESSED_RGB";
      case 0x84EE: return "GL_COMPRESSED_RGBA";
      case 0x84EF: return "GL_TEXTURE_COMPRESSION_HINT";
      case 0x84F5: return "GL_TEXTURE_RECTANGLE";
      case 0x84F6: return "GL_TEXTURE_BINDING_RECTANGLE";
      case 0x84F7: return "GL_PROXY_TEXTURE_RECTANGLE";
      case 0x84F8: return "GL_MAX_RECTANGLE_TEXTURE_SIZE";
      case 0x84F9: return "GL_DEPTH_STENCIL";
      case 0x84FA: return "GL_UNSIGNED_INT_24_8";
      case 0x84FD: return "GL_MAX_TEXTURE_LOD_BIAS";
      case 0x8500: return "GL_TEXTURE_FILTER_CONTROL";
      case 0x8501: return "GL_TEXTURE_LOD_BIAS";
      case 0x8507: return "GL_INCR_WRAP";
      case 0x8508: return "GL_DECR_WRAP";
      case 0x8511: return "GL_NORMAL_MAP";
      case 0x8512: return "GL_REFLECTION_MAP";
      case 0x8513: return "GL_TEXTURE_CUBE_MAP";
      case 0x8514: return "GL_TEXTURE_BINDING_CUBE_MAP";
      case 0x8515: return "GL_TEXTURE_CUBE_MAP_POSITIVE_X";
      case 0x8516: return "GL_TEXTURE_CUBE_MAP_NEGATIVE_X";
      case 0x8517: return "GL_TEXTURE_CUBE_MAP_POSITIVE_Y";
      case 0x8518: return "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y";
      case 0x8519: return "GL_TEXTURE_CUBE_MAP_POSITIVE_Z";
      case 0x851A: return "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z";
      case 0x851B: return "GL_PROXY_TEXTURE_CUBE_MAP";
      case 0x851C: return "GL_MAX_CUBE_MAP_TEXTURE_SIZE";
      case 0x8570: return "GL_COMBINE";
      case 0x8571: return "GL_COMBINE_RGB";
      case 0x8572: return "GL_COMBINE_ALPHA";
      case 0x8573: return "GL_RGB_SCALE";
      case 0x8574: return "GL_ADD_SIGNED";
      case 0x8575: return "GL_INTERPOLATE";
      case 0x8576: return "GL_CONSTANT";
      case 0x8577: return "GL_PRIMARY_COLOR";
      case 0x8578: return "GL_PREVIOUS";
      case 0x8580: return "GL_SOURCE0_RGB";
      case 0x8581: return "GL_SOURCE1_RGB";
      case 0x8582: return "GL_SOURCE2_RGB";
      case 0x8588: return "GL_SOURCE0_ALPHA";
      case 0x8589: return "GL_SOURCE1_ALPHA";
      case 0x858A: return "GL_SOURCE2_ALPHA";
      case 0x8590: return "GL_OPERAND0_RGB";
      case 0x8591: return "GL_OPERAND1_RGB";
      case 0x8592: return "GL_OPERAND2_RGB";
      case 0x8598: return "GL_OPERAND0_ALPHA";
      case 0x8599: return "GL_OPERAND1_ALPHA";
      case 0x859A: return "GL_OPERAND2_ALPHA";
      case 0x85B5: return "GL_VERTEX_ARRAY_BINDING";
      case 0x8622: return "GL_VERTEX_ATTRIB_ARRAY_ENABLED";
      case 0x8623: return "GL_VERTEX_ATTRIB_ARRAY_SIZE";
      case 0x8624: return "GL_VERTEX_ATTRIB_ARRAY_STRIDE";
      case 0x8625: return "GL_VERTEX_ATTRIB_ARRAY_TYPE";
      case 0x8626: return "GL_CURRENT_VERTEX_ATTRIB";
      case 0x8642: return "GL_VERTEX_PROGRAM_POINT_SIZE";
      case 0x8643: return "GL_VERTEX_PROGRAM_TWO_SIDE";
      case 0x8645: return "GL_VERTEX_ATTRIB_ARRAY_POINTER";
      case 0x864F: return "GL_DEPTH_CLAMP";
      case 0x86A0: return "GL_TEXTURE_COMPRESSED_IMAGE_SIZE";
      case 0x86A1: return "GL_TEXTURE_COMPRESSED";
      case 0x86A2: return "GL_NUM_COMPRESSED_TEXTURE_FORMATS";
      case 0x86A3: return "GL_COMPRESSED_TEXTURE_FORMATS";
      case 0x86AE: return "GL_DOT3_RGB";
      case 0x86AF: return "GL_DOT3_RGBA";
      case 0x8764: return "GL_BUFFER_SIZE";
      case 0x8765: return "GL_BUFFER_USAGE";
      case 0x8800: return "GL_STENCIL_BACK_FUNC";
      case 0x8801: return "GL_STENCIL_BACK_FAIL";
      case 0x8802: return "GL_STENCIL_BACK_PASS_DEPTH_FAIL";
      case 0x8803: return "GL_STENCIL_BACK_PASS_DEPTH_PASS";
      case 0x8814: return "GL_RGBA32F";
      case 0x8815: return "GL_RGB32F";
      case 0x881A: return "GL_RGBA16F";
      case 0x881B: return "GL_RGB16F";
      case 0x8824: return "GL_MAX_DRAW_BUFFERS";
      case 0x8825: return "GL_DRAW_BUFFER0";
      case 0x8826: return "GL_DRAW_BUFFER1";
      case 0x8827: return "GL_DRAW_BUFFER2";
      case 0x8828: return "GL_DRAW_BUFFER3";
      case 0x8829: return "GL_DRAW_BUFFER4";
      case 0x882A: return "GL_DRAW_BUFFER5";
      case 0x882B: return "GL_DRAW_BUFFER6";
      case 0x882C: return "GL_DRAW_BUFFER7";
      case 0x882D: return "GL_DRAW_BUFFER8";
      case 0x882E: return "GL_DRAW_BUFFER9";
      case 0x882F: return "GL_DRAW_BUFFER10";
      case 0x8830: return "GL_DRAW_BUFFER11";
      case 0x8831: return "GL_DRAW_BUFFER12";
      case 0x8832: return "GL_DRAW_BUFFER13";
      case 0x8833: return "GL_DRAW_BUFFER14";
      case 0x8834: return "GL_DRAW_BUFFER15";
      case 0x883D: return "GL_BLEND_EQUATION_ALPHA";
      case 0x884A: return "GL_TEXTURE_DEPTH_SIZE";
      case 0x884B: return "GL_DEPTH_TEXTURE_MODE";
      case 0x884C: return "GL_TEXTURE_COMPARE_MODE";
      case 0x884D: return "GL_TEXTURE_COMPARE_FUNC";
      case 0x884E: return "GL_COMPARE_R_TO_TEXTURE";
      case 0x884F: return "GL_TEXTURE_CUBE_MAP_SEAMLESS";
      case 0x8861: return "GL_POINT_SPRITE";
      case 0x8862: return "GL_COORD_REPLACE";
      case 0x8864: return "GL_QUERY_COUNTER_BITS";
      case 0x8865: return "GL_CURRENT_QUERY";
      case 0x8866: return "GL_QUERY_RESULT";
      case 0x8867: return "GL_QUERY_RESULT_AVAILABLE";
      case 0x8869: return "GL_MAX_VERTEX_ATTRIBS";
      case 0x886A: return "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED";
      case 0x8871: return "GL_MAX_TEXTURE_COORDS";
      case 0x8872: return "GL_MAX_TEXTURE_IMAGE_UNITS";
      case 0x8892: return "GL_ARRAY_BUFFER";
      case 0x8893: return "GL_ELEMENT_ARRAY_BUFFER";
      case 0x8894: return "GL_ARRAY_BUFFER_BINDING";
      case 0x8895: return "GL_ELEMENT_ARRAY_BUFFER_BINDING";
      case 0x8896: return "GL_VERTEX_ARRAY_BUFFER_BINDING";
      case 0x8897: return "GL_NORMAL_ARRAY_BUFFER_BINDING";
      case 0x8898: return "GL_COLOR_ARRAY_BUFFER_BINDING";
      case 0x8899: return "GL_INDEX_ARRAY_BUFFER_BINDING";
      case 0x889A: return "GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING";
      case 0x889B: return "GL_EDGE_FLAG_ARRAY_BUFFER_BINDING";
      case 0x889C: return "GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING";
      case 0x889D: return "GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING";
      case 0x889E: return "GL_WEIGHT_ARRAY_BUFFER_BINDING";
      case 0x889F: return "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING";
      case 0x88B8: return "GL_READ_ONLY";
      case 0x88B9: return "GL_WRITE_ONLY";
      case 0x88BA: return "GL_READ_WRITE";
      case 0x88BB: return "GL_BUFFER_ACCESS";
      case 0x88BC: return "GL_BUFFER_MAPPED";
      case 0x88BD: return "GL_BUFFER_MAP_POINTER";
      case 0x88BF: return "GL_TIME_ELAPSED";
      case 0x88E0: return "GL_STREAM_DRAW";
      case 0x88E1: return "GL_STREAM_READ";
      case 0x88E2: return "GL_STREAM_COPY";
      case 0x88E4: return "GL_STATIC_DRAW";
      case 0x88E5: return "GL_STATIC_READ";
      case 0x88E6: return "GL_STATIC_COPY";
      case 0x88E8: return "GL_DYNAMIC_DRAW";
      case 0x88E9: return "GL_DYNAMIC_READ";
      case 0x88EA: return "GL_DYNAMIC_COPY";
      case 0x88EB: return "GL_PIXEL_PACK_BUFFER";
      case 0x88EC: return "GL_PIXEL_UNPACK_BUFFER";
      case 0x88ED: return "GL_PIXEL_PACK_BUFFER_BINDING";
      case 0x88EF: return "GL_PIXEL_UNPACK_BUFFER_BINDING";
      case 0x88F0: return "GL_DEPTH24_STENCIL8";
      case 0x88F1: return "GL_TEXTURE_STENCIL_SIZE";
      case 0x88F9: return "GL_SRC1_COLOR";
      case 0x88FA: return "GL_ONE_MINUS_SRC1_COLOR";
      case 0x88FB: return "GL_ONE_MINUS_SRC1_ALPHA";
      case 0x88FC: return "GL_MAX_DUAL_SOURCE_DRAW_BUFFERS";
      case 0x88FD: return "GL_VERTEX_ATTRIB_ARRAY_INTEGER";
      case 0x88FE: return "GL_VERTEX_ATTRIB_ARRAY_DIVISOR";
      case 0x88FF: return "GL_MAX_ARRAY_TEXTURE_LAYERS";
      case 0x8904: return "GL_MIN_PROGRAM_TEXEL_OFFSET";
      case 0x8905: return "GL_MAX_PROGRAM_TEXEL_OFFSET";
      case 0x8914: return "GL_SAMPLES_PASSED";
      case 0x8916: return "GL_GEOMETRY_VERTICES_OUT";
      case 0x8917: return "GL_GEOMETRY_INPUT_TYPE";
      case 0x8918: return "GL_GEOMETRY_OUTPUT_TYPE";
      case 0x8919: return "GL_SAMPLER_BINDING";
      case 0x891A: return "GL_CLAMP_VERTEX_COLOR";
      case 0x891B: return "GL_CLAMP_FRAGMENT_COLOR";
      case 0x891C: return "GL_CLAMP_READ_COLOR";
      case 0x891D: return "GL_FIXED_ONLY";
      case 0x8A11: return "GL_UNIFORM_BUFFER";
      case 0x8A28: return "GL_UNIFORM_BUFFER_BINDING";
      case 0x8A29: return "GL_UNIFORM_BUFFER_START";
      case 0x8A2A: return "GL_UNIFORM_BUFFER_SIZE";
      case 0x8A2B: return "GL_MAX_VERTEX_UNIFORM_BLOCKS";
      case 0x8A2C: return "GL_MAX_GEOMETRY_UNIFORM_BLOCKS";
      case 0x8A2D: return "GL_MAX_FRAGMENT_UNIFORM_BLOCKS";
      case 0x8A2E: return "GL_MAX_COMBINED_UNIFORM_BLOCKS";
      case 0x8A2F: return "GL_MAX_UNIFORM_BUFFER_BINDINGS";
      case 0x8A30: return "GL_MAX_UNIFORM_BLOCK_SIZE";
      case 0x8A31: return "GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS";
      case 0x8A32: return "GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS";
      case 0x8A33: return "GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS";
      case 0x8A34: return "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT";
      case 0x8A35: return "GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH";
      case 0x8A36: return "GL_ACTIVE_UNIFORM_BLOCKS";
      case 0x8A37: return "GL_UNIFORM_TYPE";
      case 0x8A38: return "GL_UNIFORM_SIZE";
      case 0x8A39: return "GL_UNIFORM_NAME_LENGTH";
      case 0x8A3A: return "GL_UNIFORM_BLOCK_INDEX";
      case 0x8A3B: return "GL_UNIFORM_OFFSET";
      case 0x8A3C: return "GL_UNIFORM_ARRAY_STRIDE";
      case 0x8A3D: return "GL_UNIFORM_MATRIX_STRIDE";
      case 0x8A3E: return "GL_UNIFORM_IS_ROW_MAJOR";
      case 0x8A3F: return "GL_UNIFORM_BLOCK_BINDING";
      case 0x8A40: return "GL_UNIFORM_BLOCK_DATA_SIZE";
      case 0x8A41: return "GL_UNIFORM_BLOCK_NAME_LENGTH";
      case 0x8A42: return "GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS";
      case 0x8A43: return "GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES";
      case 0x8A44: return "GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER";
      case 0x8A45: return "GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER";
      case 0x8A46: return "GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER";
      case 0x8B30: return "GL_FRAGMENT_SHADER";
      case 0x8B31: return "GL_VERTEX_SHADER";
      case 0x8B49: return "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS";
      case 0x8B4A: return "GL_MAX_VERTEX_UNIFORM_COMPONENTS";
      case 0x8B4B: return "GL_MAX_VARYING_FLOATS";
      case 0x8B4C: return "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS";
      case 0x8B4D: return "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS";
      case 0x8B4F: return "GL_SHADER_TYPE";
      case 0x8B50: return "GL_FLOAT_VEC2";
      case 0x8B51: return "GL_FLOAT_VEC3";
      case 0x8B52: return "GL_FLOAT_VEC4";
      case 0x8B53: return "GL_INT_VEC2";
      case 0x8B54: return "GL_INT_VEC3";
      case 0x8B55: return "GL_INT_VEC4";
      case 0x8B56: return "GL_BOOL";
      case 0x8B57: return "GL_BOOL_VEC2";
      case 0x8B58: return "GL_BOOL_VEC3";
      case 0x8B59: return "GL_BOOL_VEC4";
      case 0x8B5A: return "GL_FLOAT_MAT2";
      case 0x8B5B: return "GL_FLOAT_MAT3";
      case 0x8B5C: return "GL_FLOAT_MAT4";
      case 0x8B5D: return "GL_SAMPLER_1D";
      case 0x8B5E: return "GL_SAMPLER_2D";
      case 0x8B5F: return "GL_SAMPLER_3D";
      case 0x8B60: return "GL_SAMPLER_CUBE";
      case 0x8B61: return "GL_SAMPLER_1D_SHADOW";
      case 0x8B62: return "GL_SAMPLER_2D_SHADOW";
      case 0x8B63: return "GL_SAMPLER_2D_RECT";
      case 0x8B64: return "GL_SAMPLER_2D_RECT_SHADOW";
      case 0x8B65: return "GL_FLOAT_MAT2x3";
      case 0x8B66: return "GL_FLOAT_MAT2x4";
      case 0x8B67: return "GL_FLOAT_MAT3x2";
      case 0x8B68: return "GL_FLOAT_MAT3x4";
      case 0x8B69: return "GL_FLOAT_MAT4x2";
      case 0x8B6A: return "GL_FLOAT_MAT4x3";
      case 0x8B80: return "GL_DELETE_STATUS";
      case 0x8B81: return "GL_COMPILE_STATUS";
      case 0x8B82: return "GL_LINK_STATUS";
      case 0x8B83: return "GL_VALIDATE_STATUS";
      case 0x8B84: return "GL_INFO_LOG_LENGTH";
      case 0x8B85: return "GL_ATTACHED_SHADERS";
      case 0x8B86: return "GL_ACTIVE_UNIFORMS";
      case 0x8B87: return "GL_ACTIVE_UNIFORM_MAX_LENGTH";
      case 0x8B88: return "GL_SHADER_SOURCE_LENGTH";
      case 0x8B89: return "GL_ACTIVE_ATTRIBUTES";
      case 0x8B8A: return "GL_ACTIVE_ATTRIBUTE_MAX_LENGTH";
      case 0x8B8B: return "GL_FRAGMENT_SHADER_DERIVATIVE_HINT";
      case 0x8B8C: return "GL_SHADING_LANGUAGE_VERSION";
      case 0x8B8D: return "GL_CURRENT_PROGRAM";
      case 0x8C10: return "GL_TEXTURE_RED_TYPE";
      case 0x8C11: return "GL_TEXTURE_GREEN_TYPE";
      case 0x8C12: return "GL_TEXTURE_BLUE_TYPE";
      case 0x8C13: return "GL_TEXTURE_ALPHA_TYPE";
      case 0x8C14: return "GL_TEXTURE_LUMINANCE_TYPE";
      case 0x8C15: return "GL_TEXTURE_INTENSITY_TYPE";
      case 0x8C16: return "GL_TEXTURE_DEPTH_TYPE";
      case 0x8C17: return "GL_UNSIGNED_NORMALIZED";
      case 0x8C18: return "GL_TEXTURE_1D_ARRAY";
      case 0x8C19: return "GL_PROXY_TEXTURE_1D_ARRAY";
      case 0x8C1A: return "GL_TEXTURE_2D_ARRAY";
      case 0x8C1B: return "GL_PROXY_TEXTURE_2D_ARRAY";
      case 0x8C1C: return "GL_TEXTURE_BINDING_1D_ARRAY";
      case 0x8C1D: return "GL_TEXTURE_BINDING_2D_ARRAY";
      case 0x8C29: return "GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS";
      case 0x8C2A: return "GL_TEXTURE_BUFFER";
      case 0x8C2B: return "GL_MAX_TEXTURE_BUFFER_SIZE";
      case 0x8C2C: return "GL_TEXTURE_BINDING_BUFFER";
      case 0x8C2D: return "GL_TEXTURE_BUFFER_DATA_STORE_BINDING";
      case 0x8C2F: return "GL_ANY_SAMPLES_PASSED";
      case 0x8C3A: return "GL_R11F_G11F_B10F";
      case 0x8C3B: return "GL_UNSIGNED_INT_10F_11F_11F_REV";
      case 0x8C3D: return "GL_RGB9_E5";
      case 0x8C3E: return "GL_UNSIGNED_INT_5_9_9_9_REV";
      case 0x8C3F: return "GL_TEXTURE_SHARED_SIZE";
      case 0x8C40: return "GL_SRGB";
      case 0x8C41: return "GL_SRGB8";
      case 0x8C42: return "GL_SRGB_ALPHA";
      case 0x8C43: return "GL_SRGB8_ALPHA8";
      case 0x8C44: return "GL_SLUMINANCE_ALPHA";
      case 0x8C45: return "GL_SLUMINANCE8_ALPHA8";
      case 0x8C46: return "GL_SLUMINANCE";
      case 0x8C47: return "GL_SLUMINANCE8";
      case 0x8C48: return "GL_COMPRESSED_SRGB";
      case 0x8C49: return "GL_COMPRESSED_SRGB_ALPHA";
      case 0x8C4A: return "GL_COMPRESSED_SLUMINANCE";
      case 0x8C4B: return "GL_COMPRESSED_SLUMINANCE_ALPHA";
      case 0x8C4C: return "GL_COMPRESSED_SRGB_S3TC_DXT1_EXT";
      case 0x8C4D: return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT";
      case 0x8C4E: return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT";
      case 0x8C4F: return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT";
      case 0x8C76: return "GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH";
      case 0x8C7F: return "GL_TRANSFORM_FEEDBACK_BUFFER_MODE";
      case 0x8C80: return "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS";
      case 0x8C83: return "GL_TRANSFORM_FEEDBACK_VARYINGS";
      case 0x8C84: return "GL_TRANSFORM_FEEDBACK_BUFFER_START";
      case 0x8C85: return "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE";
      case 0x8C87: return "GL_PRIMITIVES_GENERATED";
      case 0x8C88: return "GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN";
      case 0x8C89: return "GL_RASTERIZER_DISCARD";
      case 0x8C8A: return "GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS";
      case 0x8C8B: return "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS";
      case 0x8C8C: return "GL_INTERLEAVED_ATTRIBS";
      case 0x8C8D: return "GL_SEPARATE_ATTRIBS";
      case 0x8C8E: return "GL_TRANSFORM_FEEDBACK_BUFFER";
      case 0x8C8F: return "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING";
      case 0x8CA0: return "GL_POINT_SPRITE_COORD_ORIGIN";
      case 0x8CA1: return "GL_LOWER_LEFT";
      case 0x8CA2: return "GL_UPPER_LEFT";
      case 0x8CA3: return "GL_STENCIL_BACK_REF";
      case 0x8CA4: return "GL_STENCIL_BACK_VALUE_MASK";
      case 0x8CA5: return "GL_STENCIL_BACK_WRITEMASK";
      case 0x8CA6: return "GL_DRAW_FRAMEBUFFER_BINDING";
      case 0x8CA7: return "GL_RENDERBUFFER_BINDING";
      case 0x8CA8: return "GL_READ_FRAMEBUFFER";
      case 0x8CA9: return "GL_DRAW_FRAMEBUFFER";
      case 0x8CAA: return "GL_READ_FRAMEBUFFER_BINDING";
      case 0x8CAB: return "GL_RENDERBUFFER_SAMPLES";
      case 0x8CAC: return "GL_DEPTH_COMPONENT32F";
      case 0x8CAD: return "GL_DEPTH32F_STENCIL8";
      case 0x8CD0: return "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE";
      case 0x8CD1: return "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME";
      case 0x8CD2: return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL";
      case 0x8CD3: return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE";
      case 0x8CD4: return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER";
      case 0x8CD5: return "GL_FRAMEBUFFER_COMPLETE";
      case 0x8CD6: return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
      case 0x8CD7: return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
      case 0x8CDB: return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
      case 0x8CDC: return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
      case 0x8CDD: return "GL_FRAMEBUFFER_UNSUPPORTED";
      case 0x8CDF: return "GL_MAX_COLOR_ATTACHMENTS";
      case 0x8CE0: return "GL_COLOR_ATTACHMENT0";
      case 0x8CE1: return "GL_COLOR_ATTACHMENT1";
      case 0x8CE2: return "GL_COLOR_ATTACHMENT2";
      case 0x8CE3: return "GL_COLOR_ATTACHMENT3";
      case 0x8CE4: return "GL_COLOR_ATTACHMENT4";
      case 0x8CE5: return "GL_COLOR_ATTACHMENT5";
      case 0x8CE6: return "GL_COLOR_ATTACHMENT6";
      case 0x8CE7: return "GL_COLOR_ATTACHMENT7";
      case 0x8CE8: return "GL_COLOR_ATTACHMENT8";
      case 0x8CE9: return "GL_COLOR_ATTACHMENT9";
      case 0x8CEA: return "GL_COLOR_ATTACHMENT10";
      case 0x8CEB: return "GL_COLOR_ATTACHMENT11";
      case 0x8CEC: return "GL_COLOR_ATTACHMENT12";
      case 0x8CED: return "GL_COLOR_ATTACHMENT13";
      case 0x8CEE: return "GL_COLOR_ATTACHMENT14";
      case 0x8CEF: return "GL_COLOR_ATTACHMENT15";
      case 0x8CF0: return "GL_COLOR_ATTACHMENT16";
      case 0x8CF1: return "GL_COLOR_ATTACHMENT17";
      case 0x8CF2: return "GL_COLOR_ATTACHMENT18";
      case 0x8CF3: return "GL_COLOR_ATTACHMENT19";
      case 0x8CF4: return "GL_COLOR_ATTACHMENT20";
      case 0x8CF5: return "GL_COLOR_ATTACHMENT21";
      case 0x8CF6: return "GL_COLOR_ATTACHMENT22";
      case 0x8CF7: return "GL_COLOR_ATTACHMENT23";
      case 0x8CF8: return "GL_COLOR_ATTACHMENT24";
      case 0x8CF9: return "GL_COLOR_ATTACHMENT25";
      case 0x8CFA: return "GL_COLOR_ATTACHMENT26";
      case 0x8CFB: return "GL_COLOR_ATTACHMENT27";
      case 0x8CFC: return "GL_COLOR_ATTACHMENT28";
      case 0x8CFD: return "GL_COLOR_ATTACHMENT29";
      case 0x8CFE: return "GL_COLOR_ATTACHMENT30";
      case 0x8CFF: return "GL_COLOR_ATTACHMENT31";
      case 0x8D00: return "GL_DEPTH_ATTACHMENT";
      case 0x8D20: return "GL_STENCIL_ATTACHMENT";
      case 0x8D40: return "GL_FRAMEBUFFER";
      case 0x8D41: return "GL_RENDERBUFFER";
      case 0x8D42: return "GL_RENDERBUFFER_WIDTH";
      case 0x8D43: return "GL_RENDERBUFFER_HEIGHT";
      case 0x8D44: return "GL_RENDERBUFFER_INTERNAL_FORMAT";
      case 0x8D46: return "GL_STENCIL_INDEX1";
      case 0x8D47: return "GL_STENCIL_INDEX4";
      case 0x8D48: return "GL_STENCIL_INDEX8";
      case 0x8D49: return "GL_STENCIL_INDEX16";
      case 0x8D50: return "GL_RENDERBUFFER_RED_SIZE";
      case 0x8D51: return "GL_RENDERBUFFER_GREEN_SIZE";
      case 0x8D52: return "GL_RENDERBUFFER_BLUE_SIZE";
      case 0x8D53: return "GL_RENDERBUFFER_ALPHA_SIZE";
      case 0x8D54: return "GL_RENDERBUFFER_DEPTH_SIZE";
      case 0x8D55: return "GL_RENDERBUFFER_STENCIL_SIZE";
      case 0x8D56: return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
      case 0x8D57: return "GL_MAX_SAMPLES";
      case 0x8D62: return "GL_RGB565";
      case 0x8D70: return "GL_RGBA32UI";
      case 0x8D71: return "GL_RGB32UI";
      case 0x8D76: return "GL_RGBA16UI";
      case 0x8D77: return "GL_RGB16UI";
      case 0x8D7C: return "GL_RGBA8UI";
      case 0x8D7D: return "GL_RGB8UI";
      case 0x8D82: return "GL_RGBA32I";
      case 0x8D83: return "GL_RGB32I";
      case 0x8D88: return "GL_RGBA16I";
      case 0x8D89: return "GL_RGB16I";
      case 0x8D8E: return "GL_RGBA8I";
      case 0x8D8F: return "GL_RGB8I";
      case 0x8D94: return "GL_RED_INTEGER";
      case 0x8D95: return "GL_GREEN_INTEGER";
      case 0x8D96: return "GL_BLUE_INTEGER";
      case 0x8D97: return "GL_ALPHA_INTEGER";
      case 0x8D98: return "GL_RGB_INTEGER";
      case 0x8D99: return "GL_RGBA_INTEGER";
      case 0x8D9A: return "GL_BGR_INTEGER";
      case 0x8D9B: return "GL_BGRA_INTEGER";
      case 0x8D9F: return "GL_INT_2_10_10_10_REV";
      case 0x8DA7: return "GL_FRAMEBUFFER_ATTACHMENT_LAYERED";
      case 0x8DA8: return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
      case 0x8DAD: return "GL_FLOAT_32_UNSIGNED_INT_24_8_REV";
      case 0x8DB9: return "GL_FRAMEBUFFER_SRGB";
      case 0x8DBB: return "GL_COMPRESSED_RED_RGTC1";
      case 0x8DBC: return "GL_COMPRESSED_SIGNED_RED_RGTC1";
      case 0x8DBD: return "GL_COMPRESSED_RG_RGTC2";
      case 0x8DBE: return "GL_COMPRESSED_SIGNED_RG_RGTC2";
      case 0x8DC0: return "GL_SAMPLER_1D_ARRAY";
      case 0x8DC1: return "GL_SAMPLER_2D_ARRAY";
      case 0x8DC2: return "GL_SAMPLER_BUFFER";
      case 0x8DC3: return "GL_SAMPLER_1D_ARRAY_SHADOW";
      case 0x8DC4: return "GL_SAMPLER_2D_ARRAY_SHADOW";
      case 0x8DC5: return "GL_SAMPLER_CUBE_SHADOW";
      case 0x8DC6: return "GL_UNSIGNED_INT_VEC2";
      case 0x8DC7: return "GL_UNSIGNED_INT_VEC3";
      case 0x8DC8: return "GL_UNSIGNED_INT_VEC4";
      case 0x8DC9: return "GL_INT_SAMPLER_1D";
      case 0x8DCA: return "GL_INT_SAMPLER_2D";
      case 0x8DCB: return "GL_INT_SAMPLER_3D";
      case 0x8DCC: return "GL_INT_SAMPLER_CUBE";
      case 0x8DCD: return "GL_INT_SAMPLER_2D_RECT";
      case 0x8DCE: return "GL_INT_SAMPLER_1D_ARRAY";
      case 0x8DCF: return "GL_INT_SAMPLER_2D_ARRAY";
      case 0x8DD0: return "GL_INT_SAMPLER_BUFFER";
      case 0x8DD1: return "GL_UNSIGNED_INT_SAMPLER_1D";
      case 0x8DD2: return "GL_UNSIGNED_INT_SAMPLER_2D";
      case 0x8DD3: return "GL_UNSIGNED_INT_SAMPLER_3D";
      case 0x8DD4: return "GL_UNSIGNED_INT_SAMPLER_CUBE";
      case 0x8DD5: return "GL_UNSIGNED_INT_SAMPLER_2D_RECT";
      case 0x8DD6: return "GL_UNSIGNED_INT_SAMPLER_1D_ARRAY";
      case 0x8DD7: return "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY";
      case 0x8DD8: return "GL_UNSIGNED_INT_SAMPLER_BUFFER";
      case 0x8DD9: return "GL_GEOMETRY_SHADER";
      case 0x8DDF: return "GL_MAX_GEOMETRY_UNIFORM_COMPONENTS";
      case 0x8DE0: return "GL_MAX_GEOMETRY_OUTPUT_VERTICES";
      case 0x8DE1: return "GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS";
      case 0x8E13: return "GL_QUERY_WAIT";
      case 0x8E14: return "GL_QUERY_NO_WAIT";
      case 0x8E15: return "GL_QUERY_BY_REGION_WAIT";
      case 0x8E16: return "GL_QUERY_BY_REGION_NO_WAIT";
      case 0x8E28: return "GL_TIMESTAMP";
      case 0x8E42: return "GL_TEXTURE_SWIZZLE_R";
      case 0x8E43: return "GL_TEXTURE_SWIZZLE_G";
      case 0x8E44: return "GL_TEXTURE_SWIZZLE_B";
      case 0x8E45: return "GL_TEXTURE_SWIZZLE_A";
      case 0x8E46: return "GL_TEXTURE_SWIZZLE_RGBA";
      case 0x8E4C: return "GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION";
      case 0x8E4D: return "GL_FIRST_VERTEX_CONVENTION";
      case 0x8E4E: return "GL_LAST_VERTEX_CONVENTION";
      case 0x8E4F: return "GL_PROVOKING_VERTEX";
      case 0x8E50: return "GL_SAMPLE_POSITION";
      case 0x8E51: return "GL_SAMPLE_MASK";
      case 0x8E52: return "GL_SAMPLE_MASK_VALUE";
      case 0x8E59: return "GL_MAX_SAMPLE_MASK_WORDS";
      case 0x8E8C: return "GL_COMPRESSED_RGBA_BPTC_UNORM";
      case 0x8E8D: return "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM";
      case 0x8E8E: return "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT";
      case 0x8E8F: return "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT";
      case 0x8F36: return "GL_COPY_READ_BUFFER";
      case 0x8F37: return "GL_COPY_WRITE_BUFFER";
      case 0x8F94: return "GL_R8_SNORM";
      case 0x8F95: return "GL_RG8_SNORM";
      case 0x8F96: return "GL_RGB8_SNORM";
      case 0x8F97: return "GL_RGBA8_SNORM";
      case 0x8F98: return "GL_R16_SNORM";
      case 0x8F99: return "GL_RG16_SNORM";
      case 0x8F9A: return "GL_RGB16_SNORM";
      case 0x8F9B: return "GL_RGBA16_SNORM";
      case 0x8F9C: return "GL_SIGNED_NORMALIZED";
      case 0x8F9D: return "GL_PRIMITIVE_RESTART";
      case 0x8F9E: return "GL_PRIMITIVE_RESTART_INDEX";
      case 0x906F: return "GL_RGB10_A2UI";
      case 0x9100: return "GL_TEXTURE_2D_MULTISAMPLE";
      case 0x9101: return "GL_PROXY_TEXTURE_2D_MULTISAMPLE";
      case 0x9102: return "GL_TEXTURE_2D_MULTISAMPLE_ARRAY";
      case 0x9103: return "GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY";
      case 0x9104: return "GL_TEXTURE_BINDING_2D_MULTISAMPLE";
      case 0x9105: return "GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY";
      case 0x9106: return "GL_TEXTURE_SAMPLES";
      case 0x9107: return "GL_TEXTURE_FIXED_SAMPLE_LOCATIONS";
      case 0x9108: return "GL_SAMPLER_2D_MULTISAMPLE";
      case 0x9109: return "GL_INT_SAMPLER_2D_MULTISAMPLE";
      case 0x910A: return "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE";
      case 0x910B: return "GL_SAMPLER_2D_MULTISAMPLE_ARRAY";
      case 0x910C: return "GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
      case 0x910D: return "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
      case 0x910E: return "GL_MAX_COLOR_TEXTURE_SAMPLES";
      case 0x910F: return "GL_MAX_DEPTH_TEXTURE_SAMPLES";
      case 0x9110: return "GL_MAX_INTEGER_SAMPLES";
      case 0x9111: return "GL_MAX_SERVER_WAIT_TIMEOUT";
      case 0x9112: return "GL_OBJECT_TYPE";
      case 0x9113: return "GL_SYNC_CONDITION";
      case 0x9114: return "GL_SYNC_STATUS";
      case 0x9115: return "GL_SYNC_FLAGS";
      case 0x9116: return "GL_SYNC_FENCE";
      case 0x9117: return "GL_SYNC_GPU_COMMANDS_COMPLETE";
      case 0x9118: return "GL_UNSIGNALED";
      case 0x9119: return "GL_SIGNALED";
      case 0x911A: return "GL_ALREADY_SIGNALED";
      case 0x911B: return "GL_TIMEOUT_EXPIRED";
      case 0x911C: return "GL_CONDITION_SATISFIED";
      case 0x911D: return "GL_WAIT_FAILED";
      case 0x911F: return "GL_BUFFER_ACCESS_FLAGS";
      case 0x9120: return "GL_BUFFER_MAP_LENGTH";
      case 0x9121: return "GL_BUFFER_MAP_OFFSET";
      case 0x9122: return "GL_MAX_VERTEX_OUTPUT_COMPONENTS";
      case 0x9123: return "GL_MAX_GEOMETRY_INPUT_COMPONENTS";
      case 0x9124: return "GL_MAX_GEOMETRY_OUTPUT_COMPONENTS";
      case 0x9125: return "GL_MAX_FRAGMENT_INPUT_COMPONENTS";
      case 0x9126: return "GL_CONTEXT_PROFILE_MASK";
      case 0x9143: return "GL_MAX_DEBUG_MESSAGE_LENGTH";
      case 0x9144: return "GL_MAX_DEBUG_LOGGED_MESSAGES";
      case 0x9145: return "GL_DEBUG_LOGGED_MESSAGES";
      case 0x9146: return "GL_DEBUG_SEVERITY_HIGH";
      case 0x9147: return "GL_DEBUG_SEVERITY_MEDIUM";
      case 0x9148: return "GL_DEBUG_SEVERITY_LOW";
      case 0x9270: return "GL_COMPRESSED_R11_EAC";
      case 0x9271: return "GL_COMPRESSED_SIGNED_R11_EAC";
      case 0x9272: return "GL_COMPRESSED_RG11_EAC";
      case 0x9273: return "GL_COMPRESSED_SIGNED_RG11_EAC";
      case 0x9274: return "GL_COMPRESSED_RGB8_ETC2";
      case 0x9275: return "GL_COMPRESSED_SRGB8_ETC2";
      case 0x9276: return "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2";
      case 0x9277: return "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2";
      case 0x9278: return "GL_COMPRESSED_RGBA8_ETC2_EAC";
      case 0x9279: return "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC";
      case 0x92E0: return "GL_DEBUG_OUTPUT";
      case 0x93B0: return "GL_COMPRESSED_RGBA_ASTC_4x4_KHR";
      case 0x93B1: return "GL_COMPRESSED_RGBA_ASTC_5x4_KHR";
      case 0x93B2: return "GL_COMPRESSED_RGBA_ASTC_5x5_KHR";
      case 0x93B3: return "GL_COMPRESSED_RGBA_ASTC_6x5_KHR";
      case 0x93B4: return "GL_COMPRESSED_RGBA_ASTC_6x6_KHR";
      case 0x93B5: return "GL_COMPRESSED_RGBA_ASTC_8x5_KHR";
      case 0x93B6: return "GL_COMPRESSED_RGBA_ASTC_8x6_KHR";
      case 0x93B7: return "GL_COMPRESSED_RGBA_ASTC_8x8_KHR";
      case 0x93B8: return "GL_COMPRESSED_RGBA_ASTC_10x5_KHR";
      case 0x93B9: return "GL_COMPRESSED_RGBA_ASTC_10x6_KHR";
      case 0x93BA: return "GL_COMPRESSED_RGBA_ASTC_10x8_KHR";
      case 0x93BB: return "GL_COMPRESSED_RGBA_ASTC_10x10_KHR";
      case 0x93BC: return "GL_COMPRESSED_RGBA_ASTC_12x10_KHR";
      case 0x93BD: return "GL_COMPRESSED_RGBA_ASTC_12x12_KHR";
      case 0x93D0: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR";
      case 0x93D1: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR";
      case 0x93D2: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR";
      case 0x93D3: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR";
      case 0x93D4: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR";
      case 0x93D5: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR";
      case 0x93D6: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR";
      case 0x93D7: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR";
      case 0x93D8: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR";
      case 0x93D9: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR";
      case 0x93DA: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR";
      case 0x93DB: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR";
      case 0x93DC: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR";
      case 0x93DD: return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR";
      case 0x00010000: return "GL_EVAL_BIT";
      case 0x00020000: return "GL_LIST_BIT";
      case 0x00040000: return "GL_TEXTURE_BIT";
      case 0x00080000: return "GL_SCISSOR_BIT";
      case 0x20000000: return "GL_MULTISAMPLE_BIT";
      case 0xFFFFFFFF: return "GL_ALL_ATTRIB_BITS";
      default: return "?";
   }
}

////////// FEATURES (IMPL) ///////////////////////////////////////////////////

bool gl10() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_1_0;
}
bool gl11() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_1_1;
}
bool gl12() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_1_2;
}
bool gl13() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_1_3;
}
bool gl14() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_1_4;
}
bool gl15() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_1_5;
}
bool gl20() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_2_0;
}
bool gl21() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_2_1;
}
bool gl30() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_3_0;
}
bool gl31() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_3_1;
}
bool gl32() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_3_2;
}
bool gl33() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_version_3_3;
}

////////// EXTENSIONS (IMPL) /////////////////////////////////////////////////

bool khr_debug() noexcept {
   return BE_GFX_BGL_CONTEXT.bgl_khr_debug;
}

////////// COMMANDS (IMPL) ///////////////////////////////////////////////////

const GLubyte *glGetString(GLenum name) noexcept {
   return BE_GFX_BGL_CONTEXT.bglGetString(name);
}
void glTexCoord2fv(const GLfloat * v) noexcept {
   return BE_GFX_BGL_CONTEXT.bglTexCoord2fv(v);
}
void glTexParameteri(GLenum target, GLenum pname, GLint param) noexcept {
   return BE_GFX_BGL_CONTEXT.bglTexParameteri(target, pname, param);
}
void glVertex2f(GLfloat x, GLfloat y) noexcept {
   return BE_GFX_BGL_CONTEXT.bglVertex2f(x, y);
}
void glEnable(GLenum cap) noexcept {
   return BE_GFX_BGL_CONTEXT.bglEnable(cap);
}
void glBegin(GLenum mode) noexcept {
   return BE_GFX_BGL_CONTEXT.bglBegin(mode);
}
void glBindTexture(GLenum target, GLuint texture) noexcept {
   return BE_GFX_BGL_CONTEXT.bglBindTexture(target, texture);
}
void glClear(GLbitfield mask) noexcept {
   return BE_GFX_BGL_CONTEXT.bglClear(mask);
}
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) noexcept {
   return BE_GFX_BGL_CONTEXT.bglClearColor(red, green, blue, alpha);
}
void glColor3fv(const GLfloat * v) noexcept {
   return BE_GFX_BGL_CONTEXT.bglColor3fv(v);
}
void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam) noexcept {
   return BE_GFX_BGL_CONTEXT.bglDebugMessageCallback(callback, userParam);
}
void glDeleteTextures(GLsizei n, const GLuint * textures) noexcept {
   return BE_GFX_BGL_CONTEXT.bglDeleteTextures(n, textures);
}
void glEnd() noexcept {
   return BE_GFX_BGL_CONTEXT.bglEnd();
}
void glGenTextures(GLsizei n, GLuint * textures) noexcept {
   return BE_GFX_BGL_CONTEXT.bglGenTextures(n, textures);
}
void glGetIntegerv(GLenum pname, GLint * data) noexcept {
   return BE_GFX_BGL_CONTEXT.bglGetIntegerv(pname, data);
}
const GLubyte *glGetStringi(GLenum name, GLuint index) noexcept {
   return BE_GFX_BGL_CONTEXT.bglGetStringi(name, index);
}
void glPixelStorei(GLenum pname, GLint param) noexcept {
   return BE_GFX_BGL_CONTEXT.bglPixelStorei(pname, param);
}
void glTexEnvi(GLenum target, GLenum pname, GLint param) noexcept {
   return BE_GFX_BGL_CONTEXT.bglTexEnvi(target, pname, param);
}
void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) noexcept {
   return BE_GFX_BGL_CONTEXT.bglTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) noexcept {
   return BE_GFX_BGL_CONTEXT.bglViewport(x, y, width, height);
}

} // be::gfx::gl

#endif

#endif

/* ######################### END OF GENERATED CODE ######################### */
