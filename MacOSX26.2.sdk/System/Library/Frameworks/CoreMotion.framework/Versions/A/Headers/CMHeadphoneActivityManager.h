/*
 *  CMHeadphoneActivityManager.h
 *  CoreMotion
 *
 *  Copyright (c) 2024 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMMotionActivity.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

#define CM_VISION_OS_AVAILABLE API_UNAVAILABLE(visionos)

typedef NS_ENUM(NSInteger, CMHeadphoneActivityStatus) {
	CMHeadphoneActivityStatusDisconnected = 0,
	CMHeadphoneActivityStatusConnected,
} NS_SWIFT_NAME(CMHeadphoneActivityManager.Status);

/*
 *  CMHeadphoneActivityStatusHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when status updates are available.
 */
typedef void (^CMHeadphoneActivityStatusHandler)(CMHeadphoneActivityStatus status, NSError * __nullable error) NS_SWIFT_NAME(CMHeadphoneActivityManager.StatusHandler);

/*
 *  CMHeadphoneActivityHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when headphone motion activity data is available. Currently automotive and cycling are not supported.
 */
typedef void (^CMHeadphoneActivityHandler)(CMMotionActivity * __nullable activity, NSError * __nullable error) NS_SWIFT_NAME(CMHeadphoneActivityManager.ActivityHandler) CM_VISION_OS_AVAILABLE;


/*
 *  CMHeadphoneActivityManager
 *
 *  Discussion:
 *    The CMHeadphoneActivityManager object is your entry point to the headphone activity service.
 */
COREMOTION_EXPORT API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0)) CM_VISION_OS_AVAILABLE

@interface CMHeadphoneActivityManager : NSObject

/*
 *  authorizationStatus
 *
 *  Discussion:
 *    Returns the current authorization status for headphone activity.
 */
+ (CMAuthorizationStatus)authorizationStatus;

/*
 *  activityAvailable
 *
 *  Discussion:
 *    Determines whether headphone motion activity is available.
 */
@property(readonly, nonatomic, getter=isActivityAvailable) BOOL activityAvailable;

/*
 *  activityActive
 *
 *  Discussion:
 *    Determines whether the CMHeadphoneActivityManager is currently providing
 *    headphone motion activity updates.
 */
@property(readonly, nonatomic, getter=isActivityActive) BOOL activityActive;

/*
 *  statusAvailable
 *
 *  Discussion:
 *    Determines whether headphone status is available.
 */
@property(readonly, nonatomic, getter=isStatusAvailable) BOOL statusAvailable;

/*
 *  statusActive
 *
 *  Discussion:
 *    Determines whether the CMHeadphoneActivityManager is currently providing
 *    status updates.
 */
@property(readonly, nonatomic, getter=isStatusActive) BOOL statusActive;

/*
 *  startActivityUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts headphone activity updates, providing data to the given handler through the given queue.
 */
- (void)startActivityUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMHeadphoneActivityHandler)handler;

/*
 *  stopActivityUpdates
 *
 *  Discussion:
 *    Stops headphone activity updates.
 */
- (void)stopActivityUpdates;

/*
 *  startStatusUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts headphone status updates (Connected/Disconnected), providing data to the given handler through the given queue.
 *    Connected will only be sent when a compatible headphone is connected.
 */
- (void)startStatusUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMHeadphoneActivityStatusHandler)handler;

/*
 *  stopStatusUpdates
 *
 *  Discussion:
 *    Stops headphone status updates.
 */
- (void)stopStatusUpdates;

@end

#undef CM_VISION_OS_AVAILABLE

NS_ASSUME_NONNULL_END
