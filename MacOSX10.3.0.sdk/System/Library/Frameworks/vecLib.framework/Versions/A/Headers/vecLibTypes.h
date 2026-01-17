/*
     File:       vecLib/vecLibTypes.h
 
     Contains:   Master include for vecLib framework
 
     Version:    Technology: MacOS X
                 Release:    vecLib-151~21
 
     Copyright:  © 2000-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VECLIBTYPES__
#define __VECLIBTYPES__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma options align=mac68k

#ifdef __ppc__
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

#elif defined(__i386__)
#ifdef __SSE__
typedef int __m128i __attribute__((mode(V4SI)));
typedef int __m128  __attribute__((mode(V4SF)));
typedef __m128i                         vUInt8;
typedef __m128i                         vSInt8;
typedef __m128i                         vUInt16;
typedef __m128i                         vSInt16;
typedef __m128i                         vUInt32;
typedef __m128i                         vSInt32;
typedef __m128                          vFloat;
typedef __m128i                         vBool32;
#endif  /* defined(__SSE__) */

#else
#error Unknown architecture
#endif  /*  */


#pragma options align=reset


#endif /* __VECLIBTYPES__ */

