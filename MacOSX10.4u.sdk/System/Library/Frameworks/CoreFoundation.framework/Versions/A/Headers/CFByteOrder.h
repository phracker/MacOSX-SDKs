/*	CFByteOrder.h
	Copyright (c) 1995-2005, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBYTEORDER__)
#define __COREFOUNDATION_CFBYTEORDER__ 1

#if defined(__i386__) && !defined(__LITTLE_ENDIAN__)
    #define __LITTLE_ENDIAN__ 1
#endif

#if !defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)
#error Do not know the endianess of this architecture
#endif

#include <CoreFoundation/CFBase.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum __CFByteOrder {
    CFByteOrderUnknown,
    CFByteOrderLittleEndian,
    CFByteOrderBigEndian
} CFByteOrder;

CF_INLINE CFByteOrder CFByteOrderGetCurrent(void) {
    uint32_t x = (CFByteOrderBigEndian << 24) | CFByteOrderLittleEndian;
    return (CFByteOrder)*((uint8_t *)&x);
}

CF_INLINE uint16_t CFSwapInt16(uint16_t arg) {
#if defined(__i386__) && defined(__GNUC__)
    __asm__("xchgb %b0, %h0" : "+q" (arg));
    return arg;
#elif defined(__ppc__) && defined(__GNUC__)
    uint16_t result;
    __asm__("lhbrx %0,0,%1" : "=r" (result) : "r" (&arg), "m" (arg));
    return result;
#else
    uint16_t result;
    result = ((arg << 8) & 0xFF00) | ((arg >> 8) & 0xFF);
    return result;
#endif
}

CF_INLINE uint32_t CFSwapInt32(uint32_t arg) {
#if defined(__i386__) && defined(__GNUC__)
    __asm__("bswap %0" : "+r" (arg));
    return arg;
#elif defined(__ppc__) && defined(__GNUC__)
    uint32_t result;
    __asm__("lwbrx %0,0,%1" : "=r" (result) : "r" (&arg), "m" (arg));
    return result;
#else
    uint32_t result;
    result = ((arg & 0xFF) << 24) | ((arg & 0xFF00) << 8) | ((arg >> 8) & 0xFF00) | ((arg >> 24) & 0xFF);
    return result;
#endif
}

CF_INLINE uint64_t CFSwapInt64(uint64_t arg) {
    union CFSwap {
        uint64_t sv;
        uint32_t ul[2];
    } tmp, result;
    tmp.sv = arg;
    result.ul[0] = CFSwapInt32(tmp.ul[1]); 
    result.ul[1] = CFSwapInt32(tmp.ul[0]);
    return result.sv;
}

CF_INLINE uint16_t CFSwapInt16BigToHost(uint16_t arg) {
#if defined(__BIG_ENDIAN__)
    return arg;
#else
    return CFSwapInt16(arg);
#endif
}

CF_INLINE uint32_t CFSwapInt32BigToHost(uint32_t arg) {
#if defined(__BIG_ENDIAN__)
    return arg;
#else
    return CFSwapInt32(arg);
#endif
}

CF_INLINE uint64_t CFSwapInt64BigToHost(uint64_t arg) {
#if defined(__BIG_ENDIAN__)
    return arg;
#else
    return CFSwapInt64(arg);
#endif
}

CF_INLINE uint16_t CFSwapInt16HostToBig(uint16_t arg) {
#if defined(__BIG_ENDIAN__)
    return arg;
#else
    return CFSwapInt16(arg);
#endif
}

CF_INLINE uint32_t CFSwapInt32HostToBig(uint32_t arg) {
#if defined(__BIG_ENDIAN__)
    return arg;
#else
    return CFSwapInt32(arg);
#endif
}

CF_INLINE uint64_t CFSwapInt64HostToBig(uint64_t arg) {
#if defined(__BIG_ENDIAN__)
    return arg;
#else
    return CFSwapInt64(arg);
#endif
}

CF_INLINE uint16_t CFSwapInt16LittleToHost(uint16_t arg) {
#if defined(__LITTLE_ENDIAN__)
    return arg;
#else
    return CFSwapInt16(arg);
#endif
}

CF_INLINE uint32_t CFSwapInt32LittleToHost(uint32_t arg) {
#if defined(__LITTLE_ENDIAN__)
    return arg;
#else
    return CFSwapInt32(arg);
#endif
}

CF_INLINE uint64_t CFSwapInt64LittleToHost(uint64_t arg) {
#if defined(__LITTLE_ENDIAN__)
    return arg;
#else
    return CFSwapInt64(arg);
#endif
}

CF_INLINE uint16_t CFSwapInt16HostToLittle(uint16_t arg) {
#if defined(__LITTLE_ENDIAN__)
    return arg;
#else
    return CFSwapInt16(arg);
#endif
}

CF_INLINE uint32_t CFSwapInt32HostToLittle(uint32_t arg) {
#if defined(__LITTLE_ENDIAN__)
    return arg;
#else
    return CFSwapInt32(arg);
#endif
}

CF_INLINE uint64_t CFSwapInt64HostToLittle(uint64_t arg) {
#if defined(__LITTLE_ENDIAN__)
    return arg;
#else
    return CFSwapInt64(arg);
#endif
}

typedef struct {uint32_t v;} CFSwappedFloat32;
typedef struct {uint64_t v;} CFSwappedFloat64;

CF_INLINE CFSwappedFloat32 CFConvertFloat32HostToSwapped(Float32 arg) {
    union CFSwap {
	Float32 v;
	CFSwappedFloat32 sv;
    } result;
    result.v = arg;
#if defined(__LITTLE_ENDIAN__)
    result.sv.v = CFSwapInt32(result.sv.v);
#endif
    return result.sv;
}

CF_INLINE Float32 CFConvertFloat32SwappedToHost(CFSwappedFloat32 arg) {
    union CFSwap {
	Float32 v;
	CFSwappedFloat32 sv;
    } result;
    result.sv = arg;
#if defined(__LITTLE_ENDIAN__)
    result.sv.v = CFSwapInt32(result.sv.v);
#endif
    return result.v;
}

CF_INLINE CFSwappedFloat64 CFConvertFloat64HostToSwapped(Float64 arg) {
    union CFSwap {
	Float64 v;
	CFSwappedFloat64 sv;
    } result;
    result.v = arg;
#if defined(__LITTLE_ENDIAN__)
    result.sv.v = CFSwapInt64(result.sv.v);
#endif
    return result.sv;
}

CF_INLINE Float64 CFConvertFloat64SwappedToHost(CFSwappedFloat64 arg) {
    union CFSwap {
	Float64 v;
	CFSwappedFloat64 sv;
    } result;
    result.sv = arg;
#if defined(__LITTLE_ENDIAN__)
    result.sv.v = CFSwapInt64(result.sv.v);
#endif
    return result.v;
}

CF_INLINE CFSwappedFloat32 CFConvertFloatHostToSwapped(float arg) {
    union CFSwap {
	float v;
	CFSwappedFloat32 sv;
    } result;
    result.v = arg;
#if defined(__LITTLE_ENDIAN__)
    result.sv.v = CFSwapInt32(result.sv.v);
#endif
    return result.sv;
}

CF_INLINE float CFConvertFloatSwappedToHost(CFSwappedFloat32 arg) {
    union CFSwap {
	float v;
	CFSwappedFloat32 sv;
    } result;
    result.sv = arg;
#if defined(__LITTLE_ENDIAN__)
    result.sv.v = CFSwapInt32(result.sv.v);
#endif
    return result.v;
}

CF_INLINE CFSwappedFloat64 CFConvertDoubleHostToSwapped(double arg) {
    union CFSwap {
	double v;
	CFSwappedFloat64 sv;
    } result;
    result.v = arg;
#if defined(__LITTLE_ENDIAN__)
    result.sv.v = CFSwapInt64(result.sv.v);
#endif
    return result.sv;
}

CF_INLINE double CFConvertDoubleSwappedToHost(CFSwappedFloat64 arg) {
    union CFSwap {
	double v;
	CFSwappedFloat64 sv;
    } result;
    result.sv = arg;
#if defined(__LITTLE_ENDIAN__)
    result.sv.v = CFSwapInt64(result.sv.v);
#endif
    return result.v;
}

#if defined(__cplusplus)
}
#endif

#endif /* ! __COREFOUNDATION_CFBYTEORDER__ */

