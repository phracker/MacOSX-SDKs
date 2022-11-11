/*
vForce.h (from vecLib-794.0)
Copyright (c) 1999-2021 by Apple Inc. All rights reserved.

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

/*! @header
 *  vForce provides fast mathematical operations on large arrays.
 *
 *  There are several differences between vForce and the similar functions
 *  available in libm. They are:
 *  1) vForce can operate on arrays of any size (libm only works on scalars,
 *     and simd.h on small fixed size vectors).
 *  2) vForce may treat some or all denormal numbers as zero.
 *  3) vForce does not guarantee to set floating point flags correctly.
 *
 *  However, unlike some fast math alternatives, vForce respects the closure of
 *  the number system, therefore infinities and NaNs are correctly processed.
 *
 *  Developers should assume that the exact value returned and treatment of
 *  denormal values will vary across different microarchitectures and versions
 *  of the operating system.
 *
 *  For very small vectors, users may wish to consider using simd.h for
 *  increased performance.
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

#include <os/availability.h>


#if !defined __has_feature
    #define __has_feature(f)    0
#endif
#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull begin")
#endif



/*! @abstract Calculates the reciprocal for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to 1/x[i].
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvrecf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the reciprocal for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to 1/x[i].
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvrec (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the quotient of the two source vectors.
 *
 *  @param z (output) Output vector of size *n. z[i] is set to y[i]/x[i].
 *
 *  @param y (input)  Input vector of size *n, numerators in division.
 *
 *  @param x (input)  Input vector of size *n, denominators in division.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvdivf (float * /* z */, const float * /* y */, const float * /* x */, const int *  /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the quotient of the two source vectors.
 *
 *  @param z (output) Output vector of size *n. z[i] is set to y[i]/x[i].
 *
 *  @param y (input)  Input vector of size *n, numerators in division.
 *
 *  @param x (input)  Input vector of size *n, denominators in division.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvdiv (double * /* z */, const double * /* y */, const double * /* x */, const int *  /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the square root for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to sqrt(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsqrtf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the square root for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to sqrt(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsqrt (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the cube root for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cbrt(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcbrtf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.10), ios(8.0));
/*! @abstract Calculates the cube root for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cbrt(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcbrt (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.10), ios(8.0));
    
/*! @abstract Calculates the reciprocal square root for each element of a
 *            vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to 1/sqrt(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvrsqrtf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the reciprocal square root for each element of a
 *            vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to 1/sqrt(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvrsqrt (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the exponential function e**x for each element of a
 *            vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to exp(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvexpf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the exponential function e**x for each element of a
 *            vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to exp(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvexp (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the base 2 exponential function 2**x for each element
 *            of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to exp2(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvexp2f (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
/*! @abstract Calculates the base 2 exponential function 2**x for each element
 *            of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to exp2(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvexp2 (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

/*! @abstract Calculates (e**x) - 1 for each element of a vector, with high
 *            accuracy around x=0.
 *
 *  @discussion
 *  If x is nearly zero, then the common expression exp(x) - 1.0 will suffer
 *  from catastrophic cancellation and the result will have little or no
 *  precision.  This function provides an alternative means to do this
 *  calculation without the risk of significant loss of precision.
 *
 *  @seealso log1pf
 *
 *  @param y (output) Output vector of size *n. y[i] is set to expm1(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvexpm1f (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.5), ios(5.0));
/*! @abstract Calculates (e**x) - 1 for each element of a vector, with high
 *            accuracy around x=0.
 *
 *  @discussion
 *  If x is nearly zero, then the common expression exp(x) - 1.0 will suffer
 *  from catastrophic cancellation and the result will have little or no
 *  precision.  This function provides an alternative means to do this
 *  calculation without the risk of significant loss of precision.
 *
 *  @seealso log1p
 *
 *  @param y (output) Output vector of size *n. y[i] is set to expm1(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvexpm1 (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
	
/*! @abstract Calculates the natural logarithm for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlogf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the natural logarithm for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlog (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the logarithm base 10 for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log10(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlog10f (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the logarithm base 10 for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log10(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlog10 (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates log(1+x) for each element of a vector, with high
 *            accuracy around x=0.
 *
 *  @discussion
 *  If x is nearly zero, the expression log(1+x) will be highly inaccurate
 *  due to floating point rounding errors in (1+x).
 *  This function provides an alternative means to calculate this value with
 *  higher accuracy.
 *
 *  @seealso expm1f
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log1p(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlog1pf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.5), ios(5.0));
/*! @abstract Calculates log(1+x) for each element of a vector, with high
 *            accuracy around x=0.
 *
 *  @discussion
 *  If x is nearly zero, the expression log(1+x) will be highly inaccurate
 *  due to floating point rounding errors in (1+x).
 *  This function provides an alternative means to calculate this value with
 *  higher accuracy.
 *
 *  @seealso expm1
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log1p(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlog1p (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

/*! @abstract Calculates the base 2 logarithm for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log2(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlog2f (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
/*! @abstract Calculates the base 2 logarithm for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log2(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlog2 (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
	
/*! @abstract Returns, as a floating-point value, the unbiased floating-point
 *            exponent for each element of a vector.
 *
 *  @discussion
 *  For a non-zero finite floating-point number f, logb is defined to be the
 *  integer that satisfies abs(f) = significand * 2**logb(f), with significand
 *  in [1,2).
 *
 *  If x is +/-0, then y is set to -inf.
 *  If x is +/-inf, then y is set to +inf.
 *  If x is NaN, then y is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log10(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlogbf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.5), ios(5.0));
/*! @abstract Returns, as a floating-point value, the unbiased floating-point
 *            exponent for each element of a vector.
 *
 *  @discussion
 *  For a non-zero finite floating-point number f, logb is defined to be the
 *  integer that satisfies abs(f) = significand * 2**logb(f), with significand
 *  in [1,2).
 *
 *  If x is +/-0, then y is set to -inf.
 *  If x is +/-inf, then y is set to +inf.
 *  If x is NaN, then y is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to log10(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvlogb (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
	
/*! @abstract Returns the absolute value for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to fabs(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvfabsf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
/*! @abstract Returns the absolute value for each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to fabs(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvfabs (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

/*! @abstract Calculates, elementwise, x**y for two vectors x and y.
 *
 *  @discussion
 *  The following special values of x and y produce the given value of z:
 *         y            x         z
 *  ==============   =======   =======
 *  odd integer,<0    +/-0     +/-inf
 *  odd integer,>0    +/-0     +/-0
 *  otherwise,  <0    +/-0       +inf
 *  otherwise,  >0    +/-0       +0
 *      +/-inf          -1        1
 *       NaN            +1        1
 *      +/-0           NaN        1
 *        -inf        |x|<1      +inf
 *        -inf        |x|>1      +0
 *        +inf        |x|<1      +0
 *        +inf        |x|>1      +inf
 *  odd integer,<0     -inf      -0
 *  odd integer,>0     -inf      -inf
 *  otherwise,  <0     -inf      +0
 *  otherwise,  >0     -inf      +inf
 *        <0           +inf      +0
 *        >0           +inf      +inf
 *    non-integer       <0       NaN
 *
 *  @param z (output) Output vector of size *n. z[i] is set to pow(x[i], y[i]).
 *
 *  @param y (input)  Input vector of size *n, exponent in calculation.
 *
 *  @param x (input)  Input vector of size *n, base in calculation.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.
 */
void vvpowf (float * /* z */, const float * /* y */, const float * /* x */, const int *  /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates, elementwise, x**y for two vectors x and y.
 *
 *  @discussion
 *  The following special values of x and y produce the given value of z:
 *         y            x         z
 *  ==============   =======   =======
 *  odd integer,<0    +/-0     +/-inf
 *  odd integer,>0    +/-0     +/-0
 *  otherwise,  <0    +/-0       +inf
 *  otherwise,  >0    +/-0       +0
 *      +/-inf          -1        1
 *       NaN            +1        1
 *      +/-0           NaN        1
 *        -inf        |x|<1      +inf
 *        -inf        |x|>1      +0
 *        +inf        |x|<1      +0
 *        +inf        |x|>1      +inf
 *  odd integer,<0     -inf      -0
 *  odd integer,>0     -inf      -inf
 *  otherwise,  <0     -inf      +0
 *  otherwise,  >0     -inf      +inf
 *        <0           +inf      +0
 *        >0           +inf      +inf
 *    non-integer       <0       NaN
 *
 *  @param z (output) Output vector of size *n. z[i] is set to pow(x[i], y[i]).
 *
 *  @param y (input)  Input vector of size *n, exponent in calculation.
 *
 *  @param x (input)  Input vector of size *n, base in calculation.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.
 */
void vvpow (double * /* z */, const double * /* y */, const double * /* x */, const int *  /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates, elementwise, x**y for a vector x and a scalar y.
 *
 *  @param z (output) Output vector of size *n. z[i] is set to pow(x[i], y).
 *
 *  @param y (input)  Input scalar, exponent in calculation.
 *
 *  @param x (input)  Input vector of size *n, base in calculation.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvpowsf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.9), ios(6.0));
/*! @abstract Calculates, elementwise, x**y for a vector x and a scalar y.
 *
 *  @param z (output) Output vector of size *n. z[i] is set to pow(x[i], y).
 *
 *  @param y (input)  Input scalar, exponent in calculation.
 *
 *  @param x (input)  Input vector of size *n, base in calculation.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvpows (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.9), ios(6.0));

/*! @abstract Returns the sine for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to sin(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsinf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Returns the sine for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to sin(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsin (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Returns the cosine for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-inf, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cos(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcosf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Returns the cosine for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-inf, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cos(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcos (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Returns the tangent for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to tan(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvtanf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Returns the tangent for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to tan(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvtan (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Returns the principal value of arc sine for each element of a
 *            vector.
 *
 *  @discussion
 *  The calculated values are in the range [-pi/2, +pi/2].
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If |x[i]| > 1, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to asin(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvasinf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Returns the principal value of arc sine for each element of a
 *            vector.
 *
 *  @discussion
 *  The calculated values are in the range [-pi/2, +pi/2].
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If |x[i]| > 1, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to asin(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvasin (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Returns the principal value of arc cosine for each element of a
 *            vector.
 *
 *  @discussion
 *  The calculated values are in the range [0, pi].
 *  If x[i] is 1, y[i] is set to +0.
 *  If |x[i]| > 1, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to acos(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvacosf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Returns the principal value of arc cosine for each element of a
 *            vector.
 *
 *  @discussion
 *  The calculated values are in the range [0, pi].
 *  If x[i] is 1, y[i] is set to +0.
 *  If |x[i]| > 1, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to acos(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvacos (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Returns the principal value of arc tangent for each element of a
 *            vector.
 *
 *  @discussion
 *  The calculated values are in the range [-pi/2, pi/2].
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to +/-pi/2.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to atan(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvatanf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Returns the principal value of arc tangent for each element of a
 *            vector.
 *
 *  @discussion
 *  The calculated values are in the range [-pi/2, pi/2].
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to +/-pi/2.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to atan(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvatan (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates, elementwise, the principal value of the arc tangent
 *            of y/x, for two vectors x and y.
 *
 *  @discusssion
 *  The signs of both arguments are used to determine the quadrant of the
 *  calculated value.
 *
 *  The following special values of x and y produce the given value of z:
 *     y         x         z
 *  =======   =======   =======
 *   +/-0       -0       +/-pi
 *   +/-0       +0       +/-0
 *   +/-0       <0       +/-pi
 *   +/-0       >0       +/-0
 *    >0       +/-0      +pi/2
 *    <0       +/-0      -pi/2
 *   +/-y      -inf      +/-pi       y>0, finite
 *   +/-y      +inf      +/-0        y>0, finite
 *  +/-inf      x       +/-pi/2      x finite
 *  +/-inf     -inf     +/-3pi/4
 *  +/-inf     +inf     +/-pi/4
 *
 *  @param z (output) Output vector of size *n. z[i] is set to atan2(y,x).
 *
 *  @param y (input)  Input vector of size *n.
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvatan2f (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates, elementwise, the principal value of the arc tangent
 *            of y/x, for two vectors x and y.
 *
 *  @discusssion
 *  The signs of both arguments are used to determine the quadrant of the
 *  calculated value.
 *
 *  The following special values of x and y produce the given value of z:
 *     y         x         z
 *  =======   =======   =======
 *   +/-0       -0       +/-pi
 *   +/-0       +0       +/-0
 *   +/-0       <0       +/-pi
 *   +/-0       >0       +/-0
 *    >0       +/-0      +pi/2
 *    <0       +/-0      -pi/2
 *   +/-y      -inf      +/-pi       y>0, finite
 *   +/-y      +inf      +/-0        y>0, finite
 *  +/-inf      x       +/-pi/2      x finite
 *  +/-inf     -inf     +/-3pi/4
 *  +/-inf     +inf     +/-pi/4
 *
 *  @param z (output) Output vector of size *n. z[i] is set to atan2(y,x).
 *
 *  @param y (input)  Input vector of size *n.
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvatan2 (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Returns the sine and cosine for each element of a vector.
 *
 *  @param z (output) Output vector of size *n. z[i] is set to sin(x[i]).
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cos(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsincosf (float * /* z */, float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Returns the sine and cosine for each element of a vector.
 *
 *  @param z (output) Output vector of size *n. z[i] is set to sin(x[i]).
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cos(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsincos (double * /* z */, double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Returns the complex number on the unit circle corresponding to
 *            the angle given by each element of a vector.
 *
 *  @discussion
 *  Sets the real part of C to the cosine of x, and the imaginary part to the
 *  sine of y.
 *
 *  The typedef __float_complex_t is defined on a per language basis, and the
 *  following types should be used:
 *  In C,   _Complex float
 *  In C++, std::complex<float>.
 *
 *  @param C (output) Output vector of size *n.
 *                    C[i] is set to cos(x[i]) + I*sin(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcosisinf (__float_complex_t * /* C */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Returns the complex number on the unit circle corresponding to
 *            the angle given by each element of a vector.
 *
 *  @discussion
 *  Sets the real part of C to the cosine of x, and the imaginary part to the
 *  sine of y.
 *
 *  The typedef __double_complex_t is defined on a per language basis, and the
 *  following types should be used:
 *  In C,   _Complex double
 *  In C++, std::complex<double>.
 *
 *  @param C (output) Output vector of size *n.
 *                    C[i] is set to cos(x[i]) + I*sin(x[i]).
 *
 *  @param x (input)  Input vector of size *n, in radians.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcosisin (__double_complex_t * /* C */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the hyperbolic sine for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to +/-inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to sinh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsinhf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the hyperbolic sine for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to +/-inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to sinh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsinh (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the hyperbolic cosine for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] is set to 1.
 *  If x[i] is +/-inf, y[i] is set to +inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cosh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcoshf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the hyperbolic cosine for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] is set to 1.
 *  If x[i] is +/-inf, y[i] is set to +inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cosh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcosh (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the hyperbolic tangent for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to +/-1.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to tanh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvtanhf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the hyperbolic tangent for each element of a vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to +/-1.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to tanh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvtanh (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the inverse hyperbolic sine for each element of a
 *            vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to +/-inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to asinh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvasinhf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the inverse hyperbolic sine for each element of a
 *            vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-inf, y[i] is set to +/-inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to asinh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvasinh (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the principal value of inverse hyperbolic cosine for
 *            each element of a vector.
 *
 *  @discussion
 *  The calculated values are in the range [0, +inf].
 *  If x[i] == 1, y[i] is set to +0.
 *  If x[i] < 1, y[i] is set to NaN.
 *  If x[i] == +inf, y[i] is set to +inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to acosh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvacoshf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the principal value of inverse hyperbolic cosine for
 *            each element of a vector.
 *
 *  @discussion
 *  The calculated values are in the range [0, +inf].
 *  If x[i] == 1, y[i] is set to +0.
 *  If x[i] < 1, y[i] is set to NaN.
 *  If x[i] == +inf, y[i] is set to +inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to acosh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvacosh (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the inverse hyperbolic tangent for each element of a
 *            vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-1, y[i] is set to +/-inf.
 *  If |x[i]|>1, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to atanh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvatanhf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the inverse hyperbolic tangent for each element of a
 *            vector.
 *
 *  @discussion
 *  If x[i] is +/-0, y[i] preserves the signed zero.
 *  If x[i] is +/-1, y[i] is set to +/-inf.
 *  If |x[i]|>1, y[i] is set to NaN.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to atanh(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvatanh (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the integer truncation for each element of a vector.
 *
 *  @discussion
 *  The behavior of this function is equivalent to the libm function truncf().
 *  It rounds x[i] to the nearest integer in the direction of zero,
 *  equivalent to the C typecast y[i] = (float) (int) x[i].
 *
 *  @param y (output) Output vector of size *n. y[i] is set to integer
 *                    trunction of x[i].
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvintf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the integer truncation for each element of a vector.
 *
 *  @discussion
 *  The behavior of this function is equivalent to the libm function trunc().
 *  It rounds x[i] to the nearest integer in the direction of zero,
 *  equivalent to the C typecast y[i] = (double) (int) x[i].
 *
 *  @param y (output) Output vector of size *n. y[i] is set to integer
 *                    trunction of x[i].
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvint (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the rounding to the nearest integer for each element
 *            of a vector.
 *
 *  @discussion
 *  Rounds x[i] to the nearest integer, with ties rounded to even.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to the nearest
 *                    integer to x[i].
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvnintf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the rounding to the nearest integer for each element
 *            of a vector.
 *
 *  @discussion
 *  Rounds x[i] to the nearest integer, with ties rounded to even.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to the nearest
 *                    integer to x[i].
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvnint (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the ceiling function for each element of a vector.
 *
 *  @discussion
 *  Rounds to smallest integral value not less than x[i]. That is to say,
 *  rounds towards +inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to ceil(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvceilf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the ceiling function for each element of a vector.
 *
 *  @discussion
 *  Rounds to smallest integral value not less than x[i]. That is to say,
 *  rounds towards +inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to ceil(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvceil (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates the floor function for each element of a vector.
 *
 *  @discussion
 *  Rounds to smallest integral value not greater than x[i]. That is to say,
 *  rounds towards -inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to floor(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvfloorf (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));
/*! @abstract Calculates the floor function for each element of a vector.
 *
 *  @discussion
 *  Rounds to smallest integral value not greater than x[i]. That is to say,
 *  rounds towards -inf.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to floor(x[i]).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvfloor (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.4), ios(5.0));

/*! @abstract Calculates, elementwise, the floating-point remainder of y/x,
 *            for two vectors x and y.
 *
 *  @discussion
 *  Specifically, the function calculates z=y-k*x, for some integer k such that,
 *  if x is non-zero, the result has the same sign as y, and magnitude less than
 *  that of x.
 *
 *  If y[i] is +/-0, and x[i] is not 0 or NaN, z[i] is set to +/-0.
 *  If y[i] is +/-inf, or x[i] is +/-0, z[i] is set to NaN.
 *  If x[i] is +/-inf, and y is finite, z[i] is set to y[i].
 *
 *  Note that argument labels are switched with respect to the libm function
 *  fmod().
 *
 *  @seealso vvremainderf
 *
 *  @param z (output) Output vector of size *n. z[i] is set to fmod(y[i], x[i]).
 *
 *  @param y (input)  Input vector of size *n, numerator in calculation.
 *
 *  @param x (input)  Input vector of size *n, denominator in calculation.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvfmodf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.5), ios(5.0));
/*! @abstract Calculates, elementwise, the floating-point remainder of y/x,
 *            for two vectors x and y.
 *
 *  @discussion
 *  Specifically, the function calculates z=y-k*x, for some integer k such that,
 *  if x is non-zero, the result has the same sign as y, and magnitude less than
 *  that of x.
 *
 *  If y[i] is +/-0, and x[i] is not 0 or NaN, z[i] is set to +/-0.
 *  If y[i] is +/-inf, or x[i] is +/-0, z[i] is set to NaN.
 *  If x[i] is +/-inf, and y is finite, z[i] is set to y[i].
 *
 *  Note that argument labels are switched with respect to the libm function
 *  fmod().
 *
 *  @seealso vvremainder
 *
 *  @param z (output) Output vector of size *n. z[i] is set to fmod(y[i], x[i]).
 *
 *  @param y (input)  Input vector of size *n, numerator in calculation.
 *
 *  @param x (input)  Input vector of size *n, denominator in calculation.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvfmod (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

/*! @abstract Calculates, elementwise, the difference between k*x and y, where
 *            k is the nearest integer to y/x.
 *
 *  @discussion
 *  Specifically, the function calculates z=y-k*x, for the integer k nearest the
 *  exact value of y/x, with ties rounded to even.
 *  The result z satisfies abs(z) <= abs(x)/2.
 *
 *  If y-k*x is zero, it is given the same sign as y.
 *
 *  If y[i] is +/-inf, or x[i] is +/-0, z[i] is set to NaN.
 *  If x[i] is +/-inf, and y is finite, z[i] is set to y[i].
 *
 *  @seealso vvfmodf
 *
 *  @param z (output) Output vector of size *n. z[i] is set to y[i]-k[i]*x[i].
 *
 *  @param y (input)  Input vector of size *n, numerator in calculation.
 *
 *  @param x (input)  Input vector of size *n, denominator in calculation.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvremainderf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.5), ios(5.0));
/*! @abstract Calculates, elementwise, the difference between k*x and y, where
 *            k is the nearest integer to y/x.
 *
 *  @discussion
 *  Specifically, the function calculates z=y-k*x, for the integer k nearest the
 *  exact value of y/x, with ties rounded to even.
 *  The result z satisfies abs(z) <= abs(x)/2.
 *
 *  If y-k*x is zero, it is given the same sign as y.
 *
 *  If y[i] is +/-inf, or x[i] is +/-0, z[i] is set to NaN.
 *  If x[i] is +/-inf, and y is finite, z[i] is set to y[i].
 *
 *  @seealso vvfmod
 *
 *  @param z (output) Output vector of size *n. z[i] is set to y[i]-k[i]*x[i].
 *
 *  @param y (input)  Input vector of size *n, numerator in calculation.
 *
 *  @param x (input)  Input vector of size *n, denominator in calculation.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvremainder (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
	
/*! @abstract Copies, elementwise, the sign of x with the value of y, for two
 *            vectors x and y.
 *
 *  @param z (output) Output vector of size *n.
 *                    z[i] is set to copysign(y[i], x[i]).
 *
 *  @param y (input)  Input vector of size *n, used for the magnitude.
 *
 *  @param x (input)  Input vector of size *n, used for the sign.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvcopysignf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.5), ios(5.0));
/*! @abstract Copies, elementwise, the sign of x with the value of y, for two
 *            vectors x and y.
 *
 *  @param z (output) Output vector of size *n.
 *                    z[i] is set to copysign(y[i], x[i]).
 *
 *  @param y (input)  Input vector of size *n, used for the magnitude.
 *
 *  @param x (input)  Input vector of size *n, used for the sign.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvcopysign (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

/*! @abstract Determines, elementwise, the next machine representable number
 *            from y in the direction of x.
 *
 *  @param z (output) Output vector of size *n.
 *                    z[i] is set to nextafter(y[i], x[i]).
 *
 *  @param y (input)  Input vector of size *n, used for the magnitude.
 *
 *  @param x (input)  Input vector of size *n, used for the sign.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvnextafterf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.5), ios(5.0));
/*! @abstract Determines, elementwise, the next machine representable number
 *            from y in the direction of x.
 *
 *  @param z (output) Output vector of size *n.
 *                    z[i] is set to nextafter(y[i], x[i]).
 *
 *  @param y (input)  Input vector of size *n, used for the magnitude.
 *
 *  @param x (input)  Input vector of size *n, used for the sign.
 *
 *  @param n (input)  The number of elements in the vectors x, y and z.       */
void vvnextafter (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

/*! @abstract Calculates the sine for pi times each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to sin(x[i]*PI).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsinpif (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
/*! @abstract Calculates the sine for pi times each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to sin(x[i]*PI).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvsinpi (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

/*! @abstract Calculates the cosine for pi times each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cos(x[i]*PI).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcospif (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
/*! @abstract Calculates the cosine for pi times each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to cos(x[i]*PI).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvcospi (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

/*! @abstract Calculates the tangent for pi times each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to tan(x[i]*PI).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvtanpif (float * /* y */, const float * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));
/*! @abstract Calculates the tangent for pi times each element of a vector.
 *
 *  @param y (output) Output vector of size *n. y[i] is set to tan(x[i]*PI).
 *
 *  @param x (input)  Input vector of size *n.
 *
 *  @param n (input)  The number of elements in the vectors x and y.          */
void vvtanpi (double * /* y */, const double * /* x */, const int * /* n */) API_AVAILABLE(macos(10.7), ios(5.0));

#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull end")
#endif
	
#ifdef __cplusplus
}
#endif
#endif /* __VFORCE_H */
