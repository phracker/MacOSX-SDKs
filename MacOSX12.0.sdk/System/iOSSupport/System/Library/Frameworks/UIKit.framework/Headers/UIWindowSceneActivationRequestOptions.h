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

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0))
typedef NS_ENUM(NSUInteger, UIWindowScenePresentationStyle) {
    /// System determines most appropriate style
    UIWindowScenePresentationStyleAutomatic,

    /// The default style of the system
    UIWindowScenePresentationStyleStandard,

    /// Present prominently above others in the current space
    UIWindowScenePresentationStyleProminent
} NS_SWIFT_NAME(UIWindowScene.PresentationStyle);


UIKIT_EXTERN API_AVAILABLE(ios(15.0))
@interface UIWindowSceneActivationRequestOptions : UISceneActivationRequestOptions

/// Request a specific presentation style. Defaults to @c UIWindowScenePresentationStyleAutomatic .
@property (nonatomic, readwrite) UIWindowScenePresentationStyle preferredPresentationStyle;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIWindowSceneActivationRequestOptions.h>
#endif
