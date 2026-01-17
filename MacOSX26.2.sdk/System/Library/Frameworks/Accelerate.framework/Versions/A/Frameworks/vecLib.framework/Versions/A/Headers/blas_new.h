
#pragma once

#if defined(ACCELERATE_NEW_LAPACK)

#include "lapack_types.h"
#include "lapack_version.h"

#if __has_include(<os/availability.h>)
#   include <os/availability.h>
#else // __has_include(<os/availability.h>)
#   undef API_AVAILABLE
#   define API_AVAILABLE(...) /* Nothing */
#endif // __has_include(<os/availability.h>)

#ifdef __cplusplus
extern "C" {
#endif


// MARK: Auxiliary Routines and Extensions

void xerbla_(char * _Nonnull srname, __LAPACK_int * _Nonnull info)
__LAPACK_ALIAS(xerbla)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: BLAS Level 1

// MARK: AMAX

__LAPACK_int isamax_(const __LAPACK_int * _Nonnull N, const float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(isamax)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

__LAPACK_int idamax_(const __LAPACK_int * _Nonnull N, const double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(idamax)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

__LAPACK_int icamax_(const __LAPACK_int * _Nonnull N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(icamax)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

__LAPACK_int izamax_(const __LAPACK_int * _Nonnull N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(izamax)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: ASUM

float sasum_(const __LAPACK_int * _Nonnull N, const float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(sasum)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double dasum_(const __LAPACK_int * _Nonnull N, const double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dasum)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

float scasum_(const __LAPACK_int * _Nonnull N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(scasum)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double dzasum_(const __LAPACK_int * _Nonnull N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dzasum)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: AXPY

void saxpy_(const __LAPACK_int * _Nonnull N, const float * _Nonnull ALPHA,
            const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(saxpy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void daxpy_(const __LAPACK_int * _Nonnull N, const double * _Nonnull ALPHA,
            const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(daxpy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void caxpy_(const __LAPACK_int * _Nonnull N, const __LAPACK_float_complex * _Nonnull ALPHA,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(caxpy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zaxpy_(const __LAPACK_int * _Nonnull N, const __LAPACK_double_complex * _Nonnull ALPHA,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zaxpy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: AXPBY

void saxpby_(const __LAPACK_int * _Nonnull N, const float * _Nonnull ALPHA,
             const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
             const float * _Nonnull BETA, float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(saxpby)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void daxpby_(const __LAPACK_int * _Nonnull N, const double * _Nonnull ALPHA,
             const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
             const double * _Nonnull BETA, double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(daxpby)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void caxpby_(const __LAPACK_int * _Nonnull N, const __LAPACK_float_complex * _Nonnull ALPHA,
             const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
             const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(caxpby)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zaxpby_(const __LAPACK_int * _Nonnull N, const __LAPACK_double_complex * _Nonnull ALPHA,
             const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
             const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zaxpby)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: COPY

void scopy_(const __LAPACK_int * _Nonnull N,
            const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(scopy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dcopy_(const __LAPACK_int * _Nonnull N,
            const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(dcopy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ccopy_(const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(ccopy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zcopy_(const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zcopy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: DOT

float sdot_(const __LAPACK_int * _Nonnull N,
            const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(sdot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double ddot_(const __LAPACK_int * _Nonnull N,
             const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
             const double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(ddot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: DOTU

void cdotu_(__LAPACK_float_complex * _Nonnull ret_val, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(cdotu)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zdotu_(__LAPACK_double_complex * _Nonnull ret_val, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zdotu)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: DOTC

void cdotc_(__LAPACK_float_complex * _Nonnull ret_val, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(cdotc)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zdotc_(__LAPACK_double_complex * _Nonnull ret_val, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zdotc)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: DSDOT

float sdsdot_(const __LAPACK_int * _Nonnull N, const float * _Nonnull ALPHA,
              const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
              const float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(sdsdot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double dsdot_(const __LAPACK_int * _Nonnull N,
              const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
              const float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(dsdot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: NRM2

float snrm2_(const __LAPACK_int * _Nonnull N, const float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(snrm2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double dnrm2_(const __LAPACK_int * _Nonnull N, const double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dnrm2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

float scnrm2_(const __LAPACK_int * _Nonnull N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(scnrm2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double dznrm2_(const __LAPACK_int * _Nonnull N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dznrm2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: ROT

void srot_(const __LAPACK_int * _Nonnull N,
           float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           float * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
           const float * _Nonnull C, const float * _Nonnull S)
__LAPACK_ALIAS(srot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void drot_(const __LAPACK_int * _Nonnull N,
           double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           double * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
           const double * _Nonnull C, const double * _Nonnull S)
__LAPACK_ALIAS(drot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void csrot_(const __LAPACK_int * _Nonnull N,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            const float * _Nonnull C, const float * _Nonnull S)
__LAPACK_ALIAS(csrot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zdrot_(const __LAPACK_int * _Nonnull N,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            const double * _Nonnull C, const double * _Nonnull S)
__LAPACK_ALIAS(zdrot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: ROTG

void srotg_(float * _Nonnull A, float * _Nonnull B,
            float * _Nonnull C, float * _Nonnull S)
__LAPACK_ALIAS(srotg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void drotg_(double * _Nonnull A, double * _Nonnull B,
            double * _Nonnull C, double * _Nonnull S)
__LAPACK_ALIAS(drotg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void crotg_(__LAPACK_float_complex * _Nonnull A, __LAPACK_float_complex * _Nonnull B, float * _Nonnull C, __LAPACK_float_complex * _Nonnull S)
__LAPACK_ALIAS(crotg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zrotg_(__LAPACK_double_complex * _Nonnull A, __LAPACK_double_complex * _Nonnull B,
           double * _Nonnull C, __LAPACK_double_complex * _Nonnull S)
__LAPACK_ALIAS(zrotg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: ROTM

void srotm_(const __LAPACK_int * _Nonnull N,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            float * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            const float * _Nonnull PARAM)
__LAPACK_ALIAS(srotm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void drotm_(const __LAPACK_int * _Nonnull N,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            double * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            const double * _Nonnull PARAM)
__LAPACK_ALIAS(drotm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: ROTMG

void srotmg_(float * _Nonnull D1, float * _Nonnull D2,
             float * _Nonnull X1, const float * _Nonnull Y1,
             float * _Nonnull PARAM)
__LAPACK_ALIAS(srotmg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void drotmg_(double * _Nonnull D1, double * _Nonnull D2,
             double * _Nonnull X1, const double * _Nonnull Y1,
             double * _Nonnull PARAM)
__LAPACK_ALIAS(drotmg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SCAL

void sscal_(const __LAPACK_int * _Nonnull N, const float * _Nonnull ALPHA,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(sscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dscal_(const __LAPACK_int * _Nonnull N, const double * _Nonnull ALPHA,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cscal_(const __LAPACK_int * _Nonnull N, const __LAPACK_float_complex * _Nonnull ALPHA,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(cscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zscal_(const __LAPACK_int * _Nonnull N, const __LAPACK_double_complex * _Nonnull ALPHA,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(zscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void csscal_(const __LAPACK_int * _Nonnull N, const float * _Nonnull ALPHA,
             __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(csscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zdscal_(const __LAPACK_int * _Nonnull N, const double * _Nonnull ALPHA,
             __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(zdscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SWAP

void sswap_(const __LAPACK_int * _Nonnull N,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(sswap)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dswap_(const __LAPACK_int * _Nonnull N,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(dswap)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cswap_(const __LAPACK_int * _Nonnull N,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(cswap)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zswap_(const __LAPACK_int * _Nonnull N,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zswap)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: BLAS Level 2


// MARK: GEMV

void sgemv_(const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const float * _Nonnull BETA, float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(sgemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dgemv_(const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const double * _Nonnull BETA, double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(dgemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cgemv_(const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(cgemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zgemv_(const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zgemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: GBMV

void sgbmv_(const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_int * _Nonnull KL, const __LAPACK_int * _Nonnull KU,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const float * _Nonnull BETA, float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(sgbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dgbmv_(const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_int * _Nonnull KL, const __LAPACK_int * _Nonnull KU,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const double * _Nonnull BETA, double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(dgbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cgbmv_(const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_int * _Nonnull KL, const __LAPACK_int * _Nonnull KU,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(cgbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zgbmv_(const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_int * _Nonnull KL, const __LAPACK_int * _Nonnull KU,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zgbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: GER

void sger_(const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
           const float * _Nonnull ALPHA, const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           const float * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
           float * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(sger)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dger_(const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
           const double * _Nonnull ALPHA, const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           const double * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
           double * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(dger)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: GERC

void cgerc_(const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(cgerc)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zgerc_(const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(zgerc)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: GERU

void cgeru_(const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(cgeru)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zgeru_(const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(zgeru)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HBMV

void chbmv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(chbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zhbmv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zhbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HEMV

void chemv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(chemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zhemv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zhemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HER

void cher_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
           const float * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(cher)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zher_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
           const double * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(zher)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HER2

void cher2_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(cher2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zher2_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(zher2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HPMV

void chpmv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable AP,
            const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(chpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zhpmv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable AP,
            const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(zhpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HPR

void chpr_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
           const float * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           __LAPACK_float_complex * _Nullable AP)
__LAPACK_ALIAS(chpr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zhpr_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
           const double * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           __LAPACK_double_complex * _Nullable AP)
__LAPACK_ALIAS(zhpr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HPR2

void chpr2_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            __LAPACK_float_complex * _Nullable AP)
__LAPACK_ALIAS(chpr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zhpr2_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            __LAPACK_double_complex * _Nullable AP)
__LAPACK_ALIAS(zhpr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SBMV

void ssbmv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const float * _Nonnull BETA, float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(ssbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dsbmv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const double * _Nonnull BETA, double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(dsbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SPMV

void sspmv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const float * _Nonnull ALPHA, const float * _Nullable AP,
            const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const float * _Nonnull BETA, float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(sspmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dspmv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const double * _Nonnull ALPHA, const double * _Nullable AP,
            const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const double * _Nonnull BETA, double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(dspmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SPR

void sspr_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
           const float * _Nonnull ALPHA, const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           float * _Nullable AP)
__LAPACK_ALIAS(sspr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dspr_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
           const double * _Nonnull ALPHA, const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           double * _Nullable AP)
__LAPACK_ALIAS(dspr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SPR2

void sspr2_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const float * _Nonnull ALPHA, const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const float * _Nullable Y, const __LAPACK_int * _Nonnull INCY, float * _Nullable AP)
__LAPACK_ALIAS(sspr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dspr2_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const double * _Nonnull ALPHA, const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const double * _Nullable Y, const __LAPACK_int * _Nonnull INCY, double * _Nullable AP)
__LAPACK_ALIAS(dspr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYMV

void ssymv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const float * _Nonnull BETA, float * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(ssymv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dsymv_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const double * _Nullable X,const  __LAPACK_int * _Nonnull INCX,
            const double * _Nonnull BETA, double * _Nullable Y, const __LAPACK_int * _Nonnull INCY)
__LAPACK_ALIAS(dsymv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYR

void ssyr_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
           const float * _Nonnull ALPHA, const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           float * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(ssyr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dsyr_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
           const double * _Nonnull ALPHA, const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
           double * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(dsyr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYR2

void ssyr2_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const float * _Nonnull ALPHA, const float * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const float * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            float * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(ssyr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dsyr2_(const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull N,
            const double * _Nonnull ALPHA, const double * _Nullable X, const __LAPACK_int * _Nonnull INCX,
            const double * _Nullable Y, const __LAPACK_int * _Nonnull INCY,
            double * _Nullable A, const __LAPACK_int * _Nonnull LDA)
__LAPACK_ALIAS(dsyr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TBMV

void stbmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(stbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dtbmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dtbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ctbmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ctbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ztbmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ztbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TBSV

void stbsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(stbsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dtbsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dtbsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ctbsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ctbsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ztbsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ztbsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TPMV

void stpmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const float * _Nullable AP,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(stpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dtpmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const double * _Nullable AP,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dtpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ctpmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nullable AP,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ctpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ztpmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nullable AP,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ztpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TPSV

void stpsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const float * _Nullable AP,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(stpsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dtpsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const double * _Nullable AP,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dtpsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ctpsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nullable AP,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ctpsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ztpsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nullable AP,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ztpsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TRMV

void strmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(strmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dtrmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dtrmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ctrmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ctrmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ztrmv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ztrmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TRSV

void strsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            float * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(strsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dtrsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            double * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(dtrsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ctrsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_float_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ctrsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ztrsv_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_double_complex * _Nullable X, const __LAPACK_int * _Nonnull INCX)
__LAPACK_ALIAS(ztrsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: BLAS Level 3

// MARK: GEMM

void sgemm_(const char * _Nonnull TRANSA, const char * _Nonnull TRANSB,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const float * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const float * _Nonnull BETA, float * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(sgemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dgemm_(const char * _Nonnull TRANSA, const char * _Nonnull TRANSB,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const double * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const double * _Nonnull BETA, double * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(dgemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cgemm_(const char * _Nonnull TRANSA, const char * _Nonnull TRANSB,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_float_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(cgemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zgemm_(const char * _Nonnull TRANSA, const char * _Nonnull TRANSB,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_double_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(zgemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HEMM

void chemm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_float_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(chemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zhemm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_double_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(zhemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HERK

void cherk_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const float * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const float * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(cherk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zherk_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const double * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const double * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(zherk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HER2K

void cher2k_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
             const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
             const __LAPACK_float_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
             const float * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(cher2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zher2k_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
             const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
             const __LAPACK_double_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
             const double * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(zher2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYMM

void ssymm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const float * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const float * _Nonnull BETA, float * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(ssymm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dsymm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const double * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const double * _Nonnull BETA, double * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(dsymm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void csymm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_float_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(csymm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zsymm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_double_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(zsymm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYRK

void ssyrk_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const float * _Nonnull BETA, float * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(ssyrk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dsyrk_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const double * _Nonnull BETA, double * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(dsyrk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void csyrk_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(csyrk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zsyrk_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(zsyrk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYR2K

void ssyr2k_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
             const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
             const float * _Nullable B, const __LAPACK_int * _Nonnull LDB,
             const float * _Nonnull BETA, float * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(ssyr2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dsyr2k_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
             const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
             const double * _Nullable B, const __LAPACK_int * _Nonnull LDB,
             const double * _Nonnull BETA, double * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(dsyr2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void csyr2k_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
             const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
             const __LAPACK_float_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
             const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(csyr2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void zsyr2k_(const char * _Nonnull UPLO, const char * _Nonnull TRANS, const __LAPACK_int * _Nonnull N, const __LAPACK_int * _Nonnull K,
             const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
             const __LAPACK_double_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB,
             const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int * _Nonnull LDC)
__LAPACK_ALIAS(zsyr2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TRMM

void strmm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const char * _Nonnull TRANSA, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            float * _Nullable B, const __LAPACK_int * _Nonnull LDB)
__LAPACK_ALIAS(strmm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dtrmm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const char * _Nonnull TRANSA, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            double * _Nullable B, const __LAPACK_int * _Nonnull LDB)
__LAPACK_ALIAS(dtrmm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ctrmm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const char * _Nonnull TRANSA, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_float_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB)
__LAPACK_ALIAS(ctrmm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ztrmm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const char * _Nonnull TRANSA, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_double_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB)
__LAPACK_ALIAS(ztrmm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TRSM

void strsm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const char * _Nonnull TRANSA, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const float * _Nonnull ALPHA, const float * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            float * _Nullable B, const __LAPACK_int * _Nonnull LDB)
__LAPACK_ALIAS(strsm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void dtrsm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const char * _Nonnull TRANSA, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const double * _Nonnull ALPHA, const double * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            double * _Nullable B, const __LAPACK_int * _Nonnull LDB)
__LAPACK_ALIAS(dtrsm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ctrsm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const char * _Nonnull TRANSA, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_float_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB)
__LAPACK_ALIAS(ctrsm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void ztrsm_(const char * _Nonnull SIDE, const char * _Nonnull UPLO, const char * _Nonnull TRANSA, const char * _Nonnull DIAG,
            const __LAPACK_int * _Nonnull M, const __LAPACK_int * _Nonnull N,
            const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int * _Nonnull LDA,
            __LAPACK_double_complex * _Nullable B, const __LAPACK_int * _Nonnull LDB)
__LAPACK_ALIAS(ztrsm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


#ifdef __cplusplus
}
#endif

#endif // #if defined(ACCELERATE_NEW_LAPACK)
