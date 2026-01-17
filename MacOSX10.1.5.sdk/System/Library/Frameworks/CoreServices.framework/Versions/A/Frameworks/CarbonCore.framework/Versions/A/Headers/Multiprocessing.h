/*
     File:       CarbonCore/Multiprocessing.h
 
     Contains:   Multiprocessing interfaces
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1995-2001 DayStar Digital, Inc.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/


/*
   ===========================================================================================
   *** WARNING: You must properly check the availability of MP services before calling them!
   See the section titled "Checking API Availability".
   ===========================================================================================
*/


#ifndef __MULTIPROCESSING__
#define __MULTIPROCESSING__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=power
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/*
   ===========================================================================================
   This is the header file for version 2.2 of the Mac OS multiprocessing support.  This version
   has been totally reimplemented and has significant new services.  The main goal of the
   reimplementation has been to transfer task management into the core operating system to provide
   much more reliable and more efficient operation, including on single processor machines.
   The memory management has also been massively improved, it is much faster and wastes much
   less space.  New services include POSIX style per-task storage, timers with millisecond and
   microsecond resolutions, memory allocation at a specified alignment, and system pageable
   and RAM resident memory pools.  See the MP API documentation for details.
   The old "DayStar" debugging services (whose names began with an underscore) have been
   removed from this header.  A very few are still implemented for binary compatibility, or in
   cases where they happened to be exposed inappropriately.  (E.g. _MPIsFullyInitialized must
   be called to see if the MP API is ReallyTrulyª usable.)  New code and recompiles of old
   code should avoid use of these defunct services, except for _MPIsFullyInitialized.
   ===========================================================================================
*/


/*
   ===========================================================================================
   The following services are from the original MP API and remain supported in version 2.0:
    MPProcessors
    MPCreateTask
    MPTerminateTask
    MPCurrentTaskID
    MPYield
    MPExit
    MPCreateQueue
    MPDeleteQueue
    MPNotifyQueue
    MPWaitOnQueue
    MPCreateSemaphore
    MPCreateBinarySemaphore     (In C only, a macro that calls MPCreateSemaphore.)
    MPDeleteSemaphore
    MPSignalSemaphore
    MPWaitOnSemaphore
    MPCreateCriticalRegion
    MPDeleteCriticalRegion
    MPEnterCriticalRegion
    MPExitCriticalRegion
    MPAllocate                  (Deprecated, use MPAllocateAligned for new builds.)
    MPFree
    MPBlockCopy
    MPLibraryIsLoaded           (In C only, a macro.)
    _MPIsFullyInitialized       (See comments about checking for MP API availability.)
   ===========================================================================================
*/


/*
   ===========================================================================================
   The following services are new in version 2.0:
    MPProcessorsScheduled
    MPSetTaskWeight
    MPTaskIsPreemptive
    MPAllocateTaskStorageIndex
    MPDeallocateTaskStorageIndex
    MPSetTaskStorageValue
    MPGetTaskStorageValue
    MPSetQueueReserve
    MPCreateEvent
    MPDeleteEvent
    MPSetEvent
    MPWaitForEvent
    UpTime
    DurationToAbsolute
    AbsoluteToDuration
    MPDelayUntil
    MPCreateTimer
    MPDeleteTimer
    MPSetTimerNotify
    MPArmTimer
    MPCancelTimer
    MPSetExceptionHandler
    MPThrowException
    MPDisposeTaskException
    MPExtractTaskState
    MPSetTaskState
    MPRegisterDebugger
    MPUnregisterDebugger
    MPAllocateAligned           (Preferred over MPAllocate.)
    MPGetAllocatedBlockSize
    MPBlockClear
    MPDataToCode
    MPRemoteCall                (Preferred over _MPRPC.)
   ===========================================================================================
*/


/*
   ===========================================================================================
   The following services are new in version 2.1:
    MPCreateNotification
    MPDeleteNotification
    MPModifyNotification
    MPCauseNotification
    MPGetNextTaskID
    MPGetNextCpuID
   ===========================================================================================
*/


/*
   ===========================================================================================
   The following services are "unofficial" extensions to the original API.  They are not in
   the multiprocessing API documentation, but were in previous versions of this header.  They
   remain supported in version 2.0.  They may not be supported in other environments.
    _MPRPC                      (Deprecated, use MPRemoteCall for new builds.)
    _MPAllocateSys              (Deprecated, use MPAllocateAligned for new builds.)
    _MPTaskIsToolboxSafe
    _MPLibraryVersion
    _MPLibraryIsCompatible
   ===========================================================================================
*/


/*
   ===========================================================================================
   The following services were in previous versions of this header for "debugging only" use.
   They are NOT implemented in version 2.0.  For old builds they can be accessed by defining
   the symbol MPIncludeDefunctServices to have a nonzero value.
    _MPInitializePrintf
    _MPPrintf
    _MPDebugStr
    _MPStatusPString
    _MPStatusCString
   ===========================================================================================
*/


/*
   ¤
   ===========================================================================================
   General Types and Constants
   ===========================
*/


#define MPCopyrightNotice   \
    "Copyright © 1995-2000 Apple Computer, Inc.\n"
#define MPLibraryName "MPLibrary"
#define MPLibraryCName MPLibraryName
#define MPLibraryPName "\p" MPLibraryName
#define MP_API_Version "2.3"

enum {
  MPLibrary_MajorVersion        = 2,    /* ! When these change be sure to update the build versions*/
  MPLibrary_MinorVersion        = 3,    /* !  used in the startup check in MPInitializeAPI!*/
  MPLibrary_Release             = 1,
  MPLibrary_DevelopmentRevision = 1
};



typedef struct OpaqueMPProcessID*       MPProcessID;
typedef struct OpaqueMPTaskID*          MPTaskID;
typedef struct OpaqueMPQueueID*         MPQueueID;
typedef struct OpaqueMPSemaphoreID*     MPSemaphoreID;
typedef struct OpaqueMPCriticalRegionID*  MPCriticalRegionID;
typedef struct OpaqueMPTimerID*         MPTimerID;
typedef struct OpaqueMPEventID*         MPEventID;
typedef struct OpaqueMPAddressSpaceID*  MPAddressSpaceID;
typedef struct OpaqueMPNotificationID*  MPNotificationID;
typedef struct OpaqueMPCoherenceID*     MPCoherenceID;
typedef struct OpaqueMPCpuID*           MPCpuID;
typedef struct OpaqueMPAreaID*          MPAreaID;
typedef struct OpaqueMPConsoleID*       MPConsoleID;
typedef struct OpaqueMPOpaqueID*        MPOpaqueID;
enum {
                                        /* Values for MPOpaqueIDClass.*/
  kOpaqueAnyID                  = 0,
  kOpaqueProcessID              = 1,
  kOpaqueTaskID                 = 2,
  kOpaqueTimerID                = 3,
  kOpaqueQueueID                = 4,
  kOpaqueSemaphoreID            = 5,
  kOpaqueCriticalRegionID       = 6,
  kOpaqueCpuID                  = 7,
  kOpaqueAddressSpaceID         = 8,
  kOpaqueEventID                = 9,
  kOpaqueCoherenceID            = 10,
  kOpaqueAreaID                 = 11,
  kOpaqueNotificationID         = 12,
  kOpaqueConsoleID              = 13
};

typedef UInt32                          MPOpaqueIDClass;

enum {
  kMPNoID                       = kInvalidID /* New code should use kInvalidID everywhere.*/
};


typedef OptionBits                      MPTaskOptions;
typedef UInt32                          TaskStorageIndex;
typedef UInt32                          TaskStorageValue;
typedef ItemCount                       MPSemaphoreCount;
typedef UInt32                          MPTaskWeight;
typedef UInt32                          MPEventFlags;
typedef UInt32                          MPExceptionKind;
typedef UInt32                          MPTaskStateKind;
typedef UInt32                          MPPageSizeClass;

enum {
  kDurationImmediate            = 0L,
  kDurationForever              = 0x7FFFFFFF,
  kDurationMillisecond          = 1,
  kDurationMicrosecond          = -1
};


/*
   ¤
   ===========================================================================================
   Process/Processor Services
   ==========================
*/



/*
 *  MPProcessors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern ItemCount 
MPProcessors(void);


/* The physical total.*/

/*
 *  MPProcessorsScheduled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern ItemCount 
MPProcessorsScheduled(void);


/* Those currently in use.*/

/*
   ¤
   ===========================================================================================
   Tasking Services
   ================
*/



enum {
                                        /* For MPCreateTask options*/
  kMPCreateTaskSuspendedMask    = 1L << 0,
  kMPCreateTaskTakesAllExceptionsMask = 1L << 1,
  kMPCreateTaskNotDebuggableMask = 1L << 2,
  kMPCreateTaskValidOptionsMask = kMPCreateTaskSuspendedMask | kMPCreateTaskTakesAllExceptionsMask | kMPCreateTaskNotDebuggableMask
};


/* -------------------------------------------------------------------------------------------*/




typedef CALLBACK_API_C( OSStatus , TaskProc )(void * parameter);

/*
 *  MPCreateTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPCreateTask(
  TaskProc        entryPoint,
  void *          parameter,
  ByteCount       stackSize,
  MPQueueID       notifyQueue,
  void *          terminationParameter1,
  void *          terminationParameter2,
  MPTaskOptions   options,
  MPTaskID *      task);




/*
 *  MPTerminateTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPTerminateTask(
  MPTaskID   task,
  OSStatus   terminationStatus);




/*
 *  MPSetTaskWeight()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetTaskWeight(
  MPTaskID       task,
  MPTaskWeight   weight);




/*
 *  MPTaskIsPreemptive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern Boolean 
MPTaskIsPreemptive(MPTaskID taskID);


/* May be kInvalidID.*/

/*
 *  MPExit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
MPExit(OSStatus status);




/*
 *  MPYield()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
MPYield(void);




/*
 *  MPCurrentTaskID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern MPTaskID 
MPCurrentTaskID(void);




/*
 *  MPSetTaskType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.3 and later
 */
extern OSStatus 
MPSetTaskType(
  MPTaskID   task,
  OSType     taskType);



/* -------------------------------------------------------------------------------------------*/


/*
   ---------------------------------------------------
   ! The task storage services are new in version 2.0.
*/



/*
 *  MPAllocateTaskStorageIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPAllocateTaskStorageIndex(TaskStorageIndex * index);




/*
 *  MPDeallocateTaskStorageIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDeallocateTaskStorageIndex(TaskStorageIndex index);




/*
 *  MPSetTaskStorageValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetTaskStorageValue(
  TaskStorageIndex   index,
  TaskStorageValue   value);




/*
 *  MPGetTaskStorageValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern TaskStorageValue 
MPGetTaskStorageValue(TaskStorageIndex index);



/*
   ¤
   ===========================================================================================
   Synchronization Services
   ========================
*/



/*
 *  MPCreateQueue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPCreateQueue(MPQueueID * queue);




/*
 *  MPDeleteQueue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPDeleteQueue(MPQueueID queue);




/*
 *  MPNotifyQueue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPNotifyQueue(
  MPQueueID   queue,
  void *      param1,
  void *      param2,
  void *      param3);




/*
 *  MPWaitOnQueue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPWaitOnQueue(
  MPQueueID   queue,
  void **     param1,
  void **     param2,
  void **     param3,
  Duration    timeout);




/*
 *  MPSetQueueReserve()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetQueueReserve(
  MPQueueID   queue,
  ItemCount   count);



/* -------------------------------------------------------------------------------------------*/



/*
 *  MPCreateSemaphore()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPCreateSemaphore(
  MPSemaphoreCount   maximumValue,
  MPSemaphoreCount   initialValue,
  MPSemaphoreID *    semaphore);




/*
 *  MPDeleteSemaphore()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPDeleteSemaphore(MPSemaphoreID semaphore);




/*
 *  MPSignalSemaphore()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPSignalSemaphore(MPSemaphoreID semaphore);




/*
 *  MPWaitOnSemaphore()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPWaitOnSemaphore(
  MPSemaphoreID   semaphore,
  Duration        timeout);



#define MPCreateBinarySemaphore(semaphore)  \
            MPCreateSemaphore ( 1, 1, (semaphore) )

/* -------------------------------------------------------------------------------------------*/



/*
 *  MPCreateCriticalRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPCreateCriticalRegion(MPCriticalRegionID * criticalRegion);




/*
 *  MPDeleteCriticalRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPDeleteCriticalRegion(MPCriticalRegionID criticalRegion);




/*
 *  MPEnterCriticalRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPEnterCriticalRegion(
  MPCriticalRegionID   criticalRegion,
  Duration             timeout);




/*
 *  MPExitCriticalRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPExitCriticalRegion(MPCriticalRegionID criticalRegion);



/* -------------------------------------------------------------------------------------------*/


/*
 *  MPCreateEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPCreateEvent(MPEventID * event);



/*
 *  MPDeleteEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDeleteEvent(MPEventID event);




/*
 *  MPSetEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetEvent(
  MPEventID      event,
  MPEventFlags   flags);



/*
 *  MPWaitForEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPWaitForEvent(
  MPEventID       event,
  MPEventFlags *  flags,
  Duration        timeout);


/*
   ¤
   ===========================================================================================
   Notification Services (API)
   =====================
*/



/*
 *  MPCreateNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */
extern OSStatus 
MPCreateNotification(MPNotificationID * notificationID);




/*
 *  MPDeleteNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */
extern OSStatus 
MPDeleteNotification(MPNotificationID notificationID);




/*
 *  MPModifyNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */
extern OSStatus 
MPModifyNotification(
  MPNotificationID   notificationID,
  MPOpaqueID         anID,
  void *             notifyParam1,
  void *             notifyParam2,
  void *             notifyParam3);




/*
 *  MPModifyNotificationParameters()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.3 and later
 */
extern OSStatus 
MPModifyNotificationParameters(
  MPNotificationID   notificationID,
  MPOpaqueIDClass    kind,
  void *             notifyParam1,
  void *             notifyParam2,
  void *             notifyParam3);




/*
 *  MPCauseNotification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */
extern OSStatus 
MPCauseNotification(MPNotificationID notificationID);



/*
   ¤
   ===========================================================================================
   Timer Services
   ==============
*/


/*
   --------------------------------------------
   ! The timer services are new in version 2.0.
*/



enum {
                                        /* For MPArmTimer options*/
  kMPPreserveTimerIDMask        = 1L << 0,
  kMPTimeIsDeltaMask            = 1L << 1,
  kMPTimeIsDurationMask         = 1L << 2
};



/*
 *  MPDelayUntil()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDelayUntil(AbsoluteTime * expirationTime);




/*
 *  MPDelayUntilSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */




/*
 *  MPCreateTimer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPCreateTimer(MPTimerID * timerID);




/*
 *  MPDeleteTimer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDeleteTimer(MPTimerID timerID);




/*
 *  MPSetTimerNotify()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetTimerNotify(
  MPTimerID    timerID,
  MPOpaqueID   anID,
  void *       notifyParam1,
  void *       notifyParam2,
  void *       notifyParam3);




/*
 *  MPArmTimer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPArmTimer(
  MPTimerID       timerID,
  AbsoluteTime *  expirationTime,
  OptionBits      options);




/*
 *  MPCancelTimer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPCancelTimer(
  MPTimerID       timerID,
  AbsoluteTime *  timeRemaining);



/*
   ¤
   ===========================================================================================
   Memory Services
   ===============
*/


enum {
                                        /* Maximum allocation request size is 1GB.*/
  kMPMaxAllocSize               = 1024L * 1024 * 1024
};

enum {
                                        /* Values for the alignment parameter to MPAllocateAligned.*/
  kMPAllocateDefaultAligned     = 0,
  kMPAllocate8ByteAligned       = 3,
  kMPAllocate16ByteAligned      = 4,
  kMPAllocate32ByteAligned      = 5,
  kMPAllocate1024ByteAligned    = 10,
  kMPAllocate4096ByteAligned    = 12,
  kMPAllocateMaxAlignment       = 16,   /* Somewhat arbitrary limit on expectations.*/
  kMPAllocateAltiVecAligned     = kMPAllocate16ByteAligned, /* The P.C. name.*/
  kMPAllocateVMXAligned         = kMPAllocateAltiVecAligned, /* The older, common name.*/
  kMPAllocateVMPageAligned      = 254,  /* Pseudo value, converted at runtime.*/
  kMPAllocateInterlockAligned   = 255   /* Pseudo value, converted at runtime.*/
};



enum {
                                        /* Values for the options parameter to MPAllocateAligned.*/
  kMPAllocateClearMask          = 0x0001, /* Zero the allocated block.*/
  kMPAllocateGloballyMask       = 0x0002, /* Allocate from the globally visible pool.*/
  kMPAllocateResidentMask       = 0x0004, /* Allocate from the RAM-resident pool.*/
  kMPAllocateNoGrowthMask       = 0x0010, /* Do not attempt to grow the pool.*/
  kMPAllocateNoCreateMask       = 0x0020 /* Do not attempt to create the pool if it doesn't exist yet.*/
};


/* -------------------------------------------------------------------------------------------*/



/*
 *  MPAllocateAligned()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern LogicalAddress 
MPAllocateAligned(
  ByteCount    size,
  UInt8        alignment,
  OptionBits   options);


/* ! MPAllocateAligned is new in version 2.0.*/

/*
 *  MPAllocate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern LogicalAddress 
MPAllocate(ByteCount size);


/* Use MPAllocateAligned instead.*/

/*
 *  MPFree()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
MPFree(LogicalAddress object);




/*
 *  MPGetAllocatedBlockSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern ByteCount 
MPGetAllocatedBlockSize(LogicalAddress object);



/* -------------------------------------------------------------------------------------------*/



/*
 *  MPBlockCopy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
MPBlockCopy(
  LogicalAddress   source,
  LogicalAddress   destination,
  ByteCount        size);




/*
 *  MPBlockClear()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern void 
MPBlockClear(
  LogicalAddress   address,
  ByteCount        size);


/* ! MPBlockClear is new in version 2.0.*/

/*
 *  MPDataToCode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern void 
MPDataToCode(
  LogicalAddress   address,
  ByteCount        size);


/* ! MPDataToCode is new in version 2.0.*/
/*
   ¤
   ===========================================================================================
   Exception/Debugging Services
   ============================
*/


/*
   -------------------------------------------------------------------------------------------
   *** Important Note ***
   ----------------------
   
   The functions MPExtractTaskState and MPSetTaskState infer the size of the "info" buffer
   from the "kind" parameter.  A given value for MPTaskStateKind will always refer to a
   single specific physical buffer layout.  Should new register sets be added, or the size
   or number of any registers change, new values of MPTaskStateKind will be introduced to
   refer to the new buffer layouts.
   
   The following types for the buffers are in MachineExceptions. The correspondence between
   MPTaskStateKind values and MachineExceptions types is:
   
        kMPTaskStateRegisters               -> RegisterInformation
        kMPTaskStateFPU                     -> FPUInformation
        kMPTaskStateVectors                 -> VectorInformation
        kMPTaskStateMachine                 -> MachineInformation
        kMPTaskState32BitMemoryException    -> ExceptionInfo for old-style 32-bit memory exceptions
   
    For reference, on PowerPC the MachineExceptions types contain:
   
        RegisterInformation -> The GPRs, 32 values of 64 bits each.
        FPUInformation      -> The FPRs plus FPSCR, 32 values of 64 bits each, one value of
                                32 bits.
        VectorInformation   -> The AltiVec vector registers plus VSCR and VRSave, 32 values
                                of 128 bits each, one value of 128 bits, and one 32 bit value.
        MachineInformation  -> The CTR, LR, PC, each of 64 bits.  The CR, XER, MSR, MQ,
                                exception kind, and DSISR, each of 32 bits.  The 64 bit DAR.
        ExceptionInfo       -> Only memory exceptions are specified, 4 fields of 32 bits each.
                                Note that this type only covers memory exceptions on 32-bit CPUs!
   The following types are declared here:
        kMPTaskStateTaskInfo                -> MPTaskInfo
*/



enum {
                                        /* Values for the TaskStateKind to MPExtractTaskState and MPSetTaskState.*/
  kMPTaskStateRegisters         = 0,    /* The task general registers.*/
  kMPTaskStateFPU               = 1,    /* The task floating point registers*/
  kMPTaskStateVectors           = 2,    /* The task vector registers*/
  kMPTaskStateMachine           = 3,    /* The task machine registers*/
  kMPTaskState32BitMemoryException = 4, /* The task memory exception information for 32-bit CPUs.*/
  kMPTaskStateTaskInfo          = 5     /* Static and dynamic information about the task.*/
};



enum {
                                        /* Option bits and numbers for MPDisposeTaskException.*/
  kMPTaskPropagate              = 0,    /* The exception is propagated.*/
  kMPTaskResumeStep             = 1,    /* The task is resumed and single step is enabled.*/
  kMPTaskResumeBranch           = 2,    /* The task is resumed and branch stepping is enabled.*/
  kMPTaskResumeMask             = 0x0000, /* The task is resumed.*/
  kMPTaskPropagateMask          = 1 << kMPTaskPropagate, /* The exception is propagated.*/
  kMPTaskResumeStepMask         = 1 << kMPTaskResumeStep, /* The task is resumed and single step is enabled.*/
  kMPTaskResumeBranchMask       = 1 << kMPTaskResumeBranch /* The task is resumed and branch stepping is enabled.*/
};



enum {
                                        /* For kMPTaskStateTaskInfo, the task's runState*/
  kMPTaskBlocked                = 0,    /* Task is blocked (queued on resource)*/
  kMPTaskReady                  = 1,    /* Task is runnable*/
  kMPTaskRunning                = 2     /* Task is running*/
};

enum {
                                        /* For kMPTaskStateTaskInfo, the version of the MPTaskInfo structure requested.*/
  kMPTaskInfoVersion            = 3
};


struct MPTaskInfoVersion2 {
  PBVersion           version;                /* Version 2 of the data structure requested*/

  OSType              name;                   /* Task name*/

  OSType              queueName;              /* Task's queue owner name*/
  UInt16              runState;               /* Running, ready, blocked*/
  UInt16              lastCPU;                /* Address of CPU where task previously ran*/
  UInt32              weight;                 /* Processing weight: 1 - 10,000*/

  MPProcessID         processID;              /* Owning process ID*/

  AbsoluteTime        cpuTime;                /* Accumulated task time*/
  AbsoluteTime        schedTime;              /* Time when last scheduled*/
  AbsoluteTime        creationTime;           /* Time when task created*/

  ItemCount           codePageFaults;         /* Page faults from code execution*/
  ItemCount           dataPageFaults;         /* Page faults from data access*/
  ItemCount           preemptions;            /* Number of times task was preempted*/

  MPCpuID             cpuID;                  /* ID of CPU where task previously ran*/
};
typedef struct MPTaskInfoVersion2       MPTaskInfoVersion2;
struct MPTaskInfo {
  PBVersion           version;                /* Version 3 of the data structure requested*/

  OSType              name;                   /* Task name*/

  OSType              queueName;              /* Task's queue owner name*/
  UInt16              runState;               /* Running, ready, blocked*/
  UInt16              lastCPU;                /* Address of CPU where task previously ran*/
  UInt32              weight;                 /* Processing weight: 1 - 10,000*/

  MPProcessID         processID;              /* Owning process ID*/

  AbsoluteTime        cpuTime;                /* Accumulated task time*/
  AbsoluteTime        schedTime;              /* Time when last scheduled*/
  AbsoluteTime        creationTime;           /* Time when task created*/

  ItemCount           codePageFaults;         /* Page faults from code execution*/
  ItemCount           dataPageFaults;         /* Page faults from data access*/
  ItemCount           preemptions;            /* Number of times task was preempted*/

  MPCpuID             cpuID;                  /* ID of CPU where task previously ran.*/
  MPOpaqueID          blockedObject;          /* ID of blocked object.*/
  MPAddressSpaceID    spaceID;                /* Address space ID of this task.*/

  LogicalAddress      stackBase;              /* Base of stack (lowest address).*/
  LogicalAddress      stackLimit;             /* Stack limit (highest address).*/
  LogicalAddress      stackCurr;              /* Current stack address.*/
};
typedef struct MPTaskInfo               MPTaskInfo;
/*
    Upon a task exception, the following message is sent to the designated queue:
      1. The MPTaskID, 
      2. The exception kind. These are enumerated in the interfaces header MachineExceptions.h 
      3. N/A
*/


/* -------------------------------------------------------------------------------------------*/



/*
 *  MPSetExceptionHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetExceptionHandler(
  MPTaskID    task,
  MPQueueID   exceptionQ);




/*
 *  MPDisposeTaskException()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDisposeTaskException(
  MPTaskID     task,
  OptionBits   action);




/*
 *  MPExtractTaskState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPExtractTaskState(
  MPTaskID          task,
  MPTaskStateKind   kind,
  void *            info);




/*
 *  MPSetTaskState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetTaskState(
  MPTaskID          task,
  MPTaskStateKind   kind,
  void *            info);




/*
 *  MPThrowException()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPThrowException(
  MPTaskID          task,
  MPExceptionKind   kind);



/* -------------------------------------------------------------------------------------------*/


typedef UInt32 MPDebuggerLevel;
enum {
  kMPLowLevelDebugger           = 0x00000000, /* MacsBug-like*/
  kMPMidLevelDebugger           = 0x10000000, /* Jasik-like*/
  kMPHighLevelDebugger          = 0x20000000 /* Metrowerks-like*/
};



/*
 *  MPRegisterDebugger()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPRegisterDebugger(
  MPQueueID         queue,
  MPDebuggerLevel   level);




/*
 *  MPUnregisterDebugger()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPUnregisterDebugger(MPQueueID queue);



/*
   ¤
   ===========================================================================================
   Remote Call Services
   ====================
*/



typedef CALLBACK_API_C( void *, MPRemoteProcedure )(void * parameter);

typedef UInt8                           MPRemoteContext;
enum {
  kMPAnyRemoteContext           = 0,
  kMPOwningProcessRemoteContext = 1,
  kMPInterruptRemoteContext     = 2,
  kMPAsyncInterruptRemoteContext = 3
};



/*
 *  MPRemoteCall()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern void * 
MPRemoteCall(
  MPRemoteProcedure   remoteProc,
  void *              parameter,
  MPRemoteContext     context);


/* ! MPRemoteCall is new in version 2.0.*/
/*
   ¤
   ===========================================================================================
   Checking API Availability
   =========================
*/


/*
   ===========================================================================================
   *** WARNING: You must properly check the availability of MP services before calling them!
   ===========================================================================================
   
   Checking for the availability of the MP API is rather ugly.  This is a historical problem,
   caused by the original implementation letting itself get prepared when it really wasn't
   usable and complicated by some important clients then depending on weak linking to "work".
   (And further complicated by CFM not supporting "deferred" imports, which is how many
   programmers think weak imports work.)
   
   The end result is that the MP API library may get prepared by CFM but be totally unusable.
   This means that if you import from the MP API library, you cannot simply check for a
   resolved import to decide if MP services are available.  Worse, if you explicitly prepare
   the MP API library you cannot assume that a noErr result from GetSharedLibrary means that
   MP services are available.
   
   ¥ If you import from the MP API library you MUST:
   
        Use the MPLibraryIsLoaded macro (or equivalent code in languages other than C) to tell
        if the MP API services are available.  It is not sufficient to simply check that an
        imported symbol is resolved as is commonly done for other libraries.  The macro expands
        to the expression:
   
            ( ( (UInt32)_MPIsFullyInitialized != (UInt32)kUnresolvedCFragSymbolAddress ) &&
              ( _MPIsFullyInitialized () ) )
   
        This checks if the imported symbol _MPIsFullyInitialized is resolved and if resolved
        calls it.  Both parts must succeed for the MP API services to be available.
   
   ¥ If you explicitly prepare the MP API library you MUST:
   
        Use code similar to the following example to tell if the MP API services are available.
        It is not sufficient to depend on just a noErr result from GetSharedLibrary.
   
            OSErr                       err;
            Boolean                     mpIsAvailable           = false;
            CFragConnectionID           connID                  = kInvalidID;
            MPIsFullyInitializedProc    mpIsFullyInitialized    = NULL;
   
            err = GetSharedLibrary  ( "\pMPLibrary", kCompiledCFragArch, kReferenceCFrag,
                                      &connID, NULL, NULL );
   
            if ( err == noErr ) {
                err = FindSymbol    ( connID, "\p_MPIsFullyInitialized",
                                      (Ptr *) &mpIsFullyInitialized, NULL );
            }
   
            if ( err == noErr ) {
                mpIsAvailable = (* mpIsFullyInitialized) ();
            }
   
   ===========================================================================================
*/


/*
 *  _MPIsFullyInitialized()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern Boolean 
_MPIsFullyInitialized(void);


typedef CALLBACK_API_C( Boolean , MPIsFullyInitializedProc )(void);
#define kMPUnresolvedCFragSymbolAddress 0
#define MPLibraryIsLoaded()     \
            ( ( (UInt32)_MPIsFullyInitialized != (UInt32)kMPUnresolvedCFragSymbolAddress ) &&   \
              ( _MPIsFullyInitialized () ) )
/*
   ¤
   ===========================================================================================
   Miscellaneous Services
   ======================
*/


/*
 *  _MPLibraryVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
_MPLibraryVersion(
  const char **  versionCString,
  UInt32 *       major,
  UInt32 *       minor,
  UInt32 *       release,
  UInt32 *       revision);


/*
   ¤
   ===========================================================================================
   Unofficial Services
   ===================
*/


/*
   ===========================================================================================
   *** WARNING ***
   These services are not part of the officially documented multiprocessing API.  They may not
   be avaliable in future versions of Mac OS multiprocessing support, or in environments that
   have a different underlying OS architecture such as Mac OS on top of a microkernel, the
   Mac OS Blue Box under Mac OS X, native MP support in Mac OS X, etc.
   ===========================================================================================
*/

#if CALL_NOT_IN_CARBON
/*
 *  _MPAllocateSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */


/* Use MPAllocateAligned instead.*/
/*
 *  _MPRPC()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */


/* Use _MPRemoteCall instead.*/
/*
 *  _MPTaskIsToolboxSafe()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */


#endif  /* CALL_NOT_IN_CARBON */

/*
 *  _MPLibraryIsCompatible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern Boolean 
_MPLibraryIsCompatible(
  const char *  versionCString,
  UInt32        major,
  UInt32        minor,
  UInt32        release,
  UInt32        revision);



#define MPRPC                   _MPRPC
#define MPTaskIsToolboxSafe     _MPTaskIsToolboxSafe

/*
   ¤
   ===========================================================================================
   Defunct Services
   ================
*/

#if CALL_NOT_IN_CARBON
#ifndef MPIncludeDefunctServices
#define MPIncludeDefunctServices 0
#endif  /* !defined(MPIncludeDefunctServices) */

#if MPIncludeDefunctServices
/*
 *  _MPDebugStr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibraryObsolete 1.0 and later
 */


/*
 *  _MPStatusPString()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibraryObsolete 1.0 and later
 */


/*
 *  _MPStatusCString()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibraryObsolete 1.0 and later
 */



#include <stdarg.h>
typedef CALLBACK_API_C( void , MPPrintfHandler )(MPTaskID taskID, const char *format, va_list args);
/*
 *  _MPInitializePrintf()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibraryObsolete 1.0 and later
 */


/*
 *  _MPPrintf()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibraryObsolete 1.0 and later
 */


#endif  /* MPIncludeDefunctServices */

#endif  /* CALL_NOT_IN_CARBON */

/* ===========================================================================================*/



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

#endif /* __MULTIPROCESSING__ */

