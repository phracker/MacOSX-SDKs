/*
	NSFormCell.h
	Application Kit
	Copyright (c) 1994-2013, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@interface NSFormCell : NSActionCell
{
    /*All instance variables are private*/
    CGFloat	_titleWidth;
    id		_titleCell;
    CGFloat	_titleEndPoint;
#if __LP64__
    CGFloat    _preferredTextFieldWidth;
#endif
}

- (id)initTextCell:(NSString *)aString;

- (CGFloat)titleWidth:(NSSize)aSize;
- (CGFloat)titleWidth;
- (void)setTitleWidth:(CGFloat)width;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSFont *)titleFont;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSTextAlignment)titleAlignment;
- (void)setTitleAlignment:(NSTextAlignment)mode;
- (BOOL)isOpaque;

- (void)setPreferredTextFieldWidth:(CGFloat)preferredWidth;
- (CGFloat)preferredTextFieldWidth;
- (void)setPlaceholderString:(NSString*)string;
- (NSString*)placeholderString;
- (void)setPlaceholderAttributedString:(NSAttributedString*)string;
- (NSAttributedString*)placeholderAttributedString;

- (NSWritingDirection)titleBaseWritingDirection;
- (void)setTitleBaseWritingDirection:(NSWritingDirection)writingDirection;


/* Determine the preferred width of the text field portion of the receiver. The preferred width is reflected in the cell's cellSize, which will be large enough to accommodate the title, bezel, and a text field of width preferredTextWidth. It is also reflected in the intrinsicContentSize of the NSForm. That is, under autolayout, the NSForm will try to size itself so that the text field cell is the given width, according to the usual content size constraint priorities.
 
 If the width is negative, the cellSize matches the historic behavior, which is that it is large enough to accommodate the title, bezel, and the current text. The default is -1.
 
 This method can aid migration to autolayout, and is sufficient for simple cases. However, for new apps, prefer to use NSTextFields directly instead of NSForm.
 */
- (void)setPreferredTextFieldWidth:(CGFloat)width NS_AVAILABLE_MAC(10_8);
- (CGFloat)preferredTextFieldWidth NS_AVAILABLE_MAC(10_8);

@end

@interface NSFormCell(NSKeyboardUI)
/* Deprecated in 10.8 and higher. Use setTitle: instead.
 */
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);
@end

@interface NSFormCell(NSFormCellAttributedStringMethods)
- (NSAttributedString *)attributedTitle;
- (void)setAttributedTitle:(NSAttributedString *)obj;
@end
