/*
 JNFDate.h
 Java Native Foundation
 Copyright (c) 2009, Apple Inc.
 All rights reserved.
 
 Functions to convert between date container classes.
 */

#import <Foundation/NSDate.h>

#import <JavaNativeFoundation/JNFJNI.h>

/*
 * Converts java.util.Calendar and java.util.Date to an NSDate
 *  NOTE: Return value is auto-released.
 */
JNF_EXPORT NSDate *JNFJavaToNSDate(JNIEnv *env, jobject date);

/*
 * Converts an NSDate to a java.util.Calendar
 *  NOTE: This returns a JNI local ref. Any code that calls this should call DeleteLocalRef when done with the return value.
 */
JNF_EXPORT jobject JNFNSToJavaCalendar(JNIEnv *env, NSDate *date);

/*
 * Converts a millisecond time interval since the Java Jan 1, 1970 epoch into an
 * NSTimeInterval since Mac OS X's Jan 1, 2001 epoch.
 */
JNF_EXPORT NSTimeInterval JNFJavaMillisToNSTimeInterval(jlong javaMillisSince1970);

/*
 * Converts an NSTimeInterval since the Mac OS X Jan 1, 2001 epoch into a
 * Java millisecond time interval since Java's Jan 1, 1970 epoch.
 */
JNF_EXPORT jlong JNFNSTimeIntervalToJavaMillis(NSTimeInterval intervalSince2001);
