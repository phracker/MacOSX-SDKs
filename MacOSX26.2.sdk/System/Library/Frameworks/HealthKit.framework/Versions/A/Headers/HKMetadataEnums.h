//
//  HKMetadataEnums.h
//  HealthKit
//
//  Copyright © 2013-2025 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <HealthKit/HKDefines.h>



NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKAppleECGAlgorithmVersion
 @abstract      Indicates which algorithm version number was used by the ECG app on Apple Watch.

 @constant      HKAppleECGAlgorithmVersion1     Apple Watch used a version 1 algorithm to generate this ECG.
 @constant      HKAppleECGAlgorithmVersion2     Apple Watch used a version 2 algorithm to generate this ECG.
 */
typedef NS_ENUM(NSInteger, HKAppleECGAlgorithmVersion) {
    HKAppleECGAlgorithmVersion1 = 1,
    HKAppleECGAlgorithmVersion2 API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0)),
} API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/*!
 @enum          HKBloodGlucoseMealTime
 @abstract      Indicates how your blood glucose reading relates to a meal.

 @constant      HKBloodGlucoseMealTimePreprandial   A glucose value measured at the time just before a meal.
 @constant      HKBloodGlucoseMealTimePostprandial  A glucose value measured after a meal.
 */
typedef NS_ENUM(NSInteger, HKBloodGlucoseMealTime) {
    HKBloodGlucoseMealTimePreprandial = 1,
    HKBloodGlucoseMealTimePostprandial,
} API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

typedef NS_ENUM(NSInteger, HKBodyTemperatureSensorLocation) {
    HKBodyTemperatureSensorLocationOther = 0,
    HKBodyTemperatureSensorLocationArmpit,
    HKBodyTemperatureSensorLocationBody,
    HKBodyTemperatureSensorLocationEar,
    HKBodyTemperatureSensorLocationFinger,
    HKBodyTemperatureSensorLocationGastroIntestinal,
    HKBodyTemperatureSensorLocationMouth,
    HKBodyTemperatureSensorLocationRectum,
    HKBodyTemperatureSensorLocationToe,
    HKBodyTemperatureSensorLocationEarDrum,
    HKBodyTemperatureSensorLocationTemporalArtery,
    HKBodyTemperatureSensorLocationForehead,
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKCyclingFunctionalThresholdPowerTestType
 @abstract      Represents the test used to determine a Cycling Functional Threshold Power value.

 @constant      HKCyclingFunctionalThresholdPowerTestTypeMaxExercise60Minute    The user was exerted to their physical
                                                                                limit for a sustained period of 60
                                                                                minutes.
 @constant      HKCyclingFunctionalThresholdPowerTestTypeMaxExercise20Minute    The user was exerted to their physical
                                                                                limit for a sustained period of 20
                                                                                minutes.
 @constant      HKCyclingFunctionalThresholdPowerTestTypeRampTest               Test with gradual intensity increase
                                                                                until exhaustion.
 @constant      HKCyclingFunctionalThresholdPowerTestTypePredictionExercise     An equation was used based on data from
                                                                                the user’s cycling workouts to calculate
                                                                                a predicted Cycling Functional Threshold
                                                                                Power.
 */
typedef NS_ENUM(NSInteger, HKCyclingFunctionalThresholdPowerTestType) {
    HKCyclingFunctionalThresholdPowerTestTypeMaxExercise60Minute = 1,
    HKCyclingFunctionalThresholdPowerTestTypeMaxExercise20Minute,
    HKCyclingFunctionalThresholdPowerTestTypeRampTest,
    HKCyclingFunctionalThresholdPowerTestTypePredictionExercise,
} API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

/*!
 @enum          HKDevicePlacementSide
 @abstract      The detected placement of the device during the bout of walking

 @constant      HKDevicePlacementSideUnknown    Unable to determine the placement of the device
 @constant      HKDevicePlacementSideLeft       Device predominantly worn on left side
 @constant      HKDevicePlacementSideRight      Device predominantly worn on right side
 @constant      HKDevicePlacementSideCentral    Device predominantly worn on the middle of the body
 */
typedef NS_ENUM(NSInteger, HKDevicePlacementSide) {
    HKDevicePlacementSideUnknown = 0,
    HKDevicePlacementSideLeft,
    HKDevicePlacementSideRight,
    HKDevicePlacementSideCentral,
} API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

typedef NS_ENUM(NSInteger, HKHeartRateMotionContext) {
    HKHeartRateMotionContextNotSet = 0,
    HKHeartRateMotionContextSedentary,
    HKHeartRateMotionContextActive,
} API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKHeartRateRecoveryTestType
 @abstract      Represents the test used to determine a Heart Rate Recovery value

 @constant      HKHeartRateRecoveryTestTypeMaxExercise                  The user was exerted to their physical limit to
                                                                        evaluate actual Heart Rate Recovery.
 @constant      HKHeartRateRecoveryTestTypePredictionSubMaxExercise     A specific test protocol was used to calculate
                                                                        and correlate a predicted Heart Rate Recovery.
 @constant      HKHeartRateRecoveryTestTypePredictionNonExercise        A non-exercise equation was used based on user
                                                                        metrics to calculate a predicted Heart Rate
                                                                        Recovery.
 */
typedef NS_ENUM(NSInteger, HKHeartRateRecoveryTestType) {
    HKHeartRateRecoveryTestTypeMaxExercise = 1,
    HKHeartRateRecoveryTestTypePredictionSubMaxExercise,
    HKHeartRateRecoveryTestTypePredictionNonExercise,
} API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

typedef NS_ENUM(NSInteger, HKHeartRateSensorLocation) {
    HKHeartRateSensorLocationOther = 0,
    HKHeartRateSensorLocationChest,
    HKHeartRateSensorLocationWrist,
    HKHeartRateSensorLocationFinger,
    HKHeartRateSensorLocationHand,
    HKHeartRateSensorLocationEarLobe,
    HKHeartRateSensorLocationFoot,
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKInsulinDeliveryReason
 @abstract      Represents a medical reason for the delivery of insulin

 @constant      HKInsulinDeliveryReasonBasal    Delivery for the base metabolic needs of the individual, often
                                                administered as a continuous rate from an insulin pump, or a periodic
                                                injection of slow-acting insulin.
 @constant      HKInsulinDeliveryReasonBolus    Delivery for the episodic needs of the individual, such as a meal or
                                                glucose level correction.
 */
typedef NS_ENUM(NSInteger, HKInsulinDeliveryReason) {
    HKInsulinDeliveryReasonBasal = 1,
    HKInsulinDeliveryReasonBolus,
} API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKPhysicalEffortEstimationType
 @abstract      Represents the estimation used to create a Physical Effort Sample.

 @constant      HKPhysicalEffortEstimationTypeActivityLookup    Indicates the value was calculated based on external
                                                                standard such as a stationary bike
 @constant      HKPhysicalEffortEstimationTypeDeviceSensed      Indicates the value was calculated based on movement
                                                                signals (walking, running etc.)
 */
typedef NS_ENUM(NSInteger, HKPhysicalEffortEstimationType) {
    HKPhysicalEffortEstimationTypeActivityLookup = 1,
    HKPhysicalEffortEstimationTypeDeviceSensed,
} API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

/*!
 @enum          HKSwimmingStrokeStyle
 @abstract      Represents a style of stroke used during a swimming workout.
 */
typedef NS_ENUM(NSInteger, HKSwimmingStrokeStyle) {
    HKSwimmingStrokeStyleUnknown = 0,
    HKSwimmingStrokeStyleMixed,
    HKSwimmingStrokeStyleFreestyle,
    HKSwimmingStrokeStyleBackstroke,
    HKSwimmingStrokeStyleBreaststroke,
    HKSwimmingStrokeStyleButterfly,
    HKSwimmingStrokeStyleKickboard API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0)),
} API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

typedef NS_ENUM(NSInteger, HKUserMotionContext) {
    HKUserMotionContextNotSet = 0,
    HKUserMotionContextStationary,
    HKUserMotionContextActive,
} API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @enum          HKVO2MaxTestType
 @abstract      Represents the test used to create a VO2 Max Sample.

 @constant      HKVO2MaxTestTypeMaxExercise                 The user was exerted to their physical limit to evaluate and
                                                            measure actual VO2Max.
 @constant      HKVO2MaxTestTypePredictionSubMaxExercise    A specific test protocol was used to calculate and correlate
                                                            a predicted VO2Max.
 @constant      HKVO2MaxTestTypePredictionNonExercise       A non-exercise equation was used based on user metrics to
                                                            calculate a predicted VO2Max.
 @constant      HKVO2MaxTestTypePredictionStepTest          The step test protocol was used to calculate and correlate a
                                                            predicted VO2Max.
 */
typedef NS_ENUM(NSInteger, HKVO2MaxTestType) {
    HKVO2MaxTestTypeMaxExercise = 1,
    HKVO2MaxTestTypePredictionSubMaxExercise,
    HKVO2MaxTestTypePredictionNonExercise,
    HKVO2MaxTestTypePredictionStepTest API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0)),
} API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKWaterSalinity
 @abstract      Represents the water salinity for an underwater depth or water temperature sample.
 @discussion    This value indicates the water salinity
 */
typedef NS_ENUM(NSInteger, HKWaterSalinity) {
    HKWaterSalinityFreshWater = 1,
    HKWaterSalinitySaltWater,
} API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

typedef NS_ENUM(NSInteger, HKWeatherCondition) {
    HKWeatherConditionNone = 0,
    HKWeatherConditionClear,
    HKWeatherConditionFair,
    HKWeatherConditionPartlyCloudy,
    HKWeatherConditionMostlyCloudy,
    HKWeatherConditionCloudy,
    HKWeatherConditionFoggy,
    HKWeatherConditionHaze,
    HKWeatherConditionWindy,
    HKWeatherConditionBlustery,
    HKWeatherConditionSmoky,
    HKWeatherConditionDust,
    HKWeatherConditionSnow,
    HKWeatherConditionHail,
    HKWeatherConditionSleet,
    HKWeatherConditionFreezingDrizzle,
    HKWeatherConditionFreezingRain,
    HKWeatherConditionMixedRainAndHail,
    HKWeatherConditionMixedRainAndSnow,
    HKWeatherConditionMixedRainAndSleet,
    HKWeatherConditionMixedSnowAndSleet,
    HKWeatherConditionDrizzle,
    HKWeatherConditionScatteredShowers,
    HKWeatherConditionShowers,
    HKWeatherConditionThunderstorms,
    HKWeatherConditionTropicalStorm,
    HKWeatherConditionHurricane,
    HKWeatherConditionTornado,
} API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKWorkoutSwimmingLocationType
 @abstract      This enumerated type is used to represent the location type of a swimming workout.
 @discussion    This value indicates whether a swimming workout was performed in a pool or open water.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSwimmingLocationType) {
    HKWorkoutSwimmingLocationTypeUnknown = 0,
    HKWorkoutSwimmingLocationTypePool,
    HKWorkoutSwimmingLocationTypeOpenWater,
} API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
