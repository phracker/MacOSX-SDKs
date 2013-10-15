/*
Copyright (c) 1999-2004 Apple Computer, Inc.  All rights reserved.

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
#include <complex>
typedef std::complex<float> __float_complex_t;
typedef std::complex<double> __double_complex_t;
#else
#include "complex.h" /* included before math.h in order to get modern cabs() prototype */
typedef complex float __float_complex_t;
typedef complex double __double_complex_t;
#endif

#include "math.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <AvailabilityMacros.h>

/* 
When the float versions of the vector functions (vvrecf(), vvdivf(), etc.) are invoked on platforms equipped
with the AltiVec SIMD unit, they expect that "Java Mode" has been disabled in the AltiVec VSCR register.  By 
default, Mac OS X starts a process in non-Java mode, which means that the VSCR bit is set to 1.
"non-Java Mode" entails flushing de-normal vector floating point values to zero.  A process running in "non-Java 
Mode" enjoys performance advantages when executing AltiVec floating point instructions.

The double versions of the vector functions must be called with the IEEE rounding mode set to round-to-nearest 
and with exceptions masked off. 

The accuracy of the vector functions is comparable to that of the corresponding scalar functions in libm, though 
results may not be bit-wise identical. 
*/

/* Set y[i] to the reciprocal of x[i], for i=0,..,n-1 */
void vvrecf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
void vvrec (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/* Set z[i] to y[i]/x[i], for i=0,..,n-1 */
void vvdivf (float * /* z */, const float * /* y */, const float * /* x */, const int *  /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
void vvdiv (double * /* z */, const double * /* y */, const double * /* x */, const int *  /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/* Set y[i] to the square root of x[i], for i=0,..,n-1 */
void vvsqrtf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
void vvsqrt (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/* Set y[i] to the reciprocal of the square root of x[i], for i=0,..,n-1 */
void vvrsqrtf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
void vvrsqrt (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/* Set y[i] to the exponential function of x[i], for i=0,..,n-1 */
void vvexpf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
void vvexp (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/* Set y[i] to the base-e exponential of x , minus 1 accurately even
   for very small values of x[i], for i=0,..,n-1 */
void vvexpm1f (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
/* No double-precision version currently available */

/* Set y[i] to the natural logarithm of x[i], for i=0,..,n-1 */
void vvlogf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
void vvlog (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/* Set y[i] to the base 10 logarithm of x[i], for i=0,..,n-1 */
void vvlog10f (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
void vvlog10 (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/* Set y[i] to the value of log(1+x[i]) accurately even for very small
   values of x[i], for i=0,..,n-1 */
void vvlog1pf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
/* No double-precision version currently available */

/* Set y[i] to the the exponent of x[i], represented as a floating-
     point number, for i=0,..,n-1 */
void vvlogbf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
/* No double-precision version currently available */

/* Set y[i] to the absolute value of a floating-point number x[i], for
     i=0,..,n-1 */
void vvfabf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
/* No double-precision version currently available */

/* Set z[i] to x[i] ** y[i], for i=0,..,n-1 */
void vvpowf (float * /* z */, const float * /* y */, const float * /* x */, const int *  /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
void vvpow (double * /* z */, const double * /* y */, const double * /* x */, const int *  /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

/* Set y[i] to the sine of x[i], for i=0,..,n-1 */
void vvsinf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvsin (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the cosine of x[i], for i=0,..,n-1 */
void vvcosf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvcos (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the tangent of x[i], for i=0,..,n-1 */
void vvtanf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvtan (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the arcsine of x[i], for i=0,..,n-1 */
void vvasinf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvasin (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the arccosine of x[i], for i=0,..,n-1 */
void vvacosf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvacos (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the arctangent of x[i], for i=0,..,n-1 */
void vvatanf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvatan (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set z[i] to the arctangent of y[i]/x[i], for i=0,..,n-1 */
void vvatan2f (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvatan2 (double * /* z */, const double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set z[i] to the sine of x[i] and y[i] to the cosine of x[i], for i=0,..,n-1 */
void vvsincosf (float * /* z */, float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvsincos (double * /* z */, double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set the real part of C[i] to the cosine of x[i] and the imaginary part of C[i] to the 
   sine of x[i], for i=0,..,n-1 */
void vvcosisinf (__float_complex_t * /* C */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvcosisin (__double_complex_t * /* C */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the hyperbolic sine of x[i], for i=0,..,n-1 */
void vvsinhf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvsinh (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the hyperbolic cosine of x[i], for i=0,..,n-1 */
void vvcoshf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvcosh (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the hyperbolic tangent of x[i], for i=0,..,n-1 */
void vvtanhf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvtanh (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the inverse hyperbolic sine of x[i], for i=0,..,n-1 */
void vvasinhf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvasinh (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the inverse hyperbolic  cosine of x[i], for i=0,..,n-1 */
void vvacoshf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvacosh (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the inverse hyperbolic  tangent of x[i], for i=0,..,n-1 */
void vvatanhf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvatanh (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the integer truncation of x[i], for i=0,..,n-1 */
void vvintf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvint (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the nearest integer to x[i], for i=0,..,n-1 */
void vvnintf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvnint (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the ceiling of x[i], for i=0,..,n-1 */
void vvceilf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvceil (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set y[i] to the floor of x[i], for i=0,..,n-1 */
void vvfloorf (float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
void vvfloor (double * /* y */, const double * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set z[i] to the floating-point remainder of x[i]/y[i], for
   i=0,..,n-1 */
void vvfmodf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* No double-precision version currently available */

/* Set z[i] to the value r such that r = x[i] - N*y[i], where N is the
     integer nearest the exact value of x[i]/y[i].  If there are two
     integers closest to x[i]/y[i], N shall be the even one. If r is
     zero, it is given the same sign as x[i], for i=0,..,n-1 */
void vvremainderf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* No double-precision version currently available */

/* Set z[i] to x[i] with its sign changed to y[i]'s, for i=0,..,n-1 */
void vvcopysignf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* No double-precision version currently available */

/* Set z[i] to the next machine representable number from x[i] in
     direction y[i], for i=0,..,n-1 */
void vvnextafterf (float * /* z */, const float * /* y */, const float * /* x */, const int * /* n */)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* No double-precision version currently available */


#ifdef __cplusplus
}
#endif
#endif /* __VFORCE_H */
