/*
 *  QLBase.h
 *  Quick Look
 *
 *  Copyright 2007 Apple Inc.
 *  All rights reserved.
 *
 */

#if !defined(__QUICKLOOK_QLBASE__)
#define __QUICKLOOK_QLBASE__

#ifdef __cplusplus
    #define QL_EXTERN_C_BEGIN extern "C" {
    #define QL_EXTERN_C_END }
#else
    #define QL_EXTERN_C_BEGIN
    #define QL_EXTERN_C_END
#endif

#define QL_EXPORT_OSX
#define QL_EXPORT __attribute__((visibility("default")))
#define QL_PRIVATE_EXPORT __attribute__((visibility("hidden")))
#define QL_INLINE static __inline__ __attribute__((always_inline))
#define QL_NOINLINE __attribute__((noinline))
#define QL_DEPRECATED __attribute__((deprecated))
#define QL_FORMAT_ARG(F, A) __attribute__((format(CFString, F, A)))

#endif
