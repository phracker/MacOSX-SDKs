/*
	NSSliderCell.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

typedef NS_ENUM(NSUInteger, NSTickMarkPosition) {
    NSTickMarkPositionBelow = 0,
    NSTickMarkPositionAbove = 1,
    NSTickMarkPositionLeading = NSTickMarkPositionAbove,
    NSTickMarkPositionTrailing = NSTickMarkPositionBelow
};
typedef NS_ENUM(NSUInteger, NSSliderType) {
    NSSliderTypeLinear = 0,
    NSSliderTypeCircular = 1,
};

@interface NSSliderCell : NSActionCell
{
    /*All instance variables are private*/
    id       _sliderCellPrivateData APPKIT_IVAR;
    CGFloat  _previousValue APPKIT_IVAR;
    CGFloat  _knobOffset APPKIT_IVAR;
    int      _numberOfTickMarks APPKIT_IVAR;
    double	_altIncValue APPKIT_IVAR;
    double	_value APPKIT_IVAR;
    double	_maxValue APPKIT_IVAR;
    double	_minValue APPKIT_IVAR;
    NSRect	_trackRect APPKIT_IVAR;
    struct __sliderCellFlags {
        unsigned int weAreVertical:1;
        unsigned int weAreVerticalSet:1;
        unsigned int weHaveStickyOrientation:1;
        unsigned int isPressed:1;
        unsigned int allowsTickMarkValuesOnly:1;
        unsigned int tickMarkPosition:1;
        unsigned int sliderType:2;
        unsigned int drawing:1;
        unsigned int snappedToTickMark:1;
        unsigned int snappedToPreviousValue:1;
        unsigned int snappedToDefaultValue:1;
        unsigned int snappingAllowed:1;
        unsigned int collapseOnResize:1;
        unsigned int startedOnAccessory:1;
        unsigned int reserved2:17;
    } _scFlags APPKIT_IVAR;
}

@property (class, readonly) BOOL prefersTrackingUntilMouseUp;

@property double minValue;
@property double maxValue;
@property double altIncrementValue;

@property NSSliderType sliderType;
@property (readwrite, getter=isVertical) BOOL vertical NS_AVAILABLE_MAC(10_11);

@property (readonly) NSRect trackRect;

@property (readonly) CGFloat knobThickness;

- (NSRect)knobRectFlipped:(BOOL)flipped;
- (NSRect)barRectFlipped:(BOOL)flipped NS_AVAILABLE_MAC(10_9);

- (void)drawKnob:(NSRect)knobRect;
- (void)drawKnob;
- (void)drawBarInside:(NSRect)rect flipped:(BOOL)flipped;

@end

@interface NSSliderCell (NSSliderCellVerticalGetter)
@property (readonly, getter=isVertical) BOOL vertical NS_AVAILABLE_MAC(10_0);
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

@interface NSSliderCell (NSDeprecated)
- (void)setTitleCell:(null_unspecified NSCell *)cell NS_DEPRECATED_MAC(10_0, 10_9, "-setTitleCell: had no effect since 10.0");
- (null_unspecified id)titleCell NS_DEPRECATED_MAC(10_0, 10_9, "-titleCell has returned nil since 10.0");
- (void)setTitleColor:(null_unspecified NSColor *)newColor NS_DEPRECATED_MAC(10_0, 10_9, "-setTitleColor: had no effect since 10.0");
- (null_unspecified NSColor *)titleColor NS_DEPRECATED_MAC(10_0, 10_9, "-titleColor has returned nil since 10.0");
- (void)setTitleFont:(null_unspecified NSFont *)fontObj NS_DEPRECATED_MAC(10_0, 10_9, "-setTitleFont: had no effect since 10.0");
- (null_unspecified NSFont *)titleFont NS_DEPRECATED_MAC(10_0, 10_9, "-titleFont has returned nil since 10.0");
- (null_unspecified NSString *)title NS_DEPRECATED_MAC(10_0, 10_9, "-title has returned nil since 10.0");
- (void)setTitle:(null_unspecified NSString *)string NS_DEPRECATED_MAC(10_0, 10_9, "-setTitle: had no effect since 10.0");
- (void)setKnobThickness:(CGFloat)thickness NS_DEPRECATED_MAC(10_0, 10_9, "-knobThickness has returned 0 since 10.0");
- (void)setImage:(null_unspecified NSImage *)backgroundImage NS_DEPRECATED_MAC(10_0, 10_9, "-setImage: had no effect since 10.0");
- (null_unspecified NSImage *)image NS_DEPRECATED_MAC(10_0, 10_9, "-image has returned nil since 10.0");
@end

static const NSTickMarkPosition NSTickMarkBelow NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSTickMarkPositionBelow", 10_0, 10_12) = NSTickMarkPositionBelow;
static const NSTickMarkPosition NSTickMarkAbove NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSTickMarkPositionAbove", 10_0, 10_12) = NSTickMarkPositionAbove;
static const NSTickMarkPosition NSTickMarkLeft NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSTickMarkPositionLeading", 10_0, 10_12) = NSTickMarkPositionLeading;
static const NSTickMarkPosition NSTickMarkRight NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSTickMarkPositionTrailing", 10_0, 10_12) = NSTickMarkPositionTrailing;

static const NSSliderType NSLinearSlider NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSSliderTypeLinear", 10_0, 10_12) = NSSliderTypeLinear;
static const NSSliderType NSCircularSlider NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSSliderTypeCircular", 10_0, 10_12) = NSSliderTypeCircular;
