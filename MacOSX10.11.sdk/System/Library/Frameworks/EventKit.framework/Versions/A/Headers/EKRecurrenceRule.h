//
//  EKRecurrenceRule.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKRecurrenceEnd.h>
#import <EventKit/EKRecurrenceDayOfWeek.h>
#import <EventKit/EKTypes.h>
#import <EventKit/EKObject.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKCalendarItem;

/*!
    @class      EKRecurrenceRule
    @abstract   Represents how an event repeats.
    @discussion This class describes the recurrence pattern for a repeating event. The recurrence rules that 
                can be expressed are not restricted to the recurrence patterns that can be set in Calendar's UI. 
 
                It is currently not possible to directly modify a EKRecurrenceRule or any of its properties. 
                This functionality is achieved by creating a new EKRecurrenceRule, and setting an event to use the new rule. 
                When a new recurrence rule is set on an EKEvent, that change is not saved until the client 
                has passed the modified event to EKEventStore's saveEvent: method.
 */
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKRecurrenceRule : EKObject <NSCopying>

/*!
    @method     initRecurrenceWithFrequency:interval:end:
    @abstract   Simple initializer to create a recurrence.
    @discussion This is used to create a simple recurrence with a specific type, interval and end. If interval is
                0, an exception is raised. The end parameter can be nil.
*/
- (instancetype)initRecurrenceWithFrequency:(EKRecurrenceFrequency)type interval:(NSInteger)interval end:(nullable EKRecurrenceEnd *)end;

/*!
    @method     initRecurrenceWithFrequency:interval:daysOfTheWeek:daysOfTheMonth:monthsOfTheYear:weeksOfTheYear:daysOfTheYear:setPositions:end:
    @abstract   The designated initializer.
    @discussion This can be used to build any kind of recurrence rule. But be aware that certain combinations make
                no sense and will be ignored. For example, if you pass daysOfTheWeek for a daily recurrence, they
                will be ignored.
    @param      type            The type of recurrence
    @param      interval        The interval. Passing zero will raise an exception.
    @param      daysOfTheWeek   An array of EKRecurrenceDayOfWeek objects. Valid for all recurrence types except daily. Ignored otherwise.
                                Corresponds to the BYDAY value in the iCalendar specification.
    @param      daysOfTheMonth  An array of NSNumbers ([+/-] 1 to 31). Negative numbers infer counting from the end of the month.
                                For example, -1 means the last day of the month. Valid only for monthly recurrences. Ignored otherwise.
                                Corresponds to the BYMONTHDAY value in the iCalendar specification.
    @param      monthsOfTheYear An array of NSNumbers (1 to 12). Valid only for yearly recurrences. Ignored otherwise. Corresponds to
                                the BYMONTH value in the iCalendar specification.
    @param      weeksOfTheYear  An array of NSNumbers ([+/1] 1 to 53). Negative numbers infer counting from the end of the year.
                                For example, -1 means the last week of the year. Valid only for yearly recurrences. Ignored otherwise.
                                Corresponds to the BYWEEKNO value in the iCalendar specification.
    @param      daysOfTheYear   An array of NSNumbers ([+/1] 1 to 366). Negative numbers infer counting from the end of the year.
                                For example, -1 means the last day of the year. Valid only for yearly recurrences. Ignored otherwise.
                                Corresponds to the BYYEARDAY value in the iCalendar specification.
    @param      setPositions    An array of NSNumbers ([+/1] 1 to 366). Used at the end of recurrence computation to filter the list
                                to the positions specified. Negative numbers indicate starting at the end, i.e. -1 indicates taking the
                                last result of the set. Valid when daysOfTheWeek, daysOfTheMonth, monthsOfTheYear, weeksOfTheYear, or 
                                daysOfTheYear is passed. Ignored otherwise. Corresponds to the BYSETPOS value in the iCalendar specification.
    @param      end             The recurrence end, or nil.
*/
- (instancetype)initRecurrenceWithFrequency:(EKRecurrenceFrequency)type
                         interval:(NSInteger)interval 
                    daysOfTheWeek:(nullable NSArray<EKRecurrenceDayOfWeek *> *)days
                   daysOfTheMonth:(nullable NSArray<NSNumber *> *)monthDays
                  monthsOfTheYear:(nullable NSArray<NSNumber *> *)months
                   weeksOfTheYear:(nullable NSArray<NSNumber *> *)weeksOfTheYear
                    daysOfTheYear:(nullable NSArray<NSNumber *> *)daysOfTheYear
                     setPositions:(nullable NSArray<NSNumber *> *)setPositions
                              end:(nullable EKRecurrenceEnd *)end;

/*  Properties that exist in all EKRecurrenceRules  */

/*!
    @property       calendarIdentifier;
    @description    Calendar used by this recurrence rule.
*/
@property(nonatomic, readonly) NSString *calendarIdentifier;

/*!
    @property       recurrenceEnd
    @discussion     This property defines when the the repeating event is scheduled to end. The end date can be specified by a number of
                    occurrences, or with an end date.
*/
@property(nonatomic, copy, nullable) EKRecurrenceEnd *recurrenceEnd;

/*!
    @property       frequency
    @discussion     This property designates the unit of time used to describe the recurrence pattern.
*/
@property(nonatomic, readonly) EKRecurrenceFrequency frequency;

/*!
    @property       interval
    @discussion     The interval of a EKRecurrenceRule is an integer value which specifies how often the recurrence rule repeats
                    over the unit of time described by the EKRecurrenceFrequency. For example, if the EKRecurrenceFrequency is
                    EKRecurrenceWeekly, then an interval of 1 means the pattern is repeated every week. A value of 2
                    indicates it is repeated every other week, 3 means every third week, and so on. The value must be a
                    positive integer; 0 is not a valid value, and nil will be returned if the client attempts to initialize a
                    rule with a negative or zero interval. 
*/
@property(nonatomic, readonly) NSInteger interval;

/*!
    @property       firstDayOfTheWeek
    @discussion     Recurrence patterns can specify which day of the week should be treated as the first day. Possible values for this
                    property are integers 0 and 1-7, which correspond to days of the week with Sunday = 1. Zero indicates that the 
                    property is not set for this recurrence. The first day of the week only affects the way the recurrence is expanded
                    for weekly recurrence patterns with an interval greater than 1. For those types of recurrence patterns, the 
                    Calendar framework will set firstDayOfTheWeek to be 2 (Monday). In all other cases, this property will be set 
                    to zero. The iCalendar spec stipulates that the default value is Monday if this property is not set.
*/
@property(nonatomic, readonly) NSInteger firstDayOfTheWeek;


/*  Properties that are only valid for certain EKRecurrenceRules  */

//  The properties that follow are only valid for certain recurrence rules, and are always arrays. For recurrence rules
//  that can be expressed with one of the simple initializers, the arrays will contain a single object, corresponding 
//  to the day of the week, the day of the month, the "NthWeekDay" (for example, the fourth Thursday), or the month of 
//  the year the event recurs. The objects will be NSNumbers, except in the "NthWeekDay" case just mentioned, when
//  the array will contain a CalNthWeekDay instead of an NSNumber.
//  
//  Repeating events using one of the advanced initializers may recur multiple times in the specified time period, for 
//  example, the first and sixteenth days of a month. When this is true, the arrays may contain more than one entry.
//  
//  These properties will only be valid for certain EKRecurrenceRules, depending on how the rule's recurrence is 
//  defined. The constraints on when these properties is valid are described below. When these constraints are not met,
//  the property's value will be nil.

/*!
    @property       daysOfTheWeek
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyWeekly, EKRecurrenceFrequencyMonthly, or 
                    EKRecurrenceFrequencyYearly. This property can be accessed as an array containing one or more EKRecurrenceDayOfWeek objects
                    corresponding to the days of the week the event recurs. For all other EKRecurrenceRules, this property is nil.
                    This property corresponds to BYDAY in the iCalendar specification.
*/
@property(nonatomic, readonly, nullable) NSArray<EKRecurrenceDayOfWeek *> *daysOfTheWeek;

/*!
    @property       daysOfTheMonth
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyMonthly, and that were initialized 
                    with one or more specific days of the month (not with a day of the week and week of the month). This property can be
                    accessed as an array containing one or more NSNumbers corresponding to the days of the month the event recurs.
                    For all other EKRecurrenceRules, this property is nil. This property corresponds to BYMONTHDAY in the iCalendar 
                    specification.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *daysOfTheMonth;

/*!
    @property       daysOfTheYear
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyYearly. This property can be accessed 
                    as an array containing one or more NSNumbers corresponding to the days of the year the event recurs. For all other 
                    EKRecurrenceRules, this property is nil. This property corresponds to BYYEARDAY in the iCalendar specification. It should
                    contain values between 1 to 366 or -366 to -1.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *daysOfTheYear;

/*!
    @property       weeksOfTheYear
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyYearly. This property can be accessed 
                    as an array containing one or more NSNumbers corresponding to the weeks of the year the event recurs. For all other 
                    EKRecurrenceRules, this property is nil. This property corresponds to BYWEEK in the iCalendar specification. It should
                    contain integers from 1 to 53 or -1 to -53.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *weeksOfTheYear;

/*!
    @property       monthsOfTheYear
    @discussion     This property is valid for rules whose EKRecurrenceFrequency is EKRecurrenceFrequencyYearly. This property can be accessed 
                    as an array containing one or more NSNumbers corresponding to the months of the year the event recurs. For all other 
                    EKRecurrenceRules, this property is nil. This property corresponds to BYMONTH in the iCalendar specification.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *monthsOfTheYear;

/*!
    @property       setPositions
    @discussion     This property is valid for rules which have a valid daysOfTheWeek, daysOfTheMonth, weeksOfTheYear, or monthsOfTheYear property. 
                    It allows you to specify a set of ordinal numbers to help choose which objects out of the set of selected events should be
                    included. For example, setting the daysOfTheWeek to Monday-Friday and including a value of -1 in the array would indicate
                    the last weekday in the recurrence range (month, year, etc). This value corresponds to the iCalendar BYSETPOS property.
*/
@property(nonatomic, readonly, nullable) NSArray<NSNumber *> *setPositions;

@end

NS_ASSUME_NONNULL_END
