/*
	NSCustomImageRep.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSCustomImageRep : NSImageRep {
    /*All instance variables are private*/
    SEL _drawMethod;
    id _drawObject;
    unsigned int _reserved;
}
// Note that the block passed to the below method may be invoked whenever and on whatever thread the image itself is drawn on. Care should be taken to ensure that all state accessed within the drawingHandler block is done so in a thread safe manner.
- (instancetype)initWithSize:(NSSize)size flipped:(BOOL)drawingHandlerShouldBeCalledWithFlippedContext drawingHandler:(BOOL (^)(NSRect dstRect))drawingHandler NS_AVAILABLE_MAC(10_8);
@property (nullable, readonly, copy) BOOL (^drawingHandler)(NSRect) NS_AVAILABLE_MAC(10_8);

- (instancetype)initWithDrawSelector:(SEL)aMethod delegate:(id)anObject;
@property (nullable, readonly) SEL drawSelector;
@property (nullable, readonly, assign) id delegate;

@end

NS_ASSUME_NONNULL_END

