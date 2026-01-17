/*
 JNFJObjectWrapper.h
 Java Native Foundation
 Copyright (c) 2008-2011, Apple Inc.
 All rights reserved.
 
 Simple wrapper classes to hold Java Objects in JNI global references.
 
 This is used to pass Java objects across thread boundries, often through
 -performSelectorOnMainThread invocations. This wrapper properly creates a
 new global ref, and clears it on -dealloc or -finalize, attaching to the
 current VM, attaching the current thread if necessary, releasing the global
 ref, and detaching the thread from the VM if it attached it.
 
 Destruction of this wrapper is expensive if the jobject has not been
 pre-cleared, because it must re-attach to the JVM.
 
 The JNFWeakJObjectWrapper manages a weak global reference which may become
 invalid if the JVM garbage collects the original object.
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
- (jobject) jObject; // returns the raw global-ref

@end


@interface JNFWeakJObjectWrapper : JNFJObjectWrapper { }

+ (JNFWeakJObjectWrapper *) wrapperWithJObject:(jobject)jObjectIn withEnv:(JNIEnv *)env;

@end
