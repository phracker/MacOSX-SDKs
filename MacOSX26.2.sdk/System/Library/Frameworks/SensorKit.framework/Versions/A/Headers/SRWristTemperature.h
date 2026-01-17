//
//  SRWristTemperature.h
//  SensorKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  SRWristTemperatureCondition
 *
 *  Discussion:
 *     Indicates if the temperature accuracy has been impacted by any user initiated activiy.
 *
 *    Definitions of each condition as follows:
 *        - SRWristTemperatureConditionNone indicates data has not been impacted.
 *        - SRWristTemperatureConditionOffWrist indicates device has been off wrist and data has been impacted.
 *        - SRWristTemperatureConditionOnCharger indicates device has been on the charger and data has been impacted.
 *        - SRWristTemperatureConditionInMotion indicates data has been impacted by movement.
 */
typedef NS_OPTIONS(NSUInteger, SRWristTemperatureCondition) {
    SRWristTemperatureConditionNone = 0,
    SRWristTemperatureConditionOffWrist = 1 << 0,
    SRWristTemperatureConditionOnCharger = 1 << 1,
    SRWristTemperatureConditionInMotion = 1 << 2,
} API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRWristTemperature : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property timestamp
 *
 * @brief Timestamp of when temperature measurement was taken.
 *
 */
@property(nonatomic, strong, readonly) NSDate *timestamp;

/*!
 * @property value
 *
 * @brief Temperature sensor value in celsius
 *
 */
@property(nonatomic, strong, readonly) NSMeasurement<NSUnitTemperature *> *value;

/*!
 * @property condition
 *
 * @brief Indicate system conditions that may impact the temperature sample.
 *
 */
@property (nonatomic, readonly) SRWristTemperatureCondition condition;

/*!
 * @property errorEstimate
 *
 * @brief Estimated temperature error per sample.
 *        Error could be in either positive or negative direction.
 */
@property(nonatomic, strong, readonly) NSMeasurement<NSUnitTemperature *> *errorEstimate;
@end

NS_ASSUME_NONNULL_END
