//
//  HKWorkoutConfiguration.h
//  HealthKit
//
//  Copyright © 2018-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKMetadata.h>
#import <HealthKit/HKWorkout.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKWorkoutSessionLocationType
 @abstract      This enumerated type is used to represent the location type of a workout session.
 @discussion    This value represents whether a workout is performed indoors or outdoors.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionLocationType) {
    HKWorkoutSessionLocationTypeUnknown = 1,
    HKWorkoutSessionLocationTypeIndoor,
    HKWorkoutSessionLocationTypeOutdoor,
} API_AVAILABLE(ios(10.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @class         HKWorkoutConfiguration
 @abstract      An HKWorkoutConfiguration is an object that can be used to describe the workout activity.
 */
HK_EXTERN
API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0))
@interface HKWorkoutConfiguration : NSObject <NSCopying, NSSecureCoding>

/*!
 @property      activityType
 @abstract      Indicates the type of workout for the configuration.
 */
@property (assign) HKWorkoutActivityType activityType;

/*!
 @property      locationType
 @abstract      Indicates the type of location (indoors vs. outdoors) for the configuration.
 */
@property (assign) HKWorkoutSessionLocationType locationType;

/*!
 @property      swimmingLocationType
 @abstract      Indicates the type of swimming location (pool vs. open water) where the workout will take place.
 */
@property (assign) HKWorkoutSwimmingLocationType swimmingLocationType;

/*!
 @property      lapLength
 @abstract      Indicates the length of the pool, when the workout location type is pool.
 @discussion    This metric represents the length of the pool where the workout takes place. It should be a quantity with
                a unit representing length.
 */
@property (copy, nullable) HKQuantity *lapLength;

@end

NS_ASSUME_NONNULL_END
