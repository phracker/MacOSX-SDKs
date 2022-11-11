//
//  ARRaycastQuery.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A value describing the target of a ray used for raycasting.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARRaycastTarget) {
    
    /** Ray's target is an already detected plane, considering the plane's estimated size and shape. */
    ARRaycastTargetExistingPlaneGeometry,
    
    /** Ray's target is an already detected plane, without considering the plane's size. */
    ARRaycastTargetExistingPlaneInfinite,
    
    /**
     Ray's target is a plane that is estimated using the feature points around the ray.
     When alignment is ARRaycastTargetAlignmentAny, alignment of estimated planes is based on the normal of the real world
     surface corresponding to the estimated plane.
     */
    ARRaycastTargetEstimatedPlane,
} NS_SWIFT_NAME(ARRaycastQuery.Target);

/**
 A value describing the alignment of a target.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARRaycastTargetAlignment) {
    /** A target that is horizontal with respect to gravity. */
    ARRaycastTargetAlignmentHorizontal,
    
    /** A target that is vertical with respect to gravity. */
    ARRaycastTargetAlignmentVertical,
    
    /** A target that is in any alignment, inclusive of horizontal and vertical. */
    ARRaycastTargetAlignmentAny
    
} NS_SWIFT_NAME(ARRaycastQuery.TargetAlignment);


/**
 Representation of a ray and its target which is used for raycasting.
 @discussion Represents a 3D ray and its target which is used to perform raycasting.
 */
API_AVAILABLE(ios(13.0))
@interface ARRaycastQuery : NSObject

/**
 Origin of the ray.
 */
@property (nonatomic, readonly) simd_float3 origin;

/**
 Direction of the ray.
 */
@property (nonatomic, readonly) simd_float3 direction;

/**
 Type of target where the ray should terminate.
 */
@property (nonatomic, readonly) ARRaycastTarget target;

/**
 The alignment of the target that should be considered for raycasting.
 */
@property (nonatomic, readonly) ARRaycastTargetAlignment targetAlignment;

/**
 Create a new ARRaycastQuery with the provided origin, direction, allowed target and its alignment.
 @param origin Origin of the ray.
 @param direction Direction of the ray.
 @param target Type of target where the ray is allowed to terminate.
 @param alignment Alignment of the target that should be considered for raycasting.
 */
- (instancetype)initWithOrigin:(simd_float3)origin direction:(simd_float3)direction allowingTarget:(ARRaycastTarget)target alignment:(ARRaycastTargetAlignment)alignment;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
