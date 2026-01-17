//
//  EKReminder.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKCalendarItem.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKCalendar, EKRecurrenceRule, EKAlarm;

/*!
    @class      EKReminder
    @abstract   The EKReminder class represents a reminder (task/todo).
*/
NS_CLASS_AVAILABLE(10_8, 6_0)
@interface EKReminder : EKCalendarItem

/*!
    @method     reminderWithEventStore:
    @abstract   Creates a new reminder in the given event store.
*/
+ (EKReminder *)reminderWithEventStore:(EKEventStore *)eventStore;

/*!
    @property   startDateComponents
    @abstract   The start date of the task, as date components.
    @discussion The use of date components allows the start date and its time zone to be represented in a single property. 
                A nil time zone represents a floating date.  Setting a date component without a hour, minute and second component will set allDay to YES.
                If you set this property, the calendar must be set to NSCalendarIdentifierGregorian. An exception is raised otherwise.
*/
@property(nonatomic, copy, nullable) NSDateComponents *startDateComponents;

/*!
    @property   dueDateComponents
    @abstract   The date by which this reminder should be completed.
    @discussion The use of date components allows the due date and its time zone to be represented in a single property. 
                A nil time zone represents a floating date.  Setting a date component without a hour, minute and second component will set allDay to YES.
                If you set this property, the calendar must be set to NSCalendarIdentifierGregorian. An exception is raised otherwise.
 
                On iOS, if you set the due date for a reminder, you must also set a start date, otherwise you will receive
                an error (EKErrorNoStartDate) when attempting to save this reminder. This is not a requirement on OS X.
*/
@property(nonatomic, copy, nullable) NSDateComponents *dueDateComponents;

//  These two properties are inextricably linked.  Setting completed to be YES, will set the completedDate to be now,
//  and setting any completedDate will change completed to be YES. Similarly, setting completed to be NO will set
//  the completedDate to be nil, and setting the completedDate changes completed to NO.
//  Note, you may encounter the case where isCompleted is YES, but completionDate is nil, if the reminder was completed using a different client.

/*!
    @property   completed
    @abstract   Whether or not the reminder is completed. 
    @discussion Setting it to YES will set the completed date to the current date. 
                Setting it to NO will set the completed date to nil.
*/
@property(nonatomic, getter=isCompleted) BOOL completed;

/*!
    @property   completionDate
    @abstract   The date on which this reminder was completed.
*/
@property(nonatomic, copy, nullable) NSDate *completionDate;

/*!
    @property   priority
    @abstract   The priority of the reminder.
    @discussion Priorities run from 1 (highest) to 9 (lowest).  A priority of 0 means no priority.
                Saving a reminder with any other priority will fail.
                Per RFC 5545, priorities of 1-4 are considered "high," a priority of 5 is "medium," and priorities of 6-9 are "low."
 */
@property(nonatomic) NSUInteger priority;

@end

NS_ASSUME_NONNULL_END
