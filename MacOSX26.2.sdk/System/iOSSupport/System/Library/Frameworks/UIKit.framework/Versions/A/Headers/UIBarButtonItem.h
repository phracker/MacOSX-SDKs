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

#import <Symbols/NSSymbolEffect.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIBarButtonItemStyle) {
    UIBarButtonItemStylePlain,

    /// A button item style for a prominent button.
    ///
    /// For example, use this for a button that completes or finalizes some task.
    /// Buttons with this style will not be visually grouped with other items
    /// in a navigation bar or toolbar, and will also have other styling changes
    /// appropriate to their context to indicate their prominence.
    UIBarButtonItemStyleProminent API_AVAILABLE(ios(26.0)) = 2,

    UIBarButtonItemStyleBordered API_DEPRECATED_WITH_REPLACEMENT("UIBarButtonItemStylePlain", ios(2.0, 8.0)) API_UNAVAILABLE(visionos, watchos) = 1,
    UIBarButtonItemStyleDone API_DEPRECATED_WITH_REPLACEMENT("UIBarButtonItemStyleProminent", ios(2.0, 26.0)) = UIBarButtonItemStyleProminent,
} API_UNAVAILABLE(watchos);

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
    UIBarButtonSystemItemPageCurl API_DEPRECATED("", ios(4.0, 11.0)) API_UNAVAILABLE(visionos, watchos),
    UIBarButtonSystemItemClose API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos),
    UIBarButtonSystemItemWritingTools API_AVAILABLE(ios(18.2), visionos(26.0)) API_UNAVAILABLE(tvos, watchos)
} API_UNAVAILABLE(watchos);

@class UIImage, UIView;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIBarButtonItem : UIBarItem <NSCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithImage:(nullable UIImage *)image style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithImage:(nullable UIImage *)image landscapeImagePhone:(nullable UIImage *)landscapeImagePhone style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action API_AVAILABLE(ios(5.0)); // landscapeImagePhone will be used for the bar button image when the bar has Compact or Condensed bar metrics.
- (instancetype)initWithTitle:(nullable NSString *)title style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithCustomView:(UIView *)customView;

/// Creates a bar button item for the given systemItem. The primaryAction is copied, and its title & image are ignored.
- (instancetype)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem primaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Creates a plain-style bar button item from the properties of primaryAction. primaryAction is copied.
- (instancetype)initWithPrimaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Creates a bar button item for the given systemItem. The constructed item will present the menu immediately when touched.
- (instancetype)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem menu:(nullable UIMenu *)menu API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Creates a plain-style bar button item with the given title. The constructed item will present the menu immediately when touched.
- (instancetype)initWithTitle:(nullable NSString *)title menu:(nullable UIMenu *)menu API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Creates a plain-style bar button item with the given image. The constructed item will present the menu immediately when touched.
- (instancetype)initWithImage:(nullable UIImage *)image menu:(nullable UIMenu *)menu API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Creates a plain-style bar button item from the properties of primaryAction. primaryAction is copied.
- (instancetype)initWithPrimaryAction:(nullable UIAction *)primaryAction menu:(nullable UIMenu *)menu API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/// Creates a bar button item for the given systemItem. The primaryAction is copied, and its title & image are ignored.
- (instancetype)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem primaryAction:(nullable UIAction *)primaryAction menu:(nullable UIMenu *)menu API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/// Creates a plain-style bar button item with the given title and image.
- (instancetype)initWithTitle:(nullable NSString *)title image:(nullable UIImage *)image target:(nullable id)target action:(nullable SEL)action menu:(nullable UIMenu *)menu API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/// Construct a new fixed space item with the given width.
+ (instancetype)fixedSpaceItemOfWidth:(CGFloat)width API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Construct a new flexible space item.
+ (instancetype)flexibleSpaceItem API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Creates a new fixed space item of zero width.
///
/// A fixed space of 0 width separates the shared background used
/// in navigation bars and toolbars to visually group items.
+ (instancetype)fixedSpaceItem API_AVAILABLE(ios(26.0));

@property (nonatomic, readwrite, assign) UIBarButtonItemStyle style;            // default is UIBarButtonItemStylePlain
@property (nonatomic, readwrite, assign) CGFloat              width;            // default is 0.0
@property (nonatomic, readwrite, copy  , nullable) NSSet<NSString *>   *possibleTitles;   // default is nil
@property (nonatomic, readwrite, strong, nullable) __kindof UIView     *customView;       // default is nil
@property (nonatomic, readwrite, assign, nullable) SEL                  action;           // default is NULL
@property (nonatomic, readwrite, weak  , nullable) id                   target;           // default is nil

/// Set the primaryAction on this item, updating the title & image of the item if appropriate (primaryAction's title is non-nil for the title update, primaryAction's image is non-nil for the image update, and if this is not a system item). When primaryAction is non-nil, the target & action properties are ignored. If primaryAction is set to nil, the title & image properties are left unchanged.
@property (nonatomic, readwrite, copy, nullable) UIAction *primaryAction API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// When non-nil the menu is presented, the gesture used to trigger the menu is based on if the bar button item would normally trigger an action when tapped.
@property (nonatomic, readwrite, copy, nullable) UIMenu *menu API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Preferred menu element ordering strategy for menus displayed by this button.
@property (nonatomic) UIContextMenuConfigurationElementOrder preferredMenuElementOrder API_AVAILABLE(ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Indicates if the button changes selection as its primary action.
/// This shows the menu as options for selection if a menu is populated and no action when tapped is enabled.
/// If no menu is provided and no action is enabled when tapped, the item is toggled on and off for the primary action.
@property (nonatomic, readwrite, assign) BOOL changesSelectionAsPrimaryAction API_AVAILABLE(ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@property (nonatomic, readwrite, assign, getter=isSelected) BOOL selected API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

/// If the item should be hidden from display.
@property (nonatomic, readwrite, assign, getter = isHidden) BOOL hidden API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// Whether or not symbol animations are enabled for this bar button item.
@property (nonatomic, readwrite, assign, getter=isSymbolAnimationEnabled) BOOL symbolAnimationEnabled API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// A UIMenuElement that should substitute for the UIBarButtonItem when displayed in a menu.
@property (nonatomic, readwrite, copy, nullable) UIMenuElement *menuRepresentation API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// A boolean value indicating whether the background this item may share with other items in the bar
/// should be hidden.
///
/// Set this property to `YES` to prevent the standard shared background (typically using the Glass effect)
/// from being drawn behind this bar button item.
///
/// This item will not be visually grouped with any other items,
/// without the standard shared background.
/// This property is ignored if the item is in a `UIBarButtonItemGroup` with more than one item.
/// The default value is `NO`.
@property (nonatomic) BOOL hidesSharedBackground API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos);

/// A boolean value indicating whether this bar button item can share a background with other items
/// in a navigation bar or a toolbar.
///
/// When `NO`, This item will not be visually grouped with any other items.
///
/// This property is ignored if the item is in a `UIBarButtonItemGroup` with more than one item.
/// The default value is `YES`.
@property (nonatomic) BOOL sharesBackground API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos);

/// An identifier used to match bar button items across transitions in a navigation bar or toolbar.
///
/// When the set of bar button items in a navigation bar or toolbar changes (for example, when pushing
/// or popping view controllers), UIKit automatically animates the transition between the different sets
/// of items. By default, UIKit uses heuristics based on item position and content to determine which items
/// should be matched for these transitions.
///
/// Set this property with the same value on two different bar button items in different navigation item
/// configurations to indicate that they should be treated as the same item during transitions. This allows
/// for more natural animations when the visuals or function of an item changes across contexts.
///
/// The default value is `nil`, which means UIKit will use its default heuristics for transitions.
@property (nonatomic, copy, nullable) NSString *identifier API_AVAILABLE(ios(26.0));

/// Create a fixed group containing this bar button item. UIBarButtonItems may only be in a single UIBarButtonItemGroup at a time, adding a bar button item to a group removes it from any previous group.
- (UIBarButtonItemGroup *)creatingFixedGroup API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// Create a movable group containing this bar button item. UIBarButtonItems may only be in a single UIBarButtonItemGroup at a time, adding a bar button item to a group removes it from any previous group.
- (UIBarButtonItemGroup *)creatingMovableGroupWithCustomizationIdentifier:(NSString *)customizationIdentifier API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// Create an optional group containing this bar button item. UIBarButtonItems may only be in a single UIBarButtonItemGroup at a time, adding a bar button item to a group removes it from any previous group.
- (UIBarButtonItemGroup *)creatingOptionalGroupWithCustomizationIdentifier:(NSString *)customizationIdentifier inDefaultCustomization:(BOOL)inDefaultCustomization API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

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

@interface UIBarButtonItem (/*Symbol animation presets*/)

/// Adds a symbol effect to the bar button item with default options and animation.
/// Only a subset of symbol effects are supported; Appear and Disappear effects, for example, are unsupported, and will assert.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Adds a symbol effect to the bar button item with specified options and default animation.
/// Only a subset of symbol effects are supported; Appear and Disappear effects, for example, are unsupported, and will assert.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Adds a symbol effect to the bar button item with specified options and animation.
/// Only a subset of symbol effects are supported; Appear and Disappear effects, for example, are unsupported, and will assert.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Removes from the bar button item the symbol effect matching the type of effect passed in, with default options and animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes from the bar button item the symbol effect matching the type of effect passed in, with specified options and default animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes from the bar button item the symbol effect matching the type of effect passed in, with specified options and animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Removes all symbol effects from the bar button item with default options and animation.
- (void)removeAllSymbolEffects API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes all symbol effects from the bar button item with specified options and default animation.
- (void)removeAllSymbolEffectsWithOptions:(NSSymbolEffectOptions *)options API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes all symbol effects from the bar button item with specified options and animation.
- (void)removeAllSymbolEffectsWithOptions:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Sets the symbol image on the bar button item with a symbol content transition and default options.
/// Passing in a non-symbol image will result in undefined behavior.
- (void)setSymbolImage:(UIImage *)symbolImage withContentTransition:(NSSymbolContentTransition *)transition API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Sets the symbol image on the bar button item with a symbol content transition and specified options.
/// Passing in a non-symbol image will result in undefined behavior.
- (void)setSymbolImage:(UIImage *)symbolImage withContentTransition:(NSSymbolContentTransition *)transition options:(NSSymbolEffectOptions *)options API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIBarButtonItem.h>
#endif
