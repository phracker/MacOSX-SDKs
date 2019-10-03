/*
        NSStepperCell.h
        Application Kit
        Copyright (c) 2000-2019, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSActionCell.h>

API_UNAVAILABLE_BEGIN(ios)

@interface NSStepperCell : NSActionCell

@property double minValue;

@property double maxValue;

@property double increment;

@property BOOL valueWraps;

@property BOOL autorepeat;

@end

API_UNAVAILABLE_END
