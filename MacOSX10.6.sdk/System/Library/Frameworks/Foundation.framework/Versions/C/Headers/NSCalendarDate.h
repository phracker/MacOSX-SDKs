/*	NSCalendarDate.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSDate.h>

@class NSString, NSArray, NSTimeZone;

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
+ (id)calendarDate;
+ (id)dateWithString:(NSString *)description calendarFormat:(NSString *)format locale:(id)locale;
+ (id)dateWithString:(NSString *)description calendarFormat:(NSString *)format;
+ (id)dateWithYear:(NSInteger)year month:(NSUInteger)month day:(NSUInteger)day hour:(NSUInteger)hour minute:(NSUInteger)minute second:(NSUInteger)second timeZone:(NSTimeZone *)aTimeZone;
- (NSCalendarDate *)dateByAddingYears:(NSInteger)year months:(NSInteger)month days:(NSInteger)day hours:(NSInteger)hour minutes:(NSInteger)minute seconds:(NSInteger)second;
- (NSInteger)dayOfCommonEra;
- (NSInteger)dayOfMonth;
- (NSInteger)dayOfWeek;
- (NSInteger)dayOfYear;
- (NSInteger)hourOfDay;
- (NSInteger)minuteOfHour;
- (NSInteger)monthOfYear;
- (NSInteger)secondOfMinute;
- (NSInteger)yearOfCommonEra;
- (NSString *)calendarFormat;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format locale:(id)locale;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format;
- (NSString *)descriptionWithLocale:(id)locale;
- (NSTimeZone *)timeZone;
- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format locale:(id)locale;
- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format;
- (id)initWithString:(NSString *)description;
- (id)initWithYear:(NSInteger)year month:(NSUInteger)month day:(NSUInteger)day hour:(NSUInteger)hour minute:(NSUInteger)minute second:(NSUInteger)second timeZone:(NSTimeZone *)aTimeZone;
- (void)setCalendarFormat:(NSString *)format;
- (void)setTimeZone:(NSTimeZone *)aTimeZone;
- (void)years:(NSInteger *)yp months:(NSInteger *)mop days:(NSInteger *)dp hours:(NSInteger *)hp minutes:(NSInteger *)mip seconds:(NSInteger *)sp sinceDate:(NSCalendarDate *)date;

@end

@interface NSDate (NSCalendarDateExtras)
/*    DEPRECATED DEPRECATED DEPRECATED
 *    These methods are deprecated.
 *    Use NSCalendar for calendrical calculations.
 *    Use NSDateFormatter for date<->string conversions.
 */
+ (id)dateWithNaturalLanguageString:(NSString *)string locale:(id)locale;
+ (id)dateWithNaturalLanguageString:(NSString *)string;
+ (id)dateWithString:(NSString *)aString;
- (NSCalendarDate *)dateWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone locale:(id)locale;
- (id)initWithString:(NSString *)description;
@end

