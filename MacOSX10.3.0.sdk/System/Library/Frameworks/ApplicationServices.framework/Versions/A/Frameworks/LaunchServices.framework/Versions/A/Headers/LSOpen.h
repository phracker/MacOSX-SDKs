/*
     File:       LaunchServices/LSOpen.h
 
     Contains:   Public interfaces for LaunchServices.framework
 
     Version:    LaunchServices-98~1
 
     Copyright:  © 2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __LSOPEN__
#define __LSOPEN__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __LSINFO__
#include <LaunchServices/LSInfo.h>
#endif

#ifndef __AE__
#include <AE/AE.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/* ======================================================================================================== */
/* LaunchServices Type & Constants                                                                          */
/* ======================================================================================================== */

typedef OptionBits                      LSLaunchFlags;
enum {
  kLSLaunchDefaults             = 0x00000001, /* default = open, async, use Info.plist, start Classic*/
  kLSLaunchAndPrint             = 0x00000002, /* print items instead of open them*/
  kLSLaunchReserved2            = 0x00000004,
  kLSLaunchReserved3            = 0x00000008,
  kLSLaunchReserved4            = 0x00000010,
  kLSLaunchReserved5            = 0x00000020,
  kLSLaunchReserved6            = 0x00000040,
  kLSLaunchInhibitBGOnly        = 0x00000080, /* causes launch to fail if target is background-only.*/
  kLSLaunchDontAddToRecents     = 0x00000100, /* do not add app or documents to recents menus.*/
  kLSLaunchDontSwitch           = 0x00000200, /* don't bring new app to the foreground.*/
  kLSLaunchNoParams             = 0x00000800, /* Use Info.plist to determine launch parameters*/
  kLSLaunchAsync                = 0x00010000, /* launch async; obtain results from kCPSNotifyLaunch.*/
  kLSLaunchStartClassic         = 0x00020000, /* start up Classic environment if required for app.*/
  kLSLaunchInClassic            = 0x00040000, /* force app to launch in Classic environment.*/
  kLSLaunchNewInstance          = 0x00080000, /* Instantiate app even if it is already running.*/
  kLSLaunchAndHide              = 0x00100000, /* Send child a "hide" request as soon as it checks in.*/
  kLSLaunchAndHideOthers        = 0x00200000 /* Hide all other apps when child checks in.*/
};

struct LSLaunchFSRefSpec {
  const FSRef *       appRef;                 /* app to use, can be NULL*/
  UInt32              numDocs;                /* items to open/print, can be NULL*/
  const FSRef *       itemRefs;               /* array of FSRefs*/
  const AEDesc *      passThruParams;         /* passed untouched to application as optional parameter*/
  LSLaunchFlags       launchFlags;
  void *              asyncRefCon;            /* used if you register for app birth/death notification*/
};
typedef struct LSLaunchFSRefSpec        LSLaunchFSRefSpec;
struct LSLaunchURLSpec {
  CFURLRef            appURL;                 /* app to use, can be NULL*/
  CFArrayRef          itemURLs;               /* items to open/print, can be NULL*/
  const AEDesc *      passThruParams;         /* passed untouched to application as optional parameter*/
  LSLaunchFlags       launchFlags;
  void *              asyncRefCon;            /* used if you register for app birth/death notification*/
};
typedef struct LSLaunchURLSpec          LSLaunchURLSpec;


/* ======================================================================================================== */
/* LaunchServices API                                                                                       */
/* ======================================================================================================== */

/*
 *  LSOpenFSRef()
 *  
 *  Summary:
 *    Open an application, document, or folder.
 *  
 *  Discussion:
 *    Opens applications, documents, and folders. Applications are
 *    opened via an 'oapp' or 'rapp' event. Documents are opened in
 *    their user-overridden or default applications as appropriate.
 *    Folders are opened in the Finder. Use the more specific
 *    LSOpenFromRefSpec for more control over launching.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inRef:
 *      The FSRef of the item to launch.
 *    
 *    outLaunchedRef:
 *      The FSRef of the item actually launched. For inRefs that are
 *      documents, outLaunchedRef will be the application used to
 *      launch the document. Can be NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenFSRef(
  const FSRef *  inRef,
  FSRef *        outLaunchedRef)       /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LSOpenCFURLRef()
 *  
 *  Summary:
 *    Open an application, document, or folder.
 *  
 *  Discussion:
 *    Opens applications, documents, and folders. Applications are
 *    opened via an 'oapp' or 'rapp' event. Documents are opened in
 *    their user-overridden or default applications as appropriate.
 *    Folders are opened in the Finder. Use the more specific
 *    LSOpenFromURLSpec for more control over launching.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The CFURLRef of the item to launch.
 *    
 *    outLaunchedURL:
 *      The CFURLRef of the item actually launched. For inURLs that are
 *      documents, outLaunchedURL will be the application used to
 *      launch the document. Can be NULL. THIS FUNCTION, DESPITE ITS
 *      NAME, RETAINS THE URL REFERENCE ON BEHALF OF THE CALLER. THE
 *      CALLER MUST EVENTUALLY RELEASE THE RETURNED URL REFERENCE.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenCFURLRef(
  CFURLRef    inURL,
  CFURLRef *  outLaunchedURL)       /* can be NULL */         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LSOpenFromRefSpec()
 *  
 *  Summary:
 *    Opens an application or one or more documents or folders.
 *  
 *  Discussion:
 *    Opens applications, documents, and folders.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inLaunchSpec:
 *      The specification of what to launch and how to launch it.
 *    
 *    outLaunchedRef:
 *      The FSRef of the item actually launched. For inRefs that are
 *      documents, outLaunchedRef will be the application used to
 *      launch the document. Can be NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenFromRefSpec(
  const LSLaunchFSRefSpec *  inLaunchSpec,
  FSRef *                    outLaunchedRef)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LSOpenFromURLSpec()
 *  
 *  Summary:
 *    Opens an application or one or more documents or folders.
 *  
 *  Discussion:
 *    Opens applications, documents, and folders.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inLaunchSpec:
 *      The specification of what to launch and how to launch it.
 *    
 *    outLaunchedURL:
 *      The CFURLRef of the item actually launched. For inURLs that are
 *      documents, outLaunchedURL will be the application used to
 *      launch the document. Can be NULL. THIS FUNCTION, DESPITE ITS
 *      NAME, RETAINS THE URL REFERENCE ON BEHALF OF THE CALLER. THE
 *      CALLER MUST EVENTUALLY RELEASE THE RETURNED URL REFERENCE.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenFromURLSpec(
  const LSLaunchURLSpec *  inLaunchSpec,
  CFURLRef *               outLaunchedURL)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __LSOPEN__ */

