#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneProminentPlacement.h>)
//
//  UIWindowSceneProminentPlacement.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIWindowScenePlacement.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos)
/// Positions a window scene more prominently than others in the current space.
@interface UIWindowSceneProminentPlacement : UIWindowScenePlacement

/// Creates a prominent placement.
+ (instancetype)prominentPlacement;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneProminentPlacement.h>
#endif
