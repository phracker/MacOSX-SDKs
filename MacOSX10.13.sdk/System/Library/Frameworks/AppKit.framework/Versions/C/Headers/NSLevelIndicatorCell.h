/*
    NSLevelIndicatorCell.h
    Application Kit
    Copyright (c) 2004-2017, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSActionCell.h>
#import <AppKit/NSSliderCell.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSLevelIndicatorStyle) {
    NSLevelIndicatorStyleRelevancy,
    NSLevelIndicatorStyleContinuousCapacity,
    NSLevelIndicatorStyleDiscreteCapacity,
    NSLevelIndicatorStyleRating
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
        unsigned int placeholderVisibility:2;
        unsigned int tieredCapacity:1;
        unsigned int inTableView:1;
        unsigned int reserved:22;
    } _liFlags;
    NSRect _cellFrame;
    id     _aux;
    id     _core;
    int    _reserved1 __unused;
    int    _reserved2 __unused;
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

@end

/* Legacy style names. These constants will be deprecated in a future release. */
static const NSLevelIndicatorStyle NSRelevancyLevelIndicatorStyle = NSLevelIndicatorStyleRelevancy;
static const NSLevelIndicatorStyle NSContinuousCapacityLevelIndicatorStyle = NSLevelIndicatorStyleContinuousCapacity;
static const NSLevelIndicatorStyle NSDiscreteCapacityLevelIndicatorStyle = NSLevelIndicatorStyleDiscreteCapacity;
static const NSLevelIndicatorStyle NSRatingLevelIndicatorStyle = NSLevelIndicatorStyleRating;

NS_ASSUME_NONNULL_END

