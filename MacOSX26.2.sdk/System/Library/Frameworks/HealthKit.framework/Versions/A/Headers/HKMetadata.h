//
//  HKMetadata.h
//  HealthKit
//
//  Copyright (c) 2013-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKMetadataEnums.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the serial number of the device that created the HKObject.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceSerialNumber API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyBodyTemperatureSensorLocation
 @abstract      Represents the location where a particular body temperature reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKBodyTemperatureSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyBodyTemperatureSensorLocation API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyHeartRateSensorLocation
 @abstract      Represents the location where a particular heart rate reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKHeartRateSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateSensorLocation API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyHeartRateMotionContext
 @abstract      Represents the context in which a particular heart rate reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKHeartRateMotionContext value. The value is active
                (HKHeartRateMotionContextActive) if the user is in motion or working out, sedentary if the user is
                still (HKHeartRateMotionContextSedentary), or not set (HKHeartRateMotionContextNotSet) otherwise.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateMotionContext API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyUserMotionContext
 @abstract      Represents the user's motion when a particular sample was taken.
 @discussion    The expected value type is an NSNumber containing a HKUserMotionContext value. The value is active
                (HKUserMotionContextActive) if the user is in motion or working out, stationary if the user is
                still (HKUserMotionContextStationary), or not set (HKUserMotionContextNotSet) otherwise.
 */
HK_EXTERN NSString * const HKMetadataKeyUserMotionContext API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeySessionEstimate
 @abstract      Represents a per-session estimate prior to longitudinal smoothing applied to the value stored in the associated HKQuantitySample.
 @discussion    The expected value type is an HKQuantity object with a unit compatible with the associated HKQuantitySample.
 */
HK_EXTERN NSString * const HKMetadataKeySessionEstimate API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyHeartRateRecoveryTestType
 @abstract      Represents the test used to determine a Heart Rate Recovery value
 @discussion    The expected value type is an NSNumber containing a HKHeartRateRecoveryTestType value.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateRecoveryTestType API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyHeartRateRecoveryActivityType
 @abstract      Represents the activity which preceded a Heart Rate Recovery value
 @discussion    The expected value type is an NSNumber containing a HKWorkoutActivityType value.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateRecoveryActivityType API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyHeartRateRecoveryActivityDuration
 @abstract      Represents the duration of activity which preceded a Heart Rate Recovery value
 @discussion    The expected value type is an HKQuantity object compatible with a time unit.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateRecoveryActivityDuration API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyHeartRateRecoveryMaxObservedRecoveryHeartRate
 @abstract      Represents the maximum heart rate observed during the corresponding Heart Rate Recovery sample interval
 @discussion    The expected value type is an HKQuantity object compatible with "count/min" unit (eg "BPM").
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateRecoveryMaxObservedRecoveryHeartRate API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyFoodType
 @abstract      Represents the type of food that was consumed when creating an HKObject.
 @discussion    This should be a short string representing the type of food, such as 'Banana'. The expected value type
                is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyFoodType API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyUDIDeviceIdentifier
 @abstract      Represents the device identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    The device identifier can be used to reference the GUDID (Globally Unique Device Identifier Database).
                The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIDeviceIdentifier API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the production identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    While part of a device's UDI, the production identifier is not saved in the FDA's GUDID 
                (Globally Unique Device Identifier Database) and its use in HealthKit is now discouraged for
                user privacy reasons. Apps should consider handling this independently of HealthKit APIs if
                needed.
                The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIProductionIdentifier API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyDigitalSignature
 @abstract      Represents a digital signature validating the origin of an HKObject's value.
 @discussion    Intended to provide data integrity for sample data produced by trusted (tamper resistant) measuring devices.
                The digital signature format should be CMS (Cryptographic Message Syntax specified in IETF RFC 5652).
                It should be a “Signed-data” type signature containing the data items to be signed (e.g., timestamp, value, etc.)
                using ASN.1 encoding with DER (Distinguished Encoding Rules). The entire enveloping signature should be further
                encoded using base64. Recommended digest is SHA256, and recommended cipher is FIPS PUB 186-4 Digital Signature 
                Standard Elliptic Curve P-256. See documentation for details.

 */
HK_EXTERN NSString * const HKMetadataKeyDigitalSignature API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyExternalUUID
 @abstract      Represents a unique identifier for an HKObject that is set by its source.
                Uniqueness of objects with the same value of this key is not enforced by HealthKit.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyExternalUUID API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeySyncIdentifier
 @abstract      Represents an identifier for an HKObject that is set by its source and is used by HealthKit to uniquely
                identify an object.
 @discussion    Saving a HKObject with a HKMetadataKeySyncIdentifier will replace an existing HKObject with the
                same HKMetadataKeySyncIdentifier value if the new HKObject has a greater HKMetadataKeySyncVersion.
                The new sample will be added to all HKWorkouts or HKCorrelations containing the replaced sample.
                HKMetadataKeySyncVersion must be provided if HKMetadataKeySyncIdentifier is provided.
                The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeySyncIdentifier API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeySyncVersion
 @abstract      Represents the version of the HKObject that is set by its source and is used by HealthKit to identify an
                object's version.
 @discussion    HKMetadataKeySyncVersion may not be provided if HKMetadataKeySyncIdentifier is not provided.
                The expected value type is NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeySyncVersion API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyTimeZone
 @abstract      Represents the time zone that the user was in when the HKObject was created.
 @discussion    The expected value type is an NSString compatible with NSTimeZone's +timeZoneWithName:.
 */
HK_EXTERN NSString * const HKMetadataKeyTimeZone API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));


/*!
 @constant      HKMetadataKeyDeviceName
 @abstract      Represents the name of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceName API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyDeviceManufacturerName
 @abstract      Represents the name of the manufacturer of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceManufacturerName API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyWasTakenInLab
 @abstract      Represents whether or not the reading was taken in a lab.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasTakenInLab API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyReferenceRangeLowerLimit
 @abstract      Represents the lower limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeLowerLimit API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyReferenceRangeUpperLimit
 @abstract      Represents the upper limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeUpperLimit API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyWasUserEntered
 @abstract      Represents whether or not the reading was entered by the user.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasUserEntered API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyWorkoutBrandName
 @abstract      Represents the brand name of a particular workout.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyWorkoutBrandName API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyGroupFitness
 @abstract      Represents whether or not a workout was performed as part of a group fitness class.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyGroupFitness API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyAppleFitnessPlusCatalogIdentifier
 @abstract      Contains the catalog identifier of the Fitness+ workout.
 @discussion    This key only exists if the workout was completed in Fitness+. The expected value type is an NSString containing the Fitness+ catalog identifier.
 */
HK_EXTERN NSString * const HKMetadataKeyAppleFitnessPlusCatalogIdentifier API_AVAILABLE(ios(18.2), watchos(11.2), macCatalyst(18.2), macos(15.2), visionos(2.2));

/*!
  @constant      HKMetadataKeyAppleFitnessPlusSession
  @abstract      Represents whether or not a workout is a Fitness+ workout.
  @discussion    The expected value type is an NSNumber containing a BOOL value.
  */
HK_EXTERN NSString * const HKMetadataKeyAppleFitnessPlusSession API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

/*!
 @constant      HKMetadataKeyIndoorWorkout
 @abstract      Represents whether or not a workout was performed indoors as opposed to outdoors.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyIndoorWorkout API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyCoachedWorkout
 @abstract      Represents whether or not a workout was performed with a coach or personal trainer.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyCoachedWorkout API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyWeatherCondition
 @abstract      Represents the weather condition during the sample.
 @discussion    The expected value type is an NSNumber containing an HKWeatherCondition value. This key may be set on an
                HKWorkout object to represent the overall weather condition during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherCondition API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyWeatherTemperature
 @abstract      Represents the weather temperature during the sample.
 @discussion    The expected value type is an HKQuantity expressed in a temperature unit. This key may be set on an
                HKWorkout object to represent the overall temperature during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherTemperature API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyWeatherHumidity
 @abstract      Represents the weather humidity during the sample.
 @discussion    The expected value type is an HKQuantity expressed in percent. This key may be set on an HKWorkout
                object to represent the overall humidity during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherHumidity API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeySexualActivityProtectionUsed
 @abstract      Represents whether or not protection was used during sexual activity. This can be used to track either
                protection from STIs or protection from pregnancy.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeySexualActivityProtectionUsed API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyMenstrualCycleStart
 @abstract      Indicates whether or not the sample represents the start of a menstrual cycle. This is a required
                metadata key for category samples of type HKCategoryTypeIdentifierMenstrualFlow.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyMenstrualCycleStart API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyLapLength
 @abstract      Represents the length of a lap recorded during a workout.
 @discussion    The expected value type is an HKQuantity object compatible with a length unit. This key may be set on an
                HKWorkout object to represent the length of a lap.
 */
HK_EXTERN NSString * const HKMetadataKeyLapLength API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeySwimmingLocationType
 @abstract      Represents the location type of a swimming workout.
 @discussion    The expected value type is an NSNumber containing an HKWorkoutSwimmingLocationType value. This key may
                be set on an HKWorkout object to represent the swimming location type.
 */
HK_EXTERN NSString * const HKMetadataKeySwimmingLocationType API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeySwimmingStrokeStyle
 @abstract      Represents the predominant stroke style during a lap of a swimming workout.
 @discussion    The expected value type is an NSNumber containing an HKSwimmingStrokeStyle value. This key may be set on
                an HKWorkoutEvent object with the type HKWorkoutEventTypeLap to represent the predominant style used
                during the lap.
 */
HK_EXTERN NSString * const HKMetadataKeySwimmingStrokeStyle API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyInsulinDeliveryReason
 @abstract      Represents the medical reason for the delivery of an insulin dose. This is a required metadata key for
                samples of type HKQuantityTypeIdentifierInsulinDelivery.
 @discussion    The expected value type is an NSNumber containing a HKInsulinDeliveryReason value.
 */
HK_EXTERN NSString * const HKMetadataKeyInsulinDeliveryReason API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyBloodGlucoseMealTime
 @abstract      Indicates the relative timing of a blood glucose reading to a meal.
 @discussion    This timing, as well as other factors like meal composition, can be used by medical professionals to
                determine the acceptable value range for a blood glucose reading. For use cases requiring the capture of
                precise timing and composition information, developers should record additional dietary samples, such as
                HKQuantityTypeIdentifierDietaryCarbohydrates. The expected value type is an NSNumber containing a
                HKBloodGlucoseMealTime value.
 */
HK_EXTERN NSString * const HKMetadataKeyBloodGlucoseMealTime API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyVO2MaxTestType
 @abstract      Represents the test used to create VO2 Max Sample
 @discussion    The expected value type is an NSNumber containing a HKVO2MaxTestType value.
 */
HK_EXTERN NSString * const HKMetadataKeyVO2MaxTestType API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyAverageSpeed
 @abstract      Represents the average speed for a workout segment or distance sample.
 @discussion    This represents the average speed when moving so it may not match the value of distance/time for a
 distance sample.
 
 The expected value type is an HKQuantity object compatible with a speed unit (e.g. m/s). This key may be
 set on quantity samples of type HKQuantityTypeIdentifierDistanceDownhillSnowSports or a workout segment
 representing a skiing run.
 */
HK_EXTERN NSString * const HKMetadataKeyAverageSpeed API_AVAILABLE(ios(11.2), watchos(4.2), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyMaximumSpeed
 @abstract      Represents the maximum speed for a workout segment or distance sample.
 @discussion    The expected value type is an HKQuantity object compatible with a speed unit (e.g. m/s). This key may be
 set on quantity samples of type HKQuantityTypeIdentifierDistanceDownhillSnowSports or a workout segment
 representing a skiing run.
 */
HK_EXTERN NSString * const HKMetadataKeyMaximumSpeed API_AVAILABLE(ios(11.2), watchos(4.2), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyAlpineSlopeGrade
 @abstract      Represents the grade of a ski run.
 @discussion    Alpine slope grade is measured in percent where 100% grade is a 45 degree slope.
 
 The expected value type is an HKQuantity object compatible with percent unit. This key may be set on
 quantity samples of type HKQuantityTypeIdentifierDistanceDownhillSnowSports or a workout segment
 representing a skiing run.
 */
HK_EXTERN NSString * const HKMetadataKeyAlpineSlopeGrade API_AVAILABLE(ios(11.2), watchos(4.2), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyElevationAscended
 @abstract      Represents the cumulative elevation ascent during a workout.
 @discussion    The expected value type is an HKQuantity object compatible with length unit. This key may be set on a
 workout, workout segments or distance samples.
 */
HK_EXTERN NSString * const HKMetadataKeyElevationAscended API_AVAILABLE(ios(11.2), watchos(4.2), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyElevationDescended
 @abstract      Represents the cumulative elevation descent during a workout.
 @discussion    The expected value type is an HKQuantity object compatible with length unit. This key may be set on a
 workout, workout segments or distance samples.
 */
HK_EXTERN NSString * const HKMetadataKeyElevationDescended API_AVAILABLE(ios(11.2), watchos(4.2), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyFitnessMachineDuration
 @abstract      Represents the workout duration as displayed by a GymKit connected fitness machine.
 @discussion    The expected value type is an HKQuantity object compatible with a time unit. This key may be set on an
                HKWorkout object to represent the duration of the workout as displayed by a GymKit connected fitness
                machine.
 */
HK_EXTERN NSString * const HKMetadataKeyFitnessMachineDuration API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyIndoorBikeDistance
 @abstract      Represents the distance covered during an indoor bike workout.
 @discussion    The expected value type is an HKQuantity object compatible with a length unit. This key may be set on an
                HKWorkout object to represent the distance covered during an indoor bike workout.
 */
HK_EXTERN NSString * const HKMetadataKeyIndoorBikeDistance API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyCrossTrainerDistance
 @abstract      Represents the distance covered during a cross trainer workout.
 @discussion    The expected value type is an HKQuantity object compatible with a length unit. This key may be set on an
                HKWorkout object to represent the distance covered during a cross trainer workout.
 */
HK_EXTERN NSString * const HKMetadataKeyCrossTrainerDistance API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyHeartRateEventThreshold
 @abstract      Represents the threshold heart rate that triggered a heart rate event.
 @discussion    The expected value is an HKQuantity object with a compatible unit (e.g. count/min).
                This key will be set on heart rate event samples of type HKCategoryTypeIdentifierHighHeartRateEvent and
                HKCategoryTypeIdentifierLowHeartRateEvent.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateEventThreshold API_AVAILABLE(ios(12.2), watchos(5.2), macCatalyst(13.0), macos(13.0));


/*!
 @constant      HKMetadataKeyAverageMETs
 @abstract      Represents the average METs, or Metabolic Equivalent of Task during a workout.
 @discussion    The expected value type is an HKQuantity expressed in a METs (kcal/(kg*hr)) unit. This key may be set on an
                HKWorkout object to represent the average workout intensity represented as METs over the entire workout duration.
 */
HK_EXTERN NSString * const HKMetadataKeyAverageMETs API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

/*!
 @constant      HKMetadataKeyAudioExposureLevel
 @abstract      Represents the audio level associated with an audio event.
 @discussion    The expected value is an HKQuantity whose value is the audio level
                associated with the event measured in dBASPL units.
 */
HK_EXTERN NSString * const HKMetadataKeyAudioExposureLevel API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

/*!
@constant      HKMetadataKeyAudioExposureDuration
@abstract      Represents the duration of time that is covered by audio samples.
@discussion    The expected value type is an HKQuantity object compatible with a time unit.
               This key may be set on headphone audio exposure event samples to indicate
               the duration of time that the user was actually exposed to audio through their headphones.
*/
HK_EXTERN NSString * const HKMetadataKeyAudioExposureDuration API_AVAILABLE(ios(14.2), watchos(7.1), macCatalyst(14.2), macos(13.0));

/*!
 @constant      HKMetadataKeyAppleECGAlgorithmVersion
 @abstract      Represents the ECG algorithm version that was used to generate a particular HKElectrocardiogram.
 @discussion    The expected value type is an an NSNumber containing a HKAppleECGAlgorithmVersion value.
 */
HK_EXTERN NSString * const HKMetadataKeyAppleECGAlgorithmVersion API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/*!
 @constant      HKMetadataKeyDevicePlacementSide
 @abstract      Represents the detected placement of the device during the bout of walking
 @discussion    The expected value type is an NSNumber containing a HKDevicePlacementSide value.  This key is expected to
                be written for Walking Aymmetry Percentage.
 */
HK_EXTERN NSString * const HKMetadataKeyDevicePlacementSide API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/*!
@constant      HKMetadataKeyBarometricPressure
@abstract      Represents the barometric pressure recorded at the time of a sample.
@discussion    The expected value type is an HKQuantity representing a value in units of pressure (atmospheres, pascals, millimeters of Mercury).
*/
HK_EXTERN NSString * const HKMetadataKeyBarometricPressure API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/*!
 @constant      HKMetadataKeyAppleDeviceCalibrated
 @abstract      Represents the calibration status of the devices used to generate this sample.
 @discussion    The expected value is a boolean NSNumber indicating whether the sample value was estimated using a sufficient set of device calibration data. The calibration status of a device may vary per data type. This key is read-only.
 */
HK_EXTERN NSString * const HKMetadataKeyAppleDeviceCalibrated API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/*!
@constant      HKMetadataKeyVO2MaxValue
@abstract      Represents a VO2Max value that can be associated with, for example, Cardio Fitness Events
@discussion    This key should be used to store an HKQuantity with a unit of `ml/kg·min`
*/
HK_EXTERN NSString * const HKMetadataKeyVO2MaxValue API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0));

/*!
@constant      HKMetadataKeyLowCardioFitnessEventThreshold
@abstract      Can be used to store a snapshot of the threshold used to classify VO2Max values as "low"
@discussion    This key should be used to store an HKQuantity, with a unit of `ml/kg·min`, representing the low fitness threshold.
*/
HK_EXTERN NSString * const HKMetadataKeyLowCardioFitnessEventThreshold API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0));

/*!
@constant      HKMetadataKeyDateOfEarliestDataUsedForEstimate
@abstract      Represents how far back an estimation algorithm incorporated data from.
@discussion    The expected value is an NSDate indicating the earliest date of data used to produce an estimated value for an HKSample.
*/
HK_EXTERN NSString * const HKMetadataKeyDateOfEarliestDataUsedForEstimate API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0));

/*!
 @constant      HKMetadataKeyAlgorithmVersion
 @abstract      The version of the algorithm used to generate the sample.
 @discussion    The key for an NSNumber containing an NSInteger indicating the version of the algorithm used to generate the sample.
 */
HK_EXTERN NSString * const HKMetadataKeyAlgorithmVersion API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0));

/*!
 @constant      HKMetadataKeySWOLFScore
 @abstract      Represents sum of strokes per length and time for the length. Calculated for each lap event and segment event during swimming workout.
 @discussion    The expected value type is an NSNumber containing a score. This key may be set on an HKWorkout object to represent the SWOLF Score during the whole workout.
 */
HK_EXTERN NSString * const HKMetadataKeySWOLFScore API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyQuantityClampedToLowerBound
 @abstract      Indicates the quantity was clamped to a lower bound.
 @discussion    Value is a BOOL indicating whether or not the quantity value in the sample has been clamped to some lower bound
 */
HK_EXTERN NSString * const HKMetadataKeyQuantityClampedToLowerBound API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyQuantityClampedToUpperBound
 @abstract      Indicates the quantity was clamped to an upper bound.
 @discussion    Value is a BOOL indicating whether or not the quantity value in the sample has been clamped to some upper bound
 */
HK_EXTERN NSString * const HKMetadataKeyQuantityClampedToUpperBound API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyGlassesPrescriptionDescription
 @abstract      Represents the description that may be associated with a HKGlassesPrescription.
 @discussion    Glasses are often customized for different purposes like reading or distance. Prescriptions received by an eye care professional can provide different ocular functions.
                Users may also customize their glasses for different scenarios. The value of the metadata is a NSString that describes the purpose of a HKGlassesPrescription.
  */
 HK_EXTERN NSString * const HKMetadataKeyGlassesPrescriptionDescription API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @constant      HKMetadataKeyWaterSalinity
 @abstract      Represents the water salinity for an underwater depth or water temperature sample.
 @discussion    The expected value type is an NSNumber containing a HKWaterSalinity value.
 */
HK_EXTERN NSString * const HKMetadataKeyWaterSalinity API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

/*!
 @constant      HKMetadataKeyHeadphoneGain
 @abstract      Represents the headphone gain associated with a Headphone audio exposure event.
 @discussion    The expected value is an HKQuantity whose value is the gain
                associated with the event measured in decibels in A-weighted Sound Pressure Level units.
 */
HK_EXTERN NSString * const HKMetadataKeyHeadphoneGain API_AVAILABLE(ios(16.4), watchos(9.4), macCatalyst(16.4), macos(13.3));

/*!
 @constant      HKMetadataKeyCyclingFunctionalThresholdPowerTestType
 @abstract      Represents the test used to determine a Cycling Functional Threshold Power value.
 @discussion    The expected value type is an NSNumber containing a HKCyclingFunctionalThresholdPowerTestType value.
 */
HK_EXTERN NSString * const HKMetadataKeyCyclingFunctionalThresholdPowerTestType API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

/*!
 @constant      HKMetadataKeyActivityType
 @abstract      Represents the activity type related to the sample
 @discussion    The expected value type is an NSNumber containing a HKWorkoutActivityType value.
 */
HK_EXTERN NSString * const HKMetadataKeyActivityType API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

/*!
 @constant      HKMetadataKeyPhysicalEffortEstimationType
 @abstract      Represents the estimation type used to create the Physical Effort Sample
 @discussion    The expected value type is an NSNumber containing a HKPhysicalEffortEstimationType value.
 */
HK_EXTERN NSString * const HKMetadataKeyPhysicalEffortEstimationType API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

/*!
 @constant      HKMetadataKeyMaximumLightIntensity
 @abstract      Represents maximum intensity of light for an outdoor time sample.
 @discussion    The expected value type is an HKQuantity expressed in HKUnit Lux.
 */
HK_EXTERN NSString * const HKMetadataKeyMaximumLightIntensity API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0));

NS_ASSUME_NONNULL_END
