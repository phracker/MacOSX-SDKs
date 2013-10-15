/*	NSObjCRuntime.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#if defined(__WIN32__)
    #undef FOUNDATION_EXPORT
    #if defined(NSBUILDINGFOUNDATION)
	#define FOUNDATION_EXPORT __declspec(dllexport) extern
    #else
	#define FOUNDATION_EXPORT __declspec(dllimport) extern
    #endif
    #if !defined(FOUNDATION_IMPORT)
	#define FOUNDATION_IMPORT __declspec(dllimport) extern
    #endif
#endif

#if defined(__cplusplus)
    #define FOUNDATION_EXPORT extern "C"
    #define FOUNDATION_IMPORT extern "C"
#endif

#if !defined(FOUNDATION_EXPORT)
    #define FOUNDATION_EXPORT extern
#endif

#if !defined(FOUNDATION_IMPORT)
    #define FOUNDATION_IMPORT extern
#endif

#if !defined(FOUNDATION_STATIC_INLINE)
#if defined (__GNUC__) && (__GNUC__ == 4)
#define FOUNDATION_STATIC_INLINE static __inline__ __attribute__((always_inline))
#else
#define FOUNDATION_STATIC_INLINE static __inline__
#endif
#endif

#if !defined(FOUNDATION_EXTERN_INLINE)
#define FOUNDATION_EXTERN_INLINE extern __inline__
#endif

#import <objc/objc.h>
#include <stdarg.h>
#include <stdint.h>
#include <AvailabilityMacros.h>
#if defined(__hpux__)
#include <sys/param.h>
#endif

FOUNDATION_EXPORT double NSFoundationVersionNumber;

#define NSFoundationVersionNumber10_0 397.4
#define NSFoundationVersionNumber10_1 425.0
#define NSFoundationVersionNumber10_2 462.0
#define NSFoundationVersionNumber10_3 500.0
#define NSFoundationVersionNumber10_3_2 500.3
#define NSFoundationVersionNumber10_3_3 500.54
#define NSFoundationVersionNumber10_3_4 500.56

@class NSString;

FOUNDATION_EXPORT NSString *NSStringFromSelector(SEL aSelector);
FOUNDATION_EXPORT SEL NSSelectorFromString(NSString *aSelectorName);
FOUNDATION_EXPORT Class NSClassFromString(NSString *aClassName);
FOUNDATION_EXPORT NSString *NSStringFromClass(Class aClass);
FOUNDATION_EXPORT const char *NSGetSizeAndAlignment(const char *typePtr, unsigned int *sizep, unsigned int *alignp);

FOUNDATION_EXPORT void NSLog(NSString *format, ...);
FOUNDATION_EXPORT void NSLogv(NSString *format, va_list args);

typedef enum _NSComparisonResult {NSOrderedAscending = -1, NSOrderedSame, NSOrderedDescending} NSComparisonResult;

enum {NSNotFound = 0x7fffffff};

#if !defined(YES)
    #define YES	(BOOL)1
#endif

#if !defined(NO)
    #define NO	(BOOL)0
#endif

#if !defined(nil)
    #define nil	(id)0
#endif

#if !defined(Nil)
    #define Nil	(Class)0
#endif

#if defined(__GNUC__) && !defined(__STRICT_ANSI__)

#if !defined(MIN)
    #define MIN(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#endif

#if !defined(MAX)
    #define MAX(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })
#endif

#if !defined(ABS)
    #define ABS(A)	({ __typeof__(A) __a = (A); __a < 0 ? -__a : __a; })
#endif

#else

#if !defined(MIN)
    #define MIN(A,B)	((A) < (B) ? (A) : (B))
#endif

#if !defined(MAX)
    #define MAX(A,B)	((A) > (B) ? (A) : (B))
#endif

#if !defined(ABS)
    #define ABS(A)	((A) < 0 ? (-(A)) : (A))
#endif

#endif	/* __GNUC__ */

