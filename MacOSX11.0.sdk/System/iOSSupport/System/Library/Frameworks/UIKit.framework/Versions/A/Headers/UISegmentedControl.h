#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISegmentedControl.h>)
//
//  UISegmentedControl.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIBarButtonItem.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UISegmentedControlStyle) {
    UISegmentedControlStylePlain,     // large plain
    UISegmentedControlStyleBordered,  // large bordered
    UISegmentedControlStyleBar,       // small button/nav bar style. tintable
    UISegmentedControlStyleBezeled,   // DEPRECATED. Do not use this style.
} API_DEPRECATED("The segmentedControlStyle property no longer has any effect", ios(2.0, 7.0)) API_UNAVAILABLE(tvos);

enum {
    UISegmentedControlNoSegment = -1   // segment index for no selected segment
};

typedef NS_ENUM(NSInteger, UISegmentedControlSegment) {
    UISegmentedControlSegmentAny = 0,
    UISegmentedControlSegmentLeft = 1,   // The capped, leftmost segment. Only applies when numSegments > 1.
    UISegmentedControlSegmentCenter = 2, // Any segment between the left and rightmost segments. Only applies when numSegments > 2.
    UISegmentedControlSegmentRight = 3,  // The capped,rightmost segment. Only applies when numSegments > 1.
    UISegmentedControlSegmentAlone = 4,  // The standalone segment, capped on both ends. Only applies when numSegments = 1.
};

@class UIImage, UIColor;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UISegmentedControl : UIControl <NSCoding>

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Initializes the segmented control with the given items. Items may be NSStrings, UIImages, or (as of iOS 14.0) UIActions. When constructing from a UIAction segments will prefer images over titles when both are provided. The segmented control is automatically sized to fit content.
- (instancetype)initWithItems:(nullable NSArray *)items NS_DESIGNATED_INITIALIZER;

/// Initializes the segmented control with the given frame and segments constructed from the given UIActions. Segments will prefer images over titles when both are provided. Selecting a segment calls UIAction.actionHandler as well as handlers for the ValueChanged and PrimaryActionTriggered control events.
- (instancetype)initWithFrame:(CGRect)frame actions:(NSArray<UIAction *> *)actions API_AVAILABLE(ios(14.0));

/// Insert a segment with the given action at the given index. Segments will prefer images over titles when both are provided. When the segment is selected UIAction.actionHandler is called. If a segment already exists with the action's identifier that segment will either be updated (if the index is the same) or it will be removed (if different).
- (void)insertSegmentWithAction:(UIAction *)action atIndex:(NSUInteger)segment animated:(BOOL)animated API_AVAILABLE(ios(14.0));
/// Reconfigures the given segment with this action. Segments will prefer images over titles when both are provided. When the segment is selected UIAction.actionHandler is called. UIAction.identifier must either match the action of the existing segment at this index, or be unique within all actions associated with the segmented control, or this method will assert.
- (void)setAction:(UIAction *)action forSegmentAtIndex:(NSUInteger)segment API_AVAILABLE(ios(14.0));
/// Fetch the action for the given segment, if one has been assigned to that segment
- (nullable UIAction *)actionForSegmentAtIndex:(NSUInteger)segment API_AVAILABLE(ios(14.0));
/// Returns the index of the segment associated with the given actionIdentifier, or NSNotFound if the identifier could not be found.
- (NSInteger)segmentIndexForActionIdentifier:(UIActionIdentifier)actionIdentifier API_AVAILABLE(ios(14.0));

@property(nonatomic) UISegmentedControlStyle segmentedControlStyle API_DEPRECATED("The segmentedControlStyle property no longer has any effect", ios(2.0, 7.0)) API_UNAVAILABLE(tvos);
@property(nonatomic,getter=isMomentary) BOOL momentary;             // if set, then we don't keep showing selected state after tracking ends. default is NO
@property(nonatomic,readonly) NSUInteger numberOfSegments;

// For segments whose width value is 0, setting this property to YES attempts to adjust segment widths based on their content widths. Default is NO.
@property(nonatomic) BOOL apportionsSegmentWidthsByContent API_AVAILABLE(ios(5.0));

- (void)insertSegmentWithTitle:(nullable NSString *)title atIndex:(NSUInteger)segment animated:(BOOL)animated; // insert before segment number. 0..#segments. value pinned
- (void)insertSegmentWithImage:(nullable UIImage *)image  atIndex:(NSUInteger)segment animated:(BOOL)animated;
- (void)removeSegmentAtIndex:(NSUInteger)segment animated:(BOOL)animated;
- (void)removeAllSegments;

- (void)setTitle:(nullable NSString *)title forSegmentAtIndex:(NSUInteger)segment;      // can only have image or title, not both. must be 0..#segments - 1 (or ignored). default is nil
- (nullable NSString *)titleForSegmentAtIndex:(NSUInteger)segment;

- (void)setImage:(nullable UIImage *)image forSegmentAtIndex:(NSUInteger)segment;       // can only have image or title, not both. must be 0..#segments - 1 (or ignored). default is nil
- (nullable UIImage *)imageForSegmentAtIndex:(NSUInteger)segment;

- (void)setWidth:(CGFloat)width forSegmentAtIndex:(NSUInteger)segment;         // set to 0.0 width to autosize. default is 0.0
- (CGFloat)widthForSegmentAtIndex:(NSUInteger)segment;

- (void)setContentOffset:(CGSize)offset forSegmentAtIndex:(NSUInteger)segment; // adjust offset of image or text inside the segment. default is (0,0)
- (CGSize)contentOffsetForSegmentAtIndex:(NSUInteger)segment;

- (void)setEnabled:(BOOL)enabled forSegmentAtIndex:(NSUInteger)segment;        // default is YES
- (BOOL)isEnabledForSegmentAtIndex:(NSUInteger)segment;

// ignored in momentary mode. returns last segment pressed. default is UISegmentedControlNoSegment until a segment is pressed
// the UIControlEventValueChanged action is invoked when the segment changes via a user event. set to UISegmentedControlNoSegment to turn off selection
@property(nonatomic) NSInteger selectedSegmentIndex;

// The color to use for highlighting the currently selected segment.
@property(nullable, nonatomic, strong) UIColor *selectedSegmentTintColor API_AVAILABLE(ios(13.0)) UI_APPEARANCE_SELECTOR;

/* If backgroundImage is an image returned from -[UIImage resizableImageWithCapInsets:] the cap widths will be calculated from that information, otherwise, the cap width will be calculated by subtracting one from the image's width then dividing by 2. The cap widths will also be used as the margins for text placement. To adjust the margin use the margin adjustment methods.
 
 In general, you should specify a value for the normal state to be used by other states which don't have a custom value set.
 
 Similarly, when a property is dependent on the bar metrics, be sure to specify a value for UIBarMetricsDefault.
 In the case of the segmented control, appearance properties for UIBarMetricsCompact are only respected for segmented controls in the smaller navigation and toolbars.
 */
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR; 
- (nullable UIImage *)backgroundImageForState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* To customize the segmented control appearance you will need to provide divider images to go between two unselected segments (leftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateNormal), selected on the left and unselected on the right (leftSegmentState:UIControlStateSelected rightSegmentState:UIControlStateNormal), and unselected on the left and selected on the right (leftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateSelected).
 */
- (void)setDividerImage:(nullable UIImage *)dividerImage forLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)dividerImageForLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState barMetrics:(UIBarMetrics)barMetrics  API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* You may specify the font, text color, and shadow properties for the title in the text attributes dictionary, using the keys found in NSAttributedString.h.
 */
- (void)setTitleTextAttributes:(nullable NSDictionary<NSAttributedStringKey,id> *)attributes forState:(UIControlState)state API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
- (nullable NSDictionary<NSAttributedStringKey,id> *)titleTextAttributesForState:(UIControlState)state API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* For adjusting the position of a title or image within the given segment of a segmented control.
 */
- (void)setContentPositionAdjustment:(UIOffset)adjustment forSegmentType:(UISegmentedControlSegment)leftCenterRightOrAlone barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR; 
- (UIOffset)contentPositionAdjustmentForSegmentType:(UISegmentedControlSegment)leftCenterRightOrAlone barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

@end

#if TARGET_OS_IOS
@interface UISegmentedControl (SpringLoading) <UISpringLoadedInteractionSupporting>
@end
#endif

NS_ASSUME_NONNULL_END


#else
#import <UIKitCore/UISegmentedControl.h>
#endif
