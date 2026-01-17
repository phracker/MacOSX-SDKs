/*
     File:       vecLib/vDSP.h
 
     Contains:   AltiVec DSP Interfaces
 
     Version:    vecLib-192.17
 
     Copyright:  © 2000-2007 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VDSP__
#define __VDSP__

/*  For documentation on vDSP, see _vDSP Library_ at
    http://developer.apple.com/documentation/Performance/index-date.html or
    search for "vDSP Library" at http://developer.apple.com.
*/

#if defined __ppc__ || defined __i386__
#ifndef __VDSP_TRANSLATE__
#include <vecLib/vDSP_translate.h>
#endif

#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=power


/*	These symbols describe the vecLib version associated with this header.

	vDSP_Version0 is a major version number.
	vDSP_Version1 is a minor version number.
*/
#define	vDSP_Version0	192
#define	vDSP_Version1	17


typedef unsigned long                   vDSP_Length;
/*    vDSP_Length is for numbers of elements in arrays and indices of
    elements in arrays.

    (It is also used for the base-two logarithm of numbers of elements,
    although a much smaller type is suitable for that.)
    */
typedef long                            vDSP_Stride;
/*    vDSP_Stride is for differences of indices of elements (which of
    course includes strides).
    */

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

typedef int                             FFTDirection;
typedef int                             FFTRadix;
enum {
  kFFTDirection_Forward         = 1,
  kFFTDirection_Inverse         = -1
};

enum {
  kFFTRadix2                    = 0,
  kFFTRadix3                    = 1,
  kFFTRadix5                    = 2
};

enum {
  vDSP_HALF_WINDOW              = 1,
  vDSP_HANN_DENORM              = 0,
  vDSP_HANN_NORM                = 2
};



/*  create_fftsetup and create_ffsetupD allocate memory and prepare constants
    used by single- and double-precision FFT routines, respectively.

    destroy_fftsetup and destroy_fftsetupD free the memory.
*/
/*
 *  vDSP_create_fftsetup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern FFTSetup 
vDSP_create_fftsetup(
  vDSP_Length   __vDSP_log2n,
  FFTRadix      __vDSP_radix)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_destroy_fftsetup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_destroy_fftsetup(FFTSetup __vDSP_setup)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_create_fftsetupD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern FFTSetupD 
vDSP_create_fftsetupD(
  vDSP_Length   __vDSP_log2n,
  FFTRadix      __vDSP_radix)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_destroy_fftsetupD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_destroy_fftsetupD(FFTSetupD __vDSP_setup)                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  ctoz and ctozD convert a complex array to a complex-split array.
    ztoc and ztocD convert a complex-split array to a complex array.
*/
/*
 *  vDSP_ctoz()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_ctoz(
  const DSPComplex   __vDSP_C[],
  vDSP_Stride        __vDSP_strideC,
  DSPSplitComplex *  __vDSP_Z,
  vDSP_Stride        __vDSP_strideZ,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_ztoc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_ztoc(
  const DSPSplitComplex *  __vDSP_Z,
  vDSP_Stride              __vDSP_strideZ,
  DSPComplex               __vDSP_C[],
  vDSP_Stride              __vDSP_strideC,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_ctozD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_ctozD(
  const DSPDoubleComplex   __vDSP_C[],
  vDSP_Stride              __vDSP_strideC,
  DSPDoubleSplitComplex *  __vDSP_Z,
  vDSP_Stride              __vDSP_strideZ,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_ztocD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_ztocD(
  const DSPDoubleSplitComplex *  __vDSP_Z,
  vDSP_Stride                    __vDSP_strideZ,
  DSPDoubleComplex               __vDSP_C[],
  vDSP_Stride                    __vDSP_strideC,
  vDSP_Length                    __vDSP_size)                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  In-place complex Discrete Fourier Transform routines.

    fft_zip Single-precision without temporary memory.
    fft_zipt    Single-precision with temporary memory.
    fft_zipD    Double-precision without temporary memory.
    fft_ziptD   Double-precision with temporary memory.
*/
/*
 *  vDSP_fft_zip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft_zip(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_ioData,
  vDSP_Stride        __vDSP_stride,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft_zipt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft_zipt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_ioData,
  vDSP_Stride        __vDSP_stride,
  DSPSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft_zipD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft_zipD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_stride,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_direction)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft_ziptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft_ziptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_stride,
  DSPDoubleSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_direction)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  Out-of-place complex Discrete Fourier Transform routines.

    fft_zop Single-precision without temporary memory.
    fft_zopt    Single-precision with temporary memory.
    fft_zopD    Double-precision without temporary memory.
    fft_zoptD   Double-precision with temporary memory.
*/
/*
 *  vDSP_fft_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft_zop(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft_zopt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft_zopt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  DSPSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft_zopD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_direction)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft_zoptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft_zoptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  DSPDoubleSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_direction)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  In-place real-to-complex Discrete Fourier Transform routines.

    fft_zrip    Single-precision without temporary memory.
    fft_zript   Single-precision with temporary memory.
    fft_zripD   Double-precision without temporary memory.
    fft_zriptD  Double-precision with temporary memory.
*/
/*
 *  vDSP_fft_zrip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft_zrip(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_ioData,
  vDSP_Stride        __vDSP_stride,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft_zript()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft_zript(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_ioData,
  vDSP_Stride        __vDSP_stride,
  DSPSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft_zripD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft_zripD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_stride,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft_zriptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft_zriptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_stride,
  DSPDoubleSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  Out-of-place real-to-complex Discrete Fourier Transform routines.

    fft_zrop    Single-precision without temporary memory.
    fft_zropt   Single-precision with temporary memory.
    fft_zropD   Double-precision without temporary memory.
    fft_zroptD  Double-precision with temporary memory.
*/
/*
 *  vDSP_fft_zrop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft_zrop(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft_zropt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft_zropt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  DSPSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft_zropD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft_zropD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft_zroptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft_zroptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  DSPDoubleSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  In-place two-dimensional complex Discrete Fourier Transform routines.

    fft2d_zip   Single-precision without temporary memory.
    fft2d_zipt  Single-precision with temporary memory.
    fft2d_zipD  Double-precision without temporary memory.
    fft2d_ziptD Double-precision with temporary memory.
*/
/*
 *  vDSP_fft2d_zip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft2d_zip(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_ioData,
  vDSP_Stride        __vDSP_strideInRow,
  vDSP_Stride        __vDSP_strideInCol,
  vDSP_Length        __vDSP_log2nInCol,
  vDSP_Length        __vDSP_log2nInRow,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft2d_zipt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft2d_zipt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_ioData,
  vDSP_Stride        __vDSP_strideInRow,
  vDSP_Stride        __vDSP_strideInCol,
  DSPSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length        __vDSP_log2nInCol,
  vDSP_Length        __vDSP_log2nInRow,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft2d_zipD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft2d_zipD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_strideInRow,
  vDSP_Stride              __vDSP_strideInCol,
  vDSP_Length              __vDSP_log2nInCol,
  vDSP_Length              __vDSP_log2nInRow,
  FFTDirection             __vDSP_direction)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft2d_ziptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft2d_ziptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_strideInRow,
  vDSP_Stride              __vDSP_strideInCol,
  DSPDoubleSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length              __vDSP_log2nInCol,
  vDSP_Length              __vDSP_log2nInRow,
  FFTDirection             __vDSP_direction)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  Out-of-place two-dimensional complex Discrete Fourier Transform routines.

    fft2d_zop   Single-precision without temporary memory.
    fft2d_zopt  Single-precision with temporary memory.
    fft2d_zopD  Double-precision without temporary memory.
    fft2d_zoptD Double-precision with temporary memory.
*/
/*
 *  vDSP_fft2d_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft2d_zop(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStrideInRow,
  vDSP_Stride        __vDSP_signalStrideInCol,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResultInRow,
  vDSP_Stride        __vDSP_strideResultInCol,
  vDSP_Length        __vDSP_log2nInCol,
  vDSP_Length        __vDSP_log2nInRow,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft2d_zopt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft2d_zopt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStrideInRow,
  vDSP_Stride        __vDSP_signalStrideInCol,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResultInRow,
  vDSP_Stride        __vDSP_strideResultInCol,
  DSPSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length        __vDSP_log2nInCol,
  vDSP_Length        __vDSP_log2nInRow,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft2d_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft2d_zopD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStrideInRow,
  vDSP_Stride              __vDSP_signalStrideInCol,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResultInRow,
  vDSP_Stride              __vDSP_strideResultInCol,
  vDSP_Length              __vDSP_log2nInCol,
  vDSP_Length              __vDSP_log2nInRow,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft2d_zoptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft2d_zoptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStrideInRow,
  vDSP_Stride              __vDSP_signalStrideInCol,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResultInRow,
  vDSP_Stride              __vDSP_strideResultInCol,
  DSPDoubleSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length              __vDSP_log2nInCol,
  vDSP_Length              __vDSP_log2nInRow,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  In-place two-dimensional real-to-complex Discrete Fourier Transform
    routines.

    fft2d_zrip      Single-precision without temporary memory.
    fft2d_zript     Single-precision with temporary memory.
    fft2d_zripD     Double-precision without temporary memory.
    fft2d_zriptD    Double-precision with temporary memory.
*/
/*
 *  vDSP_fft2d_zrip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft2d_zrip(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_ioData,
  vDSP_Stride        __vDSP_strideInRow,
  vDSP_Stride        __vDSP_strideInCol,
  vDSP_Length        __vDSP_log2nInCol,
  vDSP_Length        __vDSP_log2nInRow,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft2d_zript()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft2d_zript(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_ioData,
  vDSP_Stride        __vDSP_strideInRow,
  vDSP_Stride        __vDSP_strideInCol,
  DSPSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length        __vDSP_log2nInCol,
  vDSP_Length        __vDSP_log2nInRow,
  FFTDirection       __vDSP_direction)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft2d_zripD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft2d_zripD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_strideInRow,
  vDSP_Stride              __vDSP_strideInCol,
  vDSP_Length              __vDSP_log2nInCol,
  vDSP_Length              __vDSP_log2nInRow,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft2d_zriptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft2d_zriptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_strideInRow,
  vDSP_Stride              __vDSP_strideInCol,
  DSPDoubleSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length              __vDSP_log2nInCol,
  vDSP_Length              __vDSP_log2nInRow,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  Out-of-place two-dimensional real-to-complex Discrete Fourier Transform
    routines.

    fft2d_zrop      Single-precision without temporary memory.
    fft2d_zropt     Single-precision with temporary memory.
    fft2d_zropD     Double-precision without temporary memory.
    fft2d_zroptD    Double-precision with temporary memory.
*/
/*
 *  vDSP_fft2d_zrop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft2d_zrop(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStrideInRow,
  vDSP_Stride        __vDSP_signalStrideInCol,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResultInRow,
  vDSP_Stride        __vDSP_strideResultInCol,
  vDSP_Length        __vDSP_log2nInCol,
  vDSP_Length        __vDSP_log2nInRow,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft2d_zropt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_fft2d_zropt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStrideInRow,
  vDSP_Stride        __vDSP_signalStrideInCol,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResultInRow,
  vDSP_Stride        __vDSP_strideResultInCol,
  DSPSplitComplex *  __vDSP_bufferTemp,
  vDSP_Length        __vDSP_log2nInCol,
  vDSP_Length        __vDSP_log2nInRow,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vDSP_fft2d_zropD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft2d_zropD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_Kr,
  vDSP_Stride              __vDSP_Kc,
  DSPDoubleSplitComplex *  __vDSP_ioData2,
  vDSP_Stride              __vDSP_Ir,
  vDSP_Stride              __vDSP_Ic,
  vDSP_Length              __vDSP_log2nc,
  vDSP_Length              __vDSP_log2nr,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft2d_zroptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft2d_zroptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_Kr,
  vDSP_Stride              __vDSP_Kc,
  DSPDoubleSplitComplex *  __vDSP_ioData2,
  vDSP_Stride              __vDSP_Ir,
  vDSP_Stride              __vDSP_Ic,
  DSPDoubleSplitComplex *  __vDSP_temp,
  vDSP_Length              __vDSP_log2nc,
  vDSP_Length              __vDSP_log2nr,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  In-place multiple complex Discrete Fourier Transform routines.

    fftm_zip    Single-precision without temporary memory.
    fftm_zipt   Single-precision with temporary memory.
    fftm_zipD   Double-precision without temporary memory.
    fftm_ziptD  Double-precision with temporary memory.
*/
/*
 *  vDSP_fftm_zip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zip(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  vDSP_Stride        __vDSP_fftStride,
  vDSP_Length        __vDSP_log2n,
  vDSP_Length        __vDSP_numFFT,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zipt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zipt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  vDSP_Stride        __vDSP_fftStride,
  DSPSplitComplex *  __vDSP_temp,
  vDSP_Length        __vDSP_log2n,
  vDSP_Length        __vDSP_numFFT,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zipD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zipD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  vDSP_Stride              __vDSP_fftStride,
  vDSP_Length              __vDSP_log2n,
  vDSP_Length              __vDSP_numFFT,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_ziptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_ziptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  vDSP_Stride              __vDSP_fftStride,
  DSPDoubleSplitComplex *  __vDSP_temp,
  vDSP_Length              __vDSP_log2n,
  vDSP_Length              __vDSP_numFFT,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  Out-of-place multiple complex Discrete Fourier Transform routines.

    fftm_zop    Single-precision without temporary memory.
    fftm_zopt   Single-precision with temporary memory.
    fftm_zopD   Double-precision without temporary memory.
    fftm_zoptD  Double-precision with temporary memory.
*/
/*
 *  vDSP_fftm_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zop(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  vDSP_Stride        __vDSP_fftStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_resultStride,
  vDSP_Stride        __vDSP_rfftStride,
  vDSP_Length        __vDSP_log2n,
  vDSP_Length        __vDSP_numFFT,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zopt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zopt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  vDSP_Stride        __vDSP_fftStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_resultStride,
  vDSP_Stride        __vDSP_rfftStride,
  DSPSplitComplex *  __vDSP_temp,
  vDSP_Length        __vDSP_log2n,
  vDSP_Length        __vDSP_numFFT,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zopD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  vDSP_Stride              __vDSP_fftStride,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_resultStride,
  vDSP_Stride              __vDSP_rfftStride,
  vDSP_Length              __vDSP_log2n,
  vDSP_Length              __vDSP_numFFT,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zoptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zoptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  vDSP_Stride              __vDSP_fftStride,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_resultStride,
  vDSP_Stride              __vDSP_rfftStride,
  DSPDoubleSplitComplex *  __vDSP_temp,
  vDSP_Length              __vDSP_log2n,
  vDSP_Length              __vDSP_numFFT,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*  In-place multiple real-to-complex Discrete Fourier Transform routines.

    fftm_zip    Single-precision without temporary memory.
    fftm_zipt   Single-precision with temporary memory.
    fftm_zipD   Double-precision without temporary memory.
    fftm_ziptD  Double-precision with temporary memory.
*/
/*
 *  vDSP_fftm_zrip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zrip(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  vDSP_Stride        __vDSP_fftStride,
  vDSP_Length        __vDSP_log2n,
  vDSP_Length        __vDSP_numFFT,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zript()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zript(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  vDSP_Stride        __vDSP_fftStride,
  DSPSplitComplex *  __vDSP_temp,
  vDSP_Length        __vDSP_log2n,
  vDSP_Length        __vDSP_numFFT,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zripD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zripD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  vDSP_Stride              __vDSP_fftStride,
  vDSP_Length              __vDSP_log2n,
  vDSP_Length              __vDSP_numFFT,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zriptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zriptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  vDSP_Stride              __vDSP_fftStride,
  DSPDoubleSplitComplex *  __vDSP_temp,
  vDSP_Length              __vDSP_log2n,
  vDSP_Length              __vDSP_numFFT,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*  Out-of-place multiple real-to-complex Discrete Fourier Transform routines.

    fftm_zrop   Single-precision without temporary memory.
    fftm_zropt  Single-precision with temporary memory.
    fftm_zropD  Double-precision without temporary memory.
    fftm_zroptD Double-precision with temporary memory.
*/
/*
 *  vDSP_fftm_zrop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zrop(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  vDSP_Stride        __vDSP_fftStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_resultStride,
  vDSP_Stride        __vDSP_rfftStride,
  vDSP_Length        __vDSP_log2n,
  vDSP_Length        __vDSP_numFFT,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zropt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zropt(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  vDSP_Stride        __vDSP_fftStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_resultStride,
  vDSP_Stride        __vDSP_rfftStride,
  DSPSplitComplex *  __vDSP_temp,
  vDSP_Length        __vDSP_log2n,
  vDSP_Length        __vDSP_numFFT,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zropD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zropD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  vDSP_Stride              __vDSP_fftStride,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_resultStride,
  vDSP_Stride              __vDSP_rfftStride,
  vDSP_Length              __vDSP_log2n,
  vDSP_Length              __vDSP_numFFT,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fftm_zroptD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fftm_zroptD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  vDSP_Stride              __vDSP_fftStride,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_resultStride,
  vDSP_Stride              __vDSP_rfftStride,
  DSPDoubleSplitComplex *  __vDSP_temp,
  vDSP_Length              __vDSP_log2n,
  vDSP_Length              __vDSP_numFFT,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*  Non-power-of-two out-of-place complex Discrete Fourier Transform routines.

    fft3_zop    3*2**n elements, single-precision without temporary memory.
    fft3_zopD   3*2**n elements, double-precision without temporary memory.
    fft5_zop    5*2**n elements, single-precision without temporary memory.
    fft5_zopD   5*2**n elements, double-precision without temporary memory.
*/
/*
 *  vDSP_fft3_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft3_zop(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_resultStride,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft5_zop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft5_zop(
  FFTSetup           __vDSP_setup,
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_resultStride,
  vDSP_Length        __vDSP_log2n,
  FFTDirection       __vDSP_flag)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft3_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft3_zopD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_K,
  DSPDoubleSplitComplex *  __vDSP_ioData2,
  vDSP_Stride              __vDSP_L,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  vDSP_fft5_zopD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_fft5_zopD(
  FFTSetupD                __vDSP_setup,
  DSPDoubleSplitComplex *  __vDSP_ioData,
  vDSP_Stride              __vDSP_K,
  DSPDoubleSplitComplex *  __vDSP_ioData2,
  vDSP_Stride              __vDSP_L,
  vDSP_Length              __vDSP_log2n,
  FFTDirection             __vDSP_flag)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Convolution (or correlation), single-precision.*/
/*
 *  vDSP_conv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_conv(
  const float   __vDSP_signal[],
  vDSP_Stride   __vDSP_signalStride,
  const float   __vDSP_filter[],
  vDSP_Stride   __vDSP_strideFilter,
  float         __vDSP_result[],
  vDSP_Stride   __vDSP_strideResult,
  vDSP_Length   __vDSP_lenResult,
  vDSP_Length   __vDSP_lenFilter)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Convolution (or correlation), double-precision.*/
/*
 *  vDSP_convD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_convD(
  const double   __vDSP_signal[],
  vDSP_Stride    __vDSP_signalStride,
  const double   __vDSP_filter[],
  vDSP_Stride    __vDSP_strideFilter,
  double         __vDSP_result[],
  vDSP_Stride    __vDSP_strideResult,
  vDSP_Length    __vDSP_lenResult,
  vDSP_Length    __vDSP_lenFilter)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* 3*3 filter convolution, single-precision.*/
/*
 *  vDSP_f3x3()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_f3x3(
  float *       __vDSP_signal,
  vDSP_Length   __vDSP_rows,
  vDSP_Length   __vDSP_cols,
  float *       __vDSP_filter,
  float *       __vDSP_result)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* 3*3 filter convolution, double-precision.*/
/*
 *  vDSP_f3x3D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_f3x3D(
  double *      __vDSP_signal,
  vDSP_Length   __vDSP_rows,
  vDSP_Length   __vDSP_cols,
  double *      __vDSP_filter,
  double *      __vDSP_result)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* 5*5 filter convolution, single-precision.*/
/*
 *  vDSP_f5x5()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_f5x5(
  float *       __vDSP_signal,
  vDSP_Length   __vDSP_rows,
  vDSP_Length   __vDSP_cols,
  float *       __vDSP_filter,
  float *       __vDSP_result)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* 5*5 filter convolution, double-precision.*/
/*
 *  vDSP_f5x5D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_f5x5D(
  double *      __vDSP_signal,
  vDSP_Length   __vDSP_rows,
  vDSP_Length   __vDSP_cols,
  double *      __vDSP_filter,
  double *      __vDSP_result)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* General two-dimensional (image) convolution, single-precision.*/
/*
 *  vDSP_imgfir()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_imgfir(
  float *       __vDSP_signal,
  vDSP_Length   __vDSP_numRow,
  vDSP_Length   __vDSP_numCol,
  float *       __vDSP_filter,
  float *       __vDSP_result,
  vDSP_Length   __vDSP_fnumRow,
  vDSP_Length   __vDSP_fnumCol)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* General two-dimensional (image) convolution, double-precision.*/
/*
 *  vDSP_imgfirD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_imgfirD(
  double *      __vDSP_signal,
  vDSP_Length   __vDSP_numRow,
  vDSP_Length   __vDSP_numCol,
  double *      __vDSP_filter,
  double *      __vDSP_result,
  vDSP_Length   __vDSP_fnumRow,
  vDSP_Length   __vDSP_fnumCol)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Matrix transpose, single-precision.*/
/*
 *  vDSP_mtrans()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_mtrans(
  float *       __vDSP_a,
  vDSP_Stride   __vDSP_aStride,
  float *       __vDSP_c,
  vDSP_Stride   __vDSP_cStride,
  vDSP_Length   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Matrix transpose, double-precision.*/
/*
 *  vDSP_mtransD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_mtransD(
  double *      __vDSP_a,
  vDSP_Stride   __vDSP_aStride,
  double *      __vDSP_c,
  vDSP_Stride   __vDSP_cStride,
  vDSP_Length   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Matrix multiply, single-precision.*/
/*
 *  vDSP_mmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_mmul(
  float *       __vDSP_a,
  vDSP_Stride   __vDSP_aStride,
  float *       __vDSP_b,
  vDSP_Stride   __vDSP_bStride,
  float *       __vDSP_c,
  vDSP_Stride   __vDSP_cStride,
  vDSP_Length   __vDSP_M,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_P)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Matrix multiply, double-precision.*/
/*
 *  vDSP_mmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_mmulD(
  double *      __vDSP_a,
  vDSP_Stride   __vDSP_aStride,
  double *      __vDSP_b,
  vDSP_Stride   __vDSP_bStride,
  double *      __vDSP_c,
  vDSP_Stride   __vDSP_cStride,
  vDSP_Length   __vDSP_M,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_P)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split matrix multiply and add, single-precision.*/
/*
 *  vDSP_zmma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zmma(
  DSPSplitComplex *  __vDSP_a,
  vDSP_Stride        __vDSP_i,
  DSPSplitComplex *  __vDSP_b,
  vDSP_Stride        __vDSP_j,
  DSPSplitComplex *  __vDSP_c,
  vDSP_Stride        __vDSP_k,
  DSPSplitComplex *  __vDSP_d,
  vDSP_Stride        __vDSP_l,
  vDSP_Length        __vDSP_M,
  vDSP_Length        __vDSP_N,
  vDSP_Length        __vDSP_P)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split matrix multiply and add, double-precision.*/
/*
 *  vDSP_zmmaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zmmaD(
  DSPDoubleSplitComplex *  __vDSP_a,
  vDSP_Stride              __vDSP_i,
  DSPDoubleSplitComplex *  __vDSP_b,
  vDSP_Stride              __vDSP_j,
  DSPDoubleSplitComplex *  __vDSP_c,
  vDSP_Stride              __vDSP_k,
  DSPDoubleSplitComplex *  __vDSP_d,
  vDSP_Stride              __vDSP_l,
  vDSP_Length              __vDSP_M,
  vDSP_Length              __vDSP_N,
  vDSP_Length              __vDSP_P)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split matrix multiply and subtract, single-precision.*/
/*
 *  vDSP_zmms()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zmms(
  DSPSplitComplex *  __vDSP_a,
  vDSP_Stride        __vDSP_i,
  DSPSplitComplex *  __vDSP_b,
  vDSP_Stride        __vDSP_j,
  DSPSplitComplex *  __vDSP_c,
  vDSP_Stride        __vDSP_k,
  DSPSplitComplex *  __vDSP_d,
  vDSP_Stride        __vDSP_l,
  vDSP_Length        __vDSP_M,
  vDSP_Length        __vDSP_N,
  vDSP_Length        __vDSP_P)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split matrix multiply and subtract, double-precision.*/
/*
 *  vDSP_zmmsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zmmsD(
  DSPDoubleSplitComplex *  __vDSP_a,
  vDSP_Stride              __vDSP_i,
  DSPDoubleSplitComplex *  __vDSP_b,
  vDSP_Stride              __vDSP_j,
  DSPDoubleSplitComplex *  __vDSP_c,
  vDSP_Stride              __vDSP_k,
  DSPDoubleSplitComplex *  __vDSP_d,
  vDSP_Stride              __vDSP_l,
  vDSP_Length              __vDSP_M,
  vDSP_Length              __vDSP_N,
  vDSP_Length              __vDSP_P)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split matrix subtract and multiply, single-precision.*/
/*
 *  vDSP_zmsm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zmsm(
  DSPSplitComplex *  __vDSP_a,
  vDSP_Stride        __vDSP_i,
  DSPSplitComplex *  __vDSP_b,
  vDSP_Stride        __vDSP_j,
  DSPSplitComplex *  __vDSP_c,
  vDSP_Stride        __vDSP_k,
  DSPSplitComplex *  __vDSP_d,
  vDSP_Stride        __vDSP_l,
  vDSP_Length        __vDSP_M,
  vDSP_Length        __vDSP_N,
  vDSP_Length        __vDSP_P)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split matrix subtract and multiply, double-precision.*/
/*
 *  vDSP_zmsmD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zmsmD(
  DSPDoubleSplitComplex *  __vDSP_a,
  vDSP_Stride              __vDSP_i,
  DSPDoubleSplitComplex *  __vDSP_b,
  vDSP_Stride              __vDSP_j,
  DSPDoubleSplitComplex *  __vDSP_c,
  vDSP_Stride              __vDSP_k,
  DSPDoubleSplitComplex *  __vDSP_d,
  vDSP_Stride              __vDSP_l,
  vDSP_Length              __vDSP_M,
  vDSP_Length              __vDSP_N,
  vDSP_Length              __vDSP_P)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split matrix multiply, single-precision.*/
/*
 *  vDSP_zmmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zmmul(
  DSPSplitComplex *  __vDSP_a,
  vDSP_Stride        __vDSP_i,
  DSPSplitComplex *  __vDSP_b,
  vDSP_Stride        __vDSP_j,
  DSPSplitComplex *  __vDSP_c,
  vDSP_Stride        __vDSP_k,
  vDSP_Length        __vDSP_M,
  vDSP_Length        __vDSP_N,
  vDSP_Length        __vDSP_P)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split matrix multiply, double-precision.*/
/*
 *  vDSP_zmmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zmmulD(
  DSPDoubleSplitComplex *  __vDSP_a,
  vDSP_Stride              __vDSP_i,
  DSPDoubleSplitComplex *  __vDSP_b,
  vDSP_Stride              __vDSP_j,
  DSPDoubleSplitComplex *  __vDSP_c,
  vDSP_Stride              __vDSP_k,
  vDSP_Length              __vDSP_M,
  vDSP_Length              __vDSP_N,
  vDSP_Length              __vDSP_P)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Vector add, single-precision.*/
/*
 *  vDSP_vadd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_vadd(
  const float   __vDSP_input1[],
  vDSP_Stride   __vDSP_stride1,
  const float   __vDSP_input2[],
  vDSP_Stride   __vDSP_stride2,
  float         __vDSP_result[],
  vDSP_Stride   __vDSP_strideResult,
  vDSP_Length   __vDSP_size)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Vector add, double-precision.*/
/*
 *  vDSP_vaddD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vaddD(
  const double   __vDSP_input1[],
  vDSP_Stride    __vDSP_stride1,
  const double   __vDSP_input2[],
  vDSP_Stride    __vDSP_stride2,
  double         __vDSP_result[],
  vDSP_Stride    __vDSP_strideResult,
  vDSP_Length    __vDSP_size)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Vector subtract, single-precision.*/
/*
 *  vDSP_vsub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_vsub(
  const float   __vDSP_input1[],
  vDSP_Stride   __vDSP_stride1,
  const float   __vDSP_input2[],
  vDSP_Stride   __vDSP_stride2,
  float         __vDSP_result[],
  vDSP_Stride   __vDSP_strideResult,
  vDSP_Length   __vDSP_size)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Vector subtract, double-precision.*/
/*
 *  vDSP_vsubD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsubD(
  const double   __vDSP_input1[],
  vDSP_Stride    __vDSP_stride1,
  const double   __vDSP_input2[],
  vDSP_Stride    __vDSP_stride2,
  double         __vDSP_result[],
  vDSP_Stride    __vDSP_strideResult,
  vDSP_Length    __vDSP_size)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Vector multiply, single-precision.*/
/*
 *  vDSP_vmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_vmul(
  const float   __vDSP_input1[],
  vDSP_Stride   __vDSP_stride1,
  const float   __vDSP_input2[],
  vDSP_Stride   __vDSP_stride2,
  float         __vDSP_result[],
  vDSP_Stride   __vDSP_strideResult,
  vDSP_Length   __vDSP_size)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Vector multiply, double-precision.*/
/*
 *  vDSP_vmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmulD(
  const double   __vDSP_input1[],
  vDSP_Stride    __vDSP_stride1,
  const double   __vDSP_input2[],
  vDSP_Stride    __vDSP_stride2,
  double         __vDSP_result[],
  vDSP_Stride    __vDSP_strideResult,
  vDSP_Length    __vDSP_size)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Vector-scalar multiply, single-precision.*/
/*
 *  vDSP_vsmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_vsmul(
  const float    __vDSP_input1[],
  vDSP_Stride    __vDSP_stride1,
  const float *  __vDSP_input2,
  float          __vDSP_result[],
  vDSP_Stride    __vDSP_strideResult,
  vDSP_Length    __vDSP_size)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Vector-scalar multiply, double-precision.*/
/*
 *  vDSP_vsmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsmulD(
  const double    __vDSP_input1[],
  vDSP_Stride     __vDSP_stride1,
  const double *  __vDSP_input2,
  double          __vDSP_result[],
  vDSP_Stride     __vDSP_strideResult,
  vDSP_Length     __vDSP_size)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Vector square, single-precision.*/
/*
 *  vDSP_vsq()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_vsq(
  const float   __vDSP_input[],
  vDSP_Stride   __vDSP_strideInput,
  float         __vDSP_result[],
  vDSP_Stride   __vDSP_strideResult,
  vDSP_Length   __vDSP_size)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Vector square, double-precision.*/
/*
 *  vDSP_vsqD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsqD(
  const double   __vDSP_input[],
  vDSP_Stride    __vDSP_strideInput,
  double         __vDSP_result[],
  vDSP_Stride    __vDSP_strideResult,
  vDSP_Length    __vDSP_size)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/* Vector signed square, single-precision.*/
/*
 *  vDSP_vssq()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_vssq(
  const float   __vDSP_input[],
  vDSP_Stride   __vDSP_strideInput,
  float         __vDSP_result[],
  vDSP_Stride   __vDSP_strideResult,
  vDSP_Length   __vDSP_size)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Vector signed square, double-precision.*/
/*
 *  vDSP_vssqD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vssqD(
  const double   __vDSP_input[],
  vDSP_Stride    __vDSP_strideInput,
  double         __vDSP_result[],
  vDSP_Stride    __vDSP_strideResult,
  vDSP_Length    __vDSP_size)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Dot product, single-precision.*/
/*
 *  vDSP_dotpr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_dotpr(
  const float   __vDSP_input1[],
  vDSP_Stride   __vDSP_stride1,
  const float   __vDSP_input2[],
  vDSP_Stride   __vDSP_stride2,
  float *       __vDSP_result,
  vDSP_Length   __vDSP_size)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Dot product, double-precision.*/
/*
 *  vDSP_dotprD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_dotprD(
  const double   __vDSP_input1[],
  vDSP_Stride    __vDSP_stride1,
  const double   __vDSP_input2[],
  vDSP_Stride    __vDSP_stride2,
  double *       __vDSP_result,
  vDSP_Length    __vDSP_size)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Vector add and multiply, single-precision.*/
/*
 *  vDSP_vam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_vam(
  const float   __vDSP_input1[],
  vDSP_Stride   __vDSP_stride1,
  const float   __vDSP_input2[],
  vDSP_Stride   __vDSP_stride2,
  const float   __vDSP_input3[],
  vDSP_Stride   __vDSP_stride3,
  float         __vDSP_result[],
  vDSP_Stride   __vDSP_strideResult,
  vDSP_Length   __vDSP_size)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Vector add and multiply, double-precision.*/
/*
 *  vDSP_vamD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vamD(
  const double   __vDSP_input1[],
  vDSP_Stride    __vDSP_stride1,
  const double   __vDSP_input2[],
  vDSP_Stride    __vDSP_stride2,
  const double   __vDSP_input3[],
  vDSP_Stride    __vDSP_stride3,
  double         __vDSP_result[],
  vDSP_Stride    __vDSP_strideResult,
  vDSP_Length    __vDSP_size)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split convolution, single-precision.*/
/*
 *  vDSP_zconv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zconv(
  DSPSplitComplex *  __vDSP_signal,
  vDSP_Stride        __vDSP_signalStride,
  DSPSplitComplex *  __vDSP_filter,
  vDSP_Stride        __vDSP_strideFilter,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_lenResult,
  vDSP_Length        __vDSP_lenFilter)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Complex-split convolution, double-precision.*/
/*
 *  vDSP_zconvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zconvD(
  DSPDoubleSplitComplex *  __vDSP_signal,
  vDSP_Stride              __vDSP_signalStride,
  DSPDoubleSplitComplex *  __vDSP_filter,
  vDSP_Stride              __vDSP_strideFilter,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_lenResult,
  vDSP_Length              __vDSP_lenFilter)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split vector add, single-precision.*/
/*
 *  vDSP_zvadd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zvadd(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  DSPSplitComplex *  __vDSP_input2,
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Complex-split vector add, double-precision.*/
/*
 *  vDSP_zvaddD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvaddD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  DSPDoubleSplitComplex *  __vDSP_input2,
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split vector subtract, single-precision.*/
/*
 *  vDSP_zvsub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zvsub(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  DSPSplitComplex *  __vDSP_input2,
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Complex-split vector subtract, double-precision.*/
/*
 *  vDSP_zvsubD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvsubD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  DSPDoubleSplitComplex *  __vDSP_input2,
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split vector multiply, single-precision.*/
/*
 *  vDSP_zvmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zvmul(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  DSPSplitComplex *  __vDSP_input2,
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_size,
  int                __vDSP_conjugate)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Complex-split vector multiply, double-precision.*/
/*
 *  vDSP_zvmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvmulD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  DSPDoubleSplitComplex *  __vDSP_input2,
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_size,
  int                      __vDSP_conjugate)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split dot product, single-precision.*/
/*
 *  vDSP_zdotpr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zdotpr(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  DSPSplitComplex *  __vDSP_input2,
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Complex-split dot product, double-precision.*/
/*
 *  vDSP_zdotprD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zdotprD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  DSPDoubleSplitComplex *  __vDSP_input2,
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split inner (conjugate) dot product, single-precision.*/
/*
 *  vDSP_zidotpr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zidotpr(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  DSPSplitComplex *  __vDSP_input2,
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Complex-split inner (conjugate) dot product, double-precision.*/
/*
 *  vDSP_zidotprD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zidotprD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  DSPDoubleSplitComplex *  __vDSP_input2,
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Dot product of complex-split with real, single-precision.*/
/*
 *  vDSP_zrdotpr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zrdotpr(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  const float        __vDSP_input2[],
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Dot product of complex-split with real, double-precision.*/
/*
 *  vDSP_zrdotprD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zrdotprD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  const double             __vDSP_input2[],
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Complex-split conjugate multiply and add, single-precision.*/
/*
 *  vDSP_zvcma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zvcma(
  const DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  const DSPSplitComplex *  __vDSP_input2,
  vDSP_Stride              __vDSP_stride2,
  DSPSplitComplex *        __vDSP_input3,
  vDSP_Stride              __vDSP_stride3,
  DSPSplitComplex *        __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Complex-split conjugate multiply and add, double-precision.*/
/*
 *  vDSP_zvcmaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvcmaD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  DSPDoubleSplitComplex *  __vDSP_input2,
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_input3,
  vDSP_Stride              __vDSP_stride3,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Add complex-split and real, single-precision.*/
/*
 *  vDSP_zrvadd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zrvadd(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  const float        __vDSP_input2[],
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Add complex-split and real, double-precision.*/
/*
 *  vDSP_zrvaddD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zrvaddD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  const double             __vDSP_input2[],
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Subtract real from complex-split, single-precision.*/
/*
 *  vDSP_zrvsub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zrvsub(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  const float        __vDSP_input2[],
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Subtract real from complex-split, double-precision.*/
/*
 *  vDSP_zrvsubD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zrvsubD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  const double             __vDSP_input2[],
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Multiply complex-split and real, single-precision.*/
/*
 *  vDSP_zrvmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_zrvmul(
  DSPSplitComplex *  __vDSP_input1,
  vDSP_Stride        __vDSP_stride1,
  const float        __vDSP_input2[],
  vDSP_Stride        __vDSP_stride2,
  DSPSplitComplex *  __vDSP_result,
  vDSP_Stride        __vDSP_strideResult,
  vDSP_Length        __vDSP_size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Multiply complex-split and real, double-precision.*/
/*
 *  vDSP_zrvmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zrvmulD(
  DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride              __vDSP_stride1,
  const double             __vDSP_input2[],
  vDSP_Stride              __vDSP_stride2,
  DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride              __vDSP_strideResult,
  vDSP_Length              __vDSP_size)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Vector convert double-precision to single-precision.*/
/*
 *  vDSP_vdpsp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vdpsp(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert single-precision to double-precision.*/
/*
 *  vDSP_vspdp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vspdp(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector absolute value, integer.*/
/*
 *  vDSP_vabsi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vabsi(
  int *         __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector (bit-wise) equivalence (not (A xor B)), integer.*/
/*
 *  vDSP_veqvi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_veqvi(
  int *         __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_B,
  vDSP_Stride   __vDSP_J,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector divide, integer.*/
/*
 *  vDSP_vdivi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vdivi(
  int *         __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_B,
  vDSP_Stride   __vDSP_J,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector fill, integer.*/
/*
 *  vDSP_vfilli()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfilli(
  int *         __vDSP_A,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar add, integer.*/
/*
 *  vDSP_vsaddi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsaddi(
  int *         __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_B,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar divide, integer.*/
/*
 *  vDSP_vsdivi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsdivi(
  int *         __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_B,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split accumulating autospectrum, single-precision.*/
/*
 *  vDSP_zaspec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zaspec(
  DSPSplitComplex *  __vDSP_A,
  float *            __vDSP_C,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split accumulating autospectrum, double-precision.*/
/*
 *  vDSP_zaspecD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zaspecD(
  DSPDoubleSplitComplex *  A,
  double *                 __vDSP_C,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Create Blackman window, single-precision.*/
/*
 *  vDSP_blkman_window()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_blkman_window(
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N,
  int           __vDSP_FLAG)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Create Blackman window, double-precision.*/
/*
 *  vDSP_blkman_windowD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_blkman_windowD(
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N,
  int           __vDSP_FLAG)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split coherence function, single-precision.*/
/*
 *  vDSP_zcoher()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zcoher(
  float *            __vDSP_A,
  float *            __vDSP_B,
  DSPSplitComplex *  __vDSP_C,
  float *            __vDSP_D,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split coherence function, double-precision.*/
/*
 *  vDSP_zcoherD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zcoherD(
  double *                 __vDSP_A,
  double *                 __vDSP_B,
  DSPDoubleSplitComplex *  __vDSP_C,
  double *                 __vDSP_D,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split anti-aliasing down-sample with real filter, single-precision.*/
/*
 *  vDSP_zrdesamp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zrdesamp(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  float *            __vDSP_B,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Length        __vDSP_N,
  vDSP_Length        __vDSP_M)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split anti-aliasing down-sample with real filter, double-precision.*/
/*
 *  vDSP_zrdesampD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zrdesampD(
  DSPDoubleSplitComplex *  A,
  vDSP_Stride              __vDSP_I,
  double *                 __vDSP_B,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Length              __vDSP_N,
  vDSP_Length              __vDSP_M)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector complex-split divide by real, single-precision.*/
/*
 *  vDSP_zrvdiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zrvdiv(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  float *            __vDSP_B,
  vDSP_Stride        __vDSP_J,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector complex-split divide by real, double-precision.*/
/*
 *  vDSP_zrvdivD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zrvdivD(
  DSPDoubleSplitComplex *  A,
  vDSP_Stride              __vDSP_I,
  double *                 __vDSP_B,
  vDSP_Stride              __vDSP_J,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Transfer function (B/A), single-precision.*/
/*
 *  vDSP_ztrans()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_ztrans(
  float *            __vDSP_A,
  DSPSplitComplex *  __vDSP_B,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Transfer function (B/A), double-precision.*/
/*
 *  vDSP_ztransD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_ztransD(
  double *                 __vDSP_A,
  DSPDoubleSplitComplex *  __vDSP_B,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector divide, single-precision.*/
/*
 *  vDSP_zvdiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvdiv(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  DSPSplitComplex *  __vDSP_B,
  vDSP_Stride        __vDSP_J,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector divide, double-precision.*/
/*
 *  vDSP_zvdivD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvdivD(
  DSPDoubleSplitComplex *  A,
  vDSP_Stride              __vDSP_I,
  DSPDoubleSplitComplex *  __vDSP_B,
  vDSP_Stride              __vDSP_J,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split accumulating cross-spectrum, single-precision.*/
/*
 *  vDSP_zcspec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zcspec(
  DSPSplitComplex *  __vDSP_A,
  DSPSplitComplex *  __vDSP_B,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split accumulating cross-spectrum, double-precision.*/
/*
 *  vDSP_zcspecD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zcspecD(
  DSPDoubleSplitComplex *  A,
  DSPDoubleSplitComplex *  __vDSP_B,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector absolute value, single-precision.*/
/*
 *  vDSP_zvabs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvabs(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  float *            __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector absolute value, double-precision.*/
/*
 *  vDSP_zvabsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvabsD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  double *                 __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector conjugate and multiply, single-precision.*/
/*
 *  vDSP_zvcmul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvcmul(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  DSPSplitComplex *  __vDSP_B,
  vDSP_Stride        __vDSP_J,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector conjugate and multiply, double-precision.*/
/*
 *  vDSP_zvcmulD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvcmulD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  DSPDoubleSplitComplex *  __vDSP_B,
  vDSP_Stride              __vDSP_J,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector conjugate, single-precision.*/
/*
 *  vDSP_zvconj()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvconj(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector conjugate, double-precision.*/
/*
 *  vDSP_zvconjD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvconjD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector multiply with scalar, single-precision.*/
/*
 *  vDSP_zvzsml()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvzsml(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  DSPSplitComplex *  __vDSP_B,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector multiply with scalar, double-precision.*/
/*
 *  vDSP_zvzsmlD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvzsmlD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  DSPDoubleSplitComplex *  __vDSP_B,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector fill, single-precision.*/
/*
 *  vDSP_zvfill()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvfill(
  DSPSplitComplex *  __vDSP_A,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector fill, double-precision.*/
/*
 *  vDSP_zvfillD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvfillD(
  DSPDoubleSplitComplex *  __vDSP_A,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector magnitudes squared, single-precision.*/
/*
 *  vDSP_zvmags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvmags(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  float *            __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector magnitudes squared, double-precision.*/
/*
 *  vDSP_zvmagsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvmagsD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  double *                 __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector magnitudes square and add, single-precision.*/
/*
 *  vDSP_zvmgsa()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvmgsa(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  float *            __vDSP_B,
  vDSP_Stride        __vDSP_J,
  float *            __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector magnitudes square and add, double-precision.*/
/*
 *  vDSP_zvmgsaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvmgsaD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  double *                 __vDSP_B,
  vDSP_Stride              __vDSP_J,
  double *                 __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector move, single-precision.*/
/*
 *  vDSP_zvmov()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvmov(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector move, double-precision.*/
/*
 *  vDSP_zvmovD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvmovD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector negate, single-precision.*/
/*
 *  vDSP_zvneg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvneg(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector negate, double-precision.*/
/*
 *  vDSP_zvnegD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvnegD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector phase, single-precision.*/
/*
 *  vDSP_zvphas()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvphas(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  float *            __vDSP_C,
  vDSP_Stride        __vDSP_K,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector phase, double-precision.*/
/*
 *  vDSP_zvphasD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvphasD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  double *                 __vDSP_C,
  vDSP_Stride              __vDSP_K,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector multiply by scalar and add, single-precision.*/
/*
 *  vDSP_zvsma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvsma(
  DSPSplitComplex *  __vDSP_A,
  vDSP_Stride        __vDSP_I,
  DSPSplitComplex *  __vDSP_B,
  DSPSplitComplex *  __vDSP_C,
  vDSP_Stride        __vDSP_K,
  DSPSplitComplex *  __vDSP_D,
  vDSP_Stride        __vDSP_L,
  vDSP_Length        __vDSP_N)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Complex-split vector multiply by scalar and add, double-precision.*/
/*
 *  vDSP_zvsmaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_zvsmaD(
  DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride              __vDSP_I,
  DSPDoubleSplitComplex *  __vDSP_B,
  DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride              __vDSP_K,
  DSPDoubleSplitComplex *  __vDSP_D,
  vDSP_Stride              __vDSP_L,
  vDSP_Length              __vDSP_N)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Difference equation, 2 poles, 2 zeros, single-precision.*/
/*
 *  vDSP_deq22()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_deq22(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Difference equation, 2 poles, 2 zeros, double-precision.*/
/*
 *  vDSP_deq22D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_deq22D(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Convolution with decimation (desampling), single-precision.*/
/*
 *  vDSP_desamp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_desamp(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_M)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Convolution with decimation (desampling), double-precision.*/
/*
 *  vDSP_desampD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_desampD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_M)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Create Hamming window, single-precision.*/
/*
 *  vDSP_hamm_window()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_hamm_window(
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N,
  int           __vDSP_FLAG)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Create Hamming window, double-precision.*/
/*
 *  vDSP_hamm_windowD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_hamm_windowD(
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N,
  int           __vDSP_FLAG)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Create Hanning window, single-precision.*/
/*
 *  vDSP_hann_window()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_hann_window(
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N,
  int           __vDSP_FLAG)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Create Hanning window, double-precision.*/
/*
 *  vDSP_hann_windowD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_hann_windowD(
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N,
  int           __vDSP_FLAG)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Maximum magnitude of vector, single-precision.*/
/*
 *  vDSP_maxmgv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_maxmgv(
  const float *  __vDSP_A,
  vDSP_Stride    __vDSP_I,
  float *        __vDSP_C,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Maximum magnitude of vector, double-precision.*/
/*
 *  vDSP_maxmgvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_maxmgvD(
  const double *  __vDSP_A,
  vDSP_Stride     __vDSP_I,
  double *        __vDSP_C,
  vDSP_Length     __vDSP_N)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Maximum magnitude of vector, with index, single-precision.*/
/*
 *  vDSP_maxmgvi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_maxmgvi(
  float *        __vDSP_A,
  vDSP_Stride    __vDSP_I,
  float *        __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Maximum magnitude of vector, with index, double-precision.*/
/*
 *  vDSP_maxmgviD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_maxmgviD(
  double *       __vDSP_A,
  vDSP_Stride    __vDSP_I,
  double *       __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Maximum value of vector, single-precision.*/
/*
 *  vDSP_maxv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_maxv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Maximum value of vector, double-precision.*/
/*
 *  vDSP_maxvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_maxvD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Maximum value of vector, with index, single-precision.*/
/*
 *  vDSP_maxvi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_maxvi(
  float *        __vDSP_A,
  vDSP_Stride    __vDSP_I,
  float *        __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Maximum value of vector, with index, double-precision.*/
/*
 *  vDSP_maxviD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_maxviD(
  double *       __vDSP_A,
  vDSP_Stride    __vDSP_I,
  double *       __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Mean magnitude of vector, single-precision.*/
/*
 *  vDSP_meamgv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_meamgv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Mean magnitude of vector, double-precision.*/
/*
 *  vDSP_meamgvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_meamgvD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Mean of vector, single-precision.*/
/*
 *  vDSP_meanv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_meanv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Mean of vector, double-precision.*/
/*
 *  vDSP_meanvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_meanvD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Mean square of vector, single-precision.*/
/*
 *  vDSP_measqv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_measqv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Mean square of vector, double-precision.*/
/*
 *  vDSP_measqvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_measqvD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Minimum magnitude of vector, single-precision.*/
/*
 *  vDSP_minmgv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_minmgv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Minimum magnitude of vector, double-precision.*/
/*
 *  vDSP_minmgvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_minmgvD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Minimum magnitude of vector, with index, single-precision.*/
/*
 *  vDSP_minmgvi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_minmgvi(
  float *        __vDSP_A,
  vDSP_Stride    __vDSP_I,
  float *        __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Minimum magnitude of vector, with index, double-precision.*/
/*
 *  vDSP_minmgviD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_minmgviD(
  double *       __vDSP_A,
  vDSP_Stride    __vDSP_I,
  double *       __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Minimum value of vector, single-precision.*/
/*
 *  vDSP_minv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_minv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Minimum value of vector, double-precision.*/
/*
 *  vDSP_minvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_minvD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Minimum value of vector, with index, single-precision.*/
/*
 *  vDSP_minvi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_minvi(
  float *        __vDSP_A,
  vDSP_Stride    __vDSP_I,
  float *        __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Minimum value of vector, with index, double-precision.*/
/*
 *  vDSP_minviD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_minviD(
  double *       __vDSP_A,
  vDSP_Stride    __vDSP_I,
  double *       __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Matrix move, single-precision.*/
/*
 *  vDSP_mmov()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_mmov(
  float *       __vDSP_A,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_NC,
  vDSP_Length   __vDSP_NR,
  vDSP_Length   __vDSP_TCA,
  vDSP_Length   __vDSP_TCC)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Matrix move, double-precision.*/
/*
 *  vDSP_mmovD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_mmovD(
  double *      __vDSP_A,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_NC,
  vDSP_Length   __vDSP_NR,
  vDSP_Length   __vDSP_TCA,
  vDSP_Length   __vDSP_TCC)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Mean of signed squares of vector, single-precision.*/
/*
 *  vDSP_mvessq()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_mvessq(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Mean of signed squares of vector, double-precision.*/
/*
 *  vDSP_mvessqD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_mvessqD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Find zero crossing, single-precision.*/
/*
 *  vDSP_nzcros()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_nzcros(
  float *        __vDSP_A,
  vDSP_Stride    __vDSP_I,
  vDSP_Length    __vDSP_B,
  vDSP_Length *  __vDSP_C,
  vDSP_Length *  __vDSP_D,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Find zero crossing, double-precision.*/
/*
 *  vDSP_nzcrosD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_nzcrosD(
  double *       __vDSP_A,
  vDSP_Stride    __vDSP_I,
  vDSP_Length    __vDSP_B,
  vDSP_Length *  __vDSP_C,
  vDSP_Length *  __vDSP_D,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Convert rectangular to polar, single-precision.*/
/*
 *  vDSP_polar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_polar(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Convert rectangular to polar, double-precision.*/
/*
 *  vDSP_polarD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_polarD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Convert polar to rectangular, single-precision.*/
/*
 *  vDSP_rect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_rect(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Convert polar to rectangular, double-precision.*/
/*
 *  vDSP_rectD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_rectD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Root-mean-square of vector, single-precision.*/
/*
 *  vDSP_rmsqv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_rmsqv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Root-mean-square of vector, double-precision.*/
/*
 *  vDSP_rmsqvD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_rmsqvD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Scalar-vector divide, single-precision.*/
/*
 *  vDSP_svdiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_svdiv(
  float *       __vDSP_A,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Scalar-vector divide, double-precision.*/
/*
 *  vDSP_svdivD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_svdivD(
  double *      __vDSP_A,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Sum of vector elements, single-precision.*/
/*
 *  vDSP_sve()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_sve(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Sum of vector elements, double-precision.*/
/*
 *  vDSP_sveD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_sveD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Sum of vector elements magnitudes, single-precision.*/
/*
 *  vDSP_svemg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_svemg(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Sum of vector elements' magnitudes, double-precision.*/
/*
 *  vDSP_svemgD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_svemgD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Sum of vector elements' squares, single-precision.*/
/*
 *  vDSP_svesq()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_svesq(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Sum of vector elements' squares, double-precision.*/
/*
 *  vDSP_svesqD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_svesqD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Sum of vector elements' signed squares, single-precision.*/
/*
 *  vDSP_svs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_svs(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Sum of vector elements' signed squares, double-precision.*/
/*
 *  vDSP_svsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_svsD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector add, add, and multiply, single-precision.*/
/*
 *  vDSP_vaam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vaam(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  float *       __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector add, add, and multiply, double-precision.*/
/*
 *  vDSP_vaamD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vaamD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  double *      __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector absolute value, single-precision.*/
/*
 *  vDSP_vabs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vabs(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector absolute value, double-precision.*/
/*
 *  vDSP_vabsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vabsD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector add, subtract, and multiply, single-precision.*/
/*
 *  vDSP_vasbm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vasbm(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  float *       __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector add, subtract, and multiply, double-precision.*/
/*
 *  vDSP_vasbmD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vasbmD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  double *      __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector add and scalar multiply, single-precision.*/
/*
 *  vDSP_vasm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vasm(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector add and scalar multiply, double-precision.*/
/*
 *  vDSP_vasmD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vasmD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector linear average, single-precision.*/
/*
 *  vDSP_vavlin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vavlin(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector linear average, double-precision.*/
/*
 *  vDSP_vavlinD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vavlinD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector clip, single-precision.*/
/*
 *  vDSP_vclip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vclip(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector clip, double-precision.*/
/*
 *  vDSP_vclipD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vclipD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector clip and count, single-precision.*/
/*
 *  vDSP_vclipc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vclipc(
  float *        __vDSP_A,
  vDSP_Stride    __vDSP_I,
  float *        __vDSP_B,
  float *        __vDSP_C,
  float *        __vDSP_D,
  vDSP_Stride    __vDSP_L,
  vDSP_Length    __vDSP_N,
  vDSP_Length *  __vDSP_NLOW,
  vDSP_Length *  __vDSP_NHI)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector clip and count, double-precision.*/
/*
 *  vDSP_vclipcD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vclipcD(
  double *       __vDSP_A,
  vDSP_Stride    __vDSP_I,
  double *       __vDSP_B,
  double *       __vDSP_C,
  double *       __vDSP_D,
  vDSP_Stride    __vDSP_L,
  vDSP_Length    __vDSP_N,
  vDSP_Length *  __vDSP_NLOW,
  vDSP_Length *  __vDSP_NHI)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector clear, single-precision.*/
/*
 *  vDSP_vclr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vclr(
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector clear, double-precision.*/
/*
 *  vDSP_vclrD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vclrD(
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector compress, single-precision.*/
/*
 *  vDSP_vcmprs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vcmprs(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector compress, double-precision.*/
/*
 *  vDSP_vcmprsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vcmprsD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to decibels, power, or amplitude, single-precision.*/
/*
 *  vDSP_vdbcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vdbcon(
  float *        __vDSP_A,
  vDSP_Stride    __vDSP_I,
  float *        __vDSP_B,
  float *        __vDSP_C,
  vDSP_Stride    __vDSP_K,
  vDSP_Length    __vDSP_N,
  unsigned int   __vDSP_F)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to decibels, power, or amplitude, double-precision.*/
/*
 *  vDSP_vdbconD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vdbconD(
  double *       __vDSP_A,
  vDSP_Stride    __vDSP_I,
  double *       __vDSP_B,
  double *       __vDSP_C,
  vDSP_Stride    __vDSP_K,
  vDSP_Length    __vDSP_N,
  unsigned int   __vDSP_F)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector distance, single-precision.*/
/*
 *  vDSP_vdist()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vdist(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector distance, double-precision.*/
/*
 *  vDSP_vdistD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vdistD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector divide, single-precision.*/
/*
 *  vDSP_vdiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vdiv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector divide, double-precision.*/
/*
 *  vDSP_vdivD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vdivD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector envelope, single-precision.*/
/*
 *  vDSP_venvlp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_venvlp(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector envelope, double-precision.*/
/*
 *  vDSP_venvlpD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_venvlpD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector fill, single-precision.*/
/*
 *  vDSP_vfill()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfill(
  float *       __vDSP_A,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector fill, double-precision.*/
/*
 *  vDSP_vfillD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfillD(
  double *      __vDSP_A,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 8-bit integer, round toward zero, single-precision.*/
/*
 *  vDSP_vfix8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfix8(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  char *        __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 8-bit integer, round toward zero, double-precision.*/
/*
 *  vDSP_vfix8D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfix8D(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  char *        __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 16-bit integer, round toward zero, single-precision.*/
/*
 *  vDSP_vfix16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfix16(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  short *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 16-bit integer, round toward zero, double-precision.*/
/*
 *  vDSP_vfix16D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfix16D(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  short *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 32-bit integer, round toward zero, single-precision.*/
/*
 *  vDSP_vfix32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfix32(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 32-bit integer, round toward zero, double-precision.*/
/*
 *  vDSP_vfix32D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfix32D(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 8-bit integer, round to nearest, single-precision.*/
/*
 *  vDSP_vfixr8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixr8(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  char *        __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 8-bit integer, round to nearest, double-precision.*/
/*
 *  vDSP_vfixr8D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixr8D(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  char *        __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 16-bit integer, round to nearest, single-precision.*/
/*
 *  vDSP_vfixr16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixr16(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  short *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 16-bit integer, round to nearest, double-precision.*/
/*
 *  vDSP_vfixr16D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixr16D(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  short *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 32-bit integer, round to nearest, single-precision.*/
/*
 *  vDSP_vfixr32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixr32(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to 32-bit integer, round to nearest, double-precision.*/
/*
 *  vDSP_vfixr32D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixr32D(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  int *         __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 8-bit integer, toward zero, single-precision.*/
/*
 *  vDSP_vfixu8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixu8(
  float *          __vDSP_A,
  vDSP_Stride      __vDSP_I,
  unsigned char *  __vDSP_C,
  vDSP_Stride      __vDSP_K,
  vDSP_Length      __vDSP_N)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 8-bit integer, toward zero, double-precision.*/
/*
 *  vDSP_vfixu8D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixu8D(
  double *         __vDSP_A,
  vDSP_Stride      __vDSP_I,
  unsigned char *  __vDSP_C,
  vDSP_Stride      __vDSP_K,
  vDSP_Length      __vDSP_N)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 16-bit integer, toward zero, single-precision.*/
/*
 *  vDSP_vfixu16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixu16(
  float *           __vDSP_A,
  vDSP_Stride       __vDSP_I,
  unsigned short *  __vDSP_C,
  vDSP_Stride       __vDSP_K,
  vDSP_Length       __vDSP_N)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 16-bit integer, toward zero, double-precision.*/
/*
 *  vDSP_vfixu16D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixu16D(
  double *          __vDSP_A,
  vDSP_Stride       __vDSP_I,
  unsigned short *  __vDSP_C,
  vDSP_Stride       __vDSP_K,
  vDSP_Length       __vDSP_N)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 32-bit integer, toward zero, single-precision.*/
/*
 *  vDSP_vfixu32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixu32(
  float *         __vDSP_A,
  vDSP_Stride     __vDSP_I,
  unsigned int *  __vDSP_C,
  vDSP_Stride     __vDSP_K,
  vDSP_Length     __vDSP_N)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 32-bit integer, toward zero, double-precision.*/
/*
 *  vDSP_vfixu32D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixu32D(
  double *        __vDSP_A,
  vDSP_Stride     __vDSP_I,
  unsigned int *  __vDSP_C,
  vDSP_Stride     __vDSP_K,
  vDSP_Length     __vDSP_N)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 8-bit integer, to nearest, single-precision.*/
/*
 *  vDSP_vfixru8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixru8(
  float *          __vDSP_A,
  vDSP_Stride      __vDSP_I,
  unsigned char *  __vDSP_C,
  vDSP_Stride      __vDSP_K,
  vDSP_Length      __vDSP_N)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 8-bit integer, to nearest, double-precision.*/
/*
 *  vDSP_vfixru8D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixru8D(
  double *         __vDSP_A,
  vDSP_Stride      __vDSP_I,
  unsigned char *  __vDSP_C,
  vDSP_Stride      __vDSP_K,
  vDSP_Length      __vDSP_N)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 16-bit integer, to nearest, single-precision.*/
/*
 *  vDSP_vfixru16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixru16(
  float *           __vDSP_A,
  vDSP_Stride       __vDSP_I,
  unsigned short *  __vDSP_C,
  vDSP_Stride       __vDSP_K,
  vDSP_Length       __vDSP_N)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 16-bit integer, to nearest, double-precision.*/
/*
 *  vDSP_vfixru16D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixru16D(
  double *          __vDSP_A,
  vDSP_Stride       __vDSP_I,
  unsigned short *  __vDSP_C,
  vDSP_Stride       __vDSP_K,
  vDSP_Length       __vDSP_N)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 32-bit integer, to nearest, single-precision.*/
/*
 *  vDSP_vfixru32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixru32(
  float *         __vDSP_A,
  vDSP_Stride     __vDSP_I,
  unsigned int *  __vDSP_C,
  vDSP_Stride     __vDSP_K,
  vDSP_Length     __vDSP_N)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert to unsigned 32-bit integer, to nearest, double-precision.*/
/*
 *  vDSP_vfixru32D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfixru32D(
  double *        __vDSP_A,
  vDSP_Stride     __vDSP_I,
  unsigned int *  __vDSP_C,
  vDSP_Stride     __vDSP_K,
  vDSP_Length     __vDSP_N)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 8-bit integer, single-precision.*/
/*
 *  vDSP_vflt8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vflt8(
  char *        A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 8-bit integer, double-precision.*/
/*
 *  vDSP_vflt8D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vflt8D(
  char *        A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 16-bit integer, single-precision.*/
/*
 *  vDSP_vflt16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vflt16(
  short *       A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 16-bit integer, double-precision.*/
/*
 *  vDSP_vflt16D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vflt16D(
  short *       A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 32-bit integer, single-precision.*/
/*
 *  vDSP_vflt32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vflt32(
  int *         __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 32-bit integer, double-precision.*/
/*
 *  vDSP_vflt32D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vflt32D(
  int *         __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 8-bit integer, single-precision.*/
/*
 *  vDSP_vfltu8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfltu8(
  unsigned char *  A,
  vDSP_Stride      __vDSP_I,
  float *          __vDSP_C,
  vDSP_Stride      __vDSP_K,
  vDSP_Length      __vDSP_N)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 8-bit integer, double-precision.*/
/*
 *  vDSP_vfltu8D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfltu8D(
  unsigned char *  A,
  vDSP_Stride      __vDSP_I,
  double *         __vDSP_C,
  vDSP_Stride      __vDSP_K,
  vDSP_Length      __vDSP_N)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 16-bit integer, single-precision.*/
/*
 *  vDSP_vfltu16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfltu16(
  unsigned short *  A,
  vDSP_Stride       __vDSP_I,
  float *           __vDSP_C,
  vDSP_Stride       __vDSP_K,
  vDSP_Length       __vDSP_N)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 16-bit integer, double-precision.*/
/*
 *  vDSP_vfltu16D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfltu16D(
  unsigned short *  A,
  vDSP_Stride       __vDSP_I,
  double *          __vDSP_C,
  vDSP_Stride       __vDSP_K,
  vDSP_Length       __vDSP_N)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 32-bit integer, single-precision.*/
/*
 *  vDSP_vfltu32()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfltu32(
  unsigned int *  __vDSP_A,
  vDSP_Stride     __vDSP_I,
  float *         __vDSP_C,
  vDSP_Stride     __vDSP_K,
  vDSP_Length     __vDSP_N)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector convert from 32-bit integer, double-precision.*/
/*
 *  vDSP_vfltu32D()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfltu32D(
  unsigned int *  __vDSP_A,
  vDSP_Stride     __vDSP_I,
  double *        __vDSP_C,
  vDSP_Stride     __vDSP_K,
  vDSP_Length     __vDSP_N)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector fraction part (subtract integer toward zero), single-precision.*/
/*
 *  vDSP_vfrac()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfrac(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector fraction part (subtract integer toward zero), double-precision.*/
/*
 *  vDSP_vfracD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vfracD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector gather, single-precision.*/
/*
 *  vDSP_vgathr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vgathr(
  float *        __vDSP_A,
  vDSP_Length *  __vDSP_B,
  vDSP_Stride    __vDSP_J,
  float *        __vDSP_C,
  vDSP_Stride    __vDSP_K,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector gather, double-precision.*/
/*
 *  vDSP_vgathrD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vgathrD(
  double *       __vDSP_A,
  vDSP_Length *  __vDSP_B,
  vDSP_Stride    __vDSP_J,
  double *       __vDSP_C,
  vDSP_Stride    __vDSP_K,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector gather, absolute pointers, single-precision.*/
/*
 *  vDSP_vgathra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vgathra(
  float **      A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector gather, absolute pointers, double-precision.*/
/*
 *  vDSP_vgathraD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vgathraD(
  double **     A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector generate tapered ramp, single-precision.*/
/*
 *  vDSP_vgen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vgen(
  float *       __vDSP_A,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector generate tapered ramp, double-precision.*/
/*
 *  vDSP_vgenD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vgenD(
  double *      __vDSP_A,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector generate by extrapolation and interpolation, single-precision.*/
/*
 *  vDSP_vgenp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vgenp(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_M)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector generate by extrapolation and interpolation, double-precision.*/
/*
 *  vDSP_vgenpD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vgenpD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_M)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector inverted clip, single-precision.*/
/*
 *  vDSP_viclip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_viclip(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector inverted clip, double-precision.*/
/*
 *  vDSP_viclipD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_viclipD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector index (C[i] = A[truncate[B[i]]), single-precision.*/
/*
 *  vDSP_vindex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vindex(
  float *       __vDSP_A,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector index (C[i] = A[truncate[B[i]]), double-precision.*/
/*
 *  vDSP_vindexD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vindexD(
  double *      __vDSP_A,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector interpolation between vectors, single-precision.*/
/*
 *  vDSP_vintb()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vintb(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector interpolation between vectors, double-precision.*/
/*
 *  vDSP_vintbD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vintbD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector test limit, single-precision.*/
/*
 *  vDSP_vlim()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vlim(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector test limit, double-precision.*/
/*
 *  vDSP_vlimD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vlimD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector linear interpolation, single-precision.*/
/*
 *  vDSP_vlint()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vlint(
  float *       __vDSP_A,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_M)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector linear interpolation, double-precision.*/
/*
 *  vDSP_vlintD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vlintD(
  double *      __vDSP_A,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_M)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply and add, single-precision.*/
/*
 *  vDSP_vma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vma(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply and add, double-precision.*/
/*
 *  vDSP_vmaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmaD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector maxima, single-precision.*/
/*
 *  vDSP_vmax()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmax(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector maxima, double-precision.*/
/*
 *  vDSP_vmaxD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmaxD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector maximum magnitude, single-precision.*/
/*
 *  vDSP_vmaxmg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmaxmg(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector maximum magnitude, double-precision.*/
/*
 *  vDSP_vmaxmgD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmaxmgD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector minima, single-precision.*/
/*
 *  vDSP_vmin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmin(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector minima, double-precision.*/
/*
 *  vDSP_vminD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vminD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector minimum magnitude, single-precision.*/
/*
 *  vDSP_vminmg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vminmg(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector minimum magnitude, double-precision.*/
/*
 *  vDSP_vminmgD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vminmgD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply, multiply, and add, single-precision.*/
/*
 *  vDSP_vmma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmma(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  float *       __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply, multiply, and add, double-precision.*/
/*
 *  vDSP_vmmaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmmaD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  double *      __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply, multiply, and subtract, single-precision.*/
/*
 *  vDSP_vmmsb()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmmsb(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  float *       __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply, multiply, and subtract, double-precision.*/
/*
 *  vDSP_vmmsbD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmmsbD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  double *      __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply and scalar add, single-precision.*/
/*
 *  vDSP_vmsa()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmsa(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply and scalar add, double-precision.*/
/*
 *  vDSP_vmsaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmsaD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply and subtract, single-precision.*/
/*
 *  vDSP_vmsb()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmsb(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector multiply and subtract, double-precision.*/
/*
 *  vDSP_vmsbD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vmsbD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector negative absolute value, single-precision.*/
/*
 *  vDSP_vnabs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vnabs(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector negative absolute value, double-precision.*/
/*
 *  vDSP_vnabsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vnabsD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector negate, single-precision.*/
/*
 *  vDSP_vneg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vneg(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector negate, double-precision.*/
/*
 *  vDSP_vnegD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vnegD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector polynomial, single-precision.*/
/*
 *  vDSP_vpoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vpoly(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_P)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector polynomial, single-precision.*/
/*
 *  vDSP_vpolyD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vpolyD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_P)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector Pythagoras, single-precision.*/
/*
 *  vDSP_vpythg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vpythg(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  float *       __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector Pythagoras, double-precision.*/
/*
 *  vDSP_vpythgD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vpythgD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  double *      __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector quadratic interpolation, single-precision.*/
/*
 *  vDSP_vqint()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vqint(
  float *       __vDSP_A,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_M)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector quadratic interpolation, double-precision.*/
/*
 *  vDSP_vqintD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vqintD(
  double *      __vDSP_A,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_M)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector build ramp, single-precision.*/
/*
 *  vDSP_vramp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vramp(
  float *       __vDSP_A,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector build ramp, double-precision.*/
/*
 *  vDSP_vrampD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vrampD(
  double *      __vDSP_A,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector running sum integration, single-precision.*/
/*
 *  vDSP_vrsum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vrsum(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_S,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector running sum integration, double-precision.*/
/*
 *  vDSP_vrsumD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vrsumD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_S,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector reverse order, in-place, single-precision.*/
/*
 *  vDSP_vrvrs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vrvrs(
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector reverse order, in-place, double-precision.*/
/*
 *  vDSP_vrvrsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vrvrsD(
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar add, single-precision.*/
/*
 *  vDSP_vsadd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsadd(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar add, double-precision.*/
/*
 *  vDSP_vsaddD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsaddD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector subtract and multiply, single-precision.*/
/*
 *  vDSP_vsbm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsbm(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector subtract and multiply, double-precision.*/
/*
 *  vDSP_vsbmD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsbmD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector subtract, subtract, and multiply, single-precision.*/
/*
 *  vDSP_vsbsbm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsbsbm(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  float *       __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector subtract, subtract, and multiply, double-precision.*/
/*
 *  vDSP_vsbsbmD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsbsbmD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  double *      __vDSP_E,
  vDSP_Stride   __vDSP_M,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector subtract and scalar multiply, single-precision.*/
/*
 *  vDSP_vsbsm()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsbsm(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector subtract and scalar multiply, double-precision.*/
/*
 *  vDSP_vsbsmD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsbsmD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar divide, single-precision.*/
/*
 *  vDSP_vsdiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsdiv(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar divide, double-precision.*/
/*
 *  vDSP_vsdivD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsdivD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector Simpson integration, single-precision.*/
/*
 *  vDSP_vsimps()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsimps(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector Simpson integration, double-precision.*/
/*
 *  vDSP_vsimpsD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsimpsD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar multiply and vector add, single-precision.*/
/*
 *  vDSP_vsma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsma(
  const float *  __vDSP_A,
  vDSP_Stride    __vDSP_I,
  const float *  __vDSP_B,
  const float *  __vDSP_C,
  vDSP_Stride    __vDSP_K,
  float *        __vDSP_D,
  vDSP_Stride    __vDSP_L,
  vDSP_Length    __vDSP_N)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar multiply and vector add, double-precision.*/
/*
 *  vDSP_vsmaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsmaD(
  const double *  __vDSP_A,
  vDSP_Stride     __vDSP_I,
  const double *  __vDSP_B,
  const double *  __vDSP_C,
  vDSP_Stride     __vDSP_K,
  double *        __vDSP_D,
  vDSP_Stride     __vDSP_L,
  vDSP_Length     __vDSP_N)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar multiply and scalar add, single-precision.*/
/*
 *  vDSP_vsmsa()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsmsa(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector-scalar multiply and scalar add, double-precision.*/
/*
 *  vDSP_vsmsaD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsmsaD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector scalar multiply and vector subtract, single-precision.*/
/*
 *  vDSP_vsmsb()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsmsb(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector scalar multiply and vector subtract, double-precision.*/
/*
 *  vDSP_vsmsbD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsmsbD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector sort, in-place, single-precision.*/
/*
 *  vDSP_vsort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsort(
  float *       __vDSP_C,
  vDSP_Length   __vDSP_N,
  int           __vDSP_OFLAG)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector sort, in-place, double-precision.*/
/*
 *  vDSP_vsortD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsortD(
  double *      __vDSP_C,
  vDSP_Length   __vDSP_N,
  int           __vDSP_OFLAG)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector sort, in-place, integer, single-precision.*/
/*
 *  vDSP_vsorti()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsorti(
  float *        __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length *  __vDSP_List_addr,
  vDSP_Length    __vDSP_N,
  int            __vDSP_OFLAG)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector sort, in-place, integer, double-precision.*/
/*
 *  vDSP_vsortiD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vsortiD(
  double *       __vDSP_C,
  vDSP_Length *  __vDSP_IC,
  vDSP_Length *  __vDSP_List_addr,
  vDSP_Length    __vDSP_N,
  int            __vDSP_OFLAG)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector swap, single-precision.*/
/*
 *  vDSP_vswap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vswap(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector swap, double-precision.*/
/*
 *  vDSP_vswapD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vswapD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector sliding window sum, single-precision.*/
/*
 *  vDSP_vswsum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vswsum(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_P)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector sliding window sum, double-precision.*/
/*
 *  vDSP_vswsumD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vswsumD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N,
  vDSP_Length   __vDSP_P)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector table lookup and interpolation, single-precision.*/
/*
 *  vDSP_vtabi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vtabi(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_S1,
  float *       __vDSP_S2,
  float *       __vDSP_C,
  vDSP_Length   __vDSP_M,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector table lookup and interpolation, double-precision.*/
/*
 *  vDSP_vtabiD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vtabiD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_S1,
  double *      __vDSP_S2,
  double *      __vDSP_C,
  vDSP_Length   __vDSP_M,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector threshold, single-precision.*/
/*
 *  vDSP_vthr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vthr(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector threshold, double-precision.*/
/*
 *  vDSP_vthrD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vthrD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector threshold with zero fill, single-precision.*/
/*
 *  vDSP_vthres()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vthres(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector threshold with zero fill, double-precision.*/
/*
 *  vDSP_vthresD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vthresD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector threshold with signed constant, single-precision.*/
/*
 *  vDSP_vthrsc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vthrsc(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  float *       __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector threshold with signed constant, double-precision.*/
/*
 *  vDSP_vthrscD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vthrscD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  double *      __vDSP_D,
  vDSP_Stride   __vDSP_L,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector tapered merge, single-precision.*/
/*
 *  vDSP_vtmerg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vtmerg(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector tapered merge, double-precision.*/
/*
 *  vDSP_vtmergD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vtmergD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  vDSP_Stride   __vDSP_J,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector trapezoidal integration, single-precision.*/
/*
 *  vDSP_vtrapz()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vtrapz(
  float *       __vDSP_A,
  vDSP_Stride   __vDSP_I,
  float *       __vDSP_B,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Vector trapezoidal integration, double-precision.*/
/*
 *  vDSP_vtrapzD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_vtrapzD(
  double *      __vDSP_A,
  vDSP_Stride   __vDSP_I,
  double *      __vDSP_B,
  double *      __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Wiener Levinson, single-precision.*/
/*
 *  vDSP_wiener()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_wiener(
  vDSP_Length   __vDSP_L,
  float *       __vDSP_A,
  float *       __vDSP_C,
  float *       __vDSP_F,
  float *       __vDSP_P,
  int           __vDSP_IFLG,
  int *         __vDSP_IERR)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Wiener Levinson, double-precision.*/
/*
 *  vDSP_wienerD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_wienerD(
  vDSP_Length   __vDSP_L,
  double *      __vDSP_A,
  double *      __vDSP_C,
  double *      __vDSP_F,
  double *      __vDSP_P,
  int           __vDSP_IFLG,
  int *         __vDSP_IERR)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



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

