//
//  SACrashDetectionEvent.h
//  SafetyKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <SafetyKit/SABase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief This enumeration defines possible emergency responses to a crash event
 * @sa SACrashDetectionEventResponse
 */
typedef NS_ENUM(NSInteger, SACrashDetectionEventResponse) {
    SACrashDetectionEventResponseAttempted, ///< Emergency SOS response for the crash event was attempted
    SACrashDetectionEventResponseDisabled, ///< Emergency SOS response for crash events is disabled
} NS_SWIFT_NAME(SACrashDetectionEvent.Response) API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos);

/**
 * @brief This object describes a Crash Detection event and response to it.
 * @sa SACrashDetectionEvent
 */
SA_EXTERN API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos)
@interface SACrashDetectionEvent : NSObject<NSSecureCoding, NSCopying>

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

/**
 * date
 *
 * @discussion
 * The time a crash was detected
 */
@property (nonatomic, readonly) NSDate *date;

/**
 * response
 *
 * @discussion
 * enum value representing the emergency response to the Crash Detection event
 *
 * @sa SACrashDetectionEventResponse
 */
@property (nonatomic, readonly) SACrashDetectionEventResponse response;

/**
 * location
 *
 * @discussion
 * Location information describing the geographical location of where the Crash Detection occurred.
 *
 *  @sa CLLocation
 */
@property (nonatomic, readonly, nullable) CLLocation *location;

@end

NS_ASSUME_NONNULL_END
