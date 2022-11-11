//
//  ARSkeletonDefinition.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


typedef NSString *ARSkeletonJointName NS_TYPED_ENUM NS_SWIFT_NAME(ARSkeleton.JointName)        API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRoot                            API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameHead                            API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftHand                        API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightHand                       API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftFoot                        API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightFoot                       API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftShoulder                    API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightShoulder                   API_AVAILABLE(ios(13.0));


@class ARSkeleton2D;
@class ARSkeleton3D;

/**
 Definition of a skeleton.

 @discussion A skeleton consists of a set of labeled joints that are defined in a certain hierarchy, i.e. joints are parented to other joints.
 One may use the parentIndices property to identify the hierarchy for a given skeleton definition.
 */
API_AVAILABLE(ios(13.0))
@interface ARSkeletonDefinition : NSObject

/**
 Default skeleton definition for bodies defined in 3D.
 @note The default height of this skeleton, measured from lowest to highest joint in standing position, is defined to be 1.71 meters.
 @see ARSkeleton3D
 */
@property (class, nonatomic, readonly) ARSkeletonDefinition *defaultBody3DSkeletonDefinition;

/**
 Default skeleton definition for bodies defined in 2D.
 @see ARBody2D
 */
@property (class, nonatomic, readonly) ARSkeletonDefinition *defaultBody2DSkeletonDefinition;


/**
 The number of joints.
 */
@property (nonatomic, readonly) NSUInteger jointCount;

/**
 The joint names.
 */
@property (nonatomic, readonly) NSArray<NSString *> *jointNames;

/**
 The parent index for each joint.
 @discussion This property may be used to identify the hierarchical dependency between joints. If a line is drawn for every joint and its parent joint
 the result is a visualization of the underlying skeleton. The joint with no parent is denoted as the root joint. The root joint's parent index has
 a value of -1.
  */
@property (nonatomic, readonly) NSArray<NSNumber *> *parentIndices NS_REFINED_FOR_SWIFT;

/**
 The 3D skeleton in neutral pose.
 @discussion The neutral skeleton pose assumes a standardized size of the skeleton in meters. The neutral pose is defined as the skeleton's T-pose.
 */
@property (nonatomic, nullable, readonly) ARSkeleton3D *neutralBodySkeleton3D;

/**
 Returns the index for a given joint identifier.
 
 @param jointName Name of a given joint.
 @discussion This function returns NSNotFound if an invalid joint name is passed.
 @return Joint index.
 */
- (NSUInteger)indexForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
