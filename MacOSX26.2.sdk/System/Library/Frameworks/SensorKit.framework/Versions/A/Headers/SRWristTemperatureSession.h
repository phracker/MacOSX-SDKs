//
//  SRWristTemperatureSession.h
//  SensorKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>
#import <SensorKit/SRWristTemperature.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRWristTemperatureSession : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property startDate
 *
 * @brief Indicates when temperatures were collected.
 *
 */
@property(nonatomic, strong, readonly) NSDate *startDate;

/*!
 * @property duration
 *
 * @brief Precise number of seconds temperatures were collected.
 *
 */
@property(nonatomic, readonly) NSTimeInterval duration;

/*!
 * @property version
 *
 * @brief Algorithm version.
 *
 */
@property(nonatomic, copy, readonly) NSString *version;

/*!
 * @property temperatures
 *
 * @brief Enumerator which could be used to view calculated wrist temperatures, along with their reading accuracy.
 *
 */
@property(nonatomic, copy, readonly) NSEnumerator<SRWristTemperature *> *temperatures NS_REFINED_FOR_SWIFT;
@end

NS_ASSUME_NONNULL_END
