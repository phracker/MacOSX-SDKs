/*
     File:       HIToolbox/AEInteraction.h
 
     Contains:   AppleEvent functions that deal with Events and interacting with user
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AEINTERACTION__
#define __AEINTERACTION__

#ifndef __AEDATAMODEL__
#include <AE/AEDataModel.h>
#endif

#ifndef __NOTIFICATION__
#include <HIToolbox/Notification.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
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

/**************************************************************************
  AppleEvent callbacks. 
**************************************************************************/
typedef CALLBACK_API( Boolean , AEIdleProcPtr )(EventRecord *theEvent, long *sleepTime, RgnHandle *mouseRgn);
typedef CALLBACK_API( Boolean , AEFilterProcPtr )(EventRecord *theEvent, long returnID, long transactionID, const AEAddressDesc *sender);
typedef STACK_UPP_TYPE(AEIdleProcPtr)                           AEIdleUPP;
typedef STACK_UPP_TYPE(AEFilterProcPtr)                         AEFilterUPP;

/**************************************************************************
  The next couple of calls are basic routines used to create, send,
  and process AppleEvents. 
**************************************************************************/
/*
 *  AESend()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AESend(
  const AppleEvent *  theAppleEvent,
  AppleEvent *        reply,
  AESendMode          sendMode,
  AESendPriority      sendPriority,
  long                timeOutInTicks,
  AEIdleUPP           idleProc,             /* can be NULL */
  AEFilterUPP         filterProc);          /* can be NULL */


/*
 *  AEProcessAppleEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEProcessAppleEvent(const EventRecord * theEventRecord);



/* 
 Note: during event processing, an event handler may realize that it is likely
 to exceed the client's timeout limit. Passing the reply to this
 routine causes a wait event to be generated that asks the client
 for more time. 
*/
/*
 *  AEResetTimer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEResetTimer(const AppleEvent * reply);



/**************************************************************************
  The following three calls are used to allow applications to behave
  courteously when a user interaction such as a dialog box is needed. 
**************************************************************************/

typedef SInt8 AEInteractAllowed;
enum {
  kAEInteractWithSelf           = 0,
  kAEInteractWithLocal          = 1,
  kAEInteractWithAll            = 2
};

/*
 *  AEGetInteractionAllowed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetInteractionAllowed(AEInteractAllowed * level);


/*
 *  AESetInteractionAllowed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AESetInteractionAllowed(AEInteractAllowed level);


/*
 *  AEInteractWithUser()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEInteractWithUser(
  long        timeOutInTicks,
  NMRecPtr    nmReqPtr,
  AEIdleUPP   idleProc);



/**************************************************************************
 The following four calls are available for applications which need more
 sophisticated control over when and how events are processed. Applications
 which implement multi-session servers or which implement their own
 internal event queueing will probably be the major clients of these
 routines. They can be called from within a handler to prevent the AEM from
 disposing of the AppleEvent when the handler returns. They can be used to
 asynchronously process the event (as MacApp does).
**************************************************************************/
/*
 *  AESuspendTheCurrentEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AESuspendTheCurrentEvent(const AppleEvent * theAppleEvent);


/* 
 Note: The following routine tells the AppleEvent manager that processing
 is either about to resume or has been completed on a previously suspended
 event. The procPtr passed in as the dispatcher parameter will be called to
 attempt to redispatch the event. Several constants for the dispatcher
 parameter allow special behavior. They are:
    - kAEUseStandardDispatch means redispatch as if the event was just
      received, using the standard AppleEvent dispatch mechanism.
    - kAENoDispatch means ignore the parameter.
      Use this in the case where the event has been handled and no
      redispatch is needed.
    - non nil means call the routine which the dispatcher points to.
*/
/* Constants for Refcon in AEResumeTheCurrentEvent with kAEUseStandardDispatch */
enum {
  kAEDoNotIgnoreHandler         = 0x00000000,
  kAEIgnoreAppPhacHandler       = 0x00000001, /* available only in vers 1.0.1 and greater */
  kAEIgnoreAppEventHandler      = 0x00000002, /* available only in vers 1.0.1 and greater */
  kAEIgnoreSysPhacHandler       = 0x00000004, /* available only in vers 1.0.1 and greater */
  kAEIgnoreSysEventHandler      = 0x00000008, /* available only in vers 1.0.1 and greater */
  kAEIngoreBuiltInEventHandler  = 0x00000010, /* available only in vers 1.0.1 and greater */
  kAEDontDisposeOnResume        = (long)0x80000000 /* available only in vers 1.0.1 and greater */
};

/* Constants for AEResumeTheCurrentEvent */
enum {
  kAENoDispatch                 = 0,    /* dispatch parameter to AEResumeTheCurrentEvent takes a pointer to a dispatch */
  kAEUseStandardDispatch        = (long)0xFFFFFFFF /* table, or one of these two constants */
};

/*
 *  AEResumeTheCurrentEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEResumeTheCurrentEvent(
  const AppleEvent *  theAppleEvent,
  const AppleEvent *  reply,
  AEEventHandlerUPP   dispatcher,          /* can be NULL */
  long                handlerRefcon);


/*
 *  AEGetTheCurrentEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetTheCurrentEvent(AppleEvent * theAppleEvent);


/*
 *  AESetTheCurrentEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AESetTheCurrentEvent(const AppleEvent * theAppleEvent);



/**************************************************************************
  AppleEvent callbacks. 
**************************************************************************/
/*
 *  NewAEIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AEIdleUPP
NewAEIdleUPP(AEIdleProcPtr userRoutine);

/*
 *  NewAEFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AEFilterUPP
NewAEFilterUPP(AEFilterProcPtr userRoutine);

/*
 *  DisposeAEIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAEIdleUPP(AEIdleUPP userUPP);

/*
 *  DisposeAEFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAEFilterUPP(AEFilterUPP userUPP);

/*
 *  InvokeAEIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeAEIdleUPP(
  EventRecord *  theEvent,
  long *         sleepTime,
  RgnHandle *    mouseRgn,
  AEIdleUPP      userUPP);

/*
 *  InvokeAEFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeAEFilterUPP(
  EventRecord *          theEvent,
  long                   returnID,
  long                   transactionID,
  const AEAddressDesc *  sender,
  AEFilterUPP            userUPP);





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

#endif /* __AEINTERACTION__ */

