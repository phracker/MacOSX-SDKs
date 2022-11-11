#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBarButtonItem.h>)
//
//  UIBarButtonItem.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIBarItem.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIBarCommon.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIBarButtonItemStyle) {
    UIBarButtonItemStylePlain,
    UIBarButtonItemStyleBordered API_DEPRECATED_WITH_REPLACEMENT("UIBarButtonItemStylePlain", ios(2.0, 8.0)),
    UIBarButtonItemStyleDone,
};

typedef NS_ENUM(NSInteger, UIBarButtonSystemItem) {
    UIBarButtonSystemItemDone,
    UIBarButtonSystemItemCancel,
    UIBarButtonSystemItemEdit,  
    UIBarButtonSystemItemSave,  
    UIBarButtonSystemItemAdd,
    UIBarButtonSystemItemFlexibleSpace,
    UIBarButtonSystemItemFixedSpace,
    UIBarButtonSystemItemCompose,
    UIBarButtonSystemItemReply,
    UIBarButtonSystemItemAction,
    UIBarButtonSystemItemOrganize,
    UIBarButtonSystemItemBookmarks,
    UIBarButtonSystemItemSearch,
    UIBarButtonSystemItemRefresh,
    UIBarButtonSystemItemStop,
    UIBarButtonSystemItemCamera,
    UIBarButtonSystemItemTrash,
    UIBarButtonSystemItemPlay,
    UIBarButtonSystemItemPause,
    UIBarButtonSystemItemRewind,
    UIBarButtonSystemItemFastForward,
    UIBarButtonSystemItemUndo API_AVAILABLE(ios(3.0)),
    UIBarButtonSystemItemRedo API_AVAILABLE(ios(3.0)),
    UIBarButtonSystemItemPageCurl API_DEPRECATED("", ios(4.0, 11.0)),
    UIBarButtonSystemItemClose API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos)
};

@class UIImage, UIView;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) NS_SWIFT_UI_ACTOR
@interface UIBarButtonItem : UIBarItem <NSCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithImage:(nullable UIImage *)image style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithImage:(nullable UIImage *)image landscapeImagePhone:(nullable UIImage *)landscapeImagePhone style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action API_AVAILABLE(ios(5.0)); // landscapeImagePhone will be used for the bar button image when the bar has Compact or Condensed bar metrics.
- (instancetype)initWithTitle:(nullable NSString *)title style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithCustomView:(UIView *)customView;

/// Creates a bar button item for the given systemItem. The primaryAction is copied, and its title & image are ignored.
- (instancetype)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem primaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0));

/// Creates a plain-style bar button item from the properties of primaryAction. primaryAction is copied.
- (instancetype)initWithPrimaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0));

/// Creates a bar button item for the given systemItem. The constructed item will present the menu immediately when touched.
- (instancetype)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem menu:(nullable UIMenu *)menu API_AVAILABLE(ios(14.0));

/// Creates a plain-style bar button item with the given title. The constructed item will present the menu immediately when touched.
- (instancetype)initWithTitle:(nullable NSString *)title menu:(nullable UIMenu *)menu API_AVAILABLE(ios(14.0));

/// Creates a plain-style bar button item with the given item. The constructed item will present the menu immediately when touched.
- (instancetype)initWithImage:(nullable UIImage *)image menu:(nullable UIMenu *)menu API_AVAILABLE(ios(14.0));

/// Construct a new fixed space item with the given width.
+ (instancetype)fixedSpaceItemOfWidth:(CGFloat)width API_AVAILABLE(ios(14.0));

/// Construct a new flexible space item.
+ (instancetype)flexibleSpaceItem API_AVAILABLE(ios(14.0));

@property (nonatomic, readwrite, assign) UIBarButtonItemStyle style;            // default is UIBarButtonItemStylePlain
@property (nonatomic, readwrite, assign) CGFloat              width;            // default is 0.0
@property (nonatomic, readwrite, copy  , nullable) NSSet<NSString *>   *possibleTitles;   // default is nil
@property (nonatomic, readwrite, strong, nullable) __kindof UIView     *customView;       // default is nil
@property (nonatomic, readwrite, assign, nullable) SEL                  action;           // default is NULL
@property (nonatomic, readwrite, weak  , nullable) id                   target;           // default is nil

/// Set the primaryAction on this item, updating the title & image of the item if appropriate (primaryAction is non-nil, and this is not a system item). When primaryAction is non-nil, the target & action properties are ignored. If primaryAction is set to nil, the title & image properties are left unchanged.
@property (nonatomic, readwrite, copy, nullable) UIAction *primaryAction API_AVAILABLE(ios(14.0));

/// When non-nil the menu is presented, the gesture used to trigger the menu is based on if the bar button item would normally trigger an action when tapped.
@property (nonatomic, readwrite, copy, nullable) UIMenu *menu API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/// Indicates if the button changes selection as its primary action.
/// This shows the menu as options for selection if a menu is populated and no action when tapped is enabled.
/// If no menu is provided and no action is enabled when tapped, the item is toggled on and off for the primary action.
@property (nonatomic, readwrite, assign) BOOL changesSelectionAsPrimaryAction API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

@property (nonatomic, readwrite, assign, getter=isSelected) BOOL selected API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

//
// Appearance modifiers
//

/* Send these messages to the [UIBarButtonItem appearance] proxy to customize all buttons, or, to customize a specific button, send them to a specific UIBarButtonItem instance, which may be used in all the usual places in a UINavigationItem (backBarButtonItem, leftBarButtonItem, rightBarButtonItem) or a UIToolbar.
 */

/* In general, you should specify a value for the normal state to be used by other states which don't have a custom value set.
 
 Similarly, when a property is dependent on the bar metrics (on the iPhone in landscape orientation, bars have a different height from standard), be sure to specify a value for UIBarMetricsDefault.
 
 This sets the background image for buttons of any style.
 */
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)backgroundImageForState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* This sets the background image for buttons with a specific style. When calling this on a UIBarButtonItem instance, the style argument must match the button's style; when calling on the UIAppearance proxy, any style may be passed.
 */
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state style:(UIBarButtonItemStyle)style barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)backgroundImageForState:(UIControlState)state style:(UIBarButtonItemStyle)style barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

@property(nullable, nonatomic,strong) UIColor *tintColor API_AVAILABLE(ios(5.0));

/* For adjusting the vertical centering of bordered bar buttons within the bar 
 */
- (void)setBackgroundVerticalPositionAdjustment:(CGFloat)adjustment forBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR; 
- (CGFloat)backgroundVerticalPositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* For adjusting the position of a title (if any) within a bordered bar button 
 */
- (void)setTitlePositionAdjustment:(UIOffset)adjustment forBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR; 
- (UIOffset)titlePositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* The remaining appearance modifiers apply solely to UINavigationBar back buttons and are ignored by other buttons.
 */
/*
 backgroundImage must be a resizable image for good results.
 */
- (void)setBackButtonBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);
- (nullable UIImage *)backButtonBackgroundImageForState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);

- (void)setBackButtonTitlePositionAdjustment:(UIOffset)adjustment forBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);
- (UIOffset)backButtonTitlePositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);

/* For adjusting the vertical centering of bordered bar buttons within the bar 
 */
- (void)setBackButtonBackgroundVerticalPositionAdjustment:(CGFloat)adjustment forBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);
- (CGFloat)backButtonBackgroundVerticalPositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos);

@end

#if TARGET_OS_IOS
@interface UIBarButtonItem (SpringLoading) <UISpringLoadedInteractionSupporting>
@end
#endif

NS_ASSUME_NONNULL_END


#else
#import <UIKitCore/UIBarButtonItem.h>
#endif
