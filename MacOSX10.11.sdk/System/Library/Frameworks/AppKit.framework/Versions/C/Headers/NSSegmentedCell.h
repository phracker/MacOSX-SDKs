/*
    NSSegmentedCell.h
    Application Kit
    Copyright (c) 2003-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSGeometry.h>
#import <AppKit/NSActionCell.h>
#import <AppKit/NSSegmentedControl.h>

NS_ASSUME_NONNULL_BEGIN

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
        unsigned int menuShouldBeUniquedAgainstMain:1;
        unsigned int style:8;
        unsigned int flatMinX:1;
        unsigned int flatMaxX:1;
        unsigned int segmentedSeparated:1;
        unsigned int reserved:10;
    } _seFlags;
    id           _segmentTrackingInfo;
    id           _menuUniquer;
    NSInteger    _reserved3;
    NSInteger    _reserved4;
}

/* Number of segments
*/
@property NSInteger segmentCount;

/* Which button is active. May turn off other segments depending on mode.
*/
@property NSInteger selectedSegment;

- (BOOL)selectSegmentWithTag:(NSInteger)tag;

/* For keyboard UI. Wraps.
*/
- (void)makeNextSegmentKey;
- (void)makePreviousSegmentKey;

@property NSSegmentSwitchTracking trackingMode;


// per segment info

/* Width of 0 means autosize to fit
*/
- (void)setWidth:(CGFloat)width forSegment:(NSInteger)segment;
- (CGFloat)widthForSegment:(NSInteger)segment;

- (void)setImage:(nullable NSImage *)image forSegment:(NSInteger)segment;
- (nullable NSImage *)imageForSegment:(NSInteger)segment;


- (void)setImageScaling:(NSImageScaling)scaling forSegment:(NSInteger)segment NS_AVAILABLE_MAC(10_5);
- (NSImageScaling)imageScalingForSegment:(NSInteger)segment NS_AVAILABLE_MAC(10_5);


- (void)setLabel:(NSString *)label forSegment:(NSInteger)segment;
- (nullable NSString *)labelForSegment:(NSInteger)segment;

- (void)setSelected:(BOOL)selected forSegment:(NSInteger)segment;
- (BOOL)isSelectedForSegment:(NSInteger)segment;

- (void)setEnabled:(BOOL)enabled forSegment:(NSInteger)segment;
- (BOOL)isEnabledForSegment:(NSInteger)segment;

- (void)setMenu:(nullable NSMenu *)menu forSegment:(NSInteger)segment;
- (nullable NSMenu *)menuForSegment:(NSInteger)segment;

- (void)setToolTip:(nullable NSString *)toolTip forSegment:(NSInteger)segment;
- (nullable NSString *)toolTipForSegment:(NSInteger)segment;

- (void)setTag:(NSInteger)tag forSegment:(NSInteger)segment;
- (NSInteger)tagForSegment:(NSInteger)segment;

/* see NSSegmentedControl.h for segment style names and values */
@property NSSegmentStyle segmentStyle NS_AVAILABLE_MAC(10_5);

/* For custom content drawing. frame has been adjusted to content area
*/
- (void)drawSegment:(NSInteger)segment inFrame:(NSRect)frame withView:(NSView *)controlView;

@end

@interface NSSegmentedCell (NSSegmentBackgroundStyle)
/* Describes the surface drawn onto in -[NSCell drawSegment:inFrame:withView:]. That method draws a segment interior, not the segment bezel.  This is both an override point and a useful method to call. A segmented cell that draws a custom bezel would override this to describe that surface. A cell that has custom segment drawing might query this method to help pick an image that looks good on the cell. Calling this method gives you some independence from changes in framework art style.
*/
- (NSBackgroundStyle)interiorBackgroundStyleForSegment:(NSInteger)segment NS_AVAILABLE_MAC(10_5);
@end

NS_ASSUME_NONNULL_END

