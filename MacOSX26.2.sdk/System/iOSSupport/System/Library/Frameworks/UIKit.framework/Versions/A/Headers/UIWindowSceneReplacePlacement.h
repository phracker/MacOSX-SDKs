#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneReplacePlacement.h>)
//
//  UIWindowSceneReplacePlacement.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIWindowScenePlacement.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UISceneSession;

/// Background the scene of the provided scene session and replace it with the
/// activated scene. Closing the activated scene will result in the replaced
/// scene reappearing. The activated scene will be center aligned with the
/// replaced scene. There is no impact on the sizing of either scene.
UIKIT_EXTERN API_DEPRECATED("UIWindowSceneReplacePlacement has been replaced with UIWindowScenePushPlacement", visionos(2.0, 2.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst) NS_REFINED_FOR_SWIFT
@interface UIWindowSceneReplacePlacement : UIWindowScenePlacement

/// Creates the placement that targets the given `sceneSession`
/// - Parameter sceneSession: The scene session of the window scene to replace.
+ (instancetype)placementToReplaceSceneSession:(UISceneSession *)sceneSession;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneReplacePlacement.h>
#endif
