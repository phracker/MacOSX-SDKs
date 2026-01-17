//	
//	CalCalendarStore.h
//	Calendar Store Framework
//	
//  Copyright 2006 Apple Inc. All rights reserved.
//	
//	Allows the client to access the user's calendars, events, and tasks. Clients can also save changes to an event, task,
//  or calendar.
//
//  The Calendar Store framework is deprecated.  Please use the Event Kit framework instead. 

@class CalCalendar, CalEvent, CalTask;

//  CalSpan
//  This enumerated type is used to indicate the scope of a change being made to a repeating event. CalSpanThisEvent 
//  indicates the changes should apply only to this event, CalSpanFutureEvents indicates the changes should apply to 
//  this event and all future events in the pattern, and using CalSpanAllEvents will apply the change to every event, 
//  past and present, in the pattern.
typedef enum {
    CalSpanThisEvent,
    CalSpanFutureEvents,
    CalSpanAllEvents
} CalSpan NS_ENUM_DEPRECATED_MAC(10_5, 10_8);

@interface CalCalendarStore : NSObject
{
    @private
    void *_reserved;
}

//  Returns an instance of the calendar store.

+ (CalCalendarStore *)defaultCalendarStore NS_DEPRECATED_MAC(10_5, 10_8);


/*  Accessing calendars  */

//  An array of all the user's calendars, represented as CalCalendars. If the user has iCal data from a previous
//  version of Mac OS X, but has not launched iCal in 10.5, this will return an array of empty calendars. iCal needs
//  to be launched at least once in order to migrate the user's calendar data.
//
//  If no calendar data from any version of Mac OS X exists, then this method will create and return two default
//  calendars, named Home and Work.
- (NSArray *)calendars NS_DEPRECATED_MAC(10_5, 10_8);

//  The calendar associated with the specific UID. If no record with this UID exists, nil is returned.
- (CalCalendar *)calendarWithUID:(NSString *)UID NS_DEPRECATED_MAC(10_5, 10_8);

/*  Writing changes to calendars  */

//   CalendarStoreErrors.h defines the error codes and the domain used by NSError in the following methods.

//  - (BOOL)saveCalendar:(CalCalendar *)calendar error:(NSError **)error;
//  - (BOOL)removeCalendar:(CalCalendar *)calendar error:(NSError **)error;
//  
//  These methods allow the client to add, modify, and remove calendars in the user's calendar store. saveCalendar:error:
//  should be used both to add a new calendar to the calendar store, and to modify a calendar already in the store.
//  The only calendars that can be added with this API are local calendars; it is not possible to add subscribed
//  or CalDAV calendars, or the birthday calendar.
//  
//  Changes made to a CalCalendar are not persisted until that calendar has been passed to saveCalendar. If saveCalendar
//  is not called, the changes will be lost.

- (BOOL)saveCalendar:(CalCalendar *)calendar error:(NSError **)error NS_DEPRECATED_MAC(10_5, 10_8);
- (BOOL)removeCalendar:(CalCalendar *)calendar error:(NSError **)error NS_DEPRECATED_MAC(10_5, 10_8);


/*  Accessing events and tasks  */

//  - (NSArray *)eventsWithPredicate:(NSPredicate *)predicate;
//
//  This method returns an array of all the CalEvents which match the conditions described in the predicate that is 
//  passed. At this time, eventsWithPredicate: only suppports predicates generated with one of the class methods added 
//  to NSPredicate below.
//  
//  If the predicate passed to eventsWithPredicate: was not created with one of the class methods included in this file, 
//  nil is returned. If nil is passed as the predicate, an exception will be raised.
//
//  For performance reasons, this method will only return occurrences of repeating events that fall within a specific 
//  four year timespan. If the date range between the startDate and endDate is greater than four years, then the 
//  timespan containing recurrences is always the first four years of date range.

- (NSArray *)eventsWithPredicate:(NSPredicate *)predicate NS_DEPRECATED_MAC(10_5, 10_8);
- (CalEvent *)eventWithUID:(NSString *)uid occurrence:(NSDate *)date NS_DEPRECATED_MAC(10_5, 10_8);

//  - (NSArray *)tasksWithPredicate:(NSPredicate *)predicate;
//
//  This method returns an array of all the CalTasks which match the conditions described in the predicate that is 
//  passed. At this time, tasksWithPredicate: only suppports predicates generated with one of the class methods added to 
//  NSPredicate below.
//
//  If the predicate passed to tasksWithPredicate: was not created with one of the class methods included in thsi file, 
//  nil is returned. If nil is passed as the predicate, an exception will be raised.

- (NSArray *)tasksWithPredicate:(NSPredicate *)predicate NS_DEPRECATED_MAC(10_5, 10_8);
- (CalTask *)taskWithUID:(NSString *)uid NS_DEPRECATED_MAC(10_5, 10_8);

/*  Writing changes to events and tasks  */

//   CalendarStoreErrors.h defines the error codes and the domain used by NSError in the following methods.

//  - (BOOL)saveEvent:(CalEvent *)event span:(CalSpan)span error:(NSError **)error;
//  - (BOOL)removeEvent:(CalEvent *)event span:(CalSpan)span error:(NSError **)error;
//  
//  These methods allow the client to add, modify, and remove events in the user's calendar store. The first method 
//  should be used both to add a new event to the calendar store, and to modify an event already in the calendar store. 
//  If the event being saved is a repeating event, the second argument is used to describe whether the change being made 
//  should apply to future occurrences of that event, all occurrences, or only this instance. This is analogous to 
//  options on the dialog iCal presents when a user modifies a recurring event (though iCal's UI does not provide a way 
//  to change all events, past and present).
//
//  Changes made to a CalEvent are not persisted until that event has been passed to saveEvent. If saveEvent is not 
//  called, the changes will be lost.
//  
//  Applying changes to all events or all future events may cause the UID or the occurrence date of the event to change.

- (BOOL)saveEvent:(CalEvent *)event span:(CalSpan)span error:(NSError **)error NS_DEPRECATED_MAC(10_5, 10_8);
- (BOOL)removeEvent:(CalEvent *)event span:(CalSpan)span error:(NSError **)error NS_DEPRECATED_MAC(10_5, 10_8);

//  - (BOOL)saveTask:(CalTask *)task error:(NSError **)error;
//  - (BOOL)removeTask:(CalTask *)task error:(NSError **)error;
//
//  These methods allow the client to add, modify, and remove tasks in the user's calendar store. saveTask: should be 
//  used both to add a new task to the calendar store, and to modify a task already in the calendar store.
//  
//  Changes made to a CalTask are not persisted until that task has been passed to saveTask. If saveTask is not called, 
//  the changes will be lost.

- (BOOL)saveTask:(CalTask *)task error:(NSError **)error NS_DEPRECATED_MAC(10_5, 10_8);
- (BOOL)removeTask:(CalTask *)task error:(NSError **)error NS_DEPRECATED_MAC(10_5, 10_8);


//  A predicate passed to eventsWithPredicate: or tasksWithPredicate: must be returned from one of these methods.

+ (NSPredicate *)eventPredicateWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate calendars:(NSArray *)calendars NS_DEPRECATED_MAC(10_5, 10_8);
+ (NSPredicate *)eventPredicateWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate UID:(NSString *)UID calendars:(NSArray *)calendars NS_DEPRECATED_MAC(10_5, 10_8);

+ (NSPredicate *)taskPredicateWithCalendars:(NSArray *)calendars NS_DEPRECATED_MAC(10_5, 10_8); //  This will return all tasks, completed and uncompleted, for a set of calendars
+ (NSPredicate *)taskPredicateWithUncompletedTasks:(NSArray *)calendars NS_DEPRECATED_MAC(10_5, 10_8);
+ (NSPredicate *)taskPredicateWithUncompletedTasksDueBefore:(NSDate *)dueDate calendars:(NSArray *)calendars NS_DEPRECATED_MAC(10_5, 10_8);
+ (NSPredicate *)taskPredicateWithTasksCompletedSince:(NSDate *)completedSince calendars:(NSArray *)calendars NS_DEPRECATED_MAC(10_5, 10_8);

@end

//  The Calendar Store frameworks posts notifications when any application, including yours, makes changes to the user's 
//  calendar data. Your application will not receive these notification until you have called defaultCalendarStore at 
//  least once.

//  CalCalendarsChangedNotification
//  This notification will be posted when this process has added, modified, or removed a calendar. The process ID of the 
//  sender and the effective user ID are included in the userInfo dictionary, and can be accessed through the 
//  CalSenderProcessIDKey and CalUserUIDKey, respectively. In addition, depending on the operation performed, one or 
//  more of the following keys may be included: CalInsertedRecordsKey, CalUpdatedRecordsKey, and CalDeletedRecordsKey. 
//  The values for each of the keys are arrays containing the UIDs of the affected calendar(s).

extern NSString * const CalCalendarsChangedNotification NS_DEPRECATED_MAC(10_5, 10_8);

//  CalEventsChangedNotification
//  This notification will be posted when this process has added, modified, or removed an event. The process ID of the 
//  sender and the effective user ID are included in the userInfo dictionary, and can be accessed through the 
//  CalSenderProcessIDKey and CalUserUIDKey, respectively. In addition, depending on the operation performed, one or 
//  more of the following keys may be included: CalInsertedRecordsKey, CalUpdatedRecordsKey, and CalDeletedRecordsKey. 
//  The values for each of the keys are arrays containing the UIDs of the affected event(s).

extern NSString * const CalEventsChangedNotification NS_DEPRECATED_MAC(10_5, 10_8);

//  CalTasksChangedNotification
//  This notification will be posted when this process has added, modified, or removed a task. The process ID of the 
//  sender and the effective user ID are included in the userInfo dictionary, and can be accessed through the 
//  CalSenderProcessIDKey and CalUserUIDKey, respectively. In addition, depending on the operation performed, one or 
//  more of the following keys may be included: CalInsertedRecordsKey, CalUpdatedRecordsKey, and CalDeletedRecordsKey. 
//  The values for each of the keys are the affected task(s).

extern NSString * const CalTasksChangedNotification NS_DEPRECATED_MAC(10_5, 10_8);

//  CalEventsChangedExternallyNotification, CalTasksChangedExternallyNotification
//  These notifications are exactly the same as the similarly named ones described above, except that they are only 
//  posted when another process has added, modified, or removed an event, or task. Since modifying calendars is not 
//  currently supported in this API, there is not a separate notification for calendars which have been changed 
//  externally; for now all modifications to calendars are made externally, and clients should just observe the 
//  CalCalendarsChangedExternallyNotification.

extern NSString * const CalCalendarsChangedExternallyNotification NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalEventsChangedExternallyNotification NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalTasksChangedExternallyNotification NS_DEPRECATED_MAC(10_5, 10_8);


//  CalInsertedRecords, CalUpdatedRecords, CalDeletedRecords
//  The userInfo dictionary in the above notifications will contain the following 3 keys. Value for each keys is an 
//  array of UIDs of CalCalendars, CalEvents, or CalTasks, depending on the notification. If all three values are nil, 
//  that indicates everything has changed, and the client should refresh the calendar, event, and task information 
//  currently being used. Since this tends to be an expensive and inconvenient operation, it will only occur under 
//  unusual circumstances, such as when restoring from backup.

extern NSString * const CalInsertedRecordsKey;
extern NSString * const CalUpdatedRecordsKey;
extern NSString * const CalDeletedRecordsKey;

//  These constants can be passed as keys to the userInfo dictionary included when any of the above notifications
//  are posted.

extern NSString * const CalSenderProcessIDKey NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalUserUIDKey NS_DEPRECATED_MAC(10_5, 10_8);

