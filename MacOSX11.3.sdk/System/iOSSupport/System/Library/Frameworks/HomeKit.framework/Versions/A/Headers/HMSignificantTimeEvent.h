//  HMSignificantTimeEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMSignificantEvents.h>
#import <HomeKit/HMTimeEvent.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a significant time event.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMSignificantTimeEvent : HMTimeEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a significant time event.
 *
 * @param significantEvent The significant event for the trigger.
 *
 * @param offset An offset from the time of the signficant event. To specify an offset before the significant event, the
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
@property(readonly, strong, nonatomic) HMSignificantEvent significantEvent;

/*!
 * @brief offset An offset from the time of the signficant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 */
@property(readonly, strong, nonatomic, nullable) NSDateComponents *offset;

@end




/*!
 * @brief This class is used to represent a significant time event.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableSignificantTimeEvent : HMSignificantTimeEvent

/*!
 * @brief significantEvent The significant event for the trigger.
 */
@property(readwrite, strong, nonatomic) HMSignificantEvent significantEvent;

/*!
 * @brief offset An offset from the time of the signficant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 */
@property(readwrite, strong, nonatomic) NSDateComponents *offset;

@end

NS_ASSUME_NONNULL_END
