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

#define NAN		__nan( )

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
                              
extern long  __fpclassifyd( double x );
extern long  __fpclassifyf( float x );
extern long  __fpclassify( long double x );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
  #ifdef __cplusplus
    inline long __fpclassify( long double x ) { return __fpclassifyd((double)( x )); }
  #else
    #define __fpclassify( x ) (__fpclassifyd((double)( x )))
  #endif
#endif


extern long  __isnormald( double x );
extern long  __isnormalf( float x );
extern long  __isnormal( long double x );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
  #ifdef __cplusplus
    inline long __isnormal( long double x ) { return __isnormald((double)( x )); }
  #else
    #define __isnormal( x ) (__isnormald((double)( x )))
  #endif
#endif

extern long  __isfinited( double x );
extern long  __isfinitef( float x );
extern long  __isfinite( long double x );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
  #ifdef __cplusplus
    inline long __isfinite( long double x ) { return __isfinited((double)( x )); }
  #else
    #define __isfinite( x ) (__isfinited((double)( x )))
  #endif
#endif


extern long  __isinfd( double x );
extern long  __isinff( float x );
extern long  __isinf( long double x );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
  #ifdef __cplusplus
    inline long __isinf( long double x ) { return __isinfd((double)( x )); }
  #else
    #define __isinf( x ) (__isinfd((double)( x )))
  #endif
#endif


extern long  __isnand( double x );
extern long  __isnanf( float x );
extern long  __isnan( long double x );
#if __TYPE_LONGDOUBLE_IS_DOUBLE
  #ifdef __cplusplus
    inline long __isnan( long double x ) { return __isnand((double)( x )); }
  #else
    #define __isnan( x ) (__isnand((double)( x )))
  #endif
#endif


extern long  __signbitd( double x );
extern long  __signbitf( float x );
extern long  __signbitl( long double x );
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

extern double  acos( double x );
extern float  acosf( float x );

extern double  asin( double x );
extern float  asinf( float x );

extern double  atan( double x );
extern float  atanf( float x );

extern double  atan2( double y, double x );
extern float  atan2f( float y, float x );

extern double  cos( double x );
extern float  cosf( float x );

extern double  sin( double x );
extern float  sinf( float x );

extern double  tan( double x );
extern float  tanf( float x );

extern double  acosh( double x );
extern float  acoshf( float x );

extern double  asinh( double x );
extern float  asinhf( float x );

extern double  atanh( double x );
extern float  atanhf( float x );

extern double  cosh( double x );
extern float  coshf( float x );

extern double  sinh( double x );
extern float  sinhf( float x );

extern double  tanh( double x );
extern float  tanhf( float x );

extern double exp ( double x );
extern float expf ( float x );

extern double exp2 ( double x ); 
extern float exp2f ( float x );

extern double expm1 ( double x ); 
extern float expm1f ( float x );

extern double log ( double x );
extern float logf ( float x );

extern double log10 ( double x );
extern float log10f ( float x );

extern double log2 ( double x );
extern float log2f ( float x );

extern double log1p ( double x );
extern float log1pf ( float x );

extern double logb ( double x );
extern float logbf ( float x );

extern double modf ( double x, double *iptr );
extern float modff ( float x, float *iptr );

extern double ldexp ( double value, int exp );
extern float ldexpf ( float value, int exp );

extern double frexp ( double value, int *eptr );
extern float frexpf ( float value, int *eptr );

extern int ilogb ( double x );
extern int ilogbf ( float x );

extern double scalbn ( double x, int n );
extern float scalbnf ( float x, int n );

extern double scalbln ( double x, long int n );
extern float scalblnf ( float x, long int n );

extern double  fabs( double x );
extern float  fabsf( float x );

extern double  cbrt( double x );
extern float  cbrtf( float x );

extern double hypot ( double x, double y );
extern float hypotf ( float x, float y );

extern double pow ( double x, double y );
extern float powf ( float x, float y );

extern double  sqrt( double x );
extern float  sqrtf( float x );

extern double  erf( double x );
extern float  erff( float x );

extern double  erfc( double x );
extern float  erfcf( float x );

extern double  lgamma( double x );
extern float  lgammaf( float x );

extern double  tgamma( double x );
extern float  tgammaf( float x );

extern double ceil ( double x );
extern float ceilf ( float x );

extern double floor ( double x );
extern float floorf ( float x );

extern double nearbyint ( double x );
extern float nearbyintf ( float x );

extern double rint ( double x );
extern float rintf ( float x );

extern long int lrint ( double x );
extern long int lrintf ( float x );

extern long long int llrint ( double x );
extern long long int llrintf ( float x );

extern double round ( double x );
extern float roundf ( float x );

extern long int lround ( double x );
extern long int lroundf ( float x );

extern long long int llround ( double x );
extern long long int llroundf ( float x );

extern double trunc ( double x );
extern float truncf ( float x );

extern double fmod ( double x, double y );
extern float fmodf ( float x, float y );

extern double remainder ( double x, double y );
extern float remainderf ( float x, float y );

extern double remquo ( double x, double y, int *quo );
extern float remquof ( float x, float y, int *quo );

extern double copysign ( double x, double y );
extern float copysignf ( float x, float y );

extern double nan( const char *tagp );
extern float nanf( const char *tagp );

extern double nextafter ( double x, double y );
extern float nextafterf ( float x, float y );

extern double fdim ( double x, double y );
extern float fdimf ( float x, float y );

extern double fmax ( double x, double y );
extern float fmaxf ( float x, float y );

extern double fmin ( double x, double y );
extern float fminf ( float x, float y );

extern double fma ( double x, double y, double z );
extern float fmaf ( float x, float y, float z );

#define isgreater(x, y) __builtin_isgreater (x, y)
#define isgreaterequal(x, y) __builtin_isgreaterequal (x, y)
#define isless(x, y) __builtin_isless (x, y)
#define islessequal(x, y) __builtin_islessequal (x, y)
#define islessgreater(x, y) __builtin_islessgreater (x, y)
#define isunordered(x, y) __builtin_isunordered (x, y)

extern double  		__inf( void );
extern float  		__inff( void );
extern long double  	__infl( void );
extern float  		__nan( void );

#ifndef __NOEXTENSIONS__

#define FP_SNAN		FP_NAN
#define FP_QNAN		FP_NAN

extern long int rinttol ( double x );

extern long int roundtol ( double x );

typedef struct _complx {
        double Real;
        double Imag;
} _complex;

typedef struct _complxf {
        float Real;
        float Imag;
} _complexf;

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
extern int finite ( double x );
extern int finitef ( float x );

extern double gamma ( double x );
extern float gammaf ( float x );

extern double j0 ( double x );
extern float j0f ( float x );

extern double j1 ( double x );
extern float j1f ( float x );

extern double jn ( int n, double x );
extern float jnf ( int n, float x );

extern double y0 ( double x );
extern float y0f ( float x );

extern double y1 ( double x );
extern float y1f ( float x );

extern double yn ( int n, double x );
extern float ynf ( int n, float x );

#if !defined(_XOPEN_SOURCE)

extern double scalb ( double x, int n );
extern float scalbf ( float x, int n );

#if !defined(__cplusplus)
extern int matherr ( struct exception * );
#endif

/*
 * IEEE Test Vector
 */
extern double significand ( double x );

/*
 * BSD math library entry points
 */
extern double cabs ( _complex z );
extern float cabsf ( _complexf z );

extern double drem ( double x, double y );
extern float dremf ( float x, float y );

/*
 * Reentrant version of gamma & lgamma; passes signgam back by reference
 * as the second argument; user must allocate space for signgam.
 */
#ifdef _REENTRANT
extern double gamma_r ( double x, int *psigngam );
extern float gammaf_r ( float x, int *psigngam );

extern double lgamma_r ( double x, int *psigngam );
extern float lgammaf_r ( float x, int *psigngam );
#endif /* _REENTRANT */
#endif /* !_XOPEN_SOURCE */
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */

#endif /* __NOEXTENSIONS__ */

#ifdef __cplusplus
}
#endif

#endif /* __MATH__ */
