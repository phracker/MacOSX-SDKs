/*
	NSSlider.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSSliderCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSSlider : NSControl <NSAccessibilitySlider>

@property NSSliderType sliderType NS_AVAILABLE_MAC(10_10);

@property double minValue;
@property double maxValue;
@property double altIncrementValue;
@property (readonly) CGFloat knobThickness;
@property (getter=isVertical, readonly) NSInteger vertical;
- (BOOL)acceptsFirstMouse:(nullable NSEvent *)theEvent;

/* These methods have never done anything, and are formally deprecated as of 10.9*/
- (void)setTitleCell:(null_unspecified NSCell *)aCell NS_DEPRECATED_MAC(10_0, 10_9);
- (null_unspecified id)titleCell NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setTitleColor:(null_unspecified NSColor *)newColor NS_DEPRECATED_MAC(10_0, 10_9);
- (null_unspecified NSColor *)titleColor NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setTitleFont:(null_unspecified NSFont *)fontObj NS_DEPRECATED_MAC(10_0, 10_9);
- (null_unspecified NSFont *)titleFont NS_DEPRECATED_MAC(10_0, 10_9);
- (null_unspecified NSString *)title NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setTitle:(null_unspecified NSString *)aString NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setKnobThickness:(CGFloat)aFloat NS_DEPRECATED_MAC(10_0, 10_9);
- (void)setImage:(null_unspecified NSImage *)backgroundImage NS_DEPRECATED_MAC(10_0, 10_9);
- (null_unspecified NSImage *)image NS_DEPRECATED_MAC(10_0, 10_9);
@end

@interface NSSlider(NSTickMarkSupport)

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

@end

NS_ASSUME_NONNULL_END
