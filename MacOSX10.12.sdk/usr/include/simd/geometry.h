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
 *      vector_length(x)            The length (two-norm) of x.  Undefined if
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
 *      vector_norm_one(x)          The one-norm (sum of absolute values) of x.
 *
 *      vector_norm_inf(x)          The inf-norm (max absolute value) of x.
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
 *      vector_refract(x,n,eta)     Calculates the refraction direction given
 *                                  unit incident vector x, unit normal vector
 *                                  n, and index of refraction eta.  If the
 *                                  angle between the incident vector and the
 *                                  surface normal is too great for the
 *                                  specified index of refraction, zero is
 *                                  returned.
 *                                  Available for vectors of length 2, 3, or 4.
 *
 *  In C++ the following geometric functions are available in the simd::
 *  namespace:
 *
 *      C++ Function                    Equivalent C Function
 *      --------------------------------------------------------------------
 *      simd::dot(x,y)                  vector_dot(x,y)
 *      simd::project(x,y)              vector_project(x,y)
 *      simd::length_squared(x)         vector_length_squared(x)
 *      simd::length(x)                 vector_length(x)
 *      simd::distance_squared(x,y)     vector_distance_squared(x,y)
 *      simd::norm_one(x)               vector_norm_one(x)
 *      simd::norm_inf(x)               vector_norm_inf(x)
 *      simd::distance(x,y)             vector_distance(x,y)
 *      simd::normalize(x)              vector_normalize(x)
 *      simd::cross(x,y)                vector_cross(x,y)
 *      simd::reflect(x,n)              vector_reflect(x,n)
 *      simd::refract(x,n,eta)          vector_refract(x,n,eta)
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

static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float2 __x);
static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float3 __x);
static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float4 __x);
static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float8 __x);
static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float16 __x);
static double __SIMD_ATTRIBUTES__ vector_norm_one(vector_double2 __x);
static double __SIMD_ATTRIBUTES__ vector_norm_one(vector_double3 __x);
static double __SIMD_ATTRIBUTES__ vector_norm_one(vector_double4 __x);
static double __SIMD_ATTRIBUTES__ vector_norm_one(vector_double8 __x);

static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float2 __x);
static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float3 __x);
static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float4 __x);
static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float8 __x);
static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float16 __x);
static double __SIMD_ATTRIBUTES__ vector_norm_inf(vector_double2 __x);
static double __SIMD_ATTRIBUTES__ vector_norm_inf(vector_double3 __x);
static double __SIMD_ATTRIBUTES__ vector_norm_inf(vector_double4 __x);
static double __SIMD_ATTRIBUTES__ vector_norm_inf(vector_double8 __x);

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

static vector_float2  __SIMD_ATTRIBUTES__ vector_refract(vector_float2  __x, vector_float2  __n, float __eta);
static vector_float3  __SIMD_ATTRIBUTES__ vector_refract(vector_float3  __x, vector_float3  __n, float __eta);
static vector_float4  __SIMD_ATTRIBUTES__ vector_refract(vector_float4  __x, vector_float4  __n, float __eta);
static vector_double2 __SIMD_ATTRIBUTES__ vector_refract(vector_double2 __x, vector_double2 __n, double __eta);
static vector_double3 __SIMD_ATTRIBUTES__ vector_refract(vector_double3 __x, vector_double3 __n, double __eta);
static vector_double4 __SIMD_ATTRIBUTES__ vector_refract(vector_double4 __x, vector_double4 __n, double __eta);

#if SIMD_LIBRARY_VERSION >= 2
/*  These functions require that you are building for OS X 10.12 or later,
 *  iOS 10.0 or later, watchOS 3.0 or later, and tvOS 10.0 or later.  On
 *  earlier OS versions, the library functions that implement these
 *  operations are not available.                                             */

/*! @functiongroup vector orientation
 *
 *  @discussion These functions return a positive value if the origin and
 *  their ordered arguments determine a positively oriented parallelepiped,
 *  zero if it is degenerate, and a negative value if it is negatively
 *  oriented.  This is equivalent to saying that the matrix with rows equal
 *  to the vectors has a positive, zero, or negative determinant,
 *  respectively.
 *
 *  Naive evaluation of the determinant is prone to producing incorrect
 *  results if the vectors are nearly degenerate (e.g. floating-point
 *  rounding might cause the determinant to be zero or negative when
 *  the points are very nearly coplanar but positively oriented).  If
 *  the vectors are very large or small, computing the determininat is
 *  also prone to premature overflow, which may cause the result to be
 *  NaN even though the vectors contain normal floating-point numbers.
 *
 *  These routines take care to avoid those issues and always return a
 *  result with correct sign, even when the problem is very ill-
 *  conditioned.                                                              */

/*! @abstract Test the orientation of two 2d vectors.
 *
 *  @param __x The first vector.
 *  @param __y The second vector.
 *
 *  @result Positive if (x, y) are positively oriented, zero if they are
 *  colinear, and negative if they are negatively oriented.
 *
 *  @discussion For two-dimensional vectors, "positively oriented" is
 *  equivalent to the ordering (0, x, y) proceeding counter-clockwise
 *  when viewed down the z axis, or to the cross product of x and y
 *  extended to three-dimensions having positive z-component.                 */
static float __SIMD_ATTRIBUTES__ simd_orient(vector_float2 __x, vector_float2 __y);

/*! @abstract Test the orientation of two 2d vectors.
 *
 *  @param __x The first vector.
 *  @param __y The second vector.
 *
 *  @result Positive if (x, y) are positively oriented, zero if they are
 *  colinear, and negative if they are negatively oriented.
 *
 *  @discussion For two-dimensional vectors, "positively oriented" is
 *  equivalent to the ordering (0, x, y) proceeding counter- clockwise
 *  when viewed down the z axis, or to the cross product of x and y
 *  extended to three-dimensions having positive z-component.                 */
static double __SIMD_ATTRIBUTES__ simd_orient(vector_double2 __x, vector_double2 __y);

/*! @abstract Test the orientation of three 3d vectors.
 *
 *  @param __x The first vector.
 *  @param __y The second vector.
 *  @param __z The third vector.
 *
 *  @result Positive if (x, y, z) are positively oriented, zero if they
 *  are coplanar, and negative if they are negatively oriented.
 *
 *  @discussion For three-dimensional vectors, "positively oriented" is
 *  equivalent to the ordering (x, y, z) following the "right hand rule",
 *  or to the dot product of z with the cross product of x and y being
 *  positive.                                                                 */
static float __SIMD_ATTRIBUTES__ simd_orient(vector_float3 __x, vector_float3 __y, vector_float3 __z);

/*! @abstract Test the orientation of three 3d vectors.
 *
 *  @param __x The first vector.
 *  @param __y The second vector.
 *  @param __z The third vector.
 *
 *  @result Positive if (x, y, c) are positively oriented, zero if they
 *  are coplanar, and negative if they are negatively oriented.
 *
 *  @discussion For three-dimensional vectors, "positively oriented" is
 *  equivalent to the ordering (x, y, z) following the "right hand rule",
 *  or to the dot product of z with the cross product of x and y being
 *  positive.                                                                 */
static double __SIMD_ATTRIBUTES__ simd_orient(vector_double3 __x, vector_double3 __y, vector_double3 __z);

/*! @functiongroup point (affine) orientation
 *
 *  @discussion These functions return a positive value if their ordered
 *  arguments determine a positively oriented parallelepiped, zero if it
 *  is degenerate, and a negative value if it is negatively oriented.
 *
 *  simd_orient(a, b, c) is formally equivalent to simd_orient(b-a, c-a),
 *  but it is not effected by rounding error from subtraction of points,
 *  as that implementation would be.  Care is taken so that the sign of
 *  the result is always correct, even if the problem is ill-conditioned.     */

/*! @abstract Test the orientation of a triangle in 2d.
 *
 *  @param __a The first point of the triangle.
 *  @param __b The second point of the triangle.
 *  @param __c The third point of the triangle.
 *
 *  @result Positive if the triangle is positively oriented, zero if it
 *  is degenerate (three points in a line), and negative if it is negatively
 *  oriented.
 *
 *  @discussion "Positively oriented" is equivalent to the ordering
 *  (a, b, c) proceeding counter-clockwise when viewed down the z axis,
 *  or to the cross product of a-c and b-c extended to three-dimensions
 *  having positive z-component.                                              */
static float __SIMD_ATTRIBUTES__ simd_orient(vector_float2 __a, vector_float2 __b, vector_float2 __c);

/*! @abstract Test the orientation of a triangle in 2d.
 *
 *  @param __a The first point of the triangle.
 *  @param __b The second point of the triangle.
 *  @param __c The third point of the triangle.
 *
 *  @result Positive if the triangle is positively oriented, zero if it
 *  is degenerate (three points in a line), and negative if it is negatively
 *  oriented.
 *
 *  @discussion "Positively oriented" is equivalent to the ordering
 *  (a, b, c) proceeding counter-clockwise when viewed down the z axis,
 *  or to the cross product of a-c and b-c extended to three-dimensions
 *  having positive z-component.                                              */
static double __SIMD_ATTRIBUTES__ simd_orient(vector_double2 __a, vector_double2 __b, vector_double2 __c);

/*! @abstract Test the orientation of a tetrahedron in 3d.
 *
 *  @param __a The first point of the tetrahedron.
 *  @param __b The second point of the tetrahedron.
 *  @param __c The third point of the tetrahedron.
 *  @param __d The fourth point of the tetrahedron.
 *
 *  @result Positive if the tetrahedron is positively oriented, zero if it
 *  is degenerate (four points in a plane), and negative if it is negatively
 *  oriented.
 *
 *  @discussion "Positively oriented" is equivalent to the vectors
 *  (a-d, b-d, c-d) following the "right hand rule", or to the dot product
 *  of c-d with the the cross product of a-d and b-d being positive.          */
static float __SIMD_ATTRIBUTES__ simd_orient(vector_float3 __a, vector_float3 __b, vector_float3 __c, vector_float3 __d);

/*! @abstract Test the orientation of a tetrahedron in 3d.
 *
 *  @param __a The first point of the tetrahedron.
 *  @param __b The second point of the tetrahedron.
 *  @param __c The third point of the tetrahedron.
 *  @param __d The fourth point of the tetrahedron.
 *
 *  @result Positive if the tetrahedron is positively oriented, zero if it
 *  is degenerate (four points in a plane), and negative if it is negatively
 *  oriented.
 *
 *  @discussion "Positively oriented" is equivalent to the vectors
 *  (a-d, b-d, c-d) following the "right hand rule", or to the dot product
 *  of c-d with the the cross product of a-d and b-d being positive.          */
static double __SIMD_ATTRIBUTES__ simd_orient(vector_double3 __a, vector_double3 __b, vector_double3 __c, vector_double3 __d);

/*! @functiongroup incircle (points) tests
 *
 *  @discussion These functions determine whether the point x is inside, on,
 *  or outside the circle or sphere passing through a group of points.  If
 *  x is inside the circle, the result is positive; if x is on the circle,
 *  the result is zero; if x is outside the circle the result is negative.
 *
 *  These functions are always exact, even if the problem is ill-
 *  conditioned (meaning that the points are nearly co-linear or
 *  co-planar).
 *
 *  If the points are negatively-oriented, the the notions of "inside" and
 *  "outside" are flipped.  If the points are degenerate, then the result
 *  is undefined.                                                             */

/*! @abstract Test if x lies inside, on, or outside the circle passing
 *  through a, b, and c.
 *
 *  @param __x The point being tested.
 *  @param __a The first point determining the circle.
 *  @param __b The second point determining the circle.
 *  @param __c The third point determining the circle.
 *
 *  @result Assuming that (a,b,c) are positively-oriented, positive if x is
 *  inside the circle, zero if x is on the circle, and negative if x is
 *  outside the circle.  The sign of the result is flipped if (a,b,c) are
 *  negatively-oriented.                                                      */
static float __SIMD_ATTRIBUTES__ simd_incircle(vector_float2 __x, vector_float2 __a, vector_float2 __b, vector_float2 __c);

/*! @abstract Test if x lies inside, on, or outside the circle passing
 *  through a, b, and c.
 *
 *  @param __x The point being tested.
 *  @param __a The first point determining the circle.
 *  @param __b The second point determining the circle.
 *  @param __c The third point determining the circle.
 *
 *  @result Assuming that (a,b,c) are positively-oriented, positive if x is
 *  inside the circle, zero if x is on the circle, and negative if x is
 *  outside the circle.  The sign of the result is flipped if (a,b,c) are
 *  negatively-oriented.                                                      */
static double __SIMD_ATTRIBUTES__ simd_incircle(vector_double2 __x, vector_double2 __a, vector_double2 __b, vector_double2 __c);

/*! @abstract Test if x lies inside, on, or outside the sphere passing
 *  through a, b, c, and d.
 *
 *  @param __x The point being tested.
 *  @param __a The first point determining the sphere.
 *  @param __b The second point determining the sphere.
 *  @param __c The third point determining the sphere.
 *  @param __d The fourth point determining the sphere.
 *
 *  @result Assuming that the points are positively-oriented, positive if x
 *  is inside the sphere, zero if x is on the sphere, and negative if x is
 *  outside the sphere.  The sign of the result is flipped if the points are
 *  negatively-oriented.                                                      */
static float __SIMD_ATTRIBUTES__ simd_insphere(vector_float3 __x, vector_float3 __a, vector_float3 __b, vector_float3 __c, vector_float3 __d);

/*! @abstract Test if x lies inside, on, or outside the sphere passing
 *  through a, b, c, and d.
 *
 *  @param __x The point being tested.
 *  @param __a The first point determining the sphere.
 *  @param __b The second point determining the sphere.
 *  @param __c The third point determining the sphere.
 *  @param __d The fourth point determining the sphere.
 *
 *  @result Assuming that the points are positively-oriented, positive if x
 *  is inside the sphere, zero if x is on the sphere, and negative if x is
 *  outside the sphere.  The sign of the result is flipped if the points are
 *  negatively-oriented.                                                      */
static double __SIMD_ATTRIBUTES__ simd_insphere(vector_double3 __x, vector_double3 __a, vector_double3 __b, vector_double3 __c, vector_double3 __d);
#endif /* SIMD_LIBRARY_VERSION */
  
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
  
  static __SIMD_INLINE__ float2  project(const float2  x, const float2  y) { return ::vector_project(x, y); }
  static __SIMD_INLINE__ float3  project(const float3  x, const float3  y) { return ::vector_project(x, y); }
  static __SIMD_INLINE__ float4  project(const float4  x, const float4  y) { return ::vector_project(x, y); }
  static __SIMD_INLINE__ float8  project(const float8  x, const float8  y) { return ::vector_project(x, y); }
  static __SIMD_INLINE__ float16 project(const float16 x, const float16 y) { return ::vector_project(x, y); }
  static __SIMD_INLINE__ double2 project(const double2 x, const double2 y) { return ::vector_project(x, y); }
  static __SIMD_INLINE__ double3 project(const double3 x, const double3 y) { return ::vector_project(x, y); }
  static __SIMD_INLINE__ double4 project(const double4 x, const double4 y) { return ::vector_project(x, y); }
  static __SIMD_INLINE__ double8 project(const double8 x, const double8 y) { return ::vector_project(x, y); }
  
  static __SIMD_INLINE__ float  length_squared(const float2  x) { return ::vector_length_squared(x); }
  static __SIMD_INLINE__ float  length_squared(const float3  x) { return ::vector_length_squared(x); }
  static __SIMD_INLINE__ float  length_squared(const float4  x) { return ::vector_length_squared(x); }
  static __SIMD_INLINE__ float  length_squared(const float8  x) { return ::vector_length_squared(x); }
  static __SIMD_INLINE__ float  length_squared(const float16 x) { return ::vector_length_squared(x); }
  static __SIMD_INLINE__ double length_squared(const double2 x) { return ::vector_length_squared(x); }
  static __SIMD_INLINE__ double length_squared(const double3 x) { return ::vector_length_squared(x); }
  static __SIMD_INLINE__ double length_squared(const double4 x) { return ::vector_length_squared(x); }
  static __SIMD_INLINE__ double length_squared(const double8 x) { return ::vector_length_squared(x); }
  
  static __SIMD_INLINE__ float  norm_one(const float2  x) { return ::vector_norm_one(x); }
  static __SIMD_INLINE__ float  norm_one(const float3  x) { return ::vector_norm_one(x); }
  static __SIMD_INLINE__ float  norm_one(const float4  x) { return ::vector_norm_one(x); }
  static __SIMD_INLINE__ float  norm_one(const float8  x) { return ::vector_norm_one(x); }
  static __SIMD_INLINE__ float  norm_one(const float16 x) { return ::vector_norm_one(x); }
  static __SIMD_INLINE__ double norm_one(const double2 x) { return ::vector_norm_one(x); }
  static __SIMD_INLINE__ double norm_one(const double3 x) { return ::vector_norm_one(x); }
  static __SIMD_INLINE__ double norm_one(const double4 x) { return ::vector_norm_one(x); }
  static __SIMD_INLINE__ double norm_one(const double8 x) { return ::vector_norm_one(x); }
  
  static __SIMD_INLINE__ float  norm_inf(const float2  x) { return ::vector_norm_inf(x); }
  static __SIMD_INLINE__ float  norm_inf(const float3  x) { return ::vector_norm_inf(x); }
  static __SIMD_INLINE__ float  norm_inf(const float4  x) { return ::vector_norm_inf(x); }
  static __SIMD_INLINE__ float  norm_inf(const float8  x) { return ::vector_norm_inf(x); }
  static __SIMD_INLINE__ float  norm_inf(const float16 x) { return ::vector_norm_inf(x); }
  static __SIMD_INLINE__ double norm_inf(const double2 x) { return ::vector_norm_inf(x); }
  static __SIMD_INLINE__ double norm_inf(const double3 x) { return ::vector_norm_inf(x); }
  static __SIMD_INLINE__ double norm_inf(const double4 x) { return ::vector_norm_inf(x); }
  static __SIMD_INLINE__ double norm_inf(const double8 x) { return ::vector_norm_inf(x); }
  
  static __SIMD_INLINE__ float  length(const float2  x) { return ::vector_length(x); }
  static __SIMD_INLINE__ float  length(const float3  x) { return ::vector_length(x); }
  static __SIMD_INLINE__ float  length(const float4  x) { return ::vector_length(x); }
  static __SIMD_INLINE__ float  length(const float8  x) { return ::vector_length(x); }
  static __SIMD_INLINE__ float  length(const float16 x) { return ::vector_length(x); }
  static __SIMD_INLINE__ double length(const double2 x) { return ::vector_length(x); }
  static __SIMD_INLINE__ double length(const double3 x) { return ::vector_length(x); }
  static __SIMD_INLINE__ double length(const double4 x) { return ::vector_length(x); }
  static __SIMD_INLINE__ double length(const double8 x) { return ::vector_length(x); }
  
  static __SIMD_INLINE__ float  distance_squared(const float2  x, const float2  y) { return ::vector_distance_squared(x, y); }
  static __SIMD_INLINE__ float  distance_squared(const float3  x, const float3  y) { return ::vector_distance_squared(x, y); }
  static __SIMD_INLINE__ float  distance_squared(const float4  x, const float4  y) { return ::vector_distance_squared(x, y); }
  static __SIMD_INLINE__ float  distance_squared(const float8  x, const float8  y) { return ::vector_distance_squared(x, y); }
  static __SIMD_INLINE__ float  distance_squared(const float16 x, const float16 y) { return ::vector_distance_squared(x, y); }
  static __SIMD_INLINE__ double distance_squared(const double2 x, const double2 y) { return ::vector_distance_squared(x, y); }
  static __SIMD_INLINE__ double distance_squared(const double3 x, const double3 y) { return ::vector_distance_squared(x, y); }
  static __SIMD_INLINE__ double distance_squared(const double4 x, const double4 y) { return ::vector_distance_squared(x, y); }
  static __SIMD_INLINE__ double distance_squared(const double8 x, const double8 y) { return ::vector_distance_squared(x, y); }
  
  static __SIMD_INLINE__ float  distance(const float2  x, const float2  y) { return ::vector_distance(x, y); }
  static __SIMD_INLINE__ float  distance(const float3  x, const float3  y) { return ::vector_distance(x, y); }
  static __SIMD_INLINE__ float  distance(const float4  x, const float4  y) { return ::vector_distance(x, y); }
  static __SIMD_INLINE__ float  distance(const float8  x, const float8  y) { return ::vector_distance(x, y); }
  static __SIMD_INLINE__ float  distance(const float16 x, const float16 y) { return ::vector_distance(x, y); }
  static __SIMD_INLINE__ double distance(const double2 x, const double2 y) { return ::vector_distance(x, y); }
  static __SIMD_INLINE__ double distance(const double3 x, const double3 y) { return ::vector_distance(x, y); }
  static __SIMD_INLINE__ double distance(const double4 x, const double4 y) { return ::vector_distance(x, y); }
  static __SIMD_INLINE__ double distance(const double8 x, const double8 y) { return ::vector_distance(x, y); }
  
  static __SIMD_INLINE__ float2  normalize(const float2  x) { return ::vector_normalize(x); }
  static __SIMD_INLINE__ float3  normalize(const float3  x) { return ::vector_normalize(x); }
  static __SIMD_INLINE__ float4  normalize(const float4  x) { return ::vector_normalize(x); }
  static __SIMD_INLINE__ float8  normalize(const float8  x) { return ::vector_normalize(x); }
  static __SIMD_INLINE__ float16 normalize(const float16 x) { return ::vector_normalize(x); }
  static __SIMD_INLINE__ double2 normalize(const double2 x) { return ::vector_normalize(x); }
  static __SIMD_INLINE__ double3 normalize(const double3 x) { return ::vector_normalize(x); }
  static __SIMD_INLINE__ double4 normalize(const double4 x) { return ::vector_normalize(x); }
  static __SIMD_INLINE__ double8 normalize(const double8 x) { return ::vector_normalize(x); }
  
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
  
  static __SIMD_INLINE__ float2  refract(const float2  x, const float2  n, const float eta) { return ::vector_refract(x,n,eta); }
  static __SIMD_INLINE__ float3  refract(const float3  x, const float3  n, const float eta) { return ::vector_refract(x,n,eta); }
  static __SIMD_INLINE__ float4  refract(const float4  x, const float4  n, const float eta) { return ::vector_refract(x,n,eta); }
  static __SIMD_INLINE__ double2 refract(const double2 x, const double2 n, const float eta) { return ::vector_refract(x,n,eta); }
  static __SIMD_INLINE__ double3 refract(const double3 x, const double3 n, const float eta) { return ::vector_refract(x,n,eta); }
  static __SIMD_INLINE__ double4 refract(const double4 x, const double4 n, const float eta) { return ::vector_refract(x,n,eta); }
  
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

static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float2  __x, vector_float2  __y) { return vector_reduce_add(__x*__y); }
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float3  __x, vector_float3  __y) { return vector_reduce_add(__x*__y); }
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float4  __x, vector_float4  __y) { return vector_reduce_add(__x*__y); }
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float8  __x, vector_float8  __y) { return vector_reduce_add(__x*__y); }
static float  __SIMD_ATTRIBUTES__ vector_dot(vector_float16 __x, vector_float16 __y) { return vector_reduce_add(__x*__y); }
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double2 __x, vector_double2 __y) { return vector_reduce_add(__x*__y); }
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double3 __x, vector_double3 __y) { return vector_reduce_add(__x*__y); }
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double4 __x, vector_double4 __y) { return vector_reduce_add(__x*__y); }
static double __SIMD_ATTRIBUTES__ vector_dot(vector_double8 __x, vector_double8 __y) { return vector_reduce_add(__x*__y); }

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

static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float2 __x) { return vector_reduce_add(__tg_fabs(__x)); }
static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float3 __x) { return vector_reduce_add(__tg_fabs(__x)); }
static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float4 __x) { return vector_reduce_add(__tg_fabs(__x)); }
static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float8 __x) { return vector_reduce_add(__tg_fabs(__x)); }
static float __SIMD_ATTRIBUTES__ vector_norm_one(vector_float16 __x) { return vector_reduce_add(__tg_fabs(__x)); }
static double __SIMD_ATTRIBUTES__ vector_norm_one(vector_double2 __x) { return vector_reduce_add(__tg_fabs(__x)); }
static double __SIMD_ATTRIBUTES__ vector_norm_one(vector_double3 __x) { return vector_reduce_add(__tg_fabs(__x)); }
static double __SIMD_ATTRIBUTES__ vector_norm_one(vector_double4 __x) { return vector_reduce_add(__tg_fabs(__x)); }
static double __SIMD_ATTRIBUTES__ vector_norm_one(vector_double8 __x) { return vector_reduce_add(__tg_fabs(__x)); }

static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float2 __x) { return vector_reduce_max(__tg_fabs(__x)); }
static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float3 __x) { return vector_reduce_max(__tg_fabs(__x)); }
static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float4 __x) { return vector_reduce_max(__tg_fabs(__x)); }
static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float8 __x) { return vector_reduce_max(__tg_fabs(__x)); }
static float __SIMD_ATTRIBUTES__ vector_norm_inf(vector_float16 __x) { return vector_reduce_max(__tg_fabs(__x)); }
static double __SIMD_ATTRIBUTES__ vector_norm_inf(vector_double2 __x) { return vector_reduce_max(__tg_fabs(__x)); }
static double __SIMD_ATTRIBUTES__ vector_norm_inf(vector_double3 __x) { return vector_reduce_max(__tg_fabs(__x)); }
static double __SIMD_ATTRIBUTES__ vector_norm_inf(vector_double4 __x) { return vector_reduce_max(__tg_fabs(__x)); }
static double __SIMD_ATTRIBUTES__ vector_norm_inf(vector_double8 __x) { return vector_reduce_max(__tg_fabs(__x)); }

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
static vector_float3  __SIMD_ATTRIBUTES__ vector_cross(vector_float3  __x, vector_float3  __y) { return (__x.zxy*__y - __x*__y.zxy).zxy; }
static vector_double3 __SIMD_ATTRIBUTES__ vector_cross(vector_double2 __x, vector_double2 __y) { return (vector_double3){ 0, 0, __x.x*__y.y - __x.y*__y.x }; }
static vector_double3 __SIMD_ATTRIBUTES__ vector_cross(vector_double3 __x, vector_double3 __y) { return (__x.zxy*__y - __x*__y.zxy).zxy; }

static vector_float2  __SIMD_ATTRIBUTES__ vector_reflect(vector_float2  __x, vector_float2  __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_float3  __SIMD_ATTRIBUTES__ vector_reflect(vector_float3  __x, vector_float3  __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_float4  __SIMD_ATTRIBUTES__ vector_reflect(vector_float4  __x, vector_float4  __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_double2 __SIMD_ATTRIBUTES__ vector_reflect(vector_double2 __x, vector_double2 __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_double3 __SIMD_ATTRIBUTES__ vector_reflect(vector_double3 __x, vector_double3 __n) { return __x - 2*vector_dot(__x,__n)*__n; }
static vector_double4 __SIMD_ATTRIBUTES__ vector_reflect(vector_double4 __x, vector_double4 __n) { return __x - 2*vector_dot(__x,__n)*__n; }

static vector_float2  __SIMD_ATTRIBUTES__ vector_refract(vector_float2  __x, vector_float2  __n, float __eta) {
  const float __k = 1.0f - __eta*__eta*(1.0f - vector_dot(__x,__n)*vector_dot(__x,__n));
  return (__k >= 0.0f) ? __eta*__x - (__eta*vector_dot(__x,__n) + __tg_sqrt(__k))*__n : (vector_float2)0.0f;
}
static vector_float3  __SIMD_ATTRIBUTES__ vector_refract(vector_float3  __x, vector_float3  __n, float __eta) {
  const float __k = 1.0f - __eta*__eta*(1.0f - vector_dot(__x,__n)*vector_dot(__x,__n));
  return (__k >= 0.0f) ? __eta*__x - (__eta*vector_dot(__x,__n) + __tg_sqrt(__k))*__n : (vector_float3)0.0f;
}
static vector_float4  __SIMD_ATTRIBUTES__ vector_refract(vector_float4  __x, vector_float4  __n, float __eta) {
  const float __k = 1.0f - __eta*__eta*(1.0f - vector_dot(__x,__n)*vector_dot(__x,__n));
  return (__k >= 0.0f) ? __eta*__x - (__eta*vector_dot(__x,__n) + __tg_sqrt(__k))*__n : (vector_float4)0.0f;
}
static vector_double2 __SIMD_ATTRIBUTES__ vector_refract(vector_double2 __x, vector_double2 __n, double __eta) {
  const double __k = 1.0 - __eta*__eta*(1.0 - vector_dot(__x,__n)*vector_dot(__x,__n));
  return (__k >= 0.0) ? __eta*__x - (__eta*vector_dot(__x,__n) + __tg_sqrt(__k))*__n : (vector_double2)0.0;
}
static vector_double3 __SIMD_ATTRIBUTES__ vector_refract(vector_double3 __x, vector_double3 __n, double __eta) {
  const double __k = 1.0 - __eta*__eta*(1.0 - vector_dot(__x,__n)*vector_dot(__x,__n));
  return (__k >= 0.0) ? __eta*__x - (__eta*vector_dot(__x,__n) + __tg_sqrt(__k))*__n : (vector_double3)0.0;
}
static vector_double4 __SIMD_ATTRIBUTES__ vector_refract(vector_double4 __x, vector_double4 __n, double __eta) {
  const double __k = 1.0 - __eta*__eta*(1.0 - vector_dot(__x,__n)*vector_dot(__x,__n));
  return (__k >= 0.0) ? __eta*__x - (__eta*vector_dot(__x,__n) + __tg_sqrt(__k))*__n : (vector_double4)0.0;
}

#if SIMD_LIBRARY_VERSION >= 2
static float __SIMD_ATTRIBUTES__ simd_orient(vector_float2 __x, vector_float2 __y) {
  return _simd_orient_vf2(__x, __y);
}
static double __SIMD_ATTRIBUTES__ simd_orient(vector_double2 __x, vector_double2 __y) {
  return _simd_orient_vd2(__x, __y);
}
static float __SIMD_ATTRIBUTES__ simd_orient(vector_float3 __x, vector_float3 __y, vector_float3 __z) {
  return _simd_orient_vf3(__x, __y, __z);
}
static double __SIMD_ATTRIBUTES__ simd_orient(vector_double3 __x, vector_double3 __y, vector_double3 __z) {
  vector_double3 __args[3] = { __x, __y, __z };
  return _simd_orient_vd3((const double *)__args);
}

static float __SIMD_ATTRIBUTES__ simd_orient(vector_float2 __a, vector_float2 __b, vector_float2 __c) {
  return _simd_orient_pf2(__a, __b, __c);
}
static double __SIMD_ATTRIBUTES__ simd_orient(vector_double2 __a, vector_double2 __b, vector_double2 __c) {
  return _simd_orient_pd2(__a, __b, __c);
}
static float __SIMD_ATTRIBUTES__ simd_orient(vector_float3 __a, vector_float3 __b, vector_float3 __c, vector_float3 __d) {
  return _simd_orient_pf3(__a, __b, __c, __d);
}
static double __SIMD_ATTRIBUTES__ simd_orient(vector_double3 __a, vector_double3 __b, vector_double3 __c, vector_double3 __d) {
  vector_double3 __args[4] = { __a, __b, __c, __d };
  return _simd_orient_vd3((const double *)__args);
}

static float __SIMD_ATTRIBUTES__ simd_incircle(vector_float2 __x, vector_float2 __a, vector_float2 __b, vector_float2 __c) {
  return _simd_incircle_pf2(__x, __a, __b, __c);
}
static double __SIMD_ATTRIBUTES__ simd_incircle(vector_double2 __x, vector_double2 __a, vector_double2 __b, vector_double2 __c) {
  return _simd_incircle_pd2(__x, __a, __b, __c);
}
static float __SIMD_ATTRIBUTES__ simd_insphere(vector_float3 __x, vector_float3 __a, vector_float3 __b, vector_float3 __c, vector_float3 __d) {
  return _simd_insphere_pf3(__x, __a, __b, __c, __d);
}
static double __SIMD_ATTRIBUTES__ simd_insphere(vector_double3 __x, vector_double3 __a, vector_double3 __b, vector_double3 __c, vector_double3 __d) {
  vector_double3 __args[5] = { __x, __a, __b, __c, __d };
  return _simd_insphere_pd3((const double *)__args);
}
#endif /* SIMD_LIBRARY_VERSION */

#ifdef __cplusplus
}
#endif
#endif /* __SIMD_REQUIRED_COMPILER_FEATURES__ */
#endif /* __SIMD_COMMON_HEADER__ */
