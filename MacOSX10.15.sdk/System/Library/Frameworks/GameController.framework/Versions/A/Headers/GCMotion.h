//
//  GCMotion.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;

/**
 A 3 dimensional acceleration vector measured as scalar multiples of earth's gravitational acceleration, G.
 
 The azimuth direction is assumed to be (0, 0, 1), so a device held at rest with the z axis aligned with the azimuth
 is assumed to have gravitation applying the vector (0, 0, -1).
 
 @field x X-axis acceleration as a scalar multiple of earth's gravitational acceleration, G.
 @field y Y-axis acceleration as a scalar multiple of earth's gravitational acceleration, G.
 @field z Z-axis acceleration as a scalar multiple of earth's gravitational acceleration, G.
 */
typedef struct {
    double x, y, z;
} GCAcceleration;

/**
 A structure containing 3-axis rotation rate data.
 
 
 @field x   X-axis rotation rate in radians/second. The sign follows the right hand
            rule (i.e. if the right hand is wrapped around the X axis such that the 
            tip of the thumb points toward positive X, a positive rotation is one
            toward the tips of the other 4 fingers).
 
 @field y   Y-axis rotation rate in radians/second. The sign follows the right hand 
            rule (i.e. if the right hand is wrapped around the Y axis such that the 
            tip of the thumb points toward positive Y, a positive rotation is one   
            toward the tips of the other 4 fingers).
 @field z
            Z-axis rotation rate in radians/second. The sign follows the right hand
            rule (i.e. if the right hand is wrapped around the Z axis such that the
            tip of the thumb points toward positive Z, a positive rotation is one
            toward the tips of the other 4 fingers).
 */
typedef struct {
	double x, y, z;
} GCRotationRate;


/**
 A structure containing 3-axis rotation data. The angles are rotated in order or pitch then yaw then roll.
 
 
 @field pitch X-axis rotation in radians. The sign follows the right hand
 rule (i.e. if the right hand is wrapped around the X axis such that the
 tip of the thumb points toward positive X, a positive rotation is one
 toward the tips of the other 4 fingers).
 
 @field yaw   Y-axis rotation in radians. The sign follows the right hand
 rule (i.e. if the right hand is wrapped around the Y axis such that the
 tip of the thumb points toward positive Y, a positive rotation is one
 toward the tips of the other 4 fingers).
 
 @field roll  Z-axis rotation in radians. The sign follows the right hand
 rule (i.e. if the right hand is wrapped around the Z axis such that the
 tip of the thumb points toward positive Z, a positive rotation is one
 toward the tips of the other 4 fingers).
 */
typedef struct {
    double pitch, yaw, roll;
} GCEulerAngles;

/**
 Represents a quaternion (one way of parameterizing attitude).
 If q is an instance of GCQuaternion, mathematically it represents the following quaternion:
 
 		q.x*i + q.y*j + q.z*k + q.w
 
 */
typedef struct GCQuaternion {
    double x, y, z, w;
} GCQuaternion;


/**
 A profile for getting motion input from a controller that has the ability to measure acceleration
 and rotation rate. 
 
 You check for the availablity of motion inputs by getting the motion property
 of a controller. If that returns a nil value; motion is not available. A non-nil value is a valid
 GCMotion profile that is able to provide motion input.
 
 @see GCController.motion
 */
API_AVAILABLE(macos(10.10), ios(8.0), tvos(8.0))
@interface GCMotion : NSObject

/**
 A profile keeps a reference to the controller that it is mapping input from.
 
 @see GCController
 */
#if !__has_feature(objc_arc)
@property (nonatomic, readonly, assign) GCController *controller;
#else
@property (nonatomic, readonly, weak) GCController *controller;
#endif

/**
 Called whenever a motion value changed.
 */
typedef void (^GCMotionValueChangedHandler)(GCMotion *motion);
@property (nonatomic, copy, nullable) GCMotionValueChangedHandler valueChangedHandler;

/**
 The gravity vector expressed in the controller's reference frame.
 
 Note that the total acceleration of the controller is equal to gravity plus userAcceleration.
 
 @see userAcceleration
 */
@property (nonatomic, assign, readonly) GCAcceleration gravity;

/**
 The acceleration that the user is giving to the controller.
 
 Note that the total acceleration of the controller is equal to gravity plus userAcceleration.
 
 @see userAcceleration
 */
@property (nonatomic, assign, readonly) GCAcceleration userAcceleration;

/**
 The controller generating the motion data has sensors that can accurately determine the current attitude and rotation rate. If this is enabled the motion data for attitude and rotation rate are usable for inputs.
 */
@property (nonatomic, assign, readonly) BOOL hasAttitudeAndRotationRate API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/**
 The current attitude of the controller.
 
 @note Remotes without accurate attitude and rotation rate can not determine a stable attitude so the values will be (0,0,0,1) at all times.
 @see hasAttitudeAndRotationRate
 @see GCMicroGamepad
 */
@property (nonatomic, assign, readonly) GCQuaternion attitude API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/**
 The current rotation rate of the controller.
 
 @note Remotes without accurate attitude and rotation rate can not determine a stable rotation rate so the values will be (0,0,0) at all times.
 @see hasAttitudeAndRotationRate
 @see GCMicroGamepad
 */
@property (nonatomic, assign, readonly) GCRotationRate rotationRate API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/**
 Sets the gravity vector expressed in the controller's reference frame.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see gravity
 */
- (void)setGravity:(GCAcceleration)gravity API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Sets the acceleration that the user is giving to the controller.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see userAcceleration
 */
- (void)setUserAcceleration:(GCAcceleration)userAcceleration API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Sets the current rotation rate of the controller.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see attitude
 */
- (void)setAttitude:(GCQuaternion)attitude API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Sets the current rotation rate of the controller.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see rotationRate
 */
- (void)setRotationRate:(GCRotationRate)rotationRate API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Sets the state vector of the motion profile to a copy of the input motion profile's state vector.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see GCController.snapshot
 */
- (void) setStateFromMotion:(GCMotion *)motion API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end

NS_ASSUME_NONNULL_END
