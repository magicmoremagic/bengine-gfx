#if !defined(BE_GFX_TEX_PIXEL_ACCESS_NORM_HPP_) && !defined(DOXYGEN)
#include "pixel_access_norm.hpp"
#elif !defined(BE_GFX_TEX_PIXEL_ACCESS_NORM_INL_)
#define BE_GFX_TEX_PIXEL_ACCESS_NORM_INL_

namespace be::gfx::tex {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename UnsignedType, std::size_t Bits>
I32 signed_from_bits(UnsignedType data) {
   constexpr UnsignedType sign_bit_mask = 1ull << (Bits - 1ull);
   if (0 == (data & sign_bit_mask)) {
      return static_cast<I32>(data);
   } else {
      return static_cast<I32>(data | (~U32(0) ^ ((1ull << Bits) - 1ull)));
   }
}

#pragma region FieldRawNorm

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits, FieldType FieldType>
struct FieldRawNorm {
   static_assert(Bits > 0);
   static F32 decode(T data) {
      return 0.f;
   }
   static T encode(F32 field) {
      return T();
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits>
struct FieldRawNorm<T, Bits, FieldType::uint> {
   static_assert(Bits > 0);
   static F32 decode(T data) {
      return static_cast<F32>(data);
   }
   static T encode(F32 field) {
      F32 scale = static_cast<F32>((1ull << Bits) - 1ull);
      return static_cast<T>(glm::clamp(std::round(field), 0.f, scale));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 64, FieldType::uint> {
   static F32 decode(T data) {
      return static_cast<F32>(data);
   }
   static T encode(F32 field) {
      F32 scale = static_cast<F32>(~U64(0));
      return static_cast<T>(glm::clamp(std::round(field), 0.f, scale));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits>
struct FieldRawNorm<T, Bits, FieldType::sint> {
   static_assert(Bits > 1);
   static F32 decode(T data) {
      return static_cast<F32>(signed_from_bits<T, Bits>(data));
   }
   static T encode(F32 field) {
      F32 scale = static_cast<F32>((1ull << (Bits - 1)) - 1ull);
      field = glm::clamp(std::round(field), -scale - 1, scale);
      if (field < 0) {
         field += static_cast<F32>(1ull << Bits);
      }
      return static_cast<T>(field);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 1, FieldType::sint> {
   static F32 decode(T data) {
      return static_cast<F32>(data);
   }
   static T encode(F32 field) {
      field = glm::clamp(std::round(field), 0.f, 1.f);
      return static_cast<T>(field);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 64, FieldType::sint> {
   static F32 decode(T data) {
      return static_cast<F32>(static_cast<I64>(data));
   }
   static T encode(F32 field) {
      F32 scale = static_cast<F32>((1ull << 63) - 1ull);
      field = glm::clamp(std::round(field), -scale - 1, scale);
      return static_cast<T>(static_cast<I64>(field));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits>
struct FieldRawNorm<T, Bits, FieldType::unorm> {
   static_assert(Bits > 0);
   static constexpr F32 scale = static_cast<F32>((1ull << Bits) - 1ull);
   static constexpr F32 invscale = 1.f / scale;
   static F32 decode(T data) {
      return static_cast<F32>(data) * invscale;
   }
   static T encode(F32 field) {
      return static_cast<T>(std::round(glm::clamp(field, 0.f, 1.f) * scale));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 64, FieldType::unorm> {
   static constexpr F32 scale = static_cast<F32>(~U64(0));
   static constexpr F32 invscale = 1.f / scale;
   static F32 decode(T data) {
      return static_cast<F32>(data) * invscale;
   }
   static T encode(F32 field) {
      return static_cast<T>(std::round(glm::clamp(field, 0.f, 1.f) * scale));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t Bits>
struct FieldRawNorm<T, Bits, FieldType::snorm> {
   static_assert(Bits > 1);
   static constexpr F32 scale = static_cast<F32>((1ull << (Bits - 1)) - 1ull);
   static constexpr F32 invscale = 1.f / scale;
   static F32 decode(T data) {
      return std::max(-scale, static_cast<F32>(signed_from_bits<T, Bits>(data))) * invscale;
   }
   static T encode(F32 field) {
      field = std::round(glm::clamp(field, -1.f, 1.f) * scale);
      if (field < 0) {
         field += static_cast<F32>(1ull << Bits);
      }
      return static_cast<T>(field);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 1, FieldType::snorm> {
   static F32 decode(T data) {
      return std::max(0.f, static_cast<F32>(data));
   }
   static T encode(F32 field) {
      field = std::round(glm::clamp(field, 0.f, 1.f));
      return static_cast<T>(field);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 64, FieldType::snorm> {
   static constexpr F32 scale = static_cast<F32>((1ull << 63) - 1ull);
   static constexpr F32 invscale = 1.f / scale;
   static F32 decode(T data) {
      return std::max(-scale, static_cast<F32>(static_cast<I64>(data))) * invscale;
   }
   static T encode(F32 field) {
      field = std::round(glm::clamp(field, -1.f, 1.f) * scale);
      return static_cast<T>(static_cast<I64>(field));
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 11, FieldType::ufloat> {
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

   static T encode(F32 field) {
      U16 f11_data;
      U32 f32_data;
      std::memcpy(&f32_data, &field, sizeof(U32));

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
struct FieldRawNorm<T, 10, FieldType::ufloat> {
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

   static T encode(F32 field) {
      U16 f10_data;
      U32 f32_data;
      std::memcpy(&f32_data, &field, sizeof(U32));

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
struct FieldRawNorm<T, 64, FieldType::sfloat> {
   static F32 decode(T data) {
      static_assert(sizeof(T) == 8);
      F64 float_data;
      std::memcpy(&float_data, &data, sizeof(F64));
      return static_cast<F32>(float_data);
   }
   static T encode(F32 field) {
      static_assert(sizeof(T) == 8);
      T data;
      F64 float_data = field;
      std::memcpy(&data, &float_data, sizeof(F64));
      return data;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 32, FieldType::sfloat> {
   static F32 decode(T data) {
      static_assert(sizeof(T) == 4);
      F32 float_data;
      std::memcpy(&float_data, &data, sizeof(F32));
      return float_data;
   }
   static T encode(F32 field) {
      static_assert(sizeof(T) == 4);
      T data;
      std::memcpy(&data, &field, sizeof(F32));
      return data;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct FieldRawNorm<T, 16, FieldType::sfloat> {
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

   static T encode(F32 field) {
      U16 f16_data;
      U32 f32_data;
      std::memcpy(&f32_data, &field, sizeof(U32));

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
F32 decode_field(UnsignedType data, FieldType type) {
   switch (type) {
      case FieldType::expo:
      case FieldType::uint:   return FieldRawNorm<UnsignedType, Bits, FieldType::uint>::decode(data);
      case FieldType::sint:   return FieldRawNorm<UnsignedType, Bits, FieldType::sint>::decode(data);
      case FieldType::unorm:  return FieldRawNorm<UnsignedType, Bits, FieldType::unorm>::decode(data);
      case FieldType::snorm:  return FieldRawNorm<UnsignedType, Bits, FieldType::snorm>::decode(data);
      case FieldType::ufloat: return FieldRawNorm<UnsignedType, Bits, FieldType::ufloat>::decode(data);
      case FieldType::sfloat: return FieldRawNorm<UnsignedType, Bits, FieldType::sfloat>::decode(data);
      default:                return FieldRawNorm<UnsignedType, Bits, FieldType::none>::decode(data);
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename UnsignedType, std::size_t Bits>
UnsignedType encode_field(F32 field, FieldType type) {
   switch (type) {
      case FieldType::expo:
      case FieldType::uint:   return FieldRawNorm<UnsignedType, Bits, FieldType::uint>::encode(field);
      case FieldType::sint:   return FieldRawNorm<UnsignedType, Bits, FieldType::sint>::encode(field);
      case FieldType::unorm:  return FieldRawNorm<UnsignedType, Bits, FieldType::unorm>::encode(field);
      case FieldType::snorm:  return FieldRawNorm<UnsignedType, Bits, FieldType::snorm>::encode(field);
      case FieldType::ufloat: return FieldRawNorm<UnsignedType, Bits, FieldType::ufloat>::encode(field);
      case FieldType::sfloat: return FieldRawNorm<UnsignedType, Bits, FieldType::sfloat>::encode(field);
      default:                return FieldRawNorm<UnsignedType, Bits, FieldType::none>::encode(field);
   }
}

#pragma region PixelRawNormAccessUncompressedNonPacked

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType>
struct PixelRawNormAccessUncompressedNonPacked {
   static constexpr glm::length_t fields = BlockPackingInfo<Packing>::fields;
   static constexpr std::size_t word_size_bits = BlockPackingInfo<Packing>::word_size * 8;

   using word_type = typename BlockPackingInfo<Packing>::unsigned_word_type;
   using data_type = glm::vec<fields, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      for (glm::length_t c = 0; c < fields; ++c) {
         pixel[c] = FieldRawNorm<word_type, word_size_bits, FieldType>::decode(data[c]);
      }
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      for (glm::length_t c = 0; c < fields; ++c) {
         data[c] = FieldRawNorm<word_type, word_size_bits, FieldType>::encode(pixel[c]);
      }
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedNonPacked<ImageView, Coord, IsSimple, Packing, FieldType::none> {
   static constexpr glm::length_t fields = BlockPackingInfo<Packing>::fields;
   static constexpr std::size_t word_size_bits = BlockPackingInfo<Packing>::word_size * 8;

   using word_type = typename BlockPackingInfo<Packing>::unsigned_word_type;
   using data_type = glm::vec<fields, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto field_types = image.format().field_types();
      for (glm::length_t c = 0; c < fields; ++c) {
         pixel[c] = decode_field<word_type, word_size_bits>(data[c], field_types[c]);
      }
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto field_types = image.format().field_types();
      for (glm::length_t c = 0; c < fields; ++c) {
         data[c] = encode_field<word_type, word_size_bits>(pixel[c], field_types[c]);
      }
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }
};

#pragma endregion
#pragma region PixelRawNormAccessUncompressedPacked

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType, U8 Fields = BlockPackingInfo<Packing>::fields>
struct PixelRawNormAccessUncompressedPacked { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType, 1> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      pixel[0] = FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType>::decode((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::field_word_offset[0]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType>::encode(pixel[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType::none, 1> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto field_types = image.format().field_types();
      pixel[0] = decode_field<word_type, packing_info::field_bit_width[0]>((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]), field_types[0]);
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto field_types = image.format().field_types();
      data[packing_info::field_word_offset[0]] |= (encode_field<word_type, packing_info::field_bit_width[0]>(pixel[0], field_types[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType, 2> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      pixel[0] = FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType>::decode((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]));
      pixel[1] = FieldRawNorm<word_type, packing_info::field_bit_width[1], FieldType>::decode((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::field_word_offset[0]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType>::encode(pixel[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
      data[packing_info::field_word_offset[1]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[1], FieldType>::encode(pixel[1]) & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType::none, 2> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto field_types = image.format().field_types();
      pixel[0] = decode_field<word_type, packing_info::field_bit_width[0]>((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]), field_types[0]);
      pixel[1] = decode_field<word_type, packing_info::field_bit_width[1]>((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]), field_types[1]);
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto field_types = image.format().field_types();
      data[packing_info::field_word_offset[0]] |= (encode_field<word_type, packing_info::field_bit_width[0]>(pixel[0], field_types[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
      data[packing_info::field_word_offset[1]] |= (encode_field<word_type, packing_info::field_bit_width[1]>(pixel[1], field_types[1]) & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType, 3> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      pixel[0] = FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType>::decode((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]));
      pixel[1] = FieldRawNorm<word_type, packing_info::field_bit_width[1], FieldType>::decode((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]));
      pixel[2] = FieldRawNorm<word_type, packing_info::field_bit_width[2], FieldType>::decode((data[packing_info::field_word_offset[2]] >> packing_info::field_bit_offset[2]) & low_mask(packing_info::field_bit_width[2]));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::field_word_offset[0]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType>::encode(pixel[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
      data[packing_info::field_word_offset[1]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[1], FieldType>::encode(pixel[1]) & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
      data[packing_info::field_word_offset[2]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[2], FieldType>::encode(pixel[2]) & low_mask(packing_info::field_bit_width[2])) << packing_info::field_bit_offset[2];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType::none, 3> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto field_types = image.format().field_types();
      pixel[0] = decode_field<word_type, packing_info::field_bit_width[0]>((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]), field_types[0]);
      pixel[1] = decode_field<word_type, packing_info::field_bit_width[1]>((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]), field_types[1]);
      pixel[2] = decode_field<word_type, packing_info::field_bit_width[2]>((data[packing_info::field_word_offset[2]] >> packing_info::field_bit_offset[2]) & low_mask(packing_info::field_bit_width[2]), field_types[2]);
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto field_types = image.format().field_types();
      data[packing_info::field_word_offset[0]] |= (encode_field<word_type, packing_info::field_bit_width[0]>(pixel[0], field_types[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
      data[packing_info::field_word_offset[1]] |= (encode_field<word_type, packing_info::field_bit_width[1]>(pixel[1], field_types[1]) & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
      data[packing_info::field_word_offset[2]] |= (encode_field<word_type, packing_info::field_bit_width[2]>(pixel[2], field_types[2]) & low_mask(packing_info::field_bit_width[2])) << packing_info::field_bit_offset[2];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType, 4> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      pixel[0] = FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType>::decode((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]));
      pixel[1] = FieldRawNorm<word_type, packing_info::field_bit_width[1], FieldType>::decode((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]));
      pixel[2] = FieldRawNorm<word_type, packing_info::field_bit_width[2], FieldType>::decode((data[packing_info::field_word_offset[2]] >> packing_info::field_bit_offset[2]) & low_mask(packing_info::field_bit_width[2]));
      pixel[3] = FieldRawNorm<word_type, packing_info::field_bit_width[3], FieldType>::decode((data[packing_info::field_word_offset[3]] >> packing_info::field_bit_offset[3]) & low_mask(packing_info::field_bit_width[3]));
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      data[packing_info::field_word_offset[0]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType>::encode(pixel[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
      data[packing_info::field_word_offset[1]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[1], FieldType>::encode(pixel[1]) & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
      data[packing_info::field_word_offset[2]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[2], FieldType>::encode(pixel[2]) & low_mask(packing_info::field_bit_width[2])) << packing_info::field_bit_offset[2];
      data[packing_info::field_word_offset[3]] |= (FieldRawNorm<word_type, packing_info::field_bit_width[3], FieldType>::encode(pixel[3]) & low_mask(packing_info::field_bit_width[3])) << packing_info::field_bit_offset[3];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType::none, 4> {
   using packing_info = BlockPackingInfo<Packing>;
   using word_type = typename packing_info::unsigned_word_type;
   using data_type = glm::vec<packing_info::words, word_type>;

   static vec4 get(const ImageView& image, Coord pixel_coord) {
      vec4 pixel;
      data_type data = get_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord);
      const auto field_types = image.format().field_types();
      pixel[0] = decode_field<word_type, packing_info::field_bit_width[0]>((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]), field_types[0]);
      pixel[1] = decode_field<word_type, packing_info::field_bit_width[1]>((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]), field_types[1]);
      pixel[2] = decode_field<word_type, packing_info::field_bit_width[2]>((data[packing_info::field_word_offset[2]] >> packing_info::field_bit_offset[2]) & low_mask(packing_info::field_bit_width[2]), field_types[2]);
      pixel[3] = decode_field<word_type, packing_info::field_bit_width[3]>((data[packing_info::field_word_offset[3]] >> packing_info::field_bit_offset[3]) & low_mask(packing_info::field_bit_width[3]), field_types[3]);
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto field_types = image.format().field_types();
      data[packing_info::field_word_offset[0]] |= (encode_field<word_type, packing_info::field_bit_width[0]>(pixel[0], field_types[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
      data[packing_info::field_word_offset[1]] |= (encode_field<word_type, packing_info::field_bit_width[1]>(pixel[1], field_types[1]) & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
      data[packing_info::field_word_offset[2]] |= (encode_field<word_type, packing_info::field_bit_width[2]>(pixel[2], field_types[2]) & low_mask(packing_info::field_bit_width[2])) << packing_info::field_bit_offset[2];
      data[packing_info::field_word_offset[3]] |= (encode_field<word_type, packing_info::field_bit_width[3]>(pixel[3], field_types[3]) & low_mask(packing_info::field_bit_width[3])) << packing_info::field_bit_offset[3];
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, BlockPacking::p_9_9_9_5, FieldType::none, 4> {
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
      const auto field_types = image.format().field_types();
      if (field_types == ImageFormat::field_types_type(FieldType::ufloat, FieldType::ufloat, FieldType::ufloat, FieldType::expo)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         vec3 pixel3;
         pixel3[0] = FieldRawNorm<word_type, packing_info::field_bit_width[0], FieldType::uint>::decode((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]));
         pixel3[1] = FieldRawNorm<word_type, packing_info::field_bit_width[1], FieldType::uint>::decode((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]));
         pixel3[2] = FieldRawNorm<word_type, packing_info::field_bit_width[2], FieldType::uint>::decode((data[packing_info::field_word_offset[2]] >> packing_info::field_bit_offset[2]) & low_mask(packing_info::field_bit_width[2]));

         word_type exponent = (data[packing_info::field_word_offset[3]] >> packing_info::field_bit_offset[3]) & low_mask(packing_info::field_bit_width[3]);
         pixel3 *= pow2(exponent - f14_exponent_basis - f14_mantissa_bits);
         pixel = vec4(pixel3, 0.f);
      } else {
         pixel[0] = decode_field<word_type, packing_info::field_bit_width[0]>((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]), field_types[0]);
         pixel[1] = decode_field<word_type, packing_info::field_bit_width[1]>((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]), field_types[1]);
         pixel[2] = decode_field<word_type, packing_info::field_bit_width[2]>((data[packing_info::field_word_offset[2]] >> packing_info::field_bit_offset[2]) & low_mask(packing_info::field_bit_width[2]), field_types[2]);
         pixel[3] = decode_field<word_type, packing_info::field_bit_width[3]>((data[packing_info::field_word_offset[3]] >> packing_info::field_bit_offset[3]) & low_mask(packing_info::field_bit_width[3]), field_types[3]);
      }
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto field_types = image.format().field_types();
      if (field_types == ImageFormat::field_types_type(FieldType::ufloat, FieldType::ufloat, FieldType::ufloat, FieldType::expo)) {
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

         uvec3 comp_fields(color * mult + 0.5f);

         assert(comp_fields[0] >= 0);
         assert(comp_fields[1] >= 0);
         assert(comp_fields[2] >= 0);
         assert(comp_fields[0] <= f14_mantissa_mask);
         assert(comp_fields[1] <= f14_mantissa_mask);
         assert(comp_fields[2] <= f14_mantissa_mask);

         data[packing_info::field_word_offset[0]] |= (comp_fields[0] & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
         data[packing_info::field_word_offset[1]] |= (comp_fields[1] & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
         data[packing_info::field_word_offset[2]] |= (comp_fields[2] & low_mask(packing_info::field_bit_width[2])) << packing_info::field_bit_offset[2];
         data[packing_info::field_word_offset[3]] |= (static_cast<unsigned int>(exp_shared) & low_mask(packing_info::field_bit_width[3])) << packing_info::field_bit_offset[3];
      } else {
         data[packing_info::field_word_offset[0]] |= (encode_field<word_type, packing_info::field_bit_width[0]>(pixel[0], field_types[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
         data[packing_info::field_word_offset[1]] |= (encode_field<word_type, packing_info::field_bit_width[1]>(pixel[1], field_types[1]) & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
         data[packing_info::field_word_offset[2]] |= (encode_field<word_type, packing_info::field_bit_width[2]>(pixel[2], field_types[2]) & low_mask(packing_info::field_bit_width[2])) << packing_info::field_bit_offset[2];
         data[packing_info::field_word_offset[3]] |= (encode_field<word_type, packing_info::field_bit_width[3]>(pixel[3], field_types[3]) & low_mask(packing_info::field_bit_width[3])) << packing_info::field_bit_offset[3];
      }
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple>
struct PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, BlockPacking::p_5_9_9_9, FieldType::none, 4> {
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
      const auto field_types = image.format().field_types();
      if (field_types == ImageFormat::field_types_type(FieldType::expo, FieldType::ufloat, FieldType::ufloat, FieldType::ufloat)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         vec3 pixel3;
         pixel3[0] = FieldRawNorm<word_type, packing_info::field_bit_width[1], FieldType::uint>::decode((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]));
         pixel3[1] = FieldRawNorm<word_type, packing_info::field_bit_width[2], FieldType::uint>::decode((data[packing_info::field_word_offset[2]] >> packing_info::field_bit_offset[2]) & low_mask(packing_info::field_bit_width[2]));
         pixel3[2] = FieldRawNorm<word_type, packing_info::field_bit_width[3], FieldType::uint>::decode((data[packing_info::field_word_offset[3]] >> packing_info::field_bit_offset[3]) & low_mask(packing_info::field_bit_width[3]));

         word_type exponent = (data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]);
         pixel3 *= pow2(exponent - f14_exponent_basis - f14_mantissa_bits);
         pixel = vec4(0.f, pixel3);
      } else {
         pixel[0] = decode_field<word_type, packing_info::field_bit_width[0]>((data[packing_info::field_word_offset[0]] >> packing_info::field_bit_offset[0]) & low_mask(packing_info::field_bit_width[0]), field_types[0]);
         pixel[1] = decode_field<word_type, packing_info::field_bit_width[1]>((data[packing_info::field_word_offset[1]] >> packing_info::field_bit_offset[1]) & low_mask(packing_info::field_bit_width[1]), field_types[1]);
         pixel[2] = decode_field<word_type, packing_info::field_bit_width[2]>((data[packing_info::field_word_offset[2]] >> packing_info::field_bit_offset[2]) & low_mask(packing_info::field_bit_width[2]), field_types[2]);
         pixel[3] = decode_field<word_type, packing_info::field_bit_width[3]>((data[packing_info::field_word_offset[3]] >> packing_info::field_bit_offset[3]) & low_mask(packing_info::field_bit_width[3]), field_types[3]);
      }
      return pixel;
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      data_type data;
      const auto field_types = image.format().field_types();
      if (field_types == ImageFormat::field_types_type(FieldType::expo, FieldType::ufloat, FieldType::ufloat, FieldType::ufloat)) {
         // https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_shared_exponent.txt
         constexpr F32 limit = (F32)f14_mantissa_mask * (1 << (f14_exponent_max - f14_exponent_basis - f14_mantissa_bits));
         vec3 color = glm::clamp(vec3(pixel.g, pixel.b, pixel.a), 0.f, limit); // nan -> 0, inf -> limit
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

         uvec3 comp_fields(color * mult + 0.5f);

         assert(comp_fields[0] >= 0);
         assert(comp_fields[1] >= 0);
         assert(comp_fields[2] >= 0);
         assert(comp_fields[0] <= f14_mantissa_mask);
         assert(comp_fields[1] <= f14_mantissa_mask);
         assert(comp_fields[2] <= f14_mantissa_mask);

         data[packing_info::field_word_offset[0]] |= (static_cast<unsigned int>(exp_shared) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
         data[packing_info::field_word_offset[1]] |= (comp_fields[0] & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
         data[packing_info::field_word_offset[2]] |= (comp_fields[1] & low_mask(packing_info::field_bit_width[2])) << packing_info::field_bit_offset[2];
         data[packing_info::field_word_offset[3]] |= (comp_fields[2] & low_mask(packing_info::field_bit_width[3])) << packing_info::field_bit_offset[3];
      } else {
         data[packing_info::field_word_offset[0]] |= (encode_field<word_type, packing_info::field_bit_width[0]>(pixel[0], field_types[0]) & low_mask(packing_info::field_bit_width[0])) << packing_info::field_bit_offset[0];
         data[packing_info::field_word_offset[1]] |= (encode_field<word_type, packing_info::field_bit_width[1]>(pixel[1], field_types[1]) & low_mask(packing_info::field_bit_width[1])) << packing_info::field_bit_offset[1];
         data[packing_info::field_word_offset[2]] |= (encode_field<word_type, packing_info::field_bit_width[2]>(pixel[2], field_types[2]) & low_mask(packing_info::field_bit_width[2])) << packing_info::field_bit_offset[2];
         data[packing_info::field_word_offset[3]] |= (encode_field<word_type, packing_info::field_bit_width[3]>(pixel[3], field_types[3]) & low_mask(packing_info::field_bit_width[3])) << packing_info::field_bit_offset[3];
      }
      put_pixel_uncompressed<data_type, Coord, ImageView, IsSimple>(image, pixel_coord, data);
   }

private:
   static constexpr word_type low_mask(U8 bits) noexcept {
      return static_cast<word_type>((1ull << bits) - 1ull);
   }
};

#pragma endregion
#pragma region PixelRawNormAccessUncompressed

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType, bool IsPacked = BlockPackingInfo<Packing>::is_packed::value>
struct PixelRawNormAccessUncompressed { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType>
struct PixelRawNormAccessUncompressed<ImageView, Coord, IsSimple, Packing, FieldType, false>
   : PixelRawNormAccessUncompressedNonPacked<ImageView, Coord, IsSimple, Packing, FieldType> { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType>
struct PixelRawNormAccessUncompressed<ImageView, Coord, IsSimple, Packing, FieldType, true>
   : PixelRawNormAccessUncompressedPacked<ImageView, Coord, IsSimple, Packing, FieldType> { };

#pragma endregion
#pragma region PixelNormAccessUncompressed

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, bool IsSimple, BlockPacking Packing, FieldType FieldType = FieldType::none>
struct PixelNormAccessUncompressed {
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      F32 data[6] = { 0.f, 0.f, 0.f, 0.f, 0.f, 1.f };
      const vec4 raw = PixelRawNormAccessUncompressed<ImageView, Coord, IsSimple, Packing, FieldType>::get(image, pixel_coord);
      std::memcpy(data, glm::value_ptr(raw), sizeof(vec4));
      const auto swizzles = image.format().swizzles();
      return vec4(data[static_cast<U8>(swizzles.r)],
                  data[static_cast<U8>(swizzles.g)],
                  data[static_cast<U8>(swizzles.b)],
                  data[static_cast<U8>(swizzles.a)]);
   }

   static void put(ImageView& image, Coord pixel_coord, vec4 pixel) {
      vec4 unswizzled_pixel;
      const auto swizzles = image.format().swizzles();
      for (glm::length_t c = 3; c >= 0; --c) {
         U8 swizzle = static_cast<U8>(swizzles[c]);
         if (swizzle < 4) {
            unswizzled_pixel[swizzle] = pixel[c];
         }
      }
      PixelRawNormAccessUncompressed<ImageView, Coord, IsSimple, Packing, FieldType>::put(image, pixel_coord, unswizzled_pixel);
   }
};

#pragma endregion
#pragma region ASTC

// TODO

#pragma endregion
#pragma region BPTC

///////////////////////////////////////////////////////////////////////////////
struct BptcBlock {
   U8 data[16];
};

enum class BptcRotation {
   none = 0,
   swap_ra = 1,
   swap_ga = 2,
   swap_ba = 3
};

///////////////////////////////////////////////////////////////////////////////
struct BptcUnormFields {
   U8 n_subsets = 1;
   U8 partition = 0;
   BptcRotation rotation = BptcRotation::none;
   vec4 endpoints[6] = {
      vec4(0, 0, 0, 1),
      vec4(0, 0, 0, 1),
      vec4(0, 0, 0, 1),
      vec4(0, 0, 0, 1),
      vec4(0, 0, 0, 1),
      vec4(0, 0, 0, 1),
   };
   U64 color_index_data = 0;
   U64 alpha_index_data = 0;
   U8 color_index_bpp = 2;
   U8 alpha_index_bpp = 2;
};

///////////////////////////////////////////////////////////////////////////////
struct BptcFloatFields {
   U8 n_subsets = 1;
   U8 partition = 0;
   U16 r0 = 0, g0 = 0, b0 = 0;
   U16 r1 = 0, g1 = 0, b1 = 0;
   U16 r2 = 0, g2 = 0, b2 = 0;
   U16 r3 = 0, g3 = 0, b3 = 0;
   U64 index_data = 0;
   U8 index_bpp = 3;
};

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
BptcBlock get_bptc_block(const ImageView& image, Coord block_coord) {
   BptcBlock block;
   const void* ptr = image.data() + BlockOffset<ImageView, Coord>::offset(image, block_coord);
   std::memcpy(&block, ptr, sizeof(block));
   return block;
}

///////////////////////////////////////////////////////////////////////////////
inline BptcUnormFields decode_bptc_unorm_fields(BptcBlock block) {
   BptcUnormFields f;

   constexpr U8 anchor2_1[64] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 2, 8, 2, 2, 8, 8,15, 2, 8, 2, 2, 8, 8, 2, 2,15,15, 6, 8, 2, 8,15,15, 2, 8, 2, 2, 2,15,15, 6, 6, 2, 6, 8,15,15, 2, 2,15,15,15,15,15, 2, 2,15 };
   constexpr U8 anchor3_1[64] = { 3, 3, 8, 3, 8, 3, 3, 8, 8, 8, 6, 6, 6, 5, 3, 3, 3, 3, 8, 3, 3, 3, 6, 8, 3, 8, 6, 6, 8, 5,10, 8, 8, 3, 3, 5, 6, 8, 8,10, 6, 3, 8, 5, 3, 6, 6, 8, 3, 3, 5, 5, 5, 8, 5,10, 5,10, 8,13, 3,12, 3, 3 };
   constexpr U8 anchor3_2[64] = {15, 8,15,15,15,15,15,15,15,15,15,15,15,15,15, 8,15, 8,15,15,15, 8,15,10, 5,15, 8,10,15,15,15,15,15,15,15,10,10,10, 9,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 8 };

   if (0 != (block.data[0] & 0x01)) {
      /////////////////////////////////////////////////////////////////////////
      // Mode 0
      f.n_subsets = 3;

      /*!! include 'tex/bptc'
      decode_bptc_u8  { bits = 4, begin = 1, dest = 'f.partition' }
      decode_bptc_rgb { bits = 4, count = 6 }
      decode_bptc_p   { pad_bits = 3, count = 6 }
      decode_bptc_u64 { bits = 45, dest = 'f.color_index_data' }
      !! 44 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.partition = U8((block.data[0] >> 1) & 0xfu);
      U8 r[6] = {
         U8(((block.data[0] >> 5) | (block.data[1] << 3)) & 0xfu),
         U8((block.data[1] >> 1) & 0xfu),
         U8(((block.data[1] >> 5) | (block.data[2] << 3)) & 0xfu),
         U8((block.data[2] >> 1) & 0xfu),
         U8(((block.data[2] >> 5) | (block.data[3] << 3)) & 0xfu),
         U8((block.data[3] >> 1) & 0xfu)
      };
      U8 g[6] = {
         U8(((block.data[3] >> 5) | (block.data[4] << 3)) & 0xfu),
         U8((block.data[4] >> 1) & 0xfu),
         U8(((block.data[4] >> 5) | (block.data[5] << 3)) & 0xfu),
         U8((block.data[5] >> 1) & 0xfu),
         U8(((block.data[5] >> 5) | (block.data[6] << 3)) & 0xfu),
         U8((block.data[6] >> 1) & 0xfu)
      };
      U8 b[6] = {
         U8(((block.data[6] >> 5) | (block.data[7] << 3)) & 0xfu),
         U8((block.data[7] >> 1) & 0xfu),
         U8(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu),
         U8((block.data[8] >> 1) & 0xfu),
         U8(((block.data[8] >> 5) | (block.data[9] << 3)) & 0xfu),
         U8((block.data[9] >> 1) & 0xfu)
      };
      U8 p[6] = {
         U8((block.data[9] >> 2) & 0x8u),
         U8((block.data[9] >> 3) & 0x8u),
         U8((block.data[9] >> 4) & 0x8u),
         U8((block.data[10] << 3) & 0x8u),
         U8((block.data[10] << 2) & 0x8u),
         U8((block.data[10] << 1) & 0x8u)
      };
      f.color_index_data = U64((
         (U64(block.data[10]) >> 3) |
         (U64(block.data[11]) << 5) |
         (U64(block.data[12]) << 13) |
         (U64(block.data[13]) << 21) |
         (U64(block.data[14]) << 29) |
         (U64(block.data[15]) << 37)) & 0x1fffffffffffull);

      /* ######################### END OF GENERATED CODE ######################### */

      for (glm::length_t e = 0; e < 6; ++e) {
         f.endpoints[e].r = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((r[e] << 4) | p[e] | (r[e] >> 1)));
         f.endpoints[e].g = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((g[e] << 4) | p[e] | (g[e] >> 1)));
         f.endpoints[e].b = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((b[e] << 4) | p[e] | (b[e] >> 1)));
      }

      constexpr U8 bpi = 3;
      const U8 anchor0 = 0;
      const U8 anchor1 = anchor3_1[f.partition];
      const U8 anchor2 = anchor3_2[f.partition];

      const U64 mask0 = (1ull << ((anchor0 + 1) * bpi - 1)) - 1;
      const U64 mask1 = (1ull << ((anchor1 + 1) * bpi - 2)) - 1;
      const U64 mask2 = (1ull << ((anchor2 + 1) * bpi - 3)) - 1;

      f.color_index_data = (f.color_index_data & mask0) |
         ((f.color_index_data & (mask1 & ~mask0)) << 1) |
         ((f.color_index_data & (mask2 & ~mask1)) << 2) |
         ((f.color_index_data & ~mask2) << 3);

      f.alpha_index_data = f.color_index_data;

      f.color_index_bpp = bpi;
      f.alpha_index_bpp = bpi;

   } else if (0 != (block.data[0] & 0x02)) {
      /////////////////////////////////////////////////////////////////////////
      // Mode 1
      f.n_subsets = 2;

      /*!!
      decode_bptc_u8  { bits = 6, begin = 2, dest = 'f.partition' }
      decode_bptc_rgb { bits = 6, count = 4 }
      decode_bptc_p   { pad_bits = 1, count = 2, array_size = 4 }
      decode_bptc_u64 { bits = 46, dest = 'f.color_index_data' }
      !! 36 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.partition = U8((block.data[0] >> 2) & 0x3fu);
      U8 r[4] = {
         U8(block.data[1] & 0x3fu),
         U8(((block.data[1] >> 6) | (block.data[2] << 2)) & 0x3fu),
         U8(((block.data[2] >> 4) | (block.data[3] << 4)) & 0x3fu),
         U8((block.data[3] >> 2) & 0x3fu)
      };
      U8 g[4] = {
         U8(block.data[4] & 0x3fu),
         U8(((block.data[4] >> 6) | (block.data[5] << 2)) & 0x3fu),
         U8(((block.data[5] >> 4) | (block.data[6] << 4)) & 0x3fu),
         U8((block.data[6] >> 2) & 0x3fu)
      };
      U8 b[4] = {
         U8(block.data[7] & 0x3fu),
         U8(((block.data[7] >> 6) | (block.data[8] << 2)) & 0x3fu),
         U8(((block.data[8] >> 4) | (block.data[9] << 4)) & 0x3fu),
         U8((block.data[9] >> 2) & 0x3fu)
      };
      U8 p[4] = {
         U8((block.data[10] << 1) & 0x2u),
         U8(block.data[10] & 0x2u)
      };
      p[2] = p[0];
      p[3] = p[1];
      f.color_index_data = U64((
         (U64(block.data[10]) >> 2) |
         (U64(block.data[11]) << 6) |
         (U64(block.data[12]) << 14) |
         (U64(block.data[13]) << 22) |
         (U64(block.data[14]) << 30) |
         (U64(block.data[15]) << 38)) & 0x3fffffffffffull);

      /* ######################### END OF GENERATED CODE ######################### */

      for (glm::length_t e = 0; e < 4; ++e) {
         f.endpoints[e].r = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((r[e] << 2) | p[e] | (r[e] >> 5)));
         f.endpoints[e].g = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((g[e] << 2) | p[e] | (g[e] >> 5)));
         f.endpoints[e].b = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((b[e] << 2) | p[e] | (b[e] >> 5)));
      }

      constexpr U8 bpi = 3;
      const U8 anchor0 = 0;
      const U8 anchor1 = anchor2_1[f.partition];

      const U64 mask0 = (1ull << ((anchor0 + 1) * bpi - 1)) - 1;
      const U64 mask1 = (1ull << ((anchor1 + 1) * bpi - 2)) - 1;

      f.color_index_data = (f.color_index_data & mask0) |
         ((f.color_index_data & (mask1 & ~mask0)) << 1) |
         ((f.color_index_data & ~mask1) << 2);

      f.alpha_index_data = f.color_index_data;

      f.color_index_bpp = bpi;
      f.alpha_index_bpp = bpi;

   } else if (0 != (block.data[0] & 0x04)) {
      /////////////////////////////////////////////////////////////////////////
      // Mode 2
      f.n_subsets = 3;

      /*!!
      decode_bptc_u8  { bits = 6, begin = 3, dest = 'f.partition' }
      decode_bptc_rgb { bits = 5, count = 6 }
      decode_bptc_u64 { bits = 29, dest = 'f.color_index_data' }
      !! 34 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.partition = U8(((block.data[0] >> 3) | (block.data[1] << 5)) & 0x3fu);
      U8 r[6] = {
         U8((block.data[1] >> 1) & 0x1fu),
         U8(((block.data[1] >> 6) | (block.data[2] << 2)) & 0x1fu),
         U8((block.data[2] >> 3) & 0x1fu),
         U8(block.data[3] & 0x1fu),
         U8(((block.data[3] >> 5) | (block.data[4] << 3)) & 0x1fu),
         U8((block.data[4] >> 2) & 0x1fu)
      };
      U8 g[6] = {
         U8(((block.data[4] >> 7) | (block.data[5] << 1)) & 0x1fu),
         U8(((block.data[5] >> 4) | (block.data[6] << 4)) & 0x1fu),
         U8((block.data[6] >> 1) & 0x1fu),
         U8(((block.data[6] >> 6) | (block.data[7] << 2)) & 0x1fu),
         U8((block.data[7] >> 3) & 0x1fu),
         U8(block.data[8] & 0x1fu)
      };
      U8 b[6] = {
         U8(((block.data[8] >> 5) | (block.data[9] << 3)) & 0x1fu),
         U8((block.data[9] >> 2) & 0x1fu),
         U8(((block.data[9] >> 7) | (block.data[10] << 1)) & 0x1fu),
         U8(((block.data[10] >> 4) | (block.data[11] << 4)) & 0x1fu),
         U8((block.data[11] >> 1) & 0x1fu),
         U8(((block.data[11] >> 6) | (block.data[12] << 2)) & 0x1fu)
      };
      f.color_index_data = U64((
         (block.data[12] >> 3) |
         (block.data[13] << 5) |
         (block.data[14] << 13) |
         (block.data[15] << 21)) & 0x1fffffffu);

      /* ######################### END OF GENERATED CODE ######################### */

      for (glm::length_t e = 0; e < 6; ++e) {
         f.endpoints[e].r = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((r[e] << 3) | (r[e] >> 2)));
         f.endpoints[e].g = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((g[e] << 3) | (g[e] >> 2)));
         f.endpoints[e].b = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((b[e] << 3) | (b[e] >> 2)));
      }

      constexpr U8 bpi = 2;
      const U8 anchor0 = 0;
      const U8 anchor1 = anchor3_1[f.partition];
      const U8 anchor2 = anchor3_2[f.partition];

      const U64 mask0 = (1ull << ((anchor0 + 1) * bpi - 1)) - 1;
      const U64 mask1 = (1ull << ((anchor1 + 1) * bpi - 2)) - 1;
      const U64 mask2 = (1ull << ((anchor2 + 1) * bpi - 3)) - 1;

      f.color_index_data = (f.color_index_data & mask0) |
         ((f.color_index_data & (mask1 & ~mask0)) << 1) |
         ((f.color_index_data & (mask2 & ~mask1)) << 2) |
         ((f.color_index_data & ~mask2) << 3);

      f.alpha_index_data = f.color_index_data;

      f.color_index_bpp = bpi;
      f.alpha_index_bpp = bpi;

   } else if (0 != (block.data[0] & 0x08)) {
      /////////////////////////////////////////////////////////////////////////
      // Mode 3
      f.n_subsets = 2;

      /*!!
      decode_bptc_u8  { bits = 6, begin = 4, dest = 'f.partition' }
      decode_bptc_rgb { bits = 7, count = 4 }
      decode_bptc_p   { count = 4 }
      decode_bptc_u64 { bits = 30, dest = 'f.color_index_data' }
      !! 34 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.partition = U8(((block.data[0] >> 4) | (block.data[1] << 4)) & 0x3fu);
      U8 r[4] = {
         U8(((block.data[1] >> 2) | (block.data[2] << 6)) & 0x7fu),
         U8((block.data[2] >> 1) & 0x7fu),
         U8(block.data[3] & 0x7fu),
         U8(((block.data[3] >> 7) | (block.data[4] << 1)) & 0x7fu)
      };
      U8 g[4] = {
         U8(((block.data[4] >> 6) | (block.data[5] << 2)) & 0x7fu),
         U8(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x7fu),
         U8(((block.data[6] >> 4) | (block.data[7] << 4)) & 0x7fu),
         U8(((block.data[7] >> 3) | (block.data[8] << 5)) & 0x7fu)
      };
      U8 b[4] = {
         U8(((block.data[8] >> 2) | (block.data[9] << 6)) & 0x7fu),
         U8((block.data[9] >> 1) & 0x7fu),
         U8(block.data[10] & 0x7fu),
         U8(((block.data[10] >> 7) | (block.data[11] << 1)) & 0x7fu)
      };
      U8 p[4] = {
         U8((block.data[11] >> 6) & 0x1u),
         U8((block.data[11] >> 7) & 0x1u),
         U8(block.data[12] & 0x1u),
         U8((block.data[12] >> 1) & 0x1u)
      };
      f.color_index_data = U64((
         (block.data[12] >> 2) |
         (block.data[13] << 6) |
         (block.data[14] << 14) |
         (block.data[15] << 22)) & 0x3fffffffu);

      /* ######################### END OF GENERATED CODE ######################### */

      for (glm::length_t e = 0; e < 4; ++e) {
         f.endpoints[e].r = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((r[e] << 1) | p[e]));
         f.endpoints[e].g = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((g[e] << 1) | p[e]));
         f.endpoints[e].b = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((b[e] << 1) | p[e]));
      }

      constexpr U8 bpi = 2;
      const U8 anchor0 = 0;
      const U8 anchor1 = anchor2_1[f.partition];

      const U64 mask0 = (1ull << ((anchor0 + 1) * bpi - 1)) - 1;
      const U64 mask1 = (1ull << ((anchor1 + 1) * bpi - 2)) - 1;

      f.color_index_data = (f.color_index_data & mask0) |
         ((f.color_index_data & (mask1 & ~mask0)) << 1) |
         ((f.color_index_data & ~mask1) << 2);

      f.alpha_index_data = f.color_index_data;

      f.color_index_bpp = bpi;
      f.alpha_index_bpp = bpi;

   } else if (0 != (block.data[0] & 0x10)) {
      /////////////////////////////////////////////////////////////////////////
      // Mode 4
      f.n_subsets = 1;

      /*!!
      decode_bptc     { bits = 2, begin = 5, typename = 'BptcRotation', dest = 'f.rotation' }
      decode_bptc_u8  { bits = 1, dest = 'index_selection', declare = true }
      decode_bptc_rgb { bits = 5, count = 2 }
      decode_bptc_a   { bits = 6, count = 2 }
      decode_bptc_u64 { bits = 31, dest = 'primary_index_data', declare = true }
      decode_bptc_u64 { bits = 47, dest = 'secondary_index_data', declare = true }
      !! 35 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.rotation = BptcRotation((block.data[0] >> 5) & 0x3u);
      U8 index_selection = U8((block.data[0] >> 7) & 0x1u);
      U8 r[2] = {
         U8(block.data[1] & 0x1fu),
         U8(((block.data[1] >> 5) | (block.data[2] << 3)) & 0x1fu)
      };
      U8 g[2] = {
         U8((block.data[2] >> 2) & 0x1fu),
         U8(((block.data[2] >> 7) | (block.data[3] << 1)) & 0x1fu)
      };
      U8 b[2] = {
         U8(((block.data[3] >> 4) | (block.data[4] << 4)) & 0x1fu),
         U8((block.data[4] >> 1) & 0x1fu)
      };
      U8 a[2] = {
         U8(((block.data[4] >> 6) | (block.data[5] << 2)) & 0x3fu),
         U8(((block.data[5] >> 4) | (block.data[6] << 4)) & 0x3fu)
      };
      U64 primary_index_data = U64((
         (block.data[6] >> 2) |
         (block.data[7] << 6) |
         (block.data[8] << 14) |
         (block.data[9] << 22) |
         (block.data[10] << 30)) & 0x7fffffffu);
      U64 secondary_index_data = U64((
         (U64(block.data[10]) >> 1) |
         (U64(block.data[11]) << 7) |
         (U64(block.data[12]) << 15) |
         (U64(block.data[13]) << 23) |
         (U64(block.data[14]) << 31) |
         (U64(block.data[15]) << 39)) & 0x7fffffffffffull);

      /* ######################### END OF GENERATED CODE ######################### */

      for (glm::length_t e = 0; e < 2; ++e) {
         f.endpoints[e].r = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((r[e] << 3) | (r[e] >> 2)));
         f.endpoints[e].g = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((g[e] << 3) | (g[e] >> 2)));
         f.endpoints[e].b = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((b[e] << 3) | (b[e] >> 2)));
         f.endpoints[e].a = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((a[e] << 2) | (a[e] >> 4)));
      }

      constexpr U8 primary_bpi = 2;
      constexpr U8 secondary_bpi = 3;
      const U8 anchor = 0;

      const U64 primary_mask = (1ull << ((anchor + 1) * primary_bpi - 1)) - 1;
      const U64 secondary_mask = (1ull << ((anchor + 1) * secondary_bpi - 1)) - 1;

      primary_index_data = (primary_index_data & primary_mask) |
         ((primary_index_data & ~primary_mask) << 1);

      secondary_index_data = (secondary_index_data & secondary_mask) |
         ((secondary_index_data & ~secondary_mask) << 1);

      if (index_selection == 0) {
         f.color_index_data = primary_index_data;
         f.color_index_bpp = primary_bpi;
         f.alpha_index_data = secondary_index_data;
         f.alpha_index_bpp = secondary_bpi;
      } else {
         f.alpha_index_data = primary_index_data;
         f.alpha_index_bpp = primary_bpi;
         f.color_index_data = secondary_index_data;
         f.color_index_bpp = secondary_bpi;
      }

   } else if (0 != (block.data[0] & 0x20)) {
      /////////////////////////////////////////////////////////////////////////
      // Mode 5
      f.n_subsets = 1;

      /*!!
      decode_bptc     { bits = 2, begin = 6, typename = 'BptcRotation', dest = 'f.rotation' }
      decode_bptc_rgb { bits = 7, count = 2 }
      decode_bptc_a   { bits = 8, count = 2 }
      decode_bptc_u64 { bits = 31, dest = 'primary_index_data', declare = true }
      decode_bptc_u64 { bits = 31, dest = 'secondary_index_data', declare = true }
      !! 32 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.rotation = BptcRotation((block.data[0] >> 6) & 0x3u);
      U8 r[2] = {
         U8(block.data[1] & 0x7fu),
         U8(((block.data[1] >> 7) | (block.data[2] << 1)) & 0x7fu)
      };
      U8 g[2] = {
         U8(((block.data[2] >> 6) | (block.data[3] << 2)) & 0x7fu),
         U8(((block.data[3] >> 5) | (block.data[4] << 3)) & 0x7fu)
      };
      U8 b[2] = {
         U8(((block.data[4] >> 4) | (block.data[5] << 4)) & 0x7fu),
         U8(((block.data[5] >> 3) | (block.data[6] << 5)) & 0x7fu)
      };
      U8 a[2] = {
         U8(((block.data[6] >> 2) | (block.data[7] << 6)) & 0xffu),
         U8(((block.data[7] >> 2) | (block.data[8] << 6)) & 0xffu)
      };
      U64 primary_index_data = U64((
         (block.data[8] >> 2) |
         (block.data[9] << 6) |
         (block.data[10] << 14) |
         (block.data[11] << 22) |
         (block.data[12] << 30)) & 0x7fffffffu);
      U64 secondary_index_data = U64((
         (block.data[12] >> 1) |
         (block.data[13] << 7) |
         (block.data[14] << 15) |
         (block.data[15] << 23)) & 0x7fffffffu);

      /* ######################### END OF GENERATED CODE ######################### */

      for (glm::length_t e = 0; e < 2; ++e) {
         f.endpoints[e].r = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((r[e] << 1) | (r[e] >> 6)));
         f.endpoints[e].g = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((g[e] << 1) | (g[e] >> 6)));
         f.endpoints[e].b = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((b[e] << 1) | (b[e] >> 6)));
         f.endpoints[e].a = FieldRawNorm<U8, 8, FieldType::unorm>::decode(a[e]);
      }

      constexpr U8 primary_bpi = 2;
      constexpr U8 secondary_bpi = 2;
      const U8 anchor = 0;

      const U64 primary_mask = (1ull << ((anchor + 1) * primary_bpi - 1)) - 1;
      const U64 secondary_mask = (1ull << ((anchor + 1) * secondary_bpi - 1)) - 1;

      primary_index_data = (primary_index_data & primary_mask) |
         ((primary_index_data & ~primary_mask) << 1);

      secondary_index_data = (secondary_index_data & secondary_mask) |
         ((secondary_index_data & ~secondary_mask) << 1);

      f.color_index_data = primary_index_data;
      f.color_index_bpp = primary_bpi;
      f.alpha_index_data = secondary_index_data;
      f.alpha_index_bpp = secondary_bpi;

   } else if (0 != (block.data[0] & 0x40)) {
      /////////////////////////////////////////////////////////////////////////
      // Mode 6
      f.n_subsets = 1;

      /*!!
      decode_bptc_rgba { bits = 7, begin = 7, count = 2 }
      decode_bptc_p    { count = 2 }
      decode_bptc_u64  { bits = 63, dest = 'f.color_index_data' }
      !! 33 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      U8 r[2] = {
         U8(((block.data[0] >> 7) | (block.data[1] << 1)) & 0x7fu),
         U8(((block.data[1] >> 6) | (block.data[2] << 2)) & 0x7fu)
      };
      U8 g[2] = {
         U8(((block.data[2] >> 5) | (block.data[3] << 3)) & 0x7fu),
         U8(((block.data[3] >> 4) | (block.data[4] << 4)) & 0x7fu)
      };
      U8 b[2] = {
         U8(((block.data[4] >> 3) | (block.data[5] << 5)) & 0x7fu),
         U8(((block.data[5] >> 2) | (block.data[6] << 6)) & 0x7fu)
      };
      U8 a[2] = {
         U8((block.data[6] >> 1) & 0x7fu),
         U8(block.data[7] & 0x7fu)
      };
      U8 p[2] = {
         U8((block.data[7] >> 7) & 0x1u),
         U8(block.data[8] & 0x1u)
      };
      f.color_index_data = U64((
         (U64(block.data[8]) >> 1) |
         (U64(block.data[9]) << 7) |
         (U64(block.data[10]) << 15) |
         (U64(block.data[11]) << 23) |
         (U64(block.data[12]) << 31) |
         (U64(block.data[13]) << 39) |
         (U64(block.data[14]) << 47) |
         (U64(block.data[15]) << 55)) & 0x7fffffffffffffffull);

      /* ######################### END OF GENERATED CODE ######################### */

      for (glm::length_t e = 0; e < 2; ++e) {
         f.endpoints[e].r = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((r[e] << 1) | p[e]));
         f.endpoints[e].g = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((g[e] << 1) | p[e]));
         f.endpoints[e].b = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((b[e] << 1) | p[e]));
         f.endpoints[e].a = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((a[e] << 1) | p[e]));
      }

      constexpr U8 bpi = 4;
      const U8 anchor = 0;

      const U64 mask = (1ull << ((anchor + 1) * bpi - 1)) - 1;

      f.color_index_data = (f.color_index_data & mask) |
         ((f.color_index_data & ~mask) << 1);

      f.alpha_index_data = f.color_index_data;

      f.color_index_bpp = bpi;
      f.alpha_index_bpp = bpi;

   } else if (0 != (block.data[0] & 0x80)) {
      /////////////////////////////////////////////////////////////////////////
      // Mode 7
      f.n_subsets = 2;

      /*!!
      decode_bptc_u8   { bits = 6, begin = 8, dest = 'f.partition' }
      decode_bptc_rgba { bits = 5, count = 4 }
      decode_bptc_p    { pad_bits = 2, count = 4 }
      decode_bptc_u64  { bits = 30, dest = 'f.color_index_data' }
      !! 40 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.partition = U8(block.data[1] & 0x3fu);
      U8 r[4] = {
         U8(((block.data[1] >> 6) | (block.data[2] << 2)) & 0x1fu),
         U8((block.data[2] >> 3) & 0x1fu),
         U8(block.data[3] & 0x1fu),
         U8(((block.data[3] >> 5) | (block.data[4] << 3)) & 0x1fu)
      };
      U8 g[4] = {
         U8((block.data[4] >> 2) & 0x1fu),
         U8(((block.data[4] >> 7) | (block.data[5] << 1)) & 0x1fu),
         U8(((block.data[5] >> 4) | (block.data[6] << 4)) & 0x1fu),
         U8((block.data[6] >> 1) & 0x1fu)
      };
      U8 b[4] = {
         U8(((block.data[6] >> 6) | (block.data[7] << 2)) & 0x1fu),
         U8((block.data[7] >> 3) & 0x1fu),
         U8(block.data[8] & 0x1fu),
         U8(((block.data[8] >> 5) | (block.data[9] << 3)) & 0x1fu)
      };
      U8 a[4] = {
         U8((block.data[9] >> 2) & 0x1fu),
         U8(((block.data[9] >> 7) | (block.data[10] << 1)) & 0x1fu),
         U8(((block.data[10] >> 4) | (block.data[11] << 4)) & 0x1fu),
         U8((block.data[11] >> 1) & 0x1fu)
      };
      U8 p[4] = {
         U8((block.data[11] >> 4) & 0x4u),
         U8((block.data[11] >> 5) & 0x4u),
         U8((block.data[12] << 2) & 0x4u),
         U8((block.data[12] << 1) & 0x4u)
      };
      f.color_index_data = U64((
         (block.data[12] >> 2) |
         (block.data[13] << 6) |
         (block.data[14] << 14) |
         (block.data[15] << 22)) & 0x3fffffffu);

      /* ######################### END OF GENERATED CODE ######################### */

      for (glm::length_t e = 0; e < 4; ++e) {
         f.endpoints[e].r = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((r[e] << 3) | p[e] | (r[e] >> 3)));
         f.endpoints[e].g = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((g[e] << 3) | p[e] | (g[e] >> 3)));
         f.endpoints[e].b = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((b[e] << 3) | p[e] | (b[e] >> 3)));
         f.endpoints[e].a = FieldRawNorm<U8, 8, FieldType::unorm>::decode(U8((a[e] << 3) | p[e] | (a[e] >> 3)));
      }

      constexpr U8 bpi = 2;
      const U8 anchor0 = 0;
      const U8 anchor1 = anchor2_1[f.partition];

      const U64 mask0 = (1ull << ((anchor0 + 1) * bpi - 1)) - 1;
      const U64 mask1 = (1ull << ((anchor1 + 1) * bpi - 2)) - 1;

      f.color_index_data = (f.color_index_data & mask0) |
         ((f.color_index_data & (mask1 & ~mask0)) << 1) |
         ((f.color_index_data & ~mask1) << 2);

      f.alpha_index_data = f.color_index_data;

      f.color_index_bpp = bpi;
      f.alpha_index_bpp = bpi;
   }

   return f;
}

///////////////////////////////////////////////////////////////////////////////
inline U16 bptc_unquantize_unsigned(U16 value, U8 epb) {
   if (value == 0) {
      return 0;
   } else if (value == (1 << epb) - 1) {
      return 0xffff;
   } else {
      return ((value << 15) + 0x4000) >> (epb - 1);
   }
}

///////////////////////////////////////////////////////////////////////////////
inline U16 bptc_unquantize_signed(U16 value, U8 epb) {
   if (value == 0) {
      return 0;
   } else {
      U16 sign_mask = 1 << (epb - 1);
      if (value == sign_mask) {
         return 0x8001;
      }

      if (0 != (value & sign_mask)) {
         value = ((~value) + 1) & ((1 << epb) - 1);
         value = ((value << 15) + 0x4000) >> (epb - 1);
         value = (~value) + 1;
      } else {
         value = ((value << 15) + 0x4000) >> (epb - 1);
      }
      return value;
   }
}

///////////////////////////////////////////////////////////////////////////////
inline BptcFloatFields decode_bptc_float_fields(BptcBlock block, bool is_signed) {
   BptcFloatFields f;

   constexpr U8 anchor2_1[32] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 2, 8, 2, 2, 8, 8,15, 2, 8, 2, 2, 8, 8, 2, 2 };

   U8 mode = (0 == (block.data[0] & 0x2)) ? (block.data[0] & 0x3) : (block.data[0] & 0x1f);
   U8 epb = 11;
   switch (mode) {
      case 0:
      {
         /*!! bits_used = 2
         decode_bptc_g2(4)
         decode_bptc_b2(4)
         decode_bptc_b3(4)
         decode_bptc_u16 { bits = 10, dest = { 'f.r0', 'f.g0', 'f.b0' } }
         decode_bptc_r1  { bits = 5 }
         decode_bptc_g3(4)
         decode_bptc_g2  { bits = 4 }
         decode_bptc_g1  { bits = 5 }
         decode_bptc_b3(0)
         decode_bptc_g3  { bits = 4 }
         decode_bptc_b1  { bits = 5 }
         decode_bptc_b3(1)
         decode_bptc_b2  { bits = 4 }
         decode_bptc_r2  { bits = 5 }
         decode_bptc_b3(2)
         decode_bptc_r3  { bits = 5 }
         decode_bptc_b3(3)
         sign_extend(2, 10, 5)
         bptc_delta(2, 10)
         !! 41 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.g2 |= U16((block.data[0] << 2) & 0x10u);
         f.b2 |= U16((block.data[0] << 1) & 0x10u);
         f.b3 |= U16(block.data[0] & 0x10u);
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3ffu);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1) | (block.data[3] << 9)) & 0x3ffu);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x3ffu);
         f.r1 = U16((block.data[4] >> 3) & 0x1fu);
         f.g3 |= U16((block.data[5] << 4) & 0x10u);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x1fu);
         f.b3 |= U16((block.data[6] >> 2) & 0x1u);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[7] >> 3) & 0x2u);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0x1fu);
         f.b3 |= U16((block.data[8] >> 4) & 0x4u);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[9] >> 1) & 0x8u);
         if (0 != (f.r1 & 0x10u)) f.r1 |= 0x3e0u;
         if (0 != (f.g1 & 0x10u)) f.g1 |= 0x3e0u;
         if (0 != (f.b1 & 0x10u)) f.b1 |= 0x3e0u;
         if (0 != (f.r2 & 0x10u)) f.r2 |= 0x3e0u;
         if (0 != (f.g2 & 0x10u)) f.g2 |= 0x3e0u;
         if (0 != (f.b2 & 0x10u)) f.b2 |= 0x3e0u;
         if (0 != (f.r3 & 0x10u)) f.r3 |= 0x3e0u;
         if (0 != (f.g3 & 0x10u)) f.g3 |= 0x3e0u;
         if (0 != (f.b3 & 0x10u)) f.b3 |= 0x3e0u;
         f.r1 = (f.r0 + f.r1) & 0x3ffu;
         f.g1 = (f.g0 + f.g1) & 0x3ffu;
         f.b1 = (f.b0 + f.b1) & 0x3ffu;
         f.r2 = (f.r0 + f.r2) & 0x3ffu;
         f.g2 = (f.g0 + f.g2) & 0x3ffu;
         f.b2 = (f.b0 + f.b2) & 0x3ffu;
         f.r3 = (f.r0 + f.r3) & 0x3ffu;
         f.g3 = (f.g0 + f.g3) & 0x3ffu;
         f.b3 = (f.b0 + f.b3) & 0x3ffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 10;
         break;
      }

      case 1:
      {
         /*!! bits_used = 2
         decode_bptc_g2(5)
         decode_bptc_g3 { bits = 2, pad_bits = 4 }
         decode_bptc_r0 { bits = 7 }
         decode_bptc_b3 { bits = 2 }
         decode_bptc_b2(4)
         decode_bptc_g0 { bits = 7 }
         decode_bptc_b2(5)
         decode_bptc_b3(2)
         decode_bptc_g2(4)
         decode_bptc_b0 { bits = 7 }
         decode_bptc_b3(3)
         decode_bptc_b3(4)
         decode_bptc_b3(5)
         decode_bptc_r1 { bits = 6 }
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 6 }
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 6 }
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 6 }
         decode_bptc_r3 { bits = 6 }
         sign_extend(2, 7, 6)
         bptc_delta(2, 7)
         !! 43 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.g2 |= U16((block.data[0] << 3) & 0x20u);
         f.g3 |= U16((block.data[0] << 1) & 0x30u);
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x7fu);
         f.b3 |= U16((block.data[1] >> 4) & 0x3u);
         f.b2 |= U16((block.data[1] >> 2) & 0x10u);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1)) & 0x7fu);
         f.b2 |= U16((block.data[2] >> 1) & 0x20u);
         f.b3 |= U16((block.data[2] >> 5) & 0x4u);
         f.g2 |= U16((block.data[3] << 4) & 0x10u);
         f.b0 = U16((block.data[3] >> 1) & 0x7fu);
         f.b3 |= U16((block.data[4] << 3) & 0x8u);
         f.b3 |= U16((block.data[4] << 3) & 0x10u);
         f.b3 |= U16((block.data[4] << 3) & 0x20u);
         f.r1 = U16(((block.data[4] >> 3) | (block.data[5] << 5)) & 0x3fu);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x3fu);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x3fu);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0x3fu);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0x3fu);
         if (0 != (f.r1 & 0x20u)) f.r1 |= 0x40u;
         if (0 != (f.g1 & 0x20u)) f.g1 |= 0x40u;
         if (0 != (f.b1 & 0x20u)) f.b1 |= 0x40u;
         if (0 != (f.r2 & 0x20u)) f.r2 |= 0x40u;
         if (0 != (f.g2 & 0x20u)) f.g2 |= 0x40u;
         if (0 != (f.b2 & 0x20u)) f.b2 |= 0x40u;
         if (0 != (f.r3 & 0x20u)) f.r3 |= 0x40u;
         if (0 != (f.g3 & 0x20u)) f.g3 |= 0x40u;
         if (0 != (f.b3 & 0x20u)) f.b3 |= 0x40u;
         f.r1 = (f.r0 + f.r1) & 0x7fu;
         f.g1 = (f.g0 + f.g1) & 0x7fu;
         f.b1 = (f.b0 + f.b1) & 0x7fu;
         f.r2 = (f.r0 + f.r2) & 0x7fu;
         f.g2 = (f.g0 + f.g2) & 0x7fu;
         f.b2 = (f.b0 + f.b2) & 0x7fu;
         f.r3 = (f.r0 + f.r3) & 0x7fu;
         f.g3 = (f.g0 + f.g3) & 0x7fu;
         f.b3 = (f.b0 + f.b3) & 0x7fu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 7;
         break;
      }

      case 2:
      {
         /*!! bits_used = 5
         decode_bptc_u16 { bits = 10, dest = { 'f.r0', 'f.g0', 'f.b0' } }
         decode_bptc_r1 { bits = 5 }
         decode_bptc_r0(10)
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 4 }
         decode_bptc_g0(10)
         decode_bptc_b3(0)
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 4 }
         decode_bptc_b0(10)
         decode_bptc_b3(1)
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 5 }
         decode_bptc_b3(2)
         decode_bptc_r3 { bits = 5 }
         decode_bptc_b3(3)
         sign_extend(2, 11, 5, 4, 4)
         bptc_delta(2, 11)
         !! 40 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3ffu);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1) | (block.data[3] << 9)) & 0x3ffu);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x3ffu);
         f.r1 = U16((block.data[4] >> 3) & 0x1fu);
         f.r0 |= U16((block.data[5] << 10) & 0x400u);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0xfu);
         f.g0 |= U16((block.data[6] << 9) & 0x400u);
         f.b3 |= U16((block.data[6] >> 2) & 0x1u);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0xfu);
         f.b0 |= U16((block.data[7] << 7) & 0x400u);
         f.b3 |= U16((block.data[7] >> 3) & 0x2u);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0x1fu);
         f.b3 |= U16((block.data[8] >> 4) & 0x4u);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[9] >> 1) & 0x8u);
         if (0 != (f.r1 & 0x10u)) f.r1 |= 0x7e0u;
         if (0 != (f.g1 & 0x8u)) f.g1 |= 0x7f0u;
         if (0 != (f.b1 & 0x8u)) f.b1 |= 0x7f0u;
         if (0 != (f.r2 & 0x10u)) f.r2 |= 0x7e0u;
         if (0 != (f.g2 & 0x8u)) f.g2 |= 0x7f0u;
         if (0 != (f.b2 & 0x8u)) f.b2 |= 0x7f0u;
         if (0 != (f.r3 & 0x10u)) f.r3 |= 0x7e0u;
         if (0 != (f.g3 & 0x8u)) f.g3 |= 0x7f0u;
         if (0 != (f.b3 & 0x8u)) f.b3 |= 0x7f0u;
         f.r1 = (f.r0 + f.r1) & 0x7ffu;
         f.g1 = (f.g0 + f.g1) & 0x7ffu;
         f.b1 = (f.b0 + f.b1) & 0x7ffu;
         f.r2 = (f.r0 + f.r2) & 0x7ffu;
         f.g2 = (f.g0 + f.g2) & 0x7ffu;
         f.b2 = (f.b0 + f.b2) & 0x7ffu;
         f.r3 = (f.r0 + f.r3) & 0x7ffu;
         f.g3 = (f.g0 + f.g3) & 0x7ffu;
         f.b3 = (f.b0 + f.b3) & 0x7ffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 11;
         break;
      }

      case 6:
      {
         /*!! bits_used = 5
         decode_bptc_u16 { bits = 10, dest = { 'f.r0', 'f.g0', 'f.b0' } }
         decode_bptc_r1 { bits = 4 }
         decode_bptc_r0(10)
         decode_bptc_g3(4)
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 5 }
         decode_bptc_g0(10)
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 4 }
         decode_bptc_b0(10)
         decode_bptc_b3(1)
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 4 }
         decode_bptc_b3(0)
         decode_bptc_b3(2)
         decode_bptc_r3 { bits = 4 }
         decode_bptc_g2(4)
         decode_bptc_b3(3)
         sign_extend(2, 11, 4, 5, 4)
         bptc_delta(2, 11)
         !! 42 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3ffu);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1) | (block.data[3] << 9)) & 0x3ffu);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x3ffu);
         f.r1 = U16((block.data[4] >> 3) & 0xfu);
         f.r0 |= U16((block.data[4] << 3) & 0x400u);
         f.g3 |= U16((block.data[5] << 4) & 0x10u);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x1fu);
         f.g0 |= U16((block.data[6] << 8) & 0x400u);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0xfu);
         f.b0 |= U16((block.data[7] << 7) & 0x400u);
         f.b3 |= U16((block.data[7] >> 3) & 0x2u);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0xfu);
         f.b3 |= U16((block.data[8] >> 5) & 0x1u);
         f.b3 |= U16((block.data[8] >> 4) & 0x4u);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0xfu);
         f.g2 |= U16((block.data[9] << 1) & 0x10u);
         f.b3 |= U16((block.data[9] >> 1) & 0x8u);
         if (0 != (f.r1 & 0x8u)) f.r1 |= 0x7f0u;
         if (0 != (f.g1 & 0x10u)) f.g1 |= 0x7e0u;
         if (0 != (f.b1 & 0x8u)) f.b1 |= 0x7f0u;
         if (0 != (f.r2 & 0x8u)) f.r2 |= 0x7f0u;
         if (0 != (f.g2 & 0x10u)) f.g2 |= 0x7e0u;
         if (0 != (f.b2 & 0x8u)) f.b2 |= 0x7f0u;
         if (0 != (f.r3 & 0x8u)) f.r3 |= 0x7f0u;
         if (0 != (f.g3 & 0x10u)) f.g3 |= 0x7e0u;
         if (0 != (f.b3 & 0x8u)) f.b3 |= 0x7f0u;
         f.r1 = (f.r0 + f.r1) & 0x7ffu;
         f.g1 = (f.g0 + f.g1) & 0x7ffu;
         f.b1 = (f.b0 + f.b1) & 0x7ffu;
         f.r2 = (f.r0 + f.r2) & 0x7ffu;
         f.g2 = (f.g0 + f.g2) & 0x7ffu;
         f.b2 = (f.b0 + f.b2) & 0x7ffu;
         f.r3 = (f.r0 + f.r3) & 0x7ffu;
         f.g3 = (f.g0 + f.g3) & 0x7ffu;
         f.b3 = (f.b0 + f.b3) & 0x7ffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 11;
         break;
      }

      case 10:
      {
         /*!! bits_used = 5
         decode_bptc_u16 { bits = 10, dest = { 'f.r0', 'f.g0', 'f.b0' } }
         decode_bptc_r1 { bits = 4 }
         decode_bptc_r0(10)
         decode_bptc_b2(4)
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 4 }
         decode_bptc_g0(10)
         decode_bptc_b3(0)
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 5 }
         decode_bptc_b0(10)
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 4 }
         decode_bptc_b3 { bits = 2, pad_bits = 1 }
         decode_bptc_r3 { bits = 4 }
         decode_bptc_b3(4)
         decode_bptc_b3(4)
         sign_extend(2, 11, 4, 4, 5)
         bptc_delta(2, 11)
         !! 41 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3ffu);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1) | (block.data[3] << 9)) & 0x3ffu);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x3ffu);
         f.r1 = U16((block.data[4] >> 3) & 0xfu);
         f.r0 |= U16((block.data[4] << 3) & 0x400u);
         f.b2 |= U16((block.data[5] << 4) & 0x10u);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0xfu);
         f.g0 |= U16((block.data[6] << 9) & 0x400u);
         f.b3 |= U16((block.data[6] >> 2) & 0x1u);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x1fu);
         f.b0 |= U16((block.data[7] << 6) & 0x400u);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0xfu);
         f.b3 |= U16((block.data[8] >> 4) & 0x6u);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0xfu);
         f.b3 |= U16((block.data[9] << 1) & 0x10u);
         f.b3 |= U16(block.data[9] & 0x10u);
         if (0 != (f.r1 & 0x8u)) f.r1 |= 0x7f0u;
         if (0 != (f.g1 & 0x8u)) f.g1 |= 0x7f0u;
         if (0 != (f.b1 & 0x10u)) f.b1 |= 0x7e0u;
         if (0 != (f.r2 & 0x8u)) f.r2 |= 0x7f0u;
         if (0 != (f.g2 & 0x8u)) f.g2 |= 0x7f0u;
         if (0 != (f.b2 & 0x10u)) f.b2 |= 0x7e0u;
         if (0 != (f.r3 & 0x8u)) f.r3 |= 0x7f0u;
         if (0 != (f.g3 & 0x8u)) f.g3 |= 0x7f0u;
         if (0 != (f.b3 & 0x10u)) f.b3 |= 0x7e0u;
         f.r1 = (f.r0 + f.r1) & 0x7ffu;
         f.g1 = (f.g0 + f.g1) & 0x7ffu;
         f.b1 = (f.b0 + f.b1) & 0x7ffu;
         f.r2 = (f.r0 + f.r2) & 0x7ffu;
         f.g2 = (f.g0 + f.g2) & 0x7ffu;
         f.b2 = (f.b0 + f.b2) & 0x7ffu;
         f.r3 = (f.r0 + f.r3) & 0x7ffu;
         f.g3 = (f.g0 + f.g3) & 0x7ffu;
         f.b3 = (f.b0 + f.b3) & 0x7ffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 11;
         break;
      }

      case 14:
      {
         /*!! bits_used = 5
         decode_bptc_r0 { bits = 9 }
         decode_bptc_b2(4)
         decode_bptc_g0 { bits = 9 }
         decode_bptc_g2(4)
         decode_bptc_b0 { bits = 9 }
         decode_bptc_b3(4)
         decode_bptc_r1 { bits = 5 }
         decode_bptc_g3(4)
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 5 }
         decode_bptc_b3(0)
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 5 }
         decode_bptc_b3(1)
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 5 }
         decode_bptc_b3(2)
         decode_bptc_r3 { bits = 5 }
         decode_bptc_b3(3)
         sign_extend(2, 9, 5)
         bptc_delta(2, 9)
         !! 41 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x1ffu);
         f.b2 |= U16((block.data[1] >> 2) & 0x10u);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1)) & 0x1ffu);
         f.g2 |= U16((block.data[3] << 4) & 0x10u);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x1ffu);
         f.b3 |= U16((block.data[4] << 2) & 0x10u);
         f.r1 = U16((block.data[4] >> 3) & 0x1fu);
         f.g3 |= U16((block.data[5] << 4) & 0x10u);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x1fu);
         f.b3 |= U16((block.data[6] >> 2) & 0x1u);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[7] >> 3) & 0x2u);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0x1fu);
         f.b3 |= U16((block.data[8] >> 4) & 0x4u);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[9] >> 1) & 0x8u);
         if (0 != (f.r1 & 0x10u)) f.r1 |= 0x1e0u;
         if (0 != (f.g1 & 0x10u)) f.g1 |= 0x1e0u;
         if (0 != (f.b1 & 0x10u)) f.b1 |= 0x1e0u;
         if (0 != (f.r2 & 0x10u)) f.r2 |= 0x1e0u;
         if (0 != (f.g2 & 0x10u)) f.g2 |= 0x1e0u;
         if (0 != (f.b2 & 0x10u)) f.b2 |= 0x1e0u;
         if (0 != (f.r3 & 0x10u)) f.r3 |= 0x1e0u;
         if (0 != (f.g3 & 0x10u)) f.g3 |= 0x1e0u;
         if (0 != (f.b3 & 0x10u)) f.b3 |= 0x1e0u;
         f.r1 = (f.r0 + f.r1) & 0x1ffu;
         f.g1 = (f.g0 + f.g1) & 0x1ffu;
         f.b1 = (f.b0 + f.b1) & 0x1ffu;
         f.r2 = (f.r0 + f.r2) & 0x1ffu;
         f.g2 = (f.g0 + f.g2) & 0x1ffu;
         f.b2 = (f.b0 + f.b2) & 0x1ffu;
         f.r3 = (f.r0 + f.r3) & 0x1ffu;
         f.g3 = (f.g0 + f.g3) & 0x1ffu;
         f.b3 = (f.b0 + f.b3) & 0x1ffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 9;
         break;
      }

      case 18:
      {
         /*!! bits_used = 5
         decode_bptc_r0 { bits = 8 }
         decode_bptc_g3(4)
         decode_bptc_b2(4)
         decode_bptc_g0 { bits = 8 }
         decode_bptc_b3(2)
         decode_bptc_g2(4)
         decode_bptc_b0 { bits = 8 }
         decode_bptc_b3 { bits = 2, pad_bits = 3 }
         decode_bptc_r1 { bits = 6 }
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 5 }
         decode_bptc_b3(0)
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 5 }
         decode_bptc_b3(1)
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 6 }
         decode_bptc_r3 { bits = 6 }
         sign_extend(2, 8, 6, 5, 5)
         bptc_delta(2, 8)
         !! 40 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0xffu);
         f.g3 |= U16((block.data[1] >> 1) & 0x10u);
         f.b2 |= U16((block.data[1] >> 2) & 0x10u);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1)) & 0xffu);
         f.b3 |= U16((block.data[2] >> 5) & 0x4u);
         f.g2 |= U16((block.data[3] << 4) & 0x10u);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0xffu);
         f.b3 |= U16((block.data[4] << 2) & 0x18u);
         f.r1 = U16(((block.data[4] >> 3) | (block.data[5] << 5)) & 0x3fu);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x1fu);
         f.b3 |= U16((block.data[6] >> 2) & 0x1u);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[7] >> 3) & 0x2u);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0x3fu);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0x3fu);
         if (0 != (f.r1 & 0x20u)) f.r1 |= 0xc0u;
         if (0 != (f.g1 & 0x10u)) f.g1 |= 0xe0u;
         if (0 != (f.b1 & 0x10u)) f.b1 |= 0xe0u;
         if (0 != (f.r2 & 0x20u)) f.r2 |= 0xc0u;
         if (0 != (f.g2 & 0x10u)) f.g2 |= 0xe0u;
         if (0 != (f.b2 & 0x10u)) f.b2 |= 0xe0u;
         if (0 != (f.r3 & 0x20u)) f.r3 |= 0xc0u;
         if (0 != (f.g3 & 0x10u)) f.g3 |= 0xe0u;
         if (0 != (f.b3 & 0x10u)) f.b3 |= 0xe0u;
         f.r1 = (f.r0 + f.r1) & 0xffu;
         f.g1 = (f.g0 + f.g1) & 0xffu;
         f.b1 = (f.b0 + f.b1) & 0xffu;
         f.r2 = (f.r0 + f.r2) & 0xffu;
         f.g2 = (f.g0 + f.g2) & 0xffu;
         f.b2 = (f.b0 + f.b2) & 0xffu;
         f.r3 = (f.r0 + f.r3) & 0xffu;
         f.g3 = (f.g0 + f.g3) & 0xffu;
         f.b3 = (f.b0 + f.b3) & 0xffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 8;
         break;
      }

      case 22:
      {
         /*!! bits_used = 5
         decode_bptc_r0 { bits = 8 }
         decode_bptc_b3(0)
         decode_bptc_b2(4)
         decode_bptc_g0 { bits = 8 }
         decode_bptc_g2(5)
         decode_bptc_g2(4)
         decode_bptc_b0 { bits = 8 }
         decode_bptc_g3(5)
         decode_bptc_b3(4)
         decode_bptc_r1 { bits = 5 }
         decode_bptc_g3(4)
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 6 }
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 5 }
         decode_bptc_b3(1)
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 5 }
         decode_bptc_b3(2)
         decode_bptc_r3 { bits = 5 }
         decode_bptc_b3(3)
         sign_extend(2, 8, 5, 6, 5)
         bptc_delta(2, 8)
         !! 43 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0xffu);
         f.b3 |= U16((block.data[1] >> 5) & 0x1u);
         f.b2 |= U16((block.data[1] >> 2) & 0x10u);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1)) & 0xffu);
         f.g2 |= U16((block.data[2] >> 2) & 0x20u);
         f.g2 |= U16((block.data[3] << 4) & 0x10u);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0xffu);
         f.g3 |= U16((block.data[4] << 4) & 0x20u);
         f.b3 |= U16((block.data[4] << 2) & 0x10u);
         f.r1 = U16((block.data[4] >> 3) & 0x1fu);
         f.g3 |= U16((block.data[5] << 4) & 0x10u);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x3fu);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[7] >> 3) & 0x2u);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0x1fu);
         f.b3 |= U16((block.data[8] >> 4) & 0x4u);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[9] >> 1) & 0x8u);
         if (0 != (f.r1 & 0x10u)) f.r1 |= 0xe0u;
         if (0 != (f.g1 & 0x20u)) f.g1 |= 0xc0u;
         if (0 != (f.b1 & 0x10u)) f.b1 |= 0xe0u;
         if (0 != (f.r2 & 0x10u)) f.r2 |= 0xe0u;
         if (0 != (f.g2 & 0x20u)) f.g2 |= 0xc0u;
         if (0 != (f.b2 & 0x10u)) f.b2 |= 0xe0u;
         if (0 != (f.r3 & 0x10u)) f.r3 |= 0xe0u;
         if (0 != (f.g3 & 0x20u)) f.g3 |= 0xc0u;
         if (0 != (f.b3 & 0x10u)) f.b3 |= 0xe0u;
         f.r1 = (f.r0 + f.r1) & 0xffu;
         f.g1 = (f.g0 + f.g1) & 0xffu;
         f.b1 = (f.b0 + f.b1) & 0xffu;
         f.r2 = (f.r0 + f.r2) & 0xffu;
         f.g2 = (f.g0 + f.g2) & 0xffu;
         f.b2 = (f.b0 + f.b2) & 0xffu;
         f.r3 = (f.r0 + f.r3) & 0xffu;
         f.g3 = (f.g0 + f.g3) & 0xffu;
         f.b3 = (f.b0 + f.b3) & 0xffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 8;
         break;
      }

      case 26:
      {
         /*!! bits_used = 5
         decode_bptc_r0 { bits = 8 }
         decode_bptc_b3(1)
         decode_bptc_b2(4)
         decode_bptc_g0 { bits = 8 }
         decode_bptc_b2(5)
         decode_bptc_g2(4)
         decode_bptc_b0 { bits = 8 }
         decode_bptc_b3(5)
         decode_bptc_b3(4)
         decode_bptc_r1 { bits = 5 }
         decode_bptc_g3(4)
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 5 }
         decode_bptc_b3(0)
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 6 }
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 5 }
         decode_bptc_b3(2)
         decode_bptc_r3 { bits = 5 }
         decode_bptc_b3(3)
         sign_extend(2, 8, 5, 5, 6)
         bptc_delta(2, 8)
         !! 43 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0xffu);
         f.b3 |= U16((block.data[1] >> 4) & 0x2u);
         f.b2 |= U16((block.data[1] >> 2) & 0x10u);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1)) & 0xffu);
         f.b2 |= U16((block.data[2] >> 2) & 0x20u);
         f.g2 |= U16((block.data[3] << 4) & 0x10u);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0xffu);
         f.b3 |= U16((block.data[4] << 4) & 0x20u);
         f.b3 |= U16((block.data[4] << 2) & 0x10u);
         f.r1 = U16((block.data[4] >> 3) & 0x1fu);
         f.g3 |= U16((block.data[5] << 4) & 0x10u);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x1fu);
         f.b3 |= U16((block.data[6] >> 2) & 0x1u);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x3fu);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0x1fu);
         f.b3 |= U16((block.data[8] >> 4) & 0x4u);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0x1fu);
         f.b3 |= U16((block.data[9] >> 1) & 0x8u);
         if (0 != (f.r1 & 0x10u)) f.r1 |= 0xe0u;
         if (0 != (f.g1 & 0x10u)) f.g1 |= 0xe0u;
         if (0 != (f.b1 & 0x20u)) f.b1 |= 0xc0u;
         if (0 != (f.r2 & 0x10u)) f.r2 |= 0xe0u;
         if (0 != (f.g2 & 0x10u)) f.g2 |= 0xe0u;
         if (0 != (f.b2 & 0x20u)) f.b2 |= 0xc0u;
         if (0 != (f.r3 & 0x10u)) f.r3 |= 0xe0u;
         if (0 != (f.g3 & 0x10u)) f.g3 |= 0xe0u;
         if (0 != (f.b3 & 0x20u)) f.b3 |= 0xc0u;
         f.r1 = (f.r0 + f.r1) & 0xffu;
         f.g1 = (f.g0 + f.g1) & 0xffu;
         f.b1 = (f.b0 + f.b1) & 0xffu;
         f.r2 = (f.r0 + f.r2) & 0xffu;
         f.g2 = (f.g0 + f.g2) & 0xffu;
         f.b2 = (f.b0 + f.b2) & 0xffu;
         f.r3 = (f.r0 + f.r3) & 0xffu;
         f.g3 = (f.g0 + f.g3) & 0xffu;
         f.b3 = (f.b0 + f.b3) & 0xffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 8;
         break;
      }

      case 30:
      {
         /*!! bits_used = 5
         decode_bptc_r0 { bits = 6 }
         decode_bptc_g3(4)
         decode_bptc_b3 { bits = 2 }
         decode_bptc_b2(4)
         decode_bptc_g0 { bits = 6 }
         decode_bptc_g2(5)
         decode_bptc_b2(5)
         decode_bptc_b3(2)
         decode_bptc_g2(4)
         decode_bptc_b0 { bits = 6 }
         decode_bptc_g3(5)
         decode_bptc_b3(3)
         decode_bptc_b3(5)
         decode_bptc_b3(4)
         decode_bptc_r1 { bits = 6 }
         decode_bptc_g2 { bits = 4 }
         decode_bptc_g1 { bits = 6 }
         decode_bptc_g3 { bits = 4 }
         decode_bptc_b1 { bits = 6 }
         decode_bptc_b2 { bits = 4 }
         decode_bptc_r2 { bits = 6 }
         decode_bptc_r3 { bits = 6 }
         !! 26 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3fu);
         f.g3 |= U16((block.data[1] << 1) & 0x10u);
         f.b3 |= U16((block.data[1] >> 4) & 0x3u);
         f.b2 |= U16((block.data[1] >> 2) & 0x10u);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1)) & 0x3fu);
         f.g2 |= U16(block.data[2] & 0x20u);
         f.b2 |= U16((block.data[2] >> 1) & 0x20u);
         f.b3 |= U16((block.data[2] >> 5) & 0x4u);
         f.g2 |= U16((block.data[3] << 4) & 0x10u);
         f.b0 = U16((block.data[3] >> 1) & 0x3fu);
         f.g3 |= U16((block.data[3] >> 2) & 0x20u);
         f.b3 |= U16((block.data[4] << 3) & 0x8u);
         f.b3 |= U16((block.data[4] << 4) & 0x20u);
         f.b3 |= U16((block.data[4] << 2) & 0x10u);
         f.r1 = U16(((block.data[4] >> 3) | (block.data[5] << 5)) & 0x3fu);
         f.g2 |= U16((block.data[5] >> 1) & 0xfu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x3fu);
         f.g3 |= U16((block.data[6] >> 3) & 0xfu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x3fu);
         f.b2 |= U16(((block.data[7] >> 5) | (block.data[8] << 3)) & 0xfu);
         f.r2 = U16((block.data[8] >> 1) & 0x3fu);
         f.r3 = U16(((block.data[8] >> 7) | (block.data[9] << 1)) & 0x3fu);

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 6;
         break;
      }

      case 3:
      {
         /*!! bits_used = 5
         decode_bptc_u16 { bits = 10, dest = { 'f.r0', 'f.g0', 'f.b0', 'f.r1', 'f.g1', 'f.b1' } }
         !! 10 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3ffu);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1) | (block.data[3] << 9)) & 0x3ffu);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x3ffu);
         f.r1 = U16(((block.data[4] >> 3) | (block.data[5] << 5)) & 0x3ffu);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x3ffu);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1) | (block.data[8] << 9)) & 0x3ffu);

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 10;
         break;
      }

      case 7:
      {
         /*!! bits_used = 5
         decode_bptc_u16 { bits = 10, dest = { 'f.r0', 'f.g0', 'f.b0' } }
         decode_bptc_r1  { bits = 9 }
         decode_bptc_r0(10)
         decode_bptc_g1  { bits = 9 }
         decode_bptc_g0(10)
         decode_bptc_b1  { bits = 9 }
         decode_bptc_b0(10)
         sign_extend(1, 11, 9)
         bptc_delta(1, 11)
         !! 19 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3ffu);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1) | (block.data[3] << 9)) & 0x3ffu);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x3ffu);
         f.r1 = U16(((block.data[4] >> 3) | (block.data[5] << 5)) & 0x1ffu);
         f.r0 |= U16((block.data[5] << 6) & 0x400u);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0x1ffu);
         f.g0 |= U16((block.data[6] << 4) & 0x400u);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0x1ffu);
         f.b0 |= U16((block.data[8] << 10) & 0x400u);
         if (0 != (f.r1 & 0x100u)) f.r1 |= 0x600u;
         if (0 != (f.g1 & 0x100u)) f.g1 |= 0x600u;
         if (0 != (f.b1 & 0x100u)) f.b1 |= 0x600u;
         f.r1 = (f.r0 + f.r1) & 0x7ffu;
         f.g1 = (f.g0 + f.g1) & 0x7ffu;
         f.b1 = (f.b0 + f.b1) & 0x7ffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 11;
         break;
      }

      case 11:
      {
         /*!! bits_used = 5
         decode_bptc_u16 { bits = 10, dest = { 'f.r0', 'f.g0', 'f.b0' } }
         decode_bptc_r1  { bits = 8 }
         decode_bptc_r0(11)
         decode_bptc_r0(10)
         decode_bptc_g1  { bits = 8 }
         decode_bptc_g0(11)
         decode_bptc_g0(10)
         decode_bptc_b1  { bits = 8 }
         decode_bptc_b0(11)
         decode_bptc_b0(10)
         sign_extend(1, 12, 8)
         bptc_delta(1, 12)
         !! 22 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3ffu);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1) | (block.data[3] << 9)) & 0x3ffu);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x3ffu);
         f.r1 = U16(((block.data[4] >> 3) | (block.data[5] << 5)) & 0xffu);
         f.r0 |= U16((block.data[5] << 8) & 0x800u);
         f.r0 |= U16((block.data[5] << 6) & 0x400u);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0xffu);
         f.g0 |= U16((block.data[6] << 6) & 0x800u);
         f.g0 |= U16((block.data[6] << 4) & 0x400u);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0xffu);
         f.b0 |= U16((block.data[7] << 4) & 0x800u);
         f.b0 |= U16((block.data[8] << 10) & 0x400u);
         if (0 != (f.r1 & 0x80u)) f.r1 |= 0xf00u;
         if (0 != (f.g1 & 0x80u)) f.g1 |= 0xf00u;
         if (0 != (f.b1 & 0x80u)) f.b1 |= 0xf00u;
         f.r1 = (f.r0 + f.r1) & 0xfffu;
         f.g1 = (f.g0 + f.g1) & 0xfffu;
         f.b1 = (f.b0 + f.b1) & 0xfffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 12;
         break;
      }

      case 15:
      {
         /*!! bits_used = 5
         decode_bptc_u16 { bits = 10, dest = { 'f.r0', 'f.g0', 'f.b0' } }
         decode_bptc_r1  { bits = 4 }
         decode_bptc_r0(15)
         decode_bptc_r0(14)
         decode_bptc_r0(13)
         decode_bptc_r0(12)
         decode_bptc_r0(11)
         decode_bptc_r0(10)
         decode_bptc_g1  { bits = 4 }
         decode_bptc_g0(15)
         decode_bptc_g0(14)
         decode_bptc_g0(13)
         decode_bptc_g0(12)
         decode_bptc_g0(11)
         decode_bptc_g0(10)
         decode_bptc_b1  { bits = 4 }
         decode_bptc_b0(15)
         decode_bptc_b0(14)
         decode_bptc_b0(13)
         decode_bptc_b0(12)
         decode_bptc_b0(11)
         decode_bptc_b0(10)
         sign_extend(1, 16, 4)
         bptc_delta(1, 16)
         !! 34 */
         /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
         f.r0 = U16(((block.data[0] >> 5) | (block.data[1] << 3)) & 0x3ffu);
         f.g0 = U16(((block.data[1] >> 7) | (block.data[2] << 1) | (block.data[3] << 9)) & 0x3ffu);
         f.b0 = U16(((block.data[3] >> 1) | (block.data[4] << 7)) & 0x3ffu);
         f.r1 = U16((block.data[4] >> 3) & 0xfu);
         f.r0 |= U16((block.data[4] << 8) & 0x8000u);
         f.r0 |= U16((block.data[5] << 14) & 0x4000u);
         f.r0 |= U16((block.data[5] << 12) & 0x2000u);
         f.r0 |= U16((block.data[5] << 10) & 0x1000u);
         f.r0 |= U16((block.data[5] << 8) & 0x800u);
         f.r0 |= U16((block.data[5] << 6) & 0x400u);
         f.g1 = U16(((block.data[5] >> 5) | (block.data[6] << 3)) & 0xfu);
         f.g0 |= U16((block.data[6] << 14) & 0x8000u);
         f.g0 |= U16((block.data[6] << 12) & 0x4000u);
         f.g0 |= U16((block.data[6] << 10) & 0x2000u);
         f.g0 |= U16((block.data[6] << 8) & 0x1000u);
         f.g0 |= U16((block.data[6] << 6) & 0x800u);
         f.g0 |= U16((block.data[6] << 4) & 0x400u);
         f.b1 = U16(((block.data[6] >> 7) | (block.data[7] << 1)) & 0xfu);
         f.b0 |= U16((block.data[7] << 12) & 0x8000u);
         f.b0 |= U16((block.data[7] << 10) & 0x4000u);
         f.b0 |= U16((block.data[7] << 8) & 0x2000u);
         f.b0 |= U16((block.data[7] << 6) & 0x1000u);
         f.b0 |= U16((block.data[7] << 4) & 0x800u);
         f.b0 |= U16((block.data[8] << 10) & 0x400u);
         if (0 != (f.r1 & 0x8u)) f.r1 |= 0xfff0u;
         if (0 != (f.g1 & 0x8u)) f.g1 |= 0xfff0u;
         if (0 != (f.b1 & 0x8u)) f.b1 |= 0xfff0u;
         f.r1 = (f.r0 + f.r1) & 0xffffu;
         f.g1 = (f.g0 + f.g1) & 0xffffu;
         f.b1 = (f.b0 + f.b1) & 0xffffu;

         /* ######################### END OF GENERATED CODE ######################### */
         epb = 16;
         break;
      }
   }

   if (is_signed) {
      if (epb < 16) {
         f.r0 = bptc_unquantize_signed(f.r0, epb);
         f.g0 = bptc_unquantize_signed(f.g0, epb);
         f.b0 = bptc_unquantize_signed(f.b0, epb);
         f.r1 = bptc_unquantize_signed(f.r1, epb);
         f.g1 = bptc_unquantize_signed(f.g1, epb);
         f.b1 = bptc_unquantize_signed(f.b1, epb);
         if (f.n_subsets > 1) {
            f.r2 = bptc_unquantize_signed(f.r2, epb);
            f.g2 = bptc_unquantize_signed(f.g2, epb);
            f.b2 = bptc_unquantize_signed(f.b2, epb);
            f.r3 = bptc_unquantize_signed(f.r3, epb);
            f.g3 = bptc_unquantize_signed(f.g3, epb);
            f.b3 = bptc_unquantize_signed(f.b3, epb);
         }
      }
   } else {
      if (epb < 15) {
         f.r0 = bptc_unquantize_unsigned(f.r0, epb);
         f.g0 = bptc_unquantize_unsigned(f.g0, epb);
         f.b0 = bptc_unquantize_unsigned(f.b0, epb);
         f.r1 = bptc_unquantize_unsigned(f.r1, epb);
         f.g1 = bptc_unquantize_unsigned(f.g1, epb);
         f.b1 = bptc_unquantize_unsigned(f.b1, epb);
         if (f.n_subsets > 1) {
            f.r2 = bptc_unquantize_unsigned(f.r2, epb);
            f.g2 = bptc_unquantize_unsigned(f.g2, epb);
            f.b2 = bptc_unquantize_unsigned(f.b2, epb);
            f.r3 = bptc_unquantize_unsigned(f.r3, epb);
            f.g3 = bptc_unquantize_unsigned(f.g3, epb);
            f.b3 = bptc_unquantize_unsigned(f.b3, epb);
         }
      }
   }

   if (0 == (mode & 1)) {
      /*!!
      decode_bptc_u8 { bits = 5, begin = 77, dest = 'f.partition' }
      decode_bptc_u64 { bits = 46, dest = 'f.index_data' }
      !! 12 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.partition = U8(((block.data[9] >> 5) | (block.data[10] << 3)) & 0x1fu);
      f.index_data = U64((
         (U64(block.data[10]) >> 2) |
         (U64(block.data[11]) << 6) |
         (U64(block.data[12]) << 14) |
         (U64(block.data[13]) << 22) |
         (U64(block.data[14]) << 30) |
         (U64(block.data[15]) << 38)) & 0x3fffffffffffull);

      /* ######################### END OF GENERATED CODE ######################### */

      constexpr U8 bpi = 3;
      const U8 anchor0 = 0;
      const U8 anchor1 = anchor2_1[f.partition];

      const U64 mask0 = (1ull << ((anchor0 + 1) * bpi - 1)) - 1;
      const U64 mask1 = (1ull << ((anchor1 + 1) * bpi - 2)) - 1;

      f.index_data = (f.index_data & mask0) |
         ((f.index_data & (mask1 & ~mask0)) << 1) |
         ((f.index_data & ~mask1) << 2);

      f.index_bpp = bpi;
      f.n_subsets = 2;

   } else {
      /*!! decode_bptc_u64 { bits = 63, begin = 65, dest = 'f.index_data' } !! 13 */
      /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
      f.index_data = U64((
         (U64(block.data[8]) >> 1) |
         (U64(block.data[9]) << 7) |
         (U64(block.data[10]) << 15) |
         (U64(block.data[11]) << 23) |
         (U64(block.data[12]) << 31) |
         (U64(block.data[13]) << 39) |
         (U64(block.data[14]) << 47) |
         (U64(block.data[15]) << 55)) & 0x7fffffffffffffffull);

      /* ######################### END OF GENERATED CODE ######################### */

      constexpr U8 bpi = 4;
      const U8 anchor = 0;

      const U64 mask = (1ull << ((anchor + 1) * bpi - 1)) - 1;

      f.index_data = (f.index_data & mask) |
         ((f.index_data & ~mask) << 1);

      f.index_bpp = bpi;
      f.n_subsets = 1;
   }

   return f;
}

///////////////////////////////////////////////////////////////////////////////
inline U8 bptc_pixel_subset_2(U8 partition, U32 pixel_num) {
   constexpr U8 data[][16] = {
      { 0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1 },
      { 0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1 },
      { 0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1 },
      { 0,0,0,1,0,0,1,1,0,0,1,1,0,1,1,1 },
      { 0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1 },
      { 0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1 },
      { 0,0,0,1,0,0,1,1,0,1,1,1,1,1,1,1 },
      { 0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1 },
      { 0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1 },
      { 0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1 },
      { 0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1 },
      { 0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1 },
      { 0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1 },
      { 0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1 },
      { 0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
      { 0,0,0,0,1,0,0,0,1,1,1,0,1,1,1,1 },
      { 0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0 },
      { 0,1,1,1,0,0,1,1,0,0,0,1,0,0,0,0 },
      { 0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,1,0,0,0,1,1,0,0,1,1,1,0 },
      { 0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0 },
      { 0,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1 },
      { 0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0 },
      { 0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0 },
      { 0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0 },
      { 0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0 },
      { 0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0 },
      { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
      { 0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0 },
      { 0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0 },
      { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
      { 0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1 },
      { 0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0 },
      { 0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0 },
      { 0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0 },
      { 0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0 },
      { 0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1 },
      { 0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1 },
      { 0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0 },
      { 0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0 },
      { 0,0,1,1,0,0,1,0,0,1,0,0,1,1,0,0 },
      { 0,0,1,1,1,0,1,1,1,1,0,1,1,1,0,0 },
      { 0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0 },
      { 0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,1 },
      { 0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,1 },
      { 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },
      { 0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,0 },
      { 0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0 },
      { 0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0 },
      { 0,0,0,0,0,1,0,0,1,1,1,0,0,1,0,0 },
      { 0,1,1,0,1,1,0,0,1,0,0,1,0,0,1,1 },
      { 0,0,1,1,0,1,1,0,1,1,0,0,1,0,0,1 },
      { 0,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0 },
      { 0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,0 },
      { 0,1,1,0,1,1,0,0,1,1,0,0,1,0,0,1 },
      { 0,1,1,0,0,0,1,1,0,0,1,1,1,0,0,1 },
      { 0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1 },
      { 0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1 },
      { 0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1 },
      { 0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0 },
      { 0,0,1,0,0,0,1,0,1,1,1,0,1,1,1,0 },
      { 0,1,0,0,0,1,0,0,0,1,1,1,0,1,1,1 },
   };

   return data[partition][pixel_num];
}

///////////////////////////////////////////////////////////////////////////////
inline U8 bptc_pixel_subset_3(U8 partition, U32 pixel_num) {
   constexpr U8 data[][16] = {
      { 0,0,1,1,0,0,1,1,0,2,2,1,2,2,2,2 },
      { 0,0,0,1,0,0,1,1,2,2,1,1,2,2,2,1 },
      { 0,0,0,0,2,0,0,1,2,2,1,1,2,2,1,1 },
      { 0,2,2,2,0,0,2,2,0,0,1,1,0,1,1,1 },
      { 0,0,0,0,0,0,0,0,1,1,2,2,1,1,2,2 },
      { 0,0,1,1,0,0,1,1,0,0,2,2,0,0,2,2 },
      { 0,0,2,2,0,0,2,2,1,1,1,1,1,1,1,1 },
      { 0,0,1,1,0,0,1,1,2,2,1,1,2,2,1,1 },
      { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2 },
      { 0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2 },
      { 0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2 },
      { 0,0,1,2,0,0,1,2,0,0,1,2,0,0,1,2 },
      { 0,1,1,2,0,1,1,2,0,1,1,2,0,1,1,2 },
      { 0,1,2,2,0,1,2,2,0,1,2,2,0,1,2,2 },
      { 0,0,1,1,0,1,1,2,1,1,2,2,1,2,2,2 },
      { 0,0,1,1,2,0,0,1,2,2,0,0,2,2,2,0 },
      { 0,0,0,1,0,0,1,1,0,1,1,2,1,1,2,2 },
      { 0,1,1,1,0,0,1,1,2,0,0,1,2,2,0,0 },
      { 0,0,0,0,1,1,2,2,1,1,2,2,1,1,2,2 },
      { 0,0,2,2,0,0,2,2,0,0,2,2,1,1,1,1 },
      { 0,1,1,1,0,1,1,1,0,2,2,2,0,2,2,2 },
      { 0,0,0,1,0,0,0,1,2,2,2,1,2,2,2,1 },
      { 0,0,0,0,0,0,1,1,0,1,2,2,0,1,2,2 },
      { 0,0,0,0,1,1,0,0,2,2,1,0,2,2,1,0 },
      { 0,1,2,2,0,1,2,2,0,0,1,1,0,0,0,0 },
      { 0,0,1,2,0,0,1,2,1,1,2,2,2,2,2,2 },
      { 0,1,1,0,1,2,2,1,1,2,2,1,0,1,1,0 },
      { 0,0,0,0,0,1,1,0,1,2,2,1,1,2,2,1 },
      { 0,0,2,2,1,1,0,2,1,1,0,2,0,0,2,2 },
      { 0,1,1,0,0,1,1,0,2,0,0,2,2,2,2,2 },
      { 0,0,1,1,0,1,2,2,0,1,2,2,0,0,1,1 },
      { 0,0,0,0,2,0,0,0,2,2,1,1,2,2,2,1 },
      { 0,0,0,0,0,0,0,2,1,1,2,2,1,2,2,2 },
      { 0,2,2,2,0,0,2,2,0,0,1,2,0,0,1,1 },
      { 0,0,1,1,0,0,1,2,0,0,2,2,0,2,2,2 },
      { 0,1,2,0,0,1,2,0,0,1,2,0,0,1,2,0 },
      { 0,0,0,0,1,1,1,1,2,2,2,2,0,0,0,0 },
      { 0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0 },
      { 0,1,2,0,2,0,1,2,1,2,0,1,0,1,2,0 },
      { 0,0,1,1,2,2,0,0,1,1,2,2,0,0,1,1 },
      { 0,0,1,1,1,1,2,2,2,2,0,0,0,0,1,1 },
      { 0,1,0,1,0,1,0,1,2,2,2,2,2,2,2,2 },
      { 0,0,0,0,0,0,0,0,2,1,2,1,2,1,2,1 },
      { 0,0,2,2,1,1,2,2,0,0,2,2,1,1,2,2 },
      { 0,0,2,2,0,0,1,1,0,0,2,2,0,0,1,1 },
      { 0,2,2,0,1,2,2,1,0,2,2,0,1,2,2,1 },
      { 0,1,0,1,2,2,2,2,2,2,2,2,0,1,0,1 },
      { 0,0,0,0,2,1,2,1,2,1,2,1,2,1,2,1 },
      { 0,1,0,1,0,1,0,1,0,1,0,1,2,2,2,2 },
      { 0,2,2,2,0,1,1,1,0,2,2,2,0,1,1,1 },
      { 0,0,0,2,1,1,1,2,0,0,0,2,1,1,1,2 },
      { 0,0,0,0,2,1,1,2,2,1,1,2,2,1,1,2 },
      { 0,2,2,2,0,1,1,1,0,1,1,1,0,2,2,2 },
      { 0,0,0,2,1,1,1,2,1,1,1,2,0,0,0,2 },
      { 0,1,1,0,0,1,1,0,0,1,1,0,2,2,2,2 },
      { 0,0,0,0,0,0,0,0,2,1,1,2,2,1,1,2 },
      { 0,1,1,0,0,1,1,0,2,2,2,2,2,2,2,2 },
      { 0,0,2,2,0,0,1,1,0,0,1,1,0,0,2,2 },
      { 0,0,2,2,1,1,2,2,1,1,2,2,0,0,2,2 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,2 },
      { 0,0,0,2,0,0,0,1,0,0,0,2,0,0,0,1 },
      { 0,2,2,2,1,2,2,2,0,2,2,2,1,2,2,2 },
      { 0,1,0,1,2,2,2,2,2,2,2,2,2,2,2,2 },
      { 0,1,1,1,2,0,1,1,2,2,0,1,2,2,2,0 },
   };

   return data[partition][pixel_num];
}

///////////////////////////////////////////////////////////////////////////////
inline U8 bptc_interpolation_factor_2(U8 code) {
   constexpr U8 data[] = { 0, 21, 43, 64 };
   assert(code < sizeof(data) / sizeof(U8));
   return data[code];
}

///////////////////////////////////////////////////////////////////////////////
inline U8 bptc_interpolation_factor_3(U8 code) {
   constexpr U8 data[] = { 0, 9, 18, 27, 37, 46, 55, 64 };
   assert(code < sizeof(data) / sizeof(U8));
   return data[code];
}

///////////////////////////////////////////////////////////////////////////////
inline U8 bptc_interpolation_factor_4(U8 code) {
   constexpr U8 data[] = { 0, 4, 9, 13, 17, 21, 26, 30, 34, 38, 43, 47, 51, 55, 60, 64 };
   assert(code < sizeof(data) / sizeof(U8));
   return data[code];
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_bptc_unorm_linear(BptcBlock block, uvec2 local) {
   vec4 pixel;

   BptcUnormFields f = decode_bptc_unorm_fields(block);
   U32 pixel_num = 4 * local.y + local.x;

   U8 subset;
   switch (f.n_subsets) {
      case 2:  subset = bptc_pixel_subset_2(f.partition, pixel_num); break;
      case 3:  subset = bptc_pixel_subset_3(f.partition, pixel_num); break;
      default: subset = 0; break;
   }

   vec4 first = f.endpoints[subset * 2];
   vec4 second = f.endpoints[subset * 2 + 1];

   F32 color_factor;
   switch (f.color_index_bpp) {
      case 2: color_factor = bptc_interpolation_factor_2((f.color_index_data >> (2 * pixel_num)) & 0x3); break;
      case 3: color_factor = bptc_interpolation_factor_3((f.color_index_data >> (3 * pixel_num)) & 0x7); break;
      case 4: color_factor = bptc_interpolation_factor_4((f.color_index_data >> (4 * pixel_num)) & 0xf); break;
      default: assert(false); break;
   }
   F32 color_inv = 64.f - color_factor;
   pixel = (first * color_inv + second * color_factor) / 64.f;

   F32 alpha_factor;
   switch (f.alpha_index_bpp) {
      case 2: alpha_factor = bptc_interpolation_factor_2((f.alpha_index_data >> (2 * pixel_num)) & 0x3); break;
      case 3: alpha_factor = bptc_interpolation_factor_3((f.alpha_index_data >> (3 * pixel_num)) & 0x7); break;
      case 4: alpha_factor = bptc_interpolation_factor_4((f.alpha_index_data >> (4 * pixel_num)) & 0xf); break;
      default: assert(false); break;
   }
   F32 alpha_inv = 64.f - alpha_factor;
   pixel.a = (first.a * alpha_inv + second.a * alpha_factor) / 64.f;

   using std::swap;
   switch (f.rotation) {
      case BptcRotation::swap_ra: swap(pixel.a, pixel.r); break;
      case BptcRotation::swap_ga: swap(pixel.a, pixel.g); break;
      case BptcRotation::swap_ba: swap(pixel.a, pixel.b); break;
   }

   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_bptc_unorm_srgb(BptcBlock block, uvec2 local) {
   vec4 pixel;

   BptcUnormFields f = decode_bptc_unorm_fields(block);
   U32 pixel_num = 4 * local.y + local.x;

   U8 subset;
   switch (f.n_subsets) {
      case 2:  subset = bptc_pixel_subset_2(f.partition, pixel_num); break;
      case 3:  subset = bptc_pixel_subset_3(f.partition, pixel_num); break;
      default: subset = 0; break;
   }

   vec4 first = f.endpoints[subset * 2];
   vec4 second = f.endpoints[subset * 2 + 1];

   switch (f.color_index_bpp) {
      case 2:
      {
         U8 code = (f.color_index_data >> (2 * pixel_num)) & 0x3;
         if (code == 0) {
            pixel = first;
         } else if (code == 3) {
            pixel = second;
         } else {
            F32 factor = bptc_interpolation_factor_2(code);
            F32 inv = 64.f - factor;
            vec3 lin_first = srgb_to_linear(vec3(first));
            vec3 lin_second = srgb_to_linear(vec3(second));
            pixel = vec4(linear_to_srgb((lin_first * inv + lin_second * factor) / 64.f), 1.f);
         }
         break;
      }
      case 3:
      {
         U8 code = (f.color_index_data >> (3 * pixel_num)) & 0x7;
         if (code == 0) {
            pixel = first;
         } else if (code == 7) {
            pixel = second;
         } else {
            F32 factor = bptc_interpolation_factor_3(code);
            F32 inv = 64.f - factor;
            vec3 lin_first = srgb_to_linear(vec3(first));
            vec3 lin_second = srgb_to_linear(vec3(second));
            pixel = vec4(linear_to_srgb((lin_first * inv + lin_second * factor) / 64.f), 1.f);
         }
         break;
      }
      case 4:
      {
         U8 code = (f.color_index_data >> (4 * pixel_num)) & 0xf;
         if (code == 0) {
            pixel = first;
         } else if (code == 15) {
            pixel = second;
         } else {
            F32 factor = bptc_interpolation_factor_4(code);
            F32 inv = 64.f - factor;
            vec3 lin_first = srgb_to_linear(vec3(first));
            vec3 lin_second = srgb_to_linear(vec3(second));
            pixel = vec4(linear_to_srgb((lin_first * inv + lin_second * factor) / 64.f), 1.f);
         }
         break;
      }
      default: assert(false); break;
   }

   F32 alpha_factor = 0;
   switch (f.alpha_index_bpp) {
      case 2: alpha_factor = bptc_interpolation_factor_2((f.alpha_index_data >> (2 * pixel_num)) & 0x3); break;
      case 3: alpha_factor = bptc_interpolation_factor_3((f.alpha_index_data >> (3 * pixel_num)) & 0x7); break;
      case 4: alpha_factor = bptc_interpolation_factor_4((f.alpha_index_data >> (4 * pixel_num)) & 0xf); break;
      default: assert(false); break;
   }
   F32 alpha_inv = 64.f - alpha_factor;
   pixel.a = (first.a * alpha_inv + second.a * alpha_factor) / 64.f;

   using std::swap;
   switch (f.rotation) {
      case BptcRotation::swap_ra: swap(pixel.a, pixel.r); break;
      case BptcRotation::swap_ga: swap(pixel.a, pixel.g); break;
      case BptcRotation::swap_ba: swap(pixel.a, pixel.b); break;
   }

   return pixel;
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_bptc_float(BptcBlock block, uvec2 local, bool is_signed) {
   using cvec = glm::tvec3<U16>;

   vec4 pixel;

   BptcFloatFields f = decode_bptc_float_fields(block, is_signed);
   U32 pixel_num = 4 * local.y + local.x;

   U8 subset = f.n_subsets == 1 ? 0 : bptc_pixel_subset_2(f.partition, pixel_num);

   cvec first, second;
   if (subset == 0) {
      first = cvec(f.r0, f.g0, f.b0);
      second = cvec(f.r1, f.g1, f.b1);
   } else {
      first = cvec(f.r2, f.g2, f.b2);
      second = cvec(f.r3, f.g3, f.b3);
   }

   U8 factor;
   if (f.index_bpp == 3) {
      factor = bptc_interpolation_factor_3((f.index_data >> (3 * pixel_num)) & 0x7);
   } else {
      factor = bptc_interpolation_factor_4((f.index_data >> (3 * pixel_num)) & 0xf);
   }
   U8 inv_factor = 64 - factor;
   cvec interpolated;
   for (glm::length_t c = 0; c < 3; ++c) {
      interpolated[c] = U16((first[c] * inv_factor + second[c] * factor) / 64);
   }

   if (is_signed) {
      cvec sign = interpolated & (U16)0x8000;
      interpolated ^= sign;
      for (glm::length_t c = 0; c < 3; ++c) {
         interpolated[c] = U16(interpolated[c] * 31 / 32);
      }
      interpolated |= sign;
   } else {
      for (glm::length_t c = 0; c < 3; ++c) {
         interpolated[c] = U16(interpolated[c] * 63 / 64);
      }
   }

   for (glm::length_t c = 0; c < 3; ++c) {
      pixel[c] = FieldRawNorm<U16, 16, FieldType::sfloat>::decode(interpolated[c]);
   }
   pixel.a = 1.f;

   return pixel;
}

#pragma endregion
#pragma region ETC

// TODO

#pragma endregion
#pragma region RGTC

///////////////////////////////////////////////////////////////////////////////
struct Rgtc1Block {
   U8 val0;
   U8 val1;
   U8 data[6];
};

///////////////////////////////////////////////////////////////////////////////
struct Rgtc2Block {
   Rgtc1Block red;
   Rgtc1Block green;
};

///////////////////////////////////////////////////////////////////////////////
template <FieldType T>
struct RgtcMinValue : std::integral_constant<I8, 0> { };
template <>
struct RgtcMinValue<FieldType::snorm> : std::integral_constant<I8, -1> { };

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
Rgtc1Block get_rgtc1_block(const ImageView& image, Coord block_coord) {
   Rgtc1Block block;
   const void* ptr = image.data() + BlockOffset<ImageView, Coord>::offset(image, block_coord);
   std::memcpy(&block, ptr, sizeof(block));
   return block;
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
Rgtc2Block get_rgtc2_block(const ImageView& image, Coord block_coord) {
   Rgtc2Block block;
   const void* ptr = image.data() + BlockOffset<ImageView, Coord>::offset(image, block_coord);
   std::memcpy(&block, ptr, sizeof(block));
   return block;
}

///////////////////////////////////////////////////////////////////////////////
template <FieldType T = FieldType::unorm>
F32 decode_rgtc1_impl(Rgtc1Block block, U32 pixel_num) {
   U64 data = (U64)block.data[0] |
      ((U64)block.data[1] << 8) |
      ((U64)block.data[2] << 16) |
      ((U64)block.data[3] << 24) |
      ((U64)block.data[4] << 32) |
      ((U64)block.data[5] << 40);

   std::pair<F32, F32> val = std::make_pair(
      FieldRawNorm<U8, 8, T>::decode(block.val0),
      FieldRawNorm<U8, 8, T>::decode(block.val1)
   );

   U64 code = (data >> (3 * pixel_num)) & 0x7;
   if (block.val0 > block.val1) {
      switch (code) {
         case 0: return val.first;
         case 1: return val.second;
         case 2: return (6.f * val.first + 1.f * val.second) / 7.f;
         case 3: return (5.f * val.first + 2.f * val.second) / 7.f;
         case 4: return (4.f * val.first + 3.f * val.second) / 7.f;
         case 5: return (3.f * val.first + 4.f * val.second) / 7.f;
         case 6: return (2.f * val.first + 5.f * val.second) / 7.f;
         case 7: return (1.f * val.first + 6.f * val.second) / 7.f;
      }
   } else {
      switch (code) {
         case 0: return val.first;
         case 1: return val.second;
         case 2: return (4.f * val.first + 1.f * val.second) / 5.f;
         case 3: return (3.f * val.first + 2.f * val.second) / 5.f;
         case 4: return (2.f * val.first + 3.f * val.second) / 5.f;
         case 5: return (1.f * val.first + 4.f * val.second) / 5.f;
         case 6: return F32(RgtcMinValue<T>::value);
         case 7: return 1.f;
      }
   }

   assert(false);
   return 0.f;
}

///////////////////////////////////////////////////////////////////////////////
template <FieldType T = FieldType::unorm>
F32 decode_rgtc1(Rgtc1Block block, uvec2 local) {
   return decode_rgtc1_impl<T>(block, 4 * local.y + local.x);
}

#pragma endregion
#pragma region S3TC

///////////////////////////////////////////////////////////////////////////////
struct S3tc1Block {
   U16 color0;
   U16 color1;
   U32 data;
};

///////////////////////////////////////////////////////////////////////////////
struct S3tc2Block {
   U64 alpha;
   S3tc1Block rgb;
};

///////////////////////////////////////////////////////////////////////////////
struct S3tc3Block {
   Rgtc1Block alpha;
   S3tc1Block rgb;
};

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
S3tc1Block get_s3tc1_block(const ImageView& image, Coord block_coord) {
   S3tc1Block block;
   const void* ptr = image.data() + BlockOffset<ImageView, Coord>::offset(image, block_coord);
   std::memcpy(&block, ptr, sizeof(block));
   bo::static_to_host<bo::Little::value>(block.color0);
   bo::static_to_host<bo::Little::value>(block.color1);
   bo::static_to_host<bo::Little::value>(block.data);
   return block;
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
S3tc2Block get_s3tc2_block(const ImageView& image, Coord block_coord) {
   S3tc2Block block;
   const void* ptr = image.data() + BlockOffset<ImageView, Coord>::offset(image, block_coord);
   std::memcpy(&block, ptr, sizeof(block));
   bo::static_to_host<bo::Little::value>(block.alpha);
   bo::static_to_host<bo::Little::value>(block.rgb.color0);
   bo::static_to_host<bo::Little::value>(block.rgb.color1);
   bo::static_to_host<bo::Little::value>(block.rgb.data);
   return block;
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename ImageView>
S3tc3Block get_s3tc3_block(const ImageView& image, Coord block_coord) {
   S3tc3Block block;
   const void* ptr = image.data() + BlockOffset<ImageView, Coord>::offset(image, block_coord);
   std::memcpy(&block, ptr, sizeof(block));
   bo::static_to_host<bo::Little::value>(block.rgb.color0);
   bo::static_to_host<bo::Little::value>(block.rgb.color1);
   bo::static_to_host<bo::Little::value>(block.rgb.data);
   return block;
}

///////////////////////////////////////////////////////////////////////////////
inline std::pair<vec3, vec3> s3tc1_colors(S3tc1Block block) {
   return std::make_pair(
      vec3 {
         FieldRawNorm<U16, 5, FieldType::unorm>::decode(block.color0 >> 11),
         FieldRawNorm<U16, 6, FieldType::unorm>::decode((block.color0 >> 5) & 0x3f),
         FieldRawNorm<U16, 5, FieldType::unorm>::decode(block.color0 & 0x1f)
      },
      vec3 {
         FieldRawNorm<U16, 5, FieldType::unorm>::decode(block.color1 >> 11),
         FieldRawNorm<U16, 6, FieldType::unorm>::decode((block.color1 >> 5) & 0x3f),
         FieldRawNorm<U16, 5, FieldType::unorm>::decode(block.color1 & 0x1f)
      });
}

///////////////////////////////////////////////////////////////////////////////
inline vec3 decode_s3tc1_simple_linear(S3tc1Block block, U32 pixel_num) {
   auto color = s3tc1_colors(block);
   U32 code = (block.data >> (2 * pixel_num)) & 0x3;
   switch (code) {
      case 0: return vec4(color.first, 1.f);
      case 1: return vec4(color.second, 1.f);
      case 2: return vec4((color.first * 2.f + color.second) / 3.f, 1.f);
      case 3: return vec4((color.first + 2.f * color.second) / 3.f, 1.f);
   }
   assert(false);
   return vec3();
}

///////////////////////////////////////////////////////////////////////////////
inline vec3 decode_s3tc1_simple_srgb(S3tc1Block block, U32 pixel_num) {
   auto color = s3tc1_colors(block);
   U32 code = (block.data >> (2 * pixel_num)) & 0x3;
   switch (code) {
      case 0: return vec4(color.first, 1.f);
      case 1: return vec4(color.second, 1.f);
      case 2: return vec4(linear_to_srgb((srgb_to_linear(color.first) * 2.f + srgb_to_linear(color.second)) / 3.f), 1.f);
      case 3: return vec4(linear_to_srgb((srgb_to_linear(color.first) + 2.f * srgb_to_linear(color.second)) / 3.f), 1.f);
   }
   assert(false);
   return vec3();
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_s3tc1_linear(S3tc1Block block, uvec2 local, vec4 special_color) {
   auto color = s3tc1_colors(block);
   U32 code = (block.data >> (2 * (4 * local.y + local.x))) & 0x3;
   if (block.color0 > block.color1) {
      switch (code) {
         case 0: return vec4(color.first, 1.f);
         case 1: return vec4(color.second, 1.f);
         case 2: return vec4((color.first * 2.f + color.second) / 3.f, 1.f);
         case 3: return vec4((color.first + 2.f * color.second) / 3.f, 1.f);
      }
   } else {
      switch (code) {
         case 0: return vec4(color.first, 1.f);
         case 1: return vec4(color.second, 1.f);
         case 2: return vec4((color.first + color.second) / 2.f, 1.f);
         case 3: return special_color;
      }
   }
   assert(false);
   return vec4();
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_s3tc1_srgb(S3tc1Block block, uvec2 local, vec4 special_color) {
   auto color = s3tc1_colors(block);
   U32 code = (block.data >> (2 * (4 * local.y + local.x))) & 0x3;
   if (block.color0 > block.color1) {
      switch (code) {
         case 0: return vec4(color.first, 1.f);
         case 1: return vec4(color.second, 1.f);
         case 2: return vec4(linear_to_srgb((color.first * 2.f + color.second) / 3.f), 1.f);
         case 3: return vec4(linear_to_srgb((color.first + 2.f * color.second) / 3.f), 1.f);
      }
   } else {
      switch (code) {
         case 0: return vec4(color.first, 1.f);
         case 1: return vec4(color.second, 1.f);
         case 2: return vec4(linear_to_srgb((srgb_to_linear(color.first) + srgb_to_linear(color.second)) / 2.f), 1.f);
         case 3: return special_color;
      }
   }
   assert(false);
   return vec4();
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_s3tc2_linear(S3tc2Block block, uvec2 local) {
   auto pixel_num = 4 * local.y + local.x;
   U64 alpha = (block.alpha >> (4 * pixel_num)) & 0xf;
   F32 a = FieldRawNorm<U64, 4, FieldType::unorm>::decode(alpha);
   return vec4(decode_s3tc1_simple_linear(block.rgb, pixel_num), a);
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_s3tc2_srgb(S3tc2Block block, uvec2 local) {
   auto pixel_num = 4 * local.y + local.x;
   U64 alpha = (block.alpha >> (4 * pixel_num)) & 0xf;
   F32 a = FieldRawNorm<U64, 4, FieldType::unorm>::decode(alpha);
   return vec4(decode_s3tc1_simple_srgb(block.rgb, pixel_num), a);
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_s3tc3_linear(S3tc3Block block, uvec2 local) {
   auto pixel_num = 4 * local.y + local.x;
   return vec4(decode_s3tc1_simple_linear(block.rgb, pixel_num),
               decode_rgtc1_impl<FieldType::unorm>(block.alpha, pixel_num));
}

///////////////////////////////////////////////////////////////////////////////
inline vec4 decode_s3tc3_srgb(S3tc3Block block, uvec2 local) {
   auto pixel_num = 4 * local.y + local.x;
   return vec4(decode_s3tc1_simple_srgb(block.rgb, pixel_num),
               decode_rgtc1_impl<FieldType::unorm>(block.alpha, pixel_num));
}

#pragma endregion
#pragma region PixelRawNormAccessCompressed

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, BlockPacking Packing>
struct PixelRawNormAccessCompressed { };

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_s3tc1> {   // DXT1, BC1
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      std::pair<Coord, Coord> block_coords = to_block_coords(image, pixel_coord);
      S3tc1Block block = get_s3tc1_block(image, block_coords.first);
      uvec2 local = convert_coord<uvec2>(block_coords.second);
      vec4 special = image.format().components() == 4 ? vec4() : vec4(0, 0, 0, 1);
      return image.format().colorspace() == Colorspace::srgb ?
         decode_s3tc1_srgb(block, local, special) :
         decode_s3tc1_linear(block, local, special);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_s3tc2> {   // DXT2, DXT3, BC2
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      std::pair<Coord, Coord> block_coords = to_block_coords(image, pixel_coord);
      S3tc2Block block = get_s3tc2_block(image, block_coords.first);
      uvec2 local = convert_coord<uvec2>(block_coords.second);
      return image.format().colorspace() == Colorspace::srgb ?
         decode_s3tc2_srgb(block, local) :
         decode_s3tc2_linear(block, local);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_s3tc3> {   // DXT4, DXT5, BC3
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      std::pair<Coord, Coord> block_coords = to_block_coords(image, pixel_coord);
      S3tc3Block block = get_s3tc3_block(image, block_coords.first);
      uvec2 local = convert_coord<uvec2>(block_coords.second);
      return image.format().colorspace() == Colorspace::srgb ?
         decode_s3tc3_srgb(block, local) :
         decode_s3tc3_linear(block, local);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_rgtc1> {   // RGTC1, BC4
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      std::pair<Coord, Coord> block_coords = to_block_coords(image, pixel_coord);
      Rgtc1Block block = get_rgtc1_block(image, block_coords.first);
      uvec2 local = convert_coord<uvec2>(block_coords.second);

      F32 red;
      if (image.format().field_type(0) == FieldType::snorm) {
         red = decode_rgtc1<FieldType::snorm>(block, local);
      } else {
         red = decode_rgtc1<FieldType::unorm>(block, local);
      }

      return vec4(red, 0.f, 0.f, 1.f);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_rgtc2> {   // RGTC2, BC5
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      std::pair<Coord, Coord> block_coords = to_block_coords(image, pixel_coord);
      Rgtc2Block block = get_rgtc2_block(image, block_coords.first);
      uvec2 local = convert_coord<uvec2>(block_coords.second);

      F32 red, green;
      if (image.format().field_type(0) == FieldType::snorm) {
         red = decode_rgtc1<FieldType::snorm>(block.red, local);
      } else {
         red = decode_rgtc1<FieldType::unorm>(block.red, local);
      }
      if (image.format().field_type(1) == FieldType::snorm) {
         green = decode_rgtc1<FieldType::snorm>(block.green, local);
      } else {
         green = decode_rgtc1<FieldType::unorm>(block.green, local);
      }

      return vec4(red, green, 0.f, 1.f);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_bptc> {   // BPTC, BC6H, BC7
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      std::pair<Coord, Coord> block_coords = to_block_coords(image, pixel_coord);
      BptcBlock block = get_bptc_block(image, block_coords.first);
      uvec2 local = convert_coord<uvec2>(block_coords.second);

      if (image.format().field_type(0) == FieldType::unorm) {
         if (image.format().colorspace() == Colorspace::srgb) {
            return decode_bptc_unorm_srgb(block, local);
         } else {
            return decode_bptc_unorm_srgb(block, local);
         }
      } else {
         return decode_bptc_float(block, local, image.format().field_type(0) == FieldType::sfloat);
      }
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_etc1> {   // ETC1
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      // TODO
      return vec4(0, 0, 0, 1);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_etc2> {   // ETC2
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      // TODO
      return vec4(0, 0, 0, 1);
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord>
struct PixelRawNormAccessCompressed<ImageView, Coord, BlockPacking::c_astc> {   // ASTC
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      // TODO
      return vec4(0, 0, 0, 1);
   }
};

#pragma endregion
#pragma region PixelNormAccessCompressed

///////////////////////////////////////////////////////////////////////////////
template <typename ImageView, typename Coord, BlockPacking Packing>
struct PixelNormAccessCompressed {
   static vec4 get(const ImageView& image, Coord pixel_coord) {
      F32 data[6] = { 0.f, 0.f, 0.f, 0.f, 0.f, 1.f };
      const vec4 raw = PixelRawNormAccessCompressed<ImageView, Coord, Packing>::get(image, pixel_coord);
      std::memcpy(data, glm::value_ptr(raw), sizeof(vec4));
      const auto swizzles = image.format().swizzles();
      return vec4(data[static_cast<U8>(swizzles.r)],
                  data[static_cast<U8>(swizzles.g)],
                  data[static_cast<U8>(swizzles.b)],
                  data[static_cast<U8>(swizzles.a)]);
   }
};

#pragma endregion

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

         function is_compressed (t)  return t.n_fields == 0 end
         function not_compressed (t) return t.n_fields ~= 0 end
         function is_standard (t)    return t.n_fields ~= 0 and t.n_fields == t.n_words end

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
      auto field_types = image.format().field_types();
      glm::length_t fields = field_count(image.format().packing());
      FieldType field_type = static_cast<FieldType>(field_types[0]);
      for (glm::length_t c = 1; c < fields; ++c) {
         if (static_cast<FieldType>(field_types[c]) != field_type) {
            field_type = FieldType::none;
            break;
         }
      }

      if (field_type == FieldType::unorm) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', post_params = ', FieldType::unorm', func_name = 'get' }) !! 45 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, FieldType::unorm>::get;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, FieldType::unorm>::get;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, FieldType::unorm>::get;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, FieldType::unorm>::get;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, FieldType::unorm>::get;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, FieldType::unorm>::get;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, FieldType::unorm>::get;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, FieldType::unorm>::get;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, FieldType::unorm>::get;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, FieldType::unorm>::get;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, FieldType::unorm>::get;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, FieldType::unorm>::get;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, FieldType::unorm>::get;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, FieldType::unorm>::get;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, FieldType::unorm>::get;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, FieldType::unorm>::get;
            case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4, FieldType::unorm>::get;
            case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2, FieldType::unorm>::get;
            case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3, FieldType::unorm>::get;
            case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3, FieldType::unorm>::get;
            case BlockPacking::p_4_2_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_2_2, FieldType::unorm>::get;
            case BlockPacking::p_2_2_4:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_4, FieldType::unorm>::get;
            case BlockPacking::p_2_4_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_4_2, FieldType::unorm>::get;
            case BlockPacking::p_2_2_2_2:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_2_2, FieldType::unorm>::get;
            case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4, FieldType::unorm>::get;
            case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5, FieldType::unorm>::get;
            case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1, FieldType::unorm>::get;
            case BlockPacking::p_6_5_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_6_5_5, FieldType::unorm>::get;
            case BlockPacking::p_5_5_6:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_6, FieldType::unorm>::get;
            case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5, FieldType::unorm>::get;
            case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24, FieldType::unorm>::get;
            case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8, FieldType::unorm>::get;
            case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10, FieldType::unorm>::get;
            case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11, FieldType::unorm>::get;
            case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11, FieldType::unorm>::get;
            case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8, FieldType::unorm>::get;
            case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5, FieldType::unorm>::get;
            case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9, FieldType::unorm>::get;
            case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2, FieldType::unorm>::get;
            case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10, FieldType::unorm>::get;
            case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8, FieldType::unorm>::get;

            /* ######################### END OF GENERATED CODE ######################### */
         }
      } else if (field_type == FieldType::uint) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', post_params = ', FieldType::uint', func_name = 'get' }) !! 45 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, FieldType::uint>::get;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, FieldType::uint>::get;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, FieldType::uint>::get;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, FieldType::uint>::get;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, FieldType::uint>::get;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, FieldType::uint>::get;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, FieldType::uint>::get;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, FieldType::uint>::get;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, FieldType::uint>::get;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, FieldType::uint>::get;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, FieldType::uint>::get;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, FieldType::uint>::get;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, FieldType::uint>::get;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, FieldType::uint>::get;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, FieldType::uint>::get;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, FieldType::uint>::get;
            case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4, FieldType::uint>::get;
            case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2, FieldType::uint>::get;
            case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3, FieldType::uint>::get;
            case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3, FieldType::uint>::get;
            case BlockPacking::p_4_2_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_2_2, FieldType::uint>::get;
            case BlockPacking::p_2_2_4:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_4, FieldType::uint>::get;
            case BlockPacking::p_2_4_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_4_2, FieldType::uint>::get;
            case BlockPacking::p_2_2_2_2:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_2_2, FieldType::uint>::get;
            case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4, FieldType::uint>::get;
            case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5, FieldType::uint>::get;
            case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1, FieldType::uint>::get;
            case BlockPacking::p_6_5_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_6_5_5, FieldType::uint>::get;
            case BlockPacking::p_5_5_6:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_6, FieldType::uint>::get;
            case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5, FieldType::uint>::get;
            case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24, FieldType::uint>::get;
            case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8, FieldType::uint>::get;
            case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10, FieldType::uint>::get;
            case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11, FieldType::uint>::get;
            case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11, FieldType::uint>::get;
            case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8, FieldType::uint>::get;
            case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5, FieldType::uint>::get;
            case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9, FieldType::uint>::get;
            case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2, FieldType::uint>::get;
            case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10, FieldType::uint>::get;
            case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8, FieldType::uint>::get;

            /* ######################### END OF GENERATED CODE ######################### */
         }
      } else if (field_type == FieldType::sfloat) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = is_standard, pre_params = ', true', post_params = ', FieldType::sfloat', func_name = 'get' }) !! 20 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, FieldType::sfloat>::get;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, FieldType::sfloat>::get;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, FieldType::sfloat>::get;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, FieldType::sfloat>::get;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, FieldType::sfloat>::get;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, FieldType::sfloat>::get;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, FieldType::sfloat>::get;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, FieldType::sfloat>::get;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, FieldType::sfloat>::get;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, FieldType::sfloat>::get;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, FieldType::sfloat>::get;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, FieldType::sfloat>::get;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, FieldType::sfloat>::get;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, FieldType::sfloat>::get;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, FieldType::sfloat>::get;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, FieldType::sfloat>::get;

            /* ######################### END OF GENERATED CODE ######################### */
         }
      }
      switch (image.format().packing()) {
         /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', func_name = 'get' }) !! 45 */
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
         case BlockPacking::p_4_2_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_2_2>::get;
         case BlockPacking::p_2_2_4:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_4>::get;
         case BlockPacking::p_2_4_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_4_2>::get;
         case BlockPacking::p_2_2_2_2:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_2_2>::get;
         case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4>::get;
         case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5>::get;
         case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1>::get;
         case BlockPacking::p_6_5_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_6_5_5>::get;
         case BlockPacking::p_5_5_6:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_6>::get;
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
         default:
            assert(false);
            break;
      }
   } else {
      switch (image.format().packing()) {
         /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', false', func_name = 'get' }) !! 45 */
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
         case BlockPacking::p_4_2_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_4_2_2>::get;
         case BlockPacking::p_2_2_4:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_2_4>::get;
         case BlockPacking::p_2_4_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_4_2>::get;
         case BlockPacking::p_2_2_2_2:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_2_2_2>::get;
         case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_4_4_4_4>::get;
         case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_1_5_5_5>::get;
         case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_5_5_1>::get;
         case BlockPacking::p_6_5_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_6_5_5>::get;
         case BlockPacking::p_5_5_6:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_5_6>::get;
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
      auto field_types = image.format().field_types();
      glm::length_t fields = field_count(image.format().packing());
      FieldType field_type = static_cast<FieldType>(field_types[0]);
      for (glm::length_t c = 1; c < fields; ++c) {
         if (static_cast<FieldType>(field_types[c]) != field_type) {
            field_type = FieldType::none;
            break;
         }
      }

      if (field_type == FieldType::unorm) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', post_params = ', FieldType::unorm', func_name = 'put' }) !! 45 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, FieldType::unorm>::put;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, FieldType::unorm>::put;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, FieldType::unorm>::put;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, FieldType::unorm>::put;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, FieldType::unorm>::put;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, FieldType::unorm>::put;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, FieldType::unorm>::put;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, FieldType::unorm>::put;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, FieldType::unorm>::put;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, FieldType::unorm>::put;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, FieldType::unorm>::put;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, FieldType::unorm>::put;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, FieldType::unorm>::put;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, FieldType::unorm>::put;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, FieldType::unorm>::put;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, FieldType::unorm>::put;
            case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4, FieldType::unorm>::put;
            case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2, FieldType::unorm>::put;
            case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3, FieldType::unorm>::put;
            case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3, FieldType::unorm>::put;
            case BlockPacking::p_4_2_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_2_2, FieldType::unorm>::put;
            case BlockPacking::p_2_2_4:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_4, FieldType::unorm>::put;
            case BlockPacking::p_2_4_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_4_2, FieldType::unorm>::put;
            case BlockPacking::p_2_2_2_2:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_2_2, FieldType::unorm>::put;
            case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4, FieldType::unorm>::put;
            case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5, FieldType::unorm>::put;
            case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1, FieldType::unorm>::put;
            case BlockPacking::p_6_5_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_6_5_5, FieldType::unorm>::put;
            case BlockPacking::p_5_5_6:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_6, FieldType::unorm>::put;
            case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5, FieldType::unorm>::put;
            case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24, FieldType::unorm>::put;
            case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8, FieldType::unorm>::put;
            case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10, FieldType::unorm>::put;
            case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11, FieldType::unorm>::put;
            case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11, FieldType::unorm>::put;
            case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8, FieldType::unorm>::put;
            case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5, FieldType::unorm>::put;
            case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9, FieldType::unorm>::put;
            case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2, FieldType::unorm>::put;
            case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10, FieldType::unorm>::put;
            case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8, FieldType::unorm>::put;

            /* ######################### END OF GENERATED CODE ######################### */
         }
      } else if (field_type == FieldType::uint) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', post_params = ', FieldType::uint', func_name = 'put' }) !! 45 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, FieldType::uint>::put;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, FieldType::uint>::put;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, FieldType::uint>::put;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, FieldType::uint>::put;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, FieldType::uint>::put;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, FieldType::uint>::put;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, FieldType::uint>::put;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, FieldType::uint>::put;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, FieldType::uint>::put;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, FieldType::uint>::put;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, FieldType::uint>::put;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, FieldType::uint>::put;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, FieldType::uint>::put;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, FieldType::uint>::put;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, FieldType::uint>::put;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, FieldType::uint>::put;
            case BlockPacking::p_4_4:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4, FieldType::uint>::put;
            case BlockPacking::p_3_3_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_3_2, FieldType::uint>::put;
            case BlockPacking::p_2_3_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_3_3, FieldType::uint>::put;
            case BlockPacking::p_3_2_3:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_3_2_3, FieldType::uint>::put;
            case BlockPacking::p_4_2_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_2_2, FieldType::uint>::put;
            case BlockPacking::p_2_2_4:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_4, FieldType::uint>::put;
            case BlockPacking::p_2_4_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_4_2, FieldType::uint>::put;
            case BlockPacking::p_2_2_2_2:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_2_2, FieldType::uint>::put;
            case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4, FieldType::uint>::put;
            case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5, FieldType::uint>::put;
            case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1, FieldType::uint>::put;
            case BlockPacking::p_6_5_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_6_5_5, FieldType::uint>::put;
            case BlockPacking::p_5_5_6:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_6, FieldType::uint>::put;
            case BlockPacking::p_5_6_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_6_5, FieldType::uint>::put;
            case BlockPacking::p_8_24:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_24, FieldType::uint>::put;
            case BlockPacking::p_24_8:        return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_24_8, FieldType::uint>::put;
            case BlockPacking::p_11_11_10:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_11_10, FieldType::uint>::put;
            case BlockPacking::p_10_11_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_11_11, FieldType::uint>::put;
            case BlockPacking::p_11_10_11:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_11_10_11, FieldType::uint>::put;
            case BlockPacking::p_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_8_8_8_8, FieldType::uint>::put;
            case BlockPacking::p_9_9_9_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_9_9_9_5, FieldType::uint>::put;
            case BlockPacking::p_5_9_9_9:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_9_9_9, FieldType::uint>::put;
            case BlockPacking::p_10_10_10_2:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_10_10_10_2, FieldType::uint>::put;
            case BlockPacking::p_2_10_10_10:  return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_10_10_10, FieldType::uint>::put;
            case BlockPacking::s_32_p_24_8:   return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_p_24_8, FieldType::uint>::put;

            /* ######################### END OF GENERATED CODE ######################### */
         }
      } else if (field_type == FieldType::sfloat) {
         switch (image.format().packing()) {
            /*!! write_template('packing_switch', { pred = is_standard, pre_params = ', true', post_params = ', FieldType::sfloat', func_name = 'put' }) !! 20 */
            /* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
            case BlockPacking::s_8:           return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8, FieldType::sfloat>::put;
            case BlockPacking::s_8_8:         return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8, FieldType::sfloat>::put;
            case BlockPacking::s_8_8_8:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8, FieldType::sfloat>::put;
            case BlockPacking::s_8_8_8_8:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_8_8_8_8, FieldType::sfloat>::put;
            case BlockPacking::s_16:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16, FieldType::sfloat>::put;
            case BlockPacking::s_16_16:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16, FieldType::sfloat>::put;
            case BlockPacking::s_16_16_16:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16, FieldType::sfloat>::put;
            case BlockPacking::s_16_16_16_16: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_16_16_16_16, FieldType::sfloat>::put;
            case BlockPacking::s_32:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32, FieldType::sfloat>::put;
            case BlockPacking::s_32_32:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32, FieldType::sfloat>::put;
            case BlockPacking::s_32_32_32:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32, FieldType::sfloat>::put;
            case BlockPacking::s_32_32_32_32: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_32_32_32_32, FieldType::sfloat>::put;
            case BlockPacking::s_64:          return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64, FieldType::sfloat>::put;
            case BlockPacking::s_64_64:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64, FieldType::sfloat>::put;
            case BlockPacking::s_64_64_64:    return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64, FieldType::sfloat>::put;
            case BlockPacking::s_64_64_64_64: return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::s_64_64_64_64, FieldType::sfloat>::put;

            /* ######################### END OF GENERATED CODE ######################### */
         }
      }
      switch (image.format().packing()) {
         /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', true', func_name = 'put' }) !! 45 */
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
         case BlockPacking::p_4_2_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_2_2>::put;
         case BlockPacking::p_2_2_4:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_4>::put;
         case BlockPacking::p_2_4_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_4_2>::put;
         case BlockPacking::p_2_2_2_2:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_2_2_2_2>::put;
         case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_4_4_4_4>::put;
         case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_1_5_5_5>::put;
         case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_5_1>::put;
         case BlockPacking::p_6_5_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_6_5_5>::put;
         case BlockPacking::p_5_5_6:       return detail::PixelNormAccessUncompressed<ImageView, Coord, true, BlockPacking::p_5_5_6>::put;
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
         /*!! write_template('packing_switch', { pred = not_compressed, pre_params = ', false', func_name = 'put' }) !! 45 */
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
         case BlockPacking::p_4_2_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_4_2_2>::put;
         case BlockPacking::p_2_2_4:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_2_4>::put;
         case BlockPacking::p_2_4_2:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_4_2>::put;
         case BlockPacking::p_2_2_2_2:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_2_2_2_2>::put;
         case BlockPacking::p_4_4_4_4:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_4_4_4_4>::put;
         case BlockPacking::p_1_5_5_5:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_1_5_5_5>::put;
         case BlockPacking::p_5_5_5_1:     return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_5_5_1>::put;
         case BlockPacking::p_6_5_5:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_6_5_5>::put;
         case BlockPacking::p_5_5_6:       return detail::PixelNormAccessUncompressed<ImageView, Coord, false, BlockPacking::p_5_5_6>::put;
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
