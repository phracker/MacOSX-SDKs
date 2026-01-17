/*
     File:       vecLib/vDSP.h
 
     Contains:   AltiVec DSP Interfaces
 
     Version:    vecLib-153.2~2
 
     Copyright:  © 2000-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VDSP__
#define __VDSP__

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

#pragma options align=mac68k

struct DSPComplex {
  float               real;
  float               imag;
};
typedef struct DSPComplex               DSPComplex;
struct DSPSplitComplex {
  float *             realp;
  float *             imagp;
};
typedef struct DSPSplitComplex          DSPSplitComplex;
struct DSPDoubleComplex {
  double              real;
  double              imag;
};
typedef struct DSPDoubleComplex         DSPDoubleComplex;
struct DSPDoubleSplitComplex {
  double *            realp;
  double *            imagp;
};
typedef struct DSPDoubleSplitComplex    DSPDoubleSplitComplex;
typedef struct OpaqueFFTSetup*          FFTSetup;
typedef struct OpaqueFFTSetupD*         FFTSetupD;
typedef SInt32 FFTDirection;
enum {
  kFFTDirection_Forward         = 1,
  kFFTDirection_Inverse         = -1
};

typedef SInt32 FFTRadix;
enum {
  kFFTRadix2                    = 0,
  kFFTRadix3                    = 1,
  kFFTRadix5                    = 2
};

/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    The criteria to invoke the PowerPC vector implementation is subject to     
    change and become less restrictive in the future.                          
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/

/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions create_fftsetup and destroy_fftsetup.
              create_fftsetupD and destroy_fftsetupD.
              
    create_fftsetup will allocate memory and setup a weight array used by      
    the FFT. The call destroy_fftsetup will free the array.                    
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  create_fftsetup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern FFTSetup 
create_fftsetup(
  UInt32     log2n,
  FFTRadix   radix)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  destroy_fftsetup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
destroy_fftsetup(FFTSetup setup)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  create_fftsetupD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern FFTSetupD 
create_fftsetupD(
  UInt32     log2n,
  FFTRadix   radix)                                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  destroy_fftsetupD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
destroy_fftsetupD(FFTSetupD setup)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions ctoz and ztoc.
              ctozD and ztocD.
    
    ctoz converts a complex array to a complex-split array
    ztoc converts a complex-split array to a complex array
    
    Criteria to invoke PowerPC vector code:    
        1. size > 3
        2. strideC = 2
        3. strideZ = 1
        4. C is 16-byte aligned and Z.realp and Z.imagp are 16-byte aligned.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  ctoz()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
ctoz(
  const DSPComplex   C[],
  SInt32             strideC,
  DSPSplitComplex *  Z,
  SInt32             strideZ,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ztoc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
ztoc(
  const DSPSplitComplex *  Z,
  SInt32                   strideZ,
  DSPComplex               C[],
  SInt32                   strideC,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ctozD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ctozD(
  const DSPDoubleComplex   C[],
  SInt32                   strideC,
  DSPDoubleSplitComplex *  Z,
  SInt32                   strideZ,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ztocD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ztocD(
  const DSPDoubleSplitComplex *  Z,
  SInt32                         strideZ,
  DSPDoubleComplex               C[],
  SInt32                         strideC,
  UInt32                         size)                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions fft_zip and fft_zipt 
              fft_zipD and fft_ziptD
              
    In-place Split Complex Fourier Transform with or without temporary memory.
            
      Criteria to invoke PowerPC vector code:    
        
        1. ioData.realp and ioData.imagp must be 16-byte aligned.
        2. stride = 1
        3. 2 <= log2n <= 20
        4. bufferTemp.realp and bufferTemp.imagp must be 16-byte aligned.
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The size of temporary memory for each part
      is the lower value of 4*n and 16k.  Direction can be either
      kFFTDirection_Forward or kFFTDirection_Inverse.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  fft_zip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft_zip(
  FFTSetup           setup,
  DSPSplitComplex *  ioData,
  SInt32             stride,
  UInt32             log2n,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft_zipt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft_zipt(
  FFTSetup           setup,
  DSPSplitComplex *  ioData,
  SInt32             stride,
  DSPSplitComplex *  bufferTemp,
  UInt32             log2n,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft_zipD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft_zipD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   stride,
  UInt32                   log2n,
  FFTDirection             direction)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft_ziptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft_ziptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   stride,
  DSPDoubleSplitComplex *  bufferTemp,
  UInt32                   log2n,
  FFTDirection             direction)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
     Functions fft_zop and fft_zopt
               fft_zopD and fft_zoptD
     
     Out-of-place Split Complex Fourier Transform with or without temporary
     memory
            
      Criteria to invoke PowerPC vector code:  
        
        1. signal.realp and signal.imagp must be 16-byte aligned.
        2. signalStride = 1
        3. result.realp and result.imagp must be 16-byte aligned.
        4. strideResult = 1
        5. 2 <= log2n <= 20
        6. bufferTemp.realp and bufferTemp.imagp must be 16-byte aligned.
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The size of temporary memory for each part
      is the lower value of 4*n and 16k.  Direction can be either
      kFFTDirection_Forward or kFFTDirection_Inverse.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  fft_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft_zop(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             log2n,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft_zopt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft_zopt(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  DSPSplitComplex *  bufferTemp,
  UInt32             log2n,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft_zopD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   log2n,
  FFTDirection             direction)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft_zoptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft_zoptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  DSPDoubleSplitComplex *  bufferTemp,
  UInt32                   log2n,
  FFTDirection             direction)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions fft_zrip and fft_zript
              fft_zripD and fft_zriptD
              
    In-Place Real Fourier Transform with or without temporary memory,
    split Complex Format
            
      Criteria to invoke PowerPC vector code:    
        1. ioData.realp and ioData.imagp must be 16-byte aligned.
        2. stride = 1
        3. 3 <= log2n <= 13
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The size of temporary memory for each part
      is the lower value of 4*n and 16k.  Direction can be either
      kFFTDirection_Forward or kFFTDirection_Inverse.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  fft_zrip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft_zrip(
  FFTSetup           setup,
  DSPSplitComplex *  ioData,
  SInt32             stride,
  UInt32             log2n,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft_zript()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft_zript(
  FFTSetup           setup,
  DSPSplitComplex *  ioData,
  SInt32             stride,
  DSPSplitComplex *  bufferTemp,
  UInt32             log2n,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft_zripD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft_zripD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   stride,
  UInt32                   log2n,
  FFTDirection             flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft_zriptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft_zriptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   stride,
  DSPDoubleSplitComplex *  bufferTemp,
  UInt32                   log2n,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions fft_zrop and fft_zropt
              fft_zropD and fft_zroptD
              
    Out-of-Place Real Fourier Transform with or without temporary memory,
    split Complex Format
            
      Criteria to invoke PowerPC vector code:  
        1. signal.realp and signal.imagp must be 16-byte aligned.
        2. signalStride = 1
        3. result.realp and result.imagp must be be 16-byte aligned.
        4. strideResult = 1
        5. 3 <= log2n <= 13
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The size of temporary memory for each part
      is the lower value of 4*n and 16k.  Direction can be either
      kFFTDirection_Forward or kFFTDirection_Inverse.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  fft_zrop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft_zrop(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             log2n,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft_zropt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft_zropt(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  DSPSplitComplex *  bufferTemp,
  UInt32             log2n,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft_zropD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft_zropD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   log2n,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft_zroptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft_zroptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  DSPDoubleSplitComplex *  bufferTemp,
  UInt32                   log2n,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions fft2d_zip and fft2d_zipt
              fft2d_zipD and fft2d_ziptD
              
    In-place two dimensional Split Complex Fourier Transform with or without
    temporary memory
            
      Criteria to invoke PowerPC vector code:  
        1. ioData.realp and ioData.imagp must be 16-byte aligned.
        2. strideInRow = 1;
        3. strideInCol must be a multiple of 4
        4. 2 <= log2nInRow <= 12
        5. 2 <= log2nInCol <= 12
        6. bufferTemp.realp and bufferTemp.imagp must be 16-byte aligned.
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The size of temporary memory for each part
      is the lower value of 4*n and 16k.  ( log2n = log2nInRow + log2nInCol ) 
      Direction can be either kFFTDirection_Forward or kFFTDirection_Inverse.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  fft2d_zip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft2d_zip(
  FFTSetup           setup,
  DSPSplitComplex *  ioData,
  SInt32             strideInRow,
  SInt32             strideInCol,
  UInt32             log2nInCol,
  UInt32             log2nInRow,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft2d_zipt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft2d_zipt(
  FFTSetup           setup,
  DSPSplitComplex *  ioData,
  SInt32             strideInRow,
  SInt32             strideInCol,
  DSPSplitComplex *  bufferTemp,
  UInt32             log2nInCol,
  UInt32             log2nInRow,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft2d_zipD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft2d_zipD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   strideInRow,
  SInt32                   strideInCol,
  UInt32                   log2nInCol,
  UInt32                   log2nInRow,
  FFTDirection             direction)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft2d_ziptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft2d_ziptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   strideInRow,
  SInt32                   strideInCol,
  DSPDoubleSplitComplex *  bufferTemp,
  UInt32                   log2nInCol,
  UInt32                   log2nInRow,
  FFTDirection             direction)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions fft2d_zop and fft2d_zopt
              fft2d_zopD and fft2d_zoptD
              
    Out-of-Place two dimemsional Split Complex Fourier Transform with or
    without temporary memory
            
      Criteria to invoke PowerPC vector code:  
        
        1. signal.realp and signal.imagp must be 16-byte aligned.
        2. signalStrideInRow = 1;
        3. signalStrideInCol must be a multiple of 4
        4. result.realp and result.imagp must be 16-byte aligned.
        5. strideResultInRow = 1;
        6. strideResultInCol must be a multiple of 4
        7. 2 <= log2nInRow <= 12
        8. 2 <= log2nInCol <= 12
        9. bufferTemp.realp and bufferTemp.imagp must be 16-byte aligned.

      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The size of temporary memory for each part
      is the lower value of 4*n and 16k.  ( log2n = log2nInRow + log2nInCol ) 
      Direction can be either kFFTDirection_Forward or kFFTDirection_Inverse.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  fft2d_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft2d_zop(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStrideInRow,
  SInt32             signalStrideInCol,
  DSPSplitComplex *  result,
  SInt32             strideResultInRow,
  SInt32             strideResultInCol,
  UInt32             log2nInCol,
  UInt32             log2nInRow,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft2d_zopt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft2d_zopt(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStrideInRow,
  SInt32             signalStrideInCol,
  DSPSplitComplex *  result,
  SInt32             strideResultInRow,
  SInt32             strideResultInCol,
  DSPSplitComplex *  bufferTemp,
  UInt32             log2nInCol,
  UInt32             log2nInRow,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft2d_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft2d_zopD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStrideInRow,
  SInt32                   signalStrideInCol,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResultInRow,
  SInt32                   strideResultInCol,
  UInt32                   log2nInCol,
  UInt32                   log2nInRow,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft2d_zoptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft2d_zoptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStrideInRow,
  SInt32                   signalStrideInCol,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResultInRow,
  SInt32                   strideResultInCol,
  DSPDoubleSplitComplex *  bufferTemp,
  UInt32                   log2nInCol,
  UInt32                   log2nInRow,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions fft2d_zrip and fft2d_zript
              fft2d_zripD and fft2d_zriptD
              
    In-place two dimensional Real Fourier Transform with or without temporary
    memory, Split Complex Format
            
      Criteria to invoke PowerPC vector code:  
        1. ioData.realp and ioData.imagp must be 16-byte aligned.
        2. strideInRow = 1;
        3. strideInCol must be a multiple of 4
        4. 3 <= log2nInRow <= 12
        5. 3 <= log2nInCol <= 13
        6. bufferTemp.realp and bufferTemp.imagp must be 16-byte aligned.

      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The size of temporary memory for each part
      is the lower value of 4*n and 16k.  ( log2n = log2nInRow + log2nInCol ) 
      Direction can be either kFFTDirection_Forward or kFFTDirection_Inverse.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  fft2d_zrip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft2d_zrip(
  FFTSetup           setup,
  DSPSplitComplex *  ioData,
  SInt32             strideInRow,
  SInt32             strideInCol,
  UInt32             log2nInCol,
  UInt32             log2nInRow,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft2d_zript()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft2d_zript(
  FFTSetup           setup,
  DSPSplitComplex *  ioData,
  SInt32             strideInRow,
  SInt32             strideInCol,
  DSPSplitComplex *  bufferTemp,
  UInt32             log2nInCol,
  UInt32             log2nInRow,
  FFTDirection       direction)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft2d_zripD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft2d_zripD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   strideInRow,
  SInt32                   strideInCol,
  UInt32                   log2nInCol,
  UInt32                   log2nInRow,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft2d_zriptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft2d_zriptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   strideInRow,
  SInt32                   strideInCol,
  DSPDoubleSplitComplex *  bufferTemp,
  UInt32                   log2nInCol,
  UInt32                   log2nInRow,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Functions fft2d_zrop and fft2d_zropt
              fft2d_zropD and fft2d_zroptD
              
    Out-of-Place Two-Dimemsional Real Fourier Transform with or without
    temporary memory, Split Complex Format
            
      Criteria to invoke PowerPC vector code:  
        1. signal.realp and signal.imagp must be 16-byte aligned.
        2. signalStrideInRow = 1;
        3. signalStrideInCol must be a multiple of 4
        4. result.realp and result.imagp must be 16-byte aligned.
        5. strideResultInRow = 1;
        6. strideResultInCol must be a multiple of 4
        7. 3 <= log2nInRow <= 12
        8. 3 <= log2nInCol <= 13
        9. bufferTemp.realp and bufferTemp.imagp must be 16-byte aligned.

      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The size of temporary memory for each part
      is the lower value of 4*n and 16k.  ( log2n = log2nInRow + log2nInCol ) 
      Direction can be either kFFTDirection_Forward or kFFTDirection_Inverse.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  fft2d_zrop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft2d_zrop(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStrideInRow,
  SInt32             signalStrideInCol,
  DSPSplitComplex *  result,
  SInt32             strideResultInRow,
  SInt32             strideResultInCol,
  UInt32             log2nInCol,
  UInt32             log2nInRow,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft2d_zropt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
fft2d_zropt(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStrideInRow,
  SInt32             signalStrideInCol,
  DSPSplitComplex *  result,
  SInt32             strideResultInRow,
  SInt32             strideResultInCol,
  DSPSplitComplex *  bufferTemp,
  UInt32             log2nInCol,
  UInt32             log2nInRow,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  fft2d_zropD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft2d_zropD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   Kr,
  SInt32                   Kc,
  DSPDoubleSplitComplex *  ioData2,
  SInt32                   Ir,
  SInt32                   Ic,
  UInt32                   log2nc,
  UInt32                   log2nr,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft2d_zroptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft2d_zroptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   Kr,
  SInt32                   Kc,
  DSPDoubleSplitComplex *  ioData2,
  SInt32                   Ir,
  SInt32                   Ic,
  DSPDoubleSplitComplex *  temp,
  UInt32                   log2nc,
  UInt32                   log2nr,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
________________________________________________________________________________
      Functions fftm_zip and fftm_zipt
                fftm_zipD and fftm_ziptD
                
      In-Place multiple One_Dimensional Complex Fourier Transform with or 
      without temporary memory, Split Complex Format
      
         Criteria to invoke PowerPC vector code:
            1. signal.realp and signal.imagp must be 16-byte aligned.
            2. signalStride = 1;
            3. fftStride must be a multiple of 4
            4. 2 <= log2n <= 12
            5. temp.realp and temp.imagp must be 16-byte aligned.
         
         If any of the above criteria are not satisfied, the PowerPC scalar code
         implementation will be used.
________________________________________________________________________________
*/
/*
 *  fftm_zip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zip(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  SInt32             fftStride,
  UInt32             log2n,
  UInt32             numFFT,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zipt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zipt(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  SInt32             fftStride,
  DSPSplitComplex *  temp,
  UInt32             log2n,
  UInt32             numFFT,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zipD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zipD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  SInt32                   fftStride,
  UInt32                   log2n,
  UInt32                   numFFT,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_ziptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_ziptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  SInt32                   fftStride,
  DSPDoubleSplitComplex *  temp,
  UInt32                   log2n,
  UInt32                   numFFT,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
________________________________________________________________________________
      Functions fftm_zop and fftm_zopt
                fftm_zopD and fftm_zoptD
                
      Out-Of-Place multiple One_Dimensional Complex Fourier Transform with or 
      without temporary memory, Split Complex Format
      
         Criteria to invoke PowerPC vector code:
            1. signal.realp and signal.imagp must be 16-byte aligned.
            2. signalStride = 1;
            3. fftStride must be a multiple of 4
            4. result.realp and result.imagp must be 16-byte aligned.
            5. resultStride = 1;
            6. rfftStride must be a multiple of 4
            7. 2 <= log2n <= 12
            8. temp.realp and temp.imagp must be 16-byte aligned.
        
        If any of the above criteria are not satisfied, the PowerPC scalar code
        implementation will be used.
________________________________________________________________________________
*/
/*
 *  fftm_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zop(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  SInt32             fftStride,
  DSPSplitComplex *  result,
  SInt32             resultStride,
  SInt32             rfftStride,
  UInt32             log2n,
  UInt32             numFFT,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zopt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zopt(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  SInt32             fftStride,
  DSPSplitComplex *  result,
  SInt32             resultStride,
  SInt32             rfftStride,
  DSPSplitComplex *  temp,
  UInt32             log2n,
  UInt32             numFFT,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zopD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  SInt32                   fftStride,
  DSPDoubleSplitComplex *  result,
  SInt32                   resultStride,
  SInt32                   rfftStride,
  UInt32                   log2n,
  UInt32                   numFFT,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zoptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zoptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  SInt32                   fftStride,
  DSPDoubleSplitComplex *  result,
  SInt32                   resultStride,
  SInt32                   rfftStride,
  DSPDoubleSplitComplex *  temp,
  UInt32                   log2n,
  UInt32                   numFFT,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
________________________________________________________________________________
      Functions fftm_zrip and fftm_zript
                fftm_zripD and fftm_zriptD
                
      In-Place multiple One_Dimensional Real Fourier Transform with or 
      without temporary memory, Split Complex Format
      
         Criteria to invoke PowerPC vector code:
            1. signal.realp and signal.imagp must be 16-byte aligned.
            2. signalStride = 1;
            3. fftStride must be a multiple of 4
            4. 3 <= log2n <= 13
            5. temp.realp and temp.imagp must be 16-byte aligned.
        If any of the above criteria are not satisfied, the PowerPC scalar code
        implementation will be used.
________________________________________________________________________________
*/
/*
 *  fftm_zrip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zrip(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  SInt32             fftStride,
  UInt32             log2n,
  UInt32             numFFT,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zript()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zript(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  SInt32             fftStride,
  DSPSplitComplex *  temp,
  UInt32             log2n,
  UInt32             numFFT,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zripD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zripD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  SInt32                   fftStride,
  UInt32                   log2n,
  UInt32                   numFFT,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zriptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zriptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  SInt32                   fftStride,
  DSPDoubleSplitComplex *  temp,
  UInt32                   log2n,
  UInt32                   numFFT,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
________________________________________________________________________________
      Functions fftm_zrop and fftm_zropt
                fftm_zropD and fftm_zroptD
                
      Out-Of-Place multiple One_Dimensional Real Fourier Transform with or 
      without temporary memory, Split Complex Format
      
         Criteria to invoke PowerPC vector code:
            1. signal.realp and signal.imagp must be 16-byte aligned.
            2. signalStride = 1;
            3. fftStride must be a multiple of 4
            4. result.realp and result.imagp must be 16-byte aligned.
            5. resultStride = 1;
            6. rfftStride must be a multiple of 4
            7. 3 <= log2n <= 13
            8. temp.realp and temp.imagp must be 16-byte aligned.
         
         If any of the above criteria are not satisfied, the PowerPC scalar code
         implementation will be used.
________________________________________________________________________________
*/
/*
 *  fftm_zrop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zrop(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  SInt32             fftStride,
  DSPSplitComplex *  result,
  SInt32             resultStride,
  SInt32             rfftStride,
  UInt32             log2n,
  UInt32             numFFT,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zropt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zropt(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  SInt32             fftStride,
  DSPSplitComplex *  result,
  SInt32             resultStride,
  SInt32             rfftStride,
  DSPSplitComplex *  temp,
  UInt32             log2n,
  UInt32             numFFT,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zropD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zropD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  SInt32                   fftStride,
  DSPDoubleSplitComplex *  result,
  SInt32                   resultStride,
  SInt32                   rfftStride,
  UInt32                   log2n,
  UInt32                   numFFT,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fftm_zroptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fftm_zroptD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  SInt32                   fftStride,
  DSPDoubleSplitComplex *  result,
  SInt32                   resultStride,
  SInt32                   rfftStride,
  DSPDoubleSplitComplex *  temp,
  UInt32                   log2n,
  UInt32                   numFFT,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
________________________________________________________________________________
      Functions fft3_zop and fft5_zop
                fft3_zopD and fft5_zopD
                
      Out-Of-Place One_Dimensional Complex Fourier Transform in base-3 and 
      base-5 with or without temporary memory, Split Complex Format 
      
         Criteria to invoke PowerPC vector code:
            1. signal.realp and signal.imagp must be 16-byte aligned.
            2. signalStride = 1;
            3. result.realp and result.imagp must be 16-byte aligned.
            4. resultStride = 1;
            5. 3 <= log2n 
         
         If any of the above criteria are not satisfied, the PowerPC scalar code
         implementation will be used.
________________________________________________________________________________
*/
/*
 *  fft3_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft3_zop(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  DSPSplitComplex *  result,
  SInt32             resultStride,
  UInt32             log2n,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft5_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft5_zop(
  FFTSetup           setup,
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  DSPSplitComplex *  result,
  SInt32             resultStride,
  UInt32             log2n,
  SInt32             flag)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft3_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft3_zopD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   K,
  DSPDoubleSplitComplex *  ioData2,
  SInt32                   L,
  UInt32                   log2n,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  fft5_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
fft5_zopD(
  FFTSetupD                setup,
  DSPDoubleSplitComplex *  ioData,
  SInt32                   K,
  DSPDoubleSplitComplex *  ioData2,
  SInt32                   L,
  UInt32                   log2n,
  SInt32                   flag)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function conv
             convD
             
    Floating Point Convolution and Correlation in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. signal and result must have relative alignement.
        2. 4 <= lenFilter <= 256
        3. lenResult > 36
        4. signalStride = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  strideFilter can be positive for
      correlation or negative for convolution.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  conv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
conv(
  const float   signal[],
  SInt32        signalStride,
  const float   filter[],
  SInt32        strideFilter,
  float         result[],
  SInt32        strideResult,
  SInt32        lenResult,
  SInt32        lenFilter)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  convD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
convD(
  const double   signal[],
  SInt32         signalStride,
  const double   filter[],
  SInt32         strideFilter,
  double         result[],
  SInt32         strideResult,
  SInt32         lenResult,
  SInt32         lenFilter)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
_______________________________________________________________________________
     Functions f3x3, f5x5, and imgfir
               f3x3D, f5x5D and imgfirD
               
     Filter, 3x3, 5x5, MxN Single and Double Precision Convolution
     
       Criteria to invoke PowerPC vector code:
         1. signal, filter, and result must have relative alignment and
            be 16-byte aligned.
         2. for f3x3, NC >= 18
         3. for f5x5, NC >= 20
         4. for imgfir, NC >= 20
       
       If any of the above criteria are not satisfied, the PowerPC scalar code
       implementation will be used.
_______________________________________________________________________________
*/
/*
 *  f3x3()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
f3x3(
  float *  signal,
  SInt32   rowStride,
  SInt32   colStride,
  float *  filter,
  float *  result)                                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  f3x3D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
f3x3D(
  double *  signal,
  SInt32    rowStride,
  SInt32    colStride,
  double *  filter,
  double *  result)                                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  f5x5()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
f5x5(
  float *  signal,
  SInt32   rowStride,
  SInt32   colStride,
  float *  filter,
  float *  result)                                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  f5x5D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
f5x5D(
  double *  signal,
  SInt32    rowStride,
  SInt32    colStride,
  double *  filter,
  double *  result)                                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  imgfir()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
imgfir(
  float *  signal,
  SInt32   numRow,
  SInt32   numCol,
  float *  filter,
  float *  result,
  SInt32   fnumRow,
  SInt32   fnumCol)                                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  imgfirD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
imgfirD(
  double *  signal,
  SInt32    numRow,
  SInt32    numCol,
  double *  filter,
  double *  result,
  SInt32    fnumRow,
  SInt32    fnumCol)                                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
_______________________________________________________________________________
     Function mtrans
              mtransD
              
     Single and Double Precision Matrix Transpose
     
       Criteria to invoke PowerPC vector code:
         1. a = c
         2. a and c must be 16-byte aligned.
         3. M must be a multiple of 8.
       
       If any of the above criteria are not satisfied, the PowerPC scalar code
       implementation will be used.
_______________________________________________________________________________
*/
/*
 *  mtrans()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
mtrans(
  float *  a,
  SInt32   aStride,
  float *  c,
  SInt32   cStride,
  SInt32   M,
  SInt32   N)                                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  mtransD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
mtransD(
  double *  a,
  SInt32    aStride,
  double *  c,
  SInt32    cStride,
  SInt32    M,
  SInt32    N)                                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
_______________________________________________________________________________
      Function mmul
               mmulD
               
      Single and Double Precision Matrix Multiply
      
        Criteria to invoke PowerPC vector code:
          1. a, b, c must be 16-byte aligned.
          2. M >= 8.
          3. N >= 32.
          4. P is a multiple of 8.
        
        If any of the above criteria are not satisfied, the PowerPC scalar code
        implementation will be used.
_______________________________________________________________________________
*/
/*
 *  mmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
mmul(
  float *  a,
  SInt32   aStride,
  float *  b,
  SInt32   bStride,
  float *  c,
  SInt32   cStride,
  SInt32   M,
  SInt32   N,
  SInt32   P)                                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  mmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
mmulD(
  double *  a,
  SInt32    aStride,
  double *  b,
  SInt32    bStride,
  double *  c,
  SInt32    cStride,
  SInt32    M,
  SInt32    N,
  SInt32    P)                                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
_______________________________________________________________________________
      Function zmma, zmms, zmsm, and zmmul
               zmmaD, zmmsD, zmsmD, and zmmulD
               
      Single and Double Precision Complex Split Matrix mul/add, mul/sub, sub/mul, 
                                                       and mul
      
        Criteria to invoke PowerPC vector code:
          1. a, b, c, and d must be 16-byte aligned.
          2. N is a multiple of 4.
          3. P is a multiple of 4.
          4. I, J, K, L = 1;
          
       If any of the above criteria are not satisfied, the PowerPC scalar code
       implementation will be used.
_______________________________________________________________________________
*/
/*
 *  zmma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zmma(
  DSPSplitComplex *  a,
  SInt32             i,
  DSPSplitComplex *  b,
  SInt32             j,
  DSPSplitComplex *  c,
  SInt32             k,
  DSPSplitComplex *  d,
  SInt32             l,
  SInt32             M,
  SInt32             N,
  SInt32             P)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  zmmaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zmmaD(
  DSPDoubleSplitComplex *  a,
  SInt32                   i,
  DSPDoubleSplitComplex *  b,
  SInt32                   j,
  DSPDoubleSplitComplex *  c,
  SInt32                   k,
  DSPDoubleSplitComplex *  d,
  SInt32                   l,
  SInt32                   M,
  SInt32                   N,
  SInt32                   P)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  zmms()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zmms(
  DSPSplitComplex *  a,
  SInt32             i,
  DSPSplitComplex *  b,
  SInt32             j,
  DSPSplitComplex *  c,
  SInt32             k,
  DSPSplitComplex *  d,
  SInt32             l,
  SInt32             M,
  SInt32             N,
  SInt32             P)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  zmmsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zmmsD(
  DSPDoubleSplitComplex *  a,
  SInt32                   i,
  DSPDoubleSplitComplex *  b,
  SInt32                   j,
  DSPDoubleSplitComplex *  c,
  SInt32                   k,
  DSPDoubleSplitComplex *  d,
  SInt32                   l,
  SInt32                   M,
  SInt32                   N,
  SInt32                   P)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  zmsm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zmsm(
  DSPSplitComplex *  a,
  SInt32             i,
  DSPSplitComplex *  b,
  SInt32             j,
  DSPSplitComplex *  c,
  SInt32             k,
  DSPSplitComplex *  d,
  SInt32             l,
  SInt32             M,
  SInt32             N,
  SInt32             P)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  zmsmD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zmsmD(
  DSPDoubleSplitComplex *  a,
  SInt32                   i,
  DSPDoubleSplitComplex *  b,
  SInt32                   j,
  DSPDoubleSplitComplex *  c,
  SInt32                   k,
  DSPDoubleSplitComplex *  d,
  SInt32                   l,
  SInt32                   M,
  SInt32                   N,
  SInt32                   P)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  zmmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zmmul(
  DSPSplitComplex *  a,
  SInt32             i,
  DSPSplitComplex *  b,
  SInt32             j,
  DSPSplitComplex *  c,
  SInt32             k,
  SInt32             M,
  SInt32             N,
  SInt32             P)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  zmmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zmmulD(
  DSPDoubleSplitComplex *  a,
  SInt32                   i,
  DSPDoubleSplitComplex *  b,
  SInt32                   j,
  DSPDoubleSplitComplex *  c,
  SInt32                   k,
  SInt32                   M,
  SInt32                   N,
  SInt32                   P)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function vadd
             vaddD
    
    Floating Point Add in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1 and input2 and result are all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vadd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vadd(
  const float   input1[],
  SInt32        stride1,
  const float   input2[],
  SInt32        stride2,
  float         result[],
  SInt32        strideResult,
  UInt32        size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vaddD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vaddD(
  const double   input1[],
  SInt32         stride1,
  const double   input2[],
  SInt32         stride2,
  double         result[],
  SInt32         strideResult,
  UInt32         size)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function vsub
             vsubD
             
     Floating Point Substract in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. input1 and input2 and result are all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vsub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vsub(
  const float   input1[],
  SInt32        stride1,
  const float   input2[],
  SInt32        stride2,
  float         result[],
  SInt32        strideResult,
  UInt32        size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vsubD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vsubD(
  const double   input1[],
  SInt32         stride1,
  const double   input2[],
  SInt32         stride2,
  double         result[],
  SInt32         strideResult,
  UInt32         size)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function vmul
             vmulD
             
    Floating Point Multiply in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1 and input2 and result must be all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vmul(
  const float   input1[],
  SInt32        stride1,
  const float   input2[],
  SInt32        stride2,
  float         result[],
  SInt32        strideResult,
  UInt32        size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vmulD(
  const double   input1[],
  SInt32         stride1,
  const double   input2[],
  SInt32         stride2,
  double         result[],
  SInt32         strideResult,
  UInt32         size)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function vsmul
             vsmulD
    
    Floating Point - Scalar Multiply in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1 and result are all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vsmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vsmul(
  const float    input1[],
  SInt32         stride1,
  const float *  input2,
  float          result[],
  SInt32         strideResult,
  UInt32         size)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vsmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vsmulD(
  const double    input1[],
  SInt32          stride1,
  const double *  input2,
  double          result[],
  SInt32          strideResult,
  UInt32          size)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function vsq
             vsqD
    
    Floating Point Square in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. input and result are relatively aligned.
        2. size >= 8
        3. strideInput = 1
        4. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vsq()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vsq(
  const float   input[],
  SInt32        strideInput,
  float         result[],
  SInt32        strideResult,
  UInt32        size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vsqD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vsqD(
  const double   input[],
  SInt32         strideInput,
  double         result[],
  SInt32         strideResult,
  UInt32         size)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function vssq
             vssqD
             
    Floating Point Signed Square in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. input and result must be all relatively aligned.
        2. size >= 8
        3. strideInput = 1
        4. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vssq()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vssq(
  const float   input[],
  SInt32        strideInput,
  float         result[],
  SInt32        strideResult,
  UInt32        size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vssqD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vssqD(
  const double   input[],
  SInt32         strideInput,
  double         result[],
  SInt32         strideResult,
  UInt32         size)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function dotpr
             dotprD
    
    Floating Point Dot product in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1 and input2 are relatively aligned.
        2. size >= 20
        3. stride1 = 1
        4. stride2 = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  dotpr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
dotpr(
  const float   input1[],
  SInt32        stride1,
  const float   input2[],
  SInt32        stride2,
  float *       result,
  UInt32        size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  dotprD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
dotprD(
  const double   input1[],
  SInt32         stride1,
  const double   input2[],
  SInt32         stride2,
  double *       result,
  UInt32         size)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function vam
             vamD
             
    Floating Point vadd and Multiply in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1, input2, input_3 and result are all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. stride_3 = 1
        6. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  vam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vam(
  const float   input1[],
  SInt32        stride1,
  const float   input2[],
  SInt32        stride2,
  const float   input3[],
  SInt32        stride3,
  float         result[],
  SInt32        strideResult,
  UInt32        size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vamD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vamD(
  const double   input1[],
  SInt32         stride1,
  const double   input2[],
  SInt32         stride2,
  const double   input3[],
  SInt32         stride3,
  double         result[],
  SInt32         strideResult,
  UInt32         size)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zconv
             zconvD
                
    Split Complex Convolution and Correlation in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. signal->realp, signal->imagp, result->realp, result->imagp
           must be relatively aligned.
        2. 4 <= lenFilter <= 128
        3. lenResult > 20
        4. signalStride = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  strideFilter can be positive for correlation
      or negative for convolution
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zconv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zconv(
  DSPSplitComplex *  signal,
  SInt32             signalStride,
  DSPSplitComplex *  filter,
  SInt32             strideFilter,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  SInt32             lenResult,
  SInt32             lenFilter)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zconvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zconvD(
  DSPDoubleSplitComplex *  signal,
  SInt32                   signalStride,
  DSPDoubleSplitComplex *  filter,
  SInt32                   strideFilter,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  SInt32                   lenResult,
  SInt32                   lenFilter)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zvadd
             zvaddD
    
    Split Complex vadd in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2.realp, input2.imagp,
           result.realp, result.imagp must be all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zvadd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zvadd(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  DSPSplitComplex *  input2,
  SInt32             stride2,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zvaddD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zvaddD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  DSPDoubleSplitComplex *  input2,
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zvsub
             zvsubD
             
    Split Complex Substract in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2.realp, input2.imagp,
           result.realp, result.imagp must be all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zvsub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zvsub(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  DSPSplitComplex *  input2,
  SInt32             stride2,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zvsubD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zvsubD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  DSPDoubleSplitComplex *  input2,
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zvmul
             zvmulD
             
    Split Complex Multiply in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2.realp, input2.imagp,
           result.realp, result.imagp must be all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1

      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.  The conjugate value can be 1 or -1.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zvmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zvmul(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  DSPSplitComplex *  input2,
  SInt32             stride2,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             size,
  SInt32             conjugate)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zvmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zvmulD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  DSPDoubleSplitComplex *  input2,
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   size,
  SInt32                   conjugate)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zdotpr
             zdotprD
             
    Split Complex Dot product in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2.realp, input2.imagp are all
           relatively aligned.
        2. size >= 20
        3. stride1 = 1
        4. stride2 = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zdotpr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zdotpr(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  DSPSplitComplex *  input2,
  SInt32             stride2,
  DSPSplitComplex *  result,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zdotprD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zdotprD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  DSPDoubleSplitComplex *  input2,
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zidotpr
             zidotprD
             
    Split Complex Inner Dot product in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2.realp, input2.imagp must be
           all relatively aligned.
        2. size >= 20
        3. stride1 = 1
        4. stride2 = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zidotpr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zidotpr(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  DSPSplitComplex *  input2,
  SInt32             stride2,
  DSPSplitComplex *  result,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zidotprD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zidotprD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  DSPDoubleSplitComplex *  input2,
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zrdotpr
             zrdotprD
                
    Split Complex - Real Dot product in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2 are must be relatively aligned.
        2. size >= 16
        3. stride1 = 1
        4. stride2 = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zrdotpr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zrdotpr(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  const float        input2[],
  SInt32             stride2,
  DSPSplitComplex *  result,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zrdotprD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zrdotprD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  const double             input2[],
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zvcma
             zvcmaD
             
    Split Complex Conjugate Multiply And vadd in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2.realp, input2.imagp,
          input_3.realp, input_3.imagp, result.realp, result.imagp
          must be all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. stride_3 = 1
        6. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zvcma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zvcma(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  DSPSplitComplex *  input2,
  SInt32             stride2,
  DSPSplitComplex *  input3,
  SInt32             stride3,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zvcmaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zvcmaD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  DSPDoubleSplitComplex *  input2,
  SInt32                   stride2,
  DSPDoubleSplitComplex *  input3,
  SInt32                   stride3,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zrvadd
             zrvaddD
             
    Split Complex - Real Add in Single and Double Precision
      
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2, result.realp, result.imagp
           are all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zrvadd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zrvadd(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  const float        input2[],
  SInt32             stride2,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zrvaddD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zrvaddD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  const double             input2[],
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zrvsub
             zrvsubD
                
    Split Complex - Real Substract in Single and Double Precision
    
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2, result.realp, result.imagp
           must be all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zrvsub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zrvsub(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  const float        input2[],
  SInt32             stride2,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zrvsubD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zrvsubD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  const double             input2[],
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Function zrvmul
             zrvmulD
             
    Split Complex - Real Multiply
    
      Criteria to invoke PowerPC vector code:  
        1. input1.realp, input1.imagp, input2, result.realp, result.imagp
           must be all relatively aligned.
        2. size >= 8
        3. stride1 = 1
        4. stride2 = 1
        5. strideResult = 1
      
      If any of the above criteria are not satisfied, the PowerPC scalar code
      implementation will be used.
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/*
 *  zrvmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
zrvmul(
  DSPSplitComplex *  input1,
  SInt32             stride1,
  const float        input2[],
  SInt32             stride2,
  DSPSplitComplex *  result,
  SInt32             strideResult,
  UInt32             size)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  zrvmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
zrvmulD(
  DSPDoubleSplitComplex *  input1,
  SInt32                   stride1,
  const double             input2[],
  SInt32                   stride2,
  DSPDoubleSplitComplex *  result,
  SInt32                   strideResult,
  UInt32                   size)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#ifndef USE_NON_APPLE_STANDARD_DATATYPES
#define USE_NON_APPLE_STANDARD_DATATYPES 1
#endif  /* !defined(USE_NON_APPLE_STANDARD_DATATYPES) */

#if USE_NON_APPLE_STANDARD_DATATYPES
enum {
  FFT_FORWARD                   = kFFTDirection_Forward,
  FFT_INVERSE                   = kFFTDirection_Inverse
};

enum {
  FFT_RADIX2                    = kFFTRadix2,
  FFT_RADIX3                    = kFFTRadix3,
  FFT_RADIX5                    = kFFTRadix5
};


typedef DSPComplex                      COMPLEX;
typedef DSPSplitComplex                 COMPLEX_SPLIT;
typedef DSPDoubleComplex                DOUBLE_COMPLEX;
typedef DSPDoubleSplitComplex           DOUBLE_COMPLEX_SPLIT;
#endif  /* USE_NON_APPLE_STANDARD_DATATYPES */


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __VDSP__ */

