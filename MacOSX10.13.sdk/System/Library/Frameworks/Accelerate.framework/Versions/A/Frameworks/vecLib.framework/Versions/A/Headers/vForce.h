/*
vForce.h (from vecLib-622.0)
Copyright (c) 1999-2017 by Apple Inc. All rights reserved.

@APPLE_LICENSE_HEADER_START@

This file contains Original Code and/or Modifications of Original Code
as defined in and that are subject to the Apple Public Source License
Version 2.0 (the 'License'). You may not use this file except in
compliance with the License. Please obtain a copy of the License at
http://www.opensource.apple.com/apsl/ and read it before using this
file.

The Original Code and all software distributed under the License are
distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
Please see the License for the specific language governing rights and
limitations under the License.

@APPLE_LICENSE_HEADER_END@
*/

#ifndef __VFORCE_H
#define __VFORCE_H

#ifdef __cplusplus
	#include <ciso646>	// Get library version.
	#if	defined _LIBCPP_VERSION
		// When using libc++, include <complex>.
		#include <complex>
	#else
		// When not using libc++, try using definition as given in C++ 98.
		namespace std
		{
			template<class T> class complex;
			template<> class complex<float>;
			template<> class complex<double>;
		}
	#endif
	typedef std::complex<float> __float_complex_t;
	typedef std::complex<double> __double_complex_t;
#else
	typedef _Complex float __float_complex_t;
	typedef _Complex double __double_complex_t;
#endif

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <Availability.h>


#if !defined __has_feature
    #define __has_feature(f)    0
#endif
#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull begin")
#else
    #define __nullable
    #define __nonnull
#endif



/* Set y[i] to the reciprocal of x[i], for i=0,..,n-1 */
void vvrecf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
void vvrec (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 

/* Set z[i] to y[i]/x[i], for i=0,..,n-1 */
void vvdivf (float * /* z */, const float * /* y */, const float * /* x */, const int *  /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
void vvdiv (double * /* z */, const double * /* y */, const double * /* x */, const int *  /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 

/* Set y[i] to the square root of x[i], for i=0,..,n-1 */
void vvsqrtf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
void vvsqrt (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 

/* Set y[i] to the cube root of x[i], for i=0,..,n-1 */
void vvcbrtf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);
void vvcbrt (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);
    
/* Set y[i] to the reciprocal of the square root of x[i], for i=0,..,n-1 */
void vvrsqrtf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
void vvrsqrt (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 

/* Set y[i] to the exponential function of x[i], for i=0,..,n-1 */
void vvexpf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
void vvexp (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 

/* Set y[i] to the base-e exponential of x , minus 1 accurately even
   for very small values of x[i], for i=0,..,n-1 */
void vvexpm1f (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_5_0); 
/*
 vvexpm1
 
 This routine computes the base-e exponential of the double precision
 floating point numbers in the input array, minus 1 and store the double
 precision results to the output array. Results are accurate even for very
 small input values.
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvexpm1 (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 
	
/* Set y[i] to the natural logarithm of x[i], for i=0,..,n-1 */
void vvlogf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
void vvlog (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 

/* Set y[i] to the base 10 logarithm of x[i], for i=0,..,n-1 */
void vvlog10f (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
void vvlog10 (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 

/* Set y[i] to the value of log(1+x[i]) accurately even for very small
   values of x[i], for i=0,..,n-1 */
void vvlog1pf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_5_0); 
/*
 vvlog1p
 
 Given double-precision arrray x[] and y[] with *n element each,
 this routine sets y[i] to the value of log(1+x[i]) for each i
 in 0 <= i < *n accurately even for very small values of x[i].
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvlog1p (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
	
/* Set y[i] to the the exponent of x[i], represented as a floating-
     point number, for i=0,..,n-1 */
void vvlogbf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_5_0); 
/*
 vvlogb
 
 Given double-precision arrray x[] and y[] with *n element each,
 this routine sets y[i] to the exponent of x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvlogb (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
	
/*
 vvfabf
 
 Given single-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the absolute value of x[i] for each i in
 0 <= i < *n.
 
 This function is deprecated in Mac OS X 10.7 and later to keep function name
 consistent with Libm. Use vvfabsf instead.
 
 Parameters:
 
 x: Input array filled with single precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvfabf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);
/*
 vvfabsf
 
 Given single-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the absolute value of x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with single precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvfabsf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 
/*
 vvfabs
 
 Given double-precision arrray x[] and y[] with *n element each,
 this routine sets y[i] to the absolute value of x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvfabs (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
	
/* Set z[i] to x[i] ** y[i], for i=0,..,n-1 */
void vvpowf (float * /* z */, const float * /* y */, const float * /* x */, const int *  /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
void vvpow (double * /* z */, const double * /* y */, const double * /* x */, const int *  /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 

/* Set z[i] to pow(x[i],y) for i=0,..,n-1 */
void vvpowsf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
void vvpows (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */)__OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/* Set y[i] to the sine of x[i], for i=0,..,n-1 */
void vvsinf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvsin (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the cosine of x[i], for i=0,..,n-1 */
void vvcosf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvcos (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the tangent of x[i], for i=0,..,n-1 */
void vvtanf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvtan (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the arcsine of x[i], for i=0,..,n-1 */
void vvasinf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvasin (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the arccosine of x[i], for i=0,..,n-1 */
void vvacosf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvacos (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the arctangent of x[i], for i=0,..,n-1 */
void vvatanf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvatan (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set z[i] to the arctangent of y[i]/x[i], for i=0,..,n-1 */
void vvatan2f (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvatan2 (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set z[i] to the sine of x[i] and y[i] to the cosine of x[i], for i=0,..,n-1 */
void vvsincosf (float * /* z */, float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvsincos (double * /* z */, double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set the real part of C[i] to the cosine of x[i] and the imaginary part of C[i] to the 
   sine of x[i], for i=0,..,n-1 */
void vvcosisinf (__float_complex_t * /* C */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvcosisin (__double_complex_t * /* C */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the hyperbolic sine of x[i], for i=0,..,n-1 */
void vvsinhf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvsinh (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the hyperbolic cosine of x[i], for i=0,..,n-1 */
void vvcoshf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvcosh (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the hyperbolic tangent of x[i], for i=0,..,n-1 */
void vvtanhf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvtanh (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the inverse hyperbolic sine of x[i], for i=0,..,n-1 */
void vvasinhf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvasinh (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the inverse hyperbolic  cosine of x[i], for i=0,..,n-1 */
void vvacoshf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvacosh (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the inverse hyperbolic  tangent of x[i], for i=0,..,n-1 */
void vvatanhf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvatanh (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the integer truncation of x[i], for i=0,..,n-1 */
void vvintf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvint (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the nearest integer to x[i], for i=0,..,n-1 */
void vvnintf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvnint (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the ceiling of x[i], for i=0,..,n-1 */
void vvceilf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvceil (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set y[i] to the floor of x[i], for i=0,..,n-1 */
void vvfloorf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);
void vvfloor (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);

/* Set z[i] to the floating-point remainder of y[i]/x[i], for
   i=0,..,n-1 */
void vvfmodf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_5_0);
/*
 vvfmod
 
 Given double-precision array x[], y[], and z[] with *n element each,
 this routine sets z[i] to the remainder of y[i] when divided by x[i]
 for each i in 0 <= i < *n.
 
 Specifically, the function returns the value y-k*x, for some integer k
 such that, if x is non-zero, the result has the same sign as y and
 magnitude less than the magnitude of x.
 
 Parameters:
 
 z: Output array, same size as input array
 y: Numerator array filled with double precision floating point numbers
 x: Denominator array filled with double precision floating point numbers
 n: number of floating point elements specified by *n
 
 */
void vvfmod (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
	
/* Set z[i] to the value r such that r = y[i] - N*x[i], where N is the
     integer nearest the exact value of y[i]/x[i].  If there are two
     integers closest to y[i]/x[i], N shall be the even one. If r is
     zero, it is given the same sign as y[i], for i=0,..,n-1 */
void vvremainderf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_5_0);
/*
 vvremainder
 
 Given double-precision array x[], y[], and z[] with *n element each,
 this routine sets z[i] to the value r such that r = y[i] - N*x[i], where N
 is the integer nearest the exact value of y[i] divided by x[i], for each
 i in 0 <= i < *n.  If there are two integers closest to y[i]/x[i],
 N shall be the even one. If r is zero, it is given the same sign as y[i].
 
 Parameters:
 
 z: Output array, same size as input array
 y: Numerator array filled with double precision floating point numbers
 x: Denominator array filled with double precision floating point numbers
 n: number of floating point elements specified by *n
 
 */
void vvremainder (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
	
/* Set z[i] to y[i] with its sign changed to x[i]'s, for i=0,..,n-1 */
void vvcopysignf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_5_0);
/*
 vvcopysign
 
 Given double-precision array x[], y[], and z[] with *n element each,
 this routine sets z[i] to y[i] with its sign changed to x[i]'s sign
 for each i in 0 <= i < *n.
 
 Parameters:
 
 z: Output array, same size as input array
 y: Magnitude array filled with double precision floating point numbers
 x: Sign array filled with double precision floating point numbers
 n: number of floating point elements specified by *n
 
 */
void vvcopysign (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
	
/* Set z[i] to the next machine representable number from y[i] in
     direction x[i], for i=0,..,n-1 */
void vvnextafterf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_5_0);
/*
 vvnextafter
 
 Given double-precision array x[], y[], and z[] with *n element each,
 this routine sets z[i] to the next machine representable number from y[i]
 in the direction toward x[i] for each i in 0 <= i < *n.
 
 Parameters:
 
 z: Output array, same size as input array
 y: Current value array filled with double precision floating point numbers
 x: Direction array filled with double precision floating point numbers
 n: number of floating point elements specified by *n
 
 */
void vvnextafter (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
	
/*
 vvlog2f
 
 Given single-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the base 2 logarithm of x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with single precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvlog2f (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 
/*
 vvlog2
 
 Given double-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the base 2 logarithm of x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvlog2 (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 

/*
 vvexp2f
 
 Given single-precision array x[] and y[] with *n element each,
 This routine sets y[i] to the base 2 exponential function of x[i],
 ie. y[i]=2^x[i], for each i in 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with single precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvexp2f (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 
/*
 vvexp2
 
 Given double-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the base 2 exponential function of x[i],
 ie. y[i]=2^x[i], for each i in 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvexp2 (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 

/*
 vvsinpif
 
 Given single-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the sine of pi * x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with single precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvsinpif (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 
/*
 vvsinpi
 
 Given double-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the sine of pi * x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvsinpi (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 

/*
 vvcospif
 
 Given single-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the cosine of pi * x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with single precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvcospif (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 
/*
 vvcospi
 
 Given double-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the cosine of pi * x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvcospi (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 

/*
 vvtanpif
 
 Given single-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the tangent of pi * x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with single precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvtanpif (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 
/*
 vvtanpi
 
 Given double-precision array x[] and y[] with *n element each,
 this routine sets y[i] to the tangent of pi * x[i] for each i in
 0 <= i < *n.
 
 Parameters:
 
 x: Input array filled with double precision floating point numbers
 y: Output array, same size as input array
 n: number of floating point elements specified by *n
 
 */
void vvtanpi (double * /* y */, const double * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); 

#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull end")
#endif
	
#ifdef __cplusplus
}
#endif
#endif /* __VFORCE_H */
