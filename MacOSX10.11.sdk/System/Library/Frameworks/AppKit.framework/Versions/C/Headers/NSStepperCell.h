/*
        NSStepperCell.h
        Application Kit
        Copyright (c) 2000-2015, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@interface NSStepperCell : NSActionCell {
  @private
    double _value;
    double _minValue;
    double _maxValue;
    double _increment;
    struct {
        unsigned int valueWraps:1;
        unsigned int autorepeat:1;
        unsigned int drawing:1;
        unsigned int stats1:1;
        unsigned int reserved:28;
    } _stFlags;
    unsigned int _reserved1;
    unsigned int _reserved2;
    unsigned int _reserved3;
    unsigned int _reserved4;
}

@property double minValue;

@property double maxValue;

@property double increment;

@property BOOL valueWraps;

@property BOOL autorepeat;

@end

