//
//  EKEvent.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>
#import <EventKit/EKCalendarItem.h>

NS_ASSUME_NONNULL_BEGIN

@class EKEventStore, EKCalendar, EKRecurrenceRule, EKAlarm, EKParticipant, EKStructuredLocation;

typedef NS_ENUM(NSInteger, EKEventAvailability) {
    EKEventAvailabilityNotSupported = -1,
    EKEventAvailabilityBusy = 0,
    EKEventAvailabilityFree,
    EKEventAvailabilityTentative,
    EKEventAvailabilityUnavailable
};

typedef NS_ENUM(NSInteger, EKEventStatus) {
    EKEventStatusNone = 0,
    EKEventStatusConfirmed,
    EKEventStatusTentative,
    EKEventStatusCanceled,
};


/*!
    @class      EKEvent
    @abstract   The EKEvent class represents an occurrence of an event.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKEvent : EKCalendarItem

/*!
    @method     eventWithEventStore:
    @abstract   Creates a new autoreleased event object.
*/
+ (EKEvent *)eventWithEventStore:(EKEventStore *)eventStore;

/*!
    @property   eventIdentifier
    @abstract   A unique identifier for this event.
    @discussion This identifier can be used to look the event up using [EKEventStore eventWithIdentifier:].
                You can use this not only to simply fetch the event, but also to validate the event
                has not been deleted out from under you when you get an external change notification
                via the EKEventStore database changed notification. If eventWithIdentifier: returns nil,
                the event was deleted.

                Please note that if you change the calendar of an event, this ID will likely change. It is
                currently also possible for the ID to change due to a sync operation. For example, if
                a user moved an event on a different client to another calendar, we'd see it as a 
                completely new event here.
 
                This may be nil for events that have not been saved.
*/
@property(null_unspecified, nonatomic, readonly) NSString *eventIdentifier;

/*!
    @property   allDay
    @abstract   Indicates this event is an 'all day' event.
*/
@property(nonatomic, getter=isAllDay) BOOL allDay;

/*!
     @property   startDate
     @abstract   The start date for the event.
     @discussion This property represents the start date for this event. Floating events (such
                 as all-day events) are currently always returned in the default time zone.
                 ([NSTimeZone defaultTimeZone])

                 This will be nil for new events until you set it.
 */
@property(null_unspecified, nonatomic, copy) NSDate *startDate;

/*!
    @property   endDate
    @abstract   The end date for the event.
    @discussion This will be nil for new events until you set it.
*/
@property(null_unspecified, nonatomic, copy) NSDate *endDate;

/*!
    @property   structuredLocation
    @abstract   Allows you to set a structured location (a location with a potential geo-coordinate) on an
                event. The getter for EKEvent’s location property just returns the structured location’s title.
                The setter for EKEvent’s location property is equivalent to
                [event setStructuredLocation:[EKStructuredLocation locationWithTitle:…]].
 */
@property(nonatomic, copy, nullable) EKStructuredLocation *structuredLocation NS_AVAILABLE(10_11, 9_0);

/*!
    @method     compareStartDateWithEvent
    @abstract   Comparison function you can pass to sort NSArrays of EKEvents by start date.
*/
- (NSComparisonResult)compareStartDateWithEvent:(EKEvent *)other;

/*!
    @property   organizer
    @abstract   The organizer of this event, or nil.
*/
@property(nonatomic, readonly, nullable) EKParticipant *organizer;

/*!
    @property   availability
    @abstract   The availability setting for this event.
    @discussion The availability setting is used by CalDAV and Exchange servers to indicate
                how the time should be treated for scheduling. If the calendar the event is
                currently in does not support event availability, EKEventAvailabilityNotSupported
                is returned.
*/
@property(nonatomic) EKEventAvailability    availability;

/*!
    @property   status
    @abstract   The status of the event.
    @discussion While the status offers four different values in the EKEventStatus enumeration,
                in practice, the only actionable and reliable status is canceled. Any other status
                should be considered informational at best. You cannot set this property. If you
                wish to cancel an event, you should simply remove it using removeEvent:.
*/
@property(nonatomic, readonly) EKEventStatus          status;

/*!
    @property   isDetached
    @abstract   Represents whether this event is detached from a recurring series.
    @discussion If this EKEvent is an instance of a repeating event, and an attribute of this 
                EKEvent has been changed from the default value generated by the repeating event,
                isDetached will return YES. If the EKEvent is unchanged from its default state, or
                is not a repeating event, isDetached returns NO.
*/
@property(nonatomic, readonly) BOOL isDetached;

/*!
    @property   occurrenceDate:
    @abstract   The occurrence date of an event if it is part of a recurring series.
    @discussion This is only set if the event is part of a recurring series. It returns
                the date on which this event was originally scheduled to occur. For occurrences
                that are unmodified from the recurring series, this is the same as the start date.
                This value will remain the same even if the event has been detached and its start 
                date has changed. Floating events (such as all-day events) are currently returned
                in the default time zone. ([NSTimeZone defaultTimeZone])
 
                This will be nil for new events until you set startDate.
 */
@property(null_unspecified, nonatomic, readonly) NSDate *occurrenceDate NS_AVAILABLE(10_8, 9_0);

/*!
     @method     refresh
     @abstract   Refreshes an event object to ensure it's still valid.
     @discussion When the database changes, your application is sent an EKEventStoreChangedNotification
                 note. You should generally consider all EKEvent instances to be invalid as soon as
                 you receive the notification. However, for events you truly care to keep around, you
                 can call this method. It ensures the record is still valid by ensuring the event and
                 start date are still valid. It also attempts to refresh all properties except those
                 you might have modified. If this method returns NO, the record has been deleted or is
                 otherwise invalid. You should not continue to use it. If it returns YES, all is still
                 well, and the record is ready for continued use. You should only call this method on
                 events that are more critical to keep around if possible, such as an event that is
                 being actively edited, as this call is fairly heavyweight. Do not use it to refresh
                 the entire selected range of events you might have had selected. It is mostly pointless
                 anyway, as recurrence information may have changed.
*/
- (BOOL)refresh;

/*!
    @method     birthdayContactIdentifier
    @abstract   Specifies the contact identifier of the person this event was created for.
    @discussion This property is only valid for events in the built-in Birthdays calendar. It specifies
                the contact identifier (for use with the Contacts framework) of the person this event was
                created for. For any other type of event, this property returns nil.
 */
@property(nonatomic, readonly, nullable) NSString *birthdayContactIdentifier NS_AVAILABLE(10_11, 9_0);

/*!
    @property   birthdayPersonID
    @abstract   Specifies the address book ID of the person this event was created for.
    @discussion  This property is only valid for events in the built-in Birthdays calendar. It specifies
                the Address Book ID of the person this event was created for. For any other type of event,
                this property returns -1.
*/
@property(nonatomic, readonly) NSInteger birthdayPersonID NS_DEPRECATED_IOS(5_0, 9_0, "Use birthdayContactIdentifier instead");

/*!
    @property   birthdayPersonUniqueID
    @abstract   Specifies the address book unique ID of the person this event was created for.
    @discussion This property is only valid for events in the built-in Birthdays calendar. It specifies
                the Address Book unique ID of the person this event was created for. For any other type of event,
                this property returns nil.
 */
@property(nonatomic, readonly, nullable) NSString *birthdayPersonUniqueID NS_DEPRECATED_MAC(10_8, 10_11, "Use birthdayContactIdentifier instead");

@end

NS_ASSUME_NONNULL_END
