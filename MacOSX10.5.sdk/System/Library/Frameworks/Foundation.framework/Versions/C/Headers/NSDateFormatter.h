/*	NSDateFormatter.h
	Copyright (c) 1995-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFDateFormatter.h>

@class NSLocale, NSDate, NSCalendar, NSTimeZone, NSError, NSArray, NSMutableDictionary;

@interface NSDateFormatter : NSFormatter {
@private
    NSMutableDictionary *_attributes;
    __strong CFDateFormatterRef _formatter;
    NSUInteger _counter;
}

- (id)init;

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(id *)obj forString:(NSString *)string range:(inout NSRange *)rangep error:(NSError **)error;

// Even though NSDateFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (NSString *)stringFromDate:(NSDate *)date;
- (NSDate *)dateFromString:(NSString *)string;

#endif

// Attributes of an NSDateFormatter

- (NSString *)dateFormat;

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

enum {    // date and time format styles
    NSDateFormatterNoStyle = kCFDateFormatterNoStyle,
    NSDateFormatterShortStyle = kCFDateFormatterShortStyle,
    NSDateFormatterMediumStyle = kCFDateFormatterMediumStyle,
    NSDateFormatterLongStyle = kCFDateFormatterLongStyle,
    NSDateFormatterFullStyle = kCFDateFormatterFullStyle
};
typedef NSUInteger NSDateFormatterStyle;

- (NSDateFormatterStyle)dateStyle;
- (void)setDateStyle:(NSDateFormatterStyle)style;

- (NSDateFormatterStyle)timeStyle;
- (void)setTimeStyle:(NSDateFormatterStyle)style;

- (NSLocale *)locale;
- (void)setLocale:(NSLocale *)locale;

- (BOOL)generatesCalendarDates;
- (void)setGeneratesCalendarDates:(BOOL)b;

enum {
    NSDateFormatterBehaviorDefault = 0,
    NSDateFormatterBehavior10_0 = 1000,
    NSDateFormatterBehavior10_4 = 1040,
};
typedef NSUInteger NSDateFormatterBehavior;

- (NSDateFormatterBehavior)formatterBehavior;
- (void)setFormatterBehavior:(NSDateFormatterBehavior)behavior;

+ (NSDateFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSDateFormatterBehavior)behavior;

- (void)setDateFormat:(NSString *)string;

- (NSTimeZone *)timeZone;
- (void)setTimeZone:(NSTimeZone *)tz;

- (NSCalendar *)calendar;
- (void)setCalendar:(NSCalendar *)calendar;

- (BOOL)isLenient;
- (void)setLenient:(BOOL)b;

- (NSDate *)twoDigitStartDate;
- (void)setTwoDigitStartDate:(NSDate *)date;

- (NSDate *)defaultDate;
- (void)setDefaultDate:(NSDate *)date;

- (NSArray *)eraSymbols;
- (void)setEraSymbols:(NSArray *)array;

- (NSArray *)monthSymbols;
- (void)setMonthSymbols:(NSArray *)array;

- (NSArray *)shortMonthSymbols;
- (void)setShortMonthSymbols:(NSArray *)array;

- (NSArray *)weekdaySymbols;
- (void)setWeekdaySymbols:(NSArray *)array;

- (NSArray *)shortWeekdaySymbols;
- (void)setShortWeekdaySymbols:(NSArray *)array;

- (NSString *)AMSymbol;
- (void)setAMSymbol:(NSString *)string;

- (NSString *)PMSymbol;
- (void)setPMSymbol:(NSString *)string;

#endif

- (NSArray *)longEraSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setLongEraSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)veryShortMonthSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setVeryShortMonthSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)standaloneMonthSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setStandaloneMonthSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)shortStandaloneMonthSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setShortStandaloneMonthSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)veryShortStandaloneMonthSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setVeryShortStandaloneMonthSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)veryShortWeekdaySymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setVeryShortWeekdaySymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)standaloneWeekdaySymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setStandaloneWeekdaySymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)shortStandaloneWeekdaySymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setShortStandaloneWeekdaySymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)veryShortStandaloneWeekdaySymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setVeryShortStandaloneWeekdaySymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)quarterSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setQuarterSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)shortQuarterSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setShortQuarterSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)standaloneQuarterSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setStandaloneQuarterSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSArray *)shortStandaloneQuarterSymbols AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setShortStandaloneQuarterSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSDate *)gregorianStartDate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setGregorianStartDate:(NSDate *)date AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

@interface NSDateFormatter (NSDateFormatterCompatibility)

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag;
- (BOOL)allowsNaturalLanguage;

@end

