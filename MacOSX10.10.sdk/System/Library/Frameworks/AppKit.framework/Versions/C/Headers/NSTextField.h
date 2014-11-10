/*
	NSTextField.h
	Application Kit
	Copyright (c) 1994-2014, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSTextFieldCell.h>
#import <AppKit/NSUserInterfaceValidation.h>

@protocol NSTextFieldDelegate;

@interface NSTextField : NSControl <NSUserInterfaceValidations, NSAccessibilityNavigableStaticText>
{
    /*All instance variables are private*/
    id	_delegate;
    SEL	_errorAction;
#if __LP64__
    CGFloat _maxLayoutWidth;
#endif
}

@property (copy) NSString *placeholderString NS_AVAILABLE_MAC(10_10);
@property (copy) NSAttributedString *placeholderAttributedString NS_AVAILABLE_MAC(10_10);

@property (copy) NSColor *backgroundColor;
@property BOOL drawsBackground;
@property (copy) NSColor *textColor;
@property (getter=isBordered) BOOL bordered;
@property (getter=isBezeled) BOOL bezeled;
@property (getter=isEditable) BOOL editable;
@property (getter=isSelectable) BOOL selectable;
- (void)selectText:(id)sender;
@property (assign) id<NSTextFieldDelegate> delegate;
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;
@property (readonly) BOOL acceptsFirstResponder;

@property NSTextFieldBezelStyle bezelStyle;

/* The preferredMaxLayoutWidth determines the maximum width of the intrinsicContentSize. If the text field wraps, the intrinsic height will be large enough to show the entire text contents at that width. The default is 0, which implies no maximum preferred width.
 */
@property CGFloat preferredMaxLayoutWidth NS_AVAILABLE_MAC(10_8);

@end

@interface NSTextField(NSTextFieldAttributedStringMethods)
@property BOOL allowsEditingTextAttributes;
@property BOOL importsGraphics;
@end

@protocol NSTextFieldDelegate <NSControlTextEditingDelegate> @end

@interface NSTextField(NSDeprecated)

/* This method is deprecated in 10.8 and higher. Use setTitle: instead.
 */
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

@end


