/*	NSDate.h
	Copyright (c) 1994-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;

FOUNDATION_EXPORT NSString * const NSSystemClockDidChangeNotification NS_AVAILABLE(10_6, 4_0);

typedef double NSTimeInterval;

#define NSTimeIntervalSince1970  978307200.0

@interface NSDate : NSObject <NSCopying, NSSecureCoding>

@property (readonly) NSTimeInterval timeIntervalSinceReferenceDate;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)ti NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSDate (NSExtendedDate)

- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;
@property (readonly) NSTimeInterval timeIntervalSinceNow;
@property (readonly) NSTimeInterval timeIntervalSince1970;

- (id)addTimeInterval:(NSTimeInterval)seconds NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);
- (instancetype)dateByAddingTimeInterval:(NSTimeInterval)ti NS_AVAILABLE(10_6, 2_0);

- (NSDate *)earlierDate:(NSDate *)anotherDate;
- (NSDate *)laterDate:(NSDate *)anotherDate;
- (NSComparisonResult)compare:(NSDate *)other;
- (BOOL)isEqualToDate:(NSDate *)otherDate;

@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(id)locale;

+ (NSTimeInterval)timeIntervalSinceReferenceDate;

@end

@interface NSDate (NSDateCreation)

+ (instancetype)date;
+ (instancetype)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;
+ (instancetype)dateWithTimeIntervalSinceReferenceDate:(NSTimeInterval)ti;
+ (instancetype)dateWithTimeIntervalSince1970:(NSTimeInterval)secs;
+ (instancetype)dateWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)date;

+ (id /* NSDate * */)distantFuture;
+ (id /* NSDate * */)distantPast;

- (instancetype)initWithTimeIntervalSinceNow:(NSTimeInterval)secs;
- (instancetype)initWithTimeIntervalSince1970:(NSTimeInterval)secs;
- (instancetype)initWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)date;

@end

