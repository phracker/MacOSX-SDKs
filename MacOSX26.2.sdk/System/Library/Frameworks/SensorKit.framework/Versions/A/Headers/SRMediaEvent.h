//
//  SRMediaEvent.h
//  SensorKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SRMediaEventType) {
    SRMediaEventOnScreen = 1,
    SRMediaEventOffScreen,
} API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRMediaEvent : NSObject <NSCopying, NSSecureCoding>

/*!
 * @property mediaIdentifier
 *
 * @brief Unique media identifier
 *
 * @discussion
 * Unique media identifier to track a specific media object.
 */
@property (nonatomic, readonly, strong) NSString *mediaIdentifier;
/*!
 * @property eventType
 *
 * @brief Type of the event
 *
 * @discussion
 * Type of media event (e.g., media has been displayed on a screen).
 */
@property (nonatomic, readonly, assign) SRMediaEventType eventType;
@end
NS_ASSUME_NONNULL_END
