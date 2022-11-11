//
//  ARCamera.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
#import <simd/simd.h>
#import <ARKit/ARTrackingStatusTypes.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A model representing the camera and its parameters.
 */
API_AVAILABLE(ios(11.0))
@interface ARCamera : NSObject <NSCopying>

/**
 The transformation matrix that defines the camera’s rotation and translation in world coordinates.
 */
@property (nonatomic, readonly) simd_float4x4 transform;

/**
 The camera’s orientation defined as Euler angles.
 
 @dicussion The order of components in this vector matches the axes of rotation:
               1. Pitch (the x component) is the rotation about the node’s x-axis (in radians)
               2. Yaw   (the y component) is the rotation about the node’s y-axis (in radians)
               3. Roll  (the z component) is the rotation about the node’s z-axis (in radians)
            ARKit applies these rotations in the following order:
               1. first roll
               2. then pitch
               3. then yaw
 */
@property (nonatomic, readonly) simd_float3 eulerAngles;

/**
 The tracking state of the camera.
 */
@property (nonatomic, readonly) ARTrackingState trackingState NS_REFINED_FOR_SWIFT;

/**
 The reason for the camera’s current tracking state.
 */
@property (nonatomic, readonly) ARTrackingStateReason trackingStateReason NS_REFINED_FOR_SWIFT;

/**
 The camera intrinsics.
 @discussion The matrix has the following contents:
 fx 0   px
 0  fy  py
 0  0   1
 fx and fy are the focal length in pixels.
 px and py are the coordinates of the principal point in pixels.
 The origin is at the center of the upper-left pixel.
 */
@property (nonatomic, readonly) simd_float3x3 intrinsics;

/**
 The camera image resolution in pixels.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 The camera exposure duration in seconds.
 */
@property (nonatomic, readonly) NSTimeInterval exposureDuration API_AVAILABLE(ios(13.0));

/**
 The camera exposure offset in EV (exposure value) units.
 */
@property (nonatomic, readonly) float exposureOffset API_AVAILABLE(ios(13.0));

/**
 The projection matrix of the camera.
 @discussion The projection matrix assumes no far clipping plane limit.
*/
@property (nonatomic, readonly) simd_float4x4 projectionMatrix;

/**
 Creates a projection matrix for the camera given rendering parameters.
 
 @discussion The projection matrix returned provides an aspect fill for the provided viewport size and orientation.
 If zFar is set to 0, an infinite projection matrix will be returned.
 @param orientation Viewport orientation.
 @param viewportSize Viewport size.
 @param zNear Near depth limit.
 @param zFar Far depth limit.
 */
- (simd_float4x4)projectionMatrixForOrientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize zNear:(CGFloat)zNear zFar:(CGFloat)zFar;

/**
 Project a 3D point in world coordinate system into 2D viewport space.
 
 @param point 3D point in world coordinate system.
 @param orientation Viewport orientation.
 @param viewportSize Viewport (or image) size.
 @return 2D point in viewport coordinate system with origin at top-left.
 */
- (CGPoint)projectPoint:(simd_float3)point orientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize;

/**
 Unproject a 2D point from the viewport onto a plane in 3D world coordinates.
 
 @discussion A 2D point in the viewport coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Unprojecting calculates the 3D position of the point along this line segment that intersects the provided plane.
 @param point A point in the viewport coordinate system with origin at top-left.
 @param planeTransform The transform used to define the coordinate system of the plane.
 The coordinate system’s positive Y axis is assumed to be the normal of the plane.
 @return 3D position in world coordinates or a NAN values if unprojection is not possible.
 */
- (simd_float3)unprojectPoint:(CGPoint)point ontoPlaneWithTransform:(simd_float4x4)planeTransform orientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize
API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

/**
 Returns the view matrix for the camera with a given interface orientation.
 
 @discussion The view matrix can be used to transform geometry from world space into camera space for a given orientation.
 @param orientation The interface orientation that will be used to render the camera’s view.
 */
- (simd_float4x4)viewMatrixForOrientation:(UIInterfaceOrientation)orientation;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
