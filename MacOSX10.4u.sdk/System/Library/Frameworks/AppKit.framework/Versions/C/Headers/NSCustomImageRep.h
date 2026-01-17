/*
	NSCustomImageRep.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@interface NSCustomImageRep : NSImageRep {
    /*All instance variables are private*/
    SEL _drawMethod;
    id _drawObject;
    unsigned int _reserved;
}

- (id)initWithDrawSelector:(SEL)aMethod delegate:(id)anObject;
- (SEL)drawSelector;
- (id)delegate;

@end

