/*
	NSControl.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSView.h>
#import <AppKit/NSText.h>
#import <AppKit/NSCell.h>

NS_ASSUME_NONNULL_BEGIN

@class NSCell, NSFont, NSTextView, NSNotification, NSAttributedString, NSFormatter, NSControlAuxiliary;

@interface NSControl : NSView
{
    /*All instance variables are private*/
    NSControlAuxiliary *_aux;
    id		_cell;
    struct __conFlags {
        unsigned int enabled:1;
        unsigned int ignoreMultiClick:1;
        unsigned int calcSize:1;
        unsigned int drawingAncestor:1;
        unsigned int ibReserved:1;
        unsigned int updateCellFocus:1;
        unsigned int allowsLogicalLayoutDirection:1;
        unsigned int asmlwidth:1;
        unsigned int hsmlwidth:1;
        unsigned int dontValidate:1;
        unsigned int reserved:22;
    } _conFlags;
}

@property (nullable, weak) id target; // Target is weak for zeroing-weak compatible objects in apps linked on 10.10 or later. Otherwise the behavior of this property is 'assign’.
@property (nullable) SEL action;
@property NSInteger tag;
@property BOOL ignoresMultiClick;
@property (getter=isContinuous) BOOL continuous;
@property (getter=isEnabled) BOOL enabled;
@property BOOL refusesFirstResponder;
@property (getter=isHighlighted) BOOL highlighted NS_AVAILABLE_MAC(10_10);
@property NSControlSize controlSize NS_AVAILABLE_MAC(10_10);
@property (nullable, strong) __kindof NSFormatter *formatter;

@property (copy) NSString *stringValue;
@property (copy) NSAttributedString *attributedStringValue;
@property (nullable, copy) id  /* id<NSCopying> */ objectValue;
@property int intValue;
@property NSInteger integerValue;
@property float floatValue;
@property double doubleValue;


- (NSSize)sizeThatFits:(NSSize)size NS_AVAILABLE_MAC(10_10);
- (instancetype)initWithFrame:(NSRect)frameRect NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (void)sizeToFit;
- (NSInteger)sendActionOn:(NSInteger)mask;

- (BOOL)sendAction:(SEL)theAction to:(nullable id)theTarget;
- (void)takeIntValueFrom:(nullable id)sender;
- (void)takeFloatValueFrom:(nullable id)sender;
- (void)takeDoubleValueFrom:(nullable id)sender;
- (void)takeStringValueFrom:(nullable id)sender;
- (void)takeObjectValueFrom:(nullable id)sender;
- (void)takeIntegerValueFrom:(nullable id)sender NS_AVAILABLE_MAC(10_5);

- (void)mouseDown:(NSEvent *)theEvent;

@end

@interface NSControl(NSKeyboardUI)
- (void)performClick:(nullable id)sender;
@end


/* The following category applies only to controls with apparent textual content of some sort (buttons with labels, textfields, etc.).
 */
@interface NSControl(NSControlTextMethods)

@property NSTextAlignment alignment;
@property (nullable, copy) NSFont *font;
@property NSLineBreakMode lineBreakMode NS_AVAILABLE_MAC(10_10);
@property BOOL usesSingleLineMode NS_AVAILABLE_MAC(10_10);

@property NSWritingDirection baseWritingDirection;

/* Gets and sets the ability for expansion tool tips to be shown or not. Expansion tooltips are automatically shown when the cell can not show the full content. This is controlled by the NSCell API expansionFrameWithFrame:inView: and is drawn by drawWithExpansionFrame:inView:. The default value is NO.
    This value is encoded along with the control. In general, it is recommended to turn this on for NSTextFields in a View Based NSTableView.
 */
@property BOOL allowsExpansionToolTips NS_AVAILABLE_MAC(10_8);

/*  Allows the control to return an expansion tool tip frame if contentFrame is too small for the entire contents in the view. When the mouse is hovered over the text in certain controls, the full contents will be shown in a special floating tool tip view. If the frame is not too small, return an empty rect, and no expansion tool tip view will be shown. By default, NSControl returns NSZeroRect, while some subclasses (such as NSTextField) will return the proper frame when required.
 */
- (NSRect)expansionFrameWithFrame:(NSRect)contentFrame NS_AVAILABLE_MAC(10_10);

/* Allows the control to perform custom expansion tool tip drawing. Note that the view may be different from the original view that the text appeared in.
 */
- (void)drawWithExpansionFrame:(NSRect)contentFrame inView:(NSView *)view NS_AVAILABLE_MAC(10_10);

@end


/* The following category applies only to controls with editable text, like NSTextField.
 */
@interface NSControl(NSControlEditableTextMethods)
- (nullable NSText *)currentEditor;
- (BOOL)abortEditing;
- (void)validateEditing;

- (void)editWithFrame:(NSRect)aRect editor:(NSText *)textObj delegate:(nullable id)anObject event:(NSEvent *)theEvent NS_AVAILABLE_MAC(10_10);
- (void)selectWithFrame:(NSRect)aRect editor:(NSText *)textObj delegate:(nullable id)anObject start:(NSInteger)selStart length:(NSInteger)selLength NS_AVAILABLE_MAC(10_10);
- (void)endEditing:(NSText *)textObj NS_AVAILABLE_MAC(10_10);
@end


@interface NSObject(NSControlSubclassNotifications)
- (void)controlTextDidBeginEditing:(NSNotification *)obj;
- (void)controlTextDidEndEditing:(NSNotification *)obj;
- (void)controlTextDidChange:(NSNotification *)obj;
@end


@protocol NSControlTextEditingDelegate <NSObject>
@optional

// These delegate and notification methods are sent from NSControl subclasses that allow text editing such as NSTextField and NSMatrix.  The classes that need to send these have delegates.  NSControl does not.
- (BOOL)control:(NSControl *)control textShouldBeginEditing:(NSText *)fieldEditor;
- (BOOL)control:(NSControl *)control textShouldEndEditing:(NSText *)fieldEditor;
- (BOOL)control:(NSControl *)control didFailToFormatString:(NSString *)string errorDescription:(nullable NSString *)error;
- (void)control:(NSControl *)control didFailToValidatePartialString:(NSString *)string errorDescription:(nullable NSString *)error;
- (BOOL)control:(NSControl *)control isValidObject:(id)obj;

- (BOOL)control:(NSControl *)control textView:(NSTextView *)textView doCommandBySelector:(SEL)commandSelector;
- (NSArray<NSString *> *)control:(NSControl *)control textView:(NSTextView *)textView completions:(NSArray<NSString *> *)words forPartialWordRange:(NSRange)charRange indexOfSelectedItem:(NSInteger *)index;
@end

                                                                    // userInfo keys:
APPKIT_EXTERN NSString * NSControlTextDidBeginEditingNotification;	//	@"NSFieldEditor"
APPKIT_EXTERN NSString * NSControlTextDidEndEditingNotification;	//	@"NSFieldEditor"
APPKIT_EXTERN NSString * NSControlTextDidChangeNotification;		//	@"NSFieldEditor"


@interface NSControl (NSDeprecated)

// Use formatters instead.  See -[NSControl formatter] and -[NSControl setFormatter:].
- (void)setFloatingPointFormat:(BOOL)autoRange left:(NSUInteger)leftDigits right:(NSUInteger)rightDigits NS_DEPRECATED_MAC(10_0, 10_0);

+ (void)setCellClass:(nullable Class)factoryId;
+ (nullable Class)cellClass;

@property (nullable, strong) __kindof NSCell *cell;

- (nullable __kindof NSCell *)selectedCell;
- (NSInteger)selectedTag;

- (void)setNeedsDisplay;    // Use setNeedsDisplay:YES instead.
- (void)calcSize;

- (void)updateCell:(NSCell *)aCell;
- (void)updateCellInside:(NSCell *)aCell;
- (void)drawCellInside:(NSCell *)aCell;
- (void)drawCell:(NSCell *)aCell;
- (void)selectCell:(NSCell *)aCell;

@end

NS_ASSUME_NONNULL_END

