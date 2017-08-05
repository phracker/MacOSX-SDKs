/*  Copyright (c) 2014 Apple, Inc. All rights reserved.                       */
 
#ifndef __SIMD_EXTERN_HEADER__
#define __SIMD_EXTERN_HEADER__

#include <simd/internal.h>
#if __SIMD_REQUIRED_COMPILER_FEATURES__
#include <simd/vector_types.h>
#include <simd/matrix_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - geometry
#if SIMD_LIBRARY_VERSION >= 2
extern float _simd_orient_vf2(vector_float2, vector_float2);
extern float _simd_orient_pf2(vector_float2, vector_float2, vector_float2);
extern float _simd_incircle_pf2(vector_float2, vector_float2, vector_float2, vector_float2);

extern float _simd_orient_vf3(vector_float3, vector_float3, vector_float3);
extern float _simd_orient_pf3(vector_float3, vector_float3, vector_float3, vector_float3);
extern float _simd_insphere_pf3(vector_float3, vector_float3, vector_float3, vector_float3, vector_float3);
  
extern double _simd_orient_vd2(vector_double2, vector_double2);
extern double _simd_orient_pd2(vector_double2, vector_double2, vector_double2);
extern double _simd_incircle_pd2(vector_double2, vector_double2, vector_double2, vector_double2);

/*  The double3 variants of these functions take their arguments in a buffer
 *  to workaround the fact that double3 calling conventions are different
 *  depending on whether or not the executable has been compiled with AVX
 *  enabled.                                                                  */
extern double _simd_orient_vd3(const double *);
extern double _simd_orient_pd3(const double *);
extern double _simd_insphere_pd3(const double *);
#endif /* SIMD_LIBRARY_VERSION */
  
#pragma mark - math
extern  vector_float4 __cos_f4( vector_float4);
extern vector_double2 __cos_d2(vector_double2);

extern  vector_float4 __sin_f4( vector_float4);
extern vector_double2 __sin_d2(vector_double2);

#if defined __AVX__
extern  vector_float8 __cos_f8( vector_float8);
extern vector_double4 __cos_d4(vector_double4);

extern  vector_float8 __sin_f8( vector_float8);
extern vector_double4 __sin_d4(vector_double4);
#endif

#pragma mark - matrix
extern  matrix_float2x2 __invert_f2( matrix_float2x2);
extern matrix_double2x2 __invert_d2(matrix_double2x2);
extern  matrix_float3x3 __invert_f3( matrix_float3x3);
extern matrix_double3x3 __invert_d3(matrix_double3x3);
extern  matrix_float4x4 __invert_f4( matrix_float4x4);
extern matrix_double4x4 __invert_d4(matrix_double4x4);

#ifdef __cplusplus
}
#endif
#endif /* __SIMD_REQUIRED_COMPILER_FEATURES__ */
#endif /* __SIMD_EXTERN_HEADER__ */
