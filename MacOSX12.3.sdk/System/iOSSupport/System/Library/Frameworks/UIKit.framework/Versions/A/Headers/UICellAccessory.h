#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICellAccessory.h>)
//
//  UICellAccessory.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIView;
@class UIImage;
@class UIColor;
@class UIFont;

typedef NS_ENUM(NSInteger, UICellAccessoryDisplayedState) {
    /// The accessory is always displayed.
    UICellAccessoryDisplayedAlways,
    /// The accessory is displayed only when the cell is editing.
    UICellAccessoryDisplayedWhenEditing,
    /// The accessory is displayed only when the cell is not editing.
    UICellAccessoryDisplayedWhenNotEditing
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// A special constant that can be set to the `reservedLayoutWidth` property. This requests the
/// system standard layout width.
UIKIT_EXTERN const CGFloat UICellAccessoryStandardDimension API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));


/// Abstract base class. Do not instantiate directly.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessory : NSObject <NSCopying, NSSecureCoding>

/// The state(s) for which the accessory should be displayed.
@property (nonatomic) UICellAccessoryDisplayedState displayedState;

/// Hidden accessories take up space in the layout, but are not visible and do not provide any behaviors.
/// Use this property to achieve a consistent layout across cells when some show the accessory and others do not.
@property (nonatomic, getter=isHidden) BOOL hidden;

/// The layout width that is reserved for the accessory, inside which the accessory will be centered.
/// This is used to ensure horizontal alignment of different accessories in adjacent cells, even when
/// the actual accessory view width varies slightly. A value of 0 means the actual width of the
/// accessory will be used. Use UICellAccessoryStandardDimension to request the standard width.
@property (nonatomic) CGFloat reservedLayoutWidth;

/// The tint color to apply to the accessory. Default value is nil, which uses the system default.
@property (nonatomic, strong, nullable) UIColor *tintColor;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end


/// A disclosure chevron that points in the trailing direction.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryDisclosureIndicator : UICellAccessory
@end


/// A detail (info) button.
UIKIT_EXTERN API_AVAILABLE(ios(15.4), tvos(15.4), watchos(8.5)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryDetail : UICellAccessory

/// An optional handler to call when the detail accessory is tapped. If nil, taps on the accessory are ignored.
@property (nonatomic, copy, nullable) void (^actionHandler)(void);

@end


/// A checkmark with default green color.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryCheckmark : UICellAccessory
@end


/// A delete control (minus sign inside a circle) with default red color.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryDelete : UICellAccessory

/// The background color to apply to the accessory. Default value is nil, which uses the system default.
@property (nonatomic, strong, nullable) UIColor *backgroundColor;

/// An optional handler to call when the delete accessory is tapped. If nil, a tap will reveal any trailing swipe actions for the cell.
@property (nonatomic, copy, nullable) void (^actionHandler)(void);

@end


/// An insert control (plus sign inside a circle) with default green color.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryInsert : UICellAccessory

/// The background color to apply to the accessory. Default value is nil, which uses the system default.
@property (nonatomic, strong, nullable) UIColor *backgroundColor;

/// An optional handler to call when the insert accessory is tapped. If nil, taps on the accessory are ignored.
@property (nonatomic, copy, nullable) void (^actionHandler)(void);

@end


/// A reorder control (three horizontal lines) with default gray color that automatically initiates interactive
/// reordering on the collection view when dragged (if supported).
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryReorder : UICellAccessory

/// Whether a vertical separator is displayed before the accessory when it is placed after another accessory. Default is YES.
@property (nonatomic) BOOL showsVerticalSeparator;

@end


/// A two-state control whose appearance follows the selection state of the cell (empty circle when deselected,
/// filled circle with checkmark when selected).
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryMultiselect : UICellAccessory

/// The background color to apply to the accessory. Default value is nil, which uses the system default.
@property (nonatomic, strong, nullable) UIColor *backgroundColor;

@end


typedef NS_ENUM(NSInteger, UICellAccessoryOutlineDisclosureStyle) {
    /// The style will be automatically determined based on whether the cell is configured to be a section header or not.
    UICellAccessoryOutlineDisclosureStyleAutomatic,
    /// A style appropriate for a section header, where a tap anywhere in the header will toggle the expansion state
    /// of the item (the cell cannot be selected).
    UICellAccessoryOutlineDisclosureStyleHeader,
    /// A style appropriate for a cell which can be selected itself and also has nested children, where only taps on the
    /// outline disclosure will toggle the expansion state of the item; taps on the cell will select the item as normal.
    UICellAccessoryOutlineDisclosureStyleCell
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/// A rotating disclosure chevron for use with outlines, used to indicate and toggle the expanded/collapsed state of the item.
UIKIT_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryOutlineDisclosure : UICellAccessory

/// The style of the outline disclosure accessory. Default is automatic.
@property (nonatomic) UICellAccessoryOutlineDisclosureStyle style;

/// An optional handler to call when the outline disclosure accessory is tapped. If nil, the default behavior when using
/// a NSDiffableDataSourceSectionSnapshot is to toggle the expand/collapse state of the item in the section snapshot.
@property (nonatomic, copy, nullable) void (^actionHandler)(void);

@end


/// A label displaying a short string of text, typically a small number such as a count for the associated item.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryLabel : UICellAccessory

/// Creates a new label accessory using the provided text.
- (instancetype)initWithText:(NSString *)text NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, readonly) NSString *text;

/// The font used for the label. Default is the preferred font for UIFontTextStyleBody.
@property (nonatomic, strong) UIFont *font;

/// Whether the label automatically adjusts its font based on the content size category. Default is YES.
@property (nonatomic) BOOL adjustsFontForContentSizeCategory;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


typedef NS_ENUM(NSInteger, UICellAccessoryPlacement) {
    /// Accessory placed on the leading edge.
    UICellAccessoryPlacementLeading,
    /// Accessory placed on the trailing edge.
    UICellAccessoryPlacementTrailing
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// Return an index to insert the accessory at, given an array of the existing accessories on the edge (in leading to trailing order).
typedef NSUInteger (^UICellAccessoryPosition)(NSArray<__kindof UICellAccessory *> *accessories) API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// Positions the accessory before the accessory matching the class specified, or at the beginning if not found.
UIKIT_EXTERN UICellAccessoryPosition UICellAccessoryPositionBeforeAccessoryOfClass(Class accessoryClass) API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));
/// Positions the accessory after the accessory matching the class specified, or at the end if not found.
UIKIT_EXTERN UICellAccessoryPosition UICellAccessoryPositionAfterAccessoryOfClass(Class accessoryClass) API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));


/// An accessory using a custom view.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0)) NS_SWIFT_UI_ACTOR
@interface UICellAccessoryCustomView : UICellAccessory

/// Creates a new custom view accessory using the provided view and specified placement. The custom view must have translatesAutoresizingMaskIntoConstraints
/// enabled, but may use auto layout constraints internally for layout of subviews and/or to indicate its preferred size.
- (instancetype)initWithCustomView:(UIView *)customView placement:(UICellAccessoryPlacement)placement NS_DESIGNATED_INITIALIZER;

@property (nonatomic, strong, readonly) UIView *customView;
@property (nonatomic, readonly) UICellAccessoryPlacement placement;

/// Whether the current frame size of the view is preserved (YES), or whether it is sized during layout of accessories (NO). Default is NO.
@property (nonatomic) BOOL maintainsFixedSize;

/// Allows customizing the relative position of the accessory amongst any other accessories displayed on the same edge.
/// The default is to insert the accessory at a position closest to the inside of the cell.
@property (nonatomic, copy, null_resettable) UICellAccessoryPosition position;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UICellAccessory.h>
#endif
