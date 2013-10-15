/*
	NSSegmentedControl.h
	Application Kit
	Copyright (c) 2003-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSCell.h>


@class NSImage;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
enum {
    NSSegmentStyleAutomatic = 0, //Appearance is chosen depending on the type of window and the control's position inside it
    NSSegmentStyleRounded = 1,
    NSSegmentStyleRoundRect = 3,
    NSSegmentStyleTexturedSquare = 4,
    NSSegmentStyleSmallSquare = 6
};
#endif

typedef NSInteger NSSegmentStyle;

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

- (BOOL)selectSegmentWithTag:(NSInteger)tag;

- (void)setWidth:(CGFloat)width forSegment:(NSInteger)segment;
- (CGFloat)widthForSegment:(NSInteger)segment;

- (void)setImage:(NSImage *)image forSegment:(NSInteger)segment;
- (NSImage *)imageForSegment:(NSInteger)segment;


- (void)setImageScaling:(NSImageScaling)scaling forSegment:(NSInteger)segment NS_AVAILABLE_MAC(10_5);
- (NSImageScaling)imageScalingForSegment:(NSInteger)segment NS_AVAILABLE_MAC(10_5);


- (void)setLabel:(NSString *)label forSegment:(NSInteger)segment;
- (NSString *)labelForSegment:(NSInteger)segment;

- (void)setMenu:(NSMenu *)menu forSegment:(NSInteger)segment;
- (NSMenu *)menuForSegment:(NSInteger)segment;

- (void)setSelected:(BOOL)selected forSegment:(NSInteger)segment;
- (BOOL)isSelectedForSegment:(NSInteger)segment;

- (void)setEnabled:(BOOL)enabled forSegment:(NSInteger)segment;
- (BOOL)isEnabledForSegment:(NSInteger)segment;

- (void)setSegmentStyle:(NSSegmentStyle)segmentStyle NS_AVAILABLE_MAC(10_5);
- (NSSegmentStyle)segmentStyle NS_AVAILABLE_MAC(10_5);

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* In Mac OS X 10.7, the following styles have artwork identical with NSSegmentStyleTexturedSquare, and their usage is discouraged.  Prefer to use NSSegmentStyleTexturedSquare because it has the correct metrics for this artwork. */
enum {
    NSSegmentStyleTexturedRounded = 2,
    NSSegmentStyleCapsule = 5
};
#endif
