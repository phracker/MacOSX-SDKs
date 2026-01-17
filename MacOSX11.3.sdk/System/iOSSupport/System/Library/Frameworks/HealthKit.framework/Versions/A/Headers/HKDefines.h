//
//  HKDefines.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if !defined(__cplusplus)
#define HK_EXTERN extern __attribute__((visibility("default")))
#else
#define HK_EXTERN extern "C" __attribute__((visibility("default")))
#endif

HK_EXTERN NSString * const HKErrorDomain API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum      HKErrorCode

 @constant  HKNoError                           No error.
 @constant  HKErrorHealthDataUnavailable        HealthKit is not available on this device.
 @constant  HKErrorHealthDataRestricted         HealthKit is restricted on this device.
 @constant  HKErrorInvalidArgument              An invalid argument was provided to the API.
 @constant  HKErrorAuthorizationDenied          The application is not authorized to perform the requested operation.
 @constant  HKErrorAuthorizationNotDetermined   The user has not yet chosen whether the application is authorized to
                                                perform the requested operation.
 @constant  HKErrorDatabaseInaccessible         Protected health data is inaccessible because the device is locked.
 @constant  HKErrorUserCanceled                 The user canceled the operation.
 @constant  HKErrorAnotherWorkoutSessionStarted Another workout session was started by this or another application.
 @constant  HKErrorUserExitedWorkoutSession     User exited the application while a workout session was running.
 @constant  HKErrorRequiredAuthorizationDenied  The user has not granted the application authorization to access
                                                required data types.
 @constant  HKErrorNoData                       No data is available for the requested query and predicate, and so the
                                                query's result could not be meaningfully computed.
 */
typedef NS_ENUM(NSInteger, HKErrorCode) {
    HKNoError = 0,
    HKErrorHealthDataUnavailable,
    HKErrorHealthDataRestricted,
    HKErrorInvalidArgument,
    HKErrorAuthorizationDenied,
    HKErrorAuthorizationNotDetermined,
    HKErrorDatabaseInaccessible,
    HKErrorUserCanceled,
    HKErrorAnotherWorkoutSessionStarted     API_AVAILABLE(ios(9.0), watchos(2.0)),
    HKErrorUserExitedWorkoutSession         API_AVAILABLE(ios(9.0), watchos(2.0)),
    HKErrorRequiredAuthorizationDenied      API_AVAILABLE(ios(12.0), watchos(5.0)),
    HKErrorNoData                           API_AVAILABLE(ios(14.0), watchos(7.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum      HKUpdateFrequency
 */
typedef NS_ENUM(NSInteger, HKUpdateFrequency) {
    HKUpdateFrequencyImmediate = 1,
    HKUpdateFrequencyHourly,
    HKUpdateFrequencyDaily,
    HKUpdateFrequencyWeekly,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum      HKAuthorizationStatus
 @abstract  This enumerated type is used to indicate the currently granted authorization status for a specific
            HKObjectType.

 @constant  HKAuthorizationStatusNotDetermined      The user has not yet made a choice regarding whether this
                                                    application may save objects of the specified type.
 @constant  HKAuthorizationStatusSharingDenied      This application is not allowed to save objects of the specified type.
 @constant  HKAuthorizationStatusSharingAuthorized  This application is authorized to save objects of the specified type.
 */
typedef NS_ENUM(NSInteger, HKAuthorizationStatus) {
    HKAuthorizationStatusNotDetermined = 0,
    HKAuthorizationStatusSharingDenied,
    HKAuthorizationStatusSharingAuthorized,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum      HKAuthorizationRequestStatus
 @abstract  This enumerated type is used to indicate whether it is necessary to request authorization from the user.

 @constant  HKAuthorizationRequestStatusUnknown         The authorization request status could not be determined because
                                                        an error occurred.
 @constant  HKAuthorizationRequestStatusShouldRequest   The application should request authorization from the user.
 @constant  HKAuthorizationRequestStatusUnnecessary     Requesting authorization from the user is unnecessary.
 */
typedef NS_ENUM(NSInteger, HKAuthorizationRequestStatus) {
    HKAuthorizationRequestStatusUnknown = 0,
    HKAuthorizationRequestStatusShouldRequest,
    HKAuthorizationRequestStatusUnnecessary,
} API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @enum       HKBiologicalSex
 @abstract   This enumerated type is used to represent the biological sex of an individual.
 */
typedef NS_ENUM(NSInteger, HKBiologicalSex) {
    HKBiologicalSexNotSet = 0,
    HKBiologicalSexFemale,
    HKBiologicalSexMale,
    HKBiologicalSexOther API_AVAILABLE(ios(8.2), watchos(2.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum       HKBloodType
 @abstract   This enumerated type is used to represent the blood type of an individual.
 */
typedef NS_ENUM(NSInteger, HKBloodType) {
    HKBloodTypeNotSet = 0,
    HKBloodTypeAPositive,
    HKBloodTypeANegative,
    HKBloodTypeBPositive,
    HKBloodTypeBNegative,
    HKBloodTypeABPositive,
    HKBloodTypeABNegative,
    HKBloodTypeOPositive,
    HKBloodTypeONegative,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum          HKCategoryValueSleepAnalysis
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryTypeIdentifierSleepAnalysis type.
 @discussion    To represent the user being both in bed and asleep, use two or more samples with overlapping times. By comparing the
                start and end times of these samples, it is possible to calculate a number of secondary statistics:
                1) The amount of time it took for the user to fall asleep
                2) The percentage of time in bed that the user actually spent sleeping,
                3) The number of times the user woke while in bed
                4) The total amount of time spent both in bed and asleep.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueSleepAnalysis) {
    HKCategoryValueSleepAnalysisInBed,
    HKCategoryValueSleepAnalysisAsleep,
    HKCategoryValueSleepAnalysisAwake API_AVAILABLE(ios(10.0), watchos(3.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0));


/*!
 @enum          HKCategoryValueAppleStandHour
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryTypeIdentifierAppleStandHour type.

 @constant      HKCategoryValueAppleStandHourStood  The user stood up and moved a little for at least one minute during
                                                    the sample.
 @constant      HKCategoryValueAppleStandHourIdle   The user did not stand up and move a little for at least one
                                                    continuous minute during the sample.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueAppleStandHour) {
    HKCategoryValueAppleStandHourStood = 0,
    HKCategoryValueAppleStandHourIdle,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKFitzpatrickSkinType
 @abstract      This enumerated type is used to represent the skin type of an individual based on the Fitzpatrick scale.
 @discussion    The Fitzpatrick scale is a numerical classification for skin color based on the skin's response to sun
                exposure in terms of the degree of burning and tanning.

 @constant      HKFitzpatrickSkinTypeI      Pale white skin that always burns easily in the sun and never tans.
 @constant      HKFitzpatrickSkinTypeII     White skin that burns easily and tans minimally.
 @constant      HKFitzpatrickSkinTypeIII    White to light brown skin that burns moderately and tans uniformly.
 @constant      HKFitzpatrickSkinTypeIV     Beige-olive, lightly tanned skin that burns minimally and tans moderately.
 @constant      HKFitzpatrickSkinTypeV      Brown skin that rarely burns and tans profusely.
 @constant      HKFitzpatrickSkinTypeVI     Dark brown to black skin that never burns and tans profusely.
 */
typedef NS_ENUM(NSInteger, HKFitzpatrickSkinType) {
    HKFitzpatrickSkinTypeNotSet = 0,
    HKFitzpatrickSkinTypeI,
    HKFitzpatrickSkinTypeII,
    HKFitzpatrickSkinTypeIII,
    HKFitzpatrickSkinTypeIV,
    HKFitzpatrickSkinTypeV,
    HKFitzpatrickSkinTypeVI,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKWheelchairUse
 @abstract      This enumerated type is used to represent whether the user uses a wheelchair.

 @constant      HKWheelchairUseNo      The user does not use a wheelchair.
 @constant      HKWheelchairUseYes     The user does use a wheelchair.
 */
typedef NS_ENUM(NSInteger, HKWheelchairUse) {
    HKWheelchairUseNotSet = 0,
    HKWheelchairUseNo,
    HKWheelchairUseYes,
} API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @enum          HKCategoryValueCervicalMucusQuality
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryValueCervicalMucusQuality type.
 @discussion    These cervical mucus quality values are ordered from least-fertile (Dry) to most-fertile (EggWhite).
 */
typedef NS_ENUM(NSInteger, HKCategoryValueCervicalMucusQuality) {
    HKCategoryValueCervicalMucusQualityDry = 1,
    HKCategoryValueCervicalMucusQualitySticky,
    HKCategoryValueCervicalMucusQualityCreamy,
    HKCategoryValueCervicalMucusQualityWatery,
    HKCategoryValueCervicalMucusQualityEggWhite,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKCategoryValueOvulationTestResult
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryValueOvulationTestResult type.
 @discussion    This category value tracks the result of a home ovulation test that use surges in hormone levels to
                indicate fertility.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueOvulationTestResult) {
    HKCategoryValueOvulationTestResultNegative = 1,
    HKCategoryValueOvulationTestResultLuteinizingHormoneSurge API_AVAILABLE(ios(13.0), watchos(6.0)) = 2,
    HKCategoryValueOvulationTestResultPositive API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueOvulationTestResultLuteinizingHormoneSurge", ios(9.0, 13.0), watchos(2.0, 6.0)) = HKCategoryValueOvulationTestResultLuteinizingHormoneSurge,
    HKCategoryValueOvulationTestResultIndeterminate = 3,
    HKCategoryValueOvulationTestResultEstrogenSurge API_AVAILABLE(ios(13.0), watchos(6.0)) = 4,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKCategoryValueMenstrualFlow
 @abstract      Set of values to indicate the type of menstrual flow.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueMenstrualFlow) {
    HKCategoryValueMenstrualFlowUnspecified = 1,
    HKCategoryValueMenstrualFlowLight,
    HKCategoryValueMenstrualFlowMedium,
    HKCategoryValueMenstrualFlowHeavy,
    HKCategoryValueMenstrualFlowNone API_AVAILABLE(ios(12.0), watchos(5.0)),
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKCategoryValue
 @abstract      This category value is to be used for types which don't have a specific value defined.
 */
typedef NS_ENUM(NSInteger, HKCategoryValue) {
    HKCategoryValueNotApplicable = 0,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKCategoryValueAudioExposureEvent
 @abstract      Specifies the kind of audio exposure event associated with the sample.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueAudioExposureEvent) {
    HKCategoryValueAudioExposureEventLoudEnvironment API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueEnvironmentalAudioExposureEventMomentaryLimit", ios(13.0, 14.0), watchos(6.0, 7.0)) = 1,
} API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueEnvironmentalAudioExposureEvent", ios(13.0, 14.0), watchos(6.0, 7.0));

/*!
 @enum          HKCategoryValueEnvironmentalAudioExposureEvent
 @abstract      Specifies the kind of environmental audio exposure event associated with the sample.

 @constant      HKCategoryValueEnvironmentalAudioExposureEventMomentaryLimit          This constant defines environmental events associated
                with the user being exposed to a loud environment during a short timespan.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueEnvironmentalAudioExposureEvent) {
    HKCategoryValueEnvironmentalAudioExposureEventMomentaryLimit = 1,
} API_AVAILABLE(ios(14.0), watchos(7.0));

/*!
 @enum          HKCategoryValueContraceptive
 @abstract      Set of values to indicate the type of contraceptive.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueContraceptive) {
    HKCategoryValueContraceptiveUnspecified = 1,
    HKCategoryValueContraceptiveImplant,
    HKCategoryValueContraceptiveInjection,
    HKCategoryValueContraceptiveIntrauterineDevice,
    HKCategoryValueContraceptiveIntravaginalRing,
    HKCategoryValueContraceptiveOral,
    HKCategoryValueContraceptivePatch,
} API_AVAILABLE(ios(14.3), watchos(7.2));

/*!
 @enum          HKCategoryValueSeverity
 @abstract      Set of values to indicate the severity of a symptom.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueSeverity) {
    HKCategoryValueSeverityUnspecified = 0,
    HKCategoryValueSeverityNotPresent,
    HKCategoryValueSeverityMild,
    HKCategoryValueSeverityModerate,
    HKCategoryValueSeveritySevere,
} API_AVAILABLE(ios(13.6), watchos(7.0));

/*!
 @enum          HKCategoryValueAppetiteChanges
 @abstract      Set of values to indicate the direction of appetite changes.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueAppetiteChanges) {
    HKCategoryValueAppetiteChangesUnspecified = 0,
    HKCategoryValueAppetiteChangesNoChange,
    HKCategoryValueAppetiteChangesDecreased,
    HKCategoryValueAppetiteChangesIncreased,
} API_AVAILABLE(ios(13.6), watchos(7.0));

/*!
 @enum          HKCategoryValuePresence
 @abstract      Set of values to indicate whether a data type is present or not.
 */
typedef NS_ENUM(NSInteger, HKCategoryValuePresence) {
    HKCategoryValuePresencePresent = 0,
    HKCategoryValuePresenceNotPresent,
} API_AVAILABLE(ios(13.6), watchos(7.0));

/*!
@enum          HKCategoryValueHeadphoneAudioExposureEvent
@abstract      Specifies the kind of headphone exposure event associated with the sample.
@constant      HKCategoryValueHeadphoneAudioExposureEventSevenDayLimit     This constant defines headphone events associated with the user being exposed to significant audio levels throught a seven-day period.
*/
typedef NS_ENUM(NSInteger, HKCategoryValueHeadphoneAudioExposureEvent) {
    HKCategoryValueHeadphoneAudioExposureEventSevenDayLimit = 1
} API_AVAILABLE(ios(14.2), watchos(7.1));

/*!
 @enum          HKCategoryValueLowCardioFitnessEvent
 @abstract      Specifies the type of cardio fitness event.

 @constant      HKCategoryValueLowCardioFitnessEventLowFitness       This constant defines an event where a VO2Max measurement was recorded that falls into the "Low" fitness classification
  */
typedef NS_ENUM(NSInteger, HKCategoryValueLowCardioFitnessEvent) {
    HKCategoryValueLowCardioFitnessEventLowFitness = 1,
} API_AVAILABLE(ios(14.3), watchos(7.2));

/*!
 @enum          HKActivityMoveMode
 @abstract      This enumerated type is used to represent the activity mode for the user's move ring.
 @constant      HKActivityMoveModeActiveEnergy     User's move ring is updated from Active Energy Burned
 @constant      HKActivityMoveModeAppleMoveTime    User's move ring is updated from Apple Move Time
 */
typedef NS_ENUM(NSInteger, HKActivityMoveMode) {
    HKActivityMoveModeActiveEnergy = 1,
    HKActivityMoveModeAppleMoveTime = 2,
} API_AVAILABLE(ios(14.0), watchos(7.0));

NS_ASSUME_NONNULL_END
