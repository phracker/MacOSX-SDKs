/*
 JNFObject.h
 Java Native Foundation
 Copyright (c) 2008, Apple Inc.
 All rights reserved.
 
 Functions that access some of the base functionality of java.lang.Object.
 */

#import <Foundation/NSString.h>

#import <JavaNativeFoundation/JNFJNI.h>


/*
 * Returns Object.equals() for the two items
 */
JNF_EXPORT BOOL JNFObjectEquals(JNIEnv* env, jobject a, jobject b);

/*
 * Returns Object.toString() as an NSString
 */
JNF_EXPORT NSString *JNFObjectToString(JNIEnv *env, jobject obj);

/*
 * Returns Object.getClass().toString() as an NSString. Useful in gdb.
 */
JNF_EXPORT NSString *JNFObjectClassName(JNIEnv* env, jobject obj);
