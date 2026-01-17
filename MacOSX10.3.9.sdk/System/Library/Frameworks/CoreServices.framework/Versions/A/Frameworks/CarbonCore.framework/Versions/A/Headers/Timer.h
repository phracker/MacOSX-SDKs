/*
     File:       CarbonCore/Timer.h
 
     Contains:   Time Manager interfaces.
 
     Version:    CarbonCore-557~1
 
     Copyright:  © 1985-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TIMER__
#define __TIMER__

#ifndef __CONDITIONALMACROS__
#include <CarbonCore/ConditionalMacros.h>
#endif

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __OSUTILS__
#include <CarbonCore/OSUtils.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

enum {
                                        /* high bit of qType is set if task is active */
  kTMTaskActive                 = (1L << 15)
};

typedef struct TMTask                   TMTask;
typedef TMTask *                        TMTaskPtr;
typedef CALLBACK_API( void , TimerProcPtr )(TMTaskPtr tmTaskPtr);
typedef STACK_UPP_TYPE(TimerProcPtr)                            TimerUPP;
struct TMTask {
  QElemPtr            qLink;
  short               qType;
  TimerUPP            tmAddr;
  long                tmCount;
  long                tmWakeUp;
  long                tmReserved;
};

/*
 *  InsTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InsTime(QElemPtr tmTaskPtr)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InsXTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InsXTime(QElemPtr tmTaskPtr)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PrimeTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PrimeTime(
  QElemPtr   tmTaskPtr,
  long       count)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RmvTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RmvTime(QElemPtr tmTaskPtr)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* InstallTimeTask, InstallXTimeTask, PrimeTimeTask and RemoveTimeTask work */
/* just like InsTime, InsXTime, PrimeTime, and RmvTime except that they */
/* return an OSErr result. */
/*
 *  InstallTimeTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
InstallTimeTask(QElemPtr tmTaskPtr)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InstallXTimeTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
InstallXTimeTask(QElemPtr tmTaskPtr)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PrimeTimeTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
PrimeTimeTask(
  QElemPtr   tmTaskPtr,
  long       count)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveTimeTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
RemoveTimeTask(QElemPtr tmTaskPtr)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  Microseconds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Microseconds(UnsignedWide * microTickCount)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewTimerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TimerUPP
NewTimerUPP(TimerProcPtr userRoutine)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTimerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTimerUPP(TimerUPP userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTimerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeTimerUPP(
  TMTaskPtr  tmTaskPtr,
  TimerUPP   userUPP)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __TIMER__ */

