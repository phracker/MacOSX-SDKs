/*
    File:       vecLib/vDSP.h

    Contains:   AltiVec DSP Interfaces

    Version:    vecLib-423.32

    Copyright:  � 2000-2013 by Apple Computer, Inc., all rights reserved.

    For vDSP documentation, search for "vDSP" at <http://developer.apple.com>
    or search for one of the routine names below.

    Some documentation for vDSP routines is provided below.

    To report bugs, please use <http://developer.apple.com/bugreporter>.
*/
#ifndef __VDSP__
#define __VDSP__


// Tell compiler this file is idempotent (no need to process it more than once).
#if PRAGMA_ONCE
#pragma once
#endif


/*  Documentation conventions:

        Many of the routines below are documented with C-like pseudocode that
        describes what they do.  For example, vDSP_vadd is declared with:

            extern void vDSP_vadd(
                const float *__vDSP_A,
                vDSP_Stride  __vDSP_IA,
                const float *__vDSP_B,
                vDSP_Stride  __vDSP_IB,
                float       *__vDSP_C,
                vDSP_Stride  __vDSP_IC,
                vDSP_Length  __vDSP_N)
                    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);

        and is described with:

            for (n = 0; n < N; ++n)
                C[n] = A[n] + B[n];

        The pseudocode uses two important simplifications:

            Names are shorted.

                The prefix "__vDSP_" is removed.  This prefix is used in this
                header file so that Apple parameter names do not conflict with
                other developer macro names that might be used in source files
                that include this header, as when a program might use "#define
                N 1024" to set a preprocessor macro "N" to expand to "1024".

            Vectors are simplified by omitting strides.

                The parameters A and IA (with the prefix omitted) represent a
                vector with its elements at memory locations A[i*IA], for
                appropriate values of i.  In the pseudocode, the stride IA
                is omitted; the vector is treated as a simple mathematical
                vector with elements A[i].

                This default map is assumed for all vDSP routines unless stated
                otherwise.  An array without a stride parameter has unit
                stride.  Some routines have more complicated maps.  These are
                documented with each routine.

    Default maps:

        These default maps are used unless documented otherwise for a routine.
        For real vectors:

            Pseudocode:     Memory:
            C[n]            C[n*IC]

        For complex vectors:

            Pseudocode:     Memory:
            C[n]            C->realp[n*IC] + i * C->imagp[n*IC]

        Observe that C[n] in the pseudocode is a complex number, with a real
        component and an imaginary component.


    Pseudocode:

        The pseudo-code used to describe routines is largely C with some
        additions:

            e, pi, and i are the usual mathematical constants, approximately
            2.71828182845, 3.1415926535, and sqrt(-1).

            "**" is exponentiation.  3**4 is 81.

            Re and Im are the real and imaginary parts of a complex number.
            Re(3+4*i) is 3, and Im(3+4*i) is 4.

            sum(f(j), 0 <= j < N) is the sum of f(j) evaluated for each integer
            j from 0 (inclusive) to N (exclusive).  sum(j**2, 0 <= j < 4) is
            0 + 1 + 4 + 9 = 14.  Multiple dimensions may be used.  Thus,
            sum(f(j, k), 0 <= j < M, 0 <= k < N) is the sum of f(j, k)
            evaluated for each pair of integers (j, k) satisfying the
            constraints.

            conj(z) is the complex conjugate of z (the imaginary part is
            negated).

            |x| is the absolute value of x.

    Exactness:

        vDSP routines are not expected to produce results identical to the
        pseudo-code in the descriptions, because vDSP routines are free to
        rearrange calculations for better performance.  These rearrangements
        are mathematical identities, so they would produce identical results
        if exact arithmetic were used.  However, floating-point arithmetic
        is approximate, and the rounding errors will often be different when
        operations are rearranged.

    Const:

        vDSP does not modify the contents of input arrays (including input
        scalars passed by address).  If the specification of a routine does not
        state that it alters the memory that a parameter points to, then the
        routine does not alter that memory through that parameter.  (It may of
        course alter the same memory if it is also pointed to by an output
        parameter.  Such in-place operation is permitted for some vDSP routines
        and not for others.)

        Unfortunately, C semantics make it impractical to add "const" to
        pointers inside structs, because such structs are type-incompatible
        with structs containing pointers that are not const.  Thus, vDSP
        routines with complex parameters accept those parameters via
        DSPSplitComplex and DSPDoubleSplitComplex structs (among other types)
        and not via const versions of those structures.

    Strides:

        (Note:  This section introduces strides.  For an issue using strides
        with complex data, see "Complex strides" below.)

        Many vDSP routines use strides, which specify that the vector operated
        on is embedded in a larger array in memory.  Consider an array A of
        1024 elements.  Then:

            Passing a vDSP routine:     Says to operate on:

            Address A and stride 1      Each element A[j]

            Address A and stride 2      Every other element, A[j*2]

            Address A+1 and stride 2    Every other element, starting
                                        with A[1], so A[j*2+1]

        Strides may be used to operate on columns of multi-dimensional arrays.
        For example, consider a 32*64 element array, A[32][64].  Then passing
        address A+13 and stride 64 instructs vDSP to operate on the elements of
        column 13.

        When strides are used, generally there is some accompanying parameter
        that specifies the length of the operation.  This length is typically
        the number of elements to be processed, not the number in the larger
        array.  (Some vDSP routines have interactions between parameters so
        that the length may specify some number of output elements but requires
        a different numbe of input elements.  This is documented with each
        routine.)

    Complex strides:

        Strides with complex data (interleaved complex data, not split
        complex data) are complicated by a legacy issue.  Originally, complex
        data was regarded as an array of individual elements, so that memory
        containing values to represent complex numbers 2 + 3i, 4 + 5i, 6 + 7i,
        and so on, contained individual floating-point elements:

            A[0] A[1] A[2] A[3] A[4] A[5]…
             2    3    4    5    6    7  …

        This arrangement was said to have a stride of two, indicating that a
        new complex number starts every two elements.  In the modern view, we
        would regard this as an array of struct with a stride of one struct.
        Unfortunately, the vDSP interface is bound by requirements of backward
        compatibility and must retain the original use.

        Adding to this issue, a parameter is declared as a pointer to DSPComplex
        or DSPDoubleComplex (both structures of two floating-point elements),
        but its stride is still passed as a stride of floating-point elements.
        This means that, in C, to refer to complex element i of a vector C with
        stride IC, you must divide the stride by 2, using C[i*IC/2].
        Essentially, the floating-point element stride passed to the vDSP
        routine, IA, should be twice the complex-number struct stride.
*/


// For i386, translate new names to legacy names.
#if defined __i386__ && !defined __vDSP_TRANSLATE__
#include <vecLib/vDSP_translate.h>
#endif


#include <Availability.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#pragma options align=power


/*  These symbols describe the vecLib version associated with this header.

    vDSP_Version0 is a major version number.
    vDSP_Version1 is a minor version number.
*/
#define vDSP_Version0   423
#define vDSP_Version1   32


/*  Define types:

        vDSP_Length for numbers of elements in arrays and for indices of
        elements in arrays.  (It is also used for the base-two logarithm of
        numbers of elements, although a much smaller type is suitable for
        that.)

        vDSP_Stride for differences of indices of elements (which of course
        includes strides).
*/
typedef unsigned long vDSP_Length;
typedef long          vDSP_Stride;

/*  A DSPComplex or DSPDoubleComplex is a pair of float or double values that
    together represent a complex value.
*/
typedef struct DSPComplex {
    float  real;
    float  imag;
} DSPComplex;
typedef struct DSPDoubleComplex {
    double real;
    double imag;
} DSPDoubleComplex;


/*  A DSPSplitComplex or DSPDoubleSplitComplex is a structure containing
    two pointers, each to an array of float or double.  These represent arrays
    of complex values, with the real components of the values stored in one
    array and the imaginary components of the values stored in a separate
    array.
*/
typedef struct DSPSplitComplex {
    float  *realp;
    float  *imagp;
} DSPSplitComplex;
typedef struct DSPDoubleSplitComplex {
    double *realp;
    double *imagp;
} DSPDoubleSplitComplex;


/*  The following statements declare a few simple types and constants used by
    various vDSP routines.
*/
typedef int FFTDirection;
typedef int FFTRadix;
enum {
    kFFTDirection_Forward         = +1,
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
    
/*
    The following types are used to define 24 bit data.
*/
typedef struct { uint8_t bytes[3];} vDSP_uint24;    // unsigned integer
typedef struct { uint8_t bytes[3];} vDSP_int24;     // signed integer

    
/*  A filter object to be used with a multi-channel cascaded biquad IIR.  This
    object carries internal state which may be modified by any routine which
    uses it.  Upon creation the state is initialized such that all delay
    elements are zero.
 
    A single filter object should only be used in a single thread at a time.
*/
typedef struct vDSP_biquadm_SetupStruct *vDSP_biquadm_Setup;

/*  The following types are pointers to structures that contain data used
    inside vDSP routines to assist FFT and biquad filter operations.  The
    contents of these structures may change from release to release, so
    applications should manipulate the values only via the corresponding vDSP
    setup and destroy routines.
*/
typedef struct OpaqueFFTSetup           *FFTSetup;
typedef struct OpaqueFFTSetupD          *FFTSetupD;
typedef struct vDSP_biquad_SetupStruct  *vDSP_biquad_Setup;
typedef struct vDSP_biquad_SetupStructD *vDSP_biquad_SetupD;


/*  vDSP_create_fftsetup and vDSP_create_ffsetupD allocate memory and prepare
    constants used by single- and double-precision FFT routines, respectively.

    vDSP_destroy_fftsetup and vDSP_destroy_fftsetupD free the memory.
*/
extern FFTSetup vDSP_create_fftsetup(
    vDSP_Length __vDSP_Log2n,
    FFTRadix    __vDSP_Radix)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);

extern void vDSP_destroy_fftsetup(FFTSetup __vDSP_setup)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);

extern FFTSetupD vDSP_create_fftsetupD(
    vDSP_Length __vDSP_Log2n,
    FFTRadix    __vDSP_Radix)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);

extern void vDSP_destroy_fftsetupD(FFTSetupD __vDSP_setup)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);

/*  vDSP_biquadm_CreateSetup allocates memory and prepares the coefficients for
    processing a multi-channel cascaded biquad IIR filter.
     
    vDSP_biquadm_DestroySetup frees the memory allocated by
    vDSP_biquadm_CreateSetup.
*/
    
/*
 *  vDSP_biquadm_CreateSetup()
 */
extern vDSP_biquadm_Setup
vDSP_biquadm_CreateSetup(
    const double *__vDSP_coeffs,
    vDSP_Length __vDSP_M,
    vDSP_Length __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
    
/*
 *  vDSP_biquadm_DestroySetup()
 */
extern void vDSP_biquadm_DestroySetup(vDSP_biquadm_Setup __vDSP_setup) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
    
/*  vDSP_biquadm_CopyState copies the current state between two
    vDSP_biquadm_Setup objects.  The two objects must have been created
    with the same number of channels and sections.
 
    vDSP_biquadm_ResetState resets the state of a vDSP_biquadm_Setup
    object to its initial values upon creation with vDSP_biquadm_CreateSetup.
*/
   
/*
 *  vDSP_biquadm_CopyState()
 */
extern void
vDSP_biquadm_CopyState(
    vDSP_biquadm_Setup __vDSP_dest,
    const struct vDSP_biquadm_SetupStruct *__vDSP_src) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
    
/*
 *  vDSP_biquadm_ResetState()
 */
extern void vDSP_biquadm_ResetState(vDSP_biquadm_Setup __vDSP_setup) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
    
    
/*  vDSP_biquadm applies a multi-channel biquadm IIR filter created with
 vDSP_biquadm_CreateSetup.
 */
    
/*
 *  vDSP_biquadm()
 */
extern void vDSP_biquadm(
    vDSP_biquadm_Setup __vDSP_setup, const float** __vDSP_in_channels, vDSP_Stride __vDSP_in_stride,
    float**       __vDSP_out_channels, vDSP_Stride __vDSP_out_stride,
    vDSP_Length   __vDSP_N) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);

/*  vDSP_biquad_CreateSetup allocates memory and prepares the
    coefficients for processing a cascaded biquad IIR filter.

    vDSP_biquad_DestroySetup frees the memory allocated by
    vDSP_biquad_CreateSetup.
*/
extern vDSP_biquad_Setup vDSP_biquad_CreateSetup(
    const double *__vDSP_Coefficients,
    vDSP_Length  __vDSP_M)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

extern void vDSP_biquad_DestroySetup(vDSP_biquad_Setup __vDSP_setup)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

extern vDSP_biquad_SetupD vDSP_biquad_CreateSetupD(
    const double *__vDSP_Coefficients,
    vDSP_Length   __vDSP_M)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

extern void vDSP_biquad_DestroySetupD(vDSP_biquad_SetupD __vDSP_setup)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);


// Convert a complex array to a complex-split array.
extern void vDSP_ctoz(
    const DSPComplex      *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_Z,
    vDSP_Stride            __vDSP_IZ,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_ctozD(
    const DSPDoubleComplex      *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_Z,
    vDSP_Stride                  __vDSP_IZ,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Map:

            Pseudocode:     Memory:
            C[n]            C[n*IC/2].real + i * C[n*IC/2].imag
            Z[n]            Z->realp[n*IZ] + i * Z->imagp[n*IZ]

        These compute:

            for (n = 0; n < N; ++n)
                Z[n] = C[n];
    */


//  Convert a complex-split array to a complex array.
extern void vDSP_ztoc(
    const DSPSplitComplex *__vDSP_Z,
    vDSP_Stride            __vDSP_IZ,
    DSPComplex            *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_ztocD(
    const DSPDoubleSplitComplex *__vDSP_Z,
    vDSP_Stride                  __vDSP_IZ,
    DSPDoubleComplex            *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Map:

            Pseudocode:     Memory:
            Z[n]            Z->realp[n*IZ] + i * Z->imagp[n*IZ]
            C[n]            C[n*IC/2].real + i * C[n*IC/2].imag

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = Z[n];
    */



/*  In-place complex Discrete Fourier Transform routines, with and without
    temporary memory.  We suggest you use the DFT routines instead of these.
*/
extern void vDSP_fft_zip(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft_zipD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft_zipt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft_ziptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N = 1 << Log2N;

        scale = 0 < Direction ? 1 : 1./N;

        // Define a complex vector, h:
        for (j = 0; j < N; ++j)
            h[j] = C->realp[j*IC] + i * C->imagp[j*IC];

        // Perform Discrete Fourier Transform.
        for (k = 0; k < N; ++k)
            H[k] = scale * sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

        // Store result.
        for (k = 0; k < N; ++k)
        {
            C->realp[k*IC] = Re(H[k]);
            C->imagp[k*IC] = Im(H[k]);
        }

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain the lesser of 16,384
        bytes or N * sizeof *C->realp bytes and is preferably 16-byte aligned
        or better.
    */


/*  Out-of-place complex Discrete Fourier Transform routines, with and without
    temporary memory.  We suggest you use the DFT routines instead of these.
*/
extern void vDSP_fft_zop(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft_zopt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft_zopD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft_zoptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N = 1 << Log2N;

        scale = 0 < Direction ? 1 : 1./N;

        // Define a complex vector, h:
        for (j = 0; j < N; ++j)
            h[j] = A->realp[j*IA] + i * A->imagp[j*IA];

        // Perform Discrete Fourier Transform.
        for (k = 0; k < N; ++k)
            H[k] = scale * sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

        // Store result.
        for (k = 0; k < N; ++k)
        {
            C->realp[k*IC] = Re(H[k]);
            C->imagp[k*IC] = Im(H[k]);
        }

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain the lesser of 16,384
        bytes or N * sizeof *C->realp bytes and is preferably 16-byte aligned
        or better.
    */


/*  In-place real-to-complex Discrete Fourier Transform routines, with and
    without temporary memory.  We suggest you use the DFT routines instead of
    these.
*/
extern void vDSP_fft_zrip(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft_zripD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft_zript(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft_zriptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N = 1 << Log2N;

        If Direction is +1, a real-to-complex transform is performed, taking
        input from a real vector that has been coerced into the complex
        structure:

            scale = 2;

            // Define a real vector, h:
            for (j = 0; j < N/2; ++j)
            {
                h[2*j + 0] = C->realp[j*IC];
                h[2*j + 1] = C->imagp[j*IC];
            }

            // Perform Discrete Fourier Transform.
            for (k = 0; k < N; ++k)
                H[k] = scale *
                    sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

            // Pack DC and Nyquist components into C->realp[0] and C->imagp[0].
            C->realp[0*IC] = Re(H[ 0 ]).
            C->imagp[0*IC] = Re(H[N/2]).

            // Store regular components:
            for (k = 1; k < N/2; ++k)
            {
                C->realp[k*IC] = Re(H[k]);
                C->imagp[k*IC] = Im(H[k]);
            }

            Note that, for N/2 < k < N, H[k] is not stored.  However, since
            the input is a real vector, the output has symmetry that allows the
            unstored elements to be derived from the stored elements:  H[k] =
            conj(H(N-k)).  This symmetry also implies the DC and Nyquist
            components are real, so their imaginary parts are zero.

        If Direction is -1, a complex-to-real inverse transform is performed,
        producing a real output vector coerced into the complex structure:

            scale = 1./N;

            // Define a complex vector, h:
            h[ 0 ] = C->realp[0*IC];
            h[N/2] = C->imagp[0*IC];
            for (j = 1; j < N/2; ++j)
            {
                h[ j ] = C->realp[j*IC] + i * C->imagp[j*IC];
                h[N-j] = conj(h[j]);
            }

            // Perform Discrete Fourier Transform.
            for (k = 0; k < N; ++k)
                H[k] = scale *
                    sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

            // Coerce real results into complex structure:
            for (k = 0; k < N/2; ++k)
            {
                C->realp[k*IC] = H[2*k+0];
                C->imagp[k*IC] = H[2*k+1];
            }

            Note that, mathematically, the symmetry in the input vector compels
            every H[k] to be real, so there are no imaginary components to be
            stored.

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain N/2 * sizeof *C->realp
        bytes and is preferably 16-byte aligned or better.
    */


/*  Out-of-place real-to-complex Discrete Fourier Transform routines, with and
    without temporary memory.  We suggest you use the DFT routines instead of
    these.
*/
extern void vDSP_fft_zrop(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft_zropD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft_zropt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft_zroptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N = 1 << Log2N;

        If Direction is +1, a real-to-complex transform is performed, taking
        input from a real vector that has been coerced into the complex
        structure:

            scale = 2;

            // Define a real vector, h:
            for (j = 0; j < N/2; ++j)
            {
                h[2*j + 0] = A->realp[j*IA];
                h[2*j + 1] = A->imagp[j*IA];
            }

            // Perform Discrete Fourier Transform.
            for (k = 0; k < N; ++k)
                H[k] = scale *
                    sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

            // Pack DC and Nyquist components into C->realp[0] and C->imagp[0].
            C->realp[0*IC] = Re(H[ 0 ]).
            C->imagp[0*IC] = Re(H[N/2]).

            // Store regular components:
            for (k = 1; k < N/2; ++k)
            {
                C->realp[k*IC] = Re(H[k]);
                C->imagp[k*IC] = Im(H[k]);
            }

            Note that, for N/2 < k < N, H[k] is not stored.  However, since
            the input is a real vector, the output has symmetry that allows the
            unstored elements to be derived from the stored elements:  H[k] =
            conj(H(N-k)).  This symmetry also implies the DC and Nyquist
            components are real, so their imaginary parts are zero.

        If Direction is -1, a complex-to-real inverse transform is performed,
        producing a real output vector coerced into the complex structure:

            scale = 1./N;

            // Define a complex vector, h:
            h[ 0 ] = A->realp[0*IA];
            h[N/2] = A->imagp[0*IA];
            for (j = 1; j < N/2; ++j)
            {
                h[ j ] = A->realp[j*IA] + i * A->imagp[j*IA];
                h[N-j] = conj(h[j]);
            }

            // Perform Discrete Fourier Transform.
            for (k = 0; k < N; ++k)
                H[k] = scale *
                    sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

            // Coerce real results into complex structure:
            for (k = 0; k < N/2; ++k)
            {
                C->realp[k*IC] = H[2*k+0];
                C->imagp[k*IC] = H[2*k+1];
            }

            Note that, mathematically, the symmetry in the input vector compels
            every H[k] to be real, so there are no imaginary components to be
            stored.

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain N/2 * sizeof *C->realp
        bytes and is preferably 16-byte aligned or better.
    */


/*  In-place two-dimensional complex Discrete Fourier Transform routines, with
    and without temporary memory.
*/
extern void vDSP_fft2d_zip(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC0,
    vDSP_Stride            __vDSP_IC1,
    vDSP_Length            __vDSP_Log2N0,
    vDSP_Length            __vDSP_Log2N1,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft2d_zipD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC0,
    vDSP_Stride                  __vDSP_IC1,
    vDSP_Length                  __vDSP_Log2N0,
    vDSP_Length                  __vDSP_Log2N1,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft2d_zipt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC1,
    vDSP_Stride            __vDSP_IC0,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N0,
    vDSP_Length            __vDSP_Log2N1,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft2d_ziptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC0,
    vDSP_Stride                  __vDSP_IC1,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N0,
    vDSP_Length                  __vDSP_Log2N1,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N0 = 1 << Log2N0;
        N1 = 1 << Log2N1;

        if (IC1 == 0) IC1 = IC0*N0;

        scale = 0 < Direction ? 1 : 1. / (N1*N0);

        // Define a complex matrix, h:
        for (j1 = 0; j1 < N1; ++j1)
        for (j0 = 0; j0 < N0; ++j0)
            h[j1][j0] = C->realp[j1*IC1 + j0*IC0]
                  + i * C->imagp[j1*IC1 + j0*IC0];

        // Perform Discrete Fourier Transform.
        for (k1 = 0; k1 < N1; ++k1)
        for (k0 = 0; k0 < N0; ++k0)
            H[k1][k0] = scale * sum(sum(h[j1][j0]
                * e**(-Direction*2*pi*i*j0*k0/N0), 0 <= j0 < N0)
                * e**(-Direction*2*pi*i*j1*k1/N1), 0 <= j1 < N1);

        // Store result.
        for (k1 = 0; k1 < N1; ++k1)
        for (k0 = 0; k0 < N0; ++k0)
        {
            C->realp[k1*IC1 + k0*IC0] = Re(H[k1][k0]);
            C->imagp[k1*IC1 + k0*IC0] = Im(H[k1][k0]);
        }

        Note that the 0 and 1 dimensions are separate and identical, except
        that IC1 is set to a default, IC0*N0, if it is zero.  If IC1 is not
        zero, then the IC0 and N0 arguments may be swapped with the IC1 and N1
        arguments without affecting the results.

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain the lesser of 16,384
        bytes or N1*N0 * sizeof *C->realp bytes and is preferably 16-byte
        aligned or better.
    */


/*  Out-of-place two-dimensional complex Discrete Fourier Transform routines,
    with and without temporary memory.
*/
extern void vDSP_fft2d_zop(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA0,
    vDSP_Stride            __vDSP_IA1,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC0,
    vDSP_Stride            __vDSP_IC1,
    vDSP_Length            __vDSP_Log2N0,
    vDSP_Length            __vDSP_Log2N1,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft2d_zopD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA0,
    vDSP_Stride                  __vDSP_IA1,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC0,
    vDSP_Stride                  __vDSP_IC1,
    vDSP_Length                  __vDSP_Log2N0,
    vDSP_Length                  __vDSP_Log2N1,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft2d_zopt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA0,
    vDSP_Stride            __vDSP_IA1,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC0,
    vDSP_Stride            __vDSP_IC1,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N0,
    vDSP_Length            __vDSP_Log2N1,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft2d_zoptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA0,
    vDSP_Stride                  __vDSP_IA1,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC0,
    vDSP_Stride                  __vDSP_IC1,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N0,
    vDSP_Length                  __vDSP_Log2N1,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N0 = 1 << Log2N0;
        N1 = 1 << Log2N1;

        if (IA1 == 0) IA1 = IA0*N0;
        if (IC1 == 0) IC1 = IC0*N0;

        scale = 0 < Direction ? 1 : 1. / (N1*N0);

        // Define a complex matrix, h:
        for (j1 = 0; j1 < N1; ++j1)
        for (j0 = 0; j0 < N0; ++j0)
            h[j1][j0] = A->realp[j1*IA1 + j0*IA0]
                  + i * A->imagp[j1*IA1 + j0*IA0];

        // Perform Discrete Fourier Transform.
        for (k1 = 0; k1 < N1; ++k1)
        for (k0 = 0; k0 < N0; ++k0)
            H[k1][k0] = scale * sum(sum(h[j1][j0]
                * e**(-Direction*2*pi*i*j0*k0/N0), 0 <= j0 < N0)
                * e**(-Direction*2*pi*i*j1*k1/N1), 0 <= j1 < N1);

        // Store result.
        for (k1 = 0; k1 < N1; ++k1)
        for (k0 = 0; k0 < N0; ++k0)
        {
            C->realp[k1*IC1 + k0*IC0] = Re(H[k1][k0]);
            C->imagp[k1*IC1 + k0*IC0] = Im(H[k1][k0]);
        }

        Note that the 0 and 1 dimensions are separate and identical, except
        that IA1 or IC1 are set to defaults, IA0*N0 or IC0*N0, if either is
        zero.  If neither is zero, then the IA0, IC0, and N0 arguments may be
        swapped with the IA1, IC1 and N1 arguments without affecting the
        results.

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain the lesser of 16,384
        bytes or N1*N0 * sizeof *C->realp bytes and is preferably 16-byte
        aligned or better.
    */


/*  In-place two-dimensional real-to-complex Discrete Fourier Transform
    routines, with and without temporary memory.
*/
extern void vDSP_fft2d_zrip(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC0,
    vDSP_Stride            __vDSP_IC1,
    vDSP_Length            __vDSP_Log2N0,
    vDSP_Length            __vDSP_Log2N1,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft2d_zripD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC0,
    vDSP_Stride                  __vDSP_IC1,
    vDSP_Length                  __vDSP_Log2N0,
    vDSP_Length                  __vDSP_Log2N1,
    FFTDirection                 __vDSP_flag)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft2d_zript(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC0,
    vDSP_Stride            __vDSP_IC1,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N0,
    vDSP_Length            __vDSP_Log2N1,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft2d_zriptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC0,
    vDSP_Stride                  __vDSP_IC1,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N0,
    vDSP_Length                  __vDSP_Log2N1,
    FFTDirection                 __vDSP_flag)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N0 = 1 << Log2N0;
        N1 = 1 << Log2N1;

        if (IC1 == 0) IC1 = IC0*N0/2;

        If Direction is +1, a real-to-complex transform is performed, taking
        input from a real vector that has been coerced into the complex
        structure:

            scale = 2;

            // Define a real matrix, h:
            for (j1 = 0; j1 < N1  ; ++j1)
            for (j0 = 0; j0 < N0/2; ++j0)
            {
                h[j1][2*j0+0] = C->realp[j1*IC1 + j0*IC0]
                          + i * C->imagp[j1*IC1 + j0*IC0];
                h[j1][2*j0+1] = C->realp[j1*IC1 + j0*IC0]
                          + i * C->imagp[j1*IC1 + j0*IC0];
            }

            // Perform Discrete Fourier Transform.
            for (k1 = 0; k1 < N1; ++k1)
            for (k0 = 0; k0 < N0; ++k0)
                H[k1][k0] = scale * sum(sum(h[j1][j0]
                    * e**(-Direction*2*pi*i*j0*k0/N0), 0 <= j0 < N0)
                    * e**(-Direction*2*pi*i*j1*k1/N1), 0 <= j1 < N1);

            // Pack special pure-real elements into output matrix:
            C->realp[0*IC1][0*IC0] = H[0   ][0   ].
            C->imagp[0*IC1][0*IC0] = H[0   ][N0/2]
            C->realp[1*IC1][0*IC0] = H[N1/2][0   ].
            C->imagp[1*IC1][0*IC0] = H[N1/2][N0/2]

            // Pack two vectors into output matrix "vertically":
            // (This awkward format is due to a legacy implementation.)
            for (k1 = 1; k1 < N1/2; ++k1)
            {
                C->realp[(2*k1+0)*IC1][0*IC0] = Re(H[k1][0   ]);
                C->realp[(2*k1+1)*IC1][0*IC0] = Im(H[k1][0   ]);
                C->imagp[(2*k1+0)*IC1][0*IC0] = Re(H[k1][N0/2]);
                C->imagp[(2*k1+1)*IC1][0*IC0] = Im(H[k1][N0/2]);
            }

            // Store regular elements:
            for (k1 = 0; k1 < N1  ; ++k1)
            for (k0 = 1; k0 < N0/2; ++k0)
            {
                C->realp[k1*IC1 + k0*IC0] = Re(H[k1][k0]);
                C->imagp[k1*IC1 + k0*IC0] = Im(H[k1][k0]);
            }

            Many elements of H are not stored.  However, since the input is a
            real matrix, H has symmetry that makes all the unstored elements of
            H functions of the stored elements of H.  So the data stored in C
            has complete information about the transform result.

        If Direction is -1, a complex-to-real inverse transform is performed,
        producing a real output vector coerced into the complex structure:

            scale = 1. / (N1*N0);

            // Define a complex matrix, h, in multiple steps:

            // Unpack the special elements:
            h[0   ][0   ] = C->realp[0*IC1][0*IC0];
            h[0   ][N0/2] = C->imagp[0*IC1][0*IC0];
            h[N1/2][0   ] = C->realp[1*IC1][0*IC0];
            h[N1/2][N0/2] = C->imagp[1*IC1][0*IC0];

            // Unpack the two vectors from "vertical" storage:
            for (j1 = 1; j1 < N1/2; ++j1)
            {
                h[j1][0   ] = C->realp[(2*j1+0)*IC1][0*IC0]
                        + i * C->realp[(2*j1+1)*IC1][0*IC0]
                h[j1][N0/2] = C->imagp[(2*j1+0)*IC1][0*IC0]
                        + i * C->imagp[(2*j1+1)*IC1][0*IC0]
            }

            // Take regular elements:
            for (j1 = 0; j1 < N1  ; ++j1)
            for (j0 = 1; j0 < N0/2; ++j0)
            {
                h[j1][j0   ] = C->realp[j1*IC1 + j0*IC0]
                         + i * C->imagp[j1*IC1 + j0*IC0];
                h[j1][N0-j0] = conj(h[j1][j0]);
            }

            // Perform Discrete Fourier Transform.
            for (k1 = 0; k1 < N1; ++k1)
            for (k0 = 0; k0 < N0; ++k0)
                H[k1][k0] = scale * sum(sum(h[j1][j0]
                    * e**(-Direction*2*pi*i*j0*k0/N0), 0 <= j0 < N0)
                    * e**(-Direction*2*pi*i*j1*k1/N1), 0 <= j1 < N1);

            // Store result.
            for (k1 = 0; k1 < N1  ; ++k1)
            for (k0 = 0; k0 < N0/2; ++k0)
            {
                C->realp[k1*IC1 + k0*IC0] = Re(H[k1][2*k0+0]);
                C->imagp[k1*IC1 + k0*IC0] = Im(H[k1][2*k0+1]);
            }

        Unlike the two-dimensional complex transform, the dimensions are not
        symmetric in this real-to-complex transform.

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain space for the greater
        of N1 or N0/2 floating-point elements.  The addresses are preferably
        16-byte aligned or better.
    */


/*  Out-of-place two-dimensional real-to-complex Discrete Fourier Transform
    routines, with and without temporary memory.
*/
extern void vDSP_fft2d_zrop(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA0,
    vDSP_Stride            __vDSP_IA1,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC0,
    vDSP_Stride            __vDSP_IC1,
    vDSP_Length            __vDSP_Log2N0,
    vDSP_Length            __vDSP_Log2N1,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft2d_zropt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA0,
    vDSP_Stride            __vDSP_IA1,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC0,
    vDSP_Stride            __vDSP_IC1,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N0,
    vDSP_Length            __vDSP_Log2N1,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_fft2d_zropD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA0,
    vDSP_Stride                  __vDSP_IA1,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC0,
    vDSP_Stride                  __vDSP_IC1,
    vDSP_Length                  __vDSP_Log2N0,
    vDSP_Length                  __vDSP_Log2N1,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft2d_zroptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA0,
    vDSP_Stride                  __vDSP_IA1,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC0,
    vDSP_Stride                  __vDSP_IC1,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N0,
    vDSP_Length                  __vDSP_Log2N1,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N0 = 1 << Log2N0;
        N1 = 1 << Log2N1;

        if (IA1 == 0) IA1 = IA0*N0/2;
        if (IC1 == 0) IC1 = IC0*N0/2;

        If Direction is +1, a real-to-complex transform is performed, taking
        input from a real vector that has been coerced into the complex
        structure:

            scale = 2;

            // Define a real matrix, h:
            for (j1 = 0; j1 < N1  ; ++j1)
            for (j0 = 0; j0 < N0/2; ++j0)
            {
                h[j1][2*j0+0] = A->realp[j1*IA1 + j0*IA0]
                          + i * A->imagp[j1*IA1 + j0*IA0];
                h[j1][2*j0+1] = A->realp[j1*IA1 + j0*IA0]
                          + i * A->imagp[j1*IA1 + j0*IA0];
            }

            // Perform Discrete Fourier Transform.
            for (k1 = 0; k1 < N1; ++k1)
            for (k0 = 0; k0 < N0; ++k0)
                H[k1][k0] = scale * sum(sum(h[j1][j0]
                    * e**(-Direction*2*pi*i*j0*k0/N0), 0 <= j0 < N0)
                    * e**(-Direction*2*pi*i*j1*k1/N1), 0 <= j1 < N1);

            // Pack special pure-real elements into output matrix:
            C->realp[0*IC1][0*IC0] = H[0   ][0   ].
            C->imagp[0*IC1][0*IC0] = H[0   ][N0/2]
            C->realp[1*IC1][0*IC0] = H[N1/2][0   ].
            C->imagp[1*IC1][0*IC0] = H[N1/2][N0/2]

            // Pack two vectors into output matrix "vertically":
            // (This awkward format is due to a legacy implementation.)
            for (k1 = 1; k1 < N1/2; ++k1)
            {
                C->realp[(2*k1+0)*IC1][0*IC0] = Re(H[k1][0   ]);
                C->realp[(2*k1+1)*IC1][0*IC0] = Im(H[k1][0   ]);
                C->imagp[(2*k1+0)*IC1][0*IC0] = Re(H[k1][N0/2]);
                C->imagp[(2*k1+1)*IC1][0*IC0] = Im(H[k1][N0/2]);
            }

            // Store regular elements:
            for (k1 = 0; k1 < N1  ; ++k1)
            for (k0 = 1; k0 < N0/2; ++k0)
            {
                C->realp[k1*IC1 + k0*IC0] = Re(H[k1][k0]);
                C->imagp[k1*IC1 + k0*IC0] = Im(H[k1][k0]);
            }

            Many elements of H are not stored.  However, since the input is a
            real matrix, H has symmetry that makes all the unstored elements of
            H functions of the stored elements of H.  So the data stored in C
            has complete information about the transform result.

        If Direction is -1, a complex-to-real inverse transform is performed,
        producing a real output vector coerced into the complex structure:

            scale = 1. / (N1*N0);

            // Define a complex matrix, h, in multiple steps:

            // Unpack the special elements:
            h[0   ][0   ] = A->realp[0*IA1][0*IA0];
            h[0   ][N0/2] = A->imagp[0*IA1][0*IA0];
            h[N1/2][0   ] = A->realp[1*IA1][0*IA0];
            h[N1/2][N0/2] = A->imagp[1*IA1][0*IA0];

            // Unpack the two vectors from "vertical" storage:
            for (j1 = 1; j1 < N1/2; ++j1)
            {
                h[j1][0   ] = A->realp[(2*j1+0)*IA1][0*IA0]
                        + i * A->realp[(2*j1+1)*IA1][0*IA0]
                h[j1][N0/2] = A->imagp[(2*j1+0)*IA1][0*IA0]
                        + i * A->imagp[(2*j1+1)*IA1][0*IA0]
            }

            // Take regular elements:
            for (j1 = 0; j1 < N1  ; ++j1)
            for (j0 = 1; j0 < N0/2; ++j0)
            {
                h[j1][j0   ] = A->realp[j1*IA1 + j0*IA0]
                         + i * A->imagp[j1*IA1 + j0*IA0];
                h[j1][N0-j0] = conj(h[j1][j0]);
            }

            // Perform Discrete Fourier Transform.
            for (k1 = 0; k1 < N1; ++k1)
            for (k0 = 0; k0 < N0; ++k0)
                H[k1][k0] = scale * sum(sum(h[j1][j0]
                    * e**(-Direction*2*pi*i*j0*k0/N0), 0 <= j0 < N0)
                    * e**(-Direction*2*pi*i*j1*k1/N1), 0 <= j1 < N1);

            // Store result.
            for (k1 = 0; k1 < N1  ; ++k1)
            for (k0 = 0; k0 < N0/2; ++k0)
            {
                C->realp[k1*IC1 + k0*IC0] = Re(H[k1][2*k0+0]);
                C->imagp[k1*IC1 + k0*IC0] = Im(H[k1][2*k0+1]);
            }

        Unlike the two-dimensional complex transform, the dimensions are not
        symmetric in this real-to-complex transform.

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain space for the greater
        of N1 or N0/2 floating-point elements.  The addresses are preferably
        16-byte aligned or better.
    */


/*  In-place multiple complex Discrete Fourier Transform routines, with and
    without temporary memory.
*/
extern void vDSP_fftm_zip(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Stride            __vDSP_IM,
    vDSP_Length            __vDSP_Log2N,
    vDSP_Length            __vDSP_M,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zipD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Stride                  __vDSP_IM,
    vDSP_Length                  __vDSP_Log2N,
    vDSP_Length                  __vDSP_M,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zipt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Stride            __vDSP_IM,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N,
    vDSP_Length            __vDSP_M,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_ziptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Stride                  __vDSP_IM,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N,
    vDSP_Length                  __vDSP_M,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N = 1 << Log2N;

        scale = 0 < Direction ? 1 : 1./N;

        // Repeat M times:
        for (m = 0; m < M; ++m)
        {

            // Define a complex vector, h:
            for (j = 0; j < N; ++j)
                h[j] = C->realp[m*IM + j*IC] + i * C->imagp[m*IM + j*IC];

            // Perform Discrete Fourier Transform.
            for (k = 0; k < N; ++k)
                H[k] = scale * sum(h[j]
                    * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

            // Store result.
            for (k = 0; k < N; ++k)
            {
                C->realp[m*IM + k*IC] = Re(H[k]);
                C->imagp[m*IM + k*IC] = Im(H[k]);
            }

        }

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain space for N
        floating-point elements and is preferably 16-byte aligned or better.
    */


/*  Out-of-place multiple complex Discrete Fourier Transform routines, with and
    without temporary memory.
*/
extern void vDSP_fftm_zop(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    vDSP_Stride            __vDSP_IMA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Stride            __vDSP_IMC,
    vDSP_Length            __vDSP_Log2N,
    vDSP_Length            __vDSP_M,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zopD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    vDSP_Stride                  __vDSP_IMA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Stride                  __vDSP_IMC,
    vDSP_Length                  __vDSP_Log2N,
    vDSP_Length                  __vDSP_M,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zopt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    vDSP_Stride            __vDSP_IMA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Stride            __vDSP_IMC,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N,
    vDSP_Length            __vDSP_M,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zoptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    vDSP_Stride                  __vDSP_IMA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Stride                  __vDSP_IMC,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N,
    vDSP_Length                  __vDSP_M,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N = 1 << Log2N;

        scale = 0 < Direction ? 1 : 1./N;

        // Repeat M times:
        for (m = 0; m < M; ++m)
        {

            // Define a complex vector, h:
            for (j = 0; j < N; ++j)
                h[j] = A->realp[m*IMA + j*IA] + i * A->imagp[m*IMA + j*IA];

            // Perform Discrete Fourier Transform.
            for (k = 0; k < N; ++k)
                H[k] = scale * sum(h[j]
                    * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

            // Store result.
            for (k = 0; k < N; ++k)
            {
                C->realp[m*IM + k*IC] = Re(H[k]);
                C->imagp[m*IM + k*IC] = Im(H[k]);
            }

        }

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain space for N
        floating-point elements and is preferably 16-byte aligned or better.
    */


/*  In-place multiple real-to-complex Discrete Fourier Transform routines, with
    and without temporary memory.  We suggest you use the DFT routines instead
    of these.
*/
extern void vDSP_fftm_zrip(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Stride            __vDSP_IM,
    vDSP_Length            __vDSP_Log2N,
    vDSP_Length            __vDSP_M,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zripD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Stride                  __vDSP_IM,
    vDSP_Length                  __vDSP_Log2N,
    vDSP_Length                  __vDSP_M,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zript(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Stride            __vDSP_IM,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N,
    vDSP_Length            __vDSP_M,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zriptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Stride                  __vDSP_IM,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N,
    vDSP_Length                  __vDSP_M,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N = 1 << Log2N;

        // Repeat M times:
        for (m = 0; m < M; ++m)
        {

            If Direction is +1, a real-to-complex transform is performed,
            taking input from a real vector that has been coerced into the
            complex structure:

                scale = 2;

                // Define a real vector, h:
                for (j = 0; j < N/2; ++j)
                {
                    h[2*j + 0] = C->realp[m*IM + j*IC];
                    h[2*j + 1] = C->imagp[m*IM + j*IC];
                }

                // Perform Discrete Fourier Transform.
                for (k = 0; k < N; ++k)
                    H[k] = scale *
                        sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

                // Pack DC and Nyquist components into initial elements.
                C->realp[m*IM + 0*IC] = Re(H[ 0 ]).
                C->imagp[m*IM + 0*IC] = Re(H[N/2]).

                // Store regular components:
                for (k = 1; k < N/2; ++k)
                {
                    C->realp[m*IM + k*IC] = Re(H[k]);
                    C->imagp[m*IM + k*IC] = Im(H[k]);
                }

                Note that, for N/2 < k < N, H[k] is not stored.  However, since
                the input is a real vector, the output has symmetry that allows
                the unstored elements to be derived from the stored elements:
                H[k] = conj(H(N-k)).  This symmetry also implies the DC and
                Nyquist components are real, so their imaginary parts are zero.

            If Direction is -1, a complex-to-real inverse transform is
            performed, producing a real output vector coerced into the complex
            structure:

                scale = 1./N;

                // Define a complex vector, h:
                h[ 0 ] = C->realp[m*IM + 0*IC];
                h[N/2] = C->imagp[m*IM + 0*IC];
                for (j = 1; j < N/2; ++j)
                {
                    h[ j ] = C->realp[m*IM + j*IC] + i * C->imagp[m*IM + j*IC];
                    h[N-j] = conj(h[j]);
                }

                // Perform Discrete Fourier Transform.
                for (k = 0; k < N; ++k)
                    H[k] = scale *
                        sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

                // Coerce real results into complex structure:
                for (k = 0; k < N/2; ++k)
                {
                    C->realp[m*IM + k*IC] = H[2*k+0];
                    C->imagp[m*IM + k*IC] = H[2*k+1];
                }

                Note that, mathematically, the symmetry in the input vector
                compels every H[k] to be real, so there are no imaginary
                components to be stored.

        }

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain space for N/2
        floating-point elements and is preferably 16-byte aligned or better.
    */



/*  Out-of-place multiple real-to-complex Discrete Fourier Transform routines,
    with and without temporary memory.  We suggest you use the DFT routines
    instead of these.
*/
extern void vDSP_fftm_zrop(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    vDSP_Stride            __vDSP_IMA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Stride            __vDSP_IMC,
    vDSP_Length            __vDSP_Log2N,
    vDSP_Length            __vDSP_M,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zropt(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    vDSP_Stride            __vDSP_IMA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Stride            __vDSP_IMC,
    const DSPSplitComplex *__vDSP_Buffer,
    vDSP_Length            __vDSP_Log2N,
    vDSP_Length            __vDSP_M,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zropD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    vDSP_Stride                  __vDSP_IMA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Stride                  __vDSP_IMC,
    vDSP_Length                  __vDSP_Log2N,
    vDSP_Length                  __vDSP_M,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fftm_zroptD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    vDSP_Stride                  __vDSP_IMA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Stride                  __vDSP_IMC,
    const DSPDoubleSplitComplex *__vDSP_Buffer,
    vDSP_Length                  __vDSP_Log2N,
    vDSP_Length                  __vDSP_M,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        N = 1 << Log2N;

        // Repeat M times:
        for (m = 0; m < M; ++m)
        {

            If Direction is +1, a real-to-complex transform is performed,
            taking input from a real vector that has been coerced into the
            complex structure:

                scale = 2;

                // Define a real vector, h:
                for (j = 0; j < N/2; ++j)
                {
                    h[2*j + 0] = A->realp[m*IMA + j*IA];
                    h[2*j + 1] = A->imagp[m*IMA + j*IA];
                }

                // Perform Discrete Fourier Transform.
                for (k = 0; k < N; ++k)
                    H[k] = scale *
                        sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

                // Pack DC and Nyquist components into initial elements.
                C->realp[m*IMC + 0*IC] = Re(H[ 0 ]).
                C->imagp[m*IMC + 0*IC] = Re(H[N/2]).

                // Store regular components:
                for (k = 1; k < N/2; ++k)
                {
                    C->realp[m*IMC + k*IC] = Re(H[k]);
                    C->imagp[m*IMC + k*IC] = Im(H[k]);
                }

                Note that, for N/2 < k < N, H[k] is not stored.  However, since
                the input is a real vector, the output has symmetry that allows
                the unstored elements to be derived from the stored elements:
                H[k] = conj(H(N-k)).  This symmetry also implies the DC and
                Nyquist components are real, so their imaginary parts are zero.

            If Direction is -1, a complex-to-real inverse transform is
            performed, producing a real output vector coerced into the complex
            structure:

                scale = 1./N;

                // Define a complex vector, h:
                h[ 0 ] = A->realp[m*IMA + 0*IA];
                h[N/2] = A->imagp[m*IMA + 0*IA];
                for (j = 1; j < N/2; ++j)
                {
                    h[ j ] = A->realp[m*IMA + j*IA]
                       + i * A->imagp[m*IMA + j*IA];
                    h[N-j] = conj(h[j]);
                }

                // Perform Discrete Fourier Transform.
                for (k = 0; k < N; ++k)
                    H[k] = scale *
                        sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

                // Coerce real results into complex structure:
                for (k = 0; k < N/2; ++k)
                {
                    C->realp[m*IMC + k*IC] = H[2*k+0];
                    C->imagp[m*IMC + k*IC] = H[2*k+1];
                }

                Note that, mathematically, the symmetry in the input vector
                compels every H[k] to be real, so there are no imaginary
                components to be stored.

        }

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.

        The temporary buffer versions perform the same operation but are
        permitted to use the temporary buffer for improved performance.  Each
        of Buffer->realp and Buffer->imagp must contain space for N/2
        floating-point elements and is preferably 16-byte aligned or better.
    */


/*  Non-power-of-two out-of-place complex Discrete Fourier Transform routines.
    We suggest you use the DFT routines instead of these.
*/
extern void vDSP_fft3_zop(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft3_zopD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft5_zop(
    FFTSetup               __vDSP_Setup,
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_Log2N,
    FFTDirection           __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_fft5_zopD(
    FFTSetupD                    __vDSP_Setup,
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_Log2N,
    FFTDirection                 __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        p = 3 or 5, as shown in the routine name.

        N = p << Log2N;

        scale = 0 < Direction ? 1 : 1./N;

        // Define a complex vector, h:
        for (j = 0; j < N; ++j)
            h[j] = A->realp[j*IA] + i * A->imagp[j*IA];

        // Perform Discrete Fourier Transform.
        for (k = 0; k < N; ++k)
            H[k] = scale * sum(h[j] * e**(-Direction*2*pi*i*j*k/N), 0 <= j < N);

        // Store result.
        for (k = 0; k < N; ++k)
        {
            C->realp[k*IC] = Re(H[k]);
            C->imagp[k*IC] = Im(H[k]);
        }

        Setup must have been properly created by a call to vDSP_create_fftsetup
        (for single precision) or vDSP_create_fftsetupD (for double precision)
        and not subsequently destroyed.

        Direction must be +1 or -1.
    */


/*  Cascade biquadratic IIR filters.
*/
extern void vDSP_biquad(
    const struct vDSP_biquad_SetupStruct *__vDSP_Setup,
    float       *__vDSP_Delay,
    const float *__vDSP_X, vDSP_Stride __vDSP_IX,
    float       *__vDSP_Y, vDSP_Stride __vDSP_IY,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
extern void vDSP_biquadD(
    const struct vDSP_biquad_SetupStructD *__vDSP_Setup,
    double       *__vDSP_Delay,
    const double *__vDSP_X, vDSP_Stride __vDSP_IX,
    double       *__vDSP_Y, vDSP_Stride __vDSP_IY,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
    /*  Maps:

            For this routine, strides are shown explicitly; the default maps
            are not used.

        These compute:

        S, A0, A1, A2, B1, and B2 are determined by Setup.
        S is the number of sections.

        X provides the bulk of the input signal.  Delay provides prior state
        data for S biquadratic filters.  The filters are applied to the data in
        turn.  The output of the final filter is stored in Y, and the final
        state data of the filters are stored in Delay.

        // Initialize the first row of a matrix x with data from X:
        for (n = 0; n < N; ++n)
            x[0][n ] = X[n*IX];

        // Initialize the "past" information, elements -2 and -1, from Delay:
        for (s = 0; s <= S; ++s)
        {
            x[s][-2] = Delay[2*s+0];
            x[s][-1] = Delay[2*s+1];
        }

        // Apply each filter:
        for (s = 1; s <= S; ++s)
            for (n = 0; n < N; ++n)
                x[s][n] =
                    + A0[s] * x[s-1][n-0]
                    + A1[s] * x[s-1][n-1]
                    + A2[s] * x[s-1][n-2]
                    - B1[s] * x[s  ][n-1]
                    - B2[s] * x[s  ][n-2];

        // Save the updated state data from the end of each row:
        for (s = 0; s <= S; ++s)
        {
            Delay[2*s+0] = x[s][N-2];
            Delay[2*s+1] = x[s][N-1];
        }

        // Store the results of the final filter:
        for (n = 0; n < N; ++n)
            Y[n*IY] = x[S][n];
    */

/*  Convolution and correlation.
*/
extern void vDSP_conv(
    const float *__vDSP_A,  // Input signal.
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_F,  // Filter.
    vDSP_Stride  __vDSP_IF,
    float       *__vDSP_C,  // Output signal.
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N,  // Output length.
    vDSP_Length  __vDSP_P)  // Filter length.
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_convD(
    const double *__vDSP_A, // Input signal.
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_F, // Filter
    vDSP_Stride   __vDSP_IF,
    double       *__vDSP_C, // Output signal.
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N, // Output length.
    vDSP_Length   __vDSP_P) // Filter length.
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zconv(
    const DSPSplitComplex *__vDSP_A,  // Input signal.
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_F,  // Filter.
    vDSP_Stride            __vDSP_IF,
    const DSPSplitComplex *__vDSP_C,  // Output signal.
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N,  // Output length.
    vDSP_Length            __vDSP_P)  // Filter length.
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zconvD(
    const DSPDoubleSplitComplex *__vDSP_A,    // Input signal.
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_F,    // Filter.
    vDSP_Stride                  __vDSP_IF,
    const DSPDoubleSplitComplex *__vDSP_C,    // Output signal.
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N,    // Output length.
    vDSP_Length                  __vDSP_P)    // Filter length.
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = sum(A[n+p] * F[p], 0 <= p < P);

        Commonly, this is called correlation if IF is positive and convolution
        if IF is negative.
    */


/*  3*3 and 5*5 convolutions.
*/
extern void vDSP_f3x3(
    const float *__vDSP_A,
    vDSP_Length  __vDSP_NR,
    vDSP_Length  __vDSP_NC,
    const float *__vDSP_F,
    float       *__vDSP_C)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_f3x3D(
    const double *__vDSP_A,
    vDSP_Length   __vDSP_NR,
    vDSP_Length   __vDSP_NC,
    const double *__vDSP_F,
    double       *__vDSP_C)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_f5x5(
    const float *__vDSP_A,
    vDSP_Length  __vDSP_NR,
    vDSP_Length  __vDSP_NC,
    const float *__vDSP_F,
    float       *__vDSP_C)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_f5x5D(
    const double *__vDSP_A,
    vDSP_Length   __vDSP_NR,
    vDSP_Length   __vDSP_NC,
    const double *__vDSP_F,
    double       *__vDSP_C)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            This routine does not have strides.

            A and C are regarded as two-dimensional matrices with dimensions
            [NR][NC].  F is regarded as a two-dimensional matrix with
            dimensions [P][P]:

            Pseudocode:     Memory:
            A[j][k]         A[j*NC + k]
            C[j][k]         C[j*NC + k]
            F[j][k]         F[j*P  + k]

        These compute:

            P = 3 or 5, according to the routine name.

            Below, "P/2" is evaluated using integer arithmetic, so it is 1 or 2
            (not 1.5 or 2.5).

            for (r = P/2; r < NR-P/2; ++r)
            for (c = P/2; c < NC-P/2; ++c)
                C[r][c] = sum(A[r+j][c+k] * F[j+P/2][k+P/2],
                    -P/2 <= j < P/2, -P/2 <= k < P/2);

            All other elements of C (a border of P/2 elements around all four
            sides) are set to zero.
    */


/*  Two-dimensional (image) convolution.
*/
extern void vDSP_imgfir(
    const float *__vDSP_A,  // Input.
    vDSP_Length  __vDSP_NR, // Number of image rows.
    vDSP_Length  __vDSP_NC, // Number of image columns.
    const float *__vDSP_F,  // Filter.
    float       *__vDSP_C,  // Output.
    vDSP_Length  __vDSP_P,  // Number of filter rows.
    vDSP_Length  __vDSP_Q)  // Number of filter columns.
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_imgfirD(
    const double *__vDSP_A,  // Input.
    vDSP_Length   __vDSP_NR, // Number of image rows.
    vDSP_Length   __vDSP_NC, // Number of image columns.
    const double *__vDSP_F,  // Filter.
    double       *__vDSP_C,  // Output.
    vDSP_Length   __vDSP_P,  // Number of filter rows.
    vDSP_Length   __vDSP_Q)  // Number of filter columns.
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            This routine does not have strides.

            A and C are regarded as two-dimensional matrices with dimensions
            [NR][NC].  F is regarded as a two-dimensional matrix with
            dimensions [P][Q].

            A and C are regarded as two-dimensional matrices with dimensions
            [NR][NC].  F is regarded as a two-dimensional matrix with
            dimensions [P][P]:

            Pseudocode:     Memory:
            A[j][k]         A[j*NC + k]
            C[j][k]         C[j*NC + k]
            F[j][k]         F[j*Q  + k]

        These compute:

            P and Q must be odd.  "P/2" and "Q/2" are evaluated with integer
            arithmetic, so, if P is 3, P/2 is 1, not 1.5.

            for (r = P/2; r < NR-P/2; ++r)
            for (c = Q/2; c < NC-Q/2; ++c)
                C[r][c] = sum(A[r+j][c+k] * F[j+P/2][k+Q/2],
                    -P/2 <= j < P/2, -Q/2 <= k < Q/2);

            All other elements of C (borders of P/2 elements at the top and
            bottom and Q/2 elements at the left and right) are set to zero.
    */


extern void vDSP_mtrans(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_M,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_mtransD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_M,
    vDSP_Length   __vDSP_N)
            __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            A is regarded as a two-dimensional matrix with dimemnsions
            [N][M] and stride IA.  C is regarded as a two-dimensional matrix
            with dimemnsions [M][N] and stride IC:

            Pseudocode:     Memory:
            A[n][m]         A[(n*M + m)*IA]
            C[m][n]         C[(m*N + n)*IC]

        These compute:

            for (m = 0; m < M; ++m)
            for (n = 0; n < N; ++n)
                C[m][n] = A[n][m];
    */


/*  Matrix multiply.
*/
extern void vDSP_mmul(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_M,
    vDSP_Length  __vDSP_N,
    vDSP_Length  __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_mmulD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_M,
    vDSP_Length   __vDSP_N,
    vDSP_Length   __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            A is regarded as a two-dimensional matrix with dimemnsions [M][P]
            and stride IA.  B is regarded as a two-dimensional matrix with
            dimemnsions [P][N] and stride IB.  C is regarded as a
            two-dimensional matrix with dimemnsions [M][N] and stride IC.

            Pseudocode:     Memory:
            A[m][p]         A[(m*P+p)*IA]
            B[p][n]         B[(p*N+n)*IB]
            C[m][n]         C[(m*N+n)*IC]

        These compute:

            for (m = 0; m < M; ++m)
            for (n = 0; n < N; ++n)
                C[m][n] = sum(A[m][p] * B[p][n], 0 <= p < P);
    */


/*  Split-complex matrix multiply and add.
*/
extern void vDSP_zmma(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_D,
    vDSP_Stride            __vDSP_ID,
    vDSP_Length            __vDSP_M,
    vDSP_Length            __vDSP_N,
    vDSP_Length            __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zmmaD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_D,
    vDSP_Stride                  __vDSP_ID,
    vDSP_Length                  __vDSP_M,
    vDSP_Length                  __vDSP_N,
    vDSP_Length                  __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            Pseudocode:     Memory:
            A[m][p]         A->realp[(m*P+p)*IA] + i * A->imagp[(m*P+p)*IA].
            B[p][n]         B->realp[(p*N+n)*IB] + i * B->imagp[(p*N+n)*IB].
            C[m][n]         C->realp[(m*N+n)*IC] + i * C->imagp[(m*N+n)*IC].
            D[m][n]         D->realp[(m*N+n)*ID] + i * D->imagp[(m*N+n)*ID].

        These compute:

            for (m = 0; m < M; ++m)
            for (n = 0; n < N; ++n)
                D[m][n] = sum(A[m][p] * B[p][n], 0 <= p < P) + C[m][n];
    */


/*  Split-complex matrix multiply and subtract.
*/
extern void vDSP_zmms(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_D,
    vDSP_Stride            __vDSP_ID,
    vDSP_Length            __vDSP_M,
    vDSP_Length            __vDSP_N,
    vDSP_Length            __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zmmsD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_D,
    vDSP_Stride                  __vDSP_ID,
    vDSP_Length                  __vDSP_M,
    vDSP_Length                  __vDSP_N,
    vDSP_Length                  __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            Pseudocode:     Memory:
            A[m][p]         A->realp[(m*P+p)*IA] + i * A->imagp[(m*P+p)*IA].
            B[p][n]         B->realp[(p*N+n)*IB] + i * B->imagp[(p*N+n)*IB].
            C[m][n]         C->realp[(m*N+n)*IC] + i * C->imagp[(m*N+n)*IC].
            D[m][n]         D->realp[(m*N+n)*ID] + i * D->imagp[(m*N+n)*ID].

        These compute:

            for (m = 0; m < M; ++m)
            for (n = 0; n < N; ++n)
                D[m][n] = sum(A[m][p] * B[p][n], 0 <= p < P) - C[m][n];
    */


// Vector multiply, multiply, add, and add.
extern void vDSP_zvmmaa(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_D,
    vDSP_Stride            __vDSP_ID,
    const DSPSplitComplex *__vDSP_E,
    vDSP_Stride            __vDSP_IE,
    const DSPSplitComplex *__vDSP_F,
    vDSP_Stride            __vDSP_IF,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                F[n] = A[n] * B[n] + C[n] * D[n] + E[n];
    */


/*  Split-complex matrix multiply and reverse subtract.
*/
extern void vDSP_zmsm(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_D,
    vDSP_Stride            __vDSP_ID,
    vDSP_Length            __vDSP_M,
    vDSP_Length            __vDSP_N,
    vDSP_Length            __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zmsmD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_D,
    vDSP_Stride                  __vDSP_ID,
    vDSP_Length                  __vDSP_M,
    vDSP_Length                  __vDSP_N,
    vDSP_Length                  __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            Pseudocode:     Memory:
            A[m][p]         A->realp[(m*P+p)*IA] + i * A->imagp[(m*P+p)*IA].
            B[p][n]         B->realp[(p*N+n)*IB] + i * B->imagp[(p*N+n)*IB].
            C[m][n]         C->realp[(m*N+n)*IC] + i * C->imagp[(m*N+n)*IC].
            D[m][n]         D->realp[(m*N+n)*ID] + i * D->imagp[(m*N+n)*ID].

        These compute:

            for (m = 0; m < M; ++m)
            for (n = 0; n < N; ++n)
                D[m][n] = C[m][n] - sum(A[m][p] * B[p][n], 0 <= p < P);
    */


/*  Split-complex matrix multiply.
*/
extern void vDSP_zmmul(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_M,
    vDSP_Length            __vDSP_N,
    vDSP_Length            __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zmmulD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_M,
    vDSP_Length                  __vDSP_N,
    vDSP_Length                  __vDSP_P)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:

            Pseudocode:     Memory:
            A[m][p]         A->realp[(m*P+p)*IA] + i * A->imagp[(m*P+p)*IA].
            B[p][n]         B->realp[(p*N+n)*IB] + i * B->imagp[(p*N+n)*IB].
            C[m][n]         C->realp[(m*N+n)*IC] + i * C->imagp[(m*N+n)*IC].

        These compute:

            for (m = 0; m < M; ++m)
            for (n = 0; n < N; ++n)
                C[m][n] = sum(A[m][p] * B[p][n], 0 <= p < P);
    */


// Vector add.
extern void vDSP_vadd(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_vaddD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_vaddi(
    const int   *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const int   *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
extern void vDSP_zvadd(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zvaddD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zrvadd(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const float           *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zrvaddD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const double                *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] + B[n];
    */


// Vector subtract.
extern void vDSP_vsub(
    const float *__vDSP_B,  // Caution:  A and B are swapped!
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_A,  // Caution:  A and B are swapped!
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_vsubD(
    const double *__vDSP_B, // Caution:  A and B are swapped!
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_A, // Caution:  A and B are swapped!
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zvsub(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zvsubD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] - B[n];
    */


// Vector multiply.
extern void vDSP_vmul(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_vmulD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zrvmul(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const float           *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zrvmulD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const double                *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] * B[n];
    */


// Vector divide.
extern void vDSP_vdiv(
    const float *__vDSP_B,  // Caution:  A and B are swapped!
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_A,  // Caution:  A and B are swapped!
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vdivD(
    const double *__vDSP_B, // Caution:  A and B are swapped!
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_A, // Caution:  A and B are swapped!
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vdivi(
    const int   *__vDSP_B,  // Caution:  A and B are swapped!
    vDSP_Stride  __vDSP_IB,
    const int   *__vDSP_A,  // Caution:  A and B are swapped!
    vDSP_Stride  __vDSP_IA,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvdiv(
    const DSPSplitComplex *__vDSP_B,    // Caution:  A and B are swapped!
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_A,    // Caution:  A and B are swapped!
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvdivD(
    const DSPDoubleSplitComplex *__vDSP_B,  // Caution:  A and B are swapped!
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_A,  // Caution:  A and B are swapped!
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zrvdiv(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const float           *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zrvdivD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const double                *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] / B[n];
    */


// Vector-scalar multiply.
extern void vDSP_vsmul(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_vsmulD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] * B[0];
    */


// Vector square.
extern void vDSP_vsq(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_vsqD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n]**2;
    */



// Vector signed square.
extern void vDSP_vssq(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_vssqD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] * |A[n]|;
    */


// Euclidean distance, squared.
extern void vDSP_distancesq(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum((A[n] - B[n]) ** 2, 0 <= n < N);
    */


// Dot product.
extern void vDSP_dotpr(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_dotprD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zdotpr(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zdotprD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
extern void vDSP_zrdotpr(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const float           *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zrdotprD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const double                *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(A[n] * B[n], 0 <= n < N);
    */


// Vector add and multiply.
extern void vDSP_vam(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_vamD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_IDD,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                D[n] = (A[n] + B[n]) * C[n];
    */


// Vector multiply and add.
extern void vDSP_vma(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vmaD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvma(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_D,
    vDSP_Stride            __vDSP_ID,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                D[n] = A[n] * B[n] + C[n];
    */


// Complex multiplication with optional conjugation.
extern void vDSP_zvmul(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N,
    int                    __vDSP_Conjugate)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zvmulD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N,
    int                          __vDSP_Conjugate)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            If Conjugate is +1:

                for (n = 0; n < N; ++n)
                    C[n] = A[n] * B[n];

            If Conjugate is -1:

                for (n = 0; n < N; ++n)
                    C[n] = conj(A[n]) * B[n];
    */


// Complex-split inner (conjugate) dot product.
extern void vDSP_zidotpr(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zidotprD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(conj(A[n]) * B[n], 0 <= n < N);
    */


// Complex-split conjugate multiply and add.
extern void vDSP_zvcma(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_D,
    vDSP_Stride            __vDSP_ID,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zvcmaD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_D,
    vDSP_Stride                  __vDSP_ID,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                D[n] = conj(A[n]) * B[n] + C[n];
    */


// Subtract real from complex-split.
extern void vDSP_zrvsub(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const float           *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_4_0);
extern void vDSP_zrvsubD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const double                *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] - B[n];
    */


// Vector convert between double precision and single precision.
extern void vDSP_vdpsp(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    float        *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vspdp(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    double      *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n];
    */


// Vector absolute value.
extern void vDSP_vabs(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vabsD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vabsi(
    const int   *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvabs(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    float                 *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvabsD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    double                      *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = |A[n]|;
    */


// Vector bit-wise equivalence, NOT (A XOR B).
extern void vDSP_veqvi(
    const int   *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const int   *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = ~(A[n] ^ B[n]);
    */


// Vector fill.
extern void vDSP_vfill(
    const float *__vDSP_A,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IA,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfillD(
    const double *__vDSP_A,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfilli(
    const int   *__vDSP_A,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvfill(
    const DSPSplitComplex *__vDSP_A,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvfillD(
    const DSPDoubleSplitComplex *__vDSP_A,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[0];
    */


// Vector-scalar add.
extern void vDSP_vsadd(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsaddD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsaddi(
    const int   *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const int   *__vDSP_B,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] + B[0];
    */


// Vector-scalar divide.
extern void vDSP_vsdiv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsdivD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsdivi(
    const int   *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const int   *__vDSP_B,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] / B[0];
    */


// Complex-split accumulating autospectrum.
extern void vDSP_zaspec(
    const DSPSplitComplex *__vDSP_A,
    float                 *__vDSP_C,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zaspecD(
    const DSPDoubleSplitComplex *__vDSP_A,
    double                      *__vDSP_C,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            No strides are used; arrays map directly to memory.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] += |A[n]| ** 2;
    */


// Create Blackman window.
extern void vDSP_blkman_window(
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Flag)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_blkman_windowD(
    double      *__vDSP_C,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Flag)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            No strides are used; the array maps directly to memory.

        These compute:

            If Flag & vDSP_HALF_WINDOW:
                Length = (N+1)/2;
            Else
                Length = N;

            for (n = 0; n < Length; ++n)
            {
                angle = 2*pi*n/N;
                C[n] = .42 - .5 * cos(angle) + .08 * cos(2*angle);
            }
    */


// Coherence function.
extern void vDSP_zcoher(
    const float           *__vDSP_A,
    const float           *__vDSP_B,
    const DSPSplitComplex *__vDSP_C,
    float                 *__vDSP_D,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zcoherD(
    const double                *__vDSP_A,
    const double                *__vDSP_B,
    const DSPDoubleSplitComplex *__vDSP_C,
    double                      *__vDSP_D,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            No strides are used; arrays map directly to memory.

        These compute:

            for (n = 0; n < N; ++n)
                D[n] = |C[n]| ** 2 / (A[n] * B[n]);
    */


// Anti-aliasing down-sample with real filter.
extern void vDSP_desamp(
    const float *__vDSP_A,  // Input signal.
    vDSP_Stride  __vDSP_I,  // Sampling interval.
    const float *__vDSP_F,  // Filter.
    float       *__vDSP_C,  // Output.
    vDSP_Length  __vDSP_N,  // Output length.
    vDSP_Length  __vDSP_P)  // Filter length.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_desampD(
    const double *__vDSP_A, // Input signal.
    vDSP_Stride   __vDSP_I, // Sampling interval.
    const double *__vDSP_F, // Filter.
    double       *__vDSP_C, // Output.
    vDSP_Length   __vDSP_N, // Output length.
    vDSP_Length   __vDSP_P) // Filter length.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zrdesamp(
    const DSPSplitComplex *__vDSP_A,  // Input signal.
    vDSP_Stride            __vDSP_I,  // Sampling interval.
    const float           *__vDSP_F,  // Filter.
    const DSPSplitComplex *__vDSP_C,  // Output.
    vDSP_Length            __vDSP_N,  // Output length.
    vDSP_Length            __vDSP_P)  // Filter length.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zrdesampD(
    const DSPDoubleSplitComplex *__vDSP_A,    // Input signal.
    vDSP_Stride                  __vDSP_I,    // Sampling interval.
    const double                *__vDSP_F,    // Filter.
    const DSPDoubleSplitComplex *__vDSP_C,    // Output.
    vDSP_Length                  __vDSP_N,    // Output length.
    vDSP_Length                  __vDSP_P)    // Filter length.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            No strides are used; arrays map directly to memory.  I specifies
            a sampling interval.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = sum(A[n*I+p] * F[p], 0 <= p < P);
    */


// Transfer function, B/A.
extern void vDSP_ztrans(
    const float           *__vDSP_A,
    const DSPSplitComplex *__vDSP_B,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_ztransD(
    const double                *__vDSP_A,
    const DSPDoubleSplitComplex *__vDSP_B,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            No strides are used; arrays map directly to memory.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = B[n] / A[n];
    */


// Accumulating cross-spectrum.
extern void vDSP_zcspec(
    const DSPSplitComplex *__vDSP_A,
    const DSPSplitComplex *__vDSP_B,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zcspecD(
    const DSPDoubleSplitComplex *__vDSP_A,
    const DSPDoubleSplitComplex *__vDSP_B,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            No strides are used; arrays map directly to memory.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] += conj(A[n]) * B[n];
    */


// Vector conjugate and multiply.
extern void vDSP_zvcmul(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvcmulD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_iC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = conj(A[n]) * B[n];
    */


// Vector conjugate.
extern void vDSP_zvconj(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvconjD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = conj(A[n]);
    */


// Vector multiply with scalar.
extern void vDSP_zvzsml(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvzsmlD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] * B[0];
    */


// Vector magnitudes squared.
extern void vDSP_zvmags(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    float                 *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvmagsD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    double                      *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = |A[n]| ** 2;
    */


// Vector magnitudes square and add.
extern void vDSP_zvmgsa(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const float           *__vDSP_B,
    vDSP_Stride            __vDSP_IB,
    float                 *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvmgsaD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const double                *__vDSP_B,
    vDSP_Stride                  __vDSP_IB,
    double                      *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = |A[n]| ** 2 + B[n];
    */


// Complex-split vector move.
extern void vDSP_zvmov(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvmovD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n];
    */


// Vector negate.
extern void vDSP_zvneg(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvnegD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = -A[n];
    */


// Vector phasea.
extern void vDSP_zvphas(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    float                 *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvphasD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    double                      *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = atan2(Im(A[n]), Re(A[n]));
    */


// Vector multiply by scalar and add.
extern void vDSP_zvsma(
    const DSPSplitComplex *__vDSP_A,
    vDSP_Stride            __vDSP_IA,
    const DSPSplitComplex *__vDSP_B,
    const DSPSplitComplex *__vDSP_C,
    vDSP_Stride            __vDSP_IC,
    const DSPSplitComplex *__vDSP_D,
    vDSP_Stride            __vDSP_ID,
    vDSP_Length            __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_zvsmaD(
    const DSPDoubleSplitComplex *__vDSP_A,
    vDSP_Stride                  __vDSP_IA,
    const DSPDoubleSplitComplex *__vDSP_B,
    const DSPDoubleSplitComplex *__vDSP_C,
    vDSP_Stride                  __vDSP_IC,
    const DSPDoubleSplitComplex *__vDSP_D,
    vDSP_Stride                  __vDSP_ID,
    vDSP_Length                  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                D[n] = A[n] * B[0] + C[n];
    */


// Difference equation, 2 poles, 2 zeros.
extern void vDSP_deq22(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_deq22D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n+2] =
                    + A[n-0]*B[0]
                    + A[n-1]*B[1]
                    + A[n-2]*B[2]
                    - C[n-1]*B[3]
                    - C[n-2]*B[4];
    */


// Create Hamming window.
extern void vDSP_hamm_window(
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Flag)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_hamm_windowD(
    double      *__vDSP_C,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Flag)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            No strides are used; the array maps directly to memory.

        These compute:

            If Flag & vDSP_HALF_WINDOW:
                Length = (N+1)/2;
            Else
                Length = N;

            for (n = 0; n < Length; ++n)
                C[n] = .54 - .46 * cos(2*pi*n/N);
    */


// Create Hanning window.
extern void vDSP_hann_window(
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Flag)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_hann_windowD(
    double      *__vDSP_C,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Flag)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            No strides are used; the array maps directly to memory.

        These compute:

            If Flag & vDSP_HALF_WINDOW:
                Length = (N+1)/2;
            Else
                Length = N;

            If Flag & vDSP_HANN_NORM:
                W = .8165;
            Else
                W = .5;

            for (n = 0; n < Length; ++n)
                C[n] = W * (1 - cos(2*pi*n/N));
    */


// Maximum magnitude of vector.
extern void vDSP_maxmgv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_maxmgvD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        C[0] is set to the greatest value of |A[n]| for 0 <= n < N.
    */


// Maximum magnitude of vector.
extern void vDSP_maxmgvi(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length *__vDSP_I,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_maxmgviD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length  *__vDSP_I,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        C[0] is set to the greatest value of |A[n]| for 0 <= n < N.
        I[0] is set to the least i*IA such that |A[i]| has the value in C[0].
    */


// Maximum value of vector.
extern void vDSP_maxv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_maxvD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_I,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        C[0] is set to the greatest value of A[n] for 0 <= n < N.
    */


// Maximum value of vector, with index.
extern void vDSP_maxvi(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length *__vDSP_I,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_maxviD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length  *__vDSP_I,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        C[0] is set to the greatest value of A[n] for 0 <= n < N.
        I[0] is set to the least i*IA such that A[i] has the value in C[0].
    */


// Mean magnitude of vector.
extern void vDSP_meamgv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_meamgvD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(|A[n]|, 0 <= n < N) / N;
    */


// Mean of vector.
extern void vDSP_meanv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_meanvD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(A[n], 0 <= n < N) / N;
    */


// Mean square of vector.
extern void vDSP_measqv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_measqvD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_I,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(A[n]**2, 0 <= n < N) / N;
    */


// Minimum magnitude of vector.
extern void vDSP_minmgv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_minmgvD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        C[0] is set to the least value of |A[n]| for 0 <= n < N.
    */


// Minimum magnitude of vector, with index.
extern void vDSP_minmgvi(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length *__vDSP_I,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_minmgviD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length  *__vDSP_I,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        C[0] is set to the least value of |A[n]| for 0 <= n < N.
        I[0] is set to the least i*IA such that |A[i]| has the value in C[0].
    */


// Minimum value of vector.
extern void vDSP_minv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_minvD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        C[0] is set to the least value of A[n] for 0 <= n < N.
    */


// Minimum value of vector, with index.
extern void vDSP_minvi(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length *__vDSP_I,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_minviD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length  *__vDSP_I,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        C[0] is set to the least value of A[n] for 0 <= n < N.
        I[0] is set to the least i*IA such that A[i] has the value in C[0].
    */


// Matrix move.
extern void vDSP_mmov(
    const float *__vDSP_A,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_M,
    vDSP_Length  __vDSP_N,
    vDSP_Length  __vDSP_TA,
    vDSP_Length  __vDSP_TC)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_mmovD(
    const double *__vDSP_A,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_M,
    vDSP_Length   __vDSP_N,
    vDSP_Length   __vDSP_TA,
    vDSP_Length   __vDSP_TC)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:

            This routine does not have strides.

            A is regarded as a two-dimensional matrix with dimensions [N][TA].
            C is regarded as a two-dimensional matrix with dimensions [N][TC].

        These compute:

            for (n = 0; n < N; ++n)
            for (m = 0; m < M; ++m)
                C[n][m] = A[n][m];
    */


// Mean of signed squares of vector.
extern void vDSP_mvessq(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_mvessqD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(A[n] * |A[n]|, 0 <= n < N) / N;
    */


// Find zero crossing.
extern void vDSP_nzcros(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    vDSP_Length  __vDSP_B,
    vDSP_Length *__vDSP_C,
    vDSP_Length *__vDSP_D,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_nzcrosD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    vDSP_Length   __vDSP_B,
    vDSP_Length  *__vDSP_C,
    vDSP_Length  *__vDSP_D,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        Let S be the number of times the sign bit changes in the sequence A[0],
        A[1],... A[N-1].

        If B <= S:
            D[0] is set to B.
            C[0] is set to n*IA, where the B-th sign bit change occurs between
            elements A[n-1] and A[n].
        Else:
            D[0] is set to S.
            C[0] is set to 0.
    */


// Convert rectangular to polar.
extern void vDSP_polar(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_polarD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  Strides are shown explicitly in pseudocode.

        These compute:

            for (n = 0; n < N; ++n)
            {
                x = A[n*IA+0];
                y = A[n*IA+1];
                C[n*IC+0] = sqrt(x**2 + y**2);
                C[n*IC+1] = atan2(y, x);
            }
    */


// Convert polar to rectangular.
extern void vDSP_rect(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_rectD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  Strides are shown explicitly in pseudocode.

        These compute:

            for (n = 0; n < N; ++n)
            {
                r     = A[n*IA+0];
                theta = A[n*IA+1];
                C[n*IC+0] = r * cos(theta);
                C[n*IC+1] = r * sin(theta);
            }
    */


// Root-mean-square of vector.
extern void vDSP_rmsqv(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_rmsqvD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sqrt(sum(A[n] ** 2, 0 <= n < N) / N);
    */


// Scalar-vector divide.
extern void vDSP_svdiv(
    const float *__vDSP_A,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_svdivD(
    const double *__vDSP_A,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[0] / B[n];
    */


// Sum of vector elements.
extern void vDSP_sve(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_I,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_sveD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_I,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(A[n], 0 <= n < N);
    */


// Sum of vector elements magnitudes.
extern void vDSP_svemg(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_svemgD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(|A[n]|, 0 <= n < N);
    */


// Sum of vector elements' squares.
extern void vDSP_svesq(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_svesqD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(A[n] ** 2, 0 <= n < N);
    */


// Sum of vector elements and sum of vector elements' squares.
extern void vDSP_sve_svesq(
    const float  *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    float        *__vDSP_Sum,
    float        *__vDSP_SumOfSquares,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
extern void vDSP_sve_svesqD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_Sum,
    double       *__vDSP_SumOfSquares,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
    /*  Maps:  The default maps are used.

        These compute:

            Sum[0]          = sum(A[n],      0 <= n < N);
            SumOfSquares[0] = sum(A[n] ** 2, 0 <= n < N);
    */


// Normalize elements to zero mean and unit standard deviation.
extern void vDSP_normalize(
    const float  *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    float        *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    float        *__vDSP_Mean,
    float        *__vDSP_StandardDeviation,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
extern void vDSP_normalizeD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    double       *__vDSP_Mean,
    double       *__vDSP_StandardDeviation,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
    /*  Maps:  The default maps are used.

        These compute:

            // Calculate mean and standard deviation.
            m = sum(A[n], 0 <= n < N) / N;
            d = sqrt(sum(A[n]**2, 0 <= n < N) / N - m**2);

            // Normalize.
            for (n = 0; n < N; ++n)
                C[n] = (A[n] - m) / d;
    */


// Sum of vector elements' signed squares.
extern void vDSP_svs(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_svsD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            C[0] = sum(A[n] * |A[n]|, 0 <= n < N);
    */


// Vector add, add, and multiply.
extern void vDSP_vaam(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    const float *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    float       *__vDSP_E,
    vDSP_Stride  __vDSP_IE,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vaamD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    const double *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    double       *__vDSP_E,
    vDSP_Stride   __vDSP_IE,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                E[n] = (A[n] + B[n]) * (C[n] + D[n]);
    */


// Vector add, subtract, and multiply.
extern void vDSP_vasbm(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    const float *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    float       *__vDSP_E,
    vDSP_Stride  __vDSP_IE,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vasbmD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    const double *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    double       *__vDSP_E,
    vDSP_Stride   __vDSP_IE,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                E[n] = (A[n] + B[n]) * (C[n] - D[n]);
    */


// Vector add and scalar multiply.
extern void vDSP_vasm(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vasmD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                D[n] = (A[n] + B[n]) * C[0];
    */


// Vector linear average.
extern void vDSP_vavlin(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vavlinD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = (C[n]*B[0] + A[n]) / (B[0] + 1);
    */


// Vector clip.
extern void vDSP_vclip(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vclipD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
            {
                D[n] = A[n];
                if (D[n] < B[0]) D[n] = B[0];
                if (C[0] < D[n]) D[n] = C[0];
            }
    */


// Vector clip and count.
extern void vDSP_vclipc(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N,
    vDSP_Length *__vDSP_NLow,
    vDSP_Length *__vDSP_NHigh)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vclipcD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N,
    vDSP_Length  *__vDSP_NLow,
    vDSP_Length  *__vDSP_NHigh)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            NLow[0]  = 0;
            NHigh[0] = 0;
            for (n = 0; n < N; ++n)
            {
                D[n] = A[n];
                if (D[n] < B[0]) { D[n] = B[0]; ++NLow[0];  }
                if (C[0] < D[n]) { D[n] = C[0]; ++NHigh[0]; }
            }
    */


// Vector clear.
extern void vDSP_vclr(
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vclrD(
    double      *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = 0;
    */


// Vector compress.
extern void vDSP_vcmprs(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vcmprsD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            p = 0;
            for (n = 0; n < N; ++n)
                if (B[n] != 0)
                    C[p++] = A[n];
    */


// Vector convert to decibels, power, or amplitude.
extern void vDSP_vdbcon(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N,
    unsigned int __vDSP_F)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vdbconD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N,
    unsigned int  __vDSP_F)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            If Flag is 1:
                alpha = 20;
            If Flag is 0:
                alpha = 10;

            for (n = 0; n < N; ++n)
                C[n] = alpha * log10(A[n] / B[0]);
    */


// Vector distance.
extern void vDSP_vdist(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_I,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_J,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_K,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vdistD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_I,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_J,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_K,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = sqrt(A[n]**2 + B[n]**2);
    */


// Vector envelope.
extern void vDSP_venvlp(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_venvlpD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
            {
                if (D[n] < B[n] || A[n] < D[n]) D[n] = C[n];
                else D[n] = 0;
            }
    */


// Vector convert to integer, round toward zero.
extern void vDSP_vfix8(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    char        *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfix8D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    char         *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfix16(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    short       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfix16D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    short        *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfix32(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfix32D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    int          *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixu8(
    const float   *__vDSP_A,
    vDSP_Stride    __vDSP_IA,
    unsigned char *__vDSP_C,
    vDSP_Stride    __vDSP_IC,
    vDSP_Length    __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixu8D(
    const double  *__vDSP_A,
    vDSP_Stride    __vDSP_IA,
    unsigned char *__vDSP_C,
    vDSP_Stride    __vDSP_IC,
    vDSP_Length    __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixu16(
    const float    *__vDSP_A,
    vDSP_Stride     __vDSP_IA,
    unsigned short *__vDSP_C,
    vDSP_Stride     __vDSP_IC,
    vDSP_Length     __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixu16D(
    const double   *__vDSP_A,
    vDSP_Stride     __vDSP_IA,
    unsigned short *__vDSP_C,
    vDSP_Stride     __vDSP_IC,
    vDSP_Length     __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixu32(
    const float  *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    unsigned int *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixu32D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    unsigned int *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = trunc(A[n]);
    */

// Vector convert single precision to 24 bit integer with pre-scaling.
// The scaled value is rounded toward zero.
extern void vDSP_vsmfixu24(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_uint24 *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
    
// Vector convert single precision to 24 bit unsigned integer with pre-scaling.
// The scaled value is rounded toward zero.
extern void vDSP_vsmfix24(
   const float *__vDSP_A,
   vDSP_Stride  __vDSP_IA,
   const float *__vDSP_B,
   vDSP_int24  *__vDSP_C,
   vDSP_Stride  __vDSP_IC,
   vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
/*  Maps:  The default maps are used.
 
 These compute:
 
    for (n = 0; n < N; ++n)
        C[n] = trunc(A[n] * B[0]);
 
 Note: Values outside the representable range are clamped to the largest or smallest
        representable values of the destination type.
 */
    
// Vector convert unsigned 24 bit integer to single precision float
extern void vDSP_vfltu24(
   const vDSP_uint24 *__vDSP_A,
   vDSP_Stride       __vDSP_IA,
   float             *__vDSP_C,
   vDSP_Stride       __vDSP_IC,
   vDSP_Length       __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);

// Vector convert 24 bit integer to single precision float
extern void vDSP_vflt24(
  const vDSP_int24 *__vDSP_A,
  vDSP_Stride      __vDSP_IA,
  float            *__vDSP_C,
  vDSP_Stride      __vDSP_IC,
  vDSP_Length      __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
/*  Maps:  The default maps are used.
 
    These compute:
 
        for (n = 0; n < N; ++n)
            C[n] = A[n];
 */
    
// Vector convert unsigned 24 bit integer to single precision float and scale
extern void vDSP_vfltsmu24(
     const vDSP_uint24 *__vDSP_A,
     vDSP_Stride       __vDSP_IA,
     const float       *__vDSP_B,
     float             *__vDSP_C,
     vDSP_Stride       __vDSP_IC,
     vDSP_Length       __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
    
// Vector convert 24 bit integer to single precision float and scale
extern void vDSP_vfltsm24(
    const vDSP_int24 *__vDSP_A,
    vDSP_Stride      __vDSP_IA,
    const float      *__vDSP_B,
    float            *__vDSP_C,
    vDSP_Stride      __vDSP_IC,
    vDSP_Length      __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
/*  Maps:  The default maps are used.
 
    These compute:
 
        for (n = 0; n < N; ++n)
            C[n] = B[0] * (float)A[n];
 */
    
// Vector convert to integer, round to nearest.
extern void vDSP_vfixr8(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    char        *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixr8D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    char         *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixr16(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    short       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixr16D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    short        *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixr32(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    int         *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixr32D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    int          *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixru8(
    const float   *__vDSP_A,
    vDSP_Stride    __vDSP_IA,
    unsigned char *__vDSP_C,
    vDSP_Stride    __vDSP_IC,
    vDSP_Length    __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixru8D(
    const double  *__vDSP_A,
    vDSP_Stride    __vDSP_IA,
    unsigned char *__vDSP_C,
    vDSP_Stride    __vDSP_IC,
    vDSP_Length    __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixru16(
    const float    *__vDSP_A,
    vDSP_Stride     __vDSP_IA,
    unsigned short *__vDSP_C,
    vDSP_Stride     __vDSP_IC,
    vDSP_Length     __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixru16D(
    const double   *__vDSP_A,
    vDSP_Stride     __vDSP_IA,
    unsigned short *__vDSP_C,
    vDSP_Stride     __vDSP_IC,
    vDSP_Length     __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixru32(
    const float  *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    unsigned int *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfixru32D(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    unsigned int *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = rint(A[n]);

        Note:  It is expected that the global rounding mode be the default,
        round-to-nearest.  It is unspecified whether ties round up or down.
    */


// Vector convert from it integer.
extern void vDSP_vflt8(
    const char  *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vflt8D(
    const char  *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    double      *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vflt16(
    const short *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vflt16D(
    const short *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    double      *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vflt32(
    const int   *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vflt32D(
    const int   *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    double      *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfltu8(
    const unsigned char *__vDSP_A,
    vDSP_Stride          __vDSP_IA,
    float               *__vDSP_C,
    vDSP_Stride          __vDSP_IC,
    vDSP_Length          __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfltu8D(
    const unsigned char *__vDSP_A,
    vDSP_Stride          __vDSP_IA,
    double              *__vDSP_C,
    vDSP_Stride          __vDSP_IC,
    vDSP_Length          __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfltu16(
    const unsigned short *__vDSP_A,
    vDSP_Stride           __vDSP_IA,
    float                *__vDSP_C,
    vDSP_Stride           __vDSP_IC,
    vDSP_Length           __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfltu16D(
    const unsigned short *__vDSP_A,
    vDSP_Stride           __vDSP_IA,
    double               *__vDSP_C,
    vDSP_Stride           __vDSP_IC,
    vDSP_Length           __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfltu32(
    const unsigned int *__vDSP_A,
    vDSP_Stride         __vDSP_IA,
    float              *__vDSP_C,
    vDSP_Stride         __vDSP_IC,
    vDSP_Length         __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfltu32D(
    const unsigned int *__vDSP_A,
    vDSP_Stride         __vDSP_IA,
    double             *__vDSP_C,
    vDSP_Stride         __vDSP_IC,
    vDSP_Length         __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n];
    */


// Vector fraction part (subtract integer toward zero).
extern void vDSP_vfrac(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vfracD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] - trunc(A[n]);
    */


// Vector gather.
extern void vDSP_vgathr(
    const float       *__vDSP_A,
    const vDSP_Length *__vDSP_B,
    vDSP_Stride        __vDSP_IB,
    float             *__vDSP_C,
    vDSP_Stride        __vDSP_IC,
    vDSP_Length        __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vgathrD(
    const double      *__vDSP_A,
    const vDSP_Length *__vDSP_B,
    vDSP_Stride        __vDSP_IB,
    double            *__vDSP_C,
    vDSP_Stride        __vDSP_IC,
    vDSP_Length        __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.  Note that A has unit stride.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[B[n] - 1];
    */


// Vector gather, absolute pointers.
extern void vDSP_vgathra(
    const float **__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    float        *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vgathraD(
    const double **__vDSP_A,
    vDSP_Stride    __vDSP_IA,
    double        *__vDSP_C,
    vDSP_Stride    __vDSP_IC,
    vDSP_Length    __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = *A[n];
    */


// Vector generate tapered ramp.
extern void vDSP_vgen(
    const float *__vDSP_A,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vgenD(
    const double *__vDSP_A,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[0] + (B[0] - A[0]) * n/(N-1);
    */


// Vector generate by extrapolation and interpolation.
extern void vDSP_vgenp(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N,
    vDSP_Length  __vDSP_M)  // Length of A and of B.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vgenpD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N,
    vDSP_Length   __vDSP_M)  // Length of A and of B.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                If n <= B[0],  then C[n] = A[0].
                If B[M-1] < n, then C[n] = A[M-1].
                Otherwise:
                    Let m be such that B[m] < n <= B[m+1].
                    C[n] = A[m] + (A[m+1]-A[m]) * (n-B[m]) / (B[m+1]-B[m]).

         The elements of B are expected to be in increasing order.
    */


// Vector inverted clip.
extern void vDSP_viclip(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_viclipD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
            {
                if (A[n] <= B[0] || C[0] <= A[n])
                    D[n] = A[n];
                else
                    if (A[n] < 0)
                        D[n] = B[0];
                    else
                        D[n] = C[0];
            }
    */


// Vector index, C[i] = A[truncate[B[i]].
extern void vDSP_vindex(
    const float *__vDSP_A,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vindexD(
    const double *__vDSP_A,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[trunc(B[n])];
    */


// Vector interpolation between vectors.
extern void vDSP_vintb(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vintbD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                D[n] = A[n] + C[0] * (B[n] - A[n]);
    */


// Vector test limit.
extern void vDSP_vlim(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vlimD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                if (B[0] <= A[n])
                    D[n] = +C[0];
                else
                    D[n] = -C[0];
    */


// Vector linear interpolation.
extern void vDSP_vlint(
    const float *__vDSP_A,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N,
    vDSP_Length  __vDSP_M)  // Nominal length of A, but not used.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vlintD(
    const double *__vDSP_A,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N,
    vDSP_Length   __vDSP_M)  // Nominal length of A, but not used.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
            {
                b = trunc(B[n]);
                a = B[n] - b;
                C[n] = A[b] + a * (A[b+1] - A[b]);
            }
    */


// Vector maxima.
extern void vDSP_vmax(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vmaxD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = B[n] <= A[n] ? A[n] : B[n];
    */


// Vector maximum magnitude.
extern void vDSP_vmaxmg(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vmaxmgD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = |B[n]| <= |A[n]| ? |A[n]| : |B[n]|;
    */


// Vector minima.
extern void vDSP_vmin(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vminD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] <= B[n] ? A[n] : B[n];
    */


// Vector minimum magnitude.
extern void vDSP_vminmg(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vminmgD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.

        These compute:

            for (n = 0; n < N; ++n)
                C[n] = |A[n]| <= |B[n]| ? |A[n]| : |B[n]|;
    */


// Vector multiply, multiply, and add.
extern void vDSP_vmma(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    const float *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    float       *__vDSP_E,
    vDSP_Stride  __vDSP_IE,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vmmaD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    const double *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    double       *__vDSP_E,
    vDSP_Stride   __vDSP_IE,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                E[n] = A[n]*B[n] + C[n]*D[n];
    */


// Vector multiply, multiply, and subtract.
extern void vDSP_vmmsb(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    const float *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    float       *__vDSP_E,
    vDSP_Stride  __vDSP_IE,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vmmsbD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    const double *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    double       *__vDSP_E,
    vDSP_Stride   __vDSP_IE,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                E[n] = A[n]*B[n] - C[n]*D[n];
    */


// Vector multiply and scalar add.
extern void vDSP_vmsa(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vmsaD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                D[n] = A[n]*B[n] + C[0];
    */


// Vector multiply and subtract.
extern void vDSP_vmsb(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vmsbD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                D[n] = A[n]*B[n] - C[n];
    */


// Vector negative absolute value.
extern void vDSP_vnabs(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vnabsD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                C[n] = -|A[n]|;
    */


// Vector negate.
extern void vDSP_vneg(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vnegD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                C[n] = -A[n];
    */


// Vector polynomial.
extern void vDSP_vpoly(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N,
    vDSP_Length  __vDSP_P)  // P is the polynomial degree.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vpolyD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N,
    vDSP_Length   __vDSP_P)  // P is the polynomial degree.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                C[n] = sum(A[P-p] * B[n]**p, 0 <= p <= P);
    */


// Vector Pythagoras.
extern void vDSP_vpythg(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    const float *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    float       *__vDSP_E,
    vDSP_Stride  __vDSP_IE,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vpythgD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    const double *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    double       *__vDSP_E,
    vDSP_Stride   __vDSP_IE,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                E[n] = sqrt((A[n]-C[n])**2 + (B[n]-D[n])**2);
    */


// Vector quadratic interpolation.
extern void vDSP_vqint(
    const float *__vDSP_A,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N,
    vDSP_Length  __vDSP_M)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vqintD(
    const double *__vDSP_A,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N,
    vDSP_Length   __vDSP_M)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
            {
                b = max(trunc(B[n]), 1);
                a = B[n] - b;
                C[n] = (A[b-1]*(a**2-a) + A[b]*(2-2*a**2) + A[b+1]*(a**2+a))
                    / 2;
            }
    */


// Vector build ramp.
extern void vDSP_vramp(
    const float *__vDSP_A,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vrampD(
    const double *__vDSP_A,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[0] + n*B[0];
    */


// Vector running sum integration.
extern void vDSP_vrsum(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_S,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vrsumD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_S,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                C[n] = S[0] * sum(A[j], 0 < j <= n);

        Observe that C[0] is set to 0, and A[0] is not used.
    */


// Vector reverse order, in-place.
extern void vDSP_vrvrs(
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vrvrsD(
    double      *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            Let A contain a copy of C.
            for (n = 0; n < N; ++n)
                C[n] = A[N-1-n];
    */


// Vector subtract and multiply.
extern void vDSP_vsbm(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsbmD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                D[n] = (A[n] - B[n]) * C[n];
    */


// Vector subtract, subtract, and multiply.
extern void vDSP_vsbsbm(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    const float *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    float       *__vDSP_E,
    vDSP_Stride  __vDSP_IE,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsbsbmD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    const double *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    double       *__vDSP_E,
    vDSP_Stride   __vDSP_IE,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                C[n] = (A[n] - B[n]) * (C[n] - D[n]);
    */


// Vector subtract and scalar multiply.
extern void vDSP_vsbsm(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsbsmD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                D[n] = (A[n] - B[n]) * C[0];
    */


// Vector Simpson integration.
extern void vDSP_vsimps(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsimpsD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            C[0] = 0;
            C[1] = B[0] * (A[0] + A[1])/2;
            for (n = 2; n < N; ++n)
                C[n] = C[n-2] + B[0] * (A[n-2] + 4*A[n-1] + A[n])/3;
    */


// Vector-scalar multiply and vector add.
extern void vDSP_vsma(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsmaD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                D[n] = A[n]*B[0] + C[n];
    */


// Vector-scalar multiply and scalar add.
extern void vDSP_vsmsa(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsmsaD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    const double *__vDSP_C,
    double       *__vDSP_ID,
    vDSP_Stride   __vDSP_L,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                D[n] = A[n]*B[0] + C[0];
    */


// Vector scalar multiply and vector subtract.
extern void vDSP_vsmsb(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_I,
    const float *__vDSP_B,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_K,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_L,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsmsbD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_I,
    const double *__vDSP_B,
    const double *__vDSP_C,
    vDSP_Stride   __vDSP_K,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_L,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                D[n] = A[n]*B[0] - C[n];
    */


// Vector-scalar multiply, vector-scalar multiply and vector add.
extern void vDSP_vsmsma(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    const float *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    const float *__vDSP_D,
    float       *__vDSP_E,
    vDSP_Stride  __vDSP_IE,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
    /*  Maps:  The default maps are used.
        
        This computes:

            for (n = 0; n < N; ++n)
                E[n] = A[n]*B[0] + C[n]*D[0];
    */


// Vector sort, in-place.
extern void vDSP_vsort(
    float       *__vDSP_C,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Order)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsortD(
    double      *__vDSP_C,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Order)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  If Order is +1, C is sorted in ascending order.
        If Order is -1, C is sorted in descending order.
    */


// Vector sort indices, in-place.
extern void vDSP_vsorti(
    const float *__vDSP_C,
    vDSP_Length *__vDSP_I,
    vDSP_Length *__vDSP_Temporary,
    vDSP_Length  __vDSP_N,
    int          __vDSP_Order)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vsortiD(
    const double *__vDSP_C,
    vDSP_Length  *__vDSP_I,
    vDSP_Length  *__vDSP_Temporary,
    vDSP_Length   __vDSP_N,
    int           __vDSP_Order)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  No strides are used; arrays map directly to memory.

        I contains indices into C.
        
        If Order is +1, I is sorted so that C[I[n]] increases, for 0 <= n < N.
        If Order is -1, I is sorted so that C[I[n]] decreases, for 0 <= n < N.

        Temporary is not used.  NULL should be passed for it.
    */


// Vector swap.
extern void vDSP_vswap(
    float       *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vswapD(
    double      *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    double      *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                A[n] is swapped with B[n].
    */


// Vector sliding window sum.
extern void vDSP_vswsum(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N,
    vDSP_Length  __vDSP_P) // Length of window.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vswsumD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N,
    vDSP_Length   __vDSP_P) // Length of window.
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                C[n] = sum(A[n+p], 0 <= p < P);

        Note that A must contain N+P-1 elements.
    */


// Vector table lookup and interpolation.
extern void vDSP_vtabi(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_S1,
    const float *__vDSP_S2,
    const float *__vDSP_C,
    vDSP_Length  __vDSP_M,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vtabiD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_S1,
    const double *__vDSP_S2,
    const double *__vDSP_C,
    vDSP_Length   __vDSP_M,
    double       *__vDSP_ID,
    vDSP_Stride   __vDSP_L,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
            {
                p = S1[0] * A[n] + S2[0];
                if (p < 0)
                    D[n] = C[0];
                else if (p < M-1)
                {
                    q = trunc(p);
                    r = p-q;
                    D[n] = (1-r)*C[q] + r*C[q+1];
                }
                else
                    D[n] = C[M-1];
            }
    */


// Vector threshold.
extern void vDSP_vthr(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vthrD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                if (B[0] <= A[n])
                    C[n] = A[n];
                else
                    C[n] = B[0];
    */


// Vector threshold with zero fill.
extern void vDSP_vthres(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vthresD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                if (B[0] <= A[n])
                    C[n] = A[n];
                else
                    C[n] = 0;
    */


// Vector threshold with signed constant.
extern void vDSP_vthrsc(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    const float *__vDSP_C,
    float       *__vDSP_D,
    vDSP_Stride  __vDSP_ID,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vthrscD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    const double *__vDSP_C,
    double       *__vDSP_D,
    vDSP_Stride   __vDSP_ID,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                if (B[0] <= A[n])
                    D[n] = +C[0];
                else
                    D[n] = -C[0];
    */


// Vector tapered merge.
extern void vDSP_vtmerg(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    vDSP_Stride  __vDSP_IB,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vtmergD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    vDSP_Stride   __vDSP_IB,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            for (n = 0; n < N; ++n)
                C[n] = A[n] + (B[n] - A[n]) * n/(N-1);
    */


// Vector trapezoidal integration.
extern void vDSP_vtrapz(
    const float *__vDSP_A,
    vDSP_Stride  __vDSP_IA,
    const float *__vDSP_B,
    float       *__vDSP_C,
    vDSP_Stride  __vDSP_IC,
    vDSP_Length  __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_vtrapzD(
    const double *__vDSP_A,
    vDSP_Stride   __vDSP_IA,
    const double *__vDSP_B,
    double       *__vDSP_C,
    vDSP_Stride   __vDSP_IC,
    vDSP_Length   __vDSP_N)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
    /*  Maps:  The default maps are used.
        
        These compute:

            C[0] = 0;
            for (n = 1; n < N; ++n)
                C[n] = C[n-1] + B[0] * (A[n-1] + A[n])/2;
    */


// Wiener Levinson.
extern void vDSP_wiener(
    vDSP_Length  __vDSP_L,
    const float *__vDSP_A,
    const float *__vDSP_C,
    float       *__vDSP_F,
    float       *__vDSP_P,
    int          __vDSP_Flag,
    int         *__vDSP_Error)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);
extern void vDSP_wienerD(
    vDSP_Length   __vDSP_L,
    const double *__vDSP_A,
    const double *__vDSP_C,
    double       *__vDSP_F,
    double       *__vDSP_P,
    int           __vDSP_Flag,
    int          *__vDSP_Error)
        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/*  vDSP_FFT16_copv and vDSP_FFT32_copv perform 16- and 32-element FFTs on
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


/*  vDSP_FFT16_zopv and vDSP_FFT32_zopv perform 16- and 32-element FFTs on
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


/*  How to use the Discrete Fourier Transform (DFT) and Discrete Cosine
    Transform (DCT) interfaces.

    There are three steps to performing a DFT or DCT:

        Call a setup routine (e.g., vDSP_DFT_zop_CreateSetup) to get a setup
        object.

            This is a preparation step to be done when a program is starting or
            is starting some new phase (e.g., when a communication channel is
            opened).  It should never be done during real-time processing.  The
            setup routine is slow and is called only once to prepare data that
            can be used many times.

        Call an execution routine (e.g., vDSP_DFT_Execute or vDSP_DCT_Execute)
        to perform a DFT or DCT, and pass it the setup object.

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

            vDSP_DCT_CreateSetup, vDSP_DCT_Execute, vDSP_DFT_DestroySetup;

            vDSP_DFT_CreateSetup, vDSP_DFT_zop, vDSP_DFT_DestroySetup.

        Sharing DFT and DCT setups:

            Any setup returned by a DFT or DCT setup routine may be passed as
            input to any DFT or DCT setup routine, in the parameter named
            Previous.  (This allows the setups to share data, avoiding
            unnecessary duplication of some setup data.)  Setup routines may be
            executed in any order.  Passing any setup of a group of setups
            sharing data will result in a new setup sharing data with all of
            the group.

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

        Never call a setup or destroy routine in a thread when any DFT or DCT
        routine (setup, execution, or destroy) that shares setup data may be
        executing.  (This applies not just to multiple threads but also to
        calling DFT or DCT routines in signal handlers.)

        Multiple DFT or DCT execution routines may be called simultaneously.
        (Their access to the setup data is read-only.)

        If you need to call setup and/or destroy routines while other DFT or
        DCT routines might be executing, you can either use Grand Central
        Dispatch or locks (costs time) to avoid simultaneous execution or you
        can create separate setup objects for them (costs memory).
*/


/*  A vDSP_DFT_Setup object is a pointer to a structure whose definition is
    unpublished.
*/
typedef struct vDSP_DFT_SetupStruct  *vDSP_DFT_Setup;
typedef struct vDSP_DFT_SetupStructD *vDSP_DFT_SetupD;


// DFT direction may be specified as vDSP_DFT_FORWARD or vDSP_DFT_INVERSE.
typedef enum { vDSP_DFT_FORWARD = +1, vDSP_DFT_INVERSE = -1 }
    vDSP_DFT_Direction;


/*  vDSP_DFT_CreateSetup is a DFT setup routine.  It creates a setup object
    for use with the vDSP_DFT_zop execution routine.  We recommend you use
    vDSP_DFT_zop_CreateSetup instead of this routine.

    Parameters:

        vDSP_DFT_Setup Previous

            Previous is either zero or a previous DFT or DCT setup.  If a
            previous setup is passed, the new setup will share data with the
            previous setup, if feasible (and with any other setups the previous
            setup shares with).  If zero is passed, the routine will allocate
            and initialize new memory.

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


/*  vDSP_DFT_zop_CreateSetup is a DFT setup routine.  It creates a setup object
    for use with the vDSP_DFT_Execute execution routine, to perform a
    complex-to-complex DFT.

    Parameters:

        vDSP_DFT_Setup Previous

            Previous is either zero or a previous DFT or DCT setup.  If a
            previous setup is passed, the new setup will share data with the
            previous setup, if feasible (and with any other setups the previous
            setup shares with).  If zero is passed, the routine will allocate
            and initialize new memory.

        vDSP_Length Length

            Length is the number of complex elements to be transformed.

        vDSP_DFT_Direction Direction

            Transform direction, vDSP_DFT_FORWARD or vDSP_DFT_INVERSE.

    Return value:

        Zero is returned if memory is unavailable or if there is no
        implementation for the requested case.  Currently, the implemented
        cases are:

            Length = 2**n.

            Length = f * 2**n, where f is 3, 5, or 15 and 3 <= n.

        Additionally, it is recommended that the array addresses (passed to
        vDSP_DFT_Execute) be 16-byte aligned.  For other cases, performance may
        be slightly or greatly worse, depending on transform length and
        processor model.

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

        Performance is good when the array addresses (passed to
        vDSP_DFT_Execute) are 16-byte aligned.  Other alignments are supported,
        but performance may be significantly worse in some cases, depending on
        the processor model or the transform length (because different
        algorithms are used for different forms of transform length).

    In-Place Operation:

        Or may equal Ir and Oi may equal Ii (in the call to vDSP_DFT_Execute).
        Otherwise, no overlap of Or, Oi, Ir, and Ii is supported.

    The returned setup object may be used only with vDSP_DFT_Execute for the
    length given during setup.  Unlike previous vDSP FFT routines, the setup
    may not be used to execute transforms with shorter lengths.

    Do not call this routine while any DFT or DCT routine sharing setup data
    might be executing.
*/
vDSP_DFT_Setup vDSP_DFT_zop_CreateSetup(vDSP_DFT_Setup __vDSP_Previous,
    vDSP_Length __vDSP_Length, vDSP_DFT_Direction __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_0);
vDSP_DFT_SetupD vDSP_DFT_zop_CreateSetupD(vDSP_DFT_SetupD __vDSP_Previous,
    vDSP_Length __vDSP_Length, vDSP_DFT_Direction __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);

/*  vDSP_DFT_zrop_CreateSetup is a DFT setup routine.  It creates a setup
    object for use with the vDSP_DFT_Execute execution routine, to perform a
    real-to-complex DFT or a complex-to-real DFT.

    Parameters:

        vDSP_DFT_Setup Previous

            Previous is either zero or a previous DFT or DCT setup.  If a
            previous setup is passed, the new setup will share data with the
            previous setup, if feasible (and with any other setups the previous
            setup shares with).  If zero is passed, the routine will allocate
            and initialize new memory.

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

            Length = 2**n.

            Length = f * 2**n, where f is 3, 5, or 15 and 4 <= n.

        Additionally, it is recommended that the array addresses (passed to
        vDSP_DFT_Execute) be 16-byte aligned.  For other cases, performance may
        be slightly or greatly worse, depending on transform length and
        processor model.

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

        Performance is good when the array addresses (passed to
        vDSP_DFT_Execute) are 16-byte aligned.  Other alignments are supported,
        but performance may be significantly worse in some cases, depending on
        the processor model or the transform length (because different
        algorithms are used for different forms of transform length).

    In-Place Operation:

        Or may equal Ir and Oi may equal Ii (in the call to vDSP_DFT_Execute).
        Otherwise, no overlap of Or, Oi, Ir, and Ii is supported.

    The returned setup object may be used only with vDSP_DFT_Execute for the
    length given during setup.  Unlike previous vDSP FFT routines, the setup
    may not be used to execute transforms with shorter lengths.

    Do not call this routine while any DFT routine sharing setup data might be
    executing.
*/
vDSP_DFT_Setup vDSP_DFT_zrop_CreateSetup(vDSP_DFT_Setup __vDSP_Previous,
    vDSP_Length __vDSP_Length, vDSP_DFT_Direction __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_0);
vDSP_DFT_SetupD vDSP_DFT_zrop_CreateSetupD(vDSP_DFT_SetupD __vDSP_Previous,
    vDSP_Length __vDSP_Length, vDSP_DFT_Direction __vDSP_Direction)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);


/*  vDSP_DFT_DestroySetup is a DFT destroy routine.  It releases the memory
    used by a setup object.

    Parameters:

        vDSP_DFT_Setup Setup

            Setup is the setup object to be released.  The object may have
            been previously allocated with any DFT or DCT setup routine, such
            as vDSP_DFT_zop_CreateSetup, vDSP_DFT_zrop_CreateSetup, or
            vDSP_DCT_CreateSetup.

    Destroying a setup with shared data is safe; it will release only memory
    not needed by other undestroyed setups.  Memory (and the data it contains)
    is freed only when all setup objects using it have been destroyed.

    Do not call this routine while any DFT or DCT routine sharing setup data
    might be executing.
*/
void vDSP_DFT_DestroySetup(vDSP_DFT_Setup __vDSP_Setup)
        __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_4_0);
void vDSP_DFT_DestroySetupD(vDSP_DFT_SetupD __vDSP_Setup)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);


/*  vDSP_DFT_zop is a DFT execution routine.  It performs a DFT, with the aid
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

        For cases where the length is f * 2**n, where f is 3, 5, or 15 and 3 <=
        n, Or may equal Ir and Oi may equal Ii.  Otherwise, no overlap of Or,
        Oi, Ir, and Ii is supported.

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


/*  vDSP_DFT_Execute is a DFT execution routine.  It performs a DFT, with the
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

void vDSP_DFT_ExecuteD(
    const struct vDSP_DFT_SetupStructD *__vDSP_Setup,
    const double *__vDSP_Ir,  const double *__vDSP_Ii,
          double *__vDSP_Or,        double *__vDSP_Oi)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);


/*  vDSP_DCT_CreateSetup is a DCT setup routine.  It creates a setup object
    for use with the vDSP_DCT_Execute routine.  See additional information
    above, at "How to use the Discrete Fourier Transform (DFT) and Discrete
    Cosine Transform (DCT) interfaces."

    Parameters:

        vDSP_DFT_Setup Previous

            Previous is either zero or a previous DFT or DCT setup.  If a
            previous setup is passed, the new setup will share data with the
            previous setup, if feasible (and with any other setups the
            previous setup shares with).  If zero is passed, the routine
            will allocate and initialize new memory.

        vDSP_Length Length

            Length is the number of real elements to be transformed.

        vDSP_DCT_Type Type

            Type specifies which DCT variant to perform.  At present, the
            supported DCT types are II and III, which are mutual inverses (up
            to scaling).  Types II and III are specified with symbol names
            vDSP_DCT_II and vDSP_DCT_III, respectively.

    Return value:

        Zero is returned if memory is unavailable or if there is no
        implementation for the requested case.  Currently, the implemented
        cases are:

            Length = f * 2**n, where f is 1, 3, 5, or 15 and 4 <= n.

    Function:

        When vDSP_DCT_Execute is called with a setup returned from this
        routine, it calculates:

            If Type is vDSP_DCT_II:

                For 0 <= k < N,

                    Or[k] = sum(Ir[j] * cos(k * (j+1/2) * pi / N, 0 <= j < N).

            If Type is vDSP_DCT_III

                For 0 <= k < N,

                    Or[k] = Ir[0]/2
                        + sum(Ir[j] * cos((k+1/2) * j * pi / N), 1 <= j < N).

            Where:

                N is the length given in the setup,

                h is the array of real numbers passed to vDSP_DCT_Execute in
                Input, and

                H is the array of real numbers stored by vDSP_DCT_Execute in
                the array passed to it in Output.

     Performance:

        Performance is good when the array addresses (passed to
        vDSP_DFT_Execute) are 16-byte aligned.  Other alignments are supported,
        but performance may be significantly worse in some cases, depending on
        the processor model or the transform length (because different
        algorithms are used for different forms of transform length).

    In-Place Operation:

        Output may equal Input (in the call the vDSP_DCT_Execute).  Otherwise,
        no overlap is permitted between the two buffers.

    The returned setup object may be used only with vDSP_DCT_Execute for the
    length given during setup.

    Do not call this routine while any DFT or DCT routine sharing setup data
    might be executing.
*/
typedef enum
{
    vDSP_DCT_II  = 2,
    vDSP_DCT_III = 3
} vDSP_DCT_Type;

vDSP_DFT_Setup vDSP_DCT_CreateSetup(
    vDSP_DFT_Setup __vDSP_Previous,
    vDSP_Length    __vDSP_Length,
    vDSP_DCT_Type  __vDSP_Type)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);


/*  vDSP_DCT_Execute is a DCT execution routine.  It performs a DCT, with the
    aid of previously created setup data.  See additional information above, at
    "How to use the Discrete Fourier Transform (DFT) and Discrete Cosine
    Transform (DCT) interfaces."

    Parameters:

        vDSP_DFT_Setup Setup

            A setup object returned by a previous call to vDSP_DCT_CreateSetup.

        const float *Input

            Pointer to the input buffer.

        float *Output

            Pointer to the output buffer.

        Observe there are no separate length or type parameters.  They are
        specified at the time that the Setup is created.

        Because the DCT is real-to-real, the parameters for vDSP_DCT_Execute
        are different from those used for a DFT.
*/
void vDSP_DCT_Execute(
    const struct vDSP_DFT_SetupStruct *__vDSP_Setup,
    const float                       *__vDSP_Input,
    float                             *__vDSP_Output)
        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);


/*  vDSP_dotpr2, vector single-precision stereo dot product.

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


/*  vDSP_dotpr_s1_15, vector integer 1.15 format dot product.

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


/*  vDSP_dotpr2_s1_15, vector integer 1.15 format stereo dot product.

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


/*  vDSP_dotpr_s8_24, vector integer 8.24 format dot product.

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


/*  vDSP_dotpr2_s8_24, vector integer 8.24 format stereo dot product.

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



/*  vDSP_vrampmul, vector single-precision vramp and multiply.

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


/*  vDSP_vrampmuladd, vector single-precision vramp, multiply and add.

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


/*  vDSP_vrampmul2, stereo vector single-precision vramp and multiply.

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


/*  vDSP_vrampmuladd2, stereo vector single-precision vramp, multiply and add.

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


/*  vDSP_vrampmul_s1_15, vector integer 1.15 format vramp and multiply.

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


/*  vDSP_vrampmuladd_s1_15, vector integer 1.15 format vramp, multiply and add.

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


/*  vDSP_vrampmul2_s1_15, stereo vector integer 1.15 format vramp and multiply.

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

            Starting addresses of both outputs and stride for the output
            vectors.

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


/*  vDSP_vrampmuladd2_s1_15, stereo vector integer 1.15 format vramp, multiply
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

            Starting addresses of both outputs and stride for the output
            vectors.

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


/*  vDSP_vrampmul_s8_24, vector integer 8.24 format vramp and multiply.

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


/*  vDSP_vrampmuladd_s8_24, vector integer 8.24 format vramp, multiply and add.

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


/*  vDSP_vrampmul2_s8_24, stereo vector integer 8.24 format vramp and multiply.

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

            Starting addresses of both outputs and stride for the output
            vectors.

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


/*  vDSP_vrampmuladd2_s8_24, stereo vector integer 8.24 format vramp, multiply
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

            Starting addresses of both outputs and stride for the output
            vectors.

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
    FFT_FORWARD = kFFTDirection_Forward,
    FFT_INVERSE = kFFTDirection_Inverse
};

enum {
    FFT_RADIX2  = kFFTRadix2,
    FFT_RADIX3  = kFFTRadix3,
    FFT_RADIX5  = kFFTRadix5
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


#endif // __VDSP__
