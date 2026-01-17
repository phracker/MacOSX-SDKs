//
//  CLCircularGeographicCondition.h
//  CoreLocation
//
//  Copyright (c) 2023 Apple Inc. All rights reserved.
//

#pragma once

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLCondition.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
CL_EXTERN
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(watchos, tvos, visionos)

/*
 * @brief
 *		CLCircularGeographicCondition
 *
   @discussion
 *		Circular geographic condition defined by center(lat, lon) and radius
 */
@interface CLCircularGeographicCondition : CLCondition<NSSecureCoding>

/*
 * @brief
 *		center
 *
   @discussion
 *		The center of the circular geographic condition
 */
@property (readonly) CLLocationCoordinate2D center;

/*
 * @brief
 *		radius
 *
 * @discussion
 *		The radius of the circular geographic condition
 */
@property (readonly) CLLocationDistance radius;

/*
 * @brief
 *		initWithCenter:radius
 *
 * @discussion
 *		Returns an instance of circular geographic condition initialized
 *		with given center and radius
 */
-(instancetype) initWithCenter:(CLLocationCoordinate2D)center radius:(CLLocationDistance)radius;

@end

NS_ASSUME_NONNULL_END
