/*
	NSSegmentedControl.h
	Application Kit
	Copyright (c) 2003-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSCell.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@class NSImage;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
enum {
    NSSegmentStyleAutomatic = 0, //Appearance is chosen depending on the type of window and the control's position inside it
    NSSegmentStyleRounded = 1,
    NSSegmentStyleTexturedRounded = 2,
    NSSegmentStyleRoundRect = 3,
    NSSegmentStyleTexturedSquare = 4,
    NSSegmentStyleCapsule = 5,
    NSSegmentStyleSmallSquare = 6
};

typedef NSInteger NSSegmentStyle;
#endif

@interface NSSegmentedControl : NSControl {
  @private
    NSInteger _reserved1;
    NSInteger _reserved2;
    NSInteger _reserved3;
    NSInteger _reserved4;
}

- (void)setSegmentCount:(NSInteger)count;
- (NSInteger)segmentCount;

- (void)setSelectedSegment:(NSInteger)selectedSegment;
- (NSInteger)selectedSegment;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)selectSegmentWithTag:(NSInteger)tag;
#endif

- (void)setWidth:(CGFloat)width forSegment:(NSInteger)segment;
- (CGFloat)widthForSegment:(NSInteger)segment;

- (void)setImage:(NSImage *)image forSegment:(NSInteger)segment;
- (NSImage *)imageForSegment:(NSInteger)segment;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

- (void)setImageScaling:(NSImageScaling)scaling forSegment:(NSInteger)segment;
- (NSImageScaling)imageScalingForSegment:(NSInteger)segment;

#endif

- (void)setLabel:(NSString *)label forSegment:(NSInteger)segment;
- (NSString *)labelForSegment:(NSInteger)segment;

- (void)setMenu:(NSMenu *)menu forSegment:(NSInteger)segment;
- (NSMenu *)menuForSegment:(NSInteger)segment;

- (void)setSelected:(BOOL)selected forSegment:(NSInteger)segment;
- (BOOL)isSelectedForSegment:(NSInteger)segment;

- (void)setEnabled:(BOOL)enabled forSegment:(NSInteger)segment;
- (BOOL)isEnabledForSegment:(NSInteger)segment;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)setSegmentStyle:(NSSegmentStyle)segmentStyle;
- (NSSegmentStyle)segmentStyle;
#endif

@end

#endif
