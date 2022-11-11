#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBarCommon.h>)
//
//  UIBarCommon.h
//  UIKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIBarMetrics) {
    UIBarMetricsDefault,
    UIBarMetricsCompact,
    UIBarMetricsDefaultPrompt = 101, // Applicable only in bars with the prompt property, such as UINavigationBar and UISearchBar
    UIBarMetricsCompactPrompt,

    UIBarMetricsLandscapePhone API_DEPRECATED_WITH_REPLACEMENT("UIBarMetricsCompact", ios(5.0, 8.0)) = UIBarMetricsCompact,
    UIBarMetricsLandscapePhonePrompt API_DEPRECATED_WITH_REPLACEMENT("UIBarMetricsCompactPrompt", ios(7.0, 8.0)) = UIBarMetricsCompactPrompt,
};

typedef NS_ENUM(NSInteger, UIBarPosition) {
    UIBarPositionAny = 0,
    UIBarPositionBottom = 1, // The bar is at the bottom of its local context, and directional decoration draws accordingly (e.g., shadow above the bar).
    UIBarPositionTop = 2, // The bar is at the top of its local context, and directional decoration draws accordingly (e.g., shadow below the bar)
    UIBarPositionTopAttached = 3, // The bar is at the top of the screen (as well as its local context), and its background extends upward—currently only enough for the status bar.
} API_AVAILABLE(ios(7.0));

#define UIToolbarPosition UIBarPosition
#define UIToolbarPositionAny UIBarPositionAny
#define UIToolbarPositionBottom UIBarPositionBottom
#define UIToolbarPositionTop UIBarPositionTop


NS_SWIFT_UI_ACTOR
@protocol UIBarPositioning <NSObject> // UINavigationBar, UIToolbar, and UISearchBar conform to this
@property(nonatomic,readonly) UIBarPosition barPosition;
@end

NS_SWIFT_UI_ACTOR
@protocol UIBarPositioningDelegate <NSObject> // UINavigationBarDelegate, UIToolbarDelegate, and UISearchBarDelegate all extend from this
@optional
/* Implement this method on your manual bar delegate when not managed by a UIKit controller.
 UINavigationBar and UISearchBar default to UIBarPositionTop, UIToolbar defaults to UIBarPositionBottom.
 This message will be sent when the bar moves to a window.
 */
- (UIBarPosition)positionForBar:(id <UIBarPositioning>)bar;
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIBarCommon.h>
#endif
