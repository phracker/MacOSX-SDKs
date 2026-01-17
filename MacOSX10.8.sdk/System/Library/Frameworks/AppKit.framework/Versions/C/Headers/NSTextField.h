/*
	NSTextField.h
	Application Kit
	Copyright (c) 1994-2012, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSTextFieldCell.h>
#import <AppKit/NSUserInterfaceValidation.h>

@protocol NSTextFieldDelegate;

@interface NSTextField : NSControl <NSUserInterfaceValidations>
{
    /*All instance variables are private*/
    id	_delegate;
    SEL	_errorAction;
#if __LP64__
    CGFloat _maxLayoutWidth;
#endif
}

- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setDrawsBackground:(BOOL)flag;
- (BOOL)drawsBackground;
- (void)setTextColor:(NSColor *)color;
- (NSColor *)textColor;
- (BOOL)isBordered;
- (void)setBordered:(BOOL)flag;
- (BOOL)isBezeled;
- (void)setBezeled:(BOOL)flag;
- (BOOL)isEditable;
- (void)setEditable:(BOOL)flag;
- (BOOL)isSelectable;
- (void)setSelectable:(BOOL)flag;
- (void)selectText:(id)sender;
- (id <NSTextFieldDelegate>)delegate;
- (void)setDelegate:(id <NSTextFieldDelegate>)anObject;
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;
- (BOOL)acceptsFirstResponder;

- (void)setBezelStyle:(NSTextFieldBezelStyle)style;
- (NSTextFieldBezelStyle)bezelStyle;

/* The preferredMaxLayoutWidth determines the maximum width of the intrinsicContentSize. If the text field wraps, the intrinsic height will be large enough to show the entire text contents at that width. The default is 0, which implies no maximum preferred width.
 */
- (void)setPreferredMaxLayoutWidth:(CGFloat)width NS_AVAILABLE_MAC(10_8);
- (CGFloat)preferredMaxLayoutWidth NS_AVAILABLE_MAC(10_8);

@end

@interface NSTextField(NSTextFieldAttributedStringMethods)
- (BOOL)allowsEditingTextAttributes;
- (void)setAllowsEditingTextAttributes:(BOOL)flag;
- (BOOL)importsGraphics;
- (void)setImportsGraphics:(BOOL)flag;
@end

@protocol NSTextFieldDelegate <NSControlTextEditingDelegate> @end

@interface NSTextField(NSDeprecated)

/* This method is deprecated in 10.8 and higher. Use setTitle: instead.
 */
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

@end


