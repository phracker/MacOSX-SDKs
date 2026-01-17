/*
        NSStepperCell.h
        Application Kit
        Copyright (c) 2000-2018, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@interface NSStepperCell : NSActionCell {
  @private
    double _value APPKIT_IVAR;
    double _minValue APPKIT_IVAR;
    double _maxValue APPKIT_IVAR;
    double _increment APPKIT_IVAR;
    struct {
        unsigned int valueWraps:1;
        unsigned int autorepeat:1;
        unsigned int drawing:1;
        unsigned int stats1:1;
        unsigned int reserved:28;
    } _stFlags APPKIT_IVAR;
    unsigned int _reserved1 APPKIT_IVAR;
    unsigned int _reserved2 APPKIT_IVAR;
    unsigned int _reserved3 APPKIT_IVAR;
    unsigned int _reserved4 APPKIT_IVAR;
}

@property double minValue;

@property double maxValue;

@property double increment;

@property BOOL valueWraps;

@property BOOL autorepeat;

@end

