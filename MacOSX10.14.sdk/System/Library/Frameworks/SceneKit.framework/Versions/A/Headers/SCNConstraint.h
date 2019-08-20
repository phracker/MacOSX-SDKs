//
//  SCNConstraint.h
//  SceneKit
//
//  Copyright © 2013-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*!
 @class SCNConstraint
 @abstract A SCNConstraint is an abstract class that represents a single constraint that can be applied to a node.
 */

SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNConstraint : NSObject <NSCopying, NSSecureCoding, SCNAnimatable>

/*!
 @property enable
 @abstract Determines whether the constraint is enabled or not. Defaults to YES.
 */
@property(nonatomic, getter = isEnabled) BOOL enabled API_AVAILABLE(macos(10.10));

/*!
 @property influenceFactor
 @abstract Specifies the inflence factor of the receiver. Defaults to 1. Animatable
 */
@property(nonatomic) CGFloat influenceFactor API_AVAILABLE(macos(10.10));

/*!
 @property incremental
 @abstract Specifies whether or not the contraint should applies incrementally and have it's effect being cumulated over the rendered frames. Defaults to YES on macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Defaults to NO in earlier versions.
 */
@property(nonatomic, getter=isIncremental) BOOL incremental API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

// MARK: -

/*!
 @class SCNLookAtConstraint
 @abstract A SCNLookAtConstraint applies on a node's orientation so that it always look at another node.
 */

SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNLookAtConstraint : SCNConstraint

/*!
 @method lookAtConstraintWithTarget:
 @abstract Creates and returns a SCNLookAtConstraint object with the specified target.
 @param target The target node to look at.
 */
+ (instancetype)lookAtConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to look at.
 */
@property(nonatomic, retain, nullable) SCNNode *target;
- (nullable SCNNode *)target;
- (void)setTarget:(nullable SCNNode *)target API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property targetOffset
 @abstract Offset look at position in target space. Defaults to zero. Animatable
 */
@property(nonatomic, assign) SCNVector3 targetOffset API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property targetOffset
 @abstract Front direction in the constraint owner local space. Defaults to -[SCNNode localFront]. Animatable
 */
@property(nonatomic, assign) SCNVector3 localFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property worldUp
 @abstract Up reference direction in world space. Defaults to -[SCNNode localUp]. Animatable
 */
@property(nonatomic, assign) SCNVector3 worldUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/*!
 @property gimbalLockEnabled
 @abstract Specifies whether the receiver enables the gimbal lock. Defaults to NO.
 @discussion Enabling the gimbal lock prevents the receiver from rotating the constrained node around to roll axis.
 */
@property(nonatomic) BOOL gimbalLockEnabled;

@end

// MARK: -

typedef NS_OPTIONS(NSUInteger, SCNBillboardAxis) {
    SCNBillboardAxisX = 0x1 << 0,
    SCNBillboardAxisY = 0x1 << 1,
    SCNBillboardAxisZ = 0x1 << 2,
    SCNBillboardAxisAll = SCNBillboardAxisX | SCNBillboardAxisY | SCNBillboardAxisZ
};

SCN_EXPORT API_AVAILABLE(macos(10.11), ios(9.0))
@interface SCNBillboardConstraint : SCNConstraint

/*!
 @method billboardConstraint:
 @abstract Creates and returns a SCNBillboardConstraint constraint.
 @discussion A billboard constraint forces the receiver to look into the direction of the current point of view.
 */
+ (instancetype)billboardConstraint;

/*!
 @property freeAxes
 @abstract Specifies the axes on which the billboarding orientation operates. Defaults to SCNBillboardAxisAll.
 */
@property(nonatomic) SCNBillboardAxis freeAxes;

@end

// MARK: -

/*!
 @class SCNTransformConstraint
 @abstract A SCNTransformConstraint applies on the transform of a node via a custom block.
 */
SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNTransformConstraint : SCNConstraint

/*!
 @method transformConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its transform are passed to the block. The transform returned by the block will be used to render the node.
 */
+ (instancetype)transformConstraintInWorldSpace:(BOOL)world withBlock:(SCNMatrix4 (^)(SCNNode *node, SCNMatrix4 transform))block;

/*!
 @method positionConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its position are passed to the block. The position returned by the block will be used to render the node.
 */
+ (instancetype)positionConstraintInWorldSpace:(BOOL)world withBlock:(SCNVector3 (^)(SCNNode *node, SCNVector3 position))block API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @method orientationConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its quaternion are passed to the block. The quaternion returned by the block will be used to render the node.
 */
+ (instancetype)orientationConstraintInWorldSpace:(BOOL)world withBlock:(SCNQuaternion (^)(SCNNode *node, SCNQuaternion quaternion))block API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

// MARK: -

/*!
 @class SCNIKConstraint
 @abstract A SCNIKConstraint applies an inverse kinematics constraint
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNIKConstraint : SCNConstraint

/*!
 @method initWithChainRootNode:
 @abstract Creates and returns a SCNIKConstraint object with the specified parameter.
 @param chainRootNode The root node of the kinematic chain.
 @discussion "chainRootNode" must be an ancestor of the node on which the constraint is applied.
 */
- (instancetype)initWithChainRootNode:(SCNNode *)chainRootNode API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method inverseKinematicsConstraintWithChainRootNode:
 @abstract Creates and returns a SCNIKConstraint object with the specified parameter.
 @param chainRootNode The root node of the kinematic chain.
 @discussion "chainRootNode" must be an ancestor of the node on which the constraint is applied.
*/
+ (instancetype)inverseKinematicsConstraintWithChainRootNode:(SCNNode *)chainRootNode;

/*!
 @property chainRootNode
 @abstract Specifies the root node of the kinematic chain.
 */
@property(nonatomic, readonly) SCNNode *chainRootNode;

/*!
 @property target
 @abstract Specifies the target position (in world space coordinates) of the end joint (i.e the node that owns the IK constraint). Defaults to (0,0,0). Animatable.
 */
@property(nonatomic) SCNVector3 targetPosition;

/*!
 @method setMaxAllowedRotationAngle:forJoint:
 @abstract Specifies the maximum rotation allowed (in degrees) for the specified joint from its initial orientation. Defaults to 180.
 */
- (void)setMaxAllowedRotationAngle:(CGFloat)angle forJoint:(SCNNode *)node;
- (CGFloat)maxAllowedRotationAngleForJoint:(SCNNode *)node;

@end

// MARK: -

/*!
 @class SCNDistanceConstraint
 @abstract A SCNDistanceConstraint ensure a minimum/maximum distance with a target node.
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNDistanceConstraint : SCNConstraint

/*!
 @method distanceConstraintWithTarget
 @abstract Creates and returns a SCNDistanceConstraint constraint.
 */
+ (instancetype)distanceConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to keep distance with.
 */
@property(nonatomic, retain, nullable) SCNNode *target;

/*!
 @property minimumDistance
 @abstract The minimum distance. Defaults to 0. Animatable.
 */
@property(nonatomic, assign) CGFloat minimumDistance;

/*!
 @property maximumDistance
 @abstract The minimum distance. Defaults to MAXFLOAT. Animatable.
 */
@property(nonatomic, assign) CGFloat maximumDistance;

@end

// MARK: -

/*!
 @class SCNReplicatorConstraint
 @abstract A SCNReplicatorConstraint replicates the position/orientation/scale of a target node
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNReplicatorConstraint : SCNConstraint

/*!
 @method replicatorWithTargetNode
 @abstract Creates and returns a SCNReplicatorConstraint constraint.
 */
+ (instancetype)replicatorConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to replicate
 */
@property(nonatomic, retain, nullable) SCNNode *target;

/*!
 @property replicatesOrientation
 @abstract Defines whether or not the constraint should replicate the target orientation. Defaults to YES.
 */
@property(nonatomic, assign) BOOL replicatesOrientation;

/*!
 @property replicatesPosition
 @abstract Defines whether or not the constraint should replicate the target position. Defaults to YES.
 */
@property(nonatomic, assign) BOOL replicatesPosition;

/*!
 @property replicatesScale
 @abstract Defines whether or not the constraint should replicate the target scale. Defaults to YES.
 */
@property(nonatomic, assign) BOOL replicatesScale;

/*!
 @property orientationOffset
 @abstract Defines an addition orientation offset. Defaults to no offset. Animatable.
 */
@property(nonatomic, assign) SCNQuaternion orientationOffset;

/*!
 @property positionOffset
 @abstract Defines an addition orientation offset. Defaults to no offset. Animatable.
 */
@property(nonatomic, assign) SCNVector3 positionOffset;

/*!
 @property scaleOffset
 @abstract Defines an addition scale offset. Defaults to no offset. Animatable.
 */
@property(nonatomic, assign) SCNVector3 scaleOffset;

@end

// MARK: -

/*!
 @class SCNAccelerationConstraint
 @abstract A SCNAccelerationConstraint caps the acceleration and velocity of a node
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNAccelerationConstraint : SCNConstraint

/*!
 @method accelerationConstraint
 @abstract Creates and returns a SCNAccelerationConstraint object.
 */
+ (instancetype)accelerationConstraint;

/*!
 @property maximumLinearAcceleration
 @abstract Controls the maximum linear acceleration. Defaults to MAXFLOAT. Animatable.
 @discussion The maximum linear acceleration is in m.s^-2
 */
@property(nonatomic, assign) CGFloat maximumLinearAcceleration;

/*!
 @property maximumLinearVelocity
 @abstract Controls the maximum linear velocity. Defaults to MAXFLOAT. Animatable.
 @discussion The maximum linear velocity is in m.s
 */
@property(nonatomic, assign) CGFloat maximumLinearVelocity;

/*!
 @property decelerationDistance
 @abstract Controls the distance at which the node should start decelerating. Defaults to 0. Animatable.
 */
@property(nonatomic, assign) CGFloat decelerationDistance;

/*!
 @property damping
 @abstract Specifies the damping factor of the receiver. Optionally reduce the body's linear velocity each frame to simulate fluid/air friction. Value should be zero or greater. Defaults to 0.1. Animatable.
 */
@property(nonatomic, assign) CGFloat damping;

@end

// MARK: -

/*!
 @class SCNSliderConstraint
 @abstract A SCNSliderConstraint constraint makes a node to collide and slide against a category of nodes
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNSliderConstraint : SCNConstraint

/*!
 @method accelerationConstraint
 @abstract Creates and returns a SCNSliderConstraint object.
 */
+ (instancetype)sliderConstraint;

/*!
 @property collisionCategoryBitMask
 @abstract Defines the category of node to collide against. Defaults to 0.
 */
@property(nonatomic, assign) NSUInteger collisionCategoryBitMask;

/*!
 @property radius
 @abstract Defines the radius of the slider. Defaults to 1.
 */
@property(nonatomic, assign) CGFloat radius;

/*!
 @property offset
 @abstract Defines the offset of the slider. Defaults to (0,0,0). 
 */
@property(nonatomic, assign) SCNVector3 offset;

@end

// MARK: -

@class SCNAvoidOccluderConstraint;

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@protocol SCNAvoidOccluderConstraintDelegate <NSObject>
@optional
- (BOOL)avoidOccluderConstraint:(SCNAvoidOccluderConstraint *)constraint shouldAvoidOccluder:(SCNNode *)occluder forNode:(SCNNode *)node;
- (void)avoidOccluderConstraint:(SCNAvoidOccluderConstraint *)constraint didAvoidOccluder:(SCNNode *)occluder forNode:(SCNNode *)node;
@end

/*!
 @class SCNAvoidOccluderConstraint
 @abstract A SCNAvoidOccluderConstraint constraints place the receiver at a position that prevent nodes with the specified category to occlude the target.
 @discussion The target node and it's children are ignored as potential occluders.
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNAvoidOccluderConstraint : SCNConstraint

/*!
 @method avoidOccluderConstraintWithTarget
 @abstract Creates and returns a SCNAvoidOccluderConstraint object.
 */
+ (instancetype)avoidOccluderConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property delegate
 @abstract The receiver's delegate
 */
@property(nonatomic, assign) id <SCNAvoidOccluderConstraintDelegate> delegate;

/*!
 @property target
 @abstract Defines the target node
 */
@property(nonatomic, retain, nullable) SCNNode *target;

/*!
 @property occluderCategoryBitMask
 @abstract Defines the category of node to consider as occluder. Defaults to 1.
 */
@property(nonatomic, assign) NSUInteger occluderCategoryBitMask;

/*!
 @property bias
 @abstract Defines the bias the apply after moving the receiver to avoid occluders. Defaults to 10e-5.
 @discussion A positive bias will move the receiver closer to the target.
 */
@property(nonatomic, assign) CGFloat bias;

@end

NS_ASSUME_NONNULL_END
