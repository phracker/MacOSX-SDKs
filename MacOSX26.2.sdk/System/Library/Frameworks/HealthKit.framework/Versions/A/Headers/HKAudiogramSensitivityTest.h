//
//  HKAudiogramSensitivityTest.h
//  HealthKit
//
//  Copyright © 2023-2024 Apple. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>


@class HKAudiogramSensitivityPointClampingRange;
@class HKQuantity;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKAudiogramConductionType
 @abstract      Represents the conduction type used for an HKAudiogramSensitivityTest
 
 @constant      HKAudiogramConductionTypeAir
 */
typedef NS_ENUM(NSInteger, HKAudiogramConductionType) {
    HKAudiogramConductionTypeAir = 0,
} API_AVAILABLE(ios(18.1), watchos(11.1), macCatalyst(18.1), macos(15.1), visionos(2.1));

/*!
 @enum          HKAudiogramSensitivityTestSide
 @abstract      Represents the test side used for an HKAudiogramSensitivityTest
 
 @constant      HKAudiogramSensitivityTestSideLeft
 @constant      HKAudiogramSensitivityTestSideRight
 */
typedef NS_ENUM(NSInteger, HKAudiogramSensitivityTestSide) {
    HKAudiogramSensitivityTestSideLeft = 0,
    HKAudiogramSensitivityTestSideRight = 1,
} API_AVAILABLE(ios(18.1), watchos(11.1), macCatalyst(18.1), macos(15.1), visionos(2.1));

HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.1), watchos(11.1), macCatalyst(18.1), macos(15.1), visionos(2.1))
@interface HKAudiogramSensitivityTest : NSObject<NSSecureCoding, NSCopying>

/*!
 @property      sensitivity
 @abstract      Ear sensitivity measured in dB from a baseline of 0 dB. Reduced hearing sensitivity corresponds to an increase from 0 dB.
 The unit of measurement is `HKUnit.decibelHearingLevelUnit` or "dBHL".
 */
@property (nonatomic, readonly, copy) HKQuantity *sensitivity;

/*!
 @property      type
 @abstract      The conduction type
 */
@property (nonatomic, assign, readonly) HKAudiogramConductionType type;

/*!
 @property      masked
 @abstract      Indicates if the test was conducted with or without masking
 */
@property (nonatomic, assign, readonly) BOOL masked;

/*!
 @property      side
 @abstract      The test side
 */
@property (nonatomic, assign, readonly) HKAudiogramSensitivityTestSide side;

/*!
 @property      clampingRange
 @abstract      If present, indicates that the range within which the sensitivity point should be clamped.
 */
@property (nonatomic, readonly, copy, nullable) HKAudiogramSensitivityPointClampingRange *clampingRange;

/*!
 @method                    initWithSensitivity:type:masked:side:clampingRange:error:
 @abstract                  Creates a sensitivity test which can be added to a HKAudiogramSensitivityPoint
 @param sensitivity         The ear sensitivity measured in dB from a baseline of 0 dB with unit `HKUnit.decibelHearingLevelUnit` or "dBHL".
 @param type                The type of test
 @param masked              If the test was conducted with or without masking
 @param side                The test side which was tested
 @param clampingRange       The clamping range (if any)
 @param errorOut            If there was a problem creating this instance this will contain the error.
 @return                    New instance of a Sensitivity Test or nil if there were problems
                            creating the instance.  Errors may include incorrect quantity units or sensitivity out of range
 */
- (nullable instancetype)initWithSensitivity:(HKQuantity *)sensitivity
                                        type:(HKAudiogramConductionType)type
                                      masked:(BOOL)masked
                                        side:(HKAudiogramSensitivityTestSide)side
                               clampingRange:(nullable HKAudiogramSensitivityPointClampingRange *)clampingRange
                                       error:(NSError **)errorOut;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

