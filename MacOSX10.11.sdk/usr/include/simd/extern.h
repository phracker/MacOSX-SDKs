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
