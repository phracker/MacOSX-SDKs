//
//  ARRaycastResult.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import <ARKit/ARRaycastQuery.h>

@class ARAnchor;

NS_ASSUME_NONNULL_BEGIN

/**
 Result of a raycast on a single target.
 */
API_AVAILABLE(ios(13.0))
@interface ARRaycastResult : NSObject

/**
 The transformation matrix that defines the raycast result's rotation, translation and scale relative to the world.
 */
@property (nonatomic, readonly) simd_float4x4 worldTransform;

/**
 Type of the target where the ray terminated.
 */
@property (nonatomic, readonly, assign) ARRaycastTarget target;

/**
 Alignment of the target.
 */
@property (nonatomic, readonly, assign) ARRaycastTargetAlignment targetAlignment;

/**
 The anchor that the ray intersected.
 
 @discussion In case of an existing plane target, an anchor will always be provided. In case of an estimated plane target,
 an anchor may be provided if the ray hit an existing plane.
 */
@property (nonatomic, readonly, strong, nullable) ARAnchor *anchor;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
