#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITableViewCell.h>)
//
//  UITableViewCell.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIColor, UILabel, UIImageView, UIButton, UITextField, UITableView, UILongPressGestureRecognizer;

typedef NS_ENUM(NSInteger, UITableViewCellStyle) {
    UITableViewCellStyleDefault,	// Simple cell with text label and optional image view (behavior of UITableViewCell in iPhoneOS 2.x)
    UITableViewCellStyleValue1,		// Left aligned label on left and right aligned label on right with blue text (Used in Settings)
    UITableViewCellStyleValue2,		// Right aligned label on left with blue text and left aligned label on right (Used in Phone/Contacts)
    UITableViewCellStyleSubtitle	// Left aligned label on top and left aligned label on bottom with gray text (Used in iPod).
};             // available in iPhone OS 3.0

typedef NS_ENUM(NSInteger, UITableViewCellSeparatorStyle) {
    UITableViewCellSeparatorStyleNone,
    UITableViewCellSeparatorStyleSingleLine,
    UITableViewCellSeparatorStyleSingleLineEtched NS_ENUM_DEPRECATED_IOS(2_0, 11_0, "Use UITableViewCellSeparatorStyleSingleLine for a single line separator.")
} API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, UITableViewCellSelectionStyle) {
    UITableViewCellSelectionStyleNone,
    UITableViewCellSelectionStyleBlue,
    UITableViewCellSelectionStyleGray,
    UITableViewCellSelectionStyleDefault API_AVAILABLE(ios(7.0))
};

typedef NS_ENUM(NSInteger, UITableViewCellFocusStyle) {
    UITableViewCellFocusStyleDefault,
    UITableViewCellFocusStyleCustom
} API_AVAILABLE(ios(9.0));

typedef NS_ENUM(NSInteger, UITableViewCellEditingStyle) {
    UITableViewCellEditingStyleNone,
    UITableViewCellEditingStyleDelete,
    UITableViewCellEditingStyleInsert
};

typedef NS_ENUM(NSInteger, UITableViewCellAccessoryType) {
    UITableViewCellAccessoryNone,                                                      // don't show any accessory view
    UITableViewCellAccessoryDisclosureIndicator,                                       // regular chevron. doesn't track
    UITableViewCellAccessoryDetailDisclosureButton API_UNAVAILABLE(tvos),                 // info button w/ chevron. tracks
    UITableViewCellAccessoryCheckmark,                                                 // checkmark. doesn't track
    UITableViewCellAccessoryDetailButton API_AVAILABLE(ios(7.0))  API_UNAVAILABLE(tvos) // info button. tracks
};

typedef NS_OPTIONS(NSUInteger, UITableViewCellStateMask) {
    UITableViewCellStateDefaultMask                     = 0,
    UITableViewCellStateShowingEditControlMask          = 1 << 0,
    UITableViewCellStateShowingDeleteConfirmationMask   = 1 << 1
};

typedef NS_ENUM(NSInteger, UITableViewCellDragState) {
    UITableViewCellDragStateNone,
    UITableViewCellDragStateLifting, // The cell is lifting from the table view before it joins the drag session.
    UITableViewCellDragStateDragging // The cell is involved in a drag session.
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

#define UITableViewCellStateEditingMask UITableViewCellStateShowingEditControlMask

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UITableViewCell : UIView <NSCoding, UIGestureRecognizerDelegate>

// Designated initializer.  If the cell can be reused, you must pass in a reuse identifier.  You should use the same reuse identifier for all cells of the same form.  
- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(nullable NSString *)reuseIdentifier API_AVAILABLE(ios(3.0)) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// Content.  These properties provide direct access to the internal label and image views used by the table view cell.  These should be used instead of the content properties below.
@property (nonatomic, readonly, strong, nullable) UIImageView *imageView API_AVAILABLE(ios(3.0));   // default is nil.  image view will be created if necessary.

@property (nonatomic, readonly, strong, nullable) UILabel *textLabel API_AVAILABLE(ios(3.0));   // default is nil.  label will be created if necessary.
@property (nonatomic, readonly, strong, nullable) UILabel *detailTextLabel API_AVAILABLE(ios(3.0)); // default is nil.  label will be created if necessary (and the current style supports a detail label).

// If you want to customize cells by simply adding additional views, you should add them to the content view so they will be positioned appropriately as the cell transitions into and out of editing mode.
@property (nonatomic, readonly, strong) UIView *contentView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'backgroundView' will be added as a subview behind all other views.
@property (nonatomic, strong, nullable) UIView *backgroundView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'selectedBackgroundView' will be added as a subview directly above the backgroundView if not nil, or behind all other views. It is added as a subview only when the cell is selected. Calling -setSelected:animated: will cause the 'selectedBackgroundView' to animate in and out with an alpha fade.
@property (nonatomic, strong, nullable) UIView *selectedBackgroundView;

// If not nil, takes the place of the selectedBackgroundView when using multiple selection.
@property (nonatomic, strong, nullable) UIView *multipleSelectionBackgroundView API_AVAILABLE(ios(5.0));

@property (nonatomic, readonly, copy, nullable) NSString *reuseIdentifier;
- (void)prepareForReuse NS_REQUIRES_SUPER;                                                        // if the cell is reusable (has a reuse identifier), this is called just before the cell is returned from the table view method dequeueReusableCellWithIdentifier:.  If you override, you MUST call super.

@property (nonatomic) UITableViewCellSelectionStyle   selectionStyle;             // default is UITableViewCellSelectionStyleDefault.
@property (nonatomic, getter=isSelected) BOOL         selected;                   // set selected state (title, image, background). default is NO. animated is NO
@property (nonatomic, getter=isHighlighted) BOOL      highlighted;                // set highlighted state (title, image, background). default is NO. animated is NO
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;                     // animate between regular and selected state
- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated;               // animate between regular and highlighted state

@property (nonatomic, readonly) UITableViewCellEditingStyle editingStyle;         // default is UITableViewCellEditingStyleNone. This is set by UITableView using the delegate's value for cells who customize their appearance accordingly.
@property (nonatomic) BOOL                            showsReorderControl;        // default is NO
@property (nonatomic) BOOL                            shouldIndentWhileEditing;   // default is YES.  This is unrelated to the indentation level below.

@property (nonatomic) UITableViewCellAccessoryType    accessoryType;              // default is UITableViewCellAccessoryNone. use to set standard type
@property (nonatomic, strong, nullable) UIView       *accessoryView;              // if set, use custom view. ignore accessoryType. tracks if enabled can calls accessory action
@property (nonatomic) UITableViewCellAccessoryType    editingAccessoryType;       // default is UITableViewCellAccessoryNone. use to set standard type
@property (nonatomic, strong, nullable) UIView       *editingAccessoryView;       // if set, use custom view. ignore editingAccessoryType. tracks if enabled can calls accessory action

@property (nonatomic) NSInteger                       indentationLevel;           // adjust content indent. default is 0
@property (nonatomic) CGFloat                         indentationWidth;           // width for each level. default is 10.0
@property (nonatomic) UIEdgeInsets                    separatorInset API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos); // allows customization of the separator frame

@property (nonatomic, getter=isEditing) BOOL          editing;                    // show appropriate edit controls (+/- & reorder). By default -setEditing: calls setEditing:animated: with NO for animated.
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

@property(nonatomic, readonly) BOOL                   showingDeleteConfirmation;  // currently showing "Delete" button

@property (nonatomic) UITableViewCellFocusStyle       focusStyle API_AVAILABLE(ios(9.0)) UI_APPEARANCE_SELECTOR;

// These methods can be used by subclasses to animate additional changes to the cell when the cell is changing state
// Note that when the cell is swiped, the cell will be transitioned into the UITableViewCellStateShowingDeleteConfirmationMask state,
// but the UITableViewCellStateShowingEditControlMask will not be set.
- (void)willTransitionToState:(UITableViewCellStateMask)state API_AVAILABLE(ios(3.0));
- (void)didTransitionToState:(UITableViewCellStateMask)state API_AVAILABLE(ios(3.0));

/* Override this method to receive notifications that the cell's drag state has changed.
 * Call super if you want to apply the default appearance.
 */
- (void)dragStateDidChange:(UITableViewCellDragState)dragState API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/* Controls whether the cell in the table view allows user interaction once it is part of a drag (UITableViewCellDragStateDragging).
 * Default is NO.
 */
@property (nonatomic) BOOL userInteractionEnabledWhileDragging API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@end

@interface UITableViewCell (UIDeprecated)

// Frame is ignored.  The size will be specified by the table view width and row height.
- (id)initWithFrame:(CGRect)frame reuseIdentifier:(nullable NSString *)reuseIdentifier API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);

// Content properties.  These properties were deprecated in iPhone OS 3.0.  The textLabel and imageView properties above should be used instead.
// For selected attributes, set the highlighted attributes on the textLabel and imageView.
@property (nonatomic, copy, nullable)   NSString *text API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);                        // default is nil
@property (nonatomic, strong, nullable) UIFont   *font API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);                        // default is nil (Use default font)
@property (nonatomic) NSTextAlignment   textAlignment API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);               // default is UITextAlignmentLeft
@property (nonatomic) NSLineBreakMode   lineBreakMode API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);               // default is UILineBreakModeTailTruncation
@property (nonatomic, strong, nullable) UIColor  *textColor API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);                   // default is nil (text draws black)
@property (nonatomic, strong, nullable) UIColor  *selectedTextColor API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);           // default is nil (text draws white)

@property (nonatomic, strong, nullable) UIImage  *image API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);                       // default is nil. appears on left next to title.
@property (nonatomic, strong, nullable) UIImage  *selectedImage API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);               // default is nil

// Use the new editingAccessoryType and editingAccessoryView instead
@property (nonatomic) BOOL              hidesAccessoryWhenEditing API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);   // default is YES

// Use the table view data source method -tableView:commitEditingStyle:forRowAtIndexPath: or the table view delegate method -tableView:accessoryButtonTappedForRowWithIndexPath: instead
@property (nonatomic, assign, nullable) id        target API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);                      // target for insert/delete/accessory clicks. default is nil (i.e. go up responder chain). weak reference
@property (nonatomic, nullable) SEL               editAction API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);                  // action to call on insert/delete call. set by UITableView
@property (nonatomic, nullable) SEL               accessoryAction API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);             // action to call on accessory view clicked. set by UITableView

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITableViewCell.h>
#endif
