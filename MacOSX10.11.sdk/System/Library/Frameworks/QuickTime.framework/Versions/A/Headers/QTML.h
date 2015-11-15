/*
     File:       QuickTime/QTML.h
 
     Contains:   QuickTime Cross-platform specific interfaces
 
     Version:    QuickTime 7.7.3
 
     Copyright:  © 1997-2015 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*
  QuickTime has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.
*/

#ifndef __QTML__
#define __QTML__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* QuickTime is not available to 64-bit clients */

#if !__LP64__

/*
 *  QTMLYieldCPU()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern void 
QTMLYieldCPU(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/* QTMLYieldCPUTime flags*/
enum {
  kQTMLHandlePortEvents         = (1L << 0) /* ask for event handling during the yield*/
};

/*
 *  QTMLYieldCPUTime()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern void 
QTMLYieldCPUTime(
  long            milliSeconds,
  unsigned long   flags)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


typedef struct OpaqueQTMLMutex*         QTMLMutex;
typedef struct OpaqueQTMLSyncVar*       QTMLSyncVar;
typedef QTMLSyncVar *                   QTMLSyncVarPtr;
/* InitializeQTML flags*/
enum {
  kInitializeQTMLNoSoundFlag    = (1L << 0), /* flag for requesting no sound when calling InitializeQTML*/
  kInitializeQTMLUseGDIFlag     = (1L << 1), /* flag for requesting GDI when calling InitializeQTML*/
  kInitializeQTMLDisableDirectSound = (1L << 2), /* disables QTML's use of DirectSound*/
  kInitializeQTMLUseExclusiveFullScreenModeFlag = (1L << 3), /* later than QTML 3.0: qtml starts up in exclusive full screen mode*/
  kInitializeQTMLDisableDDClippers = (1L << 4), /* flag for requesting QTML not to use DirectDraw clipper objects; QTML 5.0 and later*/
  kInitializeQTMLEnableDoubleBufferedSurface = (1L << 6) /* flag for requesting QuickTime use a double-buffered destination surface; QT6.4 and later*/
};

/*
 *  InitializeQTML()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  TerminateQTML()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */



/* CreatePortAssociation flags*/
enum {
  kQTMLNoIdleEvents             = (1L << 1), /* ask for a non-auto-idled port to be created*/
  kQTMLNoDoubleBufferPort       = (1L << 2) /* ask for QTML not to double-buffer this port*/
};

#define kQTMLIsDoubleBuffered "UsesDoubleBuffer"
/*
 *  CreatePortAssociation()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  DestroyPortAssociation()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */



/*
 *  QTMLGrabMutex()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern void 
QTMLGrabMutex(QTMLMutex mu)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTMLTryGrabMutex()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 4.1 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 4.1 and later
 */
extern Boolean 
QTMLTryGrabMutex(QTMLMutex mu)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTMLReturnMutex()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern void 
QTMLReturnMutex(QTMLMutex mu)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTMLCreateMutex()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern QTMLMutex 
QTMLCreateMutex(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTMLDestroyMutex()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern void 
QTMLDestroyMutex(QTMLMutex mu)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*
 *  QTMLCreateSyncVar()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTMLDestroySyncVar()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTMLTestAndSetSyncVar()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTMLWaitAndSetSyncVar()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTMLResetSyncVar()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */



/*
 *  InitializeQHdr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  TerminateQHdr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */



/*
 *  QTMLAcquireWindowList()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTMLReleaseWindowList()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
   These routines are here to support "interrupt level" code
      These are dangerous routines, only use if you know what you are doing.
*/

/*
 *  QTMLRegisterInterruptSafeThread()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTMLUnregisterInterruptSafeThread()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */



/*
 *  NativeEventToMacEvent()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


#if TARGET_OS_WIN32
/*
 *  WinEventToMacEvent()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


#define WinEventToMacEvent  NativeEventToMacEvent
/*
 *  IsTaskBarVisible()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  ShowHideTaskBar()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


enum {
  kDDSurfaceLocked              = (1L << 0),
  kDDSurfaceStatic              = (1L << 1)
};

/*
 *  QTGetDDObject()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTSetDDObject()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTSetDDPrimarySurface()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */



/*
 *  QTMLGetVolumeRootPath()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */



/*
 *  QTMLSetWindowWndProc()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTMLGetWindowWndProc()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


#endif  /* TARGET_OS_WIN32 */

/*
 *  QTMLGetCanonicalPathName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


enum {
  kFullNativePath               = 0,
  kFileNameOnly                 = (1 << 0),
  kDirectoryPathOnly            = (1 << 1),
  kUFSFullPathName              = (1 << 2),
  kTryVDIMask                   = (1 << 3), /*    Used in NativePathNameToFSSpec to specify to search VDI mountpoints*/
  kFullPathSpecifiedMask        = (1 << 4) /*    the passed in name is a fully qualified full path*/
};

/*
 *  FSSpecToNativePathName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


enum {
  kErrorIfFileNotFound          = 1L << 31
};

/*
 *  NativePathNameToFSSpec()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 3.0 and later
 */


/*
 *  QTGetAliasInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 5.0 and later
 */



#endif // !__LP64__


#ifdef __cplusplus
}
#endif

#endif /* __QTML__ */

