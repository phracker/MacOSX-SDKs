
#pragma once

#if __has_include(<os/availability.h>)
# include <os/availability.h>
#else // __has_include(<os/availability.h>)
# undef API_AVAILABLE
# define API_AVAILABLE(...) /* Nothing */
# undef API_DEPRECATED
# define API_DEPRECATED(...) /* Nothing */
#endif // __has_include(<os/availability.h>)

#ifdef __cplusplus
extern "C" {
#endif


int xerbla_(char *srname, int *info)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

/*
 * =====================================
 * Prototypes for level 1 BLAS functions
 * =====================================
 */

int isamax_(int *n, float *sx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int idamax_(int *n, double *dx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int icamax_(int *n, void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int izamax_(int *n, void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double sasum_(int *n, float *sx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double dasum_(int *n, double *dx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double scasum_(int *n, void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double dzasum_(int *n, void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int saxpy_(int *n, float *da,
           float *sx, int *incx,
           float *sy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int daxpy_(int *n, double *da,
           double *dx, int *incx,
           double *dy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int caxpy_(int *n, void *ca,
           void *cx, int *incx,
           void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zaxpy_(int *n, void *ca,
           void *cx, int *incx,
           void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int scopy_(int *n,
           float *sx, int *incx,
           float *sy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dcopy_(int *n,
           double *dx, int *incx,
           double *dy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ccopy_(int *n,
           void *cx, int *incx,
           void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zcopy_(int *n,
           void *cx, int *incx,
           void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double sdot_(int *n,
                 float *sx, int *incx,
                 float *sy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double ddot_(int *n,
                 double *dx, int *incx,
                 double *dy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double sdsdot_(int *n, float *sb,
                   float *sx, int *incx,
                   float *sy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double dsdot_(int *n,
                  float *sx, int *incx,
                  float *sy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

void cdotc_(void * ret_val, int *n,
            void *cx, int *incx,
            void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

void zdotc_(void * ret_val, int *n,
            void *cx, int *incx,
            void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

void cdotu_(void * ret_val, int *n,
            void *cx, int *incx,
            void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

void zdotu_(void * ret_val, int *n,
            void *cx, int *incx,
            void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double snrm2_(int *n, float *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double dnrm2_(int *n, double *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double scnrm2_(int *n, void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

double dznrm2_(int *n, void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int srot_(int *n,
          float *sx, int *incx,
          float *sy, int *incy,
          float *c, float *s)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int drot_(int *n,
          double *dx, int *incx,
          double *dy, int *incy,
          double *c, double *s)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int csrot_(int *n,
           void *cx, int *incx,
           void *cy, int *incy,
           float *c, float *s)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zdrot_(int *n,
           void *cx, int *incx,
           void *cy, int *incy,
           double *c, double *s)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int srotg_(float *sa, float *sb,
           float *c, float *s)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int drotg_(double *da, double *db,
           double *c, double *s)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int crotg_(void *ca, void *cb, float *c, void *cs)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zrotg_(void *ca, void *cb,
           double *c, void *cs)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int srotm_(int *n,
           float *sx, int *incx,
           float *sy, int *incy,
           float *param)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int drotm_(int *n,
           double *dx, int *incx,
           double *dy, int *incy,
           double *dparam)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int srotmg_(float *sd1, float *sd2,
            float *sx1, float *sy1,
            float *param)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int drotmg_(double *dd1, double *dd2,
            double *dx1, double *dy1,
            double *dparam)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int sscal_(int *n, float *sa,
           float *sx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dscal_(int *n, double *da,
           double *dx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cscal_(int *n, void *ca,
           void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zscal_(int *n, void *ca,
           void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int csscal_(int *n, float *sa,
            void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zdscal_(int *n, double *sa,
            void *cx, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int sswap_(int *n,
           float *sx, int *incx,
           float *sy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dswap_(int *n,
           double *dx, int *incx,
           double *dy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cswap_(int *n,
           void *cx, int *incx,
           void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zswap_(int *n,
           void *cx, int *incx,
           void *cy, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

/*
 * =====================================
 * Prototypes for level 2 BLAS functions
 * =====================================
 */

int sgemv_(char *trans, int *m, int *n, float *alpha,
           float *a, int *lda, float *x, int *incx, float *beta, float *y,
           int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dgemv_(char *trans, int *m, int *n, double *alpha,
           double *a, int *lda, double *x, int *incx, double *beta, double *y,
           int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cgemv_(char *trans, int *m, int *n, void *alpha, void *a,
           int *lda, void *x, int *incx, void *beta, void *y,
           int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zgemv_(char *trans, int *m, int *n, void *alpha, void *a,
           int *lda, void *x, int *incx, void *beta, void *y,
           int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int sgbmv_(char *trans, int *m, int *n, int *kl,
           int *ku, float *alpha, float *a, int *lda, float *x, int *
           incx, float *beta, float *y, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dgbmv_(char *trans, int *m, int *n, int *kl,
           int *ku, double *alpha, double *a, int *lda, double *x, int *
           incx, double *beta, double *y, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cgbmv_(char *trans, int *m, int *n, int *kl,
           int *ku, void *alpha, void *a, int *lda, void *x,
           int *incx, void *beta, void *y, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zgbmv_(char *trans, int *m, int *n, int *kl,
           int *ku, void *alpha, void *a, int *lda, void *x,
           int *incx, void *beta, void *y, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ssymv_(char *uplo, int *n, float *alpha, float *a,
           int *lda, float *x, int *incx, float *beta, float *y, int *
           incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dsymv_(char *uplo, int *n, double *alpha, double *a,
           int *lda, double *x, int *incx, double *beta, double *y, int *
           incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int chemv_(char *uplo, int *n, void *alpha, void *
           a, int *lda, void *x, int *incx, void *beta, void *y,
           int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zhemv_(char *uplo, int *n, void *alpha, void *
           a, int *lda, void *x, int *incx, void *beta, void *y,
           int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ssbmv_(char *uplo, int *n, int *k, float *alpha,
           float *a, int *lda, float *x, int *incx, float *beta, float *y,
           int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dsbmv_(char *uplo, int *n, int *k, double *alpha,
           double *a, int *lda, double *x, int *incx, double *beta, double *y,
           int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int chbmv_(char *uplo, int *n, int *k, void *
           alpha, void *a, int *lda, void *x, int *incx, void *
           beta, void *y, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zhbmv_(char *uplo, int *n, int *k, void *
           alpha, void *a, int *lda, void *x, int *incx, void *
           beta, void *y, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int sspmv_(char *uplo, int *n, float *alpha, float *ap,
           float *x, int *incx, float *beta, float *y, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dspmv_(char *uplo, int *n, double *alpha, double *ap,
           double *x, int *incx, double *beta, double *y, int *incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int chpmv_(char *uplo, int *n, void *alpha, void *
           ap, void *x, int *incx, void *beta, void *y, int *
           incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zhpmv_(char *uplo, int *n, void *alpha, void *
           ap, void *x, int *incx, void *beta, void *y, int *
           incy)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int strmv_(char *uplo, char *trans, char *diag, int *n,
           float *a, int *lda, float *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dtrmv_(char *uplo, char *trans, char *diag, int *n,
           double *a, int *lda, double *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ctrmv_(char *uplo, char *trans, char *diag, int *n,
           void *a, int *lda, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ztrmv_(char *uplo, char *trans, char *diag, int *n,
           void *a, int *lda, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int stbmv_(char *uplo, char *trans, char *diag, int *n,
           int *k, float *a, int *lda, float *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dtbmv_(char *uplo, char *trans, char *diag, int *n,
           int *k, double *a, int *lda, double *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ctbmv_(char *uplo, char *trans, char *diag, int *n,
           int *k, void *a, int *lda, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ztbmv_(char *uplo, char *trans, char *diag, int *n,
           int *k, void *a, int *lda, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int stpmv_(char *uplo, char *trans, char *diag, int *n,
           float *ap, float *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dtpmv_(char *uplo, char *trans, char *diag, int *n,
           double *ap, double *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ctpmv_(char *uplo, char *trans, char *diag, int *n,
           void *ap, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ztpmv_(char *uplo, char *trans, char *diag, int *n,
           void *ap, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int strsv_(char *uplo, char *trans, char *diag, int *n,
           float *a, int *lda, float *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dtrsv_(char *uplo, char *trans, char *diag, int *n,
           double *a, int *lda, double *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ctrsv_(char *uplo, char *trans, char *diag, int *n,
           void *a, int *lda, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ztrsv_(char *uplo, char *trans, char *diag, int *n,
           void *a, int *lda, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int stbsv_(char *uplo, char *trans, char *diag, int *n,
           int *k, float *a, int *lda, float *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dtbsv_(char *uplo, char *trans, char *diag, int *n,
           int *k, double *a, int *lda, double *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ctbsv_(char *uplo, char *trans, char *diag, int *n,
           int *k, void *a, int *lda, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ztbsv_(char *uplo, char *trans, char *diag, int *n,
           int *k, void *a, int *lda, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int stpsv_(char *uplo, char *trans, char *diag, int *n,
           float *ap, float *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dtpsv_(char *uplo, char *trans, char *diag, int *n,
           double *ap, double *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ctpsv_(char *uplo, char *trans, char *diag, int *n,
           void *ap, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ztpsv_(char *uplo, char *trans, char *diag, int *n,
           void *ap, void *x, int *incx)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int sger_(int *m, int *n, float *alpha, float *x,
          int *incx, float *y, int *incy, float *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dger_(int *m, int *n, double *alpha, double *x,
          int *incx, double *y, int *incy, double *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cgerc_(int *m, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zgerc_(int *m, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cgeru_(int *m, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zgeru_(int *m, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ssyr_(char *uplo, int *n, float *alpha, float *x,
          int *incx, float *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dsyr_(char *uplo, int *n, double *alpha, double *x,
          int *incx, double *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cher_(char *uplo, int *n, float *alpha, void *x,
          int *incx, void *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zher_(char *uplo, int *n, double *alpha, void *x,
          int *incx, void *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ssyr2_(char *uplo, int *n, float *alpha, float *x,
           int *incx, float *y, int *incy, float *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dsyr2_(char *uplo, int *n, double *alpha, double *x,
           int *incx, double *y, int *incy, double *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cher2_(char *uplo, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zher2_(char *uplo, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int sspr_(char *uplo, int *n, float *alpha, float *x, int *incx, float *ap)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dspr_(char *uplo, int *n, double *alpha, double *x, int *incx, double *ap)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int chpr_(char *uplo, int *n, float *alpha, void *x,
          int *incx, void *ap)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zhpr_(char *uplo, int *n, double *alpha, void *x,
          int *incx, void *ap)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int sspr2_(char *uplo, int *n, float *alpha, float *x,
           int *incx, float *y, int *incy, float *ap)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dspr2_(char *uplo, int *n, double *alpha, double *x,
           int *incx, double *y, int *incy, double *ap)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int chpr2_(char *uplo, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *ap)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zhpr2_(char *uplo, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *ap)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

/*
 * =====================================
 * Prototypes for level 3 BLAS functions
 * =====================================
 */

int sgemm_(char *transa, char *transb, int *m, int *n, int *k,
           float *alpha, float *a, int *lda, float *b, int *ldb,
           float *beta, float *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dgemm_(char *transa, char *transb, int *m, int *n, int *k,
           double *alpha, double *a, int *lda, double *b,
           int *ldb, double *beta, double *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cgemm_(char *transa, char *transb, int *m, int *n,
           int *k, void *alpha, void *a, int *lda, void *b,
           int *ldb, void *beta, void *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zgemm_(char *transa, char *transb, int *m, int *
           n, int *k, void *alpha, void *a, int *lda,
           void *b, int *ldb, void *beta, void *
           c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ssymm_(char *side, char *uplo, int *m, int *n, float *alpha,
           float *a, int *lda, float *b, int *ldb, float *beta,
           float *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dsymm_(char *side, char *uplo, int *m, int *n,
           double *alpha, double *a, int *lda, double *b,
           int *ldb, double *beta, double *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int csymm_(char *side, char *uplo, int *m, int *n,
           void *alpha, void *a, int *lda, void *b, int *ldb,
           void *beta, void *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zsymm_(char *side, char *uplo, int *m, int *n,
           void *alpha, void *a, int *lda, void *
           b, int *ldb, void *beta, void *c__, int *
           ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int chemm_(char *side, char *uplo, int *m, int *n,
           void *alpha, void *a, int *lda, void *b, int *ldb,
           void *beta, void *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zhemm_(char *side, char *uplo, int *m, int *n,
           void *alpha, void *a, int *lda, void *
           b, int *ldb, void *beta, void *c__, int *
           ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int strmm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, float *alpha, float *a, int *lda,
           float *b, int *ldb)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dtrmm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, double *alpha, double *a, int *
           lda, double *b, int *ldb)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ctrmm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, void *alpha, void *a, int *lda,
           void *b, int *ldb)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ztrmm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, void *alpha, void *a,
           int *lda, void *b, int *ldb)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int strsm_(char *side, char *uplo, char *transa, char *diag, int *m,
           int *n, float *alpha, float *a, int *lda, float *b, int *ldb)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dtrsm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, double *alpha, double *a, int *
           lda, double *b, int *ldb)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ctrsm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, void *alpha, void *a, int *lda,
           void *b, int *ldb)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ztrsm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, void *alpha, void *a,
           int *lda, void *b, int *ldb)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ssyrk_(char *uplo, char *trans, int *n, int *k, float *alpha,
           float *a, int *lda, float *beta, float *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dsyrk_(char *uplo, char *trans, int *n, int *k,
           double *alpha, double *a, int *lda, double *beta,
           double *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int csyrk_(char *uplo, char *trans, int *n, int *k,
           void *alpha, void *a, int *lda, void *beta, void *c__,
           int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zsyrk_(char *uplo, char *trans, int *n, int *k,
           void *alpha, void *a, int *lda, void *
           beta, void *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cherk_(char *uplo, char *trans, int *n, int *k,
           float *alpha, void *a, int *lda, float *beta, void *c__,
           int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zherk_(char *uplo, char *trans, int *n, int *k,
           double *alpha, void *a, int *lda, double *beta,
           void *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int ssyr2k_(char *uplo, char *trans, int *n, int *k, float *alpha,
            float *a, int *lda, float *b, int *ldb, float *beta,
            float *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int dsyr2k_(char *uplo, char *trans, int *n, int *k,
            double *alpha, double *a, int *lda, double *b,
            int *ldb, double *beta, double *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int csyr2k_(char *uplo, char *trans, int *n, int *k,
            void *alpha, void *a, int *lda, void *b, int *ldb,
            void *beta, void *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zsyr2k_(char *uplo, char *trans, int *n, int *k,
            void *alpha, void *a, int *lda, void *
            b, int *ldb, void *beta, void *c__, int *
            ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int cher2k_(char *uplo, char *trans, int *n, int *k,
            void *alpha, void *a, int *lda, void *b, int *ldb,
            float *beta, void *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));

int zher2k_(char *uplo, char *trans, int *n, int *k,
            void *alpha, void *a, int *lda, void *
            b, int *ldb, double *beta, void *c__, int *ldc)
API_DEPRECATED("An updated BLAS interface supporting ILP64 is available.  Please compile with -DACCELERATE_NEW_LAPACK to access the new headers and -DACCELERATE_LAPACK_ILP64 for ILP64 support.", macos(10.2,13.3), ios(4.0,16.4), watchos(1.0,9.4), tvos(4.0,16.4));


#ifdef __cplusplus
}
#endif
