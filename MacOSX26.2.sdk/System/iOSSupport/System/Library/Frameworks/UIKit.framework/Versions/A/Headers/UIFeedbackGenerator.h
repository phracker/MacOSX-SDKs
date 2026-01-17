#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFeedbackGenerator.h>)
//
//  UIFeedbackGenerator.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInteraction.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// UIFeedbackGenerator is an abstract class that should not be used directly
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(visionos, tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIFeedbackGenerator : NSObject

/// initalize the generator with a view to attach it to the provided view as an interaction.
+ (instancetype)feedbackGeneratorForView:(UIView *)view NS_SWIFT_NAME(init(view:)) API_AVAILABLE(ios(17.5)) API_UNAVAILABLE(visionos);

- (instancetype)init API_DEPRECATED_WITH_REPLACEMENT("+feedbackGeneratorForView:", ios(10.0, API_TO_BE_DEPRECATED));

/// informs self that it will likely receive events soon, so that it can ensure minimal latency for any feedback generated
/// safe to call more than once before the generator receives an event, if events are still imminently possible
- (void)prepare;

@end

UIKIT_EXTERN API_AVAILABLE(ios(17.5)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIFeedbackGenerator () <UIInteraction>
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFeedbackGenerator.h>
#endif
