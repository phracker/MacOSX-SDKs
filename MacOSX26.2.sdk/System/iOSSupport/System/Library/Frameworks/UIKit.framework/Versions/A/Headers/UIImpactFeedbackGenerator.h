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

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIImpactFeedbackStyle) {
    UIImpactFeedbackStyleLight,
    UIImpactFeedbackStyleMedium,
    UIImpactFeedbackStyleHeavy,
    UIImpactFeedbackStyleSoft     API_AVAILABLE(ios(13.0)),
    UIImpactFeedbackStyleRigid    API_AVAILABLE(ios(13.0)),
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(visionos, tvos) API_UNAVAILABLE(watchos);

// UIImpactFeedbackGenerator is used to give user feedback when an impact between UI elements occurs
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(visionos, tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIImpactFeedbackGenerator : UIFeedbackGenerator

/// set a style on the feedback generator and attach it to the provided view as an interaction.
+ (instancetype)feedbackGeneratorWithStyle:(UIImpactFeedbackStyle)style forView:(UIView *)view API_AVAILABLE(ios(17.5)) API_UNAVAILABLE(visionos) NS_SWIFT_NAME(init(style:view:));

/// call when your UI element impacts something else
- (void)impactOccurred;
- (void)impactOccurredAtLocation:(CGPoint)location API_AVAILABLE(ios(17.5)) API_UNAVAILABLE(visionos) NS_SWIFT_NAME(impactOccurred(at:));

/// call when your UI element impacts something else with a specific intensity [0.0, 1.0]
- (void)impactOccurredWithIntensity:(CGFloat)intensity API_AVAILABLE(ios(13.0));
- (void)impactOccurredWithIntensity:(CGFloat)intensity atLocation:(CGPoint)location API_AVAILABLE(ios(17.5)) API_UNAVAILABLE(visionos) NS_SWIFT_NAME(impactOccurred(intensity:at:));

- (instancetype)initWithStyle:(UIImpactFeedbackStyle)style API_DEPRECATED_WITH_REPLACEMENT("+feedbackGeneratorWithStyle:forView:", ios(10.0, API_TO_BE_DEPRECATED));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIImpactFeedbackGenerator.h>
#endif
