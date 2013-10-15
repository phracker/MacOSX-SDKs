/*	NSProxy.h
	Copyright (c) 1994-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSMethodSignature, NSInvocation;

@interface NSProxy <NSObject> {
    Class	isa;
}

+ (id)alloc;
+ (id)allocWithZone:(NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
+ (Class)class;

- (void)forwardInvocation:(NSInvocation *)invocation;
- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel;
- (void)dealloc;
- (void)finalize;
- (NSString *)description;
+ (BOOL)respondsToSelector:(SEL)aSelector;

- (BOOL)allowsWeakReference NS_UNAVAILABLE;
- (BOOL)retainWeakReference NS_UNAVAILABLE;

// - (id)forwardingTargetForSelector:(SEL)aSelector;

@end

