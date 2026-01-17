/*
	NSForm.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSMatrix.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFormCell;

NS_CLASS_DEPRECATED_MAC(10_0, 10_10, "Use NSTextField directly instead, and consider NSStackView for layout assistance")
@interface  NSForm : NSMatrix

- (NSInteger)indexOfSelectedItem;
- (void)setEntryWidth:(CGFloat)width;
- (void)setInterlineSpacing:(CGFloat)spacing;
- (void)setBordered:(BOOL)flag;
- (void)setBezeled:(BOOL)flag;
- (void)setTitleAlignment:(NSTextAlignment)mode;
- (void)setTextAlignment:(NSTextAlignment)mode;
- (void)setTitleFont:(NSFont *)fontObj;
- (void)setTextFont:(NSFont *)fontObj;
- (null_unspecified id)cellAtIndex:(NSInteger)index;
- (void)drawCellAtIndex:(NSInteger)index;
- (NSFormCell *)addEntry:(NSString *)title;
- (null_unspecified NSFormCell *)insertEntry:(NSString *)title atIndex:(NSInteger)index;
- (void)removeEntryAtIndex:(NSInteger)index;
- (NSInteger)indexOfCellWithTag:(NSInteger)aTag;
- (void)selectTextAtIndex:(NSInteger)index;
- (void)setFrameSize:(NSSize)newSize;
- (void)setTitleBaseWritingDirection:(NSWritingDirection)writingDirection;
- (void)setTextBaseWritingDirection:(NSWritingDirection)writingDirection;

/* Determine the preferred width of the text field portion of the receiver's cells. The preferred width is reflected in the cell's cellSize, which will be large enough to accommodate the title, bezel, and a text field of width preferredTextWidth. It is also reflected in the intrinsicContentSize of the NSForm. That is, under autolayout, the NSForm will try to size itself so that the text field cell is the given width, according to the usual content size constraint priorities.
 
 If the width is negative, the cellSize matches the historic behavior, which is that it is large enough to accommodate the title, bezel, and the current text. The default is -1.

 This method can aid migration to autolayout, and is sufficient for simple cases. However, for new apps, prefer to use NSTextFields directly instead of NSForm.
*/
- (void)setPreferredTextFieldWidth:(CGFloat)preferredWidth NS_AVAILABLE_MAC(10_8);
- (CGFloat)preferredTextFieldWidth NS_AVAILABLE_MAC(10_8);

@end

NS_ASSUME_NONNULL_END
