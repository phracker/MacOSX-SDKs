#ifndef __SIMD_PACKED_HEADER__
#define __SIMD_PACKED_HEADER__

#if defined __has_attribute && __has_attribute(__ext_vector_type__) && __has_attribute(__aligned__)
/*  The function of this header fundamentally depends on the ext_vector_type
 *  and aligned attributes.  There is no fallback if these attributes are not
 *  supported by your compiler.                                               */

typedef __attribute__((__ext_vector_type__(2),__aligned__(1))) char packed_char2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(1))) char packed_char4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(1))) char packed_char8;
typedef __attribute__((__ext_vector_type__(16),__aligned__(1))) char packed_char16;
typedef __attribute__((__ext_vector_type__(32),__aligned__(1))) char packed_char32;

typedef __attribute__((__ext_vector_type__(2),__aligned__(1))) unsigned char packed_uchar2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(1))) unsigned char packed_uchar4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(1))) unsigned char packed_uchar8;
typedef __attribute__((__ext_vector_type__(16),__aligned__(1))) unsigned char packed_uchar16;
typedef __attribute__((__ext_vector_type__(32),__aligned__(1))) unsigned char packed_uchar32;

typedef __attribute__((__ext_vector_type__(2),__aligned__(2))) short packed_short2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(2))) short packed_short4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(2))) short packed_short8;
typedef __attribute__((__ext_vector_type__(16),__aligned__(2))) short packed_short16;
typedef __attribute__((__ext_vector_type__(32),__aligned__(2))) short packed_short32;

typedef __attribute__((__ext_vector_type__(2),__aligned__(2))) unsigned short packed_ushort2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(2))) unsigned short packed_ushort4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(2))) unsigned short packed_ushort8;
typedef __attribute__((__ext_vector_type__(16),__aligned__(2))) unsigned short packed_ushort16;
typedef __attribute__((__ext_vector_type__(32),__aligned__(2))) unsigned short packed_ushort32;

typedef __attribute__((__ext_vector_type__(2),__aligned__(4))) int packed_int2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(4))) int packed_int4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(4))) int packed_int8;
typedef __attribute__((__ext_vector_type__(16),__aligned__(4))) int packed_int16;

typedef __attribute__((__ext_vector_type__(2),__aligned__(4))) unsigned int packed_uint2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(4))) unsigned int packed_uint4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(4))) unsigned int packed_uint8;
typedef __attribute__((__ext_vector_type__(16),__aligned__(4))) unsigned int packed_uint16;

typedef __attribute__((__ext_vector_type__(2),__aligned__(4))) float packed_float2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(4))) float packed_float4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(4))) float packed_float8;
typedef __attribute__((__ext_vector_type__(16),__aligned__(4))) float packed_float16;

#if defined __LP64__
typedef __attribute__((__ext_vector_type__(2),__aligned__(8))) long packed_long2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(8))) long packed_long4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(8))) long packed_long8;

typedef __attribute__((__ext_vector_type__(2),__aligned__(8))) unsigned long packed_ulong2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(8))) unsigned long packed_ulong4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(8))) unsigned long packed_ulong8;
#else
typedef __attribute__((__ext_vector_type__(2),__aligned__(8))) long long packed_long2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(8))) long long packed_long4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(8))) long long packed_long8;

typedef __attribute__((__ext_vector_type__(2),__aligned__(8))) unsigned long long packed_ulong2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(8))) unsigned long long packed_ulong4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(8))) unsigned long long packed_ulong8;
#endif

typedef __attribute__((__ext_vector_type__(2),__aligned__(8))) double packed_double2;
typedef __attribute__((__ext_vector_type__(4),__aligned__(8))) double packed_double4;
typedef __attribute__((__ext_vector_type__(8),__aligned__(8))) double packed_double8;

#endif /* __has_attribute(__ext_vector_type__) */
#endif /* __SIMD_PACKED_HEADER__ */
