/*
 *  QLBase.h
 *  Quick Look
 *
 *  Copyright 2007 Apple Inc.
 *  All rights reserved.
 *
 */

#if !defined(__QUICKLOOK_QLTHUMBNAILINGBASE__)
#define __QUICKLOOK_QLTHUMBNAILINGBASE__

#ifdef __cplusplus
    #define QLT_EXTERN_C_BEGIN extern "C" {
    #define QLT_EXTERN_C_END }
#else
    #define QLT_EXTERN_C_BEGIN
    #define QLT_EXTERN_C_END
#endif

#define QLT_EXPORT __attribute__((visibility("default")))
#define QLT_WEAK_EXPORT __attribute__((weak_import, visibility("default")))
#define QLT_PRIVATE_EXPORT __attribute__((visibility("hidden")))
#define QLT_INLINE static __inline__ __attribute__((always_inline))
#define QLT_NOINLINE __attribute__((noinline))
#define QLT_DEPRECATED __attribute__((deprecated))
#define QLT_FORMAT_ARG(F, A) __attribute__((format(CFString, F, A)))

#define QLT_LIKELY(T) __builtin_expect(T, 1);
#define QLT_UNLIKELY(T) __builtin_expect(T, 0)

#endif
