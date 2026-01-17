/*
 JNFNumber.h
 Java Native Foundation
 Copyright (c) 2008-2011, Apple Inc.
 All rights reserved.

 Functions that convert between number container classes.
 */

#import <Foundation/NSValue.h>

#import <JavaNativeFoundation/JNFJNI.h>

__BEGIN_DECLS

/*
 * Converts java.lang.Number to an NSNumber
 *  NOTE: Return value is auto-released, so if you need to hang on to it, you should retain it.
 */
JNF_EXPORT extern NSNumber *JNFJavaToNSNumber(JNIEnv *env, jobject n);

/*
 * Converts an NSNumber to a java.lang.Number
 * Only returns java.lang.Longs or java.lang.Doubles.
 *  NOTE: This returns a JNI Local Ref. Any code that calls must call DeleteLocalRef with the return value.
 */
JNF_EXPORT extern jobject JNFNSToJavaNumber(JNIEnv *env, NSNumber *n);

/*
 * Converts a java.lang.Boolean constants to the CFBooleanRef constants
 */
JNF_EXPORT extern CFBooleanRef JNFJavaToCFBoolean(JNIEnv* env, jobject b);

/*
 * Converts a CFBooleanRef constants to the java.lang.Boolean constants
 */
JNF_EXPORT extern jobject JNFCFToJavaBoolean(JNIEnv *env, CFBooleanRef b);

__END_DECLS
