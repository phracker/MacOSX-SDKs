//
//  CLKTextProvider.h
//  ClockKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <ClockKit/CLKDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;

API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(2.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios)
@interface CLKTextProvider : NSObject <NSCopying>

- (instancetype)init API_DEPRECATED("Use initializers that take parameters.", watchos(2.0, 7.0), ios(9.0, 14.0));
+ (instancetype)new API_DEPRECATED("Use factory methods that take parameters.", watchos(2.0, 7.0), ios(9.0, 14.0));

// By passing one or more CLKTextProviders in the format substitutions, you can add text around the output of a text provider.
// In certain multi-color contexts, it can provide multi-color text to the template by nesting text providers with different tint colors.
+ (CLKTextProvider *)textProviderWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);

@property (nonatomic, retain) UIColor *tintColor;

@property (nonatomic, copy, nullable) NSString *accessibilityLabel;

@end


#pragma mark - Simple

// Simple text providers display arbitrary text. If shortText is provided, we will fall back on it before truncating.
// If accessibilityLabel is provided, it will be used in place of the text property for VoiceOver.

API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(2.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios)
@interface CLKSimpleTextProvider : CLKTextProvider

- (instancetype)initWithText:(NSString *)text API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");
- (instancetype)initWithText:(NSString *)text shortText:(NSString * __nullable)shortText API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");
- (instancetype)initWithText:(NSString *)text shortText:(NSString * __nullable)shortText accessibilityLabel:(NSString * __nullable)accessibilityLabel API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");

+ (instancetype)textProviderWithText:(NSString *)text;
+ (instancetype)textProviderWithText:(NSString *)text shortText:(NSString * __nullable)shortText;
+ (instancetype)textProviderWithText:(NSString *)text shortText:(NSString * __nullable)shortText accessibilityLabel:(NSString * __nullable)accessibilityLabel;

@property (nonatomic, copy) NSString *text;
@property (nonatomic, copy, nullable) NSString *shortText;

@end


#pragma mark - Date

// Date text providers can display any subset of the following calendar units:
//    NSCalendarUnitYear
//    NSCalendarUnitMonth
//    NSCalendarUnitDay
//    NSCalendarUnitWeekday
// Unsupported calendar units will be ignored.
//
// We will attempt to include all of the requested units in the output string, but will drop units before truncating.
//
// For example, if you ask for Weekday, Month, and Day units, and the locale is English-US, we would attempt the following outputs in order, space permitting:
//    Wednesday, December 23
//    Wednesday, Dec 23
//    Wed, Dec 23
//    Dec 23
//    23

API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(2.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios)
@interface CLKDateTextProvider : CLKTextProvider

- (instancetype)initWithDate:(NSDate *)date units:(NSCalendarUnit)calendarUnits API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");
- (instancetype)initWithDate:(NSDate *)date units:(NSCalendarUnit)calendarUnits timeZone:(NSTimeZone * __nullable)timeZone API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");

+ (instancetype)textProviderWithDate:(NSDate *)date units:(NSCalendarUnit)calendarUnits;
+ (instancetype)textProviderWithDate:(NSDate *)date units:(NSCalendarUnit)calendarUnits timeZone:(NSTimeZone * __nullable)timeZone;

@property (nonatomic, retain) NSDate *date;
@property (nonatomic) NSCalendarUnit calendarUnits;
@property (nonatomic, nullable, retain) NSTimeZone *timeZone;
@property (nonatomic) BOOL uppercase;

@end


#pragma mark - Time

// Time text providers will display a time in one of the following two formats, depending on the available space:
//   11:23PM
//   11:23

API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(2.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios)
@interface CLKTimeTextProvider : CLKTextProvider

- (instancetype)initWithDate:(NSDate *)date API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");
- (instancetype)initWithDate:(NSDate *)date timeZone:(NSTimeZone * __nullable)timeZone API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");

+ (instancetype)textProviderWithDate:(NSDate *)date;
+ (instancetype)textProviderWithDate:(NSDate *)date timeZone:(NSTimeZone * __nullable)timeZone;

@property (nonatomic, retain) NSDate *date;
@property (nonatomic, nullable, retain) NSTimeZone *timeZone;

@end


#pragma mark - Time Interval

// Time interval text providers will display a date range in a variety of different ways, depending on the size of the interval and the available space:
//
// Some examples:
//   If one date is in the AM and the other is in the PM:
//      9:30AM - 3:30PM
//   If both dates are in the AM (or PM):
//      9:30 - 10:30AM
//      9:30 - 10:30PM
//   If interval is greater than 24 hours:
//      Jan 1 - Jan 7
//      1/1 - 1/7
//
// If space is constrained, this text provider will fall back on showing only the startDate before truncating.

API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(2.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios)
@interface CLKTimeIntervalTextProvider : CLKTextProvider

- (instancetype)initWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");
- (instancetype)initWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate timeZone:(NSTimeZone * __nullable)timeZone API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");

+ (instancetype)textProviderWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate;
+ (instancetype)textProviderWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate timeZone:(NSTimeZone * __nullable)timeZone;

@property (nonatomic, retain) NSDate *startDate;
@property (nonatomic, retain) NSDate *endDate;
@property (nonatomic, nullable, retain) NSTimeZone *timeZone;

@end


#pragma mark - Relative Date

// Relative date text providers display the difference between now and the provided date.
//
// They support the following calendar units:
//    NSCalendarUnitYear
//    NSCalendarUnitMonth
//    NSCalendarUnitWeekOfMonth (used to mean "quantity of weeks")
//    NSCalendarUnitDay
//    NSCalendarUnitHour
//    NSCalendarUnitMinute
//    NSCalendarUnitSecond
//
// Three formatting styles are supported.
//    Natural:
//       0 mins
//       2hrs 7mins
//       13mins 5secs
//       3wks 4days
//       2yrs 3mos
//    Offset:
//       Now
//       +14 seconds
//       -59 minutes
//       +2 hours
//       -6 days
//       +12 weeks
//    Timer (only supports hours, minutes, seconds):
//       0:14
//       2:32
//       21:15:59

typedef NS_ENUM(NSInteger, CLKRelativeDateStyle) {
    CLKRelativeDateStyleNatural,
    CLKRelativeDateStyleOffset,
    CLKRelativeDateStyleTimer,
    CLKRelativeDateStyleNaturalAbbreviated API_AVAILABLE(watchos(5.0)),
    CLKRelativeDateStyleOffsetShort API_AVAILABLE(watchos(6.0)),
    CLKRelativeDateStyleNaturalFull API_AVAILABLE(watchos(6.0)),
}  API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(2.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios);

API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(2.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios)
@interface CLKRelativeDateTextProvider : CLKTextProvider

- (instancetype)initWithDate:(NSDate *)date style:(CLKRelativeDateStyle)style units:(NSCalendarUnit)calendarUnits API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");
- (instancetype)initWithDate:(NSDate *)date relativeToDate:(NSDate * __nullable)relativeDate style:(CLKRelativeDateStyle)style units:(NSCalendarUnit)calendarUnits API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");

+ (instancetype)textProviderWithDate:(NSDate *)date style:(CLKRelativeDateStyle)style units:(NSCalendarUnit)calendarUnits;
+ (instancetype)textProviderWithDate:(NSDate *)date relativeToDate:(NSDate * __nullable)relativeToDate style:(CLKRelativeDateStyle)style units:(NSCalendarUnit)calendarUnits API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

@property (nonatomic, retain) NSDate *date;
@property (nonatomic, nullable, retain) NSDate *relativeToDate API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);
@property (nonatomic) CLKRelativeDateStyle relativeDateStyle;
@property (nonatomic) NSCalendarUnit calendarUnits;

@end


#pragma mark - Localizable

API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(2.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios)
@interface CLKTextProvider (Localizable)

// Creates a localizable simple text provider with a strings file key for the text and (optionally) a strings file key for shorter fallback text.
+ (instancetype)localizableTextProviderWithStringsFileTextKey:(NSString *)textKey API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios);
+ (instancetype)localizableTextProviderWithStringsFileTextKey:(NSString *)textKey shortTextKey:(NSString * __nullable)shortTextKey API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios);

// Creates a localizable text provider with a strings file key that resolves to a format, and text provider replacement arguments.
// Since the replacement arguments must all be text providers, the only allowable format specifiers are %@ and variants. (Reordering specifiers like %1@ are supported.)
+ (instancetype)localizableTextProviderWithStringsFileFormatKey:(NSString *)formatKey textProviders:(NSArray<CLKTextProvider *> *)textProviders API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios);

@end

NS_ASSUME_NONNULL_END

