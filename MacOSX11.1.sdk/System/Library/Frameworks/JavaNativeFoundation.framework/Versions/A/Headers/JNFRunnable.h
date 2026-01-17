/*
 JNFRunnable.h
 Java Native Foundation
 Copyright (c) 2009-2010, Apple Inc.
 All rights reserved.

 Creates NSInvocations which wrap java.lang.Runnables.
 */

#import <Foundation/Foundation.h>
#import <JavaNativeFoundation/JNFJNI.h>

__BEGIN_DECLS

JNF_EXPORT
@interface JNFRunnable : NSObject { }
+ (NSInvocation *) invocationWithRunnable:(jobject)runnable withEnv:(JNIEnv *)env;
#if __BLOCKS__
+ (void(^)(void)) blockWithRunnable:(jobject)runnable withEnv:(JNIEnv *)env;
#endif
@end

__END_DECLS
