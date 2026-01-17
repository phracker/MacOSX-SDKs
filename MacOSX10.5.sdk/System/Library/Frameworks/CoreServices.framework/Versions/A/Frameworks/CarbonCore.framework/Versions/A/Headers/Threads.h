/*
     File:       CarbonCore/Threads.h
 
     Contains:   Thread Manager Interfaces.
 
     Version:    CarbonCore-783~134
 
     Copyright:  © 1991-2006 by Apple Computer, Inc., all rights reserved.
 
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



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

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
typedef unsigned long                   ThreadID;
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
NewThreadEntryUPP(ThreadEntryProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadSchedulerUPP
NewThreadSchedulerUPP(ThreadSchedulerProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewThreadSwitchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadSwitchUPP
NewThreadSwitchUPP(ThreadSwitchProcPtr userRoutine)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewThreadTerminationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThreadTerminationUPP
NewThreadTerminationUPP(ThreadTerminationProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDebuggerNewThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DebuggerNewThreadUPP
NewDebuggerNewThreadUPP(DebuggerNewThreadProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDebuggerDisposeThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DebuggerDisposeThreadUPP
NewDebuggerDisposeThreadUPP(DebuggerDisposeThreadProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDebuggerThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DebuggerThreadSchedulerUPP
NewDebuggerThreadSchedulerUPP(DebuggerThreadSchedulerProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeThreadEntryUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThreadEntryUPP(ThreadEntryUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThreadSchedulerUPP(ThreadSchedulerUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeThreadSwitchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThreadSwitchUPP(ThreadSwitchUPP userUPP)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeThreadTerminationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThreadTerminationUPP(ThreadTerminationUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDebuggerNewThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDebuggerNewThreadUPP(DebuggerNewThreadUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDebuggerDisposeThreadUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDebuggerDisposeThreadUPP(DebuggerDisposeThreadUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDebuggerThreadSchedulerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDebuggerThreadSchedulerUPP(DebuggerThreadSchedulerUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ThreadEntryUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ThreadSchedulerUPP   userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ThreadSwitchUPP  userUPP)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ThreadTerminationUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  DebuggerNewThreadUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  DebuggerDisposeThreadUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  DebuggerThreadSchedulerUPP  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if __MACH__
  #ifdef __cplusplus
    inline ThreadEntryUPP                                       NewThreadEntryUPP(ThreadEntryProcPtr userRoutine) { return userRoutine; }
    inline ThreadSchedulerUPP                                   NewThreadSchedulerUPP(ThreadSchedulerProcPtr userRoutine) { return userRoutine; }
    inline ThreadSwitchUPP                                      NewThreadSwitchUPP(ThreadSwitchProcPtr userRoutine) { return userRoutine; }
    inline ThreadTerminationUPP                                 NewThreadTerminationUPP(ThreadTerminationProcPtr userRoutine) { return userRoutine; }
    inline DebuggerNewThreadUPP                                 NewDebuggerNewThreadUPP(DebuggerNewThreadProcPtr userRoutine) { return userRoutine; }
    inline DebuggerDisposeThreadUPP                             NewDebuggerDisposeThreadUPP(DebuggerDisposeThreadProcPtr userRoutine) { return userRoutine; }
    inline DebuggerThreadSchedulerUPP                           NewDebuggerThreadSchedulerUPP(DebuggerThreadSchedulerProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeThreadEntryUPP(ThreadEntryUPP) { }
    inline void                                                 DisposeThreadSchedulerUPP(ThreadSchedulerUPP) { }
    inline void                                                 DisposeThreadSwitchUPP(ThreadSwitchUPP) { }
    inline void                                                 DisposeThreadTerminationUPP(ThreadTerminationUPP) { }
    inline void                                                 DisposeDebuggerNewThreadUPP(DebuggerNewThreadUPP) { }
    inline void                                                 DisposeDebuggerDisposeThreadUPP(DebuggerDisposeThreadUPP) { }
    inline void                                                 DisposeDebuggerThreadSchedulerUPP(DebuggerThreadSchedulerUPP) { }
    inline voidPtr                                              InvokeThreadEntryUPP(void * threadParam, ThreadEntryUPP userUPP) { return (*userUPP)(threadParam); }
    inline ThreadID                                             InvokeThreadSchedulerUPP(SchedulerInfoRecPtr schedulerInfo, ThreadSchedulerUPP userUPP) { return (*userUPP)(schedulerInfo); }
    inline void                                                 InvokeThreadSwitchUPP(ThreadID threadBeingSwitched, void * switchProcParam, ThreadSwitchUPP userUPP) { (*userUPP)(threadBeingSwitched, switchProcParam); }
    inline void                                                 InvokeThreadTerminationUPP(ThreadID threadTerminated, void * terminationProcParam, ThreadTerminationUPP userUPP) { (*userUPP)(threadTerminated, terminationProcParam); }
    inline void                                                 InvokeDebuggerNewThreadUPP(ThreadID threadCreated, DebuggerNewThreadUPP userUPP) { (*userUPP)(threadCreated); }
    inline void                                                 InvokeDebuggerDisposeThreadUPP(ThreadID threadDeleted, DebuggerDisposeThreadUPP userUPP) { (*userUPP)(threadDeleted); }
    inline ThreadID                                             InvokeDebuggerThreadSchedulerUPP(SchedulerInfoRecPtr schedulerInfo, DebuggerThreadSchedulerUPP userUPP) { return (*userUPP)(schedulerInfo); }
  #else
    #define NewThreadEntryUPP(userRoutine)                      ((ThreadEntryUPP)userRoutine)
    #define NewThreadSchedulerUPP(userRoutine)                  ((ThreadSchedulerUPP)userRoutine)
    #define NewThreadSwitchUPP(userRoutine)                     ((ThreadSwitchUPP)userRoutine)
    #define NewThreadTerminationUPP(userRoutine)                ((ThreadTerminationUPP)userRoutine)
    #define NewDebuggerNewThreadUPP(userRoutine)                ((DebuggerNewThreadUPP)userRoutine)
    #define NewDebuggerDisposeThreadUPP(userRoutine)            ((DebuggerDisposeThreadUPP)userRoutine)
    #define NewDebuggerThreadSchedulerUPP(userRoutine)          ((DebuggerThreadSchedulerUPP)userRoutine)
    #define DisposeThreadEntryUPP(userUPP)
    #define DisposeThreadSchedulerUPP(userUPP)
    #define DisposeThreadSwitchUPP(userUPP)
    #define DisposeThreadTerminationUPP(userUPP)
    #define DisposeDebuggerNewThreadUPP(userUPP)
    #define DisposeDebuggerDisposeThreadUPP(userUPP)
    #define DisposeDebuggerThreadSchedulerUPP(userUPP)
    #define InvokeThreadEntryUPP(threadParam, userUPP)          (*userUPP)(threadParam)
    #define InvokeThreadSchedulerUPP(schedulerInfo, userUPP)    (*userUPP)(schedulerInfo)
    #define InvokeThreadSwitchUPP(threadBeingSwitched, switchProcParam, userUPP) (*userUPP)(threadBeingSwitched, switchProcParam)
    #define InvokeThreadTerminationUPP(threadTerminated, terminationProcParam, userUPP) (*userUPP)(threadTerminated, terminationProcParam)
    #define InvokeDebuggerNewThreadUPP(threadCreated, userUPP)  (*userUPP)(threadCreated)
    #define InvokeDebuggerDisposeThreadUPP(threadDeleted, userUPP) (*userUPP)(threadDeleted)
    #define InvokeDebuggerThreadSchedulerUPP(schedulerInfo, userUPP) (*userUPP)(schedulerInfo)
  #endif
#endif

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
  ThreadID *       threadMade)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetThreadScheduler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
SetThreadScheduler(ThreadSchedulerTPP threadScheduler)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean           inOrOut)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                 terminationProcParam)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  DebuggerThreadSchedulerTPP   notifyThreadScheduler)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Size          stackSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Size *        stackSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ThreadID     thread,
  ByteCount *  freeStack)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean    recycleThread)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  YieldToThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
YieldToThread(ThreadID suggestedThread)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  YieldToAnyThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
YieldToAnyThread(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
MacGetCurrentThread(ThreadID * currentThreadID)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ThreadState *  threadState)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ThreadID      suggestedThread)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ThreadID      suggestedThread)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ThreadBeginCritical()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
ThreadBeginCritical(void)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ThreadEndCritical()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
ThreadEndCritical(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetThreadCurrentTaskRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetThreadCurrentTaskRef(ThreadTaskRef * threadTRef)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ThreadState *   threadState)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ThreadID        threadToSet)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__
/* This routine was never implemented on Mac OS X.*/
/*
 *  GetFreeThreadCount()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetFreeThreadCount(
  ThreadStyle   threadStyle,
  SInt16 *      freeCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/* This routine was never implemented on Mac OS X.*/
/*
 *  GetSpecificFreeThreadCount()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ThreadsLib 1.0 and later
 */
extern OSErr 
GetSpecificFreeThreadCount(
  ThreadStyle   threadStyle,
  Size          stackSize,
  SInt16 *      freeCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


#endif  /* !__LP64__ */


#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __THREADS__ */

