/*	NSDateFormatter.h
	Copyright (c) 1995-2013, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFDateFormatter.h>

@class NSLocale, NSDate, NSCalendar, NSTimeZone, NSError, NSArray, NSMutableDictionary;

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#if NS_ENABLE_CALENDAR_DEPRECATIONS
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#else
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_AVAILABLE(A, C)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_AVAILABLE(A, C)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_AVAILABLE_MAC(A)
#endif
#endif


@interface NSDateFormatter : NSFormatter {
@private
    NSMutableDictionary *_attributes;
    __strong CFDateFormatterRef _formatter;
    NSUInteger _counter;
}

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id *)obj forString:(NSString *)string range:(inout NSRange *)rangep error:(out NSError **)error;

// Even though NSDateFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (NSString *)stringFromDate:(NSDate *)date;
- (NSDate *)dateFromString:(NSString *)string;

typedef NS_ENUM(NSUInteger, NSDateFormatterStyle) {    // date and time format styles
    NSDateFormatterNoStyle = kCFDateFormatterNoStyle,
    NSDateFormatterShortStyle = kCFDateFormatterShortStyle,
    NSDateFormatterMediumStyle = kCFDateFormatterMediumStyle,
    NSDateFormatterLongStyle = kCFDateFormatterLongStyle,
    NSDateFormatterFullStyle = kCFDateFormatterFullStyle
};

typedef NS_ENUM(NSUInteger, NSDateFormatterBehavior) {
    NSDateFormatterBehaviorDefault = 0,
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    NSDateFormatterBehavior10_0 = 1000,
#endif
    NSDateFormatterBehavior10_4 = 1040,
};


+ (NSString *)localizedStringFromDate:(NSDate *)date dateStyle:(NSDateFormatterStyle)dstyle timeStyle:(NSDateFormatterStyle)tstyle NS_AVAILABLE(10_6, 4_0);

+ (NSString *)dateFormatFromTemplate:(NSString *)tmplate options:(NSUInteger)opts locale:(NSLocale *)locale NS_AVAILABLE(10_6, 4_0);
	// no options defined, pass 0 for now

// Attributes of an NSDateFormatter

- (NSString *)dateFormat;

- (NSDateFormatterStyle)dateStyle;
- (void)setDateStyle:(NSDateFormatterStyle)style;

- (NSDateFormatterStyle)timeStyle;
- (void)setTimeStyle:(NSDateFormatterStyle)style;

- (NSLocale *)locale;
- (void)setLocale:(NSLocale *)locale;

- (BOOL)generatesCalendarDates;
- (void)setGeneratesCalendarDates:(BOOL)b;

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

- (NSArray *)longEraSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setLongEraSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)veryShortMonthSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setVeryShortMonthSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)standaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setStandaloneMonthSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)shortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setShortStandaloneMonthSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)veryShortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setVeryShortStandaloneMonthSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)veryShortWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
- (void)setVeryShortWeekdaySymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)standaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
- (void)setStandaloneWeekdaySymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)shortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
- (void)setShortStandaloneWeekdaySymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)veryShortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
- (void)setVeryShortStandaloneWeekdaySymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)quarterSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setQuarterSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)shortQuarterSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setShortQuarterSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)standaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setStandaloneQuarterSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSArray *)shortStandaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
- (void)setShortStandaloneQuarterSymbols:(NSArray *)array NS_AVAILABLE(10_5, 2_0);

- (NSDate *)gregorianStartDate NS_AVAILABLE(10_5, 2_0);
- (void)setGregorianStartDate:(NSDate *)date NS_AVAILABLE(10_5, 2_0);

- (BOOL)doesRelativeDateFormatting NS_AVAILABLE(10_6, 4_0);
- (void)setDoesRelativeDateFormatting:(BOOL)b NS_AVAILABLE(10_6, 4_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSDateFormatter (NSDateFormatterCompatibility)

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "Use -setDateFormat: as of OS X 10.9 to set the date format of a 10.0-style date formatter; but expect 10.0-style date formatting to be deprecated in the future as well");
- (BOOL)allowsNaturalLanguage NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "Use -setDateFormat: as of OS X 10.9 to set the date format of a 10.0-style date formatter; but expect 10.0-style date formatting to be deprecated in the future as well");

@end
#endif

