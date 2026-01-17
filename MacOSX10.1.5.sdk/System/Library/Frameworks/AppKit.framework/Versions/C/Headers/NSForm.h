/*
	NSForm.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSMatrix.h>

@class NSFormCell;

@interface  NSForm : NSMatrix

- (int)indexOfSelectedItem;
- (void)setEntryWidth:(float)width;
- (void)setInterlineSpacing:(float)spacing;
- (void)setBordered:(BOOL)flag;
- (void)setBezeled:(BOOL)flag;
- (void)setTitleAlignment:(NSTextAlignment)mode;
- (void)setTextAlignment:(int)mode;
- (void)setTitleFont:(NSFont *)fontObj;
- (void)setTextFont:(NSFont *)fontObj;
- (id)cellAtIndex:(int)index;
- (void)drawCellAtIndex:(int)index;
- (NSFormCell *)addEntry:(NSString *)title;
- (NSFormCell *)insertEntry:(NSString *)title atIndex:(int)index;
- (void)removeEntryAtIndex:(int)index;
- (int)indexOfCellWithTag:(int)aTag;
- (void)selectTextAtIndex:(int)index;

@end
