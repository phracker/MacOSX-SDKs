/*	NSCalendarDate.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSDate.h>

@class NSString, NSArray, NSDictionary, NSTimeZone;

@interface NSCalendarDate : NSDate {
@private
    unsigned		refCount;
    NSTimeInterval 	_timeIntervalSinceReferenceDate;
    NSTimeZone		*_timeZone;
    NSString 		*_formatString;
    void		*_reserved;
}

+ (id)dateWithYear:(int)year month:(unsigned)month day:(unsigned)day hour:(unsigned)hour minute:(unsigned)minute second:(unsigned)second timeZone:(NSTimeZone *)aTimeZone;

+ (id)dateWithString:(NSString *)description calendarFormat:(NSString *)format;

+ (id)dateWithString:(NSString *)description calendarFormat:(NSString *)format locale:(NSDictionary *)dict;

+ (id)calendarDate;

- (id)initWithYear:(int)year month:(unsigned)month day:(unsigned)day hour:(unsigned)hour minute:(unsigned)minute second:(unsigned)second timeZone:(NSTimeZone *)aTimeZone;
    
- (id)initWithString:(NSString *)description;
- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format;

- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format locale:(NSDictionary *)dict;

- (NSTimeZone *)timeZone;
- (void)setTimeZone:(NSTimeZone *)aTimeZone;

- (NSString *)calendarFormat;
- (void)setCalendarFormat:(NSString *)format;

- (int)yearOfCommonEra;
- (int)monthOfYear;
- (int)dayOfMonth;
- (int)dayOfWeek;
- (int)dayOfYear;
- (int)dayOfCommonEra;
- (int)hourOfDay;
- (int)minuteOfHour;
- (int)secondOfMinute;

- (NSCalendarDate *)dateByAddingYears:(int)year months:(int)month days:(int)day hours:(int)hour minutes:(int)minute seconds:(int)second;

- (void)years:(int *)yp months:(int *)mop days:(int *)dp hours:(int *)hp minutes:(int *)mip seconds:(int *)sp sinceDate:(NSCalendarDate *)date;

- (NSString *)description;
- (NSString *)descriptionWithLocale:(NSDictionary *)locale;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format locale:(NSDictionary *)locale;

@end

/*******	Conveniences to deal with Western calendar	*******/

@interface NSDate (NSCalendarDateExtras)

+ (id)dateWithString:(NSString *)aString;

- (id)initWithString:(NSString *)description;

- (NSCalendarDate *)dateWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone;

- (NSString *)descriptionWithLocale:(NSDictionary *)locale;

- (NSString *)descriptionWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone locale:(NSDictionary *)locale;

@end

@interface NSDate (NSNaturalLangage)

+ dateWithNaturalLanguageString:(NSString *)string;
+ dateWithNaturalLanguageString:(NSString *)string locale:(NSDictionary *)dict;

@end

