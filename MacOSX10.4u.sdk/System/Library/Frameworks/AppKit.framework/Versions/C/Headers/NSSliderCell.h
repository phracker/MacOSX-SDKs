/*
	NSSliderCell.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

typedef enum _NSTickMarkPosition {
    NSTickMarkBelow = 0,
    NSTickMarkAbove = 1,
    NSTickMarkLeft  = NSTickMarkAbove,
    NSTickMarkRight = NSTickMarkBelow
} NSTickMarkPosition;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
typedef enum {
    NSLinearSlider   = 0,
    NSCircularSlider = 1
} NSSliderType;
#endif

@interface NSSliderCell : NSActionCell
{
    /*All instance variables are private*/
    int     _reserved[3];
    int     _numberOfTickMarks;
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
        unsigned int reserved2:23;
    } _scFlags;
}


+ (BOOL)prefersTrackingUntilMouseUp;


- (double)minValue;
- (void)setMinValue:(double)aDouble;
- (double)maxValue;
- (void)setMaxValue:(double)aDouble;
- (void)setAltIncrementValue:(double)incValue;
- (double)altIncrementValue;
- (int)isVertical;
- (void)setTitleColor:(NSColor *)newColor;
- (NSColor *)titleColor;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSFont *)titleFont;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (void)setTitleCell:(NSCell *)aCell;
- (id)titleCell;
- (void)setKnobThickness:(float)aFloat;
- (float)knobThickness;
- (NSRect)knobRectFlipped:(BOOL)flipped;
- (void)drawKnob:(NSRect)knobRect;
- (void)drawKnob;
- (void)drawBarInside:(NSRect)aRect flipped:(BOOL)flipped;
- (NSRect)trackRect;	// Only valid while tracking the mouse!

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void) setSliderType:(NSSliderType)sliderType;
- (NSSliderType)sliderType;
#endif

@end

@interface NSSliderCell(NSTickMarkSupport)

// For setting and retrieving the number of tick marks on a slider.
//   0 indicates no tick marks are present, which is the default
- (void)setNumberOfTickMarks:(int)count;
- (int)numberOfTickMarks;

// For setting and retrieving the position tick marks will be displayed in.
//   This has no effect if numberOfTickMarks is 0.
- (void)setTickMarkPosition:(NSTickMarkPosition)position;
- (NSTickMarkPosition)tickMarkPosition;

// For setting and retrieving whether values on the slider can be anything
//   the slider normally allows, or only values that correspond to a tick mark.
//   This has no effect if numberOfTickMarks is 0.
- (void)setAllowsTickMarkValuesOnly:(BOOL)yorn;
- (BOOL)allowsTickMarkValuesOnly;

// Determine the slider value for a particular tick mark.
//   An NSRangeException will be raised if the index is invalid.
- (double)tickMarkValueAtIndex:(int)index;

// Determine the bounding rectangle of a particular tick mark.
//   An NSRangeException will be raised if the index is invalid.
- (NSRect)rectOfTickMarkAtIndex:(int)index;

// Determine whether a particular point is "near" a tick mark and return its
// index if so.  NSNotFound will be returned if no tick mark is close enough
// to qualify.
- (int)indexOfTickMarkAtPoint:(NSPoint)point;

- (double)closestTickMarkValueToValue:(double)value;

@end
