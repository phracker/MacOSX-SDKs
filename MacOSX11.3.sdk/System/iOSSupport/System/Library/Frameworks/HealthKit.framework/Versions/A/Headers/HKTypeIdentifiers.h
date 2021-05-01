//
//  HKTypeIdentifiers
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <objc/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

/*--------------------------------*/
/*   HKQuantityType Identifiers   */
/*--------------------------------*/

typedef NSString * HKQuantityTypeIdentifier NS_STRING_ENUM;

// Body Measurements
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyMassIndex API_AVAILABLE(ios(8.0), watchos(2.0));                       // Scalar(Count),               Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyFatPercentage API_AVAILABLE(ios(8.0), watchos(2.0));                   // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeight API_AVAILABLE(ios(8.0), watchos(2.0));                              // Length,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyMass API_AVAILABLE(ios(8.0), watchos(2.0));                            // Mass,                        Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierLeanBodyMass API_AVAILABLE(ios(8.0), watchos(2.0));                        // Mass,                        Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWaistCircumference API_AVAILABLE(ios(11.0), watchos(4.0));                 // Length,                      Discrete

// Fitness
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierStepCount API_AVAILABLE(ios(8.0), watchos(2.0));                           // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceWalkingRunning API_AVAILABLE(ios(8.0), watchos(2.0));              // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceCycling API_AVAILABLE(ios(8.0), watchos(2.0));                     // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceWheelchair API_AVAILABLE(ios(10.0), watchos(3.0));                 // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBasalEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0));                   // Energy,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierActiveEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0));                  // Energy,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierFlightsClimbed API_AVAILABLE(ios(8.0), watchos(2.0));                      // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNikeFuel API_AVAILABLE(ios(8.0), watchos(2.0));                            // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleExerciseTime API_AVAILABLE(ios(9.3), watchos(2.2));                   // Time                         Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPushCount API_AVAILABLE(ios(10.0), watchos(3.0));                          // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceSwimming API_AVAILABLE(ios(10.0), watchos(3.0));                   // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0));                // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierVO2Max API_AVAILABLE(ios(11.0), watchos(4.0));                             // ml/(kg*min)                  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceDownhillSnowSports API_AVAILABLE(ios(11.2), watchos(4.2));         // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleStandTime API_AVAILABLE(ios(13.0), watchos(6.0));                     // Time,                        Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingSpeed API_AVAILABLE(ios(14.0), watchos(7.0));                       // m/s,                         Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingDoubleSupportPercentage API_AVAILABLE(ios(14.0), watchos(7.0));     // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingAsymmetryPercentage API_AVAILABLE(ios(14.0), watchos(7.0));         // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingStepLength API_AVAILABLE(ios(14.0), watchos(7.0));                  // Length,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierSixMinuteWalkTestDistance API_AVAILABLE(ios(14.0), watchos(7.0));          // Length,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierStairAscentSpeed API_AVAILABLE(ios(14.0), watchos(7.0));                   // m/s,                         Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierStairDescentSpeed API_AVAILABLE(ios(14.0), watchos(7.0));                  // m/s),                        Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleMoveTime API_AVAILABLE(ios(14.5), watchos(7.4));                      // Time,                        Cumulative

// Vitals
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeartRate API_AVAILABLE(ios(8.0), watchos(2.0));                           // Scalar(Count)/Time,          Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyTemperature API_AVAILABLE(ios(8.0), watchos(2.0));                     // Temperature,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBasalBodyTemperature API_AVAILABLE(ios(9.0), watchos(2.0));                // Basal Body Temperature,      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodPressureSystolic API_AVAILABLE(ios(8.0), watchos(2.0));               // Pressure,                    Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodPressureDiastolic API_AVAILABLE(ios(8.0), watchos(2.0));              // Pressure,                    Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRespiratoryRate API_AVAILABLE(ios(8.0), watchos(2.0));                     // Scalar(Count)/Time,          Discrete
// Beats per minute estimate of a user's lowest heart rate while at rest
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRestingHeartRate API_AVAILABLE(ios(11.0), watchos(4.0));                   // Scalar(Count)/Time,          Discrete
// Average heartbeats per minute captured by an Apple Watch while a user is walking
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingHeartRateAverage API_AVAILABLE(ios(11.0), watchos(4.0));            // Scalar(Count)/Time,          Discrete
// The standard deviation of heart beat-to-beat intevals (Standard Deviation of Normal to Normal)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeartRateVariabilitySDNN API_AVAILABLE(ios(11.0), watchos(4.0));           // Time (ms),                   Discrete

// Results
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierOxygenSaturation API_AVAILABLE(ios(8.0), watchos(2.0));                    // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPeripheralPerfusionIndex API_AVAILABLE(ios(8.0), watchos(2.0));            // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodGlucose API_AVAILABLE(ios(8.0), watchos(2.0));                        // Mass/Volume,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNumberOfTimesFallen API_AVAILABLE(ios(8.0), watchos(2.0));                 // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierElectrodermalActivity API_AVAILABLE(ios(8.0), watchos(2.0));               // Conductance,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierInhalerUsage API_AVAILABLE(ios(8.0), watchos(2.0));                        // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierInsulinDelivery API_AVAILABLE(ios(11.0), watchos(4.0));                    // Pharmacology (IU)            Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodAlcoholContent API_AVAILABLE(ios(8.0), watchos(2.0));                 // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierForcedVitalCapacity API_AVAILABLE(ios(8.0), watchos(2.0));                 // Volume,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierForcedExpiratoryVolume1 API_AVAILABLE(ios(8.0), watchos(2.0));             // Volume,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPeakExpiratoryFlowRate API_AVAILABLE(ios(8.0), watchos(2.0));              // Volume/Time,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierEnvironmentalAudioExposure API_AVAILABLE(ios(13.0), watchos(6.0));         // Pressure,                    DiscreteEquivalentContinuousLevel
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeadphoneAudioExposure API_AVAILABLE(ios(13.0), watchos(6.0));             // Pressure,                    DiscreteEquivalentContinuousLevel

// Nutrition
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatTotal API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatPolyunsaturated API_AVAILABLE(ios(8.0), watchos(2.0));           // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatMonounsaturated API_AVAILABLE(ios(8.0), watchos(2.0));           // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatSaturated API_AVAILABLE(ios(8.0), watchos(2.0));                 // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCholesterol API_AVAILABLE(ios(8.0), watchos(2.0));                  // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySodium API_AVAILABLE(ios(8.0), watchos(2.0));                       // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCarbohydrates API_AVAILABLE(ios(8.0), watchos(2.0));                // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFiber API_AVAILABLE(ios(8.0), watchos(2.0));                        // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySugar API_AVAILABLE(ios(8.0), watchos(2.0));                        // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryEnergyConsumed API_AVAILABLE(ios(8.0), watchos(2.0));               // Energy, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryProtein API_AVAILABLE(ios(8.0), watchos(2.0));                      // Mass,   Cumulative

HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminA API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminB6 API_AVAILABLE(ios(8.0), watchos(2.0));                    // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminB12 API_AVAILABLE(ios(8.0), watchos(2.0));                   // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminC API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminD API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminE API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminK API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCalcium API_AVAILABLE(ios(8.0), watchos(2.0));                      // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryIron API_AVAILABLE(ios(8.0), watchos(2.0));                         // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryThiamin API_AVAILABLE(ios(8.0), watchos(2.0));                      // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryRiboflavin API_AVAILABLE(ios(8.0), watchos(2.0));                   // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryNiacin API_AVAILABLE(ios(8.0), watchos(2.0));                       // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFolate API_AVAILABLE(ios(8.0), watchos(2.0));                       // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryBiotin API_AVAILABLE(ios(8.0), watchos(2.0));                       // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPantothenicAcid API_AVAILABLE(ios(8.0), watchos(2.0));              // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPhosphorus API_AVAILABLE(ios(8.0), watchos(2.0));                   // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryIodine API_AVAILABLE(ios(8.0), watchos(2.0));                       // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryMagnesium API_AVAILABLE(ios(8.0), watchos(2.0));                    // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryZinc API_AVAILABLE(ios(8.0), watchos(2.0));                         // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySelenium API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCopper API_AVAILABLE(ios(8.0), watchos(2.0));                       // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryManganese API_AVAILABLE(ios(8.0), watchos(2.0));                    // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryChromium API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryMolybdenum API_AVAILABLE(ios(8.0), watchos(2.0));                   // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryChloride API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPotassium API_AVAILABLE(ios(8.0), watchos(2.0));                    // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCaffeine API_AVAILABLE(ios(8.0), watchos(2.0));                     // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryWater API_AVAILABLE(ios(9.0), watchos(2.0));                        // Volume, Cumulative

HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierUVExposure API_AVAILABLE(ios(9.0), watchos(2.0));                          // Scalar(Count), Discrete

/*--------------------------------*/
/*   HKCategoryType Identifiers   */
/*--------------------------------*/

typedef NSString * HKCategoryTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSleepAnalysis API_AVAILABLE(ios(8.0), watchos(2.0));                       // HKCategoryValueSleepAnalysis
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAppleStandHour API_AVAILABLE(ios(9.0), watchos(2.0));                      // HKCategoryValueAppleStandHour
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierCervicalMucusQuality API_AVAILABLE(ios(9.0), watchos(2.0));                // HKCategoryValueCervicalMucusQuality
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierOvulationTestResult API_AVAILABLE(ios(9.0), watchos(2.0));                 // HKCategoryValueOvulationTestResult
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMenstrualFlow API_AVAILABLE(ios(9.0), watchos(2.0));                       // HKCategoryValueMenstrualFlow
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierIntermenstrualBleeding API_AVAILABLE(ios(9.0), watchos(2.0));              // (Spotting) HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSexualActivity API_AVAILABLE(ios(9.0), watchos(2.0));                      // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMindfulSession API_AVAILABLE(ios(10.0), watchos(3.0));                     // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHighHeartRateEvent API_AVAILABLE(ios(12.2), watchos(5.2));                 // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLowHeartRateEvent API_AVAILABLE(ios(12.2), watchos(5.2));                  // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierIrregularHeartRhythmEvent API_AVAILABLE(ios(12.2), watchos(5.2));          // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAudioExposureEvent                                                         // HKCategoryValueAudioExposureEvent
    API_DEPRECATED_WITH_REPLACEMENT("HKCategoryTypeIdentifierEnvironmentalAudioExposureEvent", ios(13.0, 14.0), watchos(6.0, 7.0));
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierToothbrushingEvent API_AVAILABLE(ios(13.0), watchos(6.0));                 // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierPregnancy API_AVAILABLE(ios(14.3), watchos(7.2));                          // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLactation API_AVAILABLE(ios(14.3), watchos(7.2));                          // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierContraceptive API_AVAILABLE(ios(14.3), watchos(7.2));                      // HKCategoryValueContraceptive
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierEnvironmentalAudioExposureEvent API_AVAILABLE(ios(14.0), watchos(7.0));    // HKCategoryValueEnvironmentalAudioExposureEvent
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHeadphoneAudioExposureEvent API_AVAILABLE(ios(14.2), watchos(7.1));        // HKCategoryValueHeadphoneAudioExposureEvent
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHandwashingEvent API_AVAILABLE(ios(14.0), watchos(7.0));                   // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLowCardioFitnessEvent API_AVAILABLE(ios(14.3), watchos(7.2));

// Symptoms
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAbdominalCramps API_AVAILABLE(ios(13.6), watchos(7.0));                    // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAcne API_AVAILABLE(ios(13.6), watchos(7.0));                               // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAppetiteChanges API_AVAILABLE(ios(13.6), watchos(7.0));                    // HKCategoryValueAppetiteChanges
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierBladderIncontinence API_AVAILABLE(ios(14.0), watchos(7.0));                // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierBloating API_AVAILABLE(ios(13.6), watchos(7.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierBreastPain API_AVAILABLE(ios(13.6), watchos(7.0));                         // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierChestTightnessOrPain API_AVAILABLE(ios(13.6), watchos(7.0));               // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierChills API_AVAILABLE(ios(13.6), watchos(7.0));                             // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierConstipation API_AVAILABLE(ios(13.6), watchos(7.0));                       // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierCoughing API_AVAILABLE(ios(13.6), watchos(7.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierDiarrhea API_AVAILABLE(ios(13.6), watchos(7.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierDizziness API_AVAILABLE(ios(13.6), watchos(7.0));                          // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierDrySkin API_AVAILABLE(ios(14.0), watchos(7.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierFainting API_AVAILABLE(ios(13.6), watchos(7.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierFatigue API_AVAILABLE(ios(13.6), watchos(7.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierFever API_AVAILABLE(ios(13.6), watchos(7.0));                              // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierGeneralizedBodyAche API_AVAILABLE(ios(13.6), watchos(7.0));                // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHairLoss API_AVAILABLE(ios(14.0), watchos(7.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHeadache API_AVAILABLE(ios(13.6), watchos(7.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHeartburn API_AVAILABLE(ios(13.6), watchos(7.0));                          // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHotFlashes API_AVAILABLE(ios(13.6), watchos(7.0));                         // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLossOfSmell API_AVAILABLE(ios(13.6), watchos(7.0));                        // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLossOfTaste API_AVAILABLE(ios(13.6), watchos(7.0));                        // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLowerBackPain API_AVAILABLE(ios(13.6), watchos(7.0));                      // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMemoryLapse API_AVAILABLE(ios(14.0), watchos(7.0));                        // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMoodChanges API_AVAILABLE(ios(13.6), watchos(7.0));                        // HKCategoryValuePresence
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierNausea API_AVAILABLE(ios(13.6), watchos(7.0));                             // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierNightSweats API_AVAILABLE(ios(14.0), watchos(7.0));                        // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierPelvicPain API_AVAILABLE(ios(13.6), watchos(7.0));                         // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierRapidPoundingOrFlutteringHeartbeat API_AVAILABLE(ios(13.6), watchos(7.0)); // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierRunnyNose API_AVAILABLE(ios(13.6), watchos(7.0));                          // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierShortnessOfBreath API_AVAILABLE(ios(13.6), watchos(7.0));                  // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSinusCongestion API_AVAILABLE(ios(13.6), watchos(7.0));                    // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSkippedHeartbeat API_AVAILABLE(ios(13.6), watchos(7.0));                   // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSleepChanges API_AVAILABLE(ios(13.6), watchos(7.0));                       // HKCategoryValuePresence
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSoreThroat API_AVAILABLE(ios(13.6), watchos(7.0));                         // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierVaginalDryness API_AVAILABLE(ios(14.0), watchos(7.0));                     // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierVomiting API_AVAILABLE(ios(13.6), watchos(7.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierWheezing API_AVAILABLE(ios(13.6), watchos(7.0));                           // HKCategoryValueSeverity


/*--------------------------------------*/
/*   HKCharacteristicType Identifiers   */
/*--------------------------------------*/

typedef NSString * HKCharacteristicTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierBiologicalSex API_AVAILABLE(ios(8.0), watchos(2.0));           // HKBiologicalSexObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierBloodType API_AVAILABLE(ios(8.0), watchos(2.0));               // HKBloodTypeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierDateOfBirth API_AVAILABLE(ios(8.0), watchos(2.0));             // NSDateComponents
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierFitzpatrickSkinType API_AVAILABLE(ios(9.0), watchos(2.0));     // HKFitzpatrickSkinTypeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierWheelchairUse API_AVAILABLE(ios(10.0), watchos(3.0));          // HKWheelchairUseObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierActivityMoveMode API_AVAILABLE(ios(14.0), watchos(7.0));       // HKActivityMoveModeObject

/*-----------------------------------*/
/*   HKCorrelationType Identifiers   */
/*-----------------------------------*/

typedef NSString * HKCorrelationTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCorrelationTypeIdentifier const HKCorrelationTypeIdentifierBloodPressure API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN HKCorrelationTypeIdentifier const HKCorrelationTypeIdentifierFood API_AVAILABLE(ios(8.0), watchos(2.0));

/*--------------------------------*/
/*   HKDocumentType Identifiers   */
/*--------------------------------*/

typedef NSString * HKDocumentTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKDocumentTypeIdentifier const HKDocumentTypeIdentifierCDA API_AVAILABLE(ios(10.0), watchos(3.0));

/*------------------------------*/
/*   HKWorkoutType Identifier   */
/*------------------------------*/

HK_EXTERN NSString * const HKWorkoutTypeIdentifier API_AVAILABLE(ios(8.0), watchos(2.0));

/*--------------------------------*/
/*   HKSeriesSample Identifiers   */
/*--------------------------------*/

HK_EXTERN NSString * const HKWorkoutRouteTypeIdentifier API_AVAILABLE(ios(11.0), watchos(4.0));
HK_EXTERN NSString * const HKDataTypeIdentifierHeartbeatSeries API_AVAILABLE(ios(13.0), watchos(6.0));

NS_ASSUME_NONNULL_END
