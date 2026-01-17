/*******************************************************************************
 * Copyright (c) 2014 Apple Inc. All rights reserved
 ******************************************************************************/

#ifndef __CL_KERNEL_H
#define __CL_KERNEL_H

// FIXME: Intel needs this defined for their builtin until they fixed there library.
// We should also verify that cl_khr_fp64 pragma is correctly supported in the compiler.
// <rdar://problem/29068635>
#if ! defined( cl_khr_fp64 )                                       &&  \
  /* Intel  */ (defined( __i386__ ) || defined( __x86_64__ )       ||  \
  /* GPUf64 */ (defined(cl_APPLE_fp64_basic_ops)))
  #define cl_khr_fp64 1
#endif


// 5.1.2 OpenCL Vector Data Types
typedef __attribute__(( ext_vector_type(2) ))  char __char2;
typedef __attribute__(( ext_vector_type(3) ))  char __char3;
typedef __attribute__(( ext_vector_type(4) ))  char __char4;
typedef __attribute__(( ext_vector_type(8) ))  char __char8;
typedef __attribute__(( ext_vector_type(16) )) char __char16;
typedef unsigned char uchar;
typedef __attribute__(( ext_vector_type(2) ))  unsigned char __uchar2;
typedef __attribute__(( ext_vector_type(3) ))  unsigned char __uchar3;
typedef __attribute__(( ext_vector_type(4) ))  unsigned char __uchar4;
typedef __attribute__(( ext_vector_type(8) ))  unsigned char __uchar8;
typedef __attribute__(( ext_vector_type(16) )) unsigned char __uchar16;
typedef __attribute__(( ext_vector_type(2) ))  short __short2;
typedef __attribute__(( ext_vector_type(3) ))  short __short3;
typedef __attribute__(( ext_vector_type(4) ))  short __short4;
typedef __attribute__(( ext_vector_type(8) ))  short __short8;
typedef __attribute__(( ext_vector_type(16) )) short __short16;
typedef unsigned short ushort;
typedef __attribute__(( ext_vector_type(2) ))  unsigned short __ushort2;
typedef __attribute__(( ext_vector_type(3) ))  unsigned short __ushort3;
typedef __attribute__(( ext_vector_type(4) ))  unsigned short __ushort4;
typedef __attribute__(( ext_vector_type(8) ))  unsigned short __ushort8;
typedef __attribute__(( ext_vector_type(16) )) unsigned short __ushort16;
typedef __attribute__(( ext_vector_type(2) ))  int __int2;
typedef __attribute__(( ext_vector_type(3) ))  int __int3;
typedef __attribute__(( ext_vector_type(4) ))  int __int4;
typedef __attribute__(( ext_vector_type(8) ))  int __int8;
typedef __attribute__(( ext_vector_type(16) )) int __int16;
typedef unsigned int uint;
typedef __attribute__(( ext_vector_type(2) ))  unsigned int __uint2;
typedef __attribute__(( ext_vector_type(3) ))  unsigned int __uint3;
typedef __attribute__(( ext_vector_type(4) ))  unsigned int __uint4;
typedef __attribute__(( ext_vector_type(8) ))  unsigned int __uint8;
typedef __attribute__(( ext_vector_type(16) )) unsigned int __uint16;
typedef __attribute__(( ext_vector_type(2) ))  long __long2;
typedef __attribute__(( ext_vector_type(3) ))  long __long3;
typedef __attribute__(( ext_vector_type(4) ))  long __long4;
typedef __attribute__(( ext_vector_type(8) ))  long __long8;
typedef __attribute__(( ext_vector_type(16) )) long __long16;
typedef unsigned long ulong;
typedef __attribute__(( ext_vector_type(2) ))  unsigned long __ulong2;
typedef __attribute__(( ext_vector_type(3) ))  unsigned long __ulong3;
typedef __attribute__(( ext_vector_type(4) ))  unsigned long __ulong4;
typedef __attribute__(( ext_vector_type(8) ))  unsigned long __ulong8;
typedef __attribute__(( ext_vector_type(16) )) unsigned long __ulong16;
typedef __attribute__(( ext_vector_type(2) ))  float __float2;
typedef __attribute__(( ext_vector_type(3) ))  float __float3;
typedef __attribute__(( ext_vector_type(4) ))  float __float4;
typedef __attribute__(( ext_vector_type(8) ))  float __float8;
typedef __attribute__(( ext_vector_type(16) )) float __float16;
typedef __attribute__(( ext_vector_type(32) )) float __float32;

#if (defined(cl_khr_fp16) || defined(cl_APPLE_fp16_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
typedef __attribute__(( ext_vector_type(2) ))  half __half2;
typedef __attribute__(( ext_vector_type(3) ))  half __half3;
typedef __attribute__(( ext_vector_type(4) ))  half __half4;
typedef __attribute__(( ext_vector_type(8) ))  half __half8;
typedef __attribute__(( ext_vector_type(16) )) half __half16;
typedef __attribute__(( ext_vector_type(32) )) half __half32;
#endif

#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  typedef __attribute__(( ext_vector_type(2) ))  double __double2;
  typedef __attribute__(( ext_vector_type(3) ))  double __double3;
  typedef __attribute__(( ext_vector_type(4) ))  double __double4;
  typedef __attribute__(( ext_vector_type(8) ))  double __double8;
  typedef __attribute__(( ext_vector_type(16) )) double __double16;
#endif

//Vector type common names. These can now be #undef'd to avoid collision with similar names in imported C code. 
#define char2			__char2
#define char3			__char3
#define char4			__char4
#define char8			__char8
#define char16			__char16
#define uchar2			__uchar2
#define uchar3			__uchar3
#define uchar4			__uchar4
#define uchar8			__uchar8
#define uchar16			__uchar16
#define short2			__short2
#define short3			__short3
#define short4			__short4
#define short8			__short8
#define short16			__short16
#define ushort2			__ushort2
#define ushort3			__ushort3
#define ushort4			__ushort4
#define ushort8			__ushort8
#define ushort16		__ushort16
#define int2			__int2
#define int3			__int3
#define int4			__int4
#define int8			__int8
#define int16			__int16
#define uint2			__uint2
#define uint3			__uint3
#define uint4			__uint4
#define uint8			__uint8
#define uint16			__uint16
#define long2			__long2
#define long3			__long3
#define long4			__long4
#define long8			__long8
#define long16			__long16
#define ulong2			__ulong2
#define ulong3			__ulong3
#define ulong4			__ulong4
#define ulong8			__ulong8
#define ulong16			__ulong16
#define float2			__float2
#define float3			__float3
#define float4			__float4
#define float8			__float8
#define float16			__float16
#define float32			__float32

#if (defined(cl_khr_fp16) || defined(cl_APPLE_fp16_basic_ops))
    #define half2               __half2
    #define half3               __half3
    #define half4               __half4
    #define half8               __half8
    #define half16              __half16
#else
typedef struct __Reserved_Name__Do_not_use_half2        half2;
typedef struct __Reserved_Name__Do_not_use_half3        half3;
typedef struct __Reserved_Name__Do_not_use_half4        half4;
typedef struct __Reserved_Name__Do_not_use_half8        half8;
typedef struct __Reserved_Name__Do_not_use_half16       half16;
#endif


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
    #define double2			__double2
    #define double3			__double3
    #define double4			__double4
    #define double8			__double8
    #define double16		__double16
#else
typedef struct __Unsupported_Type__Do_not_use_double2_on_this_device      double2;
typedef struct __Unsupported_Type__Do_not_use_double3_on_this_device      double3;
typedef struct __Unsupported_Type__Do_not_use_double4_on_this_device      double4;
typedef struct __Unsupported_Type__Do_not_use_double8_on_this_device      double8;
typedef struct __Unsupported_Type__Do_not_use_double16_on_this_device     double16;
#endif

//Legacy SPI interfaces
#define __int3_SPI		__int3
#define __float3_SPI	__float3

typedef struct __Reserved_Name__Do_not_use_bool2        bool2;
typedef struct __Reserved_Name__Do_not_use_bool3        bool3;
typedef struct __Reserved_Name__Do_not_use_bool4        bool4;
typedef struct __Reserved_Name__Do_not_use_bool8        bool8;
typedef struct __Reserved_Name__Do_not_use_bool16       bool16;

// Defend reserved types
typedef struct __Reserved_Name__Do_not_use_quad         quad;
typedef struct __Reserved_Name__Do_not_use_quad2        quad2;
typedef struct __Reserved_Name__Do_not_use_quad3        quad3;
typedef struct __Reserved_Name__Do_not_use_quad4        quad4;
typedef struct __Reserved_Name__Do_not_use_quad8        quad8;
typedef struct __Reserved_Name__Do_not_use_quad16       quad16;
typedef struct __Reserved_Name__Do_not_use_complex      complex;
typedef struct __Reserved_Name__Do_not_use_imaginary    imaginary;
typedef struct __Reserved_Name__Do_not_use_float2x2     float2x2;
typedef struct __Reserved_Name__Do_not_use_float2x3     float2x3;
typedef struct __Reserved_Name__Do_not_use_float3x2     float3x2;
typedef struct __Reserved_Name__Do_not_use_float2x4     float2x4;
typedef struct __Reserved_Name__Do_not_use_float4x2     float4x2;
typedef struct __Reserved_Name__Do_not_use_float3x4     float3x4;
typedef struct __Reserved_Name__Do_not_use_float4x3     float4x3;
typedef struct __Reserved_Name__Do_not_use_float4x4     float4x4;
typedef struct __Reserved_Name__Do_not_use_float8x8     float8x8;
typedef struct __Reserved_Name__Do_not_use_float16x16   float16x16;
typedef struct __Reserved_Name__Do_not_use_double2x2    double2x2;
typedef struct __Reserved_Name__Do_not_use_double2x3    double2x3;
typedef struct __Reserved_Name__Do_not_use_double3x2    double3x2;
typedef struct __Reserved_Name__Do_not_use_double2x4    double2x4;
typedef struct __Reserved_Name__Do_not_use_double4x2    double4x2;
typedef struct __Reserved_Name__Do_not_use_double3x4    double3x4;
typedef struct __Reserved_Name__Do_not_use_double4x3    double4x3;
typedef struct __Reserved_Name__Do_not_use_double4x4    double4x4;
typedef struct __Reserved_Name__Do_not_use_double8x8    double8x8;
typedef struct __Reserved_Name__Do_not_use_double16x16  double16x16;
typedef struct __Reserved_Name__Do_not_use_float5       float5;
typedef struct __Reserved_Name__Do_not_use_float6       float6;
typedef struct __Reserved_Name__Do_not_use_float7       float7;
typedef struct __Reserved_Name__Do_not_use_float9       float9;
typedef struct __Reserved_Name__Do_not_use_float10      float10;
typedef struct __Reserved_Name__Do_not_use_float11      float11;
typedef struct __Reserved_Name__Do_not_use_float12      float12;
typedef struct __Reserved_Name__Do_not_use_float13      float13;
typedef struct __Reserved_Name__Do_not_use_float14      float14;
typedef struct __Reserved_Name__Do_not_use_float15      float15;
typedef struct __Reserved_Name__Do_not_use_double5      double5;
typedef struct __Reserved_Name__Do_not_use_double6      double6;
typedef struct __Reserved_Name__Do_not_use_double7      double7;
typedef struct __Reserved_Name__Do_not_use_double9      double9;
typedef struct __Reserved_Name__Do_not_use_double10     double10;
typedef struct __Reserved_Name__Do_not_use_double11     double11;
typedef struct __Reserved_Name__Do_not_use_double12     double12;
typedef struct __Reserved_Name__Do_not_use_double13     double13;
typedef struct __Reserved_Name__Do_not_use_double14     double14;
typedef struct __Reserved_Name__Do_not_use_double15     double15;
typedef struct __Reserved_Name__Do_not_use_double32     double32;
typedef struct __Reserved_Name__Do_not_use_char5        char5;
typedef struct __Reserved_Name__Do_not_use_char6        char6;
typedef struct __Reserved_Name__Do_not_use_char7        char7;
typedef struct __Reserved_Name__Do_not_use_char9        char9;
typedef struct __Reserved_Name__Do_not_use_char10       char10;
typedef struct __Reserved_Name__Do_not_use_char11       char11;
typedef struct __Reserved_Name__Do_not_use_char12       char12;
typedef struct __Reserved_Name__Do_not_use_char13       char13;
typedef struct __Reserved_Name__Do_not_use_char14       char14;
typedef struct __Reserved_Name__Do_not_use_char15       char15;
typedef struct __Reserved_Name__Do_not_use_char32       char32;
typedef struct __Reserved_Name__Do_not_use_uchar5       uchar5;
typedef struct __Reserved_Name__Do_not_use_uchar6       uchar6;
typedef struct __Reserved_Name__Do_not_use_uchar7       uchar7;
typedef struct __Reserved_Name__Do_not_use_uchar9       uchar9;
typedef struct __Reserved_Name__Do_not_use_uchar10      uchar10;
typedef struct __Reserved_Name__Do_not_use_uchar11      uchar11;
typedef struct __Reserved_Name__Do_not_use_uchar12      uchar12;
typedef struct __Reserved_Name__Do_not_use_uchar13      uchar13;
typedef struct __Reserved_Name__Do_not_use_uchar14      uchar14;
typedef struct __Reserved_Name__Do_not_use_uchar15      uchar15;
typedef struct __Reserved_Name__Do_not_use_uchar32      uchar32;
typedef struct __Reserved_Name__Do_not_use_short5       short5;
typedef struct __Reserved_Name__Do_not_use_short6       short6;
typedef struct __Reserved_Name__Do_not_use_short7       short7;
typedef struct __Reserved_Name__Do_not_use_short9       short9;
typedef struct __Reserved_Name__Do_not_use_short10      short10;
typedef struct __Reserved_Name__Do_not_use_short11      short11;
typedef struct __Reserved_Name__Do_not_use_short12      short12;
typedef struct __Reserved_Name__Do_not_use_short13      short13;
typedef struct __Reserved_Name__Do_not_use_short14      short14;
typedef struct __Reserved_Name__Do_not_use_short15      short15;
typedef struct __Reserved_Name__Do_not_use_short32      short32;
typedef struct __Reserved_Name__Do_not_use_ushort5      ushort5;
typedef struct __Reserved_Name__Do_not_use_ushort6      ushort6;
typedef struct __Reserved_Name__Do_not_use_ushort7      ushort7;
typedef struct __Reserved_Name__Do_not_use_ushort9      ushort9;
typedef struct __Reserved_Name__Do_not_use_ushort10     ushort10;
typedef struct __Reserved_Name__Do_not_use_ushort11     ushort11;
typedef struct __Reserved_Name__Do_not_use_ushort12     ushort12;
typedef struct __Reserved_Name__Do_not_use_ushort13     ushort13;
typedef struct __Reserved_Name__Do_not_use_ushort14     ushort14;
typedef struct __Reserved_Name__Do_not_use_ushort15     ushort15;
typedef struct __Reserved_Name__Do_not_use_ushort32     ushort32;
typedef struct __Reserved_Name__Do_not_use_int5         int5;
typedef struct __Reserved_Name__Do_not_use_int6         int6;
typedef struct __Reserved_Name__Do_not_use_int7         int7;
typedef struct __Reserved_Name__Do_not_use_int9         int9;
typedef struct __Reserved_Name__Do_not_use_int10        int10;
typedef struct __Reserved_Name__Do_not_use_int11        int11;
typedef struct __Reserved_Name__Do_not_use_int12        int12;
typedef struct __Reserved_Name__Do_not_use_int13        int13;
typedef struct __Reserved_Name__Do_not_use_int14        int14;
typedef struct __Reserved_Name__Do_not_use_int15        int15;
typedef struct __Reserved_Name__Do_not_use_int32        int32;
typedef struct __Reserved_Name__Do_not_use_uint5        uint5;
typedef struct __Reserved_Name__Do_not_use_uint6        uint6;
typedef struct __Reserved_Name__Do_not_use_uint7        uint7;
typedef struct __Reserved_Name__Do_not_use_uint9        uint9;
typedef struct __Reserved_Name__Do_not_use_uint10       uint10;
typedef struct __Reserved_Name__Do_not_use_uint11       uint11;
typedef struct __Reserved_Name__Do_not_use_uint12       uint12;
typedef struct __Reserved_Name__Do_not_use_uint13       uint13;
typedef struct __Reserved_Name__Do_not_use_uint14       uint14;
typedef struct __Reserved_Name__Do_not_use_uint15       uint15;
typedef struct __Reserved_Name__Do_not_use_uint32       uint32;
typedef struct __Reserved_Name__Do_not_use_long5        long5;
typedef struct __Reserved_Name__Do_not_use_long6        long6;
typedef struct __Reserved_Name__Do_not_use_long7        long7;
typedef struct __Reserved_Name__Do_not_use_long9        long9;
typedef struct __Reserved_Name__Do_not_use_long10       long10;
typedef struct __Reserved_Name__Do_not_use_long11       long11;
typedef struct __Reserved_Name__Do_not_use_long12       long12;
typedef struct __Reserved_Name__Do_not_use_long13       long13;
typedef struct __Reserved_Name__Do_not_use_long14       long14;
typedef struct __Reserved_Name__Do_not_use_long15       long15;
typedef struct __Reserved_Name__Do_not_use_long32       long32;
typedef struct __Reserved_Name__Do_not_use_ulong5       ulong5;
typedef struct __Reserved_Name__Do_not_use_ulong6       ulong6;
typedef struct __Reserved_Name__Do_not_use_ulong7       ulong7;
typedef struct __Reserved_Name__Do_not_use_ulong9       ulong9;
typedef struct __Reserved_Name__Do_not_use_ulong10      ulong10;
typedef struct __Reserved_Name__Do_not_use_ulong11      ulong11;
typedef struct __Reserved_Name__Do_not_use_ulong12      ulong12;
typedef struct __Reserved_Name__Do_not_use_ulong13      ulong13;
typedef struct __Reserved_Name__Do_not_use_ulong14      ulong14;
typedef struct __Reserved_Name__Do_not_use_ulong15      ulong15;
typedef struct __Reserved_Name__Do_not_use_ulong32      ulong32;
typedef struct __Reserved_Name__Do_not_use_quad5        quad5;
typedef struct __Reserved_Name__Do_not_use_quad6        quad6;
typedef struct __Reserved_Name__Do_not_use_quad7        quad7;
typedef struct __Reserved_Name__Do_not_use_quad9        quad9;
typedef struct __Reserved_Name__Do_not_use_quad10       quad10;
typedef struct __Reserved_Name__Do_not_use_quad11       quad11;
typedef struct __Reserved_Name__Do_not_use_quad12       quad12;
typedef struct __Reserved_Name__Do_not_use_quad13       quad13;
typedef struct __Reserved_Name__Do_not_use_quad14       quad14;
typedef struct __Reserved_Name__Do_not_use_quad15       quad15;
typedef struct __Reserved_Name__Do_not_use_quad32       quad32;
typedef struct __Reserved_Name__Do_not_use_half5        half5;
typedef struct __Reserved_Name__Do_not_use_half6        half6;
typedef struct __Reserved_Name__Do_not_use_half7        half7;
typedef struct __Reserved_Name__Do_not_use_half9        half9;
typedef struct __Reserved_Name__Do_not_use_half10       half10;
typedef struct __Reserved_Name__Do_not_use_half11       half11;
typedef struct __Reserved_Name__Do_not_use_half12       half12;
typedef struct __Reserved_Name__Do_not_use_half13       half13;
typedef struct __Reserved_Name__Do_not_use_half14       half14;
typedef struct __Reserved_Name__Do_not_use_half15       half15;
typedef struct __Reserved_Name__Do_not_use_half32       half32;



typedef __typeof__(((int*)0)-((int*)0)) ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
typedef __SIZE_TYPE__ uintptr_t;
typedef __PTRDIFF_TYPE__ intptr_t;
typedef size_t       event_t;

#define __ALWAYS_INLINE__ __attribute__((__always_inline__))
#define __OVERLOAD_INLINE__ __attribute__((__overloadable__, __always_inline__))
#define __OVERLOAD__ __attribute__((__overloadable__))
#define __NO_DUPLICATE__ __attribute__((__no_duplicate__))

// Macro machinery for C-based type overloading of builtin functions

// Returns float or double, one float or double input.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1FD(name) float __OVERLOAD__ name(float x); \
float2 __OVERLOAD__ name(float2 x); \
float3 __OVERLOAD__ name(float3 x); \
float4 __OVERLOAD__ name(float4 x); \
float8 __OVERLOAD__ name(float8 x); \
float16 __OVERLOAD__ name(float16 x); \
double __OVERLOAD__ name(double x); \
double2 __OVERLOAD__ name(double2 x); \
double3 __OVERLOAD__ name(double3 x); \
double4 __OVERLOAD__ name(double4 x); \
double8 __OVERLOAD__ name(double8 x); \
double16 __OVERLOAD__ name(double16 x);
#else
#define __CLFN_FD_1FD(name) float __OVERLOAD__ name(float x); \
float2 __OVERLOAD__ name(float2 x); \
float3 __OVERLOAD__ name(float3 x); \
float4 __OVERLOAD__ name(float4 x); \
float8 __OVERLOAD__ name(float8 x); \
float16 __OVERLOAD__ name(float16 x);
#endif


#if defined(__FAST_RELAXED_MATH__)
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1FD_FAST_RELAX(_name, _native_name, _default_name) \
inline float __OVERLOAD__ _name(float x) { return _native_name(x); } \
inline float2 __OVERLOAD__ _name(float2 x) { return _native_name(x); } \
inline float3 __OVERLOAD__ _name(float3 x) { return _native_name(x); } \
inline float4 __OVERLOAD__ _name(float4 x) { return _native_name(x); } \
inline float8 __OVERLOAD__ _name(float8 x) { return _native_name(x); } \
inline float16 __OVERLOAD__ _name(float16 x){ return _native_name(x); } \
inline double __OVERLOAD__ _name(double x) { return _default_name(x); } \
inline double2 __OVERLOAD__ _name(double2 x) { return _default_name(x); } \
inline double3 __OVERLOAD__ _name(double3 x) { return _default_name(x); } \
inline double4 __OVERLOAD__ _name(double4 x) { return _default_name(x); } \
inline double8 __OVERLOAD__ _name(double8 x) { return _default_name(x); } \
inline double16 __OVERLOAD__ _name(double16 x) { return _default_name(x); }
#else
#define __CLFN_FD_1FD_FAST_RELAX(_name, _native_name, _default_name) \
inline float __OVERLOAD__ _name(float x) { return _native_name(x); } \
inline float2 __OVERLOAD__ _name(float2 x) { return _native_name(x); } \
inline float3 __OVERLOAD__ _name(float3 x) { return _native_name(x); } \
inline float4 __OVERLOAD__ _name(float4 x) { return _native_name(x); } \
inline float8 __OVERLOAD__ _name(float8 x) { return _native_name(x); } \
inline float16 __OVERLOAD__ _name(float16 x){ return _native_name(x); }
#endif
#else //! __FAST_RELAXED_MATH__
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1FD_FAST_RELAX(_name, _native_name, _default_name) \
inline float __OVERLOAD__ _name(float x) { return _default_name(x); } \
inline float2 __OVERLOAD__ _name(float2 x) { return _default_name(x); } \
inline float3 __OVERLOAD__ _name(float3 x) { return _default_name(x); } \
inline float4 __OVERLOAD__ _name(float4 x) { return _default_name(x); } \
inline float8 __OVERLOAD__ _name(float8 x) { return _default_name(x); } \
inline float16 __OVERLOAD__ _name(float16 x){ return _default_name(x); } \
inline double __OVERLOAD__ _name(double x) { return _default_name(x); } \
inline double2 __OVERLOAD__ _name(double2 x) { return _default_name(x); } \
inline double3 __OVERLOAD__ _name(double3 x) { return _default_name(x); } \
inline double4 __OVERLOAD__ _name(double4 x) { return _default_name(x); } \
inline double8 __OVERLOAD__ _name(double8 x) { return _default_name(x); } \
inline double16 __OVERLOAD__ _name(double16 x) { return _default_name(x); }
#else
#define __CLFN_FD_1FD_FAST_RELAX(_name, _native_name, _default_name) \
inline float __OVERLOAD__ _name(float x) { return _default_name(x); } \
inline float2 __OVERLOAD__ _name(float2 x) { return _default_name(x); } \
inline float3 __OVERLOAD__ _name(float3 x) { return _default_name(x); } \
inline float4 __OVERLOAD__ _name(float4 x) { return _default_name(x); } \
inline float8 __OVERLOAD__ _name(float8 x) { return _default_name(x); } \
inline float16 __OVERLOAD__ _name(float16 x){ return _default_name(x); }
#endif
#endif

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1FD_MODD(name) float __OVERLOAD__ name(float x); \
float __OVERLOAD__ name(float2 x); \
float __OVERLOAD__ name(float3 x); \
float __OVERLOAD__ name(float4 x); \
float __OVERLOAD__ name(float8 x); \
float __OVERLOAD__ name(float16 x); \
double __OVERLOAD__ name(double x); \
double __OVERLOAD__ name(double2 x); \
double __OVERLOAD__ name(double3 x); \
double __OVERLOAD__ name(double4 x); \
double __OVERLOAD__ name(double8 x); \
double __OVERLOAD__ name(double16 x);
#else
#define __CLFN_FD_1FD_MODD(name) float __OVERLOAD__ name(float x); \
float __OVERLOAD__ name(float2 x); \
float __OVERLOAD__ name(float3 x); \
float __OVERLOAD__ name(float4 x); \
float __OVERLOAD__ name(float8 x); \
float __OVERLOAD__ name(float16 x);
#endif

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_I_1FD(name) int __OVERLOAD__ name(float x); \
int2 __OVERLOAD__ name(float2 x); \
int3 __OVERLOAD__ name(float3 x); \
int4 __OVERLOAD__ name(float4 x); \
int8 __OVERLOAD__ name(float8 x); \
int16 __OVERLOAD__ name(float16 x); \
int __OVERLOAD__ name(double x); \
int2 __OVERLOAD__ name(double2 x); \
int3 __OVERLOAD__ name(double3 x); \
int4 __OVERLOAD__ name(double4 x); \
int8 __OVERLOAD__ name(double8 x); \
int16 __OVERLOAD__ name(double16 x);
#else
#define __CLFN_I_1FD(name) int __OVERLOAD__ name(float x); \
int2 __OVERLOAD__ name(float2 x); \
int3 __OVERLOAD__ name(float3 x); \
int4 __OVERLOAD__ name(float4 x); \
int8 __OVERLOAD__ name(float8 x); \
int16 __OVERLOAD__ name(float16 x);
#endif

// Returns float, float inputs, up to size 4.
#define __CLFN_1F_2F(name) float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float2 y); \
float3 __OVERLOAD__ name(float3 x, float3 y); \
float4 __OVERLOAD__ name(float4 x, float4 y);

// Returns float, float inputs, up to size 4.
#define __CLFN_1F_2F_MODD(name) float __OVERLOAD__ name(float x, float y); \
float __OVERLOAD__ name(float2 x, float2 y); \
float __OVERLOAD__ name(float3 x, float3 y); \
float __OVERLOAD__ name(float4 x, float4 y);

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_1FD_2FD_MODD(name) float __OVERLOAD__ name(float x, float y); \
float __OVERLOAD__ name(float2 x, float2 y); \
float __OVERLOAD__ name(float3 x, float3 y); \
float __OVERLOAD__ name(float4 x, float4 y); \
double __OVERLOAD__ name(double x, double y); \
double __OVERLOAD__ name(double2 x, double2 y); \
double __OVERLOAD__ name(double3 x, double3 y); \
double __OVERLOAD__ name(double4 x, double4 y);
#else
#define __CLFN_1FD_2FD_MODD(name) float __OVERLOAD__ name(float x, float y); \
float __OVERLOAD__ name(float2 x, float2 y); \
float __OVERLOAD__ name(float3 x, float3 y); \
float __OVERLOAD__ name(float4 x, float4 y);
#endif

// Returns float, float inputs, up to size 4.
#define __CLFN_F_1F_MODD4(name) float __OVERLOAD__ name(float x ); \
float __OVERLOAD__ name(float2 x); \
float __OVERLOAD__ name(float3 x); \
float __OVERLOAD__ name(float4 x);

// Returns float or double, two float or double input. Only up to size 4.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_2FD_MODD4(name) float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float2 y); \
float3 __OVERLOAD__ name(float3 x, float3 y); \
float4 __OVERLOAD__ name(float4 x, float4 y); \
double __OVERLOAD__ name(double x, double y); \
double2 __OVERLOAD__ name(double2 x, double2 y); \
double3 __OVERLOAD__ name(double3 x, double3 y); \
double4 __OVERLOAD__ name(double4 x, double4 y);
#else
#define __CLFN_FD_2FD_MODD4(name) float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float2 y); \
float3 __OVERLOAD__ name(float3 x, float3 y); \
float4 __OVERLOAD__ name(float4 x, float4 y);
#endif

// Returns float or double, one float or double input. Only up to size 4.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1FD_MODD4(name) float __OVERLOAD__ name(float x); \
float2 __OVERLOAD__ name(float2 x); \
float3 __OVERLOAD__ name(float3 x); \
float4 __OVERLOAD__ name(float4 x); \
double __OVERLOAD__ name(double x); \
double2 __OVERLOAD__ name(double2 x); \
double3 __OVERLOAD__ name(double3 x); \
double4 __OVERLOAD__ name(double4 x);
#else
#define __CLFN_FD_1FD_MODD4(name) float __OVERLOAD__ name(float x); \
float2 __OVERLOAD__ name(float2 x); \
float3 __OVERLOAD__ name(float3 x); \
float4 __OVERLOAD__ name(float4 x);
#endif

// Returns float or double, one uing or ulong input.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1UIL(name) float __OVERLOAD__ name(uint x); \
float2 __OVERLOAD__ name(uint2 x); \
float3 __OVERLOAD__ name(uint3 x); \
float4 __OVERLOAD__ name(uint4 x); \
float8 __OVERLOAD__ name(uint8 x); \
float16 __OVERLOAD__ name(uint16 x); \
double __OVERLOAD__ name(ulong x); \
double2 __OVERLOAD__ name(ulong2 x); \
double3 __OVERLOAD__ name(ulong3 x); \
double4 __OVERLOAD__ name(ulong4 x); \
double8 __OVERLOAD__ name(ulong8 x); \
double16 __OVERLOAD__ name(ulong16 x);
#else
#define __CLFN_FD_1UIL(name) float __OVERLOAD__ name(uint x); \
float2 __OVERLOAD__ name(uint2 x); \
float3 __OVERLOAD__ name(uint3 x); \
float4 __OVERLOAD__ name(uint4 x); \
float8 __OVERLOAD__ name(uint8 x); \
float16 __OVERLOAD__ name(uint16 x);
#endif

// Returns int or long, one float or double input.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_IL_1FD(name) int __OVERLOAD__ name(float x); \
int2 __OVERLOAD__ name(float2 x); \
int3 __OVERLOAD__ name(float3 x); \
int4 __OVERLOAD__ name(float4 x); \
int8 __OVERLOAD__ name(float8 x); \
int16 __OVERLOAD__ name(float16 x); \
long __OVERLOAD__ name(double x); \
long2 __OVERLOAD__ name(double2 x); \
long3 __OVERLOAD__ name(double3 x); \
long4 __OVERLOAD__ name(double4 x); \
long8 __OVERLOAD__ name(double8 x); \
long16 __OVERLOAD__ name(double16 x);
#else
#define __CLFN_IL_1FD(name) int __OVERLOAD__ name(float x); \
int2 __OVERLOAD__ name(float2 x); \
int3 __OVERLOAD__ name(float3 x); \
int4 __OVERLOAD__ name(float4 x); \
int8 __OVERLOAD__ name(float8 x); \
int16 __OVERLOAD__ name(float16 x);
#endif

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_IL_1FD_MODD(name) int __OVERLOAD__ name(float x); \
int2 __OVERLOAD__ name(float2 x); \
int3 __OVERLOAD__ name(float3 x); \
int4 __OVERLOAD__ name(float4 x); \
int8 __OVERLOAD__ name(float8 x); \
int16 __OVERLOAD__ name(float16 x); \
int __OVERLOAD__ name(double x); \
long2 __OVERLOAD__ name(double2 x); \
long3 __OVERLOAD__ name(double3 x); \
long4 __OVERLOAD__ name(double4 x); \
long8 __OVERLOAD__ name(double8 x); \
long16 __OVERLOAD__ name(double16 x);
#else
#define __CLFN_IL_1FD_MODD(name) int __OVERLOAD__ name(float x); \
int2 __OVERLOAD__ name(float2 x); \
int3 __OVERLOAD__ name(float3 x); \
int4 __OVERLOAD__ name(float4 x); \
int8 __OVERLOAD__ name(float8 x); \
int16 __OVERLOAD__ name(float16 x);
#endif


// Returns same as the input. Accepts char,uchar,short,ushort,
// long,ulong,int,unint.
#define __CLFN_CSIL_1CSIL(name) char __OVERLOAD__ name(char x); \
char2 __OVERLOAD__ name(char2 x); \
char3 __OVERLOAD__ name(char3 x); \
char4 __OVERLOAD__ name(char4 x); \
char8 __OVERLOAD__ name(char8 x); \
char16 __OVERLOAD__ name(char16 x); \
uchar __OVERLOAD__ name(uchar x); \
uchar2 __OVERLOAD__ name(uchar2 x); \
uchar3 __OVERLOAD__ name(uchar3 x); \
uchar4 __OVERLOAD__ name(uchar4 x); \
uchar8 __OVERLOAD__ name(uchar8 x); \
uchar16 __OVERLOAD__ name(uchar16 x); \
int __OVERLOAD__ name(int x); \
int2 __OVERLOAD__ name(int2 x); \
int3 __OVERLOAD__ name(int3 x); \
int4 __OVERLOAD__ name(int4 x); \
int8 __OVERLOAD__ name(int8 x); \
int16 __OVERLOAD__ name(int16 x); \
uint __OVERLOAD__ name(uint x); \
uint2 __OVERLOAD__ name(uint2 x); \
uint3 __OVERLOAD__ name(uint3 x); \
uint4 __OVERLOAD__ name(uint4 x); \
uint8 __OVERLOAD__ name(uint8 x); \
uint16 __OVERLOAD__ name(uint16 x); \
short __OVERLOAD__ name(short x); \
short2 __OVERLOAD__ name(short2 x); \
short3 __OVERLOAD__ name(short3 x); \
short4 __OVERLOAD__ name(short4 x); \
short8 __OVERLOAD__ name(short8 x); \
short16 __OVERLOAD__ name(short16 x); \
ushort __OVERLOAD__ name(ushort x); \
ushort2 __OVERLOAD__ name(ushort2 x); \
ushort3 __OVERLOAD__ name(ushort3 x); \
ushort4 __OVERLOAD__ name(ushort4 x); \
ushort8 __OVERLOAD__ name(ushort8 x); \
ushort16 __OVERLOAD__ name(ushort16 x); \
long __OVERLOAD__ name(long x); \
long2 __OVERLOAD__ name(long2 x); \
long3 __OVERLOAD__ name(long3 x); \
long4 __OVERLOAD__ name(long4 x); \
long8 __OVERLOAD__ name(long8 x); \
long16 __OVERLOAD__ name(long16 x); \
ulong __OVERLOAD__ name(ulong x); \
ulong2 __OVERLOAD__ name(ulong2 x); \
ulong3 __OVERLOAD__ name(ulong3 x); \
ulong4 __OVERLOAD__ name(ulong4 x); \
ulong8 __OVERLOAD__ name(ulong8 x); \
ulong16 __OVERLOAD__ name(ulong16 x);

// Returns same as the input but unsigned. Accepts char,uchar,short,ushort,
// long,ulong,int,unint.
#define __CLFN_UCSIL_1CSIL(name) uchar __OVERLOAD__ name(char x); \
uchar2 __OVERLOAD__ name(char2 x); \
uchar3 __OVERLOAD__ name(char3 x); \
uchar4 __OVERLOAD__ name(char4 x); \
uchar8 __OVERLOAD__ name(char8 x); \
uchar16 __OVERLOAD__ name(char16 x); \
uchar __OVERLOAD__ name(uchar x); \
uchar2 __OVERLOAD__ name(uchar2 x); \
uchar3 __OVERLOAD__ name(uchar3 x); \
uchar4 __OVERLOAD__ name(uchar4 x); \
uchar8 __OVERLOAD__ name(uchar8 x); \
uchar16 __OVERLOAD__ name(uchar16 x); \
uint __OVERLOAD__ name(int x); \
uint2 __OVERLOAD__ name(int2 x); \
uint3 __OVERLOAD__ name(int3 x); \
uint4 __OVERLOAD__ name(int4 x); \
uint8 __OVERLOAD__ name(int8 x); \
uint16 __OVERLOAD__ name(int16 x); \
uint __OVERLOAD__ name(uint x); \
uint2 __OVERLOAD__ name(uint2 x); \
uint3 __OVERLOAD__ name(uint3 x); \
uint4 __OVERLOAD__ name(uint4 x); \
uint8 __OVERLOAD__ name(uint8 x); \
uint16 __OVERLOAD__ name(uint16 x); \
ushort __OVERLOAD__ name(short x); \
ushort2 __OVERLOAD__ name(short2 x); \
ushort3 __OVERLOAD__ name(short3 x); \
ushort4 __OVERLOAD__ name(short4 x); \
ushort8 __OVERLOAD__ name(short8 x); \
ushort16 __OVERLOAD__ name(short16 x); \
ushort __OVERLOAD__ name(ushort x); \
ushort2 __OVERLOAD__ name(ushort2 x); \
ushort3 __OVERLOAD__ name(ushort3 x); \
ushort4 __OVERLOAD__ name(ushort4 x); \
ushort8 __OVERLOAD__ name(ushort8 x); \
ushort16 __OVERLOAD__ name(ushort16 x); \
ulong __OVERLOAD__ name(long x); \
ulong2 __OVERLOAD__ name(long2 x); \
ulong3 __OVERLOAD__ name(long3 x); \
ulong4 __OVERLOAD__ name(long4 x); \
ulong8 __OVERLOAD__ name(long8 x); \
ulong16 __OVERLOAD__ name(long16 x); \
ulong __OVERLOAD__ name(ulong x); \
ulong2 __OVERLOAD__ name(ulong2 x); \
ulong3 __OVERLOAD__ name(ulong3 x); \
ulong4 __OVERLOAD__ name(ulong4 x); \
ulong8 __OVERLOAD__ name(ulong8 x); \
ulong16 __OVERLOAD__ name(ulong16 x);

// Returns float or double, two float or double input.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1F(name) float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float2 y); \
float3 __OVERLOAD__ name(float3 x, float3 y); \
float4 __OVERLOAD__ name(float4 x, float4 y); \
float8 __OVERLOAD__ name(float8 x, float8 y); \
float16 __OVERLOAD__ name(float16 x, float16 y); \
double __OVERLOAD__ name(double x, double y); \
double2 __OVERLOAD__ name(double2 x, double2 y); \
double3 __OVERLOAD__ name(double3 x, double3 y); \
double4 __OVERLOAD__ name(double4 x, double4 y); \
double8 __OVERLOAD__ name(double8 x, double8 y); \
double16 __OVERLOAD__ name(double16 x, double16 y);
#else
#define __CLFN_FD_1F(name) float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float2 y); \
float3 __OVERLOAD__ name(float3 x, float3 y); \
float4 __OVERLOAD__ name(float4 x, float4 y); \
float8 __OVERLOAD__ name(float8 x, float8 y); \
float16 __OVERLOAD__ name(float16 x, float16 y);
#endif

// Returns float or double, two float or double input.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1FD_1I(name) float __OVERLOAD__ name(float x, int y); \
float2 __OVERLOAD__ name(float2 x, int2 y); \
float3 __OVERLOAD__ name(float3 x, int3 y); \
float4 __OVERLOAD__ name(float4 x, int4 y); \
float8 __OVERLOAD__ name(float8 x, int8 y); \
float16 __OVERLOAD__ name(float16 x, int16 y); \
float2 __OVERLOAD__ name(float2 x, int y); \
float3 __OVERLOAD__ name(float3 x, int y); \
float4 __OVERLOAD__ name(float4 x, int y); \
float8 __OVERLOAD__ name(float8 x, int y); \
float16 __OVERLOAD__ name(float16 x, int y); \
double __OVERLOAD__ name(double x, int y); \
double2 __OVERLOAD__ name(double2 x, int2 y); \
double3 __OVERLOAD__ name(double3 x, int3 y); \
double4 __OVERLOAD__ name(double4 x, int4 y); \
double8 __OVERLOAD__ name(double8 x, int8 y); \
double16 __OVERLOAD__ name(double16 x, int16 y); \
double2 __OVERLOAD__ name(double2 x, int y); \
double3 __OVERLOAD__ name(double3 x, int y); \
double4 __OVERLOAD__ name(double4 x, int y); \
double8 __OVERLOAD__ name(double8 x, int y); \
double16 __OVERLOAD__ name(double16 x, int y);
#else
#define __CLFN_FD_1FD_1I(name) float __OVERLOAD__ name(float x, int y); \
float2 __OVERLOAD__ name(float2 x, int2 y); \
float3 __OVERLOAD__ name(float3 x, int3 y); \
float4 __OVERLOAD__ name(float4 x, int4 y); \
float8 __OVERLOAD__ name(float8 x, int8 y); \
float16 __OVERLOAD__ name(float16 x, int16 y); \
float2 __OVERLOAD__ name(float2 x, int y); \
float3 __OVERLOAD__ name(float3 x, int y); \
float4 __OVERLOAD__ name(float4 x, int y); \
float8 __OVERLOAD__ name(float8 x, int y); \
float16 __OVERLOAD__ name(float16 x, int y);
#endif

// Returns float or double, one float or double input, and one pointer to
// float or double.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1FD_1PFD(name) float __OVERLOAD__ name(float x, float* y); \
float2 __OVERLOAD__ name(float2 x, float2* y); \
float3 __OVERLOAD__ name(float3 x, float3* y); \
float4 __OVERLOAD__ name(float4 x, float4* y); \
float8 __OVERLOAD__ name(float8 x, float8* y); \
float16 __OVERLOAD__ name(float16 x, float16* y); \
float __OVERLOAD__ name(float x, __global float* y); \
float2 __OVERLOAD__ name(float2 x, __global float2* y); \
float3 __OVERLOAD__ name(float3 x, __global float3* y); \
float4 __OVERLOAD__ name(float4 x, __global float4* y); \
float8 __OVERLOAD__ name(float8 x, __global float8* y); \
float16 __OVERLOAD__ name(float16 x, __global float16* y); \
float __OVERLOAD__ name(float x, __local float* y); \
float2 __OVERLOAD__ name(float2 x, __local float2* y); \
float3 __OVERLOAD__ name(float3 x, __local float3* y); \
float4 __OVERLOAD__ name(float4 x, __local float4* y); \
float8 __OVERLOAD__ name(float8 x, __local float8* y); \
float16 __OVERLOAD__ name(float16 x, __local float16* y); \
double __OVERLOAD__ name(double x, double* y); \
double2 __OVERLOAD__ name(double2 x, double2* y); \
double3 __OVERLOAD__ name(double3 x, double3* y); \
double4 __OVERLOAD__ name(double4 x, double4* y); \
double8 __OVERLOAD__ name(double8 x, double8* y); \
double16 __OVERLOAD__ name(double16 x, double16* y); \
double __OVERLOAD__ name(double x, __global double* y); \
double2 __OVERLOAD__ name(double2 x, __global double2* y); \
double3 __OVERLOAD__ name(double3 x, __global double3* y); \
double4 __OVERLOAD__ name(double4 x, __global double4* y); \
double8 __OVERLOAD__ name(double8 x, __global double8* y); \
double16 __OVERLOAD__ name(double16 x, __global double16* y); \
double __OVERLOAD__ name(double x, __local double* y); \
double2 __OVERLOAD__ name(double2 x, __local double2* y); \
double3 __OVERLOAD__ name(double3 x, __local double3* y); \
double4 __OVERLOAD__ name(double4 x, __local double4* y); \
double8 __OVERLOAD__ name(double8 x, __local double8* y); \
double16 __OVERLOAD__ name(double16 x, __local double16* y);
#else
#define __CLFN_FD_1FD_1PFD(name) float __OVERLOAD__ name(float x, float* y); \
float2 __OVERLOAD__ name(float2 x, float2* y); \
float3 __OVERLOAD__ name(float3 x, float3* y); \
float4 __OVERLOAD__ name(float4 x, float4* y); \
float8 __OVERLOAD__ name(float8 x, float8* y); \
float16 __OVERLOAD__ name(float16 x, float16* y); \
float __OVERLOAD__ name(float x, __global float* y); \
float2 __OVERLOAD__ name(float2 x, __global float2* y); \
float3 __OVERLOAD__ name(float3 x, __global float3* y); \
float4 __OVERLOAD__ name(float4 x, __global float4* y); \
float8 __OVERLOAD__ name(float8 x, __global float8* y); \
float16 __OVERLOAD__ name(float16 x, __global float16* y); \
float __OVERLOAD__ name(float x, __local float* y); \
float2 __OVERLOAD__ name(float2 x, __local float2* y); \
float3 __OVERLOAD__ name(float3 x, __local float3* y); \
float4 __OVERLOAD__ name(float4 x, __local float4* y); \
float8 __OVERLOAD__ name(float8 x, __local float8* y); \
float16 __OVERLOAD__ name(float16 x, __local float16* y);
#endif

// Returns float or double, one float or double input, and one pointer to
// int.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_1FD_1PI(name) float __OVERLOAD__ name(float x, int* y); \
float2 __OVERLOAD__ name(float2 x, int2* y); \
float3 __OVERLOAD__ name(float3 x, int3* y); \
float4 __OVERLOAD__ name(float4 x, int4* y); \
float8 __OVERLOAD__ name(float8 x, int8* y); \
float16 __OVERLOAD__ name(float16 x, int16* y); \
float __OVERLOAD__ name(float x, __global int* y); \
float2 __OVERLOAD__ name(float2 x, __global int2* y); \
float3 __OVERLOAD__ name(float3 x, __global int3* y); \
float4 __OVERLOAD__ name(float4 x, __global int4* y); \
float8 __OVERLOAD__ name(float8 x, __global int8* y); \
float16 __OVERLOAD__ name(float16 x, __global int16* y); \
float __OVERLOAD__ name(float x, __local int* y); \
float2 __OVERLOAD__ name(float2 x, __local int2* y); \
float3 __OVERLOAD__ name(float3 x, __local int3* y); \
float4 __OVERLOAD__ name(float4 x, __local int4* y); \
float8 __OVERLOAD__ name(float8 x, __local int8* y); \
float16 __OVERLOAD__ name(float16 x, __local int16* y); \
double __OVERLOAD__ name(double x, int* y); \
double2 __OVERLOAD__ name(double2 x, int2* y); \
double3 __OVERLOAD__ name(double3 x, int3* y); \
double4 __OVERLOAD__ name(double4 x, int4* y); \
double8 __OVERLOAD__ name(double8 x, int8* y); \
double16 __OVERLOAD__ name(double16 x, int16* y); \
double __OVERLOAD__ name(double x, __global int* y); \
double2 __OVERLOAD__ name(double2 x, __global int2* y); \
double3 __OVERLOAD__ name(double3 x, __global int3* y); \
double4 __OVERLOAD__ name(double4 x, __global int4* y); \
double8 __OVERLOAD__ name(double8 x, __global int8* y); \
double16 __OVERLOAD__ name(double16 x, __global int16* y); \
double __OVERLOAD__ name(double x, __local int* y); \
double2 __OVERLOAD__ name(double2 x, __local int2* y); \
double3 __OVERLOAD__ name(double3 x, __local int3* y); \
double4 __OVERLOAD__ name(double4 x, __local int4* y); \
double8 __OVERLOAD__ name(double8 x, __local int8* y); \
double16 __OVERLOAD__ name(double16 x, __local int16* y);
#else
#define __CLFN_FD_1FD_1PI(name) float __OVERLOAD__ name(float x, int* y); \
float2 __OVERLOAD__ name(float2 x, int2* y); \
float3 __OVERLOAD__ name(float3 x, int3* y); \
float4 __OVERLOAD__ name(float4 x, int4* y); \
float8 __OVERLOAD__ name(float8 x, int8* y); \
float16 __OVERLOAD__ name(float16 x, int16* y); \
float __OVERLOAD__ name(float x, __global int* y); \
float2 __OVERLOAD__ name(float2 x, __global int2* y); \
float3 __OVERLOAD__ name(float3 x, __global int3* y); \
float4 __OVERLOAD__ name(float4 x, __global int4* y); \
float8 __OVERLOAD__ name(float8 x, __global int8* y); \
float16 __OVERLOAD__ name(float16 x, __global int16* y); \
float __OVERLOAD__ name(float x, __local int* y); \
float2 __OVERLOAD__ name(float2 x, __local int2* y); \
float3 __OVERLOAD__ name(float3 x, __local int3* y); \
float4 __OVERLOAD__ name(float4 x, __local int4* y); \
float8 __OVERLOAD__ name(float8 x, __local int8* y); \
float16 __OVERLOAD__ name(float16 x, __local int16* y);
#endif

// Returns float or double, two float or double input, and one pointer to
// int.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_2FD_1PI(name) float __OVERLOAD__ name(float x, float y, int* z); \
float2 __OVERLOAD__ name(float2 x, float2 y, int2* z); \
float3 __OVERLOAD__ name(float3 x, float3 y, int3* z); \
float4 __OVERLOAD__ name(float4 x, float4 y, int4* z); \
float8 __OVERLOAD__ name(float8 x, float8 y, int8* z); \
float16 __OVERLOAD__ name(float16 x, float16 y, int16* z); \
float __OVERLOAD__ name(float x, float y, __global int* z); \
float2 __OVERLOAD__ name(float2 x, float2 y, __global int2* z); \
float3 __OVERLOAD__ name(float3 x, float3 y, __global int3* z); \
float4 __OVERLOAD__ name(float4 x, float4 y, __global int4* z); \
float8 __OVERLOAD__ name(float8 x, float8 y, __global int8* z); \
float16 __OVERLOAD__ name(float16 x, float16 y, __global int16* z); \
float __OVERLOAD__ name(float x, float y, __local int* z); \
float2 __OVERLOAD__ name(float2 x, float2 y, __local int2* z); \
float3 __OVERLOAD__ name(float3 x, float3 y, __local int3* z); \
float4 __OVERLOAD__ name(float4 x, float4 y, __local int4* z); \
float8 __OVERLOAD__ name(float8 x, float8 y, __local int8* z); \
float16 __OVERLOAD__ name(float16 x, float16 y, __local int16* z); \
double __OVERLOAD__ name(double x, double y, int* z); \
double2 __OVERLOAD__ name(double2 x, double2 y, int2* z); \
double3 __OVERLOAD__ name(double3 x, double3 y, int3* z); \
double4 __OVERLOAD__ name(double4 x, double4 y, int4* z); \
double8 __OVERLOAD__ name(double8 x, double8 y, int8* z); \
double16 __OVERLOAD__ name(double16 x, double16 y, int16* z); \
double __OVERLOAD__ name(double x, double y, __global int* z); \
double2 __OVERLOAD__ name(double2 x, double2 y, __global int2* z); \
double3 __OVERLOAD__ name(double3 x, double3 y, __global int3* z); \
double4 __OVERLOAD__ name(double4 x, double4 y, __global int4* z); \
double8 __OVERLOAD__ name(double8 x, double8 y, __global int8* z); \
double16 __OVERLOAD__ name(double16 x, double16 y, __global int16* z); \
double __OVERLOAD__ name(double x, double y, __local int* z); \
double2 __OVERLOAD__ name(double2 x, double2 y, __local int2* z); \
double3 __OVERLOAD__ name(double3 x, double3 y, __local int3* z); \
double4 __OVERLOAD__ name(double4 x, double4 y, __local int4* z); \
double8 __OVERLOAD__ name(double8 x, double8 y, __local int8* z); \
double16 __OVERLOAD__ name(double16 x, double16 y, __local int16* z);
#else
#define __CLFN_FD_2FD_1PI(name) float __OVERLOAD__ name(float x, float y, int* z); \
float2 __OVERLOAD__ name(float2 x, float2 y, int2* z); \
float3 __OVERLOAD__ name(float3 x, float3 y, int3* z); \
float4 __OVERLOAD__ name(float4 x, float4 y, int4* z); \
float8 __OVERLOAD__ name(float8 x, float8 y, int8* z); \
float16 __OVERLOAD__ name(float16 x, float16 y, int16* z); \
float __OVERLOAD__ name(float x, float y, __global int* z); \
float2 __OVERLOAD__ name(float2 x, float2 y, __global int2* z); \
float3 __OVERLOAD__ name(float3 x, float3 y, __global int3* z); \
float4 __OVERLOAD__ name(float4 x, float4 y, __global int4* z); \
float8 __OVERLOAD__ name(float8 x, float8 y, __global int8* z); \
float16 __OVERLOAD__ name(float16 x, float16 y, __global int16* z); \
float __OVERLOAD__ name(float x, float y, __local int* z); \
float2 __OVERLOAD__ name(float2 x, float2 y, __local int2* z); \
float3 __OVERLOAD__ name(float3 x, float3 y, __local int3* z); \
float4 __OVERLOAD__ name(float4 x, float4 y, __local int4* z); \
float8 __OVERLOAD__ name(float8 x, float8 y, __local int8* z); \
float16 __OVERLOAD__ name(float16 x, float16 y, __local int16* z);
#endif

// Returns float or double, three float or double input.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_3FD_MOD(name) float __OVERLOAD__ name(float x, float y, float z); \
float2 __OVERLOAD__ name(float2 x, float2 y, float z); \
float3 __OVERLOAD__ name(float3 x, float3 y, float z); \
float4 __OVERLOAD__ name(float4 x, float4 y, float z); \
float8 __OVERLOAD__ name(float8 x, float8 y, float z); \
float16 __OVERLOAD__ name(float16 x, float16 y, float z); \
double __OVERLOAD__ name(double x, double y, double z); \
double2 __OVERLOAD__ name(double2 x, double2 y, double z); \
double3 __OVERLOAD__ name(double3 x, double3 y, double z); \
double4 __OVERLOAD__ name(double4 x, double4 y, double z); \
double8 __OVERLOAD__ name(double8 x, double8 y, double z); \
double16 __OVERLOAD__ name(double16 x, double16 y, double z);
#else
#define __CLFN_FD_3FD_MOD(name) float __OVERLOAD__ name(float x, float y, float z); \
float2 __OVERLOAD__ name(float2 x, float2 y, float z); \
float3 __OVERLOAD__ name(float3 x, float3 y, float z); \
float4 __OVERLOAD__ name(float4 x, float4 y, float z); \
float8 __OVERLOAD__ name(float8 x, float8 y, float z); \
float16 __OVERLOAD__ name(float16 x, float16 y, float z);
#endif

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_3FD(name) float __OVERLOAD__ name(float x, float y, float z); \
float2 __OVERLOAD__ name(float2 x, float2 y, float2 z); \
float3 __OVERLOAD__ name(float3 x, float3 y, float3 z); \
float4 __OVERLOAD__ name(float4 x, float4 y, float4 z); \
float8 __OVERLOAD__ name(float8 x, float8 y, float8 z); \
float16 __OVERLOAD__ name(float16 x, float16 y, float16 z); \
double __OVERLOAD__ name(double x, double y, double z); \
double2 __OVERLOAD__ name(double2 x, double2 y, double2 z); \
double3 __OVERLOAD__ name(double3 x, double3 y, double3 z); \
double4 __OVERLOAD__ name(double4 x, double4 y, double4 z); \
double8 __OVERLOAD__ name(double8 x, double8 y, double8 z); \
double16 __OVERLOAD__ name(double16 x, double16 y, double16 z);
#else
#define __CLFN_FD_3FD(name) float __OVERLOAD__ name(float x, float y, float z); \
float2 __OVERLOAD__ name(float2 x, float2 y, float2 z); \
float3 __OVERLOAD__ name(float3 x, float3 y, float3 z); \
float4 __OVERLOAD__ name(float4 x, float4 y, float4 z); \
float8 __OVERLOAD__ name(float8 x, float8 y, float8 z); \
float16 __OVERLOAD__ name(float16 x, float16 y, float16 z);
#endif

// Returns float or double, two float or double input (possible not vector).
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_2FD(name) float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float2 y); \
float3 __OVERLOAD__ name(float3 x, float3 y); \
float4 __OVERLOAD__ name(float4 x, float4 y); \
float8 __OVERLOAD__ name(float8 x, float8 y); \
float16 __OVERLOAD__ name(float16 x, float16 y); \
double __OVERLOAD__ name(double x, double y); \
double2 __OVERLOAD__ name(double2 x, double2 y); \
double3 __OVERLOAD__ name(double3 x, double3 y); \
double4 __OVERLOAD__ name(double4 x, double4 y); \
double8 __OVERLOAD__ name(double8 x, double8 y); \
double16 __OVERLOAD__ name(double16 x, double16 y);
#else
#define __CLFN_FD_2FD(name) float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float2 y); \
float3 __OVERLOAD__ name(float3 x, float3 y); \
float4 __OVERLOAD__ name(float4 x, float4 y); \
float8 __OVERLOAD__ name(float8 x, float8 y); \
float16 __OVERLOAD__ name(float16 x, float16 y);
#endif

#if defined(__FAST_RELAXED_MATH__)
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_2FD_FAST_RELAX(name, native_name, default_name) \
inline float __OVERLOAD__ name(float x, float y) { return native_name(x,y); } \
inline float2 __OVERLOAD__ name(float2 x, float2 y) { return native_name(x,y); } \
inline float3 __OVERLOAD__ name(float3 x, float3 y) { return native_name(x,y); } \
inline float4 __OVERLOAD__ name(float4 x, float4 y) { return native_name(x,y); } \
inline float8 __OVERLOAD__ name(float8 x, float8 y) { return native_name(x,y); } \
inline float16 __OVERLOAD__ name(float16 x, float16 y){ return native_name(x,y); } \
inline double __OVERLOAD__ name(double x, double y) { return default_name(x,y); } \
inline double2 __OVERLOAD__ name(double2 x, double2 y) { return default_name(x,y); } \
inline double3 __OVERLOAD__ name(double3 x, double3 y) { return default_name(x,y); } \
inline double4 __OVERLOAD__ name(double4 x, double4 y) { return default_name(x,y); } \
inline double8 __OVERLOAD__ name(double8 x, double8 y) { return default_name(x,y); } \
inline double16 __OVERLOAD__ name(double16 x, double16 y) { return default_name(x,y); }
#else
#define __CLFN_FD_2FD_FAST_RELAX(name, native_name, default_name) \
inline float __OVERLOAD__ name(float x, float y) { return native_name(x,y); } \
inline float2 __OVERLOAD__ name(float2 x, float2 y) { return native_name(x,y); } \
inline float3 __OVERLOAD__ name(float3 x, float3 y) { return native_name(x,y); } \
inline float4 __OVERLOAD__ name(float4 x, float4 y) { return native_name(x,y); } \
inline float8 __OVERLOAD__ name(float8 x, float8 y) { return native_name(x,y); } \
inline float16 __OVERLOAD__ name(float16 x, float16 y){ return native_name(x,y); }
#endif
#else //! __FAST_RELAXED_MATH__
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_2FD_FAST_RELAX(name, native_name, default_name) \
inline float __OVERLOAD__ name(float x, float y) { return default_name(x,y); } \
inline float2 __OVERLOAD__ name(float2 x, float2 y) { return default_name(x,y); } \
inline float3 __OVERLOAD__ name(float3 x, float3 y) { return default_name(x,y); } \
inline float4 __OVERLOAD__ name(float4 x, float4 y) { return default_name(x,y); } \
inline float8 __OVERLOAD__ name(float8 x, float8 y) { return default_name(x,y); } \
inline float16 __OVERLOAD__ name(float16 x, float16 y){ return default_name(x,y); } \
inline double __OVERLOAD__ name(double x, double y) { return default_name(x,y); } \
inline double2 __OVERLOAD__ name(double2 x, double2 y) { return default_name(x,y); } \
inline double3 __OVERLOAD__ name(double3 x, double3 y) { return default_name(x,y); } \
inline double4 __OVERLOAD__ name(double4 x, double4 y) { return default_name(x,y); } \
inline double8 __OVERLOAD__ name(double8 x, double8 y) { return default_name(x,y); } \
inline double16 __OVERLOAD__ name(double16 x, double16 y) { return default_name(x,y); }
#else
#define __CLFN_FD_2FD_FAST_RELAX(name, native_name, default_name) \
inline float __OVERLOAD__ name(float x, float y) { return default_name(x,y); } \
inline float2 __OVERLOAD__ name(float2 x, float2 y) { return default_name(x,y); } \
inline float3 __OVERLOAD__ name(float3 x, float3 y) { return default_name(x,y); } \
inline float4 __OVERLOAD__ name(float4 x, float4 y) { return default_name(x,y); } \
inline float8 __OVERLOAD__ name(float8 x, float8 y) { return default_name(x,y); } \
inline float16 __OVERLOAD__ name(float16 x, float16 y){ return default_name(x,y); }
#endif
#endif

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_FD_2FD_EXT(name) float2 __OVERLOAD__ name(float2 x, float y); \
float3 __OVERLOAD__ name(float3 x, float y); \
float4 __OVERLOAD__ name(float4 x, float y); \
float8 __OVERLOAD__ name(float8 x, float y); \
float16 __OVERLOAD__ name(float16 x, float y); \
double2 __OVERLOAD__ name(double2 x, double y); \
double3 __OVERLOAD__ name(double3 x, double y); \
double4 __OVERLOAD__ name(double4 x, double y); \
double8 __OVERLOAD__ name(double8 x, double y); \
double16 __OVERLOAD__ name(double16 x, double y);
#else
#define __CLFN_FD_2FD_EXT(name) float2 __OVERLOAD__ name(float2 x, float y); \
float3 __OVERLOAD__ name(float3 x, float y); \
float4 __OVERLOAD__ name(float4 x, float y); \
float8 __OVERLOAD__ name(float8 x, float y); \
float16 __OVERLOAD__ name(float16 x, float y);
#endif

// Returns int or long, two float or double input.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_IL_2FD(name) int __OVERLOAD__ name(float x, float y); \
int2 __OVERLOAD__ name(float2 x, float2 y); \
int3 __OVERLOAD__ name(float3 x, float3 y); \
int4 __OVERLOAD__ name(float4 x, float4 y); \
int8 __OVERLOAD__ name(float8 x, float8 y); \
int16 __OVERLOAD__ name(float16 x, float16 y); \
int __OVERLOAD__ name(double x, double y); \
long2 __OVERLOAD__ name(double2 x, double2 y); \
long3 __OVERLOAD__ name(double3 x, double3 y); \
long4 __OVERLOAD__ name(double4 x, double4 y); \
long8 __OVERLOAD__ name(double8 x, double8 y); \
long16 __OVERLOAD__ name(double16 x, double16 y);
#else
#define __CLFN_IL_2FD(name) int __OVERLOAD__ name(float x, float y); \
int2 __OVERLOAD__ name(float2 x, float2 y); \
int3 __OVERLOAD__ name(float3 x, float3 y); \
int4 __OVERLOAD__ name(float4 x, float4 y); \
int8 __OVERLOAD__ name(float8 x, float8 y); \
int16 __OVERLOAD__ name(float16 x, float16 y);
#endif

// These macros are for the operations that support SPI types

// Returns float and takes one float.
#define __CLFN_F_1F(name) float __OVERLOAD__ name(float x); \
float2 __OVERLOAD__ name(float2 x); \
float3 __OVERLOAD__ name(float3 x); \
float4 __OVERLOAD__ name(float4 x); \
float8 __OVERLOAD__ name(float8 x); \
float16 __OVERLOAD__ name(float16 x);

// Returns float or double, two float or double input.
#define __CLFN_F_2F(name) float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float2 y); \
float3 __OVERLOAD__ name(float3 x, float3 y); \
float4 __OVERLOAD__ name(float4 x, float4 y); \
float8 __OVERLOAD__ name(float8 x, float8 y); \
float16 __OVERLOAD__ name(float16 x, float16 y);

// Returns uchar,uint, ushort, or ulong,
// and takes two char, uchar, short, ushort, int, uint, long, ulong inputs.
#define __CLFN_UCSIL_2CSIL(name) uchar __OVERLOAD__ name(char x, char y); \
uchar2 __OVERLOAD__ name(char2 x, char2 y); \
uchar3 __OVERLOAD__ name(char3 x, char3 y); \
uchar4 __OVERLOAD__ name(char4 x, char4 y); \
uchar8 __OVERLOAD__ name(char8 x, char8 y); \
uchar16 __OVERLOAD__ name(char16 x, char16 y); \
uchar __OVERLOAD__ name(uchar x, uchar y); \
uchar2 __OVERLOAD__ name(uchar2 x, uchar2 y); \
uchar3 __OVERLOAD__ name(uchar3 x, uchar3 y); \
uchar4 __OVERLOAD__ name(uchar4 x, uchar4 y); \
uchar8 __OVERLOAD__ name(uchar8 x, uchar8 y); \
uchar16 __OVERLOAD__ name(uchar16 x,uchar16 y); \
ushort __OVERLOAD__ name(short x, short y); \
ushort2 __OVERLOAD__ name(short2 x, short2 y); \
ushort3 __OVERLOAD__ name(short3 x, short3 y); \
ushort4 __OVERLOAD__ name(short4 x, short4 y); \
ushort8 __OVERLOAD__ name(short8 x, short8 y); \
ushort16 __OVERLOAD__ name(short16 x, short16 y); \
ushort __OVERLOAD__ name(ushort x, ushort y); \
ushort2 __OVERLOAD__ name(ushort2 x, ushort2 y); \
ushort3 __OVERLOAD__ name(ushort3 x, ushort3 y); \
ushort4 __OVERLOAD__ name(ushort4 x, ushort4 y); \
ushort8 __OVERLOAD__ name(ushort8 x, ushort8 y); \
ushort16 __OVERLOAD__ name(ushort16 x, ushort16 y); \
uint __OVERLOAD__ name(int x, int y); \
uint2 __OVERLOAD__ name(int2 x, int2 y); \
uint3 __OVERLOAD__ name(int3 x, int3 y); \
uint4 __OVERLOAD__ name(int4 x, int4 y); \
uint8 __OVERLOAD__ name(int8 x, int8 y); \
uint16 __OVERLOAD__ name(int16 x, int16 y); \
uint __OVERLOAD__ name(uint x, uint y); \
uint2 __OVERLOAD__ name(uint2 x, uint2 y); \
uint3 __OVERLOAD__ name(uint3 x, uint3 y); \
uint4 __OVERLOAD__ name(uint4 x, uint4 y); \
uint8 __OVERLOAD__ name(uint8 x, uint8 y); \
uint16 __OVERLOAD__ name(uint16 x, uint16 y); \
ulong __OVERLOAD__ name(long x, long y); \
ulong2 __OVERLOAD__ name(long2 x, long2 y); \
ulong3 __OVERLOAD__ name(long3 x, long3 y); \
ulong4 __OVERLOAD__ name(long4 x, long4 y); \
ulong8 __OVERLOAD__ name(long8 x, long8 y); \
ulong16 __OVERLOAD__ name(long16 x, long16 y); \
ulong __OVERLOAD__ name(ulong x, ulong y); \
ulong2 __OVERLOAD__ name(ulong2 x, ulong2 y); \
ulong3 __OVERLOAD__ name(ulong3 x, ulong3 y); \
ulong4 __OVERLOAD__ name(ulong4 x, ulong4 y); \
ulong8 __OVERLOAD__ name(ulong8 x, ulong8 y); \
ulong16 __OVERLOAD__ name(ulong16 x, ulong16 y);

// Returns char, int, short, or long, or the unsigned variety
// and takes two char, uchar, short, ushort, int, uint, long, ulong inputs.
#define __CLFN_ALL(name) char __OVERLOAD__ name(char x, char y); \
char2 __OVERLOAD__ name(char2 x, char2 y); \
char3 __OVERLOAD__ name(char3 x, char3 y); \
char4 __OVERLOAD__ name(char4 x, char4 y); \
char8 __OVERLOAD__ name(char8 x, char8 y); \
char16 __OVERLOAD__ name(char16 x, char16 y); \
uchar __OVERLOAD__ name(uchar x, uchar y); \
uchar2 __OVERLOAD__ name(uchar2 x, uchar2 y); \
uchar3 __OVERLOAD__ name(uchar3 x, uchar3 y); \
uchar4 __OVERLOAD__ name(uchar4 x, uchar4 y); \
uchar8 __OVERLOAD__ name(uchar8 x, uchar8 y); \
uchar16 __OVERLOAD__ name(uchar16 x,uchar16 y); \
short __OVERLOAD__ name(short x, short y); \
short2 __OVERLOAD__ name(short2 x, short2 y); \
short3 __OVERLOAD__ name(short3 x, short3 y); \
short4 __OVERLOAD__ name(short4 x, short4 y); \
short8 __OVERLOAD__ name(short8 x, short8 y); \
short16 __OVERLOAD__ name(short16 x, short16 y); \
ushort __OVERLOAD__ name(ushort x, ushort y); \
ushort2 __OVERLOAD__ name(ushort2 x, ushort2 y); \
ushort3 __OVERLOAD__ name(ushort3 x, ushort3 y); \
ushort4 __OVERLOAD__ name(ushort4 x, ushort4 y); \
ushort8 __OVERLOAD__ name(ushort8 x, ushort8 y); \
ushort16 __OVERLOAD__ name(ushort16 x, ushort16 y); \
int __OVERLOAD__ name(int x, int y); \
int2 __OVERLOAD__ name(int2 x, int2 y); \
int3 __OVERLOAD__ name(int3 x, int3 y); \
int4 __OVERLOAD__ name(int4 x, int4 y); \
int8 __OVERLOAD__ name(int8 x, int8 y); \
int16 __OVERLOAD__ name(int16 x, int16 y); \
uint __OVERLOAD__ name(uint x, uint y); \
uint2 __OVERLOAD__ name(uint2 x, uint2 y); \
uint3 __OVERLOAD__ name(uint3 x, uint3 y); \
uint4 __OVERLOAD__ name(uint4 x, uint4 y); \
uint8 __OVERLOAD__ name(uint8 x, uint8 y); \
uint16 __OVERLOAD__ name(uint16 x, uint16 y); \
long __OVERLOAD__ name(long x, long y); \
long2 __OVERLOAD__ name(long2 x, long2 y); \
long3 __OVERLOAD__ name(long3 x, long3 y); \
long4 __OVERLOAD__ name(long4 x, long4 y); \
long8 __OVERLOAD__ name(long8 x, long8 y); \
long16 __OVERLOAD__ name(long16 x, long16 y); \
ulong __OVERLOAD__ name(ulong x, ulong y); \
ulong2 __OVERLOAD__ name(ulong2 x, ulong2 y); \
ulong3 __OVERLOAD__ name(ulong3 x, ulong3 y); \
ulong4 __OVERLOAD__ name(ulong4 x, ulong4 y); \
ulong8 __OVERLOAD__ name(ulong8 x, ulong8 y); \
ulong16 __OVERLOAD__ name(ulong16 x, ulong16 y);

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_ALL_MODD(name) char __OVERLOAD__ name(char x, char y); \
char2 __OVERLOAD__ name(char2 x, char y); \
char3 __OVERLOAD__ name(char3 x, char y); \
char4 __OVERLOAD__ name(char4 x, char y); \
char8 __OVERLOAD__ name(char8 x, char y); \
char16 __OVERLOAD__ name(char16 x, char y); \
uchar __OVERLOAD__ name(uchar x, uchar y); \
uchar2 __OVERLOAD__ name(uchar2 x, uchar y); \
uchar3 __OVERLOAD__ name(uchar3 x, uchar y); \
uchar4 __OVERLOAD__ name(uchar4 x, uchar y); \
uchar8 __OVERLOAD__ name(uchar8 x, uchar y); \
uchar16 __OVERLOAD__ name(uchar16 x,uchar y); \
short __OVERLOAD__ name(short x, short y); \
short2 __OVERLOAD__ name(short2 x, short y); \
short3 __OVERLOAD__ name(short3 x, short y); \
short4 __OVERLOAD__ name(short4 x, short y); \
short8 __OVERLOAD__ name(short8 x, short y); \
short16 __OVERLOAD__ name(short16 x, short y); \
ushort __OVERLOAD__ name(ushort x, ushort y); \
ushort2 __OVERLOAD__ name(ushort2 x, ushort y); \
ushort3 __OVERLOAD__ name(ushort3 x, ushort y); \
ushort4 __OVERLOAD__ name(ushort4 x, ushort y); \
ushort8 __OVERLOAD__ name(ushort8 x, ushort y); \
ushort16 __OVERLOAD__ name(ushort16 x, ushort y); \
int __OVERLOAD__ name(int x, int y); \
int2 __OVERLOAD__ name(int2 x, int y); \
int3 __OVERLOAD__ name(int3 x, int y); \
int4 __OVERLOAD__ name(int4 x, int y); \
int8 __OVERLOAD__ name(int8 x, int y); \
int16 __OVERLOAD__ name(int16 x, int y); \
uint __OVERLOAD__ name(uint x, uint y); \
uint2 __OVERLOAD__ name(uint2 x, uint y); \
uint3 __OVERLOAD__ name(uint3 x, uint y); \
uint4 __OVERLOAD__ name(uint4 x, uint y); \
uint8 __OVERLOAD__ name(uint8 x, uint y); \
uint16 __OVERLOAD__ name(uint16 x, uint y); \
long __OVERLOAD__ name(long x, long y); \
long2 __OVERLOAD__ name(long2 x, long y); \
long3 __OVERLOAD__ name(long3 x, long y); \
long4 __OVERLOAD__ name(long4 x, long y); \
long8 __OVERLOAD__ name(long8 x, long y); \
long16 __OVERLOAD__ name(long16 x, long y); \
ulong __OVERLOAD__ name(ulong x, ulong y); \
ulong2 __OVERLOAD__ name(ulong2 x, ulong y); \
ulong3 __OVERLOAD__ name(ulong3 x, ulong y); \
ulong4 __OVERLOAD__ name(ulong4 x, ulong y); \
ulong8 __OVERLOAD__ name(ulong8 x, ulong y); \
ulong16 __OVERLOAD__ name(ulong16 x, ulong y); \
float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float y); \
float3 __OVERLOAD__ name(float3 x, float y); \
float4 __OVERLOAD__ name(float4 x, float y); \
float8 __OVERLOAD__ name(float8 x, float y); \
float16 __OVERLOAD__ name(float16 x, float y); \
double __OVERLOAD__ name(double x, double y); \
double2 __OVERLOAD__ name(double2 x, double y); \
double3 __OVERLOAD__ name(double3 x, double y); \
double4 __OVERLOAD__ name(double4 x, double y); \
double8 __OVERLOAD__ name(double8 x, double y); \
double16 __OVERLOAD__ name(double16 x, double y);
#else
#define __CLFN_ALL_MODD(name) char __OVERLOAD__ name(char x, char y); \
char2 __OVERLOAD__ name(char2 x, char y); \
char3 __OVERLOAD__ name(char3 x, char y); \
char4 __OVERLOAD__ name(char4 x, char y); \
char8 __OVERLOAD__ name(char8 x, char y); \
char16 __OVERLOAD__ name(char16 x, char y); \
uchar __OVERLOAD__ name(uchar x, uchar y); \
uchar2 __OVERLOAD__ name(uchar2 x, uchar y); \
uchar3 __OVERLOAD__ name(uchar3 x, uchar y); \
uchar4 __OVERLOAD__ name(uchar4 x, uchar y); \
uchar8 __OVERLOAD__ name(uchar8 x, uchar y); \
uchar16 __OVERLOAD__ name(uchar16 x,uchar y); \
short __OVERLOAD__ name(short x, short y); \
short2 __OVERLOAD__ name(short2 x, short y); \
short3 __OVERLOAD__ name(short3 x, short y); \
short4 __OVERLOAD__ name(short4 x, short y); \
short8 __OVERLOAD__ name(short8 x, short y); \
short16 __OVERLOAD__ name(short16 x, short y); \
ushort __OVERLOAD__ name(ushort x, ushort y); \
ushort2 __OVERLOAD__ name(ushort2 x, ushort y); \
ushort3 __OVERLOAD__ name(ushort3 x, ushort y); \
ushort4 __OVERLOAD__ name(ushort4 x, ushort y); \
ushort8 __OVERLOAD__ name(ushort8 x, ushort y); \
ushort16 __OVERLOAD__ name(ushort16 x, ushort y); \
int __OVERLOAD__ name(int x, int y); \
int2 __OVERLOAD__ name(int2 x, int y); \
int3 __OVERLOAD__ name(int3 x, int y); \
int4 __OVERLOAD__ name(int4 x, int y); \
int8 __OVERLOAD__ name(int8 x, int y); \
int16 __OVERLOAD__ name(int16 x, int y); \
uint __OVERLOAD__ name(uint x, uint y); \
uint2 __OVERLOAD__ name(uint2 x, uint y); \
uint3 __OVERLOAD__ name(uint3 x, uint y); \
uint4 __OVERLOAD__ name(uint4 x, uint y); \
uint8 __OVERLOAD__ name(uint8 x, uint y); \
uint16 __OVERLOAD__ name(uint16 x, uint y); \
long __OVERLOAD__ name(long x, long y); \
long2 __OVERLOAD__ name(long2 x, long y); \
long3 __OVERLOAD__ name(long3 x, long y); \
long4 __OVERLOAD__ name(long4 x, long y); \
long8 __OVERLOAD__ name(long8 x, long y); \
long16 __OVERLOAD__ name(long16 x, long y); \
ulong __OVERLOAD__ name(ulong x, ulong y); \
ulong2 __OVERLOAD__ name(ulong2 x, ulong y); \
ulong3 __OVERLOAD__ name(ulong3 x, ulong y); \
ulong4 __OVERLOAD__ name(ulong4 x, ulong y); \
ulong8 __OVERLOAD__ name(ulong8 x, ulong y); \
ulong16 __OVERLOAD__ name(ulong16 x, ulong y); \
float __OVERLOAD__ name(float x, float y); \
float2 __OVERLOAD__ name(float2 x, float y); \
float3 __OVERLOAD__ name(float3 x, float y); \
float4 __OVERLOAD__ name(float4 x, float y); \
float8 __OVERLOAD__ name(float8 x, float y); \
float16 __OVERLOAD__ name(float16 x, float y);
#endif

#define __CLFN_I3(name) char __OVERLOAD__ name(char x, char y, char z); \
short __OVERLOAD__ name( short x, short y, short z ); \
int __OVERLOAD__ name( int x, int y, int z ); \
long __OVERLOAD__ name( long x, long y, long z ); \
uchar __OVERLOAD__ name( uchar x, uchar y, uchar z ); \
ushort __OVERLOAD__ name( ushort x, ushort y, ushort z ); \
uint __OVERLOAD__ name( uint x, uint y, uint z ); \
ulong __OVERLOAD__ name( ulong x, ulong y, ulong z ); \
char2 __OVERLOAD__ name( char2 x, char2 y, char2 z ); \
short2 __OVERLOAD__ name( short2 x, short2 y, short2 z ); \
int2 __OVERLOAD__ name( int2 x, int2 y, int2 z ); \
long2 __OVERLOAD__ name( long2 x, long2 y, long2 z ); \
uchar2 __OVERLOAD__ name( uchar2 x, uchar2 y, uchar2 z ); \
ushort2 __OVERLOAD__ name( ushort2 x, ushort2 y, ushort2 z ); \
uint2 __OVERLOAD__ name( uint2 x, uint2 y, uint2 z ); \
ulong2 __OVERLOAD__ name( ulong2 x, ulong2 y, ulong2 z ); \
char3 __OVERLOAD__ name( char3 x, char3 y, char3 z ); \
short3 __OVERLOAD__ name( short3 x, short3 y, short3 z ); \
int3 __OVERLOAD__ name( int3 x, int3 y, int3 z ); \
long3 __OVERLOAD__ name( long3 x, long3 y, long3 z ); \
uchar3 __OVERLOAD__ name( uchar3 x, uchar3 y, uchar3 z ); \
ushort3 __OVERLOAD__ name( ushort3 x, ushort3 y, ushort3 z ); \
uint3 __OVERLOAD__ name( uint3 x, uint3 y, uint3 z ); \
ulong3 __OVERLOAD__ name( ulong3 x, ulong3 y, ulong3 z ); \
char4 __OVERLOAD__ name( char4 x, char4 y, char4 z ); \
short4 __OVERLOAD__ name( short4 x, short4 y, short4 z ); \
int4 __OVERLOAD__ name( int4 x, int4 y, int4 z ); \
long4 __OVERLOAD__ name( long4 x, long4 y, long4 z ); \
uchar4 __OVERLOAD__ name( uchar4 x, uchar4 y, uchar4 z ); \
ushort4 __OVERLOAD__ name( ushort4 x, ushort4 y, ushort4 z ); \
uint4 __OVERLOAD__ name( uint4 x, uint4 y, uint4 z ); \
ulong4 __OVERLOAD__ name( ulong4 x, ulong4 y, ulong4 z ); \
char8 __OVERLOAD__ name( char8 x, char8 y, char8 z ); \
short8 __OVERLOAD__ name( short8 x, short8 y, short8 z ); \
int8 __OVERLOAD__ name( int8 x, int8 y, int8 z ); \
long8 __OVERLOAD__ name( long8 x, long8 y, long8 z ); \
uchar8 __OVERLOAD__ name( uchar8 x, uchar8 y, uchar8 z ); \
ushort8 __OVERLOAD__ name( ushort8 x, ushort8 y, ushort8 z ); \
uint8 __OVERLOAD__ name( uint8 x, uint8 y, uint8 z ); \
ulong8 __OVERLOAD__ name( ulong8 x, ulong8 y, ulong8 z ); \
char16 __OVERLOAD__ name( char16 x, char16 y, char16 z ); \
short16 __OVERLOAD__ name( short16 x, short16 y, short16 z ); \
int16 __OVERLOAD__ name( int16 x, int16 y, int16 z ); \
long16 __OVERLOAD__ name( long16 x, long16 y, long16 z ); \
uchar16 __OVERLOAD__ name( uchar16 x, uchar16 y, uchar16 z ); \
ushort16 __OVERLOAD__ name( ushort16 x, ushort16 y, ushort16 z ); \
uint16 __OVERLOAD__ name( uint16 x, uint16 y, uint16 z ); \
ulong16 __OVERLOAD__ name( ulong16 x, ulong16 y, ulong16 z );

#define __CLFN_I_3CSIL(name) int __OVERLOAD__ name(short2 a, short2 b, int c); \
int __OVERLOAD__ name(short2 a, ushort2 b, int c); \
uint __OVERLOAD__ name(ushort2 a, ushort2 b, uint c); \
int2 __OVERLOAD__ name(short4 a, short4 b, int2 c); \
int2 __OVERLOAD__ name(short4 a, ushort4 b, int2 c); \
uint2 __OVERLOAD__ name(ushort4 a, ushort4 b, uint2 c); \
int4 __OVERLOAD__ name(short8 a, short8 b, int4 c); \
int4 __OVERLOAD__ name(short8 a, ushort8 b, int4 c); \
uint4 __OVERLOAD__ name(ushort8 a, ushort8 b, uint4 c); \
int8 __OVERLOAD__ name(short16 a, short16 b, int8 c); \
int8 __OVERLOAD__ name(short16 a, ushort16 b, int8 c); \
uint8 __OVERLOAD__ name(ushort16 a, ushort16 b, uint8 c);

// Returns int or unsigned and takes 3 ints or 3 unsigned ints
#define __CLFN_I_3I(name) int __OVERLOAD__ name(int a, int b, int c); \
int2 __OVERLOAD__ name(int2 a, int2 b, int2 c); \
int3 __OVERLOAD__ name(int3 a, int3 b, int3 c); \
int4 __OVERLOAD__ name(int4 a, int4 b, int4 c); \
int8 __OVERLOAD__ name(int8 a, int8 b, int8 c); \
int16 __OVERLOAD__ name(int16 a, int16 b, int16 c); \
uint __OVERLOAD__ name(uint a, uint b, uint c); \
uint2 __OVERLOAD__ name(uint2 a, uint2 b, uint2 c); \
uint3 __OVERLOAD__ name(uint3 a, uint3 b, uint3 c); \
uint4 __OVERLOAD__ name(uint4 a, uint4 b, uint4 c); \
uint8 __OVERLOAD__ name(uint8 a, uint8 b, uint8 c); \
uint16 __OVERLOAD__ name(uint16 a, uint16 b, uint16 c);

#define __CLFN_I_2I(name) int __OVERLOAD__ name(int a, int b); \
int2 __OVERLOAD__ name(int2 a, int2 b); \
int3 __OVERLOAD__ name(int3 a, int3 b); \
int4 __OVERLOAD__ name(int4 a, int4 b); \
int8 __OVERLOAD__ name(int8 a, int8 b); \
int16 __OVERLOAD__ name(int16 a, int16 b); \
uint __OVERLOAD__ name(uint a, uint b); \
uint2 __OVERLOAD__ name(uint2 a, uint2 b); \
uint3 __OVERLOAD__ name(uint3 a, uint3 b); \
uint4 __OVERLOAD__ name(uint4 a, uint4 b); \
uint8 __OVERLOAD__ name(uint8 a, uint8 b); \
uint16 __OVERLOAD__ name(uint16 a, uint16 b);


// Returns an int, takes all types of input
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_I_ALL(name) int __OVERLOAD__ name(uchar x); \
int __OVERLOAD__ name(uchar2 x); \
int __OVERLOAD__ name(uchar3 x); \
int __OVERLOAD__ name(uchar4 x); \
int __OVERLOAD__ name(uchar8 x); \
int __OVERLOAD__ name(uchar16 x); \
int __OVERLOAD__ name(char x); \
int __OVERLOAD__ name(char2 x); \
int __OVERLOAD__ name(char3 x); \
int __OVERLOAD__ name(char4 x); \
int __OVERLOAD__ name(char8 x); \
int __OVERLOAD__ name(char16 x); \
int __OVERLOAD__ name(ushort x); \
int __OVERLOAD__ name(ushort2 x); \
int __OVERLOAD__ name(ushort3 x); \
int __OVERLOAD__ name(ushort4 x); \
int __OVERLOAD__ name(ushort8 x); \
int __OVERLOAD__ name(ushort16 x); \
int __OVERLOAD__ name(short x); \
int __OVERLOAD__ name(short2 x); \
int __OVERLOAD__ name(short3 x); \
int __OVERLOAD__ name(short4 x); \
int __OVERLOAD__ name(short8 x); \
int __OVERLOAD__ name(short16 x); \
int __OVERLOAD__ name(int x); \
int __OVERLOAD__ name(int2 x); \
int __OVERLOAD__ name(int3 x); \
int __OVERLOAD__ name(int4 x); \
int __OVERLOAD__ name(int8 x); \
int __OVERLOAD__ name(int16 x); \
int __OVERLOAD__ name(uint x); \
int __OVERLOAD__ name(uint2 x); \
int __OVERLOAD__ name(uint3 x); \
int __OVERLOAD__ name(uint4 x); \
int __OVERLOAD__ name(uint8 x); \
int __OVERLOAD__ name(uint16 x); \
int __OVERLOAD__ name(long x); \
int __OVERLOAD__ name(long2 x); \
int __OVERLOAD__ name(long3 x); \
int __OVERLOAD__ name(long4 x); \
int __OVERLOAD__ name(long8 x); \
int __OVERLOAD__ name(long16 x); \
int __OVERLOAD__ name(ulong x); \
int __OVERLOAD__ name(ulong2 x); \
int __OVERLOAD__ name(ulong3 x); \
int __OVERLOAD__ name(ulong4 x); \
int __OVERLOAD__ name(ulong8 x); \
int __OVERLOAD__ name(ulong16 x); \
int __OVERLOAD__ name(float x); \
int __OVERLOAD__ name(float2 x); \
int __OVERLOAD__ name(float3 x); \
int __OVERLOAD__ name(float4 x); \
int __OVERLOAD__ name(float8 x); \
int __OVERLOAD__ name(float16 x); \
int __OVERLOAD__ name(double x); \
int __OVERLOAD__ name(double2 x); \
int __OVERLOAD__ name(double3 x); \
int __OVERLOAD__ name(double4 x); \
int __OVERLOAD__ name(double8 x); \
int __OVERLOAD__ name(double16 x);
#else
#define __CLFN_I_ALL(name) int __OVERLOAD__ name(uchar x); \
int __OVERLOAD__ name(uchar2 x); \
int __OVERLOAD__ name(uchar3 x); \
int __OVERLOAD__ name(uchar4 x); \
int __OVERLOAD__ name(uchar8 x); \
int __OVERLOAD__ name(uchar16 x); \
int __OVERLOAD__ name(char x); \
int __OVERLOAD__ name(char2 x); \
int __OVERLOAD__ name(char3 x); \
int __OVERLOAD__ name(char4 x); \
int __OVERLOAD__ name(char8 x); \
int __OVERLOAD__ name(char16 x); \
int __OVERLOAD__ name(ushort x); \
int __OVERLOAD__ name(ushort2 x); \
int __OVERLOAD__ name(ushort3 x); \
int __OVERLOAD__ name(ushort4 x); \
int __OVERLOAD__ name(ushort8 x); \
int __OVERLOAD__ name(ushort16 x); \
int __OVERLOAD__ name(short x); \
int __OVERLOAD__ name(short2 x); \
int __OVERLOAD__ name(short3 x); \
int __OVERLOAD__ name(short4 x); \
int __OVERLOAD__ name(short8 x); \
int __OVERLOAD__ name(short16 x); \
int __OVERLOAD__ name(int x); \
int __OVERLOAD__ name(int2 x); \
int __OVERLOAD__ name(int3 x); \
int __OVERLOAD__ name(int4 x); \
int __OVERLOAD__ name(int8 x); \
int __OVERLOAD__ name(int16 x); \
int __OVERLOAD__ name(uint x); \
int __OVERLOAD__ name(uint2 x); \
int __OVERLOAD__ name(uint3 x); \
int __OVERLOAD__ name(uint4 x); \
int __OVERLOAD__ name(uint8 x); \
int __OVERLOAD__ name(uint16 x); \
int __OVERLOAD__ name(long x); \
int __OVERLOAD__ name(long2 x); \
int __OVERLOAD__ name(long3 x); \
int __OVERLOAD__ name(long4 x); \
int __OVERLOAD__ name(long8 x); \
int __OVERLOAD__ name(long16 x); \
int __OVERLOAD__ name(ulong x); \
int __OVERLOAD__ name(ulong2 x); \
int __OVERLOAD__ name(ulong3 x); \
int __OVERLOAD__ name(ulong4 x); \
int __OVERLOAD__ name(ulong8 x); \
int __OVERLOAD__ name(ulong16 x); \
int __OVERLOAD__ name(float x); \
int __OVERLOAD__ name(float2 x); \
int __OVERLOAD__ name(float3 x); \
int __OVERLOAD__ name(float4 x); \
int __OVERLOAD__ name(float8 x); \
int __OVERLOAD__ name(float16 x);
#endif

// Returns an event, takes 2 inputs of all types with either a 
// local or global qualifier, and then a size_t and event_t input.
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_EVENT_ALL(name) event_t __OVERLOAD__ name(__global char *dest, const __local char *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar *dest, const __local uchar *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char *dest, const __global char *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar *dest, const __global uchar *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short *dest, const __local short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort *dest, const __local ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short *dest, const __local short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort *dest, const __local ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int *dest, const __local int *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint *dest, const __local uint *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int *dest, const __global int *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint *dest, const __global uint *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long *dest, const __local long *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong *dest, const __local ulong *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long *dest, const __global long *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong *dest, const __global ulong *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float *dest, const __local float *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double *dest, const __local double *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float *dest, const __global float *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double *dest, const __global double *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global char2 *dest, const __local char2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar2 *dest, const __local uchar2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char2 *dest, const __global char2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar2 *dest, const __global uchar2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short2 *dest, const __local short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort2 *dest, const __local ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short2 *dest, const __local short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort2 *dest, const __local ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int2 *dest, const __local int2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint2 *dest, const __local uint2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int2 *dest, const __global int2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint2 *dest, const __global uint2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long2 *dest, const __local long2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong2 *dest, const __local ulong2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long2 *dest, const __global long2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong2 *dest, const __global ulong2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float2 *dest, const __local float2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double2 *dest, const __local double2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float2 *dest, const __global float2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double2 *dest, const __global double2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global char4 *dest, const __local char4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar4 *dest, const __local uchar4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char4 *dest, const __global char4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar4 *dest, const __global uchar4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short4 *dest, const __local short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort4 *dest, const __local ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short4 *dest, const __local short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort4 *dest, const __local ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int4 *dest, const __local int4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint4 *dest, const __local uint4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int4 *dest, const __global int4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint4 *dest, const __global uint4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long4 *dest, const __local long4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong4 *dest, const __local ulong4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long4 *dest, const __global long4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong4 *dest, const __global ulong4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float4 *dest, const __local float4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double4 *dest, const __local double4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float4 *dest, const __global float4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double4 *dest, const __global double4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global char8 *dest, const __local char8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar8 *dest, const __local uchar8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char8 *dest, const __global char8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar8 *dest, const __global uchar8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short8 *dest, const __local short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort8 *dest, const __local ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short8 *dest, const __local short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort8 *dest, const __local ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int8 *dest, const __local int8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint8 *dest, const __local uint8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int8 *dest, const __global int8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint8 *dest, const __global uint8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long8 *dest, const __local long8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong8 *dest, const __local ulong8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long8 *dest, const __global long8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong8 *dest, const __global ulong8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float8 *dest, const __local float8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double8 *dest, const __local double8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float8 *dest, const __global float8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double8 *dest, const __global double8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global char16 *dest, const __local char16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar16 *dest, const __local uchar16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char16 *dest, const __global char16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar16 *dest, const __global uchar16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short16 *dest, const __local short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort16 *dest, const __local ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short16 *dest, const __local short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort16 *dest, const __local ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int16 *dest, const __local int16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint16 *dest, const __local uint16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int16 *dest, const __global int16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint16 *dest, const __global uint16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long16 *dest, const __local long16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong16 *dest, const __local ulong16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long16 *dest, const __global long16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong16 *dest, const __global ulong16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float16 *dest, const __local float16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double16 *dest, const __local double16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float16 *dest, const __global float16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double16 *dest, const __global double16 *src, size_t count, event_t evt); 
#else
#define __CLFN_EVENT_ALL(name) event_t __OVERLOAD__ name(__global char *dest, const __local char *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar *dest, const __local uchar *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char *dest, const __global char *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar *dest, const __global uchar *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short *dest, const __local short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort *dest, const __local ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short *dest, const __local short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort *dest, const __local ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int *dest, const __local int *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint *dest, const __local uint *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int *dest, const __global int *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint *dest, const __global uint *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long *dest, const __local long *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong *dest, const __local ulong *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long *dest, const __global long *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong *dest, const __global ulong *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float *dest, const __local float *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float *dest, const __global float *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global char2 *dest, const __local char2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar2 *dest, const __local uchar2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char2 *dest, const __global char2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar2 *dest, const __global uchar2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short2 *dest, const __local short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort2 *dest, const __local ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short2 *dest, const __local short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort2 *dest, const __local ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int2 *dest, const __local int2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint2 *dest, const __local uint2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int2 *dest, const __global int2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint2 *dest, const __global uint2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long2 *dest, const __local long2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong2 *dest, const __local ulong2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long2 *dest, const __global long2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong2 *dest, const __global ulong2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float2 *dest, const __local float2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double2 *dest, const __local double2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float2 *dest, const __global float2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double2 *dest, const __global double2 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global char4 *dest, const __local char4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar4 *dest, const __local uchar4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char4 *dest, const __global char4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar4 *dest, const __global uchar4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short4 *dest, const __local short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort4 *dest, const __local ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short4 *dest, const __local short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort4 *dest, const __local ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int4 *dest, const __local int4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint4 *dest, const __local uint4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int4 *dest, const __global int4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint4 *dest, const __global uint4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long4 *dest, const __local long4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong4 *dest, const __local ulong4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long4 *dest, const __global long4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong4 *dest, const __global ulong4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float4 *dest, const __local float4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double4 *dest, const __local double4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float4 *dest, const __global float4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double4 *dest, const __global double4 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global char8 *dest, const __local char8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar8 *dest, const __local uchar8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char8 *dest, const __global char8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar8 *dest, const __global uchar8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short8 *dest, const __local short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort8 *dest, const __local ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short8 *dest, const __local short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort8 *dest, const __local ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int8 *dest, const __local int8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint8 *dest, const __local uint8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int8 *dest, const __global int8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint8 *dest, const __global uint8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long8 *dest, const __local long8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong8 *dest, const __local ulong8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long8 *dest, const __global long8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong8 *dest, const __global ulong8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float8 *dest, const __local float8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double8 *dest, const __local double8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float8 *dest, const __global float8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double8 *dest, const __global double8 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global char16 *dest, const __local char16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uchar16 *dest, const __local uchar16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local char16 *dest, const __global char16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uchar16 *dest, const __global uchar16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short16 *dest, const __local short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort16 *dest, const __local ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global short16 *dest, const __local short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ushort16 *dest, const __local ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global int16 *dest, const __local int16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global uint16 *dest, const __local uint16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local int16 *dest, const __global int16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local uint16 *dest, const __global uint16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global long16 *dest, const __local long16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global ulong16 *dest, const __local ulong16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local long16 *dest, const __global long16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local ulong16 *dest, const __global ulong16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global float16 *dest, const __local float16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__global double16 *dest, const __local double16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local float16 *dest, const __global float16 *src, size_t count, event_t evt); \
event_t __OVERLOAD__ name(__local double16 *dest, const __global double16 *src, size_t count, event_t evt); 
#endif

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_EVENT_ALL4(name) event_t __OVERLOAD__ name(__global char *dest, const __local char *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar *dest, const __local uchar *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char *dest, const __global char *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar *dest, const __global uchar *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short *dest, const __local short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort *dest, const __local ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short *dest, const __local short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort *dest, const __local ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int *dest, const __local int *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint *dest, const __local uint *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int *dest, const __global int *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint *dest, const __global uint *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long *dest, const __local long *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong *dest, const __local ulong *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long *dest, const __global long *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong *dest, const __global ulong *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float *dest, const __local float *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double *dest, const __local double *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float *dest, const __global float *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double *dest, const __global double *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global char2 *dest, const __local char2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar2 *dest, const __local uchar2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char2 *dest, const __global char2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar2 *dest, const __global uchar2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short2 *dest, const __local short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort2 *dest, const __local ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short2 *dest, const __local short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort2 *dest, const __local ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int2 *dest, const __local int2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint2 *dest, const __local uint2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int2 *dest, const __global int2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint2 *dest, const __global uint2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long2 *dest, const __local long2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong2 *dest, const __local ulong2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long2 *dest, const __global long2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong2 *dest, const __global ulong2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float2 *dest, const __local float2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double2 *dest, const __local double2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float2 *dest, const __global float2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double2 *dest, const __global double2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global char4 *dest, const __local char4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar4 *dest, const __local uchar4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char4 *dest, const __global char4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar4 *dest, const __global uchar4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short4 *dest, const __local short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort4 *dest, const __local ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short4 *dest, const __local short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort4 *dest, const __local ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int4 *dest, const __local int4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint4 *dest, const __local uint4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int4 *dest, const __global int4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint4 *dest, const __global uint4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long4 *dest, const __local long4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong4 *dest, const __local ulong4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long4 *dest, const __global long4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong4 *dest, const __global ulong4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float4 *dest, const __local float4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double4 *dest, const __local double4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float4 *dest, const __global float4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double4 *dest, const __global double4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global char8 *dest, const __local char8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar8 *dest, const __local uchar8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char8 *dest, const __global char8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar8 *dest, const __global uchar8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short8 *dest, const __local short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort8 *dest, const __local ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short8 *dest, const __local short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort8 *dest, const __local ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int8 *dest, const __local int8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint8 *dest, const __local uint8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int8 *dest, const __global int8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint8 *dest, const __global uint8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long8 *dest, const __local long8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong8 *dest, const __local ulong8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long8 *dest, const __global long8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong8 *dest, const __global ulong8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float8 *dest, const __local float8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double8 *dest, const __local double8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float8 *dest, const __global float8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double8 *dest, const __global double8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global char16 *dest, const __local char16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar16 *dest, const __local uchar16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char16 *dest, const __global char16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar16 *dest, const __global uchar16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short16 *dest, const __local short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort16 *dest, const __local ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short16 *dest, const __local short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort16 *dest, const __local ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int16 *dest, const __local int16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint16 *dest, const __local uint16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int16 *dest, const __global int16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint16 *dest, const __global uint16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long16 *dest, const __local long16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong16 *dest, const __local ulong16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long16 *dest, const __global long16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong16 *dest, const __global ulong16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float16 *dest, const __local float16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double16 *dest, const __local double16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float16 *dest, const __global float16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double16 *dest, const __global double16 *src, size_t count, size_t stride, event_t evt);
#else
#define __CLFN_EVENT_ALL4(name) event_t __OVERLOAD__ name(__global char *dest, const __local char *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar *dest, const __local uchar *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char *dest, const __global char *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar *dest, const __global uchar *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short *dest, const __local short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort *dest, const __local ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short *dest, const __local short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort *dest, const __local ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short *dest, const __global short *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort *dest, const __global ushort *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int *dest, const __local int *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint *dest, const __local uint *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int *dest, const __global int *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint *dest, const __global uint *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long *dest, const __local long *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong *dest, const __local ulong *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long *dest, const __global long *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong *dest, const __global ulong *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float *dest, const __local float *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float *dest, const __global float *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global char2 *dest, const __local char2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar2 *dest, const __local uchar2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char2 *dest, const __global char2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar2 *dest, const __global uchar2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short2 *dest, const __local short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort2 *dest, const __local ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short2 *dest, const __local short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort2 *dest, const __local ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short2 *dest, const __global short2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort2 *dest, const __global ushort2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int2 *dest, const __local int2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint2 *dest, const __local uint2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int2 *dest, const __global int2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint2 *dest, const __global uint2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long2 *dest, const __local long2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong2 *dest, const __local ulong2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long2 *dest, const __global long2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong2 *dest, const __global ulong2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float2 *dest, const __local float2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double2 *dest, const __local double2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float2 *dest, const __global float2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double2 *dest, const __global double2 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global char4 *dest, const __local char4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar4 *dest, const __local uchar4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char4 *dest, const __global char4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar4 *dest, const __global uchar4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short4 *dest, const __local short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort4 *dest, const __local ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short4 *dest, const __local short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort4 *dest, const __local ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short4 *dest, const __global short4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort4 *dest, const __global ushort4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int4 *dest, const __local int4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint4 *dest, const __local uint4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int4 *dest, const __global int4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint4 *dest, const __global uint4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long4 *dest, const __local long4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong4 *dest, const __local ulong4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long4 *dest, const __global long4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong4 *dest, const __global ulong4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float4 *dest, const __local float4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double4 *dest, const __local double4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float4 *dest, const __global float4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double4 *dest, const __global double4 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global char8 *dest, const __local char8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar8 *dest, const __local uchar8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char8 *dest, const __global char8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar8 *dest, const __global uchar8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short8 *dest, const __local short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort8 *dest, const __local ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short8 *dest, const __local short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort8 *dest, const __local ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short8 *dest, const __global short8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort8 *dest, const __global ushort8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int8 *dest, const __local int8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint8 *dest, const __local uint8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int8 *dest, const __global int8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint8 *dest, const __global uint8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long8 *dest, const __local long8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong8 *dest, const __local ulong8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long8 *dest, const __global long8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong8 *dest, const __global ulong8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float8 *dest, const __local float8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double8 *dest, const __local double8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float8 *dest, const __global float8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double8 *dest, const __global double8 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global char16 *dest, const __local char16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uchar16 *dest, const __local uchar16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local char16 *dest, const __global char16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uchar16 *dest, const __global uchar16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short16 *dest, const __local short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort16 *dest, const __local ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global short16 *dest, const __local short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ushort16 *dest, const __local ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local short16 *dest, const __global short16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ushort16 *dest, const __global ushort16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global int16 *dest, const __local int16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global uint16 *dest, const __local uint16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local int16 *dest, const __global int16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local uint16 *dest, const __global uint16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global long16 *dest, const __local long16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global ulong16 *dest, const __local ulong16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local long16 *dest, const __global long16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local ulong16 *dest, const __global ulong16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global float16 *dest, const __local float16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__global double16 *dest, const __local double16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local float16 *dest, const __global float16 *src, size_t count, size_t stride, event_t evt); \
event_t __OVERLOAD__ name(__local double16 *dest, const __global double16 *src, size_t count, size_t stride, event_t evt);
#endif

#define CHAR_BIT 	8
#define	SCHAR_MAX	127		/* min value for a signed char */
#define	SCHAR_MIN	(-128)		/* max value for a signed char */
#define	UCHAR_MAX	255		/* max value for an unsigned char */
#define	CHAR_MAX	SCHAR_MAX		/* max value for a char */
#define	CHAR_MIN	SCHAR_MIN		/* min value for a char */
#define	USHRT_MAX	65535		/* max value for an unsigned short */
#define	SHRT_MAX	32767		/* max value for a short */
#define	SHRT_MIN	(-32768)	/* min value for a short */
#define	UINT_MAX	0xffffffff	/* max value for an unsigned int */
#define	INT_MAX		2147483647	/* max value for an int */
#define	INT_MIN		(-2147483647-1)	/* min value for an int */
#define	ULONG_MAX	0xffffffffffffffffUL	/* max unsigned long */
#define	LONG_MAX	((long)0x7fffffffffffffffL)	/* max signed long */
#define	LONG_MIN	((long)(-0x7fffffffffffffffL-1)) /* min signed long */

#define FLT_DIG         6
#define FLT_MANT_DIG    24
#define FLT_MAX_10_EXP  +38
#define FLT_MAX_EXP     +128
#define FLT_MIN_10_EXP  -37
#define FLT_MIN_EXP     -125
#define FLT_RADIX       2
#define FLT_MAX         0x1.fffffep127f
#define FLT_MIN         0x1.0p-126f
#define FLT_EPSILON     0x1.0p-23f

#define FP_ILOGB0       INT_MIN
#define FP_ILOGBNAN     INT_MIN

// Section 6.9
#define __kernel_exec( _X, _type)   __kernel __attribute__ ((work_group_size_hint(_X, 1, 1)))  __attribute__((vec_type_hint(_type)))
#define kernel_exec( _X, _type)     __kernel_exec( _X, _type)
#define CL_VERSION_1_0  100
#define CL_VERSION_1_1  110
#define CL_VERSION_1_2  120

#define M_E_F         2.71828182845904523536028747135266250f   /* e */
#define M_LOG2E_F     1.44269504088896340735992468100189214f   /* log 2e */
#define M_LOG10E_F    0.434294481903251827651128918916605082f  /* log 10e */
#define M_LN2_F       0.693147180559945309417232121458176568f  /* log e2 */
#define M_LN10_F      2.3025850929940456840179914546843642f    /* log e10 */
#define M_PI_F        3.14159265358979323846264338327950288f   /* pi */
#define M_PI_2_F      1.57079632679489661923132169163975144f   /* pi/2 */
#define M_PI_4_F      0.785398163397448309615660845819875721f  /* pi/4 */
#define M_1_PI_F      0.318309886183790671537767526745028724f  /* 1/pi */
#define M_2_PI_F      0.636619772367581343075535053490057448f  /* 2/pi */
#define M_2_SQRTPI_F  1.12837916709551257389615890312154517f   /* 2/sqrt(pi) */
#define M_SQRT2_F     1.41421356237309504880168872420969808f   /* sqrt(2) */
#define M_SQRT1_2_F   0.707106781186547524400844362104849039f  /* 1/sqrt(2) */


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

    #define DBL_DIG         15
    #define DBL_MANT_DIG    53
    #define DBL_MAX_10_EXP  +308
    #define DBL_MAX_EXP     +1024
    #define DBL_MIN_10_EXP  -307
    #define DBL_MIN_EXP     -1021
    #define DBL_RADIX       2
    #define DBL_MAX         0x1.fffffffffffffp1023
    #define DBL_MIN         0x1.0p-1022
    #define DBL_EPSILON     0x1.0p-52

    #define HUGE_VAL        __builtin_huge_val()

    #define M_E         2.71828182845904523536028747135266250   /* e */
    #define M_LOG2E     1.44269504088896340735992468100189214   /* log 2e */
    #define M_LOG10E    0.434294481903251827651128918916605082  /* log 10e */
    #define M_LN2       0.693147180559945309417232121458176568  /* log e2 */
    #define M_LN10      2.30258509299404568401799145468436421   /* log e10 */
    #define M_PI        3.14159265358979323846264338327950288   /* pi */
    #define M_PI_2      1.57079632679489661923132169163975144   /* pi/2 */
    #define M_PI_4      0.785398163397448309615660845819875721  /* pi/4 */
    #define M_1_PI      0.318309886183790671537767526745028724  /* 1/pi */
    #define M_2_PI      0.636619772367581343075535053490057448  /* 2/pi */
    #define M_2_SQRTPI  1.12837916709551257389615890312154517   /* 2/sqrt(pi) */
    #define M_SQRT2     1.41421356237309504880168872420969808   /* sqrt(2) */
    #define M_SQRT1_2   0.707106781186547524400844362104849039  /* 1/sqrt(2) */

#endif

#define __OPENCL_TYPES_DEFINED__ 1

/* vload2 */
char2     __OVERLOAD__ vload2(size_t index, const char *p);
uchar2    __OVERLOAD__ vload2(size_t index, const uchar *p);
short2    __OVERLOAD__ vload2(size_t index, const short *p);
ushort2   __OVERLOAD__ vload2(size_t index, const ushort *p);
int2      __OVERLOAD__ vload2(size_t index, const int *p);
uint2     __OVERLOAD__ vload2(size_t index, const uint *p);
long2     __OVERLOAD__ vload2(size_t index, const long *p);
ulong2    __OVERLOAD__ vload2(size_t index, const ulong *p);
float2    __OVERLOAD__ vload2(size_t index, const float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double2   __OVERLOAD__ vload2(size_t index, const double *p);
#endif
char2     __OVERLOAD__ vload2(size_t index, const __global char *p);
uchar2    __OVERLOAD__ vload2(size_t index, const __global uchar *p);
short2    __OVERLOAD__ vload2(size_t index, const __global short *p);
ushort2   __OVERLOAD__ vload2(size_t index, const __global ushort *p);
int2      __OVERLOAD__ vload2(size_t index, const __global int *p);
uint2     __OVERLOAD__ vload2(size_t index, const __global uint *p);
long2     __OVERLOAD__ vload2(size_t index, const __global long *p);
ulong2    __OVERLOAD__ vload2(size_t index, const __global ulong *p);
float2    __OVERLOAD__ vload2(size_t index, const __global float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double2   __OVERLOAD__ vload2(size_t index, const __global double *p);
#endif
char2     __OVERLOAD__ vload2(size_t index, const __local char *p);
uchar2    __OVERLOAD__ vload2(size_t index, const __local uchar *p);
short2    __OVERLOAD__ vload2(size_t index, const __local short *p);
ushort2   __OVERLOAD__ vload2(size_t index, const __local ushort *p);
int2      __OVERLOAD__ vload2(size_t index, const __local int *p);
uint2     __OVERLOAD__ vload2(size_t index, const __local uint *p);
long2     __OVERLOAD__ vload2(size_t index, const __local long *p);
ulong2    __OVERLOAD__ vload2(size_t index, const __local ulong *p);
float2    __OVERLOAD__ vload2(size_t index, const __local float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double2   __OVERLOAD__ vload2(size_t index, const __local double *p);
#endif
char2     __OVERLOAD__ vload2(size_t index, const __constant char *p);
uchar2    __OVERLOAD__ vload2(size_t index, const __constant uchar *p);
short2    __OVERLOAD__ vload2(size_t index, const __constant short *p);
ushort2   __OVERLOAD__ vload2(size_t index, const __constant ushort *p);
int2      __OVERLOAD__ vload2(size_t index, const __constant int *p);
uint2     __OVERLOAD__ vload2(size_t index, const __constant uint *p);
long2     __OVERLOAD__ vload2(size_t index, const __constant long *p);
ulong2    __OVERLOAD__ vload2(size_t index, const __constant ulong *p);
float2    __OVERLOAD__ vload2(size_t index, const __constant float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double2   __OVERLOAD__ vload2(size_t index, const __constant double *p);
#endif

/* vload3 */
char3     __OVERLOAD__ vload3(size_t index, const char *p);
uchar3    __OVERLOAD__ vload3(size_t index, const uchar *p);
short3    __OVERLOAD__ vload3(size_t index, const short *p);
ushort3   __OVERLOAD__ vload3(size_t index, const ushort *p);
int3      __OVERLOAD__ vload3(size_t index, const int *p);
uint3     __OVERLOAD__ vload3(size_t index, const uint *p);
long3     __OVERLOAD__ vload3(size_t index, const long *p);
ulong3    __OVERLOAD__ vload3(size_t index, const ulong *p);
float3    __OVERLOAD__ vload3(size_t index, const float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double3   __OVERLOAD__ vload3(size_t index, const double *p);
#endif
char3     __OVERLOAD__ vload3(size_t index, const __global char *p);
uchar3    __OVERLOAD__ vload3(size_t index, const __global uchar *p);
short3    __OVERLOAD__ vload3(size_t index, const __global short *p);
ushort3   __OVERLOAD__ vload3(size_t index, const __global ushort *p);
int3      __OVERLOAD__ vload3(size_t index, const __global int *p);
uint3     __OVERLOAD__ vload3(size_t index, const __global uint *p);
long3     __OVERLOAD__ vload3(size_t index, const __global long *p);
ulong3    __OVERLOAD__ vload3(size_t index, const __global ulong *p);
float3    __OVERLOAD__ vload3(size_t index, const __global float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double3   __OVERLOAD__ vload3(size_t index, const __global double *p);
#endif
char3     __OVERLOAD__ vload3(size_t index, const __local char *p);
uchar3    __OVERLOAD__ vload3(size_t index, const __local uchar *p);
short3    __OVERLOAD__ vload3(size_t index, const __local short *p);
ushort3   __OVERLOAD__ vload3(size_t index, const __local ushort *p);
int3      __OVERLOAD__ vload3(size_t index, const __local int *p);
uint3     __OVERLOAD__ vload3(size_t index, const __local uint *p);
long3     __OVERLOAD__ vload3(size_t index, const __local long *p);
ulong3    __OVERLOAD__ vload3(size_t index, const __local ulong *p);
float3    __OVERLOAD__ vload3(size_t index, const __local float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double3   __OVERLOAD__ vload3(size_t index, const __local double *p);
#endif
char3     __OVERLOAD__ vload3(size_t index, const __constant char *p);
uchar3    __OVERLOAD__ vload3(size_t index, const __constant uchar *p);
short3    __OVERLOAD__ vload3(size_t index, const __constant short *p);
ushort3   __OVERLOAD__ vload3(size_t index, const __constant ushort *p);
int3      __OVERLOAD__ vload3(size_t index, const __constant int *p);
uint3     __OVERLOAD__ vload3(size_t index, const __constant uint *p);
long3     __OVERLOAD__ vload3(size_t index, const __constant long *p);
ulong3    __OVERLOAD__ vload3(size_t index, const __constant ulong *p);
float3    __OVERLOAD__ vload3(size_t index, const __constant float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double3   __OVERLOAD__ vload3(size_t index, const __constant double *p);
#endif
/* vload4 */
char4     __OVERLOAD__ vload4(size_t index, const char *p);
uchar4    __OVERLOAD__ vload4(size_t index, const uchar *p);
short4    __OVERLOAD__ vload4(size_t index, const short *p);
ushort4   __OVERLOAD__ vload4(size_t index, const ushort *p);
int4      __OVERLOAD__ vload4(size_t index, const int *p);
uint4     __OVERLOAD__ vload4(size_t index, const uint *p);
long4     __OVERLOAD__ vload4(size_t index, const long *p);
ulong4    __OVERLOAD__ vload4(size_t index, const ulong *p);
float4    __OVERLOAD__ vload4(size_t index, const float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double4   __OVERLOAD__ vload4(size_t index, const double *p);
#endif
char4     __OVERLOAD__ vload4(size_t index, const __global char *p);
uchar4    __OVERLOAD__ vload4(size_t index, const __global uchar *p);
short4    __OVERLOAD__ vload4(size_t index, const __global short *p);
ushort4   __OVERLOAD__ vload4(size_t index, const __global ushort *p);
int4      __OVERLOAD__ vload4(size_t index, const __global int *p);
uint4     __OVERLOAD__ vload4(size_t index, const __global uint *p);
long4     __OVERLOAD__ vload4(size_t index, const __global long *p);
ulong4    __OVERLOAD__ vload4(size_t index, const __global ulong *p);
float4    __OVERLOAD__ vload4(size_t index, const __global float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double4   __OVERLOAD__ vload4(size_t index, const __global double *p);
#endif
char4     __OVERLOAD__ vload4(size_t index, const __local char *p);
uchar4    __OVERLOAD__ vload4(size_t index, const __local uchar *p);
short4    __OVERLOAD__ vload4(size_t index, const __local short *p);
ushort4   __OVERLOAD__ vload4(size_t index, const __local ushort *p);
int4      __OVERLOAD__ vload4(size_t index, const __local int *p);
uint4     __OVERLOAD__ vload4(size_t index, const __local uint *p);
long4     __OVERLOAD__ vload4(size_t index, const __local long *p);
ulong4    __OVERLOAD__ vload4(size_t index, const __local ulong *p);
float4    __OVERLOAD__ vload4(size_t index, const __local float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double4   __OVERLOAD__ vload4(size_t index, const __local double *p);
#endif
char4     __OVERLOAD__ vload4(size_t index, const __constant char *p);
uchar4    __OVERLOAD__ vload4(size_t index, const __constant uchar *p);
short4    __OVERLOAD__ vload4(size_t index, const __constant short *p);
ushort4   __OVERLOAD__ vload4(size_t index, const __constant ushort *p);
int4      __OVERLOAD__ vload4(size_t index, const __constant int *p);
uint4     __OVERLOAD__ vload4(size_t index, const __constant uint *p);
long4     __OVERLOAD__ vload4(size_t index, const __constant long *p);
ulong4    __OVERLOAD__ vload4(size_t index, const __constant ulong *p);
float4    __OVERLOAD__ vload4(size_t index, const __constant float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double4   __OVERLOAD__ vload4(size_t index, const __constant double *p);
#endif
/* vload8 */
char8     __OVERLOAD__ vload8(size_t index, const char *p);
uchar8    __OVERLOAD__ vload8(size_t index, const uchar *p);
short8    __OVERLOAD__ vload8(size_t index, const short *p);
ushort8   __OVERLOAD__ vload8(size_t index, const ushort *p);
int8      __OVERLOAD__ vload8(size_t index, const int *p);
uint8     __OVERLOAD__ vload8(size_t index, const uint *p);
long8     __OVERLOAD__ vload8(size_t index, const long *p);
ulong8    __OVERLOAD__ vload8(size_t index, const ulong *p);
float8    __OVERLOAD__ vload8(size_t index, const float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double8   __OVERLOAD__ vload8(size_t index, const double *p);
#endif
char8     __OVERLOAD__ vload8(size_t index, const __global char *p);
uchar8    __OVERLOAD__ vload8(size_t index, const __global uchar *p);
short8    __OVERLOAD__ vload8(size_t index, const __global short *p);
ushort8   __OVERLOAD__ vload8(size_t index, const __global ushort *p);
int8      __OVERLOAD__ vload8(size_t index, const __global int *p);
uint8     __OVERLOAD__ vload8(size_t index, const __global uint *p);
long8     __OVERLOAD__ vload8(size_t index, const __global long *p);
ulong8    __OVERLOAD__ vload8(size_t index, const __global ulong *p);
float8    __OVERLOAD__ vload8(size_t index, const __global float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double8   __OVERLOAD__ vload8(size_t index, const __global double *p);
#endif
char8     __OVERLOAD__ vload8(size_t index, const __local char *p);
uchar8    __OVERLOAD__ vload8(size_t index, const __local uchar *p);
short8    __OVERLOAD__ vload8(size_t index, const __local short *p);
ushort8   __OVERLOAD__ vload8(size_t index, const __local ushort *p);
int8      __OVERLOAD__ vload8(size_t index, const __local int *p);
uint8     __OVERLOAD__ vload8(size_t index, const __local uint *p);
long8     __OVERLOAD__ vload8(size_t index, const __local long *p);
ulong8    __OVERLOAD__ vload8(size_t index, const __local ulong *p);
float8    __OVERLOAD__ vload8(size_t index, const __local float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double8   __OVERLOAD__ vload8(size_t index, const __local double *p);
#endif
char8     __OVERLOAD__ vload8(size_t index, const __constant char *p);
uchar8    __OVERLOAD__ vload8(size_t index, const __constant uchar *p);
short8    __OVERLOAD__ vload8(size_t index, const __constant short *p);
ushort8   __OVERLOAD__ vload8(size_t index, const __constant ushort *p);
int8      __OVERLOAD__ vload8(size_t index, const __constant int *p);
uint8     __OVERLOAD__ vload8(size_t index, const __constant uint *p);
long8     __OVERLOAD__ vload8(size_t index, const __constant long *p);
ulong8    __OVERLOAD__ vload8(size_t index, const __constant ulong *p);
float8    __OVERLOAD__ vload8(size_t index, const __constant float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double8   __OVERLOAD__ vload8(size_t index, const __constant double *p);
#endif
/* vload16 */
char16    __OVERLOAD__ vload16(size_t index, const char *p);
uchar16   __OVERLOAD__ vload16(size_t index, const uchar *p);
short16   __OVERLOAD__ vload16(size_t index, const short *p);
ushort16  __OVERLOAD__ vload16(size_t index, const ushort *p);
int16     __OVERLOAD__ vload16(size_t index, const int *p);
uint16    __OVERLOAD__ vload16(size_t index, const uint *p);
long16    __OVERLOAD__ vload16(size_t index, const long *p);
ulong16   __OVERLOAD__ vload16(size_t index, const ulong *p);
float16   __OVERLOAD__ vload16(size_t index, const float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double16  __OVERLOAD__ vload16(size_t index, const double *p);
#endif
char16    __OVERLOAD__ vload16(size_t index, const __global char *p);
uchar16   __OVERLOAD__ vload16(size_t index, const __global uchar *p);
short16   __OVERLOAD__ vload16(size_t index, const __global short *p);
ushort16  __OVERLOAD__ vload16(size_t index, const __global ushort *p);
int16     __OVERLOAD__ vload16(size_t index, const __global int *p);
uint16    __OVERLOAD__ vload16(size_t index, const __global uint *p);
long16    __OVERLOAD__ vload16(size_t index, const __global long *p);
ulong16   __OVERLOAD__ vload16(size_t index, const __global ulong *p);
float16   __OVERLOAD__ vload16(size_t index, const __global float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double16  __OVERLOAD__ vload16(size_t index, const __global double *p);
#endif
char16    __OVERLOAD__ vload16(size_t index, const __local char *p);
uchar16   __OVERLOAD__ vload16(size_t index, const __local uchar *p);
short16   __OVERLOAD__ vload16(size_t index, const __local short *p);
ushort16  __OVERLOAD__ vload16(size_t index, const __local ushort *p);
int16     __OVERLOAD__ vload16(size_t index, const __local int *p);
uint16    __OVERLOAD__ vload16(size_t index, const __local uint *p);
long16    __OVERLOAD__ vload16(size_t index, const __local long *p);
ulong16   __OVERLOAD__ vload16(size_t index, const __local ulong *p);
float16   __OVERLOAD__ vload16(size_t index, const __local float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double16  __OVERLOAD__ vload16(size_t index, const __local double *p);
#endif
char16    __OVERLOAD__ vload16(size_t index, const __constant char *p);
uchar16   __OVERLOAD__ vload16(size_t index, const __constant uchar *p);
short16   __OVERLOAD__ vload16(size_t index, const __constant short *p);
ushort16  __OVERLOAD__ vload16(size_t index, const __constant ushort *p);
int16     __OVERLOAD__ vload16(size_t index, const __constant int *p);
uint16    __OVERLOAD__ vload16(size_t index, const __constant uint *p);
long16    __OVERLOAD__ vload16(size_t index, const __constant long *p);
ulong16   __OVERLOAD__ vload16(size_t index, const __constant ulong *p);
float16   __OVERLOAD__ vload16(size_t index, const __constant float *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double16  __OVERLOAD__ vload16(size_t index, const __constant double *p);
#endif
/* vload_half */
float   __OVERLOAD__ vload_half(size_t index, const half *p);
float   __OVERLOAD__ vload_half(size_t index, const __global half *p);
float   __OVERLOAD__ vload_half(size_t index, const __local half *p);
float   __OVERLOAD__ vload_half(size_t index, const __constant half *p);

/* vload_ahalf */
float __OVERLOAD__ vloada_half(size_t index, const half *p);
float __OVERLOAD__ vloada_half(size_t index, const __global half *p);
float __OVERLOAD__ vloada_half(size_t index, const __local half *p);
float __OVERLOAD__ vloada_half(size_t index, const __constant half *p);

/* vload_half2 */
float2  __OVERLOAD__ vload_half2(size_t index, const half *p);
float2  __OVERLOAD__ vload_half2(size_t index, const __global half *p);
float2  __OVERLOAD__ vload_half2(size_t index, const __local half *p);
float2  __OVERLOAD__ vload_half2(size_t index, const __constant half *p);

/* vloada_half2 */
float2 __OVERLOAD__ vloada_half2(size_t index, const half *p);
float2 __OVERLOAD__ vloada_half2(size_t index, const __global half *p);
float2 __OVERLOAD__ vloada_half2(size_t index, const __local half *p);
float2 __OVERLOAD__ vloada_half2(size_t index, const __constant half *p);

/* vload_half3 */
float3 __OVERLOAD__ vload_half3( size_t index, const half *p);
float3 __OVERLOAD__ vload_half3(size_t index, const __global half *p);
float3 __OVERLOAD__ vload_half3(size_t index, const __local half *p);
float3 __OVERLOAD__ vload_half3(size_t index, const __constant half *p);

/* vloada_half3 */
float3 __OVERLOAD__ vloada_half3(size_t index, const half *p);
float3 __OVERLOAD__ vloada_half3(size_t index, const __global half *p);
float3 __OVERLOAD__ vloada_half3(size_t index, const __local half *p);
float3 __OVERLOAD__ vloada_half3(size_t index, const __constant half *p);

/* vload_half4 */
float4 __OVERLOAD__ vload_half4(size_t index, const half *p);
float4 __OVERLOAD__ vload_half4(size_t index, const __global half *p);
float4 __OVERLOAD__ vload_half4(size_t index, const __local half *p);
float4 __OVERLOAD__ vload_half4(size_t index, const __constant half *p);

/* vloada_half4 */
float4 __OVERLOAD__ vloada_half4(size_t index, const half *p);
float4 __OVERLOAD__ vloada_half4(size_t index, const __global half *p);
float4 __OVERLOAD__ vloada_half4(size_t index, const __local half *p);
float4 __OVERLOAD__ vloada_half4(size_t index, const __constant half *p);

/* vload_half8 */
float8 __OVERLOAD__ vload_half8(size_t index, const half *p);
float8 __OVERLOAD__ vload_half8(size_t index, const __global half *p);
float8 __OVERLOAD__ vload_half8(size_t index, const __local half *p);
float8 __OVERLOAD__ vload_half8(size_t index, const __constant half *p);

/* vloada_half8 */
float8 __OVERLOAD__ vloada_half8(size_t index, const half *p);
float8 __OVERLOAD__ vloada_half8(size_t index, const __global half *p);
float8 __OVERLOAD__ vloada_half8(size_t index, const __local half *p);
float8 __OVERLOAD__ vloada_half8(size_t index, const __constant half *p);

/* vload_half16 */
float16 __OVERLOAD__ vload_half16(size_t index, const half *p);
float16 __OVERLOAD__ vload_half16(size_t index, const __global half *p);
float16 __OVERLOAD__ vload_half16(size_t index, const __local half *p);
float16 __OVERLOAD__ vload_half16(size_t index, const __constant half *p);

/* vloada_half16 */
float16 __OVERLOAD__ vloada_half16(size_t index, const half *p);
float16 __OVERLOAD__ vloada_half16(size_t index, const __global half *p);
float16 __OVERLOAD__ vloada_half16(size_t index, const __local half *p);
float16 __OVERLOAD__ vloada_half16(size_t index, const __constant half *p);

/* vstore2 */
void __OVERLOAD__ vstore2( char2 v, size_t index, char *p );
void __OVERLOAD__ vstore2( uchar2 v, size_t index, uchar *p );
void __OVERLOAD__ vstore2( short2 v, size_t index, short *p );
void __OVERLOAD__ vstore2( ushort2 v, size_t index, ushort *p );
void __OVERLOAD__ vstore2( int2 v, size_t index, int *p );
void __OVERLOAD__ vstore2( uint2 v, size_t index, uint *p );
void __OVERLOAD__ vstore2( long2 v, size_t index, long *p );
void __OVERLOAD__ vstore2( ulong2 v, size_t index, ulong *p );
void __OVERLOAD__ vstore2( float2 v, size_t index, float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore2( double2 v, size_t index, double *p );
#endif
void __OVERLOAD__ vstore2( char2 v, size_t index, __global char *p );
void __OVERLOAD__ vstore2( uchar2 v, size_t index, __global uchar *p );
void __OVERLOAD__ vstore2( short2 v, size_t index, __global short *p );
void __OVERLOAD__ vstore2( ushort2 v, size_t index, __global ushort *p );
void __OVERLOAD__ vstore2( int2 v, size_t index, __global int *p );
void __OVERLOAD__ vstore2( uint2 v, size_t index, __global uint *p );
void __OVERLOAD__ vstore2( long2 v, size_t index, __global long *p );
void __OVERLOAD__ vstore2( ulong2 v, size_t index, __global ulong *p );
void __OVERLOAD__ vstore2( float2 v, size_t index, __global float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore2( double2 v, size_t index, __global double *p );
#endif
void __OVERLOAD__ vstore2( char2 v, size_t index, __local char *p );
void __OVERLOAD__ vstore2( uchar2 v, size_t index, __local uchar *p );
void __OVERLOAD__ vstore2( short2 v, size_t index, __local short *p );
void __OVERLOAD__ vstore2( ushort2 v, size_t index, __local ushort *p );
void __OVERLOAD__ vstore2( int2 v, size_t index, __local int *p );
void __OVERLOAD__ vstore2( uint2 v, size_t index, __local uint *p );
void __OVERLOAD__ vstore2( long2 v, size_t index, __local long *p );
void __OVERLOAD__ vstore2( ulong2 v, size_t index, __local ulong *p );
void __OVERLOAD__ vstore2( float2 v, size_t index, __local float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore2( double2 v, size_t index, __local double *p );
#endif
/* vstore3 */
void __OVERLOAD__ vstore3( char3 v, size_t index, char *p );
void __OVERLOAD__ vstore3( uchar3 v, size_t index, uchar *p );
void __OVERLOAD__ vstore3( short3 v, size_t index, short *p );
void __OVERLOAD__ vstore3( ushort3 v, size_t index, ushort *p );
void __OVERLOAD__ vstore3( int3 v, size_t index, int *p );
void __OVERLOAD__ vstore3( uint3 v, size_t index, uint *p );
void __OVERLOAD__ vstore3( long3 v, size_t index, long *p );
void __OVERLOAD__ vstore3( ulong3 v, size_t index, ulong *p );
void __OVERLOAD__ vstore3( float3 v, size_t index, float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore3( double3 v, size_t index, double *p );
#endif
void __OVERLOAD__ vstore3( char3 v, size_t index, __global char *p );
void __OVERLOAD__ vstore3( uchar3 v, size_t index, __global uchar *p );
void __OVERLOAD__ vstore3( short3 v, size_t index, __global short *p );
void __OVERLOAD__ vstore3( ushort3 v, size_t index, __global ushort *p );
void __OVERLOAD__ vstore3( int3 v, size_t index, __global int *p );
void __OVERLOAD__ vstore3( uint3 v, size_t index, __global uint *p );
void __OVERLOAD__ vstore3( long3 v, size_t index, __global long *p );
void __OVERLOAD__ vstore3( ulong3 v, size_t index, __global ulong *p );
void __OVERLOAD__ vstore3( float3 v, size_t index, __global float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore3( double3 v, size_t index, __global double *p );
#endif
void __OVERLOAD__ vstore3( char3 v, size_t index, __local char *p );
void __OVERLOAD__ vstore3( uchar3 v, size_t index, __local uchar *p );
void __OVERLOAD__ vstore3( short3 v, size_t index, __local short *p );
void __OVERLOAD__ vstore3( ushort3 v, size_t index, __local ushort *p );
void __OVERLOAD__ vstore3( int3 v, size_t index, __local int *p );
void __OVERLOAD__ vstore3( uint3 v, size_t index, __local uint *p );
void __OVERLOAD__ vstore3( long3 v, size_t index, __local long *p );
void __OVERLOAD__ vstore3( ulong3 v, size_t index, __local ulong *p );
void __OVERLOAD__ vstore3( float3 v, size_t index, __local float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore3( double3 v, size_t index, __local double *p );
#endif

/* vstore4 */
void __OVERLOAD__ vstore4( char4 v, size_t index, char *p );
void __OVERLOAD__ vstore4( uchar4 v, size_t index, uchar *p );
void __OVERLOAD__ vstore4( short4 v, size_t index, short *p );
void __OVERLOAD__ vstore4( ushort4 v, size_t index, ushort *p );
void __OVERLOAD__ vstore4( int4 v, size_t index, int *p );
void __OVERLOAD__ vstore4( uint4 v, size_t index, uint *p );
void __OVERLOAD__ vstore4( long4 v, size_t index, long *p );
void __OVERLOAD__ vstore4( ulong4 v, size_t index, ulong *p );
void __OVERLOAD__ vstore4( float4 v, size_t index, float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore4( double4 v, size_t index, double *p );
#endif
void __OVERLOAD__ vstore4( char4 v, size_t index, __global char *p );
void __OVERLOAD__ vstore4( uchar4 v, size_t index, __global uchar *p );
void __OVERLOAD__ vstore4( short4 v, size_t index, __global short *p );
void __OVERLOAD__ vstore4( ushort4 v, size_t index, __global ushort *p );
void __OVERLOAD__ vstore4( int4 v, size_t index, __global int *p );
void __OVERLOAD__ vstore4( uint4 v, size_t index, __global uint *p );
void __OVERLOAD__ vstore4( long4 v, size_t index, __global long *p );
void __OVERLOAD__ vstore4( ulong4 v, size_t index, __global ulong *p );
void __OVERLOAD__ vstore4( float4 v, size_t index, __global float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore4( double4 v, size_t index, __global double *p );
#endif
void __OVERLOAD__ vstore4( char4 v, size_t index, __local char *p );
void __OVERLOAD__ vstore4( uchar4 v, size_t index, __local uchar *p );
void __OVERLOAD__ vstore4( short4 v, size_t index, __local short *p );
void __OVERLOAD__ vstore4( ushort4 v, size_t index, __local ushort *p );
void __OVERLOAD__ vstore4( int4 v, size_t index, __local int *p );
void __OVERLOAD__ vstore4( uint4 v, size_t index, __local uint *p );
void __OVERLOAD__ vstore4( long4 v, size_t index, __local long *p );
void __OVERLOAD__ vstore4( ulong4 v, size_t index, __local ulong *p );
void __OVERLOAD__ vstore4( float4 v, size_t index, __local float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore4( double4 v, size_t index, __local double *p );
#endif

/* vstore8 */
void __OVERLOAD__ vstore8( char8 v, size_t index, char *p );
void __OVERLOAD__ vstore8( uchar8 v, size_t index, uchar *p );
void __OVERLOAD__ vstore8( short8 v, size_t index, short *p );
void __OVERLOAD__ vstore8( ushort8 v, size_t index, ushort *p );
void __OVERLOAD__ vstore8( int8 v, size_t index, int *p );
void __OVERLOAD__ vstore8( uint8 v, size_t index, uint *p );
void __OVERLOAD__ vstore8( long8 v, size_t index, long *p );
void __OVERLOAD__ vstore8( ulong8 v, size_t index, ulong *p );
void __OVERLOAD__ vstore8( float8 v, size_t index, float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore8( double8 v, size_t index, double *p );
#endif
void __OVERLOAD__ vstore8( char8 v, size_t index, __global char *p );
void __OVERLOAD__ vstore8( uchar8 v, size_t index, __global uchar *p );
void __OVERLOAD__ vstore8( short8 v, size_t index, __global short *p );
void __OVERLOAD__ vstore8( ushort8 v, size_t index, __global ushort *p );
void __OVERLOAD__ vstore8( int8 v, size_t index, __global int *p );
void __OVERLOAD__ vstore8( uint8 v, size_t index, __global uint *p );
void __OVERLOAD__ vstore8( long8 v, size_t index, __global long *p );
void __OVERLOAD__ vstore8( ulong8 v, size_t index, __global ulong *p );
void __OVERLOAD__ vstore8( float8 v, size_t index, __global float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore8( double8 v, size_t index, __global double *p );
#endif
void __OVERLOAD__ vstore8( char8 v, size_t index, __local char *p );
void __OVERLOAD__ vstore8( uchar8 v, size_t index, __local uchar *p );
void __OVERLOAD__ vstore8( short8 v, size_t index, __local short *p );
void __OVERLOAD__ vstore8( ushort8 v, size_t index, __local ushort *p );
void __OVERLOAD__ vstore8( int8 v, size_t index, __local int *p );
void __OVERLOAD__ vstore8( uint8 v, size_t index, __local uint *p );
void __OVERLOAD__ vstore8( long8 v, size_t index, __local long *p );
void __OVERLOAD__ vstore8( ulong8 v, size_t index, __local ulong *p );
void __OVERLOAD__ vstore8( float8 v, size_t index, __local float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore8( double8 v, size_t index, __local double *p );
#endif

/* vstore16 */
void __OVERLOAD__ vstore16( char16 v, size_t index, char *p );
void __OVERLOAD__ vstore16( uchar16 v, size_t index, uchar *p );
void __OVERLOAD__ vstore16( short16 v, size_t index, short *p );
void __OVERLOAD__ vstore16( ushort16 v, size_t index, ushort *p );
void __OVERLOAD__ vstore16( int16 v, size_t index, int *p );
void __OVERLOAD__ vstore16( uint16 v, size_t index, uint *p );
void __OVERLOAD__ vstore16( long16 v, size_t index, long *p );
void __OVERLOAD__ vstore16( ulong16 v, size_t index, ulong *p );
void __OVERLOAD__ vstore16( float16 v, size_t index, float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore16( double16 v, size_t index, double *p );
#endif
void __OVERLOAD__ vstore16( char16 v, size_t index, __global char *p );
void __OVERLOAD__ vstore16( uchar16 v, size_t index, __global uchar *p );
void __OVERLOAD__ vstore16( short16 v, size_t index, __global short *p );
void __OVERLOAD__ vstore16( ushort16 v, size_t index, __global ushort *p );
void __OVERLOAD__ vstore16( int16 v, size_t index, __global int *p );
void __OVERLOAD__ vstore16( uint16 v, size_t index, __global uint *p );
void __OVERLOAD__ vstore16( long16 v, size_t index, __global long *p );
void __OVERLOAD__ vstore16( ulong16 v, size_t index, __global ulong *p );
void __OVERLOAD__ vstore16( float16 v, size_t index, __global float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore16( double16 v, size_t index, __global double *p );
#endif
void __OVERLOAD__ vstore16( char16 v, size_t index, __local char *p );
void __OVERLOAD__ vstore16( uchar16 v, size_t index, __local uchar *p );
void __OVERLOAD__ vstore16( short16 v, size_t index, __local short *p );
void __OVERLOAD__ vstore16( ushort16 v, size_t index, __local ushort *p );
void __OVERLOAD__ vstore16( int16 v, size_t index, __local int *p );
void __OVERLOAD__ vstore16( uint16 v, size_t index, __local uint *p );
void __OVERLOAD__ vstore16( long16 v, size_t index, __local long *p );
void __OVERLOAD__ vstore16( ulong16 v, size_t index, __local ulong *p );
void __OVERLOAD__ vstore16( float16 v, size_t index, __local float *p );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore16( double16 v, size_t index, __local double *p );
#endif
/* vstore_half */
void __OVERLOAD__ vstore_half (float  f, size_t index, half *p);
void __OVERLOAD__ vstore_half (float  f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half (float  f, size_t index, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore_half(double f, size_t index, half *p);
void __OVERLOAD__ vstore_half(double f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half(double f, size_t index, __local half *p);
#endif
/* vstore_half2 */
void __OVERLOAD__ vstore_half2(float2 f, size_t index, half *p);
void __OVERLOAD__ vstore_half2(float2 f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half2(float2 f, size_t index, __local half *p);
void __OVERLOAD__ vstore_half2(double2 f, size_t index, half *p);
void __OVERLOAD__ vstore_half2(double2 f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half2(double2 f, size_t index, __local half *p);

/* vstore_half3 */
void __OVERLOAD__ vstore_half3(float3 f, size_t index, half *p);
void __OVERLOAD__ vstore_half3(float3 f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half3(float3 f, size_t index, __local half *p);
void __OVERLOAD__ vstore_half3(double3 f, size_t index, half *p);
void __OVERLOAD__ vstore_half3(double3 f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half3(double3 f, size_t index, __local half *p);

/* vstore_half4 */
void __OVERLOAD__ vstore_half4(float4 x, size_t index, half *p);
void __OVERLOAD__ vstore_half4(float4 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half4(float4 x, size_t index, __local half *p);
void __OVERLOAD__ vstore_half4(double4 f, size_t index, half *p);
void __OVERLOAD__ vstore_half4(double4 f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half4(double4 f, size_t index, __local half *p);

/* vstore_half8 */
void __OVERLOAD__ vstore_half8(float8 x, size_t index, half *p);
void __OVERLOAD__ vstore_half8(float8 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half8(float8 x, size_t index, __local half *p);
void __OVERLOAD__ vstore_half8(double8 f, size_t index, half *p);
void __OVERLOAD__ vstore_half8(double8 f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half8(double8 f, size_t index, __local half *p);

/* vstore_half16 */
void __OVERLOAD__ vstore_half16(float16 v, size_t index, half *p);
void __OVERLOAD__ vstore_half16(float16 v, size_t index, __global half *p);
void __OVERLOAD__ vstore_half16(float16 v, size_t index, __local half *p);
void __OVERLOAD__ vstore_half16(double16 f, size_t index, half *p);
void __OVERLOAD__ vstore_half16(double16 f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half16(double16 f, size_t index, __local half *p);

/* vstorea_half */
void __OVERLOAD__ vstorea_half (float  f, size_t index, half *p);
void __OVERLOAD__ vstorea_half (float  f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half (float  f, size_t index, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstorea_half(double f, size_t index, half *p);
void __OVERLOAD__ vstorea_half(double f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half(double f, size_t index, __local half *p);
#endif
/* vstorea_half2 */
void __OVERLOAD__ vstorea_half2(float2 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half2(float2 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half2(float2 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half2(double2 f, size_t index, half *p);
void __OVERLOAD__ vstorea_half2(double2 f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half2(double2 f, size_t index, __local half *p);

/* vstorea_half3 */
void __OVERLOAD__ vstorea_half3(float3 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half3(float3 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half3(float3 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half3(double3 f, size_t index, half *p);
void __OVERLOAD__ vstorea_half3(double3 f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half3(double3 f, size_t index, __local half *p);

/* vstorea_half4 */
void __OVERLOAD__ vstorea_half4(float4 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half4(float4 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half4(float4 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half4(double4 f, size_t index, half *p);
void __OVERLOAD__ vstorea_half4(double4 f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half4(double4 f, size_t index, __local half *p);

/* vstorea_half8 */
void __OVERLOAD__ vstorea_half8(float8 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half8(float8 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half8(float8 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half8(double8 f, size_t index, half *p);
void __OVERLOAD__ vstorea_half8(double8 f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half8(double8 f, size_t index, __local half *p);

/* vstorea_half16 */
void __OVERLOAD__ vstorea_half16(float16 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half16(float16 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half16(float16 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half16(double16 f, size_t index, half *p);
void __OVERLOAD__ vstorea_half16(double16 f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half16(double16 f, size_t index, __local half *p);

/* vstore_half_rte */
void __OVERLOAD__ vstore_half_rte(float f, size_t index, half *p);
void __OVERLOAD__ vstore_half_rte(float f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half_rte(float f, size_t index, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore_half_rte(double f, size_t index, half *p);
void __OVERLOAD__ vstore_half_rte(double f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half_rte(double f, size_t index, __local half *p);
#endif
/* vstore_half2_rte */
void __OVERLOAD__ vstore_half2_rte(float2 f, size_t index, half *p);
void __OVERLOAD__ vstore_half2_rte(float2 f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half2_rte(float2 f, size_t index, __local half *p);
void __OVERLOAD__ vstore_half2_rte(double2 x, size_t index, half *p);
void __OVERLOAD__ vstore_half2_rte(double2 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half2_rte(double2 x, size_t index, __local half *p);

/* vstore_half3_rte */
void __OVERLOAD__ vstore_half3_rte(float3 x3, size_t index, half *p);
void __OVERLOAD__ vstore_half3_rte(float3 x3, size_t index, __global half *p);
void __OVERLOAD__ vstore_half3_rte(float3 x3, size_t index, __local half *p);
void __OVERLOAD__ vstore_half3_rte(double3 x, size_t index, half *p);
void __OVERLOAD__ vstore_half3_rte(double3 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half3_rte(double3 x, size_t index, __local half *p);

/* vstore_half4_rte */
void __OVERLOAD__ vstore_half4_rte(float4 x, size_t index, half *p);
void __OVERLOAD__ vstore_half4_rte(float4 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half4_rte(float4 x, size_t index, __local half *p);
void __OVERLOAD__ vstore_half4_rte(double4 x, size_t index, half *p);
void __OVERLOAD__ vstore_half4_rte(double4 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half4_rte(double4 x, size_t index, __local half *p);

/* vstore_half8_rte */
void __OVERLOAD__ vstore_half8_rte(float8 x, size_t index, half *p);
void __OVERLOAD__ vstore_half8_rte(float8 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half8_rte(float8 x, size_t index, __local half *p);
void __OVERLOAD__ vstore_half8_rte(double8 x, size_t index, half *p);
void __OVERLOAD__ vstore_half8_rte(double8 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half8_rte(double8 x, size_t index, __local half *p);

/* vstore_half16_rte */
void __OVERLOAD__ vstore_half16_rte(float16 x, size_t index, half *p);
void __OVERLOAD__ vstore_half16_rte(float16 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half16_rte(float16 x, size_t index, __local half *p);
void __OVERLOAD__ vstore_half16_rte(double16 x, size_t index, half *p);
void __OVERLOAD__ vstore_half16_rte(double16 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half16_rte(double16 x, size_t index, __local half *p);

/* vstorea_half_rte */
void __OVERLOAD__ vstorea_half_rte(float f, size_t index, half *p);
void __OVERLOAD__ vstorea_half_rte(float f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half_rte(float f, size_t index, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstorea_half_rte(double f, size_t index, half *p);
void __OVERLOAD__ vstorea_half_rte(double f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half_rte(double f, size_t index, __local half *p);
#endif
#define vstorea_half_rte( X, Y, Z )     vstore_half_rte( X, Y, Z )

/* vstorea_half2_rte */
void __OVERLOAD__ vstorea_half2_rte(float2 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half2_rte(float2 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half2_rte(float2 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half2_rte( double2 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half2_rte( double2 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half2_rte( double2 x, size_t index, __local half *p );

/* vstorea_half3_rte */
void __OVERLOAD__ vstorea_half3_rte(float3 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half3_rte(float3 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half3_rte(float3 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half3_rte( double3 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half3_rte( double3 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half3_rte( double3 x, size_t index, __local half *p );

/* vstorea_half4_rte */
void __OVERLOAD__ vstorea_half4_rte(float4 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half4_rte(float4 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half4_rte(float4 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half4_rte( double4 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half4_rte( double4 x, size_t index, __global  half *p );
void __OVERLOAD__ vstorea_half4_rte( double4 x, size_t index, __local half *p );

/* vstorea_half8_rte */
void __OVERLOAD__ vstorea_half8_rte(float8 x, size_t index, half *p);
void __OVERLOAD__ vstorea_half8_rte(float8 x, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half8_rte(float8 x, size_t index, __local half *p);
void __OVERLOAD__ vstorea_half8_rte( double8 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half8_rte( double8 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half8_rte( double8 x, size_t index, __local half *p );

/* vstorea_half16_rte */
void __OVERLOAD__ vstorea_half16_rte(float16 x, size_t index, half *p);
void __OVERLOAD__ vstorea_half16_rte(float16 x, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half16_rte(float16 x, size_t index, __local half *p);
void __OVERLOAD__ vstorea_half16_rte( double16 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half16_rte( double16 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half16_rte( double16 x, size_t index, __local half *p );

/* vstore_half_rtz */
void __OVERLOAD__ vstore_half_rtz(float f, size_t i, half *p);
void __OVERLOAD__ vstore_half_rtz(float f, size_t i, __global half *p);
void __OVERLOAD__ vstore_half_rtz(float f, size_t i, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore_half_rtz(double f, size_t index, half *p);
void __OVERLOAD__ vstore_half_rtz(double f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half_rtz(double f, size_t index, __local half *p);
#endif
/* vstore_half2_rtz */
void __OVERLOAD__ vstore_half2_rtz(float2 f, size_t i, half *p);
void __OVERLOAD__ vstore_half2_rtz(float2 f, size_t i, __global half *p);
void __OVERLOAD__ vstore_half2_rtz(float2 f, size_t i, __local half *p);
void __OVERLOAD__ vstore_half2_rtz(double2 x, size_t index, half *p);
void __OVERLOAD__ vstore_half2_rtz(double2 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half2_rtz(double2 x, size_t index, __local half *p);

/* vstore_half3_rtz */
void __OVERLOAD__ vstore_half3_rtz(float3 f, size_t i, half *p);
void __OVERLOAD__ vstore_half3_rtz(float3 f, size_t i, __global half *p);
void __OVERLOAD__ vstore_half3_rtz(float3 f, size_t i, __local half *p);
void __OVERLOAD__ vstore_half3_rtz( double3 x, size_t index, half *p );
void __OVERLOAD__ vstore_half3_rtz( double3 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half3_rtz( double3 x, size_t index, __local half *p );

/* vstore_half4_rtz */
void __OVERLOAD__ vstore_half4_rtz(float4 f, size_t i, half *p);
void __OVERLOAD__ vstore_half4_rtz(float4 f, size_t i, __global half *p);
void __OVERLOAD__ vstore_half4_rtz(float4 f, size_t i, __local half *p);
void __OVERLOAD__ vstore_half4_rtz( double4 x, size_t index, half *p );
void __OVERLOAD__ vstore_half4_rtz( double4 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half4_rtz( double4 x, size_t index, __local half *p );

/* vstore_half8_rtz */
void __OVERLOAD__ vstore_half8_rtz(float8 f, size_t i, half *p);
void __OVERLOAD__ vstore_half8_rtz(float8 f, size_t i, __global half *p);
void __OVERLOAD__ vstore_half8_rtz(float8 f, size_t i, __local half *p);
void __OVERLOAD__ vstore_half8_rtz( double8 x, size_t index, half *p );
void __OVERLOAD__ vstore_half8_rtz( double8 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half8_rtz( double8 x, size_t index, __local half *p );

/* vstore_half16_rtz */
void __OVERLOAD__ vstore_half16_rtz(float16 f, size_t i, half *p);
void __OVERLOAD__ vstore_half16_rtz(float16 f, size_t i, __global half *p);
void __OVERLOAD__ vstore_half16_rtz(float16 f, size_t i, __local half *p);
void __OVERLOAD__ vstore_half16_rtz( double16 x, size_t index, half *p );
void __OVERLOAD__ vstore_half16_rtz( double16 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half16_rtz( double16 x, size_t index, __local half *p );

/* vstorea_half_rtz */
void __OVERLOAD__ vstorea_half_rtz(float f, size_t i, half *p);
void __OVERLOAD__ vstorea_half_rtz(float f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half_rtz(float f, size_t i, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstorea_half_rtz(double f, size_t index, half *p);
void __OVERLOAD__ vstorea_half_rtz(double f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half_rtz(double f, size_t index, __local half *p);
#endif
#define vstorea_half_rtz( X, Y, Z )     vstore_half_rtz( X, Y, Z )

/* vstorea_half2_rtz */
void __OVERLOAD__ vstorea_half2_rtz(float2 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half2_rtz(float2 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half2_rtz(float2 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half2_rtz( double2 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half2_rtz( double2 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half2_rtz( double2 x, size_t index, __local half *p );

/* vstorea_half3_rtz */
void __OVERLOAD__ vstorea_half3_rtz(float3 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half3_rtz(float3 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half3_rtz(float3 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half3_rtz( double3 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half3_rtz( double3 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half3_rtz( double3 x, size_t index, __local half *p );

/* vstorea_half4_rtz */
void __OVERLOAD__ vstorea_half4_rtz(float4 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half4_rtz(float4 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half4_rtz(float4 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half4_rtz( double4 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half4_rtz( double4 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half4_rtz( double4 x, size_t index, __local half *p );

/* vstorea_half8_rtz */
void __OVERLOAD__ vstorea_half8_rtz(float8 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half8_rtz(float8 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half8_rtz(float8 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half8_rtz( double8 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half8_rtz( double8 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half8_rtz( double8 x, size_t index, __local half *p );

/* vstorea_half16_rtz */
void __OVERLOAD__ vstorea_half16_rtz(float16 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half16_rtz(float16 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half16_rtz(float16 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half16_rtz( double16 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half16_rtz( double16 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half16_rtz( double16 x, size_t index, __local half *p );

/* vstore_half_rtp */
void __OVERLOAD__ vstore_half_rtp(float f, size_t index, half *p);
void __OVERLOAD__ vstore_half_rtp(float f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half_rtp(float f, size_t index, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore_half_rtp(double f, size_t index, half *p);
void __OVERLOAD__ vstore_half_rtp(double f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half_rtp(double f, size_t index, __local half *p);
#endif

/* vstore_half2_rtp */
void __OVERLOAD__ vstore_half2_rtp(float2 f, size_t i , half *p);
void __OVERLOAD__ vstore_half2_rtp(float2 f, size_t i , __global half *p);
void __OVERLOAD__ vstore_half2_rtp(float2 f, size_t i , __local half *p);
void __OVERLOAD__ vstore_half2_rtp(double2 x, size_t index, half *p);
void __OVERLOAD__ vstore_half2_rtp(double2 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half2_rtp(double2 x, size_t index, __local half *p);

/* vstore_half3_rtp */
void __OVERLOAD__ vstore_half3_rtp(float3 f, size_t i , half *p);
void __OVERLOAD__ vstore_half3_rtp(float3 f, size_t i , __global half *p);
void __OVERLOAD__ vstore_half3_rtp(float3 f, size_t i , __local half *p);
void __OVERLOAD__ vstore_half3_rtp( double3 x, size_t index, half *p );
void __OVERLOAD__ vstore_half3_rtp( double3 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half3_rtp( double3 x, size_t index, __local half *p );

/* vstore_half4_rtp */
void __OVERLOAD__ vstore_half4_rtp(float4 f, size_t i , half *p);
void __OVERLOAD__ vstore_half4_rtp(float4 f, size_t i , __global half *p);
void __OVERLOAD__ vstore_half4_rtp(float4 f, size_t i , __local half *p);
void __OVERLOAD__ vstore_half4_rtp( double4 x, size_t index, half *p );
void __OVERLOAD__ vstore_half4_rtp( double4 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half4_rtp( double4 x, size_t index, __local half *p );

/* vstore_half8_rtp */
void __OVERLOAD__ vstore_half8_rtp(float8 f, size_t i , half *p);
void __OVERLOAD__ vstore_half8_rtp(float8 f, size_t i , __global half *p);
void __OVERLOAD__ vstore_half8_rtp(float8 f, size_t i , __local half *p);
void __OVERLOAD__ vstore_half8_rtp( double8 x, size_t index, half *p );
void __OVERLOAD__ vstore_half8_rtp( double8 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half8_rtp( double8 x, size_t index, __local half *p );

/* vstore_half16_rtp */
void __OVERLOAD__ vstore_half16_rtp(float16 f, size_t i , half *p);
void __OVERLOAD__ vstore_half16_rtp(float16 f, size_t i , __global half *p);
void __OVERLOAD__ vstore_half16_rtp(float16 f, size_t i , __local half *p);
void __OVERLOAD__ vstore_half16_rtp( double16 x, size_t index, half *p );
void __OVERLOAD__ vstore_half16_rtp( double16 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half16_rtp( double16 x, size_t index, __local half *p );

/* vstorea_half_rtp */
void __OVERLOAD__ vstorea_half_rtp(float f, size_t index, half *p);
void __OVERLOAD__ vstorea_half_rtp(float f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half_rtp(float f, size_t index, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstorea_half_rtp(double f, size_t index, half *p);
void __OVERLOAD__ vstorea_half_rtp(double f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half_rtp(double f, size_t index, __local half *p);
#endif
#define vstorea_half_rtp( X, Y, Z )     vstore_half_rtp( X, Y, Z )

/* vstorea_half2_rtp */
void __OVERLOAD__ vstorea_half2_rtp(float2 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half2_rtp(float2 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half2_rtp(float2 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half2_rtp( double2 x, size_t index, half *p);
void __OVERLOAD__ vstorea_half2_rtp( double2 x, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half2_rtp( double2 x, size_t index, __local half *p);

/* vstorea_half3_rtp */
void __OVERLOAD__ vstorea_half3_rtp(float3 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half3_rtp(float3 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half3_rtp(float3 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half3_rtp( double3 x, size_t index, half *p);
void __OVERLOAD__ vstorea_half3_rtp( double3 x, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half3_rtp( double3 x, size_t index, __local half *p);

/* vstorea_half4_rtp */
void __OVERLOAD__ vstorea_half4_rtp(float4 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half4_rtp(float4 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half4_rtp(float4 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half4_rtp( double4 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half4_rtp( double4 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half4_rtp( double4 x, size_t index, __local half *p );

/* vstorea_half8_rtp */
void __OVERLOAD__ vstorea_half8_rtp(float8 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half8_rtp(float8 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half8_rtp(float8 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half8_rtp( double8 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half8_rtp( double8 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half8_rtp( double8 x, size_t index, __local half *p );

/* vstorea_half16_rtp */
void __OVERLOAD__ vstorea_half16_rtp(float16 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half16_rtp(float16 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half16_rtp(float16 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half16_rtp( double16 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half16_rtp( double16 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half16_rtp( double16 x, size_t index, __local half *p );

/* vstore_half_rtn */
void __OVERLOAD__ vstore_half_rtn(float f, size_t index, half *p);
void __OVERLOAD__ vstore_half_rtn(float f, size_t index, __global half *p);
void __OVERLOAD__ vstore_half_rtn(float f, size_t index, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstore_half_rtn( double x, size_t index, half *p );
void __OVERLOAD__ vstore_half_rtn( double x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half_rtn( double x, size_t index, __local half *p );
#endif

/* vstore_half2_rtn */
void __OVERLOAD__ vstore_half2_rtn(float2 f, size_t i, half *p);
void __OVERLOAD__ vstore_half2_rtn(float2 f, size_t i, __global half *p);
void __OVERLOAD__ vstore_half2_rtn(float2 f, size_t i, __local half *p);
void __OVERLOAD__ vstore_half2_rtn(double2 x, size_t index, half *p);
void __OVERLOAD__ vstore_half2_rtn(double2 x, size_t index, __global half *p);
void __OVERLOAD__ vstore_half2_rtn(double2 x, size_t index, __local half *p);

/* vstore_half3_rtn */
void __OVERLOAD__ vstore_half3_rtn(float3 x3, size_t i, half *p);
void __OVERLOAD__ vstore_half3_rtn(float3 x3, size_t i, __global half *p);
void __OVERLOAD__ vstore_half3_rtn(float3 x3, size_t i, __local half *p);
void __OVERLOAD__ vstore_half3_rtn( double3 x, size_t index, half *p );
void __OVERLOAD__ vstore_half3_rtn( double3 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half3_rtn( double3 x, size_t index, __local half *p );

/* vstore_half4_rtn */
void __OVERLOAD__ vstore_half4_rtn(float4 x, size_t i, half *p);
void __OVERLOAD__ vstore_half4_rtn(float4 x, size_t i, __global half *p);
void __OVERLOAD__ vstore_half4_rtn(float4 x, size_t i, __local half *p);
void __OVERLOAD__ vstore_half4_rtn( double4 x, size_t index, half *p );
void __OVERLOAD__ vstore_half4_rtn( double4 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half4_rtn( double4 x, size_t index, __local half *p );

/* vstore_half8_rtn */
void __OVERLOAD__ vstore_half8_rtn(float8 x, size_t i, half *p);
void __OVERLOAD__ vstore_half8_rtn(float8 x, size_t i, __global half *p);
void __OVERLOAD__ vstore_half8_rtn(float8 x, size_t i, __local half *p);
void __OVERLOAD__ vstore_half8_rtn( double8 x, size_t index, half *p );
void __OVERLOAD__ vstore_half8_rtn( double8 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half8_rtn( double8 x, size_t index, __local half *p );

/* vstore_half16_rtn */
void __OVERLOAD__ vstore_half16_rtn(float16 v, size_t i, half *p);
void __OVERLOAD__ vstore_half16_rtn(float16 v, size_t i, __global half *p);
void __OVERLOAD__ vstore_half16_rtn(float16 v, size_t i, __local half *p);
void __OVERLOAD__ vstore_half16_rtn( double16 x, size_t index, half *p );
void __OVERLOAD__ vstore_half16_rtn( double16 x, size_t index, __global half *p );
void __OVERLOAD__ vstore_half16_rtn( double16 x, size_t index, __local half *p );

/* vstorea_half_rtn */
void __OVERLOAD__ vstorea_half_rtn(float f, size_t index, half *p);
void __OVERLOAD__ vstorea_half_rtn(float f, size_t index, __global half *p);
void __OVERLOAD__ vstorea_half_rtn(float f, size_t index, __local half *p);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__ vstorea_half_rtn( double x, size_t index, half *p );
void __OVERLOAD__ vstorea_half_rtn( double x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half_rtn( double x, size_t index, __local half *p );
#endif
#define vstorea_half_rtn( X, Y, Z )     vstore_half_rtn( X, Y, Z )

/* vstorea_half2_rtn */
void __OVERLOAD__ vstorea_half2_rtn(float2 f, size_t i, half *p);
void __OVERLOAD__ vstorea_half2_rtn(float2 f, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half2_rtn(float2 f, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half2_rtn( double2 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half2_rtn( double2 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half2_rtn( double2 x, size_t index, __local half *p );

/* vstorea_half3_rtn */
void __OVERLOAD__ vstorea_half3_rtn(float3 x3, size_t i, half *p);
void __OVERLOAD__ vstorea_half3_rtn(float3 x3, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half3_rtn(float3 x3, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half3_rtn( double3 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half3_rtn( double3 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half3_rtn( double3 x, size_t index, __local half *p );

/* vstorea_half4_rtn */
void __OVERLOAD__ vstorea_half4_rtn(float4 x, size_t i, half *p);
void __OVERLOAD__ vstorea_half4_rtn(float4 x, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half4_rtn(float4 x, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half4_rtn( double4 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half4_rtn( double4 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half4_rtn( double4 x, size_t index, __local half *p );

/* vstorea_half8_rtn */
void __OVERLOAD__ vstorea_half8_rtn(float8 x, size_t i, half *p);
void __OVERLOAD__ vstorea_half8_rtn(float8 x, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half8_rtn(float8 x, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half8_rtn( double8 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half8_rtn( double8 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half8_rtn( double8 x, size_t index, __local half *p );

/* vstorea_half16_rtn */
void __OVERLOAD__ vstorea_half16_rtn(float16 v, size_t i, half *p);
void __OVERLOAD__ vstorea_half16_rtn(float16 v, size_t i, __global half *p);
void __OVERLOAD__ vstorea_half16_rtn(float16 v, size_t i, __local half *p);
void __OVERLOAD__ vstorea_half16_rtn( double16 x, size_t index, half *p );
void __OVERLOAD__ vstorea_half16_rtn( double16 x, size_t index, __global half *p );
void __OVERLOAD__ vstorea_half16_rtn( double16 x, size_t index, __local half *p );


// Vector Components / Constructors to be backward compatible with initial release though they are not in the OpenCL1.0 spec.
#define make_uchar2(A,B) (uchar2)((A),(B))
#define make_uchar3(A,B,C) (uchar3)((A),(B),(C))
#define make_uchar4(A,B,C,D) (uchar4)((A),(B),(C),(D))
#define make_uchar8(A,B,C,D,E,F,G,H) (uchar8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_uchar16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (uchar16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_char2(A,B) (char2)((A),(B))
#define make_char3(A,B,C) (char3)((A),(B),(C))
#define make_char4(A,B,C,D) (char4)((A),(B),(C),(D))
#define make_char8(A,B,C,D,E,F,G,H) (char8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_char16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (char16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_short2(A,B) (short2)((A),(B))
#define make_short3(A,B,C) (short3)((A),(B),(C))
#define make_short4(A,B,C,D) (short4)((A),(B),(C),(D))
#define make_short8(A,B,C,D,E,F,G,H) (short8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_short16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (short16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_ushort2(A,B) (ushort2)((A),(B))
#define make_ushort3(A,B,C) (ushort3)((A),(B),(C))
#define make_ushort4(A,B,C,D) (ushort4)((A),(B),(C),(D))
#define make_ushort8(A,B,C,D,E,F,G,H) (ushort8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_ushort16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (ushort16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_int2(A,B) (int2)((A),(B))
#define make_int3(A,B,C) (int3)((A),(B),(C))
#define make_int4(A,B,C,D) (int4)((A),(B),(C),(D))
#define make_int8(A,B,C,D,E,F,G,H) (int8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_int16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (int16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_uint2(A,B) (uint2)((A),(B))
#define make_uint3(A,B,C) (uint3)((A),(B),(C))
#define make_uint4(A,B,C,D) (uint4)((A),(B),(C),(D))
#define make_uint8(A,B,C,D,E,F,G,H) (uint8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_uint16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (uint16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_long2(A,B) (long2)((A),(B))
#define make_long3(A,B,C) (long3)((A),(B),(C))
#define make_long4(A,B,C,D) (long4)((A),(B),(C),(D))
#define make_long8(A,B,C,D,E,F,G,H) (long8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_long16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (long16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_ulong2(A,B) (ulong2)((A),(B))
#define make_ulong3(A,B,C) (ulong3)((A),(B),(C))
#define make_ulong4(A,B,C,D) (ulong4)((A),(B),(C),(D))
#define make_ulong8(A,B,C,D,E,F,G,H) (ulong8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_ulong16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (ulong16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_float2(A,B) (float2)((A),(B))
#define make_float3(A,B,C) (float3)((A),(B),(C))
#define make_float3_SPI(A,B,C) (float3)((A),(B),(C))
#define make_float4(A,B,C,D) (float4)((A),(B),(C),(D))
#define make_float8(A,B,C,D,E,F,G,H) (float8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_float16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (float16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))

#define make_double2(A,B) (double2)((A),(B))
#define make_double3(A,B,C) (double3)((A),(B),(C))
#define make_double4(A,B,C,D) (double4)((A),(B),(C),(D))
#define make_double8(A,B,C,D,E,F,G,H) (double8)((A),(B),(C),(D),(E),(F),(G),(H))
#define make_double16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (double16)((A),(B),(C),(D),(E),(F),(G),(H),(I),(J),(K),(L),(M),(N),(O),(P))


#if !defined(__AIR64__)
// 5.2.3 convert_ operators
typedef enum
{
    __kDefaultRoundingMode = 0,
    __kRoundToNearestEven = 1,
    __kRoundTowardNegativeInf = 2,
    __kRoundTowardInf = 3,
    __kRoundTowardZero = 4
}__clRoundingMode;

typedef enum
{
    __kUnsaturated = 0,
    __kSaturated = 1
}__clSaturationMode;

#if defined( __PTX__ )

    //type
    #define convert_char(_X)    __builtin_convert(_X, char, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uchar(_X)   __builtin_convert(_X, uchar, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_short(_X)   __builtin_convert(_X, short, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ushort(_X)  __builtin_convert(_X, ushort, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_int(_X)     __builtin_convert(_X, int, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uint(_X)    __builtin_convert(_X, uint, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_long(_X)    __builtin_convert(_X, long, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ulong(_X)   __builtin_convert(_X, ulong, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_float(_X)   __builtin_convert(_X, float, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_double(_X)  __builtin_convert(_X, double, __kDefaultRoundingMode, __kUnsaturated )

    #define convert_char_sat(_X)    __builtin_convert(_X, char, __kDefaultRoundingMode, __kSaturated )
    #define convert_uchar_sat(_X)   __builtin_convert(_X, uchar, __kDefaultRoundingMode, __kSaturated )
    #define convert_short_sat(_X)   __builtin_convert(_X, short, __kDefaultRoundingMode, __kSaturated )
    #define convert_ushort_sat(_X)  __builtin_convert(_X, ushort, __kDefaultRoundingMode, __kSaturated )
    #define convert_int_sat(_X)     __builtin_convert(_X, int, __kDefaultRoundingMode, __kSaturated )
    #define convert_uint_sat(_X)    __builtin_convert(_X, uint, __kDefaultRoundingMode, __kSaturated )
    #define convert_long_sat(_X)    __builtin_convert(_X, long, __kDefaultRoundingMode, __kSaturated )
    #define convert_ulong_sat(_X)   __builtin_convert(_X, ulong, __kDefaultRoundingMode, __kSaturated )
    #define convert_float_sat(_X)   __builtin_convert(_X, float, __kDefaultRoundingMode, __kSaturated )
    #define convert_double_sat(_X)  __builtin_convert(_X, double, __kDefaultRoundingMode, __kSaturated )

    #define convert_char_rte(_X)    __builtin_convert(_X, char, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uchar_rte(_X)   __builtin_convert(_X, uchar, __kRoundToNearestEven, __kUnsaturated )
    #define convert_short_rte(_X)   __builtin_convert(_X, short, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ushort_rte(_X)  __builtin_convert(_X, ushort, __kRoundToNearestEven, __kUnsaturated )
    #define convert_int_rte(_X)     __builtin_convert(_X, int, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uint_rte(_X)    __builtin_convert(_X, uint, __kRoundToNearestEven, __kUnsaturated )
    #define convert_long_rte(_X)    __builtin_convert(_X, long, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ulong_rte(_X)   __builtin_convert(_X, ulong, __kRoundToNearestEven, __kUnsaturated )
    #define convert_float_rte(_X)   __builtin_convert(_X, float, __kRoundToNearestEven, __kUnsaturated )
    #define convert_double_rte(_X)  __builtin_convert(_X, double, __kRoundToNearestEven, __kUnsaturated )

    #define convert_char_sat_rte(_X)    __builtin_convert(_X, char, __kRoundToNearestEven, __kSaturated )
    #define convert_uchar_sat_rte(_X)   __builtin_convert(_X, uchar, __kRoundToNearestEven, __kSaturated )
    #define convert_short_sat_rte(_X)   __builtin_convert(_X, short, __kRoundToNearestEven, __kSaturated )
    #define convert_ushort_sat_rte(_X)  __builtin_convert(_X, ushort, __kRoundToNearestEven, __kSaturated )
    #define convert_int_sat_rte(_X)     __builtin_convert(_X, int, __kRoundToNearestEven, __kSaturated )
    #define convert_uint_sat_rte(_X)    __builtin_convert(_X, uint, __kRoundToNearestEven, __kSaturated )
    #define convert_long_sat_rte(_X)    __builtin_convert(_X, long, __kRoundToNearestEven, __kSaturated )
    #define convert_ulong_sat_rte(_X)   __builtin_convert(_X, ulong, __kRoundToNearestEven, __kSaturated )
    #define convert_float_sat_rte(_X)   __builtin_convert(_X, float, __kRoundToNearestEven, __kSaturated )
    #define convert_double_sat_rte(_X)  __builtin_convert(_X, double, __kRoundToNearestEven, __kSaturated )

    #define convert_char_rtn(_X)    __builtin_convert(_X, char, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uchar_rtn(_X)   __builtin_convert(_X, uchar, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_short_rtn(_X)   __builtin_convert(_X, short, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ushort_rtn(_X)  __builtin_convert(_X, ushort, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_int_rtn(_X)     __builtin_convert(_X, int, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uint_rtn(_X)    __builtin_convert(_X, uint, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_long_rtn(_X)    __builtin_convert(_X, long, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ulong_rtn(_X)   __builtin_convert(_X, ulong, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_float_rtn(_X)   __builtin_convert(_X, float, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_double_rtn(_X)  __builtin_convert(_X, double, __kRoundTowardNegativeInf, __kUnsaturated )

    #define convert_char_sat_rtn(_X)    __builtin_convert(_X, char, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uchar_sat_rtn(_X)   __builtin_convert(_X, uchar, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_short_sat_rtn(_X)   __builtin_convert(_X, short, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ushort_sat_rtn(_X)  __builtin_convert(_X, ushort, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_int_sat_rtn(_X)     __builtin_convert(_X, int, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uint_sat_rtn(_X)    __builtin_convert(_X, uint, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_long_sat_rtn(_X)    __builtin_convert(_X, long, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ulong_sat_rtn(_X)   __builtin_convert(_X, ulong, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_float_sat_rtn(_X)   __builtin_convert(_X, float, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_double_sat_rtn(_X)  __builtin_convert(_X, double, __kRoundTowardNegativeInf, __kSaturated )

    #define convert_char_rtp(_X)    __builtin_convert(_X, char, __kRoundTowardInf, __kUnsaturated )
    #define convert_uchar_rtp(_X)   __builtin_convert(_X, uchar, __kRoundTowardInf, __kUnsaturated )
    #define convert_short_rtp(_X)   __builtin_convert(_X, short, __kRoundTowardInf, __kUnsaturated )
    #define convert_ushort_rtp(_X)  __builtin_convert(_X, ushort, __kRoundTowardInf, __kUnsaturated )
    #define convert_int_rtp(_X)     __builtin_convert(_X, int, __kRoundTowardInf, __kUnsaturated )
    #define convert_uint_rtp(_X)    __builtin_convert(_X, uint, __kRoundTowardInf, __kUnsaturated )
    #define convert_long_rtp(_X)    __builtin_convert(_X, long, __kRoundTowardInf, __kUnsaturated )
    #define convert_ulong_rtp(_X)   __builtin_convert(_X, ulong, __kRoundTowardInf, __kUnsaturated )
    #define convert_float_rtp(_X)   __builtin_convert(_X, float, __kRoundTowardInf, __kUnsaturated )
    #define convert_double_rtp(_X)  __builtin_convert(_X, double, __kRoundTowardInf, __kUnsaturated )

    #define convert_char_sat_rtp(_X)    __builtin_convert(_X, char, __kRoundTowardInf, __kSaturated )
    #define convert_uchar_sat_rtp(_X)   __builtin_convert(_X, uchar, __kRoundTowardInf, __kSaturated )
    #define convert_short_sat_rtp(_X)   __builtin_convert(_X, short, __kRoundTowardInf, __kSaturated )
    #define convert_ushort_sat_rtp(_X)  __builtin_convert(_X, ushort, __kRoundTowardInf, __kSaturated )
    #define convert_int_sat_rtp(_X)     __builtin_convert(_X, int, __kRoundTowardInf, __kSaturated )
    #define convert_uint_sat_rtp(_X)    __builtin_convert(_X, uint, __kRoundTowardInf, __kSaturated )
    #define convert_long_sat_rtp(_X)    __builtin_convert(_X, long, __kRoundTowardInf, __kSaturated )
    #define convert_ulong_sat_rtp(_X)   __builtin_convert(_X, ulong, __kRoundTowardInf, __kSaturated )
    #define convert_float_sat_rtp(_X)   __builtin_convert(_X, float, __kRoundTowardInf, __kSaturated )
    #define convert_double_sat_rtp(_X)  __builtin_convert(_X, double, __kRoundTowardInf, __kSaturated )

    #define convert_char_rtz(_X)    __builtin_convert(_X, char, __kRoundTowardZero, __kUnsaturated )
    #define convert_uchar_rtz(_X)   __builtin_convert(_X, uchar, __kRoundTowardZero, __kUnsaturated )
    #define convert_short_rtz(_X)   __builtin_convert(_X, short, __kRoundTowardZero, __kUnsaturated )
    #define convert_ushort_rtz(_X)  __builtin_convert(_X, ushort, __kRoundTowardZero, __kUnsaturated )
    #define convert_int_rtz(_X)     __builtin_convert(_X, int, __kRoundTowardZero, __kUnsaturated )
    #define convert_uint_rtz(_X)    __builtin_convert(_X, uint, __kRoundTowardZero, __kUnsaturated )
    #define convert_long_rtz(_X)    __builtin_convert(_X, long, __kRoundTowardZero, __kUnsaturated )
    #define convert_ulong_rtz(_X)   __builtin_convert(_X, ulong, __kRoundTowardZero, __kUnsaturated )
    #define convert_float_rtz(_X)   __builtin_convert(_X, float, __kRoundTowardZero, __kUnsaturated )
    #define convert_double_rtz(_X)  __builtin_convert(_X, double, __kRoundTowardZero, __kUnsaturated )

    #define convert_char_sat_rtz(_X)    __builtin_convert(_X, char, __kRoundTowardZero, __kSaturated )
    #define convert_uchar_sat_rtz(_X)   __builtin_convert(_X, uchar, __kRoundTowardZero, __kSaturated )
    #define convert_short_sat_rtz(_X)   __builtin_convert(_X, short, __kRoundTowardZero, __kSaturated )
    #define convert_ushort_sat_rtz(_X)  __builtin_convert(_X, ushort, __kRoundTowardZero, __kSaturated )
    #define convert_int_sat_rtz(_X)     __builtin_convert(_X, int, __kRoundTowardZero, __kSaturated )
    #define convert_uint_sat_rtz(_X)    __builtin_convert(_X, uint, __kRoundTowardZero, __kSaturated )
    #define convert_long_sat_rtz(_X)    __builtin_convert(_X, long, __kRoundTowardZero, __kSaturated )
    #define convert_ulong_sat_rtz(_X)   __builtin_convert(_X, ulong, __kRoundTowardZero, __kSaturated )
    #define convert_float_sat_rtz(_X)   __builtin_convert(_X, float, __kRoundTowardZero, __kSaturated )
    #define convert_double_sat_rtz(_X)  __builtin_convert(_X, double, __kRoundTowardZero, __kSaturated )

    //type2
    #define convert_char2(_X)    __builtin_convert(_X, char2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uchar2(_X)   __builtin_convert(_X, uchar2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_short2(_X)   __builtin_convert(_X, short2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ushort2(_X)  __builtin_convert(_X, ushort2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_int2(_X)     __builtin_convert(_X, int2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uint2(_X)    __builtin_convert(_X, uint2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_long2(_X)    __builtin_convert(_X, long2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ulong2(_X)   __builtin_convert(_X, ulong2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_float2(_X)   __builtin_convert(_X, float2, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_double2(_X)  __builtin_convert(_X, double2, __kDefaultRoundingMode, __kUnsaturated )

    #define convert_char2_sat(_X)    __builtin_convert(_X, char2, __kDefaultRoundingMode, __kSaturated )
    #define convert_uchar2_sat(_X)   __builtin_convert(_X, uchar2, __kDefaultRoundingMode, __kSaturated )
    #define convert_short2_sat(_X)   __builtin_convert(_X, short2, __kDefaultRoundingMode, __kSaturated )
    #define convert_ushort2_sat(_X)  __builtin_convert(_X, ushort2, __kDefaultRoundingMode, __kSaturated )
    #define convert_int2_sat(_X)     __builtin_convert(_X, int2, __kDefaultRoundingMode, __kSaturated )
    #define convert_uint2_sat(_X)    __builtin_convert(_X, uint2, __kDefaultRoundingMode, __kSaturated )
    #define convert_long2_sat(_X)    __builtin_convert(_X, long2, __kDefaultRoundingMode, __kSaturated )
    #define convert_ulong2_sat(_X)   __builtin_convert(_X, ulong2, __kDefaultRoundingMode, __kSaturated )
    #define convert_float2_sat(_X)   __builtin_convert(_X, float2, __kDefaultRoundingMode, __kSaturated )
    #define convert_double2_sat(_X)  __builtin_convert(_X, double2, __kDefaultRoundingMode, __kSaturated )

    #define convert_char2_rte(_X)    __builtin_convert(_X, char2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uchar2_rte(_X)   __builtin_convert(_X, uchar2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_short2_rte(_X)   __builtin_convert(_X, short2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ushort2_rte(_X)  __builtin_convert(_X, ushort2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_int2_rte(_X)     __builtin_convert(_X, int2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uint2_rte(_X)    __builtin_convert(_X, uint2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_long2_rte(_X)    __builtin_convert(_X, long2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ulong2_rte(_X)   __builtin_convert(_X, ulong2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_float2_rte(_X)   __builtin_convert(_X, float2, __kRoundToNearestEven, __kUnsaturated )
    #define convert_double2_rte(_X)  __builtin_convert(_X, double2, __kRoundToNearestEven, __kUnsaturated )

    #define convert_char2_sat_rte(_X)    __builtin_convert(_X, char2, __kRoundToNearestEven, __kSaturated )
    #define convert_uchar2_sat_rte(_X)   __builtin_convert(_X, uchar2, __kRoundToNearestEven, __kSaturated )
    #define convert_short2_sat_rte(_X)   __builtin_convert(_X, short2, __kRoundToNearestEven, __kSaturated )
    #define convert_ushort2_sat_rte(_X)  __builtin_convert(_X, ushort2, __kRoundToNearestEven, __kSaturated )
    #define convert_int2_sat_rte(_X)     __builtin_convert(_X, int2, __kRoundToNearestEven, __kSaturated )
    #define convert_uint2_sat_rte(_X)    __builtin_convert(_X, uint2, __kRoundToNearestEven, __kSaturated )
    #define convert_long2_sat_rte(_X)    __builtin_convert(_X, long2, __kRoundToNearestEven, __kSaturated )
    #define convert_ulong2_sat_rte(_X)   __builtin_convert(_X, ulong2, __kRoundToNearestEven, __kSaturated )
    #define convert_float2_sat_rte(_X)   __builtin_convert(_X, float2, __kRoundToNearestEven, __kSaturated )
    #define convert_double2_sat_rte(_X)  __builtin_convert(_X, double2, __kRoundToNearestEven, __kSaturated )

    #define convert_char2_rtn(_X)    __builtin_convert(_X, char2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uchar2_rtn(_X)   __builtin_convert(_X, uchar2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_short2_rtn(_X)   __builtin_convert(_X, short2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ushort2_rtn(_X)  __builtin_convert(_X, ushort2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_int2_rtn(_X)     __builtin_convert(_X, int2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uint2_rtn(_X)    __builtin_convert(_X, uint2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_long2_rtn(_X)    __builtin_convert(_X, long2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ulong2_rtn(_X)   __builtin_convert(_X, ulong2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_float2_rtn(_X)   __builtin_convert(_X, float2, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_double2_rtn(_X)  __builtin_convert(_X, double2, __kRoundTowardNegativeInf, __kUnsaturated )

    #define convert_char2_sat_rtn(_X)    __builtin_convert(_X, char2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uchar2_sat_rtn(_X)   __builtin_convert(_X, uchar2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_short2_sat_rtn(_X)   __builtin_convert(_X, short2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ushort2_sat_rtn(_X)  __builtin_convert(_X, ushort2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_int2_sat_rtn(_X)     __builtin_convert(_X, int2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uint2_sat_rtn(_X)    __builtin_convert(_X, uint2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_long2_sat_rtn(_X)    __builtin_convert(_X, long2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ulong2_sat_rtn(_X)   __builtin_convert(_X, ulong2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_float2_sat_rtn(_X)   __builtin_convert(_X, float2, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_double2_sat_rtn(_X)  __builtin_convert(_X, double2, __kRoundTowardNegativeInf, __kSaturated )

    #define convert_char2_rtp(_X)    __builtin_convert(_X, char2, __kRoundTowardInf, __kUnsaturated )
    #define convert_uchar2_rtp(_X)   __builtin_convert(_X, uchar2, __kRoundTowardInf, __kUnsaturated )
    #define convert_short2_rtp(_X)   __builtin_convert(_X, short2, __kRoundTowardInf, __kUnsaturated )
    #define convert_ushort2_rtp(_X)  __builtin_convert(_X, ushort2, __kRoundTowardInf, __kUnsaturated )
    #define convert_int2_rtp(_X)     __builtin_convert(_X, int2, __kRoundTowardInf, __kUnsaturated )
    #define convert_uint2_rtp(_X)    __builtin_convert(_X, uint2, __kRoundTowardInf, __kUnsaturated )
    #define convert_long2_rtp(_X)    __builtin_convert(_X, long2, __kRoundTowardInf, __kUnsaturated )
    #define convert_ulong2_rtp(_X)   __builtin_convert(_X, ulong2, __kRoundTowardInf, __kUnsaturated )
    #define convert_float2_rtp(_X)   __builtin_convert(_X, float2, __kRoundTowardInf, __kUnsaturated )
    #define convert_double2_rtp(_X)  __builtin_convert(_X, double2, __kRoundTowardInf, __kUnsaturated )

    #define convert_char2_sat_rtp(_X)    __builtin_convert(_X, char2, __kRoundTowardInf, __kSaturated )
    #define convert_uchar2_sat_rtp(_X)   __builtin_convert(_X, uchar2, __kRoundTowardInf, __kSaturated )
    #define convert_short2_sat_rtp(_X)   __builtin_convert(_X, short2, __kRoundTowardInf, __kSaturated )
    #define convert_ushort2_sat_rtp(_X)  __builtin_convert(_X, ushort2, __kRoundTowardInf, __kSaturated )
    #define convert_int2_sat_rtp(_X)     __builtin_convert(_X, int2, __kRoundTowardInf, __kSaturated )
    #define convert_uint2_sat_rtp(_X)    __builtin_convert(_X, uint2, __kRoundTowardInf, __kSaturated )
    #define convert_long2_sat_rtp(_X)    __builtin_convert(_X, long2, __kRoundTowardInf, __kSaturated )
    #define convert_ulong2_sat_rtp(_X)   __builtin_convert(_X, ulong2, __kRoundTowardInf, __kSaturated )
    #define convert_float2_sat_rtp(_X)   __builtin_convert(_X, float2, __kRoundTowardInf, __kSaturated )
    #define convert_double2_sat_rtp(_X)  __builtin_convert(_X, double2, __kRoundTowardInf, __kSaturated )

    #define convert_char2_rtz(_X)    __builtin_convert(_X, char2, __kRoundTowardZero, __kUnsaturated )
    #define convert_uchar2_rtz(_X)   __builtin_convert(_X, uchar2, __kRoundTowardZero, __kUnsaturated )
    #define convert_short2_rtz(_X)   __builtin_convert(_X, short2, __kRoundTowardZero, __kUnsaturated )
    #define convert_ushort2_rtz(_X)  __builtin_convert(_X, ushort2, __kRoundTowardZero, __kUnsaturated )
    #define convert_int2_rtz(_X)     __builtin_convert(_X, int2, __kRoundTowardZero, __kUnsaturated )
    #define convert_uint2_rtz(_X)    __builtin_convert(_X, uint2, __kRoundTowardZero, __kUnsaturated )
    #define convert_long2_rtz(_X)    __builtin_convert(_X, long2, __kRoundTowardZero, __kUnsaturated )
    #define convert_ulong2_rtz(_X)   __builtin_convert(_X, ulong2, __kRoundTowardZero, __kUnsaturated )
    #define convert_float2_rtz(_X)   __builtin_convert(_X, float2, __kRoundTowardZero, __kUnsaturated )
    #define convert_double2_rtz(_X)  __builtin_convert(_X, double2, __kRoundTowardZero, __kUnsaturated )

    #define convert_char2_sat_rtz(_X)    __builtin_convert(_X, char2, __kRoundTowardZero, __kSaturated )
    #define convert_uchar2_sat_rtz(_X)   __builtin_convert(_X, uchar2, __kRoundTowardZero, __kSaturated )
    #define convert_short2_sat_rtz(_X)   __builtin_convert(_X, short2, __kRoundTowardZero, __kSaturated )
    #define convert_ushort2_sat_rtz(_X)  __builtin_convert(_X, ushort2, __kRoundTowardZero, __kSaturated )
    #define convert_int2_sat_rtz(_X)     __builtin_convert(_X, int2, __kRoundTowardZero, __kSaturated )
    #define convert_uint2_sat_rtz(_X)    __builtin_convert(_X, uint2, __kRoundTowardZero, __kSaturated )
    #define convert_long2_sat_rtz(_X)    __builtin_convert(_X, long2, __kRoundTowardZero, __kSaturated )
    #define convert_ulong2_sat_rtz(_X)   __builtin_convert(_X, ulong2, __kRoundTowardZero, __kSaturated )
    #define convert_float2_sat_rtz(_X)   __builtin_convert(_X, float2, __kRoundTowardZero, __kSaturated )
    #define convert_double2_sat_rtz(_X)  __builtin_convert(_X, double2, __kRoundTowardZero, __kSaturated )

    //type3
    #define convert_char3(_X)    __builtin_convert(_X, char3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uchar3(_X)   __builtin_convert(_X, uchar3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_short3(_X)   __builtin_convert(_X, short3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ushort3(_X)  __builtin_convert(_X, ushort3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_int3(_X)     __builtin_convert(_X, int3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uint3(_X)    __builtin_convert(_X, uint3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_long3(_X)    __builtin_convert(_X, long3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ulong3(_X)   __builtin_convert(_X, ulong3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_float3(_X)   __builtin_convert(_X, float3, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_double3(_X)  __builtin_convert(_X, double3, __kDefaultRoundingMode, __kUnsaturated )

    #define convert_char3_sat(_X)    __builtin_convert(_X, char3, __kDefaultRoundingMode, __kSaturated )
    #define convert_uchar3_sat(_X)   __builtin_convert(_X, uchar3, __kDefaultRoundingMode, __kSaturated )
    #define convert_short3_sat(_X)   __builtin_convert(_X, short3, __kDefaultRoundingMode, __kSaturated )
    #define convert_ushort3_sat(_X)  __builtin_convert(_X, ushort3, __kDefaultRoundingMode, __kSaturated )
    #define convert_int3_sat(_X)     __builtin_convert(_X, int3, __kDefaultRoundingMode, __kSaturated )
    #define convert_uint3_sat(_X)    __builtin_convert(_X, uint3, __kDefaultRoundingMode, __kSaturated )
    #define convert_long3_sat(_X)    __builtin_convert(_X, long3, __kDefaultRoundingMode, __kSaturated )
    #define convert_ulong3_sat(_X)   __builtin_convert(_X, ulong3, __kDefaultRoundingMode, __kSaturated )
    #define convert_float3_sat(_X)   __builtin_convert(_X, float3, __kDefaultRoundingMode, __kSaturated )
    #define convert_double3_sat(_X)  __builtin_convert(_X, double3, __kDefaultRoundingMode, __kSaturated )

    #define convert_char3_rte(_X)    __builtin_convert(_X, char3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uchar3_rte(_X)   __builtin_convert(_X, uchar3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_short3_rte(_X)   __builtin_convert(_X, short3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ushort3_rte(_X)  __builtin_convert(_X, ushort3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_int3_rte(_X)     __builtin_convert(_X, int3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uint3_rte(_X)    __builtin_convert(_X, uint3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_long3_rte(_X)    __builtin_convert(_X, long3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ulong3_rte(_X)   __builtin_convert(_X, ulong3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_float3_rte(_X)   __builtin_convert(_X, float3, __kRoundToNearestEven, __kUnsaturated )
    #define convert_double3_rte(_X)  __builtin_convert(_X, double3, __kRoundToNearestEven, __kUnsaturated )

    #define convert_char3_sat_rte(_X)    __builtin_convert(_X, char3, __kRoundToNearestEven, __kSaturated )
    #define convert_uchar3_sat_rte(_X)   __builtin_convert(_X, uchar3, __kRoundToNearestEven, __kSaturated )
    #define convert_short3_sat_rte(_X)   __builtin_convert(_X, short3, __kRoundToNearestEven, __kSaturated )
    #define convert_ushort3_sat_rte(_X)  __builtin_convert(_X, ushort3, __kRoundToNearestEven, __kSaturated )
    #define convert_int3_sat_rte(_X)     __builtin_convert(_X, int3, __kRoundToNearestEven, __kSaturated )
    #define convert_uint3_sat_rte(_X)    __builtin_convert(_X, uint3, __kRoundToNearestEven, __kSaturated )
    #define convert_long3_sat_rte(_X)    __builtin_convert(_X, long3, __kRoundToNearestEven, __kSaturated )
    #define convert_ulong3_sat_rte(_X)   __builtin_convert(_X, ulong3, __kRoundToNearestEven, __kSaturated )
    #define convert_float3_sat_rte(_X)   __builtin_convert(_X, float3, __kRoundToNearestEven, __kSaturated )
    #define convert_double3_sat_rte(_X)  __builtin_convert(_X, double3, __kRoundToNearestEven, __kSaturated )

    #define convert_char3_rtn(_X)    __builtin_convert(_X, char3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uchar3_rtn(_X)   __builtin_convert(_X, uchar3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_short3_rtn(_X)   __builtin_convert(_X, short3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ushort3_rtn(_X)  __builtin_convert(_X, ushort3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_int3_rtn(_X)     __builtin_convert(_X, int3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uint3_rtn(_X)    __builtin_convert(_X, uint3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_long3_rtn(_X)    __builtin_convert(_X, long3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ulong3_rtn(_X)   __builtin_convert(_X, ulong3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_float3_rtn(_X)   __builtin_convert(_X, float3, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_double3_rtn(_X)  __builtin_convert(_X, double3, __kRoundTowardNegativeInf, __kUnsaturated )

    #define convert_char3_sat_rtn(_X)    __builtin_convert(_X, char3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uchar3_sat_rtn(_X)   __builtin_convert(_X, uchar3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_short3_sat_rtn(_X)   __builtin_convert(_X, short3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ushort3_sat_rtn(_X)  __builtin_convert(_X, ushort3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_int3_sat_rtn(_X)     __builtin_convert(_X, int3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uint3_sat_rtn(_X)    __builtin_convert(_X, uint3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_long3_sat_rtn(_X)    __builtin_convert(_X, long3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ulong3_sat_rtn(_X)   __builtin_convert(_X, ulong3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_float3_sat_rtn(_X)   __builtin_convert(_X, float3, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_double3_sat_rtn(_X)  __builtin_convert(_X, double3, __kRoundTowardNegativeInf, __kSaturated )

    #define convert_char3_rtp(_X)    __builtin_convert(_X, char3, __kRoundTowardInf, __kUnsaturated )
    #define convert_uchar3_rtp(_X)   __builtin_convert(_X, uchar3, __kRoundTowardInf, __kUnsaturated )
    #define convert_short3_rtp(_X)   __builtin_convert(_X, short3, __kRoundTowardInf, __kUnsaturated )
    #define convert_ushort3_rtp(_X)  __builtin_convert(_X, ushort3, __kRoundTowardInf, __kUnsaturated )
    #define convert_int3_rtp(_X)     __builtin_convert(_X, int3, __kRoundTowardInf, __kUnsaturated )
    #define convert_uint3_rtp(_X)    __builtin_convert(_X, uint3, __kRoundTowardInf, __kUnsaturated )
    #define convert_long3_rtp(_X)    __builtin_convert(_X, long3, __kRoundTowardInf, __kUnsaturated )
    #define convert_ulong3_rtp(_X)   __builtin_convert(_X, ulong3, __kRoundTowardInf, __kUnsaturated )
    #define convert_float3_rtp(_X)   __builtin_convert(_X, float3, __kRoundTowardInf, __kUnsaturated )
    #define convert_double3_rtp(_X)  __builtin_convert(_X, double3, __kRoundTowardInf, __kUnsaturated )

    #define convert_char3_sat_rtp(_X)    __builtin_convert(_X, char3, __kRoundTowardInf, __kSaturated )
    #define convert_uchar3_sat_rtp(_X)   __builtin_convert(_X, uchar3, __kRoundTowardInf, __kSaturated )
    #define convert_short3_sat_rtp(_X)   __builtin_convert(_X, short3, __kRoundTowardInf, __kSaturated )
    #define convert_ushort3_sat_rtp(_X)  __builtin_convert(_X, ushort3, __kRoundTowardInf, __kSaturated )
    #define convert_int3_sat_rtp(_X)     __builtin_convert(_X, int3, __kRoundTowardInf, __kSaturated )
    #define convert_uint3_sat_rtp(_X)    __builtin_convert(_X, uint3, __kRoundTowardInf, __kSaturated )
    #define convert_long3_sat_rtp(_X)    __builtin_convert(_X, long3, __kRoundTowardInf, __kSaturated )
    #define convert_ulong3_sat_rtp(_X)   __builtin_convert(_X, ulong3, __kRoundTowardInf, __kSaturated )
    #define convert_float3_sat_rtp(_X)   __builtin_convert(_X, float3, __kRoundTowardInf, __kSaturated )
    #define convert_double3_sat_rtp(_X)  __builtin_convert(_X, double3, __kRoundTowardInf, __kSaturated )

    #define convert_char3_rtz(_X)    __builtin_convert(_X, char3, __kRoundTowardZero, __kUnsaturated )
    #define convert_uchar3_rtz(_X)   __builtin_convert(_X, uchar3, __kRoundTowardZero, __kUnsaturated )
    #define convert_short3_rtz(_X)   __builtin_convert(_X, short3, __kRoundTowardZero, __kUnsaturated )
    #define convert_ushort3_rtz(_X)  __builtin_convert(_X, ushort3, __kRoundTowardZero, __kUnsaturated )
    #define convert_int3_rtz(_X)     __builtin_convert(_X, int3, __kRoundTowardZero, __kUnsaturated )
    #define convert_uint3_rtz(_X)    __builtin_convert(_X, uint3, __kRoundTowardZero, __kUnsaturated )
    #define convert_long3_rtz(_X)    __builtin_convert(_X, long3, __kRoundTowardZero, __kUnsaturated )
    #define convert_ulong3_rtz(_X)   __builtin_convert(_X, ulong3, __kRoundTowardZero, __kUnsaturated )
    #define convert_float3_rtz(_X)   __builtin_convert(_X, float3, __kRoundTowardZero, __kUnsaturated )
    #define convert_double3_rtz(_X)  __builtin_convert(_X, double3, __kRoundTowardZero, __kUnsaturated )

    #define convert_char3_sat_rtz(_X)    __builtin_convert(_X, char3, __kRoundTowardZero, __kSaturated )
    #define convert_uchar3_sat_rtz(_X)   __builtin_convert(_X, uchar3, __kRoundTowardZero, __kSaturated )
    #define convert_short3_sat_rtz(_X)   __builtin_convert(_X, short3, __kRoundTowardZero, __kSaturated )
    #define convert_ushort3_sat_rtz(_X)  __builtin_convert(_X, ushort3, __kRoundTowardZero, __kSaturated )
    #define convert_int3_sat_rtz(_X)     __builtin_convert(_X, int3, __kRoundTowardZero, __kSaturated )
    #define convert_uint3_sat_rtz(_X)    __builtin_convert(_X, uint3, __kRoundTowardZero, __kSaturated )
    #define convert_long3_sat_rtz(_X)    __builtin_convert(_X, long3, __kRoundTowardZero, __kSaturated )
    #define convert_ulong3_sat_rtz(_X)   __builtin_convert(_X, ulong3, __kRoundTowardZero, __kSaturated )
    #define convert_float3_sat_rtz(_X)   __builtin_convert(_X, float3, __kRoundTowardZero, __kSaturated )
    #define convert_double3_sat_rtz(_X)  __builtin_convert(_X, double3, __kRoundTowardZero, __kSaturated )

    //type4
    #define convert_char4(_X)    __builtin_convert(_X, char4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uchar4(_X)   __builtin_convert(_X, uchar4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_short4(_X)   __builtin_convert(_X, short4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ushort4(_X)  __builtin_convert(_X, ushort4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_int4(_X)     __builtin_convert(_X, int4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uint4(_X)    __builtin_convert(_X, uint4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_long4(_X)    __builtin_convert(_X, long4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ulong4(_X)   __builtin_convert(_X, ulong4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_float4(_X)   __builtin_convert(_X, float4, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_double4(_X)  __builtin_convert(_X, double4, __kDefaultRoundingMode, __kUnsaturated )

    #define convert_char4_sat(_X)    __builtin_convert(_X, char4, __kDefaultRoundingMode, __kSaturated )
    #define convert_uchar4_sat(_X)   __builtin_convert(_X, uchar4, __kDefaultRoundingMode, __kSaturated )
    #define convert_short4_sat(_X)   __builtin_convert(_X, short4, __kDefaultRoundingMode, __kSaturated )
    #define convert_ushort4_sat(_X)  __builtin_convert(_X, ushort4, __kDefaultRoundingMode, __kSaturated )
    #define convert_int4_sat(_X)     __builtin_convert(_X, int4, __kDefaultRoundingMode, __kSaturated )
    #define convert_uint4_sat(_X)    __builtin_convert(_X, uint4, __kDefaultRoundingMode, __kSaturated )
    #define convert_long4_sat(_X)    __builtin_convert(_X, long4, __kDefaultRoundingMode, __kSaturated )
    #define convert_ulong4_sat(_X)   __builtin_convert(_X, ulong4, __kDefaultRoundingMode, __kSaturated )
    #define convert_float4_sat(_X)   __builtin_convert(_X, float4, __kDefaultRoundingMode, __kSaturated )
    #define convert_double4_sat(_X)  __builtin_convert(_X, double4, __kDefaultRoundingMode, __kSaturated )

    #define convert_char4_rte(_X)    __builtin_convert(_X, char4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uchar4_rte(_X)   __builtin_convert(_X, uchar4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_short4_rte(_X)   __builtin_convert(_X, short4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ushort4_rte(_X)  __builtin_convert(_X, ushort4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_int4_rte(_X)     __builtin_convert(_X, int4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uint4_rte(_X)    __builtin_convert(_X, uint4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_long4_rte(_X)    __builtin_convert(_X, long4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ulong4_rte(_X)   __builtin_convert(_X, ulong4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_float4_rte(_X)   __builtin_convert(_X, float4, __kRoundToNearestEven, __kUnsaturated )
    #define convert_double4_rte(_X)  __builtin_convert(_X, double4, __kRoundToNearestEven, __kUnsaturated )

    #define convert_char4_sat_rte(_X)    __builtin_convert(_X, char4, __kRoundToNearestEven, __kSaturated )
    #define convert_uchar4_sat_rte(_X)   __builtin_convert(_X, uchar4, __kRoundToNearestEven, __kSaturated )
    #define convert_short4_sat_rte(_X)   __builtin_convert(_X, short4, __kRoundToNearestEven, __kSaturated )
    #define convert_ushort4_sat_rte(_X)  __builtin_convert(_X, ushort4, __kRoundToNearestEven, __kSaturated )
    #define convert_int4_sat_rte(_X)     __builtin_convert(_X, int4, __kRoundToNearestEven, __kSaturated )
    #define convert_uint4_sat_rte(_X)    __builtin_convert(_X, uint4, __kRoundToNearestEven, __kSaturated )
    #define convert_long4_sat_rte(_X)    __builtin_convert(_X, long4, __kRoundToNearestEven, __kSaturated )
    #define convert_ulong4_sat_rte(_X)   __builtin_convert(_X, ulong4, __kRoundToNearestEven, __kSaturated )
    #define convert_float4_sat_rte(_X)   __builtin_convert(_X, float4, __kRoundToNearestEven, __kSaturated )
    #define convert_double4_sat_rte(_X)  __builtin_convert(_X, double4, __kRoundToNearestEven, __kSaturated )

    #define convert_char4_rtn(_X)    __builtin_convert(_X, char4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uchar4_rtn(_X)   __builtin_convert(_X, uchar4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_short4_rtn(_X)   __builtin_convert(_X, short4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ushort4_rtn(_X)  __builtin_convert(_X, ushort4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_int4_rtn(_X)     __builtin_convert(_X, int4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uint4_rtn(_X)    __builtin_convert(_X, uint4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_long4_rtn(_X)    __builtin_convert(_X, long4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ulong4_rtn(_X)   __builtin_convert(_X, ulong4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_float4_rtn(_X)   __builtin_convert(_X, float4, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_double4_rtn(_X)  __builtin_convert(_X, double4, __kRoundTowardNegativeInf, __kUnsaturated )

    #define convert_char4_sat_rtn(_X)    __builtin_convert(_X, char4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uchar4_sat_rtn(_X)   __builtin_convert(_X, uchar4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_short4_sat_rtn(_X)   __builtin_convert(_X, short4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ushort4_sat_rtn(_X)  __builtin_convert(_X, ushort4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_int4_sat_rtn(_X)     __builtin_convert(_X, int4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uint4_sat_rtn(_X)    __builtin_convert(_X, uint4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_long4_sat_rtn(_X)    __builtin_convert(_X, long4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ulong4_sat_rtn(_X)   __builtin_convert(_X, ulong4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_float4_sat_rtn(_X)   __builtin_convert(_X, float4, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_double4_sat_rtn(_X)  __builtin_convert(_X, double4, __kRoundTowardNegativeInf, __kSaturated )

    #define convert_char4_rtp(_X)    __builtin_convert(_X, char4, __kRoundTowardInf, __kUnsaturated )
    #define convert_uchar4_rtp(_X)   __builtin_convert(_X, uchar4, __kRoundTowardInf, __kUnsaturated )
    #define convert_short4_rtp(_X)   __builtin_convert(_X, short4, __kRoundTowardInf, __kUnsaturated )
    #define convert_ushort4_rtp(_X)  __builtin_convert(_X, ushort4, __kRoundTowardInf, __kUnsaturated )
    #define convert_int4_rtp(_X)     __builtin_convert(_X, int4, __kRoundTowardInf, __kUnsaturated )
    #define convert_uint4_rtp(_X)    __builtin_convert(_X, uint4, __kRoundTowardInf, __kUnsaturated )
    #define convert_long4_rtp(_X)    __builtin_convert(_X, long4, __kRoundTowardInf, __kUnsaturated )
    #define convert_ulong4_rtp(_X)   __builtin_convert(_X, ulong4, __kRoundTowardInf, __kUnsaturated )
    #define convert_float4_rtp(_X)   __builtin_convert(_X, float4, __kRoundTowardInf, __kUnsaturated )
    #define convert_double4_rtp(_X)  __builtin_convert(_X, double4, __kRoundTowardInf, __kUnsaturated )

    #define convert_char4_sat_rtp(_X)    __builtin_convert(_X, char4, __kRoundTowardInf, __kSaturated )
    #define convert_uchar4_sat_rtp(_X)   __builtin_convert(_X, uchar4, __kRoundTowardInf, __kSaturated )
    #define convert_short4_sat_rtp(_X)   __builtin_convert(_X, short4, __kRoundTowardInf, __kSaturated )
    #define convert_ushort4_sat_rtp(_X)  __builtin_convert(_X, ushort4, __kRoundTowardInf, __kSaturated )
    #define convert_int4_sat_rtp(_X)     __builtin_convert(_X, int4, __kRoundTowardInf, __kSaturated )
    #define convert_uint4_sat_rtp(_X)    __builtin_convert(_X, uint4, __kRoundTowardInf, __kSaturated )
    #define convert_long4_sat_rtp(_X)    __builtin_convert(_X, long4, __kRoundTowardInf, __kSaturated )
    #define convert_ulong4_sat_rtp(_X)   __builtin_convert(_X, ulong4, __kRoundTowardInf, __kSaturated )
    #define convert_float4_sat_rtp(_X)   __builtin_convert(_X, float4, __kRoundTowardInf, __kSaturated )
    #define convert_double4_sat_rtp(_X)  __builtin_convert(_X, double4, __kRoundTowardInf, __kSaturated )

    #define convert_char4_rtz(_X)    __builtin_convert(_X, char4, __kRoundTowardZero, __kUnsaturated )
    #define convert_uchar4_rtz(_X)   __builtin_convert(_X, uchar4, __kRoundTowardZero, __kUnsaturated )
    #define convert_short4_rtz(_X)   __builtin_convert(_X, short4, __kRoundTowardZero, __kUnsaturated )
    #define convert_ushort4_rtz(_X)  __builtin_convert(_X, ushort4, __kRoundTowardZero, __kUnsaturated )
    #define convert_int4_rtz(_X)     __builtin_convert(_X, int4, __kRoundTowardZero, __kUnsaturated )
    #define convert_uint4_rtz(_X)    __builtin_convert(_X, uint4, __kRoundTowardZero, __kUnsaturated )
    #define convert_long4_rtz(_X)    __builtin_convert(_X, long4, __kRoundTowardZero, __kUnsaturated )
    #define convert_ulong4_rtz(_X)   __builtin_convert(_X, ulong4, __kRoundTowardZero, __kUnsaturated )
    #define convert_float4_rtz(_X)   __builtin_convert(_X, float4, __kRoundTowardZero, __kUnsaturated )
    #define convert_double4_rtz(_X)  __builtin_convert(_X, double4, __kRoundTowardZero, __kUnsaturated )

    #define convert_char4_sat_rtz(_X)    __builtin_convert(_X, char4, __kRoundTowardZero, __kSaturated )
    #define convert_uchar4_sat_rtz(_X)   __builtin_convert(_X, uchar4, __kRoundTowardZero, __kSaturated )
    #define convert_short4_sat_rtz(_X)   __builtin_convert(_X, short4, __kRoundTowardZero, __kSaturated )
    #define convert_ushort4_sat_rtz(_X)  __builtin_convert(_X, ushort4, __kRoundTowardZero, __kSaturated )
    #define convert_int4_sat_rtz(_X)     __builtin_convert(_X, int4, __kRoundTowardZero, __kSaturated )
    #define convert_uint4_sat_rtz(_X)    __builtin_convert(_X, uint4, __kRoundTowardZero, __kSaturated )
    #define convert_long4_sat_rtz(_X)    __builtin_convert(_X, long4, __kRoundTowardZero, __kSaturated )
    #define convert_ulong4_sat_rtz(_X)   __builtin_convert(_X, ulong4, __kRoundTowardZero, __kSaturated )
    #define convert_float4_sat_rtz(_X)   __builtin_convert(_X, float4, __kRoundTowardZero, __kSaturated )
    #define convert_double4_sat_rtz(_X)  __builtin_convert(_X, double4, __kRoundTowardZero, __kSaturated )

    //type8
    #define convert_char8(_X)    __builtin_convert(_X, char8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uchar8(_X)   __builtin_convert(_X, uchar8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_short8(_X)   __builtin_convert(_X, short8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ushort8(_X)  __builtin_convert(_X, ushort8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_int8(_X)     __builtin_convert(_X, int8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uint8(_X)    __builtin_convert(_X, uint8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_long8(_X)    __builtin_convert(_X, long8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ulong8(_X)   __builtin_convert(_X, ulong8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_float8(_X)   __builtin_convert(_X, float8, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_double8(_X)  __builtin_convert(_X, double8, __kDefaultRoundingMode, __kUnsaturated )

    #define convert_char8_sat(_X)    __builtin_convert(_X, char8, __kDefaultRoundingMode, __kSaturated )
    #define convert_uchar8_sat(_X)   __builtin_convert(_X, uchar8, __kDefaultRoundingMode, __kSaturated )
    #define convert_short8_sat(_X)   __builtin_convert(_X, short8, __kDefaultRoundingMode, __kSaturated )
    #define convert_ushort8_sat(_X)  __builtin_convert(_X, ushort8, __kDefaultRoundingMode, __kSaturated )
    #define convert_int8_sat(_X)     __builtin_convert(_X, int8, __kDefaultRoundingMode, __kSaturated )
    #define convert_uint8_sat(_X)    __builtin_convert(_X, uint8, __kDefaultRoundingMode, __kSaturated )
    #define convert_long8_sat(_X)    __builtin_convert(_X, long8, __kDefaultRoundingMode, __kSaturated )
    #define convert_ulong8_sat(_X)   __builtin_convert(_X, ulong8, __kDefaultRoundingMode, __kSaturated )
    #define convert_float8_sat(_X)   __builtin_convert(_X, float8, __kDefaultRoundingMode, __kSaturated )
    #define convert_double8_sat(_X)  __builtin_convert(_X, double8, __kDefaultRoundingMode, __kSaturated )

    #define convert_char8_rte(_X)    __builtin_convert(_X, char8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uchar8_rte(_X)   __builtin_convert(_X, uchar8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_short8_rte(_X)   __builtin_convert(_X, short8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ushort8_rte(_X)  __builtin_convert(_X, ushort8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_int8_rte(_X)     __builtin_convert(_X, int8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uint8_rte(_X)    __builtin_convert(_X, uint8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_long8_rte(_X)    __builtin_convert(_X, long8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ulong8_rte(_X)   __builtin_convert(_X, ulong8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_float8_rte(_X)   __builtin_convert(_X, float8, __kRoundToNearestEven, __kUnsaturated )
    #define convert_double8_rte(_X)  __builtin_convert(_X, double8, __kRoundToNearestEven, __kUnsaturated )

    #define convert_char8_sat_rte(_X)    __builtin_convert(_X, char8, __kRoundToNearestEven, __kSaturated )
    #define convert_uchar8_sat_rte(_X)   __builtin_convert(_X, uchar8, __kRoundToNearestEven, __kSaturated )
    #define convert_short8_sat_rte(_X)   __builtin_convert(_X, short8, __kRoundToNearestEven, __kSaturated )
    #define convert_ushort8_sat_rte(_X)  __builtin_convert(_X, ushort8, __kRoundToNearestEven, __kSaturated )
    #define convert_int8_sat_rte(_X)     __builtin_convert(_X, int8, __kRoundToNearestEven, __kSaturated )
    #define convert_uint8_sat_rte(_X)    __builtin_convert(_X, uint8, __kRoundToNearestEven, __kSaturated )
    #define convert_long8_sat_rte(_X)    __builtin_convert(_X, long8, __kRoundToNearestEven, __kSaturated )
    #define convert_ulong8_sat_rte(_X)   __builtin_convert(_X, ulong8, __kRoundToNearestEven, __kSaturated )
    #define convert_float8_sat_rte(_X)   __builtin_convert(_X, float8, __kRoundToNearestEven, __kSaturated )
    #define convert_double8_sat_rte(_X)  __builtin_convert(_X, double8, __kRoundToNearestEven, __kSaturated )

    #define convert_char8_rtn(_X)    __builtin_convert(_X, char8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uchar8_rtn(_X)   __builtin_convert(_X, uchar8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_short8_rtn(_X)   __builtin_convert(_X, short8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ushort8_rtn(_X)  __builtin_convert(_X, ushort8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_int8_rtn(_X)     __builtin_convert(_X, int8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uint8_rtn(_X)    __builtin_convert(_X, uint8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_long8_rtn(_X)    __builtin_convert(_X, long8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ulong8_rtn(_X)   __builtin_convert(_X, ulong8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_float8_rtn(_X)   __builtin_convert(_X, float8, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_double8_rtn(_X)  __builtin_convert(_X, double8, __kRoundTowardNegativeInf, __kUnsaturated )

    #define convert_char8_sat_rtn(_X)    __builtin_convert(_X, char8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uchar8_sat_rtn(_X)   __builtin_convert(_X, uchar8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_short8_sat_rtn(_X)   __builtin_convert(_X, short8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ushort8_sat_rtn(_X)  __builtin_convert(_X, ushort8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_int8_sat_rtn(_X)     __builtin_convert(_X, int8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uint8_sat_rtn(_X)    __builtin_convert(_X, uint8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_long8_sat_rtn(_X)    __builtin_convert(_X, long8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ulong8_sat_rtn(_X)   __builtin_convert(_X, ulong8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_float8_sat_rtn(_X)   __builtin_convert(_X, float8, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_double8_sat_rtn(_X)  __builtin_convert(_X, double8, __kRoundTowardNegativeInf, __kSaturated )

    #define convert_char8_rtp(_X)    __builtin_convert(_X, char8, __kRoundTowardInf, __kUnsaturated )
    #define convert_uchar8_rtp(_X)   __builtin_convert(_X, uchar8, __kRoundTowardInf, __kUnsaturated )
    #define convert_short8_rtp(_X)   __builtin_convert(_X, short8, __kRoundTowardInf, __kUnsaturated )
    #define convert_ushort8_rtp(_X)  __builtin_convert(_X, ushort8, __kRoundTowardInf, __kUnsaturated )
    #define convert_int8_rtp(_X)     __builtin_convert(_X, int8, __kRoundTowardInf, __kUnsaturated )
    #define convert_uint8_rtp(_X)    __builtin_convert(_X, uint8, __kRoundTowardInf, __kUnsaturated )
    #define convert_long8_rtp(_X)    __builtin_convert(_X, long8, __kRoundTowardInf, __kUnsaturated )
    #define convert_ulong8_rtp(_X)   __builtin_convert(_X, ulong8, __kRoundTowardInf, __kUnsaturated )
    #define convert_float8_rtp(_X)   __builtin_convert(_X, float8, __kRoundTowardInf, __kUnsaturated )
    #define convert_double8_rtp(_X)  __builtin_convert(_X, double8, __kRoundTowardInf, __kUnsaturated )

    #define convert_char8_sat_rtp(_X)    __builtin_convert(_X, char8, __kRoundTowardInf, __kSaturated )
    #define convert_uchar8_sat_rtp(_X)   __builtin_convert(_X, uchar8, __kRoundTowardInf, __kSaturated )
    #define convert_short8_sat_rtp(_X)   __builtin_convert(_X, short8, __kRoundTowardInf, __kSaturated )
    #define convert_ushort8_sat_rtp(_X)  __builtin_convert(_X, ushort8, __kRoundTowardInf, __kSaturated )
    #define convert_int8_sat_rtp(_X)     __builtin_convert(_X, int8, __kRoundTowardInf, __kSaturated )
    #define convert_uint8_sat_rtp(_X)    __builtin_convert(_X, uint8, __kRoundTowardInf, __kSaturated )
    #define convert_long8_sat_rtp(_X)    __builtin_convert(_X, long8, __kRoundTowardInf, __kSaturated )
    #define convert_ulong8_sat_rtp(_X)   __builtin_convert(_X, ulong8, __kRoundTowardInf, __kSaturated )
    #define convert_float8_sat_rtp(_X)   __builtin_convert(_X, float8, __kRoundTowardInf, __kSaturated )
    #define convert_double8_sat_rtp(_X)  __builtin_convert(_X, double8, __kRoundTowardInf, __kSaturated )

    #define convert_char8_rtz(_X)    __builtin_convert(_X, char8, __kRoundTowardZero, __kUnsaturated )
    #define convert_uchar8_rtz(_X)   __builtin_convert(_X, uchar8, __kRoundTowardZero, __kUnsaturated )
    #define convert_short8_rtz(_X)   __builtin_convert(_X, short8, __kRoundTowardZero, __kUnsaturated )
    #define convert_ushort8_rtz(_X)  __builtin_convert(_X, ushort8, __kRoundTowardZero, __kUnsaturated )
    #define convert_int8_rtz(_X)     __builtin_convert(_X, int8, __kRoundTowardZero, __kUnsaturated )
    #define convert_uint8_rtz(_X)    __builtin_convert(_X, uint8, __kRoundTowardZero, __kUnsaturated )
    #define convert_long8_rtz(_X)    __builtin_convert(_X, long8, __kRoundTowardZero, __kUnsaturated )
    #define convert_ulong8_rtz(_X)   __builtin_convert(_X, ulong8, __kRoundTowardZero, __kUnsaturated )
    #define convert_float8_rtz(_X)   __builtin_convert(_X, float8, __kRoundTowardZero, __kUnsaturated )
    #define convert_double8_rtz(_X)  __builtin_convert(_X, double8, __kRoundTowardZero, __kUnsaturated )

    #define convert_char8_sat_rtz(_X)    __builtin_convert(_X, char8, __kRoundTowardZero, __kSaturated )
    #define convert_uchar8_sat_rtz(_X)   __builtin_convert(_X, uchar8, __kRoundTowardZero, __kSaturated )
    #define convert_short8_sat_rtz(_X)   __builtin_convert(_X, short8, __kRoundTowardZero, __kSaturated )
    #define convert_ushort8_sat_rtz(_X)  __builtin_convert(_X, ushort8, __kRoundTowardZero, __kSaturated )
    #define convert_int8_sat_rtz(_X)     __builtin_convert(_X, int8, __kRoundTowardZero, __kSaturated )
    #define convert_uint8_sat_rtz(_X)    __builtin_convert(_X, uint8, __kRoundTowardZero, __kSaturated )
    #define convert_long8_sat_rtz(_X)    __builtin_convert(_X, long8, __kRoundTowardZero, __kSaturated )
    #define convert_ulong8_sat_rtz(_X)   __builtin_convert(_X, ulong8, __kRoundTowardZero, __kSaturated )
    #define convert_float8_sat_rtz(_X)   __builtin_convert(_X, float8, __kRoundTowardZero, __kSaturated )
    #define convert_double8_sat_rtz(_X)  __builtin_convert(_X, double8, __kRoundTowardZero, __kSaturated )

    //type16
    #define convert_char16(_X)    __builtin_convert(_X, char16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uchar16(_X)   __builtin_convert(_X, uchar16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_short16(_X)   __builtin_convert(_X, short16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ushort16(_X)  __builtin_convert(_X, ushort16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_int16(_X)     __builtin_convert(_X, int16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_uint16(_X)    __builtin_convert(_X, uint16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_long16(_X)    __builtin_convert(_X, long16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_ulong16(_X)   __builtin_convert(_X, ulong16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_float16(_X)   __builtin_convert(_X, float16, __kDefaultRoundingMode, __kUnsaturated )
    #define convert_double16(_X)  __builtin_convert(_X, double16, __kDefaultRoundingMode, __kUnsaturated )

    #define convert_char16_sat(_X)    __builtin_convert(_X, char16, __kDefaultRoundingMode, __kSaturated )
    #define convert_uchar16_sat(_X)   __builtin_convert(_X, uchar16, __kDefaultRoundingMode, __kSaturated )
    #define convert_short16_sat(_X)   __builtin_convert(_X, short16, __kDefaultRoundingMode, __kSaturated )
    #define convert_ushort16_sat(_X)  __builtin_convert(_X, ushort16, __kDefaultRoundingMode, __kSaturated )
    #define convert_int16_sat(_X)     __builtin_convert(_X, int16, __kDefaultRoundingMode, __kSaturated )
    #define convert_uint16_sat(_X)    __builtin_convert(_X, uint16, __kDefaultRoundingMode, __kSaturated )
    #define convert_long16_sat(_X)    __builtin_convert(_X, long16, __kDefaultRoundingMode, __kSaturated )
    #define convert_ulong16_sat(_X)   __builtin_convert(_X, ulong16, __kDefaultRoundingMode, __kSaturated )
    #define convert_float16_sat(_X)   __builtin_convert(_X, float16, __kDefaultRoundingMode, __kSaturated )
    #define convert_double16_sat(_X)  __builtin_convert(_X, double16, __kDefaultRoundingMode, __kSaturated )

    #define convert_char16_rte(_X)    __builtin_convert(_X, char16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uchar16_rte(_X)   __builtin_convert(_X, uchar16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_short16_rte(_X)   __builtin_convert(_X, short16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ushort16_rte(_X)  __builtin_convert(_X, ushort16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_int16_rte(_X)     __builtin_convert(_X, int16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_uint16_rte(_X)    __builtin_convert(_X, uint16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_long16_rte(_X)    __builtin_convert(_X, long16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_ulong16_rte(_X)   __builtin_convert(_X, ulong16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_float16_rte(_X)   __builtin_convert(_X, float16, __kRoundToNearestEven, __kUnsaturated )
    #define convert_double16_rte(_X)  __builtin_convert(_X, double16, __kRoundToNearestEven, __kUnsaturated )

    #define convert_char16_sat_rte(_X)    __builtin_convert(_X, char16, __kRoundToNearestEven, __kSaturated )
    #define convert_uchar16_sat_rte(_X)   __builtin_convert(_X, uchar16, __kRoundToNearestEven, __kSaturated )
    #define convert_short16_sat_rte(_X)   __builtin_convert(_X, short16, __kRoundToNearestEven, __kSaturated )
    #define convert_ushort16_sat_rte(_X)  __builtin_convert(_X, ushort16, __kRoundToNearestEven, __kSaturated )
    #define convert_int16_sat_rte(_X)     __builtin_convert(_X, int16, __kRoundToNearestEven, __kSaturated )
    #define convert_uint16_sat_rte(_X)    __builtin_convert(_X, uint16, __kRoundToNearestEven, __kSaturated )
    #define convert_long16_sat_rte(_X)    __builtin_convert(_X, long16, __kRoundToNearestEven, __kSaturated )
    #define convert_ulong16_sat_rte(_X)   __builtin_convert(_X, ulong16, __kRoundToNearestEven, __kSaturated )
    #define convert_float16_sat_rte(_X)   __builtin_convert(_X, float16, __kRoundToNearestEven, __kSaturated )
    #define convert_double16_sat_rte(_X)  __builtin_convert(_X, double16, __kRoundToNearestEven, __kSaturated )

    #define convert_char16_rtn(_X)    __builtin_convert(_X, char16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uchar16_rtn(_X)   __builtin_convert(_X, uchar16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_short16_rtn(_X)   __builtin_convert(_X, short16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ushort16_rtn(_X)  __builtin_convert(_X, ushort16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_int16_rtn(_X)     __builtin_convert(_X, int16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_uint16_rtn(_X)    __builtin_convert(_X, uint16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_long16_rtn(_X)    __builtin_convert(_X, long16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_ulong16_rtn(_X)   __builtin_convert(_X, ulong16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_float16_rtn(_X)   __builtin_convert(_X, float16, __kRoundTowardNegativeInf, __kUnsaturated )
    #define convert_double16_rtn(_X)  __builtin_convert(_X, double16, __kRoundTowardNegativeInf, __kUnsaturated )

    #define convert_char16_sat_rtn(_X)    __builtin_convert(_X, char16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uchar16_sat_rtn(_X)   __builtin_convert(_X, uchar16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_short16_sat_rtn(_X)   __builtin_convert(_X, short16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ushort16_sat_rtn(_X)  __builtin_convert(_X, ushort16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_int16_sat_rtn(_X)     __builtin_convert(_X, int16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_uint16_sat_rtn(_X)    __builtin_convert(_X, uint16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_long16_sat_rtn(_X)    __builtin_convert(_X, long16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_ulong16_sat_rtn(_X)   __builtin_convert(_X, ulong16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_float16_sat_rtn(_X)   __builtin_convert(_X, float16, __kRoundTowardNegativeInf, __kSaturated )
    #define convert_double16_sat_rtn(_X)  __builtin_convert(_X, double16, __kRoundTowardNegativeInf, __kSaturated )

    #define convert_char16_rtp(_X)    __builtin_convert(_X, char16, __kRoundTowardInf, __kUnsaturated )
    #define convert_uchar16_rtp(_X)   __builtin_convert(_X, uchar16, __kRoundTowardInf, __kUnsaturated )
    #define convert_short16_rtp(_X)   __builtin_convert(_X, short16, __kRoundTowardInf, __kUnsaturated )
    #define convert_ushort16_rtp(_X)  __builtin_convert(_X, ushort16, __kRoundTowardInf, __kUnsaturated )
    #define convert_int16_rtp(_X)     __builtin_convert(_X, int16, __kRoundTowardInf, __kUnsaturated )
    #define convert_uint16_rtp(_X)    __builtin_convert(_X, uint16, __kRoundTowardInf, __kUnsaturated )
    #define convert_long16_rtp(_X)    __builtin_convert(_X, long16, __kRoundTowardInf, __kUnsaturated )
    #define convert_ulong16_rtp(_X)   __builtin_convert(_X, ulong16, __kRoundTowardInf, __kUnsaturated )
    #define convert_float16_rtp(_X)   __builtin_convert(_X, float16, __kRoundTowardInf, __kUnsaturated )
    #define convert_double16_rtp(_X)  __builtin_convert(_X, double16, __kRoundTowardInf, __kUnsaturated )

    #define convert_char16_sat_rtp(_X)    __builtin_convert(_X, char16, __kRoundTowardInf, __kSaturated )
    #define convert_uchar16_sat_rtp(_X)   __builtin_convert(_X, uchar16, __kRoundTowardInf, __kSaturated )
    #define convert_short16_sat_rtp(_X)   __builtin_convert(_X, short16, __kRoundTowardInf, __kSaturated )
    #define convert_ushort16_sat_rtp(_X)  __builtin_convert(_X, ushort16, __kRoundTowardInf, __kSaturated )
    #define convert_int16_sat_rtp(_X)     __builtin_convert(_X, int16, __kRoundTowardInf, __kSaturated )
    #define convert_uint16_sat_rtp(_X)    __builtin_convert(_X, uint16, __kRoundTowardInf, __kSaturated )
    #define convert_long16_sat_rtp(_X)    __builtin_convert(_X, long16, __kRoundTowardInf, __kSaturated )
    #define convert_ulong16_sat_rtp(_X)   __builtin_convert(_X, ulong16, __kRoundTowardInf, __kSaturated )
    #define convert_float16_sat_rtp(_X)   __builtin_convert(_X, float16, __kRoundTowardInf, __kSaturated )
    #define convert_double16_sat_rtp(_X)  __builtin_convert(_X, double16, __kRoundTowardInf, __kSaturated )

    #define convert_char16_rtz(_X)    __builtin_convert(_X, char16, __kRoundTowardZero, __kUnsaturated )
    #define convert_uchar16_rtz(_X)   __builtin_convert(_X, uchar16, __kRoundTowardZero, __kUnsaturated )
    #define convert_short16_rtz(_X)   __builtin_convert(_X, short16, __kRoundTowardZero, __kUnsaturated )
    #define convert_ushort16_rtz(_X)  __builtin_convert(_X, ushort16, __kRoundTowardZero, __kUnsaturated )
    #define convert_int16_rtz(_X)     __builtin_convert(_X, int16, __kRoundTowardZero, __kUnsaturated )
    #define convert_uint16_rtz(_X)    __builtin_convert(_X, uint16, __kRoundTowardZero, __kUnsaturated )
    #define convert_long16_rtz(_X)    __builtin_convert(_X, long16, __kRoundTowardZero, __kUnsaturated )
    #define convert_ulong16_rtz(_X)   __builtin_convert(_X, ulong16, __kRoundTowardZero, __kUnsaturated )
    #define convert_float16_rtz(_X)   __builtin_convert(_X, float16, __kRoundTowardZero, __kUnsaturated )
    #define convert_double16_rtz(_X)  __builtin_convert(_X, double16, __kRoundTowardZero, __kUnsaturated )

    #define convert_char16_sat_rtz(_X)    __builtin_convert(_X, char16, __kRoundTowardZero, __kSaturated )
    #define convert_uchar16_sat_rtz(_X)   __builtin_convert(_X, uchar16, __kRoundTowardZero, __kSaturated )
    #define convert_short16_sat_rtz(_X)   __builtin_convert(_X, short16, __kRoundTowardZero, __kSaturated )
    #define convert_ushort16_sat_rtz(_X)  __builtin_convert(_X, ushort16, __kRoundTowardZero, __kSaturated )
    #define convert_int16_sat_rtz(_X)     __builtin_convert(_X, int16, __kRoundTowardZero, __kSaturated )
    #define convert_uint16_sat_rtz(_X)    __builtin_convert(_X, uint16, __kRoundTowardZero, __kSaturated )
    #define convert_long16_sat_rtz(_X)    __builtin_convert(_X, long16, __kRoundTowardZero, __kSaturated )
    #define convert_ulong16_sat_rtz(_X)   __builtin_convert(_X, ulong16, __kRoundTowardZero, __kSaturated )
    #define convert_float16_sat_rtz(_X)   __builtin_convert(_X, float16, __kRoundTowardZero, __kSaturated )
    #define convert_double16_sat_rtz(_X)  __builtin_convert(_X, double16, __kRoundTowardZero, __kSaturated )


#else

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_CONVERT(name, rtype) rtype __OVERLOAD__ name( uchar a); \
rtype __OVERLOAD__ name( ushort a); \
rtype __OVERLOAD__ name( uint a); \
rtype __OVERLOAD__ name( ulong a); \
rtype __OVERLOAD__ name( char a); \
rtype __OVERLOAD__ name( short a); \
rtype __OVERLOAD__ name( int a); \
rtype __OVERLOAD__ name( long a); \
rtype __OVERLOAD__ name( float a); \
rtype __OVERLOAD__ name( double a); \
rtype##2 __OVERLOAD__ name##2( uchar2 a); \
rtype##2 __OVERLOAD__ name##2( ushort2 a); \
rtype##2 __OVERLOAD__ name##2( uint2 a); \
rtype##2 __OVERLOAD__ name##2( ulong2 a); \
rtype##2 __OVERLOAD__ name##2( char2 a); \
rtype##2 __OVERLOAD__ name##2( short2 a); \
rtype##2 __OVERLOAD__ name##2( int2 a); \
rtype##2 __OVERLOAD__ name##2( long2 a); \
rtype##2 __OVERLOAD__ name##2( float2 a); \
rtype##2 __OVERLOAD__ name##2( double2 a); \
rtype##3 __OVERLOAD__ name##3( uchar3 a); \
rtype##3 __OVERLOAD__ name##3( ushort3 a); \
rtype##3 __OVERLOAD__ name##3( uint3 a); \
rtype##3 __OVERLOAD__ name##3( ulong3 a); \
rtype##3 __OVERLOAD__ name##3( char3 a); \
rtype##3 __OVERLOAD__ name##3( short3 a); \
rtype##3 __OVERLOAD__ name##3( int3 a); \
rtype##3 __OVERLOAD__ name##3( long3 a); \
rtype##3 __OVERLOAD__ name##3( float3 a); \
rtype##3 __OVERLOAD__ name##3( double3 a); \
rtype##4 __OVERLOAD__ name##4( uchar4 a); \
rtype##4 __OVERLOAD__ name##4( ushort4 a); \
rtype##4 __OVERLOAD__ name##4( uint4 a); \
rtype##4 __OVERLOAD__ name##4( ulong4 a); \
rtype##4 __OVERLOAD__ name##4( char4 a); \
rtype##4 __OVERLOAD__ name##4( short4 a); \
rtype##4 __OVERLOAD__ name##4( int4 a); \
rtype##4 __OVERLOAD__ name##4( long4 a); \
rtype##4 __OVERLOAD__ name##4( float4 a); \
rtype##4 __OVERLOAD__ name##4( double4 a); \
rtype##8 __OVERLOAD__ name##8( uchar8 a); \
rtype##8 __OVERLOAD__ name##8( ushort8 a); \
rtype##8 __OVERLOAD__ name##8( uint8 a); \
rtype##8 __OVERLOAD__ name##8( ulong8 a); \
rtype##8 __OVERLOAD__ name##8( char8 a); \
rtype##8 __OVERLOAD__ name##8( short8 a); \
rtype##8 __OVERLOAD__ name##8( int8 a); \
rtype##8 __OVERLOAD__ name##8( long8 a); \
rtype##8 __OVERLOAD__ name##8( float8 a); \
rtype##8 __OVERLOAD__ name##8( double8 a); \
rtype##16 __OVERLOAD__ name##16( uchar16 a); \
rtype##16 __OVERLOAD__ name##16( ushort16 a); \
rtype##16 __OVERLOAD__ name##16( uint16 a); \
rtype##16 __OVERLOAD__ name##16( ulong16 a); \
rtype##16 __OVERLOAD__ name##16( char16 a); \
rtype##16 __OVERLOAD__ name##16( short16 a); \
rtype##16 __OVERLOAD__ name##16( int16 a); \
rtype##16 __OVERLOAD__ name##16( long16 a); \
rtype##16 __OVERLOAD__ name##16( float16 a); \
rtype##16 __OVERLOAD__ name##16( double16 a);
#else
#define __CLFN_CONVERT(name, rtype) rtype __OVERLOAD__ name( uchar a); \
rtype __OVERLOAD__ name( ushort a); \
rtype __OVERLOAD__ name( uint a); \
rtype __OVERLOAD__ name( ulong a); \
rtype __OVERLOAD__ name( char a); \
rtype __OVERLOAD__ name( short a); \
rtype __OVERLOAD__ name( int a); \
rtype __OVERLOAD__ name( long a); \
rtype __OVERLOAD__ name( float a); \
rtype##2 __OVERLOAD__ name##2( uchar2 a); \
rtype##2 __OVERLOAD__ name##2( ushort2 a); \
rtype##2 __OVERLOAD__ name##2( uint2 a); \
rtype##2 __OVERLOAD__ name##2( ulong2 a); \
rtype##2 __OVERLOAD__ name##2( char2 a); \
rtype##2 __OVERLOAD__ name##2( short2 a); \
rtype##2 __OVERLOAD__ name##2( int2 a); \
rtype##2 __OVERLOAD__ name##2( long2 a); \
rtype##2 __OVERLOAD__ name##2( float2 a); \
rtype##3 __OVERLOAD__ name##3( uchar3 a); \
rtype##3 __OVERLOAD__ name##3( ushort3 a); \
rtype##3 __OVERLOAD__ name##3( uint3 a); \
rtype##3 __OVERLOAD__ name##3( ulong3 a); \
rtype##3 __OVERLOAD__ name##3( char3 a); \
rtype##3 __OVERLOAD__ name##3( short3 a); \
rtype##3 __OVERLOAD__ name##3( int3 a); \
rtype##3 __OVERLOAD__ name##3( long3 a); \
rtype##3 __OVERLOAD__ name##3( float3 a); \
rtype##4 __OVERLOAD__ name##4( uchar4 a); \
rtype##4 __OVERLOAD__ name##4( ushort4 a); \
rtype##4 __OVERLOAD__ name##4( uint4 a); \
rtype##4 __OVERLOAD__ name##4( ulong4 a); \
rtype##4 __OVERLOAD__ name##4( char4 a); \
rtype##4 __OVERLOAD__ name##4( short4 a); \
rtype##4 __OVERLOAD__ name##4( int4 a); \
rtype##4 __OVERLOAD__ name##4( long4 a); \
rtype##4 __OVERLOAD__ name##4( float4 a); \
rtype##8 __OVERLOAD__ name##8( uchar8 a); \
rtype##8 __OVERLOAD__ name##8( ushort8 a); \
rtype##8 __OVERLOAD__ name##8( uint8 a); \
rtype##8 __OVERLOAD__ name##8( ulong8 a); \
rtype##8 __OVERLOAD__ name##8( char8 a); \
rtype##8 __OVERLOAD__ name##8( short8 a); \
rtype##8 __OVERLOAD__ name##8( int8 a); \
rtype##8 __OVERLOAD__ name##8( long8 a); \
rtype##8 __OVERLOAD__ name##8( float8 a); \
rtype##16 __OVERLOAD__ name##16( uchar16 a); \
rtype##16 __OVERLOAD__ name##16( ushort16 a); \
rtype##16 __OVERLOAD__ name##16( uint16 a); \
rtype##16 __OVERLOAD__ name##16( ulong16 a); \
rtype##16 __OVERLOAD__ name##16( char16 a); \
rtype##16 __OVERLOAD__ name##16( short16 a); \
rtype##16 __OVERLOAD__ name##16( int16 a); \
rtype##16 __OVERLOAD__ name##16( long16 a); \
rtype##16 __OVERLOAD__ name##16( float16 a);
#endif

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
#define __CLFN_CONVERT_EXT(name, ext, rtype) rtype __OVERLOAD__ name##ext( uchar a); \
rtype __OVERLOAD__ name##ext( ushort a); \
rtype __OVERLOAD__ name##ext( uint a); \
rtype __OVERLOAD__ name##ext( ulong a); \
rtype __OVERLOAD__ name##ext( char a); \
rtype __OVERLOAD__ name##ext( short a); \
rtype __OVERLOAD__ name##ext( int a); \
rtype __OVERLOAD__ name##ext( long a); \
rtype __OVERLOAD__ name##ext( float a); \
rtype __OVERLOAD__ name##ext( double a); \
rtype##2 __OVERLOAD__ name##2##ext( uchar2 a); \
rtype##2 __OVERLOAD__ name##2##ext( ushort2 a); \
rtype##2 __OVERLOAD__ name##2##ext( uint2 a); \
rtype##2 __OVERLOAD__ name##2##ext( ulong2 a); \
rtype##2 __OVERLOAD__ name##2##ext( char2 a); \
rtype##2 __OVERLOAD__ name##2##ext( short2 a); \
rtype##2 __OVERLOAD__ name##2##ext( int2 a); \
rtype##2 __OVERLOAD__ name##2##ext( long2 a); \
rtype##2 __OVERLOAD__ name##2##ext( float2 a); \
rtype##2 __OVERLOAD__ name##2##ext( double2 a); \
rtype##3 __OVERLOAD__ name##3##ext( uchar3 a); \
rtype##3 __OVERLOAD__ name##3##ext( ushort3 a); \
rtype##3 __OVERLOAD__ name##3##ext( uint3 a); \
rtype##3 __OVERLOAD__ name##3##ext( ulong3 a); \
rtype##3 __OVERLOAD__ name##3##ext( char3 a); \
rtype##3 __OVERLOAD__ name##3##ext( short3 a); \
rtype##3 __OVERLOAD__ name##3##ext( int3 a); \
rtype##3 __OVERLOAD__ name##3##ext( long3 a); \
rtype##3 __OVERLOAD__ name##3##ext( float3 a); \
rtype##3 __OVERLOAD__ name##3##ext( double3 a); \
rtype##4 __OVERLOAD__ name##4##ext( uchar4 a); \
rtype##4 __OVERLOAD__ name##4##ext( ushort4 a); \
rtype##4 __OVERLOAD__ name##4##ext( uint4 a); \
rtype##4 __OVERLOAD__ name##4##ext( ulong4 a); \
rtype##4 __OVERLOAD__ name##4##ext( char4 a); \
rtype##4 __OVERLOAD__ name##4##ext( short4 a); \
rtype##4 __OVERLOAD__ name##4##ext( int4 a); \
rtype##4 __OVERLOAD__ name##4##ext( long4 a); \
rtype##4 __OVERLOAD__ name##4##ext( float4 a); \
rtype##4 __OVERLOAD__ name##4##ext( double4 a); \
rtype##8 __OVERLOAD__ name##8##ext( uchar8 a); \
rtype##8 __OVERLOAD__ name##8##ext( ushort8 a); \
rtype##8 __OVERLOAD__ name##8##ext( uint8 a); \
rtype##8 __OVERLOAD__ name##8##ext( ulong8 a); \
rtype##8 __OVERLOAD__ name##8##ext( char8 a); \
rtype##8 __OVERLOAD__ name##8##ext( short8 a); \
rtype##8 __OVERLOAD__ name##8##ext( int8 a); \
rtype##8 __OVERLOAD__ name##8##ext( long8 a); \
rtype##8 __OVERLOAD__ name##8##ext( float8 a); \
rtype##8 __OVERLOAD__ name##8##ext( double8 a); \
rtype##16 __OVERLOAD__ name##16##ext( uchar16 a); \
rtype##16 __OVERLOAD__ name##16##ext( ushort16 a); \
rtype##16 __OVERLOAD__ name##16##ext( uint16 a); \
rtype##16 __OVERLOAD__ name##16##ext( ulong16 a); \
rtype##16 __OVERLOAD__ name##16##ext( char16 a); \
rtype##16 __OVERLOAD__ name##16##ext( short16 a); \
rtype##16 __OVERLOAD__ name##16##ext( int16 a); \
rtype##16 __OVERLOAD__ name##16##ext( long16 a); \
rtype##16 __OVERLOAD__ name##16##ext( float16 a); \
rtype##16 __OVERLOAD__ name##16##ext( double16 a);
#else
#define __CLFN_CONVERT_EXT(name, ext, rtype) rtype __OVERLOAD__ name##ext( uchar a); \
rtype __OVERLOAD__ name##ext( ushort a); \
rtype __OVERLOAD__ name##ext( uint a); \
rtype __OVERLOAD__ name##ext( ulong a); \
rtype __OVERLOAD__ name##ext( char a); \
rtype __OVERLOAD__ name##ext( short a); \
rtype __OVERLOAD__ name##ext( int a); \
rtype __OVERLOAD__ name##ext( long a); \
rtype __OVERLOAD__ name##ext( float a); \
rtype##2 __OVERLOAD__ name##2##ext( uchar2 a); \
rtype##2 __OVERLOAD__ name##2##ext( ushort2 a); \
rtype##2 __OVERLOAD__ name##2##ext( uint2 a); \
rtype##2 __OVERLOAD__ name##2##ext( ulong2 a); \
rtype##2 __OVERLOAD__ name##2##ext( char2 a); \
rtype##2 __OVERLOAD__ name##2##ext( short2 a); \
rtype##2 __OVERLOAD__ name##2##ext( int2 a); \
rtype##2 __OVERLOAD__ name##2##ext( long2 a); \
rtype##2 __OVERLOAD__ name##2##ext( float2 a); \
rtype##3 __OVERLOAD__ name##3##ext( uchar3 a); \
rtype##3 __OVERLOAD__ name##3##ext( ushort3 a); \
rtype##3 __OVERLOAD__ name##3##ext( uint3 a); \
rtype##3 __OVERLOAD__ name##3##ext( ulong3 a); \
rtype##3 __OVERLOAD__ name##3##ext( char3 a); \
rtype##3 __OVERLOAD__ name##3##ext( short3 a); \
rtype##3 __OVERLOAD__ name##3##ext( int3 a); \
rtype##3 __OVERLOAD__ name##3##ext( long3 a); \
rtype##3 __OVERLOAD__ name##3##ext( float3 a); \
rtype##4 __OVERLOAD__ name##4##ext( uchar4 a); \
rtype##4 __OVERLOAD__ name##4##ext( ushort4 a); \
rtype##4 __OVERLOAD__ name##4##ext( uint4 a); \
rtype##4 __OVERLOAD__ name##4##ext( ulong4 a); \
rtype##4 __OVERLOAD__ name##4##ext( char4 a); \
rtype##4 __OVERLOAD__ name##4##ext( short4 a); \
rtype##4 __OVERLOAD__ name##4##ext( int4 a); \
rtype##4 __OVERLOAD__ name##4##ext( long4 a); \
rtype##4 __OVERLOAD__ name##4##ext( float4 a); \
rtype##8 __OVERLOAD__ name##8##ext( uchar8 a); \
rtype##8 __OVERLOAD__ name##8##ext( ushort8 a); \
rtype##8 __OVERLOAD__ name##8##ext( uint8 a); \
rtype##8 __OVERLOAD__ name##8##ext( ulong8 a); \
rtype##8 __OVERLOAD__ name##8##ext( char8 a); \
rtype##8 __OVERLOAD__ name##8##ext( short8 a); \
rtype##8 __OVERLOAD__ name##8##ext( int8 a); \
rtype##8 __OVERLOAD__ name##8##ext( long8 a); \
rtype##8 __OVERLOAD__ name##8##ext( float8 a); \
rtype##16 __OVERLOAD__ name##16##ext( uchar16 a); \
rtype##16 __OVERLOAD__ name##16##ext( ushort16 a); \
rtype##16 __OVERLOAD__ name##16##ext( uint16 a); \
rtype##16 __OVERLOAD__ name##16##ext( ulong16 a); \
rtype##16 __OVERLOAD__ name##16##ext( char16 a); \
rtype##16 __OVERLOAD__ name##16##ext( short16 a); \
rtype##16 __OVERLOAD__ name##16##ext( int16 a); \
rtype##16 __OVERLOAD__ name##16##ext( long16 a); \
rtype##16 __OVERLOAD__ name##16##ext( float16 a);
#endif


__CLFN_CONVERT_EXT(convert_uchar, _sat_rtz, uchar);
__CLFN_CONVERT_EXT(convert_uchar, _sat_rtp, uchar);
__CLFN_CONVERT_EXT(convert_uchar, _sat_rtn, uchar);
__CLFN_CONVERT_EXT(convert_uchar, _sat_rte, uchar);
__CLFN_CONVERT_EXT(convert_uchar, _sat, uchar);
__CLFN_CONVERT_EXT(convert_uchar, _rtz, uchar);
__CLFN_CONVERT_EXT(convert_uchar, _rtn, uchar);
__CLFN_CONVERT_EXT(convert_uchar, _rtp, uchar);
__CLFN_CONVERT_EXT(convert_uchar, _rte, uchar);
__CLFN_CONVERT(convert_uchar, uchar);

__CLFN_CONVERT(convert_ushort, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _rte, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _rtp, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _rtn, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _rtz, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _sat, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _sat_rte, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _sat_rtn, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _sat_rtp, ushort);
__CLFN_CONVERT_EXT(convert_ushort, _sat_rtz, ushort);

__CLFN_CONVERT(convert_uint, uint);
__CLFN_CONVERT_EXT(convert_uint, _rte, uint);
__CLFN_CONVERT_EXT(convert_uint, _rtp, uint);
__CLFN_CONVERT_EXT(convert_uint, _rtn, uint);
__CLFN_CONVERT_EXT(convert_uint, _rtz, uint);
__CLFN_CONVERT_EXT(convert_uint, _sat, uint);
__CLFN_CONVERT_EXT(convert_uint, _sat_rte, uint);
__CLFN_CONVERT_EXT(convert_uint, _sat_rtn, uint);
__CLFN_CONVERT_EXT(convert_uint, _sat_rtp, uint);
__CLFN_CONVERT_EXT(convert_uint, _sat_rtz, uint);

__CLFN_CONVERT(convert_ulong, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _rte, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _rtp, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _rtn, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _rtz, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _sat, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _sat_rte, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _sat_rtn, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _sat_rtp, ulong);
__CLFN_CONVERT_EXT(convert_ulong, _sat_rtz, ulong);

__CLFN_CONVERT(convert_char, char);
__CLFN_CONVERT_EXT(convert_char, _rte, char);
__CLFN_CONVERT_EXT(convert_char, _rtp, char);
__CLFN_CONVERT_EXT(convert_char, _rtn, char);
__CLFN_CONVERT_EXT(convert_char, _rtz, char);
__CLFN_CONVERT_EXT(convert_char, _sat, char);
__CLFN_CONVERT_EXT(convert_char, _sat_rte, char);
__CLFN_CONVERT_EXT(convert_char, _sat_rtn, char);
__CLFN_CONVERT_EXT(convert_char, _sat_rtp, char);
__CLFN_CONVERT_EXT(convert_char, _sat_rtz, char);

__CLFN_CONVERT(convert_short, short);
__CLFN_CONVERT_EXT(convert_short, _rte, short);
__CLFN_CONVERT_EXT(convert_short, _rtp, short);
__CLFN_CONVERT_EXT(convert_short, _rtn, short);
__CLFN_CONVERT_EXT(convert_short, _rtz, short);
__CLFN_CONVERT_EXT(convert_short, _sat, short);
__CLFN_CONVERT_EXT(convert_short, _sat_rte, short);
__CLFN_CONVERT_EXT(convert_short, _sat_rtn, short);
__CLFN_CONVERT_EXT(convert_short, _sat_rtp, short);
__CLFN_CONVERT_EXT(convert_short, _sat_rtz, short);

__CLFN_CONVERT(convert_int, int);
__CLFN_CONVERT_EXT(convert_int, _rte, int);
__CLFN_CONVERT_EXT(convert_int, _rtp, int);
__CLFN_CONVERT_EXT(convert_int, _rtn, int);
__CLFN_CONVERT_EXT(convert_int, _rtz, int);
__CLFN_CONVERT_EXT(convert_int, _sat, int);
__CLFN_CONVERT_EXT(convert_int, _sat_rte, int);
__CLFN_CONVERT_EXT(convert_int, _sat_rtn, int);
__CLFN_CONVERT_EXT(convert_int, _sat_rtp, int);
__CLFN_CONVERT_EXT(convert_int, _sat_rtz, int);

__CLFN_CONVERT(convert_long, long);
__CLFN_CONVERT_EXT(convert_long, _rte, long);
__CLFN_CONVERT_EXT(convert_long, _rtp, long);
__CLFN_CONVERT_EXT(convert_long, _rtn, long);
__CLFN_CONVERT_EXT(convert_long, _rtz, long);
__CLFN_CONVERT_EXT(convert_long, _sat, long);
__CLFN_CONVERT_EXT(convert_long, _sat_rte, long);
__CLFN_CONVERT_EXT(convert_long, _sat_rtn, long);
__CLFN_CONVERT_EXT(convert_long, _sat_rtp, long);
__CLFN_CONVERT_EXT(convert_long, _sat_rtz, long);

__CLFN_CONVERT(convert_float, float);
__CLFN_CONVERT_EXT(convert_float, _rte, float);
__CLFN_CONVERT_EXT(convert_float, _rtp, float);
__CLFN_CONVERT_EXT(convert_float, _rtn, float);
__CLFN_CONVERT_EXT(convert_float, _rtz, float);

#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
__CLFN_CONVERT(convert_double, double);
__CLFN_CONVERT_EXT(convert_double, _rte, double);
__CLFN_CONVERT_EXT(convert_double, _rtp, double);
__CLFN_CONVERT_EXT(convert_double, _rtn, double);
__CLFN_CONVERT_EXT(convert_double, _rtz, double);
#endif

#endif

#endif // !AIR64

// 6.2.4.2 as_typen
#define as_char( _x )   __builtin_astype( _x, char )
#define as_uchar( _x )  __builtin_astype( _x, uchar )
#define as_short( _x )  __builtin_astype( _x, short )
#define as_ushort( _x ) __builtin_astype( _x, ushort )
#define as_int( _x )    __builtin_astype( _x, int )
#define as_uint( _x )   __builtin_astype( _x, uint )
#define as_float( _x )  __builtin_astype( _x, float )
#define as_long( _x )   __builtin_astype( _x, long )
#define as_ulong( _x )  __builtin_astype( _x, ulong )
#define as_double( _x ) __builtin_astype( _x, double )

#define as_size_t( _x ) __builtin_astype( _x, size_t )
#define as_intptr_t( _x ) __builtin_astype( _x, intptr_t )
#define as_uintptr_t( _x ) __builtin_astype( _x, uintptr_t )
#define as_ptrdiff_t( _x ) __builtin_astype( _x, ptrdiff_t )

#define as_char2( _x )   __builtin_astype( _x, char2 )
#define as_char3( _x )   __builtin_astype( _x, char3 )
#define as_char4( _x )   __builtin_astype( _x, char4 )
#define as_char8( _x )   __builtin_astype( _x, char8 )
#define as_char16( _x )  __builtin_astype( _x, char16 )

#define as_uchar2( _x )   __builtin_astype( _x, uchar2 )
#define as_uchar3( _x )   __builtin_astype( _x, uchar3 )
#define as_uchar4( _x )   __builtin_astype( _x, uchar4 )
#define as_uchar8( _x )   __builtin_astype( _x, uchar8 )
#define as_uchar16( _x )  __builtin_astype( _x, uchar16 )

#define as_short2( _x )   __builtin_astype( _x, short2 )
#define as_short3( _x )   __builtin_astype( _x, short3 )
#define as_short4( _x )   __builtin_astype( _x, short4 )
#define as_short8( _x )   __builtin_astype( _x, short8 )
#define as_short16( _x )  __builtin_astype( _x, short16 )

#define as_ushort2( _x )   __builtin_astype( _x, ushort2 )
#define as_ushort3( _x )   __builtin_astype( _x, ushort3 )
#define as_ushort4( _x )   __builtin_astype( _x, ushort4 )
#define as_ushort8( _x )   __builtin_astype( _x, ushort8 )
#define as_ushort16( _x )  __builtin_astype( _x, ushort16 )

#define as_int2( _x )   __builtin_astype( _x, int2 )
#define as_int3( _x )   __builtin_astype( _x, int3 )
#define as_int4( _x )   __builtin_astype( _x, int4 )
#define as_int8( _x )   __builtin_astype( _x, int8 )
#define as_int16( _x )  __builtin_astype( _x, int16 )

#define as_uint2( _x )   __builtin_astype( _x, uint2 )
#define as_uint3( _x )   __builtin_astype( _x, uint3 )
#define as_uint4( _x )   __builtin_astype( _x, uint4 )
#define as_uint8( _x )   __builtin_astype( _x, uint8 )
#define as_uint16( _x )  __builtin_astype( _x, uint16 )

#define as_float2( _x )   __builtin_astype( _x, float2 )
#define as_float3( _x )   __builtin_astype( _x, float3 )
#define as_float4( _x )   __builtin_astype( _x, float4 )
#define as_float8( _x )   __builtin_astype( _x, float8 )
#define as_float16( _x )  __builtin_astype( _x, float16 )

#define as_long2( _x )   __builtin_astype( _x, long2 )
#define as_long3( _x )   __builtin_astype( _x, long3 )
#define as_long4( _x )   __builtin_astype( _x, long4 )
#define as_long8( _x )   __builtin_astype( _x, long8 )
#define as_long16( _x )  __builtin_astype( _x, long16 )

#define as_ulong2( _x )   __builtin_astype( _x, ulong2 )
#define as_ulong3( _x )   __builtin_astype( _x, ulong3 )
#define as_ulong4( _x )   __builtin_astype( _x, ulong4 )
#define as_ulong8( _x )   __builtin_astype( _x, ulong8 )
#define as_ulong16( _x )  __builtin_astype( _x, ulong16 )

#define as_double2( _x )   __builtin_astype( _x, double2 )
#define as_double3( _x )   __builtin_astype( _x, double3 )
#define as_double4( _x )   __builtin_astype( _x, double4 )
#define as_double8( _x )   __builtin_astype( _x, double8 )
#define as_double16( _x )  __builtin_astype( _x, double16 )

// 5.6 Image Access Qualifiers
#define __rd __attribute__((annotate("__rd")))
#define __wr __attribute__((annotate("__wr")))
#define __read_only __attribute__((annotate("__rd")))
#define read_only __attribute__((annotate("__rd")))
#define __write_only __attribute__((annotate("__wr")))
#define write_only __attribute__((annotate("__wr")))
#define __read_write __attribute__((annotate("__rw")))
#define read_write __attribute__((annotate("__rw")))

// 5.9.1 - Work-item Functions
// These are defined for GPUs by their respective builtin implementations.
#if defined(__AIR64__)
#define __AIR_ASM__ __OVERLOAD__
#define __AIR_FUNC__ static inline __OVERLOAD_INLINE__
#define __AIR_INTERNAL__ __OVERLOAD__
#define __AIR_TGT__ __OVERLOAD__


__AIR_ASM__ uint   get_work_dim(void) __asm("air.get_work_dim.i32");
__AIR_ASM__ size_t get_global_size(uint dimindx) __asm("air.get_global_size.i32");
__AIR_ASM__ size_t get_global_id(uint dimindx) __asm("air.get_global_id.i32");
__AIR_ASM__ size_t get_global_offset(uint dimindx) __asm("air.get_global_offset.i32");
__AIR_ASM__ size_t get_local_size(uint dimindx) __asm("air.get_local_size.i32");
__AIR_ASM__ size_t get_local_id (uint dimindx) __asm("air.get_local_id.i32");
__AIR_ASM__ size_t get_num_groups(uint dimindx) __asm("air.get_num_groups.i32");
__AIR_ASM__ size_t get_group_id(uint dimindx) __asm("air.get_group_id.i32");
#else  // !AIR64
uint   get_work_dim(void);
size_t get_global_size(uint dimindx);
size_t get_global_id(uint dimindx);
size_t get_global_offset(uint dimindx);
size_t get_local_size(uint dimindx);
size_t get_local_id (uint dimindx);
size_t get_num_groups(uint dimindx);
size_t get_group_id(uint dimindx);
#endif

// 5.9.2 - Math Defines
#define MAXFLOAT 0x1.fffffep+127f
#define HUGE_VALF __builtin_huge_valf()
#define INFINITY __builtin_inff()
#define NAN __builtin_nanf("0x7fc00000")

// image format description
typedef struct _cl_image_format_t {
  unsigned int num_channels;
  unsigned int channel_order;
  unsigned int channel_data_type;
} cl_image_format_t;

typedef __global struct  _image1d_t        *image1d_t;
typedef __global struct  _image2d_t        *image2d_t;
typedef __global struct  _image3d_t        *image3d_t;

typedef __global struct  _image1d_array_t  *image1d_array_t;
typedef __global struct  _image2d_array_t  *image2d_array_t;

typedef __global struct  _image1d_buffer_t *image1d_buffer_t;

typedef __global struct  _image2d_depth_t       *image2d_depth_t;
typedef __global struct  _image2d_array_depth_t *image2d_array_depth_t;
typedef __global struct  _image2d_msaa_t        *image2d_msaa_t;
typedef __global struct  _image2d_array_msaa_t  *image2d_array_msaa_t;
typedef __global struct  _image2d_msaa_depth_t  *image2d_msaa_depth_t;
typedef __global struct  _image2d_array_msaa_depth_t *image2d_array_msaa_depth_t;

#if defined(__AIR64__)
  // Include air header
  #include "cl_kernel_air64.h"
#else // !__AIR64__
/* Section 5.9.2, Table 5.7 */
__CLFN_F_1F(half_cos);
__CLFN_F_2F(half_divide);
__CLFN_F_1F(half_exp);
__CLFN_F_1F(half_exp2);
__CLFN_F_1F(half_exp10);
__CLFN_F_1F(half_log);
__CLFN_F_1F(half_log2);
__CLFN_F_1F(half_log10);
__CLFN_F_2F(half_powr);
__CLFN_F_1F(half_recip);
__CLFN_F_1F(half_rsqrt);
__CLFN_F_1F(half_sin);
__CLFN_F_1F(half_sqrt);
__CLFN_F_1F(half_tan);

__CLFN_FD_1FD(native_cos);
__CLFN_FD_2FD(native_divide);
__CLFN_FD_1FD(native_exp);
__CLFN_FD_1FD(native_exp2);
__CLFN_FD_1FD(native_exp10);
__CLFN_FD_1FD(native_log);
__CLFN_FD_1FD(native_log2);
__CLFN_FD_1FD(native_log10);
__CLFN_FD_2FD(native_powr);
__CLFN_FD_1FD(native_recip);
__CLFN_FD_1FD(native_rsqrt);
__CLFN_FD_1FD(native_sin);
__CLFN_FD_1FD(native_sqrt);
__CLFN_FD_1FD(native_tan);


/* Section 5.9.2, Table 5.6 */
__CLFN_FD_1FD(__cl_acos);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef acos
    #define acos(__x) __cl_acos(__x)
#else
    #warning  __CL_INTERNAL_SKIP_MATH_DEFINES__  defined.   Many builtin definitions will be missing.
#endif

__CLFN_FD_1FD(__cl_acosh);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef acosh
    #define acosh(__x) __cl_acosh(__x)
#endif

__CLFN_FD_1FD(acospi);

__CLFN_FD_1FD(__cl_asin);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef asin
    #define asin(__x) __cl_asin(__x)
#endif

__CLFN_FD_1FD(__cl_asinh);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef asinh
    #define asinh(__x) __cl_asinh(__x)
#endif

__CLFN_FD_1FD(asinpi);

__CLFN_FD_1FD(__cl_atan);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef atan
    #define atan(__x) __cl_atan(__x)
#endif

__CLFN_FD_1FD(__cl_atanh);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef atanh
    #define atanh(__x) __cl_atanh(__x)
#endif

__CLFN_FD_1FD(atanpi);

__CLFN_FD_2FD(__cl_atan2);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef atan2
    #define atan2(__x, __y) __cl_atan2(__x, __y)
#endif

__CLFN_FD_2FD(atan2pi);

__CLFN_FD_1FD(__cl_cbrt);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef cbrt
    #define cbrt(__x) __cl_cbrt(__x)
#endif

__CLFN_FD_1FD(__cl_ceil);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef ceil
    #define ceil(__x) __cl_ceil(__x)
#endif

__CLFN_FD_2FD(__cl_copysign);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef copysign
    #define copysign(__x, __y) __cl_copysign(__x, __y)
#endif

__CLFN_FD_1FD(__cl_cosh);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef cosh
    #define cosh(__x) __cl_cosh(__x)
#endif

__CLFN_FD_1FD(cospi);

__CLFN_FD_1FD(__cl_erf);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef erf
    #define erf(__x) __cl_erf(__x)
#endif

__CLFN_FD_1FD(__cl_erfc);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef erfc
    #define erfc(__x) __cl_erfc(__x)
#endif

__CLFN_FD_1FD(__cl_exp);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    __CLFN_FD_1FD_FAST_RELAX(__fast_relax_exp, native_exp, __cl_exp);
    #undef exp
    #define exp(__x) __fast_relax_exp(__x)
#endif

__CLFN_FD_1FD(__cl_exp2);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    __CLFN_FD_1FD_FAST_RELAX(__fast_relax_exp2, native_exp2, __cl_exp2);
    #undef exp2
    #define exp2(__x) __fast_relax_exp2(__x)
#endif

__CLFN_FD_1FD(__cl_exp10);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    __CLFN_FD_1FD_FAST_RELAX(__fast_relax_exp10, native_exp10, __cl_exp10);
    #undef exp10
    #define exp10(__x) __fast_relax_exp10(__x)
#endif

__CLFN_FD_1FD(asinpi);

__CLFN_FD_1FD(__cl_expm1);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef expm1
    #define expm1(__x) __cl_expm1(__x)
#endif

__CLFN_FD_1FD(__cl_fabs);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef fabs
    #define fabs(__x) __cl_fabs(__x)
#endif

__CLFN_FD_2FD(__cl_fdim);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef fdim
    #define fdim(__x, __y) __cl_fdim(__x, __y)
#endif

__CLFN_FD_1FD(__cl_floor);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef floor
    #define floor(__x) __cl_floor(__x)
#endif

__CLFN_FD_3FD(__cl_fma);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef fma
    #define fma(__x, __y, __z) __cl_fma(__x, __y, __z)
#endif

__CLFN_FD_2FD(__cl_fmax);
__CLFN_FD_2FD_EXT(__cl_fmax);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef fmax
    #define fmax(__x, __y) __cl_fmax(__x, __y)
#endif

__CLFN_FD_2FD(__cl_fmin);
__CLFN_FD_2FD_EXT(__cl_fmin);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef fmin
    #define fmin(__x, __y) __cl_fmin(__x, __y)
#endif

__CLFN_FD_2FD(__cl_fmod);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef fmod
    #define fmod(__x, __y) __cl_fmod(__x, __y)
#endif

__CLFN_FD_1FD_1PFD(fract);

__CLFN_FD_1FD_1PI(__cl_frexp);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef frexp
    #define frexp(__x, __y) __cl_frexp(__x, __y)
#endif

__CLFN_FD_2FD(__cl_hypot);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef hypot
    #define hypot(__x, __y) __cl_hypot(__x, __y)
#endif

__CLFN_I_1FD(__cl_ilogb);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef ilogb
    #define ilogb(__x) __cl_ilogb(__x)
#endif

__CLFN_FD_1FD_1I(__cl_ldexp);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef ldexp
    #define ldexp(__x, __y) __cl_ldexp(__x, __y)
#endif

__CLFN_FD_1FD(__cl_lgamma);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef lgamma
    #define lgamma(__x) __cl_lgamma(__x)
#endif

__CLFN_FD_1FD_1PI(__cl_lgamma_r);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef lgamma_r
    #define lgamma_r(__x, __y) __cl_lgamma_r(__x, __y)
#endif

__CLFN_FD_1FD(__cl_log);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    __CLFN_FD_1FD_FAST_RELAX(__fast_relax_log, native_log, __cl_log);
    #undef log
    #define log(__x) __fast_relax_log(__x)
#endif

__CLFN_FD_1FD(__cl_log10);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    __CLFN_FD_1FD_FAST_RELAX(__fast_relax_log10, native_log10, __cl_log10);
    #undef log10
    #define log10(__x) __cl_log10(__x)
#endif

__CLFN_FD_1FD(__cl_log1p);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef log1p
    #define log1p(__x) __cl_log1p(__x)
#endif

__CLFN_FD_1FD(__cl_log2);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef log2
    #define log2(__x) __cl_log2(__x)
#endif

__CLFN_FD_1FD(__cl_logb);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef logb
    #define logb(__x) __cl_logb(__x)
#endif

__CLFN_FD_3FD(mad);
__CLFN_FD_2FD(maxmag);
__CLFN_FD_2FD(minmag);

__CLFN_FD_1FD_1PFD(__cl_modf);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef modf
    #define modf(__x, __y) __cl_modf(__x, __y)
#endif


__CLFN_FD_1UIL(__cl_nan);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef nan
    #define nan(__x) __cl_nan(__x)
#endif

__CLFN_FD_2FD(__cl_nextafter);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef nextafter
    #define nextafter(__x, __y) __cl_nextafter(__x, __y)
#endif

__CLFN_FD_2FD(__cl_pow);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef pow
    #define pow(__x, __y) __cl_pow(__x, __y)
#endif

__CLFN_FD_1FD_1I(__cl_pown);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef pown
    #define pown(__x, __y) __cl_pown(__x, __y)
#endif

__CLFN_FD_2FD(__cl_powr);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
   __CLFN_FD_2FD_FAST_RELAX(__fast_relax_powr, native_powr, __cl_powr);
    #undef powr
    #define powr(__x, __y) __cl_powr(__x, __y)
#endif

__CLFN_FD_2FD(__cl_remainder);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef remainder
    #define remainder(__x, __y) __cl_remainder(__x, __y)
#endif

__CLFN_FD_2FD_1PI(__cl_remquo);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef remquo
    #define remquo(__x, __y, __z) __cl_remquo(__x, __y, __z)
#endif

__CLFN_FD_1FD(__cl_rint);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef rint
    #define rint(__x) __cl_rint(__x)
#endif

__CLFN_FD_1FD_1I(rootn);

__CLFN_FD_1FD(__cl_round);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef round
    #define round(__x) __cl_round(__x)
#endif

__CLFN_FD_1FD(rsqrt);


__CLFN_FD_1FD(__cl_cos);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    __CLFN_FD_1FD_FAST_RELAX(__fast_relax_cos, native_cos, __cl_cos);
    #undef cos
    #define cos(__x) __fast_relax_cos(__x)
#endif

__CLFN_FD_1FD(__cl_sin);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    __CLFN_FD_1FD_FAST_RELAX(__fast_relax_sin, native_sin, __cl_sin);
    #undef sin
    #define sin(__x) __fast_relax_sin(__x)
#endif

__CLFN_FD_1FD(__cl_tan);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    __CLFN_FD_1FD_FAST_RELAX(__fast_relax_tan, native_tan, __cl_tan);
    #undef tan
    #define tan(__x) __fast_relax_tan(__x)
#endif

__CLFN_FD_1FD_1PFD(sincos);

__CLFN_FD_1FD(__cl_sinh);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef sinh
    #define sinh(__x) __cl_sinh(__x)
#endif

__CLFN_FD_1FD(sinpi);

__CLFN_FD_1FD(__cl_sqrt);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef sqrt
    #define sqrt(__x) __cl_sqrt(__x)
#endif


__CLFN_FD_1FD(__cl_tanh);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef tanh
    #define tanh(__x) __cl_tanh(__x)
#endif

__CLFN_FD_1FD(tanpi);

__CLFN_FD_1FD(__cl_tgamma);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef tgamma
    #define tgamma(__x) __cl_tgamma(__x)
#endif

__CLFN_FD_1FD(__cl_trunc);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef trunc
    #define trunc(__x) __cl_trunc(__x)
#endif

/* Section 5.9.3 */

__CLFN_UCSIL_1CSIL(__cl_abs);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef abs
    #define abs(__x) __cl_abs(__x)
#endif

__CLFN_UCSIL_2CSIL(abs_diff);
__CLFN_ALL(add_sat);

/* upsample */
short __OVERLOAD_INLINE__ upsample(char ahi, uchar alo);
short2 __OVERLOAD_INLINE__ upsample(char2 ahi, uchar2 alo);
short4 __OVERLOAD_INLINE__ upsample(char4 ahi, uchar4 alo);
short3 __OVERLOAD_INLINE__ upsample(char3 ahi, uchar3 alo);
short8 __OVERLOAD_INLINE__ upsample(char8 ahi, uchar8 alo);
short16 __OVERLOAD_INLINE__ upsample(char16 ahi, uchar16 alo);
ushort __OVERLOAD_INLINE__ upsample(uchar ahi, uchar alo);
ushort2 __OVERLOAD_INLINE__ upsample(uchar2 ahi, uchar2 alo);
ushort3 __OVERLOAD_INLINE__ upsample(uchar3 ahi, uchar3 alo);
ushort4 __OVERLOAD_INLINE__ upsample(uchar4 ahi, uchar4 alo);
ushort8 __OVERLOAD_INLINE__ upsample(uchar8 ahi, uchar8 alo);
ushort16 __OVERLOAD_INLINE__ upsample(uchar16 ahi, uchar16 alo);
int __OVERLOAD_INLINE__ upsample(short ahi, ushort alo);
int2 __OVERLOAD_INLINE__ upsample(short2 ahi, ushort2 alo);
int4 __OVERLOAD_INLINE__ upsample(short4 ahi, ushort4 alo);
int3 __OVERLOAD_INLINE__ upsample(short3 ahi, ushort3 alo);
int8 __OVERLOAD_INLINE__ upsample(short8 ahi, ushort8 alo);
int16 __OVERLOAD_INLINE__ upsample(short16 ahi, ushort16 alo);
uint __OVERLOAD_INLINE__ upsample(ushort ahi, ushort alo);
uint2 __OVERLOAD_INLINE__ upsample(ushort2 ahi, ushort2 alo);
uint3 __OVERLOAD_INLINE__ upsample(ushort3 ahi, ushort3 alo);
uint4 __OVERLOAD_INLINE__ upsample(ushort4 ahi, ushort4 alo);
uint8 __OVERLOAD_INLINE__ upsample(ushort8 ahi, ushort8 alo);
uint16 __OVERLOAD_INLINE__ upsample(ushort16 ahi, ushort16 alo);
long __OVERLOAD_INLINE__ upsample(int ahi, uint alo);
long2 __OVERLOAD_INLINE__ upsample(int2 ahi, uint2 alo); 
long3 __OVERLOAD_INLINE__ upsample(int3 ahi, uint3 alo);
long4 __OVERLOAD_INLINE__ upsample(int4 ahi, uint4 alo);
long8 __OVERLOAD_INLINE__ upsample(int8 ahi, uint8 alo);
long16 __OVERLOAD_INLINE__ upsample(int16 ahi, uint16 alo);
ulong __OVERLOAD_INLINE__ upsample(uint ahi, uint alo);
ulong2 __OVERLOAD_INLINE__ upsample(uint2 ahi, uint2 alo); 
ulong3 __OVERLOAD_INLINE__ upsample(uint3 ahi3, uint3 alo3); 
ulong4 __OVERLOAD_INLINE__ upsample(uint4 ahi, uint4 alo); 
ulong8 __OVERLOAD_INLINE__ upsample(uint8 ahi, uint8 alo);
ulong16 __OVERLOAD_INLINE__ upsample(uint16 ahi, uint16 alo);

__CLFN_ALL(hadd);
__CLFN_ALL(rhadd);
__CLFN_CSIL_1CSIL(clz);
__CLFN_CSIL_1CSIL(popcount);
__CLFN_I3(mad_hi);
__CLFN_I3(mad_hi_sat);
__CLFN_I3(mad_sat);

__CLFN_ALL(max);
__CLFN_ALL_MODD(max);
__CLFN_FD_2FD(max);

__CLFN_ALL(min);
__CLFN_ALL_MODD(min);
__CLFN_FD_2FD(min);

__CLFN_I_3CSIL(msum);
__CLFN_ALL(rotate);
__CLFN_ALL(mul_hi);
__CLFN_ALL(sub_sat);

__CLFN_I_3I(mad24);
__CLFN_I_2I(mul24);

/* Section 5.9.4 */
float __OVERLOAD__ clamp(float x, float minval, float maxval);
float2 __OVERLOAD__ clamp(float2 x, float2 minval, float2 maxval);
float3 __OVERLOAD__ clamp(float3 x, float3 minval, float3 maxval);
float4 __OVERLOAD__ clamp(float4 x, float4 minval, float4 maxval);
float8 __OVERLOAD__ clamp( float8 x, float8 minval, float8 maxval );
float16 __OVERLOAD__ clamp( float16 x, float16 minval, float16 maxval );
#if 0
float2 __OVERLOAD__ clamp(float2 x, float minval, float maxval);
float3 __OVERLOAD__ clamp(float3 x, float minval, float maxval);
float4 __OVERLOAD__ clamp(float4 x, float minval, float maxval);
float8 __OVERLOAD__ clamp(float8 x, float minval, float maxval);
float16 __OVERLOAD__ clamp(float16 x, float minval, float maxval);
double2 __OVERLOAD__ clamp(double2 x, double minval, double maxval);
double3 __OVERLOAD__ clamp(double3 x, double minval, double maxval);
double4 __OVERLOAD__ clamp(double4 x, double minval, double maxval);
double8 __OVERLOAD__ clamp(double8 x, double minval, double maxval);
double16 __OVERLOAD__ clamp(double16 x, double minval, double maxval);
#endif
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double __OVERLOAD__ clamp(double x, double minval, double maxval);
#endif
double2 __OVERLOAD__ clamp(double2 x, double2 minval, double2 maxval);
double3 __OVERLOAD__ clamp(double3 x, double3 minval, double3 maxval);
double4 __OVERLOAD__ clamp(double4 x, double4 minval, double4 maxval);
double8 __OVERLOAD__ clamp( double8 x, double8 minval, double8 maxval );
double16 __OVERLOAD__ clamp( double16 x, double16 minval, double16 maxval );
char __OVERLOAD__ clamp( char x, char min, char max );
short __OVERLOAD__ clamp( short x, short min, short max );
int __OVERLOAD__ clamp( int x, int min, int max );
long __OVERLOAD__ clamp( long x, long min, long max );
uchar __OVERLOAD__ clamp( uchar x, uchar min, uchar max );
ushort __OVERLOAD__ clamp( ushort x, ushort min, ushort max );
uint __OVERLOAD__ clamp( uint x, uint min, uint max );
ulong __OVERLOAD__ clamp( ulong x, ulong min, ulong max );
char2 __OVERLOAD__ clamp( char2 x, char2 min, char2 max );
short2 __OVERLOAD__ clamp( short2 x, short2 min, short2 max );
int2 __OVERLOAD__ clamp( int2 x, int2 min, int2 max );
long2 __OVERLOAD__ clamp( long2 x, long2 min, long2 max );
uchar2 __OVERLOAD__ clamp( uchar2 x, uchar2 min, uchar2 max );
ushort2 __OVERLOAD__ clamp( ushort2 x, ushort2 min, ushort2 max );
uint2 __OVERLOAD__ clamp( uint2 x, uint2 min, uint2 max );
ulong2 __OVERLOAD__ clamp( ulong2 x, ulong2 min, ulong2 max );
char3 __OVERLOAD__ clamp( char3 x, char3 min, char3 max );
short3 __OVERLOAD__ clamp( short3 x, short3 min, short3 max );
int3 __OVERLOAD__ clamp( int3 x3, int3 min3, int3 max3 );
long3 __OVERLOAD__ clamp( long3 x3, long3 min3, long3 max3 );
uchar3 __OVERLOAD__ clamp( uchar3 x, uchar3 min, uchar3 max );
ushort3 __OVERLOAD__ clamp( ushort3 x, ushort3 min, ushort3 max );
uint3 __OVERLOAD__ clamp( uint3 x3, uint3 min3, uint3 max3 );
ulong3 __OVERLOAD__ clamp( ulong3 x3, ulong3 min3, ulong3 max3 );
char4 __OVERLOAD__ clamp( char4 x, char4 min, char4 max );
short4 __OVERLOAD__ clamp( short4 x, short4 min, short4 max );
int4 __OVERLOAD__ clamp( int4 x, int4 min, int4 max );
long4 __OVERLOAD__ clamp( long4 x, long4 min, long4 max );
uchar4 __OVERLOAD__ clamp( uchar4 x, uchar4 min, uchar4 max );
ushort4 __OVERLOAD__ clamp( ushort4 x, ushort4 min, ushort4 max );
uint4 __OVERLOAD__ clamp( uint4 x, uint4 min, uint4 max );
ulong4 __OVERLOAD__ clamp( ulong4 x, ulong4 min, ulong4 max );
char8 __OVERLOAD__ clamp( char8 x, char8 min, char8 max );
short8 __OVERLOAD__ clamp( short8 x, short8 min, short8 max );
int8 __OVERLOAD__ clamp( int8 x, int8 min, int8 max );
long8 __OVERLOAD__ clamp( long8 x, long8 min, long8 max );
uchar8 __OVERLOAD__ clamp( uchar8 x, uchar8 min, uchar8 max );
ushort8 __OVERLOAD__ clamp( ushort8 x, ushort8 min, ushort8 max );
uint8 __OVERLOAD__ clamp( uint8 x, uint8 min, uint8 max );
ulong8 __OVERLOAD__ clamp( ulong8 x, ulong8 min, ulong8 max );
char16 __OVERLOAD__ clamp( char16 x, char16 min, char16 max );
short16 __OVERLOAD__ clamp( short16 x, short16 min, short16 max );
int16 __OVERLOAD__ clamp( int16 x, int16 min, int16 max );
long16 __OVERLOAD__ clamp( long16 x, long16 min, long16 max );
ushort16 __OVERLOAD__ clamp( ushort16 x, ushort16 min, ushort16 max );
uchar16 __OVERLOAD__ clamp( uchar16 x, uchar16 min, uchar16 max );
uint16 __OVERLOAD__ clamp( uint16 x, uint16 min, uint16 max );
ulong16 __OVERLOAD__ clamp( ulong16 x, ulong16 min, ulong16 max );
char2 __OVERLOAD__ clamp( char2 x,  char y, char z );
char3 __OVERLOAD__ clamp( char3 x,  char y, char z );
char4 __OVERLOAD__ clamp( char4 x,  char y, char z );
char8 __OVERLOAD__ clamp( char8 x,  char y, char z );
char16 __OVERLOAD__ clamp( char16 x, char y, char z );
uchar2 __OVERLOAD__ clamp( uchar2 x,  uchar y, uchar z );
uchar3 __OVERLOAD__ clamp( uchar3 x,  uchar y, uchar z );
uchar4 __OVERLOAD__ clamp( uchar4 x,  uchar y, uchar z );
uchar8 __OVERLOAD__ clamp( uchar8 x,  uchar y, uchar z );
uchar16 __OVERLOAD__ clamp( uchar16 x, uchar y, uchar z );
short2 __OVERLOAD__ clamp( short2 x,  short y, short z );
short3 __OVERLOAD__ clamp( short3 x,  short y, short z );
short4 __OVERLOAD__ clamp( short4 x,  short y, short z );
short8 __OVERLOAD__ clamp( short8 x,  short y, short z );
short16 __OVERLOAD__ clamp( short16 x, short y, short z );
ushort2 __OVERLOAD__ clamp( ushort2 x,  ushort y, ushort z );
ushort3 __OVERLOAD__ clamp( ushort3 x,  ushort y, ushort z );
ushort4 __OVERLOAD__ clamp( ushort4 x,  ushort y, ushort z );
ushort8 __OVERLOAD__ clamp( ushort8 x,  ushort y, ushort z );
ushort16 __OVERLOAD__ clamp( ushort16 x, ushort y, ushort z );
int2 __OVERLOAD__ clamp( int2 x,  int y, int z );
int3 __OVERLOAD__ clamp( int3 x,  int y, int z );
int4 __OVERLOAD__ clamp( int4 x,  int y, int z );
int8 __OVERLOAD__ clamp( int8 x,  int y, int z );
int16 __OVERLOAD__ clamp( int16 x, int y, int z );
uint2 __OVERLOAD__ clamp( uint2 x,  uint y, uint z );
uint3 __OVERLOAD__ clamp( uint3 x,  uint y, uint z );
uint4 __OVERLOAD__ clamp( uint4 x,  uint y, uint z );
uint8 __OVERLOAD__ clamp( uint8 x,  uint y, uint z );
uint16 __OVERLOAD__ clamp( uint16 x, uint y, uint z );
long2 __OVERLOAD__ clamp( long2 x,  long y, long z );
long3 __OVERLOAD__ clamp( long3 x,  long y, long z );
long4 __OVERLOAD__ clamp( long4 x,  long y, long z );
long8 __OVERLOAD__ clamp( long8 x,  long y, long z );
long16 __OVERLOAD__ clamp( long16 x, long y, long z );
ulong2 __OVERLOAD__ clamp( ulong2 x,  ulong y, ulong z );
ulong3 __OVERLOAD__ clamp( ulong3 x,  ulong y, ulong z );
ulong4 __OVERLOAD__ clamp( ulong4 x,  ulong y, ulong z );
ulong8 __OVERLOAD__ clamp( ulong8 x,  ulong y, ulong z );
ulong16 __OVERLOAD__ clamp( ulong16 x, ulong y, ulong z );
float2 __OVERLOAD__ clamp(float2 x, float minval, float maxval);
float3 __OVERLOAD__ clamp(float3 x, float minval, float maxval);
float4 __OVERLOAD__ clamp(float4 x, float minval, float maxval);
float8 __OVERLOAD__ clamp(float8 x, float minval, float maxval);
float16 __OVERLOAD__ clamp(float16 x, float minval, float maxval);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double2 __OVERLOAD__ clamp(double2 x, double minval, double maxval);
double3 __OVERLOAD__ clamp(double3 x, double minval, double maxval);
double4 __OVERLOAD__ clamp(double4 x, double minval, double maxval);
double8 __OVERLOAD__ clamp(double8 x, double minval, double maxval);
double16 __OVERLOAD__ clamp(double16 x, double minval, double maxval);
#endif


__CLFN_FD_1FD(degrees);

__CLFN_1FD_2FD_MODD(distance);
__CLFN_1FD_2FD_MODD(dot);

float3 __OVERLOAD__ cross(float3 x, float3 y);
float4 __OVERLOAD__ cross(float4 x, float4 y);
double3 __OVERLOAD__ cross(double3 x, double3 y); \
double4 __OVERLOAD__ cross(double4 x, double4 y); \

__CLFN_FD_1FD_MODD(length);
__CLFN_FD_3FD(mix);
__CLFN_FD_3FD_MOD(mix);
__CLFN_FD_1FD_MODD4(normalize);
__CLFN_FD_1FD(radians);

__CLFN_FD_2FD(step);
float2 __OVERLOAD__ step(float edge, float2 x);
float3 __OVERLOAD__ step(float edge, float3 x);
float4 __OVERLOAD__ step(float edge, float4 x);
float8 __OVERLOAD__ step(float edge, float8 x);
float16 __OVERLOAD__ step(float edge, float16 x);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double2 __OVERLOAD__ step(double edge, double2 x);
double3 __OVERLOAD__ step(double edge, double3 x);
double4 __OVERLOAD__ step(double edge, double4 x);
double8 __OVERLOAD__ step(double edge, double8 x);
double16 __OVERLOAD__ step(double edge, double16 x);
#endif

__CLFN_FD_3FD(smoothstep);
float2 __OVERLOAD__ smoothstep( float edge0, float edge1, float2 x );
float3 __OVERLOAD__ smoothstep( float edge0, float edge1, float3 x );
float4 __OVERLOAD__ smoothstep( float edge0, float edge1, float4 x );
float8 __OVERLOAD__ smoothstep( float edge0, float edge1, float8 x );
float16 __OVERLOAD__ smoothstep( float edge0, float edge1, float16 x );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double2 __OVERLOAD__ smoothstep( double e0, double e1, double2 x );
double3 __OVERLOAD__ smoothstep( double e0, double e1, double3 x );
double4 __OVERLOAD__ smoothstep( double e0, double e1, double4 x );
double8 __OVERLOAD__ smoothstep( double e0, double e1, double8 x );
double16 __OVERLOAD__ smoothstep( double e0, double e1, double16 x );
#endif
__CLFN_FD_1FD(sign);
        
__CLFN_1F_2F_MODD(fast_distance);
__CLFN_F_1F_MODD4(fast_length);
__CLFN_F_1F(fast_normalize);

/* Section 5.9.5 */
#define isless(X,Y)             ((X) <  (Y))
#define islessequal(X,Y)        ((X) <= (Y))
#define isgreater(X,Y)          ((X) >  (Y))
#define isgreaterequal(X,Y)     ((X) >= (Y))
#define isequal(X,Y)            ((X) == (Y))
#define isnotequal(X,Y)         ((X) != (Y))

__CLFN_IL_2FD(__cl_islessgreater);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef islessgreater
    #define islessgreater(__x, __y) __cl_islessgreater(__x, __y)
#endif

__CLFN_IL_1FD_MODD(__cl_isfinite);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef isfinite
    #define isfinite(__x) __cl_isfinite(__x)
#endif

__CLFN_IL_1FD_MODD(__cl_isinf);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef isinf
    #define isinf(__x) __cl_isinf(__x)
#endif

__CLFN_IL_1FD_MODD(__cl_isnan);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef isnan
    #define isnan(__x) __cl_isnan(__x)
#endif

__CLFN_IL_1FD_MODD(__cl_isnormal);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef isnormal
    #define isnormal(__x) __cl_isnormal(__x)
#endif

__CLFN_IL_2FD(isordered);

__CLFN_IL_2FD(__cl_isunordered);
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef isunordered
    #define isunordered(__x, __y) __cl_isunordered(__x, __y)
#endif

int __OVERLOAD__ __cl_signbit( float x );
int2 __OVERLOAD__ __cl_signbit( float2 x );
int3 __OVERLOAD__ __cl_signbit( float3 x );
int4 __OVERLOAD__ __cl_signbit( float4 x );
int8 __OVERLOAD__ __cl_signbit( float8 x );
int16 __OVERLOAD__ __cl_signbit( float16 x );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
int __OVERLOAD__ __cl_signbit( double x );
#endif
long2 __OVERLOAD__ __cl_signbit( double2 x );
long3 __OVERLOAD__ __cl_signbit( double3 x );
long4 __OVERLOAD__ __cl_signbit( double4 x );
long8 __OVERLOAD__ __cl_signbit( double8 x );
long16 __OVERLOAD__ __cl_signbit( double16 x );
#ifndef __CL_INTERNAL_SKIP_MATH_DEFINES__
    #undef signbit
    #define signbit(__x) __cl_signbit(__x)
#endif

__CLFN_I_ALL(any);
__CLFN_I_ALL(all);

char __OVERLOAD__ select( char x, char y, char m );
uchar __OVERLOAD__ select( uchar x, uchar y, char m );
short __OVERLOAD__ select( short x, short y, short m );
ushort __OVERLOAD__ select( ushort x, ushort y, short m );
int __OVERLOAD__ select( int x, int y, int m );
uint __OVERLOAD__ select( uint x, uint y, int m );
long __OVERLOAD__ select( long x, long y, long m );
ulong __OVERLOAD__ select( ulong x, ulong y, long m );
char __OVERLOAD__ select( char x, char y, uchar m );
uchar __OVERLOAD__ select( uchar x, uchar y, uchar m );
short __OVERLOAD__ select( short x, short y, ushort m );
ushort __OVERLOAD__ select( ushort x, ushort y, ushort m );
int __OVERLOAD__ select( int x, int y, uint m );
uint __OVERLOAD__ select( uint x, uint y, uint m );
long __OVERLOAD__ select( long x, long y, ulong m );
ulong __OVERLOAD__ select( ulong x, ulong y, ulong m );
float __OVERLOAD__ select( float x, float y, int m );
float __OVERLOAD__ select( float x, float y, uint m );
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double __OVERLOAD__ select( double x, double y, long m );
double __OVERLOAD__ select( double x, double y, ulong m );
#endif
char2 __OVERLOAD__ select( char2 x, char2 y, char2 m );
char3 __OVERLOAD__ select( char3 x, char3 y, char3 m );
char4 __OVERLOAD__ select( char4 x, char4 y, char4 m );
char8 __OVERLOAD__ select( char8 x, char8 y, char8 m );
char16 __OVERLOAD__ select( char16 vx, char16 vy, char16 vm );
uchar2 __OVERLOAD__ select( uchar2 x, uchar2 y, char2 m );
uchar3 __OVERLOAD__ select( uchar3 x, uchar3 y, char3 m );
uchar4 __OVERLOAD__ select( uchar4 x, uchar4 y, char4 m );
uchar8 __OVERLOAD__ select( uchar8 x, uchar8 y, char8 m );
uchar16 __OVERLOAD__ select( uchar16 vx, uchar16 vy, char16 vm );
char2 __OVERLOAD__ select( char2 x, char2 y, uchar2 m );
char3 __OVERLOAD__ select( char3 x, char3 y, uchar3 m );
char4 __OVERLOAD__ select( char4 x, char4 y, uchar4 m );
char8 __OVERLOAD__ select( char8 x, char8 y, uchar8 m );
char16 __OVERLOAD__ select( char16 x, char16 y, uchar16 m );
uchar2 __OVERLOAD__ select( uchar2 x, uchar2 y, uchar2 m );
uchar3 __OVERLOAD__ select( uchar3 x, uchar3 y, uchar3 m );
uchar4 __OVERLOAD__ select( uchar4 x, uchar4 y, uchar4 m );
uchar8 __OVERLOAD__ select( uchar8 x, uchar8 y, uchar8 m );
uchar16 __OVERLOAD__ select( uchar16 x, uchar16 y, uchar16 m );
short2 __OVERLOAD__ select( short2 x, short2 y, short2 m );
short3 __OVERLOAD__ select( short3 x, short3 y, short3 m );
short4 __OVERLOAD__ select( short4 x, short4 y, short4 m );
short8 __OVERLOAD__ select( short8 vx, short8 vy, short8 vm );
short16 __OVERLOAD__ select( short16 vx, short16 vy, short16 vm );
ushort2 __OVERLOAD__ select( ushort2 x, ushort2 y, short2 m );
ushort3 __OVERLOAD__ select( ushort3 x, ushort3 y, short3 m );
ushort4 __OVERLOAD__ select( ushort4 x, ushort4 y, short4 m );
ushort8 __OVERLOAD__ select( ushort8 vx, ushort8 vy, short8 vm );
ushort16 __OVERLOAD__ select( ushort16 vx, ushort16 vy, short16 vm );
short2 __OVERLOAD__ select( short2 x, short2 y, ushort2 m );
short3 __OVERLOAD__ select( short3 x, short3 y, ushort3 m );
short4 __OVERLOAD__ select( short4 x, short4 y, ushort4 m );
short8 __OVERLOAD__ select( short8 x, short8 y, ushort8 m );
short16 __OVERLOAD__ select( short16 x, short16 y, ushort16 m );
ushort2 __OVERLOAD__ select( ushort2 x, ushort2 y, ushort2 m );
ushort3 __OVERLOAD__ select( ushort3 x, ushort3 y, ushort3 m );
ushort4 __OVERLOAD__ select( ushort4 x, ushort4 y, ushort4 m );
ushort8 __OVERLOAD__ select( ushort8 x, ushort8 y, ushort8 m );
ushort16 __OVERLOAD__ select( ushort16 x, ushort16 y, ushort16 m );
int2 __OVERLOAD__ select( int2 x, int2 y, int2 m );
int3 __OVERLOAD__ select( int3 x, int3 y, int3 m );
int4 __OVERLOAD__ select( int4 vx, int4 vy, int4 vm );
int8 __OVERLOAD__ select( int8 vx, int8 vy, int8 vm );
int16 __OVERLOAD__ select( int16 vx, int16 vy, int16 vm );
uint2 __OVERLOAD__ select( uint2 x, uint2 y, int2 m );
uint3 __OVERLOAD__ select( uint3 x, uint3 y, int3 m );
uint4 __OVERLOAD__ select( uint4 x, uint4 y, int4 m );
uint8 __OVERLOAD__ select( uint8 x, uint8 y, int8 m );
uint16 __OVERLOAD__ select( uint16 x, uint16 y, int16 m );
int2 __OVERLOAD__ select( int2 x, int2 y, uint2 m );
int3 __OVERLOAD__ select( int3 x, int3 y, uint3 m );
int4 __OVERLOAD__ select( int4 x, int4 y, uint4 m );
int8 __OVERLOAD__ select( int8 x, int8 y, uint8 m );
int16 __OVERLOAD__ select( int16 x, int16 y, uint16 m );
uint2 __OVERLOAD__ select( uint2 x, uint2 y, uint2 m );
uint3 __OVERLOAD__ select( uint3 x, uint3 y, uint3 m );
uint4 __OVERLOAD__ select( uint4 x, uint4 y, uint4 m );
uint8 __OVERLOAD__ select( uint8 x, uint8 y, uint8 m );
uint16 __OVERLOAD__ select( uint16 x, uint16 y, uint16 m );
long2 __OVERLOAD__ select( long2 x, long2 y, long2 m );
long3 __OVERLOAD__ select( long3 x, long3 y, long3 m );
long4 __OVERLOAD__ select( long4 x, long4 y, long4 m );
long8 __OVERLOAD__ select( long8 x, long8 y, long8 m );
long16 __OVERLOAD__ select( long16 x, long16 y, long16 m );
ulong2 __OVERLOAD__ select( ulong2 x, ulong2 y, long2 m );
ulong3 __OVERLOAD__ select( ulong3 x, ulong3 y, long3 m );
ulong4 __OVERLOAD__ select( ulong4 x, ulong4 y, long4 m );
ulong8 __OVERLOAD__ select( ulong8 x, ulong8 y, long8 m );
ulong16 __OVERLOAD__ select( ulong16 x, ulong16 y, long16 m );
long2 __OVERLOAD__ select( long2 x, long2 y, ulong2 m );
long3 __OVERLOAD__ select( long3 x, long3 y, ulong3 m );
long4 __OVERLOAD__ select( long4 x, long4 y, ulong4 m );
long8 __OVERLOAD__ select( long8 x, long8 y, ulong8 m );
long16 __OVERLOAD__ select( long16 x, long16 y, ulong16 m );
ulong2 __OVERLOAD__ select( ulong2 x, ulong2 y, ulong2 m );
ulong3 __OVERLOAD__ select( ulong3 x, ulong3 y, ulong3 m );
ulong4 __OVERLOAD__ select( ulong4 x, ulong4 y, ulong4 m );
ulong8 __OVERLOAD__ select( ulong8 x, ulong8 y, ulong8 m );
ulong16 __OVERLOAD__ select( ulong16 x, ulong16 y, ulong16 m );
float2 __OVERLOAD__ select( float2 x, float2 y, int2 m );
float3 __OVERLOAD__ select(float3 x, float3 y, __int3_SPI z);
float4 __OVERLOAD__ select( float4 x, float4 y, int4 m );
float8 __OVERLOAD__ select( float8 x, float8 y, int8 m );
float16 __OVERLOAD__ select( float16 x, float16 y, int16 m );
float2 __OVERLOAD__ select( float2 x, float2 y, uint2 m );
float3 __OVERLOAD__ select( float3 x, float3 y, uint3 m );
float4 __OVERLOAD__ select( float4 x, float4 y, uint4 m );
float8 __OVERLOAD__ select( float8 x, float8 y, uint8 m );
float16 __OVERLOAD__ select( float16 x, float16 y, uint16 m );
double2 __OVERLOAD__ select( double2 x, double2 y, long2 m ) ;
double3 __OVERLOAD__ select( double3 x, double3 y, long3 m ) ;
double4 __OVERLOAD__ select( double4 x, double4 y, long4 m ) ;
double8 __OVERLOAD__ select( double8 x, double8 y, long8 m ) ;
double16 __OVERLOAD__ select( double16 x, double16 y, long16 m ) ;
double2 __OVERLOAD__ select( double2 x, double2 y, ulong2 m ) ;
double3 __OVERLOAD__ select( double3 x, double3 y, ulong3 m ) ;
double4 __OVERLOAD__ select( double4 x, double4 y, ulong4 m ) ;
double8 __OVERLOAD__ select( double8 x, double8 y, ulong8 m ) ;
double16 __OVERLOAD__ select( double16 x, double16 y, ulong16 m ) ;

char __OVERLOAD__ bitselect( char x, char y, char m);
char2 __OVERLOAD__ bitselect( char2 x, char2 y, char2 m);
char3 __OVERLOAD__ bitselect( char3 x, char3 y, char3 m);
char4 __OVERLOAD__ bitselect( char4 x, char4 y, char4 m);
char8 __OVERLOAD__ bitselect( char8 x, char8 y, char8 m);
char16 __OVERLOAD__ bitselect( char16 x, char16 y, char16 m);
uchar __OVERLOAD__ bitselect( uchar x, uchar y, char m);
uchar2 __OVERLOAD__ bitselect( uchar2 x, uchar2 y, char2 m);
uchar3 __OVERLOAD__ bitselect( uchar3 x, uchar3 y, char3 m);
uchar4 __OVERLOAD__ bitselect( uchar4 x, uchar4 y, char4 m);
uchar8 __OVERLOAD__ bitselect( uchar8 x, uchar8 y, char8 m);
uchar16 __OVERLOAD__ bitselect( uchar16 x, uchar16 y, char16 m);
short __OVERLOAD__ bitselect( short x, short y, short m);
short2 __OVERLOAD__ bitselect( short2 x, short2 y, short2 m);
short3 __OVERLOAD__ bitselect( short3 x, short3 y, short3 m);
short4 __OVERLOAD__ bitselect( short4 x, short4 y, short4 m);
short8 __OVERLOAD__ bitselect( short8 x, short8 y, short8 m);
short16 __OVERLOAD__ bitselect( short16 x, short16 y, short16 m);
ushort __OVERLOAD__ bitselect( ushort x, ushort y, short m);
ushort2 __OVERLOAD__ bitselect( ushort2 x, ushort2 y, short2 m);
ushort3 __OVERLOAD__ bitselect( ushort3 x, ushort3 y, short3 m);
ushort4 __OVERLOAD__ bitselect( ushort4 x, ushort4 y, short4 m);
ushort8 __OVERLOAD__ bitselect( ushort8 x, ushort8 y, short8 m);
ushort16 __OVERLOAD__ bitselect( ushort16 x, ushort16 y, short16 m);
int __OVERLOAD__ bitselect( int x, int y, int m);
int2 __OVERLOAD__ bitselect( int2 x, int2 y, int2 m);
int3 __OVERLOAD__ bitselect( int3 x, int3 y, int3 m);
int4 __OVERLOAD__ bitselect( int4 x, int4 y, int4 m);
int8 __OVERLOAD__ bitselect( int8 x, int8 y, int8 m);
int16 __OVERLOAD__ bitselect( int16 x, int16 y, int16 m);
uint __OVERLOAD__ bitselect( uint x, uint y, int m);
uint2 __OVERLOAD__ bitselect( uint2 x, uint2 y, int2 m);
uint3 __OVERLOAD__ bitselect( uint3 x, uint3 y, int3 m);
uint4 __OVERLOAD__ bitselect( uint4 x, uint4 y, int4 m);
uint8 __OVERLOAD__ bitselect( uint8 x, uint8 y, int8 m);
uint16 __OVERLOAD__ bitselect( uint16 x, uint16 y, int16 m);
long __OVERLOAD__ bitselect( long x, long y, long m);
long2 __OVERLOAD__ bitselect( long2 x, long2 y, long2 m);
long3 __OVERLOAD__ bitselect( long3 x, long3 y, long3 m);
long4 __OVERLOAD__ bitselect( long4 x, long4 y, long4 m);
long8 __OVERLOAD__ bitselect( long8 x, long8 y, long8 m);
long16 __OVERLOAD__ bitselect( long16 x, long16 y, long16 m);
ulong __OVERLOAD__ bitselect( ulong x, ulong y, long m);
ulong2 __OVERLOAD__ bitselect( ulong2 x, ulong2 y, long2 m);
ulong3 __OVERLOAD__ bitselect( ulong3 x, ulong3 y, long3 m);
ulong4 __OVERLOAD__ bitselect( ulong4 x, ulong4 y, long4 m);
ulong8 __OVERLOAD__ bitselect( ulong8 x, ulong8 y, long8 m);
ulong16 __OVERLOAD__ bitselect( ulong16 x, ulong16 y, long16 m);
char __OVERLOAD__ bitselect( char x, char y, uchar m);
char2 __OVERLOAD__ bitselect( char2 x, char2 y, uchar2 m);
char3 __OVERLOAD__ bitselect( char3 x, char3 y, uchar3 m);
char4 __OVERLOAD__ bitselect( char4 x, char4 y, uchar4 m);
char8 __OVERLOAD__ bitselect( char8 x, char8 y, uchar8 m);
char16 __OVERLOAD__ bitselect( char16 x, char16 y, uchar16 m);
uchar __OVERLOAD__ bitselect( uchar x, uchar y, uchar m);
uchar2 __OVERLOAD__ bitselect( uchar2 x, uchar2 y, uchar2 m);
uchar3 __OVERLOAD__ bitselect( uchar3 x, uchar3 y, uchar3 m);
uchar4 __OVERLOAD__ bitselect( uchar4 x, uchar4 y, uchar4 m);
uchar8 __OVERLOAD__ bitselect( uchar8 x, uchar8 y, uchar8 m);
uchar16 __OVERLOAD__ bitselect( uchar16 x, uchar16 y, uchar16 m);
short __OVERLOAD__ bitselect( short x, short y, ushort m);
short2 __OVERLOAD__ bitselect( short2 x, short2 y, ushort2 m);
short3 __OVERLOAD__ bitselect( short3 x, short3 y, ushort3 m);
short4 __OVERLOAD__ bitselect( short4 x, short4 y, ushort4 m);
short8 __OVERLOAD__ bitselect( short8 x, short8 y, ushort8 m);
short16 __OVERLOAD__ bitselect( short16 x, short16 y, ushort16 m);
ushort __OVERLOAD__ bitselect( ushort x, ushort y, ushort m);
ushort2 __OVERLOAD__ bitselect( ushort2 x, ushort2 y, ushort2 m);
ushort3 __OVERLOAD__ bitselect( ushort3 x, ushort3 y, ushort3 m);
ushort4 __OVERLOAD__ bitselect( ushort4 x, ushort4 y, ushort4 m);
ushort8 __OVERLOAD__ bitselect( ushort8 x, ushort8 y, ushort8 m);
ushort16 __OVERLOAD__ bitselect( ushort16 x, ushort16 y, ushort16 m);
int __OVERLOAD__ bitselect( int x, int y, uint m);
int2 __OVERLOAD__ bitselect( int2 x, int2 y, uint2 m);
int3 __OVERLOAD__ bitselect( int3 x, int3 y, uint3 m);
int4 __OVERLOAD__ bitselect( int4 x, int4 y, uint4 m);
int8 __OVERLOAD__ bitselect( int8 x, int8 y, uint8 m);
int16 __OVERLOAD__ bitselect( int16 x, int16 y, uint16 m);
uint __OVERLOAD__ bitselect( uint x, uint y, uint m);
uint2 __OVERLOAD__ bitselect( uint2 x, uint2 y, uint2 m);
uint3 __OVERLOAD__ bitselect( uint3 x, uint3 y, uint3 m);
uint4 __OVERLOAD__ bitselect( uint4 x, uint4 y, uint4 m);
uint8 __OVERLOAD__ bitselect( uint8 x, uint8 y, uint8 m);
uint16 __OVERLOAD__ bitselect( uint16 x, uint16 y, uint16 m);
long __OVERLOAD__ bitselect( long x, long y, ulong m);
long2 __OVERLOAD__ bitselect( long2 x, long2 y, ulong2 m);
long3 __OVERLOAD__ bitselect( long3 x, long3 y, ulong3 m);
long4 __OVERLOAD__ bitselect( long4 x, long4 y, ulong4 m);
long8 __OVERLOAD__ bitselect( long8 x, long8 y, ulong8 m);
long16 __OVERLOAD__ bitselect( long16 x, long16 y, ulong16 m);
ulong __OVERLOAD__ bitselect( ulong x, ulong y, ulong m);
ulong2 __OVERLOAD__ bitselect( ulong2 x, ulong2 y, ulong2 m);
ulong3 __OVERLOAD__ bitselect( ulong3 x, ulong3 y, ulong3 m);
ulong4 __OVERLOAD__ bitselect( ulong4 x, ulong4 y, ulong4 m);
ulong8 __OVERLOAD__ bitselect( ulong8 x, ulong8 y, ulong8 m);
ulong16 __OVERLOAD__ bitselect( ulong16 x, ulong16 y, ulong16 m);
float __OVERLOAD__ bitselect( float x, float y, float m);
float2 __OVERLOAD__ bitselect( float2 x, float2 y, float2 m);
float3 __OVERLOAD__ bitselect( float3 x, float3 y, float3 m);
float4 __OVERLOAD__ bitselect( float4 x, float4 y, float4 m);
float8 __OVERLOAD__ bitselect( float8 x, float8 y, float8 m);
float16 __OVERLOAD__ bitselect( float16 x, float16 y, float16 m);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
double __OVERLOAD__ bitselect( double x, double y, double m);
#endif
double2 __OVERLOAD__ bitselect( double2 x, double2 y, double2 m);
double3 __OVERLOAD__ bitselect( double3 x, double3 y, double3 m);
double4 __OVERLOAD__ bitselect( double4 x, double4 y, double4 m);
double8 __OVERLOAD__ bitselect( double8 x, double8 y, double8 m);
double16 __OVERLOAD__ bitselect( double16 x, double16 y, double16 m);

#endif // __AIR64__

// Include shared types that have to be visible both here and in the framework
#include "cl_kernel_shared.h"

// 5.8.4 - Image Stream Read and Write

// 1D
float4 __OVERLOAD__ read_imagef(image1d_t image, sampler_t sampler, int coord);
float4 __OVERLOAD__ read_imagef(image1d_t image, sampler_t sampler, float coord);
int4   __OVERLOAD__ read_imagei(image1d_t image, sampler_t sampler, int coord);
int4   __OVERLOAD__ read_imagei(image1d_t image, sampler_t sampler, float coord);
uint4  __OVERLOAD__ read_imageui(image1d_t image, sampler_t sampler, int coord);
uint4  __OVERLOAD__ read_imageui(image1d_t image, sampler_t sampler, float coord);

// 2D
float4 __OVERLOAD__ read_imagef(image2d_t image, sampler_t sampler, int2 coord);
float4 __OVERLOAD__ read_imagef(image2d_t image, sampler_t sampler, float2 coord);
int4   __OVERLOAD__ read_imagei(image2d_t image, sampler_t sampler, int2 coord);
int4   __OVERLOAD__ read_imagei(image2d_t image, sampler_t sampler, float2 coord);
uint4  __OVERLOAD__ read_imageui(image2d_t image, sampler_t sampler, int2 coord);
uint4  __OVERLOAD__ read_imageui(image2d_t image, sampler_t sampler, float2 coord);
float4 __OVERLOAD__ read_gradient_imagef( image2d_t image, sampler_t sampler, float2 ddx, float2 ddy, float2 coord);
int4   __OVERLOAD__ read_gradient_imagei( image2d_t image, sampler_t sampler, float2 ddx, float2 ddy, float2 coord);
uint4  __OVERLOAD__ read_gradient_imageui( image2d_t image, sampler_t sampler, float2 ddx, float2 ddy, float2 coord);

// 3D
float4 __OVERLOAD__ read_imagef(image3d_t image, sampler_t sampler, int4 coord);
float4 __OVERLOAD__ read_imagef(image3d_t image, sampler_t sampler, float4 coord);
int4   __OVERLOAD__ read_imagei(image3d_t image, sampler_t sampler, int4 coord);
int4   __OVERLOAD__ read_imagei(image3d_t image, sampler_t sampler, float4 coord);
uint4  __OVERLOAD__ read_imageui(image3d_t image, sampler_t sampler, int4 coord);
uint4  __OVERLOAD__ read_imageui(image3d_t image, sampler_t sampler, float4 coord);
float4 __OVERLOAD__ read_gradient_imagef( image3d_t image, sampler_t sampler, float4 ddx, float4 ddy, float4 coord);
int4   __OVERLOAD__ read_gradient_imagei( image3d_t image, sampler_t sampler, float4 ddx, float4 ddy, float4 coord);
uint4  __OVERLOAD__ read_gradient_imageui( image3d_t image, sampler_t sampler, float4 ddx, float4 ddy, float4 coord);

// 1D array
float4 __OVERLOAD__ read_imagef(image1d_array_t image, sampler_t sampler, int2 coord);
float4 __OVERLOAD__ read_imagef(image1d_array_t image, sampler_t sampler, float2 coord);
int4   __OVERLOAD__ read_imagei(image1d_array_t image, sampler_t sampler, int2 coord);
int4   __OVERLOAD__ read_imagei(image1d_array_t image, sampler_t sampler, float2 coord);
uint4  __OVERLOAD__ read_imageui(image1d_array_t image, sampler_t sampler, int2 coord);
uint4  __OVERLOAD__ read_imageui(image1d_array_t image, sampler_t sampler, float2 coord);

// 2D array
float4 __OVERLOAD__ read_imagef(image2d_array_t image, sampler_t sampler, int4 coord);
float4 __OVERLOAD__ read_imagef(image2d_array_t image, sampler_t sampler, float4 coord);
int4   __OVERLOAD__ read_imagei(image2d_array_t image, sampler_t sampler, int4 coord);
int4   __OVERLOAD__ read_imagei(image2d_array_t image, sampler_t sampler, float4 coord);
uint4  __OVERLOAD__ read_imageui(image2d_array_t image, sampler_t sampler, int4 coord);
uint4  __OVERLOAD__ read_imageui(image2d_array_t image, sampler_t sampler, float4 coord);

// Depth image and depth image array
float __OVERLOAD__ read_imagef(image2d_depth_t image, sampler_t sampler, float2 coord);
float __OVERLOAD__ read_imagef(image2d_depth_t image, sampler_t sampler, int2 coord);
float __OVERLOAD__ read_imagef(image2d_array_depth_t image, sampler_t sampler, float4 coord);
float __OVERLOAD__ read_imagef(image2d_array_depth_t image, sampler_t sampler, int4 coord);

// MSAA textures
float4 __OVERLOAD__ read_imagef(image2d_msaa_t image, int2 coord, int sample);
int4   __OVERLOAD__ read_imagei(image2d_msaa_t image, int2 coord, int sample);
uint4  __OVERLOAD__ read_imageui(image2d_msaa_t image, int2 coord, int sample);

float  __OVERLOAD__ read_imagef(image2d_msaa_depth_t image, int2 coord, int sample);

float4 __OVERLOAD__ read_imagef(image2d_array_msaa_t image, int4 coord, int sample);
int4   __OVERLOAD__ read_imagei(image2d_array_msaa_t image, int4 coord, int sample);
uint4  __OVERLOAD__ read_imageui(image2d_array_msaa_t image, int4 coord, int sample);

float  __OVERLOAD__ read_imagef(image2d_array_msaa_depth_t image, int4 coord, int sample);

void __OVERLOAD__ write_imagef(image1d_t image, int coord, float4 color);
void __OVERLOAD__ write_imagef(image1d_buffer_t image, int coord, float4 color);
void __OVERLOAD__ write_imagef(image2d_t image, int2 coord, float4 color);
void __OVERLOAD__ write_imagef(image3d_t image, int4 coord, float4 color);
void __OVERLOAD__ write_imagef(image1d_array_t image, int2 coord, float4 color);
void __OVERLOAD__ write_imagef(image2d_array_t image, int4 coord, float4 color);

// Depth image and depth image array
void __OVERLOAD__ write_imagef(image2d_depth_t image, int2 coord, float color);
void __OVERLOAD__ write_imagef(image2d_array_depth_t image, int4 coord, float color);

void __OVERLOAD__ write_imagei(image1d_t image, int  coord, int4 color);
void __OVERLOAD__ write_imagei(image1d_buffer_t image, int coord, int4 color);
void __OVERLOAD__ write_imagei(image2d_t image, int2 coord, int4 color);
void __OVERLOAD__ write_imagei(image3d_t image, int4 coord, int4 color);
void __OVERLOAD__ write_imagei(image1d_array_t image, int2 coord, int4 color);
void __OVERLOAD__ write_imagei(image2d_array_t image, int4 coord, int4 color);

void __OVERLOAD__ write_imageui(image1d_t image, int coord, uint4 val);
void __OVERLOAD__ write_imageui(image1d_buffer_t image, int coord, uint4 color);
void __OVERLOAD__ write_imageui(image2d_t image, int2 coord, uint4 val);
void __OVERLOAD__ write_imageui(image3d_t image, int4 coord, uint4 val);
void __OVERLOAD__ write_imageui(image1d_array_t image, int2 coord, uint4 color);
void __OVERLOAD__ write_imageui(image2d_array_t image, int4 coord, uint4 color);

void __write_imagef_2d_unorm_int8_rgba_apple_SPI(image2d_t image, int2 coord, float4 val);
void __write_imagef_2d_unorm_int8_bgra_apple_SPI(image2d_t image, int2 coord, float4 val); 
#define write_imagef_unorm_int8_rgba_apple_SPI(_image, _coord, _val) __write_imagef_2d_unorm_int8_rgba_apple_SPI(_image, _coord, _val)
#define write_imagef_unorm_int8_bgra_apple_SPI(_image, _coord, _val) __write_imagef_2d_unorm_int8_bgra_apple_SPI(_image, _coord, _val)

// Sampler-less Reads
// 1D
float4 __OVERLOAD__ read_imagef(image1d_t image, int coord);
float4 __OVERLOAD__ read_imagef(image1d_t image, float coord);
int4   __OVERLOAD__ read_imagei(image1d_t image, int coord);
int4   __OVERLOAD__ read_imagei(image1d_t image, float coord);
uint4  __OVERLOAD__ read_imageui(image1d_t image, int coord);
uint4  __OVERLOAD__ read_imageui(image1d_t image, float coord);

// 2D
float4 __OVERLOAD__ read_imagef(image2d_t image, int2 coord);
float4 __OVERLOAD__ read_imagef(image2d_t image, float2 coord);
int4   __OVERLOAD__ read_imagei(image2d_t image, int2 coord);
int4   __OVERLOAD__ read_imagei(image2d_t image, float2 coord);
uint4  __OVERLOAD__ read_imageui(image2d_t image, int2 coord);
uint4  __OVERLOAD__ read_imageui(image2d_t image, float2 coord);

// 3D
float4 __OVERLOAD__ read_imagef(image3d_t image, int4 coord);
float4 __OVERLOAD__ read_imagef(image3d_t image, float4 coord);
int4   __OVERLOAD__ read_imagei(image3d_t image, int4 coord);
int4   __OVERLOAD__ read_imagei(image3d_t image, float4 coord);
uint4  __OVERLOAD__ read_imageui(image3d_t image, int4 coord);
uint4  __OVERLOAD__ read_imageui(image3d_t image, float4 coord);

// 1D buffer
float4 __OVERLOAD__ read_imagef(image1d_buffer_t image, int coord);
float4 __OVERLOAD__ read_imagef(image1d_buffer_t image, float coord);
int4   __OVERLOAD__ read_imagei(image1d_buffer_t image, int coord);
int4   __OVERLOAD__ read_imagei(image1d_buffer_t image, float coord);
uint4  __OVERLOAD__ read_imageui(image1d_buffer_t image, int coord);
uint4  __OVERLOAD__ read_imageui(image1d_buffer_t image, float coord);

// 1D array
float4 __OVERLOAD__ read_imagef(image1d_array_t image, int2 coord);
float4 __OVERLOAD__ read_imagef(image1d_array_t image, float2 coord);
int4   __OVERLOAD__ read_imagei(image1d_array_t image, int2 coord);
int4   __OVERLOAD__ read_imagei(image1d_array_t image, float2 coord);
uint4  __OVERLOAD__ read_imageui(image1d_array_t image, int2 coord);
uint4  __OVERLOAD__ read_imageui(image1d_array_t image, float2 coord);

// 2D array
float4 __OVERLOAD__ read_imagef(image2d_array_t image, int4 coord);
float4 __OVERLOAD__ read_imagef(image2d_array_t image, float4 coord);
int4   __OVERLOAD__ read_imagei(image2d_array_t image, int4 coord);
int4   __OVERLOAD__ read_imagei(image2d_array_t image, float4 coord);
uint4  __OVERLOAD__ read_imageui(image2d_array_t image, int4 coord);
uint4  __OVERLOAD__ read_imageui(image2d_array_t image, float4 coord);

// Depth image and depth image array
float __OVERLOAD__ read_imagef(image2d_depth_t image, int2 coord);
float __OVERLOAD__ read_imagef(image2d_array_depth_t image, int4 coord);

int __OVERLOAD__ get_image_width(image1d_t img);
int __OVERLOAD__ get_image_width(image2d_t img);
int __OVERLOAD__ get_image_width(image3d_t img);
int __OVERLOAD__ get_image_width(image1d_array_t img);
int __OVERLOAD__ get_image_width(image2d_array_t img);
int __OVERLOAD__ get_image_width(image2d_depth_t img);
int __OVERLOAD__ get_image_width(image2d_array_depth_t img);
int __OVERLOAD__ get_image_width(image2d_msaa_t img);
int __OVERLOAD__ get_image_width(image2d_array_msaa_t img);
int __OVERLOAD__ get_image_width(image2d_msaa_depth_t img);
int __OVERLOAD__ get_image_width(image2d_array_msaa_depth_t img);

int __OVERLOAD__ get_image_height(image2d_t img);
int __OVERLOAD__ get_image_height(image3d_t img);
int __OVERLOAD__ get_image_height(image2d_array_t img);
int __OVERLOAD__ get_image_height(image2d_depth_t img);
int __OVERLOAD__ get_image_height(image2d_array_depth_t img);
int __OVERLOAD__ get_image_height(image2d_msaa_t img);
int __OVERLOAD__ get_image_height(image2d_array_msaa_t img);
int __OVERLOAD__ get_image_height(image2d_msaa_depth_t img);
int __OVERLOAD__ get_image_height(image2d_array_msaa_depth_t img);

int __OVERLOAD__ get_image_depth(image3d_t img);

int __OVERLOAD__ get_image_channel_data_type(image1d_t image);
int __OVERLOAD__ get_image_channel_data_type(image2d_t image);
int __OVERLOAD__ get_image_channel_data_type(image3d_t image);
int __OVERLOAD__ get_image_channel_data_type(image1d_array_t image);
int __OVERLOAD__ get_image_channel_data_type(image2d_array_t image);
int __OVERLOAD__ get_image_channel_data_type(image2d_depth_t image);
int __OVERLOAD__ get_image_channel_data_type(image2d_array_depth_t image);
int __OVERLOAD__ get_image_channel_data_type(image2d_msaa_t image);
int __OVERLOAD__ get_image_channel_data_type(image2d_array_msaa_t image);
int __OVERLOAD__ get_image_channel_data_type(image2d_msaa_depth_t image);
int __OVERLOAD__ get_image_channel_data_type(image2d_array_msaa_depth_t image);

int __OVERLOAD__ get_image_channel_order(image1d_t image);
int __OVERLOAD__ get_image_channel_order(image2d_t image);
int __OVERLOAD__ get_image_channel_order(image3d_t image);
int __OVERLOAD__ get_image_channel_order(image1d_array_t image);
int __OVERLOAD__ get_image_channel_order(image2d_array_t image);
int __OVERLOAD__ get_image_channel_order(image2d_depth_t image);
int __OVERLOAD__ get_image_channel_order(image2d_array_depth_t image);
int __OVERLOAD__ get_image_channel_order(image2d_msaa_t image);
int __OVERLOAD__ get_image_channel_order(image2d_array_msaa_t image);
int __OVERLOAD__ get_image_channel_order(image2d_msaa_depth_t image);
int __OVERLOAD__ get_image_channel_order(image2d_array_msaa_depth_t image);

int2 __OVERLOAD__ get_image_dim(image2d_t image);
int4 __OVERLOAD__ get_image_dim(image3d_t image);
int2 __OVERLOAD__ get_image_dim(image2d_array_t image);
int2 __OVERLOAD__ get_image_dim(image2d_depth_t image);
int2 __OVERLOAD__ get_image_dim(image2d_array_depth_t image);
int2 __OVERLOAD__ get_image_dim(image2d_msaa_t image);
int2 __OVERLOAD__ get_image_dim(image2d_array_msaa_t image);
int2 __OVERLOAD__ get_image_dim(image2d_msaa_depth_t image);
int2 __OVERLOAD__ get_image_dim(image2d_array_msaa_depth_t image);

size_t __OVERLOAD__ get_image_array_size(image1d_array_t image);
size_t __OVERLOAD__ get_image_array_size(image2d_array_t image);
size_t __OVERLOAD__ get_image_array_size(image2d_array_depth_t image);
size_t __OVERLOAD__ get_image_array_size(image2d_array_msaa_t image);
size_t __OVERLOAD__ get_image_array_size(image2d_array_msaa_depth_t image);

// MSAA textures
int __OVERLOAD__ get_image_num_samples(image2d_msaa_t image);
int __OVERLOAD__ get_image_num_samples(image2d_array_msaa_t image);
int __OVERLOAD__ get_image_num_samples(image2d_msaa_depth_t image);
int __OVERLOAD__ get_image_num_samples(image2d_array_msaa_depth_t image);

int __OVERLOAD__ get_image_num_miplevels(image2d_t image);
int __OVERLOAD__ get_image_num_miplevels(image3d_t image);

#if defined( __i386__ ) || defined( __x86_64__ )
// SPI for CoreImage
void __OVERLOAD__ __read_transposed_imagef_resample( __rd image2d_t src, sampler_t smp, float4 x,float4 y, float4 *r, float4 *g, float4 *b, float4 *a);
void __OVERLOAD__ __read_transposed_imagef_resample( __rd image2d_t src, sampler_t smp, float8 x,float8 y, float8 *r, float8 *g, float8 *b, float8 *a);
#define read_transposed_imagef( _src, _smp, _x, _y, _r, _g, _b, _a )   __read_transposed_imagef_resample(_src, _smp, _x, _y, _r, _g, _b, _a )
void __OVERLOAD__ __read_direct_imagef_resample( __rd image2d_t src, sampler_t smp, float4 x,float4 y, float16 *dest);
void __OVERLOAD__ __read_direct_imagef_resample( __rd image2d_t src, sampler_t smp, float8 x,float8 y, float32 *dest);


void __OVERLOAD__ __read_transposed_3d_imagef_resample( __rd image3d_t src, sampler_t smp, float4 x,float4 y, float4 z, float4 *r,float4 *g,float4 *b,float4 *a);
void __OVERLOAD__ __read_transposed_3d_imagef_resample( __rd image3d_t src, sampler_t smp, float8 x,float8 y, float8 z, float8 *r,float8 *g,float8 *b,float8 *a);
#define read_transposed_3d_imagef( _src, _smp, _x, _y, _z, _r, _g, _b, _a )     __read_transposed_imagef_resample( _src, _smp, _x, _y, _z, _r, _g, _b, _a )
void __OVERLOAD__ __read_direct_3d_imagef_resample( __rd image3d_t src, sampler_t smp, float4 x,float4 y, float4 z, float16 *dest );

void __OVERLOAD__ write_transposed_imagef( __wr image2d_t dst, int x, int y, float4 r, float4 g, float4 b, float4 a);
void __OVERLOAD__ write_transposed_imagef( __wr image2d_t dst, int x, int y, float8 r, float8 g, float8 b, float8 a);
void __OVERLOAD__ write_direct_imagef( __wr image2d_t dst, int x, int y, float16 v );
void __OVERLOAD__ write_direct_imagef( __wr image2d_t dst, int x, int y, float32 v );

event_t __OVERLOAD__ __async_work_group_stream_to_image( __wr image2d_t image, size_t x, size_t y, size_t count, 
                                                    const __global float4 *r, const __global float4 *g, 
                                                    const __global float4 *b, const __global float4 *a );
event_t __OVERLOAD__ __async_work_group_stream_to_image( __wr image2d_t image, size_t x, size_t y, size_t count, 
                                                    const __constant float4 *r, const __constant float4 *g, 
                                                    const __constant float4 *b, const __constant float4 *a );
event_t __OVERLOAD__ __async_work_group_stream_to_image( __wr image2d_t image, size_t x, size_t y, size_t count, 
                                                    const __private float4 *r, const __private float4 *g, 
                                                    const __private float4 *b, const __private float4 *a );
event_t __OVERLOAD__ __async_work_group_stream_to_image( __wr image2d_t image, size_t x, size_t y, size_t count, 
                                                    const __local float4 *r, const __local float4 *g, 
                                                    const __local float4 *b, const __local float4 *a );

event_t __OVERLOAD__ __async_work_group_stream_to_image_direct( __wr image2d_t image, size_t x, size_t y, size_t count, const __global float4 *src );
event_t __OVERLOAD__ __async_work_group_stream_to_image_direct( __wr image2d_t image, size_t x, size_t y, size_t count, const __constant float4 *src );
event_t __OVERLOAD__ __async_work_group_stream_to_image_direct( __wr image2d_t image, size_t x, size_t y, size_t count, const __private float4 *src );
event_t __OVERLOAD__ __async_work_group_stream_to_image_direct( __wr image2d_t image, size_t x, size_t y, size_t count, const __local float4 *src );

                   
event_t	__OVERLOAD__  __async_work_group_stream_from_image( __rd image2d_t image, sampler_t sampler, float2 start, float2 stride, size_t count, 
                                                        __private float4 *r,  __private float4 *g,  __private float4 *b,  __private float4 *a );
event_t	__OVERLOAD__  __async_work_group_stream_from_image( __rd image2d_t image, sampler_t sampler, float2 start, float2 stride, size_t count, 
                                                        __global float4 *r,  __global float4 *g,  __global float4 *b,  __global float4 *a );
event_t	__OVERLOAD__  __async_work_group_stream_from_image( __rd image2d_t image, sampler_t sampler, float2 start, float2 stride, size_t count, 
                                                        __local float4 *r,  __local float4 *g,  __local float4 *b,  __local float4 *a );

event_t	__OVERLOAD__  __async_work_group_stream_from_image_direct( __rd image2d_t image, sampler_t sampler, float2 start, float2 stride, size_t count, __private float4 *dest );
event_t	__OVERLOAD__  __async_work_group_stream_from_image_direct( __rd image2d_t image, sampler_t sampler, float2 start, float2 stride, size_t count, __global float4 *dest );
event_t	__OVERLOAD__  __async_work_group_stream_from_image_direct( __rd image2d_t image, sampler_t sampler, float2 start, float2 stride, size_t count, __local float4 *dest );


float16  __ci_gamma_SPI( float4 r, float4 g, float4 b, float4 y );
float32  __ci_gamma8_SPI( float8 r, float8 g, float8 b, float8 y );
void     __ci_gamma_SPI_8( float8 r, float8 g, float8 b, float8 y, float8 *outR, float8 *outG, float8 *outB ); 
float3  __ci_gamma_scalar_SPI( float3 rgb, float y );
#endif

__CLFN_EVENT_ALL(async_work_group_copy);
__CLFN_EVENT_ALL4(async_work_group_strided_copy);

void wait_group_events( int, event_t* );

void __OVERLOAD__  prefetch(const __global char* p, size_t n);
void __OVERLOAD__  prefetch(const __global uchar* p, size_t n);
void __OVERLOAD__  prefetch(const __global short* p, size_t n);
void __OVERLOAD__  prefetch(const __global ushort* p, size_t n);
void __OVERLOAD__  prefetch(const __global int* p, size_t n);
void __OVERLOAD__  prefetch(const __global uint* p, size_t n);
void __OVERLOAD__  prefetch(const __global long* p, size_t n);
void __OVERLOAD__  prefetch(const __global ulong* p, size_t n);
void __OVERLOAD__  prefetch(const __global float* p, size_t n);
#if defined( cl_khr_fp64 ) || defined( cl_APPLE_fp64_basic_ops )
void __OVERLOAD__  prefetch(const __global double* p, size_t n);
#endif
void __OVERLOAD__  prefetch(const __global char2* p, size_t n);
void __OVERLOAD__  prefetch(const __global uchar2* p, size_t n);
void __OVERLOAD__  prefetch(const __global short2* p, size_t n);
void __OVERLOAD__  prefetch(const __global ushort2* p, size_t n);
void __OVERLOAD__  prefetch(const __global int2* p, size_t n);
void __OVERLOAD__  prefetch(const __global uint2* p, size_t n);
void __OVERLOAD__  prefetch(const __global long2* p, size_t n);
void __OVERLOAD__  prefetch(const __global ulong2* p, size_t n);
void __OVERLOAD__  prefetch(const __global float2* p, size_t n);
void __OVERLOAD__  prefetch(const __global double2* p, size_t n);
void __OVERLOAD__  prefetch(const __global char4* p, size_t n);
void __OVERLOAD__  prefetch(const __global uchar4* p, size_t n);
void __OVERLOAD__  prefetch(const __global short4* p, size_t n);
void __OVERLOAD__  prefetch(const __global ushort4* p, size_t n);
void __OVERLOAD__  prefetch(const __global int4* p, size_t n);
void __OVERLOAD__  prefetch(const __global uint4* p, size_t n);
void __OVERLOAD__  prefetch(const __global long4* p, size_t n);
void __OVERLOAD__  prefetch(const __global ulong4* p, size_t n);
void __OVERLOAD__  prefetch(const __global float4* p, size_t n);
void __OVERLOAD__  prefetch(const __global double4* p, size_t n);
void __OVERLOAD__  prefetch(const __global char8* p, size_t n);
void __OVERLOAD__  prefetch(const __global uchar8* p, size_t n);
void __OVERLOAD__  prefetch(const __global short8* p, size_t n);
void __OVERLOAD__  prefetch(const __global ushort8* p, size_t n);
void __OVERLOAD__  prefetch(const __global int8* p, size_t n);
void __OVERLOAD__  prefetch(const __global uint8* p, size_t n);
void __OVERLOAD__  prefetch(const __global long8* p, size_t n);
void __OVERLOAD__  prefetch(const __global ulong8* p, size_t n);
void __OVERLOAD__  prefetch(const __global float8* p, size_t n);
void __OVERLOAD__  prefetch(const __global double8* p, size_t n);
void __OVERLOAD__  prefetch(const __global char16* p, size_t n);
void __OVERLOAD__  prefetch(const __global uchar16* p, size_t n);
void __OVERLOAD__  prefetch(const __global short16* p, size_t n);
void __OVERLOAD__  prefetch(const __global ushort16* p, size_t n);
void __OVERLOAD__  prefetch(const __global int16* p, size_t n);
void __OVERLOAD__  prefetch(const __global uint16* p, size_t n);
void __OVERLOAD__  prefetch(const __global long16* p, size_t n);
void __OVERLOAD__  prefetch(const __global ulong16* p, size_t n);
void __OVERLOAD__  prefetch(const __global float16* p, size_t n);
void __OVERLOAD__  prefetch(const __global double16* p, size_t n);

// 5.9.7 - Synchronization
typedef enum {
  CLK_LOCAL_MEM_FENCE  = 1U << 0,
  CLK_GLOBAL_MEM_FENCE = 1U << 1,
  __unused_except_to_make_sure_the_enum_has_the_right_size = 1U << 31
} cl_mem_fence_flags;

#if defined(__AIR64__)
// AIR helper functions: 
typedef enum __air_mem_flags {
  mem_flags_global = 0x1,
  mem_flags_local = 0x2,
  mem_flags_texture = 0x4
} __air_mem_flags;

#define _AIR_MEM_SCOPE_WORK_GROUP 0x2
__AIR_ASM__ __NO_DUPLICATE__ void _air_llvm_mem_barrier(__air_mem_flags flags, int scope) __asm("air.mem_barrier");
__AIR_ASM__ __NO_DUPLICATE__ void _air_llvm_wg_barrier(__air_mem_flags flags, int scope) __asm("air.wg.barrier");

__AIR_FUNC__ __NO_DUPLICATE__ void barrier(cl_mem_fence_flags flags) {
  _air_llvm_wg_barrier((__air_mem_flags) flags, _AIR_MEM_SCOPE_WORK_GROUP);
}

__AIR_FUNC__ __NO_DUPLICATE__ void mem_fence(cl_mem_fence_flags flags) {
  _air_llvm_mem_barrier((__air_mem_flags)flags, _AIR_MEM_SCOPE_WORK_GROUP);
}

__AIR_FUNC__ __NO_DUPLICATE__ void read_mem_fence(cl_mem_fence_flags flags) {
  _air_llvm_mem_barrier((__air_mem_flags)flags, _AIR_MEM_SCOPE_WORK_GROUP);
}

__AIR_FUNC__ __NO_DUPLICATE__ void write_mem_fence(cl_mem_fence_flags flags) {
  _air_llvm_mem_barrier((__air_mem_flags)flags, _AIR_MEM_SCOPE_WORK_GROUP);
}
#else // !AIR64
__NO_DUPLICATE__ void barrier(cl_mem_fence_flags);
__NO_DUPLICATE__ void mem_fence(cl_mem_fence_flags);
__NO_DUPLICATE__ void read_mem_fence(cl_mem_fence_flags);
__NO_DUPLICATE__ void write_mem_fence(cl_mem_fence_flags);
#endif //AIR64

// 5.9.9 - Atomic Functions
int __OVERLOAD__  atom_add(volatile __global int *p, int val);
int __OVERLOAD__  atom_sub(volatile __global int *p, int val);
int __OVERLOAD__ atom_xchg(volatile __global int *p, int val);
int __OVERLOAD__ atom_min(volatile __global int *p, int val);
int __OVERLOAD__ atom_max(volatile __global int *p, int val);
int __OVERLOAD__ atom_inc(volatile __global int *p);
int __OVERLOAD__ atom_dec(volatile __global int *p);
int __OVERLOAD__ atom_cmpxchg(volatile __global int *p, int cmp, int val);
int __OVERLOAD__ atom_and(volatile __global int *p, int val);
int __OVERLOAD__ atom_or(volatile __global int *p, int val);
int __OVERLOAD__ atom_xor(volatile __global int *p, int val);

unsigned __OVERLOAD__  atom_add(volatile __global unsigned *p, unsigned val);
unsigned __OVERLOAD__  atom_sub(volatile __global unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_xchg(volatile __global unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_min(volatile __global unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_max(volatile __global unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_inc(volatile __global unsigned *p);
unsigned __OVERLOAD__ atom_dec(volatile __global unsigned *p);
unsigned __OVERLOAD__ atom_cmpxchg(volatile __global unsigned *p, unsigned cmp, unsigned val);
unsigned __OVERLOAD__ atom_and(volatile __global unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_or(volatile __global unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_xor(volatile __global unsigned *p, unsigned val);

float __OVERLOAD__ atom_xchg(volatile __global float *p, float val);


int __OVERLOAD__  atom_add(volatile local int *p, int val);
int __OVERLOAD__  atom_sub(volatile local int *p, int val);
int __OVERLOAD__ atom_xchg(volatile local int *p, int val);
int __OVERLOAD__ atom_min(volatile local int *p, int val);
int __OVERLOAD__ atom_max(volatile local int *p, int val);
int __OVERLOAD__ atom_inc(volatile local int *p);
int __OVERLOAD__ atom_dec(volatile local int *p);
int __OVERLOAD__ atom_cmpxchg(volatile local int *p, int cmp, int val);
int __OVERLOAD__ atom_and(volatile local int *p, int val);
int __OVERLOAD__ atom_or(volatile local int *p, int val);
int __OVERLOAD__ atom_xor(volatile local int *p, int val);

unsigned __OVERLOAD__  atom_add(volatile local unsigned *p, unsigned val);
unsigned __OVERLOAD__  atom_sub(volatile local unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_xchg(volatile local unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_min(volatile local unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_max(volatile local unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_inc(volatile local unsigned *p);
unsigned __OVERLOAD__ atom_dec(volatile local unsigned *p);
unsigned __OVERLOAD__ atom_cmpxchg(volatile local unsigned *p, unsigned cmp, unsigned val);
unsigned __OVERLOAD__ atom_and(volatile local unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_or(volatile local unsigned *p, unsigned val);
unsigned __OVERLOAD__ atom_xor(volatile local unsigned *p, unsigned val);

float __OVERLOAD__ atom_xchg(volatile local float *p, float val);


long __OVERLOAD__  atom_add(volatile __global long *p, long val);
long __OVERLOAD__  atom_sub(volatile __global long *p, long val);
long __OVERLOAD__ atom_xchg(volatile __global long *p, long val);
long __OVERLOAD__ atom_min(volatile __global long *p, long val);
long __OVERLOAD__ atom_max(volatile __global long *p, long val);
long __OVERLOAD__ atom_inc(volatile __global long *p);
long __OVERLOAD__ atom_dec(volatile __global long *p);
long __OVERLOAD__ atom_cmpxchg(volatile __global long *p, long cmp, long val);
long __OVERLOAD__ atom_and(volatile __global long *p, long val);
long __OVERLOAD__ atom_or(volatile __global long *p, long val);
long __OVERLOAD__ atom_xor(volatile __global long *p, long val);

ulong __OVERLOAD__  atom_add(volatile __global ulong *p, ulong val);
ulong __OVERLOAD__  atom_sub(volatile __global ulong *p, ulong val);
ulong __OVERLOAD__ atom_xchg(volatile __global ulong *p, ulong val);
ulong __OVERLOAD__ atom_min(volatile __global ulong *p, ulong val);
ulong __OVERLOAD__ atom_max(volatile __global ulong *p, ulong val);
ulong __OVERLOAD__ atom_inc(volatile __global ulong *p);
ulong __OVERLOAD__ atom_dec(volatile __global ulong *p);
ulong __OVERLOAD__ atom_cmpxchg(volatile __global ulong *p, ulong cmp, ulong val);
ulong __OVERLOAD__ atom_and(volatile __global ulong *p, ulong val);
ulong __OVERLOAD__ atom_or(volatile __global ulong *p, ulong val);
ulong __OVERLOAD__ atom_xor(volatile __global ulong *p, ulong val);


long __OVERLOAD__  atom_add(volatile local long *p, long val);
long __OVERLOAD__  atom_sub(volatile local long *p, long val);
long __OVERLOAD__ atom_xchg(volatile local long *p, long val);
long __OVERLOAD__ atom_min(volatile local long *p, long val);
long __OVERLOAD__ atom_max(volatile local long *p, long val);
long __OVERLOAD__ atom_inc(volatile local long *p);
long __OVERLOAD__ atom_dec(volatile local long *p);
long __OVERLOAD__ atom_cmpxchg(volatile local long *p, long cmp, long val);
long __OVERLOAD__ atom_and(volatile local long *p, long val);
long __OVERLOAD__ atom_or(volatile local long *p, long val);
long __OVERLOAD__ atom_xor(volatile local long *p, long val);

ulong __OVERLOAD__  atom_add(volatile local ulong *p, ulong val);
ulong __OVERLOAD__  atom_sub(volatile local ulong *p, ulong val);
ulong __OVERLOAD__ atom_xchg(volatile local ulong *p, ulong val);
ulong __OVERLOAD__ atom_min(volatile local ulong *p, ulong val);
ulong __OVERLOAD__ atom_max(volatile local ulong *p, ulong val);
ulong __OVERLOAD__ atom_inc(volatile local ulong *p);
ulong __OVERLOAD__ atom_dec(volatile local ulong *p);
ulong __OVERLOAD__ atom_cmpxchg(volatile local ulong *p, ulong cmp, ulong val);
ulong __OVERLOAD__ atom_and(volatile local ulong *p, ulong val);
ulong __OVERLOAD__ atom_or(volatile local ulong *p, ulong val);
ulong __OVERLOAD__ atom_xor(volatile local ulong *p, ulong val);

#define atomic_add(X,Y)         atom_add((X),(Y))
#define atomic_sub(X,Y)         atom_sub((X),(Y))
#define atomic_xchg(X,Y)        atom_xchg((X),(Y))
#define atomic_min(X,Y)         atom_min((X),(Y))
#define atomic_max(X,Y)         atom_max((X),(Y))
#define atomic_inc(X)           atom_inc(X)
#define atomic_dec(X)           atom_dec(X)
#define atomic_cmpxchg(X,Y,Z)   atom_cmpxchg((X),(Y),(Z)) 
#define atomic_and(X,Y)         atom_and((X),(Y))
#define atomic_or(X,Y)          atom_or((X),(Y))
#define atomic_xor(X,Y)         atom_xor((X),(Y))

char2 __OVERLOAD__ shuffle( char2 x, uchar2 map );
char4 __OVERLOAD__ shuffle( char2 x, uchar4 map );
char8 __OVERLOAD__ shuffle( char2 x, uchar8 map );
char16 __OVERLOAD__ shuffle( char2 x, uchar16 map );
uchar2 __OVERLOAD__ shuffle( uchar2 x, uchar2 map );
uchar4 __OVERLOAD__ shuffle( uchar2 x, uchar4 map );
uchar8 __OVERLOAD__ shuffle( uchar2 x, uchar8 map );
uchar16 __OVERLOAD__ shuffle( uchar2 x, uchar16 map );
char2 __OVERLOAD__ shuffle( char4 x, uchar2 map );
char4 __OVERLOAD__ shuffle( char4 x, uchar4 map );
char8 __OVERLOAD__ shuffle( char4 x, uchar8 map );
char16 __OVERLOAD__ shuffle( char4 x, uchar16 map );
uchar2 __OVERLOAD__ shuffle( uchar4 x, uchar2 map );
uchar4 __OVERLOAD__ shuffle( uchar4 x, uchar4 map );
uchar8 __OVERLOAD__ shuffle( uchar4 x, uchar8 map );
uchar16 __OVERLOAD__ shuffle( uchar4 x, uchar16 map );
char2 __OVERLOAD__ shuffle( char8 x, uchar2 map );
char4 __OVERLOAD__ shuffle( char8 x, uchar4 map );
char8 __OVERLOAD__ shuffle( char8 x, uchar8 map );
char16 __OVERLOAD__ shuffle( char8 x, uchar16 map );
uchar2 __OVERLOAD__ shuffle( uchar8 x, uchar2 map );
uchar4 __OVERLOAD__ shuffle( uchar8 x, uchar4 map );
uchar8 __OVERLOAD__ shuffle( uchar8 x, uchar8 map );
uchar16 __OVERLOAD__ shuffle( uchar8 x, uchar16 map );
char2 __OVERLOAD__ shuffle( char16 x, uchar2 map );
char4 __OVERLOAD__ shuffle( char16 x, uchar4 map );
char8 __OVERLOAD__ shuffle( char16 x, uchar8 map );
char16 __OVERLOAD__ shuffle( char16 x, uchar16 map );
uchar2 __OVERLOAD__ shuffle( uchar16 x, uchar2 map );
uchar4 __OVERLOAD__ shuffle( uchar16 x, uchar4 map );
uchar8 __OVERLOAD__ shuffle( uchar16 x, uchar8 map );
uchar16 __OVERLOAD__ shuffle( uchar16 x, uchar16 map );
short2 __OVERLOAD__ shuffle( short2 x, ushort2 map );
short4 __OVERLOAD__ shuffle( short2 x, ushort4 map );
short8 __OVERLOAD__ shuffle( short2 x, ushort8 map );
short16 __OVERLOAD__ shuffle( short2 x, ushort16 map );
ushort2 __OVERLOAD__ shuffle( ushort2 x, ushort2 map );
ushort4 __OVERLOAD__ shuffle( ushort2 x, ushort4 map );
ushort8 __OVERLOAD__ shuffle( ushort2 x, ushort8 map );
ushort16 __OVERLOAD__ shuffle( ushort2 x, ushort16 map );
short2 __OVERLOAD__ shuffle( short4 x, ushort2 map );
short4 __OVERLOAD__ shuffle( short4 x, ushort4 map );
short8 __OVERLOAD__ shuffle( short4 x, ushort8 map );
short16 __OVERLOAD__ shuffle( short4 x, ushort16 map );
ushort2 __OVERLOAD__ shuffle( ushort4 x, ushort2 map );
ushort4 __OVERLOAD__ shuffle( ushort4 x, ushort4 map );
ushort8 __OVERLOAD__ shuffle( ushort4 x, ushort8 map );
ushort16 __OVERLOAD__ shuffle( ushort4 x, ushort16 map );
short2 __OVERLOAD__ shuffle( short8 x, ushort2 map );
short4 __OVERLOAD__ shuffle( short8 x, ushort4 map );
short8 __OVERLOAD__ shuffle( short8 x, ushort8 map );
short16 __OVERLOAD__ shuffle( short8 x, ushort16 map );
ushort2 __OVERLOAD__ shuffle( ushort8 x, ushort2 map );
ushort4 __OVERLOAD__ shuffle( ushort8 x, ushort4 map );
ushort8 __OVERLOAD__ shuffle( ushort8 x, ushort8 map );
ushort16 __OVERLOAD__ shuffle( ushort8 x, ushort16 map );
short2 __OVERLOAD__ shuffle( short16 x, ushort2 map );
short4 __OVERLOAD__ shuffle( short16 x, ushort4 map );
short8 __OVERLOAD__ shuffle( short16 x, ushort8 map );
short16 __OVERLOAD__ shuffle( short16 x, ushort16 map );
ushort2 __OVERLOAD__ shuffle( ushort16 x, ushort2 map );
ushort4 __OVERLOAD__ shuffle( ushort16 x, ushort4 map );
ushort8 __OVERLOAD__ shuffle( ushort16 x, ushort8 map );
ushort16 __OVERLOAD__ shuffle( ushort16 x, ushort16 map );
int2 __OVERLOAD__ shuffle( int2 x, uint2 map );
int4 __OVERLOAD__ shuffle( int2 x, uint4 map );
int8 __OVERLOAD__ shuffle( int2 x, uint8 map );
int16 __OVERLOAD__ shuffle( int2 x, uint16 map );
uint2 __OVERLOAD__ shuffle( uint2 x, uint2 map );
uint4 __OVERLOAD__ shuffle( uint2 x, uint4 map );
uint8 __OVERLOAD__ shuffle( uint2 x, uint8 map );
uint16 __OVERLOAD__ shuffle( uint2 x, uint16 map );
int2 __OVERLOAD__ shuffle( int4 x, uint2 map );
int4 __OVERLOAD__ shuffle( int4 x, uint4 map );
int8 __OVERLOAD__ shuffle( int4 x, uint8 map );
int16 __OVERLOAD__ shuffle( int4 x, uint16 map );
uint2 __OVERLOAD__ shuffle( uint4 x, uint2 map );
uint4 __OVERLOAD__ shuffle( uint4 x, uint4 map );
uint8 __OVERLOAD__ shuffle( uint4 x, uint8 map );
uint16 __OVERLOAD__ shuffle( uint4 x, uint16 map );
int2 __OVERLOAD__ shuffle( int8 x, uint2 map );
int4 __OVERLOAD__ shuffle( int8 x, uint4 map );
int8 __OVERLOAD__ shuffle( int8 x, uint8 map );
int16 __OVERLOAD__ shuffle( int8 x, uint16 map );
uint2 __OVERLOAD__ shuffle( uint8 x, uint2 map );
uint4 __OVERLOAD__ shuffle( uint8 x, uint4 map );
uint8 __OVERLOAD__ shuffle( uint8 x, uint8 map );
uint16 __OVERLOAD__ shuffle( uint8 x, uint16 map );
int2 __OVERLOAD__ shuffle( int16 x, uint2 map );
int4 __OVERLOAD__ shuffle( int16 x, uint4 map );
int8 __OVERLOAD__ shuffle( int16 x, uint8 map );
int16 __OVERLOAD__ shuffle( int16 x, uint16 map );
uint2 __OVERLOAD__ shuffle( uint16 x, uint2 map );
uint4 __OVERLOAD__ shuffle( uint16 x, uint4 map );
uint8 __OVERLOAD__ shuffle( uint16 x, uint8 map );
uint16 __OVERLOAD__ shuffle( uint16 x, uint16 map );
long2 __OVERLOAD__ shuffle( long2 x, ulong2 map );
long4 __OVERLOAD__ shuffle( long2 x, ulong4 map );
long8 __OVERLOAD__ shuffle( long2 x, ulong8 map );
long16 __OVERLOAD__ shuffle( long2 x, ulong16 map );
ulong2 __OVERLOAD__ shuffle( ulong2 x, ulong2 map );
ulong4 __OVERLOAD__ shuffle( ulong2 x, ulong4 map );
ulong8 __OVERLOAD__ shuffle( ulong2 x, ulong8 map );
ulong16 __OVERLOAD__ shuffle( ulong2 x, ulong16 map );
long2 __OVERLOAD__ shuffle( long4 x, ulong2 map );
long4 __OVERLOAD__ shuffle( long4 x, ulong4 map );
long8 __OVERLOAD__ shuffle( long4 x, ulong8 map );
long16 __OVERLOAD__ shuffle( long4 x, ulong16 map );
ulong2 __OVERLOAD__ shuffle( ulong4 x, ulong2 map );
ulong4 __OVERLOAD__ shuffle( ulong4 x, ulong4 map );
ulong8 __OVERLOAD__ shuffle( ulong4 x, ulong8 map );
ulong16 __OVERLOAD__ shuffle( ulong4 x, ulong16 map );
long2 __OVERLOAD__ shuffle( long8 x, ulong2 map );
long4 __OVERLOAD__ shuffle( long8 x, ulong4 map );
long8 __OVERLOAD__ shuffle( long8 x, ulong8 map );
long16 __OVERLOAD__ shuffle( long8 x, ulong16 map );
ulong2 __OVERLOAD__ shuffle( ulong8 x, ulong2 map );
ulong4 __OVERLOAD__ shuffle( ulong8 x, ulong4 map );
ulong8 __OVERLOAD__ shuffle( ulong8 x, ulong8 map );
ulong16 __OVERLOAD__ shuffle( ulong8 x, ulong16 map );
long2 __OVERLOAD__ shuffle( long16 x, ulong2 map );
long4 __OVERLOAD__ shuffle( long16 x, ulong4 map );
long8 __OVERLOAD__ shuffle( long16 x, ulong8 map );
long16 __OVERLOAD__ shuffle( long16 x, ulong16 map );
ulong2 __OVERLOAD__ shuffle( ulong16 x, ulong2 map );
ulong4 __OVERLOAD__ shuffle( ulong16 x, ulong4 map );
ulong8 __OVERLOAD__ shuffle( ulong16 x, ulong8 map );
ulong16 __OVERLOAD__ shuffle( ulong16 x, ulong16 map );
float2  __OVERLOAD__ shuffle( float2 x, uint2 map );
float4  __OVERLOAD__ shuffle( float2 x, uint4 map );
float8  __OVERLOAD__ shuffle( float2 x, uint8 map );
float16  __OVERLOAD__ shuffle( float2 x, uint16 map );
float2  __OVERLOAD__ shuffle( float4 x, uint2 map );
float4  __OVERLOAD__ shuffle( float4 x, uint4 map );
float8  __OVERLOAD__ shuffle( float4 x, uint8 map );
float16  __OVERLOAD__ shuffle( float4 x, uint16 map );
float2  __OVERLOAD__ shuffle( float8 x, uint2 map );
float4  __OVERLOAD__ shuffle( float8 x, uint4 map );
float8  __OVERLOAD__ shuffle( float8 x, uint8 map );
float16  __OVERLOAD__ shuffle( float8 x, uint16 map );
float2  __OVERLOAD__ shuffle( float16 x, uint2 map );
float4  __OVERLOAD__ shuffle( float16 x, uint4 map );
float8  __OVERLOAD__ shuffle( float16 x, uint8 map );
float16  __OVERLOAD__ shuffle( float16 x, uint16 map );
double2  __OVERLOAD__ shuffle( double2 x, ulong2 map );
double4  __OVERLOAD__ shuffle( double2 x, ulong4 map );
double8  __OVERLOAD__ shuffle( double2 x, ulong8 map );
double16  __OVERLOAD__ shuffle( double2 x, ulong16 map );
double2  __OVERLOAD__ shuffle( double4 x, ulong2 map );
double4  __OVERLOAD__ shuffle( double4 x, ulong4 map );
double8  __OVERLOAD__ shuffle( double4 x, ulong8 map );
double16  __OVERLOAD__ shuffle( double4 x, ulong16 map );
double2  __OVERLOAD__ shuffle( double8 x, ulong2 map );
double4  __OVERLOAD__ shuffle( double8 x, ulong4 map );
double8  __OVERLOAD__ shuffle( double8 x, ulong8 map );
double16  __OVERLOAD__ shuffle( double8 x, ulong16 map );
double2  __OVERLOAD__ shuffle( double16 x, ulong2 map );
double4  __OVERLOAD__ shuffle( double16 x, ulong4 map );
double8  __OVERLOAD__ shuffle( double16 x, ulong8 map );
double16  __OVERLOAD__ shuffle( double16 x, ulong16 map );

char2 __OVERLOAD__ shuffle2( char2 x, char2 y, uchar2 map);
char2 __OVERLOAD__ shuffle2( char4 x, char4 y, uchar2 map);
char2 __OVERLOAD__ shuffle2( char8 x, char8 y, uchar2 map);
char2 __OVERLOAD__ shuffle2( char16 x, char16 y, uchar2 map);
uchar2 __OVERLOAD__ shuffle2( uchar2 x, uchar2 y, uchar2 map);
uchar2 __OVERLOAD__ shuffle2( uchar4 x, uchar4 y, uchar2 map);
uchar2 __OVERLOAD__ shuffle2( uchar8 x, uchar8 y, uchar2 map);
uchar2 __OVERLOAD__ shuffle2( uchar16 x, uchar16 y, uchar2 map);
char4 __OVERLOAD__ shuffle2( char2 x, char2 y, uchar4 map);
char4 __OVERLOAD__ shuffle2( char4 x, char4 y, uchar4 map);
char4 __OVERLOAD__ shuffle2( char8 x, char8 y, uchar4 map);
char4 __OVERLOAD__ shuffle2( char16 x, char16 y, uchar4 map);
uchar4 __OVERLOAD__ shuffle2( uchar2 x, uchar2 y, uchar4 map);
uchar4 __OVERLOAD__ shuffle2( uchar4 x, uchar4 y, uchar4 map);
uchar4 __OVERLOAD__ shuffle2( uchar8 x, uchar8 y, uchar4 map);
uchar4 __OVERLOAD__ shuffle2( uchar16 x, uchar16 y, uchar4 map);
char8 __OVERLOAD__ shuffle2( char2 x, char2 y, uchar8 map);
char8 __OVERLOAD__ shuffle2( char4 x, char4 y, uchar8 map);
char8 __OVERLOAD__ shuffle2( char8 x, char8 y, uchar8 map);
char8 __OVERLOAD__ shuffle2( char16 x, char16 y, uchar8 map);
uchar8 __OVERLOAD__ shuffle2( uchar2 x, uchar2 y, uchar8 map);
uchar8 __OVERLOAD__ shuffle2( uchar4 x, uchar4 y, uchar8 map);
uchar8 __OVERLOAD__ shuffle2( uchar8 x, uchar8 y, uchar8 map);
uchar8 __OVERLOAD__ shuffle2( uchar16 x, uchar16 y, uchar8 map);
char16 __OVERLOAD__ shuffle2( char2 x, char2 y, uchar16 map);
char16 __OVERLOAD__ shuffle2( char4 x, char4 y, uchar16 map);
char16 __OVERLOAD__ shuffle2( char8 x, char8 y, uchar16 map);
char16 __OVERLOAD__ shuffle2( char16 x, char16 y, uchar16 map);
uchar16 __OVERLOAD__ shuffle2( uchar2 x, uchar2 y, uchar16 map);
uchar16 __OVERLOAD__ shuffle2( uchar4 x, uchar4 y, uchar16 map);
uchar16 __OVERLOAD__ shuffle2( uchar8 x, uchar8 y, uchar16 map);
uchar16 __OVERLOAD__ shuffle2( uchar16 x, uchar16 y, uchar16 map);
short2 __OVERLOAD__ shuffle2( short2 x, short2 y, ushort2 map);
short2 __OVERLOAD__ shuffle2( short4 x, short4 y, ushort2 map);
short2 __OVERLOAD__ shuffle2( short8 x, short8 y, ushort2 map);
short2 __OVERLOAD__ shuffle2( short16 x, short16 y, ushort2 map);
ushort2 __OVERLOAD__ shuffle2( ushort2 x, ushort2 y, ushort2 map);
ushort2 __OVERLOAD__ shuffle2( ushort4 x, ushort4 y, ushort2 map);
ushort2 __OVERLOAD__ shuffle2( ushort8 x, ushort8 y, ushort2 map);
ushort2 __OVERLOAD__ shuffle2( ushort16 x, ushort16 y, ushort2 map);
short4 __OVERLOAD__ shuffle2( short2 x, short2 y, ushort4 map);
short4 __OVERLOAD__ shuffle2( short4 x, short4 y, ushort4 map);
short4 __OVERLOAD__ shuffle2( short8 x, short8 y, ushort4 map);
short4 __OVERLOAD__ shuffle2( short16 x, short16 y, ushort4 map);
ushort4 __OVERLOAD__ shuffle2( ushort2 x, ushort2 y, ushort4 map);
ushort4 __OVERLOAD__ shuffle2( ushort4 x, ushort4 y, ushort4 map);
ushort4 __OVERLOAD__ shuffle2( ushort8 x, ushort8 y, ushort4 map);
ushort4 __OVERLOAD__ shuffle2( ushort16 x, ushort16 y, ushort4 map);
short8 __OVERLOAD__ shuffle2( short2 x, short2 y, ushort8 map);
short8 __OVERLOAD__ shuffle2( short4 x, short4 y, ushort8 map);
short8 __OVERLOAD__ shuffle2( short8 x, short8 y, ushort8 map);
short8 __OVERLOAD__ shuffle2( short16 x, short16 y, ushort8 map);
ushort8 __OVERLOAD__ shuffle2( ushort2 x, ushort2 y, ushort8 map);
ushort8 __OVERLOAD__ shuffle2( ushort4 x, ushort4 y, ushort8 map);
ushort8 __OVERLOAD__ shuffle2( ushort8 x, ushort8 y, ushort8 map);
ushort8 __OVERLOAD__ shuffle2( ushort16 x, ushort16 y, ushort8 map);
short16 __OVERLOAD__ shuffle2( short2 x, short2 y, ushort16 map);
short16 __OVERLOAD__ shuffle2( short4 x, short4 y, ushort16 map);
short16 __OVERLOAD__ shuffle2( short8 x, short8 y, ushort16 map);
short16 __OVERLOAD__ shuffle2( short16 x, short16 y, ushort16 map);
ushort16 __OVERLOAD__ shuffle2( ushort2 x, ushort2 y, ushort16 map);
ushort16 __OVERLOAD__ shuffle2( ushort4 x, ushort4 y, ushort16 map);
ushort16 __OVERLOAD__ shuffle2( ushort8 x, ushort8 y, ushort16 map);
ushort16 __OVERLOAD__ shuffle2( ushort16 x, ushort16 y, ushort16 map);
int2 __OVERLOAD__ shuffle2( int2 x, int2 y, uint2 map);
int2 __OVERLOAD__ shuffle2( int4 x, int4 y, uint2 map);
int2 __OVERLOAD__ shuffle2( int8 x, int8 y, uint2 map);
int2  __OVERLOAD__ shuffle2( int16 x, int16 y, uint2 map);
uint2 __OVERLOAD__ shuffle2( uint2 x, uint2 y, uint2 map);
uint2 __OVERLOAD__ shuffle2( uint4 x, uint4 y, uint2 map);
uint2 __OVERLOAD__ shuffle2( uint8 x, uint8 y, uint2 map);
uint2 __OVERLOAD__ shuffle2( uint16 x, uint16 y, uint2 map);
float2 __OVERLOAD__ shuffle2( float2 x, float2 y, uint2 map);
float2 __OVERLOAD__ shuffle2( float4 x, float4 y, uint2 map);
float2 __OVERLOAD__ shuffle2( float8 x, float8 y, uint2 map);
float2 __OVERLOAD__ shuffle2( float16 x, float16 y, uint2 map);
int4 __OVERLOAD__ shuffle2( int2 x, int2 y, uint4 map);
int4 __OVERLOAD__ shuffle2( int4 x, int4 y, uint4 map);
int4 __OVERLOAD__ shuffle2( int8 x, int8 y, uint4 map);
int4 __OVERLOAD__ shuffle2( int16 x, int16 y, uint4 map);
uint4 __OVERLOAD__ shuffle2( uint2 x, uint2 y, uint4 map);
uint4 __OVERLOAD__ shuffle2( uint4 x, uint4 y, uint4 map);
uint4 __OVERLOAD__ shuffle2( uint8 x, uint8 y, uint4 map);
uint4 __OVERLOAD__ shuffle2( uint16 x, uint16 y, uint4 map);
float4 __OVERLOAD__ shuffle2( float2 x, float2 y, uint4 map);
float4 __OVERLOAD__ shuffle2( float4 x, float4 y, uint4 map);
float4 __OVERLOAD__ shuffle2( float8 x, float8 y, uint4 map);
float4 __OVERLOAD__ shuffle2( float16 x, float16 y, uint4 map);
int8 __OVERLOAD__ shuffle2( int2 x, int2 y, uint8 map);
int8 __OVERLOAD__ shuffle2( int4 x, int4 y, uint8 map);
int8 __OVERLOAD__ shuffle2( int8 x, int8 y, uint8 map);
int8 __OVERLOAD__ shuffle2( int16 x, int16 y, uint8 map);
uint8 __OVERLOAD__ shuffle2( uint2 x, uint2 y, uint8 map);
uint8 __OVERLOAD__ shuffle2( uint4 x, uint4 y, uint8 map);
uint8 __OVERLOAD__ shuffle2( uint8 x, uint8 y, uint8 map);
uint8 __OVERLOAD__ shuffle2( uint16 x, uint16 y, uint8 map);
float8 __OVERLOAD__ shuffle2( float2 x, float2 y, uint8 map);
float8 __OVERLOAD__ shuffle2( float4 x, float4 y, uint8 map);
float8 __OVERLOAD__ shuffle2( float8 x, float8 y, uint8 map);
float8 __OVERLOAD__ shuffle2( float16 x, float16 y, uint8 map);
int16 __OVERLOAD__ shuffle2( int2 x, int2 y, uint16 map);
int16 __OVERLOAD__ shuffle2( int4 x, int4 y, uint16 map);
int16 __OVERLOAD__ shuffle2( int8 x, int8 y, uint16 map);
int16 __OVERLOAD__ shuffle2( int16 x, int16 y, uint16 map);
uint16 __OVERLOAD__ shuffle2( uint2 x, uint2 y, uint16 map);
uint16 __OVERLOAD__ shuffle2( uint4 x, uint4 y, uint16 map);
uint16 __OVERLOAD__ shuffle2( uint8 x, uint8 y, uint16 map);
uint16 __OVERLOAD__ shuffle2( uint16 x, uint16 y, uint16 map);
float16 __OVERLOAD__ shuffle2( float2 x, float2 y, uint16 map);
float16 __OVERLOAD__ shuffle2( float4 x, float4 y, uint16 map);
float16 __OVERLOAD__ shuffle2( float8 x, float8 y, uint16 map);
float16 __OVERLOAD__ shuffle2( float16 x, float16 y, uint16 map);
long2 __OVERLOAD__ shuffle2( long2 x, long2 y, ulong2 map);
long2 __OVERLOAD__ shuffle2( long4 x, long4 y, ulong2 map);
long2 __OVERLOAD__ shuffle2( long8 x, long8 y, ulong2 map);
long2 __OVERLOAD__ shuffle2( long16 x, long16 y, ulong2 map);
ulong2 __OVERLOAD__ shuffle2( ulong2 x, ulong2 y, ulong2 map);
ulong2 __OVERLOAD__ shuffle2( ulong4 x, ulong4 y, ulong2 map);
ulong2 __OVERLOAD__ shuffle2( ulong8 x, ulong8 y, ulong2 map);
ulong2 __OVERLOAD__ shuffle2( ulong16 x, ulong16 y, ulong2 map);
double2 __OVERLOAD__ shuffle2( double2 x, double2 y, ulong2 map);
double2 __OVERLOAD__ shuffle2( double4 x, double4 y, ulong2 map);
double2 __OVERLOAD__ shuffle2( double8 x, double8 y, ulong2 map);
double2 __OVERLOAD__ shuffle2( double16 x, double16 y, ulong2 map);
long4 __OVERLOAD__ shuffle2( long2 x, long2 y, ulong4 map);
long4 __OVERLOAD__ shuffle2( long4 x, long4 y, ulong4 map);
long4 __OVERLOAD__ shuffle2( long8 x, long8 y, ulong4 map);
long4 __OVERLOAD__ shuffle2( long16 x, long16 y, ulong4 map);
ulong4 __OVERLOAD__ shuffle2( ulong2 x, ulong2 y, ulong4 map);
ulong4 __OVERLOAD__ shuffle2( ulong4 x, ulong4 y, ulong4 map);
ulong4 __OVERLOAD__ shuffle2( ulong8 x, ulong8 y, ulong4 map);
ulong4 __OVERLOAD__ shuffle2( ulong16 x, ulong16 y, ulong4 map);
double4 __OVERLOAD__ shuffle2( double2 x, double2 y, ulong4 map);
double4 __OVERLOAD__ shuffle2( double4 x, double4 y, ulong4 map);
double4 __OVERLOAD__ shuffle2( double8 x, double8 y, ulong4 map);
double4 __OVERLOAD__ shuffle2( double16 x, double16 y, ulong4 map);
long8 __OVERLOAD__ shuffle2( long2 x, long2 y, ulong8 map);
long8 __OVERLOAD__ shuffle2( long4 x, long4 y, ulong8 map);
long8 __OVERLOAD__ shuffle2( long8 x, long8 y, ulong8 map);
long8 __OVERLOAD__ shuffle2( long16 x, long16 y, ulong8 map);
ulong8 __OVERLOAD__ shuffle2( ulong2 x, ulong2 y, ulong8 map);
ulong8 __OVERLOAD__ shuffle2( ulong4 x, ulong4 y, ulong8 map);
ulong8 __OVERLOAD__ shuffle2( ulong8 x, ulong8 y, ulong8 map);
ulong8 __OVERLOAD__ shuffle2( ulong16 x, ulong16 y, ulong8 map);
double8 __OVERLOAD__ shuffle2( double2 x, double2 y, ulong8 map);
double8 __OVERLOAD__ shuffle2( double4 x, double4 y, ulong8 map);
double8 __OVERLOAD__ shuffle2( double8 x, double8 y, ulong8 map);
double8 __OVERLOAD__ shuffle2( double16 x, double16 y, ulong8 map);
long16 __OVERLOAD__ shuffle2( long2 x, long2 y, ulong16 map);
long16 __OVERLOAD__ shuffle2( long4 x, long4 y, ulong16 map);
long16 __OVERLOAD__ shuffle2( long8 x, long8 y, ulong16 map);
long16 __OVERLOAD__ shuffle2( long16 x, long16 y, ulong16 map);
ulong16 __OVERLOAD__ shuffle2( ulong2 x, ulong2 y, ulong16 map);
ulong16 __OVERLOAD__ shuffle2( ulong4 x, ulong4 y, ulong16 map);
ulong16 __OVERLOAD__ shuffle2( ulong8 x, ulong8 y, ulong16 map);
ulong16 __OVERLOAD__ shuffle2( ulong16 x, ulong16 y, ulong16 map);
double16 __OVERLOAD__ shuffle2( double2 x, double2 y, ulong16 map);
double16 __OVERLOAD__ shuffle2( double4 x, double4 y, ulong16 map);
double16 __OVERLOAD__ shuffle2( double8 x, double8 y, ulong16 map);
double16 __OVERLOAD__ shuffle2( double16 x, double16 y, ulong16 map);

int __printf_cl(constant char * restrict, ...);
#define printf __printf_cl

int __OVERLOAD__ float_to_fixed_int_float(float x, const int bits);
int2 __OVERLOAD__ float_to_fixed_int_float2(float2 x, const int bits);
int4 __OVERLOAD__ float_to_fixed_int_float4(float4 x, const int bits);
int8 __OVERLOAD__ float_to_fixed_int_float8(float8 x, const int bits);
int16 __OVERLOAD__ float_to_fixed_int_float16(float16 x, const int bits);

uint __OVERLOAD__ float_to_fixed_uint_float(float x, const int bits);
uint2 __OVERLOAD__ float_to_fixed_uint_float2(float2 x, const int bits);
uint4 __OVERLOAD__ float_to_fixed_uint_float4(float4 x, const int bits);
uint8 __OVERLOAD__ float_to_fixed_uint_float8(float8 x, const int bits);
uint16 __OVERLOAD__ float_to_fixed_uint_float16(float16 x, const int bits);

float __OVERLOAD__ fixed_to_float_int_int(int x, int bits);
float2 __OVERLOAD__ fixed_to_float_int_int2(int2 x, int bits);
float4 __OVERLOAD__ fixed_to_float_int_int4(int4 x, int bits);
float8 __OVERLOAD__ fixed_to_float_int_int8(int8 x, int bits);
float16 __OVERLOAD__ fixed_to_float_int_int16(int16 x, int bits);

float __OVERLOAD__ fixed_to_float_uint_uint(uint x, int bits);
float2 __OVERLOAD__ fixed_to_float_uint_uint2(uint2 x, int bits);
float4 __OVERLOAD__ fixed_to_float_uint_uint4(uint4 x, int bits);
float8 __OVERLOAD__ fixed_to_float_uint_uint8(uint8 x, int bits);
float16 __OVERLOAD__ fixed_to_float_uint_uint16(uint16 x, int bits);

#endif  // __CL_KERNEL_H
