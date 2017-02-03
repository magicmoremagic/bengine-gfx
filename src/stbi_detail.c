#define STB_IMAGE_IMPLEMENTATION
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "stbi_detail.h"

typedef void* (*be_stbi__load_func)(stbi__context*, int*, int*, int*, stbi__result_info*);

static void* be_stbi__load_jpeg(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   if (stbi__jpeg_test(s)) {
      return stbi__jpeg_load(s,x,y,comp,0, ri);
   } else {
      return NULL;
   }
}

static void* be_stbi__load_png(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   if (stbi__png_test(s)) {
      return stbi__png_load(s,x,y,comp,0, ri);
   } else {
      return NULL;
   }
}

static void* be_stbi__load_bmp(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   if (stbi__bmp_test(s)) {
      return stbi__bmp_load(s,x,y,comp,0, ri);
   } else {
      return NULL;
   }
}

static void* be_stbi__load_gif(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   if (stbi__gif_test(s)) {
      return stbi__gif_load(s,x,y,comp,0, ri);
   } else {
      return NULL;
   }
}

static void* be_stbi__load_psd(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   if (stbi__psd_test(s)) {
      return stbi__psd_load(s,x,y,comp,0, ri, 8);
   } else {
      return NULL;
   }
}

static void* be_stbi__load_pic(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   if (stbi__pic_test(s)) {
      return stbi__pic_load(s,x,y,comp,0, ri);
   } else {
      return NULL;
   }
}

static void* be_stbi__load_pnm(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   if (stbi__pnm_test(s)) {
      return stbi__pnm_load(s,x,y,comp,0, ri);
   } else {
      return NULL;
   }
}

static void* be_stbi__load_hdr(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   if (stbi__hdr_test(s)) {
      ri->bits_per_channel = 32;
      return stbi__hdr_load(s, x,y,comp,0, ri);
   } else {
      return NULL;
   }
}

static void* be_stbi__load_tga(stbi__context* s, int* x, int* y, int* comp, stbi__result_info* ri) {
   // test tga last because it's a crappy test!
   if (stbi__tga_test(s)) {
      return stbi__tga_load(s,x,y,comp,0, ri);
   } else {
      return NULL;
   }
}

static void* be_stbi__load(be_stbi__load_func func, stbi__context* s, int* x, int* y, int* comp, int* bpc) {
   stbi__result_info ri;
   memset(&ri, 0, sizeof(ri)); // make sure it's initialized if we add new fields
   ri.bits_per_channel = 8; // default is 8 so most paths don't have to be changed
   ri.channel_order = STBI_ORDER_RGB; // all current input & output are this, but this is here so we can add BGR order
   ri.num_channels = 0;

   void *result = func(s, x, y, comp, &ri);
   if (result == NULL) {
      return NULL;
   }

   if (bpc != NULL) {
      *bpc = ri.bits_per_channel;
   }
   
   return result;
}

STBIDEF void* be_stbi_load_jpeg_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_jpeg, &s, x, y, comp, bpc);
}

STBIDEF void* be_stbi_load_png_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_png, &s, x, y, comp, bpc);
}

STBIDEF void* be_stbi_load_bmp_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_bmp, &s, x, y, comp, bpc);
}

STBIDEF void* be_stbi_load_gif_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_gif, &s, x, y, comp, bpc);
}

STBIDEF void* be_stbi_load_psd_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_psd, &s, x, y, comp, bpc);
}

STBIDEF void* be_stbi_load_pic_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_pic, &s, x, y, comp, bpc);
}

STBIDEF void* be_stbi_load_pnm_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_pnm, &s, x, y, comp, bpc);
}

STBIDEF void* be_stbi_load_hdr_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_hdr, &s, x, y, comp, bpc);
}

STBIDEF void* be_stbi_load_tga_from_memory(const stbi_uc* buffer, int len, int* x, int* y, int* comp, int* bpc) {
   stbi__context s;
   stbi__start_mem(&s,buffer,len);
   return be_stbi__load(be_stbi__load_tga, &s, x, y, comp, bpc);
}
