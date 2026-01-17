#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPointerLockState.h>)
//
//  UIPointerLockState.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIScene.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos)
@interface UIPointerLockState : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @abstract The status of the pointer lock for this scene as determined by the system.
 * The preferred pointer lock value specified by a view controller is only a request, which may or may not be honored.
 * This property is key-value observable and UIPointerLockState.didChangeNotification is posted when it changes.
 */
@property (nonatomic, readonly, getter=isLocked) BOOL locked;

@end

@interface UIScene (PointerLockState)

@property (nonatomic, readonly, nullable) UIPointerLockState *pointerLockState API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

@end

/*!
 * @abstract A notification that is posted when UIPointerLockState.locked changes values for a scene.
 * It contains the related UIScene in the user info dictionary of the notification.
 */
UIKIT_EXTERN NSNotificationName const UIPointerLockStateDidChangeNotification NS_SWIFT_NAME(UIPointerLockState.didChangeNotification) API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);
UIKIT_EXTERN NSString *const UIPointerLockStateSceneUserInfoKey NS_SWIFT_NAME(UIPointerLockState.sceneUserInfoKey)API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPointerLockState.h>
#endif
