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
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wstrict-prototypes"
    typedef __CLPK_logical 	(*__CLPK_L_fp)();
#pragma clang diagnostic pop
    
    typedef int 		__CLPK_ftnlen;
#else
    typedef long int 	__CLPK_integer;
    typedef long int 	__CLPK_logical;
    typedef float 		__CLPK_real;
    typedef double 		__CLPK_doublereal;
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wstrict-prototypes"
    typedef __CLPK_logical 	(*__CLPK_L_fp)();
#pragma clang diagnostic pop
    
    typedef long int 	__CLPK_ftnlen;
#endif

typedef struct { __CLPK_real r, i; } __CLPK_complex;
typedef struct { __CLPK_doublereal r, i; } __CLPK_doublecomplex;

#include <stdint.h>
#if __has_include(<os/availability.h>)
# include <os/availability.h>
#else // __has_include(<os/availability.h>)
# undef API_AVAILABLE
# define API_AVAILABLE(...) /* Nothing */
#endif // __has_include(<os/availability.h>)

int cbdsqr_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__ncvt,
        __CLPK_integer *__nru, __CLPK_integer *__ncc, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_complex *__vt, __CLPK_integer *__ldvt,
        __CLPK_complex *__u, __CLPK_integer *__ldu, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbbrd_(char *__vect, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__ncc, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_complex *__ab, __CLPK_integer *__ldab, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_complex *__q, __CLPK_integer *__ldq,
        __CLPK_complex *__pt, __CLPK_integer *__ldpt, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbcon_(char *__norm, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbequ_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_real *__rowcnd,
        __CLPK_real *__colcnd, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbequb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_real *__rowcnd,
        __CLPK_real *__colcnd, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbrfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_integer *__nrhs, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__afb, __CLPK_integer *__ldafb,
        __CLPK_integer *__ipiv, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbsv_(__CLPK_integer *__n, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_integer *__nrhs, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbsvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__kl, __CLPK_integer *__ku, __CLPK_integer *__nrhs,
        __CLPK_complex *__ab, __CLPK_integer *__ldab, __CLPK_complex *__afb,
        __CLPK_integer *__ldafb, __CLPK_integer *__ipiv, char *__equed,
        __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__rcond, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbtf2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbtrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgbtrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_integer *__nrhs, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgebak_(char *__job, char *__side, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__scale,
        __CLPK_integer *__m, __CLPK_complex *__v, __CLPK_integer *__ldv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgebal_(char *__job, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__scale,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgebd2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_complex *__tauq, __CLPK_complex *__taup, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgebrd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_complex *__tauq, __CLPK_complex *__taup, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgecon_(char *__norm, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeequ_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__r__, __CLPK_real *__c__,
        __CLPK_real *__rowcnd, __CLPK_real *__colcnd, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeequb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__r__, __CLPK_real *__c__,
        __CLPK_real *__rowcnd, __CLPK_real *__colcnd, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgees_(char *__jobvs, char *__sort, __CLPK_L_fp __select,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__sdim, __CLPK_complex *__w, __CLPK_complex *__vs,
        __CLPK_integer *__ldvs, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeesx_(char *__jobvs, char *__sort, __CLPK_L_fp __select, char *__sense,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__sdim, __CLPK_complex *__w, __CLPK_complex *__vs,
        __CLPK_integer *__ldvs, __CLPK_real *__rconde, __CLPK_real *__rcondv,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeev_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__w,
        __CLPK_complex *__vl, __CLPK_integer *__ldvl, __CLPK_complex *__vr,
        __CLPK_integer *__ldvr, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeevx_(char *__balanc, char *__jobvl, char *__jobvr, char *__sense,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__w, __CLPK_complex *__vl, __CLPK_integer *__ldvl,
        __CLPK_complex *__vr, __CLPK_integer *__ldvr, __CLPK_integer *__ilo,
        __CLPK_integer *__ihi, __CLPK_real *__scale, __CLPK_real *__abnrm,
        __CLPK_real *__rconde, __CLPK_real *__rcondv, __CLPK_complex *__work,
        __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgegs_(char *__jobvsl, char *__jobvsr, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__alpha, __CLPK_complex *__beta,
        __CLPK_complex *__vsl, __CLPK_integer *__ldvsl, __CLPK_complex *__vsr,
        __CLPK_integer *__ldvsr, __CLPK_complex *__work,
        __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgegv_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__alpha, __CLPK_complex *__beta,
        __CLPK_complex *__vl, __CLPK_integer *__ldvl, __CLPK_complex *__vr,
        __CLPK_integer *__ldvr, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgehd2_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgehrd_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgelq2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgelqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgels_(char *__trans, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgelsd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_real *__s, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgelss_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_real *__s, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgelsx_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_integer *__jpvt, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgelsy_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_integer *__jpvt, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeql2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeqlf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeqp3_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_complex *__tau,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeqpf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_complex *__tau,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeqr2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgeqrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgerfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgerq2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgerqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgesc2_(__CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__rhs, __CLPK_integer *__ipiv, __CLPK_integer *__jpiv,
        __CLPK_real *__scale)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgesdd_(char *__jobz, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_real *__s,
        __CLPK_complex *__u, __CLPK_integer *__ldu, __CLPK_complex *__vt,
        __CLPK_integer *__ldvt, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgesv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgesvd_(char *__jobu, char *__jobvt, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_real *__s, __CLPK_complex *__u, __CLPK_integer *__ldu,
        __CLPK_complex *__vt, __CLPK_integer *__ldvt, __CLPK_complex *__work,
        __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgesvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__af, __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        char *__equed, __CLPK_real *__r__, __CLPK_real *__c__,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__x,
        __CLPK_integer *__ldx, __CLPK_real *__rcond, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgetc2_(__CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_integer *__jpiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgetf2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgetrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgetri_(__CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgetrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggbak_(char *__job, char *__side, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__lscale,
        __CLPK_real *__rscale, __CLPK_integer *__m, __CLPK_complex *__v,
        __CLPK_integer *__ldv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggbal_(char *__job, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__lscale,
        __CLPK_real *__rscale, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgges_(char *__jobvsl, char *__jobvsr, char *__sort, __CLPK_L_fp __selctg,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_integer *__sdim,
        __CLPK_complex *__alpha, __CLPK_complex *__beta, __CLPK_complex *__vsl,
        __CLPK_integer *__ldvsl, __CLPK_complex *__vsr, __CLPK_integer *__ldvsr,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggesx_(char *__jobvsl, char *__jobvsr, char *__sort, __CLPK_L_fp __selctg,
        char *__sense, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__sdim, __CLPK_complex *__alpha, __CLPK_complex *__beta,
        __CLPK_complex *__vsl, __CLPK_integer *__ldvsl, __CLPK_complex *__vsr,
        __CLPK_integer *__ldvsr, __CLPK_real *__rconde, __CLPK_real *__rcondv,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggev_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__alpha, __CLPK_complex *__beta,
        __CLPK_complex *__vl, __CLPK_integer *__ldvl, __CLPK_complex *__vr,
        __CLPK_integer *__ldvr, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggevx_(char *__balanc, char *__jobvl, char *__jobvr, char *__sense,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__alpha,
        __CLPK_complex *__beta, __CLPK_complex *__vl, __CLPK_integer *__ldvl,
        __CLPK_complex *__vr, __CLPK_integer *__ldvr, __CLPK_integer *__ilo,
        __CLPK_integer *__ihi, __CLPK_real *__lscale, __CLPK_real *__rscale,
        __CLPK_real *__abnrm, __CLPK_real *__bbnrm, __CLPK_real *__rconde,
        __CLPK_real *__rcondv, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork, __CLPK_integer *__iwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggglm_(__CLPK_integer *__n, __CLPK_integer *__m, __CLPK_integer *__p,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__d__, __CLPK_complex *__x,
        __CLPK_complex *__y, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgghrd_(char *__compq, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__q, __CLPK_integer *__ldq, __CLPK_complex *__z__,
        __CLPK_integer *__ldz,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgglse_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__p,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__c__, __CLPK_complex *__d__,
        __CLPK_complex *__x, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggqrf_(__CLPK_integer *__n, __CLPK_integer *__m, __CLPK_integer *__p,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__taua,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__taub,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggrqf_(__CLPK_integer *__m, __CLPK_integer *__p, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__taua,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__taub,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggsvd_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__p, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_real *__alpha,
        __CLPK_real *__beta, __CLPK_complex *__u, __CLPK_integer *__ldu,
        __CLPK_complex *__v, __CLPK_integer *__ldv, __CLPK_complex *__q,
        __CLPK_integer *__ldq, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cggsvp_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__p, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_real *__tola, __CLPK_real *__tolb, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_complex *__u, __CLPK_integer *__ldu,
        __CLPK_complex *__v, __CLPK_integer *__ldv, __CLPK_complex *__q,
        __CLPK_integer *__ldq, __CLPK_integer *__iwork, __CLPK_real *__rwork,
        __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgtcon_(char *__norm, __CLPK_integer *__n, __CLPK_complex *__dl,
        __CLPK_complex *__d__, __CLPK_complex *__du, __CLPK_complex *__du2,
        __CLPK_integer *__ipiv, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgtrfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__dl, __CLPK_complex *__d__, __CLPK_complex *__du,
        __CLPK_complex *__dlf, __CLPK_complex *__df, __CLPK_complex *__duf,
        __CLPK_complex *__du2, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgtsv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_complex *__dl,
        __CLPK_complex *__d__, __CLPK_complex *__du, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgtsvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__dl, __CLPK_complex *__d__,
        __CLPK_complex *__du, __CLPK_complex *__dlf, __CLPK_complex *__df,
        __CLPK_complex *__duf, __CLPK_complex *__du2, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__x,
        __CLPK_integer *__ldx, __CLPK_real *__rcond, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgttrf_(__CLPK_integer *__n, __CLPK_complex *__dl, __CLPK_complex *__d__,
        __CLPK_complex *__du, __CLPK_complex *__du2, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgttrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__dl, __CLPK_complex *__d__, __CLPK_complex *__du,
        __CLPK_complex *__du2, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cgtts2_(__CLPK_integer *__itrans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__dl, __CLPK_complex *__d__,
        __CLPK_complex *__du, __CLPK_complex *__du2, __CLPK_integer *__ipiv,
        __CLPK_complex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__w, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__w, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_complex *__q, __CLPK_integer *__ldq, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_complex *__z__, __CLPK_integer *__ldz, __CLPK_complex *__work,
        __CLPK_real *__rwork, __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbgst_(char *__vect, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__bb, __CLPK_integer *__ldbb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbgv_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__bb, __CLPK_integer *__ldbb,
        __CLPK_real *__w, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbgvd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__bb, __CLPK_integer *__ldbb,
        __CLPK_real *__w, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbgvx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__bb, __CLPK_integer *__ldbb,
        __CLPK_complex *__q, __CLPK_integer *__ldq, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_complex *__z__, __CLPK_integer *__ldz, __CLPK_complex *__work,
        __CLPK_real *__rwork, __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chbtrd_(char *__vect, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_complex *__q,
        __CLPK_integer *__ldq, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int checon_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_real *__anorm,
        __CLPK_real *__rcond, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cheequb_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__s, __CLPK_real *__scond,
        __CLPK_real *__amax, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cheev_(char *__jobz, char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__w, __CLPK_complex *__work,
        __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cheevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_real *__w,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cheevr_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_complex *__z__, __CLPK_integer *__ldz, __CLPK_integer *__isuppz,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cheevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_complex *__z__, __CLPK_integer *__ldz, __CLPK_complex *__work,
        __CLPK_integer *__lwork, __CLPK_real *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chegs2_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chegst_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chegv_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_real *__w,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chegvd_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_real *__w,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chegvx_(__CLPK_integer *__itype, char *__jobz, char *__range, char *__uplo,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_complex *__z__, __CLPK_integer *__ldz, __CLPK_complex *__work,
        __CLPK_integer *__lwork, __CLPK_real *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cherfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chesv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chesvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__af, __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__x,
        __CLPK_integer *__ldx, __CLPK_real *__rcond, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chetd2_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_complex *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chetf2_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chetrd_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_complex *__tau, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chetrf_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chetri_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chetrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chfrk_(char *__transr, char *__uplo, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_real *__alpha, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__beta,
        __CLPK_complex *__c__)
API_AVAILABLE(macos(10.2), ios(4.0));

int chgeqz_(char *__job, char *__compq, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_complex *__h__,
        __CLPK_integer *__ldh, __CLPK_complex *__t, __CLPK_integer *__ldt,
        __CLPK_complex *__alpha, __CLPK_complex *__beta, __CLPK_complex *__q,
        __CLPK_integer *__ldq, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

void chla_transtype__(char *__ret_val, __CLPK_ftnlen __ret_val_len,
        __CLPK_integer *__trans)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpcon_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_integer *__ipiv, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__ap, __CLPK_real *__w, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__ap, __CLPK_real *__w, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork, __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__ap, __CLPK_real *__vl, __CLPK_real *__vu,
        __CLPK_integer *__il, __CLPK_integer *__iu, __CLPK_real *__abstol,
        __CLPK_integer *__m, __CLPK_real *__w, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpgst_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__ap, __CLPK_complex *__bp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpgv_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_complex *__ap, __CLPK_complex *__bp,
        __CLPK_real *__w, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpgvd_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_complex *__ap, __CLPK_complex *__bp,
        __CLPK_real *__w, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpgvx_(__CLPK_integer *__itype, char *__jobz, char *__range, char *__uplo,
        __CLPK_integer *__n, __CLPK_complex *__ap, __CLPK_complex *__bp,
        __CLPK_real *__vl, __CLPK_real *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_real *__abstol, __CLPK_integer *__m,
        __CLPK_real *__w, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_real *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_complex *__afp, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__x,
        __CLPK_integer *__ldx, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chpsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__ap, __CLPK_complex *__afp,
        __CLPK_integer *__ipiv, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_real *__rcond,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chptrd_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_complex *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chptri_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_integer *__ipiv, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chsein_(char *__side, char *__eigsrc, char *__initv,
        __CLPK_logical *__select, __CLPK_integer *__n, __CLPK_complex *__h__,
        __CLPK_integer *__ldh, __CLPK_complex *__w, __CLPK_complex *__vl,
        __CLPK_integer *__ldvl, __CLPK_complex *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__mm, __CLPK_integer *__m, __CLPK_complex *__work,
        __CLPK_real *__rwork, __CLPK_integer *__ifaill,
        __CLPK_integer *__ifailr,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int chseqr_(char *__job, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_complex *__h__,
        __CLPK_integer *__ldh, __CLPK_complex *__w, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clabrd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_complex *__tauq, __CLPK_complex *__taup,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_complex *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int clacgv_(__CLPK_integer *__n, __CLPK_complex *__x,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int clacn2_(__CLPK_integer *__n, __CLPK_complex *__v, __CLPK_complex *__x,
        __CLPK_real *__est, __CLPK_integer *__kase,
        __CLPK_integer *__isave)
API_AVAILABLE(macos(10.2), ios(4.0));

int clacon_(__CLPK_integer *__n, __CLPK_complex *__v, __CLPK_complex *__x,
        __CLPK_real *__est,
        __CLPK_integer *__kase)
API_AVAILABLE(macos(10.2), ios(4.0));

int clacp2_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int clacpy_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int clacrm_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__c__, __CLPK_integer *__ldc,
        __CLPK_real *__rwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int clacrt_(__CLPK_integer *__n, __CLPK_complex *__cx, __CLPK_integer *__incx,
        __CLPK_complex *__cy, __CLPK_integer *__incy, __CLPK_complex *__c__,
        __CLPK_complex *__s)
API_AVAILABLE(macos(10.2), ios(4.0));

void cladiv_(__CLPK_complex *__ret_val, __CLPK_complex *__x,
        __CLPK_complex *__y)
API_AVAILABLE(macos(10.2), ios(4.0));

int claed0_(__CLPK_integer *__qsiz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_complex *__q, __CLPK_integer *__ldq,
        __CLPK_complex *__qstore, __CLPK_integer *__ldqs, __CLPK_real *__rwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int claed7_(__CLPK_integer *__n, __CLPK_integer *__cutpnt,
        __CLPK_integer *__qsiz, __CLPK_integer *__tlvls,
        __CLPK_integer *__curlvl, __CLPK_integer *__curpbm, __CLPK_real *__d__,
        __CLPK_complex *__q, __CLPK_integer *__ldq, __CLPK_real *__rho,
        __CLPK_integer *__indxq, __CLPK_real *__qstore, __CLPK_integer *__qptr,
        __CLPK_integer *__prmptr, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_real *__givnum, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int claed8_(__CLPK_integer *__k, __CLPK_integer *__n, __CLPK_integer *__qsiz,
        __CLPK_complex *__q, __CLPK_integer *__ldq, __CLPK_real *__d__,
        __CLPK_real *__rho, __CLPK_integer *__cutpnt, __CLPK_real *__z__,
        __CLPK_real *__dlamda, __CLPK_complex *__q2, __CLPK_integer *__ldq2,
        __CLPK_real *__w, __CLPK_integer *__indxp, __CLPK_integer *__indx,
        __CLPK_integer *__indxq, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_real *__givnum,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int claein_(__CLPK_logical *__rightv, __CLPK_logical *__noinit,
        __CLPK_integer *__n, __CLPK_complex *__h__, __CLPK_integer *__ldh,
        __CLPK_complex *__w, __CLPK_complex *__v, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_real *__rwork, __CLPK_real *__eps3,
        __CLPK_real *__smlnum,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int claesy_(__CLPK_complex *__a, __CLPK_complex *__b, __CLPK_complex *__c__,
        __CLPK_complex *__rt1, __CLPK_complex *__rt2, __CLPK_complex *__evscal,
        __CLPK_complex *__cs1,
        __CLPK_complex *__sn1)
API_AVAILABLE(macos(10.2), ios(4.0));

int claev2_(__CLPK_complex *__a, __CLPK_complex *__b, __CLPK_complex *__c__,
        __CLPK_real *__rt1, __CLPK_real *__rt2, __CLPK_real *__cs1,
        __CLPK_complex *__sn1)
API_AVAILABLE(macos(10.2), ios(4.0));

int clag2z_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__sa,
        __CLPK_integer *__ldsa, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clags2_(__CLPK_logical *__upper, __CLPK_real *__a1, __CLPK_complex *__a2,
        __CLPK_real *__a3, __CLPK_real *__b1, __CLPK_complex *__b2,
        __CLPK_real *__b3, __CLPK_real *__csu, __CLPK_complex *__snu,
        __CLPK_real *__csv, __CLPK_complex *__snv, __CLPK_real *__csq,
        __CLPK_complex *__snq)
API_AVAILABLE(macos(10.2), ios(4.0));

int clagtm_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__alpha, __CLPK_complex *__dl, __CLPK_complex *__d__,
        __CLPK_complex *__du, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__beta, __CLPK_complex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int clahef_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_integer *__kb, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_complex *__w, __CLPK_integer *__ldw,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clahqr_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_complex *__h__, __CLPK_integer *__ldh, __CLPK_complex *__w,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz, __CLPK_complex *__z__,
        __CLPK_integer *__ldz,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clahr2_(__CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__nb,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__t, __CLPK_integer *__ldt, __CLPK_complex *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int clahrd_(__CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__nb,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__t, __CLPK_integer *__ldt, __CLPK_complex *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int claic1_(__CLPK_integer *__job, __CLPK_integer *__j, __CLPK_complex *__x,
        __CLPK_real *__sest, __CLPK_complex *__w, __CLPK_complex *__gamma,
        __CLPK_real *__sestpr, __CLPK_complex *__s,
        __CLPK_complex *__c__)
API_AVAILABLE(macos(10.2), ios(4.0));

int clals0_(__CLPK_integer *__icompq, __CLPK_integer *__nl,
        __CLPK_integer *__nr, __CLPK_integer *__sqre, __CLPK_integer *__nrhs,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__bx,
        __CLPK_integer *__ldbx, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_integer *__ldgcol, __CLPK_real *__givnum,
        __CLPK_integer *__ldgnum, __CLPK_real *__poles, __CLPK_real *__difl,
        __CLPK_real *__difr, __CLPK_real *__z__, __CLPK_integer *__k,
        __CLPK_real *__c__, __CLPK_real *__s, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clalsa_(__CLPK_integer *__icompq, __CLPK_integer *__smlsiz,
        __CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__bx, __CLPK_integer *__ldbx,
        __CLPK_real *__u, __CLPK_integer *__ldu, __CLPK_real *__vt,
        __CLPK_integer *__k, __CLPK_real *__difl, __CLPK_real *__difr,
        __CLPK_real *__z__, __CLPK_real *__poles, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_integer *__ldgcol,
        __CLPK_integer *__perm, __CLPK_real *__givnum, __CLPK_real *__c__,
        __CLPK_real *__s, __CLPK_real *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clalsd_(char *__uplo, __CLPK_integer *__smlsiz, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clangb_(char *__norm, __CLPK_integer *__n,
        __CLPK_integer *__kl, __CLPK_integer *__ku, __CLPK_complex *__ab,
        __CLPK_integer *__ldab,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clange_(char *__norm, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clangt_(char *__norm, __CLPK_integer *__n,
        __CLPK_complex *__dl, __CLPK_complex *__d__,
        __CLPK_complex *__du)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clanhb_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clanhe_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clanhf_(char *__norm, char *__transr, char *__uplo,
        __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clanhp_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__ap,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clanhs_(char *__norm, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clanht_(char *__norm, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_complex *__e)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clansb_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clansp_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__ap,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clansy_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clantb_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__ab,
        __CLPK_integer *__ldab,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clantp_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal clantr_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int clapll_(__CLPK_integer *__n, __CLPK_complex *__x, __CLPK_integer *__incx,
        __CLPK_complex *__y, __CLPK_integer *__incy,
        __CLPK_real *__ssmin)
API_AVAILABLE(macos(10.2), ios(4.0));

int clapmt_(__CLPK_logical *__forwrd, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_integer *__k)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqgb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_real *__rowcnd,
        __CLPK_real *__colcnd, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqge_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__r__, __CLPK_real *__c__,
        __CLPK_real *__rowcnd, __CLPK_real *__colcnd, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqhb_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_complex *__ab, __CLPK_integer *__ldab, __CLPK_real *__s,
        __CLPK_real *__scond, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqhe_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__s, __CLPK_real *__scond,
        __CLPK_real *__amax, char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqhp_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqp2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__offset,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_integer *__jpvt,
        __CLPK_complex *__tau, __CLPK_real *__vn1, __CLPK_real *__vn2,
        __CLPK_complex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqps_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__offset,
        __CLPK_integer *__nb, __CLPK_integer *__kb, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_complex *__tau,
        __CLPK_real *__vn1, __CLPK_real *__vn2, __CLPK_complex *__auxv,
        __CLPK_complex *__f,
        __CLPK_integer *__ldf)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqr0_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_complex *__h__, __CLPK_integer *__ldh, __CLPK_complex *__w,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqr1_(__CLPK_integer *__n, __CLPK_complex *__h__, __CLPK_integer *__ldh,
        __CLPK_complex *__s1, __CLPK_complex *__s2,
        __CLPK_complex *__v)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqr2_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ktop, __CLPK_integer *__kbot,
        __CLPK_integer *__nw, __CLPK_complex *__h__, __CLPK_integer *__ldh,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__ns, __CLPK_integer *__nd,
        __CLPK_complex *__sh, __CLPK_complex *__v, __CLPK_integer *__ldv,
        __CLPK_integer *__nh, __CLPK_complex *__t, __CLPK_integer *__ldt,
        __CLPK_integer *__nv, __CLPK_complex *__wv, __CLPK_integer *__ldwv,
        __CLPK_complex *__work,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqr3_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ktop, __CLPK_integer *__kbot,
        __CLPK_integer *__nw, __CLPK_complex *__h__, __CLPK_integer *__ldh,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__ns, __CLPK_integer *__nd,
        __CLPK_complex *__sh, __CLPK_complex *__v, __CLPK_integer *__ldv,
        __CLPK_integer *__nh, __CLPK_complex *__t, __CLPK_integer *__ldt,
        __CLPK_integer *__nv, __CLPK_complex *__wv, __CLPK_integer *__ldwv,
        __CLPK_complex *__work,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqr4_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_complex *__h__, __CLPK_integer *__ldh, __CLPK_complex *__w,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqr5_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__kacc22, __CLPK_integer *__n, __CLPK_integer *__ktop,
        __CLPK_integer *__kbot, __CLPK_integer *__nshfts, __CLPK_complex *__s,
        __CLPK_complex *__h__, __CLPK_integer *__ldh, __CLPK_integer *__iloz,
        __CLPK_integer *__ihiz, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__v, __CLPK_integer *__ldv, __CLPK_complex *__u,
        __CLPK_integer *__ldu, __CLPK_integer *__nv, __CLPK_complex *__wv,
        __CLPK_integer *__ldwv, __CLPK_integer *__nh, __CLPK_complex *__wh,
        __CLPK_integer *__ldwh)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqsb_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_complex *__ab, __CLPK_integer *__ldab, __CLPK_real *__s,
        __CLPK_real *__scond, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqsp_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int claqsy_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__s, __CLPK_real *__scond,
        __CLPK_real *__amax, char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int clar1v_(__CLPK_integer *__n, __CLPK_integer *__b1, __CLPK_integer *__bn,
        __CLPK_real *__lambda, __CLPK_real *__d__, __CLPK_real *__l,
        __CLPK_real *__ld, __CLPK_real *__lld, __CLPK_real *__pivmin,
        __CLPK_real *__gaptol, __CLPK_complex *__z__, __CLPK_logical *__wantnc,
        __CLPK_integer *__negcnt, __CLPK_real *__ztz, __CLPK_real *__mingma,
        __CLPK_integer *__r__, __CLPK_integer *__isuppz, __CLPK_real *__nrminv,
        __CLPK_real *__resid, __CLPK_real *__rqcorr,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int clar2v_(__CLPK_integer *__n, __CLPK_complex *__x, __CLPK_complex *__y,
        __CLPK_complex *__z__, __CLPK_integer *__incx, __CLPK_real *__c__,
        __CLPK_complex *__s,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarcm_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__c__, __CLPK_integer *__ldc,
        __CLPK_real *__rwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarf_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__v, __CLPK_integer *__incv, __CLPK_complex *__tau,
        __CLPK_complex *__c__, __CLPK_integer *__ldc,
        __CLPK_complex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarfb_(char *__side, char *__trans, char *__direct, char *__storev,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__v, __CLPK_integer *__ldv, __CLPK_complex *__t,
        __CLPK_integer *__ldt, __CLPK_complex *__c__, __CLPK_integer *__ldc,
        __CLPK_complex *__work,
        __CLPK_integer *__ldwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarfg_(__CLPK_integer *__n, __CLPK_complex *__alpha, __CLPK_complex *__x,
        __CLPK_integer *__incx,
        __CLPK_complex *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarfp_(__CLPK_integer *__n, __CLPK_complex *__alpha, __CLPK_complex *__x,
        __CLPK_integer *__incx,
        __CLPK_complex *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarft_(char *__direct, char *__storev, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_complex *__v, __CLPK_integer *__ldv,
        __CLPK_complex *__tau, __CLPK_complex *__t,
        __CLPK_integer *__ldt)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarfx_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__v, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc,
        __CLPK_complex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int clargv_(__CLPK_integer *__n, __CLPK_complex *__x, __CLPK_integer *__incx,
        __CLPK_complex *__y, __CLPK_integer *__incy, __CLPK_real *__c__,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarnv_(__CLPK_integer *__idist, __CLPK_integer *__iseed,
        __CLPK_integer *__n,
        __CLPK_complex *__x)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarrv_(__CLPK_integer *__n, __CLPK_real *__vl, __CLPK_real *__vu,
        __CLPK_real *__d__, __CLPK_real *__l, __CLPK_real *__pivmin,
        __CLPK_integer *__isplit, __CLPK_integer *__m, __CLPK_integer *__dol,
        __CLPK_integer *__dou, __CLPK_real *__minrgp, __CLPK_real *__rtol1,
        __CLPK_real *__rtol2, __CLPK_real *__w, __CLPK_real *__werr,
        __CLPK_real *__wgap, __CLPK_integer *__iblock, __CLPK_integer *__indexw,
        __CLPK_real *__gers, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__isuppz, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarscl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_complex *__x,
        __CLPK_integer *__ldx)
API_AVAILABLE(macos(10.2), ios(4.0));

int clartg_(__CLPK_complex *__f, __CLPK_complex *__g, __CLPK_real *__cs,
        __CLPK_complex *__sn,
        __CLPK_complex *__r__)
API_AVAILABLE(macos(10.2), ios(4.0));

int clartv_(__CLPK_integer *__n, __CLPK_complex *__x, __CLPK_integer *__incx,
        __CLPK_complex *__y, __CLPK_integer *__incy, __CLPK_real *__c__,
        __CLPK_complex *__s,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarz_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__l, __CLPK_complex *__v, __CLPK_integer *__incv,
        __CLPK_complex *__tau, __CLPK_complex *__c__, __CLPK_integer *__ldc,
        __CLPK_complex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarzb_(char *__side, char *__trans, char *__direct, char *__storev,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_complex *__v, __CLPK_integer *__ldv,
        __CLPK_complex *__t, __CLPK_integer *__ldt, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__ldwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int clarzt_(char *__direct, char *__storev, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_complex *__v, __CLPK_integer *__ldv,
        __CLPK_complex *__tau, __CLPK_complex *__t,
        __CLPK_integer *__ldt)
API_AVAILABLE(macos(10.2), ios(4.0));

int clascl_(char *__type__, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_real *__cfrom, __CLPK_real *__cto, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clascl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_complex *__x,
        __CLPK_integer *__ldx)
API_AVAILABLE(macos(10.2), ios(4.0));

int claset_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__alpha, __CLPK_complex *__beta, __CLPK_complex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int clasr_(char *__side, char *__pivot, char *__direct, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__c__, __CLPK_real *__s,
        __CLPK_complex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int classq_(__CLPK_integer *__n, __CLPK_complex *__x, __CLPK_integer *__incx,
        __CLPK_real *__scale,
        __CLPK_real *__sumsq)
API_AVAILABLE(macos(10.2), ios(4.0));

int claswp_(__CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__k1, __CLPK_integer *__k2, __CLPK_integer *__ipiv,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int clasyf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_integer *__kb, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_complex *__w, __CLPK_integer *__ldw,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clatbs_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_integer *__kd, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__x, __CLPK_real *__scale,
        __CLPK_real *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clatdf_(__CLPK_integer *__ijob, __CLPK_integer *__n, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_complex *__rhs, __CLPK_real *__rdsum,
        __CLPK_real *__rdscal, __CLPK_integer *__ipiv,
        __CLPK_integer *__jpiv)
API_AVAILABLE(macos(10.2), ios(4.0));

int clatps_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_complex *__ap, __CLPK_complex *__x,
        __CLPK_real *__scale, __CLPK_real *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clatrd_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_real *__e,
        __CLPK_complex *__tau, __CLPK_complex *__w,
        __CLPK_integer *__ldw)
API_AVAILABLE(macos(10.2), ios(4.0));

int clatrs_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__x, __CLPK_real *__scale, __CLPK_real *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clatrz_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__l,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int clatzm_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__v, __CLPK_integer *__incv, __CLPK_complex *__tau,
        __CLPK_complex *__c1, __CLPK_complex *__c2, __CLPK_integer *__ldc,
        __CLPK_complex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int clauu2_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int clauum_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbcon_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_complex *__ab, __CLPK_integer *__ldab, __CLPK_real *__anorm,
        __CLPK_real *__rcond, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbequ_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_complex *__ab, __CLPK_integer *__ldab, __CLPK_real *__s,
        __CLPK_real *__scond, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_complex *__afb, __CLPK_integer *__ldafb, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbstf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__afb, __CLPK_integer *__ldafb,
        char *__equed, __CLPK_real *__s, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__rcond, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbtf2_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbtrf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpbtrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpftrf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpftri_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpftrs_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__a, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpocon_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpoequ_(__CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpoequb_(__CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cporfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__af,
        __CLPK_integer *__ldaf, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cposv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cposvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__af, __CLPK_integer *__ldaf, char *__equed,
        __CLPK_real *__s, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_real *__rcond,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpotf2_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpotrf_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpotri_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpotrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cppcon_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_real *__anorm, __CLPK_real *__rcond, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cppequ_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_complex *__afp, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cppsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cppsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__ap, __CLPK_complex *__afp,
        char *__equed, __CLPK_real *__s, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__rcond, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpptri_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpstf2_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__piv, __CLPK_integer *__rank,
        __CLPK_real *__tol, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpstrf_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__piv, __CLPK_integer *__rank,
        __CLPK_real *__tol, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cptcon_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_complex *__e,
        __CLPK_real *__anorm, __CLPK_real *__rcond, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpteqr_(char *__compz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cptrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__d__, __CLPK_complex *__e, __CLPK_real *__df,
        __CLPK_complex *__ef, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cptsv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_real *__d__,
        __CLPK_complex *__e, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cptsvx_(char *__fact, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__d__, __CLPK_complex *__e, __CLPK_real *__df,
        __CLPK_complex *__ef, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_real *__rcond,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpttrf_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_complex *__e,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cpttrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__d__, __CLPK_complex *__e, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cptts2_(__CLPK_integer *__iuplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__d__, __CLPK_complex *__e,
        __CLPK_complex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int crot_(__CLPK_integer *__n, __CLPK_complex *__cx, __CLPK_integer *__incx,
        __CLPK_complex *__cy, __CLPK_integer *__incy, __CLPK_real *__c__,
        __CLPK_complex *__s)
API_AVAILABLE(macos(10.2), ios(4.0));

int cspcon_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_integer *__ipiv, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cspmv_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__alpha,
        __CLPK_complex *__ap, __CLPK_complex *__x, __CLPK_integer *__incx,
        __CLPK_complex *__beta, __CLPK_complex *__y,
        __CLPK_integer *__incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int cspr_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__alpha,
        __CLPK_complex *__x, __CLPK_integer *__incx,
        __CLPK_complex *__ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int csprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_complex *__afp, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__x,
        __CLPK_integer *__ldx, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cspsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cspsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__ap, __CLPK_complex *__afp,
        __CLPK_integer *__ipiv, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_real *__rcond,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csptri_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_integer *__ipiv, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__ap, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csrscl_(__CLPK_integer *__n, __CLPK_real *__sa, __CLPK_complex *__sx,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int cstedc_(char *__compz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_complex *__work, __CLPK_integer *__lwork, __CLPK_real *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cstegr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_complex *__z__, __CLPK_integer *__ldz, __CLPK_integer *__isuppz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cstein_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_integer *__m, __CLPK_real *__w, __CLPK_integer *__iblock,
        __CLPK_integer *__isplit, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cstemr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_integer *__m, __CLPK_real *__w, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__nzc, __CLPK_integer *__isuppz,
        __CLPK_logical *__tryrac, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csteqr_(char *__compz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csycon_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_real *__anorm,
        __CLPK_real *__rcond, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csyequb_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_real *__s, __CLPK_real *__scond,
        __CLPK_real *__amax, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csymv_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__alpha,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__x,
        __CLPK_integer *__incx, __CLPK_complex *__beta, __CLPK_complex *__y,
        __CLPK_integer *__incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int csyr_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__alpha,
        __CLPK_complex *__x, __CLPK_integer *__incx, __CLPK_complex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int csyrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csysv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csysvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__af, __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__x,
        __CLPK_integer *__ldx, __CLPK_real *__rcond, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csytf2_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csytrf_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csytri_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int csytrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctbcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_complex *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__rcond, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctbrfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__x, __CLPK_integer *__ldx, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctbtrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_complex *__ab,
        __CLPK_integer *__ldab, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctfsm_(char *__transr, char *__side, char *__uplo, char *__trans,
        char *__diag, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__alpha, __CLPK_complex *__a, __CLPK_complex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctftri_(char *__transr, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_complex *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctfttp_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__arf, __CLPK_complex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctfttr_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__arf, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctgevc_(char *__side, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_complex *__s, __CLPK_integer *__lds,
        __CLPK_complex *__p, __CLPK_integer *__ldp, __CLPK_complex *__vl,
        __CLPK_integer *__ldvl, __CLPK_complex *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__mm, __CLPK_integer *__m, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctgex2_(__CLPK_logical *__wantq, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__q,
        __CLPK_integer *__ldq, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__j1,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctgexc_(__CLPK_logical *__wantq, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__q,
        __CLPK_integer *__ldq, __CLPK_complex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__ifst, __CLPK_integer *__ilst,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctgsen_(__CLPK_integer *__ijob, __CLPK_logical *__wantq,
        __CLPK_logical *__wantz, __CLPK_logical *__select, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__alpha, __CLPK_complex *__beta,
        __CLPK_complex *__q, __CLPK_integer *__ldq, __CLPK_complex *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__m, __CLPK_real *__pl,
        __CLPK_real *__pr, __CLPK_real *__dif, __CLPK_complex *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctgsja_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__p, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_real *__tola,
        __CLPK_real *__tolb, __CLPK_real *__alpha, __CLPK_real *__beta,
        __CLPK_complex *__u, __CLPK_integer *__ldu, __CLPK_complex *__v,
        __CLPK_integer *__ldv, __CLPK_complex *__q, __CLPK_integer *__ldq,
        __CLPK_complex *__work, __CLPK_integer *__ncycle,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctgsna_(char *__job, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__vl,
        __CLPK_integer *__ldvl, __CLPK_complex *__vr, __CLPK_integer *__ldvr,
        __CLPK_real *__s, __CLPK_real *__dif, __CLPK_integer *__mm,
        __CLPK_integer *__m, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctgsy2_(char *__trans, __CLPK_integer *__ijob, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__d__, __CLPK_integer *__ldd,
        __CLPK_complex *__e, __CLPK_integer *__lde, __CLPK_complex *__f,
        __CLPK_integer *__ldf, __CLPK_real *__scale, __CLPK_real *__rdsum,
        __CLPK_real *__rdscal,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctgsyl_(char *__trans, __CLPK_integer *__ijob, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__d__, __CLPK_integer *__ldd,
        __CLPK_complex *__e, __CLPK_integer *__lde, __CLPK_complex *__f,
        __CLPK_integer *__ldf, __CLPK_real *__scale, __CLPK_real *__dif,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctpcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_complex *__ap, __CLPK_real *__rcond, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctprfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__ap, __CLPK_complex *__b,
        __CLPK_integer *__ldb, __CLPK_complex *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_complex *__work,
        __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctptri_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_complex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctptrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__ap, __CLPK_complex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctpttf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__ap, __CLPK_complex *__arf,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctpttr_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_real *__rcond,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrevc_(char *__side, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_complex *__t, __CLPK_integer *__ldt,
        __CLPK_complex *__vl, __CLPK_integer *__ldvl, __CLPK_complex *__vr,
        __CLPK_integer *__ldvr, __CLPK_integer *__mm, __CLPK_integer *__m,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrexc_(char *__compq, __CLPK_integer *__n, __CLPK_complex *__t,
        __CLPK_integer *__ldt, __CLPK_complex *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__ifst, __CLPK_integer *__ilst,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrrfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb, __CLPK_complex *__x,
        __CLPK_integer *__ldx, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_complex *__work, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrsen_(char *__job, char *__compq, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_complex *__t, __CLPK_integer *__ldt,
        __CLPK_complex *__q, __CLPK_integer *__ldq, __CLPK_complex *__w,
        __CLPK_integer *__m, __CLPK_real *__s, __CLPK_real *__sep,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrsna_(char *__job, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_complex *__t, __CLPK_integer *__ldt,
        __CLPK_complex *__vl, __CLPK_integer *__ldvl, __CLPK_complex *__vr,
        __CLPK_integer *__ldvr, __CLPK_real *__s, __CLPK_real *__sep,
        __CLPK_integer *__mm, __CLPK_integer *__m, __CLPK_complex *__work,
        __CLPK_integer *__ldwork, __CLPK_real *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrsyl_(char *__trana, char *__tranb, __CLPK_integer *__isgn,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_complex *__c__, __CLPK_integer *__ldc, __CLPK_real *__scale,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrti2_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrtri_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrtrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrttf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__arf,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctrttp_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctzrqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ctzrzf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cung2l_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cung2r_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cungbr_(char *__vect, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__tau, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunghr_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cungl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunglq_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cungql_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cungqr_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cungr2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cungrq_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cungtr_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunm2l_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunm2r_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmbr_(char *__vect, char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmhr_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__c__, __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunml2_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmlq_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmql_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmqr_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmr2_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmr3_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__l,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__c__, __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmrq_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_complex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__tau, __CLPK_complex *__c__,
        __CLPK_integer *__ldc, __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmrz_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__l,
        __CLPK_complex *__a, __CLPK_integer *__lda, __CLPK_complex *__tau,
        __CLPK_complex *__c__, __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cunmtr_(char *__side, char *__uplo, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_complex *__a, __CLPK_integer *__lda,
        __CLPK_complex *__tau, __CLPK_complex *__c__, __CLPK_integer *__ldc,
        __CLPK_complex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cupgtr_(char *__uplo, __CLPK_integer *__n, __CLPK_complex *__ap,
        __CLPK_complex *__tau, __CLPK_complex *__q, __CLPK_integer *__ldq,
        __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int cupmtr_(char *__side, char *__uplo, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_complex *__ap, __CLPK_complex *__tau,
        __CLPK_complex *__c__, __CLPK_integer *__ldc, __CLPK_complex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dbdsdc_(char *__uplo, char *__compq, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__vt,
        __CLPK_integer *__ldvt, __CLPK_doublereal *__q, __CLPK_integer *__iq,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dbdsqr_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__ncvt,
        __CLPK_integer *__nru, __CLPK_integer *__ncc, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__vt, __CLPK_integer *__ldvt,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__c__,
        __CLPK_integer *__ldc, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ddisna_(char *__job, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__sep,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbbrd_(char *__vect, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__ncc, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_doublereal *__pt,
        __CLPK_integer *__ldpt, __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbcon_(char *__norm, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbequ_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__r__, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__rowcnd, __CLPK_doublereal *__colcnd,
        __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbequb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__r__, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__rowcnd, __CLPK_doublereal *__colcnd,
        __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbrfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_integer *__nrhs, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__afb,
        __CLPK_integer *__ldafb, __CLPK_integer *__ipiv, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbsv_(__CLPK_integer *__n, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbsvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__kl, __CLPK_integer *__ku, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__afb, __CLPK_integer *__ldafb,
        __CLPK_integer *__ipiv, char *__equed, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbtf2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbtrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgbtrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_integer *__nrhs, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_integer *__ipiv, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgebak_(char *__job, char *__side, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__scale, __CLPK_integer *__m, __CLPK_doublereal *__v,
        __CLPK_integer *__ldv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgebal_(char *__job, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__scale,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgebd2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__tauq, __CLPK_doublereal *__taup,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgebrd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__tauq, __CLPK_doublereal *__taup,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgecon_(char *__norm, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeequ_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rowcnd,
        __CLPK_doublereal *__colcnd, __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeequb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rowcnd,
        __CLPK_doublereal *__colcnd, __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgees_(char *__jobvs, char *__sort, __CLPK_L_fp __select,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__sdim, __CLPK_doublereal *__wr,
        __CLPK_doublereal *__wi, __CLPK_doublereal *__vs,
        __CLPK_integer *__ldvs, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeesx_(char *__jobvs, char *__sort, __CLPK_L_fp __select, char *__sense,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__sdim, __CLPK_doublereal *__wr,
        __CLPK_doublereal *__wi, __CLPK_doublereal *__vs,
        __CLPK_integer *__ldvs, __CLPK_doublereal *__rconde,
        __CLPK_doublereal *__rcondv, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeev_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__wr,
        __CLPK_doublereal *__wi, __CLPK_doublereal *__vl,
        __CLPK_integer *__ldvl, __CLPK_doublereal *__vr, __CLPK_integer *__ldvr,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeevx_(char *__balanc, char *__jobvl, char *__jobvr, char *__sense,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__wr, __CLPK_doublereal *__wi,
        __CLPK_doublereal *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublereal *__vr, __CLPK_integer *__ldvr, __CLPK_integer *__ilo,
        __CLPK_integer *__ihi, __CLPK_doublereal *__scale,
        __CLPK_doublereal *__abnrm, __CLPK_doublereal *__rconde,
        __CLPK_doublereal *__rcondv, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgegs_(char *__jobvsl, char *__jobvsr, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__alphar,
        __CLPK_doublereal *__alphai, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__vsl, __CLPK_integer *__ldvsl,
        __CLPK_doublereal *__vsr, __CLPK_integer *__ldvsr,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgegv_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__alphar,
        __CLPK_doublereal *__alphai, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublereal *__vr, __CLPK_integer *__ldvr,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgehd2_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgehrd_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgejsv_(char *__joba, char *__jobu, char *__jobv, char *__jobr,
        char *__jobt, char *__jobp, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__sva,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__v,
        __CLPK_integer *__ldv, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgelq2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgelqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgels_(char *__trans, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgelsd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__s,
        __CLPK_doublereal *__rcond, __CLPK_integer *__rank,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgelss_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__s,
        __CLPK_doublereal *__rcond, __CLPK_integer *__rank,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgelsx_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_integer *__jpvt,
        __CLPK_doublereal *__rcond, __CLPK_integer *__rank,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgelsy_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_integer *__jpvt,
        __CLPK_doublereal *__rcond, __CLPK_integer *__rank,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeql2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeqlf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeqp3_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeqpf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeqr2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgeqrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgerfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgerq2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgerqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgesc2_(__CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__rhs, __CLPK_integer *__ipiv,
        __CLPK_integer *__jpiv,
        __CLPK_doublereal *__scale)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgesdd_(char *__jobz, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__vt,
        __CLPK_integer *__ldvt, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgesv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgesvd_(char *__jobu, char *__jobvt, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__s, __CLPK_doublereal *__u, __CLPK_integer *__ldu,
        __CLPK_doublereal *__vt, __CLPK_integer *__ldvt,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgesvj_(char *__joba, char *__jobu, char *__jobv, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__sva, __CLPK_integer *__mv, __CLPK_doublereal *__v,
        __CLPK_integer *__ldv, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgesvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__af, __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        char *__equed, __CLPK_doublereal *__r__, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgetc2_(__CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_integer *__jpiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgetf2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgetrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgetri_(__CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgetrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggbak_(char *__job, char *__side, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__lscale, __CLPK_doublereal *__rscale,
        __CLPK_integer *__m, __CLPK_doublereal *__v, __CLPK_integer *__ldv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggbal_(char *__job, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__lscale, __CLPK_doublereal *__rscale,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgges_(char *__jobvsl, char *__jobvsr, char *__sort, __CLPK_L_fp __selctg,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_integer *__sdim,
        __CLPK_doublereal *__alphar, __CLPK_doublereal *__alphai,
        __CLPK_doublereal *__beta, __CLPK_doublereal *__vsl,
        __CLPK_integer *__ldvsl, __CLPK_doublereal *__vsr,
        __CLPK_integer *__ldvsr, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggesx_(char *__jobvsl, char *__jobvsr, char *__sort, __CLPK_L_fp __selctg,
        char *__sense, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__sdim, __CLPK_doublereal *__alphar,
        __CLPK_doublereal *__alphai, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__vsl, __CLPK_integer *__ldvsl,
        __CLPK_doublereal *__vsr, __CLPK_integer *__ldvsr,
        __CLPK_doublereal *__rconde, __CLPK_doublereal *__rcondv,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggev_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__alphar,
        __CLPK_doublereal *__alphai, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublereal *__vr, __CLPK_integer *__ldvr,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggevx_(char *__balanc, char *__jobvl, char *__jobvr, char *__sense,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__alphar, __CLPK_doublereal *__alphai,
        __CLPK_doublereal *__beta, __CLPK_doublereal *__vl,
        __CLPK_integer *__ldvl, __CLPK_doublereal *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__lscale, __CLPK_doublereal *__rscale,
        __CLPK_doublereal *__abnrm, __CLPK_doublereal *__bbnrm,
        __CLPK_doublereal *__rconde, __CLPK_doublereal *__rcondv,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggglm_(__CLPK_integer *__n, __CLPK_integer *__m, __CLPK_integer *__p,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__d__, __CLPK_doublereal *__x,
        __CLPK_doublereal *__y, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgghrd_(char *__compq, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_doublereal *__z__,
        __CLPK_integer *__ldz,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgglse_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__p,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__x,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggqrf_(__CLPK_integer *__n, __CLPK_integer *__m, __CLPK_integer *__p,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__taua, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__taub,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggrqf_(__CLPK_integer *__m, __CLPK_integer *__p, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__taua, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__taub,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggsvd_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__p, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__v,
        __CLPK_integer *__ldv, __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dggsvp_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__p, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__tola, __CLPK_doublereal *__tolb,
        __CLPK_integer *__k, __CLPK_integer *__l, __CLPK_doublereal *__u,
        __CLPK_integer *__ldu, __CLPK_doublereal *__v, __CLPK_integer *__ldv,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_integer *__iwork,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgsvj0_(char *__jobv, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__sva, __CLPK_integer *__mv, __CLPK_doublereal *__v,
        __CLPK_integer *__ldv, __CLPK_doublereal *__eps,
        __CLPK_doublereal *__sfmin, __CLPK_doublereal *__tol,
        __CLPK_integer *__nsweep, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgsvj1_(char *__jobv, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__n1, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__sva,
        __CLPK_integer *__mv, __CLPK_doublereal *__v, __CLPK_integer *__ldv,
        __CLPK_doublereal *__eps, __CLPK_doublereal *__sfmin,
        __CLPK_doublereal *__tol, __CLPK_integer *__nsweep,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgtcon_(char *__norm, __CLPK_integer *__n, __CLPK_doublereal *__dl,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__du,
        __CLPK_doublereal *__du2, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgtrfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__dl, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__du, __CLPK_doublereal *__dlf,
        __CLPK_doublereal *__df, __CLPK_doublereal *__duf,
        __CLPK_doublereal *__du2, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgtsv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_doublereal *__dl,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__du,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgtsvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__dl,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__du,
        __CLPK_doublereal *__dlf, __CLPK_doublereal *__df,
        __CLPK_doublereal *__duf, __CLPK_doublereal *__du2,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgttrf_(__CLPK_integer *__n, __CLPK_doublereal *__dl,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__du,
        __CLPK_doublereal *__du2, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgttrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__dl, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__du, __CLPK_doublereal *__du2,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dgtts2_(__CLPK_integer *__itrans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__dl,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__du,
        __CLPK_doublereal *__du2, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int dhgeqz_(char *__job, char *__compq, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_doublereal *__h__,
        __CLPK_integer *__ldh, __CLPK_doublereal *__t, __CLPK_integer *__ldt,
        __CLPK_doublereal *__alphar, __CLPK_doublereal *__alphai,
        __CLPK_doublereal *__beta, __CLPK_doublereal *__q,
        __CLPK_integer *__ldq, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dhsein_(char *__side, char *__eigsrc, char *__initv,
        __CLPK_logical *__select, __CLPK_integer *__n, __CLPK_doublereal *__h__,
        __CLPK_integer *__ldh, __CLPK_doublereal *__wr, __CLPK_doublereal *__wi,
        __CLPK_doublereal *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublereal *__vr, __CLPK_integer *__ldvr, __CLPK_integer *__mm,
        __CLPK_integer *__m, __CLPK_doublereal *__work,
        __CLPK_integer *__ifaill, __CLPK_integer *__ifailr,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dhseqr_(char *__job, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_doublereal *__h__,
        __CLPK_integer *__ldh, __CLPK_doublereal *__wr, __CLPK_doublereal *__wi,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));


        __CLPK_logical disnan_(__CLPK_doublereal *__din)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlabad_(__CLPK_doublereal *__small,
        __CLPK_doublereal *__large)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlabrd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__tauq,
        __CLPK_doublereal *__taup, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlacn2_(__CLPK_integer *__n, __CLPK_doublereal *__v, __CLPK_doublereal *__x,
        __CLPK_integer *__isgn, __CLPK_doublereal *__est,
        __CLPK_integer *__kase,
        __CLPK_integer *__isave)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlacon_(__CLPK_integer *__n, __CLPK_doublereal *__v, __CLPK_doublereal *__x,
        __CLPK_integer *__isgn, __CLPK_doublereal *__est,
        __CLPK_integer *__kase)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlacpy_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int dladiv_(__CLPK_doublereal *__a, __CLPK_doublereal *__b,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__p,
        __CLPK_doublereal *__q)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlae2_(__CLPK_doublereal *__a, __CLPK_doublereal *__b,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rt1,
        __CLPK_doublereal *__rt2)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaebz_(__CLPK_integer *__ijob, __CLPK_integer *__nitmax,
        __CLPK_integer *__n, __CLPK_integer *__mmax, __CLPK_integer *__minp,
        __CLPK_integer *__nbmin, __CLPK_doublereal *__abstol,
        __CLPK_doublereal *__reltol, __CLPK_doublereal *__pivmin,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__e2, __CLPK_integer *__nval,
        __CLPK_doublereal *__ab, __CLPK_doublereal *__c__,
        __CLPK_integer *__mout, __CLPK_integer *__nab,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed0_(__CLPK_integer *__icompq, __CLPK_integer *__qsiz,
        __CLPK_integer *__n, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_doublereal *__qstore, __CLPK_integer *__ldqs,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed1_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_integer *__indxq,
        __CLPK_doublereal *__rho, __CLPK_integer *__cutpnt,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed2_(__CLPK_integer *__k, __CLPK_integer *__n, __CLPK_integer *__n1,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__indxq, __CLPK_doublereal *__rho,
        __CLPK_doublereal *__z__, __CLPK_doublereal *__dlamda,
        __CLPK_doublereal *__w, __CLPK_doublereal *__q2, __CLPK_integer *__indx,
        __CLPK_integer *__indxc, __CLPK_integer *__indxp,
        __CLPK_integer *__coltyp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed3_(__CLPK_integer *__k, __CLPK_integer *__n, __CLPK_integer *__n1,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_doublereal *__rho, __CLPK_doublereal *__dlamda,
        __CLPK_doublereal *__q2, __CLPK_integer *__indx, __CLPK_integer *__ctot,
        __CLPK_doublereal *__w, __CLPK_doublereal *__s,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed4_(__CLPK_integer *__n, __CLPK_integer *__i__,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__delta, __CLPK_doublereal *__rho,
        __CLPK_doublereal *__dlam,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed5_(__CLPK_integer *__i__, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__z__, __CLPK_doublereal *__delta,
        __CLPK_doublereal *__rho,
        __CLPK_doublereal *__dlam)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed6_(__CLPK_integer *__kniter, __CLPK_logical *__orgati,
        __CLPK_doublereal *__rho, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__z__, __CLPK_doublereal *__finit,
        __CLPK_doublereal *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed7_(__CLPK_integer *__icompq, __CLPK_integer *__n,
        __CLPK_integer *__qsiz, __CLPK_integer *__tlvls,
        __CLPK_integer *__curlvl, __CLPK_integer *__curpbm,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__indxq, __CLPK_doublereal *__rho,
        __CLPK_integer *__cutpnt, __CLPK_doublereal *__qstore,
        __CLPK_integer *__qptr, __CLPK_integer *__prmptr,
        __CLPK_integer *__perm, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_doublereal *__givnum,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed8_(__CLPK_integer *__icompq, __CLPK_integer *__k, __CLPK_integer *__n,
        __CLPK_integer *__qsiz, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_integer *__indxq,
        __CLPK_doublereal *__rho, __CLPK_integer *__cutpnt,
        __CLPK_doublereal *__z__, __CLPK_doublereal *__dlamda,
        __CLPK_doublereal *__q2, __CLPK_integer *__ldq2, __CLPK_doublereal *__w,
        __CLPK_integer *__perm, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_doublereal *__givnum,
        __CLPK_integer *__indxp, __CLPK_integer *__indx,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaed9_(__CLPK_integer *__k, __CLPK_integer *__kstart,
        __CLPK_integer *__kstop, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_doublereal *__rho,
        __CLPK_doublereal *__dlamda, __CLPK_doublereal *__w,
        __CLPK_doublereal *__s, __CLPK_integer *__lds,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaeda_(__CLPK_integer *__n, __CLPK_integer *__tlvls,
        __CLPK_integer *__curlvl, __CLPK_integer *__curpbm,
        __CLPK_integer *__prmptr, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_doublereal *__givnum, __CLPK_doublereal *__q,
        __CLPK_integer *__qptr, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__ztemp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaein_(__CLPK_logical *__rightv, __CLPK_logical *__noinit,
        __CLPK_integer *__n, __CLPK_doublereal *__h__, __CLPK_integer *__ldh,
        __CLPK_doublereal *__wr, __CLPK_doublereal *__wi,
        __CLPK_doublereal *__vr, __CLPK_doublereal *__vi,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__work, __CLPK_doublereal *__eps3,
        __CLPK_doublereal *__smlnum, __CLPK_doublereal *__bignum,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaev2_(__CLPK_doublereal *__a, __CLPK_doublereal *__b,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rt1,
        __CLPK_doublereal *__rt2, __CLPK_doublereal *__cs1,
        __CLPK_doublereal *__sn1)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaexc_(__CLPK_logical *__wantq, __CLPK_integer *__n,
        __CLPK_doublereal *__t, __CLPK_integer *__ldt, __CLPK_doublereal *__q,
        __CLPK_integer *__ldq, __CLPK_integer *__j1, __CLPK_integer *__n1,
        __CLPK_integer *__n2, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlag2_(__CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__safmin, __CLPK_doublereal *__scale1,
        __CLPK_doublereal *__scale2, __CLPK_doublereal *__wr1,
        __CLPK_doublereal *__wr2,
        __CLPK_doublereal *__wi)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlag2s_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_real *__sa, __CLPK_integer *__ldsa,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlags2_(__CLPK_logical *__upper, __CLPK_doublereal *__a1,
        __CLPK_doublereal *__a2, __CLPK_doublereal *__a3,
        __CLPK_doublereal *__b1, __CLPK_doublereal *__b2,
        __CLPK_doublereal *__b3, __CLPK_doublereal *__csu,
        __CLPK_doublereal *__snu, __CLPK_doublereal *__csv,
        __CLPK_doublereal *__snv, __CLPK_doublereal *__csq,
        __CLPK_doublereal *__snq)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlagtf_(__CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_doublereal *__lambda, __CLPK_doublereal *__b,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__tol,
        __CLPK_doublereal *__d__, __CLPK_integer *__in,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlagtm_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__dl,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__du,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__beta, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlagts_(__CLPK_integer *__job, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_doublereal *__b, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__d__, __CLPK_integer *__in, __CLPK_doublereal *__y,
        __CLPK_doublereal *__tol,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlagv2_(__CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__alphar, __CLPK_doublereal *__alphai,
        __CLPK_doublereal *__beta, __CLPK_doublereal *__csl,
        __CLPK_doublereal *__snl, __CLPK_doublereal *__csr,
        __CLPK_doublereal *__snr)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlahqr_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__h__, __CLPK_integer *__ldh,
        __CLPK_doublereal *__wr, __CLPK_doublereal *__wi,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlahr2_(__CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__nb,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__t, __CLPK_integer *__ldt, __CLPK_doublereal *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlahrd_(__CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__nb,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__t, __CLPK_integer *__ldt, __CLPK_doublereal *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaic1_(__CLPK_integer *__job, __CLPK_integer *__j, __CLPK_doublereal *__x,
        __CLPK_doublereal *__sest, __CLPK_doublereal *__w,
        __CLPK_doublereal *__gamma, __CLPK_doublereal *__sestpr,
        __CLPK_doublereal *__s,
        __CLPK_doublereal *__c__)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_logical dlaisnan_(__CLPK_doublereal *__din1,
        __CLPK_doublereal *__din2)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaln2_(__CLPK_logical *__ltrans, __CLPK_integer *__na,
        __CLPK_integer *__nw, __CLPK_doublereal *__smin,
        __CLPK_doublereal *__ca, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__d1, __CLPK_doublereal *__d2,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__wr,
        __CLPK_doublereal *__wi, __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__scale, __CLPK_doublereal *__xnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlals0_(__CLPK_integer *__icompq, __CLPK_integer *__nl,
        __CLPK_integer *__nr, __CLPK_integer *__sqre, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__bx,
        __CLPK_integer *__ldbx, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_integer *__ldgcol, __CLPK_doublereal *__givnum,
        __CLPK_integer *__ldgnum, __CLPK_doublereal *__poles,
        __CLPK_doublereal *__difl, __CLPK_doublereal *__difr,
        __CLPK_doublereal *__z__, __CLPK_integer *__k, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__s, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlalsa_(__CLPK_integer *__icompq, __CLPK_integer *__smlsiz,
        __CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__bx, __CLPK_integer *__ldbx,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__vt,
        __CLPK_integer *__k, __CLPK_doublereal *__difl,
        __CLPK_doublereal *__difr, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__poles, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_integer *__ldgcol,
        __CLPK_integer *__perm, __CLPK_doublereal *__givnum,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlalsd_(char *__uplo, __CLPK_integer *__smlsiz, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__rcond, __CLPK_integer *__rank,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlamrg_(__CLPK_integer *__n1, __CLPK_integer *__n2, __CLPK_doublereal *__a,
        __CLPK_integer *__dtrd1, __CLPK_integer *__dtrd2,
        __CLPK_integer *__index)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer dlaneg_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__lld, __CLPK_doublereal *__sigma,
        __CLPK_doublereal *__pivmin,
        __CLPK_integer *__r__)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlangb_(char *__norm, __CLPK_integer *__n,
        __CLPK_integer *__kl, __CLPK_integer *__ku, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlange_(char *__norm, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlangt_(char *__norm, __CLPK_integer *__n,
        __CLPK_doublereal *__dl, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__du)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlanhs_(char *__norm, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlansb_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlansf_(char *__norm, char *__transr, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlansp_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__ap,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlanst_(char *__norm, __CLPK_integer *__n,
        __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlansy_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlantb_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlantp_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlantr_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlanv2_(__CLPK_doublereal *__a, __CLPK_doublereal *__b,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__rt1r, __CLPK_doublereal *__rt1i,
        __CLPK_doublereal *__rt2r, __CLPK_doublereal *__rt2i,
        __CLPK_doublereal *__cs,
        __CLPK_doublereal *__sn)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlapll_(__CLPK_integer *__n, __CLPK_doublereal *__x, __CLPK_integer *__incx,
        __CLPK_doublereal *__y, __CLPK_integer *__incy,
        __CLPK_doublereal *__ssmin)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlapmt_(__CLPK_logical *__forwrd, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_integer *__k)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlapy2_(__CLPK_doublereal *__x,
        __CLPK_doublereal *__y)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlapy3_(__CLPK_doublereal *__x, __CLPK_doublereal *__y,
        __CLPK_doublereal *__z__)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqgb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__r__, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__rowcnd, __CLPK_doublereal *__colcnd,
        __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqge_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rowcnd,
        __CLPK_doublereal *__colcnd, __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqp2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__offset,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_integer *__jpvt,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__vn1,
        __CLPK_doublereal *__vn2,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqps_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__offset,
        __CLPK_integer *__nb, __CLPK_integer *__kb, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__vn1, __CLPK_doublereal *__vn2,
        __CLPK_doublereal *__auxv, __CLPK_doublereal *__f,
        __CLPK_integer *__ldf)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqr0_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__h__, __CLPK_integer *__ldh,
        __CLPK_doublereal *__wr, __CLPK_doublereal *__wi,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqr1_(__CLPK_integer *__n, __CLPK_doublereal *__h__,
        __CLPK_integer *__ldh, __CLPK_doublereal *__sr1,
        __CLPK_doublereal *__si1, __CLPK_doublereal *__sr2,
        __CLPK_doublereal *__si2,
        __CLPK_doublereal *__v)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqr2_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ktop, __CLPK_integer *__kbot,
        __CLPK_integer *__nw, __CLPK_doublereal *__h__, __CLPK_integer *__ldh,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz, __CLPK_integer *__ns,
        __CLPK_integer *__nd, __CLPK_doublereal *__sr, __CLPK_doublereal *__si,
        __CLPK_doublereal *__v, __CLPK_integer *__ldv, __CLPK_integer *__nh,
        __CLPK_doublereal *__t, __CLPK_integer *__ldt, __CLPK_integer *__nv,
        __CLPK_doublereal *__wv, __CLPK_integer *__ldwv,
        __CLPK_doublereal *__work,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqr3_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ktop, __CLPK_integer *__kbot,
        __CLPK_integer *__nw, __CLPK_doublereal *__h__, __CLPK_integer *__ldh,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz, __CLPK_integer *__ns,
        __CLPK_integer *__nd, __CLPK_doublereal *__sr, __CLPK_doublereal *__si,
        __CLPK_doublereal *__v, __CLPK_integer *__ldv, __CLPK_integer *__nh,
        __CLPK_doublereal *__t, __CLPK_integer *__ldt, __CLPK_integer *__nv,
        __CLPK_doublereal *__wv, __CLPK_integer *__ldwv,
        __CLPK_doublereal *__work,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqr4_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__h__, __CLPK_integer *__ldh,
        __CLPK_doublereal *__wr, __CLPK_doublereal *__wi,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqr5_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__kacc22, __CLPK_integer *__n, __CLPK_integer *__ktop,
        __CLPK_integer *__kbot, __CLPK_integer *__nshfts,
        __CLPK_doublereal *__sr, __CLPK_doublereal *__si,
        __CLPK_doublereal *__h__, __CLPK_integer *__ldh, __CLPK_integer *__iloz,
        __CLPK_integer *__ihiz, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__v, __CLPK_integer *__ldv, __CLPK_doublereal *__u,
        __CLPK_integer *__ldu, __CLPK_integer *__nv, __CLPK_doublereal *__wv,
        __CLPK_integer *__ldwv, __CLPK_integer *__nh, __CLPK_doublereal *__wh,
        __CLPK_integer *__ldwh)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqsb_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublereal *__ab, __CLPK_integer *__ldab, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqsp_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqsy_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaqtr_(__CLPK_logical *__ltran, __CLPK_logical *__l__CLPK_real,
        __CLPK_integer *__n, __CLPK_doublereal *__t, __CLPK_integer *__ldt,
        __CLPK_doublereal *__b, __CLPK_doublereal *__w,
        __CLPK_doublereal *__scale, __CLPK_doublereal *__x,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlar1v_(__CLPK_integer *__n, __CLPK_integer *__b1, __CLPK_integer *__bn,
        __CLPK_doublereal *__lambda, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__l, __CLPK_doublereal *__ld,
        __CLPK_doublereal *__lld, __CLPK_doublereal *__pivmin,
        __CLPK_doublereal *__gaptol, __CLPK_doublereal *__z__,
        __CLPK_logical *__wantnc, __CLPK_integer *__negcnt,
        __CLPK_doublereal *__ztz, __CLPK_doublereal *__mingma,
        __CLPK_integer *__r__, __CLPK_integer *__isuppz,
        __CLPK_doublereal *__nrminv, __CLPK_doublereal *__resid,
        __CLPK_doublereal *__rqcorr,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlar2v_(__CLPK_integer *__n, __CLPK_doublereal *__x, __CLPK_doublereal *__y,
        __CLPK_doublereal *__z__, __CLPK_integer *__incx,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarf_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__v, __CLPK_integer *__incv,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__c__,
        __CLPK_integer *__ldc,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarfb_(char *__side, char *__trans, char *__direct, char *__storev,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__v, __CLPK_integer *__ldv, __CLPK_doublereal *__t,
        __CLPK_integer *__ldt, __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__ldwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarfg_(__CLPK_integer *__n, __CLPK_doublereal *__alpha,
        __CLPK_doublereal *__x, __CLPK_integer *__incx,
        __CLPK_doublereal *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarfp_(__CLPK_integer *__n, __CLPK_doublereal *__alpha,
        __CLPK_doublereal *__x, __CLPK_integer *__incx,
        __CLPK_doublereal *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarft_(char *__direct, char *__storev, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublereal *__v, __CLPK_integer *__ldv,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__t,
        __CLPK_integer *__ldt)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarfx_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__v, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlargv_(__CLPK_integer *__n, __CLPK_doublereal *__x, __CLPK_integer *__incx,
        __CLPK_doublereal *__y, __CLPK_integer *__incy,
        __CLPK_doublereal *__c__,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarnv_(__CLPK_integer *__idist, __CLPK_integer *__iseed,
        __CLPK_integer *__n,
        __CLPK_doublereal *__x)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarra_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__e2,
        __CLPK_doublereal *__spltol, __CLPK_doublereal *__tnrm,
        __CLPK_integer *__nsplit, __CLPK_integer *__isplit,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarrb_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__lld, __CLPK_integer *__ifirst,
        __CLPK_integer *__ilast, __CLPK_doublereal *__rtol1,
        __CLPK_doublereal *__rtol2, __CLPK_integer *__offset,
        __CLPK_doublereal *__w, __CLPK_doublereal *__wgap,
        __CLPK_doublereal *__werr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork, __CLPK_doublereal *__pivmin,
        __CLPK_doublereal *__spdiam, __CLPK_integer *__twist,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarrc_(char *__jobt, __CLPK_integer *__n, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__pivmin,
        __CLPK_integer *__eigcnt, __CLPK_integer *__lcnt,
        __CLPK_integer *__rcnt,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarrd_(char *__range, char *__order, __CLPK_integer *__n,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__gers,
        __CLPK_doublereal *__reltol, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__e2,
        __CLPK_doublereal *__pivmin, __CLPK_integer *__nsplit,
        __CLPK_integer *__isplit, __CLPK_integer *__m, __CLPK_doublereal *__w,
        __CLPK_doublereal *__werr, __CLPK_doublereal *__wl,
        __CLPK_doublereal *__wu, __CLPK_integer *__iblock,
        __CLPK_integer *__indexw, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarre_(char *__range, __CLPK_integer *__n, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__e2, __CLPK_doublereal *__rtol1,
        __CLPK_doublereal *__rtol2, __CLPK_doublereal *__spltol,
        __CLPK_integer *__nsplit, __CLPK_integer *__isplit, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__werr,
        __CLPK_doublereal *__wgap, __CLPK_integer *__iblock,
        __CLPK_integer *__indexw, __CLPK_doublereal *__gers,
        __CLPK_doublereal *__pivmin, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarrf_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__l, __CLPK_doublereal *__ld,
        __CLPK_integer *__clstrt, __CLPK_integer *__clend,
        __CLPK_doublereal *__w, __CLPK_doublereal *__wgap,
        __CLPK_doublereal *__werr, __CLPK_doublereal *__spdiam,
        __CLPK_doublereal *__clgapl, __CLPK_doublereal *__clgapr,
        __CLPK_doublereal *__pivmin, __CLPK_doublereal *__sigma,
        __CLPK_doublereal *__dplus, __CLPK_doublereal *__lplus,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarrj_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e2, __CLPK_integer *__ifirst,
        __CLPK_integer *__ilast, __CLPK_doublereal *__rtol,
        __CLPK_integer *__offset, __CLPK_doublereal *__w,
        __CLPK_doublereal *__werr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork, __CLPK_doublereal *__pivmin,
        __CLPK_doublereal *__spdiam,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarrk_(__CLPK_integer *__n, __CLPK_integer *__iw, __CLPK_doublereal *__gl,
        __CLPK_doublereal *__gu, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e2, __CLPK_doublereal *__pivmin,
        __CLPK_doublereal *__reltol, __CLPK_doublereal *__w,
        __CLPK_doublereal *__werr,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarrr_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarrv_(__CLPK_integer *__n, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__l, __CLPK_doublereal *__pivmin,
        __CLPK_integer *__isplit, __CLPK_integer *__m, __CLPK_integer *__dol,
        __CLPK_integer *__dou, __CLPK_doublereal *__minrgp,
        __CLPK_doublereal *__rtol1, __CLPK_doublereal *__rtol2,
        __CLPK_doublereal *__w, __CLPK_doublereal *__werr,
        __CLPK_doublereal *__wgap, __CLPK_integer *__iblock,
        __CLPK_integer *__indexw, __CLPK_doublereal *__gers,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__isuppz, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarscl2_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlartg_(__CLPK_doublereal *__f, __CLPK_doublereal *__g,
        __CLPK_doublereal *__cs, __CLPK_doublereal *__sn,
        __CLPK_doublereal *__r__)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlartv_(__CLPK_integer *__n, __CLPK_doublereal *__x, __CLPK_integer *__incx,
        __CLPK_doublereal *__y, __CLPK_integer *__incy,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaruv_(__CLPK_integer *__iseed, __CLPK_integer *__n,
        __CLPK_doublereal *__x)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarz_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__l, __CLPK_doublereal *__v, __CLPK_integer *__incv,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__c__,
        __CLPK_integer *__ldc,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarzb_(char *__side, char *__trans, char *__direct, char *__storev,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_doublereal *__v, __CLPK_integer *__ldv,
        __CLPK_doublereal *__t, __CLPK_integer *__ldt, __CLPK_doublereal *__c__,
        __CLPK_integer *__ldc, __CLPK_doublereal *__work,
        __CLPK_integer *__ldwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlarzt_(char *__direct, char *__storev, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublereal *__v, __CLPK_integer *__ldv,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__t,
        __CLPK_integer *__ldt)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlas2_(__CLPK_doublereal *__f, __CLPK_doublereal *__g,
        __CLPK_doublereal *__h__, __CLPK_doublereal *__ssmin,
        __CLPK_doublereal *__ssmax)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlascl_(char *__type__, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_doublereal *__cfrom, __CLPK_doublereal *__cto,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlascl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__x,
        __CLPK_integer *__ldx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd0_(__CLPK_integer *__n, __CLPK_integer *__sqre,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__vt,
        __CLPK_integer *__ldvt, __CLPK_integer *__smlsiz,
        __CLPK_integer *__iwork, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd1_(__CLPK_integer *__nl, __CLPK_integer *__nr, __CLPK_integer *__sqre,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__alpha,
        __CLPK_doublereal *__beta, __CLPK_doublereal *__u,
        __CLPK_integer *__ldu, __CLPK_doublereal *__vt, __CLPK_integer *__ldvt,
        __CLPK_integer *__idxq, __CLPK_integer *__iwork,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd2_(__CLPK_integer *__nl, __CLPK_integer *__nr, __CLPK_integer *__sqre,
        __CLPK_integer *__k, __CLPK_doublereal *__d__, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__vt,
        __CLPK_integer *__ldvt, __CLPK_doublereal *__dsigma,
        __CLPK_doublereal *__u2, __CLPK_integer *__ldu2,
        __CLPK_doublereal *__vt2, __CLPK_integer *__ldvt2,
        __CLPK_integer *__idxp, __CLPK_integer *__idx, __CLPK_integer *__idxc,
        __CLPK_integer *__idxq, __CLPK_integer *__coltyp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd3_(__CLPK_integer *__nl, __CLPK_integer *__nr, __CLPK_integer *__sqre,
        __CLPK_integer *__k, __CLPK_doublereal *__d__, __CLPK_doublereal *__q,
        __CLPK_integer *__ldq, __CLPK_doublereal *__dsigma,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__u2,
        __CLPK_integer *__ldu2, __CLPK_doublereal *__vt, __CLPK_integer *__ldvt,
        __CLPK_doublereal *__vt2, __CLPK_integer *__ldvt2,
        __CLPK_integer *__idxc, __CLPK_integer *__ctot,
        __CLPK_doublereal *__z__,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd4_(__CLPK_integer *__n, __CLPK_integer *__i__,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__delta, __CLPK_doublereal *__rho,
        __CLPK_doublereal *__sigma, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd5_(__CLPK_integer *__i__, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__z__, __CLPK_doublereal *__delta,
        __CLPK_doublereal *__rho, __CLPK_doublereal *__dsigma,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd6_(__CLPK_integer *__icompq, __CLPK_integer *__nl,
        __CLPK_integer *__nr, __CLPK_integer *__sqre, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__vf, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__beta,
        __CLPK_integer *__idxq, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_integer *__ldgcol, __CLPK_doublereal *__givnum,
        __CLPK_integer *__ldgnum, __CLPK_doublereal *__poles,
        __CLPK_doublereal *__difl, __CLPK_doublereal *__difr,
        __CLPK_doublereal *__z__, __CLPK_integer *__k, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__s, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd7_(__CLPK_integer *__icompq, __CLPK_integer *__nl,
        __CLPK_integer *__nr, __CLPK_integer *__sqre, __CLPK_integer *__k,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__zw, __CLPK_doublereal *__vf,
        __CLPK_doublereal *__vfw, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vlw, __CLPK_doublereal *__alpha,
        __CLPK_doublereal *__beta, __CLPK_doublereal *__dsigma,
        __CLPK_integer *__idx, __CLPK_integer *__idxp, __CLPK_integer *__idxq,
        __CLPK_integer *__perm, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_integer *__ldgcol,
        __CLPK_doublereal *__givnum, __CLPK_integer *__ldgnum,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasd8_(__CLPK_integer *__icompq, __CLPK_integer *__k,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__vf, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__difl, __CLPK_doublereal *__difr,
        __CLPK_integer *__lddifr, __CLPK_doublereal *__dsigma,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasda_(__CLPK_integer *__icompq, __CLPK_integer *__smlsiz,
        __CLPK_integer *__n, __CLPK_integer *__sqre, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__u, __CLPK_integer *__ldu,
        __CLPK_doublereal *__vt, __CLPK_integer *__k, __CLPK_doublereal *__difl,
        __CLPK_doublereal *__difr, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__poles, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_integer *__ldgcol,
        __CLPK_integer *__perm, __CLPK_doublereal *__givnum,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasdq_(char *__uplo, __CLPK_integer *__sqre, __CLPK_integer *__n,
        __CLPK_integer *__ncvt, __CLPK_integer *__nru, __CLPK_integer *__ncc,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__vt, __CLPK_integer *__ldvt, __CLPK_doublereal *__u,
        __CLPK_integer *__ldu, __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasdt_(__CLPK_integer *__n, __CLPK_integer *__lvl, __CLPK_integer *__nd,
        __CLPK_integer *__inode, __CLPK_integer *__ndiml,
        __CLPK_integer *__ndimr,
        __CLPK_integer *__msub)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaset_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasq1_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasq2_(__CLPK_integer *__n, __CLPK_doublereal *__z__,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasq3_(__CLPK_integer *__i0, __CLPK_integer *__n0,
        __CLPK_doublereal *__z__, __CLPK_integer *__pp,
        __CLPK_doublereal *__dmin__, __CLPK_doublereal *__sigma,
        __CLPK_doublereal *__desig, __CLPK_doublereal *__qmax,
        __CLPK_integer *__nfail, __CLPK_integer *__iter, __CLPK_integer *__ndiv,
        __CLPK_logical *__ieee, __CLPK_integer *__ttype,
        __CLPK_doublereal *__dmin1, __CLPK_doublereal *__dmin2,
        __CLPK_doublereal *__dn, __CLPK_doublereal *__dn1,
        __CLPK_doublereal *__dn2, __CLPK_doublereal *__g,
        __CLPK_doublereal *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasq4_(__CLPK_integer *__i0, __CLPK_integer *__n0,
        __CLPK_doublereal *__z__, __CLPK_integer *__pp, __CLPK_integer *__n0in,
        __CLPK_doublereal *__dmin__, __CLPK_doublereal *__dmin1,
        __CLPK_doublereal *__dmin2, __CLPK_doublereal *__dn,
        __CLPK_doublereal *__dn1, __CLPK_doublereal *__dn2,
        __CLPK_doublereal *__tau, __CLPK_integer *__ttype,
        __CLPK_doublereal *__g)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasq5_(__CLPK_integer *__i0, __CLPK_integer *__n0,
        __CLPK_doublereal *__z__, __CLPK_integer *__pp,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__dmin__,
        __CLPK_doublereal *__dmin1, __CLPK_doublereal *__dmin2,
        __CLPK_doublereal *__dn, __CLPK_doublereal *__dnm1,
        __CLPK_doublereal *__dnm2,
        __CLPK_logical *__ieee)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasq6_(__CLPK_integer *__i0, __CLPK_integer *__n0,
        __CLPK_doublereal *__z__, __CLPK_integer *__pp,
        __CLPK_doublereal *__dmin__, __CLPK_doublereal *__dmin1,
        __CLPK_doublereal *__dmin2, __CLPK_doublereal *__dn,
        __CLPK_doublereal *__dnm1,
        __CLPK_doublereal *__dnm2)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasr_(char *__side, char *__pivot, char *__direct, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_doublereal *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasrt_(char *__id, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlassq_(__CLPK_integer *__n, __CLPK_doublereal *__x, __CLPK_integer *__incx,
        __CLPK_doublereal *__scale,
        __CLPK_doublereal *__sumsq)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasv2_(__CLPK_doublereal *__f, __CLPK_doublereal *__g,
        __CLPK_doublereal *__h__, __CLPK_doublereal *__ssmin,
        __CLPK_doublereal *__ssmax, __CLPK_doublereal *__snr,
        __CLPK_doublereal *__csr, __CLPK_doublereal *__snl,
        __CLPK_doublereal *__csl)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlaswp_(__CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__k1, __CLPK_integer *__k2, __CLPK_integer *__ipiv,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasy2_(__CLPK_logical *__ltranl, __CLPK_logical *__ltranr,
        __CLPK_integer *__isgn, __CLPK_integer *__n1, __CLPK_integer *__n2,
        __CLPK_doublereal *__tl, __CLPK_integer *__ldtl,
        __CLPK_doublereal *__tr, __CLPK_integer *__ldtr, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__scale,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__xnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlasyf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_integer *__kb, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__w, __CLPK_integer *__ldw,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlat2s_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_real *__sa, __CLPK_integer *__ldsa,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlatbs_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_integer *__kd, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__x,
        __CLPK_doublereal *__scale, __CLPK_doublereal *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlatdf_(__CLPK_integer *__ijob, __CLPK_integer *__n,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__rhs, __CLPK_doublereal *__rdsum,
        __CLPK_doublereal *__rdscal, __CLPK_integer *__ipiv,
        __CLPK_integer *__jpiv)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlatps_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_doublereal *__ap, __CLPK_doublereal *__x,
        __CLPK_doublereal *__scale, __CLPK_doublereal *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlatrd_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__e,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__w,
        __CLPK_integer *__ldw)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlatrs_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__x, __CLPK_doublereal *__scale,
        __CLPK_doublereal *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlatrz_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__l,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlatzm_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__v, __CLPK_integer *__incv,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__c1,
        __CLPK_doublereal *__c2, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlauu2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlauum_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dopgtr_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dopmtr_(char *__side, char *__uplo, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__ap, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorg2l_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorg2r_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorgbr_(char *__vect, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorghr_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorgl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorglq_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorgql_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorgqr_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorgr2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorgrq_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorgtr_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorm2l_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorm2r_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormbr_(char *__vect, char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormhr_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dorml2_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormlq_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormql_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormqr_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormr2_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormr3_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__l,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormrq_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormrz_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__l,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dormtr_(char *__side, char *__uplo, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__c__,
        __CLPK_integer *__ldc, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbcon_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbequ_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublereal *__ab, __CLPK_integer *__ldab, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__afb, __CLPK_integer *__ldafb,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbstf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__afb,
        __CLPK_integer *__ldafb, char *__equed, __CLPK_doublereal *__s,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbtf2_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbtrf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpbtrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpftrf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpftri_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpftrs_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__a, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpocon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpoequ_(__CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpoequb_(__CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dporfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__af,
        __CLPK_integer *__ldaf, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dposv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dposvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__af, __CLPK_integer *__ldaf, char *__equed,
        __CLPK_doublereal *__s, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpotf2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpotrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpotri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpotrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dppcon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dppequ_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__afp,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dppsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dppsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__afp, char *__equed, __CLPK_doublereal *__s,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpptri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpstf2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__piv, __CLPK_integer *__rank,
        __CLPK_doublereal *__tol, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpstrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__piv, __CLPK_integer *__rank,
        __CLPK_doublereal *__tol, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dptcon_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpteqr_(char *__compz, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dptrfs_(__CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__df, __CLPK_doublereal *__ef,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dptsv_(__CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dptsvx_(char *__fact, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__df, __CLPK_doublereal *__ef,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpttrf_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dpttrs_(__CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dptts2_(__CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int drscl_(__CLPK_integer *__n, __CLPK_doublereal *__sa,
        __CLPK_doublereal *__sx,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbgst_(char *__vect, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__bb, __CLPK_integer *__ldbb,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbgv_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__bb, __CLPK_integer *__ldbb,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbgvd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__bb, __CLPK_integer *__ldbb,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbgvx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__bb, __CLPK_integer *__ldbb,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsbtrd_(char *__vect, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsfrk_(char *__transr, char *__uplo, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublereal *__alpha, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__c__)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsgesv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__work, __CLPK_real *__swork, __CLPK_integer *__iter,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspcon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__w,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__w,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspgst_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__bp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspgv_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublereal *__ap, __CLPK_doublereal *__bp,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspgvd_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublereal *__ap, __CLPK_doublereal *__bp,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspgvx_(__CLPK_integer *__itype, char *__jobz, char *__range, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublereal *__ap, __CLPK_doublereal *__bp,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsposv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__work, __CLPK_real *__swork, __CLPK_integer *__iter,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__afp,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__ap, __CLPK_integer *__ipiv, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dspsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__afp, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsptrd_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsptri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__ap, __CLPK_integer *__ipiv, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstebz_(char *__range, char *__order, __CLPK_integer *__n,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e, __CLPK_integer *__m,
        __CLPK_integer *__nsplit, __CLPK_doublereal *__w,
        __CLPK_integer *__iblock, __CLPK_integer *__isplit,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstedc_(char *__compz, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstegr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__isuppz, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstein_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_integer *__m, __CLPK_doublereal *__w,
        __CLPK_integer *__iblock, __CLPK_integer *__isplit,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstemr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_integer *__m, __CLPK_doublereal *__w,
        __CLPK_doublereal *__z__, __CLPK_integer *__ldz, __CLPK_integer *__nzc,
        __CLPK_integer *__isuppz, __CLPK_logical *__tryrac,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsteqr_(char *__compz, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsterf_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstev_(char *__jobz, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstevd_(char *__jobz, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstevr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__isuppz, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dstevx_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsycon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyequb_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__w,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__w,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyevr_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__isuppz, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsygs2_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsygst_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsygv_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__w,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsygvd_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__w,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsygvx_(__CLPK_integer *__itype, char *__jobz, char *__range, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsyrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsysv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsysvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__af, __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsytd2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsytf2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsytrd_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__tau, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsytrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsytri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dsytrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtbcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublereal *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtbrfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtbtrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_doublereal *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtfsm_(char *__transr, char *__side, char *__uplo, char *__trans,
        char *__diag, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__a,
        __CLPK_doublereal *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtftri_(char *__transr, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublereal *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtfttp_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__arf, __CLPK_doublereal *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtfttr_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__arf, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtgevc_(char *__side, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublereal *__s, __CLPK_integer *__lds,
        __CLPK_doublereal *__p, __CLPK_integer *__ldp, __CLPK_doublereal *__vl,
        __CLPK_integer *__ldvl, __CLPK_doublereal *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__mm, __CLPK_integer *__m, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtgex2_(__CLPK_logical *__wantq, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__q,
        __CLPK_integer *__ldq, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__j1, __CLPK_integer *__n1, __CLPK_integer *__n2,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtgexc_(__CLPK_logical *__wantq, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__q,
        __CLPK_integer *__ldq, __CLPK_doublereal *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__ifst, __CLPK_integer *__ilst,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtgsen_(__CLPK_integer *__ijob, __CLPK_logical *__wantq,
        __CLPK_logical *__wantz, __CLPK_logical *__select, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__alphar,
        __CLPK_doublereal *__alphai, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_doublereal *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__m, __CLPK_doublereal *__pl,
        __CLPK_doublereal *__pr, __CLPK_doublereal *__dif,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtgsja_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__p, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__tola, __CLPK_doublereal *__tolb,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__beta,
        __CLPK_doublereal *__u, __CLPK_integer *__ldu, __CLPK_doublereal *__v,
        __CLPK_integer *__ldv, __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_doublereal *__work, __CLPK_integer *__ncycle,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtgsna_(char *__job, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__vl,
        __CLPK_integer *__ldvl, __CLPK_doublereal *__vr, __CLPK_integer *__ldvr,
        __CLPK_doublereal *__s, __CLPK_doublereal *__dif, __CLPK_integer *__mm,
        __CLPK_integer *__m, __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtgsy2_(char *__trans, __CLPK_integer *__ijob, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__c__,
        __CLPK_integer *__ldc, __CLPK_doublereal *__d__, __CLPK_integer *__ldd,
        __CLPK_doublereal *__e, __CLPK_integer *__lde, __CLPK_doublereal *__f,
        __CLPK_integer *__ldf, __CLPK_doublereal *__scale,
        __CLPK_doublereal *__rdsum, __CLPK_doublereal *__rdscal,
        __CLPK_integer *__iwork, __CLPK_integer *__pq,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtgsyl_(char *__trans, __CLPK_integer *__ijob, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__c__,
        __CLPK_integer *__ldc, __CLPK_doublereal *__d__, __CLPK_integer *__ldd,
        __CLPK_doublereal *__e, __CLPK_integer *__lde, __CLPK_doublereal *__f,
        __CLPK_integer *__ldf, __CLPK_doublereal *__scale,
        __CLPK_doublereal *__dif, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtpcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__rcond,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtprfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__ap, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtptri_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublereal *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtptrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__ap, __CLPK_doublereal *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtpttf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__ap, __CLPK_doublereal *__arf,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtpttr_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__ap,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrevc_(char *__side, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublereal *__t, __CLPK_integer *__ldt,
        __CLPK_doublereal *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublereal *__vr, __CLPK_integer *__ldvr, __CLPK_integer *__mm,
        __CLPK_integer *__m, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrexc_(char *__compq, __CLPK_integer *__n, __CLPK_doublereal *__t,
        __CLPK_integer *__ldt, __CLPK_doublereal *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__ifst, __CLPK_integer *__ilst,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrrfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb, __CLPK_doublereal *__x,
        __CLPK_integer *__ldx, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrsen_(char *__job, char *__compq, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublereal *__t, __CLPK_integer *__ldt,
        __CLPK_doublereal *__q, __CLPK_integer *__ldq, __CLPK_doublereal *__wr,
        __CLPK_doublereal *__wi, __CLPK_integer *__m, __CLPK_doublereal *__s,
        __CLPK_doublereal *__sep, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrsna_(char *__job, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublereal *__t, __CLPK_integer *__ldt,
        __CLPK_doublereal *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublereal *__vr, __CLPK_integer *__ldvr, __CLPK_doublereal *__s,
        __CLPK_doublereal *__sep, __CLPK_integer *__mm, __CLPK_integer *__m,
        __CLPK_doublereal *__work, __CLPK_integer *__ldwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrsyl_(char *__trana, char *__tranb, __CLPK_integer *__isgn,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__scale,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrti2_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrtri_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrtrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrttf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda, __CLPK_doublereal *__arf,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtrttp_(char *__uplo, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtzrqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dtzrzf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__tau,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dzsum1_(__CLPK_integer *__n, __CLPK_doublecomplex *__cx,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer icmax1_(__CLPK_integer *__n, __CLPK_complex *__cx,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ieeeck_(__CLPK_integer *__ispec, __CLPK_real *__zero,
        __CLPK_real *__one)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilaclc_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilaclr_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_complex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer iladiag_(char *__diag)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer iladlc_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer iladlr_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilaenv_(__CLPK_integer *__ispec, char *__name__, char *__opts,
        __CLPK_integer *__n1, __CLPK_integer *__n2, __CLPK_integer *__n3,
        __CLPK_integer *__n4)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilaprec_(char *__prec)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilaslc_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilaslr_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilatrans_(char *__trans)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilauplo_(char *__uplo)
API_AVAILABLE(macos(10.2), ios(4.0));

int ilaver_(__CLPK_integer *__vers_major__, __CLPK_integer *__vers_minor__,
        __CLPK_integer *__vers_patch__)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilazlc_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilazlr_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer iparmq_(__CLPK_integer *__ispec, char *__name__, char *__opts,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer izmax1_(__CLPK_integer *__n, __CLPK_doublecomplex *__cx,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_logical lsamen_(__CLPK_integer *__n, char *__ca,
        char *__cb)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer smaxloc_(__CLPK_real *__a,
        __CLPK_integer *__dimm)
API_AVAILABLE(macos(10.2), ios(4.0));

int sbdsdc_(char *__uplo, char *__compq, __CLPK_integer *__n,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__u,
        __CLPK_integer *__ldu, __CLPK_real *__vt, __CLPK_integer *__ldvt,
        __CLPK_real *__q, __CLPK_integer *__iq, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sbdsqr_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__ncvt,
        __CLPK_integer *__nru, __CLPK_integer *__ncc, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__vt, __CLPK_integer *__ldvt,
        __CLPK_real *__u, __CLPK_integer *__ldu, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal scsum1_(__CLPK_integer *__n, __CLPK_complex *__cx,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int sdisna_(char *__job, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__d__, __CLPK_real *__sep,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbbrd_(char *__vect, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__ncc, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_real *__ab, __CLPK_integer *__ldab, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__q, __CLPK_integer *__ldq,
        __CLPK_real *__pt, __CLPK_integer *__ldpt, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbcon_(char *__norm, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbequ_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_real *__rowcnd,
        __CLPK_real *__colcnd, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbequb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_real *__rowcnd,
        __CLPK_real *__colcnd, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbrfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_integer *__nrhs, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__afb, __CLPK_integer *__ldafb,
        __CLPK_integer *__ipiv, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__x, __CLPK_integer *__ldx, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbsv_(__CLPK_integer *__n, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_integer *__nrhs, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbsvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__kl, __CLPK_integer *__ku, __CLPK_integer *__nrhs,
        __CLPK_real *__ab, __CLPK_integer *__ldab, __CLPK_real *__afb,
        __CLPK_integer *__ldafb, __CLPK_integer *__ipiv, char *__equed,
        __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__rcond, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbtf2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbtrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgbtrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_integer *__nrhs, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_integer *__ipiv, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgebak_(char *__job, char *__side, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__scale,
        __CLPK_integer *__m, __CLPK_real *__v, __CLPK_integer *__ldv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgebal_(char *__job, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__scale,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgebd2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__tauq, __CLPK_real *__taup, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgebrd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__tauq, __CLPK_real *__taup, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgecon_(char *__norm, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeequ_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__r__, __CLPK_real *__c__,
        __CLPK_real *__rowcnd, __CLPK_real *__colcnd, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeequb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__r__, __CLPK_real *__c__,
        __CLPK_real *__rowcnd, __CLPK_real *__colcnd, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgees_(char *__jobvs, char *__sort, __CLPK_L_fp __select,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__sdim, __CLPK_real *__wr, __CLPK_real *__wi,
        __CLPK_real *__vs, __CLPK_integer *__ldvs, __CLPK_real *__work,
        __CLPK_integer *__lwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeesx_(char *__jobvs, char *__sort, __CLPK_L_fp __select, char *__sense,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__sdim, __CLPK_real *__wr, __CLPK_real *__wi,
        __CLPK_real *__vs, __CLPK_integer *__ldvs, __CLPK_real *__rconde,
        __CLPK_real *__rcondv, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeev_(char *__jobvl, char *__jobvr, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__wr, __CLPK_real *__wi,
        __CLPK_real *__vl, __CLPK_integer *__ldvl, __CLPK_real *__vr,
        __CLPK_integer *__ldvr, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeevx_(char *__balanc, char *__jobvl, char *__jobvr, char *__sense,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__wr, __CLPK_real *__wi, __CLPK_real *__vl,
        __CLPK_integer *__ldvl, __CLPK_real *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__scale,
        __CLPK_real *__abnrm, __CLPK_real *__rconde, __CLPK_real *__rcondv,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgegs_(char *__jobvsl, char *__jobvsr, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__alphar, __CLPK_real *__alphai,
        __CLPK_real *__beta, __CLPK_real *__vsl, __CLPK_integer *__ldvsl,
        __CLPK_real *__vsr, __CLPK_integer *__ldvsr, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgegv_(char *__jobvl, char *__jobvr, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__alphar, __CLPK_real *__alphai, __CLPK_real *__beta,
        __CLPK_real *__vl, __CLPK_integer *__ldvl, __CLPK_real *__vr,
        __CLPK_integer *__ldvr, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgehd2_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgehrd_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgejsv_(char *__joba, char *__jobu, char *__jobv, char *__jobr,
        char *__jobt, char *__jobp, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__sva,
        __CLPK_real *__u, __CLPK_integer *__ldu, __CLPK_real *__v,
        __CLPK_integer *__ldv, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgelq2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgelqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgels_(char *__trans, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgelsd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__s, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgelss_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__s, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgelsx_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_integer *__jpvt, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgelsy_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_integer *__jpvt, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeql2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeqlf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeqp3_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_real *__tau,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeqpf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_real *__tau,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeqr2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgeqrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgerfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgerq2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgerqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgesc2_(__CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__rhs, __CLPK_integer *__ipiv, __CLPK_integer *__jpiv,
        __CLPK_real *__scale)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgesdd_(char *__jobz, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__s,
        __CLPK_real *__u, __CLPK_integer *__ldu, __CLPK_real *__vt,
        __CLPK_integer *__ldvt, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgesv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgesvd_(char *__jobu, char *__jobvt, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__s, __CLPK_real *__u, __CLPK_integer *__ldu,
        __CLPK_real *__vt, __CLPK_integer *__ldvt, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgesvj_(char *__joba, char *__jobu, char *__jobv, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__sva, __CLPK_integer *__mv, __CLPK_real *__v,
        __CLPK_integer *__ldv, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgesvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__af, __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        char *__equed, __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__rcond, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgetc2_(__CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_integer *__jpiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgetf2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgetrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgetri_(__CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgetrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggbak_(char *__job, char *__side, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__lscale,
        __CLPK_real *__rscale, __CLPK_integer *__m, __CLPK_real *__v,
        __CLPK_integer *__ldv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggbal_(char *__job, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__lscale,
        __CLPK_real *__rscale, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgges_(char *__jobvsl, char *__jobvsr, char *__sort, __CLPK_L_fp __selctg,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_integer *__sdim,
        __CLPK_real *__alphar, __CLPK_real *__alphai, __CLPK_real *__beta,
        __CLPK_real *__vsl, __CLPK_integer *__ldvsl, __CLPK_real *__vsr,
        __CLPK_integer *__ldvsr, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggesx_(char *__jobvsl, char *__jobvsr, char *__sort, __CLPK_L_fp __selctg,
        char *__sense, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__sdim, __CLPK_real *__alphar, __CLPK_real *__alphai,
        __CLPK_real *__beta, __CLPK_real *__vsl, __CLPK_integer *__ldvsl,
        __CLPK_real *__vsr, __CLPK_integer *__ldvsr, __CLPK_real *__rconde,
        __CLPK_real *__rcondv, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggev_(char *__jobvl, char *__jobvr, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__alphar, __CLPK_real *__alphai, __CLPK_real *__beta,
        __CLPK_real *__vl, __CLPK_integer *__ldvl, __CLPK_real *__vr,
        __CLPK_integer *__ldvr, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggevx_(char *__balanc, char *__jobvl, char *__jobvr, char *__sense,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__alphar,
        __CLPK_real *__alphai, __CLPK_real *__beta, __CLPK_real *__vl,
        __CLPK_integer *__ldvl, __CLPK_real *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__lscale,
        __CLPK_real *__rscale, __CLPK_real *__abnrm, __CLPK_real *__bbnrm,
        __CLPK_real *__rconde, __CLPK_real *__rcondv, __CLPK_real *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggglm_(__CLPK_integer *__n, __CLPK_integer *__m, __CLPK_integer *__p,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__d__, __CLPK_real *__x,
        __CLPK_real *__y, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgghrd_(char *__compq, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__q, __CLPK_integer *__ldq, __CLPK_real *__z__,
        __CLPK_integer *__ldz,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgglse_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__p,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__c__, __CLPK_real *__d__,
        __CLPK_real *__x, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggqrf_(__CLPK_integer *__n, __CLPK_integer *__m, __CLPK_integer *__p,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__taua,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__taub,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggrqf_(__CLPK_integer *__m, __CLPK_integer *__p, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__taua,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__taub,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggsvd_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__p, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__alpha,
        __CLPK_real *__beta, __CLPK_real *__u, __CLPK_integer *__ldu,
        __CLPK_real *__v, __CLPK_integer *__ldv, __CLPK_real *__q,
        __CLPK_integer *__ldq, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sggsvp_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__p, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__tola, __CLPK_real *__tolb, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_real *__u, __CLPK_integer *__ldu,
        __CLPK_real *__v, __CLPK_integer *__ldv, __CLPK_real *__q,
        __CLPK_integer *__ldq, __CLPK_integer *__iwork, __CLPK_real *__tau,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgsvj0_(char *__jobv, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__d__,
        __CLPK_real *__sva, __CLPK_integer *__mv, __CLPK_real *__v,
        __CLPK_integer *__ldv, __CLPK_real *__eps, __CLPK_real *__sfmin,
        __CLPK_real *__tol, __CLPK_integer *__nsweep, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgsvj1_(char *__jobv, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__n1, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__d__, __CLPK_real *__sva, __CLPK_integer *__mv,
        __CLPK_real *__v, __CLPK_integer *__ldv, __CLPK_real *__eps,
        __CLPK_real *__sfmin, __CLPK_real *__tol, __CLPK_integer *__nsweep,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgtcon_(char *__norm, __CLPK_integer *__n, __CLPK_real *__dl,
        __CLPK_real *__d__, __CLPK_real *__du, __CLPK_real *__du2,
        __CLPK_integer *__ipiv, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgtrfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__dl, __CLPK_real *__d__, __CLPK_real *__du,
        __CLPK_real *__dlf, __CLPK_real *__df, __CLPK_real *__duf,
        __CLPK_real *__du2, __CLPK_integer *__ipiv, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgtsv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_real *__dl,
        __CLPK_real *__d__, __CLPK_real *__du, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgtsvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__dl, __CLPK_real *__d__,
        __CLPK_real *__du, __CLPK_real *__dlf, __CLPK_real *__df,
        __CLPK_real *__duf, __CLPK_real *__du2, __CLPK_integer *__ipiv,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__x,
        __CLPK_integer *__ldx, __CLPK_real *__rcond, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgttrf_(__CLPK_integer *__n, __CLPK_real *__dl, __CLPK_real *__d__,
        __CLPK_real *__du, __CLPK_real *__du2, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgttrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__dl, __CLPK_real *__d__, __CLPK_real *__du,
        __CLPK_real *__du2, __CLPK_integer *__ipiv, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sgtts2_(__CLPK_integer *__itrans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__dl, __CLPK_real *__d__,
        __CLPK_real *__du, __CLPK_real *__du2, __CLPK_integer *__ipiv,
        __CLPK_real *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int shgeqz_(char *__job, char *__compq, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__h__,
        __CLPK_integer *__ldh, __CLPK_real *__t, __CLPK_integer *__ldt,
        __CLPK_real *__alphar, __CLPK_real *__alphai, __CLPK_real *__beta,
        __CLPK_real *__q, __CLPK_integer *__ldq, __CLPK_real *__z__,
        __CLPK_integer *__ldz, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int shsein_(char *__side, char *__eigsrc, char *__initv,
        __CLPK_logical *__select, __CLPK_integer *__n, __CLPK_real *__h__,
        __CLPK_integer *__ldh, __CLPK_real *__wr, __CLPK_real *__wi,
        __CLPK_real *__vl, __CLPK_integer *__ldvl, __CLPK_real *__vr,
        __CLPK_integer *__ldvr, __CLPK_integer *__mm, __CLPK_integer *__m,
        __CLPK_real *__work, __CLPK_integer *__ifaill, __CLPK_integer *__ifailr,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int shseqr_(char *__job, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_real *__h__,
        __CLPK_integer *__ldh, __CLPK_real *__wr, __CLPK_real *__wi,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));


        __CLPK_logical sisnan_(__CLPK_real *__sin__)
API_AVAILABLE(macos(10.2), ios(4.0));

int slabad_(__CLPK_real *__small,
        __CLPK_real *__large)
API_AVAILABLE(macos(10.2), ios(4.0));

int slabrd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__tauq, __CLPK_real *__taup,
        __CLPK_real *__x, __CLPK_integer *__ldx, __CLPK_real *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int slacn2_(__CLPK_integer *__n, __CLPK_real *__v, __CLPK_real *__x,
        __CLPK_integer *__isgn, __CLPK_real *__est, __CLPK_integer *__kase,
        __CLPK_integer *__isave)
API_AVAILABLE(macos(10.2), ios(4.0));

int slacon_(__CLPK_integer *__n, __CLPK_real *__v, __CLPK_real *__x,
        __CLPK_integer *__isgn, __CLPK_real *__est,
        __CLPK_integer *__kase)
API_AVAILABLE(macos(10.2), ios(4.0));

int slacpy_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int sladiv_(__CLPK_real *__a, __CLPK_real *__b, __CLPK_real *__c__,
        __CLPK_real *__d__, __CLPK_real *__p,
        __CLPK_real *__q)
API_AVAILABLE(macos(10.2), ios(4.0));

int slae2_(__CLPK_real *__a, __CLPK_real *__b, __CLPK_real *__c__,
        __CLPK_real *__rt1,
        __CLPK_real *__rt2)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaebz_(__CLPK_integer *__ijob, __CLPK_integer *__nitmax,
        __CLPK_integer *__n, __CLPK_integer *__mmax, __CLPK_integer *__minp,
        __CLPK_integer *__nbmin, __CLPK_real *__abstol, __CLPK_real *__reltol,
        __CLPK_real *__pivmin, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__e2, __CLPK_integer *__nval, __CLPK_real *__ab,
        __CLPK_real *__c__, __CLPK_integer *__mout, __CLPK_integer *__nab,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed0_(__CLPK_integer *__icompq, __CLPK_integer *__qsiz,
        __CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__q, __CLPK_integer *__ldq, __CLPK_real *__qstore,
        __CLPK_integer *__ldqs, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed1_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__q,
        __CLPK_integer *__ldq, __CLPK_integer *__indxq, __CLPK_real *__rho,
        __CLPK_integer *__cutpnt, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed2_(__CLPK_integer *__k, __CLPK_integer *__n, __CLPK_integer *__n1,
        __CLPK_real *__d__, __CLPK_real *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__indxq, __CLPK_real *__rho, __CLPK_real *__z__,
        __CLPK_real *__dlamda, __CLPK_real *__w, __CLPK_real *__q2,
        __CLPK_integer *__indx, __CLPK_integer *__indxc,
        __CLPK_integer *__indxp, __CLPK_integer *__coltyp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed3_(__CLPK_integer *__k, __CLPK_integer *__n, __CLPK_integer *__n1,
        __CLPK_real *__d__, __CLPK_real *__q, __CLPK_integer *__ldq,
        __CLPK_real *__rho, __CLPK_real *__dlamda, __CLPK_real *__q2,
        __CLPK_integer *__indx, __CLPK_integer *__ctot, __CLPK_real *__w,
        __CLPK_real *__s,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed4_(__CLPK_integer *__n, __CLPK_integer *__i__, __CLPK_real *__d__,
        __CLPK_real *__z__, __CLPK_real *__delta, __CLPK_real *__rho,
        __CLPK_real *__dlam,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed5_(__CLPK_integer *__i__, __CLPK_real *__d__, __CLPK_real *__z__,
        __CLPK_real *__delta, __CLPK_real *__rho,
        __CLPK_real *__dlam)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed6_(__CLPK_integer *__kniter, __CLPK_logical *__orgati,
        __CLPK_real *__rho, __CLPK_real *__d__, __CLPK_real *__z__,
        __CLPK_real *__finit, __CLPK_real *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed7_(__CLPK_integer *__icompq, __CLPK_integer *__n,
        __CLPK_integer *__qsiz, __CLPK_integer *__tlvls,
        __CLPK_integer *__curlvl, __CLPK_integer *__curpbm, __CLPK_real *__d__,
        __CLPK_real *__q, __CLPK_integer *__ldq, __CLPK_integer *__indxq,
        __CLPK_real *__rho, __CLPK_integer *__cutpnt, __CLPK_real *__qstore,
        __CLPK_integer *__qptr, __CLPK_integer *__prmptr,
        __CLPK_integer *__perm, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_real *__givnum, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed8_(__CLPK_integer *__icompq, __CLPK_integer *__k, __CLPK_integer *__n,
        __CLPK_integer *__qsiz, __CLPK_real *__d__, __CLPK_real *__q,
        __CLPK_integer *__ldq, __CLPK_integer *__indxq, __CLPK_real *__rho,
        __CLPK_integer *__cutpnt, __CLPK_real *__z__, __CLPK_real *__dlamda,
        __CLPK_real *__q2, __CLPK_integer *__ldq2, __CLPK_real *__w,
        __CLPK_integer *__perm, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_real *__givnum,
        __CLPK_integer *__indxp, __CLPK_integer *__indx,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaed9_(__CLPK_integer *__k, __CLPK_integer *__kstart,
        __CLPK_integer *__kstop, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__q, __CLPK_integer *__ldq, __CLPK_real *__rho,
        __CLPK_real *__dlamda, __CLPK_real *__w, __CLPK_real *__s,
        __CLPK_integer *__lds,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaeda_(__CLPK_integer *__n, __CLPK_integer *__tlvls,
        __CLPK_integer *__curlvl, __CLPK_integer *__curpbm,
        __CLPK_integer *__prmptr, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_real *__givnum, __CLPK_real *__q, __CLPK_integer *__qptr,
        __CLPK_real *__z__, __CLPK_real *__ztemp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaein_(__CLPK_logical *__rightv, __CLPK_logical *__noinit,
        __CLPK_integer *__n, __CLPK_real *__h__, __CLPK_integer *__ldh,
        __CLPK_real *__wr, __CLPK_real *__wi, __CLPK_real *__vr,
        __CLPK_real *__vi, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__work, __CLPK_real *__eps3, __CLPK_real *__smlnum,
        __CLPK_real *__bignum,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaev2_(__CLPK_real *__a, __CLPK_real *__b, __CLPK_real *__c__,
        __CLPK_real *__rt1, __CLPK_real *__rt2, __CLPK_real *__cs1,
        __CLPK_real *__sn1)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaexc_(__CLPK_logical *__wantq, __CLPK_integer *__n, __CLPK_real *__t,
        __CLPK_integer *__ldt, __CLPK_real *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__j1, __CLPK_integer *__n1, __CLPK_integer *__n2,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slag2_(__CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__safmin, __CLPK_real *__scale1,
        __CLPK_real *__scale2, __CLPK_real *__wr1, __CLPK_real *__wr2,
        __CLPK_real *__wi)
API_AVAILABLE(macos(10.2), ios(4.0));

int slag2d_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__sa,
        __CLPK_integer *__ldsa, __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slags2_(__CLPK_logical *__upper, __CLPK_real *__a1, __CLPK_real *__a2,
        __CLPK_real *__a3, __CLPK_real *__b1, __CLPK_real *__b2,
        __CLPK_real *__b3, __CLPK_real *__csu, __CLPK_real *__snu,
        __CLPK_real *__csv, __CLPK_real *__snv, __CLPK_real *__csq,
        __CLPK_real *__snq)
API_AVAILABLE(macos(10.2), ios(4.0));

int slagtf_(__CLPK_integer *__n, __CLPK_real *__a, __CLPK_real *__lambda,
        __CLPK_real *__b, __CLPK_real *__c__, __CLPK_real *__tol,
        __CLPK_real *__d__, __CLPK_integer *__in,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slagtm_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__alpha, __CLPK_real *__dl, __CLPK_real *__d__,
        __CLPK_real *__du, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__beta, __CLPK_real *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int slagts_(__CLPK_integer *__job, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_real *__b, __CLPK_real *__c__, __CLPK_real *__d__,
        __CLPK_integer *__in, __CLPK_real *__y, __CLPK_real *__tol,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slagv2_(__CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__alphar, __CLPK_real *__alphai,
        __CLPK_real *__beta, __CLPK_real *__csl, __CLPK_real *__snl,
        __CLPK_real *__csr,
        __CLPK_real *__snr)
API_AVAILABLE(macos(10.2), ios(4.0));

int slahqr_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__h__, __CLPK_integer *__ldh, __CLPK_real *__wr,
        __CLPK_real *__wi, __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slahr2_(__CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__nb,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__t, __CLPK_integer *__ldt, __CLPK_real *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int slahrd_(__CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__nb,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__t, __CLPK_integer *__ldt, __CLPK_real *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaic1_(__CLPK_integer *__job, __CLPK_integer *__j, __CLPK_real *__x,
        __CLPK_real *__sest, __CLPK_real *__w, __CLPK_real *__gamma,
        __CLPK_real *__sestpr, __CLPK_real *__s,
        __CLPK_real *__c__)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_logical slaisnan_(__CLPK_real *__sin1,
        __CLPK_real *__sin2)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaln2_(__CLPK_logical *__ltrans, __CLPK_integer *__na,
        __CLPK_integer *__nw, __CLPK_real *__smin, __CLPK_real *__ca,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__d1,
        __CLPK_real *__d2, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__wr, __CLPK_real *__wi, __CLPK_real *__x,
        __CLPK_integer *__ldx, __CLPK_real *__scale, __CLPK_real *__xnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slals0_(__CLPK_integer *__icompq, __CLPK_integer *__nl,
        __CLPK_integer *__nr, __CLPK_integer *__sqre, __CLPK_integer *__nrhs,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__bx,
        __CLPK_integer *__ldbx, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_integer *__ldgcol, __CLPK_real *__givnum,
        __CLPK_integer *__ldgnum, __CLPK_real *__poles, __CLPK_real *__difl,
        __CLPK_real *__difr, __CLPK_real *__z__, __CLPK_integer *__k,
        __CLPK_real *__c__, __CLPK_real *__s, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slalsa_(__CLPK_integer *__icompq, __CLPK_integer *__smlsiz,
        __CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__bx, __CLPK_integer *__ldbx,
        __CLPK_real *__u, __CLPK_integer *__ldu, __CLPK_real *__vt,
        __CLPK_integer *__k, __CLPK_real *__difl, __CLPK_real *__difr,
        __CLPK_real *__z__, __CLPK_real *__poles, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_integer *__ldgcol,
        __CLPK_integer *__perm, __CLPK_real *__givnum, __CLPK_real *__c__,
        __CLPK_real *__s, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slalsd_(char *__uplo, __CLPK_integer *__smlsiz, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__rcond,
        __CLPK_integer *__rank, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slamrg_(__CLPK_integer *__n1, __CLPK_integer *__n2, __CLPK_real *__a,
        __CLPK_integer *__strd1, __CLPK_integer *__strd2,
        __CLPK_integer *__index)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer slaneg_(__CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__lld, __CLPK_real *__sigma, __CLPK_real *__pivmin,
        __CLPK_integer *__r__)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slangb_(char *__norm, __CLPK_integer *__n,
        __CLPK_integer *__kl, __CLPK_integer *__ku, __CLPK_real *__ab,
        __CLPK_integer *__ldab,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slange_(char *__norm, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slangt_(char *__norm, __CLPK_integer *__n, __CLPK_real *__dl,
        __CLPK_real *__d__,
        __CLPK_real *__du)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slanhs_(char *__norm, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slansb_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slansf_(char *__norm, char *__transr, char *__uplo,
        __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slansp_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__ap,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slanst_(char *__norm, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slansy_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slantb_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__ab,
        __CLPK_integer *__ldab,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slantp_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slantr_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slanv2_(__CLPK_real *__a, __CLPK_real *__b, __CLPK_real *__c__,
        __CLPK_real *__d__, __CLPK_real *__rt1r, __CLPK_real *__rt1i,
        __CLPK_real *__rt2r, __CLPK_real *__rt2i, __CLPK_real *__cs,
        __CLPK_real *__sn)
API_AVAILABLE(macos(10.2), ios(4.0));

int slapll_(__CLPK_integer *__n, __CLPK_real *__x, __CLPK_integer *__incx,
        __CLPK_real *__y, __CLPK_integer *__incy,
        __CLPK_real *__ssmin)
API_AVAILABLE(macos(10.2), ios(4.0));

int slapmt_(__CLPK_logical *__forwrd, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_integer *__k)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slapy2_(__CLPK_real *__x,
        __CLPK_real *__y)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slapy3_(__CLPK_real *__x, __CLPK_real *__y,
        __CLPK_real *__z__)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqgb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__r__, __CLPK_real *__c__, __CLPK_real *__rowcnd,
        __CLPK_real *__colcnd, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqge_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__r__, __CLPK_real *__c__,
        __CLPK_real *__rowcnd, __CLPK_real *__colcnd, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqp2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__offset,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_integer *__jpvt,
        __CLPK_real *__tau, __CLPK_real *__vn1, __CLPK_real *__vn2,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqps_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__offset,
        __CLPK_integer *__nb, __CLPK_integer *__kb, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt, __CLPK_real *__tau,
        __CLPK_real *__vn1, __CLPK_real *__vn2, __CLPK_real *__auxv,
        __CLPK_real *__f,
        __CLPK_integer *__ldf)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqr0_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__h__, __CLPK_integer *__ldh, __CLPK_real *__wr,
        __CLPK_real *__wi, __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqr1_(__CLPK_integer *__n, __CLPK_real *__h__, __CLPK_integer *__ldh,
        __CLPK_real *__sr1, __CLPK_real *__si1, __CLPK_real *__sr2,
        __CLPK_real *__si2,
        __CLPK_real *__v)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqr2_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ktop, __CLPK_integer *__kbot,
        __CLPK_integer *__nw, __CLPK_real *__h__, __CLPK_integer *__ldh,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz, __CLPK_real *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__ns, __CLPK_integer *__nd,
        __CLPK_real *__sr, __CLPK_real *__si, __CLPK_real *__v,
        __CLPK_integer *__ldv, __CLPK_integer *__nh, __CLPK_real *__t,
        __CLPK_integer *__ldt, __CLPK_integer *__nv, __CLPK_real *__wv,
        __CLPK_integer *__ldwv, __CLPK_real *__work,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqr3_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ktop, __CLPK_integer *__kbot,
        __CLPK_integer *__nw, __CLPK_real *__h__, __CLPK_integer *__ldh,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz, __CLPK_real *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__ns, __CLPK_integer *__nd,
        __CLPK_real *__sr, __CLPK_real *__si, __CLPK_real *__v,
        __CLPK_integer *__ldv, __CLPK_integer *__nh, __CLPK_real *__t,
        __CLPK_integer *__ldt, __CLPK_integer *__nv, __CLPK_real *__wv,
        __CLPK_integer *__ldwv, __CLPK_real *__work,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqr4_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__h__, __CLPK_integer *__ldh, __CLPK_real *__wr,
        __CLPK_real *__wi, __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqr5_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__kacc22, __CLPK_integer *__n, __CLPK_integer *__ktop,
        __CLPK_integer *__kbot, __CLPK_integer *__nshfts, __CLPK_real *__sr,
        __CLPK_real *__si, __CLPK_real *__h__, __CLPK_integer *__ldh,
        __CLPK_integer *__iloz, __CLPK_integer *__ihiz, __CLPK_real *__z__,
        __CLPK_integer *__ldz, __CLPK_real *__v, __CLPK_integer *__ldv,
        __CLPK_real *__u, __CLPK_integer *__ldu, __CLPK_integer *__nv,
        __CLPK_real *__wv, __CLPK_integer *__ldwv, __CLPK_integer *__nh,
        __CLPK_real *__wh,
        __CLPK_integer *__ldwh)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqsb_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_real *__ab, __CLPK_integer *__ldab, __CLPK_real *__s,
        __CLPK_real *__scond, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqsp_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqsy_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__s, __CLPK_real *__scond,
        __CLPK_real *__amax, char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaqtr_(__CLPK_logical *__ltran, __CLPK_logical *__l__CLPK_real,
        __CLPK_integer *__n, __CLPK_real *__t, __CLPK_integer *__ldt,
        __CLPK_real *__b, __CLPK_real *__w, __CLPK_real *__scale,
        __CLPK_real *__x, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slar1v_(__CLPK_integer *__n, __CLPK_integer *__b1, __CLPK_integer *__bn,
        __CLPK_real *__lambda, __CLPK_real *__d__, __CLPK_real *__l,
        __CLPK_real *__ld, __CLPK_real *__lld, __CLPK_real *__pivmin,
        __CLPK_real *__gaptol, __CLPK_real *__z__, __CLPK_logical *__wantnc,
        __CLPK_integer *__negcnt, __CLPK_real *__ztz, __CLPK_real *__mingma,
        __CLPK_integer *__r__, __CLPK_integer *__isuppz, __CLPK_real *__nrminv,
        __CLPK_real *__resid, __CLPK_real *__rqcorr,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slar2v_(__CLPK_integer *__n, __CLPK_real *__x, __CLPK_real *__y,
        __CLPK_real *__z__, __CLPK_integer *__incx, __CLPK_real *__c__,
        __CLPK_real *__s,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarf_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__v, __CLPK_integer *__incv, __CLPK_real *__tau,
        __CLPK_real *__c__, __CLPK_integer *__ldc,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarfb_(char *__side, char *__trans, char *__direct, char *__storev,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__v, __CLPK_integer *__ldv, __CLPK_real *__t,
        __CLPK_integer *__ldt, __CLPK_real *__c__, __CLPK_integer *__ldc,
        __CLPK_real *__work,
        __CLPK_integer *__ldwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarfg_(__CLPK_integer *__n, __CLPK_real *__alpha, __CLPK_real *__x,
        __CLPK_integer *__incx,
        __CLPK_real *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarfp_(__CLPK_integer *__n, __CLPK_real *__alpha, __CLPK_real *__x,
        __CLPK_integer *__incx,
        __CLPK_real *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarft_(char *__direct, char *__storev, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_real *__v, __CLPK_integer *__ldv,
        __CLPK_real *__tau, __CLPK_real *__t,
        __CLPK_integer *__ldt)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarfx_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__v, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slargv_(__CLPK_integer *__n, __CLPK_real *__x, __CLPK_integer *__incx,
        __CLPK_real *__y, __CLPK_integer *__incy, __CLPK_real *__c__,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarnv_(__CLPK_integer *__idist, __CLPK_integer *__iseed,
        __CLPK_integer *__n,
        __CLPK_real *__x)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarra_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__e2, __CLPK_real *__spltol, __CLPK_real *__tnrm,
        __CLPK_integer *__nsplit, __CLPK_integer *__isplit,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarrb_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__lld,
        __CLPK_integer *__ifirst, __CLPK_integer *__ilast, __CLPK_real *__rtol1,
        __CLPK_real *__rtol2, __CLPK_integer *__offset, __CLPK_real *__w,
        __CLPK_real *__wgap, __CLPK_real *__werr, __CLPK_real *__work,
        __CLPK_integer *__iwork, __CLPK_real *__pivmin, __CLPK_real *__spdiam,
        __CLPK_integer *__twist,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarrc_(char *__jobt, __CLPK_integer *__n, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__pivmin, __CLPK_integer *__eigcnt, __CLPK_integer *__lcnt,
        __CLPK_integer *__rcnt,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarrd_(char *__range, char *__order, __CLPK_integer *__n,
        __CLPK_real *__vl, __CLPK_real *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_real *__gers, __CLPK_real *__reltol,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__e2,
        __CLPK_real *__pivmin, __CLPK_integer *__nsplit,
        __CLPK_integer *__isplit, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__werr, __CLPK_real *__wl, __CLPK_real *__wu,
        __CLPK_integer *__iblock, __CLPK_integer *__indexw, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarre_(char *__range, __CLPK_integer *__n, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__e2,
        __CLPK_real *__rtol1, __CLPK_real *__rtol2, __CLPK_real *__spltol,
        __CLPK_integer *__nsplit, __CLPK_integer *__isplit, __CLPK_integer *__m,
        __CLPK_real *__w, __CLPK_real *__werr, __CLPK_real *__wgap,
        __CLPK_integer *__iblock, __CLPK_integer *__indexw, __CLPK_real *__gers,
        __CLPK_real *__pivmin, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarrf_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__l,
        __CLPK_real *__ld, __CLPK_integer *__clstrt, __CLPK_integer *__clend,
        __CLPK_real *__w, __CLPK_real *__wgap, __CLPK_real *__werr,
        __CLPK_real *__spdiam, __CLPK_real *__clgapl, __CLPK_real *__clgapr,
        __CLPK_real *__pivmin, __CLPK_real *__sigma, __CLPK_real *__dplus,
        __CLPK_real *__lplus, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarrj_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e2,
        __CLPK_integer *__ifirst, __CLPK_integer *__ilast, __CLPK_real *__rtol,
        __CLPK_integer *__offset, __CLPK_real *__w, __CLPK_real *__werr,
        __CLPK_real *__work, __CLPK_integer *__iwork, __CLPK_real *__pivmin,
        __CLPK_real *__spdiam,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarrk_(__CLPK_integer *__n, __CLPK_integer *__iw, __CLPK_real *__gl,
        __CLPK_real *__gu, __CLPK_real *__d__, __CLPK_real *__e2,
        __CLPK_real *__pivmin, __CLPK_real *__reltol, __CLPK_real *__w,
        __CLPK_real *__werr,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarrr_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarrv_(__CLPK_integer *__n, __CLPK_real *__vl, __CLPK_real *__vu,
        __CLPK_real *__d__, __CLPK_real *__l, __CLPK_real *__pivmin,
        __CLPK_integer *__isplit, __CLPK_integer *__m, __CLPK_integer *__dol,
        __CLPK_integer *__dou, __CLPK_real *__minrgp, __CLPK_real *__rtol1,
        __CLPK_real *__rtol2, __CLPK_real *__w, __CLPK_real *__werr,
        __CLPK_real *__wgap, __CLPK_integer *__iblock, __CLPK_integer *__indexw,
        __CLPK_real *__gers, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__isuppz, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarscl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__x,
        __CLPK_integer *__ldx)
API_AVAILABLE(macos(10.2), ios(4.0));

int slartg_(__CLPK_real *__f, __CLPK_real *__g, __CLPK_real *__cs,
        __CLPK_real *__sn,
        __CLPK_real *__r__)
API_AVAILABLE(macos(10.2), ios(4.0));

int slartv_(__CLPK_integer *__n, __CLPK_real *__x, __CLPK_integer *__incx,
        __CLPK_real *__y, __CLPK_integer *__incy, __CLPK_real *__c__,
        __CLPK_real *__s,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaruv_(__CLPK_integer *__iseed, __CLPK_integer *__n,
        __CLPK_real *__x)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarz_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__l, __CLPK_real *__v, __CLPK_integer *__incv,
        __CLPK_real *__tau, __CLPK_real *__c__, __CLPK_integer *__ldc,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarzb_(char *__side, char *__trans, char *__direct, char *__storev,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_real *__v, __CLPK_integer *__ldv,
        __CLPK_real *__t, __CLPK_integer *__ldt, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__ldwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int slarzt_(char *__direct, char *__storev, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_real *__v, __CLPK_integer *__ldv,
        __CLPK_real *__tau, __CLPK_real *__t,
        __CLPK_integer *__ldt)
API_AVAILABLE(macos(10.2), ios(4.0));

int slas2_(__CLPK_real *__f, __CLPK_real *__g, __CLPK_real *__h__,
        __CLPK_real *__ssmin,
        __CLPK_real *__ssmax)
API_AVAILABLE(macos(10.2), ios(4.0));

int slascl_(char *__type__, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_real *__cfrom, __CLPK_real *__cto, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slascl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__x,
        __CLPK_integer *__ldx)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd0_(__CLPK_integer *__n, __CLPK_integer *__sqre, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__u, __CLPK_integer *__ldu,
        __CLPK_real *__vt, __CLPK_integer *__ldvt, __CLPK_integer *__smlsiz,
        __CLPK_integer *__iwork, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd1_(__CLPK_integer *__nl, __CLPK_integer *__nr, __CLPK_integer *__sqre,
        __CLPK_real *__d__, __CLPK_real *__alpha, __CLPK_real *__beta,
        __CLPK_real *__u, __CLPK_integer *__ldu, __CLPK_real *__vt,
        __CLPK_integer *__ldvt, __CLPK_integer *__idxq, __CLPK_integer *__iwork,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd2_(__CLPK_integer *__nl, __CLPK_integer *__nr, __CLPK_integer *__sqre,
        __CLPK_integer *__k, __CLPK_real *__d__, __CLPK_real *__z__,
        __CLPK_real *__alpha, __CLPK_real *__beta, __CLPK_real *__u,
        __CLPK_integer *__ldu, __CLPK_real *__vt, __CLPK_integer *__ldvt,
        __CLPK_real *__dsigma, __CLPK_real *__u2, __CLPK_integer *__ldu2,
        __CLPK_real *__vt2, __CLPK_integer *__ldvt2, __CLPK_integer *__idxp,
        __CLPK_integer *__idx, __CLPK_integer *__idxc, __CLPK_integer *__idxq,
        __CLPK_integer *__coltyp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd3_(__CLPK_integer *__nl, __CLPK_integer *__nr, __CLPK_integer *__sqre,
        __CLPK_integer *__k, __CLPK_real *__d__, __CLPK_real *__q,
        __CLPK_integer *__ldq, __CLPK_real *__dsigma, __CLPK_real *__u,
        __CLPK_integer *__ldu, __CLPK_real *__u2, __CLPK_integer *__ldu2,
        __CLPK_real *__vt, __CLPK_integer *__ldvt, __CLPK_real *__vt2,
        __CLPK_integer *__ldvt2, __CLPK_integer *__idxc, __CLPK_integer *__ctot,
        __CLPK_real *__z__,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd4_(__CLPK_integer *__n, __CLPK_integer *__i__, __CLPK_real *__d__,
        __CLPK_real *__z__, __CLPK_real *__delta, __CLPK_real *__rho,
        __CLPK_real *__sigma, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd5_(__CLPK_integer *__i__, __CLPK_real *__d__, __CLPK_real *__z__,
        __CLPK_real *__delta, __CLPK_real *__rho, __CLPK_real *__dsigma,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd6_(__CLPK_integer *__icompq, __CLPK_integer *__nl,
        __CLPK_integer *__nr, __CLPK_integer *__sqre, __CLPK_real *__d__,
        __CLPK_real *__vf, __CLPK_real *__vl, __CLPK_real *__alpha,
        __CLPK_real *__beta, __CLPK_integer *__idxq, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_integer *__ldgcol, __CLPK_real *__givnum,
        __CLPK_integer *__ldgnum, __CLPK_real *__poles, __CLPK_real *__difl,
        __CLPK_real *__difr, __CLPK_real *__z__, __CLPK_integer *__k,
        __CLPK_real *__c__, __CLPK_real *__s, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd7_(__CLPK_integer *__icompq, __CLPK_integer *__nl,
        __CLPK_integer *__nr, __CLPK_integer *__sqre, __CLPK_integer *__k,
        __CLPK_real *__d__, __CLPK_real *__z__, __CLPK_real *__zw,
        __CLPK_real *__vf, __CLPK_real *__vfw, __CLPK_real *__vl,
        __CLPK_real *__vlw, __CLPK_real *__alpha, __CLPK_real *__beta,
        __CLPK_real *__dsigma, __CLPK_integer *__idx, __CLPK_integer *__idxp,
        __CLPK_integer *__idxq, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_integer *__ldgcol, __CLPK_real *__givnum,
        __CLPK_integer *__ldgnum, __CLPK_real *__c__, __CLPK_real *__s,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasd8_(__CLPK_integer *__icompq, __CLPK_integer *__k, __CLPK_real *__d__,
        __CLPK_real *__z__, __CLPK_real *__vf, __CLPK_real *__vl,
        __CLPK_real *__difl, __CLPK_real *__difr, __CLPK_integer *__lddifr,
        __CLPK_real *__dsigma, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasda_(__CLPK_integer *__icompq, __CLPK_integer *__smlsiz,
        __CLPK_integer *__n, __CLPK_integer *__sqre, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__u, __CLPK_integer *__ldu,
        __CLPK_real *__vt, __CLPK_integer *__k, __CLPK_real *__difl,
        __CLPK_real *__difr, __CLPK_real *__z__, __CLPK_real *__poles,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_integer *__ldgcol, __CLPK_integer *__perm, __CLPK_real *__givnum,
        __CLPK_real *__c__, __CLPK_real *__s, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasdq_(char *__uplo, __CLPK_integer *__sqre, __CLPK_integer *__n,
        __CLPK_integer *__ncvt, __CLPK_integer *__nru, __CLPK_integer *__ncc,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__vt,
        __CLPK_integer *__ldvt, __CLPK_real *__u, __CLPK_integer *__ldu,
        __CLPK_real *__c__, __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasdt_(__CLPK_integer *__n, __CLPK_integer *__lvl, __CLPK_integer *__nd,
        __CLPK_integer *__inode, __CLPK_integer *__ndiml,
        __CLPK_integer *__ndimr,
        __CLPK_integer *__msub)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaset_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__alpha, __CLPK_real *__beta, __CLPK_real *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasq1_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasq2_(__CLPK_integer *__n, __CLPK_real *__z__,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasq3_(__CLPK_integer *__i0, __CLPK_integer *__n0, __CLPK_real *__z__,
        __CLPK_integer *__pp, __CLPK_real *__dmin__, __CLPK_real *__sigma,
        __CLPK_real *__desig, __CLPK_real *__qmax, __CLPK_integer *__nfail,
        __CLPK_integer *__iter, __CLPK_integer *__ndiv, __CLPK_logical *__ieee,
        __CLPK_integer *__ttype, __CLPK_real *__dmin1, __CLPK_real *__dmin2,
        __CLPK_real *__dn, __CLPK_real *__dn1, __CLPK_real *__dn2,
        __CLPK_real *__g,
        __CLPK_real *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasq4_(__CLPK_integer *__i0, __CLPK_integer *__n0, __CLPK_real *__z__,
        __CLPK_integer *__pp, __CLPK_integer *__n0in, __CLPK_real *__dmin__,
        __CLPK_real *__dmin1, __CLPK_real *__dmin2, __CLPK_real *__dn,
        __CLPK_real *__dn1, __CLPK_real *__dn2, __CLPK_real *__tau,
        __CLPK_integer *__ttype,
        __CLPK_real *__g)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasq5_(__CLPK_integer *__i0, __CLPK_integer *__n0, __CLPK_real *__z__,
        __CLPK_integer *__pp, __CLPK_real *__tau, __CLPK_real *__dmin__,
        __CLPK_real *__dmin1, __CLPK_real *__dmin2, __CLPK_real *__dn,
        __CLPK_real *__dnm1, __CLPK_real *__dnm2,
        __CLPK_logical *__ieee)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasq6_(__CLPK_integer *__i0, __CLPK_integer *__n0, __CLPK_real *__z__,
        __CLPK_integer *__pp, __CLPK_real *__dmin__, __CLPK_real *__dmin1,
        __CLPK_real *__dmin2, __CLPK_real *__dn, __CLPK_real *__dnm1,
        __CLPK_real *__dnm2)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasr_(char *__side, char *__pivot, char *__direct, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__c__, __CLPK_real *__s,
        __CLPK_real *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasrt_(char *__id, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slassq_(__CLPK_integer *__n, __CLPK_real *__x, __CLPK_integer *__incx,
        __CLPK_real *__scale,
        __CLPK_real *__sumsq)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasv2_(__CLPK_real *__f, __CLPK_real *__g, __CLPK_real *__h__,
        __CLPK_real *__ssmin, __CLPK_real *__ssmax, __CLPK_real *__snr,
        __CLPK_real *__csr, __CLPK_real *__snl,
        __CLPK_real *__csl)
API_AVAILABLE(macos(10.2), ios(4.0));

int slaswp_(__CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__k1, __CLPK_integer *__k2, __CLPK_integer *__ipiv,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasy2_(__CLPK_logical *__ltranl, __CLPK_logical *__ltranr,
        __CLPK_integer *__isgn, __CLPK_integer *__n1, __CLPK_integer *__n2,
        __CLPK_real *__tl, __CLPK_integer *__ldtl, __CLPK_real *__tr,
        __CLPK_integer *__ldtr, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__scale, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__xnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slasyf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_integer *__kb, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_real *__w, __CLPK_integer *__ldw,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slatbs_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_integer *__kd, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__x, __CLPK_real *__scale,
        __CLPK_real *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slatdf_(__CLPK_integer *__ijob, __CLPK_integer *__n, __CLPK_real *__z__,
        __CLPK_integer *__ldz, __CLPK_real *__rhs, __CLPK_real *__rdsum,
        __CLPK_real *__rdscal, __CLPK_integer *__ipiv,
        __CLPK_integer *__jpiv)
API_AVAILABLE(macos(10.2), ios(4.0));

int slatps_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_real *__ap, __CLPK_real *__x,
        __CLPK_real *__scale, __CLPK_real *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slatrd_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__e,
        __CLPK_real *__tau, __CLPK_real *__w,
        __CLPK_integer *__ldw)
API_AVAILABLE(macos(10.2), ios(4.0));

int slatrs_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__x, __CLPK_real *__scale, __CLPK_real *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slatrz_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__l,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slatzm_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__v, __CLPK_integer *__incv, __CLPK_real *__tau,
        __CLPK_real *__c1, __CLPK_real *__c2, __CLPK_integer *__ldc,
        __CLPK_real *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int slauu2_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int slauum_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sopgtr_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__tau, __CLPK_real *__q, __CLPK_integer *__ldq,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sopmtr_(char *__side, char *__uplo, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__ap, __CLPK_real *__tau,
        __CLPK_real *__c__, __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorg2l_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorg2r_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorgbr_(char *__vect, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__tau, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorghr_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorgl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorglq_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorgql_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorgqr_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorgr2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorgrq_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorgtr_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorm2l_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorm2r_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormbr_(char *__vect, char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormhr_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__c__, __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sorml2_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormlq_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormql_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormqr_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormr2_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormr3_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__l,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__c__, __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormrq_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormrz_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__l,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_real *__c__, __CLPK_integer *__ldc, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sormtr_(char *__side, char *__uplo, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__tau, __CLPK_real *__c__, __CLPK_integer *__ldc,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbcon_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_real *__ab, __CLPK_integer *__ldab, __CLPK_real *__anorm,
        __CLPK_real *__rcond, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbequ_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_real *__ab, __CLPK_integer *__ldab, __CLPK_real *__s,
        __CLPK_real *__scond, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__afb, __CLPK_integer *__ldafb, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbstf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__afb, __CLPK_integer *__ldafb,
        char *__equed, __CLPK_real *__s, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__rcond, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbtf2_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbtrf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spbtrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spftrf_(char *__transr, char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spftri_(char *__transr, char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spftrs_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__a, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spocon_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spoequ_(__CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spoequb_(__CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sporfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__af,
        __CLPK_integer *__ldaf, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__x, __CLPK_integer *__ldx, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sposv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sposvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__af, __CLPK_integer *__ldaf, char *__equed,
        __CLPK_real *__s, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__x, __CLPK_integer *__ldx, __CLPK_real *__rcond,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spotf2_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spotrf_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spotri_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spotrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sppcon_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__anorm, __CLPK_real *__rcond, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sppequ_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__s, __CLPK_real *__scond, __CLPK_real *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__ap, __CLPK_real *__afp, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sppsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__ap, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sppsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__ap, __CLPK_real *__afp,
        char *__equed, __CLPK_real *__s, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__rcond, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spptri_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__ap, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spstf2_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__piv, __CLPK_integer *__rank,
        __CLPK_real *__tol, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spstrf_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__piv, __CLPK_integer *__rank,
        __CLPK_real *__tol, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sptcon_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__anorm, __CLPK_real *__rcond, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spteqr_(char *__compz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sptrfs_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__df, __CLPK_real *__ef,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__x,
        __CLPK_integer *__ldx, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sptsv_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sptsvx_(char *__fact, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__df,
        __CLPK_real *__ef, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__x, __CLPK_integer *__ldx, __CLPK_real *__rcond,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spttrf_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int spttrs_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sptts2_(__CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int srscl_(__CLPK_integer *__n, __CLPK_real *__sa, __CLPK_real *__sx,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__q, __CLPK_integer *__ldq, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_real *__work,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbgst_(char *__vect, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__bb, __CLPK_integer *__ldbb,
        __CLPK_real *__x, __CLPK_integer *__ldx, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbgv_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__bb, __CLPK_integer *__ldbb,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbgvd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__bb, __CLPK_integer *__ldbb,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbgvx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__bb, __CLPK_integer *__ldbb,
        __CLPK_real *__q, __CLPK_integer *__ldq, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_real *__work,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssbtrd_(char *__vect, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__q,
        __CLPK_integer *__ldq, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssfrk_(char *__transr, char *__uplo, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_real *__alpha, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__beta,
        __CLPK_real *__c__)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspcon_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_integer *__ipiv, __CLPK_real *__anorm, __CLPK_real *__rcond,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspev_(char *__jobz, char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspevd_(char *__jobz, char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__ap, __CLPK_real *__vl, __CLPK_real *__vu,
        __CLPK_integer *__il, __CLPK_integer *__iu, __CLPK_real *__abstol,
        __CLPK_integer *__m, __CLPK_real *__w, __CLPK_real *__z__,
        __CLPK_integer *__ldz, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspgst_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__ap, __CLPK_real *__bp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspgv_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_real *__ap, __CLPK_real *__bp,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspgvd_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_real *__ap, __CLPK_real *__bp,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspgvx_(__CLPK_integer *__itype, char *__jobz, char *__range, char *__uplo,
        __CLPK_integer *__n, __CLPK_real *__ap, __CLPK_real *__bp,
        __CLPK_real *__vl, __CLPK_real *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_real *__abstol, __CLPK_integer *__m,
        __CLPK_real *__w, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__ap, __CLPK_real *__afp, __CLPK_integer *__ipiv,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__x,
        __CLPK_integer *__ldx, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__ap, __CLPK_integer *__ipiv, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sspsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__ap, __CLPK_real *__afp,
        __CLPK_integer *__ipiv, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__x, __CLPK_integer *__ldx, __CLPK_real *__rcond,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssptrd_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssptri_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_integer *__ipiv, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__ap, __CLPK_integer *__ipiv, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstebz_(char *__range, char *__order, __CLPK_integer *__n,
        __CLPK_real *__vl, __CLPK_real *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_real *__abstol, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_integer *__m, __CLPK_integer *__nsplit,
        __CLPK_real *__w, __CLPK_integer *__iblock, __CLPK_integer *__isplit,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstedc_(char *__compz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstegr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_integer *__isuppz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstein_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_integer *__m, __CLPK_real *__w, __CLPK_integer *__iblock,
        __CLPK_integer *__isplit, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstemr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_integer *__m, __CLPK_real *__w, __CLPK_real *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__nzc, __CLPK_integer *__isuppz,
        __CLPK_logical *__tryrac, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssteqr_(char *__compz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssterf_(__CLPK_integer *__n, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstev_(char *__jobz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstevd_(char *__jobz, __CLPK_integer *__n, __CLPK_real *__d__,
        __CLPK_real *__e, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstevr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_integer *__isuppz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int sstevx_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_real *__d__, __CLPK_real *__e, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_real *__work,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssycon_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_real *__anorm,
        __CLPK_real *__rcond, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyequb_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__s, __CLPK_real *__scond,
        __CLPK_real *__amax, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyev_(char *__jobz, char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__w, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyevd_(char *__jobz, char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__w, __CLPK_real *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyevr_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_integer *__isuppz,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_real *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssygs2_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssygst_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssygv_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__w,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssygvd_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__w,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssygvx_(__CLPK_integer *__itype, char *__jobz, char *__range, char *__uplo,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__vl,
        __CLPK_real *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_real *__abstol, __CLPK_integer *__m, __CLPK_real *__w,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_real *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssyrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssysv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssysvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__af, __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__x,
        __CLPK_integer *__ldx, __CLPK_real *__rcond, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssytd2_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssytf2_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssytrd_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__d__, __CLPK_real *__e,
        __CLPK_real *__tau, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssytrf_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssytri_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ssytrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stbcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_real *__ab, __CLPK_integer *__ldab,
        __CLPK_real *__rcond, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stbrfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__x, __CLPK_integer *__ldx, __CLPK_real *__ferr,
        __CLPK_real *__berr, __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stbtrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs, __CLPK_real *__ab,
        __CLPK_integer *__ldab, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stfsm_(char *__transr, char *__side, char *__uplo, char *__trans,
        char *__diag, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_real *__alpha, __CLPK_real *__a, __CLPK_real *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int stftri_(char *__transr, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_real *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stfttp_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__arf, __CLPK_real *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stfttr_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__arf, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stgevc_(char *__side, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_real *__s, __CLPK_integer *__lds,
        __CLPK_real *__p, __CLPK_integer *__ldp, __CLPK_real *__vl,
        __CLPK_integer *__ldvl, __CLPK_real *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__mm, __CLPK_integer *__m, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stgex2_(__CLPK_logical *__wantq, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__q,
        __CLPK_integer *__ldq, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__j1, __CLPK_integer *__n1, __CLPK_integer *__n2,
        __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stgexc_(__CLPK_logical *__wantq, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__q,
        __CLPK_integer *__ldq, __CLPK_real *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__ifst, __CLPK_integer *__ilst, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stgsen_(__CLPK_integer *__ijob, __CLPK_logical *__wantq,
        __CLPK_logical *__wantz, __CLPK_logical *__select, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__alphar, __CLPK_real *__alphai,
        __CLPK_real *__beta, __CLPK_real *__q, __CLPK_integer *__ldq,
        __CLPK_real *__z__, __CLPK_integer *__ldz, __CLPK_integer *__m,
        __CLPK_real *__pl, __CLPK_real *__pr, __CLPK_real *__dif,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stgsja_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__p, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__tola,
        __CLPK_real *__tolb, __CLPK_real *__alpha, __CLPK_real *__beta,
        __CLPK_real *__u, __CLPK_integer *__ldu, __CLPK_real *__v,
        __CLPK_integer *__ldv, __CLPK_real *__q, __CLPK_integer *__ldq,
        __CLPK_real *__work, __CLPK_integer *__ncycle,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stgsna_(char *__job, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__vl,
        __CLPK_integer *__ldvl, __CLPK_real *__vr, __CLPK_integer *__ldvr,
        __CLPK_real *__s, __CLPK_real *__dif, __CLPK_integer *__mm,
        __CLPK_integer *__m, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stgsy2_(char *__trans, __CLPK_integer *__ijob, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__d__, __CLPK_integer *__ldd,
        __CLPK_real *__e, __CLPK_integer *__lde, __CLPK_real *__f,
        __CLPK_integer *__ldf, __CLPK_real *__scale, __CLPK_real *__rdsum,
        __CLPK_real *__rdscal, __CLPK_integer *__iwork, __CLPK_integer *__pq,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stgsyl_(char *__trans, __CLPK_integer *__ijob, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__c__,
        __CLPK_integer *__ldc, __CLPK_real *__d__, __CLPK_integer *__ldd,
        __CLPK_real *__e, __CLPK_integer *__lde, __CLPK_real *__f,
        __CLPK_integer *__ldf, __CLPK_real *__scale, __CLPK_real *__dif,
        __CLPK_real *__work, __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stpcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_real *__ap, __CLPK_real *__rcond, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stprfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__ap, __CLPK_real *__b,
        __CLPK_integer *__ldb, __CLPK_real *__x, __CLPK_integer *__ldx,
        __CLPK_real *__ferr, __CLPK_real *__berr, __CLPK_real *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stptri_(char *__uplo, char *__diag, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stptrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__ap, __CLPK_real *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stpttf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_real *__ap, __CLPK_real *__arf,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stpttr_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__ap,
        __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_real *__a, __CLPK_integer *__lda, __CLPK_real *__rcond,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strevc_(char *__side, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_real *__t, __CLPK_integer *__ldt,
        __CLPK_real *__vl, __CLPK_integer *__ldvl, __CLPK_real *__vr,
        __CLPK_integer *__ldvr, __CLPK_integer *__mm, __CLPK_integer *__m,
        __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strexc_(char *__compq, __CLPK_integer *__n, __CLPK_real *__t,
        __CLPK_integer *__ldt, __CLPK_real *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__ifst, __CLPK_integer *__ilst, __CLPK_real *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strrfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb, __CLPK_real *__x,
        __CLPK_integer *__ldx, __CLPK_real *__ferr, __CLPK_real *__berr,
        __CLPK_real *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strsen_(char *__job, char *__compq, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_real *__t, __CLPK_integer *__ldt,
        __CLPK_real *__q, __CLPK_integer *__ldq, __CLPK_real *__wr,
        __CLPK_real *__wi, __CLPK_integer *__m, __CLPK_real *__s,
        __CLPK_real *__sep, __CLPK_real *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strsna_(char *__job, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_real *__t, __CLPK_integer *__ldt,
        __CLPK_real *__vl, __CLPK_integer *__ldvl, __CLPK_real *__vr,
        __CLPK_integer *__ldvr, __CLPK_real *__s, __CLPK_real *__sep,
        __CLPK_integer *__mm, __CLPK_integer *__m, __CLPK_real *__work,
        __CLPK_integer *__ldwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strsyl_(char *__trana, char *__tranb, __CLPK_integer *__isgn,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_real *__c__, __CLPK_integer *__ldc, __CLPK_real *__scale,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strti2_(char *__uplo, char *__diag, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strtri_(char *__uplo, char *__diag, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strtrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_real *__a, __CLPK_integer *__lda,
        __CLPK_real *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strttf_(char *__transr, char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__arf,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int strttp_(char *__uplo, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stzrqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int stzrzf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_real *__a,
        __CLPK_integer *__lda, __CLPK_real *__tau, __CLPK_real *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zbdsqr_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__ncvt,
        __CLPK_integer *__nru, __CLPK_integer *__ncc, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublecomplex *__vt,
        __CLPK_integer *__ldvt, __CLPK_doublecomplex *__u,
        __CLPK_integer *__ldu, __CLPK_doublecomplex *__c__,
        __CLPK_integer *__ldc, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zcgesv_(__CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublecomplex *__work, __CLPK_complex *__swork,
        __CLPK_doublereal *__rwork, __CLPK_integer *__iter,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zcposv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublecomplex *__work, __CLPK_complex *__swork,
        __CLPK_doublereal *__rwork, __CLPK_integer *__iter,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zdrscl_(__CLPK_integer *__n, __CLPK_doublereal *__sa,
        __CLPK_doublecomplex *__sx,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbbrd_(char *__vect, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__ncc, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__pt, __CLPK_integer *__ldpt,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbcon_(char *__norm, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbequ_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rowcnd,
        __CLPK_doublereal *__colcnd, __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbequb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rowcnd,
        __CLPK_doublereal *__colcnd, __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbrfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublecomplex *__afb, __CLPK_integer *__ldafb,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbsv_(__CLPK_integer *__n, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbsvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__kl, __CLPK_integer *__ku, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublecomplex *__afb, __CLPK_integer *__ldafb,
        __CLPK_integer *__ipiv, char *__equed, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbtf2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbtrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgbtrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgebak_(char *__job, char *__side, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__scale, __CLPK_integer *__m,
        __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgebal_(char *__job, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__scale,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgebd2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublecomplex *__tauq, __CLPK_doublecomplex *__taup,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgebrd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublecomplex *__tauq, __CLPK_doublecomplex *__taup,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgecon_(char *__norm, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeequ_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rowcnd,
        __CLPK_doublereal *__colcnd, __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeequb_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__r__, __CLPK_doublereal *__c__,
        __CLPK_doublereal *__rowcnd, __CLPK_doublereal *__colcnd,
        __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgees_(char *__jobvs, char *__sort, __CLPK_L_fp __select,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__sdim, __CLPK_doublecomplex *__w,
        __CLPK_doublecomplex *__vs, __CLPK_integer *__ldvs,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeesx_(char *__jobvs, char *__sort, __CLPK_L_fp __select, char *__sense,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__sdim, __CLPK_doublecomplex *__w,
        __CLPK_doublecomplex *__vs, __CLPK_integer *__ldvs,
        __CLPK_doublereal *__rconde, __CLPK_doublereal *__rcondv,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork, __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeev_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__w, __CLPK_doublecomplex *__vl,
        __CLPK_integer *__ldvl, __CLPK_doublecomplex *__vr,
        __CLPK_integer *__ldvr, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeevx_(char *__balanc, char *__jobvl, char *__jobvr, char *__sense,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__w, __CLPK_doublecomplex *__vl,
        __CLPK_integer *__ldvl, __CLPK_doublecomplex *__vr,
        __CLPK_integer *__ldvr, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__scale, __CLPK_doublereal *__abnrm,
        __CLPK_doublereal *__rconde, __CLPK_doublereal *__rcondv,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgegs_(char *__jobvsl, char *__jobvsr, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__alpha, __CLPK_doublecomplex *__beta,
        __CLPK_doublecomplex *__vsl, __CLPK_integer *__ldvsl,
        __CLPK_doublecomplex *__vsr, __CLPK_integer *__ldvsr,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgegv_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__alpha, __CLPK_doublecomplex *__beta,
        __CLPK_doublecomplex *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublecomplex *__vr, __CLPK_integer *__ldvr,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgehd2_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgehrd_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgelq2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgelqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgels_(char *__trans, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgelsd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__s, __CLPK_doublereal *__rcond,
        __CLPK_integer *__rank, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgelss_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__s, __CLPK_doublereal *__rcond,
        __CLPK_integer *__rank, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgelsx_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__jpvt, __CLPK_doublereal *__rcond,
        __CLPK_integer *__rank, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgelsy_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__jpvt, __CLPK_doublereal *__rcond,
        __CLPK_integer *__rank, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeql2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeqlf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeqp3_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeqpf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeqr2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgeqrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgerfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__af, __CLPK_integer *__ldaf,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgerq2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgerqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgesc2_(__CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__rhs,
        __CLPK_integer *__ipiv, __CLPK_integer *__jpiv,
        __CLPK_doublereal *__scale)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgesdd_(char *__jobz, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__s, __CLPK_doublecomplex *__u,
        __CLPK_integer *__ldu, __CLPK_doublecomplex *__vt,
        __CLPK_integer *__ldvt, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgesv_(__CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgesvd_(char *__jobu, char *__jobvt, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__s, __CLPK_doublecomplex *__u,
        __CLPK_integer *__ldu, __CLPK_doublecomplex *__vt,
        __CLPK_integer *__ldvt, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgesvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv, char *__equed,
        __CLPK_doublereal *__r__, __CLPK_doublereal *__c__,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgetc2_(__CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv, __CLPK_integer *__jpiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgetf2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgetrf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgetri_(__CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgetrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggbak_(char *__job, char *__side, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__lscale, __CLPK_doublereal *__rscale,
        __CLPK_integer *__m, __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggbal_(char *__job, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__lscale, __CLPK_doublereal *__rscale,
        __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgges_(char *__jobvsl, char *__jobvsr, char *__sort, __CLPK_L_fp __selctg,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__sdim, __CLPK_doublecomplex *__alpha,
        __CLPK_doublecomplex *__beta, __CLPK_doublecomplex *__vsl,
        __CLPK_integer *__ldvsl, __CLPK_doublecomplex *__vsr,
        __CLPK_integer *__ldvsr, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggesx_(char *__jobvsl, char *__jobvsr, char *__sort, __CLPK_L_fp __selctg,
        char *__sense, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__sdim, __CLPK_doublecomplex *__alpha,
        __CLPK_doublecomplex *__beta, __CLPK_doublecomplex *__vsl,
        __CLPK_integer *__ldvsl, __CLPK_doublecomplex *__vsr,
        __CLPK_integer *__ldvsr, __CLPK_doublereal *__rconde,
        __CLPK_doublereal *__rcondv, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggev_(char *__jobvl, char *__jobvr, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__alpha, __CLPK_doublecomplex *__beta,
        __CLPK_doublecomplex *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublecomplex *__vr, __CLPK_integer *__ldvr,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggevx_(char *__balanc, char *__jobvl, char *__jobvr, char *__sense,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__alpha, __CLPK_doublecomplex *__beta,
        __CLPK_doublecomplex *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublecomplex *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublereal *__lscale, __CLPK_doublereal *__rscale,
        __CLPK_doublereal *__abnrm, __CLPK_doublereal *__bbnrm,
        __CLPK_doublereal *__rconde, __CLPK_doublereal *__rcondv,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork, __CLPK_integer *__iwork,
        __CLPK_logical *__bwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggglm_(__CLPK_integer *__n, __CLPK_integer *__m, __CLPK_integer *__p,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__d__, __CLPK_doublecomplex *__x,
        __CLPK_doublecomplex *__y, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgghrd_(char *__compq, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgglse_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__p,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__c__, __CLPK_doublecomplex *__d__,
        __CLPK_doublecomplex *__x, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggqrf_(__CLPK_integer *__n, __CLPK_integer *__m, __CLPK_integer *__p,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__taua, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__taub,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggrqf_(__CLPK_integer *__m, __CLPK_integer *__p, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__taua, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__taub,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggsvd_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__p, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__beta,
        __CLPK_doublecomplex *__u, __CLPK_integer *__ldu,
        __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zggsvp_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__p, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__tola, __CLPK_doublereal *__tolb,
        __CLPK_integer *__k, __CLPK_integer *__l, __CLPK_doublecomplex *__u,
        __CLPK_integer *__ldu, __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__iwork, __CLPK_doublereal *__rwork,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgtcon_(char *__norm, __CLPK_integer *__n, __CLPK_doublecomplex *__dl,
        __CLPK_doublecomplex *__d__, __CLPK_doublecomplex *__du,
        __CLPK_doublecomplex *__du2, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgtrfs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__dl, __CLPK_doublecomplex *__d__,
        __CLPK_doublecomplex *__du, __CLPK_doublecomplex *__dlf,
        __CLPK_doublecomplex *__df, __CLPK_doublecomplex *__duf,
        __CLPK_doublecomplex *__du2, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgtsv_(__CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__dl, __CLPK_doublecomplex *__d__,
        __CLPK_doublecomplex *__du, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgtsvx_(char *__fact, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__dl,
        __CLPK_doublecomplex *__d__, __CLPK_doublecomplex *__du,
        __CLPK_doublecomplex *__dlf, __CLPK_doublecomplex *__df,
        __CLPK_doublecomplex *__duf, __CLPK_doublecomplex *__du2,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgttrf_(__CLPK_integer *__n, __CLPK_doublecomplex *__dl,
        __CLPK_doublecomplex *__d__, __CLPK_doublecomplex *__du,
        __CLPK_doublecomplex *__du2, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgttrs_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__dl, __CLPK_doublecomplex *__d__,
        __CLPK_doublecomplex *__du, __CLPK_doublecomplex *__du2,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zgtts2_(__CLPK_integer *__itrans, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__dl,
        __CLPK_doublecomplex *__d__, __CLPK_doublecomplex *__du,
        __CLPK_doublecomplex *__du2, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork, __CLPK_integer *__lrwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__q,
        __CLPK_integer *__ldq, __CLPK_doublereal *__vl, __CLPK_doublereal *__vu,
        __CLPK_integer *__il, __CLPK_integer *__iu, __CLPK_doublereal *__abstol,
        __CLPK_integer *__m, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbgst_(char *__vect, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__bb,
        __CLPK_integer *__ldbb, __CLPK_doublecomplex *__x,
        __CLPK_integer *__ldx, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbgv_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__bb,
        __CLPK_integer *__ldbb, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbgvd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__bb,
        __CLPK_integer *__ldbb, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork, __CLPK_integer *__lrwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbgvx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__ka, __CLPK_integer *__kb, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__bb,
        __CLPK_integer *__ldbb, __CLPK_doublecomplex *__q,
        __CLPK_integer *__ldq, __CLPK_doublereal *__vl, __CLPK_doublereal *__vu,
        __CLPK_integer *__il, __CLPK_integer *__iu, __CLPK_doublereal *__abstol,
        __CLPK_integer *__m, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhbtrd_(char *__vect, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublecomplex *__q,
        __CLPK_integer *__ldq, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhecon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zheequb_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zheev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zheevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zheevr_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__isuppz,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork, __CLPK_integer *__lrwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zheevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhegs2_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhegst_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhegv_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhegvd_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhegvx_(__CLPK_integer *__itype, char *__jobz, char *__range, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork, __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zherfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__af, __CLPK_integer *__ldaf,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhesv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhesvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhetd2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublecomplex *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhetf2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhetrd_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhetrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhetri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhetrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhfrk_(char *__transr, char *__uplo, char *__trans, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublereal *__alpha,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__beta,
        __CLPK_doublecomplex *__c__)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhgeqz_(char *__job, char *__compq, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__h__, __CLPK_integer *__ldh,
        __CLPK_doublecomplex *__t, __CLPK_integer *__ldt,
        __CLPK_doublecomplex *__alpha, __CLPK_doublecomplex *__beta,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpcon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpev_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpevd_(char *__jobz, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork, __CLPK_integer *__lrwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpevx_(char *__jobz, char *__range, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpgst_(__CLPK_integer *__itype, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap, __CLPK_doublecomplex *__bp,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpgv_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__bp, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpgvd_(__CLPK_integer *__itype, char *__jobz, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__bp, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_doublereal *__rwork, __CLPK_integer *__lrwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpgvx_(__CLPK_integer *__itype, char *__jobz, char *__range, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__bp, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_integer *__il, __CLPK_integer *__iu,
        __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_doublecomplex *__afp,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhpsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__afp, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhptrd_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublecomplex *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhptri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhsein_(char *__side, char *__eigsrc, char *__initv,
        __CLPK_logical *__select, __CLPK_integer *__n,
        __CLPK_doublecomplex *__h__, __CLPK_integer *__ldh,
        __CLPK_doublecomplex *__w, __CLPK_doublecomplex *__vl,
        __CLPK_integer *__ldvl, __CLPK_doublecomplex *__vr,
        __CLPK_integer *__ldvr, __CLPK_integer *__mm, __CLPK_integer *__m,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__ifaill, __CLPK_integer *__ifailr,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zhseqr_(char *__job, char *__compz, __CLPK_integer *__n,
        __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__h__, __CLPK_integer *__ldh,
        __CLPK_doublecomplex *__w, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlabrd_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublecomplex *__tauq, __CLPK_doublecomplex *__taup,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublecomplex *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlacgv_(__CLPK_integer *__n, __CLPK_doublecomplex *__x,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlacn2_(__CLPK_integer *__n, __CLPK_doublecomplex *__v,
        __CLPK_doublecomplex *__x, __CLPK_doublereal *__est,
        __CLPK_integer *__kase,
        __CLPK_integer *__isave)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlacon_(__CLPK_integer *__n, __CLPK_doublecomplex *__v,
        __CLPK_doublecomplex *__x, __CLPK_doublereal *__est,
        __CLPK_integer *__kase)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlacp2_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlacpy_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlacrm_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__rwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlacrt_(__CLPK_integer *__n, __CLPK_doublecomplex *__cx,
        __CLPK_integer *__incx, __CLPK_doublecomplex *__cy,
        __CLPK_integer *__incy, __CLPK_doublecomplex *__c__,
        __CLPK_doublecomplex *__s)
API_AVAILABLE(macos(10.2), ios(4.0));

void zladiv_(__CLPK_doublecomplex *__ret_val, __CLPK_doublecomplex *__x,
        __CLPK_doublecomplex *__y)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaed0_(__CLPK_integer *__qsiz, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__qstore, __CLPK_integer *__ldqs,
        __CLPK_doublereal *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaed7_(__CLPK_integer *__n, __CLPK_integer *__cutpnt,
        __CLPK_integer *__qsiz, __CLPK_integer *__tlvls,
        __CLPK_integer *__curlvl, __CLPK_integer *__curpbm,
        __CLPK_doublereal *__d__, __CLPK_doublecomplex *__q,
        __CLPK_integer *__ldq, __CLPK_doublereal *__rho,
        __CLPK_integer *__indxq, __CLPK_doublereal *__qstore,
        __CLPK_integer *__qptr, __CLPK_integer *__prmptr,
        __CLPK_integer *__perm, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_doublereal *__givnum,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaed8_(__CLPK_integer *__k, __CLPK_integer *__n, __CLPK_integer *__qsiz,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__rho,
        __CLPK_integer *__cutpnt, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__dlamda, __CLPK_doublecomplex *__q2,
        __CLPK_integer *__ldq2, __CLPK_doublereal *__w, __CLPK_integer *__indxp,
        __CLPK_integer *__indx, __CLPK_integer *__indxq, __CLPK_integer *__perm,
        __CLPK_integer *__givptr, __CLPK_integer *__givcol,
        __CLPK_doublereal *__givnum,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaein_(__CLPK_logical *__rightv, __CLPK_logical *__noinit,
        __CLPK_integer *__n, __CLPK_doublecomplex *__h__, __CLPK_integer *__ldh,
        __CLPK_doublecomplex *__w, __CLPK_doublecomplex *__v,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__rwork, __CLPK_doublereal *__eps3,
        __CLPK_doublereal *__smlnum,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaesy_(__CLPK_doublecomplex *__a, __CLPK_doublecomplex *__b,
        __CLPK_doublecomplex *__c__, __CLPK_doublecomplex *__rt1,
        __CLPK_doublecomplex *__rt2, __CLPK_doublecomplex *__evscal,
        __CLPK_doublecomplex *__cs1,
        __CLPK_doublecomplex *__sn1)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaev2_(__CLPK_doublecomplex *__a, __CLPK_doublecomplex *__b,
        __CLPK_doublecomplex *__c__, __CLPK_doublereal *__rt1,
        __CLPK_doublereal *__rt2, __CLPK_doublereal *__cs1,
        __CLPK_doublecomplex *__sn1)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlag2c_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__sa, __CLPK_integer *__ldsa,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlags2_(__CLPK_logical *__upper, __CLPK_doublereal *__a1,
        __CLPK_doublecomplex *__a2, __CLPK_doublereal *__a3,
        __CLPK_doublereal *__b1, __CLPK_doublecomplex *__b2,
        __CLPK_doublereal *__b3, __CLPK_doublereal *__csu,
        __CLPK_doublecomplex *__snu, __CLPK_doublereal *__csv,
        __CLPK_doublecomplex *__snv, __CLPK_doublereal *__csq,
        __CLPK_doublecomplex *__snq)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlagtm_(char *__trans, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__alpha, __CLPK_doublecomplex *__dl,
        __CLPK_doublecomplex *__d__, __CLPK_doublecomplex *__du,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__beta, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlahef_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_integer *__kb, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__w,
        __CLPK_integer *__ldw,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlahqr_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__h__, __CLPK_integer *__ldh,
        __CLPK_doublecomplex *__w, __CLPK_integer *__iloz,
        __CLPK_integer *__ihiz, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlahr2_(__CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__nb,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__t,
        __CLPK_integer *__ldt, __CLPK_doublecomplex *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlahrd_(__CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__nb,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__t,
        __CLPK_integer *__ldt, __CLPK_doublecomplex *__y,
        __CLPK_integer *__ldy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaic1_(__CLPK_integer *__job, __CLPK_integer *__j,
        __CLPK_doublecomplex *__x, __CLPK_doublereal *__sest,
        __CLPK_doublecomplex *__w, __CLPK_doublecomplex *__gamma,
        __CLPK_doublereal *__sestpr, __CLPK_doublecomplex *__s,
        __CLPK_doublecomplex *__c__)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlals0_(__CLPK_integer *__icompq, __CLPK_integer *__nl,
        __CLPK_integer *__nr, __CLPK_integer *__sqre, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__bx, __CLPK_integer *__ldbx,
        __CLPK_integer *__perm, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_integer *__ldgcol,
        __CLPK_doublereal *__givnum, __CLPK_integer *__ldgnum,
        __CLPK_doublereal *__poles, __CLPK_doublereal *__difl,
        __CLPK_doublereal *__difr, __CLPK_doublereal *__z__,
        __CLPK_integer *__k, __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlalsa_(__CLPK_integer *__icompq, __CLPK_integer *__smlsiz,
        __CLPK_integer *__n, __CLPK_integer *__nrhs, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__bx,
        __CLPK_integer *__ldbx, __CLPK_doublereal *__u, __CLPK_integer *__ldu,
        __CLPK_doublereal *__vt, __CLPK_integer *__k, __CLPK_doublereal *__difl,
        __CLPK_doublereal *__difr, __CLPK_doublereal *__z__,
        __CLPK_doublereal *__poles, __CLPK_integer *__givptr,
        __CLPK_integer *__givcol, __CLPK_integer *__ldgcol,
        __CLPK_integer *__perm, __CLPK_doublereal *__givnum,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_doublereal *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlalsd_(char *__uplo, __CLPK_integer *__smlsiz, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublereal *__rcond,
        __CLPK_integer *__rank, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlangb_(char *__norm, __CLPK_integer *__n,
        __CLPK_integer *__kl, __CLPK_integer *__ku, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlange_(char *__norm, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlangt_(char *__norm, __CLPK_integer *__n,
        __CLPK_doublecomplex *__dl, __CLPK_doublecomplex *__d__,
        __CLPK_doublecomplex *__du)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlanhb_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlanhe_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlanhf_(char *__norm, char *__transr, char *__uplo,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlanhp_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlanhs_(char *__norm, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlanht_(char *__norm, __CLPK_integer *__n,
        __CLPK_doublereal *__d__,
        __CLPK_doublecomplex *__e)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlansb_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlansp_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlansy_(char *__norm, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlantb_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlantp_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal zlantr_(char *__norm, char *__uplo, char *__diag,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlapll_(__CLPK_integer *__n, __CLPK_doublecomplex *__x,
        __CLPK_integer *__incx, __CLPK_doublecomplex *__y,
        __CLPK_integer *__incy,
        __CLPK_doublereal *__ssmin)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlapmt_(__CLPK_logical *__forwrd, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_integer *__k)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqgb_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__kl,
        __CLPK_integer *__ku, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rowcnd,
        __CLPK_doublereal *__colcnd, __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqge_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__r__,
        __CLPK_doublereal *__c__, __CLPK_doublereal *__rowcnd,
        __CLPK_doublereal *__colcnd, __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqhb_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqhe_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqhp_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqp2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__offset,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__jpvt, __CLPK_doublecomplex *__tau,
        __CLPK_doublereal *__vn1, __CLPK_doublereal *__vn2,
        __CLPK_doublecomplex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqps_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__offset,
        __CLPK_integer *__nb, __CLPK_integer *__kb, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__jpvt,
        __CLPK_doublecomplex *__tau, __CLPK_doublereal *__vn1,
        __CLPK_doublereal *__vn2, __CLPK_doublecomplex *__auxv,
        __CLPK_doublecomplex *__f,
        __CLPK_integer *__ldf)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqr0_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__h__, __CLPK_integer *__ldh,
        __CLPK_doublecomplex *__w, __CLPK_integer *__iloz,
        __CLPK_integer *__ihiz, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqr1_(__CLPK_integer *__n, __CLPK_doublecomplex *__h__,
        __CLPK_integer *__ldh, __CLPK_doublecomplex *__s1,
        __CLPK_doublecomplex *__s2,
        __CLPK_doublecomplex *__v)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqr2_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ktop, __CLPK_integer *__kbot,
        __CLPK_integer *__nw, __CLPK_doublecomplex *__h__,
        __CLPK_integer *__ldh, __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__ns, __CLPK_integer *__nd, __CLPK_doublecomplex *__sh,
        __CLPK_doublecomplex *__v, __CLPK_integer *__ldv, __CLPK_integer *__nh,
        __CLPK_doublecomplex *__t, __CLPK_integer *__ldt, __CLPK_integer *__nv,
        __CLPK_doublecomplex *__wv, __CLPK_integer *__ldwv,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqr3_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ktop, __CLPK_integer *__kbot,
        __CLPK_integer *__nw, __CLPK_doublecomplex *__h__,
        __CLPK_integer *__ldh, __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__ns, __CLPK_integer *__nd, __CLPK_doublecomplex *__sh,
        __CLPK_doublecomplex *__v, __CLPK_integer *__ldv, __CLPK_integer *__nh,
        __CLPK_doublecomplex *__t, __CLPK_integer *__ldt, __CLPK_integer *__nv,
        __CLPK_doublecomplex *__wv, __CLPK_integer *__ldwv,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqr4_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__h__, __CLPK_integer *__ldh,
        __CLPK_doublecomplex *__w, __CLPK_integer *__iloz,
        __CLPK_integer *__ihiz, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqr5_(__CLPK_logical *__wantt, __CLPK_logical *__wantz,
        __CLPK_integer *__kacc22, __CLPK_integer *__n, __CLPK_integer *__ktop,
        __CLPK_integer *__kbot, __CLPK_integer *__nshfts,
        __CLPK_doublecomplex *__s, __CLPK_doublecomplex *__h__,
        __CLPK_integer *__ldh, __CLPK_integer *__iloz, __CLPK_integer *__ihiz,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_doublecomplex *__u, __CLPK_integer *__ldu, __CLPK_integer *__nv,
        __CLPK_doublecomplex *__wv, __CLPK_integer *__ldwv,
        __CLPK_integer *__nh, __CLPK_doublecomplex *__wh,
        __CLPK_integer *__ldwh)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqsb_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqsp_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaqsy_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        char *__equed)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlar1v_(__CLPK_integer *__n, __CLPK_integer *__b1, __CLPK_integer *__bn,
        __CLPK_doublereal *__lambda, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__l, __CLPK_doublereal *__ld,
        __CLPK_doublereal *__lld, __CLPK_doublereal *__pivmin,
        __CLPK_doublereal *__gaptol, __CLPK_doublecomplex *__z__,
        __CLPK_logical *__wantnc, __CLPK_integer *__negcnt,
        __CLPK_doublereal *__ztz, __CLPK_doublereal *__mingma,
        __CLPK_integer *__r__, __CLPK_integer *__isuppz,
        __CLPK_doublereal *__nrminv, __CLPK_doublereal *__resid,
        __CLPK_doublereal *__rqcorr,
        __CLPK_doublereal *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlar2v_(__CLPK_integer *__n, __CLPK_doublecomplex *__x,
        __CLPK_doublecomplex *__y, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__incx, __CLPK_doublereal *__c__,
        __CLPK_doublecomplex *__s,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarcm_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__rwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarf_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__v, __CLPK_integer *__incv,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__c__,
        __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarfb_(char *__side, char *__trans, char *__direct, char *__storev,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_doublecomplex *__t, __CLPK_integer *__ldt,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__ldwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarfg_(__CLPK_integer *__n, __CLPK_doublecomplex *__alpha,
        __CLPK_doublecomplex *__x, __CLPK_integer *__incx,
        __CLPK_doublecomplex *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarfp_(__CLPK_integer *__n, __CLPK_doublecomplex *__alpha,
        __CLPK_doublecomplex *__x, __CLPK_integer *__incx,
        __CLPK_doublecomplex *__tau)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarft_(char *__direct, char *__storev, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__t,
        __CLPK_integer *__ldt)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarfx_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__v, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlargv_(__CLPK_integer *__n, __CLPK_doublecomplex *__x,
        __CLPK_integer *__incx, __CLPK_doublecomplex *__y,
        __CLPK_integer *__incy, __CLPK_doublereal *__c__,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarnv_(__CLPK_integer *__idist, __CLPK_integer *__iseed,
        __CLPK_integer *__n,
        __CLPK_doublecomplex *__x)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarrv_(__CLPK_integer *__n, __CLPK_doublereal *__vl,
        __CLPK_doublereal *__vu, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__l, __CLPK_doublereal *__pivmin,
        __CLPK_integer *__isplit, __CLPK_integer *__m, __CLPK_integer *__dol,
        __CLPK_integer *__dou, __CLPK_doublereal *__minrgp,
        __CLPK_doublereal *__rtol1, __CLPK_doublereal *__rtol2,
        __CLPK_doublereal *__w, __CLPK_doublereal *__werr,
        __CLPK_doublereal *__wgap, __CLPK_integer *__iblock,
        __CLPK_integer *__indexw, __CLPK_doublereal *__gers,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__isuppz, __CLPK_doublereal *__work,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarscl2_(__CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublecomplex *__x,
        __CLPK_integer *__ldx)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlartg_(__CLPK_doublecomplex *__f, __CLPK_doublecomplex *__g,
        __CLPK_doublereal *__cs, __CLPK_doublecomplex *__sn,
        __CLPK_doublecomplex *__r__)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlartv_(__CLPK_integer *__n, __CLPK_doublecomplex *__x,
        __CLPK_integer *__incx, __CLPK_doublecomplex *__y,
        __CLPK_integer *__incy, __CLPK_doublereal *__c__,
        __CLPK_doublecomplex *__s,
        __CLPK_integer *__incc)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarz_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__l, __CLPK_doublecomplex *__v, __CLPK_integer *__incv,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__c__,
        __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarzb_(char *__side, char *__trans, char *__direct, char *__storev,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_doublecomplex *__t, __CLPK_integer *__ldt,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__ldwork)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlarzt_(char *__direct, char *__storev, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__t,
        __CLPK_integer *__ldt)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlascl_(char *__type__, __CLPK_integer *__kl, __CLPK_integer *__ku,
        __CLPK_doublereal *__cfrom, __CLPK_doublereal *__cto,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlascl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublecomplex *__x,
        __CLPK_integer *__ldx)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaset_(char *__uplo, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__alpha, __CLPK_doublecomplex *__beta,
        __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlasr_(char *__side, char *__pivot, char *__direct, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublereal *__c__, __CLPK_doublereal *__s,
        __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlassq_(__CLPK_integer *__n, __CLPK_doublecomplex *__x,
        __CLPK_integer *__incx, __CLPK_doublereal *__scale,
        __CLPK_doublereal *__sumsq)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlaswp_(__CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__k1, __CLPK_integer *__k2,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__incx)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlasyf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_integer *__kb, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__w,
        __CLPK_integer *__ldw,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlat2c_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_complex *__sa, __CLPK_integer *__ldsa,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlatbs_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_integer *__kd, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__x,
        __CLPK_doublereal *__scale, __CLPK_doublereal *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlatdf_(__CLPK_integer *__ijob, __CLPK_integer *__n,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublecomplex *__rhs, __CLPK_doublereal *__rdsum,
        __CLPK_doublereal *__rdscal, __CLPK_integer *__ipiv,
        __CLPK_integer *__jpiv)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlatps_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__x, __CLPK_doublereal *__scale,
        __CLPK_doublereal *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlatrd_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nb,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__e, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__w,
        __CLPK_integer *__ldw)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlatrs_(char *__uplo, char *__trans, char *__diag, char *__normin,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__x, __CLPK_doublereal *__scale,
        __CLPK_doublereal *__cnorm,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlatrz_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__l,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlatzm_(char *__side, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__v, __CLPK_integer *__incv,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__c1,
        __CLPK_doublecomplex *__c2, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlauu2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zlauum_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbcon_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbequ_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__afb,
        __CLPK_integer *__ldafb, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbstf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublecomplex *__afb, __CLPK_integer *__ldafb, char *__equed,
        __CLPK_doublereal *__s, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbtf2_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbtrf_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpbtrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__kd,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpftrf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpftri_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpftrs_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__a,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpocon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpoequ_(__CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpoequb_(__CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zporfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__af, __CLPK_integer *__ldaf,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zposv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zposvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__af,
        __CLPK_integer *__ldaf, char *__equed, __CLPK_doublereal *__s,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpotf2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpotrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpotri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpotrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zppcon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zppequ_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublereal *__s, __CLPK_doublereal *__scond,
        __CLPK_doublereal *__amax,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_doublecomplex *__afp,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zppsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zppsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__afp, char *__equed, __CLPK_doublereal *__s,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpptri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpstf2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__piv, __CLPK_integer *__rank,
        __CLPK_doublereal *__tol, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpstrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__piv, __CLPK_integer *__rank,
        __CLPK_doublereal *__tol, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zptcon_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublecomplex *__e, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpteqr_(char *__compz, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zptrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublecomplex *__e,
        __CLPK_doublereal *__df, __CLPK_doublecomplex *__ef,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zptsv_(__CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublecomplex *__e,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zptsvx_(char *__fact, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublecomplex *__e,
        __CLPK_doublereal *__df, __CLPK_doublecomplex *__ef,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpttrf_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublecomplex *__e,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zpttrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublereal *__d__, __CLPK_doublecomplex *__e,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zptts2_(__CLPK_integer *__iuplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublereal *__d__,
        __CLPK_doublecomplex *__e, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int zrot_(__CLPK_integer *__n, __CLPK_doublecomplex *__cx,
        __CLPK_integer *__incx, __CLPK_doublecomplex *__cy,
        __CLPK_integer *__incy, __CLPK_doublereal *__c__,
        __CLPK_doublecomplex *__s)
API_AVAILABLE(macos(10.2), ios(4.0));

int zspcon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__ipiv, __CLPK_doublereal *__anorm,
        __CLPK_doublereal *__rcond, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zspmv_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__alpha,
        __CLPK_doublecomplex *__ap, __CLPK_doublecomplex *__x,
        __CLPK_integer *__incx, __CLPK_doublecomplex *__beta,
        __CLPK_doublecomplex *__y,
        __CLPK_integer *__incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zspr_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__alpha,
        __CLPK_doublecomplex *__x, __CLPK_integer *__incx,
        __CLPK_doublecomplex *__ap)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsprfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_doublecomplex *__afp,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zspsv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zspsvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__afp, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsptrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsptri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsptrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ap, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zstedc_(char *__compz, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__lrwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zstegr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_doublereal *__abstol, __CLPK_integer *__m,
        __CLPK_doublereal *__w, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_integer *__isuppz,
        __CLPK_doublereal *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork, __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zstein_(__CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_integer *__m, __CLPK_doublereal *__w,
        __CLPK_integer *__iblock, __CLPK_integer *__isplit,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_doublereal *__work, __CLPK_integer *__iwork,
        __CLPK_integer *__ifail,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zstemr_(char *__jobz, char *__range, __CLPK_integer *__n,
        __CLPK_doublereal *__d__, __CLPK_doublereal *__e,
        __CLPK_doublereal *__vl, __CLPK_doublereal *__vu, __CLPK_integer *__il,
        __CLPK_integer *__iu, __CLPK_integer *__m, __CLPK_doublereal *__w,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__nzc, __CLPK_integer *__isuppz,
        __CLPK_logical *__tryrac, __CLPK_doublereal *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsteqr_(char *__compz, __CLPK_integer *__n, __CLPK_doublereal *__d__,
        __CLPK_doublereal *__e, __CLPK_doublecomplex *__z__,
        __CLPK_integer *__ldz, __CLPK_doublereal *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsycon_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublereal *__anorm, __CLPK_doublereal *__rcond,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsyequb_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublereal *__s,
        __CLPK_doublereal *__scond, __CLPK_doublereal *__amax,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsymv_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__alpha,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__x, __CLPK_integer *__incx,
        __CLPK_doublecomplex *__beta, __CLPK_doublecomplex *__y,
        __CLPK_integer *__incy)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsyr_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__alpha,
        __CLPK_doublecomplex *__x, __CLPK_integer *__incx,
        __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsyrfs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__af, __CLPK_integer *__ldaf,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsysv_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsysvx_(char *__fact, char *__uplo, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__af,
        __CLPK_integer *__ldaf, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__rcond, __CLPK_doublereal *__ferr,
        __CLPK_doublereal *__berr, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsytf2_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsytrf_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsytri_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_integer *__ipiv,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zsytrs_(char *__uplo, __CLPK_integer *__n, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__ipiv, __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztbcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_doublecomplex *__ab,
        __CLPK_integer *__ldab, __CLPK_doublereal *__rcond,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztbrfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztbtrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__kd, __CLPK_integer *__nrhs,
        __CLPK_doublecomplex *__ab, __CLPK_integer *__ldab,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztfsm_(char *__transr, char *__side, char *__uplo, char *__trans,
        char *__diag, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_doublecomplex *__alpha, __CLPK_doublecomplex *__a,
        __CLPK_doublecomplex *__b,
        __CLPK_integer *__ldb)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztftri_(char *__transr, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztfttp_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__arf, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztfttr_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__arf, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztgevc_(char *__side, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublecomplex *__s, __CLPK_integer *__lds,
        __CLPK_doublecomplex *__p, __CLPK_integer *__ldp,
        __CLPK_doublecomplex *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublecomplex *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__mm, __CLPK_integer *__m, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztgex2_(__CLPK_logical *__wantq, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__j1,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztgexc_(__CLPK_logical *__wantq, __CLPK_logical *__wantz,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz,
        __CLPK_integer *__ifst, __CLPK_integer *__ilst,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztgsen_(__CLPK_integer *__ijob, __CLPK_logical *__wantq,
        __CLPK_logical *__wantz, __CLPK_logical *__select, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__alpha, __CLPK_doublecomplex *__beta,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__z__, __CLPK_integer *__ldz, __CLPK_integer *__m,
        __CLPK_doublereal *__pl, __CLPK_doublereal *__pr,
        __CLPK_doublereal *__dif, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__liwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztgsja_(char *__jobu, char *__jobv, char *__jobq, __CLPK_integer *__m,
        __CLPK_integer *__p, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_integer *__l, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublereal *__tola, __CLPK_doublereal *__tolb,
        __CLPK_doublereal *__alpha, __CLPK_doublereal *__beta,
        __CLPK_doublecomplex *__u, __CLPK_integer *__ldu,
        __CLPK_doublecomplex *__v, __CLPK_integer *__ldv,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__work, __CLPK_integer *__ncycle,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztgsna_(char *__job, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublecomplex *__vr, __CLPK_integer *__ldvr,
        __CLPK_doublereal *__s, __CLPK_doublereal *__dif, __CLPK_integer *__mm,
        __CLPK_integer *__m, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork, __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztgsy2_(char *__trans, __CLPK_integer *__ijob, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__d__, __CLPK_integer *__ldd,
        __CLPK_doublecomplex *__e, __CLPK_integer *__lde,
        __CLPK_doublecomplex *__f, __CLPK_integer *__ldf,
        __CLPK_doublereal *__scale, __CLPK_doublereal *__rdsum,
        __CLPK_doublereal *__rdscal,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztgsyl_(char *__trans, __CLPK_integer *__ijob, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__d__, __CLPK_integer *__ldd,
        __CLPK_doublecomplex *__e, __CLPK_integer *__lde,
        __CLPK_doublecomplex *__f, __CLPK_integer *__ldf,
        __CLPK_doublereal *__scale, __CLPK_doublereal *__dif,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__iwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztpcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap, __CLPK_doublereal *__rcond,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztprfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztptri_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztptrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztpttf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__ap, __CLPK_doublecomplex *__arf,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztpttr_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrcon_(char *__norm, char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublereal *__rcond, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrevc_(char *__side, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublecomplex *__t, __CLPK_integer *__ldt,
        __CLPK_doublecomplex *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublecomplex *__vr, __CLPK_integer *__ldvr,
        __CLPK_integer *__mm, __CLPK_integer *__m, __CLPK_doublecomplex *__work,
        __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrexc_(char *__compq, __CLPK_integer *__n, __CLPK_doublecomplex *__t,
        __CLPK_integer *__ldt, __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_integer *__ifst, __CLPK_integer *__ilst,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrrfs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__x, __CLPK_integer *__ldx,
        __CLPK_doublereal *__ferr, __CLPK_doublereal *__berr,
        __CLPK_doublecomplex *__work, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrsen_(char *__job, char *__compq, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublecomplex *__t, __CLPK_integer *__ldt,
        __CLPK_doublecomplex *__q, __CLPK_integer *__ldq,
        __CLPK_doublecomplex *__w, __CLPK_integer *__m, __CLPK_doublereal *__s,
        __CLPK_doublereal *__sep, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrsna_(char *__job, char *__howmny, __CLPK_logical *__select,
        __CLPK_integer *__n, __CLPK_doublecomplex *__t, __CLPK_integer *__ldt,
        __CLPK_doublecomplex *__vl, __CLPK_integer *__ldvl,
        __CLPK_doublecomplex *__vr, __CLPK_integer *__ldvr,
        __CLPK_doublereal *__s, __CLPK_doublereal *__sep, __CLPK_integer *__mm,
        __CLPK_integer *__m, __CLPK_doublecomplex *__work,
        __CLPK_integer *__ldwork, __CLPK_doublereal *__rwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrsyl_(char *__trana, char *__tranb, __CLPK_integer *__isgn,
        __CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublereal *__scale,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrti2_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrtri_(char *__uplo, char *__diag, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrtrs_(char *__uplo, char *__trans, char *__diag, __CLPK_integer *__n,
        __CLPK_integer *__nrhs, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__b, __CLPK_integer *__ldb,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrttf_(char *__transr, char *__uplo, __CLPK_integer *__n,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__arf,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztrttp_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__ap,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztzrqf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int ztzrzf_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zung2l_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zung2r_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zungbr_(char *__vect, __CLPK_integer *__m, __CLPK_integer *__n,
        __CLPK_integer *__k, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunghr_(__CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zungl2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunglq_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zungql_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zungqr_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zungr2_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zungrq_(__CLPK_integer *__m, __CLPK_integer *__n, __CLPK_integer *__k,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zungtr_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunm2l_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunm2r_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmbr_(char *__vect, char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmhr_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__ilo, __CLPK_integer *__ihi,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__c__,
        __CLPK_integer *__ldc, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunml2_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmlq_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmql_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmqr_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmr2_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmr3_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__l,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__c__,
        __CLPK_integer *__ldc, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmrq_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_doublecomplex *__a,
        __CLPK_integer *__lda, __CLPK_doublecomplex *__tau,
        __CLPK_doublecomplex *__c__, __CLPK_integer *__ldc,
        __CLPK_doublecomplex *__work, __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmrz_(char *__side, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_integer *__k, __CLPK_integer *__l,
        __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__c__,
        __CLPK_integer *__ldc, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zunmtr_(char *__side, char *__uplo, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublecomplex *__a, __CLPK_integer *__lda,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__c__,
        __CLPK_integer *__ldc, __CLPK_doublecomplex *__work,
        __CLPK_integer *__lwork,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zupgtr_(char *__uplo, __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__q,
        __CLPK_integer *__ldq, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int zupmtr_(char *__side, char *__uplo, char *__trans, __CLPK_integer *__m,
        __CLPK_integer *__n, __CLPK_doublecomplex *__ap,
        __CLPK_doublecomplex *__tau, __CLPK_doublecomplex *__c__,
        __CLPK_integer *__ldc, __CLPK_doublecomplex *__work,
        __CLPK_integer *__info)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlamc1_(__CLPK_integer *__beta, __CLPK_integer *__t, __CLPK_logical *__rnd,
        __CLPK_logical *__ieee1)
API_AVAILABLE(macos(10.2), ios(4.0));

int ilaver_(__CLPK_integer *__vers_major__, __CLPK_integer *__vers_minor__,
        __CLPK_integer *__vers_patch__)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slamch_(char *__cmach)
API_AVAILABLE(macos(10.2), ios(4.0));

int slamc1_(__CLPK_integer *__beta, __CLPK_integer *__t, __CLPK_logical *__rnd,
        __CLPK_logical *__ieee1)
API_AVAILABLE(macos(10.2), ios(4.0));

int slamc2_(__CLPK_integer *__beta, __CLPK_integer *__t, __CLPK_logical *__rnd,
        __CLPK_real *__eps, __CLPK_integer *__emin, __CLPK_real *__rmin,
        __CLPK_integer *__emax,
        __CLPK_real *__rmax)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal slamc3_(__CLPK_real *__a,
        __CLPK_real *__b)
API_AVAILABLE(macos(10.2), ios(4.0));

int slamc4_(__CLPK_integer *__emin, __CLPK_real *__start,
        __CLPK_integer *__base)
API_AVAILABLE(macos(10.2), ios(4.0));

int slamc5_(__CLPK_integer *__beta, __CLPK_integer *__p, __CLPK_integer *__emin,
        __CLPK_logical *__ieee, __CLPK_integer *__emax,
        __CLPK_real *__rmax)
API_AVAILABLE(macos(10.2), ios(4.0));


__CLPK_doublereal dlamch_(char *__cmach)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlamc1_(__CLPK_integer *__beta, __CLPK_integer *__t, __CLPK_logical *__rnd,
        __CLPK_logical *__ieee1)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlamc2_(__CLPK_integer *__beta, __CLPK_integer *__t, __CLPK_logical *__rnd,
        __CLPK_doublereal *__eps, __CLPK_integer *__emin,
        __CLPK_doublereal *__rmin, __CLPK_integer *__emax,
        __CLPK_doublereal *__rmax)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_doublereal dlamc3_(__CLPK_doublereal *__a,
        __CLPK_doublereal *__b)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlamc4_(__CLPK_integer *__emin, __CLPK_doublereal *__start,
        __CLPK_integer *__base)
API_AVAILABLE(macos(10.2), ios(4.0));

int dlamc5_(__CLPK_integer *__beta, __CLPK_integer *__p, __CLPK_integer *__emin,
        __CLPK_logical *__ieee, __CLPK_integer *__emax,
        __CLPK_doublereal *__rmax)
API_AVAILABLE(macos(10.2), ios(4.0));

__CLPK_integer ilaenv_(__CLPK_integer *__ispec, char *__name__, char *__opts,
        __CLPK_integer *__n1, __CLPK_integer *__n2, __CLPK_integer *__n3,
        __CLPK_integer *__n4)
API_AVAILABLE(macos(10.2), ios(4.0));


#ifdef __cplusplus
}
#endif
#endif /* __CLAPACK_H */
