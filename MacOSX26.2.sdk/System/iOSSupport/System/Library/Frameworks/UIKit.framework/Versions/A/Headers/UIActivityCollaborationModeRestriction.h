#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<ShareSheet/UIActivityCollaborationModeRestriction.h>)
//
//  UIActivityCollaborationModeRestriction.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIActivityItemsConfigurationReading.h>

NS_ASSUME_NONNULL_BEGIN

/// A key for a collaboration mode restriction, used to specify the case where Share Sheet should not support some modes of sharing even if they are supported by the items being shared
/// The object returned for this key should be an array of UIActivityCollaborationModeRestriction instances
/// For supported behaviour, this array should have a maximum size of one less than the amount of possible Share Sheet modes
/// Currently at most one object should be provided
UIKIT_EXTERN UIActivityItemsConfigurationMetadataKey const UIActivityItemsConfigurationMetadataKeyCollaborationModeRestrictions API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos); // NSArray<UIActivityCollaborationModeRestriction *> *

/// Represents the types of sharing (collaborating on an item vs. sending a copy of the item)
/// Share Sheet supports up to two modes, each of which corresponds to one of these types
typedef NS_ENUM(NSInteger, UIActivityCollaborationMode) {
	UIActivityCollaborationModeSendCopy,
	UIActivityCollaborationModeCollaborate,
} API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/// Specifies whether any types of sharing should be disabled in Share Sheet, and if so, whether they should provide a reason when tapped
/// If a reason is provided, the corresponding mode will show up as an option, but an alert explaining why it is disabled will show if it is chosen, and the mode will switch back to the supported one
/// Optionally, an extra alert button can be provided for a "recovery suggestion". This can give a user a way to fix whatever is causing this type of sharing to be disabled
/// If no reason is provided, the corresponding mode will not show up as an option
API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_NAME(UIActivityViewController.CollaborationModeRestriction)
@interface UIActivityCollaborationModeRestriction : NSObject<NSSecureCoding, NSCopying>

/// The type of sharing which should be disabled
@property (nonatomic, readonly) UIActivityCollaborationMode disabledMode;

/// The title of the alert if a reason for disabling is provided
@property (nonatomic, readonly, copy, nullable) NSString *alertTitle;

/// The message of the alert if a reason for disabling is provided
@property (nonatomic, readonly, copy, nullable) NSString *alertMessage;

///The label on the alert button which will simply confirm that the alert was viewed and dismiss it
/// Defaults to "OK"
@property (nonatomic, readonly, copy, nullable) NSString *alertDismissButtonTitle;

/// The label on the recovery suggestion button if it is provided
@property (nonatomic, readonly, copy, nullable) NSString *alertRecoverySuggestionButtonTitle;

/// On tapping the recovery suggestion button (if it is provided), the user will be launched to this URL
@property (nonatomic, readonly, copy, nullable) NSURL *alertRecoverySuggestionButtonLaunchURL;

/// - Parameters:
///     - disabledMode: The disabled type of sharing
- (instancetype)initWithDisabledMode:(UIActivityCollaborationMode)disabledMode;

/// - Parameters:
///     - disabledMode: The disabled type of sharing
///     - alertTitle: The alert title
///     - alertMessage: The alert message
- (instancetype)initWithDisabledMode:(UIActivityCollaborationMode)disabledMode alertTitle:(NSString *)alertTitle alertMessage:(NSString *)alertMessage;

/// - Parameters:
///     - disabledMode: The disabled type of sharing
///     - alertTitle: The alert title
///     - alertMessage: The alert message
///     - alertDismissButtonTitle: The label on the default alert button
- (instancetype)initWithDisabledMode:(UIActivityCollaborationMode)disabledMode alertTitle:(NSString *)alertTitle alertMessage:(NSString *)alertMessage alertDismissButtonTitle:(NSString *)alertDismissButtonTitle;

/// - Parameters:
///     - disabledMode: The disabled type of sharing
///     - alertTitle: The alert title
///     - alertMessage: The alert message
///     - alertDismissButtonTitle: The label on the default alert button
///     - alertRecoverySuggestionButtonTitle: The label on the optional recovery suggestion button on the alert
///     - alertRecoverySuggestionButtonLaunchURL: The URL which launches when the optional recovery suggestion button is tapped
- (instancetype)initWithDisabledMode:(UIActivityCollaborationMode)disabledMode alertTitle:(NSString *)alertTitle alertMessage:(NSString *)alertMessage alertDismissButtonTitle:(NSString *)alertDismissButtonTitle alertRecoverySuggestionButtonTitle:(NSString *)alertRecoverySuggestionButtonTitle alertRecoverySuggestionButtonLaunchURL:(NSURL *)alertRecoverySuggestionButtonLaunchURL;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (NSString *)description;

@end

NS_ASSUME_NONNULL_END

#else
#import <ShareSheet/UIActivityCollaborationModeRestriction.h>
#endif
