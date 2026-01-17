/*
 NSColorPickerTouchBarItem.h
 Application Kit
 Copyright (c) 2016-2018, Apple Inc.
 All rights reserved.
*/

#import <AppKit/NSTouchBarItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSViewController, NSColor, NSImage, NSString, NSColorList, NSColorSpace;

NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSColorPickerTouchBarItem : NSTouchBarItem {
@private
    id _overlay APPKIT_IVAR;
    NSString *_customizationLabel APPKIT_IVAR;
    NSColor *_color APPKIT_IVAR;
    __weak id _target APPKIT_IVAR;
    SEL _action APPKIT_IVAR;
    NSInteger _mode APPKIT_IVAR;
    NSView *_view APPKIT_IVAR;
    NSString *_buttonTitle APPKIT_IVAR;
    NSImage *_buttonImage APPKIT_IVAR;
    NSColorList *_colorList APPKIT_IVAR;
    id _autounbinder APPKIT_IVAR;
    NSArray<NSColorSpace *> *_allowedColorSpaces APPKIT_IVAR;
    signed char _showsAlpha:1 APPKIT_IVAR;
    signed char _supportsPressAndHoldVariants:1 APPKIT_IVAR;
    signed char _enabled:1 APPKIT_IVAR;
#if !__OBJC2__
    unsigned int _colorPickerTouchBarItemReservedFlags:29 __unused APPKIT_IVAR;
    void *_colorPickerTouchBarItemReserved[3] __unused APPKIT_IVAR;
#endif /* !__OBJC2__ */
}

/// Creates a bar item containing a button with the standard color picker icon that invokes the color picker.
+ (instancetype)colorPickerWithIdentifier:(NSTouchBarItemIdentifier)identifier;
/// Creates a bar item containing a button with the standard text color picker icon that invokes the color picker. Should be used when the item is used for picking text colors.
+ (instancetype)textColorPickerWithIdentifier:(NSTouchBarItemIdentifier)identifier;
/// Creates a bar item containing a button with the standard stroke color picker icon that invokes the color picker. Should be used when the item is used for picking stroke colors.
+ (instancetype)strokeColorPickerWithIdentifier:(NSTouchBarItemIdentifier)identifier;

/// Creates a bar item containing a button with the provided image that invokes the color picker.
+ (instancetype)colorPickerWithIdentifier:(NSTouchBarItemIdentifier)identifier buttonImage:(NSImage *)image;

/// The selected color of the picker.
@property (copy) NSColor *color;

/// Whether or not the picker should allow picking a color with non-1.0 alpha. Defaults to `!NSColor.ignoresAlpha`.
@property BOOL showsAlpha;

/// Controls the color spaces that the receiver is able to produce. If a color outside of the allowed spaces are displayed or selected, it will first be converted to the first color space in the array. `nil` signifies any color space is allowed. Empty array is an invalid value and will raise an exception if set. Defaults to `nil`.
@property (copy, nullable) NSArray<NSColorSpace *> *allowedColorSpaces NS_AVAILABLE_MAC(10_13);

/// The color list displayed in the list color picker. Defaults to the standard system color list. Setting a custom color list will disable the additional tints/shades that appear on long-press.
@property (strong, null_resettable) NSColorList *colorList;

/// The localized string labelling this item during user customization. The default value is the localized string of "Color Picker".
@property (readwrite, copy, null_resettable) NSString *customizationLabel;

@property (weak, nullable) id target;
@property (nullable) SEL action;

/// Enables or disabled the color picker. If it is currently being shown in a popover, it will be dismissed.
@property (getter=isEnabled) BOOL enabled;

@end

NS_ASSUME_NONNULL_END
