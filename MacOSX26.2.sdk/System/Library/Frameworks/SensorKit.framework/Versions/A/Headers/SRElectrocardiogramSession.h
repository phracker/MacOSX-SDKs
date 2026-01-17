//
//  SRElectrocardiogramSession.h
//  SensorKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <SensorKit/SRDefines.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @typedef SRElectrocardiogramSessionState
 * @brief
 * The state of the ECG session when this sample was taken
 *
 */
typedef NS_ENUM(NSInteger, SRElectrocardiogramSessionState) {
    SRElectrocardiogramSessionStateBegin = 1,
    SRElectrocardiogramSessionStateActive,
    SRElectrocardiogramSessionStateEnd,
} API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

/*!
 * @typedef SRElectrocardiogramSessionGuidance
 * @brief
 * The type of session used to record the ECG sample
 *
 * @const SRElectrocardiogramSessionGuidanceGuided
 * @brief
 * A session, usually of fixed duration, where the user is provided coaching to guide the ECG readings
 *
 * @const SRElectrocardiogramSessionGuidanceUnguided
 * @brief
 * A session, usually of undefined duration, where the user is not provided coaching to guide the ECG readings
 *
 */
typedef NS_ENUM(NSInteger, SRElectrocardiogramSessionGuidance) {
    SRElectrocardiogramSessionGuidanceGuided = 1,
    SRElectrocardiogramSessionGuidanceUnguided,
} API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRElectrocardiogramSession : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property state
 *
 * @brief The state of the ECG session when the sample was recorded
 *
 */
@property (nonatomic, readonly, assign) SRElectrocardiogramSessionState state;

/*!
 * @property sessionGuidance
 *
 * @brief The type of session guidance during the the ECG session
 */
@property (nonatomic, readonly, assign) SRElectrocardiogramSessionGuidance sessionGuidance;

/*!
 * @property identifier
 *
 * @discussion
 * Used to tie samples across multiple \c SRFetchResult s to the same session
 *
 */
@property (nonatomic, readonly, copy) NSString *identifier;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
