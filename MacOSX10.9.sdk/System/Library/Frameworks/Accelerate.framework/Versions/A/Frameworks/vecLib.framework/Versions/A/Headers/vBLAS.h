#ifndef __VBLAS__
#define __VBLAS__

#include <stdint.h>
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
    
#ifndef CBLAS_H
#include <vecLib/cblas.h>
#endif
typedef enum CBLAS_ORDER CBLAS_ORDER;
typedef enum CBLAS_TRANSPOSE CBLAS_TRANSPOSE;
typedef enum CBLAS_UPLO CBLAS_UPLO;
typedef enum CBLAS_DIAG CBLAS_DIAG;
typedef enum CBLAS_SIDE CBLAS_SIDE;

/*
   ------------------------------------------------------------------------------------------------------------------
   IsAlignedCount   - True if an integer is positive and a multiple of 4.  Negative strides are considered unaligned.
   IsAlignedAddr    - True if an address is a multiple of 16.
*/

#define IsAlignedCount(n)   ( (n > 0) && ((n & 3) == 0) )
#define IsAlignedAddr(a)    ( ((long)a & 15L) == 0 )

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
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
SDOT(
  const int *    /* N */,
  const float *  /* X */,
  const int *    /* incX */,
  const float *  /* Y */,
  const int *    /* incY */)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SNRM2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
SNRM2(
  const int *    /* N */,
  const float *  /* X */,
  const int *    /* incX */)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SASUM()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern float 
SASUM(
  const int *    /* N */,
  const float *  /* X */,
  const int *    /* incX */)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ISAMAX()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern int 
ISAMAX(
  const int *    /* N */,
  const float *  /* X */,
  const int *    /* incX */)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SSWAP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SSWAP(
  const int *    /* N */,
  const float *  /* X */,
  const int *    /* incX */,
  float *        /* Y */,
  const int *    /* incY */)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SCOPY()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SCOPY(
  const int *    /* N */,
  const float *  /* X */,
  const int *    /* incX */,
  float *        /* Y */,
  const int *    /* incY */)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SAXPY()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SAXPY(
  const int *    /* N */,
  const float *  /* alpha */,
  const float *  /* X */,
  const int *    /* incX */,
  float *        /* Y */,
  const int *    /* incY */)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SROT()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SROT(
  const int *    /* N */,
  float *        /* X */,
  const int *    /* incX */,
  float *        /* Y */,
  const int *    /* incY */,
  const float *  /* c */,
  const float *  /* s */)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SSCAL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SSCAL(
  const int *    /* N */,
  const float *  /* alpha */,
  float *        /* X */,
  const int *    /* incX */)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SGEMV()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SGEMV(
  const char *   /* transA */,
  const int *    /* M */,
  const int *    /* N */,
  const float *  /* alpha */,
  const float *  /* A */,
  const int *    /* lda */,
  const float *  /* X */,
  const int *    /* incX */,
  const float *  /* beta */,
  float *        /* Y */,
  const int *    /* incY */)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SGEMM()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0.2 and later
 */
extern void 
SGEMM(
  const char *   /* transA */,
  const char *   /* transB */,
  const int *    /* M */,
  const int *    /* N */,
  const int *    /* K */,
  const float *  /* alpha */,
  const float *  /* A */,
  const int *    /* lda */,
  const float *  /* B */,
  const int *    /* ldb */,
  const float *  /* beta */,
  float *        /* C */,
  const int *    /* ldc */)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ==========================================================================================================================*/
/* ==========================================================================================================================*/

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* __VBLAS__ */

