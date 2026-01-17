
#pragma once

#ifdef __cplusplus
#include <complex>
#else
#include <complex.h>
#endif


#ifdef __cplusplus
    typedef std::complex<float>  __LAPACK_float_complex;
    typedef std::complex<double> __LAPACK_double_complex;
#else
    typedef float complex  __LAPACK_float_complex;
    typedef double complex __LAPACK_double_complex;
#endif

#ifdef __cplusplus
extern "C" {
#endif

// For platforms that are neither ILP64 nor LP64, this will default to LP64 (for instance, arm64_32).
#if defined( ACCELERATE_LAPACK_ILP64 )
    typedef long __LAPACK_int;
    typedef long __LAPACK_bool;
#else
    typedef int  __LAPACK_int;
    typedef int  __LAPACK_bool;  // Because the fortran logical is 4 bytes
#endif

// Function pointers for various LAPACK routines

// sgees, sgeesx
typedef __LAPACK_bool (*__LAPACK_sgees_func_ptr)(float *, float *);

// sgges, sgges3, sggesx
typedef __LAPACK_bool (*__LAPACK_sgges_func_ptr)(float *, float *, float *);

// dgees, dgeesx
typedef __LAPACK_bool (*__LAPACK_dgees_func_ptr)(double *, double *);

// dgges, dgges3, dggesx
typedef __LAPACK_bool (*__LAPACK_dgges_func_ptr)(double *, double *, double *);

// cgees, cgeesx
typedef __LAPACK_bool (*__LAPACK_cgees_func_ptr)(__LAPACK_float_complex *);

// cgges, cgges3, cggesx
typedef __LAPACK_bool (*__LAPACK_cgges_func_ptr)(__LAPACK_float_complex *, __LAPACK_float_complex *);

// zgees, zgeesx
typedef __LAPACK_bool (*__LAPACK_zgees_func_ptr)(__LAPACK_double_complex *);

// zgges, zgges3, zggesx
typedef __LAPACK_bool (*__LAPACK_zgges_func_ptr)(__LAPACK_double_complex *, __LAPACK_double_complex *);

#ifdef __cplusplus
}
#endif
