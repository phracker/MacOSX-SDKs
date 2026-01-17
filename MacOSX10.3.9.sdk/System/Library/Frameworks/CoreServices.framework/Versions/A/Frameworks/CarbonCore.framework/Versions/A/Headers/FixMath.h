/*
     File:       CarbonCore/FixMath.h
 
     Contains:   Fixed Math Interfaces.
 
     Version:    CarbonCore-557~1
 
     Copyright:  © 1985-2003 by Apple Computer, Inc., all rights reserved
 
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
#define positiveInfinity    ((long)  0x7FFFFFFFL)
#define negativeInfinity    ((long)  0x80000000L)

#define FixedRound(a)       ((short)(((Fixed)(a) + fixed1/2) >> 16))
#define FixedSquareRoot(a)  (((Fixed)FractSquareRoot(a) + 64) >> 7)
#define FixedTruncate(a)    ((short)((Fixed)(a) >> 16))
#define FixedToFract(a)     ((Fract)(a) << 14)
#define FractToFixed(a)     (((Fixed)(a) + 8192L) >> 14)
#define FixedToInt(a)       ((short)(((Fixed)(a) + fixed1/2) >> 16))
#define IntToFixed(a)       ((Fixed)(a) << 16)
#define FixedToFloat(a)     ((float)(a) / fixed1)
#define FloatToFixed(a)     ((Fixed)((float)(a) * fixed1))
#define FractToFloat(a)     ((float)(a) / fract1)
#define FloatToFract(a)     ((Fract)((float)(a) * fract1))
#define ColorToFract(a)     (((Fract) (a) << 14) + ((Fract)(a) + 2 >> 2))
#define FractToColor(a)     ((gxColorValue) ((a) - ((a) >> 16) + 8191 >> 14))
#ifndef ff  /* ff is already defined on some platforms */
#define ff(a)              IntToFixed(a)
#define fl(a)              FloatToFixed(a)
#endif
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
extern long 
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
Long2Fix(long x)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long   x,
  long   y)                                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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


/* QuickTime 3.0 makes these Wide routines available on other platforms*/
#if TARGET_CPU_PPC
/*
 *  WideCompare()
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideShift(
  wide *  target,
  long    shift)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideSquareRoot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern unsigned long 
WideSquareRoot(const wide * source)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideMultiply(
  long    multiplicand,
  long    multiplier,
  wide *  target)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* returns the quotient */
/*
 *  WideDivide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
WideDivide(
  const wide *  dividend,
  long          divisor,
  long *        remainder)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* quotient replaces dividend */
/*
 *  WideWideDivide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideWideDivide(
  wide *  dividend,
  long    divisor,
  long *  remainder)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WideBitShift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern wide * 
WideBitShift(
  wide *  src,
  long    shift)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#endif  /* TARGET_CPU_PPC */



#ifdef __cplusplus
}
#endif

#endif /* __FIXMATH__ */

