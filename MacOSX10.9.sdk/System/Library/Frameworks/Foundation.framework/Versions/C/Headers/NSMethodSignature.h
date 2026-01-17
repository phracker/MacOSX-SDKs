/*	NSMethodSignature.h
	Copyright (c) 1994-2013, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@interface NSMethodSignature : NSObject {
@private
    void *_private;
    void *_reserved[6];
}

+ (NSMethodSignature *)signatureWithObjCTypes:(const char *)types;

- (NSUInteger)numberOfArguments;
- (const char *)getArgumentTypeAtIndex:(NSUInteger)idx NS_RETURNS_INNER_POINTER;

- (NSUInteger)frameLength;

- (BOOL)isOneway;

- (const char *)methodReturnType NS_RETURNS_INNER_POINTER;
- (NSUInteger)methodReturnLength;

@end

