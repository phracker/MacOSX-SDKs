/*
     File:       vecLib/vBLAS.h
 
     Contains:   Header for the Basic Linear Algebra Subprograms, with Apple extensions.
 
     Version:    vecLib-138.1~9
 
     Copyright:  © 2000-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/* ==========================================================================================================================*/


/*
   =================================================================================================
   Definitions of the Basic Linear Algebra Subprograms (BLAS) as provided by Apple Computer.  At
   present this is a subset of the "legacy" FORTRAN and C interfaces.  Only single precision forms
   are provided, and only the most useful routines.  For example only the general matrix forms are
   provided, not the symmetric, Hermitian, or triangular forms.  A few additional functions, unique
   to Mac OS, have also been provided.  These are clearly documented as Apple extensions.
   Documentation on the BLAS standard, including reference implementations, can be found on the web
   starting from the BLAS FAQ page at these URLs (at least as of August 2000):
        http://www.netlib.org/blas/faq.html
        http://www.netlib.org/blas/blast-forum/blast-forum.html
   =================================================================================================
*/


/*
   =================================================================================================
   Matrix shape and storage
   ========================
   Keeping the various matrix shape and storage parameters straight can be difficult.  The BLAS
   documentation generally makes a distinction between the concpetual "matrix" and the physical
   "array".  However there are a number of places where this becomes fuzzy because of the overall
   bias towards FORTRAN's column major storage.  The confusion is made worse by style differences
   between the level 2 and level 3 functions.  It is amplified further by the explicit choice of row
   or column major storage in the C interface.
   The storage order does not affect the actual computation that is performed.  That is, it does not
   affect the results other than where they appear in memory.  It does affect the values passed
   for so-called "leading dimension" parameters, such as lda in sgemv.  These are always the major
   stride in storage, allowing operations on rectangular subsets of larger matrices.  For row major
   storage this is the number of columns in the parent matrix, and for column major storage this is
   the number of rows in the parent matrix.
   For the level 2 functions, which deal with only a single matrix, the matrix shape parameters are
   always M and N.  These are the logical shape of the matrix, M rows by N columns.  The transpose
   parameter, such as transA in sgemv, defines whether the regular matrix or its transpose is used
   in the operation.  This affects the implicit length of the input and output vectors.  For example,
   if the regular matrix A is used in sgemv, the input vector X has length N, the number of columns
   of A, and the output vector Y has length M, the number of rows of A.  The length of the input and
   output vectors is not affected by the storage order of the matrix.
   The level 3 functions deal with 2 input matrices and one output matrix, the matrix shape parameters
   are M, N, and K.  The logical shape of the output matrix is always M by N, while K is the common
   dimension of the input matrices.  Like level 2, the transpose parameters, such as transA and transB
   in sgemm, define whether the regular input or its transpose is used in the operation.  However
   unlike level 2, in level 3 the transpose parameters affect the implicit shape of the input matrix.
   Consider sgemm, which computes "C = (alpha * A * B) + (beta * C)", where A and B might be regular
   or transposed.  The logical shape of C is always M rows by N columns.  The physical shape depends
   on the storage order parameter.  Using column major storage the declaration of C (the array) in C
   (the language) would be something like "float C[N][M]".  The logical shape of A without transposition
   is M by K, and B is K by N.  The one storage order parameter affects all three matrices.
   For those readers still wondering about the style differences between level 2 and level 3, they
   involve whether the input or output shapes are explicit.  For level 2, the input matrix shape is
   always M by N.  The input and output vector lengths are implicit and vary according to the
   transpose parameter.  For level 3, the output matrix shape is always M by N.  The input matrix
   shapes are implicit and vary according to the transpose parameters.
   =================================================================================================
*/


/* ==========================================================================================================================*/


#ifndef __VBLAS__
#define __VBLAS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint on
#endif


/*
   ==========================================================================================================================
   Types and constants
   ===================
*/


enum CBLAS_ORDER {
  CblasRowMajor                 = 101,
  CblasColMajor                 = 102
};
typedef enum CBLAS_ORDER CBLAS_ORDER;

enum CBLAS_TRANSPOSE {
  CblasNoTrans                  = 111,
  CblasTrans                    = 112,
  CblasConjTrans                = 113
};
typedef enum CBLAS_TRANSPOSE CBLAS_TRANSPOSE;

enum CBLAS_UPLO {
  CblasUpper                    = 121,
  CblasLower                    = 122
};
typedef enum CBLAS_UPLO CBLAS_UPLO;

enum CBLAS_DIAG {
  CblasNonUnit                  = 131,
  CblasUnit                     = 132
};
typedef enum CBLAS_DIAG CBLAS_DIAG;

enum CBLAS_SIDE {
  CblasLeft                     = 141,
  CblasRight                    = 142
};
typedef enum CBLAS_SIDE CBLAS_SIDE;


/*
   ------------------------------------------------------------------------------------------------------------------
   IsAlignedCount   - True if an integer is positive and a multiple of 4.  Negative strides are considered unaligned.
   IsAlignedAddr    - True if an address is a multiple of 16.
*/

#define IsAlignedCount(n)   ( (n > 0) && ((n & 3L) == 0) )
#define IsAlignedAddr(a)    ( ((long)a & 15L) == 0 )

/*
   ==========================================================================================================================
   ==========================================================================================================================
   Legacy BLAS Functions
   ==========================================================================================================================
   ==========================================================================================================================
*/


/*
   ==========================================================================================================================
   Level 1 Single Precision Functions
   ==================================
*/


/*
 *  cblas_sdot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
cblas_sdot(
  int            N,
  const float *  X,
  int            incX,
  const float *  Y,
  int            incY)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  cblas_snrm2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
cblas_snrm2(
  int            N,
  const float *  X,
  int            incX)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  cblas_sasum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
cblas_sasum(
  int            N,
  const float *  X,
  int            incX)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  cblas_isamax()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern int 
cblas_isamax(
  int            N,
  const float *  X,
  int            incX)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  cblas_sswap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
cblas_sswap(
  int      N,
  float *  X,
  int      incX,
  float *  Y,
  int      incY)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  cblas_scopy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
cblas_scopy(
  int            N,
  const float *  X,
  int            incX,
  float *        Y,
  int            incY)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  cblas_saxpy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
cblas_saxpy(
  int            N,
  float          alpha,
  const float *  X,
  int            incX,
  float *        Y,
  int            incY)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  cblas_srot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
cblas_srot(
  int      N,
  float *  X,
  int      incX,
  float *  Y,
  int      incY,
  float    c,
  float    s)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  cblas_sscal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
cblas_sscal(
  int      N,
  float    alpha,
  float *  X,
  int      incX)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
   ==========================================================================================================================
   Level 1 Double Precision Functions
   ==================================
*/


/* *** TBD ****/


/*
   ==========================================================================================================================
   Level 1 Complex Single Precision Functions
   ==========================================
*/


/* *** TBD ****/


/*
   ==========================================================================================================================
   Level 2 Single Precision Functions
   ==================================
*/


/*
 *  cblas_sgemv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
cblas_sgemv(
  CBLAS_ORDER       order,
  CBLAS_TRANSPOSE   transA,
  int               M,
  int               N,
  float             alpha,
  const float *     A,
  int               lda,
  const float *     X,
  int               incX,
  float             beta,
  float *           Y,
  int               incY)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
   ==========================================================================================================================
   Level 2 Double Precision Functions
   ==================================
*/


/* *** TBD ****/


/*
   ==========================================================================================================================
   Level 2 Complex Single Precision Functions
   ==========================================
*/


/* *** TBD ****/


/*
   ==========================================================================================================================
   Level 3 Single Precision Functions
   ==================================
*/


/*
 *  cblas_sgemm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
cblas_sgemm(
  CBLAS_ORDER       order,
  CBLAS_TRANSPOSE   transA,
  CBLAS_TRANSPOSE   transB,
  int               M,
  int               N,
  int               K,
  float             alpha,
  const float *     A,
  int               lda,
  const float *     B,
  int               ldb,
  float             beta,
  float *           C,
  int               ldc)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
   ==========================================================================================================================
   Level 3 Double Precision Functions
   ==================================
*/


/* *** TBD ****/


/*
   ==========================================================================================================================
   Level 3 Complex Single Precision Functions
   ==========================================
*/


/* *** TBD ****/


/*
   ==========================================================================================================================
   ==========================================================================================================================
   Latest Standard BLAS Functions
   ==========================================================================================================================
   ==========================================================================================================================
*/


/* *** TBD ****/


/*
   ==========================================================================================================================
   ==========================================================================================================================
   Additional Functions from Apple
   ==========================================================================================================================
   ==========================================================================================================================
*/


/*
   -------------------------------------------------------------------------------------------------
   These routines provide optimized, AltiVec-only support for common small matrix multiplications.
   They do not check for the availability of AltiVec instructions or parameter errors.  They just do
   the multiplication as fast as possible.  Matrices are presumed to use row major storage.  Because
   these are all square, column major matrices can be multiplied by simply reversing the parameters.
*/


#ifdef __VEC__
typedef vector float                    ConstVectorFloat;
/*
 *  vMultVecMat_4x4()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultVecMat_4x4(
  ConstVectorFloat   X[1],
  ConstVectorFloat   A[4][1],
  vector float       Y[1])                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vMultMatVec_4x4()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultMatVec_4x4(
  ConstVectorFloat   A[4][1],
  ConstVectorFloat   X[1],
  vector float       Y[1])                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vMultMatMat_4x4()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultMatMat_4x4(
  ConstVectorFloat   A[4][1],
  ConstVectorFloat   B[4][1],
  vector float       C[4][1])                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  vMultVecMat_8x8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultVecMat_8x8(
  ConstVectorFloat   X[2],
  ConstVectorFloat   A[8][2],
  vector float       Y[2])                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vMultMatVec_8x8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultMatVec_8x8(
  ConstVectorFloat   A[8][2],
  ConstVectorFloat   X[2],
  vector float       Y[2])                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vMultMatMat_8x8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultMatMat_8x8(
  ConstVectorFloat   A[8][2],
  ConstVectorFloat   B[8][2],
  vector float       C[8][2])                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  vMultVecMat_16x16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultVecMat_16x16(
  ConstVectorFloat   X[4],
  ConstVectorFloat   A[16][4],
  vector float       Y[4])                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vMultMatVec_16x16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultMatVec_16x16(
  ConstVectorFloat   A[16][4],
  ConstVectorFloat   X[4],
  vector float       Y[4])                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vMultMatMat_16x16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultMatMat_16x16(
  ConstVectorFloat   A[16][4],
  ConstVectorFloat   B[16][4],
  vector float       C[16][4])                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  vMultVecMat_32x32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultVecMat_32x32(
  ConstVectorFloat   X[8],
  ConstVectorFloat   A[32][8],
  vector float       Y[8])                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vMultMatVec_32x32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultMatVec_32x32(
  ConstVectorFloat   A[32][8],
  ConstVectorFloat   X[8],
  vector float       Y[8])                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vMultMatMat_32x32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
vMultMatMat_32x32(
  ConstVectorFloat   A[32][8],
  ConstVectorFloat   B[32][8],
  vector float       C[32][8])                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#endif  /* defined(__VEC__) */

/*
   ==========================================================================================================================
   Error handling
   ==============
*/


/*
   -------------------------------------------------------------------------------------------------
   The BLAS standard requires that parameter errors be reported and cause the program to terminate.
   The default behavior for the Mac OS implementation of the BLAS is to print a message in English
   to stdout using printf and call exit with EXIT_FAILURE as the status.  If this is adequate, then
   you need do nothing more or worry about error handling.
   The BLAS standard also mentions a function, cblas_xerbla, suggesting that a program provide its
   own implementation to override the default error handling.  This will not work in the shared
   library environment of Mac OS 9.  Instead the Mac OS implementation provides a means to install
   an error handler.  There can only be one active error handler, installing a new one causes any
   previous handler to be forgotten.  Passing a null function pointer installs the default handler.
   The default handler is automatically installed at startup and implements the default behavior
   defined above.
   An error handler may return, it need not abort the program.  If the error handler returns, the
   BLAS routine also returns immediately without performing any processing.  Level 1 functions that
   return a numeric value return zero if the error handler returns.
*/

typedef CALLBACK_API_C( void , BLASParamErrorProc )(const char *funcName, const char *paramName, const int *paramPos, const int *paramValue);
/*
 *  SetBLASParamErrorProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SetBLASParamErrorProc(BLASParamErrorProc ErrorProc)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
   =================================================================================================
   Prototypes for FORTRAN BLAS
   ===========================
   These are prototypes for the FORTRAN callable BLAS functions.  They are implemented in C for
   Mac OS, as thin shims that simply call the C BLAS counterpart.  These routines should never be
   called from C, but need to be included here so they will get output for the stub library.  It
   won't hurt to call them from C, but who would want to since you can't pass literals for sizes?
   FORTRAN compilers are typically MPW tools and use PPCLink, so they will link with the official
   vecLib stub from Apple.
   =================================================================================================
*/
/*
 *  SDOT()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
SDOT(
  const int *    N,
  const float *  X,
  const int *    incX,
  const float *  Y,
  const int *    incY)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SNRM2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
SNRM2(
  const int *    N,
  const float *  X,
  const int *    incX)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SASUM()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
SASUM(
  const int *    N,
  const float *  X,
  const int *    incX)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ISAMAX()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern int 
ISAMAX(
  const int *    N,
  const float *  X,
  const int *    incX)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SSWAP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SSWAP(
  const int *  N,
  float *      X,
  const int *  incX,
  float *      Y,
  const int *  incY)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SCOPY()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SCOPY(
  const int *    N,
  const float *  X,
  const int *    incX,
  float *        Y,
  const int *    incY)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SAXPY()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SAXPY(
  const int *    N,
  const float *  alpha,
  const float *  X,
  const int *    incX,
  float *        Y,
  const int *    incY)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SROT()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SROT(
  const int *    N,
  float *        X,
  const int *    incX,
  float *        Y,
  const int *    incY,
  const float *  c,
  const float *  s)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SSCAL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SSCAL(
  const int *    N,
  const float *  alpha,
  float *        X,
  const int *    incX)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SGEMV()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SGEMV(
  const char *   transA,
  const int *    M,
  const int *    N,
  const float *  alpha,
  const float *  A,
  const int *    lda,
  const float *  X,
  const int *    incX,
  const float *  beta,
  float *        Y,
  const int *    incY)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SGEMM()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SGEMM(
  const char *   transA,
  const char *   transB,
  const int *    M,
  const int *    N,
  const int *    K,
  const float *  alpha,
  const float *  A,
  const int *    lda,
  const float *  B,
  const int *    ldb,
  const float *  beta,
  float *        C,
  const int *    ldc)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ==========================================================================================================================*/
/* ==========================================================================================================================*/




#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __VBLAS__ */

