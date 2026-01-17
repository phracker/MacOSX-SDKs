//
//  SRWristDetection.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SRWristLocation) {
    SRWristLocationLeft,
    SRWristLocationRight,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, SRCrownOrientation) {
    SRCrownOrientationLeft,
    SRCrownOrientationRight,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRWristDetection : NSObject
@property(readonly) BOOL onWrist;
@property(readonly) SRWristLocation wristLocation;
@property(readonly) SRCrownOrientation crownOrientation;
/*!
 * @property onWristDate
 *
 * @brief Start date of the recent on-wrist state.
 *
 * @discussion
 * - When the state changes from off-wrist to on-wrist, onWristDate would be updated to the current date, and offWristDate would remain the same.
 * - When the state changes from on-wrist to off-wrist, offWristDate would be updated to the current date, and onWristDate would remain the same.
 */
@property (readonly, strong, nullable) NSDate *onWristDate API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos);

/*!
 * @property offWristDate
 *
 * @brief Start date of the recent off-wrist state.
 *
 * @discussion
 * - When the state changes from off-wrist to on-wrist, onWristDate would be updated to the current date, and offWristDate would remain the same.
 * - When the state changes from on-wrist to off-wrist, offWristDate would be updated to the current date, and onWristDate would remain the same.
 */
@property (readonly, strong, nullable) NSDate *offWristDate API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos);
@end

NS_ASSUME_NONNULL_END
