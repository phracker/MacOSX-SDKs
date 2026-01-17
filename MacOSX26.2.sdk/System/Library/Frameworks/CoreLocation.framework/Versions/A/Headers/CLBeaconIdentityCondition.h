/*
 *  CLBeaconIdentityCondition.h
 *  CoreLocation
 *
 *  Copyright (c) 2023 Apple Inc. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLCondition.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLBeaconMajorValue
 *
 *  Discussion:
 *    Type represents the most significant value in a beacon.
 *
 */
typedef uint16_t CLBeaconMajorValue;

/*
 *  CLBeaconMinorValue
 *
 *  Discussion:
 *    Type represents the least significant value in a beacon.
 *
 */
typedef uint16_t CLBeaconMinorValue;


/*
 *  CLBeaconIdentityCondition
 *
 *  Discussion:
 *    A condition that describes the identity caracteristics of a beacon.
 *
 *    A beacon identity is defined by UUID, major and minor values.
 *    UUID must be specified. If only UUID is specified, the major and
 *    minor values will be wildcarded and any beacons with the same
 *    UUID will satisfy the condition. Similarly if only UUID and
 *    major value are specified, the minor value will be wildcarded
 *    and any beacons with the same UUID and major value will satisfy
 *    the condition.
 *
 */
NS_REFINED_FOR_SWIFT
CL_EXTERN
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(watchos, tvos, visionos)
@interface CLBeaconIdentityCondition : CLCondition<NSCopying, NSSecureCoding>
/*
 *  UUID
 *
 *  Discussion:
 *    UUID associated with the beacon.
 *
 */
@property (readonly, nonatomic, copy) NSUUID *UUID;

/*
 *  major
 *
 *  Discussion:
 *    Most significant value associated with the beacon.
 *
 */
@property (readonly, nonatomic, copy, nullable) NSNumber *major NS_REFINED_FOR_SWIFT;

/*
 *  minor
 *
 *  Discussion:
 *    Least significant value associated with the beacon.
 *
 */
@property (readonly, nonatomic, copy, nullable) NSNumber *minor NS_REFINED_FOR_SWIFT;

/*
 *  initWithUUID:
 *
 *  Discussion:
 *    Initialize a beacon identity condition with a UUID. Major and
 *    minor values will be wildcarded.
 *
 */
- (instancetype)initWithUUID:(NSUUID *)uuid;

/*
 *  initWithUUID:major:
 *
 *  Discussion:
 *    Initialize a beacon identity condition with a UUID and major
 *    value.  Minor value will be wildcarded.
 *
 */
- (instancetype)initWithUUID:(NSUUID *)uuid major:(CLBeaconMajorValue)major;

/*
 *  initWithUUID:major:minor:
 *
 *  Discussion:
 *    Initialize a beacon identity condition with a UUID, major, and
 *    minor values.
 *
 */
- (instancetype)initWithUUID:(NSUUID *)uuid major:(CLBeaconMajorValue)major minor:(CLBeaconMinorValue)minor;
@end

NS_ASSUME_NONNULL_END
