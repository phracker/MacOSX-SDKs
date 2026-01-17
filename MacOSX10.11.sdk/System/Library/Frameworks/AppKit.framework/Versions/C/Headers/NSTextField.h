/*
	NSTextField.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSTextFieldCell.h>
#import <AppKit/NSUserInterfaceValidation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NSTextFieldDelegate;

@interface NSTextField : NSControl <NSUserInterfaceValidations, NSAccessibilityNavigableStaticText>
{
    /*All instance variables are private*/
    id _delegate;
    SEL _errorAction;
}

@property (nullable, copy) NSString *placeholderString NS_AVAILABLE_MAC(10_10);
@property (nullable, copy) NSAttributedString *placeholderAttributedString NS_AVAILABLE_MAC(10_10);

@property (nullable, copy) NSColor *backgroundColor;
@property BOOL drawsBackground;
@property (nullable, copy) NSColor *textColor;
@property (getter=isBordered) BOOL bordered;
@property (getter=isBezeled) BOOL bezeled;
@property (getter=isEditable) BOOL editable;
@property (getter=isSelectable) BOOL selectable;
- (void)selectText:(nullable id)sender;
@property (nullable, assign) id<NSTextFieldDelegate> delegate;
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

/* For text that wraps (see NSCell’s lineBreakMode), this property determines the maximum number of lines to display. A value of 0 means there is no limit, which is the default, and the text fills the cell’s bounds. If the text reaches the number of lines allowed, or the height of the container cannot accommodate the number of lines needed, the text will be clipped (or truncated if truncatesLastVisibleLine is set). The value of this property also affects -[NSControl sizeThatFits:], -[NSView fittingSize] and -[NSView intrinsicContentSize]. Most importantly, if the value of this property is not 1, multiple lines may be used to find the field’s intrinsicContentSize. Prior to 10.11, the intrinsicContentSize would be determined as if the maximumNumberOfLines was 1.
 */
@property NSInteger maximumNumberOfLines NS_AVAILABLE_MAC(10_11);

/* Maps to -[NSParagraphStyle allowsDefaultTighteningForTruncation] in rendering and sizing the text field. Ignored when the content value is an attributed string.
 */
@property BOOL allowsDefaultTighteningForTruncation NS_AVAILABLE_MAC(10_11);

@end

@interface NSTextField(NSTextFieldAttributedStringMethods)
@property BOOL allowsEditingTextAttributes;
@property BOOL importsGraphics;
@end

@protocol NSTextFieldDelegate <NSControlTextEditingDelegate>
@end

@interface NSTextField(NSDeprecated)

/* This method is deprecated in 10.8 and higher. Use setTitle: instead.
 */
- (void)setTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

@end

NS_ASSUME_NONNULL_END


