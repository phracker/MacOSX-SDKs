/*
     File:       vecLib/vecLibTypes.h
 
     Contains:   Master include for vecLib framework
 
     Version:    vecLib-600.0
 
     Copyright:  Copyright (c) 2000-2016 by Apple Inc. All rights reserved.
 
     Bugs:       For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
     Various types are defined here to use with vecLib.  For more generally
     useful vector/SIMD types, please consider the headers in /usr/include/simd.
*/
#ifndef __VECLIBTYPES__
#define __VECLIBTYPES__


#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif


#pragma options align=power

#if defined(__ppc__) || defined(__ppc64__)


/*
    The goal of the following preprocessor statements is to define the
    preprocessor symbol _AltiVecPIMLanguageExtensionsAreEnabled if and only if
    the AltiVec high-level language programming interface is enabled.  We
    designed the statements to accommodate some non-Apple compilers but cannot
    assure behavior with non-Apple products.

    Apple GCC version 3.3 and earlier versions defined the preprocessor symbol
    __VEC__ if and only if the AltiVec programming interface were enabled.
    Later versions define __VEC__ when the AltiVec instruction set is enabled
    (and thus available for the compiler's assembly code generation) even if
    the programming interface is not enabled (and thus not available at the
    source code level).  This occurs, for example, when -maltivec is specified
    but neither -faltivec is specified nor <altivec.h> is included.

    Due to this change, code that formerly used __VEC__ to select source code
    with or without use of the AltiVec programming interface should now use
    _AltiVecPIMLanguageExtensionsAreEnabled.

    For more information about the interface, see AltiVec Technology
    Programming Interface Manual (ALTIVECPIM/D 6/1999 Rev. 0, published by
    Motorola Inc. [now Freescale, Inc.]).
 */

#if			defined _ALTIVEC_H \
		||	(defined __APPLE_CC__ && __APPLE_ALTIVEC__) \
		|| 	(!defined __GNUC__ && defined __VEC__)
	#define _AltiVecPIMLanguageExtensionsAreEnabled
#endif

#if defined _AltiVecPIMLanguageExtensionsAreEnabled
	typedef __vector unsigned char            vUInt8;
	typedef __vector signed char              vSInt8;
	typedef __vector unsigned short           vUInt16;
	typedef __vector signed short             vSInt16;
	typedef __vector unsigned int             vUInt32;
	typedef __vector signed int               vSInt32;
	typedef __vector float                    vFloat;
	typedef __vector bool int                 vBool32;

    /* 
     * GCC allows us to create a vDouble type, even on AltiVec which has no double precision vector 
     * instructions (apart from boolean operations which are type agnostic). You can use standard 
     * operators: +-* etc. with the vDouble type. GCC will use scalar code on PowerPC to do the work. 
     * The type is provided for developers interested in writing shared Intel-PowerPC code. 
     */
    #if defined(__GNUC__) && ! defined( __XLC__ )
        #if defined(__GNUC_MINOR__) && (((__GNUC__ == 3) && (__GNUC_MINOR__ <= 3)) || (__GNUC__ < 3))
        #else
            #define __VECLIBTYPES_VDOUBLE__ 1
            typedef double vDouble         __attribute__ ((__vector_size__ (16)));
        #endif
    #endif

#endif	/* defined _AltiVecPIMLanguageExtensionsAreEnabled */

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
    #define __VECLIBTYPES_VDOUBLE__ 1
    
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

#elif defined __arm__ && defined __ARM_NEON__

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
	typedef unsigned char  vUInt8  __attribute__((__vector_size__(16), __aligned__(16)));
	typedef signed char    vSInt8  __attribute__((__vector_size__(16), __aligned__(16)));
	typedef unsigned short vUInt16 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef signed short   vSInt16 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef unsigned int   vUInt32 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef signed int     vSInt32 __attribute__((__vector_size__(16), __aligned__(16)));
	typedef float          vFloat  __attribute__((__vector_size__(16), __aligned__(16)));
	typedef double         vDouble __attribute__((__vector_size__(16), __aligned__(16)));
	typedef unsigned int   vBool32 __attribute__((__vector_size__(16), __aligned__(16)));

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
