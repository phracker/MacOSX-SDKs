/*
	NSButton.h
	Application Kit
	Copyright (c) 1994-2014, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSButtonCell.h>
#import <AppKit/NSUserInterfaceValidation.h>

@class NSSound;

@interface NSButton : NSControl <NSUserInterfaceValidations, NSAccessibilityButton>

@property (copy) NSString *title;
@property (copy) NSString *alternateTitle;
@property (strong) NSImage *image;
@property (strong) NSImage *alternateImage;
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
@property (strong) NSSound *sound;
@end


@interface NSButton(NSKeyboardUI)

/* On 10.8, this method still will call setTitle: with the ampersand stripped from stringWithAmpersand, but does nothing else. Use setTitle directly.
 */
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

@end

