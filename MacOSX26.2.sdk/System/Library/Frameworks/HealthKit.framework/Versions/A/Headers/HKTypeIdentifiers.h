//
//  HKTypeIdentifiers.h
//  HealthKit
//
//  Copyright © 2014-2025 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <HealthKit/HKDefines.h>



NS_ASSUME_NONNULL_BEGIN

/*--------------------------------*/
/*   HKQuantityType Identifiers   */
/*--------------------------------*/

typedef NSString * HKQuantityTypeIdentifier NS_STRING_ENUM;

// Body Measurements
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleSleepingWristTemperature API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));       // degC, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyFatPercentage API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // %, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyMass API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                             // kg, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyMassIndex API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // count, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierElectrodermalActivity API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                // S, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeight API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                               // m, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierLeanBodyMass API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                         // kg, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWaistCircumference API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // m, Discrete (Arithmetic)

// Fitness
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierActiveEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                   // kcal, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleExerciseTime API_AVAILABLE(ios(9.3), watchos(2.2), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // min, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleMoveTime API_AVAILABLE(ios(14.5), watchos(7.4), macCatalyst(14.5), macos(13.0), visionos(1.0));                       // min, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleStandTime API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // min, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBasalEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // kcal, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierCrossCountrySkiingSpeed API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));            // m/s, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierCyclingCadence API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0), visionos(1.0));                     // count/min, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierCyclingFunctionalThresholdPower API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0), visionos(1.0));    // W, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierCyclingPower API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0), visionos(1.0));                       // W, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierCyclingSpeed API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0), visionos(1.0));                       // m/s, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceCrossCountrySkiing API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));         // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceCycling API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceDownhillSnowSports API_AVAILABLE(ios(11.2), watchos(4.2), macCatalyst(13.0), macos(13.0), visionos(1.0));          // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistancePaddleSports API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));               // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceRowing API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));                     // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceSkatingSports API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));              // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceSwimming API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceWalkingRunning API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));               // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceWheelchair API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // m, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierEstimatedWorkoutEffortScore API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));        // appleEffortScore, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierFlightsClimbed API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                       // count, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNikeFuel API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                             // count, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPaddleSportsSpeed API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));                  // m/s, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPhysicalEffort API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0), visionos(1.0));                     // kcal/(kg*hr), Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPushCount API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                           // count, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRowingSpeed API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));                        // m/s, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRunningPower API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));                        // W, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRunningSpeed API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));                        // m/s, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierStepCount API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                            // count, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                 // count, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierUnderwaterDepth API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));                     // m, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWorkoutEffortScore API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));                 // appleEffortScore, Discrete (Arithmetic)

// Hearing Health
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierEnvironmentalAudioExposure API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0), visionos(1.0));          // dBASPL, Discrete (Equivalent Continuous Level)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierEnvironmentalSoundReduction API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));         // dBASPL, Discrete (Equivalent Continuous Level)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeadphoneAudioExposure API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0), visionos(1.0));              // dBASPL, Discrete (Equivalent Continuous Level)

// Heart
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAtrialFibrillationBurden API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));            // %, Discrete (Temporally Weighted)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeartRate API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                            // count/s, Discrete (Temporally Weighted)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeartRateRecoveryOneMinute API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));          // count/min, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeartRateVariabilitySDNN API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0), visionos(1.0));            // ms, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPeripheralPerfusionIndex API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));             // %, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRestingHeartRate API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // count/min, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierVO2Max API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                              // ml/(kg*min), Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingHeartRateAverage API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0), visionos(1.0));             // count/min, Discrete (Arithmetic)

// Mobility
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleWalkingSteadiness API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0), visionos(1.0));              // %, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRunningGroundContactTime API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));            // ms, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRunningStrideLength API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));                 // m, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRunningVerticalOscillation API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));          // cm, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierSixMinuteWalkTestDistance API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));           // m, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierStairAscentSpeed API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                    // m/s, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierStairDescentSpeed API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                   // m/s, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingAsymmetryPercentage API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));          // %, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingDoubleSupportPercentage API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));      // %, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingSpeed API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                        // m/s, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingStepLength API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                   // m, Discrete (Arithmetic)

// Nutrition
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryBiotin API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCaffeine API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCalcium API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                       // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCarbohydrates API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                 // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryChloride API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCholesterol API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                   // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryChromium API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCopper API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryEnergyConsumed API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                // kcal, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatMonounsaturated API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));            // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatPolyunsaturated API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));            // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatSaturated API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatTotal API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFiber API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                         // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFolate API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryIodine API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryIron API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                          // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryMagnesium API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                     // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryManganese API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                     // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryMolybdenum API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryNiacin API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPantothenicAcid API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));               // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPhosphorus API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPotassium API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                     // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryProtein API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                       // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryRiboflavin API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySelenium API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySodium API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySugar API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                         // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryThiamin API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                       // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminA API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminB12 API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                    // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminB6 API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                     // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminC API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminD API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminE API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminK API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // g, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryWater API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                         // mL, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryZinc API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                          // g, Cumulative

// Other
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodAlcoholContent API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // %, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodPressureDiastolic API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));               // mmHg, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodPressureSystolic API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                // mmHg, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierInsulinDelivery API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                     // IU, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNumberOfAlcoholicBeverages API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0), visionos(1.0));          // count, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNumberOfTimesFallen API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // count, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierTimeInDaylight API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0), visionos(1.0));                     // min, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierUVExposure API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                           // , Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWaterTemperature API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));                    // degC, Discrete (Arithmetic)

// Reproductive Health
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBasalBodyTemperature API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                 // degC, Discrete (Arithmetic)

// Respiratory
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleSleepingBreathingDisturbances API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0)); // count, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierForcedExpiratoryVolume1 API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));              // L, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierForcedVitalCapacity API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // L, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierInhalerUsage API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                         // count, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierOxygenSaturation API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                     // %, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPeakExpiratoryFlowRate API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));               // L/min, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRespiratoryRate API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // count/s, Discrete (Arithmetic)

// Vital Signs
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodGlucose API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                         // mg/dL, Discrete (Arithmetic)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyTemperature API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // degC, Discrete (Arithmetic)

/*--------------------------------*/
/*   HKCategoryType Identifiers   */
/*--------------------------------*/

typedef NSString * HKCategoryTypeIdentifier NS_STRING_ENUM;

// Fitness
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAppleStandHour API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                       // HKCategoryValueAppleStandHour

// Hearing Health
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierEnvironmentalAudioExposureEvent API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));     // HKCategoryValueEnvironmentalAudioExposureEvent
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHeadphoneAudioExposureEvent API_AVAILABLE(ios(14.2), watchos(7.1), macCatalyst(14.2), macos(13.0), visionos(1.0));         // HKCategoryValueHeadphoneAudioExposureEvent

// Heart
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHighHeartRateEvent API_AVAILABLE(ios(12.2), watchos(5.2), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHypertensionEvent API_AVAILABLE(ios(26.2), watchos(26.2), macCatalyst(26.2), macos(26.2), visionos(26.2));                  // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierIrregularHeartRhythmEvent API_AVAILABLE(ios(12.2), watchos(5.2), macCatalyst(13.0), macos(13.0), visionos(1.0));           // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLowCardioFitnessEvent API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0), visionos(1.0));               // HKCategoryValueLowCardioFitnessEvent
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLowHeartRateEvent API_AVAILABLE(ios(12.2), watchos(5.2), macCatalyst(13.0), macos(13.0), visionos(1.0));                   // HKCategoryValue

// Mindfulness
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMindfulSession API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                      // HKCategoryValue

// Mobility
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAppleWalkingSteadinessEvent API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0), visionos(1.0));         // HKCategoryValueAppleWalkingSteadinessEvent

// Other
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHandwashingEvent API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                    // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierToothbrushingEvent API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // HKCategoryValue

// Reproductive Health
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierBleedingAfterPregnancy API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));             // HKCategoryValueVaginalBleeding
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierBleedingDuringPregnancy API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));            // HKCategoryValueVaginalBleeding
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierCervicalMucusQuality API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                 // HKCategoryValueCervicalMucusQuality
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierContraceptive API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0), visionos(1.0));                       // HKCategoryValueContraceptive
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierInfrequentMenstrualCycles API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));           // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierIntermenstrualBleeding API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));               // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierIrregularMenstrualCycles API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));            // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLactation API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0), visionos(1.0));                           // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMenstrualFlow API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // HKCategoryValueVaginalBleeding
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierOvulationTestResult API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                  // HKCategoryValueOvulationTestResult
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierPersistentIntermenstrualBleeding API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));    // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierPregnancy API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0), visionos(1.0));                           // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierPregnancyTestResult API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0), visionos(1.0));                 // HKCategoryValuePregnancyTestResult
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierProgesteroneTestResult API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0), visionos(1.0));              // HKCategoryValueProgesteroneTestResult
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierProlongedMenstrualPeriods API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));           // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSexualActivity API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                       // HKCategoryValue

// Respiratory
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSleepApneaEvent API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));                    // HKCategoryValue

// Sleep
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSleepAnalysis API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));                        // HKCategoryValueSleepAnalysis

// Symptoms
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAbdominalCramps API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                     // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAcne API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                                // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAppetiteChanges API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                     // HKCategoryValueAppetiteChanges
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierBladderIncontinence API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                 // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierBloating API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierBreastPain API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                          // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierChestTightnessOrPain API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierChills API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                              // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierConstipation API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                        // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierCoughing API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierDiarrhea API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierDizziness API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierDrySkin API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                             // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierFainting API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierFatigue API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                             // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierFever API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                               // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierGeneralizedBodyAche API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                 // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHairLoss API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHeadache API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHeartburn API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierHotFlashes API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                          // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLossOfSmell API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                         // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLossOfTaste API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                         // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierLowerBackPain API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                       // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMemoryLapse API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                         // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMoodChanges API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                         // HKCategoryValuePresence
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierNausea API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                              // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierNightSweats API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                         // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierPelvicPain API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                          // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierRapidPoundingOrFlutteringHeartbeat API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));  // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierRunnyNose API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                           // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierShortnessOfBreath API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                   // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSinusCongestion API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                     // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSkippedHeartbeat API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                    // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSleepChanges API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                        // HKCategoryValuePresence
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSoreThroat API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                          // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierVaginalDryness API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));                      // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierVomiting API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                            // HKCategoryValueSeverity
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierWheezing API_AVAILABLE(ios(13.6), watchos(7.0), macCatalyst(13.6), macos(13.0), visionos(1.0));                            // HKCategoryValueSeverity

/*--------------------------------------*/
/*   HKCharacteristicType Identifiers   */
/*--------------------------------------*/

typedef NSString * HKCharacteristicTypeIdentifier NS_STRING_ENUM;

// Me
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierActivityMoveMode API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0), visionos(1.0));    // HKActivityMoveModeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierBiologicalSex API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));        // HKBiologicalSexObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierBloodType API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));            // HKBloodTypeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierDateOfBirth API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));          // NSDateComponents
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierFitzpatrickSkinType API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));  // HKFitzpatrickSkinTypeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierWheelchairUse API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0), visionos(1.0));       // HKWheelchairUseObject

/*-----------------------------------*/
/*   HKCorrelationType Identifiers   */
/*-----------------------------------*/

typedef NSString * HKCorrelationTypeIdentifier NS_STRING_ENUM;

// Heart
HK_EXTERN HKCorrelationTypeIdentifier const HKCorrelationTypeIdentifierBloodPressure API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));

// Other
HK_EXTERN HKCorrelationTypeIdentifier const HKCorrelationTypeIdentifierFood API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));

/*--------------------------------*/
/*   HKDocumentType Identifiers   */
/*--------------------------------*/

typedef NSString * HKDocumentTypeIdentifier NS_STRING_ENUM;

// Clinical Documents
HK_EXTERN HKDocumentTypeIdentifier const HKDocumentTypeIdentifierCDA API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0), visionos(1.0));

/*----------------------------------------*/
/*   HKScoredAssessmentType Identifiers   */
/*----------------------------------------*/

typedef NSString * HKScoredAssessmentTypeIdentifier NS_STRING_ENUM;

// Mindfulness
HK_EXTERN HKScoredAssessmentTypeIdentifier const HKScoredAssessmentTypeIdentifierGAD7 API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(17.0), macos(14.0), visionos(2.0));
HK_EXTERN HKScoredAssessmentTypeIdentifier const HKScoredAssessmentTypeIdentifierPHQ9 API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(17.0), macos(14.0), visionos(2.0));

/*-------------------------------*/
/*   HKWorkoutType Identifiers   */
/*-------------------------------*/

// Fitness
HK_EXTERN NSString * const HKWorkoutTypeIdentifier API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0), visionos(1.0));

/*--------------------------------*/
/*   HKSeriesSample Identifiers   */
/*--------------------------------*/

// Fitness
HK_EXTERN NSString * const HKWorkoutRouteTypeIdentifier API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0), visionos(1.0));

// Heart
HK_EXTERN NSString * const HKDataTypeIdentifierHeartbeatSeries API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0), visionos(1.0));

/*--------------------------------------*/
/*   HKVisionPrescription Identifiers   */
/*--------------------------------------*/

// Body Measurements
HK_EXTERN NSString * const HKVisionPrescriptionTypeIdentifier API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0), visionos(1.0));

/*-------------------------------*/
/*   HKStateofMind Identifiers   */
/*-------------------------------*/

// Mindfulness
HK_EXTERN NSString * const HKDataTypeIdentifierStateOfMind API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(17.0), macos(14.0), visionos(2.0));

/*---------------------------------------*/
/*   HKMedicationDoseEvent Identifiers   */
/*---------------------------------------*/

// Medication Tracking
HK_EXTERN NSString * const HKMedicationDoseEventTypeIdentifierMedicationDoseEvent API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));

/*-------------------------------------------*/
/*   HKUserAnnotatedMedication Identifiers   */
/*-------------------------------------------*/

// Medication Tracking
HK_EXTERN NSString * const HKDataTypeIdentifierUserAnnotatedMedicationConcept API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));

/*----------------*/
/*   Deprecated   */
/*----------------*/

HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAudioExposureEvent API_DEPRECATED_WITH_REPLACEMENT("HKCategoryTypeIdentifierEnvironmentalAudioExposureEvent", ios(13.0, 14.0), watchos(6.0, 7.0));

NS_ASSUME_NONNULL_END
