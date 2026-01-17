/*  Copyright (c) 2014 Apple, Inc. All rights reserved.
 *
 *  The interfaces declared in this header provide "common" elementwise
 *  operations that are neither math nor logic functions.  These are available
 *  only for floating-point vectors and scalars, except for min, max, abs,
 *  and clamp which also support integer vectors.
 *
 *      vector_abs(x)           Absolute value of x.  Also available as fabs
 *                              for floating-point vectors.  If x is the
 *                              smallest signed integer, x is returned.
 *
 *      vector_max(x,y)         Returns the maximum of x and y.  Also available
 *                              as fmax for floating-point vectors.
 *
 *      vector_min(x,y)         Returns the minimum of x and y.  Also available
 *                              as fmin for floating-point vectors.
 *
 *      vector_clamp(x,min,max) x clamped to the range [min, max].
 *
 *      vector_sign(x)          -1 if x is less than zero, 0 if x is zero or
 *                              NaN, and +1 if x is greater than zero.
 *
 *      vector_mix(x,y,t)       If t is not in the range [0,1], the result is
 *                              undefined.  Otherwise the result is x+(y-x)*t,
 *                              which linearly interpolates between x and y.
 *
 *      vector_recip(x)         An approximation to 1/x.  If x is very near the
 *                              limits of representable values, or is infinity
 *                              or NaN, the result is undefined.  There are
 *                              two variants of this function:
 *
 *                                  vector_precise_recip(x)
 *
 *                              and
 *
 *                                  vector_fast_recip(x).
 *
 *                              The "precise" variant is accurate to a few ULPs,
 *                              whereas the "fast" variant may have as little
 *                              as 11 bits of accuracy in float and about 22
 *                              bits in double.
 *
 *                              The function vector_recip(x) resolves to
 *                              vector_precise_recip(x) ordinarily, but to
 *                              vector_fast_recip(x) when used in a translation
 *                              unit compiled with -ffast-math (when
 *                              -ffast-math is in effect, you may still use the
 *                              precise version of this function by calling it
 *                              explicitly by name).
 *
 *      vector_rsqrt(x)         An approximation to 1/sqrt(x).  If x is
 *                              infinity or NaN, the result is undefined.
 *                              There are two variants of this function:
 *
 *                                  vector_precise_rsqrt(x)
 *
 *                              and
 *
 *                                  vector_fast_rsqrt(x).
 *
 *                              The "precise" variant is accurate to a few ULPs,
 *                              whereas the "fast" variant may have as little
 *                              as 11 bits of accuracy in float and about 22
 *                              bits in double.
 *
 *                              The function vector_rsqrt(x) resolves to
 *                              vector_precise_rsqrt(x) ordinarily, but to
 *                              vector_fast_rsqrt(x) when used in a translation
 *                              unit compiled with -ffast-math (when
 *                              -ffast-math is in effect, you may still use the
 *                              precise version of this function by calling it
 *                              explicitly by name).
 *
 *      vector_fract(x)         The "fractional part" of x, which lies strictly
 *                              in the range [0, 0x1.fffffep-1].
 *
 *      vector_step(edge,x)     0 if x < edge, and 1 otherwise.
 *
 *      vector_smoothstep(edge0,edge1,x) 0 if x <= edge0, 1 if x >= edge1, and
 *                              a Hermite interpolation between 0 and 1 if
 *                              edge0 < x < edge1.
 *
 *  The following common functions are available in the simd:: namespace:
 *
 *      C++ Function                    Equivalent C Function
 *      --------------------------------------------------------------------
 *      simd::abs(x)                    vector_abs(x)
 *      simd::max(x)                    vector_max(x)
 *      simd::min(x)                    vector_min(x)
 *      simd::clamp(x,min,max)          vector_clamp(x,min,max)
 *      simd::sign(x)                   vector_sign(x)
 *      simd::mix(x)                    vector_mix(x)
 *      simd::recip(x)                  vector_recip(x)
 *      simd::rsqrt(x)                  vector_rsqrt(x)
 *      simd::Fast::sqrt(x)             vector_fast_sqrt(x)
 *      simd::fract(x)                  vector_fract(x)
 *      simd::step(edge,x)              vector_step(edge,x)
 *      simd::smoothstep(e0,e1,x)       vector_smoothstep(e0,e1,x)
 *
 *      simd::precise::recip(x)         vector_precise_recip(x)
 *      simd::precise::rsqrt(x)         vector_precise_rsqrt(x)
 *
 *      simd::fast::recip(x)            vector_fast_recip(x)
 *      simd::fast::rsqrt(x)            vector_fast_rsqrt(x)
 */

#ifndef __SIMD_COMMON_HEADER__
#define __SIMD_COMMON_HEADER__

#include <simd/internal.h>
#if __SIMD_REQUIRED_COMPILER_FEATURES__
#include <simd/vector_types.h>
#include <simd/logic.h>
#include <simd/math.h>

#ifdef __cplusplus
extern "C" {
#endif

static vector_char2   __SIMD_ATTRIBUTES__ vector_abs(vector_char2   __x);
static vector_char3   __SIMD_ATTRIBUTES__ vector_abs(vector_char3   __x);
static vector_char4   __SIMD_ATTRIBUTES__ vector_abs(vector_char4   __x);
static vector_char8   __SIMD_ATTRIBUTES__ vector_abs(vector_char8   __x);
static vector_char16  __SIMD_ATTRIBUTES__ vector_abs(vector_char16  __x);
static vector_char32  __SIMD_ATTRIBUTES__ vector_abs(vector_char32  __x);
static vector_short2  __SIMD_ATTRIBUTES__ vector_abs(vector_short2  __x);
static vector_short3  __SIMD_ATTRIBUTES__ vector_abs(vector_short3  __x);
static vector_short4  __SIMD_ATTRIBUTES__ vector_abs(vector_short4  __x);
static vector_short8  __SIMD_ATTRIBUTES__ vector_abs(vector_short8  __x);
static vector_short16 __SIMD_ATTRIBUTES__ vector_abs(vector_short16 __x);
static vector_short32 __SIMD_ATTRIBUTES__ vector_abs(vector_short32 __x);
static vector_int2    __SIMD_ATTRIBUTES__ vector_abs(vector_int2    __x);
static vector_int3    __SIMD_ATTRIBUTES__ vector_abs(vector_int3    __x);
static vector_int4    __SIMD_ATTRIBUTES__ vector_abs(vector_int4    __x);
static vector_int8    __SIMD_ATTRIBUTES__ vector_abs(vector_int8    __x);
static vector_int16   __SIMD_ATTRIBUTES__ vector_abs(vector_int16   __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_abs(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_abs(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_abs(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_abs(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_abs(vector_float16 __x);
static vector_long2   __SIMD_ATTRIBUTES__ vector_abs(vector_long2   __x);
static vector_long3   __SIMD_ATTRIBUTES__ vector_abs(vector_long3   __x);
static vector_long4   __SIMD_ATTRIBUTES__ vector_abs(vector_long4   __x);
static vector_long8   __SIMD_ATTRIBUTES__ vector_abs(vector_long8   __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_abs(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_abs(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_abs(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_abs(vector_double8 __x);

static vector_char2    __SIMD_ATTRIBUTES__ vector_max(vector_char2    __x, vector_char2    __y);
static vector_char3    __SIMD_ATTRIBUTES__ vector_max(vector_char3    __x, vector_char3    __y);
static vector_char4    __SIMD_ATTRIBUTES__ vector_max(vector_char4    __x, vector_char4    __y);
static vector_char8    __SIMD_ATTRIBUTES__ vector_max(vector_char8    __x, vector_char8    __y);
static vector_char16   __SIMD_ATTRIBUTES__ vector_max(vector_char16   __x, vector_char16   __y);
static vector_char32   __SIMD_ATTRIBUTES__ vector_max(vector_char32   __x, vector_char32   __y);
static vector_uchar2   __SIMD_ATTRIBUTES__ vector_max(vector_uchar2   __x, vector_uchar2   __y);
static vector_uchar3   __SIMD_ATTRIBUTES__ vector_max(vector_uchar3   __x, vector_uchar3   __y);
static vector_uchar4   __SIMD_ATTRIBUTES__ vector_max(vector_uchar4   __x, vector_uchar4   __y);
static vector_uchar8   __SIMD_ATTRIBUTES__ vector_max(vector_uchar8   __x, vector_uchar8   __y);
static vector_uchar16  __SIMD_ATTRIBUTES__ vector_max(vector_uchar16  __x, vector_uchar16  __y);
static vector_uchar32  __SIMD_ATTRIBUTES__ vector_max(vector_uchar32  __x, vector_uchar32  __y);
static vector_short2   __SIMD_ATTRIBUTES__ vector_max(vector_short2   __x, vector_short2   __y);
static vector_short3   __SIMD_ATTRIBUTES__ vector_max(vector_short3   __x, vector_short3   __y);
static vector_short4   __SIMD_ATTRIBUTES__ vector_max(vector_short4   __x, vector_short4   __y);
static vector_short8   __SIMD_ATTRIBUTES__ vector_max(vector_short8   __x, vector_short8   __y);
static vector_short16  __SIMD_ATTRIBUTES__ vector_max(vector_short16  __x, vector_short16  __y);
static vector_short32  __SIMD_ATTRIBUTES__ vector_max(vector_short32  __x, vector_short32  __y);
static vector_ushort2  __SIMD_ATTRIBUTES__ vector_max(vector_ushort2  __x, vector_ushort2  __y);
static vector_ushort3  __SIMD_ATTRIBUTES__ vector_max(vector_ushort3  __x, vector_ushort3  __y);
static vector_ushort4  __SIMD_ATTRIBUTES__ vector_max(vector_ushort4  __x, vector_ushort4  __y);
static vector_ushort8  __SIMD_ATTRIBUTES__ vector_max(vector_ushort8  __x, vector_ushort8  __y);
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_max(vector_ushort16 __x, vector_ushort16 __y);
static vector_ushort32 __SIMD_ATTRIBUTES__ vector_max(vector_ushort32 __x, vector_ushort32 __y);
static vector_int2     __SIMD_ATTRIBUTES__ vector_max(vector_int2     __x, vector_int2     __y);
static vector_int3     __SIMD_ATTRIBUTES__ vector_max(vector_int3     __x, vector_int3     __y);
static vector_int4     __SIMD_ATTRIBUTES__ vector_max(vector_int4     __x, vector_int4     __y);
static vector_int8     __SIMD_ATTRIBUTES__ vector_max(vector_int8     __x, vector_int8     __y);
static vector_int16    __SIMD_ATTRIBUTES__ vector_max(vector_int16    __x, vector_int16    __y);
static vector_uint2    __SIMD_ATTRIBUTES__ vector_max(vector_uint2    __x, vector_uint2    __y);
static vector_uint3    __SIMD_ATTRIBUTES__ vector_max(vector_uint3    __x, vector_uint3    __y);
static vector_uint4    __SIMD_ATTRIBUTES__ vector_max(vector_uint4    __x, vector_uint4    __y);
static vector_uint8    __SIMD_ATTRIBUTES__ vector_max(vector_uint8    __x, vector_uint8    __y);
static vector_uint16   __SIMD_ATTRIBUTES__ vector_max(vector_uint16   __x, vector_uint16   __y);
static vector_float2   __SIMD_ATTRIBUTES__ vector_max(vector_float2   __x, vector_float2   __y);
static vector_float3   __SIMD_ATTRIBUTES__ vector_max(vector_float3   __x, vector_float3   __y);
static vector_float4   __SIMD_ATTRIBUTES__ vector_max(vector_float4   __x, vector_float4   __y);
static vector_float8   __SIMD_ATTRIBUTES__ vector_max(vector_float8   __x, vector_float8   __y);
static vector_float16  __SIMD_ATTRIBUTES__ vector_max(vector_float16  __x, vector_float16  __y);
static vector_long2    __SIMD_ATTRIBUTES__ vector_max(vector_long2    __x, vector_long2    __y);
static vector_long3    __SIMD_ATTRIBUTES__ vector_max(vector_long3    __x, vector_long3    __y);
static vector_long4    __SIMD_ATTRIBUTES__ vector_max(vector_long4    __x, vector_long4    __y);
static vector_long8    __SIMD_ATTRIBUTES__ vector_max(vector_long8    __x, vector_long8    __y);
static vector_ulong2   __SIMD_ATTRIBUTES__ vector_max(vector_ulong2   __x, vector_ulong2   __y);
static vector_ulong3   __SIMD_ATTRIBUTES__ vector_max(vector_ulong3   __x, vector_ulong3   __y);
static vector_ulong4   __SIMD_ATTRIBUTES__ vector_max(vector_ulong4   __x, vector_ulong4   __y);
static vector_ulong8   __SIMD_ATTRIBUTES__ vector_max(vector_ulong8   __x, vector_ulong8   __y);
static vector_double2  __SIMD_ATTRIBUTES__ vector_max(vector_double2  __x, vector_double2  __y);
static vector_double3  __SIMD_ATTRIBUTES__ vector_max(vector_double3  __x, vector_double3  __y);
static vector_double4  __SIMD_ATTRIBUTES__ vector_max(vector_double4  __x, vector_double4  __y);
static vector_double8  __SIMD_ATTRIBUTES__ vector_max(vector_double8  __x, vector_double8  __y);

static vector_char2    __SIMD_ATTRIBUTES__ vector_min(vector_char2    __x, vector_char2    __y);
static vector_char3    __SIMD_ATTRIBUTES__ vector_min(vector_char3    __x, vector_char3    __y);
static vector_char4    __SIMD_ATTRIBUTES__ vector_min(vector_char4    __x, vector_char4    __y);
static vector_char8    __SIMD_ATTRIBUTES__ vector_min(vector_char8    __x, vector_char8    __y);
static vector_char16   __SIMD_ATTRIBUTES__ vector_min(vector_char16   __x, vector_char16   __y);
static vector_char32   __SIMD_ATTRIBUTES__ vector_min(vector_char32   __x, vector_char32   __y);
static vector_uchar2   __SIMD_ATTRIBUTES__ vector_min(vector_uchar2   __x, vector_uchar2   __y);
static vector_uchar3   __SIMD_ATTRIBUTES__ vector_min(vector_uchar3   __x, vector_uchar3   __y);
static vector_uchar4   __SIMD_ATTRIBUTES__ vector_min(vector_uchar4   __x, vector_uchar4   __y);
static vector_uchar8   __SIMD_ATTRIBUTES__ vector_min(vector_uchar8   __x, vector_uchar8   __y);
static vector_uchar16  __SIMD_ATTRIBUTES__ vector_min(vector_uchar16  __x, vector_uchar16  __y);
static vector_uchar32  __SIMD_ATTRIBUTES__ vector_min(vector_uchar32  __x, vector_uchar32  __y);
static vector_short2   __SIMD_ATTRIBUTES__ vector_min(vector_short2   __x, vector_short2   __y);
static vector_short3   __SIMD_ATTRIBUTES__ vector_min(vector_short3   __x, vector_short3   __y);
static vector_short4   __SIMD_ATTRIBUTES__ vector_min(vector_short4   __x, vector_short4   __y);
static vector_short8   __SIMD_ATTRIBUTES__ vector_min(vector_short8   __x, vector_short8   __y);
static vector_short16  __SIMD_ATTRIBUTES__ vector_min(vector_short16  __x, vector_short16  __y);
static vector_short32  __SIMD_ATTRIBUTES__ vector_min(vector_short32  __x, vector_short32  __y);
static vector_ushort2  __SIMD_ATTRIBUTES__ vector_min(vector_ushort2  __x, vector_ushort2  __y);
static vector_ushort3  __SIMD_ATTRIBUTES__ vector_min(vector_ushort3  __x, vector_ushort3  __y);
static vector_ushort4  __SIMD_ATTRIBUTES__ vector_min(vector_ushort4  __x, vector_ushort4  __y);
static vector_ushort8  __SIMD_ATTRIBUTES__ vector_min(vector_ushort8  __x, vector_ushort8  __y);
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_min(vector_ushort16 __x, vector_ushort16 __y);
static vector_ushort32 __SIMD_ATTRIBUTES__ vector_min(vector_ushort32 __x, vector_ushort32 __y);
static vector_int2     __SIMD_ATTRIBUTES__ vector_min(vector_int2     __x, vector_int2     __y);
static vector_int3     __SIMD_ATTRIBUTES__ vector_min(vector_int3     __x, vector_int3     __y);
static vector_int4     __SIMD_ATTRIBUTES__ vector_min(vector_int4     __x, vector_int4     __y);
static vector_int8     __SIMD_ATTRIBUTES__ vector_min(vector_int8     __x, vector_int8     __y);
static vector_int16    __SIMD_ATTRIBUTES__ vector_min(vector_int16    __x, vector_int16    __y);
static vector_uint2    __SIMD_ATTRIBUTES__ vector_min(vector_uint2    __x, vector_uint2    __y);
static vector_uint3    __SIMD_ATTRIBUTES__ vector_min(vector_uint3    __x, vector_uint3    __y);
static vector_uint4    __SIMD_ATTRIBUTES__ vector_min(vector_uint4    __x, vector_uint4    __y);
static vector_uint8    __SIMD_ATTRIBUTES__ vector_min(vector_uint8    __x, vector_uint8    __y);
static vector_uint16   __SIMD_ATTRIBUTES__ vector_min(vector_uint16   __x, vector_uint16   __y);
static vector_float2   __SIMD_ATTRIBUTES__ vector_min(vector_float2   __x, vector_float2   __y);
static vector_float3   __SIMD_ATTRIBUTES__ vector_min(vector_float3   __x, vector_float3   __y);
static vector_float4   __SIMD_ATTRIBUTES__ vector_min(vector_float4   __x, vector_float4   __y);
static vector_float8   __SIMD_ATTRIBUTES__ vector_min(vector_float8   __x, vector_float8   __y);
static vector_float16  __SIMD_ATTRIBUTES__ vector_min(vector_float16  __x, vector_float16  __y);
static vector_long2    __SIMD_ATTRIBUTES__ vector_min(vector_long2    __x, vector_long2    __y);
static vector_long3    __SIMD_ATTRIBUTES__ vector_min(vector_long3    __x, vector_long3    __y);
static vector_long4    __SIMD_ATTRIBUTES__ vector_min(vector_long4    __x, vector_long4    __y);
static vector_long8    __SIMD_ATTRIBUTES__ vector_min(vector_long8    __x, vector_long8    __y);
static vector_ulong2   __SIMD_ATTRIBUTES__ vector_min(vector_ulong2   __x, vector_ulong2   __y);
static vector_ulong3   __SIMD_ATTRIBUTES__ vector_min(vector_ulong3   __x, vector_ulong3   __y);
static vector_ulong4   __SIMD_ATTRIBUTES__ vector_min(vector_ulong4   __x, vector_ulong4   __y);
static vector_ulong8   __SIMD_ATTRIBUTES__ vector_min(vector_ulong8   __x, vector_ulong8   __y);
static vector_double2  __SIMD_ATTRIBUTES__ vector_min(vector_double2  __x, vector_double2  __y);
static vector_double3  __SIMD_ATTRIBUTES__ vector_min(vector_double3  __x, vector_double3  __y);
static vector_double4  __SIMD_ATTRIBUTES__ vector_min(vector_double4  __x, vector_double4  __y);
static vector_double8  __SIMD_ATTRIBUTES__ vector_min(vector_double8  __x, vector_double8  __y);

static vector_char2    __SIMD_ATTRIBUTES__ vector_clamp(vector_char2    __x, vector_char2    __min, vector_char2    __max);
static vector_char3    __SIMD_ATTRIBUTES__ vector_clamp(vector_char3    __x, vector_char3    __min, vector_char3    __max);
static vector_char4    __SIMD_ATTRIBUTES__ vector_clamp(vector_char4    __x, vector_char4    __min, vector_char4    __max);
static vector_char8    __SIMD_ATTRIBUTES__ vector_clamp(vector_char8    __x, vector_char8    __min, vector_char8    __max);
static vector_char16   __SIMD_ATTRIBUTES__ vector_clamp(vector_char16   __x, vector_char16   __min, vector_char16   __max);
static vector_char32   __SIMD_ATTRIBUTES__ vector_clamp(vector_char32   __x, vector_char32   __min, vector_char32   __max);
static vector_uchar2   __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar2   __x, vector_uchar2   __min, vector_uchar2   __max);
static vector_uchar3   __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar3   __x, vector_uchar3   __min, vector_uchar3   __max);
static vector_uchar4   __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar4   __x, vector_uchar4   __min, vector_uchar4   __max);
static vector_uchar8   __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar8   __x, vector_uchar8   __min, vector_uchar8   __max);
static vector_uchar16  __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar16  __x, vector_uchar16  __min, vector_uchar16  __max);
static vector_uchar32  __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar32  __x, vector_uchar32  __min, vector_uchar32  __max);
static vector_short2   __SIMD_ATTRIBUTES__ vector_clamp(vector_short2   __x, vector_short2   __min, vector_short2   __max);
static vector_short3   __SIMD_ATTRIBUTES__ vector_clamp(vector_short3   __x, vector_short3   __min, vector_short3   __max);
static vector_short4   __SIMD_ATTRIBUTES__ vector_clamp(vector_short4   __x, vector_short4   __min, vector_short4   __max);
static vector_short8   __SIMD_ATTRIBUTES__ vector_clamp(vector_short8   __x, vector_short8   __min, vector_short8   __max);
static vector_short16  __SIMD_ATTRIBUTES__ vector_clamp(vector_short16  __x, vector_short16  __min, vector_short16  __max);
static vector_short32  __SIMD_ATTRIBUTES__ vector_clamp(vector_short32  __x, vector_short32  __min, vector_short32  __max);
static vector_ushort2  __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort2  __x, vector_ushort2  __min, vector_ushort2  __max);
static vector_ushort3  __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort3  __x, vector_ushort3  __min, vector_ushort3  __max);
static vector_ushort4  __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort4  __x, vector_ushort4  __min, vector_ushort4  __max);
static vector_ushort8  __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort8  __x, vector_ushort8  __min, vector_ushort8  __max);
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort16 __x, vector_ushort16 __min, vector_ushort16 __max);
static vector_ushort32 __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort32 __x, vector_ushort32 __min, vector_ushort32 __max);
static vector_int2     __SIMD_ATTRIBUTES__ vector_clamp(vector_int2     __x, vector_int2     __min, vector_int2     __max);
static vector_int3     __SIMD_ATTRIBUTES__ vector_clamp(vector_int3     __x, vector_int3     __min, vector_int3     __max);
static vector_int4     __SIMD_ATTRIBUTES__ vector_clamp(vector_int4     __x, vector_int4     __min, vector_int4     __max);
static vector_int8     __SIMD_ATTRIBUTES__ vector_clamp(vector_int8     __x, vector_int8     __min, vector_int8     __max);
static vector_int16    __SIMD_ATTRIBUTES__ vector_clamp(vector_int16    __x, vector_int16    __min, vector_int16    __max);
static vector_uint2    __SIMD_ATTRIBUTES__ vector_clamp(vector_uint2    __x, vector_uint2    __min, vector_uint2    __max);
static vector_uint3    __SIMD_ATTRIBUTES__ vector_clamp(vector_uint3    __x, vector_uint3    __min, vector_uint3    __max);
static vector_uint4    __SIMD_ATTRIBUTES__ vector_clamp(vector_uint4    __x, vector_uint4    __min, vector_uint4    __max);
static vector_uint8    __SIMD_ATTRIBUTES__ vector_clamp(vector_uint8    __x, vector_uint8    __min, vector_uint8    __max);
static vector_uint16   __SIMD_ATTRIBUTES__ vector_clamp(vector_uint16   __x, vector_uint16   __min, vector_uint16   __max);
static float           __SIMD_ATTRIBUTES__ vector_clamp(float           __x, float           __min, float           __max);
static vector_float2   __SIMD_ATTRIBUTES__ vector_clamp(vector_float2   __x, vector_float2   __min, vector_float2   __max);
static vector_float3   __SIMD_ATTRIBUTES__ vector_clamp(vector_float3   __x, vector_float3   __min, vector_float3   __max);
static vector_float4   __SIMD_ATTRIBUTES__ vector_clamp(vector_float4   __x, vector_float4   __min, vector_float4   __max);
static vector_float8   __SIMD_ATTRIBUTES__ vector_clamp(vector_float8   __x, vector_float8   __min, vector_float8   __max);
static vector_float16  __SIMD_ATTRIBUTES__ vector_clamp(vector_float16  __x, vector_float16  __min, vector_float16  __max);
static vector_long2    __SIMD_ATTRIBUTES__ vector_clamp(vector_long2    __x, vector_long2    __min, vector_long2    __max);
static vector_long3    __SIMD_ATTRIBUTES__ vector_clamp(vector_long3    __x, vector_long3    __min, vector_long3    __max);
static vector_long4    __SIMD_ATTRIBUTES__ vector_clamp(vector_long4    __x, vector_long4    __min, vector_long4    __max);
static vector_long8    __SIMD_ATTRIBUTES__ vector_clamp(vector_long8    __x, vector_long8    __min, vector_long8    __max);
static vector_ulong2   __SIMD_ATTRIBUTES__ vector_clamp(vector_ulong2   __x, vector_ulong2   __min, vector_ulong2   __max);
static vector_ulong3   __SIMD_ATTRIBUTES__ vector_clamp(vector_ulong3   __x, vector_ulong3   __min, vector_ulong3   __max);
static vector_ulong4   __SIMD_ATTRIBUTES__ vector_clamp(vector_ulong4   __x, vector_ulong4   __min, vector_ulong4   __max);
static vector_ulong8   __SIMD_ATTRIBUTES__ vector_clamp(vector_ulong8   __x, vector_ulong8   __min, vector_ulong8   __max);
static double          __SIMD_ATTRIBUTES__ vector_clamp(double          __x, double          __min, double          __max);
static vector_double2  __SIMD_ATTRIBUTES__ vector_clamp(vector_double2  __x, vector_double2  __min, vector_double2  __max);
static vector_double3  __SIMD_ATTRIBUTES__ vector_clamp(vector_double3  __x, vector_double3  __min, vector_double3  __max);
static vector_double4  __SIMD_ATTRIBUTES__ vector_clamp(vector_double4  __x, vector_double4  __min, vector_double4  __max);
static vector_double8  __SIMD_ATTRIBUTES__ vector_clamp(vector_double8  __x, vector_double8  __min, vector_double8  __max);

static float          __SIMD_ATTRIBUTES__ vector_sign(float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_sign(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_sign(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_sign(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_sign(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_sign(vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_sign(double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_sign(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_sign(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_sign(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_sign(vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_mix(float          __x, float          __y, float          __t);
static vector_float2  __SIMD_ATTRIBUTES__ vector_mix(vector_float2  __x, vector_float2  __y, vector_float2  __t);
static vector_float3  __SIMD_ATTRIBUTES__ vector_mix(vector_float3  __x, vector_float3  __y, vector_float3  __t);
static vector_float4  __SIMD_ATTRIBUTES__ vector_mix(vector_float4  __x, vector_float4  __y, vector_float4  __t);
static vector_float8  __SIMD_ATTRIBUTES__ vector_mix(vector_float8  __x, vector_float8  __y, vector_float8  __t);
static vector_float16 __SIMD_ATTRIBUTES__ vector_mix(vector_float16 __x, vector_float16 __y, vector_float16 __t);
static double         __SIMD_ATTRIBUTES__ vector_mix(double         __x, double         __y, double         __t);
static vector_double2 __SIMD_ATTRIBUTES__ vector_mix(vector_double2 __x, vector_double2 __y, vector_double2 __t);
static vector_double3 __SIMD_ATTRIBUTES__ vector_mix(vector_double3 __x, vector_double3 __y, vector_double3 __t);
static vector_double4 __SIMD_ATTRIBUTES__ vector_mix(vector_double4 __x, vector_double4 __y, vector_double4 __t);
static vector_double8 __SIMD_ATTRIBUTES__ vector_mix(vector_double8 __x, vector_double8 __y, vector_double8 __t);

static float          __SIMD_ATTRIBUTES__ vector_precise_recip(float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_precise_recip(double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_fast_recip(float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_fast_recip(double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_recip(float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_recip(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_recip(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_recip(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_recip(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_recip(vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_recip(double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_recip(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_recip(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_recip(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_recip(vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_precise_rsqrt(float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_precise_rsqrt(double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_fast_rsqrt(float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_fast_rsqrt(double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_rsqrt(float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_rsqrt(double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_fract(float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_fract(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_fract(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_fract(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_fract(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_fract(vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_fract(double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_fract(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_fract(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_fract(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_fract(vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_step(float          __edge, float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_step(vector_float2  __edge, vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_step(vector_float3  __edge, vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_step(vector_float4  __edge, vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_step(vector_float8  __edge, vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_step(vector_float16 __edge, vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_step(double         __edge, double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_step(vector_double2 __edge, vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_step(vector_double3 __edge, vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_step(vector_double4 __edge, vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_step(vector_double8 __edge, vector_double8 __x);

static float          __SIMD_ATTRIBUTES__ vector_smoothstep(float          __edge0, float          __edge1, float          __x);
static vector_float2  __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float2  __edge0, vector_float2  __edge1, vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float3  __edge0, vector_float3  __edge1, vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float4  __edge0, vector_float4  __edge1, vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float8  __edge0, vector_float8  __edge1, vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float16 __edge0, vector_float16 __edge1, vector_float16 __x);
static double         __SIMD_ATTRIBUTES__ vector_smoothstep(double         __edge0, double         __edge1, double         __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_double2 __edge0, vector_double2 __edge1, vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_double3 __edge0, vector_double3 __edge1, vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_double4 __edge0, vector_double4 __edge1, vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_double8 __edge0, vector_double8 __edge1, vector_double8 __x);

#ifdef __cplusplus
} /* extern "C" */

namespace simd {
    template <typename typeN> static __SIMD_INLINE__ typeN abs(const typeN x) { return ::vector_abs(x); }
    template <typename typeN> static __SIMD_INLINE__ typeN max(const typeN x, const typeN y) { return ::vector_max(x,y); }
    template <typename typeN> static __SIMD_INLINE__ typeN min(const typeN x, const typeN y) { return ::vector_min(x,y); }
    template <typename typeN> static __SIMD_INLINE__ typeN clamp(const typeN x, const typeN min, const typeN max) { return ::vector_clamp(x,min,max); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN sign(const fptypeN x) { return ::vector_sign(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN mix(const fptypeN x, const fptypeN y, const fptypeN t) { return ::vector_mix(x,y,t); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN recip(const fptypeN x) { return vector_recip(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN rsqrt(const fptypeN x) { return vector_rsqrt(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN fract(const fptypeN x) { return ::vector_fract(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN step(const fptypeN edge, const fptypeN x) { return ::vector_step(edge,x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN smoothstep(const fptypeN edge0, const fptypeN edge1, const fptypeN x) { return ::vector_smoothstep(edge0,edge1,x); }
    namespace precise {
        template <typename fptypeN> static __SIMD_INLINE__ fptypeN recip(const fptypeN x) { return ::vector_precise_recip(x); }
        template <typename fptypeN> static __SIMD_INLINE__ fptypeN rsqrt(const fptypeN x) { return ::vector_precise_rsqrt(x); }
    }
    namespace fast {
        template <typename fptypeN> static __SIMD_INLINE__ fptypeN recip(const fptypeN x) { return ::vector_fast_recip(x); }
        template <typename fptypeN> static __SIMD_INLINE__ fptypeN rsqrt(const fptypeN x) { return ::vector_fast_rsqrt(x); }
    }
}

extern "C" {
#endif /* __cplusplus */

#pragma mark - Implementation

#if defined __SSE4_1__
__SIMD_ELEMENTWISE_UNARY_2_IN_4(vector_abs, char)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(vector_abs, char)
__SIMD_ELEMENTWISE_UNARY_4_IN_8(vector_abs, char)
__SIMD_ELEMENTWISE_UNARY_8_IN_16(vector_abs, char)
static vector_char16  __SIMD_ATTRIBUTES__ vector_abs(vector_char16  __x) { return _mm_abs_epi8(__x); }
__SIMD_ELEMENTWISE_UNARY_2_IN_4(vector_abs, short)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(vector_abs, short)
__SIMD_ELEMENTWISE_UNARY_4_IN_8(vector_abs, short)
static vector_short8  __SIMD_ATTRIBUTES__ vector_abs(vector_short8  __x) { return _mm_abs_epi16(__x); }
__SIMD_ELEMENTWISE_UNARY_2_IN_4(vector_abs, int)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(vector_abs, int)
static vector_int4    __SIMD_ATTRIBUTES__ vector_abs(vector_int4    __x) { return _mm_abs_epi32(__x); }
#   if defined __AVX2__
static vector_char32  __SIMD_ATTRIBUTES__ vector_abs(vector_char32  __x) { return _mm256_abs_epi8(__x); }
static vector_short16 __SIMD_ATTRIBUTES__ vector_abs(vector_short16 __x) { return _mm256_abs_epi16(__x); }
static vector_int8    __SIMD_ATTRIBUTES__ vector_abs(vector_int8    __x) { return _mm256_abs_epi32(__x); }
#   else
__SIMD_ELEMENTWISE_UNARY_32_IN_16(vector_abs, char)
__SIMD_ELEMENTWISE_UNARY_16_IN_8(vector_abs, short)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(vector_abs, int)
#   endif
__SIMD_ELEMENTWISE_UNARY_32_IN_16(vector_abs, short)
__SIMD_ELEMENTWISE_UNARY_16_IN_8(vector_abs, int)
#elif defined __NEON__
__SIMD_ELEMENTWISE_UNARY_2_IN_4(vector_abs, char)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(vector_abs, char)
__SIMD_ELEMENTWISE_UNARY_4_IN_8(vector_abs, char)
static vector_char8   __SIMD_ATTRIBUTES__ vector_abs(vector_char8   __x) { return vabs_s8(__x); }
static vector_char16  __SIMD_ATTRIBUTES__ vector_abs(vector_char16  __x) { return vabsq_s8(__x); }
__SIMD_ELEMENTWISE_UNARY_2_IN_4(vector_abs, short)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(vector_abs, short)
static vector_short4  __SIMD_ATTRIBUTES__ vector_abs(vector_short4  __x) { return vabs_s16(__x); }
static vector_short8  __SIMD_ATTRIBUTES__ vector_abs(vector_short8  __x) { return vabsq_s16(__x); }
__SIMD_ELEMENTWISE_UNARY_2_IN_4(vector_abs, int)
static vector_int2    __SIMD_ATTRIBUTES__ vector_abs(vector_int2    __x) { return vabs_s32(__x); }
static vector_int4    __SIMD_ATTRIBUTES__ vector_abs(vector_int4    __x) { return vabsq_s32(__x); }
__SIMD_ELEMENTWISE_UNARY_32_IN_16(vector_abs, char)
__SIMD_ELEMENTWISE_UNARY_16_IN_8(vector_abs, short)
__SIMD_ELEMENTWISE_UNARY_32_IN_16(vector_abs, short)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(vector_abs, int)
__SIMD_ELEMENTWISE_UNARY_16_IN_8(vector_abs, int)
#else
static vector_char2    __SIMD_ATTRIBUTES__ vector_abs(vector_char2    __x) { vector_char2   __mask = __x >> (char)7; return (__x ^ __mask) - __mask; }
static vector_char3    __SIMD_ATTRIBUTES__ vector_abs(vector_char3    __x) { vector_char3   __mask = __x >> (char)7; return (__x ^ __mask) - __mask; }
static vector_char4    __SIMD_ATTRIBUTES__ vector_abs(vector_char4    __x) { vector_char4   __mask = __x >> (char)7; return (__x ^ __mask) - __mask; }
static vector_char8    __SIMD_ATTRIBUTES__ vector_abs(vector_char8    __x) { vector_char8   __mask = __x >> (char)7; return (__x ^ __mask) - __mask; }
static vector_char16   __SIMD_ATTRIBUTES__ vector_abs(vector_char16   __x) { vector_char16  __mask = __x >> (char)7; return (__x ^ __mask) - __mask; }
static vector_char32   __SIMD_ATTRIBUTES__ vector_abs(vector_char32   __x) { vector_char32  __mask = __x >> (char)7; return (__x ^ __mask) - __mask; }
static vector_short2   __SIMD_ATTRIBUTES__ vector_abs(vector_short2   __x) { vector_short2  __mask = __x >> (short)15; return (__x ^ __mask) - __mask; }
static vector_short3   __SIMD_ATTRIBUTES__ vector_abs(vector_short3   __x) { vector_short3  __mask = __x >> (short)15; return (__x ^ __mask) - __mask; }
static vector_short4   __SIMD_ATTRIBUTES__ vector_abs(vector_short4   __x) { vector_short4  __mask = __x >> (short)15; return (__x ^ __mask) - __mask; }
static vector_short8   __SIMD_ATTRIBUTES__ vector_abs(vector_short8   __x) { vector_short8  __mask = __x >> (short)15; return (__x ^ __mask) - __mask; }
static vector_short16  __SIMD_ATTRIBUTES__ vector_abs(vector_short16  __x) { vector_short16 __mask = __x >> (short)15; return (__x ^ __mask) - __mask; }
static vector_short32  __SIMD_ATTRIBUTES__ vector_abs(vector_short32  __x) { vector_short32 __mask = __x >> (short)15; return (__x ^ __mask) - __mask; }
static vector_int2     __SIMD_ATTRIBUTES__ vector_abs(vector_int2     __x) { vector_int2    __mask = __x >> 31; return (__x ^ __mask) - __mask; }
static vector_int3     __SIMD_ATTRIBUTES__ vector_abs(vector_int3     __x) { vector_int3    __mask = __x >> 31; return (__x ^ __mask) - __mask; }
static vector_int4     __SIMD_ATTRIBUTES__ vector_abs(vector_int4     __x) { vector_int4    __mask = __x >> 31; return (__x ^ __mask) - __mask; }
static vector_int8     __SIMD_ATTRIBUTES__ vector_abs(vector_int8     __x) { vector_int8    __mask = __x >> 31; return (__x ^ __mask) - __mask; }
static vector_int16    __SIMD_ATTRIBUTES__ vector_abs(vector_int16    __x) { vector_int16   __mask = __x >> 31; return (__x ^ __mask) - __mask; }
#endif
static vector_float2   __SIMD_ATTRIBUTES__ vector_abs(vector_float2   __x) { return __tg_fabs(__x); }
static vector_float3   __SIMD_ATTRIBUTES__ vector_abs(vector_float3   __x) { return __tg_fabs(__x); }
static vector_float4   __SIMD_ATTRIBUTES__ vector_abs(vector_float4   __x) { return __tg_fabs(__x); }
static vector_float8   __SIMD_ATTRIBUTES__ vector_abs(vector_float8   __x) { return __tg_fabs(__x); }
static vector_float16  __SIMD_ATTRIBUTES__ vector_abs(vector_float16  __x) { return __tg_fabs(__x); }
#if defined __arm64__
static vector_long2    __SIMD_ATTRIBUTES__ vector_abs(vector_long2    __x) { return vabsq_s64(__x); }
__SIMD_ELEMENTWISE_UNARY_3_IN_4(vector_abs, long)
__SIMD_ELEMENTWISE_UNARY_4_IN_2(vector_abs, long)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(vector_abs, long)
#else
static vector_long2    __SIMD_ATTRIBUTES__ vector_abs(vector_long2    __x) { vector_long2   __mask = __x >> 63; return (__x ^ __mask) - __mask; }
static vector_long3    __SIMD_ATTRIBUTES__ vector_abs(vector_long3    __x) { vector_long3   __mask = __x >> 63; return (__x ^ __mask) - __mask; }
static vector_long4    __SIMD_ATTRIBUTES__ vector_abs(vector_long4    __x) { vector_long4   __mask = __x >> 63; return (__x ^ __mask) - __mask; }
static vector_long8    __SIMD_ATTRIBUTES__ vector_abs(vector_long8    __x) { vector_long8   __mask = __x >> 63; return (__x ^ __mask) - __mask; }
#endif
static vector_double2  __SIMD_ATTRIBUTES__ vector_abs(vector_double2  __x) { return __tg_fabs(__x); }
static vector_double3  __SIMD_ATTRIBUTES__ vector_abs(vector_double3  __x) { return __tg_fabs(__x); }
static vector_double4  __SIMD_ATTRIBUTES__ vector_abs(vector_double4  __x) { return __tg_fabs(__x); }
static vector_double8  __SIMD_ATTRIBUTES__ vector_abs(vector_double8  __x) { return __tg_fabs(__x); }

#if defined __SSE4_1__
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, uchar)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, uchar)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_min, uchar)
__SIMD_ELEMENTWISE_BINARY_8_IN_16(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_8_IN_16(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_8_IN_16(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_8_IN_16(vector_min, uchar)
static vector_char16 __SIMD_ATTRIBUTES__ vector_max(vector_char16 __x, vector_char16 __y) { return _mm_max_epi8(__x,__y); }
static vector_char16 __SIMD_ATTRIBUTES__ vector_min(vector_char16 __x, vector_char16 __y) { return _mm_min_epi8(__x,__y); }
static vector_uchar16 __SIMD_ATTRIBUTES__ vector_max(vector_uchar16 __x, vector_uchar16 __y) { return _mm_max_epu8(__x,__y); }
static vector_uchar16 __SIMD_ATTRIBUTES__ vector_min(vector_uchar16 __x, vector_uchar16 __y) { return _mm_min_epu8(__x,__y); }
#   if defined __AVX2__
static vector_char32 __SIMD_ATTRIBUTES__ vector_max(vector_char32 __x, vector_char32 __y) { return _mm256_max_epi8(__x,__y); }
static vector_char32 __SIMD_ATTRIBUTES__ vector_min(vector_char32 __x, vector_char32 __y) { return _mm256_min_epi8(__x,__y); }
static vector_uchar32 __SIMD_ATTRIBUTES__ vector_max(vector_uchar32 __x, vector_uchar32 __y) { return _mm256_max_epu8(__x,__y); }
static vector_uchar32 __SIMD_ATTRIBUTES__ vector_min(vector_uchar32 __x, vector_uchar32 __y) { return _mm256_min_epu8(__x,__y); }
#   else
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_min, uchar)
#   endif
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, ushort)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, ushort)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_min, ushort)
static vector_short8 __SIMD_ATTRIBUTES__ vector_max(vector_short8 __x, vector_short8 __y) { return _mm_max_epi16(__x,__y); }
static vector_short8 __SIMD_ATTRIBUTES__ vector_min(vector_short8 __x, vector_short8 __y) { return _mm_min_epi16(__x,__y); }
static vector_ushort8 __SIMD_ATTRIBUTES__ vector_max(vector_ushort8 __x, vector_ushort8 __y) { return _mm_max_epu16(__x,__y); }
static vector_ushort8 __SIMD_ATTRIBUTES__ vector_min(vector_ushort8 __x, vector_ushort8 __y) { return _mm_min_epu16(__x,__y); }
#   if defined __AVX2__
static vector_short16 __SIMD_ATTRIBUTES__ vector_max(vector_short16 __x, vector_short16 __y) { return _mm256_max_epi16(__x,__y); }
static vector_short16 __SIMD_ATTRIBUTES__ vector_min(vector_short16 __x, vector_short16 __y) { return _mm256_min_epi16(__x,__y); }
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_max(vector_ushort16 __x, vector_ushort16 __y) { return _mm256_max_epu16(__x,__y); }
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_min(vector_ushort16 __x, vector_ushort16 __y) { return _mm256_min_epu16(__x,__y); }
#   else
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_min, ushort)
#   endif
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_min, ushort)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, int)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, int)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, uint)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, uint)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, int)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, int)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, uint)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, uint)
static vector_int4 __SIMD_ATTRIBUTES__ vector_max(vector_int4 __x, vector_int4 __y) { return _mm_max_epi32(__x,__y); }
static vector_int4 __SIMD_ATTRIBUTES__ vector_min(vector_int4 __x, vector_int4 __y) { return _mm_min_epi32(__x,__y); }
static vector_uint4 __SIMD_ATTRIBUTES__ vector_max(vector_uint4 __x, vector_uint4 __y) { return _mm_max_epu32(__x,__y); }
static vector_uint4 __SIMD_ATTRIBUTES__ vector_min(vector_uint4 __x, vector_uint4 __y) { return _mm_min_epu32(__x,__y); }
#   if defined __AVX2__
static vector_int8 __SIMD_ATTRIBUTES__ vector_max(vector_int8 __x, vector_int8 __y) { return _mm256_max_epi32(__x,__y); }
static vector_int8 __SIMD_ATTRIBUTES__ vector_min(vector_int8 __x, vector_int8 __y) { return _mm256_min_epi32(__x,__y); }
static vector_uint8 __SIMD_ATTRIBUTES__ vector_max(vector_uint8 __x, vector_uint8 __y) { return _mm256_max_epu32(__x,__y); }
static vector_uint8 __SIMD_ATTRIBUTES__ vector_min(vector_uint8 __x, vector_uint8 __y) { return _mm256_min_epu32(__x,__y); }
#   else
__SIMD_ELEMENTWISE_BINARY_8_IN_4(vector_max, int)
__SIMD_ELEMENTWISE_BINARY_8_IN_4(vector_min, int)
__SIMD_ELEMENTWISE_BINARY_8_IN_4(vector_max, uint)
__SIMD_ELEMENTWISE_BINARY_8_IN_4(vector_min, uint)
#   endif
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_max, int)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_min, int)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_max, uint)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_min, uint)
#elif defined __NEON__
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, uchar)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, uchar)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_4_IN_8(vector_min, uchar)
static vector_char8 __SIMD_ATTRIBUTES__ vector_max(vector_char8 __x, vector_char8 __y) { return vmax_s8(__x,__y); }
static vector_char8 __SIMD_ATTRIBUTES__ vector_min(vector_char8 __x, vector_char8 __y) { return vmin_s8(__x,__y); }
static vector_uchar8 __SIMD_ATTRIBUTES__ vector_max(vector_uchar8 __x, vector_uchar8 __y) { return vmax_u8(__x,__y); }
static vector_uchar8 __SIMD_ATTRIBUTES__ vector_min(vector_uchar8 __x, vector_uchar8 __y) { return vmin_u8(__x,__y); }
static vector_char16 __SIMD_ATTRIBUTES__ vector_max(vector_char16 __x, vector_char16 __y) { return vmaxq_s8(__x,__y); }
static vector_char16 __SIMD_ATTRIBUTES__ vector_min(vector_char16 __x, vector_char16 __y) { return vminq_s8(__x,__y); }
static vector_uchar16 __SIMD_ATTRIBUTES__ vector_max(vector_uchar16 __x, vector_uchar16 __y) { return vmaxq_u8(__x,__y); }
static vector_uchar16 __SIMD_ATTRIBUTES__ vector_min(vector_uchar16 __x, vector_uchar16 __y) { return vminq_u8(__x,__y); }
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_max, char)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_min, char)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_max, uchar)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_min, uchar)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_2_IN_4(vector_min, ushort)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, ushort)
static vector_short4 __SIMD_ATTRIBUTES__ vector_max(vector_short4 __x, vector_short4 __y) { return vmax_s16(__x,__y); }
static vector_short4 __SIMD_ATTRIBUTES__ vector_min(vector_short4 __x, vector_short4 __y) { return vmin_s16(__x,__y); }
static vector_ushort4 __SIMD_ATTRIBUTES__ vector_max(vector_ushort4 __x, vector_ushort4 __y) { return vmax_u16(__x,__y); }
static vector_ushort4 __SIMD_ATTRIBUTES__ vector_min(vector_ushort4 __x, vector_ushort4 __y) { return vmin_u16(__x,__y); }
static vector_short8 __SIMD_ATTRIBUTES__ vector_max(vector_short8 __x, vector_short8 __y) { return vmaxq_s16(__x,__y); }
static vector_short8 __SIMD_ATTRIBUTES__ vector_min(vector_short8 __x, vector_short8 __y) { return vminq_s16(__x,__y); }
static vector_ushort8 __SIMD_ATTRIBUTES__ vector_max(vector_ushort8 __x, vector_ushort8 __y) { return vmaxq_u16(__x,__y); }
static vector_ushort8 __SIMD_ATTRIBUTES__ vector_min(vector_ushort8 __x, vector_ushort8 __y) { return vminq_u16(__x,__y); }
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_min, ushort)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_max, short)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_min, short)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_max, ushort)
__SIMD_ELEMENTWISE_BINARY_32_IN_16(vector_min, ushort)
static vector_int2 __SIMD_ATTRIBUTES__ vector_max(vector_int2 __x, vector_int2 __y) { return vmax_s32(__x,__y); }
static vector_int2 __SIMD_ATTRIBUTES__ vector_min(vector_int2 __x, vector_int2 __y) { return vmin_s32(__x,__y); }
static vector_uint2 __SIMD_ATTRIBUTES__ vector_max(vector_uint2 __x, vector_uint2 __y) { return vmax_u32(__x,__y); }
static vector_uint2 __SIMD_ATTRIBUTES__ vector_min(vector_uint2 __x, vector_uint2 __y) { return vmin_u32(__x,__y); }
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, int)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, int)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_max, uint)
__SIMD_ELEMENTWISE_BINARY_3_IN_4(vector_min, uint)
static vector_int4 __SIMD_ATTRIBUTES__ vector_max(vector_int4 __x, vector_int4 __y) { return vmaxq_s32(__x,__y); }
static vector_int4 __SIMD_ATTRIBUTES__ vector_min(vector_int4 __x, vector_int4 __y) { return vminq_s32(__x,__y); }
static vector_uint4 __SIMD_ATTRIBUTES__ vector_max(vector_uint4 __x, vector_uint4 __y) { return vmaxq_u32(__x,__y); }
static vector_uint4 __SIMD_ATTRIBUTES__ vector_min(vector_uint4 __x, vector_uint4 __y) { return vminq_u32(__x,__y); }
__SIMD_ELEMENTWISE_BINARY_8_IN_4(vector_max, int)
__SIMD_ELEMENTWISE_BINARY_8_IN_4(vector_min, int)
__SIMD_ELEMENTWISE_BINARY_8_IN_4(vector_max, uint)
__SIMD_ELEMENTWISE_BINARY_8_IN_4(vector_min, uint)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_max, int)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_min, int)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_max, uint)
__SIMD_ELEMENTWISE_BINARY_16_IN_8(vector_min, uint)
#else
static vector_char2    __SIMD_ATTRIBUTES__ vector_max(vector_char2    __x, vector_char2    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_char2    __SIMD_ATTRIBUTES__ vector_min(vector_char2    __x, vector_char2    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_char3    __SIMD_ATTRIBUTES__ vector_max(vector_char3    __x, vector_char3    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_char3    __SIMD_ATTRIBUTES__ vector_min(vector_char3    __x, vector_char3    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_char4    __SIMD_ATTRIBUTES__ vector_max(vector_char4    __x, vector_char4    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_char4    __SIMD_ATTRIBUTES__ vector_min(vector_char4    __x, vector_char4    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_char8    __SIMD_ATTRIBUTES__ vector_max(vector_char8    __x, vector_char8    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_char8    __SIMD_ATTRIBUTES__ vector_min(vector_char8    __x, vector_char8    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_char16   __SIMD_ATTRIBUTES__ vector_max(vector_char16   __x, vector_char16   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_char16   __SIMD_ATTRIBUTES__ vector_min(vector_char16   __x, vector_char16   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_char32   __SIMD_ATTRIBUTES__ vector_max(vector_char32   __x, vector_char32   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_char32   __SIMD_ATTRIBUTES__ vector_min(vector_char32   __x, vector_char32   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uchar2   __SIMD_ATTRIBUTES__ vector_max(vector_uchar2   __x, vector_uchar2   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uchar2   __SIMD_ATTRIBUTES__ vector_min(vector_uchar2   __x, vector_uchar2   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uchar3   __SIMD_ATTRIBUTES__ vector_max(vector_uchar3   __x, vector_uchar3   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uchar3   __SIMD_ATTRIBUTES__ vector_min(vector_uchar3   __x, vector_uchar3   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uchar4   __SIMD_ATTRIBUTES__ vector_max(vector_uchar4   __x, vector_uchar4   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uchar4   __SIMD_ATTRIBUTES__ vector_min(vector_uchar4   __x, vector_uchar4   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uchar8   __SIMD_ATTRIBUTES__ vector_max(vector_uchar8   __x, vector_uchar8   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uchar8   __SIMD_ATTRIBUTES__ vector_min(vector_uchar8   __x, vector_uchar8   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uchar16  __SIMD_ATTRIBUTES__ vector_max(vector_uchar16  __x, vector_uchar16  __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uchar16  __SIMD_ATTRIBUTES__ vector_min(vector_uchar16  __x, vector_uchar16  __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uchar32  __SIMD_ATTRIBUTES__ vector_max(vector_uchar32  __x, vector_uchar32  __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uchar32  __SIMD_ATTRIBUTES__ vector_min(vector_uchar32  __x, vector_uchar32  __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_short2   __SIMD_ATTRIBUTES__ vector_max(vector_short2   __x, vector_short2   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_short2   __SIMD_ATTRIBUTES__ vector_min(vector_short2   __x, vector_short2   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_short3   __SIMD_ATTRIBUTES__ vector_max(vector_short3   __x, vector_short3   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_short3   __SIMD_ATTRIBUTES__ vector_min(vector_short3   __x, vector_short3   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_short4   __SIMD_ATTRIBUTES__ vector_max(vector_short4   __x, vector_short4   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_short4   __SIMD_ATTRIBUTES__ vector_min(vector_short4   __x, vector_short4   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_short8   __SIMD_ATTRIBUTES__ vector_max(vector_short8   __x, vector_short8   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_short8   __SIMD_ATTRIBUTES__ vector_min(vector_short8   __x, vector_short8   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_short16  __SIMD_ATTRIBUTES__ vector_max(vector_short16  __x, vector_short16  __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_short16  __SIMD_ATTRIBUTES__ vector_min(vector_short16  __x, vector_short16  __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_short32  __SIMD_ATTRIBUTES__ vector_max(vector_short32  __x, vector_short32  __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_short32  __SIMD_ATTRIBUTES__ vector_min(vector_short32  __x, vector_short32  __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ushort2  __SIMD_ATTRIBUTES__ vector_max(vector_ushort2  __x, vector_ushort2  __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ushort2  __SIMD_ATTRIBUTES__ vector_min(vector_ushort2  __x, vector_ushort2  __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ushort3  __SIMD_ATTRIBUTES__ vector_max(vector_ushort3  __x, vector_ushort3  __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ushort3  __SIMD_ATTRIBUTES__ vector_min(vector_ushort3  __x, vector_ushort3  __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ushort4  __SIMD_ATTRIBUTES__ vector_max(vector_ushort4  __x, vector_ushort4  __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ushort4  __SIMD_ATTRIBUTES__ vector_min(vector_ushort4  __x, vector_ushort4  __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ushort8  __SIMD_ATTRIBUTES__ vector_max(vector_ushort8  __x, vector_ushort8  __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ushort8  __SIMD_ATTRIBUTES__ vector_min(vector_ushort8  __x, vector_ushort8  __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_max(vector_ushort16 __x, vector_ushort16 __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_min(vector_ushort16 __x, vector_ushort16 __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ushort32 __SIMD_ATTRIBUTES__ vector_max(vector_ushort32 __x, vector_ushort32 __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ushort32 __SIMD_ATTRIBUTES__ vector_min(vector_ushort32 __x, vector_ushort32 __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_int2     __SIMD_ATTRIBUTES__ vector_max(vector_int2     __x, vector_int2     __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_int2     __SIMD_ATTRIBUTES__ vector_min(vector_int2     __x, vector_int2     __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_int3     __SIMD_ATTRIBUTES__ vector_max(vector_int3     __x, vector_int3     __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_int3     __SIMD_ATTRIBUTES__ vector_min(vector_int3     __x, vector_int3     __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_int4     __SIMD_ATTRIBUTES__ vector_max(vector_int4     __x, vector_int4     __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_int4     __SIMD_ATTRIBUTES__ vector_min(vector_int4     __x, vector_int4     __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_int8     __SIMD_ATTRIBUTES__ vector_max(vector_int8     __x, vector_int8     __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_int8     __SIMD_ATTRIBUTES__ vector_min(vector_int8     __x, vector_int8     __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_int16    __SIMD_ATTRIBUTES__ vector_max(vector_int16    __x, vector_int16    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_int16    __SIMD_ATTRIBUTES__ vector_min(vector_int16    __x, vector_int16    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uint2    __SIMD_ATTRIBUTES__ vector_max(vector_uint2    __x, vector_uint2    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uint2    __SIMD_ATTRIBUTES__ vector_min(vector_uint2    __x, vector_uint2    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uint3    __SIMD_ATTRIBUTES__ vector_max(vector_uint3    __x, vector_uint3    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uint3    __SIMD_ATTRIBUTES__ vector_min(vector_uint3    __x, vector_uint3    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uint4    __SIMD_ATTRIBUTES__ vector_max(vector_uint4    __x, vector_uint4    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uint4    __SIMD_ATTRIBUTES__ vector_min(vector_uint4    __x, vector_uint4    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uint8    __SIMD_ATTRIBUTES__ vector_max(vector_uint8    __x, vector_uint8    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uint8    __SIMD_ATTRIBUTES__ vector_min(vector_uint8    __x, vector_uint8    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_uint16   __SIMD_ATTRIBUTES__ vector_max(vector_uint16   __x, vector_uint16   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_uint16   __SIMD_ATTRIBUTES__ vector_min(vector_uint16   __x, vector_uint16   __y) { return vector_bitselect(__x, __y, __y < __x); }
#endif
static vector_float2   __SIMD_ATTRIBUTES__ vector_max(vector_float2   __x, vector_float2   __y) { return __tg_fmax(__x,__y); }
static vector_float2   __SIMD_ATTRIBUTES__ vector_min(vector_float2   __x, vector_float2   __y) { return __tg_fmin(__x,__y); }
static vector_float3   __SIMD_ATTRIBUTES__ vector_max(vector_float3   __x, vector_float3   __y) { return __tg_fmax(__x,__y); }
static vector_float3   __SIMD_ATTRIBUTES__ vector_min(vector_float3   __x, vector_float3   __y) { return __tg_fmin(__x,__y); }
static vector_float4   __SIMD_ATTRIBUTES__ vector_max(vector_float4   __x, vector_float4   __y) { return __tg_fmax(__x,__y); }
static vector_float4   __SIMD_ATTRIBUTES__ vector_min(vector_float4   __x, vector_float4   __y) { return __tg_fmin(__x,__y); }
static vector_float8   __SIMD_ATTRIBUTES__ vector_max(vector_float8   __x, vector_float8   __y) { return __tg_fmax(__x,__y); }
static vector_float8   __SIMD_ATTRIBUTES__ vector_min(vector_float8   __x, vector_float8   __y) { return __tg_fmin(__x,__y); }
static vector_float16  __SIMD_ATTRIBUTES__ vector_max(vector_float16  __x, vector_float16  __y) { return __tg_fmax(__x,__y); }
static vector_float16  __SIMD_ATTRIBUTES__ vector_min(vector_float16  __x, vector_float16  __y) { return __tg_fmin(__x,__y); }
static vector_long2    __SIMD_ATTRIBUTES__ vector_max(vector_long2    __x, vector_long2    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_long2    __SIMD_ATTRIBUTES__ vector_min(vector_long2    __x, vector_long2    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_long3    __SIMD_ATTRIBUTES__ vector_max(vector_long3    __x, vector_long3    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_long3    __SIMD_ATTRIBUTES__ vector_min(vector_long3    __x, vector_long3    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_long4    __SIMD_ATTRIBUTES__ vector_max(vector_long4    __x, vector_long4    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_long4    __SIMD_ATTRIBUTES__ vector_min(vector_long4    __x, vector_long4    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_long8    __SIMD_ATTRIBUTES__ vector_max(vector_long8    __x, vector_long8    __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_long8    __SIMD_ATTRIBUTES__ vector_min(vector_long8    __x, vector_long8    __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ulong2   __SIMD_ATTRIBUTES__ vector_max(vector_ulong2   __x, vector_ulong2   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ulong2   __SIMD_ATTRIBUTES__ vector_min(vector_ulong2   __x, vector_ulong2   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ulong3   __SIMD_ATTRIBUTES__ vector_max(vector_ulong3   __x, vector_ulong3   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ulong3   __SIMD_ATTRIBUTES__ vector_min(vector_ulong3   __x, vector_ulong3   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ulong4   __SIMD_ATTRIBUTES__ vector_max(vector_ulong4   __x, vector_ulong4   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ulong4   __SIMD_ATTRIBUTES__ vector_min(vector_ulong4   __x, vector_ulong4   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_ulong8   __SIMD_ATTRIBUTES__ vector_max(vector_ulong8   __x, vector_ulong8   __y) { return vector_bitselect(__x, __y, __y > __x); }
static vector_ulong8   __SIMD_ATTRIBUTES__ vector_min(vector_ulong8   __x, vector_ulong8   __y) { return vector_bitselect(__x, __y, __y < __x); }
static vector_double2  __SIMD_ATTRIBUTES__ vector_max(vector_double2  __x, vector_double2  __y) { return __tg_fmax(__x,__y); }
static vector_double2  __SIMD_ATTRIBUTES__ vector_min(vector_double2  __x, vector_double2  __y) { return __tg_fmin(__x,__y); }
static vector_double3  __SIMD_ATTRIBUTES__ vector_max(vector_double3  __x, vector_double3  __y) { return __tg_fmax(__x,__y); }
static vector_double3  __SIMD_ATTRIBUTES__ vector_min(vector_double3  __x, vector_double3  __y) { return __tg_fmin(__x,__y); }
static vector_double4  __SIMD_ATTRIBUTES__ vector_max(vector_double4  __x, vector_double4  __y) { return __tg_fmax(__x,__y); }
static vector_double4  __SIMD_ATTRIBUTES__ vector_min(vector_double4  __x, vector_double4  __y) { return __tg_fmin(__x,__y); }
static vector_double8  __SIMD_ATTRIBUTES__ vector_max(vector_double8  __x, vector_double8  __y) { return __tg_fmax(__x,__y); }
static vector_double8  __SIMD_ATTRIBUTES__ vector_min(vector_double8  __x, vector_double8  __y) { return __tg_fmin(__x,__y); }

static vector_char2    __SIMD_ATTRIBUTES__ vector_clamp(vector_char2    __x, vector_char2    __min, vector_char2    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_char3    __SIMD_ATTRIBUTES__ vector_clamp(vector_char3    __x, vector_char3    __min, vector_char3    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_char4    __SIMD_ATTRIBUTES__ vector_clamp(vector_char4    __x, vector_char4    __min, vector_char4    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_char8    __SIMD_ATTRIBUTES__ vector_clamp(vector_char8    __x, vector_char8    __min, vector_char8    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_char16   __SIMD_ATTRIBUTES__ vector_clamp(vector_char16   __x, vector_char16   __min, vector_char16   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_char32   __SIMD_ATTRIBUTES__ vector_clamp(vector_char32   __x, vector_char32   __min, vector_char32   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uchar2   __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar2   __x, vector_uchar2   __min, vector_uchar2   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uchar3   __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar3   __x, vector_uchar3   __min, vector_uchar3   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uchar4   __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar4   __x, vector_uchar4   __min, vector_uchar4   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uchar8   __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar8   __x, vector_uchar8   __min, vector_uchar8   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uchar16  __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar16  __x, vector_uchar16  __min, vector_uchar16  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uchar32  __SIMD_ATTRIBUTES__ vector_clamp(vector_uchar32  __x, vector_uchar32  __min, vector_uchar32  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_short2   __SIMD_ATTRIBUTES__ vector_clamp(vector_short2   __x, vector_short2   __min, vector_short2   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_short3   __SIMD_ATTRIBUTES__ vector_clamp(vector_short3   __x, vector_short3   __min, vector_short3   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_short4   __SIMD_ATTRIBUTES__ vector_clamp(vector_short4   __x, vector_short4   __min, vector_short4   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_short8   __SIMD_ATTRIBUTES__ vector_clamp(vector_short8   __x, vector_short8   __min, vector_short8   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_short16  __SIMD_ATTRIBUTES__ vector_clamp(vector_short16  __x, vector_short16  __min, vector_short16  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_short32  __SIMD_ATTRIBUTES__ vector_clamp(vector_short32  __x, vector_short32  __min, vector_short32  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ushort2  __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort2  __x, vector_ushort2  __min, vector_ushort2  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ushort3  __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort3  __x, vector_ushort3  __min, vector_ushort3  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ushort4  __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort4  __x, vector_ushort4  __min, vector_ushort4  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ushort8  __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort8  __x, vector_ushort8  __min, vector_ushort8  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ushort16 __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort16 __x, vector_ushort16 __min, vector_ushort16 __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ushort32 __SIMD_ATTRIBUTES__ vector_clamp(vector_ushort32 __x, vector_ushort32 __min, vector_ushort32 __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_int2     __SIMD_ATTRIBUTES__ vector_clamp(vector_int2     __x, vector_int2     __min, vector_int2     __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_int3     __SIMD_ATTRIBUTES__ vector_clamp(vector_int3     __x, vector_int3     __min, vector_int3     __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_int4     __SIMD_ATTRIBUTES__ vector_clamp(vector_int4     __x, vector_int4     __min, vector_int4     __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_int8     __SIMD_ATTRIBUTES__ vector_clamp(vector_int8     __x, vector_int8     __min, vector_int8     __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_int16    __SIMD_ATTRIBUTES__ vector_clamp(vector_int16    __x, vector_int16    __min, vector_int16    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uint2    __SIMD_ATTRIBUTES__ vector_clamp(vector_uint2    __x, vector_uint2    __min, vector_uint2    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uint3    __SIMD_ATTRIBUTES__ vector_clamp(vector_uint3    __x, vector_uint3    __min, vector_uint3    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uint4    __SIMD_ATTRIBUTES__ vector_clamp(vector_uint4    __x, vector_uint4    __min, vector_uint4    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uint8    __SIMD_ATTRIBUTES__ vector_clamp(vector_uint8    __x, vector_uint8    __min, vector_uint8    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_uint16   __SIMD_ATTRIBUTES__ vector_clamp(vector_uint16   __x, vector_uint16   __min, vector_uint16   __max) { return vector_min(vector_max(__x,__min),__max); }
static float           __SIMD_ATTRIBUTES__ vector_clamp(float           __x, float           __min, float           __max) { return __tg_fmin(__tg_fmax(__x,__min),__max); }
static vector_float2   __SIMD_ATTRIBUTES__ vector_clamp(vector_float2   __x, vector_float2   __min, vector_float2   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_float3   __SIMD_ATTRIBUTES__ vector_clamp(vector_float3   __x, vector_float3   __min, vector_float3   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_float4   __SIMD_ATTRIBUTES__ vector_clamp(vector_float4   __x, vector_float4   __min, vector_float4   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_float8   __SIMD_ATTRIBUTES__ vector_clamp(vector_float8   __x, vector_float8   __min, vector_float8   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_float16  __SIMD_ATTRIBUTES__ vector_clamp(vector_float16  __x, vector_float16  __min, vector_float16  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_long2    __SIMD_ATTRIBUTES__ vector_clamp(vector_long2    __x, vector_long2    __min, vector_long2    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_long3    __SIMD_ATTRIBUTES__ vector_clamp(vector_long3    __x, vector_long3    __min, vector_long3    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_long4    __SIMD_ATTRIBUTES__ vector_clamp(vector_long4    __x, vector_long4    __min, vector_long4    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_long8    __SIMD_ATTRIBUTES__ vector_clamp(vector_long8    __x, vector_long8    __min, vector_long8    __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ulong2   __SIMD_ATTRIBUTES__ vector_clamp(vector_ulong2   __x, vector_ulong2   __min, vector_ulong2   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ulong3   __SIMD_ATTRIBUTES__ vector_clamp(vector_ulong3   __x, vector_ulong3   __min, vector_ulong3   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ulong4   __SIMD_ATTRIBUTES__ vector_clamp(vector_ulong4   __x, vector_ulong4   __min, vector_ulong4   __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_ulong8   __SIMD_ATTRIBUTES__ vector_clamp(vector_ulong8   __x, vector_ulong8   __min, vector_ulong8   __max) { return vector_min(vector_max(__x,__min),__max); }
static double          __SIMD_ATTRIBUTES__ vector_clamp(double          __x, double          __min, double          __max) { return __tg_fmin(__tg_fmax(__x,__min),__max); }
static vector_double2  __SIMD_ATTRIBUTES__ vector_clamp(vector_double2  __x, vector_double2  __min, vector_double2  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_double3  __SIMD_ATTRIBUTES__ vector_clamp(vector_double3  __x, vector_double3  __min, vector_double3  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_double4  __SIMD_ATTRIBUTES__ vector_clamp(vector_double4  __x, vector_double4  __min, vector_double4  __max) { return vector_min(vector_max(__x,__min),__max); }
static vector_double8  __SIMD_ATTRIBUTES__ vector_clamp(vector_double8  __x, vector_double8  __min, vector_double8  __max) { return vector_min(vector_max(__x,__min),__max); }

#if __FINITE_MATH_ONLY__
static float          __SIMD_ATTRIBUTES__ vector_sign(float          __x) { return __x == 0 ? 0 : __tg_copysign(1,__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_sign(vector_float2  __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_sign(vector_float3  __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_sign(vector_float4  __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_sign(vector_float8  __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_sign(vector_float16 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
static double         __SIMD_ATTRIBUTES__ vector_sign(double         __x) { return __x == 0 ? 0 : __tg_copysign(1,__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_sign(vector_double2 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_sign(vector_double3 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_sign(vector_double4 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_sign(vector_double8 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, __x == 0); }
#else
static float          __SIMD_ATTRIBUTES__ vector_sign(float          __x) { return (__x == 0) || (__x != __x) ? 0 : __tg_copysign(1,__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_sign(vector_float2  __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_sign(vector_float3  __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_sign(vector_float4  __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_sign(vector_float8  __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_sign(vector_float16 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
static double         __SIMD_ATTRIBUTES__ vector_sign(double         __x) { return (__x == 0) || (__x != __x) ? 0 : __tg_copysign(1,__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_sign(vector_double2 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_sign(vector_double3 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_sign(vector_double4 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_sign(vector_double8 __x) { return vector_bitselect(__tg_copysign(1,__x), 0, (__x == 0) | (__x != __x)); }
#endif

static float          __SIMD_ATTRIBUTES__ vector_mix(float          __x, float          __y, float          __t) { return __x + __t*(__y - __x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_mix(vector_float2  __x, vector_float2  __y, vector_float2  __t) { return __x + __t*(__y - __x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_mix(vector_float3  __x, vector_float3  __y, vector_float3  __t) { return __x + __t*(__y - __x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_mix(vector_float4  __x, vector_float4  __y, vector_float4  __t) { return __x + __t*(__y - __x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_mix(vector_float8  __x, vector_float8  __y, vector_float8  __t) { return __x + __t*(__y - __x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_mix(vector_float16 __x, vector_float16 __y, vector_float16 __t) { return __x + __t*(__y - __x); }
static double         __SIMD_ATTRIBUTES__ vector_mix(double         __x, double         __y, double         __t) { return __x + __t*(__y - __x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_mix(vector_double2 __x, vector_double2 __y, vector_double2 __t) { return __x + __t*(__y - __x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_mix(vector_double3 __x, vector_double3 __y, vector_double3 __t) { return __x + __t*(__y - __x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_mix(vector_double4 __x, vector_double4 __y, vector_double4 __t) { return __x + __t*(__y - __x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_mix(vector_double8 __x, vector_double8 __y, vector_double8 __t) { return __x + __t*(__y - __x); }

static float          __SIMD_ATTRIBUTES__ vector_precise_recip(float          __x) { return 1/__x; }
static vector_float2  __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float2  __x) { return 1/__x; }
static vector_float3  __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float3  __x) { return 1/__x; }
static vector_float4  __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float4  __x) { return 1/__x; }
static vector_float8  __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float8  __x) { return 1/__x; }
static vector_float16 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_float16 __x) { return 1/__x; }
static double         __SIMD_ATTRIBUTES__ vector_precise_recip(double         __x) { return 1/__x; }
static vector_double2 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_double2 __x) { return 1/__x; }
static vector_double3 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_double3 __x) { return 1/__x; }
static vector_double4 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_double4 __x) { return 1/__x; }
static vector_double8 __SIMD_ATTRIBUTES__ vector_precise_recip(vector_double8 __x) { return 1/__x; }

static float          __SIMD_ATTRIBUTES__ vector_fast_recip(float          __x) { return vector_precise_recip(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float2  __x) { return vector_precise_recip(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float3  __x) { return vector_precise_recip(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float4  __x) { return vector_precise_recip(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float8  __x) { return vector_precise_recip(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_float16 __x) { return vector_precise_recip(__x); }
static double         __SIMD_ATTRIBUTES__ vector_fast_recip(double         __x) { return vector_precise_recip(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_double2 __x) { return vector_precise_recip(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_double3 __x) { return vector_precise_recip(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_double4 __x) { return vector_precise_recip(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_fast_recip(vector_double8 __x) { return vector_precise_recip(__x); }

#if __FAST_MATH__
static float          __SIMD_ATTRIBUTES__ vector_recip(float          __x) { return vector_fast_recip(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_recip(vector_float2  __x) { return vector_fast_recip(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_recip(vector_float3  __x) { return vector_fast_recip(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_recip(vector_float4  __x) { return vector_fast_recip(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_recip(vector_float8  __x) { return vector_fast_recip(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_recip(vector_float16 __x) { return vector_fast_recip(__x); }
static double         __SIMD_ATTRIBUTES__ vector_recip(double         __x) { return vector_fast_recip(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_recip(vector_double2 __x) { return vector_fast_recip(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_recip(vector_double3 __x) { return vector_fast_recip(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_recip(vector_double4 __x) { return vector_fast_recip(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_recip(vector_double8 __x) { return vector_fast_recip(__x); }
#else
static float          __SIMD_ATTRIBUTES__ vector_recip(float          __x) { return vector_precise_recip(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_recip(vector_float2  __x) { return vector_precise_recip(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_recip(vector_float3  __x) { return vector_precise_recip(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_recip(vector_float4  __x) { return vector_precise_recip(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_recip(vector_float8  __x) { return vector_precise_recip(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_recip(vector_float16 __x) { return vector_precise_recip(__x); }
static double         __SIMD_ATTRIBUTES__ vector_recip(double         __x) { return vector_precise_recip(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_recip(vector_double2 __x) { return vector_precise_recip(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_recip(vector_double3 __x) { return vector_precise_recip(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_recip(vector_double4 __x) { return vector_precise_recip(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_recip(vector_double8 __x) { return vector_precise_recip(__x); }
#endif

static float          __SIMD_ATTRIBUTES__ vector_precise_rsqrt(float          __x) { return 1/__tg_sqrt(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float2  __x) { return 1/__tg_sqrt(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float3  __x) { return 1/__tg_sqrt(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float4  __x) { return 1/__tg_sqrt(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float8  __x) { return 1/__tg_sqrt(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_float16 __x) { return 1/__tg_sqrt(__x); }
static double         __SIMD_ATTRIBUTES__ vector_precise_rsqrt(double         __x) { return 1/__tg_sqrt(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_double2 __x) { return 1/__tg_sqrt(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_double3 __x) { return 1/__tg_sqrt(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_double4 __x) { return 1/__tg_sqrt(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_precise_rsqrt(vector_double8 __x) { return 1/__tg_sqrt(__x); }

static float          __SIMD_ATTRIBUTES__ vector_fast_rsqrt(float          __x) { return vector_precise_rsqrt(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float2  __x) { return vector_precise_rsqrt(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float3  __x) { return vector_precise_rsqrt(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float4  __x) { return vector_precise_rsqrt(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float8  __x) { return vector_precise_rsqrt(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_float16 __x) { return vector_precise_rsqrt(__x); }
static double         __SIMD_ATTRIBUTES__ vector_fast_rsqrt(double         __x) { return vector_precise_rsqrt(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_double2 __x) { return vector_precise_rsqrt(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_double3 __x) { return vector_precise_rsqrt(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_double4 __x) { return vector_precise_rsqrt(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_fast_rsqrt(vector_double8 __x) { return vector_precise_rsqrt(__x); }

#if __FAST_MATH__
static float          __SIMD_ATTRIBUTES__ vector_rsqrt(float          __x) { return vector_fast_rsqrt(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float2  __x) { return vector_fast_rsqrt(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float3  __x) { return vector_fast_rsqrt(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float4  __x) { return vector_fast_rsqrt(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float8  __x) { return vector_fast_rsqrt(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float16 __x) { return vector_fast_rsqrt(__x); }
static double         __SIMD_ATTRIBUTES__ vector_rsqrt(double         __x) { return vector_fast_rsqrt(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double2 __x) { return vector_fast_rsqrt(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double3 __x) { return vector_fast_rsqrt(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double4 __x) { return vector_fast_rsqrt(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double8 __x) { return vector_fast_rsqrt(__x); }
#else
static float          __SIMD_ATTRIBUTES__ vector_rsqrt(float          __x) { return vector_precise_rsqrt(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float2  __x) { return vector_precise_rsqrt(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float3  __x) { return vector_precise_rsqrt(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float4  __x) { return vector_precise_rsqrt(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float8  __x) { return vector_precise_rsqrt(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_float16 __x) { return vector_precise_rsqrt(__x); }
static double         __SIMD_ATTRIBUTES__ vector_rsqrt(double         __x) { return vector_precise_rsqrt(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double2 __x) { return vector_precise_rsqrt(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double3 __x) { return vector_precise_rsqrt(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double4 __x) { return vector_precise_rsqrt(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_rsqrt(vector_double8 __x) { return vector_precise_rsqrt(__x); }
#endif

static float          __SIMD_ATTRIBUTES__ vector_fract(float          __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffep-1f); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_fract(vector_float2  __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffep-1f); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_fract(vector_float3  __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffep-1f); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_fract(vector_float4  __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffep-1f); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_fract(vector_float8  __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffep-1f); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_fract(vector_float16 __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffep-1f); }
static double         __SIMD_ATTRIBUTES__ vector_fract(double         __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffffffffffp-1); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_fract(vector_double2 __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffffffffffp-1); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_fract(vector_double3 __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffffffffffp-1); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_fract(vector_double4 __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffffffffffp-1); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_fract(vector_double8 __x) { return __tg_fmin(__x - __tg_floor(__x), 0x1.fffffffffffffp-1); }

static float          __SIMD_ATTRIBUTES__ vector_step(float          __edge, float          __x) { return !(__x < __edge); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_step(vector_float2  __edge, vector_float2  __x) { return vector_bitselect((vector_float2)1, 0, __x < __edge); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_step(vector_float3  __edge, vector_float3  __x) { return vector_bitselect((vector_float3)1, 0, __x < __edge); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_step(vector_float4  __edge, vector_float4  __x) { return vector_bitselect((vector_float4)1, 0, __x < __edge); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_step(vector_float8  __edge, vector_float8  __x) { return vector_bitselect((vector_float8)1, 0, __x < __edge); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_step(vector_float16 __edge, vector_float16 __x) { return vector_bitselect((vector_float16)1, 0, __x < __edge); }
static double         __SIMD_ATTRIBUTES__ vector_step(double         __edge, double         __x) { return !(__x < __edge); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_step(vector_double2 __edge, vector_double2 __x) { return vector_bitselect((vector_double2)1, 0, __x < __edge); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_step(vector_double3 __edge, vector_double3 __x) { return vector_bitselect((vector_double3)1, 0, __x < __edge); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_step(vector_double4 __edge, vector_double4 __x) { return vector_bitselect((vector_double4)1, 0, __x < __edge); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_step(vector_double8 __edge, vector_double8 __x) { return vector_bitselect((vector_double8)1, 0, __x < __edge); }

static float          __SIMD_ATTRIBUTES__ vector_smoothstep(float          __edge0, float          __edge1, float          __x) { float          __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_float2  __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float2  __edge0, vector_float2  __edge1, vector_float2  __x) { vector_float2  __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float3  __edge0, vector_float3  __edge1, vector_float3  __x) { vector_float3  __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float4  __edge0, vector_float4  __edge1, vector_float4  __x) { vector_float4  __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float8  __edge0, vector_float8  __edge1, vector_float8  __x) { vector_float8  __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_float16 __edge0, vector_float16 __edge1, vector_float16 __x) { vector_float16 __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static double         __SIMD_ATTRIBUTES__ vector_smoothstep(double         __edge0, double         __edge1, double         __x) { double         __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_double2 __edge0, vector_double2 __edge1, vector_double2 __x) { vector_double2 __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_double3 __edge0, vector_double3 __edge1, vector_double3 __x) { vector_double3 __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_double4 __edge0, vector_double4 __edge1, vector_double4 __x) { vector_double4 __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_smoothstep(vector_double8 __edge0, vector_double8 __edge1, vector_double8 __x) { vector_double8 __t = vector_clamp((__x - __edge0)/(__edge1 - __edge0), 0, 1); return __t*__t*(3 - 2*__t); }

#ifdef __cplusplus
}
#endif
#endif /* __SIMD_REQUIRED_COMPILER_FEATURES__ */
#endif /* __SIMD_COMMON_HEADER__ */
