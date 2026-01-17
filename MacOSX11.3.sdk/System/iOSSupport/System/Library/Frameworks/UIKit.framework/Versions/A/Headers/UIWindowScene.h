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

NS_ASSUME_NONNULL_BEGIN

@class UIScreen, UIWindow, UIWindowSceneDelegate, UISceneDestructionRequestOptions, CKShareMetadata, UISceneSizeRestrictions;

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UIWindowScene : UIScene

#pragma mark Geometry
@property (nonatomic, readonly) UIScreen *screen;
@property (nonatomic, readonly) UIInterfaceOrientation interfaceOrientation API_UNAVAILABLE(tvos);
@property (nonatomic, readonly) id<UICoordinateSpace> coordinateSpace;
@property (nonatomic, readonly) UITraitCollection *traitCollection;

// Restrictions which the system should use when resizing the scene. This property will be NULL on platforms which don't support scene resize, else a mutable object is returned which the client may customize.
@property (nonatomic, readonly, nullable) UISceneSizeRestrictions *sizeRestrictions API_AVAILABLE(ios(13.0));

#pragma mark Window management
// The array of all windows associated with this UIWindowScene
@property (nonatomic, readonly) NSArray<UIWindow *> *windows;

@end

#pragma mark - UIWindowSceneDelegate
API_AVAILABLE(ios(13.0)) @protocol UIWindowSceneDelegate <UISceneDelegate>
@optional
@property (nullable, nonatomic, strong) UIWindow *window;

- (void)windowScene:(UIWindowScene *)windowScene didUpdateCoordinateSpace:(id<UICoordinateSpace>)previousCoordinateSpace interfaceOrientation:(UIInterfaceOrientation)previousInterfaceOrientation traitCollection:(UITraitCollection *)previousTraitCollection API_UNAVAILABLE(tvos);

#pragma mark - System Integration
// Called when the user activates your application by selecting a shortcut on the home screen,
// and the window scene is already connected.
- (void)windowScene:(UIWindowScene *)windowScene performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem completionHandler:(void(^)(BOOL succeeded))completionHandler API_UNAVAILABLE(tvos);

// Called after the user indicates they want to accept a CloudKit sharing invitation in your application
// and the window scene is already connected.
// You should use the CKShareMetadata object's shareURL and containerIdentifier to schedule a CKAcceptSharesOperation, then start using
// the resulting CKShare and its associated record(s), which will appear in the CKContainer's shared database in a zone matching that of the record's owner.
- (void)windowScene:(UIWindowScene *)windowScene userDidAcceptCloudKitShareWithMetadata:(CKShareMetadata *)cloudKitShareMetadata;
@end

#pragma mark - Session Roles
// A session role which defines a typical interactive application on a device's main display
UIKIT_EXTERN UISceneSessionRole const UIWindowSceneSessionRoleApplication API_AVAILABLE(ios(13.0));

// A session role which defines an interface for a non-main external display
UIKIT_EXTERN UISceneSessionRole const UIWindowSceneSessionRoleExternalDisplay API_AVAILABLE(ios(13.0));

#pragma mark - UIWindowSceneDismissalAnimation
typedef NS_ENUM(NSInteger, UIWindowSceneDismissalAnimation) {
    UIWindowSceneDismissalAnimationStandard = 1,
    UIWindowSceneDismissalAnimationCommit = 2,
    UIWindowSceneDismissalAnimationDecline = 3
} API_AVAILABLE(ios(13.0));

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UIWindowSceneDestructionRequestOptions : UISceneDestructionRequestOptions
@property (nonatomic, readwrite) UIWindowSceneDismissalAnimation windowDismissalAnimation;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UISceneSizeRestrictions : NSObject

// Clients should never make one of these directly. See -[UIWindowScene sizeRestrictions].
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, assign) CGSize minimumSize;
@property (nonatomic, assign) CGSize maximumSize;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIWindowScene.h>
#endif
