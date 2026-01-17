/*
 JNFNumber.h
 Java Native Foundation
 Copyright (c) 2008, Apple Inc.
 All rights reserved.
 
 Functions that convert between number container classes.
 */

#import <Foundation/NSValue.h>

#import <JavaNativeFoundation/JNFJNI.h>

/*
 * Converts java.lang.Number to an NSNumber
 *  NOTE: Return value is auto-released, so if you need to hang on to it, you should retain it.
 */
JNF_EXPORT NSNumber *JNFJavaToNSNumber(JNIEnv *env, jobject n);

/*
 * Converts an NSNumber to a java.lang.Number
 * Only returns java.lang.Longs or java.lang.Doubles.
 *  NOTE: This returns a JNI Local Ref. Any code that calls must call DeleteLocalRef with the return value.
 */
JNF_EXPORT jobject JNFNSToJavaNumber(JNIEnv *env, NSNumber *n);
