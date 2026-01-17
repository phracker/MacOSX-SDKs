/*
	NSCustomImageRep.h
	Application Kit
	Copyright (c) 1994-2014, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@interface NSCustomImageRep : NSImageRep {
    /*All instance variables are private*/
    SEL _drawMethod;
    id _drawObject;
    unsigned int _reserved;
}
// Note that the block passed to the below method may be invoked whenever and on whatever thread the image itself is drawn on. Care should be taken to ensure that all state accessed within the drawingHandler block is done so in a thread safe manner.
- (instancetype)initWithSize:(NSSize)size flipped:(BOOL)drawingHandlerShouldBeCalledWithFlippedContext drawingHandler:(BOOL (^)(NSRect dstRect))drawingHandler NS_AVAILABLE_MAC(10_8);
@property (readonly, copy) BOOL (^drawingHandler)(NSRect) NS_AVAILABLE_MAC(10_8);

- (instancetype)initWithDrawSelector:(SEL)aMethod delegate:(id)anObject;
@property (readonly) SEL drawSelector;
@property (readonly, assign) id delegate;

@end

