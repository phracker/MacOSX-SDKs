//
//  HMTimerTrigger.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMTrigger.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @brief Timer based trigger.
 *
 * @discussion This class represents a trigger that is based on timers.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMTimerTrigger : HMTrigger

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initialize a new HMTimerTrigger object.
 *
 * @param name Name for the trigger.
 *
 * @param fireDate The initial fire date for the timer trigger. The seconds value must be zero.
 *                 Date should be at least 1 minute ahead for reliable firing.
 *                 HMErrorCodeDateMustBeOnSpecifiedBoundaries will be returned when adding the trigger
 *                 to a home if the fireDate includes a seconds value other than 0.
 *
 * @param recurrence The recurrence interval to fire the trigger. A value of nil indicates that the
 *                   trigger is non-repeating. The minimum reccurence interval is 5 minutes, maximum
 *                   recurrence interval is 5 weeks and the recurrence interval must be specified in
 *                   multiples of whole minutes.
 *
 * @discussion Validity checks are performed when the trigger is added to the home and the NSError in
 *             the completion block for addTrigger: method indicates the reason for the failure:
 *             HMErrorCodeDateMustBeOnSpecifiedBoundaries is returned if the seconds/nanoseconds fields
 *             in recurrence interval or seconds field in fireDate have a value other than 0.
 *             HMErrorCodeRecurrenceTooSmall is returned if recurrence interval is less than 5 minutes.
 *             HMErrorCodeRecurrenceTooLarge is returned if recurrence interval is greater than 5 weeks.
 *             HMErrorCodeFireDateInPast is returned if recurrence is nil and fireDate is in the past.
 */
- (instancetype)initWithName:(NSString *)name
                    fireDate:(NSDate *)fireDate
                  recurrence:(nullable NSDateComponents *)recurrence API_AVAILABLE(ios(16.4), watchos(9.4), tvos(16.4), macCatalyst(16.4)) API_UNAVAILABLE(macos);

- (instancetype)initWithName:(NSString *)name
                    fireDate:(NSDate *)fireDate
                    timeZone:(nullable NSTimeZone *)timeZone
                  recurrence:(nullable NSDateComponents *)recurrence
          recurrenceCalendar:(nullable NSCalendar *)recurrenceCalendar API_DEPRECATED_WITH_REPLACEMENT("-initWithName:fireDate:recurrence:", ios(8.0, 16.4), macos(10.14, 13.3), macCatalyst(14.0, 16.4), tvos(10.0, 16.4), watchos(2.0, 9.4));

/*!
 * @brief Specifies when, in an absolute time, the trigger should fire the first time.
 *
 * @discussion Timer triggers are only set at the top of the minute. When the timer trigger fires,
 *             it will typically fire within 1 minute of the scheduled fire date or calculated
 *             recurrence fire date, depending on how the system is managing its resources.
 *
 * @note Should be at least 1 minute ahead for reliable firing.
 */
@property (nonatomic, readonly, copy) NSDate *fireDate;

@property (nullable, nonatomic, readonly, copy) NSTimeZone *timeZone API_DEPRECATED("Use HMEventTrigger with HMCalendarEvent for triggers based on a time-zone-relative time of day", ios(8.0, 16.4), macos(10.14, 13.3), macCatalyst(14.0, 16.4), tvos(10.0, 16.4), watchos(2.0, 9.4));

/*!
 * @brief The date components that specify how a trigger is to be repeated. 
 *
 * @discussion This value must be nil if the trigger should not repeat. The date component
 *             values are relative to the initial fire date of the trigger. If the
 *             calendar value of the recurrence is nil, the current calendar
 *             will be used to calculate the recurrence interval. Recurrence example: if a
 *             trigger should repeat every hour, set the 'hour' property of the
 *             recurrence to 1. The minimum recurrence interval is 5 minutes, maximum recurrence
 *             interval is 5 weeks and the recurrence interval must be specified in multiples of
 *             whole minutes. Examples are 5 minutes, 6 minutes, 1 day, 2 weeks.
 *
 */
@property (nullable, nonatomic, readonly, copy) NSDateComponents *recurrence;

@property (nullable, nonatomic, readonly, copy) NSCalendar *recurrenceCalendar API_DEPRECATED("No longer supported", ios(8.0, 16.4), macos(10.14, 13.3), macCatalyst(14.0, 16.4), tvos(10.0, 16.4), watchos(2.0, 9.4));

/*!
 * @brief This method is used to change the fire date of a timer trigger.
 *
 * @param fireDate New fire date for the trigger. The seconds value must be zero.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success. HMErrorCodeDateMustBeOnSpecifiedBoundaries will
 *                   be returned if the fireDate includes a seconds value other than 0.
 */
- (void)updateFireDate:(NSDate *)fireDate completionHandler:(void (^)(NSError *__nullable error))completion API_UNAVAILABLE(watchos, tvos);

- (void)updateTimeZone:(nullable NSTimeZone *)timeZone completionHandler:(void (^)(NSError *__nullable error))completion API_DEPRECATED("Use HMEventTrigger with HMCalendarEvent for triggers based on a time-zone-relative time of day", ios(8.0, 16.4), macos(10.14, 13.3), macCatalyst(14.0, 16.4), tvos(12.0, 16.4), watchos(5.0, 9.4));

/*!
 * @brief This method is used to change the recurrence interval for a timer trigger.
 *
 * @param recurrence New recurrence interval for the trigger. Passing a nil indicates that
 *                   the trigger is non-repeating. The minimum recurrence interval is 5 minutes,
 *                   maximum recurrence interval is 5 weeks and the recurrence interval must be specified
 *                   in multiples of whole minutes.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request:
 *                   HMErrorCodeDateMustBeOnSpecifiedBoundaries is returned if the seconds/nanoseconds
 *                   fields have a value other than 0;
 *                   HMErrorCodeRecurrenceTooSmall is returned if the recurrence interval is less than
 *                   5 minutes;
 *                   HMErrorCodeRecurrenceTooLarge is returned if the recurrence interval is
 *                   greater than 5 weeks. *                   error will be nil on success.
 */
- (void)updateRecurrence:(nullable NSDateComponents *)recurrence
       completionHandler:(void (^)(NSError *__nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
