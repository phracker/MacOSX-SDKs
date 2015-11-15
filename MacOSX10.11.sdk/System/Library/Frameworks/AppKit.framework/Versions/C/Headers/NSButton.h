/*
	NSButton.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSButtonCell.h>
#import <AppKit/NSUserInterfaceValidation.h>

NS_ASSUME_NONNULL_BEGIN

@class NSSound;

@interface NSButton : NSControl <NSUserInterfaceValidations, NSAccessibilityButton>

@property (copy) NSString *title;
@property (copy) NSString *alternateTitle;
@property (nullable, strong) NSImage *image;
@property (nullable, strong) NSImage *alternateImage;
@property NSCellImagePosition imagePosition;
- (void)setButtonType:(NSButtonType)aType;
@property NSInteger state;
@property (getter=isBordered) BOOL bordered;
@property (getter=isTransparent) BOOL transparent;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
@property (copy) NSString *keyEquivalent;
@property NSUInteger keyEquivalentModifierMask;
- (void)highlight:(BOOL)flag;
- (BOOL)performKeyEquivalent:(NSEvent *)key;

@property (getter=isSpringLoaded) BOOL springLoaded NS_AVAILABLE_MAC(10_10_3); // sends action on deep-press or extended hover while dragging. Defaults to NO.
@property NSInteger maxAcceleratorLevel NS_AVAILABLE_MAC(10_10_3);	// Configures the maximum allowed level for an NSMultiLevelAcceleratorButton, allowed values range from [1,5]. Defaults to 2.

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

