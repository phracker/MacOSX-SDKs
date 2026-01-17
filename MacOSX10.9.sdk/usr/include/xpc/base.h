// Copyright (c) 2009-2011 Apple Inc. All rights reserved.

#ifndef __XPC_BASE_H__
#define __XPC_BASE_H__

#include <sys/cdefs.h>

__BEGIN_DECLS

// Certain parts of the project use all the project's headers but have to build
// against Zin -- liblaunch_host being the example. So we need to define these.
#ifndef __MAC_10_9
#define __MAC_10_9 1090
#define __AVAILABILITY_INTERNAL__MAC_10_9 \
	__attribute__((availability(macosx, introduced=10.9)))
#endif

#ifndef __IPHONE_7_0
#define __IPHONE_7_0 70000
#define __AVAILABILITY_INTERNAL__IPHONE_7_0 \
	__attribute__((availability(ios, introduced=7.0)))
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_9
#define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_9
#endif // __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_9

#ifndef __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_9
#define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_9
#endif // __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_9

#ifndef __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_9
#define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_9
#endif // __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_9

#ifndef __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_9
#define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_9
#endif // __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_9

#if !defined(__has_include)
#define __has_include(x) 0
#endif

#if !defined(__has_attribute)
#define __has_attribute(x) 0
#endif

#if __has_include(<xpc/availability.h>)
#include <xpc/availability.h>
#else
#include <Availability.h>
#define __XPC_IOS_SIMULATOR_AVAILABLE_STARTING(version)
#endif

#ifndef __XPC_INDIRECT__
#error "Please #include <xpc/xpc.h> instead of this file directly."
#endif // __XPC_INDIRECT__ 

#pragma mark Attribute Shims
#ifdef __GNUC__
#define XPC_CONSTRUCTOR __attribute__((constructor))
#define XPC_NORETURN __attribute__((__noreturn__))
#define XPC_NOTHROW __attribute__((__nothrow__))
#define XPC_NONNULL1 __attribute__((__nonnull__(1)))
#define XPC_NONNULL2 __attribute__((__nonnull__(2)))
#define XPC_NONNULL3 __attribute__((__nonnull__(3)))
#define XPC_NONNULL4 __attribute__((__nonnull__(4)))
#define XPC_NONNULL5 __attribute__((__nonnull__(5)))
#define XPC_NONNULL6 __attribute__((__nonnull__(6)))
#define XPC_NONNULL7 __attribute__((__nonnull__(7)))
#define XPC_NONNULL8 __attribute__((__nonnull__(8)))
#define XPC_NONNULL9 __attribute__((__nonnull__(9)))
#define XPC_NONNULL10 __attribute__((__nonnull__(10)))
#define XPC_NONNULL11 __attribute__((__nonnull__(11)))
#define XPC_NONNULL_ALL __attribute__((__nonnull__))
#define XPC_SENTINEL __attribute__((__sentinel__))
#define XPC_PURE __attribute__((__pure__))
#define XPC_WARN_RESULT __attribute__((__warn_unused_result__))
#define XPC_MALLOC __attribute__((__malloc__))
#define XPC_UNUSED __attribute__((unused))
#define XPC_USED __attribute__((used))
#define XPC_PACKED __attribute__((__packed__))
#define XPC_PRINTF(m, n) __attribute__((format(printf, m, n)))
#define XPC_INLINE static __inline__ __attribute__((__always_inline__))
#define XPC_NOINLINE __attribute__((noinline))
#define XPC_NOIMPL __attribute__((unavailable))

#if __has_extension(attribute_unavailable_with_message)
#define XPC_UNAVAILABLE(m) __attribute__((unavailable(m)))
#else // __has_extension(attribute_unavailable_with_message)
#define XPC_UNAVAILABLE(m) XPC_NOIMPL
#endif // __has_extension(attribute_unavailable_with_message)

#define XPC_EXPORT extern __attribute__((visibility("default")))
#define XPC_NOEXPORT __attribute__((visibility("hidden")))
#define XPC_WEAKIMPORT extern __attribute__((weak_import))
#define XPC_DEBUGGER_EXCL XPC_NOEXPORT XPC_USED
#define XPC_TRANSPARENT_UNION __attribute__((transparent_union))
#if __clang__
#define XPC_DEPRECATED(m)	__attribute__((deprecated(m)))
#else
#define XPC_DEPRECATED(m)	__attribute__((deprecated))
#endif // __clang 

#if __OBJC__
#define XPC_GIVES_REFERENCE __strong
#define XPC_UNRETAINED __unsafe_unretained
#define XPC_BRIDGE(xo) ((__bridge void *)(xo))
#define XPC_BRIDGEREF_BEGIN(xo) ((__bridge_retained void *)(xo))
#define XPC_BRIDGEREF_BEGIN_WITH_REF(xo) ((__bridge void *)(xo))
#define XPC_BRIDGEREF_MIDDLE(xo) ((__bridge id)(xo))
#define XPC_BRIDGEREF_END(xo) ((__bridge_transfer id)(xo))
#else // __OBJC__
#define XPC_GIVES_REFERENCE
#define XPC_UNRETAINED
#define XPC_BRIDGE(xo)
#define XPC_BRIDGEREF_BEGIN(xo) (xo)
#define XPC_BRIDGEREF_BEGIN_WITH_REF(xo) (xo)
#define XPC_BRIDGEREF_MIDDLE(xo) (xo)
#define XPC_BRIDGEREF_END(xo) (xo)
#endif // __OBJC__
#else // __GNUC__ 
/*! @parseOnly */
#define XPC_CONSTRUCTOR
/*! @parseOnly */
#define XPC_NORETURN
/*! @parseOnly */
#define XPC_NOTHROW
/*! @parseOnly */
#define XPC_NONNULL1
/*! @parseOnly */
#define XPC_NONNULL2
/*! @parseOnly */
#define XPC_NONNULL3
/*! @parseOnly */
#define XPC_NONNULL4
/*! @parseOnly */
#define XPC_NONNULL5
/*! @parseOnly */
#define XPC_NONNULL6
/*! @parseOnly */
#define XPC_NONNULL7
/*! @parseOnly */
#define XPC_NONNULL8
/*! @parseOnly */
#define XPC_NONNULL9
/*! @parseOnly */
#define XPC_NONNULL10
/*! @parseOnly */
#define XPC_NONNULL11
/*! @parseOnly */
#define XPC_NONNULL(n)
/*! @parseOnly */
#define XPC_NONNULL_ALL
/*! @parseOnly */
#define XPC_SENTINEL
/*! @parseOnly */
#define XPC_PURE
/*! @parseOnly */
#define XPC_WARN_RESULT
/*! @parseOnly */
#define XPC_MALLOC
/*! @parseOnly */
#define XPC_UNUSED
/*! @parseOnly */
#define XPC_PACKED
/*! @parseOnly */
#define XPC_PRINTF(m, n)
/*! @parseOnly */
#define XPC_INLINE static inline
/*! @parseOnly */
#define XPC_NOINLINE
/*! @parseOnly */
#define XPC_NOIMPL
/*! @parseOnly */
#define XPC_EXPORT extern
/*! @parseOnly */
#define XPC_WEAKIMPORT
/*! @parseOnly */
#define XPC_DEPRECATED
/*! @parseOnly */
#define XPC_UNAVAILABLE(m)
#endif // __GNUC__ 

#define XPC_PROJECT_EXPORT XPC_EXPORT

__END_DECLS

#endif // __XPC_BASE_H__ 
