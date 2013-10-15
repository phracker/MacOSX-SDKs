/*
	NSForm.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSMatrix.h>

@class NSFormCell;

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
- (id)cellAtIndex:(NSInteger)index;
- (void)drawCellAtIndex:(NSInteger)index;
- (NSFormCell *)addEntry:(NSString *)title;
- (NSFormCell *)insertEntry:(NSString *)title atIndex:(NSInteger)index;
- (void)removeEntryAtIndex:(NSInteger)index;
- (NSInteger)indexOfCellWithTag:(NSInteger)aTag;
- (void)selectTextAtIndex:(NSInteger)index;
- (void)setFrameSize:(NSSize)newSize;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setTitleBaseWritingDirection:(NSWritingDirection)writingDirection;
- (void)setTextBaseWritingDirection:(NSWritingDirection)writingDirection;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
@end
