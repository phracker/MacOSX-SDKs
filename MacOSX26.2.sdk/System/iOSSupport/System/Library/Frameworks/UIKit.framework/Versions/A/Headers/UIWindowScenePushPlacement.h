#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowScenePushPlacement.h>)
//
//  UIWindowScenePushPlacement.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIWindowScenePlacement.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UISceneSession;

/// Background the scene of the provided scene session and present the
/// activated scene in its place.
///
/// The provided scene session will be backgrounded. The activated scene will
/// be center aligned with the backgrounded scene. Closing the activated window
/// will result in the backgrounded scene reappearing.
///
/// Targeting a scene session that is currently pushed will result in an error
/// being delivered to the `errorHandler` of
/// ``-[UIApplication activateSceneSessionForRequest: errorHandler:]``.
UIKIT_EXTERN API_AVAILABLE(visionos(2.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@interface UIWindowScenePushPlacement : UIWindowScenePlacement

/// Creates the placement that will target the given `sceneSession`.
/// - Parameter targetSceneSession: The scene session of the window scene that will be backgrounded.
+ (instancetype)placementTargetingSceneSession:(UISceneSession *)targetSceneSession;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowScenePushPlacement.h>
#endif
