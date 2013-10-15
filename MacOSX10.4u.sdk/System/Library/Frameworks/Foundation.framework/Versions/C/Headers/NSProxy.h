/*	NSProxy.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSMethodSignature, NSInvocation;

@interface NSProxy <NSObject> {
    Class	isa;
}

+ (id)alloc;
+ (id)allocWithZone:(NSZone *)zone;
+ (Class)class;

- (void)forwardInvocation:(NSInvocation *)invocation;
- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel;
- (void)dealloc;
- (NSString *)description;
+ (BOOL)respondsToSelector:(SEL)aSelector;

@end

