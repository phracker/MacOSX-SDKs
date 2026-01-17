//
//  ARHitTestResult.h
//  ARKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <simd/simd.h>

@class ARAnchor;

/**
 Option set of hit-test result types.
 */
API_DEPRECATED("Use raycasting", ios(11.0, 14.0))
typedef NS_OPTIONS(NSUInteger, ARHitTestResultType) {
    /** Result type from intersecting the nearest feature point. */
    ARHitTestResultTypeFeaturePoint                                        = (1 << 0),
    
    /** Result type from intersecting a horizontal plane estimate, determined for the current frame. */
    ARHitTestResultTypeEstimatedHorizontalPlane                            = (1 << 1),
    
    /** Result type from intersecting a vertical plane estimate, determined for the current frame. */
    ARHitTestResultTypeEstimatedVerticalPlane API_AVAILABLE(ios(11.3))     = (1 << 2),
    
    /** Result type from intersecting with an existing plane anchor. */
    ARHitTestResultTypeExistingPlane                                       = (1 << 3),
    
    /** Result type from intersecting with an existing plane anchor, taking into account the plane’s extent. */
    ARHitTestResultTypeExistingPlaneUsingExtent                            = (1 << 4),
    
    /** Result type from intersecting with an existing plane anchor, taking into account the plane’s geometry. */
    ARHitTestResultTypeExistingPlaneUsingGeometry API_AVAILABLE(ios(11.3)) = (1 << 5),
} NS_SWIFT_NAME(ARHitTestResult.ResultType);

NS_ASSUME_NONNULL_BEGIN

/**
 A result of an intersection found during a hit-test.
 */
API_DEPRECATED("Use raycasting", ios(11.0, 14.0))
@interface ARHitTestResult : NSObject

/**
 The type of the hit-test result.
 */
@property (nonatomic, readonly) ARHitTestResultType type;

/**
 The distance from the camera to the intersection in meters.
 */
@property (nonatomic, readonly) CGFloat distance;

/**
 The transformation matrix that defines the intersection’s rotation, translation and scale
 relative to the anchor or nearest feature point.
 */
@property (nonatomic, readonly) simd_float4x4 localTransform;

/**
 The transformation matrix that defines the intersection’s rotation, translation and scale
 relative to the world.
 */
@property (nonatomic, readonly) simd_float4x4 worldTransform;

/**
 The anchor that the hit-test intersected.
 
 @discussion An anchor will only be provided for existing plane result types.
 */
@property (nonatomic, strong, nullable, readonly) ARAnchor *anchor;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
