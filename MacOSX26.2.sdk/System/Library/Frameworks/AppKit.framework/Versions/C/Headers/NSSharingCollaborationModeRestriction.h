//
/*
        NSSharingCollaborationModeRestriction.h
        Application Kit
        Copyright (c) 2023-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSURL.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

/// Represents the types of sharing (collaborating on an item vs. sending a copy of the item)
/// The share picker supports up to two modes, each of which corresponds to one of these types
API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos)
typedef NS_ENUM(NSInteger, NSSharingCollaborationMode) {
    NSSharingCollaborationModeSendCopy,
    NSSharingCollaborationModeCollaborate,
};

/// Specifies whether a specific type of sharing should be disabled in the share picker, and if so, whether a reason should be provided for the disablement
/// If a reason is provided, the corresponding mode will show up as an option, but an alert explaining why it is disabled will show if it is chosen, and the mode will switch back to the supported one
/// Optionally, an extra alert button can be provided for a "recovery suggestion". This can give a user a way to fix whatever is causing this type of sharing to be disabled
/// If no reason is provided, the corresponding mode will not show up as an option
API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos)
NS_SWIFT_NAME(NSSharingServicePicker.CollaborationModeRestriction)
@interface NSSharingCollaborationModeRestriction : NSObject<NSSecureCoding, NSCopying>

/// The type of sharing which should be disabled
@property (readonly) NSSharingCollaborationMode disabledMode;

/// The title of the alert if a reason for disabling is provided
@property (readonly, copy, nullable) NSString *alertTitle;

/// The message of the alert if a reason for disabling is provided
@property (readonly, copy, nullable) NSString *alertMessage;

/// The label on the alert button which will simply confirm that the alert was viewed and dismiss it
/// Defaults to "OK"
@property (readonly, copy, nullable) NSString *alertDismissButtonTitle;

/// The label on the recovery suggestion button if it is provided
@property (readonly, copy, nullable) NSString *alertRecoverySuggestionButtonTitle;

/// The URL that is opened when the user selects the recovery suggestion, if any
@property (readonly, copy, nullable) NSURL *alertRecoverySuggestionButtonLaunchURL;

/// - Parameters:
///     - disabledMode: The disabled type of sharing
- (instancetype)initWithDisabledMode:(NSSharingCollaborationMode)disabledMode;

/// - Parameters:
///     - disabledMode: The disabled type of sharing
///     - alertTitle: The alert title
///     - alertMessage: The alert message
- (instancetype)initWithDisabledMode:(NSSharingCollaborationMode)disabledMode alertTitle:(NSString *)alertTitle alertMessage:(NSString *)alertMessage;

/// - Parameters:
///     - disabledMode: The disabled type of sharing
///     - alertTitle: The alert title
///     - alertMessage: The alert message
///     - alertDismissButtonTitle: The label on the default alert button
- (instancetype)initWithDisabledMode:(NSSharingCollaborationMode)disabledMode alertTitle:(NSString *)alertTitle alertMessage:(NSString *)alertMessage alertDismissButtonTitle:(NSString *)alertDismissButtonTitle;

/// - Parameters:
///     - disabledMode: The disabled type of sharing
///     - alertTitle: The alert title
///     - alertMessage: The alert message
///     - alertDismissButtonTitle: The label on the default alert button
///     - alertRecoverySuggestionButtonTitle: The label on the optional recovery suggestion button on the alert
///     - alertRecoverySuggestionButtonLaunchURL: The URL that is opened when the optional recovery suggestion button is selected
- (instancetype)initWithDisabledMode:(NSSharingCollaborationMode)disabledMode alertTitle:(NSString *)alertTitle alertMessage:(NSString *)alertMessage alertDismissButtonTitle:(NSString *)alertDismissButtonTitle alertRecoverySuggestionButtonTitle:(NSString *)alertRecoverySuggestionButtonTitle alertRecoverySuggestionButtonLaunchURL:(NSURL *)alertRecoverySuggestionButtonLaunchURL;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
