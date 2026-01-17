/*
    NSLevelIndicatorCell.h
    Application Kit
    Copyright (c) 2004-2018, Apple Inc.
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
    double _value APPKIT_IVAR;
    double _minValue APPKIT_IVAR;
    double _maxValue APPKIT_IVAR;
    double _warningValue APPKIT_IVAR;
    double _criticalValue APPKIT_IVAR;
    int    _numberOfTickMarks APPKIT_IVAR;
    int    _numberOfMajorTickMarks APPKIT_IVAR;
    struct {
        unsigned int indicatorStyle:4;
        unsigned int tickMarkPosition:1;
        unsigned int selectable:1;
        unsigned int placeholderVisibility:2;
        unsigned int tieredCapacity:1;
        unsigned int inTableView:1;
        unsigned int reserved:22;
    } _liFlags APPKIT_IVAR;
    NSRect _cellFrame APPKIT_IVAR;
    id     _aux APPKIT_IVAR;
    id     _core APPKIT_IVAR;
    int    _reserved1 __unused APPKIT_IVAR;
    int    _reserved2 __unused APPKIT_IVAR;
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

static const NSLevelIndicatorStyle NSRelevancyLevelIndicatorStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLevelIndicatorStyleRelevancy", 10_0, 10_14) = NSLevelIndicatorStyleRelevancy;
static const NSLevelIndicatorStyle NSContinuousCapacityLevelIndicatorStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLevelIndicatorStyleContinuousCapacity", 10_0, 10_14) = NSLevelIndicatorStyleContinuousCapacity;
static const NSLevelIndicatorStyle NSDiscreteCapacityLevelIndicatorStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLevelIndicatorStyleDiscreteCapacity", 10_0, 10_14) = NSLevelIndicatorStyleDiscreteCapacity;
static const NSLevelIndicatorStyle NSRatingLevelIndicatorStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSLevelIndicatorStyleRating", 10_0, 10_14) = NSLevelIndicatorStyleRating;

NS_ASSUME_NONNULL_END

