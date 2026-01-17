//  HMCalendarEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMTimeEvent.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @brief A calendar event which fires at an absolute time. It can also be used to set up a recurring events which will fire at a scheduled time.
 *
 * @note: Not all the fields in NSDateComponents are used to calculate the next fire date. Only Month, Day & Minutes are used. Other NSDateComponents such as
 *       year, weekday, quarter, week of the year / month are not used in calculation for next fire date.
 *       If its expected to fire on the same day, it should be at least 1 minute ahead or it could get scheduled for the next recurrent day.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCalendarEvent : HMTimeEvent<NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a calendar event
 *
 * @param fireDateComponents The date component that specifies the time when the event is fired
 *
 * @note: Not all the fields in NSDateComponents are used to calculate the next fire date. Only Month, Day & Minutes are used. Other NSDateComponents such as
 *       year, weekday, quarter, week of the year / month are not used in calculation for next fire date.
 *       If its expected to fire on the same day, it should be at least 1 minute ahead or it could get scheduled for the next recurrent day.
 *
 * @return Instance object representing the event trigger.
 */
- (instancetype)initWithFireDateComponents:(NSDateComponents *)fireDateComponents;


/*!
 * @brief The date component that specifies the time when the event is fired
 *
 * @note: Not all the fields in NSDateComponents are used to calculate the next fire date. Only Month, Day & Minutes are used. Other NSDateComponents such as
 *       year, weekday, quarter, week of the year / month are not used in calculation for next fire date.
 *       If its expected to fire on the same day, it should be at least 1 minute ahead or it could get scheduled for the next recurrent day.
 */
@property (nonatomic, readonly, strong) NSDateComponents *fireDateComponents;

@end

/*!
 * @brief This class is used to represent a calendar event.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableCalendarEvent : HMCalendarEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The date component that specifies the time when the event is fired
 */
@property (nonatomic, readwrite, strong) NSDateComponents *fireDateComponents;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
