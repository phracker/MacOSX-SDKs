/*
 *  CoreTelephonyDefines.h
 *  CFTelephony
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

// Macros to export a symbol from the CoreTelephony library
#ifndef __CORETELEPHONY_DEFINES_H__
#define __CORETELEPHONY_DEFINES_H__

#ifdef __cplusplus
#define CORETELEPHONY_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define CORETELEPHONY_EXTERN   extern __attribute__((visibility ("default")))
#endif

#define	CORETELEPHONY_EXTERN_CLASS	__attribute__((visibility("default")))
#define CORETELEPHONY_CLASS_AVAILABLE(_iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, _iphoneIntro)

#include <CoreFoundation/CoreFoundation.h>	// need this for SInt32

enum {
	kCTErrorDomainNoError	= 0,
	kCTErrorDomainPOSIX		= 1,	/* POSIX error listed in sys/errno.h */
	kCTErrorDomainMach				/* mach error listed in mach/error.h */
};

typedef struct {
	SInt32 domain;
	SInt32 error;
} CTError;
		
#endif
