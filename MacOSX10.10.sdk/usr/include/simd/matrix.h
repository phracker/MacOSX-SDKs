/* Copyright (c) 2014 Apple, Inc. All rights reserved.
 *
 *      Function                        Result
 *      ------------------------------------------------------------------
 *
 *      matrix_from_diagonal(x)         A square matrix with the vector x
 *                                      as its diagonal.
 *
 *      matrix_from_columns(c0, c1, ... ) A matrix with the specified vectors
 *                                      as columns.
 *
 *      matrix_from_rows(r0, r1, ... )  A matrix with the specified vectors
 *                                      as rows.
 *
 *      matrix_scale(a,x)               Scalar product a*x.
 *
 *      matrix_linear_combination(a,x,b,y)  a*x + b*y.
 *
 *      matrix_add(x,y)                 Macro wrapping linear_combination
 *                                      to compute x + y.
 *
 *      matrix_sub(x,y)                 Macro wrapping linear_combination
 *                                      to compute x - y.
 *
 *      matrix_transpose(x)             Transpose of the matrix x.
 *
 *      matrix_invert(x)                Inverse of x if x is non-singular.  If
 *                                      x is singular, the result is undefined.
 *
 *      matrix_multiply(x,y)            If x is a matrix, returns the matrix
 *                                      product x*y, where y is either a matrix
 *                                      or a column vector.  If x is a vector,
 *                                      returns the product x*y where x is
 *                                      interpreted as a row vector.
 *
 *  The header also defines a few useful global matrix objects:
 *  matrix_identity_floatNxM and matrix_identity_doubleNxM, may be used to get
 *  an identity matrix of the specified size.
 *
 *  In C++, we are able to use namespacing to make the functions more concise;
 *  we also overload some common arithmetic operators to work with the matrix
 *  types:
 *
 *      C++ Function                    Equivalent C Function
 *      --------------------------------------------------------------------
 *      SIMD::inverse                   matrix_invert
 *      SIMD::transpose                 matrix_transpose
 *      operator+                       matrix_add
 *      operator-                       matrix_sub
 *      operator+=                      N/A
 *      operator-=                      N/A
 *      operator*                       matrix_scale or matrix_multiply
 *      operator*=                      matrix_scale or matrix_multiply
 *
 *  <simd/matrix_types.h> provides constructors that are equivalent to the
 *  various matrix_from functions.
 */

#ifndef __SIMD_MATRIX_HEADER__
#define __SIMD_MATRIX_HEADER__

#include <simd/internal.h>
#if __SIMD_REQUIRED_COMPILER_FEATURES__
#include <simd/matrix_types.h>
#include <simd/geometry.h>
#include <simd/extern.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const matrix_float2x2 matrix_identity_float2x2  __SIMD_AVAILABILITY__;
extern const matrix_float3x3 matrix_identity_float3x3  __SIMD_AVAILABILITY__;
extern const matrix_float4x4 matrix_identity_float4x4  __SIMD_AVAILABILITY__;
extern const matrix_double2x2 matrix_identity_double2x2 __SIMD_AVAILABILITY__;
extern const matrix_double3x3 matrix_identity_double3x3 __SIMD_AVAILABILITY__;
extern const matrix_double4x4 matrix_identity_double4x4 __SIMD_AVAILABILITY__;

static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_float2 __x);
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_float3 __x);
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_float4 __x);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_double2 __x);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_double3 __x);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_double4 __x);

static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float2 col0, vector_float2 col1);
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float2 col0, vector_float2 col1, vector_float2 col2);
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float2 col0, vector_float2 col1, vector_float2 col2, vector_float2 col3);
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float3 col0, vector_float3 col1);
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float3 col0, vector_float3 col1, vector_float3 col2);
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float3 col0, vector_float3 col1, vector_float3 col2, vector_float3 col3);
static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float4 col0, vector_float4 col1);
static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float4 col0, vector_float4 col1, vector_float4 col2);
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float4 col0, vector_float4 col1, vector_float4 col2, vector_float4 col3);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double2 col0, vector_double2 col1);
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double2 col0, vector_double2 col1, vector_double2 col2);
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double2 col0, vector_double2 col1, vector_double2 col2, vector_double2 col3);
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double3 col0, vector_double3 col1);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double3 col0, vector_double3 col1, vector_double3 col2);
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double3 col0, vector_double3 col1, vector_double3 col2, vector_double3 col3);
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double4 col0, vector_double4 col1);
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double4 col0, vector_double4 col1, vector_double4 col2);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double4 col0, vector_double4 col1, vector_double4 col2, vector_double4 col3);

static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float2 row0, vector_float2 row1);
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float2 row0, vector_float2 row1, vector_float2 row2);
static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float2 row0, vector_float2 row1, vector_float2 row2, vector_float2 row3);
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float3 row0, vector_float3 row1);
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float3 row0, vector_float3 row1, vector_float3 row2);
static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float3 row0, vector_float3 row1, vector_float3 row2, vector_float3 row3);
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float4 row0, vector_float4 row1);
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float4 row0, vector_float4 row1, vector_float4 row2);
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float4 row0, vector_float4 row1, vector_float4 row2, vector_float4 row3);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double2 row0, vector_double2 row1);
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double2 row0, vector_double2 row1, vector_double2 row2);
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double2 row0, vector_double2 row1, vector_double2 row2, vector_double2 row3);
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double3 row0, vector_double3 row1);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double3 row0, vector_double3 row1, vector_double3 row2);
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double3 row0, vector_double3 row1, vector_double3 row2, vector_double3 row3);
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double4 row0, vector_double4 row1);
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double4 row0, vector_double4 row1, vector_double4 row2);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double4 row0, vector_double4 row1, vector_double4 row2, vector_double4 row3);

static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float2x2 __x);
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float3x2 __x);
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float4x2 __x);
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float2x3 __x);
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float3x3 __x);
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float4x3 __x);
static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float2x4 __x);
static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float3x4 __x);
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_scale(float __a, matrix_float4x4 __x);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double2x2 __x);
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double3x2 __x);
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double4x2 __x);
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double2x3 __x);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double3x3 __x);
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double4x3 __x);
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double2x4 __x);
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double3x4 __x);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double4x4 __x);

static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float2x2 __x, float __b, matrix_float2x2 __y);
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float3x2 __x, float __b, matrix_float3x2 __y);
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float4x2 __x, float __b, matrix_float4x2 __y);
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float2x3 __x, float __b, matrix_float2x3 __y);
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float3x3 __x, float __b, matrix_float3x3 __y);
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float4x3 __x, float __b, matrix_float4x3 __y);
static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float2x4 __x, float __b, matrix_float2x4 __y);
static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float3x4 __x, float __b, matrix_float3x4 __y);
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(float __a, matrix_float4x4 __x, float __b, matrix_float4x4 __y);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double2x2 __x, double __b, matrix_double2x2 __y);
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double3x2 __x, double __b, matrix_double3x2 __y);
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double4x2 __x, double __b, matrix_double4x2 __y);
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double2x3 __x, double __b, matrix_double2x3 __y);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double3x3 __x, double __b, matrix_double3x3 __y);
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double4x3 __x, double __b, matrix_double4x3 __y);
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double2x4 __x, double __b, matrix_double2x4 __y);
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double3x4 __x, double __b, matrix_double3x4 __y);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double4x4 __x, double __b, matrix_double4x4 __y);

#define matrix_add(__x,__y) matrix_linear_combination(1,(__x), 1,(__y))
#define matrix_sub(__x,__y) matrix_linear_combination(1,(__x),-1,(__y))

static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float2x2 __x);
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float3x2 __x);
static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float4x2 __x);
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float2x3 __x);
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float3x3 __x);
static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float4x3 __x);
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float2x4 __x);
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float3x4 __x);
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float4x4 __x);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double2x2 __x);
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double3x2 __x);
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double4x2 __x);
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double2x3 __x);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double3x3 __x);
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double4x3 __x);
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double2x4 __x);
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double3x4 __x);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double4x4 __x);

static float __SIMD_ATTRIBUTES__ matrix_determinant(matrix_float2x2 __x);
static float __SIMD_ATTRIBUTES__ matrix_determinant(matrix_float3x3 __x);
static float __SIMD_ATTRIBUTES__ matrix_determinant(matrix_float4x4 __x) __SIMD_AVAILABILITY__;
static double __SIMD_ATTRIBUTES__ matrix_determinant(matrix_double2x2 __x);
static double __SIMD_ATTRIBUTES__ matrix_determinant(matrix_double3x3 __x);
static double __SIMD_ATTRIBUTES__ matrix_determinant(matrix_double4x4 __x) __SIMD_AVAILABILITY__;

static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_invert(matrix_float2x2 __x) __SIMD_AVAILABILITY__;
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_invert(matrix_float3x3 __x) __SIMD_AVAILABILITY__;
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_invert(matrix_float4x4 __x) __SIMD_AVAILABILITY__;
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_invert(matrix_double2x2 __x) __SIMD_AVAILABILITY__;
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_invert(matrix_double3x3 __x) __SIMD_AVAILABILITY__;
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_invert(matrix_double4x4 __x) __SIMD_AVAILABILITY__;

static vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x2 __x, vector_float2 __y);
static vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x2 __x, vector_float3 __y);
static vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x2 __x, vector_float4 __y);
static vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x3 __x, vector_float2 __y);
static vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x3 __x, vector_float3 __y);
static vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x3 __x, vector_float4 __y);
static vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x4 __x, vector_float2 __y);
static vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x4 __x, vector_float3 __y);
static vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x4 __x, vector_float4 __y);
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x2 __x, vector_double2 __y);
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x2 __x, vector_double3 __y);
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x2 __x, vector_double4 __y);
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x3 __x, vector_double2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x3 __x, vector_double3 __y);
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x3 __x, vector_double4 __y);
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x4 __x, vector_double2 __y);
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x4 __x, vector_double3 __y);
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x4 __x, vector_double4 __y);
static vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float2 __x, matrix_float2x2 __y);
static vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float2 __x, matrix_float3x2 __y);
static vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float2 __x, matrix_float4x2 __y);
static vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float3 __x, matrix_float2x3 __y);
static vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float3 __x, matrix_float3x3 __y);
static vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float3 __x, matrix_float4x3 __y);
static vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float4 __x, matrix_float2x4 __y);
static vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float4 __x, matrix_float3x4 __y);
static vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_float4 __x, matrix_float4x4 __y);
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double2 __x, matrix_double2x2 __y);
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double2 __x, matrix_double3x2 __y);
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double2 __x, matrix_double4x2 __y);
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double3 __x, matrix_double2x3 __y);
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double3 __x, matrix_double3x3 __y);
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double3 __x, matrix_double4x3 __y);
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double4 __x, matrix_double2x4 __y);
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double4 __x, matrix_double3x4 __y);
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double4 __x, matrix_double4x4 __y);
static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x2 __x, matrix_float2x2 __y);
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x2 __x, matrix_float3x2 __y);
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x2 __x, matrix_float4x2 __y);
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x3 __x, matrix_float2x2 __y);
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x3 __x, matrix_float3x2 __y);
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x3 __x, matrix_float4x2 __y);
static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x4 __x, matrix_float2x2 __y);
static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x4 __x, matrix_float3x2 __y);
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float2x4 __x, matrix_float4x2 __y);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x2 __x, matrix_double2x2 __y);
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x2 __x, matrix_double3x2 __y);
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x2 __x, matrix_double4x2 __y);
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x3 __x, matrix_double2x2 __y);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x3 __x, matrix_double3x2 __y);
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x3 __x, matrix_double4x2 __y);
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x4 __x, matrix_double2x2 __y);
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x4 __x, matrix_double3x2 __y);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x4 __x, matrix_double4x2 __y);
static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x2 __x, matrix_float2x3 __y);
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x2 __x, matrix_float3x3 __y);
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x2 __x, matrix_float4x3 __y);
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x3 __x, matrix_float2x3 __y);
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x3 __x, matrix_float3x3 __y);
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x3 __x, matrix_float4x3 __y);
static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x4 __x, matrix_float2x3 __y);
static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x4 __x, matrix_float3x3 __y);
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float3x4 __x, matrix_float4x3 __y);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x2 __x, matrix_double2x3 __y);
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x2 __x, matrix_double3x3 __y);
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x2 __x, matrix_double4x3 __y);
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x3 __x, matrix_double2x3 __y);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x3 __x, matrix_double3x3 __y);
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x3 __x, matrix_double4x3 __y);
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x4 __x, matrix_double2x3 __y);
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x4 __x, matrix_double3x3 __y);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x4 __x, matrix_double4x3 __y);
static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x2 __x, matrix_float2x4 __y);
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x2 __x, matrix_float3x4 __y);
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x2 __x, matrix_float4x4 __y);
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x3 __x, matrix_float2x4 __y);
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x3 __x, matrix_float3x4 __y);
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x3 __x, matrix_float4x4 __y);
static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x4 __x, matrix_float2x4 __y);
static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x4 __x, matrix_float3x4 __y);
static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_float4x4 __x, matrix_float4x4 __y);
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x2 __x, matrix_double2x4 __y);
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x2 __x, matrix_double3x4 __y);
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x2 __x, matrix_double4x4 __y);
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x3 __x, matrix_double2x4 __y);
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x3 __x, matrix_double3x4 __y);
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x3 __x, matrix_double4x4 __y);
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x4 __x, matrix_double2x4 __y);
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x4 __x, matrix_double3x4 __y);
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x4 __x, matrix_double4x4 __y);

#ifdef __cplusplus
} /* extern "C" */

namespace simd {
    template <typename fptypeNxM> static __SIMD_INLINE__ fptypeNxM operator+(const fptypeNxM x, const fptypeNxM y) { return fptypeNxM(::matrix_linear_combination(1, x, 1, y)); }
    template <typename fptypeNxM> static __SIMD_INLINE__ fptypeNxM operator-(const fptypeNxM x, const fptypeNxM y) { return fptypeNxM(::matrix_linear_combination(1, x,-1, y)); }
    template <typename fptypeNxM> static __SIMD_INLINE__ fptypeNxM& operator+=(fptypeNxM& x, const fptypeNxM y) { x = ::matrix_linear_combination(1, x, 1, y); return x; }
    template <typename fptypeNxM> static __SIMD_INLINE__ fptypeNxM& operator-=(fptypeNxM& x, const fptypeNxM y) { x = ::matrix_linear_combination(1, x,-1, y); return x; }

    static __SIMD_INLINE__ float2x2 transpose(const float2x2 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ float2x3 transpose(const float3x2 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ float2x4 transpose(const float4x2 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ float3x2 transpose(const float2x3 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ float3x3 transpose(const float3x3 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ float3x4 transpose(const float4x3 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ float4x2 transpose(const float2x4 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ float4x3 transpose(const float3x4 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ float4x4 transpose(const float4x4 x) { return ::matrix_transpose(x); }

    static __SIMD_INLINE__ float determinant(const float2x2 x) { return ::matrix_determinant(x); }
    static __SIMD_INLINE__ float determinant(const float3x3 x) { return ::matrix_determinant(x); }
    static __SIMD_INLINE__ float determinant(const float4x4 x) { return ::matrix_determinant(x); }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"
    static __SIMD_INLINE__ float2x2 inverse(const float2x2 x) __SIMD_AVAILABILITY__ { return ::matrix_invert(x); }
    static __SIMD_INLINE__ float3x3 inverse(const float3x3 x) __SIMD_AVAILABILITY__ { return ::matrix_invert(x); }
    static __SIMD_INLINE__ float4x4 inverse(const float4x4 x) __SIMD_AVAILABILITY__ { return ::matrix_invert(x); }
#pragma clang diagnostic pop

    static __SIMD_INLINE__ float2x2 operator*(const float a, const float2x2 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float2x3 operator*(const float a, const float2x3 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float2x4 operator*(const float a, const float2x4 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float3x2 operator*(const float a, const float3x2 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float3x3 operator*(const float a, const float3x3 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float3x4 operator*(const float a, const float3x4 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float4x2 operator*(const float a, const float4x2 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float4x3 operator*(const float a, const float4x3 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float4x4 operator*(const float a, const float4x4 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float2x2 operator*(const float2x2 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float2x3 operator*(const float2x3 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float2x4 operator*(const float2x4 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float3x2 operator*(const float3x2 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float3x3 operator*(const float3x3 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float3x4 operator*(const float3x4 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float4x2 operator*(const float4x2 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float4x3 operator*(const float4x3 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float4x4 operator*(const float4x4 x, const float a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ float2x2& operator*=(float2x2& x, const float a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ float2x3& operator*=(float2x3& x, const float a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ float2x4& operator*=(float2x4& x, const float a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ float3x2& operator*=(float3x2& x, const float a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ float3x3& operator*=(float3x3& x, const float a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ float3x4& operator*=(float3x4& x, const float a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ float4x2& operator*=(float4x2& x, const float a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ float4x3& operator*=(float4x3& x, const float a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ float4x4& operator*=(float4x4& x, const float a) { x = ::matrix_scale(a, x); return x; }

    static __SIMD_INLINE__ float2 operator*(const float2 x, const float2x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3 operator*(const float2 x, const float3x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4 operator*(const float2 x, const float4x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2 operator*(const float3 x, const float2x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3 operator*(const float3 x, const float3x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4 operator*(const float3 x, const float4x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2 operator*(const float4 x, const float2x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3 operator*(const float4 x, const float3x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4 operator*(const float4 x, const float4x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2 operator*(const float2x2 x, const float2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2 operator*(const float3x2 x, const float3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2 operator*(const float4x2 x, const float4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3 operator*(const float2x3 x, const float2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3 operator*(const float3x3 x, const float3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3 operator*(const float4x3 x, const float4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4 operator*(const float2x4 x, const float2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4 operator*(const float3x4 x, const float3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4 operator*(const float4x4 x, const float4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2& operator*=(float2& x, const float2x2 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float3& operator*=(float3& x, const float3x3 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float4& operator*=(float4& x, const float4x4 y) { x = ::matrix_multiply(x, y); return x; }

    static __SIMD_INLINE__ float2x2 operator*(const float2x2 x, const float2x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x2 operator*(const float2x2 x, const float3x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x2 operator*(const float2x2 x, const float4x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x3 operator*(const float2x3 x, const float2x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x3 operator*(const float2x3 x, const float3x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x3 operator*(const float2x3 x, const float4x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x4 operator*(const float2x4 x, const float2x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x4 operator*(const float2x4 x, const float3x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x4 operator*(const float2x4 x, const float4x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x2 operator*(const float3x2 x, const float2x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x2 operator*(const float3x2 x, const float3x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x2 operator*(const float3x2 x, const float4x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x3 operator*(const float3x3 x, const float2x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x3 operator*(const float3x3 x, const float3x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x3 operator*(const float3x3 x, const float4x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x4 operator*(const float3x4 x, const float2x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x4 operator*(const float3x4 x, const float3x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x4 operator*(const float3x4 x, const float4x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x2 operator*(const float4x2 x, const float2x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x2 operator*(const float4x2 x, const float3x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x2 operator*(const float4x2 x, const float4x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x3 operator*(const float4x3 x, const float2x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x3 operator*(const float4x3 x, const float3x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x3 operator*(const float4x3 x, const float4x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x4 operator*(const float4x4 x, const float2x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float3x4 operator*(const float4x4 x, const float3x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float4x4 operator*(const float4x4 x, const float4x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ float2x2& operator*=(float2x2& x, const float2x2 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float2x3& operator*=(float2x3& x, const float2x2 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float2x4& operator*=(float2x4& x, const float2x2 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float3x2& operator*=(float3x2& x, const float3x3 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float3x3& operator*=(float3x3& x, const float3x3 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float3x4& operator*=(float3x4& x, const float3x3 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float4x2& operator*=(float4x2& x, const float4x4 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float4x3& operator*=(float4x3& x, const float4x4 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ float4x4& operator*=(float4x4& x, const float4x4 y) { x = ::matrix_multiply(x, y); return x; }

    static __SIMD_INLINE__ double2x2 transpose(const double2x2 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ double2x3 transpose(const double3x2 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ double2x4 transpose(const double4x2 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ double3x2 transpose(const double2x3 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ double3x3 transpose(const double3x3 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ double3x4 transpose(const double4x3 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ double4x2 transpose(const double2x4 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ double4x3 transpose(const double3x4 x) { return ::matrix_transpose(x); }
    static __SIMD_INLINE__ double4x4 transpose(const double4x4 x) { return ::matrix_transpose(x); }

    static __SIMD_INLINE__ double determinant(const double2x2 x) { return ::matrix_determinant(x); }
    static __SIMD_INLINE__ double determinant(const double3x3 x) { return ::matrix_determinant(x); }
    static __SIMD_INLINE__ double determinant(const double4x4 x) { return ::matrix_determinant(x); }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"
    static __SIMD_INLINE__ double2x2 inverse(const double2x2 x) __SIMD_AVAILABILITY__ { return ::matrix_invert(x); }
    static __SIMD_INLINE__ double3x3 inverse(const double3x3 x) __SIMD_AVAILABILITY__ { return ::matrix_invert(x); }
    static __SIMD_INLINE__ double4x4 inverse(const double4x4 x) __SIMD_AVAILABILITY__ { return ::matrix_invert(x); }
#pragma clang diagnostic pop

    static __SIMD_INLINE__ double2x2 operator*(const double a, const double2x2 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double2x3 operator*(const double a, const double2x3 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double2x4 operator*(const double a, const double2x4 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double3x2 operator*(const double a, const double3x2 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double3x3 operator*(const double a, const double3x3 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double3x4 operator*(const double a, const double3x4 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double4x2 operator*(const double a, const double4x2 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double4x3 operator*(const double a, const double4x3 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double4x4 operator*(const double a, const double4x4 x) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double2x2 operator*(const double2x2 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double2x3 operator*(const double2x3 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double2x4 operator*(const double2x4 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double3x2 operator*(const double3x2 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double3x3 operator*(const double3x3 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double3x4 operator*(const double3x4 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double4x2 operator*(const double4x2 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double4x3 operator*(const double4x3 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double4x4 operator*(const double4x4 x, const double a) { return ::matrix_scale(a, x); }
    static __SIMD_INLINE__ double2x2& operator*=(double2x2& x, const double a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ double2x3& operator*=(double2x3& x, const double a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ double2x4& operator*=(double2x4& x, const double a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ double3x2& operator*=(double3x2& x, const double a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ double3x3& operator*=(double3x3& x, const double a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ double3x4& operator*=(double3x4& x, const double a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ double4x2& operator*=(double4x2& x, const double a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ double4x3& operator*=(double4x3& x, const double a) { x = ::matrix_scale(a, x); return x; }
    static __SIMD_INLINE__ double4x4& operator*=(double4x4& x, const double a) { x = ::matrix_scale(a, x); return x; }

    static __SIMD_INLINE__ double2 operator*(const double2 x, const double2x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3 operator*(const double2 x, const double3x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4 operator*(const double2 x, const double4x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2 operator*(const double3 x, const double2x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3 operator*(const double3 x, const double3x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4 operator*(const double3 x, const double4x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2 operator*(const double4 x, const double2x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3 operator*(const double4 x, const double3x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4 operator*(const double4 x, const double4x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2 operator*(const double2x2 x, const double2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2 operator*(const double3x2 x, const double3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2 operator*(const double4x2 x, const double4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3 operator*(const double2x3 x, const double2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3 operator*(const double3x3 x, const double3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3 operator*(const double4x3 x, const double4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4 operator*(const double2x4 x, const double2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4 operator*(const double3x4 x, const double3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4 operator*(const double4x4 x, const double4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2& operator*=(double2& x, const double2x2 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double3& operator*=(double3& x, const double3x3 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double4& operator*=(double4& x, const double4x4 y) { x = ::matrix_multiply(x, y); return x; }

    static __SIMD_INLINE__ double2x2 operator*(const double2x2 x, const double2x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x2 operator*(const double2x2 x, const double3x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x2 operator*(const double2x2 x, const double4x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x3 operator*(const double2x3 x, const double2x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x3 operator*(const double2x3 x, const double3x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x3 operator*(const double2x3 x, const double4x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x4 operator*(const double2x4 x, const double2x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x4 operator*(const double2x4 x, const double3x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x4 operator*(const double2x4 x, const double4x2 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x2 operator*(const double3x2 x, const double2x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x2 operator*(const double3x2 x, const double3x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x2 operator*(const double3x2 x, const double4x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x3 operator*(const double3x3 x, const double2x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x3 operator*(const double3x3 x, const double3x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x3 operator*(const double3x3 x, const double4x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x4 operator*(const double3x4 x, const double2x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x4 operator*(const double3x4 x, const double3x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x4 operator*(const double3x4 x, const double4x3 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x2 operator*(const double4x2 x, const double2x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x2 operator*(const double4x2 x, const double3x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x2 operator*(const double4x2 x, const double4x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x3 operator*(const double4x3 x, const double2x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x3 operator*(const double4x3 x, const double3x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x3 operator*(const double4x3 x, const double4x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x4 operator*(const double4x4 x, const double2x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double3x4 operator*(const double4x4 x, const double3x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double4x4 operator*(const double4x4 x, const double4x4 y) { return ::matrix_multiply(x, y); }
    static __SIMD_INLINE__ double2x2& operator*=(double2x2& x, const double2x2 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double2x3& operator*=(double2x3& x, const double2x2 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double2x4& operator*=(double2x4& x, const double2x2 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double3x2& operator*=(double3x2& x, const double3x3 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double3x3& operator*=(double3x3& x, const double3x3 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double3x4& operator*=(double3x4& x, const double3x3 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double4x2& operator*=(double4x2& x, const double4x4 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double4x3& operator*=(double4x3& x, const double4x4 y) { x = ::matrix_multiply(x, y); return x; }
    static __SIMD_INLINE__ double4x4& operator*=(double4x4& x, const double4x4 y) { x = ::matrix_multiply(x, y); return x; }
}

extern "C" {
#endif /* __cplusplus */

#pragma mark - Implementation

static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_float2  __x) {  matrix_float2x2 __r = { .columns[0] = {__x.x,0}, .columns[1] = {0,__x.y} }; return __r; }
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_double2 __x) { matrix_double2x2 __r = { .columns[0] = {__x.x,0}, .columns[1] = {0,__x.y} }; return __r; }
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_float3  __x) {  matrix_float3x3 __r = { .columns[0] = {__x.x,0,0}, .columns[1] = {0,__x.y,0}, .columns[2] = {0,0,__x.z} }; return __r; }
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_double3 __x) { matrix_double3x3 __r = { .columns[0] = {__x.x,0,0}, .columns[1] = {0,__x.y,0}, .columns[2] = {0,0,__x.z} }; return __r; }
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_float4  __x) {  matrix_float4x4 __r = { .columns[0] = {__x.x,0,0,0}, .columns[1] = {0,__x.y,0,0}, .columns[2] = {0,0,__x.z,0}, .columns[3] = {0,0,0,__x.w} }; return __r; }
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_from_diagonal(vector_double4 __x) { matrix_double4x4 __r = { .columns[0] = {__x.x,0,0,0}, .columns[1] = {0,__x.y,0,0}, .columns[2] = {0,0,__x.z,0}, .columns[3] = {0,0,0,__x.w} }; return __r; }

static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float2  col0, vector_float2  col1) {  matrix_float2x2 __r = { .columns[0] = col0, .columns[1] = col1 }; return __r; }
static  matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float3  col0, vector_float3  col1) {  matrix_float2x3 __r = { .columns[0] = col0, .columns[1] = col1 }; return __r; }
static  matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float4  col0, vector_float4  col1) {  matrix_float2x4 __r = { .columns[0] = col0, .columns[1] = col1 }; return __r; }
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double2 col0, vector_double2 col1) { matrix_double2x2 __r = { .columns[0] = col0, .columns[1] = col1 }; return __r; }
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double3 col0, vector_double3 col1) { matrix_double2x3 __r = { .columns[0] = col0, .columns[1] = col1 }; return __r; }
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double4 col0, vector_double4 col1) { matrix_double2x4 __r = { .columns[0] = col0, .columns[1] = col1 }; return __r; }
static  matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float2  col0, vector_float2  col1, vector_float2  col2) {  matrix_float3x2 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2 }; return __r; }
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float3  col0, vector_float3  col1, vector_float3  col2) {  matrix_float3x3 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2 }; return __r; }
static  matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float4  col0, vector_float4  col1, vector_float4  col2) {  matrix_float3x4 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2 }; return __r; }
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double2 col0, vector_double2 col1, vector_double2 col2) { matrix_double3x2 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2 }; return __r; }
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double3 col0, vector_double3 col1, vector_double3 col2) { matrix_double3x3 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2 }; return __r; }
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double4 col0, vector_double4 col1, vector_double4 col2) { matrix_double3x4 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2 }; return __r; }
static  matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float2  col0, vector_float2  col1, vector_float2  col2, vector_float2  col3) {  matrix_float4x2 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2, .columns[3] = col3 }; return __r; }
static  matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float3  col0, vector_float3  col1, vector_float3  col2, vector_float3  col3) {  matrix_float4x3 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2, .columns[3] = col3 }; return __r; }
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_float4  col0, vector_float4  col1, vector_float4  col2, vector_float4  col3) {  matrix_float4x4 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2, .columns[3] = col3 }; return __r; }
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double2 col0, vector_double2 col1, vector_double2 col2, vector_double2 col3) { matrix_double4x2 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2, .columns[3] = col3 }; return __r; }
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double3 col0, vector_double3 col1, vector_double3 col2, vector_double3 col3) { matrix_double4x3 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2, .columns[3] = col3 }; return __r; }
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_from_columns(vector_double4 col0, vector_double4 col1, vector_double4 col2, vector_double4 col3) { matrix_double4x4 __r = { .columns[0] = col0, .columns[1] = col1, .columns[2] = col2, .columns[3] = col3 }; return __r; }

static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float2  row0, vector_float2  row1) { return matrix_transpose(matrix_from_columns(row0, row1)); }
static  matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float3  row0, vector_float3  row1) { return matrix_transpose(matrix_from_columns(row0, row1)); }
static  matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float4  row0, vector_float4  row1) { return matrix_transpose(matrix_from_columns(row0, row1)); }
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double2 row0, vector_double2 row1) { return matrix_transpose(matrix_from_columns(row0, row1)); }
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double3 row0, vector_double3 row1) { return matrix_transpose(matrix_from_columns(row0, row1)); }
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double4 row0, vector_double4 row1) { return matrix_transpose(matrix_from_columns(row0, row1)); }
static  matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float2  row0, vector_float2  row1, vector_float2  row2) { return matrix_transpose(matrix_from_columns(row0, row1, row2)); }
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float3  row0, vector_float3  row1, vector_float3  row2) { return matrix_transpose(matrix_from_columns(row0, row1, row2)); }
static  matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float4  row0, vector_float4  row1, vector_float4  row2) { return matrix_transpose(matrix_from_columns(row0, row1, row2)); }
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double2 row0, vector_double2 row1, vector_double2 row2) { return matrix_transpose(matrix_from_columns(row0, row1, row2)); }
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double3 row0, vector_double3 row1, vector_double3 row2) { return matrix_transpose(matrix_from_columns(row0, row1, row2)); }
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double4 row0, vector_double4 row1, vector_double4 row2) { return matrix_transpose(matrix_from_columns(row0, row1, row2)); }
static  matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float2  row0, vector_float2  row1, vector_float2  row2, vector_float2  row3) { return matrix_transpose(matrix_from_columns(row0, row1, row2, row3)); }
static  matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float3  row0, vector_float3  row1, vector_float3  row2, vector_float3  row3) { return matrix_transpose(matrix_from_columns(row0, row1, row2, row3)); }
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_float4  row0, vector_float4  row1, vector_float4  row2, vector_float4  row3) { return matrix_transpose(matrix_from_columns(row0, row1, row2, row3)); }
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double2 row0, vector_double2 row1, vector_double2 row2, vector_double2 row3) { return matrix_transpose(matrix_from_columns(row0, row1, row2, row3)); }
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double3 row0, vector_double3 row1, vector_double3 row2, vector_double3 row3) { return matrix_transpose(matrix_from_columns(row0, row1, row2, row3)); }
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_from_rows(vector_double4 row0, vector_double4 row1, vector_double4 row2, vector_double4 row3) { return matrix_transpose(matrix_from_columns(row0, row1, row2, row3)); }

static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float2x2 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; return __x; }
static  matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float3x2 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; return __x; }
static  matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float4x2 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; __x.columns[3] *= __a; return __x; }
static  matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float2x3 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; return __x; }
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float3x3 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; return __x; }
static  matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float4x3 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; __x.columns[3] *= __a; return __x; }
static  matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float2x4 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; return __x; }
static  matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float3x4 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; return __x; }
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_scale(float  __a,  matrix_float4x4 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; __x.columns[3] *= __a; return __x; }
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double2x2 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; return __x; }
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double3x2 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; return __x; }
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double4x2 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; __x.columns[3] *= __a; return __x; }
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double2x3 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; return __x; }
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double3x3 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; return __x; }
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double4x3 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; __x.columns[3] *= __a; return __x; }
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double2x4 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; return __x; }
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double3x4 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; return __x; }
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_scale(double __a, matrix_double4x4 __x) { __x.columns[0] *= __a; __x.columns[1] *= __a; __x.columns[2] *= __a; __x.columns[3] *= __a; return __x; }

static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float2x2 __x, float  __b,  matrix_float2x2 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    return __x;
}
static  matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float3x2 __x, float  __b,  matrix_float3x2 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    return __x;
}
static  matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float4x2 __x, float  __b,  matrix_float4x2 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    __x.columns[3] = __a*__x.columns[3] + __b*__y.columns[3];
    return __x;
}
static  matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float2x3 __x, float  __b,  matrix_float2x3 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    return __x;
}
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float3x3 __x, float  __b,  matrix_float3x3 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    return __x;
}
static  matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float4x3 __x, float  __b,  matrix_float4x3 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    __x.columns[3] = __a*__x.columns[3] + __b*__y.columns[3];
    return __x;
}
static  matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float2x4 __x, float  __b,  matrix_float2x4 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    return __x;
}
static  matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float3x4 __x, float  __b,  matrix_float3x4 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    return __x;
}
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(float  __a,  matrix_float4x4 __x, float  __b,  matrix_float4x4 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    __x.columns[3] = __a*__x.columns[3] + __b*__y.columns[3];
    return __x;
}
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double2x2 __x, double __b, matrix_double2x2 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    return __x;
}
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double3x2 __x, double __b, matrix_double3x2 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    return __x;
}
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double4x2 __x, double __b, matrix_double4x2 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    __x.columns[3] = __a*__x.columns[3] + __b*__y.columns[3];
    return __x;
}
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double2x3 __x, double __b, matrix_double2x3 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    return __x;
}
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double3x3 __x, double __b, matrix_double3x3 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    return __x;
}
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double4x3 __x, double __b, matrix_double4x3 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    __x.columns[3] = __a*__x.columns[3] + __b*__y.columns[3];
    return __x;
}
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double2x4 __x, double __b, matrix_double2x4 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    return __x;
}
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double3x4 __x, double __b, matrix_double3x4 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    return __x;
}
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_linear_combination(double __a, matrix_double4x4 __x, double __b, matrix_double4x4 __y) {
    __x.columns[0] = __a*__x.columns[0] + __b*__y.columns[0];
    __x.columns[1] = __a*__x.columns[1] + __b*__y.columns[1];
    __x.columns[2] = __a*__x.columns[2] + __b*__y.columns[2];
    __x.columns[3] = __a*__x.columns[3] + __b*__y.columns[3];
    return __x;
}

static matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float2x2 __x) {
#if defined __SSE__
    vector_float4 __x0, __x1;
    __x0.xy = __x.columns[0];
    __x1.xy = __x.columns[1];
    vector_float4 __r01 = _mm_unpacklo_ps(__x0, __x1);
    return matrix_from_columns(__r01.lo, __r01.hi);
#else
    return matrix_from_columns((vector_float2){__x.columns[0][0], __x.columns[1][0]},
                               (vector_float2){__x.columns[0][1], __x.columns[1][1]});
#endif
}
    
static matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float2x3 __x) {
#if defined __SSE__
    vector_float4 __x0, __x1;
    __x0.xyz = __x.columns[0];
    __x1.xyz = __x.columns[1];
    vector_float4 __r01 = _mm_unpacklo_ps(__x0, __x1);
    vector_float4 __r2x = _mm_unpackhi_ps(__x0, __x1);
    return matrix_from_columns(__r01.lo, __r01.hi, __r2x.lo);
#else
    return matrix_from_columns((vector_float2){__x.columns[0][0], __x.columns[1][0]},
                               (vector_float2){__x.columns[0][1], __x.columns[1][1]},
                               (vector_float2){__x.columns[0][2], __x.columns[1][2]});
#endif
}
    
static matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float2x4 __x) {
#if defined __SSE__
    vector_float4 __r01 = _mm_unpacklo_ps(__x.columns[0], __x.columns[1]);
    vector_float4 __r23 = _mm_unpackhi_ps(__x.columns[0], __x.columns[1]);
    return matrix_from_columns(__r01.lo, __r01.hi, __r23.lo, __r23.hi);
#else
    return matrix_from_columns((vector_float2){__x.columns[0][0], __x.columns[1][0]},
                               (vector_float2){__x.columns[0][1], __x.columns[1][1]},
                               (vector_float2){__x.columns[0][2], __x.columns[1][2]},
                               (vector_float2){__x.columns[0][3], __x.columns[1][3]});
#endif
}
    
static matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float3x2 __x) {
#if defined __SSE__
    vector_float4 __x0, __x1, __x2;
    __x0.xy = __x.columns[0];
    __x1.xy = __x.columns[1];
    __x2.xy = __x.columns[2];
    vector_float4 __t = _mm_unpacklo_ps(__x0, __x1);
    vector_float4 __r0 = _mm_shuffle_ps(__t,__x2,0xc4);
    vector_float4 __r1 = _mm_shuffle_ps(__t,__x2,0xde);
    return matrix_from_columns(__r0.xyz, __r1.xyz);
#else
    return matrix_from_columns((vector_float3){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0]},
                               (vector_float3){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1]});
#endif
}
    
static matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float3x3 __x) {
#if defined __SSE__
    vector_float4 __x0, __x1, __x2;
    __x0.xyz = __x.columns[0];
    __x1.xyz = __x.columns[1];
    __x2.xyz = __x.columns[2];
    vector_float4 __t0 = _mm_unpacklo_ps(__x0, __x1);
    vector_float4 __t1 = _mm_unpackhi_ps(__x0, __x1);
    vector_float4 __r0 = __t0; __r0.hi = __x2.lo;
    vector_float4 __r1 = _mm_shuffle_ps(__t0, __x2, 0xde);
    vector_float4 __r2 = __x2; __r2.lo = __t1.lo;
    return matrix_from_columns(__r0.xyz, __r1.xyz, __r2.xyz);
#else
    return matrix_from_columns((vector_float3){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0]},
                               (vector_float3){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1]},
                               (vector_float3){__x.columns[0][2], __x.columns[1][2], __x.columns[2][2]});
#endif
}
    
static matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float3x4 __x) {
#if defined __SSE__
    vector_float4 __t0 = _mm_unpacklo_ps(__x.columns[0],__x.columns[1]); /* 00 10 01 11 */
    vector_float4 __t1 = _mm_unpackhi_ps(__x.columns[0],__x.columns[1]); /* 02 12 03 13 */
    vector_float4 __r0 = __t0; __r0.hi = __x.columns[2].lo;
    vector_float4 __r1 = _mm_shuffle_ps(__t0, __x.columns[2], 0xde);
    vector_float4 __r2 = __x.columns[2]; __r2.lo = __t1.lo;
    vector_float4 __r3 = _mm_shuffle_ps(__t1, __x.columns[2], 0xfe);
    return matrix_from_columns(__r0.xyz, __r1.xyz, __r2.xyz, __r3.xyz);
#else
    return matrix_from_columns((vector_float3){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0]},
                               (vector_float3){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1]},
                               (vector_float3){__x.columns[0][2], __x.columns[1][2], __x.columns[2][2]},
                               (vector_float3){__x.columns[0][3], __x.columns[1][3], __x.columns[2][3]});
#endif
}

static matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float4x2 __x) {
#if defined __SSE__
    vector_float4 __x0, __x1, __x2, __x3;
    __x0.xy = __x.columns[0];
    __x1.xy = __x.columns[1];
    __x2.xy = __x.columns[2];
    __x3.xy = __x.columns[3];
    vector_float4 __t0 = _mm_unpacklo_ps(__x0,__x2);
    vector_float4 __t1 = _mm_unpacklo_ps(__x1,__x3);
    vector_float4 __r0 = _mm_unpacklo_ps(__t0,__t1);
    vector_float4 __r1 = _mm_unpackhi_ps(__t0,__t1);
    return matrix_from_columns(__r0,__r1);
#else
    return matrix_from_columns((vector_float4){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0], __x.columns[3][0]},
                               (vector_float4){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1], __x.columns[3][1]});
#endif
}

static matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float4x3 __x) {
#if defined __SSE__
    vector_float4 __x0, __x1, __x2, __x3;
    __x0.xyz = __x.columns[0];
    __x1.xyz = __x.columns[1];
    __x2.xyz = __x.columns[2];
    __x3.xyz = __x.columns[3];
    vector_float4 __t0 = _mm_unpacklo_ps(__x0,__x2);
    vector_float4 __t1 = _mm_unpackhi_ps(__x0,__x2);
    vector_float4 __t2 = _mm_unpacklo_ps(__x1,__x3);
    vector_float4 __t3 = _mm_unpackhi_ps(__x1,__x3);
    vector_float4 __r0 = _mm_unpacklo_ps(__t0,__t2);
    vector_float4 __r1 = _mm_unpackhi_ps(__t0,__t2);
    vector_float4 __r2 = _mm_unpacklo_ps(__t1,__t3);
    return matrix_from_columns(__r0,__r1,__r2);
#else
    return matrix_from_columns((vector_float4){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0], __x.columns[3][0]},
                               (vector_float4){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1], __x.columns[3][1]},
                               (vector_float4){__x.columns[0][2], __x.columns[1][2], __x.columns[2][2], __x.columns[3][2]});
#endif
}

static matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_float4x4 __x) {
#if defined __SSE__
    vector_float4 __t0 = _mm_unpacklo_ps(__x.columns[0],__x.columns[2]);
    vector_float4 __t1 = _mm_unpackhi_ps(__x.columns[0],__x.columns[2]);
    vector_float4 __t2 = _mm_unpacklo_ps(__x.columns[1],__x.columns[3]);
    vector_float4 __t3 = _mm_unpackhi_ps(__x.columns[1],__x.columns[3]);
    vector_float4 __r0 = _mm_unpacklo_ps(__t0,__t2);
    vector_float4 __r1 = _mm_unpackhi_ps(__t0,__t2);
    vector_float4 __r2 = _mm_unpacklo_ps(__t1,__t3);
    vector_float4 __r3 = _mm_unpackhi_ps(__t1,__t3);
    return matrix_from_columns(__r0,__r1,__r2,__r3);
#else
    return matrix_from_columns((vector_float4){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0], __x.columns[3][0]},
                               (vector_float4){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1], __x.columns[3][1]},
                               (vector_float4){__x.columns[0][2], __x.columns[1][2], __x.columns[2][2], __x.columns[3][2]},
                               (vector_float4){__x.columns[0][3], __x.columns[1][3], __x.columns[2][3], __x.columns[3][3]});
#endif
}

static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double2x2 __x) {
    return matrix_from_columns((vector_double2){__x.columns[0][0], __x.columns[1][0]},
                               (vector_double2){__x.columns[0][1], __x.columns[1][1]});
}

static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double2x3 __x) {
    return matrix_from_columns((vector_double2){__x.columns[0][0], __x.columns[1][0]},
                               (vector_double2){__x.columns[0][1], __x.columns[1][1]},
                               (vector_double2){__x.columns[0][2], __x.columns[1][2]});
}

static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double2x4 __x) {
    return matrix_from_columns((vector_double2){__x.columns[0][0], __x.columns[1][0]},
                               (vector_double2){__x.columns[0][1], __x.columns[1][1]},
                               (vector_double2){__x.columns[0][2], __x.columns[1][2]},
                               (vector_double2){__x.columns[0][3], __x.columns[1][3]});
}

static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double3x2 __x) {
    return matrix_from_columns((vector_double3){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0]},
                               (vector_double3){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1]});
}

static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double3x3 __x) {
    return matrix_from_columns((vector_double3){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0]},
                               (vector_double3){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1]},
                               (vector_double3){__x.columns[0][2], __x.columns[1][2], __x.columns[2][2]});
}

static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double3x4 __x) {
    return matrix_from_columns((vector_double3){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0]},
                               (vector_double3){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1]},
                               (vector_double3){__x.columns[0][2], __x.columns[1][2], __x.columns[2][2]},
                               (vector_double3){__x.columns[0][3], __x.columns[1][3], __x.columns[2][3]});
}

static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double4x2 __x) {
    return matrix_from_columns((vector_double4){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0], __x.columns[3][0]},
                               (vector_double4){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1], __x.columns[3][1]});
}

static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double4x3 __x) {
    return matrix_from_columns((vector_double4){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0], __x.columns[3][0]},
                               (vector_double4){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1], __x.columns[3][1]},
                               (vector_double4){__x.columns[0][2], __x.columns[1][2], __x.columns[2][2], __x.columns[3][2]});
}

static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_transpose(matrix_double4x4 __x) {
    return matrix_from_columns((vector_double4){__x.columns[0][0], __x.columns[1][0], __x.columns[2][0], __x.columns[3][0]},
                               (vector_double4){__x.columns[0][1], __x.columns[1][1], __x.columns[2][1], __x.columns[3][1]},
                               (vector_double4){__x.columns[0][2], __x.columns[1][2], __x.columns[2][2], __x.columns[3][2]},
                               (vector_double4){__x.columns[0][3], __x.columns[1][3], __x.columns[2][3], __x.columns[3][3]});
}

static  vector_float3 __SIMD_ATTRIBUTES__ __rotate1( vector_float3 __x) { return __builtin_shufflevector(__x,__x,1,2,0); }
static  vector_float3 __SIMD_ATTRIBUTES__ __rotate2( vector_float3 __x) { return __builtin_shufflevector(__x,__x,2,0,1); }
static  vector_float4 __SIMD_ATTRIBUTES__ __rotate1( vector_float4 __x) { return __builtin_shufflevector(__x,__x,1,2,3,0); }
static  vector_float4 __SIMD_ATTRIBUTES__ __rotate2( vector_float4 __x) { return __builtin_shufflevector(__x,__x,2,3,0,1); }
static  vector_float4 __SIMD_ATTRIBUTES__ __rotate3( vector_float4 __x) { return __builtin_shufflevector(__x,__x,3,0,1,2); }
static vector_double3 __SIMD_ATTRIBUTES__ __rotate1(vector_double3 __x) { return __builtin_shufflevector(__x,__x,1,2,0); }
static vector_double3 __SIMD_ATTRIBUTES__ __rotate2(vector_double3 __x) { return __builtin_shufflevector(__x,__x,2,0,1); }
static vector_double4 __SIMD_ATTRIBUTES__ __rotate1(vector_double4 __x) { return __builtin_shufflevector(__x,__x,1,2,3,0); }
static vector_double4 __SIMD_ATTRIBUTES__ __rotate2(vector_double4 __x) { return __builtin_shufflevector(__x,__x,2,3,0,1); }
static vector_double4 __SIMD_ATTRIBUTES__ __rotate3(vector_double4 __x) { return __builtin_shufflevector(__x,__x,3,0,1,2); }

static  float __SIMD_ATTRIBUTES__ matrix_determinant( matrix_float2x2 __x) { return __x.columns[0][0]*__x.columns[1][1] - __x.columns[0][1]*__x.columns[1][0]; }
static double __SIMD_ATTRIBUTES__ matrix_determinant(matrix_double2x2 __x) { return __x.columns[0][0]*__x.columns[1][1] - __x.columns[0][1]*__x.columns[1][0]; }
static  float __SIMD_ATTRIBUTES__ matrix_determinant( matrix_float3x3 __x) { return __horizontal_sum(__x.columns[0]*(__rotate1(__x.columns[1])*__rotate2(__x.columns[2]) - __rotate2(__x.columns[1])*__rotate1(__x.columns[2]))); }
static double __SIMD_ATTRIBUTES__ matrix_determinant(matrix_double3x3 __x) { return __horizontal_sum(__x.columns[0]*(__rotate1(__x.columns[1])*__rotate2(__x.columns[2]) - __rotate2(__x.columns[1])*__rotate1(__x.columns[2]))); }
static  float __SIMD_ATTRIBUTES__ matrix_determinant( matrix_float4x4 __x) {
    return __horizontal_sum(__x.columns[0]*(__rotate1(__x.columns[1])*(__rotate2(__x.columns[2])*__rotate3(__x.columns[3])-__rotate3(__x.columns[2])*__rotate2(__x.columns[3])) +
                                            __rotate2(__x.columns[1])*(__rotate3(__x.columns[2])*__rotate1(__x.columns[3])-__rotate1(__x.columns[2])*__rotate3(__x.columns[3])) +
                                            __rotate3(__x.columns[1])*(__rotate1(__x.columns[2])*__rotate2(__x.columns[3])-__rotate2(__x.columns[2])*__rotate1(__x.columns[3]))));
}
static double __SIMD_ATTRIBUTES__ matrix_determinant(matrix_double4x4 __x) {
    return __horizontal_sum(__x.columns[0]*(__rotate1(__x.columns[1])*(__rotate2(__x.columns[2])*__rotate3(__x.columns[3])-__rotate3(__x.columns[2])*__rotate2(__x.columns[3])) +
                                            __rotate2(__x.columns[1])*(__rotate3(__x.columns[2])*__rotate1(__x.columns[3])-__rotate1(__x.columns[2])*__rotate3(__x.columns[3])) +
                                            __rotate3(__x.columns[1])*(__rotate1(__x.columns[2])*__rotate2(__x.columns[3])-__rotate2(__x.columns[2])*__rotate1(__x.columns[3]))));
}

static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_invert( matrix_float2x2 __x) { return __invert_f2(__x); }
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_invert( matrix_float3x3 __x) { return __invert_f3(__x); }
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_invert( matrix_float4x4 __x) { return __invert_f4(__x); }
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_invert(matrix_double2x2 __x) { return __invert_d2(__x); }
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_invert(matrix_double3x3 __x) { return __invert_d3(__x); }
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_invert(matrix_double4x4 __x) { return __invert_d4(__x); }

static  vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x2 __x,  vector_float2 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1]; }
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x2 __x, vector_double2 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1]; }
static  vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x3 __x,  vector_float2 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1]; }
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x3 __x, vector_double2 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1]; }
static  vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x4 __x,  vector_float2 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1]; }
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x4 __x, vector_double2 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1]; }
static  vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x2 __x,  vector_float3 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2]; }
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x2 __x, vector_double3 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2]; }
static  vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x3 __x,  vector_float3 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2]; }
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x3 __x, vector_double3 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2]; }
static  vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x4 __x,  vector_float3 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2]; }
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x4 __x, vector_double3 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2]; }
static  vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x2 __x,  vector_float4 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2] + __x.columns[3]*__y[3]; }
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x2 __x, vector_double4 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2] + __x.columns[3]*__y[3]; }
static  vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x3 __x,  vector_float4 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2] + __x.columns[3]*__y[3]; }
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x3 __x, vector_double4 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2] + __x.columns[3]*__y[3]; }
static  vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x4 __x,  vector_float4 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2] + __x.columns[3]*__y[3]; }
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x4 __x, vector_double4 __y) { return __x.columns[0]*__y[0] + __x.columns[1]*__y[1] + __x.columns[2]*__y[2] + __x.columns[3]*__y[3]; }

static  vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float2 __x,  matrix_float2x2 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static  vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float2 __x,  matrix_float3x2 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static  vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float2 __x,  matrix_float4x2 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static  vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float3 __x,  matrix_float2x3 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static  vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float3 __x,  matrix_float3x3 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static  vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float3 __x,  matrix_float4x3 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static  vector_float2 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float4 __x,  matrix_float2x4 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static  vector_float3 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float4 __x,  matrix_float3x4 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static  vector_float4 __SIMD_ATTRIBUTES__ matrix_multiply( vector_float4 __x,  matrix_float4x4 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double2 __x, matrix_double2x2 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double2 __x, matrix_double3x2 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double2 __x, matrix_double4x2 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double3 __x, matrix_double2x3 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double3 __x, matrix_double3x3 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double3 __x, matrix_double4x3 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double2 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double4 __x, matrix_double2x4 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double3 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double4 __x, matrix_double3x4 __y) { return matrix_multiply(matrix_transpose(__y), __x); }
static vector_double4 __SIMD_ATTRIBUTES__ matrix_multiply(vector_double4 __x, matrix_double4x4 __y) { return matrix_multiply(matrix_transpose(__y), __x); }

static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x2 __x,  matrix_float2x2 __y) {  matrix_float2x2 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x2 __x, matrix_double2x2 __y) { matrix_double2x2 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x3 __x,  matrix_float2x2 __y) {  matrix_float2x3 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x3 __x, matrix_double2x2 __y) { matrix_double2x3 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x4 __x,  matrix_float2x2 __y) {  matrix_float2x4 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x4 __x, matrix_double2x2 __y) { matrix_double2x4 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x2 __x,  matrix_float2x3 __y) {  matrix_float2x2 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x2 __x, matrix_double2x3 __y) { matrix_double2x2 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x3 __x,  matrix_float2x3 __y) {  matrix_float2x3 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x3 __x, matrix_double2x3 __y) { matrix_double2x3 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x4 __x,  matrix_float2x3 __y) {  matrix_float2x4 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x4 __x, matrix_double2x3 __y) { matrix_double2x4 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float2x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x2 __x,  matrix_float2x4 __y) {  matrix_float2x2 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x2 __x, matrix_double2x4 __y) { matrix_double2x2 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float2x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x3 __x,  matrix_float2x4 __y) {  matrix_float2x3 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x3 __x, matrix_double2x4 __y) { matrix_double2x3 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float2x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x4 __x,  matrix_float2x4 __y) {  matrix_float2x4 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double2x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x4 __x, matrix_double2x4 __y) { matrix_double2x4 __r; for (int i=0; i<2; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }

static  matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x2 __x,  matrix_float3x2 __y) {  matrix_float3x2 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x2 __x, matrix_double3x2 __y) { matrix_double3x2 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x3 __x,  matrix_float3x2 __y) {  matrix_float3x3 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x3 __x, matrix_double3x2 __y) { matrix_double3x3 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x4 __x,  matrix_float3x2 __y) {  matrix_float3x4 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x4 __x, matrix_double3x2 __y) { matrix_double3x4 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x2 __x,  matrix_float3x3 __y) {  matrix_float3x2 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x2 __x, matrix_double3x3 __y) { matrix_double3x2 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x3 __x,  matrix_float3x3 __y) {  matrix_float3x3 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x3 __x, matrix_double3x3 __y) { matrix_double3x3 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x4 __x,  matrix_float3x3 __y) {  matrix_float3x4 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x4 __x, matrix_double3x3 __y) { matrix_double3x4 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float3x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x2 __x,  matrix_float3x4 __y) {  matrix_float3x2 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x2 __x, matrix_double3x4 __y) { matrix_double3x2 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float3x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x3 __x,  matrix_float3x4 __y) {  matrix_float3x3 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x3 __x, matrix_double3x4 __y) { matrix_double3x3 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float3x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x4 __x,  matrix_float3x4 __y) {  matrix_float3x4 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double3x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x4 __x, matrix_double3x4 __y) { matrix_double3x4 __r; for (int i=0; i<3; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }

static  matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x2 __x,  matrix_float4x2 __y) {  matrix_float4x2 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x2 __x, matrix_double4x2 __y) { matrix_double4x2 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x3 __x,  matrix_float4x2 __y) {  matrix_float4x3 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x3 __x, matrix_double4x2 __y) { matrix_double4x3 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float2x4 __x,  matrix_float4x2 __y) {  matrix_float4x4 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double2x4 __x, matrix_double4x2 __y) { matrix_double4x4 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x2 __x,  matrix_float4x3 __y) {  matrix_float4x2 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x2 __x, matrix_double4x3 __y) { matrix_double4x2 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x3 __x,  matrix_float4x3 __y) {  matrix_float4x3 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x3 __x, matrix_double4x3 __y) { matrix_double4x3 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float3x4 __x,  matrix_float4x3 __y) {  matrix_float4x4 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double3x4 __x, matrix_double4x3 __y) { matrix_double4x4 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float4x2 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x2 __x,  matrix_float4x4 __y) {  matrix_float4x2 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x2 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x2 __x, matrix_double4x4 __y) { matrix_double4x2 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float4x3 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x3 __x,  matrix_float4x4 __y) {  matrix_float4x3 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x3 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x3 __x, matrix_double4x4 __y) { matrix_double4x3 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static  matrix_float4x4 __SIMD_ATTRIBUTES__ matrix_multiply( matrix_float4x4 __x,  matrix_float4x4 __y) {  matrix_float4x4 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }
static matrix_double4x4 __SIMD_ATTRIBUTES__ matrix_multiply(matrix_double4x4 __x, matrix_double4x4 __y) { matrix_double4x4 __r; for (int i=0; i<4; ++i) __r.columns[i] = matrix_multiply(__x, __y.columns[i]); return __r; }

#ifdef __cplusplus
}
#endif
#endif /* __SIMD_REQUIRED_COMPILER_FEATURES__ */
#endif /* __SIMD_HEADER__ */
