/*
 JNFRunLoop.h
 Java Native Foundation
 Copyright (c) 2009, Apple Inc.
 All rights reserved.
 
 Used to perform selectors in the Java runloop mode.
 */

#import <Foundation/Foundation.h>

@interface JNFRunLoop : NSObject { }

+ (NSString *)javaRunLoopMode;
+ (void)performOnMainThread:(SEL)aSelector on:(id)target withObject:(id)arg waitUntilDone:(BOOL)wait;

@end
