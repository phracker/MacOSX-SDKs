#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UINotificationFeedbackGenerator.h>)
//
//  UINotificationFeedbackGenerator.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIFeedbackGenerator.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UINotificationFeedbackType) {
    UINotificationFeedbackTypeSuccess,
    UINotificationFeedbackTypeWarning,
    UINotificationFeedbackTypeError
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(visionos, tvos) API_UNAVAILABLE(watchos);

// UINotificationFeedbackGenerator is used to give user feedback when an notification is displayed
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(visionos, tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UINotificationFeedbackGenerator : UIFeedbackGenerator

/// call when a notification is displayed, passing the corresponding type
- (void)notificationOccurred:(UINotificationFeedbackType)notificationType;
- (void)notificationOccurred:(UINotificationFeedbackType)notificationType atLocation:(CGPoint)location API_AVAILABLE(ios(17.5)) API_UNAVAILABLE(visionos) NS_SWIFT_NAME(notificationOccurred(_:at:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UINotificationFeedbackGenerator.h>
#endif
