#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIInterface.h>)
//
//  UIInterface.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIColor.h>
#import <UIKit/UIFont.h>

// for UINavigationBar and UIToolBar

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIBarStyle) {
    UIBarStyleDefault          = 0,
    UIBarStyleBlack            = 1,
    
    UIBarStyleBlackOpaque API_DEPRECATED("Use UIBarStyleBlack instead.", ios(2.0, 13.0)) = 1,
    UIBarStyleBlackTranslucent API_DEPRECATED("Use UIBarStyleBlack and set the translucent property to YES instead.", ios(2.0, 13.0)) = 2,
} API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, UIUserInterfaceSizeClass) {
    UIUserInterfaceSizeClassUnspecified = 0,
    UIUserInterfaceSizeClassCompact     = 1,
    UIUserInterfaceSizeClassRegular     = 2,
} API_AVAILABLE(ios(8.0));

typedef NS_ENUM(NSInteger, UIUserInterfaceStyle) {
    UIUserInterfaceStyleUnspecified,
    UIUserInterfaceStyleLight,
    UIUserInterfaceStyleDark,
} API_AVAILABLE(tvos(10.0)) API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIUserInterfaceLayoutDirection) {
    UIUserInterfaceLayoutDirectionLeftToRight,
    UIUserInterfaceLayoutDirectionRightToLeft,
} API_AVAILABLE(ios(5.0));

// These values are only used for the layout direction trait, which informs but does not completely dictate the layout direction of views. To determine the effective layout direction of a view, consult the UIView.effectiveUserInterfaceLayoutDirection property, whose values are members of the UIUserInterfaceLayoutDirection enum.
typedef NS_ENUM(NSInteger, UITraitEnvironmentLayoutDirection) {
    UITraitEnvironmentLayoutDirectionUnspecified = -1,
    UITraitEnvironmentLayoutDirectionLeftToRight = UIUserInterfaceLayoutDirectionLeftToRight,
    UITraitEnvironmentLayoutDirectionRightToLeft = UIUserInterfaceLayoutDirectionRightToLeft,
} API_AVAILABLE(ios(10.0));

typedef NS_ENUM(NSInteger, UIDisplayGamut) {
    UIDisplayGamutUnspecified = -1, // UIKit will not set this anymore, instead a sensible default is chosen based on the device capabilities and settings always
    UIDisplayGamutSRGB,
    UIDisplayGamutP3
} API_AVAILABLE(ios(10.0));

/* The value of the "high contrast" Accessibility setting is available via `UIAccessibilityDarkerSystemColorsEnabled()`,
 * and is also expressed as the UIAccessibilityContrast trait.
 */
typedef NS_ENUM(NSInteger, UIAccessibilityContrast) {
    UIAccessibilityContrastUnspecified = -1,
    UIAccessibilityContrastNormal,
    UIAccessibilityContrastHigh,
} API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);


typedef NS_ENUM(NSInteger, UILegibilityWeight) {
    UILegibilityWeightUnspecified = -1,
    UILegibilityWeightRegular,
    UILegibilityWeightBold
} API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0));

typedef NS_ENUM(NSInteger, UIUserInterfaceLevel) {
    UIUserInterfaceLevelUnspecified = -1,
    UIUserInterfaceLevelBase,
    UIUserInterfaceLevelElevated
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// System colors

@interface UIColor (UIColorSystemColors)

#pragma mark System colors

/* Some colors that are used by system elements and applications.
 * These return named colors whose values may vary between different contexts and releases.
 * Do not make assumptions about the color spaces or actual colors used.
 */
@property (class, nonatomic, readonly) UIColor *systemRedColor          API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *systemGreenColor        API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *systemBlueColor         API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *systemOrangeColor       API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *systemYellowColor       API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *systemPinkColor         API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *systemPurpleColor       API_AVAILABLE(ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *systemTealColor         API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *systemIndigoColor       API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/* Shades of gray. systemGray is the base gray color.
 */
@property (class, nonatomic, readonly) UIColor *systemGrayColor         API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* The numbered variations, systemGray2 through systemGray6, are grays which increasingly
 * trend away from systemGray and in the direction of systemBackgroundColor.
 *
 * In UIUserInterfaceStyleLight: systemGray1 is slightly lighter than systemGray.
 *                               systemGray2 is lighter than that, and so on.
 * In UIUserInterfaceStyleDark:  systemGray1 is slightly darker than systemGray.
 *                               systemGray2 is darker than that, and so on.
 */
@property (class, nonatomic, readonly) UIColor *systemGray2Color        API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
@property (class, nonatomic, readonly) UIColor *systemGray3Color        API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
@property (class, nonatomic, readonly) UIColor *systemGray4Color        API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
@property (class, nonatomic, readonly) UIColor *systemGray5Color        API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
@property (class, nonatomic, readonly) UIColor *systemGray6Color        API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

#pragma mark Foreground colors

/* Foreground colors for static text and related elements.
 */
@property (class, nonatomic, readonly) UIColor *labelColor              API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *secondaryLabelColor     API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *tertiaryLabelColor      API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *quaternaryLabelColor    API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/* Foreground color for standard system links.
 */
@property (class, nonatomic, readonly) UIColor *linkColor               API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/* Foreground color for placeholder text in controls or text fields or text views.
 */
@property (class, nonatomic, readonly) UIColor *placeholderTextColor    API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/* Foreground colors for separators (thin border or divider lines).
 * `separatorColor` may be partially transparent, so it can go on top of any content.
 * `opaqueSeparatorColor` is intended to look similar, but is guaranteed to be opaque, so it will
 * completely cover anything behind it. Depending on the situation, you may need one or the other.
 */
@property (class, nonatomic, readonly) UIColor *separatorColor          API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (class, nonatomic, readonly) UIColor *opaqueSeparatorColor    API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

#pragma mark Background colors

/* We provide two design systems (also known as "stacks") for structuring an iOS app's backgrounds.
 *
 * Each stack has three "levels" of background colors. The first color is intended to be the
 * main background, farthest back. Secondary and tertiary colors are layered on top
 * of the main background, when appropriate.
 *
 * Inside of a discrete piece of UI, choose a stack, then use colors from that stack.
 * We do not recommend mixing and matching background colors between stacks.
 * The foreground colors above are designed to work in both stacks.
 *
 * 1. systemBackground
 *    Use this stack for views with standard table views, and designs which have a white
 *    primary background in light mode.
 */
@property (class, nonatomic, readonly) UIColor *systemBackgroundColor                   API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
@property (class, nonatomic, readonly) UIColor *secondarySystemBackgroundColor          API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
@property (class, nonatomic, readonly) UIColor *tertiarySystemBackgroundColor           API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/* 2. systemGroupedBackground
 *    Use this stack for views with grouped content, such as grouped tables and
 *    platter-based designs. These are like grouped table views, but you may use these
 *    colors in places where a table view wouldn't make sense.
 */
@property (class, nonatomic, readonly) UIColor *systemGroupedBackgroundColor            API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
@property (class, nonatomic, readonly) UIColor *secondarySystemGroupedBackgroundColor   API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);
@property (class, nonatomic, readonly) UIColor *tertiarySystemGroupedBackgroundColor    API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

#pragma mark Fill colors

/* Fill colors for UI elements.
 * These are meant to be used over the background colors, since their alpha component is less than 1.
 *
 * systemFillColor is appropriate for filling thin and small shapes.
 * Example: The track of a slider.
 */
@property (class, nonatomic, readonly) UIColor *systemFillColor                         API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/* secondarySystemFillColor is appropriate for filling medium-size shapes.
 * Example: The background of a switch.
 */
@property (class, nonatomic, readonly) UIColor *secondarySystemFillColor                API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/* tertiarySystemFillColor is appropriate for filling large shapes.
 * Examples: Input fields, search bars, buttons.
 */
@property (class, nonatomic, readonly) UIColor *tertiarySystemFillColor                 API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/* quaternarySystemFillColor is appropriate for filling large areas containing complex content.
 * Example: Expanded table cells.
 */
@property (class, nonatomic, readonly) UIColor *quaternarySystemFillColor               API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

#pragma mark Other colors

/* lightTextColor is always light, and darkTextColor is always dark, regardless of the current UIUserInterfaceStyle.
 * When possible, we recommend using `labelColor` and its variants, instead.
 */
@property(class, nonatomic, readonly) UIColor *lightTextColor API_UNAVAILABLE(tvos);    // for a dark background
@property(class, nonatomic, readonly) UIColor *darkTextColor API_UNAVAILABLE(tvos);     // for a light background

/* groupTableViewBackgroundColor is now the same as systemGroupedBackgroundColor.
 */
@property(class, nonatomic, readonly) UIColor *groupTableViewBackgroundColor API_DEPRECATED_WITH_REPLACEMENT("systemGroupedBackgroundColor", ios(2.0, 13.0), tvos(13.0, 13.0));

@property(class, nonatomic, readonly) UIColor *viewFlipsideBackgroundColor API_DEPRECATED("", ios(2.0, 7.0)) API_UNAVAILABLE(tvos);
@property(class, nonatomic, readonly) UIColor *scrollViewTexturedBackgroundColor API_DEPRECATED("", ios(3.2, 7.0)) API_UNAVAILABLE(tvos);
@property(class, nonatomic, readonly) UIColor *underPageBackgroundColor API_DEPRECATED("", ios(5.0, 7.0)) API_UNAVAILABLE(tvos);

@end


// System fonts

@interface UIFont (UIFontSystemFonts)
@property(class, nonatomic, readonly) CGFloat labelFontSize API_UNAVAILABLE(tvos);
@property(class, nonatomic, readonly) CGFloat buttonFontSize API_UNAVAILABLE(tvos);
@property(class, nonatomic, readonly) CGFloat smallSystemFontSize API_UNAVAILABLE(tvos);
@property(class, nonatomic, readonly) CGFloat systemFontSize API_UNAVAILABLE(tvos);
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIInterface.h>
#endif
