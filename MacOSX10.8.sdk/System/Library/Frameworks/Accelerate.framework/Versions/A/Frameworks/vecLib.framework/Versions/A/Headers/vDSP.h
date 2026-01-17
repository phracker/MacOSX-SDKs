/*
     File:       vecLib/vDSP.h
 
     Contains:   AltiVec DSP Interfaces
 
     Version:    vecLib-380.6
 
     Copyright:  � 2000-2012 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VDSP__
#define __VDSP__

/*  For documentation on vDSP, search for "vDSP" at http://developer.apple.com,
	or search for one of the routine names below.
*/

#if defined __ppc__ || defined __i386__
#ifndef __VDSP_TRANSLATE__
#include <vecLib/vDSP_translate.h>
#endif

#endif


#include <Availability.h>

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
#define	vDSP_Version0	380
#define	vDSP_Version1	6


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
  FFTRadix      __vDSP_radix) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


/*
 *  vDSP_destroy_fftsetup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_destroy_fftsetup(FFTSetup __vDSP_setup) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTRadix      __vDSP_radix) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


/*
 *  vDSP_destroy_fftsetupD()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in vecLib.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
vDSP_destroy_fftsetupD(FFTSetupD __vDSP_setup) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length                    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection             __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection             __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection             __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection       __vDSP_direction) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection       __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  FFTDirection             __vDSP_flag) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_lenFilter) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_lenFilter) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  float *       __vDSP_result) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  double *      __vDSP_result) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  float *       __vDSP_result) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  double *      __vDSP_result) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_fnumCol) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_fnumCol) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);



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
  vDSP_Length   __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);

/* Euclidean distance square, single-precision.*/
/*
 *  vDSP_distancesq()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void 
vDSP_distancesq(
  const float   __vDSP_input1[],
  vDSP_Stride   __vDSP_stride1,
  const float   __vDSP_input2[],
  vDSP_Stride   __vDSP_stride2,
  float *       __vDSP_result,
  vDSP_Length   __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

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
  vDSP_Length   __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_lenFilter) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_lenFilter) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
	const DSPSplitComplex *__vDSP_input1, vDSP_Stride __vDSP_stride1,
	const DSPSplitComplex *__vDSP_input2, vDSP_Stride __vDSP_stride2,
	const DSPSplitComplex *__vDSP_result, vDSP_Stride __vDSP_strideResult,
	vDSP_Length __vDSP_size,
	int __vDSP_conjugate)
		__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  const DSPDoubleSplitComplex *  __vDSP_input1,
  vDSP_Stride							__vDSP_stride1,
  const DSPDoubleSplitComplex *  __vDSP_input2,
  vDSP_Stride							__vDSP_stride2,
  const DSPDoubleSplitComplex *  __vDSP_result,
  vDSP_Stride							__vDSP_strideResult,
  vDSP_Length							__vDSP_size,
  int										__vDSP_conjugate) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


/* Complex-split conjugate multiply and add, single-precision.*/
/*
 *  vDSP_zvcma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern void vDSP_zvcma(
	const DSPSplitComplex *__vDSP_input1, vDSP_Stride __vDSP_stride1,
	const DSPSplitComplex *__vDSP_input2, vDSP_Stride __vDSP_stride2,
	const DSPSplitComplex *__vDSP_input3, vDSP_Stride __vDSP_stride3,
	const DSPSplitComplex *__vDSP_result, vDSP_Stride __vDSP_strideResult,
	vDSP_Length __vDSP_size)
		__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_size) __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int           __vDSP_FLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int           __vDSP_FLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  const DSPSplitComplex *  __vDSP_A,
  vDSP_Stride					__vDSP_I,
  const DSPSplitComplex *  __vDSP_B,
  vDSP_Stride					__vDSP_J,
  const DSPSplitComplex *  __vDSP_C,
  vDSP_Stride					__vDSP_K,
  vDSP_Length					__vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  const DSPDoubleSplitComplex *  __vDSP_A,
  vDSP_Stride							__vDSP_I,
  const DSPDoubleSplitComplex *  __vDSP_B,
  vDSP_Stride							__vDSP_J,
  const DSPDoubleSplitComplex *  __vDSP_C,
  vDSP_Stride							__vDSP_K,
  vDSP_Length							__vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length        __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length              __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int           __vDSP_FLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int           __vDSP_FLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int           __vDSP_FLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int           __vDSP_FLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_TCC) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_TCC) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/* Sum of vector elements and sum of vector elements' squares,
 * single-precision.
 *
 * vDSP_sve_svesq()
 */
extern void vDSP_sve_svesq(
	const float  *__vDSP_A,
	vDSP_Stride   __vDSP_I,
	float        *__vDSP_Sum,
	float        *__vDSP_SumOfSquares,
	vDSP_Length   __vDSP_N)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);


/* Sum of vector elements and sum of vector elements' squares,
 * double-precision.
 *
 * vDSP_sve_svesqD()
 */
extern void vDSP_sve_svesqD(
	const double *__vDSP_A,
	vDSP_Stride   __vDSP_I,
	double       *__vDSP_Sum,
	double       *__vDSP_SumOfSquares,
	vDSP_Length   __vDSP_N)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);


/* Normalize elements to zero mean and unit standard deviation,
 * single-precision.
 *
 * vDSP_normalize()
 */
extern void vDSP_normalize(
	const float  *__vDSP_A,
	vDSP_Stride   __vDSP_IA,
	float        *__vDSP_C,
	vDSP_Stride   __vDSP_IC,
	float        *__vDSP_Mean,
	float        *__vDSP_StandardDeviation,
	vDSP_Length   __vDSP_N)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);


/* Normalize elements to zero mean and unit standard deviation,
 * double-precision.
 *
 * vDSP_normalize()
 */
extern void vDSP_normalizeD(
	const double *__vDSP_A,
	vDSP_Stride   __vDSP_IA,
	double       *__vDSP_C,
	vDSP_Stride   __vDSP_IC,
	double       *__vDSP_Mean,
	double       *__vDSP_StandardDeviation,
	vDSP_Length   __vDSP_N)
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length *  __vDSP_NHI) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length *  __vDSP_NHI) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  unsigned int   __vDSP_F) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  unsigned int   __vDSP_F) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length      __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length      __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length       __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length       __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length      __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length      __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length       __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length       __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length      __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length      __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length       __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length       __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  const float * __vDSP_A,
  vDSP_Stride   __vDSP_I,
  const float * __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  const float * __vDSP_A,
  vDSP_Stride   __vDSP_I,
  const float * __vDSP_B,
  vDSP_Stride   __vDSP_J,
  float *       __vDSP_C,
  vDSP_Stride   __vDSP_K,
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_M) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length    __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length     __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int           __vDSP_OFLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int           __vDSP_OFLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int            __vDSP_OFLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int            __vDSP_OFLAG) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_P) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int *         __vDSP_IERR) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


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
  int *         __vDSP_IERR) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/*	vDSP_FFT16_copv and vDSP_FFT32_copv perform 16- and 32-element FFTs on
	interleaved complex unit-stride vector-block-aligned data.

	Parameters:

		float *Output

			Pointer to space for output data (interleaved complex).  This
			address must be vector-block aligned.

		const float *Input

			Pointer to input data (interleaved complex).  This address must be
			vector-block aligned.

		FFT_Direction Direction

			Transform direction, FFT_FORWARD or FFT_INVERSE.

	These routines calculate:

		For 0 <= k < N,

			H[k] = sum(1**(S * j*k/N) * h[j], 0 <= j < N),

	where:

		N is 16 or 32, as specified by the routine name,

		h[j] is Input[2*j+0] + i * Input[2*j+1] at routine entry,

		H[j] is Output[2*j+0] + i * Output[2*j+1] at routine exit,

		S is -1 if Direction is FFT_FORWARD and +1 if Direction is FFT_INVERSE,
		and

		1**x is e**(2*pi*i*x).

	Input and Output may be equal but may not otherwise overlap.
*/
void vDSP_FFT16_copv(float *__vDSP_Output, const float *__vDSP_Input,
	FFTDirection __vDSP_Direction)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
void vDSP_FFT32_copv(float *__vDSP_Output, const float *__vDSP_Input,
	FFTDirection __vDSP_Direction)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_FFT16_zopv and vDSP_FFT32_zopv perform 16- and 32-element FFTs on
	separated complex unit-stride vector-block-aligned data.

	Parameters:

		float *Or, float *Oi

			Pointers to space for real and imaginary output data.  These
			addresses must be vector-block aligned.

		const float *Ir, *Ii

			Pointers to real and imaginary input data.  These addresses must be
			vector-block aligned.

		FFT_Direction Direction

			Transform direction, FFT_FORWARD or FFT_INVERSE.

	These routines calculate:

		For 0 <= k < N,

			H[k] = sum(1**(S * j*k/N) * h[j], 0 <= j < N),

	where:

		N is 16 or 32, as specified by the routine name,

		h[j] is Ir[j] + i * Ii[j] at routine entry,

		H[j] is Or[j] + i * Oi[j] at routine exit,

		S is -1 if Direction is FFT_FORWARD and +1 if Direction is FFT_INVERSE,
		and

		1**x is e**(2*pi*i*x).

	Or may equal Ir or Ii, and Oi may equal Ii or Ir, but the ararys may not
	otherwise overlap.
*/
void vDSP_FFT16_zopv(
	      float *__vDSP_Or,       float *__vDSP_Oi,
	const float *__vDSP_Ir, const float *__vDSP_Ii,
	FFTDirection __vDSP_Direction)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
void vDSP_FFT32_zopv(
	      float *__vDSP_Or,       float *__vDSP_Oi,
	const float *__vDSP_Ir, const float *__vDSP_Ii,
	FFTDirection __vDSP_Direction)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	How to use the Discrete Fourier Transform (DFT) interface.

	There are three steps to performing a DFT:

		Call a setup routine (e.g., vDSP_DFT_zop_CreateSetup) to get a setup
		object.

			This is a preparation step to be done when a program is starting or
			is starting some new phase (e.g., when a communication channel is
			opened).  It should never be done during real-time processing.  The
			setup routine is slow and is called only once to prepare data that
			can be used many times.

		Call an execution routine (e.g., vDSP_DFT_Execute) to perform a DFT,
		and pass it the setup object.

			The execution routine is fast (for selected cases) and is generally
			called many times.

		Call a destroy routine (e.g., vDSP_DFT_DestroySetup) to release the
		memory held by the setup object.

			This is done when a program is ending or is ending some phase.
			After calling a destroy routine, the setup data is no longer valid
			and should not be used.

	Discussion:

		The current sequences of setup, execution, destroy routines are:

			vDSP_DFT_zop_CreateSetup, vDSP_DFT_Execute, vDSP_DFT_DestroySetup;

			vDSP_DFT_zrop_CreateSetup, vDSP_DFT_Execute, vDSP_DFT_DestroySetup;
		
			vDSP_DFT_CreateSetup, vDSP_DFT_zop, vDSP_DFT_DestroySetup.

		Sharing DFT setups:

			Any setup returned by a DFT setup routine may be passed as input to
			any DFT setup routine, in the parameter named Previous.  (This
			allows the setups to share data, avoiding unnecessary duplication
			of some setup data.)  Setup routines may be executed in any order.
			Passing any setup of a group of setups sharing data will result in
			a new setup sharing data with all of the group.

			When calling an execution routine, each setup can be used only with
			its intended execution routine.  Thus the setup returned by
			vDSP_DFT_CreateSetup can only be used with vDSP_DFT_zop and not
			with vDSP_DFT_Execute.

			vDSP_DFT_DestroySetup is used to destroy any DFT setup.

		History:

			vDSP_DFT_CreateSetup and vDSP_DFT_zop are the original vDSP DFT
			routines.  vDSP_DFT_zop_CreateSetup, vDSP_DFT_zrop_CreateSetup, and
			vDSP_DFT_Execute are newer, more specialized DFT routines.  These
			newer routines do not have stride parameters (stride is one) and
			incorporate the direction parameter into the setup.  This reduces
			the number of arguments passed to the execution routine, which
			receives only the setup and four address parameters.  Additionally,
			the complex-to-complex DFT (zop) and real-to-complex DFT (zrop) use
			the same execution routine (the setup indicates which function to
			perform).

			We recommend you use vDSP_DFT_zop_CreateSetup,
			vDPS_DFT_zrop_CreateSetup, and vDSP_DFT_Execute, and that you not
			use vDSP_DFT_CreateSetup and vDSP_DFT_zop.

	Multithreading:

		Never call a setup or destroy routine in a thread when any DFT routine
		(setup, execution, or destroy) that shares setup data may be
		executing.  (This applies not just to multiple threads but also to
		calling DFT routines in signal handlers.)

		Multiple DFT execution routines may be called simultaneously.  (Their
		access to the setup data is read-only.)

		If you need to call setup and/or destroy routines while other DFT
		routines might be executing, you can either use Grand Central Dispatch
		or locks (costs time) to avoid simultaneous execution or you can create
		separate setup objects for them (costs memory).
*/


/*	A vDSP_DFT_Setup object is a pointer to a structure whose definition is
	unpublished.
*/
typedef struct vDSP_DFT_SetupStruct *vDSP_DFT_Setup;


// DFT direction may be specified as vDSP_DFT_FORWARD or vDSP_DFT_INVERSE.
typedef enum { vDSP_DFT_FORWARD = +1, vDSP_DFT_INVERSE = -1 }
	vDSP_DFT_Direction;


/*	vDSP_DFT_CreateSetup is a DFT setup routine.  It creates a setup object
	for use with the vDSP_DFT_zop execution routine.  We recommend you use
	vDSP_DFT_zop_CreateSetup instead of this routine.

	Parameters:

		vDSP_DFT_Setup Previous

			Previous is either zero or a previous DFT setup.  If a previous
			setup is passed, the new setup will share data with the previous
			setup, if feasible (and with any other setups the previous setup
			shares with).  If zero is passed, the routine will allocate and
			initialize new memory.

		vDSP_Length Length

			Length is the number of complex elements to be transformed.

	Return value:

		Zero is returned if memory is unavailable.

	The returned setup object may be used only with vDSP_DFT_zop for the length
	given during setup.  Unlike previous vDSP FFT routines, the setup may not
	be used to execute transforms with shorter lengths.

	Do not call this routine while any DFT routine sharing setup data might be
	executing.
*/
vDSP_DFT_Setup vDSP_DFT_CreateSetup(vDSP_DFT_Setup __vDSP_Previous,
	vDSP_Length __vDSP_Length)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_DFT_zop_CreateSetup is a DFT setup routine.  It creates a setup object
	for use with the vDSP_DFT_Execute execution routine, to perform a
	complex-to-complex DFT.

	Parameters:

		vDSP_DFT_Setup Previous

			Previous is either zero or a previous DFT setup.  If a previous
			setup is passed, the new setup will share data with the previous
			setup, if feasible (and with any other setups the previous setup
			shares with).  If zero is passed, the routine will allocate and
			initialize new memory.

		vDSP_Length Length

			Length is the number of complex elements to be transformed.

		vDSP_DFT_Direction Direction

			Transform direction, vDSP_DFT_FORWARD or vDSP_DFT_INVERSE.

	Return value:

		Zero is returned if memory is unavailable or if there is no
		implementation for the requested case.  Currently, the implemented
		cases are:

			Length = f * 2**n, where f is 3, 5, or 15 and 3 <= n.

		Additionally, only cases where the array addresses (passed to
		vDSP_DFT_Execute) are 16-byte aligned are optimized.

	Function:

		When vDSP_DFT_Execute is called with a setup returned from this
		routine, it calculates:

			For 0 <= k < N,

				H[k] = sum(1**(S * j*k/N) * h[j], 0 <= j < N),

		where:

			N is the length given in the setup;

			h is the array of complex numbers specified by Ir and Ii when
			vDSP_DFT_Execute is called:

				for 0 <= j < N,
					h[j] = Ir[j] + i * Ii[j];

			H is the array of complex numbers specified by Or and Oi when
			vDSP_DFT_Execute returns:

				for 0 <= k < N,
					H[k] = Or[k] + i * Oi[k];

			S is -1 if Direction is vDSP_DFT_FORWARD and +1 if Direction is
			vDSP_DFT_INVERSE; and

			1**x is e**(2*pi*i*x).

	Performance:

		Performance is good for these cases:

			All addresses are 16-byte aligned, and the length is f * 2**n,
			where f is 3, 5, or 15 and 3 <= n.

		Performance is extremely slow for all other cases.

	In-Place Operation:

		For the cases with good performance as described above, Or may equal Ir
		and Oi may equal Ii (in the call to vDSP_DFT_Execute).  Otherwise, no
		overlap of Or, Oi, Ir, and Ii is supported.

	The returned setup object may be used only with vDSP_DFT_Execute for the
	length given during setup.  Unlike previous vDSP FFT routines, the setup
	may not be used to execute transforms with shorter lengths.

	Do not call this routine while any DFT routine sharing setup data might be
	executing.
*/
vDSP_DFT_Setup vDSP_DFT_zop_CreateSetup(vDSP_DFT_Setup __vDSP_Previous,
	vDSP_Length __vDSP_Length, vDSP_DFT_Direction __vDSP_Direction)
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_0);


/*	vDSP_DFT_zrop_CreateSetup is a DFT setup routine.  It creates a setup
	object for use with the vDSP_DFT_Execute execution routine, to perform a
	real-to-complex DFT or a complex-to-real DFT.

	Parameters:

		vDSP_DFT_Setup Previous

			Previous is either zero or a previous DFT setup.  If a previous
			setup is passed, the new setup will share data with the previous
			setup, if feasible (and with any other setups the previous setup
			shares with).  If zero is passed, the routine will allocate and
			initialize new memory.

		vDSP_Length Length

			Length is the number of real elements to be transformed (in a a
			forward, real-to-complex transform) or produced (in a reverse,
			complex-to-real transform).  Length must be even.

		vDSP_DFT_Direction Direction

			Transform direction, vDSP_DFT_FORWARD or vDSP_DFT_INVERSE.

	Return value:

		Zero is returned if memory is unavailable or if there is no
		implementation for the requested case.  Currently, the implemented
		cases are:

			Length = f * 2**n, where f is 3, 5, or 15 and 4 <= n.

		Additionally, only cases where the array addresses (passed to
		vDSP_DFT_Execute) are 16-byte aligned are optimized.

	Function:

		When vDSP_DFT_Execute is called with a setup returned from this
		routine, it calculates:

			For 0 <= k < N,

				H[k] = C * sum(1**(S * j*k/N) * h[j], 0 <= j < N),

		where:

			N is the Length given in the setup;

			h is the array of numbers specified by Ir and Ii when
			vDSP_DFT_Execute is called (see "Data Layout" below);

			H is the array of numbers specified by Or and Oi when
			vDSP_DFT_Execute returns (see "Data Layout" below);

			C is 2 if Direction is vDSP_DFT_FORWARD and 1 if Direction is
			vDSP_DFT_INVERSE;

			S is -1 if Direction is vDSP_DFT_FORWARD and +1 if Direction is
			vDSP_DFT_INVERSE; and

			1**x is e**(2*pi*i*x).

		Data Layout:

			If Direction is vDSP_DFT_FORWARD, then:

				h is an array of real numbers, with its even-index elements
				stored in Ir and its odd-index elements stored in Ii:

					For 0 <= j < N/2,
						h[2*j+0] = Ir[j], and
						h[2*j+1] = Ii[j].

				H is an array of complex numbers, stored in Or and Oi:

					H[0  ] = Or[0].  (H[0  ] is pure real.)
					H[N/2] = Oi[0].  (H[N/2] is pure real.)
					For 1 < k < N/2,
						H[k] = Or[k] + i * Oi[k].

				For N/2 < k < N, H[k] is not explicitly stored in memory but is
				known because it necessarily equals the conjugate of H[N-k],
				which is stored as described above.

			If Direction is vDSP_DFT_Inverse, then the layouts of the input and
			output arrays are swapped.  Ir and Ii describe an input array with
			complex elements laid out as described above for Or and Oi.  When
			vDSP_DFT_Execute returns, Or and Oi contain a pure real array, with
			its even-index elements stored in Or and its odd-index elements in
			Oi.

	Performance:

		Performance is good for these cases:

			All addresses are 16-byte aligned, and the length is f * 2**n,
			where f is 3, 5, or 15 and 4 <= n.

		Performance is extremely slow for all other cases.

	In-Place Operation:

		For the cases with good performance as described above, Or may equal Ir
		and Oi may equal Ii (in the call to vDSP_DFT_Execute).  Otherwise, no
		overlap of Or, Oi, Ir, and Ii is supported.

	The returned setup object may be used only with vDSP_DFT_Execute for the
	length given during setup.  Unlike previous vDSP FFT routines, the setup
	may not be used to execute transforms with shorter lengths.

	Do not call this routine while any DFT routine sharing setup data might be
	executing.
*/
vDSP_DFT_Setup vDSP_DFT_zrop_CreateSetup(vDSP_DFT_Setup __vDSP_Previous,
	vDSP_Length __vDSP_Length, vDSP_DFT_Direction __vDSP_Direction)
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_0);


/*	vDSP_DFT_DestroySetup is a DFT destroy routine.  It releases the memory
	used by a setup object.

	Parameters:

		vDSP_DFT_Setup Setup

			Setup is the setup object to be released.  The object may have
			been previously allocated with any DFT setup routine, such as
			vDSP_DFT_zop_CreateSetup or vDSP_DFT_zrop_CreateSetup.

	Destroying a setup with shared data is safe; it will release only memory
	not needed by other undestroyed setups.  Memory (and the data it contains)
	is freed only when all setup objects using it have been destroyed.

	Do not call this routine while any DFT routine sharing setup data might be
	executing.
*/
void vDSP_DFT_DestroySetup(vDSP_DFT_Setup __vDSP_Setup)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_DFT_zop is a DFT execution routine.  It performs a DFT, with the aid
	of previously created setup data.

	Parameters:

		vDSP_DFT_Setup Setup

			A setup object returned by a previous call to
			vDSP_DFT_zop_CreateSetup.

		const float *Ir
		const float *Ii

			Pointers to real and imaginary components of input data.

		vDSP_Stride Is

			The number of physical elements from one logical input element to
			the next.

		float *Or
		float *Oi

			Pointers to space for real and imaginary components of output
			data.

			The input and output arrays may not overlap except as specified
			in "In-Place Operation", below.

		vDSP_Stride Os

			The number of physical elements from one logical output element to
			the next.

		vDSP_DFT_Direction Direction

			Transform direction, vDSP_DFT_FORWARD or vDSP_DFT_INVERSE.

	Observe there is no separate length parameter.  The length is passed via
	the setup object.

	Performance:

		Performance is good for these cases:

			All addresses are 16-byte aligned, all strides are one, and the
			length is f * 2**n, where f is 3, 5, or 15 and 3 <= n.

		Performance is extremely slow for all other cases.

	In-Place Operation:

		For the cases with good performance as described above, Or may equal Ir
		and Oi may equal Ii.  Otherwise, no overlap of Or, Oi, Ir, and Ii is
		supported.

	This routine calculates:

		For 0 <= k < N,

			H[k] = sum(1**(S * j*k/N) * h[j], 0 <= j < N),

	where:

		N is the length given in the setup,

		h is the array of complex numbers specified by Ir, Ii, and Is at
		routine entry:

			h[j] = Ir[j*Is] + i * Ii[j*Is],
			for 0 <= j < N,

		H is the array of complex numbers stored as specified by Or, Oi, and Os
		at routine exit:

			H[k] = Or[k*Os] + i * Oi[k*Os],
			for 0 <= k < N,

		S is -1 if Direction is vDSP_DFT_FORWARD and +1 if Direction is
		vDSP_DFT_INVERSE, and

		1**x is e**(2*pi*i*x).

	Do not call this routine while any DFT setup or destroy routine sharing
	setup data might be executing.
*/
void vDSP_DFT_zop(
	const struct vDSP_DFT_SetupStruct *__vDSP_Setup,
	const float *__vDSP_Ir, const float *__vDSP_Ii, vDSP_Stride __vDSP_Is,
	      float *__vDSP_Or,       float *__vDSP_Oi, vDSP_Stride __vDSP_Os,
	vDSP_DFT_Direction __vDSP_Direction)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_DFT_Execute is a DFT execution routine.  It performs a DFT, with the
	aid of previously created setup data.

	Parameters:

		vDSP_DFT_Setup Setup

			A setup object returned by a previous call to
			vDSP_DFT_zop_CreateSetup or vDSP_DFT_zrop_CreateSetup.

		const float *Ir
		const float *Ii

			Pointers to input data.

		float *Or
		float *Oi

			Pointers to output data.

			The input and output arrays may not overlap except as specified
			in "In-Place Operation", below.

	Performance and In-Place Operation:

		See notes for the setup routine for the operation being executed.

	Function:

		The function performed by this routine is determined by the setup
		passed to it.  The documentation for the routine used to create the
		setup describes the function.

		Note that different numbers of elements are required when this routine
		is called, depending on the setup used:

			When the setup is from vDSP_zop_CreateSetup, each array (Ir, Ii,
			Or, and Oi) must have Length elements.

			When the setup is from vDSP_zrop_CreateSetup, each array (Ir, Ii,
			Or, and Oi) must have Length/2 elements.

	Do not call this routine while any DFT setup or destroy routine sharing
	setup data might be executing.
*/
void vDSP_DFT_Execute(
	const struct vDSP_DFT_SetupStruct *__vDSP_Setup,
	const float *__vDSP_Ir,  const float *__vDSP_Ii,
	      float *__vDSP_Or,        float *__vDSP_Oi)
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_0);


/*	vDSP_dotpr2, vector single-precision stereo dot product.

	Function:

		This routine calculates the dot product of A0 with B and the dot
		product of A1 with B.  This is functionally equivalent to calculating
		two dot products but might execute faster.

		In pseudocode, the operation is:

			sum0 = 0;
			sum1 = 0;
			for (i = 0; i < Length; ++i)
			{
				sum0 += A0[i*A0Stride] * B[i*BStride];
				sum1 += A1[i*A1Stride] * B[i*BStride];
			}
			*C0 = sum0;
			*C1 = sum1;

	Input:

		const float *A0, vDSP_Stride A0Stride.

			Starting address and stride for input vector A0.

		const float *A1, vDSP_Stride A1Stride.

			Starting address and stride for input vector A1.

		const float *B,  vDSP_Stride BStride.

			Starting address and stride for input vector B.

		float *C0.

			Address for dot product of A0 and B.

		float *C1.

			Address for dot product of A1 and B.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to *C0 and *C1.
*/
void vDSP_dotpr2(
	const float *__vDSP_A0, vDSP_Stride __vDSP_A0Stride,
	const float *__vDSP_A1, vDSP_Stride __vDSP_A1Stride,
	const float *__vDSP_B,  vDSP_Stride __vDSP_BStride,
	float *__vDSP_C0,
	float *__vDSP_C1,
	vDSP_Length __vDSP_Length)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_dotpr_s1_15, vector integer 1.15 format dot product.

	Function:

		This routine calculates the dot product of A with B.

		In pseudocode, the operation is:

			sum = 0;
			for (i = 0; i < N; ++i)
			{
				sum0 += A[i*AStride] * B[i*BStride];
			}
			*C = sum;

	The elements are fixed-point numbers, each with one sign bit and 15
	fraction bits.  Where the value of the short int is normally x, it is
	x/32768 for the purposes of this routine.

	Input:

		const short int *A, vDSP_Stride AStride.

			Starting address and stride for input vector A.

		const short int *B,  vDSP_Stride BStride.

			Starting address and stride for input vector B.

		short int *C.

			Address for dot product of A and B.

		vDSP_Length N.

			Number of elements in each vector.

	Output:

		The result is written to *C.
*/
void vDSP_dotpr_s1_15(
	const short int *__vDSP_A, vDSP_Stride __vDSP_AStride,
	const short int *__vDSP_B, vDSP_Stride __vDSP_BStride,
	short int *__vDSP_C,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_dotpr2_s1_15, vector integer 1.15 format stereo dot product.

	Function:

		This routine calculates the dot product of A0 with B and the dot
		product of A1 with B.  This is functionally equivalent to calculating
		two dot products but might execute faster.

		In pseudocode, the operation is:

			sum0 = 0;
			sum1 = 0;
			for (i = 0; i < N; ++i)
			{
				sum0 += A0[i*A0Stride] * B[i*BStride];
				sum1 += A1[i*A1Stride] * B[i*BStride];
			}
			*C0 = sum0;
			*C1 = sum1;

	The elements are fixed-point numbers, each with one sign bit and 15
	fraction bits.  Where the value of the short int is normally x, it is
	x/32768 for the purposes of this routine.

	Input:

		const short int *A0, vDSP_Stride A0Stride.

			Starting address and stride for input vector A0.

		const short int *A1, vDSP_Stride A1Stride.

			Starting address and stride for input vector A1.

		const short int *B,  vDSP_Stride BStride.

			Starting address and stride for input vector B.

		short int *C0.

			Address for dot product of A0 and B.

		short int *C1.

			Address for dot product of A1 and B.

		vDSP_Length N.

			Number of elements in each vector.

	Output:

		The results are written to *C0 and *C1.
*/
void vDSP_dotpr2_s1_15(
	const short int *__vDSP_A0, vDSP_Stride __vDSP_A0Stride,
	const short int *__vDSP_A1, vDSP_Stride __vDSP_A1Stride,
	const short int *__vDSP_B,  vDSP_Stride __vDSP_BStride,
	short int *__vDSP_C0,
	short int *__vDSP_C1,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_dotpr_s8_24, vector integer 8.24 format dot product.

	Function:

		This routine calculates the dot product of A with B.

		In pseudocode, the operation is:

			sum = 0;
			for (i = 0; i < N; ++i)
			{
				sum0 += A[i*AStride] * B[i*BStride];
			}
			*C = sum;

	The elements are fixed-point numbers, each with eight integer bits
	(including sign) and 24 fraction bits.  Where the value of the int is
	normally x, it is x/16777216 for the purposes of this routine.

	Input:

		const int *A, vDSP_Stride AStride.

			Starting address and stride for input vector A.

		const int *B,  vDSP_Stride BStride.

			Starting address and stride for input vector B.

		int *C.

			Address for dot product of A and B.

		vDSP_Length N.

			Number of elements in each vector.

	Output:

		The result is written to *C.
*/
void vDSP_dotpr_s8_24(
	const int *__vDSP_A, vDSP_Stride __vDSP_AStride,
	const int *__vDSP_B, vDSP_Stride __vDSP_BStride,
	int *__vDSP_C,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_dotpr2_s8_24, vector integer 8.24 format stereo dot product.

	Function:

		This routine calculates the dot product of A0 with B and the dot
		product of A1 with B.  This is functionally equivalent to calculating
		two dot products but might execute faster.

		In pseudocode, the operation is:

			sum0 = 0;
			sum1 = 0;
			for (i = 0; i < N; ++i)
			{
				sum0 += A0[i*A0Stride] * B[i*BStride];
				sum1 += A1[i*A1Stride] * B[i*BStride];
			}
			*C0 = sum0;
			*C1 = sum1;

	The elements are fixed-point numbers, each with eight integer bits
	(including sign) and 24 fraction bits.  Where the value of the int is
	normally x, it is x/16777216 for the purposes of this routine.

	Input:

		const int *A0, vDSP_Stride A0Stride.

			Starting address and stride for input vector A0.

		const int *A1, vDSP_Stride A1Stride.

			Starting address and stride for input vector A1.

		const int *B,  vDSP_Stride BStride.

			Starting address and stride for input vector B.

		int *C0.

			Address for dot product of A0 and B.

		int *C1.

			Address for dot product of A1 and B.

		vDSP_Length N.

			Number of elements in each vector.

	Output:

		The results are written to *C0 and *C1.
*/
void vDSP_dotpr2_s8_24(
	const int *__vDSP_A0, vDSP_Stride __vDSP_A0Stride,
	const int *__vDSP_A1, vDSP_Stride __vDSP_A1Stride,
	const int *__vDSP_B,  vDSP_Stride __vDSP_BStride,
	int *__vDSP_C0,
	int *__vDSP_C1,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);



/*	vDSP_vrampmul, vector single-precision vramp and multiply.

	This routine puts into O the product of I and a ramp function with initial
	value *Start and slope *Step.  *Start is updated to continue the ramp
	in a consecutive call.  To continue the ramp smoothly, the new value of
	*Step includes rounding errors accumulated during the routine rather than
	being calculated directly as *Start + N * *Step.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O[i*OS] = *Start * I[i*IS];
			*Start += *Step;
		}

	Input:

		const float *I, vDSP_Stride IS.

			Starting address and stride for the input vector.

		float *Start.

			Starting value for the ramp.

		const float *Step.

			Value of the step for the ramp.

		float *O, vDSP_Stride *OS.

			Starting address and stride for the output vector.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to O.

		On return, *Start contains initial *Start + N * *Step.
*/
void vDSP_vrampmul(
	const float *__vDSP_I, vDSP_Stride __vDSP_IS,
	float *__vDSP_Start,
	const float *__vDSP_Step,
	float *__vDSP_O, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmuladd, vector single-precision vramp, multiply and add.

	This routine adds to O the product of I and a ramp function with initial
	value *Start and slope *Step.  *Start is updated to continue the ramp in a
	consecutive call.  To continue the ramp smoothly, the new value of *Step
	includes rounding errors accumulated during the routine rather than being
	calculated directly as *Start + N * *Step.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O[i*OS] += *Start * I[i*IS];
			*Start += *Step;
		}

	Input:

		const float *I, vDSP_Stride IS.

			Starting address and stride for the input vector.

		float *Start.

			Starting value for the ramp.

		const float *Step.

			Value of the step for the ramp.

		float *O, vDSP_Stride *OS.

			Starting address and stride for the output vector.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are added to O.

		On return, *Start contains initial *Start + N * *Step.
*/
void vDSP_vrampmuladd(
	const float *__vDSP_I, vDSP_Stride __vDSP_IS,
	float *__vDSP_Start,
	const float *__vDSP_Step,
	float *__vDSP_O, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmul2, stereo vector single-precision vramp and multiply.

	This routine:

		Puts into O0 the product of I0 and a ramp function with initial value
		*Start and slope *Step.

		Puts into O1 the product of I1 and a ramp function with initial value
		*Start and slope *Step.

	*Start is updated to continue the ramp in a consecutive call.  To continue
	the ramp smoothly, the new value of *Step includes rounding errors
	accumulated during the routine rather than being calculated directly as
	*Start + N * *Step.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O0[i*OS] = *Start * I0[i*IS];
			O1[i*OS] = *Start * I1[i*IS];
			*Start += *Step;
		}

	Input:

		const float *I0, const float *I1, vDSP_Stride IS.

			Starting addresses of both inputs and stride for the input vectors.

		float *Start.

			Starting value for the ramp.

		const float *Step.

			Value of the step for the ramp.

		float *O0, float *O1, vDSP_Stride *OS.

			Starting addresses of both outputs and stride for the output vectors.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to O0 and O1.

		On return, *Start contains initial *Start + N * *Step.
*/
void vDSP_vrampmul2(
	const float *__vDSP_I0, const float *__vDSP_I1, vDSP_Stride __vDSP_IS,
	float *__vDSP_Start,
	const float *__vDSP_Step,
	float *__vDSP_O0, float *__vDSP_O1, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmuladd2, stereo vector single-precision vramp, multiply and add.

	This routine:

		Adds to O0 the product of I0 and a ramp function with initial value
		*Start and slope *Step.

		Adds to O1 the product of I1 and a ramp function with initial value
		*Start and slope *Step.

	*Start is updated to continue the ramp in a consecutive call.  To continue
	the ramp smoothly, the new value of *Step includes rounding errors
	accumulated during the routine rather than being calculated directly as
	*Start + N * *Step.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O0[i*OS] += *Start * I0[i*IS];
			O1[i*OS] += *Start * I1[i*IS];
			*Start += *Step;
		}

	Input:

		const float *I0, const float *I1, vDSP_Stride IS.

			Starting addresses of both inputs and stride for the input vectors.

		float *Start.

			Starting value for the ramp.

		const float *Step.

			Value of the step for the ramp.

		float *O0, float *O1, vDSP_Stride *OS.

			Starting addresses of both outputs and stride for the output vectors.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to O0 and O1.

		On return, *Start contains initial *Start + N * *Step.
*/
void vDSP_vrampmuladd2(
	const float *__vDSP_I0, const float *__vDSP_I1, vDSP_Stride __vDSP_IS,
	float *__vDSP_Start,
	const float *__vDSP_Step,
	float *__vDSP_O0, float *__vDSP_O1, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmul_s1_15, vector integer 1.15 format vramp and multiply.

	This routine puts into O the product of I and a ramp function with initial
	value *Start and slope *Step.  *Start is updated to continue the ramp
	in a consecutive call.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O[i*OS] = *Start * I[i*IS];
			*Start += *Step;
		}

	The elements are fixed-point numbers, each with one sign bit and 15
	fraction bits.  Where the value of the short int is normally x, it is
	x/32768 for the purposes of this routine.

	Input:

		const short int *I, vDSP_Stride IS.

			Starting address and stride for the input vector.

		short int *Start.

			Starting value for the ramp.

		const short int *Step.

			Value of the step for the ramp.

		short int *O, vDSP_Stride *OS.

			Starting address and stride for the output vector.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to O.

		On return, *Start contains initial *Start + N * *Step.
*/
void vDSP_vrampmul_s1_15(
	const short int *__vDSP_I, vDSP_Stride __vDSP_IS,
	short int *__vDSP_Start,
	const short int *__vDSP_Step,
	short int *__vDSP_O, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmuladd_s1_15, vector integer 1.15 format vramp, multiply and add.

	This routine adds to O the product of I and a ramp function with initial
	value *Start and slope *Step.  *Start is updated to continue the ramp in a
	consecutive call.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O[i*OS] += *Start * I[i*IS];
			*Start += *Step;
		}

	The elements are fixed-point numbers, each with one sign bit and 15
	fraction bits.  Where the value of the short int is normally x, it is
	x/32768 for the purposes of this routine.

	Input:

		const short int *I, vDSP_Stride IS.

			Starting address and stride for the input vector.

		short int *Start.

			Starting value for the ramp.

		const short int *Step.

			Value of the step for the ramp.

		short int *O, vDSP_Stride *OS.

			Starting address and stride for the output vector.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are added to O.

		On return, *Start contains initial *Start + N * *Step.
*/
void vDSP_vrampmuladd_s1_15(
	const short int *__vDSP_I, vDSP_Stride __vDSP_IS,
	short int *__vDSP_Start,
	const short int *__vDSP_Step,
	short int *__vDSP_O, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmul2_s1_15, stereo vector integer 1.15 format vramp and multiply.

	This routine:

		Puts into O0 the product of I0 and a ramp function with initial value
		*Start and slope *Step.

		Puts into O1 the product of I1 and a ramp function with initial value
		*Start and slope *Step.

	*Start is updated to continue the ramp in a consecutive call.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O0[i*OS] = *Start * I0[i*IS];
			O1[i*OS] = *Start * I1[i*IS];
			*Start += *Step;
		}

	The elements are fixed-point numbers, each with one sign bit and 15
	fraction bits.  Where the value of the short int is normally x, it is
	x/32768 for the purposes of this routine.

	Input:

		const short int *I0, const short int *I1, vDSP_Stride IS.

			Starting addresses of both inputs and stride for the input vectors.

		short int *Start.

			Starting value for the ramp.

		const short int *Step.

			Value of the step for the ramp.

		short int *O0, short int *O1, vDSP_Stride *OS.

			Starting addresses of both outputs and stride for the output vectors.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to O0 and O1.

		On return, *Start contains initial *Start + N * *Step.

*/
void vDSP_vrampmul2_s1_15(
	const short int *__vDSP_I0, const short int *__vDSP_I1, vDSP_Stride __vDSP_IS,
	short int *__vDSP_Start,
	const short int *__vDSP_Step,
	short int *__vDSP_O0, short int *__vDSP_O1, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmuladd2_s1_15, stereo vector integer 1.15 format vramp, multiply
	and add.

	This routine:

		Adds to O0 the product of I0 and a ramp function with initial value
		*Start and slope *Step.

		Adds to O1 the product of I1 and a ramp function with initial value
		*Start and slope *Step.

	*Start is updated to continue the ramp in a consecutive call.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O0[i*OS] += *Start * I0[i*IS];
			O1[i*OS] += *Start * I1[i*IS];
			*Start += *Step;
		}

	The elements are fixed-point numbers, each with one sign bit and 15
	fraction bits.  Where the value of the short int is normally x, it is
	x/32768 for the purposes of this routine.

	Input:

		const short int *I0, const short int *I1, vDSP_Stride IS.

			Starting addresses of both inputs and stride for the input vectors.

		short int *Start.

			Starting value for the ramp.

		const short int *Step.

			Value of the step for the ramp.

		short int *O0, short int *O1, vDSP_Stride *OS.

			Starting addresses of both outputs and stride for the output vectors.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are added to O0 and O1.

		On return, *Start contains initial *Start + N * *Step.

*/
void vDSP_vrampmuladd2_s1_15(
	const short int *__vDSP_I0, const short int *__vDSP_I1, vDSP_Stride __vDSP_IS,
	short int *__vDSP_Start,
	const short int *__vDSP_Step,
	short int *__vDSP_O0, short int *__vDSP_O1, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmul_s8_24, vector integer 8.24 format vramp and multiply.

	This routine puts into O the product of I and a ramp function with initial
	value *Start and slope *Step.  *Start is updated to continue the ramp
	in a consecutive call.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O[i*OS] = *Start * I[i*IS];
			*Start += *Step;
		}

	The elements are fixed-point numbers, each with eight integer bits
	(including sign) and 24 fraction bits.  Where the value of the int is
	normally x, it is x/16777216 for the purposes of this routine.

	Input:

		const int *I, vDSP_Stride IS.

			Starting address and stride for the input vector.

		int *Start.

			Starting value for the ramp.

		const int *Step.

			Value of the step for the ramp.

		int *O, vDSP_Stride *OS.

			Starting address and stride for the output vector.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to O.

		On return, *Start contains initial *Start + N * *Step.
*/
void vDSP_vrampmul_s8_24(
	const int *__vDSP_I, vDSP_Stride __vDSP_IS,
	int *__vDSP_Start,
	const int *__vDSP_Step,
	int *__vDSP_O, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmuladd_s8_24, vector integer 8.24 format vramp, multiply and add.

	This routine adds to O the product of I and a ramp function with initial
	value *Start and slope *Step.  *Start is updated to continue the ramp in a
	consecutive call.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O[i*OS] += *Start * I[i*IS];
			*Start += *Step;
		}

	The elements are fixed-point numbers, each with eight integer bits
	(including sign) and 24 fraction bits.  Where the value of the int is
	normally x, it is x/16777216 for the purposes of this routine.

	Input:

		const int *I, vDSP_Stride IS.

			Starting address and stride for the input vector.

		int *Start.

			Starting value for the ramp.

		const int *Step.

			Value of the step for the ramp.

		int *O, vDSP_Stride *OS.

			Starting address and stride for the output vector.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are added to O.

		On return, *Start contains initial *Start + N * *Step.
*/
void vDSP_vrampmuladd_s8_24(
	const int *__vDSP_I, vDSP_Stride __vDSP_IS,
	int *__vDSP_Start,
	const int *__vDSP_Step,
	int *__vDSP_O, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmul2_s8_24, stereo vector integer 8.24 format vramp and multiply.

	This routine:

		Puts into O0 the product of I0 and a ramp function with initial value
		*Start and slope *Step.

		Puts into O1 the product of I1 and a ramp function with initial value
		*Start and slope *Step.

	*Start is updated to continue the ramp in a consecutive call.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O0[i*OS] = *Start * I0[i*IS];
			O1[i*OS] = *Start * I1[i*IS];
			*Start += *Step;
		}

	The elements are fixed-point numbers, each with eight integer bits
	(including sign) and 24 fraction bits.  Where the value of the int is
	normally x, it is x/16777216 for the purposes of this routine.

	Input:

		const int *I0, const int *I1, vDSP_Stride IS.

			Starting addresses of both inputs and stride for the input vectors.

		int *Start.

			Starting value for the ramp.

		const int *Step.

			Value of the step for the ramp.

		int *O0, int *O1, vDSP_Stride *OS.

			Starting addresses of both outputs and stride for the output vectors.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to O0 and O1.

		On return, *Start contains initial *Start + N * *Step.

*/
void vDSP_vrampmul2_s8_24(
	const int *__vDSP_I0, const int *__vDSP_I1, vDSP_Stride __vDSP_IS,
	int *__vDSP_Start,
	const int *__vDSP_Step,
	int *__vDSP_O0, int *__vDSP_O1, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);


/*	vDSP_vrampmuladd2_s8_24, stereo vector integer 8.24 format vramp, multiply
	and add.

	This routine:

		Adds to O0 the product of I0 and a ramp function with initial value
		*Start and slope *Step.

		Adds to O1 the product of I1 and a ramp function with initial value
		*Start and slope *Step.

	*Start is updated to continue the ramp in a consecutive call.

	This routine calculates:

		for (i = 0; i < N; ++i)
		{
			O0[i*OS] += *Start * I0[i*IS];
			O1[i*OS] += *Start * I1[i*IS];
			*Start += *Step;
		}

	The elements are fixed-point numbers, each with eight integer bits
	(including sign) and 24 fraction bits.  Where the value of the int is
	normally x, it is x/16777216 for the purposes of this routine.

	Input:

		const int *I0, const int *I1, vDSP_Stride IS.

			Starting addresses of both inputs and stride for the input vectors.

		int *Start.

			Starting value for the ramp.

		const int *Step.

			Value of the step for the ramp.

		int *O0, int *O1, vDSP_Stride *OS.

			Starting addresses of both outputs and stride for the output vectors.

		vDSP_Length Length.

			Number of elements in each vector.

	Output:

		The results are written to O0 and O1.

		On return, *Start contains initial *Start + N * *Step.

*/
void vDSP_vrampmuladd2_s8_24(
	const int *__vDSP_I0, const int *__vDSP_I1, vDSP_Stride __vDSP_IS,
	int *__vDSP_Start,
	const int *__vDSP_Step,
	int *__vDSP_O0, int *__vDSP_O1, vDSP_Stride __vDSP_OS,
	vDSP_Length __vDSP_N)
		__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);



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

