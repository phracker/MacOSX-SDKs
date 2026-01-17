/*
     File:       CarbonCore/MacMemory.h
 
     Contains:   Memory Manager Interfaces.
 
     Version:    CarbonCore-472~1
 
     Copyright:  © 1985-2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MACMEMORY__
#define __MACMEMORY__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
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
  maxSize                       = 0x7FFFFFF0 /*the largest block possible*/
};

enum {
  defaultPhysicalEntryCount     = 8
};

enum {
                                        /* values returned from the GetPageState function */
  kPageInMemory                 = 0,
  kPageOnDisk                   = 1,
  kNotPaged                     = 2
};

enum {
                                        /* masks for Zone->heapType field */
  k32BitHeap                    = 1,    /* valid in all Memory Managers */
  kNewStyleHeap                 = 2,    /* true if new Heap Manager is present */
  kNewDebugHeap                 = 4     /* true if new Heap Manager is running in debug mode on this heap */
};


/* bits for use with HGetState/HSetState*/
enum {
  kHandleIsResourceBit          = 5,
  kHandlePurgeableBit           = 6,
  kHandleLockedBit              = 7
};

/* masks for use with HGetState/HSetState*/
enum {
  kHandleIsResourceMask         = 0x20,
  kHandlePurgeableMask          = 0x40,
  kHandleLockedMask             = 0x80
};


typedef CALLBACK_API( long , GrowZoneProcPtr )(Size cbNeeded);
typedef CALLBACK_API( void , PurgeProcPtr )(Handle blockToPurge);
typedef CALLBACK_API( void , UserFnProcPtr )(void * parameter);
typedef STACK_UPP_TYPE(GrowZoneProcPtr)                         GrowZoneUPP;
typedef STACK_UPP_TYPE(PurgeProcPtr)                            PurgeUPP;
typedef STACK_UPP_TYPE(UserFnProcPtr)                           UserFnUPP;
struct Zone {
  Ptr                 bkLim;
  Ptr                 purgePtr;
  Ptr                 hFstFree;
  long                zcbFree;
  GrowZoneUPP         gzProc;
  short               moreMast;
  short               flags;
  short               cntRel;
  short               maxRel;
  short               cntNRel;
  SInt8               heapType;               /* previously "maxNRel", now holds flags (e.g. k32BitHeap)*/
  SInt8               unused;
  short               cntEmpty;
  short               cntHandles;
  long                minCBFree;
  PurgeUPP            purgeProc;
  Ptr                 sparePtr;
  Ptr                 allocPtr;
  short               heapData;
};
typedef struct Zone                     Zone;
typedef Zone *                          THz;
typedef THz *                           THzPtr;
struct MemoryBlock {
  void *              address;
  unsigned long       count;
};
typedef struct MemoryBlock              MemoryBlock;
struct LogicalToPhysicalTable {
  MemoryBlock         logical;
  MemoryBlock         physical[8];
};
typedef struct LogicalToPhysicalTable   LogicalToPhysicalTable;

typedef short                           PageState;
typedef short                           StatusRegisterContents;
enum {
  kVolumeVirtualMemoryInfoVersion1 = 1  /* first version of VolumeVirtualMemoryInfo*/
};

struct VolumeVirtualMemoryInfo {
  PBVersion           version;                /* Input: Version of the VolumeVirtualMemoryInfo structure*/
  SInt16              volumeRefNum;           /* Input: volume reference number*/
  Boolean             inUse;                  /* output: true if volume is currently used for file mapping*/
  UInt8               _fill;
  UInt32              vmOptions;              /* output: tells what volume can support (same as DriverGestaltVMOptionsResponse vmOptions bits in DriverGestalt)*/
                                              /* end of kVolumeVirtualMemoryInfoVersion1 structure*/
};
typedef struct VolumeVirtualMemoryInfo  VolumeVirtualMemoryInfo;
typedef VolumeVirtualMemoryInfo *       VolumeVirtualMemoryInfoPtr;
/*
 *  NewGrowZoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern GrowZoneUPP
NewGrowZoneUPP(GrowZoneProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewPurgeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern PurgeUPP
NewPurgeUPP(PurgeProcPtr userRoutine)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewUserFnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern UserFnUPP
NewUserFnUPP(UserFnProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeGrowZoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeGrowZoneUPP(GrowZoneUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposePurgeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposePurgeUPP(PurgeUPP userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeUserFnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeUserFnUPP(UserFnUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeGrowZoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern long
InvokeGrowZoneUPP(
  Size         cbNeeded,
  GrowZoneUPP  userUPP)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokePurgeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokePurgeUPP(
  Handle    blockToPurge,
  PurgeUPP  userUPP)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeUserFnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeUserFnUPP(
  void *     parameter,
  UserFnUPP  userUPP)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  GetApplLimit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SystemZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ApplicationZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GZSaveHnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
GZSaveHnd(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TopMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
TopMem(void)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MemError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
MemError(void)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  GetZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NewHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
NewHandle(Size byteCount)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewHandleSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NewHandleClear()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
NewHandleClear(Size byteCount)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewHandleSysClear()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HandleZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  RecoverHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
RecoverHandle(Ptr p)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RecoverHandleSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NewPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
NewPtr(Size byteCount)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewPtrSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NewPtrClear()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
NewPtrClear(Size byteCount)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewPtrSysClear()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PtrZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  MaxBlock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
MaxBlock(void)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MaxBlockSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  StackSpace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
StackSpace(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewEmptyHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
NewEmptyHandle(void)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewEmptyHandleSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  HLock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HLock(Handle h)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HUnlock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HUnlock(Handle h)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HPurge()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HPurge(Handle h)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HNoPurge()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HNoPurge(Handle h)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HLockHi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HLockHi(Handle h)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TempNewHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
TempNewHandle(
  Size     logicalSize,
  OSErr *  resultCode)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TempMaxMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Size 
TempMaxMem(Size * grow)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TempFreeMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
TempFreeMem(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InitZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SetZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CompactMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Size 
CompactMem(Size cbNeeded)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CompactMemSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PurgeMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PurgeMem(Size cbNeeded)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PurgeMemSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FreeMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
FreeMem(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FreeMemSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ReserveMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ReserveMem(Size cbNeeded)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ReserveMemSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  MaxMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Size 
MaxMem(Size * grow)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MaxMemSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SetGrowZone()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetGrowZone(GrowZoneUPP growZone)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetGrowZone()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern GrowZoneUPP 
GetGrowZone(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MoveHHi()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MoveHHi(Handle h)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposePtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposePtr(Ptr p)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPtrSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Size 
GetPtrSize(Ptr p)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPtrSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPtrSize(
  Ptr    p,
  Size   newSize)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeHandle(Handle h)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetHandleSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetHandleSize(
  Handle   h,
  Size     newSize)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* 
    NOTE
    
    GetHandleSize and GetPtrSize are documented in Inside Mac as returning 0 
    in case of an error, but the traps actually return an error code in D0.
    The glue sets D0 to 0 if an error occurred.
*/
/*
 *  GetHandleSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Size 
GetHandleSize(Handle h)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InlineGetHandleSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ReallocateHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ReallocateHandle(
  Handle   h,
  Size     byteCount)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ReallocateHandleSys()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  EmptyHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EmptyHandle(Handle h)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HSetRBit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HSetRBit(Handle h)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HClrRBit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HClrRBit(Handle h)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HGetState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt8 
HGetState(Handle h)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HSetState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HSetState(
  Handle   h,
  SInt8    flags)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PurgeSpace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PurgeSpace(
  long *  total,
  long *  contig)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    PurgeSpaceTotal and PurgeSpaceContiguous are currently only implement
    on classic 68K.  The are the same as PurgeSpace() but return just
    one value (either total space purgable or contiguous space purgable).
    Begining in Mac OS 8.5 they are available in InterfaceLib.
*/
/*
 *  PurgeSpaceTotal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern long 
PurgeSpaceTotal(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PurgeSpaceContiguous()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern long 
PurgeSpaceContiguous(void)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PurgeSpaceSysTotal()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  PurgeSpaceSysContiguous()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */



/*****************************************************************************

    The routines: 

        BlockMoveUncached, BlockMoveDataUncached
        BlockZero, BlockZeroUncached
    
    were first created for developers writing drivers. Originally they only
    existed in DriverServicesLib.  Later they were added to InterfaceLib 
    in PCI based PowerMacs.  MacOS 8.5 provides these routines in InterfaceLib
    on all supported machines. 
    
*****************************************************************************/
/*
 *  BlockMove()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */
extern void 
BlockMove(
  const void *  srcPtr,
  void *        destPtr,
  Size          byteCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BlockMoveData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DriverServicesLib 1.0 and later
 */
extern void 
BlockMoveData(
  const void *  srcPtr,
  void *        destPtr,
  Size          byteCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BlockMoveUncached()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void 
BlockMoveUncached(
  const void *  srcPtr,
  void *        destPtr,
  Size          byteCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BlockMoveDataUncached()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void 
BlockMoveDataUncached(
  const void *  srcPtr,
  void *        destPtr,
  Size          byteCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BlockZero()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void 
BlockZero(
  void *  destPtr,
  Size    byteCount)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BlockZeroUncached()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void 
BlockZeroUncached(
  void *  destPtr,
  Size    byteCount)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  MaxApplZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SetApplBase()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  MoreMasters()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MoreMasters(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MoreMasterPointers()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
MoreMasterPointers(UInt32 inCount)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetApplLimit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  InitApplZone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*  Temporary Memory routines renamed, but obsolete, in System 7.0 and later.  */
/*
 *  TempHLock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TempHLock(
  Handle   h,
  OSErr *  resultCode)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TempHUnlock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TempHUnlock(
  Handle   h,
  OSErr *  resultCode)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TempDisposeHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TempDisposeHandle(
  Handle   h,
  OSErr *  resultCode)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TempTopMem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
TempTopMem(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HoldMemory()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HoldMemory(
  void *          address,
  unsigned long   count)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UnholdMemory()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
UnholdMemory(
  void *          address,
  unsigned long   count)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LockMemory()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  LockMemoryForOutput()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  LockMemoryContiguous()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  UnlockMemory()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  MakeMemoryResident()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr 
MakeMemoryResident(
  void *          address,
  unsigned long   count)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ReleaseMemoryData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr 
ReleaseMemoryData(
  void *          address,
  unsigned long   count)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MakeMemoryNonResident()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr 
MakeMemoryNonResident(
  void *          address,
  unsigned long   count)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlushMemory()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr 
FlushMemory(
  void *          address,
  unsigned long   count)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPhysical()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetVolumeVirtualMemoryInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */


/*
 *  DeferUserFn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DebuggerGetMax()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DebuggerEnter()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DebuggerExit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DebuggerPoll()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetPageState()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PageFaultFatal()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DebuggerLockMemory()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DebuggerUnlockMemory()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  EnterSupervisorMode()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
 *  StripAddress()
 *  
 *  Summary:
 *    A trap on classic 68K, and the identity function for pre-carbon
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*
 *  Translate24To32()
 *  
 *  Summary:
 *    A trap on classic 68K, and the identity function for pre-carbon
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */



/*
 *  HandToHand()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HandToHand(Handle * theHndl)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PtrToXHand()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PtrToXHand(
  const void *  srcPtr,
  Handle        dstHndl,
  long          size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PtrToHand()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PtrToHand(
  const void *  srcPtr,
  Handle *      dstHndl,
  long          size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HandAndHand()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HandAndHand(
  Handle   hand1,
  Handle   hand2)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PtrAndHand()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PtrAndHand(
  const void *  ptr1,
  Handle        hand2,
  long          size)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Carbon routines to aid in debugging. */
/* Checks all applicable heaps for validity */
/*
 *  CheckAllHeaps()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
CheckAllHeaps(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Checks the application heap for validity */
/*
 *  IsHeapValid()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsHeapValid(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* It is invalid to pass a NULL or an empty Handle to IsHandleValid */
/*
 *  IsHandleValid()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsHandleValid(Handle h)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* It is invalid to pass a NULL Pointer to IsPointerValid */
/*
 *  IsPointerValid()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsPointerValid(Ptr p)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#if OLDROUTINENAMES
#define ApplicZone() ApplicationZone()
#define MFTempNewHandle(logicalSize, resultCode) TempNewHandle(logicalSize, resultCode)
#define MFMaxMem(grow) TempMaxMem(grow)
#define MFFreeMem() TempFreeMem()
#define MFTempHLock(h, resultCode) TempHLock(h, resultCode)
#define MFTempHUnlock(h, resultCode) TempHUnlock(h, resultCode)
#define MFTempDisposHandle(h, resultCode) TempDisposeHandle(h, resultCode)
#define MFTopMem() TempTopMem()
#define ResrvMem(cbNeeded) ReserveMem(cbNeeded)
#define DisposPtr(p) DisposePtr(p)
#define DisposHandle(h) DisposeHandle(h)
#define ReallocHandle(h, byteCount) ReallocateHandle(h, byteCount)
#endif  /* OLDROUTINENAMES */


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __MACMEMORY__ */

