/*
    NSLevelIndicatorCell.h
    Application Kit
    Copyright (c) 2004-2005, Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <AppKit/NSActionCell.h>
#import <AppKit/NSSliderCell.h>

typedef enum {
    NSRelevancyLevelIndicatorStyle,
    NSContinuousCapacityLevelIndicatorStyle,
    NSDiscreteCapacityLevelIndicatorStyle,
    NSRatingLevelIndicatorStyle
} NSLevelIndicatorStyle;

@interface NSLevelIndicatorCell : NSActionCell {
  @private
    double _value;
    double _minValue;
    double _maxValue;
    double _warningValue;
    double _criticalValue;
    int    _numberOfTickMarks;
    int    _numberOfMajorTickMarks;
    struct {
	unsigned int indicatorStyle:4;
        unsigned int tickMarkPosition:1;
	unsigned int reserved:27;
    } _liFlags;
    NSRect _cellFrame;
    int    _reserved1;
    int    _reserved2;
    int    _reserved3;
    int    _reserved4;
}

- (id)initWithLevelIndicatorStyle:(NSLevelIndicatorStyle)levelIndicatorStyle;

- (NSLevelIndicatorStyle)levelIndicatorStyle;
- (void)setLevelIndicatorStyle:(NSLevelIndicatorStyle)levelIndicatorStyle;

- (double)minValue;
- (void)setMinValue:(double)minValue;

- (double)maxValue;
- (void)setMaxValue:(double)maxValue;

- (double)warningValue;
- (void)setWarningValue:(double)warningValue;

- (double)criticalValue;
- (void)setCriticalValue:(double)criticalValue;

- (void)setTickMarkPosition:(NSTickMarkPosition)position;
- (NSTickMarkPosition)tickMarkPosition;

- (void)setNumberOfTickMarks:(int)count;
- (int)numberOfTickMarks;

- (void)setNumberOfMajorTickMarks:(int)count;
- (int)numberOfMajorTickMarks;

- (NSRect)rectOfTickMarkAtIndex:(int)index;
- (double)tickMarkValueAtIndex:(int)index;

- (void)setImage:(NSImage*)image;

@end

#endif
