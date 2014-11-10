/*
 * "$Id: versioning.h 11468 2013-12-18 20:31:42Z msweet $"
 *
 *   API versioning definitions for CUPS.
 *
 *   Copyright 2007-2013 by Apple Inc.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_VERSIONING_H_
#  define _CUPS_VERSIONING_H_

/*
 * This header defines several constants - _CUPS_DEPRECATED,
 * _CUPS_DEPRECATED_MSG, _CUPS_INTERNAL_MSG, _CUPS_API_1_1, _CUPS_API_1_1_19,
 * _CUPS_API_1_1_20, _CUPS_API_1_1_21, _CUPS_API_1_2, _CUPS_API_1_3,
 * _CUPS_API_1_4, _CUPS_API_1_5, _CUPS_API_1_6, _CUPS_API_1_7, and
 * _CUPS_API_2_0 - which add compiler-specific attributes that flag functions
 * that are deprecated, added in particular releases, or internal to CUPS.
 *
 * On OS X, the _CUPS_API_* constants are defined based on the values of
 * the MAC_OS_X_VERSION_MIN_ALLOWED and MAC_OS_X_VERSION_MAX_ALLOWED constants
 * provided by the compiler.
 */

#  if defined(__APPLE__) && !defined(_CUPS_SOURCE)
#    include <AvailabilityMacros.h>
#    ifndef AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#      define AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER __attribute__((unavailable))
#    endif /* !AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER */
#    ifndef AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
#      define AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER __attribute__((unavailable))
#    endif /* !AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER */
#    ifndef AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
#      define AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER __attribute__((unavailable))
#    endif /* !AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER */
#    ifndef AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER
#      define AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER __attribute__((unavailable))
#    endif /* !AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER */
#    ifndef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER
#      define AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER __attribute__((unavailable))
#    endif /* !AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER */
#    ifndef AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER
#      define AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER __attribute__((unavailable))
#    endif /* !AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER */
#    ifndef AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER
#      define AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER __attribute__((unavailable))
#    endif /* !AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER */
#    define _CUPS_API_1_1_19 AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#    define _CUPS_API_1_1_20 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
#    define _CUPS_API_1_1_21 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
#    define _CUPS_API_1_2 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
#    define _CUPS_API_1_3 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
#    define _CUPS_API_1_4 AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER
#    define _CUPS_API_1_5 AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER
#    define _CUPS_API_1_6 AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER
#    define _CUPS_API_1_7 AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER
#    define _CUPS_API_2_0
#  else
#    define _CUPS_API_1_1_19
#    define _CUPS_API_1_1_20
#    define _CUPS_API_1_1_21
#    define _CUPS_API_1_2
#    define _CUPS_API_1_3
#    define _CUPS_API_1_4
#    define _CUPS_API_1_5
#    define _CUPS_API_1_6
#    define _CUPS_API_1_7
#    define _CUPS_API_2_0
#  endif /* __APPLE__ && !_CUPS_SOURCE */

/*
 * With GCC and Clang we can mark old APIs as "deprecated" or "unavailable" with
 * messages so you get warnings/errors are compile-time...
 */

#  ifdef __has_extension		/* Clang */
#    define _CUPS_HAS_DEPRECATED
#    if __has_extension(attribute_deprecated_with_message)
#      define _CUPS_HAS_DEPRECATED_WITH_MESSAGE
#    endif
#    if __has_extension(attribute_unavailable_with_message)
#      define _CUPS_HAS_UNAVAILABLE_WITH_MESSAGE
#    endif
#  elif defined(__GNUC__)		/* GCC and compatible */
#    if __GNUC__ >= 3			/* GCC 3.0 or higher */
#      define _CUPS_HAS_DEPRECATED
#    endif /* __GNUC__ >= 3 */
#    if __GNUC__ >= 5			/* GCC 5.x */
#      define _CUPS_HAS_DEPRECATED_WITH_MESSAGE
#    elif __GNUC__ == 4 && __GNUC_MINOR__ >= 5
					/* GCC 4.5 or higher */
#      define _CUPS_HAS_DEPRECATED_WITH_MESSAGE
#    endif /* __GNUC__ >= 5 */
#  endif /* __has_extension */

#  if !defined(_CUPS_HAS_DEPRECATED) || (defined(_CUPS_SOURCE) && !defined(_CUPS_NO_DEPRECATED))
    /*
     * Don't mark functions deprecated if the compiler doesn't support it
     * or we are building CUPS source that doesn't care.
     */
#    define _CUPS_DEPRECATED
#    define _CUPS_DEPRECATED_MSG(m)
#    define _CUPS_DEPRECATED_1_6_MSG(m)
#    define _CUPS_DEPRECATED_1_7_MSG(m)
#    define _CUPS_INTERNAL_MSG(m)
#  elif defined(_CUPS_HAS_UNAVAILABLE_WITH_MESSAGE) && defined(_CUPS_NO_DEPRECATED)
    /*
     * Compiler supports the unavailable attribute, so use it when the code
     * wants to exclude the use of deprecated API.
     */
#    define _CUPS_DEPRECATED __attribute__ ((unavailable))
#    define _CUPS_DEPRECATED_MSG(m) __attribute__ ((unavailable(m)))
#    define _CUPS_DEPRECATED_1_6_MSG(m) __attribute__ ((unavailable(m)))
#    define _CUPS_DEPRECATED_1_7_MSG(m) __attribute__ ((unavailable(m)))
#    define _CUPS_INTERNAL_MSG(m) __attribute__ ((unavailable(m)))
#  else
    /*
     * Compiler supports the deprecated attribute, so use it.
     */
#    define _CUPS_DEPRECATED __attribute__ ((deprecated))
#    ifdef _CUPS_HAS_DEPRECATED_WITH_MESSAGE
#      define _CUPS_DEPRECATED_MSG(m) __attribute__ ((deprecated(m)))
#    else
#      define _CUPS_DEPRECATED_MSG(m) __attribute__ ((deprecated))
#    endif /* _CUPS_HAS_DEPRECATED_WITH_MESSAGE */
#    if defined(MAC_OS_X_VERSION_10_8) && MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_8
#      define _CUPS_DEPRECATED_1_6_MSG(m) _CUPS_DEPRECATED_MSG(m)
#    else
#      define _CUPS_DEPRECATED_1_6_MSG(m)
#    endif /* MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_8 */
#    if defined(MAC_OS_X_VERSION_10_9) && MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_9
#      define _CUPS_DEPRECATED_1_7_MSG(m) _CUPS_DEPRECATED_MSG(m)
#    else
#      define _CUPS_DEPRECATED_1_7_MSG(m)
#    endif /* MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_9 */
#    ifdef _CUPS_SOURCE
#      define _CUPS_INTERNAL_MSG(m)
#    elif defined(_CUPS_HAS_UNAVAILABLE_WITH_MESSAGE)
#      define _CUPS_INTERNAL_MSG(m) __attribute__ ((unavailable(m)))
#    elif defined(_CUPS_HAS_DEPRECATED_WITH_MESSAGE)
#      define _CUPS_INTERNAL_MSG(m) __attribute__ ((deprecated(m)))
#    else
#      define _CUPS_INTERNAL_MSG(m) __attribute__ ((deprecated))
#    endif /* _CUPS_SOURCE */
#  endif /* !_CUPS_HAS_DEPRECATED || (_CUPS_SOURCE && !_CUPS_NO_DEPRECATED) */

#  ifndef __GNUC__
#    define __attribute__(x)
#  endif /* !__GNUC__ */

#endif /* !_CUPS_VERSIONING_H_ */

/*
 * End of "$Id: versioning.h 11468 2013-12-18 20:31:42Z msweet $".
 */
