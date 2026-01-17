/*
    NSLevelIndicatorCell.h
    Application Kit
    Copyright (c) 2004-2005, Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <AppKit/NSControl.h>
#import <AppKit/NSLevelIndicatorCell.h>

@interface NSLevelIndicator : NSControl {
}

- (double)minValue;
- (void)setMinValue:(double)minValue;

- (double)maxValue;
- (void)setMaxValue:(double)maxValue;

- (double)warningValue;
- (void)setWarningValue:(double)warningValue;

- (double)criticalValue;
- (void)setCriticalValue:(double)criticalValue;

- (NSTickMarkPosition)tickMarkPosition;
- (void)setTickMarkPosition:(NSTickMarkPosition)position;

- (int)numberOfTickMarks;
- (void)setNumberOfTickMarks:(int)count;

- (int)numberOfMajorTickMarks;
- (void)setNumberOfMajorTickMarks:(int)count;

- (double)tickMarkValueAtIndex:(int)index;
- (NSRect)rectOfTickMarkAtIndex:(int)index;

@end

#endif
