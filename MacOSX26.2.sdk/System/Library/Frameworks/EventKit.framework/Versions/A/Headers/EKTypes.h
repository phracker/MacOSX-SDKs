//
//  EKTypes.h
//  EventKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @enum       EKAuthorizationStatus
    @abstract   This enumerated type is used to indicate the currently granted authorization status for a specific
                entity type.
    @constant   EKAuthorizationStatusNotDetermined  The user has not yet made a choice regarding whether this application
                                                    may access the service.
    @constant   EKAuthorizationStatusRestricted     This application is not authorized to access the service.
                                                    The user cannot change this application’s status, possibly due to
                                                    active restrictions such as parental controls being in place.
    @constant   EKAuthorizationStatusDenied         The user explicitly denied access to the service for this application.
 
    @constant   EKAuthorizationStatusWriteOnly      This application is authorized to save new items.
    @constant   EKAuthorizationStatusFullAccess     This application is authorized to read or modify all data for the service.
    @constant   EKAuthorizationStatusAuthorized     (Deprecated) This application is authorized to access the service.
 */
typedef NS_ENUM(NSInteger, EKAuthorizationStatus) {
    EKAuthorizationStatusNotDetermined = 0,
    EKAuthorizationStatusRestricted,
    EKAuthorizationStatusDenied,
    EKAuthorizationStatusFullAccess NS_ENUM_AVAILABLE(14_0, 17_0),
    EKAuthorizationStatusWriteOnly NS_ENUM_AVAILABLE(14_0, 17_0),
    
    EKAuthorizationStatusAuthorized NS_ENUM_DEPRECATED(10_0, 14_0, 6_0, 17_0, "Check for full access or write only access") = EKAuthorizationStatusFullAccess,
} NS_AVAILABLE(10_9, 6_0);


typedef NS_ENUM(NSInteger, EKWeekday) {
    EKWeekdaySunday = 1,
    EKWeekdayMonday,
    EKWeekdayTuesday,
    EKWeekdayWednesday,
    EKWeekdayThursday,
    EKWeekdayFriday,
    EKWeekdaySaturday,
    
    EKSunday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdaySunday instead") = EKWeekdaySunday,
    EKMonday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayMonday instead") = EKWeekdayMonday,
    EKTuesday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayTuesday instead") = EKWeekdayTuesday,
    EKWednesday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayWednesday instead") = EKWeekdayWednesday,
    EKThursday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayThursday instead") = EKWeekdayThursday,
    EKFriday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdayFriday instead") = EKWeekdayFriday,
    EKSaturday NS_ENUM_DEPRECATED(10_8, 10_11, 4_0, 9_0, "Use EKWeekdaySaturday instead") = EKWeekdaySaturday,
};

/*!
    @enum       EKRecurrenceFrequency
    @abstract   The frequency of a recurrence
    @discussion EKRecurrenceFrequency designates the unit of time used to describe the recurrence.
                It has four possible values, which correspond to recurrence rules that are defined
                in terms of days, weeks, months, and years.
*/
typedef NS_ENUM(NSInteger, EKRecurrenceFrequency) {
    EKRecurrenceFrequencyDaily,
    EKRecurrenceFrequencyWeekly,
    EKRecurrenceFrequencyMonthly,
    EKRecurrenceFrequencyYearly
};

/*!
 @enum       EKParticipantType
 @abstract   Value representing the type of attendee.
 */
typedef NS_ENUM(NSInteger, EKParticipantType) {
    EKParticipantTypeUnknown,
    EKParticipantTypePerson,
    EKParticipantTypeRoom,
    EKParticipantTypeResource,
    EKParticipantTypeGroup
};

/*!
 @enum       EKParticipantRole
 @abstract   Value representing the role of a meeting participant.
 */
typedef NS_ENUM(NSInteger, EKParticipantRole) {
    EKParticipantRoleUnknown,
    EKParticipantRoleRequired,
    EKParticipantRoleOptional,
    EKParticipantRoleChair,
    EKParticipantRoleNonParticipant
};

/*!
 @enum       EKParticipantScheduleStatus
 @abstract   Value representing the status of a meeting invite.
 
 @constant   EKParticipantScheduleStatusNone                     Default value. Indicates that no
                                                                 invitation has been sent yet.
 @constant   EKParticipantScheduleStatusPending                  The invitation is in the process of being
                                                                 sent.
 @constant   EKParticipantScheduleStatusSent                     The invitation has been sent, but we have
                                                                 no way of determing if it was successfully
                                                                 delivered.
 @constant   EKParticipantScheduleStatusDelivered                The invitation has been sent and
                                                                 successfully delivered.
 @constant   EKParticipantScheduleStatusRecipientNotRecognized   The invitation wasn't delivered because we
                                                                 source doesn't recognize the recipient.
 @constant   EKParticipantScheduleStatusNoPrivileges             The invitation wasn't delivered because of
                                                                 insufficient privileges.
 @constant   EKParticipantScheduleStatusDeliveryFailed           The invitation wasn't delivered most
                                                                 likely due to a temporary failure.
 @constant   EKParticipantScheduleStatusCannotDeliver            The invitation wasn't delivered because
                                                                 we're unsure how to deliver it. This is a
                                                                 permanent failure.
 @constant   EKParticipantScheduleStatusRecipientNotAllowed      The invitation wasn't delivered because
                                                                 scheduling with the participant isn't
                                                                 allowed. This is a permanent failure.
 */
typedef NS_ENUM(NSInteger, EKParticipantScheduleStatus) {
    EKParticipantScheduleStatusNone,
    EKParticipantScheduleStatusPending,
    EKParticipantScheduleStatusSent,
    EKParticipantScheduleStatusDelivered,
    EKParticipantScheduleStatusRecipientNotRecognized,
    EKParticipantScheduleStatusNoPrivileges,
    EKParticipantScheduleStatusDeliveryFailed,
    EKParticipantScheduleStatusCannotDeliver,
    EKParticipantScheduleStatusRecipientNotAllowed,
};

/*!
 @enum       EKParticipantStatus
 @abstract   Value representing the status of a meeting participant.
 */
typedef NS_ENUM(NSInteger, EKParticipantStatus) {
    EKParticipantStatusUnknown,
    EKParticipantStatusPending,
    EKParticipantStatusAccepted,
    EKParticipantStatusDeclined,
    EKParticipantStatusTentative,
    EKParticipantStatusDelegated,
    EKParticipantStatusCompleted,
    EKParticipantStatusInProcess
};

/*!
 @enum       EKCalendarType
 @abstract   An enum representing the type of a calendar.
 
 @constant   EKCalendarTypeLocal        This calendar is sync'd from either Mobile Me or tethered.
 @constant   EKCalendarTypeCalDAV       This calendar is from a CalDAV server.
 @constant   EKCalendarTypeExchange     This calendar comes from an Exchange server.
 @constant   EKCalendarTypeSubscription This is a locally subscribed calendar.
 @constant   EKCalendarTypeBirthday     This is the built-in birthday calendar.
 */

typedef NS_ENUM(NSInteger, EKCalendarType) {
    EKCalendarTypeLocal,
    EKCalendarTypeCalDAV,
    EKCalendarTypeExchange,
    EKCalendarTypeSubscription,
    EKCalendarTypeBirthday
};

// Event availability support (free/busy)
typedef NS_OPTIONS(NSUInteger, EKCalendarEventAvailabilityMask) {
    EKCalendarEventAvailabilityNone         = 0,    // calendar doesn't support event availability
    
    EKCalendarEventAvailabilityBusy         = (1 << 0),
    EKCalendarEventAvailabilityFree         = (1 << 1),
    EKCalendarEventAvailabilityTentative    = (1 << 2),
    EKCalendarEventAvailabilityUnavailable  = (1 << 3),
};

typedef NS_ENUM(NSInteger, EKSourceType) {
    EKSourceTypeLocal,
    EKSourceTypeExchange,
    EKSourceTypeCalDAV,
    EKSourceTypeMobileMe,
    EKSourceTypeSubscribed,
    EKSourceTypeBirthdays
};

/*!
 @enum       EKEntityType
 @abstract   A value which specifies an entity type of event or reminder.
 */
typedef NS_ENUM(NSUInteger, EKEntityType) {
    EKEntityTypeEvent,
    EKEntityTypeReminder
};

/*!
 @enum       EKEntityMask
 @abstract   A bitmask based on EKEntityType that can be used to specify multiple entities at once.
 */
typedef NS_OPTIONS(NSUInteger, EKEntityMask) {
    EKEntityMaskEvent      = (1 << EKEntityTypeEvent),
    EKEntityMaskReminder   = (1 << EKEntityTypeReminder)
};

/*!
 @enum       EKAlarmProximity
 @abstract   A value indicating whether an alarm is triggered by entering or exiting a geofence.
 
 @constant   EKAlarmProximityNone       The alarm has no proximity trigger.
 @constant   EKAlarmProximityEnter      The alarm is set to fire when entering a region (geofence).
 @constant   EKAlarmProximityLeave      The alarm is set to fire when leaving a region (geofence).
 */
typedef NS_ENUM(NSInteger, EKAlarmProximity) {
    EKAlarmProximityNone,
    EKAlarmProximityEnter,
    EKAlarmProximityLeave
};

/*!
 @enum       EKAlarmType
 @abstract   A value which specifies the action that occurs when the alarm is triggered.
 
 @constant   EKAlarmTypeDisplay          The alarm displays a message.
 @constant   EKAlarmTypeAudio            The alarm plays a sound.
 @constant   EKAlarmTypeProcedure        The alarm opens a URL.
 @constant   EKAlarmTypeEmail            The alarm sends an email.
 */
typedef NS_ENUM(NSInteger, EKAlarmType) {
    EKAlarmTypeDisplay,
    EKAlarmTypeAudio,
    EKAlarmTypeProcedure,
    EKAlarmTypeEmail
};

/*!
 @enum       EKReminderPriority
 @abstract   A priority for a reminder.
 @discussion RFC 5545 allows priority to be specified with an integer in the range of 0-9,
             with 0 representing an undefined priority, 1 the highest priority, and 9 the lowest priority.
             Clients are encouraged to use these values when setting a reminders's priority,
             but is is possible to specify any integer value from 0 to 9.
 
 @constant   EKReminderPriorityNone          The reminder has no priority set.
 @constant   EKReminderPriorityHigh          The reminder is high priority.
 @constant   EKReminderPriorityMedium        The reminder is medium priority.
 @constant   EKReminderPriorityLow           The reminder is low priority.
 */
typedef NS_ENUM(NSUInteger, EKReminderPriority) {
    EKReminderPriorityNone     = 0,
    EKReminderPriorityHigh     = 1,
    EKReminderPriorityMedium   = 5,
    EKReminderPriorityLow      = 9
};

NS_ASSUME_NONNULL_END
