//
//  EKAlarm.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <EventKit/EKTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class EKCalendarItem, EKStructuredLocation;

/*!
    @class          EKAlarm
    @abstract       The EKAlarm class provides an interface for accessing and manipulating calendar event alarms.
    @discussion     The EKAlarm class represents alarms on an event. An alarm can be relative (e.g. 15 mins before) 
                    or absolute (specific time).
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
@interface EKAlarm : EKObject <NSCopying> {
}

/*!
    @method     alarmWithAbsoluteDate:
    @abstract   Creates a new autoreleased alarm with an absolute trigger time.
    @param      date    The date the alarm should fire.
*/
+ (EKAlarm *)alarmWithAbsoluteDate:(NSDate *)date;

/*!
    @method     alarmWithRelativeOffset:
    @abstract   Creates a new autoreleased alarm with a relative trigger time.
    @discussion Creates a new autoreleased alarm with a relative trigger time. This offset
                is added to the start date of the event.

    @param      offset    The offset from the event start that the alarm should fire.
*/
+ (EKAlarm *)alarmWithRelativeOffset:(NSTimeInterval)offset;

/*!
    @property   relativeOffset
    @abstract   Specifies a relative offset from an event start date to fire an alarm.
    @discussion Set this property to an appropriate negative value to establish an alarm trigger
                relative to the start date/time of an event. Setting this clears any existing
                date trigger.
*/
@property(nonatomic) NSTimeInterval relativeOffset;

/*!
    @property   absoluteDate
    @abstract   Represents an alarm that fires at a specific date.
    @discussion Set this property to a date to establish an absolute alarm trigger. Setting this
                clears any relative interval trigger.
*/
@property(nonatomic, copy, nullable) NSDate *absoluteDate;

/*!
    @property   structuredLocation
    @discussion Allows you to set a structured location (a location with a potential geo-coordinate)
                on an alarm. This is used in conjunction with proximity to do geofence-based
                triggering of reminders.
 */
@property(nonatomic, copy, nullable) EKStructuredLocation   *structuredLocation;

/*!
    @property   proximity
    @discussion Defines whether this alarm triggers via entering/exiting a geofence as defined by
                structuredLocation.
 */
@property(nonatomic) EKAlarmProximity    proximity;

/*!
 @property   type
 @abstract   The type of alarm, based on the action taken when triggering the alarm.
 @discussion This field is read-only; to change the type of alarm, set emailAddress for EKAlarmTypeEmail,
             soundName for EKAlarmTypeAudio or url for EKAlarmTypeProcedure.
             Setting all of those to nil will change it to EKAlarmTypeDisplay.
 */
@property(nonatomic, readonly) EKAlarmType type NS_AVAILABLE(10_8, NA);

/*!
 @property   emailAddress
 @abstract   An email address that is the recipient of an email alarm, which is an alarm that triggers an email message.
 @discussion When you set the emailAddress property, the action property is set to EKAlarmTypeEmail,
             and the soundName and url properties are set to nil.
 */
@property(nonatomic, copy, nullable) NSString *emailAddress NS_AVAILABLE(10_8, NA);

/*!
 @property   soundName
 @abstract   The name of the sound to play when the alarm triggers.
 @discussion The value of this property is the name of a system sound that can be used with
             the soundNamed: class method to create an NSSound object. When you set the soundName property,
             the action property is set to EKAlarmTypeAudio, and the emailAddress and url properties are set to nil.
 */
@property(nonatomic, copy, nullable) NSString *soundName NS_AVAILABLE(10_8, NA);

/*!
 @property   url
 @abstract   The URL to open when the alarm triggers.
 @discussion When you set the url property, the action property is set to EKAlarmTypeProcedure,
             and the emailAddress and soundName properties are set to nil.
             Note: Starting with OS X 10.9, it is not possible to create new procedure alarms or view URLs for existing procedure alarms.
             Trying to save or modify a procedure alarm will result in a save error.
             Editing other aspects of events or reminders that have existing procedure alarms is allowed as long as the alarm isn't modified.
 */
@property(nonatomic, copy, nullable) NSURL *url NS_DEPRECATED(10_8, 10_9, NA, NA);

@end

NS_ASSUME_NONNULL_END
