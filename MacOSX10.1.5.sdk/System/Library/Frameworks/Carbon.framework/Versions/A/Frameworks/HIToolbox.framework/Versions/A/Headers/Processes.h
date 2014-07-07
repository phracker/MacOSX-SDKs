/*
     File:       HIToolbox/Processes.h
 
     Contains:   Process Manager Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1989-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PROCESSES__
#define __PROCESSES__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __TEXTCOMMON__
#include <CarbonCore/TextCommon.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif


#include <sys/types.h>



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

/* type for unique process identifier */
struct ProcessSerialNumber {
  unsigned long       highLongOfPSN;
  unsigned long       lowLongOfPSN;
};
typedef struct ProcessSerialNumber      ProcessSerialNumber;
typedef ProcessSerialNumber *           ProcessSerialNumberPtr;
enum {
                                        /* Process identifier - Various reserved process serial numbers */
  kNoProcess                    = 0,
  kSystemProcess                = 1,
  kCurrentProcess               = 2
};

/* Definition of the parameter block passed to _Launch */
/* Typedef and flags for launchControlFlags field*/
typedef unsigned short                  LaunchFlags;
enum {
  launchContinue                = 0x4000,
  launchNoFileFlags             = 0x0800,
  launchUseMinimum              = 0x0400,
  launchDontSwitch              = 0x0200,
  launchAllow24Bit              = 0x0100,
  launchInhibitDaemon           = 0x0080
};

/* Format for first AppleEvent to pass to new process.  The size of the overall
  buffer variable: the message body immediately follows the messageLength */
struct AppParameters {
  EventRecord         theMsgEvent;
  unsigned long       eventRefCon;
  unsigned long       messageLength;
};
typedef struct AppParameters            AppParameters;
typedef AppParameters *                 AppParametersPtr;
/* Parameter block to _Launch */
struct LaunchParamBlockRec {
  unsigned long       reserved1;
  unsigned short      reserved2;
  unsigned short      launchBlockID;
  unsigned long       launchEPBLength;
  unsigned short      launchFileFlags;
  LaunchFlags         launchControlFlags;
  FSSpecPtr           launchAppSpec;
  ProcessSerialNumber  launchProcessSN;
  unsigned long       launchPreferredSize;
  unsigned long       launchMinimumSize;
  unsigned long       launchAvailableSize;
  AppParametersPtr    launchAppParameters;
};
typedef struct LaunchParamBlockRec      LaunchParamBlockRec;
typedef LaunchParamBlockRec *           LaunchPBPtr;
/* Set launchBlockID to extendedBlock to specify that extensions exist.
 Set launchEPBLength to extendedBlockLen for compatibility.*/
enum {
  extendedBlock                 = 0x4C43, /* 'LC' */
  extendedBlockLen              = sizeof(LaunchParamBlockRec) - 12
};

enum {
                                        /* Definition of the information block returned by GetProcessInformation */
  modeReserved                  = 0x01000000,
  modeControlPanel              = 0x00080000,
  modeLaunchDontSwitch          = 0x00040000,
  modeDeskAccessory             = 0x00020000,
  modeMultiLaunch               = 0x00010000,
  modeNeedSuspendResume         = 0x00004000,
  modeCanBackground             = 0x00001000,
  modeDoesActivateOnFGSwitch    = 0x00000800,
  modeOnlyBackground            = 0x00000400,
  modeGetFrontClicks            = 0x00000200,
  modeGetAppDiedMsg             = 0x00000100,
  mode32BitCompatible           = 0x00000080,
  modeHighLevelEventAware       = 0x00000040,
  modeLocalAndRemoteHLEvents    = 0x00000020,
  modeStationeryAware           = 0x00000010,
  modeUseTextEditServices       = 0x00000008,
  modeDisplayManagerAware       = 0x00000004
};

/*
   Record returned by GetProcessInformation
    When calling GetProcessInformation(), the input ProcesInfoRec
    should have the processInfoLength set to sizeof(ProcessInfoRec),
    the processName field set to nil or a pointer to a Str255, and
    processAppSpec set to nil or a pointer to an FSSpec.  If
    processName or processAppSpec are not specified, this routine
    will very likely write data to whatever random location in memory
    these happen to point to, which is not a good thing.
*/
struct ProcessInfoRec {
  unsigned long       processInfoLength;
  StringPtr           processName;
  ProcessSerialNumber  processNumber;
  unsigned long       processType;
  OSType              processSignature;
  unsigned long       processMode;
  Ptr                 processLocation;
  unsigned long       processSize;
  unsigned long       processFreeMem;
  ProcessSerialNumber  processLauncher;
  unsigned long       processLaunchDate;
  unsigned long       processActiveTime;
  FSSpecPtr           processAppSpec;
};
typedef struct ProcessInfoRec           ProcessInfoRec;
typedef ProcessInfoRec *                ProcessInfoRecPtr;
/*
    Some applications assumed the size of a ProcessInfoRec would never change,
    which has caused problems trying to return additional information.  In
    the future, we will add fields to ProcessInfoExtendedRec when necessary,
    and callers which wish to access 'more' data than originally was present
    in ProcessInfoRec should allocate space for a ProcessInfoExtendedRec,
    fill in the processInfoLength ( and processName and processAppSpec ptrs ),
    then coerce this to a ProcessInfoRecPtr in the call to
    GetProcessInformation().
*/
struct ProcessInfoExtendedRec {
  unsigned long       processInfoLength;
  StringPtr           processName;
  ProcessSerialNumber  processNumber;
  unsigned long       processType;
  OSType              processSignature;
  unsigned long       processMode;
  Ptr                 processLocation;
  unsigned long       processSize;
  unsigned long       processFreeMem;
  ProcessSerialNumber  processLauncher;
  unsigned long       processLaunchDate;
  unsigned long       processActiveTime;
  FSSpecPtr           processAppSpec;
  unsigned long       processTempMemTotal;
  unsigned long       processPurgeableTempMemTotal;
};
typedef struct ProcessInfoExtendedRec   ProcessInfoExtendedRec;
typedef ProcessInfoExtendedRec *        ProcessInfoExtendedRecPtr;
/* Record corresponding to the SIZE resource definition */
struct SizeResourceRec {
  unsigned short      flags;
  unsigned long       preferredHeapSize;
  unsigned long       minimumHeapSize;
};
typedef struct SizeResourceRec          SizeResourceRec;
typedef SizeResourceRec *               SizeResourceRecPtr;
typedef SizeResourceRecPtr *            SizeResourceRecHandle;
/*
    Applications and background applications can control when they are asked to quit
    by the system at restart/shutdown by setting these bits in a 'quit' ( 0 ) resource
    in their application's resource fork.  Applications without a 'quit' ( 0 ) will
    be quit at kQuitAtNormalTime mask.
*/
enum {
  kQuitBeforeNormalTimeMask     = 1,
  kQuitAtNormalTimeMask         = 2,
  kQuitBeforeFBAsQuitMask       = 4,
  kQuitBeforeShellQuitsMask     = 8,
  kQuitBeforeTerminatorAppQuitsMask = 16,
  kQuitNeverMask                = 32,
  kQuitOptionsMask              = 0x7F,
  kQuitNotQuitDuringInstallMask = 0x0100,
  kQuitNotQuitDuringLogoutMask  = 0x0200
};


/*
 *  LaunchApplication()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
LaunchApplication(LaunchPBPtr LaunchParams);


/*
 *  LaunchDeskAccessory()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  [Mac]GetCurrentProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacGetCurrentProcess GetCurrentProcess
#endif
extern OSErr 
MacGetCurrentProcess(ProcessSerialNumber * PSN);


/*
 *  GetFrontProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetFrontProcess(ProcessSerialNumber * PSN);


/*
 *  GetNextProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetNextProcess(ProcessSerialNumber * PSN);


/*
 *  GetProcessInformation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetProcessInformation(
  const ProcessSerialNumber *  PSN,
  ProcessInfoRec *             info);


/*
 *  SetFrontProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetFrontProcess(const ProcessSerialNumber * PSN);


/*
 *  WakeUpProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
WakeUpProcess(const ProcessSerialNumber * PSN);


/*
 *  SameProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SameProcess(
  const ProcessSerialNumber *  PSN1,
  const ProcessSerialNumber *  PSN2,
  Boolean *                    result);


/*  ExitToShell was previously in SegLoad.h*/
/*
 *  ExitToShell()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ExitToShell(void);


/*
   LaunchControlPanel is similar to LaunchDeskAccessory, but for Control Panel files instead.
   It launches a control panel in an application shell maintained by the Process Manager.
*/
/*
 *  LaunchControlPanel()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */


/*
 *  GetApplicationTextEncoding()
 *  
 *  Summary:
 *    Returns the application text encoding for Resource Manager
 *    resources.
 *  
 *  Discussion:
 *    The application text encoding is used when you create a
 *    CFStringRef from text stored in Resource Manager resources, which
 *    typically uses one of the Mac encodings such as MacRoman or
 *    MacJapanese.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.2 and later
 *    Non-Carbon CFM:   not available
 */
extern TextEncoding 
GetApplicationTextEncoding(void);


/*
 *  GetApplicationScript()
 *  
 *  Summary:
 *    Returns the application script.
 *  
 *  Discussion:
 *    The application script is used when you need a ScriptCode to pass
 *    to some other API, such as UseThemeFont.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern ScriptCode 
GetApplicationScript(void);


/*
 *  GetProcessBundleLocation()
 *  
 *  Summary:
 *    Retrieve the filesystem location of the process bundle, or
 *    executable if unbundled.
 *  
 *  Discussion:
 *    Retrieves a reference to the filesystem location of the specified
 *    application.  For an application that is packaged as an app
 *    bundle, this will be the app bundle directory; otherwise it will
 *    be the location of the executable itself.
 *  
 *  Parameters:
 *    
 *    psn:
 *      Serial number of the target process
 *    
 *    location:
 *      Location of the bundle or executable, as an FSRef
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetProcessBundleLocation(
  const ProcessSerialNumber *  psn,
  FSRef *                      location);


/*
 *  CopyProcessName()
 *  
 *  Summary:
 *    Get a copy of the name of a process.
 *  
 *  Discussion:
 *    Use this call to get the name of a process as a CFString.  The
 *    name returned is a copy, so the caller must CFRelease the name
 *    when finished with it.  The difference between this call and the
 *    processName field filled in by GetProcessInformation is that the
 *    name here is a CFString, and thus is capable of representing a
 *    multi-lingual name, whereas previously only a mac-encoded string
 *    was possible.
 *  
 *  Parameters:
 *    
 *    psn:
 *      Serial number of the target process
 *    
 *    name:
 *      CFString representing the name of the process (must be released
 *      by caller with CFRelease)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyProcessName(
  const ProcessSerialNumber *  psn,
  CFStringRef *                name);


/*
 *  GetProcessPID()
 *  
 *  Summary:
 *    Get the UNIX process ID corresponding to a process.
 *  
 *  Discussion:
 *    Given a Process serial number, this call will get the UNIX
 *    process ID for that process.  Note that this call does not make
 *    sense for Classic apps, since they all share a single UNIX
 *    process ID.
 *  
 *  Parameters:
 *    
 *    psn:
 *      Serial number of the target process
 *    
 *    pid:
 *      UNIX process ID of the process
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetProcessPID(
  const ProcessSerialNumber *  psn,
  pid_t *                      pid);


/*
 *  GetProcessForPID()
 *  
 *  Summary:
 *    Get the process serial number corresponding to a UNIX process ID.
 *  
 *  Discussion:
 *    Given a UNIX process ID, this call will get the process serial
 *    number for that process, if appropriate.  Note that this call
 *    does not make sense for Classic apps, since they all share a
 *    single UNIX process ID.
 *  
 *  Parameters:
 *    
 *    psn:
 *      Serial number of the process
 *    
 *    pid:
 *      UNIX process ID of the target process
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetProcessForPID(
  pid_t                  pid,
  ProcessSerialNumber *  psn);


/*************************************************************************
 *  Process Visibility.
 *************************************************************************/
/*
 *  IsProcessVisible()
 *  
 *  Summary:
 *    Determines whether a particular process is visible or not.
 *  
 *  Discussion:
 *    Given a psn, this call will return true or false depending on
 *    whether or not the process is currently visible.
 *  
 *  Parameters:
 *    
 *    psn:
 *      Serial number of the process
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsProcessVisible(ProcessSerialNumber * psn);


/*
 *  ShowHideProcess()
 *  
 *  Summary:
 *    Hides or shows a given process.
 *  
 *  Discussion:
 *    Given a psn, this call will hide or show the process specified in
 *    the psn parameter. You determine whether you would like to show
 *    or hide the process with the visible parameter. True passed into
 *    visible indicates you wish for the process to become visible.
 *  
 *  Parameters:
 *    
 *    psn:
 *      Serial number of the process
 *    
 *    visible:
 *      true = show process; false = hide process
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ShowHideProcess(
  ProcessSerialNumber *  psn,
  Boolean                visible);



/* Values of the 'message' parameter to a Control Panel 'cdev' */
enum {
  initDev                       = 0,    /*Time for cdev to initialize itself*/
  hitDev                        = 1,    /*Hit on one of my items*/
  closeDev                      = 2,    /*Close yourself*/
  nulDev                        = 3,    /*Null event*/
  updateDev                     = 4,    /*Update event*/
  activDev                      = 5,    /*Activate event*/
  deactivDev                    = 6,    /*Deactivate event*/
  keyEvtDev                     = 7,    /*Key down/auto key*/
  macDev                        = 8,    /*Decide whether or not to show up*/
  undoDev                       = 9,
  cutDev                        = 10,
  copyDev                       = 11,
  pasteDev                      = 12,
  clearDev                      = 13,
  cursorDev                     = 14
};

/* Special values a Control Panel 'cdev' can return */
enum {
  cdevGenErr                    = -1,   /*General error; gray cdev w/o alert*/
  cdevMemErr                    = 0,    /*Memory shortfall; alert user please*/
  cdevResErr                    = 1,    /*Couldn't get a needed resource; alert*/
  cdevUnset                     = 3     /* cdevValue is initialized to this*/
};

/* Control Panel Default Proc */
typedef CALLBACK_API( long , ControlPanelDefProcPtr )(short message, short item, short numItems, short cPanelID, EventRecord *theEvent, long cdevValue, DialogPtr cpDialog);
typedef STACK_UPP_TYPE(ControlPanelDefProcPtr)                  ControlPanelDefUPP;
/*
 *  NewControlPanelDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeControlPanelDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeControlPanelDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
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

#endif /* __PROCESSES__ */

