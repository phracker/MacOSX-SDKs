#ifndef __SIMD_PACKED_HEADER__
#define __SIMD_PACKED_HEADER__

/* This is an internal version for Metal compiler. Unlike the host version,
 * packed_* versions are built-in to metal under the metal namespace and
 * we only need to expose it at the top level. 
 */

#if defined(__HAVE_SIMD_PACKED__)

typedef metal::packed_char2 packed_char2;
typedef metal::packed_char4 packed_char4;

typedef metal::packed_uchar2 packed_uchar2;
typedef metal::packed_uchar4 packed_uchar4;

typedef metal::packed_short2 packed_short2;
typedef metal::packed_short4 packed_short4;

typedef metal::packed_ushort2 packed_ushort2;
typedef metal::packed_ushort4 packed_ushort4;

typedef metal::packed_int2 packed_int2;
typedef metal::packed_int4 packed_int4;

typedef metal::packed_uint2 packed_uint2;
typedef metal::packed_uint4 packed_uint4;

typedef metal::packed_float2 packed_float2;
typedef metal::packed_float4 packed_float4;

#endif /* __HAVE_SIMD_PACKED__ */
#endif /* __SIMD_PACKED_HEADER__ */
