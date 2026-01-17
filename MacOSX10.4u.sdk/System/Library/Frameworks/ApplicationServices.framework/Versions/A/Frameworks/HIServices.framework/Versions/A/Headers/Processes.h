/*
     File:       HIServices/Processes.h
 
     Contains:   Process Manager Interfaces.
 
     Version:    HIServices-169~651
 
     Copyright:  © 1989-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PROCESSES__
#define __PROCESSES__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#include <sys/types.h>

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

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

/* Format for first AppleEvent to pass to new process. The size of the overall
  buffer variable: the message body immediately follows the messageLength */
struct AppParameters {
  struct {
    UInt16              what;
    UInt32              message;
    UInt32              when;
    Point               where;
    UInt16              modifiers;
  }                       theMsgEvent;
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

typedef UInt32 ProcessApplicationTransformState;
enum {
  kProcessTransformToForegroundApplication = 1L
};

/*
   Record returned by GetProcessInformation
    When calling GetProcessInformation(), the input ProcessInfoRec
    should have the processInfoLength set to sizeof(ProcessInfoRec),
    the processName field set to nil or a pointer to a Str255, and
    processAppSpec set to nil or a pointer to an FSSpec. If
    processName or processAppSpec are not specified, this routine
    will very likely write data to whatever random location in memory
    these happen to point to, which is not a good thing.
    Note:  The processName field may not be what you expect, especially if
    an application has a localized name. The .processName field, if not NULL,
    on return will contain the filename part of the executable file of the
    application. If you want the localized, user-displayable name for an 
    application, call CopyProcessName().
    On Mac OS X, some flags in processMode will not be set as they were on
    Mac OS 9, even for Classic applications.  Mac OS X doesn't support
    applications which can't be sent into the background, so 
    modeCanBackground will always be set.  Similarly, Mac OS X applications
    will always have mode32BitCompatible and modeHighLevelEventAware
    set.
    
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
    which has caused problems trying to return additional information. In
    the future, we will add fields to ProcessInfoExtendedRec when necessary,
    and callers which wish to access 'more' data than originally was present
    in ProcessInfoRec should allocate space for a ProcessInfoExtendedRec,
    fill in the processInfoLength ( and processName and processAppSpec ptrs ),
    then coerce this to a ProcessInfoRecPtr in the call to
    GetProcessInformation().
    Note:  The processName field may not be what you expect, especially if
    an application has a localized name. The .processName field, if not NULL,
    on return will contain the filename part of the executable file of the
    application. If you want the localized, user-displayable name for an 
    application, call CopyProcessName().
    On Mac OS X, some flags in processMode will not be set as they were on
    Mac OS 9, even for Classic applications.  Mac OS X doesn't support
    applications which can't be sent into the background, so 
    modeCanBackground will always be set.  Similarly, Mac OS X applications
    will always have mode32BitCompatible and modeHighLevelEventAware
    set.
    
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
 *  Summary:
 *    Options for ProcessInformationCopyDictionary
 */
enum {

  /*
   * Return all information known about the application in the
   * dictionary.
   */
  kProcessDictionaryIncludeAllInformationMask = (long)0xFFFFFFFF
};

/*
    Applications and background applications can control when they are asked to quit
    by the system at restart/shutdown by setting these bits in a 'quit' ( 0 ) resource
    in their application's resource fork. Applications without a 'quit' ( 0 ) will
    be quit at kQuitAtNormalTime mask.
    These options only function on Mac OS 9.x at this time.
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
LaunchApplication(LaunchPBPtr LaunchParams)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
 *  Discussion:
 *    Return the canonical process serial number to the caller.
 *    
 *    All applications ( things which can appear in the Dock or which
 *    are not documents and are launched by the Finder or Dock ) on Mac
 *    OS 10 have a unique process serial number. This number is created
 *    when the application launches, and remains until the application
 *    quits. Other system services, like AppleEvents, use the
 *    ProcessSerialNumber to specify an application.
 *    
 *    During launch, every application 'checks in' with the Process
 *    Manager. Before this checkin, the application can not receive
 *    events or draw to the screen. Prior to Mac OS 10.2, this 'check
 *    in' happened before the applications's main() function was
 *    entered. In Mac OS 10.2 and later, this 'check in' does not
 *    happen until the first time the application calls a Process
 *    Manager function, or until it enters CFRunLoopRun() for the main
 *    runloop. This allows tools and other executables which do not
 *    need to receive events to link against more of the higher level
 *    toolbox frameworks, but may cause a problem if the application
 *    expects to be able to retrieve events or use CoreGraphics
 *    services before this checkin has occurred.
 *    
 *    An application can force the connection to the Process Manager to
 *    be set up by calling any Process Manager routine, but the
 *    recommended way to do this is to call GetCurrentProcess() to ask
 *    for the current application's PSN. This will initialize the
 *    connection to the Process Manager if it has not already been set
 *    up and 'check in' the application with the system.
 *    
 *    This function is named MacGetCurrentProcess() on non Macintosh
 *    platforms and GetCurrentProcess on the Macintosh. However, even
 *    Macintosh code can use the MacGetCurrentProcess() name since
 *    there is a macro which maps back to GetCurrentProcess().
 *    
 *    Lastly, it is usually not necessary to call GetCurrentProcess()
 *    to get the 'current' process psn merely to pass it to another
 *    Process Manager routine. Instead, just construct a
 *    ProcessSerialNumber with 0 in highLongOfPSN and kCurrentProcess
 *    in lowLongOfPSN and pass that. For example, to make the current
 *    process the frontmost process, use ( C code follows )
 *    
 *    ProcessSerialNumber psn = { 0, kCurrentProcess }; 
 *    
 *    OSErr err = SetFrontProcess( & psn );
 *    
 *    If you need to pass a ProcessSerialNumber to another application
 *    or use it in an AppleEvent, you do need to get the canonical PSN
 *    with this routine.
 *  
 *  Parameters:
 *    
 *    PSN:
 *      Pass in where the current application process serial number
 *      should be returned.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacGetCurrentProcess GetCurrentProcess
#endif
extern OSErr 
MacGetCurrentProcess(ProcessSerialNumber * PSN)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFrontProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetFrontProcess(ProcessSerialNumber * PSN)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetNextProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetNextProcess(ProcessSerialNumber * PSN)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetProcessInformation()
 *  
 *  Discussion:
 *    Fill in the provided record with information about the process
 *    with the provided process serial number.
 *    
 *    The caller must fill in the .processInfoLength field with the
 *    value sizeof ( ProcessInformationRecord ) before making this
 *    call. Also, the .processName field must point to either NULL or
 *    to a Str31 structure in the caller's memory space, and the
 *    .processAppSpec field must point to a FSSpec in the caller's
 *    memory space.
 *    
 *    If the caller does not care about the process name or the process
 *    application spec values, then setting those fields in the
 *    structure to NULL before this call means less work must be done
 *    to construct these values and so the call is more
 *    efficient.
 *    
 *    The processName field may not be what you expect, especially if
 *    an application has a localized name. The .processName field, if
 *    not NULL, on return will contain the filename part of the
 *    executable file of the application. If you want the localized,
 *    user-displayable name for an application, call
 *    CopyProcessName().
 *    
 *    On Mac OS X, the processSize and processFreeMem fields are
 *    returned with the value 0.
 *  
 *  Parameters:
 *    
 *    PSN:
 *      Pass in the process serial number of the process to return
 *      information for.
 *    
 *    info:
 *      Pass in a structure where the information will be returned.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetProcessInformation(
  const ProcessSerialNumber *  PSN,
  ProcessInfoRec *             info)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ProcessInformationCopyDictionary()
 *  
 *  Discussion:
 *    Return a CFDictionary containing information about the given
 *    process. This is intended to return a superset of the information
 *    returned by GetProcessInformation(), in more modern datatypes.
 *  
 *  Parameters:
 *    
 *    PSN:
 *      Pass in the process serial number of the process to return
 *      information for.
 *    
 *    infoToReturn:
 *      Pass in the value kProcessDictionaryIncludeAllInformationMask.
 *  
 *  Result:
 *    An immutable CFDictionaryRef containing these keys and their
 *    values. Keys marked with a '*' are optional. Over time more keys
 *    may be added.
 *    
 *    Key Name                    Type 
 *    --------                    ---- 
 *    "PSN"                       CFNumber, kCFNumberLongLongType 
 *     "Flavor"                    CFNumber, kCFNumberSInt32.  A hint
 *    as to the flavor of the application. Note that this should only
 *    be used as a hint, since a bundle of a different flavor might be
 *    loaded into an application's address space.  The assigned values
 *    at present are:  Mac OS Classic aplications have the value 0,
 *    Carbon applications have the value 2, Cocoa applications have the
 *    value 4. Other undocumented values may also be returned.
 *     "Attributes"                CFNumber, kCFNumberSInt32 
 *     "ParentPSN" *               CFNumber, kCFNumberLongLong 
 *     "FileType" *                CFString, file type 
 *     "FileCreator" *             CFString, file creator 
 *    "pid" *                     CFNumber, kCFNumberLongType 
 *     "LSBackgroundOnly"          CFBoolean 
 *    "LSUIElement"               CFBoolean 
 *    "IsHiddenAttr"              CFBoolean 
 *    "IsCheckedInAttr"           CFBoolean 
 *    "RequiresClassic"           CFBoolean 
 *    "RequiresCarbon"            CFBoolean 
 *    "LSUserQuitOnly"            CFBoolean 
 *    "LSUIPresentationMode"      CFNumber, kCFNumberShortType 
 *     "BundlePath" *              CFString 
 *    kIOBundleExecutableKey *    CFString 
 *    kIOBundleNameKey *          CFString 
 *    kIOBundleIdentifierKey *    CFString
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFDictionaryRef 
ProcessInformationCopyDictionary(
  const ProcessSerialNumber *  PSN,
  UInt32                       infoToReturn)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SetFrontProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetFrontProcess(const ProcessSerialNumber * PSN)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  Summary:
 *    Options for SetFrontProcessWithOptions
 */
enum {

  /*
   * Activate the process, but bring only the frontmost non-floating
   * window forward. If this option is not set, all process windows are
   * brought forward.
   */
  kSetFrontProcessFrontWindowOnly = (1 << 0)
};


/*
 *  SetFrontProcessWithOptions()
 *  
 *  Discussion:
 *    Brings a process to the front of the process list and activates
 *    it. This is much like the SetFrontProcess API, though we allow
 *    more control here. Passing 0 for the options is equivalent to
 *    calling SetFrontProcess. Alternatively, you can pass
 *    kSetFrontProcessFrontWindowOnly, which will activate a process
 *    without bringing all of the process's windows forward (just the
 *    front window of the process will come forward).
 *  
 *  Parameters:
 *    
 *    inProcess:
 *      The process to make frontmost.
 *    
 *    inOptions:
 *      Any options you wish to specify.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetFrontProcessWithOptions(
  const ProcessSerialNumber *  inProcess,
  OptionBits                   inOptions)                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  WakeUpProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
WakeUpProcess(const ProcessSerialNumber * PSN)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SameProcess()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SameProcess(
  const ProcessSerialNumber *  PSN1,
  const ProcessSerialNumber *  PSN2,
  Boolean *                    result)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*  ExitToShell was previously in SegLoad.h*/
/*
 *  ExitToShell()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ExitToShell(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KillProcess()
 *  
 *  Discussion:
 *    Kills the process with the given process serial number, without
 *    sending it a 'quit' AppleEvent or otherwise allowing it to save
 *    user data or clean up. This should be a last resort way to 'kill'
 *    an application, after all other attempts to make it stop have
 *    failed. It is not guaranteed that this will succeed and that the
 *    target application will be killed, even if this function returns
 *    noErr and seems to work.
 *  
 *  Parameters:
 *    
 *    inProcess:
 *      The process to kill.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
KillProcess(const ProcessSerialNumber * inProcess)            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


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
 *  GetProcessBundleLocation()
 *  
 *  Summary:
 *    Retrieve the filesystem location of the process bundle, or
 *    executable if unbundled.
 *  
 *  Discussion:
 *    Retrieves a reference to the filesystem location of the specified
 *    application. For an application that is packaged as an app
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetProcessBundleLocation(
  const ProcessSerialNumber *  psn,
  FSRef *                      location)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyProcessName()
 *  
 *  Summary:
 *    Get a copy of the name of a process.
 *  
 *  Discussion:
 *    Use this call to get the name of a process as a CFString. The
 *    name returned is a copy, so the caller must CFRelease the name
 *    when finished with it. The difference between this call and the
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyProcessName(
  const ProcessSerialNumber *  psn,
  CFStringRef *                name)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetProcessPID()
 *  
 *  Summary:
 *    Get the UNIX process ID corresponding to a process.
 *  
 *  Discussion:
 *    Given a Process serial number, this call will get the UNIX
 *    process ID for that process. Note that this call does not make
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetProcessPID(
  const ProcessSerialNumber *  psn,
  pid_t *                      pid)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetProcessForPID()
 *  
 *  Summary:
 *    Get the process serial number corresponding to a UNIX process ID.
 *  
 *  Discussion:
 *    Given a UNIX process ID, this call will get the process serial
 *    number for that process, if appropriate. Note that this call does
 *    not make sense for Classic apps, since they all share a single
 *    UNIX process ID.
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetProcessForPID(
  pid_t                  pid,
  ProcessSerialNumber *  psn)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsProcessVisible(const ProcessSerialNumber * psn)             AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


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
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ShowHideProcess(
  const ProcessSerialNumber *  psn,
  Boolean                      visible)                       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*
 *  TransformProcessType()
 *  
 *  Summary:
 *    Changes the 'type' of the process specified in the psn parameter.
 *     The type is specified in the transformState parameter.
 *  
 *  Discussion:
 *    Given a psn which is a background-only application, this call can
 *    cause that application to be transformed into a foreground
 *    application.  A background only application does not appear in
 *    the Dock or in the Force Quit dialog, and never has a menu bar or
 *    is frontmost, while a foreground application does appear in the
 *    Dock and Force Quit dialog and does have a menu bar.  This call
 *    does not cause the application to be brought to the front ( use
 *    SetFrontProcess for that ).
 *  
 *  Parameters:
 *    
 *    psn:
 *      Serial number of the process
 *    
 *    transformState:
 *      state to tranform the application to.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TransformProcessType(
  const ProcessSerialNumber *        psn,
  ProcessApplicationTransformState   transformState)          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




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



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __PROCESSES__ */

