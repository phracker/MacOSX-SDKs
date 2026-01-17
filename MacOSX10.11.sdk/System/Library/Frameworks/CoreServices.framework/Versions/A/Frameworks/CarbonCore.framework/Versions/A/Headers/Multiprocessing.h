/*
     File:       CarbonCore/Multiprocessing.h
 
     Contains:   Multiprocessing interfaces
                 The contents of this header file are deprecated.
 
     Copyright:  © 1995-2011 DayStar Digital, Inc.
*/

/*********************************************************************************************
 
 The Multiprocessing Utilities are deprecated.  Callers should use blocks, libDispatch, or pthreads.
  
*********************************************************************************************/
/*
   ===========================================================================================
   *** WARNING: You must properly check the availability of MP services before calling them!
   See the section titled "Checking API Availability".
   ===========================================================================================
*/


#ifndef __MULTIPROCESSING__
#define __MULTIPROCESSING__

#ifndef __MACTYPES__
#include <MacTypes.h>
#endif



#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=power


/*
   ======================================= NOTICE ============================================
   As of Mac OS X v10.6, the APIs in this header file are discouraged. These APIs are slated
   for deprecation in the next major release of OS X. The new dispatch APIs (see dispatch(3))
   replace the Multiprocessing APIs and the pthread threading APIs.
   ===========================================================================================
*/

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
typedef ItemCount                       TaskStorageIndex;
typedef LogicalAddress                  TaskStorageValue;
typedef ItemCount                       MPSemaphoreCount;
typedef UInt32                          MPTaskWeight;
typedef UInt32                          MPEventFlags;
typedef UInt32                          MPExceptionKind;
typedef UInt32                          MPTaskStateKind;
typedef UInt32                          MPPageSizeClass;

enum {
  kDurationImmediate            = 0,
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
 *  MPProcessors()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern ItemCount 
MPProcessors(void)                                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


/* The physical total.*/

/*
 *  MPProcessorsScheduled()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern ItemCount 
MPProcessorsScheduled(void)                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


/* Those currently in use.*/

/*
   ¤
   ===========================================================================================
   Tasking Services
   ================
*/



enum {
                                        /* For MPCreateTask options*/
  kMPCreateTaskSuspendedMask    = 1L << 0, /*    not supported on Mac OS X*/
  kMPCreateTaskTakesAllExceptionsMask = 1L << 1,
  kMPCreateTaskNotDebuggableMask = 1L << 2,
  kMPCreateTaskValidOptionsMask = kMPCreateTaskSuspendedMask | kMPCreateTaskTakesAllExceptionsMask | kMPCreateTaskNotDebuggableMask
};


/* -------------------------------------------------------------------------------------------*/




typedef CALLBACK_API_C( OSStatus , TaskProc )(void * parameter);

/*
 *  MPCreateTask()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
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
  MPTaskID *      task)                                       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPTerminateTask()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPTerminateTask(
  MPTaskID   task,
  OSStatus   terminationStatus)                               __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPSetTaskWeight()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetTaskWeight(
  MPTaskID       task,
  MPTaskWeight   weight)                                      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPTaskIsPreemptive()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern Boolean 
MPTaskIsPreemptive(MPTaskID taskID)                           __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


/* May be kInvalidID.*/

/*
 *  MPExit()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
MPExit(OSStatus status)                                       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPYield()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
MPYield(void)                                                 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPCurrentTaskID()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern MPTaskID 
MPCurrentTaskID(void)                                         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPSetTaskType()
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.3 and later
 */
extern OSStatus 
MPSetTaskType(
  MPTaskID   task,
  OSType     taskType)                                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1, __MAC_10_8, __IPHONE_NA, __IPHONE_NA);



/* -------------------------------------------------------------------------------------------*/


/*
   ---------------------------------------------------
   ! The task storage services are new in version 2.0.
*/



/*
 *  MPAllocateTaskStorageIndex()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPAllocateTaskStorageIndex(TaskStorageIndex * taskIndex)      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPDeallocateTaskStorageIndex()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDeallocateTaskStorageIndex(TaskStorageIndex taskIndex)      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPSetTaskStorageValue()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetTaskStorageValue(
  TaskStorageIndex   taskIndex,
  TaskStorageValue   value)                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPGetTaskStorageValue()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern TaskStorageValue 
MPGetTaskStorageValue(TaskStorageIndex taskIndex)             __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



/*
   ¤
   ===========================================================================================
   Synchronization Services
   ========================
*/



/*
 *  MPCreateQueue()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPCreateQueue(MPQueueID * queue)                              __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPDeleteQueue()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPDeleteQueue(MPQueueID queue)                                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPNotifyQueue()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPNotifyQueue(
  MPQueueID   queue,
  void *      param1,
  void *      param2,
  void *      param3)                                         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPWaitOnQueue()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPWaitOnQueue(
  MPQueueID   queue,
  void **     param1,
  void **     param2,
  void **     param3,
  Duration    timeout)                                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPSetQueueReserve()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetQueueReserve(
  MPQueueID   queue,
  ItemCount   count)                                          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



/* -------------------------------------------------------------------------------------------*/



/*
 *  MPCreateSemaphore()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPCreateSemaphore(
  MPSemaphoreCount   maximumValue,
  MPSemaphoreCount   initialValue,
  MPSemaphoreID *    semaphore)                               __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPDeleteSemaphore()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPDeleteSemaphore(MPSemaphoreID semaphore)                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPSignalSemaphore()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPSignalSemaphore(MPSemaphoreID semaphore)                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPWaitOnSemaphore()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPWaitOnSemaphore(
  MPSemaphoreID   semaphore,
  Duration        timeout)                                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



#define MPCreateBinarySemaphore(semaphore)  \
            MPCreateSemaphore ( 1, 1, (semaphore) )

/* -------------------------------------------------------------------------------------------*/



/*
 *  MPCreateCriticalRegion()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPCreateCriticalRegion(MPCriticalRegionID * criticalRegion)   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPDeleteCriticalRegion()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPDeleteCriticalRegion(MPCriticalRegionID criticalRegion)     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPEnterCriticalRegion()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPEnterCriticalRegion(
  MPCriticalRegionID   criticalRegion,
  Duration             timeout)                               __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPExitCriticalRegion()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern OSStatus 
MPExitCriticalRegion(MPCriticalRegionID criticalRegion)       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



/* -------------------------------------------------------------------------------------------*/


/*
 *  MPCreateEvent()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPCreateEvent(MPEventID * event)                              __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



/*
 *  MPDeleteEvent()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDeleteEvent(MPEventID event)                                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPSetEvent()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetEvent(
  MPEventID      event,
  MPEventFlags   flags)                                       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



/*
 *  MPWaitForEvent()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPWaitForEvent(
  MPEventID       event,
  MPEventFlags *  flags,
  Duration        timeout)                                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


/*
   ¤
   ===========================================================================================
   Notification Services (API)
   =====================
*/



/*
 *  MPCreateNotification()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */
extern OSStatus 
MPCreateNotification(MPNotificationID * notificationID)       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPDeleteNotification()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */
extern OSStatus 
MPDeleteNotification(MPNotificationID notificationID)         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPModifyNotification()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */
extern OSStatus 
MPModifyNotification(
  MPNotificationID   notificationID,
  MPOpaqueID         anID,
  void *             notifyParam1,
  void *             notifyParam2,
  void *             notifyParam3)                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPModifyNotificationParameters()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.3 and later
 */
extern OSStatus 
MPModifyNotificationParameters(
  MPNotificationID   notificationID,
  MPOpaqueIDClass    kind,
  void *             notifyParam1,
  void *             notifyParam2,
  void *             notifyParam3)                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPCauseNotification()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */
extern OSStatus 
MPCauseNotification(MPNotificationID notificationID)          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



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
 *  MPDelayUntil()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDelayUntil(AbsoluteTime * expirationTime)                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPDelayUntilSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibrary 2.1 and later
 */




/*
 *  MPCreateTimer()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPCreateTimer(MPTimerID * timerID)                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPDeleteTimer()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDeleteTimer(MPTimerID timerID)                              __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPSetTimerNotify()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetTimerNotify(
  MPTimerID    timerID,
  MPOpaqueID   anID,
  void *       notifyParam1,
  void *       notifyParam2,
  void *       notifyParam3)                                  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPArmTimer()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPArmTimer(
  MPTimerID       timerID,
  AbsoluteTime *  expirationTime,
  OptionBits      options)                                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPCancelTimer()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPCancelTimer(
  MPTimerID       timerID,
  AbsoluteTime *  timeRemaining)                              __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



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
 *  MPAllocateAligned()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern LogicalAddress 
MPAllocateAligned(
  ByteCount    size,
  UInt8        alignment,
  OptionBits   options)                                       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


/* ! MPAllocateAligned is new in version 2.0.*/

/*
 *  MPAllocate()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern LogicalAddress 
MPAllocate(ByteCount size)                                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


/* Use MPAllocateAligned instead.*/

/*
 *  MPFree()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
MPFree(LogicalAddress object)                                 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPGetAllocatedBlockSize()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern ByteCount 
MPGetAllocatedBlockSize(LogicalAddress object)                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



/* -------------------------------------------------------------------------------------------*/



/*
 *  MPBlockCopy()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
MPBlockCopy(
  LogicalAddress   source,
  LogicalAddress   destination,
  ByteCount        size)                                      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPBlockClear()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern void 
MPBlockClear(
  LogicalAddress   address,
  ByteCount        size)                                      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




#if !__LP64__
/*
 *  MPDataToCode()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern void 
MPDataToCode(
  LogicalAddress   address,
  ByteCount        size)                                      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


/* NOTE:    MPDataToCode is not supported for 64-bit applications. Use mprotect(2) instead.*/


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



#endif  /* !__LP64__ */

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
 *  MPSetExceptionHandler()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetExceptionHandler(
  MPTaskID    task,
  MPQueueID   exceptionQ)                                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPDisposeTaskException()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPDisposeTaskException(
  MPTaskID     task,
  OptionBits   action)                                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPExtractTaskState()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPExtractTaskState(
  MPTaskID          task,
  MPTaskStateKind   kind,
  void *            info)                                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPSetTaskState()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPSetTaskState(
  MPTaskID          task,
  MPTaskStateKind   kind,
  void *            info)                                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPThrowException()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPThrowException(
  MPTaskID          task,
  MPExceptionKind   kind)                                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



/* -------------------------------------------------------------------------------------------*/


typedef UInt32 MPDebuggerLevel;
enum {
  kMPLowLevelDebugger           = 0x00000000, /* MacsBug-like*/
  kMPMidLevelDebugger           = 0x10000000, /* Jasik-like*/
  kMPHighLevelDebugger          = 0x20000000 /* Metrowerks-like*/
};



/*
 *  MPRegisterDebugger()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPRegisterDebugger(
  MPQueueID         queue,
  MPDebuggerLevel   level)                                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);




/*
 *  MPUnregisterDebugger()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern OSStatus 
MPUnregisterDebugger(MPQueueID queue)                         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



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
 *  MPRemoteCall()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Calls a nonreentrant function and blocks the current task.
 *  
 *  Discussion:
 *    You use this function primarily to indirectly execute Mac OS
 *    system software functions. The task making the remote call is
 *    blocked until the call completes. The amount of time taken to
 *    schedule the remote procedure depends on the choice of the
 *    designated operating context. Specifying kMPAnyRemoteContext
 *    offers the lowest latency, but the called procedure may not have
 *    access to process-specific resources such as some low-memory
 *    values. Specifying kMPOwningProcessRemoteContext has higher
 *    latency because the remote procedure is deferred until the owning
 *    process becomes active. However, the remote procedure is
 *    guaranteed to execute within the owning process. Note that with
 *    the exception of functions in Multiprocessing Services, you
 *    cannot safely call any system software functions directly from a
 *    preemptive task. Even if some system software function appears to
 *    work today when called from a preemptive task, unless explicitly
 *    stated otherwise there is no guarantee that subsequent versions
 *    of the same function will continue to work in future versions of
 *    system software. In Mac OS 8 implementations of Multiprocessing
 *    Services, the only exceptions to this rule are the atomic memory
 *    operations (such as AddAtomic ) exported in the InterfaceLib
 *    shared library. Even these functions may switch to 68K mode if
 *    the operands to them are not aligned. If you need to access
 *    system software functions from a preemptive task, you must do so
 *    using the MPRemoteCall function. %%     @deprecated Use blocks to
 *    make a call on anothed dispatch queue() and block on the result.
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Parameters:
 *    
 *    remoteProc:
 *      A pointer of type MPRemoteProcedure that references the
 *      application-defined function you want to call. See
 *      MyRemoteProcedure for more information about the form of this
 *      function.
 *    
 *    parameter:
 *      A pointer to a parameter to pass to the application-defined
 *      function. For example, this value could point to a data
 *      structure or a memory location.
 *    
 *    context:
 *      A value of type MPRemoteContext that specifies which contexts
 *      (that is processes) are allowed to execute the function. See
 *      ÒRemote Call Context Option ConstantsÓ for a list of possible
 *      values.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern void * 
MPRemoteCall(
  MPRemoteProcedure   remoteProc,
  void *              parameter,
  MPRemoteContext     context)                                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


/*
 *  MPRemoteCallCFM()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer applicable now that the Multiprocessing Utilities have
 *    been deprecated.
 *  
 *  Summary:
 *    Calls a nonreentrant function and blocks the current task.
 *  
 *  Discussion:
 *    You use this function primarily to indirectly execute Mac OS
 *    system software functions. The task making the remote call is
 *    blocked until the call completes. The amount of time taken to
 *    schedule the remote procedure depends on the choice of the
 *    designated operating context. Specifying kMPAnyRemoteContext
 *    offers the lowest latency, but the called procedure may not have
 *    access to process-specific resources such as some low-memory
 *    values. Specifying kMPOwningProcessRemoteContext has higher
 *    latency because the remote procedure is deferred until the owning
 *    process becomes active. However, the remote procedure is
 *    guaranteed to execute within the owning process. Note that with
 *    the exception of functions in Multiprocessing Services, you
 *    cannot safely call any system software functions directly from a
 *    preemptive task. Even if some system software function appears to
 *    work today when called from a preemptive task, unless explicitly
 *    stated otherwise there is no guarantee that subsequent versions
 *    of the same function will continue to work in future versions of
 *    system software.
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Parameters:
 *    
 *    remoteProc:
 *      A pointer of type MPRemoteProcedure to a CFM function that
 *      references the application-defined function you want to call.
 *      See MyRemoteProcedure for more information about the form of
 *      this function.
 *    
 *    parameter:
 *      A pointer to a parameter to pass to the application-defined
 *      function. For example, this value could point to a data
 *      structure or a memory location.
 *    
 *    context:
 *      A value of type MPRemoteContext that specifies which contexts
 *      (that is processes) are allowed to execute the function. See
 *      ÒRemote Call Context Option ConstantsÓ for a list of possible
 *      values.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in MPLibrary 2.0 and later
 */
extern void * 
MPRemoteCallCFM(
  MPRemoteProcedure   remoteProc,
  void *              parameter,
  MPRemoteContext     context)                                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


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
 *  _MPIsFullyInitialized()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern Boolean 
_MPIsFullyInitialized(void)                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


typedef CALLBACK_API_C( Boolean , MPIsFullyInitializedProc )(void);
#define kMPUnresolvedCFragSymbolAddress 0
#define MPLibraryIsLoaded()     (true)
/*
   ¤
   ===========================================================================================
   Miscellaneous Services
   ======================
*/


/*
 *  _MPLibraryVersion()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern void 
_MPLibraryVersion(
  const char **  versionCString,
  UInt32 *       major,
  UInt32 *       minor,
  UInt32 *       release,
  UInt32 *       revision)                                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);


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
 *  _MPLibraryIsCompatible()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.7
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MPLibrary 1.0 and later
 */
extern Boolean 
_MPLibraryIsCompatible(
  const char *  versionCString,
  UInt32        major,
  UInt32        minor,
  UInt32        release,
  UInt32        revision)                                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_7, __IPHONE_NA, __IPHONE_NA);



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



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __MULTIPROCESSING__ */

