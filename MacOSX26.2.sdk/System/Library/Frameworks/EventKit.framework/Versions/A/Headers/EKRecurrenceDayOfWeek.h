//
//  EKRecurrenceDayOfWeek.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @class      EKRecurrenceDayOfWeek
    @abstract   Class which represents a day of the week this recurrence will occur.
    @discussion EKRecurrenceDayOfWeek specifies either a simple day of the week, or the nth instance
                of a particular day of the week, such as the third Tuesday of every month. The week
                number is only valid when used with monthly or yearly recurrences, since it would
                be otherwise meaningless.

                Valid values for dayOfTheWeek are integers 1-7, which correspond to days of the week
                with Sunday = 1. Valid values for weekNumber portion are (+/-)1-53, where a negative
                value indicates a value from the end of the range. For example, in a yearly event -1
                means last week of the year. -1 in a Monthly recurrence indicates the last week of
                the month. 

                The value 0 also indicates the weekNumber is irrelevant (every Sunday, etc.).

                Day-of-week weekNumber values that are out of bounds for the recurrence type will
                result in an exception when trying to initialize the recurrence. In particular,
                weekNumber must be zero when passing EKRecurrenceDayOfWeek objects to initialize a weekly 
                recurrence.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKRecurrenceDayOfWeek : NSObject <NSCopying, NSSecureCoding> {
}

/*!
     @method     dayOfWeek:
     @abstract   Creates an autoreleased object with a day of the week and week number of zero.
*/
+ (instancetype)dayOfWeek:(EKWeekday)dayOfTheWeek;

/*!
     @method     dayOfWeek:weekNumber:
     @abstract   Creates an autoreleased object with a specific day of week and week number.
*/
+ (instancetype)dayOfWeek:(EKWeekday)dayOfTheWeek weekNumber:(NSInteger)weekNumber;

/*!
     @method     initWithDayOfTheWeek:weekNumber:
     @abstract   Creates an day-of-week object with a specific day of week and week number.
*/
- (id)initWithDayOfTheWeek:(EKWeekday)dayOfTheWeek weekNumber:(NSInteger)weekNumber;

/*!
     @property   dayOfTheWeek
     @abstract   The day of the week.
*/
@property(nonatomic, readonly) EKWeekday dayOfTheWeek;

/*!
     @property   weekNumber
     @abstract   The week number.
*/
@property(nonatomic, readonly) NSInteger weekNumber;

@end

NS_ASSUME_NONNULL_END
