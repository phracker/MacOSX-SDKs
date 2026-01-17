#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneActivationRequestOptions.h>)
//
//  UIWindowSceneActivationRequestOptions.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

#import <Foundation/Foundation.h>
#import <UIKit/UISceneOptions.h>
#import <UIKit/UIWindowScenePlacement.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_DEPRECATED("Please use an appropriate UIWindowScenePlacement", ios(15.0, 17.0), visionos(1.0, 1.0))
typedef NS_ENUM(NSUInteger, UIWindowScenePresentationStyle) {
    UIWindowScenePresentationStyleAutomatic,
    UIWindowScenePresentationStyleStandard,
    UIWindowScenePresentationStyleProminent
} NS_SWIFT_NAME(UIWindowScene.PresentationStyle) API_UNAVAILABLE(watchos);


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos)
@interface UIWindowSceneActivationRequestOptions : UISceneActivationRequestOptions

@property (nonatomic, readwrite) UIWindowScenePresentationStyle preferredPresentationStyle API_DEPRECATED("Place use .placement with an appropriate UIWindowScenePlacement.", ios(15.0, 17.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

/// The preferred placement of the window scene to be activated. Scene placements influence how the
/// system positions the activated scene. A `nil` value indicates that the system should determine
/// the most appropriate placement to use.
@property (nonatomic, nullable, copy) UIWindowScenePlacement *placement API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneActivationRequestOptions.h>
#endif
