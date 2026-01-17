/* cblas.h
 *
 * This header defines C bindings for the Basic Linear Algebra Subprograms,
 * providing optimized basic operations on vectors and matrices.  Single-
 * and double-precision, real and complex data formats are supported by this
 * library.
 *
 * A note on complex data layouts:
 *
 * In order to allow straightforward interoperation with other libraries and
 * complex types in C and C++, complex data in BLAS is passed through an opaque
 * pointer (void *).  The layout requirements on this complex data are that
 * the real and imaginary parts are stored consecutively in memory, and have
 * the alignment of the corresponding real type (float or double).  The BLAS
 * complex interfaces are compatible with the following types:
 *
 *     - The C complex types, defined in <complex.h>.
 *     - The C++ std::complex types, defined in <complex>.
 *     - The LAPACK complex types, defined in <Accelerate/vecLib/clapack.h>.
 *     - The vDSP types DSPComplex and DSPDoubleComplex, defined in <Accelerate/vecLib/vDSP.h>.
 *     - An array of size two of the corresponding real type.
 *     - A structure containing two elements, each of the corresponding real type.
 *
 */

#ifndef CBLAS_H

#ifdef __cplusplus
extern "C" {
#endif
  
#ifndef CBLAS_ENUM_DEFINED_H
#define CBLAS_ENUM_DEFINED_H
  enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102 };
  enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113,
    AtlasConj=114};
  enum CBLAS_UPLO  {CblasUpper=121, CblasLower=122};
  enum CBLAS_DIAG  {CblasNonUnit=131, CblasUnit=132};
  enum CBLAS_SIDE  {CblasLeft=141, CblasRight=142};
#endif  /* CBLAS_ENUM_DEFINED_H */
  
#ifndef CBLAS_ENUM_ONLY
#define CBLAS_H
#define CBLAS_INDEX int
  
#include <stdint.h>
#if __has_include(<os/availability.h>)
# include <os/availability.h>
#else // __has_include(<os/availability.h>)
# undef API_AVAILABLE
# define API_AVAILABLE(...) /* Nothing */
#endif // __has_include(<os/availability.h>)
  
int cblas_errprn(int __ierr, int __info, char *__form, ...)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_xerbla(int __p, char *__rout, char *__form, ...)
API_AVAILABLE(macos(10.2), ios(4.0));

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS functions (complex are recast as routines)
 * ===========================================================================
 */
float  cblas_sdsdot(const int __N, const float __alpha, const float *__X,
                    const int __incX, const float *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
double cblas_dsdot(const int __N, const float *__X, const int __incX,
                   const float *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
float  cblas_sdot(const int __N, const float *__X, const int __incX,
                  const float *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
double cblas_ddot(const int __N, const double *__X, const int __incX,
                  const double *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
/*
 * Functions having prefixes Z and C only
 */
void   cblas_cdotu_sub(const int __N, const void *__X, const int __incX,
                       const void *__Y, const int __incY, void *__dotu)
API_AVAILABLE(macos(10.2), ios(4.0));
void   cblas_cdotc_sub(const int __N, const void *__X, const int __incX,
                       const void *__Y, const int __incY, void *__dotc)
API_AVAILABLE(macos(10.2), ios(4.0));

void   cblas_zdotu_sub(const int __N, const void *__X, const int __incX,
                       const void *__Y, const int __incY, void *__dotu)
API_AVAILABLE(macos(10.2), ios(4.0));
void   cblas_zdotc_sub(const int __N, const void *__X, const int __incX,
                       const void *__Y, const int __incY, void *__dotc)
API_AVAILABLE(macos(10.2), ios(4.0));


/*
 * Functions having prefixes S D SC DZ
 */
float  cblas_snrm2(const int __N, const float *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
float  cblas_sasum(const int __N, const float *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

double cblas_dnrm2(const int __N, const double *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
double cblas_dasum(const int __N, const double *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

float  cblas_scnrm2(const int __N, const void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
float  cblas_scasum(const int __N, const void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

double cblas_dznrm2(const int __N, const void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
double cblas_dzasum(const int __N, const void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));


/*
 * Functions having standard 4 prefixes (S D C Z)
 */
CBLAS_INDEX cblas_isamax(const int __N, const float *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
CBLAS_INDEX cblas_idamax(const int __N, const double *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
CBLAS_INDEX cblas_icamax(const int __N, const void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
CBLAS_INDEX cblas_izamax(const int __N, const void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS routines
 * ===========================================================================
 */

/*
 * Routines with standard 4 prefixes (s, d, c, z)
 */
void cblas_sswap(const int __N, float *__X, const int __incX, float *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_scopy(const int __N, const float *__X, const int __incX, float *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_saxpy(const int __N, const float __alpha, const float *__X,
                 const int __incX, float *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void catlas_saxpby(const int __N, const float __alpha, const float *__X,
                   const int __incX, const float __beta, float *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void catlas_sset(const int __N, const float __alpha, float *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_dswap(const int __N, double *__X, const int __incX, double *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dcopy(const int __N, const double *__X, const int __incX,
                 double *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_daxpy(const int __N, const double __alpha, const double *__X,
                 const int __incX, double *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void catlas_daxpby(const int __N, const double __alpha, const double *__X,
                   const int __incX, const double __beta, double *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void catlas_dset(const int __N, const double __alpha, double *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_cswap(const int __N, void *__X, const int __incX, void *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ccopy(const int __N, const void *__X, const int __incX, void *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_caxpy(const int __N, const void *__alpha, const void *__X,
                 const int __incX, void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void catlas_caxpby(const int __N, const void *__alpha, const void *__X,
                   const int __incX, const void *__beta, void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void catlas_cset(const int __N, const void *__alpha, void *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_zswap(const int __N, void *__X, const int __incX, void *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zcopy(const int __N, const void *__X, const int __incX, void *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zaxpy(const int __N, const void *__alpha, const void *__X,
                 const int __incX, void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void catlas_zaxpby(const int __N, const void *__alpha, const void *__X,
                   const int __incX, const void *__beta, void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void catlas_zset(const int __N, const void *__alpha, void *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));


/*
 * Routines with S and D prefix only
 */
void cblas_srotg(float *__a, float *__b, float *__c, float *__s)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_srotmg(float *__d1, float *__d2, float *__b1, const float __b2,
                  float *__P)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_srot(const int __N, float *__X, const int __incX, float *__Y,
                const int __incY, const float __c, const float __s)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_srotm(const int __N, float *__X, const int __incX, float *__Y,
                 const int __incY, const float *__P)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_drotg(double *__a, double *__b, double *__c, double *__s)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_drotmg(double *__d1, double *__d2, double *__b1, const double __b2,
                  double *__P)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_drot(const int __N, double *__X, const int __incX, double *__Y,
                const int __incY, const double __c, const double __s)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_drotm(const int __N, double *__X, const int __incX, double *__Y,
                 const int __incY, const double *__P)
API_AVAILABLE(macos(10.2), ios(4.0));


/*
 * Routines with S D C Z CS and ZD prefixes
 */
void cblas_sscal(const int __N, const float __alpha, float *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dscal(const int __N, const double __alpha, double *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_cscal(const int __N, const void *__alpha, void *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zscal(const int __N, const void *__alpha, void *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_csscal(const int __N, const float __alpha, void *__X,
                  const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zdscal(const int __N, const double __alpha, void *__X,
                  const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

/*
 * Extra reference routines provided by ATLAS, but not mandated by the standard
 */
void cblas_crotg(void *__a, void *__b, void *__c, void *__s)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zrotg(void *__a, void *__b, void *__c, void *__s)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_csrot(const int __N, void *__X, const int __incX, void *__Y,
                 const int __incY, const float __c, const float __s)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zdrot(const int __N, void *__X, const int __incX, void *__Y,
                 const int __incY, const double __c, const double __s)
API_AVAILABLE(macos(10.2), ios(4.0));

/*
 * ===========================================================================
 * Prototypes for level 2 BLAS
 * ===========================================================================
 */

/*
 * Routines with standard 4 prefixes (S, D, C, Z)
 */
void cblas_sgemv(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA, const int __M, const int __N,
                 const float __alpha, const float *__A, const int __lda,
                 const float *__X, const int __incX, const float __beta, float *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_sgbmv(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA, const int __M, const int __N,
                 const int __KL, const int __KU, const float __alpha, const float *__A,
                 const int __lda, const float *__X, const int __incX,
                 const float __beta, float *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_strmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const float *__A, const int __lda, float *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_stbmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const int __K, const float *__A, const int __lda,
                 float *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_stpmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const float *__Ap, float *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_strsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const float *__A, const int __lda, float *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_stbsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const int __K, const float *__A, const int __lda,
                 float *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_stpsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const float *__Ap, float *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_dgemv(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA, const int __M, const int __N,
                 const double __alpha, const double *__A, const int __lda,
                 const double *__X, const int __incX, const double __beta, double *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dgbmv(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA, const int __M, const int __N,
                 const int __KL, const int __KU, const double __alpha,
                 const double *__A, const int __lda, const double *__X,
                 const int __incX, const double __beta, double *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dtrmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const double *__A, const int __lda, double *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dtbmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const int __K, const double *__A, const int __lda,
                 double *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dtpmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const double *__Ap, double *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dtrsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const double *__A, const int __lda, double *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dtbsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const int __K, const double *__A, const int __lda,
                 double *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dtpsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const double *__Ap, double *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_cgemv(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, const void *__X,
                 const int __incX, const void *__beta, void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_cgbmv(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA, const int __M, const int __N,
                 const int __KL, const int __KU, const void *__alpha, const void *__A,
                 const int __lda, const void *__X, const int __incX, const void *__beta,
                 void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ctrmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const void *__A, const int __lda, void *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ctbmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const int __K, const void *__A, const int __lda,
                 void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ctpmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const void *__Ap, void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ctrsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const void *__A, const int __lda, void *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ctbsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const int __K, const void *__A, const int __lda,
                 void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ctpsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const void *__Ap, void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_zgemv(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, const void *__X,
                 const int __incX, const void *__beta, void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zgbmv(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA, const int __M, const int __N,
                 const int __KL, const int __KU, const void *__alpha, const void *__A,
                 const int __lda, const void *__X, const int __incX, const void *__beta,
                 void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ztrmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const void *__A, const int __lda, void *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ztbmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const int __K, const void *__A, const int __lda,
                 void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ztpmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const void *__Ap, void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ztrsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const void *__A, const int __lda, void *__X,
                 const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ztbsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const int __K, const void *__A, const int __lda,
                 void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ztpsv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __TransA, const enum CBLAS_DIAG __Diag,
                 const int __N, const void *__Ap, void *__X, const int __incX)
API_AVAILABLE(macos(10.2), ios(4.0));


/*
 * Routines with S and D prefixes only
 */
void cblas_ssymv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const float __alpha, const float *__A, const int __lda,
                 const float *__X, const int __incX, const float __beta, float *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ssbmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const int __K, const float __alpha, const float *__A,
                 const int __lda, const float *__X, const int __incX,
                 const float __beta, float *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_sspmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const float __alpha, const float *__Ap,
                 const float *__X, const int __incX, const float __beta, float *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_sger(const enum CBLAS_ORDER __Order, const int __M, const int __N,
                const float __alpha, const float *__X, const int __incX,
                const float *__Y, const int __incY, float *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ssyr(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                const int __N, const float __alpha, const float *__X, const int __incX,
                float *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_sspr(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                const int __N, const float __alpha, const float *__X, const int __incX,
                float *__Ap)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ssyr2(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const float __alpha, const float *__X, const int __incX,
                 const float *__Y, const int __incY, float *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_sspr2(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const float __alpha, const float *__X, const int __incX,
                 const float *__Y, const int __incY, float *__A)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_dsymv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const double __alpha, const double *__A,
                 const int __lda, const double *__X, const int __incX,
                 const double __beta, double *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dsbmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const int __K, const double __alpha, const double *__A,
                 const int __lda, const double *__X, const int __incX,
                 const double __beta, double *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dspmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const double __alpha, const double *__Ap,
                 const double *__X, const int __incX, const double __beta, double *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dger(const enum CBLAS_ORDER __Order, const int __M, const int __N,
                const double __alpha, const double *__X, const int __incX,
                const double *__Y, const int __incY, double *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dsyr(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                const int __N, const double __alpha, const double *__X,
                const int __incX, double *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dspr(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                const int __N, const double __alpha, const double *__X,
                const int __incX, double *__Ap)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dsyr2(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const double __alpha, const double *__X,
                 const int __incX, const double *__Y, const int __incY, double *__A,
                 const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dspr2(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const double __alpha, const double *__X,
                 const int __incX, const double *__Y, const int __incY, double *__A)
API_AVAILABLE(macos(10.2), ios(4.0));


/*
 * Routines with C and Z prefixes only
 */
void cblas_chemv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const void *__alpha, const void *__A, const int __lda,
                 const void *__X, const int __incX, const void *__beta, void *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_chbmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const int __K, const void *__alpha, const void *__A,
                 const int __lda, const void *__X, const int __incX, const void *__beta,
                 void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_chpmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const void *__alpha, const void *__Ap, const void *__X,
                 const int __incX, const void *__beta, void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_cgeru(const enum CBLAS_ORDER __Order, const int __M, const int __N,
                 const void *__alpha, const void *__X, const int __incX,
                 const void *__Y, const int __incY, void *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_cgerc(const enum CBLAS_ORDER __Order, const int __M, const int __N,
                 const void *__alpha, const void *__X, const int __incX,
                 const void *__Y, const int __incY, void *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_cher(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                const int __N, const float __alpha, const void *__X, const int __incX,
                void *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_chpr(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                const int __N, const float __alpha, const void *__X, const int __incX,
                void *__A)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_cher2(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const void *__alpha, const void *__X, const int __incX,
                 const void *__Y, const int __incY, void *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_chpr2(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const void *__alpha, const void *__X, const int __incX,
                 const void *__Y, const int __incY, void *__Ap)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_zhemv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const void *__alpha, const void *__A, const int __lda,
                 const void *__X, const int __incX, const void *__beta, void *__Y,
                 const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zhbmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const int __K, const void *__alpha, const void *__A,
                 const int __lda, const void *__X, const int __incX, const void *__beta,
                 void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zhpmv(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const void *__alpha, const void *__Ap, const void *__X,
                 const int __incX, const void *__beta, void *__Y, const int __incY)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zgeru(const enum CBLAS_ORDER __Order, const int __M, const int __N,
                 const void *__alpha, const void *__X, const int __incX,
                 const void *__Y, const int __incY, void *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zgerc(const enum CBLAS_ORDER __Order, const int __M, const int __N,
                 const void *__alpha, const void *__X, const int __incX,
                 const void *__Y, const int __incY, void *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zher(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                const int __N, const double __alpha, const void *__X, const int __incX,
                void *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zhpr(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                const int __N, const double __alpha, const void *__X, const int __incX,
                void *__A)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zher2(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const void *__alpha, const void *__X, const int __incX,
                 const void *__Y, const int __incY, void *__A, const int __lda)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zhpr2(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const int __N, const void *__alpha, const void *__X, const int __incX,
                 const void *__Y, const int __incY, void *__Ap)
API_AVAILABLE(macos(10.2), ios(4.0));

/*
 * ===========================================================================
 * Prototypes for level 3 BLAS
 * ===========================================================================
 */

/*
 * Routines with standard 4 prefixes (S, D, C, Z)
 */
void cblas_sgemm(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_TRANSPOSE __TransB, const int __M, const int __N,
                 const int __K, const float __alpha, const float *__A, const int __lda,
                 const float *__B, const int __ldb, const float __beta, float *__C,
                 const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ssymm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const int __M, const int __N,
                 const float __alpha, const float *__A, const int __lda,
                 const float *__B, const int __ldb, const float __beta, float *__C,
                 const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ssyrk(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                 const float __alpha, const float *__A, const int __lda,
                 const float __beta, float *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ssyr2k(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                  const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                  const float __alpha, const float *__A, const int __lda,
                  const float *__B, const int __ldb, const float __beta, float *__C,
                  const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_strmm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_DIAG __Diag, const int __M, const int __N,
                 const float __alpha, const float *__A, const int __lda, float *__B,
                 const int __ldb)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_strsm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_DIAG __Diag, const int __M, const int __N,
                 const float __alpha, const float *__A, const int __lda, float *__B,
                 const int __ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_dgemm(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_TRANSPOSE __TransB, const int __M, const int __N,
                 const int __K, const double __alpha, const double *__A,
                 const int __lda, const double *__B, const int __ldb,
                 const double __beta, double *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dsymm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const int __M, const int __N,
                 const double __alpha, const double *__A, const int __lda,
                 const double *__B, const int __ldb, const double __beta, double *__C,
                 const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dsyrk(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                 const double __alpha, const double *__A, const int __lda,
                 const double __beta, double *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dsyr2k(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                  const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                  const double __alpha, const double *__A, const int __lda,
                  const double *__B, const int __ldb, const double __beta, double *__C,
                  const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dtrmm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_DIAG __Diag, const int __M, const int __N,
                 const double __alpha, const double *__A, const int __lda, double *__B,
                 const int __ldb)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_dtrsm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_DIAG __Diag, const int __M, const int __N,
                 const double __alpha, const double *__A, const int __lda, double *__B,
                 const int __ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_cgemm(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_TRANSPOSE __TransB, const int __M, const int __N,
                 const int __K, const void *__alpha, const void *__A, const int __lda,
                 const void *__B, const int __ldb, const void *__beta, void *__C,
                 const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_csymm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, const void *__B,
                 const int __ldb, const void *__beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_csyrk(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                 const void *__alpha, const void *__A, const int __lda,
                 const void *__beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_csyr2k(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                  const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                  const void *__alpha, const void *__A, const int __lda, const void *__B,
                  const int __ldb, const void *__beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ctrmm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_DIAG __Diag, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, void *__B,
                 const int __ldb)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ctrsm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_DIAG __Diag, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, void *__B,
                 const int __ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

void cblas_zgemm(const enum CBLAS_ORDER __Order,
                 const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_TRANSPOSE __TransB, const int __M, const int __N,
                 const int __K, const void *__alpha, const void *__A, const int __lda,
                 const void *__B, const int __ldb, const void *__beta, void *__C,
                 const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zsymm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, const void *__B,
                 const int __ldb, const void *__beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zsyrk(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                 const void *__alpha, const void *__A, const int __lda,
                 const void *__beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zsyr2k(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                  const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                  const void *__alpha, const void *__A, const int __lda, const void *__B,
                  const int __ldb, const void *__beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ztrmm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_DIAG __Diag, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, void *__B,
                 const int __ldb)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_ztrsm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const enum CBLAS_TRANSPOSE __TransA,
                 const enum CBLAS_DIAG __Diag, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, void *__B,
                 const int __ldb)
API_AVAILABLE(macos(10.2), ios(4.0));


/*
 * Routines with prefixes C and Z only
 */
void cblas_chemm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, const void *__B,
                 const int __ldb, const void *__beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_cherk(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                 const float __alpha, const void *__A, const int __lda,
                 const float __beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_cher2k(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                  const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                  const void *__alpha, const void *__A, const int __lda, const void *__B,
                  const int __ldb, const float __beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zhemm(const enum CBLAS_ORDER __Order, const enum CBLAS_SIDE __Side,
                 const enum CBLAS_UPLO __Uplo, const int __M, const int __N,
                 const void *__alpha, const void *__A, const int __lda, const void *__B,
                 const int __ldb, const void *__beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zherk(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                 const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                 const double __alpha, const void *__A, const int __lda,
                 const double __beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));
void cblas_zher2k(const enum CBLAS_ORDER __Order, const enum CBLAS_UPLO __Uplo,
                  const enum CBLAS_TRANSPOSE __Trans, const int __N, const int __K,
                  const void *__alpha, const void *__A, const int __lda, const void *__B,
                  const int __ldb, const double __beta, void *__C, const int __ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

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

extern void appleblas_sgeadd(const enum CBLAS_ORDER __order,
                             const enum CBLAS_TRANSPOSE __transA,
                             const enum CBLAS_TRANSPOSE __transB, const int __m, const int __n,
                             const float __alpha, const float *__A, const int __lda,
                             const float __beta, const float *__B, const int __ldb, float *__C,
                             const int __ldc)
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0), tvos(8.0));

extern void appleblas_dgeadd(const enum CBLAS_ORDER __order,
                             const enum CBLAS_TRANSPOSE __transA,
                             const enum CBLAS_TRANSPOSE __transB, const int __m, const int __n,
                             const double __alpha, const double *__A, const int __lda,
                             const double __beta, const double *__B, const int __ldb, double *__C,
                             const int __ldc)
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0), tvos(8.0));

/* The BLAS standard defines a function, cblas_xerbla( ), and suggests that
 * programs provide their own implementation in order to override default
 * error handling.  This scheme is incompatible with the shared library /
 * framework environment of OS X and iOS.
 *
 * Instead, if you wish to change the default BLAS error handling (which is to
 * print an english error message and exit( )), you need to install your own
 * error handlger by calling SetBLASParamErrorProc.
 *
 * Your error handler should adhere to the BLASParamErrorProc interface; it
 * need to terminate program execution.  If your error handler returns normally,
 * then the BLAS call will return normally following its execution without
 * performing any further processing.                                         */

typedef void (*BLASParamErrorProc)(const char *funcName, const char *paramName,
                                   const int *paramPos,  const int *paramValue);

void SetBLASParamErrorProc(BLASParamErrorProc __ErrorProc)
API_AVAILABLE(macos(10.2), ios(4.0));
  
#endif /* CBLAS_ENUM_ONLY */
  
#ifdef __cplusplus
}
#endif

#endif /* CBLAS_H */
