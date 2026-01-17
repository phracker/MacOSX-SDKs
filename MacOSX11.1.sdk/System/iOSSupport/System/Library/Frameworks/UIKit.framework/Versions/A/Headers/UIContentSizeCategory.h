#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentSizeCategory.h>)
//
//  UIContentSizeCategory.h
//  UIKit
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * UIContentSizeCategory NS_TYPED_ENUM API_AVAILABLE(ios(7.0));

// Content size category constants

UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryUnspecified API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryExtraSmall API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategorySmall API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryMedium API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryLarge API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryExtraLarge API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryExtraExtraLarge API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryExtraExtraExtraLarge API_AVAILABLE(ios(7.0));

// Accessibility sizes
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryAccessibilityMedium API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryAccessibilityLarge API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryAccessibilityExtraLarge API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryAccessibilityExtraExtraLarge API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIContentSizeCategory const UIContentSizeCategoryAccessibilityExtraExtraExtraLarge API_AVAILABLE(ios(7.0));

// Notification is emitted when the user has changed the preferredContentSizeCategory for the system
UIKIT_EXTERN NSNotificationName const UIContentSizeCategoryDidChangeNotification API_AVAILABLE(ios(7.0)); // userInfo dictionary will contain new value for UIContentSizeCategoryNewValueKey
UIKIT_EXTERN NSString *const UIContentSizeCategoryNewValueKey API_AVAILABLE(ios(7.0)); // NSString instance with new content size category in userInfo

UIKIT_EXTERN BOOL UIContentSizeCategoryIsAccessibilityCategory(UIContentSizeCategory category) API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0)) NS_REFINED_FOR_SWIFT;
UIKIT_EXTERN NSComparisonResult UIContentSizeCategoryCompareToCategory(UIContentSizeCategory lhs, UIContentSizeCategory rhs) API_AVAILABLE(ios(11.0),tvos(11.0),watchos(4.0)) NS_REFINED_FOR_SWIFT;

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIContentSizeCategory.h>
#endif
