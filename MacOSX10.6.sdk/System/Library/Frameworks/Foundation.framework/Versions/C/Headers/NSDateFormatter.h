/*	NSDateFormatter.h
	Copyright (c) 1995-2009, Apple Inc. All rights reserved.
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

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id *)obj forString:(NSString *)string range:(inout NSRange *)rangep error:(out NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// Even though NSDateFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (NSString *)stringFromDate:(NSDate *)date AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSDate *)dateFromString:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

enum {    // date and time format styles
    NSDateFormatterNoStyle = kCFDateFormatterNoStyle,
    NSDateFormatterShortStyle = kCFDateFormatterShortStyle,
    NSDateFormatterMediumStyle = kCFDateFormatterMediumStyle,
    NSDateFormatterLongStyle = kCFDateFormatterLongStyle,
    NSDateFormatterFullStyle = kCFDateFormatterFullStyle
};
typedef NSUInteger NSDateFormatterStyle;

enum {
    NSDateFormatterBehaviorDefault = 0,
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    NSDateFormatterBehavior10_0 = 1000,
#endif
    NSDateFormatterBehavior10_4 = 1040,
};
typedef NSUInteger NSDateFormatterBehavior;

#endif

+ (NSString *)localizedStringFromDate:(NSDate *)date dateStyle:(NSDateFormatterStyle)dstyle timeStyle:(NSDateFormatterStyle)tstyle AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

+ (NSString *)dateFormatFromTemplate:(NSString *)tmplate options:(NSUInteger)opts locale:(NSLocale *)locale AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
	// no options defined, pass 0 for now

// Attributes of an NSDateFormatter

- (NSString *)dateFormat;

- (NSDateFormatterStyle)dateStyle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setDateStyle:(NSDateFormatterStyle)style AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDateFormatterStyle)timeStyle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setTimeStyle:(NSDateFormatterStyle)style AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSLocale *)locale AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setLocale:(NSLocale *)locale AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (BOOL)generatesCalendarDates AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setGeneratesCalendarDates:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDateFormatterBehavior)formatterBehavior AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setFormatterBehavior:(NSDateFormatterBehavior)behavior AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

+ (NSDateFormatterBehavior)defaultFormatterBehavior AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
+ (void)setDefaultFormatterBehavior:(NSDateFormatterBehavior)behavior AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (void)setDateFormat:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSTimeZone *)timeZone AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setTimeZone:(NSTimeZone *)tz AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSCalendar *)calendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setCalendar:(NSCalendar *)calendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (BOOL)isLenient AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setLenient:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDate *)twoDigitStartDate AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setTwoDigitStartDate:(NSDate *)date AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSDate *)defaultDate AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setDefaultDate:(NSDate *)date AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSArray *)eraSymbols AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setEraSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSArray *)monthSymbols AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setMonthSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSArray *)shortMonthSymbols AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setShortMonthSymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSArray *)weekdaySymbols AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setWeekdaySymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSArray *)shortWeekdaySymbols AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setShortWeekdaySymbols:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)AMSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setAMSymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSString *)PMSymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setPMSymbol:(NSString *)string AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

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

- (BOOL)doesRelativeDateFormatting AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setDoesRelativeDateFormatting:(BOOL)b AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSDateFormatter (NSDateFormatterCompatibility)

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag;
- (BOOL)allowsNaturalLanguage;

@end
#endif

