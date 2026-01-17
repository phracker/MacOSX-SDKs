/*	NSDateFormatter.h
	Copyright (c) 1995-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFDateFormatter.h>

@class NSLocale, NSDate, NSCalendar, NSTimeZone, NSError, NSArray, NSMutableDictionary;

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


@interface NSDateFormatter : NSFormatter {
@private
    NSMutableDictionary *_attributes;
    __strong CFDateFormatterRef _formatter;
    NSUInteger _counter;
}

@property NSFormattingContext formattingContext NS_AVAILABLE(10_10, 8_0); // default is NSFormattingContextUnknown

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

+ (NSDateFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSDateFormatterBehavior)behavior;

/*
 A convenient way to generate an appropriate localized date format, and set it, in a single operation.

 Equivalent to, though not necessarily implemented as:
 formatter.dateFormat = [NSDateFormatter dateFormatFromTemplate:dateFormatTemplate options:0 locale:formatter.locale];

 Note that the template string is used only to specify which date format components should be included. Ordering and other text will not be preserved.
 The parameter is also not stored, or updated when the locale or other options change, just as with the ‘dateFormat’ property.
 */
- (void) setLocalizedDateFormatFromTemplate:(NSString *)dateFormatTemplate NS_AVAILABLE(10_10, 8_0);

@property (copy) NSString *dateFormat;
@property NSDateFormatterStyle dateStyle;
@property NSDateFormatterStyle timeStyle;
@property (copy) NSLocale *locale;
@property BOOL generatesCalendarDates;
@property NSDateFormatterBehavior formatterBehavior;
@property (copy) NSTimeZone *timeZone;
@property (copy) NSCalendar *calendar;
@property (getter=isLenient) BOOL lenient;
@property (copy) NSDate *twoDigitStartDate;
@property (copy) NSDate *defaultDate;
@property (copy) NSArray *eraSymbols;
@property (copy) NSArray *monthSymbols;
@property (copy) NSArray *shortMonthSymbols;
@property (copy) NSArray *weekdaySymbols;
@property (copy) NSArray *shortWeekdaySymbols;
@property (copy) NSString *AMSymbol;
@property (copy) NSString *PMSymbol;
@property (copy) NSArray *longEraSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *veryShortMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *standaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *shortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *veryShortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *veryShortWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *standaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *shortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *veryShortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *quarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *shortQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *standaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSArray *shortStandaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (copy) NSDate *gregorianStartDate NS_AVAILABLE(10_5, 2_0);
@property BOOL doesRelativeDateFormatting NS_AVAILABLE(10_6, 4_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSDateFormatter (NSDateFormatterCompatibility)

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "Use -setDateFormat: as of OS X 10.9 to set the date format of a 10.0-style date formatter; but expect 10.0-style date formatting to be deprecated in the future as well");
- (BOOL)allowsNaturalLanguage NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "There is no replacement");

@end
#endif

