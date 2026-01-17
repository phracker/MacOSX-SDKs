#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIGuidedAccess.h>)
//
//  UIGuidedAccess.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN NSErrorDomain const UIGuidedAccessErrorDomain API_AVAILABLE(ios(12.2));

typedef NS_ERROR_ENUM(UIGuidedAccessErrorDomain, UIGuidedAccessErrorCode) {
    // The application is not authorized to perform the requested action. For example, it may have requested a configuration change but is not locked into Single App Mode via a configuration profile.
    UIGuidedAccessErrorPermissionDenied,
    // Generic failure.
    UIGuidedAccessErrorFailed = NSIntegerMax
} API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(watchos, tvos);

/*
 UIGuidedAccessRestrictions
 
 Guided Access is a feature that restricts iOS to running only one app, while disabling the use of hardware buttons.
 
 The UIGuidedAccessRestrictions protocol allows an app to specify additional features that can be disabled by users when in Guided Access mode.
 
 For example, a Photos-based app could disallow photo deletion.
 If the user disabled photo deletion, guidedAccessRestrictionWithIdentifier:willChangeState: will be called.
 The app should then completely remove the ability to delete photos through any user interface mechanism.
 
 The app should provide the list of semantic features that are desirable to be disabled while running in Guided Access mode.
 */

typedef NS_ENUM(NSInteger, UIGuidedAccessRestrictionState) {
    UIGuidedAccessRestrictionStateAllow,
    UIGuidedAccessRestrictionStateDeny
};

/*
 UIGuidedAccessRestrictionDelegate
 
 Implement on the application delegate to present the user with additional Guided Access restrictions.
 
 The initial state of all Guided Access restrictions is UIGuidedAccessRestrictionStateAllow.
 */
UIKIT_EXTERN API_AVAILABLE(ios(7.0)) @protocol UIGuidedAccessRestrictionDelegate <NSObject>

@required

/*
 Returns a list of restriction identifiers in the order they will be presented to the user.
 Each restriction identifier must be unique string.
 For example: com.MyCompany.MyApp.SomeRestrictionIdentifier
 */
@property(nonatomic, readonly, nullable) NSArray<NSString *> *guidedAccessRestrictionIdentifiers;

// Called each time the restriction associated with the identifier changes state.
- (void)guidedAccessRestrictionWithIdentifier:(NSString *)restrictionIdentifier didChangeState:(UIGuidedAccessRestrictionState)newRestrictionState;

// Returns a localized string that describes the restriction associated with the identifier.
- (nullable NSString *)textForGuidedAccessRestrictionWithIdentifier:(NSString *)restrictionIdentifier;

@optional

// Returns a localized string that gives additional detail about the restriction associated with the identifier.
- (nullable NSString *)detailTextForGuidedAccessRestrictionWithIdentifier:(NSString *)restrictionIdentifier;

@end

// Returns the state of the restriction associated with the identifier.
UIKIT_EXTERN UIGuidedAccessRestrictionState UIGuidedAccessRestrictionStateForIdentifier(NSString *restrictionIdentifier) API_AVAILABLE(ios(7.0));

/*
 * Applications that are locked into Guided Access via a Single App Mode profile are granted the ability to configure certain accessibility features,
 * to support kiosk deployments. If your app is locked into Single App Mode, you can use the UIGuidedAccessConfigureAccessibilityFeatures function
 * to configure what accessibility features are enabled.
 */
typedef NS_OPTIONS(NSUInteger, UIGuidedAccessAccessibilityFeature) {
    UIGuidedAccessAccessibilityFeatureVoiceOver        = 1 << 0,
    UIGuidedAccessAccessibilityFeatureZoom             = 1 << 1,
    UIGuidedAccessAccessibilityFeatureAssistiveTouch   = 1 << 2,
    UIGuidedAccessAccessibilityFeatureInvertColors     = 1 << 3,
    UIGuidedAccessAccessibilityFeatureGrayscaleDisplay = 1 << 4,
} API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN void UIGuidedAccessConfigureAccessibilityFeatures(UIGuidedAccessAccessibilityFeature features, BOOL enabled, void (^completion)(BOOL success, NSError *error)) API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(watchos, tvos);

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIGuidedAccess.h>
#endif
