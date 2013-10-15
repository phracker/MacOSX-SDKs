/*	NSCalendarDate.h
	Copyright (c) 1994-2007, Apple Inc. All rights reserved.
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

+ (id)dateWithYear:(NSInteger)year month:(NSUInteger)month day:(NSUInteger)day hour:(NSUInteger)hour minute:(NSUInteger)minute second:(NSUInteger)second timeZone:(NSTimeZone *)aTimeZone;

+ (id)dateWithString:(NSString *)description calendarFormat:(NSString *)format;

+ (id)dateWithString:(NSString *)description calendarFormat:(NSString *)format locale:(id)locale;

+ (id)calendarDate;

- (id)initWithYear:(NSInteger)year month:(NSUInteger)month day:(NSUInteger)day hour:(NSUInteger)hour minute:(NSUInteger)minute second:(NSUInteger)second timeZone:(NSTimeZone *)aTimeZone;
    
- (id)initWithString:(NSString *)description;
- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format;

- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format locale:(id)locale;

- (NSTimeZone *)timeZone;
- (void)setTimeZone:(NSTimeZone *)aTimeZone;

- (NSString *)calendarFormat;
- (void)setCalendarFormat:(NSString *)format;

- (NSInteger)yearOfCommonEra;
- (NSInteger)monthOfYear;
- (NSInteger)dayOfMonth;
- (NSInteger)dayOfWeek;
- (NSInteger)dayOfYear;
- (NSInteger)dayOfCommonEra;
- (NSInteger)hourOfDay;
- (NSInteger)minuteOfHour;
- (NSInteger)secondOfMinute;

- (NSCalendarDate *)dateByAddingYears:(NSInteger)year months:(NSInteger)month days:(NSInteger)day hours:(NSInteger)hour minutes:(NSInteger)minute seconds:(NSInteger)second;

- (void)years:(NSInteger *)yp months:(NSInteger *)mop days:(NSInteger *)dp hours:(NSInteger *)hp minutes:(NSInteger *)mip seconds:(NSInteger *)sp sinceDate:(NSCalendarDate *)date;

- (NSString *)description;
- (NSString *)descriptionWithLocale:(id)locale;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format locale:(id)locale;

@end

/*******	Conveniences to deal with Western calendar	*******/

@interface NSDate (NSCalendarDateExtras)

+ (id)dateWithString:(NSString *)aString;

- (id)initWithString:(NSString *)description;

- (NSCalendarDate *)dateWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone;

- (NSString *)descriptionWithLocale:(id)locale;

- (NSString *)descriptionWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone locale:(id)locale;

@end

@interface NSDate (NSNaturalLangage)

+ dateWithNaturalLanguageString:(NSString *)string;
+ dateWithNaturalLanguageString:(NSString *)string locale:(id)locale;

@end

