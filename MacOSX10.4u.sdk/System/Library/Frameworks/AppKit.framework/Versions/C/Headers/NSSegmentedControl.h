/*
	NSSegmentedControl.h
	Application Kit
	Copyright (c) 2003-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@class NSImage;

@interface NSSegmentedControl : NSControl {
  @private
    unsigned int _reserved1;
    unsigned int _reserved2;
    unsigned int _reserved3;
    unsigned int _reserved4;
}

- (void)setSegmentCount:(int)count;
- (int)segmentCount;

- (void)setSelectedSegment:(int)selectedSegment;
- (int)selectedSegment;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)selectSegmentWithTag:(int)tag;
#endif

- (void)setWidth:(float)width forSegment:(int)segment;
- (float)widthForSegment:(int)segment;

- (void)setImage:(NSImage *)image forSegment:(int)segment;
- (NSImage *)imageForSegment:(int)segment;

- (void)setLabel:(NSString *)label forSegment:(int)segment;
- (NSString *)labelForSegment:(int)segment;

- (void)setMenu:(NSMenu *)menu forSegment:(int)segment;
- (NSMenu *)menuForSegment:(int)segment;

- (void)setSelected:(BOOL)selected forSegment:(int)segment;
- (BOOL)isSelectedForSegment:(int)segment;

- (void)setEnabled:(BOOL)enabled forSegment:(int)segment;
- (BOOL)isEnabledForSegment:(int)segment;

@end

#endif
