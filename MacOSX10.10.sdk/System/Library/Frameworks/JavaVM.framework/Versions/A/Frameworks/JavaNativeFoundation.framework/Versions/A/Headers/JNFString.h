/*
 JNFString.h
 Java Native Foundation
 Copyright (c) 2008, Apple Inc.
 All rights reserved.
 
 Functions that create NSStrings, UTF16 unichars, or UTF8 chars from java.lang.Strings
 */

#import <Foundation/NSString.h>

#import <JavaNativeFoundation/JNFJNI.h>


// Returns an NSString given a java.lang.String object
//	NOTE: Return value is auto-released, so if you need to hang on to it, you should retain it.
JNF_EXPORT NSString *JNFJavaToNSString(JNIEnv *env, jstring javaString);

// Returns a java.lang.String object as a JNI local ref.
//	NOTE: This returns a JNI Local Ref. Any code that calls this should call DeleteLocalRef with the return value.
JNF_EXPORT jstring JNFNSToJavaString(JNIEnv *env, NSString *nsString);

/*
 * Gets UTF16 unichars from a Java string, and checks for errors and raises a JNFException if
 * the unichars cannot be obtained from Java.
 */
JNF_EXPORT const unichar *JNFGetStringUTF16UniChars(JNIEnv *env, jstring javaString);

/*
 * Releases the unichars obtained from JNFGetStringUTF16UniChars()
 */
JNF_EXPORT void JNFReleaseStringUTF16UniChars(JNIEnv *env, jstring javaString, const unichar *unichars);

/*
 * Gets UTF8 chars from a Java string, and checks for errors and raises a JNFException if
 * the chars cannot be obtained from Java.
 */
JNF_EXPORT const char *JNFGetStringUTF8Chars(JNIEnv *env, jstring javaString);

/*
 * Releases the chars obtained from JNFGetStringUTF8Chars()
 */
JNF_EXPORT void JNFReleaseStringUTF8Chars(JNIEnv *env, jstring javaString, const char *chars);
