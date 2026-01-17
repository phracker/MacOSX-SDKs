/*
	NSButton.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSButtonCell.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSUserInterfaceCompression.h>

NS_ASSUME_NONNULL_BEGIN

@class NSSound;

@interface NSButton : NSControl <NSUserInterfaceValidations, NSAccessibilityButton, NSUserInterfaceCompression>

@property (copy) NSString *title;
@property (copy) NSString *alternateTitle;
@property (nullable, strong) NSImage *image;
@property (nullable, strong) NSImage *alternateImage;
@property NSCellImagePosition imagePosition;
@property NSImageScaling imageScaling NS_AVAILABLE_MAC(10_5);
@property BOOL imageHugsTitle API_AVAILABLE(macosx(10.12));

- (void)setButtonType:(NSButtonType)type;
@property NSControlStateValue state;
@property (getter=isBordered) BOOL bordered;
@property (getter=isTransparent) BOOL transparent;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
@property (copy) NSString *keyEquivalent;
@property NSEventModifierFlags keyEquivalentModifierMask;
- (void)highlight:(BOOL)flag;
- (BOOL)performKeyEquivalent:(NSEvent *)key;

@property (getter=isSpringLoaded) BOOL springLoaded NS_AVAILABLE_MAC(10_10_3); // sends action on deep-press or extended hover while dragging. Defaults to NO.
@property NSInteger maxAcceleratorLevel NS_AVAILABLE_MAC(10_10_3);	// Configures the maximum allowed level for an NSMultiLevelAcceleratorButton, allowed values range from [1,5]. Defaults to 2.

/*! Applies a custom color to the button's bezel, in appearances that support it. A nil value indicates an unmodified button appearance. The default value is nil. */
@property (nullable, copy) NSColor *bezelColor NS_AVAILABLE_MAC(10_12_2);

/*! Applies a tint color to template image and text content, in combination with other theme-appropriate effects. Only applicable to borderless buttons. A nil value indicates the standard set of effects without color modification. The default value is nil. Non-template images and attributed string values are not affected by the contentTintColor. */
@property (nullable, copy) NSColor *contentTintColor NS_AVAILABLE_MAC(10_14);

- (void)compressWithPrioritizedCompressionOptions:(NSArray<NSUserInterfaceCompressionOptions *> *)prioritizedOptions NS_AVAILABLE_MAC(10_13);
- (NSSize)minimumSizeWithPrioritizedCompressionOptions:(NSArray<NSUserInterfaceCompressionOptions *> *)prioritizedOptions NS_AVAILABLE_MAC(10_13);
@property (readonly, copy) NSUserInterfaceCompressionOptions *activeCompressionOptions NS_AVAILABLE_MAC(10_13);

@end


@interface NSButton(NSButtonConvenience)

/*!
 Creates a standard push button with a title and image.
 @param title The localized title string that is displayed on the button.
 @param image The image that is displayed alongside the title. In left-to-right localizations, the image is displayed to the left of the title. In right-to-left localizations, it is displayed to the right.
 @param target The target object that receives action messages from the control.
 @param action The action message sent by the control.
 @return An initialized button object.
 */
+ (instancetype)buttonWithTitle:(NSString *)title image:(NSImage *)image target:(nullable id)target action:(nullable SEL)action NS_AVAILABLE_MAC(10_12);

/*!
 Creates a standard push button with the provided title.
 @param title The localized title string that is displayed on the button.
 @param target The target object that receives action messages from the control.
 @param action The action message sent by the control.
 @return An initialized button object.
 */
+ (instancetype)buttonWithTitle:(NSString *)title target:(nullable id)target action:(nullable SEL)action NS_AVAILABLE_MAC(10_12);

/*!
 Creates a standard push button with the provided image. Set the image's accessibilityDescription property to ensure accessibility for this control.
 @param image The image to display in the body of the button.
 @param target The target object that receives action messages from the control.
 @param action The action message sent by the control.
 @return An initialized button object.
 */
+ (instancetype)buttonWithImage:(NSImage *)image target:(nullable id)target action:(nullable SEL)action NS_AVAILABLE_MAC(10_12);

/*!
 Creates a standard checkbox with the provided title.
 @param title The localized title string that is displayed alongside the checkbox.
 @param target The target object that receives action messages from the control.
 @param action The action message sent by the control.
 @return An initialized button object.
 */
+ (instancetype)checkboxWithTitle:(NSString *)title target:(nullable id)target action:(nullable SEL)action NS_AVAILABLE_MAC(10_12);

/*!
 Creates a standard radio button with the provided title.
 @param title The localized title string that is displayed alongside the radio button.
 @param target The target object that receives action messages from the control.
 @param action The action message sent by the control.
 @return An initialized button object.
 */
+ (instancetype)radioButtonWithTitle:(NSString *)title target:(nullable id)target action:(nullable SEL)action NS_AVAILABLE_MAC(10_12);

@end

@interface NSButton(NSButtonAttributedStringMethods)
@property (copy) NSAttributedString *attributedTitle;
@property (copy) NSAttributedString *attributedAlternateTitle;
@end

@interface NSButton(NSButtonBezelStyles)
@property NSBezelStyle bezelStyle;
@end

@interface NSButton(NSButtonMixedState)
@property BOOL allowsMixedState;
- (void)setNextState;
@end

@interface NSButton(NSButtonBorder)
@property BOOL showsBorderOnlyWhileMouseInside;
@end

@interface NSButton (NSButtonSoundExtensions)
@property (nullable, strong) NSSound *sound;
@end


@interface NSButton(NSKeyboardUI)

/* On 10.8, this method still will call setTitle: with the ampersand stripped from stringWithAmpersand, but does nothing else. Use setTitle directly.
 */
- (void)setTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

@end

NS_ASSUME_NONNULL_END

