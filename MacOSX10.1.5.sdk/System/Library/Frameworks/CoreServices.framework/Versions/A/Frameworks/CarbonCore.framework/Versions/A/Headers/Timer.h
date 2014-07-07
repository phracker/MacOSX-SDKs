/*
     File:       CarbonCore/Timer.h
 
     Contains:   Time Manager interfaces.
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
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




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

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
InsTime(QElemPtr tmTaskPtr);


/*
 *  InsXTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InsXTime(QElemPtr tmTaskPtr);


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
  long       count);


/*
 *  RmvTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RmvTime(QElemPtr tmTaskPtr);



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
InstallTimeTask(QElemPtr tmTaskPtr);


/*
 *  InstallXTimeTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
InstallXTimeTask(QElemPtr tmTaskPtr);


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
  long       count);


/*
 *  RemoveTimeTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
RemoveTimeTask(QElemPtr tmTaskPtr);



/*
 *  Microseconds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Microseconds(UnsignedWide * microTickCount);


/*
 *  NewTimerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TimerUPP
NewTimerUPP(TimerProcPtr userRoutine);

/*
 *  DisposeTimerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTimerUPP(TimerUPP userUPP);

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
  TimerUPP   userUPP);




#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __TIMER__ */

