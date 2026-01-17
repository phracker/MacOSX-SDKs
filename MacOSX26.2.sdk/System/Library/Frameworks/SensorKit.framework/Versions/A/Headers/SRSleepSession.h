//
//  SRSleepSession.h
//  SensorKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(26.0), watchos(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, macos)
@interface SRSleepSession : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property startDate
 *
 * @brief Start date of sleep session
 */
@property(nonatomic, readonly, strong) NSDate* startDate;

/*!
 * @property duration
 *
 * @brief Sleep session duration
 *
 * @discussion
 * Equal to 0 if endReason is SRSleepSessionEndReasonNoEndEvent
 */
@property(nonatomic, readonly, assign) NSTimeInterval duration;

/*!
 * @property identifier
 *
 * @brief Sleep session unique identifier
 */
@property(nonatomic, readonly, copy) NSString *identifier;

@end
NS_HEADER_AUDIT_END(nullability, sendability)
