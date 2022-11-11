//
//  ARSkeleton.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARSkeletonDefinition.h>
#import <simd/simd.h>
#import <Foundation/Foundation.h>
#import <Vision/Vision.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing a skeleton.
 @discussion A skeleton's structure is defined by a skeleton definition.
 @see ARSkeletonDefinition
 */
API_AVAILABLE(ios(13.0))
@interface ARSkeleton : NSObject

/**
 Skeleton definition.
 */
@property (nonatomic, readonly) ARSkeletonDefinition *definition;

/**
 The number of joints.
 */
@property (nonatomic, readonly) NSUInteger jointCount NS_REFINED_FOR_SWIFT;

/**
 Tracking state for a given joint.
 
 @param jointIndex The index of the joint.
 @return True if the joint is tracked. False otherwise.
 */
- (BOOL)isJointTracked:(NSInteger)jointIndex;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 An object representing a skeleton in 3D.
 */
API_AVAILABLE(ios(13.0))
@interface ARSkeleton3D : ARSkeleton

/**
 The model space transforms for each joint.
 */
@property (nonatomic, readonly) const simd_float4x4 *jointModelTransforms NS_REFINED_FOR_SWIFT;

/**
 The local space joint data for each joint.
 */
@property (nonatomic, readonly) const simd_float4x4 *jointLocalTransforms NS_REFINED_FOR_SWIFT;

/**
 Returns the model transform for a joint with a given name.
 
 @discussion If an invalid joint name is passed the returned matrix will be filled with NaN values.
 @param jointName The name of the joint.
 @return Model transform
 */
- (simd_float4x4)modelTransformForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/**
 Returns the local transform for a joint with a given name.
 
 @discussion If an invalid joint name is passed the returned matrix will be filled with NaN values.
 @param jointName The name of the joint.
 @return Local transform
 */
- (simd_float4x4)localTransformForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 An object representing a skeleton in 2D.
 */
API_AVAILABLE(ios(13.0))
@interface ARSkeleton2D : ARSkeleton

/**
 The joint landmarks in normalized coordinates.
 @discussion The joint landmarks are detected in the captured image on the ARFrame.
 @see -[ARFrame capturedImage]
 */
@property (nonatomic, readonly) const simd_float2 *jointLandmarks NS_REFINED_FOR_SWIFT;

/**
 Returns the landmark point for a joint with a given name.
 @discussion If an invalid joint name is passed the returned point will be filled with NaN values.
 
 @param jointName The name of the joint.
 @return Landmark in normalized image coordinates.
 */
- (simd_float2)landmarkForJointNamed:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Returns the landmark joint name that corresponds to a key point defined in Vision framework.
 @see VNRecognizedPointKey, VNDetectHumanBodyPoseRequest
 @discussion If an invalid key point is passed the returned point will be nil.
 
 @param recognizedPointKey Recognized key point.
 @return Joint name that could be mapped to a ARSkeleton2D. Nil if no mapping exists.
 */
FOUNDATION_EXTERN __nullable ARSkeletonJointName ARSkeletonJointNameForRecognizedPointKey(VNRecognizedPointKey recognizedPointKey) NS_SWIFT_NAME(ARSkeletonJointName.init(_:)) API_AVAILABLE(ios(14.0));

NS_ASSUME_NONNULL_END
