/*  vfp.h (from vecLib-622.0)
 *  Copyright (c) 1999-2017 by Apple Inc. All rights reserved.
 *
 *  Overview:
 *  vfp.h provides math library operations for SIMD vectors.  These functions
 *  are intended for use as replacements for calls to the system math library
 *  in hand-vectorized code.
 *
 *  If you are not writing vector code, but are looking for high-performance
 *  math library operations, consult vForce.h instead, which provides math
 *  library operations on arrays of floating-point data.
 *
 *  Compatibility:
 *  These routines operate on SIMD vectors, and are compatible with the types
 *  declared in the headers for both SSE (Intel) and NEON (ARM) intrinsics.
 *
 *  Bugs:
 *  For bug reports or feature requests use
 *  http://developer.apple.com/bugreporter/
 */

#ifndef __VFP__
#define __VFP__
#if defined __SSE2__ || defined __ARM_NEON__

#include "vecLibTypes.h"
#include <stdint.h>
#include <Availability.h>

#ifdef __cplusplus
extern "C" {
#endif

/*  Rounding Functions
 *
 *  Each lane of the result vector contains the value in the corresponding
 *  lane of the input vector rounded to an integral value in the specified
 *  direction:
 *
 *     Function         Rounding Direction
 *     --------         ------------------------
 *     vceilf           toward +infinity
 *     vfloorf          toward -infinity
 *     vtruncf          toward zero
 *     vnintf           to nearest, ties to even
 *
 *  When SSE4.1 code generation is enabled on Intel architectures, single-
 *  instruction implementations of these operations are inlined instead of
 *  making an external function call.                                         */

#if defined __SSE4_1__
#include <immintrin.h>
#define __VFP_INLINE_ATTR__ __attribute__((__always_inline__, __nodebug__))
static __inline__ vFloat __VFP_INLINE_ATTR__  vceilf(vFloat __vfp_a) { return _mm_ceil_ps(__vfp_a); }
static __inline__ vFloat __VFP_INLINE_ATTR__ vfloorf(vFloat __vfp_a) { return _mm_floor_ps(__vfp_a); }
static __inline__ vFloat __VFP_INLINE_ATTR__ vtruncf(vFloat __vfp_a) { return _mm_round_ps(__vfp_a, _MM_FROUND_TRUNC); }
static __inline__ vFloat __VFP_INLINE_ATTR__  vnintf(vFloat __vfp_a) { return _mm_round_ps(__vfp_a, _MM_FROUND_NINT); }
#else
extern vFloat  vceilf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_6_0);
extern vFloat vfloorf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_6_0);
extern vFloat vtruncf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
extern vFloat  vnintf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_6_0);
/*  The legacy name vintf is not available on iOS.  Use vtruncf instead.      */
extern vFloat   vintf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
#endif


#if !defined __has_feature
    #define __has_feature(f)    0
#endif
#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull begin")
#else
    #define __nullable
    #define __nonnull
#endif


/*  Exponential and Logarithmic Functions
 *
 *  Each lane of the result contains the result of the specified operation
 *  applied to the corresponding lane of the input vector:
 *
 *      Function        Lanewise Operation
 *      --------        ----------------------------
 *      vexpf           base-e exponential function.
 *      vexp2f          base-two exponential function.
 *      vexpm1f         e**x - 1, computed in such a way as to be more
 *                      accurate than calling vexpf and then subtracting 1
 *                      when the argument is close to zero.
 *      vlogf           natural logarithm.
 *      vlog2f          base-two logarithm.
 *      vlog10f         base-ten logarithm.
 *      vlog1pf         natural logarithm of (1+x), computed in such a way as
 *                      to be more accurate than adding 1 and calling vlogf
 *                      when the argument is close to zero.                   */
 
extern vFloat   vexpf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat  vexp2f(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
extern vFloat vexpm1f(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat   vlogf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat  vlog2f(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
extern vFloat vlog10f(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_6_0);
extern vFloat vlog1pf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
 
/*  Scaling Functions
 *
 *  These functions can be used to efficiently rescale floating-point
 *  computations when necessary:
 *
 *      Function        Lanewise Operation
 *      --------        ----------------------------
 *      vlogbf          extracts the exponent of its argument as a signed
 *                      integral value.  Subnormal arguments are treated as
 *                      though they were first normalized.  Thus:
 *                          1 <= x * 2**(-logbf(x)) < 2
 *      vscalbf         efficiently computes x * 2**n, where x is the first
 *                      argument and n is the second.                         */

extern vFloat  vlogbf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat vscalbf(vFloat, vSInt32) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);

/*  Power Functions
 *  
 *  vpowf raises the first argument to the power specified by the second
 *  argument, and returns the result.  Edge cases are as specified for the
 *  pow( ) function in the math library.  vipowf also raises the first
 *  argument to the power specified by the second argument, but the second
 *  argument to vipowf is an integer, not a floating-point number.            */

extern vFloat  vpowf(vFloat, vFloat)  __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat vipowf(vFloat, vSInt32) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);

/*  Trigonometric and Hyperbolic Functions
 *
 *  These functions compute lanewise trigonometric and hyperbolic functions
 *  and their inverses.  All inputs to the trigonometric functions, and 
 *  results from their inverses, are interpreted as angles measured in radians.
 *
 *      Function        Result
 *      --------        ----------------------------
 *      vsinf           sine of the argument.
 *      vcosf           cosine of the argument.
 *      vsincosf        returns the cosine of the first argument, and stores
 *                      the sine of the first argument to the destination
 *                      specified by the second argument.  This address must
 *                      be a valid pointer and must be 16-byte aligned.
 *      vtanf           tangent of the argument.
 *
 *      vsinpif         sine of the argument multiplied by pi.
 *      vcospif         cosine of the argument multiplied by pi.
 *      vtanpif         tangent of the argument multiplied by pi.
 *
 *      vasinf          arcsine of the argument, in the range [-pi/2, pi/2].
 *      vacosf          arccosine of the argument, in the range [0, pi].
 *      vatanf          arctangent of the argument, in the range [-pi/2, pi/2].
 *      vatan2f         arctangent of the first argument divided by the
 *                      second argument, using the sign of both arguments to
 *                      determine in which quadrant the result lies.  The
 *                      result is in the range [-pi, pi], and is the signed
 *                      angle from the positive x axis to the point
 *                          (second argument, first argument).
 *
 *      vsinhf          hyperbolic sine of the argument.
 *      vcoshf          hyperbolic cosine of the argument.
 *      vtanhf          hyperbolic tangent of the argument.
 *
 *      vasinhf         inverse hyperbolic sine of the argument.
 *      vacoshf         inverse hyperbolic cosine of the argument.
 *      vatanhf         inverse hyperbolic tangent of the argument.           */

extern vFloat    vsinf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat    vcosf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat vsincosf(vFloat, vFloat *) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_6_0);
extern vFloat    vtanf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat  vsinpif(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
extern vFloat  vcospif(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
extern vFloat  vtanpif(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
extern vFloat   vasinf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat   vacosf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat   vatanf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat  vatan2f(vFloat, vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat   vsinhf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat   vcoshf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat   vtanhf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat  vasinhf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat  vacoshf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat  vatanhf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);

/*  Arithmetic Functions
 *
 *  vrecf, vsqrtf, and vrsqrtf provide lane-wise reciprocal, square-root, and
 *  reciprocal square-root operations, respectively.  Each lane in the result
 *  of vdivf contains the corresponding lane of the first argument divided by
 *  the corresponding lane of the second argument.                            */

extern vFloat   vrecf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_6_0);
extern vFloat  vsqrtf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat vrsqrtf(vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat   vdivf(vFloat, vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);

/*  Remainder Functions
 *
 *  These functions compute various forms of the remainder from division of the
 *  first argument by the second argument.  If we call the first argument x and
 *  the second argument y, then the behavior of these functions is as follows:
 *
 *  vfmodf returns the value r = x - qy, where q is an integer such that r has
 *  the same sign as x and satisfies |r| < |y|, if y is not zero.
 *
 *  vremainderf performs the remainder operation defined in the IEEE-754
 *  standard.  It returns the value r = x - qy, where q is the integer value
 *  closest to the exact value of x/y.  If there are two integers closest to
 *  x/y, then the one which is even is used.  Thus, |r| <= |y|/2.
 *
 *  vremquof returns the same remainder as vremainderf, and also stores the
 *  7 low-order bits of q to the address pointed to by the third argument.
 *  This must be a valid pointer, and must have 16-byte alignment.            */

extern vFloat      vfmodf(vFloat, vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat vremainderf(vFloat, vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat    vremquof(vFloat, vFloat, vUInt32 *) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);

/*  Floating-point Utility Functions
 *
 *  These functions provide vector versions of common utility operations
 *  for working with floating-point data:
 *
 *      Function        Lanewise Operation
 *      --------        ----------------------------
 *      vfabsf          absolute value
 *      vcopysignf      returns a floating-point value with the magnitude of
 *                      the first operand and the sign of the second operand.
 *      vsignbitf       non-zero if and only if the signbit of the argument is
 *                      set.  (Note that this applies to NaNs, zeros, and 
 *                      infinities as well, and so is not the same as x < 0.)
 *      vnextafterf     returns the floating-point value adjacent to the
 *                      first operand in the direction of the second operand.
 *      vclassifyf      returns the value of the FP_xxxx macro (defined in
 *                      <math.h>) corresponding to the "class" of the argument.
 *                      e.g. if the argument is infinity, the result is
 *                      FP_INFINITE; if the argument is zero, the result is
 *                      FP_ZERO.  Consult <math.h> for further details.       */

extern vFloat       vfabsf(vFloat)         __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);
extern vFloat   vcopysignf(vFloat, vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vUInt32   vsignbitf(vFloat)         __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vFloat  vnextafterf(vFloat, vFloat) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
extern vUInt32  vclassifyf(vFloat)         __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);
/*  The legacy name vfabf is not available on iOS.  Use vfabsf instead.       */
extern vFloat        vfabf(vFloat)         __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*  Generalized Table Lookup
 *
 *  This function provides a gather operation (table lookup).  Each lane of the
 *  result vector contains the value found in a table at index specified by
 *  the corresponding lane of the first argument.  The table base address is
 *  specified by the second argument.  Note please that the indices are
 *  *signed* 32-bit integers.                                                 */

extern vUInt32 vtablelookup(vSInt32, uint32_t *) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_6_0);

#if __has_feature(assume_nonnull)
    _Pragma("clang assume_nonnull end")
#endif

#ifdef __cplusplus
}
#endif
#endif /* defined __SSE2__ || defined __ARM_NEON__ */
#endif /* __VFP__ */
