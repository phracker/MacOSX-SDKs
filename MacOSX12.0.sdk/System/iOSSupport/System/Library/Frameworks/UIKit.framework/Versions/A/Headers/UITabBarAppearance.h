#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITabBarAppearance.h>)
//
//  UITabBarAppearance.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIBarAppearance.h>
#import <UIKit/UITabBar.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) NS_SWIFT_UI_ACTOR
@interface UITabBarItemStateAppearance : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Text attributes to be used for rendering title text. If the font or color are unspecified, appropriate defaults are supplied.
@property (nonatomic, readwrite, copy) NSDictionary<NSAttributedStringKey, id> *titleTextAttributes;

/// An offset to apply to the UITabBarItem's title position
@property (nonatomic, readwrite, assign) UIOffset titlePositionAdjustment;

/// The color to use for item icons. If not specified, a suitable color will be derived.
@property (nonatomic, readwrite, copy, nullable) UIColor *iconColor;

/// An offset to apply to the badge's position
@property (nonatomic, readwrite, assign) UIOffset badgePositionAdjustment;

/// The color to use for the badge background
@property (nonatomic, readwrite, copy, nullable) UIColor *badgeBackgroundColor;

/// Text attributes to be used for rendering badge text. If the font and color are unspecified, appropriate defaults are supplied.
@property (nonatomic, readwrite, copy) NSDictionary<NSAttributedStringKey, id> *badgeTextAttributes;

/// An offset to apply to the badge's title position
@property (nonatomic, readwrite, assign) UIOffset badgeTitlePositionAdjustment;

@end

typedef NS_ENUM(NSInteger, UITabBarItemAppearanceStyle) {
    UITabBarItemAppearanceStyleStacked,
    UITabBarItemAppearanceStyleInline,
    UITabBarItemAppearanceStyleCompactInline,
};

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) NS_SWIFT_UI_ACTOR
@interface UITabBarItemAppearance : NSObject<NSCopying, NSSecureCoding>

/// Construct an appearance with default values for the stacked layout.
- (instancetype)init;

/// Construct an appearance with default values for the given layout.
- (instancetype)initWithStyle:(UITabBarItemAppearanceStyle)style NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)copy;

/// Reset this appearance to that of the given layout.
- (void)configureWithDefaultForStyle:(UITabBarItemAppearanceStyle)style;

/// The appearance when the tab bar item is in the normal state
@property (nonatomic, readonly, strong) UITabBarItemStateAppearance *normal;

/// The appearance when the tab bar item is in the selected state
@property (nonatomic, readonly, strong) UITabBarItemStateAppearance *selected;

/// The appearance when the tab bar item is in the disabled state
@property (nonatomic, readonly, strong) UITabBarItemStateAppearance *disabled;

/// The appearance when the tab bar item is in the focused state
@property (nonatomic, readonly, strong) UITabBarItemStateAppearance *focused;

@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) NS_SWIFT_UI_ACTOR
@interface UITabBarAppearance : UIBarAppearance

/// The appearance for the stacked tab bar item layout
@property (nonatomic, readwrite, copy) UITabBarItemAppearance *stackedLayoutAppearance;

/// The appearance for the inline tab bar item layout
@property (nonatomic, readwrite, copy) UITabBarItemAppearance *inlineLayoutAppearance;

/// The appearance for the compact inline tab bar item layout
@property (nonatomic, readwrite, copy) UITabBarItemAppearance *compactInlineLayoutAppearance;

/// A color to use for the selectionIndicator, its specific behavior depends on the value of selectionIndicatorImage. If selectionIndicatorImage is nil, then the selectionIndicatorTintColor is used to color the UITabBar's default selection indicator; a nil or clearColor selectionIndicatorTintColor will result in no indicator. If selectionIndicatorImage is a template image, then the selectionIndicatorTintColor is used to tint the image; a nil or clearColor selectionIndicatorTintColor will also result in no indicator. If the selectionIndicatorImage is not a template image, then it will be rendered without respect to the value of selectionIndicatorTintColor.
@property (nonatomic, readwrite, copy, nullable) UIColor *selectionIndicatorTintColor;
/// An image that is rendered behind the selected UITabBarItem and above the tab bar's background. Modified by selectionIndicatorTintColor when appropriate.
@property (nonatomic, readwrite, strong, nullable) UIImage *selectionIndicatorImage;

/// Determines how items in the tab bar lay out in the stacked item layout
@property (nonatomic, readwrite, assign) UITabBarItemPositioning stackedItemPositioning;
@property (nonatomic, readwrite, assign) CGFloat stackedItemWidth;
@property (nonatomic, readwrite, assign) CGFloat stackedItemSpacing;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITabBarAppearance.h>
#endif
