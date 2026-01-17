/*
     File:       LSQuarantine.h
 
     Contains:   File quarantine property keys
 
     Copyright:  Copyright 2003-2009 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/
#ifndef __LSQUARANTINE__
#define __LSQUARANTINE__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

/*
 *    The following keys may appear in a quarantine properties dictionary. To access a
 *    file's quarantine properties dictionary, fetch the kLSItemQuarantineProperties
 *    attribute using LSCopyItemAttribute() or LSCopyItemAttributes(). 
 *    The quarantine property dictionary can be set using LSSetItemAttribute().
 *
 *
 * kLSQuarantineAgentNameKey - value type CFStringRef
 *
 *    The name of the quarantining agent (application or program). When setting quarantine
 *    properties, this value is set automatically to the current process name if this key is not 
 *    present in the caller's dictionary.
 *
 *
 * kLSQuarantineAgentBundleIdentifierKey - value type CFStringRef
 *
 *    The bundle identifier of the quarantining agent, if available. When setting quarantine 
 *    properties, this value is set automatically if the key is not present in the caller's 
 *    dictionary. The automatic value is the main bundle identifier of the current process.
 *
 *
 * kLSQuarantineTimeStampKey - value type CFDateRef
 *
 *    The date and time the item was quarantined. When setting quarantine properties,
 *    this property is set automatically to the current date and time if this key is not present 
 *    in the caller's dictionary.
 *
 *
 * kLSQuarantineTypeKey - value type CFStringRef
 *
 *    A symbolic string identifying the why the item is quarantined, if available. 
 *    The value is one of the following:
 *
 *    kLSQuarantineTypeWebDownload
 *    kLSQuarantineTypeOtherDownload
 *    kLSQuarantineTypeEmailAttachment
 *    kLSQuarantineTypeInstantMessageAttachment
 *    kLSQuarantineTypeCalendarEventAttachment
 *    kLSQuarantineTypeOtherAttachment
 *
 *
 * kLSQuarantineDataURLKey - value type CFURLRef
 *
 *    The URL from which the data for the quarantined item data was actaully streamed
 *    or downloaded, if available.
 *
 *
 * kLSQuarantineOriginURLKey - value type CFURLRef
 *
 *    The URL of the resource originally hosting the quarantined item, from the user's point of
 *    view. For web downloads, this property is the URL of the web page on which the user initiated
 *    the download. For attachments, this property is the URL of the resource to which the quarantined
 *    item was attached (e.g. the email message, calendar event, etc.). The origin URL may be a file URL
 *    for local resources, or a custom URL to which the quarantining application will respond when asked 
 *    to open it. The quarantining application should respond by displaying the resource to the user. 
 *    Note: The origin URL should not be set to the data URL, or the quarantining application may start 
 *    downloading the file again if the user choses to view the origin URL while resolving a quarantine 
 *    warning.
 *
 */
/*
 *  kLSQuarantineAgentNameKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineAgentNameKey                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineAgentBundleIdentifierKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineAgentBundleIdentifierKey       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineTimeStampKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineTimeStampKey                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineTypeKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineTypeKey                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineTypeWebDownload
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineTypeWebDownload                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineTypeOtherDownload
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineTypeOtherDownload              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineTypeEmailAttachment
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineTypeEmailAttachment            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineTypeInstantMessageAttachment
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineTypeInstantMessageAttachment   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineTypeCalendarEventAttachment
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineTypeCalendarEventAttachment    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineTypeOtherAttachment
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineTypeOtherAttachment            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineOriginURLKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineOriginURLKey                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSQuarantineDataURLKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSQuarantineDataURLKey                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


#endif /* __LSQUARANTINE__ */

