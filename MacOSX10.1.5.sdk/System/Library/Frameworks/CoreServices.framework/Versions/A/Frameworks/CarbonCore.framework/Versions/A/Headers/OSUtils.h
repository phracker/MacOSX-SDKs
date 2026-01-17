/*
     File:       CarbonCore/OSUtils.h
 
     Contains:   OS Utilities Interfaces.
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
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

/*  GetTrapAddress and other trap table utilties were moved to Patches.h */
#ifndef __PATCHES__
#include <CarbonCore/Patches.h>
#endif

/*  Date and Time utilties were moved to DateTimeUtils.h */
#ifndef __DATETIMEUTILS__
#include <CarbonCore/DateTimeUtils.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
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
NewDeferredTaskUPP(DeferredTaskProcPtr userRoutine);

/*
 *  DisposeDeferredTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDeferredTaskUPP(DeferredTaskUPP userUPP);

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
  DeferredTaskUPP  userUPP);

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
struct MachineLocation {
  Fract               latitude;
  Fract               longitude;
  union {
    SInt8               dlsDelta;             /* signed byte; daylight savings delta */
    long                gmtDelta;             /* use low 24-bits only */
  }                       u;
};
typedef struct MachineLocation          MachineLocation;
/*
 *  IsMetric()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
IsMetric(void);


/*
 *  GetSysPPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SysPPtr 
GetSysPPtr(void);



/*
    NOTE: SysBeep() has been moved to Sound.h.  
          We could not automatically #include Sound.h in this file
          because Sound.h indirectly #include's OSUtils.h which
          would make a circular include.
*/
/*
 *  DTInstall()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DTInstall(DeferredTaskPtr dtTaskPtr);




#if TARGET_CPU_PPC || !TARGET_OS_MAC
#define GetMMUMode() ((SInt8)true32b)
#define SwapMMUMode(x) (*(SInt8*)(x) = true32b)
#else
/*
 *  GetMMUMode()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  SwapMMUMode()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


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
  unsigned long *  finalTicks);


/*
 *  WriteParam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
WriteParam(void);


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
  QHdrPtr    qHeader);


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
  QHdrPtr    qHeader);



/*
 *  SetCurrentA5()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
SetCurrentA5(void);


/*
 *  SetA5()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
SetA5(long newA5);


/*
 *  InitUtil()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
InitUtil(void);



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
  unsigned long   length);



/*
 *  FlushCodeCacheRange()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  ReadLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ReadLocation(MachineLocation * loc);



/*
 *  WriteLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
WriteLocation(const MachineLocation * loc);



/*
 *  TickCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt32 
TickCount(void);



/*
 *  CSCopyUserName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
CSCopyUserName(Boolean useShortName);


/*
 *  CSCopyMachineName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
CSCopyMachineName(void);



#if OLDROUTINENAMES
#define IUMetric() IsMetric()
#endif  /* OLDROUTINENAMES */

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

/*
 *  SysEnvirons()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */






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

#endif /* __OSUTILS__ */

