/*
     File:       vecLib/vecLibTypes.h
 
     Contains:   Master include for vecLib framework
 
     Version:    vecLib-794.100
 
     Copyright:  Copyright (c) 2000-2022 by Apple Inc. All rights reserved.
 
     Bugs:       For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
     Various types are defined here to use with vecLib.  For more generally
     useful vector/SIMD types, please consider the headers in /usr/include/simd.
*/
#ifndef __VECLIBTYPES__
#define __VECLIBTYPES__

#include <os/availability.h>

#if PRAGMA_ONCE
#pragma once
#endif


#pragma options align=power

#if defined(__i386__) || defined(__x86_64__)
#include <immintrin.h>
#ifdef __SSE__
#if defined(__GNUC__)
typedef float                   vFloat          __attribute__ ((__vector_size__ (16)));
#else /* not __GNUC__ */
typedef __m128                          vFloat;
#endif /* __GNUC__ */
#endif  /* defined(__SSE__) */

#ifdef __SSE2__
    #define __VECLIBTYPES_VDOUBLE__ 1
    
    #if defined(__GNUC__)
        #if defined(__GNUC_MINOR__) && (((__GNUC__ == 3) && (__GNUC_MINOR__ <= 3)) || (__GNUC__ < 3))
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

#elif ( defined __arm__ || defined __arm64__ ) && defined __ARM_NEON__

	#if !defined ARM_NEON_GCC_COMPATIBILITY  

		#define ARM_NEON_GCC_COMPATIBILITY

		#if \
			defined __ARM_NEON_H && \
			defined __GNUC__ && \
			! defined __clang__ && \
			! defined SQUELCH_VECLIB_WARNINGS_ABOUT_BROKEN_NEON_TYPES

			/*	GCC decided to make neon vector types using something other
				than basic C types as the underlying element by default. This
				prevents the below types from being used with the functions in
				arm_neon.h.  GCC did put in a workaround, however.  Define
				ARM_NEON_GCC_COMPATIBILITY before including arm_neon.h and then
				everything will start working as designed. You are getting this
				warning  because some other header included arm_neon.h without
				defining ARM_NEON_GCC_COMPATIBILITY before we arrived here. 

				#define SQUELCH_VECLIB_WARNINGS_ABOUT_BROKEN_NEON_TYPES to silence this warning
			*/
			#warning "arm_neon.h was included without #define ARM_NEON_GCC_COMPATIBILITY.  Vector types defined in vecLibTypes.h, such as vUInt8, might not work with NEON intrinsics."

		#endif

	#endif	/* !defined ARM_NEON_GCC_COMPATIBILITY */

	#include <arm_neon.h>
	typedef unsigned char  		vUInt8  __attribute__((__vector_size__(16), __aligned__(16)));
	typedef signed char    		vSInt8  __attribute__((__vector_size__(16), __aligned__(16)));
	typedef unsigned short 		vUInt16 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef signed short   		vSInt16 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef unsigned int   		vUInt32 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef signed int     		vSInt32 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef unsigned long long 	vUInt64 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef long long      		vSInt64 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef float          		vFloat  __attribute__((__vector_size__(16), __aligned__(16)));
	typedef double         		vDouble __attribute__((__vector_size__(16), __aligned__(16)));
	typedef unsigned int   		vBool32 __attribute__((__vector_size__(16), __aligned__(16)));

#else

	typedef unsigned char       vUInt8  __attribute__((__vector_size__(16)));
	typedef signed char         vSInt8  __attribute__((__vector_size__(16)));
	typedef unsigned short      vUInt16 __attribute__((__vector_size__(16)));
	typedef signed short        vSInt16 __attribute__((__vector_size__(16)));
	typedef unsigned int        vUInt32 __attribute__((__vector_size__(16)));
	typedef signed int          vSInt32 __attribute__((__vector_size__(16)));
    typedef long long           vSInt64 __attribute__((__vector_size__(16)));
    typedef unsigned long long  vUInt64 __attribute__((__vector_size__(16)));
	typedef float               vFloat  __attribute__((__vector_size__(16)));
	typedef double              vDouble __attribute__((__vector_size__(16)));
	typedef unsigned int        vBool32 __attribute__((__vector_size__(16)));

#endif


#pragma options align=reset


#endif /* __VECLIBTYPES__ */
