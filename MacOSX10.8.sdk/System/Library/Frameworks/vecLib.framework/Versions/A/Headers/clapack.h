/*
 =================================================================================================
 Definitions and prototypes for LAPACK v3.2.1 as provided Apple Computer.
 
 Documentation of the LAPACK interfaces, including reference implementations, can be found on
 the web starting from the LAPACK FAQ page at this URL (verified live as of January 2010):
 http://netlib.org/lapack/faq.html
 
 A hardcopy maanual is:
 LAPACK Users' Guide, Third Edition. 
 @BOOK{laug,
 AUTHOR = {Anderson, E. and Bai, Z. and Bischof, C. and
 Blackford, S. and Demmel, J. and Dongarra, J. and
 Du Croz, J. and Greenbaum, A. and Hammarling, S. and
 McKenney, A. and Sorensen, D.},
 TITLE = {{LAPACK} Users' Guide},
 EDITION = {Third},
 PUBLISHER = {Society for Industrial and Applied Mathematics},
 YEAR = {1999},
 ADDRESS = {Philadelphia, PA},
 ISBN = {0-89871-447-8 (paperback)} }
 
 =================================================================================================
 */

#ifndef __CLAPACK_H
#define __CLAPACK_H

#ifdef __cplusplus
extern "C" {
#endif
    
#if defined(__LP64__) /* In LP64 match sizes with the 32 bit ABI */
    typedef int 		__CLPK_integer;
    typedef int 		__CLPK_logical;
    typedef float 		__CLPK_real;
    typedef double 		__CLPK_doublereal;
    typedef __CLPK_logical 	(*__CLPK_L_fp)();
    typedef int 		__CLPK_ftnlen;
#else
    typedef long int 	__CLPK_integer;
    typedef long int 	__CLPK_logical;
    typedef float 		__CLPK_real;
    typedef double 		__CLPK_doublereal;
    typedef __CLPK_logical 	(*__CLPK_L_fp)();
    typedef long int 	__CLPK_ftnlen;
#endif

typedef struct { __CLPK_real r, i; } __CLPK_complex;
typedef struct { __CLPK_doublereal r, i; } __CLPK_doublecomplex;

#include <Availability.h>
 
int cbdsqr_(char *uplo, __CLPK_integer *n, __CLPK_integer *ncvt, __CLPK_integer *
	nru, __CLPK_integer *ncc, __CLPK_real *d__, __CLPK_real *e, __CLPK_complex *vt, __CLPK_integer *ldvt, 
	__CLPK_complex *u, __CLPK_integer *ldu, __CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbbrd_(char *vect, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *ncc, 
	 __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_complex *q, __CLPK_integer *ldq, __CLPK_complex *pt, __CLPK_integer *ldpt, 
	__CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbcon_(char *norm, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_real *anorm, __CLPK_real *rcond, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbequ_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real 
	*colcnd, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbequb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, 
	__CLPK_real *colcnd, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbrfs_(char *trans, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_integer *nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *afb, __CLPK_integer *
	ldafb, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *
	ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbsv_(__CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_integer *
	nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *
	ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbsvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *kl, 
	 __CLPK_integer *ku, __CLPK_integer *nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *afb, 
	 __CLPK_integer *ldafb, __CLPK_integer *ipiv, char *equed, __CLPK_real *r__, __CLPK_real *c__, 
	__CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real 
	*ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbtf2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbtrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgbtrs_(char *trans, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_integer *nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_complex 
	*b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgebak_(char *job, char *side, __CLPK_integer *n, __CLPK_integer *ilo, 
	__CLPK_integer *ihi, __CLPK_real *scale, __CLPK_integer *m, __CLPK_complex *v, __CLPK_integer *ldv, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgebal_(char *job, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *scale, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgebd2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *d__, __CLPK_real *e, __CLPK_complex *tauq, __CLPK_complex *taup, __CLPK_complex *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgebrd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *d__, __CLPK_real *e, __CLPK_complex *tauq, __CLPK_complex *taup, __CLPK_complex *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgecon_(char *norm, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeequ_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real *colcnd, __CLPK_real *amax, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeequb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real *colcnd, __CLPK_real *amax, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgees_(char *jobvs, char *sort, __CLPK_L_fp select, __CLPK_integer *n, 
	__CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *sdim, __CLPK_complex *w, __CLPK_complex *vs, 
	__CLPK_integer *ldvs, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_logical *
	bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeesx_(char *jobvs, char *sort, __CLPK_L_fp select, char *
	sense, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *sdim, __CLPK_complex *
	w, __CLPK_complex *vs, __CLPK_integer *ldvs, __CLPK_real *rconde, __CLPK_real *rcondv, __CLPK_complex *
	work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeev_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *w, __CLPK_complex *vl, __CLPK_integer *ldvl, __CLPK_complex *vr, 
	__CLPK_integer *ldvr, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *w, __CLPK_complex *vl, 
	__CLPK_integer *ldvl, __CLPK_complex *vr, __CLPK_integer *ldvr, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	 __CLPK_real *scale, __CLPK_real *abnrm, __CLPK_real *rconde, __CLPK_real *rcondv, __CLPK_complex *work, 
	__CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgegs_(char *jobvsl, char *jobvsr, __CLPK_integer *n, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *alpha, __CLPK_complex *
	beta, __CLPK_complex *vsl, __CLPK_integer *ldvsl, __CLPK_complex *vsr, __CLPK_integer *ldvsr, 
	__CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgegv_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *alpha, __CLPK_complex *beta, 
	 __CLPK_complex *vl, __CLPK_integer *ldvl, __CLPK_complex *vr, __CLPK_integer *ldvr, __CLPK_complex *
	work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgehd2_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgehrd_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer 
	*info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgelq2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgelqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgels_(char *trans, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgelsd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_real *s, __CLPK_real *rcond, 
	__CLPK_integer *rank, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgelss_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_real *s, __CLPK_real *rcond, 
	__CLPK_integer *rank, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgelsx_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *jpvt, __CLPK_real *rcond, 
	 __CLPK_integer *rank, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgelsy_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *jpvt, __CLPK_real *rcond, 
	 __CLPK_integer *rank, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeql2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeqlf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeqp3_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *jpvt, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *
	rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeqpf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *jpvt, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeqr2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgeqrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgerfs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *af, __CLPK_integer *ldaf, __CLPK_integer *ipiv, __CLPK_complex *
	b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgerq2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgerqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgesc2_(__CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *
	rhs, __CLPK_integer *ipiv, __CLPK_integer *jpiv, __CLPK_real *scale) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgesdd_(char *jobz, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_real *s, __CLPK_complex *u, __CLPK_integer *ldu, __CLPK_complex *vt, __CLPK_integer 
	*ldvt, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgesv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgesvd_(char *jobu, char *jobvt, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *s, __CLPK_complex *u, __CLPK_integer *ldu, __CLPK_complex *
	vt, __CLPK_integer *ldvt, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgesvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *af, __CLPK_integer *ldaf, __CLPK_integer *
	ipiv, char *equed, __CLPK_real *r__, __CLPK_real *c__, __CLPK_complex *b, __CLPK_integer *ldb, 
	__CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgetc2_(__CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *
	ipiv, __CLPK_integer *jpiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgetf2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgetrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgetri_(__CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *
	ipiv, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgetrs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggbak_(char *job, char *side, __CLPK_integer *n, __CLPK_integer *ilo, 
	__CLPK_integer *ihi, __CLPK_real *lscale, __CLPK_real *rscale, __CLPK_integer *m, __CLPK_complex *v, 
	__CLPK_integer *ldv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggbal_(char *job, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	__CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *lscale, 
	__CLPK_real *rscale, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgges_(char *jobvsl, char *jobvsr, char *sort, __CLPK_L_fp 
	selctg, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *
	ldb, __CLPK_integer *sdim, __CLPK_complex *alpha, __CLPK_complex *beta, __CLPK_complex *vsl, 
	__CLPK_integer *ldvsl, __CLPK_complex *vsr, __CLPK_integer *ldvsr, __CLPK_complex *work, __CLPK_integer *
	lwork, __CLPK_real *rwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggesx_(char *jobvsl, char *jobvsr, char *sort, __CLPK_L_fp 
	selctg, char *sense, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, 
	 __CLPK_integer *ldb, __CLPK_integer *sdim, __CLPK_complex *alpha, __CLPK_complex *beta, __CLPK_complex *
	vsl, __CLPK_integer *ldvsl, __CLPK_complex *vsr, __CLPK_integer *ldvsr, __CLPK_real *rconde, __CLPK_real 
	*rcondv, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggev_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *alpha, __CLPK_complex *beta, 
	 __CLPK_complex *vl, __CLPK_integer *ldvl, __CLPK_complex *vr, __CLPK_integer *ldvr, __CLPK_complex *
	work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, 
	 __CLPK_complex *alpha, __CLPK_complex *beta, __CLPK_complex *vl, __CLPK_integer *ldvl, __CLPK_complex *
	vr, __CLPK_integer *ldvr, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *lscale, __CLPK_real *
	rscale, __CLPK_real *abnrm, __CLPK_real *bbnrm, __CLPK_real *rconde, __CLPK_real *rcondv, __CLPK_complex 
	*work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *iwork, __CLPK_logical *bwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggglm_(__CLPK_integer *n, __CLPK_integer *m, __CLPK_integer *p, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *d__, __CLPK_complex *x, 
	__CLPK_complex *y, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgghrd_(char *compq, char *compz, __CLPK_integer *n, __CLPK_integer *
	ilo, __CLPK_integer *ihi, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, 
	 __CLPK_complex *q, __CLPK_integer *ldq, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgglse_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *p, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *c__, __CLPK_complex *d__, 
	__CLPK_complex *x, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggqrf_(__CLPK_integer *n, __CLPK_integer *m, __CLPK_integer *p, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *taua, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *taub, 
	__CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggrqf_(__CLPK_integer *m, __CLPK_integer *p, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *taua, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *taub, 
	__CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggsvd_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_integer *p, __CLPK_integer *k, __CLPK_integer *l, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_real *alpha, __CLPK_real *beta, __CLPK_complex *u, 
	__CLPK_integer *ldu, __CLPK_complex *v, __CLPK_integer *ldv, __CLPK_complex *q, __CLPK_integer *ldq, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cggsvp_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *p, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer 
	*ldb, __CLPK_real *tola, __CLPK_real *tolb, __CLPK_integer *k, __CLPK_integer *l, __CLPK_complex *u, 
	__CLPK_integer *ldu, __CLPK_complex *v, __CLPK_integer *ldv, __CLPK_complex *q, __CLPK_integer *ldq, 
	__CLPK_integer *iwork, __CLPK_real *rwork, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgtcon_(char *norm, __CLPK_integer *n, __CLPK_complex *dl, __CLPK_complex *
	d__, __CLPK_complex *du, __CLPK_complex *du2, __CLPK_integer *ipiv, __CLPK_real *anorm, __CLPK_real *
	rcond, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgtrfs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	dl, __CLPK_complex *d__, __CLPK_complex *du, __CLPK_complex *dlf, __CLPK_complex *df, __CLPK_complex *
	duf, __CLPK_complex *du2, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *
	x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgtsv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *dl, __CLPK_complex *
	d__, __CLPK_complex *du, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgtsvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *dl, __CLPK_complex *d__, __CLPK_complex *du, __CLPK_complex *dlf, __CLPK_complex *
	df, __CLPK_complex *duf, __CLPK_complex *du2, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *
	ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgttrf_(__CLPK_integer *n, __CLPK_complex *dl, __CLPK_complex *d__, __CLPK_complex *
	du, __CLPK_complex *du2, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgttrs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	dl, __CLPK_complex *d__, __CLPK_complex *du, __CLPK_complex *du2, __CLPK_integer *ipiv, __CLPK_complex *
	b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cgtts2_(__CLPK_integer *itrans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_complex *dl, __CLPK_complex *d__, __CLPK_complex *du, __CLPK_complex *du2, __CLPK_integer *ipiv, 
	__CLPK_complex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chbev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chbevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, 
	__CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *lrwork, __CLPK_integer *
	iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chbevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *q, __CLPK_integer *ldq, 
	__CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, __CLPK_integer *
	m, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chbgst_(char *vect, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *bb, __CLPK_integer *ldbb, 
	__CLPK_complex *x, __CLPK_integer *ldx, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chbgv_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *bb, __CLPK_integer *ldbb, 
	__CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chbgvd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *bb, __CLPK_integer *ldbb, 
	__CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_integer *lwork, 
	__CLPK_real *rwork, __CLPK_integer *lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chbgvx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_integer *ka, __CLPK_integer *kb, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *bb, 
	__CLPK_integer *ldbb, __CLPK_complex *q, __CLPK_integer *ldq, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *
	il, __CLPK_integer *iu, __CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_complex *z__, 
	__CLPK_integer *ldz, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *iwork, __CLPK_integer *
	ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chbtrd_(char *vect, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *d__, __CLPK_real *e, __CLPK_complex *q, __CLPK_integer *
	ldq, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int checon_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cheequb_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cheev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_real *w, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cheevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_real *w, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, 
	__CLPK_integer *lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cheevr_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *
	iu, __CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, 
	__CLPK_integer *isuppz, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *
	lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cheevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *
	iu, __CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, 
	__CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *iwork, __CLPK_integer *
	ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chegs2_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chegst_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chegv_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_real *w, 
	__CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chegvd_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_real *w, 
	__CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *lrwork, __CLPK_integer *
	iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chegvx_(__CLPK_integer *itype, char *jobz, char *range, char *
	uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, 
	__CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, __CLPK_integer *
	m, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_integer *lwork, 
	 __CLPK_real *rwork, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cherfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *af, __CLPK_integer *ldaf, __CLPK_integer *ipiv, __CLPK_complex *
	b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chesv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *a, 
	 __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *work, 
	 __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chesvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *af, __CLPK_integer *ldaf, __CLPK_integer *
	ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *rcond, 
	 __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chetd2_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *d__, __CLPK_real *e, __CLPK_complex *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chetf2_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chetrd_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *d__, __CLPK_real *e, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chetrf_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chetri_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chetrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chfrk_(char *transr, char *uplo, char *trans, __CLPK_integer *n, 
	 __CLPK_integer *k, __CLPK_real *alpha, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *beta, 
	__CLPK_complex *c__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chgeqz_(char *job, char *compq, char *compz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_complex *t, 
	__CLPK_integer *ldt, __CLPK_complex *alpha, __CLPK_complex *beta, __CLPK_complex *q, __CLPK_integer *ldq, 
	 __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *
	rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void chla_transtype__(char *ret_val, __CLPK_ftnlen ret_val_len, 
	__CLPK_integer *trans) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpcon_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_integer *
	ipiv, __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_complex *ap, 
	__CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_complex *ap, 
	__CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_integer *lwork, 
	__CLPK_real *rwork, __CLPK_integer *lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_complex *ap, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *
	abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *
	work, __CLPK_real *rwork, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpgst_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, __CLPK_complex *
	ap, __CLPK_complex *bp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpgv_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_complex *ap, __CLPK_complex *bp, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpgvd_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_complex *ap, __CLPK_complex *bp, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, 
	__CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, __CLPK_integer *lrwork, __CLPK_integer *
	iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpgvx_(__CLPK_integer *itype, char *jobz, char *range, char *
	uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_complex *bp, __CLPK_real *vl, __CLPK_real *vu, 
	__CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_complex *
	z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *iwork, 
	__CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_complex *afp, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, 
	 __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chpsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *ap, __CLPK_complex *afp, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *
	ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chptrd_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_complex *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chptrf_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_integer *
	ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chptri_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_integer *
	ipiv, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chsein_(char *side, char *eigsrc, char *initv, __CLPK_logical *
	select, __CLPK_integer *n, __CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_complex *w, __CLPK_complex *
	vl, __CLPK_integer *ldvl, __CLPK_complex *vr, __CLPK_integer *ldvr, __CLPK_integer *mm, __CLPK_integer *
	m, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *ifaill, __CLPK_integer *ifailr, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int chseqr_(char *job, char *compz, __CLPK_integer *n, __CLPK_integer *ilo, 
	 __CLPK_integer *ihi, __CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_complex *w, __CLPK_complex *z__, 
	__CLPK_integer *ldz, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clabrd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_real *d__, __CLPK_real *e, __CLPK_complex *tauq, __CLPK_complex *taup, 
	__CLPK_complex *x, __CLPK_integer *ldx, __CLPK_complex *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clacgv_(__CLPK_integer *n, __CLPK_complex *x, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clacn2_(__CLPK_integer *n, __CLPK_complex *v, __CLPK_complex *x, __CLPK_real *est, 
	__CLPK_integer *kase, __CLPK_integer *isave) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clacon_(__CLPK_integer *n, __CLPK_complex *v, __CLPK_complex *x, __CLPK_real *est, 
	__CLPK_integer *kase) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clacp2_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clacpy_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clacrm_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *b, __CLPK_integer *ldb, __CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_real *rwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clacrt_(__CLPK_integer *n, __CLPK_complex *cx, __CLPK_integer *incx, __CLPK_complex *
	cy, __CLPK_integer *incy, __CLPK_complex *c__, __CLPK_complex *s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cladiv_(__CLPK_complex * ret_val, __CLPK_complex *x, __CLPK_complex *y) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claed0_(__CLPK_integer *qsiz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_complex *q, __CLPK_integer *ldq, __CLPK_complex *qstore, __CLPK_integer *ldqs, __CLPK_real *rwork, 
	 __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claed7_(__CLPK_integer *n, __CLPK_integer *cutpnt, __CLPK_integer *qsiz, 
	__CLPK_integer *tlvls, __CLPK_integer *curlvl, __CLPK_integer *curpbm, __CLPK_real *d__, __CLPK_complex *
	q, __CLPK_integer *ldq, __CLPK_real *rho, __CLPK_integer *indxq, __CLPK_real *qstore, __CLPK_integer *
	qptr, __CLPK_integer *prmptr, __CLPK_integer *perm, __CLPK_integer *givptr, __CLPK_integer *
	givcol, __CLPK_real *givnum, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claed8_(__CLPK_integer *k, __CLPK_integer *n, __CLPK_integer *qsiz, __CLPK_complex *
	q, __CLPK_integer *ldq, __CLPK_real *d__, __CLPK_real *rho, __CLPK_integer *cutpnt, __CLPK_real *z__, 
	__CLPK_real *dlamda, __CLPK_complex *q2, __CLPK_integer *ldq2, __CLPK_real *w, __CLPK_integer *indxp, 
	__CLPK_integer *indx, __CLPK_integer *indxq, __CLPK_integer *perm, __CLPK_integer *givptr, 
	__CLPK_integer *givcol, __CLPK_real *givnum, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claein_(__CLPK_logical *rightv, __CLPK_logical *noinit, __CLPK_integer *n, 
	__CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_complex *w, __CLPK_complex *v, __CLPK_complex *b, 
	__CLPK_integer *ldb, __CLPK_real *rwork, __CLPK_real *eps3, __CLPK_real *smlnum, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claesy_(__CLPK_complex *a, __CLPK_complex *b, __CLPK_complex *c__, __CLPK_complex *
	rt1, __CLPK_complex *rt2, __CLPK_complex *evscal, __CLPK_complex *cs1, __CLPK_complex *sn1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claev2_(__CLPK_complex *a, __CLPK_complex *b, __CLPK_complex *c__, __CLPK_real *rt1, 
	__CLPK_real *rt2, __CLPK_real *cs1, __CLPK_complex *sn1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clag2z_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *sa, __CLPK_integer *
	ldsa, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clags2_(__CLPK_logical *upper, __CLPK_real *a1, __CLPK_complex *a2, __CLPK_real *a3, 
	__CLPK_real *b1, __CLPK_complex *b2, __CLPK_real *b3, __CLPK_real *csu, __CLPK_complex *snu, __CLPK_real *csv, 
	__CLPK_complex *snv, __CLPK_real *csq, __CLPK_complex *snq) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clagtm_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *
	alpha, __CLPK_complex *dl, __CLPK_complex *d__, __CLPK_complex *du, __CLPK_complex *x, __CLPK_integer *
	ldx, __CLPK_real *beta, __CLPK_complex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clahef_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_integer *kb, 
	 __CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_complex *w, __CLPK_integer *ldw, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clahqr_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_complex *w, 
	__CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clahr2_(__CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *nb, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *t, __CLPK_integer *ldt, __CLPK_complex *y, 
	__CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clahrd_(__CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *nb, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *t, __CLPK_integer *ldt, __CLPK_complex *y, 
	__CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claic1_(__CLPK_integer *job, __CLPK_integer *j, __CLPK_complex *x, __CLPK_real *sest, 
	 __CLPK_complex *w, __CLPK_complex *gamma, __CLPK_real *sestpr, __CLPK_complex *s, __CLPK_complex *c__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clals0_(__CLPK_integer *icompq, __CLPK_integer *nl, __CLPK_integer *nr, 
	__CLPK_integer *sqre, __CLPK_integer *nrhs, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *bx, 
	__CLPK_integer *ldbx, __CLPK_integer *perm, __CLPK_integer *givptr, __CLPK_integer *givcol, 
	__CLPK_integer *ldgcol, __CLPK_real *givnum, __CLPK_integer *ldgnum, __CLPK_real *poles, __CLPK_real *
	difl, __CLPK_real *difr, __CLPK_real *z__, __CLPK_integer *k, __CLPK_real *c__, __CLPK_real *s, __CLPK_real *
	rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clalsa_(__CLPK_integer *icompq, __CLPK_integer *smlsiz, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *bx, __CLPK_integer *ldbx, 
	__CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *vt, __CLPK_integer *k, __CLPK_real *difl, __CLPK_real *difr, 
	__CLPK_real *z__, __CLPK_real *poles, __CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_integer *
	ldgcol, __CLPK_integer *perm, __CLPK_real *givnum, __CLPK_real *c__, __CLPK_real *s, __CLPK_real *rwork, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clalsd_(char *uplo, __CLPK_integer *smlsiz, __CLPK_integer *n, __CLPK_integer 
	*nrhs, __CLPK_real *d__, __CLPK_real *e, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_real *rcond, 
	__CLPK_integer *rank, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *iwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clangb_(char *norm, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_complex *
	ab, __CLPK_integer *ldab, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clange_(char *norm, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clangt_(char *norm, __CLPK_integer *n, __CLPK_complex *dl, __CLPK_complex *d__, __CLPK_complex 
	*du) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clanhb_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *
	ab, __CLPK_integer *ldab, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clanhe_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clanhf_(char *norm, char *transr, char *uplo, __CLPK_integer *n, __CLPK_complex *
	a, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clanhp_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_real *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clanhs_(char *norm, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clanht_(char *norm, __CLPK_integer *n, __CLPK_real *d__, __CLPK_complex *e) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clansb_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *
	ab, __CLPK_integer *ldab, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clansp_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_real *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clansy_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clantb_(char *norm, char *uplo, char *diag, __CLPK_integer *n, __CLPK_integer *k, 
	 __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clantp_(char *norm, char *uplo, char *diag, __CLPK_integer *n, __CLPK_complex *
	ap, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal clantr_(char *norm, char *uplo, char *diag, __CLPK_integer *m, __CLPK_integer *n, 
	 __CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clapll_(__CLPK_integer *n, __CLPK_complex *x, __CLPK_integer *incx, __CLPK_complex *
	y, __CLPK_integer *incy, __CLPK_real *ssmin) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clapmt_(__CLPK_logical *forwrd, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex 
	*x, __CLPK_integer *ldx, __CLPK_integer *k) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqgb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real 
	*colcnd, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqge_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real *colcnd, __CLPK_real *amax, char *
	equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqhb_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_complex *ab, 
	 __CLPK_integer *ldab, __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqhe_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqhp_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_real *s, 
	__CLPK_real *scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqp2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *offset, __CLPK_complex 
	*a, __CLPK_integer *lda, __CLPK_integer *jpvt, __CLPK_complex *tau, __CLPK_real *vn1, __CLPK_real *vn2, 
	__CLPK_complex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqps_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *offset, __CLPK_integer 
	*nb, __CLPK_integer *kb, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *jpvt, __CLPK_complex *
	tau, __CLPK_real *vn1, __CLPK_real *vn2, __CLPK_complex *auxv, __CLPK_complex *f, __CLPK_integer *ldf) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqr0_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_complex *w, 
	__CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqr1_(__CLPK_integer *n, __CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_complex *
	s1, __CLPK_complex *s2, __CLPK_complex *v) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqr2_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nw, __CLPK_complex *h__, __CLPK_integer *ldh, 
	 __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *
	ns, __CLPK_integer *nd, __CLPK_complex *sh, __CLPK_complex *v, __CLPK_integer *ldv, __CLPK_integer *nh, 
	__CLPK_complex *t, __CLPK_integer *ldt, __CLPK_integer *nv, __CLPK_complex *wv, __CLPK_integer *ldwv, 
	__CLPK_complex *work, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqr3_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nw, __CLPK_complex *h__, __CLPK_integer *ldh, 
	 __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *
	ns, __CLPK_integer *nd, __CLPK_complex *sh, __CLPK_complex *v, __CLPK_integer *ldv, __CLPK_integer *nh, 
	__CLPK_complex *t, __CLPK_integer *ldt, __CLPK_integer *nv, __CLPK_complex *wv, __CLPK_integer *ldwv, 
	__CLPK_complex *work, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqr4_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_complex *w, 
	__CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqr5_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *kacc22, 
	__CLPK_integer *n, __CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nshfts, __CLPK_complex *s, 
	 __CLPK_complex *h__, __CLPK_integer *ldh, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_complex *
	z__, __CLPK_integer *ldz, __CLPK_complex *v, __CLPK_integer *ldv, __CLPK_complex *u, __CLPK_integer *ldu, 
	 __CLPK_integer *nv, __CLPK_complex *wv, __CLPK_integer *ldwv, __CLPK_integer *nh, __CLPK_complex *wh, 
	__CLPK_integer *ldwh) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqsb_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_complex *ab, 
	 __CLPK_integer *ldab, __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqsp_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_real *s, 
	__CLPK_real *scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claqsy_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clar1v_(__CLPK_integer *n, __CLPK_integer *b1, __CLPK_integer *bn, __CLPK_real *
	lambda, __CLPK_real *d__, __CLPK_real *l, __CLPK_real *ld, __CLPK_real *lld, __CLPK_real *pivmin, __CLPK_real *
	gaptol, __CLPK_complex *z__, __CLPK_logical *wantnc, __CLPK_integer *negcnt, __CLPK_real *ztz, 
	__CLPK_real *mingma, __CLPK_integer *r__, __CLPK_integer *isuppz, __CLPK_real *nrminv, __CLPK_real *
	resid, __CLPK_real *rqcorr, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clar2v_(__CLPK_integer *n, __CLPK_complex *x, __CLPK_complex *y, __CLPK_complex *z__, 
	 __CLPK_integer *incx, __CLPK_real *c__, __CLPK_complex *s, __CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarcm_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_real *rwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarf_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *v, 
	__CLPK_integer *incv, __CLPK_complex *tau, __CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_complex *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarfb_(char *side, char *trans, char *direct, char *
	storev, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *v, __CLPK_integer *ldv, 
	__CLPK_complex *t, __CLPK_integer *ldt, __CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_complex *work, 
	__CLPK_integer *ldwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarfg_(__CLPK_integer *n, __CLPK_complex *alpha, __CLPK_complex *x, __CLPK_integer *
	incx, __CLPK_complex *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarfp_(__CLPK_integer *n, __CLPK_complex *alpha, __CLPK_complex *x, __CLPK_integer *
	incx, __CLPK_complex *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarft_(char *direct, char *storev, __CLPK_integer *n, __CLPK_integer *
	k, __CLPK_complex *v, __CLPK_integer *ldv, __CLPK_complex *tau, __CLPK_complex *t, __CLPK_integer *ldt) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarfx_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *v, 
	__CLPK_complex *tau, __CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_complex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clargv_(__CLPK_integer *n, __CLPK_complex *x, __CLPK_integer *incx, __CLPK_complex *
	y, __CLPK_integer *incy, __CLPK_real *c__, __CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarnv_(__CLPK_integer *idist, __CLPK_integer *iseed, __CLPK_integer *n, 
	__CLPK_complex *x) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarrv_(__CLPK_integer *n, __CLPK_real *vl, __CLPK_real *vu, __CLPK_real *d__, __CLPK_real *
	l, __CLPK_real *pivmin, __CLPK_integer *isplit, __CLPK_integer *m, __CLPK_integer *dol, __CLPK_integer *
	dou, __CLPK_real *minrgp, __CLPK_real *rtol1, __CLPK_real *rtol2, __CLPK_real *w, __CLPK_real *werr, 
	__CLPK_real *wgap, __CLPK_integer *iblock, __CLPK_integer *indexw, __CLPK_real *gers, __CLPK_complex *
	z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarscl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *d__, __CLPK_complex *x, 
	__CLPK_integer *ldx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clartg_(__CLPK_complex *f, __CLPK_complex *g, __CLPK_real *cs, __CLPK_complex *sn, 
	__CLPK_complex *r__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clartv_(__CLPK_integer *n, __CLPK_complex *x, __CLPK_integer *incx, __CLPK_complex *
	y, __CLPK_integer *incy, __CLPK_real *c__, __CLPK_complex *s, __CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarz_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *l, 
	__CLPK_complex *v, __CLPK_integer *incv, __CLPK_complex *tau, __CLPK_complex *c__, __CLPK_integer *ldc, 
	__CLPK_complex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarzb_(char *side, char *trans, char *direct, char *
	storev, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *l, __CLPK_complex *v, 
	__CLPK_integer *ldv, __CLPK_complex *t, __CLPK_integer *ldt, __CLPK_complex *c__, __CLPK_integer *ldc, 
	__CLPK_complex *work, __CLPK_integer *ldwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clarzt_(char *direct, char *storev, __CLPK_integer *n, __CLPK_integer *
	k, __CLPK_complex *v, __CLPK_integer *ldv, __CLPK_complex *tau, __CLPK_complex *t, __CLPK_integer *ldt) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clascl_(char *type__, __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_real *
	cfrom, __CLPK_real *cto, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clascl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *d__, __CLPK_complex *x, 
	__CLPK_integer *ldx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claset_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *
	alpha, __CLPK_complex *beta, __CLPK_complex *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clasr_(char *side, char *pivot, char *direct, __CLPK_integer *m, 
	 __CLPK_integer *n, __CLPK_real *c__, __CLPK_real *s, __CLPK_complex *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int classq_(__CLPK_integer *n, __CLPK_complex *x, __CLPK_integer *incx, __CLPK_real *
	scale, __CLPK_real *sumsq) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int claswp_(__CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *
	k1, __CLPK_integer *k2, __CLPK_integer *ipiv, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clasyf_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_integer *kb, 
	 __CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_complex *w, __CLPK_integer *ldw, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clatbs_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *
	x, __CLPK_real *scale, __CLPK_real *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clatdf_(__CLPK_integer *ijob, __CLPK_integer *n, __CLPK_complex *z__, __CLPK_integer 
	*ldz, __CLPK_complex *rhs, __CLPK_real *rdsum, __CLPK_real *rdscal, __CLPK_integer *ipiv, __CLPK_integer 
	*jpiv) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clatps_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_complex *x, __CLPK_real *scale, __CLPK_real *cnorm, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clatrd_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_real *e, __CLPK_complex *tau, __CLPK_complex *w, __CLPK_integer *ldw) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clatrs_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *x, __CLPK_real *scale, 
	 __CLPK_real *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clatrz_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *l, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clatzm_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *v, 
	__CLPK_integer *incv, __CLPK_complex *tau, __CLPK_complex *c1, __CLPK_complex *c2, __CLPK_integer *ldc, 
	__CLPK_complex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clauu2_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int clauum_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbcon_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_complex *ab, 
	 __CLPK_integer *ldab, __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbequ_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_complex *ab, 
	 __CLPK_integer *ldab, __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *afb, __CLPK_integer *ldafb, 
	__CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *
	berr, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbstf_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_complex *ab, 
	 __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_integer *nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *afb, __CLPK_integer *
	ldafb, char *equed, __CLPK_real *s, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, 
	__CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, 
	__CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbtf2_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_complex *ab, 
	 __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbtrf_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_complex *ab, 
	 __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpbtrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpftrf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_complex *a, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpftri_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_complex *a, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpftrs_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *a, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpocon_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpoequ_(__CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *s, 
	__CLPK_real *scond, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpoequb_(__CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *s, 
	__CLPK_real *scond, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cporfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *af, __CLPK_integer *ldaf, __CLPK_complex *b, __CLPK_integer *ldb, 
	 __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, 
	__CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cposv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *a, 
	 __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cposvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *af, __CLPK_integer *ldaf, char *
	equed, __CLPK_real *s, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, 
	__CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpotf2_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpotrf_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpotri_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpotrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cppcon_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_real *anorm, 
	 __CLPK_real *rcond, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cppequ_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_real *s, 
	__CLPK_real *scond, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_complex *afp, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, 
	__CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cppsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cppsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *ap, __CLPK_complex *afp, char *equed, __CLPK_real *s, __CLPK_complex *b, 
	__CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real 
	*berr, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpptrf_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpptri_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpstf2_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *piv, __CLPK_integer *rank, __CLPK_real *tol, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpstrf_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *piv, __CLPK_integer *rank, __CLPK_real *tol, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cptcon_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_complex *e, __CLPK_real *anorm, 
	__CLPK_real *rcond, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpteqr_(char *compz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cptrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, 
	 __CLPK_complex *e, __CLPK_real *df, __CLPK_complex *ef, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex 
	*x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cptsv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, __CLPK_complex *e, 
	__CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cptsvx_(char *fact, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, 
	 __CLPK_complex *e, __CLPK_real *df, __CLPK_complex *ef, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex 
	*x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, 
	__CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpttrf_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_complex *e, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cpttrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, 
	 __CLPK_complex *e, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cptts2_(__CLPK_integer *iuplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *
	d__, __CLPK_complex *e, __CLPK_complex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int crot_(__CLPK_integer *n, __CLPK_complex *cx, __CLPK_integer *incx, __CLPK_complex *
	cy, __CLPK_integer *incy, __CLPK_real *c__, __CLPK_complex *s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cspcon_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_integer *
	ipiv, __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cspmv_(char *uplo, __CLPK_integer *n, __CLPK_complex *alpha, __CLPK_complex *
	ap, __CLPK_complex *x, __CLPK_integer *incx, __CLPK_complex *beta, __CLPK_complex *y, __CLPK_integer *
	incy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cspr_(char *uplo, __CLPK_integer *n, __CLPK_complex *alpha, __CLPK_complex *x, 
	 __CLPK_integer *incx, __CLPK_complex *ap) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_complex *afp, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, 
	 __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cspsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cspsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *ap, __CLPK_complex *afp, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *
	ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csptrf_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_integer *
	ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csptri_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_integer *
	ipiv, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	ap, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csrscl_(__CLPK_integer *n, __CLPK_real *sa, __CLPK_complex *sx, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cstedc_(char *compz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *
	rwork, __CLPK_integer *lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cstegr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, 
	__CLPK_integer *m, __CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, 
	__CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cstein_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_integer *m, __CLPK_real 
	*w, __CLPK_integer *iblock, __CLPK_integer *isplit, __CLPK_complex *z__, __CLPK_integer *ldz, 
	__CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cstemr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_integer *m, 
	__CLPK_real *w, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *nzc, __CLPK_integer *isuppz, 
	__CLPK_logical *tryrac, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *
	liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csteqr_(char *compz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csycon_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csyequb_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csymv_(char *uplo, __CLPK_integer *n, __CLPK_complex *alpha, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *x, __CLPK_integer *incx, __CLPK_complex *beta, __CLPK_complex *y, 
	 __CLPK_integer *incy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csyr_(char *uplo, __CLPK_integer *n, __CLPK_complex *alpha, __CLPK_complex *x, 
	 __CLPK_integer *incx, __CLPK_complex *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csyrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *af, __CLPK_integer *ldaf, __CLPK_integer *ipiv, __CLPK_complex *
	b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csysv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *a, 
	 __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *work, 
	 __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csysvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *af, __CLPK_integer *ldaf, __CLPK_integer *
	ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *rcond, 
	 __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csytf2_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csytrf_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csytri_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_integer *ipiv, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int csytrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctbcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_real *rcond, __CLPK_complex *work, 
	__CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctbrfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_integer *nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *b, 
	__CLPK_integer *ldb, __CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, 
	__CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctbtrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_integer *nrhs, __CLPK_complex *ab, __CLPK_integer *ldab, __CLPK_complex *b, 
	__CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctfsm_(char *transr, char *side, char *uplo, char *trans, 
	 char *diag, __CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *alpha, __CLPK_complex *a, 
	__CLPK_complex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctftri_(char *transr, char *uplo, char *diag, __CLPK_integer *n, 
	 __CLPK_complex *a, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctfttp_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_complex *
	arf, __CLPK_complex *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctfttr_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_complex *
	arf, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctgevc_(char *side, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_complex *s, __CLPK_integer *lds, __CLPK_complex *p, __CLPK_integer *ldp, 
	__CLPK_complex *vl, __CLPK_integer *ldvl, __CLPK_complex *vr, __CLPK_integer *ldvr, __CLPK_integer *mm, 
	__CLPK_integer *m, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctgex2_(__CLPK_logical *wantq, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *q, 
	__CLPK_integer *ldq, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *j1, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctgexc_(__CLPK_logical *wantq, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *q, 
	__CLPK_integer *ldq, __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *ifst, __CLPK_integer *
	ilst, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctgsen_(__CLPK_integer *ijob, __CLPK_logical *wantq, __CLPK_logical *wantz, 
	__CLPK_logical *select, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, 
	__CLPK_integer *ldb, __CLPK_complex *alpha, __CLPK_complex *beta, __CLPK_complex *q, __CLPK_integer *ldq, 
	 __CLPK_complex *z__, __CLPK_integer *ldz, __CLPK_integer *m, __CLPK_real *pl, __CLPK_real *pr, __CLPK_real *
	dif, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctgsja_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *p, __CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *l, __CLPK_complex *a, __CLPK_integer *
	lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_real *tola, __CLPK_real *tolb, __CLPK_real *alpha, 
	__CLPK_real *beta, __CLPK_complex *u, __CLPK_integer *ldu, __CLPK_complex *v, __CLPK_integer *ldv, 
	__CLPK_complex *q, __CLPK_integer *ldq, __CLPK_complex *work, __CLPK_integer *ncycle, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctgsna_(char *job, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, 
	__CLPK_complex *vl, __CLPK_integer *ldvl, __CLPK_complex *vr, __CLPK_integer *ldvr, __CLPK_real *s, __CLPK_real 
	*dif, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer 
	*iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctgsy2_(char *trans, __CLPK_integer *ijob, __CLPK_integer *m, __CLPK_integer *
	n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *d__, __CLPK_integer *ldd, __CLPK_complex *e, __CLPK_integer *lde, 
	__CLPK_complex *f, __CLPK_integer *ldf, __CLPK_real *scale, __CLPK_real *rdsum, __CLPK_real *rdscal, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctgsyl_(char *trans, __CLPK_integer *ijob, __CLPK_integer *m, __CLPK_integer *
	n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *d__, __CLPK_integer *ldd, __CLPK_complex *e, __CLPK_integer *lde, 
	__CLPK_complex *f, __CLPK_integer *ldf, __CLPK_real *scale, __CLPK_real *dif, __CLPK_complex *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctpcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_complex *ap, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctprfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_complex *ap, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_complex *x, 
	__CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctptri_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_complex *ap, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctptrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_complex *ap, __CLPK_complex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctpttf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_complex *
	ap, __CLPK_complex *arf, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctpttr_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_complex *a, __CLPK_integer *lda, __CLPK_real *rcond, __CLPK_complex *work, __CLPK_real *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrevc_(char *side, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_complex *t, __CLPK_integer *ldt, __CLPK_complex *vl, __CLPK_integer *ldvl, 
	__CLPK_complex *vr, __CLPK_integer *ldvr, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_complex *work, 
	__CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrexc_(char *compq, __CLPK_integer *n, __CLPK_complex *t, __CLPK_integer *
	ldt, __CLPK_complex *q, __CLPK_integer *ldq, __CLPK_integer *ifst, __CLPK_integer *ilst, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrrfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, 
	__CLPK_complex *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_complex *work, __CLPK_real 
	*rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrsen_(char *job, char *compq, __CLPK_logical *select, __CLPK_integer 
	*n, __CLPK_complex *t, __CLPK_integer *ldt, __CLPK_complex *q, __CLPK_integer *ldq, __CLPK_complex *w, 
	__CLPK_integer *m, __CLPK_real *s, __CLPK_real *sep, __CLPK_complex *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrsna_(char *job, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_complex *t, __CLPK_integer *ldt, __CLPK_complex *vl, __CLPK_integer *ldvl, 
	__CLPK_complex *vr, __CLPK_integer *ldvr, __CLPK_real *s, __CLPK_real *sep, __CLPK_integer *mm, __CLPK_integer *
	m, __CLPK_complex *work, __CLPK_integer *ldwork, __CLPK_real *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrsyl_(char *trana, char *tranb, __CLPK_integer *isgn, __CLPK_integer 
	*m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, 
	__CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_real *scale, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrti2_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrtri_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrtrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrttf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_complex *a, 
	 __CLPK_integer *lda, __CLPK_complex *arf, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctrttp_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctzrqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ctzrzf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cung2l_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cung2r_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cungbr_(char *vect, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunghr_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_complex *
	a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer 
	*info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cungl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunglq_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cungql_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cungqr_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cungr2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cungrq_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, 
	__CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cungtr_(char *uplo, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, 
	 __CLPK_complex *tau, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunm2l_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunm2r_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmbr_(char *vect, char *side, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, 
	__CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmhr_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, 
	__CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunml2_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmlq_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmql_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmqr_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmr2_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmr3_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_integer *l, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, 
	__CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmrq_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmrz_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_integer *l, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, 
	__CLPK_complex *c__, __CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cunmtr_(char *side, char *uplo, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda, __CLPK_complex *tau, __CLPK_complex *c__, 
	__CLPK_integer *ldc, __CLPK_complex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cupgtr_(char *uplo, __CLPK_integer *n, __CLPK_complex *ap, __CLPK_complex *
	tau, __CLPK_complex *q, __CLPK_integer *ldq, __CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int cupmtr_(char *side, char *uplo, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_complex *ap, __CLPK_complex *tau, __CLPK_complex *c__, __CLPK_integer *ldc, 
	__CLPK_complex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dbdsdc_(char *uplo, char *compq, __CLPK_integer *n, __CLPK_doublereal *
	d__, __CLPK_doublereal *e, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *vt, 
	__CLPK_integer *ldvt, __CLPK_doublereal *q, __CLPK_integer *iq, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dbdsqr_(char *uplo, __CLPK_integer *n, __CLPK_integer *ncvt, __CLPK_integer *
	nru, __CLPK_integer *ncc, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *vt, 
	__CLPK_integer *ldvt, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *c__, __CLPK_integer *
	ldc, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ddisna_(char *job, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *
	d__, __CLPK_doublereal *sep, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbbrd_(char *vect, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *ncc, 
	 __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *
	d__, __CLPK_doublereal *e, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *pt, 
	__CLPK_integer *ldpt, __CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbcon_(char *norm, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_doublereal *anorm, 
	__CLPK_doublereal *rcond, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbequ_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *r__, __CLPK_doublereal *c__, 
	__CLPK_doublereal *rowcnd, __CLPK_doublereal *colcnd, __CLPK_doublereal *amax, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbequb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *r__, __CLPK_doublereal *c__, 
	__CLPK_doublereal *rowcnd, __CLPK_doublereal *colcnd, __CLPK_doublereal *amax, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbrfs_(char *trans, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_integer *nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *afb, 
	__CLPK_integer *ldafb, __CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbsv_(__CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_integer *
	nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbsvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *kl, 
	 __CLPK_integer *ku, __CLPK_integer *nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, 
	__CLPK_doublereal *afb, __CLPK_integer *ldafb, __CLPK_integer *ipiv, char *equed, 
	__CLPK_doublereal *r__, __CLPK_doublereal *c__, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbtf2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbtrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgbtrs_(char *trans, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_integer *nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgebak_(char *job, char *side, __CLPK_integer *n, __CLPK_integer *ilo, 
	__CLPK_integer *ihi, __CLPK_doublereal *scale, __CLPK_integer *m, __CLPK_doublereal *v, __CLPK_integer *
	ldv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgebal_(char *job, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *scale, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgebd2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *tauq, __CLPK_doublereal *
	taup, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgebrd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *tauq, __CLPK_doublereal *
	taup, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgecon_(char *norm, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeequ_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *r__, __CLPK_doublereal *c__, __CLPK_doublereal *rowcnd, __CLPK_doublereal 
	*colcnd, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeequb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *r__, __CLPK_doublereal *c__, __CLPK_doublereal *rowcnd, __CLPK_doublereal 
	*colcnd, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgees_(char *jobvs, char *sort, __CLPK_L_fp select, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *sdim, __CLPK_doublereal *wr, 
	__CLPK_doublereal *wi, __CLPK_doublereal *vs, __CLPK_integer *ldvs, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeesx_(char *jobvs, char *sort, __CLPK_L_fp select, char *
	sense, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *sdim, 
	__CLPK_doublereal *wr, __CLPK_doublereal *wi, __CLPK_doublereal *vs, __CLPK_integer *ldvs, 
	__CLPK_doublereal *rconde, __CLPK_doublereal *rcondv, __CLPK_doublereal *work, __CLPK_integer *
	lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeev_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *wr, __CLPK_doublereal *wi, __CLPK_doublereal *vl, 
	__CLPK_integer *ldvl, __CLPK_doublereal *vr, __CLPK_integer *ldvr, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *wr, 
	__CLPK_doublereal *wi, __CLPK_doublereal *vl, __CLPK_integer *ldvl, __CLPK_doublereal *vr, 
	__CLPK_integer *ldvr, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *scale, 
	__CLPK_doublereal *abnrm, __CLPK_doublereal *rconde, __CLPK_doublereal *rcondv, __CLPK_doublereal 
	*work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgegs_(char *jobvsl, char *jobvsr, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *
	alphar, __CLPK_doublereal *alphai, __CLPK_doublereal *beta, __CLPK_doublereal *vsl, 
	__CLPK_integer *ldvsl, __CLPK_doublereal *vsr, __CLPK_integer *ldvsr, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgegv_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *alphar, 
	__CLPK_doublereal *alphai, __CLPK_doublereal *beta, __CLPK_doublereal *vl, __CLPK_integer *ldvl, 
	__CLPK_doublereal *vr, __CLPK_integer *ldvr, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgehd2_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgehrd_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgejsv_(char *joba, char *jobu, char *jobv, char *jobr, 
	char *jobt, char *jobp, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, 
	__CLPK_integer *lda, __CLPK_doublereal *sva, __CLPK_doublereal *u, __CLPK_integer *ldu, 
	__CLPK_doublereal *v, __CLPK_integer *ldv, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgelq2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgelqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgels_(char *trans, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgelsd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *
	s, __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	 __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgelss_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *
	s, __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgelsx_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *
	jpvt, __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublereal *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgelsy_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *
	jpvt, __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublereal *work, __CLPK_integer *
	lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeql2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeqlf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeqp3_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *jpvt, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeqpf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *jpvt, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeqr2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgeqrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgerfs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *af, __CLPK_integer *ldaf, __CLPK_integer *
	ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgerq2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgerqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgesc2_(__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, 
	__CLPK_doublereal *rhs, __CLPK_integer *ipiv, __CLPK_integer *jpiv, __CLPK_doublereal *scale) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgesdd_(char *jobz, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *s, __CLPK_doublereal *u, __CLPK_integer *ldu, 
	__CLPK_doublereal *vt, __CLPK_integer *ldvt, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgesv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal *a, __CLPK_integer 
	*lda, __CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgesvd_(char *jobu, char *jobvt, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *s, __CLPK_doublereal *u, __CLPK_integer *
	ldu, __CLPK_doublereal *vt, __CLPK_integer *ldvt, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgesvj_(char *joba, char *jobu, char *jobv, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *sva, __CLPK_integer *mv, 
	 __CLPK_doublereal *v, __CLPK_integer *ldv, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgesvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *af, __CLPK_integer *ldaf, 
	__CLPK_integer *ipiv, char *equed, __CLPK_doublereal *r__, __CLPK_doublereal *c__, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *
	rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgetc2_(__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer 
	*ipiv, __CLPK_integer *jpiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgetf2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgetrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgetri_(__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer 
	*ipiv, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgetrs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *
	ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggbak_(char *job, char *side, __CLPK_integer *n, __CLPK_integer *ilo, 
	__CLPK_integer *ihi, __CLPK_doublereal *lscale, __CLPK_doublereal *rscale, __CLPK_integer *m, 
	__CLPK_doublereal *v, __CLPK_integer *ldv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggbal_(char *job, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	__CLPK_doublereal *lscale, __CLPK_doublereal *rscale, __CLPK_doublereal *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgges_(char *jobvsl, char *jobvsr, char *sort, __CLPK_L_fp 
	selctg, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_integer *sdim, __CLPK_doublereal *alphar, __CLPK_doublereal *alphai, 
	__CLPK_doublereal *beta, __CLPK_doublereal *vsl, __CLPK_integer *ldvsl, __CLPK_doublereal *vsr, 
	__CLPK_integer *ldvsr, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_logical *bwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggesx_(char *jobvsl, char *jobvsr, char *sort, __CLPK_L_fp 
	selctg, char *sense, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *sdim, __CLPK_doublereal *alphar, 
	__CLPK_doublereal *alphai, __CLPK_doublereal *beta, __CLPK_doublereal *vsl, __CLPK_integer *ldvsl, 
	 __CLPK_doublereal *vsr, __CLPK_integer *ldvsr, __CLPK_doublereal *rconde, __CLPK_doublereal *
	rcondv, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *
	liwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggev_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *alphar, 
	__CLPK_doublereal *alphai, __CLPK_doublereal *beta, __CLPK_doublereal *vl, __CLPK_integer *ldvl, 
	__CLPK_doublereal *vr, __CLPK_integer *ldvr, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_doublereal *alphar, __CLPK_doublereal *alphai, __CLPK_doublereal *
	beta, __CLPK_doublereal *vl, __CLPK_integer *ldvl, __CLPK_doublereal *vr, __CLPK_integer *ldvr, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *lscale, __CLPK_doublereal *rscale, 
	__CLPK_doublereal *abnrm, __CLPK_doublereal *bbnrm, __CLPK_doublereal *rconde, __CLPK_doublereal *
	rcondv, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_logical *
	bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggglm_(__CLPK_integer *n, __CLPK_integer *m, __CLPK_integer *p, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *d__, 
	__CLPK_doublereal *x, __CLPK_doublereal *y, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgghrd_(char *compq, char *compz, __CLPK_integer *n, __CLPK_integer *
	ilo, __CLPK_integer *ihi, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *z__, __CLPK_integer *
	ldz, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgglse_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *p, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *c__, 
	__CLPK_doublereal *d__, __CLPK_doublereal *x, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggqrf_(__CLPK_integer *n, __CLPK_integer *m, __CLPK_integer *p, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *taua, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *taub, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggrqf_(__CLPK_integer *m, __CLPK_integer *p, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *taua, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *taub, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggsvd_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_integer *p, __CLPK_integer *k, __CLPK_integer *l, __CLPK_doublereal *a, 
	__CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *alpha, 
	__CLPK_doublereal *beta, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *v, __CLPK_integer 
	*ldv, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dggsvp_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *p, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_doublereal *tola, __CLPK_doublereal *tolb, __CLPK_integer *k, __CLPK_integer 
	*l, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *v, __CLPK_integer *ldv, 
	__CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_integer *iwork, __CLPK_doublereal *tau, 
	__CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgsvj0_(char *jobv, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *d__, __CLPK_doublereal *sva, __CLPK_integer *mv, 
	__CLPK_doublereal *v, __CLPK_integer *ldv, __CLPK_doublereal *eps, __CLPK_doublereal *sfmin, 
	__CLPK_doublereal *tol, __CLPK_integer *nsweep, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgsvj1_(char *jobv, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *n1, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *d__, __CLPK_doublereal *sva, 
	__CLPK_integer *mv, __CLPK_doublereal *v, __CLPK_integer *ldv, __CLPK_doublereal *eps, __CLPK_doublereal 
	*sfmin, __CLPK_doublereal *tol, __CLPK_integer *nsweep, __CLPK_doublereal *work, __CLPK_integer *
	lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgtcon_(char *norm, __CLPK_integer *n, __CLPK_doublereal *dl, 
	__CLPK_doublereal *d__, __CLPK_doublereal *du, __CLPK_doublereal *du2, __CLPK_integer *ipiv, 
	__CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgtrfs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *dl, __CLPK_doublereal *d__, __CLPK_doublereal *du, __CLPK_doublereal *dlf, 
	__CLPK_doublereal *df, __CLPK_doublereal *duf, __CLPK_doublereal *du2, __CLPK_integer *ipiv, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *
	ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgtsv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal *dl, 
	__CLPK_doublereal *d__, __CLPK_doublereal *du, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer 
	*info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgtsvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublereal *dl, __CLPK_doublereal *d__, __CLPK_doublereal *du, __CLPK_doublereal *
	dlf, __CLPK_doublereal *df, __CLPK_doublereal *duf, __CLPK_doublereal *du2, __CLPK_integer *ipiv, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *
	rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgttrf_(__CLPK_integer *n, __CLPK_doublereal *dl, __CLPK_doublereal *d__, 
	__CLPK_doublereal *du, __CLPK_doublereal *du2, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgttrs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *dl, __CLPK_doublereal *d__, __CLPK_doublereal *du, __CLPK_doublereal *du2, 
	__CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dgtts2_(__CLPK_integer *itrans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *dl, __CLPK_doublereal *d__, __CLPK_doublereal *du, __CLPK_doublereal *du2, 
	__CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dhgeqz_(char *job, char *compq, char *compz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *h__, __CLPK_integer *ldh, __CLPK_doublereal 
	*t, __CLPK_integer *ldt, __CLPK_doublereal *alphar, __CLPK_doublereal *alphai, __CLPK_doublereal *
	beta, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *z__, __CLPK_integer *ldz, 
	__CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dhsein_(char *side, char *eigsrc, char *initv, __CLPK_logical *
	select, __CLPK_integer *n, __CLPK_doublereal *h__, __CLPK_integer *ldh, __CLPK_doublereal *wr, 
	__CLPK_doublereal *wi, __CLPK_doublereal *vl, __CLPK_integer *ldvl, __CLPK_doublereal *vr, 
	__CLPK_integer *ldvr, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_doublereal *work, __CLPK_integer *
	ifaill, __CLPK_integer *ifailr, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dhseqr_(char *job, char *compz, __CLPK_integer *n, __CLPK_integer *ilo, 
	 __CLPK_integer *ihi, __CLPK_doublereal *h__, __CLPK_integer *ldh, __CLPK_doublereal *wr, 
	__CLPK_doublereal *wi, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_logical disnan_(__CLPK_doublereal *din) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlabad_(__CLPK_doublereal *small, __CLPK_doublereal *large) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlabrd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *tauq, 
	__CLPK_doublereal *taup, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *y, __CLPK_integer 
	*ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlacn2_(__CLPK_integer *n, __CLPK_doublereal *v, __CLPK_doublereal *x, 
	__CLPK_integer *isgn, __CLPK_doublereal *est, __CLPK_integer *kase, __CLPK_integer *isave) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlacon_(__CLPK_integer *n, __CLPK_doublereal *v, __CLPK_doublereal *x, 
	__CLPK_integer *isgn, __CLPK_doublereal *est, __CLPK_integer *kase) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlacpy_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dladiv_(__CLPK_doublereal *a, __CLPK_doublereal *b, __CLPK_doublereal *c__, 
	__CLPK_doublereal *d__, __CLPK_doublereal *p, __CLPK_doublereal *q) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlae2_(__CLPK_doublereal *a, __CLPK_doublereal *b, __CLPK_doublereal *c__, 
	__CLPK_doublereal *rt1, __CLPK_doublereal *rt2) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaebz_(__CLPK_integer *ijob, __CLPK_integer *nitmax, __CLPK_integer *n, 
	__CLPK_integer *mmax, __CLPK_integer *minp, __CLPK_integer *nbmin, __CLPK_doublereal *abstol, 
	__CLPK_doublereal *reltol, __CLPK_doublereal *pivmin, __CLPK_doublereal *d__, __CLPK_doublereal *
	e, __CLPK_doublereal *e2, __CLPK_integer *nval, __CLPK_doublereal *ab, __CLPK_doublereal *c__, 
	__CLPK_integer *mout, __CLPK_integer *nab, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed0_(__CLPK_integer *icompq, __CLPK_integer *qsiz, __CLPK_integer *n, 
	__CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *q, __CLPK_integer *ldq, 
	__CLPK_doublereal *qstore, __CLPK_integer *ldqs, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed1_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *q, 
	__CLPK_integer *ldq, __CLPK_integer *indxq, __CLPK_doublereal *rho, __CLPK_integer *cutpnt, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed2_(__CLPK_integer *k, __CLPK_integer *n, __CLPK_integer *n1, __CLPK_doublereal *
	d__, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_integer *indxq, __CLPK_doublereal *rho, 
	__CLPK_doublereal *z__, __CLPK_doublereal *dlamda, __CLPK_doublereal *w, __CLPK_doublereal *q2, 
	__CLPK_integer *indx, __CLPK_integer *indxc, __CLPK_integer *indxp, __CLPK_integer *coltyp, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed3_(__CLPK_integer *k, __CLPK_integer *n, __CLPK_integer *n1, __CLPK_doublereal *
	d__, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *rho, __CLPK_doublereal *dlamda, 
	 __CLPK_doublereal *q2, __CLPK_integer *indx, __CLPK_integer *ctot, __CLPK_doublereal *w, 
	__CLPK_doublereal *s, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed4_(__CLPK_integer *n, __CLPK_integer *i__, __CLPK_doublereal *d__, 
	__CLPK_doublereal *z__, __CLPK_doublereal *delta, __CLPK_doublereal *rho, __CLPK_doublereal *dlam, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed5_(__CLPK_integer *i__, __CLPK_doublereal *d__, __CLPK_doublereal *z__, 
	__CLPK_doublereal *delta, __CLPK_doublereal *rho, __CLPK_doublereal *dlam) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed6_(__CLPK_integer *kniter, __CLPK_logical *orgati, __CLPK_doublereal *
	rho, __CLPK_doublereal *d__, __CLPK_doublereal *z__, __CLPK_doublereal *finit, __CLPK_doublereal *
	tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed7_(__CLPK_integer *icompq, __CLPK_integer *n, __CLPK_integer *qsiz, 
	__CLPK_integer *tlvls, __CLPK_integer *curlvl, __CLPK_integer *curpbm, __CLPK_doublereal *d__, 
	__CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_integer *indxq, __CLPK_doublereal *rho, __CLPK_integer 
	*cutpnt, __CLPK_doublereal *qstore, __CLPK_integer *qptr, __CLPK_integer *prmptr, __CLPK_integer *
	perm, __CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_doublereal *givnum, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed8_(__CLPK_integer *icompq, __CLPK_integer *k, __CLPK_integer *n, __CLPK_integer 
	*qsiz, __CLPK_doublereal *d__, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_integer *indxq, 
	__CLPK_doublereal *rho, __CLPK_integer *cutpnt, __CLPK_doublereal *z__, __CLPK_doublereal *dlamda, 
	 __CLPK_doublereal *q2, __CLPK_integer *ldq2, __CLPK_doublereal *w, __CLPK_integer *perm, __CLPK_integer 
	*givptr, __CLPK_integer *givcol, __CLPK_doublereal *givnum, __CLPK_integer *indxp, __CLPK_integer 
	*indx, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaed9_(__CLPK_integer *k, __CLPK_integer *kstart, __CLPK_integer *kstop, 
	__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *
	rho, __CLPK_doublereal *dlamda, __CLPK_doublereal *w, __CLPK_doublereal *s, __CLPK_integer *lds, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaeda_(__CLPK_integer *n, __CLPK_integer *tlvls, __CLPK_integer *curlvl, 
	__CLPK_integer *curpbm, __CLPK_integer *prmptr, __CLPK_integer *perm, __CLPK_integer *givptr, 
	__CLPK_integer *givcol, __CLPK_doublereal *givnum, __CLPK_doublereal *q, __CLPK_integer *qptr, 
	__CLPK_doublereal *z__, __CLPK_doublereal *ztemp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaein_(__CLPK_logical *rightv, __CLPK_logical *noinit, __CLPK_integer *n, 
	__CLPK_doublereal *h__, __CLPK_integer *ldh, __CLPK_doublereal *wr, __CLPK_doublereal *wi, 
	__CLPK_doublereal *vr, __CLPK_doublereal *vi, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *work, __CLPK_doublereal *eps3, __CLPK_doublereal *smlnum, __CLPK_doublereal *
	bignum, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaev2_(__CLPK_doublereal *a, __CLPK_doublereal *b, __CLPK_doublereal *c__, 
	__CLPK_doublereal *rt1, __CLPK_doublereal *rt2, __CLPK_doublereal *cs1, __CLPK_doublereal *sn1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaexc_(__CLPK_logical *wantq, __CLPK_integer *n, __CLPK_doublereal *t, 
	__CLPK_integer *ldt, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_integer *j1, __CLPK_integer *n1, 
	__CLPK_integer *n2, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlag2_(__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_doublereal *safmin, __CLPK_doublereal *scale1, __CLPK_doublereal *
	scale2, __CLPK_doublereal *wr1, __CLPK_doublereal *wr2, __CLPK_doublereal *wi) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlag2s_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_real *sa, __CLPK_integer *ldsa, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlags2_(__CLPK_logical *upper, __CLPK_doublereal *a1, __CLPK_doublereal *a2, 
	__CLPK_doublereal *a3, __CLPK_doublereal *b1, __CLPK_doublereal *b2, __CLPK_doublereal *b3, 
	__CLPK_doublereal *csu, __CLPK_doublereal *snu, __CLPK_doublereal *csv, __CLPK_doublereal *snv, 
	__CLPK_doublereal *csq, __CLPK_doublereal *snq) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlagtf_(__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_doublereal *lambda, 
	__CLPK_doublereal *b, __CLPK_doublereal *c__, __CLPK_doublereal *tol, __CLPK_doublereal *d__, 
	__CLPK_integer *in, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlagtm_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *alpha, __CLPK_doublereal *dl, __CLPK_doublereal *d__, __CLPK_doublereal *du, 
	__CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *beta, __CLPK_doublereal *b, __CLPK_integer 
	*ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlagts_(__CLPK_integer *job, __CLPK_integer *n, __CLPK_doublereal *a, 
	__CLPK_doublereal *b, __CLPK_doublereal *c__, __CLPK_doublereal *d__, __CLPK_integer *in, 
	__CLPK_doublereal *y, __CLPK_doublereal *tol, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlagv2_(__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_doublereal *alphar, __CLPK_doublereal *alphai, __CLPK_doublereal *
	beta, __CLPK_doublereal *csl, __CLPK_doublereal *snl, __CLPK_doublereal *csr, __CLPK_doublereal *
	snr) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlahqr_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *h__, __CLPK_integer *ldh, __CLPK_doublereal 
	*wr, __CLPK_doublereal *wi, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlahr2_(__CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *nb, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *t, __CLPK_integer *ldt, 
	__CLPK_doublereal *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlahrd_(__CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *nb, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *t, __CLPK_integer *ldt, 
	__CLPK_doublereal *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaic1_(__CLPK_integer *job, __CLPK_integer *j, __CLPK_doublereal *x, 
	__CLPK_doublereal *sest, __CLPK_doublereal *w, __CLPK_doublereal *gamma, __CLPK_doublereal *
	sestpr, __CLPK_doublereal *s, __CLPK_doublereal *c__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_logical dlaisnan_(__CLPK_doublereal *din1, __CLPK_doublereal *din2) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaln2_(__CLPK_logical *ltrans, __CLPK_integer *na, __CLPK_integer *nw, 
	__CLPK_doublereal *smin, __CLPK_doublereal *ca, __CLPK_doublereal *a, __CLPK_integer *lda, 
	__CLPK_doublereal *d1, __CLPK_doublereal *d2, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *wr, __CLPK_doublereal *wi, __CLPK_doublereal *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *scale, __CLPK_doublereal *xnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlals0_(__CLPK_integer *icompq, __CLPK_integer *nl, __CLPK_integer *nr, 
	__CLPK_integer *sqre, __CLPK_integer *nrhs, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal 
	*bx, __CLPK_integer *ldbx, __CLPK_integer *perm, __CLPK_integer *givptr, __CLPK_integer *givcol, 
	__CLPK_integer *ldgcol, __CLPK_doublereal *givnum, __CLPK_integer *ldgnum, __CLPK_doublereal *
	poles, __CLPK_doublereal *difl, __CLPK_doublereal *difr, __CLPK_doublereal *z__, __CLPK_integer *
	k, __CLPK_doublereal *c__, __CLPK_doublereal *s, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlalsa_(__CLPK_integer *icompq, __CLPK_integer *smlsiz, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *bx, __CLPK_integer *
	ldbx, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *vt, __CLPK_integer *k, 
	__CLPK_doublereal *difl, __CLPK_doublereal *difr, __CLPK_doublereal *z__, __CLPK_doublereal *
	poles, __CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_integer *ldgcol, __CLPK_integer *
	perm, __CLPK_doublereal *givnum, __CLPK_doublereal *c__, __CLPK_doublereal *s, __CLPK_doublereal *
	work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlalsd_(char *uplo, __CLPK_integer *smlsiz, __CLPK_integer *n, __CLPK_integer 
	*nrhs, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlamrg_(__CLPK_integer *n1, __CLPK_integer *n2, __CLPK_doublereal *a, __CLPK_integer 
	*dtrd1, __CLPK_integer *dtrd2, __CLPK_integer *index) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer dlaneg_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *lld, __CLPK_doublereal *
	sigma, __CLPK_doublereal *pivmin, __CLPK_integer *r__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlangb_(char *norm, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	__CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlange_(char *norm, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer 
	*lda, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlangt_(char *norm, __CLPK_integer *n, __CLPK_doublereal *dl, __CLPK_doublereal *d__, 
	__CLPK_doublereal *du) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlanhs_(char *norm, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, 
	__CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlansb_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal 
	*ab, __CLPK_integer *ldab, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlansf_(char *norm, char *transr, char *uplo, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlansp_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, 
	__CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlanst_(char *norm, __CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlansy_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer 
	*lda, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlantb_(char *norm, char *uplo, char *diag, __CLPK_integer *n, __CLPK_integer *k, 
	 __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlantp_(char *norm, char *uplo, char *diag, __CLPK_integer *n, __CLPK_doublereal 
	*ap, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlantr_(char *norm, char *uplo, char *diag, __CLPK_integer *m, __CLPK_integer *n, 
	 __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlanv2_(__CLPK_doublereal *a, __CLPK_doublereal *b, __CLPK_doublereal *c__, 
	__CLPK_doublereal *d__, __CLPK_doublereal *rt1r, __CLPK_doublereal *rt1i, __CLPK_doublereal *rt2r, 
	 __CLPK_doublereal *rt2i, __CLPK_doublereal *cs, __CLPK_doublereal *sn) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlapll_(__CLPK_integer *n, __CLPK_doublereal *x, __CLPK_integer *incx, 
	__CLPK_doublereal *y, __CLPK_integer *incy, __CLPK_doublereal *ssmin) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlapmt_(__CLPK_logical *forwrd, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_integer *k) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlapy2_(__CLPK_doublereal *x, __CLPK_doublereal *y) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlapy3_(__CLPK_doublereal *x, __CLPK_doublereal *y, __CLPK_doublereal *z__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqgb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *r__, __CLPK_doublereal *c__, 
	__CLPK_doublereal *rowcnd, __CLPK_doublereal *colcnd, __CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqge_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *r__, __CLPK_doublereal *c__, __CLPK_doublereal *rowcnd, __CLPK_doublereal 
	*colcnd, __CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqp2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *offset, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *jpvt, __CLPK_doublereal *tau, 
	__CLPK_doublereal *vn1, __CLPK_doublereal *vn2, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqps_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *offset, __CLPK_integer 
	*nb, __CLPK_integer *kb, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *jpvt, 
	__CLPK_doublereal *tau, __CLPK_doublereal *vn1, __CLPK_doublereal *vn2, __CLPK_doublereal *auxv, 
	__CLPK_doublereal *f, __CLPK_integer *ldf) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqr0_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *h__, __CLPK_integer *ldh, __CLPK_doublereal 
	*wr, __CLPK_doublereal *wi, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqr1_(__CLPK_integer *n, __CLPK_doublereal *h__, __CLPK_integer *ldh, 
	__CLPK_doublereal *sr1, __CLPK_doublereal *si1, __CLPK_doublereal *sr2, __CLPK_doublereal *si2, 
	__CLPK_doublereal *v) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqr2_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nw, __CLPK_doublereal *h__, __CLPK_integer *
	ldh, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublereal *z__, __CLPK_integer *ldz, 
	__CLPK_integer *ns, __CLPK_integer *nd, __CLPK_doublereal *sr, __CLPK_doublereal *si, __CLPK_doublereal *
	v, __CLPK_integer *ldv, __CLPK_integer *nh, __CLPK_doublereal *t, __CLPK_integer *ldt, __CLPK_integer *
	nv, __CLPK_doublereal *wv, __CLPK_integer *ldwv, __CLPK_doublereal *work, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqr3_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nw, __CLPK_doublereal *h__, __CLPK_integer *
	ldh, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublereal *z__, __CLPK_integer *ldz, 
	__CLPK_integer *ns, __CLPK_integer *nd, __CLPK_doublereal *sr, __CLPK_doublereal *si, __CLPK_doublereal *
	v, __CLPK_integer *ldv, __CLPK_integer *nh, __CLPK_doublereal *t, __CLPK_integer *ldt, __CLPK_integer *
	nv, __CLPK_doublereal *wv, __CLPK_integer *ldwv, __CLPK_doublereal *work, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqr4_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *h__, __CLPK_integer *ldh, __CLPK_doublereal 
	*wr, __CLPK_doublereal *wi, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqr5_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *kacc22, 
	__CLPK_integer *n, __CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nshfts, __CLPK_doublereal 
	*sr, __CLPK_doublereal *si, __CLPK_doublereal *h__, __CLPK_integer *ldh, __CLPK_integer *iloz, 
	__CLPK_integer *ihiz, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *v, __CLPK_integer *
	ldv, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_integer *nv, __CLPK_doublereal *wv, 
	__CLPK_integer *ldwv, __CLPK_integer *nh, __CLPK_doublereal *wh, __CLPK_integer *ldwh) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqsb_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_doublereal *
	ab, __CLPK_integer *ldab, __CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, 
	 char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqsp_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqsy_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaqtr_(__CLPK_logical *ltran, __CLPK_logical *l__CLPK_real, __CLPK_integer *n, 
	__CLPK_doublereal *t, __CLPK_integer *ldt, __CLPK_doublereal *b, __CLPK_doublereal *w, __CLPK_doublereal 
	*scale, __CLPK_doublereal *x, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlar1v_(__CLPK_integer *n, __CLPK_integer *b1, __CLPK_integer *bn, __CLPK_doublereal 
	*lambda, __CLPK_doublereal *d__, __CLPK_doublereal *l, __CLPK_doublereal *ld, __CLPK_doublereal *
	lld, __CLPK_doublereal *pivmin, __CLPK_doublereal *gaptol, __CLPK_doublereal *z__, __CLPK_logical 
	*wantnc, __CLPK_integer *negcnt, __CLPK_doublereal *ztz, __CLPK_doublereal *mingma, 
	__CLPK_integer *r__, __CLPK_integer *isuppz, __CLPK_doublereal *nrminv, __CLPK_doublereal *resid, 
	__CLPK_doublereal *rqcorr, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlar2v_(__CLPK_integer *n, __CLPK_doublereal *x, __CLPK_doublereal *y, 
	__CLPK_doublereal *z__, __CLPK_integer *incx, __CLPK_doublereal *c__, __CLPK_doublereal *s, 
	__CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarf_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *v, 
	 __CLPK_integer *incv, __CLPK_doublereal *tau, __CLPK_doublereal *c__, __CLPK_integer *ldc, 
	__CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarfb_(char *side, char *trans, char *direct, char *
	storev, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *v, __CLPK_integer *
	ldv, __CLPK_doublereal *t, __CLPK_integer *ldt, __CLPK_doublereal *c__, __CLPK_integer *ldc, 
	__CLPK_doublereal *work, __CLPK_integer *ldwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarfg_(__CLPK_integer *n, __CLPK_doublereal *alpha, __CLPK_doublereal *x, 
	__CLPK_integer *incx, __CLPK_doublereal *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarfp_(__CLPK_integer *n, __CLPK_doublereal *alpha, __CLPK_doublereal *x, 
	__CLPK_integer *incx, __CLPK_doublereal *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarft_(char *direct, char *storev, __CLPK_integer *n, __CLPK_integer *
	k, __CLPK_doublereal *v, __CLPK_integer *ldv, __CLPK_doublereal *tau, __CLPK_doublereal *t, 
	__CLPK_integer *ldt) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarfx_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *
	v, __CLPK_doublereal *tau, __CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlargv_(__CLPK_integer *n, __CLPK_doublereal *x, __CLPK_integer *incx, 
	__CLPK_doublereal *y, __CLPK_integer *incy, __CLPK_doublereal *c__, __CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarnv_(__CLPK_integer *idist, __CLPK_integer *iseed, __CLPK_integer *n, 
	__CLPK_doublereal *x) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarra_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_doublereal *e2, __CLPK_doublereal *spltol, __CLPK_doublereal *tnrm, __CLPK_integer *nsplit, 
	 __CLPK_integer *isplit, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarrb_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *lld, 
	__CLPK_integer *ifirst, __CLPK_integer *ilast, __CLPK_doublereal *rtol1, __CLPK_doublereal *rtol2, 
	 __CLPK_integer *offset, __CLPK_doublereal *w, __CLPK_doublereal *wgap, __CLPK_doublereal *werr, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_doublereal *pivmin, __CLPK_doublereal *
	spdiam, __CLPK_integer *twist, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarrc_(char *jobt, __CLPK_integer *n, __CLPK_doublereal *vl, 
	__CLPK_doublereal *vu, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *pivmin, 
	__CLPK_integer *eigcnt, __CLPK_integer *lcnt, __CLPK_integer *rcnt, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarrd_(char *range, char *order, __CLPK_integer *n, __CLPK_doublereal 
	*vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *gers, 
	__CLPK_doublereal *reltol, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *e2, 
	__CLPK_doublereal *pivmin, __CLPK_integer *nsplit, __CLPK_integer *isplit, __CLPK_integer *m, 
	__CLPK_doublereal *w, __CLPK_doublereal *werr, __CLPK_doublereal *wl, __CLPK_doublereal *wu, 
	__CLPK_integer *iblock, __CLPK_integer *indexw, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarre_(char *range, __CLPK_integer *n, __CLPK_doublereal *vl, 
	__CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *d__, __CLPK_doublereal 
	*e, __CLPK_doublereal *e2, __CLPK_doublereal *rtol1, __CLPK_doublereal *rtol2, __CLPK_doublereal *
	spltol, __CLPK_integer *nsplit, __CLPK_integer *isplit, __CLPK_integer *m, __CLPK_doublereal *w, 
	__CLPK_doublereal *werr, __CLPK_doublereal *wgap, __CLPK_integer *iblock, __CLPK_integer *indexw, 
	__CLPK_doublereal *gers, __CLPK_doublereal *pivmin, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarrf_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *l, 
	__CLPK_doublereal *ld, __CLPK_integer *clstrt, __CLPK_integer *clend, __CLPK_doublereal *w, 
	__CLPK_doublereal *wgap, __CLPK_doublereal *werr, __CLPK_doublereal *spdiam, __CLPK_doublereal *
	clgapl, __CLPK_doublereal *clgapr, __CLPK_doublereal *pivmin, __CLPK_doublereal *sigma, 
	__CLPK_doublereal *dplus, __CLPK_doublereal *lplus, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarrj_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e2, 
	__CLPK_integer *ifirst, __CLPK_integer *ilast, __CLPK_doublereal *rtol, __CLPK_integer *offset, 
	__CLPK_doublereal *w, __CLPK_doublereal *werr, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_doublereal *pivmin, __CLPK_doublereal *spdiam, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarrk_(__CLPK_integer *n, __CLPK_integer *iw, __CLPK_doublereal *gl, 
	__CLPK_doublereal *gu, __CLPK_doublereal *d__, __CLPK_doublereal *e2, __CLPK_doublereal *pivmin, 
	__CLPK_doublereal *reltol, __CLPK_doublereal *w, __CLPK_doublereal *werr, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarrr_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarrv_(__CLPK_integer *n, __CLPK_doublereal *vl, __CLPK_doublereal *vu, 
	__CLPK_doublereal *d__, __CLPK_doublereal *l, __CLPK_doublereal *pivmin, __CLPK_integer *isplit, 
	__CLPK_integer *m, __CLPK_integer *dol, __CLPK_integer *dou, __CLPK_doublereal *minrgp, 
	__CLPK_doublereal *rtol1, __CLPK_doublereal *rtol2, __CLPK_doublereal *w, __CLPK_doublereal *werr, 
	 __CLPK_doublereal *wgap, __CLPK_integer *iblock, __CLPK_integer *indexw, __CLPK_doublereal *gers, 
	 __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_doublereal *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarscl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *x, __CLPK_integer *ldx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlartg_(__CLPK_doublereal *f, __CLPK_doublereal *g, __CLPK_doublereal *cs, 
	__CLPK_doublereal *sn, __CLPK_doublereal *r__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlartv_(__CLPK_integer *n, __CLPK_doublereal *x, __CLPK_integer *incx, 
	__CLPK_doublereal *y, __CLPK_integer *incy, __CLPK_doublereal *c__, __CLPK_doublereal *s, __CLPK_integer 
	*incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaruv_(__CLPK_integer *iseed, __CLPK_integer *n, __CLPK_doublereal *x) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarz_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *l, 
	__CLPK_doublereal *v, __CLPK_integer *incv, __CLPK_doublereal *tau, __CLPK_doublereal *c__, 
	__CLPK_integer *ldc, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarzb_(char *side, char *trans, char *direct, char *
	storev, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *l, __CLPK_doublereal *v, 
	 __CLPK_integer *ldv, __CLPK_doublereal *t, __CLPK_integer *ldt, __CLPK_doublereal *c__, __CLPK_integer *
	ldc, __CLPK_doublereal *work, __CLPK_integer *ldwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlarzt_(char *direct, char *storev, __CLPK_integer *n, __CLPK_integer *
	k, __CLPK_doublereal *v, __CLPK_integer *ldv, __CLPK_doublereal *tau, __CLPK_doublereal *t, 
	__CLPK_integer *ldt) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlas2_(__CLPK_doublereal *f, __CLPK_doublereal *g, __CLPK_doublereal *h__, 
	__CLPK_doublereal *ssmin, __CLPK_doublereal *ssmax) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlascl_(char *type__, __CLPK_integer *kl, __CLPK_integer *ku, 
	__CLPK_doublereal *cfrom, __CLPK_doublereal *cto, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlascl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *x, __CLPK_integer *ldx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd0_(__CLPK_integer *n, __CLPK_integer *sqre, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *vt, __CLPK_integer *
	ldvt, __CLPK_integer *smlsiz, __CLPK_integer *iwork, __CLPK_doublereal *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd1_(__CLPK_integer *nl, __CLPK_integer *nr, __CLPK_integer *sqre, 
	__CLPK_doublereal *d__, __CLPK_doublereal *alpha, __CLPK_doublereal *beta, __CLPK_doublereal *u, 
	__CLPK_integer *ldu, __CLPK_doublereal *vt, __CLPK_integer *ldvt, __CLPK_integer *idxq, __CLPK_integer *
	iwork, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd2_(__CLPK_integer *nl, __CLPK_integer *nr, __CLPK_integer *sqre, __CLPK_integer 
	*k, __CLPK_doublereal *d__, __CLPK_doublereal *z__, __CLPK_doublereal *alpha, __CLPK_doublereal *
	beta, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *vt, __CLPK_integer *ldvt, 
	__CLPK_doublereal *dsigma, __CLPK_doublereal *u2, __CLPK_integer *ldu2, __CLPK_doublereal *vt2, 
	__CLPK_integer *ldvt2, __CLPK_integer *idxp, __CLPK_integer *idx, __CLPK_integer *idxc, __CLPK_integer *
	idxq, __CLPK_integer *coltyp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd3_(__CLPK_integer *nl, __CLPK_integer *nr, __CLPK_integer *sqre, __CLPK_integer 
	*k, __CLPK_doublereal *d__, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *dsigma, 
	__CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *u2, __CLPK_integer *ldu2, 
	__CLPK_doublereal *vt, __CLPK_integer *ldvt, __CLPK_doublereal *vt2, __CLPK_integer *ldvt2, 
	__CLPK_integer *idxc, __CLPK_integer *ctot, __CLPK_doublereal *z__, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd4_(__CLPK_integer *n, __CLPK_integer *i__, __CLPK_doublereal *d__, 
	__CLPK_doublereal *z__, __CLPK_doublereal *delta, __CLPK_doublereal *rho, __CLPK_doublereal *
	sigma, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd5_(__CLPK_integer *i__, __CLPK_doublereal *d__, __CLPK_doublereal *z__, 
	__CLPK_doublereal *delta, __CLPK_doublereal *rho, __CLPK_doublereal *dsigma, __CLPK_doublereal *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd6_(__CLPK_integer *icompq, __CLPK_integer *nl, __CLPK_integer *nr, 
	__CLPK_integer *sqre, __CLPK_doublereal *d__, __CLPK_doublereal *vf, __CLPK_doublereal *vl, 
	__CLPK_doublereal *alpha, __CLPK_doublereal *beta, __CLPK_integer *idxq, __CLPK_integer *perm, 
	__CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_integer *ldgcol, __CLPK_doublereal *givnum, 
	 __CLPK_integer *ldgnum, __CLPK_doublereal *poles, __CLPK_doublereal *difl, __CLPK_doublereal *
	difr, __CLPK_doublereal *z__, __CLPK_integer *k, __CLPK_doublereal *c__, __CLPK_doublereal *s, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd7_(__CLPK_integer *icompq, __CLPK_integer *nl, __CLPK_integer *nr, 
	__CLPK_integer *sqre, __CLPK_integer *k, __CLPK_doublereal *d__, __CLPK_doublereal *z__, 
	__CLPK_doublereal *zw, __CLPK_doublereal *vf, __CLPK_doublereal *vfw, __CLPK_doublereal *vl, 
	__CLPK_doublereal *vlw, __CLPK_doublereal *alpha, __CLPK_doublereal *beta, __CLPK_doublereal *
	dsigma, __CLPK_integer *idx, __CLPK_integer *idxp, __CLPK_integer *idxq, __CLPK_integer *perm, 
	__CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_integer *ldgcol, __CLPK_doublereal *givnum, 
	 __CLPK_integer *ldgnum, __CLPK_doublereal *c__, __CLPK_doublereal *s, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasd8_(__CLPK_integer *icompq, __CLPK_integer *k, __CLPK_doublereal *d__, 
	__CLPK_doublereal *z__, __CLPK_doublereal *vf, __CLPK_doublereal *vl, __CLPK_doublereal *difl, 
	__CLPK_doublereal *difr, __CLPK_integer *lddifr, __CLPK_doublereal *dsigma, __CLPK_doublereal *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasda_(__CLPK_integer *icompq, __CLPK_integer *smlsiz, __CLPK_integer *n, 
	__CLPK_integer *sqre, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *u, __CLPK_integer 
	*ldu, __CLPK_doublereal *vt, __CLPK_integer *k, __CLPK_doublereal *difl, __CLPK_doublereal *difr, 
	__CLPK_doublereal *z__, __CLPK_doublereal *poles, __CLPK_integer *givptr, __CLPK_integer *givcol, 
	__CLPK_integer *ldgcol, __CLPK_integer *perm, __CLPK_doublereal *givnum, __CLPK_doublereal *c__, 
	__CLPK_doublereal *s, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasdq_(char *uplo, __CLPK_integer *sqre, __CLPK_integer *n, __CLPK_integer *
	ncvt, __CLPK_integer *nru, __CLPK_integer *ncc, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_doublereal *vt, __CLPK_integer *ldvt, __CLPK_doublereal *u, __CLPK_integer *ldu, 
	__CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasdt_(__CLPK_integer *n, __CLPK_integer *lvl, __CLPK_integer *nd, __CLPK_integer *
	inode, __CLPK_integer *ndiml, __CLPK_integer *ndimr, __CLPK_integer *msub) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaset_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *
	alpha, __CLPK_doublereal *beta, __CLPK_doublereal *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasq1_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasq2_(__CLPK_integer *n, __CLPK_doublereal *z__, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasq3_(__CLPK_integer *i0, __CLPK_integer *n0, __CLPK_doublereal *z__, 
	__CLPK_integer *pp, __CLPK_doublereal *dmin__, __CLPK_doublereal *sigma, __CLPK_doublereal *desig, 
	 __CLPK_doublereal *qmax, __CLPK_integer *nfail, __CLPK_integer *iter, __CLPK_integer *ndiv, 
	__CLPK_logical *ieee, __CLPK_integer *ttype, __CLPK_doublereal *dmin1, __CLPK_doublereal *dmin2, 
	__CLPK_doublereal *dn, __CLPK_doublereal *dn1, __CLPK_doublereal *dn2, __CLPK_doublereal *g, 
	__CLPK_doublereal *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasq4_(__CLPK_integer *i0, __CLPK_integer *n0, __CLPK_doublereal *z__, 
	__CLPK_integer *pp, __CLPK_integer *n0in, __CLPK_doublereal *dmin__, __CLPK_doublereal *dmin1, 
	__CLPK_doublereal *dmin2, __CLPK_doublereal *dn, __CLPK_doublereal *dn1, __CLPK_doublereal *dn2, 
	__CLPK_doublereal *tau, __CLPK_integer *ttype, __CLPK_doublereal *g) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasq5_(__CLPK_integer *i0, __CLPK_integer *n0, __CLPK_doublereal *z__, 
	__CLPK_integer *pp, __CLPK_doublereal *tau, __CLPK_doublereal *dmin__, __CLPK_doublereal *dmin1, 
	__CLPK_doublereal *dmin2, __CLPK_doublereal *dn, __CLPK_doublereal *dnm1, __CLPK_doublereal *dnm2, 
	 __CLPK_logical *ieee) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasq6_(__CLPK_integer *i0, __CLPK_integer *n0, __CLPK_doublereal *z__, 
	__CLPK_integer *pp, __CLPK_doublereal *dmin__, __CLPK_doublereal *dmin1, __CLPK_doublereal *dmin2, 
	 __CLPK_doublereal *dn, __CLPK_doublereal *dnm1, __CLPK_doublereal *dnm2) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasr_(char *side, char *pivot, char *direct, __CLPK_integer *m, 
	 __CLPK_integer *n, __CLPK_doublereal *c__, __CLPK_doublereal *s, __CLPK_doublereal *a, __CLPK_integer *
	lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasrt_(char *id, __CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlassq_(__CLPK_integer *n, __CLPK_doublereal *x, __CLPK_integer *incx, 
	__CLPK_doublereal *scale, __CLPK_doublereal *sumsq) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasv2_(__CLPK_doublereal *f, __CLPK_doublereal *g, __CLPK_doublereal *h__, 
	__CLPK_doublereal *ssmin, __CLPK_doublereal *ssmax, __CLPK_doublereal *snr, __CLPK_doublereal *
	csr, __CLPK_doublereal *snl, __CLPK_doublereal *csl) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlaswp_(__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer 
	*k1, __CLPK_integer *k2, __CLPK_integer *ipiv, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasy2_(__CLPK_logical *ltranl, __CLPK_logical *ltranr, __CLPK_integer *isgn, 
	__CLPK_integer *n1, __CLPK_integer *n2, __CLPK_doublereal *tl, __CLPK_integer *ldtl, __CLPK_doublereal *
	tr, __CLPK_integer *ldtr, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *scale, 
	__CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *xnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlasyf_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_integer *kb, 
	 __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublereal *w, __CLPK_integer *
	ldw, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlat2s_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_real *sa, __CLPK_integer *ldsa, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlatbs_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_doublereal *ab, __CLPK_integer *ldab, 
	__CLPK_doublereal *x, __CLPK_doublereal *scale, __CLPK_doublereal *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlatdf_(__CLPK_integer *ijob, __CLPK_integer *n, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *rhs, __CLPK_doublereal *rdsum, __CLPK_doublereal *rdscal, 
	__CLPK_integer *ipiv, __CLPK_integer *jpiv) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlatps_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_doublereal *ap, __CLPK_doublereal *x, __CLPK_doublereal *scale, 
	__CLPK_doublereal *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlatrd_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *e, __CLPK_doublereal *tau, __CLPK_doublereal *w, 
	__CLPK_integer *ldw) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlatrs_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *x, 
	__CLPK_doublereal *scale, __CLPK_doublereal *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlatrz_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *l, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlatzm_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *
	v, __CLPK_integer *incv, __CLPK_doublereal *tau, __CLPK_doublereal *c1, __CLPK_doublereal *c2, 
	__CLPK_integer *ldc, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlauu2_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlauum_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dopgtr_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, 
	__CLPK_doublereal *tau, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dopmtr_(char *side, char *uplo, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_doublereal *ap, __CLPK_doublereal *tau, __CLPK_doublereal *c__, __CLPK_integer 
	*ldc, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorg2l_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorg2r_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorgbr_(char *vect, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorghr_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorgl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorglq_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorgql_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorgqr_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorgr2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorgrq_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorgtr_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorm2l_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorm2r_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormbr_(char *vect, char *side, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, 
	__CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormhr_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *
	tau, __CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dorml2_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormlq_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormql_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormqr_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormr2_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormr3_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_integer *l, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, 
	__CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormrq_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormrz_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_integer *l, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, 
	__CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dormtr_(char *side, char *uplo, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *tau, __CLPK_doublereal *
	c__, __CLPK_integer *ldc, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbcon_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_doublereal *
	ab, __CLPK_integer *ldab, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *
	work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbequ_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_doublereal *
	ab, __CLPK_integer *ldab, __CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *afb, __CLPK_integer *ldafb, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *
	ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbstf_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_doublereal *
	ab, __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_integer *nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *afb, 
	__CLPK_integer *ldafb, char *equed, __CLPK_doublereal *s, __CLPK_doublereal *b, __CLPK_integer *
	ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, 
	 __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbtf2_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_doublereal *
	ab, __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbtrf_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_doublereal *
	ab, __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpbtrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpftrf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_doublereal 
	*a, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpftri_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_doublereal 
	*a, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpftrs_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublereal *a, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpocon_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpoequ_(__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpoequb_(__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dporfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *af, __CLPK_integer *ldaf, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *
	ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dposv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal 
	*a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dposvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *af, __CLPK_integer *ldaf, 
	char *equed, __CLPK_doublereal *s, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *
	x, __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *
	berr, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpotf2_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpotrf_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpotri_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpotrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dppcon_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, 
	__CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dppequ_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *ap, __CLPK_doublereal *afp, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dppsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal 
	*ap, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dppsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublereal *ap, __CLPK_doublereal *afp, char *equed, __CLPK_doublereal *s, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *
	rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpptrf_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpptri_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *ap, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpstf2_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *piv, __CLPK_integer *rank, __CLPK_doublereal *tol, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpstrf_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *piv, __CLPK_integer *rank, __CLPK_doublereal *tol, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dptcon_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpteqr_(char *compz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dptrfs_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *df, __CLPK_doublereal *ef, __CLPK_doublereal *b, __CLPK_integer 
	*ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	 __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dptsv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dptsvx_(char *fact, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *df, __CLPK_doublereal *ef, 
	__CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *
	rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpttrf_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dpttrs_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dptts2_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int drscl_(__CLPK_integer *n, __CLPK_doublereal *sa, __CLPK_doublereal *sx, 
	__CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsbev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *w, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsbevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *w, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsbevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *q, __CLPK_integer *
	ldq, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, 
	__CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *ifail, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsbgst_(char *vect, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *bb, __CLPK_integer *
	ldbb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsbgv_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *bb, __CLPK_integer *
	ldbb, __CLPK_doublereal *w, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsbgvd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *bb, __CLPK_integer *
	ldbb, __CLPK_doublereal *w, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsbgvx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_integer *ka, __CLPK_integer *kb, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *
	bb, __CLPK_integer *ldbb, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *vl, 
	__CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer 
	*m, __CLPK_doublereal *w, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsbtrd_(char *vect, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsfrk_(char *transr, char *uplo, char *trans, __CLPK_integer *n, 
	 __CLPK_integer *k, __CLPK_doublereal *alpha, __CLPK_doublereal *a, __CLPK_integer *lda, 
	__CLPK_doublereal *beta, __CLPK_doublereal *c__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsgesv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *
	x, __CLPK_integer *ldx, __CLPK_doublereal *work, __CLPK_real *swork, __CLPK_integer *iter, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspcon_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, __CLPK_integer *
	ipiv, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *work, __CLPK_integer 
	*iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_doublereal *
	ap, __CLPK_doublereal *w, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_doublereal *
	ap, __CLPK_doublereal *w, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_doublereal *ap, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *
	iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *ifail, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspgst_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, 
	__CLPK_doublereal *ap, __CLPK_doublereal *bp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspgv_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_doublereal *ap, __CLPK_doublereal *bp, __CLPK_doublereal *w, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspgvd_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_doublereal *ap, __CLPK_doublereal *bp, __CLPK_doublereal *w, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspgvx_(__CLPK_integer *itype, char *jobz, char *range, char *
	uplo, __CLPK_integer *n, __CLPK_doublereal *ap, __CLPK_doublereal *bp, __CLPK_doublereal *vl, 
	__CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer 
	*m, __CLPK_doublereal *w, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsposv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *
	x, __CLPK_integer *ldx, __CLPK_doublereal *work, __CLPK_real *swork, __CLPK_integer *iter, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *ap, __CLPK_doublereal *afp, __CLPK_integer *ipiv, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal 
	*ap, __CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dspsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublereal *ap, __CLPK_doublereal *afp, __CLPK_integer *ipiv, __CLPK_doublereal *b, 
	__CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *rcond, 
	__CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsptrd_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, 
	__CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsptrf_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, __CLPK_integer *
	ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsptri_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, __CLPK_integer *
	ipiv, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *ap, __CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstebz_(char *range, char *order, __CLPK_integer *n, __CLPK_doublereal 
	*vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *abstol, 
	__CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_integer *m, __CLPK_integer *nsplit, 
	__CLPK_doublereal *w, __CLPK_integer *iblock, __CLPK_integer *isplit, __CLPK_doublereal *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstedc_(char *compz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstegr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_doublereal *
	d__, __CLPK_doublereal *e, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, 
	__CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, 
	__CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstein_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_integer *m, __CLPK_doublereal *w, __CLPK_integer *iblock, __CLPK_integer *isplit, 
	__CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstemr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_doublereal *
	d__, __CLPK_doublereal *e, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, 
	__CLPK_integer *iu, __CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublereal *z__, __CLPK_integer *ldz, 
	 __CLPK_integer *nzc, __CLPK_integer *isuppz, __CLPK_logical *tryrac, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsteqr_(char *compz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsterf_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstev_(char *jobz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstevd_(char *jobz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstevr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_doublereal *
	d__, __CLPK_doublereal *e, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, 
	__CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, 
	__CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dstevx_(char *jobz, char *range, __CLPK_integer *n, __CLPK_doublereal *
	d__, __CLPK_doublereal *e, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, 
	__CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, 
	__CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsycon_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *ipiv, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *
	work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsyequb_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, __CLPK_doublereal *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsyev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, 
	 __CLPK_integer *lda, __CLPK_doublereal *w, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsyevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublereal *w, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsyevr_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *
	il, __CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, 
	__CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsyevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *
	il, __CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, 
	__CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *lwork, 
	__CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsygs2_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsygst_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsygv_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *w, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsygvd_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *w, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsygvx_(__CLPK_integer *itype, char *jobz, char *range, char *
	uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer 
	*ldb, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, 
	__CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublereal *z__, 
	__CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, 
	__CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsyrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *af, __CLPK_integer *ldaf, __CLPK_integer *
	ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsysv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal 
	*a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsysvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *af, __CLPK_integer *ldaf, 
	__CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *
	ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsytd2_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsytf2_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsytrd_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublereal *tau, __CLPK_doublereal *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsytrf_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *ipiv, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsytri_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_integer *ipiv, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dsytrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublereal *b, __CLPK_integer *
	ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtbcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal *rcond, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtbrfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_integer *nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal 
	*b, __CLPK_integer *ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtbtrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_integer *nrhs, __CLPK_doublereal *ab, __CLPK_integer *ldab, __CLPK_doublereal 
	*b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtfsm_(char *transr, char *side, char *uplo, char *trans, 
	 char *diag, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *alpha, __CLPK_doublereal *a, 
	 __CLPK_doublereal *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtftri_(char *transr, char *uplo, char *diag, __CLPK_integer *n, 
	 __CLPK_doublereal *a, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtfttp_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_doublereal 
	*arf, __CLPK_doublereal *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtfttr_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_doublereal 
	*arf, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtgevc_(char *side, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_doublereal *s, __CLPK_integer *lds, __CLPK_doublereal *p, __CLPK_integer *ldp, 
	__CLPK_doublereal *vl, __CLPK_integer *ldvl, __CLPK_doublereal *vr, __CLPK_integer *ldvr, __CLPK_integer 
	*mm, __CLPK_integer *m, __CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtgex2_(__CLPK_logical *wantq, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *
	q, __CLPK_integer *ldq, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_integer *j1, __CLPK_integer *
	n1, __CLPK_integer *n2, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtgexc_(__CLPK_logical *wantq, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *
	q, __CLPK_integer *ldq, __CLPK_doublereal *z__, __CLPK_integer *ldz, __CLPK_integer *ifst, 
	__CLPK_integer *ilst, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtgsen_(__CLPK_integer *ijob, __CLPK_logical *wantq, __CLPK_logical *wantz, 
	__CLPK_logical *select, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *
	b, __CLPK_integer *ldb, __CLPK_doublereal *alphar, __CLPK_doublereal *alphai, __CLPK_doublereal *
	beta, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_doublereal *z__, __CLPK_integer *ldz, 
	__CLPK_integer *m, __CLPK_doublereal *pl, __CLPK_doublereal *pr, __CLPK_doublereal *dif, 
	__CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtgsja_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *p, __CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *l, __CLPK_doublereal *a, 
	__CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublereal *tola, 
	__CLPK_doublereal *tolb, __CLPK_doublereal *alpha, __CLPK_doublereal *beta, __CLPK_doublereal *u, 
	__CLPK_integer *ldu, __CLPK_doublereal *v, __CLPK_integer *ldv, __CLPK_doublereal *q, __CLPK_integer *
	ldq, __CLPK_doublereal *work, __CLPK_integer *ncycle, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtgsna_(char *job, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *vl, __CLPK_integer *ldvl, __CLPK_doublereal *vr, __CLPK_integer *ldvr, 
	__CLPK_doublereal *s, __CLPK_doublereal *dif, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_doublereal *
	work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtgsy2_(char *trans, __CLPK_integer *ijob, __CLPK_integer *m, __CLPK_integer *
	n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *d__, __CLPK_integer *ldd, 
	__CLPK_doublereal *e, __CLPK_integer *lde, __CLPK_doublereal *f, __CLPK_integer *ldf, __CLPK_doublereal *
	scale, __CLPK_doublereal *rdsum, __CLPK_doublereal *rdscal, __CLPK_integer *iwork, __CLPK_integer 
	*pq, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtgsyl_(char *trans, __CLPK_integer *ijob, __CLPK_integer *m, __CLPK_integer *
	n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *d__, __CLPK_integer *ldd, 
	__CLPK_doublereal *e, __CLPK_integer *lde, __CLPK_doublereal *f, __CLPK_integer *ldf, __CLPK_doublereal *
	scale, __CLPK_doublereal *dif, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtpcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_doublereal *ap, __CLPK_doublereal *rcond, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtprfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublereal *ap, __CLPK_doublereal *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtptri_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_doublereal *
	ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtptrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublereal *ap, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtpttf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_doublereal 
	*ap, __CLPK_doublereal *arf, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtpttr_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *ap, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *rcond, __CLPK_doublereal *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrevc_(char *side, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_doublereal *t, __CLPK_integer *ldt, __CLPK_doublereal *vl, __CLPK_integer *
	ldvl, __CLPK_doublereal *vr, __CLPK_integer *ldvr, __CLPK_integer *mm, __CLPK_integer *m, 
	__CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrexc_(char *compq, __CLPK_integer *n, __CLPK_doublereal *t, __CLPK_integer *
	ldt, __CLPK_doublereal *q, __CLPK_integer *ldq, __CLPK_integer *ifst, __CLPK_integer *ilst, 
	__CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrrfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *
	ldb, __CLPK_doublereal *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublereal *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrsen_(char *job, char *compq, __CLPK_logical *select, __CLPK_integer 
	*n, __CLPK_doublereal *t, __CLPK_integer *ldt, __CLPK_doublereal *q, __CLPK_integer *ldq, 
	__CLPK_doublereal *wr, __CLPK_doublereal *wi, __CLPK_integer *m, __CLPK_doublereal *s, __CLPK_doublereal 
	*sep, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *
	liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrsna_(char *job, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_doublereal *t, __CLPK_integer *ldt, __CLPK_doublereal *vl, __CLPK_integer *
	ldvl, __CLPK_doublereal *vr, __CLPK_integer *ldvr, __CLPK_doublereal *s, __CLPK_doublereal *sep, 
	__CLPK_integer *mm, __CLPK_integer *m, __CLPK_doublereal *work, __CLPK_integer *ldwork, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrsyl_(char *trana, char *tranb, __CLPK_integer *isgn, __CLPK_integer 
	*m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *
	ldb, __CLPK_doublereal *c__, __CLPK_integer *ldc, __CLPK_doublereal *scale, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrti2_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrtri_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrtrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *
	ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrttf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_doublereal 
	*a, __CLPK_integer *lda, __CLPK_doublereal *arf, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtrttp_(char *uplo, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtzrqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dtzrzf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublereal *tau, __CLPK_doublereal *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dzsum1_(__CLPK_integer *n, __CLPK_doublecomplex *cx, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer icmax1_(__CLPK_integer *n, __CLPK_complex *cx, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ieeeck_(__CLPK_integer *ispec, __CLPK_real *zero, __CLPK_real *one) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilaclc_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilaclr_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_complex *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer iladiag_(char *diag) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer iladlc_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer iladlr_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilaenv_(__CLPK_integer *ispec, char *name__, char *opts, __CLPK_integer *n1, 
	__CLPK_integer *n2, __CLPK_integer *n3, __CLPK_integer *n4) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilaprec_(char *prec) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilaslc_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilaslr_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilatrans_(char *trans) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilauplo_(char *uplo) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ilaver_(__CLPK_integer *vers_major__, __CLPK_integer *vers_minor__, 
	__CLPK_integer *vers_patch__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilazlc_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilazlr_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer iparmq_(__CLPK_integer *ispec, char *name__, char *opts, __CLPK_integer *n, __CLPK_integer 
	*ilo, __CLPK_integer *ihi, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer izmax1_(__CLPK_integer *n, __CLPK_doublecomplex *cx, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_logical lsamen_(__CLPK_integer *n, char *ca, char *cb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer smaxloc_(__CLPK_real *a, __CLPK_integer *dimm) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sbdsdc_(char *uplo, char *compq, __CLPK_integer *n, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *vt, __CLPK_integer *ldvt, __CLPK_real *q, 
	__CLPK_integer *iq, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sbdsqr_(char *uplo, __CLPK_integer *n, __CLPK_integer *ncvt, __CLPK_integer *
	nru, __CLPK_integer *ncc, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *vt, __CLPK_integer *ldvt, __CLPK_real *
	u, __CLPK_integer *ldu, __CLPK_real *c__, __CLPK_integer *ldc, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal scsum1_(__CLPK_integer *n, __CLPK_complex *cx, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sdisna_(char *job, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *d__, 
	__CLPK_real *sep, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbbrd_(char *vect, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *ncc, 
	 __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *d__, __CLPK_real *
	e, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *pt, __CLPK_integer *ldpt, __CLPK_real *c__, __CLPK_integer 
	*ldc, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbcon_(char *norm, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_real *anorm, __CLPK_real *rcond, 
	__CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbequ_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real *
	colcnd, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbequb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real 
	*colcnd, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbrfs_(char *trans, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_integer *nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *afb, __CLPK_integer *ldafb, 
	 __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *
	ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbsv_(__CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_integer *
	nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbsvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *kl, 
	 __CLPK_integer *ku, __CLPK_integer *nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *afb, 
	__CLPK_integer *ldafb, __CLPK_integer *ipiv, char *equed, __CLPK_real *r__, __CLPK_real *c__, 
	__CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, 
	 __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbtf2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbtrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgbtrs_(char *trans, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_integer *nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_real *b, 
	__CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgebak_(char *job, char *side, __CLPK_integer *n, __CLPK_integer *ilo, 
	__CLPK_integer *ihi, __CLPK_real *scale, __CLPK_integer *m, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_integer 
	*info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgebal_(char *job, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *scale, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgebd2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *d__, __CLPK_real *e, __CLPK_real *tauq, __CLPK_real *taup, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgebrd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *d__, __CLPK_real *e, __CLPK_real *tauq, __CLPK_real *taup, __CLPK_real *work, __CLPK_integer *
	lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgecon_(char *norm, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *anorm, __CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeequ_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real *colcnd, __CLPK_real *amax, __CLPK_integer 
	*info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeequb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real *colcnd, __CLPK_real *amax, __CLPK_integer 
	*info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgees_(char *jobvs, char *sort, __CLPK_L_fp select, __CLPK_integer *n, 
	__CLPK_real *a, __CLPK_integer *lda, __CLPK_integer *sdim, __CLPK_real *wr, __CLPK_real *wi, __CLPK_real *vs, 
	__CLPK_integer *ldvs, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_logical *bwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeesx_(char *jobvs, char *sort, __CLPK_L_fp select, char *
	sense, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_integer *sdim, __CLPK_real *wr, 
	__CLPK_real *wi, __CLPK_real *vs, __CLPK_integer *ldvs, __CLPK_real *rconde, __CLPK_real *rcondv, __CLPK_real *
	work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_logical *bwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeev_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *wr, __CLPK_real *wi, __CLPK_real *vl, __CLPK_integer *ldvl, __CLPK_real *vr, 
	__CLPK_integer *ldvr, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *wr, __CLPK_real *wi, __CLPK_real *
	vl, __CLPK_integer *ldvl, __CLPK_real *vr, __CLPK_integer *ldvr, __CLPK_integer *ilo, __CLPK_integer *
	ihi, __CLPK_real *scale, __CLPK_real *abnrm, __CLPK_real *rconde, __CLPK_real *rcondv, __CLPK_real *work, 
	 __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgegs_(char *jobvsl, char *jobvsr, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *alphar, __CLPK_real *alphai, __CLPK_real 
	*beta, __CLPK_real *vsl, __CLPK_integer *ldvsl, __CLPK_real *vsr, __CLPK_integer *ldvsr, __CLPK_real *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgegv_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *alphar, __CLPK_real *alphai, __CLPK_real 
	*beta, __CLPK_real *vl, __CLPK_integer *ldvl, __CLPK_real *vr, __CLPK_integer *ldvr, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgehd2_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgehrd_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgejsv_(char *joba, char *jobu, char *jobv, char *jobr, 
	char *jobt, char *jobp, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	 __CLPK_real *sva, __CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgelq2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgelqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgels_(char *trans, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgelsd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *s, __CLPK_real *rcond, __CLPK_integer *
	rank, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgelss_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *s, __CLPK_real *rcond, __CLPK_integer *
	rank, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgelsx_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *jpvt, __CLPK_real *rcond, 
	__CLPK_integer *rank, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgelsy_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *jpvt, __CLPK_real *rcond, 
	__CLPK_integer *rank, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeql2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeqlf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeqp3_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *jpvt, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeqpf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *jpvt, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeqr2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgeqrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgerfs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *af, __CLPK_integer *ldaf, __CLPK_integer *ipiv, __CLPK_real *b, 
	__CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *
	work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgerq2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgerqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgesc2_(__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *rhs, 
	__CLPK_integer *ipiv, __CLPK_integer *jpiv, __CLPK_real *scale) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgesdd_(char *jobz, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *s, __CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *vt, __CLPK_integer *ldvt, 
	 __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgesv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgesvd_(char *jobu, char *jobvt, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_real *a, __CLPK_integer *lda, __CLPK_real *s, __CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *vt, 
	__CLPK_integer *ldvt, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgesvj_(char *joba, char *jobu, char *jobv, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *sva, __CLPK_integer *mv, __CLPK_real *v, 
	__CLPK_integer *ldv, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgesvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *af, __CLPK_integer *ldaf, __CLPK_integer *ipiv, 
	char *equed, __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, 
	__CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgetc2_(__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_integer *ipiv, 
	 __CLPK_integer *jpiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgetf2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgetrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgetri_(__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_integer *ipiv, 
	 __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgetrs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggbak_(char *job, char *side, __CLPK_integer *n, __CLPK_integer *ilo, 
	__CLPK_integer *ihi, __CLPK_real *lscale, __CLPK_real *rscale, __CLPK_integer *m, __CLPK_real *v, 
	__CLPK_integer *ldv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggbal_(char *job, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *lscale, __CLPK_real 
	*rscale, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgges_(char *jobvsl, char *jobvsr, char *sort, __CLPK_L_fp 
	selctg, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, 
	__CLPK_integer *sdim, __CLPK_real *alphar, __CLPK_real *alphai, __CLPK_real *beta, __CLPK_real *vsl, 
	__CLPK_integer *ldvsl, __CLPK_real *vsr, __CLPK_integer *ldvsr, __CLPK_real *work, __CLPK_integer *lwork, 
	 __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggesx_(char *jobvsl, char *jobvsr, char *sort, __CLPK_L_fp 
	selctg, char *sense, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, 
	__CLPK_integer *ldb, __CLPK_integer *sdim, __CLPK_real *alphar, __CLPK_real *alphai, __CLPK_real *beta, 
	__CLPK_real *vsl, __CLPK_integer *ldvsl, __CLPK_real *vsr, __CLPK_integer *ldvsr, __CLPK_real *rconde, 
	__CLPK_real *rcondv, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *
	liwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggev_(char *jobvl, char *jobvr, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *alphar, __CLPK_real *alphai, __CLPK_real 
	*beta, __CLPK_real *vl, __CLPK_integer *ldvl, __CLPK_real *vr, __CLPK_integer *ldvr, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real 
	*alphar, __CLPK_real *alphai, __CLPK_real *beta, __CLPK_real *vl, __CLPK_integer *ldvl, __CLPK_real *vr, 
	__CLPK_integer *ldvr, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *lscale, __CLPK_real *rscale, 
	 __CLPK_real *abnrm, __CLPK_real *bbnrm, __CLPK_real *rconde, __CLPK_real *rcondv, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggglm_(__CLPK_integer *n, __CLPK_integer *m, __CLPK_integer *p, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *d__, __CLPK_real *x, __CLPK_real *y, 
	__CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgghrd_(char *compq, char *compz, __CLPK_integer *n, __CLPK_integer *
	ilo, __CLPK_integer *ihi, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real 
	*q, __CLPK_integer *ldq, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgglse_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *p, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *c__, __CLPK_real *d__, __CLPK_real *x, 
	__CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggqrf_(__CLPK_integer *n, __CLPK_integer *m, __CLPK_integer *p, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *taua, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *taub, __CLPK_real *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggrqf_(__CLPK_integer *m, __CLPK_integer *p, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *taua, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *taub, __CLPK_real *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggsvd_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_integer *p, __CLPK_integer *k, __CLPK_integer *l, __CLPK_real *a, __CLPK_integer *lda, 
	 __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *alpha, __CLPK_real *beta, __CLPK_real *u, __CLPK_integer *
	ldu, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sggsvp_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *p, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, 
	__CLPK_real *tola, __CLPK_real *tolb, __CLPK_integer *k, __CLPK_integer *l, __CLPK_real *u, __CLPK_integer *ldu, 
	 __CLPK_real *v, __CLPK_integer *ldv, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_integer *iwork, __CLPK_real *
	tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgsvj0_(char *jobv, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *d__, __CLPK_real *sva, __CLPK_integer *mv, __CLPK_real *v, __CLPK_integer *
	ldv, __CLPK_real *eps, __CLPK_real *sfmin, __CLPK_real *tol, __CLPK_integer *nsweep, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgsvj1_(char *jobv, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *n1, 
	__CLPK_real *a, __CLPK_integer *lda, __CLPK_real *d__, __CLPK_real *sva, __CLPK_integer *mv, __CLPK_real *v, 
	__CLPK_integer *ldv, __CLPK_real *eps, __CLPK_real *sfmin, __CLPK_real *tol, __CLPK_integer *nsweep, 
	__CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgtcon_(char *norm, __CLPK_integer *n, __CLPK_real *dl, __CLPK_real *d__, 
	__CLPK_real *du, __CLPK_real *du2, __CLPK_integer *ipiv, __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_real *
	work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgtrfs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *dl, 
	 __CLPK_real *d__, __CLPK_real *du, __CLPK_real *dlf, __CLPK_real *df, __CLPK_real *duf, __CLPK_real *du2, 
	__CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *
	ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgtsv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *dl, __CLPK_real *d__, 
	__CLPK_real *du, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgtsvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_real *dl, __CLPK_real *d__, __CLPK_real *du, __CLPK_real *dlf, __CLPK_real *df, __CLPK_real *duf, 
	__CLPK_real *du2, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *
	ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgttrf_(__CLPK_integer *n, __CLPK_real *dl, __CLPK_real *d__, __CLPK_real *du, __CLPK_real *
	du2, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgttrs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *dl, 
	 __CLPK_real *d__, __CLPK_real *du, __CLPK_real *du2, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sgtts2_(__CLPK_integer *itrans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real 
	*dl, __CLPK_real *d__, __CLPK_real *du, __CLPK_real *du2, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *
	ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int shgeqz_(char *job, char *compq, char *compz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *h__, __CLPK_integer *ldh, __CLPK_real *t, __CLPK_integer 
	*ldt, __CLPK_real *alphar, __CLPK_real *alphai, __CLPK_real *beta, __CLPK_real *q, __CLPK_integer *ldq, 
	__CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int shsein_(char *side, char *eigsrc, char *initv, __CLPK_logical *
	select, __CLPK_integer *n, __CLPK_real *h__, __CLPK_integer *ldh, __CLPK_real *wr, __CLPK_real *wi, __CLPK_real 
	*vl, __CLPK_integer *ldvl, __CLPK_real *vr, __CLPK_integer *ldvr, __CLPK_integer *mm, __CLPK_integer *m, 
	__CLPK_real *work, __CLPK_integer *ifaill, __CLPK_integer *ifailr, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int shseqr_(char *job, char *compz, __CLPK_integer *n, __CLPK_integer *ilo, 
	 __CLPK_integer *ihi, __CLPK_real *h__, __CLPK_integer *ldh, __CLPK_real *wr, __CLPK_real *wi, __CLPK_real *z__, 
	 __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_logical sisnan_(__CLPK_real *sin__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slabad_(__CLPK_real *small, __CLPK_real *large) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slabrd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *tauq, __CLPK_real *taup, __CLPK_real *x, 
	__CLPK_integer *ldx, __CLPK_real *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slacn2_(__CLPK_integer *n, __CLPK_real *v, __CLPK_real *x, __CLPK_integer *isgn, 
	__CLPK_real *est, __CLPK_integer *kase, __CLPK_integer *isave) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slacon_(__CLPK_integer *n, __CLPK_real *v, __CLPK_real *x, __CLPK_integer *isgn, 
	__CLPK_real *est, __CLPK_integer *kase) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slacpy_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sladiv_(__CLPK_real *a, __CLPK_real *b, __CLPK_real *c__, __CLPK_real *d__, __CLPK_real *p, 
	__CLPK_real *q) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slae2_(__CLPK_real *a, __CLPK_real *b, __CLPK_real *c__, __CLPK_real *rt1, __CLPK_real *rt2) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaebz_(__CLPK_integer *ijob, __CLPK_integer *nitmax, __CLPK_integer *n, 
	__CLPK_integer *mmax, __CLPK_integer *minp, __CLPK_integer *nbmin, __CLPK_real *abstol, __CLPK_real *
	reltol, __CLPK_real *pivmin, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *e2, __CLPK_integer *nval, 
	__CLPK_real *ab, __CLPK_real *c__, __CLPK_integer *mout, __CLPK_integer *nab, __CLPK_real *work, __CLPK_integer 
	*iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed0_(__CLPK_integer *icompq, __CLPK_integer *qsiz, __CLPK_integer *n, __CLPK_real 
	*d__, __CLPK_real *e, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *qstore, __CLPK_integer *ldqs, 
	__CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed1_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *q, __CLPK_integer *ldq, 
	__CLPK_integer *indxq, __CLPK_real *rho, __CLPK_integer *cutpnt, __CLPK_real *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed2_(__CLPK_integer *k, __CLPK_integer *n, __CLPK_integer *n1, __CLPK_real *d__, 
	__CLPK_real *q, __CLPK_integer *ldq, __CLPK_integer *indxq, __CLPK_real *rho, __CLPK_real *z__, __CLPK_real *
	dlamda, __CLPK_real *w, __CLPK_real *q2, __CLPK_integer *indx, __CLPK_integer *indxc, __CLPK_integer *
	indxp, __CLPK_integer *coltyp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed3_(__CLPK_integer *k, __CLPK_integer *n, __CLPK_integer *n1, __CLPK_real *d__, 
	__CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *rho, __CLPK_real *dlamda, __CLPK_real *q2, __CLPK_integer *
	indx, __CLPK_integer *ctot, __CLPK_real *w, __CLPK_real *s, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed4_(__CLPK_integer *n, __CLPK_integer *i__, __CLPK_real *d__, __CLPK_real *z__, 
	__CLPK_real *delta, __CLPK_real *rho, __CLPK_real *dlam, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed5_(__CLPK_integer *i__, __CLPK_real *d__, __CLPK_real *z__, __CLPK_real *delta, 
	__CLPK_real *rho, __CLPK_real *dlam) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed6_(__CLPK_integer *kniter, __CLPK_logical *orgati, __CLPK_real *rho, 
	__CLPK_real *d__, __CLPK_real *z__, __CLPK_real *finit, __CLPK_real *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed7_(__CLPK_integer *icompq, __CLPK_integer *n, __CLPK_integer *qsiz, 
	__CLPK_integer *tlvls, __CLPK_integer *curlvl, __CLPK_integer *curpbm, __CLPK_real *d__, __CLPK_real *q, 
	__CLPK_integer *ldq, __CLPK_integer *indxq, __CLPK_real *rho, __CLPK_integer *cutpnt, __CLPK_real *
	qstore, __CLPK_integer *qptr, __CLPK_integer *prmptr, __CLPK_integer *perm, __CLPK_integer *
	givptr, __CLPK_integer *givcol, __CLPK_real *givnum, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed8_(__CLPK_integer *icompq, __CLPK_integer *k, __CLPK_integer *n, __CLPK_integer 
	*qsiz, __CLPK_real *d__, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_integer *indxq, __CLPK_real *rho, 
	__CLPK_integer *cutpnt, __CLPK_real *z__, __CLPK_real *dlamda, __CLPK_real *q2, __CLPK_integer *ldq2, 
	__CLPK_real *w, __CLPK_integer *perm, __CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_real *
	givnum, __CLPK_integer *indxp, __CLPK_integer *indx, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaed9_(__CLPK_integer *k, __CLPK_integer *kstart, __CLPK_integer *kstop, 
	__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *rho, __CLPK_real *dlamda, 
	 __CLPK_real *w, __CLPK_real *s, __CLPK_integer *lds, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaeda_(__CLPK_integer *n, __CLPK_integer *tlvls, __CLPK_integer *curlvl, 
	__CLPK_integer *curpbm, __CLPK_integer *prmptr, __CLPK_integer *perm, __CLPK_integer *givptr, 
	__CLPK_integer *givcol, __CLPK_real *givnum, __CLPK_real *q, __CLPK_integer *qptr, __CLPK_real *z__, 
	__CLPK_real *ztemp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaein_(__CLPK_logical *rightv, __CLPK_logical *noinit, __CLPK_integer *n, 
	__CLPK_real *h__, __CLPK_integer *ldh, __CLPK_real *wr, __CLPK_real *wi, __CLPK_real *vr, __CLPK_real *vi, __CLPK_real 
	*b, __CLPK_integer *ldb, __CLPK_real *work, __CLPK_real *eps3, __CLPK_real *smlnum, __CLPK_real *bignum, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaev2_(__CLPK_real *a, __CLPK_real *b, __CLPK_real *c__, __CLPK_real *rt1, __CLPK_real *
	rt2, __CLPK_real *cs1, __CLPK_real *sn1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaexc_(__CLPK_logical *wantq, __CLPK_integer *n, __CLPK_real *t, __CLPK_integer *
	ldt, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_integer *j1, __CLPK_integer *n1, __CLPK_integer *n2, 
	__CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slag2_(__CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, 
	__CLPK_real *safmin, __CLPK_real *scale1, __CLPK_real *scale2, __CLPK_real *wr1, __CLPK_real *wr2, __CLPK_real *
	wi) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slag2d_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *sa, __CLPK_integer *ldsa, 
	__CLPK_doublereal *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slags2_(__CLPK_logical *upper, __CLPK_real *a1, __CLPK_real *a2, __CLPK_real *a3, 
	__CLPK_real *b1, __CLPK_real *b2, __CLPK_real *b3, __CLPK_real *csu, __CLPK_real *snu, __CLPK_real *csv, __CLPK_real *
	snv, __CLPK_real *csq, __CLPK_real *snq) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slagtf_(__CLPK_integer *n, __CLPK_real *a, __CLPK_real *lambda, __CLPK_real *b, __CLPK_real 
	*c__, __CLPK_real *tol, __CLPK_real *d__, __CLPK_integer *in, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slagtm_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *
	alpha, __CLPK_real *dl, __CLPK_real *d__, __CLPK_real *du, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *
	beta, __CLPK_real *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slagts_(__CLPK_integer *job, __CLPK_integer *n, __CLPK_real *a, __CLPK_real *b, __CLPK_real 
	*c__, __CLPK_real *d__, __CLPK_integer *in, __CLPK_real *y, __CLPK_real *tol, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slagv2_(__CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, 
	__CLPK_real *alphar, __CLPK_real *alphai, __CLPK_real *beta, __CLPK_real *csl, __CLPK_real *snl, __CLPK_real *
	csr, __CLPK_real *snr) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slahqr_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *h__, __CLPK_integer *ldh, __CLPK_real *wr, __CLPK_real *
	wi, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slahr2_(__CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *nb, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *t, __CLPK_integer *ldt, __CLPK_real *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slahrd_(__CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *nb, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *t, __CLPK_integer *ldt, __CLPK_real *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaic1_(__CLPK_integer *job, __CLPK_integer *j, __CLPK_real *x, __CLPK_real *sest, 
	__CLPK_real *w, __CLPK_real *gamma, __CLPK_real *sestpr, __CLPK_real *s, __CLPK_real *c__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_logical slaisnan_(__CLPK_real *sin1, __CLPK_real *sin2) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaln2_(__CLPK_logical *ltrans, __CLPK_integer *na, __CLPK_integer *nw, __CLPK_real *
	smin, __CLPK_real *ca, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *d1, __CLPK_real *d2, __CLPK_real *b, 
	__CLPK_integer *ldb, __CLPK_real *wr, __CLPK_real *wi, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *scale, 
	__CLPK_real *xnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slals0_(__CLPK_integer *icompq, __CLPK_integer *nl, __CLPK_integer *nr, 
	__CLPK_integer *sqre, __CLPK_integer *nrhs, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *bx, 
	__CLPK_integer *ldbx, __CLPK_integer *perm, __CLPK_integer *givptr, __CLPK_integer *givcol, 
	__CLPK_integer *ldgcol, __CLPK_real *givnum, __CLPK_integer *ldgnum, __CLPK_real *poles, __CLPK_real *
	difl, __CLPK_real *difr, __CLPK_real *z__, __CLPK_integer *k, __CLPK_real *c__, __CLPK_real *s, __CLPK_real *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slalsa_(__CLPK_integer *icompq, __CLPK_integer *smlsiz, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *bx, __CLPK_integer *ldbx, __CLPK_real *
	u, __CLPK_integer *ldu, __CLPK_real *vt, __CLPK_integer *k, __CLPK_real *difl, __CLPK_real *difr, __CLPK_real *
	z__, __CLPK_real *poles, __CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_integer *ldgcol, 
	__CLPK_integer *perm, __CLPK_real *givnum, __CLPK_real *c__, __CLPK_real *s, __CLPK_real *work, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slalsd_(char *uplo, __CLPK_integer *smlsiz, __CLPK_integer *n, __CLPK_integer 
	*nrhs, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *rcond, 
	__CLPK_integer *rank, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slamrg_(__CLPK_integer *n1, __CLPK_integer *n2, __CLPK_real *a, __CLPK_integer *
	strd1, __CLPK_integer *strd2, __CLPK_integer *index) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer slaneg_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *lld, __CLPK_real *sigma, __CLPK_real *pivmin, 
	__CLPK_integer *r__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slangb_(char *norm, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_real *ab, 
	 __CLPK_integer *ldab, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slange_(char *norm, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slangt_(char *norm, __CLPK_integer *n, __CLPK_real *dl, __CLPK_real *d__, __CLPK_real *du) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slanhs_(char *norm, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slansb_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *ab, 
	__CLPK_integer *ldab, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slansf_(char *norm, char *transr, char *uplo, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slansp_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slanst_(char *norm, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slansy_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slantb_(char *norm, char *uplo, char *diag, __CLPK_integer *n, __CLPK_integer *k, 
	 __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slantp_(char *norm, char *uplo, char *diag, __CLPK_integer *n, __CLPK_real *ap, 
	__CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slantr_(char *norm, char *uplo, char *diag, __CLPK_integer *m, __CLPK_integer *n, 
	 __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slanv2_(__CLPK_real *a, __CLPK_real *b, __CLPK_real *c__, __CLPK_real *d__, __CLPK_real *
	rt1r, __CLPK_real *rt1i, __CLPK_real *rt2r, __CLPK_real *rt2i, __CLPK_real *cs, __CLPK_real *sn) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slapll_(__CLPK_integer *n, __CLPK_real *x, __CLPK_integer *incx, __CLPK_real *y, 
	__CLPK_integer *incy, __CLPK_real *ssmin) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slapmt_(__CLPK_logical *forwrd, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *x, 
	 __CLPK_integer *ldx, __CLPK_integer *k) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slapy2_(__CLPK_real *x, __CLPK_real *y) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slapy3_(__CLPK_real *x, __CLPK_real *y, __CLPK_real *z__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqgb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real *
	colcnd, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqge_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *r__, __CLPK_real *c__, __CLPK_real *rowcnd, __CLPK_real *colcnd, __CLPK_real *amax, char *
	equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqp2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *offset, __CLPK_real *a, 
	 __CLPK_integer *lda, __CLPK_integer *jpvt, __CLPK_real *tau, __CLPK_real *vn1, __CLPK_real *vn2, __CLPK_real *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqps_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *offset, __CLPK_integer 
	*nb, __CLPK_integer *kb, __CLPK_real *a, __CLPK_integer *lda, __CLPK_integer *jpvt, __CLPK_real *tau, 
	__CLPK_real *vn1, __CLPK_real *vn2, __CLPK_real *auxv, __CLPK_real *f, __CLPK_integer *ldf) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqr0_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *h__, __CLPK_integer *ldh, __CLPK_real *wr, __CLPK_real *
	wi, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, 
	 __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqr1_(__CLPK_integer *n, __CLPK_real *h__, __CLPK_integer *ldh, __CLPK_real *sr1, 
	__CLPK_real *si1, __CLPK_real *sr2, __CLPK_real *si2, __CLPK_real *v) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqr2_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nw, __CLPK_real *h__, __CLPK_integer *ldh, 
	__CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *ns, 
	__CLPK_integer *nd, __CLPK_real *sr, __CLPK_real *si, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_integer *nh, 
	__CLPK_real *t, __CLPK_integer *ldt, __CLPK_integer *nv, __CLPK_real *wv, __CLPK_integer *ldwv, __CLPK_real *
	work, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqr3_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nw, __CLPK_real *h__, __CLPK_integer *ldh, 
	__CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *ns, 
	__CLPK_integer *nd, __CLPK_real *sr, __CLPK_real *si, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_integer *nh, 
	__CLPK_real *t, __CLPK_integer *ldt, __CLPK_integer *nv, __CLPK_real *wv, __CLPK_integer *ldwv, __CLPK_real *
	work, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqr4_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *h__, __CLPK_integer *ldh, __CLPK_real *wr, __CLPK_real *
	wi, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, 
	 __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqr5_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *kacc22, 
	__CLPK_integer *n, __CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nshfts, __CLPK_real *sr, 
	__CLPK_real *si, __CLPK_real *h__, __CLPK_integer *ldh, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_real 
	*z__, __CLPK_integer *ldz, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_real *u, __CLPK_integer *ldu, 
	__CLPK_integer *nv, __CLPK_real *wv, __CLPK_integer *ldwv, __CLPK_integer *nh, __CLPK_real *wh, __CLPK_integer *
	ldwh) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqsb_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_real *ab, 
	__CLPK_integer *ldab, __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqsp_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *s, __CLPK_real *
	scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqsy_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaqtr_(__CLPK_logical *ltran, __CLPK_logical *l__CLPK_real, __CLPK_integer *n, __CLPK_real 
	*t, __CLPK_integer *ldt, __CLPK_real *b, __CLPK_real *w, __CLPK_real *scale, __CLPK_real *x, __CLPK_real *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slar1v_(__CLPK_integer *n, __CLPK_integer *b1, __CLPK_integer *bn, __CLPK_real *
	lambda, __CLPK_real *d__, __CLPK_real *l, __CLPK_real *ld, __CLPK_real *lld, __CLPK_real *pivmin, __CLPK_real *
	gaptol, __CLPK_real *z__, __CLPK_logical *wantnc, __CLPK_integer *negcnt, __CLPK_real *ztz, __CLPK_real *
	mingma, __CLPK_integer *r__, __CLPK_integer *isuppz, __CLPK_real *nrminv, __CLPK_real *resid, 
	__CLPK_real *rqcorr, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slar2v_(__CLPK_integer *n, __CLPK_real *x, __CLPK_real *y, __CLPK_real *z__, __CLPK_integer 
	*incx, __CLPK_real *c__, __CLPK_real *s, __CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarf_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *v, 
	__CLPK_integer *incv, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarfb_(char *side, char *trans, char *direct, char *
	storev, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *v, __CLPK_integer *ldv, 
	__CLPK_real *t, __CLPK_integer *ldt, __CLPK_real *c__, __CLPK_integer *ldc, __CLPK_real *work, __CLPK_integer *
	ldwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarfg_(__CLPK_integer *n, __CLPK_real *alpha, __CLPK_real *x, __CLPK_integer *incx, 
	__CLPK_real *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarfp_(__CLPK_integer *n, __CLPK_real *alpha, __CLPK_real *x, __CLPK_integer *incx, 
	__CLPK_real *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarft_(char *direct, char *storev, __CLPK_integer *n, __CLPK_integer *
	k, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_real *tau, __CLPK_real *t, __CLPK_integer *ldt) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarfx_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *v, 
	__CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slargv_(__CLPK_integer *n, __CLPK_real *x, __CLPK_integer *incx, __CLPK_real *y, 
	__CLPK_integer *incy, __CLPK_real *c__, __CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarnv_(__CLPK_integer *idist, __CLPK_integer *iseed, __CLPK_integer *n, __CLPK_real 
	*x) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarra_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *e2, __CLPK_real *
	spltol, __CLPK_real *tnrm, __CLPK_integer *nsplit, __CLPK_integer *isplit, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarrb_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *lld, __CLPK_integer *
	ifirst, __CLPK_integer *ilast, __CLPK_real *rtol1, __CLPK_real *rtol2, __CLPK_integer *offset, 
	__CLPK_real *w, __CLPK_real *wgap, __CLPK_real *werr, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_real *
	pivmin, __CLPK_real *spdiam, __CLPK_integer *twist, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarrc_(char *jobt, __CLPK_integer *n, __CLPK_real *vl, __CLPK_real *vu, __CLPK_real 
	*d__, __CLPK_real *e, __CLPK_real *pivmin, __CLPK_integer *eigcnt, __CLPK_integer *lcnt, __CLPK_integer *
	rcnt, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarrd_(char *range, char *order, __CLPK_integer *n, __CLPK_real *vl, 
	__CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *gers, __CLPK_real *reltol, __CLPK_real *
	d__, __CLPK_real *e, __CLPK_real *e2, __CLPK_real *pivmin, __CLPK_integer *nsplit, __CLPK_integer *
	isplit, __CLPK_integer *m, __CLPK_real *w, __CLPK_real *werr, __CLPK_real *wl, __CLPK_real *wu, __CLPK_integer *
	iblock, __CLPK_integer *indexw, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarre_(char *range, __CLPK_integer *n, __CLPK_real *vl, __CLPK_real *vu, 
	__CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *e2, __CLPK_real *rtol1, 
	__CLPK_real *rtol2, __CLPK_real *spltol, __CLPK_integer *nsplit, __CLPK_integer *isplit, __CLPK_integer *
	m, __CLPK_real *w, __CLPK_real *werr, __CLPK_real *wgap, __CLPK_integer *iblock, __CLPK_integer *indexw, 
	__CLPK_real *gers, __CLPK_real *pivmin, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarrf_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *l, __CLPK_real *ld, 
	__CLPK_integer *clstrt, __CLPK_integer *clend, __CLPK_real *w, __CLPK_real *wgap, __CLPK_real *werr, 
	__CLPK_real *spdiam, __CLPK_real *clgapl, __CLPK_real *clgapr, __CLPK_real *pivmin, __CLPK_real *sigma, 
	__CLPK_real *dplus, __CLPK_real *lplus, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarrj_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e2, __CLPK_integer *ifirst, 
	 __CLPK_integer *ilast, __CLPK_real *rtol, __CLPK_integer *offset, __CLPK_real *w, __CLPK_real *werr, 
	__CLPK_real *work, __CLPK_integer *iwork, __CLPK_real *pivmin, __CLPK_real *spdiam, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarrk_(__CLPK_integer *n, __CLPK_integer *iw, __CLPK_real *gl, __CLPK_real *gu, 
	__CLPK_real *d__, __CLPK_real *e2, __CLPK_real *pivmin, __CLPK_real *reltol, __CLPK_real *w, __CLPK_real *werr, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarrr_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarrv_(__CLPK_integer *n, __CLPK_real *vl, __CLPK_real *vu, __CLPK_real *d__, __CLPK_real *
	l, __CLPK_real *pivmin, __CLPK_integer *isplit, __CLPK_integer *m, __CLPK_integer *dol, __CLPK_integer *
	dou, __CLPK_real *minrgp, __CLPK_real *rtol1, __CLPK_real *rtol2, __CLPK_real *w, __CLPK_real *werr, 
	__CLPK_real *wgap, __CLPK_integer *iblock, __CLPK_integer *indexw, __CLPK_real *gers, __CLPK_real *z__, 
	__CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarscl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *x, 
	__CLPK_integer *ldx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slartg_(__CLPK_real *f, __CLPK_real *g, __CLPK_real *cs, __CLPK_real *sn, __CLPK_real *r__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slartv_(__CLPK_integer *n, __CLPK_real *x, __CLPK_integer *incx, __CLPK_real *y, 
	__CLPK_integer *incy, __CLPK_real *c__, __CLPK_real *s, __CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaruv_(__CLPK_integer *iseed, __CLPK_integer *n, __CLPK_real *x) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarz_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *l, 
	__CLPK_real *v, __CLPK_integer *incv, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, __CLPK_real *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarzb_(char *side, char *trans, char *direct, char *
	storev, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *l, __CLPK_real *v, 
	__CLPK_integer *ldv, __CLPK_real *t, __CLPK_integer *ldt, __CLPK_real *c__, __CLPK_integer *ldc, __CLPK_real *
	work, __CLPK_integer *ldwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slarzt_(char *direct, char *storev, __CLPK_integer *n, __CLPK_integer *
	k, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_real *tau, __CLPK_real *t, __CLPK_integer *ldt) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slas2_(__CLPK_real *f, __CLPK_real *g, __CLPK_real *h__, __CLPK_real *ssmin, __CLPK_real *
	ssmax) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slascl_(char *type__, __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_real *
	cfrom, __CLPK_real *cto, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slascl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *x, 
	__CLPK_integer *ldx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd0_(__CLPK_integer *n, __CLPK_integer *sqre, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *vt, __CLPK_integer *ldvt, __CLPK_integer *smlsiz, 
	__CLPK_integer *iwork, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd1_(__CLPK_integer *nl, __CLPK_integer *nr, __CLPK_integer *sqre, __CLPK_real *
	d__, __CLPK_real *alpha, __CLPK_real *beta, __CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *vt, 
	__CLPK_integer *ldvt, __CLPK_integer *idxq, __CLPK_integer *iwork, __CLPK_real *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd2_(__CLPK_integer *nl, __CLPK_integer *nr, __CLPK_integer *sqre, __CLPK_integer 
	*k, __CLPK_real *d__, __CLPK_real *z__, __CLPK_real *alpha, __CLPK_real *beta, __CLPK_real *u, __CLPK_integer *
	ldu, __CLPK_real *vt, __CLPK_integer *ldvt, __CLPK_real *dsigma, __CLPK_real *u2, __CLPK_integer *ldu2, 
	__CLPK_real *vt2, __CLPK_integer *ldvt2, __CLPK_integer *idxp, __CLPK_integer *idx, __CLPK_integer *idxc, 
	 __CLPK_integer *idxq, __CLPK_integer *coltyp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd3_(__CLPK_integer *nl, __CLPK_integer *nr, __CLPK_integer *sqre, __CLPK_integer 
	*k, __CLPK_real *d__, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *dsigma, __CLPK_real *u, __CLPK_integer *
	ldu, __CLPK_real *u2, __CLPK_integer *ldu2, __CLPK_real *vt, __CLPK_integer *ldvt, __CLPK_real *vt2, 
	__CLPK_integer *ldvt2, __CLPK_integer *idxc, __CLPK_integer *ctot, __CLPK_real *z__, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd4_(__CLPK_integer *n, __CLPK_integer *i__, __CLPK_real *d__, __CLPK_real *z__, 
	__CLPK_real *delta, __CLPK_real *rho, __CLPK_real *sigma, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd5_(__CLPK_integer *i__, __CLPK_real *d__, __CLPK_real *z__, __CLPK_real *delta, 
	__CLPK_real *rho, __CLPK_real *dsigma, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd6_(__CLPK_integer *icompq, __CLPK_integer *nl, __CLPK_integer *nr, 
	__CLPK_integer *sqre, __CLPK_real *d__, __CLPK_real *vf, __CLPK_real *vl, __CLPK_real *alpha, __CLPK_real *beta, 
	 __CLPK_integer *idxq, __CLPK_integer *perm, __CLPK_integer *givptr, __CLPK_integer *givcol, 
	__CLPK_integer *ldgcol, __CLPK_real *givnum, __CLPK_integer *ldgnum, __CLPK_real *poles, __CLPK_real *
	difl, __CLPK_real *difr, __CLPK_real *z__, __CLPK_integer *k, __CLPK_real *c__, __CLPK_real *s, __CLPK_real *
	work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd7_(__CLPK_integer *icompq, __CLPK_integer *nl, __CLPK_integer *nr, 
	__CLPK_integer *sqre, __CLPK_integer *k, __CLPK_real *d__, __CLPK_real *z__, __CLPK_real *zw, __CLPK_real *vf, 
	__CLPK_real *vfw, __CLPK_real *vl, __CLPK_real *vlw, __CLPK_real *alpha, __CLPK_real *beta, __CLPK_real *dsigma, 
	 __CLPK_integer *idx, __CLPK_integer *idxp, __CLPK_integer *idxq, __CLPK_integer *perm, __CLPK_integer *
	givptr, __CLPK_integer *givcol, __CLPK_integer *ldgcol, __CLPK_real *givnum, __CLPK_integer *
	ldgnum, __CLPK_real *c__, __CLPK_real *s, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasd8_(__CLPK_integer *icompq, __CLPK_integer *k, __CLPK_real *d__, __CLPK_real *
	z__, __CLPK_real *vf, __CLPK_real *vl, __CLPK_real *difl, __CLPK_real *difr, __CLPK_integer *lddifr, 
	__CLPK_real *dsigma, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasda_(__CLPK_integer *icompq, __CLPK_integer *smlsiz, __CLPK_integer *n, 
	__CLPK_integer *sqre, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *vt, 
	__CLPK_integer *k, __CLPK_real *difl, __CLPK_real *difr, __CLPK_real *z__, __CLPK_real *poles, __CLPK_integer *
	givptr, __CLPK_integer *givcol, __CLPK_integer *ldgcol, __CLPK_integer *perm, __CLPK_real *givnum, 
	 __CLPK_real *c__, __CLPK_real *s, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasdq_(char *uplo, __CLPK_integer *sqre, __CLPK_integer *n, __CLPK_integer *
	ncvt, __CLPK_integer *nru, __CLPK_integer *ncc, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *vt, 
	__CLPK_integer *ldvt, __CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *c__, __CLPK_integer *ldc, __CLPK_real *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasdt_(__CLPK_integer *n, __CLPK_integer *lvl, __CLPK_integer *nd, __CLPK_integer *
	inode, __CLPK_integer *ndiml, __CLPK_integer *ndimr, __CLPK_integer *msub) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaset_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *alpha, 
	__CLPK_real *beta, __CLPK_real *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasq1_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasq2_(__CLPK_integer *n, __CLPK_real *z__, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasq3_(__CLPK_integer *i0, __CLPK_integer *n0, __CLPK_real *z__, __CLPK_integer *pp, 
	 __CLPK_real *dmin__, __CLPK_real *sigma, __CLPK_real *desig, __CLPK_real *qmax, __CLPK_integer *nfail, 
	__CLPK_integer *iter, __CLPK_integer *ndiv, __CLPK_logical *ieee, __CLPK_integer *ttype, __CLPK_real *
	dmin1, __CLPK_real *dmin2, __CLPK_real *dn, __CLPK_real *dn1, __CLPK_real *dn2, __CLPK_real *g, __CLPK_real *
	tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasq4_(__CLPK_integer *i0, __CLPK_integer *n0, __CLPK_real *z__, __CLPK_integer *pp, 
	 __CLPK_integer *n0in, __CLPK_real *dmin__, __CLPK_real *dmin1, __CLPK_real *dmin2, __CLPK_real *dn, 
	__CLPK_real *dn1, __CLPK_real *dn2, __CLPK_real *tau, __CLPK_integer *ttype, __CLPK_real *g) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasq5_(__CLPK_integer *i0, __CLPK_integer *n0, __CLPK_real *z__, __CLPK_integer *pp, 
	 __CLPK_real *tau, __CLPK_real *dmin__, __CLPK_real *dmin1, __CLPK_real *dmin2, __CLPK_real *dn, __CLPK_real *
	dnm1, __CLPK_real *dnm2, __CLPK_logical *ieee) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasq6_(__CLPK_integer *i0, __CLPK_integer *n0, __CLPK_real *z__, __CLPK_integer *pp, 
	 __CLPK_real *dmin__, __CLPK_real *dmin1, __CLPK_real *dmin2, __CLPK_real *dn, __CLPK_real *dnm1, __CLPK_real *
	dnm2) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasr_(char *side, char *pivot, char *direct, __CLPK_integer *m, 
	 __CLPK_integer *n, __CLPK_real *c__, __CLPK_real *s, __CLPK_real *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasrt_(char *id, __CLPK_integer *n, __CLPK_real *d__, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slassq_(__CLPK_integer *n, __CLPK_real *x, __CLPK_integer *incx, __CLPK_real *scale, 
	__CLPK_real *sumsq) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasv2_(__CLPK_real *f, __CLPK_real *g, __CLPK_real *h__, __CLPK_real *ssmin, __CLPK_real *
	ssmax, __CLPK_real *snr, __CLPK_real *csr, __CLPK_real *snl, __CLPK_real *csl) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slaswp_(__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_integer *k1, 
	__CLPK_integer *k2, __CLPK_integer *ipiv, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasy2_(__CLPK_logical *ltranl, __CLPK_logical *ltranr, __CLPK_integer *isgn, 
	__CLPK_integer *n1, __CLPK_integer *n2, __CLPK_real *tl, __CLPK_integer *ldtl, __CLPK_real *tr, __CLPK_integer *
	ldtr, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *scale, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real 
	*xnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slasyf_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_integer *kb, 
	 __CLPK_real *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_real *w, __CLPK_integer *ldw, __CLPK_integer 
	*info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slatbs_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *x, 
	__CLPK_real *scale, __CLPK_real *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slatdf_(__CLPK_integer *ijob, __CLPK_integer *n, __CLPK_real *z__, __CLPK_integer *
	ldz, __CLPK_real *rhs, __CLPK_real *rdsum, __CLPK_real *rdscal, __CLPK_integer *ipiv, __CLPK_integer *
	jpiv) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slatps_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *x, __CLPK_real *scale, __CLPK_real *cnorm, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slatrd_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *e, __CLPK_real *tau, __CLPK_real *w, __CLPK_integer *ldw) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slatrs_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *x, __CLPK_real *scale, __CLPK_real 
	*cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slatrz_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *l, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slatzm_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *v, 
	__CLPK_integer *incv, __CLPK_real *tau, __CLPK_real *c1, __CLPK_real *c2, __CLPK_integer *ldc, __CLPK_real *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slauu2_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slauum_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sopgtr_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *tau, 
	__CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sopmtr_(char *side, char *uplo, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_real *ap, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, __CLPK_real *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorg2l_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorg2r_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorgbr_(char *vect, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer 
	*info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorghr_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorgl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorglq_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorgql_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorgqr_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorgr2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorgrq_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorgtr_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorm2l_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorm2r_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormbr_(char *vect, char *side, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, 
	__CLPK_integer *ldc, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormhr_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *
	c__, __CLPK_integer *ldc, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sorml2_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormlq_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormql_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormqr_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormr2_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormr3_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_integer *l, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, 
	__CLPK_integer *ldc, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormrq_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormrz_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_integer *l, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, 
	__CLPK_integer *ldc, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sormtr_(char *side, char *uplo, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *tau, __CLPK_real *c__, __CLPK_integer *ldc, 
	 __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbcon_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_real *ab, 
	__CLPK_integer *ldab, __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbequ_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_real *ab, 
	__CLPK_integer *ldab, __CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *afb, __CLPK_integer *ldafb, __CLPK_real *b, 
	__CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *
	work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbstf_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_real *ab, 
	__CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_integer *nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *afb, __CLPK_integer *ldafb, 
	char *equed, __CLPK_real *s, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, 
	__CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbtf2_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_real *ab, 
	__CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbtrf_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_real *ab, 
	__CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spbtrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spftrf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spftri_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spftrs_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_real *a, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spocon_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *anorm, __CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spoequ_(__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *s, __CLPK_real 
	*scond, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spoequb_(__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *s, 
	__CLPK_real *scond, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sporfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *af, __CLPK_integer *ldaf, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, 
	 __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sposv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sposvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *af, __CLPK_integer *ldaf, char *equed, 
	__CLPK_real *s, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *rcond, 
	__CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spotf2_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spotrf_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spotri_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spotrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sppcon_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *anorm, 
	__CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sppequ_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *s, __CLPK_real *
	scond, __CLPK_real *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *ap, 
	__CLPK_real *afp, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *ferr, 
	__CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sppsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *ap, 
	__CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sppsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_real *ap, __CLPK_real *afp, char *equed, __CLPK_real *s, __CLPK_real *b, __CLPK_integer *
	ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real 
	*work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spptrf_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spptri_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *ap, 
	__CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spstf2_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *piv, __CLPK_integer *rank, __CLPK_real *tol, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spstrf_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *piv, __CLPK_integer *rank, __CLPK_real *tol, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sptcon_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *anorm, 
	__CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spteqr_(char *compz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sptrfs_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_real *df, __CLPK_real *ef, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, 
	__CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sptsv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sptsvx_(char *fact, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, 
	 __CLPK_real *e, __CLPK_real *df, __CLPK_real *ef, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer 
	*ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spttrf_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int spttrs_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sptts2_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_real *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int srscl_(__CLPK_integer *n, __CLPK_real *sa, __CLPK_real *sx, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssbev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssbevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, 
	 __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssbevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *vl, 
	 __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *
	w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *
	ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssbgst_(char *vect, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *bb, __CLPK_integer *ldbb, __CLPK_real *
	x, __CLPK_integer *ldx, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssbgv_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *bb, __CLPK_integer *ldbb, __CLPK_real *
	w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssbgvd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *bb, __CLPK_integer *ldbb, __CLPK_real *
	w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *
	iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssbgvx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_integer *ka, __CLPK_integer *kb, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *bb, __CLPK_integer *
	ldbb, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer 
	*iu, __CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real 
	*work, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssbtrd_(char *vect, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *q, __CLPK_integer *ldq, 
	__CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssfrk_(char *transr, char *uplo, char *trans, __CLPK_integer *n, 
	 __CLPK_integer *k, __CLPK_real *alpha, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *beta, __CLPK_real *
	c__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspcon_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_integer *ipiv, 
	__CLPK_real *anorm, __CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_real *ap, 
	__CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_real *ap, 
	__CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer 
	*iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_real *ap, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, 
	__CLPK_integer *m, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *
	iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspgst_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, __CLPK_real *ap, 
	 __CLPK_real *bp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspgv_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_real *ap, __CLPK_real *bp, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspgvd_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_real *ap, __CLPK_real *bp, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspgvx_(__CLPK_integer *itype, char *jobz, char *range, char *
	uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *bp, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, 
	 __CLPK_integer *iu, __CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *
	ldz, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *ap, 
	__CLPK_real *afp, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *
	ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *ap, 
	__CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sspsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_real *ap, __CLPK_real *afp, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real 
	*x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssptrd_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_real *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssptrf_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_integer *ipiv, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssptri_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_integer *ipiv, 
	__CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *ap, 
	__CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstebz_(char *range, char *order, __CLPK_integer *n, __CLPK_real *vl, 
	__CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_integer *m, __CLPK_integer *nsplit, __CLPK_real *w, __CLPK_integer *iblock, __CLPK_integer *
	isplit, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstedc_(char *compz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstegr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, 
	__CLPK_integer *m, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_real *
	work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstein_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_integer *m, __CLPK_real 
	*w, __CLPK_integer *iblock, __CLPK_integer *isplit, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *
	work, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstemr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_integer *m, 
	__CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *nzc, __CLPK_integer *isuppz, 
	__CLPK_logical *tryrac, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *
	liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssteqr_(char *compz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, 
	__CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssterf_(__CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstev_(char *jobz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_real *
	z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstevd_(char *jobz, __CLPK_integer *n, __CLPK_real *d__, __CLPK_real *e, __CLPK_real 
	*z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstevr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, 
	__CLPK_integer *m, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_real *
	work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int sstevx_(char *jobz, char *range, __CLPK_integer *n, __CLPK_real *d__, 
	__CLPK_real *e, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, 
	__CLPK_integer *m, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *
	iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssycon_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_real *anorm, __CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssyequb_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *s, __CLPK_real *scond, __CLPK_real *amax, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssyev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *w, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssyevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *w, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssyevr_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_real *a, __CLPK_integer *lda, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, 
	__CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *
	isuppz, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssyevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_real *a, __CLPK_integer *lda, __CLPK_real *vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, 
	__CLPK_real *abstol, __CLPK_integer *m, __CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *
	work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssygs2_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssygst_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssygv_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *w, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssygvd_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *w, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssygvx_(__CLPK_integer *itype, char *jobz, char *range, char *
	uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *
	vl, __CLPK_real *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_real *abstol, __CLPK_integer *m, 
	__CLPK_real *w, __CLPK_real *z__, __CLPK_integer *ldz, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer 
	*iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssyrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *af, __CLPK_integer *ldaf, __CLPK_integer *ipiv, __CLPK_real *b, 
	__CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *
	work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssysv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssysvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *af, __CLPK_integer *ldaf, __CLPK_integer *ipiv, 
	__CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *rcond, __CLPK_real *ferr, 
	 __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssytd2_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *d__, __CLPK_real *e, __CLPK_real *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssytf2_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssytrd_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *d__, __CLPK_real *e, __CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssytrf_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssytri_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ssytrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stbcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *rcond, __CLPK_real *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stbrfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_integer *nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *b, __CLPK_integer 
	*ldb, __CLPK_real *x, __CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stbtrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_integer *nrhs, __CLPK_real *ab, __CLPK_integer *ldab, __CLPK_real *b, __CLPK_integer 
	*ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stfsm_(char *transr, char *side, char *uplo, char *trans, 
	 char *diag, __CLPK_integer *m, __CLPK_integer *n, __CLPK_real *alpha, __CLPK_real *a, __CLPK_real *b, 
	__CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stftri_(char *transr, char *uplo, char *diag, __CLPK_integer *n, 
	 __CLPK_real *a, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stfttp_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_real *arf, 
	__CLPK_real *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stfttr_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_real *arf, 
	__CLPK_real *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stgevc_(char *side, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_real *s, __CLPK_integer *lds, __CLPK_real *p, __CLPK_integer *ldp, __CLPK_real *vl, 
	__CLPK_integer *ldvl, __CLPK_real *vr, __CLPK_integer *ldvr, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_real 
	*work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stgex2_(__CLPK_logical *wantq, __CLPK_logical *wantz, __CLPK_integer *n, __CLPK_real 
	*a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *
	z__, __CLPK_integer *ldz, __CLPK_integer *j1, __CLPK_integer *n1, __CLPK_integer *n2, __CLPK_real *work, 
	__CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stgexc_(__CLPK_logical *wantq, __CLPK_logical *wantz, __CLPK_integer *n, __CLPK_real 
	*a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *
	z__, __CLPK_integer *ldz, __CLPK_integer *ifst, __CLPK_integer *ilst, __CLPK_real *work, __CLPK_integer *
	lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stgsen_(__CLPK_integer *ijob, __CLPK_logical *wantq, __CLPK_logical *wantz, 
	__CLPK_logical *select, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *
	ldb, __CLPK_real *alphar, __CLPK_real *alphai, __CLPK_real *beta, __CLPK_real *q, __CLPK_integer *ldq, 
	__CLPK_real *z__, __CLPK_integer *ldz, __CLPK_integer *m, __CLPK_real *pl, __CLPK_real *pr, __CLPK_real *dif, 
	__CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stgsja_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *p, __CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *l, __CLPK_real *a, __CLPK_integer *lda, 
	 __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *tola, __CLPK_real *tolb, __CLPK_real *alpha, __CLPK_real *
	beta, __CLPK_real *u, __CLPK_integer *ldu, __CLPK_real *v, __CLPK_integer *ldv, __CLPK_real *q, __CLPK_integer *
	ldq, __CLPK_real *work, __CLPK_integer *ncycle, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stgsna_(char *job, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *vl, 
	__CLPK_integer *ldvl, __CLPK_real *vr, __CLPK_integer *ldvr, __CLPK_real *s, __CLPK_real *dif, __CLPK_integer *
	mm, __CLPK_integer *m, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stgsy2_(char *trans, __CLPK_integer *ijob, __CLPK_integer *m, __CLPK_integer *
	n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *c__, __CLPK_integer *
	ldc, __CLPK_real *d__, __CLPK_integer *ldd, __CLPK_real *e, __CLPK_integer *lde, __CLPK_real *f, __CLPK_integer 
	*ldf, __CLPK_real *scale, __CLPK_real *rdsum, __CLPK_real *rdscal, __CLPK_integer *iwork, __CLPK_integer 
	*pq, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stgsyl_(char *trans, __CLPK_integer *ijob, __CLPK_integer *m, __CLPK_integer *
	n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *c__, __CLPK_integer *
	ldc, __CLPK_real *d__, __CLPK_integer *ldd, __CLPK_real *e, __CLPK_integer *lde, __CLPK_real *f, __CLPK_integer 
	*ldf, __CLPK_real *scale, __CLPK_real *dif, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *
	iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stpcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_real *ap, __CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stprfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_real *ap, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, __CLPK_integer *ldx, 
	 __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stptri_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_real *ap, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stptrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_real *ap, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stpttf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_real *ap, 
	__CLPK_real *arf, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stpttr_(char *uplo, __CLPK_integer *n, __CLPK_real *ap, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_real *a, __CLPK_integer *lda, __CLPK_real *rcond, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strevc_(char *side, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_real *t, __CLPK_integer *ldt, __CLPK_real *vl, __CLPK_integer *ldvl, __CLPK_real *vr, 
	__CLPK_integer *ldvr, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_real *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strexc_(char *compq, __CLPK_integer *n, __CLPK_real *t, __CLPK_integer *ldt, 
	__CLPK_real *q, __CLPK_integer *ldq, __CLPK_integer *ifst, __CLPK_integer *ilst, __CLPK_real *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strrfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *x, 
	__CLPK_integer *ldx, __CLPK_real *ferr, __CLPK_real *berr, __CLPK_real *work, __CLPK_integer *iwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strsen_(char *job, char *compq, __CLPK_logical *select, __CLPK_integer 
	*n, __CLPK_real *t, __CLPK_integer *ldt, __CLPK_real *q, __CLPK_integer *ldq, __CLPK_real *wr, __CLPK_real *wi, 
	__CLPK_integer *m, __CLPK_real *s, __CLPK_real *sep, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *
	iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strsna_(char *job, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_real *t, __CLPK_integer *ldt, __CLPK_real *vl, __CLPK_integer *ldvl, __CLPK_real *vr, 
	__CLPK_integer *ldvr, __CLPK_real *s, __CLPK_real *sep, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_real *
	work, __CLPK_integer *ldwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strsyl_(char *trana, char *tranb, __CLPK_integer *isgn, __CLPK_integer 
	*m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_real *
	c__, __CLPK_integer *ldc, __CLPK_real *scale, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strti2_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strtri_(char *uplo, char *diag, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strtrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_real *a, __CLPK_integer *lda, __CLPK_real *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strttf_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_real *a, 
	__CLPK_integer *lda, __CLPK_real *arf, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int strttp_(char *uplo, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stzrqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int stzrzf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_real *a, __CLPK_integer *lda, 
	__CLPK_real *tau, __CLPK_real *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zbdsqr_(char *uplo, __CLPK_integer *n, __CLPK_integer *ncvt, __CLPK_integer *
	nru, __CLPK_integer *ncc, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublecomplex *vt, 
	__CLPK_integer *ldvt, __CLPK_doublecomplex *u, __CLPK_integer *ldu, __CLPK_doublecomplex *c__, 
	__CLPK_integer *ldc, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zcgesv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublecomplex *work, __CLPK_complex *swork, 
	__CLPK_doublereal *rwork, __CLPK_integer *iter, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zcposv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublecomplex *work, __CLPK_complex *swork, 
	__CLPK_doublereal *rwork, __CLPK_integer *iter, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zdrscl_(__CLPK_integer *n, __CLPK_doublereal *sa, __CLPK_doublecomplex *sx, 
	__CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbbrd_(char *vect, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *ncc, 
	 __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, 
	__CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublecomplex *q, __CLPK_integer *ldq, 
	__CLPK_doublecomplex *pt, __CLPK_integer *ldpt, __CLPK_doublecomplex *c__, __CLPK_integer *ldc, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbcon_(char *norm, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_doublereal *anorm, 
	__CLPK_doublereal *rcond, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbequ_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *r__, __CLPK_doublereal *c__, 
	__CLPK_doublereal *rowcnd, __CLPK_doublereal *colcnd, __CLPK_doublereal *amax, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbequb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *r__, __CLPK_doublereal *
	c__, __CLPK_doublereal *rowcnd, __CLPK_doublereal *colcnd, __CLPK_doublereal *amax, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbrfs_(char *trans, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_integer *nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *
	afb, __CLPK_integer *ldafb, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbsv_(__CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_doublecomplex *
	b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbsvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *kl, 
	 __CLPK_integer *ku, __CLPK_integer *nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, 
	__CLPK_doublecomplex *afb, __CLPK_integer *ldafb, __CLPK_integer *ipiv, char *equed, 
	__CLPK_doublereal *r__, __CLPK_doublereal *c__, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbtf2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbtrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgbtrs_(char *trans, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *
	ku, __CLPK_integer *nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_integer *ipiv, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgebak_(char *job, char *side, __CLPK_integer *n, __CLPK_integer *ilo, 
	__CLPK_integer *ihi, __CLPK_doublereal *scale, __CLPK_integer *m, __CLPK_doublecomplex *v, 
	__CLPK_integer *ldv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgebal_(char *job, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer 
	*lda, __CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *scale, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgebd2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublecomplex *tauq, 
	__CLPK_doublecomplex *taup, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgebrd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublecomplex *tauq, 
	__CLPK_doublecomplex *taup, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgecon_(char *norm, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeequ_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *r__, __CLPK_doublereal *c__, __CLPK_doublereal *rowcnd, 
	__CLPK_doublereal *colcnd, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeequb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *r__, __CLPK_doublereal *c__, __CLPK_doublereal *rowcnd, 
	__CLPK_doublereal *colcnd, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgees_(char *jobvs, char *sort, __CLPK_L_fp select, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *sdim, __CLPK_doublecomplex *w, 
	__CLPK_doublecomplex *vs, __CLPK_integer *ldvs, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_doublereal *rwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeesx_(char *jobvs, char *sort, __CLPK_L_fp select, char *
	sense, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *sdim, 
	__CLPK_doublecomplex *w, __CLPK_doublecomplex *vs, __CLPK_integer *ldvs, __CLPK_doublereal *
	rconde, __CLPK_doublereal *rcondv, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	__CLPK_doublereal *rwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeev_(char *jobvl, char *jobvr, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *w, __CLPK_doublecomplex *vl, 
	__CLPK_integer *ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *ldvr, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *w, 
	__CLPK_doublecomplex *vl, __CLPK_integer *ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *ldvr, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *scale, __CLPK_doublereal *abnrm, 
	__CLPK_doublereal *rconde, __CLPK_doublereal *rcondv, __CLPK_doublecomplex *work, __CLPK_integer *
	lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgegs_(char *jobvsl, char *jobvsr, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *alpha, __CLPK_doublecomplex *beta, __CLPK_doublecomplex *vsl, 
	__CLPK_integer *ldvsl, __CLPK_doublecomplex *vsr, __CLPK_integer *ldvsr, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgegv_(char *jobvl, char *jobvr, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *alpha, __CLPK_doublecomplex *beta, __CLPK_doublecomplex *vl, __CLPK_integer 
	*ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *ldvr, __CLPK_doublecomplex *work, __CLPK_integer 
	*lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgehd2_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgehrd_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgelq2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgelqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgels_(char *trans, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgelsd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *s, __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgelss_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *s, __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgelsx_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *jpvt, __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublecomplex *work, 
	__CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgelsy_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *jpvt, __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeql2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeqlf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeqp3_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *jpvt, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeqpf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *jpvt, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, 
	__CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeqr2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgeqrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgerfs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *af, __CLPK_integer *ldaf, 
	__CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, 
	__CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *work, 
	 __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgerq2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgerqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgesc2_(__CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_doublecomplex *rhs, __CLPK_integer *ipiv, __CLPK_integer *jpiv, __CLPK_doublereal *scale) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgesdd_(char *jobz, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *s, __CLPK_doublecomplex *u, 
	__CLPK_integer *ldu, __CLPK_doublecomplex *vt, __CLPK_integer *ldvt, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgesv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgesvd_(char *jobu, char *jobvt, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *s, __CLPK_doublecomplex *u, 
	__CLPK_integer *ldu, __CLPK_doublecomplex *vt, __CLPK_integer *ldvt, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgesvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *af, __CLPK_integer *
	ldaf, __CLPK_integer *ipiv, char *equed, __CLPK_doublereal *r__, __CLPK_doublereal *c__, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgetc2_(__CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_integer *jpiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgetf2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgetrf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgetri_(__CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_integer *ipiv, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgetrs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggbak_(char *job, char *side, __CLPK_integer *n, __CLPK_integer *ilo, 
	__CLPK_integer *ihi, __CLPK_doublereal *lscale, __CLPK_doublereal *rscale, __CLPK_integer *m, 
	__CLPK_doublecomplex *v, __CLPK_integer *ldv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggbal_(char *job, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer 
	*lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	__CLPK_doublereal *lscale, __CLPK_doublereal *rscale, __CLPK_doublereal *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgges_(char *jobvsl, char *jobvsr, char *sort, __CLPK_L_fp 
	selctg, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_integer *sdim, __CLPK_doublecomplex *alpha, __CLPK_doublecomplex *
	beta, __CLPK_doublecomplex *vsl, __CLPK_integer *ldvsl, __CLPK_doublecomplex *vsr, __CLPK_integer 
	*ldvsr, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, 
	__CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggesx_(char *jobvsl, char *jobvsr, char *sort, __CLPK_L_fp 
	selctg, char *sense, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *sdim, __CLPK_doublecomplex *alpha, 
	__CLPK_doublecomplex *beta, __CLPK_doublecomplex *vsl, __CLPK_integer *ldvsl, 
	__CLPK_doublecomplex *vsr, __CLPK_integer *ldvsr, __CLPK_doublereal *rconde, __CLPK_doublereal *
	rcondv, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, 
	__CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggev_(char *jobvl, char *jobvr, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *alpha, __CLPK_doublecomplex *beta, __CLPK_doublecomplex *vl, __CLPK_integer 
	*ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *ldvr, __CLPK_doublecomplex *work, __CLPK_integer 
	*lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_doublecomplex *alpha, __CLPK_doublecomplex *beta, 
	__CLPK_doublecomplex *vl, __CLPK_integer *ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *ldvr, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublereal *lscale, __CLPK_doublereal *rscale, 
	__CLPK_doublereal *abnrm, __CLPK_doublereal *bbnrm, __CLPK_doublereal *rconde, __CLPK_doublereal *
	rcondv, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, 
	__CLPK_integer *iwork, __CLPK_logical *bwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggglm_(__CLPK_integer *n, __CLPK_integer *m, __CLPK_integer *p, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *d__, __CLPK_doublecomplex *x, __CLPK_doublecomplex *y, __CLPK_doublecomplex 
	*work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgghrd_(char *compq, char *compz, __CLPK_integer *n, __CLPK_integer *
	ilo, __CLPK_integer *ihi, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgglse_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *p, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *c__, __CLPK_doublecomplex *d__, __CLPK_doublecomplex *x, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggqrf_(__CLPK_integer *n, __CLPK_integer *m, __CLPK_integer *p, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *taua, __CLPK_doublecomplex *b, 
	 __CLPK_integer *ldb, __CLPK_doublecomplex *taub, __CLPK_doublecomplex *work, __CLPK_integer *
	lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggrqf_(__CLPK_integer *m, __CLPK_integer *p, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *taua, __CLPK_doublecomplex *b, 
	 __CLPK_integer *ldb, __CLPK_doublecomplex *taub, __CLPK_doublecomplex *work, __CLPK_integer *
	lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggsvd_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_integer *p, __CLPK_integer *k, __CLPK_integer *l, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublereal *alpha, 
	__CLPK_doublereal *beta, __CLPK_doublecomplex *u, __CLPK_integer *ldu, __CLPK_doublecomplex *v, 
	__CLPK_integer *ldv, __CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *work, 
	__CLPK_doublereal *rwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zggsvp_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *p, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex 
	*b, __CLPK_integer *ldb, __CLPK_doublereal *tola, __CLPK_doublereal *tolb, __CLPK_integer *k, 
	__CLPK_integer *l, __CLPK_doublecomplex *u, __CLPK_integer *ldu, __CLPK_doublecomplex *v, __CLPK_integer 
	*ldv, __CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_integer *iwork, __CLPK_doublereal *
	rwork, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgtcon_(char *norm, __CLPK_integer *n, __CLPK_doublecomplex *dl, 
	__CLPK_doublecomplex *d__, __CLPK_doublecomplex *du, __CLPK_doublecomplex *du2, __CLPK_integer *
	ipiv, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublecomplex *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgtrfs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *dl, __CLPK_doublecomplex *d__, __CLPK_doublecomplex *du, 
	__CLPK_doublecomplex *dlf, __CLPK_doublecomplex *df, __CLPK_doublecomplex *duf, 
	__CLPK_doublecomplex *du2, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgtsv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublecomplex *dl, 
	__CLPK_doublecomplex *d__, __CLPK_doublecomplex *du, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgtsvx_(char *fact, char *trans, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *dl, __CLPK_doublecomplex *d__, __CLPK_doublecomplex *du, 
	__CLPK_doublecomplex *dlf, __CLPK_doublecomplex *df, __CLPK_doublecomplex *duf, 
	__CLPK_doublecomplex *du2, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgttrf_(__CLPK_integer *n, __CLPK_doublecomplex *dl, __CLPK_doublecomplex *
	d__, __CLPK_doublecomplex *du, __CLPK_doublecomplex *du2, __CLPK_integer *ipiv, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgttrs_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *dl, __CLPK_doublecomplex *d__, __CLPK_doublecomplex *du, 
	__CLPK_doublecomplex *du2, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zgtts2_(__CLPK_integer *itrans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *dl, __CLPK_doublecomplex *d__, __CLPK_doublecomplex *du, 
	__CLPK_doublecomplex *du2, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhbev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhbevd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, 
	__CLPK_integer *lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhbevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *q, 
	__CLPK_integer *ldq, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *
	iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, 
	 __CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *iwork, 
	 __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhbgst_(char *vect, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *bb, 
	__CLPK_integer *ldbb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublecomplex *work, 
	__CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhbgv_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *bb, 
	__CLPK_integer *ldbb, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhbgvd_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_integer *ka, 
	__CLPK_integer *kb, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *bb, 
	__CLPK_integer *ldbb, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *
	lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhbgvx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_integer *ka, __CLPK_integer *kb, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, 
	__CLPK_doublecomplex *bb, __CLPK_integer *ldbb, __CLPK_doublecomplex *q, __CLPK_integer *ldq, 
	__CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *
	abstol, __CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *iwork, __CLPK_integer *
	ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhbtrd_(char *vect, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhecon_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, 
	__CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zheequb_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, 
	__CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zheev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_doublecomplex 
	*a, __CLPK_integer *lda, __CLPK_doublereal *w, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	__CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zheevd_(char *jobz, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *w, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *lrwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zheevr_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *vl, __CLPK_doublereal *vu, 
	__CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *
	w, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *lrwork, __CLPK_integer *
	iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zheevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *vl, __CLPK_doublereal *vu, 
	__CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *
	w, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_integer *
	lwork, __CLPK_doublereal *rwork, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhegs2_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhegst_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhegv_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *w, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhegvd_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublereal *w, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, 
	 __CLPK_integer *lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhegvx_(__CLPK_integer *itype, char *jobz, char *range, char *
	uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *
	iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, 
	 __CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, 
	 __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zherfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *af, __CLPK_integer *ldaf, 
	__CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, 
	__CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *work, 
	 __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhesv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhesvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *af, __CLPK_integer *
	ldaf, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, 
	 __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhetd2_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublecomplex *tau, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhetf2_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhetrd_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhetrf_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhetri_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhetrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhfrk_(char *transr, char *uplo, char *trans, __CLPK_integer *n, 
	 __CLPK_integer *k, __CLPK_doublereal *alpha, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_doublereal *beta, __CLPK_doublecomplex *c__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhgeqz_(char *job, char *compq, char *compz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublecomplex *h__, __CLPK_integer *ldh, 
	__CLPK_doublecomplex *t, __CLPK_integer *ldt, __CLPK_doublecomplex *alpha, __CLPK_doublecomplex *
	beta, __CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *z__, __CLPK_integer *
	ldz, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpcon_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_integer *ipiv, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublecomplex *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpev_(char *jobz, char *uplo, __CLPK_integer *n, __CLPK_doublecomplex 
	*ap, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpevd_(char *jobz, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *ap, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *
	lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpevx_(char *jobz, char *range, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *ap, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, 
	__CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, 
	__CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_doublereal *
	rwork, __CLPK_integer *iwork, __CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpgst_(__CLPK_integer *itype, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *ap, __CLPK_doublecomplex *bp, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpgv_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *bp, __CLPK_doublereal *w, __CLPK_doublecomplex 
	*z__, __CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpgvd_(__CLPK_integer *itype, char *jobz, char *uplo, __CLPK_integer *
	n, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *bp, __CLPK_doublereal *w, __CLPK_doublecomplex 
	*z__, __CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *
	rwork, __CLPK_integer *lrwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpgvx_(__CLPK_integer *itype, char *jobz, char *range, char *
	uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *bp, __CLPK_doublereal *
	vl, __CLPK_doublereal *vu, __CLPK_integer *il, __CLPK_integer *iu, __CLPK_doublereal *abstol, 
	__CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *iwork, __CLPK_integer *
	ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_doublecomplex *afp, __CLPK_integer *ipiv, __CLPK_doublecomplex *
	b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhpsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *afp, __CLPK_integer *ipiv, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhptrd_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublecomplex *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhptrf_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhptri_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_integer *ipiv, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhsein_(char *side, char *eigsrc, char *initv, __CLPK_logical *
	select, __CLPK_integer *n, __CLPK_doublecomplex *h__, __CLPK_integer *ldh, __CLPK_doublecomplex *
	w, __CLPK_doublecomplex *vl, __CLPK_integer *ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *ldvr, 
	 __CLPK_integer *mm, __CLPK_integer *m, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, 
	__CLPK_integer *ifaill, __CLPK_integer *ifailr, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zhseqr_(char *job, char *compz, __CLPK_integer *n, __CLPK_integer *ilo, 
	 __CLPK_integer *ihi, __CLPK_doublecomplex *h__, __CLPK_integer *ldh, __CLPK_doublecomplex *w, 
	__CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlabrd_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *nb, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_doublecomplex *tauq, __CLPK_doublecomplex *taup, __CLPK_doublecomplex *x, __CLPK_integer *
	ldx, __CLPK_doublecomplex *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlacgv_(__CLPK_integer *n, __CLPK_doublecomplex *x, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlacn2_(__CLPK_integer *n, __CLPK_doublecomplex *v, __CLPK_doublecomplex *x, 
	__CLPK_doublereal *est, __CLPK_integer *kase, __CLPK_integer *isave) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlacon_(__CLPK_integer *n, __CLPK_doublecomplex *v, __CLPK_doublecomplex *x, 
	__CLPK_doublereal *est, __CLPK_integer *kase) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlacp2_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *
	a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlacpy_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlacrm_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *b, __CLPK_integer *ldb, __CLPK_doublecomplex *c__, 
	__CLPK_integer *ldc, __CLPK_doublereal *rwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlacrt_(__CLPK_integer *n, __CLPK_doublecomplex *cx, __CLPK_integer *incx, 
	__CLPK_doublecomplex *cy, __CLPK_integer *incy, __CLPK_doublecomplex *c__, __CLPK_doublecomplex *
	s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void zladiv_(__CLPK_doublecomplex * ret_val, __CLPK_doublecomplex *x, 
	__CLPK_doublecomplex *y) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaed0_(__CLPK_integer *qsiz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *qstore, 
	__CLPK_integer *ldqs, __CLPK_doublereal *rwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaed7_(__CLPK_integer *n, __CLPK_integer *cutpnt, __CLPK_integer *qsiz, 
	__CLPK_integer *tlvls, __CLPK_integer *curlvl, __CLPK_integer *curpbm, __CLPK_doublereal *d__, 
	__CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublereal *rho, __CLPK_integer *indxq, 
	__CLPK_doublereal *qstore, __CLPK_integer *qptr, __CLPK_integer *prmptr, __CLPK_integer *perm, 
	__CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_doublereal *givnum, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaed8_(__CLPK_integer *k, __CLPK_integer *n, __CLPK_integer *qsiz, 
	__CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublereal *d__, __CLPK_doublereal *rho, 
	__CLPK_integer *cutpnt, __CLPK_doublereal *z__, __CLPK_doublereal *dlamda, __CLPK_doublecomplex *
	q2, __CLPK_integer *ldq2, __CLPK_doublereal *w, __CLPK_integer *indxp, __CLPK_integer *indx, 
	__CLPK_integer *indxq, __CLPK_integer *perm, __CLPK_integer *givptr, __CLPK_integer *givcol, 
	__CLPK_doublereal *givnum, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaein_(__CLPK_logical *rightv, __CLPK_logical *noinit, __CLPK_integer *n, 
	__CLPK_doublecomplex *h__, __CLPK_integer *ldh, __CLPK_doublecomplex *w, __CLPK_doublecomplex *v, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublereal *rwork, __CLPK_doublereal *eps3, 
	__CLPK_doublereal *smlnum, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaesy_(__CLPK_doublecomplex *a, __CLPK_doublecomplex *b, 
	__CLPK_doublecomplex *c__, __CLPK_doublecomplex *rt1, __CLPK_doublecomplex *rt2, 
	__CLPK_doublecomplex *evscal, __CLPK_doublecomplex *cs1, __CLPK_doublecomplex *sn1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaev2_(__CLPK_doublecomplex *a, __CLPK_doublecomplex *b, 
	__CLPK_doublecomplex *c__, __CLPK_doublereal *rt1, __CLPK_doublereal *rt2, __CLPK_doublereal *cs1, 
	 __CLPK_doublecomplex *sn1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlag2c_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_complex *sa, __CLPK_integer *ldsa, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlags2_(__CLPK_logical *upper, __CLPK_doublereal *a1, __CLPK_doublecomplex *
	a2, __CLPK_doublereal *a3, __CLPK_doublereal *b1, __CLPK_doublecomplex *b2, __CLPK_doublereal *b3, 
	 __CLPK_doublereal *csu, __CLPK_doublecomplex *snu, __CLPK_doublereal *csv, __CLPK_doublecomplex *
	snv, __CLPK_doublereal *csq, __CLPK_doublecomplex *snq) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlagtm_(char *trans, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *alpha, __CLPK_doublecomplex *dl, __CLPK_doublecomplex *d__, 
	__CLPK_doublecomplex *du, __CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *beta, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlahef_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_integer *kb, 
	 __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *w, 
	__CLPK_integer *ldw, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlahqr_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublecomplex *h__, __CLPK_integer *ldh, 
	__CLPK_doublecomplex *w, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlahr2_(__CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *nb, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *t, 
	__CLPK_integer *ldt, __CLPK_doublecomplex *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlahrd_(__CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *nb, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *t, 
	__CLPK_integer *ldt, __CLPK_doublecomplex *y, __CLPK_integer *ldy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaic1_(__CLPK_integer *job, __CLPK_integer *j, __CLPK_doublecomplex *x, 
	__CLPK_doublereal *sest, __CLPK_doublecomplex *w, __CLPK_doublecomplex *gamma, __CLPK_doublereal *
	sestpr, __CLPK_doublecomplex *s, __CLPK_doublecomplex *c__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlals0_(__CLPK_integer *icompq, __CLPK_integer *nl, __CLPK_integer *nr, 
	__CLPK_integer *sqre, __CLPK_integer *nrhs, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *bx, __CLPK_integer *ldbx, __CLPK_integer *perm, __CLPK_integer *givptr, 
	__CLPK_integer *givcol, __CLPK_integer *ldgcol, __CLPK_doublereal *givnum, __CLPK_integer *ldgnum, 
	 __CLPK_doublereal *poles, __CLPK_doublereal *difl, __CLPK_doublereal *difr, __CLPK_doublereal *
	z__, __CLPK_integer *k, __CLPK_doublereal *c__, __CLPK_doublereal *s, __CLPK_doublereal *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlalsa_(__CLPK_integer *icompq, __CLPK_integer *smlsiz, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *bx, 
	__CLPK_integer *ldbx, __CLPK_doublereal *u, __CLPK_integer *ldu, __CLPK_doublereal *vt, __CLPK_integer *
	k, __CLPK_doublereal *difl, __CLPK_doublereal *difr, __CLPK_doublereal *z__, __CLPK_doublereal *
	poles, __CLPK_integer *givptr, __CLPK_integer *givcol, __CLPK_integer *ldgcol, __CLPK_integer *
	perm, __CLPK_doublereal *givnum, __CLPK_doublereal *c__, __CLPK_doublereal *s, __CLPK_doublereal *
	rwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlalsd_(char *uplo, __CLPK_integer *smlsiz, __CLPK_integer *n, __CLPK_integer 
	*nrhs, __CLPK_doublereal *d__, __CLPK_doublereal *e, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	 __CLPK_doublereal *rcond, __CLPK_integer *rank, __CLPK_doublecomplex *work, __CLPK_doublereal *
	rwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlangb_(char *norm, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlange_(char *norm, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlangt_(char *norm, __CLPK_integer *n, __CLPK_doublecomplex *dl, __CLPK_doublecomplex *
	d__, __CLPK_doublecomplex *du) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlanhb_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlanhe_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlanhf_(char *norm, char *transr, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlanhp_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlanhs_(char *norm, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlanht_(char *norm, __CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublecomplex *e) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlansb_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlansp_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlansy_(char *norm, char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlantb_(char *norm, char *uplo, char *diag, __CLPK_integer *n, __CLPK_integer *k, 
	 __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlantp_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_doublecomplex *ap, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal zlantr_(char *norm, char *uplo, char *diag, __CLPK_integer *m, __CLPK_integer *n, 
	 __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlapll_(__CLPK_integer *n, __CLPK_doublecomplex *x, __CLPK_integer *incx, 
	__CLPK_doublecomplex *y, __CLPK_integer *incy, __CLPK_doublereal *ssmin) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlapmt_(__CLPK_logical *forwrd, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_integer *k) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqgb_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *kl, __CLPK_integer *ku, 
	 __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *r__, __CLPK_doublereal *c__, 
	__CLPK_doublereal *rowcnd, __CLPK_doublereal *colcnd, __CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqge_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *r__, __CLPK_doublereal *c__, __CLPK_doublereal *rowcnd, 
	__CLPK_doublereal *colcnd, __CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqhb_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *s, __CLPK_doublereal *scond, 
	__CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqhe_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, 
	char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqhp_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqp2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *offset, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *jpvt, __CLPK_doublecomplex *tau, 
	__CLPK_doublereal *vn1, __CLPK_doublereal *vn2, __CLPK_doublecomplex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqps_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *offset, __CLPK_integer 
	*nb, __CLPK_integer *kb, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *jpvt, 
	__CLPK_doublecomplex *tau, __CLPK_doublereal *vn1, __CLPK_doublereal *vn2, __CLPK_doublecomplex *
	auxv, __CLPK_doublecomplex *f, __CLPK_integer *ldf) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqr0_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublecomplex *h__, __CLPK_integer *ldh, 
	__CLPK_doublecomplex *w, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqr1_(__CLPK_integer *n, __CLPK_doublecomplex *h__, __CLPK_integer *ldh, 
	__CLPK_doublecomplex *s1, __CLPK_doublecomplex *s2, __CLPK_doublecomplex *v) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqr2_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nw, __CLPK_doublecomplex *h__, 
	__CLPK_integer *ldh, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_integer *ns, __CLPK_integer *nd, __CLPK_doublecomplex *sh, 
	__CLPK_doublecomplex *v, __CLPK_integer *ldv, __CLPK_integer *nh, __CLPK_doublecomplex *t, 
	__CLPK_integer *ldt, __CLPK_integer *nv, __CLPK_doublecomplex *wv, __CLPK_integer *ldwv, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqr3_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nw, __CLPK_doublecomplex *h__, 
	__CLPK_integer *ldh, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_integer *ns, __CLPK_integer *nd, __CLPK_doublecomplex *sh, 
	__CLPK_doublecomplex *v, __CLPK_integer *ldv, __CLPK_integer *nh, __CLPK_doublecomplex *t, 
	__CLPK_integer *ldt, __CLPK_integer *nv, __CLPK_doublecomplex *wv, __CLPK_integer *ldwv, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqr4_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublecomplex *h__, __CLPK_integer *ldh, 
	__CLPK_doublecomplex *w, __CLPK_integer *iloz, __CLPK_integer *ihiz, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqr5_(__CLPK_logical *wantt, __CLPK_logical *wantz, __CLPK_integer *kacc22, 
	__CLPK_integer *n, __CLPK_integer *ktop, __CLPK_integer *kbot, __CLPK_integer *nshfts, 
	__CLPK_doublecomplex *s, __CLPK_doublecomplex *h__, __CLPK_integer *ldh, __CLPK_integer *iloz, 
	__CLPK_integer *ihiz, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublecomplex *v, 
	__CLPK_integer *ldv, __CLPK_doublecomplex *u, __CLPK_integer *ldu, __CLPK_integer *nv, 
	__CLPK_doublecomplex *wv, __CLPK_integer *ldwv, __CLPK_integer *nh, __CLPK_doublecomplex *wh, 
	__CLPK_integer *ldwh) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqsb_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *s, __CLPK_doublereal *scond, 
	__CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqsp_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaqsy_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, 
	char *equed) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlar1v_(__CLPK_integer *n, __CLPK_integer *b1, __CLPK_integer *bn, __CLPK_doublereal 
	*lambda, __CLPK_doublereal *d__, __CLPK_doublereal *l, __CLPK_doublereal *ld, __CLPK_doublereal *
	lld, __CLPK_doublereal *pivmin, __CLPK_doublereal *gaptol, __CLPK_doublecomplex *z__, 
	__CLPK_logical *wantnc, __CLPK_integer *negcnt, __CLPK_doublereal *ztz, __CLPK_doublereal *mingma, 
	 __CLPK_integer *r__, __CLPK_integer *isuppz, __CLPK_doublereal *nrminv, __CLPK_doublereal *resid, 
	 __CLPK_doublereal *rqcorr, __CLPK_doublereal *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlar2v_(__CLPK_integer *n, __CLPK_doublecomplex *x, __CLPK_doublecomplex *y, 
	__CLPK_doublecomplex *z__, __CLPK_integer *incx, __CLPK_doublereal *c__, __CLPK_doublecomplex *s, 
	__CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarcm_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *a, __CLPK_integer *
	lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *c__, __CLPK_integer *ldc, 
	 __CLPK_doublereal *rwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarf_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex 
	*v, __CLPK_integer *incv, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *c__, __CLPK_integer *
	ldc, __CLPK_doublecomplex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarfb_(char *side, char *trans, char *direct, char *
	storev, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_doublecomplex *v, __CLPK_integer 
	*ldv, __CLPK_doublecomplex *t, __CLPK_integer *ldt, __CLPK_doublecomplex *c__, __CLPK_integer *
	ldc, __CLPK_doublecomplex *work, __CLPK_integer *ldwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarfg_(__CLPK_integer *n, __CLPK_doublecomplex *alpha, __CLPK_doublecomplex *
	x, __CLPK_integer *incx, __CLPK_doublecomplex *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarfp_(__CLPK_integer *n, __CLPK_doublecomplex *alpha, __CLPK_doublecomplex *
	x, __CLPK_integer *incx, __CLPK_doublecomplex *tau) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarft_(char *direct, char *storev, __CLPK_integer *n, __CLPK_integer *
	k, __CLPK_doublecomplex *v, __CLPK_integer *ldv, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	t, __CLPK_integer *ldt) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarfx_(char *side, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublecomplex *v, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *c__, __CLPK_integer *
	ldc, __CLPK_doublecomplex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlargv_(__CLPK_integer *n, __CLPK_doublecomplex *x, __CLPK_integer *incx, 
	__CLPK_doublecomplex *y, __CLPK_integer *incy, __CLPK_doublereal *c__, __CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarnv_(__CLPK_integer *idist, __CLPK_integer *iseed, __CLPK_integer *n, 
	__CLPK_doublecomplex *x) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarrv_(__CLPK_integer *n, __CLPK_doublereal *vl, __CLPK_doublereal *vu, 
	__CLPK_doublereal *d__, __CLPK_doublereal *l, __CLPK_doublereal *pivmin, __CLPK_integer *isplit, 
	__CLPK_integer *m, __CLPK_integer *dol, __CLPK_integer *dou, __CLPK_doublereal *minrgp, 
	__CLPK_doublereal *rtol1, __CLPK_doublereal *rtol2, __CLPK_doublereal *w, __CLPK_doublereal *werr, 
	 __CLPK_doublereal *wgap, __CLPK_integer *iblock, __CLPK_integer *indexw, __CLPK_doublereal *gers, 
	 __CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_doublereal *work, 
	__CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarscl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlartg_(__CLPK_doublecomplex *f, __CLPK_doublecomplex *g, __CLPK_doublereal *
	cs, __CLPK_doublecomplex *sn, __CLPK_doublecomplex *r__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlartv_(__CLPK_integer *n, __CLPK_doublecomplex *x, __CLPK_integer *incx, 
	__CLPK_doublecomplex *y, __CLPK_integer *incy, __CLPK_doublereal *c__, __CLPK_doublecomplex *s, 
	__CLPK_integer *incc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarz_(char *side, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *l, 
	__CLPK_doublecomplex *v, __CLPK_integer *incv, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarzb_(char *side, char *trans, char *direct, char *
	storev, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *l, __CLPK_doublecomplex 
	*v, __CLPK_integer *ldv, __CLPK_doublecomplex *t, __CLPK_integer *ldt, __CLPK_doublecomplex *c__, 
	__CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *ldwork) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlarzt_(char *direct, char *storev, __CLPK_integer *n, __CLPK_integer *
	k, __CLPK_doublecomplex *v, __CLPK_integer *ldv, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	t, __CLPK_integer *ldt) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlascl_(char *type__, __CLPK_integer *kl, __CLPK_integer *ku, 
	__CLPK_doublereal *cfrom, __CLPK_doublereal *cto, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlascl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaset_(char *uplo, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublecomplex *alpha, __CLPK_doublecomplex *beta, __CLPK_doublecomplex *a, __CLPK_integer *
	lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlasr_(char *side, char *pivot, char *direct, __CLPK_integer *m, 
	 __CLPK_integer *n, __CLPK_doublereal *c__, __CLPK_doublereal *s, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlassq_(__CLPK_integer *n, __CLPK_doublecomplex *x, __CLPK_integer *incx, 
	__CLPK_doublereal *scale, __CLPK_doublereal *sumsq) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlaswp_(__CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_integer *k1, __CLPK_integer *k2, __CLPK_integer *ipiv, __CLPK_integer *incx) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlasyf_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, __CLPK_integer *kb, 
	 __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *w, 
	__CLPK_integer *ldw, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlat2c_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_complex *sa, __CLPK_integer *ldsa, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlatbs_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, 
	__CLPK_doublecomplex *x, __CLPK_doublereal *scale, __CLPK_doublereal *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlatdf_(__CLPK_integer *ijob, __CLPK_integer *n, __CLPK_doublecomplex *z__, 
	__CLPK_integer *ldz, __CLPK_doublecomplex *rhs, __CLPK_doublereal *rdsum, __CLPK_doublereal *
	rdscal, __CLPK_integer *ipiv, __CLPK_integer *jpiv) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlatps_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *x, __CLPK_doublereal *
	scale, __CLPK_doublereal *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlatrd_(char *uplo, __CLPK_integer *n, __CLPK_integer *nb, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *e, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *w, __CLPK_integer *ldw) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlatrs_(char *uplo, char *trans, char *diag, char *
	normin, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *x, 
	__CLPK_doublereal *scale, __CLPK_doublereal *cnorm, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlatrz_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *l, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlatzm_(char *side, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_doublecomplex *v, __CLPK_integer *incv, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	c1, __CLPK_doublecomplex *c2, __CLPK_integer *ldc, __CLPK_doublecomplex *work) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlauu2_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zlauum_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbcon_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *anorm, __CLPK_doublereal *
	rcond, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbequ_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *s, __CLPK_doublereal *scond, 
	__CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *afb, __CLPK_integer *
	ldafb, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	 __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *
	rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbstf_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *b, __CLPK_integer *
	ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_integer *nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *afb, 
	__CLPK_integer *ldafb, char *equed, __CLPK_doublereal *s, __CLPK_doublecomplex *b, __CLPK_integer 
	*ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *
	ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbtf2_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbtrf_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, 
	__CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpbtrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *kd, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublecomplex *b, __CLPK_integer *
	ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpftrf_(char *transr, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpftri_(char *transr, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpftrs_(char *transr, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *a, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpocon_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpoequ_(__CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpoequb_(__CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zporfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *af, __CLPK_integer *ldaf, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *
	rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zposv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zposvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *af, __CLPK_integer *
	ldaf, char *equed, __CLPK_doublereal *s, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpotf2_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpotrf_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpotri_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpotrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zppcon_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublecomplex *work, __CLPK_doublereal 
	*rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zppequ_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_doublecomplex *afp, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	 __CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zppsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zppsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *afp, char *equed, __CLPK_doublereal *
	s, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpptrf_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpptri_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpstf2_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *piv, __CLPK_integer *rank, __CLPK_doublereal *tol, 
	__CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpstrf_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *piv, __CLPK_integer *rank, __CLPK_doublereal *tol, 
	__CLPK_doublereal *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zptcon_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublecomplex *e, 
	__CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpteqr_(char *compz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zptrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *d__, __CLPK_doublecomplex *e, __CLPK_doublereal *df, __CLPK_doublecomplex *ef, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *
	rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zptsv_(__CLPK_integer *n, __CLPK_integer *nrhs, __CLPK_doublereal *d__, 
	__CLPK_doublecomplex *e, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zptsvx_(char *fact, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *d__, __CLPK_doublecomplex *e, __CLPK_doublereal *df, __CLPK_doublecomplex *ef, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpttrf_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublecomplex *e, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zpttrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *d__, __CLPK_doublecomplex *e, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zptts2_(__CLPK_integer *iuplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublereal *d__, __CLPK_doublecomplex *e, __CLPK_doublecomplex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zrot_(__CLPK_integer *n, __CLPK_doublecomplex *cx, __CLPK_integer *incx, 
	__CLPK_doublecomplex *cy, __CLPK_integer *incy, __CLPK_doublereal *c__, __CLPK_doublecomplex *s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zspcon_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_integer *ipiv, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, __CLPK_doublecomplex *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zspmv_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *alpha, 
	__CLPK_doublecomplex *ap, __CLPK_doublecomplex *x, __CLPK_integer *incx, __CLPK_doublecomplex *
	beta, __CLPK_doublecomplex *y, __CLPK_integer *incy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zspr_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *alpha, 
	__CLPK_doublecomplex *x, __CLPK_integer *incx, __CLPK_doublecomplex *ap) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsprfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_doublecomplex *afp, __CLPK_integer *ipiv, __CLPK_doublecomplex *
	b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zspsv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zspsvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *afp, __CLPK_integer *ipiv, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsptrf_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsptri_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_integer *ipiv, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsptrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *ap, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zstedc_(char *compz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublecomplex *work, 
	__CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *lrwork, __CLPK_integer *iwork, 
	__CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zstegr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_doublereal *
	d__, __CLPK_doublereal *e, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, 
	__CLPK_integer *iu, __CLPK_doublereal *abstol, __CLPK_integer *m, __CLPK_doublereal *w, 
	__CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_integer *isuppz, __CLPK_doublereal *work, 
	__CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zstein_(__CLPK_integer *n, __CLPK_doublereal *d__, __CLPK_doublereal *e, 
	__CLPK_integer *m, __CLPK_doublereal *w, __CLPK_integer *iblock, __CLPK_integer *isplit, 
	__CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, __CLPK_integer *iwork, 
	__CLPK_integer *ifail, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zstemr_(char *jobz, char *range, __CLPK_integer *n, __CLPK_doublereal *
	d__, __CLPK_doublereal *e, __CLPK_doublereal *vl, __CLPK_doublereal *vu, __CLPK_integer *il, 
	__CLPK_integer *iu, __CLPK_integer *m, __CLPK_doublereal *w, __CLPK_doublecomplex *z__, __CLPK_integer *
	ldz, __CLPK_integer *nzc, __CLPK_integer *isuppz, __CLPK_logical *tryrac, __CLPK_doublereal *work, 
	 __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsteqr_(char *compz, __CLPK_integer *n, __CLPK_doublereal *d__, 
	__CLPK_doublereal *e, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, __CLPK_doublereal *work, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsycon_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublereal *anorm, __CLPK_doublereal *rcond, 
	__CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsyequb_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublereal *s, __CLPK_doublereal *scond, __CLPK_doublereal *amax, 
	__CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsymv_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *alpha, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *x, __CLPK_integer *incx, 
	__CLPK_doublecomplex *beta, __CLPK_doublecomplex *y, __CLPK_integer *incy) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsyr_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *alpha, 
	__CLPK_doublecomplex *x, __CLPK_integer *incx, __CLPK_doublecomplex *a, __CLPK_integer *lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsyrfs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *af, __CLPK_integer *ldaf, 
	__CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, 
	__CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *work, 
	 __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsysv_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsysvx_(char *fact, char *uplo, __CLPK_integer *n, __CLPK_integer *
	nrhs, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *af, __CLPK_integer *
	ldaf, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, 
	 __CLPK_integer *ldx, __CLPK_doublereal *rcond, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsytf2_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsytrf_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsytri_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zsytrs_(char *uplo, __CLPK_integer *n, __CLPK_integer *nrhs, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *ipiv, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztbcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, __CLPK_doublereal *rcond, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztbrfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_integer *nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, 
	__CLPK_doublereal *ferr, __CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *
	rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztbtrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *kd, __CLPK_integer *nrhs, __CLPK_doublecomplex *ab, __CLPK_integer *ldab, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztfsm_(char *transr, char *side, char *uplo, char *trans, 
	 char *diag, __CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *alpha, 
	__CLPK_doublecomplex *a, __CLPK_doublecomplex *b, __CLPK_integer *ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztftri_(char *transr, char *uplo, char *diag, __CLPK_integer *n, 
	 __CLPK_doublecomplex *a, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztfttp_(char *transr, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *arf, __CLPK_doublecomplex *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztfttr_(char *transr, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *arf, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztgevc_(char *side, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_doublecomplex *s, __CLPK_integer *lds, __CLPK_doublecomplex *p, __CLPK_integer 
	*ldp, __CLPK_doublecomplex *vl, __CLPK_integer *ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *
	ldvr, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztgex2_(__CLPK_logical *wantq, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, 
	__CLPK_integer *j1, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztgexc_(__CLPK_logical *wantq, __CLPK_logical *wantz, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *z__, __CLPK_integer *ldz, 
	__CLPK_integer *ifst, __CLPK_integer *ilst, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztgsen_(__CLPK_integer *ijob, __CLPK_logical *wantq, __CLPK_logical *wantz, 
	__CLPK_logical *select, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublecomplex *alpha, __CLPK_doublecomplex *
	beta, __CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *z__, __CLPK_integer *
	ldz, __CLPK_integer *m, __CLPK_doublereal *pl, __CLPK_doublereal *pr, __CLPK_doublereal *dif, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *liwork, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztgsja_(char *jobu, char *jobv, char *jobq, __CLPK_integer *m, 
	__CLPK_integer *p, __CLPK_integer *n, __CLPK_integer *k, __CLPK_integer *l, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, __CLPK_doublereal *tola, 
	__CLPK_doublereal *tolb, __CLPK_doublereal *alpha, __CLPK_doublereal *beta, __CLPK_doublecomplex *
	u, __CLPK_integer *ldu, __CLPK_doublecomplex *v, __CLPK_integer *ldv, __CLPK_doublecomplex *q, 
	__CLPK_integer *ldq, __CLPK_doublecomplex *work, __CLPK_integer *ncycle, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztgsna_(char *job, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer 
	*ldb, __CLPK_doublecomplex *vl, __CLPK_integer *ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *
	ldvr, __CLPK_doublereal *s, __CLPK_doublereal *dif, __CLPK_integer *mm, __CLPK_integer *m, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztgsy2_(char *trans, __CLPK_integer *ijob, __CLPK_integer *m, __CLPK_integer *
	n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *d__, __CLPK_integer *ldd, 
	__CLPK_doublecomplex *e, __CLPK_integer *lde, __CLPK_doublecomplex *f, __CLPK_integer *ldf, 
	__CLPK_doublereal *scale, __CLPK_doublereal *rdsum, __CLPK_doublereal *rdscal, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztgsyl_(char *trans, __CLPK_integer *ijob, __CLPK_integer *m, __CLPK_integer *
	n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *d__, __CLPK_integer *ldd, 
	__CLPK_doublecomplex *e, __CLPK_integer *lde, __CLPK_doublecomplex *f, __CLPK_integer *ldf, 
	__CLPK_doublereal *scale, __CLPK_doublereal *dif, __CLPK_doublecomplex *work, __CLPK_integer *
	lwork, __CLPK_integer *iwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztpcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_doublecomplex *ap, __CLPK_doublereal *rcond, __CLPK_doublecomplex *work, __CLPK_doublereal 
	*rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztprfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, __CLPK_doublereal *berr, 
	__CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztptri_(char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_doublecomplex *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztptrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *b, __CLPK_integer *ldb, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztpttf_(char *transr, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *ap, __CLPK_doublecomplex *arf, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztpttr_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrcon_(char *norm, char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublereal *rcond, __CLPK_doublecomplex *
	work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrevc_(char *side, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_doublecomplex *t, __CLPK_integer *ldt, __CLPK_doublecomplex *vl, 
	__CLPK_integer *ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *ldvr, __CLPK_integer *mm, __CLPK_integer 
	*m, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrexc_(char *compq, __CLPK_integer *n, __CLPK_doublecomplex *t, 
	__CLPK_integer *ldt, __CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_integer *ifst, __CLPK_integer *
	ilst, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrrfs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_doublecomplex *x, __CLPK_integer *ldx, __CLPK_doublereal *ferr, 
	__CLPK_doublereal *berr, __CLPK_doublecomplex *work, __CLPK_doublereal *rwork, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrsen_(char *job, char *compq, __CLPK_logical *select, __CLPK_integer 
	*n, __CLPK_doublecomplex *t, __CLPK_integer *ldt, __CLPK_doublecomplex *q, __CLPK_integer *ldq, 
	__CLPK_doublecomplex *w, __CLPK_integer *m, __CLPK_doublereal *s, __CLPK_doublereal *sep, 
	__CLPK_doublecomplex *work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrsna_(char *job, char *howmny, __CLPK_logical *select, 
	__CLPK_integer *n, __CLPK_doublecomplex *t, __CLPK_integer *ldt, __CLPK_doublecomplex *vl, 
	__CLPK_integer *ldvl, __CLPK_doublecomplex *vr, __CLPK_integer *ldvr, __CLPK_doublereal *s, 
	__CLPK_doublereal *sep, __CLPK_integer *mm, __CLPK_integer *m, __CLPK_doublecomplex *work, 
	__CLPK_integer *ldwork, __CLPK_doublereal *rwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrsyl_(char *trana, char *tranb, __CLPK_integer *isgn, __CLPK_integer 
	*m, __CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublereal *scale, 
	__CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrti2_(char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrtri_(char *uplo, char *diag, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrtrs_(char *uplo, char *trans, char *diag, __CLPK_integer *n, 
	__CLPK_integer *nrhs, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *b, 
	__CLPK_integer *ldb, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrttf_(char *transr, char *uplo, __CLPK_integer *n, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *arf, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztrttp_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *ap, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztzrqf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ztzrzf_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zung2l_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zung2r_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zungbr_(char *vect, __CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunghr_(__CLPK_integer *n, __CLPK_integer *ilo, __CLPK_integer *ihi, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zungl2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunglq_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zungql_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zungqr_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zungr2_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zungrq_(__CLPK_integer *m, __CLPK_integer *n, __CLPK_integer *k, 
	__CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zungtr_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *a, 
	__CLPK_integer *lda, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunm2l_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunm2r_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmbr_(char *vect, char *side, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex 
	*tau, __CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *
	lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmhr_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *ilo, __CLPK_integer *ihi, __CLPK_doublecomplex *a, __CLPK_integer *lda, 
	__CLPK_doublecomplex *tau, __CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *
	work, __CLPK_integer *lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunml2_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmlq_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmql_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmqr_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmr2_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmr3_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_integer *l, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex 
	*tau, __CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *
	info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmrq_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmrz_(char *side, char *trans, __CLPK_integer *m, __CLPK_integer *n, 
	__CLPK_integer *k, __CLPK_integer *l, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex 
	*tau, __CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *
	lwork, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zunmtr_(char *side, char *uplo, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_doublecomplex *a, __CLPK_integer *lda, __CLPK_doublecomplex *tau, 
	__CLPK_doublecomplex *c__, __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *lwork, 
	 __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zupgtr_(char *uplo, __CLPK_integer *n, __CLPK_doublecomplex *ap, 
	__CLPK_doublecomplex *tau, __CLPK_doublecomplex *q, __CLPK_integer *ldq, __CLPK_doublecomplex *
	work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int zupmtr_(char *side, char *uplo, char *trans, __CLPK_integer *m, 
	__CLPK_integer *n, __CLPK_doublecomplex *ap, __CLPK_doublecomplex *tau, __CLPK_doublecomplex *c__, 
	 __CLPK_integer *ldc, __CLPK_doublecomplex *work, __CLPK_integer *info) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlamc1_(__CLPK_integer *beta, __CLPK_integer *t, __CLPK_logical *rnd, __CLPK_logical 
	*ieee1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int ilaver_(__CLPK_integer *vers_major__, __CLPK_integer *vers_minor__, 
	__CLPK_integer *vers_patch__) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slamch_(char *cmach) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slamc1_(__CLPK_integer *beta, __CLPK_integer *t, __CLPK_logical *rnd, __CLPK_logical 
	*ieee1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slamc2_(__CLPK_integer *beta, __CLPK_integer *t, __CLPK_logical *rnd, __CLPK_real *
		    eps, __CLPK_integer *emin, __CLPK_real *rmin, __CLPK_integer *emax, __CLPK_real *rmax) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal slamc3_(__CLPK_real *a, __CLPK_real *b) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slamc4_(__CLPK_integer *emin, __CLPK_real *start, __CLPK_integer *base) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int slamc5_(__CLPK_integer *beta, __CLPK_integer *p, __CLPK_integer *emin,
		    __CLPK_logical *ieee, __CLPK_integer *emax, __CLPK_real *rmax) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);


__CLPK_doublereal dlamch_(char *cmach) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlamc1_(__CLPK_integer *beta, __CLPK_integer *t, __CLPK_logical *rnd, __CLPK_logical
		    *ieee1) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlamc2_(__CLPK_integer *beta, __CLPK_integer *t, __CLPK_logical *rnd,
		    __CLPK_doublereal *eps, __CLPK_integer *emin, __CLPK_doublereal *rmin, __CLPK_integer *emax,
			    __CLPK_doublereal *rmax) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_doublereal dlamc3_(__CLPK_doublereal *a, __CLPK_doublereal *b) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlamc4_(__CLPK_integer *emin, __CLPK_doublereal *start, __CLPK_integer *base) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

int dlamc5_(__CLPK_integer *beta, __CLPK_integer *p, __CLPK_integer *emin,
		    __CLPK_logical *ieee, __CLPK_integer *emax, __CLPK_doublereal *rmax) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

__CLPK_integer ilaenv_(__CLPK_integer *ispec, char *name__, char *opts, __CLPK_integer *n1, 
	__CLPK_integer *n2, __CLPK_integer *n3, __CLPK_integer *n4) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

    
#ifdef __cplusplus
}
#endif
#endif /* __CLAPACK_H */
