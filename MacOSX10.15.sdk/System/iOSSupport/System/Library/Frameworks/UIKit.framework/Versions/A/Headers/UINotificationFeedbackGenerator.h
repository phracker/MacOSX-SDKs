#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UINotificationFeedbackGenerator.h>)
//
//  UINotificationFeedbackGenerator.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIFeedbackGenerator.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UINotificationFeedbackType) {
    UINotificationFeedbackTypeSuccess,
    UINotificationFeedbackTypeWarning,
    UINotificationFeedbackTypeError
};

// UINotificationFeedbackGenerator is used to give user feedback when an notification is displayed
UIKIT_CLASS_AVAILABLE_IOS_ONLY(10_0) @interface UINotificationFeedbackGenerator : UIFeedbackGenerator

/// call when a notification is displayed, passing the corresponding type
- (void)notificationOccurred:(UINotificationFeedbackType)notificationType;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UINotificationFeedbackGenerator.h>
#endif
