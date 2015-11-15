/*
        NSStepper.h
        Application Kit
        Copyright (c) 2000-2015, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSControl.h>

@interface NSStepper : NSControl <NSAccessibilityStepper> {
  @private
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
