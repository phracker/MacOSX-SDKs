/*  Copyright (c) 2014 Apple, Inc. All rights reserved.
 *
 *  This header defines nine matrix types for each of float and double, which
 *  are intended for use together with the vector types defined in
 *  <simd/vector_types.h>.
 *
 *  For compatibility with common graphics libraries, these matrices are stored
 *  in column-major order, and implemented as arrays of column vectors.
 *  Column-major storage order may seem a little strange if you aren't used to
 *  it, but for most usage the memory layout of the matrices shouldn't matter
 *  at all; instead you should think of matrices as abstract mathematical
 *  objects that you use to perform arithmetic without worrying about the
 *  details of the underlying representation.
 *
 *  WARNING: vectors of length three are internally represented as length four
 *  vectors with one element of padding (for alignment purposes).  This means
 *  that when a floatNx3 or doubleNx3 is viewed as a vector, it appears to
 *  have 4*N elements instead of the expected 3*N (with one padding element
 *  at the end of each column).  The matrix elements are laid out in memory
 *  as follows:
 *
 *      { 0, 1, 2, x, 3, 4, 5, x, ... }
 *
 *  (where the scalar indices used above indicate the conceptual column-
 *  major storage order).  If you aren't monkeying around with the internal
 *  storage details of matrices, you don't need to worry about this at all.
 *  Consider this yet another good reason to avoid doing so.                  */

#ifndef __SIMD_MATRIX_TYPES_HEADER__
#define __SIMD_MATRIX_TYPES_HEADER__

#include <simd/internal.h>
#include <simd/vector_types.h>
#if __has_attribute(__ext_vector_type__)
/*  The function of this header fundamentally depends on the ext_vector_type
 *  attribute.  There is no fallback if these attributes are not supported by
 *  your compiler.                                                            */

/*  Matrix types available in C, Objective-C, and C++                         */
typedef struct { vector_float2 columns[2]; } matrix_float2x2;
typedef struct { vector_float2 columns[3]; } matrix_float3x2;
typedef struct { vector_float2 columns[4]; } matrix_float4x2;

typedef struct { vector_float3 columns[2]; } matrix_float2x3;
typedef struct { vector_float3 columns[3]; } matrix_float3x3;
typedef struct { vector_float3 columns[4]; } matrix_float4x3;

typedef struct { vector_float4 columns[2]; } matrix_float2x4;
typedef struct { vector_float4 columns[3]; } matrix_float3x4;
typedef struct { vector_float4 columns[4]; } matrix_float4x4;

typedef struct { vector_double2 columns[2]; } matrix_double2x2;
typedef struct { vector_double2 columns[3]; } matrix_double3x2;
typedef struct { vector_double2 columns[4]; } matrix_double4x2;

typedef struct { vector_double3 columns[2]; } matrix_double2x3;
typedef struct { vector_double3 columns[3]; } matrix_double3x3;
typedef struct { vector_double3 columns[4]; } matrix_double4x3;

typedef struct { vector_double4 columns[2]; } matrix_double2x4;
typedef struct { vector_double4 columns[3]; } matrix_double3x4;
typedef struct { vector_double4 columns[4]; } matrix_double4x4;

#ifdef __cplusplus
namespace simd {
    struct float2x2 : ::matrix_float2x2 {
        float2x2() { columns[0] = 0; columns[1] = 0; }
        float2x2(simd::float2 v) { columns[0] = (simd::float2){v.x,0}; columns[1] = (simd::float2){0,v.y}; }
        float2x2(simd::float2 c0, simd::float2 c1) { columns[0] = c0; columns[1] = c1; }
        float2x2(::matrix_float2x2 m) : ::matrix_float2x2(m) { }
    };
    struct float3x2 : ::matrix_float3x2 {
        float3x2() { columns[0] = 0; columns[1] = 0; columns[2] = 0; }
        float3x2(simd::float2 v) { columns[0] = (simd::float2){v.x,0}; columns[1] = (simd::float2){0,v.y}; columns[2] = 0; }
        float3x2(simd::float2 c0, simd::float2 c1, simd::float2 c2) { columns[0] = c0; columns[1] = c1; columns[2] = c2; }
        float3x2(::matrix_float3x2 m) : ::matrix_float3x2(m) { }
    };
    struct float4x2 : ::matrix_float4x2 {
        float4x2() { columns[0] = 0; columns[1] = 0; columns[2] = 0; columns[3] = 0; }
        float4x2(simd::float2 v) { columns[0] = (simd::float2){v.x,0}; columns[1] = (simd::float2){0,v.y}; columns[2] = 0; columns[3] = 0; }
        float4x2(simd::float2 c0, simd::float2 c1, simd::float2 c2, simd::float2 c3) { columns[0] = c0; columns[1] = c1; columns[2] = c2; columns[3] = c3; }
        float4x2(::matrix_float4x2 m) : ::matrix_float4x2(m) { }
    };
    struct float2x3 : ::matrix_float2x3 {
        float2x3() { columns[0] = 0; columns[1] = 0; }
        float2x3(simd::float2 v) { columns[0] = (simd::float3){v.x,0,0}; columns[1] = (simd::float3){0,v.y,0}; }
        float2x3(simd::float3 c0, simd::float3 c1) { columns[0] = c0; columns[1] = c1; }
        float2x3(::matrix_float2x3 m) : ::matrix_float2x3(m) { }
    };
    struct float3x3 : ::matrix_float3x3 {
        float3x3() { columns[0] = 0; columns[1] = 0; columns[2] = 0; }
        float3x3(simd::float3 v) { columns[0] = (simd::float3){v.x,0,0}; columns[1] = (simd::float3){0,v.y,0}; columns[2] = (simd::float3){0,0,v.z}; }
        float3x3(simd::float3 c0, simd::float3 c1, simd::float3 c2) { columns[0] = c0; columns[1] = c1; columns[2] = c2; }
        float3x3(::matrix_float3x3 m) : ::matrix_float3x3(m) { }
    };
    struct float4x3 : ::matrix_float4x3 {
        float4x3() { columns[0] = 0; columns[1] = 0; columns[2] = 0; columns[3] = 0; }
        float4x3(simd::float3 v) { columns[0] = (simd::float3){v.x,0,0}; columns[1] = (simd::float3){0,v.y,0}; columns[2] = (simd::float3){0,0,v.z}; columns[3] = 0; }
        float4x3(simd::float3 c0, simd::float3 c1, simd::float3 c2, simd::float3 c3) { columns[0] = c0; columns[1] = c1; columns[2] = c2; columns[3] = c3; }
        float4x3(::matrix_float4x3 m) : ::matrix_float4x3(m) { }
    };
    struct float2x4 : ::matrix_float2x4 {
        float2x4() { columns[0] = 0; columns[1] = 0; }
        float2x4(simd::float2 v) { columns[0] = (simd::float4){v.x,0,0,0}; columns[1] = (simd::float4){0,v.y,0,0}; }
        float2x4(simd::float4 c0, simd::float4 c1) { columns[0] = c0; columns[1] = c1; }
        float2x4(::matrix_float2x4 m) : ::matrix_float2x4(m) { }
    };
    struct float3x4 : ::matrix_float3x4 {
        float3x4() { columns[0] = 0; columns[1] = 0; columns[2] = 0; }
        float3x4(simd::float3 v) { columns[0] = (simd::float4){v.x,0,0,0}; columns[1] = (simd::float4){0,v.y,0,0}; columns[2] = (simd::float4){0,0,v.z,0}; }
        float3x4(simd::float4 c0, simd::float4 c1, simd::float4 c2) { columns[0] = c0; columns[1] = c1; columns[2] = c2; }
        float3x4(::matrix_float3x4 m) : ::matrix_float3x4(m) { }
    };
    struct float4x4 : ::matrix_float4x4 {
        float4x4() { columns[0] = 0; columns[1] = 0; columns[2] = 0; columns[3] = 0; }
        float4x4(simd::float4 v) { columns[0] = (simd::float4){v.x,0,0,0}; columns[1] = (simd::float4){0,v.y,0,0}; columns[2] = (simd::float4){0,0,v.z,0}; columns[3] = (simd::float4){0,0,0,v.w}; }
        float4x4(simd::float4 c0, simd::float4 c1, simd::float4 c2, simd::float4 c3) { columns[0] = c0; columns[1] = c1; columns[2] = c2; columns[3] = c3; }
        float4x4(::matrix_float4x4 m) : ::matrix_float4x4(m) { }
    };
    struct double2x2 : ::matrix_double2x2 {
        double2x2() { columns[0] = 0; columns[1] = 0; }
        double2x2(simd::double2 v) { columns[0] = (simd::double2){v.x,0}; columns[1] = (simd::double2){0,v.y}; }
        double2x2(simd::double2 c0, simd::double2 c1) { columns[0] = c0; columns[1] = c1; }
        double2x2(::matrix_double2x2 m) : ::matrix_double2x2(m) { }
    };
    struct double3x2 : ::matrix_double3x2 {
        double3x2() { columns[0] = 0; columns[1] = 0; columns[2] = 0; }
        double3x2(simd::double2 v) { columns[0] = (simd::double2){v.x,0}; columns[1] = (simd::double2){0,v.y}; columns[2] = 0; }
        double3x2(simd::double2 c0, simd::double2 c1, simd::double2 c2) { columns[0] = c0; columns[1] = c1; columns[2] = c2; }
        double3x2(::matrix_double3x2 m) : ::matrix_double3x2(m) { }
    };
    struct double4x2 : ::matrix_double4x2 {
        double4x2() { columns[0] = 0; columns[1] = 0; columns[2] = 0; columns[3] = 0; }
        double4x2(simd::double2 v) { columns[0] = (simd::double2){v.x,0}; columns[1] = (simd::double2){0,v.y}; columns[2] = 0; columns[3] = 0; }
        double4x2(simd::double2 c0, simd::double2 c1, simd::double2 c2, simd::double2 c3) { columns[0] = c0; columns[1] = c1; columns[2] = c2; columns[3] = c3; }
        double4x2(::matrix_double4x2 m) : ::matrix_double4x2(m) { }
    };
    struct double2x3 : ::matrix_double2x3 {
        double2x3() { columns[0] = 0; columns[1] = 0; }
        double2x3(simd::double2 v) { columns[0] = (simd::double3){v.x,0,0}; columns[1] = (simd::double3){0,v.y,0}; }
        double2x3(simd::double3 c0, simd::double3 c1) { columns[0] = c0; columns[1] = c1; }
        double2x3(::matrix_double2x3 m) : ::matrix_double2x3(m) { }
    };
    struct double3x3 : ::matrix_double3x3 {
        double3x3() { columns[0] = 0; columns[1] = 0; columns[2] = 0; }
        double3x3(simd::double3 v) { columns[0] = (simd::double3){v.x,0,0}; columns[1] = (simd::double3){0,v.y,0}; columns[2] = (simd::double3){0,0,v.z}; }
        double3x3(simd::double3 c0, simd::double3 c1, simd::double3 c2) { columns[0] = c0; columns[1] = c1; columns[2] = c2; }
        double3x3(::matrix_double3x3 m) : ::matrix_double3x3(m) { }
    };
    struct double4x3 : ::matrix_double4x3 {
        double4x3() { columns[0] = 0; columns[1] = 0; columns[2] = 0; columns[3] = 0; }
        double4x3(simd::double3 v) { columns[0] = (simd::double3){v.x,0,0}; columns[1] = (simd::double3){0,v.y,0}; columns[2] = (simd::double3){0,0,v.z}; columns[3] = 0; }
        double4x3(simd::double3 c0, simd::double3 c1, simd::double3 c2, simd::double3 c3) { columns[0] = c0; columns[1] = c1; columns[2] = c2; columns[3] = c3; }
        double4x3(::matrix_double4x3 m) : ::matrix_double4x3(m) { }
    };
    struct double2x4 : ::matrix_double2x4 {
        double2x4() { columns[0] = 0; columns[1] = 0; }
        double2x4(simd::double2 v) { columns[0] = (simd::double4){v.x,0,0,0}; columns[1] = (simd::double4){0,v.y,0,0}; }
        double2x4(simd::double4 c0, simd::double4 c1) { columns[0] = c0; columns[1] = c1; }
        double2x4(::matrix_double2x4 m) : ::matrix_double2x4(m) { }
    };
    struct double3x4 : ::matrix_double3x4 {
        double3x4() { columns[0] = 0; columns[1] = 0; columns[2] = 0; }
        double3x4(simd::double3 v) { columns[0] = (simd::double4){v.x,0,0,0}; columns[1] = (simd::double4){0,v.y,0,0}; columns[2] = (simd::double4){0,0,v.z,0}; }
        double3x4(simd::double4 c0, simd::double4 c1, simd::double4 c2) { columns[0] = c0; columns[1] = c1; columns[2] = c2; }
        double3x4(::matrix_double3x4 m) : ::matrix_double3x4(m) { }
    };
    struct double4x4 : ::matrix_double4x4 {
        double4x4() { columns[0] = 0; columns[1] = 0; columns[2] = 0; columns[3] = 0; }
        double4x4(simd::double4 v) { columns[0] = (simd::double4){v.x,0,0,0}; columns[1] = (simd::double4){0,v.y,0,0}; columns[2] = (simd::double4){0,0,v.z,0}; columns[3] = (simd::double4){0,0,0,v.w}; }
        double4x4(simd::double4 c0, simd::double4 c1, simd::double4 c2, simd::double4 c3) { columns[0] = c0; columns[1] = c1; columns[2] = c2; columns[3] = c3; }
        double4x4(::matrix_double4x4 m) : ::matrix_double4x4(m) { }
    };
}
#endif /* __cplusplus */
#endif /* __has_attribute(__ext_vector_type__) */
#endif // __SIMD_MATRIX_TYPES_HEADER__
