/*
 *  CMFallDetectionEvent.h
 *  CoreMotion
 *
 *  Copyright (c) 2020 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief Fall Detection Event Resolution
 * @sa CMFallDetectionEvent
 *
 * @discussion
 * This enumeration defines the different states in which a Fall Detection event can be resolved
 */
COREMOTION_EXPORT API_AVAILABLE(watchos(7.2)) API_UNAVAILABLE(macos, ios, tvos)
typedef NS_ENUM(NSInteger, CMFallDetectionEventUserResolution) {
	
	CMFallDetectionEventUserResolutionConfirmed, ///< the user confirmed the fall alert
	CMFallDetectionEventUserResolutionDismissed, ///< the user dismissed the fall alert either immediately or after a sequence of haptics and chimes
	CMFallDetectionEventUserResolutionRejected, ///< the user rejected the fall alert, indicating that they didn't fall
	CMFallDetectionEventUserResolutionUnresponsive, ///< the user did not respond to the fall alert and no recovery motion was detected
	
} NS_SWIFT_NAME(CMFallDetectionEvent.UserResolution);


/**
 * @brief Fall Detection Event
 * @sa CMFallDetectionEventResolution
 *
 * This object represents a Fall Detection event and how it was resolved
 */
COREMOTION_EXPORT API_AVAILABLE(watchos(7.2)) API_UNAVAILABLE(macos, ios, tvos)
@interface CMFallDetectionEvent : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 * date
 *  @discussion
 *    The time a fall was detected
 */
@property (nonatomic, readonly) NSDate *date;

/**
 * resolution
 *  @discussion
 *    enum value representing how the Fall Detection event was resolved
 *    @sa CMFallDetectionEventResolution
 */
@property (nonatomic, readonly) CMFallDetectionEventUserResolution resolution;

@end
NS_ASSUME_NONNULL_END
