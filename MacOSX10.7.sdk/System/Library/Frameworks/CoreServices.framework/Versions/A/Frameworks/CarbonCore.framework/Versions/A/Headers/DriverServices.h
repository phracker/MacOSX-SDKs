/*
     File:       CarbonCore/DriverServices.h
 
     Contains:   Driver Services Interfaces.
 
     Version:    CarbonCore-960.18~3
 
     Copyright:  © 1985-2008 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DRIVERSERVICES__
#define __DRIVERSERVICES__

#ifndef __CONDITIONALMACROS__
#include <CarbonCore/ConditionalMacros.h>
#endif

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __MACHINEEXCEPTIONS__
#include <CarbonCore/MachineExceptions.h>
#endif

#ifndef __DRIVERSYNCHRONIZATION__
#include <CarbonCore/DriverSynchronization.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=power


enum {
  durationMicrosecond           = -1L,  /* Microseconds are negative*/
  durationMillisecond           = 1,    /* Milliseconds are positive*/
  durationSecond                = 1000, /* 1000 * durationMillisecond*/
  durationMinute                = 60000, /* 60 * durationSecond,*/
  durationHour                  = 3600000, /* 60 * durationMinute,*/
  durationDay                   = 86400000, /* 24 * durationHour,*/
  durationNoWait                = 0,    /* don't block*/
  durationForever               = 0x7FFFFFFF /* no time limit*/
};


typedef UnsignedWide                    Nanoseconds;
/*
 *  UpTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
UpTime(void)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */



/*
 *  AbsoluteToNanoseconds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern Nanoseconds 
AbsoluteToNanoseconds(AbsoluteTime absoluteTime)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AbsoluteToDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern Duration 
AbsoluteToDuration(AbsoluteTime absoluteTime)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NanosecondsToAbsolute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
NanosecondsToAbsolute(Nanoseconds nanoseconds)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DurationToAbsolute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
DurationToAbsolute(Duration duration)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddAbsoluteToAbsolute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
AddAbsoluteToAbsolute(
  AbsoluteTime   absoluteTime1,
  AbsoluteTime   absoluteTime2)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SubAbsoluteFromAbsolute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
SubAbsoluteFromAbsolute(
  AbsoluteTime   leftAbsoluteTime,
  AbsoluteTime   rightAbsoluteTime)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddNanosecondsToAbsolute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
AddNanosecondsToAbsolute(
  Nanoseconds    nanoseconds,
  AbsoluteTime   absoluteTime)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddDurationToAbsolute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
AddDurationToAbsolute(
  Duration       duration,
  AbsoluteTime   absoluteTime)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SubNanosecondsFromAbsolute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
SubNanosecondsFromAbsolute(
  Nanoseconds    nanoseconds,
  AbsoluteTime   absoluteTime)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SubDurationFromAbsolute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern AbsoluteTime 
SubDurationFromAbsolute(
  Duration       duration,
  AbsoluteTime   absoluteTime)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AbsoluteDeltaToNanoseconds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern Nanoseconds 
AbsoluteDeltaToNanoseconds(
  AbsoluteTime   leftAbsoluteTime,
  AbsoluteTime   rightAbsoluteTime)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AbsoluteDeltaToDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern Duration 
AbsoluteDeltaToDuration(
  AbsoluteTime   leftAbsoluteTime,
  AbsoluteTime   rightAbsoluteTime)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DurationToNanoseconds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern Nanoseconds 
DurationToNanoseconds(Duration theDuration)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NanosecondsToDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern Duration 
NanosecondsToDuration(Nanoseconds theNanoseconds)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __DRIVERSERVICES__ */

