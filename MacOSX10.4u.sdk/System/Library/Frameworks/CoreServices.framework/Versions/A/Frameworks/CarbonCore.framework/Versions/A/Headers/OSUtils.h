/*
     File:       CarbonCore/OSUtils.h
 
     Contains:   OS Utilities Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1985-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __OSUTILS__
#define __OSUTILS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

/*  HandToHand and other memory utilties were moved to MacMemory.h */
#ifndef __MACMEMORY__
#include <CarbonCore/MacMemory.h>
#endif

/*  Date and Time utilties were moved to DateTimeUtils.h */
#ifndef __DATETIMEUTILS__
#include <CarbonCore/DateTimeUtils.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
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
  useFree                       = 0,
  useATalk                      = 1,
  useAsync                      = 2,
  useExtClk                     = 3,    /*Externally clocked*/
  useMIDI                       = 4
};

enum {
  false32b                      = 0,    /*24 bit addressing error*/
  true32b                       = 1     /*32 bit addressing error*/
};

enum {
                                        /* result types for RelString Call */
  sortsBefore                   = -1,   /*first string < second string*/
  sortsEqual                    = 0,    /*first string = second string*/
  sortsAfter                    = 1     /*first string > second string*/
};

enum {
  dummyType                     = 0,
  vType                         = 1,
  ioQType                       = 2,
  drvQType                      = 3,
  evType                        = 4,
  fsQType                       = 5,
  sIQType                       = 6,
  dtQType                       = 7,
  nmType                        = 8
};

typedef SignedByte                      QTypes;
#if ALLOW_OBSOLETE_CARBON_OSUTILS
struct SysParmType {
  UInt8               valid;
  UInt8               aTalkA;
  UInt8               aTalkB;
  UInt8               config;
  short               portA;
  short               portB;
  long                alarm;
  short               font;
  short               kbdPrint;
  short               volClik;
  short               misc;
};
typedef struct SysParmType              SysParmType;
typedef SysParmType *                   SysPPtr;
#else
typedef void *                          SysPPtr;
#endif  /* ALLOW_OBSOLETE_CARBON_OSUTILS */

struct QElem {
  struct QElem *      qLink;
  short               qType;
  short               qData[1];
};
typedef struct QElem                    QElem;
typedef QElem *                         QElemPtr;
struct QHdr {
  volatile short      qFlags;
  volatile QElemPtr   qHead;
  volatile QElemPtr   qTail;
};
typedef struct QHdr                     QHdr;
typedef QHdr *                          QHdrPtr;
typedef CALLBACK_API( void , DeferredTaskProcPtr )(long dtParam);
typedef STACK_UPP_TYPE(DeferredTaskProcPtr)                     DeferredTaskUPP;
/*
 *  NewDeferredTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DeferredTaskUPP
NewDeferredTaskUPP(DeferredTaskProcPtr userRoutine)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDeferredTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDeferredTaskUPP(DeferredTaskUPP userUPP)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDeferredTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDeferredTaskUPP(
  long             dtParam,
  DeferredTaskUPP  userUPP)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

struct DeferredTask {
  volatile QElemPtr   qLink;
  short               qType;
  volatile short      dtFlags;
  DeferredTaskUPP     dtAddr;
  long                dtParam;
  long                dtReserved;
};
typedef struct DeferredTask             DeferredTask;
typedef DeferredTask *                  DeferredTaskPtr;
/* 
    In order for MachineLocation to be endian-safe, a new member 
    has been added to the 'u' union in the structure. You are 
    encouraged to use the new member instead of the old one.
    
    If your code looked like this:
    
        MachineLocation.u.dlsDelta = isDLS? 0x80: 0x00;
    
    you should change it to this:
    
        MachineLocation.u.dls.Delta = isDLS? 0x80: 0x00;
    
    to be endian safe. The gmtDelta remains the same; the low 24-bits
    are used. Remember that order of assignment DOES matter:
    
    This will overwrite results:
    
        MachineLocation.u.dls.Delta = 0xAA;         // u = 0xAAGGGGGG; G=Garbage
        MachineLocation.u.gmtDelta = 0xBBBBBB;      // u = 0x00BBBBBB;
    
    when in fact reversing the assignment would have preserved the values:

        MachineLocation.u.gmtDelta = 0xBBBBBB;      // u = 0x00BBBBBB;  
        MachineLocation.u.dls.Delta = 0xAA;         // u = 0xAABBBBBB;
        
    NOTE:   The information regarding dlsDelta in Inside Mac is INCORRECT.
            It's always 0x80 for daylight-saving time or 0x00 for standard time.
*/
struct MachineLocation {
    Fract   latitude;
    Fract   longitude;
    union {
    #if TARGET_RT_BIG_ENDIAN
        SInt8 dlsDelta;
    #endif
        long    gmtDelta;           /* use low 24-bits only */
        struct {
        #if TARGET_RT_LITTLE_ENDIAN
            SInt8   pad[3];
        #endif
            SInt8   Delta;          /* signed byte; daylight savings delta */
        } dls;
    } u;
};
typedef struct MachineLocation MachineLocation;
/*
 *  IsMetric()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
IsMetric(void)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSysPPtr()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Don't use this function; it always returns NULL on Mac OS X.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SysPPtr 
GetSysPPtr(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
    NOTE: SysBeep() has been moved to Sound.h.  
          We could not automatically #include Sound.h in this file
          because Sound.h indirectly #include's OSUtils.h which
          would make a circular include.
*/
/*
 *  DTInstall()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Deferred Task Manager is deprecated.  Look into restructuring
 *    your code to use threads, or MPTasks, or some other threading
 *    solution.
 *  
 *  Summary:
 *    Adds the specified task record to the deferred-task queue.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DTInstall(DeferredTaskPtr dtTaskPtr)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  DTUninstall()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Deferred Task Manager is deprecated.  Look into restructuring
 *    your code to use threads, or MPTasks, or some other threading
 *    solution.
 *  
 *  Summary:
 *    Adds the specified task record to the deferred-task queue.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
DTUninstall(DeferredTaskPtr dtTaskPtr)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



#if TARGET_API_MAC_CARBON
#define GetMMUMode() ((SInt8)true32b)
#define SwapMMUMode(x) (*(SInt8*)(x) = true32b)
#endif
/*
 *  Delay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Delay(
  unsigned long    numTicks,
  unsigned long *  finalTicks)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WriteParam()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function no longer does anything on Mac OS X; you should
 *    remove all calls to it from your code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
WriteParam(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  Enqueue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Enqueue(
  QElemPtr   qElement,
  QHdrPtr    qHeader)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Dequeue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
Dequeue(
  QElemPtr   qElement,
  QHdrPtr    qHeader)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetCurrentA5()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    You no longer need to use SetCurrentA5() on Mac OS X.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
SetCurrentA5(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetA5()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    You no longer need to use SetA5() on Mac OS X.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
SetA5(long newA5)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  InitUtil()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
InitUtil(void)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/*
 *  MakeDataExecutable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern void 
MakeDataExecutable(
  void *          baseAddress,
  unsigned long   length)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ReadLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ReadLocation(MachineLocation * loc)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WriteLocation()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
WriteLocation(const MachineLocation * loc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  TickCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt32 
TickCount(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CSCopyUserName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
CSCopyUserName(Boolean useShortName)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CSCopyMachineName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
CSCopyMachineName(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if OLDROUTINENAMES
#define IUMetric() IsMetric()
#endif  /* OLDROUTINENAMES */

#if ALLOW_OBSOLETE_CARBON_OSUTILS
/*
    NOTE: SysEnvirons is obsolete.  You should be using Gestalt.
*/
/* Environs Equates */
enum {
  curSysEnvVers                 = 2     /*Updated to equal latest SysEnvirons version*/
};

struct SysEnvRec {
  short               environsVersion;
  short               machineType;
  short               systemVersion;
  short               processor;
  Boolean             hasFPU;
  Boolean             hasColorQD;
  short               keyBoardType;
  short               atDrvrVersNum;
  short               sysVRefNum;
};
typedef struct SysEnvRec                SysEnvRec;
enum {
                                        /* Machine Types */
  envMac                        = -1,
  envXL                         = -2,
  envMachUnknown                = 0,
  env512KE                      = 1,
  envMacPlus                    = 2,
  envSE                         = 3,
  envMacII                      = 4,
  envMacIIx                     = 5,
  envMacIIcx                    = 6,
  envSE30                       = 7,
  envPortable                   = 8,
  envMacIIci                    = 9,
  envMacIIfx                    = 11
};

enum {
                                        /* CPU types */
  envCPUUnknown                 = 0,
  env68000                      = 1,
  env68010                      = 2,
  env68020                      = 3,
  env68030                      = 4,
  env68040                      = 5
};

enum {
                                        /* Keyboard types */
  envUnknownKbd                 = 0,
  envMacKbd                     = 1,
  envMacAndPad                  = 2,
  envMacPlusKbd                 = 3,
  envAExtendKbd                 = 4,
  envStandADBKbd                = 5,
  envPrtblADBKbd                = 6,
  envPrtblISOKbd                = 7,
  envStdISOADBKbd               = 8,
  envExtISOADBKbd               = 9
};

#endif  /* ALLOW_OBSOLETE_CARBON_OSUTILS */




#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __OSUTILS__ */

