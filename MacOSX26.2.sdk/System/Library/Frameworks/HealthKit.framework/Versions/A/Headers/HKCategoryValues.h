//
//  HKCategoryValues.h
//  HealthKit
//
//  Copyright © 2022-2025 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <HealthKit/HKDefines.h>



NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKCategoryValue
 @abstract      This category value is to be used for types which don't have a specific value defined.
 */
typedef NS_ENUM(NSInteger, HKCategoryValue) {
    HKCategoryValueNotApplicable = 0,
} API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKCategoryValueAppetiteChanges
 @abstract      Set of values to indicate the direction of appetite changes.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueAppetiteChanges) {
    HKCategoryValueAppetiteChangesUnspecified = 0,
    HKCategoryValueAppetiteChangesNoChange = 1,
    HKCategoryValueAppetiteChangesDecreased = 2,
    HKCategoryValueAppetiteChangesIncreased = 3,
} API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0));

/*!
 @enum          HKCategoryValueAppleStandHour
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryTypeIdentifierAppleStandHour
                type.

 @constant      HKCategoryValueAppleStandHourStood  The user stood up and moved a little for at least one minute during
                                                    the sample.
 @constant      HKCategoryValueAppleStandHourIdle   The user did not stand up and move a little for at least one
                                                    continuous minute during the sample.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueAppleStandHour) {
    HKCategoryValueAppleStandHourStood = 0,
    HKCategoryValueAppleStandHourIdle = 1,
} API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKCategoryValueAppleWalkingSteadinessEvent
 @abstract      Set of values that may be used for HKCategorySamples with the
                HKCategoryTypeIdentifierAppleWalkingSteadinessEvent type.

 @constant      HKCategoryValueAppleWalkingSteadinessEventInitialLow        This constant defines Apple Walking
                                                                            Steadiness events associated with the user's
                                                                            walking steadiness being low.
 @constant      HKCategoryValueAppleWalkingSteadinessEventInitialVeryLow    This constant defines Apple Walking
                                                                            Steadiness events associated with the user's
                                                                            walking steadiness being very low.
 @constant      HKCategoryValueAppleWalkingSteadinessEventRepeatLow         This constant defines Apple Walking
                                                                            Steadiness events associated with the user's
                                                                            walking steadiness remaining low over a
                                                                            significant time period.
 @constant      HKCategoryValueAppleWalkingSteadinessEventRepeatVeryLow     This constant defines Apple Walking
                                                                            Steadiness events associated with the user's
                                                                            walking steadiness remaining very low over a
                                                                            significant time period.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueAppleWalkingSteadinessEvent) {
    HKCategoryValueAppleWalkingSteadinessEventInitialLow = 1,
    HKCategoryValueAppleWalkingSteadinessEventInitialVeryLow = 2,
    HKCategoryValueAppleWalkingSteadinessEventRepeatLow = 3,
    HKCategoryValueAppleWalkingSteadinessEventRepeatVeryLow = 4,
} API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0));

/*!
 @enum          HKCategoryValueCervicalMucusQuality
 @abstract      Set of values that may be used for HKCategorySamples with the
                HKCategoryTypeIdentifierCervicalMucusQuality type.
 @discussion    These cervical mucus quality values are ordered from least-fertile (Dry) to most-fertile (EggWhite).
 */
typedef NS_ENUM(NSInteger, HKCategoryValueCervicalMucusQuality) {
    HKCategoryValueCervicalMucusQualityDry = 1,
    HKCategoryValueCervicalMucusQualitySticky = 2,
    HKCategoryValueCervicalMucusQualityCreamy = 3,
    HKCategoryValueCervicalMucusQualityWatery = 4,
    HKCategoryValueCervicalMucusQualityEggWhite = 5,
} API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKCategoryValueContraceptive
 @abstract      Set of values to indicate the type of contraceptive.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueContraceptive) {
    HKCategoryValueContraceptiveUnspecified = 1,
    HKCategoryValueContraceptiveImplant = 2,
    HKCategoryValueContraceptiveInjection = 3,
    HKCategoryValueContraceptiveIntrauterineDevice = 4,
    HKCategoryValueContraceptiveIntravaginalRing = 5,
    HKCategoryValueContraceptiveOral = 6,
    HKCategoryValueContraceptivePatch = 7,
} API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0));

/*!
 @enum          HKCategoryValueEnvironmentalAudioExposureEvent
 @abstract      Specifies the kind of environmental audio exposure event associated with the sample.

 @constant      HKCategoryValueEnvironmentalAudioExposureEventMomentaryLimit    This constant defines environmental
                                                                                events associated with the user being
                                                                                exposed to a loud environment during a
                                                                                short timespan.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueEnvironmentalAudioExposureEvent) {
    HKCategoryValueEnvironmentalAudioExposureEventMomentaryLimit = 1,
} API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/*!
 @enum          HKCategoryValueHeadphoneAudioExposureEvent
 @abstract      Specifies the kind of headphone audio exposure event associated with the sample.

 @constant      HKCategoryValueHeadphoneAudioExposureEventSevenDayLimit     This constant defines headphone events
                                                                            associated with the user being exposed to
                                                                            significant audio levels throught a
                                                                            seven-day period.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueHeadphoneAudioExposureEvent) {
    HKCategoryValueHeadphoneAudioExposureEventSevenDayLimit = 1,
} API_AVAILABLE(ios(14.2), watchos(7.1), macCatalyst(14.2), macos(13.0));

/*!
 @enum          HKCategoryValueLowCardioFitnessEvent
 @abstract      Specifies the type of cardio fitness event.

 @constant      HKCategoryValueLowCardioFitnessEventLowFitness  This constant defines an event where a VO2Max
                                                                measurement was recorded that falls into the "Low"
                                                                fitness classification
 */
typedef NS_ENUM(NSInteger, HKCategoryValueLowCardioFitnessEvent) {
    HKCategoryValueLowCardioFitnessEventLowFitness = 1,
} API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0));

/*!
 @enum          HKCategoryValueMenstrualFlow
 @abstract      Set of values to indicate the type of menstrual flow.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueMenstrualFlow) {
    HKCategoryValueMenstrualFlowUnspecified = 1,
    HKCategoryValueMenstrualFlowLight = 2,
    HKCategoryValueMenstrualFlowMedium = 3,
    HKCategoryValueMenstrualFlowHeavy = 4,
    HKCategoryValueMenstrualFlowNone API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueVaginalBleeding", ios(12.0, 18.0), watchos(5.0, 11.0), macCatalyst(13.0, 18.0), macos(13.0, 15.0), visionos(1.0, 2.0)) = 5,
} API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueVaginalBleeding", ios(9.0, 18.0), watchos(2.0, 11.0), macCatalyst(13.0, 18.0), macos(13.0, 15.0), visionos(1.0, 2.0));

/*!
 @enum          HKCategoryValueOvulationTestResult
 @abstract      Set of values that may be used for HKCategorySamples with the
                HKCategoryTypeIdentifierOvulationTestResult type.
 @discussion    This category value tracks the result of a home ovulation test that use surges in hormone levels to
                indicate fertility.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueOvulationTestResult) {
    HKCategoryValueOvulationTestResultNegative = 1,
    HKCategoryValueOvulationTestResultLuteinizingHormoneSurge API_AVAILABLE(ios(13.0), watchos(6.0)) = 2,
    HKCategoryValueOvulationTestResultPositive API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueOvulationTestResultLuteinizingHormoneSurge", ios(9.0, 13.0), watchos(2.0, 6.0)) = HKCategoryValueOvulationTestResultLuteinizingHormoneSurge,
    HKCategoryValueOvulationTestResultIndeterminate = 3,
    HKCategoryValueOvulationTestResultEstrogenSurge API_AVAILABLE(ios(13.0), watchos(6.0)) = 4,
} API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKCategoryValuePregnancyTestResult
 @abstract      Set of values that may be used for HKCategorySamples with the
                HKCategoryTypeIdentifierPregnancyTestResult type.
 @discussion    This category value tracks the result of a home pregnancy test that checks for presence of the human
                chorionic gonadotrophin (hCG) hormone in urine to confirm pregnancy.
 */
typedef NS_ENUM(NSInteger, HKCategoryValuePregnancyTestResult) {
    HKCategoryValuePregnancyTestResultNegative = 1,
    HKCategoryValuePregnancyTestResultPositive = 2,
    HKCategoryValuePregnancyTestResultIndeterminate = 3,
} API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0));

/*!
 @enum          HKCategoryValuePresence
 @abstract      Set of values to indicate whether a data type is present or not.
 */
typedef NS_ENUM(NSInteger, HKCategoryValuePresence) {
    HKCategoryValuePresencePresent = 0,
    HKCategoryValuePresenceNotPresent = 1,
} API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0));

/*!
 @enum          HKCategoryValueProgesteroneTestResult
 @abstract      Set of values that may be used for HKCategorySamples with the
                HKCategoryTypeIdentifierProgesteroneTestResult type.
 @discussion    This category value tracks the result of a home ovulation confirmation test that use surges in hormone
                levels to confirm if ovulation has occurred.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueProgesteroneTestResult) {
    HKCategoryValueProgesteroneTestResultNegative = 1,
    HKCategoryValueProgesteroneTestResultPositive = 2,
    HKCategoryValueProgesteroneTestResultIndeterminate = 3,
} API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0));

/*!
 @enum          HKCategoryValueSeverity
 @abstract      Set of values to indicate the severity of a symptom.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueSeverity) {
    HKCategoryValueSeverityUnspecified = 0,
    HKCategoryValueSeverityNotPresent = 1,
    HKCategoryValueSeverityMild = 2,
    HKCategoryValueSeverityModerate = 3,
    HKCategoryValueSeveritySevere = 4,
} API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0));

/*!
 @enum          HKCategoryValueSleepAnalysis
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryTypeIdentifierSleepAnalysis
                type.
 @discussion    To represent the user being both in bed and asleep, use two or more samples with overlapping times. By
                comparing the start and end times of these samples, it is possible to calculate a number of secondary
                statistics:
                1) The amount of time it took for the user to fall asleep
                2) The percentage of time in bed that the user actually spent sleeping,
                3) The number of times the user woke while in bed
                4) The total amount of time spent both in bed and asleep.

 @constant      HKCategoryValueSleepAnalysisInBed               The user is in bed.
 @constant      HKCategoryValueSleepAnalysisAsleepUnspecified   The user is asleep and no specific stage is specified.
 @constant      HKCategoryValueSleepAnalysisAwake               The user is awake.
 @constant      HKCategoryValueSleepAnalysisAsleepCore          Corresponds to Stages 1 and 2 of AASM scoring model.
 @constant      HKCategoryValueSleepAnalysisAsleepDeep          Corresponds to Stage 3 of AASM scoring model.
 @constant      HKCategoryValueSleepAnalysisAsleepREM           Corresponds to REM stage of AASM scoring model.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueSleepAnalysis) {
    HKCategoryValueSleepAnalysisInBed = 0,
    HKCategoryValueSleepAnalysisAsleepUnspecified API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0)) = 1,
    HKCategoryValueSleepAnalysisAsleep API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueSleepAnalysisAsleepUnspecified", ios(8.0, 16.0), watchos(2.0, 9.0), macCatalyst(13.0, 16.0), macos(13.0, 13.0)) = HKCategoryValueSleepAnalysisAsleepUnspecified,
    HKCategoryValueSleepAnalysisAwake API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 2,
    HKCategoryValueSleepAnalysisAsleepCore API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0)) = 3,
    HKCategoryValueSleepAnalysisAsleepDeep API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0)) = 4,
    HKCategoryValueSleepAnalysisAsleepREM API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0)) = 5,
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum          HKCategoryValueVaginalBleeding
 @abstract      Set of values to indicate the type of bleeding.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueVaginalBleeding) {
    HKCategoryValueVaginalBleedingUnspecified = 1,
    HKCategoryValueVaginalBleedingLight = 2,
    HKCategoryValueVaginalBleedingMedium = 3,
    HKCategoryValueVaginalBleedingHeavy = 4,
    HKCategoryValueVaginalBleedingNone = 5,
} API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

// MARK: Deprecated

/*!
@enum          HKCategoryValueAudioExposureEvent
@abstract      Specifies the kind of audio exposure event associated with the sample.
*/
typedef NS_ENUM(NSInteger, HKCategoryValueAudioExposureEvent) {
    HKCategoryValueAudioExposureEventLoudEnvironment API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueEnvironmentalAudioExposureEventMomentaryLimit", ios(13.0, 14.0), watchos(6.0, 7.0)) = 1,
} API_DEPRECATED_WITH_REPLACEMENT("HKCategoryValueEnvironmentalAudioExposureEvent", ios(13.0, 14.0), watchos(6.0, 7.0));

NS_ASSUME_NONNULL_END
