#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITabBar.h>)
//
//  UITabBar.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIControl.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UITabBarItemPositioning) {
    UITabBarItemPositioningAutomatic,
    UITabBarItemPositioningFill,
    UITabBarItemPositioningCentered,
} API_AVAILABLE(ios(7.0));

@class UITabBarItem;
@class UIImageView;
@class UITabBarAppearance;
@protocol UITabBarDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UITabBar : UIView

@property(nullable, nonatomic, weak) id<UITabBarDelegate> delegate;     // weak reference. default is nil
@property(nullable, nonatomic, copy) NSArray<UITabBarItem *> *items;        // get/set visible UITabBarItems. default is nil. changes not animated. shown in order
@property(nullable, nonatomic, weak) UITabBarItem *selectedItem; // will show feedback based on mode. default is nil

- (void)setItems:(nullable NSArray<UITabBarItem *> *)items animated:(BOOL)animated;   // will fade in or out or reorder and adjust spacing

// Reorder items. This will display a sheet with all the items listed, allow the user to change/reorder items and shows a 'Done' button at the top

- (void)beginCustomizingItems:(NSArray<UITabBarItem *> *)items API_UNAVAILABLE(tvos);   // list all items that can be reordered. always animates a sheet up. visible items not listed are fixed in place
- (BOOL)endCustomizingAnimated:(BOOL)animated API_UNAVAILABLE(tvos);    // hide customization sheet. normally you should let the user do it. check list of items to see new layout. returns YES if layout changed

@property(nonatomic, readonly, getter=isCustomizing) BOOL customizing API_UNAVAILABLE(tvos);

/*
 The behavior of tintColor for bars has changed on iOS 7.0. It no longer affects the bar's background
 and behaves as described for the tintColor property added to UIView.
 To tint the bar's background, please use -barTintColor.
 */
@property(null_resettable, nonatomic, strong) UIColor *tintColor API_AVAILABLE(ios(5.0));
@property(nullable, nonatomic, strong) UIColor *barTintColor API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR;  // default is nil
/// Unselected items in this tab bar will be tinted with this color. Setting this value to nil indicates that UITabBar should use its default value instead.
@property (nonatomic, readwrite, copy, nullable) UIColor *unselectedItemTintColor API_AVAILABLE(ios(10.0)) UI_APPEARANCE_SELECTOR;

/* selectedImageTintColor will be applied to the gradient image used when creating the
 selected image. Default is nil and will result in the system bright blue for selected
 tab item images. If you wish to also customize the unselected image appearance, you must
 use the image and selectedImage properties on UITabBarItem along with UIImageRenderingModeAlways
 
 Deprecated in iOS 8.0. On iOS 7.0 and later the selected image takes its color from the
 inherited tintColor of the UITabBar, which may be set separately if necessary.
 */
@property(nullable, nonatomic, strong) UIColor *selectedImageTintColor API_DEPRECATED_WITH_REPLACEMENT("tintColor", ios(5.0, 8.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);

/* The background image will be tiled to fit, even if it was not created via the UIImage resizableImage methods.
 */
@property(nullable, nonatomic, strong) UIImage *backgroundImage API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* The selection indicator image is drawn on top of the tab bar, behind the bar item icon.
 */
@property(nullable, nonatomic, strong) UIImage *selectionIndicatorImage API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* Default is nil. When non-nil, a custom shadow image to show instead of the default shadow image. For a custom shadow to be shown, a custom background image must also be set with -setBackgroundImage: (if the default background image is used, the default shadow image will be used).
 */
@property(nullable, nonatomic, strong) UIImage *shadowImage API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

/*
 Default is UITabBarItemPositioningAutomatic. The tab bar items fill horizontally
 for the iPhone user interface idiom, and are centered with a default width and 
 inter-item spacing (customizable with the itemWidth and itemSpacing
 properties) for the iPad idiom. When the tab bar is owned by a UITabBarController
 further heuristics may determine the positioning for UITabBarItemPositioningAutomatic.
    Use UITabBarItemPositioningFill to force the items to fill horizontally.
    Use UITabBarItemPositioningCenter to force the items to center with a default
 width (or the itemWidth, if set).
 */
@property(nonatomic) UITabBarItemPositioning itemPositioning API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);

/*
 Set the itemWidth to a positive value to be used as the width for tab bar items
 when they are positioned as a centered group (as opposed to filling the tab bar).
 Default of 0 or values less than 0 will be interpreted as a system-defined width.
 */
@property(nonatomic) CGFloat itemWidth API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR;

/*
 Set the itemSpacing to a positive value to be used between tab bar items
 when they are positioned as a centered group.
 Default of 0 or values less than 0 will be interpreted as a system-defined spacing.
 */
@property(nonatomic) CGFloat itemSpacing API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR;

/*
 Valid bar styles are UIBarStyleDefault (default) and UIBarStyleBlack.
 */
@property(nonatomic) UIBarStyle barStyle API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);

/*
 Default is YES.
 You may force an opaque background by setting the property to NO.
 If the tab bar has a custom background image, the default is inferred from the alpha
 values of the image—YES if it has any pixel with alpha < 1.0
 If you send setTranslucent:YES to a tab bar with an opaque custom background image
 the tab bar will apply a system opacity less than 1.0 to the image.
 If you send setTranslucent:NO to a tab bar with a translucent custom background image
 the tab bar will provide an opaque background for the image using the bar's barTintColor if defined, or black
 for UIBarStyleBlack or white for UIBarStyleDefault if barTintColor is nil.
 */
@property(nonatomic,getter=isTranslucent) BOOL translucent API_AVAILABLE(ios(7.0));

/// Describes the appearance attributes for the tab bar to use.
@property (nonatomic, readwrite, copy) UITabBarAppearance *standardAppearance UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(13.0), tvos(13.0));


// A small view (200pt by 68pt) in the leading gutter next to tab bar to add accessories, such as logos, time, so on. If auto layout is used, it will be respected when placing subviews. If not, subviews will be places in respect to top left corner--meaning, frames of subviews will not be updated in any way.
// This view and its subviews will have userInteractionEnabled set to NO at all time.
@property(nonatomic, readonly, strong) UIView *leadingAccessoryView API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, watchos);

// A small view (200pt by 68pt) in the trailing gutter next to tab bar to add accessories, such as logos, time, so on. If auto layout is used, it will be respected when placing subviews. If not, subviews will be places in respect to top left corner--meaning, frames of subviews will not be updated in any way.
// This view and its subviews will have userInteractionEnabled set to NO at all time.
@property(nonatomic, readonly, strong) UIView *trailingAccessoryView API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, watchos);

@end

//___________________________________________________________________________________________________

@protocol UITabBarDelegate<NSObject>
@optional

- (void)tabBar:(UITabBar *)tabBar didSelectItem:(UITabBarItem *)item; // called when a new view is selected by the user (but not programatically)

/* called when user shows or dismisses customize sheet. you can use the 'willEnd' to set up what appears underneath. 
 changed is YES if there was some change to which items are visible or which order they appear. If selectedItem is no longer visible, 
 it will be set to nil.
 */

- (void)tabBar:(UITabBar *)tabBar willBeginCustomizingItems:(NSArray<UITabBarItem *> *)items API_UNAVAILABLE(tvos);                     // called before customize sheet is shown. items is current item list
- (void)tabBar:(UITabBar *)tabBar didBeginCustomizingItems:(NSArray<UITabBarItem *> *)items API_UNAVAILABLE(tvos);                      // called after customize sheet is shown. items is current item list
- (void)tabBar:(UITabBar *)tabBar willEndCustomizingItems:(NSArray<UITabBarItem *> *)items changed:(BOOL)changed API_UNAVAILABLE(tvos); // called before customize sheet is hidden. items is new item list
- (void)tabBar:(UITabBar *)tabBar didEndCustomizingItems:(NSArray<UITabBarItem *> *)items changed:(BOOL)changed API_UNAVAILABLE(tvos);  // called after customize sheet is hidden. items is new item list

@end

#if TARGET_OS_IOS
@interface UITabBar (SpringLoading) <UISpringLoadedInteractionSupporting>
@end
#endif

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITabBar.h>
#endif
