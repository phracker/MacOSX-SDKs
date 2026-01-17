/*
 *  CLBeaconIdentityConstraint.h
 *  CoreLocation
 *
 *  Copyright (c) 2023 Apple Inc. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLCondition.h>
#import <CoreLocation/CLBeaconIdentityCondition.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * @brief
 *		CLBeaconIdentityConstraint
 *
 * @discussion
 *		Refer to \ref CLBeaconIdentityCondition for more details.
 */

CL_EXTERN
API_DEPRECATED_WITH_REPLACEMENT("Use CLBeaconIdentityCondition", macos(10.15, API_TO_BE_DEPRECATED), ios(13.0, API_TO_BE_DEPRECATED))
API_UNAVAILABLE(watchos, tvos)
API_UNAVAILABLE(visionos)
@interface CLBeaconIdentityConstraint : CLBeaconIdentityCondition<NSCopying, NSSecureCoding>

@end

NS_ASSUME_NONNULL_END
