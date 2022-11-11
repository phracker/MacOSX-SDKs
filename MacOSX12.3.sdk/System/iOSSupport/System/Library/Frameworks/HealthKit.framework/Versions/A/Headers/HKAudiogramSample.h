//
//  HKAudiogramSample.h
//  HealthKit
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <HealthKit/HKQuantity.h>
#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKAudiogramSensitivityPoint;

/*!
 @class     HKAudiogramSample
 @abstract  A sample object representing the results of a standard hearing test.
 */
HK_EXTERN API_AVAILABLE(ios(13.0), watchos(6.0))
@interface HKAudiogramSample : HKSample

/*!
 @property  sensitivityPoints
 @abstract  The hearing sensitivity readings associated with a hearing test.
 */
@property (readonly, copy) NSArray<HKAudiogramSensitivityPoint *> *sensitivityPoints;

/*!
 @method                   audiogramSampleWithsensitivityPoints:startDate:endDate:metadata:
 @abstract                 Creates a new audiogram sample with the specified attributes.
 @param sensitivityPoints  Sensitivity data associated with the sample, with a maximum limit of 30 points. Frequencies must be unique, and ordered ascending.
 @param startDate          The start date for the hearing test.
 @param endDate            The end date for the hearing test.
 @param metadata           Optional meta data associated with the sample.
 @return                   A new instance of an audiogram sample.
 */
+ (instancetype)audiogramSampleWithSensitivityPoints:(NSArray<HKAudiogramSensitivityPoint *> *)sensitivityPoints
                                           startDate:(NSDate *)startDate
                                             endDate:(NSDate *)endDate
                                            metadata:(nullable NSDictionary<NSString *, id> *)metadata;

@end

HK_EXTERN API_AVAILABLE(ios(13.0), watchos(6.0))
@interface HKAudiogramSensitivityPoint : NSObject

/*!
 @property frequency  Frequency where sensitivity was measured.  The unit of measurement
 is [HKUnit hertzUnit] or "Hz".
 */
@property (readonly, copy) HKQuantity *frequency;

/*!
 @property sensitivity Left ear sensitivity measured in attenuated dB from a baseline of 0 dB.
 The unit of measurement is [HKUnit decibelHearingLevelUnit] or "dBHL".
 */
@property (readonly, copy, nullable) HKQuantity *leftEarSensitivity;

/*!
 @property sensitivity Right ear sensitivity measured in attenuated dB from a baseline of 0 dB.
 The unit of measurement is [HKUnit decibelHearingLevelUnit] or "dBHL".
 */
@property (readonly, copy, nullable) HKQuantity *rightEarSensitivity;

/*!
 @method                    sensitivityPointWithFrequency:leftEarSensitivity:rightEarSensitivity:error:
 @abstract                  Creates a point that can be included in a audiogram.
 @param frequency           Frequency where sensitivity was measured.
 @param leftEarSensitivity  Left ear sensitivity measured in attenuated dB from a baseline of 0 dB.
 @param rightEarSensitivity Right ear sensitivity measured in attenuated dB from a baseline of 0 dB.
 @param error               If there was a problem creating this instance this will contain the error.
 @return                    New instance of a sensitivity point or nil if there were problems
                            creating the instance.  Errors may include incorrect quantity units
                            or data that is out of an expected range.
 */
+ (nullable instancetype)sensitivityPointWithFrequency:(HKQuantity *)frequency
                                    leftEarSensitivity:(nullable HKQuantity *)leftEarSensitivity
                                   rightEarSensitivity:(nullable HKQuantity *)rightEarSensitivity
                                                 error:(NSError * _Nullable *)error;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

