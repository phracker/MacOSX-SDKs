/*
    NSLevelIndicator.h
    Application Kit
    Copyright (c) 2004-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSLevelIndicatorCell.h>

typedef NS_ENUM(NSInteger, NSLevelIndicatorPlaceholderVisibility) {
    /* Placeholders are always displayed for standalone indicators. For level indicators inside a table view, placeholders draw only in the selected row and while the control is being edited. */
    NSLevelIndicatorPlaceholderVisibilityAutomatic = 0,
    
    /* Always display placeholders */
    NSLevelIndicatorPlaceholderVisibilityAlways = 1,
    
    /* Only display placeholders while the control is being edited */
    NSLevelIndicatorPlaceholderVisibilityWhileEditing = 2
};

@interface NSLevelIndicator : NSControl {
}

@property NSLevelIndicatorStyle levelIndicatorStyle NS_AVAILABLE_MAC(10_10);

@property (getter=isEditable) BOOL editable NS_AVAILABLE_MAC(10_13);

#pragma mark Value Thresholds

@property double minValue;

@property double maxValue;

@property double warningValue;

@property double criticalValue;

#pragma mark Tick Marks

@property NSTickMarkPosition tickMarkPosition;

@property NSInteger numberOfTickMarks;

@property NSInteger numberOfMajorTickMarks;

- (double)tickMarkValueAtIndex:(NSInteger)index;
- (NSRect)rectOfTickMarkAtIndex:(NSInteger)index;

#pragma mark Custom Colors

/*! Sets the fill color used by Continuous and Discrete Capacity indicators when drawing the "normal" state, and by the Rating indicator when drawing stars. The default value is a system-defined color which may vary between level indicator styles and OS releases. */
@property (copy, null_resettable) NSColor *fillColor NS_AVAILABLE_MAC(10_13);

/*! Sets the fill color used by Continuous and Discrete Capacity indicators when drawing values above the "warning" threshold. The default value is a system-defined color which may vary between level indicator styles and OS releases. */
@property (copy, null_resettable) NSColor *warningFillColor NS_AVAILABLE_MAC(10_13);

/*! Sets the fill color used by Continuous and Discrete Capacity indicators when drawing values above the "critical" threshold. The default value is a system-defined color which may vary between level indicator styles and OS releases. */
@property (copy, null_resettable) NSColor *criticalFillColor NS_AVAILABLE_MAC(10_13);

#pragma mark Capacity Indicator Options

@property BOOL drawsTieredCapacityLevels NS_AVAILABLE_MAC(10_13);

#pragma mark Rating Indicator Options

/*! For a Rating-style indicator, sets the conditions under which Rating placeholders are displayed. This property currently has no effect for other indicator styles. The default value is \c NSLevelIndicatorPlaceholderVisibilityAutomatic. */
@property NSLevelIndicatorPlaceholderVisibility placeholderVisibility NS_AVAILABLE_MAC(10_13);

/*! If non-nil, sets the image used by the Rating indicator style in place of the default star image. The default value is nil. */
@property (strong, nullable) NSImage *ratingImage NS_AVAILABLE_MAC(10_13);

/*! If non-nil, sets the image used by the Rating indicator style in place of the default faded placeholder image. The default value is nil.
 
 If the custom placeholder is a template image, its fill opacity can be adjusted by modifying the opacity of the template image.
 
 If both a ratingImage and ratingPlaceholderImage are set, each rating position is sized such that either image will fit without scaling (i.e. sized to the maximum width and height of both images). */
@property (strong, nullable) NSImage *ratingPlaceholderImage NS_AVAILABLE_MAC(10_13);

@end
