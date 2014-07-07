/*
     File:       CarbonCore/Threads.h
 
     Contains:   Thread Manager Interfaces.
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1991-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __THREADS__
#define __THREADS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
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

/* Thread states*/
typedef UInt16 ThreadState;
enum {
  kReadyThreadState             = 0,
  kStoppedThreadState           = 1,
  kRunningThreadState           = 2
};

/* Error codes have been moved to Errors.(pah)*/

/* Thread environment characteristics*/
typedef void *                          ThreadTaskRef;
/* Thread characteristics*/
typedef UInt32 ThreadStyle;
enum {
  kCooperativeThread            = 1L << 0,
  kPreemptiveThread             = 1L << 1
};

/* Thread identifiers*/
typedef UInt32 ThreadID;
enum {
  kNoThreadID                   = 0,
  kCurrentThreadID              = 1,
  kApplicationThreadID          = 2
};

/* Options when creating a thread*/
typedef UInt32 ThreadOptions;
enum {
  kNewSuspend                   = (1 << 0),
  kUsePremadeThread             = (1 << 1),
  kCreateIfNeeded               = (1 << 2),
  kFPUNotNeeded                 = (1 << 3),
  kExactMatchThread             = (1 << 4)
};

/* Information supplied to the custom scheduler*/
struct SchedulerInfoRec {
  UInt32              InfoRecSize;
  ThreadID            CurrentThreadID;
  ThreadID            SuggestedThreadID;
  ThreadID            InterruptedCoopThreadID;
};
typedef struct SchedulerInfoRec         SchedulerInfoRec;
typedef SchedulerInfoRec *              SchedulerInfoRecPtr;

/*
    The following ProcPtrs cannot be interchanged with UniversalProcPtrs because
    of differences between 680x0 and PowerPC runtime architectures with regard to
    the implementation of the Thread Manager.
 */
typedef void *                          voidPtr;
/* Prototype for thread's entry (main) routine*/
typedef CALLBACK_API( voidPtr , ThreadEntryProcPtr )(void * threadParam);
/* Prototype for custom thread scheduler routine*/
typedef CALLBACK_API( ThreadID , ThreadSchedulerProcPtr )(SchedulerInfoRecPtr schedulerInfo);
/* Prototype for custom thread switcher routine*/
typedef CALLBACK_API( void , ThreadSwitchProcPtr )(ThreadID threadBeingSwitched, void *switchProcParam);
/* Prototype for thread termination notification routine*/
typedef CALLBACK_API( void , ThreadTerminationProcPtr )(ThreadID threadTerminated, void *terminationProcParam);
/* Prototype for debugger NewThread notification*/
typedef CALLBACK_API( void , DebuggerNewThreadProcPtr )(ThreadID threadCreated);
/* Prototype for debugger DisposeThread notification*/
typedef CALLBACK_API( void , DebuggerDisposeThreadProcPtr )(ThreadID threadDeleted);
/* Prototype for debugger schedule notification*/
typedef CALLBACK_API( ThreadID , DebuggerThreadSchedulerProcPtr )(SchedulerInfoRecPtr schedulerInfo);
typedef STACK_UPP_TYPE(ThreadEntryProcPtr)                      ThreadEntryUPP;
typedef STACK_UPP_TYPE(ThreadSchedulerProcPtr)                  ThreadSchedulerUPP;
typedef STACK_UPP_TYPE(ThreadSwitchProcPtr)                     ThreadSwitchUPP;
typedef STACK_UPP_TYPE(ThreadTerminationProcPtr)                ThreadTerminationUPP;
typedef STACK_UPP_TYPE(DebuggerNewThreadProcPtr)                DebuggerNewThreadUPP;
typedef STACK_UPP_TYPE(DebuggerDisposeThreadProcPtr)            DebuggerDisposeThreadUPP;
typedef STACK_UPP_TYPE(DebuggerThreadSchedulerProcPtr)          DebuggerThreadSchedulerUPP;
/*
 *  NewThreadEntryUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadEntryUPP
NewThreadEntryUPP(ThreadEntryProcPtr userRoutine);

/*
 *  NewThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadSchedulerUPP
NewThreadSchedulerUPP(ThreadSchedulerProcPtr userRoutine);

/*
 *  NewThreadSwitchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadSwitchUPP
NewThreadSwitchUPP(ThreadSwitchProcPtr userRoutine);

/*
 *  NewThreadTerminationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadTerminationUPP
NewThreadTerminationUPP(ThreadTerminationProcPtr userRoutine);

/*
 *  NewDebuggerNewThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DebuggerNewThreadUPP
NewDebuggerNewThreadUPP(DebuggerNewThreadProcPtr userRoutine);

/*
 *  NewDebuggerDisposeThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DebuggerDisposeThreadUPP
NewDebuggerDisposeThreadUPP(DebuggerDisposeThreadProcPtr userRoutine);

/*
 *  NewDebuggerThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DebuggerThreadSchedulerUPP
NewDebuggerThreadSchedulerUPP(DebuggerThreadSchedulerProcPtr userRoutine);

/*
 *  DisposeThreadEntryUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThreadEntryUPP(ThreadEntryUPP userUPP);

/*
 *  DisposeThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThreadSchedulerUPP(ThreadSchedulerUPP userUPP);

/*
 *  DisposeThreadSwitchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThreadSwitchUPP(ThreadSwitchUPP userUPP);

/*
 *  DisposeThreadTerminationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThreadTerminationUPP(ThreadTerminationUPP userUPP);

/*
 *  DisposeDebuggerNewThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDebuggerNewThreadUPP(DebuggerNewThreadUPP userUPP);

/*
 *  DisposeDebuggerDisposeThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDebuggerDisposeThreadUPP(DebuggerDisposeThreadUPP userUPP);

/*
 *  DisposeDebuggerThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDebuggerThreadSchedulerUPP(DebuggerThreadSchedulerUPP userUPP);

/*
 *  InvokeThreadEntryUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern voidPtr
InvokeThreadEntryUPP(
  void *          threadParam,
  ThreadEntryUPP  userUPP);

/*
 *  InvokeThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadID
InvokeThreadSchedulerUPP(
  SchedulerInfoRecPtr  schedulerInfo,
  ThreadSchedulerUPP   userUPP);

/*
 *  InvokeThreadSwitchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeThreadSwitchUPP(
  ThreadID         threadBeingSwitched,
  void *           switchProcParam,
  ThreadSwitchUPP  userUPP);

/*
 *  InvokeThreadTerminationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeThreadTerminationUPP(
  ThreadID              threadTerminated,
  void *                terminationProcParam,
  ThreadTerminationUPP  userUPP);

/*
 *  InvokeDebuggerNewThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDebuggerNewThreadUPP(
  ThreadID              threadCreated,
  DebuggerNewThreadUPP  userUPP);

/*
 *  InvokeDebuggerDisposeThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDebuggerDisposeThreadUPP(
  ThreadID                  threadDeleted,
  DebuggerDisposeThreadUPP  userUPP);

/*
 *  InvokeDebuggerThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadID
InvokeDebuggerThreadSchedulerUPP(
  SchedulerInfoRecPtr         schedulerInfo,
  DebuggerThreadSchedulerUPP  userUPP);

/*
   Thread Manager function pointers (TPP):
   on classic 68k use raw function pointers (same as UPP's)
   on classic PowerPC, use raw function pointers
   on classic PowerPC with OPAQUE_UPP_TYPES=1, use UPP's
   on CFM-68K, use UPP's
   on Carbon, use UPP's
*/

/* use UPP's*/
typedef ThreadEntryUPP                  ThreadEntryTPP;
typedef ThreadSchedulerUPP              ThreadSchedulerTPP;
typedef ThreadSwitchUPP                 ThreadSwitchTPP;
typedef ThreadTerminationUPP            ThreadTerminationTPP;
typedef DebuggerNewThreadUPP            DebuggerNewThreadTPP;
typedef DebuggerDisposeThreadUPP        DebuggerDisposeThreadTPP;
typedef DebuggerThreadSchedulerUPP      DebuggerThreadSchedulerTPP;
/*
 *  NewThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
NewThread(
  ThreadStyle      threadStyle,
  ThreadEntryTPP   threadEntry,
  void *           threadParam,
  Size             stackSize,
  ThreadOptions    options,
  void **          threadResult,       /* can be NULL */
  ThreadID *       threadMade);


/*
 *  SetThreadScheduler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
SetThreadScheduler(ThreadSchedulerTPP threadScheduler);


/*
 *  SetThreadSwitcher()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
SetThreadSwitcher(
  ThreadID          thread,
  ThreadSwitchTPP   threadSwitcher,
  void *            switchProcParam,
  Boolean           inOrOut);


/*
 *  SetThreadTerminator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
SetThreadTerminator(
  ThreadID               thread,
  ThreadTerminationTPP   threadTerminator,
  void *                 terminationProcParam);


/*
 *  SetDebuggerNotificationProcs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
SetDebuggerNotificationProcs(
  DebuggerNewThreadTPP         notifyNewThread,
  DebuggerDisposeThreadTPP     notifyDisposeThread,
  DebuggerThreadSchedulerTPP   notifyThreadScheduler);


/*
 *  CreateThreadPool()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
CreateThreadPool(
  ThreadStyle   threadStyle,
  SInt16        numToCreate,
  Size          stackSize);


/*
 *  GetFreeThreadCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetFreeThreadCount(
  ThreadStyle   threadStyle,
  SInt16 *      freeCount);


/*
 *  GetSpecificFreeThreadCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetSpecificFreeThreadCount(
  ThreadStyle   threadStyle,
  Size          stackSize,
  SInt16 *      freeCount);


/*
 *  GetDefaultThreadStackSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetDefaultThreadStackSize(
  ThreadStyle   threadStyle,
  Size *        stackSize);


/*
 *  ThreadCurrentStackSpace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
ThreadCurrentStackSpace(
  ThreadID   thread,
  UInt32 *   freeStack);


/*
 *  DisposeThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
DisposeThread(
  ThreadID   threadToDump,
  void *     threadResult,
  Boolean    recycleThread);


/*
 *  YieldToThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
YieldToThread(ThreadID suggestedThread);


/*
 *  YieldToAnyThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
YieldToAnyThread(void);


/*
 *  [Mac]GetCurrentThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
#if TARGET_OS_MAC
    #define MacGetCurrentThread GetCurrentThread
#endif
extern OSErr 
MacGetCurrentThread(ThreadID * currentThreadID);


/*
 *  GetThreadState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetThreadState(
  ThreadID       threadToGet,
  ThreadState *  threadState);


/*
 *  SetThreadState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
SetThreadState(
  ThreadID      threadToSet,
  ThreadState   newState,
  ThreadID      suggestedThread);


/*
 *  SetThreadStateEndCritical()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
SetThreadStateEndCritical(
  ThreadID      threadToSet,
  ThreadState   newState,
  ThreadID      suggestedThread);


/*
 *  ThreadBeginCritical()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
ThreadBeginCritical(void);


/*
 *  ThreadEndCritical()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
ThreadEndCritical(void);


/*
 *  GetThreadCurrentTaskRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetThreadCurrentTaskRef(ThreadTaskRef * threadTRef);


/*
 *  GetThreadStateGivenTaskRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetThreadStateGivenTaskRef(
  ThreadTaskRef   threadTRef,
  ThreadID        threadToGet,
  ThreadState *   threadState);


/*
 *  SetThreadReadyGivenTaskRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
SetThreadReadyGivenTaskRef(
  ThreadTaskRef   threadTRef,
  ThreadID        threadToSet);



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

#endif /* __THREADS__ */

