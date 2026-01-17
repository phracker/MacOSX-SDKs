/*
     File:       LaunchServices/LSOpen.h
 
     Contains:   Public interfaces for LaunchServices.framework
 
     Version:    LaunchServices-182~2
 
     Copyright:  © 2001-2006 by Apple Computer, Inc., all rights reserved.
 
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
  kLSLaunchDefaults             = 0x00000001, /* Defaults = open, async, use Info.plist, start Classic*/
  kLSLaunchAndPrint             = 0x00000002, /* Print items instead of open them*/
  kLSLaunchReserved2            = 0x00000004,
  kLSLaunchReserved3            = 0x00000008,
  kLSLaunchReserved4            = 0x00000010,
  kLSLaunchReserved5            = 0x00000020,
  kLSLaunchAndDisplayErrors     = 0x00000040, /* Report launch/open failures in the UI*/
  kLSLaunchInhibitBGOnly        = 0x00000080, /* Causes launch to fail if target is background-only.*/
  kLSLaunchDontAddToRecents     = 0x00000100, /* Do not add app or documents to recents menus.*/
  kLSLaunchDontSwitch           = 0x00000200, /* Don't bring new app to the foreground.*/
  kLSLaunchNoParams             = 0x00000800, /* Use Info.plist to determine launch parameters*/
  kLSLaunchAsync                = 0x00010000, /* Asynchronous launch; return as soon as the app starts launching.*/
  kLSLaunchStartClassic         = 0x00020000, /* Start up Classic environment if required for app.*/
  kLSLaunchInClassic            = 0x00040000, /* Force app to launch in Classic environment.*/
  kLSLaunchNewInstance          = 0x00080000, /* Instantiate app even if it is already running.*/
  kLSLaunchAndHide              = 0x00100000, /* Send child a "hide" request as soon as it checks in.*/
  kLSLaunchAndHideOthers        = 0x00200000, /* Hide all other apps when the app checks in.*/
  kLSLaunchHasUntrustedContents = 0x00400000 /* Mark items to be opened as untrusted*/
};

struct LSLaunchFSRefSpec {
  const FSRef *       appRef;                 /* app to use, can be NULL*/
  UInt32              numDocs;                /* items to open/print, can be zero*/
  const FSRef *       itemRefs;               /* array of FSRefs, ignored when numDocs is zero*/
  const AEDesc *      passThruParams;         /* passed untouched to application as optional event parameter, */
                                              /* with keyword keyAEPropData (can be NULL)*/
  LSLaunchFlags       launchFlags;
  void *              asyncRefCon;            /* used if you register for app birth/death notification*/
};
typedef struct LSLaunchFSRefSpec        LSLaunchFSRefSpec;
struct LSLaunchURLSpec {
  CFURLRef            appURL;                 /* app to use, can be NULL*/
  CFArrayRef          itemURLs;               /* items to open/print, can be NULL*/
  const AEDesc *      passThruParams;         /* passed untouched to application as optional parameter (can be NULL)*/
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



/* ================================================================================== */
/*   API for opening with a specific role and additional parameters                   */
/* ================================================================================== */

/*
 * LSApplicationParameters
 *
 *    This structure is used by the new LSOpen functions to specify
 *    an application, launch flags, and additional parameters
 *    controlling how an application is launched.
 *
 *    A version field allows the structure to be extended in 
 *    future releases. 
 */
struct LSApplicationParameters {
  CFIndex             version;                /* This must be set to zero by the client */
  LSLaunchFlags       flags;                  /* See the LSLaunchFlags enum */
  const FSRef *       application;            /* The application to open (and possibly handle documents/URLs) */
  void *              asyncLaunchRefCon;      /* The client refCon which will appear in subsequent launch notifications */
  CFDictionaryRef     environment;            /* Environment variables to set in the launched process */
                                              /* (a dictionary of CFStringRef keys and values). Can be NULL. */
  CFArrayRef          argv;                   /* Arguments to pass to main() in the launched process */
                                              /* (an array of CFStringRef values). Can be NULL */
  AppleEvent *        initialEvent;           /* The first Apple Event to be sent to the launched process. Can be NULL. */
};
typedef struct LSApplicationParameters  LSApplicationParameters;
/*
 *  LSOpenApplication()
 *  
 *    LSOpenApplication launches one application. This function
 *    is an updated alternative to the Process Manager's LaunchApplication().
 *
 *    Launch arguments are specified in the inAppParams argument, which
 *    must be supplied. If the application is already running in the current
 *    session, it will be made the front process (unless the kLSLaunchNewInstance
 *    flag is used, which will always cause a new process to be created).
 *
 *    If outPSN is not NULL, the structure it points to will contain the process 
 *    serial number of the launched (or activated) process. Note that for 
 *    asynchronous launches, the application may not have finished launching
 *    when this function returns.
 */
/*
 *  LSOpenApplication()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenApplication(
  const LSApplicationParameters *  appParams,
  ProcessSerialNumber *            outPSN)          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  LSOpenItemsWithRole()
 *  
 *    Opens the items specified as an array of FSRefs with the role
 *    specified by inRoleMask. If the role doesn't matter, use kLSRolesAll.
 *
 *    Clients can optionally specify the application and launch parameters 
 *    in inAppParams. If a specific application is given in inAppParams, then 
 *    inRoleMask is ignored and the application is launched (if necessary). 
 *    Otherwise, an application will be selected which can handle each input 
 *    item in the specified role(s).
 *
 *    Each launched application will receive an 'odoc' Apple Event specifying
 *    which items are to be opened.
 *
 *    Note that if the input items array contains any applications, this 
 *    function will not launch them unless the kLSRolesShell bit is set
 *    in the inRolesMask (in which case the application is its own shell).
 *
 *    The optional inAEParam argument specifies an AEDesc to be attached to
 *    the Apple Event(s) generated by Launch Services with the specified
 *    AEKeyword.
 *
 *    If not NULL, the outPSNs buffer will be filled with the PSN which
 *    was used to open each item at the same index of the input FSRef array. The
 *    PSN capacity of the output buffer is specified by inMaxPSNCount.
 */
/*
 *  LSOpenItemsWithRole()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenItemsWithRole(
  const FSRef *                    inItems,
  CFIndex                          inItemCount,
  LSRolesMask                      inRole,
  const AEKeyDesc *                inAEParam,           /* can be NULL */
  const LSApplicationParameters *  inAppParams,         /* can be NULL */
  ProcessSerialNumber *            outPSNs,             /* can be NULL */
  CFIndex                          inMaxPSNCount)             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  LSOpenURLsWithRole()
 *  
 *    Opens the URLs specified by inURLs (an array of CFURLRefs) with the role
 *    specified by inRoleMask. If the role doesn't matter, use kLSRolesAll.
 *
 *    Clients can optionally specify the application and launch parameters 
 *    in inAppParams. If a specific application is given in inAppParams, then 
 *    inRoleMask is ignored and the application is launched (if necessary). 
 *    Otherwise, an application will be selected which can handle each input 
 *    URL in at least one of the specified role(s).
 *
 *    Each launched application will receive one or more 'GURL' Apple Event 
 *    specifying the URLs to be opened. Clients may also pass file URLs, which
 *    will be interpreted as file system items and opened in the manner of 
 *    LSOpenItemsWithRole (i.e., a handler will be selected base on the item's
 *    metadata).
 *
 *    Note that if the input array contains any application URLs, this 
 *    function will not launch them unless the kLSRolesShell bit is set 
 *    in the inRolesMask (in which case the application is its own shell).
 *
 *    The optional inAEParam argument specifies an AEDesc to be attached to
 *    the Apple Event(s) generated by Launch Services with the specified
 *    AEKeyword.
 *
 *    If not NULL, the outPSNs buffer will be filled with the PSN which
 *    was used to open each URL at the same index of the input URL array. The
 *    PSN capacity of the output buffer is specified by inMaxPSNCount.
 */
/*
 *  LSOpenURLsWithRole()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenURLsWithRole(
  CFArrayRef                       inURLs,
  LSRolesMask                      inRole,
  const AEKeyDesc *                inAEParam,           /* can be NULL */
  const LSApplicationParameters *  inAppParams,         /* can be NULL */
  ProcessSerialNumber *            outPSNs,             /* can be NULL */
  CFIndex                          inMaxPSNCount)             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;





#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __LSOPEN__ */

