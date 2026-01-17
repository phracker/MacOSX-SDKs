#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneDestructionCondition.h>)
//
//  UISceneDestructionCondition.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Specifies when UIKit destroys the current scene.
UIKIT_EXTERN API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR NS_REFINED_FOR_SWIFT
@interface UISceneDestructionCondition : NSObject <NSCopying>

/// The scene should be destroyed when dismissed by the user.
/// For example, swiping home on iOS, or tapping x on visionOS.
+ (instancetype)userInitiatedDismissal API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// The scene should be destroyed when disconnected by the system.
/// For example, terminating the process, or rebooting the device.
+ (instancetype)systemDisconnection API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(ios, watchos, tvos);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneDestructionCondition.h>
#endif
