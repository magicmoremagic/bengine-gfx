#if !defined(BE_GFX_TEX_PIXEL_ACCESS_NORM_HPP_) && !defined(DOXYGEN)
#include "pixel_access_norm.hpp"
#elif !defined(BE_GFX_TEX_PIXEL_ACCESS_NORM_INL_)
#define BE_GFX_TEX_PIXEL_ACCESS_NORM_INL_

namespace be::gfx::tex {
namespace detail {

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

#pragma region ComponentRawNorm

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits, ComponentType ComponentType>
struct ComponentRawNorm {
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
struct ComponentRawNorm<T, Bits, ComponentType::uint> {
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
struct ComponentRawNorm<T, 64, ComponentType::uint> {
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
struct ComponentRawNorm<T, Bits, ComponentType::sint> {
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
struct ComponentRawNorm<T, 1, ComponentType::sint> {
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
struct ComponentRawNorm<T, 64, ComponentType::sint> {
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
struct ComponentRawNorm<T, Bits, ComponentType::unorm> {
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
struct ComponentRawNorm<T, 64, ComponentType::unorm> {
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
struct ComponentRawNorm<T, Bits, ComponentType::snorm> {
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
struct ComponentRawNorm<T, 1, ComponentType::snorm> {
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
struct ComponentRawNorm<T, 64, ComponentType::snorm> {
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
struct ComponentRawNorm<T, 11, ComponentType::ufloat> {
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
            std::memcpy(&value, &f32_data, sizeof(F32));
         }
      } else if (f11_exponent == f11_exponent_mask) {
         if (f11_data == f11_exponent_mask) {
            // inf -> inf
            constexpr U32 f32_data = f32_exponent_mask;
            std::memcpy(&value, &f32_data, sizeof(F32));
         } else {
            // any nan -> qnan
            constexpr U32 f32_data = f32_exponent_mask | (f32_mantissa_mask & ~0);
            std::memcpy(&value, &f32_data, sizeof(F32));
         }
      } else {
         // normal -> normal
         U32 f32_data = ((f11_exponent << shift) + ((f32_exponent_basis - f11_exponent_basis) << f32_mantissa_bits)) | ((f11_data & f11_mantissa_mask) << shift);
         std::memcpy(&value, &f32_data, sizeof(F32));
      }
      return value;
   }

   static T encode(F32 component) {
      U16 f11_data;
      U32 f32_data;
      std::memcpy(&f32_data, &component, sizeof(U32));

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
struct ComponentRawNorm<T, 10, ComponentType::ufloat> {
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
            std::memcpy(&value, &f32_data, sizeof(F32));
         }
      } else if (f10_exponent == f10_exponent_mask) {
         if (f10_data == f10_exponent_mask) {
            // inf -> inf
            constexpr U32 f32_data = f32_exponent_mask;
            std::memcpy(&value, &f32_data, sizeof(F32));
         } else {
            // any nan -> qnan
            constexpr U32 f32_data = f32_exponent_mask | (f32_mantissa_mask & ~0);
            std::memcpy(&value, &f32_data, sizeof(F32));
         }
      } else {
         // normal -> normal
         U32 f32_data = ((f10_exponent << shift) + ((f32_exponent_basis - f10_exponent_basis) << f32_mantissa_bits)) | ((f10_data & f10_mantissa_mask) << shift);
         std::memcpy(&value, &f32_data, sizeof(F32));
      }
      return value;
   }

   static T encode(F32 component) {
      U16 f10_data;
      U32 f32_data;
      std::memcpy(&f32_data, &component, sizeof(U32));

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
struct ComponentRawNorm<T, 64, ComponentType::sfloat> {
   static F32 decode(T data) {
      static_assert(sizeof(T) == 8);
      F64 float_data;
      std::memcpy(&float_data, &data, sizeof(F64));
      return static_cast<F32>(float_data);
   }
   static T encode(F32 component) {
      static_assert(sizeof(T) == 8);
      T data;
      F64 float_data = component;
      std::memcpy(&data, &float_data, sizeof(F64));
      return data;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct ComponentRawNorm<T, 32, ComponentType::sfloat> {
   static F32 decode(T data) {
      static_assert(sizeof(T) == 4);
      F32 float_data;
      std::memcpy(&float_data, &data, sizeof(F32));
      return float_data;
   }
   static T encode(F32 component) {
      static_assert(sizeof(T) == 4);
      T data;
      std::memcpy(&data, &component, sizeof(F32));
      return data;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct ComponentRawNorm<T, 16, ComponentType::sfloat> {
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
            std::memcpy(&value, &f32_data, sizeof(F32));
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
            std::memcpy(&value, &f32_data, sizeof(F32));
         }
      } else if (f16_exponent == f16_exponent_mask) {
         if (f16_data == f16_exponent_mask) {
            // inf -> inf
            U32 f32_data = f32_exponent_mask | f32_sign;
            std::memcpy(&value, &f32_data, sizeof(F32));
         } else {
            // any nan -> qnan
            U32 f32_data = f32_exponent_mask | (f32_mantissa_mask & ~0) | f32_sign;
            std::memcpy(&value, &f32_data, sizeof(F32));
         }
      } else {
         // normal -> normal
         U32 f32_data = f32_sign | ((f16_exponent << shift) + ((f32_exponent_basis - f16_exponent_basis) << f32_mantissa_bits)) | ((f16_data & f16_mantissa_mask) << shift);
         std::memcpy(&value, &f32_data, sizeof(F32));
      }
      return value;
   }

   static T encode(F32 component) {
      U16 f16_data;
      U32 f32_data;
      std::memcpy(&f32_data, &component, sizeof(U32));

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
F32 decode_image_component(UnsignedType data, ComponentType type) {
   switch (type) {
      case ComponentType::expo:
      case ComponentType::uint:   return ComponentRawNorm<UnsignedType, Bits, ComponentType::uint>::decode(data);
      case ComponentType::sint:   return ComponentRawNorm<UnsignedType, Bits, ComponentType::sint>::decode(data);
      case ComponentType::unorm:  return ComponentRawNorm<UnsignedType, Bits, ComponentType::unorm>::decode(data);
      case ComponentType::snorm:  return ComponentRawNorm<UnsignedType, Bits, ComponentType::snorm>::decode(data);
      case ComponentType::ufloat: return ComponentRawNorm<UnsignedType, Bits, ComponentType::ufloat>::decode(data);
      case ComponentType::sfloat: return ComponentRawNorm<UnsignedType, Bits, ComponentType::sfloat>::decode(data);
      default:                         return ComponentRawNorm<UnsignedType, Bits, ComponentType::none>::decode(data);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename UnsignedType, std::size_t Bits>
UnsignedType encode_image_component(F32 component, ComponentType type) {
   switch (type) {
      case ComponentType::expo:
      case ComponentType::uint:   return ComponentRawNorm<UnsignedType, Bits, ComponentType::uint>::encode(component);
      case ComponentType::sint:   return ComponentRawNorm<UnsignedType, Bits, ComponentType::sint>::encode(component);
      case ComponentType::unorm:  return ComponentRawNorm<UnsignedType, Bits, ComponentType::unorm>::encode(component);
      case ComponentType::snorm:  return ComponentRawNorm<UnsignedType, Bits, ComponentType::snorm>::encode(component);
      case ComponentType::ufloat: return ComponentRawNorm<UnsignedType, Bits, ComponentType::ufloat>::encode(component);
      case ComponentType::sfloat: return ComponentRawNorm<UnsignedType, Bits, ComponentType::sfloat>::encode(component);
      default:                         return ComponentRawNorm<UnsignedType, Bits, ComponentType::none>::encode(component);
   }
}

#pragma region PixelRawNormAccessUncompressedNonPacked

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType>
struct PixelRawNormAccessUncompressedNonPacked {
   static constexpr glm::length_t components = BlockPackingInfo<Packing>::components;
   static constexpr std::size_t word_size_bits = BlockPackingInfo<Packing>::word_size * 8;

   using word_type = typename BlockPackingInfo<Packing>::unsigned_word_type;
   using data_type = glm::vec<components, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      for (glm::length_t c = 0; c < components; ++c) {
         pixel[c] = ComponentRawNorm<word_type, word_size_bits, ComponentType>::decode(data[c]);
      }
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      for (glm::length_t c = 0; c < components; ++c) {
         data[c] = ComponentRawNorm<word_type, word_size_bits, ComponentType>::encode(pixel[c]);
      }
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedNonPacked<ImageView, Coord, IsSimple, Packing, ComponentType::none> {
   static constexpr glm::length_t components = BlockPackingInfo<Packing>::components;
   static constexpr std::size_t word_size_bits = BlockPackingInfo<Packing>::word_size * 8;

   using word_type = typename BlockPackingInfo<Packing>::unsigned_word_type;
   using data_type = glm::vec<components, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto component_types = image.format().component_types();
      for (glm::length_t c = 0; c < components; ++c) {
         pixel[c] = decode_image_component<word_type, word_size_bits>(data[c], static_cast<ComponentType>(component_types[c]));
      }
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      for (glm::length_t c = 0; c < components; ++c) {
         data[c] = encode_image_component<word_type, word_size_bits>(pixel[c], static_cast<ComponentType>(component_types[c]));
      }
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

#pragma endregion
#pragma region PixelRawNormAccessUncompressedPacked

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType, U8 Components = BlockPackingInfo<Packing>::components>
struct PixelRawNormAccessUncompressedPacked { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType, 1> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      pixel[0] = ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::component_word_offset[0]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType>::encode(pixel[0]) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType::none, 1> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto component_types = image.format().component_types();
      pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ComponentType>(component_types[0]));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType, 2> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      pixel[0] = ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
      pixel[1] = ComponentRawNorm<word_type, packing_info::component_bit_width[1], ComponentType>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::component_word_offset[0]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType>::encode(pixel[0]) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[1], ComponentType>::encode(pixel[1]) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType::none, 2> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto component_types = image.format().component_types();
      pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ComponentType>(component_types[0]));
      pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ComponentType>(component_types[1]));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType, 3> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      pixel[0] = ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
      pixel[1] = ComponentRawNorm<word_type, packing_info::component_bit_width[1], ComponentType>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
      pixel[2] = ComponentRawNorm<word_type, packing_info::component_bit_width[2], ComponentType>::decode((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::component_word_offset[0]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType>::encode(pixel[0]) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[1], ComponentType>::encode(pixel[1]) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      data[packing_info::component_word_offset[2]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[2], ComponentType>::encode(pixel[2]) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType::none, 3> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto component_types = image.format().component_types();
      pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ComponentType>(component_types[0]));
      pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ComponentType>(component_types[1]));
      pixel[2] = decode_image_component<word_type, packing_info::component_bit_width[2]>((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1), static_cast<ComponentType>(component_types[2]));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      data[packing_info::component_word_offset[2]] |= (encode_image_component<word_type, packing_info::component_bit_width[2]>(pixel[2], static_cast<ComponentType>(component_types[2])) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType, 4> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      pixel[0] = ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
      pixel[1] = ComponentRawNorm<word_type, packing_info::component_bit_width[1], ComponentType>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
      pixel[2] = ComponentRawNorm<word_type, packing_info::component_bit_width[2], ComponentType>::decode((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1));
      pixel[3] = ComponentRawNorm<word_type, packing_info::component_bit_width[3], ComponentType>::decode((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::component_word_offset[0]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType>::encode(pixel[0]) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[1], ComponentType>::encode(pixel[1]) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      data[packing_info::component_word_offset[2]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[2], ComponentType>::encode(pixel[2]) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
      data[packing_info::component_word_offset[3]] |= (ComponentRawNorm<word_type, packing_info::component_bit_width[3], ComponentType>::encode(pixel[3]) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType::none, 4> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto component_types = image.format().component_types();
      pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ComponentType>(component_types[0]));
      pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ComponentType>(component_types[1]));
      pixel[2] = decode_image_component<word_type, packing_info::component_bit_width[2]>((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1), static_cast<ComponentType>(component_types[2]));
      pixel[3] = decode_image_component<word_type, packing_info::component_bit_width[3]>((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1), static_cast<ComponentType>(component_types[3]));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
      data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
      data[packing_info::component_word_offset[2]] |= (encode_image_component<word_type, packing_info::component_bit_width[2]>(pixel[2], static_cast<ComponentType>(component_types[2])) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
      data[packing_info::component_word_offset[3]] |= (encode_image_component<word_type, packing_info::component_bit_width[3]>(pixel[3], static_cast<ComponentType>(component_types[3])) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, BlockPacking::p_9_9_9_5, ComponentType::none, 4> {
   using packing_info = BlockPackingInfo<BlockPacking::p_9_9_9_5>;
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
      std::memcpy(&data, &value, sizeof(F32));
      return (data >> f32_mantissa_bits) - f32_exponent_basis;
   }

   static F32 pow2(int exponent) {
      F32 value;
      exponent += f32_exponent_basis;
      assert(exponent > 0);
      assert(exponent < (1u << f32_exponent_bits) - 1);
      U32 data = exponent << f32_mantissa_bits;
      std::memcpy(&value, &data, sizeof(F32));
      return value;
   }

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto component_types = image.format().component_types();
      constexpr U8 ufloat = static_cast<U8>(ComponentType::ufloat);
      constexpr U8 expo = static_cast<U8>(ComponentType::expo);
      if (component_types == ImageFormat::component_types_type(ufloat, ufloat, ufloat, expo)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         vec3 pixel3;
         pixel3[0] = ComponentRawNorm<word_type, packing_info::component_bit_width[0], ComponentType::uint>::decode((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1));
         pixel3[1] = ComponentRawNorm<word_type, packing_info::component_bit_width[1], ComponentType::uint>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
         pixel3[2] = ComponentRawNorm<word_type, packing_info::component_bit_width[2], ComponentType::uint>::decode((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1));

         word_type exponent = (data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1);
         pixel3 *= pow2(exponent - f14_exponent_basis - f14_mantissa_bits);
         pixel = vec4(pixel3, 0.f);
      } else {
         pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ComponentType>(component_types[0]));
         pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ComponentType>(component_types[1]));
         pixel[2] = decode_image_component<word_type, packing_info::component_bit_width[2]>((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1), static_cast<ComponentType>(component_types[2]));
         pixel[3] = decode_image_component<word_type, packing_info::component_bit_width[3]>((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1), static_cast<ComponentType>(component_types[3]));
      }
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      constexpr U8 ufloat = static_cast<U8>(ComponentType::ufloat);
      constexpr U8 expo = static_cast<U8>(ComponentType::expo);
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
         data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
         data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
         data[packing_info::component_word_offset[2]] |= (encode_image_component<word_type, packing_info::component_bit_width[2]>(pixel[2], static_cast<ComponentType>(component_types[2])) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
         data[packing_info::component_word_offset[3]] |= (encode_image_component<word_type, packing_info::component_bit_width[3]>(pixel[3], static_cast<ComponentType>(component_types[3])) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      }
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, BlockPacking::p_5_9_9_9, ComponentType::none, 4> {
   using packing_info = BlockPackingInfo<BlockPacking::p_5_9_9_9>;
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
      std::memcpy(&data, &value, sizeof(F32));
      return (data >> f32_mantissa_bits) - f32_exponent_basis;
   }

   static F32 pow2(int exponent) {
      F32 value;
      exponent += f32_exponent_basis;
      assert(exponent > 0);
      assert(exponent < (1u << f32_exponent_bits) - 1);
      U32 data = exponent << f32_mantissa_bits;
      std::memcpy(&value, &data, sizeof(F32));
      return value;
   }

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto component_types = image.format().component_types();
      constexpr U8 ufloat = static_cast<U8>(ComponentType::ufloat);
      constexpr U8 expo = static_cast<U8>(ComponentType::expo);
      if (component_types == ImageFormat::component_types_type(expo, ufloat, ufloat, ufloat)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         vec3 pixel3;
         pixel3[0] = ComponentRawNorm<word_type, packing_info::component_bit_width[1], ComponentType::uint>::decode((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1));
         pixel3[1] = ComponentRawNorm<word_type, packing_info::component_bit_width[2], ComponentType::uint>::decode((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1));
         pixel3[2] = ComponentRawNorm<word_type, packing_info::component_bit_width[3], ComponentType::uint>::decode((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1));

         word_type exponent = (data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1);
         pixel3 *= pow2(exponent - f14_exponent_basis - f14_mantissa_bits);
         pixel = vec4(0.f, pixel3);
      } else {
         pixel[0] = decode_image_component<word_type, packing_info::component_bit_width[0]>((data[packing_info::component_word_offset[0]] >> packing_info::component_bit_offset[0]) & ((1 << packing_info::component_bit_width[0]) - 1), static_cast<ComponentType>(component_types[0]));
         pixel[1] = decode_image_component<word_type, packing_info::component_bit_width[1]>((data[packing_info::component_word_offset[1]] >> packing_info::component_bit_offset[1]) & ((1 << packing_info::component_bit_width[1]) - 1), static_cast<ComponentType>(component_types[1]));
         pixel[2] = decode_image_component<word_type, packing_info::component_bit_width[2]>((data[packing_info::component_word_offset[2]] >> packing_info::component_bit_offset[2]) & ((1 << packing_info::component_bit_width[2]) - 1), static_cast<ComponentType>(component_types[2]));
         pixel[3] = decode_image_component<word_type, packing_info::component_bit_width[3]>((data[packing_info::component_word_offset[3]] >> packing_info::component_bit_offset[3]) & ((1 << packing_info::component_bit_width[3]) - 1), static_cast<ComponentType>(component_types[3]));
      }
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto component_types = image.format().component_types();
      constexpr U8 ufloat = static_cast<U8>(ComponentType::ufloat);
      constexpr U8 expo = static_cast<U8>(ComponentType::expo);
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
         data[packing_info::component_word_offset[0]] |= (encode_image_component<word_type, packing_info::component_bit_width[0]>(pixel[0], static_cast<ComponentType>(component_types[0])) & ((1 << packing_info::component_bit_width[0]) - 1)) << packing_info::component_bit_offset[0];
         data[packing_info::component_word_offset[1]] |= (encode_image_component<word_type, packing_info::component_bit_width[1]>(pixel[1], static_cast<ComponentType>(component_types[1])) & ((1 << packing_info::component_bit_width[1]) - 1)) << packing_info::component_bit_offset[1];
         data[packing_info::component_word_offset[2]] |= (encode_image_component<word_type, packing_info::component_bit_width[2]>(pixel[2], static_cast<ComponentType>(component_types[2])) & ((1 << packing_info::component_bit_width[2]) - 1)) << packing_info::component_bit_offset[2];
         data[packing_info::component_word_offset[3]] |= (encode_image_component<word_type, packing_info::component_bit_width[3]>(pixel[3], static_cast<ComponentType>(component_types[3])) & ((1 << packing_info::component_bit_width[3]) - 1)) << packing_info::component_bit_offset[3];
      }
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

#pragma endregion
#pragma region PixelRawNormAccessUncompressed

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType, bool IsPacked = BlockPackingInfo<Packing>::is_packed::value>
struct PixelRawNormAccessUncompressed { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType>
struct PixelRawNormAccessUncompressed<ImageView, Coord, IsSimple, Packing, ComponentType, false>
   : PixelRawNormAccessUncompressedNonPacked<ImageView, Coord, IsSimple, Packing, ComponentType> { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType>
struct PixelRawNormAccessUncompressed<ImageView, Coord, IsSimple, Packing, ComponentType, true>
   : PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, ComponentType> { };

#pragma endregion
#pragma region PixelNormAccessUncompressed

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, ComponentType ComponentType = ComponentType::none>
struct PixelNormAccessUncompressed {
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      F32 data[6] = { 0.f, 1.f };
      const vec4 raw = PixelRawNormAccessUncompressed<ImageView, Coord, IsSimple, Packing, ComponentType>::get(image, pixel_coord);
      std::memcpy(data + 2, glm::value_ptr(raw), sizeof(vec4));
      const auto swizzles = image.format().swizzles();
      return vec4(data[swizzles.r], data[swizzles.g], data[swizzles.b], data[swizzles.a]);
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      vec4 unswizzled_pixel;
      const auto swizzles = image.format().swizzles();
      for (glm::length_t c = 3; c >= 0; --c) {
         U8 swizzle = swizzles[c];
         if (swizzle >= 2) {
            unswizzled_pixel[swizzle - 2] = pixel[c];
         }
      }
      PixelRawNormAccessUncompressed<ImageView, Coord, IsSimple, Packing, ComponentType>::put(image, pixel_coord, unswizzled_pixel);
   }
};

#pragma endregion

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, BlockPacking Packing>
struct PixelNormAccessCompressed {
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      // TODO
      return vec4();
   }
};

} // be::gfx::tex::detail

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
GetPixelNormFunc<Coord, ImageView> get_pixel_norm_func(const ImageView& image) {
   using dim_type = glm::vec<t::vector_components<Coord>::value, ImageFormat::block_size_type>;
   assert(image);
   if (is_compressed(image.format().packing())) {
      switch (image.format().packing()) {
         /*!! include('tex/block_packing', true)
         register_template_string([[`
         max_length = image_block_packing.max_constant_name_length
         c = $
         with each image_block_packing.constants using # {
            if not c.pred or c.pred($) {
               `case BlockPacking::`name`:`
               string.rep(' ', max_length + 1 - #name)
               `return detail::` c.struct_name or 'PixelNormAccessUncompressed'
               `<ImageView, Coord` c.pre_params`, BlockPacking::`name c.post_params`>::`c.func_name`;` nl
            }
         }
         ]], 'packing_switch')

         function is_compressed (t)  return t.n_comp == 0 end
         function not_compressed (t) return t.n_comp ~= 0 end
         function is_standard (t)    return t.n_comp ~= 0 and t.n_comp == t.n_words end

         write_template('packing_switch', { pred = is_compressed, struct_name = 'PixelNormAccessCompressed', func_name = 'get' }) !! 13 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         case BlockPacking::c_astc:        return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_astc>::get;
         case BlockPacking::c_bptc:        return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_bptc>::get;
         case BlockPacking::c_etc1:        return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_etc1>::get;
         case BlockPacking::c_etc2:        return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_etc2>::get;
         case BlockPacking::c_s3tc1:       return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_s3tc1>::get;
         case BlockPacking::c_s3tc2:       return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_s3tc2>::get;
         case BlockPacking::c_s3tc3:       return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_s3tc3>::get;
         case BlockPacking::c_rgtc1:       return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_rgtc1>::get;
         case BlockPacking::c_rgtc2:       return detail::PixelNormAccessCompressed<ImageView, Coord, BlockPacking::c_rgtc2>::get;
         
         /* ######################### END OF GENERATED CODE ######################### */
         default:
            assert(false);
            break;
      }
   } else if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ComponentType component_type = static_cast<ComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ComponentType>(component_types[c]) != component_type) {
            component_type = ComponentType::none;
            break;
         }
      }

      if (component_type == ComponentType::unorm) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', post_params = ', ComponentType::unorm', func_name = 'get' }) !! 39 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, ComponentType::unorm>::get;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, ComponentType::unorm>::get;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, ComponentType::unorm>::get;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, ComponentType::unorm>::get;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, ComponentType::unorm>::get;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, ComponentType::unorm>::get;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, ComponentType::unorm>::get;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, ComponentType::unorm>::get;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, ComponentType::unorm>::get;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, ComponentType::unorm>::get;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, ComponentType::unorm>::get;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, ComponentType::unorm>::get;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, ComponentType::unorm>::get;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, ComponentType::unorm>::get;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, ComponentType::unorm>::get;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, ComponentType::unorm>::get;
            case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4, ComponentType::unorm>::get;
            case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2, ComponentType::unorm>::get;
            case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3, ComponentType::unorm>::get;
            case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3, ComponentType::unorm>::get;
            case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4, ComponentType::unorm>::get;
            case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5, ComponentType::unorm>::get;
            case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1, ComponentType::unorm>::get;
            case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5, ComponentType::unorm>::get;
            case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24, ComponentType::unorm>::get;
            case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8, ComponentType::unorm>::get;
            case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10, ComponentType::unorm>::get;
            case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11, ComponentType::unorm>::get;
            case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11, ComponentType::unorm>::get;
            case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8, ComponentType::unorm>::get;
            case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5, ComponentType::unorm>::get;
            case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9, ComponentType::unorm>::get;
            case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2, ComponentType::unorm>::get;
            case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10, ComponentType::unorm>::get;
            case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8, ComponentType::unorm>::get;
            
            /* ######################### END OF GENERATED CODE ######################### */

      //`return detail::PixelNormAccessUncompressed<ImageView, `i`, true, BlockPacking::`name`, ComponentType::unorm>::get;`
         }
      } else if (component_type == ComponentType::uint) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', post_params = ', ComponentType::uint', func_name = 'get' }) !! 39 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, ComponentType::uint>::get;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, ComponentType::uint>::get;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, ComponentType::uint>::get;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, ComponentType::uint>::get;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, ComponentType::uint>::get;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, ComponentType::uint>::get;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, ComponentType::uint>::get;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, ComponentType::uint>::get;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, ComponentType::uint>::get;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, ComponentType::uint>::get;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, ComponentType::uint>::get;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, ComponentType::uint>::get;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, ComponentType::uint>::get;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, ComponentType::uint>::get;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, ComponentType::uint>::get;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, ComponentType::uint>::get;
            case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4, ComponentType::uint>::get;
            case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2, ComponentType::uint>::get;
            case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3, ComponentType::uint>::get;
            case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3, ComponentType::uint>::get;
            case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4, ComponentType::uint>::get;
            case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5, ComponentType::uint>::get;
            case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1, ComponentType::uint>::get;
            case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5, ComponentType::uint>::get;
            case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24, ComponentType::uint>::get;
            case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8, ComponentType::uint>::get;
            case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10, ComponentType::uint>::get;
            case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11, ComponentType::uint>::get;
            case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11, ComponentType::uint>::get;
            case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8, ComponentType::uint>::get;
            case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5, ComponentType::uint>::get;
            case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9, ComponentType::uint>::get;
            case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2, ComponentType::uint>::get;
            case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10, ComponentType::uint>::get;
            case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8, ComponentType::uint>::get;
            
            /* ######################### END OF GENERATED CODE ######################### */

      //`return detail::PixelNormAccessUncompressed<ImageView, `i`, true, BlockPacking::`name`, ComponentType::uint>::get;`
         }
      } else if (component_type == ComponentType::sfloat) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = is_standard, pre_params = ', true', post_params = ', ComponentType::sfloat', func_name = 'get' }) !! 20 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, ComponentType::sfloat>::get;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, ComponentType::sfloat>::get;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, ComponentType::sfloat>::get;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, ComponentType::sfloat>::get;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, ComponentType::sfloat>::get;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, ComponentType::sfloat>::get;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, ComponentType::sfloat>::get;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, ComponentType::sfloat>::get;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, ComponentType::sfloat>::get;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, ComponentType::sfloat>::get;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, ComponentType::sfloat>::get;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, ComponentType::sfloat>::get;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, ComponentType::sfloat>::get;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, ComponentType::sfloat>::get;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, ComponentType::sfloat>::get;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, ComponentType::sfloat>::get;
            
            /* ######################### END OF GENERATED CODE ######################### */

      //`return detail::PixelNormAccessUncompressed<ImageView, `i`, true, BlockPacking::`name`, ComponentType::sfloat>::get;`
         }
      }
      switch (image.format().packing()) {
         /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', func_name = 'get' }) !! 39 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8>::get;
         case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8>::get;
         case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8>::get;
         case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8>::get;
         case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16>::get;
         case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16>::get;
         case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16>::get;
         case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16>::get;
         case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32>::get;
         case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32>::get;
         case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32>::get;
         case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32>::get;
         case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64>::get;
         case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64>::get;
         case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64>::get;
         case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64>::get;
         case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4>::get;
         case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2>::get;
         case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3>::get;
         case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3>::get;
         case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4>::get;
         case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5>::get;
         case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1>::get;
         case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5>::get;
         case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24>::get;
         case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8>::get;
         case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10>::get;
         case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11>::get;
         case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11>::get;
         case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8>::get;
         case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5>::get;
         case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9>::get;
         case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2>::get;
         case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10>::get;
         case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8>::get;
         
         /* ######################### END OF GENERATED CODE ######################### */

      //`return detail::PixelNormAccessUncompressed<ImageView, `i`, true, BlockPacking::`name`>::get;`
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', false', func_name = 'get' }) !! 39 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_8>::get;
         case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_8_8>::get;
         case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_8_8_8>::get;
         case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_8_8_8_8>::get;
         case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_16>::get;
         case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_16_16>::get;
         case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_16_16_16>::get;
         case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_16_16_16_16>::get;
         case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32>::get;
         case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32_32>::get;
         case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32_32_32>::get;
         case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32_32_32_32>::get;
         case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_64>::get;
         case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_64_64>::get;
         case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_64_64_64>::get;
         case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_64_64_64_64>::get;
         case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_4_4>::get;
         case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_3_3_2>::get;
         case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_3_3>::get;
         case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_3_2_3>::get;
         case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_4_4_4_4>::get;
         case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_1_5_5_5>::get;
         case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_5_5_1>::get;
         case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_6_5>::get;
         case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_8_24>::get;
         case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_24_8>::get;
         case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_11_11_10>::get;
         case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_10_11_11>::get;
         case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_11_10_11>::get;
         case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_8_8_8_8>::get;
         case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_9_9_9_5>::get;
         case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_9_9_9>::get;
         case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_10_10_10_2>::get;
         case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_10_10_10>::get;
         case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32_p_24_8>::get;
         
         /* ######################### END OF GENERATED CODE ######################### */

      //`return detail::PixelNormAccessUncompressed<ImageView, `i`, false, BlockPacking::`name`>::get;`
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
vec4 get_pixel_norm(const ImageView& image, Coord pixel_coord) {
   return get_pixel_norm_func<Coord, ImageView>(image)(image, pixel_coord);
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
PutPixelNormFunc<Coord, ImageView> put_pixel_norm_func(const ImageView& image) {
   using dim_type = glm::vec<t::vector_components<Coord>::value, ImageFormat::block_size_type>;
   assert(image);
   assert(!is_compressed(image.format().packing()));
   if (dim_type(image.block_dim()) == dim_type(1)) {
      auto component_types = image.format().component_types();
      glm::length_t packing_components = component_count(image.format().packing());
      ComponentType component_type = static_cast<ComponentType>(component_types[0]);
      for (glm::length_t c = 1; c < packing_components; ++c) {
         if (static_cast<ComponentType>(component_types[c]) != component_type) {
            component_type = ComponentType::none;
            break;
         }
      }

      if (component_type == ComponentType::unorm) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', post_params = ', ComponentType::unorm', func_name = 'put' }) !! 39 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, ComponentType::unorm>::put;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, ComponentType::unorm>::put;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, ComponentType::unorm>::put;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, ComponentType::unorm>::put;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, ComponentType::unorm>::put;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, ComponentType::unorm>::put;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, ComponentType::unorm>::put;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, ComponentType::unorm>::put;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, ComponentType::unorm>::put;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, ComponentType::unorm>::put;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, ComponentType::unorm>::put;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, ComponentType::unorm>::put;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, ComponentType::unorm>::put;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, ComponentType::unorm>::put;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, ComponentType::unorm>::put;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, ComponentType::unorm>::put;
            case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4, ComponentType::unorm>::put;
            case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2, ComponentType::unorm>::put;
            case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3, ComponentType::unorm>::put;
            case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3, ComponentType::unorm>::put;
            case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4, ComponentType::unorm>::put;
            case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5, ComponentType::unorm>::put;
            case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1, ComponentType::unorm>::put;
            case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5, ComponentType::unorm>::put;
            case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24, ComponentType::unorm>::put;
            case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8, ComponentType::unorm>::put;
            case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10, ComponentType::unorm>::put;
            case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11, ComponentType::unorm>::put;
            case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11, ComponentType::unorm>::put;
            case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8, ComponentType::unorm>::put;
            case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5, ComponentType::unorm>::put;
            case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9, ComponentType::unorm>::put;
            case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2, ComponentType::unorm>::put;
            case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10, ComponentType::unorm>::put;
            case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8, ComponentType::unorm>::put;
            
            /* ######################### END OF GENERATED CODE ######################### */
         }
      } else if (component_type == ComponentType::uint) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', post_params = ', ComponentType::uint', func_name = 'put' }) !! 39 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, ComponentType::uint>::put;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, ComponentType::uint>::put;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, ComponentType::uint>::put;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, ComponentType::uint>::put;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, ComponentType::uint>::put;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, ComponentType::uint>::put;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, ComponentType::uint>::put;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, ComponentType::uint>::put;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, ComponentType::uint>::put;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, ComponentType::uint>::put;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, ComponentType::uint>::put;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, ComponentType::uint>::put;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, ComponentType::uint>::put;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, ComponentType::uint>::put;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, ComponentType::uint>::put;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, ComponentType::uint>::put;
            case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4, ComponentType::uint>::put;
            case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2, ComponentType::uint>::put;
            case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3, ComponentType::uint>::put;
            case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3, ComponentType::uint>::put;
            case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4, ComponentType::uint>::put;
            case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5, ComponentType::uint>::put;
            case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1, ComponentType::uint>::put;
            case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5, ComponentType::uint>::put;
            case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24, ComponentType::uint>::put;
            case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8, ComponentType::uint>::put;
            case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10, ComponentType::uint>::put;
            case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11, ComponentType::uint>::put;
            case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11, ComponentType::uint>::put;
            case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8, ComponentType::uint>::put;
            case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5, ComponentType::uint>::put;
            case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9, ComponentType::uint>::put;
            case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2, ComponentType::uint>::put;
            case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10, ComponentType::uint>::put;
            case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8, ComponentType::uint>::put;
            
            /* ######################### END OF GENERATED CODE ######################### */
         }
      } else if (component_type == ComponentType::sfloat) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = is_standard, pre_params = ', true', post_params = ', ComponentType::sfloat', func_name = 'put' }) !! 20 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, ComponentType::sfloat>::put;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, ComponentType::sfloat>::put;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, ComponentType::sfloat>::put;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, ComponentType::sfloat>::put;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, ComponentType::sfloat>::put;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, ComponentType::sfloat>::put;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, ComponentType::sfloat>::put;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, ComponentType::sfloat>::put;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, ComponentType::sfloat>::put;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, ComponentType::sfloat>::put;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, ComponentType::sfloat>::put;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, ComponentType::sfloat>::put;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, ComponentType::sfloat>::put;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, ComponentType::sfloat>::put;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, ComponentType::sfloat>::put;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, ComponentType::sfloat>::put;
            
            /* ######################### END OF GENERATED CODE ######################### */
         }
      }
      switch (image.format().packing()) {
         /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', func_name = 'put' }) !! 39 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8>::put;
         case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8>::put;
         case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8>::put;
         case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8>::put;
         case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16>::put;
         case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16>::put;
         case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16>::put;
         case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16>::put;
         case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32>::put;
         case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32>::put;
         case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32>::put;
         case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32>::put;
         case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64>::put;
         case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64>::put;
         case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64>::put;
         case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64>::put;
         case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4>::put;
         case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2>::put;
         case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3>::put;
         case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3>::put;
         case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4>::put;
         case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5>::put;
         case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1>::put;
         case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5>::put;
         case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24>::put;
         case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8>::put;
         case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10>::put;
         case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11>::put;
         case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11>::put;
         case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8>::put;
         case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5>::put;
         case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9>::put;
         case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2>::put;
         case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10>::put;
         case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8>::put;
         
         /* ######################### END OF GENERATED CODE ######################### */
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', false', func_name = 'put' }) !! 39 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_8>::put;
         case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_8_8>::put;
         case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_8_8_8>::put;
         case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_8_8_8_8>::put;
         case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_16>::put;
         case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_16_16>::put;
         case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_16_16_16>::put;
         case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_16_16_16_16>::put;
         case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32>::put;
         case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32_32>::put;
         case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32_32_32>::put;
         case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32_32_32_32>::put;
         case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_64>::put;
         case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_64_64>::put;
         case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_64_64_64>::put;
         case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_64_64_64_64>::put;
         case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_4_4>::put;
         case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_3_3_2>::put;
         case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_3_3>::put;
         case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_3_2_3>::put;
         case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_4_4_4_4>::put;
         case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_1_5_5_5>::put;
         case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_5_5_1>::put;
         case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_6_5>::put;
         case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_8_24>::put;
         case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_24_8>::put;
         case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_11_11_10>::put;
         case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_10_11_11>::put;
         case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_11_10_11>::put;
         case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_8_8_8_8>::put;
         case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_9_9_9_5>::put;
         case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_9_9_9>::put;
         case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_10_10_10_2>::put;
         case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_10_10_10>::put;
         case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::s_32_p_24_8>::put;
         
         /* ######################### END OF GENERATED CODE ######################### */
         default:
            assert(false);
            break;
      }
   }
   return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
void put_pixel_norm(ImageView& image, Coord pixel_coord, vec4 pixel) {
   put_pixel_norm_func<Coord, ImageView>(image)(image, pixel_coord, pixel);
}


} // be::gfx::tex

#endif
