//
//  CalRecurrenceRule.h
//	CalendarStore Framework
//
//  Copyright 2006 Apple Inc. All rights reserved.
//	
//	This class describes the recurrence pattern for a repeating event. The recurrence rules that can be expressed are 
//  restricted to the recurrence patterns that can be set in iCal's UI. It is not possible to directly modify a 
//  CalRecurrenceRule or any of its properties. This functionality is achieved by creating a new CalRecurrenceRule, and 
//  setting an event to use the new rule. When a new recurrence rule is set on an CalEvent, that change is not saved 
//  until the client has passed the modified event to CalCalendarStore's saveEvent: method.
//
//  The CalendarStore framework is deprecated.  Please use the EventKit framework instead.

/*  Custom classes used by CalRecurrenceRule */

//  CalRecurrenceEnd
//  CalRecurrenceEnd is an attribute of CalRecurrenceRule that defines how long the recurrence is scheduled to repeat. 
//  The recurrence can be defined either with an NSUInteger that indicates the total number times it repeats, or with an
//  NSDate, after which it no longer repeats. An event which is set to never end should have its CalRecurrenceEnd set to
//  nil. 
//  
//  If the end of the pattern is defines with an NSDate, the client must pass a valid NSDate, nil cannot be passed. If 
//  the end of the pattern is defined as terms of a number of occurrences, the occurrenceCount passed to the initializer
//  must be positive, it cannot be 0. If the client attempts to initialize a CalRecurrenceEnd with a nil NSDate or 
//  OccurrenceCount of 0, an exception is raised.
//  
//  A CalRecurrenceEnd initialized with an end date will return 0 for occurrenceCount. One initialized with a number of
//  occurrences will return nil for its endDate.

#import <Foundation/Foundation.h>

@interface CalRecurrenceEnd : NSObject <NSCopying> {
    @private
    NSDate *_endDate;
    NSUInteger _occurrenceCount;
}

+ (id)recurrenceEndWithEndDate:(NSDate *)endDate NS_DEPRECATED_MAC(10_5, 10_8);
+ (id)recurrenceEndWithOccurrenceCount:(NSUInteger)occurrenceCount NS_DEPRECATED_MAC(10_5, 10_8);

@property(readonly) BOOL usesEndDate NS_DEPRECATED_MAC(10_5, 10_8);
@property(readonly) NSDate *endDate NS_DEPRECATED_MAC(10_5, 10_8);
@property(readonly) NSUInteger occurrenceCount NS_DEPRECATED_MAC(10_5, 10_8);
@end

//  CalNthWeekDay
//  CalNthWeekDay specifies the nth instance of a particular day of the week, such as the third Tuesday of every month.
//  
//  Valid values for dayOfTheWeek are integers 1-7, which correspond to days of the week with Sunday = 1.
//  Valid values for weekNumber portion are 1, 2, 3, 4, or -1, where a value of -1 indicates the last week.

@interface CalNthWeekDay : NSObject <NSCopying> {
    @private
    NSUInteger _dayOfTheWeek;
    NSInteger _weekNumber;
}

@property(readonly) NSUInteger dayOfTheWeek NS_DEPRECATED_MAC(10_5, 10_8);
@property(readonly) NSInteger weekNumber NS_DEPRECATED_MAC(10_5, 10_8);

@end

//  CalRecurrenceType
//  CalRecurrenceType designates the unit of time used to describe the recurrence. It has four possible values, which 
//  correspond to recurrence rules that are defined in terms of days, weeks, months, and years.
//  
//  The interval of a CalRecurrenceRule is an NSUInteger which specifies how often the recurrence rule repeats over the
//  unit of time described by the CalRecurrenceType. For example, if the CalRecurrenceType is CalWeeklyRecurrence, then 
//  an interval of 1 means the pattern is repeated every week. A NSUInteger of 2 indicates it is repeated every other 
//  week, 3 means every third week, and so on. The NSUInteger must be a positive integer; 0 is not a valid value, and 
//  nil will be returned if the client attempts to initialize a rule with a negative or zero interval.
//
//  Together, CalRecurrenceType and interval define how often the CalRecurrenceRule's pattern repeats.

typedef enum {
    CalRecurrenceDaily,
    CalRecurrenceWeekly,
    CalRecurrenceMonthly,
    CalRecurrenceYearly
} CalRecurrenceType;

//  CalDefaultRecurrenceInterval
//  The CalDefaultRecurrenceInterval is 1, indicating the event repeats every day, week, month, or year, depending on 
//  its CalRecurrenceType.
extern NSUInteger const CalDefaultRecurrenceInterval NS_DEPRECATED_MAC(10_5, 10_8);

@interface CalRecurrenceRule : NSObject <NSCopying>
{
    @private
    id _objectID;
    void *_reserved;
    NSArray *_monthsOfTheYear;
    NSArray *_nthWeekDaysOfTheMonth;
    NSArray *_daysOfTheMonth;
    NSArray *_daysOfTheWeek;
    NSUInteger _firstDayOfTheWeek;
    NSUInteger _recurrenceInterval;
    CalRecurrenceType _recurrenceType;
    CalRecurrenceEnd *_recurrenceEnd;
}

//  Recurrence initializers
//  Two parameters are included in every CalRecurrenceRule initializer. The first is the interval, which is described 
//  above and indicates how many CalRecurrenceTypes make up the period of the recurrence (every week, every other week, 
//  etc.). The second is a CalRecurrenceEnd, which describes when the CalRecurrenceRule ends. If valid values for these 
//  two parameters are not included, nil is returned. There are simple initializers for each CalRecurrenceType which 
//  take only these two parameters. 
//  
//  In addition, there are also initializers for more sophisticated recurrence patterns. The recurrence patterns allowed
//  are restricted to that can be represented in iCal's UI, including all repeating patterns that can be represented 
//  with a "Custom" repeating pattern. A description is included with each of the advanced initlizaers provided below.
//  
//  Valid values for days of the week are integers 1-7, which correspond to days of the week with Sunday = 1.
//  Valid values for days of the month are integers 1-31.
//  Valid values for weeks of the month are integers 1-4 and -1, which is used to indicate the last week of the month.
//  Valid values for months of the year are integers 1-12, which correspond to months of the year with January = 1.

/*  Daily Recurrence initializer  */

- (id)initDailyRecurrenceWithInterval:(NSUInteger)interval end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);

/*  Weekly Recurrence initializers  */

- (id)initWeeklyRecurrenceWithInterval:(NSUInteger)interval end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);

//  This initializer allows the client to specify multiple days of the week that an event will recur. This initializer 
//  should be used to initialize events that occur more than once a week, in a set weekly pattern.
- (id)initWeeklyRecurrenceWithInterval:(NSUInteger)interval 
                      forDaysOfTheWeek:(NSArray *)days
                                   end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);


/*  Monthly Recurrence initializers  */

- (id)initMonthlyRecurrenceWithInterval:(NSUInteger)interval end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);

//  This initializer allows the client to specify multiple days of the month that an event will recur. This method 
//  should be used to initialize events that occur more than once a month, in a set monthly pattern.
- (id)initMonthlyRecurrenceWithInterval:(NSUInteger)interval 
                      forDaysOfTheMonth:(NSArray *)monthDays 
                                    end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);
                                                    
//  This initializer allows the client to specify a repeating monthly pattern in terms of a day of the week and a week 
//  of the month that the even repeats. An example is an event that recurs the first Monday of every month.
- (id)initMonthlyRecurrenceWithInterval:(NSUInteger)interval 
						forDayOfTheWeek:(NSUInteger)weekDay
					  forWeekOfTheMonth:(NSInteger)monthWeek
                                    end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);

/*  Monthly Recurrence initializers  */

- (id)initYearlyRecurrenceWithInterval:(NSUInteger)interval end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);

//  This initializer allows the client to specify multiple months of the year that an event will recur. This method 
//  should be used to initialize events that occur on the same date, in more than month a year, in a set monthly 
//  pattern. An example is an event that occurs every year on the first day of the first and seventh months.
- (id)initYearlyRecurrenceWithInterval:(NSUInteger)interval 
                    forMonthsOfTheYear:(NSArray *)months 
                                   end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);
                                                    
//  This initializer allows the client to specify multiple months of the year that an event will recur. This method 
//  should be used to initialize events that recur on the same day of the week, in the same week of a month, of possibly
//  more than one month a year, in a set yearly pattern. An example is an event that occurs every year on the last 
//  Friday of sixth and twelfth months.
- (id)initYearlyRecurrenceWithInterval:(NSUInteger)interval 
					   forDayOfTheWeek:(NSUInteger)weekDay
					 forWeekOfTheMonth:(NSInteger)monthWeek
                    forMonthsOfTheYear:(NSArray *)months 
                                   end:(CalRecurrenceEnd *)end NS_DEPRECATED_MAC(10_5, 10_8);


/*  Properties that exist in all CalRecurrenceRules  */

//  @property(readonly) CalRecurrenceEnd *recurrenceEnd;
//  This property defines when the the repeating event is scheduled to end. The end date can be specified by a number of
//  occurrences, or with an end date.
@property(readonly) CalRecurrenceEnd *recurrenceEnd NS_DEPRECATED_MAC(10_5, 10_8);

//  @property(readonly) CalRecurrenceType recurrenceType;
//  This property designates the unit of time used to describe the recurrence pattern.
@property(readonly) CalRecurrenceType recurrenceType NS_DEPRECATED_MAC(10_5, 10_8);

//  @property(readonly) NSUInteger recurrenceInterval;
//  Specifies how often the rule repeats over the given recurrence type. An interval of 1 indicates that the event 
//  repeats every time unit, while an interval of 2 indicates that the repetition occurs in every other unit, etc.
@property(readonly) NSUInteger recurrenceInterval NS_DEPRECATED_MAC(10_5, 10_8);

//  @property(readonly) NSUInteger firstDayOfTheWeek;
//  Recurrence patterns can specify which day of the week should be treated as the first day. Possible values for this
//  property are integers 0 and 1-7, which correspond to days of the week with Sunday = 1. Zero indicates that the 
//  property is not set for this recurrence. he first day of the week only affects the way the recurrence is expanded
//  for weekly recurrence patterns with an interval greater than 1. For those types of recurrence patterns, the 
//  CalendarStore framework will set firstDayOfTheWeek to be 2 (Monday). In all other cases, this property will be set 
//  to zero. The iCalendar spec stipulates that the default value is Monday if this property is not set.
@property(readonly) NSUInteger firstDayOfTheWeek NS_DEPRECATED_MAC(10_5, 10_8);

 
/*  Properties that are only valid for certain CalRecurrenceRules  */

//  The properties that follow are only valid for certain recurrence rules, and are always arrays. For recurrence rules
//  that can be expressed with one of the simple initializers, the arrays will contain a single object, corresponding 
//  to the day of the week, the day of the month, the "NthWeekDay" (for example, the fourth Thursday), or the month of 
//  the year the event recurs. The objects will be NSNumbers, except in the "NthWeekDay" case just mentioned, when
//  the array will contain a CalNthWeekDay instead of an NSNumber.
//  
//  Repeating events using one of the advanced initializers may recur multiple times in the specified time period, for 
//  example, the first and sixteenth days of a month. When this is true, the arrays may contain more than one entry.
//  
//  These properties will only be valid for certain CalRecurrenceRules, depending on how the rule's recurrence is 
//  defined. The constraints on when these properties is valid are described below. When these constraints are not met,
//  the property's value will be nil.

//  @property(readonly) NSArray *daysOfTheWeek;
//  This property is valid for rules whose CalRecurrenceType is CalWeeklyRecurrence. This property can be accessed as
//  an array containing one or more NSNumbers corresponding to the days of the week the event recurs. For all other 
//  CalRecurrenceRules, this property is nil.
@property(readonly) NSArray *daysOfTheWeek NS_DEPRECATED_MAC(10_5, 10_8);

//  @property(readonly) NSArray *daysOfTheMonth;
//  This property is valid for rules whose CalRecurrenceType is CalMonthlyRecurrence, and that were initialized with one
//  or more specific days of the month (not with a day of the week and week of the month). This property can be
//  accessed as an array containing one or more NSNumbers corresponding to the days of the month the event recurs.
//  For all other CalRecurrenceRules, this property is nil.
@property(readonly) NSArray *daysOfTheMonth NS_DEPRECATED_MAC(10_5, 10_8);

//  @property(readonly) NSArray *nthWeekDaysOfTheMonth;
//  This property is valid for rules whose CalRecurrenceType is CalMonthlyRecurrence or CalYearlyRecurrence, and that 
//  were initialized with a day of the week and week of the month. This property can be accessed as an array 
//  containing exactly one CalNthWeekDay corresponding to the week of the month the event recurs. For all other 
//  CalRecurrenceRules, this property is nil.
@property(readonly) NSArray *nthWeekDaysOfTheMonth NS_DEPRECATED_MAC(10_5, 10_8);

//  @property(readonly) NSArray *monthsOfTheYear;
//  This property is valid for rules whose CalRecurrenceType is CalYearlyRecurrence. This property can be accessed as an
//  array containing one or more NSNumbers corresponding to the months of the year the event recurs. For all other 
//  CalRecurrenceRules, this property is nil.
@property(readonly) NSArray *monthsOfTheYear NS_DEPRECATED_MAC(10_5, 10_8);

@end
