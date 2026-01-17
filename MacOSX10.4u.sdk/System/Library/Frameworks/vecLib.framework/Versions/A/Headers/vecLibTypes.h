/*
     File:       vecLib/vecLibTypes.h
 
     Contains:   Master include for vecLib framework
 
     Version:    vecLib-192.17
 
     Copyright:  © 2000-2007 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VECLIBTYPES__
#define __VECLIBTYPES__


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma options align=power

#if defined(__ppc__) || defined(__ppc64__)
#ifdef __VEC__
typedef vector unsigned char            vUInt8;
typedef vector signed char              vSInt8;
typedef vector unsigned short           vUInt16;
typedef vector signed short             vSInt16;
typedef vector unsigned int             vUInt32;
typedef vector signed int               vSInt32;
typedef vector float                    vFloat;
typedef vector bool int vBool32;
#endif  /* defined(__VEC__) */

#elif defined(__i386__) || defined(__x86_64__)
#ifdef __SSE__
#if defined(__GNUC__)
#include <xmmintrin.h>
typedef float                   vFloat          __attribute__ ((__vector_size__ (16)));
#else /* not __GNUC__ */
#include <xmmintrin.h>
typedef __m128                          vFloat;
#endif /* __GNUC__ */
#endif  /* defined(__SSE__) */

#ifdef __SSE2__
#if defined(__GNUC__)
#if defined(__GNUC_MINOR__) && (((__GNUC__ == 3) && (__GNUC_MINOR__ <= 3)) || (__GNUC__ < 3))
#include <xmmintrin.h>
typedef __m128i vUInt8;
typedef __m128i vSInt8;
typedef __m128i vUInt16;
typedef __m128i vSInt16;
typedef __m128i vUInt32;
typedef __m128i vSInt32;
typedef __m128i vBool32;
typedef __m128i vUInt64;
typedef __m128i vSInt64;
typedef __m128d vDouble;
#else /* gcc-3.5 or later */
#include <emmintrin.h>
typedef unsigned char           vUInt8          __attribute__ ((__vector_size__ (16)));
typedef char                    vSInt8          __attribute__ ((__vector_size__ (16)));
typedef unsigned short          vUInt16         __attribute__ ((__vector_size__ (16)));
typedef short                   vSInt16         __attribute__ ((__vector_size__ (16)));
typedef unsigned int            vUInt32         __attribute__ ((__vector_size__ (16)));
typedef int                     vSInt32         __attribute__ ((__vector_size__ (16)));
typedef unsigned int            vBool32         __attribute__ ((__vector_size__ (16)));
typedef unsigned long long      vUInt64         __attribute__ ((__vector_size__ (16)));
typedef long long               vSInt64         __attribute__ ((__vector_size__ (16)));
typedef double                  vDouble         __attribute__ ((__vector_size__ (16)));
#endif /* __GNUC__ <= 3.3 */
#else /* not __GNUC__ */
#include <emmintrin.h>
typedef __m128i                         vUInt8;
typedef __m128i                         vSInt8;
typedef __m128i                         vUInt16;
typedef __m128i                         vSInt16;
typedef __m128i                         vUInt32;
typedef __m128i                         vSInt32;
typedef __m128i                         vBool32;
typedef __m128i                         vUInt64;
typedef __m128i                         vSInt64;
typedef __m128d                         vDouble;
#endif /* __GNUC__ */
#endif  /* defined(__SSE2__) */

#else
#error Unknown architecture
#endif  /*  */


#pragma options align=reset


#endif /* __VECLIBTYPES__ */

