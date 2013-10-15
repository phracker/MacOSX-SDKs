/*
 JNFJObjectWrapper.h
 Java Native Foundation
 Copyright (c) 2008, Apple Inc.
 All rights reserved.
 
 Simple wrapper class to hold Java Objects in JNI gobal references.
 
 This is used to pass Java objects across thread boundries, often though
 -performSelectorOnMainThread invocations. This wrapper properly create a
 new global ref, and clears it on -dealloc or -finalize, attaching to the
 current VM, attaching the current thread if necessary, releasing the global
 ref, and detaching the thread from the VM, if it attached it.
 
 Destruction of this object is, of course, expensive, unless the jobject has
 been pre-cleared.
 */

#import <Foundation/Foundation.h>
#import <JavaVM/jni.h>


@interface JNFJObjectWrapper : NSObject {
	jobject jobj;
}

+ (JNFJObjectWrapper *) wrapperWithJObject:(jobject)jObjectIn withEnv:(JNIEnv *)env;
- (id) initWithJObject:(jobject)jObjectIn withEnv:(JNIEnv *)env;
- (void) setJObject:(jobject)jObjectIn withEnv:(JNIEnv *)env; // clears any pre-existing global-ref
- (jobject) jObjectWithEnv:(JNIEnv *)env; // returns a new local-ref, must be released with DeleteLocalRef
- (jobject) jObject; // returns the global-ref

@end
