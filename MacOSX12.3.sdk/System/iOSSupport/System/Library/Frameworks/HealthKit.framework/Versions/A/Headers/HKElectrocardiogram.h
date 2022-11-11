//
//  HKElectrocardiogram.h
//  HealthKit
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <HealthKit/HKSample.h>

@class HKQuantity;

NS_ASSUME_NONNULL_BEGIN

/*!
@enum          HKElectrocardiogramLead
@abstract      The medically-defined leads supported by HKElectrocardiogram
@constant      HKElectrocardiogramLeadAppleWatchSimilarToLeadI.   Apple Watch Series 4 and above has an electrical heart sensor that, when using
                                                                  the ECG app, enables the generation and analysis of an ECG  similar to a Lead I ECG.
*/
typedef NS_ENUM(NSInteger, HKElectrocardiogramLead) {
    HKElectrocardiogramLeadAppleWatchSimilarToLeadI = 1
} API_AVAILABLE(ios(14.0), watchos(7.0)) NS_SWIFT_NAME(HKElectrocardiogram.Lead);

/*!
@enum          HKElectrocardiogramClassification
@abstract      The possible classifications determined for HKElectrocardiograms

@constant      HKElectrocardiogramClassificationNotSet                      No classification is set on this sample.
@constant      HKElectrocardiogramClassificationSinusRhythm                 The sample exhibits no signs  of atrial fibrillation.
@constant      HKElectrocardiogramClassificationAtrialFibrillation          The sample exhibits signs of atrial fibrillation.
@constant      HKElectrocardiogramClassificationInconclusiveLowHeartRate    The sample classifier could not check for atrial fibrillation due to a heart rate under 50 BPM.
@constant      HKElectrocardiogramClassificationInconclusiveHighHeartRate   The sample classifier could not check for atrial fibrillation due to a high heart rate.
@constant      HKElectrocardiogramClassificationInconclusivePoorReading     The sample classifier did not attempt a classification due to not meeting the signal requirements.
@constant      HKElectrocardiogramClassificationInconclusiveOther           The sample classifier could not determine a classification.
@constant      HKElectrocardiogramClassificationUnrecognized                The classification created for this sample is unrecognized on this device.
*/
typedef NS_ENUM(NSInteger, HKElectrocardiogramClassification) {
    HKElectrocardiogramClassificationNotSet = 0,
    HKElectrocardiogramClassificationSinusRhythm,
    HKElectrocardiogramClassificationAtrialFibrillation,
    HKElectrocardiogramClassificationInconclusiveLowHeartRate,
    HKElectrocardiogramClassificationInconclusiveHighHeartRate,
    HKElectrocardiogramClassificationInconclusivePoorReading,
    HKElectrocardiogramClassificationInconclusiveOther,
    
    HKElectrocardiogramClassificationUnrecognized = 100,
} API_AVAILABLE(ios(14.0), watchos(7.0)) NS_SWIFT_NAME(HKElectrocardiogram.Classification);

/*!
@enum          HKElectrocardiogramSymptomsStatus
@abstract      An indication of whether the user experienced symptoms when taking an ECG
@constant      HKElectrocardiogramSymptomsStatusNotSet        The user did not specify whether or not they experienced symptoms.
               HKElectrocardiogramSymptomsStatusNone          The user did not experience any symptoms during the duration of the electrocardiogram reading.
               HKElectrocardiogramSymptomsStatusPresent       The user indicated that they experienced symptoms during the duration of the electrocardiogram reading.
@discussion    If an HKElectrocardiogram indicates that there are symptoms present, you must do a separate sample query to
                                retrieve those symptoms.
 */
typedef NS_ENUM(NSInteger, HKElectrocardiogramSymptomsStatus) {
    HKElectrocardiogramSymptomsStatusNotSet = 0,
    HKElectrocardiogramSymptomsStatusNone = 1,
    HKElectrocardiogramSymptomsStatusPresent = 2,
} API_AVAILABLE(ios(14.0), watchos(7.0)) NS_SWIFT_NAME(HKElectrocardiogram.SymptomsStatus);

/*!
 @class         HKElectrocardiogram
 @abstract      An HKElectrocardiogram is a collection of voltage values as waveforms
                from one or more leads
*/
HK_EXTERN API_AVAILABLE(ios(14.0), watchos(7.0))
@interface HKElectrocardiogram : HKSample

/*!
 The number of voltage measurements in the electrocardiogram.
 */
@property (nonatomic, readonly, assign) NSInteger numberOfVoltageMeasurements;

/*!
 The frequency at which the data was sampled. This is reported in [HKUnit hertzUnit].
*/
@property (nonatomic, readonly, copy, nullable) HKQuantity *samplingFrequency;

/*!
 The classification of this electrocardiogram sample.
*/
@property (nonatomic, readonly, assign) HKElectrocardiogramClassification classification;

/*!
 The average heart rate of the user while the electrocardiogram was recorded.
*/
@property (nonatomic, readonly, copy, nullable) HKQuantity *averageHeartRate;

/*!
 Whether the user experienced symptoms during this electrocardiogram.
*/
@property (nonatomic, readonly, assign) HKElectrocardiogramSymptomsStatus symptomsStatus;

@end


// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathAverageHeartRate API_AVAILABLE(ios(14.0), watchos(7.0));
HK_EXTERN NSString * const HKPredicateKeyPathECGClassification API_AVAILABLE(ios(14.0), watchos(7.0));
HK_EXTERN NSString * const HKPredicateKeyPathECGSymptomsStatus API_AVAILABLE(ios(14.0), watchos(7.0));

NS_ASSUME_NONNULL_END
