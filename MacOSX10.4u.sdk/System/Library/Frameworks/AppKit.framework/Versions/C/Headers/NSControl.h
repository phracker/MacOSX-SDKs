/*
	NSControl.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSText.h>

@class NSCell, NSFont, NSTextView, NSNotification, NSAttributedString, NSFormatter;

@interface NSControl : NSView
{
    /*All instance variables are private*/
    int	_tag;
    id	_cell;
    struct __conFlags {
	unsigned int        enabled:1;
	unsigned int        ignoreMultiClick:1;
	unsigned int        calcSize:1;
	unsigned int        drawingAncestor:1;
        unsigned int	    ibReserved:1;
	unsigned int        updateCellFocus:1;
        unsigned int        deallocating:1;
	unsigned int        reserved:25;
    } _conFlags;
}

+ (void)setCellClass:(Class)factoryId;
+ (Class)cellClass;

- (id)initWithFrame:(NSRect)frameRect;
- (void)sizeToFit;
- (void)calcSize;
- (id)cell;
- (void)setCell:(NSCell *)aCell;
- (id)selectedCell;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (int)tag;
- (void)setTag:(int)anInt;
- (int)selectedTag;
- (void)setIgnoresMultiClick:(BOOL)flag;
- (BOOL)ignoresMultiClick;
- (int)sendActionOn:(int)mask;
- (BOOL)isContinuous;
- (void)setContinuous:(BOOL)flag;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;
- (void)setFloatingPointFormat:(BOOL)autoRange left:(unsigned)leftDigits right:(unsigned)rightDigits;
- (NSTextAlignment)alignment;
- (void)setAlignment:(NSTextAlignment)mode;
- (NSFont *)font;
- (void)setFont:(NSFont *)fontObj;
- (void)setFormatter:(NSFormatter *)newFormatter;
- (id)formatter;
- (void)setObjectValue:(id<NSCopying>)obj;
- (void)setStringValue:(NSString *)aString;
- (void)setIntValue:(int)anInt;
- (void)setFloatValue:(float)aFloat;
- (void)setDoubleValue:(double)aDouble;
- (id)objectValue;
- (NSString *)stringValue;
- (int)intValue;
- (float)floatValue;
- (double)doubleValue;
- (void)setNeedsDisplay;
- (void)updateCell:(NSCell *)aCell;
- (void)updateCellInside:(NSCell *)aCell;
- (void)drawCellInside:(NSCell *)aCell;
- (void)drawCell:(NSCell *)aCell;
- (void)selectCell:(NSCell *)aCell;

- (BOOL)sendAction:(SEL)theAction to:(id)theTarget;
- (void)takeIntValueFrom:(id)sender;
- (void)takeFloatValueFrom:(id)sender;
- (void)takeDoubleValueFrom:(id)sender;
- (void)takeStringValueFrom:(id)sender;
- (void)takeObjectValueFrom:(id)sender;
- (NSText *)currentEditor;
- (BOOL)abortEditing;
- (void)validateEditing;
- (void)mouseDown:(NSEvent *)theEvent;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSWritingDirection)baseWritingDirection;
- (void)setBaseWritingDirection:(NSWritingDirection)writingDirection;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
@end

@interface NSControl(NSKeyboardUI)
- (void)performClick:sender;
- (void)setRefusesFirstResponder:(BOOL)flag;
- (BOOL)refusesFirstResponder;
@end

@interface NSObject(NSControlSubclassNotifications)

- (void)controlTextDidBeginEditing:(NSNotification *)obj;
- (void)controlTextDidEndEditing:(NSNotification *)obj;
- (void)controlTextDidChange:(NSNotification *)obj;

@end



@interface NSObject(NSControlSubclassDelegate)

// These delegate and notification methods are sent from NSControl subclasses that allow text editing such as NSTextField and NSMatrix.  The classes that need to send these have delegates.  NSControl does not.

- (BOOL)control:(NSControl *)control textShouldBeginEditing:(NSText *)fieldEditor;
- (BOOL)control:(NSControl *)control textShouldEndEditing:(NSText *)fieldEditor;
- (BOOL)control:(NSControl *)control didFailToFormatString:(NSString *)string errorDescription:(NSString *)error;
- (void)control:(NSControl *)control didFailToValidatePartialString:(NSString *)string errorDescription:(NSString *)error;
- (BOOL)control:(NSControl *)control isValidObject:(id)obj;

- (BOOL)control:(NSControl *)control textView:(NSTextView *)textView doCommandBySelector:(SEL)commandSelector;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSArray *)control:(NSControl *)control textView:(NSTextView *)textView completions:(NSArray *)words forPartialWordRange:(NSRange)charRange indexOfSelectedItem:(int *)index;
#endif
@end

								// userInfo keys:
APPKIT_EXTERN NSString *NSControlTextDidBeginEditingNotification;	//	@"NSFieldEditor"
APPKIT_EXTERN NSString *NSControlTextDidEndEditingNotification;	//	@"NSFieldEditor"
APPKIT_EXTERN NSString *NSControlTextDidChangeNotification;		//	@"NSFieldEditor"

@interface NSControl(NSControlAttributedStringMethods)
- (NSAttributedString *)attributedStringValue;
- (void)setAttributedStringValue:(NSAttributedString *)obj;
@end
