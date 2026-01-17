/*
     File:       LSOpenDeprecated.h
 
     Contains:   Deprecated interfaces for LaunchServices.framework
 
     Copyright:  (c) 2003-2015 by Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/

*/

#ifndef __LSOPENDEPRECATED__
#define __LSOPENDEPRECATED__

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)



enum {
  kLSLaunchStartClassic         __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_11, __IPHONE_NA, __IPHONE_NA, "The Classic environment is no longer supported.") = 0x00020000, /* Does nothing.*/
  kLSLaunchInClassic            __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_11, __IPHONE_NA, __IPHONE_NA, "The Classic environment is no longer supported.") = 0x00040000, /* Always fails with kLSNoClassicEnvironmentErr.*/
};



#if !TARGET_OS_IPHONE
typedef struct LSLaunchFSRefSpec {
  const FSRef *       appRef;                 /* app to use, can be NULL*/
  ItemCount           numDocs;                /* items to open/print, can be zero*/
  const FSRef *       itemRefs;               /* array of FSRefs, ignored when numDocs is zero*/
  const AEDesc *      passThruParams;         /* passed untouched to application as optional event parameter, */
                                              /* with keyword keyAEPropData (can be NULL)*/
  LSLaunchFlags       launchFlags;
  void *              asyncRefCon;            /* used if you register for app birth/death notification*/
} LSLaunchFSRefSpec __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSLaunchURLSpec instead.");



/*
 *  LSOpenFSRef()   *** DEPRECATED ***
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
 *  Deprecated:
 *    Use LSOpenCFURLRef or -[NSWorkspace openURL:] instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenFSRef(
  const FSRef *  inRef,
  FSRef *        outLaunchedRef)       /* can be NULL */      __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSOpenCFURLRef or -[NSWorkspace openURL:] instead.");

	

/*
 *  LSOpenFromRefSpec()   *** DEPRECATED ***
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
 *  Deprecated:
 *    Use LSOpenFromURLSpec or NSWorkspace instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenFromRefSpec(
  const LSLaunchFSRefSpec *  inLaunchSpec,
  FSRef *                    outLaunchedRef)       /* can be NULL */ __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSOpenFromURLSpec or NSWorkspace instead.");



/*
 * LSApplicationParameters   *** DEPRECATED ***
 *
 *    This structure is used by the new LSOpen functions to specify
 *    an application, launch flags, and additional parameters
 *    controlling how an application is launched.
 *
 *    A version field allows the structure to be extended in 
 *    future releases. 
 *
 *  Deprecated:
 *    Use NSWorkspace instead.
 *
 */
typedef struct LSApplicationParameters {
  CFIndex             version;                /* This must be set to zero by the client */
  LSLaunchFlags       flags;                  /* See the LSLaunchFlags enum */
  const FSRef *       application;            /* The application to open (and possibly handle documents/URLs) */
  void *              asyncLaunchRefCon;      /* The client refCon which will appear in subsequent launch notifications */
  CFDictionaryRef     environment;            /* Environment variables to set in the launched process */
                                              /* (a dictionary of CFStringRef keys and values). Can be NULL. */
  CFArrayRef          argv;                   /* Note: argv is ignored on 10.4. On 10.5 and later, the array elements */
                                              /* (which must be CFStringRefs) are passed as arguments to main() in the launched process. */
  AppleEvent *        initialEvent;           /* The first Apple Event to be sent to the launched process. Can be NULL. */
} LSApplicationParameters __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use NSWorkspace instead.");



/*
 *  LSOpenApplication()   *** DEPRECATED ***
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
 *
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *
 *  Deprecated:
 *    Use -[NSWorkspace launchApplicationAtURL:options:configuration:error:] instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSOpenApplication(
  const LSApplicationParameters *  appParams,
  ProcessSerialNumber *            outPSN)          /* can be NULL */ __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use -[NSWorkspace launchApplicationAtURL:options:configuration:error:] instead.");



/*
 *  LSOpenItemsWithRole()   *** DEPRECATED ***
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
 *
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *
 *  Deprecated:
 *    Use NSWorkspace instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
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
  CFIndex                          inMaxPSNCount)             __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use NSWorkspace instead.");



/*
 *  LSOpenURLsWithRole()   *** DEPRECATED ***
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
 *
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *
 *  Deprecated:
 *    Use NSWorkspace instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
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
  CFIndex                          inMaxPSNCount)             __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use NSWorkspace instead.");
#endif



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __LSOPENDEPRECATED__ */

