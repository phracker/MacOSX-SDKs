#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneWindowingControlStyle.h>)
//
//  UISceneWindowingControlStyle.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Describes the placement and style of the system windowing controls for a scene
UIKIT_EXTERN
NS_SWIFT_SENDABLE
NS_SWIFT_NAME(UIWindowScene.WindowingControlStyle)
API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface UISceneWindowingControlStyle : NSObject

/// Windowing controls will use the default system style
@property (class, nonatomic, readonly) UISceneWindowingControlStyle *automaticStyle API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Windowing controls will appear as part of the scene's content
@property (class, nonatomic, readonly) UISceneWindowingControlStyle *unifiedStyle API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Windowing controls will occupy as little of the scene's space as possible
@property (class, nonatomic, readonly) UISceneWindowingControlStyle *minimalStyle API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneWindowingControlStyle.h>
#endif
