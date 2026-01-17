/*  Copyright (c) 2014 Apple, Inc. All rights reserved.
 *
 *  The interfaces declared in this header provide operations for mathematical
 *  vectors; these functions and macros operate on vectors of floating-point
 *  data only.
 *
 *      Function                    Result
 *      ------------------------------------------------------------------
 *      vector_dot(x,y)             The dot product of x and y.
 *
 *      vector_project(x,y)         x projected onto y.  There are two variants
 *                                  of this function, vector_precise_project
 *                                  and vector_fast_project.  vector_project
 *                                  is equivalent to vector_precise_project
 *                                  unless you are compiling with -ffast-math
 *                                  specified, in which case it is equivalent
 *                                  to vector_fast_project.
 *
 *      vector_length(x)            The length (l2 norm) of x.  Undefined if
 *                                  x is poorly scaled such that an
 *                                  intermediate computation overflows or
 *                                  underflows.  There are two variants
 *                                  of this function, vector_precise_length
 *                                  and vector_fast_length.  vector_length
 *                                  is equivalent to vector_precise_length
 *                                  unless you are compiling with -ffast-math
 *                                  specified, in which case it is equivalent
 *                                  to vector_fast_length.
 *
 *      vector_length_squared(x)    The square of the length of x.  If you
 *                                  simply need to compare relative magnitudes,
 *                                  use this instead of vector_length; it is
 *                                  faster than vector_fast_length and as
 *                                  accurate as vector_precise_length.
 *
 *      vector_distance(x,y)        The distance between x and y. Undefined if
 *                                  x and y are poorly scaled such that an
 *                                  intermediate computation overflows
 *                                  or underflows.  There are two variants
 *                                  of this function, vector_precise_distance
 *                                  and vector_fast_distance.  vector_distance
 *                                  is equivalent to vector_precise_distance
 *                                  unless you are compiling with -ffast-math
 *                                  specified, in which case it is equivalent
 *                                  to vector_fast_distance.
 *
 *      vector_distance_squared(x,y) The square of the distance between x and y.
 *
 *      vector_normalize(x)         A vector pointing in the direction of x
 *                                  with length 1.0.  Undefined if x is
 *                                  the zero vector, or if x is poorly scaled
 *                                  such that an intermediate computation
 *                                  overflows or underflows.  There are two
 *                                  variants of this function,
 *                                  vector_precise_normalize and
 *                                  vector_fast_normalize.  vector_normalize
 *                                  is equivalent to vector_precise_normalize
 *                                  unless you are compiling with -ffast-math
 *                                  specified, in which case it is equivalent
 *                                  to vector_fast_normalize.
 *
 *      vector_cross(x,y)           If x and y are vectors of dimension 3,
 *                                  the cross-product of x and y.
 *
 *                                  If x and y are vectors of dimension 2,
 *                                  the cross-product of x and y interpreted as
 *                                  vectors in the z == 0 plane of a three-
 *                                  dimensional space.
 *
 *                                  If x and y are vectors with a length that
 *                                  is neither 2 nor 3, this operation is not
 *                                  available.
 *
 *      vector_reflect(x,n)         Reflects x through the plane perpendicular
 *                                  to the normal vector n.  Only available
 *                                  for vectors of length 2, 3, or 4.
 *
 *  In C++ the following geometric functions are available in the simd::
 *  namespace:
 *
 *      C++ Function                    Equivalent C Function
 *      --------------------------------------------------------------------
 *      simd::dot(x,y)                  vector_dot(x,y)
 *      simd::project(x,y)              vector_project(x,y)
 *      simd::length_squared(x)         vector_length_squared(x)
 *      simd::length(x)                 vector_length(x,y)
 *      simd::distance_squared(x,y)     vector_distance_squared(x,y)
 *      simd::distance(x,y)             vector_distance(x,y)
 *      simd::normalize(x)              vector_normalize(x)
 *      simd::cross(x,y)                vector_cross(x,y)
 *      simd::reflect(x,n)              vector_reflect(x,n)
 *
 *      simd::precise::project(x,y)     vector_precise_project(x,y)
 *      simd::precise::length(x)        vector_precise_length(x)
 *      simd::precise::distance(x,y)    vector_precise_distance(x,y)
 *      simd::precise::normalize(x)     vector_precise_normalize(x)
 *
 *      simd::fast::project(x,y)        vector_fast_project(x,y)
 *      simd::fast::length(x)           vector_fast_length(x)
 *      simd::fast::distance(x,y)       vector_fast_distance(x,y)
 *      simd::fast::normalize(x)        vector_fast_normalize(x)
 */

#ifndef __SIMD_GEOMETRY_HEADER__
#define __SIMD_GEOMETRY_HEADER__

#include <simd/internal.h>
#if __SIMD_REQUIRED_COMPILER_FEATURES__
#include <simd/vector_types.h>
#include <simd/common.h>

#ifdef __cplusplus
extern "C" {
#endif

static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float2  __x, vector_float2  __y);
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float3  __x, vector_float3  __y);
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float4  __x, vector_float4  __y);
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float8  __x, vector_float8  __y);
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float16 __x, vector_float16 __y);
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double2 __x, vector_double2 __y);
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double3 __x, vector_double3 __y);
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double4 __x, vector_double4 __y);
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double8 __x, vector_double8 __y);

static vector_float2  __SIMD_ATTRIBUTES__ vector_precise_project(vector_float2  __x, vector_float2  __y);
static vector_float3  __SIMD_ATTRIBUTES__ vector_precise_project(vector_float3  __x, vector_float3  __y);
static vector_float4  __SIMD_ATTRIBUTES__ vector_precise_project(vector_float4  __x, vector_float4  __y);
static vector_float8  __SIMD_ATTRIBUTES__ vector_precise_project(vector_float8  __x, vector_float8  __y);
static vector_float16 __SIMD_ATTRIBUTES__ vector_precise_project(vector_float16 __x, vector_float16 __y);
static vector_double2 __SIMD_ATTRIBUTES__ vector_precise_project(vector_double2 __x, vector_double2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ vector_precise_project(vector_double3 __x, vector_double3 __y);
static vector_double4 __SIMD_ATTRIBUTES__ vector_precise_project(vector_double4 __x, vector_double4 __y);
static vector_double8 __SIMD_ATTRIBUTES__ vector_precise_project(vector_double8 __x, vector_double8 __y);

static vector_float2  __SIMD_ATTRIBUTES__ vector_fast_project(vector_float2  __x, vector_float2  __y);
static vector_float3  __SIMD_ATTRIBUTES__ vector_fast_project(vector_float3  __x, vector_float3  __y);
static vector_float4  __SIMD_ATTRIBUTES__ vector_fast_project(vector_float4  __x, vector_float4  __y);
static vector_float8  __SIMD_ATTRIBUTES__ vector_fast_project(vector_float8  __x, vector_float8  __y);
static vector_float16 __SIMD_ATTRIBUTES__ vector_fast_project(vector_float16 __x, vector_float16 __y);
static vector_double2 __SIMD_ATTRIBUTES__ vector_fast_project(vector_double2 __x, vector_double2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ vector_fast_project(vector_double3 __x, vector_double3 __y);
static vector_double4 __SIMD_ATTRIBUTES__ vector_fast_project(vector_double4 __x, vector_double4 __y);
static vector_double8 __SIMD_ATTRIBUTES__ vector_fast_project(vector_double8 __x, vector_double8 __y);

static vector_float2  __SIMD_ATTRIBUTES__ vector_project(vector_float2  __x, vector_float2  __y);
static vector_float3  __SIMD_ATTRIBUTES__ vector_project(vector_float3  __x, vector_float3  __y);
static vector_float4  __SIMD_ATTRIBUTES__ vector_project(vector_float4  __x, vector_float4  __y);
static vector_float8  __SIMD_ATTRIBUTES__ vector_project(vector_float8  __x, vector_float8  __y);
static vector_float16 __SIMD_ATTRIBUTES__ vector_project(vector_float16 __x, vector_float16 __y);
static vector_double2 __SIMD_ATTRIBUTES__ vector_project(vector_double2 __x, vector_double2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ vector_project(vector_double3 __x, vector_double3 __y);
static vector_double4 __SIMD_ATTRIBUTES__ vector_project(vector_double4 __x, vector_double4 __y);
static vector_double8 __SIMD_ATTRIBUTES__ vector_project(vector_double8 __x, vector_double8 __y);

static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float2  __x);
static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float3  __x);
static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float4  __x);
static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float8  __x);
static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float16 __x);
static double __SIMD_ATTRIBUTES__ vector_precise_length(vector_double2 __x);
static double __SIMD_ATTRIBUTES__ vector_precise_length(vector_double3 __x);
static double __SIMD_ATTRIBUTES__ vector_precise_length(vector_double4 __x);
static double __SIMD_ATTRIBUTES__ vector_precise_length(vector_double8 __x);

static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float2  __x);
static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float3  __x);
static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float4  __x);
static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float8  __x);
static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float16 __x);
static double __SIMD_ATTRIBUTES__ vector_fast_length(vector_double2 __x);
static double __SIMD_ATTRIBUTES__ vector_fast_length(vector_double3 __x);
static double __SIMD_ATTRIBUTES__ vector_fast_length(vector_double4 __x);
static double __SIMD_ATTRIBUTES__ vector_fast_length(vector_double8 __x);

static float  __SIMD_ATTRIBUTES__ vector_length(vector_float2  __x);
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float3  __x);
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float4  __x);
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float8  __x);
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float16 __x);
static double __SIMD_ATTRIBUTES__ vector_length(vector_double2 __x);
static double __SIMD_ATTRIBUTES__ vector_length(vector_double3 __x);
static double __SIMD_ATTRIBUTES__ vector_length(vector_double4 __x);
static double __SIMD_ATTRIBUTES__ vector_length(vector_double8 __x);

static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float2  __x);
static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float3  __x);
static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float4  __x);
static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float8  __x);
static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float16 __x);
static double __SIMD_ATTRIBUTES__ vector_length_squared(vector_double2 __x);
static double __SIMD_ATTRIBUTES__ vector_length_squared(vector_double3 __x);
static double __SIMD_ATTRIBUTES__ vector_length_squared(vector_double4 __x);
static double __SIMD_ATTRIBUTES__ vector_length_squared(vector_double8 __x);

static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float2  __x, vector_float2  __y);
static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float3  __x, vector_float3  __y);
static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float4  __x, vector_float4  __y);
static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float8  __x, vector_float8  __y);
static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float16 __x, vector_float16 __y);
static double __SIMD_ATTRIBUTES__ vector_precise_distance(vector_double2 __x, vector_double2 __y);
static double __SIMD_ATTRIBUTES__ vector_precise_distance(vector_double3 __x, vector_double3 __y);
static double __SIMD_ATTRIBUTES__ vector_precise_distance(vector_double4 __x, vector_double4 __y);
static double __SIMD_ATTRIBUTES__ vector_precise_distance(vector_double8 __x, vector_double8 __y);

static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float2  __x, vector_float2  __y);
static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float3  __x, vector_float3  __y);
static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float4  __x, vector_float4  __y);
static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float8  __x, vector_float8  __y);
static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float16 __x, vector_float16 __y);
static double __SIMD_ATTRIBUTES__ vector_fast_distance(vector_double2 __x, vector_double2 __y);
static double __SIMD_ATTRIBUTES__ vector_fast_distance(vector_double3 __x, vector_double3 __y);
static double __SIMD_ATTRIBUTES__ vector_fast_distance(vector_double4 __x, vector_double4 __y);
static double __SIMD_ATTRIBUTES__ vector_fast_distance(vector_double8 __x, vector_double8 __y);

static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float2  __x, vector_float2  __y);
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float3  __x, vector_float3  __y);
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float4  __x, vector_float4  __y);
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float8  __x, vector_float8  __y);
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float16 __x, vector_float16 __y);
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double2 __x, vector_double2 __y);
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double3 __x, vector_double3 __y);
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double4 __x, vector_double4 __y);
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double8 __x, vector_double8 __y);

static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float2  __x, vector_float2  __y);
static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float3  __x, vector_float3  __y);
static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float4  __x, vector_float4  __y);
static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float8  __x, vector_float8  __y);
static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float16 __x, vector_float16 __y);
static double __SIMD_ATTRIBUTES__ vector_distance_squared(vector_double2 __x, vector_double2 __y);
static double __SIMD_ATTRIBUTES__ vector_distance_squared(vector_double3 __x, vector_double3 __y);
static double __SIMD_ATTRIBUTES__ vector_distance_squared(vector_double4 __x, vector_double4 __y);
static double __SIMD_ATTRIBUTES__ vector_distance_squared(vector_double8 __x, vector_double8 __y);

static vector_float2  __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_double8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_double8 __x);

static vector_float2  __SIMD_ATTRIBUTES__ vector_normalize(vector_float2  __x);
static vector_float3  __SIMD_ATTRIBUTES__ vector_normalize(vector_float3  __x);
static vector_float4  __SIMD_ATTRIBUTES__ vector_normalize(vector_float4  __x);
static vector_float8  __SIMD_ATTRIBUTES__ vector_normalize(vector_float8  __x);
static vector_float16 __SIMD_ATTRIBUTES__ vector_normalize(vector_float16 __x);
static vector_double2 __SIMD_ATTRIBUTES__ vector_normalize(vector_double2 __x);
static vector_double3 __SIMD_ATTRIBUTES__ vector_normalize(vector_double3 __x);
static vector_double4 __SIMD_ATTRIBUTES__ vector_normalize(vector_double4 __x);
static vector_double8 __SIMD_ATTRIBUTES__ vector_normalize(vector_double8 __x);

static vector_float3  __SIMD_ATTRIBUTES__ vector_cross(vector_float2  __x, vector_float2  __y);
static vector_float3  __SIMD_ATTRIBUTES__ vector_cross(vector_float3  __x, vector_float3  __y);
static vector_double3 __SIMD_ATTRIBUTES__ vector_cross(vector_double2 __x, vector_double2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ vector_cross(vector_double3 __x, vector_double3 __y);

static vector_float2  __SIMD_ATTRIBUTES__ vector_reflect(vector_float2  __x, vector_float2  __n);
static vector_float3  __SIMD_ATTRIBUTES__ vector_reflect(vector_float3  __x, vector_float3  __n);
static vector_float4  __SIMD_ATTRIBUTES__ vector_reflect(vector_float4  __x, vector_float4  __n);
static vector_double2 __SIMD_ATTRIBUTES__ vector_reflect(vector_double2 __x, vector_double2 __n);
static vector_double3 __SIMD_ATTRIBUTES__ vector_reflect(vector_double3 __x, vector_double3 __n);
static vector_double4 __SIMD_ATTRIBUTES__ vector_reflect(vector_double4 __x, vector_double4 __n);

#ifdef __cplusplus
} /* extern "C" */

namespace simd {
    static __SIMD_INLINE__ float  dot(const float2  x, const float2  y) { return ::vector_dot(x, y); }
    static __SIMD_INLINE__ float  dot(const float3  x, const float3  y) { return ::vector_dot(x, y); }
    static __SIMD_INLINE__ float  dot(const float4  x, const float4  y) { return ::vector_dot(x, y); }
    static __SIMD_INLINE__ float  dot(const float8  x, const float8  y) { return ::vector_dot(x, y); }
    static __SIMD_INLINE__ float  dot(const float16 x, const float16 y) { return ::vector_dot(x, y); }
    static __SIMD_INLINE__ double dot(const double2 x, const double2 y) { return ::vector_dot(x, y); }
    static __SIMD_INLINE__ double dot(const double3 x, const double3 y) { return ::vector_dot(x, y); }
    static __SIMD_INLINE__ double dot(const double4 x, const double4 y) { return ::vector_dot(x, y); }
    static __SIMD_INLINE__ double dot(const double8 x, const double8 y) { return ::vector_dot(x, y); }

    static __SIMD_INLINE__ float2  project(const float2  x, const float2  y) { return vector_project(x, y); }
    static __SIMD_INLINE__ float3  project(const float3  x, const float3  y) { return vector_project(x, y); }
    static __SIMD_INLINE__ float4  project(const float4  x, const float4  y) { return vector_project(x, y); }
    static __SIMD_INLINE__ float8  project(const float8  x, const float8  y) { return vector_project(x, y); }
    static __SIMD_INLINE__ float16 project(const float16 x, const float16 y) { return vector_project(x, y); }
    static __SIMD_INLINE__ double2 project(const double2 x, const double2 y) { return vector_project(x, y); }
    static __SIMD_INLINE__ double3 project(const double3 x, const double3 y) { return vector_project(x, y); }
    static __SIMD_INLINE__ double4 project(const double4 x, const double4 y) { return vector_project(x, y); }
    static __SIMD_INLINE__ double8 project(const double8 x, const double8 y) { return vector_project(x, y); }

    static __SIMD_INLINE__ float  length_squared(const float2  x) { return ::vector_length_squared(x); }
    static __SIMD_INLINE__ float  length_squared(const float3  x) { return ::vector_length_squared(x); }
    static __SIMD_INLINE__ float  length_squared(const float4  x) { return ::vector_length_squared(x); }
    static __SIMD_INLINE__ float  length_squared(const float8  x) { return ::vector_length_squared(x); }
    static __SIMD_INLINE__ float  length_squared(const float16 x) { return ::vector_length_squared(x); }
    static __SIMD_INLINE__ double length_squared(const double2 x) { return ::vector_length_squared(x); }
    static __SIMD_INLINE__ double length_squared(const double3 x) { return ::vector_length_squared(x); }
    static __SIMD_INLINE__ double length_squared(const double4 x) { return ::vector_length_squared(x); }
    static __SIMD_INLINE__ double length_squared(const double8 x) { return ::vector_length_squared(x); }

    static __SIMD_INLINE__ float  length(const float2  x) { return vector_length(x); }
    static __SIMD_INLINE__ float  length(const float3  x) { return vector_length(x); }
    static __SIMD_INLINE__ float  length(const float4  x) { return vector_length(x); }
    static __SIMD_INLINE__ float  length(const float8  x) { return vector_length(x); }
    static __SIMD_INLINE__ float  length(const float16 x) { return vector_length(x); }
    static __SIMD_INLINE__ double length(const double2 x) { return vector_length(x); }
    static __SIMD_INLINE__ double length(const double3 x) { return vector_length(x); }
    static __SIMD_INLINE__ double length(const double4 x) { return vector_length(x); }
    static __SIMD_INLINE__ double length(const double8 x) { return vector_length(x); }

    static __SIMD_INLINE__ float  distance_squared(const float2  x, const float2  y) { return ::vector_distance_squared(x, y); }
    static __SIMD_INLINE__ float  distance_squared(const float3  x, const float3  y) { return ::vector_distance_squared(x, y); }
    static __SIMD_INLINE__ float  distance_squared(const float4  x, const float4  y) { return ::vector_distance_squared(x, y); }
    static __SIMD_INLINE__ float  distance_squared(const float8  x, const float8  y) { return ::vector_distance_squared(x, y); }
    static __SIMD_INLINE__ float  distance_squared(const float16 x, const float16 y) { return ::vector_distance_squared(x, y); }
    static __SIMD_INLINE__ double distance_squared(const double2 x, const double2 y) { return ::vector_distance_squared(x, y); }
    static __SIMD_INLINE__ double distance_squared(const double3 x, const double3 y) { return ::vector_distance_squared(x, y); }
    static __SIMD_INLINE__ double distance_squared(const double4 x, const double4 y) { return ::vector_distance_squared(x, y); }
    static __SIMD_INLINE__ double distance_squared(const double8 x, const double8 y) { return ::vector_distance_squared(x, y); }

    static __SIMD_INLINE__ float  distance(const float2  x, const float2  y) { return vector_distance(x, y); }
    static __SIMD_INLINE__ float  distance(const float3  x, const float3  y) { return vector_distance(x, y); }
    static __SIMD_INLINE__ float  distance(const float4  x, const float4  y) { return vector_distance(x, y); }
    static __SIMD_INLINE__ float  distance(const float8  x, const float8  y) { return vector_distance(x, y); }
    static __SIMD_INLINE__ float  distance(const float16 x, const float16 y) { return vector_distance(x, y); }
    static __SIMD_INLINE__ double distance(const double2 x, const double2 y) { return vector_distance(x, y); }
    static __SIMD_INLINE__ double distance(const double3 x, const double3 y) { return vector_distance(x, y); }
    static __SIMD_INLINE__ double distance(const double4 x, const double4 y) { return vector_distance(x, y); }
    static __SIMD_INLINE__ double distance(const double8 x, const double8 y) { return vector_distance(x, y); }

    static __SIMD_INLINE__ float2  normalize(const float2  x) { return vector_normalize(x); }
    static __SIMD_INLINE__ float3  normalize(const float3  x) { return vector_normalize(x); }
    static __SIMD_INLINE__ float4  normalize(const float4  x) { return vector_normalize(x); }
    static __SIMD_INLINE__ float8  normalize(const float8  x) { return vector_normalize(x); }
    static __SIMD_INLINE__ float16 normalize(const float16 x) { return vector_normalize(x); }
    static __SIMD_INLINE__ double2 normalize(const double2 x) { return vector_normalize(x); }
    static __SIMD_INLINE__ double3 normalize(const double3 x) { return vector_normalize(x); }
    static __SIMD_INLINE__ double4 normalize(const double4 x) { return vector_normalize(x); }
    static __SIMD_INLINE__ double8 normalize(const double8 x) { return vector_normalize(x); }

    static __SIMD_INLINE__ float3  cross(const float2  x, const float2  y) { return ::vector_cross(x,y); }
    static __SIMD_INLINE__ float3  cross(const float3  x, const float3  y) { return ::vector_cross(x,y); }
    static __SIMD_INLINE__ double3 cross(const double2 x, const double2 y) { return ::vector_cross(x,y); }
    static __SIMD_INLINE__ double3 cross(const double3 x, const double3 y) { return ::vector_cross(x,y); }

    static __SIMD_INLINE__ float2  reflect(const float2  x, const float2  n) { return ::vector_reflect(x,n); }
    static __SIMD_INLINE__ float3  reflect(const float3  x, const float3  n) { return ::vector_reflect(x,n); }
    static __SIMD_INLINE__ float4  reflect(const float4  x, const float4  n) { return ::vector_reflect(x,n); }
    static __SIMD_INLINE__ double2 reflect(const double2 x, const double2 n) { return ::vector_reflect(x,n); }
    static __SIMD_INLINE__ double3 reflect(const double3 x, const double3 n) { return ::vector_reflect(x,n); }
    static __SIMD_INLINE__ double4 reflect(const double4 x, const double4 n) { return ::vector_reflect(x,n); }

    /* precise and fast sub-namespaces                                        */
    namespace precise {
        static __SIMD_INLINE__ float2  project(const float2  x, const float2  y) { return ::vector_precise_project(x, y); }
        static __SIMD_INLINE__ float3  project(const float3  x, const float3  y) { return ::vector_precise_project(x, y); }
        static __SIMD_INLINE__ float4  project(const float4  x, const float4  y) { return ::vector_precise_project(x, y); }
        static __SIMD_INLINE__ float8  project(const float8  x, const float8  y) { return ::vector_precise_project(x, y); }
        static __SIMD_INLINE__ float16 project(const float16 x, const float16 y) { return ::vector_precise_project(x, y); }
        static __SIMD_INLINE__ double2 project(const double2 x, const double2 y) { return ::vector_precise_project(x, y); }
        static __SIMD_INLINE__ double3 project(const double3 x, const double3 y) { return ::vector_precise_project(x, y); }
        static __SIMD_INLINE__ double4 project(const double4 x, const double4 y) { return ::vector_precise_project(x, y); }
        static __SIMD_INLINE__ double8 project(const double8 x, const double8 y) { return ::vector_precise_project(x, y); }

        static __SIMD_INLINE__ float  length(const float2  x) { return ::vector_precise_length(x); }
        static __SIMD_INLINE__ float  length(const float3  x) { return ::vector_precise_length(x); }
        static __SIMD_INLINE__ float  length(const float4  x) { return ::vector_precise_length(x); }
        static __SIMD_INLINE__ float  length(const float8  x) { return ::vector_precise_length(x); }
        static __SIMD_INLINE__ float  length(const float16 x) { return ::vector_precise_length(x); }
        static __SIMD_INLINE__ double length(const double2 x) { return ::vector_precise_length(x); }
        static __SIMD_INLINE__ double length(const double3 x) { return ::vector_precise_length(x); }
        static __SIMD_INLINE__ double length(const double4 x) { return ::vector_precise_length(x); }
        static __SIMD_INLINE__ double length(const double8 x) { return ::vector_precise_length(x); }

        static __SIMD_INLINE__ float  distance(const float2  x, const float2  y) { return ::vector_precise_distance(x, y); }
        static __SIMD_INLINE__ float  distance(const float3  x, const float3  y) { return ::vector_precise_distance(x, y); }
        static __SIMD_INLINE__ float  distance(const float4  x, const float4  y) { return ::vector_precise_distance(x, y); }
        static __SIMD_INLINE__ float  distance(const float8  x, const float8  y) { return ::vector_precise_distance(x, y); }
        static __SIMD_INLINE__ float  distance(const float16 x, const float16 y) { return ::vector_precise_distance(x, y); }
        static __SIMD_INLINE__ double distance(const double2 x, const double2 y) { return ::vector_precise_distance(x, y); }
        static __SIMD_INLINE__ double distance(const double3 x, const double3 y) { return ::vector_precise_distance(x, y); }
        static __SIMD_INLINE__ double distance(const double4 x, const double4 y) { return ::vector_precise_distance(x, y); }
        static __SIMD_INLINE__ double distance(const double8 x, const double8 y) { return ::vector_precise_distance(x, y); }

        static __SIMD_INLINE__ float2  normalize(const float2  x) { return ::vector_precise_normalize(x); }
        static __SIMD_INLINE__ float3  normalize(const float3  x) { return ::vector_precise_normalize(x); }
        static __SIMD_INLINE__ float4  normalize(const float4  x) { return ::vector_precise_normalize(x); }
        static __SIMD_INLINE__ float8  normalize(const float8  x) { return ::vector_precise_normalize(x); }
        static __SIMD_INLINE__ float16 normalize(const float16 x) { return ::vector_precise_normalize(x); }
        static __SIMD_INLINE__ double2 normalize(const double2 x) { return ::vector_precise_normalize(x); }
        static __SIMD_INLINE__ double3 normalize(const double3 x) { return ::vector_precise_normalize(x); }
        static __SIMD_INLINE__ double4 normalize(const double4 x) { return ::vector_precise_normalize(x); }
        static __SIMD_INLINE__ double8 normalize(const double8 x) { return ::vector_precise_normalize(x); }
    }

    namespace fast {
        static __SIMD_INLINE__ float2  project(const float2  x, const float2  y) { return ::vector_fast_project(x, y); }
        static __SIMD_INLINE__ float3  project(const float3  x, const float3  y) { return ::vector_fast_project(x, y); }
        static __SIMD_INLINE__ float4  project(const float4  x, const float4  y) { return ::vector_fast_project(x, y); }
        static __SIMD_INLINE__ float8  project(const float8  x, const float8  y) { return ::vector_fast_project(x, y); }
        static __SIMD_INLINE__ float16 project(const float16 x, const float16 y) { return ::vector_fast_project(x, y); }
        static __SIMD_INLINE__ double2 project(const double2 x, const double2 y) { return ::vector_fast_project(x, y); }
        static __SIMD_INLINE__ double3 project(const double3 x, const double3 y) { return ::vector_fast_project(x, y); }
        static __SIMD_INLINE__ double4 project(const double4 x, const double4 y) { return ::vector_fast_project(x, y); }
        static __SIMD_INLINE__ double8 project(const double8 x, const double8 y) { return ::vector_fast_project(x, y); }

        static __SIMD_INLINE__ float  length(const float2  x) { return ::vector_fast_length(x); }
        static __SIMD_INLINE__ float  length(const float3  x) { return ::vector_fast_length(x); }
        static __SIMD_INLINE__ float  length(const float4  x) { return ::vector_fast_length(x); }
        static __SIMD_INLINE__ float  length(const float8  x) { return ::vector_fast_length(x); }
        static __SIMD_INLINE__ float  length(const float16 x) { return ::vector_fast_length(x); }
        static __SIMD_INLINE__ double length(const double2 x) { return ::vector_fast_length(x); }
        static __SIMD_INLINE__ double length(const double3 x) { return ::vector_fast_length(x); }
        static __SIMD_INLINE__ double length(const double4 x) { return ::vector_fast_length(x); }
        static __SIMD_INLINE__ double length(const double8 x) { return ::vector_fast_length(x); }

        static __SIMD_INLINE__ float  distance(const float2  x, const float2  y) { return ::vector_fast_distance(x, y); }
        static __SIMD_INLINE__ float  distance(const float3  x, const float3  y) { return ::vector_fast_distance(x, y); }
        static __SIMD_INLINE__ float  distance(const float4  x, const float4  y) { return ::vector_fast_distance(x, y); }
        static __SIMD_INLINE__ float  distance(const float8  x, const float8  y) { return ::vector_fast_distance(x, y); }
        static __SIMD_INLINE__ float  distance(const float16 x, const float16 y) { return ::vector_fast_distance(x, y); }
        static __SIMD_INLINE__ double distance(const double2 x, const double2 y) { return ::vector_fast_distance(x, y); }
        static __SIMD_INLINE__ double distance(const double3 x, const double3 y) { return ::vector_fast_distance(x, y); }
        static __SIMD_INLINE__ double distance(const double4 x, const double4 y) { return ::vector_fast_distance(x, y); }
        static __SIMD_INLINE__ double distance(const double8 x, const double8 y) { return ::vector_fast_distance(x, y); }

        static __SIMD_INLINE__ float2  normalize(const float2  x) { return ::vector_fast_normalize(x); }
        static __SIMD_INLINE__ float3  normalize(const float3  x) { return ::vector_fast_normalize(x); }
        static __SIMD_INLINE__ float4  normalize(const float4  x) { return ::vector_fast_normalize(x); }
        static __SIMD_INLINE__ float8  normalize(const float8  x) { return ::vector_fast_normalize(x); }
        static __SIMD_INLINE__ float16 normalize(const float16 x) { return ::vector_fast_normalize(x); }
        static __SIMD_INLINE__ double2 normalize(const double2 x) { return ::vector_fast_normalize(x); }
        static __SIMD_INLINE__ double3 normalize(const double3 x) { return ::vector_fast_normalize(x); }
        static __SIMD_INLINE__ double4 normalize(const double4 x) { return ::vector_fast_normalize(x); }
        static __SIMD_INLINE__ double8 normalize(const double8 x) { return ::vector_fast_normalize(x); }
    }
}

extern "C" {
#endif /* __cplusplus */

#pragma mark - Implementation

static float  __SIMD_ATTRIBUTES__ __horizontal_sum(vector_float2  __x) { return __x.x + __x.y; }
static float  __SIMD_ATTRIBUTES__ __horizontal_sum(vector_float3  __x) { return __x.x + __x.z + __x.y; }
static float  __SIMD_ATTRIBUTES__ __horizontal_sum(vector_float4  __x) { return __horizontal_sum(__x.lo + __x.hi); }
static float  __SIMD_ATTRIBUTES__ __horizontal_sum(vector_float8  __x) { return __horizontal_sum(__x.lo + __x.hi); }
static float  __SIMD_ATTRIBUTES__ __horizontal_sum(vector_float16 __x) { return __horizontal_sum(__x.lo + __x.hi); }
static double __SIMD_ATTRIBUTES__ __horizontal_sum(vector_double2 __x) { return __x.x + __x.y; }
static double __SIMD_ATTRIBUTES__ __horizontal_sum(vector_double3 __x) { return __x.x + __x.z + __x.y; }
static double __SIMD_ATTRIBUTES__ __horizontal_sum(vector_double4 __x) { return __horizontal_sum(__x.lo + __x.hi); }
static double __SIMD_ATTRIBUTES__ __horizontal_sum(vector_double8 __x) { return __horizontal_sum(__x.lo + __x.hi); }

static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float2  __x, vector_float2  __y) { return __horizontal_sum(__x*__y); }
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float3  __x, vector_float3  __y) { return __horizontal_sum(__x*__y); }
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float4  __x, vector_float4  __y) { return __horizontal_sum(__x*__y); }
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float8  __x, vector_float8  __y) { return __horizontal_sum(__x*__y); }
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float16 __x, vector_float16 __y) { return __horizontal_sum(__x*__y); }
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double2 __x, vector_double2 __y) { return __horizontal_sum(__x*__y); }
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double3 __x, vector_double3 __y) { return __horizontal_sum(__x*__y); }
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double4 __x, vector_double4 __y) { return __horizontal_sum(__x*__y); }
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double8 __x, vector_double8 __y) { return __horizontal_sum(__x*__y); }

static vector_float2  __SIMD_ATTRIBUTES__ vector_precise_project(vector_float2  __x, vector_float2  __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }
static vector_float3  __SIMD_ATTRIBUTES__ vector_precise_project(vector_float3  __x, vector_float3  __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }
static vector_float4  __SIMD_ATTRIBUTES__ vector_precise_project(vector_float4  __x, vector_float4  __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }
static vector_float8  __SIMD_ATTRIBUTES__ vector_precise_project(vector_float8  __x, vector_float8  __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }
static vector_float16 __SIMD_ATTRIBUTES__ vector_precise_project(vector_float16 __x, vector_float16 __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }
static vector_double2 __SIMD_ATTRIBUTES__ vector_precise_project(vector_double2 __x, vector_double2 __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }
static vector_double3 __SIMD_ATTRIBUTES__ vector_precise_project(vector_double3 __x, vector_double3 __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }
static vector_double4 __SIMD_ATTRIBUTES__ vector_precise_project(vector_double4 __x, vector_double4 __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }
static vector_double8 __SIMD_ATTRIBUTES__ vector_precise_project(vector_double8 __x, vector_double8 __y) { return vector_dot(__x,__y)/vector_dot(__y,__y)*__y; }

static vector_float2  __SIMD_ATTRIBUTES__ vector_fast_project(vector_float2  __x, vector_float2  __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_fast_project(vector_float3  __x, vector_float3  __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_fast_project(vector_float4  __x, vector_float4  __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_fast_project(vector_float8  __x, vector_float8  __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_fast_project(vector_float16 __x, vector_float16 __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_fast_project(vector_double2 __x, vector_double2 __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_fast_project(vector_double3 __x, vector_double3 __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_fast_project(vector_double4 __x, vector_double4 __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_fast_project(vector_double8 __x, vector_double8 __y) { return __y*vector_dot(__x,__y)*vector_fast_recip(vector_dot(__y,__y)); }

#if defined __FAST_MATH__
static vector_float2  __SIMD_ATTRIBUTES__ vector_project(vector_float2  __x, vector_float2  __y) { return vector_fast_project(__x,__y); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_project(vector_float3  __x, vector_float3  __y) { return vector_fast_project(__x,__y); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_project(vector_float4  __x, vector_float4  __y) { return vector_fast_project(__x,__y); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_project(vector_float8  __x, vector_float8  __y) { return vector_fast_project(__x,__y); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_project(vector_float16 __x, vector_float16 __y) { return vector_fast_project(__x,__y); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_project(vector_double2 __x, vector_double2 __y) { return vector_fast_project(__x,__y); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_project(vector_double3 __x, vector_double3 __y) { return vector_fast_project(__x,__y); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_project(vector_double4 __x, vector_double4 __y) { return vector_fast_project(__x,__y); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_project(vector_double8 __x, vector_double8 __y) { return vector_fast_project(__x,__y); }
#else
static vector_float2  __SIMD_ATTRIBUTES__ vector_project(vector_float2  __x, vector_float2  __y) { return vector_precise_project(__x,__y); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_project(vector_float3  __x, vector_float3  __y) { return vector_precise_project(__x,__y); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_project(vector_float4  __x, vector_float4  __y) { return vector_precise_project(__x,__y); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_project(vector_float8  __x, vector_float8  __y) { return vector_precise_project(__x,__y); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_project(vector_float16 __x, vector_float16 __y) { return vector_precise_project(__x,__y); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_project(vector_double2 __x, vector_double2 __y) { return vector_precise_project(__x,__y); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_project(vector_double3 __x, vector_double3 __y) { return vector_precise_project(__x,__y); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_project(vector_double4 __x, vector_double4 __y) { return vector_precise_project(__x,__y); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_project(vector_double8 __x, vector_double8 __y) { return vector_precise_project(__x,__y); }
#endif

static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float2  __x) { return sqrtf(vector_length_squared(__x)); }
static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float3  __x) { return sqrtf(vector_length_squared(__x)); }
static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float4  __x) { return sqrtf(vector_length_squared(__x)); }
static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float8  __x) { return sqrtf(vector_length_squared(__x)); }
static float  __SIMD_ATTRIBUTES__ vector_precise_length(vector_float16 __x) { return sqrtf(vector_length_squared(__x)); }
static double __SIMD_ATTRIBUTES__ vector_precise_length(vector_double2 __x) { return sqrt(vector_length_squared(__x)); }
static double __SIMD_ATTRIBUTES__ vector_precise_length(vector_double3 __x) { return sqrt(vector_length_squared(__x)); }
static double __SIMD_ATTRIBUTES__ vector_precise_length(vector_double4 __x) { return sqrt(vector_length_squared(__x)); }
static double __SIMD_ATTRIBUTES__ vector_precise_length(vector_double8 __x) { return sqrt(vector_length_squared(__x)); }

static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float2  __x) { return vector_precise_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float3  __x) { return vector_precise_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float4  __x) { return vector_precise_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float8  __x) { return vector_precise_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_fast_length(vector_float16 __x) { return vector_precise_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_fast_length(vector_double2 __x) { return vector_precise_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_fast_length(vector_double3 __x) { return vector_precise_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_fast_length(vector_double4 __x) { return vector_precise_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_fast_length(vector_double8 __x) { return vector_precise_length(__x); }

#if defined __FAST_MATH__
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float2  __x) { return vector_fast_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float3  __x) { return vector_fast_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float4  __x) { return vector_fast_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float8  __x) { return vector_fast_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float16 __x) { return vector_fast_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_length(vector_double2 __x) { return vector_fast_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_length(vector_double3 __x) { return vector_fast_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_length(vector_double4 __x) { return vector_fast_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_length(vector_double8 __x) { return vector_fast_length(__x); }
#else
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float2  __x) { return vector_precise_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float3  __x) { return vector_precise_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float4  __x) { return vector_precise_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float8  __x) { return vector_precise_length(__x); }
static float  __SIMD_ATTRIBUTES__ vector_length(vector_float16 __x) { return vector_precise_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_length(vector_double2 __x) { return vector_precise_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_length(vector_double3 __x) { return vector_precise_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_length(vector_double4 __x) { return vector_precise_length(__x); }
static double __SIMD_ATTRIBUTES__ vector_length(vector_double8 __x) { return vector_precise_length(__x); }
#endif

static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float2  __x) { return vector_dot(__x,__x); }
static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float3  __x) { return vector_dot(__x,__x); }
static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float4  __x) { return vector_dot(__x,__x); }
static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float8  __x) { return vector_dot(__x,__x); }
static float  __SIMD_ATTRIBUTES__ vector_length_squared(vector_float16 __x) { return vector_dot(__x,__x); }
static double __SIMD_ATTRIBUTES__ vector_length_squared(vector_double2 __x) { return vector_dot(__x,__x); }
static double __SIMD_ATTRIBUTES__ vector_length_squared(vector_double3 __x) { return vector_dot(__x,__x); }
static double __SIMD_ATTRIBUTES__ vector_length_squared(vector_double4 __x) { return vector_dot(__x,__x); }
static double __SIMD_ATTRIBUTES__ vector_length_squared(vector_double8 __x) { return vector_dot(__x,__x); }

static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float2  __x, vector_float2  __y) { return vector_precise_length(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float3  __x, vector_float3  __y) { return vector_precise_length(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float4  __x, vector_float4  __y) { return vector_precise_length(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float8  __x, vector_float8  __y) { return vector_precise_length(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_precise_distance(vector_float16 __x, vector_float16 __y) { return vector_precise_length(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_precise_distance(vector_double2 __x, vector_double2 __y) { return vector_precise_length(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_precise_distance(vector_double3 __x, vector_double3 __y) { return vector_precise_length(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_precise_distance(vector_double4 __x, vector_double4 __y) { return vector_precise_length(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_precise_distance(vector_double8 __x, vector_double8 __y) { return vector_precise_length(__x - __y); }

static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float2  __x, vector_float2  __y) { return vector_fast_length(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float3  __x, vector_float3  __y) { return vector_fast_length(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float4  __x, vector_float4  __y) { return vector_fast_length(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float8  __x, vector_float8  __y) { return vector_fast_length(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_fast_distance(vector_float16 __x, vector_float16 __y) { return vector_fast_length(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_fast_distance(vector_double2 __x, vector_double2 __y) { return vector_fast_length(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_fast_distance(vector_double3 __x, vector_double3 __y) { return vector_fast_length(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_fast_distance(vector_double4 __x, vector_double4 __y) { return vector_fast_length(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_fast_distance(vector_double8 __x, vector_double8 __y) { return vector_fast_length(__x - __y); }

#if defined __FAST_MATH__
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float2  __x, vector_float2  __y) { return vector_fast_distance(__x,__y); }
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float3  __x, vector_float3  __y) { return vector_fast_distance(__x,__y); }
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float4  __x, vector_float4  __y) { return vector_fast_distance(__x,__y); }
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float8  __x, vector_float8  __y) { return vector_fast_distance(__x,__y); }
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float16 __x, vector_float16 __y) { return vector_fast_distance(__x,__y); }
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double2 __x, vector_double2 __y) { return vector_fast_distance(__x,__y); }
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double3 __x, vector_double3 __y) { return vector_fast_distance(__x,__y); }
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double4 __x, vector_double4 __y) { return vector_fast_distance(__x,__y); }
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double8 __x, vector_double8 __y) { return vector_fast_distance(__x,__y); }
#else
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float2  __x, vector_float2  __y) { return vector_precise_distance(__x,__y); }
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float3  __x, vector_float3  __y) { return vector_precise_distance(__x,__y); }
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float4  __x, vector_float4  __y) { return vector_precise_distance(__x,__y); }
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float8  __x, vector_float8  __y) { return vector_precise_distance(__x,__y); }
static float  __SIMD_ATTRIBUTES__ vector_distance(vector_float16 __x, vector_float16 __y) { return vector_precise_distance(__x,__y); }
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double2 __x, vector_double2 __y) { return vector_precise_distance(__x,__y); }
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double3 __x, vector_double3 __y) { return vector_precise_distance(__x,__y); }
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double4 __x, vector_double4 __y) { return vector_precise_distance(__x,__y); }
static double __SIMD_ATTRIBUTES__ vector_distance(vector_double8 __x, vector_double8 __y) { return vector_precise_distance(__x,__y); }
#endif

static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float2  __x, vector_float2  __y) { return vector_length_squared(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float3  __x, vector_float3  __y) { return vector_length_squared(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float4  __x, vector_float4  __y) { return vector_length_squared(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float8  __x, vector_float8  __y) { return vector_length_squared(__x - __y); }
static float  __SIMD_ATTRIBUTES__ vector_distance_squared(vector_float16 __x, vector_float16 __y) { return vector_length_squared(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_distance_squared(vector_double2 __x, vector_double2 __y) { return vector_length_squared(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_distance_squared(vector_double3 __x, vector_double3 __y) { return vector_length_squared(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_distance_squared(vector_double4 __x, vector_double4 __y) { return vector_length_squared(__x - __y); }
static double __SIMD_ATTRIBUTES__ vector_distance_squared(vector_double8 __x, vector_double8 __y) { return vector_length_squared(__x - __y); }

static vector_float2  __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float2  __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float3  __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float4  __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float8  __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_float16 __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_double2 __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_double3 __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_double4 __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_precise_normalize(vector_double8 __x) { return __x * vector_precise_rsqrt(vector_length_squared(__x)); }

static vector_float2  __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float2  __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float3  __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float4  __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float8  __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_float16 __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_double2 __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_double3 __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_double4 __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_fast_normalize(vector_double8 __x) { return __x * vector_fast_rsqrt(vector_length_squared(__x)); }

#if defined __FAST_MATH__
static vector_float2  __SIMD_ATTRIBUTES__ vector_normalize(vector_float2  __x) { return vector_fast_normalize(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_normalize(vector_float3  __x) { return vector_fast_normalize(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_normalize(vector_float4  __x) { return vector_fast_normalize(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_normalize(vector_float8  __x) { return vector_fast_normalize(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_normalize(vector_float16 __x) { return vector_fast_normalize(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_normalize(vector_double2 __x) { return vector_fast_normalize(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_normalize(vector_double3 __x) { return vector_fast_normalize(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_normalize(vector_double4 __x) { return vector_fast_normalize(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_normalize(vector_double8 __x) { return vector_fast_normalize(__x); }
#else
static vector_float2  __SIMD_ATTRIBUTES__ vector_normalize(vector_float2  __x) { return vector_precise_normalize(__x); }
static vector_float3  __SIMD_ATTRIBUTES__ vector_normalize(vector_float3  __x) { return vector_precise_normalize(__x); }
static vector_float4  __SIMD_ATTRIBUTES__ vector_normalize(vector_float4  __x) { return vector_precise_normalize(__x); }
static vector_float8  __SIMD_ATTRIBUTES__ vector_normalize(vector_float8  __x) { return vector_precise_normalize(__x); }
static vector_float16 __SIMD_ATTRIBUTES__ vector_normalize(vector_float16 __x) { return vector_precise_normalize(__x); }
static vector_double2 __SIMD_ATTRIBUTES__ vector_normalize(vector_double2 __x) { return vector_precise_normalize(__x); }
static vector_double3 __SIMD_ATTRIBUTES__ vector_normalize(vector_double3 __x) { return vector_precise_normalize(__x); }
static vector_double4 __SIMD_ATTRIBUTES__ vector_normalize(vector_double4 __x) { return vector_precise_normalize(__x); }
static vector_double8 __SIMD_ATTRIBUTES__ vector_normalize(vector_double8 __x) { return vector_precise_normalize(__x); }
#endif

static vector_float3  __SIMD_ATTRIBUTES__ vector_cross(vector_float2  __x, vector_float2  __y) { return (vector_float3){ 0, 0, __x.x*__y.y - __x.y*__y.x }; }
static vector_float3  __SIMD_ATTRIBUTES__ vector_cross(vector_float3  __x, vector_float3  __y) { return (vector_float3){ __x.y*__y.z - __x.z*__y.y, __x.z*__y.x - __x.x*__y.z, __x.x*__y.y - __x.y*__y.x }; }
static vector_double3 __SIMD_ATTRIBUTES__ vector_cross(vector_double2 __x, vector_double2 __y) { return (vector_double3){ 0, 0, __x.x*__y.y - __x.y*__y.x }; }
static vector_double3 __SIMD_ATTRIBUTES__ vector_cross(vector_double3 __x, vector_double3 __y) { return (vector_double3){ __x.y*__y.z - __x.z*__y.y, __x.z*__y.x - __x.x*__y.z, __x.x*__y.y - __x.y*__y.x }; }

static vector_float2  __SIMD_ATTRIBUTES__ vector_reflect(vector_float2  __x, vector_float2  __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_float3  __SIMD_ATTRIBUTES__ vector_reflect(vector_float3  __x, vector_float3  __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_float4  __SIMD_ATTRIBUTES__ vector_reflect(vector_float4  __x, vector_float4  __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_double2 __SIMD_ATTRIBUTES__ vector_reflect(vector_double2 __x, vector_double2 __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_double3 __SIMD_ATTRIBUTES__ vector_reflect(vector_double3 __x, vector_double3 __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_double4 __SIMD_ATTRIBUTES__ vector_reflect(vector_double4 __x, vector_double4 __n) { return __x - 2*vector_dot(__x,__n)*__n; }

#ifdef __cplusplus
}
#endif
#endif /* __SIMD_REQUIRED_COMPILER_FEATURES__ */
#endif /* __SIMD_COMMON_HEADER__ */
