//
//  HKAudiogramSensitivityPoint.h
//  HealthKit
//
//  Copyright © 2019-2024 Apple. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

@class HKAudiogramSensitivityPointClampingRange;
@class HKAudiogramSensitivityTest;
@class HKQuantity;

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0))
@interface HKAudiogramSensitivityPoint : NSObject <NSSecureCoding>

/*!
 @property frequency  Frequency where sensitivity was measured.  The unit of measurement
 is [HKUnit hertzUnit] or "Hz".
 */
@property (readonly, copy) HKQuantity *frequency;

/*!
 @property sensitivity Left ear sensitivity measured in dB from a baseline of 0 dB. Reduced hearing sensitivity corresponds to an increase from 0 dB.
 The unit of measurement is `HKUnit.decibelHearingLevelUnit` or "dBHL".
 */
@property (readonly, copy, nullable) HKQuantity *leftEarSensitivity API_DEPRECATED("Use tests object which will contain a value for left ear", ios(13.0, 18.1), watchos(6.0, 11.1));

/*!
 @property sensitivity Right ear sensitivity measured in dB from a baseline of 0 dB. Reduced hearing sensitivity corresponds to an increase from 0 dB.
 The unit of measurement is `HKUnit.decibelHearingLevelUnit` or "dBHL".
 */
@property (readonly, copy, nullable) HKQuantity *rightEarSensitivity API_DEPRECATED("Use tests object which will contain a value for right ear", ios(13.0, 18.1), watchos(6.0, 11.1));

/*!
 @property      tests
 @abstract      The tests conducted at this frequency
 */
@property (nonatomic, readonly, copy) NSArray<HKAudiogramSensitivityTest *> *tests API_AVAILABLE(ios(18.1), watchos(11.1), macCatalyst(18.1), macos(15.1), visionos(2.1));

/*!
 @method                    sensitivityPointWithFrequency:leftEarSensitivity:rightEarSensitivity:error:
 @abstract                  Creates a point that can be included in a audiogram.
 @param frequency           Frequency where sensitivity was measured.
 @param leftEarSensitivity  Left ear sensitivity measured in dB from a baseline of 0 dB. Reduced hearing sensitivity corresponds to an increase from 0 dB.
 @param rightEarSensitivity Right ear sensitivity measured in dB from a baseline of 0 dB. Reduced hearing sensitivity corresponds to an increase from 0 dB.
 @param error               If there was a problem creating this instance this will contain the error.
 @return                    New instance of a sensitivity point or nil if there were problems
                            creating the instance.  Errors may include incorrect quantity units
                            or data that is out of an expected range.
 */
+ (nullable instancetype)sensitivityPointWithFrequency:(HKQuantity *)frequency
                                    leftEarSensitivity:(nullable HKQuantity *)leftEarSensitivity
                                   rightEarSensitivity:(nullable HKQuantity *)rightEarSensitivity
                                                 error:(NSError * _Nullable *)error API_DEPRECATED("Use +[HKAudiogramSensitivityPoint sensitivityPointWithFrequency:tests:error:]", ios(13.0, 18.1), watchos(6.0, 11.1));

/*!
 @method                    sensitivityPointWithFrequency:tests:error:
 @abstract                  Creates a point that can be included in a audiogram.
 @param frequency           Frequency at which sensitivity was measured.
 @param tests               The tests conducted at the frequency
 @param errorOut            If there was a problem creating this instance this will contain the error.
 @return                    New instance of a sensitivity point or nil if there were problems
                            creating the instance.  Errors may include incorrect quantity units
                            or data that is out of an expected range.
 */
+ (nullable instancetype)sensitivityPointWithFrequency:(HKQuantity *)frequency
                                                 tests:(NSArray<HKAudiogramSensitivityTest *> *)tests
                                                 error:(NSError **)errorOut API_AVAILABLE(ios(18.1), watchos(11.1), macCatalyst(18.1), macos(15.1), visionos(2.1));

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
