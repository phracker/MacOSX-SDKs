/*
     File:       CarbonCore/DriverSynchronization.h
 
     Contains:   Driver Synchronization Interfaces.
 
     Version:    CarbonCore-472~1
 
     Copyright:  © 1985-2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DRIVERSYNCHRONIZATION__
#define __DRIVERSYNCHRONIZATION__

#ifndef __CONDITIONALMACROS__
#include <CarbonCore/ConditionalMacros.h>
#endif

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

/*
 *  SynchronizeIO()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CompareAndSwap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern Boolean 
CompareAndSwap(
  UInt32    oldVvalue,
  UInt32    newValue,
  UInt32 *  OldValueAdr)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TestAndClear()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern Boolean 
TestAndClear(
  UInt32   bit,
  UInt8 *  startAddress)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TestAndSet()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern Boolean 
TestAndSet(
  UInt32   bit,
  UInt8 *  startAddress)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IncrementAtomic8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt8 
IncrementAtomic8(SInt8 * value)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DecrementAtomic8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt8 
DecrementAtomic8(SInt8 * value)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddAtomic8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt8 
AddAtomic8(
  SInt32   amount,
  SInt8 *  value)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitAndAtomic8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt8 
BitAndAtomic8(
  UInt32   mask,
  UInt8 *  value)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitOrAtomic8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt8 
BitOrAtomic8(
  UInt32   mask,
  UInt8 *  value)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitXorAtomic8()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt8 
BitXorAtomic8(
  UInt32   mask,
  UInt8 *  value)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IncrementAtomic16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt16 
IncrementAtomic16(SInt16 * value)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DecrementAtomic16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt16 
DecrementAtomic16(SInt16 * value)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddAtomic16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt16 
AddAtomic16(
  SInt32    amount,
  SInt16 *  value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitAndAtomic16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt16 
BitAndAtomic16(
  UInt32    mask,
  UInt16 *  value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitOrAtomic16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt16 
BitOrAtomic16(
  UInt32    mask,
  UInt16 *  value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitXorAtomic16()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt16 
BitXorAtomic16(
  UInt32    mask,
  UInt16 *  value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IncrementAtomic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt32 
IncrementAtomic(SInt32 * value)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DecrementAtomic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt32 
DecrementAtomic(SInt32 * value)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddAtomic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern SInt32 
AddAtomic(
  SInt32    amount,
  SInt32 *  value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitAndAtomic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt32 
BitAndAtomic(
  UInt32    mask,
  UInt32 *  value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitOrAtomic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt32 
BitOrAtomic(
  UInt32    mask,
  UInt32 *  value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitXorAtomic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern UInt32 
BitXorAtomic(
  UInt32    mask,
  UInt32 *  value)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




#ifdef __cplusplus
}
#endif

#endif /* __DRIVERSYNCHRONIZATION__ */

