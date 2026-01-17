/*
 *  GKDefines.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#ifndef GK_EXTERN
#ifdef __cplusplus
#define GK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define GK_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

#define	GK_EXTERN_CLASS	__attribute__((visibility("default")))

#ifndef GK_EXTERN_WEAK
#define GK_EXTERN_WEAK  GK_EXTERN __attribute__((weak_import))
#endif

#if !TARGET_OS_IPHONE
#ifndef __AVAILABILITY_INTERNAL__MAC_10_9
#define __AVAILABILITY_INTERNAL__MAC_10_9 __attribute__((weak_import))
#endif
#ifndef __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_9
#define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_9 __attribute__((weak_import))
#endif
#endif