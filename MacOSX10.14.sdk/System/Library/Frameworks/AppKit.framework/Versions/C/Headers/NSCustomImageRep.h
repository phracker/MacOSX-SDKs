/*
	NSCustomImageRep.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSCustomImageRep : NSImageRep {
    /*All instance variables are private*/
#if __OBJC2__
    unsigned int _reserved APPKIT_IVAR;
    SEL _drawMethod APPKIT_IVAR;
    id _drawObject APPKIT_IVAR;
#else /* __OBJC2__ */
    SEL _drawMethod APPKIT_IVAR;
    id _drawObject APPKIT_IVAR;
    unsigned int _reserved APPKIT_IVAR;
#endif /* __OBJC2__ */
}
// Note that the block passed to the below method may be invoked whenever and on whatever thread the image itself is drawn on. Care should be taken to ensure that all state accessed within the drawingHandler block is done so in a thread safe manner.
- (instancetype)initWithSize:(NSSize)size flipped:(BOOL)drawingHandlerShouldBeCalledWithFlippedContext drawingHandler:(BOOL (^)(NSRect dstRect))drawingHandler NS_AVAILABLE_MAC(10_8);
@property (nullable, readonly, copy) BOOL (^drawingHandler)(NSRect) NS_AVAILABLE_MAC(10_8);

- (instancetype)initWithDrawSelector:(SEL)selector delegate:(id)delegate;
@property (nullable, readonly) SEL drawSelector;
@property (nullable, readonly, weak) id delegate;

@end

NS_ASSUME_NONNULL_END

