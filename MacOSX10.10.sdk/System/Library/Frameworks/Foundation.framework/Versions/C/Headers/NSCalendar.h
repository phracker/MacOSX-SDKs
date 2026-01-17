/*	NSCalendar.h
	Copyright (c) 2004-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>
#include <CoreFoundation/CFCalendar.h>

@class NSDateComponents, NSLocale, NSTimeZone, NSString, NSArray;

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

FOUNDATION_EXPORT NSString * const NSCalendarIdentifierGregorian  NS_AVAILABLE(10_6, 4_0); // the common calendar in Europe, the Western Hemisphere, and elsewhere
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierBuddhist            NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierChinese             NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierCoptic              NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierEthiopicAmeteMihret NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierEthiopicAmeteAlem   NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierHebrew              NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierISO8601             NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIndian              NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIslamic             NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIslamicCivil        NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierJapanese            NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierPersian             NS_AVAILABLE(10_6, 4_0);
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierRepublicOfChina     NS_AVAILABLE(10_6, 4_0);
// A simple tabular Islamic calendar using the astronomical/Thursday epoch of CE 622 July 15
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIslamicTabular      NS_AVAILABLE(10_10, 8_0);
// The Islamic Umm al-Qura calendar used in Saudi Arabia. This is based on astronomical calculation, instead of tabular behavior.
FOUNDATION_EXPORT NSString * const NSCalendarIdentifierIslamicUmmAlQura    NS_AVAILABLE(10_10, 8_0);


typedef NS_OPTIONS(NSUInteger, NSCalendarUnit) {
        NSCalendarUnitEra                = kCFCalendarUnitEra,
        NSCalendarUnitYear               = kCFCalendarUnitYear,
        NSCalendarUnitMonth              = kCFCalendarUnitMonth,
        NSCalendarUnitDay                = kCFCalendarUnitDay,
        NSCalendarUnitHour               = kCFCalendarUnitHour,
        NSCalendarUnitMinute             = kCFCalendarUnitMinute,
        NSCalendarUnitSecond             = kCFCalendarUnitSecond,
        NSCalendarUnitWeekday            = kCFCalendarUnitWeekday,
        NSCalendarUnitWeekdayOrdinal     = kCFCalendarUnitWeekdayOrdinal,
        NSCalendarUnitQuarter            NS_ENUM_AVAILABLE(10_6, 4_0) = kCFCalendarUnitQuarter,
        NSCalendarUnitWeekOfMonth        NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitWeekOfMonth,
        NSCalendarUnitWeekOfYear         NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitWeekOfYear,
        NSCalendarUnitYearForWeekOfYear  NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitYearForWeekOfYear,
        NSCalendarUnitNanosecond         NS_ENUM_AVAILABLE(10_7, 5_0) = (1 << 15),
        NSCalendarUnitCalendar           NS_ENUM_AVAILABLE(10_7, 4_0) = (1 << 20),
        NSCalendarUnitTimeZone           NS_ENUM_AVAILABLE(10_7, 4_0) = (1 << 21),

	NSEraCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitEra instead") = NSCalendarUnitEra,
	NSYearCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitYear instead") = NSCalendarUnitYear,
	NSMonthCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitMonth instead") = NSCalendarUnitMonth,
	NSDayCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitDay instead") = NSCalendarUnitDay,
	NSHourCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitHour instead") = NSCalendarUnitHour,
	NSMinuteCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitMinute instead") = NSCalendarUnitMinute,
	NSSecondCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitSecond instead") = NSCalendarUnitSecond,
	NSWeekCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitWeekOfMonth or NSCalendarUnitWeekOfYear, depending on which you mean") = kCFCalendarUnitWeek,
	NSWeekdayCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitWeekday instead") = NSCalendarUnitWeekday,
	NSWeekdayOrdinalCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarUnitWeekdayOrdinal instead") = NSCalendarUnitWeekdayOrdinal,
	NSQuarterCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_6, 10_10, 4_0, 8_0, "Use NSCalendarUnitQuarter instead") = NSCalendarUnitQuarter,
	NSWeekOfMonthCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 5_0, 8_0, "Use NSCalendarUnitWeekOfMonth instead") = NSCalendarUnitWeekOfMonth,
	NSWeekOfYearCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 5_0, 8_0, "Use NSCalendarUnitWeekOfYear instead") = NSCalendarUnitWeekOfYear,
	NSYearForWeekOfYearCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 5_0, 8_0, "Use NSCalendarUnitYearForWeekOfYear instead") = NSCalendarUnitYearForWeekOfYear,
	NSCalendarCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 4_0, 8_0, "Use NSCalendarUnitCalendar instead") = NSCalendarUnitCalendar,
	NSTimeZoneCalendarUnit NS_CALENDAR_ENUM_DEPRECATED(10_7, 10_10, 4_0, 8_0, "Use NSCalendarUnitTimeZone instead") = NSCalendarUnitTimeZone,
};
    
typedef NS_OPTIONS(NSUInteger, NSCalendarOptions) {
	NSCalendarWrapComponents = (1UL << 0), // option for arithmetic operations that do calendar addition

	NSCalendarMatchStrictly    NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 1),
	NSCalendarSearchBackwards  NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 2),
    
	NSCalendarMatchPreviousTimePreservingSmallerUnits NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 8),
	NSCalendarMatchNextTimePreservingSmallerUnits     NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 9),
	NSCalendarMatchNextTime                           NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 10),
    
	NSCalendarMatchFirst  NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 12),
	NSCalendarMatchLast   NS_ENUM_AVAILABLE(10_9, 7_0) = (1ULL << 13)
};

enum {
	NSWrapCalendarComponents NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSCalendarWrapComponents instead") = NSCalendarWrapComponents,
};


@interface NSCalendar : NSObject <NSCopying, NSSecureCoding>


+ (NSCalendar *)currentCalendar;					// user's preferred calendar
+ (NSCalendar *)autoupdatingCurrentCalendar NS_AVAILABLE(10_5, 2_0); // tracks changes to user's preferred calendar identifier

/*
	This method returns a new autoreleased calendar object of the given type, specified by a calendar identifier constant.
	The calendar defaults to having the current locale and default time zone, for those properties.
*/
+ (NSCalendar *)calendarWithIdentifier:(NSString *)calendarIdentifierConstant NS_AVAILABLE(10_9, 8_0);


- (id)initWithCalendarIdentifier:(NSString *)ident NS_DESIGNATED_INITIALIZER;

@property (readonly, copy) NSString *calendarIdentifier;
@property (copy) NSLocale *locale;
@property (copy) NSTimeZone *timeZone;
@property NSUInteger firstWeekday;
@property NSUInteger minimumDaysInFirstWeek;

// Methods to return component name strings localized to the calendar's locale

@property (readonly, copy) NSArray *eraSymbols      NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *longEraSymbols  NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSArray *monthSymbols                    NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *shortMonthSymbols               NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *veryShortMonthSymbols           NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *standaloneMonthSymbols          NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *shortStandaloneMonthSymbols     NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *veryShortStandaloneMonthSymbols NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSArray *weekdaySymbols                    NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *shortWeekdaySymbols               NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *veryShortWeekdaySymbols           NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *standaloneWeekdaySymbols          NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *shortStandaloneWeekdaySymbols     NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *veryShortStandaloneWeekdaySymbols NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSArray *quarterSymbols                 NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *shortQuarterSymbols            NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *standaloneQuarterSymbols       NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSArray *shortStandaloneQuarterSymbols  NS_AVAILABLE(10_7, 5_0);

@property (readonly, copy) NSString *AMSymbol  NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSString *PMSymbol  NS_AVAILABLE(10_7, 5_0);


// Calendrical calculations

- (NSRange)minimumRangeOfUnit:(NSCalendarUnit)unit;
- (NSRange)maximumRangeOfUnit:(NSCalendarUnit)unit;

- (NSRange)rangeOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;
- (NSUInteger)ordinalityOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;

- (BOOL)rangeOfUnit:(NSCalendarUnit)unit startDate:(NSDate **)datep interval:(NSTimeInterval *)tip forDate:(NSDate *)date NS_AVAILABLE(10_5, 2_0);

- (NSDate *)dateFromComponents:(NSDateComponents *)comps;
- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDate:(NSDate *)date;

- (NSDate *)dateByAddingComponents:(NSDateComponents *)comps toDate:(NSDate *)date options:(NSCalendarOptions)opts;

- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDate:(NSDate *)startingDate toDate:(NSDate *)resultDate options:(NSCalendarOptions)opts;


/*
	This API is a convenience for getting era, year, month, and day of a given date.
	Pass NULL for a NSInteger pointer parameter if you don't care about that value.
*/
- (void)getEra:(out NSInteger *)eraValuePointer year:(out NSInteger *)yearValuePointer month:(out NSInteger *)monthValuePointer day:(out NSInteger *)dayValuePointer fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API is a convenience for getting era, year for week-of-year calculations, week of year, and weekday of a given date.
	Pass NULL for a NSInteger pointer parameter if you don't care about that value.
*/
- (void)getEra:(out NSInteger *)eraValuePointer yearForWeekOfYear:(out NSInteger *)yearValuePointer weekOfYear:(out NSInteger *)weekValuePointer weekday:(out NSInteger *)weekdayValuePointer fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API is a convenience for getting hour, minute, second, and nanoseconds of a given date.
	Pass NULL for a NSInteger pointer parameter if you don't care about that value.
*/
- (void)getHour:(out NSInteger *)hourValuePointer minute:(out NSInteger *)minuteValuePointer second:(out NSInteger *)secondValuePointer nanosecond:(out NSInteger *)nanosecondValuePointer fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	Get just one component's value.
*/
- (NSInteger)component:(NSCalendarUnit)unit fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	Create a date with given components.
	Current era is assumed.
*/
- (NSDate *)dateWithEra:(NSInteger)eraValue year:(NSInteger)yearValue month:(NSInteger)monthValue day:(NSInteger)dayValue hour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue nanosecond:(NSInteger)nanosecondValue NS_AVAILABLE(10_9, 8_0);


/*
	Create a date with given components.
	Current era is assumed.
*/
- (NSDate *)dateWithEra:(NSInteger)eraValue yearForWeekOfYear:(NSInteger)yearValue weekOfYear:(NSInteger)weekValue weekday:(NSInteger)weekdayValue hour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue nanosecond:(NSInteger)nanosecondValue NS_AVAILABLE(10_9, 8_0);


/*
	This API returns the first moment date of a given date.
	Pass in [NSDate date], for example, if you want the start of "today".
	If there were two midnights, it returns the first.  If there was none, it returns the first moment that did exist.
*/
- (NSDate *)startOfDayForDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API returns all the date components of a date, as if in a given time zone (instead of the receiving calendar's time zone).
	The time zone overrides the time zone of the NSCalendar for the purposes of this calculation.
	Note: if you want "date information in a given time zone" in order to display it, you should use NSDateFormatter to format the date.
*/
- (NSDateComponents *)componentsInTimeZone:(NSTimeZone *)timezone fromDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API compares the given dates down to the given unit, reporting them equal if they are the same in the given unit and all larger units, otherwise either less than or greater than.
*/
- (NSComparisonResult)compareDate:(NSDate *)date1 toDate:(NSDate *)date2 toUnitGranularity:(NSCalendarUnit)unit NS_AVAILABLE(10_9, 8_0);


/*
	This API compares the given dates down to the given unit, reporting them equal if they are the same in the given unit and all larger units.
*/
- (BOOL)isDate:(NSDate *)date1 equalToDate:(NSDate *)date2 toUnitGranularity:(NSCalendarUnit)unit NS_AVAILABLE(10_9, 8_0);


/*
	This API compares the Days of the given dates, reporting them equal if they are in the same Day.
*/
- (BOOL)isDate:(NSDate *)date1 inSameDayAsDate:(NSDate *)date2 NS_AVAILABLE(10_9, 8_0);


/*
	This API reports if the date is within "today".
*/
- (BOOL)isDateInToday:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API reports if the date is within "yesterday".
*/
- (BOOL)isDateInYesterday:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API reports if the date is within "tomorrow".
*/
- (BOOL)isDateInTomorrow:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	This API reports if the date is within a weekend period, as defined by the calendar and calendar's locale.
*/
- (BOOL)isDateInWeekend:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	Find the range of the weekend around the given date, returned via two by-reference parameters.
	Returns NO if the given date is not in a weekend.
	Note that a given entire Day within a calendar is not necessarily all in a weekend or not; weekends can start in the middle of a Day in some calendars and locales.
*/
- (BOOL)rangeOfWeekendStartDate:(out NSDate **)datep interval:(out NSTimeInterval *)tip containingDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/*
	Returns the range of the next weekend, via two by-reference parameters, which starts strictly after the given date.
	The NSCalendarSearchBackwards option can be used to find the previous weekend range strictly before the date.
	Returns NO if there are no such things as weekend in the calendar and its locale.
	Note that a given entire Day within a calendar is not necessarily all in a weekend or not; weekends can start in the middle of a Day in some calendars and locales.
*/
- (BOOL)nextWeekendStartDate:(out NSDate **)datep interval:(out NSTimeInterval *)tip options:(NSCalendarOptions)options afterDate:(NSDate *)date NS_AVAILABLE(10_9, 8_0);


/* 
	This API returns the difference between two dates specified as date components.
	For units which are not specified in each NSDateComponents, but required to specify an absolute date, the base value of the unit is assumed.  For example, for an NSDateComponents with just a Year and a Month specified, a Day of 1, and an Hour, Minute, Second, and Nanosecond of 0 are assumed.
	Calendrical calculations with unspecified Year or Year value prior to the start of a calendar are not advised.
	For each date components object, if its time zone property is set, that time zone is used for it; if the calendar property is set, that is used rather than the receiving calendar, and if both the calendar and time zone are set, the time zone property value overrides the time zone of the calendar property.
	No options are currently defined; pass 0.
*/
- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDateComponents:(NSDateComponents *)startingDateComp toDateComponents:(NSDateComponents *)resultDateComp options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date calculated by adding an amount of a specific component to a given date.
	The NSCalendarWrapComponents option specifies if the component should be incremented and wrap around to zero/one on overflow, and should not cause higher units to be incremented.
*/
- (NSDate *)dateByAddingUnit:(NSCalendarUnit)unit value:(NSInteger)value toDate:(NSDate *)date options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This method computes the dates which match (or most closely match) a given set of components, and calls the block once for each of them, until the enumeration is stopped.
	There will be at least one intervening date which does not match all the components (or the given date itself must not match) between the given date and any result.
	If the NSCalendarSearchBackwards option is used, this method finds the previous match before the given date.  The intent is that the same matches as for a forwards search will be found (that is, if you are enumerating forwards or backwards for each hour with minute "27", the seconds in the date you will get in forwards search would obviously be 00, and the same will be true in a backwards search in order to implement this rule.  Similarly for DST backwards jumps which repeats times, you'll get the first match by default, where "first" is defined from the point of view of searching forwards.  So, when searching backwards looking for a particular hour, with no minute and second specified, you don't get a minute and second of 59:59 for the matching hour (which would be the nominal first match within a given hour, given the other rules here, when searching backwards).
	If the NSCalendarMatchStrictly option is used, the algorithm travels as far forward or backward as necessary looking for a match, but there are ultimately implementation-defined limits in how far distant the search will go.  If the NSCalendarMatchStrictly option is not specified, the algorithm searches up to the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument.  If you want to find the next Feb 29 in the Gregorian calendar, for example, you have to specify the NSCalendarMatchStrictly option to guarantee finding it.
	If an exact match is not possible, and requested with the NSCalendarMatchStrictly option, nil is passed to the block and the enumeration ends.  (Logically, since an exact match searches indefinitely into the future, if no match is found there's no point in continuing the enumeration.)

	If the NSCalendarMatchStrictly option is NOT used, exactly one option from the set {NSCalendarMatchPreviousTimePreservingSmallerUnits, NSCalendarMatchNextTimePreservingSmallerUnits, NSCalendarMatchNextTime} must be specified, or an illegal argument exception will be thrown.
	
        If the NSCalendarMatchPreviousTimePreservingSmallerUnits option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the previous existing value of the missing unit and preserves the lower units' values (e.g., no 2:37am results in 1:37am, if that exists).
	
        If the NSCalendarMatchNextTimePreservingSmallerUnits option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the next existing value of the missing unit and preserves the lower units' values (e.g., no 2:37am results in 3:37am, if that exists).
 
	If the NSCalendarMatchNextTime option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the next existing time which exists (e.g., no 2:37am results in 3:00am, if that exists).
	If the NSCalendarMatchFirst option is specified, and there are two or more matching times (all the components are the same, including isLeapMonth) before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the first occurrence.
	If the NSCalendarMatchLast option is specified, and there are two or more matching times (all the components are the same, including isLeapMonth) before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the last occurrence.
	If neither the NSCalendarMatchFirst or NSCalendarMatchLast option is specified, the default behavior is to act as if NSCalendarMatchFirst was specified.
	There is no option to return middle occurrences of more than two occurrences of a matching time, if such exist.

	Result dates have an integer number of seconds (as if 0 was specified for the nanoseconds property of the NSDateComponents matching parameter), unless a value was set in the nanoseconds property, in which case the result date will have that number of nanoseconds (or as close as possible with floating point numbers).
	The enumeration is stopped by setting *stop = YES in the block and return.  It is not necessary to set *stop to NO to keep the enumeration going.
*/
- (void)enumerateDatesStartingAfterDate:(NSDate *)start matchingComponents:(NSDateComponents *)comps options:(NSCalendarOptions)opts usingBlock:(void (^)(NSDate *date, BOOL exactMatch, BOOL *stop))block NS_AVAILABLE(10_9, 8_0);

/*
	This method computes the next date which matches (or most closely matches) a given set of components.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (NSDate *)nextDateAfterDate:(NSDate *)date matchingComponents:(NSDateComponents *)comps options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date found which matches a specific component value.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (NSDate *)nextDateAfterDate:(NSDate *)date matchingUnit:(NSCalendarUnit)unit value:(NSInteger)value options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date found which matches the given hour, minute, and second values.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (NSDate *)nextDateAfterDate:(NSDate *)date matchingHour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue options:(NSCalendarOptions)options NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date calculated by setting a specific component to a given time, and trying to keep lower components the same.  If the unit already has that value, this may result in a date which is the same as the given date.
	Changing a component's value often will require higher or coupled components to change as well.  For example, setting the Weekday to Thursday usually will require the Day component to change its value, and possibly the Month and Year as well.
	If no such time exists, the next available time is returned (which could, for example, be in a different day, week, month, ... than the nominal target date).  Setting a component to something which would be inconsistent forces other units to change; for example, setting the Weekday to Thursday probably shifts the Day and possibly Month and Year.
	The specific behaviors here are as yet unspecified; for example, if I change the weekday to Thursday, does that move forward to the next, backward to the previous, or to the nearest Thursday?  A likely rule is that the algorithm will try to produce a result which is in the next-larger unit to the one given (there's a table of this mapping at the top of this document).  So for the "set to Thursday" example, find the Thursday in the Week in which the given date resides (which could be a forwards or backwards move, and not necessarily the nearest Thursday).  For forwards or backwards behavior, one can use the -nextDateAfterDate:matchingUnit:value:options: method above.
 */
- (NSDate *)dateBySettingUnit:(NSCalendarUnit)unit value:(NSInteger)v ofDate:(NSDate *)date options:(NSCalendarOptions)opts NS_AVAILABLE(10_9, 8_0);


/*
	This API returns a new NSDate object representing the date calculated by setting hour, minute, and second to a given time.
	If no such time exists, the next available time is returned (which could, for example, be in a different day than the nominal target date).
	The intent is to return a date on the same day as the original date argument.  This may result in a date which is earlier than the given date, of course.
 */
- (NSDate *)dateBySettingHour:(NSInteger)h minute:(NSInteger)m second:(NSInteger)s ofDate:(NSDate *)date options:(NSCalendarOptions)opts NS_AVAILABLE(10_9, 8_0);


/*
    This API returns YES if the date has all the matched components. Otherwise, it returns NO.
    It is useful to test the return value of the -nextDateAfterDate:matchingUnit:value:options:, to find out if the components were obeyed or if the method had to fudge the result value due to missing time.
 */
- (BOOL)date:(NSDate *)date matchesComponents:(NSDateComponents *)components NS_AVAILABLE(10_9, 8_0);

@end


// This notification is posted through [NSNotificationCenter defaultCenter]
// when the system day changes. Register with "nil" as the object of this
// notification. If the computer/device is asleep when the day changed,
// this will be posted on wakeup. You'll get just one of these if the
// machine has been asleep for several days. The definition of "Day" is
// relative to the current calendar ([NSCalendar currentCalendar]) of the
// process and its locale and time zone. There are no guarantees that this
// notification is received by observers in a "timely" manner, same as
// with distributed notifications.

FOUNDATION_EXPORT NSString * const NSCalendarDayChangedNotification NS_AVAILABLE(10_9, 8_0);



// This is a just used as an extensible struct, basically;
// note that there are two uses: one for specifying a date
// via components (some components may be missing, making the
// specific date ambiguous), and the other for specifying a
// set of component quantities (like, 3 months and 5 hours).
// Undefined fields have (or fields can be set to) the value
// NSDateComponentUndefined.

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
	NSDateComponentUndefined = NSIntegerMax,

	NSUndefinedDateComponent NS_CALENDAR_ENUM_DEPRECATED(10_4, 10_10, 2_0, 8_0, "Use NSDateComponentUndefined instead") = NSDateComponentUndefined
};


@interface NSDateComponents : NSObject <NSCopying, NSSecureCoding>

@property (copy) NSCalendar *calendar NS_AVAILABLE(10_7, 4_0);
@property (copy) NSTimeZone *timeZone NS_AVAILABLE(10_7, 4_0);
@property NSInteger era;
@property NSInteger year;
@property NSInteger month;
@property NSInteger day;
@property NSInteger hour;
@property NSInteger minute;
@property NSInteger second;
@property NSInteger nanosecond NS_AVAILABLE(10_7, 5_0);
@property NSInteger weekday;
@property NSInteger weekdayOrdinal;
@property NSInteger quarter NS_AVAILABLE(10_6, 4_0);
@property NSInteger weekOfMonth NS_AVAILABLE(10_7, 5_0);
@property NSInteger weekOfYear NS_AVAILABLE(10_7, 5_0);
@property NSInteger yearForWeekOfYear NS_AVAILABLE(10_7, 5_0);
@property (getter=isLeapMonth) BOOL leapMonth NS_AVAILABLE(10_8, 6_0);
@property (readonly, copy) NSDate *date NS_AVAILABLE(10_7, 4_0);

- (NSInteger)week NS_CALENDAR_DEPRECATED(10_4, 10_9, 2_0, 7_0, "Use weekOfMonth or weekOfYear, depending on which you mean");
- (void)setWeek:(NSInteger)v NS_CALENDAR_DEPRECATED(10_4, 10_9, 2_0, 7_0, "Use setWeekOfMonth: or setWeekOfYear:, depending on which you mean");

/*
	This API allows one to set a specific component of NSDateComponents, by enum constant value rather than property name.
	The calendar and timeZone and isLeapMonth properties cannot be set by this method.
*/
- (void)setValue:(NSInteger)value forComponent:(NSCalendarUnit)unit NS_AVAILABLE(10_9, 8_0);


/*
	This API allows one to get the value of a specific component of NSDateComponents, by enum constant value rather than property name.
	The calendar and timeZone and isLeapMonth property values cannot be gotten by this method.
*/
- (NSInteger)valueForComponent:(NSCalendarUnit)unit NS_AVAILABLE(10_9, 8_0);


/*
	Reports whether or not the combination of properties which have been set in the receiver is a date which exists in the calendar.
	This method is not appropriate for use on NSDateComponents objects which are specifying relative quantities of calendar components.
	Except for some trivial cases (e.g., 'seconds' should be 0 - 59 in any calendar), this method is not necessarily cheap.
	If the time zone property is set in the NSDateComponents object, it is used.
	The calendar property must be set, or NO is returned.
*/
@property (getter=isValidDate, readonly) BOOL validDate NS_AVAILABLE(10_9, 8_0);


/*
	Reports whether or not the combination of properties which have been set in the receiver is a date which exists in the calendar.
	This method is not appropriate for use on NSDateComponents objects which are specifying relative quantities of calendar components.
	Except for some trivial cases (e.g., 'seconds' should be 0 - 59 in any calendar), this method is not necessarily cheap.
	If the time zone property is set in the NSDateComponents object, it is used.
*/
- (BOOL)isValidDateInCalendar:(NSCalendar *)calendar NS_AVAILABLE(10_9, 8_0);


@end


