
#pragma once

#if __has_include(<os/availability.h>)
# include <os/availability.h>
#else // __has_include(<os/availability.h>)
# undef API_AVAILABLE
# define API_AVAILABLE(...) /* Nothing */
#endif // __has_include(<os/availability.h>)

#ifdef __cplusplus
extern "C" {
#endif

/*
 * =====================================
 * Prototypes for level 1 BLAS functions
 * =====================================
 */

int isamax_(int *n, float *sx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int idamax_(int *n, double *dx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int icamax_(int *n, void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int izamax_(int *n, void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

double sasum_(int *n, float *sx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

double dasum_(int *n, double *dx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

double scasum_(int *n, void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

double dzasum_(int *n, void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int saxpy_(int *n, float *da,
           float *sx, int *incx,
           float *sy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int daxpy_(int *n, double *da,
           double *dx, int *incx,
           double *dy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int caxpy_(int *n, void *ca,
           void *cx, int *incx,
           void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zaxpy_(int *n, void *ca,
           void *cx, int *incx,
           void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int scopy_(int *n,
           float *sx, int *incx,
           float *sy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dcopy_(int *n,
           double *dx, int *incx,
           double *dy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int ccopy_(int *n,
           void *cx, int *incx,
           void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zcopy_(int *n,
           void *cx, int *incx,
           void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

double sdot_(int *n,
                 float *sx, int *incx,
                 float *sy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

double ddot_(int *n,
                 double *dx, int *incx,
                 double *dy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

double sdsdot_(int *n, float *sb,
                   float *sx, int *incx,
                   float *sy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

double dsdot_(int *n,
                  float *sx, int *incx,
                  float *sy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

void cdotc_(void * ret_val, int *n,
            void *cx, int *incx,
            void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

void zdotc_(void * ret_val, int *n,
            void *cx, int *incx,
            void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

void cdotu_(void * ret_val, int *n,
            void *cx, int *incx,
            void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

void zdotu_(void * ret_val, int *n,
            void *cx, int *incx,
            void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

double snrm2_(int *n, float *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

double dnrm2_(int *n, double *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

double scnrm2_(int *n, void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

double dznrm2_(int *n, void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int srot_(int *n,
          float *sx, int *incx,
          float *sy, int *incy,
          float *c, float *s)
API_AVAILABLE(macos(10.2), ios(4.0));

int drot_(int *n,
          double *dx, int *incx,
          double *dy, int *incy,
          double *c, double *s)
API_AVAILABLE(macos(10.2), ios(4.0));

int csrot_(int *n,
           void *cx, int *incx,
           void *cy, int *incy,
           float *c, float *s)
API_AVAILABLE(macos(10.2), ios(4.0));

int zdrot_(int *n,
           void *cx, int *incx,
           void *cy, int *incy,
           double *c, double *s)
API_AVAILABLE(macos(10.2), ios(4.0));

int srotg_(float *sa, float *sb,
           float *c, float *s)
API_AVAILABLE(macos(10.2), ios(4.0));

int drotg_(double *da, double *db,
           double *c, double *s)
API_AVAILABLE(macos(10.2), ios(4.0));

int crotg_(void *ca, void *cb, float *c, void *cs)
API_AVAILABLE(macos(10.2), ios(4.0));

int zrotg_(void *ca, void *cb,
           double *c, void *cs)
API_AVAILABLE(macos(10.2), ios(4.0));

int srotm_(int *n,
           float *sx, int *incx,
           float *sy, int *incy,
           float *param)
API_AVAILABLE(macos(10.2), ios(4.0));

int drotm_(int *n,
           double *dx, int *incx,
           double *dy, int *incy,
           double *dparam)
API_AVAILABLE(macos(10.2), ios(4.0));

int srotmg_(float *sd1, float *sd2,
            float *sx1, float *sy1,
            float *param)
API_AVAILABLE(macos(10.2), ios(4.0));

int drotmg_(double *dd1, double *dd2,
            double *dx1, double *dy1,
            double *dparam)
API_AVAILABLE(macos(10.2), ios(4.0));

int sscal_(int *n, float *sa,
           float *sx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dscal_(int *n, double *da,
           double *dx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int cscal_(int *n, void *ca,
           void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int zscal_(int *n, void *ca,
           void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int csscal_(int *n, float *sa,
            void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int zdscal_(int *n, double *sa,
            void *cx, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int sswap_(int *n,
           float *sx, int *incx,
           float *sy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dswap_(int *n,
           double *dx, int *incx,
           double *dy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int cswap_(int *n,
           void *cx, int *incx,
           void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zswap_(int *n,
           void *cx, int *incx,
           void *cy, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

/*
 * =====================================
 * Prototypes for level 2 BLAS functions
 * =====================================
 */

int sgemv_(char *trans, int *m, int *n, float *alpha,
           float *a, int *lda, float *x, int *incx, float *beta, float *y,
           int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgemv_(char *trans, int *m, int *n, double *alpha,
           double *a, int *lda, double *x, int *incx, double *beta, double *y,
           int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgemv_(char *trans, int *m, int *n, void *alpha, void *a,
           int *lda, void *x, int *incx, void *beta, void *y,
           int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgemv_(char *trans, int *m, int *n, void *alpha, void *a,
           int *lda, void *x, int *incx, void *beta, void *y,
           int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbmv_(char *trans, int *m, int *n, int *kl,
           int *ku, float *alpha, float *a, int *lda, float *x, int *
           incx, float *beta, float *y, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbmv_(char *trans, int *m, int *n, int *kl,
           int *ku, double *alpha, double *a, int *lda, double *x, int *
           incx, double *beta, double *y, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbmv_(char *trans, int *m, int *n, int *kl,
           int *ku, void *alpha, void *a, int *lda, void *x,
           int *incx, void *beta, void *y, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbmv_(char *trans, int *m, int *n, int *kl,
           int *ku, void *alpha, void *a, int *lda, void *x,
           int *incx, void *beta, void *y, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssymv_(char *uplo, int *n, float *alpha, float *a,
           int *lda, float *x, int *incx, float *beta, float *y, int *
           incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsymv_(char *uplo, int *n, double *alpha, double *a,
           int *lda, double *x, int *incx, double *beta, double *y, int *
           incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int chemv_(char *uplo, int *n, void *alpha, void *
           a, int *lda, void *x, int *incx, void *beta, void *y,
           int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhemv_(char *uplo, int *n, void *alpha, void *
           a, int *lda, void *x, int *incx, void *beta, void *y,
           int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbmv_(char *uplo, int *n, int *k, float *alpha,
           float *a, int *lda, float *x, int *incx, float *beta, float *y,
           int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbmv_(char *uplo, int *n, int *k, double *alpha,
           double *a, int *lda, double *x, int *incx, double *beta, double *y,
           int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbmv_(char *uplo, int *n, int *k, void *
           alpha, void *a, int *lda, void *x, int *incx, void *
           beta, void *y, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbmv_(char *uplo, int *n, int *k, void *
           alpha, void *a, int *lda, void *x, int *incx, void *
           beta, void *y, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspmv_(char *uplo, int *n, float *alpha, float *ap,
           float *x, int *incx, float *beta, float *y, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspmv_(char *uplo, int *n, double *alpha, double *ap,
           double *x, int *incx, double *beta, double *y, int *incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpmv_(char *uplo, int *n, void *alpha, void *
           ap, void *x, int *incx, void *beta, void *y, int *
           incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpmv_(char *uplo, int *n, void *alpha, void *
           ap, void *x, int *incx, void *beta, void *y, int *
           incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int strmv_(char *uplo, char *trans, char *diag, int *n,
           float *a, int *lda, float *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrmv_(char *uplo, char *trans, char *diag, int *n,
           double *a, int *lda, double *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrmv_(char *uplo, char *trans, char *diag, int *n,
           void *a, int *lda, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrmv_(char *uplo, char *trans, char *diag, int *n,
           void *a, int *lda, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int stbmv_(char *uplo, char *trans, char *diag, int *n,
           int *k, float *a, int *lda, float *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtbmv_(char *uplo, char *trans, char *diag, int *n,
           int *k, double *a, int *lda, double *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctbmv_(char *uplo, char *trans, char *diag, int *n,
           int *k, void *a, int *lda, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztbmv_(char *uplo, char *trans, char *diag, int *n,
           int *k, void *a, int *lda, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int stpmv_(char *uplo, char *trans, char *diag, int *n,
           float *ap, float *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtpmv_(char *uplo, char *trans, char *diag, int *n,
           double *ap, double *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctpmv_(char *uplo, char *trans, char *diag, int *n,
           void *ap, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztpmv_(char *uplo, char *trans, char *diag, int *n,
           void *ap, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int strsv_(char *uplo, char *trans, char *diag, int *n,
           float *a, int *lda, float *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrsv_(char *uplo, char *trans, char *diag, int *n,
           double *a, int *lda, double *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrsv_(char *uplo, char *trans, char *diag, int *n,
           void *a, int *lda, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrsv_(char *uplo, char *trans, char *diag, int *n,
           void *a, int *lda, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int stbsv_(char *uplo, char *trans, char *diag, int *n,
           int *k, float *a, int *lda, float *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtbsv_(char *uplo, char *trans, char *diag, int *n,
           int *k, double *a, int *lda, double *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctbsv_(char *uplo, char *trans, char *diag, int *n,
           int *k, void *a, int *lda, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztbsv_(char *uplo, char *trans, char *diag, int *n,
           int *k, void *a, int *lda, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int stpsv_(char *uplo, char *trans, char *diag, int *n,
           float *ap, float *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtpsv_(char *uplo, char *trans, char *diag, int *n,
           double *ap, double *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctpsv_(char *uplo, char *trans, char *diag, int *n,
           void *ap, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztpsv_(char *uplo, char *trans, char *diag, int *n,
           void *ap, void *x, int *incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int sger_(int *m, int *n, float *alpha, float *x,
          int *incx, float *y, int *incy, float *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int dger_(int *m, int *n, double *alpha, double *x,
          int *incx, double *y, int *incy, double *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgerc_(int *m, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgerc_(int *m, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeru_(int *m, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeru_(int *m, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyr_(char *uplo, int *n, float *alpha, float *x,
          int *incx, float *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyr_(char *uplo, int *n, double *alpha, double *x,
          int *incx, double *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int cher_(char *uplo, int *n, float *alpha, void *x,
          int *incx, void *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int zher_(char *uplo, int *n, double *alpha, void *x,
          int *incx, void *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyr2_(char *uplo, int *n, float *alpha, float *x,
           int *incx, float *y, int *incy, float *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyr2_(char *uplo, int *n, double *alpha, double *x,
           int *incx, double *y, int *incy, double *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int cher2_(char *uplo, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int zher2_(char *uplo, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *a, int *lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspr_(char *uplo, int *n, float *alpha, float *x, int *incx, float *ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspr_(char *uplo, int *n, double *alpha, double *x, int *incx, double *ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpr_(char *uplo, int *n, float *alpha, void *x,
          int *incx, void *ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpr_(char *uplo, int *n, double *alpha, void *x,
          int *incx, void *ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspr2_(char *uplo, int *n, float *alpha, float *x,
           int *incx, float *y, int *incy, float *ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspr2_(char *uplo, int *n, double *alpha, double *x,
           int *incx, double *y, int *incy, double *ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpr2_(char *uplo, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpr2_(char *uplo, int *n, void *alpha, void *
           x, int *incx, void *y, int *incy, void *ap)
API_AVAILABLE(macos(10.2), ios(4.0));

/*
 * =====================================
 * Prototypes for level 3 BLAS functions
 * =====================================
 */

int sgemm_(char *transa, char *transb, int *m, int *n, int *k,
           float *alpha, float *a, int *lda, float *b, int *ldb,
           float *beta, float *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgemm_(char *transa, char *transb, int *m, int *n, int *k,
           double *alpha, double *a, int *lda, double *b,
           int *ldb, double *beta, double *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgemm_(char *transa, char *transb, int *m, int *n,
           int *k, void *alpha, void *a, int *lda, void *b,
           int *ldb, void *beta, void *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgemm_(char *transa, char *transb, int *m, int *
           n, int *k, void *alpha, void *a, int *lda,
           void *b, int *ldb, void *beta, void *
           c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssymm_(char *side, char *uplo, int *m, int *n, float *alpha,
           float *a, int *lda, float *b, int *ldb, float *beta,
           float *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsymm_(char *side, char *uplo, int *m, int *n,
           double *alpha, double *a, int *lda, double *b,
           int *ldb, double *beta, double *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int csymm_(char *side, char *uplo, int *m, int *n,
           void *alpha, void *a, int *lda, void *b, int *ldb,
           void *beta, void *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsymm_(char *side, char *uplo, int *m, int *n,
           void *alpha, void *a, int *lda, void *
           b, int *ldb, void *beta, void *c__, int *
           ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int chemm_(char *side, char *uplo, int *m, int *n,
           void *alpha, void *a, int *lda, void *b, int *ldb,
           void *beta, void *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhemm_(char *side, char *uplo, int *m, int *n,
           void *alpha, void *a, int *lda, void *
           b, int *ldb, void *beta, void *c__, int *
           ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int strmm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, float *alpha, float *a, int *lda,
           float *b, int *ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrmm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, double *alpha, double *a, int *
           lda, double *b, int *ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrmm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, void *alpha, void *a, int *lda,
           void *b, int *ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrmm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, void *alpha, void *a,
           int *lda, void *b, int *ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int strsm_(char *side, char *uplo, char *transa, char *diag, int *m,
           int *n, float *alpha, float *a, int *lda, float *b, int *ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrsm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, double *alpha, double *a, int *
           lda, double *b, int *ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrsm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, void *alpha, void *a, int *lda,
           void *b, int *ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrsm_(char *side, char *uplo, char *transa, char *diag,
           int *m, int *n, void *alpha, void *a,
           int *lda, void *b, int *ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyrk_(char *uplo, char *trans, int *n, int *k, float *alpha,
           float *a, int *lda, float *beta, float *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyrk_(char *uplo, char *trans, int *n, int *k,
           double *alpha, double *a, int *lda, double *beta,
           double *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int csyrk_(char *uplo, char *trans, int *n, int *k,
           void *alpha, void *a, int *lda, void *beta, void *c__,
           int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsyrk_(char *uplo, char *trans, int *n, int *k,
           void *alpha, void *a, int *lda, void *
           beta, void *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int cherk_(char *uplo, char *trans, int *n, int *k,
           float *alpha, void *a, int *lda, float *beta, void *c__,
           int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zherk_(char *uplo, char *trans, int *n, int *k,
           double *alpha, void *a, int *lda, double *beta,
           void *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyr2k_(char *uplo, char *trans, int *n, int *k, float *alpha,
            float *a, int *lda, float *b, int *ldb, float *beta,
            float *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyr2k_(char *uplo, char *trans, int *n, int *k,
            double *alpha, double *a, int *lda, double *b,
            int *ldb, double *beta, double *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int csyr2k_(char *uplo, char *trans, int *n, int *k,
            void *alpha, void *a, int *lda, void *b, int *ldb,
            void *beta, void *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsyr2k_(char *uplo, char *trans, int *n, int *k,
            void *alpha, void *a, int *lda, void *
            b, int *ldb, void *beta, void *c__, int *
            ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int cher2k_(char *uplo, char *trans, int *n, int *k,
            void *alpha, void *a, int *lda, void *b, int *ldb,
            float *beta, void *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zher2k_(char *uplo, char *trans, int *n, int *k,
            void *alpha, void *a, int *lda, void *
            b, int *ldb, double *beta, void *c__, int *ldc)
API_AVAILABLE(macos(10.2), ios(4.0));


#ifdef __cplusplus
}
#endif
