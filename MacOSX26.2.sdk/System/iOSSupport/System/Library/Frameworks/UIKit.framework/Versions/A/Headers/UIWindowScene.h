#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowScene.h>)
//
//  UIWindowScene.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIScene.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UISceneOptions.h>
#import <UIKit/UISceneSizeRestrictions.h>
#import <UIKit/UISceneWindowingControlStyle.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIScreen, UIWindow, UIWindowSceneDelegate, UISceneDestructionRequestOptions, CKShareMetadata, UISceneSizeRestrictions, UISceneWindowingBehaviors, UIWindowSceneGeometry, UIWindowSceneGeometryPreferences;
@protocol UIActivityItemsConfigurationProviding;

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIWindowScene : UIScene

#pragma mark Geometry
@property (nonatomic, readonly) UIScreen *screen API_UNAVAILABLE(visionos);
@property (nonatomic, readonly) UIInterfaceOrientation interfaceOrientation API_DEPRECATED("Use effectiveGeometry.interfaceOrientation instead.", ios(13.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(tvos);
@property (nonatomic, readonly) id<UICoordinateSpace> coordinateSpace API_DEPRECATED("Use effectiveGeometry.coordinateSpace instead.", ios(13.0, 26.0), tvos(13.0, 26.0), visionos(1.0, 26.0));
@property (nonatomic, readonly) UITraitCollection *traitCollection;

// Request an update to the window scene's geometry in system space.
- (void)requestGeometryUpdateWithPreferences:(UIWindowSceneGeometryPreferences *)geometryPreferences errorHandler:(nullable void (^)(NSError *error))errorHandler API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

// Provides the current resolved values for the window scene's geometry in system space.
@property (nonatomic, readonly) UIWindowSceneGeometry *effectiveGeometry API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/// Preferences the system should evaluate when resizing the scene. If non `nil`, returns a mutable instance that the client may customize.
/// - Note: This property will be `nil` on platforms that don't support scene resizing.
@property (nonatomic, readonly, nullable) UISceneSizeRestrictions *sizeRestrictions API_AVAILABLE(ios(13.0));

#pragma mark Window management
// The array of all windows associated with this UIWindowScene
@property (nonatomic, readonly) NSArray<UIWindow *> *windows;

// The key window for this UIWindowScene
@property (nonatomic, readonly, strong, nullable) UIWindow *keyWindow API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

/// An optional object used as a source of scene-level activity items configuration
///
/// If this property returns @c nil, the @c activityItemsConfiguration property of the most-presented view controller
/// of the scene's key window will be used for scene-level sharing and activities.
@property (nonatomic, nullable, weak) id<UIActivityItemsConfigurationProviding> activityItemsConfigurationSource API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

/// Additional window behaviors which may be platform specific. This property will be nil on unsupported platforms, otherwise will provide a mutable object for window behavior customization.
@property (nonatomic, readonly, nullable) UISceneWindowingBehaviors *windowingBehaviors API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

@property (nonatomic, readonly, getter=isFullScreen) BOOL fullScreen API_AVAILABLE(macCatalyst(16.0)) API_UNAVAILABLE(watchos);
@end

API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface UIWindowScene () <UITraitEnvironment, UITraitChangeObservable>
@property (nonatomic, readonly) id<UITraitOverrides> traitOverrides API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
@end

#pragma mark - UIWindowSceneDelegate
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIWindowSceneDelegate <UISceneDelegate>
@optional
@property (nullable, nonatomic, strong) UIWindow *window;

/// Called when the coordinate space, interface orientation, or trait collection of a `UIWindowScene` changes.
///
/// Always called when a UIWindowScene moves between screens.
- (void)windowScene:(UIWindowScene *)windowScene didUpdateCoordinateSpace:(id<UICoordinateSpace>)previousCoordinateSpace interfaceOrientation:(UIInterfaceOrientation)previousInterfaceOrientation traitCollection:(UITraitCollection *)previousTraitCollection API_DEPRECATED("Use windowScene(_: didUpdateEffectiveGeometry:) to be notified of the scene's geometry changes, or use traits whose values are inherited from the scene via the traitCollection of views and view controllers instead.", ios(13.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(tvos);

/// Called when the window scene's effective geometry has changed.
///
/// Always called when a `UIWindowScene` moves between screens.
- (void)windowScene:(UIWindowScene *)windowScene didUpdateEffectiveGeometry:(UIWindowSceneGeometry *)previousEffectiveGeometry API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

#pragma mark - System Integration
// Called when the user activates your application by selecting a shortcut on the home screen,
// and the window scene is already connected.
- (void)windowScene:(UIWindowScene *)windowScene performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem completionHandler:(void(^)(BOOL succeeded))completionHandler API_UNAVAILABLE(tvos);

// Called after the user indicates they want to accept a CloudKit sharing invitation in your application
// and the window scene is already connected.
// You should use the CKShareMetadata object's shareURL and containerIdentifier to schedule a CKAcceptSharesOperation, then start using
// the resulting CKShare and its associated record(s), which will appear in the CKContainer's shared database in a zone matching that of the record's owner.
- (void)windowScene:(UIWindowScene *)windowScene userDidAcceptCloudKitShareWithMetadata:(CKShareMetadata *)cloudKitShareMetadata;

/// Called by the system to determine the windowing control style for the provided scene.
/// `automaticStyle` will be used if this method is not implemented.
- (UISceneWindowingControlStyle *)preferredWindowingControlStyleForScene:(UIWindowScene *)windowScene API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

@end

#pragma mark - Session Roles
// A session role which defines a typical interactive application
UIKIT_EXTERN UISceneSessionRole const UIWindowSceneSessionRoleApplication API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

// A session role which defines an interface for a non-interactive external display
UIKIT_EXTERN UISceneSessionRole const UIWindowSceneSessionRoleExternalDisplayNonInteractive API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);
UIKIT_EXTERN UISceneSessionRole const UIWindowSceneSessionRoleExternalDisplay API_DEPRECATED_WITH_REPLACEMENT("UIWindowSceneSessionRoleExternalDisplayNonInteractive", ios(13.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

// A session role which defines a 3D volumetric application
UIKIT_EXTERN UISceneSessionRole const UIWindowSceneSessionRoleVolumetricApplication API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, macos, watchos);

// A session role which defines an application for Assistive Access
UIKIT_EXTERN UISceneSessionRole const UIWindowSceneSessionRoleAssistiveAccessApplication API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

#pragma mark - UIWindowSceneDismissalAnimation
typedef NS_ENUM(NSInteger, UIWindowSceneDismissalAnimation) {
    UIWindowSceneDismissalAnimationStandard = 1,
    UIWindowSceneDismissalAnimationCommit = 2,
    UIWindowSceneDismissalAnimationDecline = 3
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIWindowSceneDestructionRequestOptions : UISceneDestructionRequestOptions
@property (nonatomic, readwrite) UIWindowSceneDismissalAnimation windowDismissalAnimation;
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowScene.h>
#endif
