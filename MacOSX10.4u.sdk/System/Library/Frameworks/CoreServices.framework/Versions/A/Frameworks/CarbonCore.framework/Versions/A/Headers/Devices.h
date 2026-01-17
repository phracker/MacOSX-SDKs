/*
     File:       CarbonCore/Devices.h
 
     Contains:   Device Manager Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1985-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DEVICES__
#define __DEVICES__

#ifndef __OSUTILS__
#include <CarbonCore/OSUtils.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __NAMEREGISTRY__
#include <CarbonCore/NameRegistry.h>
#endif

#ifndef __CODEFRAGMENTS__
#include <CarbonCore/CodeFragments.h>
#endif

#ifndef __MULTIPROCESSING__
#include <CarbonCore/Multiprocessing.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/* Values of the 'message' parameter to a Chooser device package */
enum {
  chooserInitMsg                = 11,   /* the user selected this device package */
  newSelMsg                     = 12,   /* the user made new device selections */
  fillListMsg                   = 13,   /* fill the device list with choices */
  getSelMsg                     = 14,   /* mark one or more choices as selected */
  selectMsg                     = 15,   /* the user made a selection */
  deselectMsg                   = 16,   /* the user canceled a selection */
  terminateMsg                  = 17,   /* allows device package to clean up */
  buttonMsg                     = 19    /* the user selected a button */
};


/* Values of the 'caller' parameter to a Chooser device package */
enum {
  chooserID                     = 1
};


/* Values of the 'message' parameter to a Monitor 'mntr' */
enum {
  initMsg                       = 1,    /*initialization*/
  okMsg                         = 2,    /*user clicked OK button*/
  cancelMsg                     = 3,    /*user clicked Cancel button*/
  hitMsg                        = 4,    /*user clicked control in Options dialog*/
  nulMsg                        = 5,    /*periodic event*/
  updateMsg                     = 6,    /*update event*/
  activateMsg                   = 7,    /*not used*/
  deactivateMsg                 = 8,    /*not used*/
  keyEvtMsg                     = 9,    /*keyboard event*/
  superMsg                      = 10,   /*show superuser controls*/
  normalMsg                     = 11,   /*show only normal controls*/
  startupMsg                    = 12    /*code has been loaded*/
};


/* control codes for DeskAccessories */
enum {
  goodbye                       = -1,   /* heap being reinitialized */
  killCode                      = 1,    /* KillIO requested */
  accEvent                      = 64,   /* handle an event */
  accRun                        = 65,   /* time for periodic action */
  accCursor                     = 66,   /* change cursor shape */
  accMenu                       = 67,   /* handle menu item */
  accUndo                       = 68,   /* handle undo command */
  accCut                        = 70,   /* handle cut command */
  accCopy                       = 71,   /* handle copy command */
  accPaste                      = 72,   /* handle paste command */
  accClear                      = 73    /* handle clear command */
};

/* Control/Status Call Codes */
/* drvStsCode, ejectCode and tgBuffCode are now defined in Disks.h/p/a */

/* miscellaneous Device Manager constants */
enum {
  ioInProgress                  = 1,    /* predefined value of ioResult while I/O is pending */
  aRdCmd                        = 2,    /* low byte of ioTrap for Read calls */
  aWrCmd                        = 3,    /* low byte of ioTrap for Write calls */
  asyncTrpBit                   = 10,   /* trap word modifier */
  noQueueBit                    = 9     /* trap word modifier */
};

/* flags used in the driver header and device control entry */
enum {
  dReadEnable                   = 0,    /* set if driver responds to read requests */
  dWritEnable                   = 1,    /* set if driver responds to write requests */
  dCtlEnable                    = 2,    /* set if driver responds to control requests */
  dStatEnable                   = 3,    /* set if driver responds to status requests */
  dNeedGoodBye                  = 4,    /* set if driver needs time for performing periodic tasks */
  dNeedTime                     = 5,    /* set if driver needs time for performing periodic tasks */
  dNeedLock                     = 6     /* set if driver must be locked in memory as soon as it is opened */
};

enum {
  dNeedLockMask                 = 0x4000, /* set if driver must be locked in memory as soon as it is opened */
  dNeedTimeMask                 = 0x2000, /* set if driver needs time for performing periodic tasks */
  dNeedGoodByeMask              = 0x1000, /* set if driver needs to be called before the application heap is initialized */
  dStatEnableMask               = 0x0800, /* set if driver responds to status requests */
  dCtlEnableMask                = 0x0400, /* set if driver responds to control requests */
  dWritEnableMask               = 0x0200, /* set if driver responds to write requests */
  dReadEnableMask               = 0x0100 /* set if driver responds to read requests */
};


/* run-time flags used in the device control entry */
enum {
  dVMImmuneBit                  = 0,    /* driver does not need VM protection */
  dOpened                       = 5,    /* driver is open */
  dRAMBased                     = 6,    /* dCtlDriver is a handle (1) or pointer (0) */
  drvrActive                    = 7     /* driver is currently processing a request */
};

enum {
  dVMImmuneMask                 = 0x0001, /* driver does not need VM protection */
  dOpenedMask                   = 0x0020, /* driver is open */
  dRAMBasedMask                 = 0x0040, /* dCtlDriver is a handle (1) or pointer (0) */
  drvrActiveMask                = 0x0080 /* driver is currently processing a request */
};

struct DRVRHeader {
  short               drvrFlags;
  short               drvrDelay;
  short               drvrEMask;
  short               drvrMenu;
  short               drvrOpen;
  short               drvrPrime;
  short               drvrCtl;
  short               drvrStatus;
  short               drvrClose;
  unsigned char       drvrName[1];
};
typedef struct DRVRHeader               DRVRHeader;
typedef DRVRHeader *                    DRVRHeaderPtr;
typedef DRVRHeaderPtr *                 DRVRHeaderHandle;
typedef struct OpaqueDCtlHandle*        DCtlHandle;
/*  The NDRV Driver IO Entry Point and Commands */
typedef UInt16                          UnitNumber;
typedef UInt32                          DriverOpenCount;
typedef SInt16                          DriverRefNum;
typedef SInt16                          DriverFlags;
typedef UInt32                          IOCommandCode;
enum {
  kOpenCommand                  = 0,
  kCloseCommand                 = 1,
  kReadCommand                  = 2,
  kWriteCommand                 = 3,
  kControlCommand               = 4,
  kStatusCommand                = 5,
  kKillIOCommand                = 6,
  kInitializeCommand            = 7,    /* init driver and device*/
  kFinalizeCommand              = 8,    /* shutdown driver and device*/
  kReplaceCommand               = 9,    /* replace an old driver*/
  kSupersededCommand            = 10,   /* prepare to be replaced by a new driver*/
  kSuspendCommand               = 11,   /* prepare driver to go to sleep*/
  kResumeCommand                = 12    /* wake up sleeping driver*/
};

enum {
                                        /* one more IOCommandCode*/
  kPowerManagementCommand       = 13    /* power management command, supercedes kSuspendCommand and kResumeCommand*/
};

typedef MPAddressSpaceID                AddressSpaceID;
typedef struct OpaqueIOCommandID*       IOCommandID;
/*
 *  HigherDriverVersion()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  VerifyFragmentAsDriver()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  GetDriverMemoryFragment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  GetDriverDiskFragment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  GetNamedDriverDiskFragment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  InstallDriverFromFragment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  InstallDriverFromFile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  InstallDriverFromMemory()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  InstallDriverFromResource()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  InstallDriverFromDisk()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  FindDriversForDevice()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  FindDriverForDeviceFromFile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  FindDriverCandidates()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  FindDriverCandidatesDetailed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  ScanDriverCandidates()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  ScanDriverCandidatesDetailed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  CompareFileCandToPropCand()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  GetCompatibleProperty()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  CompatibleDriverNames()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  GetDriverForDevice()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  InstallDriverForDevice()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  GetDriverInformation()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  GetDriverDescription()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  GetNamedDriverDescFromFSSpec()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 2.0 and later
 */


/*
 *  SetDriverClosureMemory()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  ReplaceDriverWithFragment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  OpenInstalledDriver()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  RenameDriver()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  RemoveDriver()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  LookupDrivers()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  HighestUnitNumber()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  DriverGestaltOn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  DriverGestaltOff()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  DriverGestaltIsOn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverLoaderLib 1.0 and later
 */


/*
 *  PBOpenSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOpenAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOpenImmed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBCloseSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PBCloseSync(ParmBlkPtr paramBlock)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PBCloseAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PBCloseAsync(ParmBlkPtr paramBlock)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PBCloseImmed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBReadSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PBReadSync(ParmBlkPtr paramBlock)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PBReadAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PBReadAsync(ParmBlkPtr paramBlock)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PBReadImmed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBWriteSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PBWriteSync(ParmBlkPtr paramBlock)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PBWriteAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PBWriteAsync(ParmBlkPtr paramBlock)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PBWriteImmed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
    PBWaitIOComplete is a friendly way for applications to monitor
    a pending asynchronous I/O operation in power-managed and
    preemptive multitasking systems.
 */
/*
 *  PBWaitIOComplete()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBWaitIOComplete(
  ParmBlkPtr   paramBlock,
  Duration     timeout)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* AddDrive and GetDrvQHdr are now defined in Disks.h/p/a */

/*
 *  GetDCtlEntry()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
    SetChooserAlert used to simply set a bit in a low-mem global
    to tell the Chooser not to display its warning message when
    the printer is changed. However, under MultiFinder and System 7,
    this low-mem is swapped out when a layer change occurs, and the
    Chooser never sees the change. It is obsolete, and completely
    unsupported on the PowerPC. 68K apps can still call it if they
    wish.
    
    pascal Boolean SetChooserAlert(Boolean f);

*/
/*
 *  DriverInstall()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DriverInstallReserveMem()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
  Note: DrvrInstall() is no longer supported, becuase it never really worked anyways.
        There will soon be a DriverInstall() which does the right thing.

        DrvrRemove has been renamed to DriverRemove.  But, InterfaceLib for PowerPC
        still exports DrvrRemove, so a macro is used to map the new name to old.

*/
/*
 *  DrvrRemove()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#define DriverRemove(refNum) DrvrRemove(refNum)

/*
    Shim mechnanism only exist in Maxwell world.  A Shim is a translation layer
    and looks like a DRVR. 
*/
typedef CALLBACK_API( OSStatus , ShimEntryPoint )(Ptr paramBlock, Ptr refcon);
/*
 *  DriverInstallShim()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  DriverRemoveShim()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  DriverReturnShimRefcon()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  IOShimCommandIsComplete()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  [Mac]OpenDriver()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  [Mac]CloseDriver()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Control()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Status()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  KillIO()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Fetch()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  Stash()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  IODone()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  PBControlSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBControlAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBControlImmed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBStatusSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBStatusAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBStatusImmed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBKillIOSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBKillIOAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBKillIOImmed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  OpenDeskAcc()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CloseDeskAcc()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  opendeskacc()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  opendriver()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
    The PBxxx() routines are obsolete.  
    
    Use the PBxxxSync(), PBxxxAsync(), or PBxxxImmed version instead.
*/
#define PBControl(pb, async) ((async) ? PBControlAsync(pb) : PBControlSync(pb))
#define PBStatus(pb, async) ((async) ? PBStatusAsync(pb) : PBStatusSync(pb))
#define PBKillIO(pb, async) ((async) ? PBKillIOAsync(pb) : PBKillIOSync(pb))

#define PBOpen(pb, async) ((async) ? PBOpenAsync(pb) : PBOpenSync(pb))
#define PBClose(pb, async) ((async) ? PBCloseAsync(pb) : PBCloseSync(pb))
#define PBRead(pb, async) ((async) ? PBReadAsync(pb) : PBReadSync(pb))
#define PBWrite(pb, async) ((async) ? PBWriteAsync(pb) : PBWriteSync(pb))






#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __DEVICES__ */

