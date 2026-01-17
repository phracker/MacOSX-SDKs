/*
     File:       CarbonCore/DriverServices.h
 
     Contains:   Driver Services Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1985-2006 by Apple Computer, Inc., all rights reserved
 
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

#ifndef __DEVICES__
#include <CarbonCore/Devices.h>
#endif

#ifndef __DRIVERSYNCHRONIZATION__
#include <CarbonCore/DriverSynchronization.h>
#endif

#ifndef __NAMEREGISTRY__
#include <CarbonCore/NameRegistry.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=power

/******************************************************************
 *
 *      Previously in Kernel.h
 *
 ******************************************************************/
/* Kernel basics*/
typedef struct OpaqueIOPreparationID*   IOPreparationID;
typedef struct OpaqueSoftwareInterruptID*  SoftwareInterruptID;
typedef struct OpaqueTaskID*            TaskID;
typedef struct OpaqueTimerID*           TimerID;
/* Tasking*/
typedef UInt32                          ExecutionLevel;
enum {
  kTaskLevel                    = 0,
  kSoftwareInterruptLevel       = 1,
  kAcceptFunctionLevel          = 2,
  kKernelLevel                  = 3,
  kSIHAcceptFunctionLevel       = 4,
  kSecondaryInterruptLevel      = 5,
  kHardwareInterruptLevel       = 6,
  kMPTaskLevel                  = 7
};

typedef CALLBACK_API_C( void , SoftwareInterruptHandler )(void *p1, void *p2);
typedef CALLBACK_API_C( OSStatus , SecondaryInterruptHandler2 )(void *p1, void *p2);
#define kCurrentAddressSpaceID ((AddressSpaceID) -1)
/* Memory System basics*/
struct LogicalAddressRange {
  LogicalAddress      address;
  ByteCount           count;
};
typedef struct LogicalAddressRange      LogicalAddressRange;
typedef LogicalAddressRange *           LogicalAddressRangePtr;
struct PhysicalAddressRange {
  PhysicalAddress     address;
  ByteCount           count;
};
typedef struct PhysicalAddressRange     PhysicalAddressRange;
typedef PhysicalAddressRange *          PhysicalAddressRangePtr;
/* For PrepareMemoryForIO and CheckpointIO*/
typedef OptionBits                      IOPreparationOptions;
enum {
  kIOMultipleRanges             = 0x00000001,
  kIOLogicalRanges              = 0x00000002,
  kIOMinimalLogicalMapping      = 0x00000004,
  kIOShareMappingTables         = 0x00000008,
  kIOIsInput                    = 0x00000010,
  kIOIsOutput                   = 0x00000020,
  kIOCoherentDataPath           = 0x00000040,
  kIOTransferIsLogical          = 0x00000080,
  kIOClientIsUserMode           = 0x00000080
};

typedef OptionBits                      IOPreparationState;
enum {
  kIOStateDone                  = 0x00000001
};

enum {
  kInvalidPageAddress           = (-1)
};

struct AddressRange {
  void *              base;
  ByteCount           length;
};
typedef struct AddressRange             AddressRange;
/* C's treatment of arrays and array pointers is atypical*/

typedef LogicalAddress *                LogicalMappingTablePtr;
typedef PhysicalAddress *               PhysicalMappingTablePtr;
typedef AddressRange *                  AddressRangeTablePtr;
struct MultipleAddressRange {
  ItemCount           entryCount;
  AddressRangeTablePtr  rangeTable;
};
typedef struct MultipleAddressRange     MultipleAddressRange;
/*
   Separate C definition so that union has a name.  A future version of the interfacer
   tool will allow a name (that gets thrown out in Pascal and Asm).
*/
struct IOPreparationTable {
  IOPreparationOptions  options;
  IOPreparationState  state;
  IOPreparationID     preparationID;
  AddressSpaceID      addressSpace;
  ByteCount           granularity;
  ByteCount           firstPrepared;
  ByteCount           lengthPrepared;
  ItemCount           mappingEntryCount;
  LogicalMappingTablePtr  logicalMapping;
  PhysicalMappingTablePtr  physicalMapping;
  union {
    AddressRange        range;
    MultipleAddressRange  multipleRanges;
  }                       rangeInfo;
};
typedef struct IOPreparationTable       IOPreparationTable;

typedef OptionBits                      IOCheckpointOptions;
enum {
  kNextIOIsInput                = 0x00000001,
  kNextIOIsOutput               = 0x00000002,
  kMoreIOTransfers              = 0x00000004
};

/* For SetProcessorCacheMode*/

typedef UInt32                          ProcessorCacheMode;
enum {
  kProcessorCacheModeDefault    = 0,
  kProcessorCacheModeInhibited  = 1,
  kProcessorCacheModeWriteThrough = 2,
  kProcessorCacheModeCopyBack   = 3
};

/*
   For GetPageInformation
   (Note: if kPageInformationVersion fails, try 0 -- old versions of DSL defined  kPageInformationVersion as 0)
*/

enum {
  kPageInformationVersion       = 1
};

typedef UInt32                          PageStateInformation;
enum {
  kPageIsProtected              = 0x00000001,
  kPageIsProtectedPrivileged    = 0x00000002,
  kPageIsModified               = 0x00000004,
  kPageIsReferenced             = 0x00000008,
  kPageIsLockedResident         = 0x00000010, /* held and locked resident*/
  kPageIsInMemory               = 0x00000020,
  kPageIsShared                 = 0x00000040,
  kPageIsWriteThroughCached     = 0x00000080,
  kPageIsCopyBackCached         = 0x00000100,
  kPageIsHeldResident           = 0x00000200, /* held resident - use kPageIsLockedResident to check for locked state*/
  kPageIsLocked                 = kPageIsLockedResident, /* Deprecated*/
  kPageIsResident               = kPageIsInMemory /* Deprecated*/
};

struct PageInformation {
  AreaID              area;
  ItemCount           count;
  PageStateInformation  information[1];
};
typedef struct PageInformation          PageInformation;
typedef PageInformation *               PageInformationPtr;

/*  Tasks  */
/*
 *  CurrentExecutionLevel()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CurrentTaskID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  DelayFor()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  InPrivilegedMode()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */



/*  Software Interrupts  */
/*
 *  CreateSoftwareInterrupt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */



/*
 *  SendSoftwareInterrupt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  DeleteSoftwareInterrupt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*  Secondary Interrupts  */
/*
 *  CallSecondaryInterruptHandler2()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  QueueSecondaryInterruptHandler()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*  Timers  */
/*
 *  SetInterruptTimer()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  SetPersistentTimer()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CancelTimer()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */



/*  I/O related Operations  */
/*
 *  PrepareMemoryForIO()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CheckpointIO()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */



/*  Memory Operations  */
/*
 *  GetPageInformation()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*  Processor Cache Related  */
/*
 *  SetProcessorCacheMode()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/******************************************************************
 *
 *      Was in DriverSupport.h or DriverServices.h
 *
 ******************************************************************/
#define kAAPLDeviceLogicalAddress "AAPL,address"
typedef LogicalAddress *                DeviceLogicalAddressPtr;
enum {
  durationMicrosecond           = -1L,  /* Microseconds are negative*/
  durationMillisecond           = 1L,   /* Milliseconds are positive*/
  durationSecond                = 1000L, /* 1000 * durationMillisecond*/
  durationMinute                = 60000L, /* 60 * durationSecond,*/
  durationHour                  = 3600000L, /* 60 * durationMinute,*/
  durationDay                   = 86400000L, /* 24 * durationHour,*/
  durationNoWait                = 0L,   /* don't block*/
  durationForever               = 0x7FFFFFFF /* no time limit*/
};

enum {
  k8BitAccess                   = 0,    /* access as 8 bit*/
  k16BitAccess                  = 1,    /* access as 16 bit*/
  k32BitAccess                  = 2     /* access as 32 bit*/
};

typedef UnsignedWide                    Nanoseconds;

/*
 *  IOCommandIsComplete()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  GetIOCommandInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  UpdateDeviceActivity()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  BlockCopy()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PoolAllocateResident()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PoolDeallocate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  GetLogicalPageSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  GetDataCacheLineSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  FlushProcessorCache()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  MemAllocatePhysicallyContiguous()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  MemDeallocatePhysicallyContiguous()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */



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



/*
 *  PBQueueInit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PBQueueCreate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PBQueueDelete()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PBEnqueue()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PBEnqueueLast()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PBDequeue()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PBDequeueFirst()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PBDequeueLast()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CStrCopy()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PStrCopy()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CStrNCopy()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PStrNCopy()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CStrCat()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PStrCat()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CStrNCat()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PStrNCat()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PStrToCStr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CStrToPStr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CStrCmp()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PStrCmp()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CStrNCmp()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PStrNCmp()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  CStrLen()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  PStrLen()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  DeviceProbe()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  DelayForHardware()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */




/******************************************************************
 *
 *      Was in Interrupts.h 
 *
 ******************************************************************/
/*  Interrupt types  */
typedef struct OpaqueInterruptSetID*    InterruptSetID;
typedef long                            InterruptMemberNumber;
struct InterruptSetMember {
  InterruptSetID      setID;
  InterruptMemberNumber  member;
};
typedef struct InterruptSetMember       InterruptSetMember;
enum {
  kISTChipInterruptSource       = 0,
  kISTOutputDMAInterruptSource  = 1,
  kISTInputDMAInterruptSource   = 2,
  kISTPropertyMemberCount       = 3
};

typedef InterruptSetMember              ISTProperty[3];
#define kISTPropertyName    "driver-ist" 

typedef long                            InterruptReturnValue;
enum {
  kFirstMemberNumber            = 1,
  kIsrIsComplete                = 0,
  kIsrIsNotComplete             = -1,
  kMemberNumberParent           = -2
};

typedef Boolean                         InterruptSourceState;
enum {
  kSourceWasEnabled             = true,
  kSourceWasDisabled            = false
};


typedef CALLBACK_API_C( InterruptMemberNumber , InterruptHandler )(InterruptSetMember ISTmember, void *refCon, UInt32 theIntCount);
typedef CALLBACK_API_C( void , InterruptEnabler )(InterruptSetMember ISTmember, void *refCon);
typedef CALLBACK_API_C( InterruptSourceState , InterruptDisabler )(InterruptSetMember ISTmember, void *refCon);
enum {
  kReturnToParentWhenComplete   = 0x00000001,
  kReturnToParentWhenNotComplete = 0x00000002
};

typedef OptionBits                      InterruptSetOptions;
/*  Interrupt Services  */
/*
 *  CreateInterruptSet()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */



/*
 *  InstallInterruptFunctions()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */



/*
 *  GetInterruptFunctions()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  ChangeInterruptSetOptions()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */


/*
 *  GetInterruptSetOptions()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */





#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __DRIVERSERVICES__ */

