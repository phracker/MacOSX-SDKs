#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneSystemProtectionManager.h>)
//
//  UISceneSystemProtectionManager.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UIScene.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A notification posted when the system protection attributes of a scene change. The object of
/// the notification is the scene whose protection attributes changed.
UIKIT_EXTERN NSNotificationName const UISceneSystemProtectionDidChangeNotification API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NONISOLATED NS_SWIFT_NAME(UIScene.systemProtectionDidChangeNotification);

UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR NS_SWIFT_NAME(UIScene.SystemProtectionManager)
@interface UISceneSystemProtectionManager : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// \c YES if the system requires requires device owner authentication challenges to reveal the
/// content of the scene associated with this manager, else \c NO . Note in particular that this
/// is \em not the instantaneous state of whether any system-provided shield is covering the UI at
/// the moment, but whether protection is enabled in general.
@property (getter=isUserAuthenticationEnabled, readonly) BOOL userAuthenticationEnabled;

@end

UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos)
@interface UIScene (SystemProtection)

@property (nonatomic, readonly, nullable) UISceneSystemProtectionManager *systemProtectionManager;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneSystemProtectionManager.h>
#endif
