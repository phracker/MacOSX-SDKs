/*
    NSLevelIndicatorCell.h
    Application Kit
    Copyright (c) 2004-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSActionCell.h>
#import <AppKit/NSSliderCell.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSLevelIndicatorStyle) {
    NSRelevancyLevelIndicatorStyle,
    NSContinuousCapacityLevelIndicatorStyle,
    NSDiscreteCapacityLevelIndicatorStyle,
    NSRatingLevelIndicatorStyle
};

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
        unsigned int selectable:1;
	unsigned int ratingPlaceholder:1;
	unsigned int reserved:25;
    } _liFlags;
    NSRect _cellFrame;
    int    _reserved1;
    int    _reserved2;
    int    _reserved3;
    int    _reserved4;
}

- (instancetype)initWithLevelIndicatorStyle:(NSLevelIndicatorStyle)levelIndicatorStyle;

@property NSLevelIndicatorStyle levelIndicatorStyle;

@property double minValue;

@property double maxValue;

@property double warningValue;

@property double criticalValue;

@property NSTickMarkPosition tickMarkPosition;

@property NSInteger numberOfTickMarks;

@property NSInteger numberOfMajorTickMarks;

- (NSRect)rectOfTickMarkAtIndex:(NSInteger)index;
- (double)tickMarkValueAtIndex:(NSInteger)index;

- (void)setImage:(nullable NSImage*)image;

@end

NS_ASSUME_NONNULL_END

