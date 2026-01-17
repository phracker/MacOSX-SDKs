//  HMDurationEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMTimeEvent.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @brief This class is used to represent a duration of time.
 *
 * @note Characteristics turned on by the trigger will be turned off after the duration
 *       Supported characteristics are [HMCharacteristicTypePowerState, HMCharacteristicTypeActive]
 *       The duration event immediately ends if the characteristics are changed or updated during this period
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMDurationEvent : HMTimeEvent<NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a duration time event.
 *
 * @param duration The duration of time in seconds.
 *
 * @return Instance object representing the duration event.
 */
- (instancetype)initWithDuration:(NSTimeInterval)duration;

/*!
 * @brief duration The duration of time in seconds.
 */
@property (nonatomic, readonly, assign) NSTimeInterval duration;

@end


/*!
 * @brief This class is used to represent a duration of time.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableDurationEvent : HMDurationEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief duration The duration of time in seconds.
 */
@property (nonatomic, readwrite, assign) NSTimeInterval duration;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
