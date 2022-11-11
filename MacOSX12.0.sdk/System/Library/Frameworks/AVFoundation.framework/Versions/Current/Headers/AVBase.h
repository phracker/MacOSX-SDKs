#if !__has_include(<AVFCore/AVBase.h>)
/*
	File:  AVBase.h

	Framework:  AVFoundation
 
	Copyright 2010-2017 Apple Inc. All rights reserved.

 */

#import <TargetConditionals.h>
#import <Availability.h>
#import <Foundation/NSObjCRuntime.h>

#if defined(__cplusplus)
	#define AVF_EXPORT extern "C"
#else
	#define AVF_EXPORT extern
#endif

// Annotation for classes that inherit -init and +new from NSObject but cannot be usefully initialized using -init or +new
#define AV_INIT_UNAVAILABLE - (instancetype)init NS_UNAVAILABLE; \
                            + (instancetype)new  NS_UNAVAILABLE;

#ifndef __has_feature
	#define __has_feature(FEATURE) 0
#endif

#ifndef NS_STRING_ENUM
	#define NS_STRING_ENUM
#endif

#ifndef NS_EXTENSIBLE_STRING_ENUM
	#define NS_EXTENSIBLE_STRING_ENUM
#endif

// Pre-10.12
#ifndef __NSi_10_12
	#define __NSi_10_12 introduced=10.12
#endif

#ifndef __NSd_10_12
	#define __NSd_10_12 ,deprecated=10.12
#endif

// Pre-10.11
#ifndef __NSi_10_11_3
	#define __NSi_10_11_3 introduced=10.11.3
#endif

#ifndef __NSi_10_11
	#define __NSi_10_11 introduced=10.11
#endif

#ifndef __NSd_10_11
	#define __NSd_10_11 ,deprecated=10.11
#endif

// Pre-10.10
#ifndef __NSi_10_10
	#define __NSi_10_10 introduced=10.10
#endif

// Pre-10.9, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_9
	#define __AVAILABILITY_INTERNAL__MAC_10_9 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-10.8, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_8
	#define __AVAILABILITY_INTERNAL__MAC_10_8 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER
   #define AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER
   #define AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER WEAK_IMPORT_ATTRIBUTE
#endif

// Pre-10.7, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_7
	#define __AVAILABILITY_INTERNAL__MAC_10_7 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-9.0
#ifndef __NSi_9_0
	#define __NSi_9_0 introduced=9.0
#endif

// Pre-8.3
#ifndef __NSi_8_3
	#define __NSi_8_3 introduced=8.3
#endif

// Pre-5.1, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_5_1
	#define __AVAILABILITY_INTERNAL__IPHONE_5_1 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-5.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_5_0
	#define __AVAILABILITY_INTERNAL__IPHONE_5_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-6.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_6_0
       #define __AVAILABILITY_INTERNAL__IPHONE_6_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-6.1, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_6_1
       #define __AVAILABILITY_INTERNAL__IPHONE_6_1 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-7.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_7_0
       #define __AVAILABILITY_INTERNAL__IPHONE_7_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-7.1, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_7_1
       #define __AVAILABILITY_INTERNAL__IPHONE_7_1 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Deprecations
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_8
	#define AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_8 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9
	#define AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __NSd_9_0
	#define __NSd_9_0 ,deprecated=9.0
#endif

#ifndef __NSd_8_3
	#define __NSd_8_3 ,deprecated=8.3
#endif

#ifndef __NSd_11_0
	#define __NSd_11_0 ,deprecated=11.0
#endif

#ifndef __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_6_0
#define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_6_0 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_6_0
#define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_6_0 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __AVAILABILITY_INTERNAL__IPHONE_4_3_DEP__IPHONE_7_0
#define __AVAILABILITY_INTERNAL__IPHONE_4_3_DEP__IPHONE_7_0 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_7_0
#define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_7_0 WEAK_IMPORT_ATTRIBUTE
#endif

// To be determined, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_TBD
	#define __AVAILABILITY_INTERNAL__IPHONE_TBD __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_TBD
	#define __AVAILABILITY_INTERNAL__MAC_TBD __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef AVAILABLE_MAC_OS_X_VERSION_TBD_AND_LATER
   #define AVAILABLE_MAC_OS_X_VERSION_TBD_AND_LATER WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef API_AVAILABLE
	#define API_AVAILABLE(...)
#endif

#ifndef NS_AVAILABLE
    #define NS_AVAILABLE(a, b)
#endif

#ifndef NS_AVAILABLE_IOS
	#define NS_AVAILABLE_IOS(a)
#endif

#ifndef NS_CLASS_AVAILABLE
    #define NS_CLASS_AVAILABLE(a, b)
#endif

#ifndef NS_DEPRECATED
    #define NS_DEPRECATED(a, b, c, d)
#endif

#ifndef SDK_HIDE_TIDE
#ifndef __TVOS_PROHIBITED
	#define __TVOS_PROHIBITED
#endif
#endif



#else
#import <AVFCore/AVBase.h>
#endif
