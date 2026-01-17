//
//  EKError.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>

/*!
    @const      EKErrorDomain 
    @abstract   Error domain for NSError values stemming from the EventKit Framework API.
    @discussion This error domain is used as the domain for all NSError instances stemming from the
                EventKit Framework.
*/
EVENTKIT_EXTERN NSString *const EKErrorDomain NS_AVAILABLE(10_8, 4_0);

/*!
    @enum       EKErrorCode
    @abstract   Error codes for NSError values stemming from the Calendar Framework.
    @discussion These error codes are used as the codes for all NSError instances stemmming from the
                Calendar Framework.
 
    @constant   EKErrorEventNotMutable                  The event is not mutable and cannot be saved/deleted.
    @constant   EKErrorNoCalendar                       The event has no calendar set.
    @constant   EKErrorNoStartDate                      The event has no start date set.
    @constant   EKErrorNoEndDate                        The event has no end date set.
    @constant   EKErrorDatesInverted                    The end date is before the start date.
    @constant   EKErrorInternalFailure                  An internal error occurred.
    @constant   EKErrorCalendarReadOnly                 Calendar can not have events added to it.
    @constant   EKErrorDurationGreaterThanRecurrence    The duration of an event is greater than the recurrence interval.
    @constant   EKErrorAlarmGreaterThanRecurrence       The alarm interval is greater than the recurrence interval
    @constant   EKErrorStartDateTooFarInFuture          The start date is further into the future than the calendar will display.
    @constant   EKErrorStartDateCollidesWithOtherOccurrence The start date specified collides with another occurrence of that event, and the current calendar doesn't allow it.
    @constant   EKErrorObjectBelongsToDifferentStore    The object you are passing doesn't belong to the calendar store you're dealing with.
    @constant   EKErrorInvitesCannotBeMoved             The event is an invite, and therefore cannot move to another calendar.
    @constant   EKErrorInvalidSpan                      An invalid span was passed when saving/deleting.
    @constant   EKErrorCalendarHasNoSource              An attempt to save a calendar with no source set was made.
    @constant   EKErrorCalendarSourceCannotBeModified   The calendar cannot be moved to another source.
    @constant   EKErrorCalendarIsImmutable              The calendar is immutable and cannot be modified or deleted.
    @constant   EKErrorSourceDoesNotAllowCalendarAddDelete   Some sources (accounts) do not allow calendars to be added or removed.
    @constant   EKErrorRecurringReminderRequiresDueDate A recurring reminder requires a due date.
    @constant   EKErrorStructuredLocationsNotSupported  The source this calendar belongs to does not support structured locations.
    @constant   EKErrorReminderLocationsNotSupported    This source doesn't support locations on Reminders.
    @constant   EKErrorAlarmProximityNotSupported       This source doesn't allow alarm proximity (geofencing).
    @constant   EKErrorCalendarDoesNotAllowEvents       You are trying to add an event to a calendar that does not allow events.
    @constant   EKErrorCalendarDoesNotAllowReminders    You are trying to add a reminder to a calendar that does not allow reminders.
    @constant   EKErrorSourceDoesNotAllowReminders      You are trying to add a calendar that allows reminders to a source that does not allow them.
    @constant   EKErrorSourceDoesNotAllowEvents         You are trying to add a calendar that allows events to a source that does not allow them.
    @constant   EKErrorPriorityIsInvalid                You have set an invalid priority for a reminder.  Priorities must be between 0 and 9.
    @constant   EKErrorInvalidEntityType                This is not a valid EKEntityType
    @constant   EKErrorProcedureAlarmsNotMutable        Procedure alarms may not be created or modified.
    @constant   EKErrorEventStoreNotAuthorized          The user has not authorized your application to access their events and/or reminders.
    @constant   EKErrorOSNotSupported                   The action is not supported on the current operating system.
    @constant   EKErrorInvalidCalendar                  The given calendar is invalid or nil.
    @constant   EKErrorNotificationsCollectionFlagNotSet  The given notification collection does not have the EKNotificationsCollectionFlag set.
    @constant   EKErrorSourceMismatch                     The source for an object does not match its containers source.
    @constant   EKErrorNotificationCollectionMismatch     The notification collection containing a given notification does not match the collection we are trying to save.
    @constant   EKErrorNotificationSavedWithoutCollection The notification is being saved without first adding it to a notification collection and saving the collection.
*/

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED || !TARGET_OS_IPHONE
typedef NS_ENUM(NSInteger, EKErrorCode) {
    EKErrorEventNotMutable,
    EKErrorNoCalendar,
    EKErrorNoStartDate,
    EKErrorNoEndDate,
    EKErrorDatesInverted,
    EKErrorInternalFailure,
    EKErrorCalendarReadOnly,
    EKErrorDurationGreaterThanRecurrence,
    EKErrorAlarmGreaterThanRecurrence,
    EKErrorStartDateTooFarInFuture,
    EKErrorStartDateCollidesWithOtherOccurrence,
    EKErrorObjectBelongsToDifferentStore,
    EKErrorInvitesCannotBeMoved,
    EKErrorInvalidSpan,
    EKErrorCalendarHasNoSource,
    EKErrorCalendarSourceCannotBeModified,
    EKErrorCalendarIsImmutable,
    EKErrorSourceDoesNotAllowCalendarAddDelete,
    EKErrorRecurringReminderRequiresDueDate,
    EKErrorStructuredLocationsNotSupported,
    EKErrorReminderLocationsNotSupported,
    EKErrorAlarmProximityNotSupported,
    EKErrorCalendarDoesNotAllowEvents,
    EKErrorCalendarDoesNotAllowReminders,
    EKErrorSourceDoesNotAllowReminders,
    EKErrorSourceDoesNotAllowEvents,
    EKErrorPriorityIsInvalid,
    EKErrorInvalidEntityType,
    EKErrorProcedureAlarmsNotMutable,
    EKErrorEventStoreNotAuthorized,
    EKErrorOSNotSupported,
    EKErrorInvalidInviteReplyCalendar,
    EKErrorNotificationsCollectionFlagNotSet,
    EKErrorSourceMismatch,
    EKErrorNotificationCollectionMismatch,
    EKErrorNotificationSavedWithoutCollection,
    EKErrorReminderAlarmContainsEmailOrUrl,
    
    EKErrorLast // used internally
};
#endif
