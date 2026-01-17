/*
	NSTextField.h
	Application Kit
	Copyright (c) 1994-2024, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSTextFieldCell.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSTextContent.h>
#import <AppKit/NSParagraphStyle.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@protocol NSTextFieldDelegate;

@interface NSTextField : NSControl <NSUserInterfaceValidations, NSAccessibilityNavigableStaticText, NSTextContent>

@property (nullable, copy) NSString *placeholderString API_AVAILABLE(macos(10.10));
@property (nullable, copy) NSAttributedString *placeholderAttributedString API_AVAILABLE(macos(10.10));

@property (nullable, copy) NSColor *backgroundColor;
@property BOOL drawsBackground;
@property (nullable, copy) NSColor *textColor;
@property (getter=isBordered) BOOL bordered;
@property (getter=isBezeled) BOOL bezeled;
@property (getter=isEditable) BOOL editable;
@property (getter=isSelectable) BOOL selectable;
- (void)selectText:(nullable id)sender;
@property (nullable, weak) id<NSTextFieldDelegate> delegate;
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;
@property (readonly) BOOL acceptsFirstResponder;

@property NSTextFieldBezelStyle bezelStyle;

/* The preferredMaxLayoutWidth determines the maximum width of the intrinsicContentSize. If the text field wraps, the intrinsic height will be large enough to show the entire text contents at that width. The default is 0, which implies no maximum preferred width.
 */
@property CGFloat preferredMaxLayoutWidth API_AVAILABLE(macos(10.8));

/* For text that wraps (see NSCell’s lineBreakMode), this property determines the maximum number of lines to display. A value of 0 means there is no limit, which is the default, and the text fills the cell’s bounds. If the text reaches the number of lines allowed, or the height of the container cannot accommodate the number of lines needed, the text will be clipped (or truncated if truncatesLastVisibleLine is set). The value of this property also affects -[NSControl sizeThatFits:], -[NSView fittingSize] and -[NSView intrinsicContentSize]. Most importantly, if the value of this property is not 1, multiple lines may be used to find the field’s intrinsicContentSize. Prior to 10.11, the intrinsicContentSize would be determined as if the maximumNumberOfLines was 1.
 */
@property NSInteger maximumNumberOfLines API_AVAILABLE(macos(10.11));

/* Maps to -[NSParagraphStyle allowsDefaultTighteningForTruncation] in rendering and sizing the text field. Ignored when the content value is an attributed string.
 */
@property BOOL allowsDefaultTighteningForTruncation API_AVAILABLE(macos(10.11));

#if !TARGET_OS_IPHONE
/* Specifies the line break strategies that may be used for laying out the text in this text field.  If this property is not set, the default for non-editable and selectable text fields is NSLineBreakStrategyStandard and the default for editable text fields is NSLineBreakStrategyNone. If the text field contains an attributed string value with paragraph style(s) that specify a set of line break strategies, the set of strategies in the paragraph style(s) will be used instead of the set of strategies defined by this property. */
@property NSLineBreakStrategy lineBreakStrategy API_AVAILABLE(macos(10.15));
#endif

@property BOOL allowsWritingTools API_AVAILABLE(macos(15.2)); // Default is YES. Configures its field editor to work with Writing Tools.
@property BOOL allowsWritingToolsAffordance API_AVAILABLE(macos(15.4)); // Default is NO.

/* An array of NSStrings that will be animated to cycle through one by one when the textField is first responder. No animation happend when there is only string in the array, or when text field is not first responder. The text field's placeholderString property points to the first string in placeholderStrings.
 */
@property (copy) NSArray<NSString *> *placeholderStrings API_AVAILABLE(macos(26.0));

/* An array of NSStrings that will be animated to cycle through one by one when the textField is first responder. No animation happend when there is only string in the array, or when text field is not first responder. The text field's placeholderString property points to the first string in placeholderStrings.
 */
@property (copy) NSArray<NSAttributedString *> *placeholderAttributedStrings API_AVAILABLE(macos(26.0));

/// Specifies the behavior for resolving ``NSTextAlignment.natural`` to the visual alignment.
///
/// When set to ``true``, the resolved visual alignment is determined by the resolved base writing direction; otherwise, it is using the user’s preferred language.
/// The default value is ``false``.
@property BOOL resolvesNaturalAlignmentWithBaseWritingDirection API_AVAILABLE(macos(26.0));
@end

#pragma mark NSTextField NSTouchBar Properties
@interface NSTextField (NSTouchBar)

@property (getter=isAutomaticTextCompletionEnabled) BOOL automaticTextCompletionEnabled API_AVAILABLE(macos(10.12.2));
@property BOOL allowsCharacterPickerTouchBarItem API_AVAILABLE(macos(10.12.2));

@end

@interface NSTextField(NSTextFieldConvenience)

/*!
 Creates a non-wrapping, non-editable, non-selectable text field that displays text in the default system font.
 @param stringValue The title text to display in the field.
 @return An initialized text field object.
 */
+ (instancetype)labelWithString:(NSString *)stringValue API_AVAILABLE(macos(10.12));

/*!
 Creates a wrapping, non-editable, selectable text field that displays text in the default system font.
 @param stringValue The title text to display in the field.
 @return An initialized text field object.
 */
+ (instancetype)wrappingLabelWithString:(NSString *)stringValue API_AVAILABLE(macos(10.12));

/*!
 Creates a non-editable, non-selectable text field that displays attributed text.
 The line break mode of this field is determined by the attributed string's NSParagraphStyle attribute.
 @param attributedStringValue The attributed string to display in the field.
 @return An initialized text field object.
 */
+ (instancetype)labelWithAttributedString:(NSAttributedString *)attributedStringValue API_AVAILABLE(macos(10.12));

/*!
 Creates a non-wrapping editable text field.
 @param stringValue The initial contents of the text field, or empty string for an initially empty text field.
 @return An initialized text field object.
 */
+ (instancetype)textFieldWithString:(NSString *)stringValue API_AVAILABLE(macos(10.12));

@end

@interface NSTextField(NSTextFieldAttributedStringMethods)
@property BOOL allowsEditingTextAttributes;
@property BOOL importsGraphics;
@end

@protocol NSTextFieldDelegate <NSControlTextEditingDelegate>

@optional

/// Provides a customized list of candidates to the text view’s `candidateListTouchBarItem`. Invoked from `-updateCandidates`. `NSTextView` uses the candidates returned from this method and suppress its built-in candidate generation. Returning `nil` from this delegate method allows `NSTextView` to query candidates from `NSSpellChecker`.
/// - Returns: An array of objects that represent the elements of a selection.
- (nullable NSArray *)textField:(NSTextField *)textField textView:(NSTextView *)textView candidatesForSelectedRange:(NSRange)selectedRange NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.12.2));

/// Allows customizing the candidate list queried from `NSSpellChecker`.
/// - Returns: An array of text objects to include in a text selection.
- (NSArray<NSTextCheckingResult *> *)textField:(NSTextField *)textField textView:(NSTextView *)textView candidates:(NSArray<NSTextCheckingResult *> *)candidates forSelectedRange:(NSRange)selectedRange NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.12.2));

/// Notifies the delegate that the user selected the candidate at index in `-[NSCandidateListTouchBarItem candidates]` for the text view’s `candidateListTouchBarItem`. Returns a Boolean value that indicates whether to select the text object at the index.
/// - Parameters:
///   - textField: The text field that sent the message.
///   - textView: The text view that sent the message.
///   - index: The index that represents the start of the candidate text to evaluate, or `NSNotFound` if no candidate is to be selected.
/// - Returns: `YES` if the framework selects the text. `YES` allows `textView` to insert the candidate into the text storage if it’s `NSString`, `NSAttributedString`, or `NSTextCheckingResult`.
- (BOOL)textField:(NSTextField *)textField textView:(NSTextView *)textView shouldSelectCandidateAtIndex:(NSUInteger)index NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.12.2));

@end

@interface NSTextField(NSDeprecated)

- (void)setTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand API_DEPRECATED("Use `-setTitle:` instead", macos(10.0, 10.8));

@end




API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)


