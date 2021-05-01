//  HMDurationEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMTimeEvent.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a duration of time.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMDurationEvent : HMTimeEvent <NSCopying, NSMutableCopying>

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
@property(readonly, nonatomic, assign) NSTimeInterval duration;

@end


/*!
 * @brief This class is used to represent a duration of time.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableDurationEvent : HMDurationEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief duration The duration of time in seconds.
 */
@property(readwrite, nonatomic, assign) NSTimeInterval duration;

@end

NS_ASSUME_NONNULL_END
