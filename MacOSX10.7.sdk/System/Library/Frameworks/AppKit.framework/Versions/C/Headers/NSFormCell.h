/*
	NSFormCell.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@interface NSFormCell : NSActionCell
{
    /*All instance variables are private*/
    CGFloat	_titleWidth;
    id		_titleCell;
    CGFloat	_titleEndPoint;
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

- (void)setPlaceholderString:(NSString*)string;
- (NSString*)placeholderString;
- (void)setPlaceholderAttributedString:(NSAttributedString*)string;
- (NSAttributedString*)placeholderAttributedString;

- (NSWritingDirection)titleBaseWritingDirection;
- (void)setTitleBaseWritingDirection:(NSWritingDirection)writingDirection;

@end

@interface NSFormCell(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
@end

@interface NSFormCell(NSFormCellAttributedStringMethods)
- (NSAttributedString *)attributedTitle;
- (void)setAttributedTitle:(NSAttributedString *)obj;
@end
