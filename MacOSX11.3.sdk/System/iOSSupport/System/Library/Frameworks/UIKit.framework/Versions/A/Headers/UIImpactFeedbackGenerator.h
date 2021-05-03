#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIImpactFeedbackGenerator.h>)
//
//  UIImpactFeedbackGenerator.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIFeedbackGenerator.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIImpactFeedbackStyle) {
    UIImpactFeedbackStyleLight,
    UIImpactFeedbackStyleMedium,
    UIImpactFeedbackStyleHeavy,
    UIImpactFeedbackStyleSoft     API_AVAILABLE(ios(13.0)),
    UIImpactFeedbackStyleRigid    API_AVAILABLE(ios(13.0))
};

// UIImpactFeedbackGenerator is used to give user feedback when an impact between UI elements occurs
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(tvos, watchos) @interface UIImpactFeedbackGenerator : UIFeedbackGenerator

- (instancetype)initWithStyle:(UIImpactFeedbackStyle)style;

/// call when your UI element impacts something else
- (void)impactOccurred;

/// call when your UI element impacts something else with a specific intensity [0.0, 1.0]
- (void)impactOccurredWithIntensity:(CGFloat)intensity API_AVAILABLE(ios(13.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIImpactFeedbackGenerator.h>
#endif
