//
//  SRElectrocardiogramSample.h
//  SensorKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <SensorKit/SRDefines.h>
#import <SensorKit/SRElectrocardiogramSession.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @typedef SRElectrocardiogramDataFlags
 * @brief Flags indicating sensor context or events that occurred during
 * the sample reading
 *
 * @discussion
 * These flags can provide some indication of data validity or other system conditions
 * that may influence how the recorded data should be treated.
 *
 */
typedef NS_OPTIONS(NSUInteger, SRElectrocardiogramDataFlags) {
    SRElectrocardiogramDataFlagsNone = 0,

    /*!
     * @const SRElectrocardiogramDataFlagsSignalInvalid
     * @brief Indicates an invalid sensor signal in the ECG data
     */
    SRElectrocardiogramDataFlagsSignalInvalid = 1 << 0,

    /*!
     * @const SRElectrocardiogramDataFlagsCrownTouched
     * @brief Indicates ECG data was recorded when the crown was being touched
     */
    SRElectrocardiogramDataFlagsCrownTouched = 1 << 1,
} API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRElectrocardiogramData : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly, assign) SRElectrocardiogramDataFlags flags;

/*!
 * @property value
 *
 * @brief Value of the ECG AC data in microvolts
 *
 */
@property (nonatomic, readonly, strong) NSMeasurement<NSUnitElectricPotentialDifference *> *value;
@end

/*!
 * @typedef SRElectrocardiogramLead
 * @brief Which lead was used to record the ECG data
 */
typedef NS_ENUM(NSInteger, SRElectrocardiogramLead) {
    SRElectrocardiogramLeadRightArmMinusLeftArm = 1,
    SRElectrocardiogramLeadLeftArmMinusRightArm,
} API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRElectrocardiogramSample : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property date
 *
 * @brief Date of the start of the batch of ECG data
 *
 */
@property (nonatomic, readonly, strong) NSDate *date;

/*!
 * @property frequency
 *
 * @brief Frequency in hertz at which the ECG data was recorded
 *
 */
@property (nonatomic, readonly, strong) NSMeasurement<NSUnitFrequency *> *frequency;

/*!
 * @property session
 *
 * @brief The session to which this sample belongs
 *
 */
@property (nonatomic, readonly, strong) SRElectrocardiogramSession *session;

@property (nonatomic, readonly, assign) SRElectrocardiogramLead lead;

@property (nonatomic, readonly, copy) NSArray<SRElectrocardiogramData *> *data;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
