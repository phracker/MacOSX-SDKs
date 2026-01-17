//  HMSignificantTimeEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMSignificantEvents.h>
#import <HomeKit/HMTimeEvent.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @brief This class is used to represent a significant time event.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMSignificantTimeEvent : HMTimeEvent<NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a significant time event.
 *
 * @param significantEvent The significant event for the trigger.
 *
 * @param offset An offset from the time of the significant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 *
 * @return Instance object representing the significant event.
 */
- (instancetype)initWithSignificantEvent:(HMSignificantEvent)significantEvent
                                  offset:(nullable NSDateComponents *)offset;

/*!
 * @brief significantEvent The significant event for the trigger.
 */
@property (nonatomic, readonly, strong) HMSignificantEvent significantEvent;

/*!
 * @brief offset An offset from the time of the significant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 */
@property (nullable, nonatomic, readonly, strong) NSDateComponents *offset;

@end


/*!
 * @brief This class is used to represent a significant time event.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableSignificantTimeEvent : HMSignificantTimeEvent

/*!
 * @brief significantEvent The significant event for the trigger.
 */
@property (nonatomic, readwrite, strong) HMSignificantEvent significantEvent;

/*!
 * @brief offset An offset from the time of the significant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 */
@property (nonatomic, readwrite, strong) NSDateComponents *offset;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
