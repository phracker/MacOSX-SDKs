//
//  HKAppleSleepingBreathingDisturbancesClassification.h
//  HealthKit
//
//  Copyright © 2022-2024 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @enum          HKAppleSleepingBreathingDisturbancesClassification
 @abstract      This enumerated type is used to represent a classification of the user's breathing disturbances
 @constant      HKAppleSleepingBreathingDisturbancesClassificationNotElevated          BD level is not elevated
 @constant      HKAppleSleepingBreathingDisturbancesClassificationElevated                BD level is elevated
 */
typedef NS_ENUM(NSInteger, HKAppleSleepingBreathingDisturbancesClassification) {
    HKAppleSleepingBreathingDisturbancesClassificationNotElevated,
    HKAppleSleepingBreathingDisturbancesClassificationElevated,
} API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/*!
 @abstract  Determines the Breathing Disturbances classification for the provided BD value.
 @param     value Breathing Disturbances quantity
 @return    A Breathing Disturbances classification if one can be created, otherwise nil.
 */
HK_EXTERN NSNumber * _Nullable HKAppleSleepingBreathingDisturbancesClassificationForQuantity(HKQuantity *value) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0)) NS_REFINED_FOR_SWIFT;

/*!
 @abstract  Retrieves the minimum quantity for a Breathing Disturbances classification.
 @param     classification Breathing Disturbances classification for desired minimum value.
 */
HK_EXTERN HKQuantity * HKAppleSleepingBreathingDisturbancesMinimumQuantityForClassification(HKAppleSleepingBreathingDisturbancesClassification classification) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0)) NS_SWIFT_NAME(getter:HKAppleSleepingBreathingDisturbancesClassification.minimum(self:));

NS_ASSUME_NONNULL_END
