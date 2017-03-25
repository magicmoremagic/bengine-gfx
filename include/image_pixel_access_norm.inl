#if !defined(BE_GFX_IMAGE_PIXEL_ACCESS_NORM_HPP_) && !defined(DOXYGEN)
#include "image_pixel_access_norm.hpp"
#elif !defined(BE_GFX_IMAGE_PIXEL_ACCESS_NORM_INL_)
#define BE_GFX_IMAGE_PIXEL_ACCESS_NORM_INL_

namespace be::gfx {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <U8 Dimension>
struct image_coord_type { };
template <> struct image_coord_type<1> { using type = I32; };
template <> struct image_coord_type<2> { using type = ivec2; };
template <> struct image_coord_type<3> { using type = ivec3; };

///////////////////////////////////////////////////////////////////////////////
template <typename UnsignedType, std::size_t Bits>
I32 image_component_to_signed(UnsignedType data) {
   constexpr UnsignedType sign_bit_mask = 1ull << (Bits - 1ull);
   if (0 == (data & sign_bit_mask)) {
      return static_cast<I32>(data);
   } else {
      return static_cast<I32>(data | (~U32(0) ^ ((1ull << Bits) - 1ull)));
   }
}

#pragma region image_component_rawnorm

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits, ImageComponentType ComponentType>
struct image_component_rawnorm {
   static_assert(Bits > 0);
   static F32 decode(T data) {
      return 0.f;
   }
   static T encode(F32 component) {
      return T();
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits>
struct image_component_rawnorm<T, Bits, ImageComponentType::uint> {
   static_assert(Bits > 0);
   static F32 decode(T data) {
      return static_cast<F32>(data);
   }
   static T encode(F32 component) {
      F32 scale = static_cast<F32>((1ull << Bits) - 1ull);
      return static_cast<T>(glm::clamp(std::round(component), 0.f, scale));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 64, ImageComponentType::uint> {
   static F32 decode(T data) {
      return static_cast<F32>(data);
   }
   static T encode(F32 component) {
      F32 scale = static_cast<F32>(~U64(0));
      return static_cast<T>(glm::clamp(std::round(component), 0.f, scale));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits>
struct image_component_rawnorm<T, Bits, ImageComponentType::sint> {
   static_assert(Bits > 1);
   static F32 decode(T data) {
      return static_cast<F32>(image_component_to_signed<T, Bits>(data));
   }
   static T encode(F32 component) {
      F32 scale = static_cast<F32>((1ull << (Bits - 1)) - 1ull);
      component = glm::clamp(std::round(component), -scale - 1, scale);
      if (component < 0) {
         component += static_cast<F32>(1ull << Bits);
      }
      return static_cast<T>(component);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 1, ImageComponentType::sint> {
   static F32 decode(T data) {
      return static_cast<F32>(data);
   }
   static T encode(F32 component) {
      component = glm::clamp(std::round(component), 0.f, 1.f);
      return static_cast<T>(component);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 64, ImageComponentType::sint> {
   static F32 decode(T data) {
      return static_cast<F32>(static_cast<I64>(data));
   }
   static T encode(F32 component) {
      F32 scale = static_cast<F32>((1ull << 63) - 1ull);
      component = glm::clamp(std::round(component), -scale - 1, scale);
      return static_cast<T>(static_cast<I64>(component));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits>
struct image_component_rawnorm<T, Bits, ImageComponentType::unorm> {
   static_assert(Bits > 0);
   static constexpr F32 scale = static_cast<F32>((1ull << Bits) - 1ull);
   static constexpr F32 invscale = 1.f / scale;
   static F32 decode(T data) {
      return static_cast<F32>(data) * invscale;
   }
   static T encode(F32 component) {
      return static_cast<T>(std::round(glm::clamp(component, 0.f, 1.f) * scale));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 64, ImageComponentType::unorm> {
   static constexpr F32 scale = static_cast<F32>(~U64(0));
   static constexpr F32 invscale = 1.f / scale;
   static F32 decode(T data) {
      return static_cast<F32>(data) * invscale;
   }
   static T encode(F32 component) {
      return static_cast<T>(std::round(glm::clamp(component, 0.f, 1.f) * scale));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits>
struct image_component_rawnorm<T, Bits, ImageComponentType::snorm> {
   static_assert(Bits > 1);
   static constexpr F32 scale = static_cast<F32>((1ull << (Bits - 1)) - 1ull);
   static constexpr F32 invscale = 1.f / scale;
   static F32 decode(T data) {
      return std::max(-scale, static_cast<F32>(image_component_to_signed<T, Bits>(data))) * invscale;
   }
   static T encode(F32 component) {
      component = std::round(glm::clamp(component, -1.f, 1.f) * scale);
      if (component < 0) {
         component += static_cast<F32>(1ull << Bits);
      }
      return static_cast<T>(component);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 1, ImageComponentType::snorm> {
   static F32 decode(T data) {
      return std::max(0.f, static_cast<F32>(data));
   }
   static T encode(F32 component) {
      component = std::round(glm::clamp(component, 0.f, 1.f));
      return static_cast<T>(component);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 64, ImageComponentType::snorm> {
   static constexpr F32 scale = static_cast<F32>((1ull << 63) - 1ull);
   static constexpr F32 invscale = 1.f / scale;
   static F32 decode(T data) {
      return std::max(-scale, static_cast<F32>(static_cast<I64>(data))) * invscale;
   }
   static T encode(F32 component) {
      component = std::round(glm::clamp(component, -1.f, 1.f) * scale);
      return static_cast<T>(static_cast<I64>(component));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 11, ImageComponentType::ufloat> {
   static constexpr int f11_mantissa_bits = 6;
   static constexpr int f11_exponent_bits = 5;
   static constexpr U16 f11_mantissa_mask = (1u << f11_mantissa_bits) - 1u;
   static constexpr U16 f11_exponent_mask = ((1u << (f11_exponent_bits + f11_mantissa_bits)) - 1u) ^ f11_mantissa_mask;
   static constexpr U16 f11_exponent_basis = (1u << (f11_exponent_bits - 1)) - 1u;

   static constexpr int f32_mantissa_bits = 23;
   static constexpr int f32_exponent_bits = 8;
   static constexpr U32 f32_mantissa_mask = (1u << f32_mantissa_bits) - 1u;
   static constexpr U32 f32_exponent_mask = ((1u << (f32_exponent_bits + f32_mantissa_bits)) - 1u) ^ f32_mantissa_mask;
   static constexpr U16 f32_exponent_basis = (1u << (f32_exponent_bits - 1)) - 1u;
   static constexpr U32 f32_sign_mask = 1u << (f32_mantissa_bits + f32_exponent_bits);

   static constexpr int shift = f32_mantissa_bits - f11_mantissa_bits;

   static F32 decode(T data) {
      F32 value;
      U16 f11_data = (U16)data;
      U16 f11_exponent = f11_data & f11_exponent_mask;
      if (f11_exponent == 0) {
         if (f11_data == 0) {
            // zero -> zero
            value = 0.f;
         } else {
            // subnormal -> normal
            U32 f11_mantissa = f11_data & f11_mantissa_mask;
            U32 zero_bits;
            std::tie(zero_bits, std::ignore) = bitscan_rev(f11_mantissa);
            zero_bits = f11_mantissa_bits - 1 - zero_bits;
            U32 f32_data = static_cast<U32>(f11_data) << (f32_mantissa_bits - f11_mantissa_bits + zero_bits + 1); // one extra bit because the highest 1 becomes the implicit normal mantissa MSB
            f32_data &= f32_mantissa_mask;
            U32 f32_exponent = (f32_exponent_basis - f11_exponent_basis - zero_bits) << f32_mantissa_bits;
            f32_data |= f32_exponent;
            memcpy(&value, &f32_data, sizeof(F32));
         }
      } else if (f11_exponent == f11_exponent_mask) {
         if (f11_data == f11_exponent_mask) {
            // inf -> inf
            constexpr U32 f32_data = f32_exponent_mask;
            memcpy(&value, &f32_data, sizeof(F32));
         } else {
            // any nan -> qnan
            constexpr U32 f32_data = f32_exponent_mask | (f32_mantissa_mask & ~0);
            memcpy(&value, &f32_data, sizeof(F32));
         }
      } else {
         // normal -> normal
         U32 f32_data = ((f11_exponent << shift) + ((f32_exponent_basis - f11_exponent_basis) << f32_mantissa_bits)) | ((f11_data & f11_mantissa_mask) << shift);
         memcpy(&value, &f32_data, sizeof(F32));
      }
      return value;
   }

   static T encode(F32 component) {
      U16 f11_data;
      U32 f32_data;
      memcpy(&f32_data, &component, sizeof(U32));

      U32 f32_exponent = f32_data & f32_exponent_mask;

      constexpr U32 min_normal_exponent =  (U32(f32_exponent_basis - f11_exponent_basis + 1)) << f32_mantissa_bits;
      constexpr U32 max_exponent = (U32(f32_exponent_basis + f11_exponent_basis)) << f32_mantissa_bits;

      if (f32_exponent < min_normal_exponent) {
         // normal, subnormal, or zero -> subnormal or zero
         if (f32_exponent < min_normal_exponent - (f11_mantissa_bits << f32_mantissa_bits) || (f32_data & f32_sign_mask) != 0) {
            // negative, normal, subnormal, or zero -> zero
            f11_data = 0u;
         } else {
            // normal -> subnormal
            U32 mantissa = (1 << f32_mantissa_bits) | f32_data & f32_mantissa_mask; // add implicit MSB
            f11_data = static_cast<U16>(mantissa >> (shift + ((min_normal_exponent - f32_exponent) >> f32_mantissa_bits)));
         }
      } else if (f32_exponent > max_exponent) {
         // normal, inf or nan -> zero, inf or nan
         if (f32_exponent == f32_exponent_mask) {
            // inf or nan -> inf or nan
            if ((f32_data & f32_mantissa_mask) == 0) {
               // inf -> zero or inf
               if ((f32_data & f32_sign_mask) == 0) {
                  // inf -> inf
                  f11_data = f11_exponent_mask;
               } else {
                  // inf -> zero
                  f11_data = 0u;
               }
            } else {
               // nan -> nan
               f11_data = f11_exponent_mask | (f11_mantissa_mask & ~U16(0));
            }
         } else if ((f32_data & f32_sign_mask) == 0) {
            // positive normal -> inf
            f11_data = f11_exponent_mask;
         } else {
            // negative normal -> zero
            f11_data = 0u;
         }
      } else if ((f32_data & f32_sign_mask) != 0) {
         // negative normal -> zero
         f11_data = 0u;
      } else {
         // positive normal -> normal
         f11_data = static_cast<U16>(((f32_exponent - ((f32_exponent_basis - f11_exponent_basis) << f32_mantissa_bits)) | (f32_data & f32_mantissa_mask)) >> shift);
      }

      return static_cast<T>(f11_data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 10, ImageComponentType::ufloat> {
   static constexpr int f10_mantissa_bits = 5;
   static constexpr int f10_exponent_bits = 5;
   static constexpr U16 f10_mantissa_mask = (1u << f10_mantissa_bits) - 1u;
   static constexpr U16 f10_exponent_mask = ((1u << (f10_exponent_bits + f10_mantissa_bits)) - 1u) ^ f10_mantissa_mask;
   static constexpr U16 f10_exponent_basis = (1u << (f10_exponent_bits - 1)) - 1u;

   static constexpr int f32_mantissa_bits = 23;
   static constexpr int f32_exponent_bits = 8;
   static constexpr U32 f32_mantissa_mask = (1u << f32_mantissa_bits) - 1u;
   static constexpr U32 f32_exponent_mask = ((1u << (f32_exponent_bits + f32_mantissa_bits)) - 1u) ^ f32_mantissa_mask;
   static constexpr U16 f32_exponent_basis = (1u << (f32_exponent_bits - 1)) - 1u;
   static constexpr U32 f32_sign_mask = 1u << (f32_mantissa_bits + f32_exponent_bits);

   static constexpr int shift = f32_mantissa_bits - f10_mantissa_bits;

   static F32 decode(T data) {
      F32 value;
      U16 f10_data = (U16)data;
      U16 f10_exponent = f10_data & f10_exponent_mask;
      if (f10_exponent == 0) {
         if (f10_data == 0) {
            // zero -> zero
            value = 0.f;
         } else {
            // subnormal -> normal
            U32 f10_mantissa = f10_data & f10_mantissa_mask;
            U32 zero_bits;
            std::tie(zero_bits, std::ignore) = bitscan_rev(f10_mantissa);
            zero_bits = f10_mantissa_bits - 1 - zero_bits;
            U32 f32_data = static_cast<U32>(f10_data) << (f32_mantissa_bits - f10_mantissa_bits + zero_bits + 1); // one extra bit because the highest 1 becomes the implicit normal mantissa MSB
            f32_data &= f32_mantissa_mask;
            U32 f32_exponent = (f32_exponent_basis - f10_exponent_basis - zero_bits) << f32_mantissa_bits;
            f32_data |= f32_exponent;
            memcpy(&value, &f32_data, sizeof(F32));
         }
      } else if (f10_exponent == f10_exponent_mask) {
         if (f10_data == f10_exponent_mask) {
            // inf -> inf
            constexpr U32 f32_data = f32_exponent_mask;
            memcpy(&value, &f32_data, sizeof(F32));
         } else {
            // any nan -> qnan
            constexpr U32 f32_data = f32_exponent_mask | (f32_mantissa_mask & ~0);
            memcpy(&value, &f32_data, sizeof(F32));
         }
      } else {
         // normal -> normal
         U32 f32_data = ((f10_exponent << shift) + ((f32_exponent_basis - f10_exponent_basis) << f32_mantissa_bits)) | ((f10_data & f10_mantissa_mask) << shift);
         memcpy(&value, &f32_data, sizeof(F32));
      }
      return value;
   }

   static T encode(F32 component) {
      U16 f10_data;
      U32 f32_data;
      memcpy(&f32_data, &component, sizeof(U32));

      U32 f32_exponent = f32_data & f32_exponent_mask;

      constexpr U32 min_normal_exponent = (U32(f32_exponent_basis - f10_exponent_basis + 1)) << f32_mantissa_bits;
      constexpr U32 max_exponent = (U32(f32_exponent_basis + f10_exponent_basis)) << f32_mantissa_bits;

      if (f32_exponent < min_normal_exponent) {
         // normal, subnormal, or zero -> subnormal or zero
         if (f32_exponent < min_normal_exponent - (f10_mantissa_bits << f32_mantissa_bits) || (f32_data & f32_sign_mask) != 0) {
            // negative, normal, subnormal, or zero -> zero
            f10_data = 0u;
         } else {
            // normal -> subnormal
            U32 mantissa = (1 << f32_mantissa_bits) | f32_data & f32_mantissa_mask; // add implicit MSB
            f10_data = static_cast<U16>(mantissa >> (shift + ((min_normal_exponent - f32_exponent) >> f32_mantissa_bits)));
         }
      } else if (f32_exponent > max_exponent) {
         // normal, inf or nan -> zero, inf or nan
         if (f32_exponent == f32_exponent_mask) {
            // inf or nan -> inf or nan
            if ((f32_data & f32_mantissa_mask) == 0) {
               // inf -> zero or inf
               if ((f32_data & f32_sign_mask) == 0) {
                  // inf -> inf
                  f10_data = f10_exponent_mask;
               } else {
                  // inf -> zero
                  f10_data = 0u;
               }
            } else {
               // nan -> nan
               f10_data = f10_exponent_mask | (f10_mantissa_mask & ~U16(0));
            }
         } else if ((f32_data & f32_sign_mask) == 0) {
            // positive normal -> inf
            f10_data = f10_exponent_mask;
         } else {
            // negative normal -> zero
            f10_data = 0u;
         }
      } else if ((f32_data & f32_sign_mask) != 0) {
         // negative normal -> zero
         f10_data = 0u;
      } else {
         // positive normal -> normal
         f10_data = static_cast<U16>(((f32_exponent - ((f32_exponent_basis - f10_exponent_basis) << f32_mantissa_bits)) | (f32_data & f32_mantissa_mask)) >> shift);
      }

      return static_cast<T>(f10_data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 64, ImageComponentType::sfloat> {
   static F32 decode(T data) {
      static_assert(sizeof(T) == 8);
      F64 float_data;
      memcpy(&float_data, &data, sizeof(F64));
      return static_cast<F32>(float_data);
   }
   static T encode(F32 component) {
      static_assert(sizeof(T) == 8);
      T data;
      F64 float_data = component;
      memcpy(&data, &float_data, sizeof(F64));
      return data;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 32, ImageComponentType::sfloat> {
   static F32 decode(T data) {
      static_assert(sizeof(T) == 4);
      F32 float_data;
      memcpy(&float_data, &data, sizeof(F32));
      return float_data;
   }
   static T encode(F32 component) {
      static_assert(sizeof(T) == 4);
      T data;
      memcpy(&data, &component, sizeof(F32));
      return data;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct image_component_rawnorm<T, 16, ImageComponentType::sfloat> {
   static constexpr int f16_mantissa_bits = 10;
   static constexpr int f16_exponent_bits = 5;
   static constexpr U16 f16_mantissa_mask = (1u << f16_mantissa_bits) - 1u;
   static constexpr U16 f16_exponent_mask = ((1u << (f16_exponent_bits + f16_mantissa_bits)) - 1u) ^ f16_mantissa_mask;
   static constexpr U16 f16_exponent_basis = (1u << (f16_exponent_bits - 1)) - 1u;
   static constexpr U16 f16_sign_mask = 1u << (f16_mantissa_bits + f16_exponent_bits);

   static constexpr int f32_mantissa_bits = 23;
   static constexpr int f32_exponent_bits = 8;
   static constexpr U32 f32_mantissa_mask = (1u << f32_mantissa_bits) - 1u;
   static constexpr U32 f32_exponent_mask = ((1u << (f32_exponent_bits + f32_mantissa_bits)) - 1u) ^ f32_mantissa_mask;
   static constexpr U16 f32_exponent_basis = (1u << (f32_exponent_bits - 1)) - 1u;
   static constexpr U32 f32_sign_mask = 1u << (f32_mantissa_bits + f32_exponent_bits);

   static constexpr int shift = f32_mantissa_bits - f16_mantissa_bits;
   static constexpr int sign_shift = f32_mantissa_bits + f32_exponent_bits - (f16_mantissa_bits + f16_exponent_bits);

   static F32 decode(T data) {
      F32 value;
      U16 f16_data = static_cast<U16>(data);
      U16 f16_sign = f16_data & f16_sign_mask;
      //f16_data ^= f16_sign; // clear sign from data;
      U32 f32_sign = f16_sign << sign_shift;

      U16 f16_exponent = f16_data & f16_exponent_mask;
      if (f16_exponent == 0) {
         if (f16_data == 0) {
            // zero -> zero
            U32 f32_data = f32_sign;
            memcpy(&value, &f32_data, sizeof(F32));
         } else {
            // subnormal -> normal
            U32 f16_mantissa = f16_data & f16_mantissa_mask;
            U32 zero_bits;
            std::tie(zero_bits, std::ignore) = bitscan_rev(f16_mantissa);
            zero_bits = f16_mantissa_bits - 1 - zero_bits;
            U32 f32_data = static_cast<U32>(f16_data) << (f32_mantissa_bits - f16_mantissa_bits + zero_bits + 1); // one extra bit because the highest 1 becomes the implicit normal mantissa MSB
            f32_data &= f32_mantissa_mask;
            U32 f32_exponent = (f32_exponent_basis - f16_exponent_basis - zero_bits) << f32_mantissa_bits;
            f32_data |= f32_exponent | f32_sign;
            memcpy(&value, &f32_data, sizeof(F32));
         }
      } else if (f16_exponent == f16_exponent_mask) {
         if (f16_data == f16_exponent_mask) {
            // inf -> inf
            U32 f32_data = f32_exponent_mask | f32_sign;
            memcpy(&value, &f32_data, sizeof(F32));
         } else {
            // any nan -> qnan
            U32 f32_data = f32_exponent_mask | (f32_mantissa_mask & ~0) | f32_sign;
            memcpy(&value, &f32_data, sizeof(F32));
         }
      } else {
         // normal -> normal
         U32 f32_data = f32_sign | ((f16_exponent << shift) + ((f32_exponent_basis - f16_exponent_basis) << f32_mantissa_bits)) | ((f16_data & f16_mantissa_mask) << shift);
         memcpy(&value, &f32_data, sizeof(F32));
      }
      return value;
   }

   static T encode(F32 component) {
      U16 f16_data;
      U32 f32_data;
      memcpy(&f32_data, &component, sizeof(U32));

      U32 f32_sign = f32_data & f32_sign_mask;
      U32 f32_exponent = f32_data & f32_exponent_mask;

      constexpr U32 min_normal_exponent = (U32(f32_exponent_basis - f16_exponent_basis + 1)) << f32_mantissa_bits;
      constexpr U32 max_exponent = (U32(f32_exponent_basis + f16_exponent_basis)) << f32_mantissa_bits;

      if (f32_exponent < min_normal_exponent) {
         // normal, subnormal, or zero -> subnormal or zero
         if (f32_exponent < min_normal_exponent - (f16_mantissa_bits << f32_mantissa_bits)) {
            // normal, subnormal, or zero -> zero
            f16_data = 0u;
         } else {
            // normal -> subnormal
            U32 mantissa = (1 << f32_mantissa_bits) | (f32_data & f32_mantissa_mask); // add implicit MSB
            f16_data = static_cast<U16>(mantissa >> (shift + ((min_normal_exponent - f32_exponent) >> f32_mantissa_bits)));
         }
      } else if (f32_exponent > max_exponent) {
         // normal, inf or nan -> zero, inf or nan
         if (f32_exponent == f32_exponent_mask) {
            // inf or nan -> inf or nan
            if ((f32_data & f32_mantissa_mask) == 0) {
               // inf -> inf
               f16_data = f16_exponent_mask;
            } else {
               // nan -> nan
               f16_data = f16_exponent_mask | (f16_mantissa_mask & ~U16(0));
            }
         } else {
            // normal -> inf
            f16_data = f16_exponent_mask;
         }
      } else {
         // normal -> normal
         f16_data = static_cast<U16>(((f32_exponent - ((f32_exponent_basis - f16_exponent_basis) << f32_mantissa_bits)) | (f32_data & f32_mantissa_mask)) >> shift);
      }

      f16_data |= f32_sign >> sign_shift;
      return static_cast<T>(f16_data);
   }
};

#pragma endregion

///////////////////////////////////////////////////////////////////////////////
template <typename UnsignedType, std::size_t Bits>
F32 decode_image_component(UnsignedType data, ImageComponentType type) {
   switch (type) {
      case ImageComponentType::expo:
      case ImageComponentType::uint:   return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::uint>::decode(data);
      case ImageComponentType::sint:   return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::sint>::decode(data);
      case ImageComponentType::unorm:  return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::unorm>::decode(data);
      case ImageComponentType::snorm:  return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::snorm>::decode(data);
      case ImageComponentType::ufloat: return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::ufloat>::decode(data);
      case ImageComponentType::sfloat: return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::sfloat>::decode(data);
      default:                         return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::none>::decode(data);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename UnsignedType, std::size_t Bits>
UnsignedType encode_image_component(F32 component, ImageComponentType type) {
   switch (type) {
      case ImageComponentType::expo:
      case ImageComponentType::uint:   return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::uint>::encode(component);
      case ImageComponentType::sint:   return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::sint>::encode(component);
      case ImageComponentType::unorm:  return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::unorm>::encode(component);
      case ImageComponentType::snorm:  return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::snorm>::encode(component);
      case ImageComponentType::ufloat: return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::ufloat>::encode(component);
      case ImageComponentType::sfloat: return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::sfloat>::encode(component);
      default:                         return image_component_rawnorm<UnsignedType, Bits, ImageComponentType::none>::encode(component);
   }
}

#pragma region image_pixel_access_uncompressed_rawnorm_nonpacked

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType>
struct image_pixel_access_uncompressed_rawnorm_nonpacked {
   static constexpr glm::length_t components = ImageBlockPackingInfo<Packing>::components;
   static constexpr std::size_t word_size_bits = ImageBlockPackingInfo<Packing>::word_size * 8;

   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename ImageBlockPackingInfo<Packing>::unsigned_word_type;
   using data_type = glm::vec<components, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      for (glm::length_t c = 0; c < components; ++c) {
         pixel[c] = image_component_rawnorm<word_type, word_size_bits, ComponentType>::decode(data[c]);
      }
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      for (glm::length_t c = 0; c < components; ++c) {
         data[c] = image_component_rawnorm<word_type, word_size_bits, ComponentType>::encode(pixel[c]);
      }
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing>
struct image_pixel_access_uncompressed_rawnorm_nonpacked<ImageView, Dimension, IsSimple, Packing, ImageComponentType::none> {
   static constexpr glm::length_t components = ImageBlockPackingInfo<Packing>::components;
   static constexpr std::size_t word_size_bits = ImageBlockPackingInfo<Packing>::word_size * 8;

   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename ImageBlockPackingInfo<Packing>::unsigned_word_type;
   using data_type = glm::vec<components, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      const auto component_types = image.format().component_types();
      for (glm::length_t c = 0; c < components; ++c) {
         pixel[c] = decode_image_component<word_type, word_size_bits>(data[c], static_cast<ImageComponentType>(component_types[c]));
      }
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      for (glm::length_t c = 0; c < components; ++c) {
         data[c] = encode_image_component<word_type, word_size_bits>(pixel[c], static_cast<ImageComponentType>(component_types[c]));
      }
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

#pragma endregion
#pragma region image_pixel_access_uncompressed_rawnorm_packed

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType, U8 Components = ImageBlockPackingInfo<Packing>::components>
struct image_pixel_access_uncompressed_rawnorm_packed { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ComponentType, 1> {
   using packing_info = ImageBlockPackingInfo<Packing>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      pixel[0] = image_component_rawnorm<word_type, packing_info::component_bit_width[0], ComponentType>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::component_word_offset[0]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[0], ComponentType>::encode(pixel[0]) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ImageComponentType::none, 1> {
   using packing_info = ImageBlockPackingInfo<Packing>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      const auto component_types = image.format().component_types();
      pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ImageComponentType>(component_types[0]));
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ImageComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ComponentType, 2> {
   using packing_info = ImageBlockPackingInfo<Packing>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      pixel[0] = image_component_rawnorm<word_type, packing_info::component_bit_width[0], ComponentType>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
      pixel[1] = image_component_rawnorm<word_type, packing_info::component_bit_width[1], ComponentType>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::component_word_offset[0]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[0], ComponentType>::encode(pixel[0]) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[1], ComponentType>::encode(pixel[1]) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ImageComponentType::none, 2> {
   using packing_info = ImageBlockPackingInfo<Packing>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      const auto component_types = image.format().component_types();
      pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ImageComponentType>(component_types[0]));
      pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ImageComponentType>(component_types[1]));
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ImageComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ImageComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ComponentType, 3> {
   using packing_info = ImageBlockPackingInfo<Packing>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      pixel[0] = image_component_rawnorm<word_type, packing_info::component_bit_width[0], ComponentType>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
      pixel[1] = image_component_rawnorm<word_type, packing_info::component_bit_width[1], ComponentType>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
      pixel[2] = image_component_rawnorm<word_type, packing_info::component_bit_width[2], ComponentType>::decode((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1));
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::component_word_offset[0]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[0], ComponentType>::encode(pixel[0]) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[1], ComponentType>::encode(pixel[1]) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      data[packing_info::component_word_offset[2]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[2], ComponentType>::encode(pixel[2]) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ImageComponentType::none, 3> {
   using packing_info = ImageBlockPackingInfo<Packing>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      const auto component_types = image.format().component_types();
      pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ImageComponentType>(component_types[0]));
      pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ImageComponentType>(component_types[1]));
      pixel[2] = decode_image_component<word_type, packing_info::component_bit_width[2]>((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1), static_cast<ImageComponentType>(component_types[2]));
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ImageComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ImageComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      data[packing_info::component_word_offset[2]] |= (encode_image_component<word_type, packing_info::component_bit_width[2]>(pixel[2], static_cast<ImageComponentType>(component_types[2])) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ComponentType, 4> {
   using packing_info = ImageBlockPackingInfo<Packing>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      pixel[0] = image_component_rawnorm<word_type, packing_info::component_bit_width[0], ComponentType>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
      pixel[1] = image_component_rawnorm<word_type, packing_info::component_bit_width[1], ComponentType>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
      pixel[2] = image_component_rawnorm<word_type, packing_info::component_bit_width[2], ComponentType>::decode((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1));
      pixel[3] = image_component_rawnorm<word_type, packing_info::component_bit_width[3], ComponentType>::decode((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1));
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::component_word_offset[0]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[0], ComponentType>::encode(pixel[0]) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[1], ComponentType>::encode(pixel[1]) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      data[packing_info::component_word_offset[2]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[2], ComponentType>::encode(pixel[2]) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
      data[packing_info::component_word_offset[3]] |= (image_component_rawnorm<word_type, packing_info::component_bit_width[3], ComponentType>::encode(pixel[3]) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ImageComponentType::none, 4> {
   using packing_info = ImageBlockPackingInfo<Packing>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      const auto component_types = image.format().component_types();
      pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ImageComponentType>(component_types[0]));
      pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ImageComponentType>(component_types[1]));
      pixel[2] = decode_image_component<word_type, packing_info::component_bit_width[2]>((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1), static_cast<ImageComponentType>(component_types[2]));
      pixel[3] = decode_image_component<word_type, packing_info::component_bit_width[3]>((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1), static_cast<ImageComponentType>(component_types[3]));
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ImageComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ImageComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      data[packing_info::component_word_offset[2]] |= (encode_image_component<word_type, packing_info::component_bit_width[2]>(pixel[2], static_cast<ImageComponentType>(component_types[2])) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
      data[packing_info::component_word_offset[3]] |= (encode_image_component<word_type, packing_info::component_bit_width[3]>(pixel[3], static_cast<ImageComponentType>(component_types[3])) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, ImageBlockPacking::p_9_9_9_5, ImageComponentType::none, 4> {
   using packing_info = ImageBlockPackingInfo<ImageBlockPacking::p_9_9_9_5>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static constexpr int f14_mantissa_bits = 9;
   static constexpr int f14_exponent_bits = 5;
   static constexpr U16 f14_mantissa_mask = (1u << f14_mantissa_bits) - 1u;
   static constexpr int f14_exponent_basis = (1 << (f14_exponent_bits - 1)) - 1;
   static constexpr int f14_exponent_max = (1 << f14_exponent_bits) - 1;

   static constexpr int f32_mantissa_bits = 23;
   static constexpr int f32_exponent_bits = 8;
   static constexpr U16 f32_exponent_basis = (1u << (f32_exponent_bits - 1)) - 1u;

   // not accurate for negative, nan, inf, or subnormal values
   // but not important for our use case
   static int floor_log2(F32 value) {
      U32 data;
      memcpy(&data, &value, sizeof(F32));
      return (data >> f32_mantissa_bits) - f32_exponent_basis;
   }

   static F32 pow2(int exponent) {
      F32 value;
      exponent += f32_exponent_basis;
      assert(exponent > 0);
      assert(exponent < (1u << f32_exponent_bits) - 1);
      U32 data = exponent << f32_mantissa_bits;
      memcpy(&value, &data, sizeof(F32));
      return value;
   }

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      const auto component_types = image.format().component_types();
      constexpr U8 ufloat = static_cast<U8>(ImageComponentType::ufloat);
      constexpr U8 expo = static_cast<U8>(ImageComponentType::expo);
      if (component_types == ImageFormat::component_types_type(ufloat, ufloat, ufloat, expo)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         vec3 pixel3;
         pixel3[0] = image_component_rawnorm<word_type, packing_info::component_bit_width[0], ImageComponentType::uint>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
         pixel3[1] = image_component_rawnorm<word_type, packing_info::component_bit_width[1], ImageComponentType::uint>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
         pixel3[2] = image_component_rawnorm<word_type, packing_info::component_bit_width[2], ImageComponentType::uint>::decode((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1));

         word_type exponent = (data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1);
         pixel3 *= pow2(exponent - f14_exponent_basis - f14_mantissa_bits);
         pixel = vec4(pixel3, 0.f);
      } else {
         pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ImageComponentType>(component_types[0]));
         pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ImageComponentType>(component_types[1]));
         pixel[2] = decode_image_component<word_type, packing_info::component_bit_width[2]>((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1), static_cast<ImageComponentType>(component_types[2]));
         pixel[3] = decode_image_component<word_type, packing_info::component_bit_width[3]>((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1), static_cast<ImageComponentType>(component_types[3]));
      }
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      constexpr U8 ufloat = static_cast<U8>(ImageComponentType::ufloat);
      constexpr U8 expo = static_cast<U8>(ImageComponentType::expo);
      if (component_types == ImageFormat::component_types_type(ufloat, ufloat, ufloat, expo)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         constexpr F32 limit = (F32)f14_mantissa_mask * (1 << (f14_exponent_max - f14_exponent_basis - f14_mantissa_bits));
         vec3 color = glm::clamp(vec3(pixel), 0.f, limit); // nan -> 0, inf -> limit
         const F32 max_value = std::max(std::max(color.r, color.g), color.b);
         int exp_shared = std::max(-f14_exponent_basis - 1, floor_log2(max_value)) + 1 + f14_exponent_basis;
         assert(exp_shared >= 0);
         assert(exp_shared <= f14_exponent_max);
         F32 mult = pow2(f14_mantissa_bits + f14_exponent_basis - exp_shared);

         int max_multiplied = (int)(max_value * mult + 0.5f);
         if (max_multiplied == (1 << f14_mantissa_bits)) {
            mult *= 0.5f;
            exp_shared += 1;
            assert(exp_shared <= f14_exponent_max);
         } else {
            assert(max_multiplied <= f14_mantissa_mask);
         }
         
         uvec3 components(color * mult + 0.5f);

         assert(components[0] >= 0);
         assert(components[1] >= 0);
         assert(components[2] >= 0);
         assert(components[0] <= f14_mantissa_mask);
         assert(components[1] <= f14_mantissa_mask);
         assert(components[2] <= f14_mantissa_mask);

         data[packing_info::component_word_offset[0]] |= (components[0] & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
         data[packing_info::component_word_offset[1]] |= (components[1] & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
         data[packing_info::component_word_offset[2]] |= (components[2] & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
         data[packing_info::component_word_offset[3]] |= (static_cast<unsigned int>(exp_shared) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      } else {
         data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ImageComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
         data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ImageComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
         data[packing_info::component_word_offset[2]] |= (encode_image_component<word_type, packing_info::component_bit_width[2]>(pixel[2], static_cast<ImageComponentType>(component_types[2])) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
         data[packing_info::component_word_offset[3]] |= (encode_image_component<word_type, packing_info::component_bit_width[3]>(pixel[3], static_cast<ImageComponentType>(component_types[3])) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      }
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple>
struct image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, ImageBlockPacking::p_5_9_9_9, ImageComponentType::none, 4> {
   using packing_info = ImageBlockPackingInfo<ImageBlockPacking::p_5_9_9_9>;
   using coord_type = typename image_coord_type<Dimension>::type;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static constexpr int f14_mantissa_bits = 9;
   static constexpr int f14_exponent_bits = 5;
   static constexpr U16 f14_mantissa_mask = (1u << f14_mantissa_bits) - 1u;
   static constexpr int f14_exponent_basis = (1 << (f14_exponent_bits - 1)) - 1;
   static constexpr int f14_exponent_max = (1 << f14_exponent_bits) - 1;

   static constexpr int f32_mantissa_bits = 23;
   static constexpr int f32_exponent_bits = 8;
   static constexpr U16 f32_exponent_basis = (1u << (f32_exponent_bits - 1)) - 1u;

   // not accurate for negative, nan, inf, or subnormal values
   // but not important for our use case
   static int floor_log2(F32 value) {
      U32 data;
      memcpy(&data, &value, sizeof(F32));
      return (data >> f32_mantissa_bits) - f32_exponent_basis;
   }

   static F32 pow2(int exponent) {
      F32 value;
      exponent += f32_exponent_basis;
      assert(exponent > 0);
      assert(exponent < (1u << f32_exponent_bits) - 1);
      U32 data = exponent << f32_mantissa_bits;
      memcpy(&value, &data, sizeof(F32));
      return value;
   }

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      vec4 pixel;
      data_type data = image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::get(image, pixel_coord);
      const auto component_types = image.format().component_types();
      constexpr U8 ufloat = static_cast<U8>(ImageComponentType::ufloat);
      constexpr U8 expo = static_cast<U8>(ImageComponentType::expo);
      if (component_types == ImageFormat::component_types_type(expo, ufloat, ufloat, ufloat)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         vec3 pixel3;
         pixel3[0] = image_component_rawnorm<word_type, packing_info::component_bit_width[1], ImageComponentType::uint>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
         pixel3[1] = image_component_rawnorm<word_type, packing_info::component_bit_width[2], ImageComponentType::uint>::decode((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1));
         pixel3[2] = image_component_rawnorm<word_type, packing_info::component_bit_width[3], ImageComponentType::uint>::decode((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1));

         word_type exponent = (data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1);
         pixel3 *= pow2(exponent - f14_exponent_basis - f14_mantissa_bits);
         pixel = vec4(0.f, pixel3);
      } else {
         pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ImageComponentType>(component_types[0]));
         pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ImageComponentType>(component_types[1]));
         pixel[2] = decode_image_component<word_type, packing_info::component_bit_width[2]>((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1), static_cast<ImageComponentType>(component_types[2]));
         pixel[3] = decode_image_component<word_type, packing_info::component_bit_width[3]>((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1), static_cast<ImageComponentType>(component_types[3]));
      }
      return pixel;
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      constexpr U8 ufloat = static_cast<U8>(ImageComponentType::ufloat);
      constexpr U8 expo = static_cast<U8>(ImageComponentType::expo);
      if (component_types == ImageFormat::component_types_type(expo, ufloat, ufloat, ufloat)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         constexpr F32 limit = (F32)f14_mantissa_mask * (1 << (f14_exponent_max - f14_exponent_basis - f14_mantissa_bits));
         vec3 color = glm::clamp(vec3(pixel), 0.f, limit); // nan -> 0, inf -> limit
         const F32 max_value = std::max(std::max(color.r, color.g), color.b);
         int exp_shared = std::max(-f14_exponent_basis - 1, floor_log2(max_value)) + 1 + f14_exponent_basis;
         assert(exp_shared >= 0);
         assert(exp_shared <= f14_exponent_max);
         F32 mult = pow2(f14_mantissa_bits + f14_exponent_basis - exp_shared);

         int max_multiplied = (int)(max_value * mult + 0.5f);
         if (max_multiplied == (1 << f14_mantissa_bits)) {
            mult *= 0.5f;
            exp_shared += 1;
            assert(exp_shared <= f14_exponent_max);
         } else {
            assert(max_multiplied <= f14_mantissa_mask);
         }

         uvec3 components(color * mult + 0.5f);

         assert(components[0] >= 0);
         assert(components[1] >= 0);
         assert(components[2] >= 0);
         assert(components[0] <= f14_mantissa_mask);
         assert(components[1] <= f14_mantissa_mask);
         assert(components[2] <= f14_mantissa_mask);

         data[packing_info::component_word_offset[0]] |= (static_cast<unsigned int>(exp_shared) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
         data[packing_info::component_word_offset[1]] |= (components[1] & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
         data[packing_info::component_word_offset[2]] |= (components[2] & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
         data[packing_info::component_word_offset[3]] |= (components[3] & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      } else {
         data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ImageComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
         data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ImageComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
         data[packing_info::component_word_offset[2]] |= (encode_image_component<word_type, packing_info::component_bit_width[2]>(pixel[2], static_cast<ImageComponentType>(component_types[2])) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
         data[packing_info::component_word_offset[3]] |= (encode_image_component<word_type, packing_info::component_bit_width[3]>(pixel[3], static_cast<ImageComponentType>(component_types[3])) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      }
      image_pixel_access_uncompressed<data_type, ImageView, Dimension, IsSimple>::put(image, pixel_coord, data);
   }
};

#pragma endregion
#pragma region image_pixel_access_uncompressed_rawnorm

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType, bool IsPacked = ImageBlockPackingInfo<Packing>::is_packed::value>
struct image_pixel_access_uncompressed_rawnorm { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType>
struct image_pixel_access_uncompressed_rawnorm<ImageView, Dimension, IsSimple, Packing, ComponentType, false>
   : image_pixel_access_uncompressed_rawnorm_nonpacked<ImageView, Dimension, IsSimple, Packing, ComponentType> { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType>
struct image_pixel_access_uncompressed_rawnorm<ImageView, Dimension, IsSimple, Packing, ComponentType, true>
   : image_pixel_access_uncompressed_rawnorm_packed<ImageView, Dimension, IsSimple, Packing, ComponentType> { };

#pragma endregion
#pragma region image_pixel_access_uncompressed_norm

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, U8 Dimension, bool IsSimple, ImageBlockPacking Packing, ImageComponentType ComponentType = ImageComponentType::none>
struct image_pixel_access_uncompressed_norm {
   using coord_type = typename image_coord_type<Dimension>::type;

   static vec4 get(const ImageView& image, coord_type pixel_coord) {
      F32 data[6] = { 0.f, 1.f };
      const vec4 raw = image_pixel_access_uncompressed_rawnorm<ImageView, Dimension, IsSimple, Packing, ComponentType>::get(image, pixel_coord);
      memcpy(data + 2, glm::value_ptr(raw), sizeof(vec4));
      const auto swizzles = image.format().swizzles();
      return vec4(data[swizzles.r], data[swizzles.g], data[swizzles.b], data[swizzles.a]);
   }

   static void put(ImageView& image, coord_type pixel_coord, vec4 pixel) {
      vec4 unswizzled_pixel;
      const auto swizzles = image.format().swizzles();
      for (glm::length_t c = 3; c >= 0; --c) {
         U8 swizzle = swizzles[c];
         if (swizzle >= 2) {
            unswizzled_pixel[swizzle - 2] = pixel[c];
         }
      }
      image_pixel_access_uncompressed_rawnorm<ImageView, Dimension, IsSimple, Packing, ComponentType>::put(image, pixel_coord, unswizzled_pixel);
   }
};

#pragma endregion

} // be::gfx::detail

/*!! include('image_block_packing', true)
register_template_string([[
` i = i
max_length = image_block_packing.max_constant_name_length
`
///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
GetImagePixelNorm`dim_text`Func<ImageView> get_pixel_norm_`string.lower(dim_text)`_func(const ImageView& image) {
   using dim_type = glm::vec<`i`, ImageFormat::block_size_type>;
   assert(image);
   if (is_compressed(image.format().packing())) {
      switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp == 0 {`
         case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      ` // TODO`
   }
}
`
         default:
            assert(false);
            break;
      }
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ImageComponentType component_type = static_cast<ImageComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ImageComponentType>(component_types[c]) != component_type) {
            component_type = ImageComponentType::none;
            break;
         }
      }

      if (component_type == ImageComponentType::unorm) {
         switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 {`
            case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, true, ImageBlockPacking::`name`, ImageComponentType::unorm>::get;`
   }
}
`
         }
      } else if (component_type == ImageComponentType::uint) {
         switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 {`
            case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, true, ImageBlockPacking::`name`, ImageComponentType::uint>::get;`
   }
}
`
         }
      } else if (component_type == ImageComponentType::sfloat) {
         switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 and n_comp == n_words {`
            case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, true, ImageBlockPacking::`name`, ImageComponentType::sfloat>::get;`
   }
}
`
         }
      }
      switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 {`
         case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, true, ImageBlockPacking::`name`>::get;`
   }
}
`
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 {`
         case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, false, ImageBlockPacking::`name`>::get;`
   }
}
`
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}
]], 'get_pixel')

register_template_string([[
` i = i
max_length = image_block_packing.max_constant_name_length
`
///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
PutImagePixelNorm`dim_text`Func<ImageView> put_pixel_norm_`string.lower(dim_text)`_func(const ImageView& image) {
   using dim_type = glm::vec<`i`, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));   
   if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ImageComponentType component_type = static_cast<ImageComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ImageComponentType>(component_types[c]) != component_type) {
            component_type = ImageComponentType::none;
            break;
         }
      }

      if (component_type == ImageComponentType::unorm) {
         switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 {`
            case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, true, ImageBlockPacking::`name`, ImageComponentType::unorm>::put;`
   }
}
`
         }
      } else if (component_type == ImageComponentType::uint) {
         switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 {`
            case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, true, ImageBlockPacking::`name`, ImageComponentType::uint>::put;`
   }
}
`
         }
      } else if (component_type == ImageComponentType::sfloat) {
         switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 and n_comp == n_words {`
            case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, true, ImageBlockPacking::`name`, ImageComponentType::sfloat>::put;`
   }
}
`
         }
      }
      switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 {`
         case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, true, ImageBlockPacking::`name`>::put;`
   }
}
`
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {`
with each image_block_packing.constants using # {
   if n_comp ~= 0 {`
         case ImageBlockPacking::`name`:`
      string.rep(' ', max_length + 1 - #name)
      `return detail::image_pixel_access_uncompressed_norm<ImageView, `i`, false, ImageBlockPacking::`name`>::put;`
   }
}
`
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}
]], 'put_pixel')

write_template('get_pixel', { i = 1, dim_text = 'Lineal' })
write_template('get_pixel', { i = 2, dim_text = 'Planar' })
write_template('get_pixel', { i = 3, dim_text = 'Volumetric' })

write_template('put_pixel', { i = 1, dim_text = 'Lineal' })
write_template('put_pixel', { i = 2, dim_text = 'Planar' })
write_template('put_pixel', { i = 3, dim_text = 'Volumetric' })
!! 1246 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
GetImagePixelNormLinealFunc<ImageView> get_pixel_norm_lineal_func(const ImageView& image) {
   using dim_type = glm::vec<1, ImageFormat::block_size_type>;
   assert(image);
   if (is_compressed(image.format().packing())) {
      switch (image.format().packing()) {
         case ImageBlockPacking::c_astc:         // TODO
         case ImageBlockPacking::c_atc:          // TODO
         case ImageBlockPacking::c_bptc:         // TODO
         case ImageBlockPacking::c_eac:          // TODO
         case ImageBlockPacking::c_etc1:         // TODO
         case ImageBlockPacking::c_etc2:         // TODO
         case ImageBlockPacking::c_pvrtc1:       // TODO
         case ImageBlockPacking::c_pvrtc2:       // TODO
         case ImageBlockPacking::c_s3tc1:        // TODO
         case ImageBlockPacking::c_s3tc2:        // TODO
         case ImageBlockPacking::c_s3tc3:        // TODO
         case ImageBlockPacking::c_s3tc4:        // TODO
         case ImageBlockPacking::c_s3tc5:        // TODO
         default:
            assert(false);
            break;
      }
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ImageComponentType component_type = static_cast<ImageComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ImageComponentType>(component_types[c]) != component_type) {
            component_type = ImageComponentType::none;
            break;
         }
      }

      if (component_type == ImageComponentType::unorm) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_3_2, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_3_3, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_2_3, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_6_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_24, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_24_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_11_10, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_11_11, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_10_11, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::unorm>::get;
         }
      } else if (component_type == ImageComponentType::uint) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_3_2, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_3_3, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_2_3, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_6_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_24, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_24_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_11_10, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_11_11, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_10_11, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::uint>::get;
         }
      } else if (component_type == ImageComponentType::sfloat) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::sfloat>::get;
         }
      }
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8>::get;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8>::get;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8>::get;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8_8>::get;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16>::get;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16>::get;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16>::get;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16_16>::get;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32>::get;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32>::get;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32>::get;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32_32>::get;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64>::get;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64>::get;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64>::get;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64_64>::get;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4>::get;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_3_2>::get;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_3_3>::get;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_2_3>::get;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4_4_4>::get;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_1_5_5_5>::get;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_5_5_1>::get;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_6_5>::get;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_24>::get;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_24_8>::get;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_11_10>::get;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_11_11>::get;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_10_11>::get;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_8_8_8>::get;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_9_9_9_5>::get;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_9_9_9>::get;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_10_10_2>::get;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_10_10_10>::get;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_p_24_8>::get;
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_8>::get;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_8_8>::get;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_8_8_8>::get;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_8_8_8_8>::get;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_16>::get;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_16_16>::get;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_16_16_16>::get;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_16_16_16_16>::get;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32>::get;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32_32>::get;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32_32_32>::get;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32_32_32_32>::get;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_64>::get;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_64_64>::get;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_64_64_64>::get;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_64_64_64_64>::get;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_4_4>::get;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_3_3_2>::get;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_2_3_3>::get;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_3_2_3>::get;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_4_4_4_4>::get;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_1_5_5_5>::get;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_5_5_5_1>::get;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_5_6_5>::get;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_8_24>::get;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_24_8>::get;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_11_11_10>::get;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_10_11_11>::get;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_11_10_11>::get;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_8_8_8_8>::get;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_9_9_9_5>::get;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_5_9_9_9>::get;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_10_10_10_2>::get;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_2_10_10_10>::get;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32_p_24_8>::get;
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
GetImagePixelNormPlanarFunc<ImageView> get_pixel_norm_planar_func(const ImageView& image) {
   using dim_type = glm::vec<2, ImageFormat::block_size_type>;
   assert(image);
   if (is_compressed(image.format().packing())) {
      switch (image.format().packing()) {
         case ImageBlockPacking::c_astc:         // TODO
         case ImageBlockPacking::c_atc:          // TODO
         case ImageBlockPacking::c_bptc:         // TODO
         case ImageBlockPacking::c_eac:          // TODO
         case ImageBlockPacking::c_etc1:         // TODO
         case ImageBlockPacking::c_etc2:         // TODO
         case ImageBlockPacking::c_pvrtc1:       // TODO
         case ImageBlockPacking::c_pvrtc2:       // TODO
         case ImageBlockPacking::c_s3tc1:        // TODO
         case ImageBlockPacking::c_s3tc2:        // TODO
         case ImageBlockPacking::c_s3tc3:        // TODO
         case ImageBlockPacking::c_s3tc4:        // TODO
         case ImageBlockPacking::c_s3tc5:        // TODO
         default:
            assert(false);
            break;
      }
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ImageComponentType component_type = static_cast<ImageComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ImageComponentType>(component_types[c]) != component_type) {
            component_type = ImageComponentType::none;
            break;
         }
      }

      if (component_type == ImageComponentType::unorm) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_3_2, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_3_3, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_2_3, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_6_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_24, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_24_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_11_10, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_11_11, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_10_11, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::unorm>::get;
         }
      } else if (component_type == ImageComponentType::uint) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_3_2, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_3_3, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_2_3, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_6_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_24, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_24_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_11_10, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_11_11, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_10_11, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::uint>::get;
         }
      } else if (component_type == ImageComponentType::sfloat) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::sfloat>::get;
         }
      }
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8>::get;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8>::get;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8>::get;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8_8>::get;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16>::get;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16>::get;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16>::get;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16_16>::get;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32>::get;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32>::get;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32>::get;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32_32>::get;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64>::get;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64>::get;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64>::get;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64_64>::get;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4>::get;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_3_2>::get;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_3_3>::get;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_2_3>::get;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4_4_4>::get;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_1_5_5_5>::get;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_5_5_1>::get;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_6_5>::get;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_24>::get;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_24_8>::get;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_11_10>::get;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_11_11>::get;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_10_11>::get;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_8_8_8>::get;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_9_9_9_5>::get;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_9_9_9>::get;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_10_10_2>::get;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_10_10_10>::get;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_p_24_8>::get;
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_8>::get;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_8_8>::get;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_8_8_8>::get;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_8_8_8_8>::get;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_16>::get;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_16_16>::get;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_16_16_16>::get;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_16_16_16_16>::get;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32>::get;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32_32>::get;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32_32_32>::get;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32_32_32_32>::get;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_64>::get;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_64_64>::get;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_64_64_64>::get;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_64_64_64_64>::get;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_4_4>::get;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_3_3_2>::get;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_2_3_3>::get;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_3_2_3>::get;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_4_4_4_4>::get;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_1_5_5_5>::get;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_5_5_5_1>::get;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_5_6_5>::get;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_8_24>::get;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_24_8>::get;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_11_11_10>::get;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_10_11_11>::get;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_11_10_11>::get;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_8_8_8_8>::get;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_9_9_9_5>::get;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_5_9_9_9>::get;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_10_10_10_2>::get;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_2_10_10_10>::get;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32_p_24_8>::get;
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
GetImagePixelNormVolumetricFunc<ImageView> get_pixel_norm_volumetric_func(const ImageView& image) {
   using dim_type = glm::vec<3, ImageFormat::block_size_type>;
   assert(image);
   if (is_compressed(image.format().packing())) {
      switch (image.format().packing()) {
         case ImageBlockPacking::c_astc:         // TODO
         case ImageBlockPacking::c_atc:          // TODO
         case ImageBlockPacking::c_bptc:         // TODO
         case ImageBlockPacking::c_eac:          // TODO
         case ImageBlockPacking::c_etc1:         // TODO
         case ImageBlockPacking::c_etc2:         // TODO
         case ImageBlockPacking::c_pvrtc1:       // TODO
         case ImageBlockPacking::c_pvrtc2:       // TODO
         case ImageBlockPacking::c_s3tc1:        // TODO
         case ImageBlockPacking::c_s3tc2:        // TODO
         case ImageBlockPacking::c_s3tc3:        // TODO
         case ImageBlockPacking::c_s3tc4:        // TODO
         case ImageBlockPacking::c_s3tc5:        // TODO
         default:
            assert(false);
            break;
      }
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ImageComponentType component_type = static_cast<ImageComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ImageComponentType>(component_types[c]) != component_type) {
            component_type = ImageComponentType::none;
            break;
         }
      }

      if (component_type == ImageComponentType::unorm) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_3_2, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_3_3, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_2_3, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_6_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_24, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_24_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_11_10, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_11_11, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_10_11, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::unorm>::get;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::unorm>::get;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::unorm>::get;
         }
      } else if (component_type == ImageComponentType::uint) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_3_2, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_3_3, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_2_3, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_6_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_24, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_24_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_11_10, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_11_11, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_10_11, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::uint>::get;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::uint>::get;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::uint>::get;
         }
      } else if (component_type == ImageComponentType::sfloat) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64, ImageComponentType::sfloat>::get;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::sfloat>::get;
         }
      }
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8>::get;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8>::get;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8>::get;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8_8>::get;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16>::get;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16>::get;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16>::get;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16_16>::get;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32>::get;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32>::get;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32>::get;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32_32>::get;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64>::get;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64>::get;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64>::get;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64_64>::get;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4>::get;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_3_2>::get;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_3_3>::get;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_2_3>::get;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4_4_4>::get;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_1_5_5_5>::get;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_5_5_1>::get;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_6_5>::get;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_24>::get;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_24_8>::get;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_11_10>::get;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_11_11>::get;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_10_11>::get;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_8_8_8>::get;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_9_9_9_5>::get;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_9_9_9>::get;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_10_10_2>::get;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_10_10_10>::get;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_p_24_8>::get;
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_8>::get;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_8_8>::get;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_8_8_8>::get;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_8_8_8_8>::get;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_16>::get;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_16_16>::get;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_16_16_16>::get;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_16_16_16_16>::get;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32>::get;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32_32>::get;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32_32_32>::get;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32_32_32_32>::get;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_64>::get;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_64_64>::get;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_64_64_64>::get;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_64_64_64_64>::get;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_4_4>::get;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_3_3_2>::get;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_2_3_3>::get;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_3_2_3>::get;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_4_4_4_4>::get;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_1_5_5_5>::get;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_5_5_5_1>::get;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_5_6_5>::get;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_8_24>::get;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_24_8>::get;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_11_11_10>::get;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_10_11_11>::get;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_11_10_11>::get;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_8_8_8_8>::get;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_9_9_9_5>::get;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_5_9_9_9>::get;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_10_10_10_2>::get;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_2_10_10_10>::get;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32_p_24_8>::get;
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
PutImagePixelNormLinealFunc<ImageView> put_pixel_norm_lineal_func(const ImageView& image) {
   using dim_type = glm::vec<1, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));   
   if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ImageComponentType component_type = static_cast<ImageComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ImageComponentType>(component_types[c]) != component_type) {
            component_type = ImageComponentType::none;
            break;
         }
      }

      if (component_type == ImageComponentType::unorm) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_3_2, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_3_3, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_2_3, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_6_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_24, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_24_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_11_10, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_11_11, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_10_11, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::unorm>::put;
         }
      } else if (component_type == ImageComponentType::uint) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_3_2, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_3_3, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_2_3, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_6_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_24, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_24_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_11_10, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_11_11, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_10_11, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::uint>::put;
         }
      } else if (component_type == ImageComponentType::sfloat) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::sfloat>::put;
         }
      }
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8>::put;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8>::put;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8>::put;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_8_8_8_8>::put;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16>::put;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16>::put;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16>::put;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_16_16_16_16>::put;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32>::put;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32>::put;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32>::put;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_32_32_32>::put;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64>::put;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64>::put;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64>::put;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_64_64_64_64>::put;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4>::put;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_3_2>::put;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_3_3>::put;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_3_2_3>::put;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_4_4_4_4>::put;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_1_5_5_5>::put;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_5_5_1>::put;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_6_5>::put;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_24>::put;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_24_8>::put;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_11_10>::put;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_11_11>::put;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_11_10_11>::put;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_8_8_8_8>::put;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_9_9_9_5>::put;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_5_9_9_9>::put;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_10_10_10_2>::put;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::p_2_10_10_10>::put;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 1, true, ImageBlockPacking::s_32_p_24_8>::put;
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_8>::put;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_8_8>::put;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_8_8_8>::put;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_8_8_8_8>::put;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_16>::put;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_16_16>::put;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_16_16_16>::put;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_16_16_16_16>::put;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32>::put;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32_32>::put;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32_32_32>::put;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32_32_32_32>::put;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_64>::put;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_64_64>::put;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_64_64_64>::put;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_64_64_64_64>::put;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_4_4>::put;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_3_3_2>::put;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_2_3_3>::put;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_3_2_3>::put;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_4_4_4_4>::put;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_1_5_5_5>::put;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_5_5_5_1>::put;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_5_6_5>::put;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_8_24>::put;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_24_8>::put;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_11_11_10>::put;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_10_11_11>::put;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_11_10_11>::put;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_8_8_8_8>::put;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_9_9_9_5>::put;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_5_9_9_9>::put;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_10_10_10_2>::put;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::p_2_10_10_10>::put;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 1, false, ImageBlockPacking::s_32_p_24_8>::put;
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
PutImagePixelNormPlanarFunc<ImageView> put_pixel_norm_planar_func(const ImageView& image) {
   using dim_type = glm::vec<2, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));   
   if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ImageComponentType component_type = static_cast<ImageComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ImageComponentType>(component_types[c]) != component_type) {
            component_type = ImageComponentType::none;
            break;
         }
      }

      if (component_type == ImageComponentType::unorm) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_3_2, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_3_3, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_2_3, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_6_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_24, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_24_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_11_10, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_11_11, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_10_11, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::unorm>::put;
         }
      } else if (component_type == ImageComponentType::uint) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_3_2, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_3_3, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_2_3, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_6_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_24, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_24_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_11_10, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_11_11, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_10_11, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::uint>::put;
         }
      } else if (component_type == ImageComponentType::sfloat) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::sfloat>::put;
         }
      }
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8>::put;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8>::put;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8>::put;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_8_8_8_8>::put;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16>::put;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16>::put;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16>::put;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_16_16_16_16>::put;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32>::put;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32>::put;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32>::put;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_32_32_32>::put;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64>::put;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64>::put;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64>::put;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_64_64_64_64>::put;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4>::put;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_3_2>::put;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_3_3>::put;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_3_2_3>::put;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_4_4_4_4>::put;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_1_5_5_5>::put;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_5_5_1>::put;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_6_5>::put;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_24>::put;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_24_8>::put;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_11_10>::put;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_11_11>::put;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_11_10_11>::put;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_8_8_8_8>::put;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_9_9_9_5>::put;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_5_9_9_9>::put;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_10_10_10_2>::put;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::p_2_10_10_10>::put;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 2, true, ImageBlockPacking::s_32_p_24_8>::put;
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_8>::put;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_8_8>::put;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_8_8_8>::put;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_8_8_8_8>::put;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_16>::put;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_16_16>::put;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_16_16_16>::put;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_16_16_16_16>::put;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32>::put;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32_32>::put;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32_32_32>::put;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32_32_32_32>::put;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_64>::put;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_64_64>::put;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_64_64_64>::put;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_64_64_64_64>::put;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_4_4>::put;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_3_3_2>::put;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_2_3_3>::put;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_3_2_3>::put;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_4_4_4_4>::put;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_1_5_5_5>::put;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_5_5_5_1>::put;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_5_6_5>::put;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_8_24>::put;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_24_8>::put;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_11_11_10>::put;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_10_11_11>::put;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_11_10_11>::put;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_8_8_8_8>::put;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_9_9_9_5>::put;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_5_9_9_9>::put;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_10_10_10_2>::put;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::p_2_10_10_10>::put;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 2, false, ImageBlockPacking::s_32_p_24_8>::put;
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
PutImagePixelNormVolumetricFunc<ImageView> put_pixel_norm_volumetric_func(const ImageView& image) {
   using dim_type = glm::vec<3, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));   
   if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ImageComponentType component_type = static_cast<ImageComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ImageComponentType>(component_types[c]) != component_type) {
            component_type = ImageComponentType::none;
            break;
         }
      }

      if (component_type == ImageComponentType::unorm) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_3_2, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_3_3, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_2_3, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_6_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_24, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_24_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_11_10, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_11_11, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_10_11, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::unorm>::put;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::unorm>::put;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::unorm>::put;
         }
      } else if (component_type == ImageComponentType::uint) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_3_2, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_3_3, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_2_3, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4_4_4, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_1_5_5_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_5_5_1, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_6_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_24, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_24_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_11_10, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_11_11, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_10_11, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_8_8_8, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_9_9_9_5, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_9_9_9, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_10_10_2, ImageComponentType::uint>::put;
            case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_10_10_10, ImageComponentType::uint>::put;
            case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_p_24_8, ImageComponentType::uint>::put;
         }
      } else if (component_type == ImageComponentType::sfloat) {
         switch (image.format().packing()) {
            case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8_8, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16_16, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32_32, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64, ImageComponentType::sfloat>::put;
            case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64_64, ImageComponentType::sfloat>::put;
         }
      }
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8>::put;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8>::put;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8>::put;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_8_8_8_8>::put;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16>::put;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16>::put;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16>::put;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_16_16_16_16>::put;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32>::put;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32>::put;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32>::put;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_32_32_32>::put;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64>::put;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64>::put;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64>::put;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_64_64_64_64>::put;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4>::put;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_3_2>::put;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_3_3>::put;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_3_2_3>::put;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_4_4_4_4>::put;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_1_5_5_5>::put;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_5_5_1>::put;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_6_5>::put;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_24>::put;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_24_8>::put;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_11_10>::put;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_11_11>::put;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_11_10_11>::put;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_8_8_8_8>::put;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_9_9_9_5>::put;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_5_9_9_9>::put;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_10_10_10_2>::put;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::p_2_10_10_10>::put;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 3, true, ImageBlockPacking::s_32_p_24_8>::put;
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         case ImageBlockPacking::s_8:           return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_8>::put;
         case ImageBlockPacking::s_8_8:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_8_8>::put;
         case ImageBlockPacking::s_8_8_8:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_8_8_8>::put;
         case ImageBlockPacking::s_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_8_8_8_8>::put;
         case ImageBlockPacking::s_16:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_16>::put;
         case ImageBlockPacking::s_16_16:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_16_16>::put;
         case ImageBlockPacking::s_16_16_16:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_16_16_16>::put;
         case ImageBlockPacking::s_16_16_16_16: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_16_16_16_16>::put;
         case ImageBlockPacking::s_32:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32>::put;
         case ImageBlockPacking::s_32_32:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32_32>::put;
         case ImageBlockPacking::s_32_32_32:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32_32_32>::put;
         case ImageBlockPacking::s_32_32_32_32: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32_32_32_32>::put;
         case ImageBlockPacking::s_64:          return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_64>::put;
         case ImageBlockPacking::s_64_64:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_64_64>::put;
         case ImageBlockPacking::s_64_64_64:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_64_64_64>::put;
         case ImageBlockPacking::s_64_64_64_64: return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_64_64_64_64>::put;
         case ImageBlockPacking::p_4_4:         return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_4_4>::put;
         case ImageBlockPacking::p_3_3_2:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_3_3_2>::put;
         case ImageBlockPacking::p_2_3_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_2_3_3>::put;
         case ImageBlockPacking::p_3_2_3:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_3_2_3>::put;
         case ImageBlockPacking::p_4_4_4_4:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_4_4_4_4>::put;
         case ImageBlockPacking::p_1_5_5_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_1_5_5_5>::put;
         case ImageBlockPacking::p_5_5_5_1:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_5_5_5_1>::put;
         case ImageBlockPacking::p_5_6_5:       return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_5_6_5>::put;
         case ImageBlockPacking::p_8_24:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_8_24>::put;
         case ImageBlockPacking::p_24_8:        return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_24_8>::put;
         case ImageBlockPacking::p_11_11_10:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_11_11_10>::put;
         case ImageBlockPacking::p_10_11_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_10_11_11>::put;
         case ImageBlockPacking::p_11_10_11:    return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_11_10_11>::put;
         case ImageBlockPacking::p_8_8_8_8:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_8_8_8_8>::put;
         case ImageBlockPacking::p_9_9_9_5:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_9_9_9_5>::put;
         case ImageBlockPacking::p_5_9_9_9:     return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_5_9_9_9>::put;
         case ImageBlockPacking::p_10_10_10_2:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_10_10_10_2>::put;
         case ImageBlockPacking::p_2_10_10_10:  return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::p_2_10_10_10>::put;
         case ImageBlockPacking::s_32_p_24_8:   return detail::image_pixel_access_uncompressed_norm<ImageView, 3, false, ImageBlockPacking::s_32_p_24_8>::put;
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}

/* ######################### END OF GENERATED CODE ######################### */

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, I32 pixel_coord) {
   return get_pixel_norm_lineal_func<ImageView>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, ivec2 pixel_coord) {
   return get_pixel_norm_planar_func<ImageView>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
vec4 get_pixel_norm(const ImageView& image, ivec3 pixel_coord) {
   return get_pixel_norm_volumetric_func<ImageView>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
void put_pixel_norm(ImageView& image, I32 pixel_coord, vec4 pixel) {
   put_pixel_norm_lineal_func<ImageView>(image)(image, pixel_coord, pixel);
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
void put_pixel_norm(ImageView& image, ivec2 pixel_coord, vec4 pixel) {
   put_pixel_norm_planar_func<ImageView>(image)(image, pixel_coord, pixel);
}

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView>
void put_pixel_norm(ImageView& image, ivec3 pixel_coord, vec4 pixel) {
   put_pixel_norm_volumetric_func<ImageView>(image)(image, pixel_coord, pixel);
}

} // be::gfx

#endif
