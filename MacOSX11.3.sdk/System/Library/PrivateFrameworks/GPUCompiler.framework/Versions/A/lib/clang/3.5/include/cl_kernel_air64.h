//===-- cl_kernels_air64.h ------------------------------------------------===//
// Copyright (c) 2014 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __CL_KERNEL_AIR64
#define __CL_KERNEL_AIR64

#ifndef __AIR_ASM__
#define __AIR_ASM__ __OVERLOAD__
#define __AIR_FUNC__ static inline __OVERLOAD_INLINE__
#define __AIR_INTERNAL__ __OVERLOAD__
#define __AIR_TGT__ __OVERLOAD__
#endif

#define _AIR_PREFIX_half ""
#if defined(__FAST_RELAXED_MATH__)
#define _AIR_PREFIX_float "fast_"
#else
#define _AIR_PREFIX_float ""
#endif
#define _AIR_PREFIX_double ""

#ifndef LOG2_10F
#define LOG2_10F 3.32192809489f
#endif
 
 #ifndef LOG10_2F
 #define LOG10_2F 0.30102999566f
 #endif

// OpenCL 1.2 6.2.3 convert_ operators
  __AIR_ASM__ char convert_char_sat(char a) __asm("air.convert.s.i8.s.i8.sat");
  __AIR_ASM__ char2 convert_char2_sat(char2 a) __asm("air.convert.s.v2i8.s.v2i8.sat");
  __AIR_ASM__ char3 convert_char3_sat(char3 a) __asm("air.convert.s.v3i8.s.v3i8.sat");
  __AIR_ASM__ char4 convert_char4_sat(char4 a) __asm("air.convert.s.v4i8.s.v4i8.sat");
  __AIR_ASM__ char convert_char(char a) __asm("air.convert.s.i8.s.i8");
  __AIR_ASM__ char2 convert_char2(char2 a) __asm("air.convert.s.v2i8.s.v2i8");
  __AIR_ASM__ char3 convert_char3(char3 a) __asm("air.convert.s.v3i8.s.v3i8");
  __AIR_ASM__ char4 convert_char4(char4 a) __asm("air.convert.s.v4i8.s.v4i8");
  __AIR_ASM__ char convert_char_sat(uchar a) __asm("air.convert.s.i8.u.i8.sat");
  __AIR_ASM__ char2 convert_char2_sat(uchar2 a) __asm("air.convert.s.v2i8.u.v2i8.sat");
  __AIR_ASM__ char3 convert_char3_sat(uchar3 a) __asm("air.convert.s.v3i8.u.v3i8.sat");
  __AIR_ASM__ char4 convert_char4_sat(uchar4 a) __asm("air.convert.s.v4i8.u.v4i8.sat");
  __AIR_ASM__ char convert_char(uchar a) __asm("air.convert.s.i8.u.i8");
  __AIR_ASM__ char2 convert_char2(uchar2 a) __asm("air.convert.s.v2i8.u.v2i8");
  __AIR_ASM__ char3 convert_char3(uchar3 a) __asm("air.convert.s.v3i8.u.v3i8");
  __AIR_ASM__ char4 convert_char4(uchar4 a) __asm("air.convert.s.v4i8.u.v4i8");
  __AIR_ASM__ char convert_char_sat(short a) __asm("air.convert.s.i8.s.i16.sat");
  __AIR_ASM__ char2 convert_char2_sat(short2 a) __asm("air.convert.s.v2i8.s.v2i16.sat");
  __AIR_ASM__ char3 convert_char3_sat(short3 a) __asm("air.convert.s.v3i8.s.v3i16.sat");
  __AIR_ASM__ char4 convert_char4_sat(short4 a) __asm("air.convert.s.v4i8.s.v4i16.sat");
  __AIR_ASM__ char convert_char(short a) __asm("air.convert.s.i8.s.i16");
  __AIR_ASM__ char2 convert_char2(short2 a) __asm("air.convert.s.v2i8.s.v2i16");
  __AIR_ASM__ char3 convert_char3(short3 a) __asm("air.convert.s.v3i8.s.v3i16");
  __AIR_ASM__ char4 convert_char4(short4 a) __asm("air.convert.s.v4i8.s.v4i16");
  __AIR_ASM__ char convert_char_sat(ushort a) __asm("air.convert.s.i8.u.i16.sat");
  __AIR_ASM__ char2 convert_char2_sat(ushort2 a) __asm("air.convert.s.v2i8.u.v2i16.sat");
  __AIR_ASM__ char3 convert_char3_sat(ushort3 a) __asm("air.convert.s.v3i8.u.v3i16.sat");
  __AIR_ASM__ char4 convert_char4_sat(ushort4 a) __asm("air.convert.s.v4i8.u.v4i16.sat");
  __AIR_ASM__ char convert_char(ushort a) __asm("air.convert.s.i8.u.i16");
  __AIR_ASM__ char2 convert_char2(ushort2 a) __asm("air.convert.s.v2i8.u.v2i16");
  __AIR_ASM__ char3 convert_char3(ushort3 a) __asm("air.convert.s.v3i8.u.v3i16");
  __AIR_ASM__ char4 convert_char4(ushort4 a) __asm("air.convert.s.v4i8.u.v4i16");
  __AIR_ASM__ char convert_char_sat(int a) __asm("air.convert.s.i8.s.i32.sat");
  __AIR_ASM__ char2 convert_char2_sat(int2 a) __asm("air.convert.s.v2i8.s.v2i32.sat");
  __AIR_ASM__ char3 convert_char3_sat(int3 a) __asm("air.convert.s.v3i8.s.v3i32.sat");
  __AIR_ASM__ char4 convert_char4_sat(int4 a) __asm("air.convert.s.v4i8.s.v4i32.sat");
  __AIR_ASM__ char convert_char(int a) __asm("air.convert.s.i8.s.i32");
  __AIR_ASM__ char2 convert_char2(int2 a) __asm("air.convert.s.v2i8.s.v2i32");
  __AIR_ASM__ char3 convert_char3(int3 a) __asm("air.convert.s.v3i8.s.v3i32");
  __AIR_ASM__ char4 convert_char4(int4 a) __asm("air.convert.s.v4i8.s.v4i32");
  __AIR_ASM__ char convert_char_sat(uint a) __asm("air.convert.s.i8.u.i32.sat");
  __AIR_ASM__ char2 convert_char2_sat(uint2 a) __asm("air.convert.s.v2i8.u.v2i32.sat");
  __AIR_ASM__ char3 convert_char3_sat(uint3 a) __asm("air.convert.s.v3i8.u.v3i32.sat");
  __AIR_ASM__ char4 convert_char4_sat(uint4 a) __asm("air.convert.s.v4i8.u.v4i32.sat");
  __AIR_ASM__ char convert_char(uint a) __asm("air.convert.s.i8.u.i32");
  __AIR_ASM__ char2 convert_char2(uint2 a) __asm("air.convert.s.v2i8.u.v2i32");
  __AIR_ASM__ char3 convert_char3(uint3 a) __asm("air.convert.s.v3i8.u.v3i32");
  __AIR_ASM__ char4 convert_char4(uint4 a) __asm("air.convert.s.v4i8.u.v4i32");
  __AIR_ASM__ char convert_char_sat(long a) __asm("air.convert.s.i8.s.i64.sat");
  __AIR_ASM__ char2 convert_char2_sat(long2 a) __asm("air.convert.s.v2i8.s.v2i64.sat");
  __AIR_ASM__ char3 convert_char3_sat(long3 a) __asm("air.convert.s.v3i8.s.v3i64.sat");
  __AIR_ASM__ char4 convert_char4_sat(long4 a) __asm("air.convert.s.v4i8.s.v4i64.sat");
  __AIR_ASM__ char convert_char(long a) __asm("air.convert.s.i8.s.i64");
  __AIR_ASM__ char2 convert_char2(long2 a) __asm("air.convert.s.v2i8.s.v2i64");
  __AIR_ASM__ char3 convert_char3(long3 a) __asm("air.convert.s.v3i8.s.v3i64");
  __AIR_ASM__ char4 convert_char4(long4 a) __asm("air.convert.s.v4i8.s.v4i64");
  __AIR_ASM__ char convert_char_sat(ulong a) __asm("air.convert.s.i8.u.i64.sat");
  __AIR_ASM__ char2 convert_char2_sat(ulong2 a) __asm("air.convert.s.v2i8.u.v2i64.sat");
  __AIR_ASM__ char3 convert_char3_sat(ulong3 a) __asm("air.convert.s.v3i8.u.v3i64.sat");
  __AIR_ASM__ char4 convert_char4_sat(ulong4 a) __asm("air.convert.s.v4i8.u.v4i64.sat");
  __AIR_ASM__ char convert_char(ulong a) __asm("air.convert.s.i8.u.i64");
  __AIR_ASM__ char2 convert_char2(ulong2 a) __asm("air.convert.s.v2i8.u.v2i64");
  __AIR_ASM__ char3 convert_char3(ulong3 a) __asm("air.convert.s.v3i8.u.v3i64");
  __AIR_ASM__ char4 convert_char4(ulong4 a) __asm("air.convert.s.v4i8.u.v4i64");
  __AIR_ASM__ char convert_char_sat_rtz(float a) __asm("air.convert.s.i8.f.f32.rtz.sat");
  __AIR_ASM__ char2 convert_char2_sat_rtz(float2 a) __asm("air.convert.s.v2i8.f.v2f32.rtz.sat");
  __AIR_ASM__ char3 convert_char3_sat_rtz(float3 a) __asm("air.convert.s.v3i8.f.v3f32.rtz.sat");
  __AIR_ASM__ char4 convert_char4_sat_rtz(float4 a) __asm("air.convert.s.v4i8.f.v4f32.rtz.sat");
  __AIR_ASM__ char convert_char_sat_rtn(float a) __asm("air.convert.s.i8.f.f32.rtn.sat");
  __AIR_ASM__ char2 convert_char2_sat_rtn(float2 a) __asm("air.convert.s.v2i8.f.v2f32.rtn.sat");
  __AIR_ASM__ char3 convert_char3_sat_rtn(float3 a) __asm("air.convert.s.v3i8.f.v3f32.rtn.sat");
  __AIR_ASM__ char4 convert_char4_sat_rtn(float4 a) __asm("air.convert.s.v4i8.f.v4f32.rtn.sat");
  __AIR_ASM__ char convert_char_sat_rtp(float a) __asm("air.convert.s.i8.f.f32.rtp.sat");
  __AIR_ASM__ char2 convert_char2_sat_rtp(float2 a) __asm("air.convert.s.v2i8.f.v2f32.rtp.sat");
  __AIR_ASM__ char3 convert_char3_sat_rtp(float3 a) __asm("air.convert.s.v3i8.f.v3f32.rtp.sat");
  __AIR_ASM__ char4 convert_char4_sat_rtp(float4 a) __asm("air.convert.s.v4i8.f.v4f32.rtp.sat");
  __AIR_ASM__ char convert_char_sat_rte(float a) __asm("air.convert.s.i8.f.f32.rte.sat");
  __AIR_ASM__ char2 convert_char2_sat_rte(float2 a) __asm("air.convert.s.v2i8.f.v2f32.rte.sat");
  __AIR_ASM__ char3 convert_char3_sat_rte(float3 a) __asm("air.convert.s.v3i8.f.v3f32.rte.sat");
  __AIR_ASM__ char4 convert_char4_sat_rte(float4 a) __asm("air.convert.s.v4i8.f.v4f32.rte.sat");
  __AIR_ASM__ char convert_char_sat(float a) __asm("air.convert.s.i8.f.f32.sat");
  __AIR_ASM__ char2 convert_char2_sat(float2 a) __asm("air.convert.s.v2i8.f.v2f32.sat");
  __AIR_ASM__ char3 convert_char3_sat(float3 a) __asm("air.convert.s.v3i8.f.v3f32.sat");
  __AIR_ASM__ char4 convert_char4_sat(float4 a) __asm("air.convert.s.v4i8.f.v4f32.sat");
  __AIR_ASM__ char convert_char_rtz(float a) __asm("air.convert.s.i8.f.f32.rtz");
  __AIR_ASM__ char2 convert_char2_rtz(float2 a) __asm("air.convert.s.v2i8.f.v2f32.rtz");
  __AIR_ASM__ char3 convert_char3_rtz(float3 a) __asm("air.convert.s.v3i8.f.v3f32.rtz");
  __AIR_ASM__ char4 convert_char4_rtz(float4 a) __asm("air.convert.s.v4i8.f.v4f32.rtz");
  __AIR_ASM__ char convert_char_rtn(float a) __asm("air.convert.s.i8.f.f32.rtn");
  __AIR_ASM__ char2 convert_char2_rtn(float2 a) __asm("air.convert.s.v2i8.f.v2f32.rtn");
  __AIR_ASM__ char3 convert_char3_rtn(float3 a) __asm("air.convert.s.v3i8.f.v3f32.rtn");
  __AIR_ASM__ char4 convert_char4_rtn(float4 a) __asm("air.convert.s.v4i8.f.v4f32.rtn");
  __AIR_ASM__ char convert_char_rtp(float a) __asm("air.convert.s.i8.f.f32.rtp");
  __AIR_ASM__ char2 convert_char2_rtp(float2 a) __asm("air.convert.s.v2i8.f.v2f32.rtp");
  __AIR_ASM__ char3 convert_char3_rtp(float3 a) __asm("air.convert.s.v3i8.f.v3f32.rtp");
  __AIR_ASM__ char4 convert_char4_rtp(float4 a) __asm("air.convert.s.v4i8.f.v4f32.rtp");
  __AIR_ASM__ char convert_char_rte(float a) __asm("air.convert.s.i8.f.f32.rte");
  __AIR_ASM__ char2 convert_char2_rte(float2 a) __asm("air.convert.s.v2i8.f.v2f32.rte");
  __AIR_ASM__ char3 convert_char3_rte(float3 a) __asm("air.convert.s.v3i8.f.v3f32.rte");
  __AIR_ASM__ char4 convert_char4_rte(float4 a) __asm("air.convert.s.v4i8.f.v4f32.rte");
  __AIR_ASM__ char convert_char(float a) __asm("air.convert.s.i8.f.f32");
  __AIR_ASM__ char2 convert_char2(float2 a) __asm("air.convert.s.v2i8.f.v2f32");
  __AIR_ASM__ char3 convert_char3(float3 a) __asm("air.convert.s.v3i8.f.v3f32");
  __AIR_ASM__ char4 convert_char4(float4 a) __asm("air.convert.s.v4i8.f.v4f32");
  __AIR_ASM__ uchar convert_uchar_sat(char a) __asm("air.convert.u.i8.s.i8.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(char2 a) __asm("air.convert.u.v2i8.s.v2i8.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(char3 a) __asm("air.convert.u.v3i8.s.v3i8.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(char4 a) __asm("air.convert.u.v4i8.s.v4i8.sat");
  __AIR_ASM__ uchar convert_uchar(char a) __asm("air.convert.u.i8.s.i8");
  __AIR_ASM__ uchar2 convert_uchar2(char2 a) __asm("air.convert.u.v2i8.s.v2i8");
  __AIR_ASM__ uchar3 convert_uchar3(char3 a) __asm("air.convert.u.v3i8.s.v3i8");
  __AIR_ASM__ uchar4 convert_uchar4(char4 a) __asm("air.convert.u.v4i8.s.v4i8");
  __AIR_ASM__ uchar convert_uchar_sat(uchar a) __asm("air.convert.u.i8.u.i8.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(uchar2 a) __asm("air.convert.u.v2i8.u.v2i8.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(uchar3 a) __asm("air.convert.u.v3i8.u.v3i8.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(uchar4 a) __asm("air.convert.u.v4i8.u.v4i8.sat");
  __AIR_ASM__ uchar convert_uchar(uchar a) __asm("air.convert.u.i8.u.i8");
  __AIR_ASM__ uchar2 convert_uchar2(uchar2 a) __asm("air.convert.u.v2i8.u.v2i8");
  __AIR_ASM__ uchar3 convert_uchar3(uchar3 a) __asm("air.convert.u.v3i8.u.v3i8");
  __AIR_ASM__ uchar4 convert_uchar4(uchar4 a) __asm("air.convert.u.v4i8.u.v4i8");
  __AIR_ASM__ uchar convert_uchar_sat(short a) __asm("air.convert.u.i8.s.i16.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(short2 a) __asm("air.convert.u.v2i8.s.v2i16.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(short3 a) __asm("air.convert.u.v3i8.s.v3i16.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(short4 a) __asm("air.convert.u.v4i8.s.v4i16.sat");
  __AIR_ASM__ uchar convert_uchar(short a) __asm("air.convert.u.i8.s.i16");
  __AIR_ASM__ uchar2 convert_uchar2(short2 a) __asm("air.convert.u.v2i8.s.v2i16");
  __AIR_ASM__ uchar3 convert_uchar3(short3 a) __asm("air.convert.u.v3i8.s.v3i16");
  __AIR_ASM__ uchar4 convert_uchar4(short4 a) __asm("air.convert.u.v4i8.s.v4i16");
  __AIR_ASM__ uchar convert_uchar_sat(ushort a) __asm("air.convert.u.i8.u.i16.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(ushort2 a) __asm("air.convert.u.v2i8.u.v2i16.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(ushort3 a) __asm("air.convert.u.v3i8.u.v3i16.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(ushort4 a) __asm("air.convert.u.v4i8.u.v4i16.sat");
  __AIR_ASM__ uchar convert_uchar(ushort a) __asm("air.convert.u.i8.u.i16");
  __AIR_ASM__ uchar2 convert_uchar2(ushort2 a) __asm("air.convert.u.v2i8.u.v2i16");
  __AIR_ASM__ uchar3 convert_uchar3(ushort3 a) __asm("air.convert.u.v3i8.u.v3i16");
  __AIR_ASM__ uchar4 convert_uchar4(ushort4 a) __asm("air.convert.u.v4i8.u.v4i16");
  __AIR_ASM__ uchar convert_uchar_sat(int a) __asm("air.convert.u.i8.s.i32.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(int2 a) __asm("air.convert.u.v2i8.s.v2i32.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(int3 a) __asm("air.convert.u.v3i8.s.v3i32.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(int4 a) __asm("air.convert.u.v4i8.s.v4i32.sat");
  __AIR_ASM__ uchar convert_uchar(int a) __asm("air.convert.u.i8.s.i32");
  __AIR_ASM__ uchar2 convert_uchar2(int2 a) __asm("air.convert.u.v2i8.s.v2i32");
  __AIR_ASM__ uchar3 convert_uchar3(int3 a) __asm("air.convert.u.v3i8.s.v3i32");
  __AIR_ASM__ uchar4 convert_uchar4(int4 a) __asm("air.convert.u.v4i8.s.v4i32");
  __AIR_ASM__ uchar convert_uchar_sat(uint a) __asm("air.convert.u.i8.u.i32.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(uint2 a) __asm("air.convert.u.v2i8.u.v2i32.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(uint3 a) __asm("air.convert.u.v3i8.u.v3i32.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(uint4 a) __asm("air.convert.u.v4i8.u.v4i32.sat");
  __AIR_ASM__ uchar convert_uchar(uint a) __asm("air.convert.u.i8.u.i32");
  __AIR_ASM__ uchar2 convert_uchar2(uint2 a) __asm("air.convert.u.v2i8.u.v2i32");
  __AIR_ASM__ uchar3 convert_uchar3(uint3 a) __asm("air.convert.u.v3i8.u.v3i32");
  __AIR_ASM__ uchar4 convert_uchar4(uint4 a) __asm("air.convert.u.v4i8.u.v4i32");
  __AIR_ASM__ uchar convert_uchar_sat(long a) __asm("air.convert.u.i8.s.i64.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(long2 a) __asm("air.convert.u.v2i8.s.v2i64.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(long3 a) __asm("air.convert.u.v3i8.s.v3i64.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(long4 a) __asm("air.convert.u.v4i8.s.v4i64.sat");
  __AIR_ASM__ uchar convert_uchar(long a) __asm("air.convert.u.i8.s.i64");
  __AIR_ASM__ uchar2 convert_uchar2(long2 a) __asm("air.convert.u.v2i8.s.v2i64");
  __AIR_ASM__ uchar3 convert_uchar3(long3 a) __asm("air.convert.u.v3i8.s.v3i64");
  __AIR_ASM__ uchar4 convert_uchar4(long4 a) __asm("air.convert.u.v4i8.s.v4i64");
  __AIR_ASM__ uchar convert_uchar_sat(ulong a) __asm("air.convert.u.i8.u.i64.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(ulong2 a) __asm("air.convert.u.v2i8.u.v2i64.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(ulong3 a) __asm("air.convert.u.v3i8.u.v3i64.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(ulong4 a) __asm("air.convert.u.v4i8.u.v4i64.sat");
  __AIR_ASM__ uchar convert_uchar(ulong a) __asm("air.convert.u.i8.u.i64");
  __AIR_ASM__ uchar2 convert_uchar2(ulong2 a) __asm("air.convert.u.v2i8.u.v2i64");
  __AIR_ASM__ uchar3 convert_uchar3(ulong3 a) __asm("air.convert.u.v3i8.u.v3i64");
  __AIR_ASM__ uchar4 convert_uchar4(ulong4 a) __asm("air.convert.u.v4i8.u.v4i64");
  __AIR_ASM__ uchar convert_uchar_sat_rtz(float a) __asm("air.convert.u.i8.f.f32.rtz.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat_rtz(float2 a) __asm("air.convert.u.v2i8.f.v2f32.rtz.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat_rtz(float3 a) __asm("air.convert.u.v3i8.f.v3f32.rtz.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat_rtz(float4 a) __asm("air.convert.u.v4i8.f.v4f32.rtz.sat");
  __AIR_ASM__ uchar convert_uchar_sat_rtn(float a) __asm("air.convert.u.i8.f.f32.rtn.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat_rtn(float2 a) __asm("air.convert.u.v2i8.f.v2f32.rtn.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat_rtn(float3 a) __asm("air.convert.u.v3i8.f.v3f32.rtn.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat_rtn(float4 a) __asm("air.convert.u.v4i8.f.v4f32.rtn.sat");
  __AIR_ASM__ uchar convert_uchar_sat_rtp(float a) __asm("air.convert.u.i8.f.f32.rtp.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat_rtp(float2 a) __asm("air.convert.u.v2i8.f.v2f32.rtp.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat_rtp(float3 a) __asm("air.convert.u.v3i8.f.v3f32.rtp.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat_rtp(float4 a) __asm("air.convert.u.v4i8.f.v4f32.rtp.sat");
  __AIR_ASM__ uchar convert_uchar_sat_rte(float a) __asm("air.convert.u.i8.f.f32.rte.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat_rte(float2 a) __asm("air.convert.u.v2i8.f.v2f32.rte.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat_rte(float3 a) __asm("air.convert.u.v3i8.f.v3f32.rte.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat_rte(float4 a) __asm("air.convert.u.v4i8.f.v4f32.rte.sat");
  __AIR_ASM__ uchar convert_uchar_sat(float a) __asm("air.convert.u.i8.f.f32.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(float2 a) __asm("air.convert.u.v2i8.f.v2f32.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(float3 a) __asm("air.convert.u.v3i8.f.v3f32.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(float4 a) __asm("air.convert.u.v4i8.f.v4f32.sat");
  __AIR_ASM__ uchar convert_uchar_rtz(float a) __asm("air.convert.u.i8.f.f32.rtz");
  __AIR_ASM__ uchar2 convert_uchar2_rtz(float2 a) __asm("air.convert.u.v2i8.f.v2f32.rtz");
  __AIR_ASM__ uchar3 convert_uchar3_rtz(float3 a) __asm("air.convert.u.v3i8.f.v3f32.rtz");
  __AIR_ASM__ uchar4 convert_uchar4_rtz(float4 a) __asm("air.convert.u.v4i8.f.v4f32.rtz");
  __AIR_ASM__ uchar convert_uchar_rtn(float a) __asm("air.convert.u.i8.f.f32.rtn");
  __AIR_ASM__ uchar2 convert_uchar2_rtn(float2 a) __asm("air.convert.u.v2i8.f.v2f32.rtn");
  __AIR_ASM__ uchar3 convert_uchar3_rtn(float3 a) __asm("air.convert.u.v3i8.f.v3f32.rtn");
  __AIR_ASM__ uchar4 convert_uchar4_rtn(float4 a) __asm("air.convert.u.v4i8.f.v4f32.rtn");
  __AIR_ASM__ uchar convert_uchar_rtp(float a) __asm("air.convert.u.i8.f.f32.rtp");
  __AIR_ASM__ uchar2 convert_uchar2_rtp(float2 a) __asm("air.convert.u.v2i8.f.v2f32.rtp");
  __AIR_ASM__ uchar3 convert_uchar3_rtp(float3 a) __asm("air.convert.u.v3i8.f.v3f32.rtp");
  __AIR_ASM__ uchar4 convert_uchar4_rtp(float4 a) __asm("air.convert.u.v4i8.f.v4f32.rtp");
  __AIR_ASM__ uchar convert_uchar_rte(float a) __asm("air.convert.u.i8.f.f32.rte");
  __AIR_ASM__ uchar2 convert_uchar2_rte(float2 a) __asm("air.convert.u.v2i8.f.v2f32.rte");
  __AIR_ASM__ uchar3 convert_uchar3_rte(float3 a) __asm("air.convert.u.v3i8.f.v3f32.rte");
  __AIR_ASM__ uchar4 convert_uchar4_rte(float4 a) __asm("air.convert.u.v4i8.f.v4f32.rte");
  __AIR_ASM__ uchar convert_uchar(float a) __asm("air.convert.u.i8.f.f32");
  __AIR_ASM__ uchar2 convert_uchar2(float2 a) __asm("air.convert.u.v2i8.f.v2f32");
  __AIR_ASM__ uchar3 convert_uchar3(float3 a) __asm("air.convert.u.v3i8.f.v3f32");
  __AIR_ASM__ uchar4 convert_uchar4(float4 a) __asm("air.convert.u.v4i8.f.v4f32");
  __AIR_ASM__ short convert_short_sat(char a) __asm("air.convert.s.i16.s.i8.sat");
  __AIR_ASM__ short2 convert_short2_sat(char2 a) __asm("air.convert.s.v2i16.s.v2i8.sat");
  __AIR_ASM__ short3 convert_short3_sat(char3 a) __asm("air.convert.s.v3i16.s.v3i8.sat");
  __AIR_ASM__ short4 convert_short4_sat(char4 a) __asm("air.convert.s.v4i16.s.v4i8.sat");
  __AIR_ASM__ short convert_short(char a) __asm("air.convert.s.i16.s.i8");
  __AIR_ASM__ short2 convert_short2(char2 a) __asm("air.convert.s.v2i16.s.v2i8");
  __AIR_ASM__ short3 convert_short3(char3 a) __asm("air.convert.s.v3i16.s.v3i8");
  __AIR_ASM__ short4 convert_short4(char4 a) __asm("air.convert.s.v4i16.s.v4i8");
  __AIR_ASM__ short convert_short_sat(uchar a) __asm("air.convert.s.i16.u.i8.sat");
  __AIR_ASM__ short2 convert_short2_sat(uchar2 a) __asm("air.convert.s.v2i16.u.v2i8.sat");
  __AIR_ASM__ short3 convert_short3_sat(uchar3 a) __asm("air.convert.s.v3i16.u.v3i8.sat");
  __AIR_ASM__ short4 convert_short4_sat(uchar4 a) __asm("air.convert.s.v4i16.u.v4i8.sat");
  __AIR_ASM__ short convert_short(uchar a) __asm("air.convert.s.i16.u.i8");
  __AIR_ASM__ short2 convert_short2(uchar2 a) __asm("air.convert.s.v2i16.u.v2i8");
  __AIR_ASM__ short3 convert_short3(uchar3 a) __asm("air.convert.s.v3i16.u.v3i8");
  __AIR_ASM__ short4 convert_short4(uchar4 a) __asm("air.convert.s.v4i16.u.v4i8");
  __AIR_ASM__ short convert_short_sat(short a) __asm("air.convert.s.i16.s.i16.sat");
  __AIR_ASM__ short2 convert_short2_sat(short2 a) __asm("air.convert.s.v2i16.s.v2i16.sat");
  __AIR_ASM__ short3 convert_short3_sat(short3 a) __asm("air.convert.s.v3i16.s.v3i16.sat");
  __AIR_ASM__ short4 convert_short4_sat(short4 a) __asm("air.convert.s.v4i16.s.v4i16.sat");
  __AIR_ASM__ short convert_short(short a) __asm("air.convert.s.i16.s.i16");
  __AIR_ASM__ short2 convert_short2(short2 a) __asm("air.convert.s.v2i16.s.v2i16");
  __AIR_ASM__ short3 convert_short3(short3 a) __asm("air.convert.s.v3i16.s.v3i16");
  __AIR_ASM__ short4 convert_short4(short4 a) __asm("air.convert.s.v4i16.s.v4i16");
  __AIR_ASM__ short convert_short_sat(ushort a) __asm("air.convert.s.i16.u.i16.sat");
  __AIR_ASM__ short2 convert_short2_sat(ushort2 a) __asm("air.convert.s.v2i16.u.v2i16.sat");
  __AIR_ASM__ short3 convert_short3_sat(ushort3 a) __asm("air.convert.s.v3i16.u.v3i16.sat");
  __AIR_ASM__ short4 convert_short4_sat(ushort4 a) __asm("air.convert.s.v4i16.u.v4i16.sat");
  __AIR_ASM__ short convert_short(ushort a) __asm("air.convert.s.i16.u.i16");
  __AIR_ASM__ short2 convert_short2(ushort2 a) __asm("air.convert.s.v2i16.u.v2i16");
  __AIR_ASM__ short3 convert_short3(ushort3 a) __asm("air.convert.s.v3i16.u.v3i16");
  __AIR_ASM__ short4 convert_short4(ushort4 a) __asm("air.convert.s.v4i16.u.v4i16");
  __AIR_ASM__ short convert_short_sat(int a) __asm("air.convert.s.i16.s.i32.sat");
  __AIR_ASM__ short2 convert_short2_sat(int2 a) __asm("air.convert.s.v2i16.s.v2i32.sat");
  __AIR_ASM__ short3 convert_short3_sat(int3 a) __asm("air.convert.s.v3i16.s.v3i32.sat");
  __AIR_ASM__ short4 convert_short4_sat(int4 a) __asm("air.convert.s.v4i16.s.v4i32.sat");
  __AIR_ASM__ short convert_short(int a) __asm("air.convert.s.i16.s.i32");
  __AIR_ASM__ short2 convert_short2(int2 a) __asm("air.convert.s.v2i16.s.v2i32");
  __AIR_ASM__ short3 convert_short3(int3 a) __asm("air.convert.s.v3i16.s.v3i32");
  __AIR_ASM__ short4 convert_short4(int4 a) __asm("air.convert.s.v4i16.s.v4i32");
  __AIR_ASM__ short convert_short_sat(uint a) __asm("air.convert.s.i16.u.i32.sat");
  __AIR_ASM__ short2 convert_short2_sat(uint2 a) __asm("air.convert.s.v2i16.u.v2i32.sat");
  __AIR_ASM__ short3 convert_short3_sat(uint3 a) __asm("air.convert.s.v3i16.u.v3i32.sat");
  __AIR_ASM__ short4 convert_short4_sat(uint4 a) __asm("air.convert.s.v4i16.u.v4i32.sat");
  __AIR_ASM__ short convert_short(uint a) __asm("air.convert.s.i16.u.i32");
  __AIR_ASM__ short2 convert_short2(uint2 a) __asm("air.convert.s.v2i16.u.v2i32");
  __AIR_ASM__ short3 convert_short3(uint3 a) __asm("air.convert.s.v3i16.u.v3i32");
  __AIR_ASM__ short4 convert_short4(uint4 a) __asm("air.convert.s.v4i16.u.v4i32");
  __AIR_ASM__ short convert_short_sat(long a) __asm("air.convert.s.i16.s.i64.sat");
  __AIR_ASM__ short2 convert_short2_sat(long2 a) __asm("air.convert.s.v2i16.s.v2i64.sat");
  __AIR_ASM__ short3 convert_short3_sat(long3 a) __asm("air.convert.s.v3i16.s.v3i64.sat");
  __AIR_ASM__ short4 convert_short4_sat(long4 a) __asm("air.convert.s.v4i16.s.v4i64.sat");
  __AIR_ASM__ short convert_short(long a) __asm("air.convert.s.i16.s.i64");
  __AIR_ASM__ short2 convert_short2(long2 a) __asm("air.convert.s.v2i16.s.v2i64");
  __AIR_ASM__ short3 convert_short3(long3 a) __asm("air.convert.s.v3i16.s.v3i64");
  __AIR_ASM__ short4 convert_short4(long4 a) __asm("air.convert.s.v4i16.s.v4i64");
  __AIR_ASM__ short convert_short_sat(ulong a) __asm("air.convert.s.i16.u.i64.sat");
  __AIR_ASM__ short2 convert_short2_sat(ulong2 a) __asm("air.convert.s.v2i16.u.v2i64.sat");
  __AIR_ASM__ short3 convert_short3_sat(ulong3 a) __asm("air.convert.s.v3i16.u.v3i64.sat");
  __AIR_ASM__ short4 convert_short4_sat(ulong4 a) __asm("air.convert.s.v4i16.u.v4i64.sat");
  __AIR_ASM__ short convert_short(ulong a) __asm("air.convert.s.i16.u.i64");
  __AIR_ASM__ short2 convert_short2(ulong2 a) __asm("air.convert.s.v2i16.u.v2i64");
  __AIR_ASM__ short3 convert_short3(ulong3 a) __asm("air.convert.s.v3i16.u.v3i64");
  __AIR_ASM__ short4 convert_short4(ulong4 a) __asm("air.convert.s.v4i16.u.v4i64");
  __AIR_ASM__ short convert_short_sat_rtz(float a) __asm("air.convert.s.i16.f.f32.rtz.sat");
  __AIR_ASM__ short2 convert_short2_sat_rtz(float2 a) __asm("air.convert.s.v2i16.f.v2f32.rtz.sat");
  __AIR_ASM__ short3 convert_short3_sat_rtz(float3 a) __asm("air.convert.s.v3i16.f.v3f32.rtz.sat");
  __AIR_ASM__ short4 convert_short4_sat_rtz(float4 a) __asm("air.convert.s.v4i16.f.v4f32.rtz.sat");
  __AIR_ASM__ short convert_short_sat_rtn(float a) __asm("air.convert.s.i16.f.f32.rtn.sat");
  __AIR_ASM__ short2 convert_short2_sat_rtn(float2 a) __asm("air.convert.s.v2i16.f.v2f32.rtn.sat");
  __AIR_ASM__ short3 convert_short3_sat_rtn(float3 a) __asm("air.convert.s.v3i16.f.v3f32.rtn.sat");
  __AIR_ASM__ short4 convert_short4_sat_rtn(float4 a) __asm("air.convert.s.v4i16.f.v4f32.rtn.sat");
  __AIR_ASM__ short convert_short_sat_rtp(float a) __asm("air.convert.s.i16.f.f32.rtp.sat");
  __AIR_ASM__ short2 convert_short2_sat_rtp(float2 a) __asm("air.convert.s.v2i16.f.v2f32.rtp.sat");
  __AIR_ASM__ short3 convert_short3_sat_rtp(float3 a) __asm("air.convert.s.v3i16.f.v3f32.rtp.sat");
  __AIR_ASM__ short4 convert_short4_sat_rtp(float4 a) __asm("air.convert.s.v4i16.f.v4f32.rtp.sat");
  __AIR_ASM__ short convert_short_sat_rte(float a) __asm("air.convert.s.i16.f.f32.rte.sat");
  __AIR_ASM__ short2 convert_short2_sat_rte(float2 a) __asm("air.convert.s.v2i16.f.v2f32.rte.sat");
  __AIR_ASM__ short3 convert_short3_sat_rte(float3 a) __asm("air.convert.s.v3i16.f.v3f32.rte.sat");
  __AIR_ASM__ short4 convert_short4_sat_rte(float4 a) __asm("air.convert.s.v4i16.f.v4f32.rte.sat");
  __AIR_ASM__ short convert_short_sat(float a) __asm("air.convert.s.i16.f.f32.sat");
  __AIR_ASM__ short2 convert_short2_sat(float2 a) __asm("air.convert.s.v2i16.f.v2f32.sat");
  __AIR_ASM__ short3 convert_short3_sat(float3 a) __asm("air.convert.s.v3i16.f.v3f32.sat");
  __AIR_ASM__ short4 convert_short4_sat(float4 a) __asm("air.convert.s.v4i16.f.v4f32.sat");
  __AIR_ASM__ short convert_short_rtz(float a) __asm("air.convert.s.i16.f.f32.rtz");
  __AIR_ASM__ short2 convert_short2_rtz(float2 a) __asm("air.convert.s.v2i16.f.v2f32.rtz");
  __AIR_ASM__ short3 convert_short3_rtz(float3 a) __asm("air.convert.s.v3i16.f.v3f32.rtz");
  __AIR_ASM__ short4 convert_short4_rtz(float4 a) __asm("air.convert.s.v4i16.f.v4f32.rtz");
  __AIR_ASM__ short convert_short_rtn(float a) __asm("air.convert.s.i16.f.f32.rtn");
  __AIR_ASM__ short2 convert_short2_rtn(float2 a) __asm("air.convert.s.v2i16.f.v2f32.rtn");
  __AIR_ASM__ short3 convert_short3_rtn(float3 a) __asm("air.convert.s.v3i16.f.v3f32.rtn");
  __AIR_ASM__ short4 convert_short4_rtn(float4 a) __asm("air.convert.s.v4i16.f.v4f32.rtn");
  __AIR_ASM__ short convert_short_rtp(float a) __asm("air.convert.s.i16.f.f32.rtp");
  __AIR_ASM__ short2 convert_short2_rtp(float2 a) __asm("air.convert.s.v2i16.f.v2f32.rtp");
  __AIR_ASM__ short3 convert_short3_rtp(float3 a) __asm("air.convert.s.v3i16.f.v3f32.rtp");
  __AIR_ASM__ short4 convert_short4_rtp(float4 a) __asm("air.convert.s.v4i16.f.v4f32.rtp");
  __AIR_ASM__ short convert_short_rte(float a) __asm("air.convert.s.i16.f.f32.rte");
  __AIR_ASM__ short2 convert_short2_rte(float2 a) __asm("air.convert.s.v2i16.f.v2f32.rte");
  __AIR_ASM__ short3 convert_short3_rte(float3 a) __asm("air.convert.s.v3i16.f.v3f32.rte");
  __AIR_ASM__ short4 convert_short4_rte(float4 a) __asm("air.convert.s.v4i16.f.v4f32.rte");
  __AIR_ASM__ short convert_short(float a) __asm("air.convert.s.i16.f.f32");
  __AIR_ASM__ short2 convert_short2(float2 a) __asm("air.convert.s.v2i16.f.v2f32");
  __AIR_ASM__ short3 convert_short3(float3 a) __asm("air.convert.s.v3i16.f.v3f32");
  __AIR_ASM__ short4 convert_short4(float4 a) __asm("air.convert.s.v4i16.f.v4f32");
  __AIR_ASM__ ushort convert_ushort_sat(char a) __asm("air.convert.u.i16.s.i8.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(char2 a) __asm("air.convert.u.v2i16.s.v2i8.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(char3 a) __asm("air.convert.u.v3i16.s.v3i8.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(char4 a) __asm("air.convert.u.v4i16.s.v4i8.sat");
  __AIR_ASM__ ushort convert_ushort(char a) __asm("air.convert.u.i16.s.i8");
  __AIR_ASM__ ushort2 convert_ushort2(char2 a) __asm("air.convert.u.v2i16.s.v2i8");
  __AIR_ASM__ ushort3 convert_ushort3(char3 a) __asm("air.convert.u.v3i16.s.v3i8");
  __AIR_ASM__ ushort4 convert_ushort4(char4 a) __asm("air.convert.u.v4i16.s.v4i8");
  __AIR_ASM__ ushort convert_ushort_sat(uchar a) __asm("air.convert.u.i16.u.i8.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(uchar2 a) __asm("air.convert.u.v2i16.u.v2i8.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(uchar3 a) __asm("air.convert.u.v3i16.u.v3i8.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(uchar4 a) __asm("air.convert.u.v4i16.u.v4i8.sat");
  __AIR_ASM__ ushort convert_ushort(uchar a) __asm("air.convert.u.i16.u.i8");
  __AIR_ASM__ ushort2 convert_ushort2(uchar2 a) __asm("air.convert.u.v2i16.u.v2i8");
  __AIR_ASM__ ushort3 convert_ushort3(uchar3 a) __asm("air.convert.u.v3i16.u.v3i8");
  __AIR_ASM__ ushort4 convert_ushort4(uchar4 a) __asm("air.convert.u.v4i16.u.v4i8");
  __AIR_ASM__ ushort convert_ushort_sat(short a) __asm("air.convert.u.i16.s.i16.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(short2 a) __asm("air.convert.u.v2i16.s.v2i16.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(short3 a) __asm("air.convert.u.v3i16.s.v3i16.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(short4 a) __asm("air.convert.u.v4i16.s.v4i16.sat");
  __AIR_ASM__ ushort convert_ushort(short a) __asm("air.convert.u.i16.s.i16");
  __AIR_ASM__ ushort2 convert_ushort2(short2 a) __asm("air.convert.u.v2i16.s.v2i16");
  __AIR_ASM__ ushort3 convert_ushort3(short3 a) __asm("air.convert.u.v3i16.s.v3i16");
  __AIR_ASM__ ushort4 convert_ushort4(short4 a) __asm("air.convert.u.v4i16.s.v4i16");
  __AIR_ASM__ ushort convert_ushort_sat(ushort a) __asm("air.convert.u.i16.u.i16.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(ushort2 a) __asm("air.convert.u.v2i16.u.v2i16.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(ushort3 a) __asm("air.convert.u.v3i16.u.v3i16.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(ushort4 a) __asm("air.convert.u.v4i16.u.v4i16.sat");
  __AIR_ASM__ ushort convert_ushort(ushort a) __asm("air.convert.u.i16.u.i16");
  __AIR_ASM__ ushort2 convert_ushort2(ushort2 a) __asm("air.convert.u.v2i16.u.v2i16");
  __AIR_ASM__ ushort3 convert_ushort3(ushort3 a) __asm("air.convert.u.v3i16.u.v3i16");
  __AIR_ASM__ ushort4 convert_ushort4(ushort4 a) __asm("air.convert.u.v4i16.u.v4i16");
  __AIR_ASM__ ushort convert_ushort_sat(int a) __asm("air.convert.u.i16.s.i32.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(int2 a) __asm("air.convert.u.v2i16.s.v2i32.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(int3 a) __asm("air.convert.u.v3i16.s.v3i32.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(int4 a) __asm("air.convert.u.v4i16.s.v4i32.sat");
  __AIR_ASM__ ushort convert_ushort(int a) __asm("air.convert.u.i16.s.i32");
  __AIR_ASM__ ushort2 convert_ushort2(int2 a) __asm("air.convert.u.v2i16.s.v2i32");
  __AIR_ASM__ ushort3 convert_ushort3(int3 a) __asm("air.convert.u.v3i16.s.v3i32");
  __AIR_ASM__ ushort4 convert_ushort4(int4 a) __asm("air.convert.u.v4i16.s.v4i32");
  __AIR_ASM__ ushort convert_ushort_sat(uint a) __asm("air.convert.u.i16.u.i32.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(uint2 a) __asm("air.convert.u.v2i16.u.v2i32.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(uint3 a) __asm("air.convert.u.v3i16.u.v3i32.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(uint4 a) __asm("air.convert.u.v4i16.u.v4i32.sat");
  __AIR_ASM__ ushort convert_ushort(uint a) __asm("air.convert.u.i16.u.i32");
  __AIR_ASM__ ushort2 convert_ushort2(uint2 a) __asm("air.convert.u.v2i16.u.v2i32");
  __AIR_ASM__ ushort3 convert_ushort3(uint3 a) __asm("air.convert.u.v3i16.u.v3i32");
  __AIR_ASM__ ushort4 convert_ushort4(uint4 a) __asm("air.convert.u.v4i16.u.v4i32");
  __AIR_ASM__ ushort convert_ushort_sat(long a) __asm("air.convert.u.i16.s.i64.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(long2 a) __asm("air.convert.u.v2i16.s.v2i64.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(long3 a) __asm("air.convert.u.v3i16.s.v3i64.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(long4 a) __asm("air.convert.u.v4i16.s.v4i64.sat");
  __AIR_ASM__ ushort convert_ushort(long a) __asm("air.convert.u.i16.s.i64");
  __AIR_ASM__ ushort2 convert_ushort2(long2 a) __asm("air.convert.u.v2i16.s.v2i64");
  __AIR_ASM__ ushort3 convert_ushort3(long3 a) __asm("air.convert.u.v3i16.s.v3i64");
  __AIR_ASM__ ushort4 convert_ushort4(long4 a) __asm("air.convert.u.v4i16.s.v4i64");
  __AIR_ASM__ ushort convert_ushort_sat(ulong a) __asm("air.convert.u.i16.u.i64.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(ulong2 a) __asm("air.convert.u.v2i16.u.v2i64.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(ulong3 a) __asm("air.convert.u.v3i16.u.v3i64.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(ulong4 a) __asm("air.convert.u.v4i16.u.v4i64.sat");
  __AIR_ASM__ ushort convert_ushort(ulong a) __asm("air.convert.u.i16.u.i64");
  __AIR_ASM__ ushort2 convert_ushort2(ulong2 a) __asm("air.convert.u.v2i16.u.v2i64");
  __AIR_ASM__ ushort3 convert_ushort3(ulong3 a) __asm("air.convert.u.v3i16.u.v3i64");
  __AIR_ASM__ ushort4 convert_ushort4(ulong4 a) __asm("air.convert.u.v4i16.u.v4i64");
  __AIR_ASM__ ushort convert_ushort_sat_rtz(float a) __asm("air.convert.u.i16.f.f32.rtz.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat_rtz(float2 a) __asm("air.convert.u.v2i16.f.v2f32.rtz.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat_rtz(float3 a) __asm("air.convert.u.v3i16.f.v3f32.rtz.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat_rtz(float4 a) __asm("air.convert.u.v4i16.f.v4f32.rtz.sat");
  __AIR_ASM__ ushort convert_ushort_sat_rtn(float a) __asm("air.convert.u.i16.f.f32.rtn.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat_rtn(float2 a) __asm("air.convert.u.v2i16.f.v2f32.rtn.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat_rtn(float3 a) __asm("air.convert.u.v3i16.f.v3f32.rtn.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat_rtn(float4 a) __asm("air.convert.u.v4i16.f.v4f32.rtn.sat");
  __AIR_ASM__ ushort convert_ushort_sat_rtp(float a) __asm("air.convert.u.i16.f.f32.rtp.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat_rtp(float2 a) __asm("air.convert.u.v2i16.f.v2f32.rtp.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat_rtp(float3 a) __asm("air.convert.u.v3i16.f.v3f32.rtp.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat_rtp(float4 a) __asm("air.convert.u.v4i16.f.v4f32.rtp.sat");
  __AIR_ASM__ ushort convert_ushort_sat_rte(float a) __asm("air.convert.u.i16.f.f32.rte.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat_rte(float2 a) __asm("air.convert.u.v2i16.f.v2f32.rte.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat_rte(float3 a) __asm("air.convert.u.v3i16.f.v3f32.rte.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat_rte(float4 a) __asm("air.convert.u.v4i16.f.v4f32.rte.sat");
  __AIR_ASM__ ushort convert_ushort_sat(float a) __asm("air.convert.u.i16.f.f32.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(float2 a) __asm("air.convert.u.v2i16.f.v2f32.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(float3 a) __asm("air.convert.u.v3i16.f.v3f32.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(float4 a) __asm("air.convert.u.v4i16.f.v4f32.sat");
  __AIR_ASM__ ushort convert_ushort_rtz(float a) __asm("air.convert.u.i16.f.f32.rtz");
  __AIR_ASM__ ushort2 convert_ushort2_rtz(float2 a) __asm("air.convert.u.v2i16.f.v2f32.rtz");
  __AIR_ASM__ ushort3 convert_ushort3_rtz(float3 a) __asm("air.convert.u.v3i16.f.v3f32.rtz");
  __AIR_ASM__ ushort4 convert_ushort4_rtz(float4 a) __asm("air.convert.u.v4i16.f.v4f32.rtz");
  __AIR_ASM__ ushort convert_ushort_rtn(float a) __asm("air.convert.u.i16.f.f32.rtn");
  __AIR_ASM__ ushort2 convert_ushort2_rtn(float2 a) __asm("air.convert.u.v2i16.f.v2f32.rtn");
  __AIR_ASM__ ushort3 convert_ushort3_rtn(float3 a) __asm("air.convert.u.v3i16.f.v3f32.rtn");
  __AIR_ASM__ ushort4 convert_ushort4_rtn(float4 a) __asm("air.convert.u.v4i16.f.v4f32.rtn");
  __AIR_ASM__ ushort convert_ushort_rtp(float a) __asm("air.convert.u.i16.f.f32.rtp");
  __AIR_ASM__ ushort2 convert_ushort2_rtp(float2 a) __asm("air.convert.u.v2i16.f.v2f32.rtp");
  __AIR_ASM__ ushort3 convert_ushort3_rtp(float3 a) __asm("air.convert.u.v3i16.f.v3f32.rtp");
  __AIR_ASM__ ushort4 convert_ushort4_rtp(float4 a) __asm("air.convert.u.v4i16.f.v4f32.rtp");
  __AIR_ASM__ ushort convert_ushort_rte(float a) __asm("air.convert.u.i16.f.f32.rte");
  __AIR_ASM__ ushort2 convert_ushort2_rte(float2 a) __asm("air.convert.u.v2i16.f.v2f32.rte");
  __AIR_ASM__ ushort3 convert_ushort3_rte(float3 a) __asm("air.convert.u.v3i16.f.v3f32.rte");
  __AIR_ASM__ ushort4 convert_ushort4_rte(float4 a) __asm("air.convert.u.v4i16.f.v4f32.rte");
  __AIR_ASM__ ushort convert_ushort(float a) __asm("air.convert.u.i16.f.f32");
  __AIR_ASM__ ushort2 convert_ushort2(float2 a) __asm("air.convert.u.v2i16.f.v2f32");
  __AIR_ASM__ ushort3 convert_ushort3(float3 a) __asm("air.convert.u.v3i16.f.v3f32");
  __AIR_ASM__ ushort4 convert_ushort4(float4 a) __asm("air.convert.u.v4i16.f.v4f32");
  __AIR_ASM__ int convert_int_sat(char a) __asm("air.convert.s.i32.s.i8.sat");
  __AIR_ASM__ int2 convert_int2_sat(char2 a) __asm("air.convert.s.v2i32.s.v2i8.sat");
  __AIR_ASM__ int3 convert_int3_sat(char3 a) __asm("air.convert.s.v3i32.s.v3i8.sat");
  __AIR_ASM__ int4 convert_int4_sat(char4 a) __asm("air.convert.s.v4i32.s.v4i8.sat");
  __AIR_ASM__ int convert_int(char a) __asm("air.convert.s.i32.s.i8");
  __AIR_ASM__ int2 convert_int2(char2 a) __asm("air.convert.s.v2i32.s.v2i8");
  __AIR_ASM__ int3 convert_int3(char3 a) __asm("air.convert.s.v3i32.s.v3i8");
  __AIR_ASM__ int4 convert_int4(char4 a) __asm("air.convert.s.v4i32.s.v4i8");
  __AIR_ASM__ int convert_int_sat(uchar a) __asm("air.convert.s.i32.u.i8.sat");
  __AIR_ASM__ int2 convert_int2_sat(uchar2 a) __asm("air.convert.s.v2i32.u.v2i8.sat");
  __AIR_ASM__ int3 convert_int3_sat(uchar3 a) __asm("air.convert.s.v3i32.u.v3i8.sat");
  __AIR_ASM__ int4 convert_int4_sat(uchar4 a) __asm("air.convert.s.v4i32.u.v4i8.sat");
  __AIR_ASM__ int convert_int(uchar a) __asm("air.convert.s.i32.u.i8");
  __AIR_ASM__ int2 convert_int2(uchar2 a) __asm("air.convert.s.v2i32.u.v2i8");
  __AIR_ASM__ int3 convert_int3(uchar3 a) __asm("air.convert.s.v3i32.u.v3i8");
  __AIR_ASM__ int4 convert_int4(uchar4 a) __asm("air.convert.s.v4i32.u.v4i8");
  __AIR_ASM__ int convert_int_sat(short a) __asm("air.convert.s.i32.s.i16.sat");
  __AIR_ASM__ int2 convert_int2_sat(short2 a) __asm("air.convert.s.v2i32.s.v2i16.sat");
  __AIR_ASM__ int3 convert_int3_sat(short3 a) __asm("air.convert.s.v3i32.s.v3i16.sat");
  __AIR_ASM__ int4 convert_int4_sat(short4 a) __asm("air.convert.s.v4i32.s.v4i16.sat");
  __AIR_ASM__ int convert_int(short a) __asm("air.convert.s.i32.s.i16");
  __AIR_ASM__ int2 convert_int2(short2 a) __asm("air.convert.s.v2i32.s.v2i16");
  __AIR_ASM__ int3 convert_int3(short3 a) __asm("air.convert.s.v3i32.s.v3i16");
  __AIR_ASM__ int4 convert_int4(short4 a) __asm("air.convert.s.v4i32.s.v4i16");
  __AIR_ASM__ int convert_int_sat(ushort a) __asm("air.convert.s.i32.u.i16.sat");
  __AIR_ASM__ int2 convert_int2_sat(ushort2 a) __asm("air.convert.s.v2i32.u.v2i16.sat");
  __AIR_ASM__ int3 convert_int3_sat(ushort3 a) __asm("air.convert.s.v3i32.u.v3i16.sat");
  __AIR_ASM__ int4 convert_int4_sat(ushort4 a) __asm("air.convert.s.v4i32.u.v4i16.sat");
  __AIR_ASM__ int convert_int(ushort a) __asm("air.convert.s.i32.u.i16");
  __AIR_ASM__ int2 convert_int2(ushort2 a) __asm("air.convert.s.v2i32.u.v2i16");
  __AIR_ASM__ int3 convert_int3(ushort3 a) __asm("air.convert.s.v3i32.u.v3i16");
  __AIR_ASM__ int4 convert_int4(ushort4 a) __asm("air.convert.s.v4i32.u.v4i16");
  __AIR_ASM__ int convert_int_sat(int a) __asm("air.convert.s.i32.s.i32.sat");
  __AIR_ASM__ int2 convert_int2_sat(int2 a) __asm("air.convert.s.v2i32.s.v2i32.sat");
  __AIR_ASM__ int3 convert_int3_sat(int3 a) __asm("air.convert.s.v3i32.s.v3i32.sat");
  __AIR_ASM__ int4 convert_int4_sat(int4 a) __asm("air.convert.s.v4i32.s.v4i32.sat");
  __AIR_ASM__ int convert_int(int a) __asm("air.convert.s.i32.s.i32");
  __AIR_ASM__ int2 convert_int2(int2 a) __asm("air.convert.s.v2i32.s.v2i32");
  __AIR_ASM__ int3 convert_int3(int3 a) __asm("air.convert.s.v3i32.s.v3i32");
  __AIR_ASM__ int4 convert_int4(int4 a) __asm("air.convert.s.v4i32.s.v4i32");
  __AIR_ASM__ int convert_int_sat(uint a) __asm("air.convert.s.i32.u.i32.sat");
  __AIR_ASM__ int2 convert_int2_sat(uint2 a) __asm("air.convert.s.v2i32.u.v2i32.sat");
  __AIR_ASM__ int3 convert_int3_sat(uint3 a) __asm("air.convert.s.v3i32.u.v3i32.sat");
  __AIR_ASM__ int4 convert_int4_sat(uint4 a) __asm("air.convert.s.v4i32.u.v4i32.sat");
  __AIR_ASM__ int convert_int(uint a) __asm("air.convert.s.i32.u.i32");
  __AIR_ASM__ int2 convert_int2(uint2 a) __asm("air.convert.s.v2i32.u.v2i32");
  __AIR_ASM__ int3 convert_int3(uint3 a) __asm("air.convert.s.v3i32.u.v3i32");
  __AIR_ASM__ int4 convert_int4(uint4 a) __asm("air.convert.s.v4i32.u.v4i32");
  __AIR_ASM__ int convert_int_sat(long a) __asm("air.convert.s.i32.s.i64.sat");
  __AIR_ASM__ int2 convert_int2_sat(long2 a) __asm("air.convert.s.v2i32.s.v2i64.sat");
  __AIR_ASM__ int3 convert_int3_sat(long3 a) __asm("air.convert.s.v3i32.s.v3i64.sat");
  __AIR_ASM__ int4 convert_int4_sat(long4 a) __asm("air.convert.s.v4i32.s.v4i64.sat");
  __AIR_ASM__ int convert_int(long a) __asm("air.convert.s.i32.s.i64");
  __AIR_ASM__ int2 convert_int2(long2 a) __asm("air.convert.s.v2i32.s.v2i64");
  __AIR_ASM__ int3 convert_int3(long3 a) __asm("air.convert.s.v3i32.s.v3i64");
  __AIR_ASM__ int4 convert_int4(long4 a) __asm("air.convert.s.v4i32.s.v4i64");
  __AIR_ASM__ int convert_int_sat(ulong a) __asm("air.convert.s.i32.u.i64.sat");
  __AIR_ASM__ int2 convert_int2_sat(ulong2 a) __asm("air.convert.s.v2i32.u.v2i64.sat");
  __AIR_ASM__ int3 convert_int3_sat(ulong3 a) __asm("air.convert.s.v3i32.u.v3i64.sat");
  __AIR_ASM__ int4 convert_int4_sat(ulong4 a) __asm("air.convert.s.v4i32.u.v4i64.sat");
  __AIR_ASM__ int convert_int(ulong a) __asm("air.convert.s.i32.u.i64");
  __AIR_ASM__ int2 convert_int2(ulong2 a) __asm("air.convert.s.v2i32.u.v2i64");
  __AIR_ASM__ int3 convert_int3(ulong3 a) __asm("air.convert.s.v3i32.u.v3i64");
  __AIR_ASM__ int4 convert_int4(ulong4 a) __asm("air.convert.s.v4i32.u.v4i64");
  __AIR_ASM__ int convert_int_sat_rtz(float a) __asm("air.convert.s.i32.f.f32.rtz.sat");
  __AIR_ASM__ int2 convert_int2_sat_rtz(float2 a) __asm("air.convert.s.v2i32.f.v2f32.rtz.sat");
  __AIR_ASM__ int3 convert_int3_sat_rtz(float3 a) __asm("air.convert.s.v3i32.f.v3f32.rtz.sat");
  __AIR_ASM__ int4 convert_int4_sat_rtz(float4 a) __asm("air.convert.s.v4i32.f.v4f32.rtz.sat");
  __AIR_ASM__ int convert_int_sat_rtn(float a) __asm("air.convert.s.i32.f.f32.rtn.sat");
  __AIR_ASM__ int2 convert_int2_sat_rtn(float2 a) __asm("air.convert.s.v2i32.f.v2f32.rtn.sat");
  __AIR_ASM__ int3 convert_int3_sat_rtn(float3 a) __asm("air.convert.s.v3i32.f.v3f32.rtn.sat");
  __AIR_ASM__ int4 convert_int4_sat_rtn(float4 a) __asm("air.convert.s.v4i32.f.v4f32.rtn.sat");
  __AIR_ASM__ int convert_int_sat_rtp(float a) __asm("air.convert.s.i32.f.f32.rtp.sat");
  __AIR_ASM__ int2 convert_int2_sat_rtp(float2 a) __asm("air.convert.s.v2i32.f.v2f32.rtp.sat");
  __AIR_ASM__ int3 convert_int3_sat_rtp(float3 a) __asm("air.convert.s.v3i32.f.v3f32.rtp.sat");
  __AIR_ASM__ int4 convert_int4_sat_rtp(float4 a) __asm("air.convert.s.v4i32.f.v4f32.rtp.sat");
  __AIR_ASM__ int convert_int_sat_rte(float a) __asm("air.convert.s.i32.f.f32.rte.sat");
  __AIR_ASM__ int2 convert_int2_sat_rte(float2 a) __asm("air.convert.s.v2i32.f.v2f32.rte.sat");
  __AIR_ASM__ int3 convert_int3_sat_rte(float3 a) __asm("air.convert.s.v3i32.f.v3f32.rte.sat");
  __AIR_ASM__ int4 convert_int4_sat_rte(float4 a) __asm("air.convert.s.v4i32.f.v4f32.rte.sat");
  __AIR_ASM__ int convert_int_sat(float a) __asm("air.convert.s.i32.f.f32.sat");
  __AIR_ASM__ int2 convert_int2_sat(float2 a) __asm("air.convert.s.v2i32.f.v2f32.sat");
  __AIR_ASM__ int3 convert_int3_sat(float3 a) __asm("air.convert.s.v3i32.f.v3f32.sat");
  __AIR_ASM__ int4 convert_int4_sat(float4 a) __asm("air.convert.s.v4i32.f.v4f32.sat");
  __AIR_ASM__ int convert_int_rtz(float a) __asm("air.convert.s.i32.f.f32.rtz");
  __AIR_ASM__ int2 convert_int2_rtz(float2 a) __asm("air.convert.s.v2i32.f.v2f32.rtz");
  __AIR_ASM__ int3 convert_int3_rtz(float3 a) __asm("air.convert.s.v3i32.f.v3f32.rtz");
  __AIR_ASM__ int4 convert_int4_rtz(float4 a) __asm("air.convert.s.v4i32.f.v4f32.rtz");
  __AIR_ASM__ int convert_int_rtn(float a) __asm("air.convert.s.i32.f.f32.rtn");
  __AIR_ASM__ int2 convert_int2_rtn(float2 a) __asm("air.convert.s.v2i32.f.v2f32.rtn");
  __AIR_ASM__ int3 convert_int3_rtn(float3 a) __asm("air.convert.s.v3i32.f.v3f32.rtn");
  __AIR_ASM__ int4 convert_int4_rtn(float4 a) __asm("air.convert.s.v4i32.f.v4f32.rtn");
  __AIR_ASM__ int convert_int_rtp(float a) __asm("air.convert.s.i32.f.f32.rtp");
  __AIR_ASM__ int2 convert_int2_rtp(float2 a) __asm("air.convert.s.v2i32.f.v2f32.rtp");
  __AIR_ASM__ int3 convert_int3_rtp(float3 a) __asm("air.convert.s.v3i32.f.v3f32.rtp");
  __AIR_ASM__ int4 convert_int4_rtp(float4 a) __asm("air.convert.s.v4i32.f.v4f32.rtp");
  __AIR_ASM__ int convert_int_rte(float a) __asm("air.convert.s.i32.f.f32.rte");
  __AIR_ASM__ int2 convert_int2_rte(float2 a) __asm("air.convert.s.v2i32.f.v2f32.rte");
  __AIR_ASM__ int3 convert_int3_rte(float3 a) __asm("air.convert.s.v3i32.f.v3f32.rte");
  __AIR_ASM__ int4 convert_int4_rte(float4 a) __asm("air.convert.s.v4i32.f.v4f32.rte");
  __AIR_ASM__ int convert_int(float a) __asm("air.convert.s.i32.f.f32");
  __AIR_ASM__ int2 convert_int2(float2 a) __asm("air.convert.s.v2i32.f.v2f32");
  __AIR_ASM__ int3 convert_int3(float3 a) __asm("air.convert.s.v3i32.f.v3f32");
  __AIR_ASM__ int4 convert_int4(float4 a) __asm("air.convert.s.v4i32.f.v4f32");
  __AIR_ASM__ uint convert_uint_sat(char a) __asm("air.convert.u.i32.s.i8.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(char2 a) __asm("air.convert.u.v2i32.s.v2i8.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(char3 a) __asm("air.convert.u.v3i32.s.v3i8.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(char4 a) __asm("air.convert.u.v4i32.s.v4i8.sat");
  __AIR_ASM__ uint convert_uint(char a) __asm("air.convert.u.i32.s.i8");
  __AIR_ASM__ uint2 convert_uint2(char2 a) __asm("air.convert.u.v2i32.s.v2i8");
  __AIR_ASM__ uint3 convert_uint3(char3 a) __asm("air.convert.u.v3i32.s.v3i8");
  __AIR_ASM__ uint4 convert_uint4(char4 a) __asm("air.convert.u.v4i32.s.v4i8");
  __AIR_ASM__ uint convert_uint_sat(uchar a) __asm("air.convert.u.i32.u.i8.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(uchar2 a) __asm("air.convert.u.v2i32.u.v2i8.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(uchar3 a) __asm("air.convert.u.v3i32.u.v3i8.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(uchar4 a) __asm("air.convert.u.v4i32.u.v4i8.sat");
  __AIR_ASM__ uint convert_uint(uchar a) __asm("air.convert.u.i32.u.i8");
  __AIR_ASM__ uint2 convert_uint2(uchar2 a) __asm("air.convert.u.v2i32.u.v2i8");
  __AIR_ASM__ uint3 convert_uint3(uchar3 a) __asm("air.convert.u.v3i32.u.v3i8");
  __AIR_ASM__ uint4 convert_uint4(uchar4 a) __asm("air.convert.u.v4i32.u.v4i8");
  __AIR_ASM__ uint convert_uint_sat(short a) __asm("air.convert.u.i32.s.i16.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(short2 a) __asm("air.convert.u.v2i32.s.v2i16.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(short3 a) __asm("air.convert.u.v3i32.s.v3i16.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(short4 a) __asm("air.convert.u.v4i32.s.v4i16.sat");
  __AIR_ASM__ uint convert_uint(short a) __asm("air.convert.u.i32.s.i16");
  __AIR_ASM__ uint2 convert_uint2(short2 a) __asm("air.convert.u.v2i32.s.v2i16");
  __AIR_ASM__ uint3 convert_uint3(short3 a) __asm("air.convert.u.v3i32.s.v3i16");
  __AIR_ASM__ uint4 convert_uint4(short4 a) __asm("air.convert.u.v4i32.s.v4i16");
  __AIR_ASM__ uint convert_uint_sat(ushort a) __asm("air.convert.u.i32.u.i16.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(ushort2 a) __asm("air.convert.u.v2i32.u.v2i16.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(ushort3 a) __asm("air.convert.u.v3i32.u.v3i16.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(ushort4 a) __asm("air.convert.u.v4i32.u.v4i16.sat");
  __AIR_ASM__ uint convert_uint(ushort a) __asm("air.convert.u.i32.u.i16");
  __AIR_ASM__ uint2 convert_uint2(ushort2 a) __asm("air.convert.u.v2i32.u.v2i16");
  __AIR_ASM__ uint3 convert_uint3(ushort3 a) __asm("air.convert.u.v3i32.u.v3i16");
  __AIR_ASM__ uint4 convert_uint4(ushort4 a) __asm("air.convert.u.v4i32.u.v4i16");
  __AIR_ASM__ uint convert_uint_sat(int a) __asm("air.convert.u.i32.s.i32.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(int2 a) __asm("air.convert.u.v2i32.s.v2i32.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(int3 a) __asm("air.convert.u.v3i32.s.v3i32.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(int4 a) __asm("air.convert.u.v4i32.s.v4i32.sat");
  __AIR_ASM__ uint convert_uint(int a) __asm("air.convert.u.i32.s.i32");
  __AIR_ASM__ uint2 convert_uint2(int2 a) __asm("air.convert.u.v2i32.s.v2i32");
  __AIR_ASM__ uint3 convert_uint3(int3 a) __asm("air.convert.u.v3i32.s.v3i32");
  __AIR_ASM__ uint4 convert_uint4(int4 a) __asm("air.convert.u.v4i32.s.v4i32");
  __AIR_ASM__ uint convert_uint_sat(uint a) __asm("air.convert.u.i32.u.i32.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(uint2 a) __asm("air.convert.u.v2i32.u.v2i32.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(uint3 a) __asm("air.convert.u.v3i32.u.v3i32.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(uint4 a) __asm("air.convert.u.v4i32.u.v4i32.sat");
  __AIR_ASM__ uint convert_uint(uint a) __asm("air.convert.u.i32.u.i32");
  __AIR_ASM__ uint2 convert_uint2(uint2 a) __asm("air.convert.u.v2i32.u.v2i32");
  __AIR_ASM__ uint3 convert_uint3(uint3 a) __asm("air.convert.u.v3i32.u.v3i32");
  __AIR_ASM__ uint4 convert_uint4(uint4 a) __asm("air.convert.u.v4i32.u.v4i32");
  __AIR_ASM__ uint convert_uint_sat(long a) __asm("air.convert.u.i32.s.i64.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(long2 a) __asm("air.convert.u.v2i32.s.v2i64.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(long3 a) __asm("air.convert.u.v3i32.s.v3i64.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(long4 a) __asm("air.convert.u.v4i32.s.v4i64.sat");
  __AIR_ASM__ uint convert_uint(long a) __asm("air.convert.u.i32.s.i64");
  __AIR_ASM__ uint2 convert_uint2(long2 a) __asm("air.convert.u.v2i32.s.v2i64");
  __AIR_ASM__ uint3 convert_uint3(long3 a) __asm("air.convert.u.v3i32.s.v3i64");
  __AIR_ASM__ uint4 convert_uint4(long4 a) __asm("air.convert.u.v4i32.s.v4i64");
  __AIR_ASM__ uint convert_uint_sat(ulong a) __asm("air.convert.u.i32.u.i64.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(ulong2 a) __asm("air.convert.u.v2i32.u.v2i64.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(ulong3 a) __asm("air.convert.u.v3i32.u.v3i64.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(ulong4 a) __asm("air.convert.u.v4i32.u.v4i64.sat");
  __AIR_ASM__ uint convert_uint(ulong a) __asm("air.convert.u.i32.u.i64");
  __AIR_ASM__ uint2 convert_uint2(ulong2 a) __asm("air.convert.u.v2i32.u.v2i64");
  __AIR_ASM__ uint3 convert_uint3(ulong3 a) __asm("air.convert.u.v3i32.u.v3i64");
  __AIR_ASM__ uint4 convert_uint4(ulong4 a) __asm("air.convert.u.v4i32.u.v4i64");
  __AIR_ASM__ uint convert_uint_sat_rtz(float a) __asm("air.convert.u.i32.f.f32.rtz.sat");
  __AIR_ASM__ uint2 convert_uint2_sat_rtz(float2 a) __asm("air.convert.u.v2i32.f.v2f32.rtz.sat");
  __AIR_ASM__ uint3 convert_uint3_sat_rtz(float3 a) __asm("air.convert.u.v3i32.f.v3f32.rtz.sat");
  __AIR_ASM__ uint4 convert_uint4_sat_rtz(float4 a) __asm("air.convert.u.v4i32.f.v4f32.rtz.sat");
  __AIR_ASM__ uint convert_uint_sat_rtn(float a) __asm("air.convert.u.i32.f.f32.rtn.sat");
  __AIR_ASM__ uint2 convert_uint2_sat_rtn(float2 a) __asm("air.convert.u.v2i32.f.v2f32.rtn.sat");
  __AIR_ASM__ uint3 convert_uint3_sat_rtn(float3 a) __asm("air.convert.u.v3i32.f.v3f32.rtn.sat");
  __AIR_ASM__ uint4 convert_uint4_sat_rtn(float4 a) __asm("air.convert.u.v4i32.f.v4f32.rtn.sat");
  __AIR_ASM__ uint convert_uint_sat_rtp(float a) __asm("air.convert.u.i32.f.f32.rtp.sat");
  __AIR_ASM__ uint2 convert_uint2_sat_rtp(float2 a) __asm("air.convert.u.v2i32.f.v2f32.rtp.sat");
  __AIR_ASM__ uint3 convert_uint3_sat_rtp(float3 a) __asm("air.convert.u.v3i32.f.v3f32.rtp.sat");
  __AIR_ASM__ uint4 convert_uint4_sat_rtp(float4 a) __asm("air.convert.u.v4i32.f.v4f32.rtp.sat");
  __AIR_ASM__ uint convert_uint_sat_rte(float a) __asm("air.convert.u.i32.f.f32.rte.sat");
  __AIR_ASM__ uint2 convert_uint2_sat_rte(float2 a) __asm("air.convert.u.v2i32.f.v2f32.rte.sat");
  __AIR_ASM__ uint3 convert_uint3_sat_rte(float3 a) __asm("air.convert.u.v3i32.f.v3f32.rte.sat");
  __AIR_ASM__ uint4 convert_uint4_sat_rte(float4 a) __asm("air.convert.u.v4i32.f.v4f32.rte.sat");
  __AIR_ASM__ uint convert_uint_sat(float a) __asm("air.convert.u.i32.f.f32.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(float2 a) __asm("air.convert.u.v2i32.f.v2f32.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(float3 a) __asm("air.convert.u.v3i32.f.v3f32.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(float4 a) __asm("air.convert.u.v4i32.f.v4f32.sat");
  __AIR_ASM__ uint convert_uint_rtz(float a) __asm("air.convert.u.i32.f.f32.rtz");
  __AIR_ASM__ uint2 convert_uint2_rtz(float2 a) __asm("air.convert.u.v2i32.f.v2f32.rtz");
  __AIR_ASM__ uint3 convert_uint3_rtz(float3 a) __asm("air.convert.u.v3i32.f.v3f32.rtz");
  __AIR_ASM__ uint4 convert_uint4_rtz(float4 a) __asm("air.convert.u.v4i32.f.v4f32.rtz");
  __AIR_ASM__ uint convert_uint_rtn(float a) __asm("air.convert.u.i32.f.f32.rtn");
  __AIR_ASM__ uint2 convert_uint2_rtn(float2 a) __asm("air.convert.u.v2i32.f.v2f32.rtn");
  __AIR_ASM__ uint3 convert_uint3_rtn(float3 a) __asm("air.convert.u.v3i32.f.v3f32.rtn");
  __AIR_ASM__ uint4 convert_uint4_rtn(float4 a) __asm("air.convert.u.v4i32.f.v4f32.rtn");
  __AIR_ASM__ uint convert_uint_rtp(float a) __asm("air.convert.u.i32.f.f32.rtp");
  __AIR_ASM__ uint2 convert_uint2_rtp(float2 a) __asm("air.convert.u.v2i32.f.v2f32.rtp");
  __AIR_ASM__ uint3 convert_uint3_rtp(float3 a) __asm("air.convert.u.v3i32.f.v3f32.rtp");
  __AIR_ASM__ uint4 convert_uint4_rtp(float4 a) __asm("air.convert.u.v4i32.f.v4f32.rtp");
  __AIR_ASM__ uint convert_uint_rte(float a) __asm("air.convert.u.i32.f.f32.rte");
  __AIR_ASM__ uint2 convert_uint2_rte(float2 a) __asm("air.convert.u.v2i32.f.v2f32.rte");
  __AIR_ASM__ uint3 convert_uint3_rte(float3 a) __asm("air.convert.u.v3i32.f.v3f32.rte");
  __AIR_ASM__ uint4 convert_uint4_rte(float4 a) __asm("air.convert.u.v4i32.f.v4f32.rte");
  __AIR_ASM__ uint convert_uint(float a) __asm("air.convert.u.i32.f.f32");
  __AIR_ASM__ uint2 convert_uint2(float2 a) __asm("air.convert.u.v2i32.f.v2f32");
  __AIR_ASM__ uint3 convert_uint3(float3 a) __asm("air.convert.u.v3i32.f.v3f32");
  __AIR_ASM__ uint4 convert_uint4(float4 a) __asm("air.convert.u.v4i32.f.v4f32");
  __AIR_ASM__ long convert_long_sat(char a) __asm("air.convert.s.i64.s.i8.sat");
  __AIR_ASM__ long2 convert_long2_sat(char2 a) __asm("air.convert.s.v2i64.s.v2i8.sat");
  __AIR_ASM__ long3 convert_long3_sat(char3 a) __asm("air.convert.s.v3i64.s.v3i8.sat");
  __AIR_ASM__ long4 convert_long4_sat(char4 a) __asm("air.convert.s.v4i64.s.v4i8.sat");
  __AIR_ASM__ long convert_long(char a) __asm("air.convert.s.i64.s.i8");
  __AIR_ASM__ long2 convert_long2(char2 a) __asm("air.convert.s.v2i64.s.v2i8");
  __AIR_ASM__ long3 convert_long3(char3 a) __asm("air.convert.s.v3i64.s.v3i8");
  __AIR_ASM__ long4 convert_long4(char4 a) __asm("air.convert.s.v4i64.s.v4i8");
  __AIR_ASM__ long convert_long_sat(uchar a) __asm("air.convert.s.i64.u.i8.sat");
  __AIR_ASM__ long2 convert_long2_sat(uchar2 a) __asm("air.convert.s.v2i64.u.v2i8.sat");
  __AIR_ASM__ long3 convert_long3_sat(uchar3 a) __asm("air.convert.s.v3i64.u.v3i8.sat");
  __AIR_ASM__ long4 convert_long4_sat(uchar4 a) __asm("air.convert.s.v4i64.u.v4i8.sat");
  __AIR_ASM__ long convert_long(uchar a) __asm("air.convert.s.i64.u.i8");
  __AIR_ASM__ long2 convert_long2(uchar2 a) __asm("air.convert.s.v2i64.u.v2i8");
  __AIR_ASM__ long3 convert_long3(uchar3 a) __asm("air.convert.s.v3i64.u.v3i8");
  __AIR_ASM__ long4 convert_long4(uchar4 a) __asm("air.convert.s.v4i64.u.v4i8");
  __AIR_ASM__ long convert_long_sat(short a) __asm("air.convert.s.i64.s.i16.sat");
  __AIR_ASM__ long2 convert_long2_sat(short2 a) __asm("air.convert.s.v2i64.s.v2i16.sat");
  __AIR_ASM__ long3 convert_long3_sat(short3 a) __asm("air.convert.s.v3i64.s.v3i16.sat");
  __AIR_ASM__ long4 convert_long4_sat(short4 a) __asm("air.convert.s.v4i64.s.v4i16.sat");
  __AIR_ASM__ long convert_long(short a) __asm("air.convert.s.i64.s.i16");
  __AIR_ASM__ long2 convert_long2(short2 a) __asm("air.convert.s.v2i64.s.v2i16");
  __AIR_ASM__ long3 convert_long3(short3 a) __asm("air.convert.s.v3i64.s.v3i16");
  __AIR_ASM__ long4 convert_long4(short4 a) __asm("air.convert.s.v4i64.s.v4i16");
  __AIR_ASM__ long convert_long_sat(ushort a) __asm("air.convert.s.i64.u.i16.sat");
  __AIR_ASM__ long2 convert_long2_sat(ushort2 a) __asm("air.convert.s.v2i64.u.v2i16.sat");
  __AIR_ASM__ long3 convert_long3_sat(ushort3 a) __asm("air.convert.s.v3i64.u.v3i16.sat");
  __AIR_ASM__ long4 convert_long4_sat(ushort4 a) __asm("air.convert.s.v4i64.u.v4i16.sat");
  __AIR_ASM__ long convert_long(ushort a) __asm("air.convert.s.i64.u.i16");
  __AIR_ASM__ long2 convert_long2(ushort2 a) __asm("air.convert.s.v2i64.u.v2i16");
  __AIR_ASM__ long3 convert_long3(ushort3 a) __asm("air.convert.s.v3i64.u.v3i16");
  __AIR_ASM__ long4 convert_long4(ushort4 a) __asm("air.convert.s.v4i64.u.v4i16");
  __AIR_ASM__ long convert_long_sat(int a) __asm("air.convert.s.i64.s.i32.sat");
  __AIR_ASM__ long2 convert_long2_sat(int2 a) __asm("air.convert.s.v2i64.s.v2i32.sat");
  __AIR_ASM__ long3 convert_long3_sat(int3 a) __asm("air.convert.s.v3i64.s.v3i32.sat");
  __AIR_ASM__ long4 convert_long4_sat(int4 a) __asm("air.convert.s.v4i64.s.v4i32.sat");
  __AIR_ASM__ long convert_long(int a) __asm("air.convert.s.i64.s.i32");
  __AIR_ASM__ long2 convert_long2(int2 a) __asm("air.convert.s.v2i64.s.v2i32");
  __AIR_ASM__ long3 convert_long3(int3 a) __asm("air.convert.s.v3i64.s.v3i32");
  __AIR_ASM__ long4 convert_long4(int4 a) __asm("air.convert.s.v4i64.s.v4i32");
  __AIR_ASM__ long convert_long_sat(uint a) __asm("air.convert.s.i64.u.i32.sat");
  __AIR_ASM__ long2 convert_long2_sat(uint2 a) __asm("air.convert.s.v2i64.u.v2i32.sat");
  __AIR_ASM__ long3 convert_long3_sat(uint3 a) __asm("air.convert.s.v3i64.u.v3i32.sat");
  __AIR_ASM__ long4 convert_long4_sat(uint4 a) __asm("air.convert.s.v4i64.u.v4i32.sat");
  __AIR_ASM__ long convert_long(uint a) __asm("air.convert.s.i64.u.i32");
  __AIR_ASM__ long2 convert_long2(uint2 a) __asm("air.convert.s.v2i64.u.v2i32");
  __AIR_ASM__ long3 convert_long3(uint3 a) __asm("air.convert.s.v3i64.u.v3i32");
  __AIR_ASM__ long4 convert_long4(uint4 a) __asm("air.convert.s.v4i64.u.v4i32");
  __AIR_ASM__ long convert_long_sat(long a) __asm("air.convert.s.i64.s.i64.sat");
  __AIR_ASM__ long2 convert_long2_sat(long2 a) __asm("air.convert.s.v2i64.s.v2i64.sat");
  __AIR_ASM__ long3 convert_long3_sat(long3 a) __asm("air.convert.s.v3i64.s.v3i64.sat");
  __AIR_ASM__ long4 convert_long4_sat(long4 a) __asm("air.convert.s.v4i64.s.v4i64.sat");
  __AIR_ASM__ long convert_long(long a) __asm("air.convert.s.i64.s.i64");
  __AIR_ASM__ long2 convert_long2(long2 a) __asm("air.convert.s.v2i64.s.v2i64");
  __AIR_ASM__ long3 convert_long3(long3 a) __asm("air.convert.s.v3i64.s.v3i64");
  __AIR_ASM__ long4 convert_long4(long4 a) __asm("air.convert.s.v4i64.s.v4i64");
  __AIR_ASM__ long convert_long_sat(ulong a) __asm("air.convert.s.i64.u.i64.sat");
  __AIR_ASM__ long2 convert_long2_sat(ulong2 a) __asm("air.convert.s.v2i64.u.v2i64.sat");
  __AIR_ASM__ long3 convert_long3_sat(ulong3 a) __asm("air.convert.s.v3i64.u.v3i64.sat");
  __AIR_ASM__ long4 convert_long4_sat(ulong4 a) __asm("air.convert.s.v4i64.u.v4i64.sat");
  __AIR_ASM__ long convert_long(ulong a) __asm("air.convert.s.i64.u.i64");
  __AIR_ASM__ long2 convert_long2(ulong2 a) __asm("air.convert.s.v2i64.u.v2i64");
  __AIR_ASM__ long3 convert_long3(ulong3 a) __asm("air.convert.s.v3i64.u.v3i64");
  __AIR_ASM__ long4 convert_long4(ulong4 a) __asm("air.convert.s.v4i64.u.v4i64");
  __AIR_ASM__ long convert_long_sat_rtz(float a) __asm("air.convert.s.i64.f.f32.rtz.sat");
  __AIR_ASM__ long2 convert_long2_sat_rtz(float2 a) __asm("air.convert.s.v2i64.f.v2f32.rtz.sat");
  __AIR_ASM__ long3 convert_long3_sat_rtz(float3 a) __asm("air.convert.s.v3i64.f.v3f32.rtz.sat");
  __AIR_ASM__ long4 convert_long4_sat_rtz(float4 a) __asm("air.convert.s.v4i64.f.v4f32.rtz.sat");
  __AIR_ASM__ long convert_long_sat_rtn(float a) __asm("air.convert.s.i64.f.f32.rtn.sat");
  __AIR_ASM__ long2 convert_long2_sat_rtn(float2 a) __asm("air.convert.s.v2i64.f.v2f32.rtn.sat");
  __AIR_ASM__ long3 convert_long3_sat_rtn(float3 a) __asm("air.convert.s.v3i64.f.v3f32.rtn.sat");
  __AIR_ASM__ long4 convert_long4_sat_rtn(float4 a) __asm("air.convert.s.v4i64.f.v4f32.rtn.sat");
  __AIR_ASM__ long convert_long_sat_rtp(float a) __asm("air.convert.s.i64.f.f32.rtp.sat");
  __AIR_ASM__ long2 convert_long2_sat_rtp(float2 a) __asm("air.convert.s.v2i64.f.v2f32.rtp.sat");
  __AIR_ASM__ long3 convert_long3_sat_rtp(float3 a) __asm("air.convert.s.v3i64.f.v3f32.rtp.sat");
  __AIR_ASM__ long4 convert_long4_sat_rtp(float4 a) __asm("air.convert.s.v4i64.f.v4f32.rtp.sat");
  __AIR_ASM__ long convert_long_sat_rte(float a) __asm("air.convert.s.i64.f.f32.rte.sat");
  __AIR_ASM__ long2 convert_long2_sat_rte(float2 a) __asm("air.convert.s.v2i64.f.v2f32.rte.sat");
  __AIR_ASM__ long3 convert_long3_sat_rte(float3 a) __asm("air.convert.s.v3i64.f.v3f32.rte.sat");
  __AIR_ASM__ long4 convert_long4_sat_rte(float4 a) __asm("air.convert.s.v4i64.f.v4f32.rte.sat");
  __AIR_ASM__ long convert_long_sat(float a) __asm("air.convert.s.i64.f.f32.sat");
  __AIR_ASM__ long2 convert_long2_sat(float2 a) __asm("air.convert.s.v2i64.f.v2f32.sat");
  __AIR_ASM__ long3 convert_long3_sat(float3 a) __asm("air.convert.s.v3i64.f.v3f32.sat");
  __AIR_ASM__ long4 convert_long4_sat(float4 a) __asm("air.convert.s.v4i64.f.v4f32.sat");
  __AIR_ASM__ long convert_long_rtz(float a) __asm("air.convert.s.i64.f.f32.rtz");
  __AIR_ASM__ long2 convert_long2_rtz(float2 a) __asm("air.convert.s.v2i64.f.v2f32.rtz");
  __AIR_ASM__ long3 convert_long3_rtz(float3 a) __asm("air.convert.s.v3i64.f.v3f32.rtz");
  __AIR_ASM__ long4 convert_long4_rtz(float4 a) __asm("air.convert.s.v4i64.f.v4f32.rtz");
  __AIR_ASM__ long convert_long_rtn(float a) __asm("air.convert.s.i64.f.f32.rtn");
  __AIR_ASM__ long2 convert_long2_rtn(float2 a) __asm("air.convert.s.v2i64.f.v2f32.rtn");
  __AIR_ASM__ long3 convert_long3_rtn(float3 a) __asm("air.convert.s.v3i64.f.v3f32.rtn");
  __AIR_ASM__ long4 convert_long4_rtn(float4 a) __asm("air.convert.s.v4i64.f.v4f32.rtn");
  __AIR_ASM__ long convert_long_rtp(float a) __asm("air.convert.s.i64.f.f32.rtp");
  __AIR_ASM__ long2 convert_long2_rtp(float2 a) __asm("air.convert.s.v2i64.f.v2f32.rtp");
  __AIR_ASM__ long3 convert_long3_rtp(float3 a) __asm("air.convert.s.v3i64.f.v3f32.rtp");
  __AIR_ASM__ long4 convert_long4_rtp(float4 a) __asm("air.convert.s.v4i64.f.v4f32.rtp");
  __AIR_ASM__ long convert_long_rte(float a) __asm("air.convert.s.i64.f.f32.rte");
  __AIR_ASM__ long2 convert_long2_rte(float2 a) __asm("air.convert.s.v2i64.f.v2f32.rte");
  __AIR_ASM__ long3 convert_long3_rte(float3 a) __asm("air.convert.s.v3i64.f.v3f32.rte");
  __AIR_ASM__ long4 convert_long4_rte(float4 a) __asm("air.convert.s.v4i64.f.v4f32.rte");
  __AIR_ASM__ long convert_long(float a) __asm("air.convert.s.i64.f.f32");
  __AIR_ASM__ long2 convert_long2(float2 a) __asm("air.convert.s.v2i64.f.v2f32");
  __AIR_ASM__ long3 convert_long3(float3 a) __asm("air.convert.s.v3i64.f.v3f32");
  __AIR_ASM__ long4 convert_long4(float4 a) __asm("air.convert.s.v4i64.f.v4f32");
  __AIR_ASM__ ulong convert_ulong_sat(char a) __asm("air.convert.u.i64.s.i8.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(char2 a) __asm("air.convert.u.v2i64.s.v2i8.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(char3 a) __asm("air.convert.u.v3i64.s.v3i8.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(char4 a) __asm("air.convert.u.v4i64.s.v4i8.sat");
  __AIR_ASM__ ulong convert_ulong(char a) __asm("air.convert.u.i64.s.i8");
  __AIR_ASM__ ulong2 convert_ulong2(char2 a) __asm("air.convert.u.v2i64.s.v2i8");
  __AIR_ASM__ ulong3 convert_ulong3(char3 a) __asm("air.convert.u.v3i64.s.v3i8");
  __AIR_ASM__ ulong4 convert_ulong4(char4 a) __asm("air.convert.u.v4i64.s.v4i8");
  __AIR_ASM__ ulong convert_ulong_sat(uchar a) __asm("air.convert.u.i64.u.i8.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(uchar2 a) __asm("air.convert.u.v2i64.u.v2i8.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(uchar3 a) __asm("air.convert.u.v3i64.u.v3i8.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(uchar4 a) __asm("air.convert.u.v4i64.u.v4i8.sat");
  __AIR_ASM__ ulong convert_ulong(uchar a) __asm("air.convert.u.i64.u.i8");
  __AIR_ASM__ ulong2 convert_ulong2(uchar2 a) __asm("air.convert.u.v2i64.u.v2i8");
  __AIR_ASM__ ulong3 convert_ulong3(uchar3 a) __asm("air.convert.u.v3i64.u.v3i8");
  __AIR_ASM__ ulong4 convert_ulong4(uchar4 a) __asm("air.convert.u.v4i64.u.v4i8");
  __AIR_ASM__ ulong convert_ulong_sat(short a) __asm("air.convert.u.i64.s.i16.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(short2 a) __asm("air.convert.u.v2i64.s.v2i16.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(short3 a) __asm("air.convert.u.v3i64.s.v3i16.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(short4 a) __asm("air.convert.u.v4i64.s.v4i16.sat");
  __AIR_ASM__ ulong convert_ulong(short a) __asm("air.convert.u.i64.s.i16");
  __AIR_ASM__ ulong2 convert_ulong2(short2 a) __asm("air.convert.u.v2i64.s.v2i16");
  __AIR_ASM__ ulong3 convert_ulong3(short3 a) __asm("air.convert.u.v3i64.s.v3i16");
  __AIR_ASM__ ulong4 convert_ulong4(short4 a) __asm("air.convert.u.v4i64.s.v4i16");
  __AIR_ASM__ ulong convert_ulong_sat(ushort a) __asm("air.convert.u.i64.u.i16.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(ushort2 a) __asm("air.convert.u.v2i64.u.v2i16.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(ushort3 a) __asm("air.convert.u.v3i64.u.v3i16.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(ushort4 a) __asm("air.convert.u.v4i64.u.v4i16.sat");
  __AIR_ASM__ ulong convert_ulong(ushort a) __asm("air.convert.u.i64.u.i16");
  __AIR_ASM__ ulong2 convert_ulong2(ushort2 a) __asm("air.convert.u.v2i64.u.v2i16");
  __AIR_ASM__ ulong3 convert_ulong3(ushort3 a) __asm("air.convert.u.v3i64.u.v3i16");
  __AIR_ASM__ ulong4 convert_ulong4(ushort4 a) __asm("air.convert.u.v4i64.u.v4i16");
  __AIR_ASM__ ulong convert_ulong_sat(int a) __asm("air.convert.u.i64.s.i32.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(int2 a) __asm("air.convert.u.v2i64.s.v2i32.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(int3 a) __asm("air.convert.u.v3i64.s.v3i32.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(int4 a) __asm("air.convert.u.v4i64.s.v4i32.sat");
  __AIR_ASM__ ulong convert_ulong(int a) __asm("air.convert.u.i64.s.i32");
  __AIR_ASM__ ulong2 convert_ulong2(int2 a) __asm("air.convert.u.v2i64.s.v2i32");
  __AIR_ASM__ ulong3 convert_ulong3(int3 a) __asm("air.convert.u.v3i64.s.v3i32");
  __AIR_ASM__ ulong4 convert_ulong4(int4 a) __asm("air.convert.u.v4i64.s.v4i32");
  __AIR_ASM__ ulong convert_ulong_sat(uint a) __asm("air.convert.u.i64.u.i32.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(uint2 a) __asm("air.convert.u.v2i64.u.v2i32.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(uint3 a) __asm("air.convert.u.v3i64.u.v3i32.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(uint4 a) __asm("air.convert.u.v4i64.u.v4i32.sat");
  __AIR_ASM__ ulong convert_ulong(uint a) __asm("air.convert.u.i64.u.i32");
  __AIR_ASM__ ulong2 convert_ulong2(uint2 a) __asm("air.convert.u.v2i64.u.v2i32");
  __AIR_ASM__ ulong3 convert_ulong3(uint3 a) __asm("air.convert.u.v3i64.u.v3i32");
  __AIR_ASM__ ulong4 convert_ulong4(uint4 a) __asm("air.convert.u.v4i64.u.v4i32");
  __AIR_ASM__ ulong convert_ulong_sat(long a) __asm("air.convert.u.i64.s.i64.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(long2 a) __asm("air.convert.u.v2i64.s.v2i64.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(long3 a) __asm("air.convert.u.v3i64.s.v3i64.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(long4 a) __asm("air.convert.u.v4i64.s.v4i64.sat");
  __AIR_ASM__ ulong convert_ulong(long a) __asm("air.convert.u.i64.s.i64");
  __AIR_ASM__ ulong2 convert_ulong2(long2 a) __asm("air.convert.u.v2i64.s.v2i64");
  __AIR_ASM__ ulong3 convert_ulong3(long3 a) __asm("air.convert.u.v3i64.s.v3i64");
  __AIR_ASM__ ulong4 convert_ulong4(long4 a) __asm("air.convert.u.v4i64.s.v4i64");
  __AIR_ASM__ ulong convert_ulong_sat(ulong a) __asm("air.convert.u.i64.u.i64.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(ulong2 a) __asm("air.convert.u.v2i64.u.v2i64.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(ulong3 a) __asm("air.convert.u.v3i64.u.v3i64.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(ulong4 a) __asm("air.convert.u.v4i64.u.v4i64.sat");
  __AIR_ASM__ ulong convert_ulong(ulong a) __asm("air.convert.u.i64.u.i64");
  __AIR_ASM__ ulong2 convert_ulong2(ulong2 a) __asm("air.convert.u.v2i64.u.v2i64");
  __AIR_ASM__ ulong3 convert_ulong3(ulong3 a) __asm("air.convert.u.v3i64.u.v3i64");
  __AIR_ASM__ ulong4 convert_ulong4(ulong4 a) __asm("air.convert.u.v4i64.u.v4i64");
  __AIR_ASM__ ulong convert_ulong_sat_rtz(float a) __asm("air.convert.u.i64.f.f32.rtz.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat_rtz(float2 a) __asm("air.convert.u.v2i64.f.v2f32.rtz.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat_rtz(float3 a) __asm("air.convert.u.v3i64.f.v3f32.rtz.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat_rtz(float4 a) __asm("air.convert.u.v4i64.f.v4f32.rtz.sat");
  __AIR_ASM__ ulong convert_ulong_sat_rtn(float a) __asm("air.convert.u.i64.f.f32.rtn.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat_rtn(float2 a) __asm("air.convert.u.v2i64.f.v2f32.rtn.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat_rtn(float3 a) __asm("air.convert.u.v3i64.f.v3f32.rtn.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat_rtn(float4 a) __asm("air.convert.u.v4i64.f.v4f32.rtn.sat");
  __AIR_ASM__ ulong convert_ulong_sat_rtp(float a) __asm("air.convert.u.i64.f.f32.rtp.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat_rtp(float2 a) __asm("air.convert.u.v2i64.f.v2f32.rtp.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat_rtp(float3 a) __asm("air.convert.u.v3i64.f.v3f32.rtp.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat_rtp(float4 a) __asm("air.convert.u.v4i64.f.v4f32.rtp.sat");
  __AIR_ASM__ ulong convert_ulong_sat_rte(float a) __asm("air.convert.u.i64.f.f32.rte.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat_rte(float2 a) __asm("air.convert.u.v2i64.f.v2f32.rte.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat_rte(float3 a) __asm("air.convert.u.v3i64.f.v3f32.rte.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat_rte(float4 a) __asm("air.convert.u.v4i64.f.v4f32.rte.sat");
  __AIR_ASM__ ulong convert_ulong_sat(float a) __asm("air.convert.u.i64.f.f32.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(float2 a) __asm("air.convert.u.v2i64.f.v2f32.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(float3 a) __asm("air.convert.u.v3i64.f.v3f32.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(float4 a) __asm("air.convert.u.v4i64.f.v4f32.sat");
  __AIR_ASM__ ulong convert_ulong_rtz(float a) __asm("air.convert.u.i64.f.f32.rtz");
  __AIR_ASM__ ulong2 convert_ulong2_rtz(float2 a) __asm("air.convert.u.v2i64.f.v2f32.rtz");
  __AIR_ASM__ ulong3 convert_ulong3_rtz(float3 a) __asm("air.convert.u.v3i64.f.v3f32.rtz");
  __AIR_ASM__ ulong4 convert_ulong4_rtz(float4 a) __asm("air.convert.u.v4i64.f.v4f32.rtz");
  __AIR_ASM__ ulong convert_ulong_rtn(float a) __asm("air.convert.u.i64.f.f32.rtn");
  __AIR_ASM__ ulong2 convert_ulong2_rtn(float2 a) __asm("air.convert.u.v2i64.f.v2f32.rtn");
  __AIR_ASM__ ulong3 convert_ulong3_rtn(float3 a) __asm("air.convert.u.v3i64.f.v3f32.rtn");
  __AIR_ASM__ ulong4 convert_ulong4_rtn(float4 a) __asm("air.convert.u.v4i64.f.v4f32.rtn");
  __AIR_ASM__ ulong convert_ulong_rtp(float a) __asm("air.convert.u.i64.f.f32.rtp");
  __AIR_ASM__ ulong2 convert_ulong2_rtp(float2 a) __asm("air.convert.u.v2i64.f.v2f32.rtp");
  __AIR_ASM__ ulong3 convert_ulong3_rtp(float3 a) __asm("air.convert.u.v3i64.f.v3f32.rtp");
  __AIR_ASM__ ulong4 convert_ulong4_rtp(float4 a) __asm("air.convert.u.v4i64.f.v4f32.rtp");
  __AIR_ASM__ ulong convert_ulong_rte(float a) __asm("air.convert.u.i64.f.f32.rte");
  __AIR_ASM__ ulong2 convert_ulong2_rte(float2 a) __asm("air.convert.u.v2i64.f.v2f32.rte");
  __AIR_ASM__ ulong3 convert_ulong3_rte(float3 a) __asm("air.convert.u.v3i64.f.v3f32.rte");
  __AIR_ASM__ ulong4 convert_ulong4_rte(float4 a) __asm("air.convert.u.v4i64.f.v4f32.rte");
  __AIR_ASM__ ulong convert_ulong(float a) __asm("air.convert.u.i64.f.f32");
  __AIR_ASM__ ulong2 convert_ulong2(float2 a) __asm("air.convert.u.v2i64.f.v2f32");
  __AIR_ASM__ ulong3 convert_ulong3(float3 a) __asm("air.convert.u.v3i64.f.v3f32");
  __AIR_ASM__ ulong4 convert_ulong4(float4 a) __asm("air.convert.u.v4i64.f.v4f32");
  __AIR_ASM__ float convert_float_rtz(char a) __asm("air.convert.f.f32.s.i8.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(char2 a) __asm("air.convert.f.v2f32.s.v2i8.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(char3 a) __asm("air.convert.f.v3f32.s.v3i8.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(char4 a) __asm("air.convert.f.v4f32.s.v4i8.rtz");
  __AIR_ASM__ float convert_float_rtn(char a) __asm("air.convert.f.f32.s.i8.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(char2 a) __asm("air.convert.f.v2f32.s.v2i8.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(char3 a) __asm("air.convert.f.v3f32.s.v3i8.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(char4 a) __asm("air.convert.f.v4f32.s.v4i8.rtn");
  __AIR_ASM__ float convert_float_rtp(char a) __asm("air.convert.f.f32.s.i8.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(char2 a) __asm("air.convert.f.v2f32.s.v2i8.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(char3 a) __asm("air.convert.f.v3f32.s.v3i8.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(char4 a) __asm("air.convert.f.v4f32.s.v4i8.rtp");
  __AIR_ASM__ float convert_float_rte(char a) __asm("air.convert.f.f32.s.i8.rte");
  __AIR_ASM__ float2 convert_float2_rte(char2 a) __asm("air.convert.f.v2f32.s.v2i8.rte");
  __AIR_ASM__ float3 convert_float3_rte(char3 a) __asm("air.convert.f.v3f32.s.v3i8.rte");
  __AIR_ASM__ float4 convert_float4_rte(char4 a) __asm("air.convert.f.v4f32.s.v4i8.rte");
  __AIR_ASM__ float convert_float(char a) __asm("air.convert.f.f32.s.i8");
  __AIR_ASM__ float2 convert_float2(char2 a) __asm("air.convert.f.v2f32.s.v2i8");
  __AIR_ASM__ float3 convert_float3(char3 a) __asm("air.convert.f.v3f32.s.v3i8");
  __AIR_ASM__ float4 convert_float4(char4 a) __asm("air.convert.f.v4f32.s.v4i8");
  __AIR_ASM__ float convert_float_rtz(uchar a) __asm("air.convert.f.f32.u.i8.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(uchar2 a) __asm("air.convert.f.v2f32.u.v2i8.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(uchar3 a) __asm("air.convert.f.v3f32.u.v3i8.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(uchar4 a) __asm("air.convert.f.v4f32.u.v4i8.rtz");
  __AIR_ASM__ float convert_float_rtn(uchar a) __asm("air.convert.f.f32.u.i8.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(uchar2 a) __asm("air.convert.f.v2f32.u.v2i8.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(uchar3 a) __asm("air.convert.f.v3f32.u.v3i8.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(uchar4 a) __asm("air.convert.f.v4f32.u.v4i8.rtn");
  __AIR_ASM__ float convert_float_rtp(uchar a) __asm("air.convert.f.f32.u.i8.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(uchar2 a) __asm("air.convert.f.v2f32.u.v2i8.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(uchar3 a) __asm("air.convert.f.v3f32.u.v3i8.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(uchar4 a) __asm("air.convert.f.v4f32.u.v4i8.rtp");
  __AIR_ASM__ float convert_float_rte(uchar a) __asm("air.convert.f.f32.u.i8.rte");
  __AIR_ASM__ float2 convert_float2_rte(uchar2 a) __asm("air.convert.f.v2f32.u.v2i8.rte");
  __AIR_ASM__ float3 convert_float3_rte(uchar3 a) __asm("air.convert.f.v3f32.u.v3i8.rte");
  __AIR_ASM__ float4 convert_float4_rte(uchar4 a) __asm("air.convert.f.v4f32.u.v4i8.rte");
  __AIR_ASM__ float convert_float(uchar a) __asm("air.convert.f.f32.u.i8");
  __AIR_ASM__ float2 convert_float2(uchar2 a) __asm("air.convert.f.v2f32.u.v2i8");
  __AIR_ASM__ float3 convert_float3(uchar3 a) __asm("air.convert.f.v3f32.u.v3i8");
  __AIR_ASM__ float4 convert_float4(uchar4 a) __asm("air.convert.f.v4f32.u.v4i8");
  __AIR_ASM__ float convert_float_rtz(short a) __asm("air.convert.f.f32.s.i16.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(short2 a) __asm("air.convert.f.v2f32.s.v2i16.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(short3 a) __asm("air.convert.f.v3f32.s.v3i16.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(short4 a) __asm("air.convert.f.v4f32.s.v4i16.rtz");
  __AIR_ASM__ float convert_float_rtn(short a) __asm("air.convert.f.f32.s.i16.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(short2 a) __asm("air.convert.f.v2f32.s.v2i16.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(short3 a) __asm("air.convert.f.v3f32.s.v3i16.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(short4 a) __asm("air.convert.f.v4f32.s.v4i16.rtn");
  __AIR_ASM__ float convert_float_rtp(short a) __asm("air.convert.f.f32.s.i16.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(short2 a) __asm("air.convert.f.v2f32.s.v2i16.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(short3 a) __asm("air.convert.f.v3f32.s.v3i16.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(short4 a) __asm("air.convert.f.v4f32.s.v4i16.rtp");
  __AIR_ASM__ float convert_float_rte(short a) __asm("air.convert.f.f32.s.i16.rte");
  __AIR_ASM__ float2 convert_float2_rte(short2 a) __asm("air.convert.f.v2f32.s.v2i16.rte");
  __AIR_ASM__ float3 convert_float3_rte(short3 a) __asm("air.convert.f.v3f32.s.v3i16.rte");
  __AIR_ASM__ float4 convert_float4_rte(short4 a) __asm("air.convert.f.v4f32.s.v4i16.rte");
  __AIR_ASM__ float convert_float(short a) __asm("air.convert.f.f32.s.i16");
  __AIR_ASM__ float2 convert_float2(short2 a) __asm("air.convert.f.v2f32.s.v2i16");
  __AIR_ASM__ float3 convert_float3(short3 a) __asm("air.convert.f.v3f32.s.v3i16");
  __AIR_ASM__ float4 convert_float4(short4 a) __asm("air.convert.f.v4f32.s.v4i16");
  __AIR_ASM__ float convert_float_rtz(ushort a) __asm("air.convert.f.f32.u.i16.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(ushort2 a) __asm("air.convert.f.v2f32.u.v2i16.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(ushort3 a) __asm("air.convert.f.v3f32.u.v3i16.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(ushort4 a) __asm("air.convert.f.v4f32.u.v4i16.rtz");
  __AIR_ASM__ float convert_float_rtn(ushort a) __asm("air.convert.f.f32.u.i16.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(ushort2 a) __asm("air.convert.f.v2f32.u.v2i16.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(ushort3 a) __asm("air.convert.f.v3f32.u.v3i16.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(ushort4 a) __asm("air.convert.f.v4f32.u.v4i16.rtn");
  __AIR_ASM__ float convert_float_rtp(ushort a) __asm("air.convert.f.f32.u.i16.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(ushort2 a) __asm("air.convert.f.v2f32.u.v2i16.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(ushort3 a) __asm("air.convert.f.v3f32.u.v3i16.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(ushort4 a) __asm("air.convert.f.v4f32.u.v4i16.rtp");
  __AIR_ASM__ float convert_float_rte(ushort a) __asm("air.convert.f.f32.u.i16.rte");
  __AIR_ASM__ float2 convert_float2_rte(ushort2 a) __asm("air.convert.f.v2f32.u.v2i16.rte");
  __AIR_ASM__ float3 convert_float3_rte(ushort3 a) __asm("air.convert.f.v3f32.u.v3i16.rte");
  __AIR_ASM__ float4 convert_float4_rte(ushort4 a) __asm("air.convert.f.v4f32.u.v4i16.rte");
  __AIR_ASM__ float convert_float(ushort a) __asm("air.convert.f.f32.u.i16");
  __AIR_ASM__ float2 convert_float2(ushort2 a) __asm("air.convert.f.v2f32.u.v2i16");
  __AIR_ASM__ float3 convert_float3(ushort3 a) __asm("air.convert.f.v3f32.u.v3i16");
  __AIR_ASM__ float4 convert_float4(ushort4 a) __asm("air.convert.f.v4f32.u.v4i16");
  __AIR_ASM__ float convert_float_rtz(int a) __asm("air.convert.f.f32.s.i32.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(int2 a) __asm("air.convert.f.v2f32.s.v2i32.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(int3 a) __asm("air.convert.f.v3f32.s.v3i32.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(int4 a) __asm("air.convert.f.v4f32.s.v4i32.rtz");
  __AIR_ASM__ float convert_float_rtn(int a) __asm("air.convert.f.f32.s.i32.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(int2 a) __asm("air.convert.f.v2f32.s.v2i32.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(int3 a) __asm("air.convert.f.v3f32.s.v3i32.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(int4 a) __asm("air.convert.f.v4f32.s.v4i32.rtn");
  __AIR_ASM__ float convert_float_rtp(int a) __asm("air.convert.f.f32.s.i32.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(int2 a) __asm("air.convert.f.v2f32.s.v2i32.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(int3 a) __asm("air.convert.f.v3f32.s.v3i32.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(int4 a) __asm("air.convert.f.v4f32.s.v4i32.rtp");
  __AIR_ASM__ float convert_float_rte(int a) __asm("air.convert.f.f32.s.i32.rte");
  __AIR_ASM__ float2 convert_float2_rte(int2 a) __asm("air.convert.f.v2f32.s.v2i32.rte");
  __AIR_ASM__ float3 convert_float3_rte(int3 a) __asm("air.convert.f.v3f32.s.v3i32.rte");
  __AIR_ASM__ float4 convert_float4_rte(int4 a) __asm("air.convert.f.v4f32.s.v4i32.rte");
  __AIR_ASM__ float convert_float(int a) __asm("air.convert.f.f32.s.i32");
  __AIR_ASM__ float2 convert_float2(int2 a) __asm("air.convert.f.v2f32.s.v2i32");
  __AIR_ASM__ float3 convert_float3(int3 a) __asm("air.convert.f.v3f32.s.v3i32");
  __AIR_ASM__ float4 convert_float4(int4 a) __asm("air.convert.f.v4f32.s.v4i32");
  __AIR_ASM__ float convert_float_rtz(uint a) __asm("air.convert.f.f32.u.i32.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(uint2 a) __asm("air.convert.f.v2f32.u.v2i32.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(uint3 a) __asm("air.convert.f.v3f32.u.v3i32.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(uint4 a) __asm("air.convert.f.v4f32.u.v4i32.rtz");
  __AIR_ASM__ float convert_float_rtn(uint a) __asm("air.convert.f.f32.u.i32.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(uint2 a) __asm("air.convert.f.v2f32.u.v2i32.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(uint3 a) __asm("air.convert.f.v3f32.u.v3i32.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(uint4 a) __asm("air.convert.f.v4f32.u.v4i32.rtn");
  __AIR_ASM__ float convert_float_rtp(uint a) __asm("air.convert.f.f32.u.i32.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(uint2 a) __asm("air.convert.f.v2f32.u.v2i32.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(uint3 a) __asm("air.convert.f.v3f32.u.v3i32.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(uint4 a) __asm("air.convert.f.v4f32.u.v4i32.rtp");
  __AIR_ASM__ float convert_float_rte(uint a) __asm("air.convert.f.f32.u.i32.rte");
  __AIR_ASM__ float2 convert_float2_rte(uint2 a) __asm("air.convert.f.v2f32.u.v2i32.rte");
  __AIR_ASM__ float3 convert_float3_rte(uint3 a) __asm("air.convert.f.v3f32.u.v3i32.rte");
  __AIR_ASM__ float4 convert_float4_rte(uint4 a) __asm("air.convert.f.v4f32.u.v4i32.rte");
  __AIR_ASM__ float convert_float(uint a) __asm("air.convert.f.f32.u.i32");
  __AIR_ASM__ float2 convert_float2(uint2 a) __asm("air.convert.f.v2f32.u.v2i32");
  __AIR_ASM__ float3 convert_float3(uint3 a) __asm("air.convert.f.v3f32.u.v3i32");
  __AIR_ASM__ float4 convert_float4(uint4 a) __asm("air.convert.f.v4f32.u.v4i32");
  __AIR_ASM__ float convert_float_rtz(long a) __asm("air.convert.f.f32.s.i64.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(long2 a) __asm("air.convert.f.v2f32.s.v2i64.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(long3 a) __asm("air.convert.f.v3f32.s.v3i64.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(long4 a) __asm("air.convert.f.v4f32.s.v4i64.rtz");
  __AIR_ASM__ float convert_float_rtn(long a) __asm("air.convert.f.f32.s.i64.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(long2 a) __asm("air.convert.f.v2f32.s.v2i64.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(long3 a) __asm("air.convert.f.v3f32.s.v3i64.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(long4 a) __asm("air.convert.f.v4f32.s.v4i64.rtn");
  __AIR_ASM__ float convert_float_rtp(long a) __asm("air.convert.f.f32.s.i64.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(long2 a) __asm("air.convert.f.v2f32.s.v2i64.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(long3 a) __asm("air.convert.f.v3f32.s.v3i64.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(long4 a) __asm("air.convert.f.v4f32.s.v4i64.rtp");
  __AIR_ASM__ float convert_float_rte(long a) __asm("air.convert.f.f32.s.i64.rte");
  __AIR_ASM__ float2 convert_float2_rte(long2 a) __asm("air.convert.f.v2f32.s.v2i64.rte");
  __AIR_ASM__ float3 convert_float3_rte(long3 a) __asm("air.convert.f.v3f32.s.v3i64.rte");
  __AIR_ASM__ float4 convert_float4_rte(long4 a) __asm("air.convert.f.v4f32.s.v4i64.rte");
  __AIR_ASM__ float convert_float(long a) __asm("air.convert.f.f32.s.i64");
  __AIR_ASM__ float2 convert_float2(long2 a) __asm("air.convert.f.v2f32.s.v2i64");
  __AIR_ASM__ float3 convert_float3(long3 a) __asm("air.convert.f.v3f32.s.v3i64");
  __AIR_ASM__ float4 convert_float4(long4 a) __asm("air.convert.f.v4f32.s.v4i64");
  __AIR_ASM__ float convert_float_rtz(ulong a) __asm("air.convert.f.f32.u.i64.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(ulong2 a) __asm("air.convert.f.v2f32.u.v2i64.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(ulong3 a) __asm("air.convert.f.v3f32.u.v3i64.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(ulong4 a) __asm("air.convert.f.v4f32.u.v4i64.rtz");
  __AIR_ASM__ float convert_float_rtn(ulong a) __asm("air.convert.f.f32.u.i64.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(ulong2 a) __asm("air.convert.f.v2f32.u.v2i64.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(ulong3 a) __asm("air.convert.f.v3f32.u.v3i64.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(ulong4 a) __asm("air.convert.f.v4f32.u.v4i64.rtn");
  __AIR_ASM__ float convert_float_rtp(ulong a) __asm("air.convert.f.f32.u.i64.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(ulong2 a) __asm("air.convert.f.v2f32.u.v2i64.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(ulong3 a) __asm("air.convert.f.v3f32.u.v3i64.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(ulong4 a) __asm("air.convert.f.v4f32.u.v4i64.rtp");
  __AIR_ASM__ float convert_float_rte(ulong a) __asm("air.convert.f.f32.u.i64.rte");
  __AIR_ASM__ float2 convert_float2_rte(ulong2 a) __asm("air.convert.f.v2f32.u.v2i64.rte");
  __AIR_ASM__ float3 convert_float3_rte(ulong3 a) __asm("air.convert.f.v3f32.u.v3i64.rte");
  __AIR_ASM__ float4 convert_float4_rte(ulong4 a) __asm("air.convert.f.v4f32.u.v4i64.rte");
  __AIR_ASM__ float convert_float(ulong a) __asm("air.convert.f.f32.u.i64");
  __AIR_ASM__ float2 convert_float2(ulong2 a) __asm("air.convert.f.v2f32.u.v2i64");
  __AIR_ASM__ float3 convert_float3(ulong3 a) __asm("air.convert.f.v3f32.u.v3i64");
  __AIR_ASM__ float4 convert_float4(ulong4 a) __asm("air.convert.f.v4f32.u.v4i64");
  __AIR_ASM__ float convert_float_rtz(float a) __asm("air.convert.f.f32.f.f32.rtz");
  __AIR_ASM__ float2 convert_float2_rtz(float2 a) __asm("air.convert.f.v2f32.f.v2f32.rtz");
  __AIR_ASM__ float3 convert_float3_rtz(float3 a) __asm("air.convert.f.v3f32.f.v3f32.rtz");
  __AIR_ASM__ float4 convert_float4_rtz(float4 a) __asm("air.convert.f.v4f32.f.v4f32.rtz");
  __AIR_ASM__ float convert_float_rtn(float a) __asm("air.convert.f.f32.f.f32.rtn");
  __AIR_ASM__ float2 convert_float2_rtn(float2 a) __asm("air.convert.f.v2f32.f.v2f32.rtn");
  __AIR_ASM__ float3 convert_float3_rtn(float3 a) __asm("air.convert.f.v3f32.f.v3f32.rtn");
  __AIR_ASM__ float4 convert_float4_rtn(float4 a) __asm("air.convert.f.v4f32.f.v4f32.rtn");
  __AIR_ASM__ float convert_float_rtp(float a) __asm("air.convert.f.f32.f.f32.rtp");
  __AIR_ASM__ float2 convert_float2_rtp(float2 a) __asm("air.convert.f.v2f32.f.v2f32.rtp");
  __AIR_ASM__ float3 convert_float3_rtp(float3 a) __asm("air.convert.f.v3f32.f.v3f32.rtp");
  __AIR_ASM__ float4 convert_float4_rtp(float4 a) __asm("air.convert.f.v4f32.f.v4f32.rtp");
  __AIR_ASM__ float convert_float_rte(float a) __asm("air.convert.f.f32.f.f32.rte");
  __AIR_ASM__ float2 convert_float2_rte(float2 a) __asm("air.convert.f.v2f32.f.v2f32.rte");
  __AIR_ASM__ float3 convert_float3_rte(float3 a) __asm("air.convert.f.v3f32.f.v3f32.rte");
  __AIR_ASM__ float4 convert_float4_rte(float4 a) __asm("air.convert.f.v4f32.f.v4f32.rte");
  __AIR_ASM__ float convert_float(float a) __asm("air.convert.f.f32.f.f32");
  __AIR_ASM__ float2 convert_float2(float2 a) __asm("air.convert.f.v2f32.f.v2f32");
  __AIR_ASM__ float3 convert_float3(float3 a) __asm("air.convert.f.v3f32.f.v3f32");
  __AIR_ASM__ float4 convert_float4(float4 a) __asm("air.convert.f.v4f32.f.v4f32");

  __AIR_FUNC__ char8 convert_char8_sat(char8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(char16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(char8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(char16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(uchar8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(uchar16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(uchar8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(uchar16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(short8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(short16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(short8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(short16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(ushort8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(ushort16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(ushort8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(ushort16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(int8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(int16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(int8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(int16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(uint8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(uint16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(uint8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(uint16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(long8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(long16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(long8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(long16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(ulong8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(ulong16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(ulong8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(ulong16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat_rtz(float8 a) {
    char8 r;
    r.hi = convert_char4_sat_rtz(a.hi);
    r.lo = convert_char4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat_rtz(float16 a) {
    char16 r;
    r.hi = convert_char8_sat_rtz(a.hi);
    r.lo = convert_char8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat_rtn(float8 a) {
    char8 r;
    r.hi = convert_char4_sat_rtn(a.hi);
    r.lo = convert_char4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat_rtn(float16 a) {
    char16 r;
    r.hi = convert_char8_sat_rtn(a.hi);
    r.lo = convert_char8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat_rtp(float8 a) {
    char8 r;
    r.hi = convert_char4_sat_rtp(a.hi);
    r.lo = convert_char4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat_rtp(float16 a) {
    char16 r;
    r.hi = convert_char8_sat_rtp(a.hi);
    r.lo = convert_char8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat_rte(float8 a) {
    char8 r;
    r.hi = convert_char4_sat_rte(a.hi);
    r.lo = convert_char4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat_rte(float16 a) {
    char16 r;
    r.hi = convert_char8_sat_rte(a.hi);
    r.lo = convert_char8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(float8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(float16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_rtz(float8 a) {
    char8 r;
    r.hi = convert_char4_rtz(a.hi);
    r.lo = convert_char4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_rtz(float16 a) {
    char16 r;
    r.hi = convert_char8_rtz(a.hi);
    r.lo = convert_char8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_rtn(float8 a) {
    char8 r;
    r.hi = convert_char4_rtn(a.hi);
    r.lo = convert_char4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_rtn(float16 a) {
    char16 r;
    r.hi = convert_char8_rtn(a.hi);
    r.lo = convert_char8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_rtp(float8 a) {
    char8 r;
    r.hi = convert_char4_rtp(a.hi);
    r.lo = convert_char4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_rtp(float16 a) {
    char16 r;
    r.hi = convert_char8_rtp(a.hi);
    r.lo = convert_char8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_rte(float8 a) {
    char8 r;
    r.hi = convert_char4_rte(a.hi);
    r.lo = convert_char4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_rte(float16 a) {
    char16 r;
    r.hi = convert_char8_rte(a.hi);
    r.lo = convert_char8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(float8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(float16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(char8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(char16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(char8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(char16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(uchar8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(uchar16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(uchar8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(uchar16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(short8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(short16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(short8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(short16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(ushort8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(ushort16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(ushort8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(ushort16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(int8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(int16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(int8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(int16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(uint8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(uint16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(uint8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(uint16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(long8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(long16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(long8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(long16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(ulong8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(ulong16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(ulong8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(ulong16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat_rtz(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat_rtz(a.hi);
    r.lo = convert_uchar4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat_rtz(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat_rtz(a.hi);
    r.lo = convert_uchar8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat_rtn(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat_rtn(a.hi);
    r.lo = convert_uchar4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat_rtn(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat_rtn(a.hi);
    r.lo = convert_uchar8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat_rtp(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat_rtp(a.hi);
    r.lo = convert_uchar4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat_rtp(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat_rtp(a.hi);
    r.lo = convert_uchar8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat_rte(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat_rte(a.hi);
    r.lo = convert_uchar4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat_rte(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat_rte(a.hi);
    r.lo = convert_uchar8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_rtz(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_rtz(a.hi);
    r.lo = convert_uchar4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_rtz(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_rtz(a.hi);
    r.lo = convert_uchar8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_rtn(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_rtn(a.hi);
    r.lo = convert_uchar4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_rtn(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_rtn(a.hi);
    r.lo = convert_uchar8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_rtp(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_rtp(a.hi);
    r.lo = convert_uchar4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_rtp(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_rtp(a.hi);
    r.lo = convert_uchar8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_rte(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4_rte(a.hi);
    r.lo = convert_uchar4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_rte(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8_rte(a.hi);
    r.lo = convert_uchar8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(float8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(float16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(char8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(char16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(char8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(char16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(uchar8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(uchar16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(uchar8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(uchar16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(short8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(short16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(short8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(short16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(ushort8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(ushort16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(ushort8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(ushort16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(int8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(int16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(int8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(int16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(uint8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(uint16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(uint8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(uint16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(long8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(long16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(long8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(long16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(ulong8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(ulong16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(ulong8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(ulong16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat_rtz(float8 a) {
    short8 r;
    r.hi = convert_short4_sat_rtz(a.hi);
    r.lo = convert_short4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat_rtz(float16 a) {
    short16 r;
    r.hi = convert_short8_sat_rtz(a.hi);
    r.lo = convert_short8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat_rtn(float8 a) {
    short8 r;
    r.hi = convert_short4_sat_rtn(a.hi);
    r.lo = convert_short4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat_rtn(float16 a) {
    short16 r;
    r.hi = convert_short8_sat_rtn(a.hi);
    r.lo = convert_short8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat_rtp(float8 a) {
    short8 r;
    r.hi = convert_short4_sat_rtp(a.hi);
    r.lo = convert_short4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat_rtp(float16 a) {
    short16 r;
    r.hi = convert_short8_sat_rtp(a.hi);
    r.lo = convert_short8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat_rte(float8 a) {
    short8 r;
    r.hi = convert_short4_sat_rte(a.hi);
    r.lo = convert_short4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat_rte(float16 a) {
    short16 r;
    r.hi = convert_short8_sat_rte(a.hi);
    r.lo = convert_short8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(float8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(float16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_rtz(float8 a) {
    short8 r;
    r.hi = convert_short4_rtz(a.hi);
    r.lo = convert_short4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_rtz(float16 a) {
    short16 r;
    r.hi = convert_short8_rtz(a.hi);
    r.lo = convert_short8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_rtn(float8 a) {
    short8 r;
    r.hi = convert_short4_rtn(a.hi);
    r.lo = convert_short4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_rtn(float16 a) {
    short16 r;
    r.hi = convert_short8_rtn(a.hi);
    r.lo = convert_short8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_rtp(float8 a) {
    short8 r;
    r.hi = convert_short4_rtp(a.hi);
    r.lo = convert_short4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_rtp(float16 a) {
    short16 r;
    r.hi = convert_short8_rtp(a.hi);
    r.lo = convert_short8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_rte(float8 a) {
    short8 r;
    r.hi = convert_short4_rte(a.hi);
    r.lo = convert_short4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_rte(float16 a) {
    short16 r;
    r.hi = convert_short8_rte(a.hi);
    r.lo = convert_short8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(float8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(float16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(char8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(char16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(char8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(char16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(uchar8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(uchar16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(uchar8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(uchar16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(short8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(short16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(short8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(short16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(ushort8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(ushort16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(ushort8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(ushort16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(int8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(int16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(int8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(int16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(uint8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(uint16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(uint8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(uint16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(long8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(long16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(long8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(long16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(ulong8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(ulong16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(ulong8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(ulong16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat_rtz(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat_rtz(a.hi);
    r.lo = convert_ushort4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat_rtz(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat_rtz(a.hi);
    r.lo = convert_ushort8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat_rtn(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat_rtn(a.hi);
    r.lo = convert_ushort4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat_rtn(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat_rtn(a.hi);
    r.lo = convert_ushort8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat_rtp(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat_rtp(a.hi);
    r.lo = convert_ushort4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat_rtp(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat_rtp(a.hi);
    r.lo = convert_ushort8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat_rte(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat_rte(a.hi);
    r.lo = convert_ushort4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat_rte(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat_rte(a.hi);
    r.lo = convert_ushort8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_rtz(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_rtz(a.hi);
    r.lo = convert_ushort4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_rtz(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_rtz(a.hi);
    r.lo = convert_ushort8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_rtn(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_rtn(a.hi);
    r.lo = convert_ushort4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_rtn(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_rtn(a.hi);
    r.lo = convert_ushort8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_rtp(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_rtp(a.hi);
    r.lo = convert_ushort4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_rtp(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_rtp(a.hi);
    r.lo = convert_ushort8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_rte(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4_rte(a.hi);
    r.lo = convert_ushort4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_rte(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8_rte(a.hi);
    r.lo = convert_ushort8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(float8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(float16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(char8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(char16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(char8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(char16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(uchar8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(uchar16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(uchar8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(uchar16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(short8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(short16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(short8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(short16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(ushort8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(ushort16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(ushort8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(ushort16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(int8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(int16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(int8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(int16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(uint8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(uint16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(uint8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(uint16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(long8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(long16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(long8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(long16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(ulong8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(ulong16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(ulong8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(ulong16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat_rtz(float8 a) {
    int8 r;
    r.hi = convert_int4_sat_rtz(a.hi);
    r.lo = convert_int4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat_rtz(float16 a) {
    int16 r;
    r.hi = convert_int8_sat_rtz(a.hi);
    r.lo = convert_int8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat_rtn(float8 a) {
    int8 r;
    r.hi = convert_int4_sat_rtn(a.hi);
    r.lo = convert_int4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat_rtn(float16 a) {
    int16 r;
    r.hi = convert_int8_sat_rtn(a.hi);
    r.lo = convert_int8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat_rtp(float8 a) {
    int8 r;
    r.hi = convert_int4_sat_rtp(a.hi);
    r.lo = convert_int4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat_rtp(float16 a) {
    int16 r;
    r.hi = convert_int8_sat_rtp(a.hi);
    r.lo = convert_int8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat_rte(float8 a) {
    int8 r;
    r.hi = convert_int4_sat_rte(a.hi);
    r.lo = convert_int4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat_rte(float16 a) {
    int16 r;
    r.hi = convert_int8_sat_rte(a.hi);
    r.lo = convert_int8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(float8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(float16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_rtz(float8 a) {
    int8 r;
    r.hi = convert_int4_rtz(a.hi);
    r.lo = convert_int4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_rtz(float16 a) {
    int16 r;
    r.hi = convert_int8_rtz(a.hi);
    r.lo = convert_int8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_rtn(float8 a) {
    int8 r;
    r.hi = convert_int4_rtn(a.hi);
    r.lo = convert_int4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_rtn(float16 a) {
    int16 r;
    r.hi = convert_int8_rtn(a.hi);
    r.lo = convert_int8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_rtp(float8 a) {
    int8 r;
    r.hi = convert_int4_rtp(a.hi);
    r.lo = convert_int4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_rtp(float16 a) {
    int16 r;
    r.hi = convert_int8_rtp(a.hi);
    r.lo = convert_int8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_rte(float8 a) {
    int8 r;
    r.hi = convert_int4_rte(a.hi);
    r.lo = convert_int4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_rte(float16 a) {
    int16 r;
    r.hi = convert_int8_rte(a.hi);
    r.lo = convert_int8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(float8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(float16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(char8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(char16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(char8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(char16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(uchar8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(uchar16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(uchar8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(uchar16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(short8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(short16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(short8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(short16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(ushort8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(ushort16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(ushort8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(ushort16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(int8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(int16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(int8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(int16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(uint8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(uint16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(uint8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(uint16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(long8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(long16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(long8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(long16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(ulong8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(ulong16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(ulong8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(ulong16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat_rtz(float8 a) {
    uint8 r;
    r.hi = convert_uint4_sat_rtz(a.hi);
    r.lo = convert_uint4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat_rtz(float16 a) {
    uint16 r;
    r.hi = convert_uint8_sat_rtz(a.hi);
    r.lo = convert_uint8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat_rtn(float8 a) {
    uint8 r;
    r.hi = convert_uint4_sat_rtn(a.hi);
    r.lo = convert_uint4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat_rtn(float16 a) {
    uint16 r;
    r.hi = convert_uint8_sat_rtn(a.hi);
    r.lo = convert_uint8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat_rtp(float8 a) {
    uint8 r;
    r.hi = convert_uint4_sat_rtp(a.hi);
    r.lo = convert_uint4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat_rtp(float16 a) {
    uint16 r;
    r.hi = convert_uint8_sat_rtp(a.hi);
    r.lo = convert_uint8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat_rte(float8 a) {
    uint8 r;
    r.hi = convert_uint4_sat_rte(a.hi);
    r.lo = convert_uint4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat_rte(float16 a) {
    uint16 r;
    r.hi = convert_uint8_sat_rte(a.hi);
    r.lo = convert_uint8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(float8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(float16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_rtz(float8 a) {
    uint8 r;
    r.hi = convert_uint4_rtz(a.hi);
    r.lo = convert_uint4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_rtz(float16 a) {
    uint16 r;
    r.hi = convert_uint8_rtz(a.hi);
    r.lo = convert_uint8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_rtn(float8 a) {
    uint8 r;
    r.hi = convert_uint4_rtn(a.hi);
    r.lo = convert_uint4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_rtn(float16 a) {
    uint16 r;
    r.hi = convert_uint8_rtn(a.hi);
    r.lo = convert_uint8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_rtp(float8 a) {
    uint8 r;
    r.hi = convert_uint4_rtp(a.hi);
    r.lo = convert_uint4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_rtp(float16 a) {
    uint16 r;
    r.hi = convert_uint8_rtp(a.hi);
    r.lo = convert_uint8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_rte(float8 a) {
    uint8 r;
    r.hi = convert_uint4_rte(a.hi);
    r.lo = convert_uint4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_rte(float16 a) {
    uint16 r;
    r.hi = convert_uint8_rte(a.hi);
    r.lo = convert_uint8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(float8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(float16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(char8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(char16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(char8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(char16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(uchar8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(uchar16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(uchar8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(uchar16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(short8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(short16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(short8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(short16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(ushort8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(ushort16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(ushort8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(ushort16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(int8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(int16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(int8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(int16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(uint8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(uint16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(uint8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(uint16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(long8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(long16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(long8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(long16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(ulong8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(ulong16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(ulong8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(ulong16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat_rtz(float8 a) {
    long8 r;
    r.hi = convert_long4_sat_rtz(a.hi);
    r.lo = convert_long4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat_rtz(float16 a) {
    long16 r;
    r.hi = convert_long8_sat_rtz(a.hi);
    r.lo = convert_long8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat_rtn(float8 a) {
    long8 r;
    r.hi = convert_long4_sat_rtn(a.hi);
    r.lo = convert_long4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat_rtn(float16 a) {
    long16 r;
    r.hi = convert_long8_sat_rtn(a.hi);
    r.lo = convert_long8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat_rtp(float8 a) {
    long8 r;
    r.hi = convert_long4_sat_rtp(a.hi);
    r.lo = convert_long4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat_rtp(float16 a) {
    long16 r;
    r.hi = convert_long8_sat_rtp(a.hi);
    r.lo = convert_long8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat_rte(float8 a) {
    long8 r;
    r.hi = convert_long4_sat_rte(a.hi);
    r.lo = convert_long4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat_rte(float16 a) {
    long16 r;
    r.hi = convert_long8_sat_rte(a.hi);
    r.lo = convert_long8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(float8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(float16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_rtz(float8 a) {
    long8 r;
    r.hi = convert_long4_rtz(a.hi);
    r.lo = convert_long4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_rtz(float16 a) {
    long16 r;
    r.hi = convert_long8_rtz(a.hi);
    r.lo = convert_long8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_rtn(float8 a) {
    long8 r;
    r.hi = convert_long4_rtn(a.hi);
    r.lo = convert_long4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_rtn(float16 a) {
    long16 r;
    r.hi = convert_long8_rtn(a.hi);
    r.lo = convert_long8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_rtp(float8 a) {
    long8 r;
    r.hi = convert_long4_rtp(a.hi);
    r.lo = convert_long4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_rtp(float16 a) {
    long16 r;
    r.hi = convert_long8_rtp(a.hi);
    r.lo = convert_long8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_rte(float8 a) {
    long8 r;
    r.hi = convert_long4_rte(a.hi);
    r.lo = convert_long4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_rte(float16 a) {
    long16 r;
    r.hi = convert_long8_rte(a.hi);
    r.lo = convert_long8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(float8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(float16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(char8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(char16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(char8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(char16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(uchar8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(uchar16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(uchar8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(uchar16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(short8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(short16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(short8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(short16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(ushort8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(ushort16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(ushort8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(ushort16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(int8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(int16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(int8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(int16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(uint8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(uint16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(uint8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(uint16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(long8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(long16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(long8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(long16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(ulong8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(ulong16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(ulong8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(ulong16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat_rtz(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat_rtz(a.hi);
    r.lo = convert_ulong4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat_rtz(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat_rtz(a.hi);
    r.lo = convert_ulong8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat_rtn(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat_rtn(a.hi);
    r.lo = convert_ulong4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat_rtn(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat_rtn(a.hi);
    r.lo = convert_ulong8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat_rtp(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat_rtp(a.hi);
    r.lo = convert_ulong4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat_rtp(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat_rtp(a.hi);
    r.lo = convert_ulong8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat_rte(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat_rte(a.hi);
    r.lo = convert_ulong4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat_rte(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat_rte(a.hi);
    r.lo = convert_ulong8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_rtz(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_rtz(a.hi);
    r.lo = convert_ulong4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_rtz(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_rtz(a.hi);
    r.lo = convert_ulong8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_rtn(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_rtn(a.hi);
    r.lo = convert_ulong4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_rtn(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_rtn(a.hi);
    r.lo = convert_ulong8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_rtp(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_rtp(a.hi);
    r.lo = convert_ulong4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_rtp(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_rtp(a.hi);
    r.lo = convert_ulong8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_rte(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4_rte(a.hi);
    r.lo = convert_ulong4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_rte(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8_rte(a.hi);
    r.lo = convert_ulong8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(float8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(float16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(char8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(char16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(char8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(char16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(char8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(char16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(char8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(char16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(char8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(char16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(uchar8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(uchar16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(uchar8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(uchar16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(uchar8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(uchar16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(uchar8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(uchar16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(uchar8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(uchar16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(short8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(short16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(short8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(short16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(short8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(short16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(short8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(short16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(short8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(short16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(ushort8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(ushort16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(ushort8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(ushort16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(ushort8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(ushort16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(ushort8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(ushort16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(ushort8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(ushort16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(int8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(int16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(int8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(int16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(int8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(int16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(int8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(int16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(int8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(int16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(uint8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(uint16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(uint8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(uint16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(uint8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(uint16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(uint8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(uint16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(uint8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(uint16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(long8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(long16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(long8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(long16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(long8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(long16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(long8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(long16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(long8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(long16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(ulong8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(ulong16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(ulong8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(ulong16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(ulong8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(ulong16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(ulong8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(ulong16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(ulong8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(ulong16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtz(float8 a) {
    float8 r;
    r.hi = convert_float4_rtz(a.hi);
    r.lo = convert_float4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtz(float16 a) {
    float16 r;
    r.hi = convert_float8_rtz(a.hi);
    r.lo = convert_float8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtn(float8 a) {
    float8 r;
    r.hi = convert_float4_rtn(a.hi);
    r.lo = convert_float4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtn(float16 a) {
    float16 r;
    r.hi = convert_float8_rtn(a.hi);
    r.lo = convert_float8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rtp(float8 a) {
    float8 r;
    r.hi = convert_float4_rtp(a.hi);
    r.lo = convert_float4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rtp(float16 a) {
    float16 r;
    r.hi = convert_float8_rtp(a.hi);
    r.lo = convert_float8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8_rte(float8 a) {
    float8 r;
    r.hi = convert_float4_rte(a.hi);
    r.lo = convert_float4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16_rte(float16 a) {
    float16 r;
    r.hi = convert_float8_rte(a.hi);
    r.lo = convert_float8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ float8 convert_float8(float8 a) {
    float8 r;
    r.hi = convert_float4(a.hi);
    r.lo = convert_float4(a.lo);
    return r;
  }
  __AIR_FUNC__ float16 convert_float16(float16 a) {
    float16 r;
    r.hi = convert_float8(a.hi);
    r.lo = convert_float8(a.lo);
    return r;
  }


// Double conversions
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

  __AIR_ASM__ char convert_char_sat_rtz(double a) __asm("air.convert.s.i8.f.f64.rtz.sat");
  __AIR_ASM__ char2 convert_char2_sat_rtz(double2 a) __asm("air.convert.s.v2i8.f.v2f64.rtz.sat");
  __AIR_ASM__ char3 convert_char3_sat_rtz(double3 a) __asm("air.convert.s.v3i8.f.v3f64.rtz.sat");
  __AIR_ASM__ char4 convert_char4_sat_rtz(double4 a) __asm("air.convert.s.v4i8.f.v4f64.rtz.sat");
  __AIR_ASM__ char convert_char_sat_rtn(double a) __asm("air.convert.s.i8.f.f64.rtn.sat");
  __AIR_ASM__ char2 convert_char2_sat_rtn(double2 a) __asm("air.convert.s.v2i8.f.v2f64.rtn.sat");
  __AIR_ASM__ char3 convert_char3_sat_rtn(double3 a) __asm("air.convert.s.v3i8.f.v3f64.rtn.sat");
  __AIR_ASM__ char4 convert_char4_sat_rtn(double4 a) __asm("air.convert.s.v4i8.f.v4f64.rtn.sat");
  __AIR_ASM__ char convert_char_sat_rtp(double a) __asm("air.convert.s.i8.f.f64.rtp.sat");
  __AIR_ASM__ char2 convert_char2_sat_rtp(double2 a) __asm("air.convert.s.v2i8.f.v2f64.rtp.sat");
  __AIR_ASM__ char3 convert_char3_sat_rtp(double3 a) __asm("air.convert.s.v3i8.f.v3f64.rtp.sat");
  __AIR_ASM__ char4 convert_char4_sat_rtp(double4 a) __asm("air.convert.s.v4i8.f.v4f64.rtp.sat");
  __AIR_ASM__ char convert_char_sat_rte(double a) __asm("air.convert.s.i8.f.f64.rte.sat");
  __AIR_ASM__ char2 convert_char2_sat_rte(double2 a) __asm("air.convert.s.v2i8.f.v2f64.rte.sat");
  __AIR_ASM__ char3 convert_char3_sat_rte(double3 a) __asm("air.convert.s.v3i8.f.v3f64.rte.sat");
  __AIR_ASM__ char4 convert_char4_sat_rte(double4 a) __asm("air.convert.s.v4i8.f.v4f64.rte.sat");
  __AIR_ASM__ char convert_char_sat(double a) __asm("air.convert.s.i8.f.f64.sat");
  __AIR_ASM__ char2 convert_char2_sat(double2 a) __asm("air.convert.s.v2i8.f.v2f64.sat");
  __AIR_ASM__ char3 convert_char3_sat(double3 a) __asm("air.convert.s.v3i8.f.v3f64.sat");
  __AIR_ASM__ char4 convert_char4_sat(double4 a) __asm("air.convert.s.v4i8.f.v4f64.sat");
  __AIR_ASM__ char convert_char_rtz(double a) __asm("air.convert.s.i8.f.f64.rtz");
  __AIR_ASM__ char2 convert_char2_rtz(double2 a) __asm("air.convert.s.v2i8.f.v2f64.rtz");
  __AIR_ASM__ char3 convert_char3_rtz(double3 a) __asm("air.convert.s.v3i8.f.v3f64.rtz");
  __AIR_ASM__ char4 convert_char4_rtz(double4 a) __asm("air.convert.s.v4i8.f.v4f64.rtz");
  __AIR_ASM__ char convert_char_rtn(double a) __asm("air.convert.s.i8.f.f64.rtn");
  __AIR_ASM__ char2 convert_char2_rtn(double2 a) __asm("air.convert.s.v2i8.f.v2f64.rtn");
  __AIR_ASM__ char3 convert_char3_rtn(double3 a) __asm("air.convert.s.v3i8.f.v3f64.rtn");
  __AIR_ASM__ char4 convert_char4_rtn(double4 a) __asm("air.convert.s.v4i8.f.v4f64.rtn");
  __AIR_ASM__ char convert_char_rtp(double a) __asm("air.convert.s.i8.f.f64.rtp");
  __AIR_ASM__ char2 convert_char2_rtp(double2 a) __asm("air.convert.s.v2i8.f.v2f64.rtp");
  __AIR_ASM__ char3 convert_char3_rtp(double3 a) __asm("air.convert.s.v3i8.f.v3f64.rtp");
  __AIR_ASM__ char4 convert_char4_rtp(double4 a) __asm("air.convert.s.v4i8.f.v4f64.rtp");
  __AIR_ASM__ char convert_char_rte(double a) __asm("air.convert.s.i8.f.f64.rte");
  __AIR_ASM__ char2 convert_char2_rte(double2 a) __asm("air.convert.s.v2i8.f.v2f64.rte");
  __AIR_ASM__ char3 convert_char3_rte(double3 a) __asm("air.convert.s.v3i8.f.v3f64.rte");
  __AIR_ASM__ char4 convert_char4_rte(double4 a) __asm("air.convert.s.v4i8.f.v4f64.rte");
  __AIR_ASM__ char convert_char(double a) __asm("air.convert.s.i8.f.f64");
  __AIR_ASM__ char2 convert_char2(double2 a) __asm("air.convert.s.v2i8.f.v2f64");
  __AIR_ASM__ char3 convert_char3(double3 a) __asm("air.convert.s.v3i8.f.v3f64");
  __AIR_ASM__ char4 convert_char4(double4 a) __asm("air.convert.s.v4i8.f.v4f64");
  __AIR_ASM__ uchar convert_uchar_sat_rtz(double a) __asm("air.convert.u.i8.f.f64.rtz.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat_rtz(double2 a) __asm("air.convert.u.v2i8.f.v2f64.rtz.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat_rtz(double3 a) __asm("air.convert.u.v3i8.f.v3f64.rtz.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat_rtz(double4 a) __asm("air.convert.u.v4i8.f.v4f64.rtz.sat");
  __AIR_ASM__ uchar convert_uchar_sat_rtn(double a) __asm("air.convert.u.i8.f.f64.rtn.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat_rtn(double2 a) __asm("air.convert.u.v2i8.f.v2f64.rtn.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat_rtn(double3 a) __asm("air.convert.u.v3i8.f.v3f64.rtn.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat_rtn(double4 a) __asm("air.convert.u.v4i8.f.v4f64.rtn.sat");
  __AIR_ASM__ uchar convert_uchar_sat_rtp(double a) __asm("air.convert.u.i8.f.f64.rtp.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat_rtp(double2 a) __asm("air.convert.u.v2i8.f.v2f64.rtp.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat_rtp(double3 a) __asm("air.convert.u.v3i8.f.v3f64.rtp.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat_rtp(double4 a) __asm("air.convert.u.v4i8.f.v4f64.rtp.sat");
  __AIR_ASM__ uchar convert_uchar_sat_rte(double a) __asm("air.convert.u.i8.f.f64.rte.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat_rte(double2 a) __asm("air.convert.u.v2i8.f.v2f64.rte.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat_rte(double3 a) __asm("air.convert.u.v3i8.f.v3f64.rte.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat_rte(double4 a) __asm("air.convert.u.v4i8.f.v4f64.rte.sat");
  __AIR_ASM__ uchar convert_uchar_sat(double a) __asm("air.convert.u.i8.f.f64.sat");
  __AIR_ASM__ uchar2 convert_uchar2_sat(double2 a) __asm("air.convert.u.v2i8.f.v2f64.sat");
  __AIR_ASM__ uchar3 convert_uchar3_sat(double3 a) __asm("air.convert.u.v3i8.f.v3f64.sat");
  __AIR_ASM__ uchar4 convert_uchar4_sat(double4 a) __asm("air.convert.u.v4i8.f.v4f64.sat");
  __AIR_ASM__ uchar convert_uchar_rtz(double a) __asm("air.convert.u.i8.f.f64.rtz");
  __AIR_ASM__ uchar2 convert_uchar2_rtz(double2 a) __asm("air.convert.u.v2i8.f.v2f64.rtz");
  __AIR_ASM__ uchar3 convert_uchar3_rtz(double3 a) __asm("air.convert.u.v3i8.f.v3f64.rtz");
  __AIR_ASM__ uchar4 convert_uchar4_rtz(double4 a) __asm("air.convert.u.v4i8.f.v4f64.rtz");
  __AIR_ASM__ uchar convert_uchar_rtn(double a) __asm("air.convert.u.i8.f.f64.rtn");
  __AIR_ASM__ uchar2 convert_uchar2_rtn(double2 a) __asm("air.convert.u.v2i8.f.v2f64.rtn");
  __AIR_ASM__ uchar3 convert_uchar3_rtn(double3 a) __asm("air.convert.u.v3i8.f.v3f64.rtn");
  __AIR_ASM__ uchar4 convert_uchar4_rtn(double4 a) __asm("air.convert.u.v4i8.f.v4f64.rtn");
  __AIR_ASM__ uchar convert_uchar_rtp(double a) __asm("air.convert.u.i8.f.f64.rtp");
  __AIR_ASM__ uchar2 convert_uchar2_rtp(double2 a) __asm("air.convert.u.v2i8.f.v2f64.rtp");
  __AIR_ASM__ uchar3 convert_uchar3_rtp(double3 a) __asm("air.convert.u.v3i8.f.v3f64.rtp");
  __AIR_ASM__ uchar4 convert_uchar4_rtp(double4 a) __asm("air.convert.u.v4i8.f.v4f64.rtp");
  __AIR_ASM__ uchar convert_uchar_rte(double a) __asm("air.convert.u.i8.f.f64.rte");
  __AIR_ASM__ uchar2 convert_uchar2_rte(double2 a) __asm("air.convert.u.v2i8.f.v2f64.rte");
  __AIR_ASM__ uchar3 convert_uchar3_rte(double3 a) __asm("air.convert.u.v3i8.f.v3f64.rte");
  __AIR_ASM__ uchar4 convert_uchar4_rte(double4 a) __asm("air.convert.u.v4i8.f.v4f64.rte");
  __AIR_ASM__ uchar convert_uchar(double a) __asm("air.convert.u.i8.f.f64");
  __AIR_ASM__ uchar2 convert_uchar2(double2 a) __asm("air.convert.u.v2i8.f.v2f64");
  __AIR_ASM__ uchar3 convert_uchar3(double3 a) __asm("air.convert.u.v3i8.f.v3f64");
  __AIR_ASM__ uchar4 convert_uchar4(double4 a) __asm("air.convert.u.v4i8.f.v4f64");
  __AIR_ASM__ short convert_short_sat_rtz(double a) __asm("air.convert.s.i16.f.f64.rtz.sat");
  __AIR_ASM__ short2 convert_short2_sat_rtz(double2 a) __asm("air.convert.s.v2i16.f.v2f64.rtz.sat");
  __AIR_ASM__ short3 convert_short3_sat_rtz(double3 a) __asm("air.convert.s.v3i16.f.v3f64.rtz.sat");
  __AIR_ASM__ short4 convert_short4_sat_rtz(double4 a) __asm("air.convert.s.v4i16.f.v4f64.rtz.sat");
  __AIR_ASM__ short convert_short_sat_rtn(double a) __asm("air.convert.s.i16.f.f64.rtn.sat");
  __AIR_ASM__ short2 convert_short2_sat_rtn(double2 a) __asm("air.convert.s.v2i16.f.v2f64.rtn.sat");
  __AIR_ASM__ short3 convert_short3_sat_rtn(double3 a) __asm("air.convert.s.v3i16.f.v3f64.rtn.sat");
  __AIR_ASM__ short4 convert_short4_sat_rtn(double4 a) __asm("air.convert.s.v4i16.f.v4f64.rtn.sat");
  __AIR_ASM__ short convert_short_sat_rtp(double a) __asm("air.convert.s.i16.f.f64.rtp.sat");
  __AIR_ASM__ short2 convert_short2_sat_rtp(double2 a) __asm("air.convert.s.v2i16.f.v2f64.rtp.sat");
  __AIR_ASM__ short3 convert_short3_sat_rtp(double3 a) __asm("air.convert.s.v3i16.f.v3f64.rtp.sat");
  __AIR_ASM__ short4 convert_short4_sat_rtp(double4 a) __asm("air.convert.s.v4i16.f.v4f64.rtp.sat");
  __AIR_ASM__ short convert_short_sat_rte(double a) __asm("air.convert.s.i16.f.f64.rte.sat");
  __AIR_ASM__ short2 convert_short2_sat_rte(double2 a) __asm("air.convert.s.v2i16.f.v2f64.rte.sat");
  __AIR_ASM__ short3 convert_short3_sat_rte(double3 a) __asm("air.convert.s.v3i16.f.v3f64.rte.sat");
  __AIR_ASM__ short4 convert_short4_sat_rte(double4 a) __asm("air.convert.s.v4i16.f.v4f64.rte.sat");
  __AIR_ASM__ short convert_short_sat(double a) __asm("air.convert.s.i16.f.f64.sat");
  __AIR_ASM__ short2 convert_short2_sat(double2 a) __asm("air.convert.s.v2i16.f.v2f64.sat");
  __AIR_ASM__ short3 convert_short3_sat(double3 a) __asm("air.convert.s.v3i16.f.v3f64.sat");
  __AIR_ASM__ short4 convert_short4_sat(double4 a) __asm("air.convert.s.v4i16.f.v4f64.sat");
  __AIR_ASM__ short convert_short_rtz(double a) __asm("air.convert.s.i16.f.f64.rtz");
  __AIR_ASM__ short2 convert_short2_rtz(double2 a) __asm("air.convert.s.v2i16.f.v2f64.rtz");
  __AIR_ASM__ short3 convert_short3_rtz(double3 a) __asm("air.convert.s.v3i16.f.v3f64.rtz");
  __AIR_ASM__ short4 convert_short4_rtz(double4 a) __asm("air.convert.s.v4i16.f.v4f64.rtz");
  __AIR_ASM__ short convert_short_rtn(double a) __asm("air.convert.s.i16.f.f64.rtn");
  __AIR_ASM__ short2 convert_short2_rtn(double2 a) __asm("air.convert.s.v2i16.f.v2f64.rtn");
  __AIR_ASM__ short3 convert_short3_rtn(double3 a) __asm("air.convert.s.v3i16.f.v3f64.rtn");
  __AIR_ASM__ short4 convert_short4_rtn(double4 a) __asm("air.convert.s.v4i16.f.v4f64.rtn");
  __AIR_ASM__ short convert_short_rtp(double a) __asm("air.convert.s.i16.f.f64.rtp");
  __AIR_ASM__ short2 convert_short2_rtp(double2 a) __asm("air.convert.s.v2i16.f.v2f64.rtp");
  __AIR_ASM__ short3 convert_short3_rtp(double3 a) __asm("air.convert.s.v3i16.f.v3f64.rtp");
  __AIR_ASM__ short4 convert_short4_rtp(double4 a) __asm("air.convert.s.v4i16.f.v4f64.rtp");
  __AIR_ASM__ short convert_short_rte(double a) __asm("air.convert.s.i16.f.f64.rte");
  __AIR_ASM__ short2 convert_short2_rte(double2 a) __asm("air.convert.s.v2i16.f.v2f64.rte");
  __AIR_ASM__ short3 convert_short3_rte(double3 a) __asm("air.convert.s.v3i16.f.v3f64.rte");
  __AIR_ASM__ short4 convert_short4_rte(double4 a) __asm("air.convert.s.v4i16.f.v4f64.rte");
  __AIR_ASM__ short convert_short(double a) __asm("air.convert.s.i16.f.f64");
  __AIR_ASM__ short2 convert_short2(double2 a) __asm("air.convert.s.v2i16.f.v2f64");
  __AIR_ASM__ short3 convert_short3(double3 a) __asm("air.convert.s.v3i16.f.v3f64");
  __AIR_ASM__ short4 convert_short4(double4 a) __asm("air.convert.s.v4i16.f.v4f64");
  __AIR_ASM__ ushort convert_ushort_sat_rtz(double a) __asm("air.convert.u.i16.f.f64.rtz.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat_rtz(double2 a) __asm("air.convert.u.v2i16.f.v2f64.rtz.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat_rtz(double3 a) __asm("air.convert.u.v3i16.f.v3f64.rtz.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat_rtz(double4 a) __asm("air.convert.u.v4i16.f.v4f64.rtz.sat");
  __AIR_ASM__ ushort convert_ushort_sat_rtn(double a) __asm("air.convert.u.i16.f.f64.rtn.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat_rtn(double2 a) __asm("air.convert.u.v2i16.f.v2f64.rtn.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat_rtn(double3 a) __asm("air.convert.u.v3i16.f.v3f64.rtn.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat_rtn(double4 a) __asm("air.convert.u.v4i16.f.v4f64.rtn.sat");
  __AIR_ASM__ ushort convert_ushort_sat_rtp(double a) __asm("air.convert.u.i16.f.f64.rtp.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat_rtp(double2 a) __asm("air.convert.u.v2i16.f.v2f64.rtp.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat_rtp(double3 a) __asm("air.convert.u.v3i16.f.v3f64.rtp.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat_rtp(double4 a) __asm("air.convert.u.v4i16.f.v4f64.rtp.sat");
  __AIR_ASM__ ushort convert_ushort_sat_rte(double a) __asm("air.convert.u.i16.f.f64.rte.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat_rte(double2 a) __asm("air.convert.u.v2i16.f.v2f64.rte.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat_rte(double3 a) __asm("air.convert.u.v3i16.f.v3f64.rte.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat_rte(double4 a) __asm("air.convert.u.v4i16.f.v4f64.rte.sat");
  __AIR_ASM__ ushort convert_ushort_sat(double a) __asm("air.convert.u.i16.f.f64.sat");
  __AIR_ASM__ ushort2 convert_ushort2_sat(double2 a) __asm("air.convert.u.v2i16.f.v2f64.sat");
  __AIR_ASM__ ushort3 convert_ushort3_sat(double3 a) __asm("air.convert.u.v3i16.f.v3f64.sat");
  __AIR_ASM__ ushort4 convert_ushort4_sat(double4 a) __asm("air.convert.u.v4i16.f.v4f64.sat");
  __AIR_ASM__ ushort convert_ushort_rtz(double a) __asm("air.convert.u.i16.f.f64.rtz");
  __AIR_ASM__ ushort2 convert_ushort2_rtz(double2 a) __asm("air.convert.u.v2i16.f.v2f64.rtz");
  __AIR_ASM__ ushort3 convert_ushort3_rtz(double3 a) __asm("air.convert.u.v3i16.f.v3f64.rtz");
  __AIR_ASM__ ushort4 convert_ushort4_rtz(double4 a) __asm("air.convert.u.v4i16.f.v4f64.rtz");
  __AIR_ASM__ ushort convert_ushort_rtn(double a) __asm("air.convert.u.i16.f.f64.rtn");
  __AIR_ASM__ ushort2 convert_ushort2_rtn(double2 a) __asm("air.convert.u.v2i16.f.v2f64.rtn");
  __AIR_ASM__ ushort3 convert_ushort3_rtn(double3 a) __asm("air.convert.u.v3i16.f.v3f64.rtn");
  __AIR_ASM__ ushort4 convert_ushort4_rtn(double4 a) __asm("air.convert.u.v4i16.f.v4f64.rtn");
  __AIR_ASM__ ushort convert_ushort_rtp(double a) __asm("air.convert.u.i16.f.f64.rtp");
  __AIR_ASM__ ushort2 convert_ushort2_rtp(double2 a) __asm("air.convert.u.v2i16.f.v2f64.rtp");
  __AIR_ASM__ ushort3 convert_ushort3_rtp(double3 a) __asm("air.convert.u.v3i16.f.v3f64.rtp");
  __AIR_ASM__ ushort4 convert_ushort4_rtp(double4 a) __asm("air.convert.u.v4i16.f.v4f64.rtp");
  __AIR_ASM__ ushort convert_ushort_rte(double a) __asm("air.convert.u.i16.f.f64.rte");
  __AIR_ASM__ ushort2 convert_ushort2_rte(double2 a) __asm("air.convert.u.v2i16.f.v2f64.rte");
  __AIR_ASM__ ushort3 convert_ushort3_rte(double3 a) __asm("air.convert.u.v3i16.f.v3f64.rte");
  __AIR_ASM__ ushort4 convert_ushort4_rte(double4 a) __asm("air.convert.u.v4i16.f.v4f64.rte");
  __AIR_ASM__ ushort convert_ushort(double a) __asm("air.convert.u.i16.f.f64");
  __AIR_ASM__ ushort2 convert_ushort2(double2 a) __asm("air.convert.u.v2i16.f.v2f64");
  __AIR_ASM__ ushort3 convert_ushort3(double3 a) __asm("air.convert.u.v3i16.f.v3f64");
  __AIR_ASM__ ushort4 convert_ushort4(double4 a) __asm("air.convert.u.v4i16.f.v4f64");
  __AIR_ASM__ int convert_int_sat_rtz(double a) __asm("air.convert.s.i32.f.f64.rtz.sat");
  __AIR_ASM__ int2 convert_int2_sat_rtz(double2 a) __asm("air.convert.s.v2i32.f.v2f64.rtz.sat");
  __AIR_ASM__ int3 convert_int3_sat_rtz(double3 a) __asm("air.convert.s.v3i32.f.v3f64.rtz.sat");
  __AIR_ASM__ int4 convert_int4_sat_rtz(double4 a) __asm("air.convert.s.v4i32.f.v4f64.rtz.sat");
  __AIR_ASM__ int convert_int_sat_rtn(double a) __asm("air.convert.s.i32.f.f64.rtn.sat");
  __AIR_ASM__ int2 convert_int2_sat_rtn(double2 a) __asm("air.convert.s.v2i32.f.v2f64.rtn.sat");
  __AIR_ASM__ int3 convert_int3_sat_rtn(double3 a) __asm("air.convert.s.v3i32.f.v3f64.rtn.sat");
  __AIR_ASM__ int4 convert_int4_sat_rtn(double4 a) __asm("air.convert.s.v4i32.f.v4f64.rtn.sat");
  __AIR_ASM__ int convert_int_sat_rtp(double a) __asm("air.convert.s.i32.f.f64.rtp.sat");
  __AIR_ASM__ int2 convert_int2_sat_rtp(double2 a) __asm("air.convert.s.v2i32.f.v2f64.rtp.sat");
  __AIR_ASM__ int3 convert_int3_sat_rtp(double3 a) __asm("air.convert.s.v3i32.f.v3f64.rtp.sat");
  __AIR_ASM__ int4 convert_int4_sat_rtp(double4 a) __asm("air.convert.s.v4i32.f.v4f64.rtp.sat");
  __AIR_ASM__ int convert_int_sat_rte(double a) __asm("air.convert.s.i32.f.f64.rte.sat");
  __AIR_ASM__ int2 convert_int2_sat_rte(double2 a) __asm("air.convert.s.v2i32.f.v2f64.rte.sat");
  __AIR_ASM__ int3 convert_int3_sat_rte(double3 a) __asm("air.convert.s.v3i32.f.v3f64.rte.sat");
  __AIR_ASM__ int4 convert_int4_sat_rte(double4 a) __asm("air.convert.s.v4i32.f.v4f64.rte.sat");
  __AIR_ASM__ int convert_int_sat(double a) __asm("air.convert.s.i32.f.f64.sat");
  __AIR_ASM__ int2 convert_int2_sat(double2 a) __asm("air.convert.s.v2i32.f.v2f64.sat");
  __AIR_ASM__ int3 convert_int3_sat(double3 a) __asm("air.convert.s.v3i32.f.v3f64.sat");
  __AIR_ASM__ int4 convert_int4_sat(double4 a) __asm("air.convert.s.v4i32.f.v4f64.sat");
  __AIR_ASM__ int convert_int_rtz(double a) __asm("air.convert.s.i32.f.f64.rtz");
  __AIR_ASM__ int2 convert_int2_rtz(double2 a) __asm("air.convert.s.v2i32.f.v2f64.rtz");
  __AIR_ASM__ int3 convert_int3_rtz(double3 a) __asm("air.convert.s.v3i32.f.v3f64.rtz");
  __AIR_ASM__ int4 convert_int4_rtz(double4 a) __asm("air.convert.s.v4i32.f.v4f64.rtz");
  __AIR_ASM__ int convert_int_rtn(double a) __asm("air.convert.s.i32.f.f64.rtn");
  __AIR_ASM__ int2 convert_int2_rtn(double2 a) __asm("air.convert.s.v2i32.f.v2f64.rtn");
  __AIR_ASM__ int3 convert_int3_rtn(double3 a) __asm("air.convert.s.v3i32.f.v3f64.rtn");
  __AIR_ASM__ int4 convert_int4_rtn(double4 a) __asm("air.convert.s.v4i32.f.v4f64.rtn");
  __AIR_ASM__ int convert_int_rtp(double a) __asm("air.convert.s.i32.f.f64.rtp");
  __AIR_ASM__ int2 convert_int2_rtp(double2 a) __asm("air.convert.s.v2i32.f.v2f64.rtp");
  __AIR_ASM__ int3 convert_int3_rtp(double3 a) __asm("air.convert.s.v3i32.f.v3f64.rtp");
  __AIR_ASM__ int4 convert_int4_rtp(double4 a) __asm("air.convert.s.v4i32.f.v4f64.rtp");
  __AIR_ASM__ int convert_int_rte(double a) __asm("air.convert.s.i32.f.f64.rte");
  __AIR_ASM__ int2 convert_int2_rte(double2 a) __asm("air.convert.s.v2i32.f.v2f64.rte");
  __AIR_ASM__ int3 convert_int3_rte(double3 a) __asm("air.convert.s.v3i32.f.v3f64.rte");
  __AIR_ASM__ int4 convert_int4_rte(double4 a) __asm("air.convert.s.v4i32.f.v4f64.rte");
  __AIR_ASM__ int convert_int(double a) __asm("air.convert.s.i32.f.f64");
  __AIR_ASM__ int2 convert_int2(double2 a) __asm("air.convert.s.v2i32.f.v2f64");
  __AIR_ASM__ int3 convert_int3(double3 a) __asm("air.convert.s.v3i32.f.v3f64");
  __AIR_ASM__ int4 convert_int4(double4 a) __asm("air.convert.s.v4i32.f.v4f64");
  __AIR_ASM__ uint convert_uint_sat_rtz(double a) __asm("air.convert.u.i32.f.f64.rtz.sat");
  __AIR_ASM__ uint2 convert_uint2_sat_rtz(double2 a) __asm("air.convert.u.v2i32.f.v2f64.rtz.sat");
  __AIR_ASM__ uint3 convert_uint3_sat_rtz(double3 a) __asm("air.convert.u.v3i32.f.v3f64.rtz.sat");
  __AIR_ASM__ uint4 convert_uint4_sat_rtz(double4 a) __asm("air.convert.u.v4i32.f.v4f64.rtz.sat");
  __AIR_ASM__ uint convert_uint_sat_rtn(double a) __asm("air.convert.u.i32.f.f64.rtn.sat");
  __AIR_ASM__ uint2 convert_uint2_sat_rtn(double2 a) __asm("air.convert.u.v2i32.f.v2f64.rtn.sat");
  __AIR_ASM__ uint3 convert_uint3_sat_rtn(double3 a) __asm("air.convert.u.v3i32.f.v3f64.rtn.sat");
  __AIR_ASM__ uint4 convert_uint4_sat_rtn(double4 a) __asm("air.convert.u.v4i32.f.v4f64.rtn.sat");
  __AIR_ASM__ uint convert_uint_sat_rtp(double a) __asm("air.convert.u.i32.f.f64.rtp.sat");
  __AIR_ASM__ uint2 convert_uint2_sat_rtp(double2 a) __asm("air.convert.u.v2i32.f.v2f64.rtp.sat");
  __AIR_ASM__ uint3 convert_uint3_sat_rtp(double3 a) __asm("air.convert.u.v3i32.f.v3f64.rtp.sat");
  __AIR_ASM__ uint4 convert_uint4_sat_rtp(double4 a) __asm("air.convert.u.v4i32.f.v4f64.rtp.sat");
  __AIR_ASM__ uint convert_uint_sat_rte(double a) __asm("air.convert.u.i32.f.f64.rte.sat");
  __AIR_ASM__ uint2 convert_uint2_sat_rte(double2 a) __asm("air.convert.u.v2i32.f.v2f64.rte.sat");
  __AIR_ASM__ uint3 convert_uint3_sat_rte(double3 a) __asm("air.convert.u.v3i32.f.v3f64.rte.sat");
  __AIR_ASM__ uint4 convert_uint4_sat_rte(double4 a) __asm("air.convert.u.v4i32.f.v4f64.rte.sat");
  __AIR_ASM__ uint convert_uint_sat(double a) __asm("air.convert.u.i32.f.f64.sat");
  __AIR_ASM__ uint2 convert_uint2_sat(double2 a) __asm("air.convert.u.v2i32.f.v2f64.sat");
  __AIR_ASM__ uint3 convert_uint3_sat(double3 a) __asm("air.convert.u.v3i32.f.v3f64.sat");
  __AIR_ASM__ uint4 convert_uint4_sat(double4 a) __asm("air.convert.u.v4i32.f.v4f64.sat");
  __AIR_ASM__ uint convert_uint_rtz(double a) __asm("air.convert.u.i32.f.f64.rtz");
  __AIR_ASM__ uint2 convert_uint2_rtz(double2 a) __asm("air.convert.u.v2i32.f.v2f64.rtz");
  __AIR_ASM__ uint3 convert_uint3_rtz(double3 a) __asm("air.convert.u.v3i32.f.v3f64.rtz");
  __AIR_ASM__ uint4 convert_uint4_rtz(double4 a) __asm("air.convert.u.v4i32.f.v4f64.rtz");
  __AIR_ASM__ uint convert_uint_rtn(double a) __asm("air.convert.u.i32.f.f64.rtn");
  __AIR_ASM__ uint2 convert_uint2_rtn(double2 a) __asm("air.convert.u.v2i32.f.v2f64.rtn");
  __AIR_ASM__ uint3 convert_uint3_rtn(double3 a) __asm("air.convert.u.v3i32.f.v3f64.rtn");
  __AIR_ASM__ uint4 convert_uint4_rtn(double4 a) __asm("air.convert.u.v4i32.f.v4f64.rtn");
  __AIR_ASM__ uint convert_uint_rtp(double a) __asm("air.convert.u.i32.f.f64.rtp");
  __AIR_ASM__ uint2 convert_uint2_rtp(double2 a) __asm("air.convert.u.v2i32.f.v2f64.rtp");
  __AIR_ASM__ uint3 convert_uint3_rtp(double3 a) __asm("air.convert.u.v3i32.f.v3f64.rtp");
  __AIR_ASM__ uint4 convert_uint4_rtp(double4 a) __asm("air.convert.u.v4i32.f.v4f64.rtp");
  __AIR_ASM__ uint convert_uint_rte(double a) __asm("air.convert.u.i32.f.f64.rte");
  __AIR_ASM__ uint2 convert_uint2_rte(double2 a) __asm("air.convert.u.v2i32.f.v2f64.rte");
  __AIR_ASM__ uint3 convert_uint3_rte(double3 a) __asm("air.convert.u.v3i32.f.v3f64.rte");
  __AIR_ASM__ uint4 convert_uint4_rte(double4 a) __asm("air.convert.u.v4i32.f.v4f64.rte");
  __AIR_ASM__ uint convert_uint(double a) __asm("air.convert.u.i32.f.f64");
  __AIR_ASM__ uint2 convert_uint2(double2 a) __asm("air.convert.u.v2i32.f.v2f64");
  __AIR_ASM__ uint3 convert_uint3(double3 a) __asm("air.convert.u.v3i32.f.v3f64");
  __AIR_ASM__ uint4 convert_uint4(double4 a) __asm("air.convert.u.v4i32.f.v4f64");
  __AIR_ASM__ long convert_long_sat_rtz(double a) __asm("air.convert.s.i64.f.f64.rtz.sat");
  __AIR_ASM__ long2 convert_long2_sat_rtz(double2 a) __asm("air.convert.s.v2i64.f.v2f64.rtz.sat");
  __AIR_ASM__ long3 convert_long3_sat_rtz(double3 a) __asm("air.convert.s.v3i64.f.v3f64.rtz.sat");
  __AIR_ASM__ long4 convert_long4_sat_rtz(double4 a) __asm("air.convert.s.v4i64.f.v4f64.rtz.sat");
  __AIR_ASM__ long convert_long_sat_rtn(double a) __asm("air.convert.s.i64.f.f64.rtn.sat");
  __AIR_ASM__ long2 convert_long2_sat_rtn(double2 a) __asm("air.convert.s.v2i64.f.v2f64.rtn.sat");
  __AIR_ASM__ long3 convert_long3_sat_rtn(double3 a) __asm("air.convert.s.v3i64.f.v3f64.rtn.sat");
  __AIR_ASM__ long4 convert_long4_sat_rtn(double4 a) __asm("air.convert.s.v4i64.f.v4f64.rtn.sat");
  __AIR_ASM__ long convert_long_sat_rtp(double a) __asm("air.convert.s.i64.f.f64.rtp.sat");
  __AIR_ASM__ long2 convert_long2_sat_rtp(double2 a) __asm("air.convert.s.v2i64.f.v2f64.rtp.sat");
  __AIR_ASM__ long3 convert_long3_sat_rtp(double3 a) __asm("air.convert.s.v3i64.f.v3f64.rtp.sat");
  __AIR_ASM__ long4 convert_long4_sat_rtp(double4 a) __asm("air.convert.s.v4i64.f.v4f64.rtp.sat");
  __AIR_ASM__ long convert_long_sat_rte(double a) __asm("air.convert.s.i64.f.f64.rte.sat");
  __AIR_ASM__ long2 convert_long2_sat_rte(double2 a) __asm("air.convert.s.v2i64.f.v2f64.rte.sat");
  __AIR_ASM__ long3 convert_long3_sat_rte(double3 a) __asm("air.convert.s.v3i64.f.v3f64.rte.sat");
  __AIR_ASM__ long4 convert_long4_sat_rte(double4 a) __asm("air.convert.s.v4i64.f.v4f64.rte.sat");
  __AIR_ASM__ long convert_long_sat(double a) __asm("air.convert.s.i64.f.f64.sat");
  __AIR_ASM__ long2 convert_long2_sat(double2 a) __asm("air.convert.s.v2i64.f.v2f64.sat");
  __AIR_ASM__ long3 convert_long3_sat(double3 a) __asm("air.convert.s.v3i64.f.v3f64.sat");
  __AIR_ASM__ long4 convert_long4_sat(double4 a) __asm("air.convert.s.v4i64.f.v4f64.sat");
  __AIR_ASM__ long convert_long_rtz(double a) __asm("air.convert.s.i64.f.f64.rtz");
  __AIR_ASM__ long2 convert_long2_rtz(double2 a) __asm("air.convert.s.v2i64.f.v2f64.rtz");
  __AIR_ASM__ long3 convert_long3_rtz(double3 a) __asm("air.convert.s.v3i64.f.v3f64.rtz");
  __AIR_ASM__ long4 convert_long4_rtz(double4 a) __asm("air.convert.s.v4i64.f.v4f64.rtz");
  __AIR_ASM__ long convert_long_rtn(double a) __asm("air.convert.s.i64.f.f64.rtn");
  __AIR_ASM__ long2 convert_long2_rtn(double2 a) __asm("air.convert.s.v2i64.f.v2f64.rtn");
  __AIR_ASM__ long3 convert_long3_rtn(double3 a) __asm("air.convert.s.v3i64.f.v3f64.rtn");
  __AIR_ASM__ long4 convert_long4_rtn(double4 a) __asm("air.convert.s.v4i64.f.v4f64.rtn");
  __AIR_ASM__ long convert_long_rtp(double a) __asm("air.convert.s.i64.f.f64.rtp");
  __AIR_ASM__ long2 convert_long2_rtp(double2 a) __asm("air.convert.s.v2i64.f.v2f64.rtp");
  __AIR_ASM__ long3 convert_long3_rtp(double3 a) __asm("air.convert.s.v3i64.f.v3f64.rtp");
  __AIR_ASM__ long4 convert_long4_rtp(double4 a) __asm("air.convert.s.v4i64.f.v4f64.rtp");
  __AIR_ASM__ long convert_long_rte(double a) __asm("air.convert.s.i64.f.f64.rte");
  __AIR_ASM__ long2 convert_long2_rte(double2 a) __asm("air.convert.s.v2i64.f.v2f64.rte");
  __AIR_ASM__ long3 convert_long3_rte(double3 a) __asm("air.convert.s.v3i64.f.v3f64.rte");
  __AIR_ASM__ long4 convert_long4_rte(double4 a) __asm("air.convert.s.v4i64.f.v4f64.rte");
  __AIR_ASM__ long convert_long(double a) __asm("air.convert.s.i64.f.f64");
  __AIR_ASM__ long2 convert_long2(double2 a) __asm("air.convert.s.v2i64.f.v2f64");
  __AIR_ASM__ long3 convert_long3(double3 a) __asm("air.convert.s.v3i64.f.v3f64");
  __AIR_ASM__ long4 convert_long4(double4 a) __asm("air.convert.s.v4i64.f.v4f64");
  __AIR_ASM__ ulong convert_ulong_sat_rtz(double a) __asm("air.convert.u.i64.f.f64.rtz.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat_rtz(double2 a) __asm("air.convert.u.v2i64.f.v2f64.rtz.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat_rtz(double3 a) __asm("air.convert.u.v3i64.f.v3f64.rtz.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat_rtz(double4 a) __asm("air.convert.u.v4i64.f.v4f64.rtz.sat");
  __AIR_ASM__ ulong convert_ulong_sat_rtn(double a) __asm("air.convert.u.i64.f.f64.rtn.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat_rtn(double2 a) __asm("air.convert.u.v2i64.f.v2f64.rtn.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat_rtn(double3 a) __asm("air.convert.u.v3i64.f.v3f64.rtn.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat_rtn(double4 a) __asm("air.convert.u.v4i64.f.v4f64.rtn.sat");
  __AIR_ASM__ ulong convert_ulong_sat_rtp(double a) __asm("air.convert.u.i64.f.f64.rtp.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat_rtp(double2 a) __asm("air.convert.u.v2i64.f.v2f64.rtp.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat_rtp(double3 a) __asm("air.convert.u.v3i64.f.v3f64.rtp.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat_rtp(double4 a) __asm("air.convert.u.v4i64.f.v4f64.rtp.sat");
  __AIR_ASM__ ulong convert_ulong_sat_rte(double a) __asm("air.convert.u.i64.f.f64.rte.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat_rte(double2 a) __asm("air.convert.u.v2i64.f.v2f64.rte.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat_rte(double3 a) __asm("air.convert.u.v3i64.f.v3f64.rte.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat_rte(double4 a) __asm("air.convert.u.v4i64.f.v4f64.rte.sat");
  __AIR_ASM__ ulong convert_ulong_sat(double a) __asm("air.convert.u.i64.f.f64.sat");
  __AIR_ASM__ ulong2 convert_ulong2_sat(double2 a) __asm("air.convert.u.v2i64.f.v2f64.sat");
  __AIR_ASM__ ulong3 convert_ulong3_sat(double3 a) __asm("air.convert.u.v3i64.f.v3f64.sat");
  __AIR_ASM__ ulong4 convert_ulong4_sat(double4 a) __asm("air.convert.u.v4i64.f.v4f64.sat");
  __AIR_ASM__ ulong convert_ulong_rtz(double a) __asm("air.convert.u.i64.f.f64.rtz");
  __AIR_ASM__ ulong2 convert_ulong2_rtz(double2 a) __asm("air.convert.u.v2i64.f.v2f64.rtz");
  __AIR_ASM__ ulong3 convert_ulong3_rtz(double3 a) __asm("air.convert.u.v3i64.f.v3f64.rtz");
  __AIR_ASM__ ulong4 convert_ulong4_rtz(double4 a) __asm("air.convert.u.v4i64.f.v4f64.rtz");
  __AIR_ASM__ ulong convert_ulong_rtn(double a) __asm("air.convert.u.i64.f.f64.rtn");
  __AIR_ASM__ ulong2 convert_ulong2_rtn(double2 a) __asm("air.convert.u.v2i64.f.v2f64.rtn");
  __AIR_ASM__ ulong3 convert_ulong3_rtn(double3 a) __asm("air.convert.u.v3i64.f.v3f64.rtn");
  __AIR_ASM__ ulong4 convert_ulong4_rtn(double4 a) __asm("air.convert.u.v4i64.f.v4f64.rtn");
  __AIR_ASM__ ulong convert_ulong_rtp(double a) __asm("air.convert.u.i64.f.f64.rtp");
  __AIR_ASM__ ulong2 convert_ulong2_rtp(double2 a) __asm("air.convert.u.v2i64.f.v2f64.rtp");
  __AIR_ASM__ ulong3 convert_ulong3_rtp(double3 a) __asm("air.convert.u.v3i64.f.v3f64.rtp");
  __AIR_ASM__ ulong4 convert_ulong4_rtp(double4 a) __asm("air.convert.u.v4i64.f.v4f64.rtp");
  __AIR_ASM__ ulong convert_ulong_rte(double a) __asm("air.convert.u.i64.f.f64.rte");
  __AIR_ASM__ ulong2 convert_ulong2_rte(double2 a) __asm("air.convert.u.v2i64.f.v2f64.rte");
  __AIR_ASM__ ulong3 convert_ulong3_rte(double3 a) __asm("air.convert.u.v3i64.f.v3f64.rte");
  __AIR_ASM__ ulong4 convert_ulong4_rte(double4 a) __asm("air.convert.u.v4i64.f.v4f64.rte");
  __AIR_ASM__ ulong convert_ulong(double a) __asm("air.convert.u.i64.f.f64");
  __AIR_ASM__ ulong2 convert_ulong2(double2 a) __asm("air.convert.u.v2i64.f.v2f64");
  __AIR_ASM__ ulong3 convert_ulong3(double3 a) __asm("air.convert.u.v3i64.f.v3f64");
  __AIR_ASM__ ulong4 convert_ulong4(double4 a) __asm("air.convert.u.v4i64.f.v4f64");
  __AIR_ASM__ double convert_double_rtz(char a) __asm("air.convert.f.f64.s.i8.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(char2 a) __asm("air.convert.f.v2f64.s.v2i8.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(char3 a) __asm("air.convert.f.v3f64.s.v3i8.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(char4 a) __asm("air.convert.f.v4f64.s.v4i8.rtz");
  __AIR_ASM__ double convert_double_rtn(char a) __asm("air.convert.f.f64.s.i8.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(char2 a) __asm("air.convert.f.v2f64.s.v2i8.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(char3 a) __asm("air.convert.f.v3f64.s.v3i8.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(char4 a) __asm("air.convert.f.v4f64.s.v4i8.rtn");
  __AIR_ASM__ double convert_double_rtp(char a) __asm("air.convert.f.f64.s.i8.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(char2 a) __asm("air.convert.f.v2f64.s.v2i8.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(char3 a) __asm("air.convert.f.v3f64.s.v3i8.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(char4 a) __asm("air.convert.f.v4f64.s.v4i8.rtp");
  __AIR_ASM__ double convert_double_rte(char a) __asm("air.convert.f.f64.s.i8.rte");
  __AIR_ASM__ double2 convert_double2_rte(char2 a) __asm("air.convert.f.v2f64.s.v2i8.rte");
  __AIR_ASM__ double3 convert_double3_rte(char3 a) __asm("air.convert.f.v3f64.s.v3i8.rte");
  __AIR_ASM__ double4 convert_double4_rte(char4 a) __asm("air.convert.f.v4f64.s.v4i8.rte");
  __AIR_ASM__ double convert_double(char a) __asm("air.convert.f.f64.s.i8");
  __AIR_ASM__ double2 convert_double2(char2 a) __asm("air.convert.f.v2f64.s.v2i8");
  __AIR_ASM__ double3 convert_double3(char3 a) __asm("air.convert.f.v3f64.s.v3i8");
  __AIR_ASM__ double4 convert_double4(char4 a) __asm("air.convert.f.v4f64.s.v4i8");
  __AIR_ASM__ double convert_double_rtz(uchar a) __asm("air.convert.f.f64.u.i8.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(uchar2 a) __asm("air.convert.f.v2f64.u.v2i8.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(uchar3 a) __asm("air.convert.f.v3f64.u.v3i8.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(uchar4 a) __asm("air.convert.f.v4f64.u.v4i8.rtz");
  __AIR_ASM__ double convert_double_rtn(uchar a) __asm("air.convert.f.f64.u.i8.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(uchar2 a) __asm("air.convert.f.v2f64.u.v2i8.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(uchar3 a) __asm("air.convert.f.v3f64.u.v3i8.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(uchar4 a) __asm("air.convert.f.v4f64.u.v4i8.rtn");
  __AIR_ASM__ double convert_double_rtp(uchar a) __asm("air.convert.f.f64.u.i8.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(uchar2 a) __asm("air.convert.f.v2f64.u.v2i8.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(uchar3 a) __asm("air.convert.f.v3f64.u.v3i8.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(uchar4 a) __asm("air.convert.f.v4f64.u.v4i8.rtp");
  __AIR_ASM__ double convert_double_rte(uchar a) __asm("air.convert.f.f64.u.i8.rte");
  __AIR_ASM__ double2 convert_double2_rte(uchar2 a) __asm("air.convert.f.v2f64.u.v2i8.rte");
  __AIR_ASM__ double3 convert_double3_rte(uchar3 a) __asm("air.convert.f.v3f64.u.v3i8.rte");
  __AIR_ASM__ double4 convert_double4_rte(uchar4 a) __asm("air.convert.f.v4f64.u.v4i8.rte");
  __AIR_ASM__ double convert_double(uchar a) __asm("air.convert.f.f64.u.i8");
  __AIR_ASM__ double2 convert_double2(uchar2 a) __asm("air.convert.f.v2f64.u.v2i8");
  __AIR_ASM__ double3 convert_double3(uchar3 a) __asm("air.convert.f.v3f64.u.v3i8");
  __AIR_ASM__ double4 convert_double4(uchar4 a) __asm("air.convert.f.v4f64.u.v4i8");
  __AIR_ASM__ double convert_double_rtz(short a) __asm("air.convert.f.f64.s.i16.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(short2 a) __asm("air.convert.f.v2f64.s.v2i16.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(short3 a) __asm("air.convert.f.v3f64.s.v3i16.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(short4 a) __asm("air.convert.f.v4f64.s.v4i16.rtz");
  __AIR_ASM__ double convert_double_rtn(short a) __asm("air.convert.f.f64.s.i16.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(short2 a) __asm("air.convert.f.v2f64.s.v2i16.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(short3 a) __asm("air.convert.f.v3f64.s.v3i16.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(short4 a) __asm("air.convert.f.v4f64.s.v4i16.rtn");
  __AIR_ASM__ double convert_double_rtp(short a) __asm("air.convert.f.f64.s.i16.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(short2 a) __asm("air.convert.f.v2f64.s.v2i16.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(short3 a) __asm("air.convert.f.v3f64.s.v3i16.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(short4 a) __asm("air.convert.f.v4f64.s.v4i16.rtp");
  __AIR_ASM__ double convert_double_rte(short a) __asm("air.convert.f.f64.s.i16.rte");
  __AIR_ASM__ double2 convert_double2_rte(short2 a) __asm("air.convert.f.v2f64.s.v2i16.rte");
  __AIR_ASM__ double3 convert_double3_rte(short3 a) __asm("air.convert.f.v3f64.s.v3i16.rte");
  __AIR_ASM__ double4 convert_double4_rte(short4 a) __asm("air.convert.f.v4f64.s.v4i16.rte");
  __AIR_ASM__ double convert_double(short a) __asm("air.convert.f.f64.s.i16");
  __AIR_ASM__ double2 convert_double2(short2 a) __asm("air.convert.f.v2f64.s.v2i16");
  __AIR_ASM__ double3 convert_double3(short3 a) __asm("air.convert.f.v3f64.s.v3i16");
  __AIR_ASM__ double4 convert_double4(short4 a) __asm("air.convert.f.v4f64.s.v4i16");
  __AIR_ASM__ double convert_double_rtz(ushort a) __asm("air.convert.f.f64.u.i16.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(ushort2 a) __asm("air.convert.f.v2f64.u.v2i16.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(ushort3 a) __asm("air.convert.f.v3f64.u.v3i16.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(ushort4 a) __asm("air.convert.f.v4f64.u.v4i16.rtz");
  __AIR_ASM__ double convert_double_rtn(ushort a) __asm("air.convert.f.f64.u.i16.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(ushort2 a) __asm("air.convert.f.v2f64.u.v2i16.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(ushort3 a) __asm("air.convert.f.v3f64.u.v3i16.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(ushort4 a) __asm("air.convert.f.v4f64.u.v4i16.rtn");
  __AIR_ASM__ double convert_double_rtp(ushort a) __asm("air.convert.f.f64.u.i16.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(ushort2 a) __asm("air.convert.f.v2f64.u.v2i16.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(ushort3 a) __asm("air.convert.f.v3f64.u.v3i16.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(ushort4 a) __asm("air.convert.f.v4f64.u.v4i16.rtp");
  __AIR_ASM__ double convert_double_rte(ushort a) __asm("air.convert.f.f64.u.i16.rte");
  __AIR_ASM__ double2 convert_double2_rte(ushort2 a) __asm("air.convert.f.v2f64.u.v2i16.rte");
  __AIR_ASM__ double3 convert_double3_rte(ushort3 a) __asm("air.convert.f.v3f64.u.v3i16.rte");
  __AIR_ASM__ double4 convert_double4_rte(ushort4 a) __asm("air.convert.f.v4f64.u.v4i16.rte");
  __AIR_ASM__ double convert_double(ushort a) __asm("air.convert.f.f64.u.i16");
  __AIR_ASM__ double2 convert_double2(ushort2 a) __asm("air.convert.f.v2f64.u.v2i16");
  __AIR_ASM__ double3 convert_double3(ushort3 a) __asm("air.convert.f.v3f64.u.v3i16");
  __AIR_ASM__ double4 convert_double4(ushort4 a) __asm("air.convert.f.v4f64.u.v4i16");
  __AIR_ASM__ double convert_double_rtz(int a) __asm("air.convert.f.f64.s.i32.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(int2 a) __asm("air.convert.f.v2f64.s.v2i32.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(int3 a) __asm("air.convert.f.v3f64.s.v3i32.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(int4 a) __asm("air.convert.f.v4f64.s.v4i32.rtz");
  __AIR_ASM__ double convert_double_rtn(int a) __asm("air.convert.f.f64.s.i32.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(int2 a) __asm("air.convert.f.v2f64.s.v2i32.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(int3 a) __asm("air.convert.f.v3f64.s.v3i32.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(int4 a) __asm("air.convert.f.v4f64.s.v4i32.rtn");
  __AIR_ASM__ double convert_double_rtp(int a) __asm("air.convert.f.f64.s.i32.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(int2 a) __asm("air.convert.f.v2f64.s.v2i32.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(int3 a) __asm("air.convert.f.v3f64.s.v3i32.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(int4 a) __asm("air.convert.f.v4f64.s.v4i32.rtp");
  __AIR_ASM__ double convert_double_rte(int a) __asm("air.convert.f.f64.s.i32.rte");
  __AIR_ASM__ double2 convert_double2_rte(int2 a) __asm("air.convert.f.v2f64.s.v2i32.rte");
  __AIR_ASM__ double3 convert_double3_rte(int3 a) __asm("air.convert.f.v3f64.s.v3i32.rte");
  __AIR_ASM__ double4 convert_double4_rte(int4 a) __asm("air.convert.f.v4f64.s.v4i32.rte");
  __AIR_ASM__ double convert_double(int a) __asm("air.convert.f.f64.s.i32");
  __AIR_ASM__ double2 convert_double2(int2 a) __asm("air.convert.f.v2f64.s.v2i32");
  __AIR_ASM__ double3 convert_double3(int3 a) __asm("air.convert.f.v3f64.s.v3i32");
  __AIR_ASM__ double4 convert_double4(int4 a) __asm("air.convert.f.v4f64.s.v4i32");
  __AIR_ASM__ double convert_double_rtz(uint a) __asm("air.convert.f.f64.u.i32.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(uint2 a) __asm("air.convert.f.v2f64.u.v2i32.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(uint3 a) __asm("air.convert.f.v3f64.u.v3i32.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(uint4 a) __asm("air.convert.f.v4f64.u.v4i32.rtz");
  __AIR_ASM__ double convert_double_rtn(uint a) __asm("air.convert.f.f64.u.i32.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(uint2 a) __asm("air.convert.f.v2f64.u.v2i32.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(uint3 a) __asm("air.convert.f.v3f64.u.v3i32.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(uint4 a) __asm("air.convert.f.v4f64.u.v4i32.rtn");
  __AIR_ASM__ double convert_double_rtp(uint a) __asm("air.convert.f.f64.u.i32.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(uint2 a) __asm("air.convert.f.v2f64.u.v2i32.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(uint3 a) __asm("air.convert.f.v3f64.u.v3i32.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(uint4 a) __asm("air.convert.f.v4f64.u.v4i32.rtp");
  __AIR_ASM__ double convert_double_rte(uint a) __asm("air.convert.f.f64.u.i32.rte");
  __AIR_ASM__ double2 convert_double2_rte(uint2 a) __asm("air.convert.f.v2f64.u.v2i32.rte");
  __AIR_ASM__ double3 convert_double3_rte(uint3 a) __asm("air.convert.f.v3f64.u.v3i32.rte");
  __AIR_ASM__ double4 convert_double4_rte(uint4 a) __asm("air.convert.f.v4f64.u.v4i32.rte");
  __AIR_ASM__ double convert_double(uint a) __asm("air.convert.f.f64.u.i32");
  __AIR_ASM__ double2 convert_double2(uint2 a) __asm("air.convert.f.v2f64.u.v2i32");
  __AIR_ASM__ double3 convert_double3(uint3 a) __asm("air.convert.f.v3f64.u.v3i32");
  __AIR_ASM__ double4 convert_double4(uint4 a) __asm("air.convert.f.v4f64.u.v4i32");
  __AIR_ASM__ double convert_double_rtz(long a) __asm("air.convert.f.f64.s.i64.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(long2 a) __asm("air.convert.f.v2f64.s.v2i64.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(long3 a) __asm("air.convert.f.v3f64.s.v3i64.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(long4 a) __asm("air.convert.f.v4f64.s.v4i64.rtz");
  __AIR_ASM__ double convert_double_rtn(long a) __asm("air.convert.f.f64.s.i64.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(long2 a) __asm("air.convert.f.v2f64.s.v2i64.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(long3 a) __asm("air.convert.f.v3f64.s.v3i64.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(long4 a) __asm("air.convert.f.v4f64.s.v4i64.rtn");
  __AIR_ASM__ double convert_double_rtp(long a) __asm("air.convert.f.f64.s.i64.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(long2 a) __asm("air.convert.f.v2f64.s.v2i64.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(long3 a) __asm("air.convert.f.v3f64.s.v3i64.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(long4 a) __asm("air.convert.f.v4f64.s.v4i64.rtp");
  __AIR_ASM__ double convert_double_rte(long a) __asm("air.convert.f.f64.s.i64.rte");
  __AIR_ASM__ double2 convert_double2_rte(long2 a) __asm("air.convert.f.v2f64.s.v2i64.rte");
  __AIR_ASM__ double3 convert_double3_rte(long3 a) __asm("air.convert.f.v3f64.s.v3i64.rte");
  __AIR_ASM__ double4 convert_double4_rte(long4 a) __asm("air.convert.f.v4f64.s.v4i64.rte");
  __AIR_ASM__ double convert_double(long a) __asm("air.convert.f.f64.s.i64");
  __AIR_ASM__ double2 convert_double2(long2 a) __asm("air.convert.f.v2f64.s.v2i64");
  __AIR_ASM__ double3 convert_double3(long3 a) __asm("air.convert.f.v3f64.s.v3i64");
  __AIR_ASM__ double4 convert_double4(long4 a) __asm("air.convert.f.v4f64.s.v4i64");
  __AIR_ASM__ double convert_double_rtz(ulong a) __asm("air.convert.f.f64.u.i64.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(ulong2 a) __asm("air.convert.f.v2f64.u.v2i64.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(ulong3 a) __asm("air.convert.f.v3f64.u.v3i64.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(ulong4 a) __asm("air.convert.f.v4f64.u.v4i64.rtz");
  __AIR_ASM__ double convert_double_rtn(ulong a) __asm("air.convert.f.f64.u.i64.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(ulong2 a) __asm("air.convert.f.v2f64.u.v2i64.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(ulong3 a) __asm("air.convert.f.v3f64.u.v3i64.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(ulong4 a) __asm("air.convert.f.v4f64.u.v4i64.rtn");
  __AIR_ASM__ double convert_double_rtp(ulong a) __asm("air.convert.f.f64.u.i64.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(ulong2 a) __asm("air.convert.f.v2f64.u.v2i64.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(ulong3 a) __asm("air.convert.f.v3f64.u.v3i64.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(ulong4 a) __asm("air.convert.f.v4f64.u.v4i64.rtp");
  __AIR_ASM__ double convert_double_rte(ulong a) __asm("air.convert.f.f64.u.i64.rte");
  __AIR_ASM__ double2 convert_double2_rte(ulong2 a) __asm("air.convert.f.v2f64.u.v2i64.rte");
  __AIR_ASM__ double3 convert_double3_rte(ulong3 a) __asm("air.convert.f.v3f64.u.v3i64.rte");
  __AIR_ASM__ double4 convert_double4_rte(ulong4 a) __asm("air.convert.f.v4f64.u.v4i64.rte");
  __AIR_ASM__ double convert_double(ulong a) __asm("air.convert.f.f64.u.i64");
  __AIR_ASM__ double2 convert_double2(ulong2 a) __asm("air.convert.f.v2f64.u.v2i64");
  __AIR_ASM__ double3 convert_double3(ulong3 a) __asm("air.convert.f.v3f64.u.v3i64");
  __AIR_ASM__ double4 convert_double4(ulong4 a) __asm("air.convert.f.v4f64.u.v4i64");
  __AIR_ASM__ double convert_double_rtz(double a) __asm("air.convert.f.f64.f.f64.rtz");
  __AIR_ASM__ double2 convert_double2_rtz(double2 a) __asm("air.convert.f.v2f64.f.v2f64.rtz");
  __AIR_ASM__ double3 convert_double3_rtz(double3 a) __asm("air.convert.f.v3f64.f.v3f64.rtz");
  __AIR_ASM__ double4 convert_double4_rtz(double4 a) __asm("air.convert.f.v4f64.f.v4f64.rtz");
  __AIR_ASM__ double convert_double_rtn(double a) __asm("air.convert.f.f64.f.f64.rtn");
  __AIR_ASM__ double2 convert_double2_rtn(double2 a) __asm("air.convert.f.v2f64.f.v2f64.rtn");
  __AIR_ASM__ double3 convert_double3_rtn(double3 a) __asm("air.convert.f.v3f64.f.v3f64.rtn");
  __AIR_ASM__ double4 convert_double4_rtn(double4 a) __asm("air.convert.f.v4f64.f.v4f64.rtn");
  __AIR_ASM__ double convert_double_rtp(double a) __asm("air.convert.f.f64.f.f64.rtp");
  __AIR_ASM__ double2 convert_double2_rtp(double2 a) __asm("air.convert.f.v2f64.f.v2f64.rtp");
  __AIR_ASM__ double3 convert_double3_rtp(double3 a) __asm("air.convert.f.v3f64.f.v3f64.rtp");
  __AIR_ASM__ double4 convert_double4_rtp(double4 a) __asm("air.convert.f.v4f64.f.v4f64.rtp");
  __AIR_ASM__ double convert_double_rte(double a) __asm("air.convert.f.f64.f.f64.rte");
  __AIR_ASM__ double2 convert_double2_rte(double2 a) __asm("air.convert.f.v2f64.f.v2f64.rte");
  __AIR_ASM__ double3 convert_double3_rte(double3 a) __asm("air.convert.f.v3f64.f.v3f64.rte");
  __AIR_ASM__ double4 convert_double4_rte(double4 a) __asm("air.convert.f.v4f64.f.v4f64.rte");
  __AIR_ASM__ double convert_double(double a) __asm("air.convert.f.f64.f.f64");
  __AIR_ASM__ double2 convert_double2(double2 a) __asm("air.convert.f.v2f64.f.v2f64");
  __AIR_ASM__ double3 convert_double3(double3 a) __asm("air.convert.f.v3f64.f.v3f64");
  __AIR_ASM__ double4 convert_double4(double4 a) __asm("air.convert.f.v4f64.f.v4f64");


  __AIR_FUNC__ char8 convert_char8_sat_rtz(double8 a) {
    char8 r;
    r.hi = convert_char4_sat_rtz(a.hi);
    r.lo = convert_char4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat_rtz(double16 a) {
    char16 r;
    r.hi = convert_char8_sat_rtz(a.hi);
    r.lo = convert_char8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat_rtn(double8 a) {
    char8 r;
    r.hi = convert_char4_sat_rtn(a.hi);
    r.lo = convert_char4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat_rtn(double16 a) {
    char16 r;
    r.hi = convert_char8_sat_rtn(a.hi);
    r.lo = convert_char8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat_rtp(double8 a) {
    char8 r;
    r.hi = convert_char4_sat_rtp(a.hi);
    r.lo = convert_char4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat_rtp(double16 a) {
    char16 r;
    r.hi = convert_char8_sat_rtp(a.hi);
    r.lo = convert_char8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat_rte(double8 a) {
    char8 r;
    r.hi = convert_char4_sat_rte(a.hi);
    r.lo = convert_char4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat_rte(double16 a) {
    char16 r;
    r.hi = convert_char8_sat_rte(a.hi);
    r.lo = convert_char8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_sat(double8 a) {
    char8 r;
    r.hi = convert_char4_sat(a.hi);
    r.lo = convert_char4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_sat(double16 a) {
    char16 r;
    r.hi = convert_char8_sat(a.hi);
    r.lo = convert_char8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_rtz(double8 a) {
    char8 r;
    r.hi = convert_char4_rtz(a.hi);
    r.lo = convert_char4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_rtz(double16 a) {
    char16 r;
    r.hi = convert_char8_rtz(a.hi);
    r.lo = convert_char8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_rtn(double8 a) {
    char8 r;
    r.hi = convert_char4_rtn(a.hi);
    r.lo = convert_char4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_rtn(double16 a) {
    char16 r;
    r.hi = convert_char8_rtn(a.hi);
    r.lo = convert_char8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_rtp(double8 a) {
    char8 r;
    r.hi = convert_char4_rtp(a.hi);
    r.lo = convert_char4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_rtp(double16 a) {
    char16 r;
    r.hi = convert_char8_rtp(a.hi);
    r.lo = convert_char8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8_rte(double8 a) {
    char8 r;
    r.hi = convert_char4_rte(a.hi);
    r.lo = convert_char4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16_rte(double16 a) {
    char16 r;
    r.hi = convert_char8_rte(a.hi);
    r.lo = convert_char8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ char8 convert_char8(double8 a) {
    char8 r;
    r.hi = convert_char4(a.hi);
    r.lo = convert_char4(a.lo);
    return r;
  }
  __AIR_FUNC__ char16 convert_char16(double16 a) {
    char16 r;
    r.hi = convert_char8(a.hi);
    r.lo = convert_char8(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat_rtz(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat_rtz(a.hi);
    r.lo = convert_uchar4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat_rtz(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat_rtz(a.hi);
    r.lo = convert_uchar8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat_rtn(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat_rtn(a.hi);
    r.lo = convert_uchar4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat_rtn(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat_rtn(a.hi);
    r.lo = convert_uchar8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat_rtp(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat_rtp(a.hi);
    r.lo = convert_uchar4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat_rtp(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat_rtp(a.hi);
    r.lo = convert_uchar8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat_rte(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat_rte(a.hi);
    r.lo = convert_uchar4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat_rte(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat_rte(a.hi);
    r.lo = convert_uchar8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_sat(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_sat(a.hi);
    r.lo = convert_uchar4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_sat(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_sat(a.hi);
    r.lo = convert_uchar8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_rtz(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_rtz(a.hi);
    r.lo = convert_uchar4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_rtz(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_rtz(a.hi);
    r.lo = convert_uchar8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_rtn(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_rtn(a.hi);
    r.lo = convert_uchar4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_rtn(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_rtn(a.hi);
    r.lo = convert_uchar8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_rtp(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_rtp(a.hi);
    r.lo = convert_uchar4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_rtp(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_rtp(a.hi);
    r.lo = convert_uchar8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8_rte(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4_rte(a.hi);
    r.lo = convert_uchar4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16_rte(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8_rte(a.hi);
    r.lo = convert_uchar8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar8 convert_uchar8(double8 a) {
    uchar8 r;
    r.hi = convert_uchar4(a.hi);
    r.lo = convert_uchar4(a.lo);
    return r;
  }
  __AIR_FUNC__ uchar16 convert_uchar16(double16 a) {
    uchar16 r;
    r.hi = convert_uchar8(a.hi);
    r.lo = convert_uchar8(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat_rtz(double8 a) {
    short8 r;
    r.hi = convert_short4_sat_rtz(a.hi);
    r.lo = convert_short4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat_rtz(double16 a) {
    short16 r;
    r.hi = convert_short8_sat_rtz(a.hi);
    r.lo = convert_short8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat_rtn(double8 a) {
    short8 r;
    r.hi = convert_short4_sat_rtn(a.hi);
    r.lo = convert_short4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat_rtn(double16 a) {
    short16 r;
    r.hi = convert_short8_sat_rtn(a.hi);
    r.lo = convert_short8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat_rtp(double8 a) {
    short8 r;
    r.hi = convert_short4_sat_rtp(a.hi);
    r.lo = convert_short4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat_rtp(double16 a) {
    short16 r;
    r.hi = convert_short8_sat_rtp(a.hi);
    r.lo = convert_short8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat_rte(double8 a) {
    short8 r;
    r.hi = convert_short4_sat_rte(a.hi);
    r.lo = convert_short4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat_rte(double16 a) {
    short16 r;
    r.hi = convert_short8_sat_rte(a.hi);
    r.lo = convert_short8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_sat(double8 a) {
    short8 r;
    r.hi = convert_short4_sat(a.hi);
    r.lo = convert_short4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_sat(double16 a) {
    short16 r;
    r.hi = convert_short8_sat(a.hi);
    r.lo = convert_short8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_rtz(double8 a) {
    short8 r;
    r.hi = convert_short4_rtz(a.hi);
    r.lo = convert_short4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_rtz(double16 a) {
    short16 r;
    r.hi = convert_short8_rtz(a.hi);
    r.lo = convert_short8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_rtn(double8 a) {
    short8 r;
    r.hi = convert_short4_rtn(a.hi);
    r.lo = convert_short4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_rtn(double16 a) {
    short16 r;
    r.hi = convert_short8_rtn(a.hi);
    r.lo = convert_short8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_rtp(double8 a) {
    short8 r;
    r.hi = convert_short4_rtp(a.hi);
    r.lo = convert_short4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_rtp(double16 a) {
    short16 r;
    r.hi = convert_short8_rtp(a.hi);
    r.lo = convert_short8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8_rte(double8 a) {
    short8 r;
    r.hi = convert_short4_rte(a.hi);
    r.lo = convert_short4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16_rte(double16 a) {
    short16 r;
    r.hi = convert_short8_rte(a.hi);
    r.lo = convert_short8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ short8 convert_short8(double8 a) {
    short8 r;
    r.hi = convert_short4(a.hi);
    r.lo = convert_short4(a.lo);
    return r;
  }
  __AIR_FUNC__ short16 convert_short16(double16 a) {
    short16 r;
    r.hi = convert_short8(a.hi);
    r.lo = convert_short8(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat_rtz(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat_rtz(a.hi);
    r.lo = convert_ushort4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat_rtz(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat_rtz(a.hi);
    r.lo = convert_ushort8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat_rtn(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat_rtn(a.hi);
    r.lo = convert_ushort4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat_rtn(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat_rtn(a.hi);
    r.lo = convert_ushort8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat_rtp(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat_rtp(a.hi);
    r.lo = convert_ushort4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat_rtp(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat_rtp(a.hi);
    r.lo = convert_ushort8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat_rte(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat_rte(a.hi);
    r.lo = convert_ushort4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat_rte(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat_rte(a.hi);
    r.lo = convert_ushort8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_sat(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_sat(a.hi);
    r.lo = convert_ushort4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_sat(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_sat(a.hi);
    r.lo = convert_ushort8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_rtz(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_rtz(a.hi);
    r.lo = convert_ushort4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_rtz(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_rtz(a.hi);
    r.lo = convert_ushort8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_rtn(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_rtn(a.hi);
    r.lo = convert_ushort4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_rtn(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_rtn(a.hi);
    r.lo = convert_ushort8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_rtp(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_rtp(a.hi);
    r.lo = convert_ushort4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_rtp(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_rtp(a.hi);
    r.lo = convert_ushort8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8_rte(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4_rte(a.hi);
    r.lo = convert_ushort4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16_rte(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8_rte(a.hi);
    r.lo = convert_ushort8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort8 convert_ushort8(double8 a) {
    ushort8 r;
    r.hi = convert_ushort4(a.hi);
    r.lo = convert_ushort4(a.lo);
    return r;
  }
  __AIR_FUNC__ ushort16 convert_ushort16(double16 a) {
    ushort16 r;
    r.hi = convert_ushort8(a.hi);
    r.lo = convert_ushort8(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat_rtz(double8 a) {
    int8 r;
    r.hi = convert_int4_sat_rtz(a.hi);
    r.lo = convert_int4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat_rtz(double16 a) {
    int16 r;
    r.hi = convert_int8_sat_rtz(a.hi);
    r.lo = convert_int8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat_rtn(double8 a) {
    int8 r;
    r.hi = convert_int4_sat_rtn(a.hi);
    r.lo = convert_int4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat_rtn(double16 a) {
    int16 r;
    r.hi = convert_int8_sat_rtn(a.hi);
    r.lo = convert_int8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat_rtp(double8 a) {
    int8 r;
    r.hi = convert_int4_sat_rtp(a.hi);
    r.lo = convert_int4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat_rtp(double16 a) {
    int16 r;
    r.hi = convert_int8_sat_rtp(a.hi);
    r.lo = convert_int8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat_rte(double8 a) {
    int8 r;
    r.hi = convert_int4_sat_rte(a.hi);
    r.lo = convert_int4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat_rte(double16 a) {
    int16 r;
    r.hi = convert_int8_sat_rte(a.hi);
    r.lo = convert_int8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_sat(double8 a) {
    int8 r;
    r.hi = convert_int4_sat(a.hi);
    r.lo = convert_int4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_sat(double16 a) {
    int16 r;
    r.hi = convert_int8_sat(a.hi);
    r.lo = convert_int8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_rtz(double8 a) {
    int8 r;
    r.hi = convert_int4_rtz(a.hi);
    r.lo = convert_int4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_rtz(double16 a) {
    int16 r;
    r.hi = convert_int8_rtz(a.hi);
    r.lo = convert_int8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_rtn(double8 a) {
    int8 r;
    r.hi = convert_int4_rtn(a.hi);
    r.lo = convert_int4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_rtn(double16 a) {
    int16 r;
    r.hi = convert_int8_rtn(a.hi);
    r.lo = convert_int8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_rtp(double8 a) {
    int8 r;
    r.hi = convert_int4_rtp(a.hi);
    r.lo = convert_int4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_rtp(double16 a) {
    int16 r;
    r.hi = convert_int8_rtp(a.hi);
    r.lo = convert_int8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8_rte(double8 a) {
    int8 r;
    r.hi = convert_int4_rte(a.hi);
    r.lo = convert_int4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16_rte(double16 a) {
    int16 r;
    r.hi = convert_int8_rte(a.hi);
    r.lo = convert_int8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ int8 convert_int8(double8 a) {
    int8 r;
    r.hi = convert_int4(a.hi);
    r.lo = convert_int4(a.lo);
    return r;
  }
  __AIR_FUNC__ int16 convert_int16(double16 a) {
    int16 r;
    r.hi = convert_int8(a.hi);
    r.lo = convert_int8(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat_rtz(double8 a) {
    uint8 r;
    r.hi = convert_uint4_sat_rtz(a.hi);
    r.lo = convert_uint4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat_rtz(double16 a) {
    uint16 r;
    r.hi = convert_uint8_sat_rtz(a.hi);
    r.lo = convert_uint8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat_rtn(double8 a) {
    uint8 r;
    r.hi = convert_uint4_sat_rtn(a.hi);
    r.lo = convert_uint4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat_rtn(double16 a) {
    uint16 r;
    r.hi = convert_uint8_sat_rtn(a.hi);
    r.lo = convert_uint8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat_rtp(double8 a) {
    uint8 r;
    r.hi = convert_uint4_sat_rtp(a.hi);
    r.lo = convert_uint4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat_rtp(double16 a) {
    uint16 r;
    r.hi = convert_uint8_sat_rtp(a.hi);
    r.lo = convert_uint8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat_rte(double8 a) {
    uint8 r;
    r.hi = convert_uint4_sat_rte(a.hi);
    r.lo = convert_uint4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat_rte(double16 a) {
    uint16 r;
    r.hi = convert_uint8_sat_rte(a.hi);
    r.lo = convert_uint8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_sat(double8 a) {
    uint8 r;
    r.hi = convert_uint4_sat(a.hi);
    r.lo = convert_uint4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_sat(double16 a) {
    uint16 r;
    r.hi = convert_uint8_sat(a.hi);
    r.lo = convert_uint8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_rtz(double8 a) {
    uint8 r;
    r.hi = convert_uint4_rtz(a.hi);
    r.lo = convert_uint4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_rtz(double16 a) {
    uint16 r;
    r.hi = convert_uint8_rtz(a.hi);
    r.lo = convert_uint8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_rtn(double8 a) {
    uint8 r;
    r.hi = convert_uint4_rtn(a.hi);
    r.lo = convert_uint4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_rtn(double16 a) {
    uint16 r;
    r.hi = convert_uint8_rtn(a.hi);
    r.lo = convert_uint8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_rtp(double8 a) {
    uint8 r;
    r.hi = convert_uint4_rtp(a.hi);
    r.lo = convert_uint4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_rtp(double16 a) {
    uint16 r;
    r.hi = convert_uint8_rtp(a.hi);
    r.lo = convert_uint8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8_rte(double8 a) {
    uint8 r;
    r.hi = convert_uint4_rte(a.hi);
    r.lo = convert_uint4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16_rte(double16 a) {
    uint16 r;
    r.hi = convert_uint8_rte(a.hi);
    r.lo = convert_uint8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ uint8 convert_uint8(double8 a) {
    uint8 r;
    r.hi = convert_uint4(a.hi);
    r.lo = convert_uint4(a.lo);
    return r;
  }
  __AIR_FUNC__ uint16 convert_uint16(double16 a) {
    uint16 r;
    r.hi = convert_uint8(a.hi);
    r.lo = convert_uint8(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat_rtz(double8 a) {
    long8 r;
    r.hi = convert_long4_sat_rtz(a.hi);
    r.lo = convert_long4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat_rtz(double16 a) {
    long16 r;
    r.hi = convert_long8_sat_rtz(a.hi);
    r.lo = convert_long8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat_rtn(double8 a) {
    long8 r;
    r.hi = convert_long4_sat_rtn(a.hi);
    r.lo = convert_long4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat_rtn(double16 a) {
    long16 r;
    r.hi = convert_long8_sat_rtn(a.hi);
    r.lo = convert_long8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat_rtp(double8 a) {
    long8 r;
    r.hi = convert_long4_sat_rtp(a.hi);
    r.lo = convert_long4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat_rtp(double16 a) {
    long16 r;
    r.hi = convert_long8_sat_rtp(a.hi);
    r.lo = convert_long8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat_rte(double8 a) {
    long8 r;
    r.hi = convert_long4_sat_rte(a.hi);
    r.lo = convert_long4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat_rte(double16 a) {
    long16 r;
    r.hi = convert_long8_sat_rte(a.hi);
    r.lo = convert_long8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_sat(double8 a) {
    long8 r;
    r.hi = convert_long4_sat(a.hi);
    r.lo = convert_long4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_sat(double16 a) {
    long16 r;
    r.hi = convert_long8_sat(a.hi);
    r.lo = convert_long8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_rtz(double8 a) {
    long8 r;
    r.hi = convert_long4_rtz(a.hi);
    r.lo = convert_long4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_rtz(double16 a) {
    long16 r;
    r.hi = convert_long8_rtz(a.hi);
    r.lo = convert_long8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_rtn(double8 a) {
    long8 r;
    r.hi = convert_long4_rtn(a.hi);
    r.lo = convert_long4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_rtn(double16 a) {
    long16 r;
    r.hi = convert_long8_rtn(a.hi);
    r.lo = convert_long8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_rtp(double8 a) {
    long8 r;
    r.hi = convert_long4_rtp(a.hi);
    r.lo = convert_long4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_rtp(double16 a) {
    long16 r;
    r.hi = convert_long8_rtp(a.hi);
    r.lo = convert_long8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8_rte(double8 a) {
    long8 r;
    r.hi = convert_long4_rte(a.hi);
    r.lo = convert_long4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16_rte(double16 a) {
    long16 r;
    r.hi = convert_long8_rte(a.hi);
    r.lo = convert_long8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ long8 convert_long8(double8 a) {
    long8 r;
    r.hi = convert_long4(a.hi);
    r.lo = convert_long4(a.lo);
    return r;
  }
  __AIR_FUNC__ long16 convert_long16(double16 a) {
    long16 r;
    r.hi = convert_long8(a.hi);
    r.lo = convert_long8(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat_rtz(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat_rtz(a.hi);
    r.lo = convert_ulong4_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat_rtz(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat_rtz(a.hi);
    r.lo = convert_ulong8_sat_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat_rtn(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat_rtn(a.hi);
    r.lo = convert_ulong4_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat_rtn(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat_rtn(a.hi);
    r.lo = convert_ulong8_sat_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat_rtp(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat_rtp(a.hi);
    r.lo = convert_ulong4_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat_rtp(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat_rtp(a.hi);
    r.lo = convert_ulong8_sat_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat_rte(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat_rte(a.hi);
    r.lo = convert_ulong4_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat_rte(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat_rte(a.hi);
    r.lo = convert_ulong8_sat_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_sat(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_sat(a.hi);
    r.lo = convert_ulong4_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_sat(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_sat(a.hi);
    r.lo = convert_ulong8_sat(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_rtz(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_rtz(a.hi);
    r.lo = convert_ulong4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_rtz(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_rtz(a.hi);
    r.lo = convert_ulong8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_rtn(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_rtn(a.hi);
    r.lo = convert_ulong4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_rtn(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_rtn(a.hi);
    r.lo = convert_ulong8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_rtp(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_rtp(a.hi);
    r.lo = convert_ulong4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_rtp(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_rtp(a.hi);
    r.lo = convert_ulong8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8_rte(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4_rte(a.hi);
    r.lo = convert_ulong4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16_rte(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8_rte(a.hi);
    r.lo = convert_ulong8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong8 convert_ulong8(double8 a) {
    ulong8 r;
    r.hi = convert_ulong4(a.hi);
    r.lo = convert_ulong4(a.lo);
    return r;
  }
  __AIR_FUNC__ ulong16 convert_ulong16(double16 a) {
    ulong16 r;
    r.hi = convert_ulong8(a.hi);
    r.lo = convert_ulong8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(char8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(char16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(char8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(char16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(char8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(char16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(char8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(char16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(char8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(char16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(uchar8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(uchar16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(uchar8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(uchar16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(uchar8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(uchar16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(uchar8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(uchar16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(uchar8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(uchar16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(short8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(short16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(short8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(short16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(short8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(short16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(short8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(short16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(short8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(short16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(ushort8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(ushort16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(ushort8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(ushort16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(ushort8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(ushort16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(ushort8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(ushort16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(ushort8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(ushort16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(int8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(int16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(int8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(int16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(int8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(int16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(int8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(int16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(int8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(int16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(uint8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(uint16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(uint8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(uint16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(uint8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(uint16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(uint8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(uint16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(uint8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(uint16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(long8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(long16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(long8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(long16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(long8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(long16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(long8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(long16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(long8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(long16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(ulong8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(ulong16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(ulong8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(ulong16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(ulong8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(ulong16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(ulong8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(ulong16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(ulong8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(ulong16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtz(double8 a) {
    double8 r;
    r.hi = convert_double4_rtz(a.hi);
    r.lo = convert_double4_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtz(double16 a) {
    double16 r;
    r.hi = convert_double8_rtz(a.hi);
    r.lo = convert_double8_rtz(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtn(double8 a) {
    double8 r;
    r.hi = convert_double4_rtn(a.hi);
    r.lo = convert_double4_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtn(double16 a) {
    double16 r;
    r.hi = convert_double8_rtn(a.hi);
    r.lo = convert_double8_rtn(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rtp(double8 a) {
    double8 r;
    r.hi = convert_double4_rtp(a.hi);
    r.lo = convert_double4_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rtp(double16 a) {
    double16 r;
    r.hi = convert_double8_rtp(a.hi);
    r.lo = convert_double8_rtp(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8_rte(double8 a) {
    double8 r;
    r.hi = convert_double4_rte(a.hi);
    r.lo = convert_double4_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16_rte(double16 a) {
    double16 r;
    r.hi = convert_double8_rte(a.hi);
    r.lo = convert_double8_rte(a.lo);
    return r;
  }
  __AIR_FUNC__ double8 convert_double8(double8 a) {
    double8 r;
    r.hi = convert_double4(a.hi);
    r.lo = convert_double4(a.lo);
    return r;
  }
  __AIR_FUNC__ double16 convert_double16(double16 a) {
    double16 r;
    r.hi = convert_double8(a.hi);
    r.lo = convert_double8(a.lo);
    return r;
  }

#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))


// OpenCL 1.2 6.12.2 Math Functions generating Unified LLVM IR Sec 4 Math Functions

  __AIR_ASM__ float acos(float x) __asm("air." _AIR_PREFIX_float "acos.f32");
  __AIR_ASM__ float acosh(float x) __asm("air." _AIR_PREFIX_float "acosh.f32");
  __AIR_ASM__ float acospi(float x) __asm("air.acospi.f32");
  __AIR_ASM__ float asin(float x) __asm("air." _AIR_PREFIX_float "asin.f32");
  __AIR_ASM__ float asinh(float x) __asm("air." _AIR_PREFIX_float "asinh.f32");
  __AIR_ASM__ float asinpi(float x) __asm("air.asinpi.f32");
  __AIR_ASM__ float atan(float y_over_x) __asm("air." _AIR_PREFIX_float "atan.f32");
  __AIR_ASM__ float atan2(float y, float x) __asm("air." _AIR_PREFIX_float "atan2.f32");
  __AIR_ASM__ float atanh(float x) __asm("air." _AIR_PREFIX_float "atanh.f32");
  __AIR_ASM__ float atanpi(float y_over_x) __asm("air." _AIR_PREFIX_float "atanpi.f32");
  __AIR_ASM__ float atan2pi(float y, float x) __asm("air." _AIR_PREFIX_float "atanpi2.f32");
  __AIR_ASM__ float cbrt(float x) __asm("air.cbrt.f32");
  __AIR_ASM__ float ceil(float x) __asm("air.ceil.f32");
  // We will produce the code for copysign
  __AIR_TGT__ float copysign(float x, float y);
  __AIR_ASM__ float cos(float x) __asm("air." _AIR_PREFIX_float "cos.f32");
  __AIR_ASM__ float cosh(float x) __asm("air." _AIR_PREFIX_float "cosh.f32");
  __AIR_ASM__ float cospi(float x) __asm("air.cospi.f32");
  __AIR_ASM__ float erf(float x) __asm("air." _AIR_PREFIX_float "erf.f32");
  __AIR_TGT__ float erfc(float x) __asm("air." _AIR_PREFIX_float "erfc.f32");
  __AIR_ASM__ float exp(float x) __asm("air." _AIR_PREFIX_float "exp.f32");
  __AIR_ASM__ float exp2(float x) __asm("air." _AIR_PREFIX_float "exp2.f32");
#if defined(__FAST_RELAXED_MATH__)
  __AIR_FUNC__ float exp10(float x) {
    return exp2(x * LOG2_10F);
  }
#else
  __AIR_ASM__ float exp10(float x) __asm("air.exp10.f32");
#endif
  __AIR_ASM__ float expm1(float x) __asm("air.expm1.f32");
  __AIR_ASM__ float fabs(float x) __asm("air.fabs.f32");
  // We will provide fdim
  __AIR_TGT__ float fdim(float x, float y);
  __AIR_ASM__ float floor(float x) __asm("air.floor.f32");
  __AIR_ASM__ float fma(float x, float y, float z) __asm("air.fma.f32");
  __AIR_ASM__ float fmax(float x, float y) __asm("air.fmax.f32");
  __AIR_ASM__ float fmin(float x, float y) __asm("air.fmin.f32");
  __AIR_ASM__ float fmod(float x, float y) __asm("air.fmod.f32");
  __AIR_ASM__ float fract(float x, private float *iptr) __asm("air.fract.f32");
  __AIR_FUNC__ float fract(float x, global float * quo) {
    float pquo;
    float res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ float fract(float x, local float * quo)  {
    float pquo;
    float res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  // We will provide frexp and ilogb because this is not in AIR
  __AIR_TGT__ float frexp(float x, global int *exponent);
  __AIR_TGT__ float frexp(float x, local int *exponent);
  __AIR_TGT__ float frexp(float x, private int *exponent);
  __AIR_ASM__ float hypot(float y, float x) __asm("air.hypot.f32");
  __AIR_TGT__ int ilogb(float x);
  __AIR_ASM__ float ldexp(float x, int k) __asm("air.ldexp.f32");
  __AIR_ASM__ float lgamma(float x) __asm("air.lgamma.f32");
  __AIR_ASM__ float lgamma_r(float x, private int * signp) __asm("air.lgamma_r.f32");
  __AIR_FUNC__ float lgamma_r(float x, global int * signp) {
    int psignp;
    float res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_FUNC__ float lgamma_r(float x, local int * signp)  {
    int psignp;
    float res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_ASM__ float log(float x) __asm("air." _AIR_PREFIX_float "log.f32");
  __AIR_ASM__ float log2(float x) __asm("air." _AIR_PREFIX_float "log2.f32");
#if defined(__FAST_RELAXED_MATH__)
  __AIR_FUNC__ float log10(float x) {
    return log2(x) * LOG10_2F;
  }
#else
  __AIR_ASM__ float log10(float x) __asm("air.log10.f32");
#endif
  __AIR_ASM__ float log1p(float x) __asm("air.log1p.f32");
  __AIR_ASM__ float logb(float x) __asm("air.logb.f32");
  __AIR_ASM__ float mad(float x, float y, float z) __asm("air.mad.f32");
  // Targets provide maxmag and minmag.
  __AIR_TGT__ float maxmag(float x, float y);
  __AIR_TGT__ float minmag(float x, float y);
  __AIR_TGT__ float modf(float x, global float *intval);
  __AIR_TGT__ float modf(float x, local float *intval);
  __AIR_TGT__ float modf(float x, private float *intval);
  __AIR_TGT__ float nan(uint x);
  __AIR_ASM__ float native_cos(float x) __asm("air.fast_cos.f32");
  // Fixme: (rdar://problem/19724906) Need to generate a fast-divide every time here; something along the lines of:
  // 
  //   <result> = fdiv fast float %x, %y
  //
  // Keeping it as the basic implementation for now just to get it checked in.
  __AIR_FUNC__ float native_divide(float x, float y) {
    return x / y;
  }
  __AIR_ASM__ float native_exp(float x) __asm("air.fast_exp.f32");
  __AIR_ASM__ float native_exp2(float x) __asm("air.fast_exp2.f32");
  __AIR_FUNC__ float native_exp10(float x) {
    return native_exp2(x * LOG2_10F);
  }
  __AIR_ASM__ float native_log(float x) __asm("air.fast_log.f32");
  __AIR_ASM__ float native_log2(float x) __asm("air.fast_log2.f32");
  __AIR_FUNC__ float native_log10(float x) {
    return native_log2(x) * LOG10_2F;
  }
  __AIR_ASM__ float native_powr(float x, float y) __asm("air.fast_powr.f32");
  __AIR_FUNC__ float native_recip(float x) {
    return native_divide(1.0f, x);
  }
  __AIR_ASM__ float native_rsqrt(float x) __asm("air.fast_rsqrt.f32");
  __AIR_ASM__ float native_sin(float x) __asm("air.fast_sin.f32");
  __AIR_ASM__ float native_sqrt(float x) __asm("air.fast_sqrt.f32");
  __AIR_ASM__ float native_tan(float x) __asm("air.fast_tan.f32");
  __AIR_ASM__ float nextafter(float x, float y) __asm("air.nextafter.f32");
  __AIR_ASM__ float pow(float x, float y) __asm("air." _AIR_PREFIX_float "pow.f32");
  __AIR_ASM__ float pown(float x, int y) __asm("air.pown.f32");
  __AIR_ASM__ float powr(float x, float y) __asm("air.powr.f32");
  __AIR_ASM__ float remainder(float x, float y) __asm("air.remainder.f32");
  __AIR_ASM__ float remquo(float x, float y, private int * quo) __asm("air.remquo.f32");
  __AIR_FUNC__ float remquo(float x, float y, global int * quo) {
    int pquo;
    float res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ float remquo(float x, float y, local int * quo)  {
    int pquo;
    float res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_ASM__ float rint(float x) __asm("air.rint.f32");
  __AIR_ASM__ float rootn(float x, int y) __asm("air.rootn.f32");
  // FIXME: scalar rootn
  __AIR_ASM__ float round(float x) __asm("air." _AIR_PREFIX_float "round.f32");
  __AIR_ASM__ float rsqrt(float x) __asm("air." _AIR_PREFIX_float "rsqrt.f32");
  __AIR_ASM__ float sin(float x) __asm("air." _AIR_PREFIX_float "sin.f32");
  __AIR_ASM__ float sincos(float x, private float *cosval) __asm("air." _AIR_PREFIX_float "sincos.f32");
  __AIR_FUNC__ float sincos(float x, global float *cosval) {
    float pcosval;
    float res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_FUNC__ float sincos(float x, local float *cosval) {
    float pcosval;
    float res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_ASM__ float sinh(float x) __asm("air." _AIR_PREFIX_float "sinh.f32");
  __AIR_ASM__ float sinpi(float x) __asm("air.sinpi.f32");
  __AIR_ASM__ float sqrt(float x) __asm("air." _AIR_PREFIX_float "sqrt.f32");
  __AIR_ASM__ float tan(float x) __asm("air." _AIR_PREFIX_float "tan.f32");
  __AIR_ASM__ float tanh(float x) __asm("air." _AIR_PREFIX_float "tanh.f32");
  __AIR_ASM__ float tanpi(float x) __asm("air.tanpi.f32");
  __AIR_ASM__ float tgamma(float x) __asm("air.tgamma.f32");
  __AIR_ASM__ float trunc(float x) __asm("air.trunc.f32");

  __AIR_ASM__ float half_rsqrt(float x) __asm("air.fast_rsqrt.f32");
  __AIR_ASM__ float half_sqrt(float x) __asm("air.fast_sqrt.f32");


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_ASM__ double acos(double x) __asm("air." _AIR_PREFIX_double "acos.f64");
  __AIR_ASM__ double acosh(double x) __asm("air." _AIR_PREFIX_double "acosh.f64");
  __AIR_ASM__ double acospi(double x) __asm("air.acospi.f64");
  __AIR_ASM__ double asin(double x) __asm("air." _AIR_PREFIX_double "asin.f64");
  __AIR_ASM__ double asinh(double x) __asm("air." _AIR_PREFIX_double "asinh.f64");
  __AIR_ASM__ double asinpi(double x) __asm("air.asinpi.f64");
  __AIR_ASM__ double atan(double y_over_x) __asm("air." _AIR_PREFIX_double "atan.f64");
  __AIR_ASM__ double atan2(double y, double x) __asm("air." _AIR_PREFIX_double "atan2.f64");
  __AIR_ASM__ double atanh(double x) __asm("air." _AIR_PREFIX_double "atanh.f64");
  __AIR_ASM__ double atanpi(double y_over_x) __asm("air." _AIR_PREFIX_double "atanpi.f64");
  __AIR_ASM__ double atan2pi(double y, double x) __asm("air." _AIR_PREFIX_double "atanpi2.f64");
  __AIR_ASM__ double cbrt(double x) __asm("air.cbrt.f64");
  __AIR_ASM__ double ceil(double x) __asm("air.ceil.f64");
  // We will produce the code for copysign
  __AIR_TGT__ double copysign(double x, double y);
  __AIR_ASM__ double cos(double x) __asm("air." _AIR_PREFIX_double "cos.f64");
  __AIR_ASM__ double cosh(double x) __asm("air." _AIR_PREFIX_double "cosh.f64");
  __AIR_ASM__ double cospi(double x) __asm("air.cospi.f64");
  __AIR_ASM__ double erf(double x) __asm("air." _AIR_PREFIX_double "erf.f64");
  __AIR_TGT__ double erfc(double x) __asm("air." _AIR_PREFIX_double "erfc.f64");
  __AIR_ASM__ double exp(double x) __asm("air." _AIR_PREFIX_double "exp.f64");
  __AIR_ASM__ double exp2(double x) __asm("air." _AIR_PREFIX_double "exp2.f64");
  __AIR_ASM__ double exp10(double x) __asm("air.exp10.f64");
  __AIR_ASM__ double expm1(double x) __asm("air.expm1.f64");
  __AIR_ASM__ double fabs(double x) __asm("air.fabs.f64");
  // We will provide fdim
  __AIR_TGT__ double fdim(double x, double y);
  __AIR_ASM__ double floor(double x) __asm("air.floor.f64");
  __AIR_ASM__ double fma(double x, double y, double z) __asm("air.fma.f64");
  __AIR_ASM__ double fmax(double x, double y) __asm("air.fmax.f64");
  __AIR_ASM__ double fmin(double x, double y) __asm("air.fmin.f64");
  __AIR_ASM__ double fmod(double x, double y) __asm("air.fmod.f64");
  __AIR_ASM__ double fract(double x, private double *iptr) __asm("air.fract.f64");
  __AIR_FUNC__ double fract(double x, global double * quo) {
    double pquo;
    double res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ double fract(double x, local double * quo)  {
    double pquo;
    double res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  // We will provide frexp and ilogb because this is not in AIR
  __AIR_TGT__ double frexp(double x, global int *exponent);
  __AIR_TGT__ double frexp(double x, local int *exponent);
  __AIR_TGT__ double frexp(double x, private int *exponent);
  __AIR_ASM__ double hypot(double y, double x) __asm("air.hypot.f64");
  __AIR_TGT__ int ilogb(double x);
  __AIR_ASM__ double ldexp(double x, int k) __asm("air.ldexp.f64");
  __AIR_ASM__ double lgamma(double x) __asm("air.lgamma.f64");
  __AIR_ASM__ double lgamma_r(double x, private int * signp) __asm("air.lgamma_r.f64");
  __AIR_FUNC__ double lgamma_r(double x, global int * signp) {
    int psignp;
    double res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_FUNC__ double lgamma_r(double x, local int * signp)  {
    int psignp;
    double res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_ASM__ double log(double x) __asm("air." _AIR_PREFIX_double "log.f64");
  __AIR_ASM__ double log2(double x) __asm("air." _AIR_PREFIX_double "log2.f64");
  __AIR_ASM__ double log10(double x) __asm("air.log10.f64");
  __AIR_ASM__ double log1p(double x) __asm("air.log1p.f64");
  __AIR_ASM__ double logb(double x) __asm("air.logb.f64");
  __AIR_ASM__ double mad(double x, double y, double z) __asm("air.mad.f64");
  // Targets provide maxmag and minmag.
  __AIR_TGT__ double maxmag(double x, double y);
  __AIR_TGT__ double minmag(double x, double y);
  __AIR_TGT__ double modf(double x, global double *intval);
  __AIR_TGT__ double modf(double x, local double *intval);
  __AIR_TGT__ double modf(double x, private double *intval);
  __AIR_TGT__ double nan(ulong x);
  __AIR_ASM__ double nextafter(double x, double y) __asm("air.nextafter.f64");
  __AIR_ASM__ double pow(double x, double y) __asm("air." _AIR_PREFIX_double "pow.f64");
  __AIR_ASM__ double pown(double x, int y) __asm("air.pown.f64");
  __AIR_ASM__ double powr(double x, double y) __asm("air.powr.f64");
  __AIR_ASM__ double remainder(double x, double y) __asm("air.remainder.f64");
  __AIR_ASM__ double remquo(double x, double y, private int * quo) __asm("air.remquo.f64");
  __AIR_FUNC__ double remquo(double x, double y, global int * quo) {
    int pquo;
    double res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ double remquo(double x, double y, local int * quo)  {
    int pquo;
    double res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_ASM__ double rint(double x) __asm("air.rint.f64");
  __AIR_ASM__ double rootn(double x, int y) __asm("air.rootn.f64");
  // FIXME: scalar rootn
  __AIR_ASM__ double round(double x) __asm("air." _AIR_PREFIX_double "round.f64");
  __AIR_ASM__ double rsqrt(double x) __asm("air." _AIR_PREFIX_double "rsqrt.f64");
  __AIR_ASM__ double sin(double x) __asm("air." _AIR_PREFIX_double "sin.f64");
  __AIR_ASM__ double sincos(double x, private double *cosval) __asm("air." _AIR_PREFIX_double "sincos.f64");
  __AIR_FUNC__ double sincos(double x, global double *cosval) {
    double pcosval;
    double res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_FUNC__ double sincos(double x, local double *cosval) {
    double pcosval;
    double res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_ASM__ double sinh(double x) __asm("air." _AIR_PREFIX_double "sinh.f64");
  __AIR_ASM__ double sinpi(double x) __asm("air.sinpi.f64");
  __AIR_ASM__ double sqrt(double x) __asm("air." _AIR_PREFIX_double "sqrt.f64");
  __AIR_ASM__ double tan(double x) __asm("air." _AIR_PREFIX_double "tan.f64");
  __AIR_ASM__ double tanh(double x) __asm("air." _AIR_PREFIX_double "tanh.f64");
  __AIR_ASM__ double tanpi(double x) __asm("air.tanpi.f64");
  __AIR_ASM__ double tgamma(double x) __asm("air.tgamma.f64");
  __AIR_ASM__ double trunc(double x) __asm("air.trunc.f64");


#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float2 acos(float2 x) __asm("air." _AIR_PREFIX_float "acos.v2f32");
  __AIR_ASM__ float2 acosh(float2 x) __asm("air." _AIR_PREFIX_float "acosh.v2f32");
  __AIR_ASM__ float2 acospi(float2 x) __asm("air.acospi.v2f32");
  __AIR_ASM__ float2 asin(float2 x) __asm("air." _AIR_PREFIX_float "asin.v2f32");
  __AIR_ASM__ float2 asinh(float2 x) __asm("air." _AIR_PREFIX_float "asinh.v2f32");
  __AIR_ASM__ float2 asinpi(float2 x) __asm("air.asinpi.v2f32");
  __AIR_ASM__ float2 atan(float2 y_over_x) __asm("air." _AIR_PREFIX_float "atan.v2f32");
  __AIR_ASM__ float2 atan2(float2 y, float2 x) __asm("air." _AIR_PREFIX_float "atan2.v2f32");
  __AIR_ASM__ float2 atanh(float2 x) __asm("air." _AIR_PREFIX_float "atanh.v2f32");
  __AIR_ASM__ float2 atanpi(float2 y_over_x) __asm("air." _AIR_PREFIX_float "atanpi.v2f32");
  __AIR_ASM__ float2 atan2pi(float2 y, float2 x) __asm("air." _AIR_PREFIX_float "atanpi2.v2f32");
  __AIR_ASM__ float2 cbrt(float2 x) __asm("air.cbrt.v2f32");
  __AIR_ASM__ float2 ceil(float2 x) __asm("air.ceil.v2f32");
  // We will produce the code for copysign
  __AIR_TGT__ float2 copysign(float2 x, float2 y);
  __AIR_ASM__ float2 cos(float2 x) __asm("air." _AIR_PREFIX_float "cos.v2f32");
  __AIR_ASM__ float2 cosh(float2 x) __asm("air." _AIR_PREFIX_float "cosh.v2f32");
  __AIR_ASM__ float2 cospi(float2 x) __asm("air.cospi.v2f32");
  __AIR_ASM__ float2 erf(float2 x) __asm("air." _AIR_PREFIX_float "erf.v2f32");
  __AIR_TGT__ float2 erfc(float2 x) __asm("air." _AIR_PREFIX_float "erfc.v2f32");
  __AIR_ASM__ float2 exp(float2 x) __asm("air." _AIR_PREFIX_float "exp.v2f32");
  __AIR_ASM__ float2 exp2(float2 x) __asm("air." _AIR_PREFIX_float "exp2.v2f32");
#if defined(__FAST_RELAXED_MATH__)
  __AIR_FUNC__ float2 exp10(float2 x) {
    return exp2(x * LOG2_10F);
  }
#else
  __AIR_ASM__ float2 exp10(float2 x) __asm("air.exp10.v2f32");
#endif
  __AIR_ASM__ float2 expm1(float2 x) __asm("air.expm1.v2f32");
  __AIR_ASM__ float2 fabs(float2 x) __asm("air.fabs.v2f32");
  // We will provide fdim
  __AIR_TGT__ float2 fdim(float2 x, float2 y);
  __AIR_ASM__ float2 floor(float2 x) __asm("air.floor.v2f32");
  __AIR_ASM__ float2 fma(float2 x, float2 y, float2 z) __asm("air.fma.v2f32");
  __AIR_ASM__ float2 fmax(float2 x, float2 y) __asm("air.fmax.v2f32");
  __AIR_FUNC__ float2 fmax(float2 x, float y) {
    return fmax(x, (float2)(y));
  }
  __AIR_ASM__ float2 fmin(float2 x, float2 y) __asm("air.fmin.v2f32");
  __AIR_FUNC__ float2 fmin(float2 x, float y) {
    return fmin(x, (float2)(y));
  }
  __AIR_ASM__ float2 fmod(float2 x, float2 y) __asm("air.fmod.v2f32");
  __AIR_ASM__ float2 fract(float2 x, private float2 *iptr) __asm("air.fract.v2f32");
  __AIR_FUNC__ float2 fract(float2 x, global float2 * quo) {
    float2 pquo;
    float2 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ float2 fract(float2 x, local float2 * quo)  {
    float2 pquo;
    float2 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  // We will provide frexp and ilogb because this is not in AIR
  __AIR_TGT__ float2 frexp(float2 x, global int2 *exponent);
  __AIR_TGT__ float2 frexp(float2 x, local int2 *exponent);
  __AIR_TGT__ float2 frexp(float2 x, private int2 *exponent);
  __AIR_ASM__ float2 hypot(float2 y, float2 x) __asm("air.hypot.v2f32");
  __AIR_TGT__ int2 ilogb(float2 x);
  __AIR_ASM__ float2 ldexp(float2 x, int2 k) __asm("air.ldexp.v2f32");
  __AIR_ASM__ float2 lgamma(float2 x) __asm("air.lgamma.v2f32");
  __AIR_ASM__ float2 lgamma_r(float2 x, private int2 * signp) __asm("air.lgamma_r.v2f32");
  __AIR_FUNC__ float2 lgamma_r(float2 x, global int2 * signp) {
    int2 psignp;
    float2 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_FUNC__ float2 lgamma_r(float2 x, local int2 * signp)  {
    int2 psignp;
    float2 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_ASM__ float2 log(float2 x) __asm("air." _AIR_PREFIX_float "log.v2f32");
  __AIR_ASM__ float2 log2(float2 x) __asm("air." _AIR_PREFIX_float "log2.v2f32");
#if defined(__FAST_RELAXED_MATH__)
  __AIR_FUNC__ float2 log10(float2 x) {
    return log2(x) * LOG10_2F;
  }
#else
  __AIR_ASM__ float2 log10(float2 x) __asm("air.log10.v2f32");
#endif
  __AIR_ASM__ float2 log1p(float2 x) __asm("air.log1p.v2f32");
  __AIR_ASM__ float2 logb(float2 x) __asm("air.logb.v2f32");
  __AIR_ASM__ float2 mad(float2 x, float2 y, float2 z) __asm("air.mad.v2f32");
  // Targets provide maxmag and minmag.
  __AIR_TGT__ float2 maxmag(float2 x, float2 y);
  __AIR_TGT__ float2 minmag(float2 x, float2 y);
  __AIR_TGT__ float2 modf(float2 x, global float2 *intval);
  __AIR_TGT__ float2 modf(float2 x, local float2 *intval);
  __AIR_TGT__ float2 modf(float2 x, private float2 *intval);
  __AIR_TGT__ float2 nan(uint2 x);
  __AIR_ASM__ float2 native_cos(float2 x) __asm("air.fast_cos.v2f32");
  // Fixme: (rdar://problem/19724906) Need to generate a fast-divide every time here; something along the lines of:
  // 
  //   <result> = fdiv fast float %x, %y
  //
  // Keeping it as the basic implementation for now just to get it checked in.
  __AIR_FUNC__ float2 native_divide(float2 x, float2 y) {
    return x / y;
  }
  __AIR_ASM__ float2 native_exp(float2 x) __asm("air.fast_exp.v2f32");
  __AIR_ASM__ float2 native_exp2(float2 x) __asm("air.fast_exp2.v2f32");
  __AIR_FUNC__ float2 native_exp10(float2 x) {
    return native_exp2(x * LOG2_10F);
  }
  __AIR_ASM__ float2 native_log(float2 x) __asm("air.fast_log.v2f32");
  __AIR_ASM__ float2 native_log2(float2 x) __asm("air.fast_log2.v2f32");
  __AIR_FUNC__ float2 native_log10(float2 x) {
    return native_log2(x) * LOG10_2F;
  }
  __AIR_ASM__ float2 native_powr(float2 x, float2 y) __asm("air.fast_powr.v2f32");
  __AIR_FUNC__ float2 native_recip(float2 x) {
    return native_divide(1.0f, x);
  }
  __AIR_ASM__ float2 native_rsqrt(float2 x) __asm("air.fast_rsqrt.v2f32");
  __AIR_ASM__ float2 native_sin(float2 x) __asm("air.fast_sin.v2f32");
  __AIR_ASM__ float2 native_sqrt(float2 x) __asm("air.fast_sqrt.v2f32");
  __AIR_ASM__ float2 native_tan(float2 x) __asm("air.fast_tan.v2f32");
  __AIR_ASM__ float2 nextafter(float2 x, float2 y) __asm("air.nextafter.v2f32");
  __AIR_ASM__ float2 pow(float2 x, float2 y) __asm("air." _AIR_PREFIX_float "pow.v2f32");
  __AIR_ASM__ float2 pown(float2 x, int2 y) __asm("air.pown.v2f32");
  __AIR_ASM__ float2 powr(float2 x, float2 y) __asm("air.powr.v2f32");
  __AIR_ASM__ float2 remainder(float2 x, float2 y) __asm("air.remainder.v2f32");
  __AIR_ASM__ float2 remquo(float2 x, float2 y, private int2 * quo) __asm("air.remquo.v2f32");
  __AIR_FUNC__ float2 remquo(float2 x, float2 y, global int2 * quo) {
    int2 pquo;
    float2 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ float2 remquo(float2 x, float2 y, local int2 * quo)  {
    int2 pquo;
    float2 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_ASM__ float2 rint(float2 x) __asm("air.rint.v2f32");
  __AIR_ASM__ float2 rootn(float2 x, int2 y) __asm("air.rootn.v2f32");
  // FIXME: scalar rootn
  __AIR_ASM__ float2 round(float2 x) __asm("air." _AIR_PREFIX_float "round.v2f32");
  __AIR_ASM__ float2 rsqrt(float2 x) __asm("air." _AIR_PREFIX_float "rsqrt.v2f32");
  __AIR_ASM__ float2 sin(float2 x) __asm("air." _AIR_PREFIX_float "sin.v2f32");
  __AIR_ASM__ float2 sincos(float2 x, private float2 *cosval) __asm("air." _AIR_PREFIX_float "sincos.v2f32");
  __AIR_FUNC__ float2 sincos(float2 x, global float2 *cosval) {
    float2 pcosval;
    float2 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_FUNC__ float2 sincos(float2 x, local float2 *cosval) {
    float2 pcosval;
    float2 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_ASM__ float2 sinh(float2 x) __asm("air." _AIR_PREFIX_float "sinh.v2f32");
  __AIR_ASM__ float2 sinpi(float2 x) __asm("air.sinpi.v2f32");
  __AIR_ASM__ float2 sqrt(float2 x) __asm("air." _AIR_PREFIX_float "sqrt.v2f32");
  __AIR_ASM__ float2 tan(float2 x) __asm("air." _AIR_PREFIX_float "tan.v2f32");
  __AIR_ASM__ float2 tanh(float2 x) __asm("air." _AIR_PREFIX_float "tanh.v2f32");
  __AIR_ASM__ float2 tanpi(float2 x) __asm("air.tanpi.v2f32");
  __AIR_ASM__ float2 tgamma(float2 x) __asm("air.tgamma.v2f32");
  __AIR_ASM__ float2 trunc(float2 x) __asm("air.trunc.v2f32");

  __AIR_ASM__ float2 half_rsqrt(float2 x) __asm("air.fast_rsqrt.v2f32");
  __AIR_ASM__ float2 half_sqrt(float2 x) __asm("air.fast_sqrt.v2f32");


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_ASM__ double2 acos(double2 x) __asm("air." _AIR_PREFIX_double "acos.v2f64");
  __AIR_ASM__ double2 acosh(double2 x) __asm("air." _AIR_PREFIX_double "acosh.v2f64");
  __AIR_ASM__ double2 acospi(double2 x) __asm("air.acospi.v2f64");
  __AIR_ASM__ double2 asin(double2 x) __asm("air." _AIR_PREFIX_double "asin.v2f64");
  __AIR_ASM__ double2 asinh(double2 x) __asm("air." _AIR_PREFIX_double "asinh.v2f64");
  __AIR_ASM__ double2 asinpi(double2 x) __asm("air.asinpi.v2f64");
  __AIR_ASM__ double2 atan(double2 y_over_x) __asm("air." _AIR_PREFIX_double "atan.v2f64");
  __AIR_ASM__ double2 atan2(double2 y, double2 x) __asm("air." _AIR_PREFIX_double "atan2.v2f64");
  __AIR_ASM__ double2 atanh(double2 x) __asm("air." _AIR_PREFIX_double "atanh.v2f64");
  __AIR_ASM__ double2 atanpi(double2 y_over_x) __asm("air." _AIR_PREFIX_double "atanpi.v2f64");
  __AIR_ASM__ double2 atan2pi(double2 y, double2 x) __asm("air." _AIR_PREFIX_double "atanpi2.v2f64");
  __AIR_ASM__ double2 cbrt(double2 x) __asm("air.cbrt.v2f64");
  __AIR_ASM__ double2 ceil(double2 x) __asm("air.ceil.v2f64");
  // We will produce the code for copysign
  __AIR_TGT__ double2 copysign(double2 x, double2 y);
  __AIR_ASM__ double2 cos(double2 x) __asm("air." _AIR_PREFIX_double "cos.v2f64");
  __AIR_ASM__ double2 cosh(double2 x) __asm("air." _AIR_PREFIX_double "cosh.v2f64");
  __AIR_ASM__ double2 cospi(double2 x) __asm("air.cospi.v2f64");
  __AIR_ASM__ double2 erf(double2 x) __asm("air." _AIR_PREFIX_double "erf.v2f64");
  __AIR_TGT__ double2 erfc(double2 x) __asm("air." _AIR_PREFIX_double "erfc.v2f64");
  __AIR_ASM__ double2 exp(double2 x) __asm("air." _AIR_PREFIX_double "exp.v2f64");
  __AIR_ASM__ double2 exp2(double2 x) __asm("air." _AIR_PREFIX_double "exp2.v2f64");
  __AIR_ASM__ double2 exp10(double2 x) __asm("air.exp10.v2f64");
  __AIR_ASM__ double2 expm1(double2 x) __asm("air.expm1.v2f64");
  __AIR_ASM__ double2 fabs(double2 x) __asm("air.fabs.v2f64");
  // We will provide fdim
  __AIR_TGT__ double2 fdim(double2 x, double2 y);
  __AIR_ASM__ double2 floor(double2 x) __asm("air.floor.v2f64");
  __AIR_ASM__ double2 fma(double2 x, double2 y, double2 z) __asm("air.fma.v2f64");
  __AIR_ASM__ double2 fmax(double2 x, double2 y) __asm("air.fmax.v2f64");
  __AIR_FUNC__ double2 fmax(double2 x, double y) {
    return fmax(x, (double2)(y));
  }
  __AIR_ASM__ double2 fmin(double2 x, double2 y) __asm("air.fmin.v2f64");
  __AIR_FUNC__ double2 fmin(double2 x, double y) {
    return fmin(x, (double2)(y));
  }
  __AIR_ASM__ double2 fmod(double2 x, double2 y) __asm("air.fmod.v2f64");
  __AIR_ASM__ double2 fract(double2 x, private double2 *iptr) __asm("air.fract.v2f64");
  __AIR_FUNC__ double2 fract(double2 x, global double2 * quo) {
    double2 pquo;
    double2 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ double2 fract(double2 x, local double2 * quo)  {
    double2 pquo;
    double2 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  // We will provide frexp and ilogb because this is not in AIR
  __AIR_TGT__ double2 frexp(double2 x, global int2 *exponent);
  __AIR_TGT__ double2 frexp(double2 x, local int2 *exponent);
  __AIR_TGT__ double2 frexp(double2 x, private int2 *exponent);
  __AIR_ASM__ double2 hypot(double2 y, double2 x) __asm("air.hypot.v2f64");
  __AIR_TGT__ int2 ilogb(double2 x);
  __AIR_ASM__ double2 ldexp(double2 x, int2 k) __asm("air.ldexp.v2f64");
  __AIR_ASM__ double2 lgamma(double2 x) __asm("air.lgamma.v2f64");
  __AIR_ASM__ double2 lgamma_r(double2 x, private int2 * signp) __asm("air.lgamma_r.v2f64");
  __AIR_FUNC__ double2 lgamma_r(double2 x, global int2 * signp) {
    int2 psignp;
    double2 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_FUNC__ double2 lgamma_r(double2 x, local int2 * signp)  {
    int2 psignp;
    double2 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_ASM__ double2 log(double2 x) __asm("air." _AIR_PREFIX_double "log.v2f64");
  __AIR_ASM__ double2 log2(double2 x) __asm("air." _AIR_PREFIX_double "log2.v2f64");
  __AIR_ASM__ double2 log10(double2 x) __asm("air.log10.v2f64");
  __AIR_ASM__ double2 log1p(double2 x) __asm("air.log1p.v2f64");
  __AIR_ASM__ double2 logb(double2 x) __asm("air.logb.v2f64");
  __AIR_ASM__ double2 mad(double2 x, double2 y, double2 z) __asm("air.mad.v2f64");
  // Targets provide maxmag and minmag.
  __AIR_TGT__ double2 maxmag(double2 x, double2 y);
  __AIR_TGT__ double2 minmag(double2 x, double2 y);
  __AIR_TGT__ double2 modf(double2 x, global double2 *intval);
  __AIR_TGT__ double2 modf(double2 x, local double2 *intval);
  __AIR_TGT__ double2 modf(double2 x, private double2 *intval);
  __AIR_TGT__ double2 nan(ulong2 x);
  __AIR_ASM__ double2 nextafter(double2 x, double2 y) __asm("air.nextafter.v2f64");
  __AIR_ASM__ double2 pow(double2 x, double2 y) __asm("air." _AIR_PREFIX_double "pow.v2f64");
  __AIR_ASM__ double2 pown(double2 x, int2 y) __asm("air.pown.v2f64");
  __AIR_ASM__ double2 powr(double2 x, double2 y) __asm("air.powr.v2f64");
  __AIR_ASM__ double2 remainder(double2 x, double2 y) __asm("air.remainder.v2f64");
  __AIR_ASM__ double2 remquo(double2 x, double2 y, private int2 * quo) __asm("air.remquo.v2f64");
  __AIR_FUNC__ double2 remquo(double2 x, double2 y, global int2 * quo) {
    int2 pquo;
    double2 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ double2 remquo(double2 x, double2 y, local int2 * quo)  {
    int2 pquo;
    double2 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_ASM__ double2 rint(double2 x) __asm("air.rint.v2f64");
  __AIR_ASM__ double2 rootn(double2 x, int2 y) __asm("air.rootn.v2f64");
  // FIXME: scalar rootn
  __AIR_ASM__ double2 round(double2 x) __asm("air." _AIR_PREFIX_double "round.v2f64");
  __AIR_ASM__ double2 rsqrt(double2 x) __asm("air." _AIR_PREFIX_double "rsqrt.v2f64");
  __AIR_ASM__ double2 sin(double2 x) __asm("air." _AIR_PREFIX_double "sin.v2f64");
  __AIR_ASM__ double2 sincos(double2 x, private double2 *cosval) __asm("air." _AIR_PREFIX_double "sincos.v2f64");
  __AIR_FUNC__ double2 sincos(double2 x, global double2 *cosval) {
    double2 pcosval;
    double2 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_FUNC__ double2 sincos(double2 x, local double2 *cosval) {
    double2 pcosval;
    double2 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_ASM__ double2 sinh(double2 x) __asm("air." _AIR_PREFIX_double "sinh.v2f64");
  __AIR_ASM__ double2 sinpi(double2 x) __asm("air.sinpi.v2f64");
  __AIR_ASM__ double2 sqrt(double2 x) __asm("air." _AIR_PREFIX_double "sqrt.v2f64");
  __AIR_ASM__ double2 tan(double2 x) __asm("air." _AIR_PREFIX_double "tan.v2f64");
  __AIR_ASM__ double2 tanh(double2 x) __asm("air." _AIR_PREFIX_double "tanh.v2f64");
  __AIR_ASM__ double2 tanpi(double2 x) __asm("air.tanpi.v2f64");
  __AIR_ASM__ double2 tgamma(double2 x) __asm("air.tgamma.v2f64");
  __AIR_ASM__ double2 trunc(double2 x) __asm("air.trunc.v2f64");


#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float3 acos(float3 x) __asm("air." _AIR_PREFIX_float "acos.v3f32");
  __AIR_ASM__ float3 acosh(float3 x) __asm("air." _AIR_PREFIX_float "acosh.v3f32");
  __AIR_ASM__ float3 acospi(float3 x) __asm("air.acospi.v3f32");
  __AIR_ASM__ float3 asin(float3 x) __asm("air." _AIR_PREFIX_float "asin.v3f32");
  __AIR_ASM__ float3 asinh(float3 x) __asm("air." _AIR_PREFIX_float "asinh.v3f32");
  __AIR_ASM__ float3 asinpi(float3 x) __asm("air.asinpi.v3f32");
  __AIR_ASM__ float3 atan(float3 y_over_x) __asm("air." _AIR_PREFIX_float "atan.v3f32");
  __AIR_ASM__ float3 atan2(float3 y, float3 x) __asm("air." _AIR_PREFIX_float "atan2.v3f32");
  __AIR_ASM__ float3 atanh(float3 x) __asm("air." _AIR_PREFIX_float "atanh.v3f32");
  __AIR_ASM__ float3 atanpi(float3 y_over_x) __asm("air." _AIR_PREFIX_float "atanpi.v3f32");
  __AIR_ASM__ float3 atan2pi(float3 y, float3 x) __asm("air." _AIR_PREFIX_float "atanpi2.v3f32");
  __AIR_ASM__ float3 cbrt(float3 x) __asm("air.cbrt.v3f32");
  __AIR_ASM__ float3 ceil(float3 x) __asm("air.ceil.v3f32");
  // We will produce the code for copysign
  __AIR_TGT__ float3 copysign(float3 x, float3 y);
  __AIR_ASM__ float3 cos(float3 x) __asm("air." _AIR_PREFIX_float "cos.v3f32");
  __AIR_ASM__ float3 cosh(float3 x) __asm("air." _AIR_PREFIX_float "cosh.v3f32");
  __AIR_ASM__ float3 cospi(float3 x) __asm("air.cospi.v3f32");
  __AIR_ASM__ float3 erf(float3 x) __asm("air." _AIR_PREFIX_float "erf.v3f32");
  __AIR_TGT__ float3 erfc(float3 x) __asm("air." _AIR_PREFIX_float "erfc.v3f32");
  __AIR_ASM__ float3 exp(float3 x) __asm("air." _AIR_PREFIX_float "exp.v3f32");
  __AIR_ASM__ float3 exp2(float3 x) __asm("air." _AIR_PREFIX_float "exp2.v3f32");
#if defined(__FAST_RELAXED_MATH__)
  __AIR_FUNC__ float3 exp10(float3 x) {
    return exp2(x * LOG2_10F);
  }
#else
  __AIR_ASM__ float3 exp10(float3 x) __asm("air.exp10.v3f32");
#endif
  __AIR_ASM__ float3 expm1(float3 x) __asm("air.expm1.v3f32");
  __AIR_ASM__ float3 fabs(float3 x) __asm("air.fabs.v3f32");
  // We will provide fdim
  __AIR_TGT__ float3 fdim(float3 x, float3 y);
  __AIR_ASM__ float3 floor(float3 x) __asm("air.floor.v3f32");
  __AIR_ASM__ float3 fma(float3 x, float3 y, float3 z) __asm("air.fma.v3f32");
  __AIR_ASM__ float3 fmax(float3 x, float3 y) __asm("air.fmax.v3f32");
  __AIR_FUNC__ float3 fmax(float3 x, float y) {
    return fmax(x, (float3)(y));
  }
  __AIR_ASM__ float3 fmin(float3 x, float3 y) __asm("air.fmin.v3f32");
  __AIR_FUNC__ float3 fmin(float3 x, float y) {
    return fmin(x, (float3)(y));
  }
  __AIR_ASM__ float3 fmod(float3 x, float3 y) __asm("air.fmod.v3f32");
  __AIR_ASM__ float3 fract(float3 x, private float3 *iptr) __asm("air.fract.v3f32");
  __AIR_FUNC__ float3 fract(float3 x, global float3 * quo) {
    float3 pquo;
    float3 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ float3 fract(float3 x, local float3 * quo)  {
    float3 pquo;
    float3 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  // We will provide frexp and ilogb because this is not in AIR
  __AIR_TGT__ float3 frexp(float3 x, global int3 *exponent);
  __AIR_TGT__ float3 frexp(float3 x, local int3 *exponent);
  __AIR_TGT__ float3 frexp(float3 x, private int3 *exponent);
  __AIR_ASM__ float3 hypot(float3 y, float3 x) __asm("air.hypot.v3f32");
  __AIR_TGT__ int3 ilogb(float3 x);
  __AIR_ASM__ float3 ldexp(float3 x, int3 k) __asm("air.ldexp.v3f32");
  __AIR_ASM__ float3 lgamma(float3 x) __asm("air.lgamma.v3f32");
  __AIR_ASM__ float3 lgamma_r(float3 x, private int3 * signp) __asm("air.lgamma_r.v3f32");
  __AIR_FUNC__ float3 lgamma_r(float3 x, global int3 * signp) {
    int3 psignp;
    float3 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_FUNC__ float3 lgamma_r(float3 x, local int3 * signp)  {
    int3 psignp;
    float3 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_ASM__ float3 log(float3 x) __asm("air." _AIR_PREFIX_float "log.v3f32");
  __AIR_ASM__ float3 log2(float3 x) __asm("air." _AIR_PREFIX_float "log2.v3f32");
#if defined(__FAST_RELAXED_MATH__)
  __AIR_FUNC__ float3 log10(float3 x) {
    return log2(x) * LOG10_2F;
  }
#else
  __AIR_ASM__ float3 log10(float3 x) __asm("air.log10.v3f32");
#endif
  __AIR_ASM__ float3 log1p(float3 x) __asm("air.log1p.v3f32");
  __AIR_ASM__ float3 logb(float3 x) __asm("air.logb.v3f32");
  __AIR_ASM__ float3 mad(float3 x, float3 y, float3 z) __asm("air.mad.v3f32");
  // Targets provide maxmag and minmag.
  __AIR_TGT__ float3 maxmag(float3 x, float3 y);
  __AIR_TGT__ float3 minmag(float3 x, float3 y);
  __AIR_TGT__ float3 modf(float3 x, global float3 *intval);
  __AIR_TGT__ float3 modf(float3 x, local float3 *intval);
  __AIR_TGT__ float3 modf(float3 x, private float3 *intval);
  __AIR_TGT__ float3 nan(uint3 x);
  __AIR_ASM__ float3 native_cos(float3 x) __asm("air.fast_cos.v3f32");
  // Fixme: (rdar://problem/19724906) Need to generate a fast-divide every time here; something along the lines of:
  // 
  //   <result> = fdiv fast float %x, %y
  //
  // Keeping it as the basic implementation for now just to get it checked in.
  __AIR_FUNC__ float3 native_divide(float3 x, float3 y) {
    return x / y;
  }
  __AIR_ASM__ float3 native_exp(float3 x) __asm("air.fast_exp.v3f32");
  __AIR_ASM__ float3 native_exp2(float3 x) __asm("air.fast_exp2.v3f32");
  __AIR_FUNC__ float3 native_exp10(float3 x) {
    return native_exp2(x * LOG2_10F);
  }
  __AIR_ASM__ float3 native_log(float3 x) __asm("air.fast_log.v3f32");
  __AIR_ASM__ float3 native_log2(float3 x) __asm("air.fast_log2.v3f32");
  __AIR_FUNC__ float3 native_log10(float3 x) {
    return native_log2(x) * LOG10_2F;
  }
  __AIR_ASM__ float3 native_powr(float3 x, float3 y) __asm("air.fast_powr.v3f32");
  __AIR_FUNC__ float3 native_recip(float3 x) {
    return native_divide(1.0f, x);
  }
  __AIR_ASM__ float3 native_rsqrt(float3 x) __asm("air.fast_rsqrt.v3f32");
  __AIR_ASM__ float3 native_sin(float3 x) __asm("air.fast_sin.v3f32");
  __AIR_ASM__ float3 native_sqrt(float3 x) __asm("air.fast_sqrt.v3f32");
  __AIR_ASM__ float3 native_tan(float3 x) __asm("air.fast_tan.v3f32");
  __AIR_ASM__ float3 nextafter(float3 x, float3 y) __asm("air.nextafter.v3f32");
  __AIR_ASM__ float3 pow(float3 x, float3 y) __asm("air." _AIR_PREFIX_float "pow.v3f32");
  __AIR_ASM__ float3 pown(float3 x, int3 y) __asm("air.pown.v3f32");
  __AIR_ASM__ float3 powr(float3 x, float3 y) __asm("air.powr.v3f32");
  __AIR_ASM__ float3 remainder(float3 x, float3 y) __asm("air.remainder.v3f32");
  __AIR_ASM__ float3 remquo(float3 x, float3 y, private int3 * quo) __asm("air.remquo.v3f32");
  __AIR_FUNC__ float3 remquo(float3 x, float3 y, global int3 * quo) {
    int3 pquo;
    float3 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ float3 remquo(float3 x, float3 y, local int3 * quo)  {
    int3 pquo;
    float3 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_ASM__ float3 rint(float3 x) __asm("air.rint.v3f32");
  __AIR_ASM__ float3 rootn(float3 x, int3 y) __asm("air.rootn.v3f32");
  // FIXME: scalar rootn
  __AIR_ASM__ float3 round(float3 x) __asm("air." _AIR_PREFIX_float "round.v3f32");
  __AIR_ASM__ float3 rsqrt(float3 x) __asm("air." _AIR_PREFIX_float "rsqrt.v3f32");
  __AIR_ASM__ float3 sin(float3 x) __asm("air." _AIR_PREFIX_float "sin.v3f32");
  __AIR_ASM__ float3 sincos(float3 x, private float3 *cosval) __asm("air." _AIR_PREFIX_float "sincos.v3f32");
  __AIR_FUNC__ float3 sincos(float3 x, global float3 *cosval) {
    float3 pcosval;
    float3 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_FUNC__ float3 sincos(float3 x, local float3 *cosval) {
    float3 pcosval;
    float3 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_ASM__ float3 sinh(float3 x) __asm("air." _AIR_PREFIX_float "sinh.v3f32");
  __AIR_ASM__ float3 sinpi(float3 x) __asm("air.sinpi.v3f32");
  __AIR_ASM__ float3 sqrt(float3 x) __asm("air." _AIR_PREFIX_float "sqrt.v3f32");
  __AIR_ASM__ float3 tan(float3 x) __asm("air." _AIR_PREFIX_float "tan.v3f32");
  __AIR_ASM__ float3 tanh(float3 x) __asm("air." _AIR_PREFIX_float "tanh.v3f32");
  __AIR_ASM__ float3 tanpi(float3 x) __asm("air.tanpi.v3f32");
  __AIR_ASM__ float3 tgamma(float3 x) __asm("air.tgamma.v3f32");
  __AIR_ASM__ float3 trunc(float3 x) __asm("air.trunc.v3f32");

  __AIR_ASM__ float3 half_rsqrt(float3 x) __asm("air.fast_rsqrt.v3f32");
  __AIR_ASM__ float3 half_sqrt(float3 x) __asm("air.fast_sqrt.v3f32");


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_ASM__ double3 acos(double3 x) __asm("air." _AIR_PREFIX_double "acos.v3f64");
  __AIR_ASM__ double3 acosh(double3 x) __asm("air." _AIR_PREFIX_double "acosh.v3f64");
  __AIR_ASM__ double3 acospi(double3 x) __asm("air.acospi.v3f64");
  __AIR_ASM__ double3 asin(double3 x) __asm("air." _AIR_PREFIX_double "asin.v3f64");
  __AIR_ASM__ double3 asinh(double3 x) __asm("air." _AIR_PREFIX_double "asinh.v3f64");
  __AIR_ASM__ double3 asinpi(double3 x) __asm("air.asinpi.v3f64");
  __AIR_ASM__ double3 atan(double3 y_over_x) __asm("air." _AIR_PREFIX_double "atan.v3f64");
  __AIR_ASM__ double3 atan2(double3 y, double3 x) __asm("air." _AIR_PREFIX_double "atan2.v3f64");
  __AIR_ASM__ double3 atanh(double3 x) __asm("air." _AIR_PREFIX_double "atanh.v3f64");
  __AIR_ASM__ double3 atanpi(double3 y_over_x) __asm("air." _AIR_PREFIX_double "atanpi.v3f64");
  __AIR_ASM__ double3 atan2pi(double3 y, double3 x) __asm("air." _AIR_PREFIX_double "atanpi2.v3f64");
  __AIR_ASM__ double3 cbrt(double3 x) __asm("air.cbrt.v3f64");
  __AIR_ASM__ double3 ceil(double3 x) __asm("air.ceil.v3f64");
  // We will produce the code for copysign
  __AIR_TGT__ double3 copysign(double3 x, double3 y);
  __AIR_ASM__ double3 cos(double3 x) __asm("air." _AIR_PREFIX_double "cos.v3f64");
  __AIR_ASM__ double3 cosh(double3 x) __asm("air." _AIR_PREFIX_double "cosh.v3f64");
  __AIR_ASM__ double3 cospi(double3 x) __asm("air.cospi.v3f64");
  __AIR_ASM__ double3 erf(double3 x) __asm("air." _AIR_PREFIX_double "erf.v3f64");
  __AIR_TGT__ double3 erfc(double3 x) __asm("air." _AIR_PREFIX_double "erfc.v3f64");
  __AIR_ASM__ double3 exp(double3 x) __asm("air." _AIR_PREFIX_double "exp.v3f64");
  __AIR_ASM__ double3 exp2(double3 x) __asm("air." _AIR_PREFIX_double "exp2.v3f64");
  __AIR_ASM__ double3 exp10(double3 x) __asm("air.exp10.v3f64");
  __AIR_ASM__ double3 expm1(double3 x) __asm("air.expm1.v3f64");
  __AIR_ASM__ double3 fabs(double3 x) __asm("air.fabs.v3f64");
  // We will provide fdim
  __AIR_TGT__ double3 fdim(double3 x, double3 y);
  __AIR_ASM__ double3 floor(double3 x) __asm("air.floor.v3f64");
  __AIR_ASM__ double3 fma(double3 x, double3 y, double3 z) __asm("air.fma.v3f64");
  __AIR_ASM__ double3 fmax(double3 x, double3 y) __asm("air.fmax.v3f64");
  __AIR_FUNC__ double3 fmax(double3 x, double y) {
    return fmax(x, (double3)(y));
  }
  __AIR_ASM__ double3 fmin(double3 x, double3 y) __asm("air.fmin.v3f64");
  __AIR_FUNC__ double3 fmin(double3 x, double y) {
    return fmin(x, (double3)(y));
  }
  __AIR_ASM__ double3 fmod(double3 x, double3 y) __asm("air.fmod.v3f64");
  __AIR_ASM__ double3 fract(double3 x, private double3 *iptr) __asm("air.fract.v3f64");
  __AIR_FUNC__ double3 fract(double3 x, global double3 * quo) {
    double3 pquo;
    double3 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ double3 fract(double3 x, local double3 * quo)  {
    double3 pquo;
    double3 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  // We will provide frexp and ilogb because this is not in AIR
  __AIR_TGT__ double3 frexp(double3 x, global int3 *exponent);
  __AIR_TGT__ double3 frexp(double3 x, local int3 *exponent);
  __AIR_TGT__ double3 frexp(double3 x, private int3 *exponent);
  __AIR_ASM__ double3 hypot(double3 y, double3 x) __asm("air.hypot.v3f64");
  __AIR_TGT__ int3 ilogb(double3 x);
  __AIR_ASM__ double3 ldexp(double3 x, int3 k) __asm("air.ldexp.v3f64");
  __AIR_ASM__ double3 lgamma(double3 x) __asm("air.lgamma.v3f64");
  __AIR_ASM__ double3 lgamma_r(double3 x, private int3 * signp) __asm("air.lgamma_r.v3f64");
  __AIR_FUNC__ double3 lgamma_r(double3 x, global int3 * signp) {
    int3 psignp;
    double3 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_FUNC__ double3 lgamma_r(double3 x, local int3 * signp)  {
    int3 psignp;
    double3 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_ASM__ double3 log(double3 x) __asm("air." _AIR_PREFIX_double "log.v3f64");
  __AIR_ASM__ double3 log2(double3 x) __asm("air." _AIR_PREFIX_double "log2.v3f64");
  __AIR_ASM__ double3 log10(double3 x) __asm("air.log10.v3f64");
  __AIR_ASM__ double3 log1p(double3 x) __asm("air.log1p.v3f64");
  __AIR_ASM__ double3 logb(double3 x) __asm("air.logb.v3f64");
  __AIR_ASM__ double3 mad(double3 x, double3 y, double3 z) __asm("air.mad.v3f64");
  // Targets provide maxmag and minmag.
  __AIR_TGT__ double3 maxmag(double3 x, double3 y);
  __AIR_TGT__ double3 minmag(double3 x, double3 y);
  __AIR_TGT__ double3 modf(double3 x, global double3 *intval);
  __AIR_TGT__ double3 modf(double3 x, local double3 *intval);
  __AIR_TGT__ double3 modf(double3 x, private double3 *intval);
  __AIR_TGT__ double3 nan(ulong3 x);
  __AIR_ASM__ double3 nextafter(double3 x, double3 y) __asm("air.nextafter.v3f64");
  __AIR_ASM__ double3 pow(double3 x, double3 y) __asm("air." _AIR_PREFIX_double "pow.v3f64");
  __AIR_ASM__ double3 pown(double3 x, int3 y) __asm("air.pown.v3f64");
  __AIR_ASM__ double3 powr(double3 x, double3 y) __asm("air.powr.v3f64");
  __AIR_ASM__ double3 remainder(double3 x, double3 y) __asm("air.remainder.v3f64");
  __AIR_ASM__ double3 remquo(double3 x, double3 y, private int3 * quo) __asm("air.remquo.v3f64");
  __AIR_FUNC__ double3 remquo(double3 x, double3 y, global int3 * quo) {
    int3 pquo;
    double3 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ double3 remquo(double3 x, double3 y, local int3 * quo)  {
    int3 pquo;
    double3 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_ASM__ double3 rint(double3 x) __asm("air.rint.v3f64");
  __AIR_ASM__ double3 rootn(double3 x, int3 y) __asm("air.rootn.v3f64");
  // FIXME: scalar rootn
  __AIR_ASM__ double3 round(double3 x) __asm("air." _AIR_PREFIX_double "round.v3f64");
  __AIR_ASM__ double3 rsqrt(double3 x) __asm("air." _AIR_PREFIX_double "rsqrt.v3f64");
  __AIR_ASM__ double3 sin(double3 x) __asm("air." _AIR_PREFIX_double "sin.v3f64");
  __AIR_ASM__ double3 sincos(double3 x, private double3 *cosval) __asm("air." _AIR_PREFIX_double "sincos.v3f64");
  __AIR_FUNC__ double3 sincos(double3 x, global double3 *cosval) {
    double3 pcosval;
    double3 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_FUNC__ double3 sincos(double3 x, local double3 *cosval) {
    double3 pcosval;
    double3 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_ASM__ double3 sinh(double3 x) __asm("air." _AIR_PREFIX_double "sinh.v3f64");
  __AIR_ASM__ double3 sinpi(double3 x) __asm("air.sinpi.v3f64");
  __AIR_ASM__ double3 sqrt(double3 x) __asm("air." _AIR_PREFIX_double "sqrt.v3f64");
  __AIR_ASM__ double3 tan(double3 x) __asm("air." _AIR_PREFIX_double "tan.v3f64");
  __AIR_ASM__ double3 tanh(double3 x) __asm("air." _AIR_PREFIX_double "tanh.v3f64");
  __AIR_ASM__ double3 tanpi(double3 x) __asm("air.tanpi.v3f64");
  __AIR_ASM__ double3 tgamma(double3 x) __asm("air.tgamma.v3f64");
  __AIR_ASM__ double3 trunc(double3 x) __asm("air.trunc.v3f64");


#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float4 acos(float4 x) __asm("air." _AIR_PREFIX_float "acos.v4f32");
  __AIR_ASM__ float4 acosh(float4 x) __asm("air." _AIR_PREFIX_float "acosh.v4f32");
  __AIR_ASM__ float4 acospi(float4 x) __asm("air.acospi.v4f32");
  __AIR_ASM__ float4 asin(float4 x) __asm("air." _AIR_PREFIX_float "asin.v4f32");
  __AIR_ASM__ float4 asinh(float4 x) __asm("air." _AIR_PREFIX_float "asinh.v4f32");
  __AIR_ASM__ float4 asinpi(float4 x) __asm("air.asinpi.v4f32");
  __AIR_ASM__ float4 atan(float4 y_over_x) __asm("air." _AIR_PREFIX_float "atan.v4f32");
  __AIR_ASM__ float4 atan2(float4 y, float4 x) __asm("air." _AIR_PREFIX_float "atan2.v4f32");
  __AIR_ASM__ float4 atanh(float4 x) __asm("air." _AIR_PREFIX_float "atanh.v4f32");
  __AIR_ASM__ float4 atanpi(float4 y_over_x) __asm("air." _AIR_PREFIX_float "atanpi.v4f32");
  __AIR_ASM__ float4 atan2pi(float4 y, float4 x) __asm("air." _AIR_PREFIX_float "atanpi2.v4f32");
  __AIR_ASM__ float4 cbrt(float4 x) __asm("air.cbrt.v4f32");
  __AIR_ASM__ float4 ceil(float4 x) __asm("air.ceil.v4f32");
  // We will produce the code for copysign
  __AIR_TGT__ float4 copysign(float4 x, float4 y);
  __AIR_ASM__ float4 cos(float4 x) __asm("air." _AIR_PREFIX_float "cos.v4f32");
  __AIR_ASM__ float4 cosh(float4 x) __asm("air." _AIR_PREFIX_float "cosh.v4f32");
  __AIR_ASM__ float4 cospi(float4 x) __asm("air.cospi.v4f32");
  __AIR_ASM__ float4 erf(float4 x) __asm("air." _AIR_PREFIX_float "erf.v4f32");
  __AIR_TGT__ float4 erfc(float4 x) __asm("air." _AIR_PREFIX_float "erfc.v4f32");
  __AIR_ASM__ float4 exp(float4 x) __asm("air." _AIR_PREFIX_float "exp.v4f32");
  __AIR_ASM__ float4 exp2(float4 x) __asm("air." _AIR_PREFIX_float "exp2.v4f32");
#if defined(__FAST_RELAXED_MATH__)
  __AIR_FUNC__ float4 exp10(float4 x) {
    return exp2(x * LOG2_10F);
  }
#else
  __AIR_ASM__ float4 exp10(float4 x) __asm("air.exp10.v4f32");
#endif
  __AIR_ASM__ float4 expm1(float4 x) __asm("air.expm1.v4f32");
  __AIR_ASM__ float4 fabs(float4 x) __asm("air.fabs.v4f32");
  // We will provide fdim
  __AIR_TGT__ float4 fdim(float4 x, float4 y);
  __AIR_ASM__ float4 floor(float4 x) __asm("air.floor.v4f32");
  __AIR_ASM__ float4 fma(float4 x, float4 y, float4 z) __asm("air.fma.v4f32");
  __AIR_ASM__ float4 fmax(float4 x, float4 y) __asm("air.fmax.v4f32");
  __AIR_FUNC__ float4 fmax(float4 x, float y) {
    return fmax(x, (float4)(y));
  }
  __AIR_ASM__ float4 fmin(float4 x, float4 y) __asm("air.fmin.v4f32");
  __AIR_FUNC__ float4 fmin(float4 x, float y) {
    return fmin(x, (float4)(y));
  }
  __AIR_ASM__ float4 fmod(float4 x, float4 y) __asm("air.fmod.v4f32");
  __AIR_ASM__ float4 fract(float4 x, private float4 *iptr) __asm("air.fract.v4f32");
  __AIR_FUNC__ float4 fract(float4 x, global float4 * quo) {
    float4 pquo;
    float4 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ float4 fract(float4 x, local float4 * quo)  {
    float4 pquo;
    float4 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  // We will provide frexp and ilogb because this is not in AIR
  __AIR_TGT__ float4 frexp(float4 x, global int4 *exponent);
  __AIR_TGT__ float4 frexp(float4 x, local int4 *exponent);
  __AIR_TGT__ float4 frexp(float4 x, private int4 *exponent);
  __AIR_ASM__ float4 hypot(float4 y, float4 x) __asm("air.hypot.v4f32");
  __AIR_TGT__ int4 ilogb(float4 x);
  __AIR_ASM__ float4 ldexp(float4 x, int4 k) __asm("air.ldexp.v4f32");
  __AIR_ASM__ float4 lgamma(float4 x) __asm("air.lgamma.v4f32");
  __AIR_ASM__ float4 lgamma_r(float4 x, private int4 * signp) __asm("air.lgamma_r.v4f32");
  __AIR_FUNC__ float4 lgamma_r(float4 x, global int4 * signp) {
    int4 psignp;
    float4 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_FUNC__ float4 lgamma_r(float4 x, local int4 * signp)  {
    int4 psignp;
    float4 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_ASM__ float4 log(float4 x) __asm("air." _AIR_PREFIX_float "log.v4f32");
  __AIR_ASM__ float4 log2(float4 x) __asm("air." _AIR_PREFIX_float "log2.v4f32");
#if defined(__FAST_RELAXED_MATH__)
  __AIR_FUNC__ float4 log10(float4 x) {
    return log2(x) * LOG10_2F;
  }
#else
  __AIR_ASM__ float4 log10(float4 x) __asm("air.log10.v4f32");
#endif
  __AIR_ASM__ float4 log1p(float4 x) __asm("air.log1p.v4f32");
  __AIR_ASM__ float4 logb(float4 x) __asm("air.logb.v4f32");
  __AIR_ASM__ float4 mad(float4 x, float4 y, float4 z) __asm("air.mad.v4f32");
  // Targets provide maxmag and minmag.
  __AIR_TGT__ float4 maxmag(float4 x, float4 y);
  __AIR_TGT__ float4 minmag(float4 x, float4 y);
  __AIR_TGT__ float4 modf(float4 x, global float4 *intval);
  __AIR_TGT__ float4 modf(float4 x, local float4 *intval);
  __AIR_TGT__ float4 modf(float4 x, private float4 *intval);
  __AIR_TGT__ float4 nan(uint4 x);
  __AIR_ASM__ float4 native_cos(float4 x) __asm("air.fast_cos.v4f32");
  // Fixme: (rdar://problem/19724906) Need to generate a fast-divide every time here; something along the lines of:
  // 
  //   <result> = fdiv fast float %x, %y
  //
  // Keeping it as the basic implementation for now just to get it checked in.
  __AIR_FUNC__ float4 native_divide(float4 x, float4 y) {
    return x / y;
  }
  __AIR_ASM__ float4 native_exp(float4 x) __asm("air.fast_exp.v4f32");
  __AIR_ASM__ float4 native_exp2(float4 x) __asm("air.fast_exp2.v4f32");
  __AIR_FUNC__ float4 native_exp10(float4 x) {
    return native_exp2(x * LOG2_10F);
  }
  __AIR_ASM__ float4 native_log(float4 x) __asm("air.fast_log.v4f32");
  __AIR_ASM__ float4 native_log2(float4 x) __asm("air.fast_log2.v4f32");
  __AIR_FUNC__ float4 native_log10(float4 x) {
    return native_log2(x) * LOG10_2F;
  }
  __AIR_ASM__ float4 native_powr(float4 x, float4 y) __asm("air.fast_powr.v4f32");
  __AIR_FUNC__ float4 native_recip(float4 x) {
    return native_divide(1.0f, x);
  }
  __AIR_ASM__ float4 native_rsqrt(float4 x) __asm("air.fast_rsqrt.v4f32");
  __AIR_ASM__ float4 native_sin(float4 x) __asm("air.fast_sin.v4f32");
  __AIR_ASM__ float4 native_sqrt(float4 x) __asm("air.fast_sqrt.v4f32");
  __AIR_ASM__ float4 native_tan(float4 x) __asm("air.fast_tan.v4f32");
  __AIR_ASM__ float4 nextafter(float4 x, float4 y) __asm("air.nextafter.v4f32");
  __AIR_ASM__ float4 pow(float4 x, float4 y) __asm("air." _AIR_PREFIX_float "pow.v4f32");
  __AIR_ASM__ float4 pown(float4 x, int4 y) __asm("air.pown.v4f32");
  __AIR_ASM__ float4 powr(float4 x, float4 y) __asm("air.powr.v4f32");
  __AIR_ASM__ float4 remainder(float4 x, float4 y) __asm("air.remainder.v4f32");
  __AIR_ASM__ float4 remquo(float4 x, float4 y, private int4 * quo) __asm("air.remquo.v4f32");
  __AIR_FUNC__ float4 remquo(float4 x, float4 y, global int4 * quo) {
    int4 pquo;
    float4 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ float4 remquo(float4 x, float4 y, local int4 * quo)  {
    int4 pquo;
    float4 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_ASM__ float4 rint(float4 x) __asm("air.rint.v4f32");
  __AIR_ASM__ float4 rootn(float4 x, int4 y) __asm("air.rootn.v4f32");
  // FIXME: scalar rootn
  __AIR_ASM__ float4 round(float4 x) __asm("air." _AIR_PREFIX_float "round.v4f32");
  __AIR_ASM__ float4 rsqrt(float4 x) __asm("air." _AIR_PREFIX_float "rsqrt.v4f32");
  __AIR_ASM__ float4 sin(float4 x) __asm("air." _AIR_PREFIX_float "sin.v4f32");
  __AIR_ASM__ float4 sincos(float4 x, private float4 *cosval) __asm("air." _AIR_PREFIX_float "sincos.v4f32");
  __AIR_FUNC__ float4 sincos(float4 x, global float4 *cosval) {
    float4 pcosval;
    float4 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_FUNC__ float4 sincos(float4 x, local float4 *cosval) {
    float4 pcosval;
    float4 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_ASM__ float4 sinh(float4 x) __asm("air." _AIR_PREFIX_float "sinh.v4f32");
  __AIR_ASM__ float4 sinpi(float4 x) __asm("air.sinpi.v4f32");
  __AIR_ASM__ float4 sqrt(float4 x) __asm("air." _AIR_PREFIX_float "sqrt.v4f32");
  __AIR_ASM__ float4 tan(float4 x) __asm("air." _AIR_PREFIX_float "tan.v4f32");
  __AIR_ASM__ float4 tanh(float4 x) __asm("air." _AIR_PREFIX_float "tanh.v4f32");
  __AIR_ASM__ float4 tanpi(float4 x) __asm("air.tanpi.v4f32");
  __AIR_ASM__ float4 tgamma(float4 x) __asm("air.tgamma.v4f32");
  __AIR_ASM__ float4 trunc(float4 x) __asm("air.trunc.v4f32");

  __AIR_ASM__ float4 half_rsqrt(float4 x) __asm("air.fast_rsqrt.v4f32");
  __AIR_ASM__ float4 half_sqrt(float4 x) __asm("air.fast_sqrt.v4f32");


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_ASM__ double4 acos(double4 x) __asm("air." _AIR_PREFIX_double "acos.v4f64");
  __AIR_ASM__ double4 acosh(double4 x) __asm("air." _AIR_PREFIX_double "acosh.v4f64");
  __AIR_ASM__ double4 acospi(double4 x) __asm("air.acospi.v4f64");
  __AIR_ASM__ double4 asin(double4 x) __asm("air." _AIR_PREFIX_double "asin.v4f64");
  __AIR_ASM__ double4 asinh(double4 x) __asm("air." _AIR_PREFIX_double "asinh.v4f64");
  __AIR_ASM__ double4 asinpi(double4 x) __asm("air.asinpi.v4f64");
  __AIR_ASM__ double4 atan(double4 y_over_x) __asm("air." _AIR_PREFIX_double "atan.v4f64");
  __AIR_ASM__ double4 atan2(double4 y, double4 x) __asm("air." _AIR_PREFIX_double "atan2.v4f64");
  __AIR_ASM__ double4 atanh(double4 x) __asm("air." _AIR_PREFIX_double "atanh.v4f64");
  __AIR_ASM__ double4 atanpi(double4 y_over_x) __asm("air." _AIR_PREFIX_double "atanpi.v4f64");
  __AIR_ASM__ double4 atan2pi(double4 y, double4 x) __asm("air." _AIR_PREFIX_double "atanpi2.v4f64");
  __AIR_ASM__ double4 cbrt(double4 x) __asm("air.cbrt.v4f64");
  __AIR_ASM__ double4 ceil(double4 x) __asm("air.ceil.v4f64");
  // We will produce the code for copysign
  __AIR_TGT__ double4 copysign(double4 x, double4 y);
  __AIR_ASM__ double4 cos(double4 x) __asm("air." _AIR_PREFIX_double "cos.v4f64");
  __AIR_ASM__ double4 cosh(double4 x) __asm("air." _AIR_PREFIX_double "cosh.v4f64");
  __AIR_ASM__ double4 cospi(double4 x) __asm("air.cospi.v4f64");
  __AIR_ASM__ double4 erf(double4 x) __asm("air." _AIR_PREFIX_double "erf.v4f64");
  __AIR_TGT__ double4 erfc(double4 x) __asm("air." _AIR_PREFIX_double "erfc.v4f64");
  __AIR_ASM__ double4 exp(double4 x) __asm("air." _AIR_PREFIX_double "exp.v4f64");
  __AIR_ASM__ double4 exp2(double4 x) __asm("air." _AIR_PREFIX_double "exp2.v4f64");
  __AIR_ASM__ double4 exp10(double4 x) __asm("air.exp10.v4f64");
  __AIR_ASM__ double4 expm1(double4 x) __asm("air.expm1.v4f64");
  __AIR_ASM__ double4 fabs(double4 x) __asm("air.fabs.v4f64");
  // We will provide fdim
  __AIR_TGT__ double4 fdim(double4 x, double4 y);
  __AIR_ASM__ double4 floor(double4 x) __asm("air.floor.v4f64");
  __AIR_ASM__ double4 fma(double4 x, double4 y, double4 z) __asm("air.fma.v4f64");
  __AIR_ASM__ double4 fmax(double4 x, double4 y) __asm("air.fmax.v4f64");
  __AIR_FUNC__ double4 fmax(double4 x, double y) {
    return fmax(x, (double4)(y));
  }
  __AIR_ASM__ double4 fmin(double4 x, double4 y) __asm("air.fmin.v4f64");
  __AIR_FUNC__ double4 fmin(double4 x, double y) {
    return fmin(x, (double4)(y));
  }
  __AIR_ASM__ double4 fmod(double4 x, double4 y) __asm("air.fmod.v4f64");
  __AIR_ASM__ double4 fract(double4 x, private double4 *iptr) __asm("air.fract.v4f64");
  __AIR_FUNC__ double4 fract(double4 x, global double4 * quo) {
    double4 pquo;
    double4 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ double4 fract(double4 x, local double4 * quo)  {
    double4 pquo;
    double4 res = fract(x, &pquo);
    *quo = pquo;
    return res;
  }
  // We will provide frexp and ilogb because this is not in AIR
  __AIR_TGT__ double4 frexp(double4 x, global int4 *exponent);
  __AIR_TGT__ double4 frexp(double4 x, local int4 *exponent);
  __AIR_TGT__ double4 frexp(double4 x, private int4 *exponent);
  __AIR_ASM__ double4 hypot(double4 y, double4 x) __asm("air.hypot.v4f64");
  __AIR_TGT__ int4 ilogb(double4 x);
  __AIR_ASM__ double4 ldexp(double4 x, int4 k) __asm("air.ldexp.v4f64");
  __AIR_ASM__ double4 lgamma(double4 x) __asm("air.lgamma.v4f64");
  __AIR_ASM__ double4 lgamma_r(double4 x, private int4 * signp) __asm("air.lgamma_r.v4f64");
  __AIR_FUNC__ double4 lgamma_r(double4 x, global int4 * signp) {
    int4 psignp;
    double4 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_FUNC__ double4 lgamma_r(double4 x, local int4 * signp)  {
    int4 psignp;
    double4 res = lgamma_r(x, &psignp);
    *signp = psignp;
    return res;
  }
  __AIR_ASM__ double4 log(double4 x) __asm("air." _AIR_PREFIX_double "log.v4f64");
  __AIR_ASM__ double4 log2(double4 x) __asm("air." _AIR_PREFIX_double "log2.v4f64");
  __AIR_ASM__ double4 log10(double4 x) __asm("air.log10.v4f64");
  __AIR_ASM__ double4 log1p(double4 x) __asm("air.log1p.v4f64");
  __AIR_ASM__ double4 logb(double4 x) __asm("air.logb.v4f64");
  __AIR_ASM__ double4 mad(double4 x, double4 y, double4 z) __asm("air.mad.v4f64");
  // Targets provide maxmag and minmag.
  __AIR_TGT__ double4 maxmag(double4 x, double4 y);
  __AIR_TGT__ double4 minmag(double4 x, double4 y);
  __AIR_TGT__ double4 modf(double4 x, global double4 *intval);
  __AIR_TGT__ double4 modf(double4 x, local double4 *intval);
  __AIR_TGT__ double4 modf(double4 x, private double4 *intval);
  __AIR_TGT__ double4 nan(ulong4 x);
  __AIR_ASM__ double4 nextafter(double4 x, double4 y) __asm("air.nextafter.v4f64");
  __AIR_ASM__ double4 pow(double4 x, double4 y) __asm("air." _AIR_PREFIX_double "pow.v4f64");
  __AIR_ASM__ double4 pown(double4 x, int4 y) __asm("air.pown.v4f64");
  __AIR_ASM__ double4 powr(double4 x, double4 y) __asm("air.powr.v4f64");
  __AIR_ASM__ double4 remainder(double4 x, double4 y) __asm("air.remainder.v4f64");
  __AIR_ASM__ double4 remquo(double4 x, double4 y, private int4 * quo) __asm("air.remquo.v4f64");
  __AIR_FUNC__ double4 remquo(double4 x, double4 y, global int4 * quo) {
    int4 pquo;
    double4 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_FUNC__ double4 remquo(double4 x, double4 y, local int4 * quo)  {
    int4 pquo;
    double4 res = remquo(x, y, &pquo);
    *quo = pquo;
    return res;
  }
  __AIR_ASM__ double4 rint(double4 x) __asm("air.rint.v4f64");
  __AIR_ASM__ double4 rootn(double4 x, int4 y) __asm("air.rootn.v4f64");
  // FIXME: scalar rootn
  __AIR_ASM__ double4 round(double4 x) __asm("air." _AIR_PREFIX_double "round.v4f64");
  __AIR_ASM__ double4 rsqrt(double4 x) __asm("air." _AIR_PREFIX_double "rsqrt.v4f64");
  __AIR_ASM__ double4 sin(double4 x) __asm("air." _AIR_PREFIX_double "sin.v4f64");
  __AIR_ASM__ double4 sincos(double4 x, private double4 *cosval) __asm("air." _AIR_PREFIX_double "sincos.v4f64");
  __AIR_FUNC__ double4 sincos(double4 x, global double4 *cosval) {
    double4 pcosval;
    double4 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_FUNC__ double4 sincos(double4 x, local double4 *cosval) {
    double4 pcosval;
    double4 res = sincos(x, &pcosval);
    *cosval = pcosval;
    return res;
  }
  __AIR_ASM__ double4 sinh(double4 x) __asm("air." _AIR_PREFIX_double "sinh.v4f64");
  __AIR_ASM__ double4 sinpi(double4 x) __asm("air.sinpi.v4f64");
  __AIR_ASM__ double4 sqrt(double4 x) __asm("air." _AIR_PREFIX_double "sqrt.v4f64");
  __AIR_ASM__ double4 tan(double4 x) __asm("air." _AIR_PREFIX_double "tan.v4f64");
  __AIR_ASM__ double4 tanh(double4 x) __asm("air." _AIR_PREFIX_double "tanh.v4f64");
  __AIR_ASM__ double4 tanpi(double4 x) __asm("air.tanpi.v4f64");
  __AIR_ASM__ double4 tgamma(double4 x) __asm("air.tgamma.v4f64");
  __AIR_ASM__ double4 trunc(double4 x) __asm("air.trunc.v4f64");


#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))


  __AIR_FUNC__ float8 acos(float8 x) { float8 r; r.hi = acos(x.hi); r.lo = acos(x.lo); return r; }
  __AIR_FUNC__ float8 acosh(float8 x) { float8 r; r.hi = acosh(x.hi); r.lo = acosh(x.lo); return r; }
  __AIR_FUNC__ float8 acospi(float8 x) { float8 r; r.hi = acospi(x.hi); r.lo = acospi(x.lo); return r; }
  __AIR_FUNC__ float8 asin(float8 x) { float8 r; r.hi = asin(x.hi); r.lo = asin(x.lo); return r; }
  __AIR_FUNC__ float8 asinh(float8 x) { float8 r; r.hi = asinh(x.hi); r.lo = asinh(x.lo); return r; }
  __AIR_FUNC__ float8 asinpi(float8 x) { float8 r; r.hi = asinpi(x.hi); r.lo = asinpi(x.lo); return r; }
  __AIR_FUNC__ float8 atan(float8 x) { float8 r; r.hi = atan(x.hi); r.lo = atan(x.lo); return r; }
  __AIR_FUNC__ float8 atanh(float8 x) { float8 r; r.hi = atanh(x.hi); r.lo = atanh(x.lo); return r; }
  __AIR_FUNC__ float8 atanpi(float8 x) { float8 r; r.hi = atanpi(x.hi); r.lo = atanpi(x.lo); return r; }
  __AIR_FUNC__ float8 cbrt(float8 x) { float8 r; r.hi = cbrt(x.hi); r.lo = cbrt(x.lo); return r; }
  __AIR_FUNC__ float8 ceil(float8 x) { float8 r; r.hi = ceil(x.hi); r.lo = ceil(x.lo); return r; }
  __AIR_FUNC__ float8 cos(float8 x) { float8 r; r.hi = cos(x.hi); r.lo = cos(x.lo); return r; }
  __AIR_FUNC__ float8 cosh(float8 x) { float8 r; r.hi = cosh(x.hi); r.lo = cosh(x.lo); return r; }
  __AIR_FUNC__ float8 cospi(float8 x) { float8 r; r.hi = cospi(x.hi); r.lo = cospi(x.lo); return r; }
  __AIR_FUNC__ float8 erf(float8 x) { float8 r; r.hi = erf(x.hi); r.lo = erf(x.lo); return r; }
  __AIR_FUNC__ float8 erfc(float8 x) { float8 r; r.hi = erfc(x.hi); r.lo = erfc(x.lo); return r; }
  __AIR_FUNC__ float8 exp(float8 x) { float8 r; r.hi = exp(x.hi); r.lo = exp(x.lo); return r; }
  __AIR_FUNC__ float8 exp2(float8 x) { float8 r; r.hi = exp2(x.hi); r.lo = exp2(x.lo); return r; }
  __AIR_FUNC__ float8 exp10(float8 x) { float8 r; r.hi = exp10(x.hi); r.lo = exp10(x.lo); return r; }
  __AIR_FUNC__ float8 expm1(float8 x) { float8 r; r.hi = expm1(x.hi); r.lo = expm1(x.lo); return r; }
  __AIR_FUNC__ float8 fabs(float8 x) { float8 r; r.hi = fabs(x.hi); r.lo = fabs(x.lo); return r; }
  __AIR_FUNC__ float8 floor(float8 x) { float8 r; r.hi = floor(x.hi); r.lo = floor(x.lo); return r; }
  __AIR_FUNC__ float8 lgamma(float8 x) { float8 r; r.hi = lgamma(x.hi); r.lo = lgamma(x.lo); return r; }
  __AIR_FUNC__ float8 log(float8 x) { float8 r; r.hi = log(x.hi); r.lo = log(x.lo); return r; }
  __AIR_FUNC__ float8 log2(float8 x) { float8 r; r.hi = log2(x.hi); r.lo = log2(x.lo); return r; }
  __AIR_FUNC__ float8 log10(float8 x) { float8 r; r.hi = log10(x.hi); r.lo = log10(x.lo); return r; }
  __AIR_FUNC__ float8 log1p(float8 x) { float8 r; r.hi = log1p(x.hi); r.lo = log1p(x.lo); return r; }
  __AIR_FUNC__ float8 native_cos(float8 x) { float8 r; r.hi = native_cos(x.hi); r.lo = native_cos(x.lo); return r; }
  __AIR_FUNC__ float8 native_exp(float8 x) { float8 r; r.hi = native_exp(x.hi); r.lo = native_exp(x.lo); return r; }
  __AIR_FUNC__ float8 native_exp2(float8 x) { float8 r; r.hi = native_exp2(x.hi); r.lo = native_exp2(x.lo); return r; }
  __AIR_FUNC__ float8 native_exp10(float8 x) { float8 r; r.hi = native_exp10(x.hi); r.lo = native_exp10(x.lo); return r; }
  __AIR_FUNC__ float8 native_log(float8 x) { float8 r; r.hi = native_log(x.hi); r.lo = native_log(x.lo); return r; }
  __AIR_FUNC__ float8 native_log2(float8 x) { float8 r; r.hi = native_log2(x.hi); r.lo = native_log2(x.lo); return r; }
  __AIR_FUNC__ float8 native_log10(float8 x) { float8 r; r.hi = native_log10(x.hi); r.lo = native_log10(x.lo); return r; }
  __AIR_FUNC__ float8 native_recip(float8 x) { float8 r; r.hi = native_recip(x.hi); r.lo = native_recip(x.lo); return r; }
  __AIR_FUNC__ float8 native_rsqrt(float8 x) { float8 r; r.hi = native_rsqrt(x.hi); r.lo = native_rsqrt(x.lo); return r; }
  __AIR_FUNC__ float8 native_sin(float8 x) { float8 r; r.hi = native_sin(x.hi); r.lo = native_sin(x.lo); return r; }
  __AIR_FUNC__ float8 native_sqrt(float8 x) { float8 r; r.hi = native_sqrt(x.hi); r.lo = native_sqrt(x.lo); return r; }
  __AIR_FUNC__ float8 native_tan(float8 x) { float8 r; r.hi = native_tan(x.hi); r.lo = native_tan(x.lo); return r; }
  __AIR_FUNC__ float8 rint(float8 x) { float8 r; r.hi = rint(x.hi); r.lo = rint(x.lo); return r; }
  __AIR_FUNC__ float8 round(float8 x) { float8 r; r.hi = round(x.hi); r.lo = round(x.lo); return r; }
  __AIR_FUNC__ float8 rsqrt(float8 x) { float8 r; r.hi = rsqrt(x.hi); r.lo = rsqrt(x.lo); return r; }
  __AIR_FUNC__ float8 sin(float8 x) { float8 r; r.hi = sin(x.hi); r.lo = sin(x.lo); return r; }
  __AIR_FUNC__ float8 sinh(float8 x) { float8 r; r.hi = sinh(x.hi); r.lo = sinh(x.lo); return r; }
  __AIR_FUNC__ float8 sinpi(float8 x) { float8 r; r.hi = sinpi(x.hi); r.lo = sinpi(x.lo); return r; }
  __AIR_FUNC__ float8 sqrt(float8 x) { float8 r; r.hi = sqrt(x.hi); r.lo = sqrt(x.lo); return r; }
  __AIR_FUNC__ float8 tan(float8 x) { float8 r; r.hi = tan(x.hi); r.lo = tan(x.lo); return r; }
  __AIR_FUNC__ float8 tanh(float8 x) { float8 r; r.hi = tanh(x.hi); r.lo = tanh(x.lo); return r; }
  __AIR_FUNC__ float8 tanpi(float8 x) { float8 r; r.hi = tanpi(x.hi); r.lo = tanpi(x.lo); return r; }
  __AIR_FUNC__ float8 tgamma(float8 x) { float8 r; r.hi = tgamma(x.hi); r.lo = tgamma(x.lo); return r; }
  __AIR_FUNC__ float8 trunc(float8 x) { float8 r; r.hi = trunc(x.hi); r.lo = trunc(x.lo); return r; }
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double8 acos(double8 x) { double8 r; r.hi = acos(x.hi); r.lo = acos(x.lo); return r; }
  __AIR_FUNC__ double8 acosh(double8 x) { double8 r; r.hi = acosh(x.hi); r.lo = acosh(x.lo); return r; }
  __AIR_FUNC__ double8 acospi(double8 x) { double8 r; r.hi = acospi(x.hi); r.lo = acospi(x.lo); return r; }
  __AIR_FUNC__ double8 asin(double8 x) { double8 r; r.hi = asin(x.hi); r.lo = asin(x.lo); return r; }
  __AIR_FUNC__ double8 asinh(double8 x) { double8 r; r.hi = asinh(x.hi); r.lo = asinh(x.lo); return r; }
  __AIR_FUNC__ double8 asinpi(double8 x) { double8 r; r.hi = asinpi(x.hi); r.lo = asinpi(x.lo); return r; }
  __AIR_FUNC__ double8 atan(double8 x) { double8 r; r.hi = atan(x.hi); r.lo = atan(x.lo); return r; }
  __AIR_FUNC__ double8 atanh(double8 x) { double8 r; r.hi = atanh(x.hi); r.lo = atanh(x.lo); return r; }
  __AIR_FUNC__ double8 atanpi(double8 x) { double8 r; r.hi = atanpi(x.hi); r.lo = atanpi(x.lo); return r; }
  __AIR_FUNC__ double8 cbrt(double8 x) { double8 r; r.hi = cbrt(x.hi); r.lo = cbrt(x.lo); return r; }
  __AIR_FUNC__ double8 ceil(double8 x) { double8 r; r.hi = ceil(x.hi); r.lo = ceil(x.lo); return r; }
  __AIR_FUNC__ double8 cos(double8 x) { double8 r; r.hi = cos(x.hi); r.lo = cos(x.lo); return r; }
  __AIR_FUNC__ double8 cosh(double8 x) { double8 r; r.hi = cosh(x.hi); r.lo = cosh(x.lo); return r; }
  __AIR_FUNC__ double8 cospi(double8 x) { double8 r; r.hi = cospi(x.hi); r.lo = cospi(x.lo); return r; }
  __AIR_FUNC__ double8 erf(double8 x) { double8 r; r.hi = erf(x.hi); r.lo = erf(x.lo); return r; }
  __AIR_FUNC__ double8 erfc(double8 x) { double8 r; r.hi = erfc(x.hi); r.lo = erfc(x.lo); return r; }
  __AIR_FUNC__ double8 exp(double8 x) { double8 r; r.hi = exp(x.hi); r.lo = exp(x.lo); return r; }
  __AIR_FUNC__ double8 exp2(double8 x) { double8 r; r.hi = exp2(x.hi); r.lo = exp2(x.lo); return r; }
  __AIR_FUNC__ double8 exp10(double8 x) { double8 r; r.hi = exp10(x.hi); r.lo = exp10(x.lo); return r; }
  __AIR_FUNC__ double8 expm1(double8 x) { double8 r; r.hi = expm1(x.hi); r.lo = expm1(x.lo); return r; }
  __AIR_FUNC__ double8 fabs(double8 x) { double8 r; r.hi = fabs(x.hi); r.lo = fabs(x.lo); return r; }
  __AIR_FUNC__ double8 floor(double8 x) { double8 r; r.hi = floor(x.hi); r.lo = floor(x.lo); return r; }
  __AIR_FUNC__ double8 lgamma(double8 x) { double8 r; r.hi = lgamma(x.hi); r.lo = lgamma(x.lo); return r; }
  __AIR_FUNC__ double8 log(double8 x) { double8 r; r.hi = log(x.hi); r.lo = log(x.lo); return r; }
  __AIR_FUNC__ double8 log2(double8 x) { double8 r; r.hi = log2(x.hi); r.lo = log2(x.lo); return r; }
  __AIR_FUNC__ double8 log10(double8 x) { double8 r; r.hi = log10(x.hi); r.lo = log10(x.lo); return r; }
  __AIR_FUNC__ double8 log1p(double8 x) { double8 r; r.hi = log1p(x.hi); r.lo = log1p(x.lo); return r; }
  __AIR_FUNC__ double8 rint(double8 x) { double8 r; r.hi = rint(x.hi); r.lo = rint(x.lo); return r; }
  __AIR_FUNC__ double8 round(double8 x) { double8 r; r.hi = round(x.hi); r.lo = round(x.lo); return r; }
  __AIR_FUNC__ double8 rsqrt(double8 x) { double8 r; r.hi = rsqrt(x.hi); r.lo = rsqrt(x.lo); return r; }
  __AIR_FUNC__ double8 sin(double8 x) { double8 r; r.hi = sin(x.hi); r.lo = sin(x.lo); return r; }
  __AIR_FUNC__ double8 sinh(double8 x) { double8 r; r.hi = sinh(x.hi); r.lo = sinh(x.lo); return r; }
  __AIR_FUNC__ double8 sinpi(double8 x) { double8 r; r.hi = sinpi(x.hi); r.lo = sinpi(x.lo); return r; }
  __AIR_FUNC__ double8 sqrt(double8 x) { double8 r; r.hi = sqrt(x.hi); r.lo = sqrt(x.lo); return r; }
  __AIR_FUNC__ double8 tan(double8 x) { double8 r; r.hi = tan(x.hi); r.lo = tan(x.lo); return r; }
  __AIR_FUNC__ double8 tanh(double8 x) { double8 r; r.hi = tanh(x.hi); r.lo = tanh(x.lo); return r; }
  __AIR_FUNC__ double8 tanpi(double8 x) { double8 r; r.hi = tanpi(x.hi); r.lo = tanpi(x.lo); return r; }
  __AIR_FUNC__ double8 tgamma(double8 x) { double8 r; r.hi = tgamma(x.hi); r.lo = tgamma(x.lo); return r; }
  __AIR_FUNC__ double8 trunc(double8 x) { double8 r; r.hi = trunc(x.hi); r.lo = trunc(x.lo); return r; }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
  __AIR_FUNC__ float16 acos(float16 x) { float16 r; r.hi = acos(x.hi); r.lo = acos(x.lo); return r; }
  __AIR_FUNC__ float16 acosh(float16 x) { float16 r; r.hi = acosh(x.hi); r.lo = acosh(x.lo); return r; }
  __AIR_FUNC__ float16 acospi(float16 x) { float16 r; r.hi = acospi(x.hi); r.lo = acospi(x.lo); return r; }
  __AIR_FUNC__ float16 asin(float16 x) { float16 r; r.hi = asin(x.hi); r.lo = asin(x.lo); return r; }
  __AIR_FUNC__ float16 asinh(float16 x) { float16 r; r.hi = asinh(x.hi); r.lo = asinh(x.lo); return r; }
  __AIR_FUNC__ float16 asinpi(float16 x) { float16 r; r.hi = asinpi(x.hi); r.lo = asinpi(x.lo); return r; }
  __AIR_FUNC__ float16 atan(float16 x) { float16 r; r.hi = atan(x.hi); r.lo = atan(x.lo); return r; }
  __AIR_FUNC__ float16 atanh(float16 x) { float16 r; r.hi = atanh(x.hi); r.lo = atanh(x.lo); return r; }
  __AIR_FUNC__ float16 atanpi(float16 x) { float16 r; r.hi = atanpi(x.hi); r.lo = atanpi(x.lo); return r; }
  __AIR_FUNC__ float16 cbrt(float16 x) { float16 r; r.hi = cbrt(x.hi); r.lo = cbrt(x.lo); return r; }
  __AIR_FUNC__ float16 ceil(float16 x) { float16 r; r.hi = ceil(x.hi); r.lo = ceil(x.lo); return r; }
  __AIR_FUNC__ float16 cos(float16 x) { float16 r; r.hi = cos(x.hi); r.lo = cos(x.lo); return r; }
  __AIR_FUNC__ float16 cosh(float16 x) { float16 r; r.hi = cosh(x.hi); r.lo = cosh(x.lo); return r; }
  __AIR_FUNC__ float16 cospi(float16 x) { float16 r; r.hi = cospi(x.hi); r.lo = cospi(x.lo); return r; }
  __AIR_FUNC__ float16 erf(float16 x) { float16 r; r.hi = erf(x.hi); r.lo = erf(x.lo); return r; }
  __AIR_FUNC__ float16 erfc(float16 x) { float16 r; r.hi = erfc(x.hi); r.lo = erfc(x.lo); return r; }
  __AIR_FUNC__ float16 exp(float16 x) { float16 r; r.hi = exp(x.hi); r.lo = exp(x.lo); return r; }
  __AIR_FUNC__ float16 exp2(float16 x) { float16 r; r.hi = exp2(x.hi); r.lo = exp2(x.lo); return r; }
  __AIR_FUNC__ float16 exp10(float16 x) { float16 r; r.hi = exp10(x.hi); r.lo = exp10(x.lo); return r; }
  __AIR_FUNC__ float16 expm1(float16 x) { float16 r; r.hi = expm1(x.hi); r.lo = expm1(x.lo); return r; }
  __AIR_FUNC__ float16 fabs(float16 x) { float16 r; r.hi = fabs(x.hi); r.lo = fabs(x.lo); return r; }
  __AIR_FUNC__ float16 floor(float16 x) { float16 r; r.hi = floor(x.hi); r.lo = floor(x.lo); return r; }
  __AIR_FUNC__ float16 lgamma(float16 x) { float16 r; r.hi = lgamma(x.hi); r.lo = lgamma(x.lo); return r; }
  __AIR_FUNC__ float16 log(float16 x) { float16 r; r.hi = log(x.hi); r.lo = log(x.lo); return r; }
  __AIR_FUNC__ float16 log2(float16 x) { float16 r; r.hi = log2(x.hi); r.lo = log2(x.lo); return r; }
  __AIR_FUNC__ float16 log10(float16 x) { float16 r; r.hi = log10(x.hi); r.lo = log10(x.lo); return r; }
  __AIR_FUNC__ float16 log1p(float16 x) { float16 r; r.hi = log1p(x.hi); r.lo = log1p(x.lo); return r; }
  __AIR_FUNC__ float16 native_cos(float16 x) { float16 r; r.hi = native_cos(x.hi); r.lo = native_cos(x.lo); return r; }
  __AIR_FUNC__ float16 native_exp(float16 x) { float16 r; r.hi = native_exp(x.hi); r.lo = native_exp(x.lo); return r; }
  __AIR_FUNC__ float16 native_exp2(float16 x) { float16 r; r.hi = native_exp2(x.hi); r.lo = native_exp2(x.lo); return r; }
  __AIR_FUNC__ float16 native_exp10(float16 x) { float16 r; r.hi = native_exp10(x.hi); r.lo = native_exp10(x.lo); return r; }
  __AIR_FUNC__ float16 native_log(float16 x) { float16 r; r.hi = native_log(x.hi); r.lo = native_log(x.lo); return r; }
  __AIR_FUNC__ float16 native_log2(float16 x) { float16 r; r.hi = native_log2(x.hi); r.lo = native_log2(x.lo); return r; }
  __AIR_FUNC__ float16 native_log10(float16 x) { float16 r; r.hi = native_log10(x.hi); r.lo = native_log10(x.lo); return r; }
  __AIR_FUNC__ float16 native_recip(float16 x) { float16 r; r.hi = native_recip(x.hi); r.lo = native_recip(x.lo); return r; }
  __AIR_FUNC__ float16 native_rsqrt(float16 x) { float16 r; r.hi = native_rsqrt(x.hi); r.lo = native_rsqrt(x.lo); return r; }
  __AIR_FUNC__ float16 native_sin(float16 x) { float16 r; r.hi = native_sin(x.hi); r.lo = native_sin(x.lo); return r; }
  __AIR_FUNC__ float16 native_sqrt(float16 x) { float16 r; r.hi = native_sqrt(x.hi); r.lo = native_sqrt(x.lo); return r; }
  __AIR_FUNC__ float16 native_tan(float16 x) { float16 r; r.hi = native_tan(x.hi); r.lo = native_tan(x.lo); return r; }
  __AIR_FUNC__ float16 rint(float16 x) { float16 r; r.hi = rint(x.hi); r.lo = rint(x.lo); return r; }
  __AIR_FUNC__ float16 round(float16 x) { float16 r; r.hi = round(x.hi); r.lo = round(x.lo); return r; }
  __AIR_FUNC__ float16 rsqrt(float16 x) { float16 r; r.hi = rsqrt(x.hi); r.lo = rsqrt(x.lo); return r; }
  __AIR_FUNC__ float16 sin(float16 x) { float16 r; r.hi = sin(x.hi); r.lo = sin(x.lo); return r; }
  __AIR_FUNC__ float16 sinh(float16 x) { float16 r; r.hi = sinh(x.hi); r.lo = sinh(x.lo); return r; }
  __AIR_FUNC__ float16 sinpi(float16 x) { float16 r; r.hi = sinpi(x.hi); r.lo = sinpi(x.lo); return r; }
  __AIR_FUNC__ float16 sqrt(float16 x) { float16 r; r.hi = sqrt(x.hi); r.lo = sqrt(x.lo); return r; }
  __AIR_FUNC__ float16 tan(float16 x) { float16 r; r.hi = tan(x.hi); r.lo = tan(x.lo); return r; }
  __AIR_FUNC__ float16 tanh(float16 x) { float16 r; r.hi = tanh(x.hi); r.lo = tanh(x.lo); return r; }
  __AIR_FUNC__ float16 tanpi(float16 x) { float16 r; r.hi = tanpi(x.hi); r.lo = tanpi(x.lo); return r; }
  __AIR_FUNC__ float16 tgamma(float16 x) { float16 r; r.hi = tgamma(x.hi); r.lo = tgamma(x.lo); return r; }
  __AIR_FUNC__ float16 trunc(float16 x) { float16 r; r.hi = trunc(x.hi); r.lo = trunc(x.lo); return r; }
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double16 acos(double16 x) { double16 r; r.hi = acos(x.hi); r.lo = acos(x.lo); return r; }
  __AIR_FUNC__ double16 acosh(double16 x) { double16 r; r.hi = acosh(x.hi); r.lo = acosh(x.lo); return r; }
  __AIR_FUNC__ double16 acospi(double16 x) { double16 r; r.hi = acospi(x.hi); r.lo = acospi(x.lo); return r; }
  __AIR_FUNC__ double16 asin(double16 x) { double16 r; r.hi = asin(x.hi); r.lo = asin(x.lo); return r; }
  __AIR_FUNC__ double16 asinh(double16 x) { double16 r; r.hi = asinh(x.hi); r.lo = asinh(x.lo); return r; }
  __AIR_FUNC__ double16 asinpi(double16 x) { double16 r; r.hi = asinpi(x.hi); r.lo = asinpi(x.lo); return r; }
  __AIR_FUNC__ double16 atan(double16 x) { double16 r; r.hi = atan(x.hi); r.lo = atan(x.lo); return r; }
  __AIR_FUNC__ double16 atanh(double16 x) { double16 r; r.hi = atanh(x.hi); r.lo = atanh(x.lo); return r; }
  __AIR_FUNC__ double16 atanpi(double16 x) { double16 r; r.hi = atanpi(x.hi); r.lo = atanpi(x.lo); return r; }
  __AIR_FUNC__ double16 cbrt(double16 x) { double16 r; r.hi = cbrt(x.hi); r.lo = cbrt(x.lo); return r; }
  __AIR_FUNC__ double16 ceil(double16 x) { double16 r; r.hi = ceil(x.hi); r.lo = ceil(x.lo); return r; }
  __AIR_FUNC__ double16 cos(double16 x) { double16 r; r.hi = cos(x.hi); r.lo = cos(x.lo); return r; }
  __AIR_FUNC__ double16 cosh(double16 x) { double16 r; r.hi = cosh(x.hi); r.lo = cosh(x.lo); return r; }
  __AIR_FUNC__ double16 cospi(double16 x) { double16 r; r.hi = cospi(x.hi); r.lo = cospi(x.lo); return r; }
  __AIR_FUNC__ double16 erf(double16 x) { double16 r; r.hi = erf(x.hi); r.lo = erf(x.lo); return r; }
  __AIR_FUNC__ double16 erfc(double16 x) { double16 r; r.hi = erfc(x.hi); r.lo = erfc(x.lo); return r; }
  __AIR_FUNC__ double16 exp(double16 x) { double16 r; r.hi = exp(x.hi); r.lo = exp(x.lo); return r; }
  __AIR_FUNC__ double16 exp2(double16 x) { double16 r; r.hi = exp2(x.hi); r.lo = exp2(x.lo); return r; }
  __AIR_FUNC__ double16 exp10(double16 x) { double16 r; r.hi = exp10(x.hi); r.lo = exp10(x.lo); return r; }
  __AIR_FUNC__ double16 expm1(double16 x) { double16 r; r.hi = expm1(x.hi); r.lo = expm1(x.lo); return r; }
  __AIR_FUNC__ double16 fabs(double16 x) { double16 r; r.hi = fabs(x.hi); r.lo = fabs(x.lo); return r; }
  __AIR_FUNC__ double16 floor(double16 x) { double16 r; r.hi = floor(x.hi); r.lo = floor(x.lo); return r; }
  __AIR_FUNC__ double16 lgamma(double16 x) { double16 r; r.hi = lgamma(x.hi); r.lo = lgamma(x.lo); return r; }
  __AIR_FUNC__ double16 log(double16 x) { double16 r; r.hi = log(x.hi); r.lo = log(x.lo); return r; }
  __AIR_FUNC__ double16 log2(double16 x) { double16 r; r.hi = log2(x.hi); r.lo = log2(x.lo); return r; }
  __AIR_FUNC__ double16 log10(double16 x) { double16 r; r.hi = log10(x.hi); r.lo = log10(x.lo); return r; }
  __AIR_FUNC__ double16 log1p(double16 x) { double16 r; r.hi = log1p(x.hi); r.lo = log1p(x.lo); return r; }
  __AIR_FUNC__ double16 rint(double16 x) { double16 r; r.hi = rint(x.hi); r.lo = rint(x.lo); return r; }
  __AIR_FUNC__ double16 round(double16 x) { double16 r; r.hi = round(x.hi); r.lo = round(x.lo); return r; }
  __AIR_FUNC__ double16 rsqrt(double16 x) { double16 r; r.hi = rsqrt(x.hi); r.lo = rsqrt(x.lo); return r; }
  __AIR_FUNC__ double16 sin(double16 x) { double16 r; r.hi = sin(x.hi); r.lo = sin(x.lo); return r; }
  __AIR_FUNC__ double16 sinh(double16 x) { double16 r; r.hi = sinh(x.hi); r.lo = sinh(x.lo); return r; }
  __AIR_FUNC__ double16 sinpi(double16 x) { double16 r; r.hi = sinpi(x.hi); r.lo = sinpi(x.lo); return r; }
  __AIR_FUNC__ double16 sqrt(double16 x) { double16 r; r.hi = sqrt(x.hi); r.lo = sqrt(x.lo); return r; }
  __AIR_FUNC__ double16 tan(double16 x) { double16 r; r.hi = tan(x.hi); r.lo = tan(x.lo); return r; }
  __AIR_FUNC__ double16 tanh(double16 x) { double16 r; r.hi = tanh(x.hi); r.lo = tanh(x.lo); return r; }
  __AIR_FUNC__ double16 tanpi(double16 x) { double16 r; r.hi = tanpi(x.hi); r.lo = tanpi(x.lo); return r; }
  __AIR_FUNC__ double16 tgamma(double16 x) { double16 r; r.hi = tgamma(x.hi); r.lo = tgamma(x.lo); return r; }
  __AIR_FUNC__ double16 trunc(double16 x) { double16 r; r.hi = trunc(x.hi); r.lo = trunc(x.lo); return r; }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_FUNC__ float8 copysign(float8 x, float8 y) {
     float8 r;
     r.hi = copysign(x.hi, y.hi);
     r.lo = copysign(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 fdim(float8 x, float8 y) {
     float8 r;
     r.hi = fdim(x.hi, y.hi);
     r.lo = fdim(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 fmax(float8 x, float8 y) {
     float8 r;
     r.hi = fmax(x.hi, y.hi);
     r.lo = fmax(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 fmin(float8 x, float8 y) {
     float8 r;
     r.hi = fmin(x.hi, y.hi);
     r.lo = fmin(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 fmod(float8 x, float8 y) {
     float8 r;
     r.hi = fmod(x.hi, y.hi);
     r.lo = fmod(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 maxmag(float8 x, float8 y) {
     float8 r;
     r.hi = maxmag(x.hi, y.hi);
     r.lo = maxmag(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 minmag(float8 x, float8 y) {
     float8 r;
     r.hi = minmag(x.hi, y.hi);
     r.lo = minmag(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 native_divide(float8 x, float8 y) {
     float8 r;
     r.hi = native_divide(x.hi, y.hi);
     r.lo = native_divide(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 native_powr(float8 x, float8 y) {
     float8 r;
     r.hi = native_powr(x.hi, y.hi);
     r.lo = native_powr(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 nextafter(float8 x, float8 y) {
     float8 r;
     r.hi = nextafter(x.hi, y.hi);
     r.lo = nextafter(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 pow(float8 x, float8 y) {
     float8 r;
     r.hi = pow(x.hi, y.hi);
     r.lo = pow(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float8 remainder(float8 x, float8 y) {
     float8 r;
     r.hi = remainder(x.hi, y.hi);
     r.lo = remainder(x.lo, y.lo);
     return r;
  }
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double8 copysign(double8 x, double8 y) {
     double8 r;
     r.hi = copysign(x.hi, y.hi);
     r.lo = copysign(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 fdim(double8 x, double8 y) {
     double8 r;
     r.hi = fdim(x.hi, y.hi);
     r.lo = fdim(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 fmax(double8 x, double8 y) {
     double8 r;
     r.hi = fmax(x.hi, y.hi);
     r.lo = fmax(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 fmin(double8 x, double8 y) {
     double8 r;
     r.hi = fmin(x.hi, y.hi);
     r.lo = fmin(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 fmod(double8 x, double8 y) {
     double8 r;
     r.hi = fmod(x.hi, y.hi);
     r.lo = fmod(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 maxmag(double8 x, double8 y) {
     double8 r;
     r.hi = maxmag(x.hi, y.hi);
     r.lo = maxmag(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 minmag(double8 x, double8 y) {
     double8 r;
     r.hi = minmag(x.hi, y.hi);
     r.lo = minmag(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 nextafter(double8 x, double8 y) {
     double8 r;
     r.hi = nextafter(x.hi, y.hi);
     r.lo = nextafter(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 pow(double8 x, double8 y) {
     double8 r;
     r.hi = pow(x.hi, y.hi);
     r.lo = pow(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double8 remainder(double8 x, double8 y) {
     double8 r;
     r.hi = remainder(x.hi, y.hi);
     r.lo = remainder(x.lo, y.lo);
     return r;
  }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
  __AIR_FUNC__ float16 copysign(float16 x, float16 y) {
     float16 r;
     r.hi = copysign(x.hi, y.hi);
     r.lo = copysign(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 fdim(float16 x, float16 y) {
     float16 r;
     r.hi = fdim(x.hi, y.hi);
     r.lo = fdim(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 fmax(float16 x, float16 y) {
     float16 r;
     r.hi = fmax(x.hi, y.hi);
     r.lo = fmax(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 fmin(float16 x, float16 y) {
     float16 r;
     r.hi = fmin(x.hi, y.hi);
     r.lo = fmin(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 fmod(float16 x, float16 y) {
     float16 r;
     r.hi = fmod(x.hi, y.hi);
     r.lo = fmod(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 maxmag(float16 x, float16 y) {
     float16 r;
     r.hi = maxmag(x.hi, y.hi);
     r.lo = maxmag(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 minmag(float16 x, float16 y) {
     float16 r;
     r.hi = minmag(x.hi, y.hi);
     r.lo = minmag(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 native_divide(float16 x, float16 y) {
     float16 r;
     r.hi = native_divide(x.hi, y.hi);
     r.lo = native_divide(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 native_powr(float16 x, float16 y) {
     float16 r;
     r.hi = native_powr(x.hi, y.hi);
     r.lo = native_powr(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 nextafter(float16 x, float16 y) {
     float16 r;
     r.hi = nextafter(x.hi, y.hi);
     r.lo = nextafter(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 pow(float16 x, float16 y) {
     float16 r;
     r.hi = pow(x.hi, y.hi);
     r.lo = pow(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ float16 remainder(float16 x, float16 y) {
     float16 r;
     r.hi = remainder(x.hi, y.hi);
     r.lo = remainder(x.lo, y.lo);
     return r;
  }
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double16 copysign(double16 x, double16 y) {
     double16 r;
     r.hi = copysign(x.hi, y.hi);
     r.lo = copysign(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 fdim(double16 x, double16 y) {
     double16 r;
     r.hi = fdim(x.hi, y.hi);
     r.lo = fdim(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 fmax(double16 x, double16 y) {
     double16 r;
     r.hi = fmax(x.hi, y.hi);
     r.lo = fmax(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 fmin(double16 x, double16 y) {
     double16 r;
     r.hi = fmin(x.hi, y.hi);
     r.lo = fmin(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 fmod(double16 x, double16 y) {
     double16 r;
     r.hi = fmod(x.hi, y.hi);
     r.lo = fmod(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 maxmag(double16 x, double16 y) {
     double16 r;
     r.hi = maxmag(x.hi, y.hi);
     r.lo = maxmag(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 minmag(double16 x, double16 y) {
     double16 r;
     r.hi = minmag(x.hi, y.hi);
     r.lo = minmag(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 nextafter(double16 x, double16 y) {
     double16 r;
     r.hi = nextafter(x.hi, y.hi);
     r.lo = nextafter(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 pow(double16 x, double16 y) {
     double16 r;
     r.hi = pow(x.hi, y.hi);
     r.lo = pow(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ double16 remainder(double16 x, double16 y) {
     double16 r;
     r.hi = remainder(x.hi, y.hi);
     r.lo = remainder(x.lo, y.lo);
     return r;
  }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_FUNC__ float8 fma(float8 x, float8 y, float8 z) {
     float8 r;
     r.hi = fma(x.hi, y.hi, z.hi);
     r.lo = fma(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ float8 mad(float8 x, float8 y, float8 z) {
     float8 r;
     r.hi = mad(x.hi, y.hi, z.hi);
     r.lo = mad(x.lo, y.lo, z.lo);
     return r;
  }
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double8 fma(double8 x, double8 y, double8 z) {
     double8 r;
     r.hi = fma(x.hi, y.hi, z.hi);
     r.lo = fma(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ double8 mad(double8 x, double8 y, double8 z) {
     double8 r;
     r.hi = mad(x.hi, y.hi, z.hi);
     r.lo = mad(x.lo, y.lo, z.lo);
     return r;
  }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
  __AIR_FUNC__ float16 fma(float16 x, float16 y, float16 z) {
     float16 r;
     r.hi = fma(x.hi, y.hi, z.hi);
     r.lo = fma(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ float16 mad(float16 x, float16 y, float16 z) {
     float16 r;
     r.hi = mad(x.hi, y.hi, z.hi);
     r.lo = mad(x.lo, y.lo, z.lo);
     return r;
  }
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double16 fma(double16 x, double16 y, double16 z) {
     double16 r;
     r.hi = fma(x.hi, y.hi, z.hi);
     r.lo = fma(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ double16 mad(double16 x, double16 y, double16 z) {
     double16 r;
     r.hi = mad(x.hi, y.hi, z.hi);
     r.lo = mad(x.lo, y.lo, z.lo);
     return r;
  }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_FUNC__ float8 fract(float8 x, private float8 *vptr) {
     float8 r, pval;
     float4 pval_hi, pval_lo;
     r.hi = fract(x.hi, &pval_hi);
     r.lo = fract(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ float8 fract(float8 x, global float8 *vptr) {
     float8 r, pval;
     r = fract(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float8 fract(float8 x, local float8 *vptr) {
     float8 r, pval;
     r = fract(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float8 modf(float8 x, private float8 *vptr) {
     float8 r, pval;
     float4 pval_hi, pval_lo;
     r.hi = modf(x.hi, &pval_hi);
     r.lo = modf(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ float8 modf(float8 x, global float8 *vptr) {
     float8 r, pval;
     r = modf(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float8 modf(float8 x, local float8 *vptr) {
     float8 r, pval;
     r = modf(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float8 sincos(float8 x, private float8 *vptr) {
     float8 r, pval;
     float4 pval_hi, pval_lo;
     r.hi = sincos(x.hi, &pval_hi);
     r.lo = sincos(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ float8 sincos(float8 x, global float8 *vptr) {
     float8 r, pval;
     r = sincos(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float8 sincos(float8 x, local float8 *vptr) {
     float8 r, pval;
     r = sincos(x, &pval);
     *vptr = pval; 
     return r;
  }
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double8 fract(double8 x, private double8 *vptr) {
     double8 r, pval;
     double4 pval_hi, pval_lo;
     r.hi = fract(x.hi, &pval_hi);
     r.lo = fract(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ double8 fract(double8 x, global double8 *vptr) {
     double8 r, pval;
     r = fract(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double8 fract(double8 x, local double8 *vptr) {
     double8 r, pval;
     r = fract(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double8 modf(double8 x, private double8 *vptr) {
     double8 r, pval;
     double4 pval_hi, pval_lo;
     r.hi = modf(x.hi, &pval_hi);
     r.lo = modf(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ double8 modf(double8 x, global double8 *vptr) {
     double8 r, pval;
     r = modf(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double8 modf(double8 x, local double8 *vptr) {
     double8 r, pval;
     r = modf(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double8 sincos(double8 x, private double8 *vptr) {
     double8 r, pval;
     double4 pval_hi, pval_lo;
     r.hi = sincos(x.hi, &pval_hi);
     r.lo = sincos(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ double8 sincos(double8 x, global double8 *vptr) {
     double8 r, pval;
     r = sincos(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double8 sincos(double8 x, local double8 *vptr) {
     double8 r, pval;
     r = sincos(x, &pval);
     *vptr = pval; 
     return r;
  }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
  __AIR_FUNC__ float16 fract(float16 x, private float16 *vptr) {
     float16 r, pval;
     float8 pval_hi, pval_lo;
     r.hi = fract(x.hi, &pval_hi);
     r.lo = fract(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ float16 fract(float16 x, global float16 *vptr) {
     float16 r, pval;
     r = fract(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float16 fract(float16 x, local float16 *vptr) {
     float16 r, pval;
     r = fract(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float16 modf(float16 x, private float16 *vptr) {
     float16 r, pval;
     float8 pval_hi, pval_lo;
     r.hi = modf(x.hi, &pval_hi);
     r.lo = modf(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ float16 modf(float16 x, global float16 *vptr) {
     float16 r, pval;
     r = modf(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float16 modf(float16 x, local float16 *vptr) {
     float16 r, pval;
     r = modf(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float16 sincos(float16 x, private float16 *vptr) {
     float16 r, pval;
     float8 pval_hi, pval_lo;
     r.hi = sincos(x.hi, &pval_hi);
     r.lo = sincos(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ float16 sincos(float16 x, global float16 *vptr) {
     float16 r, pval;
     r = sincos(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ float16 sincos(float16 x, local float16 *vptr) {
     float16 r, pval;
     r = sincos(x, &pval);
     *vptr = pval; 
     return r;
  }
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double16 fract(double16 x, private double16 *vptr) {
     double16 r, pval;
     double8 pval_hi, pval_lo;
     r.hi = fract(x.hi, &pval_hi);
     r.lo = fract(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ double16 fract(double16 x, global double16 *vptr) {
     double16 r, pval;
     r = fract(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double16 fract(double16 x, local double16 *vptr) {
     double16 r, pval;
     r = fract(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double16 modf(double16 x, private double16 *vptr) {
     double16 r, pval;
     double8 pval_hi, pval_lo;
     r.hi = modf(x.hi, &pval_hi);
     r.lo = modf(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ double16 modf(double16 x, global double16 *vptr) {
     double16 r, pval;
     r = modf(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double16 modf(double16 x, local double16 *vptr) {
     double16 r, pval;
     r = modf(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double16 sincos(double16 x, private double16 *vptr) {
     double16 r, pval;
     double8 pval_hi, pval_lo;
     r.hi = sincos(x.hi, &pval_hi);
     r.lo = sincos(x.lo, &pval_lo);
     pval.hi = pval_hi; pval.lo = pval_lo;
     *vptr = pval;
     return r;
  }
  __AIR_FUNC__ double16 sincos(double16 x, global double16 *vptr) {
     double16 r, pval;
     r = sincos(x, &pval);
     *vptr = pval; 
     return r;
  }
  __AIR_FUNC__ double16 sincos(double16 x, local double16 *vptr) {
     double16 r, pval;
     r = sincos(x, &pval);
     *vptr = pval; 
     return r;
  }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))



// OpenCL 1.2 6.12.3 Integer Functions generating Unified LLVM IR Sec 7 Integer Functions
  __AIR_ASM__ uchar abs(char x) __asm("air.abs.s.i8");
  __AIR_ASM__ uchar abs_diff(char x, char y) __asm("air.abs_diff.s.i8");
  __AIR_ASM__ char add_sat(char x, char y) __asm("air.add_sat.s.i8");
  __AIR_ASM__ char hadd(char x, char y) __asm("air.hadd.s.i8");
  __AIR_ASM__ char rhadd(char x, char y) __asm("air.rhadd.s.i8");
  __AIR_ASM__ char clamp(char x, char minval, char maxval) __asm("air.clamp.s.i8");
  __AIR_INTERNAL__ char _air_clz(char x, bool is_zero_undef) __asm("air.clz.i8");
  __AIR_FUNC__ char clz(char x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ char _air_ctz(char x, bool is_zero_undef) __asm("air.ctz.i8");
  __AIR_FUNC__ char ctz(char x) { return _air_ctz(x,false); }
  __AIR_ASM__ char mad_hi(char a, char b, char c) __asm("air.mad_hi.s.i8");
  __AIR_ASM__ char mad_sat(char a, char b, char c) __asm("air.mad_sat.s.i8");
  __AIR_ASM__ char max(char x, char y) __asm("air.max.s.i8");
  __AIR_ASM__ char min(char x, char y) __asm("air.min.s.i8");
  __AIR_ASM__ char mul_hi(char x, char y) __asm("air.mul_hi.s.i8");
  __AIR_ASM__ char rotate(char v, char i) __asm("air.rotate.i8");
  __AIR_ASM__ char sub_sat(char x, char y) __asm("air.sub_sat.s.i8");
  __AIR_ASM__ char popcount(char x) __asm("air.popcount.i8");
  __AIR_FUNC__ short upsample(char hi, uchar lo) { return (convert_short(hi) << 8) | (convert_short(lo)); }
  __AIR_ASM__ uchar abs(uchar x) __asm("air.abs.u.i8");
  __AIR_ASM__ uchar abs_diff(uchar x, uchar y) __asm("air.abs_diff.u.i8");
  __AIR_ASM__ uchar add_sat(uchar x, uchar y) __asm("air.add_sat.u.i8");
  __AIR_ASM__ uchar hadd(uchar x, uchar y) __asm("air.hadd.u.i8");
  __AIR_ASM__ uchar rhadd(uchar x, uchar y) __asm("air.rhadd.u.i8");
  __AIR_ASM__ uchar clamp(uchar x, uchar minval, uchar maxval) __asm("air.clamp.u.i8");
  __AIR_INTERNAL__ uchar _air_clz(uchar x, bool is_zero_undef) __asm("air.clz.i8");
  __AIR_FUNC__ uchar clz(uchar x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ uchar _air_ctz(uchar x, bool is_zero_undef) __asm("air.ctz.i8");
  __AIR_FUNC__ uchar ctz(uchar x) { return _air_ctz(x,false); }
  __AIR_ASM__ uchar mad_hi(uchar a, uchar b, uchar c) __asm("air.mad_hi.u.i8");
  __AIR_ASM__ uchar mad_sat(uchar a, uchar b, uchar c) __asm("air.mad_sat.u.i8");
  __AIR_ASM__ uchar max(uchar x, uchar y) __asm("air.max.u.i8");
  __AIR_ASM__ uchar min(uchar x, uchar y) __asm("air.min.u.i8");
  __AIR_ASM__ uchar mul_hi(uchar x, uchar y) __asm("air.mul_hi.u.i8");
  __AIR_ASM__ uchar rotate(uchar v, uchar i) __asm("air.rotate.i8");
  __AIR_ASM__ uchar sub_sat(uchar x, uchar y) __asm("air.sub_sat.u.i8");
  __AIR_ASM__ uchar popcount(uchar x) __asm("air.popcount.i8");
  __AIR_FUNC__ ushort upsample(uchar hi, uchar lo) { return (convert_ushort(hi) << 8) | (convert_ushort(lo)); }
  __AIR_ASM__ ushort abs(short x) __asm("air.abs.s.i16");
  __AIR_ASM__ ushort abs_diff(short x, short y) __asm("air.abs_diff.s.i16");
  __AIR_ASM__ short add_sat(short x, short y) __asm("air.add_sat.s.i16");
  __AIR_ASM__ short hadd(short x, short y) __asm("air.hadd.s.i16");
  __AIR_ASM__ short rhadd(short x, short y) __asm("air.rhadd.s.i16");
  __AIR_ASM__ short clamp(short x, short minval, short maxval) __asm("air.clamp.s.i16");
  __AIR_INTERNAL__ short _air_clz(short x, bool is_zero_undef) __asm("air.clz.i16");
  __AIR_FUNC__ short clz(short x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ short _air_ctz(short x, bool is_zero_undef) __asm("air.ctz.i16");
  __AIR_FUNC__ short ctz(short x) { return _air_ctz(x,false); }
  __AIR_ASM__ short mad_hi(short a, short b, short c) __asm("air.mad_hi.s.i16");
  __AIR_ASM__ short mad_sat(short a, short b, short c) __asm("air.mad_sat.s.i16");
  __AIR_ASM__ short max(short x, short y) __asm("air.max.s.i16");
  __AIR_ASM__ short min(short x, short y) __asm("air.min.s.i16");
  __AIR_ASM__ short mul_hi(short x, short y) __asm("air.mul_hi.s.i16");
  __AIR_ASM__ short rotate(short v, short i) __asm("air.rotate.i16");
  __AIR_ASM__ short sub_sat(short x, short y) __asm("air.sub_sat.s.i16");
  __AIR_ASM__ short popcount(short x) __asm("air.popcount.i16");
  __AIR_FUNC__ int upsample(short hi, ushort lo) { return (convert_int(hi) << 16) | (convert_int(lo)); }
  __AIR_ASM__ ushort abs(ushort x) __asm("air.abs.u.i16");
  __AIR_ASM__ ushort abs_diff(ushort x, ushort y) __asm("air.abs_diff.u.i16");
  __AIR_ASM__ ushort add_sat(ushort x, ushort y) __asm("air.add_sat.u.i16");
  __AIR_ASM__ ushort hadd(ushort x, ushort y) __asm("air.hadd.u.i16");
  __AIR_ASM__ ushort rhadd(ushort x, ushort y) __asm("air.rhadd.u.i16");
  __AIR_ASM__ ushort clamp(ushort x, ushort minval, ushort maxval) __asm("air.clamp.u.i16");
  __AIR_INTERNAL__ ushort _air_clz(ushort x, bool is_zero_undef) __asm("air.clz.i16");
  __AIR_FUNC__ ushort clz(ushort x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ ushort _air_ctz(ushort x, bool is_zero_undef) __asm("air.ctz.i16");
  __AIR_FUNC__ ushort ctz(ushort x) { return _air_ctz(x,false); }
  __AIR_ASM__ ushort mad_hi(ushort a, ushort b, ushort c) __asm("air.mad_hi.u.i16");
  __AIR_ASM__ ushort mad_sat(ushort a, ushort b, ushort c) __asm("air.mad_sat.u.i16");
  __AIR_ASM__ ushort max(ushort x, ushort y) __asm("air.max.u.i16");
  __AIR_ASM__ ushort min(ushort x, ushort y) __asm("air.min.u.i16");
  __AIR_ASM__ ushort mul_hi(ushort x, ushort y) __asm("air.mul_hi.u.i16");
  __AIR_ASM__ ushort rotate(ushort v, ushort i) __asm("air.rotate.i16");
  __AIR_ASM__ ushort sub_sat(ushort x, ushort y) __asm("air.sub_sat.u.i16");
  __AIR_ASM__ ushort popcount(ushort x) __asm("air.popcount.i16");
  __AIR_FUNC__ uint upsample(ushort hi, ushort lo) { return (convert_uint(hi) << 16) | (convert_uint(lo)); }
  __AIR_ASM__ uint abs(int x) __asm("air.abs.s.i32");
  __AIR_ASM__ uint abs_diff(int x, int y) __asm("air.abs_diff.s.i32");
  __AIR_ASM__ int add_sat(int x, int y) __asm("air.add_sat.s.i32");
  __AIR_ASM__ int hadd(int x, int y) __asm("air.hadd.s.i32");
  __AIR_ASM__ int rhadd(int x, int y) __asm("air.rhadd.s.i32");
  __AIR_ASM__ int clamp(int x, int minval, int maxval) __asm("air.clamp.s.i32");
  __AIR_INTERNAL__ int _air_clz(int x, bool is_zero_undef) __asm("air.clz.i32");
  __AIR_FUNC__ int clz(int x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ int _air_ctz(int x, bool is_zero_undef) __asm("air.ctz.i32");
  __AIR_FUNC__ int ctz(int x) { return _air_ctz(x,false); }
  __AIR_ASM__ int mad_hi(int a, int b, int c) __asm("air.mad_hi.s.i32");
  __AIR_ASM__ int mad_sat(int a, int b, int c) __asm("air.mad_sat.s.i32");
  __AIR_ASM__ int max(int x, int y) __asm("air.max.s.i32");
  __AIR_ASM__ int min(int x, int y) __asm("air.min.s.i32");
  __AIR_ASM__ int mul_hi(int x, int y) __asm("air.mul_hi.s.i32");
  __AIR_ASM__ int rotate(int v, int i) __asm("air.rotate.i32");
  __AIR_ASM__ int sub_sat(int x, int y) __asm("air.sub_sat.s.i32");
  __AIR_ASM__ int popcount(int x) __asm("air.popcount.i32");
  __AIR_FUNC__ long upsample(int hi, uint lo) { return (convert_long(hi) << 32) | (convert_long(lo)); }
  __AIR_ASM__ uint abs(uint x) __asm("air.abs.u.i32");
  __AIR_ASM__ uint abs_diff(uint x, uint y) __asm("air.abs_diff.u.i32");
  __AIR_ASM__ uint add_sat(uint x, uint y) __asm("air.add_sat.u.i32");
  __AIR_ASM__ uint hadd(uint x, uint y) __asm("air.hadd.u.i32");
  __AIR_ASM__ uint rhadd(uint x, uint y) __asm("air.rhadd.u.i32");
  __AIR_ASM__ uint clamp(uint x, uint minval, uint maxval) __asm("air.clamp.u.i32");
  __AIR_INTERNAL__ uint _air_clz(uint x, bool is_zero_undef) __asm("air.clz.i32");
  __AIR_FUNC__ uint clz(uint x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ uint _air_ctz(uint x, bool is_zero_undef) __asm("air.ctz.i32");
  __AIR_FUNC__ uint ctz(uint x) { return _air_ctz(x,false); }
  __AIR_ASM__ uint mad_hi(uint a, uint b, uint c) __asm("air.mad_hi.u.i32");
  __AIR_ASM__ uint mad_sat(uint a, uint b, uint c) __asm("air.mad_sat.u.i32");
  __AIR_ASM__ uint max(uint x, uint y) __asm("air.max.u.i32");
  __AIR_ASM__ uint min(uint x, uint y) __asm("air.min.u.i32");
  __AIR_ASM__ uint mul_hi(uint x, uint y) __asm("air.mul_hi.u.i32");
  __AIR_ASM__ uint rotate(uint v, uint i) __asm("air.rotate.i32");
  __AIR_ASM__ uint sub_sat(uint x, uint y) __asm("air.sub_sat.u.i32");
  __AIR_ASM__ uint popcount(uint x) __asm("air.popcount.i32");
  __AIR_FUNC__ ulong upsample(uint hi, uint lo) { return (convert_ulong(hi) << 32) | (convert_ulong(lo)); }
  __AIR_ASM__ ulong abs(long x) __asm("air.abs.s.i64");
  __AIR_ASM__ ulong abs_diff(long x, long y) __asm("air.abs_diff.s.i64");
  __AIR_ASM__ long add_sat(long x, long y) __asm("air.add_sat.s.i64");
  __AIR_ASM__ long hadd(long x, long y) __asm("air.hadd.s.i64");
  __AIR_ASM__ long rhadd(long x, long y) __asm("air.rhadd.s.i64");
  __AIR_ASM__ long clamp(long x, long minval, long maxval) __asm("air.clamp.s.i64");
  __AIR_INTERNAL__ long _air_clz(long x, bool is_zero_undef) __asm("air.clz.i64");
  __AIR_FUNC__ long clz(long x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ long _air_ctz(long x, bool is_zero_undef) __asm("air.ctz.i64");
  __AIR_FUNC__ long ctz(long x) { return _air_ctz(x,false); }
  __AIR_ASM__ long mad_hi(long a, long b, long c) __asm("air.mad_hi.s.i64");
  __AIR_ASM__ long mad_sat(long a, long b, long c) __asm("air.mad_sat.s.i64");
  __AIR_ASM__ long max(long x, long y) __asm("air.max.s.i64");
  __AIR_ASM__ long min(long x, long y) __asm("air.min.s.i64");
  __AIR_ASM__ long mul_hi(long x, long y) __asm("air.mul_hi.s.i64");
  __AIR_ASM__ long rotate(long v, long i) __asm("air.rotate.i64");
  __AIR_ASM__ long sub_sat(long x, long y) __asm("air.sub_sat.s.i64");
  __AIR_ASM__ long popcount(long x) __asm("air.popcount.i64");
  __AIR_ASM__ ulong abs(ulong x) __asm("air.abs.u.i64");
  __AIR_ASM__ ulong abs_diff(ulong x, ulong y) __asm("air.abs_diff.u.i64");
  __AIR_ASM__ ulong add_sat(ulong x, ulong y) __asm("air.add_sat.u.i64");
  __AIR_ASM__ ulong hadd(ulong x, ulong y) __asm("air.hadd.u.i64");
  __AIR_ASM__ ulong rhadd(ulong x, ulong y) __asm("air.rhadd.u.i64");
  __AIR_ASM__ ulong clamp(ulong x, ulong minval, ulong maxval) __asm("air.clamp.u.i64");
  __AIR_INTERNAL__ ulong _air_clz(ulong x, bool is_zero_undef) __asm("air.clz.i64");
  __AIR_FUNC__ ulong clz(ulong x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ ulong _air_ctz(ulong x, bool is_zero_undef) __asm("air.ctz.i64");
  __AIR_FUNC__ ulong ctz(ulong x) { return _air_ctz(x,false); }
  __AIR_ASM__ ulong mad_hi(ulong a, ulong b, ulong c) __asm("air.mad_hi.u.i64");
  __AIR_ASM__ ulong mad_sat(ulong a, ulong b, ulong c) __asm("air.mad_sat.u.i64");
  __AIR_ASM__ ulong max(ulong x, ulong y) __asm("air.max.u.i64");
  __AIR_ASM__ ulong min(ulong x, ulong y) __asm("air.min.u.i64");
  __AIR_ASM__ ulong mul_hi(ulong x, ulong y) __asm("air.mul_hi.u.i64");
  __AIR_ASM__ ulong rotate(ulong v, ulong i) __asm("air.rotate.i64");
  __AIR_ASM__ ulong sub_sat(ulong x, ulong y) __asm("air.sub_sat.u.i64");
  __AIR_ASM__ ulong popcount(ulong x) __asm("air.popcount.i64");
  __AIR_ASM__ uchar2 abs(char2 x) __asm("air.abs.s.v2i8");
  __AIR_ASM__ uchar2 abs_diff(char2 x, char2 y) __asm("air.abs_diff.s.v2i8");
  __AIR_ASM__ char2 add_sat(char2 x, char2 y) __asm("air.add_sat.s.v2i8");
  __AIR_ASM__ char2 hadd(char2 x, char2 y) __asm("air.hadd.s.v2i8");
  __AIR_ASM__ char2 rhadd(char2 x, char2 y) __asm("air.rhadd.s.v2i8");
  __AIR_ASM__ char2 clamp(char2 x, char2 minval, char2 maxval) __asm("air.clamp.s.v2i8");
  __AIR_FUNC__ char2 clamp(char2 x, char minval, char maxval) { return clamp(x,(char2)(minval),(char2)(maxval)); }
  __AIR_INTERNAL__ char2 _air_clz(char2 x, bool is_zero_undef) __asm("air.clz.v2i8");
  __AIR_FUNC__ char2 clz(char2 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ char2 _air_ctz(char2 x, bool is_zero_undef) __asm("air.ctz.v2i8");
  __AIR_FUNC__ char2 ctz(char2 x) { return _air_ctz(x,false); }
  __AIR_ASM__ char2 mad_hi(char2 a, char2 b, char2 c) __asm("air.mad_hi.s.v2i8");
  __AIR_ASM__ char2 mad_sat(char2 a, char2 b, char2 c) __asm("air.mad_sat.s.v2i8");
  __AIR_ASM__ char2 max(char2 x, char2 y) __asm("air.max.s.v2i8");
  __AIR_FUNC__ char2 max(char2 x, char y) { return max(x,(char2)(y)); }
  __AIR_ASM__ char2 min(char2 x, char2 y) __asm("air.min.s.v2i8");
  __AIR_FUNC__ char2 min(char2 x, char y) { return max(x,(char2)(y)); }
  __AIR_ASM__ char2 mul_hi(char2 x, char2 y) __asm("air.mul_hi.s.v2i8");
  __AIR_ASM__ char2 rotate(char2 v, char2 i) __asm("air.rotate.v2i8");
  __AIR_ASM__ char2 sub_sat(char2 x, char2 y) __asm("air.sub_sat.s.v2i8");
  __AIR_ASM__ char2 popcount(char2 x) __asm("air.popcount.v2i8");
  __AIR_FUNC__ short2 upsample(char2 hi, uchar2 lo) { return (convert_short2(hi) << 8) | (convert_short2(lo)); }
  __AIR_ASM__ uchar2 abs(uchar2 x) __asm("air.abs.u.v2i8");
  __AIR_ASM__ uchar2 abs_diff(uchar2 x, uchar2 y) __asm("air.abs_diff.u.v2i8");
  __AIR_ASM__ uchar2 add_sat(uchar2 x, uchar2 y) __asm("air.add_sat.u.v2i8");
  __AIR_ASM__ uchar2 hadd(uchar2 x, uchar2 y) __asm("air.hadd.u.v2i8");
  __AIR_ASM__ uchar2 rhadd(uchar2 x, uchar2 y) __asm("air.rhadd.u.v2i8");
  __AIR_ASM__ uchar2 clamp(uchar2 x, uchar2 minval, uchar2 maxval) __asm("air.clamp.u.v2i8");
  __AIR_FUNC__ uchar2 clamp(uchar2 x, uchar minval, uchar maxval) { return clamp(x,(uchar2)(minval),(uchar2)(maxval)); }
  __AIR_INTERNAL__ uchar2 _air_clz(uchar2 x, bool is_zero_undef) __asm("air.clz.v2i8");
  __AIR_FUNC__ uchar2 clz(uchar2 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ uchar2 _air_ctz(uchar2 x, bool is_zero_undef) __asm("air.ctz.v2i8");
  __AIR_FUNC__ uchar2 ctz(uchar2 x) { return _air_ctz(x,false); }
  __AIR_ASM__ uchar2 mad_hi(uchar2 a, uchar2 b, uchar2 c) __asm("air.mad_hi.u.v2i8");
  __AIR_ASM__ uchar2 mad_sat(uchar2 a, uchar2 b, uchar2 c) __asm("air.mad_sat.u.v2i8");
  __AIR_ASM__ uchar2 max(uchar2 x, uchar2 y) __asm("air.max.u.v2i8");
  __AIR_FUNC__ uchar2 max(uchar2 x, uchar y) { return max(x,(uchar2)(y)); }
  __AIR_ASM__ uchar2 min(uchar2 x, uchar2 y) __asm("air.min.u.v2i8");
  __AIR_FUNC__ uchar2 min(uchar2 x, uchar y) { return max(x,(uchar2)(y)); }
  __AIR_ASM__ uchar2 mul_hi(uchar2 x, uchar2 y) __asm("air.mul_hi.u.v2i8");
  __AIR_ASM__ uchar2 rotate(uchar2 v, uchar2 i) __asm("air.rotate.v2i8");
  __AIR_ASM__ uchar2 sub_sat(uchar2 x, uchar2 y) __asm("air.sub_sat.u.v2i8");
  __AIR_ASM__ uchar2 popcount(uchar2 x) __asm("air.popcount.v2i8");
  __AIR_FUNC__ ushort2 upsample(uchar2 hi, uchar2 lo) { return (convert_ushort2(hi) << 8) | (convert_ushort2(lo)); }
  __AIR_ASM__ ushort2 abs(short2 x) __asm("air.abs.s.v2i16");
  __AIR_ASM__ ushort2 abs_diff(short2 x, short2 y) __asm("air.abs_diff.s.v2i16");
  __AIR_ASM__ short2 add_sat(short2 x, short2 y) __asm("air.add_sat.s.v2i16");
  __AIR_ASM__ short2 hadd(short2 x, short2 y) __asm("air.hadd.s.v2i16");
  __AIR_ASM__ short2 rhadd(short2 x, short2 y) __asm("air.rhadd.s.v2i16");
  __AIR_ASM__ short2 clamp(short2 x, short2 minval, short2 maxval) __asm("air.clamp.s.v2i16");
  __AIR_FUNC__ short2 clamp(short2 x, short minval, short maxval) { return clamp(x,(short2)(minval),(short2)(maxval)); }
  __AIR_INTERNAL__ short2 _air_clz(short2 x, bool is_zero_undef) __asm("air.clz.v2i16");
  __AIR_FUNC__ short2 clz(short2 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ short2 _air_ctz(short2 x, bool is_zero_undef) __asm("air.ctz.v2i16");
  __AIR_FUNC__ short2 ctz(short2 x) { return _air_ctz(x,false); }
  __AIR_ASM__ short2 mad_hi(short2 a, short2 b, short2 c) __asm("air.mad_hi.s.v2i16");
  __AIR_ASM__ short2 mad_sat(short2 a, short2 b, short2 c) __asm("air.mad_sat.s.v2i16");
  __AIR_ASM__ short2 max(short2 x, short2 y) __asm("air.max.s.v2i16");
  __AIR_FUNC__ short2 max(short2 x, short y) { return max(x,(short2)(y)); }
  __AIR_ASM__ short2 min(short2 x, short2 y) __asm("air.min.s.v2i16");
  __AIR_FUNC__ short2 min(short2 x, short y) { return max(x,(short2)(y)); }
  __AIR_ASM__ short2 mul_hi(short2 x, short2 y) __asm("air.mul_hi.s.v2i16");
  __AIR_ASM__ short2 rotate(short2 v, short2 i) __asm("air.rotate.v2i16");
  __AIR_ASM__ short2 sub_sat(short2 x, short2 y) __asm("air.sub_sat.s.v2i16");
  __AIR_ASM__ short2 popcount(short2 x) __asm("air.popcount.v2i16");
  __AIR_FUNC__ int2 upsample(short2 hi, ushort2 lo) { return (convert_int2(hi) << 16) | (convert_int2(lo)); }
  __AIR_ASM__ ushort2 abs(ushort2 x) __asm("air.abs.u.v2i16");
  __AIR_ASM__ ushort2 abs_diff(ushort2 x, ushort2 y) __asm("air.abs_diff.u.v2i16");
  __AIR_ASM__ ushort2 add_sat(ushort2 x, ushort2 y) __asm("air.add_sat.u.v2i16");
  __AIR_ASM__ ushort2 hadd(ushort2 x, ushort2 y) __asm("air.hadd.u.v2i16");
  __AIR_ASM__ ushort2 rhadd(ushort2 x, ushort2 y) __asm("air.rhadd.u.v2i16");
  __AIR_ASM__ ushort2 clamp(ushort2 x, ushort2 minval, ushort2 maxval) __asm("air.clamp.u.v2i16");
  __AIR_FUNC__ ushort2 clamp(ushort2 x, ushort minval, ushort maxval) { return clamp(x,(ushort2)(minval),(ushort2)(maxval)); }
  __AIR_INTERNAL__ ushort2 _air_clz(ushort2 x, bool is_zero_undef) __asm("air.clz.v2i16");
  __AIR_FUNC__ ushort2 clz(ushort2 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ ushort2 _air_ctz(ushort2 x, bool is_zero_undef) __asm("air.ctz.v2i16");
  __AIR_FUNC__ ushort2 ctz(ushort2 x) { return _air_ctz(x,false); }
  __AIR_ASM__ ushort2 mad_hi(ushort2 a, ushort2 b, ushort2 c) __asm("air.mad_hi.u.v2i16");
  __AIR_ASM__ ushort2 mad_sat(ushort2 a, ushort2 b, ushort2 c) __asm("air.mad_sat.u.v2i16");
  __AIR_ASM__ ushort2 max(ushort2 x, ushort2 y) __asm("air.max.u.v2i16");
  __AIR_FUNC__ ushort2 max(ushort2 x, ushort y) { return max(x,(ushort2)(y)); }
  __AIR_ASM__ ushort2 min(ushort2 x, ushort2 y) __asm("air.min.u.v2i16");
  __AIR_FUNC__ ushort2 min(ushort2 x, ushort y) { return max(x,(ushort2)(y)); }
  __AIR_ASM__ ushort2 mul_hi(ushort2 x, ushort2 y) __asm("air.mul_hi.u.v2i16");
  __AIR_ASM__ ushort2 rotate(ushort2 v, ushort2 i) __asm("air.rotate.v2i16");
  __AIR_ASM__ ushort2 sub_sat(ushort2 x, ushort2 y) __asm("air.sub_sat.u.v2i16");
  __AIR_ASM__ ushort2 popcount(ushort2 x) __asm("air.popcount.v2i16");
  __AIR_FUNC__ uint2 upsample(ushort2 hi, ushort2 lo) { return (convert_uint2(hi) << 16) | (convert_uint2(lo)); }
  __AIR_ASM__ uint2 abs(int2 x) __asm("air.abs.s.v2i32");
  __AIR_ASM__ uint2 abs_diff(int2 x, int2 y) __asm("air.abs_diff.s.v2i32");
  __AIR_ASM__ int2 add_sat(int2 x, int2 y) __asm("air.add_sat.s.v2i32");
  __AIR_ASM__ int2 hadd(int2 x, int2 y) __asm("air.hadd.s.v2i32");
  __AIR_ASM__ int2 rhadd(int2 x, int2 y) __asm("air.rhadd.s.v2i32");
  __AIR_ASM__ int2 clamp(int2 x, int2 minval, int2 maxval) __asm("air.clamp.s.v2i32");
  __AIR_FUNC__ int2 clamp(int2 x, int minval, int maxval) { return clamp(x,(int2)(minval),(int2)(maxval)); }
  __AIR_INTERNAL__ int2 _air_clz(int2 x, bool is_zero_undef) __asm("air.clz.v2i32");
  __AIR_FUNC__ int2 clz(int2 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ int2 _air_ctz(int2 x, bool is_zero_undef) __asm("air.ctz.v2i32");
  __AIR_FUNC__ int2 ctz(int2 x) { return _air_ctz(x,false); }
  __AIR_ASM__ int2 mad_hi(int2 a, int2 b, int2 c) __asm("air.mad_hi.s.v2i32");
  __AIR_ASM__ int2 mad_sat(int2 a, int2 b, int2 c) __asm("air.mad_sat.s.v2i32");
  __AIR_ASM__ int2 max(int2 x, int2 y) __asm("air.max.s.v2i32");
  __AIR_FUNC__ int2 max(int2 x, int y) { return max(x,(int2)(y)); }
  __AIR_ASM__ int2 min(int2 x, int2 y) __asm("air.min.s.v2i32");
  __AIR_FUNC__ int2 min(int2 x, int y) { return max(x,(int2)(y)); }
  __AIR_ASM__ int2 mul_hi(int2 x, int2 y) __asm("air.mul_hi.s.v2i32");
  __AIR_ASM__ int2 rotate(int2 v, int2 i) __asm("air.rotate.v2i32");
  __AIR_ASM__ int2 sub_sat(int2 x, int2 y) __asm("air.sub_sat.s.v2i32");
  __AIR_ASM__ int2 popcount(int2 x) __asm("air.popcount.v2i32");
  __AIR_FUNC__ long2 upsample(int2 hi, uint2 lo) { return (convert_long2(hi) << 32) | (convert_long2(lo)); }
  __AIR_ASM__ uint2 abs(uint2 x) __asm("air.abs.u.v2i32");
  __AIR_ASM__ uint2 abs_diff(uint2 x, uint2 y) __asm("air.abs_diff.u.v2i32");
  __AIR_ASM__ uint2 add_sat(uint2 x, uint2 y) __asm("air.add_sat.u.v2i32");
  __AIR_ASM__ uint2 hadd(uint2 x, uint2 y) __asm("air.hadd.u.v2i32");
  __AIR_ASM__ uint2 rhadd(uint2 x, uint2 y) __asm("air.rhadd.u.v2i32");
  __AIR_ASM__ uint2 clamp(uint2 x, uint2 minval, uint2 maxval) __asm("air.clamp.u.v2i32");
  __AIR_FUNC__ uint2 clamp(uint2 x, uint minval, uint maxval) { return clamp(x,(uint2)(minval),(uint2)(maxval)); }
  __AIR_INTERNAL__ uint2 _air_clz(uint2 x, bool is_zero_undef) __asm("air.clz.v2i32");
  __AIR_FUNC__ uint2 clz(uint2 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ uint2 _air_ctz(uint2 x, bool is_zero_undef) __asm("air.ctz.v2i32");
  __AIR_FUNC__ uint2 ctz(uint2 x) { return _air_ctz(x,false); }
  __AIR_ASM__ uint2 mad_hi(uint2 a, uint2 b, uint2 c) __asm("air.mad_hi.u.v2i32");
  __AIR_ASM__ uint2 mad_sat(uint2 a, uint2 b, uint2 c) __asm("air.mad_sat.u.v2i32");
  __AIR_ASM__ uint2 max(uint2 x, uint2 y) __asm("air.max.u.v2i32");
  __AIR_FUNC__ uint2 max(uint2 x, uint y) { return max(x,(uint2)(y)); }
  __AIR_ASM__ uint2 min(uint2 x, uint2 y) __asm("air.min.u.v2i32");
  __AIR_FUNC__ uint2 min(uint2 x, uint y) { return max(x,(uint2)(y)); }
  __AIR_ASM__ uint2 mul_hi(uint2 x, uint2 y) __asm("air.mul_hi.u.v2i32");
  __AIR_ASM__ uint2 rotate(uint2 v, uint2 i) __asm("air.rotate.v2i32");
  __AIR_ASM__ uint2 sub_sat(uint2 x, uint2 y) __asm("air.sub_sat.u.v2i32");
  __AIR_ASM__ uint2 popcount(uint2 x) __asm("air.popcount.v2i32");
  __AIR_FUNC__ ulong2 upsample(uint2 hi, uint2 lo) { return (convert_ulong2(hi) << 32) | (convert_ulong2(lo)); }
  __AIR_ASM__ ulong2 abs(long2 x) __asm("air.abs.s.v2i64");
  __AIR_ASM__ ulong2 abs_diff(long2 x, long2 y) __asm("air.abs_diff.s.v2i64");
  __AIR_ASM__ long2 add_sat(long2 x, long2 y) __asm("air.add_sat.s.v2i64");
  __AIR_ASM__ long2 hadd(long2 x, long2 y) __asm("air.hadd.s.v2i64");
  __AIR_ASM__ long2 rhadd(long2 x, long2 y) __asm("air.rhadd.s.v2i64");
  __AIR_ASM__ long2 clamp(long2 x, long2 minval, long2 maxval) __asm("air.clamp.s.v2i64");
  __AIR_FUNC__ long2 clamp(long2 x, long minval, long maxval) { return clamp(x,(long2)(minval),(long2)(maxval)); }
  __AIR_INTERNAL__ long2 _air_clz(long2 x, bool is_zero_undef) __asm("air.clz.v2i64");
  __AIR_FUNC__ long2 clz(long2 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ long2 _air_ctz(long2 x, bool is_zero_undef) __asm("air.ctz.v2i64");
  __AIR_FUNC__ long2 ctz(long2 x) { return _air_ctz(x,false); }
  __AIR_ASM__ long2 mad_hi(long2 a, long2 b, long2 c) __asm("air.mad_hi.s.v2i64");
  __AIR_ASM__ long2 mad_sat(long2 a, long2 b, long2 c) __asm("air.mad_sat.s.v2i64");
  __AIR_ASM__ long2 max(long2 x, long2 y) __asm("air.max.s.v2i64");
  __AIR_FUNC__ long2 max(long2 x, long y) { return max(x,(long2)(y)); }
  __AIR_ASM__ long2 min(long2 x, long2 y) __asm("air.min.s.v2i64");
  __AIR_FUNC__ long2 min(long2 x, long y) { return max(x,(long2)(y)); }
  __AIR_ASM__ long2 mul_hi(long2 x, long2 y) __asm("air.mul_hi.s.v2i64");
  __AIR_ASM__ long2 rotate(long2 v, long2 i) __asm("air.rotate.v2i64");
  __AIR_ASM__ long2 sub_sat(long2 x, long2 y) __asm("air.sub_sat.s.v2i64");
  __AIR_ASM__ long2 popcount(long2 x) __asm("air.popcount.v2i64");
  __AIR_ASM__ ulong2 abs(ulong2 x) __asm("air.abs.u.v2i64");
  __AIR_ASM__ ulong2 abs_diff(ulong2 x, ulong2 y) __asm("air.abs_diff.u.v2i64");
  __AIR_ASM__ ulong2 add_sat(ulong2 x, ulong2 y) __asm("air.add_sat.u.v2i64");
  __AIR_ASM__ ulong2 hadd(ulong2 x, ulong2 y) __asm("air.hadd.u.v2i64");
  __AIR_ASM__ ulong2 rhadd(ulong2 x, ulong2 y) __asm("air.rhadd.u.v2i64");
  __AIR_ASM__ ulong2 clamp(ulong2 x, ulong2 minval, ulong2 maxval) __asm("air.clamp.u.v2i64");
  __AIR_FUNC__ ulong2 clamp(ulong2 x, ulong minval, ulong maxval) { return clamp(x,(ulong2)(minval),(ulong2)(maxval)); }
  __AIR_INTERNAL__ ulong2 _air_clz(ulong2 x, bool is_zero_undef) __asm("air.clz.v2i64");
  __AIR_FUNC__ ulong2 clz(ulong2 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ ulong2 _air_ctz(ulong2 x, bool is_zero_undef) __asm("air.ctz.v2i64");
  __AIR_FUNC__ ulong2 ctz(ulong2 x) { return _air_ctz(x,false); }
  __AIR_ASM__ ulong2 mad_hi(ulong2 a, ulong2 b, ulong2 c) __asm("air.mad_hi.u.v2i64");
  __AIR_ASM__ ulong2 mad_sat(ulong2 a, ulong2 b, ulong2 c) __asm("air.mad_sat.u.v2i64");
  __AIR_ASM__ ulong2 max(ulong2 x, ulong2 y) __asm("air.max.u.v2i64");
  __AIR_FUNC__ ulong2 max(ulong2 x, ulong y) { return max(x,(ulong2)(y)); }
  __AIR_ASM__ ulong2 min(ulong2 x, ulong2 y) __asm("air.min.u.v2i64");
  __AIR_FUNC__ ulong2 min(ulong2 x, ulong y) { return max(x,(ulong2)(y)); }
  __AIR_ASM__ ulong2 mul_hi(ulong2 x, ulong2 y) __asm("air.mul_hi.u.v2i64");
  __AIR_ASM__ ulong2 rotate(ulong2 v, ulong2 i) __asm("air.rotate.v2i64");
  __AIR_ASM__ ulong2 sub_sat(ulong2 x, ulong2 y) __asm("air.sub_sat.u.v2i64");
  __AIR_ASM__ ulong2 popcount(ulong2 x) __asm("air.popcount.v2i64");
  __AIR_ASM__ uchar3 abs(char3 x) __asm("air.abs.s.v3i8");
  __AIR_ASM__ uchar3 abs_diff(char3 x, char3 y) __asm("air.abs_diff.s.v3i8");
  __AIR_ASM__ char3 add_sat(char3 x, char3 y) __asm("air.add_sat.s.v3i8");
  __AIR_ASM__ char3 hadd(char3 x, char3 y) __asm("air.hadd.s.v3i8");
  __AIR_ASM__ char3 rhadd(char3 x, char3 y) __asm("air.rhadd.s.v3i8");
  __AIR_ASM__ char3 clamp(char3 x, char3 minval, char3 maxval) __asm("air.clamp.s.v3i8");
  __AIR_FUNC__ char3 clamp(char3 x, char minval, char maxval) { return clamp(x,(char3)(minval),(char3)(maxval)); }
  __AIR_INTERNAL__ char3 _air_clz(char3 x, bool is_zero_undef) __asm("air.clz.v3i8");
  __AIR_FUNC__ char3 clz(char3 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ char3 _air_ctz(char3 x, bool is_zero_undef) __asm("air.ctz.v3i8");
  __AIR_FUNC__ char3 ctz(char3 x) { return _air_ctz(x,false); }
  __AIR_ASM__ char3 mad_hi(char3 a, char3 b, char3 c) __asm("air.mad_hi.s.v3i8");
  __AIR_ASM__ char3 mad_sat(char3 a, char3 b, char3 c) __asm("air.mad_sat.s.v3i8");
  __AIR_ASM__ char3 max(char3 x, char3 y) __asm("air.max.s.v3i8");
  __AIR_FUNC__ char3 max(char3 x, char y) { return max(x,(char3)(y)); }
  __AIR_ASM__ char3 min(char3 x, char3 y) __asm("air.min.s.v3i8");
  __AIR_FUNC__ char3 min(char3 x, char y) { return max(x,(char3)(y)); }
  __AIR_ASM__ char3 mul_hi(char3 x, char3 y) __asm("air.mul_hi.s.v3i8");
  __AIR_ASM__ char3 rotate(char3 v, char3 i) __asm("air.rotate.v3i8");
  __AIR_ASM__ char3 sub_sat(char3 x, char3 y) __asm("air.sub_sat.s.v3i8");
  __AIR_ASM__ char3 popcount(char3 x) __asm("air.popcount.v3i8");
  __AIR_FUNC__ short3 upsample(char3 hi, uchar3 lo) { return (convert_short3(hi) << 8) | (convert_short3(lo)); }
  __AIR_ASM__ uchar3 abs(uchar3 x) __asm("air.abs.u.v3i8");
  __AIR_ASM__ uchar3 abs_diff(uchar3 x, uchar3 y) __asm("air.abs_diff.u.v3i8");
  __AIR_ASM__ uchar3 add_sat(uchar3 x, uchar3 y) __asm("air.add_sat.u.v3i8");
  __AIR_ASM__ uchar3 hadd(uchar3 x, uchar3 y) __asm("air.hadd.u.v3i8");
  __AIR_ASM__ uchar3 rhadd(uchar3 x, uchar3 y) __asm("air.rhadd.u.v3i8");
  __AIR_ASM__ uchar3 clamp(uchar3 x, uchar3 minval, uchar3 maxval) __asm("air.clamp.u.v3i8");
  __AIR_FUNC__ uchar3 clamp(uchar3 x, uchar minval, uchar maxval) { return clamp(x,(uchar3)(minval),(uchar3)(maxval)); }
  __AIR_INTERNAL__ uchar3 _air_clz(uchar3 x, bool is_zero_undef) __asm("air.clz.v3i8");
  __AIR_FUNC__ uchar3 clz(uchar3 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ uchar3 _air_ctz(uchar3 x, bool is_zero_undef) __asm("air.ctz.v3i8");
  __AIR_FUNC__ uchar3 ctz(uchar3 x) { return _air_ctz(x,false); }
  __AIR_ASM__ uchar3 mad_hi(uchar3 a, uchar3 b, uchar3 c) __asm("air.mad_hi.u.v3i8");
  __AIR_ASM__ uchar3 mad_sat(uchar3 a, uchar3 b, uchar3 c) __asm("air.mad_sat.u.v3i8");
  __AIR_ASM__ uchar3 max(uchar3 x, uchar3 y) __asm("air.max.u.v3i8");
  __AIR_FUNC__ uchar3 max(uchar3 x, uchar y) { return max(x,(uchar3)(y)); }
  __AIR_ASM__ uchar3 min(uchar3 x, uchar3 y) __asm("air.min.u.v3i8");
  __AIR_FUNC__ uchar3 min(uchar3 x, uchar y) { return max(x,(uchar3)(y)); }
  __AIR_ASM__ uchar3 mul_hi(uchar3 x, uchar3 y) __asm("air.mul_hi.u.v3i8");
  __AIR_ASM__ uchar3 rotate(uchar3 v, uchar3 i) __asm("air.rotate.v3i8");
  __AIR_ASM__ uchar3 sub_sat(uchar3 x, uchar3 y) __asm("air.sub_sat.u.v3i8");
  __AIR_ASM__ uchar3 popcount(uchar3 x) __asm("air.popcount.v3i8");
  __AIR_FUNC__ ushort3 upsample(uchar3 hi, uchar3 lo) { return (convert_ushort3(hi) << 8) | (convert_ushort3(lo)); }
  __AIR_ASM__ ushort3 abs(short3 x) __asm("air.abs.s.v3i16");
  __AIR_ASM__ ushort3 abs_diff(short3 x, short3 y) __asm("air.abs_diff.s.v3i16");
  __AIR_ASM__ short3 add_sat(short3 x, short3 y) __asm("air.add_sat.s.v3i16");
  __AIR_ASM__ short3 hadd(short3 x, short3 y) __asm("air.hadd.s.v3i16");
  __AIR_ASM__ short3 rhadd(short3 x, short3 y) __asm("air.rhadd.s.v3i16");
  __AIR_ASM__ short3 clamp(short3 x, short3 minval, short3 maxval) __asm("air.clamp.s.v3i16");
  __AIR_FUNC__ short3 clamp(short3 x, short minval, short maxval) { return clamp(x,(short3)(minval),(short3)(maxval)); }
  __AIR_INTERNAL__ short3 _air_clz(short3 x, bool is_zero_undef) __asm("air.clz.v3i16");
  __AIR_FUNC__ short3 clz(short3 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ short3 _air_ctz(short3 x, bool is_zero_undef) __asm("air.ctz.v3i16");
  __AIR_FUNC__ short3 ctz(short3 x) { return _air_ctz(x,false); }
  __AIR_ASM__ short3 mad_hi(short3 a, short3 b, short3 c) __asm("air.mad_hi.s.v3i16");
  __AIR_ASM__ short3 mad_sat(short3 a, short3 b, short3 c) __asm("air.mad_sat.s.v3i16");
  __AIR_ASM__ short3 max(short3 x, short3 y) __asm("air.max.s.v3i16");
  __AIR_FUNC__ short3 max(short3 x, short y) { return max(x,(short3)(y)); }
  __AIR_ASM__ short3 min(short3 x, short3 y) __asm("air.min.s.v3i16");
  __AIR_FUNC__ short3 min(short3 x, short y) { return max(x,(short3)(y)); }
  __AIR_ASM__ short3 mul_hi(short3 x, short3 y) __asm("air.mul_hi.s.v3i16");
  __AIR_ASM__ short3 rotate(short3 v, short3 i) __asm("air.rotate.v3i16");
  __AIR_ASM__ short3 sub_sat(short3 x, short3 y) __asm("air.sub_sat.s.v3i16");
  __AIR_ASM__ short3 popcount(short3 x) __asm("air.popcount.v3i16");
  __AIR_FUNC__ int3 upsample(short3 hi, ushort3 lo) { return (convert_int3(hi) << 16) | (convert_int3(lo)); }
  __AIR_ASM__ ushort3 abs(ushort3 x) __asm("air.abs.u.v3i16");
  __AIR_ASM__ ushort3 abs_diff(ushort3 x, ushort3 y) __asm("air.abs_diff.u.v3i16");
  __AIR_ASM__ ushort3 add_sat(ushort3 x, ushort3 y) __asm("air.add_sat.u.v3i16");
  __AIR_ASM__ ushort3 hadd(ushort3 x, ushort3 y) __asm("air.hadd.u.v3i16");
  __AIR_ASM__ ushort3 rhadd(ushort3 x, ushort3 y) __asm("air.rhadd.u.v3i16");
  __AIR_ASM__ ushort3 clamp(ushort3 x, ushort3 minval, ushort3 maxval) __asm("air.clamp.u.v3i16");
  __AIR_FUNC__ ushort3 clamp(ushort3 x, ushort minval, ushort maxval) { return clamp(x,(ushort3)(minval),(ushort3)(maxval)); }
  __AIR_INTERNAL__ ushort3 _air_clz(ushort3 x, bool is_zero_undef) __asm("air.clz.v3i16");
  __AIR_FUNC__ ushort3 clz(ushort3 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ ushort3 _air_ctz(ushort3 x, bool is_zero_undef) __asm("air.ctz.v3i16");
  __AIR_FUNC__ ushort3 ctz(ushort3 x) { return _air_ctz(x,false); }
  __AIR_ASM__ ushort3 mad_hi(ushort3 a, ushort3 b, ushort3 c) __asm("air.mad_hi.u.v3i16");
  __AIR_ASM__ ushort3 mad_sat(ushort3 a, ushort3 b, ushort3 c) __asm("air.mad_sat.u.v3i16");
  __AIR_ASM__ ushort3 max(ushort3 x, ushort3 y) __asm("air.max.u.v3i16");
  __AIR_FUNC__ ushort3 max(ushort3 x, ushort y) { return max(x,(ushort3)(y)); }
  __AIR_ASM__ ushort3 min(ushort3 x, ushort3 y) __asm("air.min.u.v3i16");
  __AIR_FUNC__ ushort3 min(ushort3 x, ushort y) { return max(x,(ushort3)(y)); }
  __AIR_ASM__ ushort3 mul_hi(ushort3 x, ushort3 y) __asm("air.mul_hi.u.v3i16");
  __AIR_ASM__ ushort3 rotate(ushort3 v, ushort3 i) __asm("air.rotate.v3i16");
  __AIR_ASM__ ushort3 sub_sat(ushort3 x, ushort3 y) __asm("air.sub_sat.u.v3i16");
  __AIR_ASM__ ushort3 popcount(ushort3 x) __asm("air.popcount.v3i16");
  __AIR_FUNC__ uint3 upsample(ushort3 hi, ushort3 lo) { return (convert_uint3(hi) << 16) | (convert_uint3(lo)); }
  __AIR_ASM__ uint3 abs(int3 x) __asm("air.abs.s.v3i32");
  __AIR_ASM__ uint3 abs_diff(int3 x, int3 y) __asm("air.abs_diff.s.v3i32");
  __AIR_ASM__ int3 add_sat(int3 x, int3 y) __asm("air.add_sat.s.v3i32");
  __AIR_ASM__ int3 hadd(int3 x, int3 y) __asm("air.hadd.s.v3i32");
  __AIR_ASM__ int3 rhadd(int3 x, int3 y) __asm("air.rhadd.s.v3i32");
  __AIR_ASM__ int3 clamp(int3 x, int3 minval, int3 maxval) __asm("air.clamp.s.v3i32");
  __AIR_FUNC__ int3 clamp(int3 x, int minval, int maxval) { return clamp(x,(int3)(minval),(int3)(maxval)); }
  __AIR_INTERNAL__ int3 _air_clz(int3 x, bool is_zero_undef) __asm("air.clz.v3i32");
  __AIR_FUNC__ int3 clz(int3 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ int3 _air_ctz(int3 x, bool is_zero_undef) __asm("air.ctz.v3i32");
  __AIR_FUNC__ int3 ctz(int3 x) { return _air_ctz(x,false); }
  __AIR_ASM__ int3 mad_hi(int3 a, int3 b, int3 c) __asm("air.mad_hi.s.v3i32");
  __AIR_ASM__ int3 mad_sat(int3 a, int3 b, int3 c) __asm("air.mad_sat.s.v3i32");
  __AIR_ASM__ int3 max(int3 x, int3 y) __asm("air.max.s.v3i32");
  __AIR_FUNC__ int3 max(int3 x, int y) { return max(x,(int3)(y)); }
  __AIR_ASM__ int3 min(int3 x, int3 y) __asm("air.min.s.v3i32");
  __AIR_FUNC__ int3 min(int3 x, int y) { return max(x,(int3)(y)); }
  __AIR_ASM__ int3 mul_hi(int3 x, int3 y) __asm("air.mul_hi.s.v3i32");
  __AIR_ASM__ int3 rotate(int3 v, int3 i) __asm("air.rotate.v3i32");
  __AIR_ASM__ int3 sub_sat(int3 x, int3 y) __asm("air.sub_sat.s.v3i32");
  __AIR_ASM__ int3 popcount(int3 x) __asm("air.popcount.v3i32");
  __AIR_FUNC__ long3 upsample(int3 hi, uint3 lo) { return (convert_long3(hi) << 32) | (convert_long3(lo)); }
  __AIR_ASM__ uint3 abs(uint3 x) __asm("air.abs.u.v3i32");
  __AIR_ASM__ uint3 abs_diff(uint3 x, uint3 y) __asm("air.abs_diff.u.v3i32");
  __AIR_ASM__ uint3 add_sat(uint3 x, uint3 y) __asm("air.add_sat.u.v3i32");
  __AIR_ASM__ uint3 hadd(uint3 x, uint3 y) __asm("air.hadd.u.v3i32");
  __AIR_ASM__ uint3 rhadd(uint3 x, uint3 y) __asm("air.rhadd.u.v3i32");
  __AIR_ASM__ uint3 clamp(uint3 x, uint3 minval, uint3 maxval) __asm("air.clamp.u.v3i32");
  __AIR_FUNC__ uint3 clamp(uint3 x, uint minval, uint maxval) { return clamp(x,(uint3)(minval),(uint3)(maxval)); }
  __AIR_INTERNAL__ uint3 _air_clz(uint3 x, bool is_zero_undef) __asm("air.clz.v3i32");
  __AIR_FUNC__ uint3 clz(uint3 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ uint3 _air_ctz(uint3 x, bool is_zero_undef) __asm("air.ctz.v3i32");
  __AIR_FUNC__ uint3 ctz(uint3 x) { return _air_ctz(x,false); }
  __AIR_ASM__ uint3 mad_hi(uint3 a, uint3 b, uint3 c) __asm("air.mad_hi.u.v3i32");
  __AIR_ASM__ uint3 mad_sat(uint3 a, uint3 b, uint3 c) __asm("air.mad_sat.u.v3i32");
  __AIR_ASM__ uint3 max(uint3 x, uint3 y) __asm("air.max.u.v3i32");
  __AIR_FUNC__ uint3 max(uint3 x, uint y) { return max(x,(uint3)(y)); }
  __AIR_ASM__ uint3 min(uint3 x, uint3 y) __asm("air.min.u.v3i32");
  __AIR_FUNC__ uint3 min(uint3 x, uint y) { return max(x,(uint3)(y)); }
  __AIR_ASM__ uint3 mul_hi(uint3 x, uint3 y) __asm("air.mul_hi.u.v3i32");
  __AIR_ASM__ uint3 rotate(uint3 v, uint3 i) __asm("air.rotate.v3i32");
  __AIR_ASM__ uint3 sub_sat(uint3 x, uint3 y) __asm("air.sub_sat.u.v3i32");
  __AIR_ASM__ uint3 popcount(uint3 x) __asm("air.popcount.v3i32");
  __AIR_FUNC__ ulong3 upsample(uint3 hi, uint3 lo) { return (convert_ulong3(hi) << 32) | (convert_ulong3(lo)); }
  __AIR_ASM__ ulong3 abs(long3 x) __asm("air.abs.s.v3i64");
  __AIR_ASM__ ulong3 abs_diff(long3 x, long3 y) __asm("air.abs_diff.s.v3i64");
  __AIR_ASM__ long3 add_sat(long3 x, long3 y) __asm("air.add_sat.s.v3i64");
  __AIR_ASM__ long3 hadd(long3 x, long3 y) __asm("air.hadd.s.v3i64");
  __AIR_ASM__ long3 rhadd(long3 x, long3 y) __asm("air.rhadd.s.v3i64");
  __AIR_ASM__ long3 clamp(long3 x, long3 minval, long3 maxval) __asm("air.clamp.s.v3i64");
  __AIR_FUNC__ long3 clamp(long3 x, long minval, long maxval) { return clamp(x,(long3)(minval),(long3)(maxval)); }
  __AIR_INTERNAL__ long3 _air_clz(long3 x, bool is_zero_undef) __asm("air.clz.v3i64");
  __AIR_FUNC__ long3 clz(long3 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ long3 _air_ctz(long3 x, bool is_zero_undef) __asm("air.ctz.v3i64");
  __AIR_FUNC__ long3 ctz(long3 x) { return _air_ctz(x,false); }
  __AIR_ASM__ long3 mad_hi(long3 a, long3 b, long3 c) __asm("air.mad_hi.s.v3i64");
  __AIR_ASM__ long3 mad_sat(long3 a, long3 b, long3 c) __asm("air.mad_sat.s.v3i64");
  __AIR_ASM__ long3 max(long3 x, long3 y) __asm("air.max.s.v3i64");
  __AIR_FUNC__ long3 max(long3 x, long y) { return max(x,(long3)(y)); }
  __AIR_ASM__ long3 min(long3 x, long3 y) __asm("air.min.s.v3i64");
  __AIR_FUNC__ long3 min(long3 x, long y) { return max(x,(long3)(y)); }
  __AIR_ASM__ long3 mul_hi(long3 x, long3 y) __asm("air.mul_hi.s.v3i64");
  __AIR_ASM__ long3 rotate(long3 v, long3 i) __asm("air.rotate.v3i64");
  __AIR_ASM__ long3 sub_sat(long3 x, long3 y) __asm("air.sub_sat.s.v3i64");
  __AIR_ASM__ long3 popcount(long3 x) __asm("air.popcount.v3i64");
  __AIR_ASM__ ulong3 abs(ulong3 x) __asm("air.abs.u.v3i64");
  __AIR_ASM__ ulong3 abs_diff(ulong3 x, ulong3 y) __asm("air.abs_diff.u.v3i64");
  __AIR_ASM__ ulong3 add_sat(ulong3 x, ulong3 y) __asm("air.add_sat.u.v3i64");
  __AIR_ASM__ ulong3 hadd(ulong3 x, ulong3 y) __asm("air.hadd.u.v3i64");
  __AIR_ASM__ ulong3 rhadd(ulong3 x, ulong3 y) __asm("air.rhadd.u.v3i64");
  __AIR_ASM__ ulong3 clamp(ulong3 x, ulong3 minval, ulong3 maxval) __asm("air.clamp.u.v3i64");
  __AIR_FUNC__ ulong3 clamp(ulong3 x, ulong minval, ulong maxval) { return clamp(x,(ulong3)(minval),(ulong3)(maxval)); }
  __AIR_INTERNAL__ ulong3 _air_clz(ulong3 x, bool is_zero_undef) __asm("air.clz.v3i64");
  __AIR_FUNC__ ulong3 clz(ulong3 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ ulong3 _air_ctz(ulong3 x, bool is_zero_undef) __asm("air.ctz.v3i64");
  __AIR_FUNC__ ulong3 ctz(ulong3 x) { return _air_ctz(x,false); }
  __AIR_ASM__ ulong3 mad_hi(ulong3 a, ulong3 b, ulong3 c) __asm("air.mad_hi.u.v3i64");
  __AIR_ASM__ ulong3 mad_sat(ulong3 a, ulong3 b, ulong3 c) __asm("air.mad_sat.u.v3i64");
  __AIR_ASM__ ulong3 max(ulong3 x, ulong3 y) __asm("air.max.u.v3i64");
  __AIR_FUNC__ ulong3 max(ulong3 x, ulong y) { return max(x,(ulong3)(y)); }
  __AIR_ASM__ ulong3 min(ulong3 x, ulong3 y) __asm("air.min.u.v3i64");
  __AIR_FUNC__ ulong3 min(ulong3 x, ulong y) { return max(x,(ulong3)(y)); }
  __AIR_ASM__ ulong3 mul_hi(ulong3 x, ulong3 y) __asm("air.mul_hi.u.v3i64");
  __AIR_ASM__ ulong3 rotate(ulong3 v, ulong3 i) __asm("air.rotate.v3i64");
  __AIR_ASM__ ulong3 sub_sat(ulong3 x, ulong3 y) __asm("air.sub_sat.u.v3i64");
  __AIR_ASM__ ulong3 popcount(ulong3 x) __asm("air.popcount.v3i64");
  __AIR_ASM__ uchar4 abs(char4 x) __asm("air.abs.s.v4i8");
  __AIR_ASM__ uchar4 abs_diff(char4 x, char4 y) __asm("air.abs_diff.s.v4i8");
  __AIR_ASM__ char4 add_sat(char4 x, char4 y) __asm("air.add_sat.s.v4i8");
  __AIR_ASM__ char4 hadd(char4 x, char4 y) __asm("air.hadd.s.v4i8");
  __AIR_ASM__ char4 rhadd(char4 x, char4 y) __asm("air.rhadd.s.v4i8");
  __AIR_ASM__ char4 clamp(char4 x, char4 minval, char4 maxval) __asm("air.clamp.s.v4i8");
  __AIR_FUNC__ char4 clamp(char4 x, char minval, char maxval) { return clamp(x,(char4)(minval),(char4)(maxval)); }
  __AIR_INTERNAL__ char4 _air_clz(char4 x, bool is_zero_undef) __asm("air.clz.v4i8");
  __AIR_FUNC__ char4 clz(char4 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ char4 _air_ctz(char4 x, bool is_zero_undef) __asm("air.ctz.v4i8");
  __AIR_FUNC__ char4 ctz(char4 x) { return _air_ctz(x,false); }
  __AIR_ASM__ char4 mad_hi(char4 a, char4 b, char4 c) __asm("air.mad_hi.s.v4i8");
  __AIR_ASM__ char4 mad_sat(char4 a, char4 b, char4 c) __asm("air.mad_sat.s.v4i8");
  __AIR_ASM__ char4 max(char4 x, char4 y) __asm("air.max.s.v4i8");
  __AIR_FUNC__ char4 max(char4 x, char y) { return max(x,(char4)(y)); }
  __AIR_ASM__ char4 min(char4 x, char4 y) __asm("air.min.s.v4i8");
  __AIR_FUNC__ char4 min(char4 x, char y) { return max(x,(char4)(y)); }
  __AIR_ASM__ char4 mul_hi(char4 x, char4 y) __asm("air.mul_hi.s.v4i8");
  __AIR_ASM__ char4 rotate(char4 v, char4 i) __asm("air.rotate.v4i8");
  __AIR_ASM__ char4 sub_sat(char4 x, char4 y) __asm("air.sub_sat.s.v4i8");
  __AIR_ASM__ char4 popcount(char4 x) __asm("air.popcount.v4i8");
  __AIR_FUNC__ short4 upsample(char4 hi, uchar4 lo) { return (convert_short4(hi) << 8) | (convert_short4(lo)); }
  __AIR_ASM__ uchar4 abs(uchar4 x) __asm("air.abs.u.v4i8");
  __AIR_ASM__ uchar4 abs_diff(uchar4 x, uchar4 y) __asm("air.abs_diff.u.v4i8");
  __AIR_ASM__ uchar4 add_sat(uchar4 x, uchar4 y) __asm("air.add_sat.u.v4i8");
  __AIR_ASM__ uchar4 hadd(uchar4 x, uchar4 y) __asm("air.hadd.u.v4i8");
  __AIR_ASM__ uchar4 rhadd(uchar4 x, uchar4 y) __asm("air.rhadd.u.v4i8");
  __AIR_ASM__ uchar4 clamp(uchar4 x, uchar4 minval, uchar4 maxval) __asm("air.clamp.u.v4i8");
  __AIR_FUNC__ uchar4 clamp(uchar4 x, uchar minval, uchar maxval) { return clamp(x,(uchar4)(minval),(uchar4)(maxval)); }
  __AIR_INTERNAL__ uchar4 _air_clz(uchar4 x, bool is_zero_undef) __asm("air.clz.v4i8");
  __AIR_FUNC__ uchar4 clz(uchar4 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ uchar4 _air_ctz(uchar4 x, bool is_zero_undef) __asm("air.ctz.v4i8");
  __AIR_FUNC__ uchar4 ctz(uchar4 x) { return _air_ctz(x,false); }
  __AIR_ASM__ uchar4 mad_hi(uchar4 a, uchar4 b, uchar4 c) __asm("air.mad_hi.u.v4i8");
  __AIR_ASM__ uchar4 mad_sat(uchar4 a, uchar4 b, uchar4 c) __asm("air.mad_sat.u.v4i8");
  __AIR_ASM__ uchar4 max(uchar4 x, uchar4 y) __asm("air.max.u.v4i8");
  __AIR_FUNC__ uchar4 max(uchar4 x, uchar y) { return max(x,(uchar4)(y)); }
  __AIR_ASM__ uchar4 min(uchar4 x, uchar4 y) __asm("air.min.u.v4i8");
  __AIR_FUNC__ uchar4 min(uchar4 x, uchar y) { return max(x,(uchar4)(y)); }
  __AIR_ASM__ uchar4 mul_hi(uchar4 x, uchar4 y) __asm("air.mul_hi.u.v4i8");
  __AIR_ASM__ uchar4 rotate(uchar4 v, uchar4 i) __asm("air.rotate.v4i8");
  __AIR_ASM__ uchar4 sub_sat(uchar4 x, uchar4 y) __asm("air.sub_sat.u.v4i8");
  __AIR_ASM__ uchar4 popcount(uchar4 x) __asm("air.popcount.v4i8");
  __AIR_FUNC__ ushort4 upsample(uchar4 hi, uchar4 lo) { return (convert_ushort4(hi) << 8) | (convert_ushort4(lo)); }
  __AIR_ASM__ ushort4 abs(short4 x) __asm("air.abs.s.v4i16");
  __AIR_ASM__ ushort4 abs_diff(short4 x, short4 y) __asm("air.abs_diff.s.v4i16");
  __AIR_ASM__ short4 add_sat(short4 x, short4 y) __asm("air.add_sat.s.v4i16");
  __AIR_ASM__ short4 hadd(short4 x, short4 y) __asm("air.hadd.s.v4i16");
  __AIR_ASM__ short4 rhadd(short4 x, short4 y) __asm("air.rhadd.s.v4i16");
  __AIR_ASM__ short4 clamp(short4 x, short4 minval, short4 maxval) __asm("air.clamp.s.v4i16");
  __AIR_FUNC__ short4 clamp(short4 x, short minval, short maxval) { return clamp(x,(short4)(minval),(short4)(maxval)); }
  __AIR_INTERNAL__ short4 _air_clz(short4 x, bool is_zero_undef) __asm("air.clz.v4i16");
  __AIR_FUNC__ short4 clz(short4 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ short4 _air_ctz(short4 x, bool is_zero_undef) __asm("air.ctz.v4i16");
  __AIR_FUNC__ short4 ctz(short4 x) { return _air_ctz(x,false); }
  __AIR_ASM__ short4 mad_hi(short4 a, short4 b, short4 c) __asm("air.mad_hi.s.v4i16");
  __AIR_ASM__ short4 mad_sat(short4 a, short4 b, short4 c) __asm("air.mad_sat.s.v4i16");
  __AIR_ASM__ short4 max(short4 x, short4 y) __asm("air.max.s.v4i16");
  __AIR_FUNC__ short4 max(short4 x, short y) { return max(x,(short4)(y)); }
  __AIR_ASM__ short4 min(short4 x, short4 y) __asm("air.min.s.v4i16");
  __AIR_FUNC__ short4 min(short4 x, short y) { return max(x,(short4)(y)); }
  __AIR_ASM__ short4 mul_hi(short4 x, short4 y) __asm("air.mul_hi.s.v4i16");
  __AIR_ASM__ short4 rotate(short4 v, short4 i) __asm("air.rotate.v4i16");
  __AIR_ASM__ short4 sub_sat(short4 x, short4 y) __asm("air.sub_sat.s.v4i16");
  __AIR_ASM__ short4 popcount(short4 x) __asm("air.popcount.v4i16");
  __AIR_FUNC__ int4 upsample(short4 hi, ushort4 lo) { return (convert_int4(hi) << 16) | (convert_int4(lo)); }
  __AIR_ASM__ ushort4 abs(ushort4 x) __asm("air.abs.u.v4i16");
  __AIR_ASM__ ushort4 abs_diff(ushort4 x, ushort4 y) __asm("air.abs_diff.u.v4i16");
  __AIR_ASM__ ushort4 add_sat(ushort4 x, ushort4 y) __asm("air.add_sat.u.v4i16");
  __AIR_ASM__ ushort4 hadd(ushort4 x, ushort4 y) __asm("air.hadd.u.v4i16");
  __AIR_ASM__ ushort4 rhadd(ushort4 x, ushort4 y) __asm("air.rhadd.u.v4i16");
  __AIR_ASM__ ushort4 clamp(ushort4 x, ushort4 minval, ushort4 maxval) __asm("air.clamp.u.v4i16");
  __AIR_FUNC__ ushort4 clamp(ushort4 x, ushort minval, ushort maxval) { return clamp(x,(ushort4)(minval),(ushort4)(maxval)); }
  __AIR_INTERNAL__ ushort4 _air_clz(ushort4 x, bool is_zero_undef) __asm("air.clz.v4i16");
  __AIR_FUNC__ ushort4 clz(ushort4 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ ushort4 _air_ctz(ushort4 x, bool is_zero_undef) __asm("air.ctz.v4i16");
  __AIR_FUNC__ ushort4 ctz(ushort4 x) { return _air_ctz(x,false); }
  __AIR_ASM__ ushort4 mad_hi(ushort4 a, ushort4 b, ushort4 c) __asm("air.mad_hi.u.v4i16");
  __AIR_ASM__ ushort4 mad_sat(ushort4 a, ushort4 b, ushort4 c) __asm("air.mad_sat.u.v4i16");
  __AIR_ASM__ ushort4 max(ushort4 x, ushort4 y) __asm("air.max.u.v4i16");
  __AIR_FUNC__ ushort4 max(ushort4 x, ushort y) { return max(x,(ushort4)(y)); }
  __AIR_ASM__ ushort4 min(ushort4 x, ushort4 y) __asm("air.min.u.v4i16");
  __AIR_FUNC__ ushort4 min(ushort4 x, ushort y) { return max(x,(ushort4)(y)); }
  __AIR_ASM__ ushort4 mul_hi(ushort4 x, ushort4 y) __asm("air.mul_hi.u.v4i16");
  __AIR_ASM__ ushort4 rotate(ushort4 v, ushort4 i) __asm("air.rotate.v4i16");
  __AIR_ASM__ ushort4 sub_sat(ushort4 x, ushort4 y) __asm("air.sub_sat.u.v4i16");
  __AIR_ASM__ ushort4 popcount(ushort4 x) __asm("air.popcount.v4i16");
  __AIR_FUNC__ uint4 upsample(ushort4 hi, ushort4 lo) { return (convert_uint4(hi) << 16) | (convert_uint4(lo)); }
  __AIR_ASM__ uint4 abs(int4 x) __asm("air.abs.s.v4i32");
  __AIR_ASM__ uint4 abs_diff(int4 x, int4 y) __asm("air.abs_diff.s.v4i32");
  __AIR_ASM__ int4 add_sat(int4 x, int4 y) __asm("air.add_sat.s.v4i32");
  __AIR_ASM__ int4 hadd(int4 x, int4 y) __asm("air.hadd.s.v4i32");
  __AIR_ASM__ int4 rhadd(int4 x, int4 y) __asm("air.rhadd.s.v4i32");
  __AIR_ASM__ int4 clamp(int4 x, int4 minval, int4 maxval) __asm("air.clamp.s.v4i32");
  __AIR_FUNC__ int4 clamp(int4 x, int minval, int maxval) { return clamp(x,(int4)(minval),(int4)(maxval)); }
  __AIR_INTERNAL__ int4 _air_clz(int4 x, bool is_zero_undef) __asm("air.clz.v4i32");
  __AIR_FUNC__ int4 clz(int4 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ int4 _air_ctz(int4 x, bool is_zero_undef) __asm("air.ctz.v4i32");
  __AIR_FUNC__ int4 ctz(int4 x) { return _air_ctz(x,false); }
  __AIR_ASM__ int4 mad_hi(int4 a, int4 b, int4 c) __asm("air.mad_hi.s.v4i32");
  __AIR_ASM__ int4 mad_sat(int4 a, int4 b, int4 c) __asm("air.mad_sat.s.v4i32");
  __AIR_ASM__ int4 max(int4 x, int4 y) __asm("air.max.s.v4i32");
  __AIR_FUNC__ int4 max(int4 x, int y) { return max(x,(int4)(y)); }
  __AIR_ASM__ int4 min(int4 x, int4 y) __asm("air.min.s.v4i32");
  __AIR_FUNC__ int4 min(int4 x, int y) { return max(x,(int4)(y)); }
  __AIR_ASM__ int4 mul_hi(int4 x, int4 y) __asm("air.mul_hi.s.v4i32");
  __AIR_ASM__ int4 rotate(int4 v, int4 i) __asm("air.rotate.v4i32");
  __AIR_ASM__ int4 sub_sat(int4 x, int4 y) __asm("air.sub_sat.s.v4i32");
  __AIR_ASM__ int4 popcount(int4 x) __asm("air.popcount.v4i32");
  __AIR_FUNC__ long4 upsample(int4 hi, uint4 lo) { return (convert_long4(hi) << 32) | (convert_long4(lo)); }
  __AIR_ASM__ uint4 abs(uint4 x) __asm("air.abs.u.v4i32");
  __AIR_ASM__ uint4 abs_diff(uint4 x, uint4 y) __asm("air.abs_diff.u.v4i32");
  __AIR_ASM__ uint4 add_sat(uint4 x, uint4 y) __asm("air.add_sat.u.v4i32");
  __AIR_ASM__ uint4 hadd(uint4 x, uint4 y) __asm("air.hadd.u.v4i32");
  __AIR_ASM__ uint4 rhadd(uint4 x, uint4 y) __asm("air.rhadd.u.v4i32");
  __AIR_ASM__ uint4 clamp(uint4 x, uint4 minval, uint4 maxval) __asm("air.clamp.u.v4i32");
  __AIR_FUNC__ uint4 clamp(uint4 x, uint minval, uint maxval) { return clamp(x,(uint4)(minval),(uint4)(maxval)); }
  __AIR_INTERNAL__ uint4 _air_clz(uint4 x, bool is_zero_undef) __asm("air.clz.v4i32");
  __AIR_FUNC__ uint4 clz(uint4 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ uint4 _air_ctz(uint4 x, bool is_zero_undef) __asm("air.ctz.v4i32");
  __AIR_FUNC__ uint4 ctz(uint4 x) { return _air_ctz(x,false); }
  __AIR_ASM__ uint4 mad_hi(uint4 a, uint4 b, uint4 c) __asm("air.mad_hi.u.v4i32");
  __AIR_ASM__ uint4 mad_sat(uint4 a, uint4 b, uint4 c) __asm("air.mad_sat.u.v4i32");
  __AIR_ASM__ uint4 max(uint4 x, uint4 y) __asm("air.max.u.v4i32");
  __AIR_FUNC__ uint4 max(uint4 x, uint y) { return max(x,(uint4)(y)); }
  __AIR_ASM__ uint4 min(uint4 x, uint4 y) __asm("air.min.u.v4i32");
  __AIR_FUNC__ uint4 min(uint4 x, uint y) { return max(x,(uint4)(y)); }
  __AIR_ASM__ uint4 mul_hi(uint4 x, uint4 y) __asm("air.mul_hi.u.v4i32");
  __AIR_ASM__ uint4 rotate(uint4 v, uint4 i) __asm("air.rotate.v4i32");
  __AIR_ASM__ uint4 sub_sat(uint4 x, uint4 y) __asm("air.sub_sat.u.v4i32");
  __AIR_ASM__ uint4 popcount(uint4 x) __asm("air.popcount.v4i32");
  __AIR_FUNC__ ulong4 upsample(uint4 hi, uint4 lo) { return (convert_ulong4(hi) << 32) | (convert_ulong4(lo)); }
  __AIR_ASM__ ulong4 abs(long4 x) __asm("air.abs.s.v4i64");
  __AIR_ASM__ ulong4 abs_diff(long4 x, long4 y) __asm("air.abs_diff.s.v4i64");
  __AIR_ASM__ long4 add_sat(long4 x, long4 y) __asm("air.add_sat.s.v4i64");
  __AIR_ASM__ long4 hadd(long4 x, long4 y) __asm("air.hadd.s.v4i64");
  __AIR_ASM__ long4 rhadd(long4 x, long4 y) __asm("air.rhadd.s.v4i64");
  __AIR_ASM__ long4 clamp(long4 x, long4 minval, long4 maxval) __asm("air.clamp.s.v4i64");
  __AIR_FUNC__ long4 clamp(long4 x, long minval, long maxval) { return clamp(x,(long4)(minval),(long4)(maxval)); }
  __AIR_INTERNAL__ long4 _air_clz(long4 x, bool is_zero_undef) __asm("air.clz.v4i64");
  __AIR_FUNC__ long4 clz(long4 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ long4 _air_ctz(long4 x, bool is_zero_undef) __asm("air.ctz.v4i64");
  __AIR_FUNC__ long4 ctz(long4 x) { return _air_ctz(x,false); }
  __AIR_ASM__ long4 mad_hi(long4 a, long4 b, long4 c) __asm("air.mad_hi.s.v4i64");
  __AIR_ASM__ long4 mad_sat(long4 a, long4 b, long4 c) __asm("air.mad_sat.s.v4i64");
  __AIR_ASM__ long4 max(long4 x, long4 y) __asm("air.max.s.v4i64");
  __AIR_FUNC__ long4 max(long4 x, long y) { return max(x,(long4)(y)); }
  __AIR_ASM__ long4 min(long4 x, long4 y) __asm("air.min.s.v4i64");
  __AIR_FUNC__ long4 min(long4 x, long y) { return max(x,(long4)(y)); }
  __AIR_ASM__ long4 mul_hi(long4 x, long4 y) __asm("air.mul_hi.s.v4i64");
  __AIR_ASM__ long4 rotate(long4 v, long4 i) __asm("air.rotate.v4i64");
  __AIR_ASM__ long4 sub_sat(long4 x, long4 y) __asm("air.sub_sat.s.v4i64");
  __AIR_ASM__ long4 popcount(long4 x) __asm("air.popcount.v4i64");
  __AIR_ASM__ ulong4 abs(ulong4 x) __asm("air.abs.u.v4i64");
  __AIR_ASM__ ulong4 abs_diff(ulong4 x, ulong4 y) __asm("air.abs_diff.u.v4i64");
  __AIR_ASM__ ulong4 add_sat(ulong4 x, ulong4 y) __asm("air.add_sat.u.v4i64");
  __AIR_ASM__ ulong4 hadd(ulong4 x, ulong4 y) __asm("air.hadd.u.v4i64");
  __AIR_ASM__ ulong4 rhadd(ulong4 x, ulong4 y) __asm("air.rhadd.u.v4i64");
  __AIR_ASM__ ulong4 clamp(ulong4 x, ulong4 minval, ulong4 maxval) __asm("air.clamp.u.v4i64");
  __AIR_FUNC__ ulong4 clamp(ulong4 x, ulong minval, ulong maxval) { return clamp(x,(ulong4)(minval),(ulong4)(maxval)); }
  __AIR_INTERNAL__ ulong4 _air_clz(ulong4 x, bool is_zero_undef) __asm("air.clz.v4i64");
  __AIR_FUNC__ ulong4 clz(ulong4 x) { return _air_clz(x,false); }
  __AIR_INTERNAL__ ulong4 _air_ctz(ulong4 x, bool is_zero_undef) __asm("air.ctz.v4i64");
  __AIR_FUNC__ ulong4 ctz(ulong4 x) { return _air_ctz(x,false); }
  __AIR_ASM__ ulong4 mad_hi(ulong4 a, ulong4 b, ulong4 c) __asm("air.mad_hi.u.v4i64");
  __AIR_ASM__ ulong4 mad_sat(ulong4 a, ulong4 b, ulong4 c) __asm("air.mad_sat.u.v4i64");
  __AIR_ASM__ ulong4 max(ulong4 x, ulong4 y) __asm("air.max.u.v4i64");
  __AIR_FUNC__ ulong4 max(ulong4 x, ulong y) { return max(x,(ulong4)(y)); }
  __AIR_ASM__ ulong4 min(ulong4 x, ulong4 y) __asm("air.min.u.v4i64");
  __AIR_FUNC__ ulong4 min(ulong4 x, ulong y) { return max(x,(ulong4)(y)); }
  __AIR_ASM__ ulong4 mul_hi(ulong4 x, ulong4 y) __asm("air.mul_hi.u.v4i64");
  __AIR_ASM__ ulong4 rotate(ulong4 v, ulong4 i) __asm("air.rotate.v4i64");
  __AIR_ASM__ ulong4 sub_sat(ulong4 x, ulong4 y) __asm("air.sub_sat.u.v4i64");
  __AIR_ASM__ ulong4 popcount(ulong4 x) __asm("air.popcount.v4i64");

  __AIR_FUNC__ char8 clz(char8 x) { char8 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ char8 ctz(char8 x) { char8 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ char8 popcount(char8 x) { char8 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ uchar8 clz(uchar8 x) { uchar8 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ uchar8 ctz(uchar8 x) { uchar8 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ uchar8 popcount(uchar8 x) { uchar8 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ short8 clz(short8 x) { short8 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ short8 ctz(short8 x) { short8 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ short8 popcount(short8 x) { short8 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ ushort8 clz(ushort8 x) { ushort8 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ ushort8 ctz(ushort8 x) { ushort8 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ ushort8 popcount(ushort8 x) { ushort8 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ int8 clz(int8 x) { int8 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ int8 ctz(int8 x) { int8 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ int8 popcount(int8 x) { int8 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ uint8 clz(uint8 x) { uint8 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ uint8 ctz(uint8 x) { uint8 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ uint8 popcount(uint8 x) { uint8 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ long8 clz(long8 x) { long8 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ long8 ctz(long8 x) { long8 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ long8 popcount(long8 x) { long8 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ ulong8 clz(ulong8 x) { ulong8 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ ulong8 ctz(ulong8 x) { ulong8 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ ulong8 popcount(ulong8 x) { ulong8 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ char16 clz(char16 x) { char16 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ char16 ctz(char16 x) { char16 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ char16 popcount(char16 x) { char16 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ uchar16 clz(uchar16 x) { uchar16 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ uchar16 ctz(uchar16 x) { uchar16 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ uchar16 popcount(uchar16 x) { uchar16 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ short16 clz(short16 x) { short16 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ short16 ctz(short16 x) { short16 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ short16 popcount(short16 x) { short16 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ ushort16 clz(ushort16 x) { ushort16 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ ushort16 ctz(ushort16 x) { ushort16 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ ushort16 popcount(ushort16 x) { ushort16 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ int16 clz(int16 x) { int16 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ int16 ctz(int16 x) { int16 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ int16 popcount(int16 x) { int16 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ uint16 clz(uint16 x) { uint16 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ uint16 ctz(uint16 x) { uint16 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ uint16 popcount(uint16 x) { uint16 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ long16 clz(long16 x) { long16 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ long16 ctz(long16 x) { long16 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ long16 popcount(long16 x) { long16 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }
  __AIR_FUNC__ ulong16 clz(ulong16 x) { ulong16 r; r.hi = clz(x.hi); r.lo = clz(x.lo); return r; }
  __AIR_FUNC__ ulong16 ctz(ulong16 x) { ulong16 r; r.hi = ctz(x.hi); r.lo = ctz(x.lo); return r; }
  __AIR_FUNC__ ulong16 popcount(ulong16 x) { ulong16 r; r.hi = popcount(x.hi); r.lo = popcount(x.lo); return r; }

  __AIR_FUNC__ uchar8 abs(char8 x) { uchar8 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ uchar8 abs(uchar8 x) { uchar8 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ ushort8 abs(short8 x) { ushort8 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ ushort8 abs(ushort8 x) { ushort8 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ uint8 abs(int8 x) { uint8 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ uint8 abs(uint8 x) { uint8 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ ulong8 abs(long8 x) { ulong8 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ ulong8 abs(ulong8 x) { ulong8 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ uchar16 abs(char16 x) { uchar16 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ uchar16 abs(uchar16 x) { uchar16 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ ushort16 abs(short16 x) { ushort16 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ ushort16 abs(ushort16 x) { ushort16 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ uint16 abs(int16 x) { uint16 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ uint16 abs(uint16 x) { uint16 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ ulong16 abs(long16 x) { ulong16 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }
  __AIR_FUNC__ ulong16 abs(ulong16 x) { ulong16 r; r.hi = abs(x.hi); r.lo = abs(x.lo); return r; }


  __AIR_FUNC__ char8 add_sat(char8 x, char8 y) {
     char8 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char8 hadd(char8 x, char8 y) {
     char8 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char8 rhadd(char8 x, char8 y) {
     char8 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char8 max(char8 x, char8 y) {
     char8 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char8 min(char8 x, char8 y) {
     char8 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char8 mul_hi(char8 x, char8 y) {
     char8 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char8 rotate(char8 x, char8 y) {
     char8 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char8 sub_sat(char8 x, char8 y) {
     char8 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 add_sat(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 hadd(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 rhadd(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 max(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 min(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 mul_hi(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 rotate(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 sub_sat(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short8 add_sat(short8 x, short8 y) {
     short8 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short8 hadd(short8 x, short8 y) {
     short8 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short8 rhadd(short8 x, short8 y) {
     short8 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short8 max(short8 x, short8 y) {
     short8 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short8 min(short8 x, short8 y) {
     short8 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short8 mul_hi(short8 x, short8 y) {
     short8 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short8 rotate(short8 x, short8 y) {
     short8 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short8 sub_sat(short8 x, short8 y) {
     short8 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 add_sat(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 hadd(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 rhadd(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 max(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 min(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 mul_hi(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 rotate(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 sub_sat(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int8 add_sat(int8 x, int8 y) {
     int8 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int8 hadd(int8 x, int8 y) {
     int8 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int8 rhadd(int8 x, int8 y) {
     int8 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int8 max(int8 x, int8 y) {
     int8 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int8 min(int8 x, int8 y) {
     int8 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int8 mul_hi(int8 x, int8 y) {
     int8 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int8 rotate(int8 x, int8 y) {
     int8 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int8 sub_sat(int8 x, int8 y) {
     int8 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 add_sat(uint8 x, uint8 y) {
     uint8 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 hadd(uint8 x, uint8 y) {
     uint8 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 rhadd(uint8 x, uint8 y) {
     uint8 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 max(uint8 x, uint8 y) {
     uint8 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 min(uint8 x, uint8 y) {
     uint8 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 mul_hi(uint8 x, uint8 y) {
     uint8 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 rotate(uint8 x, uint8 y) {
     uint8 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 sub_sat(uint8 x, uint8 y) {
     uint8 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long8 add_sat(long8 x, long8 y) {
     long8 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long8 hadd(long8 x, long8 y) {
     long8 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long8 rhadd(long8 x, long8 y) {
     long8 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long8 max(long8 x, long8 y) {
     long8 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long8 min(long8 x, long8 y) {
     long8 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long8 mul_hi(long8 x, long8 y) {
     long8 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long8 rotate(long8 x, long8 y) {
     long8 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long8 sub_sat(long8 x, long8 y) {
     long8 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 add_sat(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 hadd(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 rhadd(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 max(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 min(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 mul_hi(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 rotate(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 sub_sat(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char16 add_sat(char16 x, char16 y) {
     char16 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char16 hadd(char16 x, char16 y) {
     char16 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char16 rhadd(char16 x, char16 y) {
     char16 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char16 max(char16 x, char16 y) {
     char16 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char16 min(char16 x, char16 y) {
     char16 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char16 mul_hi(char16 x, char16 y) {
     char16 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char16 rotate(char16 x, char16 y) {
     char16 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ char16 sub_sat(char16 x, char16 y) {
     char16 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 add_sat(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 hadd(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 rhadd(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 max(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 min(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 mul_hi(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 rotate(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 sub_sat(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short16 add_sat(short16 x, short16 y) {
     short16 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short16 hadd(short16 x, short16 y) {
     short16 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short16 rhadd(short16 x, short16 y) {
     short16 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short16 max(short16 x, short16 y) {
     short16 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short16 min(short16 x, short16 y) {
     short16 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short16 mul_hi(short16 x, short16 y) {
     short16 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short16 rotate(short16 x, short16 y) {
     short16 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ short16 sub_sat(short16 x, short16 y) {
     short16 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 add_sat(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 hadd(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 rhadd(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 max(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 min(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 mul_hi(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 rotate(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 sub_sat(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int16 add_sat(int16 x, int16 y) {
     int16 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int16 hadd(int16 x, int16 y) {
     int16 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int16 rhadd(int16 x, int16 y) {
     int16 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int16 max(int16 x, int16 y) {
     int16 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int16 min(int16 x, int16 y) {
     int16 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int16 mul_hi(int16 x, int16 y) {
     int16 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int16 rotate(int16 x, int16 y) {
     int16 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ int16 sub_sat(int16 x, int16 y) {
     int16 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 add_sat(uint16 x, uint16 y) {
     uint16 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 hadd(uint16 x, uint16 y) {
     uint16 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 rhadd(uint16 x, uint16 y) {
     uint16 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 max(uint16 x, uint16 y) {
     uint16 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 min(uint16 x, uint16 y) {
     uint16 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 mul_hi(uint16 x, uint16 y) {
     uint16 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 rotate(uint16 x, uint16 y) {
     uint16 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 sub_sat(uint16 x, uint16 y) {
     uint16 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long16 add_sat(long16 x, long16 y) {
     long16 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long16 hadd(long16 x, long16 y) {
     long16 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long16 rhadd(long16 x, long16 y) {
     long16 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long16 max(long16 x, long16 y) {
     long16 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long16 min(long16 x, long16 y) {
     long16 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long16 mul_hi(long16 x, long16 y) {
     long16 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long16 rotate(long16 x, long16 y) {
     long16 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ long16 sub_sat(long16 x, long16 y) {
     long16 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 add_sat(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = add_sat(x.hi, y.hi);
     r.lo = add_sat(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 hadd(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = hadd(x.hi, y.hi);
     r.lo = hadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 rhadd(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = rhadd(x.hi, y.hi);
     r.lo = rhadd(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 max(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = max(x.hi, y.hi);
     r.lo = max(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 min(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = min(x.hi, y.hi);
     r.lo = min(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 mul_hi(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = mul_hi(x.hi, y.hi);
     r.lo = mul_hi(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 rotate(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = rotate(x.hi, y.hi);
     r.lo = rotate(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 sub_sat(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = sub_sat(x.hi, y.hi);
     r.lo = sub_sat(x.lo, y.lo);
     return r;
  }

  __AIR_FUNC__ uchar8 abs_diff(char8 x, char8 y) {
     uchar8 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 abs_diff(uchar8 x, uchar8 y) {
     uchar8 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 abs_diff(short8 x, short8 y) {
     ushort8 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 abs_diff(ushort8 x, ushort8 y) {
     ushort8 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 abs_diff(int8 x, int8 y) {
     uint8 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint8 abs_diff(uint8 x, uint8 y) {
     uint8 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 abs_diff(long8 x, long8 y) {
     ulong8 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 abs_diff(ulong8 x, ulong8 y) {
     ulong8 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 abs_diff(char16 x, char16 y) {
     uchar16 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 abs_diff(uchar16 x, uchar16 y) {
     uchar16 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 abs_diff(short16 x, short16 y) {
     ushort16 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 abs_diff(ushort16 x, ushort16 y) {
     ushort16 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 abs_diff(int16 x, int16 y) {
     uint16 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ uint16 abs_diff(uint16 x, uint16 y) {
     uint16 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 abs_diff(long16 x, long16 y) {
     ulong16 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 abs_diff(ulong16 x, ulong16 y) {
     ulong16 r;
     r.hi = abs_diff(x.hi, y.hi);
     r.lo = abs_diff(x.lo, y.lo);
     return r;
  }

  __AIR_FUNC__ char8 clamp(char8 x, char8 y, char8 z) {
     char8 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ char8 mad_hi(char8 x, char8 y, char8 z) {
     char8 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ char8 mad_sat(char8 x, char8 y, char8 z) {
     char8 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 clamp(uchar8 x, uchar8 y, uchar8 z) {
     uchar8 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 mad_hi(uchar8 x, uchar8 y, uchar8 z) {
     uchar8 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uchar8 mad_sat(uchar8 x, uchar8 y, uchar8 z) {
     uchar8 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ short8 clamp(short8 x, short8 y, short8 z) {
     short8 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ short8 mad_hi(short8 x, short8 y, short8 z) {
     short8 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ short8 mad_sat(short8 x, short8 y, short8 z) {
     short8 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 clamp(ushort8 x, ushort8 y, ushort8 z) {
     ushort8 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 mad_hi(ushort8 x, ushort8 y, ushort8 z) {
     ushort8 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ushort8 mad_sat(ushort8 x, ushort8 y, ushort8 z) {
     ushort8 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ int8 clamp(int8 x, int8 y, int8 z) {
     int8 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ int8 mad_hi(int8 x, int8 y, int8 z) {
     int8 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ int8 mad_sat(int8 x, int8 y, int8 z) {
     int8 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uint8 clamp(uint8 x, uint8 y, uint8 z) {
     uint8 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uint8 mad_hi(uint8 x, uint8 y, uint8 z) {
     uint8 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uint8 mad_sat(uint8 x, uint8 y, uint8 z) {
     uint8 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ long8 clamp(long8 x, long8 y, long8 z) {
     long8 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ long8 mad_hi(long8 x, long8 y, long8 z) {
     long8 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ long8 mad_sat(long8 x, long8 y, long8 z) {
     long8 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 clamp(ulong8 x, ulong8 y, ulong8 z) {
     ulong8 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 mad_hi(ulong8 x, ulong8 y, ulong8 z) {
     ulong8 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ulong8 mad_sat(ulong8 x, ulong8 y, ulong8 z) {
     ulong8 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ char16 clamp(char16 x, char16 y, char16 z) {
     char16 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ char16 mad_hi(char16 x, char16 y, char16 z) {
     char16 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ char16 mad_sat(char16 x, char16 y, char16 z) {
     char16 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 clamp(uchar16 x, uchar16 y, uchar16 z) {
     uchar16 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 mad_hi(uchar16 x, uchar16 y, uchar16 z) {
     uchar16 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uchar16 mad_sat(uchar16 x, uchar16 y, uchar16 z) {
     uchar16 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ short16 clamp(short16 x, short16 y, short16 z) {
     short16 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ short16 mad_hi(short16 x, short16 y, short16 z) {
     short16 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ short16 mad_sat(short16 x, short16 y, short16 z) {
     short16 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 clamp(ushort16 x, ushort16 y, ushort16 z) {
     ushort16 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 mad_hi(ushort16 x, ushort16 y, ushort16 z) {
     ushort16 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ushort16 mad_sat(ushort16 x, ushort16 y, ushort16 z) {
     ushort16 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ int16 clamp(int16 x, int16 y, int16 z) {
     int16 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ int16 mad_hi(int16 x, int16 y, int16 z) {
     int16 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ int16 mad_sat(int16 x, int16 y, int16 z) {
     int16 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uint16 clamp(uint16 x, uint16 y, uint16 z) {
     uint16 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uint16 mad_hi(uint16 x, uint16 y, uint16 z) {
     uint16 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ uint16 mad_sat(uint16 x, uint16 y, uint16 z) {
     uint16 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ long16 clamp(long16 x, long16 y, long16 z) {
     long16 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ long16 mad_hi(long16 x, long16 y, long16 z) {
     long16 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ long16 mad_sat(long16 x, long16 y, long16 z) {
     long16 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 clamp(ulong16 x, ulong16 y, ulong16 z) {
     ulong16 r;
     r.hi = clamp(x.hi, y.hi, z.hi);
     r.lo = clamp(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 mad_hi(ulong16 x, ulong16 y, ulong16 z) {
     ulong16 r;
     r.hi = mad_hi(x.hi, y.hi, z.hi);
     r.lo = mad_hi(x.lo, y.lo, z.lo);
     return r;
  }
  __AIR_FUNC__ ulong16 mad_sat(ulong16 x, ulong16 y, ulong16 z) {
     ulong16 r;
     r.hi = mad_sat(x.hi, y.hi, z.hi);
     r.lo = mad_sat(x.lo, y.lo, z.lo);
     return r;
  }

// OpenCL 1.2 6.12.4 Common Functions generating Unified LLVM IR Sec 8 Common Functions

  __AIR_ASM__ float clamp(float x, float minval, float maxval) __asm("air.clamp.f32");

  __AIR_TGT__ float degrees(float radians);
  __AIR_TGT__ float max(float x, float y);
  __AIR_TGT__ float min(float x, float y);

  __AIR_ASM__ float mix(float x, float y, float a) __asm("air.mix.f32");

  __AIR_TGT__ float radians(float degrees);

  __AIR_FUNC__ float step(float edge, float x) {
    return (float)(x >= edge);
  }

  __AIR_FUNC__ float smoothstep(float edge0, float edge1, float x) {
    float t = clamp((x - edge0) /
                   (edge1 - edge0),
                   (float)(0), (float)(1));
    return t * t * ((float)(3) - (float)(2) * t);
  }

  __AIR_ASM__ float sign(float x) __asm("air.sign.f32");
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

  __AIR_ASM__ double clamp(double x, double minval, double maxval) __asm("air.clamp.f64");

  __AIR_TGT__ double degrees(double radians);
  __AIR_TGT__ double max(double x, double y);
  __AIR_TGT__ double min(double x, double y);

  __AIR_ASM__ double mix(double x, double y, double a) __asm("air.mix.f64");

  __AIR_TGT__ double radians(double degrees);

  __AIR_FUNC__ double step(double edge, double x) {
    return (double)(x >= edge);
  }

  __AIR_FUNC__ double smoothstep(double edge0, double edge1, double x) {
    double t = clamp((x - edge0) /
                   (edge1 - edge0),
                   (double)(0), (double)(1));
    return t * t * ((double)(3) - (double)(2) * t);
  }

  __AIR_ASM__ double sign(double x) __asm("air.sign.f64");
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float2 clamp(float2 x, float2 minval, float2 maxval) __asm("air.clamp.v2f32");
  __AIR_FUNC__ float2 clamp(float2 x, float minval, float maxval) {
    return clamp(x, (float2)(minval), (float2)(maxval));
  }

  __AIR_TGT__ float2 degrees(float2 radians);
  __AIR_TGT__ float2 max(float2 x, float2 y);
  __AIR_TGT__ float2 min(float2 x, float2 y);

  __AIR_ASM__ float2 mix(float2 x, float2 y, float2 a) __asm("air.mix.v2f32");
  __AIR_FUNC__ float2 mix(float2 x, float2 y, float a) {
    return mix(x, y, (float2)(a));
  }

  __AIR_TGT__ float2 radians(float2 degrees);

  __AIR_FUNC__ float2 step(float2 edge, float2 x) {
    return (float2)(x >= edge);
  }
  __AIR_FUNC__ float2 step(float edge, float2 x) {
    return step((float2)(edge), x);
  }

  __AIR_FUNC__ float2 smoothstep(float2 edge0, float2 edge1, float2 x) {
    float2 t = clamp((x - edge0) /
                   (edge1 - edge0),
                   (float2)(0), (float2)(1));
    return t * t * ((float2)(3) - (float2)(2) * t);
  }
  __AIR_FUNC__ float2 smoothstep(float edge0, float edge1, float2 x) {
    return smoothstep((float2)(edge0), (float2)(edge1), x);
  }

  __AIR_ASM__ float2 sign(float2 x) __asm("air.sign.v2f32");
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

  __AIR_ASM__ double2 clamp(double2 x, double2 minval, double2 maxval) __asm("air.clamp.v2f64");
  __AIR_FUNC__ double2 clamp(double2 x, double minval, double maxval) {
    return clamp(x, (double2)(minval), (double2)(maxval));
  }

  __AIR_TGT__ double2 degrees(double2 radians);
  __AIR_TGT__ double2 max(double2 x, double2 y);
  __AIR_TGT__ double2 min(double2 x, double2 y);

  __AIR_ASM__ double2 mix(double2 x, double2 y, double2 a) __asm("air.mix.v2f64");
  __AIR_FUNC__ double2 mix(double2 x, double2 y, double a) {
    return mix(x, y, (double2)(a));
  }

  __AIR_TGT__ double2 radians(double2 degrees);

  __AIR_FUNC__ double2 step(double2 edge, double2 x) {
    return (double2)(x >= edge);
  }
  __AIR_FUNC__ double2 step(double edge, double2 x) {
    return step((double2)(edge), x);
  }

  __AIR_FUNC__ double2 smoothstep(double2 edge0, double2 edge1, double2 x) {
    double2 t = clamp((x - edge0) /
                   (edge1 - edge0),
                   (double2)(0), (double2)(1));
    return t * t * ((double2)(3) - (double2)(2) * t);
  }
  __AIR_FUNC__ double2 smoothstep(double edge0, double edge1, double2 x) {
    return smoothstep((double2)(edge0), (double2)(edge1), x);
  }

  __AIR_ASM__ double2 sign(double2 x) __asm("air.sign.v2f64");
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float3 clamp(float3 x, float3 minval, float3 maxval) __asm("air.clamp.v3f32");
  __AIR_FUNC__ float3 clamp(float3 x, float minval, float maxval) {
    return clamp(x, (float3)(minval), (float3)(maxval));
  }

  __AIR_TGT__ float3 degrees(float3 radians);
  __AIR_TGT__ float3 max(float3 x, float3 y);
  __AIR_TGT__ float3 min(float3 x, float3 y);

  __AIR_ASM__ float3 mix(float3 x, float3 y, float3 a) __asm("air.mix.v3f32");
  __AIR_FUNC__ float3 mix(float3 x, float3 y, float a) {
    return mix(x, y, (float3)(a));
  }

  __AIR_TGT__ float3 radians(float3 degrees);

  __AIR_FUNC__ float3 step(float3 edge, float3 x) {
    return (float3)(x >= edge);
  }
  __AIR_FUNC__ float3 step(float edge, float3 x) {
    return step((float3)(edge), x);
  }

  __AIR_FUNC__ float3 smoothstep(float3 edge0, float3 edge1, float3 x) {
    float3 t = clamp((x - edge0) /
                   (edge1 - edge0),
                   (float3)(0), (float3)(1));
    return t * t * ((float3)(3) - (float3)(2) * t);
  }
  __AIR_FUNC__ float3 smoothstep(float edge0, float edge1, float3 x) {
    return smoothstep((float3)(edge0), (float3)(edge1), x);
  }

  __AIR_ASM__ float3 sign(float3 x) __asm("air.sign.v3f32");
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

  __AIR_ASM__ double3 clamp(double3 x, double3 minval, double3 maxval) __asm("air.clamp.v3f64");
  __AIR_FUNC__ double3 clamp(double3 x, double minval, double maxval) {
    return clamp(x, (double3)(minval), (double3)(maxval));
  }

  __AIR_TGT__ double3 degrees(double3 radians);
  __AIR_TGT__ double3 max(double3 x, double3 y);
  __AIR_TGT__ double3 min(double3 x, double3 y);

  __AIR_ASM__ double3 mix(double3 x, double3 y, double3 a) __asm("air.mix.v3f64");
  __AIR_FUNC__ double3 mix(double3 x, double3 y, double a) {
    return mix(x, y, (double3)(a));
  }

  __AIR_TGT__ double3 radians(double3 degrees);

  __AIR_FUNC__ double3 step(double3 edge, double3 x) {
    return (double3)(x >= edge);
  }
  __AIR_FUNC__ double3 step(double edge, double3 x) {
    return step((double3)(edge), x);
  }

  __AIR_FUNC__ double3 smoothstep(double3 edge0, double3 edge1, double3 x) {
    double3 t = clamp((x - edge0) /
                   (edge1 - edge0),
                   (double3)(0), (double3)(1));
    return t * t * ((double3)(3) - (double3)(2) * t);
  }
  __AIR_FUNC__ double3 smoothstep(double edge0, double edge1, double3 x) {
    return smoothstep((double3)(edge0), (double3)(edge1), x);
  }

  __AIR_ASM__ double3 sign(double3 x) __asm("air.sign.v3f64");
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float4 clamp(float4 x, float4 minval, float4 maxval) __asm("air.clamp.v4f32");
  __AIR_FUNC__ float4 clamp(float4 x, float minval, float maxval) {
    return clamp(x, (float4)(minval), (float4)(maxval));
  }

  __AIR_TGT__ float4 degrees(float4 radians);
  __AIR_TGT__ float4 max(float4 x, float4 y);
  __AIR_TGT__ float4 min(float4 x, float4 y);

  __AIR_ASM__ float4 mix(float4 x, float4 y, float4 a) __asm("air.mix.v4f32");
  __AIR_FUNC__ float4 mix(float4 x, float4 y, float a) {
    return mix(x, y, (float4)(a));
  }

  __AIR_TGT__ float4 radians(float4 degrees);

  __AIR_FUNC__ float4 step(float4 edge, float4 x) {
    return (float4)(x >= edge);
  }
  __AIR_FUNC__ float4 step(float edge, float4 x) {
    return step((float4)(edge), x);
  }

  __AIR_FUNC__ float4 smoothstep(float4 edge0, float4 edge1, float4 x) {
    float4 t = clamp((x - edge0) /
                   (edge1 - edge0),
                   (float4)(0), (float4)(1));
    return t * t * ((float4)(3) - (float4)(2) * t);
  }
  __AIR_FUNC__ float4 smoothstep(float edge0, float edge1, float4 x) {
    return smoothstep((float4)(edge0), (float4)(edge1), x);
  }

  __AIR_ASM__ float4 sign(float4 x) __asm("air.sign.v4f32");
#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

  __AIR_ASM__ double4 clamp(double4 x, double4 minval, double4 maxval) __asm("air.clamp.v4f64");
  __AIR_FUNC__ double4 clamp(double4 x, double minval, double maxval) {
    return clamp(x, (double4)(minval), (double4)(maxval));
  }

  __AIR_TGT__ double4 degrees(double4 radians);
  __AIR_TGT__ double4 max(double4 x, double4 y);
  __AIR_TGT__ double4 min(double4 x, double4 y);

  __AIR_ASM__ double4 mix(double4 x, double4 y, double4 a) __asm("air.mix.v4f64");
  __AIR_FUNC__ double4 mix(double4 x, double4 y, double a) {
    return mix(x, y, (double4)(a));
  }

  __AIR_TGT__ double4 radians(double4 degrees);

  __AIR_FUNC__ double4 step(double4 edge, double4 x) {
    return (double4)(x >= edge);
  }
  __AIR_FUNC__ double4 step(double edge, double4 x) {
    return step((double4)(edge), x);
  }

  __AIR_FUNC__ double4 smoothstep(double4 edge0, double4 edge1, double4 x) {
    double4 t = clamp((x - edge0) /
                   (edge1 - edge0),
                   (double4)(0), (double4)(1));
    return t * t * ((double4)(3) - (double4)(2) * t);
  }
  __AIR_FUNC__ double4 smoothstep(double edge0, double edge1, double4 x) {
    return smoothstep((double4)(edge0), (double4)(edge1), x);
  }

  __AIR_ASM__ double4 sign(double4 x) __asm("air.sign.v4f64");
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

// OpenCL 1.2 6.12.14.2 Built-in Image Read Functions generating Unified LLVM IR



  __AIR_INTERNAL__ float4 _air_sample_texture_1d_f1(image1d_t tex, sampler_t smp, float coord, bool offset_en, int offset, bool lod) __asm("air.sample_texture_1d.v4f32");
  __AIR_INTERNAL__ float4 _air_sample_texture_1d_f1(image1d_t tex, sampler_t smp, int coord, bool lod) __asm("air.sample_texture_1d.intcoord.v4f32");

  __AIR_FUNC__ float4 read_imagef(image1d_t image, sampler_t sampler, float coord) {
    return _air_sample_texture_1d_f1(image, sampler, coord, false, (int) 0, false);
  }  

  __AIR_FUNC__ float4 read_imagef(image1d_t image, sampler_t sampler, int coord) {
    return _air_sample_texture_1d_f1(image, sampler, coord, false);
  }

  __AIR_INTERNAL__ float4 _air_sample_texture_1d_array_f1(image1d_array_t tex, sampler_t smp, float coord, int array, bool offset_en, int offset, bool lod) __asm("air.sample_texture_1d_array.v4f32");
  __AIR_INTERNAL__ float4 _air_sample_texture_1d_array_f1(image1d_array_t tex, sampler_t smp, int coord, int array, bool lod) __asm("air.sample_texture_1d_array.intcoord.v4f32");

  __AIR_FUNC__ float4 read_imagef(image1d_array_t image, sampler_t sampler, float2 coord) {
    return _air_sample_texture_1d_array_v4f32(image, sampler, coord.x, (int) coord.y, false, (int) 0, false);
  }

  __AIR_FUNC__ float4 read_imagef(image1d_array_t image, sampler_t sampler, int2 coord) {
      return _air_sample_texture_1d_array_v4f32(image, sampler, coord.x, (int) coord.y, false);
  }

  __AIR_INTERNAL__ int4 _air_sample_texture_1d_s1(image1d_t tex, sampler_t smp, float coord, bool offset_en, int offset, bool lod) __asm("air.sample_texture_1d.s.v4i32");
  __AIR_INTERNAL__ int4 _air_sample_texture_1d_s1(image1d_t tex, sampler_t smp, int coord, bool lod) __asm("air.sample_texture_1d.intcoord.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image1d_t image, sampler_t sampler, float coord) {
    return _air_sample_texture_1d_s1(image, sampler, coord, false, (int) 0, false);
  }  

  __AIR_FUNC__ int4 read_imagei(image1d_t image, sampler_t sampler, int coord) {
    return _air_sample_texture_1d_s1(image, sampler, coord, false);
  }

  __AIR_INTERNAL__ int4 _air_sample_texture_1d_array_s1(image1d_array_t tex, sampler_t smp, float coord, int array, bool offset_en, int offset, bool lod) __asm("air.sample_texture_1d_array.s.v4i32");
  __AIR_INTERNAL__ int4 _air_sample_texture_1d_array_s1(image1d_array_t tex, sampler_t smp, int coord, int array, bool lod) __asm("air.sample_texture_1d_array.intcoord.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image1d_array_t image, sampler_t sampler, float2 coord) {
    return _air_sample_texture_1d_array_v4i32(image, sampler, coord.x, (int) coord.y, false, (int) 0, false);
  }

  __AIR_FUNC__ int4 read_imagei(image1d_array_t image, sampler_t sampler, int2 coord) {
      return _air_sample_texture_1d_array_v4i32(image, sampler, coord.x, (int) coord.y, false);
  }

  __AIR_INTERNAL__ uint4 _air_sample_texture_1d_u1(image1d_t tex, sampler_t smp, float coord, bool offset_en, int offset, bool lod) __asm("air.sample_texture_1d.u.v4i32");
  __AIR_INTERNAL__ uint4 _air_sample_texture_1d_u1(image1d_t tex, sampler_t smp, int coord, bool lod) __asm("air.sample_texture_1d.intcoord.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image1d_t image, sampler_t sampler, float coord) {
    return _air_sample_texture_1d_u1(image, sampler, coord, false, (int) 0, false);
  }  

  __AIR_FUNC__ uint4 read_imageui(image1d_t image, sampler_t sampler, int coord) {
    return _air_sample_texture_1d_u1(image, sampler, coord, false);
  }

  __AIR_INTERNAL__ uint4 _air_sample_texture_1d_array_u1(image1d_array_t tex, sampler_t smp, float coord, int array, bool offset_en, int offset, bool lod) __asm("air.sample_texture_1d_array.u.v4i32");
  __AIR_INTERNAL__ uint4 _air_sample_texture_1d_array_u1(image1d_array_t tex, sampler_t smp, int coord, int array, bool lod) __asm("air.sample_texture_1d_array.intcoord.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image1d_array_t image, sampler_t sampler, float2 coord) {
    return _air_sample_texture_1d_array_v4i32(image, sampler, coord.x, (int) coord.y, false, (int) 0, false);
  }

  __AIR_FUNC__ uint4 read_imageui(image1d_array_t image, sampler_t sampler, int2 coord) {
      return _air_sample_texture_1d_array_v4i32(image, sampler, coord.x, (int) coord.y, false);
  }


  __AIR_INTERNAL__ float4 _air_sample_texture_2d_f2(image2d_t tex, sampler_t smp, float2 coord, bool offset_en, int2 offset, bool lod) __asm("air.sample_texture_2d.v4f32");
  __AIR_INTERNAL__ float4 _air_sample_texture_2d_f2(image2d_t tex, sampler_t smp, int2 coord, bool lod) __asm("air.sample_texture_2d.intcoord.v4f32");

  __AIR_FUNC__ float4 read_imagef(image2d_t image, sampler_t sampler, float2 coord) {
    return _air_sample_texture_2d_f2(image, sampler, coord, false, (int2) 0, false);
  }  

  __AIR_FUNC__ float4 read_imagef(image2d_t image, sampler_t sampler, int2 coord) {
    return _air_sample_texture_2d_f2(image, sampler, coord, false);
  }

  __AIR_INTERNAL__ float4 _air_sample_texture_2d_array_f2(image2d_array_t tex, sampler_t smp, float2 coord, int array, bool offset_en, int2 offset, bool lod) __asm("air.sample_texture_2d_array.v4f32");
  __AIR_INTERNAL__ float4 _air_sample_texture_2d_array_f2(image2d_array_t tex, sampler_t smp, int2 coord, int array, bool lod) __asm("air.sample_texture_2d_array.intcoord.v4f32");

  __AIR_FUNC__ float4 read_imagef(image2d_array_t image, sampler_t sampler, float4 coord) {
    return _air_sample_texture_2d_array_v4f32(image, sampler, coord.xy, (int) coord.z, false, (int2) 0, false);
  }

  __AIR_FUNC__ float4 read_imagef(image2d_array_t image, sampler_t sampler, int4 coord) {
      return _air_sample_texture_2d_array_v4f32(image, sampler, coord.xy, (int) coord.z, false);
  }

  __AIR_INTERNAL__ int4 _air_sample_texture_2d_s2(image2d_t tex, sampler_t smp, float2 coord, bool offset_en, int2 offset, bool lod) __asm("air.sample_texture_2d.s.v4i32");
  __AIR_INTERNAL__ int4 _air_sample_texture_2d_s2(image2d_t tex, sampler_t smp, int2 coord, bool lod) __asm("air.sample_texture_2d.intcoord.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image2d_t image, sampler_t sampler, float2 coord) {
    return _air_sample_texture_2d_s2(image, sampler, coord, false, (int2) 0, false);
  }  

  __AIR_FUNC__ int4 read_imagei(image2d_t image, sampler_t sampler, int2 coord) {
    return _air_sample_texture_2d_s2(image, sampler, coord, false);
  }

  __AIR_INTERNAL__ int4 _air_sample_texture_2d_array_s2(image2d_array_t tex, sampler_t smp, float2 coord, int array, bool offset_en, int2 offset, bool lod) __asm("air.sample_texture_2d_array.s.v4i32");
  __AIR_INTERNAL__ int4 _air_sample_texture_2d_array_s2(image2d_array_t tex, sampler_t smp, int2 coord, int array, bool lod) __asm("air.sample_texture_2d_array.intcoord.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image2d_array_t image, sampler_t sampler, float4 coord) {
    return _air_sample_texture_2d_array_v4i32(image, sampler, coord.xy, (int) coord.z, false, (int2) 0, false);
  }

  __AIR_FUNC__ int4 read_imagei(image2d_array_t image, sampler_t sampler, int4 coord) {
      return _air_sample_texture_2d_array_v4i32(image, sampler, coord.xy, (int) coord.z, false);
  }

  __AIR_INTERNAL__ uint4 _air_sample_texture_2d_u2(image2d_t tex, sampler_t smp, float2 coord, bool offset_en, int2 offset, bool lod) __asm("air.sample_texture_2d.u.v4i32");
  __AIR_INTERNAL__ uint4 _air_sample_texture_2d_u2(image2d_t tex, sampler_t smp, int2 coord, bool lod) __asm("air.sample_texture_2d.intcoord.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image2d_t image, sampler_t sampler, float2 coord) {
    return _air_sample_texture_2d_u2(image, sampler, coord, false, (int2) 0, false);
  }  

  __AIR_FUNC__ uint4 read_imageui(image2d_t image, sampler_t sampler, int2 coord) {
    return _air_sample_texture_2d_u2(image, sampler, coord, false);
  }

  __AIR_INTERNAL__ uint4 _air_sample_texture_2d_array_u2(image2d_array_t tex, sampler_t smp, float2 coord, int array, bool offset_en, int2 offset, bool lod) __asm("air.sample_texture_2d_array.u.v4i32");
  __AIR_INTERNAL__ uint4 _air_sample_texture_2d_array_u2(image2d_array_t tex, sampler_t smp, int2 coord, int array, bool lod) __asm("air.sample_texture_2d_array.intcoord.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image2d_array_t image, sampler_t sampler, float4 coord) {
    return _air_sample_texture_2d_array_v4i32(image, sampler, coord.xy, (int) coord.z, false, (int2) 0, false);
  }

  __AIR_FUNC__ uint4 read_imageui(image2d_array_t image, sampler_t sampler, int4 coord) {
      return _air_sample_texture_2d_array_v4i32(image, sampler, coord.xy, (int) coord.z, false);
  }


  __AIR_INTERNAL__ float4 _air_sample_texture_3d_f3(image3d_t tex, sampler_t smp, float3 coord, bool offset_en, int3 offset, bool lod) __asm("air.sample_texture_3d.v4f32");
  __AIR_INTERNAL__ float4 _air_sample_texture_3d_f3(image3d_t tex, sampler_t smp, int3 coord, bool lod) __asm("air.sample_texture_3d.intcoord.v4f32");

  __AIR_FUNC__ float4 read_imagef(image3d_t image, sampler_t sampler, float4 coord) {
    return _air_sample_texture_3d_f3(image, sampler, coord.xyz, false, (int3) 0, false);
  }  

  __AIR_FUNC__ float4 read_imagef(image3d_t image, sampler_t sampler, int4 coord) {
    return _air_sample_texture_3d_f3(image, sampler, coord.xyz, false);
  }


  __AIR_INTERNAL__ int4 _air_sample_texture_3d_s3(image3d_t tex, sampler_t smp, float3 coord, bool offset_en, int3 offset, bool lod) __asm("air.sample_texture_3d.s.v4i32");
  __AIR_INTERNAL__ int4 _air_sample_texture_3d_s3(image3d_t tex, sampler_t smp, int3 coord, bool lod) __asm("air.sample_texture_3d.intcoord.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image3d_t image, sampler_t sampler, float4 coord) {
    return _air_sample_texture_3d_s3(image, sampler, coord.xyz, false, (int3) 0, false);
  }  

  __AIR_FUNC__ int4 read_imagei(image3d_t image, sampler_t sampler, int4 coord) {
    return _air_sample_texture_3d_s3(image, sampler, coord.xyz, false);
  }


  __AIR_INTERNAL__ uint4 _air_sample_texture_3d_u3(image3d_t tex, sampler_t smp, float3 coord, bool offset_en, int3 offset, bool lod) __asm("air.sample_texture_3d.u.v4i32");
  __AIR_INTERNAL__ uint4 _air_sample_texture_3d_u3(image3d_t tex, sampler_t smp, int3 coord, bool lod) __asm("air.sample_texture_3d.intcoord.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image3d_t image, sampler_t sampler, float4 coord) {
    return _air_sample_texture_3d_u3(image, sampler, coord.xyz, false, (int3) 0, false);
  }  

  __AIR_FUNC__ uint4 read_imageui(image3d_t image, sampler_t sampler, int4 coord) {
    return _air_sample_texture_3d_u3(image, sampler, coord.xyz, false);
  }


// OpenCL 1.2 6.12.14.3 Built-in Image Sampler-less Read Functions generating Unified LLVM IR



  __AIR_INTERNAL__ float4 _air_read_texture_1d_f1(image1d_t tex, int coord, bool lod) __asm("air.read_texture_1d.v4f32");

  __AIR_FUNC__ float4 read_imagef(image1d_t image, int coord) {
      return _air_read_texture_1d_f1(image, coord, false);
  }

  __AIR_INTERNAL__ float4 _air_read_texture_1d_array_f1(image1d_array_t tex, int coord, int array, bool lod) __asm("air.read_texture_1d_array.v4f32");

  __AIR_FUNC__ float4 read_imagef(image1d_array_t image, int2 coord) {
      return _air_read_texture_1d_array_f1(image, coord.x, (int) coord.y, false);
  }

  __AIR_INTERNAL__ float4 _air_read_texture_1d_buffer_f1(image1d_buffer_t tex, int coord) __asm("air.read_texture_1d_buffer.v4f32");

  __AIR_FUNC__ float4 read_imagef(image1d_buffer_t image, int coord) {
      return _air_read_texture_1d_buffer_f1(image, coord);
  }

  __AIR_INTERNAL__ int4 _air_read_texture_1d_s1(image1d_t tex, int coord, bool lod) __asm("air.read_texture_1d.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image1d_t image, int coord) {
      return _air_read_texture_1d_s1(image, coord, false);
  }

  __AIR_INTERNAL__ int4 _air_read_texture_1d_array_s1(image1d_array_t tex, int coord, int array, bool lod) __asm("air.read_texture_1d_array.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image1d_array_t image, int2 coord) {
      return _air_read_texture_1d_array_s1(image, coord.x, (int) coord.y, false);
  }

  __AIR_INTERNAL__ int4 _air_read_texture_1d_buffer_s1(image1d_buffer_t tex, int coord) __asm("air.read_texture_1d_buffer.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image1d_buffer_t image, int coord) {
      return _air_read_texture_1d_buffer_s1(image, coord);
  }

  __AIR_INTERNAL__ uint4 _air_read_texture_1d_u1(image1d_t tex, int coord, bool lod) __asm("air.read_texture_1d.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image1d_t image, int coord) {
      return _air_read_texture_1d_u1(image, coord, false);
  }

  __AIR_INTERNAL__ uint4 _air_read_texture_1d_array_u1(image1d_array_t tex, int coord, int array, bool lod) __asm("air.read_texture_1d_array.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image1d_array_t image, int2 coord) {
      return _air_read_texture_1d_array_u1(image, coord.x, (int) coord.y, false);
  }

  __AIR_INTERNAL__ uint4 _air_read_texture_1d_buffer_u1(image1d_buffer_t tex, int coord) __asm("air.read_texture_1d_buffer.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image1d_buffer_t image, int coord) {
      return _air_read_texture_1d_buffer_u1(image, coord);
  }


  __AIR_INTERNAL__ float4 _air_read_texture_2d_f2(image2d_t tex, int2 coord, bool lod) __asm("air.read_texture_2d.v4f32");

  __AIR_FUNC__ float4 read_imagef(image2d_t image, int2 coord) {
      return _air_read_texture_2d_f2(image, coord, false);
  }

  __AIR_INTERNAL__ float4 _air_read_texture_2d_array_f2(image2d_array_t tex, int2 coord, int array, bool lod) __asm("air.read_texture_2d_array.v4f32");

  __AIR_FUNC__ float4 read_imagef(image2d_array_t image, int4 coord) {
      return _air_read_texture_2d_array_f2(image, coord.xy, (int) coord.z, false);
  }


  __AIR_INTERNAL__ int4 _air_read_texture_2d_s2(image2d_t tex, int2 coord, bool lod) __asm("air.read_texture_2d.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image2d_t image, int2 coord) {
      return _air_read_texture_2d_s2(image, coord, false);
  }

  __AIR_INTERNAL__ int4 _air_read_texture_2d_array_s2(image2d_array_t tex, int2 coord, int array, bool lod) __asm("air.read_texture_2d_array.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image2d_array_t image, int4 coord) {
      return _air_read_texture_2d_array_s2(image, coord.xy, (int) coord.z, false);
  }


  __AIR_INTERNAL__ uint4 _air_read_texture_2d_u2(image2d_t tex, int2 coord, bool lod) __asm("air.read_texture_2d.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image2d_t image, int2 coord) {
      return _air_read_texture_2d_u2(image, coord, false);
  }

  __AIR_INTERNAL__ uint4 _air_read_texture_2d_array_u2(image2d_array_t tex, int2 coord, int array, bool lod) __asm("air.read_texture_2d_array.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image2d_array_t image, int4 coord) {
      return _air_read_texture_2d_array_u2(image, coord.xy, (int) coord.z, false);
  }



  __AIR_INTERNAL__ float4 _air_read_texture_3d_f3(image3d_t tex, int3 coord, bool lod) __asm("air.read_texture_3d.v4f32");

  __AIR_FUNC__ float4 read_imagef(image3d_t image, int4 coord) {
      return _air_read_texture_3d_f3(image, coord.xyz, false);
  }



  __AIR_INTERNAL__ int4 _air_read_texture_3d_s3(image3d_t tex, int3 coord, bool lod) __asm("air.read_texture_3d.s.v4i32");

  __AIR_FUNC__ int4 read_imagei(image3d_t image, int4 coord) {
      return _air_read_texture_3d_s3(image, coord.xyz, false);
  }



  __AIR_INTERNAL__ uint4 _air_read_texture_3d_u3(image3d_t tex, int3 coord, bool lod) __asm("air.read_texture_3d.u.v4i32");

  __AIR_FUNC__ uint4 read_imageui(image3d_t image, int4 coord) {
      return _air_read_texture_3d_u3(image, coord.xyz, false);
  }



// OpenCL 1.2 6.12.14.4 Built-in Image Write Functions generating Unified LLVM IR



  __AIR_INTERNAL__ void _air_write_texture_1d_f1(image1d_t tex, int coord, float4 color, bool lod) __asm("air.write_texture_1d.v4f32");

  __AIR_FUNC__ void write_imagef(image1d_t image, int coord, float4 color) {
      return _air_write_texture_1d_f1(image, coord, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_1d_array_f1(image1d_array_t tex, int coord, int array, float4 color, bool lod) __asm("air.write_texture_1d_array.v4f32");

  __AIR_FUNC__ void write_imagef(image1d_array_t image, int2 coord, float4 color) {
      return _air_write_texture_1d_array_f1(image, coord.x, (int) coord.y, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_1d_buffer_f1(image1d_buffer_t tex, int coord, float4 color) __asm("air.read_texture_1d_buffer.v4f32");

  __AIR_FUNC__ void write_imagef(image1d_buffer_t image, int coord, float4 color) {
      return _air_write_texture_1d_buffer_f1(image, coord, color);
  }

  __AIR_INTERNAL__ void _air_write_texture_1d_s1(image1d_t tex, int coord, int4 color, bool lod) __asm("air.write_texture_1d.s.v4i32");

  __AIR_FUNC__ void write_imagei(image1d_t image, int coord, int4 color) {
      return _air_write_texture_1d_s1(image, coord, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_1d_array_s1(image1d_array_t tex, int coord, int array, int4 color, bool lod) __asm("air.write_texture_1d_array.s.v4i32");

  __AIR_FUNC__ void write_imagei(image1d_array_t image, int2 coord, int4 color) {
      return _air_write_texture_1d_array_s1(image, coord.x, (int) coord.y, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_1d_buffer_s1(image1d_buffer_t tex, int coord, int4 color) __asm("air.read_texture_1d_buffer.s.v4i32");

  __AIR_FUNC__ void write_imagei(image1d_buffer_t image, int coord, int4 color) {
      return _air_write_texture_1d_buffer_s1(image, coord, color);
  }

  __AIR_INTERNAL__ void _air_write_texture_1d_u1(image1d_t tex, int coord, uint4 color, bool lod) __asm("air.write_texture_1d.u.v4i32");

  __AIR_FUNC__ void write_imageui(image1d_t image, int coord, uint4 color) {
      return _air_write_texture_1d_u1(image, coord, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_1d_array_u1(image1d_array_t tex, int coord, int array, uint4 color, bool lod) __asm("air.write_texture_1d_array.u.v4i32");

  __AIR_FUNC__ void write_imageui(image1d_array_t image, int2 coord, uint4 color) {
      return _air_write_texture_1d_array_u1(image, coord.x, (int) coord.y, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_1d_buffer_u1(image1d_buffer_t tex, int coord, uint4 color) __asm("air.read_texture_1d_buffer.u.v4i32");

  __AIR_FUNC__ void write_imageui(image1d_buffer_t image, int coord, uint4 color) {
      return _air_write_texture_1d_buffer_u1(image, coord, color);
  }


  __AIR_INTERNAL__ void _air_write_texture_2d_f2(image2d_t tex, int2 coord, float4 color, bool lod) __asm("air.write_texture_2d.v4f32");

  __AIR_FUNC__ void write_imagef(image2d_t image, int2 coord, float4 color) {
      return _air_write_texture_2d_f2(image, coord, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_2d_array_f2(image2d_array_t tex, int2 coord, int array, float4 color, bool lod) __asm("air.write_texture_2d_array.v4f32");

  __AIR_FUNC__ void write_imagef(image2d_array_t image, int4 coord, float4 color) {
      return _air_write_texture_2d_array_f2(image, coord.xy, (int) coord.z, color, false);
  }


  __AIR_INTERNAL__ void _air_write_texture_2d_s2(image2d_t tex, int2 coord, int4 color, bool lod) __asm("air.write_texture_2d.s.v4i32");

  __AIR_FUNC__ void write_imagei(image2d_t image, int2 coord, int4 color) {
      return _air_write_texture_2d_s2(image, coord, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_2d_array_s2(image2d_array_t tex, int2 coord, int array, int4 color, bool lod) __asm("air.write_texture_2d_array.s.v4i32");

  __AIR_FUNC__ void write_imagei(image2d_array_t image, int4 coord, int4 color) {
      return _air_write_texture_2d_array_s2(image, coord.xy, (int) coord.z, color, false);
  }


  __AIR_INTERNAL__ void _air_write_texture_2d_u2(image2d_t tex, int2 coord, uint4 color, bool lod) __asm("air.write_texture_2d.u.v4i32");

  __AIR_FUNC__ void write_imageui(image2d_t image, int2 coord, uint4 color) {
      return _air_write_texture_2d_u2(image, coord, color, false);
  }

  __AIR_INTERNAL__ void _air_write_texture_2d_array_u2(image2d_array_t tex, int2 coord, int array, uint4 color, bool lod) __asm("air.write_texture_2d_array.u.v4i32");

  __AIR_FUNC__ void write_imageui(image2d_array_t image, int4 coord, uint4 color) {
      return _air_write_texture_2d_array_u2(image, coord.xy, (int) coord.z, color, false);
  }



  __AIR_INTERNAL__ void _air_write_texture_3d_f3(image3d_t tex, int3 coord, float4 color, bool lod) __asm("air.write_texture_3d.v4f32");

  __AIR_FUNC__ void write_imagef(image3d_t image, int4 coord, float4 color) {
      return _air_write_texture_3d_f3(image, coord.xyz, color, false);
  }



  __AIR_INTERNAL__ void _air_write_texture_3d_s3(image3d_t tex, int3 coord, int4 color, bool lod) __asm("air.write_texture_3d.s.v4i32");

  __AIR_FUNC__ void write_imagei(image3d_t image, int4 coord, int4 color) {
      return _air_write_texture_3d_s3(image, coord.xyz, color, false);
  }



  __AIR_INTERNAL__ void _air_write_texture_3d_u3(image3d_t tex, int3 coord, uint4 color, bool lod) __asm("air.write_texture_3d.u.v4i32");

  __AIR_FUNC__ void write_imageui(image3d_t image, int4 coord, uint4 color) {
      return _air_write_texture_3d_u3(image, coord.xyz, color, false);
  }



// OpenCL 1.2 6.12.14.5 Built-in Image Query Functions generating Unified LLVM IR


  __AIR_INTERNAL__ int get_width_texture_1d(image1d_t tex, int lod) __asm("air.get_width_texture_1d");
  __AIR_FUNC__ int get_width_texture(image1d_t image) {
    get_image_width_1d(image, 0);
  }

  __AIR_INTERNAL__ int get_width_texture_1d_buffer(image1d_buffer_t tex, int lod) __asm("air.get_width_texture_1d_buffer");
  __AIR_FUNC__ int get_width_texture(image1d_buffer_t image) {
    get_image_width_1d_buffer(image, 0);
  }

  __AIR_INTERNAL__ int get_width_texture_1d_array(image1d_array_t tex, int lod) __asm("air.get_width_texture_1d_array");
  __AIR_FUNC__ int get_width_texture(image1d_array_t image) {
    get_image_width_1d_array(image, 0);
  }

  __AIR_INTERNAL__ int get_width_texture_2d(image2d_t tex, int lod) __asm("air.get_width_texture_2d");
  __AIR_FUNC__ int get_width_texture(image2d_t image) {
    get_image_width_2d(image, 0);
  }

  __AIR_INTERNAL__ int get_height_texture_2d(image2d_t tex, int lod) __asm("air.get_height_texture_2d");

  __AIR_FUNC__ int get_height_texture(image2d_t image) {
    get_image_height_2d(image, 0);
  }

  __AIR_INTERNAL__ int get_width_texture_2d_array(image2d_array_t tex, int lod) __asm("air.get_width_texture_2d_array");
  __AIR_FUNC__ int get_width_texture(image2d_array_t image) {
    get_image_width_2d_array(image, 0);
  }

  __AIR_INTERNAL__ int get_height_texture_2d_array(image2d_array_t tex, int lod) __asm("air.get_height_texture_2d_array");

  __AIR_FUNC__ int get_height_texture(image2d_array_t image) {
    get_image_height_2d_array(image, 0);
  }

  __AIR_INTERNAL__ int get_width_texture_3d(image3d_t tex, int lod) __asm("air.get_width_texture_3d");
  __AIR_FUNC__ int get_width_texture(image3d_t image) {
    get_image_width_3d(image, 0);
  }

  __AIR_INTERNAL__ int get_height_texture_3d(image3d_t tex, int lod) __asm("air.get_height_texture_3d");

  __AIR_FUNC__ int get_height_texture(image3d_t image) {
    get_image_height_3d(image, 0);
  }

  __AIR_INTERNAL__ int get_depth_texture_3d(image3d_t tex, int lod) __asm("air.get_depth_texture_3d");

  __AIR_FUNC__ int get_depth_texture(image3d_t image) {
    get_image_depth_3d(image, 0);
  }

  __AIR_FUNC__ int2 get_image_dim(image2d_t image) {
    return (int2)(get_image_width(image), get_image_height(image));
  }
  __AIR_FUNC__ int2 get_image_dim(image2d_array_t image) {
    return (int2)(get_image_width(image), get_image_height(image));
  }

  __AIR_FUNC__ int4 get_image_dim(image3d_t image) {
    return (int4)(get_image_width(image), get_image_height(image), get_image_depth(image), 0);
  }

  __AIR_ASM__ size_t get_image_array_size(image1d_array_t image) __asm("air.get_array_size_texture_1d_array");
  __AIR_ASM__ size_t get_image_array_size(image2d_array_t image) __asm("air.get_array_size_texture_2d_array");

    __AIR_ASM__ int get_image_channel_data_type(image1d_t image) __asm("air.get_channel_data_type_texture_1d");
    __AIR_ASM__ int get_image_channel_data_type(image1d_buffer_t image) __asm("air.get_channel_data_type_texture_1d_buffer");
    __AIR_ASM__ int get_image_channel_data_type(image1d_array_t image) __asm("air.get_channel_data_type_texture_1d_array");
    __AIR_ASM__ int get_image_channel_data_type(image2d_t image) __asm("air.get_channel_data_type_texture_2d");
    __AIR_ASM__ int get_image_channel_data_type(image2d_array_t image) __asm("air.get_channel_data_type_texture_2d_array");
    __AIR_ASM__ int get_image_channel_data_type(image3d_t image) __asm("air.get_channel_data_type_texture_3d");

    __AIR_ASM__ int get_image_channel_order(image1d_t image) __asm("air.get_channel_order_texture_1d");
    __AIR_ASM__ int get_image_channel_order(image1d_buffer_t image) __asm("air.get_channel_order_texture_1d_buffer");
    __AIR_ASM__ int get_image_channel_order(image1d_array_t image) __asm("air.get_channel_order_texture_1d_array");
    __AIR_ASM__ int get_image_channel_order(image2d_t image) __asm("air.get_channel_order_texture_2d");
    __AIR_ASM__ int get_image_channel_order(image2d_array_t image) __asm("air.get_channel_order_texture_2d_array");
    __AIR_ASM__ int get_image_channel_order(image3d_t image) __asm("air.get_channel_order_texture_3d");

// OpenCL 1.2 6.12.5 Geometric Functions generating Unified LLVM IR

  __AIR_FUNC__ float3 cross(float3 p0, float3 p1) {
    return (float3)((p0.y * p1.z) - (p1.y * p0.z),
                   (p0.z * p1.x) - (p1.z * p0.x),
                   (p0.x * p1.y) - (p1.x * p0.y));
  }

  __AIR_FUNC__ float4 cross(float4 p0, float4 p1) {
    return (float4)((p0.y * p1.z) - (p1.y * p0.z),
                   (p0.z * p1.x) - (p1.z * p0.x),
                   (p0.x * p1.y) - (p1.x * p0.y), 0.0);
  }

#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_FUNC__ double3 cross(double3 p0, double3 p1) {
    return (double3)((p0.y * p1.z) - (p1.y * p0.z),
                   (p0.z * p1.x) - (p1.z * p0.x),
                   (p0.x * p1.y) - (p1.x * p0.y));
  }

  __AIR_FUNC__ double4 cross(double4 p0, double4 p1) {
    return (double4)((p0.y * p1.z) - (p1.y * p0.z),
                   (p0.z * p1.x) - (p1.z * p0.x),
                   (p0.x * p1.y) - (p1.x * p0.y), 0.0);
  }
#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))


  __AIR_ASM__ float dot(float p0, float p1) __asm("air.dot.f32");
    
  __AIR_FUNC__ float length(float p) {
    return sqrt(dot(p, p));
  }
    
  __AIR_FUNC__ float distance(float p0, float p1) {
    return length(p0 - p1);
  }
    
  __AIR_FUNC__ float normalize(float p) {
    return p / length(p);
  }

  __AIR_FUNC__ float fast_length(float p) {
    return half_sqrt(dot(p, p));
  }

  __AIR_FUNC__ float fast_distance(float p0, float p1) {
    return fast_length(p0 - p1);
  }

  __AIR_FUNC__ float fast_normalize(float p) {
    return p / fast_length(p);
  }


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_ASM__ double dot(double p0, double p1) __asm("air.dot.f64");
    
  __AIR_FUNC__ double length(double p) {
    return sqrt(dot(p, p));
  }
    
  __AIR_FUNC__ double distance(double p0, double p1) {
    return length(p0 - p1);
  }
    
  __AIR_FUNC__ double normalize(double p) {
    return p / length(p);
  }


#endif // (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float dot(float2 p0, float2 p1) __asm("air.dot.v2f32");
    
  __AIR_FUNC__ float length(float2 p) {
    return sqrt(dot(p, p));
  }
    
  __AIR_FUNC__ float distance(float2 p0, float2 p1) {
    return length(p0 - p1);
  }
    
  __AIR_FUNC__ float2 normalize(float2 p) {
    return p / length(p);
  }

  __AIR_FUNC__ float fast_length(float2 p) {
    return half_sqrt(dot(p, p));
  }

  __AIR_FUNC__ float fast_distance(float2 p0, float2 p1) {
    return fast_length(p0 - p1);
  }

  __AIR_FUNC__ float2 fast_normalize(float2 p) {
    return p / fast_length(p);
  }


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_ASM__ double dot(double2 p0, double2 p1) __asm("air.dot.v2f64");
    
  __AIR_FUNC__ double length(double2 p) {
    return sqrt(dot(p, p));
  }
    
  __AIR_FUNC__ double distance(double2 p0, double2 p1) {
    return length(p0 - p1);
  }
    
  __AIR_FUNC__ double2 normalize(double2 p) {
    return p / length(p);
  }


#endif // (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float dot(float3 p0, float3 p1) __asm("air.dot.v3f32");
    
  __AIR_FUNC__ float length(float3 p) {
    return sqrt(dot(p, p));
  }
    
  __AIR_FUNC__ float distance(float3 p0, float3 p1) {
    return length(p0 - p1);
  }
    
  __AIR_FUNC__ float3 normalize(float3 p) {
    return p / length(p);
  }

  __AIR_FUNC__ float fast_length(float3 p) {
    return half_sqrt(dot(p, p));
  }

  __AIR_FUNC__ float fast_distance(float3 p0, float3 p1) {
    return fast_length(p0 - p1);
  }

  __AIR_FUNC__ float3 fast_normalize(float3 p) {
    return p / fast_length(p);
  }


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_ASM__ double dot(double3 p0, double3 p1) __asm("air.dot.v3f64");
    
  __AIR_FUNC__ double length(double3 p) {
    return sqrt(dot(p, p));
  }
    
  __AIR_FUNC__ double distance(double3 p0, double3 p1) {
    return length(p0 - p1);
  }
    
  __AIR_FUNC__ double3 normalize(double3 p) {
    return p / length(p);
  }


#endif // (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_ASM__ float dot(float4 p0, float4 p1) __asm("air.dot.v4f32");
    
  __AIR_FUNC__ float length(float4 p) {
    return sqrt(dot(p, p));
  }
    
  __AIR_FUNC__ float distance(float4 p0, float4 p1) {
    return length(p0 - p1);
  }
    
  __AIR_FUNC__ float4 normalize(float4 p) {
    return p / length(p);
  }

  __AIR_FUNC__ float fast_length(float4 p) {
    return half_sqrt(dot(p, p));
  }

  __AIR_FUNC__ float fast_distance(float4 p0, float4 p1) {
    return fast_length(p0 - p1);
  }

  __AIR_FUNC__ float4 fast_normalize(float4 p) {
    return p / fast_length(p);
  }


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
  __AIR_ASM__ double dot(double4 p0, double4 p1) __asm("air.dot.v4f64");
    
  __AIR_FUNC__ double length(double4 p) {
    return sqrt(dot(p, p));
  }
    
  __AIR_FUNC__ double distance(double4 p0, double4 p1) {
    return length(p0 - p1);
  }
    
  __AIR_FUNC__ double4 normalize(double4 p) {
    return p / length(p);
  }


#endif // (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))



// OpenCL 1.2 6.12.6 Relational Functions

  __AIR_FUNC__ int   isinf      (float x)  { return (as_int(x) & ~0x80000000) == 0x7f800000; }
  __AIR_FUNC__ int   isfinite   (float x)  { return (as_int(x) & ~0x80000000) < 0x7f800000; }
  __AIR_FUNC__ int   isnan      (float x)  { return (as_int(x) & ~0x80000000) > 0x7f800000; }
  __AIR_FUNC__ int   isnormal   (float x)  { return ((as_int(x) & ~0x80000000) - 0x00800000) < 0x7f000000; }
  __AIR_FUNC__ int   isunordered(float x, float y) { return isnan(x) || isnan(y); }
  __AIR_FUNC__ int   isordered  (float x, float y) { return !isunordered(x,y); }

  __AIR_FUNC__ int2 isinf(float2 a) {
     int2 r; 
     r.hi = isinf(a.hi) ? -1 : 0;
     r.lo = isinf(a.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int3 isinf(float3 a) {
     int3 r; 
     r.x = isinf(a.x) ? -1 : 0;
     r.y = isinf(a.y) ? -1 : 0;
     r.z = isinf(a.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int4 isinf(float4 a)  { int4 r; r.hi = isinf(a.hi); r.lo = isinf(a.lo); return r; }
  __AIR_FUNC__ int8 isinf(float8 a)  { int8 r; r.hi = isinf(a.hi); r.lo = isinf(a.lo); return r; }
  __AIR_FUNC__ int16 isinf(float16 a)  { int16 r; r.hi = isinf(a.hi); r.lo = isinf(a.lo); return r; }

  __AIR_FUNC__ int2 isfinite(float2 a) {
     int2 r; 
     r.hi = isfinite(a.hi) ? -1 : 0;
     r.lo = isfinite(a.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int3 isfinite(float3 a) {
     int3 r; 
     r.x = isfinite(a.x) ? -1 : 0;
     r.y = isfinite(a.y) ? -1 : 0;
     r.z = isfinite(a.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int4 isfinite(float4 a)  { int4 r; r.hi = isfinite(a.hi); r.lo = isfinite(a.lo); return r; }
  __AIR_FUNC__ int8 isfinite(float8 a)  { int8 r; r.hi = isfinite(a.hi); r.lo = isfinite(a.lo); return r; }
  __AIR_FUNC__ int16 isfinite(float16 a)  { int16 r; r.hi = isfinite(a.hi); r.lo = isfinite(a.lo); return r; }

  __AIR_FUNC__ int2 isnan(float2 a) {
     int2 r; 
     r.hi = isnan(a.hi) ? -1 : 0;
     r.lo = isnan(a.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int3 isnan(float3 a) {
     int3 r; 
     r.x = isnan(a.x) ? -1 : 0;
     r.y = isnan(a.y) ? -1 : 0;
     r.z = isnan(a.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int4 isnan(float4 a)  { int4 r; r.hi = isnan(a.hi); r.lo = isnan(a.lo); return r; }
  __AIR_FUNC__ int8 isnan(float8 a)  { int8 r; r.hi = isnan(a.hi); r.lo = isnan(a.lo); return r; }
  __AIR_FUNC__ int16 isnan(float16 a)  { int16 r; r.hi = isnan(a.hi); r.lo = isnan(a.lo); return r; }

  __AIR_FUNC__ int2 isnormal(float2 a) {
     int2 r; 
     r.hi = isnormal(a.hi) ? -1 : 0;
     r.lo = isnormal(a.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int3 isnormal(float3 a) {
     int3 r; 
     r.x = isnormal(a.x) ? -1 : 0;
     r.y = isnormal(a.y) ? -1 : 0;
     r.z = isnormal(a.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int4 isnormal(float4 a)  { int4 r; r.hi = isnormal(a.hi); r.lo = isnormal(a.lo); return r; }
  __AIR_FUNC__ int8 isnormal(float8 a)  { int8 r; r.hi = isnormal(a.hi); r.lo = isnormal(a.lo); return r; }
  __AIR_FUNC__ int16 isnormal(float16 a)  { int16 r; r.hi = isnormal(a.hi); r.lo = isnormal(a.lo); return r; }


  __AIR_FUNC__ int2 isordered(float2 a, float2 b) {
     int2 r;
     r.hi = isordered(a.hi, b.hi) ? -1 : 0;
     r.lo = isordered(a.lo, b.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int3 isordered(float3 a, float3 b) {
     int3 r;
     r.x = isordered(a.x, b.x) ? -1 : 0;
     r.y = isordered(a.y, b.y) ? -1 : 0;
     r.z = isordered(a.z, b.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int4 isordered(float4 a, float4 b)  { int4 r; r.hi = isordered(a.hi, b.hi); r.lo = isordered(a.lo, b.lo); return r; }
  __AIR_FUNC__ int8 isordered(float8 a, float8 b)  { int8 r; r.hi = isordered(a.hi, b.hi); r.lo = isordered(a.lo, b.lo); return r; }
  __AIR_FUNC__ int16 isordered(float16 a, float16 b)  { int16 r; r.hi = isordered(a.hi, b.hi); r.lo = isordered(a.lo, b.lo); return r; }

  __AIR_FUNC__ int2 isunordered(float2 a, float2 b) {
     int2 r;
     r.hi = isunordered(a.hi, b.hi) ? -1 : 0;
     r.lo = isunordered(a.lo, b.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int3 isunordered(float3 a, float3 b) {
     int3 r;
     r.x = isunordered(a.x, b.x) ? -1 : 0;
     r.y = isunordered(a.y, b.y) ? -1 : 0;
     r.z = isunordered(a.z, b.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ int4 isunordered(float4 a, float4 b)  { int4 r; r.hi = isunordered(a.hi, b.hi); r.lo = isunordered(a.lo, b.lo); return r; }
  __AIR_FUNC__ int8 isunordered(float8 a, float8 b)  { int8 r; r.hi = isunordered(a.hi, b.hi); r.lo = isunordered(a.lo, b.lo); return r; }
  __AIR_FUNC__ int16 isunordered(float16 a, float16 b)  { int16 r; r.hi = isunordered(a.hi, b.hi); r.lo = isunordered(a.lo, b.lo); return r; }




  __AIR_FUNC__ int isequal(float x, float y)  { return x == y; }
  __AIR_FUNC__ int2 isequal(float2 x, float2 y)  { return x == y; }
  __AIR_FUNC__ int3 isequal(float3 x, float3 y)  { return x == y; }
  __AIR_FUNC__ int4 isequal(float4 x, float4 y)  { return x == y; }
  __AIR_FUNC__ int8 isequal(float8 x, float8 y)  { return x == y; }
  __AIR_FUNC__ int16 isequal(float16 x, float16 y)  { return x == y; }

  __AIR_FUNC__ int isnotequal(float x, float y)  { return x != y; }
  __AIR_FUNC__ int2 isnotequal(float2 x, float2 y)  { return x != y; }
  __AIR_FUNC__ int3 isnotequal(float3 x, float3 y)  { return x != y; }
  __AIR_FUNC__ int4 isnotequal(float4 x, float4 y)  { return x != y; }
  __AIR_FUNC__ int8 isnotequal(float8 x, float8 y)  { return x != y; }
  __AIR_FUNC__ int16 isnotequal(float16 x, float16 y)  { return x != y; }

  __AIR_FUNC__ int isgreater(float x, float y)  { return x > y; }
  __AIR_FUNC__ int2 isgreater(float2 x, float2 y)  { return x > y; }
  __AIR_FUNC__ int3 isgreater(float3 x, float3 y)  { return x > y; }
  __AIR_FUNC__ int4 isgreater(float4 x, float4 y)  { return x > y; }
  __AIR_FUNC__ int8 isgreater(float8 x, float8 y)  { return x > y; }
  __AIR_FUNC__ int16 isgreater(float16 x, float16 y)  { return x > y; }

  __AIR_FUNC__ int isgreaterequal(float x, float y)  { return x >= y; }
  __AIR_FUNC__ int2 isgreaterequal(float2 x, float2 y)  { return x >= y; }
  __AIR_FUNC__ int3 isgreaterequal(float3 x, float3 y)  { return x >= y; }
  __AIR_FUNC__ int4 isgreaterequal(float4 x, float4 y)  { return x >= y; }
  __AIR_FUNC__ int8 isgreaterequal(float8 x, float8 y)  { return x >= y; }
  __AIR_FUNC__ int16 isgreaterequal(float16 x, float16 y)  { return x >= y; }

  __AIR_FUNC__ int isless(float x, float y)  { return x < y; }
  __AIR_FUNC__ int2 isless(float2 x, float2 y)  { return x < y; }
  __AIR_FUNC__ int3 isless(float3 x, float3 y)  { return x < y; }
  __AIR_FUNC__ int4 isless(float4 x, float4 y)  { return x < y; }
  __AIR_FUNC__ int8 isless(float8 x, float8 y)  { return x < y; }
  __AIR_FUNC__ int16 isless(float16 x, float16 y)  { return x < y; }

  __AIR_FUNC__ int islessequal(float x, float y)  { return x <= y; }
  __AIR_FUNC__ int2 islessequal(float2 x, float2 y)  { return x <= y; }
  __AIR_FUNC__ int3 islessequal(float3 x, float3 y)  { return x <= y; }
  __AIR_FUNC__ int4 islessequal(float4 x, float4 y)  { return x <= y; }
  __AIR_FUNC__ int8 islessequal(float8 x, float8 y)  { return x <= y; }
  __AIR_FUNC__ int16 islessequal(float16 x, float16 y)  { return x <= y; }



  __AIR_ASM__ int all(char x) __asm("air.all_msb.i8");
  __AIR_ASM__ int all(uchar x) __asm("air.all_msb.i8");
  __AIR_ASM__ int all(short x) __asm("air.all_msb.i16");
  __AIR_ASM__ int all(ushort x) __asm("air.all_msb.i16");
  __AIR_ASM__ int all(int x) __asm("air.all_msb.i32");
  __AIR_ASM__ int all(uint x) __asm("air.all_msb.i32");
  __AIR_ASM__ int all(long x) __asm("air.all_msb.i64");
  __AIR_ASM__ int all(ulong x) __asm("air.all_msb.i64");
  __AIR_ASM__ int all(char2 x) __asm("air.all_msb.v2i8");
  __AIR_ASM__ int all(uchar2 x) __asm("air.all_msb.v2i8");
  __AIR_ASM__ int all(short2 x) __asm("air.all_msb.v2i16");
  __AIR_ASM__ int all(ushort2 x) __asm("air.all_msb.v2i16");
  __AIR_ASM__ int all(int2 x) __asm("air.all_msb.v2i32");
  __AIR_ASM__ int all(uint2 x) __asm("air.all_msb.v2i32");
  __AIR_ASM__ int all(long2 x) __asm("air.all_msb.v2i64");
  __AIR_ASM__ int all(ulong2 x) __asm("air.all_msb.v2i64");
  __AIR_ASM__ int all(char3 x) __asm("air.all_msb.v3i8");
  __AIR_ASM__ int all(uchar3 x) __asm("air.all_msb.v3i8");
  __AIR_ASM__ int all(short3 x) __asm("air.all_msb.v3i16");
  __AIR_ASM__ int all(ushort3 x) __asm("air.all_msb.v3i16");
  __AIR_ASM__ int all(int3 x) __asm("air.all_msb.v3i32");
  __AIR_ASM__ int all(uint3 x) __asm("air.all_msb.v3i32");
  __AIR_ASM__ int all(long3 x) __asm("air.all_msb.v3i64");
  __AIR_ASM__ int all(ulong3 x) __asm("air.all_msb.v3i64");
  __AIR_ASM__ int all(char4 x) __asm("air.all_msb.v4i8");
  __AIR_ASM__ int all(uchar4 x) __asm("air.all_msb.v4i8");
  __AIR_ASM__ int all(short4 x) __asm("air.all_msb.v4i16");
  __AIR_ASM__ int all(ushort4 x) __asm("air.all_msb.v4i16");
  __AIR_ASM__ int all(int4 x) __asm("air.all_msb.v4i32");
  __AIR_ASM__ int all(uint4 x) __asm("air.all_msb.v4i32");
  __AIR_ASM__ int all(long4 x) __asm("air.all_msb.v4i64");
  __AIR_ASM__ int all(ulong4 x) __asm("air.all_msb.v4i64");

  __AIR_FUNC__ int all(char8 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(uchar8 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(short8 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(ushort8 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(int8 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(uint8 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(long8 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(ulong8 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(char16 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(uchar16 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(short16 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(ushort16 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(int16 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(uint16 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(long16 x) { return all(x.hi) && all(x.lo); }
  __AIR_FUNC__ int all(ulong16 x) { return all(x.hi) && all(x.lo); }

  __AIR_ASM__ int any(char x) __asm("air.any_msb.i8");
  __AIR_ASM__ int any(uchar x) __asm("air.any_msb.i8");
  __AIR_ASM__ int any(short x) __asm("air.any_msb.i16");
  __AIR_ASM__ int any(ushort x) __asm("air.any_msb.i16");
  __AIR_ASM__ int any(int x) __asm("air.any_msb.i32");
  __AIR_ASM__ int any(uint x) __asm("air.any_msb.i32");
  __AIR_ASM__ int any(long x) __asm("air.any_msb.i64");
  __AIR_ASM__ int any(ulong x) __asm("air.any_msb.i64");
  __AIR_ASM__ int any(char2 x) __asm("air.any_msb.v2i8");
  __AIR_ASM__ int any(uchar2 x) __asm("air.any_msb.v2i8");
  __AIR_ASM__ int any(short2 x) __asm("air.any_msb.v2i16");
  __AIR_ASM__ int any(ushort2 x) __asm("air.any_msb.v2i16");
  __AIR_ASM__ int any(int2 x) __asm("air.any_msb.v2i32");
  __AIR_ASM__ int any(uint2 x) __asm("air.any_msb.v2i32");
  __AIR_ASM__ int any(long2 x) __asm("air.any_msb.v2i64");
  __AIR_ASM__ int any(ulong2 x) __asm("air.any_msb.v2i64");
  __AIR_ASM__ int any(char3 x) __asm("air.any_msb.v3i8");
  __AIR_ASM__ int any(uchar3 x) __asm("air.any_msb.v3i8");
  __AIR_ASM__ int any(short3 x) __asm("air.any_msb.v3i16");
  __AIR_ASM__ int any(ushort3 x) __asm("air.any_msb.v3i16");
  __AIR_ASM__ int any(int3 x) __asm("air.any_msb.v3i32");
  __AIR_ASM__ int any(uint3 x) __asm("air.any_msb.v3i32");
  __AIR_ASM__ int any(long3 x) __asm("air.any_msb.v3i64");
  __AIR_ASM__ int any(ulong3 x) __asm("air.any_msb.v3i64");
  __AIR_ASM__ int any(char4 x) __asm("air.any_msb.v4i8");
  __AIR_ASM__ int any(uchar4 x) __asm("air.any_msb.v4i8");
  __AIR_ASM__ int any(short4 x) __asm("air.any_msb.v4i16");
  __AIR_ASM__ int any(ushort4 x) __asm("air.any_msb.v4i16");
  __AIR_ASM__ int any(int4 x) __asm("air.any_msb.v4i32");
  __AIR_ASM__ int any(uint4 x) __asm("air.any_msb.v4i32");
  __AIR_ASM__ int any(long4 x) __asm("air.any_msb.v4i64");
  __AIR_ASM__ int any(ulong4 x) __asm("air.any_msb.v4i64");

  __AIR_FUNC__ int any(char8 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(uchar8 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(short8 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(ushort8 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(int8 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(uint8 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(long8 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(ulong8 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(char16 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(uchar16 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(short16 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(ushort16 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(int16 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(uint16 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(long16 x) { return any(x.hi) || any(x.lo); }
  __AIR_FUNC__ int any(ulong16 x) { return any(x.hi) || any(x.lo); }

  __AIR_FUNC__ char bitselect(char a, char b, char c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uchar bitselect(uchar a, uchar b, uchar c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ short bitselect(short a, short b, short c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ushort bitselect(ushort a, ushort b, ushort c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ int bitselect(int a, int b, int c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uint bitselect(uint a, uint b, uint c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ long bitselect(long a, long b, long c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ulong bitselect(ulong a, ulong b, ulong c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ char2 bitselect(char2 a, char2 b, char2 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uchar2 bitselect(uchar2 a, uchar2 b, uchar2 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ short2 bitselect(short2 a, short2 b, short2 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ushort2 bitselect(ushort2 a, ushort2 b, ushort2 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ int2 bitselect(int2 a, int2 b, int2 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uint2 bitselect(uint2 a, uint2 b, uint2 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ long2 bitselect(long2 a, long2 b, long2 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ulong2 bitselect(ulong2 a, ulong2 b, ulong2 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ char3 bitselect(char3 a, char3 b, char3 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uchar3 bitselect(uchar3 a, uchar3 b, uchar3 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ short3 bitselect(short3 a, short3 b, short3 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ushort3 bitselect(ushort3 a, ushort3 b, ushort3 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ int3 bitselect(int3 a, int3 b, int3 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uint3 bitselect(uint3 a, uint3 b, uint3 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ long3 bitselect(long3 a, long3 b, long3 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ulong3 bitselect(ulong3 a, ulong3 b, ulong3 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ char4 bitselect(char4 a, char4 b, char4 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uchar4 bitselect(uchar4 a, uchar4 b, uchar4 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ short4 bitselect(short4 a, short4 b, short4 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ushort4 bitselect(ushort4 a, ushort4 b, ushort4 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ int4 bitselect(int4 a, int4 b, int4 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uint4 bitselect(uint4 a, uint4 b, uint4 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ long4 bitselect(long4 a, long4 b, long4 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ulong4 bitselect(ulong4 a, ulong4 b, ulong4 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ char8 bitselect(char8 a, char8 b, char8 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uchar8 bitselect(uchar8 a, uchar8 b, uchar8 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ short8 bitselect(short8 a, short8 b, short8 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ushort8 bitselect(ushort8 a, ushort8 b, ushort8 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ int8 bitselect(int8 a, int8 b, int8 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uint8 bitselect(uint8 a, uint8 b, uint8 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ long8 bitselect(long8 a, long8 b, long8 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ulong8 bitselect(ulong8 a, ulong8 b, ulong8 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ char16 bitselect(char16 a, char16 b, char16 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uchar16 bitselect(uchar16 a, uchar16 b, uchar16 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ short16 bitselect(short16 a, short16 b, short16 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ushort16 bitselect(ushort16 a, ushort16 b, ushort16 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ int16 bitselect(int16 a, int16 b, int16 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ uint16 bitselect(uint16 a, uint16 b, uint16 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ long16 bitselect(long16 a, long16 b, long16 c) { return (a & ~c) | (b & c); }
  __AIR_FUNC__ ulong16 bitselect(ulong16 a, ulong16 b, ulong16 c) { return (a & ~c) | (b & c); }

  __AIR_FUNC__ float bitselect(float a, float b, float c) {
    int ci = as_int(c);
    return as_float((as_int(a) & ~ci) | (as_int(b) & ci));
  }
  __AIR_FUNC__ float2 bitselect(float2 a, float2 b, float2 c) {
    int2 ci = as_int2(c);
    return as_float2((as_int2(a) & ~ci) | (as_int2(b) & ci));
  }
  __AIR_FUNC__ float3 bitselect(float3 a, float3 b, float3 c) {
    int3 ci = as_int3(c);
    return as_float3((as_int3(a) & ~ci) | (as_int3(b) & ci));
  }
  __AIR_FUNC__ float4 bitselect(float4 a, float4 b, float4 c) {
    int4 ci = as_int4(c);
    return as_float4((as_int4(a) & ~ci) | (as_int4(b) & ci));
  }
  __AIR_FUNC__ float8 bitselect(float8 a, float8 b, float8 c) {
    int8 ci = as_int8(c);
    return as_float8((as_int8(a) & ~ci) | (as_int8(b) & ci));
  }
  __AIR_FUNC__ float16 bitselect(float16 a, float16 b, float16 c) {
    int16 ci = as_int16(c);
    return as_float16((as_int16(a) & ~ci) | (as_int16(b) & ci));
  }


#if (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

  __AIR_FUNC__ int  isinf      (double x) { return (as_long(x) & ~0x8000000000000000) == 0x7ff0000000000000; };
  __AIR_FUNC__ int  isfinite   (double x) { return (as_long(x) & ~0x8000000000000000) < 0x7ff0000000000000; };
  __AIR_FUNC__ int  isnan      (double x) { return (as_long(x) & ~0x8000000000000000) > 0x7ff0000000000000; }
  __AIR_FUNC__ int  isnormal   (double x) { return ((as_long(x) & ~0x8000000000000000) - 0x0010000000000000) < 0x7fe0000000000000;}
  __AIR_FUNC__ int  isunordered(double x, double y) { return isnan(x) || isnan(y); }
  __AIR_FUNC__ int  isordered  (double x, double y) { return !isunordered(x,y); }

  __AIR_FUNC__ long2 isinf(double2 a) {
     long2 r; 
     r.hi = isinf(a.hi) ? -1 : 0;
     r.lo = isinf(a.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long3 isinf(double3 a) {
     long3 r; 
     r.x = isinf(a.x) ? -1 : 0;
     r.y = isinf(a.y) ? -1 : 0;
     r.z = isinf(a.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long4 isinf(double4 a)  { long4 r; r.hi = isinf(a.hi); r.lo = isinf(a.lo); return r; }
  __AIR_FUNC__ long8 isinf(double8 a)  { long8 r; r.hi = isinf(a.hi); r.lo = isinf(a.lo); return r; }
  __AIR_FUNC__ long16 isinf(double16 a)  { long16 r; r.hi = isinf(a.hi); r.lo = isinf(a.lo); return r; }

  __AIR_FUNC__ long2 isfinite(double2 a) {
     long2 r; 
     r.hi = isfinite(a.hi) ? -1 : 0;
     r.lo = isfinite(a.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long3 isfinite(double3 a) {
     long3 r; 
     r.x = isfinite(a.x) ? -1 : 0;
     r.y = isfinite(a.y) ? -1 : 0;
     r.z = isfinite(a.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long4 isfinite(double4 a)  { long4 r; r.hi = isfinite(a.hi); r.lo = isfinite(a.lo); return r; }
  __AIR_FUNC__ long8 isfinite(double8 a)  { long8 r; r.hi = isfinite(a.hi); r.lo = isfinite(a.lo); return r; }
  __AIR_FUNC__ long16 isfinite(double16 a)  { long16 r; r.hi = isfinite(a.hi); r.lo = isfinite(a.lo); return r; }

  __AIR_FUNC__ long2 isnan(double2 a) {
     long2 r; 
     r.hi = isnan(a.hi) ? -1 : 0;
     r.lo = isnan(a.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long3 isnan(double3 a) {
     long3 r; 
     r.x = isnan(a.x) ? -1 : 0;
     r.y = isnan(a.y) ? -1 : 0;
     r.z = isnan(a.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long4 isnan(double4 a)  { long4 r; r.hi = isnan(a.hi); r.lo = isnan(a.lo); return r; }
  __AIR_FUNC__ long8 isnan(double8 a)  { long8 r; r.hi = isnan(a.hi); r.lo = isnan(a.lo); return r; }
  __AIR_FUNC__ long16 isnan(double16 a)  { long16 r; r.hi = isnan(a.hi); r.lo = isnan(a.lo); return r; }

  __AIR_FUNC__ long2 isnormal(double2 a) {
     long2 r; 
     r.hi = isnormal(a.hi) ? -1 : 0;
     r.lo = isnormal(a.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long3 isnormal(double3 a) {
     long3 r; 
     r.x = isnormal(a.x) ? -1 : 0;
     r.y = isnormal(a.y) ? -1 : 0;
     r.z = isnormal(a.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long4 isnormal(double4 a)  { long4 r; r.hi = isnormal(a.hi); r.lo = isnormal(a.lo); return r; }
  __AIR_FUNC__ long8 isnormal(double8 a)  { long8 r; r.hi = isnormal(a.hi); r.lo = isnormal(a.lo); return r; }
  __AIR_FUNC__ long16 isnormal(double16 a)  { long16 r; r.hi = isnormal(a.hi); r.lo = isnormal(a.lo); return r; }


  __AIR_FUNC__ long2 isordered(double2 a, double2 b) {
     long2 r;
     r.hi = isordered(a.hi, b.hi) ? -1 : 0;
     r.lo = isordered(a.lo, b.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long3 isordered(double3 a, double3 b) {
     long3 r;
     r.x = isordered(a.x, b.x) ? -1 : 0;
     r.y = isordered(a.y, b.y) ? -1 : 0;
     r.z = isordered(a.z, b.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long4 isordered(double4 a, double4 b)  { long4 r; r.hi = isordered(a.hi, b.hi); r.lo = isordered(a.lo, b.lo); return r; }
  __AIR_FUNC__ long8 isordered(double8 a, double8 b)  { long8 r; r.hi = isordered(a.hi, b.hi); r.lo = isordered(a.lo, b.lo); return r; }
  __AIR_FUNC__ long16 isordered(double16 a, double16 b)  { long16 r; r.hi = isordered(a.hi, b.hi); r.lo = isordered(a.lo, b.lo); return r; }

  __AIR_FUNC__ long2 isunordered(double2 a, double2 b) {
     long2 r;
     r.hi = isunordered(a.hi, b.hi) ? -1 : 0;
     r.lo = isunordered(a.lo, b.lo) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long3 isunordered(double3 a, double3 b) {
     long3 r;
     r.x = isunordered(a.x, b.x) ? -1 : 0;
     r.y = isunordered(a.y, b.y) ? -1 : 0;
     r.z = isunordered(a.z, b.z) ? -1 : 0;
     return r;
  }
  __AIR_FUNC__ long4 isunordered(double4 a, double4 b)  { long4 r; r.hi = isunordered(a.hi, b.hi); r.lo = isunordered(a.lo, b.lo); return r; }
  __AIR_FUNC__ long8 isunordered(double8 a, double8 b)  { long8 r; r.hi = isunordered(a.hi, b.hi); r.lo = isunordered(a.lo, b.lo); return r; }
  __AIR_FUNC__ long16 isunordered(double16 a, double16 b)  { long16 r; r.hi = isunordered(a.hi, b.hi); r.lo = isunordered(a.lo, b.lo); return r; }



  __AIR_FUNC__ long isequal(double x, double y)  { return x == y; }
  __AIR_FUNC__ long2 isequal(double2 x, double2 y)  { return x == y; }
  __AIR_FUNC__ long3 isequal(double3 x, double3 y)  { return x == y; }
  __AIR_FUNC__ long4 isequal(double4 x, double4 y)  { return x == y; }
  __AIR_FUNC__ long8 isequal(double8 x, double8 y)  { return x == y; }
  __AIR_FUNC__ long16 isequal(double16 x, double16 y)  { return x == y; }

  __AIR_FUNC__ long isnotequal(double x, double y)  { return x != y; }
  __AIR_FUNC__ long2 isnotequal(double2 x, double2 y)  { return x != y; }
  __AIR_FUNC__ long3 isnotequal(double3 x, double3 y)  { return x != y; }
  __AIR_FUNC__ long4 isnotequal(double4 x, double4 y)  { return x != y; }
  __AIR_FUNC__ long8 isnotequal(double8 x, double8 y)  { return x != y; }
  __AIR_FUNC__ long16 isnotequal(double16 x, double16 y)  { return x != y; }

  __AIR_FUNC__ long isgreater(double x, double y)  { return x > y; }
  __AIR_FUNC__ long2 isgreater(double2 x, double2 y)  { return x > y; }
  __AIR_FUNC__ long3 isgreater(double3 x, double3 y)  { return x > y; }
  __AIR_FUNC__ long4 isgreater(double4 x, double4 y)  { return x > y; }
  __AIR_FUNC__ long8 isgreater(double8 x, double8 y)  { return x > y; }
  __AIR_FUNC__ long16 isgreater(double16 x, double16 y)  { return x > y; }

  __AIR_FUNC__ long isgreaterequal(double x, double y)  { return x >= y; }
  __AIR_FUNC__ long2 isgreaterequal(double2 x, double2 y)  { return x >= y; }
  __AIR_FUNC__ long3 isgreaterequal(double3 x, double3 y)  { return x >= y; }
  __AIR_FUNC__ long4 isgreaterequal(double4 x, double4 y)  { return x >= y; }
  __AIR_FUNC__ long8 isgreaterequal(double8 x, double8 y)  { return x >= y; }
  __AIR_FUNC__ long16 isgreaterequal(double16 x, double16 y)  { return x >= y; }

  __AIR_FUNC__ long isless(double x, double y)  { return x < y; }
  __AIR_FUNC__ long2 isless(double2 x, double2 y)  { return x < y; }
  __AIR_FUNC__ long3 isless(double3 x, double3 y)  { return x < y; }
  __AIR_FUNC__ long4 isless(double4 x, double4 y)  { return x < y; }
  __AIR_FUNC__ long8 isless(double8 x, double8 y)  { return x < y; }
  __AIR_FUNC__ long16 isless(double16 x, double16 y)  { return x < y; }

  __AIR_FUNC__ long islessequal(double x, double y)  { return x <= y; }
  __AIR_FUNC__ long2 islessequal(double2 x, double2 y)  { return x <= y; }
  __AIR_FUNC__ long3 islessequal(double3 x, double3 y)  { return x <= y; }
  __AIR_FUNC__ long4 islessequal(double4 x, double4 y)  { return x <= y; }
  __AIR_FUNC__ long8 islessequal(double8 x, double8 y)  { return x <= y; }
  __AIR_FUNC__ long16 islessequal(double16 x, double16 y)  { return x <= y; }


  __AIR_FUNC__ double bitselect(double a, double b, double c) {
    long ci = as_long(c);
    return as_double((as_long(a) & ~ci) | (as_long(b) & ci));
  }
  __AIR_FUNC__ double2 bitselect(double2 a, double2 b, double2 c) {
    long2 ci = as_long2(c);
    return as_double2((as_long2(a) & ~ci) | (as_long2(b) & ci));
  }
  __AIR_FUNC__ double3 bitselect(double3 a, double3 b, double3 c) {
    long3 ci = as_long3(c);
    return as_double3((as_long3(a) & ~ci) | (as_long3(b) & ci));
  }
  __AIR_FUNC__ double4 bitselect(double4 a, double4 b, double4 c) {
    long4 ci = as_long4(c);
    return as_double4((as_long4(a) & ~ci) | (as_long4(b) & ci));
  }
  __AIR_FUNC__ double8 bitselect(double8 a, double8 b, double8 c) {
    long8 ci = as_long8(c);
    return as_double8((as_long8(a) & ~ci) | (as_long8(b) & ci));
  }
  __AIR_FUNC__ double16 bitselect(double16 a, double16 b, double16 c) {
    long16 ci = as_long16(c);
    return as_double16((as_long16(a) & ~ci) | (as_long16(b) & ci));
  }

#endif //  (defined(cl_khr_fp64) || defined(cl_APPLE_fp64_basic_ops))

#undef LOG2_10F
#undef LOG10_2F

#endif // __CL_KERNEL_AIR64
