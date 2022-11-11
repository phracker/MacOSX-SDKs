/*
 JNFRunLoop.h
 Java Native Foundation
 Copyright (c) 2009-2011, Apple Inc.
 All rights reserved.

 Used to perform selectors and blocks in the Java runloop mode.
 */

#import <Foundation/Foundation.h>
#import <JavaNativeFoundation/JNFJNI.h>

__BEGIN_DECLS

JNF_EXPORT extern NSString *JNFRunLoopDidStartNotification;

JNF_EXPORT
@interface JNFRunLoop : NSObject { }

+ (NSString *)javaRunLoopMode;
+ (void)performOnMainThread:(SEL)aSelector on:(id)target withObject:(id)arg waitUntilDone:(BOOL)wait;
#if __BLOCKS__
+ (void)performOnMainThreadWaiting:(BOOL)waitUntilDone withBlock:(void (^)(void))block;
#endif

@end

__END_DECLS
