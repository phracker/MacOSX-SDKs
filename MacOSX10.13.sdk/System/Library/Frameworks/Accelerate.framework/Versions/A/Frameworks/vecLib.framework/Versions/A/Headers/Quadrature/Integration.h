// Numerical integration

#ifndef QUADRATURE_INTEGRATION_H
#define QUADRATURE_INTEGRATION_H

#include <stddef.h>

// Availability
#if __has_include( <Availability.h> )
#include <Availability.h>
#else
#define __OSX_AVAILABLE(a)
#define __IOS_AVAILABLE(a)
#define __TVOS_AVAILABLE(a)
#define __WATCHOS_AVAILABLE(a)
#endif

// Nullability
#if __has_feature(assume_nonnull)
  _Pragma("clang assume_nonnull begin")
#else
#define _Null_unspecified
#define _Nullable
#endif

/*!
@abstract Y=F(X) one-dimensional real function, array form, double precision

@discussion Should set values <tt>y[i] = F(x[i])</tt> for i=0..n-1.

@param arg User argument passed back to the function when evaluated
@param n Dimension of arrays X and Y
@param x Array of points to evaluate the function
@param y Array receiving the values
*/
typedef void (*quadrature_function_array)(void * _Null_unspecified __arg, size_t __n, const double *__x, double *__y);

/*! @enum quadrature_integrator

@abstract Integrators

@constant QUADRATURE_INTEGRATE_QNG
Simple non-adaptive automatic integrator using Gauss-Kronrod-Patterson quadrature coefficients.
Evaluates 21, or 43, or 87 points in the interval until the requested accuracy is reached.
No workspace is necessary for this integrator.

@constant QUADRATURE_INTEGRATE_QAG
Simple globally adaptive integrator.
Allows selection of the number of Gauss-Kronrod points used in each subinterval, and the max number of subintervals.

@constant QUADRATURE_INTEGRATE_QAGS
Global adaptive quadrature based on 21-point or 15-point (if at least one bound is infinite) Gauss–Kronrod quadrature within each subinterval, with acceleration by Peter Wynn's epsilon algorithm.
If at least one of the interval bounds is infinite, this is equivalent to the QUADPACK QAGI routine. Otherwise, this is equivalent to the QUADPACK QAGS routine.

*/
typedef enum {

  QUADRATURE_INTEGRATE_QNG,
  QUADRATURE_INTEGRATE_QAG,
  QUADRATURE_INTEGRATE_QAGS

} quadrature_integrator;

/*!
@abstract Bytes per interval to allocate in workspace for the QAG integrator. */
#define QUADRATURE_INTEGRATE_QAG_WORKSPACE_PER_INTERVAL 32

/*!
@abstract Bytes per interval to allocate in workspace for the QAGS integrator. */
#define QUADRATURE_INTEGRATE_QAGS_WORKSPACE_PER_INTERVAL 152

/*!
@abstract Function to integrate

@discussion Describes a real function Y=F(X). Since most of the integration time is spent
evaluating F, we allow the caller to provide a array callback, computing several values of F
in a single call.

@field fun Y=F(X) callback.
@field fun_arg User pointer passed as first argument to all invocations of <tt>fun</tt>.
*/
typedef struct {

  quadrature_function_array fun;
  void * _Null_unspecified fun_arg;

} quadrature_integrate_function;

/*!
@abstract Integration options

@field integrator Integration algorithm to apply.
@field abs_tolerance Requested absolute tolerance on the result.
@field rel_tolerance Requested relative tolerance on the result.

@field qag_points_per_interval Number of Gauss-Kronrod points per interval used by the QAG integrator.
Can be 0, 15, 21, 31, 41, 51, 61. 0 maps to the default 21.
Used by the QAG integrator only. Other integrators ignore this value.

@field max_intervals Limit the number of intervals in the subdivision used by adaptive integrators.
If a workspace is provided, this value is ignored, and the number of intervals is limited by <tt>workspace_size</tt>.
<br>The QNG integrator doesn't require a workspace.
<br>The QAG integrator requires at least <tt>max_intervals * QUADRATURE_INTEGRATE_QAG_WORKSPACE_PER_INTERVAL</tt> bytes in <tt>workspace</tt>.
<br>The QAGS integrator requires at least <tt>max_intervals * QUADRATURE_INTEGRATE_QAGS_WORKSPACE_PER_INTERVAL</tt> bytes in <tt>workspace</tt>.

*/
typedef struct {

  quadrature_integrator integrator;
  double abs_tolerance;
  double rel_tolerance;
  size_t qag_points_per_interval;
  size_t max_intervals;
  
} quadrature_integrate_options;

/*!
@abstract Integrate a function F over ]A,B[.

@discussion
This function provides a set of algorithms (integrators) to compute an approximation S' of the integral S = &int; F(x) dx over the interval ]A,B[.

The QNG (simple non-adaptive Gauss-Kronrod integration) and QAG (simple adaptive Gauss-Kronrod integration)
integrators are C ports of the QUADPACK library corresponding routines.
The QAGS integrator provides the functionality offered by the QAGS and QAGI QUADPACK routines.

On success, S' is assumed to verify abs(S-S') &le; max(abs_tolerance, rel_tolerance * abs(S)).
The integration algorithms will identify <b>most</b> cases of divergence, slow convergence, and bad behaviour, and report an error.
The bounds a,b do not need to verify a &le; b. If the integrator is QAGS, one or both of the interval bounds can be infinite (-INFINITY or +INFINITY).

Unless F is known to be smooth enough to guarantee success, it is strongly advised to always check the returned status and absolute error.

The QUADPACK library documentation provides a decision tree to select the integrator.
Adapted to match the contents of this library, this decision tree becomes:

<b>Integration over a finite region</b>

<ul>
<li>If performance is not a concern and you don’t know much about the specifics of the problem, use QAGS.
<li>Otherwise, if the integrand is smooth, use QNG or QAG if the requested tolerance couldn't be reached with QNG.
<li>Otherwise, if there are discontinuities or singularities of the integrand or of its derivative, and you know where they are,
split the integration range at these points and analyze each subinterval.
<li>Otherwise, if the integrand has end point singularities, use QAGS.
<li>Otherwise, if the integrand has an oscillatory behavior of nonspecific type, and no singularities, use QAG with 61 points per interval.
<li>Otherwise, use QAGS.
</ul>

<b>Integration over an infinite region</b>

<ul>
<li>If the integrand decays rapidly to zero, truncate the interval and use the finite interval decision tree.
<li>Otherwise, if you are not constrained by computer time, and do not wish to analyze the problem further, use QAGS.
<li>Otherwise, if the integrand has a non-smooth behavior in the range, and you know where it occurs, split off these regions and use
the appropriate finite range routines to integrate over them. Then begin this tree again to handle the remainder of the region.
<li>Otherwise, truncation of the interval, or application of a suitable transformation for reducing the problem to a finite range may be possible.
</ul>

QUADPACK Reference:
Robert Piessens, Elise deDoncker-Kapenga, Christian Ueberhuber, David Kahaner,
QUADPACK: A Subroutine Package for Automatic Integration,
Springer, 1983, ISBN: 3540125531, LC: QA299.3.Q36.

@param f Function to integrate. Can't be NULL.
@param a First bound of the integration interval. May be +/- INFINITY for QAGS.
@param b Second bound of the integration interval. May be +/- INFINITY for QAGS.
@param options Integration options. Can't be NULL.
@param status If not NULL, <tt>*status</tt> receives QUADRATURE_SUCCESS if the integration was successful, and a negative QUADRATURE_..._ERROR code on failure.
@param abs_error If not NULL, <tt>*abs_error</tt> receives an estimate of the absolute error on the result.
@param workspace_size Number of bytes allocated in <tt>workspace</tt>, or 0.
@param workspace If not NULL, points to a work buffer of <tt>workspace_size</tt> bytes. In that case, no additional memory will be allocated.
If NULL, the function will internally allocate a workspace buffer if one is needed.

@return Returns an approximation to the integral.
*/
extern double quadrature_integrate(const quadrature_integrate_function * __f,
                                   double __a,
                                   double __b,
                                   const quadrature_integrate_options * options,
                                   quadrature_status * _Nullable status,
                                   double * _Nullable abs_error,
                                   size_t workspace_size,
                                   void * __restrict _Nullable workspace)
__OSX_AVAILABLE(10.12) __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

// Availability
#if !__has_include(<Availability.h>)
#undef __OSX_AVAILABLE
#undef __IOS_AVAILABLE
#undef __TVOS_AVAILABLE
#undef __WATCHOS_AVAILABLE
#endif

// Nullability
#if __has_feature(assume_nonnull)
  _Pragma("clang assume_nonnull end")
#else
#undef _Nullable
#undef _Null_unspecified
#endif

#endif // QUADRATURE_INTEGRATION_H
