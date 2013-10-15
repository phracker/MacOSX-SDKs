/*
	NSSegmentedCell.h
	Application Kit
	Copyright (c) 2003-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h>
#import <AppKit/NSActionCell.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

typedef enum {
    NSSegmentSwitchTrackingSelectOne = 0,  // only one button can be selected
    NSSegmentSwitchTrackingSelectAny = 1,  // any button can be selected
    NSSegmentSwitchTrackingMomentary = 2   // only selected while tracking
} NSSegmentSwitchTracking;

@class NSMutableArray;

@interface NSSegmentedCell : NSActionCell {
  @private
    NSMutableArray* _segmentItems;
    int             _selectedSegment;
    int             _keySegment;
    NSRect          _lastBounds;
    struct {
	unsigned int trackingMode:3;
	unsigned int trimmedLabels:1;
	unsigned int drawing:1;
	unsigned int style:2;
	unsigned int recalcToolTips:1;
	unsigned int reserved:24;
    } _seFlags;
    unsigned int    _reserved1;
    unsigned int    _reserved2;
    unsigned int    _reserved3;
    unsigned int    _reserved4;
}

/* Number of segments
*/
- (void)setSegmentCount:(int)count;
- (int)segmentCount;

/* Which button is active. May turn off other segments depending on mode.
*/
- (void)setSelectedSegment:(int)selectedSegment;
- (int)selectedSegment;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)selectSegmentWithTag:(int)tag;
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
- (void)setWidth:(float)width forSegment:(int)segment;
- (float)widthForSegment:(int)segment;

- (void)setImage:(NSImage *)image forSegment:(int)segment;
- (NSImage *)imageForSegment:(int)segment;

- (void)setLabel:(NSString *)label forSegment:(int)segment;
- (NSString *)labelForSegment:(int)segment;

- (void)setSelected:(BOOL)selected forSegment:(int)segment;
- (BOOL)isSelectedForSegment:(int)segment;

- (void)setEnabled:(BOOL)enabled forSegment:(int)segment;
- (BOOL)isEnabledForSegment:(int)segment;

- (void)setMenu:(NSMenu *)menu forSegment:(int)segment;
- (NSMenu *)menuForSegment:(int)segment;

- (void)setToolTip:(NSString *)toolTip forSegment:(int)segment;
- (NSString *)toolTipForSegment:(int)segment;

- (void)setTag:(int)tag forSegment:(int)segment;
- (int)tagForSegment:(int)segment;

/* For custom content drawing. frame has been adjusted to content area
*/
- (void)drawSegment:(int)segment inFrame:(NSRect)frame withView:(NSView *)controlView;

@end

#endif
