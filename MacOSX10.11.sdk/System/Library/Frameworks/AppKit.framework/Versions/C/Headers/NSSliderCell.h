/*
	NSSliderCell.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

typedef NS_ENUM(NSUInteger, NSTickMarkPosition) {
    NSTickMarkBelow = 0,
    NSTickMarkAbove = 1,
    NSTickMarkLeft  = NSTickMarkAbove,
    NSTickMarkRight = NSTickMarkBelow
};

typedef NS_ENUM(NSUInteger, NSSliderType) {
    NSLinearSlider   = 0,
    NSCircularSlider = 1
};

@interface NSSliderCell : NSActionCell
{
    /*All instance variables are private*/
    id       _sliderCellPrivateData;
    CGFloat  _previousValue;
    CGFloat  _knobOffset;
    int      _numberOfTickMarks;
    double	_altIncValue;
    double	_value;
    double	_maxValue;
    double	_minValue;
    NSRect	_trackRect;
    struct __sliderCellFlags {
        unsigned int weAreVertical:1;
        unsigned int weAreVerticalSet:1;
        unsigned int reserved1:1;
        unsigned int isPressed:1;
        unsigned int allowsTickMarkValuesOnly:1;
        unsigned int tickMarkPosition:1;
        unsigned int sliderType:2;
        unsigned int drawing:1;
        unsigned int snappedToTickMark:1;
        unsigned int snappedToPreviousValue:1;
        unsigned int snappedToDefaultValue:1;
        unsigned int snappingAllowed:1;
        unsigned int reserved2:19;
    } _scFlags;
}

+ (BOOL)prefersTrackingUntilMouseUp;

@property double minValue;
@property double maxValue;
@property double altIncrementValue;

@property NSSliderType sliderType;
@property (getter=isVertical, readonly) NSInteger vertical;

@property (readonly) NSRect trackRect;

@property (readonly) CGFloat knobThickness;
- (NSRect)knobRectFlipped:(BOOL)flipped;
- (void)drawKnob:(NSRect)knobRect;
- (void)drawKnob;
- (NSRect)barRectFlipped:(BOOL)flipped NS_AVAILABLE_MAC(10_9);
- (void)drawBarInside:(NSRect)aRect flipped:(BOOL)flipped;

/* These methods have never done anything, and are formally deprecated as of 10.9*/
- (void)setTitleColor:(NSColor *)newColor NS_DEPRECATED_MAC(10_0, 10_9);
- (NSColor *)titleColor NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setTitleFont:(NSFont *)fontObj NS_DEPRECATED_MAC(10_0, 10_9);
- (NSFont *)titleFont NS_DEPRECATED_MAC(10_0, 10_9);
- (NSString *)title NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setTitle:(NSString *)aString NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setTitleCell:(NSCell *)aCell NS_DEPRECATED_MAC(10_0, 10_9);
- (id)titleCell NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setKnobThickness:(CGFloat)aFloat NS_DEPRECATED_MAC(10_0, 10_9);
@end

@interface NSSliderCell(NSTickMarkSupport)

// For setting and retrieving the number of tick marks on a slider.
//   0 indicates no tick marks are present, which is the default
@property NSInteger numberOfTickMarks;

// For setting and retrieving the position tick marks will be displayed in.
//   This has no effect if numberOfTickMarks is 0.
@property NSTickMarkPosition tickMarkPosition;

// For setting and retrieving whether values on the slider can be anything
//   the slider normally allows, or only values that correspond to a tick mark.
//   This has no effect if numberOfTickMarks is 0.
@property BOOL allowsTickMarkValuesOnly;

// Determine the slider value for a particular tick mark.
//   An NSRangeException will be raised if the index is invalid.
- (double)tickMarkValueAtIndex:(NSInteger)index;

// Determine the bounding rectangle of a particular tick mark.
//   An NSRangeException will be raised if the index is invalid.
- (NSRect)rectOfTickMarkAtIndex:(NSInteger)index;

// Determine whether a particular point is "near" a tick mark and return its
// index if so.  NSNotFound will be returned if no tick mark is close enough
// to qualify.
- (NSInteger)indexOfTickMarkAtPoint:(NSPoint)point;

- (double)closestTickMarkValueToValue:(double)value;

- (void)drawTickMarks NS_AVAILABLE_MAC(10_9);

@end
