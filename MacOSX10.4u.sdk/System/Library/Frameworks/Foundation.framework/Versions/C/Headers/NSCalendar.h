/*	NSCalendar.h
	Copyright (c) 2004-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

#include <CoreFoundation/CFCalendar.h>

@class NSDateComponents, NSLocale, NSTimeZone, NSDate, NSString;

typedef enum {
	NSEraCalendarUnit = kCFCalendarUnitEra,
	NSYearCalendarUnit = kCFCalendarUnitYear,
	NSMonthCalendarUnit = kCFCalendarUnitMonth,
	NSDayCalendarUnit = kCFCalendarUnitDay,
	NSHourCalendarUnit = kCFCalendarUnitHour,
	NSMinuteCalendarUnit = kCFCalendarUnitMinute,
	NSSecondCalendarUnit = kCFCalendarUnitSecond,
	NSWeekCalendarUnit = kCFCalendarUnitWeek,
	NSWeekdayCalendarUnit = kCFCalendarUnitWeekday,
	NSWeekdayOrdinalCalendarUnit = kCFCalendarUnitWeekdayOrdinal,
} NSCalendarUnit;

@interface NSCalendar : NSObject <NSCopying, NSCoding>

+ (id)currentCalendar; // users preferred calendar, tracks changes

- (id)initWithCalendarIdentifier:(NSString *)ident;

- (NSString *)calendarIdentifier;


- (void)setLocale:(NSLocale *)locale;
- (NSLocale *)locale;

- (void)setTimeZone:(NSTimeZone *)tz;
- (NSTimeZone *)timeZone;

- (void)setFirstWeekday:(unsigned)weekday;
- (unsigned)firstWeekday;

- (void)setMinimumDaysInFirstWeek:(unsigned)mdw;
- (unsigned)minimumDaysInFirstWeek;


- (NSRange)minimumRangeOfUnit:(NSCalendarUnit)unit;
- (NSRange)maximumRangeOfUnit:(NSCalendarUnit)unit;

- (NSRange)rangeOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;
- (unsigned)ordinalityOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;

- (NSDate *)dateFromComponents:(NSDateComponents *)comps;
- (NSDateComponents *)components:(unsigned)unitFlags fromDate:(NSDate *)date;

- (NSDate *)dateByAddingComponents:(NSDateComponents *)comps toDate:(NSDate *)date options:(unsigned)opts;

- (NSDateComponents *)components:(unsigned)unitFlags fromDate:(NSDate *)startingDate toDate:(NSDate *)resultDate options:(unsigned)opts;

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
	NSUndefinedDateComponent = 0x7fffffff
};

@interface NSDateComponents : NSObject <NSCopying, NSCoding>
- (int)era;
- (int)year;
- (int)month;
- (int)day;
- (int)hour;
- (int)minute;
- (int)second;
- (int)week;
- (int)weekday;
- (int)weekdayOrdinal;

- (void)setEra:(int)v;
- (void)setYear:(int)v;
- (void)setMonth:(int)v;
- (void)setDay:(int)v;
- (void)setHour:(int)v;
- (void)setMinute:(int)v;
- (void)setSecond:(int)v;
- (void)setWeek:(int)v;
- (void)setWeekday:(int)v;
- (void)setWeekdayOrdinal:(int)v;
@end

#endif

