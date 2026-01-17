/*
 *  CMBatchedSensorManager.h
 *  CoreMotion
 *
 *  Copyright (c) 2023 Apple Inc. All rights reserved.
 *
 */

#ifndef CMBatchedSensorManager_h
#define CMBatchedSensorManager_h

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAccelerometer.h>
#import <CoreMotion/CMDeviceMotion.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

COREMOTION_EXPORT API_AVAILABLE(watchos(10.0)) API_UNAVAILABLE(macos)
@interface CMBatchedSensorManager : NSObject

/*
 *  authorizationStatus
 *
 *  Discussion:
 *    Returns the current authorization status for batched sensor updates.
 */
@property(class, readonly, nonatomic) CMAuthorizationStatus authorizationStatus;

/*
 *  accelerometerSupported
 *
 *  Discussion:
 *    Reflects whether batched accelerometer data is supported on this platform.
 */
@property(class, readonly, nonatomic, getter=isAccelerometerSupported) BOOL accelerometerSupported;

/*
 *  accelerometerActive
 *
 *  Discussion:
 *    Reflects whether batched accelerometer data is currently being provided.
 */
@property(readonly, nonatomic, getter=isAccelerometerActive) BOOL accelerometerActive;

/*
 *  accelerometerFrequency
 *
 *  Discussion:
 *    Frequency of provided accelerometer data in hertz.
 */
@property(readonly, nonatomic) NSInteger accelerometerDataFrequency;

/*
 *  accelerometerBatch
 *
 *  Discussion:
 *    Latest batch of accelerometer data, or nil if none available.
 */
@property(readonly, nullable) NSArray<CMAccelerometerData *> *accelerometerBatch;

/*
 *  startAccelerometerUpdates
 *
 *  Discussion:
 *    Starts batched accelerometer updates. Examine the accelerometerBatch property to access the latest batch of data.
 */
- (void)startAccelerometerUpdates;

/*
 *  startAccelerometerUpdatesWithHandler
 *
 *  Discussion:
 *    Provides batched accelerometer updates to the provided handler.
 */
- (void)startAccelerometerUpdatesWithHandler:(void(^)(NSArray<CMAccelerometerData *> * _Nullable data, NSError * _Nullable error))handler;

/*
 *  stopAccelerometerUpdates
 *
 *  Discussion:
 *    Stop batched accelerometer updates.
 */
- (void)stopAccelerometerUpdates;

/*
 *  deviceMotionSupported
 *
 *  Discussion:
 *    Reflects whether batched device motion data is supported on this platform.
 */
@property(class, readonly, nonatomic, getter=isDeviceMotionSupported) BOOL deviceMotionSupported;

/*
 *  deviceMotionFrequency
 *
 *  Discussion:
 *    Frequency of provided device motion data in hertz.
 */
@property(readonly, nonatomic) NSInteger deviceMotionDataFrequency;

/*
 *  deviceMotionActive
 *
 *  Discussion:
 *    Reflects whether batched device motion data is currently being provided.
 */
@property(readonly, nonatomic, getter=isDeviceMotionActive) BOOL deviceMotionActive;

/*
 *  deviceMotionBatch
 *
 *  Discussion:
 *    Latest batch of device motion data, or nil if none available.
 */
@property(readonly, nullable) NSArray<CMDeviceMotion *> *deviceMotionBatch;

/*
 *  startDeviceMotionUpdates
 *
 *  Discussion:
 *    Starts batched device motion updates. Examine the deviceMotionBatch property to access the latest batch of data.
 */
- (void)startDeviceMotionUpdates;

/*
 *  startDeviceMotionUpdatesWithHandler
 *
 *  Discussion:
 *    Provides batched device motion updates to the provided handler.
 */
- (void)startDeviceMotionUpdatesWithHandler:(void(^)(NSArray<CMDeviceMotion *> * _Nullable data, NSError * _Nullable error))handler;

/*
 *  stopDeviceMotionUpdates
 *
 *  Discussion:
 *    Stop batched device motion updates.
 */
- (void)stopDeviceMotionUpdates;

@end

NS_ASSUME_NONNULL_END

#endif /* CMBatchedSensorManager_h */
