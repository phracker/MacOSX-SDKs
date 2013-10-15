/*	NSDate.h
	Copyright (c) 1994-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;

FOUNDATION_EXPORT NSString * const NSSystemClockDidChangeNotification NS_AVAILABLE(10_6, 4_0);

typedef double NSTimeInterval;

#define NSTimeIntervalSince1970  978307200.0

@interface NSDate : NSObject <NSCopying, NSCoding>

- (NSTimeInterval)timeIntervalSinceReferenceDate;

@end

@interface NSDate (NSExtendedDate)

- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;
- (NSTimeInterval)timeIntervalSinceNow;
- (NSTimeInterval)timeIntervalSince1970;

- (id)addTimeInterval:(NSTimeInterval)seconds NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);
- (id)dateByAddingTimeInterval:(NSTimeInterval)ti NS_AVAILABLE(10_6, 2_0);

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
+ (id)dateWithTimeInterval:(NSTimeInterval)ti sinceDate:(NSDate *)date;

+ (id)distantFuture;
+ (id)distantPast;

- (id)init;
- (id)initWithTimeIntervalSinceNow:(NSTimeInterval)secs;
- (id)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secsToBeAdded;
- (id)initWithTimeIntervalSince1970:(NSTimeInterval)ti;
- (id)initWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)anotherDate;

@end

