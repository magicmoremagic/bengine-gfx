#if !defined(BE_TEXI_UNIFORM_RESAMPLE_HPP_) && !defined(DOXYGEN)
#include "uniform_resample.hpp"
#elif !defined(BE_TEXI_UNIFORM_RESAMPLE_INL_)
#define BE_TEXI_UNIFORM_RESAMPLE_INL_

namespace be {
namespace texi {

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename F, typename W>
void uniform_resample_3d(image out, image in, F32 scale, quat rotation, vec3 offset, F32 support_scale, F filter, W wrap) {
   F32 sample_dst_mult = (scale > 1.f ? 1.f : scale) / support_scale;
   F32 pixel_support = support_scale * (scale > 1.f ? 1.f : (1.f / scale)) * FilterSupportRange<F>().operator()<float>();
   F32 pixel_support2 = pixel_support * pixel_support;

   auto out_size = out.extent();
   std::map<F32, F32> memo;
   image::extent_type out_tc;
   for (out_tc.z = 0; out_tc.z < out_size.z; ++out_tc.z) {
      for (out_tc.y = 0; out_tc.y < out_size.y; ++out_tc.y) {
         for (out_tc.x = 0; out_tc.x < out_size.x; ++out_tc.x) {
            vec3 in_target = offset + rotation * ((vec3(out_tc) + 0.5f) / scale);

            vec3 in_min_pixel = glm::floor(in_target - pixel_support);
            vec3 in_max_pixel = glm::floor(in_target + pixel_support);

            T out_data;
            F32 total_weight(0);

            vec3 in_pixel;
            for (in_pixel.z = in_min_pixel.z; in_pixel.z <= in_max_pixel.z; ++in_pixel.z) {
               for (in_pixel.y = in_min_pixel.y; in_pixel.y <= in_max_pixel.y; ++in_pixel.y) {
                  for (in_pixel.x = in_min_pixel.x; in_pixel.x <= in_max_pixel.x; ++in_pixel.x) {
                     vec3 in_pixel_center = in_pixel + 0.5f;
                     vec3 target_delta = in_target - in_pixel_center;
                     F32 length2 = glm::dot(target_delta, target_delta);
                     if (length2 <= pixel_support2) {
                        F32 weight;
                        auto it = memo.find(length2);
                        if (it == memo.end()) {
                           F32 target_dst = sqrt(length2);
                           weight = filter(target_dst * sample_dst_mult);
                           memo.emplace(length2, weight);
                        } else {
                           weight = it->second;
                        }

                        image::extent_type in_tc = wrap(in, image::extent_type(in_pixel), weight);
                        if (weight > 0) {
                           out_data += in.load<T>(in_tc) * weight;
                           total_weight += weight;
                        }
                     }
                  }
               }
            }

            if (total_weight != 0) {
               out_data *= 1.f / total_weight;
            }

            out.store<T>(out_tc, out_data);
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename F, typename W>
void uniform_resample_2d(image out, image in, F32 scale, F32 rotation, vec2 offset, F32 support_scale, F filter, W wrap) {
   F32 sample_dst_mult = (scale > 1.f ? 1.f : scale) / support_scale;
   F32 pixel_support = support_scale * (scale > 1.f ? 1.f : (1.f / scale)) * FilterSupportRange<F>().operator()<float>();
   F32 pixel_support2 = pixel_support * pixel_support;

   F32 rots = sin(rotation);
   F32 rotc = cos(rotation);
   mat2 rot = mat2(rotc, rots, -rots, rotc);

   auto out_size = out.extent();
   std::map<F32, F32> memo;
   image::extent_type out_tc;
   for (out_tc.y = 0; out_tc.y < out_size.y; ++out_tc.y) {
      for (out_tc.x = 0; out_tc.x < out_size.x; ++out_tc.x) {
         vec2 in_target = offset + rot * ((vec2(out_tc) + 0.5f) / scale);

         vec2 in_min_pixel = glm::floor(in_target - pixel_support);
         vec2 in_max_pixel = glm::floor(in_target + pixel_support);

         T out_data;
         F32 total_weight(0);

         vec2 in_pixel;
         for (in_pixel.y = in_min_pixel.y; in_pixel.y <= in_max_pixel.y; ++in_pixel.y) {
            for (in_pixel.x = in_min_pixel.x; in_pixel.x <= in_max_pixel.x; ++in_pixel.x) {
               vec2 in_pixel_center = in_pixel + 0.5f;
               vec2 target_delta = in_target - in_pixel_center;
               F32 length2 = glm::dot(target_delta, target_delta);
               if (length2 <= pixel_support2) {
                  F32 weight;
                  auto it = memo.find(length2);
                  if (it == memo.end()) {
                     F32 target_dst = sqrt(length2);
                     weight = filter(target_dst * sample_dst_mult);
                     memo.emplace(length2, weight);
                  } else {
                     weight = it->second;
                  }

                  image::extent_type in_tc = wrap(in, image::extent_type((int)in_pixel.x, (int)in_pixel.y, 0), weight);
                  if (weight > 0) {
                     out_data += in.load<T>(in_tc) * weight;
                     total_weight += weight;
                  }
               }
            }
         }

         if (total_weight != 0) {
            out_data *= 1.f / total_weight;
         }

         out.store<T>(out_tc, out_data);
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename F, typename W>
void uniform_resample_1d(image out, image in, F32 scale, F32 offset, F32 support_scale, F filter, W wrap) {
   F32 sample_dst_mult = (scale > 1.f ? 1.f : scale) / support_scale;
   F32 pixel_support = support_scale * (scale > 1.f ? 1.f : (1.f / scale)) * FilterSupportRange<F>().operator()<float>();

   auto out_size = out.extent();
   std::map<F32, F32> memo;
   image::extent_type out_tc;
   for (out_tc.x = 0; out_tc.x < out_size.x; ++out_tc.x) {
      F32 in_target = offset + (F32(out_tc.x) + 0.5f) / scale;
      F32 in_min_pixel = floor(in_target - pixel_support);
      F32 in_max_pixel = floor(in_target + pixel_support);

      T out_data;
      F32 total_weight(0);
      for (F32 in_pixel = in_min_pixel; in_pixel <= in_max_pixel; ++in_pixel) {
         F32 in_pixel_center = in_pixel + 0.5f;
         F32 target_dst = abs(in_target - in_pixel_center);
         F32 weight;
         auto it = memo.find(target_dst);
         if (it == memo.end()) {
            weight = filter(target_dst * sample_dst_mult);
            memo.emplace(target_dst, weight);
         } else {
            weight = it->second;
         }

         image::extent_type in_tc = wrap(in, image::extent_type((int)in_pixel, 0, 0), weight);
         if (weight > 0) {
            out_data += in.load<T>(in_tc) * weight;
            total_weight += weight;
         }
      }

      if (total_weight != 0) {
         out_data *= 1.f / total_weight;
      }

      out.store<T>(out_tc, out_data);
   }
}

} // be::texi
} // be

#endif
