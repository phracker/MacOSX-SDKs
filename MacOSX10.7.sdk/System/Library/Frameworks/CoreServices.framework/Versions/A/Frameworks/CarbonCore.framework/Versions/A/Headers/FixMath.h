/*
     File:       CarbonCore/FixMath.h
 
     Contains:   Fixed Math Interfaces.
 
     Version:    CarbonCore-960.18~3
 
     Copyright:  © 1985-2008 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FIXMATH__
#define __FIXMATH__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


#define fixed1              ((Fixed) 0x00010000L)
#define fract1              ((Fract) 0x40000000L)
#define positiveInfinity    ((Fixed)  0x7FFFFFFFL)
#define negativeInfinity    ((Fixed)  -0x80000000L)

/*  The _IntSaturate macro converts a float to an int with saturation:

        If x <= -2**31, the result is 0x80000000.
        If -2**31 < x < 2**31, the result is x truncated to an integer.
        If 2**31 <= x, the result is 0x7fffffff.
*/
#if (defined (__i386__) || defined(__x86_64__)) && __GNUC__

    // For comments, see the annotated version below.
    #define _IntSaturate(x)     ({                  \
        int _Result = (int) (x);                    \
        __asm__("                                   \
                ucomisd %[LimitFloat], %[xx]    \n  \
                cmovae  %[LimitInt], %[_Result] "   \
            :   [_Result] "+r" (_Result)            \
            :   [LimitFloat] "mx" (0x1p31),     \
                [LimitInt] "mr" (0x7fffffff),       \
                [xx] "x" ((double)(x))          \
            :   "cc"                                \
            );                                      \
         _Result; })
    /*
        // Assume result will be x.
        int _Result = (x);
        __asm__("
                // Compare x to the floating-point limit.
                ucomisd %[LimitFloat], %[xx]    \n
                // If xx is too large, set _Result to the integer limit.
                cmovae  %[LimitInt], %[_Result]
                // _Result is input and output, in a general register.
            :   [_Result] "+r" (_Result)
                // LimitFloat is 0x1p31f and may be in memory or an XMM
                // register.
            :   [LimitFloat] "mx" (0x1p31f),
                // LimitInt is 0x7fffffff and may be in memory or a general
                // register.
                [LimitInt] "mr" (0x7fffffff),
                // xx is x and must be in an XMM register.
                [xx] "x" ((double)(x))
                // The condition code is changed.
            :   "cc"
            );
        // Return _Result.
         _Result;
    */

#elif defined __ppc__ || __ppc64__

    #define _IntSaturate(x) ((int) (x))

#else

    #error "Unknown architecture."
    // To use unoptimized standard C code, remove above line.
    #define _IntSaturate(x) ((x) <= -0x1p31f ? (int) -0x80000000 : \
        0x1p31f <= (x) ? (int) 0x7fffffff : (int) (x))

#endif

#define FloatToFixed(a) (_IntSaturate((a) * fixed1))
#define FloatToFract(a) (_IntSaturate((a) * fract1))

#define FixedRound(a)       ((short)(((Fixed)(a) + fixed1/2) >> 16))
#define FixedSquareRoot(a)  (((Fixed)FractSquareRoot(a) + 64) >> 7)
#define FixedTruncate(a)    ((short)((Fixed)(a) >> 16))
#define FixedToFract(a)     ((Fract)(a) << 14)
#define FractToFixed(a)     (((Fixed)(a) + 8192L) >> 14)
#define FixedToInt(a)       ((short)(((Fixed)(a) + fixed1/2) >> 16))
#define IntToFixed(a)       ((Fixed)(a) << 16)
#define FixedToFloat(a)     ((float)(a) / fixed1)
#define FractToFloat(a)     ((float)(a) / fract1)
#define ColorToFract(a)     (((Fract) (a) << 14) + ((Fract)(a) + 2 >> 2))
#define FractToColor(a)     ((gxColorValue) ((a) - ((a) >> 16) + 8191 >> 14))
/* These macros were removed because of developer complaints of variable name collision. */
//#ifndef ff    /* ff is already defined on some platforms */
//#define ff(a)            IntToFixed(a)
//#define fl(a)            FloatToFixed(a)
//#endif
/*
    FixRatio, FixMul, and FixRound were previously in ToolUtils.h
*/
/*
 *  FixRatio()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
FixRatio(
  short   numer,
  short   denom)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FixMul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
FixMul(
  Fixed   a,
  Fixed   b)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FixRound()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
FixRound(Fixed x)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Fix2Frac()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fract 
Fix2Frac(Fixed x)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Fix2Long()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32 
Fix2Long(Fixed x)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Long2Fix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
Long2Fix(SInt32 x)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Frac2Fix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
Frac2Fix(Fract x)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FracMul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fract 
FracMul(
  Fract   x,
  Fract   y)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FixDiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
FixDiv(
  Fixed   x,
  Fixed   y)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FracDiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fract 
FracDiv(
  Fract   x,
  Fract   y)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FracSqrt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fract 
FracSqrt(Fract x)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FracSin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fract 
FracSin(Fixed x)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FracCos()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fract 
FracCos(Fixed x)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FixATan2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
FixATan2(
  SInt32   x,
  SInt32   y)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Frac2X, Fix2X, X2Fix, and X2Frac translate to and from
    the floating point type "extended" (that's what the X is for).
    On the original Mac this was 80-bits and the functions could be
    accessed via A-Traps.  When the 68881 co-processor was added,
    it used 96-bit floating point types, so the A-Traps could not 
    be used.  When PowerPC was added, it used 64-bit floating point
    types, so yet another prototype was added.
*/
/*
 *  Frac2X()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern double 
Frac2X(Fract x)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Fix2X()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern double 
Fix2X(Fixed x)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  X2Fix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
X2Fix(double x)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  X2Frac()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fract 
X2Frac(double x)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideCompare()
 *  
 *  Parameters:
 *    
 *    target:
 *      a pointer to the first wide to compare
 *    
 *    source:
 *      a pointer to the second wide to compare
 *  
 *  Result:
 *    return 0 if the value in target == the value in source ; a value
 *    < 0 if *target < *source and a value > 0 if *target > *source
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
WideCompare(
  const wide *  target,
  const wide *  source)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideAdd()
 *  
 *  Discussion:
 *    Adds the value in source to target and returns target.  Note that
 *    target is updated to the new value.
 *  
 *  Parameters:
 *    
 *    target:
 *      a pointer to the value to have source added to
 *    
 *    source:
 *      a pointer to the value to be added to target
 *  
 *  Result:
 *    returns the value target
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideAdd(
  wide *        target,
  const wide *  source)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideSubtract()
 *  
 *  Discussion:
 *    Subtracts the value in source from target and returns target. 
 *    Note that target is updated to the new value.
 *  
 *  Parameters:
 *    
 *    target:
 *      a pointer to the value to have source subtracted from
 *    
 *    source:
 *      a pointer to the value to be substracted from target
 *  
 *  Result:
 *    returns the value target
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideSubtract(
  wide *        target,
  const wide *  source)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideNegate()
 *  
 *  Discussion:
 *    Negates the value ( twos complement ) in target and returns
 *    target.  Note that target is updated to the new value.
 *  
 *  Parameters:
 *    
 *    target:
 *  
 *  Result:
 *    returns the value target
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideNegate(wide * target)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideShift()
 *  
 *  Discussion:
 *    Shift the value in target by shift bits with upwards rounding of
 *    the remainder.    Note that target is updated to the new value.
 *  
 *  Parameters:
 *    
 *    target:
 *      the value to be shifted
 *    
 *    shift:
 *      the count of bits to shift, positive values shift right and
 *      negative values shift left
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideShift(
  wide *   target,
  SInt32   shift)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideSquareRoot()
 *  
 *  Discussion:
 *    Return the closest integer value to the square root for the given
 *    number.
 *  
 *  Parameters:
 *    
 *    source:
 *      the value to calculate the root for
 *  
 *  Result:
 *    the closest integer value to the square root of source
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt32 
WideSquareRoot(const wide * source)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideMultiply()
 *  
 *  Discussion:
 *    Returns the wide result of multipling two SInt32 values
 *  
 *  Parameters:
 *    
 *    multiplicand:
 *    
 *    multiplier:
 *    
 *    target:
 *      a pointer to where to put the result  of multiplying
 *      multiplicand and multiplier, must not be NULL
 *  
 *  Result:
 *    the value target
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideMultiply(
  SInt32   multiplicand,
  SInt32   multiplier,
  wide *   target)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideDivide()
 *  
 *  Discussion:
 *    Returns the integer and remainder results after dividing a wide
 *    value by an SInt32. Will overflow to positiveInfinity or
 *    negativeInfinity if the result won't fit into an SInt32.  If
 *    remainder is (SInt32) -1 then any overflow rounds to
 *    negativeInfinity.
 *  
 *  Parameters:
 *    
 *    dividend:
 *      the value to be divided
 *    
 *    divisor:
 *      the value to divide by
 *    
 *    remainder:
 *      a pointer to where to put the remainder result, between 0 and
 *      divisor, after dividing divident by divisor. If NULL, no
 *      remainder is returned.  If (SInt32*) -1, then any overflow
 *      result will round to negativeInfinity.
 *  
 *  Result:
 *    the integer signed result of dividend / divisor
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32 
WideDivide(
  const wide *  dividend,
  SInt32        divisor,
  SInt32 *      remainder)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideWideDivide()
 *  
 *  Discussion:
 *    Returns the wide integer and remainder results after dividing a
 *    wide value by an SInt32. Note that dividend is updated with the
 *    result.
 *  
 *  Parameters:
 *    
 *    dividend:
 *      the value to be divided
 *    
 *    divisor:
 *      the value to divide by
 *    
 *    remainder:
 *      a pointer to where to put the remainder result, between 0 and
 *      divisor, after dividing divident by divisor
 *  
 *  Result:
 *    the wide result of dividend / divisor
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideWideDivide(
  wide *    dividend,
  SInt32    divisor,
  SInt32 *  remainder)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideBitShift()
 *  
 *  Discussion:
 *    Shift the value in target by shift bits.  Note that target is
 *    updated with the shifted result.
 *  
 *  Parameters:
 *    
 *    target:
 *      the value to be shifted
 *    
 *    shift:
 *      the count of bits to shift, positive values shift right and
 *      negative values shift left
 *  
 *  Result:
 *    return the value target
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideBitShift(
  wide *   target,
  SInt32   shift)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UnsignedFixedMulDiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern UnsignedFixed 
UnsignedFixedMulDiv(
  UnsignedFixed   value,
  UnsignedFixed   multiplier,
  UnsignedFixed   divisor)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




#ifdef __cplusplus
}
#endif

#endif /* __FIXMATH__ */

