/*
	NSFormCell.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setPlaceholderString:(NSString*)string;
- (NSString*)placeholderString;
- (void)setPlaceholderAttributedString:(NSAttributedString*)string;
- (NSAttributedString*)placeholderAttributedString;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSWritingDirection)titleBaseWritingDirection;
- (void)setTitleBaseWritingDirection:(NSWritingDirection)writingDirection;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

@end

@interface NSFormCell(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
@end

@interface NSFormCell(NSFormCellAttributedStringMethods)
- (NSAttributedString *)attributedTitle;
- (void)setAttributedTitle:(NSAttributedString *)obj;
@end
