/*
	NSFormCell.h
	Application Kit
	Copyright (c) 1994-2003, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@interface NSFormCell : NSActionCell
{
    /*All instance variables are private*/
    float	_titleWidth;
    id		_titleCell;
    float	_titleEndPoint;
}

- (id)initTextCell:(NSString *)aString;

- (float)titleWidth:(NSSize)aSize;
- (float)titleWidth;
- (void)setTitleWidth:(float)width;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSFont *)titleFont;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSTextAlignment)titleAlignment;
- (void)setTitleAlignment:(NSTextAlignment)mode;
- (BOOL)isOpaque;

@end

@interface NSFormCell(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
@end

@interface NSFormCell(NSFormCellAttributedStringMethods)
- (NSAttributedString *)attributedTitle;
- (void)setAttributedTitle:(NSAttributedString *)obj;
@end
