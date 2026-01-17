/*
    IMServicePlugInTypes.h
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#ifndef IMSERVICEPLUGIN_EXTERN
#ifdef __cplusplus
#define IMSERVICEPLUGIN_EXTERN  extern "C" __attribute__((visibility("default")))
#else
#define IMSERVICEPLUGIN_EXTERN  extern __attribute__((visibility("default")))
#endif
#endif

#ifndef IMSERVICEPLUGIN_EXTERN_CLASS
#define IMSERVICEPLUGIN_EXTERN_CLASS  extern __attribute__((visibility("default")))
#endif

#import <Foundation/Foundation.h>

#pragma mark -
#pragma mark Account Settings

/*
    Used by:
        -[id<IMServicePlugIn> updateAccountSettings:]
*/
IMSERVICEPLUGIN_EXTERN NSString * const IMAccountSettingServerHost NS_DEPRECATED_MAC(10_7, 10_13);  // NSString - the server hostname
IMSERVICEPLUGIN_EXTERN NSString * const IMAccountSettingServerPort NS_DEPRECATED_MAC(10_7, 10_13);  // NSNumber - the server port number
IMSERVICEPLUGIN_EXTERN NSString * const IMAccountSettingLoginHandle NS_DEPRECATED_MAC(10_7, 10_13); // NSString - the login handle to use
IMSERVICEPLUGIN_EXTERN NSString * const IMAccountSettingPassword NS_DEPRECATED_MAC(10_7, 10_13);    // NSString - the password
IMSERVICEPLUGIN_EXTERN NSString * const IMAccountSettingUsesSSL NS_DEPRECATED_MAC(10_7, 10_13);     // NSNumber - (YES = use SSL, NO = do not use SSL)


#pragma mark -
#pragma mark Session Properties

//  Used by:
//    -[id<IMServicePlugInGroupListSupport> updateSessionProperties:]
//    -[IMServiceApplication sessionPropertiesChanged:]

typedef NS_ENUM(NSInteger, IMSessionAvailability) {
    IMSessionAvailabilityAway,
    IMSessionAvailabilityAvailable
} NS_ENUM_DEPRECATED_MAC(10_7, 10_13);

IMSERVICEPLUGIN_EXTERN NSString * const IMSessionPropertyAvailability NS_DEPRECATED_MAC(10_7, 10_13);   // NSNumber of IMSessionAvailabilityStatus
IMSERVICEPLUGIN_EXTERN NSString * const IMSessionPropertyStatusMessage NS_DEPRECATED_MAC(10_7, 10_13);  // NSString  - Current status message as plaintext NSString
IMSERVICEPLUGIN_EXTERN NSString * const IMSessionPropertyPictureData NS_DEPRECATED_MAC(10_7, 10_13);    // NSData    - Image that should be used for the users icon.
IMSERVICEPLUGIN_EXTERN NSString * const IMSessionPropertyIdleDate NS_DEPRECATED_MAC(10_7, 10_13);       // NSDate    - the time of the last user activity
IMSERVICEPLUGIN_EXTERN NSString * const IMSessionPropertyIsInvisible NS_DEPRECATED_MAC(10_7, 10_13);    // NSNumber  - If YES, the user wishes to appear offline to other users.

#pragma mark -
#pragma mark Group List Types

typedef NS_ENUM(NSUInteger, IMGroupListPermissions) {
    IMGroupListCanReorderGroup   = (1 << 0),
    IMGroupListCanRenameGroup    = (1 << 1),
    IMGroupListCanAddNewMembers  = (1 << 2),
    IMGroupListCanRemoveMembers  = (1 << 3),
    IMGroupListCanReorderMembers = (1 << 4)
} NS_ENUM_DEPRECATED_MAC(10_7, 10_13);

/* Use IMGroupListDefaultGroup for IMGroupListNameKey for ungrouped handles */
IMSERVICEPLUGIN_EXTERN NSString * const IMGroupListDefaultGroup NS_DEPRECATED_MAC(10_7, 10_13);

IMSERVICEPLUGIN_EXTERN NSString * const IMGroupListNameKey NS_DEPRECATED_MAC(10_7, 10_13);          // NSString - the name of the group
IMSERVICEPLUGIN_EXTERN NSString * const IMGroupListPermissionsKey NS_DEPRECATED_MAC(10_7, 10_13);   // NSNumber - the permissions for the group
IMSERVICEPLUGIN_EXTERN NSString * const IMGroupListHandlesKey NS_DEPRECATED_MAC(10_7, 10_13);       // NSArray of NSStrings - the members in the group


#pragma mark -
#pragma mark Handle Properties

//  Used by:
//    -[IMServiceApplication handle:propertiesChanged:]

typedef NS_ENUM(NSInteger, IMHandleAvailability) {
    IMHandleAvailabilityUnknown   = -2,
    IMHandleAvailabilityOffline   = -1,
    IMHandleAvailabilityAway      =  0,
    IMHandleAvailabilityAvailable =  1
} NS_ENUM_DEPRECATED_MAC(10_7, 10_13);

typedef NS_ENUM(NSInteger, IMHandleAuthorizationStatus) {
    IMHandleAuthorizationStatusAccepted = 0,  // An outgoing authorization request was accepted.  You are now able to see the handle's online status
    IMHandleAuthorizationStatusPending  = 1,  // An outgoing authorization request has been sent to the handle.  "Waiting for authorization"
    IMHandleAuthorizationStatusDeclined = 2   // An outgoing authorization request was declined.                 "Not Authorized"
} NS_ENUM_DEPRECATED_MAC(10_7, 10_13);


IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyAvailability NS_DEPRECATED_MAC(10_7, 10_13);        // NSNumber of IMHandleAvailability
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyStatusMessage NS_DEPRECATED_MAC(10_7, 10_13);       // NSString  - Current status message as plaintext NSString
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyAuthorizationStatus NS_DEPRECATED_MAC(10_7, 10_13); // NSNumber of IMHandleAuthorizationStatus
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyIdleDate NS_DEPRECATED_MAC(10_7, 10_13);            // NSDate    - If the user is idle, the time of the last user activity.  Use [NSDate distantPast] if the exact time is not known
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyAlias NS_DEPRECATED_MAC(10_7, 10_13);               // NSString  - A "prettier" version of the handle, if available
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyFirstName NS_DEPRECATED_MAC(10_7, 10_13);           // NSString  - The first name (given name) of a handle
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyLastName NS_DEPRECATED_MAC(10_7, 10_13);            // NSString  - The last name (family name) of a handle
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyEmailAddress NS_DEPRECATED_MAC(10_7, 10_13);        // NSString  - The e-mail address for a handle
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyPictureIdentifier NS_DEPRECATED_MAC(10_7, 10_13);   // NSString  - A unique identifier for the handle's picture
IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyPictureData NS_DEPRECATED_MAC(10_7, 10_13);         // NSData    - The handle's picture data. Include only in response to a -requestPictureForHandle:withIdentifier: request

IMSERVICEPLUGIN_EXTERN NSString * const IMHandlePropertyCapabilities NS_DEPRECATED_MAC(10_7, 10_13);            // NSArray of the following NSStrings:
IMSERVICEPLUGIN_EXTERN NSString * const     IMHandleCapabilityMessaging NS_DEPRECATED_MAC(10_7, 10_13);         //      If present, the handle can send and receive instant messages
IMSERVICEPLUGIN_EXTERN NSString * const     IMHandleCapabilityOfflineMessaging NS_DEPRECATED_MAC(10_7, 10_13);  //      If present, the handle can receive instant messages when offline
IMSERVICEPLUGIN_EXTERN NSString * const     IMHandleCapabilityChatRoom NS_DEPRECATED_MAC(10_7, 10_13);          //      If present, the handle can join chat rooms
IMSERVICEPLUGIN_EXTERN NSString * const     IMHandleCapabilityHandlePicture NS_DEPRECATED_MAC(10_7, 10_13);     //      If present, the handle can have a handle picture
IMSERVICEPLUGIN_EXTERN NSString * const     IMHandleCapabilityFileTransfer NS_DEPRECATED_MAC(10_7, 10_13);      //      If present, the handle can send and receive files


#pragma mark -
#pragma mark Rich-text Message Format Attributes

//  Used by:
//    -[IMServicePlugInMessage content]

IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeFontFamily NS_DEPRECATED_MAC(10_7, 10_13);           // NSString
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeFontSize NS_DEPRECATED_MAC(10_7, 10_13);             // NSNumber
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeItalic NS_DEPRECATED_MAC(10_7, 10_13);               // NSNumber  (YES = italic,    NO = normal)
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeBold NS_DEPRECATED_MAC(10_7, 10_13);                 // NSNumber  (YES = bold,      NO = normal)
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeUnderline NS_DEPRECATED_MAC(10_7, 10_13);            // NSNumber  (YES = underline, NO = normal)
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeStrikethrough NS_DEPRECATED_MAC(10_7, 10_13);        // NSNumber  (YES = strikethrough, NO = normal)
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeLink NS_DEPRECATED_MAC(10_7, 10_13);                 // NSURL
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributePreformatted NS_DEPRECATED_MAC(10_7, 10_13);         // NSNumber  (YES = preformatted, Messages should not add smileys, URLs, or data detection)
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeBaseWritingDirection NS_DEPRECATED_MAC(10_7, 10_13); // NSNumber  (-1 = natural, 0 = left-to-right, 1 = right-to-left)

// All colors specified as NSStrings in hex format (@"#ff0000", @"#fff", @"333", @"12abcd")
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeForegroundColor NS_DEPRECATED_MAC(10_7, 10_13);          // The foreground color of text
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeBackgroundColor NS_DEPRECATED_MAC(10_7, 10_13);          // The background color behind text
IMSERVICEPLUGIN_EXTERN NSString * const IMAttributeMessageBackgroundColor NS_DEPRECATED_MAC(10_7, 10_13);   // The color of the background message bubble/box

