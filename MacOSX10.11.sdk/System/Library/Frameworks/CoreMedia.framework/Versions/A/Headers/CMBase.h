/*
    File:  CMBase.h
	
	Framework:  CoreMedia
	
    Copyright 2006-2015 Apple Inc. All rights reserved.

*/

#ifndef CMBASE_H
#define	CMBASE_H

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

// Pre-10.11, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_11
	#define __AVAILABILITY_INTERNAL__MAC_10_11 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-10.10, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_10
	#define __AVAILABILITY_INTERNAL__MAC_10_10 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-10.7, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_7
	#define __AVAILABILITY_INTERNAL__MAC_10_7 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-4.3, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_4_3
	#define __AVAILABILITY_INTERNAL__IPHONE_4_3 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-10.8, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_8
	#define __AVAILABILITY_INTERNAL__MAC_10_8 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER
	#define AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER WEAK_IMPORT_ATTRIBUTE
#endif
// Pre-6.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_6_0
	#define __AVAILABILITY_INTERNAL__IPHONE_6_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-10.9, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_9
	#define __AVAILABILITY_INTERNAL__MAC_10_9 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER
	#define AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER WEAK_IMPORT_ATTRIBUTE
#endif
// Pre-7.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_7_0
#define __AVAILABILITY_INTERNAL__IPHONE_7_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-7.1, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_7_1
#define __AVAILABILITY_INTERNAL__IPHONE_7_1 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-10.10, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_10
#define __AVAILABILITY_INTERNAL__MAC_10_10 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-9.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_9_0
#define __AVAILABILITY_INTERNAL__IPHONE_9_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-8.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_8_0
#define __AVAILABILITY_INTERNAL__IPHONE_8_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Deprecations
#ifndef __AVAILABILITY_INTERNAL__IPHONE_3_0_DEP__IPHONE_7_0
#define __AVAILABILITY_INTERNAL__IPHONE_3_0_DEP__IPHONE_7_0 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_11
#define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_11 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_0
#define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_0 WEAK_IMPORT_ATTRIBUTE
#endif

#include <stdint.h>						// int32_t, etc.
#include <stddef.h>						// size_t

#include <CoreFoundation/CFBase.h>		// OSStatus, Boolean, Float32, Float64

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

#if TARGET_OS_MAC
	#define CM_EXPORT extern
	#define VT_EXPORT extern
	#define MT_EXPORT extern
#elif TARGET_OS_WIN32
	#define CM_EXPORT __declspec( dllimport ) extern
	#define VT_EXPORT __declspec( dllimport ) extern
	#define MT_EXPORT __declspec( dllimport ) extern
#else
	#error "specify your platform"
#endif

#if TARGET_OS_WINDOWS && TARGET_CPU_X86_64
typedef int64_t CMItemCount;
typedef int64_t CMItemIndex;
#else
typedef signed long	CMItemCount;
typedef signed long	CMItemIndex;
#endif

#define COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS	(__cplusplus && __cplusplus >= 201103L && (__has_extension(cxx_strong_enums) || __has_feature(objc_fixed_enum))) || (!__cplusplus && __has_feature(objc_fixed_enum))

#if (TARGET_OS_IPHONE || TARGET_OS_MAC) && defined(__has_feature)
#if __has_feature(nullability)
	#define COREMEDIA_DECLARE_NULLABILITY 1
#endif
#if __has_feature(assume_nonnull)
	#define COREMEDIA_DECLARE_NULLABILITY_BEGIN_END 1
#endif
#if __has_feature(objc_bridge_id)
	#define COREMEDIA_DECLARE_BRIDGED_TYPES 1
#endif
#if __has_feature(attribute_cf_returns_retained)
	#define COREMEDIA_DECLARE_RETURNS_RETAINED 1
#endif
#if __has_feature(attribute_cf_returns_on_parameters)
	#define COREMEDIA_DECLARE_RETURNS_RETAINED_ON_PARAMETERS 1
	#define COREMEDIA_DECLARE_RETURNS_NOT_RETAINED_ON_PARAMETERS 1
#endif
#endif // (TARGET_OS_IPHONE || TARGET_OS_MAC) && defined(__has_feature)

#if COREMEDIA_DECLARE_NULLABILITY
#define CM_NULLABLE __nullable
#define CM_NONNULL __nonnull
#else
#define CM_NULLABLE
#define CM_NONNULL
#endif

#if COREMEDIA_DECLARE_NULLABILITY_BEGIN_END
#define CM_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define CM_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
#else
#define CM_ASSUME_NONNULL_BEGIN
#define CM_ASSUME_NONNULL_END
#endif
	
#if COREMEDIA_DECLARE_BRIDGED_TYPES
#define CM_BRIDGED_TYPE(type)	CF_BRIDGED_TYPE(type)
#else
#define CM_BRIDGED_TYPE(type)
#endif
	
#if COREMEDIA_DECLARE_RETURNS_RETAINED
#define CM_RETURNS_RETAINED		CF_RETURNS_RETAINED
#else
#define CM_RETURNS_RETAINED
#endif
	
#if COREMEDIA_DECLARE_RETURNS_RETAINED_ON_PARAMETERS
#define CM_RETURNS_RETAINED_PARAMETER	CF_RETURNS_RETAINED
#else
#define CM_RETURNS_RETAINED_PARAMETER
#endif
	
#if COREMEDIA_DECLARE_RETURNS_NOT_RETAINED_ON_PARAMETERS
#define CM_RETURNS_NOT_RETAINED_PARAMETER	CF_RETURNS_NOT_RETAINED
#else
#define CM_RETURNS_NOT_RETAINED_PARAMETER
#endif
	
typedef int32_t CMPersistentTrackID;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMPersistentTrackID
#else
enum
#endif
{
	kCMPersistentTrackID_Invalid = 0
};

#if !defined(CM_INLINE)
	#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
		#define CM_INLINE static inline
	#elif defined(__MWERKS__) || defined(__cplusplus)
		#define CM_INLINE static inline
	#elif defined(__GNUC__)
		#define CM_INLINE static __inline__
	#elif defined(_MSC_VER)
		#define CM_INLINE static __inline
	#else
		#define CM_INLINE static    
	#endif
#endif

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // CMBASE_H
