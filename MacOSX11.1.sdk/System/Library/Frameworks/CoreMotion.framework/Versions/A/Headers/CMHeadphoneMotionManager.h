/*
 *  CMHeadphoneMotionManager.h
 *  CoreMotion
 *
 *  Copyright (c) 2020 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMDeviceMotion.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMHeadphoneDeviceMotionHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when device motion data is available.
 */
typedef void (^CMHeadphoneDeviceMotionHandler)(CMDeviceMotion * __nullable motion, NSError * __nullable error) NS_SWIFT_NAME(CMHeadphoneMotionManager.DeviceMotionHandler);

@protocol CMHeadphoneMotionManagerDelegate;

/*
 *  CMHeadphoneMotionManager
 *
 *  Discussion:
 *    The CMHeadphoneMotionManager object is your entry point to the headphone motion service.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos)
@interface CMHeadphoneMotionManager : NSObject

/*
 *  authorizationStatus
 *
 *  Discussion:
 *    Returns the current authorization status for headphone motion.
 */
+ (CMAuthorizationStatus)authorizationStatus;

/*
 *  delegate
 *
 *  Discussion:
 *    The delegate object to receive motion manager events.
 */
@property(weak, nonatomic, nullable) id<CMHeadphoneMotionManagerDelegate> delegate;

/*
 *  deviceMotionAvailable
 *
 *  Discussion:
 *    Determines whether device motion is available.
 */
@property(readonly, nonatomic, getter=isDeviceMotionAvailable) BOOL deviceMotionAvailable;

/*
 *  deviceMotionActive
 *
 *  Discussion:
 *    Determines whether the CMHeadphoneMotionManager is currently providing device
 *    motion updates.
 */
@property(readonly, nonatomic, getter=isDeviceMotionActive) BOOL deviceMotionActive;

/*
 *  deviceMotion
 *
 *  Discussion:
 *    Returns the latest sample of device motion data, or nil if none is available.
 */
@property(readonly, nullable) CMDeviceMotion *deviceMotion;

/*
 *  startDeviceMotionUpdates
 *
 *  Discussion:
 *    Starts device motion updates with no handler. To receive the latest device motion data
 *    when desired, examine the deviceMotion property.
 */
- (void)startDeviceMotionUpdates;

/*
 *  startDeviceMotionUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts device motion updates, providing data to the given handler through the given queue.
 *
 */
- (void)startDeviceMotionUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMHeadphoneDeviceMotionHandler)handler;

/*
 *  stopDeviceMotionUpdates
 *
 *  Discussion:
 *    Stops device motion updates.
 */
- (void)stopDeviceMotionUpdates;

@end

NS_ASSUME_NONNULL_END
