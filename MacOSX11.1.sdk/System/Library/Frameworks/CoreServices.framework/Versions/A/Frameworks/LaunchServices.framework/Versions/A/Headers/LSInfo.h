/*
     File:       LSInfo.h
 
     Contains:   Public interfaces for LaunchServices.framework
 
     Copyright:  (c) 2001-2012 by Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/

*/

#ifndef __LSINFO__
#define __LSINFO__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#if TARGET_OS_OSX

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif
#endif // TARGET_OS_OSX

#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)



CF_ASSUME_NONNULL_BEGIN



/* ======================================================================================================== */
/* LaunchServices Type & Constants                                                                          */
/* ======================================================================================================== */

CF_ENUM(OSStatus) {
  kLSNo32BitEnvironmentErr      = -10386, /* i386 is no longer supported*/
  kLSAppInTrashErr              = -10660, /* The app cannot be run when inside a Trash folder*/
  kLSExecutableIncorrectFormat  = -10661, /* No compatible executable was found*/
  kLSAttributeNotFoundErr       = -10662, /* An item attribute value could not be found with the specified name*/
  kLSAttributeNotSettableErr    = -10663, /* The attribute is not settable*/
  kLSIncompatibleApplicationVersionErr = -10664, /* The app is incompatible with the current OS*/
  kLSNoRosettaEnvironmentErr    = -10665, /* PowerPC apps are no longer supported */
  kLSGarbageCollectionUnsupportedErr = -10666, /* Objective-C garbage collection is no longer supported*/
  kLSUnknownErr                 = -10810, /* Unexpected internal error*/
  kLSNotAnApplicationErr        = -10811, /* Item needs to be an application, but is not*/
  kLSNotInitializedErr          = -10812, /* Not used in 10.2 and later*/
  kLSDataUnavailableErr         = -10813, /* E.g. no kind string*/
  kLSApplicationNotFoundErr     = -10814, /* E.g. no application claims the file*/
  kLSUnknownTypeErr             = -10815, /* Don't know anything about the type of the item*/
  kLSDataTooOldErr              = -10816, /* Not used in 10.3 and later*/
  kLSDataErr                    = -10817, /* Not used in 10.4 and later*/
  kLSLaunchInProgressErr        = -10818, /* E.g. launching an already launching application*/
  kLSNotRegisteredErr           = -10819, /* Not used in 10.3 and later*/
  kLSAppDoesNotClaimTypeErr     = -10820, /* One or more documents are of types (and/or one or more URLs are of schemes) not supported by the target application (sandboxed callers only)*/
  kLSAppDoesNotSupportSchemeWarning = -10821, /* Not used in 10.2 and later*/
  kLSServerCommunicationErr     = -10822, /* The server process (registration and recent items) is not available*/
  kLSCannotSetInfoErr           = -10823, /* The extension visibility on this item cannot be changed*/
  kLSNoRegistrationInfoErr      = -10824, /* The item contains no registration info*/
  kLSIncompatibleSystemVersionErr = -10825, /* The app cannot run on the current OS version*/
  kLSNoLaunchPermissionErr      = -10826, /* User doesn't have permission to launch the app (managed networks)*/
  kLSNoExecutableErr            = -10827, /* The executable is missing*/
  kLSNoClassicEnvironmentErr    = -10828, /* The Classic environment was required but is not available*/
  kLSMultipleSessionsNotSupportedErr = -10829, /* The app cannot run simultaneously in two different sessions*/
};

typedef CF_OPTIONS(OptionBits, LSRolesMask) {
  kLSRolesNone                  = 0x00000001, /* no claim is made about support for this type/scheme*/
  kLSRolesViewer                = 0x00000002, /* claim to view items of this type*/
  kLSRolesEditor                = 0x00000004, /* claim to edit items of this type/scheme*/
  kLSRolesShell                 = 0x00000008, /* claim to execute items of this type*/
  kLSRolesAll                   = (UInt32)0xFFFFFFFF /* claim to do it all*/
};

CF_ENUM(OSType) {
  kLSUnknownType                = 0,
  kLSUnknownCreator             = 0
};

typedef CF_OPTIONS(OptionBits, LSAcceptanceFlags) {
  kLSAcceptDefault              = 0x00000001,
  kLSAcceptAllowLoginUI         = 0x00000002 /* show UI to log in if necessary*/
};


/* ======================================================================================================== */
/* LaunchServices API                                                                                       */
/* ======================================================================================================== */



/*
 *  LSCopyDefaultApplicationURLForURL()
 *  
 *  Summary:
 *    Return the application used to open an item.
 *  
 *  Discussion:
 *    Consults the binding tables to return the application that would
 *    be used to open inURL if it were double-clicked in the
 *    Finder. This application will be the user-specified override if
 *    appropriate or the default otherwise.
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The URL of the item for which the application is requested.
 *
 *    inRoleMask:
 *      Whether to return the editor or viewer for inURL. If you
 *      don't care which, use kLSRolesAll.
 *    
 *    outError:
 *      On failure, set to a CFError describing the problem. If you are
 *      not interested in this information, pass NULL. The caller is
 *      responsible for releasing this object.
 *
 *  Result:
 *    If an acceptable application is found, its URL is returned.
 *    If the URL is a file:// URL, the application bound to the specified
 *    file or directory's type is returned. If the URL's scheme is something
 *    else, its default scheme handler is returned. If no application could
 *    be found, NULL is returned and outError (if not NULL) is populated.
 *    with kLSApplicationNotFoundErr.
 *    The caller is responsible for releasing this URL.
 */
extern __nullable CFURLRef
LSCopyDefaultApplicationURLForURL(
  CFURLRef                           inURL,
  LSRolesMask                        inRoleMask,
  __nullable CFErrorRef *__nullable  outError)                       API_AVAILABLE( macos(10.10) ) API_UNAVAILABLE( ios, tvos, watchos );
	
	
	
/*
 *  LSCopyDefaultApplicationURLForContentType()
 *  
 *  Summary:
 *    Return the application used to open a content type (UTI).
 *  
 *  Discussion:
 *    Consults the binding tables to return the application that would
 *    be used to open a file of type inContentType if it were double-clicked
 *    in the Finder. This application will be the user-specified override if
 *    appropriate or the default otherwise.
 *  
 *  Parameters:
 *    
 *    inContentType:
 *      The Uniform Type Identifier (UTI) of the item for which the
 *      application is requested.
 *
 *    inRoleMask:
 *      Whether to return the editor or viewer for inContentType. If you
 *      don't care which, use kLSRolesAll.
 *    
 *    outError:
 *      On failure, set to a CFError describing the problem. If you are
 *      not interested in this information, pass NULL. The caller is
 *      responsible for releasing this object.
 *
 *  Result:
 *    If an acceptable application is found, its URL is returned.
 *    If no application could be found, NULL is returned and
 *    outError (if not NULL) is populated with kLSApplicationNotFoundErr.
 *    The caller is responsible for releasing this URL.
 */
extern __nullable CFURLRef
LSCopyDefaultApplicationURLForContentType(
  CFStringRef                        inContentType,
  LSRolesMask                        inRoleMask,
  __nullable CFErrorRef *__nullable  outError)                       API_AVAILABLE( macos(10.10) ) API_UNAVAILABLE( ios, tvos, watchos );
	
	
	
/*
 *  LSCopyApplicationURLsForBundleIdentifier()
 *  
 *  Summary:
 *    Given a bundle identifier (such as com.apple.finder), find
 *    all URLs to the corresponding application.
 *  
 *  Discussion:
 *    Returns zero or more URLs to applications that have the specified
 *    bundle identifier.
 *  
 *  Parameters:
 *    
 *    inBundleIdentifier:
 *      The bundle identifier of interest, such as "com.apple.finder". Must
 *      not be NULL.
 *    
 *    outError:
 *      On failure, set to a CFError describing the problem. If you are
 *      not interested in this information, pass NULL. The caller is
 *      responsible for releasing this object.
 *    
 *  Result:
 *    If any applications with the specified bundle identifier are found,
 *    their URLs are returned in a CFArray. If no application could be found,
 *    NULL is returned and outError (if not NULL) is populated with kLSApplicationNotFoundErr.
 *    The order of elements in the array is undefined.
 *    The caller is responsible for releasing this array.
 *
 */
extern __nullable CFArrayRef
LSCopyApplicationURLsForBundleIdentifier(
  CFStringRef                        inBundleIdentifier,
  __nullable CFErrorRef *__nullable  outError)                       API_AVAILABLE( macos(10.10) ) API_UNAVAILABLE( ios, tvos, watchos );
	
	
	
/*
 *  LSCopyApplicationURLsForURL()
 *  
 *  Discussion:
 *    Returns an array of URLs to applications that offer the requested
 *    role(s) for the input item.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The CFURLRef of the item for which all suitable applications
 *      are desired. If the URL is a file URL, it is treated as a
 *      document, and applications are selected based on the document's
 *      type information. Otherwise, applications are selected based on
 *      the URL's scheme.
 *    
 *    inRoleMask:
 *      The role(s) which must intersect with the role provided by an
 *      application for the specified item in order for the application
 *      to be included in the result. Pass kLSRolesAll if any role is
 *      acceptable.
 *  
 *  Result:
 *    An array of CFURLRefs, one for each application which can open
 *    inURL with at least one of the roles in inRoleMask, or NULL if no
 *    applications can open the item. When an array is returned, you
 *    must eventually release it.
 *
 *    The order of the resulting array is undefined. If you need the
 *    default application for the specified URL, use LSCopyDefaultApplicationURLForURL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern __nullable CFArrayRef
LSCopyApplicationURLsForURL(
  CFURLRef      inURL,
  LSRolesMask   inRoleMask)                                          API_AVAILABLE( macos(10.3) ) API_UNAVAILABLE( ios, tvos, watchos );

	
	
/*
 *  LSCanURLAcceptURL()
 *  
 *  Summary:
 *    Determine whether an item can accept another item.
 *  
 *  Discussion:
 *    Returns in outAcceptsItem whether inTargetURL can accept
 *    inItemURL as in a drag and drop operation. If inRoleMask is other
 *    than kLSRolesAll then make sure inTargetRef claims to fulfill the
 *    requested role.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inItemURL:
 *      CFURLRef of the item about which acceptance is requested.
 *    
 *    inTargetURL:
 *      CFURLRef of the potential target.
 *    
 *    inRoleMask:
 *      The role(s) the target must claim in order to consider
 *      acceptance.
 *    
 *    inFlags:
 *      Use kLSAcceptDefault.
 *    
 *    outAcceptsItem:
 *      Filled in with result. Must not be NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCanURLAcceptURL(
  CFURLRef            inItemURL,
  CFURLRef            inTargetURL,
  LSRolesMask         inRoleMask,
  LSAcceptanceFlags   inFlags,
  Boolean *           outAcceptsItem)                                API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );



/*
 *  LSRegisterURL()
 *  
 *  Discussion:
 *    If the specified URL refers to an application or other bundle
 *    claiming to handle documents or URLs, add the bundle's document
 *    and URL claims to the Launch Services database.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The CFURLRef of the item (a directory or file) to be registered.
 *    
 *    inUpdate:
 *      When false, LSRegisterURL does not register the item if it has
 *      already been registered and the current modification date of
 *      the item has not changed from when it was last registered. When
 *      true, the item's registered info is updated, even if the
 *      modification has not changed.
 *  
 *  Result:
 *    An OSStatus value: noErr - Success kLSNoRegistrationInfoErr - The
 *    item does not contain info requiring registration kLSDataErr -
 *    The item's property list info is malformed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSRegisterURL(
  CFURLRef   inURL,
  Boolean    inUpdate)                                               API_AVAILABLE( ios(4.0), macos(10.3), tvos(9.0), watchos(1.0) );



/* ================================================================================== */
/*   API for accessing content and URL handler preferences                            */
/* ================================================================================== */

/*
 *  LSCopyDefaultRoleHandlerForContentType
 *  
 *  Returns the application bundle identifier of the default handler 
 *  for the specified content type (UTI), in the specified role(s).
 *  For any role, specify kLSRolesAll. Returns NULL if no handler
 *  is available.
 */
/*
 *  LSCopyDefaultRoleHandlerForContentType()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern __nullable CFStringRef
LSCopyDefaultRoleHandlerForContentType(
  CFStringRef   inContentType,
  LSRolesMask   inRole)                                              API_AVAILABLE( ios(4.0), macos(10.4), tvos(9.0), watchos(1.0) );



/*
 *  LSCopyAllRoleHandlersForContentType
 *  
 *  Returns an array of application bundle identifiers for
 *  applications capable of handling the specified content type 
 *  (UTI) with the specified role(s). Application content handling 
 *  capabilities are determined according to the kCFBundleDocumentTypes 
 *  listed in an application's Info.plist). For any role, specify kLSRolesAll. 
 *  Returns NULL if no handlers are available.
 */
/*
 *  LSCopyAllRoleHandlersForContentType()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern __nullable CFArrayRef
LSCopyAllRoleHandlersForContentType(
  CFStringRef   inContentType,
  LSRolesMask   inRole)                                              API_AVAILABLE( macos(10.4) ) API_UNAVAILABLE( ios, tvos, watchos );



/*
 *  LSSetDefaultRoleHandlerForContentType
 *  
 *  Sets the user's preferred handler for the specified content
 *  type (UTI) in the specified role(s). For all roles, specify
 *  kLSRolesAll. The handler is specified as an application
 *  bundle identifier.
 */
/*
 *  LSSetDefaultRoleHandlerForContentType()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSetDefaultRoleHandlerForContentType(
  CFStringRef   inContentType,
  LSRolesMask   inRole,
  CFStringRef   inHandlerBundleID)                                   API_AVAILABLE( ios(4.0), macos(10.4), tvos(9.0), watchos(1.0) );



/*
 *  LSCopyDefaultHandlerForURLScheme()   *** DEPRECATED ***
 *  
 *  Returns the bundle identifier of the default handler for
 *  the specified URL scheme. Returns NULL if no handler
 *  is available.
 *
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Deprecated:
 *    Use LSCopyDefaultApplicationURLForURL() instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern __nullable CFStringRef
LSCopyDefaultHandlerForURLScheme(CFStringRef inURLScheme)            API_DEPRECATED("Use LSCopyDefaultApplicationURLForURL() instead.", macos(10.4, 10.15)) API_UNAVAILABLE(ios, watchos, tvos);



/*
 *  LSCopyAllHandlersForURLScheme()   *** DEPRECATED ***
 *
 *  Returns an array of application bundle identifiers for
 *  applications capable of handling the specified URL scheme.
 *  URL handling capability is determined according to the
 *  kCFBundleURLTypes listed in an application's Info.plist).
 *  Returns NULL if no handlers are available.
 *
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Deprecated:
 *    Use LSCopyApplicationURLsForURL() instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern __nullable CFArrayRef
LSCopyAllHandlersForURLScheme(CFStringRef inURLScheme)               API_DEPRECATED("Use LSCopyApplicationURLsForURL() instead.", macos(10.4, 10.15)) API_UNAVAILABLE(ios, watchos, tvos);



/*
 *  LSSetDefaultHandlerForURLScheme
 *  
 *  Sets the user's preferred handler for the specified URL
 *  scheme. The handler is specified as an application
 *  bundle identifier.
 */
/*
 *  LSSetDefaultHandlerForURLScheme()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSetDefaultHandlerForURLScheme(
  CFStringRef   inURLScheme,
  CFStringRef   inHandlerBundleID)                            API_AVAILABLE( ios(4.0), macos(10.4), tvos(9.0), watchos(1.0) );



CF_ASSUME_NONNULL_END



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#include <LaunchServices/LSInfoDeprecated.h>
	

#endif /* __LSINFO__ */

