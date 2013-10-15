/*	NSDate.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;

FOUNDATION_EXPORT NSString * const NSSystemClockDidChangeNotification AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

typedef double NSTimeInterval;

#define NSTimeIntervalSince1970  978307200.0

@interface NSDate : NSObject <NSCopying, NSCoding>

- (NSTimeInterval)timeIntervalSinceReferenceDate;

@end

@interface NSDate (NSExtendedDate)

- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;
- (NSTimeInterval)timeIntervalSinceNow;
- (NSTimeInterval)timeIntervalSince1970;

- (id)addTimeInterval:(NSTimeInterval)seconds DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
- (id)dateByAddingTimeInterval:(NSTimeInterval)ti AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSDate *)earlierDate:(NSDate *)anotherDate;
- (NSDate *)laterDate:(NSDate *)anotherDate;
- (NSComparisonResult)compare:(NSDate *)other;
- (BOOL)isEqualToDate:(NSDate *)otherDate;

- (NSString *)description;
- (NSString *)descriptionWithLocale:(id)locale;

+ (NSTimeInterval)timeIntervalSinceReferenceDate;
    
@end

@interface NSDate (NSDateCreation)

+ (id)date;
    
+ (id)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;    
+ (id)dateWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secs;
+ (id)dateWithTimeIntervalSince1970:(NSTimeInterval)secs;
+ (id)dateWithTimeInterval:(NSTimeInterval)ti sinceDate:(NSDate *)date AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

+ (id)distantFuture;
+ (id)distantPast;

- (id)init;
- (id)initWithTimeIntervalSinceNow:(NSTimeInterval)secs;
- (id)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secsToBeAdded;
- (id)initWithTimeIntervalSince1970:(NSTimeInterval)ti AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)initWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)anotherDate;

@end

