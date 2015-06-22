/*  Copyright (c) 2014 Apple, Inc. All rights reserved.
 *
 *  The vector types defined in this header are based on what clang calls
 *  "OpenCL vector types" (don't let the name fool you, these types work just
 *  fine in C, Objective-C, and C++).  There are a few tricks that make these
 *  types nicer to work with than traditional SIMD types:
 *
 *      - Basic arithmetic operators are overloaded to work with these types,
 *      including both vector-vector and vector-scalar operations.
 *
 *      - It is possible to access vector components both via array-style
 *      subscripting, and by using the "." operator with component names
 *      ("x", "y", "z", "w", or combinations thereof).
 *
 *  Some examples:
 *
 *      vector_float4 x = 1.0f;         // x = { 1, 1, 1, 1 }.
 *      vector_float3 y = { 1, 2, 3 };  // y = { 1, 2, 3 }.
 *      y = 1/y;                        // y = { 1, 1/2, 1/3 }.
 *      x.xyz = y.zyx;                  // x = { 1/3, 1/2, 1, 1 }.
 *      x.w = 0;                        // x = { 1/4, 1/3, 1/2, 0 }.
 *
 *  Besides the .xyzw component names, the following sub-vectors can be easily
 *  accessed: .lo / .hi (first half and second half of a vector), .even / .odd
 *  (the even- and odd-indexed elements of a vector).
 *
 *  Beyond basic arithmetic operations using the overloaded operators, you can
 *  also use these types with:
 *
 *      - A large assortment of vector and matrix operations that are defined
 *        in the header <simd/simd.h>.
 *      - __builtin_shufflevector and __builtin_convertvector (consult the
 *        clang documentation for details on these operations).
 *      - SSE and AVX intrinsics defined in <immintrin.h>.
 *      - NEON intrinsics defined in <arm_neon.h>.
 *
 *  You should be aware that some of these types include padding.  For
 *  example, sizeof(float3) is 16, not 12 as one might naively expect.  If
 *  one writes the following:
 *
 *      #include <vector_types.h>
 *      vector_float3 x[2];
 *
 *  then the elements of x will be laid out in memory as follows:
 *
 *    address: 0x...0  0x...4  0x...0  0x...4  0x...0  0x...4  0x...0  0x...4
 *       data: x[0].x  x[0].y  x[0].z  padding x[1].z  x[1].y  x[1].z  padding
 *
 *  In common scenarios, this improves performance and doesn't cause any real
 *  difficulty, but one needs to exercise some caution when converting between
 *  arrays of data and vectors.
 *
 *  The exact set of types defined by this header vary somewhat depending on
 *  the language in use; when using the Metal unified GPU language, the types
 *  are as follows:
 *
 *      scalar type     derived vector types
 *      -------------------------------------------------
 *      bool            bool2       bool3       bool4
 *      8-bit int       char2       char3       char4
 *      (unsigned)      uchar2      uchar3      uchar4
 *      16-bit int      short2      short3      short4
 *      (unsigned)      ushort2     ushort3     ushort4
 *      half float      half2       half3       half4
 *      32-bit int      int2        int3        int4
 *      (unsigned)      uint2       uint3       uint4
 *      float           float2      float3      float4
 *
 *  In C and Objective-C, the available types are as follows:
 *
 *      scalar type     derived vector types
 *      ----------------------------------------------------------------------
 *      8-bit int       vector_charN, where N is 2, 3, 4, 8, 16, or 32.
 *      (unsigned)      vector_ucharN, where N is 2, 3, 4, 8, 16, or 32.
 *      16-bit int      vector_shortN, where N is 2, 3, 4, 8, 16, or 32.
 *      (unsigned)      vector_ushortN, where N is 2, 3, 4, 8, 16, or 32.
 *      32-bit int      vector_intN, where N is 2, 3, 4, 8, or 16.
 *      (unsigned)      vector_uintN, where N is 2, 3, 4, 8, or 16.
 *      float           vector_floatN, where N is 2, 3, 4, 8, or 16.
 *      64-bit int      vector_longN, where N is 2, 3, 4, or 8.
 *      (unsigned)      vector_ulongN, where N is 2, 3, 4, or 8.
 *      double          vector_doubleN, where N is 2, 3, 4, or 8.
 *
 *  Note that vector_longN and vector_ulongN are always vectors of 64-bit
 *  elements, regardless of the size of the scalar "long" type (thus, they
 *  are actually "long long" on 32-bit iOS and OS X).  This follows the
 *  convention of the OpenCL language for such types.  Note also that because
 *  vector_longN and vector_ulongN have different base types on 32- and 64-bit
 *  builds, we provide vector_long1 and vector_ulong1 as compatable scalar
 *  types.
 *
 *  In C++, we provide all of the C and Objective-C types, plus more concise
 *  types within the simd:: namespace:
 *
 *      scalar type     derived vector types
 *      ----------------------------------------------------------------------
 *      8-bit int       simd::charN, where N is 2, 3, 4, 8, 16, or 32.
 *      (unsigned)      simd::ucharN, where N is 2, 3, 4, 8, 16, or 32.
 *      16-bit int      simd::shortN, where N is 2, 3, 4, 8, 16, or 32.
 *      (unsigned)      simd::ushortN, where N is 2, 3, 4, 8, 16, or 32.
 *      32-bit int      simd::intN, where N is 2, 3, 4, 8, or 16.
 *      (unsigned)      simd::uintN, where N is 2, 3, 4, 8, or 16.
 *      float           simd::floatN, where N is 2, 3, 4, 8, or 16.
 *      64-bit int      simd::longN, where N is 2, 3, 4, or 8.
 *      (unsigned)      simd::ulongN, where N is 2, 3, 4, or 8.
 *      double          simd::doubleN, where N is 2, 3, 4, or 8.
 *
 */

#ifndef __SIMD_VECTOR_TYPES_HEADER__
#define __SIMD_VECTOR_TYPES_HEADER__

#include <simd/internal.h>
#if __has_attribute(__ext_vector_type__)
/*  The function of this header fundamentally depends on the ext_vector_type
 *  attribute.  There is no fallback if these attributes are not supported by
 *  your compiler.                                                            */

#ifdef __METAL_VERSION__
typedef __attribute__((__ext_vector_type__(2))) bool vector_bool2;
typedef __attribute__((__ext_vector_type__(3))) bool vector_bool3;
typedef __attribute__((__ext_vector_type__(4))) bool vector_bool4;

typedef __attribute__((__ext_vector_type__(2))) half vector_half2;
typedef __attribute__((__ext_vector_type__(3))) half vector_half3;
typedef __attribute__((__ext_vector_type__(4))) half vector_half4;
#endif

typedef __attribute__((__ext_vector_type__(2))) char vector_char2;
typedef __attribute__((__ext_vector_type__(3))) char vector_char3;
typedef __attribute__((__ext_vector_type__(4))) char vector_char4;
#ifndef __METAL_VERSION__
typedef __attribute__((__ext_vector_type__(8))) char vector_char8;
typedef __attribute__((__ext_vector_type__(16))) char vector_char16;
typedef __attribute__((__ext_vector_type__(32))) char vector_char32;
#endif

typedef __attribute__((__ext_vector_type__(2))) unsigned char vector_uchar2;
typedef __attribute__((__ext_vector_type__(3))) unsigned char vector_uchar3;
typedef __attribute__((__ext_vector_type__(4))) unsigned char vector_uchar4;
#ifndef __METAL_VERSION__
typedef __attribute__((__ext_vector_type__(8))) unsigned char vector_uchar8;
typedef __attribute__((__ext_vector_type__(16))) unsigned char vector_uchar16;
typedef __attribute__((__ext_vector_type__(32))) unsigned char vector_uchar32;
#endif

typedef __attribute__((__ext_vector_type__(2))) short vector_short2;
typedef __attribute__((__ext_vector_type__(3))) short vector_short3;
typedef __attribute__((__ext_vector_type__(4))) short vector_short4;
#ifndef __METAL_VERSION__
typedef __attribute__((__ext_vector_type__(8))) short vector_short8;
typedef __attribute__((__ext_vector_type__(16))) short vector_short16;
typedef __attribute__((__ext_vector_type__(32))) short vector_short32;
#endif

typedef __attribute__((__ext_vector_type__(2))) unsigned short vector_ushort2;
typedef __attribute__((__ext_vector_type__(3))) unsigned short vector_ushort3;
typedef __attribute__((__ext_vector_type__(4))) unsigned short vector_ushort4;
#ifndef __METAL_VERSION__
typedef __attribute__((__ext_vector_type__(8))) unsigned short vector_ushort8;
typedef __attribute__((__ext_vector_type__(16))) unsigned short vector_ushort16;
typedef __attribute__((__ext_vector_type__(32))) unsigned short vector_ushort32;
#endif

typedef __attribute__((__ext_vector_type__(2))) int vector_int2;
typedef __attribute__((__ext_vector_type__(3))) int vector_int3;
typedef __attribute__((__ext_vector_type__(4))) int vector_int4;
#ifndef __METAL_VERSION__
typedef __attribute__((__ext_vector_type__(8))) int vector_int8;
typedef __attribute__((__ext_vector_type__(16))) int vector_int16;
#endif

typedef __attribute__((__ext_vector_type__(2))) unsigned int vector_uint2;
typedef __attribute__((__ext_vector_type__(3))) unsigned int vector_uint3;
typedef __attribute__((__ext_vector_type__(4))) unsigned int vector_uint4;
#ifndef __METAL_VERSION__
typedef __attribute__((__ext_vector_type__(8))) unsigned int vector_uint8;
typedef __attribute__((__ext_vector_type__(16))) unsigned int vector_uint16;
#endif

typedef __attribute__((__ext_vector_type__(2))) float vector_float2;
typedef __attribute__((__ext_vector_type__(3))) float vector_float3;
typedef __attribute__((__ext_vector_type__(4))) float vector_float4;
#ifndef __METAL_VERSION__
typedef __attribute__((__ext_vector_type__(8))) float vector_float8;
typedef __attribute__((__ext_vector_type__(16))) float vector_float16;
#endif

#ifndef __METAL_VERSION__
# if defined __LP64__
typedef                                         long vector_long1;
typedef __attribute__((__ext_vector_type__(2))) long vector_long2;
typedef __attribute__((__ext_vector_type__(3))) long vector_long3;
typedef __attribute__((__ext_vector_type__(4))) long vector_long4;
typedef __attribute__((__ext_vector_type__(8))) long vector_long8;

typedef                                         unsigned long vector_ulong1;
typedef __attribute__((__ext_vector_type__(2))) unsigned long vector_ulong2;
typedef __attribute__((__ext_vector_type__(3))) unsigned long vector_ulong3;
typedef __attribute__((__ext_vector_type__(4))) unsigned long vector_ulong4;
typedef __attribute__((__ext_vector_type__(8))) unsigned long vector_ulong8;
# else
typedef                                         long long vector_long1;
typedef __attribute__((__ext_vector_type__(2))) long long vector_long2;
typedef __attribute__((__ext_vector_type__(3))) long long vector_long3;
typedef __attribute__((__ext_vector_type__(4))) long long vector_long4;
typedef __attribute__((__ext_vector_type__(8))) long long vector_long8;

typedef                                         unsigned long long vector_ulong1;
typedef __attribute__((__ext_vector_type__(2))) unsigned long long vector_ulong2;
typedef __attribute__((__ext_vector_type__(3))) unsigned long long vector_ulong3;
typedef __attribute__((__ext_vector_type__(4))) unsigned long long vector_ulong4;
typedef __attribute__((__ext_vector_type__(8))) unsigned long long vector_ulong8;
# endif

typedef __attribute__((__ext_vector_type__(2))) double vector_double2;
typedef __attribute__((__ext_vector_type__(3))) double vector_double3;
typedef __attribute__((__ext_vector_type__(4))) double vector_double4;
typedef __attribute__((__ext_vector_type__(8))) double vector_double8;
#endif /* __METAL_VERSION__ */

#if defined __cplusplus || defined __METAL_VERSION__

#ifdef __METAL_VERSION__
namespace metal = simd;
#endif

namespace simd {
#ifdef __METAL_VERSION__
    typedef ::vector_bool2 bool2;
    typedef ::vector_bool3 bool3;
    typedef ::vector_bool4 bool4;

    typedef ::vector_half2 half2;
    typedef ::vector_half3 half3;
    typedef ::vector_half4 half4;
#endif
    typedef ::vector_char2 char2;
    typedef ::vector_char3 char3;
    typedef ::vector_char4 char4;
#ifndef __METAL_VERSION__
    typedef ::vector_char8 char8;
    typedef ::vector_char16 char16;
    typedef ::vector_char32 char32;
#endif

    typedef ::vector_uchar2 uchar2;
    typedef ::vector_uchar3 uchar3;
    typedef ::vector_uchar4 uchar4;
#ifndef __METAL_VERSION__
    typedef ::vector_uchar8 uchar8;
    typedef ::vector_uchar16 uchar16;
    typedef ::vector_uchar32 uchar32;
#endif

    typedef ::vector_short2 short2;
    typedef ::vector_short3 short3;
    typedef ::vector_short4 short4;
#ifndef __METAL_VERSION__
    typedef ::vector_short8 short8;
    typedef ::vector_short16 short16;
    typedef ::vector_short32 short32;
#endif

    typedef ::vector_ushort2 ushort2;
    typedef ::vector_ushort3 ushort3;
    typedef ::vector_ushort4 ushort4;
#ifndef __METAL_VERSION__
    typedef ::vector_ushort8 ushort8;
    typedef ::vector_ushort16 ushort16;
    typedef ::vector_ushort32 ushort32;
#endif

    typedef ::vector_int2 int2;
    typedef ::vector_int3 int3;
    typedef ::vector_int4 int4;
#ifndef __METAL_VERSION__
    typedef ::vector_int8 int8;
    typedef ::vector_int16 int16;
#endif

    typedef ::vector_uint2 uint2;
    typedef ::vector_uint3 uint3;
    typedef ::vector_uint4 uint4;
#ifndef __METAL_VERSION__
    typedef ::vector_uint8 uint8;
    typedef ::vector_uint16 uint16;
#endif

    typedef ::vector_float2 float2;
    typedef ::vector_float3 float3;
    typedef ::vector_float4 float4;
#ifndef __METAL_VERSION__
    typedef ::vector_float8 float8;
    typedef ::vector_float16 float16;
#endif

#ifndef __METAL_VERSION__
    typedef ::vector_long1 long1;
    typedef ::vector_long2 long2;
    typedef ::vector_long3 long3;
    typedef ::vector_long4 long4;
    typedef ::vector_long8 long8;

    typedef ::vector_ulong1 ulong1;
    typedef ::vector_ulong2 ulong2;
    typedef ::vector_ulong3 ulong3;
    typedef ::vector_ulong4 ulong4;
    typedef ::vector_ulong8 ulong8;
    
    typedef ::vector_double2 double2;
    typedef ::vector_double3 double3;
    typedef ::vector_double4 double4;
    typedef ::vector_double8 double8;
#endif
}

#endif /* __cplusplus */
#endif /* __has_attribute(__ext_vector_type__) */
#endif /* __SIMD_VECTOR_TYPES_HEADER__ */
