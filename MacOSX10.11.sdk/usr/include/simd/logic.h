/*  Copyright (c) 2014 Apple, Inc. All rights reserved.
 *
 *  The interfaces declared in this header provide logical and bitwise
 *  operations on vectors.  Some of these function operate elementwise,
 *  and some produce a scalar result that depends on all lanes of the input.
 *
 *  For functions returning a boolean value, the return type in C and
 *  Objective-C is _Bool; for C++ it is bool.
 *
 *      Function                    Result
 *      ------------------------------------------------------------------
 *      vector_all(comparison)      True if and only if the comparison is true
 *                                  in every vector lane.  e.g.:
 *
 *                                      if (vector_all(x == 0.0f)) {
 *                                          // executed if every lane of x
 *                                          // contains zero.
 *                                      }
 *
 *                                  The precise function of vector_all is to
 *                                  return the high-order bit of the result
 *                                  of a horizontal bitwise AND of all vector
 *                                  lanes.
 *
 *      vector_any(comparison)      True if and only if the comparison is true
 *                                  in at least one vector lane.  e.g.:
 *
 *                                      if (vector_any(x < 0.0f)) {
 *                                          // executed if any lane of x
 *                                          // contains a negative value.
 *                                      }
 *
 *                                  The precise function of vector_all is to
 *                                  return the high-order bit of the result
 *                                  of a horizontal bitwise OR of all vector
 *                                  lanes.
 *
 *      vector_select(x,y,mask)     For each lane in the result, selects the
 *                                  corresponding element of x if the high-
 *                                  order bit of the corresponding element of
 *                                  mask is 0, and the corresponding element
 *                                  of y otherwise.
 *
 *      vector_bitselect(x,y,mask)  For each bit in the result, selects the
 *                                  corresponding bit of x if the corresponding
 *                                  bit of mask is clear, and the corresponding
 *                                  of y otherwise.
 *
 *  In C++, these functions are available under the SIMD:: namespace:
 *
 *      C++ Function                    Equivalent C Function
 *      --------------------------------------------------------------------
 *      SIMD::all(comparison)           vector_all(comparison)
 *      SIMD::any(comparison)           vector_any(comparison)
 *      SIMD::select(x,y,mask)          vector_select(x,y,mask)
 *      SIMD::bitselect(x,y,mask)       vector_bitselect(x,y,mask)
 */

#ifndef __SIMD_LOGIC_HEADER__
#define __SIMD_LOGIC_HEADER__

#include <simd/internal.h>
#if __SIMD_REQUIRED_COMPILER_FEATURES__
#include <simd/vector_types.h>
#include <stdint.h>

#ifdef __cplusplus
#    define __SIMD_BOOLEAN_TYPE__ bool
extern "C" {
#else
#    define __SIMD_BOOLEAN_TYPE__ _Bool
#endif

static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char32 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short32 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long2 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long3 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long4 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long8 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar32 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort32 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ulong2 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ulong3 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ulong4 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ulong8 __x);

static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char32 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short32 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long2 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long3 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long4 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long8 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar32 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort32 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint2  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint3  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint4  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint8  __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint16 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ulong2 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ulong3 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ulong4 __x);
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ulong8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ vector_select(vector_float2  __x, vector_float2  __y, vector_int2  __z);
static vector_float3  __SIMD_ATTRIBUTES__ vector_select(vector_float3  __x, vector_float3  __y, vector_int3  __z);
static vector_float4  __SIMD_ATTRIBUTES__ vector_select(vector_float4  __x, vector_float4  __y, vector_int4  __z);
static vector_float8  __SIMD_ATTRIBUTES__ vector_select(vector_float8  __x, vector_float8  __y, vector_int8  __z);
static vector_float16 __SIMD_ATTRIBUTES__ vector_select(vector_float16 __x, vector_float16 __y, vector_int16 __z);
static vector_double2 __SIMD_ATTRIBUTES__ vector_select(vector_double2 __x, vector_double2 __y, vector_long2 __z);
static vector_double3 __SIMD_ATTRIBUTES__ vector_select(vector_double3 __x, vector_double3 __y, vector_long3 __z);
static vector_double4 __SIMD_ATTRIBUTES__ vector_select(vector_double4 __x, vector_double4 __y, vector_long4 __z);
static vector_double8 __SIMD_ATTRIBUTES__ vector_select(vector_double8 __x, vector_double8 __y, vector_long8 __z);

static vector_char2    __SIMD_ATTRIBUTES__ vector_bitselect(vector_char2    __x, vector_char2    __y, vector_char2   __z);
static vector_char3    __SIMD_ATTRIBUTES__ vector_bitselect(vector_char3    __x, vector_char3    __y, vector_char3   __z);
static vector_char4    __SIMD_ATTRIBUTES__ vector_bitselect(vector_char4    __x, vector_char4    __y, vector_char4   __z);
static vector_char8    __SIMD_ATTRIBUTES__ vector_bitselect(vector_char8    __x, vector_char8    __y, vector_char8   __z);
static vector_char16   __SIMD_ATTRIBUTES__ vector_bitselect(vector_char16   __x, vector_char16   __y, vector_char16  __z);
static vector_char32   __SIMD_ATTRIBUTES__ vector_bitselect(vector_char32   __x, vector_char32   __y, vector_char32  __z);
static vector_uchar2   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar2   __x, vector_uchar2   __y, vector_char2   __z);
static vector_uchar3   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar3   __x, vector_uchar3   __y, vector_char3   __z);
static vector_uchar4   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar4   __x, vector_uchar4   __y, vector_char4   __z);
static vector_uchar8   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar8   __x, vector_uchar8   __y, vector_char8   __z);
static vector_uchar16  __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar16  __x, vector_uchar16  __y, vector_char16  __z);
static vector_uchar32  __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar32  __x, vector_uchar32  __y, vector_char32  __z);
static vector_short2   __SIMD_ATTRIBUTES__ vector_bitselect(vector_short2   __x, vector_short2   __y, vector_short2  __z);
static vector_short3   __SIMD_ATTRIBUTES__ vector_bitselect(vector_short3   __x, vector_short3   __y, vector_short3  __z);
static vector_short4   __SIMD_ATTRIBUTES__ vector_bitselect(vector_short4   __x, vector_short4   __y, vector_short4  __z);
static vector_short8   __SIMD_ATTRIBUTES__ vector_bitselect(vector_short8   __x, vector_short8   __y, vector_short8  __z);
static vector_short16  __SIMD_ATTRIBUTES__ vector_bitselect(vector_short16  __x, vector_short16  __y, vector_short16 __z);
static vector_short32  __SIMD_ATTRIBUTES__ vector_bitselect(vector_short32  __x, vector_short32  __y, vector_short32 __z);
static vector_ushort2  __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort2  __x, vector_ushort2  __y, vector_short2  __z);
static vector_ushort3  __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort3  __x, vector_ushort3  __y, vector_short3  __z);
static vector_ushort4  __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort4  __x, vector_ushort4  __y, vector_short4  __z);
static vector_ushort8  __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort8  __x, vector_ushort8  __y, vector_short8  __z);
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort16 __x, vector_ushort16 __y, vector_short16 __z);
static vector_ushort32 __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort32 __x, vector_ushort32 __y, vector_short32 __z);
static vector_int2     __SIMD_ATTRIBUTES__ vector_bitselect(vector_int2     __x, vector_int2     __y, vector_int2    __z);
static vector_int3     __SIMD_ATTRIBUTES__ vector_bitselect(vector_int3     __x, vector_int3     __y, vector_int3    __z);
static vector_int4     __SIMD_ATTRIBUTES__ vector_bitselect(vector_int4     __x, vector_int4     __y, vector_int4    __z);
static vector_int8     __SIMD_ATTRIBUTES__ vector_bitselect(vector_int8     __x, vector_int8     __y, vector_int8    __z);
static vector_int16    __SIMD_ATTRIBUTES__ vector_bitselect(vector_int16    __x, vector_int16    __y, vector_int16   __z);
static vector_uint2    __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint2    __x, vector_uint2    __y, vector_int2    __z);
static vector_uint3    __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint3    __x, vector_uint3    __y, vector_int3    __z);
static vector_uint4    __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint4    __x, vector_uint4    __y, vector_int4    __z);
static vector_uint8    __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint8    __x, vector_uint8    __y, vector_int8    __z);
static vector_uint16   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint16   __x, vector_uint16   __y, vector_int16   __z);
static vector_float2   __SIMD_ATTRIBUTES__ vector_bitselect(vector_float2   __x, vector_float2   __y, vector_int2    __z);
static vector_float3   __SIMD_ATTRIBUTES__ vector_bitselect(vector_float3   __x, vector_float3   __y, vector_int3    __z);
static vector_float4   __SIMD_ATTRIBUTES__ vector_bitselect(vector_float4   __x, vector_float4   __y, vector_int4    __z);
static vector_float8   __SIMD_ATTRIBUTES__ vector_bitselect(vector_float8   __x, vector_float8   __y, vector_int8    __z);
static vector_float16  __SIMD_ATTRIBUTES__ vector_bitselect(vector_float16  __x, vector_float16  __y, vector_int16   __z);
static vector_long2    __SIMD_ATTRIBUTES__ vector_bitselect(vector_long2    __x, vector_long2    __y, vector_long2   __z);
static vector_long3    __SIMD_ATTRIBUTES__ vector_bitselect(vector_long3    __x, vector_long3    __y, vector_long3   __z);
static vector_long4    __SIMD_ATTRIBUTES__ vector_bitselect(vector_long4    __x, vector_long4    __y, vector_long4   __z);
static vector_long8    __SIMD_ATTRIBUTES__ vector_bitselect(vector_long8    __x, vector_long8    __y, vector_long8   __z);
static vector_ulong2   __SIMD_ATTRIBUTES__ vector_bitselect(vector_ulong2   __x, vector_ulong2   __y, vector_long2   __z);
static vector_ulong3   __SIMD_ATTRIBUTES__ vector_bitselect(vector_ulong3   __x, vector_ulong3   __y, vector_long3   __z);
static vector_ulong4   __SIMD_ATTRIBUTES__ vector_bitselect(vector_ulong4   __x, vector_ulong4   __y, vector_long4   __z);
static vector_ulong8   __SIMD_ATTRIBUTES__ vector_bitselect(vector_ulong8   __x, vector_ulong8   __y, vector_long8   __z);
static vector_double2  __SIMD_ATTRIBUTES__ vector_bitselect(vector_double2  __x, vector_double2  __y, vector_long2   __z);
static vector_double3  __SIMD_ATTRIBUTES__ vector_bitselect(vector_double3  __x, vector_double3  __y, vector_long3   __z);
static vector_double4  __SIMD_ATTRIBUTES__ vector_bitselect(vector_double4  __x, vector_double4  __y, vector_long4   __z);
static vector_double8  __SIMD_ATTRIBUTES__ vector_bitselect(vector_double8  __x, vector_double8  __y, vector_long8   __z);

#ifdef __cplusplus
} /* extern "C" */

namespace simd {
    template <typename inttypeN> static __SIMD_INLINE__ __SIMD_BOOLEAN_TYPE__ all(const inttypeN predicate) { return ::vector_all(predicate); }
    template <typename inttypeN> static __SIMD_INLINE__ __SIMD_BOOLEAN_TYPE__ any(const inttypeN predicate) { return ::vector_any(predicate); }
    template <typename inttypeN, typename fptypeN> static __SIMD_INLINE__ fptypeN select(const fptypeN x, const fptypeN y, const inttypeN predicate) { return ::vector_select(x,y,predicate); }
    template <typename inttypeN, typename typeN> static __SIMD_INLINE__ typeN bitselect(const typeN x, const typeN y, const inttypeN mask) { return ::vector_bitselect(x,y,mask); }
}

extern "C" {
#endif /* __cplusplus */

#pragma mark - Implementations

static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char2  __x) { union { uint16_t __i; vector_char2  __v; } __u = { .__v = __x }; return (__u.__i & 0x8080) == 0x8080; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char2  __x) { union { uint16_t __i; vector_char2  __v; } __u = { .__v = __x }; return __u.__i & 0x8080; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char3  __x) { union { uint32_t __i; vector_char3  __v; } __u = { .__v = __x }; return (__u.__i & 0x808080) == 0x808080; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char3  __x) { union { uint32_t __i; vector_char3  __v; } __u = { .__v = __x }; return __u.__i & 0x808080; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char4  __x) { union { uint32_t __i; vector_char4  __v; } __u = { .__v = __x }; return (__u.__i & 0x80808080U) == 0x80808080U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char4  __x) { union { uint32_t __i; vector_char4  __v; } __u = { .__v = __x }; return __u.__i & 0x80808080U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char8  __x) { union { uint64_t __i; vector_char8  __v; } __u = { .__v = __x }; return (__u.__i & 0x8080808080808080U) == 0x8080808080808080U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char8  __x) { union { uint64_t __i; vector_char8  __v; } __u = { .__v = __x }; return __u.__i & 0x8080808080808080U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short2 __x) { union { uint32_t __i; vector_short2 __v; } __u = { .__v = __x }; return (__u.__i & 0x80008000U) == 0x80008000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short2 __x) { union { uint32_t __i; vector_short2 __v; } __u = { .__v = __x }; return __u.__i & 0x80008000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short3 __x) { union { uint64_t __i; vector_short3 __v; } __u = { .__v = __x }; return (__u.__i & 0x800080008000U) == 0x800080008000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short3 __x) { union { uint64_t __i; vector_short3 __v; } __u = { .__v = __x }; return __u.__i & 0x800080008000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short4 __x) { union { uint64_t __i; vector_short4 __v; } __u = { .__v = __x }; return (__u.__i & 0x8000800080008000U) == 0x8000800080008000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short4 __x) { union { uint64_t __i; vector_short4 __v; } __u = { .__v = __x }; return __u.__i & 0x8000800080008000U; }
#if defined __SSE2__
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char16 __x) { return _mm_movemask_epi8(__x) == 0xffff; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char16 __x) { return _mm_movemask_epi8(__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short8 __x) { return (_mm_movemask_epi8(__x) & 0xaaaa) == 0xaaaa; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short8 __x) { return _mm_movemask_epi8(__x) & 0xaaaa; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int2  __x) { vector_int4 __x4; __x4.lo  = __x; return (_mm_movemask_ps(__x4) & 0x3) == 0x3; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int2  __x) { vector_int4 __x4; __x4.lo  = __x; return (_mm_movemask_ps(__x4) & 0x3); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int3  __x) { vector_int4 __x4; __x4.xyz = __x; return (_mm_movemask_ps(__x4) & 0x7) == 0x7; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int3  __x) { vector_int4 __x4; __x4.xyz = __x; return (_mm_movemask_ps(__x4) & 0x7); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int4  __x) { return _mm_movemask_ps(__x) == 0xf; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int4  __x) { return _mm_movemask_ps(__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long2 __x) { return _mm_movemask_pd(__x) == 0x3; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long2 __x) { return _mm_movemask_pd(__x); }
#elif defined __arm64__
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char16 __x) { return vminvq_u8(__x) & 0x80; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char16 __x) { return vmaxvq_u8(__x) & 0x80; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short8 __x) { return vminvq_u16(__x) & 0x8000; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short8 __x) { return vmaxvq_u16(__x) & 0x8000; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int2  __x) { return vminv_u32(__x) & 0x80000000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int2  __x) { return vmaxv_u32(__x) & 0x80000000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int3  __x) { return vector_all(__x.xyzz); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int3  __x) { return vector_any(__x.xyzz); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int4  __x) { return vminvq_u32(__x) & 0x80000000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int4  __x) { return vmaxvq_u32(__x) & 0x80000000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long2 __x) { return (__x.x & __x.y) & 0x8000000000000000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long2 __x) { return (__x.x | __x.y) & 0x8000000000000000U; }
#else
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char16 __x) { return vector_all(__x.hi & __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char16 __x) { return vector_any(__x.hi | __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short8 __x) { return vector_all(__x.hi & __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short8 __x) { return vector_any(__x.hi | __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int2  __x) { union { uint64_t __i; vector_int2 __v; } __u = { .__v = __x }; return (__u.__i & 0x8000000080000000U) == 0x8000000080000000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int2  __x) { union { uint64_t __i; vector_int2 __v; } __u = { .__v = __x }; return __u.__i & 0x8000000080000000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int3  __x) { return vector_all(__x.xyzz); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int3  __x) { return vector_any(__x.xyzz); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int4  __x) { return vector_all(__x.hi & __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int4  __x) { return vector_any(__x.hi | __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long2 __x) { return (__x.x & __x.y) & 0x8000000000000000U; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long2 __x) { return (__x.x | __x.y) & 0x8000000000000000U; }
#endif
#if defined __AVX__
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int8  __x) { return _mm256_movemask_ps(__x) == 0xff; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int8  __x) { return _mm256_movemask_ps(__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long3 __x) { vector_long4 __x4; __x4.xyz = __x; return (_mm256_movemask_pd(__x4) & 0x7) == 0x7; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long3 __x) { vector_long4 __x4; __x4.xyz = __x; return (_mm256_movemask_pd(__x4) & 0x7); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long4 __x) { return _mm256_movemask_pd(__x) == 0xf; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long4 __x) { return _mm256_movemask_pd(__x); }
#else
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int8  __x) { return vector_all(__x.lo & __x.hi); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int8  __x) { return vector_any(__x.hi | __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long3 __x) { return vector_all(__x.xyzz); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long3 __x) { return vector_any(__x.xyzz); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long4 __x) { return vector_all(__x.lo & __x.hi); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long4 __x) { return vector_any(__x.hi | __x.lo); }
#endif
#if defined __AVX2__
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char32  __x) { return _mm256_movemask_epi8(__x) == 0xffffffffU; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char32  __x) { return _mm256_movemask_epi8(__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short16 __x) { return (_mm256_movemask_epi8(__x) & 0xaaaaaaaaU) == 0xaaaaaaaaU; }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short16 __x) { return _mm256_movemask_epi8(__x) & 0xaaaaaaaaU; }
#else
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_char32  __x) { return vector_all(__x.lo & __x.hi); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_char32  __x) { return vector_any(__x.hi | __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short16 __x) { return vector_all(__x.lo & __x.hi); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short16 __x) { return vector_any(__x.hi | __x.lo); }
#endif
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_short32 __x) { return vector_all(__x.lo & __x.hi); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_short32 __x) { return vector_any(__x.hi | __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_int16 __x) { return vector_all(__x.lo & __x.hi); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_int16 __x) { return vector_any(__x.hi | __x.lo); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_long8 __x) { return vector_all(__x.lo & __x.hi); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_long8 __x) { return vector_any(__x.hi | __x.lo); }

static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar2   __x) { return vector_all((vector_char2)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar3   __x) { return vector_all((vector_char3)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar4   __x) { return vector_all((vector_char4)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar8   __x) { return vector_all((vector_char8)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar16  __x) { return vector_all((vector_char16)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uchar32  __x) { return vector_all((vector_char32)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort2  __x) { return vector_all((vector_short2)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort3  __x) { return vector_all((vector_short3)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort4  __x) { return vector_all((vector_short4)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort8  __x) { return vector_all((vector_short8)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort16 __x) { return vector_all((vector_short16)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ushort32 __x) { return vector_all((vector_short32)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint2    __x) { return vector_all((vector_int2)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint3    __x) { return vector_all((vector_int3)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint4    __x) { return vector_all((vector_int4)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint8    __x) { return vector_all((vector_int8)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_uint16   __x) { return vector_all((vector_int16)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ulong2   __x) { return vector_all((vector_long2)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ulong3   __x) { return vector_all((vector_long3)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ulong4   __x) { return vector_all((vector_long4)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_all(vector_ulong8   __x) { return vector_all((vector_long8)__x); }

static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar2   __x) { return vector_any((vector_char2)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar3   __x) { return vector_any((vector_char3)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar4   __x) { return vector_any((vector_char4)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar8   __x) { return vector_any((vector_char8)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar16  __x) { return vector_any((vector_char16)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uchar32  __x) { return vector_any((vector_char32)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort2  __x) { return vector_any((vector_short2)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort3  __x) { return vector_any((vector_short3)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort4  __x) { return vector_any((vector_short4)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort8  __x) { return vector_any((vector_short8)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort16 __x) { return vector_any((vector_short16)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ushort32 __x) { return vector_any((vector_short32)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint2    __x) { return vector_any((vector_int2)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint3    __x) { return vector_any((vector_int3)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint4    __x) { return vector_any((vector_int4)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint8    __x) { return vector_any((vector_int8)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_uint16   __x) { return vector_any((vector_int16)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ulong2   __x) { return vector_any((vector_long2)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ulong3   __x) { return vector_any((vector_long3)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ulong4   __x) { return vector_any((vector_long4)__x); }
static __SIMD_BOOLEAN_TYPE__ __SIMD_ATTRIBUTES__ vector_any(vector_ulong8   __x) { return vector_any((vector_long8)__x); }

static vector_float2  __SIMD_ATTRIBUTES__ vector_select(vector_float2 __x, vector_float2 __y, vector_int2 __z) { vector_float4 __x4, __y4, __r4; vector_int4 __z4; __x4.lo  = __x; __y4.lo  = __y; __z4.lo  = __z; __r4 = vector_select(__x4,__y4,__z4); return __r4.lo; }
static vector_float3  __SIMD_ATTRIBUTES__ vector_select(vector_float3 __x, vector_float3 __y, vector_int3 __z) { vector_float4 __x4, __y4, __r4; vector_int4 __z4; __x4.xyz = __x; __y4.xyz = __y; __z4.xyz = __z; __r4 = vector_select(__x4,__y4,__z4); return __r4.xyz; }
#if defined __SSE4_1__
static vector_float4  __SIMD_ATTRIBUTES__ vector_select(vector_float4  __x, vector_float4  __y, vector_int4  __z) { return _mm_blendv_ps(__x,__y,__z); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_select(vector_double2 __x, vector_double2 __y, vector_long2 __z) { return _mm_blendv_pd(__x,__y,__z); }
#elif defined __SSE2__
static vector_float4  __SIMD_ATTRIBUTES__ vector_select(vector_float4  __x, vector_float4  __y, vector_int4  __z) { return vector_bitselect(__x, __y, __z >> 31); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_select(vector_double2 __x, vector_double2 __y, vector_long2 __z) { return vector_bitselect(__x, __y, (vector_long2)((vector_int4)_mm_shuffle_ps(__z,__z,0xf5) >> 31)); }
#else
static vector_float4  __SIMD_ATTRIBUTES__ vector_select(vector_float4  __x, vector_float4  __y, vector_int4  __z) { return vector_bitselect(__x, __y, __z >> 31); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_select(vector_double2 __x, vector_double2 __y, vector_long2 __z) { return vector_bitselect(__x, __y, __z >> 63); }
#endif
static vector_double3 __SIMD_ATTRIBUTES__ vector_select(vector_double3 __x, vector_double3 __y, vector_long3 __z) { vector_double4 __x4, __y4, __r4; vector_long4 __z4; __x4.xyz = __x; __y4.xyz = __y; __z4.xyz = __z; __r4 = vector_select(__x4,__y4,__z4); return __r4.xyz; }
#if defined __AVX__
static vector_float8  __SIMD_ATTRIBUTES__ vector_select(vector_float8  __x, vector_float8  __y, vector_int8  __z) { return _mm256_blendv_ps(__x, __y, __z); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_select(vector_double4 __x, vector_double4 __y, vector_long4 __z) { return _mm256_blendv_pd(__x, __y, __z); }
#else
static vector_float8  __SIMD_ATTRIBUTES__ vector_select(vector_float8  __x, vector_float8  __y, vector_int8  __z) { vector_float8  __r;  __r.lo = vector_select(__x.lo,__y.lo,__z.lo); __r.hi = vector_select(__x.hi,__y.hi,__z.hi); return __r; }
static vector_double4 __SIMD_ATTRIBUTES__ vector_select(vector_double4 __x, vector_double4 __y, vector_long4 __z) { vector_double4 __r;  __r.lo = vector_select(__x.lo,__y.lo,__z.lo); __r.hi = vector_select(__x.hi,__y.hi,__z.hi); return __r; }
#endif
static vector_float16 __SIMD_ATTRIBUTES__ vector_select(vector_float16 __x, vector_float16 __y, vector_int16 __z) { vector_float16 __r;  __r.lo = vector_select(__x.lo,__y.lo,__z.lo); __r.hi = vector_select(__x.hi,__y.hi,__z.hi); return __r; }
static vector_double8 __SIMD_ATTRIBUTES__ vector_select(vector_double8 __x, vector_double8 __y, vector_long8 __z) { vector_double8 __r;  __r.lo = vector_select(__x.lo,__y.lo,__z.lo); __r.hi = vector_select(__x.hi,__y.hi,__z.hi); return __r; }

static vector_char2    __SIMD_ATTRIBUTES__ vector_bitselect(vector_char2    __x, vector_char2    __y, vector_char2   __z) { return (__x & ~__z) | (__y & __z); }
static vector_char3    __SIMD_ATTRIBUTES__ vector_bitselect(vector_char3    __x, vector_char3    __y, vector_char3   __z) { return (__x & ~__z) | (__y & __z); }
static vector_char4    __SIMD_ATTRIBUTES__ vector_bitselect(vector_char4    __x, vector_char4    __y, vector_char4   __z) { return (__x & ~__z) | (__y & __z); }
static vector_char8    __SIMD_ATTRIBUTES__ vector_bitselect(vector_char8    __x, vector_char8    __y, vector_char8   __z) { return (__x & ~__z) | (__y & __z); }
static vector_char16   __SIMD_ATTRIBUTES__ vector_bitselect(vector_char16   __x, vector_char16   __y, vector_char16  __z) { return (__x & ~__z) | (__y & __z); }
static vector_char32   __SIMD_ATTRIBUTES__ vector_bitselect(vector_char32   __x, vector_char32   __y, vector_char32  __z) { return (__x & ~__z) | (__y & __z); }
static vector_uchar2   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar2   __x, vector_uchar2   __y, vector_char2   __z) { return (vector_uchar2)vector_bitselect((vector_char2)__x, (vector_char2)__y, __z); }
static vector_uchar3   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar3   __x, vector_uchar3   __y, vector_char3   __z) { return (vector_uchar3)vector_bitselect((vector_char3)__x, (vector_char3)__y, __z); }
static vector_uchar4   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar4   __x, vector_uchar4   __y, vector_char4   __z) { return (vector_uchar4)vector_bitselect((vector_char4)__x, (vector_char4)__y, __z); }
static vector_uchar8   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar8   __x, vector_uchar8   __y, vector_char8   __z) { return (vector_uchar8)vector_bitselect((vector_char8)__x, (vector_char8)__y, __z); }
static vector_uchar16  __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar16  __x, vector_uchar16  __y, vector_char16  __z) { return (vector_uchar16)vector_bitselect((vector_char16)__x,(vector_char16)__y, __z); }
static vector_uchar32  __SIMD_ATTRIBUTES__ vector_bitselect(vector_uchar32  __x, vector_uchar32  __y, vector_char32  __z) { return (vector_uchar32)vector_bitselect((vector_char32)__x,(vector_char32)__y, __z); }
static vector_short2   __SIMD_ATTRIBUTES__ vector_bitselect(vector_short2   __x, vector_short2   __y, vector_short2  __z) { return (__x & ~__z) | (__y & __z); }
static vector_short3   __SIMD_ATTRIBUTES__ vector_bitselect(vector_short3   __x, vector_short3   __y, vector_short3  __z) { return (__x & ~__z) | (__y & __z); }
static vector_short4   __SIMD_ATTRIBUTES__ vector_bitselect(vector_short4   __x, vector_short4   __y, vector_short4  __z) { return (__x & ~__z) | (__y & __z); }
static vector_short8   __SIMD_ATTRIBUTES__ vector_bitselect(vector_short8   __x, vector_short8   __y, vector_short8  __z) { return (__x & ~__z) | (__y & __z); }
static vector_short16  __SIMD_ATTRIBUTES__ vector_bitselect(vector_short16  __x, vector_short16  __y, vector_short16 __z) { return (__x & ~__z) | (__y & __z); }
static vector_short32  __SIMD_ATTRIBUTES__ vector_bitselect(vector_short32  __x, vector_short32  __y, vector_short32 __z) { return (__x & ~__z) | (__y & __z); }
static vector_ushort2  __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort2  __x, vector_ushort2  __y, vector_short2  __z) { return (vector_ushort2)vector_bitselect((vector_short2)__x, (vector_short2)__y, __z); }
static vector_ushort3  __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort3  __x, vector_ushort3  __y, vector_short3  __z) { return (vector_ushort3)vector_bitselect((vector_short3)__x, (vector_short3)__y, __z); }
static vector_ushort4  __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort4  __x, vector_ushort4  __y, vector_short4  __z) { return (vector_ushort4)vector_bitselect((vector_short4)__x, (vector_short4)__y, __z); }
static vector_ushort8  __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort8  __x, vector_ushort8  __y, vector_short8  __z) { return (vector_ushort8)vector_bitselect((vector_short8)__x, (vector_short8)__y, __z); }
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort16 __x, vector_ushort16 __y, vector_short16 __z) { return (vector_ushort16)vector_bitselect((vector_short16)__x,(vector_short16)__y, __z); }
static vector_ushort32 __SIMD_ATTRIBUTES__ vector_bitselect(vector_ushort32 __x, vector_ushort32 __y, vector_short32 __z) { return (vector_ushort32)vector_bitselect((vector_short32)__x,(vector_short32)__y, __z); }
static vector_int2     __SIMD_ATTRIBUTES__ vector_bitselect(vector_int2     __x, vector_int2     __y, vector_int2    __z) { return (__x & ~__z) | (__y & __z); }
static vector_int3     __SIMD_ATTRIBUTES__ vector_bitselect(vector_int3     __x, vector_int3     __y, vector_int3    __z) { return (__x & ~__z) | (__y & __z); }
static vector_int4     __SIMD_ATTRIBUTES__ vector_bitselect(vector_int4     __x, vector_int4     __y, vector_int4    __z) { return (__x & ~__z) | (__y & __z); }
static vector_int8     __SIMD_ATTRIBUTES__ vector_bitselect(vector_int8     __x, vector_int8     __y, vector_int8    __z) { return (__x & ~__z) | (__y & __z); }
static vector_int16    __SIMD_ATTRIBUTES__ vector_bitselect(vector_int16    __x, vector_int16    __y, vector_int16   __z) { return (__x & ~__z) | (__y & __z); }
static vector_uint2    __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint2    __x, vector_uint2    __y, vector_int2    __z) { return (vector_uint2)vector_bitselect((vector_int2)__x, (vector_int2)__y, __z); }
static vector_uint3    __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint3    __x, vector_uint3    __y, vector_int3    __z) { return (vector_uint3)vector_bitselect((vector_int3)__x, (vector_int3)__y, __z); }
static vector_uint4    __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint4    __x, vector_uint4    __y, vector_int4    __z) { return (vector_uint4)vector_bitselect((vector_int4)__x, (vector_int4)__y, __z); }
static vector_uint8    __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint8    __x, vector_uint8    __y, vector_int8    __z) { return (vector_uint8)vector_bitselect((vector_int8)__x, (vector_int8)__y, __z); }
static vector_uint16   __SIMD_ATTRIBUTES__ vector_bitselect(vector_uint16   __x, vector_uint16   __y, vector_int16   __z) { return (vector_uint16)vector_bitselect((vector_int16)__x,(vector_int16)__y, __z); }
static vector_float2   __SIMD_ATTRIBUTES__ vector_bitselect(vector_float2   __x, vector_float2   __y, vector_int2    __z) { return (vector_float2)vector_bitselect((vector_int2)__x, (vector_int2)__y, __z); }
static vector_float3   __SIMD_ATTRIBUTES__ vector_bitselect(vector_float3   __x, vector_float3   __y, vector_int3    __z) { return (vector_float3)vector_bitselect((vector_int3)__x, (vector_int3)__y, __z); }
static vector_float4   __SIMD_ATTRIBUTES__ vector_bitselect(vector_float4   __x, vector_float4   __y, vector_int4    __z) { return (vector_float4)vector_bitselect((vector_int4)__x, (vector_int4)__y, __z); }
static vector_float8   __SIMD_ATTRIBUTES__ vector_bitselect(vector_float8   __x, vector_float8   __y, vector_int8    __z) { return (vector_float8)vector_bitselect((vector_int8)__x, (vector_int8)__y, __z); }
static vector_float16  __SIMD_ATTRIBUTES__ vector_bitselect(vector_float16  __x, vector_float16  __y, vector_int16   __z) { return (vector_float16)vector_bitselect((vector_int16)__x,(vector_int16)__y, __z); }
static vector_long2    __SIMD_ATTRIBUTES__ vector_bitselect(vector_long2    __x, vector_long2    __y, vector_long2   __z) { return (__x & ~__z) | (__y & __z); }
static vector_long3    __SIMD_ATTRIBUTES__ vector_bitselect(vector_long3    __x, vector_long3    __y, vector_long3   __z) { return (__x & ~__z) | (__y & __z); }
static vector_long4    __SIMD_ATTRIBUTES__ vector_bitselect(vector_long4    __x, vector_long4    __y, vector_long4   __z) { return (__x & ~__z) | (__y & __z); }
static vector_long8    __SIMD_ATTRIBUTES__ vector_bitselect(vector_long8    __x, vector_long8    __y, vector_long8   __z) { return (__x & ~__z) | (__y & __z); }
static vector_ulong2   __SIMD_ATTRIBUTES__ vector_bitselect(vector_ulong2   __x, vector_ulong2   __y, vector_long2   __z) { return (vector_ulong2)vector_bitselect((vector_long2)__x, (vector_long2)__y, __z); }
static vector_ulong3   __SIMD_ATTRIBUTES__ vector_bitselect(vector_ulong3   __x, vector_ulong3   __y, vector_long3   __z) { return (vector_ulong3)vector_bitselect((vector_long3)__x, (vector_long3)__y, __z); }
static vector_ulong4   __SIMD_ATTRIBUTES__ vector_bitselect(vector_ulong4   __x, vector_ulong4   __y, vector_long4   __z) { return (vector_ulong4)vector_bitselect((vector_long4)__x, (vector_long4)__y, __z); }
static vector_ulong8   __SIMD_ATTRIBUTES__ vector_bitselect(vector_ulong8   __x, vector_ulong8   __y, vector_long8   __z) { return (vector_ulong8)vector_bitselect((vector_long8)__x, (vector_long8)__y, __z); }
static vector_double2  __SIMD_ATTRIBUTES__ vector_bitselect(vector_double2  __x, vector_double2  __y, vector_long2   __z) { return (vector_double2)vector_bitselect((vector_long2)__x, (vector_long2)__y, __z); }
static vector_double3  __SIMD_ATTRIBUTES__ vector_bitselect(vector_double3  __x, vector_double3  __y, vector_long3   __z) { return (vector_double3)vector_bitselect((vector_long3)__x, (vector_long3)__y, __z); }
static vector_double4  __SIMD_ATTRIBUTES__ vector_bitselect(vector_double4  __x, vector_double4  __y, vector_long4   __z) { return (vector_double4)vector_bitselect((vector_long4)__x, (vector_long4)__y, __z); }
static vector_double8  __SIMD_ATTRIBUTES__ vector_bitselect(vector_double8  __x, vector_double8  __y, vector_long8   __z) { return (vector_double8)vector_bitselect((vector_long8)__x, (vector_long8)__y, __z); }

#ifdef __cplusplus
}
#endif
#endif /* __SIMD_REQUIRED_COMPILER_FEATURES__ */
#endif /* __SIMD_LOGIC_HEADER__ */
