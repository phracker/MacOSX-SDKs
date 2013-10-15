/*	NSObjCRuntime.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#include <TargetConditionals.h>

#if defined(__cplusplus)
#define FOUNDATION_EXTERN extern "C"
#else
#define FOUNDATION_EXTERN extern
#endif

#if TARGET_OS_WIN32

    #if defined(NSBUILDINGFOUNDATION)
        #define FOUNDATION_EXPORT FOUNDATION_EXTERN __declspec(dllexport)
    #else
        #define FOUNDATION_EXPORT FOUNDATION_EXTERN __declspec(dllimport)
    #endif

    #define FOUNDATION_IMPORT FOUNDATION_EXTERN __declspec(dllimport)

#else
    #define FOUNDATION_EXPORT  FOUNDATION_EXTERN
    #define FOUNDATION_IMPORT FOUNDATION_EXTERN
#endif

#if !defined(NS_INLINE)
    #if defined(__GNUC__)
        #define NS_INLINE static __inline__ __attribute__((always_inline))
    #elif defined(__MWERKS__) || defined(__cplusplus)
        #define NS_INLINE static inline
    #elif defined(_MSC_VER)
        #define NS_INLINE static __inline
    #elif TARGET_OS_WIN32
        #define NS_INLINE static __inline__
    #endif
#endif

#if !defined(FOUNDATION_STATIC_INLINE)
#define FOUNDATION_STATIC_INLINE static __inline__
#endif

#if !defined(FOUNDATION_EXTERN_INLINE)
#define FOUNDATION_EXTERN_INLINE extern __inline__
#endif

#if !defined(NS_REQUIRES_NIL_TERMINATION)
    #if TARGET_OS_WIN32
        #define NS_REQUIRES_NIL_TERMINATION
    #else
        #if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
            #define NS_REQUIRES_NIL_TERMINATION __attribute__((sentinel(0,1)))
        #else
            #define NS_REQUIRES_NIL_TERMINATION __attribute__((sentinel))
        #endif
    #endif
#endif

#if !defined(NS_BLOCKS_AVAILABLE)
    #if __BLOCKS__ && MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
        #define NS_BLOCKS_AVAILABLE 1
    #else
        #define NS_BLOCKS_AVAILABLE 0
    #endif
#endif

// Marks APIs whose iPhone versions are nonatomic, that is cannot be set/get from multiple threads safely without additional synchronization
#if !defined(NS_NONATOMIC_IPHONEONLY)
    #if TARGET_OS_IPHONE
	#define NS_NONATOMIC_IPHONEONLY nonatomic
    #else
	#define NS_NONATOMIC_IPHONEONLY
    #endif
#endif

// Marks APIs which format strings by taking a format string and optional varargs as arguments
#if !defined(NS_FORMAT_FUNCTION)
    #if (__GNUC__*10+__GNUC_MINOR__ >= 42) && (TARGET_OS_MAC || TARGET_OS_EMBEDDED)
	#define NS_FORMAT_FUNCTION(F,A) __attribute__((format(__NSString__, F, A)))
    #else
	#define NS_FORMAT_FUNCTION(F,A)
    #endif
#endif

// Marks APIs which are often used to process (take and return) format strings, so they can be used in place of a constant format string parameter in APIs
#if !defined(NS_FORMAT_ARGUMENT)
    #if (__GNUC__*10+__GNUC_MINOR__ >= 42) && (TARGET_OS_MAC || TARGET_OS_EMBEDDED)
	#define NS_FORMAT_ARGUMENT(A) __attribute__ ((format_arg(A)))
    #else
	#define NS_FORMAT_ARGUMENT(A)
    #endif
#endif

// Marks methods and functions which return an object that needs to be released by the caller but whose names are not consistent with Cocoa naming rules. The recommended fix to this is the rename the methods or functions, but this macro can be used to let the clang static analyzer know of any exceptions that cannot be fixed.
#if defined(__clang__)
#define NS_RETURNS_RETAINED __attribute__((ns_returns_retained))
#else
#define NS_RETURNS_RETAINED
#endif



#import <objc/objc.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <AvailabilityMacros.h>

FOUNDATION_EXPORT double NSFoundationVersionNumber;

#if TARGET_OS_MAC
#define NSFoundationVersionNumber10_0	397.40
#define NSFoundationVersionNumber10_1	425.00
#define NSFoundationVersionNumber10_1_1	425.00
#define NSFoundationVersionNumber10_1_2	425.00
#define NSFoundationVersionNumber10_1_3	425.00
#define NSFoundationVersionNumber10_1_4	425.00
#define NSFoundationVersionNumber10_2	462.00
#define NSFoundationVersionNumber10_2_1	462.00
#define NSFoundationVersionNumber10_2_2	462.00
#define NSFoundationVersionNumber10_2_3	462.00
#define NSFoundationVersionNumber10_2_4	462.00
#define NSFoundationVersionNumber10_2_5	462.00
#define NSFoundationVersionNumber10_2_6	462.00
#define NSFoundationVersionNumber10_2_7	462.70
#define NSFoundationVersionNumber10_2_8	462.70
#define NSFoundationVersionNumber10_3	500.00
#define NSFoundationVersionNumber10_3_1	500.00
#define NSFoundationVersionNumber10_3_2	500.30
#define NSFoundationVersionNumber10_3_3	500.54
#define NSFoundationVersionNumber10_3_4	500.56
#define NSFoundationVersionNumber10_3_5	500.56
#define NSFoundationVersionNumber10_3_6	500.56
#define NSFoundationVersionNumber10_3_7	500.56
#define NSFoundationVersionNumber10_3_8	500.56
#define NSFoundationVersionNumber10_3_9	500.58
#define NSFoundationVersionNumber10_4	567.00
#define NSFoundationVersionNumber10_4_1	567.00
#define NSFoundationVersionNumber10_4_2	567.12
#define NSFoundationVersionNumber10_4_3	567.21
#define NSFoundationVersionNumber10_4_4_Intel	567.23
#define NSFoundationVersionNumber10_4_4_PowerPC	567.21
#define NSFoundationVersionNumber10_4_5	567.25
#define NSFoundationVersionNumber10_4_6	567.26
#define NSFoundationVersionNumber10_4_7	567.27
#define NSFoundationVersionNumber10_4_8	567.28
#define NSFoundationVersionNumber10_4_9	567.29
#define NSFoundationVersionNumber10_4_10	567.29
#define NSFoundationVersionNumber10_4_11	567.36
#define NSFoundationVersionNumber10_5	677.00
#define NSFoundationVersionNumber10_5_1	677.10
#define NSFoundationVersionNumber10_5_2 677.15
#define NSFoundationVersionNumber10_5_3 677.19
#define NSFoundationVersionNumber10_5_4 677.19
#define NSFoundationVersionNumber10_5_5 677.21
#define NSFoundationVersionNumber10_5_6 677.22
#define NSFoundationVersionNumber10_5_7 677.24
#define NSFoundationVersionNumber10_5_8 677.26
#define NSFoundationVersionNumber10_6 751.00
#define NSFoundationVersionNumber10_6_1 751.00
#define NSFoundationVersionNumber10_6_2 751.14
#define NSFoundationVersionNumber10_6_3 751.21
#endif

#if TARGET_OS_IPHONE
#define NSFoundationVersionNumber_iPhoneOS_2_0	678.24
#define NSFoundationVersionNumber_iPhoneOS_2_1  678.26
#define NSFoundationVersionNumber_iPhoneOS_2_2  678.29
#define NSFoundationVersionNumber_iPhoneOS_3_0  678.47
#define NSFoundationVersionNumber_iPhoneOS_3_1  678.51
#define NSFoundationVersionNumber_iPhoneOS_3_2  678.60
#endif

#if __LP64__ || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64
typedef long NSInteger;
typedef unsigned long NSUInteger;
#else
typedef int NSInteger;
typedef unsigned int NSUInteger;
#endif

#define NSIntegerMax    LONG_MAX
#define NSIntegerMin    LONG_MIN
#define NSUIntegerMax   ULONG_MAX

#define NSINTEGER_DEFINED 1

@class NSString, Protocol;

FOUNDATION_EXPORT NSString *NSStringFromSelector(SEL aSelector);
FOUNDATION_EXPORT SEL NSSelectorFromString(NSString *aSelectorName);

FOUNDATION_EXPORT NSString *NSStringFromClass(Class aClass);
FOUNDATION_EXPORT Class NSClassFromString(NSString *aClassName);

FOUNDATION_EXPORT NSString *NSStringFromProtocol(Protocol *proto) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT Protocol *NSProtocolFromString(NSString *namestr) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

FOUNDATION_EXPORT const char *NSGetSizeAndAlignment(const char *typePtr, NSUInteger *sizep, NSUInteger *alignp);

FOUNDATION_EXPORT void NSLog(NSString *format, ...) NS_FORMAT_FUNCTION(1,2);
FOUNDATION_EXPORT void NSLogv(NSString *format, va_list args) NS_FORMAT_FUNCTION(1,0);

enum _NSComparisonResult {NSOrderedAscending = -1, NSOrderedSame, NSOrderedDescending};
typedef NSInteger NSComparisonResult;

#if NS_BLOCKS_AVAILABLE

typedef NSComparisonResult (^NSComparator)(id obj1, id obj2);

enum {
    NSEnumerationConcurrent = (1UL << 0),
    NSEnumerationReverse = (1UL << 1),
};
typedef NSUInteger NSEnumerationOptions;

enum {
    NSSortConcurrent = (1UL << 0),
    NSSortStable = (1UL << 4),
};
typedef NSUInteger NSSortOptions;

#endif


enum {NSNotFound = NSIntegerMax};

#if !defined(YES)
    #define YES	(BOOL)1
#endif

#if !defined(NO)
    #define NO	(BOOL)0
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

