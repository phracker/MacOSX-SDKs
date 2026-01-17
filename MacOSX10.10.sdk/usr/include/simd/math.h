/*  Copyright (c) 2014 Apple, Inc. All rights reserved.      
 *
 *  The interfaces declared in this header provide elementwise math operations
 *  on vectors; each lane of the result vector depends only on the data in the
 *  corresponding lane of the argument(s) to the function.
 *
 *  These functions perform operations that are declared for scalar types in
 *  <math.h>.  Overloading necessarily introduces a significant amount of noise
 *  into the declarations of these functions.  Thus, the following list of
 *  operations is generally more useful for documentation purposes than the
 *  declarations themselves.  The C and Objective-C math functions that are
 *  exported by the library are as follows:
 *
 *      Function                Result
 *      ---------------------------------------------------------------------
 *      fabs(x)                 Absolute value of x.
 *
 *      fmax(x,y)               Maximum of x and y.  If one of x or y is NaN,
 *                              fmax returns the other value.[1]
 *
 *      fmin(x,y)               Minimum of x and y.  If one of x or y is NaN,
 *                              fmin returns the other value.[1]
 *
 *      copysign(x,y)           The number with the same magnitude as x and
 *                              the same sign as y.  Undefined if x and y are
 *                              integers and x is INT_MIN and y is positive.
 *
 *      sqrt(x)                 The square root of x.
 *
 *      ceil(x)                 The largest integral value that is greater than
 *                              or equal to x; returns x if x is infinity or
 *                              NaN.
 *
 *      floor(x)                The largest integral value that is less than or
 *                              equal to x; returns x if x is infinity or NaN.
 *
 *      rint(x)                 x rounded to integer according to the current
 *                              rounding mode.  Returns x if x is infinity or
 *                              NaN.
 *
 *      trunc(x)                The integral value obtained by clearing any
 *                              fractional bits of x.  Returns x if x is
 *                              infinity or NaN.
 *
 *      cos(x)                  The cosine of x.
 *
 *      sin(x)                  The sine of x.
 *
 *  [1] When using fmax or fmin to clamp with a constant, place the constant
 *  in the second argument position.  This results in better codegen on some
 *  architectures.  E.g. use "fmin(x, 1.0f)" to clamp to the range [-inf,1].
 *
 *  In C++, these overloads are available under the SIMD:: namespace:
 *
 *      C++ Function                    Equivalent C Function
 *      --------------------------------------------------------------------
 *      SIMD::fabs(x)                   fabs(x)
 *      SIMD::fmax(x,y)                 fmax(x)
 *      SIMD::fmin(x,y)                 fmin(x)
 *      SIMD::copysign(x,y)             copysign(x,y)
 *      SIMD::sqrt(x)                   sqrt(x)
 *      SIMD::ceil(x)                   ceil(x)
 *      SIMD::floor(x)                  floor(x)
 *      SIMD::rint(x)                   rint(x)
 *      SIMD::trunc(x)                  trunc(x)
 *      SIMD::cos(x)                    cos(x)
 *      SIMD::sin(x)                    sin(x)                                 
 */

#ifndef __SIMD_MATH_HEADER__
#define __SIMD_MATH_HEADER__

#include <simd/internal.h>
#if __SIMD_REQUIRED_COMPILER_FEATURES__
#include <simd/vector_types.h>
#include <simd/logic.h>
#include <simd/extern.h>

#ifdef __cplusplus
extern "C" {
#endif

static vector_float2  __SIMD_ATTRIBUTES__ __tg_fabs(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_fabs(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fabs(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_fabs(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_fabs(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fabs(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_fabs(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_fabs(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_fabs(vector_double8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float2  __x, vector_float2  __y);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float3  __x, vector_float3  __y);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float4  __x, vector_float4  __y);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float8  __x, vector_float8  __y);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_fmax(vector_float16 __x, vector_float16 __y);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double2 __x, vector_double2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double3 __x, vector_double3 __y);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double4 __x, vector_double4 __y);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double8 __x, vector_double8 __y);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float2  __x, vector_float2  __y);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float3  __x, vector_float3  __y);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float4  __x, vector_float4  __y);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float8  __x, vector_float8  __y);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_fmin(vector_float16 __x, vector_float16 __y);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double2 __x, vector_double2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double3 __x, vector_double3 __y);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double4 __x, vector_double4 __y);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double8 __x, vector_double8 __y);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_copysign(vector_float2  __x, vector_float2  __y);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_copysign(vector_float3  __x, vector_float3  __y);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_copysign(vector_float4  __x, vector_float4  __y);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_copysign(vector_float8  __x, vector_float8  __y);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_copysign(vector_float16 __x, vector_float16 __y);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_copysign(vector_double2 __x, vector_double2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_copysign(vector_double3 __x, vector_double3 __y);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_copysign(vector_double4 __x, vector_double4 __y);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_copysign(vector_double8 __x, vector_double8 __y);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_sqrt(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_sqrt(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_sqrt(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_sqrt(vector_double8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_ceil(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_ceil(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_ceil(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_ceil(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_ceil(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_ceil(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_ceil(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_ceil(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_ceil(vector_double8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_floor(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_floor(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_floor(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_floor(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_floor(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_floor(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_floor(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_floor(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_floor(vector_double8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_rint(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_rint(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_rint(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_rint(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_rint(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_rint(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_rint(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_rint(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_rint(vector_double8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_trunc(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ __tg_trunc(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_trunc(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ __tg_trunc(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ __tg_trunc(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ __tg_trunc(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ __tg_trunc(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ __tg_trunc(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ __tg_trunc(vector_double8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_cos(vector_float2  __x) __SIMD_AVAILABILITY__;
static vector_float3  __SIMD_ATTRIBUTES__ __tg_cos(vector_float3  __x) __SIMD_AVAILABILITY__;
static vector_float4  __SIMD_ATTRIBUTES__ __tg_cos(vector_float4  __x) __SIMD_AVAILABILITY__;
static vector_float8  __SIMD_ATTRIBUTES__ __tg_cos(vector_float8  __x) __SIMD_AVAILABILITY__;
static vector_float16 __SIMD_ATTRIBUTES__ __tg_cos(vector_float16 __x) __SIMD_AVAILABILITY__;
static vector_double2 __SIMD_ATTRIBUTES__ __tg_cos(vector_double2 __x) __SIMD_AVAILABILITY__;
static vector_double3 __SIMD_ATTRIBUTES__ __tg_cos(vector_double3 __x) __SIMD_AVAILABILITY__;
static vector_double4 __SIMD_ATTRIBUTES__ __tg_cos(vector_double4 __x) __SIMD_AVAILABILITY__;
static vector_double8 __SIMD_ATTRIBUTES__ __tg_cos(vector_double8 __x) __SIMD_AVAILABILITY__;

static vector_float2  __SIMD_ATTRIBUTES__ __tg_sin(vector_float2  __x) __SIMD_AVAILABILITY__;
static vector_float3  __SIMD_ATTRIBUTES__ __tg_sin(vector_float3  __x) __SIMD_AVAILABILITY__;
static vector_float4  __SIMD_ATTRIBUTES__ __tg_sin(vector_float4  __x) __SIMD_AVAILABILITY__;
static vector_float8  __SIMD_ATTRIBUTES__ __tg_sin(vector_float8  __x) __SIMD_AVAILABILITY__;
static vector_float16 __SIMD_ATTRIBUTES__ __tg_sin(vector_float16 __x) __SIMD_AVAILABILITY__;
static vector_double2 __SIMD_ATTRIBUTES__ __tg_sin(vector_double2 __x) __SIMD_AVAILABILITY__;
static vector_double3 __SIMD_ATTRIBUTES__ __tg_sin(vector_double3 __x) __SIMD_AVAILABILITY__;
static vector_double4 __SIMD_ATTRIBUTES__ __tg_sin(vector_double4 __x) __SIMD_AVAILABILITY__;
static vector_double8 __SIMD_ATTRIBUTES__ __tg_sin(vector_double8 __x) __SIMD_AVAILABILITY__;

#ifdef __cplusplus
} /* extern "C" */

/*  Some of the implementations require __tg_* operations that are not defined
 *  in the vector_math headers; in C they come from <tgmath.h>, but that header
 *  does not define them for C++; we need to provide definitions here to make
 *  those implementations work correctly.  This is only necessary for
 *  operations used internally in this header, as developers should not be
 *  using the __tg_* names at all.                                            */
#include <cmath>
static float  __SIMD_ATTRIBUTES__ __tg_fabs(const float x) { return std::abs(x); }
static double __SIMD_ATTRIBUTES__ __tg_fabs(const double x) { return std::abs(x); }
static float  __SIMD_ATTRIBUTES__ __tg_fmax(const float x, const float y) { return fmax(x, y); }
static double __SIMD_ATTRIBUTES__ __tg_fmax(double x, double y) { return fmax(x, y); }
static float  __SIMD_ATTRIBUTES__ __tg_fmin(const float x, const float y) { return fmin(x,y); }
static double __SIMD_ATTRIBUTES__ __tg_fmin(const double x, const double y) { return fmin(x,y); }
static float  __SIMD_ATTRIBUTES__ __tg_copysign(const float x, const float y) { return copysign(x,y); }
static double __SIMD_ATTRIBUTES__ __tg_copysign(const double x, const double y) { return copysign(x,y); }
static float  __SIMD_ATTRIBUTES__ __tg_sqrt(const float x) { return sqrt(x); }
static double __SIMD_ATTRIBUTES__ __tg_sqrt(const double x) { return sqrt(x); }
static float  __SIMD_ATTRIBUTES__ __tg_ceil(const float x) { return ceil(x); }
static double __SIMD_ATTRIBUTES__ __tg_ceil(const double x) { return ceil(x); }
static float  __SIMD_ATTRIBUTES__ __tg_floor(const float x) { return floor(x); }
static double __SIMD_ATTRIBUTES__ __tg_floor(const double x) { return floor(x); }
static float  __SIMD_ATTRIBUTES__ __tg_rint(const float x) { return rint(x); }
static double __SIMD_ATTRIBUTES__ __tg_rint(const double x) { return rint(x); }
static float  __SIMD_ATTRIBUTES__ __tg_trunc(const float x) { return trunc(x); }
static double __SIMD_ATTRIBUTES__ __tg_trunc(const double x) { return trunc(x); }
static float  __SIMD_ATTRIBUTES__ __tg_sin(const float x) { return sin(x); }
static double __SIMD_ATTRIBUTES__ __tg_sin(const double x) { return sin(x); }
static float  __SIMD_ATTRIBUTES__ __tg_cos(const float x) { return cos(x); }
static double __SIMD_ATTRIBUTES__ __tg_cos(const double x) { return cos(x); }

namespace simd {
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN fabs(fptypeN x) { return ::__tg_fabs(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN fmax(fptypeN x, fptypeN y) { return ::__tg_fmax(x,y); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN fmin(fptypeN x, fptypeN y) { return ::__tg_fmin(x,y); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN copysign(fptypeN x, fptypeN y) { return ::__tg_copysign(x,y); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN sqrt(fptypeN x) { return ::__tg_sqrt(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN ceil(fptypeN x) { return ::__tg_ceil(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN floor(fptypeN x) { return ::__tg_floor(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN rint(fptypeN x) { return ::__tg_rint(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN trunc(fptypeN x) { return ::__tg_trunc(x); }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN cos(fptypeN x) __SIMD_AVAILABILITY__ { return ::__tg_cos(x); }
    template <typename fptypeN> static __SIMD_INLINE__ fptypeN sin(fptypeN x) __SIMD_AVAILABILITY__ { return ::__tg_sin(x); }
#pragma clang diagnostic pop
}

extern "C" {
#else

#include <tgmath.h>
/* C and Objective-C, we need some infrastructure to piggyback on tgmath.h    */
static vector_float2 __attribute__((__overloadable__)) __tg_promote(vector_float2);
static vector_float3 __attribute__((__overloadable__)) __tg_promote(vector_float3);
static vector_float4 __attribute__((__overloadable__)) __tg_promote(vector_float4);
static vector_float8 __attribute__((__overloadable__)) __tg_promote(vector_float8);
static vector_float16 __attribute__((__overloadable__)) __tg_promote(vector_float16);
static vector_double2 __attribute__((__overloadable__)) __tg_promote(vector_double2);
static vector_double3 __attribute__((__overloadable__)) __tg_promote(vector_double3);
static vector_double4 __attribute__((__overloadable__)) __tg_promote(vector_double4);
static vector_double8 __attribute__((__overloadable__)) __tg_promote(vector_double8);
#endif /* __cplusplus */

#pragma mark - Implementations

static vector_float2  __SIMD_ATTRIBUTES__ __tg_fabs(vector_float2  __x) { return vector_bitselect(0.f, __x, 0x7fffffff); }
static vector_float3  __SIMD_ATTRIBUTES__ __tg_fabs(vector_float3  __x) { return vector_bitselect(0.f, __x, 0x7fffffff); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fabs(vector_float4  __x) { return vector_bitselect(0.f, __x, 0x7fffffff); }
static vector_float8  __SIMD_ATTRIBUTES__ __tg_fabs(vector_float8  __x) { return vector_bitselect(0.f, __x, 0x7fffffff); }
static vector_float16 __SIMD_ATTRIBUTES__ __tg_fabs(vector_float16 __x) { return vector_bitselect(0.f, __x, 0x7fffffff); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fabs(vector_double2 __x) { return vector_bitselect(0., __x, 0x7fffffffffffffff); }
static vector_double3 __SIMD_ATTRIBUTES__ __tg_fabs(vector_double3 __x) { return vector_bitselect(0., __x, 0x7fffffffffffffff); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_fabs(vector_double4 __x) { return vector_bitselect(0., __x, 0x7fffffffffffffff); }
static vector_double8 __SIMD_ATTRIBUTES__ __tg_fabs(vector_double8 __x) { return vector_bitselect(0., __x, 0x7fffffffffffffff); }

#if defined __SSE2__
__SIMD_ELEMENTWISE_BINARY_2_IN_4(__tg_fmax,float);
__SIMD_ELEMENTWISE_BINARY_2_IN_4(__tg_fmin,float);
#   if __FINITE_MATH_ONLY__
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float4  __x, vector_float4  __y) { return _mm_max_ps(__x,__y); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float4  __x, vector_float4  __y) { return _mm_min_ps(__x,__y); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double2 __x, vector_double2 __y) { return _mm_max_pd(__x,__y); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double2 __x, vector_double2 __y) { return _mm_min_pd(__x,__y); }
#   else
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float4  __x, vector_float4  __y) { return vector_bitselect(_mm_max_ps(__x,__y), __x, __y != __y); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float4  __x, vector_float4  __y) { return vector_bitselect(_mm_min_ps(__x,__y), __x, __y != __y); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double2 __x, vector_double2 __y) { return vector_bitselect(_mm_max_pd(__x,__y), __x, __y != __y); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double2 __x, vector_double2 __y) { return vector_bitselect(_mm_min_pd(__x,__y), __x, __y != __y); }
#   endif /* __FINITE_MATH_ONLY__ */
#elif defined __arm64__
static vector_float2  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float2  __x, vector_float2  __y) { return vmaxnm_f32(__x, __y); }
static vector_float2  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float2  __x, vector_float2  __y) { return vminnm_f32(__x, __y); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float4  __x, vector_float4  __y) { return vmaxnmq_f32(__x, __y); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float4  __x, vector_float4  __y) { return vminnmq_f32(__x, __y); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double2 __x, vector_double2 __y) { return vmaxnmq_f64(__x,__y); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double2 __x, vector_double2 __y) { return vmaxnmq_f64(__x,__y); }
#elif defined __arm__ && __FINITE_MATH_ONLY__
static vector_float2  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float2  __x, vector_float2  __y) { return vmax_f32(__x, __y); }
static vector_float2  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float2  __x, vector_float2  __y) { return vmin_f32(__x, __y); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float4  __x, vector_float4  __y) { return vmaxq_f32(__x, __y); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float4  __x, vector_float4  __y) { return vminq_f32(__x, __y); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double2 __x, vector_double2 __y) { vector_double2 __z = { __tg_fmax(__x[0],__y[0]), __tg_fmax(__x[1],__y[1])}; return __z; }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double2 __x, vector_double2 __y) { vector_double2 __z = { __tg_fmin(__x[0],__y[0]), __tg_fmin(__x[1],__y[1])}; return __z; }
#else
__SIMD_ELEMENTWISE_BINARY_2_IN_4(__tg_fmax,float);
__SIMD_ELEMENTWISE_BINARY_2_IN_4(__tg_fmin,float);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float4  __x, vector_float4  __y) { return vector_bitselect(__y, __x, (__x >= __y) | (__y != __y)); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float4  __x, vector_float4  __y) { return vector_bitselect(__y, __x, (__x >= __y) | (__y != __y)); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double2 __x, vector_double2 __y) { return vector_bitselect(__y, __x, (__x >= __y) | (__y != __y)); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double2 __x, vector_double2 __y) { return vector_bitselect(__y, __x, (__x >= __y) | (__y != __y)); }
#endif
__SIMD_ELEMENTWISE_BINARY_3_IN_4(__tg_fmax,float);
__SIMD_ELEMENTWISE_BINARY_3_IN_4(__tg_fmin,float);
__SIMD_ELEMENTWISE_BINARY_3_IN_4(__tg_fmax,double);
__SIMD_ELEMENTWISE_BINARY_3_IN_4(__tg_fmin,double);
#if defined __AVX__
#   if __FINITE_MATH_ONLY__
static vector_float8  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float8  __x, vector_float8  __y) { return _mm256_max_ps(__x,__y); }
static vector_float8  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float8  __x, vector_float8  __y) { return _mm256_min_ps(__x,__y); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double4 __x, vector_double4 __y) { return _mm256_max_pd(__x,__y); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double4 __x, vector_double4 __y) { return _mm256_min_pd(__x,__y); }
#   else
static vector_float8  __SIMD_ATTRIBUTES__ __tg_fmax(vector_float8  __x, vector_float8  __y) { return vector_bitselect(_mm256_max_ps(__x,__y), __x, __y != __y); }
static vector_float8  __SIMD_ATTRIBUTES__ __tg_fmin(vector_float8  __x, vector_float8  __y) { return vector_bitselect(_mm256_min_ps(__x,__y), __x, __y != __y); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_fmax(vector_double4 __x, vector_double4 __y) { return vector_bitselect(_mm256_max_pd(__x,__y), __x, __y != __y); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_fmin(vector_double4 __x, vector_double4 __y) { return vector_bitselect(_mm256_min_pd(__x,__y), __x, __y != __y); }
#   endif /* __FINITE_MATH_ONLY__ */
#else
__SIMD_ELEMENTWISE_BINARY_8_IN_4(__tg_fmax,float);
__SIMD_ELEMENTWISE_BINARY_8_IN_4(__tg_fmin,float);
__SIMD_ELEMENTWISE_BINARY_4_IN_2(__tg_fmax,double);
__SIMD_ELEMENTWISE_BINARY_4_IN_2(__tg_fmin,double);
#endif
__SIMD_ELEMENTWISE_BINARY_16_IN_8(__tg_fmax,float);
__SIMD_ELEMENTWISE_BINARY_16_IN_8(__tg_fmin,float);
__SIMD_ELEMENTWISE_BINARY_8_IN_4(__tg_fmax,double);
__SIMD_ELEMENTWISE_BINARY_8_IN_4(__tg_fmin,double);

static vector_float2  __SIMD_ATTRIBUTES__ __tg_copysign(vector_float2  __x, vector_float2  __y) { return vector_bitselect(__y, __x, 0x7fffffff); }
static vector_float3  __SIMD_ATTRIBUTES__ __tg_copysign(vector_float3  __x, vector_float3  __y) { return vector_bitselect(__y, __x, 0x7fffffff); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_copysign(vector_float4  __x, vector_float4  __y) { return vector_bitselect(__y, __x, 0x7fffffff); }
static vector_float8  __SIMD_ATTRIBUTES__ __tg_copysign(vector_float8  __x, vector_float8  __y) { return vector_bitselect(__y, __x, 0x7fffffff); }
static vector_float16 __SIMD_ATTRIBUTES__ __tg_copysign(vector_float16 __x, vector_float16 __y) { return vector_bitselect(__y, __x, 0x7fffffff); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_copysign(vector_double2 __x, vector_double2 __y) { return vector_bitselect(__y, __x, 0x7fffffffffffffff); }
static vector_double3 __SIMD_ATTRIBUTES__ __tg_copysign(vector_double3 __x, vector_double3 __y) { return vector_bitselect(__y, __x, 0x7fffffffffffffff); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_copysign(vector_double4 __x, vector_double4 __y) { return vector_bitselect(__y, __x, 0x7fffffffffffffff); }
static vector_double8 __SIMD_ATTRIBUTES__ __tg_copysign(vector_double8 __x, vector_double8 __y) { return vector_bitselect(__y, __x, 0x7fffffffffffffff); }

#if defined __SSE2__
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_sqrt,float);
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_sqrt,float);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float4  __x) { return _mm_sqrt_ps(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_sqrt(vector_double2 __x) { return _mm_sqrt_pd(__x); }
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_sqrt,double);
#elif defined __arm64__
static vector_float2  __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float2  __x) { return vsqrt_f32(__x); }
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_sqrt,float);
static vector_float4  __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float4  __x) { return vsqrtq_f32(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_sqrt(vector_double2 __x) { return vsqrtq_f64(__x); }
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_sqrt,double);
#else
__SIMD_ELEMENTWISE_UNARY_IN_SCALAR(__tg_sqrt,float,2)
__SIMD_ELEMENTWISE_UNARY_IN_SCALAR(__tg_sqrt,float,3)
__SIMD_ELEMENTWISE_UNARY_IN_SCALAR(__tg_sqrt,float,4)
__SIMD_ELEMENTWISE_UNARY_IN_SCALAR(__tg_sqrt,double,2)
__SIMD_ELEMENTWISE_UNARY_IN_SCALAR(__tg_sqrt,double,3)
#endif
#if defined __AVX__
static vector_float8  __SIMD_ATTRIBUTES__ __tg_sqrt(vector_float8  __x) { return _mm256_sqrt_ps(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_sqrt(vector_double4 __x) { return _mm256_sqrt_pd(__x); }
#else
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_sqrt,float);
__SIMD_ELEMENTWISE_UNARY_4_IN_2(__tg_sqrt,double);
#endif
__SIMD_ELEMENTWISE_UNARY_16_IN_8(__tg_sqrt,float);
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_sqrt,double);

#if defined __SSE4_1__
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_ceil, float)
static vector_float4  __SIMD_ATTRIBUTES__ __tg_ceil(vector_float4  __x) { return _mm_ceil_ps(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_ceil(vector_double2 __x) { return _mm_ceil_pd(__x); }
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_floor, float)
static vector_float4  __SIMD_ATTRIBUTES__ __tg_floor(vector_float4  __x) { return _mm_floor_ps(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_floor(vector_double2 __x) { return _mm_floor_pd(__x); }
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_rint, float)
static vector_float4  __SIMD_ATTRIBUTES__ __tg_rint(vector_float4  __x) { return _mm_round_ps(__x,_MM_FROUND_CUR_DIRECTION); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_rint(vector_double2 __x) { return _mm_round_pd(__x,_MM_FROUND_CUR_DIRECTION); }
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_trunc, float)
static vector_float4  __SIMD_ATTRIBUTES__ __tg_trunc(vector_float4  __x) { return _mm_round_ps(__x,_MM_FROUND_TRUNC); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_trunc(vector_double2 __x) { return _mm_round_pd(__x,_MM_FROUND_TRUNC); }
#elif defined __arm64__
static vector_float2  __SIMD_ATTRIBUTES__ __tg_ceil(vector_float2  __x) { return vrndp_f32(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_ceil(vector_float4  __x) { return vrndpq_f32(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_ceil(vector_double2 __x) { return vrndpq_f64(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ __tg_floor(vector_float2  __x) { return vrndm_f32(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_floor(vector_float4  __x) { return vrndmq_f32(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_floor(vector_double2 __x) { return vrndmq_f64(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ __tg_rint(vector_float2  __x) { return vrndx_f32(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_rint(vector_float4  __x) { return vrndxq_f32(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_rint(vector_double2 __x) { return vrndxq_f64(__x); }
static vector_float2  __SIMD_ATTRIBUTES__ __tg_trunc(vector_float2  __x) { return vrnd_f32(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_trunc(vector_float4  __x) { return vrndq_f32(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_trunc(vector_double2 __x) { return vrndq_f64(__x); }
#else
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_ceil, float)
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_floor, float)
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_rint, float)
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_trunc, float)
static vector_float4 __SIMD_ATTRIBUTES__ __truncate_small(vector_float4  __x) { return __builtin_convertvector(__builtin_convertvector(__x, vector_int4),  vector_float4); }
static vector_float4 __SIMD_ATTRIBUTES__ __truncate(vector_float4 __x) { vector_int4 __sp = __tg_fabs(__x) < 0x1.0p23f; vector_float4 __sx = vector_bitselect(0, __x, __sp); return vector_bitselect(__x, __truncate_small(__sx), __sp); }
static vector_float4 __SIMD_ATTRIBUTES__ __tg_ceil(vector_float4 __x)  { vector_float4 __tx = __truncate(__x); vector_float4 __adj = vector_bitselect((vector_float4)0, 1, __tx < __x); return __tg_copysign(__tx + __adj, __x); }
static vector_float4 __SIMD_ATTRIBUTES__ __tg_floor(vector_float4 __x) { vector_float4 __tx = __truncate(__x); vector_float4 __adj = vector_bitselect((vector_float4)0, 1, __tx > __x); return __tg_copysign(__tx - __adj, __x); }
static vector_float4 __SIMD_ATTRIBUTES__ __tg_rint(vector_float4 __x)  { vector_float4 __m = __tg_copysign(0x1.0p23f,__x); vector_int4 __sp = __tg_fabs(__x) < 0x1.0p23f; vector_float4 __sx = vector_bitselect(0, __x, __sp); return vector_bitselect(__x, (__sx + __m) - __m, __sp & 0x7fffffff); }
static vector_float4 __SIMD_ATTRIBUTES__ __tg_trunc(vector_float4 __x) { return __tg_copysign(__truncate(__x), __x); }
static vector_double2 __SIMD_ATTRIBUTES__ __truncate_small(vector_double2 __x) { return __builtin_convertvector(__builtin_convertvector(__x, vector_long2),  vector_double2); }
static vector_double2 __SIMD_ATTRIBUTES__ __truncate(vector_double2 __x) { vector_long2 __sp = __tg_fabs(__x) < 0x1.0p52; vector_double2 __sx = vector_bitselect(0, __x, __sp); return vector_bitselect(__x, __truncate_small(__sx), __sp); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_ceil(vector_double2 __x)  { vector_double2 __tx = __truncate(__x); vector_double2 __adj = vector_bitselect((vector_double2)0, 1, __tx < __x); return __tg_copysign(__tx + __adj, __x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_floor(vector_double2 __x) { vector_double2 __tx = __truncate(__x); vector_double2 __adj = vector_bitselect((vector_double2)0, 1, __tx > __x); return __tg_copysign(__tx - __adj, __x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_rint(vector_double2 __x)  { vector_double2 __m = __tg_copysign(0x1.0p52,__x); vector_long2 __sp = __tg_fabs(__x) < 0x1.0p52; vector_double2 __sx = vector_bitselect(0, __x, __sp); return vector_bitselect(__x, (__sx + __m) - __m, __sp & 0x7fffffffffffffff); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_trunc(vector_double2 __x) { return __tg_copysign(__truncate(__x), __x); }
#endif
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_ceil,  float)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_ceil,  double)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_floor, float)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_floor, double)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_rint,  float)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_rint,  double)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_trunc, float)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_trunc, double)
#if defined __AVX__
static vector_float8  __SIMD_ATTRIBUTES__  __tg_ceil(vector_float8  __x) { return _mm256_ceil_ps(__x); }
static vector_double4 __SIMD_ATTRIBUTES__  __tg_ceil(vector_double4 __x) { return _mm256_ceil_pd(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ __tg_floor(vector_float8  __x) { return _mm256_floor_ps(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_floor(vector_double4 __x) { return _mm256_floor_pd(__x); }
static vector_float8  __SIMD_ATTRIBUTES__  __tg_rint(vector_float8  __x) { return _mm256_round_ps(__x,_MM_FROUND_CUR_DIRECTION); }
static vector_double4 __SIMD_ATTRIBUTES__  __tg_rint(vector_double4 __x) { return _mm256_round_pd(__x,_MM_FROUND_CUR_DIRECTION); }
static vector_float8  __SIMD_ATTRIBUTES__ __tg_trunc(vector_float8  __x) { return _mm256_round_ps(__x,_MM_FROUND_TRUNC); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_trunc(vector_double4 __x) { return _mm256_round_pd(__x,_MM_FROUND_TRUNC); }
#else
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_ceil,  float)
__SIMD_ELEMENTWISE_UNARY_4_IN_2(__tg_ceil,  double)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_floor, float)
__SIMD_ELEMENTWISE_UNARY_4_IN_2(__tg_floor, double)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_rint,  float)
__SIMD_ELEMENTWISE_UNARY_4_IN_2(__tg_rint,  double)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_trunc, float)
__SIMD_ELEMENTWISE_UNARY_4_IN_2(__tg_trunc, double)
#endif
__SIMD_ELEMENTWISE_UNARY_16_IN_8(__tg_ceil,  float)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_ceil,  double)
__SIMD_ELEMENTWISE_UNARY_16_IN_8(__tg_floor, float)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_floor, double)
__SIMD_ELEMENTWISE_UNARY_16_IN_8(__tg_rint,  float)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_rint,  double)
__SIMD_ELEMENTWISE_UNARY_16_IN_8(__tg_trunc, float)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_trunc, double)

__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_cos, float)
__SIMD_ELEMENTWISE_UNARY_2_IN_4(__tg_sin, float)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_cos, float)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_sin, float)
static vector_float4  __SIMD_ATTRIBUTES__ __tg_cos(vector_float4  __x) { return __cos_f4(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ __tg_sin(vector_float4  __x) { return __sin_f4(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_cos(vector_double2 __x) { return __cos_d2(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ __tg_sin(vector_double2 __x) { return __sin_d2(__x); }
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_cos, double)
__SIMD_ELEMENTWISE_UNARY_3_IN_4(__tg_sin, double)
#if defined __AVX__
static vector_float8  __SIMD_ATTRIBUTES__ __tg_cos(vector_float8  __x) { return __cos_f8(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ __tg_sin(vector_float8  __x) { return __sin_f8(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_cos(vector_double4 __x) { return __cos_d4(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ __tg_sin(vector_double4 __x) { return __sin_d4(__x); }
#else
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_cos, float)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_sin, float)
__SIMD_ELEMENTWISE_UNARY_4_IN_2(__tg_cos, double)
__SIMD_ELEMENTWISE_UNARY_4_IN_2(__tg_sin, double)
#endif
__SIMD_ELEMENTWISE_UNARY_16_IN_8(__tg_cos, float)
__SIMD_ELEMENTWISE_UNARY_16_IN_8(__tg_sin, float)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_cos, double)
__SIMD_ELEMENTWISE_UNARY_8_IN_4(__tg_sin, double)

#ifdef __cplusplus
}
#endif
#endif /* __SIMD_REQUIRED_COMPILER_FEATURES__ */
#endif /* __SIMD_MATH_HEADER__ */
