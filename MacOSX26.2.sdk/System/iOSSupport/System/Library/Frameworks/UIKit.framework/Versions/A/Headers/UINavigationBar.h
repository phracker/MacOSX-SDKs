#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UINavigationBar.h>)
//
//  UINavigationBar.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIFont.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIBarCommon.h>
#import <UIKit/UINavigationItem.h>
#import <UIKit/UIBehavioralStyle.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UINavigationItem, UIBarButtonItem, UIImage, UIColor, UINavigationBarAppearance;
@protocol UINavigationBarDelegate;

typedef NS_ENUM(NSInteger, UINavigationBarNSToolbarSection) {
    UINavigationBarNSToolbarSectionNone,
    UINavigationBarNSToolbarSectionSidebar,
    UINavigationBarNSToolbarSectionSupplementary,
    UINavigationBarNSToolbarSectionContent,
} NS_SWIFT_NAME(UINavigationBar.NSToolbarSection) API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UINavigationBar : UIView <NSCoding, UIBarPositioning> 

@property(nonatomic,assign) UIBarStyle barStyle UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);
@property(nullable,nonatomic,weak) id<UINavigationBarDelegate> delegate;

/*
 New behavior on iOS 7.
 Default is YES.
 You may force an opaque background by setting the property to NO.
 If the navigation bar has a custom background image, the default is inferred 
 from the alpha values of the image—YES if it has any pixel with alpha < 1.0
 If you send setTranslucent:YES to a bar with an opaque custom background image
 it will apply a system opacity less than 1.0 to the image.
 If you send setTranslucent:NO to a bar with a translucent custom background image
 it will provide an opaque background for the image using the bar's barTintColor if defined, or black
 for UIBarStyleBlack or white for UIBarStyleDefault if barTintColor is nil.
 */
@property(nonatomic,assign,getter=isTranslucent) BOOL translucent API_AVAILABLE(ios(3.0)) UI_APPEARANCE_SELECTOR; // Default is NO on iOS 6 and earlier. Always YES if barStyle is set to UIBarStyleBlackTranslucent

// Pushing a navigation item displays the item's title in the center of the navigation bar.
// The previous top navigation item (if it exists) is displayed as a "back" button on the left.
- (void)pushNavigationItem:(UINavigationItem *)item animated:(BOOL)animated;
- (nullable UINavigationItem *)popNavigationItemAnimated:(BOOL)animated; // Returns the item that was popped.

@property(nullable, nonatomic,readonly,strong) UINavigationItem *topItem;
@property(nullable, nonatomic,readonly,strong) UINavigationItem *backItem;

@property(nullable,nonatomic,copy) NSArray<UINavigationItem *> *items;
- (void)setItems:(nullable NSArray<UINavigationItem *> *)items animated:(BOOL)animated; // If animated is YES, then simulate a push or pop depending on whether the new top item was previously in the stack.

/// When set to YES, the navigation bar will use a larger out-of-line title view when requested by the current navigation item. To specify when the large out-of-line title view appears, see UINavigationItem.largeTitleDisplayMode. Defaults to NO.
@property (nonatomic, readwrite, assign) BOOL prefersLargeTitles UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

/// The toolbar section that this navigation bar is currently using.
@property (nonatomic, readonly, assign) UINavigationBarNSToolbarSection currentNSToolbarSection API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// The concrete behavioral style chosen for the navigation bar. When this resolves to .mac, the navigation bar's contents are placed in the NSToolbar.
@property (nonatomic, readonly, assign) UIBehavioralStyle behavioralStyle API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// The requested behavioral style for the navigation bar.
@property (nonatomic, readwrite, assign) UIBehavioralStyle preferredBehavioralStyle API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/*
 The behavior of tintColor for bars has changed on iOS 7.0. It no longer affects the bar's background
 and behaves as described for the tintColor property added to UIView.
 To tint the bar's background, please use -barTintColor.
 */
@property(null_resettable, nonatomic,strong) UIColor *tintColor;
@property(nullable, nonatomic,strong) UIColor *barTintColor API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR;  // default is nil

/* In general, you should specify a value for the normal state to be used by other states which don't have a custom value set.
 
 Similarly, when a property is dependent on the bar metrics (on the iPhone in landscape orientation, bars have a different height from standard), be sure to specify a value for UIBarMetricsDefault.
 */

- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forBarPosition:(UIBarPosition)barPosition barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)backgroundImageForBarPosition:(UIBarPosition)barPosition barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR;

/*
Same as using UIBarPositionAny in -setBackgroundImage:forBarPosition:barMetrics. Resizable images will be stretched
vertically if necessary when the navigation bar is in the position UIBarPositionTopAttached.
*/
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)backgroundImageForBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* Default is nil. When non-nil, a custom shadow image to show instead of the default shadow image. For a custom shadow to be shown, a custom background image must also be set with -setBackgroundImage:forBarMetrics: (if the default background image is used, the default shadow image will be used).
 */
@property(nullable, nonatomic,strong) UIImage *shadowImage API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

/* You may specify the font, text color, and shadow properties for the title in the text attributes dictionary, using the keys found in NSAttributedString.h.
 */
@property(nullable,nonatomic,copy) NSDictionary<NSAttributedStringKey, id> *titleTextAttributes API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* You may specify the font, text color, and shadow properties for the large title in the text attributes dictionary, using the keys found in NSAttributedString.h.
 */
@property(nullable, nonatomic, copy) NSDictionary<NSAttributedStringKey, id> *largeTitleTextAttributes UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

- (void)setTitleVerticalPositionAdjustment:(CGFloat)adjustment forBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
- (CGFloat)titleVerticalPositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/*
 The back indicator image is shown beside the back button.
 The back indicator transition mask image is used as a mask for content during push and pop transitions
 Note: These properties must both be set if you want to customize the back indicator image.
 */
@property(nullable,nonatomic,strong) UIImage *backIndicatorImage API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);
@property(nullable,nonatomic,strong) UIImage *backIndicatorTransitionMaskImage API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);

/*
 Fallback Behavior:
 1) Appearance objects are used in whole – that is, all values will be sourced entirely from an
 instance of UINavigationBarAppearance defined by one of these named properties (standardAppearance,
 compactAppearance, scrollEdgeAppearance, compactScrollEdgeAppearance) on either UINavigationBar
 (self) or UINavigationItem (self.topItem).
 2) The navigation bar will always attempt to use the most relevant appearance instances first,
 before falling back to less relevant ones. The fallback logic is:
     AtScrollEdge: self.topItem.scrollEdgeAppearance => self.scrollEdgeAppearance
         => self.topItem.standardAppearance => self.standardAppearance
     AtCompactScrollEdge: self.topItem.compactScrollEdgeAppearance
         => self.compactScrollEdgeAppearance => self.topItem.scrollEdgeAppearance
         => self.scrollEdgeAppearance => self.topItem.compactAppearance
         => self.compactAppearance => self.topItem.standardAppearance => self.standardAppearance
     CompactSize: self.topItem.compactAppearance => self.compactAppearance
         => self.topItem.standardAppearance => self.standardAppearance
     NormalSize: self.topItem.standardAppearance => self.standardAppearance
 */

/// Describes the appearance attributes for the navigation bar to use when it is displayed with its standard height.
@property (nonatomic, readwrite, copy) UINavigationBarAppearance *standardAppearance UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
/// Describes the appearance attributes for the navigation bar to use when it is displayed with its compact height. If not set, the standardAppearance will be used instead.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *compactAppearance UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);
/// Describes the appearance attributes for the navigation bar to use when an associated UIScrollView has reached the edge abutting the bar (the top edge for the navigation bar). If not set, a modified standardAppearance will be used instead.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *scrollEdgeAppearance UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);
/// Describes the appearance attributes for the navigation bar to use when it is displayed with its compact heights, and an associated UIScrollView has reached the edge abutting the bar. If not set, first the scrollEdgeAppearance will be tried, and if that is nil then compactAppearance followed by a modified standardAppearance.
@property(nonatomic,readwrite, copy, nullable) UINavigationBarAppearance *compactScrollEdgeAppearance UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);
@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UINavigationBarDelegate <UIBarPositioningDelegate>

@optional

- (BOOL)navigationBar:(UINavigationBar *)navigationBar shouldPushItem:(UINavigationItem *)item; // called to push. return NO not to.
- (void)navigationBar:(UINavigationBar *)navigationBar didPushItem:(UINavigationItem *)item;    // called at end of animation of push or immediately if not animated
- (BOOL)navigationBar:(UINavigationBar *)navigationBar shouldPopItem:(UINavigationItem *)item;  // same as push methods
- (void)navigationBar:(UINavigationBar *)navigationBar didPopItem:(UINavigationItem *)item;

#if !TARGET_OS_TV && !TARGET_OS_WATCH
/// Which section of the NSToolbar this navigation bar should use when attempting to host in an NSToolbar. Returning 'None' will disable NSToolbar hosting as if preferredBehavioralStyle were set to 'Pad' The specific section returned will also affect how the navigation bar presents in that section.
- (UINavigationBarNSToolbarSection)navigationBarNSToolbarSection:(UINavigationBar *)navigationBar API_UNAVAILABLE(watchos);
#endif

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UINavigationBar.h>
#endif
