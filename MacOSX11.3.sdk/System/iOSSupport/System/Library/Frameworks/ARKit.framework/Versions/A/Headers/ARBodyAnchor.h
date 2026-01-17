//
//  ARBodyAnchor.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class ARBody2D;
@class ARSkeleton3D;

/**
 An anchor representing a body in the world.
 */
API_AVAILABLE(ios(13.0))
@interface ARBodyAnchor : ARAnchor <ARTrackable>

/**
 The tracked skeleton in 3D.
 @note The default height of this skeleton, measured from lowest to highest joint in standing position, is defined to be 1.71 meters.
 */
@property (nonatomic, strong, readonly) ARSkeleton3D *skeleton;

/**
 The factor between estimated physical size and default size of the skeleton.
 @see -[ARSkeletonDefinition neutralBodySkeleton3D]
 
 @discussion This value will be estimated if automaticSkeletonScaleEstimationEnabled is set to true on the ARBodyTrackingConfiguration.
 It is used to correct the transform's translation. Default value is 1.0.
 */
@property (nonatomic, readonly) CGFloat estimatedScaleFactor;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
