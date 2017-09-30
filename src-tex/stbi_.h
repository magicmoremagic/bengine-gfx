#pragma once
#ifndef BE_GFX_TEX_STBI_H_
#define BE_GFX_TEX_STBI_H_

#ifndef STBI_NO_STDIO
#define STBI_NO_STDIO
#endif

#ifndef STBI_NO_PIC
#define STBI_NO_PIC
#endif

#include <stb/stb_image.h>

#ifdef __cplusplus
extern "C" {
#endif

   typedef int (*be_stbi_info_func)(const stbi_uc*, int, int*, int*, int*, int*);

   STBIDEF int be_stbi_jpeg_info_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF int be_stbi_png_info_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF int be_stbi_bmp_info_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF int be_stbi_gif_info_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF int be_stbi_psd_info_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF int be_stbi_pnm_info_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF int be_stbi_hdr_info_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF int be_stbi_tga_info_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);

   typedef void* (*be_stbi_load_func)(const stbi_uc*, int, int*, int*, int*, int*);

   STBIDEF void* be_stbi_load_jpeg_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF void* be_stbi_load_png_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF void* be_stbi_load_bmp_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF void* be_stbi_load_gif_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF void* be_stbi_load_psd_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF void* be_stbi_load_pnm_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF void* be_stbi_load_hdr_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
   STBIDEF void* be_stbi_load_tga_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);

#ifdef __cplusplus
}
#endif

#endif
