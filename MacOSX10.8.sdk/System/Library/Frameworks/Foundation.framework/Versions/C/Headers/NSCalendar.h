/*	NSCalendar.h
	Copyright (c) 2004-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>

#include <CoreFoundation/CFCalendar.h>

@class NSDateComponents, NSLocale, NSTimeZone, NSString;

typedef NS_ENUM(NSUInteger, NSCalendarUnit) {
	NSEraCalendarUnit = kCFCalendarUnitEra,
	NSYearCalendarUnit = kCFCalendarUnitYear,
	NSMonthCalendarUnit = kCFCalendarUnitMonth,
	NSDayCalendarUnit = kCFCalendarUnitDay,
	NSHourCalendarUnit = kCFCalendarUnitHour,
	NSMinuteCalendarUnit = kCFCalendarUnitMinute,
	NSSecondCalendarUnit = kCFCalendarUnitSecond,
	NSWeekCalendarUnit = kCFCalendarUnitWeek /* NS_DEPRECATED(10_4, 10_7, 2_0, 5_0) */,
	NSWeekdayCalendarUnit = kCFCalendarUnitWeekday,
	NSWeekdayOrdinalCalendarUnit = kCFCalendarUnitWeekdayOrdinal,
	NSQuarterCalendarUnit NS_ENUM_AVAILABLE(10_6, 4_0) = kCFCalendarUnitQuarter,
	NSWeekOfMonthCalendarUnit NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitWeekOfMonth,
	NSWeekOfYearCalendarUnit NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitWeekOfYear,
	NSYearForWeekOfYearCalendarUnit NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitYearForWeekOfYear,
        NSCalendarCalendarUnit NS_ENUM_AVAILABLE(10_7, 4_0) = (1 << 20),
        NSTimeZoneCalendarUnit NS_ENUM_AVAILABLE(10_7, 4_0) = (1 << 21),
};

@interface NSCalendar : NSObject <NSCopying, NSSecureCoding>

+ (id)currentCalendar; // users preferred calendar, tracks changes
+ (id)autoupdatingCurrentCalendar NS_AVAILABLE(10_5, 2_0);

- (id)initWithCalendarIdentifier:(NSString *)ident;

- (NSString *)calendarIdentifier;


- (void)setLocale:(NSLocale *)locale;
- (NSLocale *)locale;

- (void)setTimeZone:(NSTimeZone *)tz;
- (NSTimeZone *)timeZone;

- (void)setFirstWeekday:(NSUInteger)weekday;
- (NSUInteger)firstWeekday;

- (void)setMinimumDaysInFirstWeek:(NSUInteger)mdw;
- (NSUInteger)minimumDaysInFirstWeek;


- (NSRange)minimumRangeOfUnit:(NSCalendarUnit)unit;
- (NSRange)maximumRangeOfUnit:(NSCalendarUnit)unit;

- (NSRange)rangeOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;
- (NSUInteger)ordinalityOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;

- (BOOL)rangeOfUnit:(NSCalendarUnit)unit startDate:(NSDate **)datep interval:(NSTimeInterval *)tip forDate:(NSDate *)date NS_AVAILABLE(10_5, 2_0);

- (NSDate *)dateFromComponents:(NSDateComponents *)comps;
- (NSDateComponents *)components:(NSUInteger)unitFlags fromDate:(NSDate *)date;

- (NSDate *)dateByAddingComponents:(NSDateComponents *)comps toDate:(NSDate *)date options:(NSUInteger)opts;

- (NSDateComponents *)components:(NSUInteger)unitFlags fromDate:(NSDate *)startingDate toDate:(NSDate *)resultDate options:(NSUInteger)opts;

@end

enum {
	NSWrapCalendarComponents = kCFCalendarComponentsWrap,  // option for adding
};


// This is a just used as an extensible struct, basically;
// note that there are two uses: one for specifying a date
// via components (some components may be missing, making the
// specific date ambiguous), and the other for specifying a
// set of component quantities (like, 3 months and 5 hours).
// Undefined fields have (or fields can be set to) the value
// NSUndefinedDateComponent.
// NSDateComponents is not responsible for answering questions
// about a date beyond the information it has been initialized
// with; for example, if you initialize one with May 6, 2004,
// and then ask for the weekday, you'll get Undefined, not Thurs.
// A NSDateComponents is meaningless in itself, because you need
// to know what calendar it is interpreted against, and you need
// to know whether the values are absolute values of the units,
// or quantities of the units.
// When you create a new one of these, all values begin Undefined.

enum {
	NSUndefinedDateComponent = NSIntegerMax
};

@interface NSDateComponents : NSObject <NSCopying, NSSecureCoding>

- (NSCalendar *)calendar NS_AVAILABLE(10_7, 4_0);
- (NSTimeZone *)timeZone NS_AVAILABLE(10_7, 4_0);
- (NSInteger)era;
- (NSInteger)year;
- (NSInteger)month;
- (NSInteger)day;
- (NSInteger)hour;
- (NSInteger)minute;
- (NSInteger)second;
- (NSInteger)week;
- (NSInteger)weekday;
- (NSInteger)weekdayOrdinal;
- (NSInteger)quarter NS_AVAILABLE(10_6, 4_0);
- (NSInteger)weekOfMonth NS_AVAILABLE(10_7, 5_0);
- (NSInteger)weekOfYear NS_AVAILABLE(10_7, 5_0);
- (NSInteger)yearForWeekOfYear NS_AVAILABLE(10_7, 5_0);
- (BOOL)isLeapMonth NS_AVAILABLE(10_8, 6_0);

- (void)setCalendar:(NSCalendar *)cal NS_AVAILABLE(10_7, 4_0);
- (void)setTimeZone:(NSTimeZone *)tz NS_AVAILABLE(10_7, 4_0);
- (void)setEra:(NSInteger)v;
- (void)setYear:(NSInteger)v;
- (void)setMonth:(NSInteger)v;
- (void)setDay:(NSInteger)v;
- (void)setHour:(NSInteger)v;
- (void)setMinute:(NSInteger)v;
- (void)setSecond:(NSInteger)v;
- (void)setWeek:(NSInteger)v;
- (void)setWeekday:(NSInteger)v;
- (void)setWeekdayOrdinal:(NSInteger)v;
- (void)setQuarter:(NSInteger)v NS_AVAILABLE(10_6, 4_0);
- (void)setWeekOfMonth:(NSInteger)w NS_AVAILABLE(10_7, 5_0);
- (void)setWeekOfYear:(NSInteger)w NS_AVAILABLE(10_7, 5_0);
- (void)setYearForWeekOfYear:(NSInteger)y NS_AVAILABLE(10_7, 5_0);
- (void)setLeapMonth:(BOOL)lm NS_AVAILABLE(10_8, 6_0);

- (NSDate *)date NS_AVAILABLE(10_7, 4_0);

@end

