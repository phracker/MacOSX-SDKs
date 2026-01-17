/*
	NSSegmentedCell.h
	Application Kit
	Copyright (c) 2003-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h>
#import <AppKit/NSActionCell.h>
#import <AppKit/NSSegmentedControl.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

enum {
    NSSegmentSwitchTrackingSelectOne = 0,  // only one button can be selected
    NSSegmentSwitchTrackingSelectAny = 1,  // any button can be selected
    NSSegmentSwitchTrackingMomentary = 2   // only selected while tracking
};
typedef NSUInteger NSSegmentSwitchTracking;

@class NSMutableArray;

@interface NSSegmentedCell : NSActionCell {
  @private
    NSMutableArray* _segmentItems;
    NSInteger           _selectedSegment;
    NSInteger           _keySegment;
    NSRect          _lastBounds;
    struct {
	unsigned int trackingMode:3;
	unsigned int trimmedLabels:1;
	unsigned int drawing:1;
	unsigned int reserved1:2;
	unsigned int recalcToolTips:1;
        unsigned int usesWindowsStyle:1;
        unsigned int dontShowSelectedAndPressedAppearance:1;
	unsigned int reserved0:1;
	unsigned int style:8;
	unsigned int reserved:13;
    } _seFlags;
    id		    _segmentTrackingInfo;
    NSInteger	    _reserved2;
    NSInteger	    _reserved3;
    NSInteger	    _reserved4;
}

/* Number of segments
*/
- (void)setSegmentCount:(NSInteger)count;
- (NSInteger)segmentCount;

/* Which button is active. May turn off other segments depending on mode.
*/
- (void)setSelectedSegment:(NSInteger)selectedSegment;
- (NSInteger)selectedSegment;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)selectSegmentWithTag:(NSInteger)tag;
#endif

/* For keyboard UI. Wraps.
*/
- (void)makeNextSegmentKey;
- (void)makePreviousSegmentKey;

- (void)setTrackingMode:(NSSegmentSwitchTracking)trackingMode;
- (NSSegmentSwitchTracking)trackingMode;


// per segment info

/* Width of 0 means autosize to fit
*/
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

- (void)setSelected:(BOOL)selected forSegment:(NSInteger)segment;
- (BOOL)isSelectedForSegment:(NSInteger)segment;

- (void)setEnabled:(BOOL)enabled forSegment:(NSInteger)segment;
- (BOOL)isEnabledForSegment:(NSInteger)segment;

- (void)setMenu:(NSMenu *)menu forSegment:(NSInteger)segment;
- (NSMenu *)menuForSegment:(NSInteger)segment;

- (void)setToolTip:(NSString *)toolTip forSegment:(NSInteger)segment;
- (NSString *)toolTipForSegment:(NSInteger)segment;

- (void)setTag:(NSInteger)tag forSegment:(NSInteger)segment;
- (NSInteger)tagForSegment:(NSInteger)segment;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* see NSSegmentedControl.h for segment style names and values */
- (void)setSegmentStyle:(NSSegmentStyle)segmentStyle;
- (NSSegmentStyle)segmentStyle;
#endif

/* For custom content drawing. frame has been adjusted to content area
*/
- (void)drawSegment:(NSInteger)segment inFrame:(NSRect)frame withView:(NSView *)controlView;

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@interface NSSegmentedCell (NSSegmentBackgroundStyle)
/* Describes the surface drawn onto in -[NSCell drawSegment:inFrame:withView:]. That method draws a segment interior, not the segment bezel.  This is both an override point and a useful method to call. A segmented cell that draws a custom bezel would override this to describe that surface. A cell that has custom segment drawing might query this method to help pick an image that looks good on the cell. Calling this method gives you some independence from changes in framework art style.
*/
- (NSBackgroundStyle)interiorBackgroundStyleForSegment:(NSInteger)segment;
@end

#endif

#endif
