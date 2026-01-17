/*
     File:       CarbonCore/ToolUtils.h
 
     Contains:   Toolbox Utilities Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1990-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TOOLUTILS__
#define __TOOLUTILS__

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

#pragma options align=mac68k

/*
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    Note: 
    
    The following routines that used to be in this header file, have moved to
    more appropriate headers.  
    
        FixMath.h:      FixMul
                        FixRatio
                        FixRound
        
        Icons.h:        GetIcon
                        PlotIcon
                        
        Quickdraw.h:    AngleFromSlope
                        DeltaPoint
                        GetCursor
                        GetIndPattern
                        GetPattern
                        GetPicture
                        PackBits
                        ScreenRes
                        ShieldCursor
                        SlopeFromAngle
                        UnpackBits
                        
        TextUtils.h:    Munger
                        GetIndString
                        GetString
                        NewString
                        SetString
ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/

/*
 *  BitTst()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
BitTst(
  const void *  bytePtr,
  long          bitNum)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitSet()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BitSet(
  void *  bytePtr,
  long    bitNum)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitClr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BitClr(
  void *  bytePtr,
  long    bitNum)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitAnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
BitAnd(
  long   value1,
  long   value2)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitOr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
BitOr(
  long   value1,
  long   value2)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitXor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
BitXor(
  long   value1,
  long   value2)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitNot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
BitNot(long value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitShift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
BitShift(
  long    value,
  short   count)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#define HiWord(x) ((short)((long)(x) >> 16))
#define LoWord(x) ((short)(x))


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __TOOLUTILS__ */

