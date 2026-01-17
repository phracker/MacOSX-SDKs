/* CoreAnimation - CABase.h

   Copyright (c) 2006-2017, Apple Inc.
   All rights reserved. */

#ifndef CABASE_H
#define CABASE_H

/* Adapted from <CoreGraphics/CGBase.h> */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>

#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>

#include <Availability.h>
#include <TargetConditionals.h>

#define GET_CA_AVAIL_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define GET_CA_AVAIL_IOS_MACRO(_1,_2,_3,NAME,...) NAME
#define CA_CLASS_AVAILABLE(...) __attribute__((visibility("default"))) GET_CA_AVAIL_MACRO(__VA_ARGS__, CA_AVAILABLE_STARTING4, CA_AVAILABLE_STARTING3, CA_AVAILABLE_STARTING2, CA_AVAILABLE_STARTING1)(__VA_ARGS__)
#define CA_AVAILABLE_STARTING(...) GET_CA_AVAIL_MACRO(__VA_ARGS__, CA_AVAILABLE_STARTING4, CA_AVAILABLE_STARTING3, CA_AVAILABLE_STARTING2, CA_AVAILABLE_STARTING1)(__VA_ARGS__)
#define CA_AVAILABLE_STARTING1(m) __OSX_AVAILABLE(m)
#define CA_AVAILABLE_STARTING2(m,i) __OSX_AVAILABLE(m) __IOS_AVAILABLE(i)
#define CA_AVAILABLE_STARTING3(m,i,t) __OSX_AVAILABLE(m) __IOS_AVAILABLE(i) __TVOS_AVAILABLE(t)
#define CA_AVAILABLE_STARTING4(m,i,t,w) __OSX_AVAILABLE(m) __IOS_AVAILABLE(i) __TVOS_AVAILABLE(t) __WATCHOS_AVAILABLE(w)

#define CA_CLASS_AVAILABLE_IOS(...) __attribute__((visibility("default"))) GET_CA_AVAIL_IOS_MACRO(__VA_ARGS__, CA_AVAILABLE_IOS_STARTING3, CA_AVAILABLE_IOS_STARTING2, CA_AVAILABLE_IOS_STARTING1)(__VA_ARGS__)
#define CA_AVAILABLE_IOS_STARTING(...) GET_CA_AVAIL_IOS_MACRO(__VA_ARGS__, CA_AVAILABLE_IOS_STARTING3, CA_AVAILABLE_IOS_STARTING2, CA_AVAILABLE_IOS_STARTING1)(__VA_ARGS__)
#define CA_AVAILABLE_IOS_STARTING1(i) __IOS_AVAILABLE(i)
#define CA_AVAILABLE_IOS_STARTING2(i,t) __IOS_AVAILABLE(i) __TVOS_AVAILABLE(t)
#define CA_AVAILABLE_IOS_STARTING3(i,t,w) __IOS_AVAILABLE(i) __TVOS_AVAILABLE(t) __WATCHOS_AVAILABLE(w)

#define GET_CA_AVAIL_BUT_DEPR_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,NAME,...) NAME
#define GET_CA_AVAIL_BUT_DEPR_IOS_MACRO(_1,_2,_3,_4,_5,_6,_7,NAME,...) NAME
#define CA_AVAILABLE_BUT_DEPRECATED(...) GET_CA_AVAIL_BUT_DEPR_MACRO(__VA_ARGS__, CA_AVAILABLE_BUT_DEPRECATED9, CA_AVAILABLE_BUT_DEPRECATED8, CA_AVAILABLE_BUT_DEPRECATED7, CA_AVAILABLE_BUT_DEPRECATED6, CA_AVAILABLE_BUT_DEPRECATED5, CA_AVAILABLE_BUT_DEPRECATED4, CA_AVAILABLE_BUT_DEPRECATED3, CA_AVAILABLE_BUT_DEPRECATED2, CA_AVAILABLE_BUT_DEPRECATED1)(__VA_ARGS__)
#define CA_AVAILABLE_BUT_DEPRECATED1(m0)
#define CA_AVAILABLE_BUT_DEPRECATED2(m0,m1)
#define CA_AVAILABLE_BUT_DEPRECATED3(m0,m1,w) __OSX_DEPRECATED(m0,m1,w)
#define CA_AVAILABLE_BUT_DEPRECATED4(m0,m1,i0,i1)
#define CA_AVAILABLE_BUT_DEPRECATED5(m0,m1,i0,i1,w) __OSX_DEPRECATED(m0,m1,w) __IOS_DEPRECATED(i0,i1,w)
#define CA_AVAILABLE_BUT_DEPRECATED6(m0,m1,i0,i1,t0,t1)
#define CA_AVAILABLE_BUT_DEPRECATED7(m0,m1,i0,i1,t0,t1,w) __OSX_DEPRECATED(m0,m1,w) __IOS_DEPRECATED(i0,i1,w) __TVOS_DEPRECATED(t0,t1,w)
#define CA_AVAILABLE_BUT_DEPRECATED8(m0,m1,i0,i1,t0,t1,w0,w1)
#define CA_AVAILABLE_BUT_DEPRECATED9(m0,m1,i0,i1,t0,t1,w0,w1,w) __OSX_DEPRECATED(m0,m1,w) __IOS_DEPRECATED(i0,i1,w) __TVOS_DEPRECATED(t0,t1,w) __WATCHOS_DEPRECATED(w0,w1,w)

#define CA_AVAILABLE_BUT_DEPRECATED_IOS(...) GET_CA_AVAIL_BUT_DEPR_IOS_MACRO(__VA_ARGS__, CA_AVAILABLE_BUT_DEPRECATED_IOS7, CA_AVAILABLE_BUT_DEPRECATED_IOS6, CA_AVAILABLE_BUT_DEPRECATED_IOS5, CA_AVAILABLE_BUT_DEPRECATED_IOS4, CA_AVAILABLE_BUT_DEPRECATED_IOS3, CA_AVAILABLE_BUT_DEPRECATED_IOS2, CA_AVAILABLE_BUT_DEPRECATED_IOS1)(__VA_ARGS__)
#define CA_AVAILABLE_BUT_DEPRECATED_IOS1(i0)
#define CA_AVAILABLE_BUT_DEPRECATED_IOS2(i0,i1)
#define CA_AVAILABLE_BUT_DEPRECATED_IOS3(i0,i1,w) __IOS_DEPRECATED(i0,i1,w)
#define CA_AVAILABLE_BUT_DEPRECATED_IOS4(i0,i1,t0,t1)
#define CA_AVAILABLE_BUT_DEPRECATED_IOS5(i0,i1,t0,t1,w) __IOS_DEPRECATED(i0,i1,w) __TVOS_DEPRECATED(t0,t1,w)
#define CA_AVAILABLE_BUT_DEPRECATED_IOS6(i0,i1,t0,t1,w0,w1)
#define CA_AVAILABLE_BUT_DEPRECATED_IOS7(i0,i1,t0,t1,w0,w1,w) __IOS_DEPRECATED(i0,i1,w) __TVOS_DEPRECATED(t0,t1,w) __WATCHOS_DEPRECATED(w0,w1,w)

#ifdef CA_BUILDING_CA
# undef __OSX_AVAILABLE_STARTING
# undef __OSX_AVAILABLE_BUT_DEPRECATED
# undef CA_AVAILABLE_STARTING
# undef CA_AVAILABLE_IOS_STARTING
# undef CA_AVAILABLE_BUT_DEPRECATED_STARTING
# undef CA_AVAILABLE_BUT_DEPREDATED_IOS
#endif
#ifndef __OSX_AVAILABLE_STARTING
# define __OSX_AVAILABLE_STARTING(m0,i)
# define __OSX_AVAILABLE_BUT_DEPRECATED(m0,m1,i0,i1)
# define CA_AVAILABLE_STARTING(...)
# define CA_AVAILABLE_IOS_STARTING(...)
# define CA_AVAILABLE_BUT_DEPRECATED_STARTING(...)
# define CA_AVAILABLE_BUT_DEPREDATED_IOS(...)
#endif

#if TARGET_OS_OSX
# define CA_OSX_VERSION(v) ((v) > 0 && MAC_OS_X_VERSION_MIN_REQUIRED >= (v))
#else
# define CA_OSX_VERSION(v) (0)
#endif

#if TARGET_OS_IPHONE
# define CA_IOS_VERSION(v) ((v) > 0 && __IPHONE_OS_VERSION_MIN_REQUIRED >= (v))
#else
# define CA_IOS_VERSION(v) (0)
#endif

#if TARGET_OS_TV
# define CA_TV_VERSION(v) ((v) > 0 && __TV_OS_VERSION_MIN_REQUIRED >= (v))
#else
# define CA_TV_VERSION(v) (0)
#endif

#if TARGET_OS_WATCH
# define CA_WATCH_VERSION(v) ((v) > 0 && __WATCH_OS_VERSION_MIN_REQUIRED >= (v))
#else
# define CA_WATCH_VERSION(v) (0)
#endif

#ifdef __cplusplus
# define CA_EXTERN_C_BEGIN extern "C" {
# define CA_EXTERN_C_END   }
#else
# define CA_EXTERN_C_BEGIN
# define CA_EXTERN_C_END
#endif

#ifdef __GNUC__
# define CA_GNUC(major, minor) \
  (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
#else
# define CA_GNUC(major, minor) 0
#endif

#ifndef CA_EXTERN
# define CA_EXTERN extern __attribute__((visibility("default")))
#endif

#ifndef CA_INLINE
# if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define CA_INLINE static inline
# elif defined (__cplusplus)
#  define CA_INLINE static inline
# elif CA_GNUC (3, 0)
#  define CA_INLINE static __inline__ __attribute__ ((always_inline))
# else
#  define CA_INLINE static
# endif
#endif

#ifndef CA_HIDDEN
# if CA_GNUC (4,0)
#  define CA_HIDDEN __attribute__ ((visibility ("hidden")))
# else
#  define CA_HIDDEN /* no hidden */
# endif
#endif

#ifndef CA_PURE
# if CA_GNUC (3, 0)
#  define CA_PURE __attribute__ ((pure))
# else
#  define CA_PURE /* no pure */
# endif
#endif

#ifndef CA_CONST
# if CA_GNUC (3, 0)
#  define CA_CONST __attribute__ ((const))
# else
#  define CA_CONST /* no const */
# endif
#endif

#ifndef CA_NORETURN
# if CA_GNUC (3, 0)
#  define CA_NORETURN __attribute__ ((noreturn))
# else
#  define CA_NORETURN /* no noreturn */
# endif
#endif

#ifndef CA_MALLOC
# if CA_GNUC (3, 0)
#  define CA_MALLOC __attribute__ ((malloc))
# else
#  define CA_MALLOC /* no malloc */
# endif
#endif

#ifndef CA_WARN_UNUSED
# if CA_GNUC (3, 4)
#  define CA_WARN_UNUSED __attribute__ ((warn_unused_result))
# else
#  define CA_WARN_UNUSED /* no warn_unused */
# endif
#endif

#ifndef CA_WARN_DEPRECATED
# define CA_WARN_DEPRECATED 1
#endif

#ifndef CA_DEPRECATED
# if CA_GNUC (3, 0) && CA_WARN_DEPRECATED
#  define CA_DEPRECATED __attribute__ ((deprecated))
# else
#  define CA_DEPRECATED
# endif
#endif

CA_EXTERN_C_BEGIN

/* Returns the current CoreAnimation absolute time. This is the result of
 * calling mach_absolute_time () and converting the units to seconds. */

CA_EXTERN CFTimeInterval CACurrentMediaTime (void)
    __OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);

CA_EXTERN_C_END

#endif /* CABASE_H */
