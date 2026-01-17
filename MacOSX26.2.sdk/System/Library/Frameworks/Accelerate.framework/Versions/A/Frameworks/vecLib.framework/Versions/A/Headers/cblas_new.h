
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

#ifndef CBLAS_ENUM_DEFINED_H
#define CBLAS_ENUM_DEFINED_H
enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102 };
enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113, AtlasConj=114};
enum CBLAS_UPLO  {CblasUpper=121, CblasLower=122};
enum CBLAS_DIAG  {CblasNonUnit=131, CblasUnit=132};
enum CBLAS_SIDE  {CblasLeft=141, CblasRight=142};
#endif

// MARK: Auxiliary Routines and Extensions

__LAPACK_int cblas_errprn(__LAPACK_int ierr,  __LAPACK_int info, char * _Nonnull form, ...)
__LAPACK_ALIAS(cblas_errprn)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_xerbla(__LAPACK_int p, char * _Nonnull rout, char * _Nonnull form, ...)
__LAPACK_ALIAS(cblas_xerbla)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

/* Apple extensions to the BLAS interface. */

/* These routines perform linear operations (scalar multiplication and addition)
 * on matrices, with optional transposition.  Specifically, the operation is:
 *
 *      C = alpha * A + beta * B
 *
 * where A and B are optionally transposed as indicated by the value of transA
 * and transB.  This is a surprisingly useful operation; although its function
 * is fairly trivial, efficient implementation has enough subtlety to justify
 * a library interface.
 *
 * As an added convenience, this function supports in-place operation for
 * square matrices; in-place operation for non-square matrices in the face of
 * transposition is a subtle problem outside the scope of this interface.
 * In-place operation is only supported if the leading dimensions match as well
 * as the pointers.  If C overlaps A or B but does not have equal leading
 * dimension, or does not exactly match the source that it overlaps, the
 * behavior of this function is undefined.
 *
 * If alpha or beta is zero, then A (or B, respectively) is ignored entirely,
 * meaning that the memory is not accessed and the data does not contribute
 * to the result (meaning you can pass B == NULL if beta is zero).
 *
 * Note that m and n are the number of rows and columns of C, respectively.
 * If either A or B is transposed, then they are interpreted as n x m matrices.
 */

extern void appleblas_sgeadd(const enum CBLAS_ORDER ORDER,
                             const enum CBLAS_TRANSPOSE TRANSA,
                             const enum CBLAS_TRANSPOSE TRANSB, const __LAPACK_int M, const __LAPACK_int N,
                             const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA,
                             const float BETA, const float * _Nullable B, const __LAPACK_int LDB, float * _Nonnull C,
                             const __LAPACK_int LDC)
__LAPACK_ALIAS(appleblas_sgeadd)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

extern void appleblas_dgeadd(const enum CBLAS_ORDER ORDER,
                             const enum CBLAS_TRANSPOSE TRANSA,
                             const enum CBLAS_TRANSPOSE TRANSB, const __LAPACK_int M, const __LAPACK_int N,
                             const double ALPHA, const double * _Nullable A, const __LAPACK_int LDA,
                             const double BETA, const double * _Nullable B, const __LAPACK_int LDB, double * _Nonnull C,
                             const __LAPACK_int LDC)
__LAPACK_ALIAS(appleblas_dgeadd)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

/* The BLAS standard defines a function, cblas_xerbla( ), and suggests that
 * programs provide their own implementation in order to override default
 * error handling.  This scheme is incompatible with the shared library /
 * framework environment of OS X and iOS.
 *
 * Instead, if you wish to change the default BLAS error handling (which is to
 * print an english error message and exit( )), you need to install your own
 * error handler by calling SetBLASParamErrorProc.
 *
 * Your error handler should adhere to the BLASParamErrorProc interface; it
 * need not terminate program execution.  If your error handler returns normally,
 * then the BLAS call will return normally following its execution without
 * performing any further processing.                                         */

typedef void (*BLASParamErrorProc)(const char * _Nonnull funcName, const char * _Nonnull paramName,
                                   const __LAPACK_int * _Nonnull paramPos,  const __LAPACK_int * _Nonnull paramValue);

void SetBLASParamErrorProc(BLASParamErrorProc _Nonnull __ErrorProc)
__LAPACK_ALIAS(SetBLASParamErrorProc)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: BLAS Level 1

// MARK: AMAX
__LAPACK_int cblas_isamax(const __LAPACK_int N, const float * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_isamax)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

__LAPACK_int cblas_idamax(const __LAPACK_int N, const double * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_idamax)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

__LAPACK_int cblas_icamax(const __LAPACK_int N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_icamax)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

__LAPACK_int cblas_izamax(const __LAPACK_int N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_izamax)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: ASUM
float cblas_sasum(const __LAPACK_int N, const float * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_sasum)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double cblas_dasum(const __LAPACK_int N, const double * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dasum)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

float  cblas_scasum(const __LAPACK_int N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_scasum)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double cblas_dzasum(const __LAPACK_int N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dzasum)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));



// MARK: AXPY
void cblas_saxpy(const __LAPACK_int N, const float ALPHA, const float * _Nullable X,
                 const __LAPACK_int INCX, float * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_saxpy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_daxpy(const __LAPACK_int N, const double ALPHA, const double * _Nullable X,
                 const __LAPACK_int INCX, double * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_daxpy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_caxpy(const __LAPACK_int N, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X,
                 const __LAPACK_int INCX, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_caxpy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zaxpy(const __LAPACK_int N, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X,
                 const __LAPACK_int INCX, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_zaxpy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));



// MARK: AXPBY
void catlas_saxpby(const __LAPACK_int N, const float ALPHA, const float * _Nullable X,
                   const __LAPACK_int INCX, const float BETA, float * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(catlas_saxpby)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void catlas_daxpby(const __LAPACK_int N, const double ALPHA, const double * _Nullable X,
                   const __LAPACK_int INCX, const double BETA, double * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(catlas_daxpby)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void catlas_caxpby(const __LAPACK_int N, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X,
                   const __LAPACK_int INCX, const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(catlas_caxpby)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void catlas_zaxpby(const __LAPACK_int N, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X,
                   const __LAPACK_int INCX, const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(catlas_zaxpby)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: COPY
void cblas_scopy(const __LAPACK_int N, const float * _Nullable X, const __LAPACK_int INCX,
                 float * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_scopy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dcopy(const __LAPACK_int N, const double * _Nullable X, const __LAPACK_int INCX,
                 double * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_dcopy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ccopy(const __LAPACK_int N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                 __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_ccopy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zcopy(const __LAPACK_int N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                 __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_zcopy)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: DOT
float cblas_sdot(const __LAPACK_int N, const float * _Nullable X, const __LAPACK_int INCX,
                 const float * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_sdot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double cblas_ddot(const __LAPACK_int N, const double * _Nullable X, const __LAPACK_int INCX,
                  const double * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_ddot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: DOTU
void cblas_cdotu_sub(const __LAPACK_int N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                     const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_float_complex * _Nonnull DOTU)
__LAPACK_ALIAS(cblas_cdotu_sub)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zdotu_sub(const __LAPACK_int N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                     const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_double_complex * _Nonnull DOTU)
__LAPACK_ALIAS(cblas_zdotu_sub)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: DOTC
void cblas_cdotc_sub(const __LAPACK_int N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                     const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_float_complex * _Nonnull DOTC)
__LAPACK_ALIAS(cblas_cdotc_sub)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zdotc_sub(const __LAPACK_int N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                     const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_double_complex * _Nonnull DOTC)
__LAPACK_ALIAS(cblas_zdotc_sub)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: DSDOT
float cblas_sdsdot(const __LAPACK_int N, const float ALPHA, const float * _Nullable X,
                   const __LAPACK_int INCX, const float * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_sdsdot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


double cblas_dsdot(const __LAPACK_int N, const float * _Nullable X, const __LAPACK_int INCX,
                   const float * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_dsdot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: NRM2
float cblas_snrm2(const __LAPACK_int N, const float * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_snrm2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double cblas_dnrm2(const __LAPACK_int N, const double * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dnrm2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

float  cblas_scnrm2(const __LAPACK_int N, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_scnrm2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

double cblas_dznrm2(const __LAPACK_int N, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dznrm2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: ROT
void cblas_srot(const __LAPACK_int N, float * _Nullable X, const __LAPACK_int INCX, float * _Nullable Y,
                const __LAPACK_int INCY, const float C, const float S)
__LAPACK_ALIAS(cblas_srot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_drot(const __LAPACK_int N, double * _Nullable X, const __LAPACK_int INCX, double * _Nullable Y,
                const __LAPACK_int INCY, const double C, const double S)
__LAPACK_ALIAS(cblas_drot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_csrot(const __LAPACK_int N, __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX, __LAPACK_float_complex * _Nullable Y,
                 const __LAPACK_int INCY, const float C, const float S)
__LAPACK_ALIAS(cblas_csrot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zdrot(const __LAPACK_int N, __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX, __LAPACK_double_complex * _Nullable Y,
                 const __LAPACK_int INCY, const double C, const double S)
__LAPACK_ALIAS(cblas_zdrot)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: ROTG
void cblas_srotg(float * _Nonnull A, float * _Nonnull B, float * _Nonnull C, float * _Nonnull S)
__LAPACK_ALIAS(cblas_srotg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_drotg(double * _Nonnull A, double * _Nonnull B, double * _Nonnull C, double * _Nonnull S)
__LAPACK_ALIAS(cblas_drotg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_crotg(__LAPACK_float_complex * _Nonnull A, __LAPACK_float_complex * _Nonnull B, float * _Nonnull C, __LAPACK_float_complex * _Nonnull S)
__LAPACK_ALIAS(cblas_crotg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zrotg(__LAPACK_double_complex * _Nonnull A, __LAPACK_double_complex * _Nonnull B, double * _Nonnull C, __LAPACK_double_complex * _Nonnull S)
__LAPACK_ALIAS(cblas_zrotg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: ROTM
void cblas_srotm(const __LAPACK_int N, float * _Nullable X, const __LAPACK_int INCX, float * _Nullable Y,
                 const __LAPACK_int INCY, const float * _Nonnull P)
__LAPACK_ALIAS(cblas_srotm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_drotm(const __LAPACK_int N, double * _Nullable X, const __LAPACK_int INCX, double * _Nullable Y,
                 const __LAPACK_int INCY, const double * _Nonnull P)
__LAPACK_ALIAS(cblas_drotm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: ROTMG
void cblas_srotmg(float * _Nonnull D1, float * _Nonnull D2, float * _Nonnull B1, const float B2,
                  float * _Nonnull P)
__LAPACK_ALIAS(cblas_srotmg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_drotmg(double * _Nonnull D1, double * _Nonnull D2, double * _Nonnull B1, const double B2,
                  double * _Nonnull P)
__LAPACK_ALIAS(cblas_drotmg)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: SCAL
void cblas_sscal(const __LAPACK_int N, const float ALPHA, float * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_sscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dscal(const __LAPACK_int N, const double ALPHA, double * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_cscal(const __LAPACK_int N, const __LAPACK_float_complex * _Nonnull ALPHA, __LAPACK_float_complex * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_cscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zscal(const __LAPACK_int N, const __LAPACK_double_complex * _Nonnull ALPHA, __LAPACK_double_complex * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_zscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_csscal(const __LAPACK_int N, const float ALPHA, __LAPACK_float_complex * _Nullable X,
                  const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_csscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zdscal(const __LAPACK_int N, const double ALPHA, __LAPACK_double_complex * _Nullable X,
                  const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_zdscal)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: SET
void catlas_sset(const __LAPACK_int N, const float ALPHA, float * _Nonnull X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(catlas_sset)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void catlas_dset(const __LAPACK_int N, const double ALPHA, double * _Nonnull X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(catlas_dset)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void catlas_cset(const __LAPACK_int N, const __LAPACK_float_complex * _Nonnull ALPHA, __LAPACK_float_complex * _Nonnull X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(catlas_cset)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void catlas_zset(const __LAPACK_int N, const __LAPACK_double_complex * _Nonnull ALPHA, __LAPACK_double_complex * _Nonnull X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(catlas_zset)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: SWAP
void cblas_sswap(const __LAPACK_int N, float * _Nullable X, const __LAPACK_int INCX, float * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_sswap)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dswap(const __LAPACK_int N, double * _Nullable X, const __LAPACK_int INCX, double * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_dswap)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_cswap(const __LAPACK_int N, __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX, __LAPACK_float_complex * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_cswap)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zswap(const __LAPACK_int N, __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX, __LAPACK_double_complex * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_zswap)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));



// MARK: BLAS Level 2


// MARK: GEMV
void cblas_sgemv(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA, const __LAPACK_int M, const __LAPACK_int N,
                 const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA,
                 const float * _Nullable X, const __LAPACK_int INCX, const float BETA, float * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_sgemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dgemv(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA, const __LAPACK_int M, const __LAPACK_int N,
                 const double ALPHA, const double * _Nullable A, const __LAPACK_int LDA,
                 const double * _Nullable X, const __LAPACK_int INCX, const double BETA, double * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_dgemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_cgemv(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_float_complex * _Nullable X,
                 const __LAPACK_int INCX, const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_cgemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zgemv(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_double_complex * _Nullable X,
                 const __LAPACK_int INCX, const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_zgemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: GBMV
void cblas_sgbmv(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_int KL, const __LAPACK_int KU, const float ALPHA, const float * _Nullable A,
                 const __LAPACK_int LDA, const float * _Nullable X, const __LAPACK_int INCX,
                 const float BETA, float * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_sgbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dgbmv(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_int KL, const __LAPACK_int KU, const double ALPHA,
                 const double * _Nullable A, const __LAPACK_int LDA, const double * _Nullable X,
                 const __LAPACK_int INCX, const double BETA, double * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_dgbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_cgbmv(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_int KL, const __LAPACK_int KU, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A,
                 const __LAPACK_int LDA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX, const __LAPACK_float_complex * _Nonnull BETA,
                 __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_cgbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zgbmv(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_int KL, const __LAPACK_int KU, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A,
                 const __LAPACK_int LDA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX, const __LAPACK_double_complex * _Nonnull BETA,
                 __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_zgbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: GER
void cblas_sger(const enum CBLAS_ORDER ORDER, const __LAPACK_int M, const __LAPACK_int N,
                const float ALPHA, const float * _Nullable X, const __LAPACK_int INCX,
                const float * _Nullable Y, const __LAPACK_int INCY, float * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_sger)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dger(const enum CBLAS_ORDER ORDER, const __LAPACK_int M, const __LAPACK_int N,
                const double ALPHA, const double * _Nullable X, const __LAPACK_int INCX,
                const double * _Nullable Y, const __LAPACK_int INCY, double * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_dger)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: GERC
void cblas_cgerc(const enum CBLAS_ORDER ORDER, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                 const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_cgerc)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zgerc(const enum CBLAS_ORDER ORDER, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                 const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_zgerc)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: GERU
void cblas_cgeru(const enum CBLAS_ORDER ORDER, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                 const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_cgeru)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zgeru(const enum CBLAS_ORDER ORDER, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                 const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_zgeru)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HBMV
void cblas_chbmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_int K, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A,
                 const __LAPACK_int LDA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX, const __LAPACK_float_complex * _Nonnull BETA,
                 __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_chbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zhbmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_int K, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A,
                 const __LAPACK_int LDA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX, const __LAPACK_double_complex * _Nonnull BETA,
                 __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_zhbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HEMV
void cblas_chemv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA,
                 const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX, const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_chemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zhemv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA,
                 const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX, const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_zhemv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HER
void cblas_cher(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                const __LAPACK_int N, const float ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_cher)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zher(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                const __LAPACK_int N, const double ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_zher)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HER2
void cblas_cher2(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                 const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_cher2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zher2(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                 const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_zher2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HPMV
void cblas_chpmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable AP, const __LAPACK_float_complex * _Nullable X,
                 const __LAPACK_int INCX, const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_chpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zhpmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable AP, const __LAPACK_double_complex * _Nullable X,
                 const __LAPACK_int INCX, const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_zhpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HPR
void cblas_chpr(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                const __LAPACK_int N, const float ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                __LAPACK_float_complex * _Nullable A)
__LAPACK_ALIAS(cblas_chpr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zhpr(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                const __LAPACK_int N, const double ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                __LAPACK_double_complex * _Nullable A)
__LAPACK_ALIAS(cblas_zhpr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HPR2
void cblas_chpr2(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX,
                 const __LAPACK_float_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_float_complex * _Nullable AP)
__LAPACK_ALIAS(cblas_chpr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zhpr2(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX,
                 const __LAPACK_double_complex * _Nullable Y, const __LAPACK_int INCY, __LAPACK_double_complex * _Nullable AP)
__LAPACK_ALIAS(cblas_zhpr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SBMV
void cblas_ssbmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_int K, const float ALPHA, const float * _Nullable A,
                 const __LAPACK_int LDA, const float * _Nullable X, const __LAPACK_int INCX,
                 const float BETA, float * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_ssbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dsbmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const __LAPACK_int K, const double ALPHA, const double * _Nullable A,
                 const __LAPACK_int LDA, const double * _Nullable X, const __LAPACK_int INCX,
                 const double BETA, double * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_dsbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SPMV
void cblas_sspmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const float ALPHA, const float * _Nullable AP,
                 const float * _Nullable X, const __LAPACK_int INCX, const float BETA, float * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_sspmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dspmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const double ALPHA, const double * _Nullable AP,
                 const double * _Nullable X, const __LAPACK_int INCX, const double BETA, double * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_dspmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SPR
void cblas_sspr(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                const __LAPACK_int N, const float ALPHA, const float * _Nullable X, const __LAPACK_int INCX,
                float * _Nullable AP)
__LAPACK_ALIAS(cblas_sspr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dspr(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                const __LAPACK_int N, const double ALPHA, const double * _Nullable X,
                const __LAPACK_int INCX, double * _Nullable AP)
__LAPACK_ALIAS(cblas_dspr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SPR2
void cblas_sspr2(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const float ALPHA, const float * _Nullable X, const __LAPACK_int INCX,
                 const float * _Nullable Y, const __LAPACK_int INCY, float * _Nullable A)
__LAPACK_ALIAS(cblas_sspr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dspr2(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const double ALPHA, const double * _Nullable X,
                 const __LAPACK_int INCX, const double * _Nullable Y, const __LAPACK_int INCY, double * _Nullable A)
__LAPACK_ALIAS(cblas_dspr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYMV
void cblas_ssymv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA,
                 const float * _Nullable X, const __LAPACK_int INCX, const float BETA, float * _Nullable Y,
                 const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_ssymv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dsymv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const double ALPHA, const double * _Nullable A,
                 const __LAPACK_int LDA, const double * _Nullable X, const __LAPACK_int INCX,
                 const double BETA, double * _Nullable Y, const __LAPACK_int INCY)
__LAPACK_ALIAS(cblas_dsymv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYR
void cblas_ssyr(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                const __LAPACK_int N, const float ALPHA, const float * _Nullable X, const __LAPACK_int INCX,
                float * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_ssyr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dsyr(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                const __LAPACK_int N, const double ALPHA, const double * _Nullable X,
                const __LAPACK_int INCX, double * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_dsyr)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYR2
void cblas_ssyr2(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const float ALPHA, const float * _Nullable X, const __LAPACK_int INCX,
                 const float * _Nullable Y, const __LAPACK_int INCY, float * _Nullable A, const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_ssyr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dsyr2(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const __LAPACK_int N, const double ALPHA, const double * _Nullable X,
                 const __LAPACK_int INCX, const double * _Nullable Y, const __LAPACK_int INCY, double * _Nullable A,
                 const __LAPACK_int LDA)
__LAPACK_ALIAS(cblas_dsyr2)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TBMV
void cblas_stbmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_int K, const float * _Nullable A, const __LAPACK_int LDA,
                 float * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_stbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dtbmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_int K, const double * _Nullable A, const __LAPACK_int LDA,
                 double * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dtbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ctbmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_int K, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA,
                 __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ctbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ztbmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_int K, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA,
                 __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ztbmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TBSV
void cblas_stbsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_int K, const float * _Nullable A, const __LAPACK_int LDA,
                 float * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_stbsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dtbsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_int K, const double * _Nullable A, const __LAPACK_int LDA,
                 double * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dtbsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ctbsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_int K, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA,
                 __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ctbsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ztbsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_int K, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA,
                 __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ztbsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TPMV
void cblas_stpmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const float * _Nullable AP, float * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_stpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dtpmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const double * _Nullable AP, double * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dtpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ctpmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_float_complex * _Nullable AP, __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ctpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ztpmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_double_complex * _Nullable AP, __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ztpmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TPSV
void cblas_stpsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const float * _Nullable AP, float * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_stpsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dtpsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const double * _Nullable AP, double * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dtpsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ctpsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_float_complex * _Nullable AP, __LAPACK_float_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ctpsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ztpsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_double_complex * _Nullable AP, __LAPACK_double_complex * _Nullable X, const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ztpsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


// MARK: TRMV
void cblas_strmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const float * _Nullable A, const __LAPACK_int LDA, float * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_strmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dtrmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const double * _Nullable A, const __LAPACK_int LDA, double * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dtrmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ctrmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, __LAPACK_float_complex * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ctrmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ztrmv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, __LAPACK_double_complex * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ztrmv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TRSV
void cblas_strsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const float * _Nullable A, const __LAPACK_int LDA, float * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_strsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dtrsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const double * _Nullable A, const __LAPACK_int LDA, double * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_dtrsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ctrsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, __LAPACK_float_complex * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ctrsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ztrsv(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANSA, const enum CBLAS_DIAG DIAG,
                 const __LAPACK_int N, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, __LAPACK_double_complex * _Nullable X,
                 const __LAPACK_int INCX)
__LAPACK_ALIAS(cblas_ztrsv)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: BLAS Level 3

// MARK: GEMM
void cblas_sgemm(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_TRANSPOSE TRANSB, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_int K, const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA,
                 const float * _Nullable B, const __LAPACK_int LDB, const float BETA, float * _Nullable C,
                 const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_sgemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dgemm(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_TRANSPOSE TRANSB, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_int K, const double ALPHA, const double * _Nullable A,
                 const __LAPACK_int LDA, const double * _Nullable B, const __LAPACK_int LDB,
                 const double BETA, double * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_dgemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_cgemm(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_TRANSPOSE TRANSB, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_int K, const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA,
                 const __LAPACK_float_complex * _Nullable B, const __LAPACK_int LDB, const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C,
                 const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_cgemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zgemm(const enum CBLAS_ORDER ORDER,
                 const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_TRANSPOSE TRANSB, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_int K, const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA,
                 const __LAPACK_double_complex * _Nullable B, const __LAPACK_int LDB, const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C,
                 const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_zgemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HEMM
void cblas_chemm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_float_complex * _Nullable B,
                 const __LAPACK_int LDB, const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_chemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zhemm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_double_complex * _Nullable B,
                 const __LAPACK_int LDB, const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_zhemm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HERK
void cblas_cherk(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                 const float ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA,
                 const float BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_cherk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zherk(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                 const double ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA,
                 const double BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_zherk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: HER2K
void cblas_cher2k(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                  const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                  const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_float_complex * _Nullable B,
                  const __LAPACK_int LDB, const float BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_cher2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zher2k(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                  const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                  const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_double_complex * _Nullable B,
                  const __LAPACK_int LDB, const double BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_zher2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYMM
void cblas_ssymm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const __LAPACK_int M, const __LAPACK_int N,
                 const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA,
                 const float * _Nullable B, const __LAPACK_int LDB, const float BETA, float * _Nullable C,
                 const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_ssymm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dsymm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const __LAPACK_int M, const __LAPACK_int N,
                 const double ALPHA, const double * _Nullable A, const __LAPACK_int LDA,
                 const double * _Nullable B, const __LAPACK_int LDB, const double BETA, double * _Nullable C,
                 const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_dsymm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_csymm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_float_complex * _Nullable B,
                 const __LAPACK_int LDB, const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_csymm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zsymm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_double_complex * _Nullable B,
                 const __LAPACK_int LDB, const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_zsymm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYRK
void cblas_ssyrk(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                 const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA,
                 const float BETA, float * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_ssyrk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dsyrk(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                 const double ALPHA, const double * _Nullable A, const __LAPACK_int LDA,
                 const double BETA, double * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_dsyrk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_csyrk(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                 const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA,
                 const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_csyrk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zsyrk(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                 const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                 const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA,
                 const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_zsyrk)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: SYR2K
void cblas_ssyr2k(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                  const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                  const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA,
                  const float * _Nullable B, const __LAPACK_int LDB, const float BETA, float * _Nullable C,
                  const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_ssyr2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dsyr2k(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                  const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                  const double ALPHA, const double * _Nullable A, const __LAPACK_int LDA,
                  const double * _Nullable B, const __LAPACK_int LDB, const double BETA, double * _Nullable C,
                  const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_dsyr2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_csyr2k(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                  const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                  const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_float_complex * _Nullable B,
                  const __LAPACK_int LDB, const __LAPACK_float_complex * _Nonnull BETA, __LAPACK_float_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_csyr2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_zsyr2k(const enum CBLAS_ORDER ORDER, const enum CBLAS_UPLO UPLO,
                  const enum CBLAS_TRANSPOSE TRANS, const __LAPACK_int N, const __LAPACK_int K,
                  const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, const __LAPACK_double_complex * _Nullable B,
                  const __LAPACK_int LDB, const __LAPACK_double_complex * _Nonnull BETA, __LAPACK_double_complex * _Nullable C, const __LAPACK_int LDC)
__LAPACK_ALIAS(cblas_zsyr2k)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TRMM
void cblas_strmm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_DIAG DIAG, const __LAPACK_int M, const __LAPACK_int N,
                 const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA, float * _Nullable B,
                 const __LAPACK_int LDB)
__LAPACK_ALIAS(cblas_strmm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dtrmm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_DIAG DIAG, const __LAPACK_int M, const __LAPACK_int N,
                 const double ALPHA, const double * _Nullable A, const __LAPACK_int LDA, double * _Nullable B,
                 const __LAPACK_int LDB)
__LAPACK_ALIAS(cblas_dtrmm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ctrmm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_DIAG DIAG, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, __LAPACK_float_complex * _Nullable B,
                 const __LAPACK_int LDB)
__LAPACK_ALIAS(cblas_ctrmm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ztrmm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_DIAG DIAG, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, __LAPACK_double_complex * _Nullable B,
                 const __LAPACK_int LDB)
__LAPACK_ALIAS(cblas_ztrmm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// MARK: TRSM
void cblas_strsm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_DIAG DIAG, const __LAPACK_int M, const __LAPACK_int N,
                 const float ALPHA, const float * _Nullable A, const __LAPACK_int LDA, float * _Nullable B,
                 const __LAPACK_int LDB)
__LAPACK_ALIAS(cblas_strsm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_dtrsm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_DIAG DIAG, const __LAPACK_int M, const __LAPACK_int N,
                 const double ALPHA, const double * _Nullable A, const __LAPACK_int LDA, double * _Nullable B,
                 const __LAPACK_int LDB)
__LAPACK_ALIAS(cblas_dtrsm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ctrsm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_DIAG DIAG, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_float_complex * _Nonnull ALPHA, const __LAPACK_float_complex * _Nullable A, const __LAPACK_int LDA, __LAPACK_float_complex * _Nullable B,
                 const __LAPACK_int LDB)
__LAPACK_ALIAS(cblas_ctrsm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

void cblas_ztrsm(const enum CBLAS_ORDER ORDER, const enum CBLAS_SIDE SIDE,
                 const enum CBLAS_UPLO UPLO, const enum CBLAS_TRANSPOSE TRANSA,
                 const enum CBLAS_DIAG DIAG, const __LAPACK_int M, const __LAPACK_int N,
                 const __LAPACK_double_complex * _Nonnull ALPHA, const __LAPACK_double_complex * _Nullable A, const __LAPACK_int LDA, __LAPACK_double_complex * _Nullable B,
                 const __LAPACK_int LDB)
__LAPACK_ALIAS(cblas_ztrsm)
API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));


#ifdef __cplusplus
}
#endif

#endif // #if defined(ACCELERATE_NEW_LAPACK)
