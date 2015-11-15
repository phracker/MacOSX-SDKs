/*
    NSLevelIndicatorCell.h
    Application Kit
    Copyright (c) 2004-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSLevelIndicatorCell.h>


@interface NSLevelIndicator : NSControl {
}

@property NSLevelIndicatorStyle levelIndicatorStyle NS_AVAILABLE_MAC(10_10);

@property double minValue;

@property double maxValue;

@property double warningValue;

@property double criticalValue;

@property NSTickMarkPosition tickMarkPosition;

@property NSInteger numberOfTickMarks;

@property NSInteger numberOfMajorTickMarks;

- (double)tickMarkValueAtIndex:(NSInteger)index;
- (NSRect)rectOfTickMarkAtIndex:(NSInteger)index;

@end

