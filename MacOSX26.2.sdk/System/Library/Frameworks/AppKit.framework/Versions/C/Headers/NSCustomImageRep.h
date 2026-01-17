/*
	NSCustomImageRep.h
	Application Kit
	Copyright (c) 1994-2024, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@interface NSCustomImageRep : NSImageRep

// Note that the block passed to the below method may be invoked whenever and on whatever thread the image itself is drawn on. Care should be taken to ensure that all state accessed within the drawingHandler block is done so in a thread safe manner.
- (instancetype)initWithSize:(NSSize)size flipped:(BOOL)drawingHandlerShouldBeCalledWithFlippedContext drawingHandler:(BOOL (^)(NSRect dstRect))drawingHandler API_AVAILABLE(macos(10.8));
@property (nullable, readonly, copy) BOOL (^drawingHandler)(NSRect) API_AVAILABLE(macos(10.8));

- (instancetype)initWithDrawSelector:(SEL)selector delegate:(id)delegate;
@property (nullable, readonly) SEL drawSelector;
@property (nullable, readonly, weak) id delegate;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)

