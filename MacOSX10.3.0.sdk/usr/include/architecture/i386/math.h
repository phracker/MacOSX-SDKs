/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
 
/*******************************************************************************
*                                                                              *
*     File:  math.h	                                                       *
*                                                                              *
*     Contains: typedefs, prototypes, and macros germane to C99 floating point.*
*                                                                              *
*******************************************************************************/
#ifndef __MATH__
#define __MATH__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*       Floating point data types                                             *
******************************************************************************/

/* ix87 FPU evaluates all quantities in the 80-bit long double format. */
typedef long double	float_t;
typedef long double	double_t;

#define	HUGE_VAL	1e500
#define	HUGE_VALF	1e50f
#define	HUGE_VALL	1e5000

#define INFINITY	HUGE_VALF

#if defined(__APPLE_CC__) && (__APPLE_CC__ >= 1345)
#define NAN		__builtin_nanf("0x7fc00000") /* Constant expression, can be used as initializer. */
#else
#define NAN		__nan( )
#endif

/******************************************************************************
*      Taxonomy of floating point data types                                  *
******************************************************************************/

enum {
	FP_NAN          = 1,                   /*      NaN                    */
	FP_INFINITE     = 2,                   /*      + or - infinity        */
	FP_ZERO         = 3,                   /*      + or - zero            */
	FP_NORMAL       = 4,                   /*      all normal numbers     */
	FP_SUBNORMAL    = 5                    /*      denormal numbers       */
};

/* "Fused" multiply-add is not supported on Intel as a single fast opcode. */
#define FP_FAST_FMA	0
#define FP_FAST_FMAF	0

/* The values returned by `ilogb' for 0 and NaN respectively.  */
#define FP_ILOGB0	(-2147483647 - 1)
#define FP_ILOGBNAN	(-2147483647 - 1)

/* Bitmasks for the math_errhandling macro.  */
#define MATH_ERRNO	1	/* errno set by math functions.  */
#define MATH_ERREXCEPT	2	/* Exceptions raised by math functions.  */

#define math_errhandling (__math_errhandling())
extern unsigned int __math_errhandling ( void );

/********************************************************************************
*                                                                               *
*                              Inquiry macros                                   *
*                                                                               *
*   fpclassify      Returns one of the FP_Å values.                             *
*   isnormal        Non-zero if and only if the argument x is normalized.       *
*   isfinite        Non-zero if and only if the argument x is finite.           *
*   isnan           Non-zero if and only if the argument x is a NaN.            *
*   signbit         Non-zero if and only if the sign of the argument x is       *
*                   negative.  This includes, NaNs, infinities and zeros.       *
*                                                                               *
********************************************************************************/

#define      fpclassify( x )    ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __fpclassifyd  ( x ) :                           \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __fpclassifyf ( x ) :                            \
                              __fpclassify  ( x ) )
#define      isnormal( x )      ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __isnormald ( x ) :                              \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __isnormalf ( x ) :                              \
                              __isnormal  ( x ) )
#define      isfinite( x )      ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __isfinited ( x ) :                              \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __isfinitef ( x ) :                              \
                              __isfinite  ( x ) )
#define      isinf( x )         ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __isinfd ( x ) :                                 \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __isinff ( x ) :                                 \
                              __isinf  ( x ) )
#define      isnan( x )         ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __isnand ( x ) :                                 \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __isnanf ( x ) :                                 \
                              __isnan  ( x ) )
#define      signbit( x )       ( ( sizeof ( x ) == sizeof(double) ) ?           \
                              __signbitd ( x ) :                               \
                                ( sizeof ( x ) == sizeof( float) ) ?            \
                              __signbitf ( x ) :                               \
                              __signbitl  ( x ) )

#define __TYPE_LONGDOUBLE_IS_DOUBLE 0
                              
extern long  __fpclassifyd( double );
extern long  __fpclassifyf( float );
extern long  __fpclassify( long double );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
#ifdef __cplusplus
    inline long __fpclassify( long double x ) { return __fpclassifyd((double)( x )); }
#else
#define __fpclassify( x ) (__fpclassifyd((double)( x )))
#endif
#endif


extern long  __isnormald( double );
extern long  __isnormalf( float );
extern long  __isnormal( long double );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
#ifdef __cplusplus
    inline long __isnormal( long double x ) { return __isnormald((double)( x )); }
#else
#define __isnormal( x ) (__isnormald((double)( x )))
#endif
#endif

extern long  __isfinited( double );
extern long  __isfinitef( float );
extern long  __isfinite( long double );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
#ifdef __cplusplus
    inline long __isfinite( long double x ) { return __isfinited((double)( x )); }
#else
#define __isfinite( x ) (__isfinited((double)( x )))
#endif
#endif


extern long  __isinfd( double );
extern long  __isinff( float );
extern long  __isinf( long double );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
#ifdef __cplusplus
    inline long __isinf( long double x ) { return __isinfd((double)( x )); }
#else
#define __isinf( x ) (__isinfd((double)( x )))
#endif
#endif


extern long  __isnand( double );
extern long  __isnanf( float );
extern long  __isnan( long double );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
#ifdef __cplusplus
    inline long __isnan( long double x ) { return __isnand((double)( x )); }
#else
#define __isnan( x ) (__isnand((double)( x )))
#endif
#endif


extern long  __signbitd( double );
extern long  __signbitf( float );
extern long  __signbitl( long double );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
#ifdef __cplusplus
    inline long __signbitl( long double x ) { return __signbitd((double)( x )); }
#else
#define __signbitl( x ) (__signbitd((double)( x )))
#endif
#endif

/********************************************************************************
*                                                                               *
*                              Math Functions                                   *
*                                                                               *
********************************************************************************/

extern double  acos( double );
extern float  acosf( float );

extern double  asin( double );
extern float  asinf( float );

extern double  atan( double );
extern float  atanf( float );

extern double  atan2( double, double );
extern float  atan2f( float, float );

extern double  cos( double );
extern float  cosf( float );

extern double  sin( double );
extern float  sinf( float );

extern double  tan( double );
extern float  tanf( float );

extern double  acosh( double );
extern float  acoshf( float );

extern double  asinh( double );
extern float  asinhf( float );

extern double  atanh( double );
extern float  atanhf( float );

extern double  cosh( double );
extern float  coshf( float );

extern double  sinh( double );
extern float  sinhf( float );

extern double  tanh( double );
extern float  tanhf( float );

extern double exp ( double );
extern float expf ( float );

extern double exp2 ( double ); 
extern float exp2f ( float );

extern double expm1 ( double ); 
extern float expm1f ( float );

extern double log ( double );
extern float logf ( float );

extern double log10 ( double );
extern float log10f ( float );

extern double log2 ( double );
extern float log2f ( float );

extern double log1p ( double );
extern float log1pf ( float );

extern double logb ( double );
extern float logbf ( float );

extern double modf ( double, double * );
extern float modff ( float, float * );

extern double ldexp ( double, int );
extern float ldexpf ( float, int );

extern double frexp ( double, int * );
extern float frexpf ( float, int * );

extern int ilogb ( double );
extern int ilogbf ( float );

extern double scalbn ( double, int );
extern float scalbnf ( float, int );

extern double scalbln ( double, long int );
extern float scalblnf ( float, long int );

extern double  fabs( double );
extern float  fabsf( float );

extern double  cbrt( double );
extern float  cbrtf( float );

extern double hypot ( double, double );
extern float hypotf ( float, float );

extern double pow ( double, double );
extern float powf ( float, float );

extern double  sqrt( double );
extern float  sqrtf( float );

extern double  erf( double );
extern float  erff( float );

extern double  erfc( double );
extern float  erfcf( float );

extern double  lgamma( double );
extern float  lgammaf( float );

extern double  tgamma( double );
extern float  tgammaf( float );

extern double ceil ( double );
extern float ceilf ( float );

extern double floor ( double );
extern float floorf ( float );

extern double nearbyint ( double );
extern float nearbyintf ( float );

extern double rint ( double );
extern float rintf ( float );

extern long int lrint ( double );
extern long int lrintf ( float );

extern long long int llrint ( double );
extern long long int llrintf ( float );

extern double round ( double );
extern float roundf ( float );

extern long int lround ( double );
extern long int lroundf ( float );

extern long long int llround ( double );
extern long long int llroundf ( float );

extern double trunc ( double );
extern float truncf ( float );

extern double fmod ( double, double );
extern float fmodf ( float, float );

extern double remainder ( double, double );
extern float remainderf ( float, float );

extern double remquo ( double, double, int * );
extern float remquof ( float, float, int * );

extern double copysign ( double, double );
extern float copysignf ( float, float );

extern double nan( const char * );
extern float nanf( const char * );

extern double nextafter ( double, double );
extern float nextafterf ( float, float );

extern double fdim ( double, double );
extern float fdimf ( float, float );

extern double fmax ( double, double );
extern float fmaxf ( float, float );

extern double fmin ( double, double );
extern float fminf ( float, float );

extern double fma ( double, double, double );
extern float fmaf ( float, float, float );

#define isgreater(x, y) __builtin_isgreater (x, y)
#define isgreaterequal(x, y) __builtin_isgreaterequal (x, y)
#define isless(x, y) __builtin_isless (x, y)
#define islessequal(x, y) __builtin_islessequal (x, y)
#define islessgreater(x, y) __builtin_islessgreater (x, y)
#define isunordered(x, y) __builtin_isunordered (x, y)

extern double  		__inf( void );
extern float  		__inff( void );
extern long double  	__infl( void );
extern float  		__nan( void ); /* 10.3 (and later) must retain in ABI for backward compatability */

#ifndef __NOEXTENSIONS__

#define FP_SNAN		FP_NAN
#define FP_QNAN		FP_NAN

extern long int rinttol ( double );

extern long int roundtol ( double );

typedef struct __complex_s {
        double Real;
        double Imag;
} __complex_t;

typedef struct __complexf_s {
        float Real;
        float Imag;
} __complexf_t;

/*
 * XOPEN/SVID
 */
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
#define	M_E		2.7182818284590452354	/* e */
#define	M_LOG2E		1.4426950408889634074	/* log 2e */
#define	M_LOG10E	0.43429448190325182765	/* log 10e */
#define	M_LN2		0.69314718055994530942	/* log e2 */
#define	M_LN10		2.30258509299404568402	/* log e10 */
#define	M_PI		3.14159265358979323846	/* pi */
#define	M_PI_2		1.57079632679489661923	/* pi/2 */
#define	M_PI_4		0.78539816339744830962	/* pi/4 */
#define	M_1_PI		0.31830988618379067154	/* 1/pi */
#define	M_2_PI		0.63661977236758134308	/* 2/pi */
#define	M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define	M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define	M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */

#define	MAXFLOAT	((float)3.40282346638528860e+38)
extern int signgam;

#if !defined(_XOPEN_SOURCE)
enum fdversion {fdlibm_ieee = -1, fdlibm_svid, fdlibm_xopen, fdlibm_posix};

#define _LIB_VERSION_TYPE enum fdversion
#define _LIB_VERSION _fdlib_version  

/* if global variable _LIB_VERSION is not desirable, one may 
 * change the following to be a constant by: 
 *	#define _LIB_VERSION_TYPE const enum version
 * In that case, after one initializes the value _LIB_VERSION (see
 * s_lib_version.c) during compile time, it cannot be modified
 * in the middle of a program
 */ 
extern  _LIB_VERSION_TYPE  _LIB_VERSION;

#define _IEEE_  fdlibm_ieee
#define _SVID_  fdlibm_svid
#define _XOPEN_ fdlibm_xopen
#define _POSIX_ fdlibm_posix

#if !defined(__cplusplus)
struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};
#endif

#define	HUGE		MAXFLOAT

/* 
 * set X_TLOSS = pi*2**52, which is possibly defined in <values.h>
 * (one may replace the following line by "#include <values.h>")
 */

#define X_TLOSS		1.41484755040568800000e+16 

#define	DOMAIN		1
#define	SING		2
#define	OVERFLOW	3
#define	UNDERFLOW	4
#define	TLOSS		5
#define	PLOSS		6

#endif /* !_XOPEN_SOURCE */
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
extern int finite ( double );
extern int finitef ( float );

extern double gamma ( double );
extern float gammaf ( float );

extern double j0 ( double );
extern float j0f ( float );

extern double j1 ( double );
extern float j1f ( float );

extern double jn ( int, double );
extern float jnf ( int, float );

extern double y0 ( double );
extern float y0f ( float );

extern double y1 ( double );
extern float y1f ( float );

extern double yn ( int, double );
extern float ynf ( int, float );

#if !defined(_XOPEN_SOURCE)

extern double scalb ( double, int );
extern float scalbf ( float, int );

#if !defined(__cplusplus)
extern int matherr ( struct exception * );
#endif

/*
 * IEEE Test Vector
 */
extern double significand ( double );

/*
 * BSD math library entry points
 */
#ifndef __COMPLEX__
#define complex _Complex
extern double cabs ( double complex );
extern float cabsf ( float complex );
#undef complex
#endif

extern double drem ( double, double );
extern float dremf ( float, float );

/*
 * Reentrant version of gamma & lgamma; passes signgam back by reference
 * as the second argument; user must allocate space for signgam.
 */
#ifdef _REENTRANT
extern double gamma_r ( double, int * );
extern float gammaf_r ( float, int * );

extern double lgamma_r ( double, int * );
extern float lgammaf_r ( float, int * );
#endif /* _REENTRANT */
#endif /* !_XOPEN_SOURCE */
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */

#endif /* __NOEXTENSIONS__ */

#ifdef __cplusplus
}
#endif

#endif /* __MATH__ */
