/*
	NSTextField.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSTextFieldCell.h>

@interface NSTextField : NSControl
{
    /*All instance variables are private*/
    id	_delegate;
    SEL	_errorAction;
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
- (id)delegate;
- (void)setDelegate:(id)anObject;
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;
- (BOOL)acceptsFirstResponder;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)setBezelStyle:(NSTextFieldBezelStyle)style;
- (NSTextFieldBezelStyle)bezelStyle;
#endif
@end

@interface NSTextField(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
@end

@interface NSTextField(NSTextFieldAttributedStringMethods)
- (BOOL)allowsEditingTextAttributes;
- (void)setAllowsEditingTextAttributes:(BOOL)flag;
- (BOOL)importsGraphics;
- (void)setImportsGraphics:(BOOL)flag;
@end
