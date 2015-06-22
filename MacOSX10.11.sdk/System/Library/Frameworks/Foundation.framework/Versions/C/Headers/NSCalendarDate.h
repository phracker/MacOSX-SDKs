/*	NSCalendarDate.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSDate.h>

@class NSString, NSArray, NSTimeZone;

NS_ASSUME_NONNULL_BEGIN

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#if 1 || NS_ENABLE_CALENDAR_DEPRECATIONS
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#else
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_AVAILABLE(A, C)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_AVAILABLE(A, C)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_AVAILABLE_MAC(A)
#endif
#endif

NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendar and NSDateComponents and NSDateFormatter instead")
NS_SWIFT_UNAVAILABLE("Use NSCalendar and NSDateComponents and NSDateFormatter instead")
@interface NSCalendarDate : NSDate {
@private
    NSUInteger		refCount;
    NSTimeInterval 	_timeIntervalSinceReferenceDate;
    NSTimeZone		*_timeZone;
    NSString 		*_formatString;
    void		*_reserved;
}

/*    DEPRECATED DEPRECATED DEPRECATED
 *    These methods are deprecated.
 *    Use NSCalendar for calendrical calculations.
 *    Use NSDateFormatter for date<->string conversions.
 */
+ (id)calendarDate NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
+ (nullable id)dateWithString:(NSString *)description calendarFormat:(NSString *)format locale:(nullable id)locale NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
+ (nullable id)dateWithString:(NSString *)description calendarFormat:(NSString *)format NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
+ (id)dateWithYear:(NSInteger)year month:(NSUInteger)month day:(NSUInteger)day hour:(NSUInteger)hour minute:(NSUInteger)minute second:(NSUInteger)second timeZone:(nullable NSTimeZone *)aTimeZone NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSCalendarDate *)dateByAddingYears:(NSInteger)year months:(NSInteger)month days:(NSInteger)day hours:(NSInteger)hour minutes:(NSInteger)minute seconds:(NSInteger)second NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)dayOfCommonEra NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)dayOfMonth NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)dayOfWeek NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)dayOfYear NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)hourOfDay NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)minuteOfHour NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)monthOfYear NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)secondOfMinute NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSInteger)yearOfCommonEra NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSString *)calendarFormat NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSString *)descriptionWithCalendarFormat:(NSString *)format locale:(nullable id)locale NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSString *)descriptionWithCalendarFormat:(NSString *)format NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSString *)descriptionWithLocale:(nullable id)locale NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSTimeZone *)timeZone NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (nullable id)initWithString:(NSString *)description calendarFormat:(NSString *)format locale:(nullable id)locale NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (nullable id)initWithString:(NSString *)description calendarFormat:(NSString *)format NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (nullable id)initWithString:(NSString *)description NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (id)initWithYear:(NSInteger)year month:(NSUInteger)month day:(NSUInteger)day hour:(NSUInteger)hour minute:(NSUInteger)minute second:(NSUInteger)second timeZone:(nullable NSTimeZone *)aTimeZone NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (void)setCalendarFormat:(nullable NSString *)format NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (void)setTimeZone:(nullable NSTimeZone *)aTimeZone NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (void)years:(nullable NSInteger *)yp months:(nullable NSInteger *)mop days:(nullable NSInteger *)dp hours:(nullable NSInteger *)hp minutes:(nullable NSInteger *)mip seconds:(nullable NSInteger *)sp sinceDate:(NSCalendarDate *)date NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
+ (instancetype)distantFuture NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
+ (instancetype)distantPast NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
@end

@interface NSDate (NSCalendarDateExtras)
/*    DEPRECATED DEPRECATED DEPRECATED
 *    These methods are deprecated.
 *    Use NSCalendar for calendrical calculations.
 *    Use NSDateFormatter for date<->string conversions.
 */
+ (nullable id)dateWithNaturalLanguageString:(NSString *)string locale:(nullable id)locale NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
+ (nullable id)dateWithNaturalLanguageString:(NSString *)string NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
+ (id)dateWithString:(NSString *)aString NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (NSCalendarDate *)dateWithCalendarFormat:(nullable NSString *)format timeZone:(nullable NSTimeZone *)aTimeZone NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (nullable NSString *)descriptionWithCalendarFormat:(nullable NSString *)format timeZone:(nullable NSTimeZone *)aTimeZone locale:(nullable id)locale NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
- (nullable id)initWithString:(NSString *)description NS_CALENDAR_DEPRECATED(10_4, 10_10, 2_0, 8_0);
@end

NS_ASSUME_NONNULL_END
