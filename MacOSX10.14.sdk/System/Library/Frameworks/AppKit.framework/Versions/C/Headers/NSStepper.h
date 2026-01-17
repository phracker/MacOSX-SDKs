/*
        NSStepper.h
        Application Kit
        Copyright (c) 2000-2018, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSControl.h>

@interface NSStepper : NSControl <NSAccessibilityStepper> {
  @private
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
