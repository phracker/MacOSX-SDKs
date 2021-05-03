//===-- metal_types.h -----------------------------------------------------===//
// Copyright (c) 2014-2016 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __METAL_TYPES_H
#define __METAL_TYPES_H

#include <metal_config>

#define METAL_ASM
// The noduplicate attribute is not available on LLVM 600, use noduplicate to
// achieve the same goals.
#define METAL_CONVERGENT __attribute__((no_duplicate))
#define METAL_DEPRECATED(M) __attribute__((deprecated(M)))
#define METAL_ENABLE_IF(P, M) __attribute__((enable_if(P, M)))
#define METAL_FUNC inline __attribute__((__always_inline__))
#define METAL_INTERNAL
#define METAL_NON_NULL_RETURN __attribute__((returns_nonnull))
#define METAL_NORETURN __attribute__((noreturn))
#define METAL_PURE __attribute__((pure))
#define METAL_UNAVAILABLE(M) __attribute__((unavailable(M)))

// TODO: This is only used by the builtin library. To be removed -- see
// <rdar://problem/26107016>.
#define __INLINE__ __attribute__((__always_inline__))

// TODO: This is only used by the NVIDIA inline library.  To be removed once
// nvidia remove it uses <rdar://problem/26359043>
#define METAL_INTERNAL_NO_DUP __attribute__((no_duplicate))


namespace metal {

// This is intended to be used by the METAL_CONST_ARG macro. Each type that may
// be interested in being used in constant argument checks must specialize this
// trait.
template <typename T>
struct _constarg_traits {
  // Must return true if T is a constant argument, false otherwise. A possible
  // specialization would be to force a constexpr computation on t, such as
  // the t == t expression.
  constexpr static METAL_INTERNAL bool check(const thread T &t) { return false; }
  constexpr static METAL_INTERNAL bool check(const threadgroup T &t) { return false; }
  constexpr static METAL_INTERNAL bool check(const constant T &t) { return false; }
  constexpr static METAL_INTERNAL bool check(const device T &t) { return false; }
};

#define METAL_CONST_ARG(A)                                                     \
  METAL_ENABLE_IF(_constarg_traits<decltype(A)>::check(A),                     \
                  "'" #A "' argument must be known at compile-time")

// This is an internal implementation detail and is subject to change.
template <typename T, int numElt> using vec =
  __attribute__(( ext_vector_type(numElt))) T;

}

// 2.2 Metal Vector Data Types
#include <simd/vector_types.h>

// metal_packed_vector depends on vec<T,N> above.
#include <metal_packed_vector>

// 2.1 Metal Scalar Types
namespace metal {

typedef char           int8_t;
typedef unsigned char  uint8_t;
typedef short          int16_t;
typedef unsigned short uint16_t;
typedef int            int32_t;
typedef unsigned int   uint32_t;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

// __metal_internal_int64_t is an internal implementation detail and is subject
// to change.
using ptrdiff_t = __metal_internal_int64_t;
using size_t = unsigned __metal_internal_int64_t;

}

#include <metal_array>

#if defined(__HAVE_TESSELLATION__)
#include <metal_tessellation>
#endif

#if defined(__HAVE_FUNCTION_CONSTANTS__)
#define is_function_constant_defined(c) __builtin_air64_is_fc_defined(c)
#endif // defined(__HAVE_FUNCTION_CONSTANTS__)

namespace metal {
// 2.9 Metal Packed Vector Data Types
  typedef packed_vec<char, 2> packed_char2;
  typedef packed_vec<char, 3> packed_char3;
  typedef packed_vec<char, 4> packed_char4;
  typedef packed_vec<uchar, 2> packed_uchar2;
  typedef packed_vec<uchar, 3> packed_uchar3;
  typedef packed_vec<uchar, 4> packed_uchar4;
  typedef packed_vec<short, 2> packed_short2;
  typedef packed_vec<short, 3> packed_short3;
  typedef packed_vec<short, 4> packed_short4;
  typedef packed_vec<ushort, 2> packed_ushort2;
  typedef packed_vec<ushort, 3> packed_ushort3;
  typedef packed_vec<ushort, 4> packed_ushort4;
  typedef packed_vec<int, 2> packed_int2;
  typedef packed_vec<int, 3> packed_int3;
  typedef packed_vec<int, 4> packed_int4;
  typedef packed_vec<uint, 2> packed_uint2;
  typedef packed_vec<uint, 3> packed_uint3;
  typedef packed_vec<uint, 4> packed_uint4;
  typedef packed_vec<half, 2> packed_half2;
  typedef packed_vec<half, 3> packed_half3;
  typedef packed_vec<half, 4> packed_half4;
  typedef packed_vec<float, 2> packed_float2;
  typedef packed_vec<float, 3> packed_float3;
  typedef packed_vec<float, 4> packed_float4;
  typedef struct __Unsupported_Type__Do_not_use_packed_double2_on_this_device
    packed_double2;
  typedef struct __Unsupported_Type__Do_not_use_packed_double3_on_this_device
    packed_double3;
  typedef struct __Unsupported_Type__Do_not_use_packed_double4_on_this_device
    packed_double4;

#define _AIR_MEM_SCOPE_WORK_GROUP 0x1
#define _AIR_MEM_SCOPE_DEVICE 0x2

#define _AIR_MEM_ORDER_RELAXED 0x0

// 5.12.1 Memory Order
enum memory_order {
  memory_order_relaxed = _AIR_MEM_ORDER_RELAXED,
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
template <>
struct _constarg_traits<memory_order> {
  constexpr static METAL_INTERNAL bool check(memory_order order) { return order == order; }
};
#pragma clang diagnostic pop

// Defend reserved types
typedef struct __Reserved_Name__Do_not_use_quad         quad;
typedef struct __Reserved_Name__Do_not_use_quad2        quad2;
typedef struct __Reserved_Name__Do_not_use_quad3        quad3;
typedef struct __Reserved_Name__Do_not_use_quad4        quad4;
typedef struct __Reserved_Name__Do_not_use_complex      complex;
typedef struct __Reserved_Name__Do_not_use_imaginary    imaginary;

// Some useful constargs specializations.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
template <>
struct _constarg_traits<int> {
  constexpr static METAL_INTERNAL bool check(int a) { return a == a; }
};
template <>
struct _constarg_traits<uint> {
  constexpr static METAL_INTERNAL bool check(uint a) { return a == a; }
};
template <>
struct _constarg_traits<short> {
  constexpr static METAL_INTERNAL bool check(short a) { return a == a; }
};
template <>
struct _constarg_traits<ushort> {
  constexpr static METAL_INTERNAL bool check(ushort a) { return a == a; }
};
#pragma clang diagnostic pop
} // end namespace metal

// FIXME: Determine if these constants should be defined here and we should
// switch to using an Metal flags instead of CL flags.
#define CHAR_BIT    8
#define	SCHAR_MAX	127		/* min value for a signed char */
#define	SCHAR_MIN	(-128)		/* max value for a signed char */
#define	UCHAR_MAX	255		/* max value for an unsigned char */
#define	CHAR_MAX	SCHAR_MAX		/* max value for a char */
#define	CHAR_MIN	SCHAR_MIN		/* min value for a char */
#define	USHRT_MAX	65535		/* max value for an unsigned short */
#define	SHRT_MAX	32767		/* max value for a short */
#define	SHRT_MIN	(-32768)	/* min value for a short */
#define	UINT_MAX	0xffffffff	/* max value for an unsigned int */
#define	INT_MAX		2147483647	/* max value for an int */
#define	INT_MIN		(-2147483647-1)	/* min value for an int */

#define FLT_DIG         6
#define FLT_MANT_DIG    24
#define FLT_MAX_10_EXP  +38
#define FLT_MAX_EXP     +128
#define FLT_MIN_10_EXP  -37
#define FLT_MIN_EXP     -125
#define FLT_RADIX       2
#define FLT_MAX         0x1.fffffep127f
#define FLT_MIN         0x1.0p-126f
#define FLT_EPSILON     0x1.0p-23f

#define FP_ILOGB0       INT_MIN
#define FP_ILOGBNAN     INT_MIN

#define MAXFLOAT        0x1.fffffep+127f
#define HUGE_VALF       __builtin_huge_valf()
#define INFINITY        __builtin_inff()
#define NAN             __builtin_nanf("0x7fc00000")

#define M_E_F         2.71828182845904523536028747135266250f   /* e */
#define M_LOG2E_F     1.44269504088896340735992468100189214f   /* log 2e */
#define M_LOG10E_F    0.434294481903251827651128918916605082f  /* log 10e */
#define M_LN2_F       0.693147180559945309417232121458176568f  /* log e2 */
#define M_LN10_F      2.3025850929940456840179914546843642f    /* log e10 */
#define M_PI_F        3.14159265358979323846264338327950288f   /* pi */
#define M_PI_2_F      1.57079632679489661923132169163975144f   /* pi/2 */
#define M_PI_4_F      0.785398163397448309615660845819875721f  /* pi/4 */
#define M_1_PI_F      0.318309886183790671537767526745028724f  /* 1/pi */
#define M_2_PI_F      0.636619772367581343075535053490057448f  /* 2/pi */
#define M_2_SQRTPI_F  1.12837916709551257389615890312154517f   /* 2/sqrt(pi) */
#define M_SQRT2_F     1.41421356237309504880168872420969808f   /* sqrt(2) */
#define M_SQRT1_2_F   0.707106781186547524400844362104849039f  /* 1/sqrt(2) */

#define HALF_DIG 2
#define HALF_MANT_DIG    11
#define HALF_MAX_10_EXP  +4
#define HALF_MAX_EXP     +16
#define HALF_MIN_10_EXP  -4
#define HALF_MIN_EXP     -13
#define HALF_RADIX       2
#define HALF_MAX         0x1.ffcp15h
#define HALF_MIN         0x1.0p-14h
#define HALF_EPSILON     0x1.0p-10h

#define MAXHALF          0x1.ffcp15h
#define HUGE_VALH        ((half)INFINITY)

#define M_E_H         2.71828182845904523536028747135266250h   /* e */
#define M_LOG2E_H     1.44269504088896340735992468100189214h   /* log 2e */
#define M_LOG10E_H    0.434294481903251827651128918916605082h  /* log 10e */
#define M_LN2_H       0.693147180559945309417232121458176568h  /* log e2 */
#define M_LN10_H      2.3025850929940456840179914546843642h    /* log e10 */
#define M_PI_H        3.14159265358979323846264338327950288h   /* pi */
#define M_PI_2_H      1.57079632679489661923132169163975144h   /* pi/2 */
#define M_PI_4_H      0.785398163397448309615660845819875721h  /* pi/4 */
#define M_1_PI_H      0.318309886183790671537767526745028724h  /* 1/pi */
#define M_2_PI_H      0.636619772367581343075535053490057448h  /* 2/pi */
#define M_2_SQRTPI_H  1.12837916709551257389615890312154517h   /* 2/sqrt(pi) */
#define M_SQRT2_H     1.41421356237309504880168872420969808h   /* sqrt(2) */
#define M_SQRT1_2_H   0.707106781186547524400844362104849039h  /* 1/sqrt(2) */


#endif  // __METAL_TYPES_H
