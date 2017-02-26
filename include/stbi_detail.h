#pragma once
#ifndef BE_GFX_STBI_DETAIL_H_
#define BE_GFX_STBI_DETAIL_H_

#pragma warning(push)
//#pragma warning(disable: 4456) // local hides local
//#pragma warning(disable: 4457) // local hides parameter
#include <stb/stb_image.h>

#ifdef __cplusplus
extern "C" {
#endif

STBIDEF void* be_stbi_load_jpeg_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
STBIDEF void* be_stbi_load_png_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
STBIDEF void* be_stbi_load_bmp_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
STBIDEF void* be_stbi_load_gif_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
STBIDEF void* be_stbi_load_psd_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
STBIDEF void* be_stbi_load_pic_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
STBIDEF void* be_stbi_load_pnm_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
STBIDEF void* be_stbi_load_hdr_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);
STBIDEF void* be_stbi_load_tga_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc);

#ifdef __cplusplus
}
#endif

#pragma warning(pop)

#endif
