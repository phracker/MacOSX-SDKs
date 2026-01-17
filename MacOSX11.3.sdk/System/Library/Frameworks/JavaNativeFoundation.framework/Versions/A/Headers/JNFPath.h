/*
 JNFPath.h
 Java Native Foundation
 Copyright (c) 2008, Apple Inc.
 All rights reserved.

 Functions that create strings that are in the proper format for holding
 paths in Java and native.
 */

#import <Foundation/NSString.h>

#import <JavaNativeFoundation/JNFJNI.h>

__BEGIN_DECLS

/*
 * Returns a jstring in precomposed UTF16 format that is compatable with Java's
 * expectation of the UTF16 format for strings to be displayed.
 */
JNF_EXPORT extern jstring JNFNormalizedJavaStringForPath(JNIEnv *env, NSString *path);

/*
 * Returns an NSString in decomposed UTF16 format that is compatable with HFS's
 * expectation of the UTF16 format for file system paths.
 *  NOTE: this NSString is autoreleased.
 */
JNF_EXPORT extern NSString *JNFNormalizedNSStringForPath(JNIEnv *env, jstring path);

__END_DECLS
