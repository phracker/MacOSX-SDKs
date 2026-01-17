/*
        NSComboButton.h
        Application Kit
        Copyright (c) 2021-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSControl.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

API_AVAILABLE(macos(13.0))
typedef NS_ENUM(NSInteger, NSComboButtonStyle) {
    /// The button will be split across 2 segments. The leading segment shows `title`, `image`, or both. If `action` is set, it will be performed when the leading segment is clicked. If `action` is `nil`, the leading segment will be disabled. The trailing segment shows a menu indicator. If `menu` is set, clicking the trailing segment will show it. If `menu` is empty, the trailing segment will be disabled.
    NSComboButtonStyleSplit = 0,
    
    /// The button will be unified in a single segment. If `action` is set, `menu` will appear on click and hold. If `action` is `nil`, then `menu` will appear on click.
    NSComboButtonStyleUnified = 1
} NS_SWIFT_NAME(NSComboButton.Style);

API_AVAILABLE(macos(13.0))
@interface NSComboButton : NSControl

/*!
 Creates a standard combo button with a title, menu, and primary action.
 @param title The localized title string that is displayed on the button.
 @param menu The additional menu to display on the button.
 @param target The target object that receives primary action messages from the control.
 @param action The action message sent by the primary action portion of the control.
 */
+ (instancetype)comboButtonWithTitle:(NSString *)title menu:(nullable NSMenu *)menu target:(nullable id)target action:(nullable SEL)action;

/*!
 Creates a standard combo button with a image, menu, and primary action.
 @param image The image to display in the body of the button.
 @param menu The additional menu to display on the button.
 @param target The target object that receives primary action messages from the control.
 @param action The action message sent by the primary action portion of the control.
 */
+ (instancetype)comboButtonWithImage:(NSImage *)image menu:(nullable NSMenu *)menu target:(nullable id)target action:(nullable SEL)action;

/*!
 Creates a standard combo button with a title, image, menu, and primary action.
 @param title The localized title string that is displayed on the button.
 @param image The image to display in the body of the button.
 @param menu The additional menu to display on the button.
 @param target The target object that receives primary action messages from the control.
 @param action The action message sent by the primary action portion of the control.
 */
+ (instancetype)comboButtonWithTitle:(NSString *)title image:(NSImage *)image menu:(nullable NSMenu *)menu target:(nullable id)target action:(nullable SEL)action;

/*! The title displayed on the control. The default value is an empty string.  */
@property (copy) NSString *title;

/*! The image displayed on the control. The default value is `nil`. */
@property (nullable, strong) NSImage *image;

/*! The scaling mode applied to fit the button's image within the content area. The default value is `NSImageScaleProportionallyDown`. */
@property NSImageScaling imageScaling;

/*! Overrides behavior of NSResponder menu. This menu is shown when interacting with the button (see NSComboButtonStyle). NSComboButton does not have a context menu. Items in this menu specify their own target and action independent of the primary action that is configured on the control. */
@property (strong) NSMenu *menu;

/*! Specifies the visual presentation and behavior for NSComboButton's primary action and its menu. The default value is `NSComboButtonStyleSplit`. */
@property NSComboButtonStyle style;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
