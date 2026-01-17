/*
 *  QLBase.h
 *  Quick Look
 *
 *  Copyright 2007-2010 Apple Inc.
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

#define QUICKLOOK_VERSION 5000

#define QL_EXPORT extern
#define QL_PRIVATE_EXPORT __attribute__((visibility("hidden")))
#define QL_INLINE static __inline__ __attribute__((always_inline))
#define QL_NOINLINE __attribute__((noinline))
#define QL_DEPRECATED __attribute__((deprecated))
#define QL_FORMAT_ARG(F, A) __attribute__((format(CFString, F, A)))

/*
 * Temporary defines
 */
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER 
#endif
#ifndef MAC_OS_X_VERSION_10_7
#define MAC_OS_X_VERSION_10_7 MAC_OS_X_VERSION_10_6
#endif


#endif
