/*
     File:       QuickTime/QTML.h
 
     Contains:   QuickTime Cross-platform specific interfaces
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1997-2006 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
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
 *  QTMLYieldCPU()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
QTMLYieldCPU(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* QTMLYieldCPUTime flags*/
enum {
  kQTMLHandlePortEvents         = (1L << 0) /* ask for event handling during the yield*/
};

/*
 *  QTMLYieldCPUTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
QTMLYieldCPUTime(
  long            milliSeconds,
  unsigned long   flags)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
 *  InitializeQTML()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  TerminateQTML()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */



/* CreatePortAssociation flags*/
enum {
  kQTMLNoIdleEvents             = (1L << 1), /* ask for a non-auto-idled port to be created*/
  kQTMLNoDoubleBufferPort       = (1L << 2) /* ask for QTML not to double-buffer this port*/
};

#define kQTMLIsDoubleBuffered "UsesDoubleBuffer"
/*
 *  CreatePortAssociation()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  DestroyPortAssociation()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */



/*
 *  QTMLGrabMutex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
QTMLGrabMutex(QTMLMutex mu)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTMLTryGrabMutex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 4.1 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern Boolean 
QTMLTryGrabMutex(QTMLMutex mu)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTMLReturnMutex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
QTMLReturnMutex(QTMLMutex mu)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTMLCreateMutex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern QTMLMutex 
QTMLCreateMutex(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTMLDestroyMutex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 3.0 and later
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
QTMLDestroyMutex(QTMLMutex mu)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  QTMLCreateSyncVar()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTMLDestroySyncVar()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTMLTestAndSetSyncVar()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTMLWaitAndSetSyncVar()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTMLResetSyncVar()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */



/*
 *  InitializeQHdr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  TerminateQHdr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */



/*
 *  QTMLAcquireWindowList()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTMLReleaseWindowList()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
   These routines are here to support "interrupt level" code
      These are dangerous routines, only use if you know what you are doing.
*/

/*
 *  QTMLRegisterInterruptSafeThread()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTMLUnregisterInterruptSafeThread()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */



/*
 *  NativeEventToMacEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


#if TARGET_OS_WIN32
/*
 *  WinEventToMacEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


#define WinEventToMacEvent  NativeEventToMacEvent
/*
 *  IsTaskBarVisible()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  ShowHideTaskBar()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


enum {
  kDDSurfaceLocked              = (1L << 0),
  kDDSurfaceStatic              = (1L << 1)
};

/*
 *  QTGetDDObject()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTSetDDObject()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTSetDDPrimarySurface()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */



/*
 *  QTMLGetVolumeRootPath()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */



/*
 *  QTMLSetWindowWndProc()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTMLGetWindowWndProc()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


#endif  /* TARGET_OS_WIN32 */

/*
 *  QTMLGetCanonicalPathName()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
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
 *  FSSpecToNativePathName()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


enum {
  kErrorIfFileNotFound          = 1L << 31
};

/*
 *  NativePathNameToFSSpec()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  QTGetAliasInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 5.0 and later
 */



#endif // !__LP64__


#ifdef __cplusplus
}
#endif

#endif /* __QTML__ */

