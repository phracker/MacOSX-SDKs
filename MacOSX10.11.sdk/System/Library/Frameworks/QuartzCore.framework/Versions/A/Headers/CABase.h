/* CoreAnimation - CABase.h

   Copyright (c) 2006-2015, Apple Inc.
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

/* The earliest Mac SDK we support is 10.9 */

#ifndef __MAC_10_10
# define __MAC_10_10    101000
#endif
#ifndef __MAC_10_10_2
# define __MAC_10_10_2  101002
#endif
#ifndef __MAC_10_10_3
# define __MAC_10_10_3  101003
#endif
#ifndef __MAC_10_11
# define __MAC_10_11    101100
#endif

/* The earliest iOS SDK we support is 7.0 */

#ifndef __IPHONE_7_1
# define __IPHONE_7_1   70100
#endif
#ifndef __IPHONE_8_0
# define __IPHONE_8_0   80000
#endif
#ifndef __IPHONE_8_1
# define __IPHONE_8_1   80100
#endif
#ifndef __IPHONE_8_2
# define __IPHONE_8_2   80200
#endif
#ifndef __IPHONE_8_3
# define __IPHONE_8_3   80300
#endif
#ifndef __IPHONE_8_4
# define __IPHONE_8_4   80400
#endif
#ifndef __IPHONE_9_0
# define __IPHONE_9_0   90000
#endif

#ifdef CA_BUILDING_CA
# undef __OSX_AVAILABLE_STARTING
# undef __OSX_AVAILABLE_BUT_DEPRECATED
#endif
#ifndef __OSX_AVAILABLE_STARTING
# define __OSX_AVAILABLE_STARTING(m,i)
# define __OSX_AVAILABLE_BUT_DEPRECATED(m0,m1,i0,i1)
#endif

#if !TARGET_OS_IPHONE
#define CA_OS_VERSION(m, i) ((m) > 0 && MAC_OS_X_VERSION_MIN_REQUIRED >= (m))
#else
#define CA_OS_VERSION(m, i) ((i) > 0 && __IPHONE_OS_VERSION_MIN_REQUIRED >= (i))
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
# define CA_EXTERN extern
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
