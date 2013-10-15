/*
 JNFRunnable.h
 Java Native Foundation
 Copyright (c) 2009, Apple Inc.
 All rights reserved.
 
 Creates NSInvocations which wrap java.lang.Runnables.
 */

#import <Foundation/Foundation.h>
#import <JavaNativeFoundation/JNFJNI.h>


@interface JNFRunnable : NSObject { }
+ (NSInvocation *) invocationWithRunnable:(jobject)runnable withEnv:(JNIEnv *)env;
@end
